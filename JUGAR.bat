@echo off
cd /d "%~dp0build\Release"
if not exist "TerranigmaSNESRecomp.exe" (
    echo No se encuentra TerranigmaSNESRecomp.exe. Ejecuta primero COMPILAR.bat.
    pause
    exit /b 1
)
start "" "TerranigmaSNESRecomp.exe" --launcher
exit /b
