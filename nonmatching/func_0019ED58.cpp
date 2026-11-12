// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 1584/1588, checked 2026-11-12
#include "common.h"
#include "vu0.h"
#include "collider.h"
#include "effect.h"
#include "globals.h"
// NEAR (2026-11-10, w17): 364 of 397 instructions equal (regdiff), one instruction short of
// retail's 1588 bytes (b 0x19f34c for 0x19f350). Wave 17 fixed, in order: the 0x80 branch's
// stores (the velocity stored before qC0 is computed from it, so sched2 leaves the qA0 store for
// the delay slot as retail does); best's start as Q(best) = Q(D_00248D30) (a u128 copy with no
// alias class waits for v's frame store, so retail's lq comes after the addiu s3..s5; the FLT_MAX
// load then lines up too); RotateUntied (retail's vmaddz writes vf10 from best in vf3, not tied);
// the friction weight as `mu.q = Vu0::Scalar(..)` (Vec::Scalar's extra copy made a third
// copy-propagation hop that gcse.c's two cprop passes never reach, the vmove vf6,vf5); and the
// second direction as `dir = nv; dir = MulAddX(dir, NormalizeOr(..), mu)`, like d1 = nv for the
// first: the copy of the normal now survives cprop (retail's vmove vf6,vf8 before the branch),
// and with it the order after ComputeObjectMotionInFrame (Cross(spin, p) before Cross(c1, p),
// retail's registers vf3/vf2/vf4/vf1) is retail's. The spin's update is written before the
// velocity's: both sums tie in sched1 (priority 10, the same register weight), and the later
// statement's goes first, so this gives retail's order of the two sums (365/397). Still differs: c2 = Cross(p, dir) is kept in
// vf6 across MeasurePointToSegment (stored at 128(sp)), where retail spills it (sqc2 vf1,112(sp)
// at once and lqc2 vf1,112(sp) before Cross(c2, p): the missing instruction) and keeps dir in
// vf5 at 128(sp); c2 is local to its block with 3 refs and 1 call, so local-alloc's caller-save
// test should refuse it, yet it gets vf6. The reason, from the .lreg dump: c2 dies at the
// spin's MulXSum and combine_regs ties that sum's result to c2's quantity, adding its refs, so
// 4*calls < refs holds and c2 is caller-saved. Retail ties that result to s (vf1) and reloads c2
// from 112(sp): there c2 has no quantity to tie into, i.e. it is a global pseudo (used in another
// block, or set twice), which global-alloc spills with 3 refs. Not found: c2 without a local
// (Cross(p, dir) at both uses), declared at the block's top (with c1 or alone), returned by an
// inline with the impulse (ImpulseAlongArm), s and s2 as `.q = Scalar(..)`, or the sums named
// before the stores: all keep c2 in vf6. Then the
// globals: p vf11 / rel vf10 / tang1 vf9 against retail's vf10 / vf9 / vf7 (one register lower,
// likely from c2's and k's locals), and the ShortenEffectLife store order at the end. The FLT_MAX
// literal is the function's own (INCLUDE_RODATA(D_0024C9B0) goes with it). At retail's size,
// 355/397: the first three changes only (build/swarm/w17-19ED58b/b4.cpp in the g4 worktree). Tried: Scalar(-friction) inline in the call (a float saved register more),
// `Vu0::Vec n = nv;` (same as dir = nv), d1/nv at each of four uses (16 ways), statement order
// after the call and in ImpulseAlong (no change), its Vec parameters by const reference (no
// change), c2 as a Vec02 local (worse).
// w32 (2026-11-11): the first differing block is the second impulse: retail's sqc2 vf1,112(sp) /
// lqc2 vf1,112(sp) around Cross(c2, p) (c2 a spilled pseudo, reloaded again before the spin's
// MulXSum), and dir caller-saved at 128(sp); ours keeps c2 in vf6 (caller-saved at 128) and dir at
// 112. The later register shifts (p, rel, tang1 one higher) follow. For c2 to be spilled it must
// be a non-local pseudo (REG_BASIC_BLOCK global, or REG_N_DEATHS != 1) with REG_N_REFS <= 4 per
// call crossed, and retail's spin sum (vmaddx vf1, vf5, vf2x) ties to neither c2 nor s2, so s2
// was not a local quantity dying there either. Tried: c2 as a reuse of `turn` (one pseudo over two
// blocks): it becomes global but gets a register (more refs), 348/397.
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
void GetAttachedSetPointMotion(void* self, Vec02* in, Vec02* outA, Vec02* outB);
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
        GetAttachedSetPointMotion(other, at, &target, 0);
        Vu0::Vec vel = Vu0::MulAddX(Vu0::Vec::Of(self->qA0), Vu0::Sub(Vu0::Vec::Of(target), Vu0::Vec::Of(self->qA0)), Vu0::Vec::ScalarAt(D_0026B544));
        f32 time = D_0026B540;
        Vu0::Q(self->qA0) = vel.q;
        Vu0::Q(self->qC0) = Vu0::DivX(Vu0::Sub(Vu0::Vec::Of(target), vel), Vu0::Vec::Scalar(time)).q;
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
        Vec02 best;
        Vu0::Q(best) = Vu0::Q(D_00248D30);
        f32 bestD = 3.4028235e+38f;
        for (Vec02* q = (Vec02*)o->mesh.verts; q < end; q++) {
            Vu0::Q(cur) = Vu0::Q(*q);
            f32 d = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(v), Vu0::Vec::Of(cur)));
            if (d < bestD) {
                Vu0::Q(best) = Vu0::Q(cur);
                bestD = d;
            }
        }
        p = Vu0::RotateUntied(self->rot50, Vu0::Vec::Of(best));
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
    Vu0::Vec mu;
    mu.q = Vu0::Scalar(-friction);
    Vu0::Vec dir = nv;
    dir = Vu0::MulAddX(dir, Vu0::NormalizeOr(tang1, Vu0::Vec::Of(g_unitXVector)), mu);
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
    Vu0::Q(self->v100) = Vu0::MulAddX(Vu0::Vec::Of(self->v100), Vu0::MulXSum(c1, s, c2, s2), Vu0::Vec::Scalar(k)).q;
    Vu0::Q(self->qA0) = Vu0::Add(Vu0::Vec::Of(self->qA0), Vu0::MulXSum(d1, s, dir, s2)).q;
    if (((f32*)&self->qA0)[2] < D_0026B54C) {
        ((f32*)&self->qA0)[2] = D_0026B54C;
        ShortenEffectLife(self, D_0026B550[0]);
    }
    f32 depth = MaxF(0.0f, Vu0::ToFloat(Vu0::Dot(Vu0::Sub(Vu0::Vec::Of(*at), Vu0::Vec::Of(self->q80)), nv))) + one;
    Vu0::Q(self->q80) = Vu0::MulAddX(Vu0::Vec::Of(self->q80), nv, Vu0::Vec::Scalar(depth)).q;
    return 1;
}
