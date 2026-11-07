// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 318/352 (90.3%), checked 2026-11-01
// Still differs: Lays out the object with float constants inlined as literals and u32 for the 0x80000000 arg; only the prologue ordering of li a1,6 / li a2,7 against the float spills differs (10 lines).
// Lays out the eight-part object at D_eu_00263590 from the scaled field at 0x54C, through the func_00161xxx helpers.
extern u8 D_eu_00263590[];
void BeginGifTag(void* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(void* self, s32 a1, s32 a2);
void AddGifRgbaEntry(void* self, u32 a1);
void AddGifXyzfEntry(void* self, s32 a1, s32 a2, s32 a3, s32 a4);
void func_eu_001AE860(u8* a0)
{
    f32 f20 = *(f32*)(a0 + 0x54C) * 54.305084228515625f;
    f32 f21 = 468.61016845703125f - f20;
    BeginGifTag(D_eu_00263590, 6, 7, 0x44441EE);
    AddGifRegisterWrite(D_eu_00263590, 0x47, 0x30000);
    AddGifRegisterWrite(D_eu_00263590, 0x42, 0x44);
    AddGifRgbaEntry(D_eu_00263590, 0x80000000u);
    AddGifXyzfEntry(D_eu_00263590, 0x6C00, 0x7800, 0x0FFFFFF0, 0);
    AddGifXyzfEntry(D_eu_00263590, 0x9400, (s32)((f20 * 0.5462962985038757f + 1920.0f) * 16.0f), 0x0FFFFFF0, 0);
    AddGifXyzfEntry(D_eu_00263590, 0x6C00, (s32)((f21 * 0.5462962985038757f + 1920.0f) * 16.0f), 0x0FFFFFF0, 0);
    AddGifXyzfEntry(D_eu_00263590, 0x9400, 0x8800, 0x0FFFFFF0, 0);
}
