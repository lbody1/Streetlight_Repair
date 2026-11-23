@echo off
cd Source_Code
g++ -std=c++11 main.cpp -o app.exe
if %ERRORLEVEL% EQU 0 (
    app.exe
) else (
    echo Compilation failed.
    pause
)
cd ..
