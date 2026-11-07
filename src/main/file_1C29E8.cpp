// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "v24a0.h"
#include "globals.h"
#include "shapes.h"
#include "vertex_batch.h"
#include "s1eb050.h"
#include "game_clock.h"

struct Obj_1C29E8 { u8 pad[8]; s32 f8; s32 fC; };

struct Elem_1C30E8 { f32 f0; f32 f4; u8 pad8[8]; f32 v10[4]; f32 v20[4]; };
struct Poly_1C30E8 {
    f32 c[3];
    f32 Eval(f32 t) { return c[0] + t * (c[1] + t * c[2]); }
};
struct Range_1C30E8 {
    f32 lo;
    f32 hi;
    f32 Clamp(f32 v)
    {
        f32 l = lo;
        f32 h = hi;
        if (v < l)
            v = l;
        else if (h < v)
            v = h;
        return v;
    }
};
struct Rec_1C30E8 {
    struct Obj_1C30E8* f0;
    s32 f4;
    s32 f8;
    s32 fC;
    f32 f10;
    u8 pad14[0x3C];
    Poly_1C30E8 poly;
    u8 pad5C[4];
    Elem_1C30E8 elems[1];
};
struct Obj_1C30E8 {
    u8 pad0[0x50];
    f32 f50;
    u8 pad54[0xC];
    Rec_1C30E8* f60;
};
struct Obj2_1C30E8 { u8 pad0[0x2A8]; f32 f2A8; };

void* func_001619C0(VertexBatch* b);
void func_00152B38(V24A0* g);
void func_00161AB0(VertexBatch* b, u8* a, u8* c);
void func_00161BB0(VertexBatch* b, s32 v);
void func_00161B10(VertexBatch* b, u8* a, f32 f);
void func_001626C0(VertexBatch* b, u8* src);
void func_001626A8(VertexBatch* b, Rgba4* c);
void func_00162680(VertexBatch* b, void* v);
void func_001626D8(VertexBatch* b, s32 z);
void func_00162508(VertexBatch* b);
void func_00152D70(V24A0* g);
void func_00161A88(VertexBatch* b, s32 f);

u8 D_00274998[8] = { 0, 0, 0, 0, 0, 0, 0x80, 0x3F };
u8 D_002749A0[16] = { 0 };

void func_001C29E8(Obj_1C29E8* o);
void func_001C30E8(Obj_1C30E8* self);

void func_001C29E8(Obj_1C29E8* o)
{
    o->fC = 0;
    o->f8 = 0;
}

ASM_FUNC(func_001C29F8);

ASM_FUNC(func_001C3028);

void func_001C30E8(Obj_1C30E8* self)
{
    VertexBatch b;
    Rgba4 c;
    Rgba4 c2;
    Rec_1C30E8* r = self->f60;
    s32 none = -1;
    s32 best = none;
    u32 size = sizeof(Elem_1C30E8);
    u32 idx;
    InitVertexBatch(&b);
    *(u32*)&c = 0xFFFFFFFF;
    BeginDmaTag(&g_vifPacketWriter);
    b.f98 = 0;
    SetVertexBatchTransform(&b, ((u8*)&D_00248D30), (u8*)&g_identityMatrix);
    SetVertexBatchMode(&b, r->f4);
    func_00161B10(&b, ((u8*)&D_00248D30), ((Obj2_1C30E8*)r->f0)->f2A8);
    idx = r->f8;
    if (idx != r->fC) {
        do {
            f32 zero = 0.0f;
            f32 full = 255.0f;
            Elem_1C30E8* e = (Elem_1C30E8*)((u8*)r->elems + idx * size);
            f32 t = g_gameClock.time - e->f0;
            f32 v = (*(Range_1C30E8*)&g_unitRange).Clamp(r->poly.Eval(t));
            f32 w = self->f50 * e->f4 * v;
            if (zero < w) {
                w = w * full;
                if (best <= none)
                    best = idx;
                c.a = (s32)w;
            } else {
                c.a = 0;
            }
            SetVertexTexCoord(&b, D_00274998);
            idx++;
            c2 = c;
            SetVertexColor(&b, &c2);
            SetVertexPosition(&b, e->v10);
            AddVertex(&b, 0);
            c.a = (s32)((f32)c.a * r->f10);
            SetVertexTexCoord(&b, D_002749A0);
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
