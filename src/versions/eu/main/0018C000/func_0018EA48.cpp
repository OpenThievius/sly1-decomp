// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: sets a second field to -1, blocks at 0x30/0x50 and func_eu_0018EDE8 at 0x70
struct Obj_18EA48_eu { s32 flag; s32 f4; u8 pad0[0x30 - 8]; };
void func_eu_0018EDE8(void* self);
void func_0018EA48(Obj_18EA48_eu* self)
{
    if (self->flag != 0) {
        func_0011E460();
        self->flag = 1;
        self->f4 = -1;
        func_0013C9B0((u8*)self + 0x30);
        func_0013C9B0((u8*)self + 0x50);
        func_eu_0018EDE8((u8*)self + 0x70);
    }
}
