// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's gate: true when nothing blocks the action (other field offsets than US).
struct Obj_eu_1E9970 {
    u8 pad[0x560];
    s32 f560;
    u8 pad2[0x08];
    s32 f56C;
    s32 f570;
};

s32 AreMenusAndFadeClear(void)
{
    if (g_screenFade.mode != 0) goto fail;
    if (IsPadSelectFlagHeld((World*)g_currentWorld) != 0) goto fail;
    if (((Obj_eu_1E9970*)&g_pauseMenuElement)->f56C != 0 && ((Obj_eu_1E9970*)&g_pauseMenuElement)->f570 != 0) goto fail;
    if (((Obj_eu_1E9970*)&g_mapScreenList)->f56C != 0) goto fail;
    if (((Obj_eu_1E9970*)&g_mapScreenList)->f560 != 0) goto fail;
    if (D_00270458 == 2) goto fail;
    if (D_00270458 == 1) goto fail;
    if (D_00270458 != 4) goto ok;
fail:
    return 0;
ok:
    return 1;
}
