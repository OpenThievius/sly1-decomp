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
