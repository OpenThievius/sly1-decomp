// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: starts the library on first use, then tells whether the byte after the first is 'T'.
extern char D_eu_00284650[];
char* func_eu_0020A730(void);

s32 func_eu_0020A7D0(void)
{
    if (D_eu_00284650[0] == 0) {
        func_eu_0020A730();
    }
    return D_eu_00284650[4] == 0x54;
}
