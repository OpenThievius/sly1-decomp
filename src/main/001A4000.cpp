// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_1A5DD8 { u8 pad[0x560]; void* child; };

void func_001A76A0(void* child, int flag);

void func_001A5DD8(void* unused, Obj_1A5DD8* obj)
{
    func_001A76A0(obj->child, 1);
}

struct Obj_1A6480 { u8 pad[0x620]; s32 count; };

void* func_001A6480(void* self)
{
    Obj_1A6480* obj = (Obj_1A6480*)self;
    return (u8*)self + (obj->count * 0xC0 + 0x3E0);
}

extern u8 D_0026B7E8[];

void func_001BAC30(void* self);
void func_00124DF8(void* self, int idx, void* table);
void func_00159478(void* sub, void* self);

void func_001A64F8(u8* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 6, D_0026B7E8);
    func_00159478(self + 0x5AC, self);
}

struct Blob8_1A6540 { u8 b[8]; };

void func_001BA130(void* self);

void func_001A6540(u8* self)
{
    Blob8_1A6540 tmp = *(Blob8_1A6540*)(self + 0x5B0);
    func_001BA130(self);
    *(Blob8_1A6540*)(self + 0x5B0) = tmp;
}

typedef void (*Fn_1A6588)(void* self);

void func_00124A48(void* self);
void func_001A6BE0(void* self, int flag);

void func_001A6588(void* self)
{
    func_00124A48(self);
    func_001A6BE0(self, 0);
    Fn_1A6588* vt = *(Fn_1A6588**)self;
    vt[7](self);
}

struct Node_1A6F28 { void* flags; struct Node_1A6F28* next; s32 pad8; void* data; };

s32 func_001300E8(void* self, int kind);

void* func_001A6F28(u8* self)
{
    Node_1A6F28* cur = *(Node_1A6F28**)(*(u8**)(self + 0x480));
    while (cur) {
        if (cur->flags != 0 && func_001300E8(cur->data, 0x43) != 0)
            return cur->data;
        cur = cur->next;
    }
    return 0;
}

extern u8 D_0026B830[];

void func_001BAC30(void* self);
void func_00124DF8(void* self, int idx, void* table);
void func_00159478(void* sub, void* self);

void func_001A7008(u8* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 1, D_0026B830);
    func_00159478(self + 0x574, self);
}

struct Blob8_1A7050 { u8 b[8]; };

void func_001BA130(void* self);

void func_001A7050(u8* self)
{
    Blob8_1A7050 tmp = *(Blob8_1A7050*)(self + 0x5A0);
    func_001BA130(self);
    *(Blob8_1A7050*)(self + 0x5A0) = tmp;
}

extern u8 D_0026B840[];

struct Blob8_1A7098 { u8 b[8]; };
struct Obj_1A7098 { u8 pad[0x560]; void* a560; s32 a564; u8 pad2[0x578 - 0x568]; void* a578; };
typedef void (*Fn_1A7098)(void* self);

void func_00124A48(void* self);
void func_00124DF8(void* self, int idx, void* table);
void func_001A7480(void* self, int flag);
s32 func_001B6290(void* a, void* b, s32 c, s32 d);

void func_001A7098(u8* self)
{
    Obj_1A7098* obj = (Obj_1A7098*)self;
    func_00124A48(self);
    func_00124DF8(self, 1, D_0026B840);
    if (obj->a578 != 0) {
        *(Blob8_1A7098*)(self + 0x57C) = *(Blob8_1A7098*)((u8*)obj->a578 + 0x2DC);
    }
    if (obj->a560 != 0) {
        obj->a564 = func_001B6290(obj->a560, self, -1, 0);
    }
    func_001A7480(self, 0);
    Fn_1A7098* vt = *(Fn_1A7098**)self;
    vt[7](self);
}

extern f32 D_00261860;
extern u8 D_0026B850[];

void func_001B9338(void* self);
void func_00189378(void* sub, int zero, void* out);
void func_001B9D10(void* self, void* out, void* data, f32 scale);

struct Obj_1A7230 { u8 pad[0x18]; s32 a18; };

void func_001A7230(u8* self)
{
    func_001B9338(self);
    if (((Obj_1A7230*)self)->a18 == 0) {
        u8 buf[0x30];
        func_00189378(self + 0x110, 0, buf);
        func_001B9D10(self, buf, D_0026B850, D_00261860);
    }
}

struct Obj_1A7290 { u8 pad[0x98]; f32 a98; };

void func_001A7290(void* unused, Obj_1A7290* obj)
{
    obj->a98 = obj->a98 * 0.6f;
}

void func_001A4868(u8* self, s32 value)
{
    *(s32*)(self + 0x2D8) = value;
}

typedef void (*VFn_1A7798)(void* self);

void func_00124A48(void* self);
void* func_0015A838(void* a, int b, int c, void* d);
void func_001A7998(void* self, int flag);

void func_001A7798(void* self)
{
    u8* s = (u8*)self;
    func_00124A48(self);
    if (*(s32*)(s + 0x558) == 0) {
        VFn_1A7798* vt = *(VFn_1A7798**)self;
        vt[7](self);
        return;
    }
    *(void**)(s + 0x55C) = func_0015A838(*(void**)(s + 0x14), 0x101, 0x59, *(void**)(s + 0x34));
    func_001A7998(self, 0);
}

struct Vec_1A7D18 { s32 count; s32 pad; f32 x; };

extern s32 D_002623C0;

int func_001A7EE8(void* a);
void func_001A7D98(void* self, int mode);

void func_001A7D18(void* self, Vec_1A7D18* p, f32 f)
{
    u8* s = (u8*)self;
    if (*(s32*)(s + 0xC) != 0 && p->count > 0) {
        if (func_001A7EE8((void*)D_002623C0) != 0) {
            *(f32*)(s + 0x18) = f;
            *(Vec_1A7D18**)(s + 0x10) = p;
            *(s32*)(s + 0x14) = 0;
            f32 x = p->x;
            *(s32*)(s + 0xC) = -1;
            *(f32*)(s + 0x1C) = x;
            func_001A7D98(self, 2);
        }
    }
}

typedef void (*VFn1_1A5F78)(void* self);

struct Obj_1A5F78 {
    VFn1_1A5F78* vtbl;
    u8 pad0[0x18 - 4];
    void* a18;
    u8 pad1[0x55C - 0x1C];
    Obj_1A5F78* a55C;
    void* a560;
};

struct Self_1A5F78 {
    u8 pad0[0x35C];
    u8 a35C[0xC];
    u8 a368[0xC];
    u8 a374[0xC];
    s32 a380;
    u8 a384[0xC];
    u8 a390[0xC];
    s32 a39C;
    u8 a3A0[0xC];
    u8 a3AC[0x14];
    u8 pad1[0x628 - 0x3C0];
    s32 a628;
    u8 pad2[0x638 - 0x62C];
    f32 a638;
    f32 a63C;
    f32 a640;
};

extern f32 D_0026185C[];

void func_00152600(void* a, void* b);
void func_00152470(void* a, void* b);
void func_001A76A0(void* child, s32 flag);
void func_001A5D50(void* self, void* obj);
s32 func_001A6238(void* self, void* child);
f32 func_001EAAE0(f32 a, f32 b);

void func_001A5F78(Self_1A5F78* self, Obj_1A5F78* obj)
{
    func_00152600(self->a384, obj);
    func_00152470(self->a390, obj);
    if (obj->a560 != 0) {
        func_00152600(self->a3AC, obj->a560);
        func_00152470(self->a3A0, obj->a560);
        func_001A76A0(obj->a560, 0);
    }
    Obj_1A5F78* child = obj->a55C;
    if (child != 0) {
        if (child->a18 == obj) {
            func_001A5D50(self, obj);
        }
        func_00152600(self->a35C, child);
        func_00152470(self->a368, child);
        if (func_001A6238(self, child) == 0) {
            child->a55C = 0;
        }
    }
    obj->a560 = 0;
    obj->a55C = 0;
    obj->vtbl[7](obj);
    if (self->a39C == self->a628) {
        f32 r = func_001EAAE0(self->a638, self->a63C);
        self->a640 = D_0026185C[0] + r;
    }
    self->a39C = self->a39C - 1;
}

struct Obj_1A6168 {
    u8 pad[0x55C];
    Obj_1A6168* a55C;
};

void func_00152600(void* a, void* b);
void func_00152470(void* a, void* b);
s32 func_001A6238(void* self, void* child);
void func_001A6BE0(void* self, s32 mode);
s32 func_001A6090(void* self, void* child);

void func_001A6168(u8* self, Obj_1A6168* obj, Obj_1A6168* node)
{
    Obj_1A6168* cur = obj->a55C;
    if (cur != 0 && cur == node) {
        return;
    }
    Obj_1A6168* s2 = node->a55C;
    obj->a55C = node;
    node->a55C = obj;
    if (s2 == 0) {
        func_00152600(self + 0x368, node);
        func_00152470(self + 0x35C, node);
    }
    if (cur != 0) {
        func_00152600(self + 0x35C, cur);
        func_00152470(self + 0x368, cur);
        cur->a55C = 0;
        func_001A6238(self, cur);
    }
    if (s2 != 0) {
        s2->a55C = 0;
        func_001A6BE0(s2, 2);
        if (func_001A6090(self, s2) != 0) {
            func_001A6BE0(s2, 3);
        }
    }
}

struct Obj_1A7520 { u8 pad[0x550]; s32 state; };

void func_001B7968(void* self);

void func_001A7520(Obj_1A7520* self)
{
    func_001B7968(self);
    self->state = -1;
}

struct Ctrl_1A4258 { u8 pad0[0x614]; s32 mode614; u8 pad1[0x0C]; f32 level624; };

s32 func_001A4258(Ctrl_1A4258* self)
{
    s32 r = self->mode614;
    switch (r) {
    case 0:
        if (0.8f <= self->level624) {
            r = 1;
        }
        break;
    case 1:
        if (self->level624 < 0.8f) {
            r = 0;
        }
        break;
    }
    return r;
}

struct Ctrl_1A44E8 { u8 pad0[0x618]; f32 level618; };

extern f32 D_00261860;
extern u8 D_0026B7D8[];

void func_001B9338(Ctrl_1A44E8* self);
void func_001892A0(f32* out, f32 unused, f32 value);
void func_001B9D10(Ctrl_1A44E8* self, f32* buf, u8* table, f32 scale);

void func_001A44E8(Ctrl_1A44E8* self)
{
    f32 buf[12];
    func_001B9338(self);
    func_001892A0(buf, self->level618, 0.0f);
    func_001B9D10(self, buf, D_0026B7D8, D_00261860);
}

void func_001A7D18(void* self, void* entry);
extern u8 D_0026B8B0[];

void func_001A7CE8(void* self, s32 index)
{
    func_001A7D18(self, D_0026B8B0 + index * 0x104);
}

s32 func_002049E8(void* owner, s32 channel, u8* bytes);

struct Pair_001A7E40 { u8 pad0[4]; void* owner; s32 channel; };

void func_001A7E40(Pair_001A7E40* self)
{
    u8 bytes[2];
    bytes[0] = 0;
    bytes[1] = 0;
    func_002049E8(self->owner, self->channel, bytes);
}

struct Obj_1A45B8 { u8 pad0[0x88]; f32 ratio; u8 pad1[8]; f32 value; };

s32 func_00128230(void* ctx);

void func_001A45B8(void* ctx, Obj_1A45B8* obj)
{
    if (func_00128230(ctx) != 0) {
        return;
    }
    if (0.7f < obj->ratio) {
        obj->value = 20.0f;
    }
}

s32 func_001A4710(void)
{
    return 0;
}

struct Obj_1A4858 { u8 pad0[0x2D0]; s32 field2D0; };

void func_001A4858(Obj_1A4858* obj, s32 value)
{
    obj->field2D0 = value;
}

struct Obj_1A4860 { u8 pad0[0x2D4]; s32 field2D4; };

void func_001A4860(Obj_1A4860* obj, s32 value)
{
    obj->field2D4 = value;
}

extern s32 D_0026C3DC;

void func_001A7E70(void)
{
    if (D_0026C3DC == 0) {
        D_0026C3DC = 1;
    }
}

extern s32 D_0026C3DC;

struct Ctx_001A7E90 {
    u8 pad[0x19EC];
    s32 flags;
};

void func_001A7E90(Ctx_001A7E90* ctx)
{
    s32 v = D_0026C3DC;
    if (v == 2) {
        goto clear;
    }
    if (v < 3) {
        return;
    }
    if (v == 3) {
        goto set;
    }
    return;
clear:
    ctx->flags &= 0xFFFFFFDF;
    return;
set:
    ctx->flags |= 0x20;
}

extern s32 D_0026C3DC;

struct Ctx_001A7EE8 {
    u8 pad[0x19EC];
    s32 flags;
};

s32 func_001A7EE8(Ctx_001A7EE8* ctx)
{
    s32 v = D_0026C3DC;
    if (v == 1) {
        goto tail;
    }
    if (v < 2) {
        if (v == 0) {
            goto zero;
        }
        goto tail;
    }
    if (v == 2) {
        goto one;
    }
    if (v == 3) {
        goto zero;
    }
    goto tail;
one:
    return 1;
zero:
    return 0;
tail:
    return ((ctx->flags >> 5) ^ 1) & 1;
}

struct Obj_1A4870 { u8 pad[0x2DC]; s32 value; };

void func_001A4870(Obj_1A4870* obj, s32 value)
{
    obj->value = value;
}

struct List_1A4878 { u8 pad[0x2E0]; s32 count; s32 items[1]; };

void func_001A4878(List_1A4878* list, s32 value)
{
    s32 n = list->count;
    list->items[n] = value;
    list->count = n + 1;
}

typedef void (*VFn_1A4B30)(void* self);

struct Kin_1A4B30 {
    f32 pos;
    f32 vel;
    f32 acc;
};

struct Blend_1A4B30 {
    VFn_1A4B30* vtbl;
    u8 pad0[0x3D0 - 4];
    Kin_1A4B30 kin;
    u8 pad1[0x3E0 - 0x3DC];
    f32 a3e0[48];
    f32 b4a0[48];
    f32 out560[48];
    u8 pad2[0x64C - 0x620];
    s32 state64c;
};

struct Ctx_1A4B30 {
    u8 pad0[0xC];
    f32 dt;
};

extern Ctx_1A4B30* D_002623C8;
extern f32 D_00275C60[];

void func_00124A48(void* self);
s32 func_001A4898(void);
void func_001A5760(void* self, f32 t);
void func_001A4EF0(void* self, void* p);

void func_001A4B30(void* self)
{
    Blend_1A4B30* s = (Blend_1A4B30*)self;
    func_00124A48(self);
    if (s->state64c != func_001A4898()) {
        s->vtbl[7](self);
    } else {
        Kin_1A4B30* k = &s->kin;
        f32 dt = D_002623C8->dt;
        f32 v = k->pos + dt * (k->vel + dt * k->acc);
        f32 lo = D_00275C60[0];
        f32 hi = D_00275C60[1];
        f32 t;
        if (v < lo) {
            t = lo;
        } else if (hi < v) {
            t = hi;
        } else {
            t = v;
        }
        f32 u = 1.0f - t;
        f32* pa = s->a3e0;
        f32* pb = s->b4a0;
        f32* po = s->out560;
        for (u32 i = 0; i < 48; i++) {
            *po++ = u * *pa++ + t * *pb++;
        }
        func_001A5760(self, 0.0f);
        func_001A4EF0(self, 0);
    }
}

typedef void (*VFn_1A4D60)(void* self);

struct Mgr_1A4D60 {
    VFn_1A4D60* vtbl;
};

struct Node_1A4D60 {
    u8 pad0[0x650];
    s32 mode650;
};

extern Mgr_1A4D60 D_0026D0C8;

void* func_001E9970(void* zero);

void func_001A4D60(void* self)
{
    Node_1A4D60* n = (Node_1A4D60*)self;
    void* p = 0;
    if (n->mode650 == 2) {
        p = func_001E9970(p);
    }
    if (p != 0) {
        D_0026D0C8.vtbl[14](&D_0026D0C8);
    } else {
        D_0026D0C8.vtbl[15](&D_0026D0C8);
    }
}

struct Obj_1A5C38 { u8 pad[0x560]; void* child; };

void func_00152600(void* table, void* node);
void func_00152470(void* table, void* node);
void func_001A76A0(void* node, s32 flag);

void func_001A5C38(u8* self, Obj_1A5C38* obj)
{
    func_00152600(self + 0x3AC, obj->child);
    func_00152470(self + 0x3A0, obj->child);
    func_001A76A0(obj->child, 0);
    obj->child = 0;
}

extern u8 D_0026B888[];

void func_001BAC30(void* self);
void func_00124DF8(void* self, int idx, void* table);

void func_001A7550(u8* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 1, D_0026B888);
}

struct S_1A7698 { u8 pad[0x550]; s32 value; };
s32 func_001A7698(S_1A7698* p) { return p->value; }

struct Pk8_1A7588 { u64 v; } __attribute__((packed));
struct Obj_1A7588 { u8 pad0[0x568]; Pk8_1A7588 f568; };

void func_001BA130(void* self);

void func_001A7588(Obj_1A7588* self)
{
    Pk8_1A7588 tmp;
    tmp = self->f568;
    func_001BA130(self);
    self->f568 = tmp;
}

struct Node_1A75D0 { u8 pad0[0x1C]; Node_1A75D0* f1C; };
struct Obj_1A75D0 { u8 pad0[0x34]; Node_1A75D0* f34; u8 pad1[0x55C - 0x38]; void* f55C; void* f560; Node_1A75D0* f564; };

void func_00124A48(void* self);
s32 func_001300E8(void* node, s32 kind);
void func_001A76A0(void* node, s32 flag);

void func_001A75D0(Obj_1A75D0* self)
{
    s32 scratch[4];
    (void)scratch;
    func_00124A48(self);
    if (self->f55C != 0) {
        self->f560 = (void*)func_001B6290(self->f55C, self, -1, 1);
    }
    Node_1A75D0* n = self->f34;
    while (n != 0) {
        if (func_001300E8(n, 0x7E) != 0) {
            self->f564 = n;
            break;
        }
        n = n->f1C;
    }
    func_001A76A0(self, 0);
}

struct Obj_1A7648 { u8 pad0[0x550]; s32 f550; };

void func_001B93F8(void* self);
s32 func_001A7698(void* self);
void func_001A76A0(void* node, s32 flag);

void func_001A7648(Obj_1A7648* self)
{
    func_001B93F8(self);
    s32 v;
    while ((v = func_001A7698(self)) != self->f550) {
        func_001A76A0(self, v);
    }
}

struct Obj_1A7708 { u8 pad0[0x550]; s32 f550; };

void func_001B7968(void* self);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);

void func_001A7708(Obj_1A7708* self)
{
    func_001B7968(self);
    self->f550 = -1;
    func_001B9AE0(self, 3, 0, 3, 0);
}

f32 func_001EAAE0(f32 a, f32 b);
void func_001A5760(void* self, f32 t);
void func_00152600(u8* a, void* b);
void func_00152470(u8* a, void* b);
s32 func_001A6090(void* self, void* child);
void func_001A6BE0(void* self, s32 mode);

typedef void (*VFnV_1A5B28)(void* self);
struct Obj_1A5B28 {
    VFnV_1A5B28* vtbl;
    u8 pad[0x55C - 4];
    Obj_1A5B28* p55C;
};

struct Self_1A5B28 {
    u8 pad0[0x35C];
    u8 a35C[0x368 - 0x35C];
    u8 a368[0x374 - 0x368];
    u8 a374[0x380 - 0x374];
    s32 i380;
    u8 pad1[0x3B8 - 0x384];
    s32 i3B8;
    u8 pad2[0x3C4 - 0x3BC];
    s32 i3C4;
    u8 pad3[0x624 - 0x3C8];
    s32 i624;
    u8 pad4[0x62C - 0x628];
    f32 f62C;
    f32 f630;
    f32 f634;
};

void func_001A5B28(Self_1A5B28* self, Obj_1A5B28* obj)
{
    s32 n = self->i3C4 + 1;
    f32 x = (f32)self->i3B8;
    self->i3C4 = n;
    func_001A5760(self, (f32)n / x);
    if (obj->p55C != 0) {
        func_00152600(self->a35C, obj);
    } else {
        func_00152600(self->a368, obj);
    }
    func_00152470(self->a374, obj);
    if (obj->p55C != 0) {
        if (func_001A6090(self, obj->p55C) != 0) {
            func_001A6BE0(obj->p55C, 3);
        } else {
            obj->p55C->p55C = 0;
            func_001A6BE0(obj->p55C, 2);
        }
    }
    obj->p55C = 0;
    obj->vtbl[7](obj);
    if (self->i380 == self->i624) {
        f32 t = func_001EAAE0(self->f62C, self->f630);
        self->f634 = D_0026185C[0] + t;
    }
    self->i380 = self->i380 - 1;
}

f32 func_001EAAE0(f32 a, f32 b);
void func_001ED650(void* self, f32 x, f32 y, f32 z);

struct Self_1A63F8 { u8 pad[0x348]; f32 f348; f32 f34C; };
struct Dst_1A63F8 { u8 pad[0x574]; f32 f574; };

void func_001A63F8(Self_1A63F8* self, Dst_1A63F8* b)
{
    f32 r0 = func_001EAAE0(0.0f, 6.2831855f);
    f32 r1 = func_001EAAE0(0.0f, self->f348);
    func_001ED650(&b->pad[0x570], r0, r1, 0.0f);
    b->f574 = b->f574 * self->f34C;
}

extern f32 D_00275C60[];

struct Vec3_1A7128 { f32 x; f32 y; f32 z; };

void func_001B93F8(void* self);
s32 func_001A7420(void* self);
void func_001A7480(void* self, int flag);
void func_00155FA0(void* x);
void func_00155F90(void* x);

void func_001A7128(u8* self)
{
    func_001B93F8(self);
    s32 n;
    while ((n = func_001A7420(self)) != *(s32*)(self + 0x550)) {
        func_001A7480(self, n);
    }
    void* sub = *(void**)(self + 0x578);
    if (sub != 0) {
        f32 t = -*(f32*)(self + 0x158);
        if (9.99999975e-05f < t) {
            func_00155FA0(sub);
            Vec3_1A7128* v = (Vec3_1A7128*)(self + 0x590);
            f32 p = v->x + t * (v->y + t * v->z);
            f32 lo = D_00275C60[0];
            f32 hi = D_00275C60[1];
            f32 x;
            if (p < lo) {
                x = lo;
            } else if (hi < p) {
                x = hi;
            } else {
                x = p;
            }
            f32 a = *(f32*)(self + 0x57C) * x;
            f32 b = *(f32*)(self + 0x580) * x;
            u8* o = *(u8**)(self + 0x578);
            *(f32*)(o + 0x2DC) = a;
            *(f32*)(o + 0x2E0) = b;
        } else {
            func_00155F90(sub);
        }
    }
}


s32 func_001A7420(u8* self)
{
    s32 v = *(s32*)(self + 0x550);
    if (v > 0) {
        if (v >= 9) {
            if (v == 9) {
                goto zero;
            }
            goto end;
        }
        f32 t = D_0026185C[0] - *(f32*)(self + 0x554);
        if (*(f32*)(self + 0x56C) < t) {
            v -= 1;
        }
        goto end;
    }
    goto end;
zero:
    v = 0;
end:
    return v;
}

extern u8 D_0026B8A0[];

void func_001BAC30(void* self);
void func_00124DF8(void* self, int idx, void* table);
void func_00159478(void* sub, void* self);

void func_001A7750(u8* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 1, D_0026B8A0);
    func_00159478(self + 0x568, self);
}

struct Q_1A7AA0 { u8 pad[0x34]; f32 f34; };
struct P_1A7AA0 { u8 pad0[0x8]; Q_1A7AA0* q; u8 pad1[0x8]; f32 f14; };
struct Obj_1A7AA0 { u8 pad0[0x550]; s32 mode; u8 pad1[0x10]; P_1A7AA0* p; };

s32 func_001A7AA0(Obj_1A7AA0* self)
{
    s32 mode = self->mode;
    s32 r = mode;
    P_1A7AA0* p;
    s32* g;
    s32 bits;
    if (mode == 1) {
        goto acc;
    }
    if (mode < 2) {
        goto out;
    }
    if (mode == 2) {
        goto flags;
    }
    goto out;
acc:
    p = self->p;
    if (p == 0) {
        goto two;
    }
    if (!(p->q->f34 <= p->f14)) {
        goto flags;
    }
two:
    r = 2;
flags:
    g = *(s32**)&D_002623C8;
    bits = *g;
    r = (bits & 2) ? 3 : r;
out:
    return r;
}

void func_00192230(void* self, s32 code, void* rec);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_00155FA0(void* self);

struct Rec_1A43C8 { u8 pad[8]; s32 kind; };
struct Self_1A43C8 {
    u8 pad[0x65C];
    void* p65C;
    void* p660;
    u8 pad2[0x20];
    void* p684;
    s32 i688;
};

void func_001A43C8(Self_1A43C8* self, s32 code, Rec_1A43C8* rec)
{
    func_00192230(self, code, rec);
    if (code == 5) {
        goto code5;
    }
    if (code != 0x13) {
        return;
    }
    if (rec->kind == 0x295) {
        goto kind295;
    }
    if (rec->kind == 0x296) {
        goto kind296;
    }
    return;
kind295:
    func_001BFCD8(0x152, 0, 0, (s32)((u8*)self + 0x140), 12000.0f, 8000.0f, 0.5f, 0.0f, 0.0f, 0, 0);
    func_00155FA0(self->p65C);
    return;
kind296:
    func_001BFCD8(0x152, 0, 0, (s32)((u8*)self + 0x140), 12000.0f, 8000.0f, 0.5f, 0.0f, 0.0f, 0, 0);
    func_00155FA0(self->p660);
    return;
code5:
    if (rec == self->p684) {
        self->i688 = 1;
    }
}

f32 func_001EAAE0(f32 a, f32 b);
void func_00152600(u8* a, void* b);
void func_00152470(u8* a, void* b);
void func_001A76A0(void* node, s32 flag);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

typedef void (*VFnV_1A5DF8)(void* self);
typedef void (*VFnI_1A5DF8)(void* self, s32 arg);
struct Obj_1A5DF8 {
    VFnV_1A5DF8* vtbl;
    u8 pad[0x55C - 4];
    Obj_1A5DF8* p55C;
    Obj_1A5DF8* p560;
};

struct Self_1A5DF8 {
    u8 pad0[0x35C];
    u8 a35C[0x374 - 0x35C];
    u8 a374[0x380 - 0x374];
    s32 i380;
    u8 pad1[0x384 - 0x384];
    u8 a384[0x390 - 0x384];
    u8 a390[0x39C - 0x390];
    s32 i39C;
    u8 a3A0[0x3AC - 0x3A0];
    u8 a3AC[0x3C0 - 0x3AC];
    s32 i3C0;
    u8 pad2[0x624 - 0x3C4];
    s32 i624;
    s32 i628;
    f32 f62C;
    f32 f630;
    f32 f634;
    f32 f638;
    f32 f63C;
    f32 f640;
};

void func_001A5DF8(Self_1A5DF8* self, Obj_1A5DF8* obj)
{
    self->i3C0 = self->i3C0 + 1;
    func_00152600(self->a35C, obj->p55C);
    func_00152470(self->a374, obj->p55C);
    func_00152600(self->a384, obj);
    func_00152470(self->a390, obj);
    func_00152600(self->a3AC, obj->p560);
    func_00152470(self->a3A0, obj->p560);
    {
        Obj_1A5DF8* p = obj->p55C;
        ((VFnI_1A5DF8*)p->vtbl)[25](p, 0);
    }
    {
        Obj_1A5DF8* q = obj->p55C;
        q->vtbl[7](q);
    }
    obj->vtbl[7](obj);
    func_001A76A0(obj->p560, 0);
    obj->p560 = 0;
    obj->p55C->p55C = 0;
    obj->p55C = 0;
    if (self->i380 == self->i624) {
        f32 t = func_001EAAE0(self->f62C, self->f630);
        self->f634 = D_0026185C[0] + t;
    }
    self->i380 = self->i380 - 1;
    if (self->i39C == self->i628) {
        f32 t2 = func_001EAAE0(self->f638, self->f63C);
        self->f640 = D_0026185C[0] + t2;
    }
    self->i39C = self->i39C - 1;
    func_001BFCD8(0x51, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
}


struct __attribute__((aligned(16))) Quad_1A72B0 { s32 a; s32 b; f32 f; s32 d; };

struct Msg_1A72B0 {
    s32 kind;
    u8 pad[0xC];
    Quad_1A72B0 q10;
    Quad_1A72B0 q20;
    u8 pad2[0x20];
};

typedef void (*Fn_1A72B0)(void* self, void* msg);

void func_001A7480(void* self, int flag);
void func_001BFCD8(s32 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void* a4, void* a5);

s32 func_001A72B0(u8* self, u8* p)
{
    s32 st;

    if ((*(s32*)(p + 0xC) & 0x10) == 0) {
        goto done;
    }
    if (*(s32*)(self + 0x18) != 0) {
        goto done;
    }
    st = *(s32*)(self + 0x550);
    if (st == 9) {
        goto done;
    }
    if (D_0026185C[0] < *(f32*)(self + 0x554) + *(f32*)(self + 0x570)) {
        goto done;
    }
    st += 1;
    if (st >= *(s32*)(self + 0x568)) {
        func_001A7480(self, 9);
        void* obj = *(void**)(self + 0x574);
        if (obj != 0) {
            Msg_1A72B0 msg;
            msg.q10 = *(Quad_1A72B0*)(p + 0x30);
            f32 f = msg.q10.f + 1000.0f;
            msg.kind = 6;
            msg.q20 = *(Quad_1A72B0*)(p + 0x20);
            msg.q10.f = f;
            Fn_1A72B0* vt = *(Fn_1A72B0**)obj;
            vt[31](obj, &msg);
        }
        func_001BFCD8(0x23, 0, 0, p + 0x20, 12000.0f, 8000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    } else {
        func_001A7480(self, st);
        func_001BFCD8(0x14F, 0, 0, p + 0x20, 12000.0f, 8000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
done:
    return *(s32*)(p + 0xC) != 0;
}

extern s32 D_0026B898[];

void func_001B6628(void* a, s32 b);
void func_001B64D8(void* a, s32 b);

void func_001A76A0(void* self_, s32 idx)
{
    u8* self = (u8*)self_;
    s32 old = *(s32*)(self + 0x550);
    if (old == idx) return;
    *(s32*)(self + 0x550) = idx;
    void* child = *(void**)(self + 0x560);
    f32 d = D_0026185C[0];
    *(f32*)(self + 0x554) = d;
    if (child == 0) return;
    s32 v = D_0026B898[idx];
    if (old == -1) func_001B6628(child, v);
    else func_001B64D8(child, v);
}

struct Quad_1A7998 { s32 a, b, c, d; } __attribute__((aligned(16)));
struct Buf_1A7998 { s32 n; u8 pad[0x1C]; Quad_1A7998 q; u8 tail[0x20]; };
typedef void (*FnP_1A7998)(void* self, void* arg);
typedef void (*FnI_1A7998)(void* self, s32 arg);


void func_0012E760(void* p);
void func_0012C7B0(void* a, void* b, s32 c, void* d, f32 x, f32 y);

void func_001A7998(void* self_, s32 idx)
{
    u8* self = (u8*)self_;
    if (*(s32*)(self + 0x550) != idx) {
        if (*(void**)(self + 0x564) != 0) {
            func_0012E760(*(void**)(self + 0x564));
            *(void**)(self + 0x564) = 0;
        }
        *(s32*)(self + 0x550) = idx;
        void* s2 = 0;
        *(f32*)(self + 0x554) = D_0026185C[0];
        switch (idx) {
        case 1: {
            void* a2 = *(void**)(self + 0x568);
            s2 = *(void**)(self + 0x560);
            if (a2 != 0) {
                Buf_1A7998 buf;
                buf.n = 4;
                buf.q = *(Quad_1A7998*)(self + 0x140);
                FnP_1A7998* vt = *(FnP_1A7998**)a2;
                vt[31](a2, &buf);
            }
            break;
        }
        case 2: {
            void* a = *(void**)(self + 0x55C);
            ((FnI_1A7998*)*(void**)a)[25](a, 0);
            a = *(void**)(self + 0x55C);
            ((FnI_1A7998*)*(void**)a)[51](a, 1);
            break;
        }
        }
        if (s2 != 0) func_0012C7B0(s2, self, 0, self + 0x564, 0.0f, 1.0f);
    }
}

struct Ctrl_1A42C8 { u8 pad0[0x614]; s32 mode614; u8 pad1[0x3C]; void* ptr654; void* ptr658; };

void func_001B6628(void* p, s32 a);
void func_001B64D8(void* p, s32 a);
void func_001BF788(void* p, s32 flag);
void func_001BFCD8(s32 a0, void* a1, void* a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

void func_001A42C8(Ctrl_1A42C8* self, s32 state)
{
    s32 old = self->mode614;
    if (old == state) {
        return;
    }
    self->mode614 = state;
    s32 a2;
    s32 s1;
    switch (state) {
    case 0:
        a2 = 0x293;
        s1 = -1;
        break;
    case 1:
        a2 = 0x294;
        s1 = 0x150;
        break;
    }
    if (self->ptr654 != 0) {
        if (old == -1) {
            func_001B6628(self->ptr654, a2);
        } else {
            func_001B64D8(self->ptr654, a2);
        }
    }
    s32 cur = -1;
    if (self->ptr658 != 0) {
        cur = *(s32*)self->ptr658;
        if (s1 == cur) {
            return;
        }
        func_001BF788(self->ptr658, 0);
        self->ptr658 = 0;
        cur = -1;
    }
    if (s1 == cur) {
        return;
    }
    f32 zero = 0.0f;
    func_001BFCD8(s1, &self->ptr658, self, 0, 10000.0f, 6000.0f, 1.0f, zero, zero, 0, 0);
}

void func_001A7D98(void* self, s32 mode);

struct Track_001A7B20 { u8 pad0[4]; s32 value4; s32 value8; s32 state; };

void func_001A7B20(Track_001A7B20* self, s32 a1, s32 a2)
{
    if (self->state == 0) {
        func_001A7D98(self, 1);
    } else {
        func_001A7D98(self, 3);
    }
    self->value4 = a1;
    self->value8 = a2;
}

struct Obj_1A7480 {
    u8 pad0[0x550];
    s32 a550;
    f32 a554;
    void* a558;
    u8 pad1[0x564 - 0x55C];
    void* a564;
};

extern void* D_0026B860[];

void func_001A5B28(void* a, void* b);
void func_001B6628(void* self, void* item);
void func_001B64D8(void* self, void* item);

void func_001A7480(Obj_1A7480* self, s32 value)
{
    s32 old = self->a550;
    if (value == old) {
        return;
    }
    if (old == 9) {
        func_001A5B28(self->a558, self);
    }
    *(s32*)((u8*)self + 0x550) = value;
    self->a554 = D_0026185C[0];
    void* a2 = self->a564;
    if (a2 != 0) {
        void* item = D_0026B860[value];
        if (old == -1) {
            func_001B6628(a2, item);
        } else {
            func_001B64D8(a2, item);
        }
    }
}

struct __attribute__((aligned(16))) Quad_1A4610 { s32 a, b, c, d; };
struct Obj_1A4610 { u8 pad0[0x440]; Quad_1A4610 q440; Quad_1A4610 q450; };
extern u8 D_00248D20[];
s32 func_001300E8(void* node, s32 kind);
void func_001BC828(void* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_001A4610(Obj_1A4610* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5)
{
    Quad_1A4610 s0;
    Quad_1A4610 s1;
    s32 n = *(s32*)(a2 + ((1 - a3) << 6));
    s0 = self->q440;
    s1 = self->q450;
    if (n != 0) {
        if (func_001300E8((void*)n, 0x43) || func_001300E8((void*)n, 0x42)) {
            self->q450.a = 1;
            self->q440 = *(Quad_1A4610*)D_00248D20;
        }
    }
    func_001BC828(self, a1, a2, a3, a4, a5);
    self->q440 = s0;
    self->q450 = s1;
}

struct Iter_1A54F8 {
    void* head;
    u32 pad4;
    s32 link;
};

struct Frame_1A54F8;
extern Frame_1A54F8* D_0027B314;

struct Frame_1A54F8 {
    Iter_1A54F8* iter;
    void* cursor;
    s32 link;
    Frame_1A54F8* prev;
    Frame_1A54F8(Iter_1A54F8* i)
    {
        iter = i;
        cursor = i;
        link = i->link;
        prev = D_0027B314;
        D_0027B314 = this;
    }
    ~Frame_1A54F8() { D_0027B314 = prev; }
    void* Next()
    {
        void* n = *(void**)cursor;
        cursor = (u8*)n + link;
        return n;
    }
};

struct Vt_1A54F8 {
    void* slot[0x18 / 4];
};

struct Obj_1A54F8 {
    u8 pad0[0x560];
    void* f560;
    f32 f564;
    f32 f568;
};

struct Node_1A54F8 {
    void** vtbl;
};

struct Spawn_1A54F8 {
    u8 pad0[0x384];
    u8 l384[0xC];
    u8 l390[0xC];
    s32 n39C;
    Iter_1A54F8 l3A0;
    u8 l3AC[0x628 - 0x3AC];
    s32 n628;
    u8 pad62C[0x638 - 0x62C];
    f32 f638;
    f32 f63C;
    f32 f640;
    f32 f644;
    f32 f648;
};

s32 func_001527D8(Iter_1A54F8* list);
void func_00152600(void* list, void* item);
void func_00152470(void* list, void* item);
s32 func_001EAA70(s32 a, s32 b);
f32 func_001EAAE0(f32 a, f32 b);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_001A6BE0(void* self, s32 mode);
void func_001A76A0(void* node, s32 flag);
extern f32 D_00261858[];

void func_001A54F8(Spawn_1A54F8* self)
{
    if (self->n39C >= self->n628) {
        self->f640 = 3.4028234663852886e+38f;
    } else {
        Node_1A54F8* owner = *(Node_1A54F8**)(self->l390);
        s32 count = func_001527D8(&self->l3A0);
        if (count != 0) {
            Frame_1A54F8 w(&self->l3A0);
            u8* node;
            s32 r = func_001EAA70(0, count - 1);
            s32 j = r;
            j--;
            if (r >= 0) {
                do {
                    node = (u8*)w.Next();
                } while (j-- >= 0);
            }
            func_00152600(&self->l3A0, node);
            func_00152470(self->l3AC, node);
            func_00152600(self->l390, owner);
            func_00152470(self->l384, owner);
            *(void**)((u8*)owner + 0x560) = node;
            self->n39C++;
            ((void (*)(void*))owner->vtbl[0x18 / 4])(owner);
            ((void (*)(void*, void*))owner->vtbl[0x84 / 4])(owner, node + 0x140);
            ((void (*)(void*, void*))owner->vtbl[0x88 / 4])(owner, node + 0x110);
            func_001A6BE0(owner, 1);
            func_001A76A0(*(void**)((u8*)owner + 0x560), 1);
            *(f32*)((u8*)owner + 0x564) = self->f644;
            *(f32*)((u8*)owner + 0x568) = self->f648;
            f32* fp = &self->f638;
            self->f640 = D_00261858[1] + func_001EAAE0(self->f638, fp[1]);
            func_001BFCD8(-1, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            func_001BFCD8(0x14E, 0, (s32)node, 0, 12000.0f, 5000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
    }
}

s32 func_001A4898(void)
{
    s32 flags = *(s32*)(Ctx_1A4B30*)D_002623C8;
    if ((flags & 4) == 0) {
        s32 bit = flags & 2;
        return bit != 0;
    }
    return 2;
}

extern u8 D_00248D30[];

typedef void (*VFn_1A5C90)(void* self, void* a);
struct Obj_1A5C90 { VFn_1A5C90* vtbl; };
struct Self_1A5C90 { u8 pad[0x55C]; Obj_1A5C90* obj; };
enum Kind_1A5C90 { };

void func_001B9AE0(Obj_1A5C90* self, s32 a, s32 b, s32 c, s32 d);
void func_001BFCD8(Kind_1A5C90 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

void func_001A5C90(void* a0, void* a1)
{
    Self_1A5C90* s = (Self_1A5C90*)a1;
    s->obj->vtbl[25](s->obj, a1);
    s = (Self_1A5C90*)a1;
    s->obj->vtbl[36](s->obj, D_00248D30);
    s = (Self_1A5C90*)a1;
    s->obj->vtbl[37](s->obj, D_00248D30);
    func_001B9AE0(((Self_1A5C90*)a1)->obj, 3, 0, 3, 0);
    func_001BFCD8((Kind_1A5C90)0x151, (void*)0, 0, (void*)0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
}

extern u8 D_00248D20[];
extern u8 D_00248D30[];

struct Ctx_1A5D50 { u8 bytes[4]; };
struct Obj_1A5D50;
typedef void (*VFn_1A5D50)(Obj_1A5D50* self, void* a);
struct Obj_1A5D50 { VFn_1A5D50* vtbl; };
struct Holder_1A5D50 { u8 pad0[0x55C]; Obj_1A5D50* f55C; };

void func_001B9AE0(Obj_1A5D50* self, s32 a, void* b, s32 c, s32 d);

void func_001A5D50(Ctx_1A5D50* unused, Holder_1A5D50* h)
{
    Obj_1A5D50* o = h->f55C;

    (void)unused;
    o->vtbl[25](o, (void*)0);
    o->vtbl[36](o, (void*)D_00248D30);
    o->vtbl[37](o, (void*)D_00248D30);
    func_001B9AE0(o, 2, D_00248D20, 3, 0);
}

struct Self_001A6498 { u8 p0[0x550]; s32 f550; u8 p1[0x584 - 0x554]; f32 f584; f32 f588; };

extern u8 D_00248D20[];
void func_001B7968(Self_001A6498* self);
void func_001B9AE0(Self_001A6498* self, s32 a, void* b, s32 c, void* d);

void func_001A6498(Self_001A6498* self)
{
    func_001B7968(self);
    self->f550 = -1;
    self->f584 = 1.0f;
    self->f588 = 2.5f;
    func_001B9AE0(self, 1, D_00248D20, 2, D_00248D20);
}

// Matched: float stores in retail's order with constants loaded as locals; int stores 0x2D0..0x2DC, 0x64C, 0x650 in that order.

struct __attribute__((aligned(16))) Quad_1A4718 {
    s32 a, b, c, d;
};

struct __attribute__((aligned(16))) Table_1A4718 {
    Quad_1A4718 q[12];
};

struct Obj_1A4718 {
    u8 pad0[0x2D0];
    s32 f2D0;
    s32 f2D4;
    s32 f2D8;
    s32 f2DC;
    u8 pad1[0x340 - 0x2E0];
    s32 f340;
    f32 f344;
    f32 f348;
    f32 f34C;
    f32 f350;
    u8 pad2[0x3B8 - 0x354];
    s32 f3B8;
    u8 pad3[0x3D0 - 0x3BC];
    Quad_1A4718 f3D0;
    u8 pad4[0x64C - 0x3E0];
    s32 f64C;
    s32 f650;
};

extern Table_1A4718 D_0024C9D0;
extern Quad_1A4718 D_00275C50;

void func_00123ED0(Obj_1A4718* self);
void func_00152438(void* self, s32 value);
void func_0018D800(void* dst, void* src, s32 count);

void func_001A4718(Obj_1A4718* self)
{
    Table_1A4718 tmp;

    func_00123ED0(self);
    func_00152438((u8*)self + 0x35C, 0x5A0);
    func_00152438((u8*)self + 0x368, 0x5A0);
    func_00152438((u8*)self + 0x374, 0x5A0);
    func_00152438((u8*)self + 0x384, 0x5B0);
    func_00152438((u8*)self + 0x390, 0x5B0);
    func_00152438((u8*)self + 0x3A0, 0x568);
    func_00152438((u8*)self + 0x3AC, 0x568);
    self->f2D0 = -1;
    self->f2D4 = -1;
    self->f2D8 = -1;
    self->f2DC = -1;
    self->f64C = -1;
    self->f650 = -1;
    self->f3B8 = 0x28;
    tmp = D_0024C9D0;
    func_0018D800((u8*)self + 0x3E0, &tmp, 0xC0);
    func_0018D800((u8*)self + 0x4A0, &tmp, 0xC0);
    self->f3D0 = D_00275C50;
    f32 k2300 = 2300.0f;
    f32 k1500 = 1500.0f;
    f32 k146 = 1.46f;
    f32 k3000 = 3000.0f;
    self->f350 = k3000;
    self->f348 = k2300;
    self->f344 = k1500;
    self->f34C = k146;
    self->f340 = 0;
}

struct Obj_1A4070 {
    u8 pad0[0x610];
    s32 f610;
    u8 pad614[0x644 - 0x614];
    void* f644;
    s32* f648;
    u8 pad64C[0x668 - 0x64C];
    s32 f668;
    void* f66C[4];
    void* f67C;
    void* f680;
    s32 f684;
};
enum Kind_1A4070 { K_1A4070_0 };

void func_001F4408(Obj_1A4070* a, s32 n);
void func_00155F90(void* p);
void func_00155FA0(void* p);
void func_001B6628(void* p, s32 n);
void func_001B64D8(void* p, s32 n);
void func_0012C7B0(void* a, Obj_1A4070* self, s32 c, s32* out, f32 fa, f32 fb);
void func_001BF788(s32* p, s32 n);

void func_001A4070(Obj_1A4070* self, s32 n)
{
    s32 old = self->f610;
    if (old == n) return;
    void* h = 0;
    self->f610 = n;
    s32 snd = -1;
    s32 flag = 0;
    s32 kind = 0x14D;
    switch (n) {
    case 0:
        snd = 0x28F;
        flag = 1;
        kind = -1;
        break;
    case 1:
        snd = 0x290;
        break;
    case 2:
        snd = 0x290;
        h = self->f680;
        break;
    case 3:
        snd = 0x290;
        h = self->f67C;
        func_001F4408(0, 1);
        break;
    }
    for (s32 i = 0; i < self->f668; i++) {
        if (flag) func_00155F90(self->f66C[i]);
        else func_00155FA0(self->f66C[i]);
    }
    if (self->f644) {
        if (old == -1) func_001B6628(self->f644, snd);
        else func_001B64D8(self->f644, snd);
    }
    if (h) {
        func_0012C7B0(h, self, 1, &self->f684, 0.0f, 1.0f);
    }
    if (self->f648) {
        if (kind == *self->f648) return;
        func_001BF788(self->f648, 0);
        self->f648 = 0;
    }
    if (kind != -1) {
        func_001BFCD8((s32)(Kind_1A4070)kind, (void*)&self->f648, (void*)self, 0, 10000.0f, 6000.0f, 0.5f, 0.0f, 0.0f, 0, 0);
    }
}

extern u8 D_00248D20[];

struct Obj_1A6F88 {
    u8 pad0[0x550];
    s32 f550;
    u8 pad554[0x568 - 0x554];
    s32 f568;
    f32 f56C;
    f32 f570;
    u8 pad574[0x590 - 0x574];
    f32 f590;
    s32 f594;
    s32 f598;
};
void func_001B7968(Obj_1A6F88* self);
void func_001B9AE0(Obj_1A6F88* self, s32 a, void* b, s32 c, s32 d);
void func_001A6F88(Obj_1A6F88* self)
{
    s32* z;
    func_001B7968(self);
    func_001B9AE0(self, 2, D_00248D20, 3, 0);
    f32 one = 1.0f;
    f32 pt2 = 0.2f;
    z = (s32*)&self->f590;
self->f56C = one;
self->f590 = one;
self->f568 = 8;
self->f550 = -1;
self->f570 = pt2;
z[1]=0;z[2]=0;
}

struct Obj_1A7F50 { u8 pad[0x19EC]; s32 flags; };

void func_001A7F50(Obj_1A7F50* self)
{
    s32 g = D_0026C3DC;
    switch (g) {
    case 1: self->flags = self->flags ^ 0x20; break;
    case 2: self->flags = self->flags | 0x20; break;
    case 3: self->flags = self->flags & 0xFFFFFFDF; break;
    }
    if (self->flags & 0x20) {
        D_0026C3DC = 3;
        return;
    }
    D_0026C3DC = 2;
}

extern u8 D_002483D0[];
extern f32 D_0024CBC4;

struct __attribute__((aligned(16))) Quad_1A7FE8 {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
};

struct V_1A7FE8 { s32 a; f32 b; s32 c; };

struct Obj_1A7FE8 {
    u8 p00[0x14];
    s32 f14;
    u8 p18[0x34];
    s32 f4C;
    s32 f50;
    s32 f54;
    s32 f58;
    u8 q60[0x7C];
    f32 fD8;
    u8 pDC[0x34];
    V_1A7FE8 v110;
    u8 p11C[0x4];
    s32 f120;
    f32 f124;
    u8 p128[0x1C];
    f32 f144;
    u8 p148[0x8];
    u8 p150[0x18];
    s32 f168;
};

void func_00182C18(Obj_1A7FE8* self);
struct Buf_1A7FE8 { u8 b[1]; };
s32 func_001F5C0C(Buf_1A7FE8* p, s32 zero, s32 size);
struct Own_1A7FE8 { u8 b[1]; };
void func_001DBCC8(Own_1A7FE8* owner, void* fn, void* arg, s32 a3, s32 a4);
void func_001A8208(Obj_1A7FE8* self);

void func_001A7FE8(Obj_1A7FE8* self)
{
    func_00182C18(self);
    u8* s1 = (u8*)self + 0x60;
    self->f4C = -1;
    self->f50 = -1;
    self->f54 = -1;
    self->f58 = -1;
    (void)func_001F5C0C((Buf_1A7FE8*)s1, 0, 0x80);
    Quad_1A7FE8* src = (Quad_1A7FE8*)D_002483D0;
    *(Quad_1A7FE8*)(s1 + 0x20) = src[0];
    *(Quad_1A7FE8*)(s1 + 0x30) = src[1];
    *(Quad_1A7FE8*)(s1 + 0x40) = src[2];
    (void)func_001F5C0C((Buf_1A7FE8*)((u8*)self + 0xE0), 0, 0x70);
    V_1A7FE8* p = &self->v110;
    p->a = 0;
    p->b = 1.0f;
    p->c = 0;
    self->f120 = 0;
    self->f124 = 20000.0f;
    (void)func_001F5C0C((Buf_1A7FE8*)self->p150, 0, 0x18);
    f32 d = D_0024CBC4;
    self->fD8 = 5.0f;
    self->f168 = 0;
    self->f144 = d;
    func_001DBCC8((Own_1A7FE8*)self->f14, (void*)func_001A8208, self, 0, 0);
}

struct Sub_1A4C48 { u8 pad0[0x2D4]; s32 f2D4; };
struct Tgt_1A4C48 { u8 pad0[0x550]; s32 f550; };
struct Obj_1A4C48 {
    u8 pad0[0x358]; Tgt_1A4C48* f358;
    u8 pad1[0x3B8 - 0x35C]; s32 f3B8; s32 f3BC;
    u8 pad2[0x634 - 0x3C0]; f32 f634;
    f32 f638; f32 f63C; f32 f640;
    u8 pad4[0x650 - 0x644]; s32 f650;
    u8 pad5[4]; Sub_1A4C48* f658;
};
extern f32 D_00261858[];
void func_00124FC0(Obj_1A4C48* self);
s32 func_001A4DC0(Obj_1A4C48* self);
void func_001A4EF0(Obj_1A4C48* self, s32 mode);
void func_001A5120(Obj_1A4C48* self);
void func_001A54F8(Obj_1A4C48* self);
void func_001A7998(Tgt_1A4C48* t, s32 flag);

void func_001A4C48(Obj_1A4C48* self)
{
    Tgt_1A4C48* t;
    s32 st;
    func_00124FC0(self);
    while ((st = func_001A4DC0(self)) != self->f650) {
        func_001A4EF0(self, st);
    }
    switch (st) {
    case 0:
    case 1:
    case 3:
    case 4:
    case 6:
        break;
    case 2:
        if (self->f3BC < self->f3B8) {
            if (self->f634 < D_00261858[1]) {
                func_001A5120(self);
            }
        }
        if (self->f640 < D_00261858[1]) {
            func_001A54F8(self);
        }
        break;
    case 5: {
        t = self->f358;
        if (t) {
            if (t->f550 == 0) {
                Sub_1A4C48* s = self->f658;
                if (s == 0 || s->f2D4 != 3) {
                    func_001A7998(t, 1);
                }
            }
        }
        break;
    }
    }
}

struct Sub_1A4DC0 { u8 pad0[0x2D4]; s32 f2D4; u8 pad1[0x278]; s32 f550; f32 f554; };
struct Par_1A4DC0 { u8 pad[0x610]; u32 f610; };
struct Obj_1A4DC0 {
    u8 pad0[0x354];
    Par_1A4DC0* f354;
    Sub_1A4DC0* f358;
    u8 pad1[0x5C];
    s32 f3B8;
    s32 f3BC;
    s32 f3C0;
    s32 f3C4;
    u8 pad2[0x288];
    u32 f650;
    f32 f654;
    Sub_1A4DC0* f658;
};

u32 func_001A4DC0(Obj_1A4DC0* self)
{
    u32 s = self->f650;
    switch (s) {
    case 0:
        { u32 one = 1;
        if (self->f354->f610 <= one) s = one; }
        break;
    case 1:
        if (!self->f658 || self->f658->f2D4 != 3) s = 2;
        break;
    case 2:
        if (self->f3C0) { s = 3; break; }
        if (self->f3C4 == self->f3B8) s = 5;
        break;
    case 3:
        if (self->f658->f2D4 != 3) s = 4;
        break;
    case 5:
        if (self->f358) {
            if (self->f358->f550 == 3 && self->f358->f554 + 3.0f < D_0026185C[0]) s = 6;
        } else if (self->f654 + 5.0f < D_0026185C[0]) {
            if (!self->f658 || self->f658->f2D4 != 3) s = 6;
        }
        break;
    case 4:
    case 6:
        break;
    }
    return s;
}

struct __attribute__((aligned(16))) Vec_1A6DE0 { f32 x, y, z, w; };
struct Msg_1A6DE0 {
    s32 kind;
    u8 pad4[0xC];
    Vec_1A6DE0 a;
    Vec_1A6DE0 b;
    Vec_1A6DE0 c;
    Vec_1A6DE0 d;
};
struct Tgt_1A6DE0;
struct VT_1A6DE0 {
    u8 pad[0x7C];
    void (*f_7c)(Tgt_1A6DE0* self, Msg_1A6DE0* m);
};
struct Tgt_1A6DE0 { VT_1A6DE0* vt; };
struct Obj_1A6DE0 {
    u8 pad0[0x550];
    s32 state;
    u8 pad554[8];
    Tgt_1A6DE0* child;
    u8 pad560[0x4C];
    Tgt_1A6DE0* target;
};
struct Ev_1A6DE0 {
    u8 pad0[0xC];
    u32 flags;
    u8 pad10[0x10];
    Vec_1A6DE0 b;
    Vec_1A6DE0 a;
};
enum Id_1A6DE0 { id_1A6DE0_37 = 0x37 };

extern void func_001A6BE0(Obj_1A6DE0* o, s32 n);
extern void func_001A7480(Tgt_1A6DE0* o, s32 n);
extern void func_001BFCD8(Id_1A6DE0 id, s32 a1, s32 a2, Vec_1A6DE0* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

s32 func_001A6DE0(Obj_1A6DE0* o, Ev_1A6DE0* ev) {
    if (ev->flags & 0x20) {
        switch (o->state) {
        case 1: case 2: case 3: case 4: case 5: case 7: case 8:
            func_001A6BE0(o, 9);
            break;
        case 6: {
            Tgt_1A6DE0* c = o->child;
            func_001A6BE0(o, 9);
            if (c) func_001A7480(c, 9);
            break;
        }
        }
        if (o->state == 9) {
            Tgt_1A6DE0* t = o->target;
            if (t) {
                Msg_1A6DE0 m;
                m.kind = 6;
                m.a = ev->a;
                m.b = ev->b;
                m.a.z += 3000.0f;
                t->vt->f_7c(t, &m);
            }
            func_001BFCD8(id_1A6DE0_37, 0, 0, &ev->b, 12000.0f, 8000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
    }
    return ev->flags != 0;
}

struct Src_1A7D98 { u8 pad[4]; u8 b4; u8 b5; };
struct Obj_1A7D98 {
    u8 pad0[4];
    void* owner;
    s32 channel;
    s32 state;
    Src_1A7D98* src;
    u8 pad1[8];
    f32 f1C;
};

s32 func_002049E8(void* owner, s32 channel, u8* bytes);
void func_001A7E40(Obj_1A7D98* self);
extern f32 D_0026186C;

void func_001A7D98(Obj_1A7D98* self, s32 state)
{
    u8 bytes[2];
    if (state == self->state) return;
    switch (state) {
    case 2:
        bytes[0] = self->src->b4;
        bytes[1] = self->src->b5;
        func_002049E8(self->owner, self->channel, bytes);
        self->state = state;
        return;
    case 3:
    case 4:
        func_001A7E40(self);
        self->f1C = D_0026186C * 4.0f;
        break;
    case 0:
    case 1:
        break;
    }
    self->state = state;
}

struct Obj_1A4EF0;
struct Link_1A4EF0 { u8 pad[0x18]; Obj_1A4EF0* f18; };
struct Obj_1A4EF0 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x3B8 - 0x18];
    u8 f3B8[0xC];
    u8 f3C4[0x384 - 0x3C4 + 0x40];
};
struct Step_1A4EF0 { u8 pad[0x14]; void* f14; };
struct Vt_1A4EF0 { u8 pad[0x3C]; void (*f3C)(void* self); };
struct Single_1A4EF0 { Vt_1A4EF0* vt; };
struct Packed_1A4EF0 { u8 pad[0x324]; s32 v __attribute__((packed)); };
struct Glob_1A4EF0 { u8 pad[0x324]; s32 v; };

extern Glob_1A4EF0 D_002701F8;
extern u8 D_00275BC0[];
extern u8 D_00261EF0[];
extern u8 D_0026FF68[];
struct Tab_1A4EF0 { u8 pad[0x264]; void* f264; void* f268; };
extern Single_1A4EF0 D_0026EC70;

s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_001E9498(u8* a, u8* b);
void func_001DDC38(void* host, Obj_1A4EF0* self);
void func_001A6BE0(Obj_1A4EF0* o, s32 n);
void func_001A4070(void* a, s32 n);
void func_00151E20(u8* a, f32 b);
void func_00151FC8(u8* a);
void func_00194D30(u8* a, s32 b, s32 c);

#define F(o, off) (*(f32*)((u8*)(o) + (off)))
#define W(o, off) (*(s32*)((u8*)(o) + (off)))
#define P(o, off) (*(void**)((u8*)(o) + (off)))
#define O(o, off) (*(Obj_1A4EF0**)((u8*)(o) + (off)))

void func_001A4EF0(Obj_1A4EF0* self, s32 state)
{
    Obj_1A4EF0* o;
    s32 v;
    s32 scratch[4]; (void)scratch;
    if (W(self, 0x650) == state) return;
    W(self, 0x650) = state;
    F(self, 0x654) = D_0026185C[0];
    W(self, 0x658) = 0;
    switch (state) {
    case 0:
        break;
    case 1: {
        if (W(self, 0x64C) < 3) {
            if (W(self, 0x64C) >= 0) {
                if (((Step_1A4EF0*)D_002623C8)->f14) {
                    W(self, 0x658) = 0;
                } else {
                    W(self, 0x658) = func_0015A418(self->f14, 0x105, 0x33B, 0);
                }
            }
        }
        s32 w = W(self, 0x658);
        if (w) {
            ((Packed_1A4EF0*)&D_002701F8)->v = w;
            func_001E9498(D_00275BC0, (u8*)&D_002701F8);
        }
        break;
    }
    case 2: {
        ((Tab_1A4EF0*)&D_0026D0C8)->f264 = self->f3C4;
        ((Tab_1A4EF0*)&D_0026D0C8)->f268 = self->f3B8;
        func_001DDC38(self->f14, self);
        break;
    }
    case 5:
        v = func_0015A418(self->f14, 0x105, 0x33D, 0);
        W(self, 0x658) = v;
        if (v) {
            D_002701F8.v = v;
            func_001E9498(D_00275BC0, (u8*)&D_002701F8);
        }
        for (o = O(self, 0x384); o; o = O(o, 0x5B0)) func_001A6BE0(o, 8);
        func_00151FC8(D_00261EF0);
        break;
    case 3:
        v = func_0015A418(self->f14, 0x105, 0x33E, 0);
        W(self, 0x658) = v;
        if (v) {
            D_002701F8.v = v;
            func_001E9498(D_00275BC0, (u8*)&D_002701F8);
        }
        for (o = O(self, 0x384); o; o = O(o, 0x5B0)) {
            Link_1A4EF0* l = (Link_1A4EF0*)P(o, 0x55C);
            if (l == 0 || l->f18 != o) func_001A6BE0(o, 7);
        }
        func_00151E20(D_00261EF0, 1.0f);
        break;
    case 4:
        func_00194D30(D_0026FF68, 0, 0x1A);
        break;
    case 6:
        func_001A4070(P(self, 0x354), 3);
        D_0026EC70.vt->f3C(&D_0026EC70);
        break;
    }
}

struct Obj_1A6BE0 {
    u8 pad0[0x550];
    s32 mode;
    f32 f554;
    void* p558;
    void* p55C;
    u8 pad560[0x58C - 0x560];
    void* p58C;
    void* p590;
    void* p594;
    void* p598;
    void* p59C;
    void* p5A0;
    void* p5A4;
    void* p5A8;
};
struct Pair_1A6BE0 { s32 a; void* b; };

void func_0012E760(Obj_1A6BE0* o);
void func_001B6438(Obj_1A6BE0* o);
void func_001A5C38(void* p, Obj_1A6BE0* o);
void func_001A5DD8(void* p, Obj_1A6BE0* o);
void func_001A5DF8(void* p, Obj_1A6BE0* o);
void func_001A5F78(void* p, Obj_1A6BE0* o);
void func_001A5C90(void* p, Obj_1A6BE0* o);
void func_0012C288(f32 a, f32 b, void* h, Obj_1A6BE0* o, s32 n, Pair_1A6BE0* buf, s32 e, void** out);
void* func_001B6290(void* a, Obj_1A6BE0* o, s32 c, s32 d);

void func_001A6BE0(Obj_1A6BE0* self, s32 mode)
{
    Pair_1A6BE0 buf[2];
    Pair_1A6BE0* w;
    void* h;
    void* s3;

    if (self->mode == mode) return;
    if (self->p59C) {
        func_0012E760((Obj_1A6BE0*)self->p59C);
        self->p59C = 0;
    }
    if (self->p5A8) {
        func_001B6438((Obj_1A6BE0*)self->p5A8);
        self->p5A8 = 0;
    }
    switch (self->mode) {
    case 1:
        func_001A5C38(self->p558, self);
        break;
    case 5:
        if (mode == 6) func_001A5DD8(self->p558, self);
        break;
    case 6:
        if (mode == 0) func_001A5DF8(self->p558, self);
        break;
    case 9:
        func_001A5F78(self->p558, self);
        break;
    default:
        break;
    }
    self->mode = mode;
    h = 0;
    s3 = 0;
    self->f554 = D_0026185C[0];
    w = buf;
    switch (mode) {
    case 0: case 10:
        break;
    case 1: case 2: case 3:
        h = self->p58C;
        break;
    case 4:
        func_001A5C90(self->p558, self);
        w->a = 0x2A0; w->b = self->p55C; w++;
        h = self->p594;
        break;
    case 5: case 6:
        w->a = 0x2A0; w->b = self->p55C; w++;
        h = self->p590;
        break;
    case 7:
        s3 = self->p5A0;
        break;
    case 8:
        s3 = self->p5A4;
        break;
    case 9:
        h = self->p598;
        break;
    }
    if (h) func_0012C288(0.0f, 1.0f, h, self, w - buf, buf, 1, &self->p59C);
    if (s3) self->p5A8 = func_001B6290(s3, self, -1, 1);
}
