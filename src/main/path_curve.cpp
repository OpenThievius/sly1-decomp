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
#include "functions/buffered_stream.h"
#include "functions/collider.h"
#include "functions/collider_contact.h"
#include "functions/curve_segment.h"
#include "functions/matrix.h"
#include "functions/path_curve.h"
#include "functions/world.h"
struct PackedColor;
struct ClipPoint;

// What the nearest-time search (func_001EB168) passes its measure: the curve and the two points
// of the segment MeasurePathCurveDistance measures against (FindPathCurveNearestTime,
// FindSplinePathNearestTime).
struct NearestTimeQuery {
    PathCurve* curve;       // 0x00
    Vec4* a;               // 0x04
    Vec4* b;               // 0x08
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
// them, with the time slot 6 returns. Slot 11 is FindSplinePathNearestTime; retail's call sets
// the first pointer before the time ($f12) and the other five after it, the order of this
// type's parameters (the registers are the same in any order).
typedef void (*CurveSamplePointFn)(PathCurve* self, Vec4* out, s32 flag);
typedef void (*CurveSampleAtFn)(void* self, f32 t, void* a1, void* a2);
typedef void (*SplineSlot11Fn)(SplinePathCurve* self, Vec4* a1, f32 t, void* a2, void* a3, void* a4, f32* a5, f32* a6);

// A segment index and the fraction along it (FindNearestPathCurveSegment's two outputs).
struct SegmentFraction { s32 idx; f32 t; };

// An entry of a table of functions.
typedef void (*Fn_Table)();
extern const Fn_Table g_pathCurveKind0Methods[];
extern const Fn_Table g_pathCurveKind1Methods[];

struct CurvePoint;
void SampleCurvePoints(f32 dur, const Vec4* p0, const Vec4* m0, const Vec4* p1, const Vec4* m1, s32 count,
                       CurvePoint* out, f32 start, f32 end);
struct BufferedStream;
struct BufferedStream;
void* AllocateFrontMemory(s32 size);
void* AllocateZeroedFrontMemory(s32 n);
typedef f32 (*MinimumFn)(void* ctx, f32 x);
void FindLocalMinimum(MinimumFn fn, void* ctx, f32 x, f32 step, f32 lo, f32 hi, f32* outX, f32* outY);

void func_0014DB70(void);

// The length of the polyline through n points, giving the total and, when other is not null,
// the running length at each point.
f32 AccumulateSegmentLengths(s32 n, void* buf, void* other)
{
    Vec4* pts = (Vec4*)buf;
    f32* lengths = (f32*)other;
    Vec4 d;
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

// When wrap is set, brings x back into the table's first..last range by adding or subtracting
// the span; otherwise gives x unchanged.
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

// Gives the index of the segment of times arr that contains x (after wrapping it if wrap is set, or
// clamping to the last segment), and writes to lo the time past its start and to hi the segment's
// duration when given.
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

struct VectorConstraint;
extern const Vec4 g_unitXVector;

// Linear interpolation along a polyline of points at time t (using the segment found by
// FindPathCurveSegment): writes the position to pos and the unit direction of the segment (or the x
// axis if it has no length) to tan; either may be null.
void InterpolatePathCurvePoint(f32 t, s32 count, Vec4* points, f32* times, s32 wrap, Vec4* pos, Vec4* tan)
{
    f32 lo;
    f32 hi;
    s32 i = FindPathCurveSegment(t, count, times, wrap, &lo, &hi);
    f32 u = lo / hi;
    if (pos) {
        Vu0::Q(*pos) = Vu0::MulXSum(Vu0::Q(points[i]), Vu0::Scalar(1.0f - u), Vu0::Q(points[i + 1]), Vu0::Scalar(u));
    }
    if (tan) {
        Vu0::Vec d = Vu0::Sub(Vu0::Vec::Of(points[i + 1]), Vu0::Vec::Of(points[i]));
        *(Vu0::Vec*)tan = d;
        *(Vu0::Vec*)tan = Vu0::NormalizeOr(d, Vu0::Vec::Of(g_unitXVector));
    }
}

// The nearest point of a polyline to pos. The direction is stored, then stored again made unit
// length: as Vu0::Vec values, NormalizeOr's argument is a copy the compiler makes (its own
// vmove, a vu0 insn of latency 2), so sched2 issues the length's dot before the first store, as
// retail does (docs/TOOLCHAIN.md, "A compiler copy's latency in sched2").
void FindNearestPathCurveSegment(Vec4* pos, void* anchor, s32 n, Vec4* pts, Vec4* outPoint, Vec4* outDir, s32* outIdx, f32* outT)
{
    s32 best = -1;
    f32 frac = -1.0f;
    f32 bestDist = 3.4028234663852886e+38f;
    s32 count = n - 1;
    for (s32 i = 0; i < count; i++) {
        Vec4 d, pt, e;
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(*pos), Vu0::Q(pts[i]));
        Vu0::Q(e) = Vu0::Sub(Vu0::Q(pts[i + 1]), Vu0::Q(pts[i]));
        if (anchor != 0) {
            ConstrainVectorByAnchor((VectorConstraint*)anchor, &d, &d, 0);
            ConstrainVectorByAnchor((VectorConstraint*)anchor, &e, &e, 0);
        }
        Vu0::Vec ev = Vu0::Vec::Of(e);
        Vu0::Vec len = Vu0::Length(ev);
        f32 lenF = Vu0::ToFloatMoved(len);
        Vu0::Vec unit;
        unit.q = Vu0::DivX(ev.q, len.q);
        {
            Vec4 e0;
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

// The point at the fraction along the polyline nearest pos, walking from segment idx backwards or
// forwards (wrapping when wrap is set), and the segment's unit direction. As in func_0014D3A8, the
// vectors are Vu0::Vec values: the loop is then big enough at the loop pass that loop.c hoists
// only &d (its life is long enough) and leaves n - 2 and 0.0f in the loop, and the address is
// set before the loop's NOTE_INSN_LOOP_BEG, so sched2 interleaves it with the saves
// (docs/TOOLCHAIN.md, "Loops").
void WalkToNearestPathCurveSegment(Vec4* pos, void* anchor, s32 n, Vec4* pts, s32 idx, s32 wrap, Vec4* outPoint, Vec4* outDir, s32* outIdx, f32* outT)
{
    s32 back = 0;
    s32 fwd = 0;
    f32 frac;
    Vec4 e;
    for (;;) {
        Vec4 d, e0;
        *(Vu0::Vec*)&d = Vu0::Sub(Vu0::Vec::Of(*pos), Vu0::Vec::Of(pts[idx]));
        *(Vu0::Vec*)&e = Vu0::Sub(Vu0::Vec::Of(pts[idx + 1]), Vu0::Vec::Of(pts[idx]));
        if (anchor != 0) {
            ConstrainVectorByAnchor((VectorConstraint*)anchor, &d, &d, 0);
            ConstrainVectorByAnchor((VectorConstraint*)anchor, &e, &e, 0);
        }
        Vu0::Vec ev = Vu0::Vec::Of(e);
        Vu0::Vec len = Vu0::Length(ev);
        f32 lenF = Vu0::ToFloatMoved(len);
        Vu0::Vec unit;
        unit.q = Vu0::DivX(ev.q, len.q);
        f32 t = Vu0::ToFloat(Vu0::Dot(unit, Vu0::Vec::Of(d)));
        *(Vu0::Vec*)&e0 = ev;
        *(Vu0::Vec*)&e = unit;
        if (t < 0.0f) {
            if (fwd != 0) {
                frac = 0.0f;
                break;
            }
            if (idx > 0) {
                idx--;
            } else if (wrap != 0) {
                idx = n - 2;
            } else {
                frac = 0.0f;
                break;
            }
            back = 1;
            continue;
        }
        if (!(lenF < t)) {
            frac = t / lenF;
            break;
        }
        if (back != 0) {
            frac = 1.0f;
            break;
        }
        if (idx < n - 2) {
            idx++;
        } else if (wrap != 0) {
            idx = 0;
        } else {
            frac = 1.0f;
            break;
        }
        fwd = 1;
    }
    if (outIdx != 0) {
        *outIdx = idx;
    }
    if (outT != 0) {
        *outT = frac;
    }
    if (outPoint != 0) {
        Vu0::Q(*outPoint) = Vu0::MulXSum(Vu0::Q(pts[idx]), Vu0::Scalar(1.0f - frac), Vu0::Q(pts[idx + 1]), Vu0::Scalar(frac));
    }
    if (outDir != 0) {
        Vu0::Vec dir = Vu0::Sub(Vu0::Vec::Of(pts[idx + 1]), Vu0::Vec::Of(pts[idx]));
        *(Vu0::Vec*)outDir = dir;
        *(Vu0::Vec*)outDir = Vu0::NormalizeOr(dir, Vu0::Vec::Of(g_unitXVector));
    }
}

// Transforms count points in place by the matrix of an object (TransformMatrixByObject), as
// positions (w = 1).
void TransformPointArray(s32 count, Quad16* dst, void* arg, void* self)
{
    Quad16 mat[4];
    Quad16 tmp;

    TransformMatrixByObject((u8*)self, arg, mat);
    if (count > 0) {
        do {
            TransformByMatrixWithW(mat, (Vec4*)dst, 1.0f, (Vec4*)&tmp);
            *dst = tmp;
            dst++;
            count--;
        } while (count != 0);
    }
}

// Allocates a path curve of kind 0 (a polyline, 0x1C bytes) or kind 1 (a spline, 0x1D0 bytes)
// with its method table; any other kind gives null.
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

// The base curve method for the length at a time: 0 (the kinds override it).
f32 GetBaseCurveLengthAtTime(void)
{
    return 0.0f;
}

// The base curve method for the time at a length: 0 (the kinds override it).
f32 GetBaseCurveTimeAtLength(void)
{
    return 0.0f;
}

// The segment that time t falls in and the fraction of it, by the time table (wrapping when the
// curve wraps).
s32 FindPathCurveSegmentByTime(PathCurve* self, f32 t, f32* a, f32* b)
{
    return FindPathCurveSegment(t, self->count, self->times, self->wrap, a, b);
}

// The segment that arc length t falls in and the fraction of it, by the length table.
s32 FindPathCurveSegmentByLength(PathCurve* self, f32 t, f32* a1, f32* a2)
{
    return FindPathCurveSegment(t, self->count, self->lengths, self->wrap, a1, a2);
}

// The squared distance from the curve's sampled point to the query's point a, with the
// difference constrained by the anchor b first when there is one. Each branch returns its own
// conversion: sched2 then schedules the mtc1 inside each branch, ahead of the epilogue's
// restores, and jump2's cross-jumping merges the two tails afterwards (docs/TOOLCHAIN.md).
f32 MeasureSplinePathDistance(NearestTimeQuery* self)
{
    Vec4 p;
    Vec4 d;
    if (self->curve->vt->m01)
        ((CurveSamplePointFn)self->curve->vt->m01)(self->curve, &p, 0);
    if (self->b != 0) {
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(p), Vu0::Q(*self->a));
        ConstrainVectorByAnchor((VectorConstraint*)self->b, &d, &d, 0);
        return Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(d), Vu0::Q(d)));
    }
    u128 e = Vu0::Sub(Vu0::Q(p), Vu0::Q(*self->a));
    return Vu0::ToFloatMoved(Vu0::Dot(e, e));
}

// The curve's last key time.
f32 GetPathCurveEndTime(PathCurve* obj) { u32 address = obj->count * 4 + (u32)obj->times; return *(f32*)(address - 4); }

// The curve's total length (the last entry of the length table).
f32 GetPathCurveEndLength(PathCurve* obj) { u32 address = obj->count * 4 + (u32)obj->lengths; return *(f32*)(address - 4); }

LINKER_REMNANT(func_0014DB70);

// The distance from the query's point to its segment a..b, measured from the curve's sample
// (slot 1 of its table); used when searching for the nearest time.
f32 MeasurePathCurveDistance(NearestTimeQuery* self)
{
    Vec4 p;
    f32 o1;
    f32 o2;
    if (self->curve->vt->m01)
        ((CurveSamplePointFn)self->curve->vt->m01)(self->curve, &p, 0);
    MeasurePointToSegment(&p, self->a, self->b, &o1, &o2);
    return o2;
}

// Finds the time at which the path curve is closest to the segment a1, a2, by a local minimum
// search from the time f12 (initial step a tenth of the first interval, limited to the curve's
// times unless it wraps). Gives the curve's position and direction there (a3, a4) by method 1, the
// time (a5) and its length along the curve (a6).
void FindPathCurveNearestTime(PathCurve* self, Vec4* a1, Vec4* a2, Vec4* a3, Vec4* a4, f32* a5, f32* a6, f32 f12)
{
    NearestTimeQuery ctx;
    NearestTimeResult out;
    f32 f13;
    f32 f14;
    void* fn;

    ctx.curve = self;
    ctx.a = a1;
    ctx.b = a2;
    f14 = self->times[0];
    f13 = (self->times[1] - f14) * 0.1f;
    FindLocalMinimum((MinimumFn)MeasurePathCurveDistance, &ctx, f12, f13, self->wrap ? -3.4028235e+38f : f14, self->wrap ? 3.4028235e+38f : self->times[self->count - 1], (f32*)&out, 0);
    if (a3 != 0 || a4 != 0) {
        fn = (void*)self->vt->m01;
        if (fn != 0) {
            ((void (*)(PathCurve*, Vec4*, Vec4*, f32))fn)(self, a3, a4, out.time);
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

// The step for searches along the curve: a tenth of the first key interval.
f32 GetPathCurveSearchStep(PathCurve* self)
{
    f32* p = self->times;
    f32 b = p[1]; f32 a = p[0]; return (b - a) * 0.1f;
}

// Reads a polyline path from the stream: the wrap flag, the point count, and each point's time and
// position; then calls the curve's method 9 (which fills the lengths).
void ReadPathCurve(PathCurve* self, void* src)
{
    self->wrap = ReadBufferedU8((BufferedStream*)src);
    s32 n = ReadBufferedU8((BufferedStream*)src);
    self->count = n;
    self->times = (f32*)AllocateFrontMemory(n * 4);
    self->lengths = (f32*)AllocateFrontMemory(self->count * 4);
    self->points = AllocateFrontMemory(self->count * 16);
    for (s32 i = 0; i < self->count; i++) {
        self->times[i] = ReadBufferedFloat((BufferedStream*)src);
        ReadBufferedVector3((BufferedStream*)src, (u8*)self->points + i * 16);
    }
    f32 (*fn)(PathCurve*) = self->vt->m09;
    if (fn) fn(self);
}

// The position and tangent of the curve at time t (interpolated between the keys).
void SamplePathCurveAtTime(PathCurve* self, f32 t, Vec4* pos, Vec4* tan)
{
    InterpolatePathCurvePoint(t, self->count, (Vec4*)self->points, self->times, self->wrap, pos, tan);
}

// The position and tangent of the curve at arc length t.
void SamplePathCurveAtLength(PathCurve* self, f32 t, Vec4* pos, Vec4* tan)
{
    InterpolatePathCurvePoint(t, self->count, (Vec4*)self->points, self->lengths, self->wrap, pos, tan);
}

// Draws one segment of the path curve as a line from point idx to the next one (the first one, when
// wrap is set, for the last; otherwise nothing), with the points transformed by the matrix a2, in
// the colour a4.
void DrawPathCurveSegment(PathCurve* self, s32 idx, void* a2, u8* a3, void* a4, s32 a5)
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
    TransformByMatrixWithW((const Quad16*)a2, (const Vec4*)((u8*)self->points + (idx << 4)), 1.0f, (Vec4*)&A);
    TransformByMatrixWithW((const Quad16*)a2, (const Vec4*)((u8*)self->points + (next << 4)), 1.0f, (Vec4*)&B);
    C = *(U32P*)a4;
    DrawProjectedLine((ClipPoint*)&A, (ClipPoint*)&B, (PackedColor*)&C, a3, a5);
}

// Transforms all the curve's points by an object's matrix (TransformPointArray).
void TransformPathCurvePoints(PathCurve* self,void* a,void* b) { TransformPointArray(self->count,(Quad16*)self->points,a,b); }

// The arc length at time t0, interpolating the length table linearly between keys.
f32 GetPathCurveLengthAtTime(PathCurve* self, f32 t0)
{
    f32 a, b;
    s32 i = FindPathCurveSegmentByTime(self, t0, &a, &b);
    f32 t = a / b;
    return (1.0f - t) * self->lengths[i] + t * self->lengths[i + 1];
}

// The time at which the curve has run arc length t0, interpolating the time table linearly.
f32 GetPathCurveTimeAtLength(PathCurve* self, f32 t0)
{
    f32 lo, hi;
    s32 idx = FindPathCurveSegmentByLength(self, t0, &lo, &hi);
    f32 t = lo / hi;
    return (1.0f - t) * self->times[idx] + t * self->times[idx + 1];
}

// Fills the curve's length table from its points and gives back the total length.
f32 FillPathCurveLengths(PathCurve* self)
{
    return AccumulateSegmentLengths(self->count, self->points, self->lengths);
}

// Finds the point of the path curve nearest to the segment a1, a2 (outputs a3 and a4 are those of
// FindNearestPathCurveSegment) and gives its time (out0) and its length along the curve (out1),
// interpolated between the segment's two points.
void FindPathCurveNearestPoint(PathCurve* self, void* a1, void* a2, void* a3, void* a4, f32* out0, f32* out1)
{
    SegmentFraction f;
    FindNearestPathCurveSegment((Vec4*)a1, a2, self->count, (Vec4*)self->points, (Vec4*)a3, (Vec4*)a4, &f.idx, &f.t);
    if (out1) {
        *out1 = (1.0f - f.t) * self->lengths[f.idx] + f.t * self->lengths[f.idx + 1];
    }
    if (out0) {
        *out0 = (1.0f - f.t) * self->times[f.idx] + f.t * self->times[f.idx + 1];
    }
}

// Finds the point of the path curve nearest to the given segment (a1, a2), looking from the segment
// of time t outwards, and gives its position and direction (a3, a4) and its time (a5) and length
// along the curve (a6), interpolated between the two points of the segment found.
void ProjectOntoPathCurveNearTime(PathCurve* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6)
{
    s32 idx = FindPathCurveSegment(t, self->count, self->times, self->wrap, 0, 0);
    s32 ia;
    f32 fb;
    WalkToNearestPathCurveSegment((Vec4*)a1, a2, self->count, (Vec4*)self->points, idx, self->wrap, (Vec4*)a3, (Vec4*)a4, &ia, &fb);
    if (a6) *a6 = (1.0f - fb) * self->lengths[ia] + fb * self->lengths[ia + 1];
    if (a5) *a5 = (1.0f - fb) * self->times[ia] + fb * self->times[ia + 1];
}

// The same as ProjectOntoPathCurveNearTime, but the starting segment is the one at length t along
// the curve rather than at time t.
void ProjectOntoPathCurveNearLength(PathCurve* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6)
{
    s32 idx = FindPathCurveSegment(t, self->count, self->lengths, self->wrap, 0, 0);
    s32 ia;
    f32 fb;
    WalkToNearestPathCurveSegment((Vec4*)a1, a2, self->count, (Vec4*)self->points, idx, self->wrap, (Vec4*)a3, (Vec4*)a4, &ia, &fb);
    if (a6) *a6 = (1.0f - fb) * self->lengths[ia] + fb * self->lengths[ia + 1];
    if (a5) *a5 = (1.0f - fb) * self->times[ia] + fb * self->times[ia + 1];
}

// Reads a spline path from the stream: the wrap flag, the point count, and for each point its time,
// position, in tangent and out tangent. Calls the curve's method 9 (which fills the lengths) and
// resets the segment cache.
void ReadSplinePathCurve(SplinePathCurve* self, void* src)
{
    self->wrap = ReadBufferedU8((BufferedStream*)src);
    s32 n = ReadBufferedU8((BufferedStream*)src);
    self->count = n;
    self->times = (f32*)AllocateFrontMemory(n * 4);
    self->lengths = (f32*)AllocateFrontMemory(self->count * 4);
    self->points = AllocateFrontMemory(self->count * 16);
    self->inTan = AllocateFrontMemory(self->count * 16);
    self->outTan = AllocateFrontMemory(self->count * 16);
    for (s32 i = 0; i < self->count; i++) {
        self->times[i] = ReadBufferedFloat((BufferedStream*)src);
        ReadBufferedVector3((BufferedStream*)src, (u8*)self->points + i * 16);
        ReadBufferedVector3((BufferedStream*)src, (u8*)self->inTan + i * 16);
        ReadBufferedVector3((BufferedStream*)src, (u8*)self->outTan + i * 16);
    }
    f32 (*fn)(PathCurve*) = self->vt->m09;
    if (fn) fn(self);
    ResetSplineSegmentCache(self);
}

// Forgets which segment the spline has sampled, so the next SampleSplineSegment samples again.
void ResetSplineSegmentCache(SplinePathCurve* obj) { obj->idx1C0 = -1; }

// Samples segment i of the spline at 20 points into its cache and totals their lengths, unless
// segment i is already the cached one.
void SampleSplineSegment(SplinePathCurve* self, s32 i)
{
    if (i != self->idx1C0) {
        f32 d = self->times[i + 1] - self->times[i];
        s32 off = i * 16;
        SampleCurvePoints(d, (const Vec4*)((u8*)self->points + off), (const Vec4*)((u8*)self->outTan + off), (const Vec4*)((u8*)self->points + (off + 16)), (const Vec4*)((u8*)self->inTan + (off + 16)), 20, (CurvePoint*)self->pts30, 0.0f, d);
        AccumulateSegmentLengths(20, self->pts30, self->len170);
        self->idx1C0 = i;
    }
}


// Evaluates the spline path at time t: finds its segment, evaluates the Hermite segment between its
// points and tangents (outputs to a1), and writes the normalised direction (the x axis if zero) to
// a2 if given.
void SampleSplinePathAtTime(SplinePathCurve* self, f32 t, void* a1, Vec4* a2)
{
    f32 a;
    f32 b;
    s32 i = FindPathCurveSegmentByTime(self, t, &a, &b);
    s32 off = i * 16;
    s32 next = off + 16;
    EvaluateHermiteVectorSegment(b, (const Vec4*)((u8*)self->points + off), (const Vec4*)((u8*)self->outTan + off), (const Vec4*)((u8*)self->points + next), (const Vec4*)((u8*)self->inTan + next), a, 1.0f, (Vec4*)a1, a2, 0);
    if (a2) {
        u128 v = Vu0::Q(*a2);
        u128 fb = Vu0::Q(g_unitXVector);
        Vu0::Q(*a2) = Vu0::NormalizeOrMoved(v, fb);
    }
}

// Samples the spline at the arc length given: converts it to a time (slot 6, the length passed
// on in $f12) and calls the sampling slot 1 with it.
void SampleSplinePathAtLength(SplinePathCurve* self, f32 length, void* a1, void* a2)
{
    f32 t = self->vt->m06(self, length);
    CurveSampleAtFn fn = (CurveSampleAtFn)self->vt->m01;
    if (fn) {
        fn(self, t, a1, a2);
    }
}

// The segment from key idx to the next as a curve through the matrix m: its two points and
// their tangents, drawn in the color at a4.
void DrawSplinePathSegment(SplinePathCurve* self, s32 idx, Quad16* m, u8* a3, void* a4)
{
    Vec4 a;
    Vec4 b;
    Vec4 ta;
    Vec4 tb;
    if (idx != self->count - 1) {
        s32 next = idx + 1;
        f32 dt = self->times[next] - self->times[idx];
        Vu0::Q(a) = Vu0::Transform(*m, Vu0::Q(((Vec4*)self->points)[idx]), 1.0f);
        Vu0::Q(b) = Vu0::Transform(*m, Vu0::Q(((Vec4*)self->points)[idx + 1]), 1.0f);
        Vu0::Q(ta) = Vu0::Rotate(*m, Vu0::Q(((Vec4*)self->outTan)[idx]));
        Vu0::Q(tb) = Vu0::Rotate(*m, Vu0::Q(((Vec4*)self->inTan)[idx + 1]));
        U32P color = *(U32P*)a4;
        DrawProjectedCurve(&a, &ta, &b, &tb, &color, a3, 1, dt);
    }
}

// Transforms every point of the spline path by the matrix that takes the frame of object a to that
// of b, rotating the tangents too, and resets the segment cache.
void TransformSplinePathPoints(SplinePathCurve* self, void* a, void* b)
{
    Vec4 m[4];
    s32 i;
    TransformMatrixByObject((u8*)b, a, (Quad16*)m);
    Mat3* rot = (Mat3*)m;
    for (i = 0; i < self->count; i++) {
        u8* p = (u8*)self->points + (i << 4);
        TransformByMatrixWithW((const Quad16*)m, (const Vec4*)p, 1.0f, (Vec4*)p);
        Vu0::Q(((Vec4*)self->inTan)[i]) = Vu0::Rotate(*rot, Vu0::Q(((Vec4*)self->inTan)[i]));
        Vu0::Q(((Vec4*)self->outTan)[i]) = Vu0::Rotate(*rot, Vu0::Q(((Vec4*)self->outTan)[i]));
    }
    ResetSplineSegmentCache(self);
}

// The arc length of the spline up to time t0: the table's value at the segment start plus the
// part of the segment before t0.
f32 GetSplineLengthAtTime(SplinePathCurve* self, f32 t0)
{
    f32 a, b;
    s32 i = FindPathCurveSegmentByTime(self, t0, &a, &b);
    u32 off = i * 16;
    f32 r = MeasureCurveSegmentLength((const Vec4*)((u8*)self->points + off), (const Vec4*)((u8*)self->outTan + off),
                          (const Vec4*)((u8*)self->points + (off + 16)), (const Vec4*)((u8*)self->inTan + (off + 16)), b, a);
    return r + self->lengths[i];
}

// The curve time at which the spline has run the given arc length: finds the segment, samples it
// at 20 points and interpolates inside the sampled lengths.
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

// Fills the spline's cumulative length table: the length of each Hermite segment (between
// consecutive points, with their tangents, over the segment's time span) added to the last.
void FillSplinePathLengths(SplinePathCurve* self)
{
    *(s32*)self->lengths = 0;
    s32 m = self->count - 1;
    for (s32 i = 0; i < m; i++) {
        f32 d = self->times[i + 1] - self->times[i];
        s32 off = i * 16;
        f32 r = MeasureCurveSegmentLength((const Vec4*)((u8*)self->points + off), (const Vec4*)((u8*)self->outTan + off),
                              (const Vec4*)((u8*)self->points + (off + 16)), (const Vec4*)((u8*)self->inTan + (off + 16)), d, d);
        self->lengths[i + 1] = self->lengths[i] + r;
    }
}

// Finds the point of the spline path nearest to pos: first the control point with the smallest
// squared distance (optionally with the difference constrained by an anchor), then the nearest time
// is refined from that point's time with FindSplinePathNearestTime. The outputs a3..a6 are those of
// that function.
void FindSplinePathNearestPoint(SplinePathCurve* self, Vec4* pos, void* anchor, void* a3, void* a4, f32* a5, f32* a6)
{
    Vec4 d;
    s32 best = -1;
    f32 bestDist = 3.4028235e+38f;
    s32 i = self->count;
    while (--i >= 0) {
        f32 dist;
        if (anchor != 0) {
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(*pos), Vu0::Q(((Vec4*)self->points)[i]));
            ConstrainVectorByAnchor((VectorConstraint*)anchor, &d, &d, 0);
            dist = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(d), Vu0::Q(d)));
        } else {
            u128 e = Vu0::Sub(Vu0::Q(*pos), Vu0::Q(((Vec4*)self->points)[i]));
            dist = Vu0::ToFloatMoved(Vu0::Dot(e, e));
        }
        if (dist < bestDist) {
            bestDist = dist;
            best = i;
        }
    }
    FindSplinePathNearestTime(self, pos, anchor, a3, a4, a5, a6, self->times[best]);
}

// The spline version of FindPathCurveNearestTime: a local minimum search from time f12 of the
// distance measured by MeasureSplinePathDistance, then the position and direction (a3, a4), the
// time (a5) and the length (a6) at the minimum.
void FindSplinePathNearestTime(SplinePathCurve* self, Vec4* a1, void* a2, void* a3, void* a4, f32* a5, f32* a6, f32 f12)
{
    NearestTimeQuery ctx;
    NearestTimeResult out;
    f32 f13;
    f32 f14;
    void* fn;

    ctx.curve = self;
    ctx.a = a1;
    ctx.b = (Vec4*)a2;
    f14 = self->times[0];
    f13 = (self->times[1] - f14) * 0.1f;
    FindLocalMinimum((MinimumFn)MeasureSplinePathDistance, &ctx, f12, f13, self->wrap ? -3.4028235e+38f : f14, self->wrap ? 3.4028235e+38f : self->times[self->count - 1], (f32*)&out, 0);
    if (a3 != 0 || a4 != 0) {
        fn = (void*)self->vt->m01;
        if (fn != 0) {
            ((void (*)(PathCurve*, void*, void*, f32))fn)(self, a3, a4, out.time);
        }
    }
    if (a5 != 0) {
        *a5 = out.time;
    }
    if (a6 != 0) {
        *a6 = self->vt->m05(self, out.time);
    }
}

// Calls slot 11 of the curve's table (if it has one) with the time of the length given (slot 6)
// and the six other arguments passed on unchanged.
void ProjectOntoSplinePathNearLength(SplinePathCurve* self, f32 length, Vec4* a1, void* a2, void* a3, void* a4, f32* a5, f32* a6)
{
    f32 t = self->vt->m06(self, length);
    SplineSlot11Fn fn = (SplineSlot11Fn)self->vt->m11;
    if (fn != 0) {
        fn(self, a1, t, a2, a3, a4, a5, a6);
    }
}
