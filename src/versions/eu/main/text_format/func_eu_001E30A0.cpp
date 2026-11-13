// SPDX-License-Identifier: AGPL-3.0-or-later
// Appends the second zero-terminated u16 string to the first (strcat) and returns the first.
s32 GetWideStringLength(u16* p);
void CopyMemory(void* dst, void* src, s32 bytes);
u16* AppendWideString(u16* dst, u16* src)
{
    s32 n = GetWideStringLength(dst);
    s32 m = GetWideStringLength(src);
    CopyMemory(dst + n, src, (m + 1) * 2);
    return dst;
}
