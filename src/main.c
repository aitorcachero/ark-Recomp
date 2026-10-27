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

    /* Mode 5 and 6 are high-resolution screens (menus/dialogue/name-entry).
     * Mode 7 is the iconic Terranigma world map. */
    if (PPU_mode(g_ppu) == 5 || PPU_mode(g_ppu) == 6) {
        PpuSetExtraSideSpace(g_ppu, 0, 0, 0);
        return;
    }

    if (PPU_mode(g_ppu) == 7) {
        PpuSetExtraSpace(g_ppu, 64);
        return;
    }

    PpuSetExtraSpace(g_ppu, 64);
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
