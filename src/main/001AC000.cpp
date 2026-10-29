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
