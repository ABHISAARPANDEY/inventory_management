/**
 * @file supplier.h
 * @brief Supplier entity and management operations
 * @author Inventory Management System
 * @date 2025
 */

#ifndef SUPPLIER_H
#define SUPPLIER_H

#include "utils.h"

#define MAX_SUPPLIERS 500

/**
 * @brief Supplier structure
 */
typedef struct {
    int supplier_id;                    ///< Unique supplier identifier
    char name[MAX_NAME_LEN];            ///< Supplier name
    char contact_number[MAX_PHONE_LEN]; ///< Contact phone number
    char email[MAX_EMAIL_LEN];          ///< Email address
    char address[MAX_ADDRESS_LEN];       ///< Physical address
} Supplier;

/**
 * @brief Supplier list structure
 */
typedef struct {
    Supplier suppliers[MAX_SUPPLIERS];
    int count;
} SupplierList;

/**
 * @brief Initialize supplier list
 * @param list Pointer to SupplierList structure
 */
void supplier_list_init(SupplierList *list);

/**
 * @brief Add a new supplier to the list
 * @param list Pointer to SupplierList
 * @param supplier Supplier to add
 * @return 1 on success, 0 if list is full or duplicate ID
 */
int supplier_add(SupplierList *list, const Supplier *supplier);

/**
 * @brief Find supplier by ID
 * @param list Pointer to SupplierList
 * @param id Supplier ID to search for
 * @return Pointer to supplier if found, NULL otherwise
 */
Supplier* supplier_find_by_id(SupplierList *list, int id);

/**
 * @brief Update supplier details
 * @param list Pointer to SupplierList
 * @param id Supplier ID to update
 * @param updated_supplier Updated supplier data
 * @return 1 on success, 0 if supplier not found
 */
int supplier_update(SupplierList *list, int id, const Supplier *updated_supplier);

/**
 * @brief Delete a supplier from the list
 * @param list Pointer to SupplierList
 * @param id Supplier ID to delete
 * @return 1 on success, 0 if supplier not found
 */
int supplier_delete(SupplierList *list, int id);

/**
 * @brief Get all suppliers
 * @param list Pointer to SupplierList
 * @param results Output array
 * @return Number of suppliers
 */
int supplier_get_all(SupplierList *list, Supplier *results);

/**
 * @brief Check if supplier ID exists
 * @param list Pointer to SupplierList
 * @param id Supplier ID to check
 * @return 1 if exists, 0 otherwise
 */
int supplier_id_exists(SupplierList *list, int id);

/**
 * @brief Validate supplier data
 * @param supplier Supplier to validate
 * @return 1 if valid, 0 otherwise
 */
int supplier_validate(const Supplier *supplier);

#endif /* SUPPLIER_H */

