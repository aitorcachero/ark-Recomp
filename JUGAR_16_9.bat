@echo off
cd /d "%~dp0build\Release"
if not exist "TerranigmaSNESRecomp.exe" (
    echo No se encuentra TerranigmaSNESRecomp.exe. Ejecuta primero COMPILAR.bat.
    pause
    exit /b 1
)
copy /y config_16_9.ini config.ini >nul 2>&1
start "" "TerranigmaSNESRecomp.exe" --config config_16_9.ini --launcher
exit /b
