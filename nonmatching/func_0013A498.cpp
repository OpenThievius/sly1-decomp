// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 392/384, checked 2026-11-08
// NEAR: the loop body, the helper calls (qmtc2, lqc2 x9, vcallms 0x10 twice, cfc2.i, sqc2 x4) and the stack layout are retail's; the scale is a u128 parameter (retail passes the float in a GPR with a 128-bit por) read with ToFloatMoved. Left: register allocation. Retail keeps the kept count in a0 (saved around WrapAngle's call) and the position/extra pointers in s7/s6, the index in s8; ours puts the kept count in a callee-saved register and one pointer in a caller-saved one, and the prologue order differs (retail's qmtc2 first, j = -1 before the saves).
// Still differs (2026-11-08, vcallms worker): declaring j and kept before the loads, after them, or one each way moves the allocation but never gives retail's (kept in a2 also folds the loop test into slt).
// Why (2026-11-08, tools/regalloc.py): the s0/s1 swap is r184 (i's offset, 12 refs over 38 insns,
// priority 0.947) placed before r141 (j's, 6 over 13, 0.923); r141 goes first with a life of 12 or
// 7 refs. Reading items[j] for the wrap instead of items[i] (all three ways) adds 6 differences.
#include "common.h"
#include "vu0.h"
#include "placed_object.h"

f32 WrapAngle(f32 x);
extern f32 g_gameTime;

s32 func_0013A498(const f32* m, u128 scaleBits, Vec02* pos, Vec02* extra, Vec02* items, s32 count, s32 mode, void* ra, void* rb)
{
    Vu0::MoveToVf<27>(scaleBits);
    s32 j = -1;
    s32 kept = 0;
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
