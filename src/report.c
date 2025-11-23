/**
 * @file report.c
 * @brief Implementation of reporting functions
 */

#include "report.h"
#include <stdlib.h>
#include <string.h>

int report_total_products(const ProductList *list) {
    if (list == NULL) return 0;
    return list->count;
}

double report_total_stock_value(const ProductList *list) {
    if (list == NULL) return 0.0;
    
    double total = 0.0;
    for (int i = 0; i < list->count; i++) {
        total += list->products[i].quantity_in_stock * list->products[i].unit_price;
    }
    
    return total;
}

// Comparison function for sorting by quantity (descending)
static int compare_by_quantity(const void *a, const void *b) {
    const Product *pa = (const Product *)a;
    const Product *pb = (const Product *)b;
    
    if (pa->quantity_in_stock > pb->quantity_in_stock) return -1;
    if (pa->quantity_in_stock < pb->quantity_in_stock) return 1;
    return 0;
}

// Comparison function for sorting by value (descending)
static int compare_by_value(const void *a, const void *b) {
    const Product *pa = (const Product *)a;
    const Product *pb = (const Product *)b;
    
    double value_a = pa->quantity_in_stock * pa->unit_price;
    double value_b = pb->quantity_in_stock * pb->unit_price;
    
    if (value_a > value_b) return -1;
    if (value_a < value_b) return 1;
    return 0;
}

int report_top_products_by_quantity(const ProductList *list,
                                   Product *results, int n) {
    if (list == NULL || results == NULL || n <= 0) return 0;
    
    // Copy all products to results
    int count = (n < list->count) ? n : list->count;
    Product *temp = malloc(sizeof(Product) * list->count);
    if (temp == NULL) return 0;
    
    for (int i = 0; i < list->count; i++) {
        temp[i] = list->products[i];
    }
    
    // Sort by quantity
    qsort(temp, list->count, sizeof(Product), compare_by_quantity);
    
    // Copy top N
    for (int i = 0; i < count; i++) {
        results[i] = temp[i];
    }
    
    free(temp);
    return count;
}

int report_top_products_by_value(const ProductList *list,
                                Product *results, int n) {
    if (list == NULL || results == NULL || n <= 0) return 0;
    
    // Copy all products to results
    int count = (n < list->count) ? n : list->count;
    Product *temp = malloc(sizeof(Product) * list->count);
    if (temp == NULL) return 0;
    
    for (int i = 0; i < list->count; i++) {
        temp[i] = list->products[i];
    }
    
    // Sort by value
    qsort(temp, list->count, sizeof(Product), compare_by_value);
    
    // Copy top N
    for (int i = 0; i < count; i++) {
        results[i] = temp[i];
    }
    
    free(temp);
    return count;
}

int report_low_stock_products(const ProductList *list,
                             Product *results, int max_results) {
    if (list == NULL || results == NULL) return 0;
    
    return product_get_low_stock((ProductList *)list, results, max_results);
}

int report_transaction_count_by_date(const TransactionList *list,
                                     const char *start_date,
                                     const char *end_date) {
    if (list == NULL || start_date == NULL || end_date == NULL) return 0;
    
    int count = 0;
    for (int i = 0; i < list->count; i++) {
        // Extract date part
        char date_str[11];
        strncpy(date_str, list->transactions[i].date_time, 10);
        date_str[10] = '\0';
        
        if (strcmp(date_str, start_date) >= 0 && 
            strcmp(date_str, end_date) <= 0) {
            count++;
        }
    }
    
    return count;
}

