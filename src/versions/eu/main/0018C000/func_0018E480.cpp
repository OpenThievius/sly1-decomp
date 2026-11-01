// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: an index under 16 gives the text of its id in a table; anything else gives one fallback string.
// D_eu_0026AC20 is US D_002699C0, at an address the tools do not pair.

extern s32 D_eu_0026AC20[];
extern u8 D_eu_0027F0B0[];
const char* func_eu_001DDAB0(s32 id);

u8* func_0018E480(s32 index)
{
    if ((u32)index < 16) {
        return (u8*)func_eu_001DDAB0(D_eu_0026AC20[index]);
    }
    return D_eu_0027F0B0;
}
