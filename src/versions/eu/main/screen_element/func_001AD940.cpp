// SPDX-License-Identifier: AGPL-3.0-or-later
// Only in PAL: runs SetupScreenElementText on the object, then sets the float at 0x558 to 0.5.
struct Obj_eu_1AE6A0 {
    u8 pad0[0x558];
    f32 f558;
};

void SetupScreenElementText(Obj_eu_1AE6A0* self);

void InitLetterboxElement(Obj_eu_1AE6A0* self)
{
    SetupScreenElementText(self);
    self->f558 = 0.5f;
}
