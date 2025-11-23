@echo off
REM Build script for Inventory Management System on Windows

echo Building Inventory Management System...
echo.

REM Create obj directory if it doesn't exist
if not exist obj mkdir obj

REM Compile all source files
echo Compiling source files...
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
echo Linking...
gcc obj\utils.o obj\product.o obj\supplier.o obj\transaction.o obj\auth.o obj\storage.o obj\ui.o obj\report.o obj\main.o -o inventory.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful! Executable created: inventory.exe
    echo.
    echo To run the program, type: inventory.exe
    echo Or use: run.bat
) else (
    echo.
    echo Build failed! Please check for errors above.
)

