// SPDX-License-Identifier: AGPL-3.0-or-later
// BROKEN, checked 2026-11-01
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_00160620.cpp func_eu_00160620 --unit src/main/00160000.cpp
// Still differs: Stores the index of p in the five-entry table D_eu_002636D8; retail peels index 0 (sw zero) and indexes with sll from a copy of p in a2, ours steps a pointer.
// Finds p in the five-entry table D_eu_002636D8 and stores its index in D_eu_00263710.
extern void* D_eu_002636D8[];
extern s32 D_eu_00263710;

void func_eu_00160620(void* p)
{
    u32 i = 0;

    while (p != D_eu_002636D8[i]) {
        i++;
        if (i >= 5) {
            return;
        }
    }
    D_eu_00263710 = i;
}
