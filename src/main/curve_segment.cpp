// SPDX-License-Identifier: AGPL-3.0-or-later
// 0x130168 to 0x130F48: the curve segment helpers (a Bezier segment solved for its parameter,
// Hermite segments of values and of vectors, two rotations blended with their spins, points
// sampled along a segment and its length, the earliest time within a set of curve limits). Built
// at -mvu0-use-vf0-vf30 (config/cflags.tsv), a threshold of 94 for loop.c, where placed_object.cpp
// before it takes the default (79).
// Evidence: func_00130C58's near miss comes within 6 lines of retail only at N = 29 to 31 (179
// lines at the default), while func_0012CD78 in placed_object.cpp matches only up to N = 25 and
// func_00127B20 up to 21 (docs/toolchain/loops.md, "The threshold by function"); the other
// functions here match at any N.
// Choice: no boundary signal shows the edge; the cut was decided on 2026-11-12 on the threshold
// evidence. By the data it could lie at any function start from 0x12E5D0 to 0x130C58 (.rodata
// from func_00130C58's FLT_MAX at 0x249C90, on 16 after func_0012E4E0's jump table; no .data,
// which placed_object.cpp's functions up to func_0012B760 alone read; no .bss), and N allows any
// start after func_0012CD78. The calls bind nothing to func_00130C58 (its one caller is
// func_0015B7B8, in another file); it is cut where the role changes, from the object helpers
// to the curves.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "mul_rotation.h"
#include "globals.h"

extern void MultiplyMatrices3x3(void*, void*, void*);
extern void MatrixToAxisAngle(void*, void*, void*);

void SampleCurvePoints(s32 a, s32 b, s32 c, s32 d, f32 x, f32 y, f32 z, s32 n, void* buf);
f32 AccumulateSegmentLengths(s32 n, void* buf, s32 zero);

struct SampledCurve;
struct CurvePoint { u8 pad0[16]; };

void EvaluateHermiteVectorSegment(f32 dur, const Vec02* p0, const Vec02* m0, const Vec02* p1, const Vec02* m1, f32 t, f32 k, Vec02* pos, Vec02* vel, Vec02* acc);

void SolveBezierSegment(f32 delta, f32 diff, f32 scale, f32 p4, f32 p18, f32 p1C, f32 p24, f32 p2C, f32 p30, f32* outF, f32* outI, s32 zero)
{
    f32 c[4];
    if (diff < 0.0001f) {
        diff = 0.0f;
    } else if (delta - diff < 0.0001f) {
        diff = 1.0f;
    } else {
        f32 d3 = (delta - p2C) * 3.0f;
        f32 g3 = p18 * 3.0f;
        f32 lo = 0.0f;
        f32 hi = 1.0f;
        s32 k = 0;
        c[2] = g3;
        c[3] = -diff;
        f32 a = g3 - d3;
        f32 b = d3 - g3;
        b = b - g3;
        a = a + delta;
        c[1] = b;
        c[0] = a;
        do {
            f32 m = lo + 1.0f / (f32)(1 << (k + 1));
            f32 v = m * (m * (m * c[0] + c[1]) + c[2]) + c[3];
            if (v < 0.0f) {
                lo = m;
            } else if (0.0f < v) {
                hi = m;
            } else {
                break;
            }
        } while (++k < 16);
        diff = (lo + hi) * 0.5f;
    }
    if (outF != 0) {
        f32 a3 = p1C * 3.0f;
        f32 b3 = p30 * 3.0f;
        c[3] = p4;
        c[0] = a3 - p4 - b3 + p24;
        c[1] = p4 * 3.0f - p1C * 6.0f + b3;
        c[2] = p4 * -3.0f + a3;
        *outF = diff * (diff * (diff * c[0] + c[1]) + c[2]) + p4;
    }
    if (outI != 0) {
        c[0] = p4 * -3.0f + p1C * 9.0f - p30 * 9.0f + p24 * 3.0f;
        c[1] = p4 * 6.0f - p1C * 12.0f + p30 * 6.0f;
        c[2] = p4 * -3.0f + p1C * 3.0f;
        f32 num = diff * (diff * c[0] + c[1]) + c[2];
        f32 d3 = (delta - p2C) * 3.0f;
        f32 g3 = p18 * 3.0f;
        c[2] = g3;
        c[0] = g3 * 3.0f - d3 * 3.0f + delta * 3.0f;
        c[1] = g3 * -4.0f + (d3 + d3);
        f32 den = diff * (diff * c[0] + c[1]) + c[2];
        *outI = num * scale / den;
    }
}

void EvaluateHermiteSegment(f32* p0, f32* p1, f32* p2, f32 dur, f32 t, f32 e, f32 a, f32 b, f32 c, f32 dd)
{
    f32 u = t / dur;
    f32 v = 1.0f - u;
    f32 span = c - a;
    if (p0 != 0) {
        f32 uv = u * v;
        f32 vv = v * v;
        f32 uu = u * u;
        f32 uvv = uv * v;
        f32 vvv = vv * v;
        f32 uuv = uu * v;
        f32 t5 = uvv * 3.0f;
        f32 uvd = uvv * dur;
        f32 t4 = uuv * 3.0f;
        f32 t0 = vvv + t5;
        f32 uuu = uu * u;
        f32 p2b = uvd * b;
        f32 p1a = t0 * a;
        f32 q = uuv * dur;
        f32 t3 = uuu + t4;
        f32 s = p1a + p2b;
        f32 qd = q * dd;
        f32 t3c = t3 * c;
        f32 r = s - qd;
        *p0 = r + t3c;
    }
    if (p1 != 0) {
        f32 t1 = (u * (6.0f * v)) / dur * span;
        f32 t2 = (1.0f - (u * (4.0f - 3.0f * u))) * b;
        f32 w2 = 3.0f * u + -2.0f;
        f32 t3 = (u * w2) * dd;
        *p1 = ((t1 + t2) + t3) * e;
    }
    if (p2 != 0) {
        f32 dd2 = dur * dur;
        f32 ee = e * e;
        f32 s1 = (6.0f - 12.0f * u) / dd2 * span;
        f32 s2 = (6.0f * u - 4.0f) / dur * b;
        f32 s3 = (6.0f * u - 2.0f) / dur * dd;
        *p2 = ((s1 + s2) + s3) * ee;
    }
}

// The cubic Hermite segment from p0 (tangent m0) to p1 (tangent m1) over dur, at time t: the
// point into pos, the velocity (scaled by k) into vel and the acceleration (by k squared)
// into acc, each when given.
void EvaluateHermiteVectorSegment(f32 dur, const Vec02* p0, const Vec02* m0, const Vec02* p1, const Vec02* m1, f32 t, f32 k, Vec02* pos, Vec02* vel, Vec02* acc)
{
    Vec02 d;
    f32 u = t / dur;
    f32 w = 1.0f - u;
    if (pos != 0) {
        f32 uw = u * w;
        f32 uu = u * u;
        f32 ww = w * w;
        f32 uww = uw * w;
        f32 uuw = uu * w;
        f32 www = ww * w;
        Vu0::Q(*pos) = Vu0::MulXSum4(Vu0::Q(*p0), Vu0::Scalar(www + uww * 3.0f), Vu0::Q(*m0), Vu0::Scalar(uww * dur),
                                     Vu0::Q(*m1), Vu0::Scalar(-uuw * dur), Vu0::Q(*p1), Vu0::Scalar(uu * u + uuw * 3.0f));
    }
    if (vel != 0) {
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(*p1), Vu0::Q(*p0));
        Vu0::Q(*vel) = Vu0::MulXSum3(Vu0::Q(d), Vu0::Scalar(u * (6.0f - u * 6.0f) / dur), Vu0::Q(*m0), Vu0::Scalar(1.0f - u * (4.0f - u * 3.0f)),
                               Vu0::Q(*m1), Vu0::Scalar(u * (u * 3.0f + -2.0f)));
        Vu0::Q(*vel) = Vu0::MulX(Vu0::Q(*vel), Vu0::Scalar(k));
    }
    if (acc != 0) {
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(*p1), Vu0::Q(*p0));
        Vu0::Q(*acc) = Vu0::MulXSum3(Vu0::Q(d), Vu0::Scalar((6.0f - u * 12.0f) / dur), Vu0::Q(*m0), Vu0::Scalar(u * 6.0f - 4.0f),
                               Vu0::Q(*m1), Vu0::Scalar(u * 6.0f - 2.0f));
        Vu0::Q(*acc) = Vu0::MulX(Vu0::Q(*acc), Vu0::Scalar(k * k / dur));
    }
}

void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);

// v made unit length where it is, or fallback when shorter than 0.0001: its length.
static inline f32 NormalizeAxis(Vec02& v, const Vec02& fallback)
{
    u128 len = Vu0::Length(Vu0::Q(v));
    if (Vu0::ToFloatMoved(len) < 0.0001f) {
        v = fallback;
    } else {
        Vu0::Q(v) = Vu0::DivX(Vu0::Q(v), len);
    }
    return Vu0::ToFloatMoved(len);
}

void BlendRotationsWithSpin(Mat02* a, Vec02* wa, Mat02* b, Vec02* wb, Mat02* out, Vec02* outW, f32 dur, f32 t, f32 e)
{
    f32 u = t / dur;
    f32 v = 1.0f - u;
    if (out != 0) {
        Vec02 axis;
        Mat02 m1;
        Mat02 m2;
        Mat02 rot;
        f32 uu = u * u;
        f32 uv = u * v;
        f32 uuu = uu * u;
        f32 uuv = uu * v;
        f32 uvv = uv * v;
        f32 len;
        Vu0::Q(axis) = Vu0::Q(*wa);
        len = NormalizeAxis(axis, g_unitZVector);
        BuildAxisAngleMatrix(&axis, &rot, uvv * dur * len);
        MulRotationRowsX(&m1, rot, *a);
        Vu0::Q(axis) = Vu0::Q(*wb);
        len = NormalizeAxis(axis, g_unitZVector);
        BuildAxisAngleMatrix(&axis, &rot, -uuv * dur * len);
        MulRotationRowsX(&m2, rot, *b);
        MultiplyMatrices3x3(&m1, &m2, &rot);
        f32 angle;
        MatrixToAxisAngle(&rot, &angle, &axis);
        BuildAxisAngleMatrix(&axis, &rot, angle * (uuv * (3.0f - dur) + uuu));
        MulRotationRowsX(out, rot, m1);
    }
    if (outW != 0) {
        Mat02 d;
        Vec02 axis;
        f32 angle;
        MultiplyMatrices3x3(a, b, &d);
        MatrixToAxisAngle(&d, &angle, &axis);
        f32 w1 = angle * u * (6.0f - u * 6.0f) / dur;
        f32 w2 = 1.0f - u * (4.0f - u * 3.0f);
        f32 w3 = u * (u * 3.0f + -2.0f);
        Vu0::Q(*outW) = Vu0::MulXSum3(Vu0::Vec::Of(axis), Vu0::Vec::Scalar(w1), Vu0::Vec::Of(*wa), Vu0::Vec::Scalar(w2),
                                      Vu0::Vec::Of(*wb), Vu0::Vec::Scalar(w3)).q;
        Vu0::Q(*outW) = Vu0::MulX(Vu0::Vec::Of(*outW), Vu0::Vec::Scalar(e)).q;
    }
}

void SampleCurvePoints(f32 k, SampledCurve* self, u8* a1, u8* a2, u8* a3, s32 count, CurvePoint* out, f32 start, f32 end)
{
    f32 step = (end - start) / (f32)(count - 1);
    f32 cur = start;
    s32 i;
    for (i = 0; i < count; i++) {
        EvaluateHermiteVectorSegment(k, (const Vec02*)self, (const Vec02*)a1, (const Vec02*)a2, (const Vec02*)a3, cur, 1.0f, (Vec02*)(out + i), 0, 0);
        cur += step;
    }
}

void MeasureCurveSegmentLength(s32 a, s32 b, s32 c, s32 d, f32 x, f32 y)
{
    u8 buf[0x140];
    SampleCurvePoints(a, b, c, d, x, 0.0f, y, 20, buf);
    AccumulateSegmentLengths(20, buf, 0);
}

extern const f32 D_00249C90[4] = { 3.4028235e38f, 0, 0, 0 };

INCLUDE_ASM(func_00130C58);
