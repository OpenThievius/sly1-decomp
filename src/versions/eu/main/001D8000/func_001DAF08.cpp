// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the count fields of the two counters are at 0x58C (US 0x27C).
struct Counter_1DAF08_eu { u8 pad[0x58C]; s32 count; };

void func_001DAF08(void* self, s32 code, Rec_1DAF08* rec)
{
    func_00192230(self, code, rec);
    if (code == 0xE && rec->kind == 0x426) {
        Counter_1DAF08_eu* a = (Counter_1DAF08_eu*)D_00272430;
        s32 lim = D_002751D4;
        if (a->count < lim) {
            Counter_1DAF08_eu* b = (Counter_1DAF08_eu*)D_002726B0;
            if (b->count < lim) {
                if (rec->link->owner == self) {
                    a->count = a->count + 1;
                } else {
                    b->count = b->count + 1;
                }
            }
        }
    }
}
