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

// A point of the ring: the time it was added, its alpha, and the ribbon's two edges.
struct TrailPoint { f32 f0; f32 f4; u8 pad8[8]; f32 v10[4]; f32 v20[4]; };
// The ring of up to 0x40 points a trail keeps: the placed object it follows (its 0x2A8 is read),
// the oldest live one at +0x08, the next free at +0x0C (ResetTrailRing empties it), an alpha
// curve over age at +0x50.
struct TrailRing {
    PlacedObject* f0;
    s32 f4;
    s32 f8;
    s32 fC;
    f32 f10;
    f32 f14;                // 0x14: when above 0, the two edges are pushed apart along the camera's 0xA0
    s32 f18;                // 0x18: the edges in use (1 or 2)
    u8 pad1C[4];
    Vec02 f20[2];           // 0x20: the edges' offsets in the object's frame
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
    f32 f50;
    u8 pad54[0xC];
    TrailRing* f60;
};

void* InitVertexBatch(VertexBatch* b);
void BeginDmaTag(PacketWriter* g);
void SetVertexBatchTransform(VertexBatch* b, u8* a, u8* c);
void SetVertexBatchMode(VertexBatch* b, s32 v);
void SelectVertexBatchLights(VertexBatch* b, u8* a, f32 f);
void SetVertexTexCoord(VertexBatch* b, u8* src);
void SetVertexColor(VertexBatch* b, Rgba4* c);
void SetVertexPosition(VertexBatch* b, void* v);
void AddVertex(VertexBatch* b, s32 z);
void FlushVertexBatch(VertexBatch* b);
void CloseDmaTag(PacketWriter* g);
void DestroyVertexBatch(VertexBatch* b, s32 f);

u8 g_trailEdgeTexCoord[8] = { 0, 0, 0, 0, 0, 0, 0x80, 0x3F };
u8 g_trailZeroTexCoord[16] = { 0 };

void ResetTrailRing(TrailRing* o);
void DrawTrailRibbon(TrailOwner* self);

void ResetTrailRing(TrailRing* o)
{
    o->fC = 0;
    o->f8 = 0;
}

void ComputeObjectMotionInFrame(void* obj, PlacedObject* top, void* point, Vec02* out, s32 a, s32 b, s32 c);
void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void MatrixToAxisAngle(Mat02* m, f32* angle, Vec02* axis);
void BuildAxisAngleMatrix(Vec02* axis, Mat02* out, f32 angle);

// A point's frame as func_001C29F8 steps it from the last placement to the new one.
struct TrailFrame { Mat02 rot; Vec02 pos; };

static inline f32 MaxF(f32 a, f32 b) { return b >? a; }

void func_001C29F8(TrailRing* self, Vec02* pos, Mat02* mat, s32 flag, f32 scale, f32 dt)
{
    Vec02 pts[2];
    Vec02 motion[2];
    TrailPoint* e;
    s32 i;
    f32 speed;
    f32 alpha;
    if (self->f4 == 0 || self->f0 == 0 || dt == 0.0f)
        return;
    if (pos == 0)
        pos = &self->f0->v140;
    if (mat == 0)
        mat = &self->f0->m110;
    for (i = 0; i < self->f18; i++) {
        Vu0::Q(pts[i]) = Vu0::Rotate(*mat, Vu0::Q(self->f20[i]));
        Vu0::Q(pts[i]) = Vu0::Add(Vu0::Q(*pos), Vu0::Q(pts[i]));
        ComputeObjectMotionInFrame(self->f0, self->f0->root, &pts[i], &motion[i], 0, 0, 0);
    }
    if (self->f18 == 1) {
        f32 len = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(motion[0])));
        pts[1] = pts[0];
        speed = len;
        if (self->f14 == 0.0f)
            speed = 0.0f;
    } else {
        speed = MaxF(Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(motion[0]))), Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(motion[1]))));
    }
    if (scale != 0.0f) {
        f32 m = 0.0f;
        for (i = 0; i < self->f18; i++)
            m = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(self->f20[i]))) >? m;
        speed += scale * m;
    }
    if (flag == 0)
        alpha = g_unitRange.Clamp(self->poly40.Eval(speed));
    else
        alpha = 0.0f;
    if (alpha == 0.0f) {
        if (self->f8 == self->fC)
            goto done;
        if (self->elems[(self->fC + 0x3F) & 0x3F].f4 == 0.0f)
            goto done;
    }
    if (0.0f < self->f14) {
        f32 f = self->f14;
        Vu0::Q(pts[0]) = Vu0::MulAddX(Vu0::Q(pts[0]), Vu0::Q(g_camera->fA0), Vu0::Scalar(f));
        Vu0::Q(pts[1]) = Vu0::MulAddX(Vu0::Q(pts[1]), Vu0::Q(g_camera->fA0), Vu0::Scalar(-f));
    }
    {
        Mat02 step;
        Vec02 axis;
        f32 angle;
        MultiplyMatrices3x3(&self->mC70, mat, &step);
        MatrixToAxisAngle(&step, &angle, &axis);
        if (0.2f < __builtin_fabsf(angle) && self->f8 != self->fC) {
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
                for (i = 0; i < self->f18; i++) {
                    Vu0::Q(pts[i]) = Vu0::Rotate(cur, Vu0::Q(self->f20[i]));
                    Vu0::Q(pts[i]) = Vu0::Add(Vu0::Q(frame.pos), Vu0::Q(pts[i]));
                }
                e = &self->elems[self->fC];
                e->f0 = g_gameClock.time;
                e->f4 = alpha;
                Vu0::Q(e->v10) = Vu0::Q(pts[0]);
                Vu0::Q(e->v20) = Vu0::Q(pts[1]);
                if ((u32)++self->fC >= 0x40)
                    self->fC = 0;
                if (self->fC == self->f8) {
                    if ((u32)++self->f8 >= 0x40)
                        self->f8 = 0;
                }
            }
        } else {
            e = &self->elems[self->fC];
            e->f0 = g_gameClock.time;
            e->f4 = alpha;
            Vu0::Q(e->v10) = Vu0::Q(pts[0]);
            Vu0::Q(e->v20) = Vu0::Q(pts[1]);
            if ((u32)++self->fC >= 0x40)
                self->fC = 0;
            if (self->fC == self->f8) {
                if ((u32)++self->f8 >= 0x40)
                    self->f8 = 0;
            }
        }
    }
done:
    self->vC60 = *pos;
    self->mC70 = *mat;
}

void* FillMemory(void* p, s32 value, s32 size);
void QueueDeferredRequest(DeferredRequest* src);

void func_001C3028(TrailRing* self, u8* cam)
{
    DeferredRequest req;
    Vec02 diff;
    s32 count = self->fC - self->f8;
    if (count < 0) {
        count += 0x40;
    }
    if (count >= 2) {
        FillMemory(&req, 0, sizeof(DeferredRequest));
        req.callback = (void*)DrawTrailRibbon;
        req.group = 0xD;
        Vu0::Q(diff) = Vu0::Sub(Vu0::Q(self->f0->v140), Vu0::Q(*(Vec02*)(cam + 0x40)));
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
    TrailRing* r = self->f60;
    s32 none = -1;
    s32 best = none;
    u32 size = sizeof(TrailPoint);
    u32 idx;
    InitVertexBatch(&b);
    *(u32*)&c = 0xFFFFFFFF;
    BeginDmaTag(&g_vifPacketWriter);
    b.f98 = 0;
    SetVertexBatchTransform(&b, ((u8*)&D_00248D30), (u8*)&g_identityMatrix);
    SetVertexBatchMode(&b, r->f4);
    SelectVertexBatchLights(&b, ((u8*)&D_00248D30), r->f0->f2A8);
    idx = r->f8;
    if (idx != r->fC) {
        do {
            f32 zero = 0.0f;
            f32 full = 255.0f;
            TrailPoint* e = (TrailPoint*)((u8*)r->elems + idx * size);
            f32 t = g_gameClock.time - e->f0;
            f32 v = g_unitRange.Clamp(r->poly.Eval(t));
            f32 w = self->f50 * e->f4 * v;
            if (zero < w) {
                w = w * full;
                if (best <= none)
                    best = idx;
                c.a = (s32)w;
            } else {
                c.a = 0;
            }
            SetVertexTexCoord(&b, g_trailEdgeTexCoord);
            idx++;
            c2 = c;
            SetVertexColor(&b, &c2);
            SetVertexPosition(&b, e->v10);
            AddVertex(&b, 0);
            c.a = (s32)((f32)c.a * r->f10);
            SetVertexTexCoord(&b, g_trailZeroTexCoord);
            c2 = c;
            SetVertexColor(&b, &c2);
            SetVertexPosition(&b, e->v20);
            AddVertex(&b, 0);
            if (idx >= 0x40)
                idx = 0;
        } while (idx != r->fC);
    }
    if (best >= 0)
        r->f8 = best;
    else
        r->f8 = r->fC;
    FlushVertexBatch(&b);
    CloseDmaTag(&g_vifPacketWriter);
    DestroyVertexBatch(&b, 2);
}
