// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 1160/1144, checked 2026-11-08
// NEAR (src/main/file_1E5378.cpp, where it is INCLUDE_ASM; 2026-11-08, night-untouched): the
// arc's frame (the caption box's state test, the held object's screen point unprojected, the
// stick's height and distance in state 2 falling into state 3's placement, state 4's special
// object, the two queued draws and the zoom restored) is retail's code, 16 bytes longer. Left:
// the frame. Retail's weights, the FromFloats slot and the position all share 0xC0, the outline's
// request sits at 0xD0 and the ticks' at 0xC0, first and last at 0x150 (frame 0x1E0, s0-s5);
// here the slots take 0xC0 and 0xD0 apart, the requests 0xC0 and 0xE0, and sp+0xC0 is kept in a
// saved register across the calls (s6, s7 and 0x30 more frame). Tried: the position at function
// scope, the screen computation outside a block.
#include "common.h"
#include "switched_collider.h"
#include "screen_element.h"
#include "camera.h"
#include "pad_record.h"
#include "vu0.h"
#include "globals.h"

void GetArcVisibleRange(T217D_3F0* self, s32* first, s32* second);
void UnprojectCameraPoint(void* camera, void* in, void* out);
void FillMemory(void* p, s32 v, s32 n);

s32 AreArcMenusClosed(void);
extern PadRecord g_padRecord;
void SnapCameraZoom(Camera* camera, f32 zoom);
void BuildBasisFromXAndZHint(void* x, void* hint, void* out);
void BuildMatrixFromRotationAndTranslation(void* translation, void* rotation, void* out);
void TransformPointBetweenFrames(void* from, s32 to, void* point, void* out);
void QueueDeferredRequest(void* request);
struct ArcDrawRequest;
void DrawArcOutlinePacket(ArcDrawRequest* request);
void DrawArcTickPacket(ArcDrawRequest* request);

// What an arc holds (T217D_3F0::current): the camera zoom it is seen at, where on the screen it
// stands (a depth and the fractions of the arc's box), its offset from the point found, and its
// point in the special object's frame.
struct ArcHeld : PlacedObject {
    u8 pad2D0[0x2D4 - 0x2D0];
    f32 zoom;               // 0x2D4
    f32 depth;              // 0x2D8
    f32 u;                  // 0x2DC
    f32 v;                  // 0x2E0
    u8 pad2E4[0x2F0 - 0x2E4];
    Vec02 offset;           // 0x2F0: in the camera's frame
    Vec02 point;            // 0x300: in the special object's frame
};

// A placement handed to slot 36: a matrix with its translation and a scale.
struct ArcPlacement {
    Vec02 rows[4];
    f32 scaleX;
    f32 scaleY;
};

// The request queued for each of the arc's draws: the function, its count and the arc.
struct ArcQueueRequest {
    void (*fn)(ArcDrawRequest* request); // 0x00
    s32 f04;                // 0x04
    s32 count;              // 0x08
    u8 pad0C[0x60 - 0x0C];
    T217D_3F0* arc;         // 0x60
    u8 pad64[0x80 - 0x64];
};

// The arc's frame: while the caption box is open (state 4) only a fully grown arc that is fading
// out; otherwise once the menus are closed. Its held object goes where the arc's box shows it,
// unprojected at its depth, then (state 2 and 3) 20 above and 150 out from the camera, moved by
// the stick in state 2, or (state 4) at the special object's point; it is placed there and the
// outline and the ticks are queued, the camera's zoom put back.
void func_001E7C60(T217D_3F0* self)
{
    Vec02 screen;
    Vec02 world;
    Vec02 aim;
    Vec02 dir;
    Mat02 basis;
    ArcPlacement place;
    s32 first;
    s32 last;
    f32 zoom;
    f32 zoomY;

    if (g_typedTextCaptionBox.state == 4) {
        if (self->fade != 1) {
            return;
        }
        if (self->phase != 1) {
            return;
        }
    } else if (!AreArcMenusClosed()) {
        return;
    }
    GetArcVisibleRange(self, &first, &last);
    if (first == last) {
        return;
    }
    if (g_typedTextCaptionBox.state != 4) {
        zoom = g_camera->f1C4;
        zoomY = g_camera->f1C8;
        SnapCameraZoom(g_camera, ((ArcHeld*)self->current)->zoom);
    }
    {
        ArcHeld* held = (ArcHeld*)self->current;
        f32 sx = ((1.0f - held->u) * self->x + held->u * (self->x + self->w)) * 0.003125f - 1.0f;
        f32 sy = 1.0f - ((1.0f - held->v) * self->y + held->v * (self->y + self->h)) * 0.00405844161f;
        Vu0::Q(screen) = Vu0::FromFloats(sx, sy, held->depth);
        UnprojectCameraPoint(g_camera, &screen, &world);
    }
    {
        f32 dist = 150.0f;
        f32 height = 20.0f;
        switch (g_typedTextCaptionBox.state) {
        case 2:
            if (self->index == 0x1A) {
                height = __builtin_fabsf(g_padRecord.f44) * g_padRecord.f44 * 150.0f + height;
                dist = __builtin_fabsf(g_padRecord.f40) * g_padRecord.f40 * dist + dist;
            } else {
                height = __builtin_fabsf(g_padRecord.f78) * g_padRecord.f78 * 150.0f + height;
                dist = __builtin_fabsf(g_padRecord.f74) * g_padRecord.f74 * -150.0f + dist;
            }
        case 3: {
            Vec02 pos;
            Camera* cam;
            if (self->index == 0x1A) {
                dist = -dist;
            }
            cam = g_camera;
            Vu0::Q(aim) = Vu0::Add(Vu0::Q(cam->f40), Vu0::MulX(Vu0::Q(cam->fA0), Vu0::Scalar(height)));
            Vu0::Q(aim) = Vu0::Add(Vu0::Q(aim), Vu0::MulX(Vu0::Q(cam->f90), Vu0::Scalar(dist)));
            Vu0::Q(dir) = Vu0::Sub(Vu0::Q(aim), Vu0::Q(world));
            BuildBasisFromXAndZHint(&dir, &cam->fA0, &basis);
            BuildMatrixFromRotationAndTranslation(&world, &basis, &place);
            Vu0::Q(pos) = Vu0::Add(Vu0::Q(aim), Vu0::Rotate(*(Mat02*)&g_camera->f80, Vu0::Q(((ArcHeld*)self->current)->offset)));
            ((PlacedObject*)self->sprite)->desc02()->m1D((PlacedObject*)self->sprite, &pos);
            break;
        }
        case 4: {
            PlacedObject* special = (PlacedObject*)self->special;
            Vec02 pos;
            if (special == 0) {
                goto done;
            }
            BuildMatrixFromRotationAndTranslation(&special->v140, &special->m110, &place);
            TransformPointBetweenFrames(self->special, 0, &((ArcHeld*)self->current)->point, &pos);
            ((PlacedObject*)self->sprite)->desc02()->m1D((PlacedObject*)self->sprite, &pos);
            break;
        }
        }
    }
    if (g_typedTextCaptionBox.state != 4) {
        ArcQueueRequest request;
        FillMemory(&request, 0, 0x80);
        request.count = 2;
        request.fn = DrawArcOutlinePacket;
        request.arc = self;
        QueueDeferredRequest(&request);
    }
    ((ArcHeld*)self->current)->flags &= ~((u64)1 << 32);
    place.scaleX = 1.0f;
    place.scaleY = 1.0f;
    ((ArcHeld*)self->current)->desc02()->m24((ArcHeld*)self->current, g_camera, &place);
    ((ArcHeld*)self->current)->flags |= (u64)0x8000 << 17;
    if (g_typedTextCaptionBox.state != 4) {
        ArcQueueRequest request;
        FillMemory(&request, 0, 0x80);
        request.count = 2;
        request.fn = DrawArcTickPacket;
        request.arc = self;
        QueueDeferredRequest(&request);
    }
done:
    if (g_typedTextCaptionBox.state != 4) {
        SnapCameraZoom(g_camera, zoom);
        g_camera->f1C8 = zoomY;
    }
}
