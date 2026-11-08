// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 385/404 (95.3%), checked 2026-11-08
// NEAR (2026-11-08, night-sizex1): 6 lines from retail. The rotation is an inline writing out through a matrix local r and vector locals x, y, z (Q(x) = Q(r.r[i]) = ..., then *out = r), declared r first: retail's three copies (basis 0x00, r 0x60, x/y/z 0x90) with k reusing r's slot; target computed before eye's second sum (tools/permute.py). Still differs: the order of two pairs of stores, basis row 0 against z and k against the MulAddX (retail stores both later); Vec stores and a Scalar for k change nothing. Earlier: (2026-11-08, night-size3) the size and frame are retail's now. The rotation's rows are
// values read as a struct (*(const Vu0::Vec*)&m.r[i]) and the rows rotated are read as a struct
// too, so the stack stores alias them: retail's single load of the matrix and its reloads of rows
// 1 and 2 through a2 = self+0x20 after each product. basis is assigned (not initialised) after rv,
// eye and target are declared, which gives retail's three copies (0x00, 0x60, 0x90) with k reusing
// 0x60; the clamp sets t in each arm and its 1.0 is a named local loaded before the products.
// Still differs: retail stores each product to 0x60 before 0x90 (here 0x90 first) and gives the
// matrix's row 0 vf3 (here vf2), so the products' registers and the store order around the weights
// follow.
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
    Vec02 k;
    Vu0::Q(k) = Vu0::FromFloat(10.0f);
    Vu0::Q(eye) = Vu0::MulAddX(Vu0::Q(frame->v140), Vu0::Q(basis.r[0]), Vu0::Q(k));
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
