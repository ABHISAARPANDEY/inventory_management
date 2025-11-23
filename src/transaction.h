/**
 * @file transaction.h
 * @brief Transaction/Stock movement entity and operations
 * @author Inventory Management System
 * @date 2025
 */

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "utils.h"

#define MAX_TRANSACTIONS 5000
#define TRANSACTION_TYPE_IN "IN"
#define TRANSACTION_TYPE_OUT "OUT"

/**
 * @brief Transaction structure
 */
typedef struct {
    int transaction_id;              ///< Unique transaction identifier
    int product_id;                  ///< Associated product ID
    char type[10];                   ///< "IN" or "OUT"
    int quantity;                    ///< Quantity moved
    char date_time[30];              ///< Date and time of transaction
    char notes[MAX_NOTES_LEN];       ///< Optional notes
} Transaction;

/**
 * @brief Transaction list structure
 */
typedef struct {
    Transaction transactions[MAX_TRANSACTIONS];
    int count;
} TransactionList;

/**
 * @brief Initialize transaction list
 * @param list Pointer to TransactionList structure
 */
void transaction_list_init(TransactionList *list);

/**
 * @brief Add a new transaction
 * @param list Pointer to TransactionList
 * @param transaction Transaction to add
 * @return 1 on success, 0 if list is full
 */
int transaction_add(TransactionList *list, const Transaction *transaction);

/**
 * @brief Find transaction by ID
 * @param list Pointer to TransactionList
 * @param id Transaction ID to search for
 * @return Pointer to transaction if found, NULL otherwise
 */
Transaction* transaction_find_by_id(TransactionList *list, int id);

/**
 * @brief Get transactions for a specific product
 * @param list Pointer to TransactionList
 * @param product_id Product ID to filter by
 * @param results Output array
 * @param max_results Maximum number of results
 * @return Number of transactions found
 */
int transaction_get_by_product(TransactionList *list, int product_id,
                               Transaction *results, int max_results);

/**
 * @brief Get transactions within a date range
 * @param list Pointer to TransactionList
 * @param start_date Start date string (YYYY-MM-DD format)
 * @param end_date End date string (YYYY-MM-DD format)
 * @param results Output array
 * @param max_results Maximum number of results
 * @return Number of transactions found
 */
int transaction_get_by_date_range(TransactionList *list, 
                                  const char *start_date,
                                  const char *end_date,
                                  Transaction *results, 
                                  int max_results);

/**
 * @brief Get all transactions
 * @param list Pointer to TransactionList
 * @param results Output array
 * @return Number of transactions
 */
int transaction_get_all(TransactionList *list, Transaction *results);

/**
 * @brief Get next available transaction ID
 * @param list Pointer to TransactionList
 * @return Next available ID
 */
int transaction_get_next_id(TransactionList *list);

/**
 * @brief Validate transaction data
 * @param transaction Transaction to validate
 * @return 1 if valid, 0 otherwise
 */
int transaction_validate(const Transaction *transaction);

#endif /* TRANSACTION_H */

