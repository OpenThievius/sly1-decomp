// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's constructor tail of an object: sets its colour, speed fields and a bound-handle slot.
struct Obj_16B4A0_eu {
    u8 pad0[0x518];
    u8 f518[4];
    u8 pad51C[4];
    s32* f520;
    u8 pad524[0x570 - 0x524];
    s32 f570;
    s32 f574;
    f32 f578;
};

void func_001AA268(Obj_16B4A0_eu* self);
void func_001AA8B8(Obj_16B4A0_eu* self, f32 zero);

void func_0016B4A0(Obj_16B4A0_eu* self)
{
    func_001AA268(self);
    if (func_0015C188(2)) {
        self->f520 = D_00262988;
        *self->f520 = (s32)func_0015C1C0(2);
    }
    func_001AA8B8(self, 0.0f);
    self->f570 = 0;
    *(u32*)self->f518 = 0xDF7F7F7F;
    self->f574 = 0;
    self->f578 = -D_00262970;
}
