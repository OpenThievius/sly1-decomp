// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 132/144 (91.7%), checked 2026-11-01
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_00160680.cpp func_eu_00160680 --unit src/main/00160000.cpp
// Still differs: Scans record entries for a0; only the v0/v1 register choice for the match flag and the two xor temporaries differs (9 lines).
// Searches the five entries of each 0xAC-byte record in D_eu_002490F0 for a0 (or one with the same two words) and returns the record, or 0.
extern u8 D_eu_002490F0[];
u8* func_eu_00160680(u8* a0)
{
    s32 v;
    u8* a5 = D_eu_002490F0;
    u8* end = a5 + 0x1EE8;
    do {
        u32 k = 0;
        u8* a2 = a5;
        do {
            if (a0 == a2) {
                v = 1;
            } else if (a0 == 0) {
                v = 0;
            } else if (a2 == 0) {
                v = 0;
            } else {
                s32 x = *(s32*)(a0 + 0x8) ^ *(s32*)(a0 + 0x18);
                s32 y = *(s32*)(a2 + 0x8) ^ *(s32*)(a2 + 0x18);
                v = (x ^ y) == 0;
            }
            k++;
            if (v == 0) {
                a2 += 0x20;
                continue;
            }
            return a5;
        } while (k < 5);
        a5 += 0xAC;
    } while (a5 < end);
    return 0;
}
