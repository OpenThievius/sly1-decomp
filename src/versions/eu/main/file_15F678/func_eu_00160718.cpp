// SPDX-License-Identifier: AGPL-3.0-or-later
// Searches the 0xAC-byte table for an entry whose id word equals key; returns it, or 0.
extern u8 D_eu_002490F0[];

void* func_eu_00160718(s32 key)
{
    u8* p = D_eu_002490F0;
    u8* end = p + 0x1EE8;
    for (;;) {
        if (key != *(s32*)(p + 0xA0)) {
            p += 0xAC;
            if (p < end) {
                continue;
            }
            return 0;
        }
        return p;
    }
}
