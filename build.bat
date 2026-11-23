@echo off
echo ====================================================
echo  Building CS212 Streetlight Repair Desk...
echo ====================================================
cd Source_Code
g++ -std=c++11 -Wall -Wextra main.cpp -o streetlight_app.exe
if %ERRORLEVEL% EQU 0 (
    echo.
    echo [Build Successful!] Launching Application...
    echo.
    streetlight_app.exe
) else (
    echo.
    echo [Build Failed!] Please verify your g++ MinGW installation.
    pause
)
cd ..
