// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the two fields sit at 0xA0 and 0xA4 (not 0x8C and 0x90), and the second call passes 16 (not 8).
struct Obj_18EAA0_eu {
    s32 f00;
    u8 pad04[0x9C];
    s32 fA0;
    s32 fA4;
};

void func_0018EAA0(struct Obj_18EAA0_eu* self)
{
    self->f00 = 0;
    func_0011E498();
    func_0011D480(2, self->fA0);
    func_0011D480(16, self->fA4);
    func_001C0950(D_00275710);
    func_0011D6D8(0xFFFFFFFF);
}
