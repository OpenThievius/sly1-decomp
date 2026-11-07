// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 197/280 (70.4%), checked 2026-11-07
// NEAR: order: frame, calls and constants are retail's; retail keeps the constant stores in source
//       order and loads each constant just before its store, this form loads them early and
//       reorders the stores.
#include "common.h"

struct Cfg_18A510 {
    s32 i0; f32 f4; f32 f8; u8 pad1[0x18]; f32 f24; u32 i28; u8 pad2[8]; f32 f34; u8 pad3[0xC]; f32 f44; u32 i48; u8 pad4[4]; f32 f50; f32 f54; u8 pad5[8]; f32 f60; f32 f64; u32 i68; u8 pad6[4]; s32 i70; s32 i74;
};
struct Host_18A510 { u8 pad[0x60]; u8* inner; };
extern s32 D_002649A8;
extern Cfg_18A510 D_002BE490;
extern u8 D_00275070[];
void FillMemory(void* p, s32 zero, s32 size);
s32 FindAnimRecord(s32 id);
void DrawAngleSortedRing(void* a, s32 b, void* c, s32 d, s32 e, void* f, void* g);

void DrawGaugeAgentMarkerRing(Host_18A510* self)
{
    u8* inner = self->inner;
    if (D_002649A8 == 0) {
        FillMemory(&D_002BE490, 0, 0x80);
        D_002BE490.f4 = 5.0f;
        D_002BE490.f24 = 100.0f;
        D_002BE490.f44 = 50.0f;
        D_002BE490.f34 = 0.5f;
        D_002BE490.i0 = 1;
        D_002BE490.f8 = 0.5f;
        D_002BE490.i28 = 0x80FFFFFF;
        D_002BE490.i48 = 0x80FFFFFF;
        D_002BE490.f50 = 75.0f;
        D_002BE490.i68 = 0x80FFFFFF;
        D_002649A8 = 1;
        D_002BE490.f60 = 1.0f;
        D_002BE490.f64 = -100.0f;
        D_002BE490.f54 = 1.0f;
    }
    s32 v = FindAnimRecord(0x15D);
    D_002BE490.i70 = v;
    D_002BE490.i74 = v;
    DrawAngleSortedRing(inner + 0x140, 7, D_00275070, *(s32*)(inner + 0xE20), *(s32*)(inner + 0xE24), &D_002BE490, self);
}
