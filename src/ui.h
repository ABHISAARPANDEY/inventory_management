/**
 * @file ui.h
 * @brief User interface functions for menus and display
 * @author Inventory Management System
 * @date 2025
 */

#ifndef UI_H
#define UI_H

#include "product.h"
#include "supplier.h"
#include "transaction.h"
#include "auth.h"

/**
 * @brief Display main menu (before login)
 */
void ui_display_main_menu(void);

/**
 * @brief Display admin menu
 */
void ui_display_admin_menu(void);

/**
 * @brief Display staff menu
 */
void ui_display_staff_menu(void);

/**
 * @brief Display product management submenu
 */
void ui_display_product_menu(void);

/**
 * @brief Display supplier management submenu
 */
void ui_display_supplier_menu(void);

/**
 * @brief Display stock operations menu
 */
void ui_display_stock_menu(void);

/**
 * @brief Display reports menu
 */
void ui_display_reports_menu(void);

/**
 * @brief Display header with title
 * @param title Title to display
 */
void ui_display_header(const char *title);

/**
 * @brief Display all products in a table format
 * @param list Pointer to ProductList
 */
void ui_display_products_table(const ProductList *list);

/**
 * @brief Display a single product
 * @param product Pointer to Product
 */
void ui_display_product(const Product *product);

/**
 * @brief Display all suppliers in a table format
 * @param list Pointer to SupplierList
 */
void ui_display_suppliers_table(const SupplierList *list);

/**
 * @brief Display a single supplier
 * @param supplier Pointer to Supplier
 */
void ui_display_supplier(const Supplier *supplier);

/**
 * @brief Display transactions in a table format
 * @param transactions Array of transactions
 * @param count Number of transactions
 */
void ui_display_transactions_table(const Transaction *transactions, int count);

/**
 * @brief Display a single transaction
 * @param transaction Pointer to Transaction
 */
void ui_display_transaction(const Transaction *transaction);

/**
 * @brief Get user input for product details
 * @param product Pointer to Product structure to fill
 * @param is_edit 1 if editing existing product, 0 if adding new
 * @return 1 on success, 0 on cancel
 */
int ui_input_product(Product *product, int is_edit);

/**
 * @brief Get user input for supplier details
 * @param supplier Pointer to Supplier structure to fill
 * @param is_edit 1 if editing existing supplier, 0 if adding new
 * @return 1 on success, 0 on cancel
 */
int ui_input_supplier(Supplier *supplier, int is_edit);

/**
 * @brief Get confirmation from user
 * @param message Message to display
 * @return 1 if yes, 0 if no
 */
int ui_get_confirmation(const char *message);

/**
 * @brief Display error message
 * @param message Error message
 */
void ui_display_error(const char *message);

/**
 * @brief Display success message
 * @param message Success message
 */
void ui_display_success(const char *message);

/**
 * @brief Display info message
 * @param message Info message
 */
void ui_display_info(const char *message);

/**
 * @brief Clear screen (platform-independent)
 */
void ui_clear_screen(void);

#endif /* UI_H */

