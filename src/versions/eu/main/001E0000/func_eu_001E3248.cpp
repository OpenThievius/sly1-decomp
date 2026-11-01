// SPDX-License-Identifier: AGPL-3.0-or-later
// Upper-cases a zero-terminated string in place, for the characters the table flags with bit 2.
extern u8 D_eu_0024FB49[];

void func_eu_001E3248(u8* s)
{
    u8* p = s;
    while (*p != 0) {
        u8 c = *p;
        s32 v = c - 0x20;
        if ((D_eu_0024FB49[c] & 2) == 0) {
            v = c;
        }
        *p = v;
        p++;
    }
}
