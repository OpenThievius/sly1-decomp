// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x5E (RedirectObject) and class 0x14 (TintBlendCollider), from 0x1DDCE0 to 0x1DFD48. Its .data opens
// with the vector func_001DDCE0 reads (0x275730), just after the zeroed globals that close the
// previous file's, and ends at 0x2758D0, where class75_list.cpp's starts; its .rodata is the one
// float func_001DFBE0 reads (0x24DCA8).
#include "common.h"
#include "vu0.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "state_trigger.h"
#include "cone_volume.h"
#include "redirect_object.h"
#include "world.h"
#include "screen_element.h"
#include "font.h"
#include "globals.h"
#include "game_progress.h"
#include "level_entry.h"
#include "message_body.h"
#include "owner_message.h"
#include "shapes.h"
#include "state_walker.h"
#include "pad_record.h"
#include "camera.h"
#include "functions/camera.h"
#include "functions/camera_controller.h"
#include "functions/collider.h"
#include "functions/collider_contact.h"
#include "functions/game_progress.h"
#include "functions/heap.h"
#include "functions/matrix.h"
#include "functions/pad_input.h"
#include "functions/path_follower.h"
#include "functions/placed_object.h"
#include "functions/placed_object_model.h"
#include "functions/player.h"
#include "functions/state_walker.h"
#include "functions/switched_collider.h"
#include "functions/tint_blend_collider.h"
#include "functions/turning_collider.h"
#include "functions/warp_menu.h"
#include "functions/world.h"
#include "functions/world_contacts.h"
struct Mat02;
struct Vec02;


// Types other files define, named by the parameters of their functions declared here.
struct ObjectLink;
struct ScaledTransform;

// The links func_001DE808 resolves (ResolveObjectLinks: flags, id, offset), and the word after
// them that aligns the next table.
struct ColliderLink { s32 flags, id, offset; };
struct ColliderLinkTable { ColliderLink e[9]; s32 end; };


Quad16 D_00275730 = { 0x42C80000, 0, 0, 0 };
Quad16 D_00275740 = { { 0x3F800000, 0, 0, 0 } };
ColliderLinkTable g_tintBlendColliderLinks = { {
    { 0x0, 0x34D, 0x6DC }, { 0x0, 0x350, 0x758 }, { 0x4, 0x60, 0x748 },
    { 0x4, 0x50, 0x750 }, { 0x4, 0x34E, 0x744 }, { 0x2, 0x161, 0x588 },
    { 0x2, 0x162, 0x58C }, { 0x2, 0x163, 0x590 }, { 0x4, 0x160, 0x584 }
    }, 0 };
f32 D_002757C0[4] = { 0.0f, 2.0f, 0.0f, 0.0f };
f32 D_002757D0[1] = { 6.0f };
f32 D_002757D4 = 3.0f;
Vec02 g_reachCurve = { 0.0f, 0.0f, 800.0f, 0.0f };
f32 g_reachRange[4] = { 0.0f, 800.0f, 0.0f, 0.0f };
f32 g_tintLeanCurve[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
f32 g_leanTiltFactor[4] = { 0.150000006f, 0.0f, 0.0f, 0.0f };
f32 D_00275820[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
f32 D_00275830[4] = { -0.200000003f, 0.0f, 0.0f, 0.0f };
f32 D_00275840[4] = { 0.0f, 0.00124999997f, 0.0f, 0.0f };
f32 D_00275850[4] = { 0.0f, 2.0f, -1.0f, 0.0f };
f32 D_00275860 = 15.0f;
f32 D_00275864 = 10.0f;
Vec02 D_00275870 = { 1.0f, 0.0f, -0.75f, 0.0f };
f32 D_00275880[4] = { 0.699999988f, 0.300000012f, 0.0f, 0.0f };
f32 D_00275890 = 0.5f;
f32 D_00275894 = 700.0f;
f32 D_00275898 = 650.0f;
f32 D_0027589C = 650.0f;
f32 D_002758A0 = 300.0f;
f32 D_002758A4 = 400.0f;
f32 D_002758A8 = -100.0f;
f32 D_002758AC = 5.0f;
f32 D_002758B0[4] = { 1.5f, 0.0f, 0.0f, 0.0f };
f32 D_002758C0[4] = { 0.0f, 2.0f, 0.0f, 0.0f };




void InitRedirectObject(RedirectObject* self)
{
    InitPlacedObject(self);
    self->q320 = D_00275730;
}


void StartRedirectObject(RedirectObject* self)
{
    PlacedObject* p;
    BaseObject* c;
    RedirectStep* step;

    StartPlacedObject(self);
    if (self->parent != 0 && IsObjectOfKind(self->parent, 0x5E) != 0) {
        return;
    }
    p = self;
    if (self != 0) {
        do {
            self->chainCount++;
            c = (BaseObject*)p->children.head;
            while (c != 0 && IsObjectOfKind(c, 0x5E) == 0) {
                c = c->next;
            }
            p = (PlacedObject*)c;
        } while (c != 0);
    }
    if (self->chainCount < 2 && self->f310 == 0) {
        self->chainCount = 0;
        return;
    }
    self->chainCount++;
    self->steps = (RedirectStep*)AllocateZeroedFrontMemory(self->chainCount << 6);
    step = self->steps;
    p = self;
    if (self != 0) {
        do {
            ((RedirectObject*)p)->target = self;
            step->node = p;
            step->pos = p->v140;
            *(u32*)&step->length = Vu0::ToBits(Vu0::Length(Vu0::Q(p->pos)));
            c = (BaseObject*)p->children.head;
            while (c != 0 && IsObjectOfKind(c, 0x5E) == 0) {
                c = c->next;
            }
            p = (PlacedObject*)c;
            if (c != 0) {
                step->below = p->pos;
            } else {
                step->below = *(Vec02*)&self->q320;
            }
            step++;
        } while (c != 0);
    }
    TransformPointBetweenFrames(step[-1].node, 0, &step[-1].below, &step->pos);
    step->length = step[-1].length;
}

extern s32 g_frameCount;
extern f32 g_gameClock[];
f32 SplitVectorAlongAxis(Vec02* v, const Vec02* axis, Vec02* along, Vec02* rest);
void OrthonormalizeMatrix(Mat02* m);
Mat02 MultiplyByTransposedMatrix3x3(const Mat02& a, const Mat02& b);

// The clock's step, read through the clock's address.
static inline const f32& ClockStep(const f32* clock) { return clock[2]; }
// The product a b of two rotations, returned (g++'s named return value, so that the rows are
// stored where the caller's temporary is, with no address register). b's rows are read through a
// pointer (mul_rotation.h's Indexed forms: retail's `lqc2 0x30(v0); addiu v0, v0, 0x30; lqc2
// 0x10(v0)`); rows 0 and 1 store the result before the row local, row 2 after, as retail's P3 and
// else-branch products do (P1 and P2 order theirs either way).
static inline Mat02 MulRotationValue(const Mat02& a, const Mat02& b) return r
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    const u128* q = (const u128*)&b;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Vu0::Q(x) = *(u128*)&r.r[0] = Vu0::RotateRows(a0, a1, a2, q[0]);
    Vu0::Q(y) = *(u128*)&r.r[1] = Vu0::RotateRows(a0, a1, a2, q[1]);
    *(u128*)&r.r[2] = Vu0::Q(z) = Vu0::RotateRows(a0, a1, a2, q[2]);
}

// The same with b's rows read through Vu0::Q, which CSE folds into frame offsets: the R * M
// product, whose b is the frame's M (through a pointer the rows are read via the hoisted &M and the
// stores fall between them).
static inline Mat02 MulRotationValue2(const Mat02& a, const Mat02& b) return r
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    Vec02 x;
    Vec02 y;
    Vec02 z;
    *(u128*)&r.r[0] = Vu0::Q(x) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
    *(u128*)&r.r[1] = Vu0::Q(y) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
    *(u128*)&r.r[2] = Vu0::Q(z) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
}

void SimulateRedirectChain(RedirectObject* self)
{
    typedef Vu0::Vec Vec;
    if (self->frameStamp == g_frameCount) {
        return;
    }
    self->frameStamp = g_frameCount;
    UpdateLinkConstraint(self);
    if (self->steps == 0) {
        return;
    }
    s32 first = self->f310 != 0 ? 1 : 2;
    if (self->steps[first - 1].node->orientationAttachment != 0) {
        self->targetIsSelf = 1;
        return;
    }
    s32 i;
    RedirectStep* step;
    RedirectStep* prev;
    Vec02 a;
    Vec02 d;
    Vec02 axis;
    Vec02 b;
    Vec02 c;
    if (self->targetIsSelf != 0) {
        for (i = 0; i < self->chainCount - 1; i++) {
            step = &self->steps[i];
            step->pos = step->node->v140;
        }
        TransformPointBetweenFrames(step[-1].node, 0, &step[-1].below, &step->pos);
        for (i = 0; i < self->chainCount - 1; i++) {
            ComputeObjectMotionInFrame(step->node, 0, &step[1].pos, &step[1].vel, 0, 0, 0);
        }
        self->targetIsSelf = 0;
    }
    step = self->steps;
    step->pos = self->v140;
    ComputeObjectMotionInFrame(self, 0, &step->pos, &step->vel, 0, 0, 0);
    if (self->f310 == 0) {
        step++;
        TransformPointBetweenFrames(self, 0, &step[-1].below, &step->pos);
        ComputeObjectMotionInFrame(self, 0, &step->pos, &step->vel, 0, 0, 0);
    }
    for (i = first; i < self->chainCount; i++) {
        step = &self->steps[i];
        *(Vec*)&step->vel = Vu0::MulAddX(Vec::Of(step->vel), Vec::Of(self->gravity), Vec::ScalarAt(ClockStep(g_gameClock)));
    }
    f32 h = ClockStep(g_gameClock) / (f32)self->iterations;
    s32 k;
    for (k = 0; k < self->iterations; k++) {
        if (self->f310 != 0) {
            *(Vec*)&d = Vu0::RotateUntied(self->m1A0, Vec::Of(self->steps[0].below));
            if (self->parent != 0) {
                *(Vec*)&d = Vu0::RotateUntied(((PlacedObject*)self->parent)->m110, Vec::Of(d));
            }
        } else {
            *(Vec*)&d = Vu0::Sub(Vec::Of(self->steps[1].pos), Vec::Of(self->steps[0].pos));
        }
        for (i = first; i < self->chainCount; i++) {
            step = &self->steps[i];
            prev = &self->steps[i - 1];
            *(Vec*)&a = Vu0::Sub(Vec::Of(step->pos), Vec::Of(prev->pos));
            *(Vec*)&b = Vu0::Sub(Vec::Of(step->vel), Vec::Of(prev->vel));
            f32 angle = ComputeAngleBetweenVectors(&a, &d, &axis);
            if (self->maxBend < angle) {
                Mat02 r;
                BuildAxisAngleMatrix(&axis, &r, angle - self->maxBend);
                *(Vec*)&a = Vu0::Rotate(r, Vec::Of(a));
                *(Vec*)&step->pos = Vu0::Add(Vec::Of(prev->pos), Vec::Of(a));
            }
            f32 one = 1.0f;
            f32 rel = -self->relDrag * h;
            rel = one <? rel;
            f32 drag = -self->drag * h;
            drag = one <? drag;
            f32 bend = self->bendStiffness * angle * h;
            *(Vec*)&c = Vu0::Cross(Vec::Of(axis), Vec::Of(a));
            *(Vec*)&step->vel = Vu0::MulAddX3(Vec::Of(step->vel), Vec::Scalar(rel), Vec::Of(b), Vec::Scalar(drag),
                                             Vec::Of(step->vel), Vec::Scalar(bend), Vec::Of(c));
            *(Vec*)&step->pos = Vu0::MulAddX(Vec::Of(step->pos), Vec::Of(step->vel), Vec::Scalar(h));
            d = a;
        }
        for (i = first; i < self->chainCount; i++) {
            step = &self->steps[i];
            prev = &self->steps[i - 1];
            Vec diff = Vu0::Sub(Vec::Of(step->pos), Vec::Of(prev->pos));
            *(Vec*)&axis = diff;
            *(Vec*)&axis = Vu0::NormalizeOr(diff, Vec::Of(g_unitXVector));
            *(Vec*)&step->pos = Vu0::MulAddX(Vec::Of(prev->pos), Vec::Of(axis), Vec::ScalarAt(step->length));
            Vec02 along;
            Vec02 rest;
            SplitVectorAlongAxis(&prev->vel, &axis, &along, 0);
            SplitVectorAlongAxis(&step->vel, &axis, 0, &rest);
            *(Vec*)&step->vel = Vu0::Add(Vec::Of(along), Vec::Of(rest));
        }
    }
    Vec02 v;
    Mat02 R;
    Mat02 M;
    Mat02 m;
    if (self->f310 != 0) {
        if (self->parent != 0) {
            m = ((PlacedObject*)self->parent)->m110;
        } else {
            m = g_identityMatrix;
        }
    } else {
        m = self->m110;
    }
    for (i = first - 1; i < self->chainCount - 1; i++) {
        step = &self->steps[i];
        *(Vec*)&a = Vu0::Sub(Vec::Of(step[1].pos), Vec::Of(step->pos));
        Rec2195_224* rec = step->node->linkRecord;
        if (rec != 0) {
            M = MulRotationValue(MulRotationValue(MulRotationValue(m, *(Mat02*)((u8*)rec + 0x30)), step->node->m1A0),
                                 *(Mat02*)step->node->linkRecord);
        } else {
            M = MulRotationValue(m, step->node->m1A0);
        }
        *(Vec*)&v = Vu0::Rotate(M, Vec::Of(step->below));
        BuildRotationBetweenVectors(&v, &a, (f32*)&R);
        M = MulRotationValue2(R, M);
        OrthonormalizeMatrix(&M);
        step->node->m110 = M;
        step->node->rot = MultiplyByTransposedMatrix3x3(m, M);
        m = M;
    }
    PlacedObject* last = self->steps[first - 1].node;
    if (last->desc->m12 != 0) {
        last->desc->m12(last);
    }
}


void MarkRedirectToSelf(RedirectObject* self, PlacedObject* other)
{
    if (self->target == self) {
        self->targetIsSelf = 1;
    }
    CopyPlacedObjectFrame(self, other);
}


extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

void InitTintBlendCollider(TintBlendCollider* self)
{
    f32 f;

    InitTurningCollider(self);
    f = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    self->heading = f;
    BuildAxisAngleMatrix(&g_unitZVector, (Mat02*)((u8*)self + 0x660), f);
    self->state = -1;
    self->tintStartTime = -10.0f;
    (*(Quad16*)&self->headingWeightCurve) = D_00275740;
}

// EXACT: literal 1 stores (no `one` local), `||` condition, D_00262E10 compared as a pointer

struct AttachedEffect { void** vtbl; };
typedef void (*LinkTargetFn)(void* self, void* a1, s32 a2);
typedef void (*AttachedEffectFn)(void* self);



void StartTintBlendCollider(TintBlendCollider* self)
{
    TintBlendCollider* s = self;
    s32 flag;

    StartTurningCollider(self);
    ResolveObjectLinks(self, 9, (ObjectLink*)&g_tintBlendColliderLinks);
    ((LinkTargetFn)s->desc03()->m34)(self, s->followedMesh, 1);
    AddMatrixAttachment((PlacedObject*)s->f748, 5, (Attachment**)&s->f74C);
    ((u8*)s->f74C)[0x10] = 1;
    ((u8*)s->f74C)[0x11] = 1;
    ((AttachedEffectFn)((AttachedEffect*)s->f748)->vtbl[47])(s->f748);
    AddMatrixAttachment((PlacedObject*)s->f750, 5, (Attachment**)&s->f754);
    ((u8*)s->f754)[0x11] = 1;
    ((AttachedEffectFn)((AttachedEffect*)s->f750)->vtbl[47])(s->f750);
    s->walker = (StateWalker*)CreateStateWalker((StateGraph*)s->walkerGraph, self, -1, 1);
    if (s->f73C == 0 || g_player == 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    SetTintBlendColliderState(self, flag);
    s->f598 = self;
    s->f594 = 150.0f;
}

// NEAR: the call sequence, the list walk and the frame (0xC0) match; the scale constant D_002757D0 is held in s8 in retail but the C here addresses it through a pointer, so the register numbering of the constants 1 and 4 and the float tail differ (40 differing lines).

struct TintGlowEffect;
typedef s32 (*ContactClaimFn)(void* self, void* a1, void* a2);
typedef void (*OwnerMessageFn)(void* self, void* a1);
extern f32 g_gameClock[];


void UpdateTintBlendCollider(TintBlendCollider* self, f32 dt)
{
    OwnerMessage loc;
    f32 f20;
    Contact03* s1;
    Collider* s0;
    s32 v;
    s32 idx;

    UpdateTurningCollider(self, dt);
    if (HasAnimationDrivenAttachment(self) != 0) {
        ResetTintBlendColliderOrientation(self);
    }
    Contact03* head = ((Contact03*)self->heldContacts);
    if (head != 0) {
        s1 = head;
        do {
            idx = (s1->end[0].body != self);
            s0 = s1->end[1 - idx].part;
            while (s0 != 0 && s0->partMode == 0) {
                s0 = (Collider*)s0->parent;
            }
            if (s0 != 0) {
                v = s0->partMode;
                if (v == 1 || v == 4) {
                    InitOwnerMessage(&loc, 0, s0);
                    while (s0 != 0) {
                        if (((ContactClaimFn)s0->desc03()->m47)(s0, s1, &loc)) {
                            break;
                        }
                        s0 = (Collider*)s0->parent;
                    }
                    ((OwnerMessageFn*)self->desc)[80](self, &loc);
                }
            }
            s1 = s1->next;
        } while (s1 != 0);
        FreePooledContactChain(self->world, ((Contact03*)self->heldContacts));
        self->heldContacts = 0;
    }
    {
        f32 d = g_gameClock[1] - self->tintStartTime;
        f32 x = D_002757C0[0] + d * (D_002757C0[1] + d * D_002757C0[2]);
        f32 c0 = ((f32*)&g_unitRange)[0];
        f32 c1 = ((f32*)&g_unitRange)[1];
        if (x < c0) {
            f20 = c0;
        } else if (c1 < x) {
            f20 = c1;
        } else {
            f20 = x;
        }
    }
    SetScaledPositionSpring((PlacedObject*)self->f748, f20 * D_002757D0[0]);
    SetScaledRotationSpring((PlacedObject*)self->f748, f20 * D_002757D4);
    if (self->tinted != 0 && self->state != 2) {
        f32 e = g_gameClock[1] - self->tintFadeTime;
        if (2.0f < e) {
            self->tinted = 0;
        }
    }
}

extern f32 g_frameDt;

void ResetTintBlendColliderOrientation(TintBlendCollider* self)
{
    f32 heading, pitch, speed;
    ComputeObjectSteeringHeading(g_frameDt, self->heading, self, 0, 0, &heading, &pitch, &speed);
    self->heading = heading;
    BuildYawPitchMatrix(heading, pitch, &self->headingMatrix);
    Vu0::Q(self->headingVelocity) = Vu0::FromFloats(-speed, 0.0f, 0.0f);
}


void FinishTintBlendColliderRequest(TintBlendCollider* self)
{
    FinishSwitchedCollider(self);
    SetTintBlendColliderState(self, 1);
}

extern s32 g_movieChecksumFailed;

// The collider's effect (its frame) and a body's velocity and rotation, as this function reads
// them.
struct TintPart { u8 pad00[0x18]; PlacedObject* frame; };
struct TintBody { u8 pad00[0x20]; Vec02 v20; u8 pad30[0x40 - 0x30]; Mat02 m40; };
typedef void (*TintSelfFn)(void* self);

// A tuning curve at z: poly[0] + poly[1] z + poly[2] z^2.
static inline f32 Quadratic(const f32* poly, f32 z)
{
    return poly[0] + z * (poly[1] + z * poly[2]);
}

// The rows of m, each turned by r, returned by value (g++'s named return value).
static inline Mat02 RotatedRows(const Mat02& r, const Mat02& m) return out
{
    const u128* q = (const u128*)&m;
    Mat02 t;
    Vu0::Q(t.r[0]) = Vu0::RotateUntied(r, q[0]);
    out.r[0] = t.r[0];
    Vu0::Q(t.r[1]) = Vu0::RotateUntied(r, q[1]);
    out.r[1] = t.r[1];
    Vu0::Q(t.r[2]) = Vu0::RotateUntied(r, q[2]);
    out.r[2] = t.r[2];
}

// Slot 0x134: the collider under the pad. It follows the state walker's keys, turns to the
// stick's heading through the camera, leans and reaches by the stick's deflection (the tuning
// curves at D_002757E0 to D_00275864), sets its orientation and its effect's body rotation,
// and blends the body's velocity towards the stick.
void ControlTintBlendCollider(TintBlendCollider* self, f32 dt, PadRecord* pad)
{
    Vec02 offset;
    Vec02 axis;
    Mat02 tilt;
    Mat02 turn;
    Mat02 m;
    Mat02 rot;
    s32 cur;
    s32 tgt;
    f32 stick;
    if (HasAnimationDrivenAttachment(self) != 0) {
        return;
    }
    GetStateWalkerCurrentKey(self->walker, &cur);
    GetStateWalkerTargetKey(self->walker, &tgt);
    if (self->state == 2) {
        if (cur == 0x352) {
            ((TintSelfFn*)self->desc)[84](self);
        } else if (self->f738 != 0 && 0.7f < pad->secondStickMagnitude) {
            ((TintSelfFn*)self->desc)[84](self);
            TeleportStateWalker((StateWalker*)self->walker, 0x352);
            GetStateWalkerCurrentKey(self->walker, &cur);
            GetStateWalkerTargetKey(self->walker, &tgt);
        }
    }
    if ((u32)(cur - 0x352) >= 2) {
        return;
    }
    if (tgt != -1 && tgt != 0x352 && tgt != 0x353) {
        return;
    }
    HandleStepSequenceSkipButtons(self, pad);
    if (IsTopCameraController(&g_camera->ctl454) == 0 && 0.7f < pad->secondStickMagnitude) {
        ComputeCameraRelativeStickHeading(g_camera, pad, 1, &self->heading);
        if (__builtin_fabsf(WrapAngle(self->heading - ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x))) < 0.5f && g_movieChecksumFailed == 0) {
            SetStateWalkerTarget((StateWalker*)self->walker, 0x353);
        }
    } else {
        SetStateWalkerTarget((StateWalker*)self->walker, 0x352);
    }
    ComputeCameraRelativeStickHeading(g_camera, pad, 0, &stick);
    f32 reach = ((ValueRange*)g_reachRange)->Clamp(Quadratic(&g_reachCurve.x, pad->stickMagnitude));
    ComputePolarOffset((Vec3*)&offset, stick + 3.14159274f, reach, 0.0f);
    ComputePolarOffset((Vec3*)&axis, stick, 1.0f, 0.0f);
    Vu0::Q(axis) = Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(axis));
    f32 lean = g_unitRange.Limit(Quadratic(g_tintLeanCurve, pad->stickMagnitude));
    BuildAxisAngleMatrix(&axis, &tilt, g_leanTiltFactor[0] * lean);
    BuildAxisAngleMatrix(&g_unitZVector, &turn, self->heading);
    // Row 0 is stored after rows 1 and 2: the six stores of this block tie in sched1 and go in
    // the order they are written (docs/toolchain/sched1.md, "Argument moves held back").
    u128 p0 = Vu0::RotateUntied(tilt, Vu0::Q(turn.r[0]));
    Vu0::Q(self->headingMatrix.r[1]) = Vu0::RotateUntied(tilt, Vu0::Q(turn.r[1]));
    Vu0::Q(self->headingMatrix.r[2]) = Vu0::RotateUntied(tilt, Vu0::Q(turn.r[2]));
    Vu0::Q(self->headingMatrix.r[0]) = p0;
    m = self->headingMatrix;
    Vu0::Q(self->headingVelocity) = Vu0::RotateTransposed(self->headingMatrix, Vu0::Q(offset));
    rot = m;
    // The second curve's amount, computed and never used: the call below takes the first
    // one's. Retail's data has the curve (D_00275820, the same shape as D_00275800) between
    // the two scales and no code reads it; the statement leaves no instruction, but its
    // clamp's test ends the block here, which holds the call's arguments back behind the
    // stores, and its sums are scheduled among the rows' loads (docs/toolchain/sched1.md,
    // "Argument moves held back").
    f32 lean2 = g_unitRange.Limit(Quadratic(D_00275820, pad->stickMagnitude));
    BuildAxisAngleMatrix(&axis, &m, D_00275830[0] * lean);
    PlacedObject* frame = ((TintPart*)self->f748)->frame;
    rot = MultiplyByTransposedMatrix3x3(frame->m110, RotatedRows(m, frame->m110));
    ((TintBody*)self->f74C)->m40 = rot;
    ((TintBody*)self->f754)->m40 = rot;
    f32 speed = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(self->v150)));
    f32 k;
    if (0.0f < speed) {
        k = D_00275860 * g_unitRange.Clamp(Quadratic(D_00275840, speed)) / speed;
    } else {
        k = 0.0f;
    }
    f32 w = D_00275864 * g_unitRange.Clamp(Quadratic(D_00275850, pad->stickMagnitude));
    ComputePolarOffset((Vec3*)&axis, stick, 1.0f, 0.0f);
    Vec02 vel;
    Vu0::Q(vel) = Vu0::MulXSum(Vu0::Q(self->v150), Vu0::Scalar(k), Vu0::Q(axis), Vu0::Scalar(w));
    Vu0::Q(((TintBody*)self->f74C)->v20) = Vu0::RotateTransposedMembers(((TintPart*)self->f748)->frame->m110, Vu0::Q(vel));
    if (self->f73C != 0 && g_player != 0 && (pad->flags & 0x40)) {
        ClearPadPressedBits(pad, 0x40);
        SetTintBlendColliderState(self, 0);
    }
}


void SetTintBlendColliderTracked(TintBlendCollider* self, void* p)
{
    HandleSwitchedColliderActivation(self, p);
    if (p == 0) {
        self->tinted = 0;
    }
}

extern f32 g_gameClock[];
extern Rgba4 D_002623E0;

struct UnitClamp {
    static f32 Of(f32 v, f32 lo, f32 hi)
    {
        return v < lo ? lo : (hi < v ? hi : v);
    }
};

extern "C" f32 Cosine(f32 x);

void ApplyTintBlendColliderTint(TintBlendCollider* self, void* a1, void* a2)
{
    Rgba4 out;
    Rgba4 col;
    f32 t;
    if (!(self->flags & 0x100000000UL)) {
        *(u32*)&col = 0x800000A0;
        if (self->tinted != 0) {
            if (self->state != 2) {
                t = (g_gameClock[1] - self->tintFadeTime) * 0.5f;
            } else {
                t = 0.0f;
            }
            f32 r = Cosine((g_gameClock[1] - self->tintStartTime) * 10.0f);
            f32 a = D_00275870.x + t * (D_00275870.y + t * D_00275870.z);
            a = UnitClamp::Of(a, ((f32*)&g_unitRange)[0], ((f32*)&g_unitRange)[1]);
            f32 b = D_00275880[0] + r * (D_00275880[1] + r * D_00275880[2]);
            b = UnitClamp::Of(b, ((f32*)&g_unitRange)[0], ((f32*)&g_unitRange)[1]);
            f32 k = a * b;
            f32 inv = 1.0f - k;
            out.r = (s32)(inv * D_002623E0.r + k * col.r);
            out.g = (s32)(inv * D_002623E0.g + k * col.g);
            out.b = (s32)(inv * D_002623E0.b + k * col.b);
            out.a = D_002623E0.a;
        } else {
            out = D_002623E0;
        }
        SetObjectTreeRecordValue(self, *(u32*)&out);
        ApplyPlacedObjectTransform(self, (Camera*)a1, (ScaledTransform*)a2);
    }
}


// The pending impulse of a tint-blend collider: its frame vector, taken into the attached
// effect's frame and scaled by D_00275890, comes off the effect's v150; then the collider's
// own step, with the flag passed through.
void ApplyTintBlendColliderPendingImpulse(TintBlendCollider* self, s32 moved)
{
    Vec02 local;
    Vec02 k;
    u128 s = Vu0::FromFloatAt(D_00275890);
    PlacedObject* effect = (PlacedObject*)self->f748;
    Vu0::Q(local) = Vu0::RotateTransposed(((PlacedObject*)effect->parent)->m110, Vu0::Q(self->v490));
    u128 v = Vu0::Q(effect->v150);
    Vu0::Q(k) = s;
    Vu0::Q(effect->v150) = Vu0::Sub(v, Vu0::MulX(Vu0::Q(local), s));
    ApplyColliderPendingImpulse(self, moved);
}


s32 IsTintBlendColliderRequestBlocked(TintBlendCollider* self, s32 mode)
{
    if (mode == 5 || self->state == 2 || self->state == 0 || self->state == 3 || self->tinted != 0 || IsPadSelectFlagHeld(self->world) != 0) return 1;
    return 0;
}

extern f32 D_00275894;
extern f32 D_00275898;

void ContinueTintBlendColliderRequest(TintBlendCollider* self, TintBlendCollider* other)
{
    Vec02 d = self->v150;
    d.z = 0.0f;
    u128& q = Vu0::Q(d);
    Vec02 k;
    u128 n = Vu0::NormalizeOr(q, Vu0::Q(g_unitXVector));
    Vu0::Q(k) = Vu0::FromFloatAt(D_00275894);
    f32 z = D_00275898;
    q = Vu0::MulX(n, Vu0::Q(k));
    d.z = z;
    other->desc02()->m20(other, &d);
    other->heading = WrapAngle(ArctangentOfRatio(d.y, d.x) + 3.1415927f);
    TurnColliderTowardHeading(other);
    SetPlayerState((Player*)other, 4, 0x2B);
}


s32 AcceptTintBlendColliderRequest(TintBlendCollider* self, OwnerMessage* req)
{
    if (self->desc05()->m4B(self, req->mode)) {
        return 0;
    }
    if (HasSpareCount()) {
        self->tinted = 1;
    }
    self->tintStartTime = g_gameClock[1];
    ClearRootObjectStateBits(self->world, self, 7);
    if (req->mode == 0 && req->reply != 0) {
        req->reply(req->c, self);
        {
        Vec02 dir;
        Vec02 v;
        Vec02 w;
        const Vec02* fb = &g_unitXVector;
        dir = self->v150;
        dir.z = 0.0f;
        u128 len = Vu0::Length(Vu0::Q(dir));
        if (Vu0::ToFloatMoved(len) < 0.0001f) {
            dir = *fb;
        } else {
            Vu0::Set(dir, Vu0::DivX(Vu0::Q(dir), len));
        }
        if (HasSpareCount()) {
            Vu0::Set(v, Vu0::MulX(Vu0::Q(dir), Vu0::ScalarAt(D_0027589C)));
        } else {
            Vu0::Set(v, Vu0::MulX(Vu0::Q(dir), Vu0::ScalarAt(D_002758A0)));
        }
        self->desc02()->m20(self, &v);
        Vu0::Set(v, Vu0::MulX(Vu0::Q(dir), Vu0::ScalarAt(D_002758A4)));
        v.z = D_002758A8;
        TransformDirectionBetweenFrames(0, (PlacedObject*)(((PlacedObject*)self->f748)->parent), &v, &v);
        ((PlacedObject*)self->f748)->desc02()->m20((PlacedObject*)self->f748, &v);
        Vu0::Set(dir, Vu0::FromFloats(-dir.y, dir.x, 0.0f));
        Vu0::Set(w, Vu0::MulX(Vu0::Q(dir), Vu0::ScalarAt(D_002758AC)));
        TransformDirectionBetweenFrames(0, (PlacedObject*)(((PlacedObject*)self->f748)->parent), &w, &w);
        ((PlacedObject*)self->f748)->desc02()->m21((PlacedObject*)self->f748, &w);
}
    }
    OwnerMessage msg;
    if (HasSpareCount() || g_player == 0) {
        SetTintBlendColliderState(self, 2);
    } else {
        g_player->desc->m02(g_player);
        g_player->desc02()->m1F(g_player, (PlacedObject*)self->f744);
        ((BaseObject*)self->f744)->desc->m03((BaseObject*)self->f744);
        ActivateSwitchedCollider(g_player);
        SetTintBlendColliderState(self, 3);
        InitOwnerMessage(&msg, 0, self);
        msg.reply = (void (*)(void*, void*))ContinueTintBlendColliderRequest;
        g_player->desc05()->m4C(g_player, &msg);
        self->partMode = 3;
    }
    msg.mode = (s32)self;
    msg.owner = req->owner;
    self->desc->m0E(self, 0x17, &msg);
    return 1;
}


void CollectTintBlendColliderContacts(TintBlendCollider* self)
{
    ExtractContactsByPartMode(self, (Contact03**)((u8*)self + 0x740));
    CollectTurningColliderContacts(self);
}

struct TintBlendOutput { u8 pad0[0x94]; f32 contactValue; s32 f98; };

typedef s32 (*TintBlendTestFn)(void* self, void* out);

extern f32 g_gameTime;

void ComputeTintBlendColliderContactValue(TintBlendCollider* self, void* out)
{
    TintBlendCollider* obj = self;
    TintBlendOutput* o = (TintBlendOutput*)out;

    if (((TintBlendTestFn)obj->desc06()->m56)(self, out)) {
        f32 d = g_gameTime - obj->tintStartTime;
        f32 lo = ((f32*)&g_unitRange)[0];
        f32 hi = ((f32*)&g_unitRange)[1];
        f32 v = D_002758C0[0] + d * (D_002758C0[1] + d * D_002758C0[2]);
        f32 r;
        if (v < lo) {
            r = lo;
        } else if (hi < v) {
            r = hi;
        } else {
            r = v;
        }
        f32 k = D_002758B0[0];
        o->f98 = 0;
        o->contactValue = r * k;
    } else {
        o->contactValue = 0.0f;
        o->f98 = 0;
    }
}


void HandleTintBlendColliderNotification(TintBlendCollider* self, s32 code, MessageBody* rec)
{
    s32 loc[2];

    if (code != 0x13) {
        if (code == 0x14) {
            if (rec == (MessageBody*)self->walker) {
                GetStateWalkerCurrentKey((StateWalker*)rec, &loc[0]);
                GetStateWalkerTargetKey(self->walker, &loc[1]);
            }
        }
    } else {
        StateWalker* dev = self->walker;
        s32 key = rec->sourceId;
        if (dev != 0 && key == (s32)dev->player) {
            s32 kind = rec->code;
            if (kind != 0x15E) {
                if (kind == 0x15F) {
                    self->f738 = 0;
                }
            } else {
                self->f738 = 1;
            }
        }
    }
    HandleSwitchedColliderNotification(self, code, rec);
}

s32 GetTintBlendColliderRequestPhase(TintBlendCollider* self)
{
    return self->tinted != 0;
}

extern f32 g_gameClock[];




void SetTintBlendColliderState(TintBlendCollider* self, s32 mode)
{
    s32 old = self->state;
    if (mode != old) {
        switch (old) {
        case 2:
            self->tintFadeTime = g_gameClock[1];
            break;
        case 3:
            self->partMode = 0;
            self->tintFadeTime = g_gameClock[1];
            break;
        }
        switch (mode) {
        case 0:
            SetStateWalkerTarget((StateWalker*)self->walker, 0x351);
            break;
        case 1:
            SetStateWalkerTarget((StateWalker*)self->walker, 0x352);
            break;
        case 2:
            TeleportStateWalker((StateWalker*)self->walker, 0x354);
            self->tintFadeTime = 3.40282347e+38f;
            break;
        case 3:
            TeleportStateWalker((StateWalker*)self->walker, 0x355);
            self->partMode = mode;
            self->tintFadeTime = 3.40282347e+38f;
            break;
        }
        switch (mode) {
        case 0:
        case 2:
        case 3:
            self->headingVelocity = D_00248D30;
            BuildAxisAngleMatrix(&g_unitZVector, &self->headingMatrix, self->heading);

            self->f580 = 0;
            break;
        default:
            self->f580 = 1;
            break;
        }
        self->state = mode;
        self->stateTime = g_gameClock[1];
    }
}
