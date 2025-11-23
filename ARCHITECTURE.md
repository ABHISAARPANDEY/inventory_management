# Inventory Management System - Architecture Design

## System Overview

The Inventory Management System is a command-line application built in C that manages products, suppliers, stock transactions, and provides reporting capabilities. The system uses a modular architecture with clear separation of concerns.

## Architecture Layers

### 1. Presentation Layer (UI Module)
- **File**: `ui.c` / `ui.h`
- **Responsibility**: All user interface elements, menus, table formatting, input prompts
- **Functions**: Menu display, table printing, input validation helpers

### 2. Business Logic Layer
- **Product Module** (`product.c` / `product.h`): Product CRUD operations, search, validation
- **Supplier Module** (`supplier.c` / `supplier.h`): Supplier CRUD operations
- **Transaction Module** (`transaction.c` / `transaction.h`): Stock in/out operations, transaction logging
- **Report Module** (`report.c` / `report.h`): Analytics, statistics, low stock alerts

### 3. Data Access Layer
- **Storage Module** (`storage.c` / `storage.h`): File I/O operations, data persistence
- **Auth Module** (`auth.c` / `auth.h`): User authentication and authorization

### 4. Utility Layer
- **Utils Module** (`utils.c` / `utils.h`): Common helpers (input validation, date formatting, string operations)

### 5. Application Entry
- **Main Module** (`main.c`): Application entry point, menu orchestration, session management

## Data Model

### Product Structure
```c
typedef struct {
    int id;
    char name[100];
    char category[50];
    char description[200];
    int quantity_in_stock;
    int reorder_level;
    double unit_price;
    int supplier_id;
} Product;
```

### Supplier Structure
```c
typedef struct {
    int supplier_id;
    char name[100];
    char contact_number[20];
    char email[100];
    char address[200];
} Supplier;
```

### Transaction Structure
```c
typedef struct {
    int transaction_id;
    int product_id;
    char type[10];  // "IN" or "OUT"
    int quantity;
    char date_time[30];
    char notes[200];
} Transaction;
```

### User Structure
```c
typedef struct {
    char username[50];
    char password_hash[65];  // SHA-256 hash (64 chars + null)
    char role[10];  // "ADMIN" or "STAFF"
} User;
```

## File Format

### Data Persistence Strategy
Using structured text files (CSV-like format) for portability and human readability:

- `data/products.txt`: One product per line, fields separated by `|`
- `data/suppliers.txt`: One supplier per line, fields separated by `|`
- `data/transactions.txt`: One transaction per line, fields separated by `|`
- `data/users.txt`: One user per line, fields separated by `|`

Format example for products:
```
id|name|category|description|quantity|reorder_level|price|supplier_id
1|Laptop|Electronics|Dell Inspiron 15|50|10|599.99|1
```

## Module Dependencies

```
main.c
  ├── ui.h (menus, display)
  ├── auth.h (login)
  ├── product.h (product operations)
  ├── supplier.h (supplier operations)
  ├── transaction.h (stock operations)
  ├── report.h (reports)
  └── storage.h (backup/restore)

All modules depend on:
  └── utils.h (common utilities)
```

## Security Model

- Simple password hashing using SHA-256 (basic implementation)
- Role-based access control (Admin vs Staff)
- Input validation to prevent buffer overflows
- File operation error handling

## Error Handling Strategy

- All file operations check for errors
- Input validation prevents invalid data entry
- Graceful error messages with recovery options
- No program crashes on invalid input

