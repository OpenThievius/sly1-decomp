// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 500/536 (93.3%), checked 2026-11-08
// NEAR: identical in the loop (the whole walk of the body's faces matches) and in the frame; the first block differs: retail makes the weight of f44 first in vf4 (qmtc2 after the lw of 0x44) and the segment end b (vmaddx vf5, stored at 0x10) before the start a (vf1), stores the 0x20 weight slot twice around them, and re-reads the count at 0xA0 after the stores (lw v0,0xA0 / blez); ours computes a first, keeps the count in a0 across the stores. Something makes retail's stores alias the stack count. The weights are FromFloatAt in a 16-byte local (the lw form of Vu0::Scalar). Tried a struct for count and list, and the order of a and b.
#include "common.h"
#include "range_record.h"
#include "collider.h"
#include "world.h"
#include "globals.h"
#include "game_clock.h"
#include "vu0.h"

struct MeshHit {
    Vec02 r0;
    Vec02 r1;
    Vec02 r2;
    Vec02 r3;
    f32 f40;
    f32 f44;
    u8 pad48[0x50 - 0x48];
    void* part;             // 0x50: the part of the body the segment hit
    u8 pad54[0x70 - 0x54];
};
struct RangeDrawPart { u8 pad00[0x2C]; u32 bits; u8 pad30[0x70 - 0x30]; };
struct RangeSlot {
    u8 pad00[0x18];
    f32 stamp;
    s32 count;
    RangeRecord* owners[4];
};
struct RangePartState { s32 w0; RangeSlot* slots; u8 pad08[0x28 - 8]; };
struct RangeFacePair { s32 part; s32 slot; };
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
typedef s32 (*RangeBodyFilter)(void*, Collider*);
void GatherCollidersInSphere(f32 radius, World* world, s32 a, Vec02* centre, RangeBodyFilter filter, s32 b, s32* count, Collider*** list);
s32 CollectTreeNodeSpans(void* tree, Vec02* from, Vec02* to, s32 a, s32 b, MeshHit* hit);

// A float read from memory as a weight: stored in a slot of its own that the next weight shares.
static inline u128 WeightAt(const f32& f)
{
    Vu0::Slot t;
    Vu0::Q(t) = Vu0::FromFloatAt(f);
    return Vu0::Q(t);
}

s32 RangeRecordMatchesKinds(RangeRecord* self, u32 bits);
s32 IsRangeRecordBodyCandidate(void* unused, Collider* o);

void func_001B2140(RangeRecord* self)
{
    Vec02 a;
    Vec02 b;
    s32 count;
    Collider** list;
    PushBackMemoryMark();
    GatherCollidersInSphere(self->f60, g_currentWorld, 0, &self->v50, IsRangeRecordBodyCandidate, 0, &count, &list);
    if (count != 0) {
        u128 w40 = WeightAt(self->f40);
        u128 w44 = WeightAt(self->f44);
        Vu0::Q(b) = Vu0::MulAddX(Vu0::Q(self->v10), Vu0::Q(self->v20), w44);
        Vu0::Q(a) = Vu0::MulAddX(Vu0::Q(self->v10), Vu0::Q(self->v20), w40);
        MeshHit hit;
        for (s32 i = 0; i < count; i++) {
            Collider* obj = list[i];
            if (CollectTreeNodeSpans(obj->tree.nodes, &a, &b, 0, 1, &hit) != 0) {
                if (hit.part != 0) {
                    s32 face = ((u8*)hit.part - (u8*)obj->meshCopy.faces) >> 5;
                    s32 end = obj->faceStarts[face + 1];
                    for (s32 j = obj->faceStarts[face]; j < end; j++) {
                        RangeFacePair* pair = (RangeFacePair*)obj->refs + j;
                        RangeDrawPart* part = (RangeDrawPart*)obj->drawParts + pair->part;
                        if (RangeRecordMatchesKinds(self, part->bits) != 0) {
                            RangePartState* state = (RangePartState*)obj->partStates + pair->part;
                            RangeSlot* slot = state->slots + pair->slot;
                            if (slot->stamp != g_gameClock.time) {
                                slot->stamp = g_gameClock.time;
                                slot->count = 0;
                            }
                            if ((u32)slot->count >= 4) {
                                goto done;
                            }
                            slot->owners[slot->count] = self;
                            slot->count++;
                        }
                    }
                }
            }
        }
    }
done:
    PopBackMemoryMark();
}
