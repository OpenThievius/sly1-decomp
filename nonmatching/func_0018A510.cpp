// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 195/280 (69.6%), checked 2026-11-12
// w25 (2026-11-11, w25-deps): dependence sources enumerated (docs/toolchain/large-functions.md, "Dependence sources enumerated"): the 33rd-reference flush is not reached (12-14 references), a guard of priority 3 would need a call after `guard = 1`, and reload_cse_regs could hide a second 1.0 pseudo (C's constants apart from A's, A and B at priority 5 replay to one tie from retail's groups). A base class holding the fields with a derived constructor setting f50/f60/f54: same code.
// NEAR: order: as func_001D5FA8 (the stores keep the constructor's order in retail and are
//       scheduled out of order here);
//       the record and its guard are a function-local static with an inline constructor
//       (FillMemory, then the fields), at retail's labels through config/us/statics.tsv.
//       Landing it also needs D_002BE490 (0xB0) split at 0x2BE510: the static is 0x80 bytes.
// Retail's sched1 order (from its two %lo stores, barriers in sched2): {f4,f24,f44,f34}, i0,
//       {f8,i28,i48,i68}, guard, {f50,f60,f64,f54}; here `this` has a REG_EQUAL of cfg, so no
//       store depends on another. Not a Load method (a deferred-request callback, one argument).
// See docs/TOOLCHAIN.md, "Open: constructor stores kept in source order": retail is sched2 of an order sched1 does not give here (2026-11-09).
// 2026-11-10: retail's late constants need the early stores to have priority 4 (two dependent links); no plain form gives a store any dependent (sub-records, inline setters, static in an inline accessor ruled out; TOOLCHAIN.md, "What retail's order needs").
#include "common.h"

void* FillMemory(void* p, s32 zero, s32 size);

struct Cfg_18A510 {
    s32 i0; f32 f4; f32 f8; u8 pad1[0x18]; f32 f24; u32 i28; u8 pad2[8]; f32 f34; u8 pad3[0xC]; f32 f44; u32 i48; u8 pad4[4]; f32 f50; f32 f54; u8 pad5[8]; f32 f60; f32 f64; u32 i68; u8 pad6[4]; s32 i70; s32 i74; u8 pad7[8];
    Cfg_18A510() {
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
struct Host_18A510 { u8 pad[0x60]; u8* inner; };
extern u8 D_00275070[];
s32 FindAnimRecord(s32 id);
void DrawAngleSortedRing(void* a, s32 b, void* c, s32 d, s32 e, void* f, void* g);

void DrawGaugeAgentMarkerRing(Host_18A510* self)
{
    u8* inner = self->inner;
    static Cfg_18A510 cfg;
    s32 v = FindAnimRecord(0x15D);
    cfg.i74 = v;
    cfg.i70 = v;
    DrawAngleSortedRing(inner + 0x140, 7, D_00275070, *(s32*)(inner + 0xE20), *(s32*)(inner + 0xE24), &cfg, self);
}
