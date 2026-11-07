// SPDX-License-Identifier: AGPL-3.0-or-later
// Curves: piecewise-linear and spline tracks of keyed values (two kinds, made by func_0014D9A8,
// with the method tables D_002176D0 and D_00217708), and the segment-length and lookup helpers.
#include "common.h"
#include "asm_func.h"
#include "path_curve.h"
#include "shapes.h"

struct __attribute__((aligned(16))) Vec_14DB78 { f32 v[4]; };
struct Src_14DB78;
struct VT_14DB78 {
    void* slot0;
    void (*f4)(Src_14DB78* self, Vec_14DB78* out, s32 flag);
};
struct Src_14DB78 { VT_14DB78* vt; };
struct Obj_14DB78 {
    Src_14DB78* src;
    Vec_14DB78* a;
    Vec_14DB78* b;
};

struct Ctx_14DBD0 { PathCurve* self; s32 a1; s32 a2; s32 pad; };
struct Out_14DBD0 { f32 f; s32 p1; s32 p2; s32 p3; };

struct __attribute__((aligned(16))) Quad_0014DE78 { s32 v[4]; };
struct __attribute__((packed)) Pack4_0014DE78 { s32 v; };
struct Frac_14E090 { s32 idx; f32 t; };
typedef f32 (*Fn_14E6A8)(void* self);
typedef void (*Fn2_14E6A8)(void* self, f32 t, s32 a1, void* a2);

struct Ctx_14EC70 { PathCurve* self; s32 a1; s32 a2; s32 pad; };
struct Out_14EC70 { f32 f; s32 p1; s32 p2; s32 p3; };

typedef f32 (*Slot6_14ED98)(void* self);
typedef void (*Slot11_14ED98)(void* self, s32 p1, f32 x, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6);

// An entry of a table of functions.
typedef void (*Fn_Table)();
extern const Fn_Table D_002176D0[];
extern const Fn_Table D_00217708[];

f32 func_00130C20(void* p0, void* p1, void* p2, void* p3, f32 x, f32 y);
void func_00130B48(void* a, void* b, void* c, void* d, f32 x, f32 y, f32 z, s32 n, void* buf);
s32 func_00137B90(void* src);
f32 func_00137DF8(void* src);
void func_00137E70(void* src, void* dst);
void func_00186320(Vec_14DB78* p, Vec_14DB78* a, Vec_14DB78* b, f32* o1, f32* o2);
void func_00188700(void* a, void* b, void* c, f32 w);
void func_001891C0(void* self, void* arg, Quad16* out);
void* func_0018D500(s32 size);
void* func_0018D5C0(u32 n);
void func_001DD3E0(void* a, void* b, void* c, s32 d, s32 e);
void func_001EB168(void* fn, f32 f12, f32 f13, f32 f14, f32 f15, void* ctx, void* out, s32 a3);

f32 func_0014D0A8(s32 n, void* buf, void* other);
f32 func_0014D138(s32 count, f32* table, s32 wrap, f32 x);
s32 func_0014D1A0(f32 x, s32 n, f32* arr, s32 wrap, f32* lo, f32* hi);
void func_0014D280(s32 count, void* points, f32* times, s32 wrap, s32 a4, s32 a5);
void func_0014D3A8(void* a0, void* a1, s32 count, void* a3, void* a4, void* a5, s32* outIdx, f32* outT);
void func_0014D680(void* a0, void* a1, s32 a2, void* a3, s32 idx, s32 a5, f32* a6, f32* a7, s32* p9, f32* p10);
void func_0014D938(s32 count, Quad16* dst, void* arg, void* self);
PathCurve* func_0014D9A8(s32 kind);
f32 func_0014DA18(void);
f32 func_0014DA28(void);
s32 func_0014DA38(PathCurve* self, f32 t, f32* a, f32* b);
s32 func_0014DA68(PathCurve* self, f32 t, f32* a1, f32* a2);
void func_0014DA98(void);
f32 func_0014DB40(PathCurve* obj);
f32 func_0014DB58(PathCurve* obj);
void func_0014DB70(void);
f32 func_0014DB78(Obj_14DB78* self);
void func_0014DBD0(PathCurve* self, s32 a1, s32 a2, s32 a3, s32 a4, f32* a5, f32* a6, f32 f12);
f32 func_0014DD00(PathCurve* self);
void func_0014DD28(PathCurve* self, void* src);
void func_0014DE08(PathCurve* self, s32 a1, s32 a2);
void func_0014DE40(PathCurve* self, s32 a1, s32 a2);
void func_0014DE78(PathCurve* self, s32 idx, void* a2, s32 a3, void* a4, s32 a5);
void func_0014DF68(PathCurve* self, void* a, void* b);
f32 func_0014DF98(PathCurve* self, f32 t);
f32 func_0014E000(PathCurve* self, f32 t);
f32 func_0014E068(PathCurve* self);
void func_0014E090(PathCurve* self, void* a1, void* a2, void* a3, void* a4, f32* out0, f32* out1);
void func_0014E170(PathCurve* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6);
void func_0014E2A0(PathCurve* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6);
void func_0014E3D0(SplinePathCurve* self, void* src);
void func_0014E500(SplinePathCurve* obj);
void func_0014E510(SplinePathCurve* self, s32 i);
void func_0014E6A8(SplinePathCurve* self, s32 a1, void* a2);
f32 func_0014E910(SplinePathCurve* self, f32 t);
f32 func_0014E990(SplinePathCurve* self, f32 t);
void func_0014EA48(SplinePathCurve* self);
void func_0014EC70(SplinePathCurve* self, s32 a1, s32 a2, s32 a3, s32 a4, f32* a5, f32* a6, f32 f12);
void func_0014ED98(SplinePathCurve* self, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6);

ASM_FUNC(func_0014D0A8);

f32 func_0014D138(s32 count, f32* table, s32 wrap, f32 x)
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

s32 func_0014D1A0(f32 x, s32 n, f32* arr, s32 wrap, f32* lo, f32* hi)
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

ASM_FUNC(func_0014D280);

INCLUDE_RODATA(D_00249FBC);
ASM_FUNC(func_0014D3A8);

ASM_FUNC(func_0014D680);

void func_0014D938(s32 count, Quad16* dst, void* arg, void* self)
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

PathCurve* func_0014D9A8(s32 kind)
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

f32 func_0014DA18(void)
{
    return 0.0f;
}

f32 func_0014DA28(void)
{
    return 0.0f;
}

s32 func_0014DA38(PathCurve* self, f32 t, f32* a, f32* b)
{
    return FindPathCurveSegment(t, self->count, self->times, self->wrap, a, b);
}

s32 func_0014DA68(PathCurve* self, f32 t, f32* a1, f32* a2)
{
    return FindPathCurveSegment(t, self->count, self->lengths, self->wrap, a1, a2);
}

ASM_FUNC(func_0014DA98);

f32 func_0014DB40(PathCurve* obj) { u32 address = obj->count * 4 + (u32)obj->times; return *(f32*)(address - 4); }

f32 func_0014DB58(PathCurve* obj) { u32 address = obj->count * 4 + (u32)obj->lengths; return *(f32*)(address - 4); }

LINKER_REMNANT(func_0014DB70);

f32 func_0014DB78(Obj_14DB78* self)
{
    Vec_14DB78 p;
    f32 o1;
    f32 o2;
    if (self->src->vt->f4)
        self->src->vt->f4(self->src, &p, 0);
    MeasurePointToSegment(&p, self->a, self->b, &o1, &o2);
    return o2;
}

void func_0014DBD0(PathCurve* self, s32 a1, s32 a2, s32 a3, s32 a4, f32* a5, f32* a6, f32 f12)
{
    Ctx_14DBD0 ctx;
    Out_14DBD0 out;
    f32 f13;
    f32 f14;
    void* fn;

    ctx.self = self;
    ctx.a1 = a1;
    ctx.a2 = a2;
    f14 = self->times[0];
    f13 = (self->times[1] - f14) * 0.1f;
    func_001EB168((void*)MeasurePathCurveDistance, f12, f13, self->wrap ? -3.4028235e+38f : f14, self->wrap ? 3.4028235e+38f : self->times[self->count - 1], &ctx, &out, 0);
    if (a3 != 0 || a4 != 0) {
        fn = (void*)self->vt->m01;
        if (fn != 0) {
            ((void (*)(PathCurve*, s32, s32, f32))fn)(self, a3, a4, out.f);
        }
    }
    if (a5 != 0) {
        *a5 = out.f;
    }
    if (a6 != 0) {
        *a6 = self->vt->m05(self, out.f);
    }
}

LINKER_REMNANT(func_0014DCF8);

f32 func_0014DD00(PathCurve* self)
{
    f32* p = self->times;
    f32 b = p[1]; f32 a = p[0]; return (b - a) * 0.1f;
}

void func_0014DD28(PathCurve* self, void* src)
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

void func_0014DE08(PathCurve* self, s32 a1, s32 a2)
{
    InterpolatePathCurvePoint(self->count, self->points, self->times, self->wrap, a1, a2);
}

void func_0014DE40(PathCurve* self, s32 a1, s32 a2)
{
    InterpolatePathCurvePoint(self->count, self->points, self->lengths, self->wrap, a1, a2);
}

void func_0014DE78(PathCurve* self, s32 idx, void* a2, s32 a3, void* a4, s32 a5)
{
    Quad_0014DE78 A;
    Quad_0014DE78 B;
    Pack4_0014DE78 C;
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
    C = *(Pack4_0014DE78*)a4;
    DrawProjectedLine(&A, &B, &C, a3, a5);
}

void func_0014DF68(PathCurve* self,void* a,void* b) { TransformPointArray(self->count,(Quad16*)self->points,a,b); }

f32 func_0014DF98(PathCurve* self, f32 t0)
{
    f32 a, b;
    s32 i = FindPathCurveSegmentByTime(self, t0, &a, &b);
    f32 t = a / b;
    return (1.0f - t) * self->lengths[i] + t * self->lengths[i + 1];
}

f32 func_0014E000(PathCurve* self, f32 t0)
{
    f32 lo, hi;
    s32 idx = FindPathCurveSegmentByLength(self, t0, &lo, &hi);
    f32 t = lo / hi;
    return (1.0f - t) * self->times[idx] + t * self->times[idx + 1];
}

f32 func_0014E068(PathCurve* self)
{
    return AccumulateSegmentLengths(self->count, self->points, self->lengths);
}

void func_0014E090(PathCurve* self, void* a1, void* a2, void* a3, void* a4, f32* out0, f32* out1)
{
    Frac_14E090 f;
    FindNearestPathCurveSegment(a1, a2, self->count, self->points, a3, a4, &f.idx, &f.t);
    if (out1) {
        *out1 = (1.0f - f.t) * self->lengths[f.idx] + f.t * self->lengths[f.idx + 1];
    }
    if (out0) {
        *out0 = (1.0f - f.t) * self->times[f.idx] + f.t * self->times[f.idx + 1];
    }
}

void func_0014E170(PathCurve* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6)
{
    s32 idx = FindPathCurveSegment(t, self->count, self->times, self->wrap, 0, 0);
    s32 ia;
    f32 fb;
    WalkToNearestPathCurveSegment(a1, a2, self->count, self->points, idx, self->wrap, a3, a4, &ia, &fb);
    if (a6) *a6 = (1.0f - fb) * self->lengths[ia] + fb * self->lengths[ia + 1];
    if (a5) *a5 = (1.0f - fb) * self->times[ia] + fb * self->times[ia + 1];
}

void func_0014E2A0(PathCurve* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6)
{
    s32 idx = FindPathCurveSegment(t, self->count, self->lengths, self->wrap, 0, 0);
    s32 ia;
    f32 fb;
    WalkToNearestPathCurveSegment(a1, a2, self->count, self->points, idx, self->wrap, a3, a4, &ia, &fb);
    if (a6) *a6 = (1.0f - fb) * self->lengths[ia] + fb * self->lengths[ia + 1];
    if (a5) *a5 = (1.0f - fb) * self->times[ia] + fb * self->times[ia + 1];
}

void func_0014E3D0(SplinePathCurve* self, void* src)
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

void func_0014E500(SplinePathCurve* obj) { obj->idx1C0 = -1; }

void func_0014E510(SplinePathCurve* self, s32 i)
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

ASM_FUNC(func_0014E5B8);

void func_0014E6A8(SplinePathCurve* self, s32 a1, void* a2)
{
    f32 t = ((Fn_14E6A8)self->vt->m06)(self);
    Fn2_14E6A8 fn = (Fn2_14E6A8)self->vt->m01;
    if (fn) {
        fn(self, t, a1, a2);
    }
}

ASM_FUNC(func_0014E710);

ASM_FUNC(func_0014E828);

f32 func_0014E910(SplinePathCurve* self, f32 t0)
{
    f32 a, b;
    s32 i = FindPathCurveSegmentByTime(self, t0, &a, &b);
    u32 off = i * 16;
    f32 r = MeasureCurveSegmentLength((u8*)self->points + off, (u8*)self->outTan + off,
                          (u8*)self->points + (off + 16), (u8*)self->inTan + (off + 16), b, a);
    return r + self->lengths[i];
}

f32 func_0014E990(SplinePathCurve* self, f32 t0)
{
    f32 lo, a, b;
    s32 idx = FindPathCurveSegmentByLength(self, t0, &lo, 0);
    SampleSplineSegment(self, idx);
    s32 n = FindPathCurveSegment(lo, 20, self->len170, 0, &a, &b);
    f32 t = a / b;
    f32 u = ((f32)n + t) * 0.0526315793f;
    return (1.0f - u) * self->times[idx] + u * self->times[idx + 1];
}

// Read only by the assembly func_0014EB10. Defined in C, ahead of func_0014EA48 (which reads no
// .rodata) so the compiler leaves .rodata before that function: an include would align the label
// to 8, as its address is, but this file's .rodata starts 4 bytes past a 16-byte boundary.
extern const f32 D_00249FC8 = 3.4028235e+38f;

void func_0014EA48(SplinePathCurve* self)
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

ASM_FUNC(func_0014EB10);

void func_0014EC70(SplinePathCurve* self, s32 a1, s32 a2, s32 a3, s32 a4, f32* a5, f32* a6, f32 f12)
{
    Ctx_14EC70 ctx;
    Out_14EC70 out;
    f32 f13;
    f32 f14;
    void* fn;

    ctx.self = self;
    ctx.a1 = a1;
    ctx.a2 = a2;
    f14 = self->times[0];
    f13 = (self->times[1] - f14) * 0.1f;
    func_001EB168((void*)MeasureSplinePathDistance, f12, f13, self->wrap ? -3.4028235e+38f : f14, self->wrap ? 3.4028235e+38f : self->times[self->count - 1], &ctx, &out, 0);
    if (a3 != 0 || a4 != 0) {
        fn = (void*)self->vt->m01;
        if (fn != 0) {
            ((void (*)(PathCurve*, s32, s32, f32))fn)(self, a3, a4, out.f);
        }
    }
    if (a5 != 0) {
        *a5 = out.f;
    }
    if (a6 != 0) {
        *a6 = self->vt->m05(self, out.f);
    }
}

void func_0014ED98(SplinePathCurve* self, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6)
{
    s32 q4 = p4;
    s32 q3 = p3;
    s32 q2 = p2;
    s32 q1 = p1;
    s32 q6 = p6;
    s32 q5 = p5;
    f32 r = ((Slot6_14ED98)self->vt->m06)(self);
    Slot11_14ED98 fn = (Slot11_14ED98)self->vt->m11;
    if (fn != 0) {
        fn(self, q1, r, q2, q3, q4, q5, q6);
    }
}
