// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the linked pointer is at 0x588 (US 0x278).
struct Obj_1E87F0_eu { u8 pad0[0x588]; PlacedObject* f588; };

void SetArcSpecialObject(Obj_1E87F0_eu* self, PlacedObject* a1)
{
    PlacedObject* old = self->f588;
    if (old != 0) {
        old->flags &= ~(1ULL << 32);
    }
    self->f588 = a1;
    if (a1 != 0) {
        a1->flags |= (1ULL << 32);
    }
}
