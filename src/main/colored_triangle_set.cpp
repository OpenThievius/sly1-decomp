// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x17FE00 to 0x180EB0: two methods of the point object (class 0x80) and the
// colored triangle set (class 0x8E, include/colored_triangle_set.h) with its drawing. Its name is
// ours, after the class that holds most of its code.
#include "common.h"
#include "asm_func.h"
#include "point_object.h"
#include "colored_triangle_set.h"
#include "camera.h"



void func_00182C18(void* self);



// Built at startup: the compiler's initialiser and constructor for this file are func_00180E38
// and func_00180E90 (config/us/generated.tsv).
struct Clr_180E38 {
    u8 r, g, b, a;
    Clr_180E38(u8 r_, u8 g_, u8 b_, u8 a_) : r(r_), g(g_), b(b_), a(a_) {}
};
Clr_180E38 D_00264098(0xBF, 0xBF, 0xBF, 0x7F);
Clr_180E38 D_002640A0(0x00, 0x87, 0xFF, 0x7F);
void* D_002640A4;

void func_001830D8(void* self);



void func_00182C58(void* self);
s32 func_0015A418(void* ref, s32 mode, s32 key, void* self);



// NEAR: only li s8,12 / ori s7 (pre-loop hoist order) swapped; the rest matches

void func_0011EC40(BaseObject* o, Stream8E* r);
s32 func_00137BE0(Stream8E* r);
f32 func_00137DF8(Stream8E* r);
TrianglePoint* func_0018D5C0(s32 bytes);
TriangleIndices* func_0018D500(s32 bytes);
TriangleColor* func_001B4688(s32 key);









typedef int V128_180108 __attribute__((mode(TI)));

struct Pkt_180108 {
    u8 pad[1];
};

struct Mesh_180108 {
    s32 count;
    s32 pad4;
};

struct Group_180108 {
    s32 pad0;
    s32 n;
    Mesh_180108* tris;
};

struct Obj_180108 {
    u8 pad00[0x38];
    V128_180108* verts;
    u8 pad3C[0x28];
    Group_180108 groups[5];
};

struct Col_180108 {
    u8 r, g, b, a;
};

union Q_180108 {
    V128_180108 v;
    f32 f[4];
};

extern Pkt_180108 D_00262280;

void func_0018A008(s32 zero, void* out, f32 v);
void func_001613C0(Pkt_180108* p, s32 a, s32 b, u64 c);
void func_00161708(Pkt_180108* p, s32 a, u64 v);
void func_00161458(Pkt_180108* p, u32 c);
void func_001615F0(Pkt_180108* p, s32 a, s32 b, s32 c, s32 d);
V128_180108 func_00188740(void* m, V128_180108 v);

void func_00180108(Obj_180108* self, f32 a, f32 b, f32 c, f32 d);

void func_0017FE00(C80* self)
{
    KeptBits tmp = self->keep;
    CopyObjectData(self);
    self->keep = tmp;
}

void func_0017FE48(C80* self)
{
    StartObject(self);
    if (self->targetId != -1) {
        self->target = FindFirstObjectById(self->world, 0x104, self->targetId, self);
    }
}

void func_0017FE90(ColoredTriangleSet* self)
{
    InitObject(self);
    g_coloredTriangleSet = self;
}

void func_0017FEC0(ColoredTriangleSet* self, Stream8E* rd)
{
    s32 i;
    s32 m;
    s32 j;
    s32 k;

    ReadPropertyRecords(self, rd);
    self->pointCount = ReadBufferedU16(rd);
    self->points = AllocateZeroedFrontMemory(self->pointCount << 4);
    for (i = 0; i < self->pointCount; i++) {
        self->points[i].x = ReadBufferedFloat(rd);
        self->points[i].y = -ReadBufferedFloat(rd);
        self->points[i].w = 1.0f;
    }
    self->minX = ReadBufferedFloat(rd);
    self->minY = ReadBufferedFloat(rd);
    self->f4C = 1.0f;
    self->maxX = ReadBufferedFloat(rd);
    self->maxY = ReadBufferedFloat(rd);
    self->width = self->maxX - self->minX;
    self->f5C = 1.0f;
    m = 0;
    for (; m < 5; m++) {
        TriangleColor* p = FindAnimRecord(m + 0x48E);
        TriangleList* r = &self->lists[m];
        if (p != 0) {
            r->col = p[1];
            for (k = 0; k < 4; k++) {
                r->col.c[k] = (r->col.c[k] + 1) >> 1;
            }
        } else {
            TriangleColor d;
            *(u32*)&d = 0x80808080;
            r->col = d;
        }
        r->count = ReadBufferedU16(rd);
        r->triangles = AllocateFrontMemory(r->count * 12);
        for (j = 0; j < r->count; j++) {
            TriangleIndices* e = &r->triangles[j];
            e->a = ReadBufferedU16(rd);
            e->b = ReadBufferedU16(rd);
            e->c = ReadBufferedU16(rd);
        }
    }
}

void func_00180108(Obj_180108* self, f32 a, f32 b, f32 c, f32 d)
{
    f32 sp[16];
    Col_180108 col;
    Q_180108 vv, q;
    s32 g;
    BuildUniformScaleAboutPoint(0, sp, c);
    sp[12] = a;
    sp[13] = b;
    BeginGifTag(&g_gsPacketWriter, 0, 1, 0xE);
    AddGifRegisterWrite(&g_gsPacketWriter, 0x47, 0x31001);
    AddGifRegisterWrite(&g_gsPacketWriter, 0x42, 0x44);
    for (g = 4; g > 0; g--) {
        Group_180108* grp = &self->groups[g];
        if (grp->n > 0) {
            BeginGifTag(&g_gsPacketWriter, 0, 1, 1);
            col = *(Col_180108*)((u32)(g - 3) < 2 ? &g_triangleGroupGrey : &g_triangleGroupBlue);
            col.a = (u8)(s32)((f32)col.a * d);
            AddGifRgbaEntry(&g_gsPacketWriter, *(u32*)&col);
            BeginGifTag(&g_gsPacketWriter, (s8)col.a >= 0 ? 0x43 : 0x83, 1, 4);
            {
                s32 i;
                for (i = 0; i < grp->n; i++) {
                    u32* idx = (u32*)((u8*)grp->tris + i * 12);
                    s32 j;
                    for (j = 2; j >= 0; j--) {
                        vv.v = self->verts[*idx++];
                        q.v = TransformVector4(sp, vv.v);
                        AddGifXyzfEntry(&g_gsPacketWriter, (s32)((q.f[0] + 1728.0f) * 16.0f), (s32)((q.f[1] * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
                    }
                }
            }
        }
    }
}

struct Obj_180398;
struct Desc_180398 {
    u8 pad00[0x144];
    s32 (*m144)(Obj_180398* self);
    u8 pad148[0x15C - 0x148];
    Obj_180398* (*m15C)(Obj_180398* self);
};
struct Obj_180398 {
    const Desc_180398* desc;
    u8 pad04[0x140 - 0x04];
    u8 pos[0x10];
};
struct Vec_180398 {
    f32 x, y, z, w;
};
struct Num_180398 {
    static f32 Clamp(f32 v, f32 lo, f32 hi)
    {
        return v < lo ? lo : (hi < v ? hi : v);
    }
};
struct Col_180398 {
    u8 c[4];
    // One channel moved from a to b by t, rounding up towards b.
    static s32 Mix(s32 a, s32 b, f32 t)
    {
        if (a == b) return b;
        if (a < b) return a + (s32)(t * ((f32)b + 0.999f - (f32)a));
        return b + (s32)((1.0f - t) * ((f32)a + 0.999f - (f32)b));
    }
    // This colour set to a moved towards b by t.
    void Blend(const Col_180398& a, const Col_180398& b, f32 t)
    {
        Col_180398 r;
        r.c[0] = Mix(a.c[0], b.c[0], t);
        r.c[1] = Mix(a.c[1], b.c[1], t);
        r.c[2] = Mix(a.c[2], b.c[2], t);
        r.c[3] = Mix(a.c[3], b.c[3], t);
        *this = r;
    }
};

Obj_180398* func_001925F0(void);
extern Camera* D_00261990;
void func_001441C0(Camera* cam, void* pos, Vec_180398* out);

void func_00180398(ColoredTriangleSet* self, f32 t)
{
    f32 mat[16];
    Obj_180398* o;

    BuildUniformScaleAboutPoint(0, mat, (1.0f - t) * (1280.0f / self->width) + t * (4.0f / self->width));
    o = GetActiveSwitchedCollider();
    if (o != 0 && (o = o->desc->m15C(o)) != 0 && o->desc->m144(o) == 2) {
        Vec_180398 v;
        f32 x, y;
        func_001441C0(g_camera, o->pos, &v);
        x = Num_180398::Clamp(v.x * 320.0f + 320.0f, 10.0f, 630.0f);
        mat[12] = (1.0f - t) * 320.0f + t * x;
        y = Num_180398::Clamp(v.y * -246.40001f + 246.40001f, 16.0f, 476.80002f);
        mat[13] = (1.0f - t) * 246.40001f + t * y;
    } else {
        mat[12] = 320.0f;
        mat[13] = 246.40001f;
    }
    {
        Col_180398 base;
        s32 g;
        s32 vis;
        BeginGifTag(&g_gsPacketWriter, 0, 1, 0xE);
        AddGifRegisterWrite(&g_gsPacketWriter, 0x47, 0x31001);
        AddGifRegisterWrite(&g_gsPacketWriter, 0x42, 0x44);
        vis = 0;
        for (g = 4; g >= 0; g--) {
            TriangleList* r = &self->lists[g];
            Col_180398 col = *(Col_180398*)&r->col;
            if (g == 0) {
                Col_180398 mixed;
                Col_180398 from = *(Col_180398*)&r->col;
                Col_180398 black;
                *(u32*)&black = 0x80000000;
                mixed.Blend(from, black, t);
                col = mixed;
            }
            if (t <= 0.4f) {
                col.c[3] = (s32)((f32)col.c[3] * t * 2.5f);
            }
            if (g == 0) {
                base = col;
            }
            if (r->count > 0) {
                s32 i;
                BeginGifTag(&g_gsPacketWriter, 0, 1, 1);
                AddGifRgbaEntry(&g_gsPacketWriter, *(u32*)&col);
                BeginGifTag(&g_gsPacketWriter, (s8)col.c[3] >= 0 ? 0x43 : 0x83, 1, 4);
                for (i = 0; i < r->count; i++) {
                    u32* idx = (u32*)&r->triangles[i];
                    s32 j;
                    for (j = 2; j >= 0; j--, idx++) {
                        Q_180108 p, q;
                        p.v = *(V128_180108*)&self->points[*idx];
                        q.v = TransformVector4(mat, p.v);
                        AddGifXyzfEntry(&g_gsPacketWriter, (s32)((q.f[0] + 1728.0f) * 16.0f), (s32)((q.f[1] * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
                        vis = vis || 0.0f < q.f[0] || q.f[0] < 640.0f || 0.0f < q.f[1] || q.f[1] < 492.80002f;
                    }
                }
            }
        }
        if (vis) {
            Q_180108 lo, hi;
            f32 d;
            lo.v = TransformVector4(mat, *(V128_180108*)&self->minX);
            hi.v = TransformVector4(mat, *(V128_180108*)&self->maxX);
            BeginGifTag(&g_gsPacketWriter, (s8)base.c[3] >= 0 ? 0x44 : 0x84, 0xB, 0x44444444441ULL);
            AddGifRgbaEntry(&g_gsPacketWriter, *(u32*)&base);
            AddGifXyzfEntry(&g_gsPacketWriter, 0x6C00, 0x7900, 0, 0);
            AddGifXyzfEntry(&g_gsPacketWriter, (s32)((lo.f[0] + 1728.0f) * 16.0f), (s32)((lo.f[1] * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
            AddGifXyzfEntry(&g_gsPacketWriter, 0x9400, 0x7900, 0, 0);
            AddGifXyzfEntry(&g_gsPacketWriter, (s32)((hi.f[0] + 1728.0f) * 16.0f), (s32)((lo.f[1] * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
            AddGifXyzfEntry(&g_gsPacketWriter, 0x9400, 0x8700, 0, 0);
            AddGifXyzfEntry(&g_gsPacketWriter, (s32)((hi.f[0] + 1728.0f) * 16.0f), (s32)((hi.f[1] * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
            AddGifXyzfEntry(&g_gsPacketWriter, 0x6C00, 0x8700, 0, 0);
            AddGifXyzfEntry(&g_gsPacketWriter, (s32)((lo.f[0] + 1728.0f) * 16.0f), (s32)((hi.f[1] * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
            AddGifXyzfEntry(&g_gsPacketWriter, 0x6C00, 0x7900, 0, 0);
            AddGifXyzfEntry(&g_gsPacketWriter, (s32)((lo.f[0] + 1728.0f) * 16.0f), (s32)((lo.f[1] * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
            d = 1.0f - t;
            if (d <= 0.1f) {
                Col_180398 fade = base;
                fade.c[3] = (s32)((f32)fade.c[3] * (1.0f - d * 10.0f));
                BeginGifTag(&g_gsPacketWriter, 0x44, 5, 0x44441);
                AddGifRgbaEntry(&g_gsPacketWriter, *(u32*)&fade);
                AddGifXyzfEntry(&g_gsPacketWriter, (s32)((lo.f[0] + 1728.0f) * 16.0f), (s32)((lo.f[1] * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
                AddGifXyzfEntry(&g_gsPacketWriter, (s32)((hi.f[0] + 1728.0f) * 16.0f), (s32)((lo.f[1] * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
                AddGifXyzfEntry(&g_gsPacketWriter, (s32)((lo.f[0] + 1728.0f) * 16.0f), (s32)((hi.f[1] * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
                AddGifXyzfEntry(&g_gsPacketWriter, (s32)((hi.f[0] + 1728.0f) * 16.0f), (s32)((hi.f[1] * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
            }
        }
    }
}
