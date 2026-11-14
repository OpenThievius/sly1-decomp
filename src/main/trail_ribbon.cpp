// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "packet_writer.h"
#include "globals.h"
#include "shapes.h"
#include "vertex_batch.h"
#include "value_range.h"
#include "game_clock.h"
#include "hit_target.h"
#include "deferred_request.h"
#include "vu0.h"
#include "functions/group_marker.h"
#include "functions/matrix.h"
#include "functions/placed_object.h"
#include "functions/pooled_object.h"
#include "functions/trail_ribbon.h"
struct Mat02;
struct Vec02;


// A point of the ring: the time it was added, its alpha, and the ribbon's two edges.
struct TrailPoint { f32 time; f32 alpha; u8 pad8[8]; f32 v10[4]; f32 v20[4]; };
// The ring of up to 0x40 points a trail keeps: the placed object it follows (its 0x2A8 is read),
// the oldest live one at +0x08, the next free at +0x0C (ResetTrailRing empties it), an alpha
// curve over age at +0x50.
struct TrailRing {
    PlacedObject* target;
    u8* batchMode;          // the batch mode SetVertexBatchMode takes
    s32 oldest;
    s32 next;
    f32 edgeAlphaScale;
    f32 edgeSpread;         // 0x14: when above 0, the two edges are pushed apart along the camera's 0xA0
    s32 edgeCount;          // 0x18: the edges in use (1 or 2)
    u8 pad1C[4];
    Vec02 edgeOffsets[2];   // 0x20: the edges' offsets in the object's frame
    TimePolynomial poly40;  // 0x40: a new point's alpha over the trail's speed
    u8 pad4C[4];
    TimePolynomial poly;
    u8 pad5C[4];
    TrailPoint elems[0x40];
    Vec02 vC60;             // 0xC60: the position of the last update (func_001C29F8)
    Mat02 mC70;             // 0xC70: and its rotation
};
// The object that draws a trail: an alpha scale at +0x50 and its ring at +0x60.
struct TrailOwner {
    u8 pad0[0x50];
    f32 alphaScale;
    u8 pad54[0xC];
    TrailRing* ring;
};

void* InitVertexBatch(VertexBatch* b);
void SetVertexBatchTransform(VertexBatch* batch, void* a1, void* a2);
void SetVertexBatchMode(VertexBatch* batch, u8* value);
void SelectVertexBatchLights(VertexBatch* batch, void* center, f32 radius);
void SetVertexTexCoord(VertexBatch* dst, U64P* src);
void SetVertexColor(VertexBatch* batch, void* src);
void SetVertexPosition(VertexBatch* body, Vec3* v);
void AddVertex(VertexBatch* b, s32 z);
void FlushVertexBatch(VertexBatch* b);
void DestroyVertexBatch(VertexBatch* b, s32 f);

u8 g_trailEdgeTexCoord[8] = { 0, 0, 0, 0, 0, 0, 0x80, 0x3F };
u8 g_trailZeroTexCoord[16] = { 0 };


void ResetTrailRing(TrailRing* o)
{
    o->next = 0;
    o->oldest = 0;
}


// A point's frame as func_001C29F8 steps it from the last placement to the new one.
struct TrailFrame { Mat02 rot; Vec02 pos; };

static inline f32 MaxF(f32 a, f32 b) { return b >? a; }

void AddTrailPoint(TrailRing* self, Vec02* pos, Mat02* mat, s32 flag, f32 scale, f32 dt)
{
    Vec02 pts[2];
    Vec02 motion[2];
    TrailPoint* e;
    s32 i;
    f32 speed;
    f32 alpha;
    if (self->batchMode == 0 || self->target == 0 || dt == 0.0f)
        return;
    if (pos == 0)
        pos = &self->target->v140;
    if (mat == 0)
        mat = &self->target->m110;
    for (i = 0; i < self->edgeCount; i++) {
        Vu0::Q(pts[i]) = Vu0::Rotate(*mat, Vu0::Q(self->edgeOffsets[i]));
        Vu0::Q(pts[i]) = Vu0::Add(Vu0::Q(*pos), Vu0::Q(pts[i]));
        ComputeObjectMotionInFrame(self->target, self->target->root, &pts[i], &motion[i], 0, 0, 0);
    }
    if (self->edgeCount == 1) {
        f32 len = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(motion[0])));
        pts[1] = pts[0];
        speed = len;
        if (self->edgeSpread == 0.0f)
            speed = 0.0f;
    } else {
        speed = MaxF(Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(motion[0]))), Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(motion[1]))));
    }
    if (scale != 0.0f) {
        f32 m = 0.0f;
        for (i = 0; i < self->edgeCount; i++)
            m = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(self->edgeOffsets[i]))) >? m;
        speed += scale * m;
    }
    if (flag == 0)
        alpha = g_unitRange.Clamp(self->poly40.Eval(speed));
    else
        alpha = 0.0f;
    if (alpha == 0.0f) {
        if (self->oldest == self->next)
            goto done;
        if (self->elems[(self->next + 0x3F) & 0x3F].alpha == 0.0f)
            goto done;
    }
    if (0.0f < self->edgeSpread) {
        f32 f = self->edgeSpread;
        Vu0::Q(pts[0]) = Vu0::MulAddX(Vu0::Q(pts[0]), Vu0::Q(g_camera->fA0), Vu0::Scalar(f));
        Vu0::Q(pts[1]) = Vu0::MulAddX(Vu0::Q(pts[1]), Vu0::Q(g_camera->fA0), Vu0::Scalar(-f));
    }
    {
        Mat02 step;
        Vec02 axis;
        f32 angle;
        MultiplyMatrices3x3(&self->mC70, mat, &step);
        MatrixToAxisAngle(&step, &angle, &axis);
        if (0.2f < __builtin_fabsf(angle) && self->oldest != self->next) {
            s32 n = (s32)(__builtin_fabsf(angle) * 5.0f) + 1;
            f32 fn;
            s32 k;
            Mat02 cur = self->mC70;
            TrailFrame frame;
            Vec02 dp;
            fn = (f32)n;
            BuildAxisAngleMatrix(&axis, &step, angle / fn);
            Vu0::Q(frame.pos) = Vu0::Q(self->vC60);
            f32 ninv = -1.0f / fn;
            f32 inv = 1.0f / fn;
            u128 w = Vu0::Scalar(inv);
            u128 end = Vu0::Q(*pos);
            Vu0::Q(dp) = Vu0::MulXSum(end, w, Vu0::Q(frame.pos), Vu0::Scalar(ninv));
            for (k = 0; k < n; k++) {
                Mat02 a;
                Mat02 b;
                Vu0::Q(a.r[0]) = Vu0::Q(b.r[0]) = Vu0::RotateRows(Vu0::Q(step.r[0]), Vu0::Q(step.r[1]), Vu0::Q(step.r[2]), Vu0::Q(cur.r[0]));
                Vu0::Q(a.r[1]) = Vu0::Q(b.r[1]) = Vu0::RotateRows(Vu0::Q(step.r[0]), Vu0::Q(step.r[1]), Vu0::Q(step.r[2]), Vu0::Q(cur.r[1]));
                Vu0::Q(a.r[2]) = Vu0::Q(b.r[2]) = Vu0::RotateRows(Vu0::Q(step.r[0]), Vu0::Q(step.r[1]), Vu0::Q(step.r[2]), Vu0::Q(cur.r[2]));
                frame.rot = b;
                cur = a;
                Vu0::Q(frame.pos) = Vu0::Add(Vu0::Q(frame.pos), Vu0::Q(dp));
                for (i = 0; i < self->edgeCount; i++) {
                    Vu0::Q(pts[i]) = Vu0::Rotate(cur, Vu0::Q(self->edgeOffsets[i]));
                    Vu0::Q(pts[i]) = Vu0::Add(Vu0::Q(frame.pos), Vu0::Q(pts[i]));
                }
                e = &self->elems[self->next];
                e->time = g_gameClock.time;
                e->alpha = alpha;
                Vu0::Q(e->v10) = Vu0::Q(pts[0]);
                Vu0::Q(e->v20) = Vu0::Q(pts[1]);
                if ((u32)++self->next >= 0x40)
                    self->next = 0;
                if (self->next == self->oldest) {
                    if ((u32)++self->oldest >= 0x40)
                        self->oldest = 0;
                }
            }
        } else {
            e = &self->elems[self->next];
            e->time = g_gameClock.time;
            e->alpha = alpha;
            Vu0::Q(e->v10) = Vu0::Q(pts[0]);
            Vu0::Q(e->v20) = Vu0::Q(pts[1]);
            if ((u32)++self->next >= 0x40)
                self->next = 0;
            if (self->next == self->oldest) {
                if ((u32)++self->oldest >= 0x40)
                    self->oldest = 0;
            }
        }
    }
done:
    self->vC60 = *pos;
    self->mC70 = *mat;
}

extern "C" void* FillMemory(void* p, s32 value, s32 size);

void QueueTrailRibbonDraw(TrailRing* self, u8* cam)
{
    DeferredRequest req;
    Vec02 diff;
    s32 count = self->next - self->oldest;
    if (count < 0) {
        count += 0x40;
    }
    if (count >= 2) {
        FillMemory(&req, 0, sizeof(DeferredRequest));
        req.callback = (void*)DrawTrailRibbon;
        req.group = 0xD;
        Vu0::Q(diff) = Vu0::Sub(Vu0::Q(self->target->v140), Vu0::Q(*(Vec02*)(cam + 0x40)));
        req.f04 = Vu0::ToFloat(Vu0::Dot(Vu0::Q(diff), Vu0::Q(*(Vec02*)(cam + 0x80))));
        *(f32*)&req.block.q[4] = 1.0f;
        req.arg = self;
        QueueDeferredRequest(&req);
    }
}

void DrawTrailRibbon(TrailOwner* self)
{
    VertexBatch b;
    Rgba4 c;
    Rgba4 c2;
    TrailRing* r = self->ring;
    s32 none = -1;
    s32 best = none;
    u32 size = sizeof(TrailPoint);
    u32 idx;
    InitVertexBatch(&b);
    *(u32*)&c = 0xFFFFFFFF;
    BeginDmaTag(&g_vifPacketWriter);
    b.f98 = 0;
    SetVertexBatchTransform(&b, ((u8*)&D_00248D30), (u8*)&g_identityMatrix);
    SetVertexBatchMode(&b, r->batchMode);
    SelectVertexBatchLights(&b, ((u8*)&D_00248D30), r->target->boundRadius);
    idx = r->oldest;
    if (idx != r->next) {
        do {
            f32 zero = 0.0f;
            f32 full = 255.0f;
            TrailPoint* e = (TrailPoint*)((u8*)r->elems + idx * size);
            f32 t = g_gameClock.time - e->time;
            f32 v = g_unitRange.Clamp(r->poly.Eval(t));
            f32 w = self->alphaScale * e->alpha * v;
            if (zero < w) {
                w = w * full;
                if (best <= none)
                    best = idx;
                c.a = (s32)w;
            } else {
                c.a = 0;
            }
            SetVertexTexCoord(&b, (U64P*)g_trailEdgeTexCoord);
            idx++;
            c2 = c;
            SetVertexColor(&b, &c2);
            SetVertexPosition(&b, (Vec3*)e->v10);
            AddVertex(&b, 0);
            c.a = (s32)((f32)c.a * r->edgeAlphaScale);
            SetVertexTexCoord(&b, (U64P*)g_trailZeroTexCoord);
            c2 = c;
            SetVertexColor(&b, &c2);
            SetVertexPosition(&b, (Vec3*)e->v20);
            AddVertex(&b, 0);
            if (idx >= 0x40)
                idx = 0;
        } while (idx != r->next);
    }
    if (best >= 0)
        r->oldest = best;
    else
        r->oldest = r->next;
    FlushVertexBatch(&b);
    CloseDmaTag(&g_vifPacketWriter);
    DestroyVertexBatch(&b, 2);
}
