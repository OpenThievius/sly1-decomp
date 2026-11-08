// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 0/0, checked 2026-11-08
#include "common.h"
#include "switched_collider.h"
#include "gauge_mode_object.h"
#include "vu0.h"
#include "countdown_collider.h"
#include "globals.h"
#include "object_link.h"
#include "message_body.h"
#include "object_event.h"
#include "shapes.h"
#include "screen_element.h"
#include "placed_object.h"
#include "asm_func.h"
// NEAR (2026-11-08, worker vu0w4-e1): the frame, the calls, the two RotateTransposed sequences, the
// three weight groups and the clamps' branch layouts are retail's (tools/regdiff.py: code 94.7%, only
// the float registers and the order of a few float operations differ). Open: retail numbers the
// mode-0 clamp's registers one higher (the quotient in f1, the bounds in f4 and f0, the result in f2),
// takes max(0, c) and min(1, t) with the constant as the first operand, and
// schedules the mode-1 weights' stores and their clamps in another order. Trying named `one` and
// `zero` floats in place of the constants made it worse.
void SetBlendItemWeights(void* obj, s32 a1, s32 a2, void* a3);
void func_001B93F8(GaugeModeObject* self);
void ComputeObjectMotionInFrame(void* self, void* top, Vec02* origin, Vec02* vel, Vec02* velSum, Vec02* spin, Vec02* spinSum);
s32 ComputeObjectFrameAtTime(void* object, s32 b, Vec02* pos, Mat02* rot, Vec02* e, Vec02* f, f32 t);
void TransformPointBetweenFrames(void* from, void* to, Vec02* in, Vec02* out);
f32 ComputeAngleBetweenVectors(const Vec02* a, const Vec02* b, Vec02* out);
void* GetActiveSwitchedCollider(void);
void StopAnimationPlayer(void* player);
extern const Vec02 g_unitXVector;
extern f32 D_00263DF4;
extern f32 D_00263DF8;
extern f32 D_00263DFC;
extern f32 D_00263E00;
extern f32 D_00263AC0;

static inline f32 ClampTo(f32 v, f32 lo, f32 hi)
{
    f32 r;
    if (v < lo) {
        r = lo;
    } else if (hi < v) {
        r = hi;
    } else {
        r = v;
    }
    return r;
}

void func_0017AF38(GaugeModeObject* self)
{
    Vec02 v0;
    Vec02 local;
    Vec02 vel;
    Vec02 local2;
    Vec02 pos;
    Mat02 rot;

    func_001B93F8(self);
    if (self->mode >= 0) {
    if (self->mode < 2) {
        ComputeObjectMotionInFrame(self, 0, &self->v140, &v0, 0, 0, 0);
        Vu0::Q(local) = Vu0::RotateTransposed(self->m110, Vu0::Q(v0));
        ComputeObjectFrameAtTime(self, 0, &pos, &rot, &vel, 0, D_00263DF4);
        Vu0::Q(local2) = Vu0::RotateTransposed(rot, Vu0::Q(vel));
        if (self->mode == 0) {
            f32 c = ClampTo(local2.x / D_00263DF8, -1.0f, 1.0f);
            f32 a = c >? 0.0f;
            f32 b = -c >? 0.0f;
            f32 rest = 1.0f - a - b;
            f32 k = 1.0f - D_00263AC0;
            self->wA[3].w = D_00263AC0;
            self->wA[0].w = a * k;
            self->wA[2].w = b * k;
            self->wA[1].w = rest * k;
            SetBlendItemWeights(self->mode0Handle, 12, 4, self->wA);
        } else {
            f32 a0 = ClampTo(local2.x / D_00263DFC, 0.0f, 1.0f);
            f32 b0 = ClampTo(local2.y / D_00263E00, -1.0f, 1.0f);
            f32 s = 1.0f / (1.0f >? (__builtin_fabsf(a0) + __builtin_fabsf(b0)));
            s = s * (1.0f - D_00263AC0);
            f32 b = b0 * s;
            f32 a = a0 * s;
            self->wB[1].w = a;
            self->wB[2].w = ClampTo(b, 0.0f, 1.0f);
            self->wB[3].w = ClampTo(-b, 0.0f, 1.0f);
            self->wB[0].w = 1.0f - a - __builtin_fabsf(b);
            SetBlendItemWeights(self->mode1Handle, 12, 4, self->wB);
        }
    }
    }
    PlacedObject* p = (PlacedObject*)GetActiveSwitchedCollider();
    if (p != 0) {
        TransformPointBetweenFrames(0, self, &p->v140, &v0);
        f32 t = ComputeAngleBetweenVectors(&g_unitXVector, &v0, &local);
        t = 1.0f <? t;
        f32 y = -t * local.y;
        f32 z = t * local.z;
        f32 zp = z >? 0.0f;
        f32 yp = y >? 0.0f;
        f32 zn = -z >? 0.0f;
        f32 yn = -y >? 0.0f;
        self->wC[3].w = zp;
        self->wC[2].w = yp;
        self->wC[4].w = zn;
        self->wC[1].w = yn;
        self->wC[0].w = 1.0f - yp - yn - zp - zn;
        SetBlendItemWeights(self->loopHandle, 12, 5, self->wC);
    }
    void* target = *(void**)self->targetPlayer;
    if (target != 0) {
        if (*(f32*)((u8*)target + 0x18) == 0.0f) {
            StopAnimationPlayer(target);
            *(void**)self->targetPlayer = 0;
        }
    }
}

