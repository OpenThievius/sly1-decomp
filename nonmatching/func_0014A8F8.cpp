// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 412/404, checked 2026-11-07
// NEAR: same structure and calls; retail stores each rotated row of the frame three times (the matrix and two dead copies at 0x60/0x90, as if a Mat02 were returned by value through two levels) and clamps into a separate float; ours stores one copy (8 bytes larger overall through the clamp's layout). The rows' rotate order and registers differ for the same reason.
#include "common.h"
#include "camera.h"
#include "camera_controller.h"
#include "placed_object.h"
#include "vu0.h"

extern f32 g_gameTime[];
void func_00144BE8(Camera* a, s32 b, void* c, s32 d, s32 e, f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5);

static inline Mat02 RotateRows(const Mat02& m, const Mat02& rows)
{
    Mat02 r;
    Vu0::Q(r.r[0]) = Vu0::Rotate(m, Vu0::Q(rows.r[0]));
    Vu0::Q(r.r[1]) = Vu0::Rotate(m, Vu0::Q(rows.r[1]));
    Vu0::Q(r.r[2]) = Vu0::Rotate(m, Vu0::Q(rows.r[2]));
    return r;
}

void UpdateFrameCameraController(FrameCameraController* self, f32 dt)
{
    Camera* cam = self->owner;
    PlacedObject* frame = (PlacedObject*)cam->stack[0].target;
    Mat02 basis = RotateRows(frame->m110, *(Mat02*)&self->frame20);
    Vec02 rv;
    Vec02 eye;
    Vec02 target;
    Vec02 k;
    Vu0::Q(k) = Vu0::FromFloat(10.0f);
    Vu0::Q(eye) = Vu0::MulAddX(Vu0::Q(frame->v140), Vu0::Q(basis.r[0]), Vu0::Q(k));
    Vu0::Q(rv) = Vu0::Rotate(frame->m110, Vu0::Q(*(Vec02*)((u8*)self + 0x10)));
    Vu0::Q(eye) = Vu0::Add(Vu0::Q(eye), Vu0::Q(rv));
    Vu0::Q(target) = Vu0::Add(Vu0::Q(frame->v140), Vu0::Q(rv));
    f32 d = g_gameTime[0] - cam->f364;
    f32 t = d;
    if (d < 0.0f) {
        t = 0.0f;
    } else if (1.0f < d) {
        t = 1.0f;
    }
    f32 u = 1.0f - t;
    func_00144BE8(cam, 1, &target, (s32)&eye, 0, t * 100.0f + u * 20.0f, t * -15.0f + u * -7.0f, t * 0.25f + u, 0.0f, 0.0f, dt);
}
