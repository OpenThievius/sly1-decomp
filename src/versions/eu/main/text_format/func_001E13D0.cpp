// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL reads the table byte unsigned (lbu).
u8 GetDecimalDigit(RegDouble* self0, s32 a, s32 b)
{
    RegDouble* self = self0;
    s32 idx;
    if (a < b || a - 15 >= b) {
        idx = 0;
    } else {
        f32 t = Power(10.0f, (f32)(-b));
        // The value is held in the register view its callers give it (written on double, the code
        // changes), so each soft-float call goes through the real function cast to that view.
        RegDouble* p = ((RegDouble* (*)(RegDouble*, double))MultiplyDoubles)(self, ConvertFloatToDouble(t));
        self = ((RegDouble* (*)(RegDouble*))TruncateDouble)(p);
        p = ((RegDouble* (*)(RegDouble*))TruncateDouble)(((RegDouble* (*)(RegDouble*, double))MultiplyDoubles)(self, 0.1));
        p = ((RegDouble* (*)(RegDouble*, u64))MultiplyDoubles)(p, (u64)0x4024000000000000ULL);
        idx = ((s32 (*)(RegDouble*))ConvertDoubleToS32)(((RegDouble* (*)(RegDouble*, RegDouble*))SubtractDoubles)(self, p));
    }
    return ((u8*)&g_hexDigits)[idx];
}
