// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL picks the element D_eu_00263710 (32 bytes each) of the table at D_00247AD0 + 0x80 for the first call.
extern s32 D_eu_00263710;
void func_001F4408(s32 flag, s32 n)
{
    Ctx_1F4408* ctx = *(Ctx_1F4408**)D_002623C0;
    Obj_1F4408* o;
    Obj_1F4408* v;
    Val_1F4408* k;
    Args_1F4408 args;
    if (ctx->f19D8 == 5) {
        goto lm1;
    }
    if (ctx->f19DC != 0) {
        goto l4490;
    }
    o = *(Obj_1F4408**)D_002623C4;
    if ((o->f78 & 1) != 0) {
        goto l4470;
    }
lm1:
    func_001F0428((Val_1F4408*)(D_00247AD0 + 0x80 + D_eu_00263710 * 32), -1, n);
    return;
l4470:
    k = func_00160180((Key_1F4408*)(u32)((ctx->f19D8 << 8) | 1));
    func_001F0428(k, 0x1BD, n);
    return;
l4490:
    v = (Obj_1F4408*)func_001F4378();
    if (v == 0) {
        goto larg;
    }
    if (flag != 0) {
        v->f310 = 0;
    }
    func_001F4808(v);
    return;
larg:
    args.f00 = 1;
    args.f04 = D_00275B04;
    args.f08 = -1;
    args.f0C = -1;
    args.f10 = 0;
    func_001EFFA0((Dst_1F4408*)D_00275F80, &args, n);
}
