// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the field is at 0x558 (US 0x248).
struct Obj_1AA8C0_eu { u8 pad[1368]; f32 value; };

void func_001AA8C0(Obj_1AA8C0_eu* self, f32 v)
{
    self->value = v;
}
