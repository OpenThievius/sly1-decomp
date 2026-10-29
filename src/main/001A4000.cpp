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
