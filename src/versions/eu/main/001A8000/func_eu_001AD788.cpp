// SPDX-License-Identifier: AGPL-3.0-or-later
// Calls the state update unless the state at 0x560 is 3 and the flag at 0x570 is set.
struct Obj_eu_1AD788 {
    u8 pad[0x560];
    s32 state;
    u8 pad564[0xC];
    s32 flag;
};

void func_001AA8F0(void* self);

void func_eu_001AD788(Obj_eu_1AD788* self)
{
    if (self->state != 3 || self->flag == 0) {
        func_001AA8F0(self);
    }
}
