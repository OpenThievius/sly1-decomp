// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"


struct Obj_1C29E8 { u8 pad[8]; s32 f8; s32 fC; };

void func_001C29E8(Obj_1C29E8* o)
{
    o->fC = 0;
    o->f8 = 0;
}

void func_001921A8(void* self);

struct Obj_1C3390 { u8 pad[0x610]; s32 f610; u8 pad2[0x694 - 0x614]; s32 f694; };

void func_001C3390(Obj_1C3390* self)
{
    func_001921A8(self);
    self->f610 = -1;
    self->f694 = 5;
}

bool func_001E9970();

typedef void (*VFn_1C3928)(void*);
struct Obj_1C3928 { VFn_1C3928* vtbl; };
extern Obj_1C3928 D_0026DD48;
extern Obj_1C3928 D_0026DFC8;

// NEAR: the two lui immediates for D_0026DD48 / D_0026DFC8 come out wrong in check.py (see results.tsv note).
void func_001C3928()
{
    if (func_001E9970()) {
        D_0026DD48.vtbl[14]((void*)&D_0026DD48);
        D_0026DFC8.vtbl[14]((void*)&D_0026DFC8);
    } else {
        D_0026DD48.vtbl[15]((void*)&D_0026DD48);
        D_0026DFC8.vtbl[15]((void*)&D_0026DFC8);
    }
}

struct Entry_1C3C00 { s32 first; u8 pad[60]; };
struct Obj_1C3C00 { u8 p0[0x67C]; s32 f67C; s32 f680; s32 f684; s32 f688; u8 p1[0x694 - 0x68C]; s32 f694; };
s32 func_001300E8(s32 a, s32 b);
s32 func_001833F0(s32 a, s32 b);

void func_001C3C00(Obj_1C3C00* self, Entry_1C3C00* table, s32 idx)
{
    Entry_1C3C00* e = (Entry_1C3C00*)((u8*)table + ((1 - idx) << 6));
    if (func_001300E8(e->first, 0x21)) {
        if (self->f694 > 0) {
            self->f680 = 1;
            return;
        }
        if (self->f67C == 0) self->f684 = e->first;
        return;
    }
    if (func_001833F0(e->first, 0x52F)) self->f688 = e->first;
}

void func_00192C58(void* self);
void func_001C3FC8(void* self, s32 flag);

void func_001C3E80(void* self)
{
    func_00192C58(self);
    func_001C3FC8(self, 1);
}

typedef void (*VFn_1C3F68)(void*, void*);
struct Obj_1C3F68 { VFn_1C3F68* vtbl; };
struct Local_1C3F68 { s32 pad[2]; s32 value; VFn_1C3F68 fn; };
void func_001D7098(void* self, s32 a, s32 b);
void func_001C3EB0(void* self, void* data);

void func_001C3F68(Obj_1C3F68* self, s32 value)
{
    Local_1C3F68 local;
    func_001D7098(&local, 0, value);
    local.value = value;
    local.fn = func_001C3EB0;
    self->vtbl[80]((void*)self, (void*)&local);
}

void func_001C06A0(s32 a, s32 b, f32 x);

void func_001C0000(s32 flag, f32 x)
{
    func_001C06A0(6, 0, x);
    func_001C06A0(6, 2, x);
    func_001C06A0(6, 3, x);
    if (flag) {
        func_001C06A0(6, 1, x);
    }
}

struct Obj_001C3E50 { u8 pad[0x610]; s32 state; u8 pad2[0x24]; s32 value; };
s32 func_001C3E50(Obj_001C3E50* self) { if (self->state < 5) { if (self->state >= 2) return 1; } return self->value != 0; }

struct __attribute__((packed)) Pk8_1C33C8 { u64 v; };
struct __attribute__((packed)) Pp_1C33C8 { void* p; };

struct Obj_1C33C8 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0xD0 - 0x18];
    f32 fD0;
    f32 fD4;
    u8 pad2[0x3CC - 0xD8];
    f32 f3CC;
    u8 pad3[0x62C - 0x3D0];
    void* f62C;
    Pk8_1C33C8 f630;
    u8 pad4[0x644 - 0x638];
    f32 f644;
    f32 f648;
    u8 pad5[0x660 - 0x64C];
    void* f660;
    void* f664;
    void* f668;
    u8 pad6[0x68C - 0x66C];
    f32 f68C;
    u8 pad7[0x71C - 0x690];
    s32 count;
    void* f720[16];
};

extern char D_00274A40[4];
extern s32 D_002749B0[36];

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void* func_001B6290(void* a, void* self, s32 b, s32 c);
f32 func_00205778(f32 a, f32 b);
void func_001DDC38(void* sub, void* self);
void func_001C3FC8(void* self, s32 flag);

void func_001C33C8(Obj_1C33C8* self)
{
    func_00124A48(self);
    self->f68C = self->f3CC;
    func_00124DF8(self, 0xC, D_002749B0);
    self->f668 = func_001B6290(self->f664, self, -1, 0);
    self->f644 = func_00205778(self->fD4, self->fD0);
    Obj_1C33C8* v = (Obj_1C33C8*)self->f660;
    self->f648 = func_00205778(v->fD4, v->fD0);
    self->f630 = *(Pk8_1C33C8*)((u8*)self->f62C + 0x2DC);
    u8* g1 = (u8*)&D_0026DD48;
    ((Pp_1C33C8*)(g1 + 0x264))->p = (u8*)self + 0x690;
    u8* g2 = (u8*)&D_0026DFC8;
    ((Pp_1C33C8*)(g2 + 0x264))->p = (u8*)self + 0x694;
    *(void**)(g1 + 0x268) = D_00274A40;
    *(f32*)(g2 + 0x26C) = 4.0f;
    func_001DDC38(self->f14, self);
    s32 c = self->count;
    self->f720[c] = self;
    self->count = c + 1;
    func_001C3FC8(self, 1);
}

// NEAR: retail ends the zero path with beqz + move $v0,$zero and falls into li $v0,1; ours folds the call result into sltu $v0,$zero,$v0 (2 lines differ).

struct Obj_1C3D28 { u8 pad[0x14]; void* f14; };
extern s32 D_00262C64;
s32 func_001DDA80(void* p);

s32 func_001C3D28(Obj_1C3D28* self)
{ if ((D_00262C64 & 1) || func_001DDA80(self->f14)) return 1; return 0; }

// EXACT: declare D_0026185C as extern f32 D_0026185C[] and read [0]

typedef s32 (*VFnA_1C3D60)(void* self, s32 v);
typedef void (*VFnB_1C3D60)(void* self, s32 v, void* data);
typedef void (*VFnC_1C3D60)(void* a0, void* self);
struct Obj_1C3D60 {
    void** vtbl;
    u8 pad0[0x610 - 4];
    s32 f610;
    u8 pad1[0x638 - 0x614];
    s32 f638;
    f32 f63C;
};

struct Arg_1C3D60 {
    s32 f0;
    s32 f4;
    void* f8;
    VFnC_1C3D60 fC;
};
struct Local_1C3D60 { void* self; s32 v; };
extern f32 D_0026185C[];
s32 func_00160C58();
void func_001C3FC8(void* self, s32 flag);

s32 func_001C3D60(Obj_1C3D60* self, Arg_1C3D60* arg)
{
    Local_1C3D60 local;
    s32 m;
    if (((VFnA_1C3D60)self->vtbl[79])(self, arg->f0)) return 0;
    if (arg->f0 == 0) {
        if (arg->fC != 0) arg->fC(arg->f8, self);
    }
    m = self->f610;
    if (m < 5) {
        if (!(m < 2)) return 1;
    }
    if (self->f638 != 0) return 1;
    if (func_00160C58()) {
        func_001C3FC8(self, 2);
        self->f638 = 1;
        self->f63C = D_0026185C[0];
    } else {
        func_001C3FC8(self, 3);
    }
    local.self = self;
    local.v = arg->f4;
    ((VFnB_1C3D60)self->vtbl[18])(self, 0x17, &local);
    return 1;
}

struct Vt_1C34C8 { void* pad[7]; void (*f1C)(void*); void* pad2[0x1A]; void (*f88)(void*, void*); };
struct Obj_1C34C8_Vt { Vt_1C34C8* vt; };
struct Sub_1C34C8 { u8 pad[8]; struct Sub2_1C34C8* p8; u8 padC[8]; f32 f14; f32 f18; };
struct Sub2_1C34C8 { u8 pad[0x34]; f32 f34; };
struct Obj_1C34C8 {
    u8 pad0[0x14]; void* host;
    u8 pad1[0xD0 - 0x18]; f32 fD0; f32 fD4;
    u8 pad2[0x3CC - 0xD8]; f32 f3CC; f32 f3D0;
    u8 pad3[0x610 - 0x3D4]; s32 s610; f32 f614;
    u8 pad4[0x62C - 0x618]; u8* p62C; f32 f630; f32 f634; s32 s638; f32 f63C; f32 f640;
    u8 pad5[4]; f32 f648;
    u8 pad6[0x660 - 0x64C]; Obj_1C34C8_Vt* p660;
    u8 pad7[0x670 - 0x664]; f32 f670;
    u8 pad8[4]; void* p678; Sub_1C34C8* p67C; s32 s680; s32 s684; Obj_1C34C8_Vt* p688;
    f32 f68C; s32 s690; s32 s694;
};

f32 D_00274A50[4] = { 0.2f, 0.0f, 0.0f, 0.0f };
f32 D_00274A70[4] = { 1.0f, 0.0f, -0.75f, 0.0f };
f32 D_00274A80[4] = { 0.7f, 0.3f, 0.0f, 0.0f };
extern f32 D_00275C60[];
extern f32 D_00261854;
extern f32 D_00261858[];
extern f32 D_00274A44;
f32 D_00274A60[4] = { 4e+01f, 0.0f, 0.3f, 0.0f };
extern u8 D_00248D20[];
extern s32 D_0026E228[8];

void func_00192B58(void* self, f32 t);
void* func_0015A838(void* a, s32 b, s32 c, s32 d);
void func_00158730(void* x);
void func_001C3F68(void* self, s32 v);
void func_0012E760(void* p);
void func_0012C7B0(void* a, void* b, s32 c, void* d, f32 fa, f32 fb);
f32 func_00205778(f32 a, f32 b);
void func_00188850(void* a, void* b, f32 f);
void func_001EA918(void* a, void* b, void* c, void* d, s32 e, f32 f);
f32 func_00205210(f32 a);
void func_00126A48(void* o, u32 v);

void func_001C34C8(Obj_1C34C8* self, f32 t)
{
    f32 buf[12];
    f32 buf2[12];
    u32 ca[4];
    u32 cb[4];
    func_00192B58(self, t);
    if (self->p688) {
        void* h = func_0015A838(self->host, 0x101, 0x77, (s32)self->p688);
        if (h) func_00158730(h);
        self->s690 = self->s690 + 1;
        self->p688->vt->f1C(self->p688);
        self->p688 = 0;
    }
    if (self->s684) {
        func_001C3F68(self, self->s684);
        self->s684 = 0;
    }
    if (self->p67C) {
        if (self->p67C->f18 == 0.0f) {
            func_0012E760(self->p67C);
            self->p67C = 0;
        }
    } else if (self->s680) {
        func_0012C7B0(self->p678, self, 0, &self->p67C, 0.0f, 1.0f);
        self->s694 = self->s694 - 1;
        D_0026E228[0] = -1;
    }
    self->s680 = 0;
    f32 u;
    if (self->p67C) {
        f32* lim = D_00275C60;
        f32 r = self->p67C->f14 / self->p67C->p8->f34;
        f32* pp = D_00274A50;
        f32 lo = lim[0];
        f32 hi = lim[1];
        f32 v = pp[0] + r * (pp[1] + r * pp[2]);
        if (v < lo) v = lo;
        else if (hi < v) v = hi;
        D_00261854 = v;
        u = r;
    } else {
        D_00261854 = 1.0f;
        u = 0.0f;
    }
    f32 w = u * D_00274A44 + (1.0f - u) * self->f68C;
    self->f3D0 = w;
    self->f3CC = w;
    if (self->s638) {
        if (D_0026185C[0] - self->f640 > 2.0f) self->s638 = 0;
    }
    f32 ang = func_00205778(self->fD4, self->fD0);
    func_00188850(D_00248D20, buf, self->f648 - ang);
    func_001EA918((u8*)self->p660 + 0xD0, buf, D_00274A60, buf2, 0, t);
    self->p660->vt->f88(self->p660, buf2);
    ca[0] = 0x8010FF00;
    cb[0] = 0x800000FF;
    if (self->s638) {
        f32 q;
        if (self->s610 != 2) q = (D_00261858[1] - self->f614) * 0.5f;
        else q = 0.0f;
        f32 z = func_00205210((D_00261858[1] - self->f63C) * 10.0f);
        f32 x0 = D_00274A70[0] + q * (D_00274A70[1] + q * D_00274A70[2]);
        f32 lo = D_00275C60[0];
        f32 hi = D_00275C60[1];
        f32 x = x0 < lo ? lo : (hi < x0 ? hi : x0);
        f32 y = D_00274A80[0] + z * (D_00274A80[1] + z * D_00274A80[2]);
        f32 lo2 = D_00275C60[0];
        f32 hi2 = D_00275C60[1];
        if (y < lo2) y = lo2;
        else if (hi2 < y) y = hi2;
        f32 m = x * y;
        f32 n = 1.0f - m;
        f32 r0 = n * ((u8*)ca)[0] + m * ((u8*)cb)[0];
        f32 r1 = n * ((u8*)ca)[1] + m * ((u8*)cb)[1];
        f32 r2 = n * ((u8*)ca)[2] + m * ((u8*)cb)[2];
        ((u8*)ca)[0] = (s32)r0;
        ((u8*)ca)[2] = (s32)r2;
        ((u8*)ca)[1] = (s32)r1;
    }
    func_00126A48(self, ca[0]);
    *(f32*)(self->p62C + 0x2DC) = self->f670 * self->f630;
    *(f32*)(self->p62C + 0x2E0) = self->f670 * self->f634;
    *(s32*)(self->p62C + 0x32C) = 0;
}

// EXACT: callee func_001EA728 declared with float params first

struct Obj_1C3FC8;
struct Vt_1C3FC8 {
    u8 pad[0x94];
    void (*f94)(Obj_1C3FC8* self, void* q);
};
struct __attribute__((aligned(16))) Quad_1C3FC8 { f32 v[4]; };
struct Obj_1C3FC8 {
    Vt_1C3FC8* vt;
};

extern f32 D_00261858[];
extern Quad_1C3FC8 D_00248D30;
extern u8 D_00274AA8[];
extern s32 D_0026E228[8];
extern u8 D_00261EF0[];
extern u8 D_0026FF68[];
extern const f32 D_0024D560[4];

f32 func_00205778(f32 a, f32 b);
f32 func_001EA408(f32 a);
void func_001EA728(f32 x, f32 y, f32 z, u8* a, void* out);
void func_00151E20(u8* a, f32 b);
void func_00194D30(u8* a, s32 b, s32 c);
void func_0012C918(void* a, Obj_1C3FC8* b, s32 c, void* d, f32 e, f32 f);

#define F(o, off) (*(f32*)((u8*)(o) + (off)))
#define W(o, off) (*(s32*)((u8*)(o) + (off)))
#define P(o, off) (*(void**)((u8*)(o) + (off)))

void func_001C3FC8(Obj_1C3FC8* self, s32 state)
{
    void* s2;
    f32 f12;
    if (state == W(self, 0x610)) return;
    if (W(self, 0x610) == 2) {
        f32 t = D_00261858[1];
        W(self, 0x694) = 3;
        F(self, 0x640) = t;
    }
    W(self, 0x670) = 0;
    if (state < 4) if (state >= 2) {
        Quad_1C3FC8 q;
        f32 a = func_00205778(F(self, 0x154), F(self, 0x150));
        f32 b = func_001EA408(a + 3.14159274f);
        F(self, 0x644) = b;
        F(self, 0x648) = b;
        q = D_00248D30;
        f32 r = func_00205778(F(self, 0xD4), F(self, 0xD0));
        func_001EA728(r, F(self, 0x644), 0.0f, D_00274AA8, (u8*)&q + 8);
        self->vt->f94(self, &q);
        W(self, 0x694) = 0;
        D_0026E228[0] = -1;
        if (state == 3) func_00151E20(D_00261EF0, 1.0f);
    }
    f12 = 0.0f;
    switch (state) {
    case 0: s2 = P(self, 0x618); break;
    case 1: s2 = P(self, 0x61C); break;
    case 2: s2 = P(self, 0x620); F(self, 0x640) = D_0024D560[0]; break;
    case 3: s2 = P(self, 0x624); break;
    case 4:
        func_00194D30(D_0026FF68, 0, 0x1A);
        s2 = P(self, 0x624);
        f12 = F(s2, 0x34);
        break;
    }
    func_0012C918(s2, self, 1, (u8*)self + 0x628, f12, 1.0f);
    W(self, 0x610) = state;
    F(self, 0x614) = D_00261858[1];
}

struct Builder_1C30E8 {
    u8 pad0[0x98];
    s32 f98;
    u8 rest[0x1850 - 0x9C];
};
struct __attribute__((packed)) Col_1C30E8 { u8 r, g, b, a; };
struct Elem_1C30E8 { f32 f0; f32 f4; u8 pad8[8]; f32 v10[4]; f32 v20[4]; };
struct Poly_1C30E8 {
    f32 c[3];
    f32 Eval(f32 t) { return c[0] + t * (c[1] + t * c[2]); }
};
struct Range_1C30E8 {
    f32 lo;
    f32 hi;
    f32 Clamp(f32 v)
    {
        f32 l = lo;
        f32 h = hi;
        if (v < l)
            v = l;
        else if (h < v)
            v = h;
        return v;
    }
};
struct Rec_1C30E8 {
    struct Obj_1C30E8* f0;
    s32 f4;
    s32 f8;
    s32 fC;
    f32 f10;
    u8 pad14[0x3C];
    Poly_1C30E8 poly;
    u8 pad5C[4];
    Elem_1C30E8 elems[1];
};
struct Obj_1C30E8 {
    u8 pad0[0x50];
    f32 f50;
    u8 pad54[0xC];
    Rec_1C30E8* f60;
};
struct Obj2_1C30E8 { u8 pad0[0x2A8]; f32 f2A8; };
struct Glob_1C30E8 { u8 pad[1]; };

extern u8 D_002622A8[];
extern u8 D_002483D0[];
extern u8 D_00274998[8];
extern u8 D_002749A0[16];
extern f32 D_00261858[];

void func_001619C0(Builder_1C30E8* b);
void func_00152B38(Glob_1C30E8* g);
void func_00161AB0(Builder_1C30E8* b, u8* a, u8* c);
void func_00161BB0(Builder_1C30E8* b, s32 v);
void func_00161B10(Builder_1C30E8* b, u8* a, f32 f);
void func_001626C0(Builder_1C30E8* b, u8* src);
void func_001626A8(Builder_1C30E8* b, Col_1C30E8* c);
void func_00162680(Builder_1C30E8* b, void* v);
void func_001626D8(Builder_1C30E8* b, s32 z);
void func_00162508(Builder_1C30E8* b);
void func_00152D70(Glob_1C30E8* g);
void func_00161A88(Builder_1C30E8* b, s32 f);

void func_001C30E8(Obj_1C30E8* self)
{
    Builder_1C30E8 b;
    Col_1C30E8 c;
    Col_1C30E8 c2;
    Rec_1C30E8* r = self->f60;
    s32 none = -1;
    s32 best = none;
    u32 size = sizeof(Elem_1C30E8);
    u32 idx;
    func_001619C0(&b);
    *(u32*)&c = 0xFFFFFFFF;
    func_00152B38((Glob_1C30E8*)D_002622A8);
    b.f98 = 0;
    func_00161AB0(&b, ((u8*)&D_00248D30), D_002483D0);
    func_00161BB0(&b, r->f4);
    func_00161B10(&b, ((u8*)&D_00248D30), ((Obj2_1C30E8*)r->f0)->f2A8);
    idx = r->f8;
    if (idx != r->fC) {
        do {
            f32 zero = 0.0f;
            f32 full = 255.0f;
            Elem_1C30E8* e = (Elem_1C30E8*)((u8*)r->elems + idx * size);
            f32 t = D_00261858[1] - e->f0;
            f32 v = (*(Range_1C30E8*)&D_00275C60).Clamp(r->poly.Eval(t));
            f32 w = self->f50 * e->f4 * v;
            if (zero < w) {
                w = w * full;
                if (best <= none)
                    best = idx;
                c.a = (s32)w;
            } else {
                c.a = 0;
            }
            func_001626C0(&b, D_00274998);
            idx++;
            c2 = c;
            func_001626A8(&b, &c2);
            func_00162680(&b, e->v10);
            func_001626D8(&b, 0);
            c.a = (s32)((f32)c.a * r->f10);
            func_001626C0(&b, D_002749A0);
            c2 = c;
            func_001626A8(&b, &c2);
            func_00162680(&b, e->v20);
            func_001626D8(&b, 0);
            if (idx >= 0x40)
                idx = 0;
        } while (idx != r->fC);
    }
    if (best >= 0)
        r->f8 = best;
    else
        r->f8 = r->fC;
    func_00162508(&b);
    func_00152D70((Glob_1C30E8*)D_002622A8);
    func_00161A88(&b, 2);
}

struct Ent_1C0070;
struct Frame_1C0070 {
    void* f0; u8* f4; s32 f8; Frame_1C0070* fC;
    Ent_1C0070* Next() { Ent_1C0070* n = *(Ent_1C0070**)f4; f4 = (u8*)n + f8; return n; }
};
struct Vt_1C0070;
struct Owner_1C0070 { Vt_1C0070* vt; };
struct Vt_1C0070 { u8 pad[0x48]; void (*f48)(Owner_1C0070* o, s32 a, void* e); };
struct Ent_1C0070 {
    s32 f0; s32 f4; s32 f8; u8 pad0c[0x08]; f32 f14;
    s32 f18; u8 pad1c[0x04];
    u8 f20[0x10];
    Owner_1C0070* f30; f32 f34; f32 f38; s32 f3C; s32 f40; s32 f44; s32 f48; u8 f4C;
    u8 pad4d[3];
    s32 f50; s32 f54; f32 f58; u8 pad5c[0x18];
    f32 f74; f32 f78;
};
struct Pair_1C0070 { s32 a; s32 b; };

extern u8* D_00275710;
extern Frame_1C0070* D_0027472C;
extern s32 D_00274744;
extern s32 D_00274730;
extern s32 D_00274738;
extern s32 D_00274734;
s32 D_00274754 = 3;
extern s32 D_002748EC;
f32 D_00274750 = -2.0f;
extern f32 D_00261858[];
extern Pair_1C0070 D_00245024[];

s32 func_001BF1F0(void);
void* func_001BF3D0(void);
typedef f32 (*Fn_1C0070)(void* a, void* b);
Fn_1C0070 func_001BF578(void);
s32 func_0011D708(Frame_1C0070* h);
void func_0011D928(s32 a);
void func_001C06A0(s32 a, s32 b, f32 x);
s32 func_00182FC8(Owner_1C0070* o);
void func_0011D600(s32 h);
void func_0011D730(s32 h, void (*fn)(void), s64 arg);
void func_001BFFC8(void);
void func_001BFBF8(Ent_1C0070* e);
void func_001BF200(f32 r, void* pos, s32* o1, s32* o2, f32 a, f32 b, f32 c);
s32 func_0011D598(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
void func_001BF428(Ent_1C0070* e);
void func_001BF7F8(Ent_1C0070* e, f32 x);
void func_001BE860(Ent_1C0070* e);
void func_001BF788(Ent_1C0070* e, s32 n);
s32 func_0011CE30(void);

void func_001C0070(void)
{
    Frame_1C0070 f;
    if (func_001BF1F0() != 0) return;
    void* v4 = func_001BF3D0();
    Fn_1C0070 v5 = func_001BF578();
    u8* P = D_00275710 + 0x1BAC;
    Frame_1C0070* saved = (Frame_1C0070*)D_0027B314;
    f.f0 = P;
    f.f4 = P;
    f.f8 = *(s32*)(P + 8);
    f.fC = saved;
    D_0027B314 = (ListFrame*)&f;
    if (D_0027472C != 0 && func_0011D708(D_0027472C) == 0) {
        if (D_00274744 != 0) {
            func_001C06A0(8, 1, 1.0f);
            func_001C06A0(8, 0, 1.0f);
            func_001C06A0(8, 3, 1.0f);
        }
        D_0027472C = 0;
        D_00274744 = 0;
        D_00274730 = 0;
    }
    if (D_00274738 != -100) {
        s32 up = D_00274738 < D_00274734;
        if (D_00274734 > 0 && up) {
            func_0011D928(D_00274734 + 0x14);
            D_00274738 = D_00274734;
            func_001C06A0(7, 1, 1.0f);
            D_002748EC = 0;
        } else {
            D_00274754 = D_00274754 - 1;
            if (D_00274754 < 0) {
                s32 a = D_00274738;
                s32 v = (D_00274734 < a) ? a - 1 : a + 1;
                D_002748EC = (u32)v >> 31;
                D_00274738 = v;
                func_0011D928(v + 0x14);
                if (D_00274738 < 0) {
                    f32 cnv = (f32)D_00274738;
                    f32 k = -0.05f;
                    f32 zero = 0.0f;
                    f32 one = 1.0f;
                    f32 x = cnv * k;
                    f32 y;
                    if (x < zero) y = zero;
                    else if (one < x) y = one;
                    else y = x;
                    f32 m = y * 0.6666667f;
                    func_001C06A0(7, 1, (1.0f - y) + m);
                }
                D_00274754 = D_00274754 + 3;
            }
        }
        if (up ? !(D_00274738 < D_00274734) : !(D_00274738 > D_00274734)) {
            D_002748EC = (u32)D_00274738 >> 31;
            func_0011D928(D_00274734 + 0x14);
            D_00274738 = -100;
        }
    }
    Ent_1C0070* e;
    {
        while ((e = f.Next()) != 0) {
            u8* s1;
            f32 r;
            if (e->f30 != 0 && func_00182FC8(e->f30) == 0) {
                func_001BF788(e, 0);
                goto next;
            }
            if (e->f40 == 0) {
                if (e->f48 != 0) {
                    if (0.0f <= e->f78) {
                        e->f18 = 0;
                    } else {
                        if (e->f30 != 0) e->f30->vt->f48(e->f30, 9, e);
                        if (e->f3C == 0) goto kill;
                        func_0011D600(e->f18);
                        e->f18 = 0;
                    }
                    e->f48 = 0;
                    e->f40 = 1;
                    goto next;
                }
                e->f4C = (e->f4C + 1) % 4;
                if (e->f4C == 0) {
                    func_0011D730(e->f18, func_001BFFC8, ((s64)e->f4 << 32) | (s64)(s32)e);
                }
            }
            if (0.0f <= e->f78) {
                f32* s1 = D_00261858;
                if (s1[1] < e->f74) {
                    if (e->f40 != 0) goto next;
                } else {
                    func_001BFBF8(e);
                    if (e->f40 != 0) {
                        if (s1[1] - D_00274750 < 1.0f) goto next;
                        D_00274750 = s1[1];
                    }
                }
            }
            if (e->f44 == 0) goto next;
            {
                s1 = (u8*)e + 0x20;
                if (e->f30 != 0) s1 = (u8*)e->f30 + 0x140;
                r = v5(v4, s1);
                if (e->f34 < r) {
                    if (0.0f <= e->f78) goto next;
                    if (e->f40 != 0) goto next;
                    if (e->f3C != 0 || 0.0f < e->f74) {
                        func_0011D600(e->f18);
                        e->f18 = 0;
                        e->f40 = 1;
                        goto next;
                    }
                kill:
                    func_001BF788(e, 0);
                    goto next;
                }
                func_001BF200(r, s1, &e->f50, &e->f54, e->f14, e->f34, e->f38);
            }
            if (e->f40 != 0 && e->f0 != -2) {
                e->f18 = func_0011D598(e->f8, D_00245024[e->f0].a, 0, 0, 0, 0);
                e->f40 = 0;
            }
            func_001BF428(e);
            func_001BF7F8(e, e->f58);
            func_001BE860(e);
        next:;
        }
    }
    func_0011CE30();
    D_0027B314 = (ListFrame*)f.fC;
}

// Data definitions (retail values)
s32 D_0026E228[8] = { 0 };
f32 D_00274758[11][4] = { 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
f32 D_00274838[11][4] = { 0 };
s32 D_00274830;
u8 D_002748E8[4] = { 0 };
u8 D_00274998[8] = { 0, 0, 0, 0, 0, 0, 0x80, 0x3F };
u8 D_002749A0[16] = { 0 };
s32 D_002749B0[36] = { 4, 1317, 1632, 4, 1320, 1580, 2, 354, 1420, 2, 355, 1424, 6, 352, 1412, 0, 1319, 1636, 0, 1321, 1560, 0, 1322, 1564, 0, 1323, 1568, 0, 1324, 1572, 0, 1325, 1652, 0, 1326, 1656 };
char D_00274A40[4] = "\r";
extern const f32 D_0024D560[4] = { 3.4028235e+38f, 0.0f, 0.0f, 0.0f };

// Data of src/main/file_1C05D0.cpp, defined here until the file's own data is proved.
struct Pk8_1C0A50 { u64 v; } __attribute__((packed));
Pk8_1C0A50 D_00274820 = { 0x40C0000040800000ULL };
Pk8_1C0A50 D_00274828 = { 0x45FA0000453B8000ULL };
s32 D_00274808[6] = { 0, 2, 3, 4, 9, 1 };
