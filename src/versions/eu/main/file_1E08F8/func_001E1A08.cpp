// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL reads the %c argument as an unsigned byte (lbu where US has lb)
void func_001E1A08(Spec_001E1A08* sp, OutputBuffer* c, u8** va, const char* fmt, s32 len) {
    u64 v;
    switch (sp->ch) {
    case '%':
        AppendToOutputBuffer(c, (const char*)sp + 0x2C, 1);
        return;
    case 'c': {
        signed char buf[16];
        u8* p = *va;
        *va = p + 8;
        s32 ch = *(u8*)p;
        buf[0] = ch;
        AppendToOutputBuffer(c, (const char*)buf, 1);
        return;
    }
    case 's': {
        u8* p = *va;
        *va = p + 8;
        FormatStringArg(sp, c, *(const char**)p);
        return;
    }
    case 'p':
        sp->i1C = 8;
        sp->ch = 'x';
        sp->i20 = 0;
    case 'b': case 'd': case 'i': case 'o': case 'u': case 'x':
        switch (sp->i20) {
        case 0: case 1: { u8* p = *va; *va = p + 8; v = *(u32*)p; break; }
        case 2: { u8* p = *va; *va = p + 8; v = *(u64*)p; break; }
        }
        FormatIntegerArg(sp, c, v);
        return;
    case 'e': case 'f': case 'g':
        if (sp->i24 != 0) {
            const char* s4 = "\n";
            u8* a = *va;
            const char* s8 = ",\n";
            const char* s7 = "{ ";
            *va = a + 8;
            const char* s5 = ", ";
            const char* s6 = " }";
            f32* fp = *(f32**)a;
            if (sp->i28 >= 2) {
                AppendToOutputBuffer(c, s4, GetStringLength(s4));
            }
            for (s32 i = 0; i < sp->i28; ) {
                s32 next;
                if (i != 0) {
                    AppendToOutputBuffer(c, s8, GetStringLength(s8));
                }
                next = i + 1;
                AppendToOutputBuffer(c, s7, GetStringLength(s7));
                for (s32 j = 0; j < sp->i24; j++) {
                    if (j != 0) {
                        AppendToOutputBuffer(c, s5, GetStringLength(s5));
                    }
                    FormatFloatArg(sp, c, func_001FD868(*fp++));
                }
                AppendToOutputBuffer(c, s6, GetStringLength(s6));
                i = next;
            }
            if (sp->i28 >= 2) {
                AppendToOutputBuffer(c, s4, GetStringLength(s4));
            }
        } else {
            u8* p = *va;
            *va = p + 8;
            FormatFloatArg(sp, c, *(s64*)p);
        }
        return;
    case 'n':
        switch (sp->i20) {
        case 0: { u8* p = *va; *va = p + 8; **(s32**)p = c->count; break; }
        case 1: { u8* p = *va; *va = p + 8; s16* q = *(s16**)p; s32 n = c->count; *q = n; break; }
        case 2: { u8* p = *va; *va = p + 8; **(s64**)p = c->count; break; }
        }
        return;
    default:
        AppendToOutputBuffer(c, fmt, len);
        return;
    }
}
