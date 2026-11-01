// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: runs func_eu_001AAFB0 on the object, then sets the float at 0x558 to 0.5.
struct Obj_eu_1AE6A0 {
    u8 pad0[0x558];
    f32 f558;
};

void func_eu_001AAFB0(Obj_eu_1AE6A0* self);

void func_eu_001AE6A0(Obj_eu_1AE6A0* self)
{
    func_eu_001AAFB0(self);
    self->f558 = 0.5f;
}
