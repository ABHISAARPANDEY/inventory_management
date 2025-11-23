/**
 * @file product.h
 * @brief Product entity and management operations
 * @author Inventory Management System
 * @date 2025
 */

#ifndef PRODUCT_H
#define PRODUCT_H

#include "utils.h"

#define MAX_PRODUCTS 1000
#define MAX_CATEGORY_LEN 50
#define MAX_DESC_LEN 200

/**
 * @brief Product structure
 */
typedef struct {
    int id;                          ///< Unique product identifier
    char name[MAX_NAME_LEN];         ///< Product name
    char category[MAX_CATEGORY_LEN]; ///< Product category
    char description[MAX_DESC_LEN];  ///< Product description
    int quantity_in_stock;            ///< Current stock quantity
    int reorder_level;               ///< Minimum stock level before reorder
    double unit_price;               ///< Price per unit
    int supplier_id;                 ///< Associated supplier ID
} Product;

/**
 * @brief Product list structure
 */
typedef struct {
    Product products[MAX_PRODUCTS];
    int count;
} ProductList;

/**
 * @brief Initialize product list
 * @param list Pointer to ProductList structure
 */
void product_list_init(ProductList *list);

/**
 * @brief Add a new product to the list
 * @param list Pointer to ProductList
 * @param product Product to add
 * @return 1 on success, 0 if list is full or duplicate ID
 */
int product_add(ProductList *list, const Product *product);

/**
 * @brief Find product by ID
 * @param list Pointer to ProductList
 * @param id Product ID to search for
 * @return Pointer to product if found, NULL otherwise
 */
Product* product_find_by_id(ProductList *list, int id);

/**
 * @brief Find products by name (partial match)
 * @param list Pointer to ProductList
 * @param name Name to search for
 * @param results Output array for results
 * @param max_results Maximum number of results
 * @return Number of products found
 */
int product_find_by_name(ProductList *list, const char *name, 
                         Product *results, int max_results);

/**
 * @brief Find products by category
 * @param list Pointer to ProductList
 * @param category Category to search for
 * @param results Output array for results
 * @param max_results Maximum number of results
 * @return Number of products found
 */
int product_find_by_category(ProductList *list, const char *category,
                             Product *results, int max_results);

/**
 * @brief Update product details (except ID)
 * @param list Pointer to ProductList
 * @param id Product ID to update
 * @param updated_product Updated product data
 * @return 1 on success, 0 if product not found
 */
int product_update(ProductList *list, int id, const Product *updated_product);

/**
 * @brief Delete a product from the list
 * @param list Pointer to ProductList
 * @param id Product ID to delete
 * @return 1 on success, 0 if product not found
 */
int product_delete(ProductList *list, int id);

/**
 * @brief Get all products
 * @param list Pointer to ProductList
 * @param results Output array
 * @return Number of products
 */
int product_get_all(ProductList *list, Product *results);

/**
 * @brief Check if product ID exists
 * @param list Pointer to ProductList
 * @param id Product ID to check
 * @return 1 if exists, 0 otherwise
 */
int product_id_exists(ProductList *list, int id);

/**
 * @brief Validate product data
 * @param product Product to validate
 * @return 1 if valid, 0 otherwise
 */
int product_validate(const Product *product);

/**
 * @brief Get products below reorder level
 * @param list Pointer to ProductList
 * @param results Output array
 * @param max_results Maximum number of results
 * @return Number of low stock products
 */
int product_get_low_stock(ProductList *list, Product *results, int max_results);

#endif /* PRODUCT_H */

