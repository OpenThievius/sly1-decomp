// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR (2026-11-08, worker large-1DDE90): 565 instructions as retail's, frame 0x280 as retail's,
// everything but one block identical: 27 differing lines, all in the first relaxation loop's
// weight block (L1DE200 to the position update). The VU0 registers there differ (retail: vel vf4,
// b vf8, rel vf5, drag vf3, h vf7, bend vf1, the second vel load vf2; here vf5, vf7, vf4, vf2, vf8,
// vf1, vf3) and sched2 places h's mfc1/qmtc2 after the three-term sum where retail has it before
// bend's. Cause found (-dS dump): sched1 issues h's qmtc2 (an asm with no unit, ready at once) at
// clock 1, so h's vector lives across the whole block and local-alloc gives it the last register;
// retail's h is allocated before b, so its qmtc2 was issued late in retail's sched1 (as if it waited
// on an fmac-unit insn). Tried without change: every order of the weight statements
// (tools/permute.py), the weights inline in the Scalar calls, MinF, every Vec/u128 mix of the
// MulAddX3 operands and of the stores (256 variants), u128 forms of the position update, h passed
// through an inline helper or a copy.
//
// What this needed (docs/TOOLCHAIN.md material): a, d, axis, b, c declared at the top (retail's
// 0x00-0x4F, before the velocity loop's Scalar slot at 0x50), and v, R, M, m declared after the
// relaxation loop in that order (0x50, 0x60, 0x90, 0xC0); one `step` and one `prev` variable for
// every loop (retail keeps them in s1 and s0 throughout; per-loop variables free a saved register
// and `first` is no longer spilled); the clock's step read through an inline taking the clock's
// address (retail's hoisted `addiu a0, v0, %lo` and `lw a1, 8(a0)` in the velocity loop); the
// normalisation as `axis = diff; axis = NormalizeOr(diff, ...)` (the compiler's vmove); the
// constant-first min.s from a named `one` (`rel = one <? rel`); the three nested products as
// by-value returns (their temporaries at 0x150, 0x120 and 0xF0 in reverse order of evaluation, x/y/z
// at 0x180); the result rows written as `*(u128*)&r.r[i]`, not through Q (Q's reference pseudo of
// the 0xF0 temporary is reused by the MultiplyByTransposedMatrix3x3 call and hoisted by loop.c).
//
// Open for the lead: MulAddX3 (vadda, two vmaddax, vmaddx) has this one use in retail, so it is
// not in include/vu0.h; and MulRotationValue uses g++'s named return value (`return r`), a g++
// extension like `<?`. Neither fits include/mul_rotation.h's ten forms.
#include "common.h"
#include "vu0.h"
#include "redirect_object.h"
#include "attachment.h"
#include "globals.h"

void TransformPointBetweenFrames(void* node, s32 frame, Vec02* in, Vec02* out);
extern s32 g_frameCount;
extern f32 g_gameClock[];
void BuildAxisAngleMatrix(const Vec02* t, void* out, f32 x);
void UpdateLinkConstraint(PlacedObject* self);
void ComputeObjectMotionInFrame(void* obj, s32 z, Vec02* point, Vec02* out, s32 a, s32 b, s32 c);
f32 ComputeAngleBetweenVectors(Vec02* a, Vec02* b, Vec02* axis);
f32 SplitVectorAlongAxis(Vec02* v, const Vec02* axis, Vec02* along, Vec02* rest);
void BuildRotationBetweenVectors(Vec02* from, Vec02* to, Mat02* out);
void OrthonormalizeMatrix(Mat02* m);
Mat02 MultiplyByTransposedMatrix3x3(const Mat02& a, const Mat02& b);

// a + b * s.x + c * t.x + d * u.x: MulAddX2 with a third weighted vector (vadda.xyzw ACC, a, vf0;
// two vmaddax.xyzw ACC; vmaddx.xyzw).
static inline u128 MulAddX3(u128 a, u128 b, u128 s, u128 c, u128 t, u128 d, u128 u)
{
    u128 r;
    __asm__("vadda.xyzw ACC, %1, vf0\n\tvmaddax.xyzw ACC, %2, %3x\n\tvmaddax.xyzw ACC, %4, %5x\n\t"
            "vmaddx.xyzw %0, %6, %7x"
            : "=j"(r) : "j"(a), "j"(b), "j"(s), "j"(c), "j"(t), "j"(d), "j"(u));
    return r;
}

static inline Vu0::Vec MulAddX3(Vu0::Vec a, Vu0::Vec b, Vu0::Vec s, Vu0::Vec c, Vu0::Vec t, Vu0::Vec d, Vu0::Vec u)
{
    Vu0::Vec r;
    r.q = MulAddX3(a.q, b.q, s.q, c.q, t.q, d.q, u.q);
    return r;
}

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

void func_001DDE90(RedirectObject* self)
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
    if (self->steps[first - 1].node->f1F0 != 0) {
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
            *(Vec*)&step->vel = MulAddX3(Vec::Of(step->vel), Vec::Of(b), Vec::Scalar(rel), Vec::Of(step->vel),
                                             Vec::Scalar(drag), Vec::Of(c), Vec::Scalar(bend));
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
        Rec2195_224* rec = step->node->f224;
        if (rec != 0) {
            M = MulRotationValue(MulRotationValue(MulRotationValue(m, *(Mat02*)((u8*)rec + 0x30)), step->node->m1A0),
                                 *(Mat02*)step->node->f224);
        } else {
            M = MulRotationValue(m, step->node->m1A0);
        }
        *(Vec*)&v = Vu0::Rotate(M, Vec::Of(step->below));
        BuildRotationBetweenVectors(&v, &a, &R);
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
