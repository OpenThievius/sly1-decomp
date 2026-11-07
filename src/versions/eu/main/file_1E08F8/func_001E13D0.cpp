// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL reads the table byte unsigned (lbu).
u8 func_001E13D0(RegDouble* self0, s32 a, s32 b)
{
    RegDouble* self = self0;
    s32 idx;
    if (a < b || a - 15 >= b) {
        idx = 0;
    } else {
        f32 t = Power(10.0f, (f32)(-b));
        RegDouble* p = func_001FCDE0(self, func_001FD868(t));
        self = TruncateDouble(p);
        p = TruncateDouble(func_001FCDE0(self, 0.1));
        p = func_001FCDE0(p, (u64)0x4024000000000000ULL);
        idx = ConvertDoubleToS32(func_001FCD78(self, p));
    }
    return ((u8*)&D_00275940)[idx];
}
