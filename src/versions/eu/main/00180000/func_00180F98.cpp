// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the D_00270650 words at 0x594 and 0x598 (US 0x284 and 0x288).

void func_00180F98(Obj_180F98* self)
{
    func_001D7440(self);
    func_00124DF8(self, 0xA, D_002640B0);
    self->fBBC = (s32)func_001B6290(self->fBB8, self, -1, 0);
    func_00129D00(self->fBCC, 5, &self->fBD0);
    ((u8*)self->fBD0)[0x10] = 9;
    ((u8*)self->fBD0)[0x11] = 9;
    ((Vt_180F98*)self->fBCC)->vtbl[0xBC / 4](self->fBCC);
    func_00128018(0, self->fBC0, (u8*)self->fBCC + 0x140, (u8*)self + 0xBE0);
    func_00181DA8(self, 1);
    self->f864 = 3.4028234663852886e+38f;
    u8* base = D_00270650;
    ((Packed_180F98*)(base + 0x598))->v = 0.0f;
    *(s32*)(base + 0x594) = func_001B4688(0x36A);
}

