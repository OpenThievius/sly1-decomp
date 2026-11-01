// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the D_00270650 words at 0x594 and 0x598 (US 0x284 and 0x288).

void func_001793F0(Obj_1793F0* self)
{
    func_00124A48(self);
    func_00124DF8(self, 0x1A, D_00263AC8);
    func_0012B5B8(self->f6E8, self->f680, self->f680);
    ((Sub_1793F0*)self->f650)->fE0 = self->f660;
    self->f658 = func_001B6290(self->f654, self, -1, 0);
    func_00139038(self, 0xC, 5, &self->f684, 0, 0, 0, &self->f6C0);
    self->f684 = 1.0f;
    func_001399F8(self->f6C0, 0xC, 5, &self->f684);
    func_0017ABE8(self, 2);
    u8* base = D_00270650;
    ((Packed_1793F0*)(base + 0x598))->v = 0.0f;
    *(s32*)(base + 0x594) = func_001B4688(0x36A);
}

