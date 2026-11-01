// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the field is at 0x550 (US 0x240).
struct Obj_1AA8B0_eu { u8 pad[1360]; f32 value; };

void func_001AA8B0(Obj_1AA8B0_eu* self, f32 v)
{
    self->value = v;
}
