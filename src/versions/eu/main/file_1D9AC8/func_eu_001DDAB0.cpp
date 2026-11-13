// SPDX-License-Identifier: AGPL-3.0-or-later
// Returns entry i of the text table when i is in range, otherwise the empty string at D_eu_0027F0B0.
extern s32 D_eu_0027EE8C;
extern s32* D_eu_0027ED80;
extern char D_eu_0027F0B0[];

const char* func_eu_001DDAB0(s32 i)
{
    if (i >= 0 && i < D_eu_0027EE8C) {
        return (const char*)D_eu_0027ED80[i];
    }
    return D_eu_0027F0B0;
}
