// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 904/2028 (44.6%), checked 2026-11-08
// NEAR (2026-11-08, night-large5): the spawn shape's point and direction (func_00156718, 2028
// bytes): frame, saved registers, the five kinds (point, box, curve, ring of segments, mesh) and
// the direction modes follow retail (the inner mode tests as switches with the default first,
// the jitter range through an inline). Left: the ring's NormalizeOr loads its fallback into a VU
// register before the test (jump.c after cse2 turns the arms into a preset), where retail loads
// it into a GPR (lq) and moves it in the fallback arm; the final normalisation's result and the
// position copy are named locals at 0x80 and 0x90 in retail, which ours puts in reused slots.
#include "common.h"
#include "vu0.h"
#include "shapes.h"
#include "placed_object.h"

extern const Vec02 g_unitXVector;
extern const Vec02 g_unitZVector;
extern u8* g_camera;

struct SpawnCurve;
typedef void (*CurveEvalFn)(SpawnCurve* self, f32 t, Vec02* pos, Vec02* dir);
struct SpawnCurveClass { u8 pad0[8]; CurveEvalFn eval; };
struct SpawnCurve {
    SpawnCurveClass* desc;  // 0x00
    u8 pad04[8];
    s32 count;              // 0x0C
    u8 pad10[4];
    f32* lengths;           // 0x14
};

// A piece of a ring of segments between two objects: the radii at its ends and its length.
struct SpawnSegment {
    u8 pad00[8];
    f32 f08;                // 0x08
    f32 f0C;                // 0x0C
    f32 r0;                 // 0x10
    f32 r1;                 // 0x14
    PlacedObject* from;     // 0x18
    PlacedObject* to;       // 0x1C
    f32 f20;                // 0x20
    f32 len;                // 0x24
};

struct SpawnTriangle {
    s32 v[3];               // 0x00
    f32 area;               // 0x0C
};

struct SpawnMesh {
    u8 pad00[4];
    Vec02* verts;           // 0x04
    s32 count;              // 0x08
    SpawnTriangle* tris;    // 0x0C
    Vec02* normals;         // 0x10
    f32 area;               // 0x14
};

// A range a random float is drawn from.
struct SpawnRange {
    f32 lo;
    f32 hi;
};

struct SpawnShape {
    s32 kind;               // 0x00
    u8 pad04[0xC];
    union {
        Vec02 point;        // 0x10
        struct {
            f32 lo[4];      // 0x10
            f32 hi[4];      // 0x20
        } box;
        SpawnCurve* curve;  // 0x10
        struct {
            s32 count;      // 0x10
            SpawnSegment* segs; // 0x14
            f32 len;        // 0x18
        } ring;
        SpawnMesh mesh;     // 0x10
    };
    u8 pad30[0x40 - 0x30];
    s32 mode;               // 0x40
    u8 pad44[0x50 - 0x44];
    Vec02 dir;              // 0x50
    SpawnRange jitter;      // 0x60
    u8 pad68[4];
    void* anchor;           // 0x6C
};

f32 RandomFloatInRange(f32 a, f32 b);
void BuildPerpendicularPair(Vec02* dir, Vec02* out, const Vec02* hint, const Vec02* hint2);
void ComputePolarOffset(Vec02* out, f32 angle, f32 scale, f32 z);
s32 SolveQuadratic(f32 a, f32 b, f32 c, f32* roots);
void TransformPointBetweenFrames(void* from, void* to, Vec02* in, Vec02* out);
void TransformDirectionBetweenFrames(void* from, void* to, Vec02* in, Vec02* out);

f32 RandomFloatInRange(f32 a, f32 b);

static inline f32 RandomInRange(const SpawnRange& r)
{
    return RandomFloatInRange(r.lo, r.hi);
}

// out = v made unit length, or fallback when v is shorter than 0.0001.
static inline void SetNormalized(Vec02& out, const Vec02& v, u128 fallback)
{
    u128 len = Vu0::Length(Vu0::Q(v));
    if (Vu0::ToFloat(len) < 0.0001f) {
        Vu0::Q(out) = fallback;
    } else {
        Vu0::Set(out, Vu0::DivX(Vu0::Q(v), len));
    }
}

void func_00156718(SpawnShape* shape, s32 index, s32 count, Vec02* pos, Vec02* axis)
{
    switch (shape->kind) {
    case 0:
        *pos = shape->point;
        break;
    case 1:
        pos->x = RandomFloatInRange(shape->box.lo[0], shape->box.hi[0]);
        pos->y = RandomFloatInRange(shape->box.lo[1], shape->box.hi[1]);
        pos->z = RandomFloatInRange(shape->box.lo[2], shape->box.hi[2]);
        break;
    case 2: {
        SpawnCurve* curve = shape->curve;
        f32 step = curve->lengths[curve->count - 1] / (f32)count;
        f32 lo = (f32)index * step;
        f32 t = RandomFloatInRange(lo, lo + step);
        switch (shape->mode) {
        default:
            if (curve->desc->eval) {
                curve->desc->eval(curve, t, pos, 0);
            }
            break;
        case 2:
            if (curve->desc->eval) {
                curve->desc->eval(curve, t, pos, axis);
            }
            goto normalize;
        case 3: {
            Vec02 tangent;
            if (curve->desc->eval) {
                curve->desc->eval(curve, t, pos, &tangent);
            }
            Vu0::Set(*axis, Vu0::Cross(Vu0::Vec::Of(tangent), Vu0::Vec::Of(shape->dir)).q);
            goto normalize;
        }
        }
        break;
    }
    case 3: {
        f32 step = shape->ring.len / (f32)count;
        f32 d = RandomFloatInRange((f32)index * step, (f32)(index + 1) * step);
        SpawnSegment* seg;
        Vec02 offset;
        Mat02 frame;
        Vec02 at;
        Vec02 side;
        f32 roots[2];
        s32 i;
        for (i = 0; i < shape->ring.count; i++) {
            seg = &shape->ring.segs[i];
            d -= seg->len;
            if (d < 0.0f) {
                break;
            }
        }
        Vu0::Set(frame.r[2], Vu0::NormalizeOr(Vu0::Sub(Vu0::Q(seg->to->v140), Vu0::Q(seg->from->v140)),
                                              Vu0::Q(g_unitXVector)));
        BuildPerpendicularPair(&frame.r[2], &frame.r[0], &g_unitXVector, &g_unitZVector);
        d += seg->len;
        if (seg->f0C != seg->f08) {
            SolveQuadratic((seg->f0C - seg->f08) * 0.5f / seg->f20, seg->f08, -d, roots);
        } else {
            roots[0] = d / seg->f08;
        }
        f32 u = roots[0] / seg->f20;
        ComputePolarOffset(&offset, RandomFloatInRange(-3.14159265f, 3.14159265f), (1.0f - u) * seg->r0 + u * seg->r1,
                           roots[0]);
        Vu0::Set(at, Vu0::Add(Vu0::Vec::Of(seg->from->v140), Vu0::Rotate(frame, Vu0::Vec::Of(offset))).q);
        TransformPointBetweenFrames(0, shape->anchor, &at, pos);
        switch (shape->mode) {
        case 2:
            TransformDirectionBetweenFrames(0, shape->anchor, &frame.r[2], axis);
            goto normalize;
        case 3: {
            Vu0::Set(side, Vu0::NormalizeOr(Vu0::Cross(Vu0::Q(frame.r[2]), Vu0::Q(shape->dir)),
                                            Vu0::Q(g_unitXVector)));
            TransformDirectionBetweenFrames(0, shape->anchor, &side, axis);
            goto normalize;
        }
        }
        break;
    }
    case 4: {
        SpawnMesh* mesh = &shape->mesh;
        f32 a = RandomFloatInRange(0.0f, 1.0f) * mesh->area;
        SpawnTriangle* tri;
        Vec02 p[3];
        s32 i;
        for (i = 0; i < mesh->count; i++) {
            tri = &mesh->tris[i];
            a -= tri->area;
            if (a <= 0.0f) {
                break;
            }
        }
        p[0] = mesh->verts[tri->v[0]];
        p[1] = mesh->verts[tri->v[1]];
        p[2] = mesh->verts[tri->v[2]];
        f32 s = RandomFloatInRange(0.0f, 1.0f);
        f32 t = RandomFloatInRange(0.0f, 1.0f - s);
        f32 w = 1.0f - s - t;
        Vu0::Set(*pos, Vu0::MulXSum3(Vu0::Vec::Of(p[0]), Vu0::Vec::Scalar(s), Vu0::Vec::Of(p[1]),
                                     Vu0::Vec::Scalar(t), Vu0::Vec::Of(p[2]), Vu0::Vec::Scalar(w)).q);
        if (shape->mode == 5) {
            Vec02 n[3];
            Vu0::Set(n[0], Vu0::Vec::Of(mesh->normals[tri->v[0]]).q);
            Vu0::Set(n[1], Vu0::Vec::Of(mesh->normals[tri->v[1]]).q);
            Vu0::Set(n[2], Vu0::Vec::Of(mesh->normals[tri->v[2]]).q);
            Vu0::Set(*axis, Vu0::MulXSum3(Vu0::Vec::Of(n[0]), Vu0::Vec::Scalar(s), Vu0::Vec::Of(n[1]),
                                          Vu0::Vec::Scalar(t), Vu0::Vec::Of(n[2]), Vu0::Vec::Scalar(w)).q);
            goto normalize;
        }
        break;
    }
    }
    switch (shape->mode) {
    case 0:
        *axis = shape->dir;
        break;
    case 1:
        Vu0::Set(*axis, Vu0::Sub(Vu0::Vec::Of(*pos), Vu0::Vec::Of(shape->dir)).q);
        break;
    case 4:
        if (shape->anchor != 0) {
            Vu0::Set(*axis, Vu0::RotateTransposed(*(Mat02*)((u8*)shape->anchor + 0x110),
                                                  Vu0::Rotate(*(Mat02*)(g_camera + 0x80), Vu0::Vec::Of(shape->dir))).q);
        } else {
            Vu0::Set(*axis, Vu0::Rotate(*(Mat02*)(g_camera + 0x80), Vu0::Vec::Of(shape->dir)).q);
        }
        break;
    default:
        *axis = g_unitXVector;
        break;
    }
normalize:
    Vec02 n;
    SetNormalized(n, *axis, Vu0::Q(g_unitXVector));
    *axis = n;
    Vec02 at = *pos;
    Vu0::Set(*pos, Vu0::Add(Vu0::Vec::Of(at), Vu0::MulX(Vu0::Vec::Of(n),
                            Vu0::Vec::Scalar(RandomInRange(shape->jitter)))).q);
}
