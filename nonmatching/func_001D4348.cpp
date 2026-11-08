// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 648/848 (76.4%), checked 2026-11-08
// NEAR (2026-11-08, night-sizex1): 848 bytes, retail's size now. The case tree's blez is a third node, `case -1: break;` (the value the function starts from), which balance_case_nodes needs for retail's beqzl 0, blez, beql 1; the two three-slot blocks are one inline taking the first slot's index (slots[o + 2], ...), whose constant offsets fold as retail's unrolled stores do (a pointer to the slot kept an addiu); the weights' loop reads each weight with FromFloatAt (retail's lw a0, 0(v0)). Still differs (73 lines): the float registers of the weights (retail divides w2 into f0 and sums into f1) and the scheduling of the first weight's divide; tools/permute.py --auto found nothing. Earlier: the blend weights of the player's turn (the slots follow the velocity at 0x640). The vector work, the max.s calls and the sums are retail's, and the branches into the two three-slot blocks differ in one place: retail tests the sub-state (fA14) as `beqzl 0`, `blez` (skip), `beql 1`, ours as `beqz 0`, `beql 1` (no blez), which is what GCC's case tree gives for {0, 1}. The C is 860 bytes against retail's 848. A switch with a default, with a third case, with the cases as ifs, `if (x > 0)` nested, and the value cast to u32, s16 or long long all give other shapes (none has the blez). The blocks are one inline function called twice; retail has them unrolled.
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
    f32 length = scale * Vu0::ToFloat(Vu0::Dot(v, v));
    f32 along = Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v640), v));
    f32 first = along / length;
    zero = 0.0f;
    u128 v2 = Vu0::Q(slots[o + 2].v10);
    f32 length2 = scale * Vu0::ToFloat(Vu0::Dot(v2, v2));
    u128 v4 = Vu0::Q(slots[o + 4].v10);
    f32 length4 = scale * Vu0::ToFloat(Vu0::Dot(v4, v4));
    f32 w0 = first >? zero;
    slots[o + 0].weight = w0;
    f32 w2 = (Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v640), v2)) / length2) >? zero;
    slots[o + 2].weight = w2;
    f32 sum = w0 + w2;
    f32 w4 = (Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v640), Vu0::Q(slots[o + 4].v10))) / length4) >? zero;
    sum = sum + w4;
    slots[o + 4].weight = w4;
    if (sum < 1.0f) {
        slots[o + 6].weight = 1.0f - sum;
    } else {
        slots[o + 4].weight = w4 / sum;
        slots[o + 6].weight = zero;
        slots[o + 0].weight = w0 / sum;
        slots[o + 2].weight = w2 / sum;
    }
}

void func_001D4348(Player* self, BlendSlot* slots, Gr8B* gr)
{
    Vec02 acc;
    Vec02 k;
    f32 scale = *(f32*)((u8*)self->watched2230 + 0x18);
    s32 i;
    if (self->fA14 == -1) {
        if (Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v640), Vu0::Q(slots[0].v10))) < 0.0f)
            self->fA14 = 1;
        else
            self->fA14 = 0;
    }
    for (i = 7; i >= 0; i--)
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
    for (i = 7; i >= 0; i--) {
        Vu0::Q(k) = Vu0::FromFloatAt(e->weight);
        Vu0::Q(acc) = Vu0::MulAddX(Vu0::Q(acc), Vu0::Q(e->v10), Vu0::Q(k));
        e++;
    }
    Vu0::Q(k) = Vu0::FromFloat(scale);
    Vu0::Q(self->v640) = Vu0::MulX(Vu0::Q(acc), Vu0::Q(k));
    SetBlendItemWeights(gr, 0x20, 8, slots);
}
