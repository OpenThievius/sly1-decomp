// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the second argument is zero-extended to 16 bits instead of sign-extended from 8
V24A2_Glyph* func_0015DAB8(V24A2* a, u16 b);
s32 func_0015CA38(V24A2* a, s32 b)
{
    return FindFontGlyph(a, (u16)b) != 0;
}
