// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 644/656 (98.2%), checked 2026-11-07
#include "common.h"
#include "anim_curve.h"
#include "placed_object.h"
#include "globals.h"
#include "vu0.h"
// NEAR (2026-11-08, wave 3 retry): FromFloatAt, an f32 local for the first use (compare, mfc1)
// and the loop-invariant p0 declared first in the loop body, with each accumulator read before
// the weight's store, give retail's code but for the order of lqc2 and qmtc2 in the second and
// third uses (retail: lw, qmtc2, lqc2; here lw, lqc2, qmtc2) and the third weight's register
// (retail s0, here v0). Needs no ToBits.
s32 FindCyclicRangeIndex(f32 x, f32 period, s32 count, BlendTimeScale* p, f32* out);

void func_00120470(PositionCurveKind2* o, PlacedObject* cam, s32 c, Vec02* out0, Vec02* out1, f32 dt, f32 scale)
{
    Vec02 x0;
    Vec02 x1;
    Vec02 k;
    f32 x2;
    Vec02* p1;
    if (out0)
        Vu0::Q(*out0) = Vu0::Zero();
    if (out1)
        Vu0::Q(*out1) = Vu0::Zero();
    BlendSequence* seq = o->seq;
    BlendConfig* cfg = o->cfg;
    f32 t;
    s32 idx;
    if (!seq) {
        t = dt / cfg->length;
    } else {
        idx = FindCyclicRangeIndex(dt, cfg->length, seq->count, seq->pairs, &x2);
        t = x2 / seq->pairs[idx].b;
    }
    for (s32 i = 0; i < cfg->count; i++) {
        BlendEntry* e = (BlendEntry*)(cfg->base + i * cfg->stride);
        Vec02* p0 = out0 ? &x0 : 0;
        f32 wt = e->weight;
        if (wt == 0.0f)
            continue;
        PositionCurve* tg = o->targets[i];
        if (!tg) {
            if (out0) {
                u128 w = Vu0::FromFloat(wt);
                u128 acc = Vu0::Q(*out0);
                Vu0::Q(k) = w;
                Vu0::Q(*out0) = Vu0::MulAddX(acc, Vu0::Q(cam ? cam->v190 : D_00248D30), w);
            }
        } else {
            f32 a, b;
            if (!seq) {
                f32 s = e->sub->length;
                b = s / cfg->length;
                a = t * s;
            } else {
                BlendTimeScale* q = (BlendTimeScale*)((u8*)e + seq->stride + idx * 8);
                b = q->b;
                a = q->a + t * b;
                if (e->sub->length < a)
                    a -= e->sub->length;
                b = b / seq->pairs[idx].b;
            }
            tg->vt->eval(tg, cam, c, p0, out1 ? &x1 : 0, a, b * scale);
            if (out0) {
                u128 w = Vu0::FromFloatAt(e->weight);
                Vu0::Q(k) = w;
                Vu0::Q(*out0) = Vu0::MulAddX(Vu0::Q(*out0), Vu0::Q(x0), w);
            }
            if (out1) {
                u128 w = Vu0::FromFloatAt(e->weight);
                Vu0::Q(k) = w;
                Vu0::Q(*out1) = Vu0::MulAddX(Vu0::Q(*out1), Vu0::Q(x1), w);
            }
        }
    }
    if (cam && cam->desc02()->m28)
        cam->desc02()->m28(cam, out0, out1);
}
