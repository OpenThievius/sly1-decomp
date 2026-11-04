// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the trailing '0' and '.' are read as unsigned bytes.

s32 func_001E1498(char* buf, s32 unused, Spec_1E1498* sp, double v)
{
    Bits_001E1498 bits;
    bits.d = v;
    if ((bits.u & 0x7FF0000000000000UL) == 0x7FF0000000000000UL) {
        const char* s = (bits.u & 0x000FFFFFFFFFFFFFUL) ? D_0024E468 : D_0024E470;
        func_001E2138(buf, (char*)s);
        return func_001E2100(buf);
    }
    char* out = buf;
    s32 e = func_001E1330(v);
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
    f32 p = func_00205C78(10.0f, (f32)(base - prec));
    double r = func_001FCD20(v, func_001FCDE0(func_001FD868(p), 0.5));
    s32 e2 = func_001E1330(r);
    if (e < func_001E1330(r)) e = e2;
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
        *out++ = func_001E13D0(r, e, i--);
    }
    if (sp->noPoint == 0) {
        *out++ = '.';
        n = sp->prec;
        while (n-- > 0) {
            *out++ = func_001E13D0(r, e, i--);
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
        s32 d = (s32)func_00205C78(10.0f, 2.0f);
        for (s32 k = 2; k >= 0; k--) {
            *out++ = D_00275940[e / d];
            e = (e % d) * 10;
        }
    }
    return out - buf;
}
