// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL picks an id from a word table and resolves it with a PAL-only function instead of indexing 32-byte slots.
extern s32 D_eu_0024AFD8[];
Slot_0016D928* func_eu_001DE018(s32 id);

void func_0016D928(Self_0016D928* self)
{
    s32 r;
    s32* tbl;

    if (self->f5C0 == 0) {
        return;
    }
    if (func_001BE980() != 0) {
        return;
    }
    r = func_001EAA70(0, 0x64);
    if (r >= 0x14) {
        return;
    }
    tbl = D_eu_0024AFD8;
    r = func_001EAA70(0, 6);
    func_001BE728(func_eu_001DE018(tbl[r]));
    self->f5CC = 1;
}
