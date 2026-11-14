// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the arc's fields and the caption box's state 0x310 further on, and the screen 234.3 rows
// high where US has 246.4 (the unprojection's vertical scale).
struct Cap_eu_1E7C60 { u8 pad[0x570]; s32 state; };

struct Arc_eu_1E7C60 {
    u8 pad000[0x524];
    s32 index;              // 0x524
    u8 pad528[0x52C - 0x528];
    f32 x;                  // 0x52C
    f32 y;                  // 0x530
    u8 pad534[0x544 - 0x534];
    f32 w;                  // 0x544
    f32 h;                  // 0x548
    u8 pad54C[0x570 - 0x54C];
    s32 fade;               // 0x570
    u8 pad574[0x578 - 0x574];
    s32 phase;              // 0x578
    u8 pad57C[0x584 - 0x57C];
    void* current;          // 0x584
    void* special;          // 0x588
    void* sprite;           // 0x58C
};

struct ArcQueueRequest_eu_1E7C60 {
    void (*fn)(ArcDrawRequest* request); // 0x00
    s32 f04;                // 0x04
    s32 count;              // 0x08
    u8 pad0C[0x60 - 0x0C];
    Arc_eu_1E7C60* arc;     // 0x60
    u8 pad64[0x80 - 0x64];
};

void GetArcVisibleRange(Arc_eu_1E7C60* self, s32* first, s32* second);

static inline void ClearArcQueueRequest(ArcQueueRequest_eu_1E7C60* request)
{
    FillMemory(request, 0, sizeof(*request));
}

void QueueArcDraw(Arc_eu_1E7C60* self)
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

    if (((Cap_eu_1E7C60*)&g_typedTextCaptionBox)->state == 4) {
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
    if (((Cap_eu_1E7C60*)&g_typedTextCaptionBox)->state != 4) {
        zoom = g_camera->zoom;
        zoomY = g_camera->zoomGoal;
        SnapCameraZoom(g_camera, ((ArcHeld*)self->current)->zoom);
    }
    {
        ArcHeld* held = (ArcHeld*)self->current;
        f32 sx = ((1.0f - held->u) * self->x + held->u * (self->x + self->w)) * 0.003125f - 1.0f;
        f32 sy = 1.0f - ((1.0f - held->v) * self->y + held->v * (self->y + self->h)) * 0.00426793983f;
        Vu0::Q(screen) = Vu0::FromFloats(sx, sy, held->depth);
        UnprojectCameraPoint(g_camera, (f32*)&screen, &world);
    }
    {
        f32 dist = 150.0f;
        f32 height = 20.0f;
        switch (((Cap_eu_1E7C60*)&g_typedTextCaptionBox)->state) {
        case 2:
            if (self->index == 0x1A) {
                dist = __builtin_fabsf(g_padRecord.stickX) * g_padRecord.stickX * 150.0f + dist;
                height = __builtin_fabsf(g_padRecord.stickY) * g_padRecord.stickY * 150.0f + height;
            } else {
                dist = __builtin_fabsf(g_padRecord.secondStickX) * g_padRecord.secondStickX * -150.0f + dist;
                height = __builtin_fabsf(g_padRecord.secondStickY) * g_padRecord.secondStickY * 150.0f + height;
            }
        case 3: {
            Camera* cam;
            if (self->index == 0x1A) {
                dist = -dist;
            }
            cam = g_camera;
            Vu0::Q(aim) = Vu0::Add(Vu0::Vec::Of(cam->position).q, Vu0::MulX(Vu0::Q(cam->fA0), Vu0::Scalar(height)));
            Vu0::Q(aim) = Vu0::Add(Vu0::Q(aim), Vu0::MulX(Vu0::Q(cam->f90), Vu0::Scalar(dist)));
            Vu0::Q(dir) = Vu0::Sub(Vu0::Q(aim), Vu0::Q(world));
            BuildBasisFromXAndZHint(&dir, (const Vec02*)&cam->fA0, &basis);
            BuildMatrixFromRotationAndTranslation(&world, &basis, (Mat4A*)&place);
            Vec02 pos;
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
            BuildMatrixFromRotationAndTranslation(&special->v140, &special->m110, (Mat4A*)&place);
            TransformPointBetweenFrames((PlacedObject*)self->special, 0, &((ArcHeld*)self->current)->point, &pos);
            ((PlacedObject*)self->sprite)->desc02()->m1D((PlacedObject*)self->sprite, &pos);
            break;
        }
        }
    }
    if (((Cap_eu_1E7C60*)&g_typedTextCaptionBox)->state != 4) {
        ArcQueueRequest_eu_1E7C60 request;
        ClearArcQueueRequest(&request);
        request.count = 2;
        request.fn = DrawArcOutlinePacket;
        request.arc = self;
        QueueDeferredRequest((DeferredRequest*)&request);
    }
    ((ArcHeld*)self->current)->flags &= ~((u64)1 << 32);
    place.scaleX = place.scaleY = 1.0f;
    ((ArcHeld*)self->current)->desc02()->m24((ArcHeld*)self->current, g_camera, &place);
    ((ArcHeld*)self->current)->flags |= (u64)0x8000 << 17;
    if (((Cap_eu_1E7C60*)&g_typedTextCaptionBox)->state != 4) {
        ArcQueueRequest_eu_1E7C60 request;
        ClearArcQueueRequest(&request);
        request.count = 2;
        request.fn = DrawArcTickPacket;
        request.arc = self;
        QueueDeferredRequest((DeferredRequest*)&request);
    }
done:
    if (((Cap_eu_1E7C60*)&g_typedTextCaptionBox)->state != 4) {
        SnapCameraZoom(g_camera, zoom);
        g_camera->zoomGoal = zoomY;
    }
}
