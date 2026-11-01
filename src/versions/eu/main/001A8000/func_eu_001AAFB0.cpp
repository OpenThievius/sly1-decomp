// SPDX-License-Identifier: AGPL-3.0-or-later
// Sets the shared value at D_eu_0026358C into field 4, 1.0 into the float at 0x51C, a constant word into 0x518 and clears the short at 8.
extern s32 D_eu_0026358C;
struct Obj_eu_1AAFB0 { u8 pad[0x518]; s32 f518; f32 f51C; };
void func_eu_001AAFB0(u8* a0)
{
    s32 v = D_eu_0026358C;
    s32 c = (s32)0xFF808080;
    *(s32*)(a0 + 0x4) = v;
    ((Obj_eu_1AAFB0*)a0)->f51C = 1.0f;
    ((Obj_eu_1AAFB0*)a0)->f518 = c;
    *(s16*)(a0 + 0x8) = 0;
}
