/**
 * @file storage.c
 * @brief Implementation of file I/O operations
 */

#include "storage.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#define mkdir(path, mode) _mkdir(path)
#define access(path, mode) _access(path, mode)
#define F_OK 0
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

int storage_init_directories(void) {
    // Create data directory if it doesn't exist
#ifdef _WIN32
    if (_access(DATA_DIR, 0) != 0) {
        if (_mkdir(DATA_DIR) != 0) {
            return 0;
        }
    }
    if (_access(BACKUP_DIR, 0) != 0) {
        if (_mkdir(BACKUP_DIR) != 0) {
            return 0;
        }
    }
#else
    struct stat st = {0};
    if (stat(DATA_DIR, &st) == -1) {
        if (mkdir(DATA_DIR, 0700) != 0) {
            return 0;
        }
    }
    if (stat(BACKUP_DIR, &st) == -1) {
        if (mkdir(BACKUP_DIR, 0700) != 0) {
            return 0;
        }
    }
#endif
    return 1;
}

int storage_load_products(ProductList *list) {
    if (list == NULL) return 0;
    
    FILE *file = fopen(PRODUCTS_FILE, "r");
    if (file == NULL) {
        // File doesn't exist yet, initialize empty list
        product_list_init(list);
        return 1;
    }
    
    product_list_init(list);
    
    char line[1000];
    // Skip header line if present
    if (fgets(line, sizeof(line), file) != NULL) {
        // Check if it's a header line
        if (strstr(line, "id|") == NULL) {
            // Not a header, rewind
            rewind(file);
        }
    }
    
    while (fgets(line, sizeof(line), file) != NULL && list->count < MAX_PRODUCTS) {
        Product p = {0};
        
        // Parse line: id|name|category|description|quantity|reorder_level|price|supplier_id
        char *token = strtok(line, "|\n");
        if (token == NULL) continue;
        p.id = atoi(token);
        
        token = strtok(NULL, "|\n");
        if (token == NULL) continue;
        strncpy(p.name, token, MAX_NAME_LEN - 1);
        p.name[MAX_NAME_LEN - 1] = '\0';
        
        token = strtok(NULL, "|\n");
        if (token == NULL) continue;
        strncpy(p.category, token, MAX_CATEGORY_LEN - 1);
        p.category[MAX_CATEGORY_LEN - 1] = '\0';
        
        token = strtok(NULL, "|\n");
        if (token == NULL) continue;
        strncpy(p.description, token, MAX_DESC_LEN - 1);
        p.description[MAX_DESC_LEN - 1] = '\0';
        
        token = strtok(NULL, "|\n");
        if (token == NULL) continue;
        p.quantity_in_stock = atoi(token);
        
        token = strtok(NULL, "|\n");
        if (token == NULL) continue;
        p.reorder_level = atoi(token);
        
        token = strtok(NULL, "|\n");
        if (token == NULL) continue;
        p.unit_price = atof(token);
        
        token = strtok(NULL, "|\n");
        if (token == NULL) continue;
        p.supplier_id = atoi(token);
        
        if (product_validate(&p)) {
            list->products[list->count] = p;
            list->count++;
        }
    }
    
    fclose(file);
    return 1;
}

int storage_save_products(const ProductList *list) {
    if (list == NULL) return 0;
    
    FILE *file = fopen(PRODUCTS_FILE, "w");
    if (file == NULL) return 0;
    
    // Write header
    fprintf(file, "id|name|category|description|quantity|reorder_level|price|supplier_id\n");
    
    for (int i = 0; i < list->count; i++) {
        const Product *p = &list->products[i];
        fprintf(file, "%d|%s|%s|%s|%d|%d|%.2f|%d\n",
                p->id, p->name, p->category, p->description,
                p->quantity_in_stock, p->reorder_level, p->unit_price, p->supplier_id);
    }
    
    fclose(file);
    return 1;
}

int storage_load_suppliers(SupplierList *list) {
    if (list == NULL) return 0;
    
    FILE *file = fopen(SUPPLIERS_FILE, "r");
    if (file == NULL) {
        supplier_list_init(list);
        return 1;
    }
    
    supplier_list_init(list);
    
    char line[1000];
    // Skip header line if present
    if (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "supplier_id|") == NULL) {
            rewind(file);
        }
    }
    
    while (fgets(line, sizeof(line), file) != NULL && list->count < MAX_SUPPLIERS) {
        Supplier s = {0};
        
        // Parse: supplier_id|name|contact_number|email|address
        char *token = strtok(line, "|\n");
        if (token == NULL) continue;
        s.supplier_id = atoi(token);
        
        token = strtok(NULL, "|\n");
        if (token == NULL) continue;
        strncpy(s.name, token, MAX_NAME_LEN - 1);
        s.name[MAX_NAME_LEN - 1] = '\0';
        
        token = strtok(NULL, "|\n");
        if (token == NULL) continue;
        strncpy(s.contact_number, token, MAX_PHONE_LEN - 1);
        s.contact_number[MAX_PHONE_LEN - 1] = '\0';
        
        token = strtok(NULL, "|\n");
        if (token == NULL) continue;
        strncpy(s.email, token, MAX_EMAIL_LEN - 1);
        s.email[MAX_EMAIL_LEN - 1] = '\0';
        
        token = strtok(NULL, "|\n");
        if (token == NULL) continue;
        strncpy(s.address, token, MAX_ADDRESS_LEN - 1);
        s.address[MAX_ADDRESS_LEN - 1] = '\0';
        
        if (supplier_validate(&s)) {
            list->suppliers[list->count] = s;
            list->count++;
        }
    }
    
    fclose(file);
    return 1;
}

int storage_save_suppliers(const SupplierList *list) {
    if (list == NULL) return 0;
    
    FILE *file = fopen(SUPPLIERS_FILE, "w");
    if (file == NULL) return 0;
    
    fprintf(file, "supplier_id|name|contact_number|email|address\n");
    
    for (int i = 0; i < list->count; i++) {
        const Supplier *s = &list->suppliers[i];
        fprintf(file, "%d|%s|%s|%s|%s\n",
                s->supplier_id, s->name, s->contact_number, s->email, s->address);
    }
    
    fclose(file);
    return 1;
}

int storage_load_transactions(TransactionList *list) {
    if (list == NULL) return 0;
    
    FILE *file = fopen(TRANSACTIONS_FILE, "r");
    if (file == NULL) {
        transaction_list_init(list);
        return 1;
    }
    
    transaction_list_init(list);
    
    char line[1000];
    // Skip header line if present
    if (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "transaction_id|") == NULL) {
            rewind(file);
        }
    }
    
    while (fgets(line, sizeof(line), file) != NULL && list->count < MAX_TRANSACTIONS) {
        Transaction t = {0};
        
        // Parse: transaction_id|product_id|type|quantity|date_time|notes
        char *token = strtok(line, "|\n");
        if (token == NULL) continue;
        t.transaction_id = atoi(token);
        
        token = strtok(NULL, "|\n");
        if (token == NULL) continue;
        t.product_id = atoi(token);
        
        token = strtok(NULL, "|\n");
        if (token == NULL) continue;
        strncpy(t.type, token, 9);
        t.type[9] = '\0';
        
        token = strtok(NULL, "|\n");
        if (token == NULL) continue;
        t.quantity = atoi(token);
        
        token = strtok(NULL, "|\n");
        if (token == NULL) continue;
        strncpy(t.date_time, token, 29);
        t.date_time[29] = '\0';
        
        token = strtok(NULL, "|\n");
        if (token != NULL) {
            strncpy(t.notes, token, MAX_NOTES_LEN - 1);
            t.notes[MAX_NOTES_LEN - 1] = '\0';
        }
        
        if (transaction_validate(&t)) {
            list->transactions[list->count] = t;
            list->count++;
        }
    }
    
    fclose(file);
    return 1;
}

int storage_save_transactions(const TransactionList *list) {
    if (list == NULL) return 0;
    
    FILE *file = fopen(TRANSACTIONS_FILE, "w");
    if (file == NULL) return 0;
    
    fprintf(file, "transaction_id|product_id|type|quantity|date_time|notes\n");
    
    for (int i = 0; i < list->count; i++) {
        const Transaction *t = &list->transactions[i];
        fprintf(file, "%d|%d|%s|%d|%s|%s\n",
                t->transaction_id, t->product_id, t->type, t->quantity, 
                t->date_time, t->notes);
    }
    
    fclose(file);
    return 1;
}

int storage_load_users(UserList *list) {
    if (list == NULL) return 0;
    
    FILE *file = fopen(USERS_FILE, "r");
    if (file == NULL) {
        user_list_init(list);
        return 1;
    }
    
    user_list_init(list);
    
    char line[500];
    // Skip header line if present
    if (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "username|") == NULL) {
            rewind(file);
        }
    }
    
    while (fgets(line, sizeof(line), file) != NULL && list->count < MAX_USERS) {
        User u = {0};
        
        // Parse: username|password_hash|role
        char *token = strtok(line, "|\n");
        if (token == NULL) continue;
        strncpy(u.username, token, MAX_USERNAME_LEN - 1);
        u.username[MAX_USERNAME_LEN - 1] = '\0';
        
        token = strtok(NULL, "|\n");
        if (token == NULL) continue;
        strncpy(u.password_hash, token, HASH_LENGTH - 1);
        u.password_hash[HASH_LENGTH - 1] = '\0';
        
        token = strtok(NULL, "|\n");
        if (token != NULL) {
            strncpy(u.role, token, 9);
            u.role[9] = '\0';
        } else {
            strcpy(u.role, ROLE_STAFF);  // Default role
        }
        
        list->users[list->count] = u;
        list->count++;
    }
    
    fclose(file);
    return 1;
}

int storage_save_users(const UserList *list) {
    if (list == NULL) return 0;
    
    FILE *file = fopen(USERS_FILE, "w");
    if (file == NULL) return 0;
    
    fprintf(file, "username|password_hash|role\n");
    
    for (int i = 0; i < list->count; i++) {
        const User *u = &list->users[i];
        fprintf(file, "%s|%s|%s\n", u->username, u->password_hash, u->role);
    }
    
    fclose(file);
    return 1;
}

int storage_backup_data(void) {
    char backup_path[200];
    FILE *src, *dst;
    char buffer[4096];
    size_t bytes;
    
    // Backup products
    snprintf(backup_path, sizeof(backup_path), "%s/products.txt", BACKUP_DIR);
    src = fopen(PRODUCTS_FILE, "rb");
    if (src != NULL) {
        dst = fopen(backup_path, "wb");
        if (dst != NULL) {
            while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
                fwrite(buffer, 1, bytes, dst);
            }
            fclose(dst);
        }
        fclose(src);
    }
    
    // Backup suppliers
    snprintf(backup_path, sizeof(backup_path), "%s/suppliers.txt", BACKUP_DIR);
    src = fopen(SUPPLIERS_FILE, "rb");
    if (src != NULL) {
        dst = fopen(backup_path, "wb");
        if (dst != NULL) {
            while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
                fwrite(buffer, 1, bytes, dst);
            }
            fclose(dst);
        }
        fclose(src);
    }
    
    // Backup transactions
    snprintf(backup_path, sizeof(backup_path), "%s/transactions.txt", BACKUP_DIR);
    src = fopen(TRANSACTIONS_FILE, "rb");
    if (src != NULL) {
        dst = fopen(backup_path, "wb");
        if (dst != NULL) {
            while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
                fwrite(buffer, 1, bytes, dst);
            }
            fclose(dst);
        }
        fclose(src);
    }
    
    // Backup users
    snprintf(backup_path, sizeof(backup_path), "%s/users.txt", BACKUP_DIR);
    src = fopen(USERS_FILE, "rb");
    if (src != NULL) {
        dst = fopen(backup_path, "wb");
        if (dst != NULL) {
            while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
                fwrite(buffer, 1, bytes, dst);
            }
            fclose(dst);
        }
        fclose(src);
    }
    
    return 1;
}

int storage_restore_data(void) {
    char backup_path[200];
    FILE *src, *dst;
    char buffer[4096];
    size_t bytes;
    
    // Restore products
    snprintf(backup_path, sizeof(backup_path), "%s/products.txt", BACKUP_DIR);
    src = fopen(backup_path, "rb");
    if (src != NULL) {
        dst = fopen(PRODUCTS_FILE, "wb");
        if (dst != NULL) {
            while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
                fwrite(buffer, 1, bytes, dst);
            }
            fclose(dst);
        }
        fclose(src);
    }
    
    // Restore suppliers
    snprintf(backup_path, sizeof(backup_path), "%s/suppliers.txt", BACKUP_DIR);
    src = fopen(backup_path, "rb");
    if (src != NULL) {
        dst = fopen(SUPPLIERS_FILE, "wb");
        if (dst != NULL) {
            while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
                fwrite(buffer, 1, bytes, dst);
            }
            fclose(dst);
        }
        fclose(src);
    }
    
    // Restore transactions
    snprintf(backup_path, sizeof(backup_path), "%s/transactions.txt", BACKUP_DIR);
    src = fopen(backup_path, "rb");
    if (src != NULL) {
        dst = fopen(TRANSACTIONS_FILE, "wb");
        if (dst != NULL) {
            while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
                fwrite(buffer, 1, bytes, dst);
            }
            fclose(dst);
        }
        fclose(src);
    }
    
    // Restore users
    snprintf(backup_path, sizeof(backup_path), "%s/users.txt", BACKUP_DIR);
    src = fopen(backup_path, "rb");
    if (src != NULL) {
        dst = fopen(USERS_FILE, "wb");
        if (dst != NULL) {
            while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
                fwrite(buffer, 1, bytes, dst);
            }
            fclose(dst);
        }
        fclose(src);
    }
    
    return 1;
}

