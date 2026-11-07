// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the three node pointers are at 0x580, 0x584 and 0x588 (US 0x270, 0x274, 0x278).
struct Obj_1E7460_eu;
void SetObjectTreeRecordsValue(PlacedObject* node, Obj_1E7460_eu* self);
struct Obj_1E7460_eu { u8 pad0[0x580]; PlacedObject* f580; PlacedObject* f584; PlacedObject* f588; };

void ApplyArcTarget(Obj_1E7460_eu* self)
{
    PlacedObject* cur = self->f584;
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
            SetObjectTreeRecordsValue(self->f584, self);
        }
        self->f584->flags |= 0x100000000UL;
    }
}
