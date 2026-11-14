// SPDX-License-Identifier: AGPL-3.0-or-later
// From 0x1D62E0 to 0x1D8E40: classes 0x07 and 0x3F, the output buffer and the first of class
// 0x19's functions. Its .data runs from 0x275140 to 0x2754FC; its .rodata is the "%s" of
// func_001D72C8 and the float of func_001D8470 (0x24DC90 to 0x24DC98). Its start is an edge retail
// proves. Its end is a choice: the cut before path_follower_helpers.cpp, made on loop.c's threshold (that
// file's head), which no boundary signal shows. Between the two it could still be several files.
// Its name is ours, after its largest family, the path follower's start and steps (class 0x19),
// whose other functions follow in path_follower_helpers.cpp and world.cpp.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "mul_rotation.h"
#include "pad_record.h"
#include "deferred_request.h"
#include "list_iter.h"
#include "switched_collider.h"
#include "state_trigger.h"
#include "child_group_object.h"
#include "screen_element.h"
#include "object_link.h"
#include "object_message.h"
#include "owner_message.h"
#include "output_buffer.h"
#include "shapes.h"
#include "globals.h"
#include "world.h"
#include "queued_call.h"
#include "effect.h"
#include "game_progress.h"
#include "buffered_stream.h"
#include "value_range.h"
#include "script_value.h"
#include "cone_volume.h"
#include "redirect_object.h"
#include "font.h"
#include "level_entry.h"
#include "message_body.h"
#include "path_curve_object.h"
#include "state_notifier.h"
#include "fpu.h"
#include "scope_marker.h"
#include "object_finder.h"
#include "functions/base_object.h"
#include "functions/child_group_object.h"
#include "functions/collider.h"
#include "functions/formatted_output.h"
#include "functions/game_progress.h"
#include "functions/group_marker.h"
#include "functions/heap.h"
#include "functions/iop_file_client.h"
#include "functions/matrix.h"
#include "functions/oscillator.h"
#include "functions/path_curve.h"
#include "functions/placed_object.h"
#include "functions/player.h"
#include "functions/player_request.h"
#include "functions/state_walker.h"
#include "functions/switched_collider.h"
#include "functions/warp_menu.h"
#include "functions/world.h"
#include "functions/zone_collider.h"
struct ContactPair;
struct PlacedObject;

struct BaseObject;

struct Mat02;


extern f32 g_gameClock[];

typedef void (*VFnB)(void* self, void* arg);





extern "C" void* FillMemory(void* p, s32 value, s32 size);



void FlushOutputBuffer(OutputBuffer* self);

extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
struct StateGraph;
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

extern "C" void* FillMemory(void* p, s32 value, s32 size);

extern "C" void* FillMemory(void* p, s32 value, s32 size);

f32 GetWrappedDifference(f32 x, f32 lim, f32 base);



struct WalkerHolder { u8 pad[0x48]; void* f48; };


extern f32 g_gameClock[];

struct RampProfile;
f32 ApproachValueWithRamp(RampProfile* k, f32* out, f32 x, f32 y, f32 z);



void UpdatePathFollowerPace(PathFollower* self);
void AdvancePathFollowerAlongPath(PathFollower* self, s32* out);
void ComputePathFollowerHeadingTarget(PathFollower* self);
void SteerPathFollower(PathFollower* self);


// A quadratic by its three coefficients (func_001D8578).
struct QuadraticCurve {
    f32 c[3];
    f32 Eval(f32 t) { return c[0] + t * (c[1] + t * c[2]); }
};

struct WorldRecord { u8 b; };

#define SUB(off) ((WorldRecord*)((u8*)self + (off)))

extern f32 g_steerAngleGain;
extern f32 g_steerAngleLimit;
extern f32 g_frameDt;
extern f32 g_steerAngleRamp[3];
extern "C" f32 ArctangentOfRatio(f32 y, f32 x); f32 WrapAngle(f32 a); f32 ClampToMagnitude(f32 a, f32 b); f32 ApproachAngleWithRamp(void* p, void* out, f32 a, f32 b, f32 c);

typedef int Quadword __attribute__((mode(TI)));

void *StoreFloatAsQuadword(u128* out, f32 f);
void* CopyQuadword(u128* out, void* src);
void* StoreQuadword(u128* out, u128 v);

extern "C" void* FillMemory(void* p, s32 value, s32 size);

extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

extern f32 g_gameClock[];
void InitOwnerMessage(OwnerMessage* self, s32 mode, void* owner);

extern f32 g_gameClock[];


extern f32 g_gameClock[];

float g_markerRingTintCurve[4] = {1.0f, 0.0f, -0.75f, 0.0f};
float g_markerRingPulseCurve[4] = {0.699999988f, 0.300000012f, 0.0f, 0.0f};
float g_requestFinishMinSpeedZ = 650.0f;
float g_groundProbeTopOffset = 100.0f;
float g_groundProbeBottomOffset = -100.0f;
float g_groundProbeLift = 50.0f;
float g_attachedContactDamping[2] = {-10.0f, 0.0f};
float g_attachedContactRamp[4] = {250.0f, 0.0f, 1.0f, 4500.0f};
float g_standInSpinRate = 10.0f;
float g_standInPushSpeed = 50.0f;
float g_standInRotationPull[4] = {0.0f, 45.0f, 0.0f, 0.0f};
float g_standInRotationTurn[4] = {0.0f, 2.5f, 0.0f, 0.0f};
float g_standInPositionTurn[4] = {0.0f, 7.5f, 0.0f, 0.0f};
float g_standInAgeCurve[4] = {0.0f, 4.0f, 0.0f, 0.0f};
float g_pathLookAhead = 850.0f;
s32 D_002751D4 = 60;
float g_pathFollowerRampTime = 1.25f;
float D_002751DC = 0.75f;
float g_leanCurve[4] = {1.35000002f, 0.0f, -0.349999994f, 0.0f};
float g_leanRange[4] = {1.0f, 1.35000002f, 0.0f, 0.0f};
float g_gripScaleCurve[4] = {1.5f, 0.0f, -0.5f, 0.0f};
float g_gripScaleRange[4] = {1.0f, 1.5f, 0.0f, 0.0f};
float g_maxAccelCurve[4] = {9000.0f, 0.0f, -9000.0f, 0.0f};
float g_maxAccelRange[4] = {0.0f, 9000.0f, 0.0f, 0.0f};
float g_pathFollowerFadeCurve[4] = {1.0f, -1.0f, 0.0f, 0.0f};
f32 D_00275250[16] = {
    1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f
};
f32 g_pathFollowerInitV620[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
ObjectLink g_pathFollowerLinks[20] = {
    { 4, 0x416, 0x6B0 }, { 4, 0x417, 0x710 }, { 4, 0x418, 0x770 }, { 4, 0x419, 0x7D0 },
    { 0, 0x41A, 0x6B8 }, { 0, 0x41B, 0x718 }, { 0, 0x41C, 0x778 }, { 0, 0x41D, 0x7D8 },
    { 6, 0x41E, 0x6B4 }, { 6, 0x41F, 0x714 }, { 6, 0x420, 0x774 }, { 6, 0x421, 0x7D4 },
    { 0, 0x422, 0x690 }, { 2, 0x428, 0xB28 }, { 2, 0x429, 0xB2C }, { 2, 0x42A, 0xB44 },
    { 2, 0x42B, 0xB4C }, { 0x22, 0x423, 0xB14 }, { 0x20, 0x424, 0xB18 }, { 0x20, 0x425, 0xB1C }
};
float g_uprightSteerDelay = 1.0f;
f32 g_uprightRampTime = 2.0f;
Vec02 g_uprightPull = { 0.0f, 30.0f, 3.0f, 0.0f };
float g_wheelSlipCurve[4] = {0.0f, 0.00999999978f, 0.0f, 0.0f};
float g_wheelSlipRange[2] = {0.0f, 45.0f};
float g_suspensionDampingGain = 15.0f;
float g_suspensionSpringGain = 90.0f;
float g_suspensionDampingCurve[4] = {0.0f, 0.25f, 0.75f, 0.0f};
float g_suspensionSpringCurve[4] = {0.0f, 0.0f, 1.0f, 0.0f};
float g_airSteerCurve[4] = {0.0f, 0.0f, 1.0f, 0.0f};
float g_airSteerTurn[4] = {0.0f, 2.5f, 0.25f, 0.0f};
float g_driveForceFull = 6000.0f;
float g_gripLimitCap = 11250.0f;
float g_steerRateGain = 7.0f;
float g_steerSpeedCap = 2500.0f;
f32 g_steerSpeedCurve[4] = { 1.0f, -1.0f, 0.0f, 0.0f };
f32 g_headingAlignCurve[4] = { 0.5f, 1.0f, 0.0f, 0.0f };
f32 g_headingAlignRange[2] = { 0.5f, 1.0f };
f32 g_speedRampBelow[4] = { 4000.0f, 0.0f, 2.0f, 0.0f };
f32 g_speedRampAbove[6] = { 2000.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f };
f32 g_wheelSpinCurve[4] = { 0.0f, 0.0333333313f, 0.0f, 0.0f };
f32 g_wheelSpinRange[2] = { 0.0f, 50.0f };
f32 g_forceLeverDrop = -10.0f;
f32 g_paceRamp[4] = { 0.05f, 0.0f, 0.25f, 0.0f };
f32 g_paceChangeInterval[4] = { 1.5f, 2.5f, 0.0f, 0.0f };
f32 g_avoidSpanCurve[4] = { 1000.0f, -0.5f, 0.0f, 0.0f };
f32 g_avoidSpanRange[2] = { 0.0f, 625.0f };
ValueRange g_lateralOffsetRange = { -1300.0f, 1300.0f };
f32 g_lateralOffsetRamp[3] = { 1125.0f, 0.0f, 0.100000001f };
f32 g_turnProbeLength = 750.0f;
f32 g_cornerSpeedFactor[2] = { 1.0f, 0.0f };
f32 g_steerAngleRamp[3] = { 8.0f, 0.0f, 0.25f };
f32 g_steerAngleLimit = 0.7f;
f32 g_steerAngleGain = 0.5f;

struct RingSource {
    u8 pad00[0x40];
    Vec02 v40;              // 0x40
    u8 pad50[0x30];
    Vec02 v80;              // 0x80
};

typedef void (*RingDrawFn)(void* request);
extern "C" f32 Cosine(f32 x);
extern Rgba4 D_002623E0[];

struct RingClamp {
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        if (x < lo) {
            return lo;
        }
        if (hi < x) {
            return hi;
        }
        return x;
    }
};

void QueuePlayerMarkerRingDraw(Player* self, RingSource* a, void* b)
{
    s32 state = self->subState;
    if (state >= 0x25 && (state < 0x27 || (state == 0x37 && (MaskWorldBitsBySave() & 0x400) != 0))) {
        DeferredRequest f;
        (void)FillMemory(&f, 0, 0x80);
        f.f04 = Vu0::ToFloat(Vu0::Dot(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(a->v40)), Vu0::Q(a->v80)));
        f.group = 0xD;
        f.arg = self;
        switch (self->subState) {
        case 0x37:
            f.callback = (void*)DrawPlayerMarkerRing3;
            break;
        case 0x25:
            f.callback = (void*)DrawPlayerMarkerRing1;
            break;
        case 0x26:
            f.callback = (void*)DrawPlayerMarkerRing2;
            break;
        }
        QueueDeferredRequest(&f);
    }
    {
        Rgba4 c;
        u8 from[4];
        *(u32*)from = 0x800000A0;
        if (self->pulseActive != 0) {
            f32 t;
            if (self->state != 4) {
                t = (g_gameClock[1] - self->pulseFadeStart) / self->pulseFadeDuration;
            } else {
                t = 0.0f;
            }
            f32 s = Cosine((g_gameClock[1] - self->pulseStartTime) * 10.0f);
            f32 p = g_markerRingTintCurve[0] + t * (g_markerRingTintCurve[1] + t * g_markerRingTintCurve[2]);
            f32 x = RingClamp::Of(p, g_unitRange.lo, g_unitRange.hi);
            f32 q = g_markerRingPulseCurve[0] + s * (g_markerRingPulseCurve[1] + s * g_markerRingPulseCurve[2]);
            f32 y = RingClamp::Of(q, g_unitRange.lo, g_unitRange.hi);
            f32 w = x * y;
            f32 u = 1.0f - w;
            c.r = (u8)(u * D_002623E0[0].r + w * from[0]);
            c.g = (u8)(u * D_002623E0[0].g + w * from[1]);
            c.b = (u8)(u * D_002623E0[0].b + w * from[2]);
            c.a = D_002623E0[0].a;
        } else {
            c = D_002623E0[0];
        }
        SetObjectTreeRecordValue(self, *(u32*)&c);
    }
}

s32 GetPlayerRequestPhase(Player* self)
{
    if (self->state != 4) {
        return self->pulseActive != 0;
    }
    if (self->subState < 45) {
        return 1;
    }
    return 2;
}


void FinishPlayerRequest(Player* self)
{
    if (self->f2730 != 0) {
        FinishSwitchedCollider(self);
        self->f2730 = 0;
    }
    if (self->lastMessage.fn != 0) {
        s32 fn = self->lastMessage.fn;
        self->lastMessage.fn = 0;
        ((void (*)(s32, Player*))fn)(self->lastMessage.data, self);
    } else {
        Vec02 v = self->v150;
        v.z = g_requestFinishMinSpeedZ >? v.z;
        const Desc02* d = self->desc02();
        d->m20(self, &v);
        SetPlayerState(self, 2, 6);
    }
    self->jumpSpeed = 0.0f;
    self->f2498 = 0;
}

struct HitMessage {
    s32 kind;               // 0x00
    u8 pad04[0x20 - 0x04];
    Vec02 v20;              // 0x20
    f32 f30;                // 0x30
    u8 pad34[0x38 - 0x34];
    Collider* source;       // 0x38
    u8 pad3C[0x50 - 0x3C];
};

struct Oscillator;
struct TreeNode03;
s32 FindPlaneTreeNodeForPoint(Vec02* pos, TreeNode03* nodes);
s32 ProbeColliderBelowPoint(Player* self, Collider* col, Vec02* out);
typedef s32 (*MessageHandlerFn)(Collider* self, s32 a, OwnerMessage* msg);
typedef void (*HitFn)(Collider* self, HitMessage* msg);

void NotifyPlayerGroundObject(Player* self)
{
    u32 i;
    if (self->f2438 != 0 && *(s32*)((u8*)self->f2438 + 0x58C) != 0) {
        Vec02 p;
        Vec02 moved;
        p = self->v140;
        p.z = p.z + g_groundProbeLift;
        if (self->subState == 0x27 || self->subState == 0x2F) {
            p.z = p.z - 10.0f;
        }
        if (self->f2438->f278 != 0) {
            ComputeOscillatorDisplacement((Oscillator*)(((void**)self->f2438->f278)[3]), 50.0f, &p, 0, &moved, 0, 0);
            u128 s2 = Vu0::Scalar(2.0f);
            u128 s1 = Vu0::Scalar(-1.0f);
            Vu0::Q(p) = Vu0::MulXSum(Vu0::Q(p), s2, Vu0::Q(moved), s1);
        }
        i = FindPlaneTreeNodeForPoint((Vec02*)&p, self->f2438->tree.nodes) != 0;
    } else {
        i = 0;
    }
    if (i != 0 && (self->v150.z < 0.0f || !(self->state == 2 || self->subState == 0x2C || self->subState == 0x2B))) {
        OwnerMessage msg;
        InitOwnerMessage(&msg, 3, self->f2438);
        if (((MessageHandlerFn)self->f2438->desc03()->m47)(self->f2438, 0, &msg) != 0) {
            self->desc05()->m4C(self, (void*)&msg);
        }
    }
    Vec02 out;
    if (i == 0 || ProbeColliderBelowPoint(self, self->f2438, &out) == 0) {
        return;
    }
    f32 fresh = 0.05f;
    for (i = 0; i < 8; i++) {
        HitStamp* rec = &self->hitStamps[i];
        Collider* obj = rec->obj;
        if (obj == 0) {
            continue;
        }
        if (g_gameClock[1] - rec->time < fresh) {
            continue;
        }
        Collider* list[8];
        s32 count;
        if (IsObjectOfKind(obj, 0x78) != 0) {
            CopyMemory(list, (u8*)obj + 0x94, 0x20);
            count = *(s32*)((u8*)obj + 0x90);
        } else {
            list[0] = obj;
            count = 1;
        }
        for (s32 j = 0; j < count; j++) {
            Collider* o = list[j];
            Vec02 lo;
            Vec02 hi;
            s32 hit = 0;
            GetObjectWorldPosition(o, &lo);
            hi = *(Vec02*)((u8*)o + 0x40);
            TransformPointAtTime((PlacedObject*)(*(void**)((u8*)obj + 0x18)), 0, &hi, 0, 0, 0, g_gameClock[2]);
            if (out.z <= lo.z) {
                if (hi.z <= out.z) {
                    hit = 1;
                }
            } else if (out.z <= hi.z) {
                hit = 1;
            }
            if (hit != 0) {
                HitMessage m;
                m.v20 = lo;
                m.v20.z = out.z;
                m.kind = 4;
                u8* e = *(u8**)((u8*)o + 0x90);
                if (*(s32*)(e + 0x120) == 1 && *(s32*)(e + 0x1B0) == 2) {
                    m.kind = 0x24;
                    m.source = self->f2438;
                }
                ((HitFn*)o->desc)[31](o, &m);
                rec->time = g_gameClock[1];
            }
        }
    }
}


s32 ProbeColliderBelowPoint(Player* self, Collider* col, Vec02* out)
{
    Vec02 moved;
    Vec02 shift;
    Vec02 start;
    Vec02 end;
    ColliderSpan hit;
    if (col->f278 != 0) {
        ComputeOscillatorDisplacement((Oscillator*)(((void**)col->f278)[3]), 50.0f, &self->v140, 0, &moved, 0, 0);
        Vu0::Q(shift) = Vu0::Sub(Vu0::Q(moved), Vu0::Q(self->v140));
    } else {
        shift = D_00248D30;
    }
    u128 base = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(shift));
    Vu0::Q(end) = base;
    Vu0::Q(start) = base;
    end.z += g_groundProbeTopOffset;
    start.z += g_groundProbeBottomOffset;
    if (CollectTreeNodeSpans(col->tree.nodes, &end, &start, 0, 1, &hit) == 0) {
        return 0;
    }
    Vu0::Q(*out) = Vu0::Add(Vu0::Q(hit.q[0]), Vu0::Q(shift));
    return 1;
}

struct AttachedSet;
void AddColliderForce(void* a, void* b);

void ApplyPlayerAttachedSetContact(Player* self, Collider* other, f32 t)
{
    switch (self->subState) {
    case 6:
    case 0x2B:
        if (self->v150.z < 0.0f) {
            ApplyColliderAttachedSetContact(self, (AttachedSet*)other, t);
        }
        return;
    case 0x27:
    case 0x2F: {
        Vec02 point;
        Vec02 local;
        Vec02 q2;
        Vec02 q3;
        Vec02 force;
        Vec02 k;
        f32 next;
        if (ProbeColliderBelowPoint(self, other, &point) == 0) {
            return;
        }
        Vu0::Q(local) = Vu0::Rotate(self->headingMatrix, Vu0::Q(self->headingVelocity));
        GetAttachedSetPointMotion((AttachedSet*)other, &point, (Quad16*)&q2, (Quad16*)&q3);
        Vu0::Q(k) = Vu0::FromFloatAt(g_attachedContactDamping[0]);
        Vu0::Set(force, Vu0::MulX(Vu0::Sub(Vu0::Add(Vu0::Q(self->v150), Vu0::Q(local)), Vu0::Q(q2)), Vu0::Q(k)));
        ApproachValueClampingVelocity(self->v140.z + g_groundProbeLift, self->v150.z - q2.z, point.z, t, g_attachedContactRamp, &next);
        force.z = (next - self->v150.z) / t - self->gravity.z >? force.z;
        AddColliderForce(self, &force);
        return;
    }
    }
    ApplyColliderAttachedSetContact(self, (AttachedSet*)other, t);
}

void SwapInPlayerStandIn(Player* self)
{
    StandIn* obj = (StandIn*)self->f1518;
    if (obj != 0) {
        BaseObject* s0 = 0;
        u32 i = 0;
        while (i < 4) {
            s0 = (BaseObject*)self->f1508[i];
            if (s0 != 0 && IsObjectAttached(s0) != 0) {
                break;
            }
            i++;
        }
        if (i >= 4) {
            s0 = (BaseObject*)self->f1504;
        }
        obj->desc->m02(obj);
        ((VFnB)((void**)obj->desc)[25])(obj, 0);
        ((VFnB)((void**)obj->desc)[35])(obj, s0);
        obj->startTime = g_gameClock[1];
        obj->running = 1;
        if (s0 != self->f1504) {
            s0->desc->m03(s0);
        }
    }
}

s32 TestStandInMayContact(StandIn* self, Collider* value)
{
    if (value == g_player) {
        return 1;
    }
    return TestCollidersMayContact(self, value);
}

Quadword ScaleQuadword(Quadword a, Quadword b);
extern Quad16 g_zeroQuad;

// k times the vector at p, into dst (the quadword helpers' product).
static inline void StoreScaledQuadword(Vec02* dst, f32 k, u8* p)
{
    Quadword t;
    StoreFloatAsQuadword((u128*)&t, k);
    Quadword tv = t;
    Quadword u;
    CopyQuadword((u128*)&u, p);
    StoreQuadword((u128*)dst, ScaleQuadword(tv, u));
}

void StepStandIn(StandIn* self, f32 t)
{
    Mat02 upright;
    Vec02 push;
    Vec02 spin;
    Vec02 q50;
    Vec02 q60;
    StepCollider(self, t);
    f32 since = g_gameClock[1] - self->startTime;
    f32 age = g_unitRange.Limit(g_standInAgeCurve[0] + since * (g_standInAgeCurve[1] + since * g_standInAgeCurve[2]));
    RotateMatrixUpright(&self->rot, 0, &upright);
    StoreScaledQuadword(&q50, age, (u8*)g_standInRotationPull);
    StoreScaledQuadword(&q60, age, (u8*)g_standInRotationTurn);
    if (self->running != 0) {
        Vu0::Q(spin) = Vu0::MulX(Vu0::Q(self->rot.r[2]), Vu0::ScalarAt(g_standInSpinRate));
    } else {
        spin = D_00248D30;
        q50 = *(Vec02*)&g_zeroQuad;
    }
    SteerColliderTowardRotation(self, &upright, (f32*)&q50, &spin, (f32*)&q60, t);
    if (self->running != 0) {
        Vu0::Q(push) = Vu0::MulX(Vu0::Q(self->rot.r[0]), Vu0::ScalarAt(g_standInPushSpeed));
    } else {
        push = D_00248D30;
    }
    StoreScaledQuadword(&q60, age, (u8*)g_standInPositionTurn);
    SteerColliderTowardPosition(self, 0, 0, &push, (f32*)&q60, t);
}

void StopStandIn(StandIn* self, ContactPair* pair, s32 kind)
{
    HandleChildGroupObjectContact(self, pair, kind);
    self->running = 0;
}

void HandleStandInNotification(StandIn* self, s32 kind, ObjectMessage* ref)
{
    HandleChildGroupNotification(self, kind, ref);
    if (kind == 10 && ref->target == self) {
        ((StandIn*)ref->target)->running = 0;
    }
}

void InitOwnerMessage(OwnerMessage* self, s32 mode, void* owner) { FillMemory(self, 0, 0x10); self->owner = owner; self->mode = mode; self->c = owner; }

LINKER_REMNANT(func_001D70E8);

OutputBuffer* InitOutputBuffer(OutputBuffer* self, s32 handle)
{
    self->handle = handle;
    self->targetWord = 0;
    self->capacity = 0;
    self->used = 0;
    self->count = 0;
    self->pending = 0;
    return self;
}

OutputBuffer* InitStringOutputBuffer(OutputBuffer* self, u8* target, s32 capacity) { self->target = target; self->capacity = capacity; self->used = 0; self->handle = -1; self->count = 0; self->pending = 0; return self; }

void DestroyOutputBuffer(OutputBuffer* a0, s32 a1)
{
    FlushOutputBuffer(a0);
    if (a1 & 1) FreeObjectMemory(a0);
}

s32 AppendToOutputBuffer(OutputBuffer* self, void* src, s32 size)
{
    s32 n = size;
    s32 done = 0;

    if (self->target != 0 && self->capacity != 0 && n != 0) {
        s32 avail = self->capacity - self->used;
        if (avail < n) {
            n -= avail;
        }
    }
    if (n == 0) {
        return 0;
    }
    if (self->target != 0) {
        CopyMemory(self->target + self->used, src, n);
        self->used += n;
        done = n;
    } else if (n > 0) {
        do {
            s32 room = 0x400 - self->pending;
            s32 rem = n - done;
            s32 take = (room < rem) ? room : rem;
            if (take != 0) {
                CopyMemory((u8*)self + (self->pending + 0x18), (u8*)src + done, take);
                done += take;
                self->pending += take;
            }
            if (self->pending == 0x400) {
                FlushOutputBuffer(self);
            }
        } while (done < n);
    }
    self->count += done;
    return n;
}

void FlushOutputBuffer(OutputBuffer* self)
{
    u8 buf[0x90];
    s32 done;
    u8* p;
    s32 chunk;
    s32 rem;

    if (self->pending == 0) {
        return;
    }
    if (self->targetWord != 0) {
        return;
    }
    if (self->handle < 0) {
        p = self->buf;
        for (done = 0; done < self->pending; done += chunk) {
            rem = self->pending - done;
            chunk = 0x80;
            if (!(rem > 0x7F)) {
                chunk = rem;
            }
            CopyMemory(buf, p, chunk);
            p += chunk;
            buf[chunk] = 0;
            PrintBuffered("%s", buf);
        }
    } else {
        WriteFile(self->handle, self->buf, self->pending);
    }
    self->pending = 0;
}

void InitPathFollower(PathFollower* self)
{
    InitSwitchedCollider(self);
    self->rearWheelRadius = 50.0f;
    self->frontWheelRadius = 50.0f;
    self->maxSpeed = 3000.0f;
    self->sideLimit = 1300.0f;
    self->grip = 2.0f;
    self->lapCount = 3;
    (*(Quad16*)&self->paceBlendCurve) = *(Quad16*)g_pathFollowerInitV620;
    CopyMemory(self->blendEnds, D_00275250, 0x40);
    ResetPathFollower(self);
}

void StartPathFollower(PathFollower* self)
{
    BaseObject* buf[16];
    s32 id0;
    s32 id1;
    s32 id2;
    StartPlacedObject(self);
    ResolveObjectLinks(self, 0x14, g_pathFollowerLinks);
    self->targetHeading = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    if (self->walkerGraph != 0) {
        StateWalker* v = CreateStateWalker((StateGraph*)self->walkerGraph, self, -1, 0);
        self->walker = v;
        SetStateWalkerTarget(v, self->kind == 1 ? 0x484 : 0x384);
    }
    switch (g_currentWorld->soundBank) {
    case 3:
        id0 = self->enabled ? 0x1D2 : 0x1AD;
        id1 = 0x1BB;
        id2 = 0x1AF;
        goto spawn;
    case 5:
        id0 = self->enabled ? 0x2A6 : 0x280;
        id1 = 0x27F;
        id2 = 0x27D;
        goto spawn;
    case 6:
        id0 = self->enabled ? 0x2DE : 0x2DC;
        id1 = 0x2DB;
        id2 = 0x2DD;
    spawn:
        StartSoundEffect(id0, (PlayingSound**)self->engineSoundB, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        StartSoundEffect(id1, (PlayingSound**)self->engineSoundA, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        StartSoundEffect(id2, (PlayingSound**)self->slideSound, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        {
            f32 r = RandomFloatInRange(-0.1f, 0.1f);
            self->slidePitchOffset = self->engineBPitchOffset = self->engineAPitchOffset = self->fB98 = r;
        }
        break;
    default:
        break;
    }
    {
        void* c = FindFirstObjectById(g_currentWorld, 0x104, 7, self);
        if (c != 0) {
            self->f594 = 200.0f;
            self->partner = c;
            self->f598 = c;
        }
    }
    if (self->kind == 1) {
        s32 n = GatherObjectsByMode(self->world, 0x105, 0x426, 0, 0x10, buf);
        for (s32 i = 0; i < n; i++) {
            buf[i]->desc->m17(buf[i], self);
        }
        T217D_E30* boxA = &g_firstTallyCaption;
        T217D_E30* boxB = &g_secondTallyCaption;
        ((U32P*)&boxA->own)->v = 0;
        ((U32P*)&boxB->own)->v = 0;
        boxA->target = &boxA->own;
        boxB->target = &boxB->own;
    }
    for (s32 k = 0; k < 4; k++) {
        Slot19* s = &self->wheels[k];
        s->placedPos = s->obj->pos;
    }
    ResetPathFollower(self);
}

extern f32 g_gameClock[];
extern float g_pathFollowerRampTime;
extern float g_leanCurve[];
extern float g_leanRange[];
extern float g_gripScaleCurve[];
extern float g_gripScaleRange[];
extern float g_maxAccelCurve[];
extern float g_maxAccelRange[];
extern float g_uprightSteerDelay;
extern f32 g_uprightRampTime;
extern Vec02 g_uprightPull;
extern float g_wheelSlipCurve[];
extern float g_wheelSlipRange[];
extern float g_suspensionDampingGain;
extern float g_suspensionSpringGain;
extern float g_suspensionDampingCurve[];
extern float g_suspensionSpringCurve[];
extern float g_airSteerCurve[];
extern float g_airSteerTurn[];
extern float g_driveForceFull;
extern float g_gripLimitCap;
extern float g_steerRateGain;
extern float g_steerSpeedCap;
extern f32 g_steerSpeedCurve[];
extern f32 g_headingAlignCurve[];
extern f32 g_headingAlignRange[];
extern f32 g_speedRampBelow[];
extern f32 g_speedRampAbove[];
extern f32 g_wheelSpinCurve[];
extern f32 g_wheelSpinRange[];
extern f32 g_forceLeverDrop;

void AddColliderForce(void* a, void* b);
void* StoreFloatAsQuadword(u128* out, f32 f);
void* CopyQuadword(u128* out, void* src);
void* StoreQuadword(u128* out, u128 v);
void ApplyColliderInverseInertia(Collider* self, Vec02* in, Vec02* out);
void AddColliderTorque(Collider* self, Vec02* torque);
Quadword ScaleQuadword(Quadword a, Quadword b);
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
f32 ApproachValueWithRamp(f32 x, f32 y, f32 z, RampProfile* k, f32* out);

// v made unit length into out; returns its length.
static inline f32 NormalizeInto(Vec02& out, Vec02 v)
{
    u128 len = Vu0::Length(Vu0::Q(v));
    Vu0::Q(out) = Vu0::DivX(Vu0::Q(v), len);
    return Vu0::ToFloat(len);
}

void StepPathFollower(PathFollower* self, f32 dt)
{
    StepCollider(self, dt);
    if (g_gameClock[1] - self->uprightTime > g_uprightSteerDelay && g_gameClock[1] - self->pushedTime > g_uprightRampTime) {
        Mat02 upright;
        RotateMatrixUpright(&self->rot, 0, &upright);
        SteerColliderTowardRotation(self, &upright, (f32*)&g_uprightPull, 0, 0, dt);
    }
    f32 sum = 0.0f;
    u32 i;
    Slot19* s;
    for (i = 0; i < 4; i++) {
        s = &self->wheels[i];
        if (s->contactStamp != self->contactStamp) {
            continue;
        }
        Vec02 a;
        Vec02 b;
        Vec02 dir;
        Vec02 motion;
        Vec02 force;
        Vec02 torque;
        Vec02 accel;
        Vec02 spin;
        s32 front = (s32)i < 2;
        a = *(Vec02*)((u8*)s->obj8 + 0x40);
        a.z -= front ? self->frontWheelRadius : self->rearWheelRadius;
        TransformPointBetweenFrames(self, 0, &a, &a);
        b = s->obj->v190;
        b.z -= front ? self->frontWheelRadius : self->rearWheelRadius;
        TransformPointBetweenFrames(self, 0, &b, &b);
        Vu0::Q(dir) = Vu0::Sub(Vu0::Q(a), Vu0::Q(b));
        f32 len = NormalizeInto(dir, dir);
        ComputeObjectMotionInFrame(self, 0, &s->contactPoint, &motion, 0, 0, 0);
        u128 axis = Vu0::Q(s->contactDirection);
        u128 side = Vu0::Sub(Vu0::Q(motion), Vu0::MulX(axis, Vu0::Dot(Vu0::Q(motion), axis)));
        f32 slip = Vu0::ToFloatMoved(Vu0::Length(side));
        s->secondEmitterOwed += ((ValueRange*)g_wheelSlipRange)->Clamp(((QuadraticCurve*)g_wheelSlipCurve)->Eval(slip)) * dt;
        f32 along = Vu0::ToFloat(Vu0::Dot(Vu0::Sub(Vu0::Q(s->contactPoint), Vu0::Q(b)), Vu0::Q(dir))) / len;
        f32 one = 1.0f;
        f32 t;
        if (along < 0.0f) {
            t = 0.0f;
        } else if (one < along) {
            t = one;
        } else {
            t = along;
        }
        // The push's two curves are indexed in place: each address is then formed right before
        // its loads, a life of 3 that loop.c's first pass leaves and its second moves, after the
        // copy of &spin (docs/toolchain/loops.md, "Three invariants ranked by their place").
        f32 push = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vu0::Q(s->contactVelocity), Vu0::Q(motion)), Vu0::Q(dir)))
                       * (g_suspensionDampingCurve[0] + t * (g_suspensionDampingCurve[1] + t * g_suspensionDampingCurve[2])) * g_suspensionDampingGain
                 + Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vu0::Q(s->contactPoint), Vu0::Q(b)), Vu0::Q(dir)))
                       * (g_suspensionSpringCurve[0] + t * (g_suspensionSpringCurve[1] + t * g_suspensionSpringCurve[2])) * g_suspensionSpringGain;
        if (push < 0.0f) {
            continue;
        }
        f32 mass = self->mass;
        push *= mass;
        Vu0::Q(force) = Vu0::MulX(Vu0::Q(dir), Vu0::Scalar(push));
        Vu0::Q(torque) = Vu0::Cross(Vu0::Sub(Vu0::Q(s->contactPoint), Vu0::Q(self->v140)), Vu0::Q(force));
        *(u128*)&accel = Vu0::DivX(Vu0::Q(force), Vu0::Scalar(mass));
        ApplyColliderInverseInertia(self, &torque, &spin);
        AddColliderForce(self, &accel);
        AddColliderTorque(self, &spin);
        sum += Vu0::ToFloat(Vu0::Dot(Vu0::Q(force), Vu0::Q(self->rot.r[2])));
    }
    if (sum == 0.0f) {
        f32 t = (g_gameClock[1] - self->pushedTime) / g_uprightRampTime;
        f32 k = g_unitRange.Clamp(((QuadraticCurve*)g_airSteerCurve)->Eval(t));
        u8* p = (u8*)g_airSteerTurn;
        Quadword q;
        StoreFloatAsQuadword((u128*)&q, k);
        Quadword qv = q;
        Quadword u;
        CopyQuadword((u128*)&u, p);
        Vec02 turn;
        StoreQuadword((u128*)&turn, ScaleQuadword(qv, u));
        SteerColliderTowardRotation(self, 0, 0, (Vec02*)&D_00248D30, (f32*)&turn, dt);
    }
    f32 one = 1.0f;
    f32 drive = sum / (self->mass * g_driveForceFull);
    if (drive < 0.0f) {
        drive = 0.0f;
    } else if (one < drive) {
        drive = one;
    }
    self->drive = drive;
    f32 grip = self->activeZone != 0 ? self->activeZone->grip : self->grip;
    f32 lap = (g_gameClock[1] - self->lapTime) / g_pathFollowerRampTime;
    f32 limit = g_gripLimitCap <? grip * sum / self->mass;
    f32 w = ((ValueRange*)g_gripScaleRange)->Clamp(((QuadraticCurve*)g_gripScaleCurve)->Eval(lap));
    if (1.0f < self->pace) {
        w *= self->pace * self->pace;
    }
    limit *= w;
    Vec02 vel;
    Vu0::Q(vel) = Vu0::MulAddX(Vu0::Vec::Of(self->v150), Vu0::Vec::Of(self->v170), Vu0::Vec::ScalarInGpr(dt)).q;
    Vec02 local;
    Vu0::Q(local) = Vu0::RotateTransposed(self->rot, Vu0::Q(vel));
    f32 span = self->wheels[0].obj->v190.x - self->wheels[2].obj->v190.x;
    f32 rate = self->targetSpeed / self->maxSpeed;
    f32 r;
    if (rate < 0.0f) {
        r = 0.0f;
    } else if (1.0f < rate) {
        r = 1.0f;
    } else {
        r = rate;
    }
    r *= g_unitRange.Clamp(((QuadraticCurve*)g_steerSpeedCurve)->Eval(local.x / self->maxSpeed));
    f32 yaw = (local.x <? g_steerSpeedCap) * self->steerAngle;
    f32 r2 = r * self->steerAngle;
    Vec02 spinL;
    Vu0::Q(spinL) = Vu0::RotateTransposed(self->rot, Vu0::Q(self->v160));
    f32 inertia = self->mass * __builtin_fabsf(self->wheels[0].obj->v190.x) / self->inertia.r[2].z;
    Vec02 c;
    c.x = c.y = 0.0f;
    f32 tq = ClampToMagnitude((yaw / span + r2 * g_steerRateGain - spinL.z) / dt, inertia * limit);
    c.z = tq;
    inertia = tq / inertia;
    Vec02 torque2;
    Vu0::Q(torque2) = Vu0::Rotate(self->rot, Vu0::Q(c));
    limit -= __builtin_fabsf(inertia);
    AddColliderTorque(self, &torque2);
    f32 lean = ((ValueRange*)g_leanRange)->Clamp(((QuadraticCurve*)g_leanCurve)->Eval(lap)) * self->pace;
    f32 tilt = (g_leanRange[1] <? lean) / self->pace;
    Vec02 heading;
    ComputePolarOffset((Vec3*)&heading, self->targetHeading, 1.0f, 0.0f);
    f32 h = ((ValueRange*)g_headingAlignRange)->Limit(((QuadraticCurve*)g_headingAlignCurve)->Eval(Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(heading), Vu0::Q(self->rot.r[0])))));
    Vec02 want;
    Mat02 roll;
    BuildAxisAngleMatrix(&g_unitZVector, &roll, (spinL.z + c.z * (dt * 0.5f)) * dt);
    f32 speed;
    if (1.0f < tilt) {
        speed = tilt * self->maxSpeed;
    } else {
        speed = tilt * h * self->targetSpeed;
    }
    Vu0::Q(want) = Vu0::FromFloats(speed, 0.0f, 0.0f);
    Vu0::Q(want) = Vu0::RotateUntied(roll, Vu0::Q(want));
    f32 maxAccel = ((ValueRange*)g_maxAccelRange)->Limit(((QuadraticCurve*)g_maxAccelCurve)->Eval(lap));
    Vec02 delta;
    Vec02 world;
    Vec02 clamped;
    Vu0::Q(delta) = Vu0::DivX(Vu0::Sub(Vu0::Vec::Of(want), Vu0::Vec::Of(local)), Vu0::Vec::ScalarInGpr(dt)).q;
    delta.z = 0.0f;
    ClampVectorLength(&delta, &clamped, limit >? maxAccel);
    if (self->targetSpeed != 0.0f && self->kind == 0) {
        f32 out;
        if (local.x < self->targetSpeed) {
            ApproachValueWithRamp(local.x, self->targetSpeed, dt, (RampProfile*)g_speedRampBelow, &out);
            clamped.x = (out >? maxAccel) <? clamped.x;
        } else {
            ApproachValueWithRamp(local.x, self->targetSpeed, dt, (RampProfile*)g_speedRampAbove, &out);
            clamped.x = out >? clamped.x;
        }
    }
    Vu0::Q(world) = Vu0::Rotate(self->rot, Vu0::Q(clamped));
    AddColliderForce(self, &world);
    for (i = 0; i < 4; i++) {
        s = &self->wheels[i];
        if (s->contactStamp == self->contactStamp) {
            f32 p = ((ValueRange*)g_wheelSpinRange)->Limit(((QuadraticCurve*)g_wheelSpinCurve)->Eval(Vu0::ToFloat(Vu0::Length(Vu0::Q(delta))) * dt));
            s->firstEmitterOwed += p * g_gameClock[2];
        }
    }
    Vec02 tq3;
    Vu0::Q(tq3) = Vu0::Cross(Vu0::MulX(Vu0::Q(self->rot.r[2]), Vu0::ScalarAt(g_forceLeverDrop)), Vu0::MulX(Vu0::Q(world), Vu0::ScalarAt(self->mass)));
    ApplyColliderInverseInertia(self, &tq3, &torque2);
    AddColliderTorque(self, &torque2);
}

f32 FindNearestValueOutsideSpans(s32 count, ValueRange* spans, f32 x)
{
    if (IsInsideAnyRange(count, spans, x) == 0) {
        return x;
    }
    f32 bestDist = 3.4028234663852886e+38f;
    f32 best = bestDist;
    if (count > 0) {
        ValueRange* s = spans;
        s32 n = count;
        do {
            f32 d = __builtin_fabsf(x - s->lo);
            if (d < bestDist) {
                if (IsInsideAnyRange(count, spans, s->lo) == 0) {
                    best = s->lo;
                    bestDist = d;
                }
            }
            d = __builtin_fabsf(x - s->hi);
            if (d < bestDist) {
                if (IsInsideAnyRange(count, spans, s->hi) == 0) {
                    best = s->hi;
                    bestDist = d;
                }
            }
            s++;
            n--;
        } while (n != 0);
    }
    return best;
}

void UpdatePathFollowerPace(PathFollower* self)
{
    if (self != GetActiveSwitchedCollider()) {
        self->pace = ApproachValueWithRamp((RampProfile*)g_paceRamp, 0, self->pace, self->paceTarget, g_gameClock[2]);
        if (!(g_gameClock[1] < self->paceChangeTime)) {
            f32 one = 1.0f;  // hoisted: retail holds 1.0f in $f3 before the multiply
            s32 idx = 3 * (self->lap - 1) + self->currentMarker->index;
            f32 t = (f32)idx * 0.1f;
            f32 w;
            if (t < 0.0f) {
                w = 0.0f;
            } else if (one < t) {
                w = one;
            } else {
                w = t;
            }
            f32 val = ((QuadraticCurve*)&self->paceCurveA)->Eval(w);
            f32 lo = self->paceMin;
            f32 hi = self->paceMax;
            if (val < lo) {
                val = lo;
            } else if (hi < val) {
                val = hi;
            }
            self->paceTarget = val;
            f32 r = RandomFloatInRange(-0.05f, 0.05f);
            self->paceTarget = self->paceTarget + r;
            f32 r2 = RandomFloatInRange(g_paceChangeInterval[0], g_paceChangeInterval[1]);
            self->paceChangeTime = g_gameClock[1] + r2;
        }
    }
}

f32 GetWrappedDifference(f32 x, f32 lim, f32 base)
{
    f32 d = lim - base;
    if (x * 0.5f < d)
        d = d - x;
    else if (d < x * -0.5f)
        d = d + x;
    return d;
}

s32 IsPathFollowerAhead(PathFollower* self, PathFollower* other)
{
    s32 d = self->lap - other->lap;
    if (d > 0) return 1;
    if (d < 0) return 0;
    d = self->currentMarker->index - other->currentMarker->index;
    if (d > 0) return 1;
    if (d < 0) return 0;
    f32 r = GetWrappedDifference(self->pathLength, self->pathDistance, other->pathDistance);
    return 0.0f < r;
}


void AdvancePathFollowerAlongPath(PathFollower* self, s32* nearby)
{
    PathFollower* list[16];
    ValueRange spans[16];
    Vec02 pos;
    Vec02 tangent;
    Vec02 dir;
    Vec02 lo;
    Vec02 hi;
    Vec02 out;
    s32 n = GatherObjectsById(self->world, 5, 0x19, 0, 0x10, list);
    s32 count = 0;
    s32 k = 0;
    for (s32 i = 0; i < n; i++) {
        PathFollower* o = list[i];
        if (o == self) {
            continue;
        }
        if (o->path != self->path) {
            continue;
        }
        if (IsPathFollowerAhead(self, o)) {
            continue;
        }
        count++;
        f32 d = WrapModulo(o->pathDistance - self->pathDistance, o->pathLength);
        f32 r = ((ValueRange*)g_avoidSpanRange)->Limit(((QuadraticCurve*)g_avoidSpanCurve)->Eval(d));
        if (r <= 0.0f) {
            continue;
        }
        ValueRange* s = &spans[k++];
        s->lo = o->sideOffset - r;
        s->hi = o->sideOffset + r;
    }
    *nearby = count;
    ValueRange* s = &spans[k++];
    s->lo = -1e6f;
    s->hi = -self->sideLimit;
    s = &spans[k++];
    s->lo = self->sideLimit;
    s->hi = 1e6f;
    PathCurve* c = self->path->curve;
    c->vt->m06(c, self->pathDistance + g_pathLookAhead);
    c = self->path->curve;
    if (c->vt->m02) {
        ((void (*)(PathCurve*, f32, Vec02*, Vec02*))c->vt->m02)(c, self->pathDistance + g_pathLookAhead, &pos, &tangent);
    }
    u128 side = Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(tangent));
    Vu0::Q(dir) = Vu0::DivX(side, Vu0::Length(side));
    Vu0::Q(lo) = Vu0::MulAddX(Vu0::Q(pos), Vu0::Q(dir), Vu0::ScalarAt(g_lateralOffsetRange.lo));
    Vu0::Q(hi) = Vu0::MulAddX(Vu0::Q(pos), Vu0::Q(dir), Vu0::ScalarAt(g_lateralOffsetRange.hi));
    FindPathCurveNearestTime(self->sidePath->curve, &lo, &hi, &out, 0, &self->sidePathTime, 0, self->sidePathTime);
    f32 ahead = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vu0::Q(out), Vu0::Q(pos)), Vu0::Q(dir)));
    f32 want = ApproachValueWithRamp((RampProfile*)g_lateralOffsetRamp, 0, self->sideTarget, ahead, g_gameClock[2]);
    f32 best = FindNearestValueOutsideSpans(k, spans, want);
    if (!IsInsideRange(&g_lateralOffsetRange, best)) {
        best = want;
    } else {
        if (k > 0) {
            f32 cur = self->sideOffset;
            ValueRange* s = spans;
            s32 j = k;
            do {
                if (cur < best && cur < s->lo && s->lo < best) {
                    best = s->lo;
                } else if (best < cur && s->hi < cur && best < s->lo) {
                    best = s->hi;
                }
                s++;
                j--;
            } while (j != 0);
        }
    }
    self->sideTarget = best;
}


void ComputePathFollowerHeadingTarget(PathFollower* self)
{
    Vec02 pos;
    Vec02 tangent;
    Vec02 side;
    Vec02 w;
    Vec02 ahead;
    if (self->path != 0) {
        PathCurve* o = self->path->curve;
        if (o->vt->m02 != 0) {
            ((void (*)(PathCurve*, f32, void*, void*))o->vt->m02)(o, self->pathDistance + g_pathLookAhead, &pos, &tangent);
        }
        u128 base = Vu0::Q(pos);
        u128 c = Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(tangent));
        u128 k = Vu0::FromFloatAt(self->sideTarget);
        Vu0::Q(side) = Vu0::DivX(c, Vu0::Length(c));
        Vu0::Set(ahead, k);
        u128 p2 = Vu0::MulAddX(base, Vu0::Q(side), k);
        Vu0::Q(w) = Vu0::Sub(p2, Vu0::Q(*(Vec02*)((u8*)self + 0x100)));
        Vu0::Q(pos) = p2;
        self->targetHeading = ArctangentOfRatio(w.y, w.x);
        o = self->path->curve;
        if (o->vt->m02 != 0) {
            ((void (*)(PathCurve*, f32, void*, void*))o->vt->m02)(o, self->pathDistance + g_pathLookAhead + g_turnProbeLength, 0, &ahead);
        }
        f32 turn = ComputeAngleBetweenVectors(&tangent, &ahead, 0);
        self->targetSpeed = self->pace * self->maxSpeed;
        u8* limit = *(u8**)((u8*)self + 0xAFC);
        if (limit != 0) {
            self->targetSpeed = *(f32*)(limit + 0x1C) <? self->targetSpeed;
        }
        if (0.0f < turn) {
            f32 v = Fpu::Sqrt(g_cornerSpeedFactor[0] * (g_turnProbeLength / turn) * self->grip * -*(f32*)((u8*)self + 0x358));
            if (v < self->targetSpeed) {
                self->targetSpeed = v;
            }
        }
    }
}

void SteerPathFollower(PathFollower* self)
{
    f32 a = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    f32 b = WrapAngle(self->targetHeading - a);
    f32 c = ClampToMagnitude(g_steerAngleGain * b, g_steerAngleLimit);
    self->steerAngle = ApproachAngleWithRamp((u8*)g_steerAngleRamp, 0, self->steerAngle, c, g_frameDt);
    for (u32 i = 0; i < 4; i++) {
        Slot19* s = &self->wheels[i];
        if ((s32)i < 2) {
            s->turnRate = self->targetSpeed / self->frontWheelRadius;
        } else {
            s->turnRate = self->targetSpeed / self->rearWheelRadius;
        }

    }
}
