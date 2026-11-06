// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "switched_collider.h"
#include "fpu.h"
#include "memory_card.h"
#include "background_job.h"
#include "shapes.h"

extern void func_001C7CB8(void);
extern void func_001C6F48(void*);
extern void func_001C7140(void*);
extern void func_00124DF8(void*, s32, void*);
extern void* func_00189438(s32, void*, void*);
extern f32 func_001EA480(f32, f32);
extern void func_001884C0(void*);
extern void func_00188668(void*, void*, void*);
extern void func_001B6598(s32, s32*);
extern s32 func_001C96B8(void*);
extern s32 func_001C8010(void*);
extern s32 func_00209B80(s32, s32*, s32*);
extern s32 func_0018B930(s32);
extern s32 func_0018B988(s32, s32);
extern s32 func_002093F0(void);
extern void func_0018B5C0(void*);
extern void func_0018BD58(void*, s32, s32);
extern void func_001F6A50(s32, s32);
extern s32 func_001F6B60(s32);
extern void func_001F6B40(s32);
extern s32 func_0018B770(void*);
struct Ent_264910 { s32 a, b, c; };

struct Quad_001884E0 { s32 a, b, c, d; } __attribute__((aligned(16)));

void* func_001884E0(Quad_001884E0* destination, const Quad_001884E0* source)
{
	destination[0] = source[0];
	destination[1] = source[1];
	destination[2] = source[2];
	func_001884C0(destination);
	return destination;
}

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

void* func_001F5C0C(void* p, s32 v, s32 n);

void func_001885E0(Vec4Init_1885E0* self)
{
    func_001F5C0C(self, 0, 0x40);
    self->f3C = 1.0f;
    self->f28 = 1.0f;
    self->f14 = 1.0f;
    self->f00 = 1.0f;
}

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

void func_00188CE0(f32* p)
{
	ClampToMagnitude((p[0] + p[5] + p[10] - 1.0f) * 0.5f, 1.0f);
}

struct Span_188FD8 { f32 w[11]; };
struct Out_188FD8 { f32 o[3]; };

f32 func_00205678(f32 x);
f32 func_00205778(f32 y, f32 x);

void func_00188FD8(Span_188FD8* self, Out_188FD8* out)
{
    f32 k = 1.57069635f;
    f32 r = func_00205678(-self->w[2]);
    out->o[1] = r;
    if (r < k) {
        if (-k < r) {
            out->o[0] = func_00205778(self->w[6], self->w[10]);
            out->o[2] = func_00205778(self->w[1], self->w[0]);
        } else {
            out->o[0] = 0.0f;
            out->o[2] = -func_00205778(-self->w[4], self->w[8]);
        }
    } else {
        out->o[0] = 0.0f;
        out->o[2] = func_00205778(-self->w[4], self->w[8]);
    }
}

void func_00188B48(void* a, void* b, Quad16* out);
void func_00188668(Quad16* out, void* b, Quad16* in);

void func_001891C0(u8* self, void* arg, Quad16* out)
{
    Quad16 tmp[4];
    Quad16 res[4];

    func_00188B48(self + 0x30, self, tmp);
    func_00188668(res, arg, tmp);
    out[0] = res[0];
    out[1] = res[1];
    out[2] = res[2];
    out[3] = res[3];
}

void* func_00189AF0(void* a0, void* a1)
{
	return InvertSquareMatrix(4, a0, a1);
}

void func_001C7140(void* self);
void func_00124DF8(void* self, s32 n, void* data);

void func_001C91C8(void* self);
void func_001603E8(s32 n);
void func_0018C7F8(void* p);

void func_001B6598(void* a, s32* out);
s32 func_001C96B8(void* self);
s32 func_001C8010(void* self);

void func_001C7CB8(void);

typedef void (*VFn_18ACF0)(void* self);

struct Obj_18ACF0 {
    VFn_18ACF0* vtbl;
};

extern Obj_18ACF0 D_0026E248;

s32 func_001E9970(void);

extern void func_001C9008(void*);
extern void func_001B64D8(s32, s32);

struct Obj_18B720 { void* f0; void* f4; };


s32 func_0018B770(void* p);
void func_001F6A50(void* a, s32 b);
s32 func_001F6B60(void* a);
void func_001F6B40(void* a);

struct Src_18B780 {
    u8 pad0[1];
    u8 b1;
    u8 b2;
    u8 b3;
    u8 b4;
    u8 b5;
    u16 h6;
    u8 pad3[1];
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 bD;
    u16 hE;
    s32 f10;
    u16 f14;
    u8 pad2[0x20 - 0x16];
    u8 sub20[0x10];
};

struct Dst_18B780 {
    u8 pad0[0x44];
    s32 f44;
    u8 pad1[2];
    u8 f4A;
    u8 f4B;
    u16 f4C;
    u8 f4E;
    u8 f4F;
    u8 f50;
    u8 pad3[1];
    u8 f52;
    u8 f53;
    u16 f54;
    u8 f56;
    u8 f57;
    u8 f58;
};

void* func_001F5C0C(void* p, int c, int n);
void* func_001E2138(void* dst, void* src);

struct Pair_18BC90 { s32 a; s32 b; };

s32 func_00209B80(void* a0, s32* a1, s32* a2);
s32 func_0018B930(s32 h);
s32 func_0018B988(void* a0, s32 b);

typedef s32 (*VFnI_0018AAE0)(void* self);

s32 func_001DDA80(void* p);
void func_001B6598(void* dev, s32* out);


void func_001AC060(void* p);
void func_001C8F20(void* node, s32 kind, s32 flag);

struct Glob_18BDC8 { u8 pad0[0x25C]; s32 f25C; u8 pad260[8]; s32 f268; };

extern f32 D_00261868[];

void func_0018B670(BackgroundJob* p, void* fn, MemoryCard* self);
void func_0018C028(MemoryCard* self, s32 v);
s32 func_0018D0A0(MemoryCard* self);
void func_00194D30(Glob_18BDC8* g, s32 a, s32 b);

// Matches US and EU: retail's return-1 block is a shared target that every return-1 path branches to.
extern f32 D_0026185C;

typedef void* (*FnSelf_18A9A8)(void* self);
typedef s32 (*FnSub_18A9A8)(void* self);

struct Loc_18A9A8 {
    u8 buf[0x10];
    s32 code;
};

s32 func_0018A910(void* self, void* a, void* b);
s32 func_00125750(void* a, s32 b, void* c, s32 d, s32 e, s32 f, f32 g);

s32 func_001E2268(s32 a, s32 b);

void* func_001F5C0C(void* p, s32 zero, s32 size);
void func_0018C178(void* self, s32 value);

// NEAR: same callees, args and frame. Retail saves s2,s1,s0 then moves a2->s2, a1->s1 before the jal and fills its delay slot with self->s0; the compiler places move s0 early and fills the delay slot with move s1.
typedef s32 (*Cb_18A910)(void* self, void* ctx);

s32 func_0018A830(void* self, void* ctx);
void func_0018D608(void* self, void* a1, void* a2);
void func_001DC238(void* a0, s32 a1, void* a2, void* a3, Cb_18A910 a4, void* a5, s32* a6, s32* a7);
s32 func_0018A6C0(s32 a0, void* a1, void* a2, s32 a3, s32 a4, void* a5, f32 f);
void func_0018D6F0(void);

// Hoisting 1.0f into a local `one` matched the constant scheduling.
void func_001B6598(void* a, s32* out);

struct __attribute__((aligned(16))) Cand_18A6C0 { u8 pad0[0x40]; f32 score; u8 pad1[0x70 - 0x44]; };

s32 func_00141D00(void* self, void* p1, void* p2, f32 x, s32 p3, void* p4);

struct __attribute__((aligned(16))) Quad_1884C0 { s32 a, b, c, d; };
struct Obj_1884C0 {
    u8 pad0[0xC];  s32 f0C;
    u8 pad1[0xC];  s32 f1C;
    u8 pad2[0xC];  s32 f2C;
    Quad_1884C0 q30;
};

extern const Quad_1884C0 D_0024B260;

void func_001884C0(Obj_1884C0* self)
{
    self->f0C = 0;
    self->f1C = 0;
    self->f2C = 0;
    self->q30 = D_0024B260;
}

struct Obj_189350;

void func_00189C28(Obj_189350* self, void* table, void* value);

extern u8 D_00248D20[];

void func_00189350(Obj_189350* self, void* value)
{
    func_00189C28(self, g_unitZVector, value);
}

// was NEAR: 2 lines: retail has addiu s2 (self+0xE30) before the first call and li s3,2 in its delay slot; ours swaps them. About 20 rewrites (for/do-while, init placement, decl order, cast offsets) all give the same two swapped lines.
struct Ent_264960 { s32 key; f32 f; s32 v; };

void func_001C72A0(void* self);
void func_001DDC38(void* sub, void* self);
void func_00124DF8(void* self, s32 n, void* table);
void func_001D36F0(void* self, void* a, void* b);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
s32 func_001CA758(void* self, s32 id);
u8* func_0018D568(s32 size, void* src);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);

struct Ent_18A3F0 { s32 key; s32 pad4; s32 value; };

struct Tail_18B988
{
    static s32 Get(s32 b, s32 v, s32 lim)
    {
        s32 r = v;
        if (b >= lim) r = 31;
        return r;
    }
};

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

extern u8 D_00275960[];

s32 func_001F6B60(void* a);
void func_001F6B40(void* a);
s32 func_001F6A30();

struct Vec3_189230 { f32 x; f32 y; f32 z; };

f32 func_00205778(f32 a, f32 b);

void func_00189230(Vec3_189230* v, f32* a1, f32* a2)
{
    *a1 = func_00205778(v->y, v->x);
    *a2 = func_00205778(v->z, Fpu::Sqrt(v->x * v->x + v->y * v->y));
}

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
extern void func_001F5C0C(State_189F58* p, s32 v, s32 n);

void func_00189F58(State_189F58* self, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f)
{
    func_001F5C0C(self, 0, 0x40);
    f32 value = (e + f) / (e - f);
    self->f00 = a;
    self->f20 = c;
    self->f14 = b;
    self->f24 = d;
    self->f28 = value;
    self->f38 = e * (1.0f - value);
    self->f2C = 1.0f;
}

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

void func_001EAD88(f32 angle, f32* a, f32* b);

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

s32 func_001300E8(BaseObject* a, s32 b);
s32 func_001833F0(BaseObject* a, s32 b);

typedef s32 (*VFn_18A830)(BaseObject* self, void* arg);
struct Rec_18A830 { u8 pad[0x50]; BaseObject* sub; };

void func_001EAD88(f32 angle, f32* s, f32* c);

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

struct __attribute__((aligned(16))) Quad_18B340 { s32 w[4]; };

struct Key_18B340 {
    s32 a;
    s32 pad0;
    s32 b;
};

struct Obj_18B340 {
    u8 pad0[0xF0];
    Quad_18B340 fF0;
};

s32 func_001A8C90(void* obj, s32 v);
void func_001C9DE0(void* self, s32 code, void* req);
void func_001B6598(void* dev, s32* out);

void func_0018D608(void);
void* func_0018D658(s32 size);
void func_0018D800(void* dst, void* src, s32 count);
void func_0018D6F0(void);

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

// Data definitions.
extern const Quad_1884C0 D_0024B260 = { 0, 0, 0, 0x3F800000 };
