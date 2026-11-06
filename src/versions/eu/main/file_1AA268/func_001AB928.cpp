// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: f288 and f28c sit 784 (0x310) bytes further on than in US.
struct Obj_1AB928_eu { u8 pad[0x288 + 0x310]; f32 f288; s32 f28c; };

void func_001AB928(Obj_1AB928_eu* self, s32 v, f32 f)
{
    self->f288 = f;
    self->f28c = v;
}
