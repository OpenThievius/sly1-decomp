// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "globals.h"
#include "switched_collider.h"
#include "attachment.h"
#include "value_range.h"
#include "functions/base_object.h"
#include "functions/blend_animation.h"
#include "functions/camera.h"
#include "functions/collider.h"
#include "functions/collider_contact.h"
#include "functions/matrix.h"
#include "functions/oscillator.h"
#include "functions/placed_object.h"
#include "functions/player.h"
#include "functions/player_link.h"
#include "functions/pose_source.h"
#include "functions/symmetric_solve.h"
#include "functions/turning_collider.h"
#include "functions/world_contacts.h"
struct BaseObject;
struct Mat02;
struct Vec02;

struct Mat02;
struct Vec02;


// The file's .data, in retail's order: the constants of its assembly.
float g_linkAlongDrag = -0.25f;
float g_linkSwingAcrossDrag = -2.5f;
float g_linkRestAcrossDrag = -1.0f;
float g_linkKickDuration = 0.25f;
float g_linkKickAcceleration[4] = {5.0f, 0.0f, 0.0f, 0.0f};
float g_linkKickCurve[4] = {0.5f, -0.00999999978f, 0.0f, 0.0f};
float g_linkLengthRamp[4] = {1000.0f, 0.0f, 0.25f, 5000.0f};
float g_linkLengthMin = 75.0f;
float g_linkLengthMax = 230.0f;
float g_linkTurnRamp[3] = {15.0f, 0.0f, 0.100000001f};
float g_linkTowardHoldTime = 1.39999998f;
float g_linkAwayHoldTime = 1.39999998f;
float g_linkIdleDelay = 0.25f;
float g_linkAlignedAngle = 0.100000001f;
float g_linkMisalignedAngle = 0.400000006f;
float g_linkSlowSpeed = 80.0f;
float g_linkFastSpeed = 120.0f;
float g_linkWeightRamp[4] = {1.0f, 0.0f, 0.100000001f, 0.0f};
float g_linkBlendRamp[3] = {4.0f, 0.0f, 0.100000001f};
float g_linkAngleScale = 1.70000005f;
float g_linkAngleRateLimit = 3.0f;
float g_linkPoseTiltA = 3.5f;
float g_linkPoseTiltB = -1.70000005f;
float g_linkPoseOffsetRamp[3] = {3000.0f, 1000.0f, 0.150000006f};
float g_linkPoseRotationRamp[3] = {30.0f, 10.0f, 0.150000006f};

struct BlendAnimation;
struct Collider;
struct BlendAnimationView;

struct ThreeBlendRecord { s32 f0; u8 pad0[0xC - 0x4]; s32 fC; u8 pad1[0x18 - 0x10]; f32 f18; };

void CreateThreeEntryBlend(void* a0, ThreeBlendRecord* a1, void** a2)
{
    void* tmp;
    a1->f0 = 0;
    a1->fC = 0;
    a1->f18 = 1.0f;
    BuildCombinedBlendAnimation((Collider*)a0, 12, 3, (u8*)a1, 0, 0, 0, (BlendAnimation**)&tmp);
    SetBlendItemWeights((BlendAnimationView*)tmp, 12, 3, a1);
    if (a2 != 0) {
        *a2 = tmp;
    }
}

// A row of the link's system: the response of the two objects to a unit impulse along one axis,
// in direction (a) and in rotation (b).
struct LinkRow {
    Vec02 a;
    Vec02 b;
};

// The right-hand side of the link's system, read as components by index.
struct __attribute__((aligned(16))) LinkVector {
    f32 v[4];
};

struct VectorConstraint;
void ApplyColliderInverseInertia(void* self, Vec02* in, Vec02* out);
void ComputeColliderPointVelocity(void* self, void* data, LinkRow* row, Vec02* out);

void SolvePlayerLinkSystem(PlacedObject* a, PlacedObject* b, Vec02* point, const LinkVector* target, LinkRow* out)
{
    PlacedObject* objs[2];
    Vec02 pts[2];
    Vec02 axis;
    Vec02 cross;
    Vec02 scaled;
    Vec02 torque;
    LinkRow rows[2][3];
    Vec02 vel[2];
    Vec02 diff[3];
    f32 m[3][3];
    f32 factor[3][3];
    f32 rhs[3];
    f32 sol[3];
    s32 i;
    s32 j;
    s32 flipped = 1;    // the object whose impulse is turned the other way

    objs[0] = a;
    objs[1] = b;
    pts[0] = a->v140;
    pts[1] = *point;
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 2; i++) {
            PlacedObject* o = objs[i];
            axis = g_identityMatrix.r[j];
            if (i == flipped) {
                Vu0::Q(axis) = Vu0::MulX(Vu0::Vec::Of(axis), Vu0::Vec::Scalar(-1.0f)).q;
            }
            Vu0::Vec p = Vu0::Vec::Of(pts[i]);
            Vu0::Vec c = Vu0::Vec::Of(o->v140);
            Vu0::Vec arm = Vu0::Sub(p, c);
            Vu0::Set(cross, Vu0::Cross(arm, Vu0::Vec::Of(axis)).q);
            Vu0::Vec mass = Vu0::Vec::ScalarAtValue(*(f32*)((u8*)o + 0x368));
            Vu0::Set(scaled, Vu0::DivX(Vu0::Vec::Of(axis), mass).q);
            ConstrainVectorByParentAnchor((Collider*)o, (VectorConstraint*)((u8*)o + 0x440), &scaled, &rows[i][j].a, 0);
            ApplyColliderInverseInertia(o, &cross, &torque);
            ConstrainVectorByParentAnchor((Collider*)o, (VectorConstraint*)((u8*)o + 0x460), &torque, &rows[i][j].b, 0);
            ComputeColliderPointVelocity(o, point, &rows[i][j], &vel[i]);
        }
        Vu0::Vec v0 = Vu0::Vec::Of(vel[0]);
        Vu0::Vec v1 = Vu0::Vec::Of(vel[1]);
        Vu0::Q(diff[j]) = Vu0::Sub(v0, v1).q;
    }
    for (j = 0; j < 3; j++) {
        f32* row = m[j];
        for (s32 k = 0; k < 3; k++) {
            Vu0::Vec e = Vu0::Vec::Of(g_identityMatrix.r[k]);
            Vu0::Vec d = Vu0::Vec::Of(diff[j]);
            Vu0::StoreX(row[k], Vu0::Dot(e, d).q);
        }
        rhs[j] = target->v[j];
    }
    FactorSymmetricMatrix(3, &m[0][0], &factor[0][0]);
    SolveFactoredSystem(3, &factor[0][0], rhs, sol);
    for (i = 0; i < 2; i++) {
        Vu0::Vec s0 = Vu0::Vec::ScalarAtValue(sol[0]);
        Vu0::Vec a0 = Vu0::Vec::Of(rows[i][0].a);
        Vu0::Vec s1 = Vu0::Vec::ScalarAtValue(sol[1]);
        Vu0::Vec a1 = Vu0::Vec::Of(rows[i][1].a);
        Vu0::Vec s2 = Vu0::Vec::ScalarAtValue(sol[2]);
        Vu0::Vec a2 = Vu0::Vec::Of(rows[i][2].a);
        Vu0::Q(out[i].a) = Vu0::MulXSum3(a0, s0, a1, s1, a2, s2).q;
        Vu0::Vec t0 = Vu0::Vec::ScalarAtValue(sol[0]);
        Vu0::Vec b0 = Vu0::Vec::Of(rows[i][0].b);
        Vu0::Vec t1 = Vu0::Vec::ScalarAtValue(sol[1]);
        Vu0::Vec b1 = Vu0::Vec::Of(rows[i][1].b);
        Vu0::Vec t2 = Vu0::Vec::ScalarAtValue(sol[2]);
        Vu0::Vec b2 = Vu0::Vec::Of(rows[i][2].b);
        Vu0::Q(out[i].b) = Vu0::MulXSum3(b0, t0, b1, t1, b2, t2).q;
        TransformDirectionBetweenFrames(0, (PlacedObject*)(*(void**)((u8*)objs[i] + 0x18)), &out[i].a, &out[i].a);
        TransformDirectionBetweenFrames(0, (PlacedObject*)(*(void**)((u8*)objs[i] + 0x18)), &out[i].b, &out[i].b);
    }
}

extern f32 g_linkAlongDrag;
extern f32 g_linkSwingAcrossDrag;
extern f32 g_linkRestAcrossDrag;
extern f32 g_linkKickDuration;
extern f32 g_linkKickAcceleration[4];
extern f32 g_linkKickCurve[4];
extern f32 g_linkLengthRamp[4];
extern f32 g_linkLengthMin;
extern f32 g_linkLengthMax;
extern f32 g_gameClock[];
// The game clock as the link reads it.
struct LinkClock { s32 running; f32 time; f32 dt; };
static inline const f32& ClockDt(const LinkClock* c) { return c->dt; }
static inline f32 ClockTime(const LinkClock* c) { return c->time; }
struct LinkAnchor { u8 pad0[0x18]; void* parent; u8 pad1C[0xB0 - 0x1C]; f32 fB0; };
struct LinkSystem { u8 pad0[4]; PlacedObject* object; };

f32 SplitVectorAlongAxis(Vec02* v, Vec02* axis, Vec02* along, Vec02* across);
f32 ApproachValueClampingVelocity(f32 a, f32 b, f32 c, f32 d, void* self, f32* out);

// The player swinging on the link (states 0x32 and 0x34 pump it): the anchor's frame and
// motion, the swing's turning about the anchor eased and damped, its length kept, and the
// acceleration that gives it, handed to the link's system when there is one.
// v made unit length in place, or the fallback when it is shorter than 0.0001; its length.
static inline f32 NormalizeInPlace(Vec02* v, const Vec02& fallback)
{
    u128 len = Vu0::Length(Vu0::Q(*v));
    if (Vu0::ToFloat(len) < 0.0001f) {
        *v = fallback;
    } else {
        Vu0::Q(*v) = Vu0::DivX(Vu0::Q(*v), len);
    }
    return Vu0::ToFloatMoved(len);
}

void PlacePlayerOnLinkedObject(Player* self)
{
    Vec02 pos;
    Vec02 delta;
    Vec02 vel;
    Vec02 dir;
    Mat02 rot;
    Vec02 rel;
    Vec02 across;
    Vec02 along;
    Vec02 n1;
    Vec02 w1;
    LinkAnchor* anchor = (LinkAnchor*)self->boundObject;
    GetObjectWorldPosition((BaseObject*)anchor, &pos);
    GetObjectWorldRotation((BaseObject*)self->boundObject, &rot);
    ComputeObjectMotionInFrame((PlacedObject*)(((LinkAnchor*)self->boundObject)->parent), 0, &pos, &vel, 0, 0, 0);
    Vu0::Q(delta) = Vu0::Q(dir) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(pos));
    f32 dist = NormalizeInPlace(&dir, g_unitZVector);
    Vu0::Q(rel) = Vu0::Sub(Vu0::Q(self->v150), Vu0::Q(vel));
    f32 speed = SplitVectorAlongAxis(&rel, &dir, &along, &across);
    Vu0::Vec a1 = Vu0::NormalizeOr(Vu0::Cross(Vu0::Vec::Of(dir), Vu0::Vec::Of(across)), Vu0::Vec::Of(g_unitXVector));
    Vu0::Set(n1, a1.q);
    Vu0::Set(w1, Vu0::MulX(a1, Vu0::Vec::Scalar(Vu0::ToFloatMoved(Vu0::Length(Vu0::Vec::Of(across))) / dist)).q);
    Vu0::Vec gv = Vu0::Vec::Of(self->gravity);
    Vu0::Vec gp = Vu0::Sub(gv, Vu0::MulX(Vu0::Vec::Of(dir), Vu0::Dot(gv, Vu0::Vec::Of(dir))));
    Vec02 g;
    Vu0::Set(g, gp.q);
    Vu0::Vec a2 = Vu0::NormalizeOr(Vu0::Cross(Vu0::Vec::Of(dir), gp), Vu0::Vec::Of(g_unitYVector));
    Vec02 n2;
    Vu0::Set(n2, a2.q);
    Vec02 w2;
    Vu0::Set(w2, Vu0::MulX(a2, Vu0::Vec::Scalar(Vu0::ToFloat(Vu0::Length(Vu0::Vec::Of(g))) / dist)).q);
    f32 gain;
    if (self->subState == 0x32 || self->subState == 0x34) {
        gain = g_linkSwingAcrossDrag;
    } else {
        gain = g_linkRestAcrossDrag;
    }
    Vec02 acc;
    Vec02 accAlong;
    Vec02 accAcross;
    Vu0::Q(acc) = Vu0::MulAddX(Vu0::Q(w1), Vu0::Q(w2), Vu0::ScalarAt(ClockDt((LinkClock*)g_gameClock)));
    SplitVectorAlongAxis(&acc, &rot.r[1], &accAlong, &accAcross);
    f32 dt = ClockDt((LinkClock*)g_gameClock);
    Vu0::Q(acc) = Vu0::MulXSum(Vu0::Q(accAlong), Vu0::Scalar(g_linkAlongDrag * dt + 1.0f), Vu0::Q(accAcross), Vu0::Scalar(gain * dt + 1.0f));
    if (self->subState == 0x32 || self->subState == 0x34) {
        if (ClockTime((LinkClock*)g_gameClock) - self->subStateStartTime < g_linkKickDuration) {
            f32 push = dt * g_linkKickAcceleration[0];
            if (self->subState == 0x32) {
                push = -push;
            }
            if (self->linkReversed != 0) {
                push = -push;
            }
            f32 l = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(across)));
            f32 gz = -self->gravity.z;
            f32 t = (gz * delta.z + l * (l * 0.5f)) / gz;
            push *= g_unitRange.Limit(g_linkKickCurve[0] + t * (g_linkKickCurve[1] + t * g_linkKickCurve[2]));
            Vu0::Q(acc) = Vu0::MulAddX(Vu0::Q(acc), Vu0::Q(rot.r[1]), Vu0::Scalar(push));
        }
    }
    f32 rate;
    f32 r = ApproachValueClampingVelocity(dist, speed, g_linkLengthMax - ((LinkAnchor*)self->boundObject)->fB0, ClockDt((LinkClock*)g_gameClock), g_linkLengthRamp, &rate);
    f32 lo = g_linkLengthMin;
    f32 hi = g_linkLengthMax;
    Vu0::Q(acc) = Vu0::MulX(Vu0::Q(acc), Vu0::Scalar((hi <? dist) / (lo >? r)));
    Vec02 v2;
    Vec02 lin;
    Vec02 ang;
    if (self->linkSystem != 0) {
        PlacedObject* o = ((LinkSystem*)self->linkSystem)->object;
        Attachment* a = o->positionAttachment;
        if (a != 0 && a->mode0 == 1) {
            Vec02 p;
            Vec02 v;
            a->vt->getPos(a, 0.0f, &p, &v);
            ComputePositionSpringAcceleration(o, ClockDt((LinkClock*)g_gameClock), &p, &v, &lin);
            TransformDirectionBetweenFrames((PlacedObject*)o->parent, 0, &lin, &lin);
        } else {
            lin = D_00248D30;
        }
        a = o->orientationAttachment;
        if (a != 0 && a->mode1 == 1) {
            Mat02 m;
            Vec02 w;
            a->vt->getRot(a, 0.0f, &m, &w);
            ComputeRotationSpringAcceleration(o, ClockDt((LinkClock*)g_gameClock), &m, &w, &ang);
            TransformDirectionBetweenFrames((PlacedObject*)o->parent, 0, &ang, &ang);
        } else {
            ang = D_00248D30;
        }
        u128 h = Vu0::ScalarAt(ClockDt((LinkClock*)g_gameClock));
        Vu0::Q(v2) = Vu0::MulAddX2(Vu0::Q(vel), Vu0::Q(lin), h, Vu0::Cross(Vu0::Q(ang), Vu0::Sub(Vu0::Q(pos), Vu0::Q(o->v140))), h);
    } else {
        v2 = vel;
    }
    Vec02 p;
    Vec02 v;
    Mat02 m;
    Vu0::Q(lin) = Vu0::MulX(Vu0::Add(Vu0::Q(w1), Vu0::Q(acc)), Vu0::Scalar(ClockDt((LinkClock*)g_gameClock) * 0.5f));
    BuildRotationFromVector(&lin, &m);
    u128 nd = Vu0::Rotate(m, Vu0::Q(dir));
    // The new direction times the length is written at each use: cse1 merges the two products
    // and qmtc2s, and the second Scalar's slot store, which reload deletes, depends on the first
    // (docs/toolchain/sched1.md, "A weight written again in the next statement").
    Vu0::Q(p) = Vu0::Add(Vu0::Q(pos), Vu0::MulX(nd, Vu0::Scalar(r)));
    Vu0::Q(v) = Vu0::Add(Vu0::Add(Vu0::Q(v2), Vu0::Cross(Vu0::Q(acc), Vu0::MulX(nd, Vu0::Scalar(r)))), Vu0::MulX(nd, Vu0::ScalarAt(rate)));
    *(u128*)&g = Vu0::Sub(Vu0::DivX(Vu0::Sub(Vu0::Q(v), Vu0::Q(self->v150)), Vu0::ScalarAt(ClockDt((LinkClock*)g_gameClock))), Vu0::Q(self->gravity));
    Vu0::Q(ang) = nd;
    if (self->linkSystem != 0) {
        SolvePlayerLinkSystem(self, ((LinkSystem*)self->linkSystem)->object, &pos, (const LinkVector*)&g, (LinkRow*)&self->linkAcceleration);
    } else {
        Vu0::Q(self->linkAcceleration) = Vu0::Q(g);
    }
}

// The product a b of two rotations: b's rows each rotated by a.
static inline void MulRotation(Mat02* out, const Mat02& a, const Mat02& b)
{
    Mat02 r;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Vu0::Q(x) = Vu0::RotateUntied(a, Vu0::Q(b.r[0]));
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateUntied(a, Vu0::Q(b.r[1]));
    r.r[1] = y;
    Vu0::Q(z) = Vu0::RotateUntied(a, Vu0::Q(b.r[2]));
    r.r[2] = z;
    *out = r;
}

extern f32 g_frameDt[];
void AddColliderForce(void* target, void* slot);

void TurnPlayerTowardLinkedObject(Player* self)
{
    Vec02 pos;
    Vec02 d;
    Mat02 a;
    Mat02 b;
    Mat02 r;
    AddColliderForce(self, (u8*)self + 0x22B0);
    GetObjectWorldPosition((BaseObject*)self->boundObject, &pos);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->v140));
    BuildShortestArcRotation(&g_unitZVector, &d, &a);
    BuildAxisAngleMatrix(&g_unitZVector, &b, self->heading);
    MulRotation(&r, a, b);
    TurnColliderTowardRotation(self, g_frameDt[0], &r, g_linkTurnRamp);
}

struct LinkTargetHolder { s32 pad0; void* target; };
void AddColliderForce(void* target, void* slot);
void AddColliderTorque(void* target, void* slot);

void SyncPlayerTarget(Player* self)
{
    AddColliderForce(((LinkTargetHolder*)self->linkSystem)->target, (u8*)self + 0x22D0);
    AddColliderTorque(((LinkTargetHolder*)self->linkSystem)->target, (u8*)self + 0x22E0);
}

f32 WrapAngle(f32 a);
struct RampProfile;
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
f32 ApproachValueWithRamp(f32 x, f32 y, f32 z, RampProfile* k, f32* out);
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
f32 ClampToMagnitude(f32 a, f32 b);
extern f32 g_gameTime;
extern f32 g_gameClock[];

static inline f32 ClampBetween(f32 v, f32 lo, f32 hi)
{
    if (v < lo) {
        return lo;
    }
    if (hi < v) {
        return hi;
    }
    return v;
}

struct LinkBlend_1CD0C8 { u8 pad0[0x34]; f32 f34; };
struct LinkRoot_1CD0C8 { s32 pad0; void* root; };
struct LinkMessage_1CD0C8 { u8 pad0[0x14]; f32 f14; f32 f18; };

void ControlPlayerOnLinkedObject(Player* self, void* pad)
{
    Vec02 pos;
    Vec02 dir;
    Vec02 local;
    Mat02 m;
    f32 stick;
    s32 toward = 0;
    s32 away = 0;
    GetLinkedObjectHeading(self, &self->heading);
    if (self->linkReversed != 0) {
        self->heading = WrapAngle(self->heading + 3.14159274f);
    }
    ComputeCameraRelativeStickHeading(g_camera, (PadRecord*)pad, 0, &stick);
    f32 diff = WrapAngle(stick - self->heading);
    if (0.3f < self->stickLevel) {
        f32 ad = __builtin_fabsf(diff);
        if (ad < 1.04719758f) {
            toward = 1;
            self->linkPushTime = g_gameTime;
        } else if (2.09439516f < ad) {
            away = 1;
            self->linkPushTime = g_gameTime;
        }
    } else {
        self->linkReturnState = -1;
    }
    GetObjectWorldPosition((BaseObject*)self->boundObject, &pos);
    Vu0::Set(dir, Vu0::NormalizeOr(Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->v140)), Vu0::Q(g_unitZVector)));
    BuildAxisAngleMatrix(&g_unitZVector, &m, self->heading);
    Vu0::Q(local) = Vu0::RotateTransposed(m, Vu0::Q(dir));
    f32 angle = WrapAngle(ArctangentOfRatio(local.z, local.x) - 1.57079637f);
    s32 state = self->subState;
    switch (state) {
    case 0x32:
        if (away) {
            state = 0x34;
        } else if (toward) {
            if (g_linkTowardHoldTime < g_gameTime - self->subStateStartTime) {
                self->linkReturnState = state;
                state = 0x33;
            }
        } else if (g_linkIdleDelay < g_gameTime - self->linkPushTime) {
            state = 0x33;
        }
        break;
    case 0x34:
        if (toward) {
            state = 0x32;
        } else if (away) {
            if (g_linkAwayHoldTime < g_gameTime - self->subStateStartTime) {
                self->linkReturnState = state;
                state = 0x33;
            }
        } else if (g_linkIdleDelay < g_gameTime - self->linkPushTime) {
            state = 0x33;
        }
        break;
    case 0x33:
        if (toward && self->linkReturnState != 0x32) {
            self->linkReturnState = -1;
            state = 0x32;
        } else if (away && self->linkReturnState != 0x34) {
            self->linkReturnState = -1;
            state = 0x34;
        } else if (__builtin_fabsf(angle) < g_linkAlignedAngle) {
            s32 slow = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(self->v150))) < g_linkSlowSpeed;
            if (slow) {
                state = 0x35;
            }
        }
        break;
    case 0x35:
        if (toward && self->linkReturnState != 0x32) {
            self->linkReturnState = -1;
            state = 0x32;
        } else if (away && self->linkReturnState != 0x34) {
            self->linkReturnState = -1;
            state = 0x34;
        } else if (__builtin_fabsf(angle) > g_linkMisalignedAngle) {
            s32 fast = g_linkFastSpeed < Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(self->v150)));
            if (fast) {
                state = 0x33;
            }
        }
        break;
    }
    SetPlayerState(self, 3, state);
    PlacePlayerOnLinkedObject(self);
    if (self->linkSystem != 0) {
        ClearRootTries((PlacedObject*)(((LinkRoot_1CD0C8*)self->linkSystem)->root));
    }
    f32 w0;
    f32 w1;
    if (self->subState == 0x35) {
        return;
    }
    switch (self->subState) {
    case 0x32:
        w0 = w1 = 1.0f;
        break;
    case 0x34:
        w0 = 1.0f;
        w1 = 0.0f;
        break;
    case 0x33:
        w0 = 0.0f;
        w1 = (0.5f < self->linkTowardRamp) ? 1.0f : 0.0f;
        break;
    }
    self->linkMoveRamp = ApproachValueWithRamp(self->linkMoveRamp, w0, g_gameClock[2], (RampProfile*)g_linkWeightRamp, 0);
    f32 b = ApproachValueWithRamp(self->linkTowardRamp, w1, g_gameClock[2], (RampProfile*)g_linkBlendRamp, 0);
    self->linkTowardRamp = b;
    f32 a = self->linkMoveRamp;
    self->linkTowardWeight = a * b;
    self->linkAwayWeight = a * (1.0f - b);
    self->linkIdleWeight = 1.0f - a;
    SetBlendItemWeights((BlendAnimationView*)self->linkBlend, 0xC, 3, &self->linkTowardWeight);
    f32 c = ClampBetween(angle / g_linkAngleScale, -1.0f, 1.0f);
    ((LinkMessage_1CD0C8*)self->stateAnimPlayer)->f18 = ClampToMagnitude((((LinkBlend_1CD0C8*)self->linkBlend)->f34 * (c + 1.0f) * 0.5f - ((LinkMessage_1CD0C8*)self->stateAnimPlayer)->f14) / g_gameClock[2], g_linkAngleRateLimit);
}


struct LinkedFrame { u8 pad00[0x18]; void* frame; u8 pad1C[0x34 - 0x1C]; BaseObject* item; };
typedef void (*LinkItemFn)(BaseObject* self, Vec02* a, f32 t, s32 b, Vec02* c, s32 d, s32 e, void* f);

// Lets go of a linked object that has got too far: the first beyond 50 units, the second, after
// asking its item, beyond 50 units squared.
void ReleaseFarPlayerLinks(Player* self)
{
    Vec02 pos;
    Vec02 q;
    u8* p = (u8*)self;
    LinkedFrame* a = *(LinkedFrame**)(p + 0x2210);
    if (a != 0) {
        TransformPointBetweenFrames((PlacedObject*)a->frame, 0, (Vec02*)((u8*)a + 0x40), &pos);
        if (Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(*(Vec02*)(*(u8**)(p + 0x23D4) + 0x140)), Vu0::Q(pos)))) > 50.0f) {
            *(s32*)(p + 0x2210) = 0;
            self->f4B8 = 0;
        }
    } else {
        if (*(LinkedFrame**)(p + 0x2214) != 0) {
            TransformPointBetweenFrames(0, (PlacedObject*)((*(LinkedFrame**)(p + 0x2214))->frame), (Vec02*)(*(u8**)(p + 0x23D4) + 0x140), &pos);
            LinkItemFn fn = (LinkItemFn)((void**)(*(LinkedFrame**)(p + 0x2214))->item->desc)[12];
            if (fn != 0) {
                fn((*(LinkedFrame**)(p + 0x2214))->item, &pos, *(f32*)(p + 0x2218), 0, &q, 0, 0, p + 0x2218);
            }
            if (Vu0::ToFloat(Vu0::Dot(Vu0::Q(q), Vu0::Q(q))) > 2500.0f) {
                *(s32*)(p + 0x2214) = 0;
            }
        }
    }
}


// Walks up the parents to the first object whose class has flag bit 2.
void SetFlaggedLinkContactMask(Collider* self, BaseObject* node, s32 flag)
{
    BaseObject* n = node;
    while (n != 0) {
        if ((n->desc->flags & 2) != 0) {
            break;
        }
        n = n->parent;
    }
    if (n != 0) {
        if (IsObjectAttached(n) != 0) {
            SetContactPairFlags(self->world, self->contacts,
                                ((Collider*)((PlacedObject*)n)->root)->contacts,
                                flag != 0 ? 0x40 : 0, flag != 0 ? 0 : 0x40);
        }
    }
    self->f4B8 = 0;
}

struct PooledContact;

// Adds the contacts of the player with the object node for the axes of flags (bits 1 2 4: always,
// bits 8 0x10 0x20: when the offset along that axis is under 0.0001), in the frame of axis.
void AddPlayerObjectContacts(Player* self, s32 flags, BaseObject* node, Vec02* origin, Vec02* axis, Vec02* offset)
{
    Vec02 d;
    Mat02 m;
    if (IsObjectAttached(node) == 0) {
        SetPlayerState(self, 2, 2);
        return;
    }
    s32 each = flags & 2;
    s32 first = flags & 1;
    s32 third = flags & 4;
    BaseObject* n = node;
    while (n != 0 && (n->desc->flags & 2) == 0) {
        n = n->parent;
    }
    Contact03** last;
    Contact03** head;
    if (n != 0) {
        ContactRow03* row = self->contacts->head;
        void* want = ((PlacedObject*)n)->root;
        while (row != 0 && (void*)row->other != want) {
            row = row->next;
        }
        head = (Contact03**)row;
        last = row->link;
    } else {
        last = &self->contacts4B4;
        head = last;
    }
    if (axis != 0) {
        BuildBasisFromXAndZHint(axis, &g_unitZVector, &m);
    } else {
        m = g_identityMatrix;
    }
    Vu0::Q(d) = Vu0::Sub(Vu0::Add(Vu0::Q(*offset), Vu0::Q(self->pathPoseOffset)), Vu0::Q(*origin));
    Vu0::Q(d) = Vu0::RotateTransposed(m, Vu0::Q(d));
    if (first != 0 || ((flags & 8) != 0 && d.x < 0.0001f)) {
        CreatePooledContact(d.x, self, n, offset, &m.r[0], first != 0 ? 11 : 10, 0, 0, head);
    }
    if (each != 0 || ((flags & 0x10) != 0 && d.y < 0.0001f)) {
        CreatePooledContact(d.y, self, n, offset, &m.r[1], each != 0 ? 11 : 10, 0, 0, head);
    }
    if (third != 0 || ((flags & 0x20) != 0 && d.z < 0.0001f)) {
        CreatePooledContact(d.z, self, n, offset, &m.r[2], third != 0 ? 11 : 10, third != 0 ? 0 : *(void**)((u8*)self + 0x6D4), 0, head);
    }
    *last = *head;
}

struct HeadingVector {
    f32 x;
    f32 y;
};

extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

void GetLinkedObjectHeading(Player* self, f32* heading)
{
    HeadingVector v;
    void* owner = *(void**)((u8*)self + 0x2204);
    TransformDirectionBetweenFrames((PlacedObject*)(*(void**)((u8*)owner + 0x18)), 0, (Vec02*)((u8*)owner + 0x50), (Vec02*)&v);
    *heading = ArctangentOfRatio(v.y, v.x);
}

struct LinkSource {
    u8 pad00[0x18];
    void* frame;            // 0x18
    u8 pad1C[0x40 - 0x1C];
    Vec02 point;            // 0x40
    u8 pad50[0xB0 - 0x50];
    f32 reach;              // 0xB0
};

struct LinkRecord {
    u8 pad00[0x80];
    PlacedObject* object;   // 0x80
};

void ComputePlayerLinkPose(Player* self, Vec02* pos, Mat02* rotA, Mat02* rotB)
{
    Vec02 a;
    Vec02 b;
    Vec02 gap;
    Mat02 arc;
    Mat02 axis;
    Vec02 k;
    LinkSource* source = (LinkSource*)self->boundObject;
    PlacedObject* held = ((LinkRecord*)((PlacedObject*)self->f61C)->linkRecord)->object;
    TransformPointBetweenFrames((PlacedObject*)source->frame, self, &source->point, &a);
    TransformPointBetweenFrames(0, self, &held->v140, &b);
    Vu0::Q(gap) = Vu0::Sub(Vu0::Q(a), Vu0::Q(b));
    BuildShortestArcRotation(&g_unitXVector, &gap, &arc);
    u128 here = Vu0::Q(a);
    u128 reach = Vu0::FromFloatAt(((LinkSource*)self->boundObject)->reach);
    Vu0::Q(k) = reach;
    Vu0::Q(a) = Vu0::MulAddX(here, Vu0::NormalizeOr(Vu0::Q(gap), Vu0::Q(D_00248D30)), reach);
    BuildAxisAngleMatrix(&g_unitXVector, &axis, g_linkPoseTiltA);
    MulRotation(rotA, arc, axis);
    BuildAxisAngleMatrix(&g_unitXVector, rotB, g_linkPoseTiltB);
    u128 turned = Vu0::Rotate(*rotB, Vu0::Q(((PlacedObject*)self->f23D4)->pos));
    u128 sum = Vu0::Add(Vu0::Q((*(PlacedObject**)((u8*)self + 0x23D0))->pos), turned);
    u128 moved = Vu0::Rotate(*rotA, sum);
    PlacedObject* base = (PlacedObject*)self->f61C;
    u128 total = Vu0::Add(Vu0::Q(base->pos), moved);
    Vu0::Q(k) = total;
    Vu0::Q(*pos) = Vu0::Add(Vu0::Q(base->pos), Vu0::Sub(Vu0::Q(a), total));
}

typedef u64 Quad128 __attribute__((mode(TI)));
Quad128 ApproachPointWithRamp(u128 from, u128 to, f32 limit, RampProfile* ramp, Vec02* vel);
struct Mat02;
void ApproachRotationWithRamp(Mat02* from, Mat02* to, RampProfile* ramp, Mat02* outRot, Vec02* outSpin, f32 limit);
extern f32 g_gameClock[];

struct LinkPoseTarget {
    u8 pad00[0x20];
    Vec02 pos;              // 0x20
    u8 pad30[0x40 - 0x30];
    Mat02 rot;              // 0x40
};

struct LinkPoseView {
    u8 pad00[0x22F0];
    Vec02 offset;           // 0x22F0
    Mat02 rotA;             // 0x2300
    Mat02 rotB;             // 0x2330
};

static inline void MulRotationInto(LinkPoseTarget* obj, const Mat02& a, const Mat02& b)
{
    Mat02 r;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Vu0::Q(x) = Vu0::RotateUntied(a, Vu0::Q(b.r[0]));
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateUntied(a, Vu0::Q(b.r[1]));
    r.r[1] = y;
    Vu0::Q(z) = Vu0::RotateUntied(a, Vu0::Q(b.r[2]));
    r.r[2] = z;
    obj->rot = r;
}

void UpdatePlayerLinkPose(Player* self)
{
    Vec02 pos;
    Mat02 a;
    Mat02 b;
    LinkPoseView* v = (LinkPoseView*)self;
    ComputePlayerLinkPose(self, &pos, &a, &b);
    *(Quad128*)&v->offset = ApproachPointWithRamp(*(Quad128*)&v->offset, *(const Quad128*)&D_00248D30, g_gameClock[2], (RampProfile*)g_linkPoseOffsetRamp, 0);
    ApproachRotationWithRamp(&v->rotA, (Mat02*)&g_identityMatrix, (RampProfile*)g_linkPoseRotationRamp, &v->rotA, 0, g_gameClock[2]);
    ApproachRotationWithRamp(&v->rotB, (Mat02*)&g_identityMatrix, (RampProfile*)g_linkPoseRotationRamp, &v->rotB, 0, g_gameClock[2]);
    Vu0::Q((*(LinkPoseTarget**)((u8*)self + 0x251C))->pos) = Vu0::Add(Vu0::Q(pos), Vu0::Q(v->offset));
    MulRotationInto(*(LinkPoseTarget**)((u8*)self + 0x251C), v->rotA, a);
    MulRotationInto(*(LinkPoseTarget**)((u8*)self + 0x2520), v->rotB, b);
    ApplyPoseSource((Attachment*)(*(void**)((u8*)self + 0x251C)), 1);
    ApplyPoseSource((Attachment*)(*(void**)((u8*)self + 0x2520)), 1);
}


void GetPlayerPose(Player* self, f32 t, void* out, void* extra)
{
    if (self->state == 3) {
        GetPlacedObjectRotationAt(self, t, (Mat02*)out, (Vec02*)extra);
    } else {
        GetTurningColliderPose(self, out, (Vec02*)extra, t);
    }
}
