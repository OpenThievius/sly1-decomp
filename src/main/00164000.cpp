// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

extern s32 D_00262474;
extern u8 D_002622A8[];

void func_001EE3B8(void* obj, s32 size, s32 flags);

void func_00166658(void)
{
    s32 v = 0x23C - D_00262474;
    D_00262474 = v;
    func_001EE3B8(D_002622A8, v, 0);
}

void func_001CA5E0(void);

void func_00167EF0(void)
{
    func_001CA5E0();
}

extern u32 D_002623E0;
void func_00167D20(void* p, s32 value) { if ((u32)value == 0xFFFFu && p != 0) D_002623E0 = 0x80101010; }

void func_0016C528(void*);
void func_001660A0(u8* self)
{
    u8* p=*(u8**)(self+0x224);
    if (p && (*(s32*)(p+0xB0)&16) && *(s32*)(p+0x64)) func_0016C528(*(void**)(p+0x60));
}

void func_00167D48() { func_00167D20((void*)1, 65535); }

typedef void (*VFn_165728)(void* self);
struct Obj_165728 { VFn_165728* vtbl; };
struct Entry_165728 { u8 pad0[0x38]; Obj_165728* f38; u8 pad1[0x70 - 0x3C]; };
struct Node_165728 { u8 pad0[4]; void* f4; s32 f8; u8 pad1[0x80 - 0xC]; Node_165728* next80; };
struct Self_165728 { u8 pad0[0xC]; s32 count0C; Entry_165728* f10; u8* f14; u8 pad1[0x4C - 0x18]; Node_165728* f4C; };
struct Ctx_165728 { u8 pad0[0x14]; void* host14; };

void* func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_001662A8(void* self, void* entry, void* sub, void* ctx);
void func_001F2798(void* owner, void* unused, void* ctx);

void func_00165728(Self_165728* self, Ctx_165728* ctx)
{
    for (s32 i = 0; i < self->count0C; i++)
    {
        Entry_165728* e = self->f10 + i;
        Obj_165728* o = e->f38;
        if (o != 0)
        {
            o->vtbl[1](o);
        }
        func_001662A8(self, e, self->f14 + i * 0x28, ctx);
    }
    Node_165728* n = self->f4C;
    if (n != 0)
    {
        do
        {
            void* v = func_0015A418(ctx->host14, 0x104, n->f8, ctx);
            if (v != 0)
            {
                func_001F2798(v, ctx, n->f4);
            }
            n = n->next80;
        } while (n != 0);
    }
}

struct __attribute__((aligned(16))) Quad_165828 { s32 a, b, c, d; };
struct Mat_165828 { Quad_165828 q[4]; };
struct Node_165828 { u8 pad0[0x110]; u8 sub110[0x30]; u8 sub140[0x40]; };
struct Elem_165828 { Node_165828* p0; u8 pad0[0xC]; Mat_165828 m; u8 tail[0x90 - 0x50]; };
struct Obj_165828 { s32 count; Elem_165828* elems; s32* keys; };
struct Ctx_165828 { u8 pad0[0x14]; void* p14; u8 pad1[0x110 - 0x18]; u8 sub110[0x30]; u8 sub140[0x40]; };
struct Frame_165828 { Quad_165828 a; u8 pad0[0x30]; Quad_165828 b; u8 pad1[0x30]; Mat_165828 m; };

void* func_0015A448(void* a, s32 b, void* c);
void func_00188B08(void* a, void* b, void* out);
void func_00188B48(void* a, void* b, void* out);
void func_00188668(void* out, void* b, void* in);

void func_00165828(Obj_165828* self, Ctx_165828* ctx)
{
    Frame_165828 f;
    s32 i;

    for (i = 0; i < self->count; i++) {
        Elem_165828* e = &self->elems[i];
        Node_165828* r = (Node_165828*)func_0015A448(ctx->p14, self->keys[i], ctx);
        e->p0 = r;
        if (r != 0) {
            func_00188B08(&ctx->sub140, &ctx->sub110, &f.a);
            func_00188B48(&e->p0->sub140, &e->p0->sub110, &f.b);
            func_00188668(&f.m, &f.b, &f.a);
            e->m = f.m;
        }
    }
}

struct Ctx_167E08 { u8 pad0[0x14]; void* p14; u8 pad1[0x750 - 0x18]; void* p750; u8 pad2[0xC18 - 0x754]; s32 c18; s32 c1c; u8 pad3[0xC30 - 0xC20]; s32 c30; s32 c34; };
struct Ent_167E08 { u8 pad0[0x328]; s32 f328; };
struct Out_167E08 { s32 count; Ent_167E08** items; };

void func_001C72A0(void* self);
void* func_0015A448(void* a, s32 b, void* c);
void func_0018D608(void);
void func_0018D6F0(void);
void func_0012D1B0(void* a, void* b, s32* c, void** d);
void* func_001EFA30(void);
void func_001EFA60(void* a, void* b);

void func_00167E08(Ctx_167E08* self)
{
    Out_167E08 out;
    s32 i;

    func_001C72A0(self);
    if (self->c18 != -1) {
        self->c1c = (s32)func_0015A448(self->p14, self->c18, self);
    }
    if (self->c30 != -1) {
        self->c34 = (s32)func_0015A448(self->p14, self->c30, self);
    }
    if (self->p750 != 0) {
        func_0018D608();
        func_0012D1B0(self->p750, self, &out.count, (void**)&out.items);
        for (i = 0; i < out.count; i++) {
            Ent_167E08* e = out.items[i];
            if (e->f328 == 0) {
                void* t = func_001EFA30();
                e->f328 = (s32)t;
                func_001EFA60(t, e);
            }
        }
        func_0018D6F0();
    }
}

struct Elem_165FE0;
typedef void (*VFn_165FE0)(void* self, f32 f);

struct Elem_165FE0 {
    VFn_165FE0* vtbl;
    u8 pad4[0x8];
    void* f0C;
    u8 pad10[0x70];
    Elem_165FE0* next80;
};

struct Owner_165FE0 {
    u8 pad0[0x4C];
    Elem_165FE0* head4C;
};

struct Sub_165FE0 {
    u8 pad0[0x27C];
    s32 count27C;
    Elem_165FE0** list280;
};

s32 func_001B4B08(void* p);
void func_001F3408(void* p);

void func_00165FE0(Owner_165FE0* self, Sub_165FE0* sub, f32 f)
{
    Elem_165FE0* e;
    s32 i;

    for (i = 0; i < sub->count27C; i++) {
        e = sub->list280[i];
        if (func_001B4B08(e) != 0) {
            VFn_165FE0 fn = e->vtbl[2];
            if (fn != 0) {
                fn(e, f);
            }
        }
    }
    for (e = self->head4C; e != 0; e = e->next80) {
        func_001F3408(e->f0C);
    }
}
