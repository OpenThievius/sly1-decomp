// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Item_158108 { u8 pad0[0xC]; s32 fC; };
struct Owner_158108 { u8 pad0[0x278]; Item_158108* f278; };
struct Obj_158108 {
    void** vtbl;
    u8 pad0[0x1C - 4];
    f32 f1C;
    u8 pad1[0x114 - 0x20];
    s32 f114;
};
typedef void (*VFn_158108)(Obj_158108* self, void* a, s32 z, f32 f);

void* func_0019EA78(s32 a, s32 b);

void func_00158108(void* a0, Owner_158108* a1, f32 f)
{
    Obj_158108* o = (Obj_158108*)func_0019EA78(4, 0);
    if (o != 0) {
        ((VFn_158108*)o->vtbl)[0](o, a0, 0, f);
        o->f1C = 0.75f;
        if (a1->f278 != 0) {
            o->f114 = a1->f278->fC;
        }
    }
}

typedef void (*VFn_001585F8)(void* self);
struct Obj_001585F8 { void** vtbl; };

void func_00182C58(void* a0);

void func_001585F8(Obj_001585F8* a0)
{
    func_00182C58(a0);
    ((VFn_001585F8*)a0->vtbl)[7](a0);
}

struct Blob_158730 { u8 data[0x50]; };
struct Obj_158730 { void** vtbl; };
typedef void (*VFn_158730)(void* self, void* msg);

void func_001F5C0C(void* p, s32 v, s32 n);

void func_00158730(Obj_158730* a0)
{
    Blob_158730 b;
    func_001F5C0C(&b, 0, 0x50);
    ((VFn_158730*)a0->vtbl)[31](a0, &b);
}

struct __attribute__((aligned(16))) Quad_158778 { s32 a, b, c, d; };
struct Msg_158778 {
    s32 a;
    s32 b;
    u8 pad0[8];
    Quad_158778 q1;
    Quad_158778 q2;
    f32 x;
    f32 y;
    u8 pad1[0x50 - 0x38];
};
struct Obj_158778 { void** vtbl; };
typedef void (*VFn_158778)(void* self, void* msg);

void func_00158778(Obj_158778* a0, s32 a1, s32 a2, Quad_158778* a3, Quad_158778* a4, f32 x, f32 y)
{
    Msg_158778 m;
    m.a = a1;
    m.b = a2;
    m.q1 = *a3;
    m.q2 = *a4;
    m.x = x;
    m.y = y;
    ((VFn_158778*)a0->vtbl)[31](a0, &m);
}

void func_001587C0()
{
}

struct Item_158980 {
    void** vtbl;
    u8 pad0[0x80 - 4];
    void* owner;
};
struct Mgr_158980 {
    u8 pad0[0x14];
    void* f14;
    void* f18;
    u8 pad1[0x90 - 0x1C];
    s32 count;
    Item_158980* arr[1];
};
typedef void (*VFn_158980)(void* self);

void func_001830D8(Mgr_158980* a0);
Item_158980* func_00183058(void* a, void* b, void* c);

void func_00158980(Mgr_158980* s2)
{
    func_001830D8(s2);
    for (s32 i = 0; i < s2->count; i++) {
        Item_158980* o = func_00183058(s2->arr[i], s2->f14, s2->f18);
        ((VFn_158980*)o->vtbl)[7](o);
        s2->arr[i] = o;
        o->owner = s2;
    }
}
