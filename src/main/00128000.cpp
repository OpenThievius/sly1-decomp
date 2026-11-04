// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "c83.h"
#include "c6b.h"
#include "c02.h"
#include "c05.h"
#include "c6c.h"
#include "t2195.h"

typedef void (*Fn_2197C0)();
extern const Fn_2197C0 D_002197C0[10];
void* func_00121228(C6C* root, C01* item, void* table);

void func_00128998(C01* item)
{
    func_00121228(item->world, item, (void*)D_002197C0);
}

void func_0012A4A0(void* self, s32 a1);

void func_0012A478(void* self, s32 a1)
{
    func_0012A4A0(self, a1 != 0 ? 1 : -1);
}

void func_00129730(void* self);

struct Sub_12A580 { u8 pad[0x40]; f32 f40; };

void func_0012A580(C02* self, f32 f)
{
    func_00129730(self);
    ((Sub_12A580*)self->f200)->f40 = f;
}

struct Sub_12A5B8 { u8 pad[0x40]; f32 f40; };

void func_0012A5B8(C02* self, f32* out)
{
    f32 r = 0.0f;
    if (self->f200 != 0) r = ((Sub_12A5B8*)self->f200)->f40;
    *out = r;
}

void func_00129730(void* self);

struct Vec16_12A5D0 { s32 v[4]; } __attribute__((aligned(16)));
struct Sub_12A5D0 { u8 pad[0x50]; Vec16_12A5D0 v50; };

void func_0012A5D0(C02* self, Vec16_12A5D0* src)
{
    func_00129730(self);
    ((Sub_12A5D0*)self->f200)->v50 = *src;
}

extern u8 D_00275C40[];

struct Vec16_12A610 { s32 v[4]; } __attribute__((aligned(16)));
struct Sub_12A610 { u8 pad[0x50]; Vec16_12A610 v50; };

void func_0012A610(C02* self, Vec16_12A610* out)
{
    Vec16_12A610* src = self->f200 != 0 ? (Vec16_12A610*)((u8*)self->f200 + 0x50) : (Vec16_12A610*)D_00275C40;
    *out = *src;
}

void func_00129730(void* self);

struct __attribute__((packed)) U64_12A630 { u64 v; };
struct Sub_12A630 { u8 pad[0x60]; U64_12A630 v60; };

void func_0012A630(C02* self, U64_12A630* src)
{
    func_00129730(self);
    ((Sub_12A630*)self->f200)->v60 = *src;
}

extern u8 D_00275C60[];

struct __attribute__((packed)) U64_12A678 { u64 v; };
struct Sub_12A678 { u8 pad[0x60]; U64_12A678 v60; };

void func_0012A678(C02* self, U64_12A678* out)
{
    U64_12A678* src = self->f200 != 0 ? (U64_12A678*)((u8*)self->f200 + 0x60) : (U64_12A678*)D_00275C60;
    *out = *src;
}

void func_00129730(void* self);

struct Vec16_12A6A0 { s32 v[4]; } __attribute__((aligned(16)));
struct Sub_12A6A0 { u8 pad[0x70]; Vec16_12A6A0 v70; };

void func_0012A6A0(C02* self, Vec16_12A6A0* src)
{
    func_00129730(self);
    ((Sub_12A6A0*)self->f200)->v70 = *src;
}

extern u8 D_00275C40[];

struct Vec16_12A6E0 { s32 v[4]; } __attribute__((aligned(16)));
struct Sub_12A6E0 { u8 pad[0x70]; Vec16_12A6E0 v70; };

void func_0012A6E0(C02* self, Vec16_12A6E0* out)
{
    Vec16_12A6E0* src = self->f200 != 0 ? (Vec16_12A6E0*)((u8*)self->f200 + 0x70) : (Vec16_12A6E0*)D_00275C40;
    *out = *src;
}

void func_00128278(C07* self)
{
    T2195* a = self->f1EC;
    if (a != 0 && a->mode0 == 5) {
        do {
            a->vt->release(a, 0);
            a = self->f1EC;
        } while (a != 0 && a->mode0 == 5);
    }
    T2195* b = self->f1F0;
    if (b != 0 && b->mode1 == 5) {
        do {
            b->vt->release(b, 0);
            b = self->f1F0;
        } while (b != 0 && b->mode1 == 5);
    }
}

void func_001291A0(C02* self, f32 x)
{
    self->f290 = x * 0.01f;
}

void* func_001291D0(f32 x);
void func_001B1DA8(void* p, f32 x);

void func_001292E8(f32 x)
{
    func_001B1DA8(func_001291D0(x), x);
}

extern u8 D_0027B520[];
void func_001B1AC8(void* p);

void* func_00129400(C02* self)
{
    if (self->f284 != 0) return self->f284;
    func_001B1AC8(D_0027B520);
    return D_0027B520;
}

struct Sub_129510 { u8 pad[0x44]; f32 f44; };

void func_00129510(C02* self, f32* out)
{
    *out = ((Sub_129510*)func_00129400(self))->f44;
}

extern u8 D_00260E80[];
void* func_0018D500(s32 n);

struct __attribute__((aligned(16))) Quad_129F58 { s32 v[4]; };

void func_00129F58(C02* self, Quad_129F58* src)
{
    if (self->p210 == D_00260E80) self->p210 = (u8*)func_0018D500(16);
    *(Quad_129F58*)self->p210 = *src;
}

extern u8 D_00260EC0[];
void func_0012A320(void* self, f32* v);

void func_0012A270(void* self, f32 s)
{
    f32 v[4];
    f32* m = (f32*)D_00260EC0;
    v[0] = m[0] * s;
    v[1] = m[1] * s;
    v[2] = m[2];
    v[3] = m[3] * s;
    func_0012A320(self, v);
}

void func_0012A3E8(void* self, s32 flag);

void func_0012A3C8(void* self, s32 a1)
{
    func_0012A3E8(self, a1 != 0);
}

void func_00129730(void* self);

struct Sub_12A770 { u8 pad[0x44]; void* f44; };

void func_0012A770(C02* self, void* v)
{
    func_00129730(self);
    ((Sub_12A770*)self->f200)->f44 = v;
}

void* func_00185468(void* p);


void func_0012A888(C02* self, void** out)
{
    *out = func_00185468(self->f200);
}

struct Ctx_12AA28 { u8 pad[0x90]; void* field; };

Ctx_12AA28* func_0012A970(void* self);

void func_0012AA28(void* self, void* value)
{
    Ctx_12AA28* ctx = func_0012A970(self);
    ctx->field = value;
}

struct Inner_12AC88 { s32 value; };

void func_0012AC88(C02* self, s32* out)
{
    s32 v = -1;
    if (self->f2AC != 0) v = ((Inner_12AC88*)self->f2AC)->value;
    *out = v;
}

struct Inner_12AD98 { u8 pad[0xC]; f32 value; };

void func_0012ABA8(void* self, f32 f);

void func_0012AD98(C02* self, f32 f)
{
    func_0012ABA8(self, f);
    ((Inner_12AD98*)self->f2AC)->value = f;
}

struct Inner_12AEB0 { u8 pad[0x1C]; void* ptr; };

void func_001BF7F8(void* p);

void func_0012AEB0(C02* self)
{
    Inner_12AEB0* in = (Inner_12AEB0*)self->f2AC;
    if (in != 0) {
        if (in->ptr != 0) func_001BF7F8(in->ptr);
    }
}

struct Entry_12B0B0 { s32 w[16]; } __attribute__((aligned(16)));

extern Entry_12B0B0 D_00260F00[4];

void func_0012B040(void* self);

void func_0012B0B0(C02* self, s32 a1)
{
    func_0012B040(self);
    ((Entry_12B0B0*)self->f288)->w[0] = a1;
    Entry_12B0B0* e = (Entry_12B0B0*)self->f288;
    s32 k = e->w[0];
    if (k != -1) *e = D_00260F00[k];
}


void func_0012B250(C02* self, s32 v)
{
    self->tint[2] = v;
    self->tint[1] = v;
    self->tint[0] = v;
}


void func_0012B2A0(C02* self, s32 v)
{
    self->tint[2] = v;
}

struct Obj_12B2E8 { u8 pad[0xC]; u32 value; };

s32 func_0012B2E8(C02* self, Obj_12B2E8* a1)
{
    return a1->value != 0;
}

struct Node_128DB8 { u8 pad[0x18]; s32 f18; };
struct Part_128DB8 {
    u8 pad0[0x60];
    Node_128DB8* p60;
    Node_128DB8* p64;
    u8 pad68[0x18];
    s32 f80;
    Node_128DB8* p84;
    void* p88;
    u8 pad8c[0xB0 - 0x8C];
    s32 flags;
};

Node_128DB8* func_0015A448(void* a0, void* a1, void* a2);
void* func_0015A868(void* a0, s32 a1);

void func_00128DB8(C02* self)
{
    Part_128DB8* p = (Part_128DB8*)self->f224;
    if (p == 0) return;
    s32 v = p->flags | 0x8000;
    p->flags = v;
    if (v & 0x10) {
        p->p60 = func_0015A448(self->world, p->p60, self);
        p->p64 = (Node_128DB8*)1;
    }
    if (p->flags & 0x20) {
        Node_128DB8* r = func_0015A448(self->world, p->p84, self);
        p->p84 = r;
        s32 x = r->f18;
        p->f80 = x;
        p->p88 = func_0015A868(self, x);
    }
    if (p->flags & 0x40) {
        p->p60 = func_0015A448(self->world, p->p60, self);
        p->p64 = func_0015A448(self->world, p->p64, self);
    }
}

struct Timer_129108 { u8 pad0[4]; s32 f4; s32 f8; s32 fC; f32 f10; };

void* func_0018D5C0(s32 size);

Timer_129108* func_00129108(C02* self)
{
    if (self->f2A0 == 0) {
        Timer_129108* t = (Timer_129108*)func_0018D5C0(0x14);
        self->f2A0 = t;
        t->f4 = -1;
        ((Timer_129108*)self->f2A0)->f8 = 0;
        ((Timer_129108*)self->f2A0)->fC = 0;
        ((Timer_129108*)self->f2A0)->f10 = 1.0f;
    }
    return (Timer_129108*)self->f2A0;
}

void func_00129170(C02* self, f32 x)
{
    self->f28C = x * 0.01f;
}

void func_00129188(C02* self, f32* out)
{
    *out = self->f28C * 100.0f;
}

void func_001291B8(C02* self, f32* out)
{
    *out = self->f290 * 100.0f;
}

void* func_001B5EE0(void* a0);
void func_001B1AC8(void* a0);
void func_00152470(void* a0, void* a1);

void* func_001291D0(C02* self)
{
    if (self->f284 == 0) {
        void* o = func_001B5EE0((u8*)self->world + 0x1BF4);
        self->f284 = o;
        func_001B1AC8(o);
        func_00152470((u8*)self->world + 0x1C00, self->f284);
    }
    return self->f284;
}

struct Sub_12A7F8 { u8 pad0[0x48]; s32 f48; };

void func_0012A7F8(C02* self, s32* out)
{
    s32 v = 0;
    if (self->f200 != 0) {
        v = ((Sub_12A7F8*)self->f200)->f48;
    }
    *out = v;
}

struct Sub_12A810 { u8 pad0[0x20]; s32 f20; };

void func_00129730(C02* self);

void func_0012A810(C02* self, s32 value)
{
    func_00129730(self);
    ((Sub_12A810*)self->f200)->f20 = value;
}

struct Sub_12A848 { u8 pad0[0x20]; s32 f20; };

void func_0012A848(C02* self, s32* out)
{
    s32 v = -1;
    if (self->f200 != 0) {
        v = ((Sub_12A848*)self->f200)->f20;
    }
    *out = v;
}

struct Sub_12A8B8 { u8 pad0[0x4C]; s32 f4C; };

void func_0012A8B8(C02* self)
{
    ((Sub_12A8B8*)self->f200)->f4C = 0;
}

struct Sub_12A8C8 { u8 pad0[0x4C]; s32 f4C; };

void func_0012A8C8(C02* self)
{
    ((Sub_12A8C8*)self->f200)->f4C = 1;
}

void* func_0015A418(s32 a0, s32 a1, s32 a2, void* a3);
void* func_0011E580(s32 a0, s32 a1, void* a2, s32 a3, s32 a4);

void* func_0012A970(C02* self)
{
    void* r = func_0015A418((s32)self->world, 0x102, 0x22A, self);
    if (r != 0) {
        return r;
    }
    return func_0011E580(0x75, (s32)self->world, self, 0x22A, -1);
}

void func_0012A9C8(C02* self, s32 value)
{
    C02* o = (C02*)func_0012A970(self);
    if (value != -1) {
        o->f88 = value;
    }
}

void* func_001291D0(void* self);
void func_001B1CF8(void* self, s32 value);

void func_00129288(void* self, s32 value)
{
    func_001B1CF8(func_001291D0(self), value);
}

void* func_001291D0(void* self, f32 x);
void func_001B1D70(void* self, f32 v);

void func_001292B8(void* self, f32 x)
{
    func_001B1D70(func_001291D0(self, x), x);
}

struct __attribute__((aligned(16))) Quad_12A028 { s32 w[4]; };

extern u8 D_00260E90[];
void* func_0018D500(s32 n);

void func_0012A028(C02* self, Quad_12A028* src)
{
    if (self->p214 == D_00260E90) self->p214 = (u8*)func_0018D500(16);
    *(Quad_12A028*)self->p214 = *src;
}

struct __attribute__((aligned(16))) Quad_12A0F8 { s32 w[4]; };

extern u8 D_00260EA0[];
void* func_0018D500(s32 n);

void func_0012A0F8(C02* self, Quad_12A0F8* src)
{
    if (self->p218 == D_00260EA0) self->p218 = (u8*)func_0018D500(16);
    *(Quad_12A0F8*)self->p218 = *src;
}

struct Sub_12ACD8 { u8 pad0[4]; f32 value; };

void func_0012ACD8(C02* self, f32* out)
{
    Sub_12ACD8* s = (Sub_12ACD8*)self->f2AC;
    f32 v = 3000.0f;
    if (s != 0) v = s->value;
    *out = v;
}

struct Sub_12ACF8 { u8 pad0[8]; f32 value; };

void func_0012ABA8(C02* self);

void func_0012ACF8(C02* self, f32 value)
{
    func_0012ABA8(self);
    ((Sub_12ACF8*)self->f2AC)->value = value;
}

struct __attribute__((packed)) Rec_12AD30 { s32 a; s32 b; };
struct Sub_12AD30 { u8 pad0[0x14]; Rec_12AD30 rec; };

void func_0012AD30(C02* self, Rec_12AD30* src)
{
    func_0012ABA8(self);
    ((Sub_12AD30*)self->f2AC)->rec = *src;
}

struct Sub_12AD78 { u8 pad0[8]; f32 value; };

void func_0012AD78(C02* self, f32* out)
{
    Sub_12AD78* s = (Sub_12AD78*)self->f2AC;
    f32 v = 300.0f;
    if (s != 0) v = s->value;
    *out = v;
}

void func_0012B2C0(C02* self, s32* out)
{
    *out = self->tint[3];
}

void func_0012B2D0(C02* self, u8 v)
{
    self->f2B4 = v;
}

void func_0012B2D8(C02* self, s32* out)
{
    *out = self->f2B4;
}

extern s32 D_00261990;
s32 func_00182FC8(C02* self);
void func_00143AF8(s32 a, C02* self);
void func_00143B20(s32 a, C02* self);

void func_0012B420(C02* self, s32 flag)
{
    u64 want = flag != 0;
    if (want != (((self->flags >> 36) ^ 1) & 1)) {
        return;
    }
    u64 bit = (u64)(flag & 1) << 36;
    self->flags = (self->flags & 0xFFFFFFEFFFFFFFFFULL) | bit;
    if (func_00182FC8(self) == 0) {
        return;
    }
    if (flag != 0) {
        func_00143AF8(D_00261990, self);
    } else {
        func_00143B20(D_00261990, self);
    }
}

void func_001B1FB0(void* self, f32 x);

void func_00129318(f32 x)
{
    func_001B1FB0(func_001291D0(x), x);
}

void func_001B1FE0(void* self, f32 x);

void func_00129348(f32 x)
{
    func_001B1FE0(func_001291D0(x), x);
}

void func_001B2010(void* self, f32 x);

void func_00129378(f32 x)
{
    func_001B2010(func_001291D0(x), x);
}

void func_001B2068(void* self, void* src);

void func_001293A8(void* self, void* src)
{
    func_001B2068(func_001291D0(self), src);
}

typedef u64 Quad_129EE0 __attribute__((mode(TI)));
struct Frame_129EE0 { Quad_129EE0 r; Quad_129EE0 a; Quad_129EE0 b; };

void func_00118CF0(Quad_129EE0* out, void* src);
void func_00118D10(Quad_129EE0* out, void* src);
Quad_129EE0 func_00118D30(Quad_129EE0 a, Quad_129EE0 b);
Quad_129EE0 func_00118D20(Quad_129EE0* out, Quad_129EE0 v);
void func_00129F58(void* self, Quad_129EE0* src);

void func_00129EE0(void* self, void* src)
{
    Frame_129EE0 f;
    u8* p = D_00260E80;
    func_00118CF0(&f.a, src);
    Quad_129EE0 av = f.a;
    func_00118D10(&f.b, p);
    (void)func_00118D20(&f.r, func_00118D30(av, f.b));
    func_00129F58(self, &f.r);
}

struct __attribute__((packed)) Vec4_12A150 { f32 x, y, z, w; };
struct Vec4F_12A150 { f32 x, y, z, w; };
extern Vec4F_12A150 D_00260EB0;

void func_0012A200(C02* self, Vec4_12A150* src);

void func_0012A150(C02* self, f32 scale)
{
    Vec4F_12A150 tmp;
    tmp.x = D_00260EB0.x * scale;
    tmp.y = D_00260EB0.y * scale;
    tmp.z = D_00260EB0.z;
    tmp.w = D_00260EB0.w * scale;
    func_0012A200(self, (Vec4_12A150*)&tmp);
}

void func_0012A1A0(C02* self, f32 scale)
{
    Vec4_12A150 tmp = *(Vec4_12A150*)self->p21C;
    tmp.w = scale * (tmp.x - tmp.y) / tmp.z;
    func_0012A200(self, &tmp);
}

void* func_0018D500(s32 size);

void func_0012A200(C02* self, Vec4_12A150* src)
{
    if (self->p21C == (u8*)&D_00260EB0) {
        self->p21C = (u8*)func_0018D500(16);
    }
    *(Vec4_12A150*)self->p21C = *src;
}

struct Part_0012AC08 { void* link; f32 f4; f32 f8; f32 fc; f32 f10; u8 sub14[8]; u8 sub1C[4]; f32 f20; };

void func_0012ACA0(C02* self, f32 value)
{
    func_0012ABA8(self);
    ((Part_0012AC08*)self->f2AC)->f4 = value;
}

void func_0012ADD0(C02* self, f32 value)
{
    func_0012ABA8(self);
    ((Part_0012AC08*)self->f2AC)->f20 = value;
}

void func_0012AE08(C02* self, f32* out)
{
    f32 r = 0.0f;
    if (self->f2AC != 0) {
        r = ((Part_0012AC08*)self->f2AC)->f20;
    }
    *out = r;
}

void func_0012B290(C02* self, s32* out)
{
    *out = self->tint[1];
}

void func_0012B2A8(C02* self, s32* out)
{
    *out = self->tint[2];
}

void func_0012B2B8(C02* self, s32 value)
{
    self->tint[3] = value;
}

s32 func_00182FC8(void* self);

void func_0012B4C8(C02* self, s32 flag)
{
    if ((0 < (u32)flag) != (self->f294 == 0)) {
        goto done;
    }
    if (func_00182FC8(self) == 0) {
        goto store;
    }
    if (self->parent != 0) {
        goto store;
    }
    self->desc->m03(self);
    self->f294 = flag;
    self->desc->m02(self);
    goto done;
store:
    self->f294 = flag;
done:
    return;
}

struct Owner_1293D8 { u8 pad[0xB0]; s32 field_B0; };

void func_001293D8(void* self, s32 value)
{
    ((Owner_1293D8*)func_001291D0(self))->field_B0 = value;
}


void func_00129440(C02* self, s32* out)
{
    *out = self->f284 != 0;
}

struct __attribute__((packed)) Pack4_12A2C0 { f32 a, b, c, d; };

extern void func_0012A320(C02* self, Pack4_12A2C0* in);

void func_0012A2C0(C02* self, f32 scale)
{
    Pack4_12A2C0 tmp;
    tmp = *(Pack4_12A2C0*)self->p220;
    tmp.d = scale * (tmp.a - tmp.b) / tmp.c;
    func_0012A320(self, &tmp);
}

struct __attribute__((packed)) Pack4_12A320 { f32 a, b, c, d; };

void* func_0018D500(u32 size);

void func_0012A320(C02* self, Pack4_12A320* src)
{
    if (self->p220 == D_00260EC0) {
        self->p220 = (u8*)func_0018D500(0x10);
    }
    *(Pack4_12A320*)self->p220 = *src;
}

struct Part_12AE20 { u8 pad0[0xC]; f32 weight; u8 pad1[0xC]; void* ptr; };

void func_001BF8E8(void* p);

void func_0012AE20(C02* self)
{
    Part_12AE20* part = (Part_12AE20*)self->f2AC;
    if (part != 0) {
        void* p = part->ptr;
        if (p != 0) {
            func_001BF8E8(p);
        }
    }
}

struct Part_12AE58 { u8 pad0[0xC]; f32 weight; u8 pad1[0xC]; void* ptr; };

void func_0012AE58(C02* self, f32* out)
{
    f32 v = 1.0f;
    if (self->f2AC != 0) {
        v = ((Part_12AE58*)self->f2AC)->weight;
    }
    *out = v;
}

void func_0012B550(C02* ctx, s32 on)
{
    if (on != 0) {
        ctx->flags |= (u64)1 << 32;
    } else {
        ctx->flags &= ~((u64)1 << 32);
    }
}

void func_0012B590(C02* ctx, s32* out)
{
    if ((ctx->flags & ((u64)1 << 32)) != 0) {
        *out = 1;
    } else {
        *out = 0;
    }
}

struct Node_129450 {
    u8 pad[2];
    s16 value_2;
};

void func_00129450(C02* self, s32* out)
{
    void* p = self->f284;
    if (p == 0) {
        goto fail;
    }
    {
        Node_129450* n = *(Node_129450**)p;
        if (n == 0) {
            goto fail;
        }
        *out = n->value_2;
        return;
    }
fail:
    *out = -1;
}

struct Sub_129480 {
    u8 pad[4];
    f32 value_4;
};

void* func_00129400(void* self);

void func_00129480(void* self, f32* out)
{
    Sub_129480* s = (Sub_129480*)func_00129400(self);
    *out = s->value_4;
}

struct Node_129C20 {
    u8 pad0[0x10];
    Node_129C20* f10;
    u8 pad1[4];
    void* f18;
    void* f1C;
};

s32 func_001833F0(void* key, s32 item);

Node_129C20* func_00129C20(C02* self, s32 key)
{
    ListFrame frame;
    Node_129C20* n = (Node_129C20*)self->world->f1B94;
    while (n != 0) {
        if (n->f1C == self) {
            if (key == -1) return n;
            if (func_001833F0(n->f18, key) != 0) return n;
        }
        n = n->f10;
    }
    return 0;
}

s32 func_00123DC0(void* a);
s32 func_00123E00(void* a);

s32 func_00129D70(Actor6C* self)
{
    Actor6C* n;
    if (func_00123DC0((u8*)self + 0x150) == 0) return 0;
    if (func_00123E00((u8*)self + 0x160) != 0) goto body;
    return 0;
body:
    n = (Actor6C*)self->f34;
    while (n != 0) {
        if ((n->vtable->f8 & 1) != 0) {
            if (func_00129D70(n) == 0) return 0;
        }
        n = (Actor6C*)n->f1C;
    }
    return 1;
}

void func_00129730(void* self);

struct __attribute__((packed)) U64_12A700 { u64 v; };
struct Sub_12A700 { u8 pad[0x80]; U64_12A700 v80; };

void func_0012A700(C02* self, U64_12A700* src)
{
    func_00129730(self);
    ((Sub_12A700*)self->f200)->v80 = *src;
}

struct Part_12AE78 { u8 pad[0x10]; f32 value; };

void func_0012ABA8(void* self, f32 f);

void func_0012AE78(C02* self, f32 f)
{
    func_0012ABA8(self, f);
    ((Part_12AE78*)self->f2AC)->value = f;
}

struct Part_12AEE8 { u8 pad[0x10]; f32 value; };

void func_0012AEE8(C02* self, f32* out)
{
    f32 r = 0.0f;
    if (self->f2AC != 0) {
        r = ((Part_12AEE8*)self->f2AC)->value;
    }
    *out = r;
}

struct Inner_0012B238 { u8 pad[0x30]; f32 value; };

void func_0012B238(C02* self, f32* out)
{
    f32 v = 0.0f;
    Inner_0012B238* p = (Inner_0012B238*)self->f288;
    if (p != 0) v = p->value;
    *out = v;
}

void func_0012B260(C02* self, s32* out)
{
    *out = self->tint[0];
}

struct Sub_1294B0 { u8 pad[8]; f32 f8; };

void* func_00129400(void* self);

void func_001294B0(void* self, f32* out)
{
    *out = ((Sub_1294B0*)func_00129400(self))->f8;
}

struct Sub_1294E0 { u8 pad[0x40]; f32 f40; };

void* func_00129400(void* self);

void func_001294E0(void* self, f32* out)
{
    *out = ((Sub_1294E0*)func_00129400(self))->f40;
}

void func_00129DF8(C02* self)
{
    if (self->root != 0) self->root->tries = 0;
}

typedef u64 Quad_129E10 __attribute__((mode(TI)));
struct Frame_129E10 { Quad_129E10 r; Quad_129E10 a; Quad_129E10 b; };

extern u8 D_00260E70[];

void func_00118CF0(Quad_129E10* out, void* src);
void func_00118D10(Quad_129E10* out, void* src);
Quad_129E10 func_00118D30(Quad_129E10 a, Quad_129E10 b);
Quad_129E10 func_00118D20(Quad_129E10* out, Quad_129E10 v);
void func_00129E88(void* self, Quad_129E10* v);

void func_00129E10(void* self, void* src)
{
    Frame_129E10 f;
    u8* p = D_00260E70;
    func_00118CF0(&f.a, src);
    Quad_129E10 av = f.a;
    func_00118D10(&f.b, p);
    (void)func_00118D20(&f.r, func_00118D30(av, f.b));
    func_00129E88(self, &f.r);
}

extern u8 D_00275C60[];

struct __attribute__((packed)) U64_12A748 { u64 v; };
struct Sub_12A748 { u8 pad[0x80]; U64_12A748 v80; };

void func_0012A748(C02* self, U64_12A748* out)
{
    U64_12A748* src = self->f200 != 0 ? (U64_12A748*)((u8*)self->f200 + 0x80) : (U64_12A748*)D_00275C60;
    *out = *src;
}

struct Sub_12A7A8 { u8 pad[0x44]; s32 v44; };

void func_0012A7A8(C02* self, s32* out)
{
    s32 r = 0;
    if (self->f200 != 0) r = ((Sub_12A7A8*)self->f200)->v44;
    *out = r;
}

struct __attribute__((packed)) U64_12AF00 { u64 v; };
struct Sub_12AF00 { u8 pad[0x14]; U64_12AF00 p14; };

void func_0012AF00(C02* self, U64_12AF00* out)
{
    Sub_12AF00* s = (Sub_12AF00*)self->f2AC;
    if (s != 0) {
        *out = s->p14;
    } else {
        f32* f = (f32*)out;
        f[0] = -1.0f;
        f[1] = -1.0f;
    }
}

void func_0012B270(C02* self, s32 v)
{
    self->tint[0] = v;
}

void func_0012B278(C02* self, s32* out)
{
    *out = self->tint[0];
}

// Newly matched US functions from the small-function wave.
extern void func_0012A430(void*, s32);
extern void func_001BE4D8(void*);
struct Quad_129598 { s32 words[4]; } __attribute__((aligned(16)));
struct Result_129598 { u8 pad[0x30]; Quad_129598 value; };
struct Node_129B98 { u8 pad0[8]; void* item; void* owner; u8 pad2[0x34 - 0x10]; Node_129B98* next; };
extern s32 func_001833F0(void*, s32);
struct State_12A430 { u8 pad[0x10]; u8 value; };
extern void func_001296E0(void*);
struct State_12A4A0 { u8 pad[0x11]; u8 value; };
struct State_12A4E8 { u8 pad[0x14]; s32 value; };
extern void func_00129A58(void*);
struct State_12A7C0 { u8 pad[0x48]; s32 value; };
extern void func_00129730(void*);
extern void func_0012ABA8(void*);
struct Inner_12ABD0 { s32 value; };
extern void func_001BF788(void*, s32);
struct Inner_12B010 { u8 pad[0x1C]; void* resource; };
extern void func_0012B040(void*);
struct Vec_12B140 { s32 v[4]; } __attribute__((aligned(16)));
struct Vec_12B1A0 { s32 v[4]; } __attribute__((aligned(16)));

void func_0012A390(void* self, s8 value) { *((s8*)((u8*)self + 0x2C9)) = value; }

void func_0012A398(void* self, s8 value) { *((s8*)((u8*)self + 0x2CA)) = value; }

void func_0012A3A0(void* self, s32 value) { func_0012A430(self, value ? 1 : -1); }

void func_0012A3E8(C02* self, u32 value)
{
    self->flags = (self->flags & ~(3ull << 40)) | ((u64)(value & 3) << 40);
}

void func_0012A418(C02* self, u32* out)
{
    u32 value = (u32)(self->flags >> 40);
    value &= 3;
    *out = value;
}

void func_0012ABA8(C02* self)
{
    if (self->f2AC == 0) func_001BE4D8(&self->f2AC);
}

void func_0012B128(C02* self, s32* out) { *out = self->f288 ? *(s32*)self->f288 : -1; }

void func_0012B288(C02* self, u8 value) { self->tint[1] = value; }

void func_0012B868(void) {}

void func_00129598(void* self, Quad_129598* out)
{
    *out = ((Result_129598*)func_00129400(self))->value;
}

Node_129B98* func_00129B98(C02* self, s32 key)
{
    ListFrame frame;
    Node_129B98* node = (Node_129B98*)self->world->f1B64;
    while (node != 0) {
        if (node->owner == self) {
            if (key == -1) return node;
            if (func_001833F0(node->item, key) != 0) return node;
        }
        node = node->next;
    }
    return 0;
}

void func_0012A430(C02* self, s32 value)
{
    func_001296E0(self);
    ((State_12A430*)self->f1FC)->value = value;
    self->desc02()->m2B(self);
}

void func_0012A4A0(C02* self, s32 value)
{
    func_001296E0(self);
    ((State_12A4A0*)self->f1FC)->value = value;
    self->desc02()->m2B(self);
}

void func_0012A4E8(C02* self, s32 value)
{
    func_001296E0(self);
    ((State_12A4E8*)self->f1FC)->value = value;
    func_00129A58(self);
}

void func_0012A7C0(C02* self, s32 value)
{
    func_00129730(self);
    ((State_12A7C0*)self->f200)->value = value;
}

void func_0012ABD0(C02* self, s32 value)
{
    func_0012ABA8(self);
    ((Inner_12ABD0*)self->f2AC)->value = value;
}

void func_0012B010(C02* self)
{
    Inner_12B010* inner = (Inner_12B010*)self->f2AC;
    if (inner != 0) func_001BF788(inner->resource, 0);
}

void func_0012B140(C02* self, Vec_12B140* input)
{
    func_0012B040(self);
    *(Vec_12B140*)((u8*)self->f288 + 0x10) = *input;
}

void func_0012B1A0(C02* self, Vec_12B1A0* input)
{
    func_0012B040(self);
    *(Vec_12B1A0*)((u8*)self->f288 + 0x20) = *input;
}

void func_0012B200(C02* self, f32 value)
{
    func_0012B040(self);
    ((Inner_0012B238*)self->f288)->value = value;
}

struct Sub_00129540 { u8 pad[4]; f32 value; u8 gap[0x38]; f32 scale; };
f32 func_00205778(f32 a, f32 b);
void func_00129540(void* self, f32* out)
{
    Sub_00129540* sub = (Sub_00129540*)func_00129400(self);
    f32 value = func_00205778(sub->value / sub->scale, 1.0f) * 57.2957763671875f;
    *out = value + value;
}

void func_0012A528(C02* self, s32 value)
{
    func_00129730(self);
    if (value == 3) value = 9;
    ((u8*)self->f200)[0x11] = value;
    self->desc02()->m2B(self);
}

struct Sub_0012AA00 { u8 pad[0x8C]; f32 value; };
void func_0012AA00(void* self, f32 value)
{
    ((Sub_0012AA00*)func_0012A970(self))->value = value;
}

void func_00129E88(C02* self, Vec16_12A5D0* value)
{
    if (self->p20C == D_00260E70)
        self->p20C = (u8*)func_0018D500(16);
    *(Vec16_12A5D0*)self->p20C = *value;
}

void func_001B5388(void* part, f32 a, f32 b);
void func_0012AA50(C02* self, f32 a, f32 b)
{
    for (s32 i = 0; i < self->elemCount; i++) {
        Elem02* p = self->elems[i];
        if (p->kind == 6) func_001B5388(p, a, b);
    }
}

void func_00159A00(void* part, f32 value);
void func_0012AAE8(C02* self, f32 value)
{
    ListFrame frame;
    for (s32 i = 0; i < self->elemCount; i++) {
        Elem02* p = self->elems[i];
        if (p->kind == 5) func_00159A00(p, value);
    }
    for (C02* child = (C02*)self->children.head; child; child = (C02*)child->next) {
        if (child->desc->flags & 1) func_0012AAE8(child, value);
    }
}

extern Entry_12B0B0 D_00261000[2];
void func_0012B040(void* ptr)
{
    C02* self = (C02*)ptr;
    if (!self->f288) {
        self->f288 = (Entry_12B0B0*)func_0018D500(64);
        *(Entry_12B0B0*)self->f288 = D_00261000[0];
        ((Entry_12B0B0*)self->f288)->w[0] = -1;
    }
}

void func_001BF788(void* ptr, s32 value);

struct Node_1299E0 { u8 pad0[8]; Node_1299E0* next; u8 pad1[8]; s32 key; };

void func_00152540(void* list, Node_1299E0* before, Node_1299E0* value);

void func_001299E0(C02* self, Node_1299E0* src)
{
    ListFrame frame;
    Node_1299E0* node = (Node_1299E0*)self->list1E0.head;
    if (node != 0 && node->key > src->key) {
        node = node->next;
        while (node != 0 && node->key > src->key) {
            node = node->next;
        }
    }
    func_00152540(&self->list1E0, node, src);
    self->desc02()->m2B(self);
}

extern u8 D_00262300[];

void func_00152600(void* a, void* b);
void func_00152470(void* list, void* item);

void func_00129228(C02* self, s32 flag)
{
    if (flag != 0) {
        func_001291D0(self);
        return;
    }
    if (self->f284 == 0) {
        return;
    }
    func_00152600((u8*)self->world + 0x1C00, self->f284);
    func_00152470(D_00262300, self->f284);
    self->f284 = 0;
}

void func_00188FD8(void* a, f32* out);

void func_001295C8(C02* self, f32* out)
{
    Vec02 a[3];
    a[0] = self->rot.r[0];
    a[1] = self->rot.r[1];
    a[2] = self->rot.r[2];
    self->desc02()->m2A(self, a);
    func_00188FD8(a, out);
    s32 n = 2;
    f32* p = out;
    do {
        n--;
        *p = *p * 57.295776f;
        p++;
    } while (n >= 0);
}

struct Local_129648 { f32 tmp[4]; f32 out[4]; u8 pad[0x20]; };
typedef void (*VFnA_129648)(void* self, void* a, s32 b);

void func_00188A20(void* a, void* b);

void func_00129648(C02* self, f32* src)
{
    Local_129648 l;
    f32* out = l.out;
    f32* dst = l.tmp;
    f32 k = 0.01745329424738884f;
    s32 i = 2;
    do {
        *dst = *src * k;
        i--;
        src++;
        dst++;
    } while (i >= 0);
    func_00188A20(l.tmp, out);
    ((VFnA_129648)self->desc02()->m29)(self, out, 0);
    self->desc02()->m1E(self, (Mat02*)out);
}

void func_00182C18(void* self);
void func_00152438(void* self, s32 value);

void func_0012B870(C83* self)
{
    func_00182C18(self);
    func_00152438(&self->props6C, 0x3C);
    Kin83* k = &self->kin;
    k->pos = 1.0f;
    k->vel = 0.0f;
    k->acc = 0.0f;
    self->lo = 0.0f;
    self->hi = 1.0f;
    self->out = 1.0f;
}

// NEAR: same bytes except the load order of the arguments to func_001BFCD8 (retail loads a0, a4, f12, a1, f13..f15 and f16 last, in the delay slot)
struct Part_0012AC08R { void* link; f32 f4; f32 f8; f32 fc; f32 f10; u8 sub14[8]; void* sub1C; f32 f20; };

void func_001BF788(void* self, s32 n);
void func_001BFCD8(void* a0, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void* a1, void* a2, s32 a3, void* a4, s32 a5);

void func_0012AC08(C02* self, void* value)
{
    func_0012ABA8(self);
    func_001BF788(((Part_0012AC08R*)self->f2AC)->sub1C, 0);
    ((Part_0012AC08R*)self->f2AC)->link = value;
    Part_0012AC08R* p = (Part_0012AC08R*)self->f2AC;
    func_001BFCD8(p->link, p->f4, p->f8, p->fc, p->f10, p->f20, &p->sub1C, self, 0, p->sub14, 0);
}

// NEAR: same bytes except the load order of the arguments to func_001BFCD8 (retail loads a0, a4, f12, a1, f13..f15 and f16 last, in the delay slot)
struct __attribute__((packed)) Rec_0012AF38 { s32 a; s32 b; };
struct Part_0012AF38 { void* link; f32 f4; f32 f8; f32 fc; f32 f10; Rec_0012AF38 rec14; void* sub1C; f32 f20; };

void func_001BF788(void* self, s32 n);
void func_001BFCD8(void* a0, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void* a1, void* a2, s32 a3, void* a4, s32 a5);

void func_0012AF38(C02* self, void* value, Rec_0012AF38* src, f32 x, f32 y, f32 z)
{
    func_0012ABA8(self);
    ((Part_0012AF38*)self->f2AC)->link = value;
    ((Part_0012AF38*)self->f2AC)->f4 = x;
    ((Part_0012AF38*)self->f2AC)->f8 = y;
    ((Part_0012AF38*)self->f2AC)->fc = z;
    ((Part_0012AF38*)self->f2AC)->rec14 = *src;
    func_001BF788(((Part_0012AF38*)self->f2AC)->sub1C, 0);
    Part_0012AF38* p = (Part_0012AF38*)self->f2AC;
    func_001BFCD8(p->link, p->f4, p->f8, p->fc, p->f10, p->f20, &p->sub1C, self, 0, &p->rec14, 0);
}

// NEAR: same bytes except the prologue order: retail loads the crc word and the table base before the n > 0 test (lw v0, addiu t1, then blez); ours tests first
s32 D_00261080[4];

void func_001837E0(void* self, s32 a, s32 b, s32 c);

void func_0012B760(C6B* self)
{
    if (self->remaining != 0) {
        s32 n = self->remaining;
        u32* p = self->cursor;
        u32 crc = self->crc;
        u8* tbl = (u8*)self->table;
        s32 i = 0;
        if (n > 0) {
            do {
                u32 w = *p;
                i++;
                n -= 4;
                crc = *(u32*)(tbl + (((crc ^ w) & 0xFF) << 2)) ^ (crc >> 8);
                crc = *(u32*)(tbl + (((crc ^ (w >> 8)) & 0xFF) << 2)) ^ (crc >> 8);
                crc = *(u32*)(tbl + (((crc ^ (w >> 16)) & 0xFF) << 2)) ^ (crc >> 8);
                crc = *(u32*)(tbl + (((crc ^ (w >> 24)) & 0xFF) << 2)) ^ (crc >> 8);
                p++;
                if (i >= 64) break;
            } while (n > 0);
        }
        self->cursor = p;
        self->crc = crc;
        self->remaining = n;
        if (n == 0 && crc != 0) {
            D_00261080[0] = 1;
            func_001837E0(self, 2, 0, 0);
        }
    }
}

s32 func_00137D10(Stream83* p);
s32 func_00137BE0(Stream83* p);
s32 func_00137CC0(Stream83* p);
s32 func_00137B90(Stream83* p);
void* func_0018D500(s32 size);
void* func_0018D5C0(s32 size);
void func_0012D2A8(C83* a, Track83* b);
void func_0012BC38(C83* a, Stream83* b, s32 c, s32* d, s32* e);
void func_0011EC40(C83* a, Stream83* b);
T2196_Pos* func_00120FB0(s32 cc);
T2196_Rot* func_00121050(s32 cc);
T2196_Scale* func_001210F0(s32 cc);
T2196_Weight* func_00121160(s32 cc);

void func_0012B8C8(C83* self, Stream83* other)
{
    s32 k;
    Track83* sel = 0;
    Track83* e;
    T2196_Pos* qp;
    T2196_Rot* qr;
    T2196_Scale* qs;
    T2196_Weight* qw;
    s32 i;
    s32 j;
    s32 t;
    s32 flags;

    t = func_00137D10(other);
    self->id = t;
    t = func_00137D10(other);
    self->length = (f32)t * 0.01666666753590107f;
    t = func_00137BE0(other);
    self->targetCount = t;
    self->targets = (s32*)func_0018D500(t << 2);
    for (k = 0; k < self->targetCount; k++) {
        self->targets[k] = func_00137D10(other);
    }
    t = func_00137CC0(other);
    self->trackCount = t;
    self->tracks = (Track83*)func_0018D5C0(t * 28);
    for (i = 0; i < self->trackCount; i++) {
        e = &self->tracks[i];
        e->target = func_00137D10(other);
        flags = func_00137CC0(other);
        if (flags & 1) {
            qp = func_00120FB0(func_00137CC0(other));
            e->pos = qp;
            if (qp->vt->read) qp->vt->read(qp, other);
        }
        if (flags & 2) {
            qr = func_00121050(func_00137CC0(other));
            e->rot = qr;
            if (qr->vt->read) qr->vt->read(qr, other);
        }
        if (flags & 4) {
            qs = func_001210F0(func_00137CC0(other));
            e->scale = qs;
            if (qs->vt->read) qs->vt->read(qs, other);
        }
        if (flags & 8) {
            qw = func_00121160(func_00137CC0(other));
            e->weight = qw;
            if (qw->vt->read) qw->vt->read(qw, other);
        }
        if (flags & 0x10) {
            e->morphCount = func_00137B90(other);
            e->morph = (T2196_Weight**)func_0018D5C0(e->morphCount << 2);
            for (j = 0; j < e->morphCount; j++) {
                t = func_00137CC0(other);
                if (t != -1) {
                    e->morph[j] = func_00121160(t);
                    qw = e->morph[j];
                    if (qw->vt->read) qw->vt->read(qw, other);
                }
            }
        }
        sel = (flags & 0x20) ? e : sel;
    }
    if (sel != 0) func_0012D2A8(self, sel);
    func_0012BC38(self, other, 0, &self->startCount, &self->startList);
    func_0012BC38(self, other, 1, &self->timedCount, &self->timedList);
    func_0012BC38(self, other, 0, &self->endCount, &self->endList);
    func_0011EC40(self, other);
}

struct Sub_12B5B8 {
    u8 pad0[0x60];
    void* f60;
    u8 pad1[0xB0 - 0x64];
    s32 fB0;
};

void* func_0018D5C0(s32 bytes);
void func_00128018(void* a, void* b, void* c, void* d);
void func_00128150(void* a, void* b, void* c, void* d);

void func_0012B5B8(C02* self, void* a1, void* a2)
{
    void* t = self->parent;
    if (a1 == t || a2 == t || a1 == a2) {
        if (a1 != 0 || a2 != 0) {
            if (self->f224 == 0) {
                self->f224 = (Sub_12B5B8*)func_0018D5C0(0xC0);
            }
        }
        Sub_12B5B8* p = (Sub_12B5B8*)self->f224;
        if (a1 != self->parent) {
            p->f60 = a1;
            p->fB0 = p->fB0 | 4;
        } else {
            p->fB0 = p->fB0 & 4;
        }
        if (a2 != self->parent) {
            p->f60 = a2;
            p->fB0 = p->fB0 | 8;
        } else {
            p->fB0 = p->fB0 & 8;
        }
        func_00128018(0, a1, (u8*)self + 0x140, (u8*)self + 0x100);
        func_00128150(0, a2, (u8*)self + 0x110, (u8*)self + 0xD0);
    }
}

struct Blk_128C10 {
    u8 b[48];
} __attribute__((aligned(16)));

extern u8 D_002483D0[];

s32 func_00137C40(void* a);
void* func_0018D5C0(u32 n);
void func_00137EB0(void* a, void* b);
s32 func_00137D10(void* a);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_00137E70(void* a, void* b);
f32 func_00137DF8(void* a);
f32 func_001EA408(f32 a);
s32 func_00137B90(void* a);

void func_00128C10(C02* self, void* a1)
{
    s32 flags = func_00137C40(a1);
    if (flags) {
        u8* p = (u8*)func_0018D5C0(0xC0);
        self->f224 = p;
        *(s32*)(p + 0xB0) = flags;
        u8* q = p + 0x30;
        *(Blk_128C10*)p = *(Blk_128C10*)D_002483D0;
        *(Blk_128C10*)q = *(Blk_128C10*)D_002483D0;
        if (flags & 1) func_00137EB0(a1, p);
        if (flags & 2) func_00137EB0(a1, q);
        if (flags & 0xC) {
            s32 r = func_00137D10(a1);
            if (r != -1) {
                *(s32*)(p + 0x60) = func_0015A418(self->world, 3, r, self);
            }
        }
        if (flags & 0x10) {
            *(s32*)(p + 0x60) = func_00137D10(a1);
        }
        if (flags & 0x20) {
            *(s32*)(p + 0x84) = func_00137D10(a1);
            func_00137E70(a1, p + 0x60);
            func_00137E70(a1, p + 0x70);
            f32 f = func_001EA408(func_00137DF8(a1));
            *(s32*)(p + 0x98) = 0;
            *(f32*)(p + 0x8C) = f;
            *(f32*)(p + 0x90) = f;
        }
        if (flags & 0x40) {
            *(s32*)(p + 0x60) = func_00137D10(a1);
            *(s32*)(p + 0x64) = func_00137D10(a1);
        }
        if (flags & 0x80) {
            *(s32*)(p + 0xA0) = func_00137B90(a1);
        }
    }
}

s32 func_00128230(C05 *self) {
    T2195 *p = self->f1EC;
    if (p != 0 && p->mode0 == 5) {
        return 1;
    }
    p = self->f1F0;
    if (p != 0) {
        if (p->mode1 == 5) {
            return 1;
        }
    }
    return 0;
}

typedef u64 Quad_129FB0 __attribute__((mode(TI)));
struct Frame_129FB0 { Quad_129FB0 r; Quad_129FB0 a; Quad_129FB0 b; };
extern u8 D_00260E90[];

void func_00118CF0(Quad_129FB0* out, void* src);
void func_00118D10(Quad_129FB0* out, void* src);
Quad_129FB0 func_00118D30(Quad_129FB0 a, Quad_129FB0 b);
Quad_129FB0 func_00118D20(Quad_129FB0* out, Quad_129FB0 v);
void func_0012A028(C02* self, Quad_129FB0* src);

void func_00129FB0(C02* self, void* src)
{
    Frame_129FB0 f;
    u8* p = D_00260E90;
    func_00118CF0(&f.a, src);
    Quad_129FB0 av = f.a;
    func_00118D10(&f.b, p);
    (void)func_00118D20(&f.r, func_00118D30(av, f.b));
    func_0012A028(self, &f.r);
}

typedef u64 Quad_12A080 __attribute__((mode(TI)));
struct Frame_12A080 { Quad_12A080 r; Quad_12A080 a; Quad_12A080 b; };
extern u8 D_00260EA0[];

void func_00118CF0(Quad_12A080* out, void* src);
void func_00118D10(Quad_12A080* out, void* src);
Quad_12A080 func_00118D30(Quad_12A080 a, Quad_12A080 b);
Quad_12A080 func_00118D20(Quad_12A080* out, Quad_12A080 v);
void func_0012A0F8(C02* self, Quad_12A080* src);

void func_0012A080(C02* self, void* src)
{
    Frame_12A080 f;
    u8* p = D_00260EA0;
    func_00118CF0(&f.a, src);
    Quad_12A080 av = f.a;
    func_00118D10(&f.b, p);
    (void)func_00118D20(&f.r, func_00118D30(av, f.b));
    func_0012A0F8(self, &f.r);
}

extern u8 D_00219560[];

void func_001299E0(C02* self, void* src);

void func_001296E0(C02* self)
{
    if (self->f1FC == 0) {
        void* v = func_00121228(self->world, self, D_00219560);
        self->f1FC = v;
        func_001299E0(self, v);
    }
}

extern u8 D_0021A790[];

void func_001299E0(C02* self, void* src);

void func_00129730(C02* self)
{
    if (self->f200 == 0) {
        void* v = func_00121228(self->world, self, D_0021A790);
        self->f200 = v;
        func_001299E0(self, v);
    }
}

extern const Fn_2197C0 D_002197C0[10];

void* func_00129CA8(C02* node)
{
    while (node != 0) {
        T2195* a = node->f1EC;
        if (a != 0 && a->vt == (const T2195_Vt*)D_002197C0) {
            return ((T2195_7C0*)a)->player;
        }
        a = node->f1F0;
        if (a != 0 && a->vt == (const T2195_Vt*)D_002197C0) {
            return ((T2195_7C0*)a)->player;
        }
        node = (C02*)node->parent;
    }
    return 0;
}

struct Node_129D00 { u8 pad0[0x14]; void* w14; };

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_002195D8[];
void func_001299E0(C02* self, Node_129D00* n);

void func_00129D00(C02* self, void* v, Node_129D00** out)
{
    Node_129D00* n;

    if (self != 0) {
        n = (Node_129D00*)func_00121228(self->world, self, ((u8*)D_002195D8));
        n->w14 = v;
        func_001299E0(self, n);
        *out = n;
    }
}


void func_001853F0(void* a, void* b, void* c);

extern u8 D_00248D30[];

void func_0012A860(C02* self, void* b)
{
    func_001853F0(self->f200, b, D_00248D30);
}

extern const Fn_Table D_00219600[];

struct Inner_0012A8D8 {
    u8 pad0[0x11];
    u8 f11;
    u8 pad1[0x1C - 0x12];
    f32 f1C;
    f32 f20;
};

void func_001299E0(C02* self, Inner_0012A8D8* src);

void func_0012A8D8(C02* self, s32 a1, f32 x, f32 y)
{
    if (self->f204 == 0) {
        Inner_0012A8D8* r = (Inner_0012A8D8*)func_00121228(self->world, self, ((u8*)D_00219600));
        self->f204 = r;
        func_001299E0(self, r);
    }
    ((Inner_0012A8D8*)self->f204)->f11 = a1;
    ((Inner_0012A8D8*)self->f204)->f1C = x;
    ((Inner_0012A8D8*)self->f204)->f20 = y;
    self->desc02()->m2B(self);
}

struct __attribute__((aligned(16))) Quad_12B180 { s32 a, b, c, d; };

extern u8 D_00248D30[];

void func_0012B180(C02* self, Quad_12B180* out)
{
    u8* src = self->f288 ? (u8*)self->f288 + 0x10 : D_00248D30;
    *out = *(Quad_12B180*)src;
}

struct __attribute__((aligned(16))) Quad_12B1E0 { s32 a, b, c, d; };

extern u8 D_00248D30[];

void func_0012B1E0(C02* self, Quad_12B1E0* out)
{
    u8* src = self->f288 ? (u8*)self->f288 + 0x20 : D_00248D30;
    *out = *(Quad_12B1E0*)src;
}

void func_001F5C0C(void** p, s32 v, s32 n);
void func_00129DF8(C02* self);
void func_001226D8(T2195* n);

void func_00129780(C02* self)
{
    T2195* s3 = 0;
    T2195* s2 = 0;
    T2195* s1 = 0;
    s32 i;
    if (self->f1F8) func_001F5C0C(self->f1F8, 0, self->f26C << 2);
    for (T2195* n = (T2195*)self->list1E0.head; n != 0; n = n->link.next) {
        if (s1 == 0) if (n->mode0 != -1) s1 = n;
        if (s2 == 0) if (n->mode1 != -1) s2 = n;
        if (s3 == 0) if (n->mode2 != -1) s3 = n;
        if (n->mode3 == -1) continue;
        if (n->vt == (const T2195_Vt*)D_002197C0) {
            Track83* e = &((T2195_7C0*)n)->player->anim->tracks[((T2195_7C0*)n)->index];
            for (i = 0; i < e->morphCount; i++) {
                if (e->morph[i] != 0) {
                    if (self->f1F8[i] == 0) self->f1F8[i] = n;
                }
            }
        } else {
            for (i = 0; i < self->f26C; i++) {
                if (self->f1F8[i] == 0) self->f1F8[i] = n;
            }
        }
    }
    if (s1 && s1->mode0 == 0) s1 = 0;
    if (s2 && s2->mode1 == 0) s2 = 0;
    if (s3 && s3->mode2 == 0) s3 = 0;
    if (self->f1F8) {
        for (i = 0; i < self->f26C; i++) {
            if (self->f1F8[i] != 0) {
                if (((T2195*)self->f1F8[i])->mode3 == 0) self->f1F8[i] = 0;
            }
        }
    }
    self->f1F4 = s3;
    if (s1 != self->f1EC || s2 != self->f1F0) {
        func_00129DF8(self);
        if (s1 != self->f1EC) {
            self->f1EC = s1;
            if (s1) func_001226D8(s1);
        }
        if (s2 != self->f1F0) {
            self->f1F0 = s2;
            if (s2) func_001226D8(s2);
        }
    }
}

struct Rd_12BC38;
struct Rec_12BC38 { f32 t; s32 kind; s32 w8; s32 wC; };
struct Sub_12BC38 { s32 w0; s32 w4; s32 w8; s32 wC; s32 w10; };
struct Ev_12BC38 {
    s16 h0, h2;
    u8 pad4[0xA];
    s16 hE, h10;
    u8 pad12[2];
    s32 w14, w18;
    f32 f1C, f20, f24;
};
struct Grp_12BC38 { s16 n; s16 h[1]; };

s32 func_00137CC0(Rd_12BC38* r);
void* func_0018D5C0(s32 n);
void func_00138550(Rd_12BC38* r, void* out);
s32 func_00137D10(Rd_12BC38* r);
s32 func_00137D78(Rd_12BC38* r);
f32 func_00137DF8(Rd_12BC38* r);
s32 func_00137B90(Rd_12BC38* r);
s32 func_00137BE0(Rd_12BC38* r);
void func_00137A60(Rd_12BC38* r, s32 n, void* dst);
void func_001384A0(Rd_12BC38* r, void* out);
void* func_0018D500(s32 n);

#define F32(x) (*(f32*)&(x))
#define H0(x) (*(s16*)&(x))
#define H2(x) (*((s16*)&(x) + 1))

void func_0012BC38(void* unused, Rd_12BC38* r, s32 flag, s32* count, Rec_12BC38** out)
{
    Rec_12BC38* e;
    s32 i;
    s32 merged;
    *count = func_00137CC0(r);
    *out = (Rec_12BC38*)func_0018D5C0(*count * 16);
    for (i = 0; i < *count; i++) {
        e = &(*out)[i];
        e->kind = func_00137CC0(r);
        if (flag) e->t = (f32)func_00137D10(r) * 0.016666668f;
        switch (e->kind) {
        case 44:
        case 51:
            func_00138550(r, &e->w8);
            break;
        case 0: {
            Ev_12BC38 t;
            Grp_12BC38* g;
            s32 j;
            s32 k;
            Rec_12BC38* q;
            merged = 0;
            t.h2 = func_00137D10(r);
            t.h10 = func_00137D10(r);
            t.w14 = func_00137D78(r);
            t.w18 = func_00137D78(r);
            t.f24 = func_00137DF8(r);
            t.f1C = func_00137DF8(r);
            t.f20 = func_00137DF8(r);
            t.h0 = 1;
            t.hE = 0;
            k = i - 1;
            do {
                j = k;
                goto test;
            ins:
                g->h[g->n++] = t.h2;
                goto done;
            } while (0);
        test:
            q = &(*out)[j];
            if (q->t != e->t) goto done;
            if (j < 0) goto done;
            if (q->kind != 0) {
                j--;
                goto test;
            }
            *count = *count - 1;
            i = k;
            merged = 1;
            g = (Grp_12BC38*)q->w8;
            if (g->n < 6) goto ins;
        done:
            if (!merged) {
                e->w8 = (s32)func_0018D500(0x28);
                *(Ev_12BC38*)e->w8 = t;
            }
            break;
        }
        case 4:
        case 7:
            F32(e->w8) = (f32)func_00137D10(r) * 0.016666668f;
            F32(e->wC) = func_00137DF8(r);
            break;
        case 19:
        case 20:
            e->w8 = func_00137D10(r);
            e->wC = func_00137B90(r);
            break;
        case 16:
            e->w8 = func_00137D10(r);
            H0(e->wC) = func_00137CC0(r);
            H2(e->wC) = func_00137CC0(r);
            break;
        case 21:
        case 23:
            e->w8 = (s32)func_0018D5C0(0xC);
            ((Sub_12BC38*)e->w8)->w0 = func_00137D10(r);
            F32(((Sub_12BC38*)e->w8)->w4) = func_00137DF8(r);
            F32(((Sub_12BC38*)e->w8)->w8) = func_00137DF8(r);
            break;
        case 25:
        case 26:
            H0(e->w8) = func_00137D10(r);
            e->wC = (s32)func_0018D5C0(0x14);
            ((Sub_12BC38*)e->wC)->w0 = 1;
            ((Sub_12BC38*)e->wC)->w8 = func_00137D10(r);
            ((Sub_12BC38*)e->wC)->wC = -1;
            ((Sub_12BC38*)e->wC)->w10 = 0;
            ((Sub_12BC38*)e->wC)->w4 = (s32)func_0018D5C0(0x20);
            func_00137A60(r, 0x20, (void*)((Sub_12BC38*)e->wC)->w4);
            break;
        case 27:
            e->w8 = func_00137B90(r);
            e->wC = func_00137D10(r);
            break;
        case 28:
            e->w8 = (s32)func_0018D5C0(0x10);
            ((Sub_12BC38*)e->w8)->w0 = func_00137D10(r);
            ((Sub_12BC38*)e->w8)->w4 = func_00137D10(r);
            F32(((Sub_12BC38*)e->w8)->w8) = func_00137DF8(r);
            F32(((Sub_12BC38*)e->w8)->wC) = func_00137DF8(r);
            break;
        case 37:
            H0(e->w8) = func_00137D10(r);
            H2(e->w8) = func_00137D10(r);
            break;
        case 6: case 12: case 13: case 17: case 18: case 22: case 24:
        case 29: case 30: case 31: case 32: case 35: case 36: case 39:
        case 41: case 59:
            e->w8 = func_00137D10(r);
            break;
        case 40:
            e->w8 = func_00137BE0(r);
            break;
        case 38:
        case 45:
        case 47:
            e->w8 = func_00137D10(r);
            e->wC = func_00137D10(r);
            break;
        case 48:
            e->w8 = (s32)func_0018D5C0(0x10);
            ((Sub_12BC38*)e->w8)->w0 = func_00137D10(r);
            ((Sub_12BC38*)e->w8)->w4 = func_00137D10(r);
            ((Sub_12BC38*)e->w8)->w8 = func_00137D10(r);
            F32(((Sub_12BC38*)e->w8)->wC) = func_00137DF8(r);
            break;
        case 9:
        case 10:
            e->w8 = func_00137D10(r);
            F32(e->wC) = func_00137DF8(r);
            break;
        case 46:
        case 52:
            H0(e->w8) = func_00137D10(r);
            H2(e->w8) = func_00137D10(r);
            H0(e->wC) = func_00137D10(r);
            break;
        case 54:
            H0(e->w8) = func_00137D10(r);
            H2(e->w8) = func_00137D10(r);
            func_001384A0(r, &e->wC);
            break;
        case 5:
        case 33:
        case 57:
        case 58:
            F32(e->w8) = func_00137DF8(r);
            break;
        }
    }
}

struct Entry_12B2F8 { s32 key; s32 val; };
struct St_12B2F8 {
    u8 pad0[0x13]; s8 f13; u8 pad14[0x24]; void* f38; s32 f3C;
    s32 Set(s32 v) { s32 o = f13; f13 = v; return o != v; }
};
extern const Fn_Table D_002195B0[];

void func_0012B2F8(C02* self, s32 key)
{
    s32 callVt = 0;
    s32 i;
    St_12B2F8* st;

    if (key == -1) {
        st = (St_12B2F8*)self->f2C0;
        if (st != 0) {
            callVt = st->Set(-1);
        }
    } else {
        for (i = 0; i < self->f2B8; i++) {
            if (((Entry_12B2F8*)self->f2BC)[i].key == key) {
                break;
            }
        }
        if (i < self->f2B8) {
            if (self->f2C0 == 0) {
                self->f2C0 = (St_12B2F8*)func_00121228(self->world, self, ((u8*)D_002195B0));
                func_001299E0(self, self->f2C0);
            }
            callVt = ((St_12B2F8*)self->f2C0)->Set(3);
            ((St_12B2F8*)self->f2C0)->f38 = (u8*)self + 0x26C;
            ((St_12B2F8*)self->f2C0)->f3C = ((Entry_12B2F8*)self->f2BC)[i].val;
        }
    }
    if (callVt != 0) {
        self->desc02()->m2B(self);
    }
}

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_001212D8();
void func_00121358();
void func_00122890();
void func_00122920();
void func_00122968();
void func_001229C0();
void func_001229E0();
void func_00122A00();
void func_00122A18();
void func_00122A80();
void func_00122B30();
void func_00122C48();
void func_00122CB0();
void func_00122D90();
void func_0011EF40();
void func_0011EF48();
void func_0011EF60();
void func_0011EF68();
void func_0011EF70();
void func_0011EF88();
void func_0011EF90();
void func_0011EFA8();
void func_0011EFB0();
void func_001214B8();
void func_00121568();
void func_00121580();
void func_001215A8();
void func_00122DA0();
void func_00122DE0();
extern const Fn_Table D_002195B0[10] = { (Fn_Table)func_00122890, (Fn_Table)func_001212D8, (Fn_Table)func_00121358, 0, (Fn_Table)func_00122920, (Fn_Table)func_00122968, (Fn_Table)func_001229C0, (Fn_Table)func_001229E0, (Fn_Table)func_00122A00, 0 };
extern const Fn_Table D_002195D8[10] = { (Fn_Table)func_00122A18, (Fn_Table)func_001212D8, (Fn_Table)func_00121358, 0, (Fn_Table)func_00122A80, (Fn_Table)func_00122B30, (Fn_Table)func_00122C48, (Fn_Table)func_00122CB0, (Fn_Table)func_00122D90, 0 };
extern const Fn_Table D_00219600[26] = { (Fn_Table)func_00122DA0, (Fn_Table)func_001212D8, (Fn_Table)func_00121358, 0, (Fn_Table)func_001214B8, (Fn_Table)func_00122DE0, (Fn_Table)func_00121568, (Fn_Table)func_00121580, (Fn_Table)func_001215A8, 0, (Fn_Table)func_0011EF40, 0, (Fn_Table)func_0011EF48, 0, (Fn_Table)func_0011EF60, (Fn_Table)func_0011EF68, 0, (Fn_Table)func_0011EF70, (Fn_Table)func_0011EF88, 0, (Fn_Table)func_0011EF90, 0, (Fn_Table)func_0011EFA8, 0, (Fn_Table)func_0011EFB0, 0 };

struct Context_001288F0;
struct List_001288F0 { u8* head; u8 pad4[4]; s32 offset; };
struct Iter_001288F0 { List_001288F0* list; u8* link; s32 offset; Iter_001288F0* saved; };
s32 func_001C1A28(Context_001288F0* context, C02** obj);

struct Next_001288F0 {
    static C02* Of(Iter_001288F0* it)
    {
        C02* obj = *(C02**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_001288F0 {
    static void Of(Iter_001288F0* it, List_001288F0* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_001288F0*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

s32 func_001288F0(C02* self, Context_001288F0* context)
{
    Iter_001288F0 it;
    Begin_001288F0::Of(&it, (List_001288F0*)&self->children);
    C02* obj;
    for (obj = Next_001288F0::Of(&it); obj != 0; obj = Next_001288F0::Of(&it)) {
        if (func_001C1A28(context, &obj) == 0) {
            D_0027B314 = (ListFrame*)it.saved;
            return 0;
        }
    }
    D_0027B314 = (ListFrame*)it.saved;
    return 1;
}

struct Node_129A58 { u8 pad0[8]; Node_129A58* next; u8 padC[8]; s32 key; };

void func_00152600(List01* list, Node_129A58* node);
void func_00152540(List01* list, Node_129A58* at, Node_129A58* node);

struct Begin_129A58 {
    static void Of(Iter_001288F0* it, List01* list)
    {
        it->list = (List_001288F0*)list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_001288F0*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

struct Next_129A58 {
    static Node_129A58* Of(Iter_001288F0* it)
    {
        Node_129A58* node = *(Node_129A58**)it->link;
        it->link = (u8*)node + it->offset;
        return node;
    }
};

void func_00129A58(C02* self)
{
    Iter_001288F0 it;
    Node_129A58* nodes[20];
    s32 n = 0;
    Node_129A58* node;
    Begin_129A58::Of(&it, &self->list1E0);
    for (node = Next_129A58::Of(&it); node != 0; node = Next_129A58::Of(&it)) {
        nodes[n] = node;
        func_00152600(&self->list1E0, node);
        n++;
    }
    while (--n >= 0) {
        Node_129A58* c = (Node_129A58*)self->list1E0.head;
        node = nodes[n];
        while (c != 0 && c->key > node->key) c = c->next;
        func_00152540(&self->list1E0, c, node);
    }
    self->desc02()->m2B(self);
    D_0027B314 = (ListFrame*)it.saved;
}

Entry_12B0B0 D_00260F00[4] = {
    { { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x42F00000, 0x433E0000, 0x42E60000, 0x00000000, 0x42F00000, 0x433E0000, 0x42700000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } },
    { { 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x437F0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } },
    { { 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x42F00000, 0x437F0000, 0x437F0000, 0x00000000, 0x42F00000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } },
    { { 0x00000003, 0x00000000, 0x00000000, 0x00000000, 0x43700000, 0x437F0000, 0x437F0000, 0x00000000, 0x43700000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } }
};

Entry_12B0B0 D_00261000[2] = {
    { { 0x00000004, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x437F0000, 0x437F0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } },
    { { 0x00000005, 0x00000000, 0x00000000, 0x00000000, 0x43960000, 0x437F0000, 0x437F0000, 0x00000000, 0x43960000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } }
};

void func_00121338();
void func_00122F88();
void func_00122F28();
void func_00122FE0();
void func_00123120();
void func_00123270();
void func_001232E8();
void func_00123358();
extern const Fn_2197C0 D_002197C0[10] = {
    func_00121338, func_00122F88, func_00122F28, 0, func_00122FE0,
    func_00123120, func_00123270, func_001232E8, func_00123358, 0
};

extern u8 D_00148D64[];
void func_00123ED0(void* self);

void func_0012B6B8(C6B* self)
{
    u32 c;
    func_00123ED0(self);
    self->start = 0x100018;
    self->end = D_00148D64;
    self->crc = 0xFFFFFFFF;
    for (s32 i = 0; i < 256; i++) {
        c = (u32)i;
        s32 k = 7;
        do {
            if (c & 1) {
                c = (c >> 1) ^ 0xEDB88320;
            } else {
                c >>= 1;
            }
        } while (--k >= 0);
        self->table[i] = c;
    }
}
