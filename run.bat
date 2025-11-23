@echo off
REM Run script for Inventory Management System

if not exist inventory.exe (
    echo Executable not found. Building first...
    call build.bat
    if %ERRORLEVEL% NEQ 0 (
        echo Build failed. Cannot run.
        pause
        exit /b 1
    )
)

echo.
echo Starting Inventory Management System...
echo.
inventory.exe

