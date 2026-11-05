// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "c05.h"
#include "fpu.h"
#include "g264a40.h"
#include "g269990.h"
#include "shapes.h"

extern void func_001C7CB8(void);
extern void func_001C6F48(void*);
extern void func_001C7140(void*);
extern void func_00124DF8(void*, s32, void*);
extern void* func_00189438(s32, void*, void*);
extern void func_001EA480(f32, f32);
extern void func_001884C0(void*);
extern void func_00188668(void*, void*, void*);
extern s32 func_001B6598(s32, s32*);
extern s32 func_001C96B8(void*);
extern s32 func_001C8010(void*);
extern s32 func_00209B80(s32, s32*, s32*);
extern s32 func_0018B930(s32);
extern s32 func_0018B988(s32, s32);
extern void func_002093F0(void);
extern void func_0018B5C0(void*);
extern void func_0018BD58(void*, s32, s32);
extern void func_001F6A50(s32, s32);
extern void func_001F6B60(s32);
extern void func_001F6B40(s32);
extern s32 func_0018B770(void*);
struct Ent_264910 { s32 a, b, c; };
extern Ent_264910 D_00264910[2];

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
	func_001EA480((p[0] + p[5] + p[10] - 1.0f) * 0.5f, 1.0f);
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
	return func_00189438(4, a0, a1);
}

void func_0018A388(C0C* self)
{
	func_001C6F48(self);
	*(s32*)((char*)self + 0xE3C) = -1;
}

void func_001C7140(void* self);
void func_00124DF8(void* self, s32 n, void* data);

void func_0018A3B8(C0C* self)
{
    func_001C7140(self);
    func_00124DF8(self, 2, D_00264910);
}

void func_001C91C8(void* self);
void func_001603E8(s32 n);
void func_0018C7F8(void* p);

void func_0018AB88(C0C* self)
{
    func_001C91C8(self);
    s32 st = self->f724;
    if (st != 0xB) {
        if (st == 0x10) {
            s32 n = self->fA68;
            self->fC04 = 0;
            self->fA68 = n + 1;
        }
    } else {
        func_001603E8(2);
        func_0018C7F8(&D_00264A40);
    }
}

void func_001B6598(void* a, s32* out);
s32 func_001C96B8(void* self);
s32 func_001C8010(void* self);

s32 func_0018ABF0(C0C* self)
{
    if (self->f724 == 4) {
        s32 kind;
        func_001B6598(self->fE10, &kind);
        if (kind == 0x438) {
            if (func_001C96B8(self) == 0)
                return 2;
        }
    }
    return func_001C8010(self);
}

void func_001C7CB8(void);

void func_0018ACD0(void)
{
    func_001C7CB8();
}

typedef void (*VFn_18ACF0)(void* self);

struct Obj_18ACF0 {
    VFn_18ACF0* vtbl;
};

extern Obj_18ACF0 D_0026E248;

s32 func_001E9970(void);

void func_0018ACF0(C0C* self)
{
    s32 kind;
    func_001B6598(self->fE10, &kind);
    s32 pick = 0;
    switch (kind) {
    case 0x43A:
    case 0x43C:
    case 0x43E:
        pick = func_001E9970();
        break;
    default:
        break;
    }
    if (pick)
        D_0026E248.vtbl[14](&D_0026E248);
    else
        D_0026E248.vtbl[15](&D_0026E248);
}

extern void func_001C9008(void*);
extern void func_001B64D8(s32, s32);

void func_0018B2E8(C0C* self)
{
    func_001C9008(self);
    if (self->f724 == 16) {
        s32 token = self->fE3C;
        if (token == -1) return;
        func_001B64D8((s32)self->fE10, token);
        self->fE3C = -1;
    }
}

void func_0018B580(void)
{
	func_002093F0();
	func_0018B5C0(&D_00269990);
	func_0018BD58(&D_00264A40, 0, 0);
}

struct Obj_18B720 { void* f0; void* f4; };


s32 func_0018B770(void* p);
void func_001F6A50(void* a, s32 b);
void func_001F6B60(void* a);
void func_001F6B40(void* a);

void func_0018B720(Obj_18B720* a0)
{
    if (func_0018B770(&D_00269990)) {
        func_001F6A50(a0->f4, 1);
    }
    func_001F6B60(a0->f0);
    func_001F6B40(a0->f0);
}

s32 func_0018B770(void* p)
{
	return *(s32*)((char*)p + 4) != -1;
}

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
void func_001E2138(void* dst, void* src);

void func_0018B780(Src_18B780* s, Dst_18B780* d)
{
    func_001F5C0C(d, 0, 0x5C);
    func_001E2138(d, s->sub20);
    d->f44 = s->f10;
    if (s->f14 & 0x1) {
        *(s32*)((u8*)d + 0x48) |= 0x1;
    }
    if (s->f14 & 0x2) {
        *(s32*)((u8*)d + 0x48) |= 0x2;
    }
    if (s->f14 & 0x4) {
        *(s32*)((u8*)d + 0x48) |= 0x4;
    }
    if (s->f14 & 0x8) {
        *(s32*)((u8*)d + 0x48) |= 0x8;
    }
    if (s->f14 & 0x20) {
        *(s32*)((u8*)d + 0x48) |= 0x10;
    }
    if (s->f14 & 0x80) {
        *(s32*)((u8*)d + 0x48) |= 0x20;
    }
    if (s->f14 & 0x800) {
        *(s32*)((u8*)d + 0x48) |= 0x40;
    }
    if (s->f14 & 0x1000) {
        *(s32*)((u8*)d + 0x48) |= 0x80;
    }
    d->f4A = s->b5;
    d->f4B = s->b4;
    d->f4C = s->h6;
    d->f4E = s->b3;
    d->f4F = s->b2;
    d->f50 = s->b1;
    d->f52 = s->bD;
    d->f53 = s->bC;
    d->f54 = s->hE;
    d->f56 = s->bB;
    d->f57 = s->bA;
    d->f58 = s->b9;
}

s32 func_0018B910(s32 value)
{
	if (value == 0) return 29;
	if (value > 0) return 30;
	return 31;
}

struct Pair_18BC90 { s32 a; s32 b; };

s32 func_00209B80(void* a0, s32* a1, s32* a2);
s32 func_0018B930(s32 h);
s32 func_0018B988(void* a0, s32 b);
s32 func_0018B930(s32 value)
{
    switch (value) {
    case 0: return 32;
    case 1: return 33;
    case -1: return 34;
    default: return 31;
    }
}

s32 func_0018BC90(void* a0, void* a1, s32* a2)
{
    Pair_18BC90 t;
    s32 r = func_0018B930(func_00209B80(a0, &t.a, &t.b));
    if (a2) {
        *a2 = t.b;
    }
    if (r == 0x21) {
        r = func_0018B988(a1, t.b);
    }
    return r;
}

s32 func_0018BD00(s32 value, void* first, s32 second)
{
	s32 result = func_0018B910(value);
	if (result == 29)
		result = func_0018BC90(0, first, (s32*)second);
	return result;
}

s32 func_0018BFA8(void* lhs, void* rhs)
{
	s32 difference = *(u16*)((char*)lhs + 0x54) - *(u16*)((char*)rhs + 0x54);
	if (difference) return difference;
	difference = *(u8*)((char*)lhs + 0x52) - *(u8*)((char*)rhs + 0x52);
	if (difference) return difference;
	difference = *(u8*)((char*)lhs + 0x53) - *(u8*)((char*)rhs + 0x53);
	if (difference) return difference;
	difference = *(u8*)((char*)lhs + 0x56) - *(u8*)((char*)rhs + 0x56);
	if (difference) return difference;
	difference = *(u8*)((char*)lhs + 0x57) - *(u8*)((char*)rhs + 0x57);
	if (difference) return difference;
	return *(u8*)((char*)lhs + 0x58) - *(u8*)((char*)rhs + 0x58);
}

typedef s32 (*VFnI_0018AAE0)(void* self);

s32 func_001DDA80(void* p);
void func_001B6598(void* dev, s32* out);

s32 func_0018AAE0(C0C* self)
{
    s32 out;
    if (func_001DDA80(self->world) != 0) goto zero;
    if (self->fC10 != 0) goto zero;
    if (self->f724 == 0x10) goto zero;
    if (self->f724 == 0xB) goto zero;
    if (((VFnI_0018AAE0*)self->desc)[0x66](self) == 0) goto zero;
    func_001B6598(self->fE10, &out);
    if (out == 0x43C) goto one;
    if (out < 0x43D) {
        if (out == 0x43A) goto one;
        goto zero;
    }
    if (out == 0x43E) goto one;
zero:
    return 0;
one:
    return 1;
}

s32 D_002649D8[4] = { 16, 16, 11, 0 };
s32 D_002649E8[6] = { 1083, 1085, 1087, 0, 0, 0 };

void func_001AC060(void* p);
void func_001C8F20(void* node, s32 kind, s32 flag);

void func_0018AC58(C0C* self)
{
    func_001AC060((u8*)&D_0026E248);
    s32 idx = self->fE28;
    func_001C8F20(self, D_002649D8[idx], self->fE30[idx]);
    s32 n = self->fE28;
    self->fE3C = D_002649E8[n];
    self->fE28 = n + 1;
}

struct Glob_18BDC8 { u8 pad0[0x25C]; s32 f25C; u8 pad260[8]; s32 f268; };

extern f32 D_00261868[];
extern Glob_18BDC8 D_0026FF68[];

void func_0018B670(G269990* p, void* fn, G264A40* self);
void func_0018C028(G264A40* self, s32 v);
void func_0018D0A0(G264A40* self);
void func_00194D30(Glob_18BDC8* g, s32 a, s32 b);

void func_0018BDC8(G264A40* self)
{
    if (func_0018B770(&D_00269990) != 0) return;
    if (self->f0C == self->f14) {
        if (self->f20 <= D_00261868[0])
            func_0018B670(&D_00269990, (void*)func_0018D0A0, self);
    } else {
        func_0018C028(self, self->f14);
    }
    if (func_0018B770(&D_00269990) != 0) return;
    if (self->f18 == 1 && D_00261868[0] - self->f10 >= 0.3f) {
        if (self->i4F44 != 0) {
            if (self->f0C != 5) func_00194D30(D_0026FF68, 1, 0x15);
        } else if (D_0026FF68->f25C != 0 && D_0026FF68->f268 == 0x11) {
            if (self->f0C != 5) func_00194D30(D_0026FF68, 1, 0x20);
        } else {
            switch (self->f0C) {
            case 1: func_00194D30(D_0026FF68, 1, 3); break;
            case 2: func_00194D30(D_0026FF68, 1, 4); break;
            case 3: func_00194D30(D_0026FF68, 1, 7); break;
            case 4: func_00194D30(D_0026FF68, 1, 10); break;
            }
        }
    }
}

// Matches US and EU: retail's return-1 block is a shared target that every return-1 path branches to.
extern f32 D_0026185C;
extern f32 D_002649C8;

typedef void* (*FnSelf_18A9A8)(void* self);
typedef s32 (*FnSub_18A9A8)(void* self);

struct Loc_18A9A8 {
    u8 buf[0x10];
    s32 code;
};

s32 func_0018A910(void* self, void* a, void* b);
s32 func_00125750(void* a, s32 b, void* c, s32 d, s32 e, s32 f, f32 g);

s32 func_0018A9A8(C0C* self)
{
    u8* obj = (u8*)self;
    Loc_18A9A8 loc;
    void* sub;
    s32 code;

    if (D_0026185C < *(f32*)(obj + 0x748)) {
        return 0;
    }
    sub = ((FnSelf_18A9A8)(*(void***)obj)[0x198 / 4])(obj);
    if (sub == 0) {
        return 0;
    }
    if (*(u32*)((u8*)*(void**)sub + 8) & 8) {
        if (((FnSub_18A9A8)(*(void***)sub)[0x144 / 4])(sub)) {
            return 0;
        }
    }
    func_001B6598(*(void**)(obj + 0xE10), &loc.code);
    code = loc.code;
    if (code != 0x43C) {
        if (code < 0x43D) {
            if (code != 0x43A) {
                return 0;
            }
        } else {
            if (code == 0x43E) {
                goto one;
            }
            return 0;
        }
    }
    if (func_0018A910(obj, obj + 0x140, (u8*)sub + 0x140) != 0) {
        goto second;
    }
one:
    return 1;
second:
    func_00125750(sub, 0, loc.buf, 0, 0, 0, D_002649C8);
    if (func_0018A910(obj, obj + 0x140, loc.buf) == 0) {
        goto one;
    }
    return 0;
}

s32 func_001E2268(s32 a, s32 b);

void func_0018B5C0(G269990* self)
{
    s32 r = func_001E2268(1, 1);
    self->i00 = r; self->f04 = -1; self->f10 = 0x22;
}

void* func_001F5C0C(void* p, s32 zero, s32 size);
void func_0018C178(void* self, s32 value);

void func_0018BD58(G264A40* self, s32 a, s32 b)
{
    func_001F5C0C(self, 0, 0x4F50);
    self->f0C = -1;
    self->f14 = 0;
    func_0018C178(self, 0);
    self->f04 = (void*)a;
    self->f08 = (void*)b;
    self->i4F48 = 0;
    self->i4F44 = 0;
}

// NEAR: same callees, args and frame. Retail saves s2,s1,s0 then moves a2->s2, a1->s1 before the jal and fills its delay slot with self->s0; the compiler places move s0 early and fills the delay slot with move s1.
typedef s32 (*Cb_18A910)(void* self, void* ctx);

s32 func_0018A830(void* self, void* ctx);
void func_0018D608(void* self, void* a1, void* a2);
void func_001DC238(void* a0, s32 a1, void* a2, void* a3, Cb_18A910 a4, void* a5, s32* a6, s32* a7);
s32 func_0018A6C0(s32 a0, void* a1, void* a2, s32 a3, s32 a4, void* a5, f32 f);
void func_0018D6F0(void);
f32 D_002649C4 = 1.5e+02f;

s32 func_0018A910(C0C* self, void* a1, void* a2)
{
    u8 buf[0x70];
    s32 x;
    s32 y;
    func_0018D608(self, a1, a2);
    func_001DC238(self->world, 0, a1, a2, func_0018A830, self, &x, &y);
    s32 r = func_0018A6C0(0, a1, a2, x, y, buf, D_002649C4);
    func_0018D6F0();
    return r != 0;
}

// Hoisting 1.0f into a local `one` matched the constant scheduling.
void func_001B6598(void* a, s32* out);

void func_0018B460(C0C* a0, f32* a1)
{
    s32 kind;
    func_001B6598(a0->fE10, &kind);
    switch (kind) {
    case 0x43A:
        {
            f32 v = D_002623C8->dt * 1.3f - 0.3f;
            f32 one = 1.0f;
            if (v < 0.0f) {
                v = 0.0f;
            } else if (one < v) {
                v = one;
            }
            *a1 = v;
        }
        break;
    case 0x43C:
        {
            f32 v = D_002623C8->dt * 1.3f - 0.3f;
            f32 one = 1.0f;
            if (v < 0.0f) {
                v = 0.0f;
            } else if (one < v) {
                v = one;
            }
            *a1 = v;
        }
        break;
    default:
        *a1 = D_002623C8->dt * D_002623C8->dt;
        break;
    }
}

struct __attribute__((aligned(16))) Cand_18A6C0 { u8 pad0[0x40]; f32 score; u8 pad1[0x70 - 0x44]; };

s32 func_00141D00(void* self, void* p1, void* p2, f32 x, s32 p3, void* p4);

s32 func_0018A6C0(s32 a0, void* a1, void* a2, s32 a3, s32 a4, void* a5, f32 f)
{
    Cand_18A6C0 buf[2];
    s32* table = (s32*)a4;
    s32 best = 0;
    f32 bestScore = 3.4028234663852886e+38f;
    s32 i;

    for (i = 0; i < a3; i++) {
        s32 self = table[i];
        s32 r = func_00141D00((void*)self, a1, a2, f, 2, (void*)buf);
        s32 k = 0;
        if (r > 0) {
            if (buf[0].score == 0.0f && (a0 & 1)) {
                k = 1;
            }
        }
        if (k < r) {
            Cand_18A6C0* c = &buf[k];
            if (c->score < bestScore) {
                bestScore = c->score;
                best = self;
                if (a5 != 0) {
                    *(Cand_18A6C0*)a5 = *c;
                }
            }
        }
    }
    return best;
}

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
    func_00189C28(self, D_00248D20, value);
}

// was NEAR: 2 lines: retail has addiu s2 (self+0xE30) before the first call and li s3,2 in its delay slot; ours swaps them. About 20 rewrites (for/do-while, init placement, decl order, cast offsets) all give the same two swapped lines.
extern s32 D_00264928[10];
extern s32 D_00264950[4];
struct Ent_264960 { s32 key; f32 f; s32 v; };
extern Ent_264960 D_00264960[6];

void func_001C72A0(void* self);
void func_001DDC38(void* sub, void* self);
void func_00124DF8(void* self, s32 n, void* table);
void func_001D36F0(void* self, void* a, void* b);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
s32 func_001CA758(void* self, s32 id);
u8* func_0018D568(s32 size, void* src);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);

struct Ent_18A3F0 { s32 key; s32 pad4; s32 value; };

void func_0018A3F0(C0C* self)
{
    s32 n;
    s32 i;

    func_001C72A0(self);
    func_001DDC38(self->world, self);
    func_00124DF8(self, 3, D_00264928);
    func_001D36F0(self, (u8*)self + 0xC20, (u8*)self + 0xE00);
    self->f758[12].obj = (void*)self->fE00;
    self->fE10 = func_001B6290(self->fE0C, 0, 0x438, 0);
    for (n = 0; n < 3; n++)
        self->fE30[n] = func_001CA758(self, D_00264950[n]);
    self->fE20 = 6;
    self->fE24 = (Ent_18A3F0*)func_0018D568(0x48, D_00264960);
    for (i = 0; i < self->fE20; i++) {
        Ent_18A3F0* e = ((Ent_18A3F0*)self->fE24) + i;
        e->value = func_0015A418(self->world, 1, e->key, self);
    }
}

struct Tail_18B988
{
    static s32 Get(s32 b, s32 v, s32 lim)
    {
        s32 r = v;
        if (b >= lim) r = 31;
        return r;
    }
};

s32 func_0018B988(s32 a, s32 b)
{
    s32 r;
    switch (a) {
    case 1:
        switch (b) {
        case 0: return 0;
        case -1: return 9;
        case -2: return 10;
        case -5: return 11;
        }
        return Tail_18B988::Get(b, 11, -9);
    case 2:
        switch (b) {
        case -2: return 12;
        case -3: return 1;
        case -4: return 13;
        case -5: return 6;
        case -7: return 25;
        }
        if (b >= 0) return 0;
        return Tail_18B988::Get(b, 11, -9);
    case 3:
        switch (b) {
        case 0: return 0;
        case -2: return 12;
        case -4: return 16;
        }
        return Tail_18B988::Get(b, 11, -9);
    case 4:
        switch (b) {
        case -2: return 12;
        case -4: return 16;
        }
        if (b >= 0) return 0;
        return Tail_18B988::Get(b, 11, -9);
    case 5:
        switch (b) {
        case -2: return 12;
        case -4: return 16;
        case -5: return 17;
        }
        if (b >= 0) return 0;
        return Tail_18B988::Get(b, 11, -9);
    case 6:
        switch (b) {
        case -2: return 12;
        case -3: return 1;
        case -4: return 16;
        case -5: return 18;
        case -8: return 26;
        }
        if (b >= 0) return 0;
        return Tail_18B988::Get(b, 11, -9);
    case 10:
        switch (b) {
        case 0: return 0;
        case -2: return 12;
        case -4: return 16;
        }
        return Tail_18B988::Get(b, 11, -9);
    case 11:
        switch (b) {
        case 0: return 0;
        case -2: return 12;
        case -3: return 1;
        case -4: return 24;
        }
        return Tail_18B988::Get(b, 11, -9);
    case 12:
        switch (b) {
        case 0: return 0;
        case -2: return 12;
        case -4: return 21;
        }
        return Tail_18B988::Get(b, 11, -9);
    case 13:
        switch (b) {
        case -2: return 12;
        case -4: return 21;
        }
        if (b >= 0) return 0;
        return Tail_18B988::Get(b, 11, -9);
    case 14:
        switch (b) {
        case 0: return 0;
        case -2: return 12;
        case -4: return 22;
        }
        return Tail_18B988::Get(b, 11, -9);
    case 15:
        switch (b) {
        case 0: return 0;
        case -2: return 12;
        case -4: return 14;
        case -5: return 19;
        case -6: return 23;
        }
        return Tail_18B988::Get(b, 11, -9);
    case 16:
        r = 0;
        if (b != 0) return Tail_18B988::Get(b, 4, 0);
        break;
    case 17:
        r = 0;
        if (b != 0) return Tail_18B988::Get(b, 5, 0);
        break;
    case 18:
        switch (b) {
        case -2: return 12;
        }
        if (b >= 0) return 0;
        return Tail_18B988::Get(b, 11, -9);
    case 19:
        switch (b) {
        case 0: return 0;
        case -2: return 12;
        case -4: return 22;
        }
        return Tail_18B988::Get(b, 11, -9);
    case 20:
        switch (b) {
        case 0: return 0;
        case -403: return 35;
        }
        return 31;
    case 21:
        if (b >= 0) return 0;
        if ((u32)(b + 100) < 100) return 31;
        return Tail_18B988::Get(b, 30, -99);
    default:
        r = 31;
        break;
    }
    return r;
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
    *out = D_002483D0;
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

void func_001F6B60(void* a);
void func_001F6B40(void* a);
s32 func_001F6A30();

void func_0018B600()
{
    func_001F6B60(D_00269990.f00);
    G269990* o = &D_00269990;
    s32 r = o->fn(o->f0C);
    o->f10 = r;
    *(s32*)D_00275960 = -1;
    o->f04 = -1;
    o->f0C = 0;
    o->fn = 0;
    func_001F6B40(D_00269990.f00);
    func_001F6A30();
}

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
    func_001EAD88(in[0], &sc[0], &sc[1]);
    func_001EAD88(in[1], &sc[2], &sc[3]);
    func_001EAD88(in[2], &sc[4], &sc[5]);
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

s32 D_002649B0[5] = { 4, 5, 60, 41, 76 };
s32 func_001300E8(C01* a, s32 b);
s32 func_001833F0(C01* a, s32 b);

typedef s32 (*VFn_18A830)(C01* self, void* arg);
struct Rec_18A830 { u8 pad[0x50]; C01* sub; };

s32 func_0018A830(void* self, Rec_18A830* rec)
{
    s32* e = D_002649B0;
    u32 i;
    for (i = 0; i < 5; e++, i++) {
        if (func_001300E8(rec->sub, *e) != 0) {
            break;
        }
    }
    if (i < 5) {
        return 0;
    }
    if (rec->sub->desc->id == 3) {
        return 0;
    }
    if (func_001300E8(rec->sub, 0x34) != 0) {
        if (((VFn_18A830*)rec->sub->desc)[60](rec->sub, self) == 0) {
            return 0;
        }
    }
    if (func_001833F0(rec->sub, 0x449) != 0 || func_001833F0(rec->sub, 0x44A) != 0) {
        return 0;
    }
    return 1;
}

void func_001EAD88(f32 angle, f32* s, f32* c);

void func_00188850(f32* axis, Mat4* mat, f32 angle)
{
    f32 s;
    f32 c;
    s32 i;
    s32 j;
    f32 t;

    func_001EAD88(angle, &s, &c);
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

void func_001A8C90(void* obj, s32 v);
void func_001C9DE0(void* self, s32 code, void* req);
void func_001B6598(void* dev, s32* out);
f32 D_00264A34 = 20.0f;
extern f32 D_00264A38;

void func_0018B340(C0C* self, s32 a1, Key_18B340* key)
{
    if (a1 == 0x13 && key->a == (s32)self->f7E0) {
        switch (key->b) {
        case 0x442:
        case 0x443: {
            Obj_18B340* obj;
            if (key->b == 0x442) {
                obj = (Obj_18B340*)self->fE18;
            } else {
                obj = (Obj_18B340*)self->fE1C;
            }
            s32 kind;
            func_001B6598(self->fE10, &kind);
            switch (kind) {
            case 0x43A:
            case 0x43C:
                obj->fF0 = (*(Quad_18B340*)&self->vE40);
                *(f32*)((u8*)obj + 0xF8) = self->v140.z + D_00264A34;
                break;
            case 0x43E:
                obj->fF0 = (*(Quad_18B340*)&self->vE40);
                *(f32*)((u8*)obj + 0xF8) = *(f32*)((u8*)obj + 0xF8) + D_00264A38;
                break;
            }
            func_001A8C90(obj, 1);
            return;
        }
        case 0x444:
            self->fE2C = 1;
            break;
        case 0x445:
            self->fE2C = 0;
            break;
        }
    }
    func_001C9DE0(self, a1, key);
}

void func_0018D608(void);
void* func_0018D658(s32 size);
void func_0018D800(void* dst, void* src, s32 count);
void func_0018D6F0(void);

// Inverts the n-by-n matrix a into b by Gauss-Jordan elimination with partial
// pivoting, on a scratch copy; returns 0 when a is singular.
s32 func_00189438(s32 n, f32* a, f32* b)
{
    s32 ok = 0;
    func_0018D608();
    s32 size = n * n * 4;
    f32* m = (f32*)func_0018D658(size);
    func_0018D800(m, a, size);
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
    func_0018D6F0();
    return ok;
}

// Data definitions.
Ent_264910 D_00264910[2] = { { 0, 0x82, 0xC24 }, { 0, 0x83, 0xC74 } };
s32 D_00264928[10] = { 1, 0x437, 0xE0C, 0, 0x440, 0xE18, 0, 0x441, 0xE1C, 0 };
s32 D_00264950[4] = { 0x446, 0x447, 0x448, 0 };
Ent_264960 D_00264960[6] = {
    { 0x35, 50.0f, 0 }, { 0x36, 50.0f, 0 }, { 0x38, 80.0f, 0 },
    { 0x3B, 80.0f, 0 }, { 0x60, 70.0f, 0 }, { 0x50, 220.0f, 0 }
};
f32 D_002649C8 = 0.25f;
extern const Quad_1884C0 D_0024B260 = { 0, 0, 0, 0x3F800000 };
extern const f32 D_0024B270[4] = { 3.4028235e38f, 0.0f, 0.0f, 0.0f };
