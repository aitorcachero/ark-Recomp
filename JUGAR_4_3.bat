@echo off
cd /d "%~dp0build\Release"
if not exist "TerranigmaSNESRecomp.exe" (
    echo No se encuentra TerranigmaSNESRecomp.exe. Ejecuta primero COMPILAR.bat.
    pause
    exit /b 1
)
copy /y config_4_3.ini config.ini >nul 2>&1
start "" "TerranigmaSNESRecomp.exe" --config config_4_3.ini --no-launcher
exit /b
