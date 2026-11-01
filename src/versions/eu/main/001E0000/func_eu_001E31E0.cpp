// SPDX-License-Identifier: AGPL-3.0-or-later
// For a 16-bit code below 0x80, returns the bit 8 of its PAL table D_eu_0024FB49 entry; otherwise returns 1 only for 0x3000.
extern u8 D_eu_0024FB49[];

s32 func_eu_001E31E0(u16 c)
{
    if (c < 0x80) {
        return D_eu_0024FB49[c] & 8;
    }
    return c == 0x3000;
}
