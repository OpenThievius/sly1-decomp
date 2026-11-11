// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 204/260 (78.5%), checked 2026-11-11
// NEAR: order: frame, calls, constants and addresses are retail's; the constants get other
//       registers and the stores another order. Retail keeps the stores in the constructor's
//       order and loads 75.0 only after -100.0's last store (into its f0), as if the stores
//       depended on each other; here they are independent and scheduled out of order (the
//       explicit-guard form with D_ globals gives the same). As a probe only, the stores made
//       volatile come out in retail's order with 75.0 loaded late (17 words differ, against 21):
//       retail's stores behave as dependent on each other, which plain stores through one
//       base register never are; what original form makes them so is still open. The record
//       and its guard are a function-local static with an inline constructor (FillMemory, then
//       the fields), at retail's labels through config/us/statics.tsv; it lands only with
//       func_001D60B0 and func_001D61C8 in the same form, since the three guards close the
//       file's .data in function order (docs/AGENT_WORKFLOW.md, "A function-local static").
// Tried (order-class pass): the constructor with a member-initialiser list (65 words), stores through a local pointer (21, the same), the pointer FillMemory returns (64).
// See docs/TOOLCHAIN.md, "Open: constructor stores kept in source order": retail is sched2 of an order sched1 does not give here (2026-11-08).
// 2026-11-10: retail's late constants need the early stores to have priority 4 (two dependent links); no plain form gives a store any dependent (sub-records, inline setters, static in an inline accessor ruled out; TOOLCHAIN.md, "What retail's order needs").
#include "common.h"

void* FillMemory(void* p, s32 zero, s32 size);
s32 FindAnimRecord(s32 id);
void DrawAngleSortedRing(void* a, s32 b, void* c, s32 d, s32 e, void* f, void* g);
extern u8 D_00275070[];
struct Cfg_1D5FA8 {
    u8 pad0[4]; f32 f4; f32 f8; u8 pad1[0x1C]; s32 i28; u8 pad2[8]; f32 f34; u8 pad3[8]; f32 f40; f32 f44; u32 i48; u8 pad4[4]; f32 f50; f32 f54; u8 pad5[8]; f32 f60; f32 f64; u32 i68; u8 pad6[4]; s32 i70; s32 i74; u8 pad7[8];
    Cfg_1D5FA8() {
        FillMemory(this, 0, 0x80);
        f44 = -100.0f; f4 = 5.0f; f40 = 0.5f; f8 = 1.0f; i28 = 0; f34 = 1.0f;
        i48 = 0xFFFFFFFF; i68 = 0xFFFFFFFF; f50 = 75.0f; f60 = 1.0f; f54 = 1.0f;
    }
};
struct Host_1D5FA8 { u8 pad[0x60]; u8* inner; };
void DrawPlayerMarkerRing1(Host_1D5FA8* self)
{
    u8* inner = self->inner;
    static Cfg_1D5FA8 cfg;
    cfg.i70 = 0;
    cfg.i74 = FindAnimRecord(0x15C);
    DrawAngleSortedRing(inner + 0x140, 7, D_00275070, *(s32*)(inner + 0x26A8), *(s32*)(inner + 0x26AC), &cfg, self);
}
