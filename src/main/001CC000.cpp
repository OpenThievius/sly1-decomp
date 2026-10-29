// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Vec2_CDB28 {
    f32 x;
    f32 y;
};

void func_001280C0(void* a, s32 b, void* c, Vec2_CDB28* d);
f32 func_00205778(f32 a, f32 b);

void func_001CDB28(u8* a0, f32* a1)
{
    Vec2_CDB28 v;
    void* owner = *(void**)(a0 + 0x2204);
    func_001280C0(*(void**)((u8*)owner + 0x18), 0, (u8*)owner + 0x50, &v);
    *a1 = func_00205778(v.y, v.x);
}

struct Target_001CD088 { s32 pad0; void* target; };
struct Actor_001CD088 { u8 pad0[0x22AC]; Target_001CD088* ref; };

void func_001B9AB0(void* target, void* slot);
void func_001B9AC8(void* target, void* slot);

void func_001CD088(Actor_001CD088* self)
{
    func_001B9AB0(self->ref->target, (u8*)self + 0x22D0);
    func_001B9AC8(self->ref->target, (u8*)self + 0x22E0);
}

struct Flags_001CD7E0 { u8 pad[8]; u32 flags; };
struct Node_001CD7E0 { Flags_001CD7E0* item; u8 pad0[0x14]; Node_001CD7E0* next; u8 pad1[0x34]; void* sub; };
struct Owner_001CD7E0 { u8 pad0[0x14]; void* a14; u8 pad1[0x480 - 0x18]; void* a480; u8 pad2[0x4B8 - 0x484]; s32 b4B8; };

s32 func_00182FC8(Node_001CD7E0* node);
void func_001385A0(void* a0, void* a1, void* a2, s32 a3, s32 a4);

void func_001CD7E0(Owner_001CD7E0* self, Node_001CD7E0* node, s32 flag)
{
    Node_001CD7E0* n = node;
    while (n != 0) {
        if ((n->item->flags & 2) != 0) {
            break;
        }
        n = n->next;
    }
    if (n != 0) {
        if (func_00182FC8(n) != 0) {
            func_001385A0(self->a14, self->a480, ((Owner_001CD7E0*)n->sub)->a480,
                          flag != 0 ? 0x40 : 0, flag != 0 ? 0 : 0x40);
        }
    }
    self->b4B8 = 0;
}

struct Ref_001CE9E8 { u8 pad0[0x18]; void* p18; };
struct Obj_001CE9E8 { void* p0; Ref_001CE9E8* p4; u8 pad1[0x10 - 8]; };
struct Frame_001CE9E8 { u8 vecA[0x10]; u8 vecB[0x10]; f32 result; };

void func_001CE800(void* a0, void* a1, void* a2, void* a3);
void func_001CE590(void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, void* a6, s32 a7, s32 stack);

f32 func_001CE9E8(Obj_001CE9E8* self)
{
    Frame_001CE9E8 f;
    func_001CE800(self->p0, self->p4, f.vecA, f.vecB);
    func_001CE590(self->p0, (u8*)self + 0x10, self->p4->p18, f.vecA, f.vecB, 0, &f.result, 0, 0);
    return f.result;
}
