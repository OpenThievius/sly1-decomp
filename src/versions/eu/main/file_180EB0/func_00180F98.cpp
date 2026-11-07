// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the D_00270650 words at 0x594 and 0x598 (US 0x284 and 0x288).

void func_00180F98(ModeWalker* self)
{
    func_001D7440(self);
    ResolveObjectLinks(self, 0xA, g_modeWalkerLinks);
    self->fBBC = (StateWalker*)CreateStateWalker(self->fBB8, self, -1, 0);

    AddMatrixAttachment(self->fBCC, 5, &self->fBD0);
    ((u8*)self->fBD0)[0x10] = 9;
    ((u8*)self->fBD0)[0x11] = 9;
    ((Vt_180F98*)self->fBCC)->vtbl[0xBC / 4](self->fBCC);
    func_00128018(0, self->fBC0, (u8*)self->fBCC + 0x140, (u8*)self + 0xBE0);
    SetModeWalkerMode(self, 1);
    self->f864 = 3.4028234663852886e+38f;
    u8* base = (u8*)&D_00270650;
    ((Packed_180F98*)(base + 0x598))->v = 0.0f;
    *(s32*)(base + 0x594) = FindAnimRecord(0x36A);
}

