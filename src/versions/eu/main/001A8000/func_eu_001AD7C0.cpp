// SPDX-License-Identifier: AGPL-3.0-or-later
// Clears the field at 0x570 when the state at 0x560 is 3 and that field is set; otherwise calls func_001AA958 on the object.
struct Obj_eu_001AD7C0 { u8 pad[0x560]; s32 f560; u8 pad2[0xC]; s32 f570; };

void func_eu_001AD7C0(Obj_eu_001AD7C0* self)
{
    if (self->f560 == 3 && self->f570 != 0) {
        self->f570 = 0;
    } else {
        func_001AA958((Obj_1AA958_eu*)self);
    }
}
