// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 576/580 (99.3%), checked 2026-11-11
#include "common.h"
// NEAR (w4-1549C8): 2 lines: only the f00 and f20 stores swap (ours f20, f08, f00; retail f00, f08, f20); every register now matches. Mechanism: the 200 is a variable set before the guards and used once in the B block, so local-alloc's update_equiv_regs moves its `li` to just before the store and the widened life no longer meets the address of g_unitZVector (docs/TOOLCHAIN.md, "A constant set in an earlier block and used once"). The store order: sched1 issues dead stores (weight 0) first in LUID order; retail's f00, f08, f20, f50, f54, f70, f78 after i4C is LUID order with no dead store among them, so no order of these statements gives it (a hill-climb from the natural order and three random restarts floor at 2); the 1.0 and -1 constants would have to die outside these stores, and the function has no later float code. Also tried (2026-11-08): chained assignments in five groupings (5-10 lines), a span setter with two float parameters (7, same as literals), the floats as named locals or constructor arguments (they cross the call into saved FPRs, over 100 lines).
// w8 (2026-11-09): retail's order is the four dead stores then the seven live ones in LUID order, so sched1 saw 1.0 and -1 live past f54: a region boundary between f54 and f70 or f70/f78 waiting on earlier stores through memory dependences. A do-while(0) barrier after f54 (probe only) gives retail's eleven stores exactly but holds the copy loop's `move a0,sp`/`addiu a1,sp,128` below it (42 lines). Ruled out: overwritten dead stores (flow1 deletes frame stores, flow2 never deletes sp stores), a branch over a dead local (gone by the first jump), static locals (constructed in place, ~145 lines), an inline maker returning by value (two copies, 147). docs/TOOLCHAIN.md, "A constant set in an earlier block and used once".
// w15 (2026-11-10): with the stores in member order, retail's order is what sched1 gives when f70 and f78 wait (a pointer alias analysis cannot place, `f32* p = &f54; p[7] = ..; p[9] = ..;`, gives the eleven stores exactly but keeps the pointer in a0) or when the 1.0 and -1 pseudos live past the block. Ruled out: memory dependences between frame stores (constant offsets never conflict), the ADDRESSOF lever (const-ref setter temporaries are merged again by cse2, 7 lines; a const-ref count, 15), conditions folded by gcse (7) or kept by combine (85). docs/toolchain/alias-classes.md, "What else is ruled out (w15)".
// w19 (2026-11-10, tools/sched1.py): re-scored 2 lines. On a member-order dump (f00 f04 f08 f18 f20 q30 i4C f50 f54 f70 f78), `--prio` lowering only the f70 and f78 stores to 1 gives retail's eleven stores exactly; so does deleting the 1.0 and -1 REG_DEAD notes (weight 0), but that also raises both constants' loads by the birthing rule (sched1 issues 1.0, -1, 750, -1500 where retail's code has 1.0, 750, -1, -1500), so retail's stores are the late-ready form: f70 and f78 wait on something, not live-out constants. No plain source form of that found. docs/toolchain/alias-classes.md, "A constant set in an earlier block and used once".
// Earlier (p58b, j40o03): 10 lines with the literal 200 in the constructor: local-alloc widens each quantity's life by one insn, the 200 is set right after the lq whose address (v0) dies, so it took a0 and the copy source v0; no store order changes that (sched1 always pairs the 200 with the lq in one cycle).

struct __attribute__((aligned(16))) Q_1549C8 { s32 a, b, c, d; };
struct Dst_1549C8;
void* FillMemory(void* p, s32 v, s32 n);
extern Q_1549C8 g_unitXVector;
extern Q_1549C8 g_unitZVector;
extern Q_1549C8 D_00248D30;

struct A_1549C8 {
    Q_1549C8 q[9];
    A_1549C8()
    {
        FillMemory(this, 0, 0x90);
        q[1] = D_00248D30;
        q[5] = g_unitXVector;
        q[8] = D_00248D30;
    }
};
struct B_1549C8 {
    f32 f00;
    f32 f04;
    f32 f08;
    s32 pad0C[3];
    f32 f18;
    s32 pad1C;
    f32 f20;
    s32 pad24[3];
    Q_1549C8 q30;
    s32 pad40[3];
    s32 i4C;
    f32 f50;
    f32 f54;
    s32 pad58[6];
    f32 f70;
    s32 pad74;
    f32 f78;
    s32 pad7C;
    B_1549C8(s32 ringPoints)
    {
        FillMemory(this, 0, 0x80);
        f00 = 750.0f;
        f04 = 750.0f;
        f18 = -1500.0f;
        q30 = g_unitZVector;
        i4C = ringPoints;
        f50 = 1.0f;
        f54 = 1.0f;
        f70 = 1.0f;
        f78 = -1.0f;
        f20 = -1.0f;
        f08 = 1.0f;
    }
};
struct C_1549C8 { Q_1549C8 q[13]; };
struct Dst_1549C8 {
    s32 f0;
    A_1549C8 a;
    B_1549C8 b;
    C_1549C8 c;
};

extern s32 D_00261F70;
extern s32 D_00261F74;
extern A_1549C8 D_0027C010;
extern B_1549C8 D_0027C0A0;
extern C_1549C8 D_00261F80;

void InitSpawnRecord(Dst_1549C8* self)
{
    s32 ringPoints = 200;
    if (!D_00261F70) {
        D_0027C010 = A_1549C8();
        D_00261F70 = 1;
    }
    if (!D_00261F74) {
        D_0027C0A0 = B_1549C8(ringPoints);
        D_00261F74 = 1;
    }
    FillMemory(self, 0, 0x200);
    self->f0 = 1;
    self->a = D_0027C010;
    self->b = D_0027C0A0;
    self->c = D_00261F80;
}
