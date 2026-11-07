// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "point_object.h"
#include "collider.h"
#include "globals.h"
#include "shapes.h"
#include "placed_object.h"
#include "asm_func.h"
#include "fpu.h"
#include "vu0.h"

// From 0x17D248 to colored_triangle_set: player helpers in VU0 code, the probe test func_0017DE88, and the
// point-object list of class 0x80. Its .data runs from 0x263E50 to 0x264094 (tuning floats the
// VU0 functions read, vectors, the probe segments and the list head g_pointObjects); its
// .rodata from 0x24B060 to 0x24B164 is the jump tables of its VU0 functions.

f32 D_00263E50 = 0.150000006f;
f32 D_00263E54 = 300.0f;
f32 D_00263E58 = 2.5f;
f32 D_00263E5C = 3.5f;
f32 D_00263E60 = 2.5f;
f32 D_00263E64 = 60.0f;
f32 D_00263E68 = 20.0f;
f32 D_00263E6C = 10.0f;
f32 D_00263E70 = 0.0700000003f;
f32 D_00263E74 = 0.300000012f;
f32 D_00263E78 = -750.0f;
f32 D_00263E7C = 5.0f;
f32 D_00263E80 = 700.0f;
f32 D_00263E84 = 245.0f;
f32 D_00263E88 = 900.0f;
f32 D_00263E8C = 800.0f;
f32 D_00263E90[4] = { 0.0f, 5.0f, 0.0f, 0.0f };
f32 D_00263EA0[4] = { 0.0f, 10.0f, 0.0f, 0.0f };
f32 D_00263EB0[4] = { 0.400000006f, 0.0f, 0.0f, 0.0f };
// The 22 segment ends func_0017DE88 transforms; func_00188700 loads each whole (lqc2).
Vec02 D_00263EC0[22] = {
    { 50.0f, 0.0f, 75.0f, 0.0f },
    { 50.0f, 0.0f, -150.0f, 0.0f },
    { 50.0f, 0.0f, 75.0f, 0.0f },
    { -60.0f, 0.0f, 75.0f, 0.0f },
    { -60.0f, 0.0f, 75.0f, 0.0f },
    { -60.0f, 0.0f, -50.0f, 0.0f },
    { -57.96f, 15.53f, 75.0f, 0.0f },
    { -57.96f, 15.53f, -50.0f, 0.0f },
    { -51.96f, 30.0f, 75.0f, 0.0f },
    { -51.96f, 30.0f, -50.0f, 0.0f },
    { -42.43f, 42.43f, 75.0f, 0.0f },
    { -42.43f, 42.43f, -50.0f, 0.0f },
    { -30.0f, 51.96f, 75.0f, 0.0f },
    { -30.0f, 51.96f, -50.0f, 0.0f },
    { -57.96f, -15.53f, 75.0f, 0.0f },
    { -57.96f, -15.53f, -50.0f, 0.0f },
    { -51.96f, -30.0f, 75.0f, 0.0f },
    { -51.96f, -30.0f, -50.0f, 0.0f },
    { -42.43f, -42.43f, 75.0f, 0.0f },
    { -42.43f, -42.43f, -50.0f, 0.0f },
    { -30.0f, -51.96f, 75.0f, 0.0f },
    { -30.0f, -51.96f, -50.0f, 0.0f },
};
f32 D_00264020 = 60.0f;
f32 D_00264024 = 70.0f;
f32 D_00264028 = 300.0f;
f32 D_0026402C = 500.0f;
f32 D_00264030 = 1000.0f;
f32 D_00264034 = 3000.0f;
f32 D_00264038[2] = { -150.0f, 150.0f };
f32 D_00264040 = 0.349999994f;
f32 D_00264044 = 0.349999994f;
f32 D_00264048[2] = { 10000.0f, 0.0f };
f32 D_00264050[4] = { 682.0f, 0.5f, 0.0f, 0.0f };
f32 D_00264060[4] = { -3.40282347e+38f, 682.0f, 0.0f, 0.0f };
f32 D_00264070[4] = { 682.0f, 1.0f, 0.0f, 0.0f };
f32 D_00264080[2] = { -3.40282347e+38f, 682.0f };
// size: list head of three words, link offset at +8 (0x50)
List01 g_pointObjects = {0};

INCLUDE_RODATA(jtbl_0024B060);
INCLUDE_ASM(func_0017D248);

INCLUDE_RODATA(jtbl_0024B090);
INCLUDE_ASM(func_0017D5D8);

// An edge of a mesh: the two vertices it joins and the two faces it lies between.
struct MeshEdge {
    s16 vertA;
    s16 vertB;
    s16 faceA;
    s16 faceB;
};

// A face of a mesh: its normal, then its slope (the normal's y) at +8.
struct MeshFace {
    Vec02 normal;           // 0x00
    u8 pad10[0x20 - 0x10];
};

s32 func_0017DCE0(void* unused, Collider* c, MeshEdge* e, Vec02* out)
{
    Mesh03* mesh = &c->meshCopy;
    MeshFace* faces = (MeshFace*)mesh->faces;
    MeshFace* fa = &faces[e->faceA];
    MeshFace* fb = &faces[e->faceB];
    MeshFace* flat;
    if (0.7f < fa->normal.z && fb->normal.z < 0.55f) {
        flat = fb;
    } else if (fa->normal.z < 0.55f && 0.7f < fb->normal.z) {
        flat = fa;
    } else {
        return 0;
    }
    Vec02* verts = (Vec02*)mesh->verts;
    Vec02 d;
    Vec02 n;
    u128 vb = Vu0::Q(verts[e->vertB]);
    u128 va = Vu0::Q(verts[e->vertA]);
    Vu0::Q(d) = Vu0::Sub(vb, va);
    n.z = 0.0f;
    n.y = d.x;
    n.x = -d.y;
    Vu0::Set(n, Vu0::NormalizeOr(Vu0::Q(n), Vu0::Q(g_unitXVector)));
    if (Vu0::ToFloat(Vu0::Dot(Vu0::Q(n), Vu0::Q(flat->normal))) < 0.0f) {
        Vu0::Q(n) = Vu0::MulX(Vu0::Q(n), Vu0::Scalar(-1.0f));
    }
    *out = n;
    return 1;
}


void BuildPerpendicularPair(Quad16* q, void* out, const Vec02* a, const Vec02* b);
void BuildMatrixFromRotationAndTranslation(void* a, Quad16* b, void* out);
void TransformByMatrixWithW(void* a, f32 w, const void* b, void* c);
s32 CollectColliderSpans(Collider* self, void* a1, void* a2, s32 a3, void* a4);

s32 TestProbeSegmentsAgainstColliders(Collider* self, void* ctx, Quad16* src)
{
    u8 buf[0x100] __attribute__((aligned(16)));
    Quad16& q = *(Quad16*)buf;
    q = *src;
    s32 hits = 0;
    BuildPerpendicularPair(&q, buf + 0x10, &g_unitZVector, &g_unitZVector);
    BuildMatrixFromRotationAndTranslation(ctx, &q, buf + 0x30);
    for (s32 i = 0; (u32)i < 0x16; i += 2) {
        TransformByMatrixWithW(buf + 0x30, 1.0f, &D_00263EC0[i], buf + 0x70);
        TransformByMatrixWithW(buf + 0x30, 1.0f, &D_00263EC0[i + 1], buf + 0x80);
        ContactRow03* n = self->contacts->head;
        while (n) {
            Collider* a = n->other;
            if (!(a->flags538 & 0x40000000000ULL)) {
                Collider* c = (Collider*)a->parts.head;
                while (c) {
                    if (!(c->flags538 & 0x80000000000ULL)) {
                        if (CollectColliderSpans(c, buf + 0x70, buf + 0x80, 1, buf + 0x90) > 0) {
                            if (i < 4) return 0;
                            if (*(f32*)(buf + 0xD0) == 0.0f) return 0;
                            if (0.7f < *(f32*)(buf + 0xB8)) hits++;
                        }
                    }
                    c = (Collider*)c->link2E4.next;
                }
            }
            n = n->next;
        }
    }
    return hits >= 2;
}

INCLUDE_ASM(func_0017E088);

INCLUDE_ASM(func_0017E3C8);

s32 ChoosePlayerNextState(Player* self)
{
    s32 r;
    if (0.0f < self->f634) {
        if (self->f900 != 0) {
            r = 1;
        } else {
            r = self->fA10 ? 5 : 0;
        }
    } else r = 0;
    return r;
}

INCLUDE_ASM(func_0017E710);

INCLUDE_ASM(func_0017ECE8);

INCLUDE_RODATA(jtbl_0024B0D0);
INCLUDE_RODATA(jtbl_0024B110);
INCLUDE_ASM(func_0017F018);

s32 SolveQuadratic(f32* roots, f32 a, f32 b, f32 c);

s32 SolveArrivalTimeAtHeight(Player* self, Vec02* a, Vec02* b, Vec02* c, Vec02* d, f32* out)
{
    f32 roots[2];
    s32 count = SolveQuadratic(roots, self->gravity.z * 0.5f, b->z - d->z, a->z - c->z);
    switch (count) {
    case 0:
        return 0;
    case 1:
        break;
    case 2:
        roots[0] = (roots[1] >? roots[0]);
        break;
    }
    if (roots[0] <= 0.0f) {
        return 0;
    }
    *out = roots[0];
    return 1;
}

INCLUDE_RODATA(jtbl_0024B150);
INCLUDE_ASM(func_0017FB78);

static inline f32 EvalClampedQuadratic(const f32* poly, const f32* range, f32 z)
{
    f32 v = poly[0] + z * (poly[1] + z * poly[2]);
    f32 lo = range[0];
    f32 hi = range[1];
    if (v < lo) {
        v = lo;
    } else if (hi < v) {
        v = hi;
    }
    return v;
}

void func_0017FC48(PlacedObject* self, Vec02* out)
{
    *out = self->v150;
    f32 z = EvalClampedQuadratic(D_00264050, D_00264060, out->z);
    out->z = z;
    out->z = (z >? self->v150.z);
}
void func_0017FCC8(PlacedObject* self, Vec02* out)
{
    *out = self->v150;
    f32 z = EvalClampedQuadratic(D_00264070, D_00264080, out->z);
    out->z = z;
    out->z = (z >? self->v150.z);
}

void SetListLinkOffset(void* self, s32 value);

void SetPointObjectListLinkOffset(void)
{
    SetListLinkOffset(&g_pointObjects, 0x50);
}

void ClearList(void* p);

void ClearPointObjectList(void)
{
    ClearList(&g_pointObjects);
}

void RegisterObject(void* self);
void AppendToList(void* table, void* self);

void RegisterPointObject(C80* self)
{
    RegisterObject(self);
    AppendToList(&g_pointObjects, self);
}

void UnregisterObject(void* self);
void RemoveFromList(void* table, void* self);

void UnregisterPointObject(C80* self)
{
    UnregisterObject(self);
    RemoveFromList(&g_pointObjects, self);
}
