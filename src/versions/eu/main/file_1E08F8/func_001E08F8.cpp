// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL reads the characters as unsigned bytes.
s32 func_001E08F8(u8* s, s32* out)
{
    u8* p = s;
    s32 sign = 1;
    s32 value = 0;
    s32 count = 0;

    if (*p == 0x2D) {
        sign = -1;
    }
    if (sign == -1) {
        p++;
        count = 1;
    }
    if ((u32)(*p - 0x30) < 10) {
        do {
            value = value * 10 + (*p - 0x30);
            p++;
            count++;
        } while ((u32)(*p - 0x30) < 10);
    }
    *out = value * sign;
    return count;
}
