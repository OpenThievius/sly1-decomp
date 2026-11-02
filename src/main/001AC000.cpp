// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_1AC638 {
    u8 pad0[4];
    s32 handle;
    s8 flag;
    u8 pad1[0x20C - 9];
    f32 scale;
};

struct Loc_1AC638 {
    u8 data[0xB0];
    f32 x;
    f32 y;
};

s32 func_001E2100(void* p);
void func_001E2138(void* dst, void* p);
void func_0015C8B8(s32 handle, f32 a, f32 b);
void func_0015DB28(void* out, void* p, s32 handle);
void func_0015E290(void* out, f32 t, f32* a, f32* b);
void func_001AAB20(Obj_1AC638* self, f32 x, f32 y);
void func_0015C900(s32 handle);

void func_001AC638(Obj_1AC638* self, void* p)
{
    Loc_1AC638 loc;

    if (p != 0 && func_001E2100(p)) {
        func_001E2138(&self->flag, p);
    } else {
        self->flag = 0;
    }
    f32 v = self->scale;
    func_0015C8B8(self->handle, v, v);
    func_0015DB28(&loc, &self->flag, self->handle);
    f32 zero = 0.0f;
    func_0015E290(&loc, zero, &loc.x, &loc.y);
    f32 x = loc.x;
    func_001AAB20(self, x, (self->flag != 0) ? loc.y : 0.0f);
    func_0015C900(self->handle);
}

void func_001AA8F0(void* self);

struct Obj_1ACA30 { u8 pad[0x250]; s32 mode; u8 pad2[0x260 - 0x254]; s32 flag; };

void func_001ACA30(Obj_1ACA30* self)
{
    if (self->mode != 3 || self->flag == 0) {
        func_001AA8F0(self);
    }
}

void func_001AA958(void* self);

struct Obj_1AD3B0 { u8 pad[0x250]; s32 mode; u8 pad2[0x260 - 0x254]; s32 flag; };

void func_001AD3B0(Obj_1AD3B0* self)
{
    if (self->mode == 3 && self->flag != 0) {
        self->flag = 0;
    } else {
        func_001AA958(self);
    }
}

void func_001ADFF0(void* self);
void func_001AA998(void* self, s32 flag);

struct Obj_1AE130 { u8 pad[0x268]; s32 pending; };

void func_001AE130(Obj_1AE130* self, s32 force)
{
    if (self->pending != 0 && force == 0) {
        self->pending = 0;
        func_001ADFF0(self);
        force = 1;
    }
    func_001AA998(self, force);
}

struct Queue_1AF078 {
    u8 pad_0[0x5A0];
    u32 count;
    u32 items[4];
};

void func_001AF078(Queue_1AF078* q, u32 value)
{
    u32 n = q->count;
    if (n < 4) {
        q->items[n] = value;
        q->count = n + 1;
    }
}

struct Obj_001AECE0 {
    u8 pad0[0x550];
    s32 f550;
};

void func_001AECE0(Obj_001AECE0* self, s32 value)
{
    self->f550 = value;
}

struct Node_129CA8 {
    u8 pad0[0x18];
    union {
        s32 w;
        f32 f;
    } f18;
};

struct Obj_001AEF68 {
    u8 pad0[0x5c8];
    Node_129CA8* f5c8;
    f32 f5cc;
};

Node_129CA8* func_00129CA8(Obj_001AEF68* self);

void func_001AEF68(Obj_001AEF68* self)
{
    Node_129CA8* node = func_00129CA8(self);

    if (node != 0) {
        self->f5cc = node->f18.f;
        node->f18.w = 0;
        self->f5c8 = node;
    }
}

struct Sink_001AEFA0 { u8 pad0[0x18]; f32 value; };
struct Mixer_001AEFA0 { u8 pad0[0x5C8]; Sink_001AEFA0* sink; f32 pending; };
struct Global_001AEFA0 { u8 pad0[0x2220]; s32 state; };

extern Global_001AEFA0* D_00262E10;

void func_001B93F8(Mixer_001AEFA0* self);

void func_001AEFA0(Mixer_001AEFA0* self)
{
    func_001B93F8(self);
    Sink_001AEFA0* sink = self->sink;
    if (sink != 0) {
        Global_001AEFA0* g = D_00262E10;
        if (g != 0) {
            if (g->state != 4) {
                sink->value = self->pending;
                self->sink = 0;
                *(s32*)&self->pending = 0;
            }
        }
    }
}

struct Stack_001AF000 { u8 pad0[0x564]; u32 count; s32 items[4]; };

void func_001AF000(Stack_001AF000* self, s32 value)
{
    u32 n = self->count;
    if (n < 4) {
        self->items[n] = value;
        self->count = n + 1;
    }
}

typedef void* (*VFn_1AC5C0)(void* self, f32 sx, f32 sy);
struct VTab_1AC5C0 { s32 w0; s32 w1; s16 delta; s16 w2; VFn_1AC5C0 fn; };
struct Obj_1AC5C0 { u8 pad0[0x4C]; VTab_1AC5C0* vt; };
struct Node_1AC5C0 { u8 pad0[4]; Obj_1AC5C0* obj; u8 pad1[0x210 - 8]; void** slot; };

extern u8 D_002743D0[];
void func_001AA268(void* self);
s32 func_0015C188(s32 k);
void* func_0015C1C0(s32 k);

void func_001AC5C0(Node_1AC5C0* self)
{
    VTab_1AC5C0* vt;

    func_001AA268(self);
    vt = self->obj->vt;
    self->obj = (Obj_1AC5C0*)vt->fn((u8*)self->obj + vt->delta, 1.25f, 1.25f);
    if (func_0015C188(2)) {
        self->slot = (void**)D_002743D0;
        *self->slot = func_0015C1C0(2);
    }
}

typedef void* (*VFn_1AC888)(void* self, f32 sx, f32 sy);
struct VTab_1AC888 { s32 w0; s32 w1; s16 delta; s16 w2; VFn_1AC888 fn; };
struct Obj_1AC888 { u8 pad0[0x4C]; VTab_1AC888* vt; };
struct Node_1AC888 { u8 pad0[4]; Obj_1AC888* obj; u8 pad1[0x208 - 8]; u32 color; u8 pad2[0x210 - 0x20C]; void** slot; };

extern u8 D_002743F0[];
void func_001AA268(void* self);
s32 func_0015C188(s32 k);
void* func_0015C1C0(s32 k);

void func_001AC888(Node_1AC888* self)
{
    VTab_1AC888* vt;

    func_001AA268(self);
    vt = self->obj->vt;
    self->obj = (Obj_1AC888*)vt->fn((u8*)self->obj + vt->delta, 0.9f, 0.9f);
    self->color = 0xDF7F7F7Fu;
    if (func_0015C188(2)) {
        self->slot = (void**)D_002743F0;
        *self->slot = func_0015C1C0(2);
    }
}

struct Queue_1AF028 { u8 pad[0x578]; s32 count; void* items[4]; };

void func_001AF028(Queue_1AF028* self, void* item)
{
    s32 n = self->count;
    if ((u32)n < 4) {
        self->items[n] = item;
        self->count = n + 1;
    }
}

struct Queue_1AF050 { u8 pad[0x58C]; s32 count; void* items[4]; };

void func_001AF050(Queue_1AF050* self, void* item)
{
    s32 n = self->count;
    if ((u32)n < 4) {
        self->items[n] = item;
        self->count = n + 1;
    }
}

struct Unit_1AF0A0 { u8 pad[0xB04]; f32 scale; };

void func_001AECB0(void* self);

void func_001AF0A0(Unit_1AF0A0* self)
{
    func_001AECB0(self);
    self->scale = 1.0f;
}

extern u8 D_002744B8[];

void func_001BAC30(void* self);
void func_00124DF8(void* self, s32 n, void* table);

void func_001AF0D0(void* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 2, D_002744B8);
}

typedef void (*VFn_1AC910)(void* self, s32 mode);
struct Unit_1AC910 { VFn_1AC910* vtbl; u8 pad0[0x250 - 4]; s32 state; u8 pad1[0x260 - 0x254]; s32 flag; s32 value; };

s32 func_001F6738(void* p, s32 v);
void func_001AA4F0(void* self, s32 v);

void func_001AC910(Unit_1AC910* self, s32 v)
{
    s32 k = self->state;
    if (k == 0) {
        func_001AA4F0(self, v);
        goto done;
    }
    if (k < 0) {
        goto done;
    }
    if (k >= 4) {
        goto done;
    }
    if (func_001F6738((u8*)self + 8, v) != 0) {
        self->value = v;
        self->flag = 1;
        self->vtbl[16](self, 3);
    }
done:
    return;
}

struct Unit_1AC990 { u8 pad0[0x260]; s32 flag; s32 value; };

void func_001AA4F0(void* self, s32 v);
void func_001AA998(void* self, s32 flag);

void func_001AC990(Unit_1AC990* self, s32 v)
{
    if (self->flag != 0 && v == 0) {
        s32 x = self->value;
        self->flag = 0;
        func_001AA4F0(self, x);
        v = 1;
    }
    func_001AA998(self, v);
}

struct Obj_1AD320 { u8 pad[0x260]; s32 f260; u8 pad2[0x464 - 0x264]; s32 f464; };

void func_001AA4F0(void* self, void* p);
void func_001AA998(void* self, s32 flag);

void func_001AD320(Obj_1AD320* self, s32 flag)
{
    if (self->f260 != 0 && flag == 0) {
        self->f260 = 0;
        func_001AA4F0(self, (u8*)self + 0x264);
        flag = 1;
    }
    if (flag == 0) {
        self->f464 = 0;
    }
    func_001AA998(self, flag);
}

struct Obj_1AD378 { u8 pad[0x250]; s32 f250; u8 pad2[0x260 - 0x254]; s32 f260; };

void func_001AA8F0(void* self);

void func_001AD378(Obj_1AD378* self)
{
    if (self->f250 == 3 && self->f260 != 0) return;
    func_001AA8F0(self);
}

typedef void (*VFn_001AD718)(void* self);
struct Actor_001AD718 { VFn_001AD718* vtbl; u8 pad0[0x25C]; s32 slot260; };
struct Mgr_001AD718 { u8 pad0[4]; s32 f4; u8 pad1[0x2C - 8]; s32 f2C; };

extern u8 D_00275BC0[];
void func_001AA298(void* self);

void func_001AD718(Actor_001AD718* self)
{
    Global_001AEFA0* g;
    Mgr_001AD718* m;

    func_001AA298(self);
    if (self->slot260 == 0) goto tail;
    g = D_00262E10;
    if (g != 0 && g->state == 6) goto tail;
    m = (Mgr_001AD718*)D_00275BC0;
    if (m->f4 == 3 && m->f2C < 2) {
        self->vtbl[14](self);
        return;
    }
tail:
    self->vtbl[15](self);
}

struct Timer_001AD940 { u8 pad0[0x248]; f32 value; };

void func_001AA268(void* self);

void func_001AD940(Timer_001AD940* self)
{
    func_001AA268(self);
    self->value = 0.5f;
}

struct Obj_1ACA68 { u8 pad[0x250]; s32 f250; u8 pad2[0x260 - 0x254]; s32 f260; };

void func_001AA958(void* self);

void func_001ACA68(Obj_1ACA68* self)
{
    if (self->f250 == 3 && self->f260 != 0) {
        self->f260 = 0;
    } else {
        func_001AA958(self);
    }
}

typedef void (*VFn_1ACE38)(void* self, s32 mode);

struct Obj_1ACE38 {
    VFn_1ACE38* vtbl;
    u8 pad0[0x250 - 4];
    s32 state;
    u8 pad1[0x260 - 0x254];
    s32 flag;
    u8 f264;
};

void func_001AA4F0(void* self, s32 v);
s32 func_001F6738(void* p, s32 v);
void func_001E2138(void* dst, s32 v);

void func_001ACE38(Obj_1ACE38* self, s32 v)
{
    s32 k = self->state;
    if (k == 0) {
        func_001AA4F0(self, v);
        return;
    }
    if (k < 0) {
        return;
    }
    if (k >= 4) {
        return;
    }
    if (self->flag == 0) {
        if (func_001F6738((u8*)self + 8, v) == 0) {
            return;
        }
    }
    self->flag = 1;
    if (v != 0) {
        func_001E2138(&self->f264, v);
    } else {
        self->f264 = 0;
    }
    self->vtbl[16](self, 3);
}

struct Obj_1AE7F8 { u8 pad[0x260]; s32 f260; };

void func_001AA998(void* self, s32 flag);

void func_001AE7F8(Obj_1AE7F8* self, s32 flag)
{
    if (flag == 0) {
        self->f260 = 0;
    }
    func_001AA998(self, flag);
}

struct Obj_1AEE50 { u8 pad0[0x578]; s32 count578; s32 items57C[9]; s32 count5A0; s32 items5A4[9]; };

s32 func_001833F0(void* key, s32 item);
s32 func_001300E8(void* key, s32 item);

s32 func_001AEE50(Obj_1AEE50* self, void* key)
{
    for (s32 i = 0; i < self->count578; i++) {
        if (func_001833F0(key, self->items57C[i]) != 0) {
            return 1;
        }
    }
    for (s32 i = 0; i < self->count5A0; i++) {
        if (func_001300E8(key, self->items5A4[i]) != 0) {
            return 1;
        }
    }
    return 0;
}

typedef void* (*VFn_1ACDA0)(void* self, f32 sx, f32 sy);
struct VTab_1ACDA0 { s32 w0; s32 w1; s16 delta; s16 w2; VFn_1ACDA0 fn; };
struct Obj_1ACDA0 { u8 pad0[0x4C]; VTab_1ACDA0* vt; };
struct Node_1ACDA0 { u8 pad0[4]; void* f4; u8 pad1[0x20C - 8]; f32 f20c; void** slot; u8 pad2[0x248 - 0x214]; f32 f248; };

extern u8 D_00274410[];
void func_001AA268(void* self);
s32 func_0015C188(s32 k);
void* func_0015C1C0(s32 k);

void func_001ACDA0(Node_1ACDA0* self)
{
    Obj_1ACDA0* o;
    VTab_1ACDA0* vt;

    func_001AA268(self);
    o = (Obj_1ACDA0*)func_0015C1C0(0);
    vt = o->vt;
    self->f4 = vt->fn((u8*)o + vt->delta, 1.0f, 1.0f);
    self->f20c = 0.8f;
    self->f248 = 0.5f;
    if (func_0015C188(2)) {
        self->slot = (void**)D_00274410;
        *self->slot = func_0015C1C0(2);
    }
}

extern u8* D_00275710;
extern f32 D_00261858[];
extern s32 D_002744D0;

struct Node_1AF508 {
    u8 pad0[0x558];
    s32 x558;
    u8 pad1[0xAF0 - 0x55C];
    Node_1AF508* next;
    u8 pad2[0xAFC - 0xAF4];
    f32 fAFC;
};

void func_001AF508()
{
    s32 scratch[4];
    (void)scratch;
    s32 count = 0;
    Node_1AF508* n = *(Node_1AF508**)(D_00275710 + 0x1CA8);
    while (n != 0) {
        s32 t = count + 1;
        count = (n->x558 != 8) ? t : count;
        n = n->next;
    }
    if (count != 0) {
        s32 idx = 0;
        n = *(Node_1AF508**)(D_00275710 + 0x1CA8);
        while (n != 0) {
            if (n->x558 != 8) {
                n->fAFC = D_00261858[1] + (0.03333333507180214f / (f32)count) * (f32)idx;
                idx++;
            }
            n = n->next;
        }
    }
    D_002744D0 = 0;
}

extern s32 D_002744D0;
void func_0015FCD8(void* self, void* p);
void func_00152470(void* list, void* item);
void func_00152600(void* list, void* item);

struct Obj_1AF7A8 {
    u8 pad0[0x14];
    u8* p14;
    u8 pad1[0xAF8 - 0x18];
    s32 flag_AF8;
};

void func_001AF7A8(Obj_1AF7A8* self, void* p)
{
    func_0015FCD8(self, p);
    if (p != 0) {
        if (self->flag_AF8 != 0) {
            func_00152600(self->p14 + 0x1CA8, self);
            self->flag_AF8 = 0;
        }
    } else {
        func_00152470(self->p14 + 0x1CA8, self);
        self->flag_AF8 = 1;
    }
    D_002744D0 = 1;
}

// NEAR: register and load order of D_00262C84 vs D_00269988 (retail keeps the x load in v1, ours in a0; xori placed differently)

struct Node_001AE178 { u8 pad0[0xC]; f32 f0C; };
struct Obj_001AE178 { u8 pad0[0x260]; s32 f260; s32 f264; };

extern s32 D_00275BF0;
extern s32 D_00262C84;
extern Node_001AE178* D_00269988;

void func_001AA298(void* self);
void func_001ADFF0(void* self);

void func_001AE178(Obj_001AE178* self)
{
    if (D_00275BF0 == 1) {
        s32 b = 0;
        s32 a = D_00262C84 == 3;
        if (D_00269988 != 0 && D_00269988->f0C != 0.0f) {
            b = 1;
        }
        if ((a == 0) != (self->f260 == 0) || (b == 0) != (self->f264 == 0)) {
            self->f260 = a;
            self->f264 = b;
            func_001ADFF0(self);
        }
    }
    func_001AA298(self);
}

// NEAR: the store of func_0015C1C0 result is before the float load and call; retail puts it in the delay slot of the func_001AA788 call

typedef void (*VFn_1AE758)(void* self, void* arg);
struct Flags_1AE758 { u8 a; u8 b; };
struct Obj_1AE758 { VFn_1AE758* vtbl; void* f4; u8 f8; };
void func_001AA268(void* self);
void func_001AA8B0(void* self, f32 v);
void func_001AA8C0(void* self, f32 v);
void func_001AA8B8(void* self, f32 v);
void* func_0015C1C0(s32 k);
void func_001AA788(void* self, f32 v);
extern u8 D_002744AC[];

s8 func_001AEA08(void);
void func_001AE758(Obj_1AE758* self)
{
    f32 k = 0.25f;
    Flags_1AE758 fl;
    s32 v;

    func_001AA268(self);
    func_001AA8B0(self, k);
    func_001AA8C0(self, k);
    func_001AA8B8(self, 0.0f);
    void* r = func_0015C1C0(1);
    f32 g = *(f32*)D_002744AC;
    self->f4 = r;
    func_001AA788(self, g);
    v = func_001AEA08();
    fl.b = 0;
    fl.a = v;
    self->vtbl[8](self, &fl);
    self->f8 = 0;
}

struct Flt_1ADF28 { u8 pad[0xC]; f32 v; };
struct Obj_1ADF28 { u8 pad0[0x4C]; struct VTab_1ADF28* vt; };
struct VTab_1ADF28 { s32 w0; s32 w1; s16 delta; s16 w2; void* (*fn)(void* self, f32 sx, f32 sy); };
struct Node_1ADF28 { u8 pad0[4]; Obj_1ADF28* obj; u8 pad1[0x210 - 8]; void** slot; u8 pad2[0x260 - 0x214]; s32 f260; s32 f264; };

extern f32 D_0027446C;
extern f32 D_00274470;
extern u8 D_00274488[];
extern s32 D_00262C84;

void func_001AA268(void* self);
void* func_0015C1C0(s32 k);
void func_001ADFF0(void* self);

void func_001ADF28(Node_1ADF28* self)
{
    VTab_1ADF28* vt;

    func_001AA268(self);
    vt = self->obj->vt;
    self->obj = (Obj_1ADF28*)vt->fn((u8*)self->obj + vt->delta, D_0027446C, D_00274470);
    if (func_0015C1C0(2)) {
        self->slot = (void**)D_00274488;
        *self->slot = func_0015C1C0(2);
    }
    s32 a1 = 0;
    self->f264 = 0; *(s32*)((u8*)self+0x260) = (D_00262C84 == 3);
    if (D_00269988 != 0) {
        if (((Flt_1ADF28*)(void*)D_00269988)->v != 0.0f) {
            a1 = 1;
        }
    }
    self->f264 = a1;
    func_001ADFF0(self);
}

struct Obj_001AED78 {
    u8 pad0[0x564];
    s32 f564;
    s32 f568[9];
    s32 f58c;
    s32 f590[9];
    s32 f5b4;
};

s32 func_001AEE50(Obj_001AED78* self, s32 value);
s32 func_001833F0(s32 value, s32 item);
s32 func_001300E8(s32 value, s32 item);

s32 func_001AED78(Obj_001AED78* self, s32 value)
{

    if (self->f5b4 != 0) {
        return 1;
    }
    if (func_001AEE50(self, value) != 0) {
        return 0;
    }
    for (s32 i = 0; i < self->f564; i++) {
        if (func_001833F0(value, self->f568[i]) != 0) {
            return 1;
        }
    }
    for (s32 i = 0; i < self->f58c; i++) {
        if (func_001300E8(value, self->f590[i]) != 0) {
            return 1;
        }
    }
    return 0;
}

struct Obj_1AEF00 {
    u8 pad_0[0x564];
    s32 f564;
    s32 f568;
    u8 pad_56C[0x58C - 0x56C];
    s32 f58C;
    u8 pad_590[0x5B4 - 0x590];
    s32 f5B4;
};

s32 func_001833F0(void* a, s32 b);

s32 func_001AEF00(Obj_1AEF00* o, void* p)
{
    if (p == 0) return 0;
    if (o->f5B4 == 0 && o->f564 == 1 && o->f58C == 0 && func_001833F0(p, o->f568) != 0) return 1;
    return 0;
}

typedef void (*VFn_1AF3B8)(void* self);

struct Child_1AF3B8 { VFn_1AF3B8* vtbl; };

struct Entry_1AF3B8 { void* obj; s32 value; };

struct Group_1AF3B8 {
    Child_1AF3B8* child;
    u8 pad0[0x24 - 4];
    s32 count;
    Entry_1AF3B8 items[5];
};

struct Obj_1AF3B8 {
    VFn_1AF3B8* vtbl;
    u8 pad0[0x14 - 4];
    void* f14;
    u8 pad1[0x560 - 0x18];
    void* f560;
    u8 pad2[0x5D4 - 0x564];
    s32 groupCount;
    u8 pad3[0x5E0 - 0x5D8];
    Group_1AF3B8 groups[1];
    u8 pad4[0xB00 - 0x630];
    s32 f_B00;
};

void func_00124A48(void* self);
void* func_00183058(void* a, void* b, void* c);

void func_001AF3B8(Obj_1AF3B8* self)
{
    Group_1AF3B8* src = &self->groups[0];
    func_00124A48(self);
    for (s32 i = 0; i < self->groupCount; i++) {
        Group_1AF3B8* g = &self->groups[i];
        Child_1AF3B8* c = g->child;
        c->vtbl[7](c);
        if (i != 0) {
            {
                s32 j;
                for (j = 0; j < src->count; j++) {
                    Entry_1AF3B8* s = src->items + j;
                    Entry_1AF3B8* d = g->items + j;
                    Child_1AF3B8* o = (Child_1AF3B8*)func_00183058(s->obj, self->f14, self);
                    d->obj = o;
                    if (o->vtbl[19] != 0) {
                        o->vtbl[19](o);
                    }
                    o = (Child_1AF3B8*)d->obj;
                    o->vtbl[20](o);
                    d->value = s->value;
                }
            }
            g->count = src->count;
        }
    }
    self->f_B00 = func_001AEF00((Obj_1AEF00*)self, (void*)D_00262E10);
    ((void (*)(void*, void*))self->vtbl[81])(self, self->f560);
}

typedef void (*VFn_1AE820)(void* self);

struct Obj_1AE820 {
    VFn_1AE820* vtbl;
    void* f4;
    u8 pad0[0x208 - 8];
    s32 f208;
    f32 f20c;
    u8 pad1[0x21C - 0x210];
    f32 f21c;
    f32 f220;
    u8 pad2[0x234 - 0x224];
    f32 f234;
    f32 f238;
    u8 pad3[0x250 - 0x23C];
    s32 f250;
    f32 f254;
    u8 pad4[0x260 - 0x258];
    s32 f260;
};

extern f32 D_00261868;
extern f32 D_0027240C;
extern s32 D_00272420;
extern u8 D_00269990[];
extern u8 D_00262280[];
extern void* D_002623C0;

s32 func_0018B770(void* p);
void func_00137228(void* out, f32 x, f32 y);
void func_00137238(void* out, f32 x, f32 y);
void func_00137248(void* out, s32* value);
void func_00137260(void* out, s32 flag);
void func_00137268(void* out, s32 flag);
void* func_00160B28(void* p);
s32 func_001E1FD0(char* dst, const char* fmt, ...);
void func_0015C8B8(void* handle, f32 a, f32 b);
void func_0015DB28(void* out, void* p, void* handle);
void func_0015E318(void* buf, void* out, s32 zero, void* data);
void func_0015C900(void* handle);

void func_001AE820(Obj_1AE820* self)
{
    u8 out[0x20];
    s32 tmp[4];
    char str[0x20];
    u8 buf[0xB0];
    f32 adj;
    f32 d;
    s32 held;
    s32 c;
    const char* fmt;
    char* sp;
    f32 px;
    f32 py;

    if (self->f250 == 0) {
        return;
    }
    d = D_00261868 - self->f254;
    if (self->f250 == 2) {
        if (D_00272420 == self->f250) {
            self->f260 = d < 2.0f;
        }
    }
    if (self->f260 != 0) {
        adj = (1.0f - D_0027240C) * 66.40000915527344f;
    } else {
        adj = 0.0f;
        if (self->f250 == 2) {
            if (1.0f < d) {
                if (func_0018B770(D_00269990) == 0) {
                    self->vtbl[0x3C / 4](self);
                }
            }
        }
    }
    held = self->f208;
    px = self->f234;
    py = self->f238;
    func_00137228(out, self->f21c, self->f220 + adj);
    func_00137238(out, px, py);
    tmp[0] = held;
    func_00137248(out, tmp);
    func_00137260(out, 0);
    func_00137268(out, 0);
    fmt = "%c&1^07~b2a83d%d%%&.";
    sp = str;
    c = func_001AEA08();
    func_001E1FD0(sp, fmt, c, func_00160B28(D_002623C0));
    func_0015C8B8(self->f4, self->f20c, self->f20c);
    func_0015DB28(buf, sp, self->f4);
    func_0015E318(buf, out, 0, D_00262280);
    func_0015C900(self->f4);
}

struct Obj_1AC9E0 { u8 pad[0x260]; s32 f260; };

s32 func_001AAAC8(Obj_1AC9E0* self);

s32 func_001AC9E0(Obj_1AC9E0* self)
{
    s32 r = 0;
    if (func_001AAAC8(self) != 0 || self->f260 != 0) {
        r = 1;
    }
    return r;
}

s32 func_001AEE50(void* self, void* key);
s32 func_00160D10();
struct Obj_1AFAF8 {
    u8 pad0[0x50];
    s32 x50;
    u8 pad1[0x2CC - 0x54];
    u32 x2CC;
    u8 pad2[0x538 - 0x2D0];
    u64 f538;
    u8 pad3[0x2220 - 0x540];
    s32 x2220;
    u8 pad4[0x239C - 0x2224];
    s32 x239C;
};
s32 func_001AFAF8(Obj_1AFAF8* a0, Obj_1AFAF8* a1)
{
    u64 m = 0x8000;
    m <<= 28;
    if ((a1->f538 & m) != 0 || a1->x50 == a0->x50 || func_001AEE50(a0, a1) != 0) {
        return 0;
    }
    if ((void*)a1 == (void*)D_00262E10 && a1->x2220 == 6 && a1->x239C == 3) {
        if ((func_00160D10() & 0x12000) != 0) {
            return 0;
        }
    }
    s64 t = (s64)a1->x2CC;
    return ((s32)t ^ 1) & 1;

}

struct Obj_1AECB0 {
    u8 pad_00[0x554];
    s32 f554;
    s32 f558;
};

void func_001B7968(Obj_1AECB0* self);

void func_001AECB0(Obj_1AECB0* a0) {
    func_001B7968(a0);
    a0->f554 = 0;
    a0->f558 = -1;
}

extern f32 D_0026185C;

struct Obj_1AC060 {
    u8 pad[0x264];
    s32 f264;
    s32 f268;
    s32 f26C;
    s32 f270;
    u8 pad2[0x278 - 0x274];
    f32 f278;
    f32 f27C;
};

void func_001AC060(Obj_1AC060* self)
{
    s32 n = self->f270 - 1;
    self->f270 = n;
    if (n <= 0) {
        n = self->f26C - 1;
        self->f26C = n;
        if (n <= 0) {
            self->f270 = 0;
            self->f26C = 0;
        } else {
            self->f270 = self->f264;
        }
    }

    s32 a = self->f264;
    f32 d = (f32)self->f268;
    s32 v0 = self->f26C - 1;
    s32 b = self->f270;
    v0 = (-1 < v0) ? v0 : 0;
    self->f278 = (f32)(v0 * a + b) / d;
    self->f27C = *(f32*)&D_0026185C;
}

typedef void (*VFn_1AD088)(void* self, void* arg);
struct Obj_1AD088 { VFn_1AD088* vtbl; };

extern u8 D_0024CE00[];
void func_001AD0D0(Obj_1AD088* self, s32 hi, s32 lo);

void func_001AD088(Obj_1AD088* self, s32 value)
{
    if (value != -1) {
        func_001AD0D0(self, value >> 8, (u8)value);
    } else {
        self->vtbl[8](self, D_0024CE00);
    }
}

struct Node_1AD6A8;
struct Dispatch_1AD6A8 { u8 pad0[0x20]; void (*fn)(Node_1AD6A8* self, u8* arg); };
struct Node_1AD6A8 { Dispatch_1AD6A8* vt; void* r; u8 pad[0x260 - 8]; s32 flag; };

typedef void* (*VFn_1AD6A8)(void* self, f32 sx, f32 sy);
struct VTab_1AD6A8 { s32 w0; s32 w1; s16 delta; s16 w2; VFn_1AD6A8 fn; };
struct Obj_1AD6A8 { u8 pad0[0x4C]; VTab_1AD6A8* vt; };

extern u8 D_0024CEE0[];
void func_001AA268(Node_1AD6A8* self);
void* func_0015C1C0(s32 k);

void func_001AD6A8(Node_1AD6A8* self)
{
    Obj_1AD6A8* o;
    VTab_1AD6A8* vt;

    func_001AA268(self);
    o = (Obj_1AD6A8*)func_0015C1C0(2);
    vt = o->vt;
    self->r = vt->fn((u8*)o + vt->delta, 1.0f, 1.0f);
    self->vt->fn(self, D_0024CEE0);
    self->flag = 0;
}

struct Obj_1ADC60;
typedef void (*VFn_1ADC60)(void* self, void* arg);
typedef void* (*FnA_1ADC60)(void* self, f32 a, f32 b);
struct Tbl_1ADC60 { u8 pad0[8]; s16 off; u8 pad1[2]; FnA_1ADC60 fn; };
struct Inner_1ADC60 { u8 pad0[0x4C]; Tbl_1ADC60* tbl; };
struct Obj_1ADC60 { VFn_1ADC60* vt; void* f4; u8 pad0[0x210 - 8]; void** f210; u8 pad1[0x4C]; void* f260; };

extern f32 D_00274448;
extern f32 D_0027444C;
extern u8 D_00274450[];
extern u8 D_0024CEF0[];

void func_001AA268(Obj_1ADC60* self);
void* func_0015C1C0(s32 k);
void* func_001B4688(s32 key);
void func_001AAB20(Obj_1ADC60* self, f32 a, f32 b);

void func_001ADC60(Obj_1ADC60* self)
{
    func_001AA268(self);
    Inner_1ADC60* in = (Inner_1ADC60*)self->f4;
    self->f4 = in->tbl->fn((u8*)in + in->tbl->off, D_00274448, D_0027444C);
    if (func_0015C1C0(2) != 0) {
        self->f210 = (void**)D_00274450;
        *self->f210 = func_0015C1C0(2);
    }
    self->f260 = func_001B4688(0x493);
    if (self->f260 != 0) {
        func_001AAB20(self, 366.75f, 165.75f);
    } else {
        self->vt[8](self, D_0024CEF0);
    }
}

struct Obj_1AE510 { u8 pad0[4]; void* f4; u8 f8[0x22C]; f32 f234; f32 f238; };
struct Inner_1AE510 { u8 pad0[8]; s32 f8; u8 pad1[0x3C]; f32 f48; };

extern u8 D_00273C50[];
extern u8 D_002739F0[];
extern u8 D_0024CF98[];
extern f32 D_002744A8;

void func_001AA268(Obj_1AE510* self);
void* func_0015C1C0(s32 k);
s32 func_001E1FD0(char* dst, const char* fmt, ...);
void func_0015C8B8(Obj_1AE510* h, f32 a, f32 b);
f32 func_0015C418(void* h, char* buf);
void func_0015C900(void* h);

void func_001AE510(Obj_1AE510* self)
{
    func_001AA268(self);
    self->f4 = func_0015C1C0(2);
    if ((u8*)self == D_00273C50) {
        func_001E1FD0((char*)self->f8, (const char*)D_0024CF98, 0x4C);
    } else if ((u8*)self == D_002739F0) {
        func_001E1FD0((char*)self->f8, (const char*)D_0024CF98, 0x4B);
    }
    func_0015C8B8((Obj_1AE510*)self->f4, D_002744A8, D_002744A8);
    self->f234 = func_0015C418(self->f4, (char*)self->f8);
    Inner_1AE510* in = (Inner_1AE510*)self->f4;
    self->f238 = (f32)in->f8 * in->f48;
    func_0015C900(self->f4);
}

struct Mixer_001AF5C8;
struct MixVt_001AF5C8 {
    u8 pad0[0x130];
    void (*hook)(Mixer_001AF5C8*, s32*);
    u8 pad1[0x144 - 0x134];
    void (*done)(Mixer_001AF5C8*, s32);
};
struct Mixer_001AF5C8 {
    MixVt_001AF5C8* vt;
    u8 pad4[0x554 - 4];
    s32 f554;
    s32 state;
    f32 f55C;
    u8 pad560[0x5B8 - 0x560];
    f32 f5B8;
    f32 f5BC;
    u8 pad5C0[0xAEC - 0x5C0];
    f32 fAEC;
    u8 padAF0[0xB04 - 0xAF0];
    f32 fB04;
    f32 fB08;
};

extern s32 D_002744D0;
extern f32 D_0026185C;
void func_001AEFA0(Mixer_001AF5C8* self, f32 a);
void func_001AF508();

void func_001AF5C8(Mixer_001AF5C8* self, f32 amount)
{
    s32 cmd;
    f32 v;
    f32 hi;
    f32 lo;

    func_001AEFA0(self, amount);
    v = self->fB04 + amount * self->fB08;
    hi = 1.0f;
    lo = 0.0f;
    if (v < lo)
        v = lo;
    else if (hi < v)
        v = hi;
    self->fB04 = v;
    if (D_002744D0)
        func_001AF508();
    cmd = self->state;
    switch (cmd) {
    case 0:
        if (self->f5B8 < D_0026185C - self->f55C)
            cmd = 1;
        if (self->vt->hook)
            self->vt->hook(self, &cmd);
        break;
    case 2:
        cmd = 3;
        if (self->vt->hook)
            self->vt->hook(self, &cmd);
        break;
    case 3:
        if (self->f5BC < D_0026185C - self->f55C) {
            if (self->f554 == 0) {
                cmd = 8;
                break;
            }
            if (self->f554 != 1)
                break;
            cmd = 4;
            if (self->vt->hook)
                self->vt->hook(self, &cmd);
            break;
        }
        if (self->vt->hook)
            self->vt->hook(self, &cmd);
        break;
    case 4:
        if (self->f5B8 < D_0026185C - self->f55C)
            cmd = 5;
        if (self->vt->hook)
            self->vt->hook(self, &cmd);
        break;
    case 1:
    case 5:
    case 6:
        if (self->vt->hook)
            self->vt->hook(self, &cmd);
        break;
    case 7:
        if (self->fAEC < D_0026185C - self->f55C)
            cmd = 8;
        else if (self->vt->hook)
            self->vt->hook(self, &cmd);
        break;
    case 8:
        break;
    }
    self->vt->done(self, cmd);
}

struct Info_1ACEE0 {
    u32 flags;
    u32 pad;
    f32 time;
};

extern s32 func_001E1FD0(char*, const char*, ...);
extern s32 func_001E2180(char*, const char*);
extern char D_0024CD88[];
extern char D_0024CD90[];
extern char D_0024CD98[];
extern char D_0024CDA0[];
extern char D_0024CDA8[];
extern char D_0024CDB0[];
extern char D_0024CDB8[];
extern char D_0024CDC0[];
extern char D_0024CDC8[];
extern char D_0024CDE0[];
extern char D_0024CDF8[];

void func_001ACEE0(char* buf, Info_1ACEE0* info, u32 mask)
{
    u32 flags = info->flags;
    *buf = 0;
    if (mask & 2) {
        buf += func_001E1FD0(buf, D_0024CD88, (flags & 2) ? D_0024CD90 : D_0024CD98);
    }
    if (mask & 4) {
        if (mask & 2) {
            *buf++ = ' ';
        }
        buf += func_001E1FD0(buf, D_0024CD88, (flags & 4) ? D_0024CDA0 : D_0024CDA8);
    }
    if (mask & 8) {
        u32 f8;
        if (mask & 6) {
            *buf++ = ' ';
        }
        f8 = flags & 8;
        buf += func_001E1FD0(buf, D_0024CDB0, f8 ? D_0024CDB8 : D_0024CDC0);
        if (f8) {
            f32 t = info->time;
            if (t < 1.0f) {
                (void)func_001E1FD0(buf, D_0024CDC8, (s32)(t * 10.0f));
            } else {
                s32 s = (s32)t;
                s32 m = s / 60;
                s32 r = s % 60;
                (void)func_001E1FD0(buf, D_0024CDE0, m, r);
            }
        }
        func_001E2180(buf, D_0024CDF8);
    }
}

struct Buf_1AD0D0 { s32 w[16]; };
struct Str_1AD0D0 { s32 w[16]; };
struct Idx_1AD0D0;
struct Obj_1AD0D0;
typedef void (*VFn_1AD0D0)(void* self, void* a);
struct Obj_1AD0D0 { VFn_1AD0D0* vtbl; };

extern u8 D_0024CE10[];
extern u8 D_0024CE18[];
extern u8 D_0024CD68[];

u32 func_001601D8(Idx_1AD0D0* idx);
void* func_00160148(Idx_1AD0D0* idx);
void func_001ACEE0(Buf_1AD0D0* buf, void* p, u32 n);
s32 func_001E2100(Buf_1AD0D0* buf);
void* func_001E2138(Str_1AD0D0* dst, void* src);
s32 func_001E1FD0(Str_1AD0D0* dst, const char* fmt, ...);

void func_001AD0D0(Obj_1AD0D0* self, s32 a1, s32 a2)
{
    Buf_1AD0D0 buf;
    Str_1AD0D0 str;
    u8* p;
    u32 packed;

    p = *(u8**)((u8*)&D_002623C0);
    p += a1 * 0x44C + 0x10;
    p += a2 * 0x78;
    packed = (a1 << 8) | a2;
    func_001ACEE0(&buf, p, func_001601D8((Idx_1AD0D0*)packed));
    if (func_001E2100(&buf)) {
        func_001E1FD0(&str, (const char*)D_0024CE10, func_00160148((Idx_1AD0D0*)packed),
                      func_001E2100(&buf) ? D_0024CE18 : D_0024CD68, &buf);
    } else {
        func_001E2138(&str, func_00160148((Idx_1AD0D0*)packed));
    }
    self->vtbl[8]((void*)self, &str);
}

struct Self_001AD7B0 {
    u8 pad0[0x21C];
    f32 f21C;
    f32 f220;
    u8 pad1[0x234 - 0x224];
    f32 f234;
    f32 f238;
};

struct Node_001AD7B0 {
    u8 pad0[0x8];
    s32 i8;
    u8 pad1[0x48 - 0x0C];
    f32 f48;
};

struct Buf_001AD7B0 { u8 pad[0x30]; };

extern f32 D_00261868;
extern u8 D_0024CEE8[];
extern u8 D_00262280[];

void func_001AA790(Self_001AD7B0* self);
f32 func_001EA408(f32 a);
f32 func_00205210(f32 x);
void func_0015C8B8(Node_001AD7B0* handle, f32 a, f32 b);
f32 func_0015C418(Node_001AD7B0* h, void* buf);
void func_00137228(Buf_001AD7B0* out, f32 x, f32 y);
void func_00137238(Buf_001AD7B0* out, f32 x, f32 y);
void func_00137248(Buf_001AD7B0* out, s32* value);
void func_00137260(Buf_001AD7B0* out, s32 flag);
void func_00137268(Buf_001AD7B0* out, s32 flag);
void func_0015C638(Node_001AD7B0* a, void* b, void* c, s32 d, void* e);
void func_0015C900(Node_001AD7B0* handle);

void func_001AD7B0(Self_001AD7B0* self)
{
    Buf_001AD7B0 buf;
    s32 mask = (s32)0xFF808080;
    func_001AA790(self);
    f32 half = 0.5f;
    f32 sc = func_00205210(func_001EA408(D_00261868 * 8.0f)) * half + half;
    Node_001AD7B0* h = (Node_001AD7B0*)func_0015C1C0(1);
    f32 s2 = sc * 0.1f + half;
    func_0015C8B8(h, s2, s2);
    f32 w = func_0015C418(h, D_0024CEE8);
    f32 ht = (f32)h->i8 * h->f48;
    func_00137228(&buf, self->f21C + 2.0f + self->f234 * half - w * half,
                  self->f220 + 14.0f + self->f238 * half - ht * half);
    func_00137238(&buf, w, ht);
    *(s32*)((u8*)&buf + 0x20) = mask;
    func_00137248(&buf, (s32*)((u8*)&buf + 0x20));
    func_00137260(&buf, 0);
    func_00137268(&buf, 0);
    func_0015C638(h, D_0024CEE8, &buf, 0, D_00262280);
    func_0015C900(h);
}

extern u8 D_0024CF90[];
extern u8 D_00274478[];
extern u8 D_00274484[];

struct Col_1ADFF0 { u8 col[4]; };
struct Handle_1ADFF0 { u8 raw[4]; };
struct Text_1ADFF0 { u8 raw[0x200]; };
struct Obj_1ADFF0 { u8 raw[0xB0]; };
struct Loc_1ADFF0 { struct Col_1ADFF0 col; u8 pad[12]; struct Obj_1ADFF0 obj; };
struct Node_1ADFF0 {
    s32 pad0;
    struct Handle_1ADFF0 *handle;
    struct Text_1ADFF0 text;
    struct Col_1ADFF0 color;
    f32 scale;
    u8 pad1[0x50];
    s32 flag;
    s32 index;
};

s32 func_001E1FD0(struct Text_1ADFF0 *dst, const char *fmt, ...);
void func_001E2138(struct Text_1ADFF0 *dst, void *src);
void func_0015C8B8(struct Handle_1ADFF0 *handle, f32 a, f32 b);
void func_0015DB28(struct Obj_1ADFF0 *obj, struct Text_1ADFF0 *dst, struct Handle_1ADFF0 *handle);
f32 func_0015E1F0(struct Obj_1ADFF0 *obj);
f32 func_0015E1B0(struct Obj_1ADFF0 *obj, f32 a);
void func_001AAB20(struct Node_1ADFF0 *self, f32 x, f32 y);
void func_0015C900(struct Handle_1ADFF0 *handle);

void func_001ADFF0(struct Node_1ADFF0 *self)
{
    struct Loc_1ADFF0 loc;
    f32 y;

    if (self->flag != 0) {
        loc.col.col[0] = 0x6F;
        loc.col.col[1] = 0x6F;
        loc.col.col[2] = 0x6F;
        loc.col.col[3] = 0xFF;
        self->color = loc.col;
        u8 *tbl = D_00274478;
        s32 off = self->index ? 4 : 0;
        func_001E1FD0(&self->text, (const char *)D_0024CF90, *(s32 *)(tbl + off), *(s32 *)(tbl + 8));
    } else {
        loc.col.col[0] = 0x6F;
        loc.col.col[1] = 0x1F;
        loc.col.col[2] = 0x1F;
        loc.col.col[3] = 0xFF;
        self->color = loc.col;
        func_001E2138(&self->text, (void *)((s32 *)D_00274484)[0]);
    }
    func_0015C8B8(self->handle, self->scale, self->scale);
    func_0015DB28(&loc.obj, &self->text, self->handle);
    {
        f32 x = func_0015E1F0(&loc.obj);
        y = func_0015E1B0(&loc.obj, 0.0f);
        func_001AAB20(self, x, y);
    }
    func_0015C900(self->handle);
}

struct Buf_1AD1E8;
struct Self_1AD1E8 { void** vtbl; };
struct Sub_1AD1E8 {
    u8 pad0[0x438];
    s32 f438;
    s32 f43C;
    s32 f440;
    u8 pad444[0x8];
};
struct Mgr_1AD1E8 {
    u8 pad0[0x10];
    Sub_1AD1E8 ents[1];
};

extern char* D_00274430[];
extern char D_0024CE80[];
extern char D_0024CEA0[];
extern char D_0024CEC0[];

void func_00160208(s32 key, s32* a1, s32* a2, s32* a3);
char* func_001E2138(Buf_1AD1E8* dst, const char* src);
s32 func_001E2100(void* p);
s32 func_001E1FD0(Buf_1AD1E8* dst, const char* fmt, ...);

void func_001AD1E8(Self_1AD1E8* self, s32 idx)
{
    char buf[0x200];
    s32 a, b, c;
    func_00160208(idx, &a, &b, &c);
    Sub_1AD1E8* s1 = &(*(Mgr_1AD1E8**)&D_002623C0)->ents[idx];
    func_001E2138((Buf_1AD1E8*)buf, D_00274430[idx]);
    char* d = buf + func_001E2100(buf);
    if (a)
        d += func_001E1FD0((Buf_1AD1E8*)d, D_0024CE80, s1->f438, a);
    if (b)
        d += func_001E1FD0((Buf_1AD1E8*)d, D_0024CEA0, a ? ((char*)&D_0024CE18) : ((char*)&D_0024CD68), s1->f43C, b);
    if (c)
        func_001E1FD0((Buf_1AD1E8*)d, D_0024CEC0, (a || b) ? ((char*)&D_0024CE18) : ((char*)&D_0024CD68), s1->f440, c);
    ((void (*)(Self_1AD1E8*, char*))self->vtbl[8])(self, buf);
}

struct Table_001AEA08 {
    s32 pad_00;
};

extern f32 D_00261868;
extern s8* D_002744B0;

u32 func_001E2100(Table_001AEA08* t);

s8 func_001AEA08(void)
{
    s32 scaled = (s32)(D_00261868 * 5.0f);
    u32 divisor = func_001E2100((Table_001AEA08*)D_002744B0);
    return D_002744B0[(u32)scaled % divisor];
}
