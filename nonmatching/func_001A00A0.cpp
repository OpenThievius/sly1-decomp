// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 249/276 (90.2%), checked 2026-11-09
#include "common.h"
#include "effect.h"
#include "globals.h"
#include "placed_object.h"
#include "value_range.h"
#include "vu0.h"
extern f32 g_gameTime;
void RemoveEffect(Effect* self);
void func_001268B8(void* world, void* a1, void* a2, void* a3, f32 a, f32 b);
// NEAR (2026-11-09, w7): with the file's ClampedQuadratic (both bounds loaded before the
// compare) every instruction but four is retail's; what is left is the Scalar-slot wall
// (docs/TOOLCHAIN.md, "The weight slot of func_00181078"). k's slot store (`Q(k) = ...`, neither
// alias flag, frame base) and the coefficient loads through Clamp's `p` (`mem/s`, a pseudo
// `self + 0x40` with no known base: find_base_value loses the ADDRESS of a PLUS) may alias, so
// sched1 issues the store at t=4, before the loads, and the quotient ends in $f5, hi in $f4.
// Retail loads the coefficients first and stores k last (reorg puts it in the first bc1f's
// delay slot), and its slot is at 16(sp), after pos: a MEM_SCALAR_P slot, which
// fixed_scalar_and_varying_struct_p separates from the loads. Experiment (not a form): k as a
// `volatile u128` local given FromFloat's value gives every register and the order; only the
// store stays out of the delay slot (reorg does not move a volatile store). Not a signature
// issue: slot 5 of the kind-8 and kind-17 tables is a draw method (self, camera), and retail's
// code calls neither DrawEffect nor any other base method here.
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
