// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the field is at 0x550 (US 0x240).
struct Obj_1AA898_eu { u8 pad[1360]; f32 value; };

f32 func_001AA898(Obj_1AA898_eu* self)
{
    return self->value;
}
