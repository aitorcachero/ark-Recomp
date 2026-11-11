/*
 * Terranigma — desktop host shim.
 *
 * Identity and hooks, nothing else. The host itself is the framework's
 * (snesrecomp/runner/src/desktop/host_main.h).
 */

#include "host_main.h"
#include "game_rtl.h"
#include "snesrecomp_rom_identity.h"  /* generated from rom_identity.txt */
#include "desktop/config.h"
#include "snes/ppu.h"
#include "snes/ws_shadow.h"
#include "widescreen.h"

#ifndef __ANDROID__
#define SDL_MAIN_HANDLED 1
#endif
#include "desktop/sdl_compat.h"
#ifdef __ANDROID__
/* SDLActivity loads libmain.so and dlsyms its SDL_main. */
#define main SDL_main
#endif

#ifndef SNES_GAME_VERSION
#define SNES_GAME_VERSION "dev"
#endif

extern Ppu *g_ppu;
extern uint8 g_ram[0x20000];

static const char *const kTerranigmaAspectLabels[] = {
    "4:3 (Original Cl\xc3\xa1sico)",
    "16:9 Panor\xc3\xa1mico (Hack FOV)",
    "16:10 Panor\xc3\xa1mico (Steam Deck)",
    "Pantalla Completa (Estirado)",
};

static void TerranigmaPrepareFrame(int dw, int dh, int *w, int *h)
{
    (void)dw; (void)dh;
    if (g_config.display_aspect == 1) {
        *w = 384; /* 16:9 widescreen canvas: 256 + 2 * 64 */
    } else if (g_config.display_aspect == 2) {
        *w = 352; /* 16:10 widescreen canvas: 256 + 2 * 48 (Steam Deck 1280x800) */
    } else {
        *w = 256;
    }
    *h = 224;
}

static void TerranigmaComputeViewport(int frame_w, int frame_h, int drawable_w, int drawable_h,
                                     SnesDisplayViewport *viewport)
{
    (void)frame_w; (void)frame_h;
    if (!viewport) return;
    if (g_config.display_aspect == 0) {
        /* 4:3 Original Clásico con barras laterales en pantallas panorámicas */
        *viewport = SnesDisplayAspect_FitViewport(4.0 / 3.0, drawable_w, drawable_h);
    } else if (g_config.display_aspect == 1) {
        /* 16:9 Panorámico con lienzo extendido a resolución nativa */
        *viewport = SnesDisplayAspect_FitViewport(16.0 / 9.0, drawable_w, drawable_h);
    } else if (g_config.display_aspect == 2) {
        /* 16:10 Panorámico nativo para Steam Deck (1280x800) y pantallas 16:10 */
        *viewport = SnesDisplayAspect_FitViewport(16.0 / 10.0, drawable_w, drawable_h);
    } else {
        /* Pantalla Completa estirada sin franjas */
        viewport->x = 0;
        viewport->y = 0;
        viewport->width = drawable_w > 0 ? drawable_w : 1;
        viewport->height = drawable_h > 0 ? drawable_h : 1;
    }
}

static void TerranigmaBeginFrame(unsigned number)
{
    (void)number;
    if (!g_ppu) return;
    PpuSetPal(g_ppu, true);

    /* If mode is 4:3 or Stretched, disable extra wide PPU rasterization */
    if (g_config.ignore_aspect_ratio || (g_config.display_aspect != 1 && g_config.display_aspect != 2)) {
        PpuSetExtraSpace(g_ppu, 0);
        return;
    }

    int budget = (g_config.display_aspect == 2) ? 48 : 64;
    PpuSetExtraSpaceCentered(g_ppu, budget);

    uint16_t map_id = (uint16_t)(g_ram[0x047E] | (g_ram[0x047F] << 8));
    uint16_t camX   = (uint16_t)(g_ram[0x081E] | (g_ram[0x081F] << 8));
    uint16_t camY   = (uint16_t)(g_ram[0x0820] | (g_ram[0x0821] << 8));
    uint16_t mapW   = (uint16_t)(g_ram[0x0826] | (g_ram[0x0827] << 8));
    uint16_t mapH   = (uint16_t)(g_ram[0x0828] | (g_ram[0x0829] << 8));

    /* Static menus, logo screens, and high-res dialogue/menus:
     * - map 0x0001: Enix & Quintet logos
     * - map 0x0004: File select, Save/Load, Options, Name entry screens
     * - map 0x0022: Intro spinning Mode 7 globe
     * - Mode 5 and 6: High-resolution screens (dialogue/text/menus) */
    if (map_id == 0x0001 || map_id == 0x0004 || map_id == 0x0022 ||
        PPU_mode(g_ppu) == 5 || PPU_mode(g_ppu) == 6) {
        PpuSetExtraSideSpace(g_ppu, 0, 0, 0);
        WsShadowReset();
        return;
    }

    /* Mode 7 world map (Overworld 0x0002, Underworld 0x0003) */
    if (PPU_mode(g_ppu) == 7) {
        PpuSetExtraSpace(g_ppu, budget);
        return;
    }

    /* If map width is 256 or less, or map height is 0 (static scenes),
     * pillarbox cleanly with pure black sidebars to prevent horizontal wrapping. */
    if (mapW <= 256 || mapH == 0) {
        PpuSetExtraSideSpace(g_ppu, 0, 0, 0);
        WsShadowReset();
        return;
    }

    /* Mode 1 exploration in large towns, rooms and dungeons:
     * Clamp camera margins to prevent rendering beyond map boundaries */
    /* budget already defined */
    int extraLeft = budget;
    int extraRight = budget;

    int maxCamX = (mapW > 256) ? (mapW - 256) : 0;
    extraLeft = (int)camX;
    if (extraLeft > budget) extraLeft = budget;
    if (extraLeft < 0) extraLeft = 0;

    int rightSpace = maxCamX - (int)camX;
    extraRight = rightSpace;
    if (extraRight > budget) extraRight = budget;
    if (extraRight < 0) extraRight = 0;

    if (extraLeft == 0 && extraRight == 0) {
        PpuSetExtraSideSpace(g_ppu, 0, 0, 0);
        WsShadowReset();
        return;
    }

    PpuSetExtraSideSpace(g_ppu, extraLeft, extraRight, 0);

    static uint16_t s_prev_map_id = 0;
    if (map_id != s_prev_map_id) {
        WsShadowReset();
        s_prev_map_id = map_id;
    }

    for (int l = 0; l < 2; l++) {
        WsShadowSetWorld(l, camX, camY);
        WsShadowSetScroll(l, g_ppu->hScroll[l], g_ppu->vScroll[l]);
        WsShadowSetRejectEastEcho(l, true);
    }
    WsShadowFrame(g_ppu);
    WsShadowExtendEdges(0, budget);
    WsShadowExtendEdges(1, budget);
}

static const SnesDesktopHostGame kGameHost = {
    .display_name        = "Terranigma",
    .window_title        = "Terranigma",
    .region              = SNESRECOMP_ROM_REGION,
    .rom_file            = SNESRECOMP_ROM_FILE,
    .expected_sha256_hex = SNESRECOMP_ROM_EXPECTED_SHA256,
    .expected_crc32_hex  = SNESRECOMP_ROM_EXPECTED_CRC32,
    .game_id             = SNESRECOMP_ROM_GAME_ID,
    .build_version       = SNES_GAME_VERSION,
    .game_info           = &kGameInfo,
    .num_players         = 2,
    /* Battery-backed SRAM shows the launcher's SAVES panel. Leave NULL for a
     * title without one. The path is exe-relative. */
    .sram_path           = "saves/save.srm",
    .widescreen_supported = 1,
    .native_widescreen   = 1,
    .display_aspect_supported = 1,
    .shader_supported    = 1,
    .aspect_labels       = kTerranigmaAspectLabels,
    .num_aspect_labels   = 4,
    .aspect_setting_label = "Modo de Pantalla",
    .aspect_setting_help  = "4:3 clasico original, 16:9 Panoramico, 16:10 Steam Deck o Pantalla Completa estirada.",
    .prepare_frame       = TerranigmaPrepareFrame,
    .begin_sim_frame     = TerranigmaBeginFrame,
    .compute_viewport    = TerranigmaComputeViewport,
};

#ifndef __ANDROID__
#undef main   /* desktop: keep plain main() even if SDL_main.h remapped it */
#endif
int main(int argc, char **argv)
{
    return snesrecomp_desktop_main(&kGameHost, argc, argv);
}
