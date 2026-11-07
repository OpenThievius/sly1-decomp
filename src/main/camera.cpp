// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "camera.h"
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

void func_00143560(void* self);








struct Target_00143148 {
    u8 pad0[0x30];
    f32 f30;
    f32 f34;
};

void func_001ED650(void* self, f32 x, f32 y, f32 z);



void func_00183FE0(f32* a, f32* b, f32 x, f32 y, f32 z, f32 w);




void func_00143940(void* self);




void func_00143988(void* self);








void func_00144938(void* self, void* a, void* b);
void func_001493B8(T2173* p, s32 zero);
void func_00145088(void* self, s32 a1, void* a2, s32 a3, s32 a4);







void func_0018D800(void* dst, void* src, u32 size);



struct Entry_143BA8 { u8 pad0[0x404]; s32 flag404; u8 pad1[0x538 - 0x408]; u64 bits538; };



typedef int s32;
typedef unsigned char u8;
typedef float f32;


void func_00143560(void* self);



typedef int s32;
typedef unsigned char u8;
typedef float f32;


void func_00143560(void* self);



void func_00143560(void* self);



void func_00143560(void* self);













void func_001448C8(void* self, void* a, void* b);




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

void func_00182C18(BaseObject* self);
void func_00143560(Camera* self);
void func_00149398(T2173* self, Camera* owner);
void func_00149660(T2173_3B0* self, Camera* owner);
void func_0014A888(T2173_3C8* self, Camera* owner);
void func_00143A60(Camera* self, s32 a1);

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

f32 func_001EA620(f32 a, f32 b, f32 c, f32 d, void* p, void* q);
void func_001433E0(Camera* c, void* n, void* x);
void func_00143208(Camera* c, void* n, f32 dt, void* x);
void func_00143940(Camera* c, f32 v);
void func_00143560(Camera* c);


typedef void (*VFn_143E40)(void* self, f32 dt, void* a);



struct Probe_00144FF8 {
    u8 pad_00[0x40];
    f32 x_40;
    f32 y_44;
    u8 pad_48[0x2C];
    f32 x_74;
    f32 y_78;
};


f32 func_00205778(f32 a, f32 b);
f32 func_001EA408(f32 a);




















extern f32 D_0026185C;


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




extern u8 D_002622A8[];

void func_00152B38(void* f);
void func_001EE3B8(void* s, s32 a, s32 b);
void func_001EE668(void* s, s32 a, s32 b, void* c, s32 d);
void func_00152D70(void* self);



struct __attribute__((aligned(16))) Quad_1448C8 {
    s32 w[4];
};


void func_00144540(Camera* self);



// NEAR: only a0/a1 saved regs swapped (s0/s1) and the four loads use the other base; stores/frame match

struct __attribute__((aligned(16))) Quad_1442C8 { s32 w[4]; };
struct Mat_1442C8 { f32 m[16]; };

void func_001885E0(void* self);
void* func_00189AF0(void* a0, void* a1);
void func_00188668(void* out, void* b, void* in);




void func_00144BE8(Camera* a, s32 b, void* c, s32 d, s32 e, f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5);



struct __attribute__((aligned(16))) Vec_144B70 {
    s32 w[4];
};


void func_00144AA0(Vec_144B70* a, Vec_144B70* b, Vec_144B70* out, f32 x, f32 y, f32 z);
void func_00144978(Vec_144B70* a, Vec_144B70* b, Vec_144B70* out, f32* x, f32* y, f32* z);



struct Shape_145810;
struct Obj_145810 { u8 pad0[0x538]; Shape_145810* p538; };
struct Rec_145810 { u8 pad0[0x40]; f32 f40; f32 f44; u8 pad1[0x28]; };

s32 func_0013DFD8(Shape_145810* a0, void* a1, void* a2, s32 a3, s32 a4, void* a5);
s32 func_001429F8(s32 n, void* recs);




extern f32 D_0026185C;

void func_00143140(void);
void func_00143148(void* a0, void* a1, Target_00143148* a2, void* a3);
void func_001434C8(Camera* self, f32* out, f32 p);
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
void func_00143988(Camera* self, f32 value);
void func_001439A8(Camera* self, f32 value);
void func_001439C8(Camera* self, f32 value);
void func_001439E8(void* ptr, f32 value);
void func_00143A08(void* self, void* value);
void func_00143A38(Camera* self, f32 value);
void func_00143A60(Camera* self, s32 flag);
void func_00143AF0(Camera* obj);
void func_00143AF8(Camera* list, void* item);
void func_00143B20(Camera* list, s32 value);
s32 func_00143BA8(void* unused, Entry_143BA8* e);
void func_00143E40(Camera* self, s32 flag, f32 dt);
void func_00144270(Camera* self);
void func_001442C8(f32* b, f32* a, void* c, Quad_1442C8* out);
void func_00144848(u8* self);
void func_001448C8(Camera* self, Quad_1448C8* a, Quad_1448C8* b);
void func_00144938(Camera* self, void* p, s32 q);
void func_00144B70(Camera* self, Vec_144B70* arg);
void func_00144FF8(Camera* self, Probe_00144FF8* p, s32 mode, f32* out);
void func_001451F0(Camera* self, s32 flags, s32 k0, T2173* k1, s32 k2, s32 k3);
void func_001455C0(Camera* self, f32* src);
void func_001455E0(Camera* self);
void func_001455F0(void* p);
s32 func_00145810(s32 count, Obj_145810** objs, f32 thresh, void* a2, void* a3, f32* lo, f32* hi);
s32 func_00145DD8(void* unused, State_00145DD8* other);
void func_00145FB8(Camera* self, s32 value);
s32 func_00145FD8(Camera* self);
s32 func_00145FF8(Camera* self);
void func_00146018(Camera* obj, s32 value, f32 first, f32 second);
void func_00146028(Camera* obj);

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
    ComputePolarOffset(a3, a2->f30 + 3.1415927f, a2->f34, 0.0f);
}

ASM_FUNC(func_00143180);

ASM_FUNC(func_00143208);

ASM_FUNC(func_001433E0);

ASM_FUNC(func_00143418);

void func_001434C8(Camera* self, f32* out, f32 p)
{
    f32 one = 1.0f;
    f32 scale = 4080.0f;
    f32 a = self->f200 * p;
    f32 b = self->f1FC;
    f32 c = self->f1F8;
    FitReciprocalThroughPoints(out, out + 1, one, scale, b / c, (one - a) * scale);
    out[0] = out[0] + 8388608.0f;
    out[2] = self->f1F8;
    out[3] = out[0] + 36864.0f;
}

ASM_FUNC(func_00143560);

void func_00143648(Camera* self)
{
    u8* s = (u8*)self;

    InitObject(self);
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
    *(struct Quad_00143648*)(s + 0x80) = *(struct Quad_00143648*)g_identityMatrix;
    *(struct Quad_00143648*)(s + 0x90) = *(struct Quad_00143648*)(g_identityMatrix + 0x10);
    *(struct Quad_00143648*)(s + 0xA0) = *(struct Quad_00143648*)(g_identityMatrix + 0x20);
    UpdateCameraProjection(self);
    self->ctl454.vt = (const Vt2173*)D_00217398;
    SetCameraControllerOwner(&self->ctl454, self);
    self->ctl460.vt = (const Vt2173*)D_002173B0;
    func_00149660(&self->ctl460, self);
    self->ctl4C0.vt = (const Vt2173*)D_002173C8;
    func_0014A888(&self->ctl4C0, self);
    self->ctl510.vt = (const Vt2173*)D_002173E0;
    SetCameraControllerOwner(&self->ctl510, self);
    self->ctl520.vt = (const Vt2173*)D_002173F8;
    SetCameraControllerOwner(&self->ctl520, self);
    ResetCamera(self, 1);
}

void func_001437C0(void)
{
    SnapCameraZoom(g_camera);
}

void func_001437E8(void)
{
    SetCameraNearDistance(g_camera);
}

void func_00143810(void)
{
    SetCameraFarDistance(g_camera);
}

void func_00143838(void) { func_001439A8(g_camera); }

void func_00143860(void) { func_001439C8(g_camera); }

void func_00143888(void) { func_001439E8(g_camera); }

void func_001438B0(void) { func_00143A08(g_camera); }

void func_001438D8(void)
{
    func_00143A38(g_camera);
}

void func_00143900(void* self, void* value)
{
    SetCameraPlacement(self, value, 0);
}

void func_00143920(void* arg, void* arg2) { SetCameraPlacement(arg, 0, arg2); }

void func_00143940(void* self, f32 x)
{
    Camera* c = (Camera*)self;
    c->f1C4 = x;
    c->f1C8 = x;
    c->i1CC = 0;
    UpdateCameraProjection(self);
}

void func_00143968(void* self, f32 x)
{
    Camera* c = (Camera*)self;
    c->f1E4 = x;
    UpdateCameraProjection(self);
}

void func_00143988(Camera* self, f32 value)
{
    self->f1E8 = value;
    UpdateCameraProjection(self);
}

void func_001439A8(Camera* self, f32 value)
{
    self->f1F8 = value;
    UpdateCameraProjection(self);
}

void func_001439C8(Camera* self, f32 value)
{
    self->f1FC = value;
    UpdateCameraProjection(self);
}

void func_001439E8(void* ptr, f32 value)
{
    Camera* self = (Camera*)ptr;
    self->f200 = value;
    UpdateCameraProjection(self);
}

void func_00143A08(void* self, void* value)
{
    *(Value_00143A08*)((u8*)self + 0x204) = *(Value_00143A08*)value;
    UpdateCameraProjection(self);
}

void func_00143A38(Camera* self, f32 value)
{
    self->f1C0 = value;
    UpdateCameraProjection(g_camera);
}

void func_00143A60(Camera* self, s32 flag)
{
    if (flag != 0) {
        func_00144938(self, D_00261880, D_00261890);
    }
    self->stackCount = 0;
    func_001493B8(&self->ctl454, 0);
    PushCameraController(self, 0, &self->ctl454, 0, 0);
    func_001455C0(self, 0);
    self->f21C = 0x0FFFFFFF;
    self->f218 = -10.0f;
}

void func_00143AF0(Camera* obj)
{
    obj->f340 = 0;
}

void func_00143AF8(Camera* list, void* item)
{
    u32 n = list->f340;
    if (n < 8) {
        list->f344[n] = item;
        list->f340 = n + 1;
    }
}

void func_00143B20(Camera* list, s32 value)
{
    for (s32 i = 0; i < list->f340; i++) {
        if (value == ((s32*)list->f344)[i]) {
            CopyMemory(&((s32*)list->f344)[i], &((s32*)list->f344)[i + 1], (list->f340 - i - 1) * 4);
            list->f340--;
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

void func_00143E40(Camera* self, s32 flag, f32 dt)
{
    if (self->f220 != 0) {
        self->f220 = 0;
        self->f224 = 1;
        self->f228 = 0;
    }
    if (self->stackCount > 0) {
        T2173* n = self->stack[0].ctl;
        T2173* prev = 0;
        void* last = 0;
        if (n != 0) {
            do {
                void* o = self->stack[0].target;
                u8* x;
                if (o != 0) {
                    x = (u8*)self + 0x2F0;
                    if (o != last) {
                        ((VFn_143E40)(*(void***)o)[0x124 / 4])(o, dt, x);
                        if (prev != 0 || o != self->f2E0) {
                            func_001433E0(self, o, x);
                        }
                        func_00143208(self, o, dt, x);
                        self->f2E0 = o;
                        last = o;
                    }
                } else {
                    x = 0;
                }
                const Vt2173* vt = n->vt;
                if (vt->m04 != 0) {
                    u8* t = (D_00262C68 & 1) ? g_padRecord : g_blankPadRecord;
                    vt->m04(n, x, t, dt);
                }
                prev = n;
                if (self->stackCount <= 0) break;
                n = self->stack[0].ctl;
            } while (n != prev);
        }
    }
    if (self->f224 != 0) {
        SnapCameraZoom(self, self->f1C8);
    } else if (self->f1C4 != self->f1C8) {
        self->f1C4 = ApproachValueClampingVelocity(self->f1C4, self->f1CC, self->f1C8, dt, &self->f1D0, &self->f1CC);
        UpdateCameraProjection(self);
    }
    if (flag != 0) {
        self->f228 = 0;
        self->f224 = 0;
    }
}

ASM_FUNC(func_00144008);

ASM_FUNC(func_00144128);

ASM_FUNC(func_001441C0);

void func_00144270(Camera* self)
{
    Quad_144270 in;
    s32 out;
    Ctx_144270* g;

    func_00144008(self);
    g = *(Ctx_144270**)g_currentWorld;
    if (g != 0) {
        in = *(Quad_144270*)self->f40;
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
    InitIdentityMatrix(&m);
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
    InvertMatrix4x4(&m, &v);
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
    BeginDmaTag(g_vifPacketWriter);
    WriteVifBaseOffset(g_vifPacketWriter, 0, 0);
    CopyWordsToWriter(g_vifPacketWriter, 0xC, 4, self + 0x100, 4);
    CopyWordsToWriter(g_vifPacketWriter, 0xC, 4, self + 0x140, 8);
    CloseDmaTag(g_vifPacketWriter);
}

void func_001448C8(Camera* self, Quad_1448C8* a, Quad_1448C8* b)
{
    if (a != 0) {
        *(Quad_1448C8*)self->f40 = *a;
    }
    if (b != 0) {
        *(Quad_1448C8*)self->f80 = b[0];
        *(Quad_1448C8*)self->f90 = b[1];
        *(Quad_1448C8*)self->fA0 = b[2];
    }
    func_00144540(self);
    f32 zero = 0.0f;
    self->f2C0 = zero;
    self->f2BC = zero;
    self->f2B4 = zero;
    self->f2B0 = zero;
    self->f2B8 = zero;
}

void func_00144938(Camera* self, void* p, s32 q)
{
    func_00144BE8(self, 0, p, q, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

ASM_FUNC(func_00144978);

ASM_FUNC(func_00144AA0);

void func_00144B70(Camera* self, Vec_144B70* arg)
{
    Vec_144B70 tmp;
    func_00144AA0((Vec_144B70*)self->f2D0, (Vec_144B70*)self->f40, &tmp, self->f2B0, self->f2B4, self->f2B8);
    func_00144978(arg, (Vec_144B70*)self->f40, &tmp, &self->f2B0, &self->f2B4, &self->f2B8);
    *(Vec_144B70*)self->f2D0 = *arg;
}

ASM_FUNC(func_00144BE8);

void func_00144FF8(Camera* self, Probe_00144FF8* p, s32 mode, f32* out)
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
    *out = WrapAngle(t + func_00205778(self->g80[1], self->g80[0]));

}

LINKER_REMNANT(func_00145080);

INCLUDE_ASM(func_00145088);

void func_001451F0(Camera* self, s32 flags, s32 k0, T2173* k1, s32 k2, s32 k3)
{
    s32 s5 = 0;
    T2173* s4 = 0;
    s32 i = 0;
    T2173Entry* w = self->stack;
    T2173Entry* r = w;
    for (; i < self->stackCount; i++, r++) {
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
    self->stackCount = w - self->stack;
    if (s4 != 0) {
        Fn2173 fn = s4->vt->m01;
        if (fn != 0) {
            fn(s4, s5);
        }
        if (self->stackCount > 0) {
            self->f364 = g_gameTime;
            T2173* o = self->stack[0].ctl;
            Fn2173 fn2 = o->vt->m00;
            if (fn2 != 0) {
                fn2(o, self->stack[0].arg);
            }
        }
    }
}

ASM_FUNC(func_001453B0);

ASM_FUNC(func_00145438);

ASM_FUNC(func_001454E0);

void func_001455C0(Camera* self, f32* src)
{
    self->f224 = 1;
    if (src != 0) {
        self->f228 = 1;
        self->f22C = *src;
    }
}

void func_001455E0(Camera* self)
{
    self->f220 = 1;
}

void func_001455F0(void* p)
{
    func_001455C0((Camera*)p, 0);
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
    total = MergeOverlappingSpans(total, recs);
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

void func_00145FB8(Camera* self, s32 value)
{
    PushStackValue(&self->ctl460, value);
}

s32 func_00145FD8(Camera* self)
{
    return PopStackValue(&self->ctl460);
}

s32 func_00145FF8(Camera* self)
{
    return PeekStackValue(&self->ctl460);
}

void func_00146018(Camera* obj, s32 value, f32 first, f32 second) { obj->ctl460.f50 = value; obj->ctl460.f54 = first; obj->ctl460.f58 = second; }

void func_00146028(Camera* obj) { obj->f218 = g_gameTime; }

ASM_FUNC(func_00146038);


