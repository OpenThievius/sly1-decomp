// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 0/0 (0.0%), checked 2026-11-08
// NEAR (2026-11-08): DrawPhasedEffect (func_001A15D8): retail's size, frame and loops; regdiff: order, 95.2% of the instructions. What got there: the two inner loops start straight after their test (a statement between the test and the do lets GCSE hoist every address and product out of them, which retail does not), the fraction computed before the turn in the second (a float subtraction after the turn's branch may trap, so loop.c leaves pos - rest inside), t reused as the fraction, one point pointer for all three loops (loop 2's pointer in s0), the search index apart from the loop counter, the q30 curve evaluated before the c clamp, and the u128 forms of the sums and the product (the Vec forms make the inner loops too big for loop.c to move the 0.0 and 1.0). Still differs: loop 1's float temporaries ($f6/$f7, $f3/$f5 swapped) and the first clamp's hi load (retail in bc1f's delay slot, here before it); the first inner loop's product computes rows 0, 1, 2 where retail computes 0, 2, 1 (vf registers follow); the order of two preheader insns (lui s7 / addiu s2). Needs the Camera::rot3A0, Effect::i12C and Effect::points fields this branch adds.
// In the context of its file, src/main/file_19E040.cpp.
#include "common.h"
#include "vu0.h"
#include "camera.h"
#include "effect.h"
#include "globals.h"
#include "value_range.h"
#include "mul_rotation.h"

extern f32 g_gameTime;
extern f32 D_0026B620[4];
extern f32 D_0026B630[4];
extern f32 D_0026B640[4];
extern f32 D_0026B650[4];
extern f32 D_0026B660[4];
extern f32 D_0026B670[4];
extern f32 D_0026B680[4];
extern f32 D_0026B690[4];
f32 ArctangentOfRatio(f32 a, f32 b);
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);
void BuildScaledTransformMatrix(f32* pos, f32 (*rot)[4], f32* scale, f32 (*out)[4]);

struct EffectDraw {
    f32 m[4][4];            // 0x00
    f32 alpha;              // 0x40
    f32 f44;                // 0x44: 1.0
};

struct QuadraticCoeffs { f32 a, b, c; };

struct ClampedQuadratic {
    static f32 Eval(const QuadraticCoeffs* p, f32 t)
    {
        return p->a + t * (p->b + t * p->c);
    }
    static void Clamp(f32& c, f32 v, const ValueRange* r)
    {
        f32 lo = r->lo;
        f32 hi = r->hi;
        if (v < lo) {
            c = lo;
        } else if (hi < v) {
            c = hi;
        } else {
            c = v;
        }
    }
    static void Get(f32& c, const QuadraticCoeffs* p, f32 t)
    {
        Clamp(c, Eval(p, t), &g_unitRange);
    }
};

// A point of a phased effect's strip, as the effect's source writes them (+0x130): where the
// piece starts, the point whose x and y head to the next one and whose z is its width, then
// what DrawPhasedEffect works out for it.
struct PhasedEffectPoint {
    Vec02 base;             // 0x00
    Vec02 at;               // 0x10
    f32 heading;            // 0x20: the angle to the next point, 0 to 2 pi
    f32 length;             // 0x24: the distance to the next point in x and y
    f32 turn;               // 0x28: the turn to the next point's heading, over its width
    s32 id;                 // 0x2C
};

void DrawPhasedEffect(Effect* self, Camera* cam)
{
    PhasedEffectPoint pts[64];
    EffectDraw draw;
    Vec02 v;
    Mat02 m;
    Mat02 rot;
    Vec02 scale;
    f32 one = 1.0f;
    f32 x = (g_gameTime - self->start) / self->life;
    f32 t;
    if (x < 0.0f) {
        t = 0.0f;
    } else if (one < x) {
        t = one;
    } else {
        t = x;
    }
    f32 size;
    switch (self->i120) {
    case 0:
        size = D_0026B620[0] + t * (D_0026B620[1] + t * D_0026B620[2]);
        break;
    case 1:
        size = D_0026B630[0];
        break;
    case 2:
        size = D_0026B630[0] + t * (D_0026B630[1] + t * D_0026B630[2]);
        break;
    }
    f32 total = 0.0f;
    s32 i;
    s32 cur;
    PhasedEffectPoint* p;
    s32 n = self->points(self->p134, 0x3F, pts);
    pts[n] = pts[0];
    f32 scaleMin = 3.402823466e+38f;
    draw.f44 = 1.0f;
    draw.alpha = 0.0f;
    for (i = 0; i < n; i++) {
        p = &pts[i];
        Vu0::Q(v) = Vu0::Sub(Vu0::Q(pts[i + 1].at), Vu0::Q(p->at));
        f32 h = ArctangentOfRatio(v.y, v.x) + 3.14159274f;
        f32 w = cam->f1E4 >? p->at.z;
        p->heading = h;
        f32 a;
        f32 b;
        f32 c;
        ClampedQuadratic::Get(a, (const QuadraticCoeffs*)&self->q40, t);
        ClampedQuadratic::Clamp(b, ClampedQuadratic::Eval((const QuadraticCoeffs*)D_0026B660, w), (const ValueRange*)D_0026B670);
        draw.alpha = a * b >? draw.alpha;
        f32 s = ClampedQuadratic::Eval((const QuadraticCoeffs*)&self->q30, t);
        ClampedQuadratic::Clamp(c, ClampedQuadratic::Eval((const QuadraticCoeffs*)D_0026B640, w), (const ValueRange*)D_0026B650);
        s *= c;
        f32 len = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(v), Vu0::Q(v))));
        scaleMin = s <? scaleMin;
        p->length = len;
        total += len;
    }
    pts[n] = pts[0];
    for (i = 0; i < n; i++) {
        p = &pts[i];
        f32 dh = p[1].heading - p->heading;
        if (dh <= 0.0f) {
            dh += 6.28318548f;
        }
        f32 turn = dh * D_0026B630[0] / p[1].at.z;
        p->turn = turn;
        total += turn;
    }
    pts[n] = pts[0];
    if (self->i128 < 0) {
        f32 c;
        ClampedQuadratic::Clamp(c, ClampedQuadratic::Eval((const QuadraticCoeffs*)D_0026B680, total), (const ValueRange*)D_0026B690);
        self->i128 = (s32)c;
        cur = n;
    } else {
        for (cur = 0; cur < n; cur++) {
            if (pts[cur].id == self->i12C) {
                break;
            }
        }
    }
    if (!(cur < n)) {
        self->i12C = pts[0].id;
        cur = 0;
    }
    f32 pos = self->f124 * total / (f32)self->i128;
    i = 0;
    while (i < n) {
        s32 nextI = i + 1;
        s32 next = cur + 1;
        p = &pts[cur];
        f32 step = 0.0f;
        f32 rest = pos - p->length;
        if (rest < step) {
            do {
                t = (pos + step) / (pos - rest);
                BuildAxisAngleMatrix(&g_unitXVector, &m, p->heading);
                f32 k = size * scaleMin;
                MulRotationRowsX(&rot, cam->rot3A0, m);
                Vu0::Q(scale) = Vu0::Splat(scaleMin);
                Vu0::Q(v) = Vu0::MulXSum3(Vu0::Q(p->base), Vu0::Scalar(1.0f - t), Vu0::Q(p[1].base), Vu0::Scalar(t), Vu0::Q(rot.r[2]), Vu0::Scalar(k));
                BuildScaledTransformMatrix(&v.x, (f32 (*)[4])&rot, &scale.x, draw.m);
                PlacedObject* o = (PlacedObject*)self->p20;
                o->desc02()->m26(o, cam, &draw);
                step += total / (f32)self->i128;
            } while (rest + step < 0.0f);
        }
        pos = rest + step;
        step = 0.0f;
        rest = pos - p->turn;
        if (rest < step) {
            do {
                t = (pos + step) / (pos - rest);
                f32 dh = p[1].heading - p->heading;
                if (dh <= 0.0f) {
                    dh += 6.28318548f;
                }
                BuildAxisAngleMatrix(&g_unitXVector, &m, p->heading + t * dh);
                f32 k = size * scaleMin;
                MulRotationRowsX(&rot, cam->rot3A0, m);
                Vu0::Q(scale) = Vu0::Splat(scaleMin);
                Vu0::Q(v) = Vu0::MulAddX(Vu0::Q(p[1].base), Vu0::Q(rot.r[2]), Vu0::Scalar(k));
                BuildScaledTransformMatrix(&v.x, (f32 (*)[4])&rot, &scale.x, draw.m);
                PlacedObject* o = (PlacedObject*)self->p20;
                o->desc02()->m26(o, cam, &draw);
                step += total / (f32)self->i128;
            } while (rest + step < 0.0f);
        }
        cur = next % n;
        i = nextI;
        pos = rest + step;
    }
}
