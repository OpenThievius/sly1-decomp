// SPDX-License-Identifier: AGPL-3.0-or-later
// Curves: piecewise-linear and spline tracks of keyed values (two kinds, made by func_0014D9A8,
// with the method tables D_002176D0 and D_00217708), and the segment-length and lookup helpers.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "path_curve.h"
#include "shapes.h"
#include "placed_object.h"
#include "vu0.h"

// What the nearest-time search (func_001EB168) passes its measure: the curve and the two points
// of the segment MeasurePathCurveDistance measures against (FindPathCurveNearestTime,
// FindSplinePathNearestTime).
struct NearestTimeQuery {
    PathCurve* curve;       // 0x00
    Vec02* a;               // 0x04
    Vec02* b;               // 0x08
    s32 pad;                // 0x0C
};

// What the nearest-time search writes back: the time it found.
struct NearestTimeResult {
    f32 time;               // 0x00
    s32 p1;                 // 0x04
    s32 p2;                 // 0x08
    s32 p3;                 // 0x0C
};

// The point the curve's slot 1 samples into (MeasurePathCurveDistance's call, with the time
// still in $f12), and the spline's slot 1 and slot 11 as func_0014E6A8 and func_0014ED98 call
// them, with the time slot 6 returns.
typedef void (*CurveSamplePointFn)(PathCurve* self, Vec02* out, s32 flag);
typedef f32 (*CurveTimeFn)(void* self);
typedef void (*CurveSampleAtFn)(void* self, f32 t, s32 a1, void* a2);
typedef void (*SplineSlot11Fn)(void* self, s32 p1, f32 x, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6);

// A segment index and the fraction along it (FindNearestPathCurveSegment's two outputs).
struct SegmentFraction { s32 idx; f32 t; };

// An entry of a table of functions.
typedef void (*Fn_Table)();
extern const Fn_Table g_pathCurveKind0Methods[];
extern const Fn_Table g_pathCurveKind1Methods[];

f32 MeasureCurveSegmentLength(void* p0, void* p1, void* p2, void* p3, f32 x, f32 y);
void SampleCurvePoints(void* a, void* b, void* c, void* d, f32 x, f32 y, f32 z, s32 n, void* buf);
s32 ReadBufferedU8(void* src);
f32 ReadBufferedFloat(void* src);
void ReadBufferedVector3(void* src, void* dst);
void MeasurePointToSegment(Vec02* p, Vec02* a, Vec02* b, f32* o1, f32* o2);
void TransformByMatrixWithW(void* a, void* b, void* c, f32 w);
void TransformMatrixByObject(void* self, void* arg, Quad16* out);
void* AllocateFrontMemory(s32 size);
void* AllocateZeroedFrontMemory(u32 n);
void DrawProjectedLine(void* a, void* b, void* c, s32 d, s32 e);
void DrawProjectedCurve(void* a, void* b, void* c, void* d, void* color, s32 e, s32 f, f32 x);
void FindLocalMinimum(void* fn, f32 f12, f32 f13, f32 f14, f32 f15, void* ctx, void* out, s32 a3);

f32 AccumulateSegmentLengths(s32 n, void* buf, void* other);
f32 WrapCurveTime(s32 count, f32* table, s32 wrap, f32 x);
s32 FindPathCurveSegment(f32 x, s32 n, f32* arr, s32 wrap, f32* lo, f32* hi);
void InterpolatePathCurvePoint(s32 count, void* points, f32* times, s32 wrap, s32 a4, s32 a5);
void FindNearestPathCurveSegment(void* a0, void* a1, s32 count, void* a3, void* a4, void* a5, s32* outIdx, f32* outT);
void WalkToNearestPathCurveSegment(void* a0, void* a1, s32 a2, void* a3, s32 idx, s32 a5, f32* a6, f32* a7, s32* p9, f32* p10);
void TransformPointArray(s32 count, Quad16* dst, void* arg, void* self);
PathCurve* CreatePathCurve(s32 kind);
f32 GetBaseCurveLengthAtTime(void);
f32 GetBaseCurveTimeAtLength(void);
s32 FindPathCurveSegmentByTime(PathCurve* self, f32 t, f32* a, f32* b);
s32 FindPathCurveSegmentByLength(PathCurve* self, f32 t, f32* a1, f32* a2);
void MeasureSplinePathDistance(void);
f32 GetPathCurveEndTime(PathCurve* obj);
f32 GetPathCurveEndLength(PathCurve* obj);
void func_0014DB70(void);
f32 MeasurePathCurveDistance(NearestTimeQuery* self);
void FindPathCurveNearestTime(PathCurve* self, s32 a1, s32 a2, s32 a3, s32 a4, f32* a5, f32* a6, f32 f12);
f32 GetPathCurveSearchStep(PathCurve* self);
void ReadPathCurve(PathCurve* self, void* src);
void SamplePathCurveAtTime(PathCurve* self, s32 a1, s32 a2);
void SamplePathCurveAtLength(PathCurve* self, s32 a1, s32 a2);
void DrawPathCurveSegment(PathCurve* self, s32 idx, void* a2, s32 a3, void* a4, s32 a5);
void TransformPathCurvePoints(PathCurve* self, void* a, void* b);
f32 GetPathCurveLengthAtTime(PathCurve* self, f32 t);
f32 GetPathCurveTimeAtLength(PathCurve* self, f32 t);
f32 FillPathCurveLengths(PathCurve* self);
void FindPathCurveNearestPoint(PathCurve* self, void* a1, void* a2, void* a3, void* a4, f32* out0, f32* out1);
void ProjectOntoPathCurveNearTime(PathCurve* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6);
void ProjectOntoPathCurveNearLength(PathCurve* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6);
void ReadSplinePathCurve(SplinePathCurve* self, void* src);
void ResetSplineSegmentCache(SplinePathCurve* obj);
void SampleSplineSegment(SplinePathCurve* self, s32 i);
void SampleSplinePathAtLength(SplinePathCurve* self, s32 a1, void* a2);
f32 GetSplineLengthAtTime(SplinePathCurve* self, f32 t);
f32 GetSplineTimeAtLength(SplinePathCurve* self, f32 t);
void FillSplinePathLengths(SplinePathCurve* self);
void FindSplinePathNearestTime(SplinePathCurve* self, s32 a1, s32 a2, s32 a3, s32 a4, f32* a5, f32* a6, f32 f12);
void ProjectOntoSplinePathNearLength(SplinePathCurve* self, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6);

f32 AccumulateSegmentLengths(s32 n, void* buf, void* other)
{
    Vec02* pts = (Vec02*)buf;
    f32* lengths = (f32*)other;
    Vec02 d;
    f32 total = 0.0f;
    if (lengths != 0) {
        lengths[0] = total;
    }
    for (s32 i = 1; i < n; i++) {
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(pts[i]), Vu0::Q(pts[i - 1]));
        total += Vu0::ToFloat(Vu0::Length(Vu0::Q(d)));
        if (lengths != 0) {
            lengths[i] = total;
        }
    }
    return total;
}

f32 WrapCurveTime(s32 count, f32* table, s32 wrap, f32 x)
{
    if (wrap == 0) {
        return x;
    }
    f32 lo = table[0];
    f32 hi = table[count - 1];
    f32 span = hi - lo;
    if (x < lo) {
        do {
            x += span;
        } while (x < lo);
    }
    if (hi < x) {
        do {
            x -= span;
        } while (hi < x);
    }
    return x;
}

s32 FindPathCurveSegment(f32 x, s32 n, f32* arr, s32 wrap, f32* lo, f32* hi)
{
    f32 r = WrapCurveTime(n, arr, wrap, x);
    s32 i = 1;
    while (i < n && !(r < arr[i])) i++;
    if (i >= n) i--;
    i--;
    if (lo) *lo = r - arr[i];
    if (hi) *hi = arr[i + 1] - arr[i];
    return i;
}

INCLUDE_ASM(func_0014D280);

void ConstrainVectorByAnchor(void* self, void* a, void* b, s32 c);
extern const Vec02 g_unitXVector;

// The nearest point of a polyline to pos. The direction is stored, then stored again made unit
// length: as Vu0::Vec values, NormalizeOr's argument is a copy the compiler makes (its own
// vmove, a vu0 insn of latency 2), so sched2 issues the length's dot before the first store, as
// retail does (docs/TOOLCHAIN.md, "A compiler copy's latency in sched2").
void func_0014D3A8(Vec02* pos, void* anchor, s32 n, Vec02* pts, Vec02* outPoint, Vec02* outDir, s32* outIdx, f32* outT)
{
    s32 best = -1;
    f32 frac = -1.0f;
    f32 bestDist = 3.4028234663852886e+38f;
    s32 count = n - 1;
    for (s32 i = 0; i < count; i++) {
        Vec02 d, pt, e;
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(*pos), Vu0::Q(pts[i]));
        Vu0::Q(e) = Vu0::Sub(Vu0::Q(pts[i + 1]), Vu0::Q(pts[i]));
        if (anchor != 0) {
            ConstrainVectorByAnchor(anchor, &d, &d, 0);
            ConstrainVectorByAnchor(anchor, &e, &e, 0);
        }
        Vu0::Vec ev = Vu0::Vec::Of(e);
        Vu0::Vec len = Vu0::Length(ev);
        f32 lenF = Vu0::ToFloatMoved(len);
        Vu0::Vec unit;
        unit.q = Vu0::DivX(ev.q, len.q);
        {
            Vec02 e0;
            Vu0::Q(e0) = ev.q;
        }
        f32 t = Vu0::ToFloat(Vu0::Dot(unit, Vu0::Vec::Of(d)));
        Vu0::Q(e) = unit.q;
        f32 c = t;
        if (t < 0.0f) {
            c = 0.0f;
        } else if (lenF < t) {
            c = lenF;
        }
        Vu0::Q(pt) = Vu0::MulAddX(Vu0::Q(d), Vu0::Q(e), Vu0::Scalar(-c));
        f32 dist = Vu0::ToFloat(Vu0::Dot(Vu0::Q(pt), Vu0::Q(pt)));
        if (dist < bestDist) {
            frac = c / lenF;
            bestDist = dist;
            best = i;
        }
    }
    if (outIdx != 0) {
        *outIdx = best;
    }
    if (outT != 0) {
        *outT = frac;
    }
    if (outPoint != 0) {
        Vu0::Q(*outPoint) = Vu0::MulXSum(Vu0::Q(pts[best]), Vu0::Scalar(1.0f - frac), Vu0::Q(pts[best + 1]), Vu0::Scalar(frac));
    }
    if (outDir != 0) {
        Vu0::Vec dir = Vu0::Sub(Vu0::Vec::Of(pts[best + 1]), Vu0::Vec::Of(pts[best]));
        *(Vu0::Vec*)outDir = dir;
        *(Vu0::Vec*)outDir = Vu0::NormalizeOr(dir, Vu0::Vec::Of(g_unitXVector));
    }
}

INCLUDE_ASM(func_0014D680);

void TransformPointArray(s32 count, Quad16* dst, void* arg, void* self)
{
    Quad16 mat[4];
    Quad16 tmp;

    TransformMatrixByObject(self, arg, mat);
    if (count > 0) {
        do {
            TransformByMatrixWithW(mat, dst, &tmp, 1.0f);
            *dst = tmp;
            dst++;
            count--;
        } while (count != 0);
    }
}

PathCurve* CreatePathCurve(s32 kind)
{
    PathCurve* p;
    switch (kind) {
    case 0:
        p = (PathCurve*)AllocateZeroedFrontMemory(0x1C);
        p->vt = (const PathCurveVt*)((u8*)g_pathCurveKind0Methods);
        break;
    case 1:
        p = (PathCurve*)AllocateZeroedFrontMemory(0x1D0);
        p->vt = (const PathCurveVt*)((u8*)g_pathCurveKind1Methods);
        break;
    default:
        p = 0;
        break;
    }
    if (p != 0) {
        p->kind = kind;
    }
    return p;
}

f32 GetBaseCurveLengthAtTime(void)
{
    return 0.0f;
}

f32 GetBaseCurveTimeAtLength(void)
{
    return 0.0f;
}

s32 FindPathCurveSegmentByTime(PathCurve* self, f32 t, f32* a, f32* b)
{
    return FindPathCurveSegment(t, self->count, self->times, self->wrap, a, b);
}

s32 FindPathCurveSegmentByLength(PathCurve* self, f32 t, f32* a1, f32* a2)
{
    return FindPathCurveSegment(t, self->count, self->lengths, self->wrap, a1, a2);
}

INCLUDE_ASM(func_0014DA98);

f32 GetPathCurveEndTime(PathCurve* obj) { u32 address = obj->count * 4 + (u32)obj->times; return *(f32*)(address - 4); }

f32 GetPathCurveEndLength(PathCurve* obj) { u32 address = obj->count * 4 + (u32)obj->lengths; return *(f32*)(address - 4); }

LINKER_REMNANT(func_0014DB70);

f32 MeasurePathCurveDistance(NearestTimeQuery* self)
{
    Vec02 p;
    f32 o1;
    f32 o2;
    if (self->curve->vt->m01)
        ((CurveSamplePointFn)self->curve->vt->m01)(self->curve, &p, 0);
    MeasurePointToSegment(&p, self->a, self->b, &o1, &o2);
    return o2;
}

void FindPathCurveNearestTime(PathCurve* self, s32 a1, s32 a2, s32 a3, s32 a4, f32* a5, f32* a6, f32 f12)
{
    NearestTimeQuery ctx;
    NearestTimeResult out;
    f32 f13;
    f32 f14;
    void* fn;

    ctx.curve = self;
    ctx.a = (Vec02*)a1;
    ctx.b = (Vec02*)a2;
    f14 = self->times[0];
    f13 = (self->times[1] - f14) * 0.1f;
    FindLocalMinimum((void*)MeasurePathCurveDistance, f12, f13, self->wrap ? -3.4028235e+38f : f14, self->wrap ? 3.4028235e+38f : self->times[self->count - 1], &ctx, &out, 0);
    if (a3 != 0 || a4 != 0) {
        fn = (void*)self->vt->m01;
        if (fn != 0) {
            ((void (*)(PathCurve*, s32, s32, f32))fn)(self, a3, a4, out.time);
        }
    }
    if (a5 != 0) {
        *a5 = out.time;
    }
    if (a6 != 0) {
        *a6 = self->vt->m05(self, out.time);
    }
}

LINKER_REMNANT(func_0014DCF8);

f32 GetPathCurveSearchStep(PathCurve* self)
{
    f32* p = self->times;
    f32 b = p[1]; f32 a = p[0]; return (b - a) * 0.1f;
}

void ReadPathCurve(PathCurve* self, void* src)
{
    self->wrap = ReadBufferedU8(src);
    s32 n = ReadBufferedU8(src);
    self->count = n;
    self->times = (f32*)AllocateFrontMemory(n * 4);
    self->lengths = (f32*)AllocateFrontMemory(self->count * 4);
    self->points = AllocateFrontMemory(self->count * 16);
    for (s32 i = 0; i < self->count; i++) {
        self->times[i] = ReadBufferedFloat(src);
        ReadBufferedVector3(src, (u8*)self->points + i * 16);
    }
    f32 (*fn)(PathCurve*) = self->vt->m09;
    if (fn) fn(self);
}

void SamplePathCurveAtTime(PathCurve* self, s32 a1, s32 a2)
{
    InterpolatePathCurvePoint(self->count, self->points, self->times, self->wrap, a1, a2);
}

void SamplePathCurveAtLength(PathCurve* self, s32 a1, s32 a2)
{
    InterpolatePathCurvePoint(self->count, self->points, self->lengths, self->wrap, a1, a2);
}

void DrawPathCurveSegment(PathCurve* self, s32 idx, void* a2, s32 a3, void* a4, s32 a5)
{
    Quad16 A;
    Quad16 B;
    U32P C;
    s32 next;

    if (idx == self->count - 1) {
        next = 0;
        if (self->wrap == 0) {
            return;
        }
    } else {
        next = idx + 1;
    }
    TransformByMatrixWithW(a2, (u8*)self->points + (idx << 4), &A, 1.0f);
    TransformByMatrixWithW(a2, (u8*)self->points + (next << 4), &B, 1.0f);
    C = *(U32P*)a4;
    DrawProjectedLine(&A, &B, &C, a3, a5);
}

void TransformPathCurvePoints(PathCurve* self,void* a,void* b) { TransformPointArray(self->count,(Quad16*)self->points,a,b); }

f32 GetPathCurveLengthAtTime(PathCurve* self, f32 t0)
{
    f32 a, b;
    s32 i = FindPathCurveSegmentByTime(self, t0, &a, &b);
    f32 t = a / b;
    return (1.0f - t) * self->lengths[i] + t * self->lengths[i + 1];
}

f32 GetPathCurveTimeAtLength(PathCurve* self, f32 t0)
{
    f32 lo, hi;
    s32 idx = FindPathCurveSegmentByLength(self, t0, &lo, &hi);
    f32 t = lo / hi;
    return (1.0f - t) * self->times[idx] + t * self->times[idx + 1];
}

f32 FillPathCurveLengths(PathCurve* self)
{
    return AccumulateSegmentLengths(self->count, self->points, self->lengths);
}

void FindPathCurveNearestPoint(PathCurve* self, void* a1, void* a2, void* a3, void* a4, f32* out0, f32* out1)
{
    SegmentFraction f;
    FindNearestPathCurveSegment(a1, a2, self->count, self->points, a3, a4, &f.idx, &f.t);
    if (out1) {
        *out1 = (1.0f - f.t) * self->lengths[f.idx] + f.t * self->lengths[f.idx + 1];
    }
    if (out0) {
        *out0 = (1.0f - f.t) * self->times[f.idx] + f.t * self->times[f.idx + 1];
    }
}

void ProjectOntoPathCurveNearTime(PathCurve* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6)
{
    s32 idx = FindPathCurveSegment(t, self->count, self->times, self->wrap, 0, 0);
    s32 ia;
    f32 fb;
    WalkToNearestPathCurveSegment(a1, a2, self->count, self->points, idx, self->wrap, a3, a4, &ia, &fb);
    if (a6) *a6 = (1.0f - fb) * self->lengths[ia] + fb * self->lengths[ia + 1];
    if (a5) *a5 = (1.0f - fb) * self->times[ia] + fb * self->times[ia + 1];
}

void ProjectOntoPathCurveNearLength(PathCurve* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6)
{
    s32 idx = FindPathCurveSegment(t, self->count, self->lengths, self->wrap, 0, 0);
    s32 ia;
    f32 fb;
    WalkToNearestPathCurveSegment(a1, a2, self->count, self->points, idx, self->wrap, a3, a4, &ia, &fb);
    if (a6) *a6 = (1.0f - fb) * self->lengths[ia] + fb * self->lengths[ia + 1];
    if (a5) *a5 = (1.0f - fb) * self->times[ia] + fb * self->times[ia + 1];
}

void ReadSplinePathCurve(SplinePathCurve* self, void* src)
{
    self->wrap = ReadBufferedU8(src);
    s32 n = ReadBufferedU8(src);
    self->count = n;
    self->times = (f32*)AllocateFrontMemory(n * 4);
    self->lengths = (f32*)AllocateFrontMemory(self->count * 4);
    self->points = AllocateFrontMemory(self->count * 16);
    self->inTan = AllocateFrontMemory(self->count * 16);
    self->outTan = AllocateFrontMemory(self->count * 16);
    for (s32 i = 0; i < self->count; i++) {
        self->times[i] = ReadBufferedFloat(src);
        ReadBufferedVector3(src, (u8*)self->points + i * 16);
        ReadBufferedVector3(src, (u8*)self->inTan + i * 16);
        ReadBufferedVector3(src, (u8*)self->outTan + i * 16);
    }
    f32 (*fn)(PathCurve*) = self->vt->m09;
    if (fn) fn(self);
    ResetSplineSegmentCache(self);
}

void ResetSplineSegmentCache(SplinePathCurve* obj) { obj->idx1C0 = -1; }

void SampleSplineSegment(SplinePathCurve* self, s32 i)
{
    if (i != self->idx1C0) {
        f32 d = self->times[i + 1] - self->times[i];
        s32 off = i * 16;
        SampleCurvePoints((u8*)self->points + off, (u8*)self->outTan + off, (u8*)self->points + (off + 16),
                      (u8*)self->inTan + (off + 16), d, 0.0f, d, 20, self->pts30);
        AccumulateSegmentLengths(20, self->pts30, self->len170);
        self->idx1C0 = i;
    }
}

// The Hermite evaluation (func_00130540) with its three floats first: retail sets $f12 and
// $f13 among the pointer arguments, which the floats' place in the list decides.
void EvaluateHermiteVectorSegment(f32 u, f32 v, f32 w, void* p0, void* t0, void* p1, void* t1, void* a4, void* a5, s32 a6);

void SampleSplinePathAtTime(SplinePathCurve* self, f32 t, void* a1, Vec02* a2)
{
    f32 a;
    f32 b;
    s32 i = FindPathCurveSegmentByTime(self, t, &a, &b);
    s32 off = i * 16;
    s32 next = off + 16;
    EvaluateHermiteVectorSegment(b, a, 1.0f, (u8*)self->points + off, (u8*)self->outTan + off, (u8*)self->points + next, (u8*)self->inTan + next, a1, a2, 0);
    if (a2) {
        u128 v = Vu0::Q(*a2);
        u128 fb = Vu0::Q(g_unitXVector);
        Vu0::Q(*a2) = Vu0::NormalizeOrMoved(v, fb);
    }
}

void SampleSplinePathAtLength(SplinePathCurve* self, s32 a1, void* a2)
{
    f32 t = ((CurveTimeFn)self->vt->m06)(self);
    CurveSampleAtFn fn = (CurveSampleAtFn)self->vt->m01;
    if (fn) {
        fn(self, t, a1, a2);
    }
}

// The segment from key idx to the next as a curve through the matrix m: its two points and
// their tangents, drawn in the color at a4.
void DrawSplinePathSegment(SplinePathCurve* self, s32 idx, Quad16* m, s32 a3, void* a4)
{
    Vec02 a;
    Vec02 b;
    Vec02 ta;
    Vec02 tb;
    if (idx != self->count - 1) {
        s32 next = idx + 1;
        f32 dt = self->times[next] - self->times[idx];
        Vu0::Q(a) = Vu0::Transform(*m, Vu0::Q(((Vec02*)self->points)[idx]), 1.0f);
        Vu0::Q(b) = Vu0::Transform(*m, Vu0::Q(((Vec02*)self->points)[idx + 1]), 1.0f);
        Vu0::Q(ta) = Vu0::Rotate(*m, Vu0::Q(((Vec02*)self->outTan)[idx]));
        Vu0::Q(tb) = Vu0::Rotate(*m, Vu0::Q(((Vec02*)self->inTan)[idx + 1]));
        U32P color = *(U32P*)a4;
        DrawProjectedCurve(&a, &ta, &b, &tb, &color, a3, 1, dt);
    }
}

void TransformSplinePathPoints(SplinePathCurve* self, void* a, void* b)
{
    Vec02 m[4];
    s32 i;
    TransformMatrixByObject(b, a, (Quad16*)m);
    Mat02* rot = (Mat02*)m;
    for (i = 0; i < self->count; i++) {
        u8* p = (u8*)self->points + (i << 4);
        TransformByMatrixWithW(m, p, p, 1.0f);
        Vu0::Q(((Vec02*)self->inTan)[i]) = Vu0::Rotate(*rot, Vu0::Q(((Vec02*)self->inTan)[i]));
        Vu0::Q(((Vec02*)self->outTan)[i]) = Vu0::Rotate(*rot, Vu0::Q(((Vec02*)self->outTan)[i]));
    }
    ResetSplineSegmentCache(self);
}

f32 GetSplineLengthAtTime(SplinePathCurve* self, f32 t0)
{
    f32 a, b;
    s32 i = FindPathCurveSegmentByTime(self, t0, &a, &b);
    u32 off = i * 16;
    f32 r = MeasureCurveSegmentLength((u8*)self->points + off, (u8*)self->outTan + off,
                          (u8*)self->points + (off + 16), (u8*)self->inTan + (off + 16), b, a);
    return r + self->lengths[i];
}

f32 GetSplineTimeAtLength(SplinePathCurve* self, f32 t0)
{
    f32 lo, a, b;
    s32 idx = FindPathCurveSegmentByLength(self, t0, &lo, 0);
    SampleSplineSegment(self, idx);
    s32 n = FindPathCurveSegment(lo, 20, self->len170, 0, &a, &b);
    f32 t = a / b;
    f32 u = ((f32)n + t) * 0.0526315793f;
    return (1.0f - u) * self->times[idx] + u * self->times[idx + 1];
}

void FillSplinePathLengths(SplinePathCurve* self)
{
    *(s32*)self->lengths = 0;
    s32 m = self->count - 1;
    for (s32 i = 0; i < m; i++) {
        f32 d = self->times[i + 1] - self->times[i];
        s32 off = i * 16;
        f32 r = MeasureCurveSegmentLength((u8*)self->points + off, (u8*)self->outTan + off,
                              (u8*)self->points + (off + 16), (u8*)self->inTan + (off + 16), d, d);
        self->lengths[i + 1] = self->lengths[i] + r;
    }
}

void FindSplinePathNearestPoint(SplinePathCurve* self, Vec02* pos, void* anchor, s32 a3, s32 a4, f32* a5, f32* a6)
{
    Vec02 d;
    s32 best = -1;
    f32 bestDist = 3.4028235e+38f;
    s32 i = self->count;
    while (--i >= 0) {
        f32 dist;
        if (anchor != 0) {
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(*pos), Vu0::Q(((Vec02*)self->points)[i]));
            ConstrainVectorByAnchor(anchor, &d, &d, 0);
            dist = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(d), Vu0::Q(d)));
        } else {
            u128 e = Vu0::Sub(Vu0::Q(*pos), Vu0::Q(((Vec02*)self->points)[i]));
            dist = Vu0::ToFloatMoved(Vu0::Dot(e, e));
        }
        if (dist < bestDist) {
            bestDist = dist;
            best = i;
        }
    }
    FindSplinePathNearestTime(self, (s32)pos, (s32)anchor, a3, a4, a5, a6, self->times[best]);
}

void FindSplinePathNearestTime(SplinePathCurve* self, s32 a1, s32 a2, s32 a3, s32 a4, f32* a5, f32* a6, f32 f12)
{
    NearestTimeQuery ctx;
    NearestTimeResult out;
    f32 f13;
    f32 f14;
    void* fn;

    ctx.curve = self;
    ctx.a = (Vec02*)a1;
    ctx.b = (Vec02*)a2;
    f14 = self->times[0];
    f13 = (self->times[1] - f14) * 0.1f;
    FindLocalMinimum((void*)MeasureSplinePathDistance, f12, f13, self->wrap ? -3.4028235e+38f : f14, self->wrap ? 3.4028235e+38f : self->times[self->count - 1], &ctx, &out, 0);
    if (a3 != 0 || a4 != 0) {
        fn = (void*)self->vt->m01;
        if (fn != 0) {
            ((void (*)(PathCurve*, s32, s32, f32))fn)(self, a3, a4, out.time);
        }
    }
    if (a5 != 0) {
        *a5 = out.time;
    }
    if (a6 != 0) {
        *a6 = self->vt->m05(self, out.time);
    }
}

void ProjectOntoSplinePathNearLength(SplinePathCurve* self, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6)
{
    s32 q4 = p4;
    s32 q3 = p3;
    s32 q2 = p2;
    s32 q1 = p1;
    s32 q6 = p6;
    s32 q5 = p5;
    f32 r = ((CurveTimeFn)self->vt->m06)(self);
    SplineSlot11Fn fn = (SplineSlot11Fn)self->vt->m11;
    if (fn != 0) {
        fn(self, q1, r, q2, q3, q4, q5, q6);
    }
}
