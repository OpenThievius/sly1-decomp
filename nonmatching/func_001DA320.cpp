// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 948/956, checked 2026-11-07
// NEAR: the control flow, the calls and the vector arithmetic are retail's (86% of the instructions equal); left: the allocation (retail keeps the follower in s1 and the slot in s2, here swapped, and numbers the VU registers of the sweep differently), the flag of the replace test (retail: v0, here a0) and the order of two loads. Needs Slot19::obj8, v30, v40 and PathFollower::fB4C (include/switched_collider.h).
#include "common.h"
#include "switched_collider.h"
#include "globals.h"
#include "vu0.h"
#include "placed_object.h"
void TransformPointBetweenFrames(void* a0, void* a1, void* a2, void* a3);
s32 CollectColliderSpansInTree(Collider* self, void* a1, void* a2, void* a3, s32 a4, void* a5);
void ComputeObjectMotionInFrame(void* obj, void* a, void* b, void* c, s32 d, s32 e, s32 f);
void StartChildGroupDelay(void* obj, f32 t);
s32 IsObjectAccepted(void* obj, void* by);
void SetColliderTurnAnchorPreset(void* obj, s32 n);
void SetColliderMoveAnchorPreset(void* obj, s32 n);
s32 IsObjectAttached(Collider* c);
s32 IsObjectOfKind(void* node, s32 kind);
void AddMeshContacts(f32 f, Collider* a, void* b, Collider* c, s32 d, s32 e, s32 g, void* h);
void func_00186BA8(void* a, Collider* b, void* c, void* d, void* e, void* f);

void func_001DA320(PathFollower* self, Collider* other, void* a2, void* a3, void* a4)
{
    if ((other->flags538 & ((u64)0x8000 << 40)) != 0 || (((u32*)other->desc)[2] & 0x10) != 0) {
        for (u32 i = 0; i < 4; i++) {
            Slot19* slot = &self->f6B0[i];
            s32 first = (s32)i < 2;
            Vec02 p;
            Vec02 q;
            Vec02 k;
            ColliderSpan hit;
            p = *(Vec02*)((u8*)slot->obj8 + 0x40);
            p.z = p.z - (first ? self->f610 : self->f614);
            TransformPointBetweenFrames(self, 0, &p, &p);
            q = slot->obj->v190;
            q.z = q.z - (first ? self->f610 : self->f614);
            TransformPointBetweenFrames(self, 0, &q, &q);
            u128* pp = &Vu0::Q(p);
            u128 base = *pp;
            f32 r = first ? self->f610 : self->f614;
            u128 d = Vu0::Sub(Vu0::Q(p), Vu0::Q(q));
            Vu0::Q(k) = Vu0::FromFloat(r);
            *pp = Vu0::MulAddX(base, Vu0::DivX(d, Vu0::Sqrt(Vu0::Dot(d, d))), Vu0::Q(k));
            if (CollectColliderSpansInTree(other, a4, &p, &q, 1, &hit) > 0 && hit.time[0] > 0.0f) {
                s32 replace = 1;
                s32 cur = self->f6A0;
                if (cur + 1 == slot->f0C) {
                    replace = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(slot->v20), Vu0::Q(self->rot.r[2]))) < Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(hit.q[0]), Vu0::Q(self->rot.r[2])));
                }
                if (replace != 0) {
                    slot->v30 = *(Vec02*)&hit.q[2];
                    slot->f0C = cur + 1;
                    slot->v20 = *(Vec02*)&hit.q[0];
                    ComputeObjectMotionInFrame(other, 0, &slot->v20, &slot->v40, 0, 0, 0);
                }
                if (other->id != 1) {
                    if ((other->desc->flags & 0x20) != 0) {
                        if (*(s32*)((u8*)other + 0x550) == 0) {
                            StartChildGroupDelay(other, 0.0f);
                        }
                    } else if (IsObjectOfKind(other, 0x25) != 0 && *(s32*)((u8*)other + 0x678) == 0 && IsObjectAccepted(other, self) != 0) {
                        if (*(s32*)((u8*)other + 0x6C4) != -1) {
                            SetColliderTurnAnchorPreset(other, *(s32*)((u8*)other + 0x6C4));
                        }
                        if (*(s32*)((u8*)other + 0x6C8) != -1) {
                            SetColliderMoveAnchorPreset(other, *(s32*)((u8*)other + 0x6C8));
                        }
                        f32 m = other->mass;
                        *(s32*)((u8*)other + 0x678) = 1;
                        *(void**)((u8*)other + 0x6CC) = self;
                        other->mass = m * *(f32*)((u8*)other + 0x6C0);
                    }
                }
            }
        }
    } else if (self->fB4C != 0 && IsObjectAttached((Collider*)self->fB4C) != 0) {
        Collider* c = (Collider*)self->fB4C;
        if ((other->flags538 & ((u64)0x8000 << 25)) != 0) {
            AddMeshContacts(other->radius3CC, other, (u8*)other + 0x140, c, c->tree.count, (s32)c->tree.nodes, 0, (u8*)self + 0xB74);
        } else if (a3 != 0) {
            func_00186BA8(c, other, a2, a3, a4, (u8*)self + 0xB74);
        }
    }
}
