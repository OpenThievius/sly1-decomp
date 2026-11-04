// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "c36.h"
#include "c4e.h"
#include "c7d.h"

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
void func_001F4E18(C4E* self) { func_00123ED0(self); self->id = -1; }

void func_001F57E0(void*);
int func_001F51E8(C36* self) { func_001F57E0(&self->rec); return 1; }

struct Obj_1F7FC0 { u8 pad[0x28]; struct Node* root; };
struct Node { u8 pad0[8]; Node* child; u8 pad1[0x2C]; Node* next; };
void* func_001F7FC0(u32 key, Obj_1F7FC0* obj) { Node* node = obj->root; while (node) { Node* child = node->child; while (child) { if (*(u32*)child == key) return child; child = child->next; } node = *(Node**)((u8*)node + 0x14); } return 0; }

void func_001F5840(Rec36* self, void* entry) { u32 n = self->count; if (n < 32) { self->keys[n] = entry; self->count = n + 1; } }

extern u8 D_0027696C[];
void func_001F66F8(void* value) { void* p = *(void**)D_0027696C; *(void**)((u8*)p + 0x58) = value; }

void func_001F5590(Rec36* a, C36* b) { a->owner = b; a->f04 = 0; a->f08 = 150.0f; }

extern u8 D_00261990[];
void func_00145088(u32, int, void*, int, void*);
void func_001F4F20(void* self) { if (*(s32*)((u8*)self + 0x310)) { func_001451F0(*(u32*)D_00261990, 0xB, 7, (u8*)*(u32*)D_00261990 + 0x510, 0, self); *(s32*)((u8*)self + 0x310) = 0; } }

void* func_001BA130(void*);
void func_001F51A0(C36* self) { func_001BA130(self); self->rec.owner = self; }

void func_0013EC00(void*, int, void*, void*, void*, void*, void*);
void func_001F42D0(void* self, void* a1, void* a2, void* a3, void* a4) { func_0013EC00((u8*)self + 0xB8, 4, (u8*)self + 0xB4, a1, a2, a3, a4); }

extern u32 D_00277134;
void func_00124A48(void*);
void func_001F55A8(Rec36*);
void func_001F4FD8(C36* self) { func_00124A48(self); func_001F55A8(&self->rec); }

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

void func_00124A48(void* self);

void func_001F4660(C7D* self)
{
    func_00124A48(self);
    for (s32 i = 0; i < self->count; i++) {
        C01* e = self->items[i];
        const Desc01* vt = e->desc;
        if (vt->m0F != 0) {
            vt->m0F(e);
        }
        C01* e2 = self->items[i];
        e2->desc->m10(e2);
    }
    if (self->f2D4 != 0) {
        s32* g = (s32*)*(void**)D_002623C8;
        if ((g[0] & 2) == 0) {
            C01* a = self;
            while (a->parent != 0) {
                a = a->parent;
            }
            a->desc->m03(a);
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

void func_00124A48(C4E* self);
C01* func_0015A418(void* host, s32 a1, s32 a2, C4E* ctx);
s32 func_001300E8(C01* n, s32 kind);

void func_001F4E48(C4E* self)
{
    func_00124A48(self);
    if (self->id != -1) {
        C01* c = func_0015A418(self->world, 0x104, self->id, self);
        if (c) {
            if (c->desc->flags & 1) {
                self->found2D8 = c;
            } else if (func_001300E8(c, 0x7E)) {
                self->found2D4 = c;
            }
        }
    }
}

void func_001B7968(C03* self);

void func_001F4F70(C36* self)
{
    func_001B7968(self);
    func_001F5590(&self->rec, self);
    self->f4E0 = 1;
    self->flags538 = (self->flags538 & ~0xF000000000ULL) | 0x2000000000ULL;
}

void func_001B9AE0(C37* o, s32 a, s32 b, s32 c, s32 d);

void func_001F5218(C37* o) {
    func_001F4F70(o);
    o->flags538 |= ((u64)0x8000 << 28);
    func_001B9AE0(o, 3, 0, 3, 0);
}

struct Ev_1F5868;
s32 func_001300E8(Ev_1F5868* e, s32 kind);

void func_001F5868(Rec36* self, Ev_1F5868* e) {
    if (self->found < 0x20) {
        if (func_001300E8(e, 0x7E) || func_001300E8(e, 0x6E) || func_001300E8(e, 0x76) ||
            func_001300E8(e, 0x70) || func_001300E8(e, 0x71) || func_001300E8(e, 0x81)) {
            self->nodes[self->found++] = e;
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

void func_00138550(void* a, void* b);
void func_00137EB0(void* a, void* b);
void func_00137E70(void* a, void* b);
s32 func_001E4C48(void* a, void* b, void* c, void* d, void* e);
void func_0011EC40(void* a, void* b);
s32 func_00137D10(void* a);
void* func_0018D500(s32 size);
void* func_0011E580(s32 a, s32 b, s32 c, s32 d, s32 e);

void func_001F4500(C7D* self, void* s3)
{
    func_00138550(s3, (u8*)self + 0x2FC);
    func_00138550(s3, (u8*)self + 0x308);
    func_00137EB0(s3, &self->rot);
    func_00137E70(s3, &self->pos);
    void (*f)(C01* self) = self->desc->m12;
    if (f != 0) {
        f(self);
    }
    self->f2E4 = 0;
    func_001E4C48(s3, &self->f2EC, &self->f2F0, &self->f2F4, &self->f2F8);
    s32 i = 0;
    func_0011EC40(self, s3);
    s32 n = func_00137D10(s3);
    self->count = n;
    self->items = (C01**)func_0018D500(n * 4);
    while (i < self->count) {
        s32 a = func_00137D10(s3);
        s32 b = func_00137D10(s3);
        s32 c = func_00137D10(s3);
        C01* o = (C01*)func_0011E580(a, (s32)self->world, (s32)self->parent, b, c);
        self->items[i++] = o;
        o->desc->m0A(o, s3);
        o->desc->m03(o);
    }
}


struct Kind_1F55A8 { s32 f0; s32 type; };
struct Node_1F55A8 { Kind_1F55A8* kind; };
struct Iter_1F55A8 { List01* list; u8* link; s32 offset; Iter_1F55A8* saved; };

struct Next_1F55A8 {
    static Node_1F55A8* Of(Iter_1F55A8* it)
    {
        Node_1F55A8* obj = *(Node_1F55A8**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_1F55A8 {
    static void Of(Iter_1F55A8* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_1F55A8*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

Node_1F55A8* func_0015A418(C6C* a, s32 b, void* c, C36* d);
void func_001F5868(Rec36* self, Node_1F55A8* n);

void func_001F55A8(Rec36* self)
{
    Iter_1F55A8 it;
    Node_1F55A8* n;
    s32 i;

    Begin_1F55A8::Of(&it, &self->owner->children);
    while ((n = Next_1F55A8::Of(&it)) != 0) {
        s32 t = n->kind->type;
        if (t == 0x7E || t == 0x6E) {
            if (self->found < 0x20) {
                self->nodes[self->found++] = n;
            }
        }
    }
    for (i = 0; i < self->count; i++) {
        n = func_0015A418(self->owner->world, 0x104, self->keys[i], self->owner);
        if (n != 0) {
            func_001F5868(self, n);
        }
    }
    D_0027B314 = (ListFrame*)it.saved;
}

struct Obj_1F5008 {
    u8 pad0[0x550];
    s32 f550;
};

s32 func_001B93F8(C03* self);
s32 func_00182F40(Obj_1F5008* o, C36* self);
s32 func_001300E8(Obj_1F5008* o, s32 kind);
s32 func_001F5C0C(void* p, s32 a, s32 b);
s32 func_00177838(void* t, s32 a, s32 b);

struct Tmp_1F5008 {
    C36* self;
    Obj_1F5008* obj;
    u8 pad[0x18];
    Vec02 q20;
    Vec02 q30;
};

struct Add_1F5008 {
    static void Of(C36* self, Obj_1F5008* p, Vec02* a, Vec02* b)
    {
        s32 c = self->count;
        if ((u32)c < 10) {
            if (p->f550 != 3) {
                Slot36* s = &self->slots[c];
                self->count = c + 1;
                s->obj = (C03*)p;
                s->q10 = *a;
                s->q20 = *b;
            }
        }
    }
};
void func_001F5008(C36* self) {
    Tmp_1F5008 tmp;
    Obj_1F5008* p;
    func_001B93F8(self);
    self->count = 0;
    C03* owner = self->root03();
    for (ContactRow03* g = owner->contacts->head; g; g = g->next) {
        for (Contact03* it = g->head; it; it = it->next) {
            s32 side = (owner != it->end[0].body);
            Obj_1F5008* near = (Obj_1F5008*)it->end[side].part;
            if (func_00182F40(near, self)) {
                ContactEnd03* far = &it->end[1 - side];
                Obj_1F5008* o = (Obj_1F5008*)far->part;
                if (func_001300E8(o, 0x41)) {
                    p = o; Add_1F5008::Of(self, p, &far->v10, &it->v80);
                }
            }
        }
    }
    func_001F5C0C(&tmp, 0, 0x40);
    for (s32 i = 0; i < self->count; i++) {
        Slot36* s = &self->slots[i];
        p = (Obj_1F5008*)s->obj;
        tmp.self = self;
        tmp.obj = p;
        tmp.q20 = *(Vec02*)((u8*)p + 0x140);
        tmp.q30 = *(Vec02*)((u8*)p + 0x150);
        func_00177838(&tmp, 0, 0);
    }
}

struct Item_1F4808 { u8 pad[0x34]; f32 f34; };
struct Obj_1F4808 {
    u8 pad0[0x2D4];
    s32 f2D4;
    s32 f2D8;
    u8 pad2DC[4];
    s32 f2E0;
    u8 pad2E4[0x2FC - 0x2E4];
    s32 f2FC;
    u8 pad300[0x310 - 0x300];
    s32 f310;
    Item_1F4808** f314;
    s32 f318;
    f32 f31C;
    u8 pad320[4];
    f32 f324;
};
struct Glob_1F4808 { u8 pad[0x19DC]; s32 f19DC; };

struct Gl_1F4808 { u8 pad[0x260]; s32 f260; };
extern Gl_1F4808 D_0026E9F8;

s32 func_001601A0(s32 a);
void func_001E0828(Gl_1F4808* g);
void func_001F4760(Obj_1F4808* self, s32 state);
void func_001E02C8(Gl_1F4808* g, s32 n);
void func_001F4408(s32 flag, s32 n);
s32 func_001300E8(Item_1F4808* key, s32 kind);
void func_001451F0(u8* a0, s32 a1, s32 a2, u8* a3, s32 a4, s32 a5);
void func_0012C7B0(Item_1F4808* self, s32 a1, s32 a2, s32* out, f32 fa, f32 fb);
s32 func_0012C9A8(Item_1F4808* node);
void func_001837E0(Obj_1F4808* self, s32 a, s32 b, s32 c);

void func_001F4808(Obj_1F4808* self)
{
    Item_1F4808* key;
    s32 i;
    s32 found = 0;
    s32 next;
    Item_1F4808* it;

    key = (struct Item_1F4808 *)func_001925F0();
    if (D_0026E9F8.f260 == 2
        && (self->f2E0 != 0 || self->f2D4 != 0
            || ((*(Glob_1F4808**)&D_002623C0)->f19DC == 0 && (u8)func_001601A0(self->f2FC) == 1))) {
        func_001E0828(&D_0026E9F8);
        func_001F4760(self, 2);
        goto tail;
    }
    if (D_0026E9F8.f260 >= 2) {
        func_001E02C8(&D_0026E9F8, 4);
    }
    if (self->f2D8 != 0) {
        func_001F4408(1, self->f318);
        func_001F4760(self, 0);
        return;
    }
    if (key == 0 || func_001300E8(key, 0x16) == 0) {
        func_001451F0((*(u8**)&D_00261990), 2, 0, (*(u8**)&D_00261990) + 0x460, 0, 0);
    }
    func_001F4760(self, 5);
    for (i = 0; i < self->f310; i++) {
        it = self->f314[i];
        func_0012C7B0(it, 0, 0, 0, 0.0f, 1.0f);
        next = 0;
        if (found != 0 || func_0012C9A8(it) != 0) {
            next = 1;
        }
        found = next;
    }
    if (found == 0) {
        if (self->f324 > 0.0f) {
            self->f31C = ((f32*)&D_0026185C)[0] + self->f324;
        } else if (self->f310 > 0) {
            self->f31C = ((f32*)&D_0026185C)[0] + self->f314[0]->f34;
        } else {
            self->f31C = ((f32*)&D_0026185C)[0];
        }
    }
tail:
    func_001837E0(self, 2, 0, 0);
}
