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
