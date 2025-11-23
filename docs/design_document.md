# Design Document - Inventory Management System

## Table of Contents

1. [Overview](#overview)
2. [System Architecture](#system-architecture)
3. [Module Description](#module-description)
4. [Data Model](#data-model)
5. [File Format Specification](#file-format-specification)
6. [Error Handling](#error-handling)
7. [Security Design](#security-design)
8. [Limitations](#limitations)
9. [Future Improvements](#future-improvements)

## Overview

The Inventory Management System is designed as a modular, command-line application using the C programming language. The system follows a layered architecture with clear separation of concerns between presentation, business logic, and data access layers.

### Design Principles

- **Modularity**: Each major feature is implemented as a separate module
- **Separation of Concerns**: UI, business logic, and data access are separated
- **Data Persistence**: All data is stored in structured text files
- **Error Handling**: Comprehensive error checking and user-friendly messages
- **Extensibility**: Code structure allows for future enhancements

## System Architecture

### Architecture Layers

```
┌─────────────────────────────────────┐
│     Presentation Layer (UI)          │
│  - Menus, Tables, User Input        │
└─────────────────────────────────────┘
              ↓
┌─────────────────────────────────────┐
│     Business Logic Layer             │
│  - Product Management               │
│  - Supplier Management               │
│  - Transaction Processing            │
│  - Reporting & Analytics             │
└─────────────────────────────────────┘
              ↓
┌─────────────────────────────────────┐
│     Data Access Layer                │
│  - File I/O Operations               │
│  - Data Persistence                  │
│  - Backup & Restore                  │
└─────────────────────────────────────┘
              ↓
┌─────────────────────────────────────┐
│     Data Storage (Files)             │
│  - products.txt                      │
│  - suppliers.txt                     │
│  - transactions.txt                  │
│  - users.txt                         │
└─────────────────────────────────────┘
```

### Module Dependencies

```
main.c
├── ui.h (User Interface)
├── auth.h (Authentication)
├── product.h (Product Management)
├── supplier.h (Supplier Management)
├── transaction.h (Transaction Management)
├── report.h (Reporting)
└── storage.h (File I/O)

All modules depend on:
└── utils.h (Common Utilities)
```

## Module Description

### 1. Main Module (`main.c`)

**Purpose**: Application entry point and menu orchestration

**Responsibilities**:
- Initialize system and load data
- Handle main application loop
- Route to appropriate menus based on user role
- Coordinate between modules
- Save data on exit

**Key Functions**:
- `main()`: Entry point
- `load_all_data()`: Load all data from files
- `save_all_data()`: Save all data to files
- `handle_login()`: Authentication flow
- `handle_admin_menu()`: Admin menu handler
- `handle_staff_menu()`: Staff menu handler

### 2. Product Module (`product.c/h`)

**Purpose**: Product entity and management operations

**Data Structure**:
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

**Key Functions**:
- `product_add()`: Add new product
- `product_find_by_id()`: Search by ID
- `product_find_by_name()`: Search by name (partial match)
- `product_find_by_category()`: Search by category
- `product_update()`: Update product details
- `product_delete()`: Delete product
- `product_get_low_stock()`: Get low stock items
- `product_validate()`: Validate product data

**Constraints**:
- Product ID must be unique
- Quantity must be >= 0
- Price must be >= 0
- Supplier ID must reference existing supplier

### 3. Supplier Module (`supplier.c/h`)

**Purpose**: Supplier entity and management operations

**Data Structure**:
```c
typedef struct {
    int supplier_id;
    char name[100];
    char contact_number[20];
    char email[100];
    char address[200];
} Supplier;
```

**Key Functions**:
- `supplier_add()`: Add new supplier
- `supplier_find_by_id()`: Search by ID
- `supplier_update()`: Update supplier details
- `supplier_delete()`: Delete supplier
- `supplier_validate()`: Validate supplier data

**Constraints**:
- Supplier ID must be unique
- Email format validation (if provided)
- Phone format validation (if provided)

### 4. Transaction Module (`transaction.c/h`)

**Purpose**: Stock movement tracking and transaction logging

**Data Structure**:
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

**Key Functions**:
- `transaction_add()`: Add new transaction
- `transaction_get_by_product()`: Get transactions for a product
- `transaction_get_by_date_range()`: Filter by date range
- `transaction_get_next_id()`: Generate next transaction ID
- `transaction_validate()`: Validate transaction data

**Transaction Types**:
- `IN`: Stock increase (stock in)
- `OUT`: Stock decrease (stock out)

### 5. Authentication Module (`auth.c/h`)

**Purpose**: User authentication and authorization

**Data Structure**:
```c
typedef struct {
    char username[50];
    char password_hash[65];  // SHA-256 hash
    char role[10];  // "ADMIN" or "STAFF"
} User;

typedef struct {
    User *user;
    int is_logged_in;
} Session;
```

**Key Functions**:
- `hash_password()`: Hash password using simple algorithm
- `verify_password()`: Verify password against hash
- `authenticate_user()`: Authenticate login attempt
- `is_admin()`: Check if user is admin
- `is_staff()`: Check if user is staff
- `session_login()`: Start user session
- `session_logout()`: End user session

**Security Notes**:
- Passwords are hashed before storage
- Hash function is basic (educational purpose)
- Role-based access control implemented

### 6. Storage Module (`storage.c/h`)

**Purpose**: File I/O operations and data persistence

**Key Functions**:
- `storage_load_products()`: Load products from file
- `storage_save_products()`: Save products to file
- `storage_load_suppliers()`: Load suppliers from file
- `storage_save_suppliers()`: Save suppliers to file
- `storage_load_transactions()`: Load transactions from file
- `storage_save_transactions()`: Save transactions to file
- `storage_load_users()`: Load users from file
- `storage_save_users()`: Save users to file
- `storage_backup_data()`: Backup all data files
- `storage_restore_data()`: Restore from backup
- `storage_init_directories()`: Create data directories

**File Format**: Pipe-delimited text files (see File Format Specification)

### 7. UI Module (`ui.c/h`)

**Purpose**: User interface and display functions

**Key Functions**:
- `ui_display_main_menu()`: Show main menu
- `ui_display_admin_menu()`: Show admin menu
- `ui_display_staff_menu()`: Show staff menu
- `ui_display_products_table()`: Display products in table format
- `ui_display_suppliers_table()`: Display suppliers in table format
- `ui_display_transactions_table()`: Display transactions in table
- `ui_input_product()`: Get product input from user
- `ui_input_supplier()`: Get supplier input from user
- `ui_get_confirmation()`: Get yes/no confirmation
- `ui_display_error()`: Show error message
- `ui_display_success()`: Show success message
- `ui_clear_screen()`: Clear terminal screen

**Features**:
- Formatted tables with alignment
- Low stock indicators
- Consistent header/footer styling
- User-friendly prompts

### 8. Report Module (`report.c/h`)

**Purpose**: Reporting and analytics functions

**Key Functions**:
- `report_total_products()`: Count total products
- `report_total_stock_value()`: Calculate total inventory value
- `report_top_products_by_quantity()`: Get top N by quantity
- `report_top_products_by_value()`: Get top N by value
- `report_low_stock_products()`: Get low stock items
- `report_transaction_count_by_date()`: Count transactions in date range

**Algorithms**:
- Uses `qsort()` for sorting products
- Comparison functions for quantity and value sorting

### 9. Utils Module (`utils.c/h`)

**Purpose**: Common utility functions

**Key Functions**:
- `get_current_datetime()`: Get formatted date/time string
- `read_string()`: Safe string input
- `read_integer()`: Safe integer input with validation
- `read_double()`: Safe double input with validation
- `trim_string()`: Remove leading/trailing whitespace
- `validate_email()`: Basic email validation
- `validate_phone()`: Basic phone validation
- `to_lowercase()`: Convert string to lowercase
- `clear_input_buffer()`: Clear stdin buffer
- `print_separator()`: Print separator line
- `pause_screen()`: Wait for user input

## Data Model

### Entity Relationships

```
Supplier (1) ────< (Many) Product
Product (1) ────< (Many) Transaction
```

- One supplier can have many products
- One product can have many transactions
- Products reference suppliers via `supplier_id`
- Transactions reference products via `product_id`

### Data Constraints

**Products**:
- `id`: Unique, positive integer
- `name`: Non-empty string, max 100 chars
- `quantity_in_stock`: Non-negative integer
- `unit_price`: Non-negative double
- `reorder_level`: Non-negative integer
- `supplier_id`: Must reference existing supplier

**Suppliers**:
- `supplier_id`: Unique, positive integer
- `name`: Non-empty string, max 100 chars
- `email`: Valid email format (if provided)
- `contact_number`: Valid phone format (if provided)

**Transactions**:
- `transaction_id`: Unique, positive integer
- `product_id`: Must reference existing product
- `type`: Must be "IN" or "OUT"
- `quantity`: Positive integer
- `date_time`: Valid date/time string

**Users**:
- `username`: Unique, non-empty string
- `password_hash`: 64-character hex string
- `role`: Must be "ADMIN" or "STAFF"

## File Format Specification

### Products File (`data/products.txt`)

**Format**: Pipe-delimited text file

**Header** (first line):
```
id|name|category|description|quantity|reorder_level|price|supplier_id
```

**Data Lines**:
```
1001|Laptop Dell Inspiron|Electronics|15.6 inch laptop|50|10|599.99|1
1002|Wireless Mouse|Electronics|USB wireless mouse|100|20|25.50|1
```

**Fields**:
- `id`: Integer
- `name`: String (no pipes)
- `category`: String
- `description`: String (no pipes)
- `quantity`: Integer
- `reorder_level`: Integer
- `price`: Decimal number
- `supplier_id`: Integer

### Suppliers File (`data/suppliers.txt`)

**Format**: Pipe-delimited text file

**Header**:
```
supplier_id|name|contact_number|email|address
```

**Data Lines**:
```
1|Tech Supplies Inc.|+1-555-0123|contact@techsupplies.com|123 Main St
```

### Transactions File (`data/transactions.txt`)

**Format**: Pipe-delimited text file

**Header**:
```
transaction_id|product_id|type|quantity|date_time|notes
```

**Data Lines**:
```
1|1001|IN|25|2025-01-15 10:30:00|Received new shipment
2|1001|OUT|5|2025-01-15 14:20:00|Sold to customer
```

### Users File (`data/users.txt`)

**Format**: Pipe-delimited text file

**Header**:
```
username|password_hash|role
```

**Data Lines**:
```
admin|a1b2c3d4e5f6...|ADMIN
staff|f6e5d4c3b2a1...|STAFF
```

## Error Handling

### Input Validation

- **Integer Input**: Validates numeric input, rejects non-numeric
- **Double Input**: Validates decimal numbers
- **String Input**: Trims whitespace, validates length
- **Email/Phone**: Format validation using regex-like checks

### File Operations

- **File Open**: Checks if file exists, creates if needed
- **File Read**: Validates file format, handles corrupted data
- **File Write**: Checks write permissions, handles disk full errors
- **Directory Creation**: Creates directories if they don't exist

### Business Logic Errors

- **Duplicate IDs**: Prevents adding duplicate product/supplier IDs
- **Invalid References**: Validates foreign key references
- **Negative Stock**: Prevents stock out that would result in negative quantity
- **Invalid Data**: Validates all data before saving

### Error Messages

All errors display user-friendly messages:
- `[ERROR] Invalid product ID.`
- `[ERROR] Product ID already exists.`
- `[ERROR] Insufficient stock.`
- `[ERROR] Supplier ID does not exist.`

## Security Design

### Authentication

- **Password Hashing**: Passwords are hashed before storage
- **Hash Algorithm**: Simple hash function (educational purpose)
- **Session Management**: Tracks logged-in user and role

### Authorization

- **Role-Based Access**: Admin vs Staff roles
- **Admin Access**: Full CRUD operations
- **Staff Access**: Limited to viewing and stock operations

### Input Security

- **Buffer Overflow Prevention**: Uses safe string functions with size limits
- **Input Validation**: Validates all user inputs
- **Data Sanitization**: Trims and validates strings

### Limitations

- Password hashing is basic (not cryptographically secure)
- No encryption for data files
- Single-user access (no concurrent sessions)
- No network security (local files only)

## Limitations

### Current Limitations

1. **Data Structure Limits**:
   - Maximum 1000 products
   - Maximum 500 suppliers
   - Maximum 5000 transactions
   - Maximum 100 users

2. **Functionality Limits**:
   - Text-based UI only
   - No concurrent user support
   - No network capabilities
   - Basic password security

3. **Performance Limits**:
   - Linear search algorithms
   - In-memory data structures
   - No indexing or caching

4. **Data Persistence**:
   - Text files only (no database)
   - No transaction rollback
   - No data versioning

## Future Improvements

### Short-term Enhancements

1. **Database Backend**:
   - Migrate to SQLite for better data management
   - Support for larger datasets
   - Better query performance

2. **Enhanced Security**:
   - Use cryptographically secure password hashing (bcrypt, Argon2)
   - Encrypt sensitive data files
   - Implement password policies

3. **Improved UI**:
   - Better table formatting
   - Pagination for large lists
   - Search highlighting

### Medium-term Enhancements

1. **GUI Version**:
   - GTK or Qt-based graphical interface
   - Better user experience
   - Visual charts and graphs

2. **Advanced Features**:
   - Barcode/QR code scanning
   - Email notifications for low stock
   - Export to Excel/PDF
   - Import from CSV

3. **Multi-user Support**:
   - Concurrent user access
   - User activity logging
   - Permission granularity

### Long-term Enhancements

1. **Network Capabilities**:
   - Client-server architecture
   - Remote access
   - Cloud storage integration

2. **Advanced Analytics**:
   - Sales forecasting
   - Demand prediction
   - Inventory optimization
   - Cost analysis

3. **Integration**:
   - API for third-party integration
   - Web-based interface
   - Mobile app support
   - POS system integration

## Performance Considerations

### Current Performance

- **Search Operations**: O(n) linear search
- **Sort Operations**: O(n log n) using qsort
- **File I/O**: Sequential read/write
- **Memory Usage**: All data loaded into memory

### Optimization Opportunities

- Implement binary search for sorted data
- Add indexing for faster lookups
- Implement caching for frequently accessed data
- Use memory-mapped files for large datasets

## Testing Strategy

### Unit Testing

- Test individual functions with various inputs
- Test edge cases and boundary conditions
- Test error handling

### Integration Testing

- Test module interactions
- Test data flow between modules
- Test file I/O operations

### System Testing

- Test complete user workflows
- Test with various data sizes
- Test error recovery

## Conclusion

This design document outlines the architecture, modules, data model, and design decisions for the Inventory Management System. The system is designed to be modular, maintainable, and extensible, providing a solid foundation for future enhancements.

---

**Version**: 1.0.0  
**Last Updated**: 2025

