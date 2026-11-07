// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 203/260 (78.1%), checked 2026-11-07
// NEAR: order: frame, calls and constants are retail's; the float constants get other registers
//       (retail: -100.0 in f0, 1.0 in f1, reused for four stores), so the stores interleave
//       differently.
#include "common.h"

struct Cfg_1D5FA8 {
    u8 pad0[4]; f32 f4; f32 f8; u8 pad1[0x1C]; s32 i28; u8 pad2[8]; f32 f34; u8 pad3[8]; f32 f40; f32 f44; u32 i48; u8 pad4[4]; f32 f50; f32 f54; u8 pad5[8]; f32 f60; f32 f64; u32 i68; u8 pad6[4]; s32 i70; s32 i74;
};
struct Host_1D5FA8 { u8 pad[0x60]; u8* inner; };
extern s32 D_00275130;
extern Cfg_1D5FA8 D_00605550;
extern u8 D_00275070[];
void FillMemory(void* p, s32 zero, s32 size);
s32 FindAnimRecord(s32 id);
void DrawAngleSortedRing(void* a, s32 b, void* c, s32 d, s32 e, void* f, void* g);

void DrawPlayerMarkerRing1(Host_1D5FA8* self)
{
    u8* inner = self->inner;
    if (D_00275130 == 0) {
        FillMemory(&D_00605550, 0, 0x80);
        D_00605550.f44 = -100.0f;
        D_00605550.f4 = 5.0f;
        D_00605550.f40 = 0.5f;
        D_00605550.f8 = 1.0f;
        D_00605550.i28 = 0;
        D_00605550.f34 = 1.0f;
        D_00605550.i48 = 0xFFFFFFFF;
        D_00605550.i68 = 0xFFFFFFFF;
        D_00275130 = 1;
        D_00605550.f50 = 75.0f;
        D_00605550.f60 = 1.0f;
        D_00605550.f54 = 1.0f;
    }
    D_00605550.i70 = 0;
    D_00605550.i74 = FindAnimRecord(0x15C);
    DrawAngleSortedRing(inner + 0x140, 7, D_00275070, *(s32*)(inner + 0x26A8), *(s32*)(inner + 0x26AC), &D_00605550, self);
}
