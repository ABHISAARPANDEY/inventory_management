/**
 * @file storage.h
 * @brief File I/O operations for data persistence
 * @author Inventory Management System
 * @date 2025
 */

#ifndef STORAGE_H
#define STORAGE_H

#include "product.h"
#include "supplier.h"
#include "transaction.h"
#include "auth.h"

#define DATA_DIR "data"
#define BACKUP_DIR "backup"

// File paths
#define PRODUCTS_FILE "data/products.txt"
#define SUPPLIERS_FILE "data/suppliers.txt"
#define TRANSACTIONS_FILE "data/transactions.txt"
#define USERS_FILE "data/users.txt"

/**
 * @brief Load all products from file
 * @param list Pointer to ProductList to populate
 * @return 1 on success, 0 on failure
 */
int storage_load_products(ProductList *list);

/**
 * @brief Save all products to file
 * @param list Pointer to ProductList to save
 * @return 1 on success, 0 on failure
 */
int storage_save_products(const ProductList *list);

/**
 * @brief Load all suppliers from file
 * @param list Pointer to SupplierList to populate
 * @return 1 on success, 0 on failure
 */
int storage_load_suppliers(SupplierList *list);

/**
 * @brief Save all suppliers to file
 * @param list Pointer to SupplierList to save
 * @return 1 on success, 0 on failure
 */
int storage_save_suppliers(const SupplierList *list);

/**
 * @brief Load all transactions from file
 * @param list Pointer to TransactionList to populate
 * @return 1 on success, 0 on failure
 */
int storage_load_transactions(TransactionList *list);

/**
 * @brief Save all transactions to file
 * @param list Pointer to TransactionList to save
 * @return 1 on success, 0 on failure
 */
int storage_save_transactions(const TransactionList *list);

/**
 * @brief Load all users from file
 * @param list Pointer to UserList to populate
 * @return 1 on success, 0 on failure
 */
int storage_load_users(UserList *list);

/**
 * @brief Save all users to file
 * @param list Pointer to UserList to save
 * @return 1 on success, 0 on failure
 */
int storage_save_users(const UserList *list);

/**
 * @brief Initialize data directory (create if doesn't exist)
 * @return 1 on success, 0 on failure
 */
int storage_init_directories(void);

/**
 * @brief Backup all data files to backup directory
 * @return 1 on success, 0 on failure
 */
int storage_backup_data(void);

/**
 * @brief Restore all data files from backup directory
 * @return 1 on success, 0 on failure
 */
int storage_restore_data(void);

#endif /* STORAGE_H */

