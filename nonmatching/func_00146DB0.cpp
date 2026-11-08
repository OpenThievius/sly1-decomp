// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 986/1020 (96.7%), checked 2026-11-08
// NEAR (2026-11-07, worker night-large2): the frame, the box, the whole loop and the push are
// retail's; after the loop the registers differ (35 lines): retail's MulXSum of the split motion
// has its weight -f354 in vf1 and stores both weight slots after the arithmetic (ours stores the
// first before it, and gives along vf1), and its GPRs skip v0 in the else branch (lw v1, mfc1 a0)
// and v1 at the dot's qmfc2 (a0); the final push loads the motion (lq v0) after the weight's mfc1
// v0, ours first. Tried: u128 helpers, ToFloatMoved, Set, the copy before the push, a local for
// f33C or -f354, SplitVectorAlongAxis as void or s32, every order of the landing block's three
// statements (permute.py).
// In the context of its file, src/main/state_notifier.cpp.
#include "common.h"
#include "vu0.h"
#include "state_notifier.h"
#include "world.h"
#include "collider.h"

s32 IsEligibleNotifierTarget(void* unused, Collider* self);

// A hit CollectMeshHits gives (0x30 bytes): the surface's normal at 0x10, the depth at 0x20.
struct NotifierMeshHit {
    u8 pad0[0x10];
    Vec02 normal;           // 0x10
    f32 depth;              // 0x20
    u8 pad24[0x30 - 0x24];
};

extern const f32 D_00248D40[4];
extern u8 g_unitXVector[];
extern const Vec02 g_unitZVector;
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInBox(World* world, s32 p1, Vec02* lo, Vec02* hi, s32 (*filter)(void*, Collider*),
                          StateNotifier* self, s32* n, Collider*** list);
s32 CollectMeshHits(Vec02* pos, s32 count, TreeNode03* nodes, s32 a3, Mesh03* mesh, s32 max,
                    NotifierMeshHit* out, f32 radius);
f32 SplitVectorAlongAxis(Vec02* v, const Vec02* axis, Vec02* along, Vec02* across);

void func_00146DB0(StateNotifier* self)
{
    typedef Vu0::Vec Vec;
    PushBackMemoryMark();
    f32 best = 0.0f;
    Vec02 lo;
    Vec02 hi;
    Vu0::Q(lo) = Vu0::MulAddX(Vec::Of(self->v140), Vec::Of(D_00248D40), Vec::Scalar(-self->f34C)).q;
    Vu0::Q(hi) = Vu0::MulAddX(Vec::Of(self->v140), Vec::Of(D_00248D40), Vec::Scalar(self->f34C)).q;
    Vec02 dir;
    Vec02 bestN;
    NotifierMeshHit hits[8];
    s32 count;
    Collider** list;
    GatherCollidersInBox(self->world, 0, &lo, &hi, IsEligibleNotifierTarget, self, &count, &list);
    for (s32 i = 0; i < count; i++) {
        Collider* c = list[i];
        if (c->flags538 & 0x10000000000ULL) {
            f32 dist = Vu0::Distance(c->v140, self->v140) - c->radius3CC - self->f34C;
            if (dist < best) {
                Vu0::Set(dir, Vu0::NormalizeOr(Vu0::Sub(Vec::Of(self->v2F0), Vec::Of(c->v140)),
                                               Vec::Of(*(Vec02*)g_unitXVector)).q);
                if (Vu0::ToFloat(Vu0::Dot(Vec::Of(self->v300), Vec::Of(dir))) < 0.0f) {
                    best = dist;
                    bestN = dir;
                }
            }
        } else if (c->tree.nodes != 0) {
            s32 n = CollectMeshHits(&self->v140, c->tree.count, c->tree.nodes, 0, &c->meshCopy, 8, hits,
                                    self->f34C);
            for (s32 j = 0; j < n; j++) {
                NotifierMeshHit* h = &hits[j];
                f32 depth = h->depth;
                if (depth < best && Vu0::ToFloat(Vu0::Dot(Vec::Of(self->v300), Vec::Of(h->normal))) < 0.0f) {
                    bestN = h->normal;
                    best = depth;
                }
            }
        }
    }
    f32 zero = 0.0f;
    if (best < zero) {
        Vec02 along;
        Vec02 across;
        Vec02 motion;
        if (0.7f < bestN.z && self->state == 3) {
            SplitVectorAlongAxis(&self->v300, &g_unitZVector, &along, &across);
            Vu0::Q(motion) = Vu0::MulXSum(Vec::Of(along), Vec::Scalar(-self->f354), Vec::Of(across),
                                          Vec::ScalarAt(self->f358)).q;
            if (self->f33C == 0) {
                s32 low = Vu0::ToFloat(Vu0::Dot(Vec::Of(motion), Vec::Of(bestN))) < self->f348;
                if (low) {
                    self->f33C = 1;
                    across.z = zero >? across.z;
                    Vu0::Q(motion) = Vu0::MulAddX(Vec::Of(across), Vec::Of(g_unitZVector), Vec::Scalar(self->f348)).q;
                }
            }
        } else {
            SplitVectorAlongAxis(&self->v300, &bestN, &along, &across);
            Vu0::Q(motion) = Vu0::MulXSum(Vec::Of(along), Vec::Scalar(-self->f354), Vec::Of(across),
                                          Vec::ScalarAt(self->f358)).q;
        }
        Vu0::Q(self->v2F0) = Vu0::MulAddX(Vec::Of(self->v2F0), Vec::Of(bestN), Vec::Scalar(-best)).q;
        self->v300 = motion;
    }
    PopBackMemoryMark();
}
