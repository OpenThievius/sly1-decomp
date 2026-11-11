// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x17B998 to 0x17D248: the entry queue, class 0x8F (include/entry_queue.h), and
// the adders of each kind of entry. Its name is ours, after the class.
#include "common.h"
#include "switched_collider.h"
#include "gauge_mode_object.h"
#include "countdown_collider.h"
#include "entry_queue.h"
#include "globals.h"
#include "object_link.h"
#include "message_body.h"
#include "object_event.h"
#include "shapes.h"
#include "screen_element.h"
#include "point_object.h"
#include "collider.h"
#include "placed_object.h"
#include "path_curve_object.h"
#include "on_off_object.h"
#include "asm_func.h"
#include "vu0.h"
#include "pad_record.h"
#include "camera.h"

// The entry queue (class 0x8F): its set-up, the functions that start, advance, bind and fill it,
// and the script commands that add entries. Its .rodata (0x24B000-0x24B054) is the jump tables
// of func_0017BCD0 and func_0017C428; its .data (0x263E34-0x263E48) the five floats its VU0
// functions read; its .bss the spare entry D_002BE478.

f32 D_00263E34 = -200.0f;
f32 D_00263E38 = 25.0f;
f32 D_00263E3C = 15.0f;
f32 D_00263E40 = 0.200000003f;
f32 D_00263E44 = 0.5f;

void InitObject(void* self);
void* AllocateFrontMemory(int size);

void InitEntryQueue(EntryQueue* self)
{
    InitObject(self);
    self->buffer = AllocateFrontMemory(0xA00);
    self->flag68 = 1;
}

s32 IsObjectOfKind(BaseObject* n, s32 kind);
void ConvertPositionToWorld(BaseObject* n, Vec02* out);
s32 GetObjectWorldPosition(BaseObject* n, Vec02* out);
s32 GetObjectWorldRotation(BaseObject* n, Vec02* out);
f32 ArctangentOfRatio(f32 a, f32 b);
void TransformPointBetweenFrames(void* a, void* b, void* c, Vec02* d);
void TransformDirectionBetweenFrames(void* a, void* b, Vec02* c, Vec02* d);

void GetNodeAnchorAndHeading(EntryQueue* self, BaseObject* n, Vec02* out, f32* outf)
{
    Vec02 v;
    Vec02 a;
    Vec02 b;
    Vec02 c;
    Player* s1 = (Player*)self->f3C;
    f32 r;

    if (n == 0)
    {
        goto tail;
    }
    if (IsObjectOfKind(n, 0x7E))
    {
        ConvertPositionToWorld(n, &v);
        r = s1->f638;
    }
    else if (IsObjectOfKind(n, 0x73))
    {
        GetObjectWorldPosition(n, &v);
        GetObjectWorldRotation(n, &a);
        r = ArctangentOfRatio(a.y, a.x);
    }
    else if (IsObjectOfKind(n, 0x6E))
    {
        TransformPointBetweenFrames(0, n->parent, &s1->pos, &a);
        {
            PathCurve* curve = ((PathCurveObject*)n)->curve;
            void (*fn)(void*, Vec02*, s32, Vec02*, Vec02*, s32, s32) =
                (void (*)(void*, Vec02*, s32, Vec02*, Vec02*, s32, s32))curve->vt->m10;
            if (fn)
            {
                fn(curve, &a, 0, &a, &b, 0, 0);
            }
        }
        TransformPointBetweenFrames(n->parent, 0, &a, &v);
        TransformDirectionBetweenFrames(n->parent, 0, &b, &c);
        r = ArctangentOfRatio(c.y, c.x);
    }
    else if (IsObjectOfKind(n, 2))
    {
        v = ((PlacedObject*)n)->v140;
        r = ArctangentOfRatio(((f32*)n)[0x114 / 4], ((f32*)n)[0x110 / 4]);
    }
    else
    {
    tail:
        v = s1->pos;
        v.z -= 75.0f;
        r = s1->f638;
    }
    if (out)
    {
        *out = v;
    }
    if (outf)
    {
        *outf = r;
    }
}

// The part of the player func_0017BB78 aims: a position, a time, the aim and the mark it leaves.
struct Aim_0017BB78 {
    u8 pad0[0x100];
    Vec02 pos;              // 0x100
    u8 pad110[0x554 - 0x110];
    s32 f554;               // 0x554
    u8 pad558[0x560 - 0x558];
    Vec02 aim;              // 0x560
    u8 pad570[0x2530 - 0x570];
    Vec02 mark;             // 0x2530
};

void SetEntryQueueTargetNode(EntryQueue* self, BaseObject* target)
{
    Aim_0017BB78* p = (Aim_0017BB78*)self->f3C;
    if (self->f54 != 0) {
        Vu0::Q(p->mark) = Vu0::Sub(Vu0::Q(p->aim), Vu0::Q(p->pos));
        p->f554 = 0;
        p->mark.z = 0.0f;
        self->f54 = 0;
    }
    if (target != 0) {
        p->f554 = 1;
        GetNodeAnchorAndHeading(self, target, &p->aim, 0);
        p->aim.z += 125.0f;
        p->mark = D_00248D30;
        self->f54 = target;
    }
}


void SetOnOffObjectForcedState(void* p, s32 n);
s32 IsObjectAttached(void* p);

void ReplaceQueueOnOffObject(EntryQueue* self, OnOffObject* next)
{
    if (self->f58 != 0) {
        SetOnOffObjectForcedState(self->f58, -1);
        self->f58->f2D0 = 0;
        if (self->f5C != 0) {
            self->f58->desc->m03(self->f58);
        }
        self->f58 = 0;
    }
    if (next != 0) {
        self->f58 = next;
        s32 isNull = IsObjectAttached(next) == 0;
        self->f5C = isNull;
        if (isNull != 0) {
            next->desc->m02(next);
        }
        next->f2D0 = self->f3C;
        SetOnOffObjectForcedState(next, 1);
    }
}

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

void* FindFirstObjectById(void* world, s32 kind, s32 id, s32 from);
void PlaceAtArrivalPoint(BaseObject* self);
void BuildAxisAngleMatrix(const void* axis, f32 angle, void* out);
void SetPlayerState(Player* self, s32 state, s32 sub);
s32 ChooseNearbyPlayerTarget(Player* self, BaseObject* obj, s32* out);
void ComputePlayerJumpVelocity(Player* self, Vec02* out);
void ComputeUpwardBoostVelocityUnitSlope(Player* self, Vec02* v);
void ComputeObjectMotionInFrame(void* a, s32 b, void* c, void* d, s32 e, s32 f, s32 g);
s32 SolveArrivalTimeAtHeight(Player* self, Vec02* a, Vec02* b, Vec02* c, Vec02* d, f32* out);
void CreateAnimationPlayerWithoutPresetTargets(BaseObject* t, void* self, s32 mode, void* out, f32 x, f32 y); // stays void: retail returns a value, but declared so func_0017BCD0 differs in registers
void SetPlayerAimMode(Player* self, s32 n);
void TriggerScriptEvent(void* self, s32 kind, s32 a, s32 b);
void SetGameClockScale(f32 x);
extern f32 g_gameTime;

void StartNextQueueEntry(EntryQueue* self)
{
    s32 n = self->f40 + 1;
    self->f40 = n;
    if (n >= self->f34) {
        return;
    }
    QueueEntry* e = &((QueueEntry*)self->buffer)[n];
    Player* p = (Player*)self->f3C;
    BaseObject* obj = (BaseObject*)FindFirstObjectById(self->world, 0x104, e->id, self->f4C);
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
        f32 rise;
        self->f48 = e;
        s32 sub = e->value != 0 ? 0 : 2;
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
            vel = p->v150;
            break;
        case 1:
            ComputePlayerJumpVelocity(p, &vel);
            break;
        case 2: {
            ComputePlayerJumpVelocity(p, &vel);
            rise = -vel.z / p->gravity.z;
            Vu0::Q(goal) = Vu0::MulAddX(Vu0::Q(vel), Vu0::Q(p->gravity), Vu0::Scalar(rise));
            u128 h = Vu0::Scalar(rise * 0.5f);
            Vu0::Q(start) = Vu0::MulAddX2(Vu0::Q(start), Vu0::Q(vel), h, Vu0::Q(goal), h);
            drift = p->v150;
            p->v150 = goal;
            ComputeUpwardBoostVelocityUnitSlope(p, &vel);
            p->v150 = drift;
            break;
        }
        default:
            break;
        }
        GetNodeAnchorAndHeading(self, obj, &goal, 0);
        ComputeObjectMotionInFrame(obj->parent, 0, &goal, &drift, 0, 0, 0);
        Vu0::Q(goal) = Vu0::MulAddX(Vu0::Vec::Of(goal), Vu0::Vec::Of(drift), Vu0::Vec::Scalar(rise)).q;
        if (IsObjectOfKind(obj, 0x76)) {
            goal.z += D_00263E34;
        }
        f32 left;
        if (SolveArrivalTimeAtHeight(p, &start, &vel, &goal, &drift, &left)) {
            SetPlayerState(p, 2, sub);
            Vu0::Q(goal) = Vu0::MulAddX(Vu0::Q(goal), Vu0::Q(drift), Vu0::Scalar(left));
            Vec02 v;
            Vu0::Set(v, Vu0::DivX(Vu0::Sub(Vu0::Q(goal), Vu0::Q(p->pos)), Vu0::Scalar(left + rise)));
            v.z = p->v150.z;
            p->desc02()->m20(p, &v);
            Vec02 d;
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(goal), Vu0::Q(p->pos));
            f32 h = ArctangentOfRatio(d.y, d.x);
            p->f638 = h;
            p->f630 = h;
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
        SetEntryQueueTargetNode(self, obj);
        goto done;
    case 8:
        switch (e->value) {
        case 2:
            SetPlayerAimMode(p, 3);
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
        TriggerScriptEvent(self, 0x18, 1, (s32)&arg);
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
    self->f44 = g_gameTime;
}

extern f32 g_gameTime;
void* FindFirstObjectById(void* world, s32 kind, s32 id, s32 from);
void StopAnimationPlayer(void* p);
void SetPlayerState(Player* self, s32 a, s32 b);

s32 CheckQueueEntryDone(EntryQueue* self, QueueEntry* e)
{
    s32 done;
    Player* pl = (Player*)self->f3C;
    void* obj = FindFirstObjectById(pl->world, 0x104, e->id, self->f4C);
    switch (e->kind) {
    default:
        done = 1;
        break;
    case 4:
        done = e->valueF < g_gameTime - self->f44;
        break;
    case 5:
        done = pl->f2220 != 2;
        break;
    case 6: {
        if (obj == 0) {
            done = 1;
            break;
        }
        Vec02 pos;
        GetNodeAnchorAndHeading(self, (BaseObject*)obj, &pos, 0);
        Vu0::Vec gap = Vu0::Sub(Vu0::Vec::Of(pl->v140), Vu0::Vec::Of(pos));
        done = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(gap, gap))) < D_00263E38;
        break;
    }
    case 7:
        done = __builtin_fabsf(pl->f2410 - self->f64) < D_00263E3C;
        break;
    case 9: {
        void* p = self->f50;
        done = p == 0 || ((f32*)p)[6] == 0.0f;
        if (done && p != 0) {
            StopAnimationPlayer(p);
            self->f50 = 0;
        }
        break;
    }
    case 8:
        switch (e->value) {
        case 2:
            done = pl->f223C == -1;
            break;
        case 4:
            done = pl->f2220 != 2;
            break;
        case 8:
            done = pl->f2220 != 10;
            break;
        default:
            done = 1;
            break;
        }
        break;
    case 12:
        if (pl->f2220 == 2 && (u32)(pl->f2228 - 12) < 2) {
            done = 0;
        } else if (pl->f2220 == 6 && (u32)pl->f239C < 2) {
            SetPlayerState(pl, 0, -1);
            done = 1;
        } else {
            done = 1;
        }
        break;
    }
    return done;
}

void StartNextQueueEntry(EntryQueue* self);

void AdvanceEntryQueue(EntryQueue* self)
{
    if (self->f40 < 0 && self->f34 > 0)
        StartNextQueueEntry(self);
    while (self->f40 < self->f34) {
        QueueEntry* entry = &((QueueEntry*)self->buffer)[self->f40];
        if (entry->state == 0 && !CheckQueueEntryDone(self, entry))
            break;
        StartNextQueueEntry(self);
    }
    if (self->f48 && CheckQueueEntryDone(self, (QueueEntry*)self->f48))
        self->f48 = 0;
}

s32 ChoosePlayerTargetByCost(Player* self, void* target);
f32 WrapAngle(f32 a);
void ProjectPointToCamera(Camera* self, Vec02* in, Vec02* out);
extern f32 g_gameTime;
extern f32 D_00274F14;

struct TrackShape_17C718;
struct TrackShapeDesc_17C718 {
    void* m0;
    void (*m1)(TrackShape_17C718* self, f32 t, Vec02* pos, Vec02* dir);   // 0x04
    void (*m2)(TrackShape_17C718* self, f32 t, Vec02* pos, s32 a);        // 0x08
    u8 pad0C[0x1C - 0x0C];
    f32 (*m7)(TrackShape_17C718* self);                                   // 0x1C: the length
    f32 (*m8)(TrackShape_17C718* self);                                   // 0x20: the length
};
struct TrackShape_17C718 { TrackShapeDesc_17C718* desc; u8 pad04[4]; s32 looped; };
struct TrackRecord_17C718 { u8 pad00[0x18]; void* frame; u8 pad1C[0x34 - 0x1C]; TrackShape_17C718* shape; };

void DrivePlayerFromEntryQueue(EntryQueue* self, PadRecord* pad)
{
    Vec02 a;
    Vec02 b;
    Vec02 c;
    Vec02 d;
    Vec02 dir;
    f32 heading;
    QueueEntry* e = (QueueEntry*)self->f48;
    Player* p = (Player*)self->f3C;
    if (e == 0) {
        p->f634 = 0.0f;
        if (p->f2220 == 6) {
            pad->keyA8 |= 0x20;
        }
        return;
    }
    {
        BaseObject* o = (BaseObject*)FindFirstObjectById(p->world, 0x104, e->id, self->f4C);
        switch (e->kind) {
        case 4:
            if (o != 0) {
                GetNodeAnchorAndHeading(self, o, 0, &heading);
                p->f630 = p->f638 = heading;
            }
            p->f634 = 0.0f;
            if (p->f2220 == 6) {
                pad->keyA8 |= 0x20;
            }
            return;
        case 5:
            if (p->f2220 == 2 && o != 0) {
                if ((p->f2228 == 2 && D_00263E40 < g_gameTime - p->f222C) || (p->f2228 == 3 && D_00263E44 < g_gameTime - p->f222C)) {
                    if (IsObjectOfKind(o, 0x81) || IsObjectOfKind(o, 0x71) || IsObjectOfKind(o, 0x6F) || IsObjectOfKind(o, 0x7F) || IsObjectOfKind(o, 0x70) || IsObjectOfKind(o, 0x76)) {
                        SetPlayerState(p, 2, ChoosePlayerTargetByCost(p, o));
                    }
                }
            }
            if (e->value == 2 && p->f2228 == 2 && p->f2498 != 0) {
                SetPlayerState(p, 2, 3);
            }
            p->f634 = 0.0f;
            return;
        case 6:
            if (o != 0) {
                if (p->f2220 == 6 && p->f239C == 4) {
                    TrackRecord_17C718* r = (TrackRecord_17C718*)p->f23BC;
                    TrackShape_17C718* s = r->shape;
                    void* frame = r->frame;
                    if (s->desc->m1 != 0) {
                        s->desc->m1(s, p->f23C0, &a, &b);
                    }
                    TransformPointBetweenFrames(frame, 0, &a, &c);
                    TransformDirectionBetweenFrames(frame, 0, &b, &d);
                    d.z = 0.0f;
                    Vu0::Set(d, Vu0::NormalizeOr(Vu0::Q(d), Vu0::Q(g_unitXVector)));
                    s32 flip = 0;
                    p->f630 = ArctangentOfRatio(d.y, d.x);
                    s = ((TrackRecord_17C718*)p->f23BC)->shape;
                    if (s->looped != 0) {
                        f32 fwd;
                        f32 back;
                        if (self->f60 < p->f23C0) {
                            fwd = p->f23C0 - self->f60;
                            back = s->desc->m7(s) + self->f60 - p->f23C0;
                        } else {
                            back = self->f60 - p->f23C0;
                            fwd = s->desc->m7(s) + p->f23C0 - self->f60;
                        }
                        if (fwd < back) {
                            flip = 1;
                        }
                    } else if (self->f60 < p->f23C0) {
                        flip = 1;
                    }
                    if (flip) {
                        p->f630 = WrapAngle(p->f630 + 3.14159274f);
                    }
                } else {
                    GetNodeAnchorAndHeading(self, o, &a, 0);
                    Vu0::Q(b) = Vu0::Sub(Vu0::Q(a), Vu0::Q(p->v140));
                    p->f630 = ArctangentOfRatio(b.y, b.x);
                }
            }
            p->f634 = __builtin_fabsf(e->valueF);
            if (p->f2220 == 6 && p->f239C < 2 && p->f239C >= 0) {
                pad->keyA8 |= 0x20;
            }
            return;
        case 7: {
            TrackShape_17C718* s = ((TrackRecord_17C718*)p->f2208)->shape;
            if (s->desc->m2 != 0) {
                s->desc->m2(s, p->f2410 + D_00274F14, &a, 0);
                s = ((TrackRecord_17C718*)p->f2208)->shape;
                if (s->desc->m2 != 0) {
                    s->desc->m2(s, p->f2410 - D_00274F14, &b, 0);
                }
            }
            TransformPointBetweenFrames(((TrackRecord_17C718*)p->f2208)->frame, 0, &a, &a);
            TransformPointBetweenFrames(((TrackRecord_17C718*)p->f2208)->frame, 0, &b, &b);
            ProjectPointToCamera(g_camera, &a, &c);
            ProjectPointToCamera(g_camera, &b, &d);
            Vu0::Q(dir) = Vu0::Sub(Vu0::Q(c), Vu0::Q(d));
            dir.z = 0.0f;
            Vu0::Set(dir, Vu0::NormalizeOr(Vu0::Q(dir), Vu0::Q(g_unitYVector)));
            s32 flip = 0;
            p->f630 = ArctangentOfRatio(dir.y, dir.x);
            pad->f40 = dir.x;
            pad->f44 = dir.y;
            s = ((TrackRecord_17C718*)p->f2208)->shape;
            if (s->looped != 0) {
                f32 fwd;
                f32 back;
                if (self->f64 < p->f2410) {
                    fwd = p->f2410 - self->f64;
                    back = s->desc->m8(s) + self->f64 - p->f2410;
                } else {
                    back = self->f64 - p->f2410;
                    fwd = s->desc->m8(s) + p->f2410 - self->f64;
                }
                if (fwd < back) {
                    flip = 1;
                }
            } else if (self->f64 < p->f2410) {
                flip = 1;
            }
            if (flip) {
                p->f630 = WrapAngle(p->f630 + 3.14159274f);
                pad->f40 = -pad->f40;
                pad->f44 = -pad->f44;
            }
            p->f634 = 1.0f;
            return;
        }
        }
    }
}

void AdvanceEntryQueue(EntryQueue* self);

s32 IsEntryQueueRunning(EntryQueue* self)
{
    AdvanceEntryQueue(self);
    if (self->f34 > 0) {
        return self->f40 < self->f34;
    }
    return 0;
}

void UnbindEntryQueue(EntryQueue* self);

void ResetEntryQueue(EntryQueue* self)
{
    if (self->f3C != 0) {
        UnbindEntryQueue(self);
        self->f34 = 0;
    } else {
        self->f34 = 0;
    }
    self->f40 = 0;
}

void TriggerScriptEvent(void* self, s32 kind, s32 a, s32 b);
s32 SetPadSelectFlags(s32 a);
void AcquirePadSelectFlag(void* a);


void BindEntryQueueToObject(void* a0, void* a1)
{
    EntryQueue* self = (EntryQueue*)a0;
    ((Player*)a1)->entryQueue = self;
    self->f3C = a1;
    self->f40 = -1;
    TriggerScriptEvent(self, 0x17, 0, 0);
    if (self->flag68 != 0) {
        SetPadSelectFlags(4);
        AcquirePadSelectFlag(self->world);
    }
}


void SetGameClockScale(f32 x);
void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);
void ClearPadSelectFlags(s32 n);
void ReleasePadSelectFlag(void* p);

void UnbindEntryQueue(EntryQueue* self)
{
    if (self->f3C != 0) {
        ReplaceQueueOnOffObject(self, 0);
        SetEntryQueueTargetNode(self, 0);
        if (self->f50 != 0) {
            StopAnimationPlayer(self->f50);
            self->f50 = 0;
        }
        SetGameClockScale(1.0f);
        self->f40 = self->f34;
        self->f4C = 0;
        self->f48 = 0;
        ((Player*)self->f3C)->entryQueue = 0;
        self->f3C = 0;
        TriggerScriptEvent(self, 25, 0, 0);
        if (self->flag68 != 0) {
            ClearPadSelectFlags(4);
            ReleasePadSelectFlag(self->world);
        }
    }
}

// The entry AddQueueEntry hands out once the queue's 0x80 entries are used (0x14 bytes).
static u8 D_002BE478[0x14];
void* FillMemory(void* p, s32 value, s32 size);

void* AddQueueEntry(EntryQueue* pool, s32 a, s32 b, s32 c)
{
    if (pool->f34 >= 0x80) {
        return D_002BE478;
    }
    s32 n = pool->f34;
    u8* e = (u8*)pool->buffer + n * 0x14;
    pool->f34 = n + 1;
    FillMemory(e, 0, 0x14);
    s32* f = (s32*)e;
    f[0] = a;
    f[1] = b;
    f[2] = c;
    return e;
}

void* AddQueueEntryKind0(void* self, s32 b)
{
    return AddQueueEntry((EntryQueue*)self, 0, b, 1);
}

void* AddQueueEntryKind1(void* self, s32 b)
{
    return AddQueueEntry((EntryQueue*)self, 1, b, 1);
}

void* AddQueueEntryKind10(void* self, s32 b)
{
    return AddQueueEntry((EntryQueue*)self, 10, b, 1);
}


void AddQueueEntryKind2(void* self, s32 value)
{
    QueueEntry* o = (QueueEntry*)AddQueueEntry((EntryQueue*)self, 2, -1, 1);
    o->value = value;
}

void* AddQueueEntryKind3(void* self, s32 value)
{
    return AddQueueEntry((EntryQueue*)self, 3, value, 1);
}

void AddQueueEntryKind4(void* self, s32 a, f32 value)
{
    QueueEntry* o = (QueueEntry*)AddQueueEntry((EntryQueue*)self, 4, a, 0);
    o->valueF = value;
}

void* AddQueueEntryKind9(void* self, s32 value, s32 c)
{
    return AddQueueEntry((EntryQueue*)self, 9, value, c);
}

void AddQueueEntryKind5(void* self, s32 b, s32 c, s32 d, s32 e)
{
    QueueEntry* o = (QueueEntry*)AddQueueEntry((EntryQueue*)self, 5, b, e);
    o->value = c;
    o->value10 = d;
}

void AddQueueEntryKind6(void* self, s32 a, s32 b, f32 value)
{
    QueueEntry* o = (QueueEntry*)AddQueueEntry((EntryQueue*)self, 6, a, b);
    o->valueF = value;
}

void AddQueueEntryKind7(void* self, s32 b, s32 c, f32 value)
{
    QueueEntry* o = (QueueEntry*)AddQueueEntry((EntryQueue*)self, 7, b, c);
    o->valueF = value;
}

void AddQueueEntryKind8(void* self, s32 b, s32 c, s32 d)
{
    QueueEntry* o = (QueueEntry*)AddQueueEntry((EntryQueue*)self, 8, b, d);
    o->value = c;
}

void AddQueueEntryKind11(void* self, f32 value)
{
    QueueEntry* o = (QueueEntry*)AddQueueEntry((EntryQueue*)self, 11, -1, 1);
    o->valueF = value;
}

s32 AddQueueEntryKind12(void* self)
{
    return (s32)AddQueueEntry((EntryQueue*)self, 0xC, -1, 0);
}
