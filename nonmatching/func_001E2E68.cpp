// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 546/564 (96.8%), checked 2026-11-07
// NEAR: identical but for the names of two registers: retail loads self+0x10 into $f3 and self+0x14 into $f2 (the squares, the scale, the stores and the arguments of ComputePolarOffset follow), ours the other way round; and the store of 0 at +0x28 comes before the store at +0x40 here, after it in retail. Declaring the two values first, in either order, or swapping the terms of the sum moves them without making the pair match.
#include "common.h"
#include "on_off_object.h"
#include "camera_controller.h"
#include "camera.h"
#include "globals.h"
#include "fpu.h"
#include "vu0.h"

struct FacePoint { s32 v[4]; };
struct CameraPlacement { Vec02 q[5]; };
struct OnOffCameraView {
    u8 pad00[0x0C];
    f32 f0C;
    f32 f10;
    f32 f14;
    u8 pad18[0x20 - 0x18];
    s32 f20;
    s32 active24;
    s32 f28;
    u8 pad2C[0x30 - 0x2C];
    f32 f30;
    u8 pad34[0x40 - 0x34];
    f32 f40;
    u8 pad44[0x50 - 0x44];
    Vec02 v50;
    f32 f60;
};
struct OnOffEventObject { u8 pad[0x434]; s32 f434; f32 f438; f32 f43C; };
typedef void (*OnOffPoseFn)(Arr63* obj, Vec02* out, s32 a, s32 b, s32 c, s32 d, f32* angle);
void ConvertOffsetToCylindrical(void* camera, Vec02* point, f32* a, f32* b, f32* c);
void ComputePolarOffset(Vec02* out, f32 a, f32 b, f32 c);
void RequestCameraSnap(Camera* camera, s32 mode);
void func_00145610(Camera* camera, Vec02* point, f32 a, f32 b);
void* GetOnOffObjectBlock(void* self);
void func_001E30E8(OnOffCameraController* self, CameraPlacement* eye);
void func_00143418(Camera* camera, s32 target, CameraPlacement* out, f32 t);

void TransformPointBetweenFrames(void* a0, OnOffObject* a1, void* a2, FacePoint* a3);
extern f32 g_gameClock[];
void BlendOnOffCameraPoint(void* block, CameraPlacement* eye, Vec02* out, OnOffObject* object);

void func_001E2E68(OnOffCameraController* self, OnOffObject* object)
{
    OnOffCameraView* view = (OnOffCameraView*)self;
    CameraPlacement place;
    Vec02 blended;
    Vec02 here;
    Vec02 sum;
    Vec02 polar;
    Camera* cam = self->owner;
    self->active24 = 1;
    self->ptr = object;
    s32 target = *(s32*)((u8*)cam + 0x3DC);
    void* block = GetOnOffObjectBlock(object);
    func_00143418(cam, target, &place, 0.0f);
    BlendOnOffCameraPoint(block, &place, &blended, 0);
    if (object != 0) {
        if (object->obj != 0) {
            TransformPointBetweenFrames(0, object, &blended, (FacePoint*)&here);
            OnOffPoseFn fn = *(OnOffPoseFn*)(*(u8**)object->obj + 0x28);
            if (fn != 0) {
                fn(object->obj, &here, 0, 0, 0, 0, &object->angle3A0);
            }
        } else if (object->f38C != 0) {
            func_001E30E8(self, &place);
        }
        BlendOnOffCameraPoint(block, &place, &blended, object);
    }
    Vu0::Q(sum) = Vu0::Add(Vu0::Q(blended), Vu0::Q(*(Vec02*)((u8*)g_camera + 0x270)));
    ConvertOffsetToCylindrical((u8*)cam + 0x40, &sum, &view->f0C, &view->f10, &view->f14);
    f32 reach = Fpu::Sqrt(view->f10 * view->f10 + view->f14 * view->f14);
    f32 scale = (reach - *(f32*)((u8*)cam + 0x1E4)) / reach;
    f32 radial = view->f14 * scale;
    f32 lateral = view->f10 * scale;
    view->f14 = radial;
    view->f10 = lateral;
    ComputePolarOffset(&polar, view->f0C, lateral, radial);
    Vu0::Q(view->v50) = Vu0::Add(Vu0::Q(sum), Vu0::Q(polar));
    view->f20 = 0;
    if (object != 0 && ((OnOffEventObject*)object)->f434 != 0) {
        RequestCameraSnap(cam, 0);
    }
    view->f60 = g_gameClock[1];
    view->f40 = g_gameClock[1];
    view->f28 = 0;
    view->f30 = g_gameClock[1] - 10.0f;
    if (object != 0) {
        f32 fov = ((OnOffEventObject*)object)->f438;
        if (fov != 0.0f) {
            ((OnOffEventObject*)object)->f43C = g_camera->f1C8;
            g_camera->f1C8 = fov;
        }
    }
    func_00145610(cam, &sum, *(f32*)((u8*)block + 0x58), *(f32*)((u8*)block + 0x5C));
}
