@echo off
setlocal

if "%~1"=="" (
    echo ERROR: HEX filename was not specified
    exit /b 1
)

set "HEX=%~1"

rem Always work in project's Debug directory
cd /d "%~dp0Debug"

if not exist "%HEX%" (
    echo ERROR: HEX file not found: "%HEX%"
    echo Current directory: %CD%
    exit /b 1
)

echo Keeping: %HEX%
echo.

rem Delete all other HEX files
for %%F in (*.hex) do (
    if /I not "%%~nxF"=="%HEX%" (
        echo Deleting: %%~nxF
        del /q "%%F"
    )
)

rem Get Git hash
cd /d "%~dp0"

git rev-parse --short=7 HEAD > "%TEMP%\stm32_git_hash.txt"

if errorlevel 1 (
    echo ERROR: Cannot get Git commit hash
    exit /b 1
)

set /p HASH=<"%TEMP%\stm32_git_hash.txt"
del "%TEMP%\stm32_git_hash.txt" >nul 2>&1

if not defined HASH (
    echo ERROR: Git hash is empty
    exit /b 1
)

rem Return to Debug
cd /d "%~dp0Debug"

for %%F in ("%HEX%") do (
    ren "%%F" "%%~nF_%HASH%.hex"
    echo.
    echo Result: %%~nF_%HASH%.hex
)

exit /b 0