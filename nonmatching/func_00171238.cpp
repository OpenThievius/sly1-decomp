// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1177/1968 (59.8%), checked 2026-11-08
// CONV-SWAP (2026-11-08): ToFloat and ToFloatMoved swapped at call 0 (source line 148); 424 differing lines before, 255 now.
// NEAR: the pose of the five parts, the path sample, the turn weights and the push are retail's blocks; left: retail keeps the speed (the dot as a vector) in s0 across the curve's calls where this spills it, forms the direction's address again for each call (here kept in s0), and lays the mode test's else branch out with its own load of the part.
#include "common.h"
#include "globals.h"
#include "switched_collider.h"
#include "node_query.h"
#include "gauge_mode_object.h"
#include "countdown_collider.h"
#include "entry_queue.h"
#include "object_link.h"
#include "message_body.h"
#include "object_event.h"
#include "shapes.h"
#include "screen_element.h"
#include "base_object.h"
#include "placed_object.h"
#include "world.h"
#include "font.h"
#include "level_entry.h"
#include "threshold_range.h"
#include "scatter_controller.h"
#include "render_frame.h"
#include "background_job.h"
#include "vu0.h"
#include "path_curve.h"
#include "group_marker.h"
#include "game_progress.h"
#include "bump_allocator.h"
#include "camera.h"
#include "path_curve_object.h"
#include "asm_func.h"
#include "owner_message.h"
#include "vu0.h"
#include "ramp_profile.h"
#include "animation.h"
#include "anim_curve.h"

void TransformPointBetweenFrames(void* a, s32 b, void* c, void* d);
extern f32 D_00263800[4];
extern f32 D_00263810[4];
extern f32 D_00263820[4];
extern f32 D_00263830[4];
extern f32 D_00263840[4];
extern f32 D_00263850;
extern f32 D_00263854;
extern f32 D_00263858[6];
extern f32 D_00263870[4];
extern f32 D_002637D8;
extern f32 D_002637DC;
extern f32 D_002637E0;
extern f32 D_002637E4;
extern f32 D_002637E8[2];
extern f32 D_002637F0[4];
extern f32 g_unitRange[];
extern f32 g_frameDt[];

// A part of the player's model as func_00171238 poses it: two state bytes, its offset and its
// rotation (BuildEulerRotationMatrix).
struct PosedPart { u8 pad00[0x10]; s8 state; s8 next; u8 pad12[0x20 - 0x12]; Vec02 offset; Vec02 angles; };
struct PathRecord { u8 pad00[0x18]; PlacedObject* frame; u8 pad1C[0x34 - 0x1C]; PathCurve* curve; u8 pad38[0x40 - 0x38]; s32 f40; };

// x + t (y + t z) of a curve's three coefficients.
static inline f32 EvalCurve3(const f32* c, f32 t) { return c[0] + t * (c[1] + t * c[2]); }

void BuildEulerRotationMatrix(void* angles, void* out);
f32 ArctangentOfRatio(f32 y, f32 x);
void BuildAxisAngleMatrix(f32 angle, const Vec02* axis, Mat02* out);
void ConvertPositionToWorld(void* rec, Vec02* out);
void TransformDirectionBetweenFrames(void* a, s32 b, void* c, void* d);
f32 WrapModulo(f32 x, f32 m);
f32 SplitVectorAlongAxis(const Vec02* v, const Vec02* axis, Vec02* along, Vec02* rest);
f32 ApproachValueClampingVelocity(f32 x, f32 v, f32 target, f32 dt, void* params, f32* outv);
void SetBlendItemWeights(void* blend, s32 stride, s32 count, f32* w);
void ComputeObjectMotionInFrame(void* obj, s32 z, void* point, Vec02* out, s32 a, s32 b, s32 c);
void TransformPointAtTime(void* obj, s32 a, Vec02* p, s32 b, Vec02* out, s32 c, f32 t);
extern f32 g_frameDt[];

void func_00171238(Player* self)
{
    s32 mode = -1;
    if (self->f2220 == 6 && self->f239C == 4 && self->f2228 == 0x10 && (u32)(self->f223C - 4) < 2) {
        void* angles;
        mode = 2;
        if (((PathRecord*)self->f23BC)->f40 != 0) {
            Vu0::Q(((PosedPart*)self->f2518)->offset) = Vu0::Q(*(Vec02*)D_00263820);
            angles = D_00263830;
        } else {
            Vec02 d;
            Mat02 m;
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(((PosedPart*)self->f250C)->offset), Vu0::Q(((PosedPart*)self->f2510)->offset));
            BuildAxisAngleMatrix(D_00263850 * ArctangentOfRatio(d.z, D_00263854), &g_unitYVector, &m);
            Vu0::Q(((PosedPart*)self->f2518)->offset) = Vu0::Add(Vu0::Q(*(Vec02*)D_00263840), Vu0::Rotate(m, Vu0::Sub(Vu0::Q(*(Vec02*)D_00263800), Vu0::Q(*(Vec02*)D_00263840))));
            angles = D_00263810;
        }
        BuildEulerRotationMatrix(angles, &((PosedPart*)self->f2518)->angles);
    }
    PosedPart* part = (PosedPart*)self->f2518;
    part->next = mode;
    if (part->state != mode) {
        s32 n = ((PosedPart*)self->f2518)->next;
        part->state = n;
        ((const Desc02*)self->f24F8->desc)->m2B(self->f24F8);
    }
    Vec02 rest;
    Vec02 pos;
    Vec02 vel;
    Vec02 along;
    Vec02 side;
    Vec02 k;
    Vec02 push;
    Vu0::Q(rest) = Vu0::Q(D_00248D30);
    PlacedObject* frame = 0;
    Vec02* at = 0;
    PosedPart* lead = (PosedPart*)self->f2500;
    if (lead == 0 || lead->state == -1)
        return;
    switch (self->f2220) {
    case 0:
        if (self->f690 != 0) {
            frame = (PlacedObject*)self->f6C0;
            at = &self->v6A0;
        }
        break;
    case 6:
        if (self->f2228 == 0x10) {
            switch (self->f239C) {
            case 5: {
            PathRecord* rec = (PathRecord*)self->f23B8;
                at = &pos;
                frame = rec->frame;
                ConvertPositionToWorld(rec, &pos);
                break;
            }
            case 4: {
            PathRecord* rec = (PathRecord*)self->f23BC;
                PathCurve* c = rec->curve;
                frame = rec->frame;
                if (c->vt->m01 != 0)
                    ((void (*)(PathCurve*, f32, Vec02*, Vec02*))c->vt->m01)(c, self->f23C0, &pos, &vel);
                TransformPointBetweenFrames(frame, 0, &pos, &pos);
                at = &pos;
                if (((PathRecord*)self->f23BC)->f40 != 0) {
                    Vu0::Q(vel) = Vu0::DivX(Vu0::Q(vel), Vu0::Length(Vu0::Q(vel)));
                    u128 speed = Vu0::Dot(Vu0::Q(self->v150), Vu0::Q(vel));
                    Vu0::Q(k) = speed;
                    Vu0::Q(along) = Vu0::MulX(Vu0::Q(vel), Vu0::Q(k));
                    f32 t = self->f23C4 + Vu0::ToFloat(speed) * D_002637D8;
                    f32 len = c->vt->m08(c);
                    if (c->wrap != 0) {
                        t = WrapModulo(t, len);
                    } else {
                        f32 lo = *c->lengths;
                        if (t < lo)
                            t = lo;
                        else if (len < t)
                            t = len;
                    }
                    if (c->vt->m02 != 0)
                        ((void (*)(PathCurve*, f32, s32, Vec02*))c->vt->m02)(c, t, 0, &vel);
                    TransformDirectionBetweenFrames(frame, 0, &vel, &vel);
                    Vu0::Q(k) = speed;
                    Vu0::Q(side) = Vu0::MulX(Vu0::DivX(Vu0::Q(vel), Vu0::Length(Vu0::Q(vel))), Vu0::Q(k));
                    Vu0::Q(rest) = Vu0::Sub(Vu0::Q(side), Vu0::Q(along));
                    if (self->f1090 != 0) {
                        u128 n = Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(vel));
                        Vu0::Q(k) = Vu0::DivX(n, Vu0::Length(n));
                        f32 f = SplitVectorAlongAxis(&rest, &k, 0, &rest) / D_002637DC;
                        f32 turn;
                        if (f < -1.0f)
                            turn = -1.0f;
                        else if (1.0f < f)
                            turn = 1.0f;
                        else
                            turn = f;
                        if (self->f23C8 != 0)
                            turn = -turn;
                        f32 r = ApproachValueClampingVelocity(self->f1094, self->f1098, turn * (2.0f - __builtin_fabsf(turn)), g_frameDt[0], D_00263858, &self->f1098);
                        self->f1094 = r;
                        f32 a = r >? 0.0f;
                        f32 b = -r >? 0.0f;
                        self->f106C = a;
                        self->f1084 = b;
                        self->f1078 = 1.0f - a - b;
                        SetBlendItemWeights(self->f1090, 0xC, 3, &self->f106C);
                        goto motion;
                    }
                }
                break;
            }
            }
        }
        break;
    }
    if (frame == 0)
        return;
motion:
    ComputeObjectMotionInFrame(frame, 0, at, &vel, 0, 0, 0);
    TransformPointBetweenFrames(0, (s32)frame, at, &along);
    Vu0::Q(side) = Vu0::Zero();
    TransformPointAtTime(frame, 0, &along, 0, &side, 0, D_002637D8);
    Vu0::Q(k) = Vu0::DivX(Vu0::Sub(Vu0::Add(Vu0::Q(rest), Vu0::Q(side)), Vu0::Q(vel)), Vu0::ScalarAt(D_002637D8));
    f32 dist = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(k), Vu0::Q(k))));
    if (0.0001f < dist) {
        f32 g = EvalCurve3(D_002637F0, 1.0f <? dist / D_002637DC);
        f32 lo = g_unitRange[0];
        f32 hi = g_unitRange[1];
        if (g < lo)
            g = lo;
        else if (hi < g)
            g = hi;
        Vu0::Q(k) = Vu0::RotateTransposed(self->m660, Vu0::Q(k));
        Vu0::Q(push) = Vu0::FromFloats(k.x * D_002637E0 * g / dist, k.y * D_002637E0 * g / dist, D_002637E4 * g);
    } else {
        Vu0::Q(push) = Vu0::Q(D_00248D30);
    }
    Vu0::Q(((PosedPart*)self->f2500)->offset) = Vu0::Q(push);
    f32 e1 = EvalCurve3(D_00263870, ((PosedPart*)self->f250C)->offset.z);
    f32 e2 = EvalCurve3(D_00263870, ((PosedPart*)self->f2510)->offset.z);
    f32 z;
    if (push.z < e1)
        z = e2 <? push.z;
    else
        z = e2 <? e1;
    ((PosedPart*)self->f2500)->offset.z = z;
    if (self->f223C == -1) {
        u128 s = Vu0::MulX(Vu0::Q(push), Vu0::ScalarAt(D_002637E8[0]));
        Vu0::Q(((PosedPart*)self->f2504)->offset) = s;
        Vu0::Q(((PosedPart*)self->f2508)->offset) = s;
    } else {
        Vu0::Q(((PosedPart*)self->f2504)->offset) = Vu0::Q(D_00248D30);
        Vu0::Q(((PosedPart*)self->f2508)->offset) = Vu0::Q(((PosedPart*)self->f2504)->offset);
    }
}
