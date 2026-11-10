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
Mat4A MultiplyMatrices(Quad16* m, Quad16* in);
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

// in times m, row by row: each row of in through m (TransformMatrixByObject's product). The
// matrix is returned by value: the caller passes the address of its result in a0 and gets it
// back in v0, and each row goes to the result (g++'s named return value) as soon as it is made.
Mat4A MultiplyMatrices(Quad16* m, Quad16* in) return out
{
    u128 m0 = Vu0::Q(m[0]);
    u128 m1 = Vu0::Q(m[1]);
    u128 m2 = Vu0::Q(m[2]);
    u128 m3 = Vu0::Q(m[3]);
    Quad16 r[4];
    Vu0::Q(r[0]) = Vu0::Transform4(m0, m1, m2, m3, Vu0::Q(in[0]));
    ((Quad16*)&out)[0] = r[0];
    Vu0::Q(r[1]) = Vu0::Transform4(m0, m1, m2, m3, Vu0::Q(in[1]));
    ((Quad16*)&out)[1] = r[1];
    Vu0::Q(r[2]) = Vu0::Transform4(m0, m1, m2, m3, Vu0::Q(in[2]));
    ((Quad16*)&out)[2] = r[2];
    Vu0::Q(r[3]) = Vu0::Transform4(m0, m1, m2, m3, Vu0::Q(in[3]));
    ((Quad16*)&out)[3] = r[3];
}


LINKER_REMNANT(func_001886F8);

// The point v through m, with w as its fourth coordinate.
void TransformByMatrixWithW(const Quad16* m, const Quad16* v, f32 w, Quad16* out)
{
    Vu0::Q(*out) = Vu0::Transform(*m, Vu0::Q(*v), w);
}

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

void InvertRigidTransform(void* a, void* b, Quad16* out)
{
    *(Vu0::Rows*)out = Vu0::Transpose(*(Vu0::Rows*)b);
    Vu0::Q(out[3]) = Vu0::RotateTransposed(*(Vu0::Rows*)b, Vu0::Q(*(Quad16*)a));
    Vu0::Q(out[3]) = Vu0::MulX(Vu0::Q(out[3]), Vu0::Scalar(-1.0f));
    out[0].w[3] = 0;
    out[1].w[3] = 0;
    out[2].w[3] = 0;
    *(f32*)&out[3].w[3] = 1.0f;
}

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

f32 Arccosine(f32 x);

void MatrixToAxisAngle(Mat02* m, f32* angle, Vec02* axis)
{
    f32 (*e)[4] = (f32 (*)[4])m;
    f32* v = &axis->x;
    f32 c = (e[0][0] + e[1][1] + e[2][2] - 1.0f) * 0.5f;
    if (0.999999f < c) {
        *angle = 0.0f;
        Vu0::Q(*axis) = Vu0::FromFloats(1.0f, *angle, *angle);
        return;
    }
    f32 rem = 1.0f;
    f32 k = rem - c;
    s32 i;
    for (i = 0; i < 2; i++) {
        f32 d = (e[i][i] - c) / k;
        f32 a = __builtin_fabsf(d);
        if (rem < a) a = rem;
        else if (a < 0.0f) a = 0.0f;
        v[i] = Fpu::Sqrt(a);
        rem -= a;
    }
    v[2] = Fpu::Sqrt(rem);
    if (c < -0.9999f) {
        *angle = 3.1415927f;
        f32 x = v[0];
        f32 y = v[1];
        f32 z = v[2];
        if (x > y) {
            if (x > z) {
                if (e[0][1] < 0.0f) v[1] = -y;
                if (e[0][2] < 0.0f) v[2] = -v[2];
            } else {
                if (e[2][0] < 0.0f) v[0] = -x;
                if (e[2][1] < 0.0f) v[1] = -v[1];
            }
        } else if (y > z) {
            if (e[1][0] < 0.0f) v[0] = -x;
            if (e[1][2] < 0.0f) v[2] = -v[2];
        } else {
            if (e[2][0] < 0.0f) v[0] = -x;
            if (e[2][1] < 0.0f) v[1] = -v[1];
        }
    } else {
        *angle = Arccosine(c);
        if (e[1][0] > e[0][1]) v[2] = -v[2];
        if (e[2][0] < e[0][2]) v[1] = -v[1];
        if (e[2][1] > e[1][2]) v[0] = -v[0];
    }
}

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

// out = a's transpose times b, for 3x3 matrices.
void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out)
{
    Mat02 t;
    Vu0::MulTransposed(t, *a, *b);
    *out = t;
}

void TransformMatrixByObject(u8* self, void* arg, Quad16* out)
{
    Quad16 tmp[4];

    InvertRigidTransform(self + 0x30, self, tmp);
    *(Mat4A*)out = MultiplyMatrices((Quad16*)arg, tmp);
}

void VectorToAngles(Vec3* v, f32* a1, f32* a2)
{
    *a1 = ArctangentOfRatio(v->y, v->x);
    *a2 = ArctangentOfRatio(v->z, Fpu::Sqrt(v->x * v->x + v->y * v->y));
}

extern u8 g_unitYVector[];

// The product a b of two rotations into out: b's rows each rotated by a.
static inline void MulRotation(Mat02* out, const Mat02& a, const Mat02& b)
{
    Mat02 r;
    Vec02 x;
    Vec02 y;
    Vec02 z;
    Vu0::Q(x) = Vu0::RotateUntied(a, Vu0::Q(b.r[0]));
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateUntied(a, Vu0::Q(b.r[1]));
    r.r[1] = y;
    Vu0::Q(z) = Vu0::RotateUntied(a, Vu0::Q(b.r[2]));
    r.r[2] = z;
    *out = r;
}

void func_001892A0(f32 yaw, f32 pitch, Mat02* out)
{
    Mat02 a;
    Mat02 b;
    BuildAxisAngleMatrix((f32*)g_unitZVector, (Mat4*)&a, yaw);
    BuildAxisAngleMatrix((f32*)g_unitYVector, (Mat4*)&b, -pitch);
    MulRotation(out, a, b);
}

void BuildBasisFromX(void* self, void* value)
{
    BuildBasisFromXAndZHint(self, g_unitZVector, value);
}

void BuildShortestArcRotation(void* from, void* to, void* out);

void func_00189378(Mat02* self, Mat02* scratch, Mat02* out)
{
    Mat02 local;
    Mat02 m;
    Mat02 t;
    Mat02* z = scratch ? scratch : &local;
    BuildShortestArcRotation(&self->r[2], g_unitZVector, z);
    if (out) {
        u128 x0 = Vu0::RotateUntied(*z, Vu0::Q(self->r[0]));
        u128 x1 = Vu0::RotateUntied(*z, Vu0::Q(self->r[1]));
        u128 x2 = Vu0::RotateUntied(*z, Vu0::Q(self->r[2]));
        Vu0::Q(t.r[0]) = x0;
        Vu0::Q(m.r[0]) = x0;
        Vu0::Q(t.r[1]) = x1;
        Vu0::Q(m.r[1]) = x1;
        Vu0::Q(t.r[2]) = x2;
        Vu0::Q(m.r[2]) = x2;
        Vu0::Q(out->r[0]) = x0;
        Vu0::Q(out->r[1]) = x1;
        Vu0::Q(out->r[2]) = x2;
    }
}

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

extern const Vec02 g_unitXVector;
void ComputeUnitPerpendicular(Vec02* v, Vec02* out);

void func_00189B18(Vec02* x, Vec02* hint, Mat02* out)
{
    Vec02 c;
    out->r[0] = *x;
    Vu0::Q(out->r[0]) = Vu0::NormalizeOr(Vu0::Q(out->r[0]), Vu0::Q(g_unitXVector));
    u128 cr = Vu0::Cross(Vu0::Q(out->r[0]), Vu0::Q(*hint));
    Vu0::Q(out->r[2]) = cr;
    Vu0::Q(c) = cr;
    u128 len = Vu0::Length(cr);
    Vu0::Q(out->r[2]) = Vu0::DivX(cr, len);
    if (Vu0::ToFloat(len) < 0.0001f) {
        ComputeUnitPerpendicular(&out->r[0], &out->r[2]);
    }
    Vu0::Q(out->r[1]) = Vu0::Cross(Vu0::Q(out->r[2]), Vu0::Q(out->r[0]));
}

void func_00189C28(Vec02* x, Vec02* hint, Mat02* out)
{
    Vec02 c;
    out->r[0] = *x;
    Vu0::Q(out->r[0]) = Vu0::NormalizeOrMoved(Vu0::Q(out->r[0]), Vu0::Q(g_unitXVector));
    u128 cr = Vu0::Cross(Vu0::Q(*hint), Vu0::Q(out->r[0]));
    Vu0::Q(out->r[1]) = cr;
    Vu0::Q(c) = cr;
    u128 len = Vu0::Length(cr);
    Vu0::Q(out->r[1]) = Vu0::DivX(cr, len);
    if (Vu0::ToFloat(len) < 0.0001f) {
        ComputeUnitPerpendicular(&out->r[0], &out->r[1]);
    }
    Vu0::Q(out->r[2]) = Vu0::Cross(Vu0::Q(out->r[0]), Vu0::Q(out->r[1]));
}

// The rotation that turns the direction of from into that of to: about their cross product, by
// the angle whose cosine is their dot (both made unit, or +z when too short). When the two are
// parallel the axis is x cross from, or y cross from. The axis is written at its own address
// (*(u128*)&axis): through Vu0::Q or Set its address would stay in a saved register for the last
// call, where retail forms it again. Its length is a float the compiler keeps in the GPR of its
// qmfc2, which the divide's Scalar moves back with qmtc2.
void BuildShortestArcRotation(void* fromp, void* top, void* outp)
{
    Vec02 a = *(Vec02*)fromp;
    Vec02 b = *(Vec02*)top;
    Vec02 axis;
    Vu0::Q(a) = Vu0::NormalizeOr(Vu0::Q(a), Vu0::Q(*(Vec02*)g_unitZVector));
    u128 bn = Vu0::NormalizeOr(Vu0::Q(b), Vu0::Q(*(Vec02*)g_unitZVector));
    Vu0::Set(b, bn);
    *(u128*)&axis = Vu0::Cross(Vu0::Q(a), bn);
    f32 len = Vu0::ToFloat(Vu0::Length(*(u128*)&axis));
    if (len < 0.0001f) {
        *(u128*)&axis = Vu0::Cross(Vu0::Q(g_unitXVector), Vu0::Q(a));
        len = Vu0::ToFloat(Vu0::Length(*(u128*)&axis));
        if (len < 0.0001f) {
            *(u128*)&axis = Vu0::Cross(Vu0::Q(*(Vec02*)g_unitYVector), Vu0::Q(a));
            len = Vu0::ToFloat(Vu0::Length(*(u128*)&axis));
        }
    }
    u128 cosine = Vu0::Dot(Vu0::Q(a), Vu0::Q(b));
    *(u128*)&axis = Vu0::DivX(*(u128*)&axis, Vu0::Scalar(len));
    f32 angle = Arccosine(Vu0::ToFloatMoved(cosine));
    BuildAxisAngleMatrix(&axis.x, (Mat4*)outp, angle);
}

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

void BuildScaleAboutFrame(Quad16* pos, Quad16* rot, f32* scale, Mat4A* out);

void BuildUniformScaleAboutPoint(void* point, void* out, f32 s)
{
    Quad16 scale;
    Vu0::Q(scale) = Vu0::Splat(s);
    BuildScaleAboutFrame((Quad16*)point, 0, (f32*)&scale, (Mat4A*)out);
}

extern u8 D_00248D30[];

// A matrix of zeros.
static inline void ClearMatrix(Mat4A* m)
{
    FillMemory(m, 0, sizeof(*m));
}

// The transform that scales by scale along the axes of the frame of rotation rot at pos (the
// origin and identity when they are null): back into the frame, scaled, out again.
void BuildScaleAboutFrame(Quad16* pos, Quad16* rot, f32* scale, Mat4A* out)
{
    Mat4A frame;
    Mat4A inverse;
    Mat4A scaling;
    Mat4A step;

    if (pos == 0)
        pos = (Quad16*)D_00248D30;
    if (rot == 0)
        rot = (Quad16*)&g_identityMatrix;
    BuildMatrixFromRotationAndTranslation(pos, rot, (Quad16*)&frame);
    InvertRigidTransform(pos, rot, (Quad16*)&inverse);
    ClearMatrix(&scaling);
    scaling.m[0][0] = scale[0];
    scaling.m[1][1] = scale[1];
    scaling.m[2][2] = scale[2];
    scaling.m[3][3] = 1.0f;
    step = MultiplyMatrices((Quad16*)&scaling, (Quad16*)&inverse);
    *out = MultiplyMatrices((Quad16*)&frame, (Quad16*)&step);
}

// The rotation that turns a into the direction of b, about their cross product made unit (x
// when the two are parallel), by the angle whose sine and cosine are the cross product's length
// and the dot over the lengths' product; the identity when either is shorter than 1e-4. The
// cross product's length is read twice: for the test by ToFloat (an asm qmfc2) and for the sine
// by ToFloatMoved, whose qmfc2 is the compiler's own copy, a VU0-unit insn sched2 issues after
// the two lqc2 of the dot, where retail has the loop counter's move.
void BuildRotationBetweenVectors(Vec02* a, Vec02* b, f32* m)
{
    Vec02 axis;
    f32 la = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(*a)));
    f32 lb = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(*b)));
    if (la < 0.0001f || lb < 0.0001f) {
        *(Matrix3x4*)m = g_identityMatrix;
        return;
    }
    u128 c = Vu0::Cross(Vu0::Q(*a), Vu0::Q(*b));
    u128 lc = Vu0::Length(c);
    const Vec02* fallback = &g_unitXVector;
    Vu0::Q(axis) = c;
    if (Vu0::ToFloat(lc) < 0.0001f) {
        axis = *fallback;
    } else {
        Vu0::Q(axis) = Vu0::DivX(c, lc);
    }
    f32 prod = la * lb;
    f32 sinv = Vu0::ToFloatMoved(lc) / prod;
    f32 cosv = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(*a), Vu0::Q(*b))) / prod;
    f32 (*mm)[4] = (f32 (*)[4])m;
    f32 t = 1.0f - cosv;
    s32 i;
    s32 j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            mm[i][j] = t * ((f32*)&axis)[i] * ((f32*)&axis)[j];
        }
    }
    for (i = 0; i < 3; i++) {
        mm[i][i] += cosv;
    }
    t = sinv * axis.z;
    mm[0][1] += t;
    mm[1][0] -= t;
    t = sinv * axis.y;
    mm[0][2] -= t;
    mm[2][0] += t;
    t = sinv * axis.x;
    mm[1][2] += t;
    mm[2][1] -= t;
}
