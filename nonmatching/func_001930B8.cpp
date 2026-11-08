// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 241/312 (77.2%), checked 2026-11-08
// NEAR: order: the first block is exact with the destination pointer declared before the memset;
//       the second differs only in the order its constants are loaded and stored.
#include "common.h"
#include "shapes.h"

struct __attribute__((aligned(16))) Cfg_1930B8 {
    f32 f0; f32 f4; f32 f8; u8 padC[0xC]; f32 f18; u8 pad1C[4]; f32 f20; u8 pad24[0xC]; Quad16 q30; u8 pad40[0xC]; s32 i4c; f32 f50; f32 f54; u8 pad58[8]; Quad16 q60; f32 f70; f32 f74; u8 pad78[8];
};
typedef char check_Cfg_1930B8[sizeof(Cfg_1930B8) == 0x80 ? 1 : -1];

extern u8 D_00248D30[];
extern u8 g_unitZVector[];
extern Cfg_1930B8 D_00604700;
extern Cfg_1930B8 D_00269C10;
void* FillMemory(void* p, s32 zero, s32 size);

void ConstructSwitchedColliderDefaults(s32 a0, s32 a1)
{
    if (a1 == 0xFFFF && a0 != 0) {
        {
            Cfg_1930B8 c;
            Cfg_1930B8* p = &D_00604700;
            FillMemory(&c, 0, 0x80);
            c.q60 = *(Quad16*)D_00248D30;
            *p = c;
        }
        {
            Cfg_1930B8 c;
            Cfg_1930B8* p = &D_00269C10;
            FillMemory(&c, 0, 0x80);
            c.f0 = 1000.0f;
            c.f18 = -1750.0f;
            c.f4 = 1200.0f;
            c.f20 = -0.5f;
            c.q30 = *(Quad16*)g_unitZVector;
            c.i4c = 1;
            c.f50 = 0.5f;
            c.f54 = 2.0f;
            c.f8 = 1.0f;
            c.f70 = 1.0f;
            c.f74 = -1.0f;
            *p = c;
        }
    }
}
