// SPDX-License-Identifier: AGPL-3.0-or-later
// For a1 of -1 calls func_eu_001AB238 with the PAL string D_eu_0024E2D0; otherwise passes a1 split into its high part and its low byte to func_eu_001ADE38.
extern u8 D_eu_0024E2D0[];
void func_eu_001AB238(void* a0, u8* a1);
void func_eu_001ADE38(void* a0, s32 hi, u8 lo);
void func_eu_001ADDF8(void* a0, s32 a1)
{
    if (a1 != -1) {
        func_eu_001ADE38(a0, a1 >> 8, (u8)a1);
        return;
    }
    func_eu_001AB238(a0, D_eu_0024E2D0);
}
