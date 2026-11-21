// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_functions.h"
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
struct Mat3;
struct Vec4;

struct Mat3;
struct Vec4;


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

// Builds a combined blend animation of three entries from the record (the last weight starting at
// 1) and gives it in *a2 if requested.
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
    Vec4 a;
    Vec4 b;
};

// The right-hand side of the link's system, read as components by index.
struct __attribute__((aligned(16))) LinkVector {
    f32 v[4];
};

struct VectorConstraint;

// Works out the impulse at point that gives objects a and b the relative velocity target: for each
// axis it measures how the point's velocity on each object changes per unit impulse (mass, inverse
// inertia), then factors and solves the 3 by 3 system. Each object's linear and angular rows go to
// out; the second object takes the opposite sign.
void SolvePlayerLinkSystem(PlacedObject* a, PlacedObject* b, Vec4* point, const LinkVector* target, LinkRow* out)
{
    PlacedObject* objs[2];
    Vec4 pts[2];
    Vec4 axis;
    Vec4 cross;
    Vec4 scaled;
    Vec4 torque;
    LinkRow rows[2][3];
    Vec4 vel[2];
    Vec4 diff[3];
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
            Vu0::Vec mass = Vu0::Vec::ScalarAtValue(((Collider*)o)->mass);
            Vu0::Set(scaled, Vu0::DivX(Vu0::Vec::Of(axis), mass).q);
            ConstrainVectorByParentAnchor((Collider*)o, (VectorConstraint*)&((Collider*)o)->v440, &scaled, &rows[i][j].a, 0);
            ApplyColliderInverseInertia((Collider*)o, &cross, &torque);
            ConstrainVectorByParentAnchor((Collider*)o, (VectorConstraint*)&((Collider*)o)->v460, &torque, &rows[i][j].b, 0);
            ComputeColliderPointVelocity((Collider*)o, point, (ImpulseRow*)&rows[i][j], &vel[i]);
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
        TransformDirectionBetweenFrames(0, (PlacedObject*)objs[i]->parent, &out[i].a, &out[i].a);
        TransformDirectionBetweenFrames(0, (PlacedObject*)objs[i]->parent, &out[i].b, &out[i].b);
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

f32 ApproachValueClampingVelocity(f32 a, f32 b, f32 c, f32 d, void* self, f32* out);

// The player swinging on the link (states 0x32 and 0x34 pump it): the anchor's frame and
// motion, the swing's turning about the anchor eased and damped, its length kept, and the
// acceleration that gives it, handed to the link's system when there is one.
// v made unit length in place, or the fallback when it is shorter than 0.0001; its length.
static inline f32 NormalizeInPlace(Vec4* v, const Vec4& fallback)
{
    u128 len = Vu0::Length(Vu0::Q(*v));
    if (Vu0::ToFloat(len) < 0.0001f) {
        *v = fallback;
    } else {
        Vu0::Q(*v) = Vu0::DivX(Vu0::Q(*v), len);
    }
    return Vu0::ToFloatMoved(len);
}

// Places the player on the object it is bound to: takes the bound object's world position, rotation
// and the velocity of its parent frame, and sets the player's position, orientation and velocity
// from them (relative to the link's across and along directions).
void PlacePlayerOnLinkedObject(Player* self)
{
    Vec4 pos;
    Vec4 delta;
    Vec4 vel;
    Vec4 dir;
    Mat3 rot;
    Vec4 rel;
    Vec4 across;
    Vec4 along;
    Vec4 n1;
    Vec4 w1;
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
    Vec4 g;
    Vu0::Set(g, gp.q);
    Vu0::Vec a2 = Vu0::NormalizeOr(Vu0::Cross(Vu0::Vec::Of(dir), gp), Vu0::Vec::Of(g_unitYVector));
    Vec4 n2;
    Vu0::Set(n2, a2.q);
    Vec4 w2;
    Vu0::Set(w2, Vu0::MulX(a2, Vu0::Vec::Scalar(Vu0::ToFloat(Vu0::Length(Vu0::Vec::Of(g))) / dist)).q);
    f32 gain;
    if (self->subState == 0x32 || self->subState == 0x34) {
        gain = g_linkSwingAcrossDrag;
    } else {
        gain = g_linkRestAcrossDrag;
    }
    Vec4 acc;
    Vec4 accAlong;
    Vec4 accAcross;
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
    Vec4 v2;
    Vec4 lin;
    Vec4 ang;
    if (self->linkSystem != 0) {
        PlacedObject* o = ((LinkSystem*)self->linkSystem)->object;
        Attachment* a = o->positionAttachment;
        if (a != 0 && a->mode0 == 1) {
            Vec4 p;
            Vec4 v;
            a->vt->getPos(a, 0.0f, &p, &v);
            ComputePositionSpringAcceleration(o, ClockDt((LinkClock*)g_gameClock), &p, &v, &lin);
            TransformDirectionBetweenFrames((PlacedObject*)o->parent, 0, &lin, &lin);
        } else {
            lin = g_zeroVector;
        }
        a = o->orientationAttachment;
        if (a != 0 && a->mode1 == 1) {
            Mat3 m;
            Vec4 w;
            a->vt->getRot(a, 0.0f, &m, &w);
            ComputeRotationSpringAcceleration(o, ClockDt((LinkClock*)g_gameClock), &m, &w, &ang);
            TransformDirectionBetweenFrames((PlacedObject*)o->parent, 0, &ang, &ang);
        } else {
            ang = g_zeroVector;
        }
        u128 h = Vu0::ScalarAt(ClockDt((LinkClock*)g_gameClock));
        Vu0::Q(v2) = Vu0::MulAddX2(Vu0::Q(vel), Vu0::Q(lin), h, Vu0::Cross(Vu0::Q(ang), Vu0::Sub(Vu0::Q(pos), Vu0::Q(o->v140))), h);
    } else {
        v2 = vel;
    }
    Vec4 p;
    Vec4 v;
    Mat3 m;
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
static inline void MulRotation(Mat3* out, const Mat3& a, const Mat3& b)
{
    Mat3 r;
    Vec4 x;
    Vec4 y;
    Vec4 z;
    Vu0::Q(x) = Vu0::RotateUntied(a, Vu0::Q(b.r[0]));
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateUntied(a, Vu0::Q(b.r[1]));
    r.r[1] = y;
    Vu0::Q(z) = Vu0::RotateUntied(a, Vu0::Q(b.r[2]));
    r.r[2] = z;
    *out = r;
}

extern f32 g_frameDt[];

// Turns the player toward its bound object: adds the collider force, builds the rotation from the z
// axis to the direction of the object and spins it by the player's heading, and turns the collider
// toward it with the link turn ramp.
void TurnPlayerTowardLinkedObject(Player* self)
{
    Vec4 pos;
    Vec4 d;
    Mat3 a;
    Mat3 b;
    Mat3 r;
    AddColliderForce(self, &self->linkAcceleration);
    GetObjectWorldPosition((BaseObject*)self->boundObject, &pos);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->v140));
    BuildShortestArcRotation(&g_unitZVector, &d, &a);
    BuildAxisAngleMatrix(&g_unitZVector, &b, self->heading);
    MulRotation(&r, a, b);
    TurnColliderTowardRotation(self, g_frameDt[0], &r, g_linkTurnRamp);
}

struct LinkTargetHolder { s32 pad0; void* target; };

// Passes the player's force and torque (at 0x22D0 and 0x22E0) on to its link target collider.
void SyncPlayerTarget(Player* self)
{
    AddColliderForce((Collider*)((LinkTargetHolder*)self->linkSystem)->target, &self->linkForce);
    AddColliderTorque((Collider*)((LinkTargetHolder*)self->linkSystem)->target, &self->linkTorque);
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

struct LinkedPartBlend { u8 pad0[0x34]; f32 f34; };
struct LinkedRootHolder { s32 pad0; void* root; };
struct LinkAimMessage { u8 pad0[0x14]; f32 f14; f32 f18; };

// Per-frame control of the player while it is on a linked object: takes the heading from the object
// (reversed when linkReversed), compares the camera-relative stick direction with it to see whether
// the player pushes toward or away along the link, and moves the player accordingly.
void ControlPlayerOnLinkedObject(Player* self, void* pad)
{
    Vec4 pos;
    Vec4 dir;
    Vec4 local;
    Mat3 m;
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
        ClearRootTries((PlacedObject*)(((LinkedRootHolder*)self->linkSystem)->root));
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
    ((LinkAimMessage*)self->stateAnimPlayer)->f18 = ClampToMagnitude((((LinkedPartBlend*)self->linkBlend)->f34 * (c + 1.0f) * 0.5f - ((LinkAimMessage*)self->stateAnimPlayer)->f14) / g_gameClock[2], g_linkAngleRateLimit);
}


// The object a link was made to: its parent is the frame it is in, then the item to ask and
// a point of its own.
struct LinkedFrame : BaseObject {
    BaseObject* item;       // 0x34
    u8 pad38[0x40 - 0x38];
    Vec4 point;            // 0x40
};
typedef void (*LinkItemFn)(BaseObject* self, Vec4* a, f32 t, s32 b, Vec4* c, s32 d, s32 e, void* f);

// Lets go of a linked object that has got too far: the first beyond 50 units, the second, after
// asking its item, beyond 50 units squared.
void ReleaseFarPlayerLinks(Player* self)
{
    Vec4 pos;
    Vec4 q;
    LinkedFrame* a = (LinkedFrame*)self->previousBoundObject;
    if (a != 0) {
        TransformPointBetweenFrames((PlacedObject*)a->parent, 0, &a->point, &pos);
        if (Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(((PlacedObject*)self->f23D4)->v140), Vu0::Q(pos)))) > 50.0f) {
            self->previousBoundObject = 0;
            self->stateBits = 0;
        }
    } else {
        if (self->previousAimCurve != 0) {
            TransformPointBetweenFrames(0, (PlacedObject*)((LinkedFrame*)self->previousAimCurve)->parent, &((PlacedObject*)self->f23D4)->v140, &pos);
            LinkItemFn fn = (LinkItemFn)((void**)((LinkedFrame*)self->previousAimCurve)->item->desc)[12];
            if (fn != 0) {
                fn(((LinkedFrame*)self->previousAimCurve)->item, &pos, self->f2218, 0, &q, 0, 0, &self->f2218);
            }
            if (Vu0::ToFloat(Vu0::Dot(Vu0::Q(q), Vu0::Q(q))) > 2500.0f) {
                self->previousAimCurve = 0;
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
    self->stateBits = 0;
}

struct PooledContact;

// Adds the contacts of the player with the object node for the axes of flags (bits 1 2 4: always,
// bits 8 0x10 0x20: when the offset along that axis is under 0.0001), in the frame of axis.
void AddPlayerObjectContacts(Player* self, s32 flags, BaseObject* node, Vec4* origin, Vec4* axis, Vec4* offset)
{
    Vec4 d;
    Mat3 m;
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
    BodyContact** last;
    BodyContact** head;
    if (n != 0) {
        ContactRow03* row = self->contacts->head;
        void* want = ((PlacedObject*)n)->root;
        while (row != 0 && (void*)row->other != want) {
            row = row->next;
        }
        head = (BodyContact**)row;
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
        CreatePooledContact(d.z, self, n, offset, &m.r[2], third != 0 ? 11 : 10, third != 0 ? 0 : *(void**)&self->probeVertex, 0, head);
    }
    *last = *head;
}

struct HeadingVector {
    f32 x;
    f32 y;
};

extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

// Gives the heading, as an angle in the x/y plane, of the linked owner's direction in the world
// frame.
void GetLinkedObjectHeading(Player* self, f32* heading)
{
    HeadingVector v;
    BaseObject* owner = self->boundObject;
    // the bound object's class is not known: a vector at 0x50
    TransformDirectionBetweenFrames((PlacedObject*)owner->parent, 0, (Vec4*)((u8*)owner + 0x50), (Vec4*)&v);
    *heading = ArctangentOfRatio(v.y, v.x);
}

struct LinkSource {
    u8 pad00[0x18];
    void* frame;            // 0x18
    u8 pad1C[0x40 - 0x1C];
    Vec4 point;            // 0x40
    u8 pad50[0xB0 - 0x50];
    f32 reach;              // 0xB0
};

struct LinkRecord {
    u8 pad00[0x80];
    PlacedObject* object;   // 0x80
};

// Computes the pose that the player's two link attachments should have: the vector from the
// player's anchor on the bound object to the held object, the shortest-arc rotation from the x axis
// to it, and the position and two rotations (the reach scaled) that go to the output.
void ComputePlayerLinkPose(Player* self, Vec4* pos, Mat3* rotA, Mat3* rotB)
{
    Vec4 a;
    Vec4 b;
    Vec4 gap;
    Mat3 arc;
    Mat3 axis;
    Vec4 k;
    LinkSource* source = (LinkSource*)self->boundObject;
    PlacedObject* held = ((LinkRecord*)((PlacedObject*)self->f61C)->linkRecord)->object;
    TransformPointBetweenFrames((PlacedObject*)source->frame, self, &source->point, &a);
    TransformPointBetweenFrames(0, self, &held->v140, &b);
    Vu0::Q(gap) = Vu0::Sub(Vu0::Q(a), Vu0::Q(b));
    BuildShortestArcRotation(&g_unitXVector, &gap, &arc);
    u128 here = Vu0::Q(a);
    u128 reach = Vu0::FromFloatAt(((LinkSource*)self->boundObject)->reach);
    Vu0::Q(k) = reach;
    Vu0::Q(a) = Vu0::MulAddX(here, Vu0::NormalizeOr(Vu0::Q(gap), Vu0::Q(g_zeroVector)), reach);
    BuildAxisAngleMatrix(&g_unitXVector, &axis, g_linkPoseTiltA);
    MulRotation(rotA, arc, axis);
    BuildAxisAngleMatrix(&g_unitXVector, rotB, g_linkPoseTiltB);
    u128 turned = Vu0::Rotate(*rotB, Vu0::Q(((PlacedObject*)self->f23D4)->pos));
    u128 sum = Vu0::Add(Vu0::Q(((PlacedObject*)self->f23D0)->pos), turned);
    u128 moved = Vu0::Rotate(*rotA, sum);
    PlacedObject* base = (PlacedObject*)self->f61C;
    u128 total = Vu0::Add(Vu0::Q(base->pos), moved);
    Vu0::Q(k) = total;
    Vu0::Q(*pos) = Vu0::Add(Vu0::Q(base->pos), Vu0::Sub(Vu0::Q(a), total));
}

typedef u64 Quad128 __attribute__((mode(TI)));
Quad128 ApproachPointWithRamp(u128 from, u128 to, f32 limit, RampProfile* ramp, Vec4* vel);
struct Mat3;
void ApproachRotationWithRamp(Mat3* from, Mat3* to, RampProfile* ramp, Mat3* outRot, Vec4* outSpin, f32 limit);
extern f32 g_gameClock[];

struct LinkPoseTarget {
    u8 pad00[0x20];
    Vec4 pos;              // 0x20
    u8 pad30[0x40 - 0x30];
    Mat3 rot;              // 0x40
};

struct LinkPoseView {
    u8 pad00[0x22F0];
    Vec4 offset;           // 0x22F0
    Mat3 rotA;             // 0x2300
    Mat3 rotB;             // 0x2330
};

static inline void MulRotationInto(LinkPoseTarget* obj, const Mat3& a, const Mat3& b)
{
    Mat3 r;
    Vec4 x;
    Vec4 y;
    Vec4 z;
    Vu0::Q(x) = Vu0::RotateUntied(a, Vu0::Q(b.r[0]));
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateUntied(a, Vu0::Q(b.r[1]));
    r.r[1] = y;
    Vu0::Q(z) = Vu0::RotateUntied(a, Vu0::Q(b.r[2]));
    r.r[2] = z;
    obj->rot = r;
}

// Per-frame update of the player's link attachments: eases their offset and two rotations back
// toward zero and identity, applies them on top of the pose from ComputePlayerLinkPose, and applies
// both attachments.
void UpdatePlayerLinkPose(Player* self)
{
    Vec4 pos;
    Mat3 a;
    Mat3 b;
    LinkPoseView* v = (LinkPoseView*)self;
    ComputePlayerLinkPose(self, &pos, &a, &b);
    *(Quad128*)&v->offset = ApproachPointWithRamp(*(Quad128*)&v->offset, *(const Quad128*)&g_zeroVector, g_gameClock[2], (RampProfile*)g_linkPoseOffsetRamp, 0);
    ApproachRotationWithRamp(&v->rotA, (Mat3*)&g_identityMatrix, (RampProfile*)g_linkPoseRotationRamp, &v->rotA, 0, g_gameClock[2]);
    ApproachRotationWithRamp(&v->rotB, (Mat3*)&g_identityMatrix, (RampProfile*)g_linkPoseRotationRamp, &v->rotB, 0, g_gameClock[2]);
    Vu0::Q(((LinkPoseTarget*)self->snapshotPoseFirst)->pos) = Vu0::Add(Vu0::Q(pos), Vu0::Q(v->offset));
    MulRotationInto((LinkPoseTarget*)self->snapshotPoseFirst, v->rotA, a);
    MulRotationInto((LinkPoseTarget*)self->snapshotPoseSecond, v->rotB, b);
    ApplyPoseSource((Attachment*)self->snapshotPoseFirst, 1);
    ApplyPoseSource((Attachment*)self->snapshotPoseSecond, 1);
}


// Gives the pose at time t: from the placed object's rotation in state 3, else from the turning
// collider.
void GetPlayerPose(Player* self, f32 t, void* out, void* extra)
{
    if (self->state == 3) {
        GetPlacedObjectRotationAt(self, t, (Mat3*)out, (Vec4*)extra);
    } else {
        GetTurningColliderPose(self, out, (Vec4*)extra, t);
    }
}
