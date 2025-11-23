# How to Run the Inventory Management System

## Quick Start (Windows)

### Option 1: Using Build Script (Easiest)

1. **Open Command Prompt or PowerShell** in the project directory

2. **Build the project**:
   ```batch
   build.bat
   ```

3. **Run the application**:
   ```batch
   run.bat
   ```
   Or simply:
   ```batch
   inventory.exe
   ```

### Option 2: Manual Compilation

If you prefer to compile manually, use these commands:

```batch
REM Create object directory
mkdir obj

REM Compile all source files
gcc -Wall -Wextra -Wpedantic -std=c11 -g -c src\utils.c -o obj\utils.o
gcc -Wall -Wextra -Wpedantic -std=c11 -g -c src\product.c -o obj\product.o
gcc -Wall -Wextra -Wpedantic -std=c11 -g -c src\supplier.c -o obj\supplier.o
gcc -Wall -Wextra -Wpedantic -std=c11 -g -c src\transaction.c -o obj\transaction.o
gcc -Wall -Wextra -Wpedantic -std=c11 -g -c src\auth.c -o obj\auth.o
gcc -Wall -Wextra -Wpedantic -std=c11 -g -c src\storage.c -o obj\storage.o
gcc -Wall -Wextra -Wpedantic -std=c11 -g -c src\ui.c -o obj\ui.o
gcc -Wall -Wextra -Wpedantic -std=c11 -g -c src\report.c -o obj\report.o
gcc -Wall -Wextra -Wpedantic -std=c11 -g -c src\main.c -o obj\main.o

REM Link all object files
gcc obj\utils.o obj\product.o obj\supplier.o obj\transaction.o obj\auth.o obj\storage.o obj\ui.o obj\report.o obj\main.o -o inventory.exe
```

### Option 3: Using Make (If Available)

If you have `make` installed (via MinGW or MSYS2):

```batch
make
make run
```

## Prerequisites

- **GCC Compiler**: You need GCC installed (MinGW on Windows)
  - Check if installed: `gcc --version`
  - If not installed, download from: https://www.mingw-w64.org/

## First Run

When you run the application for the first time:

1. The system will automatically create `data/` and `backup/` directories
2. Default user accounts will be created:
   - **Admin**: username `admin`, password `admin123`
   - **Staff**: username `staff`, password `staff123`

## Running the Application

1. **Start the program**: Run `inventory.exe` or `run.bat`

2. **Login Screen**: 
   - Select option `1` to login
   - Enter username and password
   - Press Enter

3. **Main Menu**: After login, you'll see a menu based on your role:
   - **Admin**: Full access to all features
   - **Staff**: Limited access (view products, stock operations)

## Troubleshooting

### Error: "gcc is not recognized"

**Solution**: GCC is not in your PATH. 
- Install MinGW-w64
- Add MinGW bin directory to your system PATH
- Or use the full path to gcc.exe

### Error: "Cannot open file" or "File not found"

**Solution**: 
- Ensure you're running from the project root directory
- The program will create `data/` and `backup/` directories automatically
- Check file permissions

### Error: Compilation errors

**Solution**:
- Ensure all source files are in the `src/` directory
- Check that GCC version supports C11 standard
- Review error messages for specific issues

### Program crashes on startup

**Solution**:
- Check that all source files are present
- Verify GCC compilation completed successfully
- Try cleaning and rebuilding: delete `obj/` folder and `inventory.exe`, then rebuild

## Clean Build

To clean and rebuild:

```batch
REM Delete object files and executable
rmdir /s /q obj
del inventory.exe

REM Rebuild
build.bat
```

## Project Structure

```
C_INVENTORY_MANAGEMENT/
├── src/              # Source code files
├── data/             # Data files (created at runtime)
├── backup/           # Backup files (created at runtime)
├── obj/              # Object files (created during build)
├── build.bat         # Windows build script
├── run.bat           # Windows run script
├── Makefile          # Makefile (if make is available)
└── inventory.exe     # Executable (created after build)
```

## Example Session

```
D:\C_INVENTORY_MANAGEMENT> build.bat
Building Inventory Management System...
Compiling source files...
Linking...
Build successful! Executable created: inventory.exe

D:\C_INVENTORY_MANAGEMENT> inventory.exe

==========================================
     INVENTORY MANAGEMENT SYSTEM
==========================================

1. Login
2. Exit

Enter your choice: 1

Username: admin
Password: admin123

[SUCCESS] Login successful!

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

## Need Help?

- Check `README.md` for project overview
- Check `docs/user_manual.md` for detailed usage instructions
- Check `docs/design_document.md` for technical details

