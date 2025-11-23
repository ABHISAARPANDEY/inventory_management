/**
 * @file ui.c
 * @brief Implementation of UI functions
 */

#include "ui.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <stdlib.h>
#endif

void ui_clear_screen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void ui_display_header(const char *title) {
    printf("\n");
    print_separator(80, '=');
    printf("%*s\n", (int)(40 + strlen(title) / 2), title);
    print_separator(80, '=');
    printf("\n");
}

void ui_display_main_menu(void) {
    ui_clear_screen();
    ui_display_header("INVENTORY MANAGEMENT SYSTEM");
    printf("1. Login\n");
    printf("2. Exit\n");
    printf("\nEnter your choice: ");
}

void ui_display_admin_menu(void) {
    ui_clear_screen();
    ui_display_header("ADMIN MENU");
    printf("1. Product Management\n");
    printf("2. Supplier Management\n");
    printf("3. Stock Operations\n");
    printf("4. Reports\n");
    printf("5. Backup & Restore\n");
    printf("6. Logout\n");
    printf("\nEnter your choice: ");
}

void ui_display_staff_menu(void) {
    ui_clear_screen();
    ui_display_header("STAFF MENU");
    printf("1. View Products\n");
    printf("2. Search Products\n");
    printf("3. Stock Operations\n");
    printf("4. View Low Stock Products\n");
    printf("5. Logout\n");
    printf("\nEnter your choice: ");
}

void ui_display_product_menu(void) {
    ui_clear_screen();
    ui_display_header("PRODUCT MANAGEMENT");
    printf("1. Add Product\n");
    printf("2. View All Products\n");
    printf("3. Search Product by ID\n");
    printf("4. Search Product by Name\n");
    printf("5. Search Product by Category\n");
    printf("6. Edit Product\n");
    printf("7. Delete Product\n");
    printf("8. View Low Stock Products\n");
    printf("9. Back to Main Menu\n");
    printf("\nEnter your choice: ");
}

void ui_display_supplier_menu(void) {
    ui_clear_screen();
    ui_display_header("SUPPLIER MANAGEMENT");
    printf("1. Add Supplier\n");
    printf("2. View All Suppliers\n");
    printf("3. Edit Supplier\n");
    printf("4. Delete Supplier\n");
    printf("5. Back to Main Menu\n");
    printf("\nEnter your choice: ");
}

void ui_display_stock_menu(void) {
    ui_clear_screen();
    ui_display_header("STOCK OPERATIONS");
    printf("1. Stock In\n");
    printf("2. Stock Out\n");
    printf("3. View Recent Transactions\n");
    printf("4. Back to Main Menu\n");
    printf("\nEnter your choice: ");
}

void ui_display_reports_menu(void) {
    ui_clear_screen();
    ui_display_header("REPORTS & ANALYTICS");
    printf("1. Total Products Count\n");
    printf("2. Total Stock Value\n");
    printf("3. Top Products by Quantity\n");
    printf("4. Top Products by Value\n");
    printf("5. Low Stock Products\n");
    printf("6. Transactions by Date Range\n");
    printf("7. Back to Main Menu\n");
    printf("\nEnter your choice: ");
}

void ui_display_products_table(const ProductList *list) {
    if (list == NULL || list->count == 0) {
        printf("\nNo products found.\n");
        return;
    }
    
    printf("\n");
    print_separator(120, '-');
    printf("%-6s %-20s %-15s %-25s %-8s %-8s %-10s %-8s\n",
           "ID", "Name", "Category", "Description", "Qty", "Reorder", "Price", "Supp ID");
    print_separator(120, '-');
    
    for (int i = 0; i < list->count; i++) {
        const Product *p = &list->products[i];
        int is_low_stock = (p->quantity_in_stock <= p->reorder_level);
        
        if (is_low_stock) {
            printf("*");  // Mark low stock
        } else {
            printf(" ");
        }
        
        printf("%-5d %-20s %-15s %-25s %-8d %-8d $%-9.2f %-8d",
               p->id, p->name, p->category, p->description,
               p->quantity_in_stock, p->reorder_level, p->unit_price, p->supplier_id);
        
        if (is_low_stock) {
            printf(" [LOW STOCK]");
        }
        printf("\n");
    }
    
    print_separator(120, '-');
    printf("\n* = Low Stock Item\n");
}

void ui_display_product(const Product *product) {
    if (product == NULL) {
        printf("Product not found.\n");
        return;
    }
    
    printf("\n");
    print_separator(60, '-');
    printf("Product Details\n");
    print_separator(60, '-');
    printf("ID:              %d\n", product->id);
    printf("Name:            %s\n", product->name);
    printf("Category:        %s\n", product->category);
    printf("Description:    %s\n", product->description);
    printf("Quantity:       %d", product->quantity_in_stock);
    if (product->quantity_in_stock <= product->reorder_level) {
        printf(" [LOW STOCK!]");
    }
    printf("\n");
    printf("Reorder Level:  %d\n", product->reorder_level);
    printf("Unit Price:     $%.2f\n", product->unit_price);
    printf("Supplier ID:    %d\n", product->supplier_id);
    print_separator(60, '-');
}

void ui_display_suppliers_table(const SupplierList *list) {
    if (list == NULL || list->count == 0) {
        printf("\nNo suppliers found.\n");
        return;
    }
    
    printf("\n");
    print_separator(100, '-');
    printf("%-8s %-25s %-20s %-30s %-30s\n",
           "ID", "Name", "Contact", "Email", "Address");
    print_separator(100, '-');
    
    for (int i = 0; i < list->count; i++) {
        const Supplier *s = &list->suppliers[i];
        printf("%-8d %-25s %-20s %-30s %-30s\n",
               s->supplier_id, s->name, s->contact_number, s->email, s->address);
    }
    
    print_separator(100, '-');
}

void ui_display_supplier(const Supplier *supplier) {
    if (supplier == NULL) {
        printf("Supplier not found.\n");
        return;
    }
    
    printf("\n");
    print_separator(60, '-');
    printf("Supplier Details\n");
    print_separator(60, '-');
    printf("ID:             %d\n", supplier->supplier_id);
    printf("Name:           %s\n", supplier->name);
    printf("Contact:        %s\n", supplier->contact_number);
    printf("Email:          %s\n", supplier->email);
    printf("Address:        %s\n", supplier->address);
    print_separator(60, '-');
}

void ui_display_transactions_table(const Transaction *transactions, int count) {
    if (transactions == NULL || count == 0) {
        printf("\nNo transactions found.\n");
        return;
    }
    
    printf("\n");
    print_separator(100, '-');
    printf("%-8s %-8s %-6s %-8s %-20s %-30s\n",
           "Trans ID", "Prod ID", "Type", "Qty", "Date/Time", "Notes");
    print_separator(100, '-');
    
    for (int i = 0; i < count; i++) {
        const Transaction *t = &transactions[i];
        printf("%-8d %-8d %-6s %-8d %-20s %-30s\n",
               t->transaction_id, t->product_id, t->type, t->quantity,
               t->date_time, t->notes);
    }
    
    print_separator(100, '-');
}

void ui_display_transaction(const Transaction *transaction) {
    if (transaction == NULL) {
        printf("Transaction not found.\n");
        return;
    }
    
    printf("\n");
    print_separator(60, '-');
    printf("Transaction Details\n");
    print_separator(60, '-');
    printf("Transaction ID: %d\n", transaction->transaction_id);
    printf("Product ID:     %d\n", transaction->product_id);
    printf("Type:          %s\n", transaction->type);
    printf("Quantity:      %d\n", transaction->quantity);
    printf("Date/Time:     %s\n", transaction->date_time);
    printf("Notes:         %s\n", transaction->notes);
    print_separator(60, '-');
}

int ui_input_product(Product *product, int is_edit) {
    if (product == NULL) return 0;
    
    if (!is_edit) {
        printf("Enter Product ID: ");
        if (!read_integer(&product->id) || product->id <= 0) {
            ui_display_error("Invalid product ID.");
            return 0;
        }
    } else {
        printf("Product ID: %d (cannot be changed)\n", product->id);
    }
    
    printf("Enter Product Name: ");
    if (!read_string(product->name, sizeof(product->name)) || 
        strlen(product->name) == 0) {
        ui_display_error("Product name cannot be empty.");
        return 0;
    }
    
    printf("Enter Category: ");
    if (!read_string(product->category, sizeof(product->category)) ||
        strlen(product->category) == 0) {
        ui_display_error("Category cannot be empty.");
        return 0;
    }
    
    printf("Enter Description: ");
    if (!read_string(product->description, sizeof(product->description))) {
        product->description[0] = '\0';  // Optional field
    }
    
    printf("Enter Quantity in Stock: ");
    if (!read_integer(&product->quantity_in_stock) || 
        product->quantity_in_stock < 0) {
        ui_display_error("Invalid quantity (must be >= 0).");
        return 0;
    }
    
    printf("Enter Reorder Level: ");
    if (!read_integer(&product->reorder_level) || 
        product->reorder_level < 0) {
        ui_display_error("Invalid reorder level (must be >= 0).");
        return 0;
    }
    
    printf("Enter Unit Price: ");
    if (!read_double(&product->unit_price) || product->unit_price < 0.0) {
        ui_display_error("Invalid price (must be >= 0).");
        return 0;
    }
    
    printf("Enter Supplier ID: ");
    if (!read_integer(&product->supplier_id) || product->supplier_id <= 0) {
        ui_display_error("Invalid supplier ID (must be > 0).");
        return 0;
    }
    
    return 1;
}

int ui_input_supplier(Supplier *supplier, int is_edit) {
    if (supplier == NULL) return 0;
    
    if (!is_edit) {
        printf("Enter Supplier ID: ");
        if (!read_integer(&supplier->supplier_id) || supplier->supplier_id <= 0) {
            ui_display_error("Invalid supplier ID.");
            return 0;
        }
    } else {
        printf("Supplier ID: %d (cannot be changed)\n", supplier->supplier_id);
    }
    
    printf("Enter Supplier Name: ");
    if (!read_string(supplier->name, sizeof(supplier->name)) ||
        strlen(supplier->name) == 0) {
        ui_display_error("Supplier name cannot be empty.");
        return 0;
    }
    
    printf("Enter Contact Number: ");
    if (!read_string(supplier->contact_number, sizeof(supplier->contact_number))) {
        supplier->contact_number[0] = '\0';
    } else if (strlen(supplier->contact_number) > 0 && 
               !validate_phone(supplier->contact_number)) {
        ui_display_error("Invalid phone number format.");
        return 0;
    }
    
    printf("Enter Email: ");
    if (!read_string(supplier->email, sizeof(supplier->email))) {
        supplier->email[0] = '\0';
    } else if (strlen(supplier->email) > 0 && 
               !validate_email(supplier->email)) {
        ui_display_error("Invalid email format.");
        return 0;
    }
    
    printf("Enter Address: ");
    if (!read_string(supplier->address, sizeof(supplier->address))) {
        supplier->address[0] = '\0';
    }
    
    return 1;
}

int ui_get_confirmation(const char *message) {
    if (message != NULL) {
        printf("%s (y/n): ", message);
    } else {
        printf("Are you sure? (y/n): ");
    }
    
    char response[10];
    if (!read_string(response, sizeof(response))) {
        return 0;
    }
    
    to_lowercase(response);
    return (response[0] == 'y');
}

void ui_display_error(const char *message) {
    printf("\n[ERROR] %s\n", message);
    pause_screen();
}

void ui_display_success(const char *message) {
    printf("\n[SUCCESS] %s\n", message);
    pause_screen();
}

void ui_display_info(const char *message) {
    printf("\n[INFO] %s\n", message);
}

