// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 664/656, checked 2026-11-07
// NEAR: the position curve of kind 2 (a weighted mix of other position curves, like func_00120D58 for values). The frame, the calls and the loop are retail's. It differs in how the weight reaches the vector unit: retail loads it as an integer (`lw`, then qmtc2), reusing the register of the entry pointer in the last case, and keeps the first use's value in $f1 (mfc1), while ours loads it as a float (lwc1, mfc1); a local for the weight, either `u128` or `f32`, moves the problem (as an f32 local the compare's operand is converted through a GPR). The point to the owner's position is also loaded in a different order (the FromFloat result is the third input of the multiply-add in retail).
#include "common.h"
#include "anim_curve.h"
#include "placed_object.h"
#include "globals.h"
#include "vu0.h"

s32 FindCyclicRangeIndex(f32 x, f32 period, s32 count, BlendTimeScale* p, f32* out);

void func_00120470(PositionCurveKind2* o, PlacedObject* cam, s32 c, Vec02* out0, Vec02* out1, f32 dt, f32 scale)
{
    Vec02 x0;
    Vec02 x1;
    Vec02 k;
    f32 x2;
    Vec02* p0;
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
    p0 = out0 ? &x0 : 0;
    for (s32 i = 0; i < cfg->count; i++) {
        BlendEntry* e = (BlendEntry*)(cfg->base + i * cfg->stride);
        if (e->weight == 0.0f)
            continue;
        PositionCurve* tg = o->targets[i];
        if (!tg) {
            if (out0) {
                u128 w = Vu0::FromFloat(e->weight);
                Vu0::Q(k) = w;
                Vu0::Q(*out0) = Vu0::MulAddX(Vu0::Q(*out0), Vu0::Q(cam ? cam->v190 : D_00248D30), w);
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
                Vu0::Q(k) = Vu0::FromFloat(e->weight);
                Vu0::Q(*out0) = Vu0::MulAddX(Vu0::Q(*out0), Vu0::Q(x0), Vu0::Q(k));
            }
            if (out1) {
                Vu0::Q(k) = Vu0::FromFloat(e->weight);
                Vu0::Q(*out1) = Vu0::MulAddX(Vu0::Q(*out1), Vu0::Q(x1), Vu0::Q(k));
            }
        }
    }
    if (cam && cam->desc02()->m28)
        cam->desc02()->m28(cam, out0, out1);
}
