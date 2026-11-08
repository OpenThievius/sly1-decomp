// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 195/280 (69.6%), checked 2026-11-08
// NEAR: order: as func_001D5FA8 (the stores keep the constructor's order in retail and are
//       scheduled out of order here);
//       the record and its guard are a function-local static with an inline constructor
//       (FillMemory, then the fields), at retail's labels through config/us/statics.tsv.
//       Lands only with func_001D5FA8 and func_001D61C8 in the same form (the three guards
//       close the file's .data in function order).
#include "common.h"

void* FillMemory(void* p, s32 zero, s32 size);

struct Cfg_1D60B0 {
    s32 i0; f32 f4; f32 f8; u8 pad1[0x18]; f32 f24; u32 i28; u8 pad2[8]; f32 f34; u8 pad3[0xC]; f32 f44; u32 i48; u8 pad4[4]; f32 f50; f32 f54; u8 pad5[8]; f32 f60; f32 f64; u32 i68; u8 pad6[4]; s32 i70; s32 i74; u8 pad7[8];
    Cfg_1D60B0() {
        FillMemory(this, 0, 0x80);
        f4 = 5.0f;
        f24 = 100.0f;
        f44 = 50.0f;
        f34 = 0.5f;
        i0 = 1;
        f8 = 0.5f;
        i28 = 0x80FFFFFF;
        i48 = 0x80FFFFFF;
        f50 = 75.0f;
        i68 = 0x80FFFFFF;
        f60 = 1.0f;
        f64 = -100.0f;
        f54 = 1.0f;
    }
};
struct Host_1D60B0 { u8 pad[0x60]; u8* inner; };
extern u8 D_00275070[];
s32 FindAnimRecord(s32 id);
void DrawAngleSortedRing(void* a, s32 b, void* c, s32 d, s32 e, void* f, void* g);

void DrawPlayerMarkerRing2(Host_1D60B0* self)
{
    u8* inner = self->inner;
    static Cfg_1D60B0 cfg;
    s32 v = FindAnimRecord(0x15D);
    cfg.i74 = v;
    cfg.i70 = v;
    DrawAngleSortedRing(inner + 0x140, 7, D_00275070, *(s32*)(inner + 0x26A8), *(s32*)(inner + 0x26AC), &cfg, self);
}
