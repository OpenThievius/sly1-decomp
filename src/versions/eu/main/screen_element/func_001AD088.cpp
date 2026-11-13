// SPDX-License-Identifier: AGPL-3.0-or-later
// For a1 of -1 calls func_eu_001AB238 with the PAL string D_eu_0024E2D0; otherwise passes a1 split into its high part and its low byte to func_eu_001ADE38.
extern u8 D_eu_0024E2D0[];
void SetScreenElementByteText(void* a0, u8* a1);
void SetElementWideTextFromEntry(void* a0, s32 hi, u8 lo);
void SetElementTextFromPackedEntry(void* a0, s32 a1)
{
    if (a1 != -1) {
        SetElementWideTextFromEntry(a0, a1 >> 8, (u8)a1);
        return;
    }
    SetScreenElementByteText(a0, D_eu_0024E2D0);
}
