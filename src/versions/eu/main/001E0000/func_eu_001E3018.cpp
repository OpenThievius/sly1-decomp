// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: returns the length of a 16-bit zero-terminated string.
s32 func_eu_001E3018(const u16* s)
{
    s32 n = 0;
    if (*s != 0) {
        do {
            s++;
            n++;
        } while (*s != 0);
    }
    return n;
}
