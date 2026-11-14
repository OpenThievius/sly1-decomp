// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL reads the %c argument as an unsigned byte (lbu where US has lb)
void FormatConversionArg(FormatSpec* sp, OutputBuffer* c, u8** va, const char* fmt, s32 len) {
    u64 v;
    switch (sp->conv) {
    case '%':
        AppendToOutputBuffer(c, (void*)&sp->conv, 1);
        return;
    case 'c': {
        signed char buf[16];
        u8* p = *va;
        *va = p + 8;
        s32 ch = *(u8*)p;
        buf[0] = ch;
        AppendToOutputBuffer(c, (void*)buf, 1);
        return;
    }
    case 's': {
        u8* p = *va;
        *va = p + 8;
        FormatStringArg(sp, (PaddedOutput*)c, *(const char**)p);
        return;
    }
    case 'p':
        sp->prec = 8;
        sp->conv = 'x';
        sp->length = 0;
    case 'b': case 'd': case 'i': case 'o': case 'u': case 'x':
        switch (sp->length) {
        case 0: case 1: { u8* p = *va; *va = p + 8; v = *(u32*)p; break; }
        case 2: { u8* p = *va; *va = p + 8; v = *(u64*)p; break; }
        }
        FormatIntegerArg(sp, c, v);
        return;
    case 'e': case 'f': case 'g':
        if (sp->vectorCount != 0) {
            const char* s4 = "\n";
            u8* a = *va;
            const char* s8 = ",\n";
            const char* s7 = "{ ";
            *va = a + 8;
            const char* s5 = ", ";
            const char* s6 = " }";
            f32* fp = *(f32**)a;
            if (sp->matrixRows >= 2) {
                AppendToOutputBuffer(c, (void*)s4, GetStringLength(s4));
            }
            for (s32 i = 0; i < sp->matrixRows; ) {
                s32 next;
                if (i != 0) {
                    AppendToOutputBuffer(c, (void*)s8, GetStringLength(s8));
                }
                next = i + 1;
                AppendToOutputBuffer(c, (void*)s7, GetStringLength(s7));
                for (s32 j = 0; j < sp->vectorCount; j++) {
                    if (j != 0) {
                        AppendToOutputBuffer(c, (void*)s5, GetStringLength(s5));
                    }
                    FormatFloatArg(sp, c, ConvertFloatToDouble(*fp++));
                }
                AppendToOutputBuffer(c, (void*)s6, GetStringLength(s6));
                i = next;
            }
            if (sp->matrixRows >= 2) {
                AppendToOutputBuffer(c, (void*)s4, GetStringLength(s4));
            }
        } else {
            u8* p = *va;
            *va = p + 8;
            FormatFloatArg(sp, c, *(s64*)p);
        }
        return;
    case 'n':
        switch (sp->length) {
        case 0: { u8* p = *va; *va = p + 8; **(s32**)p = c->count; break; }
        case 1: { u8* p = *va; *va = p + 8; s16* q = *(s16**)p; s32 n = c->count; *q = n; break; }
        case 2: { u8* p = *va; *va = p + 8; **(s64**)p = c->count; break; }
        }
        return;
    default:
        AppendToOutputBuffer(c, (void*)fmt, len);
        return;
    }
}
