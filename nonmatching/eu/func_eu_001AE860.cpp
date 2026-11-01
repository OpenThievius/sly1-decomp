// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001AE860.cpp func_eu_001AE860 --unit src/main/001AC000.cpp
// Still differs: Lays out the object with float constants inlined as literals and u32 for the 0x80000000 arg; only the prologue ordering of li a1,6 / li a2,7 against the float spills differs (10 lines).
// Lays out the eight-part object at D_eu_00263590 from the scaled field at 0x54C, through the func_00161xxx helpers.
extern u8 D_eu_00263590[];
void func_001613C0(void* self, s32 a1, s32 a2, s32 a3);
void func_00161708(void* self, s32 a1, s32 a2);
void func_00161458(void* self, u32 a1);
void func_001615F0(void* self, s32 a1, s32 a2, s32 a3, s32 a4);
void func_eu_001AE860(u8* a0)
{
    f32 f20 = *(f32*)(a0 + 0x54C) * 54.305084228515625f;
    f32 f21 = 468.61016845703125f - f20;
    func_001613C0(D_eu_00263590, 6, 7, 0x44441EE);
    func_00161708(D_eu_00263590, 0x47, 0x30000);
    func_00161708(D_eu_00263590, 0x42, 0x44);
    func_00161458(D_eu_00263590, 0x80000000u);
    func_001615F0(D_eu_00263590, 0x6C00, 0x7800, 0x0FFFFFF0, 0);
    func_001615F0(D_eu_00263590, 0x9400, (s32)((f20 * 0.5462962985038757f + 1920.0f) * 16.0f), 0x0FFFFFF0, 0);
    func_001615F0(D_eu_00263590, 0x6C00, (s32)((f21 * 0.5462962985038757f + 1920.0f) * 16.0f), 0x0FFFFFF0, 0);
    func_001615F0(D_eu_00263590, 0x9400, 0x8800, 0x0FFFFFF0, 0);
}
