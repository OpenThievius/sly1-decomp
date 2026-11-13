// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 260/380 (68.4%), checked 2026-11-13
// w46-d (2026-11-13), 1 compile (the dumps), a first study of the order (docs/toolchain/sched1.md, "Thirty-two products of equal priority"): sched1 orders the block by INSN_REG_WEIGHT then LUID. z2*y goes first because z2 and y die in it; every x product is its pair's last use in the source's order (weight 0) and out[7], out[15] are xa's and xb's, so sched1 issues 23, then 16 20 17 21 18 22 7 15 19, then the rest by LUID: the trace agrees insn for insn. Retail's z2*y in f0 needs that pair's life at 15 insns or less (local-alloc: 4 refs over 22 insns is 3636 against the triple's 5000), i.e. out[7] and out[15] among the first eight triples, as retail's final order has them (23 16 20 17 7 18 15 22): still the last uses of xa and xb, but written before z1's x products. ny takes f10 in global-alloc's first pass over the registers (only those already used; z1*ny's quantity has f10); retail's ny is f2. Not searched: orders that are not nests.
// w44-fa (2026-11-12), 1 compile (the dumps): nothing new. sched2 delays z*y in ours as in retail (its priority drops to 13 against 23 to 25 for the other seven products, through the registers' anti dependences), so the pair products' order after reload follows the registers, and the wall stays local-alloc's ranking of z2*y against z2*y*x on sched1's order.
// NEAR: order: the statements written z weight by z weight (for each of z3, z, z1, z2: xa, xb, x,
//       each with ny then y) give retail's x, xa and xb registers ($f15, $f16, $f17), the copy of
//       x at entry and y left in $f13, and the whole branch code but z1 and ny. Left (about 50
//       lines): the multiply block's local registers. Retail's z2*y takes $f0 and z2*y*x $f1;
//       ours the other way round, because sched1 puts out[23]'s store right after the fourth
//       product (z2*y*x's life 4 insns, priority 2500 against z2*y's 2142 in local-alloc's
//       order); one insn later and z2*y wins (build/swarm emulator). From there z1 (which then
//       conflicts with $f0) takes $f10 and ny $f2, as retail's do.
// Tried (2026-11-10, w11): all 1728 regular statement orders (nest order, each index's order):
//       this one is the best (51 lines; the out-index order 70). The inner order and the z order
//       permuted on their own: no better. The 8 products named first (either order): identical
//       code. An inline column setter per z weight: 95. A separate third x weight (xc) or z
//       weight (z0): 68 and 82. Declaration orders, ny's position: no change or worse.
//       Re-associations in this order: x*(z*y) 63, (y*z)*x 55 (its operands then differ).
// Tried (order-class pass 2): the products re-associated four ways (z*(ny*xa), xa*ny*z, ny*xa*z, z*xa*ny): 94 to 98 words, worse than 70.
// Tried (2026-11-10, w15): not the blend family of func_0019C9C8 (no loop, no pointer load,
//       no SetBlendItemWeights call: only the 32 products and 24 stores through out), so its
//       typed-pointer and PRE levers have nothing to act on. A copy of y (`ya = y`) and the 24
//       products named before all 24 stores: identical code (51 lines). Without sched1
//       (-fno-schedule-insns, to explore): 94 lines, so retail's 18 live FPRs are sched1's
//       interleaving and the wall stays local-alloc's ranking on sched1's order.
#include "common.h"

void ComputeGridBlendWeights(void* self, f32* out, f32 x, f32 y, f32 z)
{
    f32 xa, xb;
    f32 z1, z2, z3;
    f32 ny = 1.0f - y;
    if (x < 0.0f) {
        xb = x + 1.0f;
        xa = -x;
        x = 0.0f;
    } else {
        xb = 1.0f - x;
        xa = 0.0f;
    }
    if (z < 1.0f) {
        z3 = 1.0f - z;
        z2 = 0.0f;
        z1 = 0.0f;
    } else if (z < 2.0f) {
        z = 2.0f - z;
        z2 = 0.0f;
        z1 = 1.0f - z;
        z3 = 0.0f;
    } else {
        z1 = 3.0f - z;
        z = 0.0f;
        z2 = 1.0f - z1;
        z3 = 0.0f;
    }
    out[0] = z3 * ny * xa;
    out[4] = z3 * y * xa;
    out[8] = z3 * ny * xb;
    out[12] = z3 * y * xb;
    out[16] = z3 * ny * x;
    out[20] = z3 * y * x;
    out[1] = z * ny * xa;
    out[5] = z * y * xa;
    out[9] = z * ny * xb;
    out[13] = z * y * xb;
    out[17] = z * ny * x;
    out[21] = z * y * x;
    out[2] = z1 * ny * xa;
    out[6] = z1 * y * xa;
    out[10] = z1 * ny * xb;
    out[14] = z1 * y * xb;
    out[18] = z1 * ny * x;
    out[22] = z1 * y * x;
    out[3] = z2 * ny * xa;
    out[7] = z2 * y * xa;
    out[11] = z2 * ny * xb;
    out[15] = z2 * y * xb;
    out[19] = z2 * ny * x;
    out[23] = z2 * y * x;
}
