// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 804/848 (94.8%), checked 2026-11-09
// NEAR (2026-11-09, w8-1D4348): every instruction in retail's order (regdiff: registers). Fixed tonight: both loops are `for (i = 0; i < 8; i++)`, which loop.c reverses (check_dbra_loop) into retail's `li v1,7 ... bgez`; the reversed counter's init is emitted at the loop start after the insns PRE hoisted to the end of the block (Zero, scale's qmtc2), which is retail's mfc1, vsub, qmtc2, li order (a source `for (i = 7; i >= 0; i--)` keeps `i = 7` first); the weights' slots are Vu0::ScalarAt(e->weight) and Vu0::Scalar(scale), no slot of our own; w2's quotient is a named local (retail divides into f0, then max.s into f4) and w4's is not (in place in f0); the sum is one expression after w4 (`sum = w0 + w2 + w4`: w0 + w2 in f1, the sum in f2); the rescale divides in slot order w0, w2, w4, then the zero: the last divide is where sum dies (INSN_REG_WEIGHT -1), sched1 issues it first, and local-alloc's ties then give w4/sum f0, w0/sum f1, w2/sum f2, which global-alloc's preferences pass to w4 (f0) and sum (f2). The conversions: the first slot's length and along are ToFloatViaBits (the mtc1 an asm with a latency of 1, so mul.s follows the qmfc2), the other two lengths ToFloatMoved (the compiler's qmfc2 holds the vu0 unit, so the 1.0 constant's lui/mtc1 takes the memory slot before the next lqc2, as retail). Still differs (26 lines, registers only): ToFloatMoved makes Dot(v2, v2) and Dot(v4, v4) GPR pseudos (regclass TI_REGS: one "=j" set against one "r" use), so local-alloc gives them v0 and the asm output reload a VU register after the scratch `one` took vf1 (ours vf3/vf4 for the product, vf1 for one; retail vf1 for the product); along's ViaBits GPR is a local pseudo (v1) where retail's a0 is reload's round robin (retail alternates v0/a0 over all six conversions, as all-ToFloat does). All six as ToFloat give every register but schedule the first divide and the 1.0 late (44 lines). What retail had is a dot product in VU_REGS whose qmfc2 is the compiler's (the wall of func_0018A160, docs/TOOLCHAIN.md).
#include "common.h"
#include "switched_collider.h"
#include "c8b.h"
#include "vu0.h"

struct BlendSlotObject;
struct BlendSlot {
    f32 weight;             // 0x00
    BlendSlotObject* object; // 0x04
    u8 pad08[0x10 - 0x08];
    Vec02 v10;              // 0x10
};

void SetBlendItemWeights(Gr8B* obj, s32 a1, s32 a2, void* a3);

// The three weights of the slots base[0], base[2] and base[4] that follow self->v640: each is
// the part of v640 along the slot's vector over the squared length, scaled by `scale` and at
// least zero. They are made to add up to at most one; what is left goes to base[6].
static inline void SetSlotWeights(Player* self, BlendSlot* slots, s32 o, f32 scale)
{
    f32 zero;
    u128 v = Vu0::Q(slots[o + 0].v10);
    f32 length = scale * Vu0::ToFloatViaBits(Vu0::Dot(v, v));
    f32 along = Vu0::ToFloatViaBits(Vu0::Dot(Vu0::Q(self->v640), v));
    f32 first = along / length;
    zero = 0.0f;
    u128 v2 = Vu0::Q(slots[o + 2].v10);
    f32 length2 = scale * Vu0::ToFloatMoved(Vu0::Dot(v2, v2));
    u128 v4 = Vu0::Q(slots[o + 4].v10);
    f32 length4 = scale * Vu0::ToFloatMoved(Vu0::Dot(v4, v4));
    f32 w0 = first >? zero;
    slots[o + 0].weight = w0;
    f32 second = Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v640), v2)) / length2;
    f32 w2 = second >? zero;
    slots[o + 2].weight = w2;
    f32 w4 = (Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v640), Vu0::Q(slots[o + 4].v10))) / length4) >? zero;
    slots[o + 4].weight = w4;
    f32 sum = w0 + w2 + w4;
    if (sum < 1.0f) {
        slots[o + 6].weight = 1.0f - sum;
    } else {
        slots[o + 0].weight = w0 / sum;
        slots[o + 2].weight = w2 / sum;
        slots[o + 4].weight = w4 / sum;
        slots[o + 6].weight = zero;
    }
}

void func_001D4348(Player* self, BlendSlot* slots, Gr8B* gr)
{
    Vec02 acc;
    f32 scale = *(f32*)((u8*)self->watched2230 + 0x18);
    s32 i;
    if (self->fA14 == -1) {
        if (Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v640), Vu0::Q(slots[0].v10))) < 0.0f)
            self->fA14 = 1;
        else
            self->fA14 = 0;
    }
    for (i = 0; i < 8; i++)
        slots[i].weight = 0.0f;
    switch (self->fA14) {
    case -1:
        break;
    case 0:
        SetSlotWeights(self, slots, 0, scale);
        break;
    case 1:
        SetSlotWeights(self, slots, 1, scale);
        break;
    }
    Vu0::Q(acc) = Vu0::Zero();
    BlendSlot* e = slots;
    for (i = 0; i < 8; i++) {
        Vu0::Q(acc) = Vu0::MulAddX(Vu0::Q(acc), Vu0::Q(e->v10), Vu0::ScalarAt(e->weight));
        e++;
    }
    Vu0::Q(self->v640) = Vu0::MulX(Vu0::Q(acc), Vu0::Scalar(scale));
    SetBlendItemWeights(gr, 0x20, 8, slots);
}
