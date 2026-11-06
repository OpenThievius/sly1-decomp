// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the field is at 0x558 (US 0x248).
struct Obj_1AA8A8_eu { u8 pad[1368]; f32 value; };

f32 func_001AA8A8(Obj_1AA8A8_eu* self)
{
    return self->value;
}
