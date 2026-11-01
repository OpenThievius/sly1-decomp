// SPDX-License-Identifier: AGPL-3.0-or-later
// Calls func_001AA8F0 (PAL 001AB6E8) on self unless its state at +0x560 is 3 and its word at +0x570 is set.
struct Obj_eu_001AE0C0 {
    u8 pad000[0x560];
    s32 state;
    u8 pad564[0xC];
    s32 flag;
};

void func_001AA8F0(void* self);

void func_eu_001AE0C0(Obj_eu_001AE0C0* self)
{
    if (self->state == 3) {
        if (self->flag != 0) {
            return;
        }
    }
    func_001AA8F0(self);
}
