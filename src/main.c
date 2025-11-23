/**
 * @file main.c
 * @brief Main entry point for Inventory Management System
 * @author Inventory Management System
 * @date 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "supplier.h"
#include "transaction.h"
#include "auth.h"
#include "storage.h"
#include "ui.h"
#include "report.h"
#include "utils.h"

// Global data structures
static ProductList products;
static SupplierList suppliers;
static TransactionList transactions;
static UserList users;
static Session session;

/**
 * @brief Load all data from files
 */
void load_all_data(void) {
    storage_init_directories();
    storage_load_products(&products);
    storage_load_suppliers(&suppliers);
    storage_load_transactions(&transactions);
    storage_load_users(&users);
}

/**
 * @brief Save all data to files
 */
void save_all_data(void) {
    storage_save_products(&products);
    storage_save_suppliers(&suppliers);
    storage_save_transactions(&transactions);
    storage_save_users(&users);
}

/**
 * @brief Handle login process
 * @return 1 on successful login, 0 on failure or cancel
 */
int handle_login(void) {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    
    ui_clear_screen();
    ui_display_header("LOGIN");
    
    printf("Username: ");
    if (!read_string(username, sizeof(username))) {
        return 0;
    }
    
    printf("Password: ");
    // Simple password input (no masking for simplicity)
    if (!read_string(password, sizeof(password))) {
        return 0;
    }
    
    User *user = authenticate_user(&users, username, password);
    if (user == NULL) {
        ui_display_error("Invalid username or password.");
        return 0;
    }
    
    session_login(&session, user);
    ui_display_success("Login successful!");
    return 1;
}

/**
 * @brief Handle product management menu
 */
void handle_product_management(void) {
    int choice;
    Product product;
    Product search_results[MAX_PRODUCTS];
    int search_count;
    int product_id;
    
    while (1) {
        ui_display_product_menu();
        if (!read_integer(&choice)) {
            ui_display_error("Invalid input.");
            continue;
        }
        
        switch (choice) {
            case 1:  // Add Product
                if (ui_input_product(&product, 0)) {
                    if (product_id_exists(&products, product.id)) {
                        ui_display_error("Product ID already exists.");
                    } else if (!supplier_id_exists(&suppliers, product.supplier_id)) {
                        ui_display_error("Supplier ID does not exist.");
                    } else if (product_add(&products, &product)) {
                        save_all_data();
                        ui_display_success("Product added successfully!");
                    } else {
                        ui_display_error("Failed to add product.");
                    }
                }
                break;
                
            case 2:  // View All Products
                ui_display_products_table(&products);
                pause_screen();
                break;
                
            case 3:  // Search by ID
                printf("Enter Product ID: ");
                if (read_integer(&product_id)) {
                    Product *p = product_find_by_id(&products, product_id);
                    ui_display_product(p);
                    pause_screen();
                } else {
                    ui_display_error("Invalid product ID.");
                }
                break;
                
            case 4:  // Search by Name
                printf("Enter product name (partial match): ");
                char name[100];
                if (read_string(name, sizeof(name))) {
                    search_count = product_find_by_name(&products, name, 
                                                       search_results, MAX_PRODUCTS);
                    if (search_count > 0) {
                        ProductList temp_list = {0};
                        for (int i = 0; i < search_count; i++) {
                            product_add(&temp_list, &search_results[i]);
                        }
                        ui_display_products_table(&temp_list);
                    } else {
                        printf("\nNo products found.\n");
                    }
                    pause_screen();
                }
                break;
                
            case 5:  // Search by Category
                printf("Enter category: ");
                char category[50];
                if (read_string(category, sizeof(category))) {
                    search_count = product_find_by_category(&products, category,
                                                           search_results, MAX_PRODUCTS);
                    if (search_count > 0) {
                        ProductList temp_list = {0};
                        for (int i = 0; i < search_count; i++) {
                            product_add(&temp_list, &search_results[i]);
                        }
                        ui_display_products_table(&temp_list);
                    } else {
                        printf("\nNo products found.\n");
                    }
                    pause_screen();
                }
                break;
                
            case 6:  // Edit Product
                printf("Enter Product ID to edit: ");
                if (read_integer(&product_id)) {
                    Product *p = product_find_by_id(&products, product_id);
                    if (p == NULL) {
                        ui_display_error("Product not found.");
                    } else {
                        product = *p;
                        if (ui_input_product(&product, 1)) {
                            if (!supplier_id_exists(&suppliers, product.supplier_id)) {
                                ui_display_error("Supplier ID does not exist.");
                            } else if (product_update(&products, product_id, &product)) {
                                save_all_data();
                                ui_display_success("Product updated successfully!");
                            } else {
                                ui_display_error("Failed to update product.");
                            }
                        }
                    }
                } else {
                    ui_display_error("Invalid product ID.");
                }
                break;
                
            case 7:  // Delete Product
                printf("Enter Product ID to delete: ");
                if (read_integer(&product_id)) {
                    Product *p = product_find_by_id(&products, product_id);
                    if (p == NULL) {
                        ui_display_error("Product not found.");
                    } else {
                        if (ui_get_confirmation("Are you sure you want to delete this product?")) {
                            if (product_delete(&products, product_id)) {
                                save_all_data();
                                ui_display_success("Product deleted successfully!");
                            } else {
                                ui_display_error("Failed to delete product.");
                            }
                        }
                    }
                } else {
                    ui_display_error("Invalid product ID.");
                }
                break;
                
            case 8:  // Low Stock Products
                search_count = product_get_low_stock(&products, search_results, MAX_PRODUCTS);
                if (search_count > 0) {
                    ProductList temp_list = {0};
                    for (int i = 0; i < search_count; i++) {
                        product_add(&temp_list, &search_results[i]);
                    }
                    ui_display_products_table(&temp_list);
                } else {
                    printf("\nNo low stock products.\n");
                }
                pause_screen();
                break;
                
            case 9:  // Back
                return;
                
            default:
                ui_display_error("Invalid choice.");
                break;
        }
    }
}

/**
 * @brief Handle supplier management menu
 */
void handle_supplier_management(void) {
    int choice;
    Supplier supplier;
    int supplier_id;
    
    while (1) {
        ui_display_supplier_menu();
        if (!read_integer(&choice)) {
            ui_display_error("Invalid input.");
            continue;
        }
        
        switch (choice) {
            case 1:  // Add Supplier
                if (ui_input_supplier(&supplier, 0)) {
                    if (supplier_id_exists(&suppliers, supplier.supplier_id)) {
                        ui_display_error("Supplier ID already exists.");
                    } else if (supplier_add(&suppliers, &supplier)) {
                        save_all_data();
                        ui_display_success("Supplier added successfully!");
                    } else {
                        ui_display_error("Failed to add supplier.");
                    }
                }
                break;
                
            case 2:  // View All Suppliers
                ui_display_suppliers_table(&suppliers);
                pause_screen();
                break;
                
            case 3:  // Edit Supplier
                printf("Enter Supplier ID to edit: ");
                if (read_integer(&supplier_id)) {
                    Supplier *s = supplier_find_by_id(&suppliers, supplier_id);
                    if (s == NULL) {
                        ui_display_error("Supplier not found.");
                    } else {
                        supplier = *s;
                        if (ui_input_supplier(&supplier, 1)) {
                            if (supplier_update(&suppliers, supplier_id, &supplier)) {
                                save_all_data();
                                ui_display_success("Supplier updated successfully!");
                            } else {
                                ui_display_error("Failed to update supplier.");
                            }
                        }
                    }
                } else {
                    ui_display_error("Invalid supplier ID.");
                }
                break;
                
            case 4:  // Delete Supplier
                printf("Enter Supplier ID to delete: ");
                if (read_integer(&supplier_id)) {
                    Supplier *s = supplier_find_by_id(&suppliers, supplier_id);
                    if (s == NULL) {
                        ui_display_error("Supplier not found.");
                    } else {
                        // Check if supplier is used by any product
                        int used = 0;
                        for (int i = 0; i < products.count; i++) {
                            if (products.products[i].supplier_id == supplier_id) {
                                used = 1;
                                break;
                            }
                        }
                        
                        if (used) {
                            ui_display_error("Cannot delete supplier: products are using this supplier.");
                        } else if (ui_get_confirmation("Are you sure you want to delete this supplier?")) {
                            if (supplier_delete(&suppliers, supplier_id)) {
                                save_all_data();
                                ui_display_success("Supplier deleted successfully!");
                            } else {
                                ui_display_error("Failed to delete supplier.");
                            }
                        }
                    }
                } else {
                    ui_display_error("Invalid supplier ID.");
                }
                break;
                
            case 5:  // Back
                return;
                
            default:
                ui_display_error("Invalid choice.");
                break;
        }
    }
}

/**
 * @brief Handle stock operations
 */
void handle_stock_operations(void) {
    int choice;
    int product_id;
    int quantity;
    char notes[MAX_NOTES_LEN];
    Transaction transaction;
    
    while (1) {
        ui_display_stock_menu();
        if (!read_integer(&choice)) {
            ui_display_error("Invalid input.");
            continue;
        }
        
        switch (choice) {
            case 1:  // Stock In
                printf("Enter Product ID: ");
                if (!read_integer(&product_id)) {
                    ui_display_error("Invalid product ID.");
                    break;
                }
                
                Product *p = product_find_by_id(&products, product_id);
                if (p == NULL) {
                    ui_display_error("Product not found.");
                    break;
                }
                
                printf("Enter quantity to add: ");
                if (!read_integer(&quantity) || quantity <= 0) {
                    ui_display_error("Invalid quantity.");
                    break;
                }
                
                printf("Enter notes (optional): ");
                if (!read_string(notes, sizeof(notes))) {
                    notes[0] = '\0';
                }
                
                // Update product quantity
                p->quantity_in_stock += quantity;
                
                // Create transaction
                transaction.transaction_id = transaction_get_next_id(&transactions);
                transaction.product_id = product_id;
                strcpy(transaction.type, TRANSACTION_TYPE_IN);
                transaction.quantity = quantity;
                get_current_datetime(transaction.date_time, sizeof(transaction.date_time));
                strncpy(transaction.notes, notes, sizeof(transaction.notes) - 1);
                transaction.notes[sizeof(transaction.notes) - 1] = '\0';
                
                transaction_add(&transactions, &transaction);
                save_all_data();
                
                printf("\nStock updated successfully!\n");
                printf("New quantity: %d\n", p->quantity_in_stock);
                pause_screen();
                break;
                
            case 2:  // Stock Out
                printf("Enter Product ID: ");
                if (!read_integer(&product_id)) {
                    ui_display_error("Invalid product ID.");
                    break;
                }
                
                p = product_find_by_id(&products, product_id);
                if (p == NULL) {
                    ui_display_error("Product not found.");
                    break;
                }
                
                printf("Enter quantity to remove: ");
                if (!read_integer(&quantity) || quantity <= 0) {
                    ui_display_error("Invalid quantity.");
                    break;
                }
                
                if (quantity > p->quantity_in_stock) {
                    ui_display_error("Insufficient stock. Available quantity is insufficient.");
                    break;
                }
                
                printf("Enter notes (optional): ");
                if (!read_string(notes, sizeof(notes))) {
                    notes[0] = '\0';
                }
                
                // Update product quantity
                p->quantity_in_stock -= quantity;
                
                // Create transaction
                transaction.transaction_id = transaction_get_next_id(&transactions);
                transaction.product_id = product_id;
                strcpy(transaction.type, TRANSACTION_TYPE_OUT);
                transaction.quantity = quantity;
                get_current_datetime(transaction.date_time, sizeof(transaction.date_time));
                strncpy(transaction.notes, notes, sizeof(transaction.notes) - 1);
                transaction.notes[sizeof(transaction.notes) - 1] = '\0';
                
                transaction_add(&transactions, &transaction);
                save_all_data();
                
                printf("\nStock updated successfully!\n");
                printf("New quantity: %d", p->quantity_in_stock);
                if (p->quantity_in_stock <= p->reorder_level) {
                    printf(" [LOW STOCK!]");
                }
                printf("\n");
                pause_screen();
                break;
                
            case 3:  // View Recent Transactions
                {
                    Transaction all_trans[MAX_TRANSACTIONS];
                    int count = transaction_get_all(&transactions, all_trans);
                    if (count > 0) {
                        // Show last 20 transactions
                        int start = (count > 20) ? count - 20 : 0;
                        ui_display_transactions_table(&all_trans[start], count - start);
                    } else {
                        printf("\nNo transactions found.\n");
                    }
                    pause_screen();
                }
                break;
                
            case 4:  // Back
                return;
                
            default:
                ui_display_error("Invalid choice.");
                break;
        }
    }
}

/**
 * @brief Handle reports menu
 */
void handle_reports(void) {
    int choice;
    Product top_products[MAX_PRODUCTS];
    int count;
    char start_date[11], end_date[11];
    Transaction date_trans[MAX_TRANSACTIONS];
    
    while (1) {
        ui_display_reports_menu();
        if (!read_integer(&choice)) {
            ui_display_error("Invalid input.");
            continue;
        }
        
        switch (choice) {
            case 1:  // Total Products
                printf("\nTotal number of products: %d\n", report_total_products(&products));
                pause_screen();
                break;
                
            case 2:  // Total Stock Value
                printf("\nTotal stock value: $%.2f\n", report_total_stock_value(&products));
                pause_screen();
                break;
                
            case 3:  // Top Products by Quantity
                printf("Enter number of top products to show: ");
                int n;
                if (read_integer(&n) && n > 0) {
                    count = report_top_products_by_quantity(&products, top_products, n);
                    if (count > 0) {
                        ProductList temp_list = {0};
                        for (int i = 0; i < count; i++) {
                            product_add(&temp_list, &top_products[i]);
                        }
                        ui_display_products_table(&temp_list);
                    } else {
                        printf("\nNo products found.\n");
                    }
                } else {
                    ui_display_error("Invalid number.");
                }
                pause_screen();
                break;
                
            case 4:  // Top Products by Value
                printf("Enter number of top products to show: ");
                if (read_integer(&n) && n > 0) {
                    count = report_top_products_by_value(&products, top_products, n);
                    if (count > 0) {
                        ProductList temp_list = {0};
                        for (int i = 0; i < count; i++) {
                            product_add(&temp_list, &top_products[i]);
                        }
                        ui_display_products_table(&temp_list);
                    } else {
                        printf("\nNo products found.\n");
                    }
                } else {
                    ui_display_error("Invalid number.");
                }
                pause_screen();
                break;
                
            case 5:  // Low Stock Products
                count = report_low_stock_products(&products, top_products, MAX_PRODUCTS);
                if (count > 0) {
                    ProductList temp_list = {0};
                    for (int i = 0; i < count; i++) {
                        product_add(&temp_list, &top_products[i]);
                    }
                    ui_display_products_table(&temp_list);
                } else {
                    printf("\nNo low stock products.\n");
                }
                pause_screen();
                break;
                
            case 6:  // Transactions by Date Range
                printf("Enter start date (YYYY-MM-DD): ");
                if (!read_string(start_date, sizeof(start_date))) {
                    ui_display_error("Invalid date format.");
                    break;
                }
                
                printf("Enter end date (YYYY-MM-DD): ");
                if (!read_string(end_date, sizeof(end_date))) {
                    ui_display_error("Invalid date format.");
                    break;
                }
                
                count = transaction_get_by_date_range(&transactions, start_date, end_date,
                                                      date_trans, MAX_TRANSACTIONS);
                if (count > 0) {
                    ui_display_transactions_table(date_trans, count);
                } else {
                    printf("\nNo transactions found in the specified date range.\n");
                }
                pause_screen();
                break;
                
            case 7:  // Back
                return;
                
            default:
                ui_display_error("Invalid choice.");
                break;
        }
    }
}

/**
 * @brief Handle staff menu (limited access)
 */
void handle_staff_menu(void) {
    int choice;
    Product search_results[MAX_PRODUCTS];
    int search_count;
    char name[100];
    
    while (1) {
        ui_display_staff_menu();
        if (!read_integer(&choice)) {
            ui_display_error("Invalid input.");
            continue;
        }
        
        switch (choice) {
            case 1:  // View Products
                ui_display_products_table(&products);
                pause_screen();
                break;
                
            case 2:  // Search Products
                printf("Enter product name (partial match): ");
                if (read_string(name, sizeof(name))) {
                    search_count = product_find_by_name(&products, name,
                                                       search_results, MAX_PRODUCTS);
                    if (search_count > 0) {
                        ProductList temp_list = {0};
                        for (int i = 0; i < search_count; i++) {
                            product_add(&temp_list, &search_results[i]);
                        }
                        ui_display_products_table(&temp_list);
                    } else {
                        printf("\nNo products found.\n");
                    }
                    pause_screen();
                }
                break;
                
            case 3:  // Stock Operations
                handle_stock_operations();
                break;
                
            case 4:  // Low Stock Products
                search_count = product_get_low_stock(&products, search_results, MAX_PRODUCTS);
                if (search_count > 0) {
                    ProductList temp_list = {0};
                    for (int i = 0; i < search_count; i++) {
                        product_add(&temp_list, &search_results[i]);
                    }
                    ui_display_products_table(&temp_list);
                } else {
                    printf("\nNo low stock products.\n");
                }
                pause_screen();
                break;
                
            case 5:  // Logout
                return;
                
            default:
                ui_display_error("Invalid choice.");
                break;
        }
    }
}

/**
 * @brief Handle admin menu (full access)
 */
void handle_admin_menu(void) {
    int choice;
    
    while (1) {
        ui_display_admin_menu();
        if (!read_integer(&choice)) {
            ui_display_error("Invalid input.");
            continue;
        }
        
        switch (choice) {
            case 1:  // Product Management
                handle_product_management();
                break;
                
            case 2:  // Supplier Management
                handle_supplier_management();
                break;
                
            case 3:  // Stock Operations
                handle_stock_operations();
                break;
                
            case 4:  // Reports
                handle_reports();
                break;
                
            case 5:  // Backup & Restore
                {
                    int backup_choice;
                    printf("\n1. Backup Data\n");
                    printf("2. Restore Data\n");
                    printf("3. Back\n");
                    printf("Enter choice: ");
                    
                    if (read_integer(&backup_choice)) {
                        switch (backup_choice) {
                            case 1:
                                if (storage_backup_data()) {
                                    ui_display_success("Data backed up successfully!");
                                } else {
                                    ui_display_error("Backup failed.");
                                }
                                break;
                                
                            case 2:
                                if (ui_get_confirmation("WARNING: This will overwrite current data. Continue?")) {
                                    if (storage_restore_data()) {
                                        load_all_data();  // Reload from restored files
                                        ui_display_success("Data restored successfully!");
                                    } else {
                                        ui_display_error("Restore failed.");
                                    }
                                }
                                break;
                                
                            case 3:
                                break;
                                
                            default:
                                ui_display_error("Invalid choice.");
                                break;
                        }
                    }
                }
                break;
                
            case 6:  // Logout
                return;
                
            default:
                ui_display_error("Invalid choice.");
                break;
        }
    }
}

/**
 * @brief Main function
 */
int main(void) {
    // Initialize session
    session_init(&session);
    
    // Load all data
    load_all_data();
    
    // Create default admin user if no users exist
    if (users.count == 0) {
        User admin = {0};
        strcpy(admin.username, "admin");
        hash_password("admin123", admin.password_hash);
        strcpy(admin.role, ROLE_ADMIN);
        user_add(&users, &admin);
        
        // Create default staff user
        User staff = {0};
        strcpy(staff.username, "staff");
        hash_password("staff123", staff.password_hash);
        strcpy(staff.role, ROLE_STAFF);
        user_add(&users, &staff);
        
        storage_save_users(&users);
    }
    
    // Main application loop
    int main_choice;
    while (1) {
        ui_display_main_menu();
        if (!read_integer(&main_choice)) {
            ui_display_error("Invalid input.");
            continue;
        }
        
        switch (main_choice) {
            case 1:  // Login
                if (handle_login()) {
                    // Route to appropriate menu based on role
                    if (is_admin(session.user)) {
                        handle_admin_menu();
                    } else if (is_staff(session.user)) {
                        handle_staff_menu();
                    }
                    session_logout(&session);
                }
                break;
                
            case 2:  // Exit
                save_all_data();
                printf("\nThank you for using Inventory Management System!\n");
                printf("All data has been saved.\n");
                return 0;
                
            default:
                ui_display_error("Invalid choice.");
                break;
        }
    }
    
    return 0;
}

