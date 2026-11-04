// SPDX-License-Identifier: AGPL-3.0-or-later
// Copies the bytes of src into dst as halfwords up to its NUL, writes a 0 halfword after them and returns dst.
u16* func_eu_001E3140(u16* dst, u8* src)
{
    u16* d = dst;
    if (*src != 0) {
        do {
            *d = *src;
            d++;
            src++;
        } while (*src != 0);
    }
    *d = 0;
    return dst;
}
