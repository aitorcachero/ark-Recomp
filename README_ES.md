# Terranigma SNES Recomp (Port Nativo para PC)

Port nativo para Windows 64-bit de la obra maestra de Super Nintendo **Terranigma** (versión oficial en castellano / ESP), desarrollado mediante técnicas de ingeniería inversa y recompilación estática sobre la base de [snesrecomp](https://github.com/RetroPortingToolKit/snesrecomp).

---

## 🌟 Características Principales

* **🖥️ Resolución Nativa 1080p y 4K UHD:** Nitidez absoluta para pantallas modernas sin filtros de reescalado borrosos.
* **📺 Selector de Modos de Pantalla Integrado en el Launcher:**
  * **4:3 (Original Clásico):** Proporciones originales idénticas a la consola con bandas laterales limpias en monitores panorámicos.
  * **16:9 Panorámico (Hack FOV):** Campo de visión ampliado nativo (384x224) con gestión dinámica de bordes para evitar la repetición de tiles en habitaciones y menús.
  * **16:9 Pantalla Completa (Estirado):** Adaptación completa al ancho de la pantalla sin franjas negras.
* **🎨 Colores Vivos y Shaders Auténticos:**
  * **Sharp HD (por defecto):** Máxima fidelidad cromática, píxeles nítidos y colores 100% auténticos de la paleta original de Super Nintendo (sin tonos descoloridos ni apagados).
  * **Shaders opcionales:** CRT Soft, Warm Composite, xBR-lv2 Anti-Aliasing, FXAA, Bicúbico y HD-2D seleccionables con un clic.
* **🔊 Audio Quintet Perfeccionado:** Sincronismo exacto con el chip S-DSP y buffer de 2048 muestras a 48000 Hz, garantizando música y efectos cristalinos sin cortes ni petardeo.
* **🎮 Compatibilidad Total con Mandos:** Detección automática plug & play de mandos de Xbox Series/One/360, PlayStation (DualShock 4 / DualSense), Nintendo Switch Pro y controladores genéricos SDL3, con asignación y calibración visual.
* **⏪ Rebobinado en Tiempo Real y Guardado Rápido:** Vuelve atrás hasta 60 segundos con **F12** y utiliza 10 ranuras de guardado y carga rápida inmediatas (**F1** a **F10**).
* **🌍 Modo 7 Panorámico:** Renderizado fluido y en alta resolución para el mapamundi del supramundo y el inframundo.

---

## ⚖️ Aviso Legal

> **Es imprescindible poseer una copia legal original del juego.**  
> Este repositorio no contiene ROMs, código binario con copyright ni recursos protegidos de Nintendo o Enix/Quintet. El ejecutable comprueba y carga tu propio volcado legal de `Terranigma (ESP).sfc`.

### Datos de la ROM compatible

| Campo | Valor |
| :--- | :--- |
| **Juego** | Terranigma |
| **Región** | España / Castellano (ESP) |
| **Archivo** | `Terranigma (ESP).sfc` (o `.smc`) |
| **Mapeado** | HiROM |
| **CRC32** | `00e61534` |
| **SHA-256** | `7f731f4bb620e682132660da39641dda5762211dca4732f8192dd2411211b822` |

---

## 🚀 Cómo Jugar

1. Coloca tu archivo `Terranigma (ESP).sfc` en la misma carpeta del ejecutable.
2. Ejecuta directamente **`TerranigmaSNESRecomp.exe`** (o **`JUGAR_TERRANIGMA.bat`**):
   * Se abrirá automáticamente la pantalla de bienvenida y configuración (**Launcher GUI**).
   * En la sección **DISPLAY**, pulsa en **Modo de Pantalla** para alternar entre:
     - `4:3 (Original Clásico)`
     - `16:9 Panorámico (Hack FOV)`
     - `16:9 Pantalla Completa (Estirado)`
   * Configura tus mandos o teclado, activa o cambia shaders a tu gusto y pulsa **JUGAR**.
   * El ejecutable guardará tus preferencias para las siguientes sesiones.

---

## 🛠️ Cómo Compilar desde el Código Fuente

### Requisitos
* Windows 10 u 11 (64 bits)
* Visual Studio 2022 (Community o Build Tools) con las herramientas de C/C++
* CMake 3.20 o superior
* Git

### Pasos de compilación

```cmd
git clone --recursive https://github.com/aitorcachero/ark-Recomp.git
cd ark-Recomp
COMPILAR.bat
```

O directamente mediante CMake en consola:
```cmd
cmake -B build -S .
cmake --build build --config Release
```

---

## 🕹️ Controles por Defecto

### Teclado
| Acción | Tecla |
| :--- | :--- |
| **Movimiento** | Flechas de dirección |
| **Atacar / Aceptar (B)** | Z |
| **Correr / Saltar / Cancelar (A)** | X |
| **Caja de Inventario (Y)** | A |
| **Bloquear / Defensa (X)** | S |
| **Giro / Menú L y R** | C / V |
| **Pausa / Start** | Enter / Return |
| **Select** | Shift Derecho |

### Atajos de Teclado
* **Alt + Enter:** Pantalla completa / Modo ventana
* **F12:** Rebobinar partida en tiempo real
* **Shift + F1 a F10:** Guardado rápido (ranuras 1 a 10)
* **F1 a F10:** Carga rápida (ranuras 1 a 10)
* **Tab:** Acelerar / Modo Turbo
* **P:** Pausa congelada
* **F:** Mostrar estadísticas de rendimiento y FPS

---

## 📜 Créditos

* Desarrollado con el framework de recompilación **snesrecomp** por RetroPortingToolKit.
* Juego original © 1995 Quintet / Enix.
