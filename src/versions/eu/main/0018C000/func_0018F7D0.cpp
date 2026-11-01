// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the wait word sits at 0x148 (not 0x134), so the struct has its own layout.
struct Obj_18F7D0_eu {
    s32 f00;
    u8 pad04[0x08];
    s32 f0C;
    u8 pad10[0x138];
    s32 f148;
};

void func_0018F7D0(Obj_18F7D0_eu* self)
{
    u8* base = (u8*)self;
    s32 mask;

    self->f0C = 0;
    func_0018EA48((Obj_18F7D0*)(base + 0x80));
    func_0018EAA0((Obj_18F7D0*)(base + 0x80));
    func_0020B0C0((Obj_18F7D0*)(base + 0x10));
    (void)func_0020B048((Obj_18F7D0*)(base + 0x10));
    if (self->f148 != 0) {
        do {
        } while (*(volatile s32*)&self->f148 != 0);
    }
    D_002626CC = 3;
    func_001B3450();
    if ((u32)self->f00 >= 16) {
        mask = 0;
    } else {
        mask = 1 << self->f00;
    }
    *(s32*)((u8*)D_002623C0 + 0x19F8) |= mask;
}
