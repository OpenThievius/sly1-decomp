// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "fpu.h"
#include "shapes.h"
#include "vu0.h"

// Matrices and vectors: identity and transposition, rotations from angles and an axis, the
// transforms of placed objects, angles back from a matrix or a vector, inversion, a projection;
// many of them VU0 assembly.

extern u8 g_unitZVector[];

void ResetMatrixHomogeneous(void*);
void* FillMemory(void* p, s32 v, s32 n);
void ComputeSinCos(f32 angle, f32* s, f32* c);
f32 ClampToMagnitude(f32, f32);
f32 Arcsine(f32 x);
f32 ArctangentOfRatio(f32 y, f32 x);
void InvertRigidTransform(void* a, void* b, Quad16* out);
void MultiplyMatrices(Quad16* out, void* b, Quad16* in);
void BuildBasisFromXAndZHint(void* self, void* table, void* value);
void PushBackMemoryMark(void);
void* AllocateBackMemory(s32 size);
void CopyMemory(void* dst, void* src, s32 count);
void PopBackMemoryMark(void);
s32 InvertSquareMatrix(s32 n, f32* a, f32* b);

// A 4x4 matrix as func_001884C0 writes it: the last word of the first three rows, then the
// fourth row as one quadword.
struct HomogeneousMatrix {
    u8 pad0[0xC];  s32 f0C;
    u8 pad1[0xC];  s32 f1C;
    u8 pad2[0xC];  s32 f2C;
    Quad16 q30;
};
// The fourth row of a 4x4 matrix: 0 0 0 1.
extern const Quad16 D_0024B260 = { { 0, 0, 0, 0x3F800000 } };

void ResetMatrixHomogeneous(HomogeneousMatrix* self)
{
    self->f0C = 0;
    self->f1C = 0;
    self->f2C = 0;
    self->q30 = D_0024B260;
}

void* CopyRotationMatrix(Quad16* destination, const Quad16* source)
{
	destination[0] = source[0];
	destination[1] = source[1];
	destination[2] = source[2];
	ResetMatrixHomogeneous(destination);
	return destination;
}

ASM_FUNC(func_00188520);

void InitIdentityMatrix(Mat4* self)
{
    FillMemory(self, 0, 0x40);
    self->m[3][3] = 1.0f;
    self->m[2][2] = 1.0f;
    self->m[1][1] = 1.0f;
    self->m[0][0] = 1.0f;
}

ASM_FUNC(func_00188628);

INCLUDE_ASM(func_00188668);

LINKER_REMNANT(func_001886F8);

INCLUDE_ASM(func_00188700);

ASM_FUNC(func_00188740);

void CopyTransposedMatrix(Quad16* src, Quad16* dst)
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

void AddMatrices(f32* a, f32* b, f32* out)
{
	s32 count = 15;
	do {
		*out++ = *a++ + *b++;
	} while (--count >= 0);
}

LINKER_REMNANT(func_00188848);

void BuildAxisAngleMatrix(f32* axis, Mat4* mat, f32 angle)
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

struct __attribute__((aligned(16))) Matrix3x4 { f32 f[3][4]; };

extern Matrix3x4 g_identityMatrix;

void BuildRotationFromVector(Vec02* v, Mat4* mat)
{
    u128 q = Vu0::Q(*v);
    f32 len = Vu0::ToFloat(Vu0::Length(q));
    if (0.0001f < len) {
        Vec02 axis;
        Vec02 k;
        Vu0::Q(k) = Vu0::FromFloat(1.0f / len);
        Vu0::Q(axis) = Vu0::MulX(q, Vu0::Q(k));
        BuildAxisAngleMatrix(&axis.x, mat, len);
    } else {
        *(Matrix3x4*)mat = g_identityMatrix;
    }
}

void BuildEulerRotationMatrix(f32* in, f32* out)
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

void BuildMatrixFromRotationAndTranslation(Quad16* a, Quad16* b, Quad16* dst)
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

INCLUDE_ASM(func_00188B48);

void BuildScaledTransformMatrix(f32* pos, f32 (*rot)[4], f32* scale, f32 (*out)[4])
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

void GetMatrixRotationCosine(f32* p)
{
	ClampToMagnitude((p[0] + p[5] + p[10] - 1.0f) * 0.5f, 1.0f);
}

INCLUDE_ASM(func_00188D28);

LINKER_REMNANT(func_00188FD0);

void MatrixToEulerAngles(Mat4* self, Vec3* out)
{
    f32 k = 1.57069635f;
    f32 r = Arcsine(-self->m[0][2]);
    out->y = r;
    if (r < k) {
        if (-k < r) {
            out->x = ArctangentOfRatio(self->m[1][2], self->m[2][2]);
            out->z = ArctangentOfRatio(self->m[0][1], self->m[0][0]);
        } else {
            out->x = 0.0f;
            out->z = -ArctangentOfRatio(-self->m[1][0], self->m[2][0]);
        }
    } else {
        out->x = 0.0f;
        out->z = ArctangentOfRatio(-self->m[1][0], self->m[2][0]);
    }
}

ASM_FUNC(func_001890A0);

INCLUDE_ASM(func_00189150);

void TransformMatrixByObject(u8* self, void* arg, Quad16* out)
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

void VectorToAngles(Vec3* v, f32* a1, f32* a2)
{
    *a1 = ArctangentOfRatio(v->y, v->x);
    *a2 = ArctangentOfRatio(v->z, Fpu::Sqrt(v->x * v->x + v->y * v->y));
}

INCLUDE_ASM(func_001892A0);

void BuildBasisFromX(void* self, void* value)
{
    BuildBasisFromXAndZHint(self, g_unitZVector, value);
}

INCLUDE_ASM(func_00189378);

LINKER_REMNANT(func_00189430);

// Inverts the n-by-n matrix a into b by Gauss-Jordan elimination with partial
// pivoting, on a scratch copy; returns 0 when a is singular.
s32 InvertSquareMatrix(s32 n, f32* a, f32* b)
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

s32 InvertMatrix3x3(Matrix3x4* in, Matrix3x4* out)
{
    Matrix3x4 m;
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

s32 InvertMatrix4x4(void* a0, void* a1)
{
	return InvertSquareMatrix(4, (f32*)a0, (f32*)a1);
}

INCLUDE_ASM(func_00189B18);

INCLUDE_ASM(func_00189C28);

INCLUDE_ASM(func_00189D38);

void BuildProjectionMatrix(Mat4* self, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f)
{
    FillMemory(self, 0, 0x40);
    f32 value = (e + f) / (e - f);
    self->m[0][0] = a;
    self->m[2][0] = c;
    self->m[1][1] = b;
    self->m[2][1] = d;
    self->m[2][2] = value;
    self->m[3][2] = e * (1.0f - value);
    self->m[2][3] = 1.0f;
}

INCLUDE_ASM(func_0018A008);

INCLUDE_ASM(func_0018A040);

INCLUDE_ASM(func_0018A160);
