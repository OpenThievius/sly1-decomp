// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1192/1588 (75.1%), checked 2026-11-10
#include "common.h"
#include "vu0.h"
#include "collider.h"
#include "effect.h"
#include "globals.h"
// NEAR (2026-11-10, w16): the size, the frame, the slots, the saved registers (bounce in f22,
// -friction in f21) and the order of the blocks are retail's; 348 of 397 instructions equal
// (regdiff), the rest are schedules and VU registers. Three changes got here: the mesh's end computed before `best` is
// set (the frame store of best then makes CSE reload the vertex pointer, retail's second
// lw 904); the first impulse's direction its own variable, `d1 = nv`, used by c1, the first
// impulse and the final sum (gcse.c's cprop, two passes, leaves that sum reading the copy of the
// normal that lives in 80(sp), as retail does, docs/toolchain/gcse.md); and both impulses
// through one inline, ImpulseAlong, which also makes the two conversions alike (the earlier
// ToFloatMoved at the second is gone). Still differs: (1) the second impulse's direction reads
// that 80(sp) copy too (lqc2 from 80(sp)) and copies the friction weight (vmove vf6,vf5), where
// retail copies the normal in the block before the NormalizeOr branch (vmove vf6,vf8): retail's
// MulAddX parameter copy survives cprop, ours is resolved to the spilled pseudo; (2) the
// scheduling after ComputeObjectMotionInFrame: retail loads the spin (+0x100) and issues
// Cross(spin, p) before Cross(c1, p), ours the reverse, and the registers that follow;
// (3) best's lq first in its block (retail after the RotateTransposed), Rotate(rot50, best)
// giving best p's register (vf10) where retail loads it into vf3; (4) the two sums at the end in
// a different order, and the ShortenEffectLife call's caller-save store before the arguments
// (retail's in the delay slot, with a reload of vf8 in the bc1f delay slot). The FLT_MAX literal
// is the function's own (INCLUDE_RODATA(D_0024C9B0) goes with it). Tried: NormalizeOr named
// before the direction (2 short), d1 in the direction too, a Vec02 copy of the normal (GPR
// copy), Of(*normal) in the sum (keeps a3 in s7), ToFloatMoved at either Dot of the inline.

extern f32 g_gameTime;
extern f32 D_0026B540;
extern f32 D_0026B544;
extern f32 D_0026B548;
extern f32 D_0026B54C;
extern f32 D_0026B550[4];
struct QuadraticCoeffs { f32 a, b, c; };
struct ClampedQuadratic {
    static f32 Eval(const QuadraticCoeffs* p, f32 t)
    {
        return p->a + t * (p->b + t * p->c);
    }
};
void ShortenEffectLife(Effect* self, f32 x);
void func_001EED68(void* self, Vec02* in, Vec02* outA, Vec02* outB);
// The larger of two floats (max.s; through an inline function, b >? a reads a first and gives
// the result b's register, as retail's pose counts are).
static inline f32 MaxF(f32 a, f32 b) { return b >? a; }
void ComputeObjectMotionInFrame(void* obj, s32 b, Vec02* pos, Vec02* vel, s32 e, s32 f, s32 g);
void MeasurePointToSegment(const Vec02* p, Vec02* a, Vec02* b, f32* o1, f32* o2);
void SpawnBriefEffectAt(Vec02* at, PlacedObject* other, f32 scale);

// One impulse of the contact along d: the weight of the turn it gives (cp, the lever arm's cross
// product, scaled by w) and the bounce decide its size j; tang is what is left of the impulse off
// the normal.
static inline f32 ImpulseAlong(Vu0::Vec d, Vu0::Vec c, Vu0::Vec p, f32 w, Vu0::Vec rel, Vu0::Vec n, f32 bounce, Vu0::Vec& tang)
{
    Vu0::Vec wv = Vu0::MulAddX(d, Vu0::Cross(c, p), Vu0::Vec::Scalar(w));
    f32 j = Vu0::ToFloat(Vu0::Dot(rel, n)) * (-1.0f - bounce) / Vu0::ToFloat(Vu0::Dot(wv, n));
    Vu0::Vec imp = Vu0::MulAddX(rel, wv, Vu0::Vec::Scalar(j));
    tang = Vu0::Sub(imp, Vu0::MulX(n, Vu0::Dot(imp, n)));
    return j;
}

// An effect that hits something (slot 7, the shared contact): against a moving object (class
// flag 0x80) it takes on half the object's motion there; otherwise it bounces as a spinning ball
// of its radius, with a bounce and a friction (kind 24's own, 0.7 and 0.8 for the rest), off the
// object's nearest vertex along the normal when the object is a collider, and is pushed out.
s32 HandleEffectContact(Effect* self, void* b, void* c, void* d)
{
    PlacedObject* other = (PlacedObject*)b;
    Vec02* at = (Vec02*)c;
    Vec02* normal = (Vec02*)d;
    f32 radius;
    f32 bounce;
    f32 friction;
    if (self->kind == 24) {
        radius = self->f120;
        bounce = self->f124;
        friction = self->f128;
    } else {
        bounce = 0.7f;
        radius = ((PlacedObject*)self->p20)->f2A8;
        friction = 0.8f;
    }
    f32 t = (g_gameTime - self->start) / self->life;
    radius *= ClampedQuadratic::Eval((const QuadraticCoeffs*)&self->q30, t);
    if (other->desc->flags & 0x80) {
        Vec02 target;
        func_001EED68(other, at, &target, 0);
        Vu0::Vec vel = Vu0::MulAddX(Vu0::Vec::Of(self->qA0), Vu0::Sub(Vu0::Vec::Of(target), Vu0::Vec::Of(self->qA0)), Vu0::Vec::ScalarAt(D_0026B544));
        f32 time = D_0026B540;
        Vu0::Q(self->qC0) = Vu0::DivX(Vu0::Sub(Vu0::Vec::Of(target), vel), Vu0::Vec::Scalar(time)).q;
        Vu0::Q(self->qA0) = vel.q;
        ShortenEffectLife(self, time);
        SpawnBriefEffectAt(at, other, radius * D_0026B548);
        return 1;
    }
    Collider* o = (Collider*)self->p20;
    Vu0::Vec nv = Vu0::Vec::Of(*normal);
    Vu0::Vec p;
    if (o->desc->flags & 2) {
        Vec02 v;
        Vu0::Q(v) = Vu0::RotateTransposed(self->rot50, nv).q;
        Vec02 cur;
        Vec02* end = (Vec02*)o->mesh.verts + o->mesh.vertCount;
        Vec02 best = D_00248D30;
        f32 bestD = 3.4028235e+38f;
        for (Vec02* q = (Vec02*)o->mesh.verts; q < end; q++) {
            Vu0::Q(cur) = Vu0::Q(*q);
            f32 d = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(v), Vu0::Vec::Of(cur)));
            if (d < bestD) {
                Vu0::Q(best) = Vu0::Q(cur);
                bestD = d;
            }
        }
        p = Vu0::Rotate(self->rot50, Vu0::Vec::Of(best));
    } else {
        p = Vu0::MulX(nv, Vu0::Vec::Scalar(-radius));
    }
    Vu0::Vec d1 = nv;
    Vu0::Vec c1 = Vu0::Cross(p, d1);
    Vec02 vAt;
    ComputeObjectMotionInFrame(other, 0, at, &vAt, 0, 0, 0);
    radius = MaxF(radius, 10.0f);
    Vu0::Vec turn = Vu0::Cross(Vu0::Vec::Of(self->v100), p);
    Vu0::Vec rel = Vu0::Sub(Vu0::Add(Vu0::Vec::Of(self->qA0), turn), Vu0::Vec::Of(vAt));
    Vu0::Vec tang1;
    f32 j1 = ImpulseAlong(d1, c1, p, 2.5f / (radius * radius), rel, nv, bounce, tang1);
    Vu0::Vec mu = Vu0::Vec::Scalar(-friction);
    Vu0::Vec dir = Vu0::MulAddX(nv, Vu0::NormalizeOr(tang1, Vu0::Vec::Of(g_unitXVector)), mu);
    Vu0::Vec c2 = Vu0::Cross(p, dir);
    f32 k = 2.5f / (radius * radius);
    Vu0::Vec tang2;
    f32 j2 = ImpulseAlong(dir, c2, p, k, rel, nv, bounce, tang2);
    Vec02 t1;
    Vec02 t2;
    Vu0::Set(t1, tang1.q);
    Vu0::Set(t2, tang2.q);
    f32 along;
    f32 off;
    MeasurePointToSegment(&D_00248D30, &t1, &t2, &along, &off);
    f32 one = 1.0f;
    Vu0::Vec s = Vu0::Vec::Scalar((one - along) * j1);
    Vu0::Vec s2 = Vu0::Vec::Scalar(along * j2);
    Vu0::Q(self->qA0) = Vu0::Add(Vu0::Vec::Of(self->qA0), Vu0::MulXSum(d1, s, dir, s2)).q;
    Vu0::Q(self->v100) = Vu0::MulAddX(Vu0::Vec::Of(self->v100), Vu0::MulXSum(c1, s, c2, s2), Vu0::Vec::Scalar(k)).q;
    if (((f32*)&self->qA0)[2] < D_0026B54C) {
        ((f32*)&self->qA0)[2] = D_0026B54C;
        ShortenEffectLife(self, D_0026B550[0]);
    }
    f32 depth = MaxF(0.0f, Vu0::ToFloat(Vu0::Dot(Vu0::Sub(Vu0::Vec::Of(*at), Vu0::Vec::Of(self->q80)), nv))) + one;
    Vu0::Q(self->q80) = Vu0::MulAddX(Vu0::Vec::Of(self->q80), nv, Vu0::Vec::Scalar(depth)).q;
    return 1;
}
