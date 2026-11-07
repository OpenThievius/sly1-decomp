// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 197/280 (70.4%), checked 2026-11-06
// NEAR: order: as func_001D5FA8; the struct's first word gets 1 and a global flag is set too.
#include "common.h"

struct Cfg_1D60B0 {
    s32 i0; f32 f4; f32 f8; u8 pad1[0x18]; f32 f24; u32 i28; u8 pad2[8]; f32 f34; u8 pad3[0xC]; f32 f44; u32 i48; u8 pad4[4]; f32 f50; f32 f54; u8 pad5[8]; f32 f60; f32 f64; u32 i68; u8 pad6[4]; s32 i70; s32 i74;
};
struct Host_1D60B0 { u8 pad[0x60]; u8* inner; };
extern s32 D_00275134;
extern Cfg_1D60B0 D_006055D0;
extern u8 D_00275070[];
void FillMemory(void* p, s32 zero, s32 size);
s32 FindAnimRecord(s32 id);
void DrawAngleSortedRing(void* a, s32 b, void* c, s32 d, s32 e, void* f, void* g);

void DrawPlayerMarkerRing2(Host_1D60B0* self)
{
    u8* inner = self->inner;
    if (D_00275134 == 0) {
        FillMemory(&D_006055D0, 0, 0x80);
        D_006055D0.f4 = 5.0f;
        D_006055D0.f24 = 100.0f;
        D_006055D0.f44 = 50.0f;
        D_006055D0.f34 = 0.5f;
        D_006055D0.i0 = 1;
        D_006055D0.f8 = 0.5f;
        D_006055D0.i28 = 0x80FFFFFF;
        D_006055D0.i48 = 0x80FFFFFF;
        D_006055D0.f50 = 75.0f;
        D_006055D0.i68 = 0x80FFFFFF;
        D_00275134 = 1;
        D_006055D0.f60 = 1.0f;
        D_006055D0.f64 = -100.0f;
        D_006055D0.f54 = 1.0f;
    }
    s32 v = FindAnimRecord(0x15D);
    D_006055D0.i70 = v;
    D_006055D0.i74 = v;
    DrawAngleSortedRing(inner + 0x140, 7, D_00275070, *(s32*)(inner + 0x26A8), *(s32*)(inner + 0x26AC), &D_006055D0, self);
}
