// SPDX-License-Identifier: AGPL-3.0-or-later
// Calls func_eu_001E3018 on n, then func_0018D800 (PAL 0018DE90) on self with n and twice the result plus one; returns self.
s32 func_eu_001E3018(s32 n);
void func_0018D800(void* self, s32 n, s32 count);

void* func_eu_001E3050(void* self, s32 n)
{
    s32 r = func_eu_001E3018(n);

    func_0018D800(self, n, (r + 1) << 1);
    return self;
}
