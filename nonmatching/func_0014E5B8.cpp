// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 222/240 (92.5%), checked 2026-11-08
// Tried night-close3, 3 compiles: the tangent pointers in other orders and passed inline: worse (12 words).
// NEAR (2026-11-08, vu0w3-e1): all but two scheduling orders: retail adds a3 (inTan + off + 16) before loading a1 (outTan), and loads the unit vector's lq before the mtc1/c.lt of the length test (here in the bc1f delay slot). Tried typed pointers, locals in several orders, the fallback as a local.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "path_curve.h"
#include "shapes.h"
#include "globals.h"
#include "placed_object.h"
#include "vu0.h"

struct NearestTimeQuery {
    PathCurve* curve;       // 0x00
    Vec02* a;               // 0x04
    Vec02* b;               // 0x08
    s32 pad;                // 0x0C
};

struct NearestTimeResult {
    f32 time;               // 0x00
    s32 p1;                 // 0x04
    s32 p2;                 // 0x08
    s32 p3;                 // 0x0C
};

typedef void (*CurveSamplePointFn)(PathCurve* self, Vec02* out, s32 flag);
typedef f32 (*CurveTimeFn)(void* self);
typedef void (*CurveSampleAtFn)(void* self, f32 t, s32 a1, void* a2);
typedef void (*SplineSlot11Fn)(void* self, s32 p1, f32 x, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6);

struct SegmentFraction { s32 idx; f32 t; };

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
void EvaluateHermiteVectorSegment(void* p0, void* t0, void* p1, void* t1, void* a4, void* a5, s32 a6, f32 u, f32 v, f32 w);
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


void SampleSplinePathAtTime(SplinePathCurve* self, f32 t, void* a1, Vec02* a2)
{
    f32 a;
    f32 b;
    s32 i = FindPathCurveSegmentByTime(self, t, &a, &b);
    s32 off = i * 16;
    s32 next = off + 16;
    u8* p0 = (u8*)self->points + off;
    u8* t0 = (u8*)self->outTan + off;
    u8* p1 = (u8*)self->points + next;
    u8* t1 = (u8*)self->inTan + next;
    EvaluateHermiteVectorSegment(p0, t0, p1, t1, a1, a2, 0, b, a, 1.0f);
    if (a2) {
        u128 v = Vu0::Q(*a2);
        u128 fb = Vu0::Q(g_unitXVector);
        Vu0::Q(*a2) = Vu0::NormalizeOr(v, fb);
    }
}

