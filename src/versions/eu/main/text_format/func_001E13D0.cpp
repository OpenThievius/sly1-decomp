// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL reads the table byte unsigned (lbu).
u8 GetDecimalDigit(double self0, s32 a, s32 b)
{
    double self = self0;
    s32 idx;
    if (a < b || a - 15 >= b) {
        idx = 0;
    } else {
        f32 t = Power(10.0f, (f32)(-b));
        double p = MultiplyDoubles(self, ConvertFloatToDouble(t));
        self = TruncateDouble(p);
        p = TruncateDouble(MultiplyDoubles(self, 0.1));
        p = MultiplyDoubles(p, 10.0);
        idx = ConvertDoubleToS32(SubtractDoubles(self, p));
    }
    return ((u8*)&g_hexDigits)[idx];
}
