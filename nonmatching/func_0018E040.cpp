// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 967/976 (99.1%), checked 2026-11-08
#include "common.h"
#include "vu0.h"
#include "list_iter.h"
#include "child_group_object.h"
#include "globals.h"
// NEAR (2026-11-08, worker night-vumid2): retail's code but for the numbering of four VU0
// registers: the weighted sum of -gravity and the rest (MulXSum with Scalar(-1.0f), the rest,
// the gravity and ScalarAt(f6F8)) comes out vf2 (the scale and the result), vf1 (the rest), vf4
// (the gravity), vf3, where retail has vf1, vf4, vf2, vf3: the same instructions, six words
// (the first qmtc2, the two lqc2, vmulax, vmaddx and the store). The order of the operands'
// declarations, mixing Vec and u128 forms and a local world pointer do not change it.
// Found: the walk's frame shares the slot of `pos` (declared in the first arm), the Hermite
// segment's outputs are declared after the weights so they share the weights' slot, the dead
// store of the normalised velocity is a local `dir`, the callee takes the float before the flag.

extern u8 g_gameClock[];
f32 D_002699BC = 0.5f;

// Class 0x3D, a contact-list object without gravity that keeps a velocity of its own.
struct ContactListGlider : ContactListObject {
    f32 speed6F0;           // 0x6F0: the speed of the velocity it keeps (func_0018DDD8)
    f32 rate6F4;            // 0x6F4: how fast it turns to that velocity (func_0018DE70)
    f32 f6F8;               // 0x6F8
    f32 time6FC;
    Vec02 v700;             // 0x700: the velocity it keeps
};

typedef char check_ContactListGlider[sizeof(ContactListGlider) == 0x710 ? 1 : -1];

void InitContactListObject(ContactListObject* self);
struct GliderListFrame {
    void* base;
    void* cur;
    s32 off;
    GliderListFrame* prev;
    GliderListFrame(List01* l)
    {
        cur = l;
        base = l;
        GliderListFrame* p = (GliderListFrame*)g_activeListFrames;
        off = l->offset;
        g_activeListFrames = (ListFrame*)this;
        prev = p;
    }
    ~GliderListFrame() { g_activeListFrames = (ListFrame*)prev; }
};

void ComputeObjectFrameAtTime(void* obj, s32 a, Vec02* pos, Mat02* rot, s32 b, s32 c, f32 t);
void EvaluateHermiteVectorSegment(f32 t, f32 u, f32 v, void* a, void* b, void* c, void* d, Vec02* outPos, Vec02* outVel, Vec02* tangent);
f32 SplitVectorAlongAxis(Vec02* v, Vec02* axis, Vec02* along, Vec02* rest);
void BuildBasisFromXAndZHint(Vec02* x, Vec02* hint, Mat02* out);

void func_0018E040(ContactListGlider* self, s32 hold, f32 dt)
{
    Vec02 accel;
    f32 now = *(f32*)(g_gameClock + 4);
    if (now < self->time6FC) {
        Vec02 pos;
        Vec02 vel;
        Mat02 rot;
        f32 remain = self->time6FC - now + dt;
        ComputeObjectFrameAtTime(self->f694, 0, &pos, &rot, 0, 0, D_002699BC <? remain);
        Vu0::Q(pos) = Vu0::Add(Vu0::Rotate(rot, Vu0::Q(self->v6A0)), Vu0::Q(pos));
        s32 still = 0;
        if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(self->v700))) < 0.0001f
            && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(self->v700))) < 0.0001f
            && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(self->v700))) < 0.0001f) {
            still = 1;
        }
        if (still) {
            Vu0::Q(vel) = Vu0::MulXSum(Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->pos)), Vu0::Scalar(1.5f / remain), Vu0::Q(self->v150), Vu0::Scalar(-0.5f));
        } else {
            vel = self->v700;
        }
        Vec02 outPos;
        Vec02 outVel;
        EvaluateHermiteVectorSegment(remain, dt, 1.0f, &self->pos, &self->v150, &pos, &vel, &outPos, &outVel, &accel);
        self->pos = outPos;
        self->v150 = outVel;
    } else {
        accel = D_00248D30;
        Vu0::Q(self->pos) = Vu0::MulAddX(Vu0::Q(self->pos), Vu0::Q(self->v150), Vu0::Scalar(dt));
    }
    if (self->ready != 0) {
        s32 still = 0;
        if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(self->v150))) < 0.0001f
            && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(self->v150))) < 0.0001f
            && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(self->v150))) < 0.0001f) {
            still = 1;
        }
        if (!still) {
            Vec02 dir;
            Vec02 rest;
            Vu0::Set(dir, Vu0::NormalizeOrMoved(Vu0::Q(self->v150), Vu0::Q(g_unitXVector)));
            SplitVectorAlongAxis(&accel, &self->rot.r[0], 0, &rest);
            u128 s = Vu0::Scalar(-1.0f);
            u128 b = Vu0::Q(rest);
            u128 a = Vu0::Q(g_currentWorld->gravity);
            u128 t = Vu0::ScalarAt(self->f6F8);
            Vu0::Q(rest) = Vu0::MulXSum(a, s, b, t);
            BuildBasisFromXAndZHint(&self->v150, &rest, &self->rot);
        }
    }
    GliderListFrame f(&self->children);
    void* n;
    void* t = *(void**)f.base;
    f.cur = (u8*)t + f.off;
    n = t;
    if (n != 0) {
        do {
            if (((PlacedObject*)n)->desc->flags & 1) {
                ((void (*)(void*, f32, s32))((PlacedObject*)n)->desc->m1B)(n, dt, 1);
            }
            void* c = f.cur;
            s32 o = f.off;
            void* a = *(void**)c;
            f.cur = (u8*)a + o;
            n = a;
        } while (n != 0);
    }
    if (hold == 0) {
        if (self->desc->m12 != 0) {
            self->desc->m12(self);
        }
    }
}
