// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "fpu.h"
#include "shapes.h"

// Matrices and vectors: identity and transposition, rotations from angles and an axis, the
// transforms of placed objects, angles back from a matrix or a vector, inversion, a projection;
// many of them VU0 assembly.

extern u8 D_00248D20[];

void func_001884C0(void*);
void* func_001F5C0C(void* p, s32 v, s32 n);
void func_001EAD88(f32 angle, f32* s, f32* c);
f32 func_001EA480(f32, f32);
f32 func_00205678(f32 x);
f32 func_00205778(f32 y, f32 x);
void func_00188B48(void* a, void* b, Quad16* out);
void func_00188668(Quad16* out, void* b, Quad16* in);
void func_00189C28(struct Obj_189350* self, void* table, void* value);
void func_0018D608(void);
void* func_0018D658(s32 size);
void func_0018D800(void* dst, void* src, s32 count);
void func_0018D6F0(void);
s32 func_00189438(s32 n, f32* a, f32* b);

struct __attribute__((aligned(16))) Quad_1884C0 { s32 a, b, c, d; };
struct Obj_1884C0 {
    u8 pad0[0xC];  s32 f0C;
    u8 pad1[0xC];  s32 f1C;
    u8 pad2[0xC];  s32 f2C;
    Quad_1884C0 q30;
};
// The fourth row of a 4x4 matrix: 0 0 0 1.
extern const Quad_1884C0 D_0024B260 = { 0, 0, 0, 0x3F800000 };

void func_001884C0(Obj_1884C0* self)
{
    self->f0C = 0;
    self->f1C = 0;
    self->f2C = 0;
    self->q30 = D_0024B260;
}

struct Quad_001884E0 { s32 a, b, c, d; } __attribute__((aligned(16)));
void* func_001884E0(Quad_001884E0* destination, const Quad_001884E0* source)
{
	destination[0] = source[0];
	destination[1] = source[1];
	destination[2] = source[2];
	ResetMatrixHomogeneous(destination);
	return destination;
}

ASM_FUNC(func_00188520);

struct Vec4Init_1885E0 {
    u8 pad0[0x0];
    f32 f00;
    u8 pad1[0x10];
    f32 f14;
    u8 pad2[0x10];
    f32 f28;
    u8 pad3[0x10];
    f32 f3C;
};
void func_001885E0(Vec4Init_1885E0* self)
{
    FillMemory(self, 0, 0x40);
    self->f3C = 1.0f;
    self->f28 = 1.0f;
    self->f14 = 1.0f;
    self->f00 = 1.0f;
}

ASM_FUNC(func_00188628);

ASM_FUNC(func_00188668);

LINKER_REMNANT(func_001886F8);

ASM_FUNC(func_00188700);

ASM_FUNC(func_00188740);

struct Quad_188770 { f32 f[4]; } __attribute__((aligned(16)));
void func_00188770(Quad_188770* src, Quad_188770* dst)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    f32 (*m)[4] = (f32 (*)[4])dst;
    for (s32 i = 0; i < 3; i++) {
        for (s32 j = i + 1; j < 4; j++) {
            f32 tmp = m[i][j];
            m[i][j] = *((f32*)((i * 4) + (u32)dst + j * 16));
            *((f32*)((i * 4) + (u32)dst + j * 16)) = tmp;
        }
    }
}

void func_00188810(f32* a, f32* b, f32* out)
{
	s32 count = 15;
	do {
		*out++ = *a++ + *b++;
	} while (--count >= 0);
}

LINKER_REMNANT(func_00188848);

void func_00188850(f32* axis, Mat4* mat, f32 angle)
{
    f32 s;
    f32 c;
    s32 i;
    s32 j;
    f32 t;

    ComputeSinCos(angle, &s, &c);
    t = 1.0f - c;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            mat->m[i][j] = t * axis[i] * axis[j];
        }
    }
    for (i = 0; i < 3; i++) {
        mat->m[i][i] += c;
    }
    t = s * axis[2];
    mat->m[0][1] += t;
    mat->m[1][0] -= t;
    t = s * axis[1];
    mat->m[0][2] -= t;
    mat->m[2][0] += t;
    t = s * axis[0];
    mat->m[1][2] += t;
    mat->m[2][1] -= t;
}

ASM_FUNC(func_00188978);

void func_00188A20(f32* in, f32* out)
{
    f32 sc[6];
    ComputeSinCos(in[0], &sc[0], &sc[1]);
    ComputeSinCos(in[1], &sc[2], &sc[3]);
    ComputeSinCos(in[2], &sc[4], &sc[5]);
    f32 sa = sc[0], ca = sc[1], sb = sc[2], cb = sc[3], cg = sc[5], sg = sc[4];
    f32 sasb = sa * sb;
    f32 casb = ca * sb;
    out[0] = cb * cg;
    out[1] = cb * sg;
    out[2] = -sb;
    out[4] = sasb * cg - ca * sg;
    out[5] = sasb * sg + ca * cg;
    out[6] = sa * cb;
    out[8] = casb * cg + sa * sg;
    out[9] = casb * sg - sa * cg;
    out[10] = ca * cb;
}

void func_00188B08(Quad16* a, Quad16* b, Quad16* dst)
{
    dst[0] = b[0];
    dst[1] = b[1];
    dst[2] = b[2];
    dst[3] = *a;
    dst[0].w[3] = 0;
    dst[1].w[3] = 0;
    dst[2].w[3] = 0;
    *(f32*)&dst[3].w[3] = 1.0f;
}

ASM_FUNC(func_00188B48);

void func_00188C10(f32* pos, f32 (*rot)[4], f32* scale, f32 (*out)[4])
{
    s32 i;
    s32 j;
    f32* trans = out[3];
    f32* col = &out[0][3];
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++)
            out[i][j] = rot[i][j] * scale[i];
    }
    for (i = 0; i < 3; i++)
        trans[i] = pos[i];
    for (i = 2; i >= 0; i--)
        col[i * 4] = 0.0f;
    out[3][3] = 1.0f;
}

LINKER_REMNANT(func_00188CC8);

void func_00188CE0(f32* p)
{
	ClampToMagnitude((p[0] + p[5] + p[10] - 1.0f) * 0.5f, 1.0f);
}

ASM_FUNC(func_00188D28);

LINKER_REMNANT(func_00188FD0);

struct Span_188FD8 { f32 w[11]; };
struct Out_188FD8 { f32 o[3]; };
void func_00188FD8(Span_188FD8* self, Out_188FD8* out)
{
    f32 k = 1.57069635f;
    f32 r = Arcsine(-self->w[2]);
    out->o[1] = r;
    if (r < k) {
        if (-k < r) {
            out->o[0] = ArctangentOfRatio(self->w[6], self->w[10]);
            out->o[2] = ArctangentOfRatio(self->w[1], self->w[0]);
        } else {
            out->o[0] = 0.0f;
            out->o[2] = -ArctangentOfRatio(-self->w[4], self->w[8]);
        }
    } else {
        out->o[0] = 0.0f;
        out->o[2] = ArctangentOfRatio(-self->w[4], self->w[8]);
    }
}

ASM_FUNC(func_001890A0);

ASM_FUNC(func_00189150);

void func_001891C0(u8* self, void* arg, Quad16* out)
{
    Quad16 tmp[4];
    Quad16 res[4];

    InvertRigidTransform(self + 0x30, self, tmp);
    MultiplyMatrices(res, arg, tmp);
    out[0] = res[0];
    out[1] = res[1];
    out[2] = res[2];
    out[3] = res[3];
}

struct Vec3_189230 { f32 x; f32 y; f32 z; };
void func_00189230(Vec3_189230* v, f32* a1, f32* a2)
{
    *a1 = ArctangentOfRatio(v->y, v->x);
    *a2 = ArctangentOfRatio(v->z, Fpu::Sqrt(v->x * v->x + v->y * v->y));
}

ASM_FUNC(func_001892A0);

struct Obj_189350;
void func_00189350(Obj_189350* self, void* value)
{
    BuildBasisFromXAndZHint(self, g_unitZVector, value);
}

ASM_FUNC(func_00189378);

LINKER_REMNANT(func_00189430);

// Inverts the n-by-n matrix a into b by Gauss-Jordan elimination with partial
// pivoting, on a scratch copy; returns 0 when a is singular.
s32 func_00189438(s32 n, f32* a, f32* b)
{
    s32 ok = 0;
    PushBackMemoryMark();
    s32 size = n * n * 4;
    f32* m = (f32*)AllocateBackMemory(size);
    CopyMemory(m, a, size);
    s32 i, j, k;
    f32 r;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            f32* p = &b[i * n + j];
            if (i == j) *p = 1.0f;
            else *p = 0;
        }
    }
    for (i = 0; i < n; i++) {
        s32 piv = i;
        s32 row = i * n;
        f32 mx = __builtin_fabsf(m[row + i]);
        for (k = i + 1; k < n; k++) {
            r = __builtin_fabsf(m[row + k]);
            if (mx < r) {
                piv = k;
                mx = r;
            }
        }
        if (mx == 0.0f) goto done;
        if (piv != i) {
            for (k = 0; k < n; k++) {
                f32 t = m[k * n + i];
                m[k * n + i] = m[k * n + piv];
                m[k * n + piv] = t;
                f32 u = b[k * n + i];
                b[k * n + i] = b[k * n + piv];
                b[k * n + piv] = u;
            }
        }
        for (j = i + 1; j < n; j++) {
            r = m[i * n + j] / m[i * n + i];
            for (k = 0; k < n; k++) {
                m[k * n + j] -= r * m[k * n + i];
                b[k * n + j] -= r * b[k * n + i];
            }
        }
    }
    for (i = n - 1; i >= 0; i--) {
        for (j = 0; j < i; j++) {
            r = m[i * n + j] / m[i * n + i];
            for (k = 0; k < n; k++) {
                m[k * n + j] -= r * m[k * n + i];
                b[k * n + j] -= r * b[k * n + i];
            }
        }
    }
    for (i = 0; i < n; i++) {
        r = m[i * n + i];
        for (j = 0; j < n; j++) b[j * n + i] /= r;
    }
    ok = 1;
done:
    PopBackMemoryMark();
    return ok;
}

struct __attribute__((aligned(16))) Mat_1897F0 { f32 f[3][4]; };

extern Mat_1897F0 D_002483D0;
s32 func_001897F0(Mat_1897F0* in, Mat_1897F0* out)
{
    Mat_1897F0 m;
    s32 i, j, k;
    f32 t;
    s32 ok = 0;
    m = *in;
    *out = g_identityMatrix;
    for (i = 0; i < 3; i++) {
        j = i;
        f32 best = __builtin_fabsf(m.f[i][j]);
        for (k = i + 1; k < 3; k++) {
            t = __builtin_fabsf(m.f[i][k]);
            if (best < t) {
                best = t;
                j = k;
            }
        }
        if (best == 0.0f) goto done;
        if (j != i) {
            for (k = 0; k < 3; k++) {
                f32 a = m.f[k][j];
                f32 b = out->f[k][j];
                f32 c = m.f[k][i];
                f32 d = out->f[k][i];
                m.f[k][i] = a;
                out->f[k][i] = b;
                m.f[k][j] = c;
                out->f[k][j] = d;
            }
        }
        for (j = i + 1; j < 3; j++) {
            t = m.f[i][j] / m.f[i][i];
            for (k = 0; k < 3; k++) {
                m.f[k][j] -= t * m.f[k][i];
                out->f[k][j] -= t * out->f[k][i];
            }
        }
    }
    for (i = 2; i >= 0; i--) {
        for (j = 0; j < i; j++) {
            t = m.f[i][j] / m.f[i][i];
            for (k = 0; k < 3; k++) {
                m.f[k][j] -= t * m.f[k][i];
                out->f[k][j] -= t * out->f[k][i];
            }
        }
    }
    for (i = 0; i < 3; i++) {
        t = m.f[i][i];
        for (j = 0; j < 3; j++) {
            out->f[j][i] /= t;
        }
    }
    ok = 1;
done:
    return ok;
}

s32 func_00189AF0(void* a0, void* a1)
{
	return InvertSquareMatrix(4, (f32*)a0, (f32*)a1);
}

ASM_FUNC(func_00189B18);

ASM_FUNC(func_00189C28);

ASM_FUNC(func_00189D38);

struct State_189F58 {
    f32 f00;
    u8 pad04[0x10];
    f32 f14;
    u8 pad18[8];
    f32 f20;
    f32 f24;
    f32 f28;
    f32 f2C;
    u8 pad30[8];
    f32 f38;
};
void func_00189F58(State_189F58* self, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f)
{
    FillMemory(self, 0, 0x40);
    f32 value = (e + f) / (e - f);
    self->f00 = a;
    self->f20 = c;
    self->f14 = b;
    self->f24 = d;
    self->f28 = value;
    self->f38 = e * (1.0f - value);
    self->f2C = 1.0f;
}

ASM_FUNC(func_0018A008);

INCLUDE_ASM(func_0018A040);

ASM_FUNC(func_0018A160);
