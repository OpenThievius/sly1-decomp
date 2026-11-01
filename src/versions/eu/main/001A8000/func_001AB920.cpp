// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: field_26C sits 784 (0x310) bytes further on than in US.
struct Actor_001AB920_eu { u8 pad[0x26C + 0x310]; f32 field_26C; };

void func_001AB920(Actor_001AB920_eu* self, f32 value)
{
    self->field_26C = value;
}
