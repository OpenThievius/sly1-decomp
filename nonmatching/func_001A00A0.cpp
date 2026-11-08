// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 252/276 (91.3%), checked 2026-11-08
// Tried night-close3, 2 compiles: Clamp loading hi before lo, Clamp assigning v then c: no change or worse.
#include "common.h"
#include "effect.h"
#include "globals.h"
#include "placed_object.h"
#include "value_range.h"
#include "vu0.h"
extern f32 g_gameTime;
void RemoveEffect(Effect* self);
void func_001268B8(void* world, void* a1, void* a2, void* a3, f32 a, f32 b);
// NEAR (2026-11-08, night-close9): the clamp written c = v first, then the two tests reading the bounds, gives retail's
// quotient register (f4); left: retail loads the high bound before the first compare and stores the weight in the
// first bc1f's delay slot; ours loads the bound after it (also with ValueRange::Limit or Clamp, or the bound named).
// Earlier (wave 3 retry): Vu0::Scalar(-m) in the MulAddX gives the same code as the k
// local (the lever is not what blocks it). Left: retail keeps the clamp's high bound (lwc1 f5)
// loaded before the first compare, the quotient in f4, and stores the weight (sqc2 vf3,16(sp))
// in the delay slot of the first bc1f; here the quotient is in f5, the bound is loaded in that
// slot and the store comes before the loads of the quadratic.
// The coefficients of a quadratic in t (a + bt + ct^2), as the pose holds them.
struct QuadraticCoeffs { f32 a, b, c; };

// A quadratic evaluated at t and clamped to a range (func_001A5760).
struct ClampedQuadratic {
    static f32 Eval(const QuadraticCoeffs* p, f32 t)
    {
        return p->a + t * (p->b + t * p->c);
    }
    static void Clamp(f32& c, f32 v, const ValueRange* r)
    {
        c = v;
        if (v < r->lo) {
            c = r->lo;
        } else if (r->hi < v) {
            c = r->hi;
        }
    }
    static void Get(f32& c, const QuadraticCoeffs* p, f32 t)
    {
        Clamp(c, Eval(p, t), &g_unitRange);
    }
};

void func_001A00A0(Effect* self, void* a1)
{
    Vec02 pos;
    Vec02 k;
    f32 t = g_gameTime - self->start;
    f32 m = self->f120;
    if (t < m) {
        m = t;
    }
    Vu0::Q(k) = Vu0::FromFloat(-m);
    Vu0::Q(pos) = Vu0::MulAddX(Vu0::Q(self->q80), Vu0::Q(self->qA0), Vu0::Q(k));
    f32 p = t / self->life;
    f32 x;
    ClampedQuadratic::Get(x, (const QuadraticCoeffs*)&self->q40, p);
    f32 y = ClampedQuadratic::Eval((const QuadraticCoeffs*)&self->q30, p);
    if (x <= 0.0f || y <= 0.0f) {
        RemoveEffect(self);
    } else {
        func_001268B8(self->p20, a1, &pos, &self->q80, y, x);
    }
}
