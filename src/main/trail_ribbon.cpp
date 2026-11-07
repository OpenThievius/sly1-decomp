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
    u8 pad14[0x3C];
    TimePolynomial poly;
    u8 pad5C[4];
    TrailPoint elems[1];
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

INCLUDE_ASM(func_001C29F8);

void* FillMemory(void* p, s32 v, s32 n);
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
