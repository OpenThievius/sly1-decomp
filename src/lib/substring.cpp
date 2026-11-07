// SPDX-License-Identifier: AGPL-3.0-or-later
// The C library's substring search, its own object from 0x1F6880 to 0x1F68EC
// (config/us/files.tsv): one function, word for word a member of the toolchain's libc.a built
// from a .c source. No data of its own. Retail pads it to 0x1F6900, where Sony's kernel library
// starts.

char* func_001F6880(char* s, char* t)
{
    int i;
    if (*s == 0) {
        if (*t) {
            return 0;
        }
        return s;
    }
    while (*s) {
        i = 0;
        while (1) {
            if (t[i] == 0) {
                return s;
            }
            if (t[i] != s[i]) {
                break;
            }
            i++;
        }
        s++;
    }
    return 0;
}
