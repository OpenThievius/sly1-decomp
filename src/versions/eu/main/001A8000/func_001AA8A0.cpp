// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the field is at 0x554 (US 0x244).
struct Obj_1AA8A0_eu { u8 pad[1364]; f32 value; };

f32 func_001AA8A0(Obj_1AA8A0_eu* self)
{
    return self->value;
}
