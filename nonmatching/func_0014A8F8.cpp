// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 400/404 (99.0%), checked 2026-11-08
// NEAR (2026-11-08, w5-14A8F8): 2 lines from retail, the order of two stores. The eye's
// MulAddX takes Vu0::Vec values (Vec::Of(frame->v140), Vec::Of(basis.r[0]), Vec::Scalar(10)):
// both Vec::Of and Vec::Scalar are nested inline calls, evaluated in argument order, so the
// v140 load comes before the Scalar slot's store (k at 0x60) and that store no longer feeds the
// load: sched1 puts it after the vmaddx, as retail does (the u128 MulAddX with a Scalar or a
// named k evaluated the slot first). Still differs: retail stores row 0 of basis (0x00) before
// row 2 of the vector locals (0xb0); here 0xb0 first. Mechanism (sched1 -dS dumps): the five
// stores after the third product have priority 23 (they all feed the v140 load); 0x10 and 0x20
// are the deaths of rows 1 and 2 (weight -1) and go first, the rest tie and fall to INSN_LUID,
// and every form whose copy `*out = r` follows both of row 2's stores gives 0x80, 0xb0, 0x00.
// tools/permute.py on split statements finds retail's order only with out's row 0 (and
// optionally row 1) copied between the two row-2 stores (r.r[2] = p2; out->r[0] = r.r[0];
// z = p2; out->r[1..2] = ...), which is not a form the original plausibly had. The shared
// mul_rotation.h forms give 3 (MulRotationRowsIndexed) to 100 lines. Ruled out: alias flags
// (x/y/z are aggregates, never MEM_SCALAR_P, so fixed_scalar_and_varying_struct_p cannot drop
// 0xb0's dependence on the v140 load), the class rule (no dependence between frame stores at
// distinct offsets) and dependent counts (all seven).
#include "common.h"
#include "camera.h"
#include "camera_controller.h"
#include "placed_object.h"
#include "vu0.h"

extern f32 g_gameTime[];
void func_00144BE8(Camera* a, s32 b, void* c, s32 d, s32 e, f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5);

static inline void RotateRowsInto(Mat02* out, const Mat02& m, const Mat02& rows)
{
    Mat02 r;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    u128 m0 = (*(const Vu0::Vec*)&m.r[0]).q;
    u128 m1 = (*(const Vu0::Vec*)&m.r[1]).q;
    u128 m2 = (*(const Vu0::Vec*)&m.r[2]).q;
    Vu0::Q(x) = Vu0::Q(r.r[0]) = Vu0::RotateRows(m0, m1, m2, (*(const Vu0::Vec*)&rows.r[0]).q);
    Vu0::Q(y) = Vu0::Q(r.r[1]) = Vu0::RotateRows(m0, m1, m2, (*(const Vu0::Vec*)&rows.r[1]).q);
    Vu0::Q(z) = Vu0::Q(r.r[2]) = Vu0::RotateRows(m0, m1, m2, (*(const Vu0::Vec*)&rows.r[2]).q);
    *out = r;
}

void UpdateFrameCameraController(FrameCameraController* self, f32 dt)
{
    Camera* cam = self->owner;
    PlacedObject* frame = (PlacedObject*)cam->stack[0].target;
    Mat02 basis;
    Vec02 rv;
    Vec02 eye;
    Vec02 target;
    RotateRowsInto(&basis, frame->m110, *(Mat02*)&self->frame20);
    Vu0::Q(eye) = Vu0::MulAddX(Vu0::Vec::Of(frame->v140), Vu0::Vec::Of(basis.r[0]), Vu0::Vec::Scalar(10.0f)).q;
    Vu0::Q(rv) = Vu0::Rotate(frame->m110, Vu0::Q(*(Vec02*)((u8*)self + 0x10)));
    Vu0::Q(target) = Vu0::Add(Vu0::Q(frame->v140), Vu0::Q(rv));
    Vu0::Q(eye) = Vu0::Add(Vu0::Q(eye), Vu0::Q(rv));
    f32 one = 1.0f;
    f32 d = g_gameTime[0] - cam->f364;
    f32 t;
    if (d < 0.0f) {
        t = 0.0f;
    } else if (one < d) {
        t = one;
    } else {
        t = d;
    }
    f32 u = 1.0f - t;
    func_00144BE8(cam, 1, &target, (s32)&eye, 0, t * 100.0f + u * 20.0f, t * -15.0f + u * -7.0f, t * 0.25f + u, 0.0f, 0.0f, dt);
}
