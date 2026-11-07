// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 276/284 (97.2%), checked 2026-11-07
// NEAR (2026-11-08, vu0w3-e1): one scheduling order: retail computes g_unitRange's hi address (addiu v1) before the first of the three lwc1/swc1 copies of +0x1F0..0x1F8; here it follows the first load. Tried the range as a pointer local, the copies before and after the length, tools/permute.py --auto.
#include "common.h"
#include "vu0.h"
#include "effect_spawner.h"
#include "effect.h"
#include "pad_record.h"

f32 RandomFloatInRange(f32 a, f32 b);
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
f32 D_0026B6F0[4] = { 0.75f, 1.25f, 0.0f, 0.0f };
f32 D_0026B700[4] = { 0.0f, 0.001f, 0.0f, 0.0f };

void RandomizeEffectSpin(Effect* self, Rec50* src)
{
    self->life *= RandomFloatInRange(D_0026B6F0[0], D_0026B6F0[1]);
    f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Q(self->qA0)));
    f32 t;
    self->f120 = *(f32*)((u8*)src + 0x1F0);
    self->f124 = *(f32*)((u8*)src + 0x1F4);
    self->f128 = *(f32*)((u8*)src + 0x1F8);
    ClampedQuadratic::Get(t, (const QuadraticCoeffs*)D_0026B700, len);
    f32 s = t * 10.0f;
    f32* p = (f32*)((u8*)self + 0x100);
    for (s32 i = 2; i >= 0; i--) {
        *p++ = RandomFloatInRange(-s, s);
    }
}
