// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the whole object is laid out 0x310 further on: f210 at 0x520, f260 at 0x570, arr268 at 0x578, f27C at 0x58C, f284 at 0x594.
struct Obj_193E58_eu {
    u8 pad0[0x520];
    void** f520;
    u8 pad1[0x4C];
    s32 f570;
    u8 pad2[0x4];
    s32 arr578[3];
    u8 pad3[0x8];
    s32 f58C;
    u8 pad4[0x4];
    f32 f594;
};

void func_00193E58(Obj_193E58_eu* self)
{
    func_001AA268((Obj_193E58*)self);
    if (func_0015C188(2)) {
        self->f520 = (void**)D_0026A210;
        *self->f520 = func_0015C1C0(2);
    }
    self->f570 = -1;
    self->f58C = -1;
    for (u32 i = 0; i < 3; i++) {
        self->arr578[i] = -1;
    }
    self->f594 = 1.0f;
}
