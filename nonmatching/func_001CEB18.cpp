// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 716/732 (97.8%), checked 2026-11-10
// NEAR (2026-11-10, w11): every register is retail's; two pairs of instructions after the call
// are in each other's order (retail: lwc1 of the radius before the vsub, mul.s r*r before the
// qmfc2 of the squared distance). Found this round: out1's inside value is Sqrt(dist2) - r
// (the old notes had Sqrt(r*r), wrong code); the two early outcomes return each with its own
// tail (cross-jumping merges them after reload: retail's shared `swc1 $f0,0(s1)` and the solve
// block last), which also lets the first block's Scalar(t) reach the tails (frame 208, the
// spill at 0x60); TransformPointAtTime takes t third (the argument moves: the $f12 copy ranks
// before a3's, as in player.cpp's matched caller; func_001259D8 stays EXACT declared so); the
// length normalisation is a file inline with the fallback by reference (its address before the
// test). Still differs: the squared distance's conversion. ToFloat gives retail's registers
// (product vf2, 1.0 vf3, qmfc2 into reload's a0) but its mtc1 is reload's (cost 2), so the
// vsub chain ties the radius chain at priority 9 and wins on dependents; retail's order needs
// a chain of 8 (ToFloatMoved or ToFloatViaBits give it), which needs the product in VU_REGS
// with a compiler qmfc2 into a reload register: the wall of func_00186230 and func_001D4348
// (docs/TOOLCHAIN.md, "A compiler's qmfc2 of a VU0 product").
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "on_off_object.h"
#include "game_clock.h"
#include "item_keeper.h"
#include "shapes.h"
#include "vu0.h"
#include "fpu.h"
#include "globals.h"
extern float D_00274E08;
extern float D_00274E14;
void TransformPointAtTime(BaseObject* self, BaseObject* top, f32 t, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin);
extern const Vec02 D_00248D30;

// v made unit length, or fallback when shorter than 0.0001; returns its length.
static inline f32 NormalizeVector(Vec02& v, const Vec02& fallback)
{
    u128 len = Vu0::Length(Vu0::Q(v));
    if (Vu0::ToFloat(len) < 0.0001f) {
        v = fallback;
    } else {
        Vu0::Set(v, Vu0::DivX(Vu0::Q(v), len));
    }
    return Vu0::ToFloatMoved(len);
}

void func_001CEB18(Player* self, BaseObject* obj, Vec02* point, f32* out1, Vec02* out2, Vec02* out3, f32 t)
{
    Vec02 pos0;
    Vec02 p;
    Vec02 d;
    Vec02 acc;
    Vec02 vel;
    Vu0::Set(pos0, Vu0::MulAddX2(Vu0::Q(self->pos), Vu0::Q(self->v150), Vu0::Scalar(t), Vu0::Q(self->gravity), Vu0::Scalar(t * (t * 0.5f))));
    p = *point;
    TransformPointAtTime(obj, 0, t, &p, 0, 0, 0);
    Vu0::Set(d, Vu0::Sub(Vu0::Q(p), Vu0::Q(pos0)));
    f32 r = D_00274E08;
    f32 dist2 = Vu0::ToFloat(Vu0::Dot(Vu0::Q(d), Vu0::Q(d)));
    if (dist2 < r * r) {
        if (out1 != 0) {
            *out1 = Fpu::Sqrt(dist2) - r;
        }
        if (out2 != 0) {
            *out2 = pos0;
        }
        if (out3 != 0) {
            Vu0::Q(*out3) = Vu0::MulAddX(Vu0::Q(self->v150), Vu0::Q(self->gravity), Vu0::Scalar(t));
        }
        return;
    }
    f32 az = __builtin_fabsf(d.z);
    if (r < az || t == 0.0f) {
        if (out1 != 0) {
            *out1 = az + 1010000.0f;
        }
        if (out2 != 0) {
            *out2 = pos0;
        }
        if (out3 != 0) {
            Vu0::Q(*out3) = Vu0::MulAddX(Vu0::Q(self->v150), Vu0::Q(self->gravity), Vu0::Scalar(t));
        }
        return;
    }
    d.z = 0.0f;
    f32 l = NormalizeVector(d, D_00248D30);
    f32 gap = l - Fpu::Sqrt(D_00274E08 * D_00274E08 - az * az);
    Vu0::Set(acc, Vu0::MulX(Vu0::Q(d), Vu0::Scalar((gap + gap) / (t * t))));
    Vu0::Set(vel, Vu0::MulAddX2(Vu0::Q(self->v150), Vu0::Q(self->gravity), Vu0::Scalar(t), Vu0::Q(acc), Vu0::Scalar(t)));
    if (out1 != 0) {
        *out1 = ((D_00274E14 + D_00274E14) * gap / t) <? 1000000.0f;
    }
    if (out2 != 0) {
        Vu0::Q(*out2) = Vu0::MulAddX(Vu0::Q(pos0), Vu0::Q(acc), Vu0::Scalar(t * (t * 0.5f)));
    }
    if (out3 != 0) {
        Vu0::Q(*out3) = Vu0::MulAddX2(Vu0::Q(self->v150), Vu0::Q(self->gravity), Vu0::Scalar(t), Vu0::Q(acc), Vu0::Scalar(t));
    }
}
