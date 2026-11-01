// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the three node pointers are at 0x580, 0x584 and 0x588 (US 0x270, 0x274, 0x278).
struct Obj_1E7460_eu { u8 pad0[0x580]; Node_1E7460* f580; Node_1E7460* f584; Node_1E7460* f588; };

void func_001E7460(Obj_1E7460_eu* self)
{
    Node_1E7460* cur = self->f584;
    if (self->f580 == cur) {
        return;
    }
    if (cur != 0) {
        if (!(D_00270458 == 4 && cur == self->f588)) {
            ((void (*)(Node_1E7460*))cur->vtable[7])(cur);
        }
    }
    self->f584 = self->f580;
    if (self->f584 != 0) {
        ((void (*)(Node_1E7460*))self->f584->vtable[6])(self->f584);
        if (D_00270458 != 4) {
            func_00126BC0(self->f584, (Obj_1E7460*)self);
        }
        self->f584->f2C8 |= 0x100000000UL;
    }
}
