// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL reads the format string as unsigned bytes (lbu).
s32 func_001E1DB8(Ctx_1E1DB8* ctx, const char* fmt, void* a2)
{
    Locals_1E1DB8 loc;
    const u8* s1 = (const u8*)fmt;

    loc.va = a2;
    if (*s1 != 0) {
        do {
            char* s2 = func_001E21D8((Str_1E1DB8*)s1, '%');
            s32 n = (s32)s2 - (s32)s1;
            if (s2 == 0) {
                n = func_001E2100((Str_1E1DB8*)s1);
                s2 = (char*)((s32)s1 + n);
            }
            if (n != 0) {
                if (func_001D7190(ctx, (const char*)s1, n) < n) {
                    break;
                }
                s1 = (const u8*)s2;
            }
            if (*s1 == '%') {
                s32 n2 = func_001E0978((const char*)s1, loc.spec, (void*)&loc.va);
                func_001E1A08(loc.spec, ctx, (void*)&loc.va, (const char*)s1, n2);
                s1 = s1 + n2;
            }
        } while (*s1 != 0);
    }
    func_001D72C8(ctx);
    return ctx->count;
}
