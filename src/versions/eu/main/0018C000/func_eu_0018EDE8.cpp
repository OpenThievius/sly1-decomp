// SPDX-License-Identifier: AGPL-3.0-or-later
// Copies the field at 0x18 to 0x24 and clears the fields at 0x1C, 0x20, 0x28 and 0x2C.
struct Obj_eu_18EDE8 { u8 pad[0x18]; s32 f18; s32 f1C; s32 f20; s32 f24; s32 f28; s32 f2C; };
void func_eu_0018EDE8(Obj_eu_18EDE8* a0)
{
    s32 v = a0->f18;
    a0->f24 = v;
    a0->f28 = 0;
    a0->f20 = 0;
    a0->f1C = 0;
    a0->f2C = 0;
}
