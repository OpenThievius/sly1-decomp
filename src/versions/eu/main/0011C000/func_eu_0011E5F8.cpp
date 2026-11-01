// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: passes two words in a local buffer to func_0011D968 with id 0x5A and size 8.
s32 func_0011D968(s32 id, s32 size, void* data);

void func_eu_0011E5F8(s32 a, s32 b)
{
    s32 buf[2];
    buf[0] = a;
    buf[1] = b;
    (void)func_0011D968(0x5A, 8, buf);
}
