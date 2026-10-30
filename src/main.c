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

static void TerranigmaPrepareFrame(int dw, int dh, int *w, int *h)
{
    (void)dw; (void)dh;
    if (g_config.widescreen) {
        *w = 384; /* 16:9 widescreen canvas: 256 + 2 * 64 */
    } else {
        *w = 256;
    }
    *h = 224;
}

static void TerranigmaBeginFrame(unsigned number)
{
    (void)number;
    if (!g_ppu) return;
    PpuSetPal(g_ppu, true);

    if (!g_config.widescreen) {
        PpuSetExtraSpace(g_ppu, 0);
        return;
    }

    /* Start each widescreen frame with a clean 64px centering budget.
     * Screens with no wide background (menus, static rooms, dialogue)
     * remain at extraLeftCur=0, extraRightCur=0 -> pure black pillarboxes. */
    PpuSetExtraSpaceCentered(g_ppu, 64);

    uint16_t map_id = (uint16_t)(g_ram[0x047E] | (g_ram[0x047F] << 8));
    uint16_t camX   = (uint16_t)(g_ram[0x081E] | (g_ram[0x081F] << 8));
    uint16_t camY   = (uint16_t)(g_ram[0x0820] | (g_ram[0x0821] << 8));
    uint16_t mapW   = (uint16_t)(g_ram[0x0826] | (g_ram[0x0827] << 8));
    uint16_t mapH   = (uint16_t)(g_ram[0x0828] | (g_ram[0x0829] << 8));

    /* Static menus, logo screens, and non-exploration screens:
     * - map 0x0001: Enix & Quintet logos
     * - map 0x0004: File select, Save/Load, Options, Name entry screens
     * - map 0x0022: Intro spinning Mode 7 globe
     * - Mode 5 and 6: High-resolution screens (dialogue/text/menus) */
    if (map_id == 0x0001 || map_id == 0x0004 || map_id == 0x0022 ||
        PPU_mode(g_ppu) == 5 || PPU_mode(g_ppu) == 6) {
        return; /* Already cleanly centered with black pillarboxes */
    }

    /* Mode 7 world map (Overworld 0x0002, Underworld 0x0003) */
    if (PPU_mode(g_ppu) == 7) {
        PpuSetExtraSpace(g_ppu, 64);
        return;
    }

    /* If map width is 256 or less, or map height is 0 (static rooms like Ark's bedroom, elder's house),
     * pillarbox cleanly with pure black sidebars */
    if (mapW <= 256 || mapH == 0) {
        return;
    }

    /* Mode 1 exploration in large towns and dungeons:
     * Clamp camera margins to prevent rendering beyond map boundaries */
    int budget = 64;
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

    PpuSetExtraSideSpace(g_ppu, extraLeft, extraRight, 0);

    static uint16_t s_prev_map_id = 0;
    if (map_id != s_prev_map_id) {
        WsShadowReset();
        s_prev_map_id = map_id;
    }

    for (int l = 0; l < 2; l++) {
        WsShadowSetWorld(l, camX, camY);
        WsShadowSetScroll(l, g_ppu->hScroll[l], g_ppu->vScroll[l]);
    }
    WsShadowFrame(g_ppu);
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
    .prepare_frame       = TerranigmaPrepareFrame,
    .begin_sim_frame     = TerranigmaBeginFrame,
};

#ifndef __ANDROID__
#undef main   /* desktop: keep plain main() even if SDL_main.h remapped it */
#endif
int main(int argc, char **argv)
{
    return snesrecomp_desktop_main(&kGameHost, argc, argv);
}
