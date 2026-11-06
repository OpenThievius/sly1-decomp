// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL takes the key as an unsigned 16-bit value and also matches it against a second table of u16 keys.
extern s32 D_00262258;

s32 func_0015C200(s32 a0)
{
    u16 key = (u16)a0;
    s32 i = 0;
    while (i < 5 && key != (u8)g_fontEscapeKeys[i] && key != ((u16*)&D_00262258)[i]) {
        i++;
    }
    if (i < 5) {
        return g_fonts[i];
    }
    return 0;
}
