// SPDX-License-Identifier: AGPL-3.0-or-later
// Calls func_eu_001E3018 on n, then func_0018D800 (PAL 0018DE90) on self with n and twice the result plus one; returns self.
s32 GetWideStringLength(s32 n);
void CopyMemory(void* self, s32 n, s32 count);

void* CopyWideString(void* self, s32 n)
{
    s32 r = GetWideStringLength(n);

    CopyMemory(self, n, (r + 1) << 1);
    return self;
}
