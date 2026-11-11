// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 507/516 (98.3%), checked 2026-11-11
// NEAR: size, control flow, every register but v0/v1 in one block, and the light loop are retail's (127 of 129 instructions, tools/regdiff.py: code). Left: the group's field loads come out lw 4, lhu 14 (count, then fE) where retail has lhu 14, lw 4, and the case-0 test `beqz a0` has the join's `addiu t7` in its delay slot where retail has a nop.
// Fixed (2026-11-10, w11): the prev test was `prev && prev->count > 0` (a second blez: retail tests prev only, the loop's own entry test does the rest); the bit starts at 1 << count and shifts at the top of the body (retail's sllv before the loop, sra in bnezl's slot); grp is set in the else arm (its address after the i == count test); count and kind are read into locals before the vi moves (retail loads all three fields before ctc2.i).
// Why (2026-11-10, w11): both remaining differences say the original's vi3/vi4/vi2/vnop block was ONE asm statement with an output, not volatile, not the four volatile one-instruction helpers. sched1: with separate asms, count's load has three dependents (its own ctc2.ni, the ctc2.i barrier, the jump) against fE's two, and rank_for_schedule puts it first whatever the source order; only an asm that consumes fE and count together ties them, and LUID then gives retail's fE, count, kind. reorg: redundant_insn refuses to see the join's `t7 = i + 1` as redundant across any volatile insn (resource_conflicts_p: either side volatil), so the default arm's `b` takes a copy that the case-0 beqz then steals; retail's empty slots need no volatile insn between the bnez (whose slot holds the same addiu) and that b. Proved in build/swarm/w11-185150/ (h4.cpp: one non-volatile asm `ctc2.i %1,$vi3; ctc2.ni %2,$vi4; cfc2.ni %0,$vi2; vnop` with mask as output and switch (grp->kind)): the loads, the delay slots and all of block 7 then match; left is only s5/s6 (the light table address, r150, 3 refs over a doubled 134-insn life, against outCount, r121, 2 refs over 90), which global-alloc ties at 0.022 and needs three more loop insns (as the four separate asms give) or one fewer for r121 outside the loop. A four-instruction asm used once is not a project helper (AGENTS.md), so this waits for a decision on such an interface helper.
// w16 (2026-11-10): the block does not recur: the only $vi3/$vi4 writes in retail are this function's (PAL func_001857B0), so no shared helper fits AGENTS.md (docs/toolchain/vu0-helpers.md).
#include "common.h"
#include "vu0.h"
#include "placed_object.h"

struct LightGroup { void** lights; s32 count; s32 flags; u16 kind; s16 fE; };
extern s32 g_lightGroupCount;
extern LightGroup g_lightGroups[16];

struct LightMode { u8 pad[0x2D4]; s32 mode; };

s32 func_00185150(u8* scene, const Vec02* centre, u32 skipMask, s32 maxLights, s32* flagged, s32* outCount, LightMode** out, f32 radius)
{
    u32 keepOut = ~skipMask;
    s32 num = 0;
    s32 flaggedCount = 0;
    LightGroup* prev = 0;
    u32 mask;
    s32 strongest = *(f32*)(scene + 0x1D6C) != 0.0f;
    Vec02 sphere = *centre;
    sphere.w = radius;
    Vu0::LoadVf<31>(&sphere);
    for (s32 i = 0; i < g_lightGroupCount + 1; i++) {
        LightGroup* grp;
        if (i == g_lightGroupCount) {
            mask = Vu0::ReadViWait<2>();
        } else {
            grp = &g_lightGroups[i];
            if (grp->flags & keepOut) {
                continue;
            }
            u16 fE = grp->fE;
            s32 count = grp->count;
            u16 kind = grp->kind;
            Vu0::MoveToViWait<3>(fE);
            Vu0::MoveToVi<4>(count);
            mask = Vu0::ReadVi<2>();
            Vu0::VuNop();
            switch (kind) {
            case 0:
                Vu0::MoveToVi<2>(0xFFFF);
                break;
            case 1:
                Vu0::CallMs<0x60>();
                break;
            case 2:
                Vu0::CallMs<0x168>();
                break;
            }
        }
        if (prev) {
            s32 bit = 1 << prev->count;
            for (s32 k = 0; k < prev->count; k++) {
                bit >>= 1;
                if (((s32)mask & bit) && num < maxLights) {
                    LightMode* l = (LightMode*)prev->lights[k];
                    out[num++] = l;
                    if (strongest < l->mode) {
                        strongest = l->mode;
                    }
                    flaggedCount += prev->flags & 1;
                }
            }
        }
        prev = grp;
    }
    *outCount = num;
    if (flagged) {
        *flagged = flaggedCount;
    }
    return strongest;
}
