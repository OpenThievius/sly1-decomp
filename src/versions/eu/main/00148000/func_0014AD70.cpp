// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: count is at 0x570 and the slots start at 0x574, 0x570 apart (US 0x260, 0x264, 0x260).
struct Slot_14AD70_eu { VFn1_14AD70* vtbl; u8 pad[0x570 - 4]; };
struct Owner_14AD70_eu { u8 pad[0x570]; s32 count; Slot_14AD70_eu slots[1]; };

void func_0014AD70(Owner_14AD70_eu* self)
{
    func_001AA298(self);
    for (s32 i = 0; i < self->count; i++) {
        Slot_14AD70_eu* s = &self->slots[i];
        s->vtbl[2](s);
    }
}
