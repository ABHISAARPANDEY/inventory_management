/**
 * @file product.c
 * @brief Implementation of product management functions
 */

#include "product.h"
#include <string.h>

void product_list_init(ProductList *list) {
    if (list == NULL) return;
    list->count = 0;
    memset(list->products, 0, sizeof(list->products));
}

int product_add(ProductList *list, const Product *product) {
    if (list == NULL || product == NULL) return 0;
    
    if (list->count >= MAX_PRODUCTS) {
        return 0;  // List is full
    }
    
    if (product_id_exists(list, product->id)) {
        return 0;  // Duplicate ID
    }
    
    if (!product_validate(product)) {
        return 0;  // Invalid product data
    }
    
    list->products[list->count] = *product;
    list->count++;
    return 1;
}

Product* product_find_by_id(ProductList *list, int id) {
    if (list == NULL) return NULL;
    
    for (int i = 0; i < list->count; i++) {
        if (list->products[i].id == id) {
            return &list->products[i];
        }
    }
    
    return NULL;
}

int product_find_by_name(ProductList *list, const char *name,
                         Product *results, int max_results) {
    if (list == NULL || name == NULL || results == NULL) return 0;
    
    int found = 0;
    char search_name[MAX_NAME_LEN];
    strncpy(search_name, name, sizeof(search_name) - 1);
    search_name[sizeof(search_name) - 1] = '\0';
    to_lowercase(search_name);
    
    for (int i = 0; i < list->count && found < max_results; i++) {
        char product_name[MAX_NAME_LEN];
        strncpy(product_name, list->products[i].name, sizeof(product_name) - 1);
        product_name[sizeof(product_name) - 1] = '\0';
        to_lowercase(product_name);
        
        if (strstr(product_name, search_name) != NULL) {
            results[found] = list->products[i];
            found++;
        }
    }
    
    return found;
}

int product_find_by_category(ProductList *list, const char *category,
                             Product *results, int max_results) {
    if (list == NULL || category == NULL || results == NULL) return 0;
    
    int found = 0;
    char search_category[MAX_CATEGORY_LEN];
    strncpy(search_category, category, sizeof(search_category) - 1);
    search_category[sizeof(search_category) - 1] = '\0';
    to_lowercase(search_category);
    
    for (int i = 0; i < list->count && found < max_results; i++) {
        char product_category[MAX_CATEGORY_LEN];
        strncpy(product_category, list->products[i].category, 
                sizeof(product_category) - 1);
        product_category[sizeof(product_category) - 1] = '\0';
        to_lowercase(product_category);
        
        if (strcmp(product_category, search_category) == 0) {
            results[found] = list->products[i];
            found++;
        }
    }
    
    return found;
}

int product_update(ProductList *list, int id, const Product *updated_product) {
    if (list == NULL || updated_product == NULL) return 0;
    
    Product *product = product_find_by_id(list, id);
    if (product == NULL) return 0;
    
    // Update all fields except ID
    strncpy(product->name, updated_product->name, MAX_NAME_LEN - 1);
    product->name[MAX_NAME_LEN - 1] = '\0';
    
    strncpy(product->category, updated_product->category, MAX_CATEGORY_LEN - 1);
    product->category[MAX_CATEGORY_LEN - 1] = '\0';
    
    strncpy(product->description, updated_product->description, MAX_DESC_LEN - 1);
    product->description[MAX_DESC_LEN - 1] = '\0';
    
    product->quantity_in_stock = updated_product->quantity_in_stock;
    product->reorder_level = updated_product->reorder_level;
    product->unit_price = updated_product->unit_price;
    product->supplier_id = updated_product->supplier_id;
    
    if (!product_validate(product)) {
        return 0;  // Updated data is invalid
    }
    
    return 1;
}

int product_delete(ProductList *list, int id) {
    if (list == NULL) return 0;
    
    int index = -1;
    for (int i = 0; i < list->count; i++) {
        if (list->products[i].id == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) return 0;
    
    // Shift remaining products
    for (int i = index; i < list->count - 1; i++) {
        list->products[i] = list->products[i + 1];
    }
    
    list->count--;
    return 1;
}

int product_get_all(ProductList *list, Product *results) {
    if (list == NULL || results == NULL) return 0;
    
    for (int i = 0; i < list->count; i++) {
        results[i] = list->products[i];
    }
    
    return list->count;
}

int product_id_exists(ProductList *list, int id) {
    return product_find_by_id(list, id) != NULL;
}

int product_validate(const Product *product) {
    if (product == NULL) return 0;
    
    if (product->id <= 0) return 0;
    if (strlen(product->name) == 0) return 0;
    if (product->quantity_in_stock < 0) return 0;
    if (product->unit_price < 0.0) return 0;
    if (product->reorder_level < 0) return 0;
    
    return 1;
}

int product_get_low_stock(ProductList *list, Product *results, int max_results) {
    if (list == NULL || results == NULL) return 0;
    
    int found = 0;
    for (int i = 0; i < list->count && found < max_results; i++) {
        if (list->products[i].quantity_in_stock <= list->products[i].reorder_level) {
            results[found] = list->products[i];
            found++;
        }
    }
    
    return found;
}

