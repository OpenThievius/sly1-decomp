// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's initialiser: sets four fields (other offsets than US) and calls the base initialiser.
struct Obj_1310F0_eu {
    u8 pad0[0x544];
    f32 f544;
    f32 f548;
    u8 pad1[0x57C - 0x54C];
    f32 f57C;
    u32 f580;
};
void func_eu_001AAF38(Obj_1310F0_eu* self, s32 a1);
void InitTextPanel(Obj_1310F0_eu* self, s32 a1)
{
    self->f544 = 640.0f;
    self->f548 = 468.610168f;
    self->f57C = 15.0f;
    self->f580 = 0x80FFFFFF;
    func_eu_001AAF38(self, a1);
}
