// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

void func_001451F0(u32, int, int, void*, int, void*);
void func_00125C90();
struct Obj_1F4308 { u8 pad[0x98]; s32 state; f32 value; };
void func_001F4308(Obj_1F4308* self, f32 value) { self->value = value; self->state = 1; }

void func_001F51C8() { func_00125C90(); }

void* func_001F5208(void* self) { return (u8*)self + 0x550; }

struct Obj_1F5210 { u8 pad[0x5E4]; s32 value; };
void func_001F5210(Obj_1F5210* self) { self->value = 0; }

struct Obj_1F7E58 { u8 pad[0x10]; u32 flags; u8 pad2[4]; s32 field_18; };
void func_001F7E58(Obj_1F7E58* self) { self->field_18 = 0; self->flags &= ~1u; }

void func_00123ED0(void*);
struct Obj_1F4E18 { u8 pad[0x2D0]; s32 value; };
void func_001F4E18(Obj_1F4E18* self) { func_00123ED0(self); self->value = -1; }

void func_001F57E0(void*);
int func_001F51E8(void* self) { func_001F57E0((u8*)self + 0x550); return 1; }

struct Obj_1F7FC0 { u8 pad[0x28]; struct Node* root; };
struct Node { u8 pad0[8]; Node* child; u8 pad1[0x2C]; Node* next; };
void* func_001F7FC0(u32 key, Obj_1F7FC0* obj) { Node* node = obj->root; while (node) { Node* child = node->child; while (child) { if (*(u32*)child == key) return child; child = child->next; } node = *(Node**)((u8*)node + 0x14); } return 0; }

struct Obj_1F5840 { u8 pad[0x10]; s32 count; void* entries[8]; };
void func_001F5840(Obj_1F5840* self, void* entry) { u32 n = self->count; if (n < 32) { self->entries[n] = entry; self->count = n + 1; } }

extern u8 D_0027696C[];
void func_001F66F8(void* value) { void* p = *(void**)D_0027696C; *(void**)((u8*)p + 0x58) = value; }

void func_001F5590(void* a, void* b) { *(void**)a = b; *(u32*)((u8*)a + 4) = 0; *(f32*)((u8*)a + 8) = 150.0f; }

extern u8 D_00261990[];
void func_00145088(u32, int, void*, int, void*);
void func_001F4F20(void* self) { if (*(s32*)((u8*)self + 0x310)) { func_001451F0(*(u32*)D_00261990, 0xB, 7, (u8*)*(u32*)D_00261990 + 0x510, 0, self); *(s32*)((u8*)self + 0x310) = 0; } }

struct Obj_1F51A0 { u8 pad[0x550]; void* field; };
void* func_001BA130(void*);
void func_001F51A0(Obj_1F51A0* self) { func_001BA130(self); self->field = self; }

void func_0013EC00(void*, int, void*, void*, void*, void*, void*);
void func_001F42D0(void* self, void* a1, void* a2, void* a3, void* a4) { func_0013EC00((u8*)self + 0xB8, 4, (u8*)self + 0xB4, a1, a2, a3, a4); }

extern u32 D_00277134;
void func_00124A48(void*);
void func_001F55A8(void*);
void func_001F4FD8(void* self) { func_00124A48(self); func_001F55A8((u8*)self + 0x550); }

void func_001FA468();
void func_001F4ED0(void* self) { if (!*(s32*)((u8*)self + 0x310)) { func_00145088(*(u32*)D_00261990, 7, (u8*)*(u32*)D_00261990 + 0x510, 0, self); *(s32*)((u8*)self + 0x310) = 1; } }

s32 func_001F3C38(void* a, void* b);
s32 func_001F4008(void* x);
s32 func_001925F0(void);
s32 func_00192620(void);
s32 func_001929D0(void* v);

s32 func_001F4318(void* unused, void* a, void* b)
{
    s32 r = func_001F3C38(a, b);
    if (r != 0) {
        r = func_001F4008((void*)r);
        goto done;
    }
    r = func_001925F0();
    if (r == 0) {
        r = func_00192620();
        if (r != 0) {
            r = func_001929D0((void*)r);
        }
    }
done:
    return r;
}

// NEAR: only the vtbl[19] load differs: retail loads it into $v1 (lw v1,76(v1)), we use $v0 for the test and the call.

extern u8 D_002623C8[];

typedef void (*Fn_1F4660)(void* self);

struct Node_1F4660 {
    Fn_1F4660* vtbl;
    u8 pad04[0x14];
    Node_1F4660* next;
    u8 pad1C[0x2D4 - 0x1C];
    void* f2D4;
    u8 pad2D8[0x310 - 0x2D8];
    s32 count;
    Node_1F4660** items;
};

void func_00124A48(void* self);

void func_001F4660(Node_1F4660* self)
{
    func_00124A48(self);
    for (s32 i = 0; i < self->count; i++) {
        Node_1F4660* e = self->items[i];
        Fn_1F4660* vt = e->vtbl;
        if (vt[19] != 0) {
            vt[19](e);
        }
        Node_1F4660* e2 = self->items[i];
        e2->vtbl[20](e2);
    }
    if (self->f2D4 != 0) {
        s32* g = (s32*)*(void**)D_002623C8;
        if ((g[0] & 2) == 0) {
            Node_1F4660* a = self;
            while (a->next != 0) {
                a = a->next;
            }
            a->vtbl[7](a);
        }
    }
}

struct Vt_1F4760 { s32 pad[15]; void (*fn)(void* self); };
struct Glob_1F4760 { Vt_1F4760* vt; };
struct Obj_1F4760 { u8 pad[0x14]; void* f14; u8 pad2[0x2C8 - 0x18]; u64 f2C8; u8 pad3[0x2E4 - 0x2D0]; s32 f2E4; f32 f2E8; };
extern Glob_1F4760 D_0026F138;
extern f32 D_0026185C;
void func_001DDA20(void* a);

void func_001F4760(Obj_1F4760* self, s32 state)
{
    if (state != self->f2E4) {
        if (self->f2E4 == 4 && state != 5)
            D_0026F138.vt->fn(&D_0026F138);
        if (state == 5) {
            self->f2C8 = (self->f2C8 & ~0x30000000000ULL) | 0x10000000000ULL;
            func_001DDA20(self->f14);
            self->f2E4 = state;
        } else {
            self->f2E4 = state;
        }
        self->f2E8 = D_0026185C;
    }
}

struct Args_1F4A30 { s32 a; s32 b; s32 c; s32 d; s32 e; };
struct Obj_1F4A30 { u8 pad[0x2FC]; s32 f2FC; s32 f300; s32 f304; s32 f308; s32 f30C; u8 pad2[0x318 - 0x310]; s32 f318; };
struct Glob_1F4A30 { s32 flags; };
extern u8 D_00275F80[];
s32 func_001601A0(s32 a0);
s32 func_00160850(s32 a0);
void func_001EFFA0(u8* dst, Args_1F4A30* args, s32 count);

void func_001F4A30(Obj_1F4A30* self)
{
    Args_1F4A30 m;
    s32 ok = 0;
    m.a = 1;
    switch (self->f304) {
    case 0: ok = func_00160850(func_001601A0(self->f2FC)) >> 1; goto fin;
    case 1: ok = ((Glob_1F4A30*)*(void**)D_002623C8)->flags >> 1;
    fin: ok &= 1;
    }
    if (ok) {
        m.b = self->f308;
        m.c = self->f30C;
    } else {
        m.b = self->f2FC;
        m.c = self->f300;
    }
    m.d = -1;
    m.e = 0;
    func_001EFFA0(D_00275F80, &m, self->f318);
}

struct Vt_1F4E48 { s32 pad[2]; s32 flags; };
struct Ch_1F4E48 { Vt_1F4E48* vt; };
struct Obj_1F4E48 { u8 pad[0x14]; void* host; u8 pad2[0x2D0 - 0x18]; s32 f2D0; Ch_1F4E48* f2D4; Ch_1F4E48* f2D8; };
void func_00124A48(Obj_1F4E48* self);
Ch_1F4E48* func_0015A418(void* host, s32 a1, s32 a2, Obj_1F4E48* ctx);
s32 func_001300E8(Ch_1F4E48* n, s32 kind);

void func_001F4E48(Obj_1F4E48* self)
{
    func_00124A48(self);
    if (self->f2D0 != -1) {
        Ch_1F4E48* c = func_0015A418(self->host, 0x104, self->f2D0, self);
        if (c) {
            if (c->vt->flags & 1) {
                self->f2D8 = c;
            } else if (func_001300E8(c, 0x7E)) {
                self->f2D4 = c;
            }
        }
    }
}

struct Obj_1F4F70 { u8 pad[0x4E0]; s32 f4E0; u8 pad2[0x538 - 0x4E4]; u64 f538; };
void func_001B7968(Obj_1F4F70* self);
void func_001F5590(void* a, Obj_1F4F70* b);

void func_001F4F70(Obj_1F4F70* self)
{
    func_001B7968(self);
    func_001F5590((u8*)self + 0x550, self);
    self->f4E0 = 1;
    self->f538 = (self->f538 & ~0xF000000000ULL) | 0x2000000000ULL;
}

struct Obj_1F5218 {
    u8 pad[0x538];
    u64 flags;
};
void func_001F4F70(Obj_1F5218* o);
void func_001B9AE0(Obj_1F5218* o, s32 a, s32 b, s32 c, s32 d);

void func_001F5218(Obj_1F5218* o) {
    func_001F4F70(o);
    o->flags |= ((u64)0x8000 << 28);
    func_001B9AE0(o, 3, 0, 3, 0);
}

struct List_1F5868 {
    u8 pad[0x94];
    u32 count;
    void* items[1];
};
struct Ev_1F5868;
s32 func_001300E8(Ev_1F5868* e, s32 kind);

void func_001F5868(List_1F5868* self, Ev_1F5868* e) {
    if (self->count < 0x20) {
        if (func_001300E8(e, 0x7E) || func_001300E8(e, 0x6E) || func_001300E8(e, 0x76) ||
            func_001300E8(e, 0x70) || func_001300E8(e, 0x71) || func_001300E8(e, 0x81)) {
            self->items[self->count++] = e;
        }
    }
}

struct Obj_1F4378 { u8 pad[0x2D0]; s32 f2D0; };

extern void* D_00275710;

s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);

Obj_1F4378* func_001F4378(void)
{
    void* arr[64];
    Obj_1F4378* found = 0;
    s32 n = func_0015A4F0(D_00275710, 0x205, 0x7D, 0, 0x100, arr);
    s32 cap = 0x40;
    s32 lim = 0x3F;
    n = (lim < n) ? cap : n;
    for (s32 i = 0; i < n; i++) {
        Obj_1F4378* o = (Obj_1F4378*)arr[i];
        if (o->f2D0 != 0) {
            found = o;
            break;
        }
    }
    return found;
}

struct Self_57E0 { void* f0; s32 f4; };
struct Out_57E0 { s32 f0; s32 f4; Self_57E0* f8; void* fC; };

void func_001837E0(void* self, s32 a, s32 b, s32 c);
void func_001F56D8(void);

void func_001F57E0(Self_57E0* self, void* a1, Out_57E0* out)
{
    func_001925F0();
    s32 v = self->f4;
    out->f8 = self;
    out->f0 = v;
    out->fC = (void*)func_001F56D8;
    func_001837E0(self->f0, 2, 0, 0);
}

struct IdList_1F5930 { u8 pad[0x94]; s32 count; s32 items[1]; };
void func_0018D800(void* dst, void* src, s32 count);

void func_001F5930(IdList_1F5930* self, s32 value)
{
    s32 i;
    for (i = 0; i < self->count; i++) {
        if (self->items[i] == value) {
            break;
        }
    }
    if (i < self->count) {
        s32* p = &self->items[i];
        func_0018D800(p, p + 1, (self->count - i - 1) * 4);
        self->count = self->count - 1;
    }
}

extern u8 D_002623C0[];
extern u8 D_002623C4[];
extern u8 D_00247AD0[];
extern u8 D_00275B04[];
extern u8 D_00275F80[];

struct Ctx_1F4408 {
    u8 pad00[0x19D8];
    s32 f19D8;
    s32 f19DC;
};

struct Obj_1F4408 {
    u8 pad00[0x78];
    s32 f78;
    u8 pad7C[0x310 - 0x7C];
    s32 f310;
};

struct Val_1F4408 { s32 unused; };
struct Key_1F4408 { s32 unused; };
struct Dst_1F4408 { s32 unused; };
struct Args_1F4408 {
    s32 f00;
    void* f04;
    s32 f08;
    s32 f0C;
    s32 f10;
};

Val_1F4408* func_00160180(Key_1F4408* k);
void func_001F0428(Val_1F4408* v, s32 m, s32 n);
void func_001F4808(Obj_1F4408* x);
void func_001EFFA0(Dst_1F4408* dst, Args_1F4408* args, s32 count);

void func_001F4408(s32 flag, s32 n)
{
    Ctx_1F4408* ctx = *(Ctx_1F4408**)D_002623C0;
    Obj_1F4408* o;
    Obj_1F4408* v;
    Val_1F4408* k;
    Args_1F4408 args;
    if (ctx->f19D8 == 5) {
        goto lm1;
    }
    if (ctx->f19DC != 0) {
        goto l4490;
    }
    o = *(Obj_1F4408**)D_002623C4;
    if ((o->f78 & 1) != 0) {
        goto l4470;
    }
lm1:
    func_001F0428((Val_1F4408*)D_00247AD0, -1, n);
    return;
l4470:
    k = func_00160180((Key_1F4408*)(u32)((ctx->f19D8 << 8) | 1));
    func_001F0428(k, 0x1BD, n);
    return;
l4490:
    v = (Obj_1F4408*)func_001F4378();
    if (v == 0) {
        goto larg;
    }
    if (flag != 0) {
        v->f310 = 0;
    }
    func_001F4808(v);
    return;
larg:
    args.f00 = 1;
    args.f04 = D_00275B04;
    args.f08 = -1;
    args.f0C = -1;
    args.f10 = 0;
    func_001EFFA0((Dst_1F4408*)D_00275F80, &args, n);
}

struct Obj_1F56D8;
struct Ctx_1F56D8;
struct Tab_1F56D8;
typedef void (*VFn_1F56D8)(Obj_1F56D8* self, void* a);

struct Obj_1F56D8 {
    VFn_1F56D8* vtbl;   // 0x00
    u8 pad04[0x634];
    f32 f638;           // 0x638
};
struct Ctx_1F56D8 {
    u8 pad00[0x0C];
    s32 cnt;            // 0x0C
    u8 pad10[0x84];
    s32 s94;            // 0x94
};
struct Frame_1F56D8 {
    s32 a[4];           // 0x00
    u8 pad10[0x10];
    s32 b[4];           // 0x20
    s32 c[4];           // 0x30
    u8 pad40[0x20];
    f32 f60;            // 0x60
};

extern u8 D_00248D20[];
extern u8 D_00248D30[];

void func_00178D98(Obj_1F56D8* self, s32 a1, void* a2, void* a3, void* a4);
void func_001782C0(Obj_1F56D8* self, void* s2, f32 f, void* a2, void* a3, void* a4);
void func_00188850(Tab_1F56D8* t, void* out, f32 x);
void func_00175170(Obj_1F56D8* self, s32 a, s32 b);
void func_00178598(Obj_1F56D8* self, void* s2, f32 f);

void func_001F56D8(Ctx_1F56D8* ctx, Obj_1F56D8* self)
{
    Frame_1F56D8 f;
    func_00178D98(self, ctx->s94, (u8*)ctx + 0x98, f.a, &f.f60);
    if (ctx->cnt != 0) {
        func_001782C0(self, f.a, 0.0f, 0, f.b, 0);
        self->vtbl[33](self, f.b);
        self->vtbl[36](self, D_00248D30);
        self->vtbl[37](self, D_00248D30);
        func_00188850((Tab_1F56D8*)D_00248D20, f.c, self->f638);
        self->vtbl[34](self, f.c);
        func_00175170(self, 2, 2);
    } else {
        func_00178598(self, f.a, f.f60);
    }
}

typedef void (*Fn_1F4500)(void* self);
typedef void (*Fn2_1F4500)(void* self, void* s3);

struct Obj_1F4500 {
    Fn_1F4500* vtbl;
    Fn2_1F4500* vtbl2() { return (Fn2_1F4500*)vtbl; }
    u8 pad04[0x10];
    s32 f14;
    s32 f18;
    u8 pad1C[0x2E4 - 0x1C];
    s32 f2E4;
    u8 pad2E8[0x310 - 0x2E8];
    s32 count;
    Obj_1F4500** items;
};

void func_00138550(void* a, void* b);
void func_00137EB0(void* a, void* b);
void func_00137E70(void* a, void* b);
s32 func_001E4C48(void* a, void* b, void* c, void* d, void* e);
void func_0011EC40(void* a, void* b);
s32 func_00137D10(void* a);
void* func_0018D500(s32 size);
void* func_0011E580(s32 a, s32 b, s32 c, s32 d, s32 e);

void func_001F4500(void* self_, void* s3)
{
    Obj_1F4500* self = (Obj_1F4500*)self_;
    func_00138550(s3, (u8*)self + 0x2FC);
    func_00138550(s3, (u8*)self + 0x308);
    func_00137EB0(s3, (u8*)self + 0xD0);
    func_00137E70(s3, (u8*)self + 0x100);
    Fn_1F4500 f = self->vtbl[22];
    if (f != 0) {
        f(self);
    }
    self->f2E4 = 0;
    func_001E4C48(s3, (u8*)self + 0x2EC, (u8*)self + 0x2F0, (u8*)self + 0x2F4, (u8*)self + 0x2F8);
    s32 i = 0;
    func_0011EC40(self, s3);
    s32 n = func_00137D10(s3);
    self->count = n;
    self->items = (Obj_1F4500**)func_0018D500(n * 4);
    while (i < self->count) {
        s32 a = func_00137D10(s3);
        s32 b = func_00137D10(s3);
        s32 c = func_00137D10(s3);
        Obj_1F4500* o = (Obj_1F4500*)func_0011E580(a, self->f14, self->f18, b, c);
        self->items[i++] = o;
        o->vtbl2()[14](o, s3);
        o->vtbl[7](o);
    }
}
