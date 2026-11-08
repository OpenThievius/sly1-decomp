// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 0/0, checked 2026-11-08
// NEAR (2026-11-08, worker night-large2): all but eight lines: in the following branch retail
// keeps the fallback of the direction's normalisation (D_00248D30, lq) in v0 and the speed's
// weight bits in v1 (so the length's qmfc2 takes v1), ours the other way round. Found: the
// touch query cleared through an inline member (its address formed again for each use), the
// player's slot 0x140 and CreateAnimationPlayerWithoutPresetTargets as declared here (an s32
// return for the first, none for the second: each moves retail's v0 and v1), the weight as a
// value of its own before the normalisation, the direction stored with Set, the class 0x46
// state as a switch over 0..5. Tried: the weight inline, before the height, as a Vec, Scalar;
// the fallback or the difference first; u128 helpers; ComputeObjectFrameAtTime returning a value.
// In the context of its file, src/main/file_14EE40.cpp.
#include "common.h"
#include "owner_message.h"
#include "vu0.h"
#include "pooled_object.h"
#include "pad_record.h"
#include "switched_collider.h"
#include "globals.h"

s32 IsObjectOfKind(void* obj, s32 kind);
PooledObject* FindEarliestPooledChild(PooledObject*);
void SetColliderAnchors(Collider* o, s32 a, s32 b, s32 c, s32 d);
s32 FillMemory(void* p, s32 zero, s32 size);
Collider* FindContactingPart(void* self);
void InitOwnerMessage(OwnerMessage* m, s32 mode, void* owner);
void LaunchObjectFromPooledObject(void);
void StartPadRecordPattern(void* rec, s32 n, f32 t);
s32 CountHeldPooledChildren(void* self);
void FindNodeForQuery(void* query, s32 a, s32 b);
void SendPointEventToWorldListener(Vec02* at, f32 x);
void ComputeObjectFrameAtTime(void* self, void* top, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin, f32 t);
void BuildBasisFromX(Vec02* v, Mat02* out);
void StartSoundEffect(s32 a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void CreateAnimationPlayerWithoutPresetTargets(void* a, PooledObject* b, s32 c, void** out, f32 fa, f32 fb);

// The query FindNodeForQuery takes for an object that touched a held one (func_0014F270).
struct HeldTouchQuery {
    PooledObject* self;     // 0x00
    Collider* other;        // 0x04
    u8 pad08[0x20 - 0x08];
    Vec02 pos;              // 0x20
    Vec02 vel;              // 0x30

    void Clear() { FillMemory(this, 0, (s32)sizeof(*this)); }
};

// What a group member's slot 0x7C is told when a held object lands (func_0014F270).
struct HeldLandEvent {
    s32 kind;               // 0x00: 4
    u8 pad04[0x20 - 0x04];
    Vec02 pos;              // 0x20
};

typedef void (*ObjFn)(void* self);
typedef void (*ObjPtrFn)(void* self, void* a);

void UpdateHeldPooledObject(PooledObject* self)
{
    typedef Vu0::Vec Vec;
    Collider* c = FindContactingPart(self);
    if (c != 0) {
        s32 lands = 1;
        if (c == (Collider*)g_player && (g_player->f2220 != 6 || g_player->f239C != 2)) {
            OwnerMessage m;
            InitOwnerMessage(&m, 0, self);
            m.fn = LaunchObjectFromPooledObject;
            ((s32 (*)(void*, void*))((void**)g_player->desc)[0x140 / 4])(g_player, &m);
        } else if (IsObjectOfKind(c, 0x3A)) {
            StartSoundEffect(0x34, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            if (g_player != 0 && g_player->heldObject == c) {
                StartPadRecordPattern(&g_padRecord, 4, 0.25f);
            }
            if (!(CountHeldPooledChildren(c) < *(s32*)((u8*)c + 0x564))) {
                PooledObject* e = FindEarliestPooledChild((PooledObject*)c);
                if (e != 0) {
                    SetPooledObjectState(e, 5);
                }
            }
            ((ObjPtrFn)((void**)self->desc)[0x64 / 4])(self, c);
            ((ObjPtrFn)((void**)self->desc)[0x90 / 4])(self, (void*)&D_00248D30);
            ((ObjPtrFn)((void**)self->desc)[0x94 / 4])(self, (void*)&D_00248D30);
            SetColliderAnchors(self, 3, 0, 3, 0);
            SetPooledObjectState(self, 4);
            if (self->f574 != 0) {
                CreateAnimationPlayerWithoutPresetTargets(self->f574, self, 0, &self->watched, 0.0f, 1.0f);
                if (self->watched != 0) {
                    SetPooledObjectState(self, 3);
                }
            }
            lands = 0;
        } else if (IsObjectOfKind(c, 0x46)) {
            switch (((PooledObject*)c)->state) {
            case 0:
            case 1:
            case 2:
                break;
            case 3:
            case 4:
            case 5:
                lands = 0;
                ((ObjPtrFn)((void**)c->desc)[0x64 / 4])(c, 0);
                ((ObjFn)((void**)c->desc)[0x1C / 4])(c);
                break;
            }
        } else {
            HeldTouchQuery q;
            q.Clear();
            q.other = c;
            q.pos = self->v140;
            q.vel = self->v150;
            q.self = self;
            FindNodeForQuery(&q, 0, 0);
        }
        if (lands) {
            StartSoundEffect(0x33, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            void* g = self->member58C;
            if (g != 0) {
                HeldLandEvent ev;
                ev.kind = 4;
                ev.pos = self->v140;
                ((ObjPtrFn)((void**)*(void**)g)[0x7C / 4])(g, &ev);
            } else {
                SendPointEventToWorldListener(&self->v140, self->f560);
            }
            ((ObjPtrFn)((void**)self->desc)[0x64 / 4])(self, 0);
            ((ObjFn)((void**)self->desc)[0x1C / 4])(self);
        }
        return;
    }
    if (g_player != 0 && g_player->f2220 == 4) {
        return;
    }
    Vec02 at;
    Vec02 dir;
    Mat02 basis;
    at = self->holder->v140;
    at.z = at.z + self->holdHeight;
    f32 t = Vu0::Distance(at, self->v140) / self->holdSpeed;
    f32 lo = 0.0f;
    f32 hi = 0.25f;
    if (t < lo) {
        t = lo;
    } else if (hi < t) {
        t = hi;
    }
    ComputeObjectFrameAtTime(self->holder, 0, &at, 0, 0, 0, t);
    at.z = at.z + self->holdHeight;
    u128 k = Vu0::ScalarAt(self->holdSpeed);
    Vu0::Set(dir, Vu0::MulX(Vu0::NormalizeOr(Vu0::Sub(Vec::Of(at), Vec::Of(self->v140)), Vec::Of(D_00248D30)).q, k));
    ((ObjPtrFn)((void**)self->desc)[0x90 / 4])(self, &dir);
    BuildBasisFromX(&dir, &basis);
    ((ObjPtrFn)((void**)self->desc)[0x88 / 4])(self, &basis);
}
