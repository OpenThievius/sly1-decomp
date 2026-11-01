// SPDX-License-Identifier: AGPL-3.0-or-later
// For a code below 0x80 returns bit 2 of a byte of D_eu_0024FB49; for the others returns 1 when the code plus 0xF0 is below 10.
extern u8 D_eu_0024FB49[];
u32 func_eu_001E3210(s32 a0)
{
    u16 c = (u16)a0;
    if (c < 0x80) {
        return D_eu_0024FB49[c] & 4;
    }
    u16 d = (u16)(c + 0xF0);
    return d < 0xA;
}
