// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 932/936 (99.6%), checked 2026-11-08
// Still differs (2026-11-08, night-close5): the weight's lw into a0 and into the dying s0 is a reload of a MEM operand in retail, here a pseudo local-alloc gives v0; combine never puts a MEM into an "r" asm operand (check_asm_operands) and validate_equiv_mem gives no REG_EQUIV when the address dies there (local-alloc.c), so the form retail compiled is still unknown.
#include "common.h"
#include "asm_func.h"
#include "property_descriptor.h"
#include "list_iter.h"
#include "placed_object.h"
#include "state_trigger.h"
#include "masked_collider.h"
#include "animation.h"
#include "attachment.h"
#include "vu0.h"
#include "anim_curve.h"
#include "world.h"
#include "entry_pool.h"
#include "buffered_stream.h"
#include "script_value.h"
// NEAR (2026-11-08, worker night-vumid2): retail's code but for two words: the bits of the
// weight e->weight that qmtc2 takes. Retail loads them with `lw a0,0(s0)` in the angle vector's
// arm and with `lw s0,0(s0)` (into the dying pointer e) in the angle arm that adds a weighted
// vector; here the loads (the asm operand's reload) take v0 in both. The same difference as
// func_00120470 (the third weight there) and func_00122DE0 (the weight loaded into the dead
// self register). Found: slot 1 of the targets' table (+4) is their angles, not slot 0; the
// flag at +0x18 picks the matrices' product over the angles' sum, with the product arm first;
// axis, rotA and prod are locals of the innermost block (they share the weights' slot at 0x40).
extern u8 D_00248D30[];
s32 FindCyclicRangeIndex(f32 x, f32 period, s32 count, BlendTimeScale* p, f32* out);
void BuildEulerRotationMatrix(void* a, void* b);
extern void MultiplyMatrices3x3(void*, void*, void*);
extern void MatrixToAxisAngle(void*, void*, void*);
void RotateVectorByTwoAngles(void* a, void* b, void* c);
typedef void (*KeyedRotationToldFn)(PlacedObject* self, void* output, void* state);

// The product a b of two rotations into out: b's rows each rotated by a, the rows of both read
// once.
static inline void MulRotation(Mat02* out, const Mat02& a, const Mat02& b)
{
    Mat02 r;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    const u128* p = (const u128*)&a;
    const u128* q = (const u128*)&b;
    u128 a0 = p[0], a1 = p[1], a2 = p[2];
    u128 b0 = q[0], b1 = q[1], b2 = q[2];
    Vu0::Q(x) = Vu0::RotateRows(a0, a1, a2, b0);
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateRows(a0, a1, a2, b1);
    r.r[1] = y;
    Vu0::Q(z) = Vu0::RotateRows(a0, a1, a2, b2);
    r.r[2] = z;
    *out = r;
}

void BuildAxisAngleMatrix(const Vec02* axis, f32 angle, Mat02* out);

void func_00120700(RotationCurveKind2* o, PlacedObject* cam, s32 c, Mat02* out0, Vec02* out1, f32 dt, f32 scale)
{
    Vec02 x0;
    Vec02 acc0;
    Vec02 x1;
    Vec02 acc1;
    f32 x2;
    if (out0)
        Vu0::Q(acc0) = Vu0::Zero();
    if (out1)
        Vu0::Q(acc1) = Vu0::Zero();
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
    f32 w = 0.0f;
    for (s32 i = 0; i < cfg->count; i++) {
        BlendEntry* e = (BlendEntry*)(cfg->base + i * cfg->stride);
        if (e->weight == 0.0f)
            continue;
        RotationCurve* tg = o->targets[i];
        if (!tg) {
            if (!out0)
                continue;
            Vu0::Set(x0, Vu0::Q(cam ? cam->v1D0 : *(Vec02*)D_00248D30));
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
            tg->vt->get(tg, cam, c, out0 ? &x0 : 0, out1 ? &x1 : 0, a, b * scale);
            if (out1)
                Vu0::Q(acc1) = Vu0::MulAddX(Vu0::Q(acc1), Vu0::Q(x1), Vu0::ScalarAt(e->weight));
        }
        if (!out0)
            continue;
        if (o->f18) {
            if (w == 0.0f) {
                BuildEulerRotationMatrix(&x0, out0);
            } else {
                Vec02 axis;
                Mat02 rotA;
                Mat02 prod;
                f32 angle;
                BuildEulerRotationMatrix(&x0, &rotA);
                MultiplyMatrices3x3(&rotA, out0, &prod);
                MatrixToAxisAngle(&prod, &angle, &axis);
                BuildAxisAngleMatrix(&axis, angle * w / (w + e->weight), &prod);
                MulRotation(out0, prod, rotA);
            }
            w += e->weight;
        } else {
            Vu0::Q(acc0) = Vu0::MulAddX(Vu0::Q(acc0), Vu0::Q(x0), Vu0::ScalarAt(e->weight));
        }
    }
    if (out0 && !o->f18)
        BuildEulerRotationMatrix(&acc0, out0);
    if (out1)
        RotateVectorByTwoAngles(&acc0, &acc1, out1);
    if (cam)
        ((KeyedRotationToldFn)cam->desc02()->m29)(cam, out0, out1);
}
