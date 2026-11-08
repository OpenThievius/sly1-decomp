// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 1688/1700, checked 2026-11-08
// NEAR (2026-11-08, night-large3): ControlTintBlendCollider. Logic, calls, clamps (Clamp in
// place for three of the quadratics, Limit for the lean) and the branch shapes follow retail;
// what differs is the frame (0x1F0 against 0x200) and where the matrix temporaries live: retail
// has the second product's rows at 0x110 and 0x140 and MultiplyByTransposedMatrix3x3's result
// at 0xE0 (later the velocity and its two Scalars), ours puts the out-parameter product at 0xE0
// and the result in a block local; retail also keeps a fifth saved register (s5, the unit range's
// address) and the self/pad pair in s0/s2. Tried: the product as an inline returning Mat02 (three
// copies where retail has two), a named result (a temporary after the locals).
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

extern f32 g_frameDt;
extern f32 D_002757F0[4];
extern Vec02 D_002757E0;
extern f32 D_00275800[4];
extern f32 D_00275810[8];
extern f32 D_00275830[4];
extern f32 D_00275840[4];
extern f32 D_00275850[4];
extern f32 D_00275860;
extern f32 D_00275864;
s32 HasAnimationDrivenAttachment(TintBlendCollider* self);
void GetStateWalkerCurrentKey(void* p, s32* out);
void GetStateWalkerTargetKey(void* p, s32* out);
void TeleportStateWalker(void* p, s32 n);
void SetStateWalkerTarget(void* p, s32 n);
void HandleStepSequenceSkipButtons(void* self, PadRecord* rec);
s32 IsTopCameraController(void* p);
void ComputeCameraRelativeStickHeading(Camera* self, PadRecord* p, s32 mode, f32* out);
f32 ArctangentOfRatio(f32 y, f32 x);
f32 WrapAngle(f32 a);
void ComputePolarOffset(void* out, f32 x, f32 y, f32 z);
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);
Mat02 MultiplyByTransposedMatrix3x3(const Mat02& a, const Mat02& b);
void ClearPadPressedBits(PadRecord* self, s32 mask);
void SetTintBlendColliderState(void* self, s32 flag);
extern s32 g_movieChecksumFailed;

struct TintPart_1DEBE8 { u8 pad00[0x18]; PlacedObject* frame; };
struct TintBody_1DEBE8 { u8 pad00[0x20]; Vec02 v20; u8 pad30[0x40 - 0x30]; Mat02 m40; };
typedef void (*TintSelfFn_1DEBE8)(void* self);

static inline f32 Quadratic(const f32* poly, f32 z)
{
    return poly[0] + z * (poly[1] + z * poly[2]);
}

// The rows of m, each turned by r.
static inline void RotateRowsBy(Mat02* out, const Mat02& r, const Mat02& m)
{
    Vu0::Q(out->r[0]) = Vu0::RotateUntied(r, Vu0::Q(m.r[0]));
    Vu0::Q(out->r[1]) = Vu0::RotateUntied(r, Vu0::Q(m.r[1]));
    Vu0::Q(out->r[2]) = Vu0::RotateUntied(r, Vu0::Q(m.r[2]));
}

void ControlTintBlendCollider(TintBlendCollider* self, PadRecord* pad)
{
    Vec02 offset;
    Vec02 axis;
    Mat02 tilt;
    Mat02 turn;
    Mat02 m;
    Mat02 rot;
    Mat02 p;
    Mat02 q;
    s32 cur;
    s32 tgt;
    f32 stick;
    if (HasAnimationDrivenAttachment(self) != 0) {
        return;
    }
    GetStateWalkerCurrentKey(self->f75C, &cur);
    GetStateWalkerTargetKey(self->f75C, &tgt);
    if (self->f720 == 2) {
        if (cur == 0x352) {
            ((TintSelfFn_1DEBE8*)self->desc)[84](self);
        } else if (self->f738 != 0 && 0.7f < pad->f7C) {
            ((TintSelfFn_1DEBE8*)self->desc)[84](self);
            TeleportStateWalker(self->f75C, 0x352);
            GetStateWalkerCurrentKey(self->f75C, &cur);
            GetStateWalkerTargetKey(self->f75C, &tgt);
        }
    }
    if ((u32)(cur - 0x352) >= 2) {
        return;
    }
    if (tgt != -1 && tgt != 0x352 && tgt != 0x353) {
        return;
    }
    HandleStepSequenceSkipButtons(self, pad);
    if (IsTopCameraController(&g_camera->ctl454) == 0 && 0.7f < pad->f7C) {
        ComputeCameraRelativeStickHeading(g_camera, pad, 1, &self->f638);
        if (__builtin_fabsf(WrapAngle(self->f638 - ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x))) < 0.5f && g_movieChecksumFailed == 0) {
            SetStateWalkerTarget(self->f75C, 0x353);
        }
    } else {
        SetStateWalkerTarget(self->f75C, 0x352);
    }
    ComputeCameraRelativeStickHeading(g_camera, pad, 0, &stick);
    f32 reach = ((ValueRange*)D_002757F0)->Clamp(Quadratic(&D_002757E0.x, pad->f48));
    ComputePolarOffset(&offset, stick + 3.14159274f, reach, 0.0f);
    ComputePolarOffset(&axis, stick, 1.0f, 0.0f);
    Vu0::Q(axis) = Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(axis));
    f32 lean = g_unitRange.Limit(Quadratic(D_00275800, pad->f48));
    BuildAxisAngleMatrix(&axis, &tilt, D_00275810[0] * lean);
    BuildAxisAngleMatrix(&g_unitZVector, &turn, self->f638);
    RotateRowsBy(&m, tilt, turn);
    self->m660 = m;
    Vu0::Q(self->v640) = Vu0::RotateTransposed(self->m660, Vu0::Q(offset));
    rot = m;
    BuildAxisAngleMatrix(&axis, &m, D_00275830[0] * lean);
    PlacedObject* frame = ((TintPart_1DEBE8*)self->f748)->frame;
    RotateRowsBy(&q, m, frame->m110);
    p = q;
    {
        Mat02 r = MultiplyByTransposedMatrix3x3(frame->m110, p);
        rot = r;
    }
    ((TintBody_1DEBE8*)self->f74C)->m40 = rot;
    ((TintBody_1DEBE8*)self->f754)->m40 = rot;
    f32 speed = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(self->v150)));
    f32 k;
    if (0.0f < speed) {
        k = D_00275860 * g_unitRange.Clamp(Quadratic(D_00275840, speed)) / speed;
    } else {
        k = 0.0f;
    }
    f32 w = D_00275864 * g_unitRange.Clamp(Quadratic(D_00275850, pad->f48));
    ComputePolarOffset(&axis, stick, 1.0f, 0.0f);
    Vec02 vel;
    Vu0::Q(vel) = Vu0::MulXSum(Vu0::Q(self->v150), Vu0::Scalar(k), Vu0::Q(axis), Vu0::Scalar(w));
    Vu0::Q(((TintBody_1DEBE8*)self->f74C)->v20) = Vu0::RotateTransposed(((TintPart_1DEBE8*)self->f748)->frame->m110, Vu0::Q(vel));
    if (self->f73C != 0 && g_player != 0 && (pad->flags & 0x40)) {
        ClearPadPressedBits(pad, 0x40);
        SetTintBlendColliderState(self, 0);
    }
}
