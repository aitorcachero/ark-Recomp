# Terranigma SNES Recomp (Port Nativo para PC)

Port nativo para Windows 64-bit de la obra maestra de Super Nintendo **Terranigma** (versión oficial en castellano / ESP), desarrollado mediante técnicas de ingeniería inversa y recompilación estática sobre la base de [snesrecomp](https://github.com/RetroPortingToolKit/snesrecomp).

---

## 🌟 Características Principales

* **🖥️ Resolución Nativa 1080p y 4K UHD:** Nitidez absoluta para pantallas modernas sin filtros de reescalado borrosos.
* **📺 Modo 16:9 Pantalla Completa (Cero Pop-in):** Arquitectura de presentación que garantiza la precarga del 100% de los mapas, tiles y escenarios en memoria (estilo *Alundra Recompiled*), evitando que los bloques de textura aparezcan de golpe en los laterales.
* **🎨 Filtros y Anti-Aliasing de Última Generación:**
  * **HD-2D Remaster (activado por defecto):** Suavizado subpíxel de bordes, micro-contraste en contornos y expansión de la paleta original de 15 bits a color dinámico de 24 bits (estilo remakes modernos de Square Enix como *Live A Live* y *Octopath Traveler*).
  * **xBR-lv2 Anti-Aliasing:** Algoritmo avanzado de vectorización que redondea los dientes de sierra de los sprites y fondos sin difuminar la imagen.
  * **FXAA Retro:** Anti-aliasing rápido direccional para bordes suaves.
  * **Smooth Bicúbico:** Suavizado de texturas mediante curvas Catmull-Rom.
  * **CRT Soft y Warm Composite:** Simulación de líneas de escaneado y calidez de televisión clásica de tubo.
  * **Sharp HD:** Escalado píxel-perfect de máxima definición.
* **🎮 Compatibilidad Total con Mandos:** Detección automática plug & play de mandos de Xbox Series/One/360, PlayStation (DualShock 4 / DualSense), Nintendo Switch Pro y controladores genéricos SDL3.
* **⏪ Rebobinado en Tiempo Real y Guardado Rápido:** Vuelve atrás hasta 60 segundos con **F12** y utiliza 10 ranuras de guardado y carga rápida inmediatas (**F1** a **F10**).
* **🌍 Modo 7 Mejorado:** Renderizado en alta resolución y gran fluidez para el mapa del supramundo y el inframundo.
* **⚡ 60 FPS Sincronizados:** Fluidez de refresco sincronizada por haz de escaneo con audio de bajísima latencia vía WASAPI.

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

1. Coloca tu archivo `Terranigma (ESP).sfc` en la carpeta raíz del proyecto o junto al ejecutable.
2. Inicia el juego con el perfil que prefieras:
   * **`JUGAR.bat`** o **`LAUNCHER.bat`**: Menú gráfico de inicio (recomp-ui) para seleccionar y configurar mandos, resolución, aspecto de video, shaders y pulsar JUGAR.
   * **`JUGAR_16_9.bat`**: Abre la pantalla de configuración con perfil panorámico 16:9 y shader HD-2D preestablecido.
   * **`JUGAR_SIN_VENTANAS.vbs`**: Ejecución directa silenciosa sin consola de comandos CMD.
   * **`JUGAR_4_3.bat`**: Modo clásico original 4:3 pixel-perfect con barras laterales.
   * **`JUGAR_HACK_16_9.bat`**: Modo panorámico con campo de visión (FOV) extendido.

---

## 🛠️ Cómo Compilar desde el Código Fuente

### Requisitos
* Windows 10 u 11 (64 bits)
* Visual Studio 2022 (Community o Build Tools) con las herramientas de C/C++
* CMake 3.20 o superior
* Git

### Pasos de compilación

```cmd
git clone --recursive https://github.com/tu-usuario/Terranigma-Recomp.git
cd Terranigma-Recomp
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
* **F12:** Rebobinar partida
* **Shift + F1 a F10:** Guardado rápido (ranuras 1 a 10)
* **F1 a F10:** Carga rápida (ranuras 1 a 10)
* **Tab:** Acelerar / Turbo
* **P:** Pausa congelada
* **F:** Mostrar estadísticas de rendimiento y FPS

---

## 📜 Créditos

* Desarrollado con el framework de recompilación **snesrecomp** por RetroPortingToolKit.
* Juego original © 1995 Quintet / Enix.
