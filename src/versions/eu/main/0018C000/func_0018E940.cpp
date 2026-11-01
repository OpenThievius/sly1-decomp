// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: no 0x6000 allocation or third sub-object; fields at 0xA0/0xA4, channel 0x10 instead of 8, 0x20000 buffer, returns nothing.
struct Obj_18E940_eu {
    s32 f00;
    s32 f04;
    s32 f08[10];
    u8 sub30[0x20];
    u8 sub50[0x50];
    s32 fA0;
    s32 fA4;
};

void func_0018E940(struct Obj_18E940_eu* self)
{
    func_0011D6A8(0xFFFFFFFF);
    func_001C08B0(D_00275710, 0, 0);
    func_0011E010();
    while (func_0011CE30() != 0) {
    }
    func_0011E110(1);
    func_0011E1F8(0);
    self->fA0 = func_0011D4B8(2);
    self->fA4 = func_0011D4B8(0x10);
    func_0011D480(2, 0x400);
    func_0011D480(0x10, 0x200);
    self->f00 = 1;
    self->f04 = -1;
    func_0013C988(self->sub30, 0x28, self->f08);
    func_0013C988(self->sub50, 0x20000, D_002CBB40);
}
