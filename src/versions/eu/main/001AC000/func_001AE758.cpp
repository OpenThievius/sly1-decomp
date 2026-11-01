// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's flag pair and the field at 8 are 16-bit.
struct Flags_1AE758_eu { u16 a; u16 b; };
struct Obj_1AE758_eu { VFn_1AE758* vtbl; void* f4; u16 f8; };

void func_001AE758(Obj_1AE758_eu* self)
{
    f32 k = 0.25f;
    Flags_1AE758_eu fl;
    s32 v;

    func_001AA268(self);
    func_001AA8B0(self, k);
    func_001AA8C0(self, k);
    func_001AA8B8(self, 0.0f);
    void* r = func_0015C1C0(1);
    f32 g = *(f32*)D_002744AC;
    self->f4 = r;
    func_001AA788(self, g);
    v = func_001AEA08();
    fl.b = 0;
    fl.a = v;
    self->vtbl[8](self, &fl);
    self->f8 = 0;
}
