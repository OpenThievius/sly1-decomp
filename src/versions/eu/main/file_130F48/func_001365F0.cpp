// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the state is at 0x570 (US 0x260).
struct Obj_1365F0_eu { u8 pad0[0x570]; s32 state; };

f32 func_001AA898(Obj_1365F0_eu* self);

f32 func_001365F0(Obj_1365F0_eu* self)
{
    switch (self->state) {
    case 1:
    case 2:
    case 5:
        return 0.0f;
    case 3:
    case 4:
    default:
        return func_001AA898(self);
    }
}
