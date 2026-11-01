// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL reads the state byte unsigned (lbu).
struct Obj_12D448_eu {
    u8 pad0[0x24];
    u8 state;
};

void func_0012D448(Obj_12D448_eu* self, s32 v)
{
    if (v == self->state) {
        return;
    }
    if (v != 0) {
        func_001DDA20(*(void**)&D_00275710);
    } else {
        func_001DDA50(*(void**)&D_00275710);
    }
    self->state = (s8)v;
}
