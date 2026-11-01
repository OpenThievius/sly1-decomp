// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the second argument is zero-extended to 16 bits instead of sign-extended from 8
s32 func_0015DAB8(void* a, u16 b);
s32 func_0015CA38(void* a, s32 b)
{
    return func_0015DAB8(a, (u16)b) != 0;
}
