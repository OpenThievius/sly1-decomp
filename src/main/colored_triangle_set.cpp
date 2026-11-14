// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x17FE00 to 0x180EB0: two methods of the point object (class 0x80) and the
// colored triangle set (class 0x8E, include/colored_triangle_set.h) with its drawing. Its name is
// ours, after the class that holds most of its code.
#include "common.h"
#include "asm_func.h"
#include "point_object.h"
#include "colored_triangle_set.h"
#include "camera.h"
#include "globals.h"
#include "packet_writer.h"
#include "switched_collider.h"
#include "object_finder.h"



void InitObject(BaseObject* self);



// Built at startup: the compiler's initialiser and constructor for this file are func_00180E38
// and func_00180E90 (config/us/generated.tsv).
// The colour of a group of triangles, made by the file's static initialiser.
struct TriangleGroupColor {
    u8 r, g, b, a;
    TriangleGroupColor(u8 r_, u8 g_, u8 b_, u8 a_) : r(r_), g(g_), b(b_), a(a_) {}
};
TriangleGroupColor g_triangleGroupGrey(0xBF, 0xBF, 0xBF, 0x7F);
TriangleGroupColor g_triangleGroupBlue(0x00, 0x87, 0xFF, 0x7F);
ColoredTriangleSet* g_coloredTriangleSet;

void CopyObjectData(BaseObject* self, BaseObject* src);



void StartObject(BaseObject* self);



// NEAR: only li s8,12 / ori s7 (pre-loop hoist order) swapped; the rest matches

struct BufferedStream;
void ReadPropertyRecords(void* self, void* obj);
u16 ReadBufferedU16(BufferedStream* self);
f32 ReadBufferedFloat(BufferedStream* r);
TrianglePoint* AllocateZeroedFrontMemory(s32 bytes);
TriangleIndices* AllocateFrontMemory(s32 bytes);
TriangleColor* FindAnimRecord(s32 key);









typedef int Quad128 __attribute__((mode(TI)));

union Quad128Floats {
    Quad128 v;
    f32 f[4];
};

void BuildUniformScaleAboutPoint(void* point, void* out, f32 s);
void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);
void AddGifRgbaEntry(PacketWriter* p, u32 c);
void AddGifXyzfEntry(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);
Quad128 TransformVector4(void* m, Quad128 v);

void DrawTriangleGroups(ColoredTriangleSet* self, f32 a, f32 b, f32 c, f32 d);

void CopyPointObject(C80* self, C80* src)
{
    KeptBits tmp = self->keep;
    CopyObjectData(self, src);
    self->keep = tmp;
}

void StartPointObject(C80* self)
{
    StartObject(self);
    if (self->targetId != -1) {
        self->target = FindFirstObjectById(self->world, 0x104, self->targetId, self);
    }
}

void InitColoredTriangles(ColoredTriangleSet* self)
{
    InitObject(self);
    g_coloredTriangleSet = self;
}

void LoadColoredTriangles(ColoredTriangleSet* self, Stream8E* rd)
{
    s32 i;
    s32 m;
    s32 j;
    s32 k;

    ReadPropertyRecords(self, rd);
    self->pointCount = ReadBufferedU16((BufferedStream*)rd);
    self->points = AllocateZeroedFrontMemory(self->pointCount << 4);
    for (i = 0; i < self->pointCount; i++) {
        self->points[i].x = ReadBufferedFloat((BufferedStream*)rd);
        self->points[i].y = -ReadBufferedFloat((BufferedStream*)rd);
        self->points[i].w = 1.0f;
    }
    self->minX = ReadBufferedFloat((BufferedStream*)rd);
    self->minY = ReadBufferedFloat((BufferedStream*)rd);
    self->f4C = 1.0f;
    self->maxX = ReadBufferedFloat((BufferedStream*)rd);
    self->maxY = ReadBufferedFloat((BufferedStream*)rd);
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
        r->count = ReadBufferedU16((BufferedStream*)rd);
        r->triangles = AllocateFrontMemory(r->count * 12);
        for (j = 0; j < r->count; j++) {
            TriangleIndices* e = &r->triangles[j];
            e->a = ReadBufferedU16((BufferedStream*)rd);
            e->b = ReadBufferedU16((BufferedStream*)rd);
            e->c = ReadBufferedU16((BufferedStream*)rd);
        }
    }
}

void DrawTriangleGroups(ColoredTriangleSet* self, f32 a, f32 b, f32 c, f32 d)
{
    f32 sp[16];
    TriangleColor col;
    Quad128Floats vv, q;
    s32 g;
    BuildUniformScaleAboutPoint(0, sp, c);
    sp[12] = a;
    sp[13] = b;
    BeginGifTag(&g_gsPacketWriter, 0, 1, 0xE);
    AddGifRegisterWrite(&g_gsPacketWriter, 0x47, 0x31001);
    AddGifRegisterWrite(&g_gsPacketWriter, 0x42, 0x44);
    for (g = 4; g > 0; g--) {
        TriangleList* grp = &self->lists[g];
        if (grp->count > 0) {
            BeginGifTag(&g_gsPacketWriter, 0, 1, 1);
            col = *(TriangleColor*)((u32)(g - 3) < 2 ? &g_triangleGroupGrey : &g_triangleGroupBlue);
            col.c[3] = (u8)(s32)((f32)col.c[3] * d);
            AddGifRgbaEntry(&g_gsPacketWriter, *(u32*)&col);
            BeginGifTag(&g_gsPacketWriter, (s8)col.c[3] >= 0 ? 0x43 : 0x83, 1, 4);
            {
                s32 i;
                for (i = 0; i < grp->count; i++) {
                    u32* idx = (u32*)((u8*)grp->triangles + i * 12);
                    s32 j;
                    for (j = 2; j >= 0; j--) {
                        vv.v = *(Quad128*)&self->points[*idx++];
                        q.v = TransformVector4(sp, vv.v);
                        AddGifXyzfEntry(&g_gsPacketWriter, (s32)((q.f[0] + 1728.0f) * 16.0f), (s32)((q.f[1] * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
                    }
                }
            }
        }
    }
}

struct ClampHelper {
    static f32 Clamp(f32 v, f32 lo, f32 hi)
    {
        return v < lo ? lo : (hi < v ? hi : v);
    }
};
struct BlendColor {
    u8 c[4];
    // One channel moved from a to b by t, rounding up towards b.
    static s32 Mix(s32 a, s32 b, f32 t)
    {
        if (a == b) return b;
        if (a < b) return a + (s32)(t * ((f32)b + 0.999f - (f32)a));
        return b + (s32)((1.0f - t) * ((f32)a + 0.999f - (f32)b));
    }
    // This colour set to a moved towards b by t.
    void Blend(const BlendColor& a, const BlendColor& b, f32 t)
    {
        BlendColor r;
        r.c[0] = Mix(a.c[0], b.c[0], t);
        r.c[1] = Mix(a.c[1], b.c[1], t);
        r.c[2] = Mix(a.c[2], b.c[2], t);
        r.c[3] = Mix(a.c[3], b.c[3], t);
        *this = r;
    }
};

SwitchedCollider* GetActiveSwitchedCollider(void);
extern Camera* g_camera;
void ProjectPointToCamera(Camera* camera, Vec02* in, f32* out);

void DrawColoredTriangles(ColoredTriangleSet* self, f32 t)
{
    f32 mat[16];
    SwitchedCollider* o;

    BuildUniformScaleAboutPoint(0, mat, (1.0f - t) * (1280.0f / self->width) + t * (4.0f / self->width));
    o = GetActiveSwitchedCollider();
    if (o != 0 && (o = o->desc05()->m53(o)) != 0 && o->desc05()->m4D(o) == 2) {
        Vec02 v;
        f32 x, y;
        ProjectPointToCamera(g_camera, &o->v140, (f32*)&v);
        x = ClampHelper::Clamp(v.x * 320.0f + 320.0f, 10.0f, 630.0f);
        mat[12] = (1.0f - t) * 320.0f + t * x;
        y = ClampHelper::Clamp(v.y * -246.40001f + 246.40001f, 16.0f, 476.80002f);
        mat[13] = (1.0f - t) * 246.40001f + t * y;
    } else {
        mat[12] = 320.0f;
        mat[13] = 246.40001f;
    }
    {
        BlendColor base;
        s32 g;
        s32 vis;
        BeginGifTag(&g_gsPacketWriter, 0, 1, 0xE);
        AddGifRegisterWrite(&g_gsPacketWriter, 0x47, 0x31001);
        AddGifRegisterWrite(&g_gsPacketWriter, 0x42, 0x44);
        vis = 0;
        for (g = 4; g >= 0; g--) {
            TriangleList* r = &self->lists[g];
            BlendColor col = *(BlendColor*)&r->col;
            if (g == 0) {
                BlendColor mixed;
                BlendColor from = *(BlendColor*)&r->col;
                BlendColor black;
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
                        Quad128Floats p, q;
                        p.v = *(Quad128*)&self->points[*idx];
                        q.v = TransformVector4(mat, p.v);
                        AddGifXyzfEntry(&g_gsPacketWriter, (s32)((q.f[0] + 1728.0f) * 16.0f), (s32)((q.f[1] * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
                        vis = vis || 0.0f < q.f[0] || q.f[0] < 640.0f || 0.0f < q.f[1] || q.f[1] < 492.80002f;
                    }
                }
            }
        }
        if (vis) {
            Quad128Floats lo, hi;
            f32 d;
            lo.v = TransformVector4(mat, *(Quad128*)&self->minX);
            hi.v = TransformVector4(mat, *(Quad128*)&self->maxX);
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
                BlendColor fade = base;
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
