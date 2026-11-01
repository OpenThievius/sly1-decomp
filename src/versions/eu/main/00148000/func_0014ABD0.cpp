// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the first entry is 0x574 in and the entries are 0x570 apart (US 0x264 and 0x260).
void func_0014ABD0(Ent_0014ABD0* self)
{
    u32 n;

    func_001AA1F0(self, 0x20);
    self = (Ent_0014ABD0*)((u8*)self + 0x574);
    for (n = 0; n < 4; n++) {
        self->link = (void*)D_00218330;
        D_00218330[0](self, 0x12);
        self = (Ent_0014ABD0*)((u8*)self + 0x570);
    }
}
