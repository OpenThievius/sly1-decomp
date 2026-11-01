// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: stores a float argument at 0x51C of its object.
struct Obj_eu_1AB550 {
    u8 pad0[0x51C];
    f32 f51C;
};

void func_eu_001AB550(Obj_eu_1AB550* self, f32 v)
{
    self->f51C = v;
}
