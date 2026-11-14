// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the trailing '0' and '.' are read as unsigned bytes.

s32 FormatFloatDigits(char* buf, s32 unused, FormatSpec* sp, double v)
{
    DoubleBits bits;
    bits.d = v;
    if ((bits.u & 0x7FF0000000000000UL) == 0x7FF0000000000000UL) {
        const char* s = (bits.u & 0x000FFFFFFFFFFFFFUL) ? "(nan)" : "(inf)";
        CopyString(buf, (char*)s);
        return GetStringLength(buf);
    }
    char* out = buf;
    s32 e = GetDecimalExponent(v);
    s32 isE = sp->conv == 'e';
    if (sp->conv == 'g') {
        if (e < -4 || e >= sp->prec) {
            isE = 1;
            sp->prec = sp->prec - 1;
        }
    }
    s32 base = 0;
    if (isE) base = e;
    s32 prec = sp->prec;
    f32 p = Power(10.0f, (f32)(base - prec));
    double r = AddDoubles(v, MultiplyDoubles(ConvertFloatToDouble(p), 0.5));
    s32 e2 = GetDecimalExponent(r);
    if (e < GetDecimalExponent(r)) e = e2;
    s32 n, i;
    if (isE) {
        n = 1;
        i = e;
    } else if (e >= 0) {
        i = e;
        n = e + 1;
    } else {
        n = 1;
        i = 0;
    }
    while (n-- > 0) {
        *out++ = GetDecimalDigit(r, e, i--);
    }
    if (sp->noprec == 0) {
        *out++ = '.';
        n = sp->prec;
        while (n-- > 0) {
            *out++ = GetDecimalDigit(r, e, i--);
        }
        if (sp->conv == 'g' && buf < out) {
            while (buf < out && ((u8*)out)[-1] == '0') out--;
            if (buf < out && ((u8*)out)[-1] == '.') out--;
        }
    }
    if (isE) {
        *out++ = 'e';
        if (e < 0) {
            *out++ = '-';
            e = -e;
        } else {
            *out++ = '+';
        }
        s32 d = (s32)Power(10.0f, 2.0f);
        for (s32 k = 2; k >= 0; k--) {
            *out++ = g_hexDigits[e / d];
            e = (e % d) * 10;
        }
    }
    return out - buf;
}
