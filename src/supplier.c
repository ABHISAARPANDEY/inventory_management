/**
 * @file supplier.c
 * @brief Implementation of supplier management functions
 */

#include "supplier.h"
#include <string.h>

void supplier_list_init(SupplierList *list) {
    if (list == NULL) return;
    list->count = 0;
    memset(list->suppliers, 0, sizeof(list->suppliers));
}

int supplier_add(SupplierList *list, const Supplier *supplier) {
    if (list == NULL || supplier == NULL) return 0;
    
    if (list->count >= MAX_SUPPLIERS) {
        return 0;  // List is full
    }
    
    if (supplier_id_exists(list, supplier->supplier_id)) {
        return 0;  // Duplicate ID
    }
    
    if (!supplier_validate(supplier)) {
        return 0;  // Invalid supplier data
    }
    
    list->suppliers[list->count] = *supplier;
    list->count++;
    return 1;
}

Supplier* supplier_find_by_id(SupplierList *list, int id) {
    if (list == NULL) return NULL;
    
    for (int i = 0; i < list->count; i++) {
        if (list->suppliers[i].supplier_id == id) {
            return &list->suppliers[i];
        }
    }
    
    return NULL;
}

int supplier_update(SupplierList *list, int id, const Supplier *updated_supplier) {
    if (list == NULL || updated_supplier == NULL) return 0;
    
    Supplier *supplier = supplier_find_by_id(list, id);
    if (supplier == NULL) return 0;
    
    // Update all fields except ID
    strncpy(supplier->name, updated_supplier->name, MAX_NAME_LEN - 1);
    supplier->name[MAX_NAME_LEN - 1] = '\0';
    
    strncpy(supplier->contact_number, updated_supplier->contact_number, 
            MAX_PHONE_LEN - 1);
    supplier->contact_number[MAX_PHONE_LEN - 1] = '\0';
    
    strncpy(supplier->email, updated_supplier->email, MAX_EMAIL_LEN - 1);
    supplier->email[MAX_EMAIL_LEN - 1] = '\0';
    
    strncpy(supplier->address, updated_supplier->address, MAX_ADDRESS_LEN - 1);
    supplier->address[MAX_ADDRESS_LEN - 1] = '\0';
    
    if (!supplier_validate(supplier)) {
        return 0;  // Updated data is invalid
    }
    
    return 1;
}

int supplier_delete(SupplierList *list, int id) {
    if (list == NULL) return 0;
    
    int index = -1;
    for (int i = 0; i < list->count; i++) {
        if (list->suppliers[i].supplier_id == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) return 0;
    
    // Shift remaining suppliers
    for (int i = index; i < list->count - 1; i++) {
        list->suppliers[i] = list->suppliers[i + 1];
    }
    
    list->count--;
    return 1;
}

int supplier_get_all(SupplierList *list, Supplier *results) {
    if (list == NULL || results == NULL) return 0;
    
    for (int i = 0; i < list->count; i++) {
        results[i] = list->suppliers[i];
    }
    
    return list->count;
}

int supplier_id_exists(SupplierList *list, int id) {
    return supplier_find_by_id(list, id) != NULL;
}

int supplier_validate(const Supplier *supplier) {
    if (supplier == NULL) return 0;
    
    if (supplier->supplier_id <= 0) return 0;
    if (strlen(supplier->name) == 0) return 0;
    
    // Optional validation for email and phone
    if (strlen(supplier->email) > 0 && !validate_email(supplier->email)) {
        return 0;
    }
    
    if (strlen(supplier->contact_number) > 0 && 
        !validate_phone(supplier->contact_number)) {
        return 0;
    }
    
    return 1;
}

