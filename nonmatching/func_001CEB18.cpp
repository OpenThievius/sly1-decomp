// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 728/732, checked 2026-11-07
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
// NEAR (2026-11-08, wave 4): the structure is retail's (a point carried to time t, distance test against D_00274E08, the sphere solve with Fpu::Sqrt, three optional outputs); the registers, the order of the three loads of the first MulAddX2 and the t weight differ. Retail keeps one Scalar(t) in vf5 across the call (spilled at 0x60 and reloaded for the early-out's out3) and builds a second in the solve path; here every Scalar(t) is rebuilt (frame 192 against 208). A named tv = Scalar(t) shared by the first expression and the early out gives the frame of 208 but a different schedule.
extern float D_00274E08;
extern float D_00274E14;
void TransformPointAtTime(BaseObject* self, BaseObject* top, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin, f32 t);
extern const Vec02 D_00248D30;

void func_001CEB18(f32 t, Player* self, BaseObject* obj, Vec02* point, f32* out1, Vec02* out2, Vec02* out3)
{
    Vec02 pos0;
    Vec02 p;
    Vec02 d;
    Vec02 acc;
    Vec02 vel;
    Vu0::Set(pos0, Vu0::MulAddX2(Vu0::Q(self->pos), Vu0::Q(self->v150), Vu0::Scalar(t), Vu0::Q(self->gravity), Vu0::Scalar(t * (t * 0.5f))));
    p = *point;
    TransformPointAtTime(obj, 0, &p, 0, 0, 0, t);
    Vu0::Set(d, Vu0::Sub(Vu0::Q(p), Vu0::Q(pos0)));
    f32 r = D_00274E08;
    if (Vu0::ToFloat(Vu0::Dot(Vu0::Q(d), Vu0::Q(d))) < r * r) {
        if (out1 != 0) {
            *out1 = Fpu::Sqrt(r * r) - r;
        }
    } else {
        f32 az = __builtin_fabsf(d.z);
        if (!(r < az) && t != 0.0f) {
            d.z = 0.0f;
            u128 len = Vu0::Length(Vu0::Q(d));
            if (Vu0::ToFloat(len) < 0.0001f) {
                d = D_00248D30;
            } else {
                Vu0::Set(d, Vu0::DivX(Vu0::Q(d), len));
            }
            f32 l = Vu0::ToFloat(len);
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
            return;
        }
        if (out1 != 0) {
            *out1 = az + 1010000.0f;
        }
    }
    if (out2 != 0) {
        *out2 = pos0;
    }
    if (out3 != 0) {
        Vu0::Q(*out3) = Vu0::MulAddX(Vu0::Q(self->v150), Vu0::Q(self->gravity), Vu0::Scalar(t));
    }
}

