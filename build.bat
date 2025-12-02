@echo off
REM Script para compilar EditorDungeon con MSBuild

echo Buscando MSBuild...

REM Intentar encontrar MSBuild de Visual Studio 2022
set MSBUILD_PATH=""

REM Buscar en la ubicación estándar de VS 2022
if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" (
    set MSBUILD_PATH="C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"
)

if exist "C:\Program Files\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe" (
    set MSBUILD_PATH="C:\Program Files\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe"
)

if exist "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe" (
    set MSBUILD_PATH="C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe"
)

if %MSBUILD_PATH%=="" (
    echo ERROR: No se encontró MSBuild. Asegúrate de tener Visual Studio 2022 instalado.
    echo Necesitas instalar "Desarrollo para el escritorio con C++" y "Compatibilidad con C++/CLI"
    pause
    exit /b 1
)

echo MSBuild encontrado en: %MSBUILD_PATH%
echo.
echo Compilando proyecto...
echo.

REM Compilar el proyecto en modo Debug x64
%MSBUILD_PATH% EditorDungeon.vcxproj /p:Configuration=Debug /p:Platform=x64 /t:Rebuild

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ========================================
    echo Compilación exitosa!
    echo El ejecutable está en: x64\Debug\EditorDungeon.exe
    echo ========================================
) else (
    echo.
    echo ========================================
    echo ERROR: La compilación falló
    echo ========================================
)

pause
