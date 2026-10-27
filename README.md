# Terranigma SNES Recomp (Native PC Port)

A native Windows 64-bit port of the legendary Action RPG **Terranigma** (Spanish release / PAL), reverse-engineered and recompiled using static recompilation on the [snesrecomp](https://github.com/RetroPortingToolKit/snesrecomp) framework.

---

## 🌟 Key Features

* **🖥️ 1080p / 4K Ultra HD Support:** Runs natively on modern PC displays with crystal-clear rendering and zero blur.
* **📺 16:9 Fullscreen (Zero Texture Pop-in):** Full-screen presentation utilizing authentic 2D streaming architecture so all background maps, tiles, and Mode 7 overworld environments load cleanly.
* **🎨 Modern Anti-Aliasing & Post-Processing Shaders:**
  * **HD-2D Remaster (Default):** Sub-pixel edge anti-aliasing, micro-contrast enhancement, and dynamic color vibrance expanding the SNES 15-bit color palette into modern 24-bit dynamic range.
  * **xBR-lv2 Anti-Aliasing:** Smart vector-like edge interpolation that eliminates pixel stair-stepping ("dientes de sierra") without blurring.
  * **FXAA Retro:** Fast Approximate Anti-Aliasing for smooth edge transitions.
  * **Smooth Bicubic:** Catmull-Rom texture smoothing.
  * **CRT Soft & Warm Composite:** Authentic scanline simulation and vintage TV warmth.
  * **Sharp HD:** Razor-sharp pixel-art scaling.
* **🎮 Full Controller & Gamepad Support:** Native plug-and-play support for Xbox, PlayStation (DualShock / DualSense), Switch Pro, and standard SDL3 controllers with configurable button mapping.
* **⏪ Real-time Rewind & Save States:** Rewind up to 60 seconds with **F12** / controller shortcuts, quick save (**Shift+F1..F10**) and quick load (**F1..F10**).
* **✨ Mode 7 Overworld Enhancements:** Smooth high-resolution rendering of the iconic spherical Underworld and Surface World maps.
* **⚡ 60 FPS Frame Pacing:** Beam-synchronized hardware frame delivery with low-latency audio via WASAPI.

---

## ⚖️ Legal Disclaimer

> **You must legally own a copy of the game.**  
> No copyrighted ROM files or copyrighted assets are included in this repository. The port verifies and loads your legally obtained copy of `Terranigma (ESP).sfc` at runtime.

### Required ROM Information

| Property | Value |
| :--- | :--- |
| **Title** | Terranigma |
| **Region** | Spain / ESP |
| **Filename** | `Terranigma (ESP).sfc` (or `.smc`) |
| **Internal Mapping** | HiROM |
| **CRC32** | `00e61534` |
| **SHA-256** | `7f731f4bb620e682132660da39641dda5762211dca4732f8192dd2411211b822` |

---

## 🚀 Quick Start (Running the Game)

1. Place your legally dumped ROM `Terranigma (ESP).sfc` into the project root or build folder.
2. Launch with your preferred display profile:
   * **`JUGAR_16_9.bat`**: Fullscreen 16:9, Zero Pop-in, Preloaded Textures & HD-2D Shader.
   * **`JUGAR_SIN_VENTANAS.vbs`**: Silent direct launch without CMD console window.
   * **`JUGAR_4_3.bat`**: Classic 4:3 Pixel-Perfect original aspect ratio.
   * **`JUGAR_HACK_16_9.bat`**: Extended field-of-view widescreen canvas.
   * **`LAUNCHER.bat`**: Graphical GUI launcher to customize resolution, keybinds, audio, and shaders.

---

## 🛠️ Building from Source

### Prerequisites
* Windows 10/11 64-bit
* Visual Studio 2022 (Community or BuildTools) with C/C++ desktop development workload
* CMake 3.20+
* Git

### Build Steps

```cmd
git clone --recursive https://github.com/your-username/Terranigma-Recomp.git
cd Terranigma-Recomp
COMPILAR.bat
```

Or manually with CMake:
```cmd
cmake -B build -S .
cmake --build build --config Release
```

---

## 🕹️ Controls & Hotkeys

### Default Keyboard Controls
| Action | Key |
| :--- | :--- |
| **Movement** | Arrow Keys (Up, Down, Left, Right) |
| **Attack / Confirm (B)** | Z |
| **Run / Jump / Cancel (A)** | X |
| **Box / Inventory (Y)** | A |
| **Block / Guard (X)** | S |
| **L / R** | C / V |
| **Start** | Return (Enter) |
| **Select** | Right Shift |

### Shortcuts
* **Alt + Enter:** Toggle Fullscreen
* **F12:** Rewind
* **Shift + F1..F10:** Quick Save slot 1..10
* **F1..F10:** Quick Load slot 1..10
* **Tab:** Fast-Forward / Turbo
* **P:** Pause
* **F:** Display Performance / FPS Overlay

---

## 📜 Credits & License

* Developed using the **snesrecomp** framework by RetroPortingToolKit.
* Original game © 1995 Quintet / Enix.
* Shaders provided under MIT / CC0-1.0 public domain.
