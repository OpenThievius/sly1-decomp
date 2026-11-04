// SPDX-License-Identifier: AGPL-3.0-or-later
// Zeroes three counters, then counts the table entries whose id word has key in bits 8 and up, by the flag bits 2, 4 and 8.
extern u8 D_eu_002490F0[];

void func_eu_00160830(s32 key, s32* c1, s32* c2, s32* c3)
{
    *c3 = 0;
    *c2 = 0;
    *c1 = 0;
    u8* p = D_eu_002490F0;
    u8* end = p + 0x1EE8;
    do {
        if ((*(s32*)(p + 0xA0) >> 8) == key) {
            if (*(s32*)(p + 0xA8) & 2) {
                *c1 += 1;
            }
            if (*(s32*)(p + 0xA8) & 4) {
                *c2 += 1;
            }
            if (*(s32*)(p + 0xA8) & 8) {
                *c3 += 1;
            }
        }
        p += 0xAC;
    } while (p < end);
}
