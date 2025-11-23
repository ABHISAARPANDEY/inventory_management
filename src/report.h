/**
 * @file report.h
 * @brief Reporting and analytics functions
 * @author Inventory Management System
 * @date 2025
 */

#ifndef REPORT_H
#define REPORT_H

#include "product.h"
#include "supplier.h"
#include "transaction.h"

/**
 * @brief Calculate total number of products
 * @param list Pointer to ProductList
 * @return Total number of products
 */
int report_total_products(const ProductList *list);

/**
 * @brief Calculate total stock value (sum of quantity * price)
 * @param list Pointer to ProductList
 * @return Total stock value
 */
double report_total_stock_value(const ProductList *list);

/**
 * @brief Get top N products by quantity
 * @param list Pointer to ProductList
 * @param results Output array
 * @param n Number of top products to retrieve
 * @return Number of products returned
 */
int report_top_products_by_quantity(const ProductList *list, 
                                   Product *results, int n);

/**
 * @brief Get top N products by value (quantity * price)
 * @param list Pointer to ProductList
 * @param results Output array
 * @param n Number of top products to retrieve
 * @return Number of products returned
 */
int report_top_products_by_value(const ProductList *list,
                                Product *results, int n);

/**
 * @brief Get low stock products (quantity <= reorder_level)
 * @param list Pointer to ProductList
 * @param results Output array
 * @param max_results Maximum number of results
 * @return Number of low stock products
 */
int report_low_stock_products(const ProductList *list,
                             Product *results, int max_results);

/**
 * @brief Get transaction count within date range
 * @param list Pointer to TransactionList
 * @param start_date Start date (YYYY-MM-DD)
 * @param end_date End date (YYYY-MM-DD)
 * @return Number of transactions
 */
int report_transaction_count_by_date(const TransactionList *list,
                                     const char *start_date,
                                     const char *end_date);

#endif /* REPORT_H */

