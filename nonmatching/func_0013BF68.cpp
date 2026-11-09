// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 2524/2532 (99.7%), checked 2026-11-09
// NEAR: every block is retail's, registers included; left: two pairs of instructions in another order: retail fills GatherCollidersInSphere's delay slot with the &list argument (here the pos copy after the call goes there), and stores the scatter loop's FromFloats vector to its local before its slot (here the slot first).
// Tried (night-close10): Set, a u128 copy, a chained store and Vec forms for the scatter vector
// (Vec makes the loop big enough that loop.c keeps the index product: 4 bytes longer); pos set
// before the sphere gather or after the other three pointers. The sched2 dump shows the two
// sqc2 independent after the qmtc2 reload, the slot's first in insn order (FromFloats stores its
// slot before the caller's local); retail's order needs the local's store first.
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
#include "child_group_object.h"
#include "object_message.h"
#include "vu0.h"
#include "object_event.h"
#include "globals.h"
#include "transform_object.h"
#include "fpu.h"
#include "owner_message.h"
#include "hit_target.h"
#include "value_range.h"

void RecordChildGroupPose(ChildGroupObject* self, s32 a, s32 b, Vec02* dir);
void StartChildGroupDelay(ChildGroupObject* self, f32 delta);
s32 IsObjectOfKind(void* node, s32 kind);
s32 IsObjectAttached(void* p);
Collider* GetActiveSwitchedCollider();
extern f32 D_00261370[4];
extern f32 D_00261380[4];
extern const f32 D_00249D78;

void PushBackMemoryMark();
void PopBackMemoryMark();
void* AllocateBackMemory(s32 size);
void CopyMemory(void* dst, void* src, s32 size);
void CollectContactingParts(ChildGroupObject* self, s32* count, Collider*** list);
void GatherCollidersInSphere(f32 radius, World* w, s32 a1, Vec02* center, s32 a3, s32 a4, s32* count, Collider*** list);
s32 CollectMeshHits(f32 radius, Vec02* p, void* a, void* b, s32 c, void* mesh, s32 d, void* out);
void InitOwnerMessage(void* msg, s32 kind, void* self);
void func_0013BE18();
f32 ClampToRange(void* range, f32 x);
void ConstrainColliderVector(Collider* c, Vec02* frame, Vec02* in, Vec02* out, s32 flag);
f32 RandomFloatInRange(f32 lo, f32 hi);
void* FillMemory(void* p, s32 v, s32 n);
void FindNodeForQuery(void* q, s32 a, s32 b);
void TransformPointBetweenFramesCG(void* from, void* to, Vec02* p, Vec02* out) __asm__("func_00128018");
void SendPointEventToWorldListener(Vec02* p, f32 radius);
void StartSoundEffect(s32 id, void* a, void* b, Vec02* pos, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void SetTimedState(Collider* c, s32 state);
void TriggerScriptEvent(void* self, s32 kind, s32 a, s32* b);
extern const Vec02 g_unitZVector;
extern ValueRange g_unitRange;

static inline f32 MaxF(f32 a, f32 b) { return b >? a; }

typedef void (*ColliderMsgFn)(Collider* self, void* msg);
typedef s32 (*ColliderQueryFn)(Collider* self, void* msg);

// The query func_0013BF68 sends for each object it hits (0x40 bytes, FillMemory'd).
struct BlastQuery { ChildGroupObject* from; Collider* to; u8 pad08[0x10 - 0x08]; s32 kind; u8 pad14[0x20 - 0x14]; Vec02 pos; Vec02 vel; };
// The message a ChildGroupObject's member gets (kind 9): the object, then two floats at 0x30.
struct BlastMessage { s32 kind; ChildGroupObject* from; u8 pad08[0x30 - 0x08]; f32 f30; f32 f34; };
// The sound slot at +0x680.
struct BlastSound { s32 id; f32 a; f32 b; f32 c; };

void func_0013BF68(ChildGroupObject* self)
{
    Collider* player;
    s32 count;
    Collider** list;
    Vec02* pos;
    Mat02* rot;
    Vec02* vel;
    Vec02* spin;
    RecordChildGroupPose(self, 0, 0, 0);
    player = (Collider*)GetActiveSwitchedCollider();
    PushBackMemoryMark();
    if (*(s32*)self->pad564 != 0) {
        CollectContactingParts(self, &count, &list);
        pos = &self->v610;
        rot = &self->m620;
        vel = &self->v650;
        spin = &self->v660;
        if (self->obj670 != 0) {
            s32 i;
            for (i = 0; i < count; i++) {
                if (self->obj670 == list[i])
                    break;
            }
            if (i >= count) {
                Collider** nl = (Collider**)AllocateBackMemory((count + 1) * 4);
                nl[0] = self->obj670;
                CopyMemory(nl + 1, list, count * 4);
                list = nl;
            }
        }
    } else {
        GatherCollidersInSphere(MaxF(self->f55C, self->f560), self->world, 0, &self->v610, 0, 0, &count, &list);
        pos = &self->v610;
        rot = &self->m620;
        vel = &self->v650;
        spin = &self->v660;
    }
    for (s32 i = 0; i < count; i++) {
        Collider* c = list[i];
        if (c->root == self->root)
            continue;
        if (c->id == 1)
            continue;
        if ((c->desc->flags & 0x20) != 0 && ((ChildGroupObject*)c)->f550 != 1) {
            StartChildGroupDelay((ChildGroupObject*)c, 0.1f);
            continue;
        }
        if (*(s32*)self->pad564 == 0 && c->tree.nodes != 0) {
            u8 hits[0x30];
            if (!CollectMeshHits(c->root == player ? self->f560 : self->f55C, pos, (void*)c->tree.count2, c->tree.nodes, 0, &c->meshCopy, 1, hits))
                continue;
        }
        if (IsObjectOfKind(c, 5)) {
            OwnerMessage msg;
            InitOwnerMessage(&msg, self->f67C, self);
            msg.fn = func_0013BE18;
            (*(ColliderQueryFn*)((u8*)c->desc + 0x140))(c, &msg);
            continue;
        }
        if (c->mass < self->f574 && c->parent == 0) {
            Vec02 dir;
            Vec02 imp;
            Vec02 nv;
            Vec02 sp;
            Vec02 ns;
            Vec02 off;
            Vu0::Q(dir) = Vu0::Sub(Vu0::Q(c->v140), Vu0::Q(self->v610));
            Vu0::Q(off) = Vu0::Q(dir);
            dir.z += 200.0f;
            Vu0::Q(dir) = Vu0::NormalizeOr(Vu0::Q(dir), Vu0::Q(g_unitZVector));
            f32 m = 1.0f / Fpu::Sqrt(ClampToRange(&self->f56C, c->mass) / *(f32*)&self->f56C.a);
            f32 sv = g_unitRange.Limit(((TimePolynomial*)D_00261370)->Eval(Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(c->v150), Vu0::Q(dir))) / self->f568));
            f32 d = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(off))) - (c->radius3CC + self->radius3D0);
            f32 sd = g_unitRange.Limit(((TimePolynomial*)D_00261380)->Eval((d >? 0.0f) / self->f55C));
            f32 k = self->f568 * m * sv * sd;
            Vu0::Q(imp) = Vu0::MulX(Vu0::Q(dir), Vu0::Scalar(k));
            ConstrainColliderVector(c, &c->v440, &imp, &imp, 0);
            Vu0::Q(nv) = Vu0::Add(Vu0::Q(c->v150), Vu0::Q(imp));
            ((const Desc02*)c->desc)->m20(c, &nv);
            if (0.0001f < k) {
                f32 r = k * 0.01f;
                f32 nr = -r;
                f32 x = RandomFloatInRange(nr, r);
                f32 y = RandomFloatInRange(nr, r);
                f32 z = RandomFloatInRange(nr, r);
                Vu0::Q(sp) = Vu0::FromFloats(x, y, z);
                ConstrainColliderVector(c, &c->v460, &sp, &sp, 0);
                Vu0::Q(ns) = Vu0::Add(Vu0::Q(c->v160), Vu0::Q(sp));
                ((const Desc02*)c->desc)->m21(c, &ns);
            }
        }
        BlastQuery q;
        FillMemory(&q, 0, sizeof(q));
        q.to = c;
        Vu0::Q(q.pos) = Vu0::Q(self->v610);
        Vu0::Q(q.vel) = Vu0::Q(self->v150);
        q.kind = 0x10;
        q.from = self;
        FindNodeForQuery(&q, 0, 0);
    }
    PopBackMemoryMark();
    Vec02 at;
    {
        void* frame;
        if (self->f224 != 0 && (*(u32*)((u8*)self->f224 + 0xB0) & 4) != 0)
            frame = *(void**)((u8*)self->f224 + 0x60);
        else
            frame = self->parent;
        TransformPointBetweenFramesCG(0, frame, pos, &at);
        ((const Desc02*)self->desc)->m1D(self, &at);
    }
    ((const Desc02*)self->desc)->m1E(self, rot);
    ((const Desc02*)self->desc)->m20(self, vel);
    ((const Desc02*)self->desc)->m21(self, spin);
    if (self->f674 != 0) {
        Vec02* at;
        if (self->member5BC != 0) {
            BlastMessage msg;
            msg.kind = 9;
            msg.f30 = *(f32*)self->pad5C0;
            msg.f34 = self->f55C;
            msg.from = self;
            (*(ColliderMsgFn*)((u8*)*(void**)self->member5BC + 0x7C))((Collider*)self->member5BC, &msg);
            at = &self->v140;
        } else {
            SendPointEventToWorldListener(&self->v140, self->f55C);
            at = &self->v140;
        }
        BlastSound* snd = (BlastSound*)self->slot;
        if (snd != 0)
            StartSoundEffect(snd->id, 0, 0, at, snd->a, snd->b, snd->c, 0.0f, 0.0f, 0, 0);
        else
            StartSoundEffect(0x35, 0, 0, at, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
    if (self->count > 0) {
        f32 sa = ((ValueRange*)&self->f5E0)->Limit(((TimePolynomial*)&self->f5D0)->Eval(self->f55C));
        f32 sb = ((ValueRange*)&self->f600)->Limit(((TimePolynomial*)&self->f5F0)->Eval(self->f55C));
        for (s32 j = 0; j < self->count; j++) {
            Collider* o = (Collider*)self->arr[j];
            if (IsObjectAttached(o))
                continue;
            f32 x, y, z;
            f32 na = -sa;
            f32 nb = -sb;
            Vec02 v;
            Vec02 w;
            Vec02 rv;
            o->desc->m02(o);
            o->desc->m15(o, 0);
            SetTimedState(o, 1);
            ((const Desc02*)o->desc)->m1D(o, &self->v140);
            x = RandomFloatInRange(0.0f, sa * 2.5f);
            y = RandomFloatInRange(na, sa);
            z = RandomFloatInRange(na, sa);
            Vu0::Q(v) = Vu0::FromFloats(x, y, z);
            Vu0::Q(rv) = Vu0::Rotate(self->m110, Vu0::Q(v));
            ((const Desc02*)o->desc)->m20(o, &rv);
            f32 sx = RandomFloatInRange(nb, sb);
            f32 sy = RandomFloatInRange(nb, sb);
            f32 sz = RandomFloatInRange(nb, sb);
            Vu0::Q(w) = Vu0::FromFloats(sx, sy, sz);
            ((const Desc02*)o->desc)->m21(o, &w);
        }
    }
    self->desc->m03(self);
    TriggerScriptEvent(self, 2, 0, 0);
    self->flag60C = 0;
    self->f554 = D_00249D78;
}
