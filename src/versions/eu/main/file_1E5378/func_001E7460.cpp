// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the three node pointers are at 0x580, 0x584 and 0x588 (US 0x270, 0x274, 0x278).
struct Obj_1E7460_eu;
void func_00126BC0(C02* node, Obj_1E7460_eu* self);
struct Obj_1E7460_eu { u8 pad0[0x580]; C02* f580; C02* f584; C02* f588; };

void func_001E7460(Obj_1E7460_eu* self)
{
    C02* cur = self->f584;
    if (self->f580 == cur) {
        return;
    }
    if (cur != 0) {
        if (!(D_00270458 == 4 && cur == self->f588)) {
            cur->desc->m03(cur);
        }
    }
    self->f584 = self->f580;
    if (self->f584 != 0) {
        self->f584->desc->m02(self->f584);
        if (D_00270458 != 4) {
            func_00126BC0(self->f584, self);
        }
        self->f584->flags |= 0x100000000UL;
    }
}
