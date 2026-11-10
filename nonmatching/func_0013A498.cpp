// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 203/384 (52.9%), checked 2026-11-10
// NEAR: retail's size since 2026-11-10: `kept = 0` written just before the loop, after the last
// asm, so combine folds jump.c's copied entry test (slt kept,count / beqz, kept being CSE's
// canonical zero) into retail's blez; written earlier, a volatile asm lies between and combine
// refuses (can_combine_p). The loop body, the helper calls and the stack layout are retail's.
// Why the rest differs (2026-11-10, w13): retail's lqc2/sqc2/qmtc2 are not scheduling barriers.
// Its `sw t2,0(sp)` (mode's spill, emitted at the parameter copy) sits after the four matrix
// lqc2s, its `move v0,a0` before the sqc2 of $vf26, and the else arm computes both addresses
// before both sqc2s; LoadVf/MoveToVf have no outputs, so stmt.c makes them volatile, and a
// volatile asm is a full barrier in sched1 and sched2 (haifa-sched.c). Retail's loads and stores
// were the compiler's own moves (vcallms and cfc2.i stay barriers: nothing crosses them). Scratch
// only (build/swarm/w13-13A498/x.cpp): file-scope `register u128 vf25 asm("vf25")` variables
// for $vf21..$vf31 with plain assignments give retail's loop body, j in s8, the iterators, the
// filled delay slot, leaving the prologue order and kept (a2 for a0) with the test back to slt
// (kept=0 then precedes the vcallms barrier). Register variables are pins (AGENTS.md): a user
// decision, so this stays a near miss with the project's helpers.
// w15 (2026-11-10): no source order of the existing helpers can match. Retail's qmtc2 is the first
// insn after `addiu sp`, ahead of the saves, and reload's entry spills of ra and mode (`sw t3,4(sp)`,
// `sw t2,0(sp)`) follow lqc2s; a volatile asm (any asm without outputs) keeps every earlier insn
// before it (haifa-sched.c), and the parameter copies are always earlier. The VU0 registers are
// already retail's; the GPRs and order differ only through the barriers. The register-variable
// scratch (w13 x.cpp) is NOT exact either: 43 lines differ (prologue order, slt entry test, kept in
// a2 for a0). Retail's kept is set before the vcallms yet its test is the folded blez, which no
// volatile vcallms between allows (combine's can_combine_p): an open point under any interface
// (docs/toolchain/vu0-helpers.md).
// w16 (2026-11-10): no new helper fits the rules: only this function (PAL func_0013A798) touches
// $vf16..$vf31 or vcallms 0x10, the loads have no natural output (so any asm is volatile), and a
// non-volatile sqc2 with a memory output gets 66 differing lines (from 73), prologue unchanged.
#include "common.h"
#include "vu0.h"
#include "placed_object.h"

f32 WrapAngle(f32 x);
extern f32 g_gameTime;

s32 func_0013A498(const f32* m, u128 scaleBits, Vec02* pos, Vec02* extra, Vec02* items, s32 count, s32 mode, void* ra, void* rb)
{
    Vu0::MoveToVf<27>(scaleBits);
    s32 j = -1;
    f32 now = g_gameTime;
    Vu0::LoadVf<25>(rb);
    Vu0::LoadVf<28>(m + 12);
    Vu0::LoadVf<31>(m);
    Vu0::LoadVf<30>(m + 4);
    Vu0::LoadVf<29>(m + 8);
    Vu0::LoadVf<26>(ra);
    Vu0::LoadVf<24>(extra);
    Vu0::LoadVf<23>(pos);
    Vu0::CallMs<0x10>();
    s32 kept = 0;
    for (s32 i = 0; i < count; i++) {
        if (extra[i].w <= now) {
            kept++;
            Vu0::ReadViWait<0>();
        } else {
            j++;
            items[j] = items[i];
            if (mode == 2) {
                items[j].w = WrapAngle(items[i].w + items[i].z * Vu0::ToFloatMoved(scaleBits));
            }
            Vu0::ReadViWait<0>();
            Vu0::StoreVf<22>(&extra[j]);
            Vu0::StoreVf<21>(&pos[j]);
        }
        Vu0::LoadVf<24>(&extra[i + 1]);
        Vu0::LoadVf<23>(&pos[i + 1]);
        Vu0::CallMs<0x10>();
    }
    Vu0::StoreVf<26>(ra);
    Vu0::StoreVf<25>(rb);
    return kept;
}
