// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the slots are 12 bytes apart (US 44) and the table ends at +0x18C (US +0x5AC).
struct Slot_001DFE80_eu { s32 key; s32 rest[2]; };

void* func_001DFE80(s32 key)
{
    Slot_001DFE80_eu* p = (Slot_001DFE80_eu*)D_00248748;
    Slot_001DFE80_eu* end = (Slot_001DFE80_eu*)(D_00248748 + 0x18C);
    do {
        if (key != p->key) {
            p++;
        } else {
            return p;
        }
    } while (p < end);
    return 0;
}
