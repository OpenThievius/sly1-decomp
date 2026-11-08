// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 812/808, checked 2026-11-07
#include "transform_object.h"
#include "warp_page.h"
#include "oscillator.h"
#include "camera.h"
#include "list_iter.h"
#include "screen_element.h"
#include "shapes.h"
#include "globals.h"
#include "game_progress.h"
#include "screen_fade.h"
#include "pad_record.h"
#include "object_link.h"
#include "contact_tracker.h"
#include "lookup_object.h"
#include "object_sub_group.h"
#include "switched_collider.h"
#include "animation.h"
#include "object_gatherer.h"
#include "asm_func.h"
#include "vu0.h"
#include "common.h"
#include "common.h"
// NEAR (2026-11-08, wave 4): UpdateC37 (1F5268): everything is retail's except one instruction (812 bytes against 808): in the edge loop retail loads the vertex array straight into $t2 (the call's seventh argument) and adds it to the two scaled indices, loading edge[1] before edge[0] into $a2 and $a1, where here the array is loaded into $a1 and copied to $t2 (a move) and edge[0] goes through $v0. The array as a local pointer, as a Quad16*, as a signed int, as separate offsets and through an inline helper compiled to the same loop. The callees are declared with the float first (CollectMeshHits, AddMeshContacts): the float arguments are loaded before the integer ones.
void UpdateCollider(Collider* self);
s32 GetActiveSwitchedCollider(void);
struct TrackerHit {
    u8 pad00[0x30];
    u8 span[0x50];
    s32 f80;
    s32 f84;
    u8 pad88[0x18];
};

typedef s32 (*TargetHitFn)(Collider* self, s32 kind);
typedef void (*TargetNotifyFn)(Collider* self, TrackerHit* hit);
s32 CollectMeshHits(f32 radius, Vec02* pos, s32 count, s32 nodes, s32 zero, void* mesh, s32 one, void* out);
s32 CollectTreeNodeSpans(s32 tree, void* a1, void* a2, s32 a3, s32 a4, void* out, void* base);
void AddSphereSphereContact(Collider* a, Collider* b, s32* out);
void AddMeshContacts(f32 radius, Collider* a, Vec02* pos, Collider* b, s32 c, s32 d, s32 e, s32* out);
void func_00186BA8(Collider* a, Collider* b, s32 c, s32 d, s32 e, void* f);
void InitOwnerMessage(void* out, s32 kind, void* owner);
void OfferTrackedNodeLaunch(void* rec, s32 result, void* hit);
void FreePooledContactChain(void* pool, s32 chain);
s32 func_0013E658(void* a, s32 b);

void UpdateC37(C37* self)
{
    TrackerHit hit;
    s32 result;
    UpdateCollider(self);
    Collider* target = (Collider*)GetActiveSwitchedCollider();
    if (target == 0) {
        return;
    }
    if (self->f4E0 != 1 && self->f4E0 != 4) {
        return;
    }
    if ((*(TargetHitFn*)((u8*)target->desc + 0x13C))(target, self->rec.f04) != 0) {
        return;
    }
    s32 far = 1;
    f32 r = self->radius3CC;
    f32 sum = r + target->radius3CC;
    Vec02* pos = &target->v140;
    u128 mine = Vu0::Q(self->v140);
    u128 gap = Vu0::Sub(mine, Vu0::Q(target->v140));
    if (!(sum * sum < Vu0::ToFloatMoved(Vu0::Dot(gap, gap)))) {
        far = 0;
    }
    if (far != 0) {
        return;
    }
    result = 0;
    if (self->rec.f04 == 5) {
        if (0.0f < ((f32*)target)[0x158 / 4]) {
            return;
        }
        if (func_0013E658(pos, (s32)self->tree.nodes) == 0) {
            return;
        }
        if ((target->flags538 & ((u64)0x8000 << 25)) != 0) {
            if (CollectMeshHits(target->radius3CC, pos, (s32)self->tree.count2, (s32)self->tree.nodes, 0, &self->meshCopy, 1, &hit) > 0) {
                return;
            }
        } else {
            for (s32 i = 0; i < target->meshCopy.edgeCount; i++) {
                s16* edge = (s16*)((u8*)target->meshCopy.edges + i * 16);
                Quad16* verts = (Quad16*)target->meshCopy.verts;
                if (CollectTreeNodeSpans((s32)self->tree.nodes, &verts[edge[0]], &verts[edge[1]], 0, 1, hit.span, verts) == 0) {
                    return;
                }
                if (hit.f80 != 0) {
                    return;
                }
                if (hit.f84 != 0) {
                    return;
                }
            }
        }
    } else {
        s32 inside;
        if ((self->flags538 & ((u64)0x8000 << 25)) != 0) {
            u128 d = Vu0::Sub(Vu0::Q(target->v140), mine);
            inside = 1;
            if (!(Vu0::ToFloat(Vu0::Length(d)) < r)) {
                inside = 0;
            }
        } else {
            inside = func_0013E658(pos, (s32)self->tree.nodes);
        }
        if (inside == 0) {
            if ((target->flags538 & ((u64)0x8000 << 25)) != 0) {
                if ((self->flags538 & ((u64)0x8000 << 25)) != 0) {
                    AddSphereSphereContact(target, self, &result);
                } else {
                    AddMeshContacts(target->radius3CC, target, pos, self, (s32)self->tree.count2, (s32)self->tree.nodes, 0, &result);
                }
            } else if ((self->flags538 & ((u64)0x8000 << 25)) != 0) {
                AddMeshContacts(self->radius3CC, self, &self->v140, target, (s32)target->tree.count2, (s32)target->tree.nodes, 0, &result);
            } else {
                s32 nodes = (s32)self->tree.nodes;
                if (nodes != 0) {
                    func_00186BA8(target, self, (s32)self->tree.count2, nodes, nodes, &result);
                }
            }
            if (result == 0) {
                return;
            }
        }
    }
    InitOwnerMessage(&hit, self->rec.f04, self);
    OfferTrackedNodeLaunch(&self->rec, result, &hit);
    (*(TargetNotifyFn*)((u8*)target->desc + 0x140))(target, &hit);
    FreePooledContactChain((void*)self->world, result);
}

