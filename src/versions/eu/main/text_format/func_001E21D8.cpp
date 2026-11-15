// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: reads the characters as unsigned bytes
char* FindCharInString(const char* s, s32 c)
{
    while (*(u8*)s != 0) {
        if (*(u8*)s == c) {
            return (char*)s;
        }
        s++;
    }
    return 0;
}
