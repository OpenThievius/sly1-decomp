// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the linked pointer is at 0x588 (US 0x278).
struct Obj_1E87F0_eu { u8 pad0[0x588]; Obj_1E87F0* f588; };

void func_001E87F0(Obj_1E87F0_eu* self, Obj_1E87F0* a1)
{
    Obj_1E87F0* old = self->f588;
    if (old != 0) {
        old->f2C8 &= ~(1ULL << 32);
    }
    self->f588 = a1;
    if (a1 != 0) {
        a1->f2C8 |= (1ULL << 32);
    }
}
