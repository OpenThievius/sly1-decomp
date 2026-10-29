// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_1389C8 { u8 pad[0x1AEC]; s32 field; };

void func_001389C8(Obj_1389C8* a0)
{
    a0->field = 0;
}

struct Node_138BE0 { u8 pad[0x4B8]; u32 flags; };
struct Owner_138BE0 { u8 pad[0x50]; Node_138BE0* node; };

void func_00138BE0(void* a0, Owner_138BE0* owner, u32 mask)
{
    Node_138BE0* n = owner->node;
    if (n) {
        n->flags &= ~mask;
    }
}

struct Sub_139B38 { u8 pad[0x18]; s32 flag; };
struct Owner_139B38 { u8 pad[8]; Sub_139B38* sub; };

void* func_0012CCE8(void);

void func_00139B38(void)
{
    Owner_139B38* o = (Owner_139B38*)func_0012CCE8();
    if (o) {
        if (o->sub) {
            o->sub->flag = 1;
        }
    }
}

extern u8 D_00261314[];
extern u8 D_00261318[];

void func_00139B70(s32 idx, void* arg);

void func_00139C38(void)
{
    func_00139B70(1, D_00261314);
    func_00139B70(2, D_00261318);
}

struct Sub_139C70 { u8 pad[0x1088]; void* p1088; struct Obj_139C70* owner; };
struct Obj_139C70 { u8 pad0[0x14]; u8* ctx; u8 pad1[0x320 - 0x18]; s32 mode; };

void* func_001B5EA0(void* p);
void func_001B5F28(void* p, void* q);
void func_001F5C0C(void* p, s32 v, s32 n);
void func_00152470(void* list, void* item);

Sub_139C70* func_00139C70(Obj_139C70* o)
{
    Sub_139C70* s = (Sub_139C70*)func_001B5EA0(o->ctx + 0x1B40);
    if (!s) {
        return 0;
    }
    func_001F5C0C(s, 0, 0x10C0);
    if (o->mode != 2) {
        s->owner = o;
    } else {
        void* r = func_001B5EA0(o->ctx + 0x1B4C);
        s->p1088 = r;
        if (r) {
            func_001F5C0C(r, 0, 0x580);
            s->owner = o;
        } else {
            func_001B5F28(o->ctx + 0x1B40, s);
            return 0;
        }
    }
    func_00152470((u8*)o + 0x624, s);
    return s;
}

struct Sub_139D28 { u8 pad[0x108C]; struct Obj_139D28* owner; };
struct Obj_139D28 { u8 pad[0x1]; };

extern u8 D_002622F0[];
void func_00152600(void* list, void* item);
void func_00152470(void* list, void* item);

void func_00139D28(Sub_139D28* o)
{
    func_00152600((u8*)o->owner + 0x624, o);
    func_00152470(D_002622F0, o);
}
