// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: f328 is at 0x5B4 (US 0x328).
struct Self_135F48_eu {
    u8 pad000[0x5B4];
    s32 f5B4;
};

void func_00135E78(Self_135F48_eu* self, s32 state, s32 flag);
void func_001358D0(Self_135F48_eu* self, s32 a1, void* a2, void* a3, s32 a4, s32 a5, f32 f);

void func_00135F48(Self_135F48_eu* self)
{
    Flag_135F48 flag;
    func_00160D30(&flag);
    if ((func_00160D10() & flag.v) == 0) {
        func_00135E78(self, 0, 1);
        return;
    }
    func_00135E78(self, 1, 0);
    if (self->f5B4 == 1) {
        f32 k = D_00249CFC;
        Ctx_135F48* ctx = *(Ctx_135F48**)D_00275710;
        func_001358D0(self, 0x2E, func_00135E20 + 0x10, func_00135E40 + 8, 5, ctx->f1D44, k);
        func_001358D0(self, 0x21, func_00135E20 + 0x10, func_00135E40 + 8, 5, (*(Ctx_135F48**)D_00275710)->f1D54, k);
    }
}
