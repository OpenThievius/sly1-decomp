// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: PalItemEntry is the column and its entries in one, as the US layout's two types differ in size; the first entry is 0x574 in and the entries are 0x570 apart (US 0x264 and 0x260).
struct PalItemEntry {
    void* link;
    u8 pad0[0x570 - 4];
};
void InitScreenElement(PalItemEntry* self, s32 index);
void InitItemColumn(PalItemEntry* self)
{
    u32 n;

    InitScreenElement(self, 0x20);
    self = (PalItemEntry*)((u8*)self + 0x574);
    for (n = 0; n < 4; n++) {
        self->link = (void*)&D_00218330;
        D_00218330.m00((ScreenElement*)self, 0x12);
        self = (PalItemEntry*)((u8*)self + 0x570);
    }
}
