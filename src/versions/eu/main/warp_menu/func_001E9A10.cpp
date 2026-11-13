// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the two gate fields of each global are at 0x560 and 0x56C (US 0x250, 0x25C).
struct Gate_1E9A10_eu { u8 pad0[0x560]; s32 f560; u8 pad1[8]; s32 f56C; };


s32 AreMenusClosed(void)
{
    if (g_screenFade.mode != 0) goto fail;
    if (((Gate_1E9A10_eu*)&g_pauseMenuElement)->f56C != 0) goto fail;
    if (((Gate_1E9A10_eu*)&g_pauseMenuElement)->f560 != 0) goto fail;
    if (((Gate_1E9A10_eu*)&g_mapScreenList)->f56C != 0) goto fail;
    if (((Gate_1E9A10_eu*)&g_mapScreenList)->f560 == 0) goto ok;
fail:
    return 0;
ok:
    return 1;
}
