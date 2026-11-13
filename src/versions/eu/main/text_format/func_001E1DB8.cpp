// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL reads the format string as unsigned bytes (lbu).
s32 FormatToOutputBuffer(OutputBuffer* ctx, const char* fmt, void* a2)
{
    FormatFrame loc;
    const u8* s1 = (const u8*)fmt;

    loc.va = a2;
    if (*s1 != 0) {
        do {
            char* s2 = FindCharInString((const char*)s1, '%');
            s32 n = (s32)s2 - (s32)s1;
            if (s2 == 0) {
                n = GetStringLength((const char*)s1);
                s2 = (char*)((s32)s1 + n);
            }
            if (n != 0) {
                if (AppendToOutputBuffer(ctx, (const char*)s1, n) < n) {
                    break;
                }
                s1 = (const u8*)s2;
            }
            if (*s1 == '%') {
                s32 n2 = ParseFormatSpec((const char*)s1, &loc.spec, (void*)&loc.va);
                FormatConversionArg(&loc.spec, ctx, (void*)&loc.va, (const char*)s1, n2);
                s1 = s1 + n2;
            }
        } while (*s1 != 0);
    }
    FlushOutputBuffer(ctx);
    return ctx->count;
}
