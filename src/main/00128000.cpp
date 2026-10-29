// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Owned { u8 pad[0x14]; void* owner; };

extern u8 D_002197C0[];
void func_00121228(void* owner, void* item, void* table);

void func_00128998(Owned* item)
{
    func_00121228(item->owner, item, D_002197C0);
}

void func_0012A4A0(void* self, s32 a1);

void func_0012A478(void* self, s32 a1)
{
    func_0012A4A0(self, a1 != 0 ? 1 : -1);
}

void func_00129730(void* self);

struct Sub_12A580 { u8 pad[0x40]; f32 f40; };
struct Obj_12A580 { void* vtbl; u8 pad[0x200 - 4]; Sub_12A580* p200; };

void func_0012A580(Obj_12A580* self, f32 f)
{
    func_00129730(self);
    self->p200->f40 = f;
}

struct Sub_12A5B8 { u8 pad[0x40]; f32 f40; };
struct Obj_12A5B8 { void* vtbl; u8 pad[0x200 - 4]; Sub_12A5B8* p200; };

void func_0012A5B8(Obj_12A5B8* self, f32* out)
{
    f32 r = 0.0f;
    if (self->p200 != 0) r = self->p200->f40;
    *out = r;
}

void func_00129730(void* self);

struct Vec16_12A5D0 { s32 v[4]; } __attribute__((aligned(16)));
struct Sub_12A5D0 { u8 pad[0x50]; Vec16_12A5D0 v50; };
struct Obj_12A5D0 { void* vtbl; u8 pad[0x200 - 4]; Sub_12A5D0* p200; };

void func_0012A5D0(Obj_12A5D0* self, Vec16_12A5D0* src)
{
    func_00129730(self);
    self->p200->v50 = *src;
}

extern u8 D_00275C40[];

struct Vec16_12A610 { s32 v[4]; } __attribute__((aligned(16)));
struct Sub_12A610 { u8 pad[0x50]; Vec16_12A610 v50; };
struct Obj_12A610 { void* vtbl; u8 pad[0x200 - 4]; Sub_12A610* p200; };

void func_0012A610(Obj_12A610* self, Vec16_12A610* out)
{
    Vec16_12A610* src = self->p200 != 0 ? (Vec16_12A610*)((u8*)self->p200 + 0x50) : (Vec16_12A610*)D_00275C40;
    *out = *src;
}

void func_00129730(void* self);

struct __attribute__((packed)) U64_12A630 { u64 v; };
struct Sub_12A630 { u8 pad[0x60]; U64_12A630 v60; };
struct Obj_12A630 { void* vtbl; u8 pad[0x200 - 4]; Sub_12A630* p200; };

void func_0012A630(Obj_12A630* self, U64_12A630* src)
{
    func_00129730(self);
    self->p200->v60 = *src;
}

extern u8 D_00275C60[];

struct __attribute__((packed)) U64_12A678 { u64 v; };
struct Sub_12A678 { u8 pad[0x60]; U64_12A678 v60; };
struct Obj_12A678 { void* vtbl; u8 pad[0x200 - 4]; Sub_12A678* p200; };

void func_0012A678(Obj_12A678* self, U64_12A678* out)
{
    U64_12A678* src = self->p200 != 0 ? (U64_12A678*)((u8*)self->p200 + 0x60) : (U64_12A678*)D_00275C60;
    *out = *src;
}

void func_00129730(void* self);

struct Vec16_12A6A0 { s32 v[4]; } __attribute__((aligned(16)));
struct Sub_12A6A0 { u8 pad[0x70]; Vec16_12A6A0 v70; };
struct Obj_12A6A0 { void* vtbl; u8 pad[0x200 - 4]; Sub_12A6A0* p200; };

void func_0012A6A0(Obj_12A6A0* self, Vec16_12A6A0* src)
{
    func_00129730(self);
    self->p200->v70 = *src;
}

extern u8 D_00275C40[];

struct Vec16_12A6E0 { s32 v[4]; } __attribute__((aligned(16)));
struct Sub_12A6E0 { u8 pad[0x70]; Vec16_12A6E0 v70; };
struct Obj_12A6E0 { void* vtbl; u8 pad[0x200 - 4]; Sub_12A6E0* p200; };

void func_0012A6E0(Obj_12A6E0* self, Vec16_12A6E0* out)
{
    Vec16_12A6E0* src = self->p200 != 0 ? (Vec16_12A6E0*)((u8*)self->p200 + 0x70) : (Vec16_12A6E0*)D_00275C40;
    *out = *src;
}

typedef void (*VFn_128278)(void* self, s32 arg);

struct Vtbl_128278 {
    u8 pad0[0x8];
    VFn_128278 f8;
};

struct Elem_128278 {
    Vtbl_128278* vt;
    u8 pad1[0x10 - 4];
    s8 b10;
    s8 b11;
};

struct Obj_128278 {
    u8 pad0[0x1EC];
    Elem_128278* f1EC;
    Elem_128278* f1F0;
};

void func_00128278(Obj_128278* self)
{
    Elem_128278* a = self->f1EC;
    if (a != 0 && a->b10 == 5) {
        do {
            a->vt->f8(a, 0);
            a = self->f1EC;
        } while (a != 0 && a->b10 == 5);
    }
    Elem_128278* b = self->f1F0;
    if (b != 0 && b->b11 == 5) {
        do {
            b->vt->f8(b, 0);
            b = self->f1F0;
        } while (b != 0 && b->b11 == 5);
    }
}

struct Obj_1291A0 {
    u8 pad0[0x290];
    f32 f290;
};

void func_001291A0(Obj_1291A0* self, f32 x)
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

struct Obj_129400 { u8 pad[0x284]; void* p284; };

void* func_00129400(Obj_129400* self)
{
    if (self->p284 != 0) return self->p284;
    func_001B1AC8(D_0027B520);
    return D_0027B520;
}

struct Obj_129510 { u8 pad[0x284]; void* p284; };
struct Sub_129510 { u8 pad[0x44]; f32 f44; };

void* func_00129400(Obj_129510* self);

void func_00129510(Obj_129510* self, f32* out)
{
    *out = ((Sub_129510*)func_00129400(self))->f44;
}

extern u8 D_00260E80[];
void* func_0018D500(s32 n);

struct __attribute__((aligned(16))) Quad_129F58 { s32 v[4]; };
struct Obj_129F58 { u8 pad[0x210]; Quad_129F58* p210; };

void func_00129F58(Obj_129F58* self, Quad_129F58* src)
{
    if (self->p210 == (Quad_129F58*)D_00260E80) self->p210 = (Quad_129F58*)func_0018D500(16);
    *self->p210 = *src;
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
struct Obj_12A770 { void* vtbl; u8 pad[0x200 - 4]; Sub_12A770* p200; };

void func_0012A770(Obj_12A770* self, void* v)
{
    func_00129730(self);
    self->p200->f44 = v;
}

void* func_00185468(void* p);

struct Obj_12A888 { u8 pad[0x200]; void* p200; };

void func_0012A888(Obj_12A888* self, void** out)
{
    *out = func_00185468(self->p200);
}

struct Ctx_12AA28 { u8 pad[0x90]; void* field; };

Ctx_12AA28* func_0012A970(void* self);

void func_0012AA28(void* self, void* value)
{
    Ctx_12AA28* ctx = func_0012A970(self);
    ctx->field = value;
}

struct Inner_12AC88 { s32 value; };
struct Outer_12AC88 { u8 pad[0x2AC]; Inner_12AC88* inner; };

void func_0012AC88(Outer_12AC88* self, s32* out)
{
    s32 v = -1;
    if (self->inner != 0) v = self->inner->value;
    *out = v;
}

struct Inner_12AD98 { u8 pad[0xC]; f32 value; };
struct Outer_12AD98 { u8 pad[0x2AC]; Inner_12AD98* inner; };

void func_0012ABA8(void* self, f32 f);

void func_0012AD98(Outer_12AD98* self, f32 f)
{
    func_0012ABA8(self, f);
    self->inner->value = f;
}

struct Inner_12AEB0 { u8 pad[0x1C]; void* ptr; };
struct Outer_12AEB0 { u8 pad[0x2AC]; Inner_12AEB0* inner; };

void func_001BF7F8(void* p);

void func_0012AEB0(Outer_12AEB0* self)
{
    Inner_12AEB0* in = self->inner;
    if (in != 0) {
        if (in->ptr != 0) func_001BF7F8(in->ptr);
    }
}

struct Entry_12B0B0 { s32 w[16]; } __attribute__((aligned(16)));
struct Outer_12B0B0 { u8 pad[0x288]; Entry_12B0B0* slot; };

extern Entry_12B0B0 D_00260F00[];

void func_0012B040(void* self);

void func_0012B0B0(Outer_12B0B0* self, s32 a1)
{
    func_0012B040(self);
    self->slot->w[0] = a1;
    Entry_12B0B0* e = self->slot;
    s32 k = e->w[0];
    if (k != -1) *e = D_00260F00[k];
}

struct Obj_12B250 { u8 pad[0x2B0]; u8 a; u8 b; u8 c; };

void func_0012B250(Obj_12B250* self, s32 v)
{
    self->c = v;
    self->b = v;
    self->a = v;
}

struct Obj_12B2A0 { u8 pad[0x2B2]; u8 c; };

void func_0012B2A0(Obj_12B2A0* self, s32 v)
{
    self->c = v;
}

struct Obj_12B2E8 { u8 pad[0xC]; u32 value; };

s32 func_0012B2E8(void* a0, Obj_12B2E8* a1)
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
struct Ent_128DB8 { u8 pad0[0x14]; void* p14; u8 pad18[0x224 - 0x18]; Part_128DB8* p224; };

Node_128DB8* func_0015A448(void* a0, void* a1, void* a2);
void* func_0015A868(void* a0, s32 a1);

void func_00128DB8(Ent_128DB8* self)
{
    Part_128DB8* p = self->p224;
    if (p == 0) return;
    s32 v = p->flags | 0x8000;
    p->flags = v;
    if (v & 0x10) {
        p->p60 = func_0015A448(self->p14, p->p60, self);
        p->p64 = (Node_128DB8*)1;
    }
    if (p->flags & 0x20) {
        Node_128DB8* r = func_0015A448(self->p14, p->p84, self);
        p->p84 = r;
        s32 x = r->f18;
        p->f80 = x;
        p->p88 = func_0015A868(self, x);
    }
    if (p->flags & 0x40) {
        p->p60 = func_0015A448(self->p14, p->p60, self);
        p->p64 = func_0015A448(self->p14, p->p64, self);
    }
}

struct Timer_129108 { u8 pad0[4]; s32 f4; s32 f8; s32 fC; f32 f10; };
struct Ent_129108 { u8 pad[0x2A0]; Timer_129108* p2A0; };

void* func_0018D5C0(s32 size);

Timer_129108* func_00129108(Ent_129108* self)
{
    if (self->p2A0 == 0) {
        Timer_129108* t = (Timer_129108*)func_0018D5C0(0x14);
        self->p2A0 = t;
        t->f4 = -1;
        self->p2A0->f8 = 0;
        self->p2A0->fC = 0;
        self->p2A0->f10 = 1.0f;
    }
    return self->p2A0;
}

struct Ent_129170 { u8 pad[0x28C]; f32 f28C; };

void func_00129170(Ent_129170* self, f32 x)
{
    self->f28C = x * 0.01f;
}

struct Ent_129188 { u8 pad[0x28C]; f32 f28C; };

void func_00129188(Ent_129188* self, f32* out)
{
    *out = self->f28C * 100.0f;
}

struct Ent_1291B8 { u8 pad[0x290]; f32 f290; };

void func_001291B8(Ent_1291B8* self, f32* out)
{
    *out = self->f290 * 100.0f;
}

struct Ent_1291D0 { u8 pad0[0x14]; u8* p14; u8 pad18[0x284 - 0x18]; void* p284; };

void* func_001B5EE0(void* a0);
void func_001B1AC8(void* a0);
void func_00152470(void* a0, void* a1);

void* func_001291D0(Ent_1291D0* self)
{
    if (self->p284 == 0) {
        void* o = func_001B5EE0(self->p14 + 0x1BF4);
        self->p284 = o;
        func_001B1AC8(o);
        func_00152470(self->p14 + 0x1C00, self->p284);
    }
    return self->p284;
}

struct Sub_12A7F8 { u8 pad0[0x48]; s32 f48; };
struct Owner_12A7F8 { u8 pad0[0x200]; Sub_12A7F8* sub; };

void func_0012A7F8(Owner_12A7F8* self, s32* out)
{
    s32 v = 0;
    if (self->sub != 0) {
        v = self->sub->f48;
    }
    *out = v;
}

struct Sub_12A810 { u8 pad0[0x20]; s32 f20; };
struct Owner_12A810 { u8 pad0[0x200]; Sub_12A810* sub; };

void func_00129730(Owner_12A810* self);

void func_0012A810(Owner_12A810* self, s32 value)
{
    func_00129730(self);
    self->sub->f20 = value;
}

struct Sub_12A848 { u8 pad0[0x20]; s32 f20; };
struct Owner_12A848 { u8 pad0[0x200]; Sub_12A848* sub; };

void func_0012A848(Owner_12A848* self, s32* out)
{
    s32 v = -1;
    if (self->sub != 0) {
        v = self->sub->f20;
    }
    *out = v;
}

struct Sub_12A8B8 { u8 pad0[0x4C]; s32 f4C; };
struct Owner_12A8B8 { u8 pad0[0x200]; Sub_12A8B8* sub; };

void func_0012A8B8(Owner_12A8B8* self)
{
    self->sub->f4C = 0;
}

struct Sub_12A8C8 { u8 pad0[0x4C]; s32 f4C; };
struct Owner_12A8C8 { u8 pad0[0x200]; Sub_12A8C8* sub; };

void func_0012A8C8(Owner_12A8C8* self)
{
    self->sub->f4C = 1;
}

struct Obj_12A970 { u8 pad0[0x14]; s32 f14; };

void* func_0015A418(s32 a0, s32 a1, s32 a2, void* a3);
void* func_0011E580(s32 a0, s32 a1, void* a2, s32 a3, s32 a4);

void* func_0012A970(Obj_12A970* self)
{
    void* r = func_0015A418(self->f14, 0x102, 0x22A, self);
    if (r != 0) {
        return r;
    }
    return func_0011E580(0x75, self->f14, self, 0x22A, -1);
}

struct Obj_12A9C8 { u8 pad0[0x88]; s32 f88; };

void* func_0012A970(Obj_12A9C8* self);

void func_0012A9C8(Obj_12A9C8* self, s32 value)
{
    Obj_12A9C8* o = (Obj_12A9C8*)func_0012A970(self);
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
struct Obj_12A028 { u8 pad[0x214]; Quad_12A028* p214; };

extern u8 D_00260E90[];
void* func_0018D500(s32 n);

void func_0012A028(Obj_12A028* self, Quad_12A028* src)
{
    if (self->p214 == (Quad_12A028*)D_00260E90) self->p214 = (Quad_12A028*)func_0018D500(16);
    *self->p214 = *src;
}

struct __attribute__((aligned(16))) Quad_12A0F8 { s32 w[4]; };
struct Obj_12A0F8 { u8 pad[0x218]; Quad_12A0F8* p218; };

extern u8 D_00260EA0[];
void* func_0018D500(s32 n);

void func_0012A0F8(Obj_12A0F8* self, Quad_12A0F8* src)
{
    if (self->p218 == (Quad_12A0F8*)D_00260EA0) self->p218 = (Quad_12A0F8*)func_0018D500(16);
    *self->p218 = *src;
}

struct Sub_12ACD8 { u8 pad0[4]; f32 value; };
struct Owner_12ACD8 { u8 pad[0x2AC]; Sub_12ACD8* sub; };

void func_0012ACD8(Owner_12ACD8* self, f32* out)
{
    Sub_12ACD8* s = self->sub;
    f32 v = 3000.0f;
    if (s != 0) v = s->value;
    *out = v;
}

struct Sub_12ACF8 { u8 pad0[8]; f32 value; };
struct Owner_12ACF8 { u8 pad[0x2AC]; Sub_12ACF8* sub; };

void func_0012ABA8(Owner_12ACF8* self);

void func_0012ACF8(Owner_12ACF8* self, f32 value)
{
    func_0012ABA8(self);
    self->sub->value = value;
}

struct __attribute__((packed)) Rec_12AD30 { s32 a; s32 b; };
struct Sub_12AD30 { u8 pad0[0x14]; Rec_12AD30 rec; };
struct Owner_12AD30 { u8 pad[0x2AC]; Sub_12AD30* sub; };

void func_0012ABA8(Owner_12AD30* self);

void func_0012AD30(Owner_12AD30* self, Rec_12AD30* src)
{
    func_0012ABA8(self);
    self->sub->rec = *src;
}

struct Sub_12AD78 { u8 pad0[8]; f32 value; };
struct Owner_12AD78 { u8 pad[0x2AC]; Sub_12AD78* sub; };

void func_0012AD78(Owner_12AD78* self, f32* out)
{
    Sub_12AD78* s = self->sub;
    f32 v = 300.0f;
    if (s != 0) v = s->value;
    *out = v;
}

struct Flags_0012B2C0 { u8 pad[0x2B3]; u8 value; };

void func_0012B2C0(Flags_0012B2C0* self, s32* out)
{
    *out = self->value;
}

struct Flags_0012B2D0 { u8 pad[0x2B4]; u8 value; };

void func_0012B2D0(Flags_0012B2D0* self, u8 v)
{
    self->value = v;
}

struct Flags_0012B2D8 { u8 pad[0x2B4]; u8 value; };

void func_0012B2D8(Flags_0012B2D8* self, s32* out)
{
    *out = self->value;
}

struct Bits_0012B420 { u8 pad[0x2C8]; u64 bits; };

extern s32 D_00261990;
s32 func_00182FC8(Bits_0012B420* self);
void func_00143AF8(s32 a, Bits_0012B420* self);
void func_00143B20(s32 a, Bits_0012B420* self);

void func_0012B420(Bits_0012B420* self, s32 flag)
{
    u64 want = flag != 0;
    if (want != (((self->bits >> 36) ^ 1) & 1)) {
        return;
    }
    u64 bit = (u64)(flag & 1) << 36;
    self->bits = (self->bits & 0xFFFFFFEFFFFFFFFFULL) | bit;
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
struct Holder_12A150 { u8 pad[0x21C]; Vec4_12A150* cur; };
extern Vec4F_12A150 D_00260EB0;

void func_0012A200(Holder_12A150* self, Vec4_12A150* src);

void func_0012A150(Holder_12A150* self, f32 scale)
{
    Vec4F_12A150 tmp;
    tmp.x = D_00260EB0.x * scale;
    tmp.y = D_00260EB0.y * scale;
    tmp.z = D_00260EB0.z;
    tmp.w = D_00260EB0.w * scale;
    func_0012A200(self, (Vec4_12A150*)&tmp);
}



void func_0012A1A0(Holder_12A150* self, f32 scale)
{
    Vec4_12A150 tmp = *self->cur;
    tmp.w = scale * (tmp.x - tmp.y) / tmp.z;
    func_0012A200(self, &tmp);
}

void* func_0018D500(s32 size);

void func_0012A200(Holder_12A150* self, Vec4_12A150* src)
{
    if (self->cur == (Vec4_12A150*)&D_00260EB0) {
        self->cur = (Vec4_12A150*)func_0018D500(16);
    }
    *self->cur = *src;
}

struct Part_0012AC08 { void* link; f32 f4; f32 f8; f32 fc; f32 f10; u8 sub14[8]; u8 sub1C[4]; f32 f20; };
struct Host_0012AC08 { u8 pad[0x2AC]; Part_0012AC08* part; };

void func_0012ABA8(Host_0012AC08* self);

void func_0012ACA0(Host_0012AC08* self, f32 value)
{
    func_0012ABA8(self);
    self->part->f4 = value;
}



void func_0012ADD0(Host_0012AC08* self, f32 value)
{
    func_0012ABA8(self);
    self->part->f20 = value;
}


void func_0012AE08(Host_0012AC08* self, f32* out)
{
    f32 r = 0.0f;
    if (self->part != 0) {
        r = self->part->f20;
    }
    *out = r;
}

typedef void (*CtrlVFn_12B4C8)(void* self);
struct Ctrl_12B290 { CtrlVFn_12B4C8* vtbl; u8 pad_04[0x14]; s32 f18; u8 pad_1C[0x294 - 0x1C]; s32 f294; u8 pad_298[0x2B1 - 0x298]; u8 b2B1; u8 b2B2; u8 b2B3; };

void func_0012B290(Ctrl_12B290* self, s32* out)
{
    *out = self->b2B1;
}


void func_0012B2A8(Ctrl_12B290* self, s32* out)
{
    *out = self->b2B2;
}


void func_0012B2B8(Ctrl_12B290* self, s32 value)
{
    self->b2B3 = value;
}


s32 func_00182FC8(void* self);

void func_0012B4C8(Ctrl_12B290* self, s32 flag)
{
    if ((0 < (u32)flag) != (self->f294 == 0)) {
        goto done;
    }
    if (func_00182FC8(self) == 0) {
        goto store;
    }
    if (self->f18 != 0) {
        goto store;
    }
    self->vtbl[7](self);
    self->f294 = flag;
    self->vtbl[6](self);
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

struct Flag_129440 { u8 pad[0x284]; s32 count; };

void func_00129440(Flag_129440* self, s32* out)
{
    *out = self->count != 0;
}

struct __attribute__((packed)) Pack4_12A2C0 { f32 a, b, c, d; };
struct Obj_12A2C0 { u8 pad[0x220]; Pack4_12A2C0* data; };

extern void func_0012A320(Obj_12A2C0* self, Pack4_12A2C0* in);

void func_0012A2C0(Obj_12A2C0* self, f32 scale)
{
    Pack4_12A2C0 tmp;
    tmp = *self->data;
    tmp.d = scale * (tmp.a - tmp.b) / tmp.c;
    func_0012A320(self, &tmp);
}

struct __attribute__((packed)) Pack4_12A320 { f32 a, b, c, d; };
struct Obj_12A320 { u8 pad[0x220]; Pack4_12A320* data; };

void* func_0018D500(u32 size);

void func_0012A320(Obj_12A320* self, Pack4_12A320* src)
{
    if (self->data == (Pack4_12A320*)D_00260EC0) {
        self->data = (Pack4_12A320*)func_0018D500(0x10);
    }
    *self->data = *src;
}

struct Part_12AE20 { u8 pad0[0xC]; f32 weight; u8 pad1[0xC]; void* ptr; };
struct Owner_12AE20 { u8 pad[0x2AC]; Part_12AE20* part; };

void func_001BF8E8(void* p);

void func_0012AE20(Owner_12AE20* self)
{
    Part_12AE20* part = self->part;
    if (part != 0) {
        void* p = part->ptr;
        if (p != 0) {
            func_001BF8E8(p);
        }
    }
}

struct Part_12AE58 { u8 pad0[0xC]; f32 weight; u8 pad1[0xC]; void* ptr; };
struct Owner_12AE58 { u8 pad[0x2AC]; Part_12AE58* part; };

void func_0012AE58(Owner_12AE58* self, f32* out)
{
    f32 v = 1.0f;
    if (self->part != 0) {
        v = self->part->weight;
    }
    *out = v;
}

struct Ctx_12B550 { u8 pad[0x2C8]; u64 flags; };

void func_0012B550(Ctx_12B550* ctx, s32 on)
{
    if (on != 0) {
        ctx->flags |= (u64)1 << 32;
    } else {
        ctx->flags &= ~((u64)1 << 32);
    }
}

struct Ctx_12B590 { u8 pad[0x2C8]; u64 flags; };

void func_0012B590(Ctx_12B590* ctx, s32* out)
{
    if ((ctx->flags & ((u64)1 << 32)) != 0) {
        *out = 1;
    } else {
        *out = 0;
    }
}

struct Ctx_129450 {
    u8 pad[0x284];
    void* link_284;
};

struct Node_129450 {
    u8 pad[2];
    s16 value_2;
};

void func_00129450(Ctx_129450* self, s32* out)
{
    void* p = self->link_284;
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

struct Owner_129C20 {
    u8 pad0[0x1B94];
    Node_129C20* f1B94;
};

struct Obj_129C20 {
    u8 pad0[0x14];
    Owner_129C20* f14;
};

s32 func_001833F0(void* key, s32 item);

Node_129C20* func_00129C20(Obj_129C20* self, s32 key)
{
    s32 scratch[4];
    Node_129C20* n = self->f14->f1B94;
    while (n != 0) {
        if (n->f1C == self) {
            if (key == -1) return n;
            if (func_001833F0(n->f18, key) != 0) return n;
        }
        n = n->f10;
    }
    (void)scratch;
    return 0;
}

struct Vt_129D70 {
    u8 pad0[8];
    s32 f8;
};

struct Obj_129D70 {
    Vt_129D70* f0;
    u8 pad1[0x1C - 4];
    Obj_129D70* f1C;
    u8 pad2[0x34 - 0x20];
    Obj_129D70* f34;
    u8 pad3[0x150 - 0x38];
};

s32 func_00123DC0(void* a);
s32 func_00123E00(void* a);

s32 func_00129D70(Obj_129D70* self)
{
    Obj_129D70* n;
    if (func_00123DC0((u8*)self + 0x150) == 0) return 0;
    if (func_00123E00((u8*)self + 0x160) != 0) goto body;
    return 0;
body:
    n = self->f34;
    while (n != 0) {
        if ((n->f0->f8 & 1) != 0) {
            if (func_00129D70(n) == 0) return 0;
        }
        n = n->f1C;
    }
    return 1;
}

void func_00129730(void* self);

struct __attribute__((packed)) U64_12A700 { u64 v; };
struct Sub_12A700 { u8 pad[0x80]; U64_12A700 v80; };
struct Obj_12A700 { void* vtbl; u8 pad[0x200 - 4]; Sub_12A700* p200; };

void func_0012A700(Obj_12A700* self, U64_12A700* src)
{
    func_00129730(self);
    self->p200->v80 = *src;
}

struct Part_12AE78 { u8 pad[0x10]; f32 value; };
struct Owner_12AE78 { u8 pad[0x2AC]; Part_12AE78* part; };

void func_0012ABA8(void* self, f32 f);

void func_0012AE78(Owner_12AE78* self, f32 f)
{
    func_0012ABA8(self, f);
    self->part->value = f;
}

struct Part_12AEE8 { u8 pad[0x10]; f32 value; };
struct Owner_12AEE8 { u8 pad[0x2AC]; Part_12AEE8* part; };

void func_0012AEE8(Owner_12AEE8* self, f32* out)
{
    f32 r = 0.0f;
    if (self->part != 0) {
        r = self->part->value;
    }
    *out = r;
}

struct Inner_0012B238 { u8 pad[0x30]; f32 value; };
struct Obj_0012B238 { u8 pad[0x288]; Inner_0012B238* inner; };

void func_0012B238(Obj_0012B238* self, f32* out)
{
    f32 v = 0.0f;
    Inner_0012B238* p = self->inner;
    if (p != 0) v = p->value;
    *out = v;
}

struct Obj_0012B260 { u8 pad[0x2B0]; u8 a; };

void func_0012B260(Obj_0012B260* self, s32* out)
{
    *out = self->a;
}
