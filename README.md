# Inventory Management System

A production-quality command-line Inventory Management System implemented in C, designed as an MVP (Minimum Viable Product) for real-world inventory management.

## Overview

This system provides comprehensive inventory management capabilities including product management, supplier tracking, stock operations, transaction logging, reporting, and user authentication with role-based access control.

## Features

### Core Functionality

- **Product Management**
  - Add, view, edit, and delete products
  - Search products by ID, name, or category
  - Track quantity, reorder levels, and pricing
  - Low stock alerts

- **Supplier Management**
  - Complete supplier CRUD operations
  - Contact information management
  - Supplier-product relationships

- **Stock Operations**
  - Stock In: Add inventory with transaction logging
  - Stock Out: Remove inventory (prevents negative stock)
  - Transaction history tracking

- **User Authentication**
  - Role-based access control (Admin/Staff)
  - Secure password hashing
  - Session management

- **Reporting & Analytics**
  - Total products count
  - Total stock value calculation
  - Top products by quantity or value
  - Low stock product reports
  - Transaction reports by date range

- **Data Management**
  - Automatic data persistence to disk
  - Backup and restore functionality
  - Data integrity validation

## Technology Stack

- **Language**: C (C11 standard)
- **Compiler**: GCC/Clang compatible
- **Build System**: Make
- **Data Storage**: Structured text files (CSV-like format)
- **Platform**: Cross-platform (Windows, Linux, macOS)

## Project Structure

```
C_INVENTORY_MANAGEMENT/
├── src/                    # Source code files
│   ├── main.c              # Application entry point
│   ├── product.c/h         # Product management
│   ├── supplier.c/h        # Supplier management
│   ├── transaction.c/h     # Transaction handling
│   ├── auth.c/h            # Authentication
│   ├── storage.c/h          # File I/O operations
│   ├── ui.c/h               # User interface
│   ├── report.c/h           # Reporting functions
│   └── utils.c/h            # Utility functions
├── data/                    # Data files (created at runtime)
│   ├── products.txt
│   ├── suppliers.txt
│   ├── transactions.txt
│   └── users.txt
├── backup/                  # Backup files (created at runtime)
├── docs/                    # Documentation
│   ├── project_report.md
│   ├── design_document.md
│   └── user_manual.md
├── Makefile                 # Build configuration
└── README.md               # This file
```

## Building the Project

### Prerequisites

- GCC compiler (MinGW on Windows, gcc on Linux/macOS)
- Make utility
- A terminal/command prompt

### Build Commands

```bash
# Build the project
make

# Build and run
make run

# Clean build artifacts
make clean

# Create data directories
make install

# Show help
make help
```

### Compilation Flags

The project uses strict compilation flags:
- `-Wall -Wextra -Wpedantic`: Enable all warnings
- `-std=c11`: Use C11 standard
- `-g`: Include debugging symbols

## Running the Application

1. Build the project: `make`
2. Run the executable: `make run` or `./inventory` (Linux/macOS) or `inventory.exe` (Windows)

### Default Credentials

The system creates default users on first run:

- **Admin User**
  - Username: `admin`
  - Password: `admin123`
  - Access: Full system access

- **Staff User**
  - Username: `staff`
  - Password: `staff123`
  - Access: Limited access (view products, stock operations)

**Important**: Change default passwords in a production environment!

## Usage

### Main Menu

1. **Login**: Enter username and password
2. **Exit**: Save all data and exit

### Admin Menu

1. **Product Management**: Full CRUD operations for products
2. **Supplier Management**: Full CRUD operations for suppliers
3. **Stock Operations**: Stock in/out operations
4. **Reports**: View various analytics and reports
5. **Backup & Restore**: Backup or restore data files
6. **Logout**: Return to main menu

### Staff Menu

1. **View Products**: Browse all products
2. **Search Products**: Search by name
3. **Stock Operations**: Perform stock in/out
4. **View Low Stock Products**: See items needing reorder
5. **Logout**: Return to main menu

## Data Format

Data is stored in structured text files using pipe (`|`) as delimiter:

- **Products**: `id|name|category|description|quantity|reorder_level|price|supplier_id`
- **Suppliers**: `supplier_id|name|contact_number|email|address`
- **Transactions**: `transaction_id|product_id|type|quantity|date_time|notes`
- **Users**: `username|password_hash|role`

## File Locations

- **Data Files**: `data/` directory
- **Backup Files**: `backup/` directory
- **Source Code**: `src/` directory
- **Documentation**: `docs/` directory

## Error Handling

The system includes comprehensive error handling:
- Input validation for all user inputs
- File operation error checking
- Data integrity validation
- Graceful error messages with recovery options

## Security Features

- Password hashing (simple hash function for educational purposes)
- Role-based access control
- Input validation to prevent buffer overflows
- Data validation before storage

## Limitations

- Password hashing is basic (not cryptographically secure for production)
- Single-user access (no concurrent user support)
- No network capabilities
- Text-based UI only
- Limited to in-memory data structures (MAX_PRODUCTS, MAX_SUPPLIERS, etc.)

## Future Enhancements

- GUI version using GTK or Qt
- Networked multi-user system
- SQLite database backend
- Barcode/QR code scanner integration
- Advanced analytics and forecasting
- Email notifications for low stock
- Export to Excel/PDF
- Web-based interface

## Documentation

Comprehensive documentation is available in the `docs/` directory:

- **project_report.md**: Complete 20+ page academic project report
- **design_document.md**: Technical design and architecture
- **user_manual.md**: User guide with examples

## Contributing

This is a student project. For educational purposes, feel free to:
- Study the code structure
- Extend functionality
- Improve documentation
- Report issues

## License

This project is created for educational purposes.

## Author

Student Project - Inventory Management System

## Acknowledgments

- C Standard Library
- Educational resources on software engineering
- System design principles

## Support

For issues or questions:
1. Check the documentation in `docs/`
2. Review the code comments
3. Verify data file formats

## Version

Version 1.0.0 - MVP Release

---

**Note**: This is an educational project. For production use, additional security measures, database backend, and comprehensive testing would be required.

