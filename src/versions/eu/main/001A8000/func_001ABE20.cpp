// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: state and timer sit 784 (0x310) bytes further on than in US.
extern f32 D_0026185C;

struct Obj_1ABE20_eu { u8 pad[0x260 + 0x310]; s32 state; f32 timer; };

void func_001ABE20(Obj_1ABE20_eu* self, s32 state)
{
    if (self->state != state) {
        self->state = state;
        self->timer = D_0026185C;
    }
}
