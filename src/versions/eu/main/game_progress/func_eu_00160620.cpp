// SPDX-License-Identifier: AGPL-3.0-or-later
// Finds p in the five-entry table D_eu_002636D8 and stores its index in D_eu_00263710.
extern s32 D_eu_002636D8[];
extern s32 D_eu_00263710;

void func_eu_00160620(s32 p)
{
    s32 key = p;
    u32 i = 0;
    while (i < 5) {
        if (p == D_eu_002636D8[i]) {
            D_eu_00263710 = i;
            break;
        }
        i++;
    }
}
