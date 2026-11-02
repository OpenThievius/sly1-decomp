// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: each entry of the table is 0xAC bytes, not 0x2C, with its two fields 0x80 further on.

s32 func_00160B28(u8* p)
{
    s32 total = 0;
    s32 done = 0;
    u32 i;
    s32 k;
    for (i = 0; i < 0x2E; i++) {
        u8* e = D_00247AF0 + i * 0xAC;
        u32 v = *(u32*)(e + 0xA0);
        s32 idx = (s32)v >> 8;
        if (idx != 0) {
            u32 flags = *(u32*)(e + 0xA8);
            u32* w = (u32*)(p + (idx * 0x44C + 0x10) + (v & 0xFF) * 0x78);
            u32 bit;
            total++;
            done += *w & 1;
            for (bit = 2; bit & 0xE; bit <<= 1) {
                if (flags & bit) {
                    total++;
                    if (*w & bit) done++;
                }
            }
        }
    }
    for (k = 0; k < 5; k++) {
        total++;
        if (*(u32*)(p + 0x8A4 + k * 0x44C) & 0x20) done++;
    }
    if (done == 0) return 0;
    if (done == total) return 100;
    return Clamp_160B28::Of(done * 100 / total, 1, 99);
}
