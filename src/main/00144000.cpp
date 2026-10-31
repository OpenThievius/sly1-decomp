// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

extern u8 D_002619A0[];
void func_0012AA28(void* a, s32 b);
void func_001289C0(void* a, void* b);
void func_00124DF8(void* a, s32 b, void* c);

void func_001463C0(void* self, void* arg)
{
    func_0012AA28(self, 1);
    func_001289C0(self, arg);
    func_00124DF8(self, 5, D_002619A0);
}

struct Obj_146418 {
    u8 pad0[0x374];
    u8 tail[8];      // 0x374: copied unaligned, 8 bytes
    s32 f37C;
};

void func_00127048(void* a, void* b);

void func_00146418(Obj_146418* self, void* arg)
{
    s32 keep = self->f37C;
    u64 tmp;
    __builtin_memcpy(&tmp, self->tail, 8);
    func_00127048(self, arg);
    __builtin_memcpy(self->tail, &tmp, 8);
    self->f37C = keep;
}

struct Obj_146470;
struct Glob_146470 {
    u8 pad0[0x19D8];
    s32 f19D8;
    s32 f19DC;
};

extern Glob_146470* D_002623C0;
extern u8 D_00261420[];
void func_00124A48(void* a);
void* func_0015A838(void* a, s32 b, s32 c, void* d);
s32 func_00141008(void* a, s32 b);

struct Obj_146470 {
    void** vtbl;
    u8 pad04[0x10];
    void* f14;
    u8 pad18[0x2D8 - 0x18];
    s32 f2D8;
    u8 pad2DC[0x2EC - 0x2DC];
    void* f2EC;
    u8 pad2F0[0x37C - 0x2F0];
    s32 f37C;
};

void func_00146470(Obj_146470* self)
{
    func_00124A48(self);
    void* r = func_0015A838(self->f14, 1, 0x75, self);
    self->f2EC = r;
    if (r != 0) {
        ((void (*)(void*))((void**)*(void***)r)[7])(r);
    }
    Glob_146470* g = D_002623C0;
    if (((g->f19D8 << 8) | g->f19DC) != 0x308) {
        if (func_00141008(D_00261420, self->f37C)) {
            self->f2D8 = 2;
        }
    }
    ((void (*)(void*, s32))self->vtbl[51])(self, self->f2D8);
}

struct Obj_1473E0;
struct Other_1473E0 {
    u8 pad0[0xC];
    s32 fC;
};
struct Obj_1473E0 {
    void** vtbl;
    u8 pad04[0x340 - 4];
    s32 f340;
};

s32 func_001473E0(Obj_1473E0* self, Other_1473E0* b)
{
    if (self->f340 != 0) {
        if (b->fC & 0x10) {
            ((void (*)(void*, s32))self->vtbl[51])(self, 1);
        }
    }
    return 1;
}

struct Obj_147ED0 {
    void** vtbl;
};

void func_00147ED0(Obj_147ED0* self)
{
    ((void (*)(void*, s32))self->vtbl[51])(self, 2);
}

extern s32 D_00270458;
extern f32 D_00261860;
void func_00147428(void* a);

void func_00147FB0(void* self)
{
    func_00147428(self);
    if (*(s32*)((u8*)self + 0x2D0) != 0) return;
    if (*(void**)((u8*)self + 0x338) == 0) return;
    if (D_00270458 != 2) {
        *(f32*)((u8*)self + 0x398) = *(f32*)((u8*)self + 0x398) - D_00261860;
    }
    if (*(f32*)((u8*)self + 0x398) <= 0.0f) {
        void** vt = *(void***)self;
        ((void (*)(void*, s32))vt[51])(self, 6);
    }
}

struct Obj_146130 {
    u8 pad0[0x554];
    f32 f554;
    f32 f558;
};

void func_001BAC30(void* self, void* p);
f32 func_00137DF8(void* p);

void func_00146130(void* self, void* p)
{
    Obj_146130* o = (Obj_146130*)self;
    func_001BAC30(self, p);
    o->f554 = func_00137DF8(p);
    o->f558 = func_00137DF8(p);
}

void func_00124A48(void* self);
void func_00146298(void* self);

void func_00146178(void* self)
{
    func_00124A48(self);
    func_00146298(self);
}

struct Obj_146240 {
    u8 pad0[0x14];
    void* p14;
    u8 pad1[0x538];
    f32 f550;
};

void func_00138BE0(void* a, void* self, s32 n);
void func_00146298(void* self);
void func_00129DF8(void* self);

void func_00146240(void* self, f32 v)
{
    Obj_146240* o = (Obj_146240*)self;
    if (v != o->f550) {
        o->f550 = v;
        func_00138BE0(o->p14, o, 7);
        func_00146298(o);
        func_00129DF8(o);
    }
}

struct Probe_00144FF8 {
    u8 pad_00[0x40];
    f32 x_40;
    f32 y_44;
    u8 pad_48[0x2C];
    f32 x_74;
    f32 y_78;
};

struct Pose_00144FF8 {
    u8 pad_00[0x80];
    f32 y_80;
    f32 x_84;
};

f32 func_00205778(f32 a, f32 b);
f32 func_001EA408(f32 a);

void func_00144FF8(Pose_00144FF8* self, Probe_00144FF8* p, s32 mode, f32* out)
{
    f32 t;
    f32 x;
    f32 y;
    switch (mode) {
    case 0:
        y = p->y_44;
        x = p->x_40;
        goto call;
    case 1:
        y = p->y_78;
        x = p->x_74;
        goto call;
    default:
        goto zero;
    }
call:
    t = func_00205778(-x, y);
    goto store;
zero:
    t = 0.0f;
store:
    *out = func_001EA408(t + func_00205778(self->x_84, self->y_80));
}

extern u32 D_002618B0;

void func_001460B8(void* self, s32 code)
{
    if (code == 0xFFFF && self != 0) {
        D_002618B0 = 0x80303030;
    }
}

void func_001460B8(void* self, s32 code);

void func_001460E0(void)
{
    func_001460B8((void*)1, 0xFFFF);
}

struct Obj_00146100 {
    u8 pad_000[0x550];
    f32 value_550;
};

void func_001B7968(void* self);

void func_00146100(Obj_00146100* self)
{
    func_001B7968(self);
    self->value_550 = 100.0f;
}

struct Flags_1455C0 { u8 pad0[0x224]; s32 f224; s32 f228; f32 f22C; };

void func_001455C0(Flags_1455C0* self, f32* src)
{
    self->f224 = 1;
    if (src != 0) {
        self->f228 = 1;
        self->f22C = *src;
    }
}

struct Flags_1455E0 { u8 pad0[0x220]; s32 f220; };

void func_001455E0(Flags_1455E0* self)
{
    self->f220 = 1;
}

void func_001455C0(void* self, s32 zero);

void func_001455F0(void* p)
{
    func_001455C0(p, 0);
}

struct Obj_146018 { u8 pad[0x4B0]; s32 integer; f32 first; f32 second; };
void func_00146018(Obj_146018* obj, s32 value, f32 first, f32 second) { obj->integer = value; obj->first = first; obj->second = second; }

extern f32 D_0026185C;
struct Obj_146028 { u8 pad[0x218]; f32 value; };
void func_00146028(Obj_146028* obj) { obj->value = D_0026185C; }

struct State_00145DD8 { u8 pad[0x538]; s32 value; };
s32 func_00145DD8(void* unused, State_00145DD8* other)
{
    return other->value != 0;
}

void func_001495E8(void* self, s32 value);
void func_00145FB8(u8* self, s32 value)
{
    func_001495E8(self + 0x460, value);
}

s32 func_00149610(void* self);
s32 func_00145FD8(u8* self)
{
    return func_00149610(self + 0x460);
}

s32 func_00149638(void* self);
s32 func_00145FF8(u8* self)
{
    return func_00149638(self + 0x460);
}

void func_00144008(void* self);
void func_001EEBB0(void* a, void* b, void* c);

extern u8 D_00275710[];

struct __attribute__((aligned(16))) Quad_144270 { s32 a, b, c, d; };

struct Ctx_144270 {
    u8 pad0[0x1EC4];
    s32 f1EC4;
};

struct Self_144270 {
    u8 pad0[0x40];
    Quad_144270 f40;
    u8 pad1[0x21C - 0x50];
    s32 f21C;
};

void func_00144270(Self_144270* self)
{
    Quad_144270 in;
    s32 out;
    Ctx_144270* g;

    func_00144008(self);
    g = *(Ctx_144270**)D_00275710;
    if (g != 0) {
        in = self->f40;
        func_001EEBB0((void*)g->f1EC4, &in, &out);
        if (out != 0) {
            self->f21C = out;
        }
    }
}

void func_00127378(void* self, s32 kind, void* msg);
void func_001B6598(void* sub, s32* out);
void func_001DBCC8(void* owner, void* fn, void* ctx, s32 a3, s32 a4);
void func_00147ED0(void* self);

typedef void (*VFn_147EF8)(void* self, void* args);
struct Obj_147EF8 { VFn_147EF8* vtbl; };
struct Mid_147EF8 { u8 pad0[0x1D60]; Obj_147EF8* p1D60; };
struct Self_147EF8 {
    u8 pad0[0x14];
    Mid_147EF8* p14;
    u8 pad1[0x2D0];
    s32 f2E8;
};
struct Args_147EF8 { s32 flag; void* self; };

void func_00147EF8(Self_147EF8* self, s32 kind, void* target)
{
    Args_147EF8 args;
    s32 code;
    u8 pad[0x40];
    func_00127378(self, kind, target);
    if (kind != 0x14) return;
    if ((s32)target != self->f2E8) return;
    func_001B6598(target, &code);
    if (code != 0x263) return;
    Obj_147EF8* obj = self->p14->p1D60;
    if (obj != 0) {
        args.flag = 1;
        args.self = self;
        obj->vtbl[31](obj, &args);
    }
    func_001DBCC8(self->p14, (void*)(void (*)(void*))func_00147ED0, self, 0, 0);
}

void func_00146340(void* self);

struct Self_147E40 {
    u8 pad0[0x320];
    f32 f320;
    u8 pad1[0x20];
    f32 f344;
    f32 f348;
    f32 f34C;
    f32 f350;
    f32 f354;
    f32 f358;
    u8 pad2[0x34];
    f32 f390;
    f32 f394;
};

void func_00147E40(Self_147E40* self)
{
    func_00146340(self);
    f32 k = 50.0f;
    self->f34C = 45.0f;
    self->f344 = 250.0f;
    self->f348 = self->f350 = k;
    self->f358 = 0.6f;
    self->f354 = 0.75f;
    self->f320 = 0.25f;
    self->f390 = 8.0f;
    self->f394 = 10.0f;
}

struct Obj_146D10 {
    u8 pad0[0x50];
    void* list;
    u8 pad1[0x538 - 0x54];
    u64 flags;
};

s32 func_001300E8(void* node, s32 kind);

s32 func_00146D10(void* unused, Obj_146D10* self)
{
    u64 bit = 0x8000;
    bit <<= 28;
    if (self->flags & bit) {
        return 0;
    }
    if (func_001300E8(self->list, 5) != 0 || func_001300E8(self->list, 0x27) != 0 ||
        func_001300E8(self->list, 0x3B) != 0 || func_001300E8(self->list, 0x40) != 0 ||
        func_001300E8(self->list, 0x2E) != 0) {
        return 0;
    }
    return 1;
}

extern u8 D_002622A8[];

void func_00152B38(void* f);
void func_001EE3B8(void* s, s32 a, s32 b);
void func_001EE668(void* s, s32 a, s32 b, void* c, s32 d);
void func_00152D70(void* self);

void func_00144848(u8* self)
{
    func_00152B38(D_002622A8);
    func_001EE3B8(D_002622A8, 0, 0);
    func_001EE668(D_002622A8, 0xC, 4, self + 0x100, 4);
    func_001EE668(D_002622A8, 0xC, 4, self + 0x140, 8);
    func_00152D70(D_002622A8);
}

struct __attribute__((aligned(16))) Quad_1448C8 {
    s32 w[4];
};

struct Obj_1448C8 {
    u8 pad0[0x40];
    Quad_1448C8 q40;
    u8 pad1[0x30];
    Quad_1448C8 q80;
    Quad_1448C8 q90;
    Quad_1448C8 qA0;
    u8 pad2[0x200];
    f32 f2B0;
    f32 f2B4;
    f32 f2B8;
    f32 f2BC;
    f32 f2C0;
};

void func_00144540(Obj_1448C8* self);

void func_001448C8(Obj_1448C8* self, Quad_1448C8* a, Quad_1448C8* b)
{
    if (a != 0) {
        self->q40 = *a;
    }
    if (b != 0) {
        self->q80 = b[0];
        self->q90 = b[1];
        self->qA0 = b[2];
    }
    func_00144540(self);
    f32 zero = 0.0f;
    self->f2C0 = zero;
    self->f2BC = zero;
    self->f2B4 = zero;
    self->f2B0 = zero;
    self->f2B8 = zero;
}

// NEAR: only a0/a1 saved regs swapped (s0/s1) and the four loads use the other base; stores/frame match

struct __attribute__((aligned(16))) Quad_1442C8 { s32 w[4]; };
struct Mat_1442C8 { f32 m[16]; };

void func_001885E0(void* self);
void func_00189AF0(void* a0, void* a1);
void func_00188668(void* out, void* b, void* in);

void func_001442C8(f32* b, f32* a, void* c, Quad_1442C8* out)
{
    Mat_1442C8 m;
    Mat_1442C8 v;
    Quad_1442C8 r[4];
    f32* d0;
    f32* d1;
    f32* d2;
    f32* d3;
    func_001885E0(&m);
    f32* pb = b;
    f32* pa = a;
    d3 = m.m + 12;
    d2 = m.m + 8;
    d1 = m.m + 4;
    d0 = m.m;
    s32 n = 2;
    do {
        n--;
        f32 w = *pb;
        f32 x = -pa[4];
        f32 y = -pa[8];
        f32 z = pa[0];
        *d0++ = x;
        *d1++ = y;
        *d2++ = z;
        *d3++ = w;
        pb++;
        pa++;
    } while (n >= 0);
    func_00189AF0(&m, &v);
    func_00188668(r, c, &v);
    out[0] = r[0];
    out[1] = r[1];
    out[2] = r[2];
    out[3] = r[3];
}

struct Ctx_144938;

void func_00144BE8(Ctx_144938* a, s32 b, void* c, s32 d, s32 e, f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5);

void func_00144938(Ctx_144938* self, void* p, s32 q)
{
    func_00144BE8(self, 0, p, q, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

struct __attribute__((aligned(16))) Vec_144B70 {
    s32 w[4];
};

struct Eng_144B70 {
    u8 pad0[0x40];
    Vec_144B70 f40;
    u8 pad50[0x2B0 - 0x50];
    f32 f2B0;
    f32 f2B4;
    f32 f2B8;
    u8 pad2BC[0x2D0 - 0x2BC];
    Vec_144B70 f2D0;
};

void func_00144AA0(Vec_144B70* a, Vec_144B70* b, Vec_144B70* out, f32 x, f32 y, f32 z);
void func_00144978(Vec_144B70* a, Vec_144B70* b, Vec_144B70* out, f32* x, f32* y, f32* z);

void func_00144B70(Eng_144B70* self, Vec_144B70* arg)
{
    Vec_144B70 tmp;
    func_00144AA0(&self->f2D0, &self->f40, &tmp, self->f2B0, self->f2B4, self->f2B8);
    func_00144978(arg, &self->f40, &tmp, &self->f2B0, &self->f2B4, &self->f2B8);
    self->f2D0 = *arg;
}

struct Elem_146298 { u8 pad0[8]; s32 tag; u8 pad1[0x20]; f32 x; f32 y; };
struct Obj_146298 { u8 pad0[0x27C]; s32 count; Elem_146298** list; u8 pad1[0x550 - 0x284]; f32 f550; f32 f554; f32 f558; };

void func_00146298(Obj_146298* self)
{
    for (s32 i = 0; i < self->count; i++) {
        if (self->list[i]->tag == 6) {
            Elem_146298* e = self->list[i];
            e->x = -(self->f550 * self->f554);
            e->y = -(self->f550 * self->f558);
            break;
        }
    }
}
