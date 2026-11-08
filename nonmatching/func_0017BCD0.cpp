// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 336/1880 (17.9%), checked 2026-11-08
#include "common.h"
#include "switched_collider.h"
#include "entry_queue.h"
#include "globals.h"
#include "shapes.h"
#include "placed_object.h"
#include "on_off_object.h"
#include "vu0.h"
// NEAR (2026-11-08, night-large4): StartNextQueueEntry. The twelve kinds in retail's block order,
// the frame's layout (the address-taken floats last; in kind 5 the velocity and the direction
// declared after the scalars whose slots they take) and the operations are retail's. Left: the
// address of the velocity passed to slot 32 (m20) is CSE'd with the slot of the drift's Scalar
// earlier in the block and kept in s7 across the calls, which takes one more saved register (s8
// for `sub`, retail s7) and shifts the frame by 0x10; passing another pointer there gives
// retail's frame. Vu0::Set for the velocity, Vec forms of the drift's update and a named 2 do
// not change it. Then a few vector registers of the MulAddX's (retail gives the weight its own
// register first).
f32 ArctangentOfRatio(f32 a, f32 b);
void TransformPointBetweenFrames(void* a, void* b, void* c, Vec02* d);
s32 IsObjectOfKind(BaseObject* n, s32 kind);
void GetNodeAnchorAndHeading(EntryQueue* self, BaseObject* n, Vec02* out, f32* outf);
void func_0017BB78(EntryQueue* self, BaseObject* target);
void ReplaceQueueOnOffObject(EntryQueue* self, OnOffObject* next);
extern f32 D_00263E34;

// The holder a player keeps at f23BC and f2208 for a kind 6 or 7 entry: the frame its point is
// put in, and an object whose slot 10 takes the point.
struct QueueTargetDriver;
struct QueueTargetDriverVt {
    u8 pad00[0x28];
    void (*m0A)(QueueTargetDriver* self, Vec02* p, s32 a, s32 b, s32 c, void* d, void* e);    // 0x28
};
struct QueueTargetDriver {
    const QueueTargetDriverVt* vt;
};
struct QueueTargetHolder {
    u8 pad00[0x18];
    void* frame;            // 0x18
    u8 pad1C[0x34 - 0x1C];
    QueueTargetDriver* driver;  // 0x34
};

BaseObject* FindFirstObjectById(void* host, s32 a1, s32 id, s32 ctx);
void PlaceAtArrivalPoint(BaseObject* self);
void BuildAxisAngleMatrix(const void* axis, f32 angle, void* out);
void SetPlayerState(Player* self, s32 state, s32 sub);
s32 ChooseNearbyPlayerTarget(Player* self, BaseObject* obj, s32* out);
void ComputePlayerJumpVelocity(Player* self, Vec02* out);
void func_0017FCC8(Player* self, Vec02* v);
void ComputeObjectMotionInFrame(void* a, s32 b, void* c, void* d, s32 e, s32 f, s32 g);
s32 SolveArrivalTimeAtHeight(Player* self, Vec02* a, Vec02* b, Vec02* c, Vec02* d, f32* out);
s32 CreateAnimationPlayerWithoutPresetTargets(BaseObject* t, void* self, s32 mode, void* out, f32 x, f32 y);
void func_001C61E0(Player* self, s32 n);
void TriggerScriptEvent(void* self, s32 a, s32 b, void* c);
void SetGameClockScale(f32 x);
extern f32 g_gameTime[];
extern const Vec02 g_unitZVector;

void StartNextQueueEntry(EntryQueue* self)
{
    s32 n = self->f40 + 1;
    self->f40 = n;
    if (n >= self->f34) {
        return;
    }
    QueueEntry* e = &((QueueEntry*)self->buffer)[n];
    Player* p = (Player*)self->f3C;
    BaseObject* obj = FindFirstObjectById(self->world, 0x104, e->id, self->f4C);
    switch (e->kind) {
    case 0:
        self->f4C = (s32)obj;
        break;
    case 1: {
        Vec02 pos;
        Mat02 rot;
        f32 heading;
        if (obj != 0 && IsObjectOfKind(obj, 0x74)) {
            PlaceAtArrivalPoint(obj);
            goto done;
        }
        GetNodeAnchorAndHeading(self, obj, &pos, &heading);
        p->v6A0 = pos;
        pos.z += 75.0f;
        p->v560 = pos;
        p->desc02()->m1D(p, &pos);
        p->f638 = heading;
        BuildAxisAngleMatrix(&g_unitZVector, heading, &rot);
        p->desc02()->m1E(p, &rot);
        p->desc02()->m20(p, (Vec02*)&D_00248D30);
        p->desc02()->m21(p, (Vec02*)&D_00248D30);
        SetPlayerState(p, 2, 2);
        p->f690 = 0;
        self->f48 = 0;
        break;
    }
    case 6: {
        self->f48 = e;
        if (obj == 0) {
            break;
        }
        if (IsObjectOfKind(obj, 0x7F) || IsObjectOfKind(obj, 0x6F) || IsObjectOfKind(obj, 0x3A)
            || IsObjectOfKind(obj, 0x70) || IsObjectOfKind(obj, 0x76)) {
            s32 t = ChooseNearbyPlayerTarget(p, obj, &p->f239C);
            if (t != -1) {
                SetPlayerState(p, 6, t);
            }
        }
        if (p->f2220 == 6 && p->f239C == 4) {
            Vec02 pos;
            GetNodeAnchorAndHeading(self, obj, &pos, 0);
            TransformPointBetweenFrames(0, ((QueueTargetHolder*)p->f23BC)->frame, &pos, &pos);
            QueueTargetDriver* d = ((QueueTargetHolder*)p->f23BC)->driver;
            if (d->vt->m0A == 0) {
                break;
            }
            d->vt->m0A(d, &pos, 0, 0, 0, &self->f60, 0);
        }
        goto done;
    }
    case 7: {
        Vec02 pos;
        self->f48 = e;
        GetNodeAnchorAndHeading(self, obj, &pos, 0);
        TransformPointBetweenFrames(0, ((QueueTargetHolder*)p->f2208)->frame, &pos, &pos);
        QueueTargetDriver* d = ((QueueTargetHolder*)p->f2208)->driver;
        if (d->vt->m0A == 0) {
            break;
        }
        d->vt->m0A(d, &pos, 0, 0, 0, 0, &self->f64);
        goto done;
    }
    case 4:
        if (obj != 0) {
            self->f48 = e;
            break;
        }
        goto done;
    case 5: {
        Vec02 start;
        Vec02 vel;
        Vec02 goal;
        Vec02 drift;
        Vec02* pv;
        Vec02* pg;
        f32 rise;
        self->f48 = e;
        s32 sub = 2;
        if (e->value != 0) {
            sub = 0;
        }
        if (obj == 0) {
            SetPlayerState(p, 2, sub);
            goto done;
        }
        start = p->pos;
        rise = 0.0f;
        p->f224C = 0;
        switch (p->f2220) {
        case 1:
            p->f224C = 2;
            break;
        case 3:
        case 7:
            p->f224C = 1;
            break;
        case 8:
            p->f224C = 4;
            break;
        }
        switch (e->value) {
        case 0:
            pv = &vel;
            vel = p->v150;
            break;
        case 1:
            pv = &vel;
            ComputePlayerJumpVelocity(p, pv);
            break;
        case 2: {
            pv = &vel;
            ComputePlayerJumpVelocity(p, pv);
            rise = -vel.z / p->gravity.z;
            Vu0::Q(goal) = Vu0::MulAddX(Vu0::Q(vel), Vu0::Q(p->gravity), Vu0::Scalar(rise));
            u128 h = Vu0::Scalar(rise * 0.5f);
            Vu0::Q(start) = Vu0::MulAddX2(Vu0::Q(start), Vu0::Q(vel), h, Vu0::Q(goal), h);
            drift = p->v150;
            p->v150 = goal;
            func_0017FCC8(p, pv);
            p->v150 = drift;
            break;
        }
        default:
            pv = &vel;
            break;
        }
        pg = &goal;
        GetNodeAnchorAndHeading(self, obj, pg, 0);
        ComputeObjectMotionInFrame(obj->parent, 0, pg, &drift, 0, 0, 0);
        Vu0::Q(goal) = Vu0::MulAddX(Vu0::Q(goal), Vu0::Q(drift), Vu0::Scalar(rise));
        if (IsObjectOfKind(obj, 0x76)) {
            goal.z += D_00263E34;
        }
        f32 left;
        if (SolveArrivalTimeAtHeight(p, &start, pv, pg, &drift, &left)) {
            SetPlayerState(p, 2, sub);
            Vu0::Q(goal) = Vu0::MulAddX(Vu0::Q(goal), Vu0::Q(drift), Vu0::Scalar(left));
            Vec02 v;
            Vu0::Set(v, Vu0::DivX(Vu0::Sub(Vu0::Q(goal), Vu0::Q(p->pos)), Vu0::Scalar(left + rise)));
            v.z = p->v150.z;
            p->desc02()->m20(p, &v);
            Vec02 d;
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(goal), Vu0::Q(p->pos));
            f32 h = ArctangentOfRatio(d.y, d.x);
            p->f630 = h;
            p->f638 = h;
        }
        p->f2250 = e->value10;
        break;
    }
    case 9: {
        void* player;
        if (obj == 0 || !IsObjectOfKind(obj, 0x83)) {
            break;
        }
        CreateAnimationPlayerWithoutPresetTargets(obj, 0, 0, &player, 0.0f, 1.0f);
        if (e->state != 0) {
            goto done;
        }
        self->f50 = player;
        break;
    }
    case 10:
        func_0017BB78(self, obj);
        goto done;
    case 8:
        switch (e->value) {
        case 2:
            func_001C61E0(p, 3);
            goto done;
        case 4:
            SetPlayerState(p, 2, 7);
            goto done;
        case 8:
            SetPlayerState(p, 0xA, 0x1F);
            goto done;
        }
        goto done;
    case 2: {
        s32* arg = &e->value;
        TriggerScriptEvent(self, 0x18, 1, &arg);
        goto done;
    }
    case 3:
        if (obj != 0 && !IsObjectOfKind(obj, 0x63)) {
            obj = 0;
        }
        ReplaceQueueOnOffObject(self, (OnOffObject*)obj);
        goto done;
    case 11:
        SetGameClockScale(e->valueF);
        break;
    }
done:
    self->f44 = g_gameTime[0];
}
