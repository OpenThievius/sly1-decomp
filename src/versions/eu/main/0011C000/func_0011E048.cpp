// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL packs one more word (a9) and passes size 0x20 instead of 0x1C.
struct Pack8_11E048 { void* w0; s32 w1; s32 w2; s32 w3; s32 w4; s32 w5; s32 w6; s32 w7; };

s32 func_0011D968(s32 id, s32 size, void* data);

s32 func_0011E048(void* a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9)
{
    Pack8_11E048 buf;
    buf.w0 = a0;
    buf.w1 = a1;
    buf.w2 = (a4 << 16) | (a2 & 0xFFFF);
    buf.w3 = (a5 << 16) | (a3 & 0xFFFF);
    buf.w4 = a6;
    buf.w5 = a7;
    buf.w6 = a8;
    buf.w7 = a9;
    return func_0011D968(0x2C, 0x20, &buf);
}
