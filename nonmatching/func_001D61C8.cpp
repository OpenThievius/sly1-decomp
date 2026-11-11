// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 220/276 (79.7%), checked 2026-11-11
// w25 (2026-11-11, w25-deps): dependence sources enumerated (docs/toolchain/large-functions.md, "Dependence sources enumerated"): the 33rd-reference flush is not reached (12-14 references), a guard of priority 3 would need a call after `guard = 1`, and reload_cse_regs could hide a second 1.0 pseudo (C's constants apart from A's, A and B at priority 5 replay to one tie from retail's groups). A base class holding the fields with a derived constructor setting f50/f60/f54: same code.
// NEAR: order: as func_001D5FA8; it passes a 12-byte stack struct as the pointer argument;
//       the record and its guard are a function-local static with an inline constructor
//       (FillMemory, then the fields), at retail's labels through config/us/statics.tsv.
//       Lands only with func_001D5FA8 and func_001D60B0 in the same form (the three guards
//       close the file's .data in function order).
// See docs/TOOLCHAIN.md, "Open: constructor stores kept in source order": retail is sched2 of an order sched1 does not give here (2026-11-08).
// Probe 2026-11-09 (not plain C; explicit guard written between i68 and f50, record base hidden): guard place, 25.0 late into f0
//       and the first loads come out as retail (18 words differ); the group before the guard stays a weight sort (i68 first).
// 2026-11-10: retail's late constants need the early stores to have priority 4 (two dependent links); no plain form gives a store any dependent (sub-records, inline setters, static in an inline accessor ruled out; TOOLCHAIN.md, "What retail's order needs").
#include "common.h"

void* FillMemory(void* p, s32 zero, s32 size);

struct Cfg_1D61C8 {
    u8 pad0[4]; f32 f4; f32 f8; u8 pad1[0x1C]; s32 i28; u8 pad2[8]; f32 f34; u8 pad3[8]; f32 f40; f32 f44; u32 i48; u8 pad4[4]; f32 f50; f32 f54; u8 pad5[8]; f32 f60; f32 f64; u32 i68; u8 pad6[4]; s32 i70; s32 i74; u8 pad7[8];
    Cfg_1D61C8() {
        FillMemory(this, 0, 0x80);
        f44 = -100.0f;
        f4 = 5.0f;
        f40 = 0.5f;
        f8 = 1.0f;
        i28 = 0;
        f34 = 1.0f;
        i48 = 0xFFFFFFFF;
        i68 = 0xFFFFFFFF;
        f50 = 25.0f;
        f60 = 1.0f;
        f54 = 1.0f;
    }
};
struct Host_1D61C8 { u8 pad[0x60]; u8* inner; };
struct Args_1D61C8 { s32 pad; f32 f4; u8* inner; };
extern u8 D_002750A8[];
s32 FindAnimRecord(s32 id);
void DrawAngleSortedRing(void* a, s32 b, void* c, s32 d, void* e, void* f, void* g);

void DrawPlayerMarkerRing3(Host_1D61C8* self)
{
    u8* inner = self->inner;
    static Cfg_1D61C8 cfg;
    Args_1D61C8 args;
    cfg.i70 = 0;
    cfg.i74 = FindAnimRecord(0x15C);
    args.f4 = 60.0f;
    args.inner = inner;
    DrawAngleSortedRing(inner + 0x140, 0x11, D_002750A8, 1, &args, &cfg, self);
}
