// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: appends a byte string to a 16-bit string (each byte widened), returns the destination.
s32 func_eu_001E3018(const u16* s);

u16* func_eu_001E3178(u16* dst, const u8* src)
{
    s32 n = func_eu_001E3018(dst);
    u16* p = dst + n;
    if (*src != 0) {
        do {
            *p++ = *src++;
        } while (*src != 0);
    }
    *p = 0;
    return dst;
}
