// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 918/924 (99.4%), checked 2026-11-08
// NEAR: 228 of 231 instructions equal by position (regdiff); same frame, jump table (the rodata check passes) and registers. The one difference is the tail of state5D8 == 0, the fade-in/out scale of the sequenced object: retail has a single block for the lowest scale (0.1f, loaded afresh with lui/ori/mtc1) that the compare of state 0 (`bc1t`), state 1 and state 2 (fall through) all go to, and each arm stores z (delay slot) then jumps to the shared store of y; here the low arm of state 0 reuses the compare's register (`mov.s $f0,$f3`) and takes `bc1f`/`b` around it. Writing the low arm as a goto-shared block, as separate `scale.y = scale.z = 0.1f` arms, or the compare the other way gave 85 to 89 percent. Found: the clamp is an inline function of three arguments (ClampRange(v, lo, hi): its constants are loaded before the first compare, as retail does); the cases lie in retail's order 0/4, 3/7, 1/2/5, 6; the sub-switch is 0, 1, 2; the vector is stored z then y (`scale.z = scale.y = r`); the blend's float read at tmp+0x40 is the transform's f40.
// In the context of its file, src/main/timed_object.cpp.
#include "common.h"
#include "timed_object.h"
#include "switched_collider.h"
#include "globals.h"
#include "vu0.h"

extern f32 g_gameTime[];

struct SequencedTransform {
    Quad16 rows[4];
    f32 f40;
    f32 f44;
    u8 pad48[8];
};
void BuildPlacedObjectTransform(PlacedObject* self, Quad16* src, SequencedTransform* dst);
void BuildScaledTransformMatrix(Vec02* pos, Mat02* rot, Vec02* scale, SequencedTransform* out);
void func_001268B8(void* world, void* a1, void* a2, void* a3, f32 a, f32 b);

static inline f32 ClampRange(f32 v, f32 lo, f32 hi)
{
    if (v < lo) {
        return lo;
    }
    if (hi < v) {
        return hi;
    }
    return v;
}

void func_001B0838(SequencedObject* self, void* a1, Quad16* a2)
{
    Vec02 scale;
    SequencedTransform tmp;
    Collider* tgt;
    if (self->state != 8) {
        BuildPlacedObjectTransform(self, a2, &tmp);
        switch (self->state) {
        case 0:
        case 4: {
            f32 t;
            if (self->f5B8 == 0.0f) {
                t = 1.0f;
            } else {
                t = (g_gameTime[0] - self->f55C) / self->f5B8;
                t = ClampRange(t, 0.0f, 1.0f);
            }
            Vu0::Q(scale) = Vu0::Splat(t);
            scale.x = 1.0f;
            break;
        }
        case 3:
        case 7: {
            f32 t;
            if (self->f5BC == 0.0f) {
                t = 0.0f;
            } else {
                t = 1.0f - (g_gameTime[0] - self->f55C) / self->f5BC;
                t = ClampRange(t, 0.0f, 1.0f);
            }
            Vu0::Q(scale) = Vu0::Splat(t);
            scale.x = 1.0f;
            break;
        }
        case 1:
        case 2:
        case 5:
            Vu0::Q(scale) = Vu0::Splat(1.0f);
            break;
        case 6: {
            f32 r;
            scale.x = 1.0f;
            switch (self->state5D8) {
            case 0:
                if (self->f5E0 == 0.0f) {
                    r = 0.1f;
                } else {
                    r = 1.0f - (g_gameTime[0] - self->f5DC) / self->f5E0;
                    r = ClampRange(r, 0.1f, 1.0f);
                }
                scale.z = scale.y = r;
                break;
            case 1:
                if (g_player != 0 && self->f5D4 != 0) {
                    f32 w;
                    if (self->f5E4 == 0.0f) {
                        w = 1.0f;
                    } else {
                        w = ClampRange((g_gameTime[0] - self->f5DC) / self->f5E4, 0.0f, 1.0f);
                    }
                    Vec02 blend;
                    Vu0::Q(blend) = Vu0::MulXSum(Vu0::Q(self->v140), Vu0::Scalar(1.0f - w), Vu0::Q(((Collider*)g_player)->v140), Vu0::Scalar(w));
                    func_001268B8((void*)self->f5D4, a1, &blend, &((Collider*)g_player)->v140, 10.0f, tmp.f40);
                }
                r = 0.1f;
                scale.z = scale.y = r;
                break;
            case 2:
                if (self->f5E8 == 0.0f) {
                    r = 1.0f;
                } else {
                    r = (g_gameTime[0] - self->f5DC) / self->f5E8;
                    r = ClampRange(r, 0.1f, 1.0f);
                }
                scale.z = scale.y = r;
                break;
            }
            break;
        }
        }
        if (self->state >= 0) {
            if (self->state < 4) {
                tgt = self;
            } else if (self->state < 8) {
                tgt = self->f5D0;
            }
        }
        BuildScaledTransformMatrix(&self->v140, &self->m110, &scale, &tmp);
        tgt->desc02()->m26(tgt, a1, &tmp);
    }
}
