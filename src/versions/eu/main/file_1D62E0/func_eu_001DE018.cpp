// SPDX-License-Identifier: AGPL-3.0-or-later
// Returns entry i of the PAL-only pointer table D_eu_0027EEA0 for i below 14, else the PAL-only string D_eu_0027EDF8.
extern const char* D_eu_0027EEA0[];
extern char D_eu_0027EDF8[];

const char* func_eu_001DE018(u32 i)
{
    if (i < 0xE) {
        return D_eu_0027EEA0[i];
    }
    return D_eu_0027EDF8;
}
