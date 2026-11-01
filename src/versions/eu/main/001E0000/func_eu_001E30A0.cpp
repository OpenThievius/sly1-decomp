// SPDX-License-Identifier: AGPL-3.0-or-later
// Appends the second zero-terminated u16 string to the first (strcat) and returns the first.
s32 func_eu_001E3018(u16* p);
void func_0018D800(void* dst, void* src, s32 bytes);
u16* func_eu_001E30A0(u16* dst, u16* src)
{
    s32 n = func_eu_001E3018(dst);
    s32 m = func_eu_001E3018(src);
    func_0018D800(dst + n, src, (m + 1) * 2);
    return dst;
}
