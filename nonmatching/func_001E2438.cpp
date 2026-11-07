// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 244/232, checked 2026-11-07
// NEAR: identical but for the address of the poly block: the blend zeroes a 0x30-byte block with func_001F5C0C (memset) and hands it to the orbit function, and retail forms its address again (addiu a0,sp,16 and addiu a2,sp,16); ours keeps it in a callee-saved register (addiu s0,sp,16) across the calls, which costs a fourth saved register (frame 160 instead of 144). The same happens with m = {}, a float array and FillMemory(&m). The weights and the blend are right (MulXSum of two Scalars).
#include "common.h"
#include "on_off_object.h"
#include "globals.h"
#include "vu0.h"

extern f32 D_002759C0[];
// The five quadwords func_00143418 gives for a camera and its target: the placement.
struct CameraPlacement { Vec02 q[5]; };
void PlaceOnOffCameraFrame(OnOffObject* object, Vec02* eye, Vec02* x, Vec02* dir);
void PlaceOnOffCameraOrbit(f32 angle, f32 offset, OnOffObject* self, f32* x, f32* poly, f32* range, s32 mode, Vec02* out);

void BlendOnOffCameraPoint(void* block, CameraPlacement* eye, Vec02* out, OnOffObject* object)
{
    f32 t = *(f32*)((u8*)block + 0x60);
    Vu0::Q(*out) = Vu0::MulXSum(Vu0::Q(eye->q[1]), Vu0::Scalar(1.0f - t), Vu0::Q(eye->q[4]), Vu0::Scalar(t));
    if (object != 0) {
        Vec02 x;
        f32 poly[12] = {};
        Vec02 dir;
        poly[1] = *(f32*)((u8*)block + 0x70);
        poly[5] = *(f32*)((u8*)block + 0x74);
        poly[9] = *(f32*)((u8*)block + 0x78);
        s32 saved = object->f380;
        object->f380 = 0;
        PlaceOnOffCameraFrame(object, out, &x, &dir);
        PlaceOnOffCameraOrbit(object->angle3A0, 0.0f, object, (f32*)&x, poly, D_002759C0, 1, out);
        object->f380 = saved;
    }
}
