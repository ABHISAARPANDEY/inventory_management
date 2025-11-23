# User Manual - Inventory Management System

## Table of Contents

1. [Introduction](#introduction)
2. [Installation](#installation)
3. [Getting Started](#getting-started)
4. [Menu Guide](#menu-guide)
5. [Common Tasks](#common-tasks)
6. [Troubleshooting](#troubleshooting)

## Introduction

The Inventory Management System is a command-line application designed to help businesses manage their inventory efficiently. It provides features for tracking products, suppliers, stock movements, and generating reports.

### System Requirements

- Windows, Linux, or macOS operating system
- GCC compiler (MinGW on Windows)
- Make utility
- Terminal/Command Prompt

## Installation

### Step 1: Extract/Clone the Project

Extract the project files to a directory of your choice, or clone the repository.

### Step 2: Compile the Project

Open a terminal/command prompt in the project directory and run:

```bash
make
```

This will compile all source files and create the executable.

### Step 3: Create Data Directories

Run the install command to create necessary directories:

```bash
make install
```

Or manually create `data/` and `backup/` directories.

### Step 4: Run the Application

```bash
make run
```

Or directly execute:
- Linux/macOS: `./inventory`
- Windows: `inventory.exe`

## Getting Started

### First Launch

When you first run the application, it will automatically create default user accounts:

- **Admin Account**
  - Username: `admin`
  - Password: `admin123`

- **Staff Account**
  - Username: `staff`
  - Password: `staff123`

**Security Note**: Change these passwords immediately in a production environment!

### Login Screen

1. Select option `1` from the main menu to login
2. Enter your username
3. Enter your password
4. Press Enter

If login is successful, you'll see a menu based on your role (Admin or Staff).

## Menu Guide

### Main Menu (Before Login)

```
==========================================
     INVENTORY MANAGEMENT SYSTEM
==========================================

1. Login
2. Exit

Enter your choice:
```

### Admin Menu

Admins have full access to all system features:

```
==========================================
              ADMIN MENU
==========================================

1. Product Management
2. Supplier Management
3. Stock Operations
4. Reports
5. Backup & Restore
6. Logout

Enter your choice:
```

### Staff Menu

Staff members have limited access:

```
==========================================
              STAFF MENU
==========================================

1. View Products
2. Search Products
3. Stock Operations
4. View Low Stock Products
5. Logout

Enter your choice:
```

### Product Management Menu (Admin Only)

```
==========================================
         PRODUCT MANAGEMENT
==========================================

1. Add Product
2. View All Products
3. Search Product by ID
4. Search Product by Name
5. Search Product by Category
6. Edit Product
7. Delete Product
8. View Low Stock Products
9. Back to Main Menu

Enter your choice:
```

### Supplier Management Menu (Admin Only)

```
==========================================
        SUPPLIER MANAGEMENT
==========================================

1. Add Supplier
2. View All Suppliers
3. Edit Supplier
4. Delete Supplier
5. Back to Main Menu

Enter your choice:
```

### Stock Operations Menu

```
==========================================
         STOCK OPERATIONS
==========================================

1. Stock In
2. Stock Out
3. View Recent Transactions
4. Back to Main Menu

Enter your choice:
```

### Reports Menu (Admin Only)

```
==========================================
        REPORTS & ANALYTICS
==========================================

1. Total Products Count
2. Total Stock Value
3. Top Products by Quantity
4. Top Products by Value
5. Low Stock Products
6. Transactions by Date Range
7. Back to Main Menu

Enter your choice:
```

## Common Tasks

### Task 1: Adding a Product

**Prerequisites**: Admin access, supplier must exist

1. Login as admin
2. Select `1` (Product Management)
3. Select `1` (Add Product)
4. Enter the following information:
   - **Product ID**: Unique integer (e.g., 1001)
   - **Product Name**: Name of the product (e.g., "Laptop Dell Inspiron")
   - **Category**: Product category (e.g., "Electronics")
   - **Description**: Brief description (optional)
   - **Quantity in Stock**: Current stock level (e.g., 50)
   - **Reorder Level**: Minimum stock before reorder (e.g., 10)
   - **Unit Price**: Price per unit (e.g., 599.99)
   - **Supplier ID**: ID of the supplier (must exist)

5. The system will validate and save the product

**Example Flow**:
```
Enter Product ID: 1001
Enter Product Name: Laptop Dell Inspiron 15
Enter Category: Electronics
Enter Description: 15.6 inch laptop, 8GB RAM, 256GB SSD
Enter Quantity in Stock: 50
Enter Reorder Level: 10
Enter Unit Price: 599.99
Enter Supplier ID: 1

[SUCCESS] Product added successfully!
```

### Task 2: Adding a Supplier

**Prerequisites**: Admin access

1. Login as admin
2. Select `2` (Supplier Management)
3. Select `1` (Add Supplier)
4. Enter supplier information:
   - **Supplier ID**: Unique integer (e.g., 1)
   - **Supplier Name**: Company name (e.g., "Tech Supplies Inc.")
   - **Contact Number**: Phone number (e.g., "+1-555-0123")
   - **Email**: Email address (e.g., "contact@techsupplies.com")
   - **Address**: Physical address (optional)

**Example Flow**:
```
Enter Supplier ID: 1
Enter Supplier Name: Tech Supplies Inc.
Enter Contact Number: +1-555-0123
Enter Email: contact@techsupplies.com
Enter Address: 123 Main St, City, State 12345

[SUCCESS] Supplier added successfully!
```

### Task 3: Stock In Operation

**Prerequisites**: Logged in (Admin or Staff)

1. Select `3` (Stock Operations) from main menu
2. Select `1` (Stock In)
3. Enter Product ID
4. Enter quantity to add
5. Enter optional notes
6. System updates stock and creates transaction record

**Example Flow**:
```
Enter Product ID: 1001
Enter quantity to add: 25
Enter notes (optional): Received new shipment from supplier

Stock updated successfully!
New quantity: 75
Press Enter to continue...
```

### Task 4: Stock Out Operation

**Prerequisites**: Logged in (Admin or Staff)

1. Select `3` (Stock Operations)
2. Select `2` (Stock Out)
3. Enter Product ID
4. Enter quantity to remove
5. System validates sufficient stock
6. If valid, stock is reduced and transaction is logged

**Example Flow**:
```
Enter Product ID: 1001
Enter quantity to remove: 5
Enter notes (optional): Sold to customer

Stock updated successfully!
New quantity: 70
Press Enter to continue...
```

**Note**: If you try to remove more than available stock, you'll get an error:
```
[ERROR] Insufficient stock. Available quantity is insufficient.
```

### Task 5: Viewing Low Stock Products

**Prerequisites**: Logged in

1. **For Admin**: Product Management → View Low Stock Products
2. **For Staff**: Staff Menu → View Low Stock Products

The system displays all products where `quantity_in_stock <= reorder_level`.

Products are marked with `*` in the table and show `[LOW STOCK]` indicator.

### Task 6: Generating Reports

**Prerequisites**: Admin access

1. Select `4` (Reports) from admin menu
2. Choose report type:
   - **Total Products Count**: Shows total number of products
   - **Total Stock Value**: Calculates sum of (quantity × price) for all products
   - **Top Products by Quantity**: Shows N products with highest stock
   - **Top Products by Value**: Shows N products with highest value
   - **Low Stock Products**: Lists all low stock items
   - **Transactions by Date Range**: Filter transactions by date

**Example - Total Stock Value**:
```
Total stock value: $125,450.75
```

**Example - Top Products by Quantity**:
```
Enter number of top products to show: 5
[Displays table with top 5 products by quantity]
```

**Example - Transactions by Date Range**:
```
Enter start date (YYYY-MM-DD): 2025-01-01
Enter end date (YYYY-MM-DD): 2025-01-31
[Displays all transactions in January 2025]
```

### Task 7: Backup Data

**Prerequisites**: Admin access

1. Select `5` (Backup & Restore) from admin menu
2. Select `1` (Backup Data)
3. System copies all data files to `backup/` directory

**Example**:
```
1. Backup Data
2. Restore Data
3. Back
Enter choice: 1

[SUCCESS] Data backed up successfully!
```

### Task 8: Restore Data

**Prerequisites**: Admin access

**Warning**: This will overwrite current data!

1. Select `5` (Backup & Restore)
2. Select `2` (Restore Data)
3. Confirm the warning message
4. System restores data from `backup/` directory

## Input Guidelines

### Valid Inputs

- **Integers**: Whole numbers (e.g., 100, 50, 0)
- **Decimals**: Numbers with decimal point (e.g., 99.99, 0.50)
- **Strings**: Text input (e.g., "Product Name", "Category")
- **Dates**: Format YYYY-MM-DD (e.g., 2025-01-15)

### Invalid Inputs

- Letters where numbers are expected
- Negative numbers for quantities (unless allowed)
- Empty strings for required fields
- Invalid date formats

### Error Messages

The system provides clear error messages:
- `[ERROR] Invalid product ID.` - Check your input format
- `[ERROR] Product ID already exists.` - Use a different ID
- `[ERROR] Insufficient stock.` - Check available quantity
- `[ERROR] Invalid username or password.` - Check credentials

## Troubleshooting

### Problem: "File not found" or "Cannot open file"

**Solution**: 
- Ensure `data/` directory exists
- Run `make install` to create directories
- Check file permissions

### Problem: "Invalid input" errors

**Solution**:
- Ensure you're entering the correct data type
- For numbers, don't include letters or special characters
- For dates, use YYYY-MM-DD format

### Problem: "Product ID already exists"

**Solution**:
- Use a different, unique product ID
- Or edit the existing product instead

### Problem: "Supplier ID does not exist"

**Solution**:
- First create the supplier with that ID
- Or use an existing supplier ID

### Problem: "Insufficient stock" during stock out

**Solution**:
- Check current stock level
- Reduce the quantity to remove
- Or perform stock in operation first

### Problem: Program crashes or exits unexpectedly

**Solution**:
- Check data file integrity
- Ensure all required directories exist
- Verify file permissions
- Check for corrupted data files

### Problem: Cannot login

**Solution**:
- Verify username and password (case-sensitive)
- Default credentials:
  - Admin: `admin` / `admin123`
  - Staff: `staff` / `staff123`
- Check `data/users.txt` file exists

### Problem: Data not saving

**Solution**:
- Check write permissions on `data/` directory
- Ensure sufficient disk space
- Verify file paths are correct

## Best Practices

1. **Regular Backups**: Use the backup feature regularly
2. **Unique IDs**: Always use unique product and supplier IDs
3. **Data Validation**: Double-check inputs before confirming
4. **Low Stock Monitoring**: Regularly check low stock reports
5. **Transaction Notes**: Add meaningful notes to transactions for audit trail
6. **Password Security**: Change default passwords immediately
7. **Data Integrity**: Don't manually edit data files

## Keyboard Shortcuts

- **Enter**: Confirm input or continue
- **Ctrl+C**: Exit program (may lose unsaved data - use Exit menu instead)

## Exiting the System

**Always use the Exit option from the menu!**

1. From main menu, select `2` (Exit)
2. Or from any submenu, navigate back to main menu, then logout, then exit
3. The system will save all data before exiting

**Warning**: Force-quitting (Ctrl+C) may result in data loss!

## Support

For additional help:
1. Review the design document (`docs/design_document.md`)
2. Check the project report (`docs/project_report.md`)
3. Review code comments in source files
4. Verify data file formats match expected structure

## Version Information

- **Version**: 1.0.0
- **Last Updated**: 2025
- **Compatibility**: Windows, Linux, macOS

---

**Note**: This manual covers the MVP version. Future versions may include additional features and capabilities.

