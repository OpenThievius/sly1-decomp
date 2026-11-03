// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: sets the object's state (0 to 3); 69 elements, fields 0x310 further on, tail 0x520 further on.
struct Obj_1E7518_eu
{
    u8 pad000[0x578];
    s32 f578;
    f32 f57C;
    u8 pad580[0x10];
    Elem_1E77C0 elems[69];
    u8 pad_tail[0x1190 - 0x590 - 69 * 0x2C];
    f32 f1190;
};

void func_001E7518(Obj_1E7518_eu* self, s32 mode)
{
    if (mode == self->f578) {
        return;
    }
    switch (mode) {
    case 0: {
        func_001BFCD8(0x8C, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        for (s32 i = 0; i < 69; i++) {
            Elem_1E77C0* e = &self->elems[i];
            e->f18 = 1.0f;
            e->f1C = func_001EAAE0(0.0f, 0.05f);
            e->f20 = 1.0f;
            e->f24 = 0.6f;
            e->f28 = 0.2f;
        }
        break;
    }
    case 2:
        func_001BFCD8(0x8D, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        break;
    case 1:
        self->f1190 = 1.0f;
        break;
    case 3:
        self->f1190 = 0.0f;
        func_001E7460((Obj_1E7460*)self);
        break;
    }
    self->f578 = mode;
    self->f57C = D_00261858[4];
}
