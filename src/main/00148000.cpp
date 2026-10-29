// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Glob_1481A0 {
    u8 pad0[0x19D8];
    s32 f19D8;
    s32 f19DC;
    s32 f19E0;
    s32 f19E4;
    s32 f19E8;
};
typedef Glob_1481A0 Glob_148178;

extern Glob_148178* D_002623C0;

void func_00148178(void)
{
    Glob_148178* g = D_002623C0;
    s32 r = 99;
    if (g->f19E0 + 1 <= 98) r = g->f19E0 + 1;
    g->f19E0 = r;
}


struct Self_1481A0 {
    u8 pad0[0x14];
    void* p14;
};

struct Sys_1481A0 {
    u8 pad0[0x26C];
    f32 f26C;
    u8 pad1[0x4];
    void (*fn274)(void);
    void* p278;
};

struct __attribute__((packed)) PSys_1481A0 {
    u8 pad0[0x26C];
    f32 f26C;
};

typedef void (*VFn_1481A0)(void* self);
struct VObj_1481A0 {
    VFn_1481A0* vtbl;
};

extern Glob_1481A0* D_002623C0;
extern u8 D_0026CE48[];
extern u8 D_0026C6C8[];

void func_00148038(void);
void func_00148178(void);
s32 func_00160D98(void);

void func_001481A0(void* self)
{
    Self_1481A0* s = (Self_1481A0*)self;
    Glob_1481A0* g = D_002623C0;
    s32 c = g->f19E8 + 1;
    s32 r;
    g->f19E8 = c;
    if (c >= 100) {
        r = func_00160D98();
        if (g->f19E4 < r) {
            D_002623C0->f19E8 = 0;
            ((PSys_1481A0*)D_0026CE48)->f26C = 250.0f;
            ((Sys_1481A0*)D_0026CE48)->fn274 = func_00148038;
            ((Sys_1481A0*)D_0026CE48)->p278 = s->p14;
            return;
        }
        if (D_002623C0->f19E0 < 99) {
            D_002623C0->f19E8 = 0;
            ((Sys_1481A0*)D_0026CE48)->f26C = 250.0f;
            ((Sys_1481A0*)D_0026CE48)->p278 = 0;
            ((Sys_1481A0*)D_0026CE48)->fn274 = func_00148178;
            {
                VObj_1481A0* obj = (VObj_1481A0*)D_0026C6C8;
                obj->vtbl[14](obj);
            }
        } else {
            D_002623C0->f19E8 = 99;
        }
    }
}

typedef void (*VFn_148CE0)(void* self, s32 arg);

struct Node_148CE0 {
    VFn_148CE0* vtbl;
    u8 pad0[0x374 - 4];
    Node_148CE0* next;
};

struct Self_148CE0 {
    u8 pad0[0x1C54];
    Node_148CE0* first;
};

typedef Glob_1481A0 Glob_148CE0;

extern s32 D_0026EC58;

s32 func_001300E8(void* node, s32 kind);

void func_00148CE0(Self_148CE0* self)
{
    Glob_148CE0* g = D_002623C0;
    if (((g->f19D8 << 8) | g->f19DC) == 0x308) return;
    s32 r = func_00160D98();
    if (g->f19E4 < r) {
        if (D_0026EC58 < 2) return;
    }
    Node_148CE0* p = self->first;
    if (p == 0) return;
    do {
        if (func_001300E8(p, 0x56) != 0) {
            p->vtbl[51](p, 2);
        }
        p = p->next;
    } while (p != 0);
}

typedef void (*VFn_148E18)(void* self, s32 arg);

struct Obj_148E18 {
    VFn_148E18* vtbl;
};

void func_00148E18(Obj_148E18* self)
{
    self->vtbl[51](self, 2);
}

typedef void (*VFn_14ADE0)(void* self);

struct Elem_14ADE0 {
    VFn_14ADE0* vtbl;
    u8 pad004[0x21C - 0x004];
    f32 f21C;
    f32 f220;
    u8 pad224[0x238 - 0x224];
    f32 f238;
    f32 f23C;
    u8 pad240[0x260 - 0x240];
};

struct Obj_14ADE0 {
    VFn_14ADE0* vtbl;
    u8 pad004[0x21C - 0x004];
    f32 f21C;
    f32 f220;
    u8 pad224[0x260 - 0x224];
    s32 count;
    Elem_14ADE0 items[1];
};

extern s32 D_00275BEC;
extern f32 D_00261850;

void func_0014ADE0(Obj_14ADE0* self)
{
    if (D_00275BEC == 1) {
        f32 acc = self->f220;
        s32 i;
        for (i = 0; i < self->count; i++) {
            Elem_14ADE0* e = &self->items[i];
            f32 saved = e->f23C;
            f32 base = self->f21C;
            f32 scaled = saved * D_00261850;
            e->f220 = acc;
            e->f21C = base;
            e->f23C = scaled;
            e->vtbl[9](e);
            e->f23C = saved;
            acc += e->f238;
        }
    }
}

typedef void (*VFn_14AEA0)(void* self, s32 arg);

struct Pair_14AEA0 {
    f32 a;
    f32 b;
};

struct Q_14AEA0 {
    u8 pad000[0x08];
    s32 v08;
    u8 pad00C[0x48 - 0x0C];
    f32 f48;
};

struct Obj_14AEA0 {
    VFn_14AEA0* vtbl;
    Q_14AEA0* q;
    u8 pad008[0x218 - 0x08];
    Pair_14AEA0* pair;
    u8 pad21C[0x234 - 0x21C];
    f32 f234;
    u8 pad238[0x260 - 0x238];
    s32 count;
};

void func_001AAB20(Obj_14AEA0* self, f32 a, f32 b);

void func_0014AEA0(Obj_14AEA0* self, s32 n, f32 x, f32 y)
{
    self->pair->a = x;
    self->pair->b = y;
    self->count = n;
    Q_14AEA0* q = self->q;
    func_001AAB20(self, self->f234, (f32)q->v08 * q->f48 * (f32)n);
    self->vtbl[16](self, 2);
}

typedef void (*VFn_14AF10)(void* self, s32 arg);

struct Obj_14AF10 {
    VFn_14AF10* vtbl;
};

void func_0014AF10(Obj_14AF10* self)
{
    self->vtbl[16](self, 0);
}

struct Stack4_1495E8 { u8 pad[0x30]; s32 items[4]; s32 count; };

void func_001495E8(Stack4_1495E8* s, s32 value)
{
    s32 n = s->count;
    if ((u32)n < 4) {
        s->items[n] = value;
        s->count = n + 1;
    }
}


s32 func_00149610(Stack4_1495E8* s)
{
    s32 n = s->count;
    if (n <= 0) {
        return -1;
    }
    n = n - 1;
    s->count = n;
    return s->items[n];
}


s32 func_00149638(Stack4_1495E8* s)
{
    s32 n = s->count;
    if (n <= 0) {
        return -1;
    }
    return s->items[n - 1];
}

struct Pending_0014BD38 { u8 pad0[0x10]; s32 f10; };
struct Actor_0014BD38 { u8 pad0[0x724]; s32 kind; u8 pad1[0x7E0 - 0x728]; void* handle; u8 pad2[0xC28 - 0x7E4]; Pending_0014BD38* pending; };
struct Ctx_0014BD38 { u8 pad0[0x448]; f32 scale; };
extern Ctx_0014BD38* D_0027C00C;
void func_001C91C8(Actor_0014BD38* self);
void func_0014CDC8(Ctx_0014BD38* ctx, Actor_0014BD38* self);
void func_0012F6B0(void* handle, f32 scale);

void func_0014BD38(Actor_0014BD38* self)
{
    func_001C91C8(self);
    switch (self->kind) {
    case 0xB:
        func_0014CDC8(D_0027C00C, self);
        if (self->pending != 0) { self->pending->f10 = 0; self->pending = 0; }
        break;
    case 0xC:
        if (self->pending != 0) { self->pending->f10 = 0; self->pending = 0; }
        func_0012F6B0(self->handle, D_0027C00C->scale);
        break;
    }
}

typedef void (*VFn_0014BDC8)(void* self, void* arg);

struct Node_0014BDC8 {
    VFn_0014BDC8* vtbl;
    u8 pad0[0xC10 - 4];
    Node_0014BDC8* next;
};

struct Owner_0014BDC8 {
    u8 pad0[0x1CCC];
    Node_0014BDC8* head;
};

struct Obj_0014BDC8 {
    u8 pad0[0x14];
    Owner_0014BDC8* owner;
};

struct Scratch_0014BDC8 {
    s32 words[8];
};

s32 func_001C8010(Obj_0014BDC8* self);
Node_0014BDC8* func_001925F0(void);
s32 func_001B9FB0(void* a, void* b);
void func_001D7098(void* out, s32 mode, Obj_0014BDC8* owner);
void func_001C8F20(void* node, s32 kind, s32 flag);

s32 func_0014BDC8(Obj_0014BDC8* self)
{
    s32 result = func_001C8010(self);
    if (result == 0xB) return result;
    Node_0014BDC8* n = func_001925F0();
    if (n != 0 && func_001B9FB0(self, n) != 0) {
        Scratch_0014BDC8 buf;
        func_001D7098(&buf, 0, self);
        result = 0xB;
        n->vtbl[0x50](n, &buf);
    }
    for (Node_0014BDC8* x = self->owner->head; x != 0; x = x->next) {
        if ((void*)x != (void*)self && func_001300E8(x, 0x12) != 0 && func_001B9FB0(self, x) != 0) {
            func_001C8F20(x, 0xB, 0);
        }
    }
    return result;
}

struct Actor_0014BEA8 {
    u8 pad0[0x14];
    void* owner;
    u8 pad1[0x724 - 0x18];
    s32 kind;
};

s32 func_001DDA80(void* p);

s32 func_0014BEA8(Actor_0014BEA8* self)
{
    if (func_001DDA80(self->owner) != 0) return 0;
    if (self->kind == 0xB || self->kind == 0x10) return 0;
    return 1;
}

typedef void (*VFn_0014BEF8)(void* self, void* arg);

struct Node_0014BEF8 {
    VFn_0014BEF8* vtbl;
};

struct Obj_0014BEF8 {
    u8 pad0[0x724];
    s32 kind;
};

struct Scratch_0014BEF8 {
    s32 words[4];
};

s32 func_001C96D8(Obj_0014BEF8* self, Node_0014BEF8** slot);
void func_001D7098(void* out, s32 mode, Obj_0014BEF8* owner);

s32 func_0014BEF8(Obj_0014BEF8* self, Node_0014BEF8** slot)
{
    if (self->kind == 0x10 || self->kind == 0xB) return 1;
    if (func_001C96D8(self, slot) == 0) return 0;
    Node_0014BEF8* found = (Node_0014BEF8*)func_001925F0();
    Node_0014BEF8* n = *slot;
    if (n == found) {
        Scratch_0014BEF8 buf;
        func_001D7098(&buf, 0, self);
        n->vtbl[0x50](n, &buf);
    }
    return 1;
}

struct Obj_148598 {
    u8 pad0[0x2D0];
    s32 f2D0;
};

struct Flags_148598 {
    s32 flags;
};

struct Ctx_148598 {
    u8 pad0[0x438];
    s32 f438;
};

typedef void (*VFn_148598)(void* self);
typedef void (*VFn3_148598)(void* self, s32 a, void* b);
struct VObj_148598 {
    VFn_148598* vtbl;
};
struct VObj3_148598 {
    VFn3_148598* vtbl;
};

extern Flags_148598* D_002623C8;
extern Ctx_148598* D_002623C4;
extern s32 D_00275C34;
extern u8 D_0026CBC8[];
extern u8 D_00261EF0[];
extern u8 D_00264A40[];

void func_001837E0(void* self, s32 a, s32 b, s32 c);
void func_00151FC8(void* p);
void func_0018C7F8(void* p);
void func_00147AB0(void* self, s32 mode);
void func_00148598(void* self, s32 mode)
{
    if (((Obj_148598*)self)->f2D0 == mode) return;
    if (mode == 1) {
        Flags_148598* fl = D_002623C8;
        s32 bits = fl->flags;
        if ((bits & 2) == 0) {
            Ctx_148598* cx = D_002623C4;
            fl->flags = bits | 2;
            s32 g = D_00275C34; s32 old = cx->f438; cx->f438 = old + 1; if (g != 0) cx->f438 = old;
        }
        VObj_148598* vo = (VObj_148598*)D_0026CBC8;
        vo->vtbl[14](vo);
        void* r = (void*)func_001925F0();
        if (r != 0) {
            ((VObj3_148598*)r)->vtbl[82](r, 0, self);
        }
        func_001837E0(self, 2, 0, 0);
        mode = 2;
        func_00151FC8(D_00261EF0);
        func_0018C7F8(D_00264A40);
    }
    func_00147AB0(self, mode);
}

struct Obj_149660 {
    u8 pad0[0x20];
    f32 f20;
    u8 pad24[0x40 - 0x24];
    s32 f40;
    u8 pad44[0x50 - 0x44];
    s32 f50;
    f32 f54;
    f32 f58;
};

void func_00149398(void* self, void* owner);
void func_001495E8(void* s, s32 value);

void func_00149660(Obj_149660* self, void* owner)
{
    func_00149398(self, owner);
    self->f40 = 0;
    self->f20 = 10.0f;
    func_001495E8(self, 0);
    self->f54 = 0.5f;
    self->f58 = -1.0f;
    self->f50 = 0;
}

struct Eng_1496C0 {
    u8 pad0[0x1C8];
    f32 f1C8;
    u8 pad1CC[0x1E4 - 0x1CC];
    f32 f1E4;
};

struct Obj_1496C0 {
    u8 pad0[0x4];
    Eng_1496C0* eng;
    u8 pad8[0x4];
    s32 f0C;
    f32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    f32 f20;
    f32 f24;
    f32 f28;
    f32 f2C;
};

struct Tmp_1496C0 {
    s32 w[4];
};

extern f32 D_00261BF0;

void func_00189230(void* a, void* b, void* c);
void func_001493C8(void* out, void* self);
void func_00144B70(void* eng, void* tmp);
void func_00143968(void* eng, f32 x);

void func_001496C0(Obj_1496C0* self)
{
    Tmp_1496C0 tmp;
    Eng_1496C0* eng = self->eng;
    func_00189230((u8*)eng + 0x80, (u8*)self + 8, (u8*)self + 0x10);
    f32 d = self->f20;
    self->f10 = D_00261BF0;
    self->f0C = 0;
    self->f14 = 0;
    self->f18 = 0;
    self->f1C = 0;
    f32 a = eng->f1C8;
    self->f28 = a;
    self->f24 = a / d;
    func_001493C8(&tmp, self);
    func_00144B70(eng, &tmp);
    self->f2C = eng->f1E4;
    func_00143968(eng, 49.0f);
}

extern void* D_0026EC68;
void func_00146470(void* self);

void func_00148718(void* self)
{
    func_00146470(self);
    D_0026EC68 = self;
}

typedef void (*VFn_148748)(void* self, s32 arg);
struct Dispatch_148748 { VFn_148748* vtbl; };

void func_00148748(Dispatch_148748* self)
{
    self->vtbl[51](self, 2);
}

struct Holder_149398 { u8 pad[4]; void* value; };

void func_00149398(Holder_149398* self, void* value)
{
    self->value = value;
}

struct Target_1493A0 { u8 pad[0x3D8]; void* ref; };
struct Holder_1493A0 { u8 pad[4]; Target_1493A0* target; };

s32 func_001493A0(Holder_1493A0* self)
{
    return self->target->ref == self;
}

void func_001AA298(void* self);
typedef void (*VFn1_14AD70)(void* self);
struct Slot_14AD70 { VFn1_14AD70* vtbl; u8 pad[0x260 - 4]; };
struct Owner_14AD70 { u8 pad[0x260]; s32 count; Slot_14AD70 slots[1]; };

void func_0014AD70(Owner_14AD70* self)
{
    func_001AA298(self);
    for (s32 i = 0; i < self->count; i++) {
        Slot_14AD70* s = &self->slots[i];
        s->vtbl[2](s);
    }
}
