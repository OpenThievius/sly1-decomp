// SPDX-License-Identifier: AGPL-3.0-or-later
// Sets up an object's fields from four arguments, points its vtable at D_eu_0024CA50, runs func_eu_0015DDA0 and returns the object.
extern u8 D_eu_0024CA50[];
void func_eu_0015DDA0(void* self);
void* func_eu_0015DC58(void* self, s32 a1, s32 a2, s32 a3)
{
    *(s32*)((u8*)self + 0x0) = 0;
    *(void**)((u8*)self + 0x64) = D_eu_0024CA50;
    *(s32*)((u8*)self + 0x4) = a1;
    *(s32*)((u8*)self + 0x10) = a2;
    *(s32*)((u8*)self + 0xB0) = (s32)0xFF808080;
    *(s32*)((u8*)self + 0xAC) = (s32)0xFF808080;
    *(s32*)((u8*)self + 0xA8) = (s32)0xFF808080;
    *(s32*)((u8*)self + 0xA4) = (s32)0xFF808080;
    *(s32*)((u8*)self + 0xB4) = a3;
    func_eu_0015DDA0(self);
    return self;
}
