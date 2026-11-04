// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "c6d.h"
#include "asm_func.h"
extern void func_001439A8(void*);
extern void func_001439C8(void*);
extern void func_001439E8(void*);
extern void func_00143A08(void*);
extern void func_001448C8(void*, s32, void*);
#include "list_iter.h"


void func_00143968(void* arg);



void func_00143A38(void* arg);



// Built at startup: the compiler's initialiser and constructor for this file are func_001460B8
// and func_001460E0 (config/us/generated.tsv).
struct Rgba_1639E8
{
    union {
        struct { u8 r, g, b, a; };
        u32 rgba;
    };
    Rgba_1639E8(u32 v) { rgba = v; }
};

struct Obj_1439A8 {
    u8 pad[0x1F8];
    f32 value;
};
void func_00143560(void* self);



struct Obj_143AF0 {
    u8 pad[0x340];
    s32 field;
};





struct Target_00143148 {
    u8 pad0[0x30];
    f32 f30;
    f32 f34;
};

void func_001ED650(void* self, f32 x, f32 y, f32 z);



struct Scaler_001434C8 {
    u8 pad0[0x1F8];
    f32 f1F8;
    f32 f1FC;
    f32 f200;
};

void func_00183FE0(f32* a, f32* b, f32 x, f32 y, f32 z, f32 w);




void func_00143940(void* self);




void func_00143988(void* self);



struct Obj_143A38 {
    u8 pad0[0x1C0];
    f32 f1C0;
};




struct Ctl_143A60 {
    u8 pad0[0x218];
    f32 f218;
    s32 f21C;
    u8 pad1[0x3D0 - 0x220];
    s32 f3D0;
    u8 pad2[0x454 - 0x3D4];
    T2173 ctl454;
};

void func_00144938(void* self, void* a, void* b);
void func_001493B8(T2173* p, s32 zero);
void func_00145088(void* self, s32 a1, void* a2, s32 a3, s32 a4);
void func_001455C0(void* self, s32 zero);



struct ItemList_143AF8 {
    u8 pad0[0x340];
    s32 count;
    void* items[8];
};



struct IdList_143B20 { u8 pad[0x340]; s32 count; s32 items[1]; };

void func_0018D800(void* dst, void* src, u32 size);



struct Entry_143BA8 { u8 pad0[0x404]; s32 flag404; u8 pad1[0x538 - 0x408]; u64 bits538; };



typedef int s32;
typedef unsigned char u8;
typedef float f32;

struct Ctl_143940 {
    u8 pad0[0x1C4];
    f32 f1C4;
    f32 f1C8;
    s32 i1CC;
};

void func_00143560(void* self);



typedef int s32;
typedef unsigned char u8;
typedef float f32;

struct Ctl_143968 {
    u8 pad0[0x1E4];
    f32 f1E4;
};

void func_00143560(void* self);



struct Obj_143988 {
    u8 pad[0x1E8];
    f32 f1E8;
};
void func_00143560(void* self);



struct Obj_1439C8 {
    u8 pad[0x1FC];
    f32 f1FC;
};
void func_00143560(void* self);













void func_001448C8(void* self, void* a, void* b);


struct State_001439E8 { u8 pad[0x200]; f32 value; };


struct __attribute__((packed)) Value_00143A08 { u32 value; };


// EXACT: float constants and .data floats as locals, 1.0f stores in source order 1C0,1C4,1C8

struct __attribute__((packed)) Pk16_00143648 {
    u64 a;
    u64 b;
};

struct __attribute__((packed)) Pk4_00143648 {
    s32 a;
};

struct __attribute__((aligned(16))) Quad_00143648 {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
};

void func_00182C18(C01* self);
void func_00143560(C6D* self);
void func_00149398(T2173* self, C6D* owner);
void func_00149660(T2173_3B0* self, C6D* owner);
void func_0014A888(T2173_3C8* self, C6D* owner);
void func_00143A60(C6D* self, s32 a1);

extern u8 D_002483D0[];
// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_00217398[];
extern const Fn_Table D_002173B0[];
extern const Fn_Table D_002173C8[];
extern const Fn_Table D_002173E0[];
extern const Fn_Table D_002173F8[];



extern s32 D_00262C68;
extern u8 D_00262C70[];
extern u8 D_00262D38[];

struct Ctl_143E40;

f32 func_001EA620(f32 a, f32 b, f32 c, f32 d, void* p, void* q);
void func_001433E0(Ctl_143E40* c, void* n, void* x);
void func_00143208(Ctl_143E40* c, void* n, f32 dt, void* x);
void func_00143940(Ctl_143E40* c, f32 v);
void func_00143560(Ctl_143E40* c);

struct Ctl_143E40 {
    u8 pad0[0x1C4];
    f32 f1C4;
    f32 f1C8;
    f32 f1CC;
    f32 f1D0;
    u8 pad1D4[0x220 - 0x1D4];
    s32 i220;
    s32 i224;
    s32 i228;
    u8 pad22C[0x2E0 - 0x22C];
    void* p2E0;
    u8 pad2E4[0x2F0 - 0x2E4];
    u8 b2F0[0xE0];
    s32 i3D0;
    T2173Entry top;
};

typedef void (*VFn_143E40)(void* self, f32 dt, void* a);



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









struct Flags_1455C0 { u8 pad0[0x224]; s32 f224; s32 f228; f32 f22C; };



struct Flags_1455E0 { u8 pad0[0x220]; s32 f220; };



void func_001455C0(void* self, s32 zero);



struct Obj_146018 { u8 pad[0x4B0]; s32 integer; f32 first; f32 second; };


extern f32 D_0026185C;
struct Obj_146028 { u8 pad[0x218]; f32 value; };


struct State_00145DD8 { u8 pad[0x538]; s32 value; };


void func_001495E8(T2173_3B0* self, s32 value);


s32 func_00149610(T2173_3B0* self);


s32 func_00149638(T2173_3B0* self);


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



extern u8 D_002622A8[];

void func_00152B38(void* f);
void func_001EE3B8(void* s, s32 a, s32 b);
void func_001EE668(void* s, s32 a, s32 b, void* c, s32 d);
void func_00152D70(void* self);



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



// NEAR: only a0/a1 saved regs swapped (s0/s1) and the four loads use the other base; stores/frame match

struct __attribute__((aligned(16))) Quad_1442C8 { s32 w[4]; };
struct Mat_1442C8 { f32 m[16]; };

void func_001885E0(void* self);
void func_00189AF0(void* a0, void* a1);
void func_00188668(void* out, void* b, void* in);



struct Ctx_144938;

void func_00144BE8(Ctx_144938* a, s32 b, void* c, s32 d, s32 e, f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5);



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



struct Shape_145810;
struct Obj_145810 { u8 pad0[0x538]; Shape_145810* p538; };
struct Rec_145810 { u8 pad0[0x40]; f32 f40; f32 f44; u8 pad1[0x28]; };

s32 func_0013DFD8(Shape_145810* a0, void* a1, void* a2, s32 a3, s32 a4, void* a5);
s32 func_001429F8(s32 n, void* recs);



struct Self_1451F0 {
    u8 pad0[0x364];
    f32 f364;
    u8 pad368[0x3D0 - 0x368];
    s32 f3D0;
    T2173Entry f3D4[1];
};

extern f32 D_0026185C;

void func_00143140(void);
void func_00143148(void* a0, void* a1, Target_00143148* a2, void* a3);
void func_001434C8(Scaler_001434C8* self, f32* out, f32 p);
void func_001437C0(void);
void func_001437E8(void);
void func_00143810(void);
void func_00143838(void);
void func_00143860(void);
void func_00143888(void);
void func_001438B0(void);
void func_001438D8(void);
void func_00143900(void* self, void* value);
void func_00143920(void* arg, void* arg2);
void func_00143940(void* self, f32 x);
void func_00143968(void* self, f32 x);
void func_00143988(Obj_143988* self, f32 value);
void func_001439A8(Obj_1439A8* self, f32 value);
void func_001439C8(Obj_1439C8* self, f32 value);
void func_001439E8(void* ptr, f32 value);
void func_00143A08(void* self, void* value);
void func_00143A38(Obj_143A38* self, f32 value);
void func_00143A60(Ctl_143A60* self, s32 flag);
void func_00143AF0(Obj_143AF0* obj);
void func_00143AF8(ItemList_143AF8* list, void* item);
void func_00143B20(IdList_143B20* list, s32 value);
s32 func_00143BA8(void* unused, Entry_143BA8* e);
void func_00143E40(Ctl_143E40* self, s32 flag, f32 dt);
void func_00144270(Self_144270* self);
void func_001442C8(f32* b, f32* a, void* c, Quad_1442C8* out);
void func_00144848(u8* self);
void func_001448C8(Obj_1448C8* self, Quad_1448C8* a, Quad_1448C8* b);
void func_00144938(Ctx_144938* self, void* p, s32 q);
void func_00144B70(Eng_144B70* self, Vec_144B70* arg);
void func_00144FF8(Pose_00144FF8* self, Probe_00144FF8* p, s32 mode, f32* out);
void func_001451F0(Self_1451F0* self, s32 flags, s32 k0, T2173* k1, s32 k2, s32 k3);
void func_001455C0(Flags_1455C0* self, f32* src);
void func_001455E0(Flags_1455E0* self);
void func_001455F0(void* p);
s32 func_00145810(s32 count, Obj_145810** objs, f32 thresh, void* a2, void* a3, f32* lo, f32* hi);
s32 func_00145DD8(void* unused, State_00145DD8* other);
void func_00145FB8(C6D* self, s32 value);
s32 func_00145FD8(C6D* self);
s32 func_00145FF8(C6D* self);
void func_00146018(Obj_146018* obj, s32 value, f32 first, f32 second);
void func_00146028(Obj_146028* obj);

// The file's .data, in retail's order; the labels only its assembly reads are included.
f32 D_00261880[4] = { 0.0f, -2000.0f, 500.0f, 0.0f };
f32 D_00261890[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 D_002618A0 = 5e+02f;
f32 D_002618A4 = 2e+04f;
f32 D_002618A8 = 0.5f;
Rgba_1639E8 D_002618B0(0x80303030);
f32 D_002618B8[4] = { 0.5f, 0.0f, 0.1f, 10.0f };
INCLUDE_DATA(D_002618C8);
INCLUDE_DATA(D_002618CC);
INCLUDE_DATA(D_002618D0);
INCLUDE_DATA(D_002618E0);
INCLUDE_DATA(D_002618F0);
INCLUDE_DATA(D_00261900);
INCLUDE_DATA(D_00261910);
INCLUDE_DATA(D_00261920);
INCLUDE_DATA(D_00261924);
INCLUDE_DATA(D_00261928);
INCLUDE_DATA(D_0026194C);
INCLUDE_DATA(D_00261950);
INCLUDE_DATA(D_00261958);
INCLUDE_DATA(D_00261970);
INCLUDE_DATA(D_00261980);
void* D_00261990 = 0;

void func_00143140(void)
{
}

void func_00143148(void* a0, void* a1, Target_00143148* a2, void* a3)
{
    func_001ED650(a3, a2->f30 + 3.1415927f, a2->f34, 0.0f);
}

ASM_FUNC(func_00143180);

ASM_FUNC(func_00143208);

ASM_FUNC(func_001433E0);

ASM_FUNC(func_00143418);

void func_001434C8(Scaler_001434C8* self, f32* out, f32 p)
{
    f32 one = 1.0f;
    f32 scale = 4080.0f;
    f32 a = self->f200 * p;
    f32 b = self->f1FC;
    f32 c = self->f1F8;
    func_00183FE0(out, out + 1, one, scale, b / c, (one - a) * scale);
    out[0] = out[0] + 8388608.0f;
    out[2] = self->f1F8;
    out[3] = out[0] + 36864.0f;
}

ASM_FUNC(func_00143560);

void func_00143648(C6D* self)
{
    u8* s = (u8*)self;

    func_00182C18(self);
    f32 one = 1.0f;
    *(f32*)(s + 0x1C0) = one;
    *(f32*)(s + 0x1C4) = one;
    *(f32*)(s + 0x1C8) = one;
    *(struct Pk16_00143648*)(s + 0x1D0) = *(struct Pk16_00143648*)D_002618B8;
    f32 k = 1.29870129f;
    f32 x = D_002618A0;
    f32 y = D_002618A4;
    f32 z = D_002618A8;
    f32 h = 100.0f;
    f32 t = 20000.0f;
    *(f32*)(s + 0x1E0) = k;
    *(f32*)(s + 0x1E4) = h;
    *(f32*)(s + 0x1E8) = t;
    *(f32*)(s + 0x1F8) = x;
    *(f32*)(s + 0x1FC) = y;
    *(f32*)(s + 0x200) = z;
    *(struct Pk4_00143648*)(s + 0x204) = *(struct Pk4_00143648*)&D_002618B0;
    *(struct Quad_00143648*)(s + 0x80) = *(struct Quad_00143648*)D_002483D0;
    *(struct Quad_00143648*)(s + 0x90) = *(struct Quad_00143648*)(D_002483D0 + 0x10);
    *(struct Quad_00143648*)(s + 0xA0) = *(struct Quad_00143648*)(D_002483D0 + 0x20);
    func_00143560(self);
    self->ctl454.vt = (const Vt2173*)D_00217398;
    func_00149398(&self->ctl454, self);
    self->ctl460.vt = (const Vt2173*)D_002173B0;
    func_00149660(&self->ctl460, self);
    self->ctl4C0.vt = (const Vt2173*)D_002173C8;
    func_0014A888(&self->ctl4C0, self);
    self->ctl510.vt = (const Vt2173*)D_002173E0;
    func_00149398(&self->ctl510, self);
    self->ctl520.vt = (const Vt2173*)D_002173F8;
    func_00149398(&self->ctl520, self);
    func_00143A60(self, 1);
}

void func_001437C0(void)
{
    func_00143940(D_00261990);
}

void func_001437E8(void)
{
    func_00143968(D_00261990);
}

void func_00143810(void)
{
    func_00143988(D_00261990);
}

void func_00143838(void) { func_001439A8(D_00261990); }

void func_00143860(void) { func_001439C8(D_00261990); }

void func_00143888(void) { func_001439E8(D_00261990); }

void func_001438B0(void) { func_00143A08(D_00261990); }

void func_001438D8(void)
{
    func_00143A38(D_00261990);
}

void func_00143900(void* self, void* value)
{
    func_001448C8(self, value, 0);
}

void func_00143920(void* arg, void* arg2) { func_001448C8(arg, 0, arg2); }

void func_00143940(void* self, f32 x)
{
    Ctl_143940* c = (Ctl_143940*)self;
    c->f1C4 = x;
    c->f1C8 = x;
    c->i1CC = 0;
    func_00143560(self);
}

void func_00143968(void* self, f32 x)
{
    Ctl_143968* c = (Ctl_143968*)self;
    c->f1E4 = x;
    func_00143560(self);
}

void func_00143988(Obj_143988* self, f32 value)
{
    self->f1E8 = value;
    func_00143560(self);
}

void func_001439A8(Obj_1439A8* self, f32 value)
{
    self->value = value;
    func_00143560(self);
}

void func_001439C8(Obj_1439C8* self, f32 value)
{
    self->f1FC = value;
    func_00143560(self);
}

void func_001439E8(void* ptr, f32 value)
{
    State_001439E8* self = (State_001439E8*)ptr;
    self->value = value;
    func_00143560(self);
}

void func_00143A08(void* self, void* value)
{
    *(Value_00143A08*)((u8*)self + 0x204) = *(Value_00143A08*)value;
    func_00143560(self);
}

void func_00143A38(Obj_143A38* self, f32 value)
{
    self->f1C0 = value;
    func_00143560(D_00261990);
}

void func_00143A60(Ctl_143A60* self, s32 flag)
{
    if (flag != 0) {
        func_00144938(self, D_00261880, D_00261890);
    }
    self->f3D0 = 0;
    func_001493B8(&self->ctl454, 0);
    func_00145088(self, 0, &self->ctl454, 0, 0);
    func_001455C0(self, 0);
    self->f21C = 0x0FFFFFFF;
    self->f218 = -10.0f;
}

void func_00143AF0(Obj_143AF0* obj)
{
    obj->field = 0;
}

void func_00143AF8(ItemList_143AF8* list, void* item)
{
    u32 n = list->count;
    if (n < 8) {
        list->items[n] = item;
        list->count = n + 1;
    }
}

void func_00143B20(IdList_143B20* list, s32 value)
{
    for (s32 i = 0; i < list->count; i++) {
        if (value == list->items[i]) {
            func_0018D800(&list->items[i], &list->items[i + 1], (list->count - i - 1) * 4);
            list->count--;
            return;
        }
    }
}

s32 func_00143BA8(void* unused, Entry_143BA8* e)
{
    s64 field = 0xF000;
    s64 want = 0x8000;
    s32 r = 0;
    field <<= 20;
    want <<= 17;
    if ((e->bits538 & field) == want) {
        goto set;
    }
    if (e->flag404 == 0) {
        goto done;
    }
set:
    r = 1;
done:
    return r;
}

ASM_FUNC(func_00143BE0);

void func_00143E40(Ctl_143E40* self, s32 flag, f32 dt)
{
    if (self->i220 != 0) {
        self->i220 = 0;
        self->i224 = 1;
        self->i228 = 0;
    }
    if (self->i3D0 > 0) {
        T2173* n = self->top.ctl;
        T2173* prev = 0;
        void* last = 0;
        if (n != 0) {
            do {
                void* o = self->top.target;
                u8* x;
                if (o != 0) {
                    x = self->b2F0;
                    if (o != last) {
                        ((VFn_143E40)(*(void***)o)[0x124 / 4])(o, dt, x);
                        if (prev != 0 || o != self->p2E0) {
                            func_001433E0(self, o, x);
                        }
                        func_00143208(self, o, dt, x);
                        self->p2E0 = o;
                        last = o;
                    }
                } else {
                    x = 0;
                }
                const Vt2173* vt = n->vt;
                if (vt->m04 != 0) {
                    u8* t = (D_00262C68 & 1) ? D_00262C70 : D_00262D38;
                    vt->m04(n, x, t, dt);
                }
                prev = n;
                if (self->i3D0 <= 0) break;
                n = self->top.ctl;
            } while (n != prev);
        }
    }
    if (self->i224 != 0) {
        func_00143940(self, self->f1C8);
    } else if (self->f1C4 != self->f1C8) {
        self->f1C4 = func_001EA620(self->f1C4, self->f1CC, self->f1C8, dt, &self->f1D0, &self->f1CC);
        func_00143560(self);
    }
    if (flag != 0) {
        self->i228 = 0;
        self->i224 = 0;
    }
}

ASM_FUNC(func_00144008);

ASM_FUNC(func_00144128);

ASM_FUNC(func_001441C0);

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

ASM_FUNC(func_001443C8);

ASM_FUNC(func_00144540);

void func_00144848(u8* self)
{
    func_00152B38(D_002622A8);
    func_001EE3B8(D_002622A8, 0, 0);
    func_001EE668(D_002622A8, 0xC, 4, self + 0x100, 4);
    func_001EE668(D_002622A8, 0xC, 4, self + 0x140, 8);
    func_00152D70(D_002622A8);
}

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

void func_00144938(Ctx_144938* self, void* p, s32 q)
{
    func_00144BE8(self, 0, p, q, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

ASM_FUNC(func_00144978);

ASM_FUNC(func_00144AA0);

void func_00144B70(Eng_144B70* self, Vec_144B70* arg)
{
    Vec_144B70 tmp;
    func_00144AA0(&self->f2D0, &self->f40, &tmp, self->f2B0, self->f2B4, self->f2B8);
    func_00144978(arg, &self->f40, &tmp, &self->f2B0, &self->f2B4, &self->f2B8);
    self->f2D0 = *arg;
}

ASM_FUNC(func_00144BE8);

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

LINKER_REMNANT(func_00145080);

INCLUDE_ASM(func_00145088);

void func_001451F0(Self_1451F0* self, s32 flags, s32 k0, T2173* k1, s32 k2, s32 k3)
{
    s32 s5 = 0;
    T2173* s4 = 0;
    s32 i = 0;
    T2173Entry* w = self->f3D4;
    T2173Entry* r = w;
    for (; i < self->f3D0; i++, r++) {
        if ((!(flags & 1) || k0 == r->key) && (!(flags & 2) || k1 == r->ctl) &&
            (!(flags & 4) || k2 == (s32)r->target) && (!(flags & 8) || k3 == r->arg)) {
            if (i == 0) {
                s5 = r->arg;
                s4 = r->ctl;
            }
            T2173* o = r->ctl;
            Fn2173 fn = o->vt->m03;
            if (fn != 0) {
                fn(o, r->arg);
            }
        } else {
            *w = *r;
            w++;
        }
    }
    self->f3D0 = w - self->f3D4;
    if (s4 != 0) {
        Fn2173 fn = s4->vt->m01;
        if (fn != 0) {
            fn(s4, s5);
        }
        if (self->f3D0 > 0) {
            self->f364 = D_0026185C;
            T2173* o = self->f3D4[0].ctl;
            Fn2173 fn2 = o->vt->m00;
            if (fn2 != 0) {
                fn2(o, self->f3D4[0].arg);
            }
        }
    }
}

ASM_FUNC(func_001453B0);

ASM_FUNC(func_00145438);

ASM_FUNC(func_001454E0);

void func_001455C0(Flags_1455C0* self, f32* src)
{
    self->f224 = 1;
    if (src != 0) {
        self->f228 = 1;
        self->f22C = *src;
    }
}

void func_001455E0(Flags_1455E0* self)
{
    self->f220 = 1;
}

void func_001455F0(void* p)
{
    func_001455C0(p, 0);
}

ASM_FUNC(func_00145610);

ASM_FUNC(func_00145718);

s32 func_00145810(s32 count, Obj_145810** objs, f32 thresh, void* a2, void* a3, f32* lo, f32* hi)
{
    Rec_145810 recs[64];
    s32 total = 0;
    s32 i;
    s32 k;
    s32 j;
    f32 f2;
    f32 f1;
    for (i = 0; i < count; i++) {
        total += func_0013DFD8(objs[i]->p538, a2, a3, 0, 0x40 - total, &recs[total]);
    }
    total = func_001429F8(total, recs);
    j = 0;
    for (k = 0;; k++) {
        if (total < k) return 0;
        f2 = 0.0f;
        if (k > 0) f2 = recs[j - 1].f44;
        if (k < total) f1 = recs[j].f40;
        else f1 = 1.0f;
        j++;
        if (thresh < f1 - f2) break;
    }
    if (lo != 0) *lo = f2;
    if (hi != 0) *hi = f1;
    return 1;
}

ASM_FUNC(func_00145950);

ASM_FUNC(func_00145B68);

s32 func_00145DD8(void* unused, State_00145DD8* other)
{
    return other->value != 0;
}

ASM_FUNC(func_00145DE8);

ASM_FUNC(func_00145E68);

void func_00145FB8(C6D* self, s32 value)
{
    func_001495E8(&self->ctl460, value);
}

s32 func_00145FD8(C6D* self)
{
    return func_00149610(&self->ctl460);
}

s32 func_00145FF8(C6D* self)
{
    return func_00149638(&self->ctl460);
}

void func_00146018(Obj_146018* obj, s32 value, f32 first, f32 second) { obj->integer = value; obj->first = first; obj->second = second; }

void func_00146028(Obj_146028* obj) { obj->value = D_0026185C; }

ASM_FUNC(func_00146038);


