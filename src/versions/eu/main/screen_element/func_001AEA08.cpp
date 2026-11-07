// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the same pick as US's, reading the table's byte unsigned.
Letter_1AEA08 GetCyclingGlyph(void)
{
    s32 scaled = (s32)(g_elapsedTime * 5.0f);
    u32 divisor = GetStringLength((const char*)D_002744B0.p);
    return ((u8*)D_002744B0.p)[(u32)scaled % divisor];
}
