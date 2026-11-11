@echo off
setlocal
cd /d "%~dp0"
if exist "build\Release\TerranigmaSNESRecomp.exe" (
    start "" "build\Release\TerranigmaSNESRecomp.exe" --launcher
) else if exist "TerranigmaSNESRecomp.exe" (
    start "" "TerranigmaSNESRecomp.exe" --launcher
) else (
    echo No se encontro TerranigmaSNESRecomp.exe. Ejecuta primero COMPILAR.bat.
    pause
)
exit /b 0
