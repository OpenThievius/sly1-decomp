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

void func_00127378(void* self, s32 kind, void* msg);
void func_001B6598(void* dev, s32* out);
void func_001DBCC8(void* target, void* fn, void* ctx, s32 a, s32 b);

typedef void (*VFn_148770)(void* self, void* arg);
struct Dev_148770 { VFn_148770* vtbl; };
struct Hub_148770 { u8 pad0[0x1D60]; Dev_148770* f1D60; };
struct Self_148770 { u8 pad0[0x14]; Hub_148770* hub; u8 pad1[0x2E8 - 0x18]; void* f2E8; };
struct Note_148770 { s32 flag; void* owner; };
struct Frame_148770 { Note_148770 note; u8 pad0[0x50 - 8]; s32 code; u8 pad1[0x60 - 0x54]; };

void func_00148770(Self_148770* self, s32 kind, void* msg)
{
    Frame_148770 fr;
    func_00127378(self, kind, msg);
    if (kind != 0x14) return;
    if (msg != self->f2E8) return;
    func_001B6598(msg, &fr.code);
    if (fr.code != 0x263) return;
    Dev_148770* dev = self->hub->f1D60;
    if (dev != 0) {
        fr.note.flag = 1;
        fr.note.owner = self;
        dev->vtbl[31](dev, &fr.note);
    }
    func_001DBCC8(self->hub, (void*)func_00148748, self, 0, 0);
}

extern f32 D_0026185C;
void func_00147428(void* a);

typedef void (*VFn_148828)(void* self, s32 arg);
struct Sub_148828 { u8 pad0[0x2308]; f32 f2308; };
struct Obj_148828 { VFn_148828* vtbl; u8 pad0[0x10]; Sub_148828* sub; u8 pad1[0x2D0 - 0x18]; s32 f2D0; };

void func_00148828(Obj_148828* self)
{
    func_00147428(self);
    if (self->f2D0 != 0) return;
    if (self->sub->f2308 <= D_0026185C) self->vtbl[51](self, 6);
}

struct Slot_1493B8 { u8 pad[0x8]; s32 value; };

void func_001493B8(Slot_1493B8* self, s32 value)
{
    self->value = value;
}

void func_001493C0(void)
{
}

void func_0014B3E0(s32 n, f32* m, f32* b, f32* x)
{
    s32 i;
    s32 k;
    f32 sum;

    for (i = 0; i < n; i++) {
        if (m[i * n + i] == 0.0f) {
            x[i] = 0.0f;
        } else {
            sum = 0.0f;
            for (k = 0; k < i; k++) {
                sum += m[k * n + i] * x[k];
            }
            x[i] = (b[i] - sum) / m[i * n + i];
        }
    }

    for (i = n - 2; i >= 0; i--) {
        if (m[i * n + i] != 0.0f) {
            sum = 0.0f;
            for (k = i + 1; k < n; k++) {
                sum += m[k * n + i] * x[k];
            }
            x[i] -= sum;
        }
    }
}

struct Owner_0014B550 { u8 pad0[0x14]; u8* p14; };

void func_001C74E8(void* self);
void func_00152470(void* table, void* self);

void func_0014B550(Owner_0014B550* self)
{
    func_001C74E8(self);
    func_00152470(self->p14 + 0x1CCC, self);
}

struct Obj_14AA90 { u8 pad[8]; s32 value; };
void func_0014AA90(Obj_14AA90* obj, s32 value) { obj->value = value; }

struct Obj_14AA98 { u8 pad[8]; s32 value; };
void func_0014AA98(Obj_14AA98* obj) { obj->value = 0; }

s32 func_00148910(const f32* first, const f32* second)
{
    s32 result = -1;
    if (*first < *second) result = 1;
    return result;
}

struct State_00149168 { u8 pad[0x340]; s32 value; };
void func_00146340(void* self);
void func_00149168(State_00149168* self)
{
    func_00146340(self);
    self->value = 0;
}

struct Parent_0014A8D0 { u8 pad[0x3DC]; u8* child; };
struct State_0014A8D0 { s32 unused; Parent_0014A8D0* parent; };
void func_0014A8D0(State_0014A8D0* self)
{
    Parent_0014A8D0* parent = self->parent;
    func_00144B70(parent, parent->child + 0x370);
}

struct State_0014B678 { f32 a; f32 b; s32 value; };
void func_001EAD88(void* a, void* b, f32 value);
void func_0014B678(State_0014B678* self, f32 value)
{
    func_001EAD88(&self->b, self, value);
    self->value = 0;
}

void func_001C7520(void*);
void func_00152600(void*, void*);
void func_0014B588(u8* self) { func_001C7520(self); func_00152600(*(u8**)(self+0x14)+0x1CCC,self); }

struct __attribute__((packed)) Pack_0014B5C0 { u64 value; };
struct Obj_0014B5C0 { u8 pad[0xC10]; Pack_0014B5C0 value; };
void func_001C7188(void*, void*);
void func_0014B5C0(Obj_0014B5C0* self, void* other) { Pack_0014B5C0 save=self->value; func_001C7188(self,other); self->value=save; }

void func_001C6F48(void*);
extern s32 D_0027C008;
void func_0014B608(u8* self) { func_001C6F48(self); *(s32*)(self+0xC24)=1; D_0027C008=0; }

void func_001C72A0(void*);
void func_0014B640(u8* self) { func_001C72A0(self); *(s32*)(self+0xC2C)=D_0027C008++; }

struct Obj_148400 {
    u8 pad0[0x320];
    f32 f320;
    u8 pad324[0x20];
    f32 f344;
    s32 f348;
    f32 f34C;
    f32 f350;
    f32 f354;
    f32 f358;
};

void func_00146340(void* self);

void func_00148400(void* self)
{
    Obj_148400* o = (Obj_148400*)self;
    func_00146340(o);
    f32 k60 = 60.0f;
    f32 k300 = 300.0f;
    f32 k075 = 0.75f;
    f32 k05 = 0.5f;
    f32 k035 = 0.35f;
    o->f320 = k035;
    o->f344 = k300;
    o->f358 = k075;
    o->f354 = k05;
    o->f34C = k60;
    o->f348 = 0;
    o->f350 = k60;
}

struct Obj_148470 {
    u8 pad0[0x2D0];
    s32 f2D0;
};

void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void func_001837E0(void* self, s32 a, s32 b, s32 c);
void func_00147AB0(void* self, s32 mode);

void func_00148470(void* self, s32 mode)
{
    Obj_148470* o = (Obj_148470*)self;
    if (o->f2D0 == mode) return;
    if (mode == 1) {
        func_001BFCD8(0x74, 0, (s32)self, 0, 0, 0, 1500.0f, 0.0f, 1.0f, 0.0f, 0.0f);
        mode = 4;
        func_001837E0(self, 2, 0, 0);
    }
    func_00147AB0(self, mode);
}

void func_001E02C8(void* self, s32 n);
void func_00147AB0(void* self, s32 mode);

extern u8 D_0026E9F8[];

struct Msg_148888 {
    s32 value;
    void* owner;
    u8 pad0[0x50 - 8];
};

typedef void (*VFn_148888)(void* self, void* msg);
struct Dev_148888 {
    VFn_148888* vtbl;
};

struct Self_148888 {
    u8 pad0[0x380];
    Dev_148888* f380;
};

void func_00148888(Self_148888* self, s32 mode)
{
    Msg_148888 msg;
    if (*(s32*)((u8*)self + 0x2D0) == mode) return;
    if (mode == 1) {
        func_001E02C8(D_0026E9F8, 2);
        Dev_148888* dev = self->f380;
        if (dev != 0) {
            msg.value = mode;
            msg.owner = self;
            dev->vtbl[31](dev, &msg);
        }
        mode = 2;
    }
    func_00147AB0(self, mode);
}

void func_00127378(void* self, s32 kind, void* msg);
void func_001B6598(void* dev, s32* out);
void func_001DBCC8(void* target, void* fn, void* ctx, s32 a, s32 b);
void func_00148E18(void* self);

typedef void (*VFn_148E40)(void* self, void* arg);
struct Dev_148E40 { VFn_148E40* vtbl; };
struct Hub_148E40 { u8 pad0[0x1D60]; Dev_148E40* f1D60; };
struct Self_148E40 { u8 pad0[0x14]; Hub_148E40* hub; u8 pad1[0x2E8 - 0x18]; void* f2E8; };
struct Note_148E40 { s32 flag; void* owner; };
struct Frame_148E40 { Note_148E40 note; u8 pad0[0x50 - 8]; s32 code; u8 pad1[0x60 - 0x54]; };

void func_00148E40(Self_148E40* self, s32 kind, void* msg)
{
    Frame_148E40 fr;
    func_00127378(self, kind, msg);
    if (kind != 0x14) return;
    if (msg != self->f2E8) return;
    func_001B6598(msg, &fr.code);
    if (fr.code != 0x263) return;
    Dev_148E40* dev = self->hub->f1D60;
    if (dev != 0) {
        fr.note.flag = 1;
        fr.note.owner = self;
        dev->vtbl[31](dev, &fr.note);
    }
    func_001DBCC8(self->hub, (void*)(void (*)(void*))func_00148E18, self, 0, 0);
}

typedef void (*VFn_148EF8)(void* self, s32 arg);

struct Obj_148EF8 {
    VFn_148EF8* vtbl;
    u8 pad004[0x2D0 - 0x004];
    s32 f2D0;
    u8 pad2D4[0x338 - 0x2D4];
    void* f338;
    u8 pad33C[0x398 - 0x33C];
    f32 f398;
};

extern s32 D_00270458;
extern f32 D_00261860;

void func_00147428(void* a);

void func_00148EF8(Obj_148EF8* self)
{
    func_00147428(self);
    if (self->f2D0 != 0) return;
    if (self->f338 == 0) return;
    if (D_00270458 != 2) {
        self->f398 = self->f398 - D_00261860;
    }
    if (self->f398 <= 0.0f) {
        self->vtbl[51](self, 6);
    }
}

typedef void (*VFn_148F80)(void* self);

struct Obj_148F80 {
    VFn_148F80* vtbl;
    u8 pad004[0x26C - 0x004];
    f32 f26C;
    s32 f270;
    s32 f274;
    s32 f278;
};

struct Glob_148F80 {
    u8 pad0[0x19E0];
    s32 f19E0;
};

extern u8 D_0026C6C8[];

void func_00148F80(void)
{
    Obj_148F80* obj = (Obj_148F80*)D_0026C6C8;
    obj->vtbl[14](obj);
    Glob_148F80* g = (Glob_148F80*)D_002623C0;
    if (g->f19E0 < 0x63) {
        g->f19E0 = g->f19E0 + 1;
        obj->f26C = 250.0f;
        obj->f274 = 0;
        obj->f278 = 0;
    } else {
        g->f19E0 = 0x63;
    }
}

struct Quad_14A7B8 {
    s32 w[4];
};

struct Node_14A7B8 {
    u8 pad0[0x1C4];
    f32 f1C4;
    u8 pad1[0x1E4 - 0x1C8];
    f32 f1E4;
};

struct Obj_14A7B8 {
    u8 pad0[0x4];
    Node_14A7B8* p4;
    u8 pad1[0x28 - 0x8];
    f32 f28;
    f32 f2C;
    u8 pad2[0x48 - 0x30];
    void* p48;
    void* p4C;
    u8 pad3[0x5C - 0x50];
    s32 f5C;
};

void func_001493C8(void* out, void* self);
void func_00149458(void* out, void* self);
void func_001BF788(void* self, s32 n);
void func_00144938(void* self, void* a, void* b);
s32 func_001EAC68(f32 a, f32 b, f32 c);
void func_00143940(void* self, f32 x);
void func_00143968(void* self, f32 x);

void func_0014A7B8(Obj_14A7B8* self)
{
    Quad_14A7B8 a;
    Quad_14A7B8 b;
    Node_14A7B8* n;

    func_001493C8(&a, self);
    func_00149458(&b, self);
    n = self->p4;
    func_001BF788(self->p48, 0);
    func_001BF788(self->p4C, 500);
    func_00144938(n, &b, &a);
    if (func_001EAC68(n->f1C4, self->f28, 1e-4f) == 0) {
        func_00143940(n, self->f28);
    }
    self->f5C = 0;
    if (n->f1E4 == 49.0f) {
        func_00143968(n, self->f2C);
    }
}


struct Slot_14BF88 {
    u8 pad0[0x10];
    s32 v10;
};

struct Obj_14BF88 {
    u8 pad0[0x724];
    s32 kind724;
    u8 pad1[0x7E0 - 0x728];
    void* sub7E0;
    u8 pad2[0xC20 - 0x7E4];
    Slot_14BF88* slotC20;
    f32 fC24;
};

void func_001C91C8(void* self);
void func_0014CD70(void* mgr, void* self);
void func_0012F6B0(void* sub, f32 x);

void func_0014BF88(Obj_14BF88* self)
{
    func_001C91C8(self);
    switch (self->kind724) {
    case 0xB:
        func_0014CD70((void*)D_0027C00C, self);
        if (self->slotC20 != 0) {
            self->slotC20->v10 = 0;
            self->slotC20 = 0;
        }
        break;
    case 0xC:
        if (self->slotC20 != 0) {
            self->slotC20->v10 = 0;
            self->slotC20 = 0;
        }
        func_0012F6B0(self->sub7E0, self->fC24);
        break;
    }
}
