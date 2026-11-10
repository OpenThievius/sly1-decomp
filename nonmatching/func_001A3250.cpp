// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 828/836, checked 2026-11-10
// NEAR: 167 of 209 instructions equal by position. The drawing of a facing effect (frustum test with Vu0::PlaneSigns, a basis turned to the camera, five clamped quadratics, MulRotationRowsX of the basis and an axis-angle matrix, then the object's slot 38). The structure, the stack (0x1C0: pos 0, dir 0x10, scale 0x20, axis 0x30, basis 0x60, rot 0x90, draw 0xC0, the PlaneSigns scalar at 0x110, x/y/z 0x120 and r 0x150) and the calls are retail's. Differs: (1) registers of the frustum test: retail loads the radius with lw into s0 (the register of o, which dies there) and has Ones in vf5 and the scalar in vf6; here the load goes to v0 and the two vectors are swapped; (2) the order of the loads and constants of the quadratics after the Length (retail loads D_0026185C, self->start and the 0.001 before the first quadratic's sub, and the table addresses with a different lui sharing); (3) the clamp of the fade is retail's two-sided branch with `mov.s $f0,$f5` / `$f6` where the helper's Clamp writes through a reference. The final call reloads self->p20 (retail does), so o is used only for the radius. Tried the scalar computed before Ones (no change) and o kept through the end (registers worse).
// In the context of its file, src/main/file_19E040.cpp.
#include "common.h"
#include "vu0.h"
#include "effect.h"
#include "camera.h"
#include "world.h"
#include "globals.h"
#include "placed_object.h"
#include "value_range.h"
#include "mul_rotation.h"

extern f32 g_gameTime;
extern Camera* g_camera;
void TransformPointBetweenFrames(void* a0, void* a1, void* a2, void* a3);
void BuildBasisFromXAndZHint(void* a, void* b, void* c);
void BuildScaledTransformMatrix(f32* pos, f32 (*rot)[4], f32* scale, f32 (*out)[4]);
void RemoveEffect(Effect* self);
extern f32 D_0026B730[4];
extern f32 D_0026B740[4];
extern f32 D_0026B750[4];
extern f32 D_0026B760[4];
extern f32 D_0026B770[2];

struct EffectDraw {
    f32 m[4][4];
    f32 alpha;
    f32 f44;
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

void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);

// Draws a facing effect: an object turned to the camera, scaled and faded by the distance and
// by the effect's age.
void func_001A3250(Effect* self, Camera* cam)
{
    Vec02 pos;
    Vec02 dir;
    Vec02 scale;
    Mat02 axis;
    Mat02 basis;
    Mat02 rot;
    EffectDraw draw;
    PlacedObject* o = (PlacedObject*)self->p20;
    if (o != 0) {
        TransformPointBetweenFrames(self->p120, 0, &self->q80, &pos);
        u128 r = Vu0::ScalarAt(o->f2A8);
        u128 ones = Vu0::Ones();
        u128 d = Vu0::Sub(Vu0::Q(pos), Vu0::Q(cam->f40));
        if ((Vu0::PlaneSigns(Vu0::Q(cam->planes[0]), Vu0::Q(cam->planes[1]), Vu0::Q(cam->planes[2]), d, ones, r) ^ 0xF0) != 0) {
            RemoveEffect(self);
            return;
        }
        Vu0::Q(dir) = Vu0::Sub(Vu0::Q(g_camera->f40), Vu0::Q(pos));
        BuildBasisFromXAndZHint(&dir, (void*)&g_unitZVector, &basis);
        f32 k = Vu0::ToFloat(Vu0::Length(Vu0::Q(dir))) * 0.001f;
        f32 t = (g_gameTime - self->start) / self->life;
        f32 near;
        ClampedQuadratic::Clamp(near, ClampedQuadratic::Eval((const QuadraticCoeffs*)D_0026B740, k), (const ValueRange*)D_0026B750);
        Vu0::Q(scale) = Vu0::Splat(ClampedQuadratic::Eval((const QuadraticCoeffs*)&self->q30, t) * near);
        f32 a;
        ClampedQuadratic::Get(a, (const QuadraticCoeffs*)&self->q40, t);
        f32 fade;
        ClampedQuadratic::Clamp(fade, ClampedQuadratic::Eval((const QuadraticCoeffs*)D_0026B760, k), (const ValueRange*)D_0026B770);
        draw.alpha = a * fade;
        draw.f44 = 1.0f;
        BuildAxisAngleMatrix(&g_unitXVector, &axis, ClampedQuadratic::Eval((const QuadraticCoeffs*)D_0026B730, t));
        MulRotationRowsX(&rot, basis, axis);
        BuildScaledTransformMatrix(&pos.x, (f32(*)[4])&rot, &scale.x, draw.m);
        ((PlacedObject*)self->p20)->desc02()->m26((PlacedObject*)self->p20, cam, &draw);
    }
}
