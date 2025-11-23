/**
 * @file transaction.c
 * @brief Implementation of transaction management functions
 */

#include "transaction.h"
#include <string.h>

void transaction_list_init(TransactionList *list) {
    if (list == NULL) return;
    list->count = 0;
    memset(list->transactions, 0, sizeof(list->transactions));
}

int transaction_add(TransactionList *list, const Transaction *transaction) {
    if (list == NULL || transaction == NULL) return 0;
    
    if (list->count >= MAX_TRANSACTIONS) {
        return 0;  // List is full
    }
    
    if (!transaction_validate(transaction)) {
        return 0;  // Invalid transaction data
    }
    
    list->transactions[list->count] = *transaction;
    list->count++;
    return 1;
}

Transaction* transaction_find_by_id(TransactionList *list, int id) {
    if (list == NULL) return NULL;
    
    for (int i = 0; i < list->count; i++) {
        if (list->transactions[i].transaction_id == id) {
            return &list->transactions[i];
        }
    }
    
    return NULL;
}

int transaction_get_by_product(TransactionList *list, int product_id,
                               Transaction *results, int max_results) {
    if (list == NULL || results == NULL) return 0;
    
    int found = 0;
    for (int i = 0; i < list->count && found < max_results; i++) {
        if (list->transactions[i].product_id == product_id) {
            results[found] = list->transactions[i];
            found++;
        }
    }
    
    return found;
}

int transaction_get_by_date_range(TransactionList *list,
                                  const char *start_date,
                                  const char *end_date,
                                  Transaction *results,
                                  int max_results) {
    if (list == NULL || start_date == NULL || end_date == NULL || 
        results == NULL) {
        return 0;
    }
    
    int found = 0;
    for (int i = 0; i < list->count && found < max_results; i++) {
        // Extract date part (first 10 characters: YYYY-MM-DD)
        char date_str[11];
        strncpy(date_str, list->transactions[i].date_time, 10);
        date_str[10] = '\0';
        
        // Simple string comparison (works for YYYY-MM-DD format)
        if (strcmp(date_str, start_date) >= 0 && 
            strcmp(date_str, end_date) <= 0) {
            results[found] = list->transactions[i];
            found++;
        }
    }
    
    return found;
}

int transaction_get_all(TransactionList *list, Transaction *results) {
    if (list == NULL || results == NULL) return 0;
    
    for (int i = 0; i < list->count; i++) {
        results[i] = list->transactions[i];
    }
    
    return list->count;
}

int transaction_get_next_id(TransactionList *list) {
    if (list == NULL) return 1;
    
    int max_id = 0;
    for (int i = 0; i < list->count; i++) {
        if (list->transactions[i].transaction_id > max_id) {
            max_id = list->transactions[i].transaction_id;
        }
    }
    
    return max_id + 1;
}

int transaction_validate(const Transaction *transaction) {
    if (transaction == NULL) return 0;
    
    if (transaction->transaction_id <= 0) return 0;
    if (transaction->product_id <= 0) return 0;
    if (transaction->quantity <= 0) return 0;
    
    // Check transaction type
    if (strcmp(transaction->type, TRANSACTION_TYPE_IN) != 0 &&
        strcmp(transaction->type, TRANSACTION_TYPE_OUT) != 0) {
        return 0;
    }
    
    if (strlen(transaction->date_time) == 0) return 0;
    
    return 1;
}

