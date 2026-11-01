// SPDX-License-Identifier: AGPL-3.0-or-later
// Compares two zero-terminated u16 strings, returning the difference at the first unequal unit, or 0.
s32 func_eu_001E3100(u16* a, u16* b)
{
    while (*a != 0 || *b != 0) {
        s32 d = *a - *b;
        if (d != 0) {
            return d;
        }
        a++;
        b++;
    }
    return 0;
}
