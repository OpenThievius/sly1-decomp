// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the unaligned word is at 0x590 (US 0x280).
void func_001DDB20(void* unused, s32 a1, s32 a2)
{
    s32 saved = a1;
    u8* p = (u8*)&g_pauseMenuElement;
    ((Unaligned_1DDB20*)(p + 0x590))->v = a2;
    SetPauseMenuLayerPage(&g_pauseMenuElement, 0, saved);
}
