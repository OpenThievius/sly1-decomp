// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the field is at 0x554 (US 0x244).
struct Obj_1AA8B8_eu { u8 pad[1364]; f32 value; };

void func_001AA8B8(Obj_1AA8B8_eu* self, f32 v)
{
    self->value = v;
}
