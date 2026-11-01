// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the bank's fields are 0x28C later (state at 0x5B4, count at 0x5E0, entries at 0x5E8).
struct SlotBank_135E78_eu {
    u8 pad0[0x5B4];
    s32 state;
    u8 pad1[0x4];
    u8 blockA[0x10];
    u8 blockB[0x10];
    s32 countA;
    s32 count;
    u8 pad2[0x4];
    SlotEntry_135E78 entries[1];
};

void func_00135E78(SlotBank_135E78_eu* self, s32 state, s32 flag)
{
    if (state == self->state) return;
    s32 i = 0;
    u8* blockA = self->blockA;
    if (self->count > 0) {
        SlotEntry_135E78* e = self->entries;
        do {
            if (flag != 0) {
                func_0019EBE8(e->handle);
                func_001F5C0C(self->blockB, 0, 16);
            } else {
                func_001A1DF0(e->handle, 2);
            }
            i++;
            e++;
        } while (i < self->count);
    }
    self->count = 0;
    self->countA = 0;
    func_001F5C0C(blockA, 0, 16);
    self->state = state;
}
