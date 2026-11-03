// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL definition: same code as US, PAL data addresses.
struct Ctx_eu_16BBA8 { u8 pad0[0x570]; s32 f570; };
void func_0016BBA8(Ctx_eu_16BBA8* ctx, Obj_16BBA8* o)
{
    s32 s1;
    s32 r2;

    if ((o->flags & 0x9B0) != 0 || (o->f14 == 1 && 5.0f <= D_0026185C[0])) {
        func_0016EC20(o, 0x9B0);
        func_001E9570((Group_16BBA8*)D_00275BC0);
        return;
    }
    if ((o->flags & 0x40) != 0) {
        func_0016EC20(o, 0x40);
        if (func_0016BB78((Bits_16BBA8*)ctx->f570) != 0) {
            func_0018E4C0((Bits_16BBA8*)ctx->f570);
            return;
        }
        func_001BFCD8((Tag_16BBA8*)0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    s1 = func_0016EC98(o);
    r2 = func_0016EED0(o);
    if (s1 == 0 && r2 == 0) {
        return;
    }
    o->f30 = D_00261858[4] + o->f34;
    o->f38 = D_00261858[4] + o->f3C;

    {
        s32 n = ctx->f570;
        s32 q = n / 4;
        s32 r = n % 4;
        if (s1 < 0 && r == 0)
            r2 = -1;
        if (s1 > 0 && r == 3)
            r2 = 1;
        s32 dy = r2 + 4;
        s32 dx = s1 + 4;
        q = (q + dy) % 4;
        r = (r + dx) % 4;
        ctx->f570 = q * 4 + r;
    }
    func_001BFCD8((Tag_16BBA8*)0x79, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
}
