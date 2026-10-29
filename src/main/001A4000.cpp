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

extern f32 D_0026185C;

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
        self->a640 = D_0026185C + r;
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
        self->f634 = D_0026185C + t;
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

extern f32 D_0026185C;

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
        f32 t = D_0026185C - *(f32*)(self + 0x554);
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
        self->f634 = D_0026185C + t;
    }
    self->i380 = self->i380 - 1;
    if (self->i39C == self->i628) {
        f32 t2 = func_001EAAE0(self->f638, self->f63C);
        self->f640 = D_0026185C + t2;
    }
    self->i39C = self->i39C - 1;
    func_001BFCD8(0x51, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
}

extern f32 D_0026185C;

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
    if (D_0026185C < *(f32*)(self + 0x554) + *(f32*)(self + 0x570)) {
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
