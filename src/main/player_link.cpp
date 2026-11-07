// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"

// The file's .data, in retail's order: the constants of its assembly.
float D_00274D40 = -0.25f;
float D_00274D44 = -2.5f;
float D_00274D48 = -1.0f;
float D_00274D4C = 0.25f;
float D_00274D50[4] = {5.0f, 0.0f, 0.0f, 0.0f};
float D_00274D60[4] = {0.5f, -0.00999999978f, 0.0f, 0.0f};
float D_00274D70[4] = {1000.0f, 0.0f, 0.25f, 5000.0f};
float D_00274D80 = 75.0f;
float D_00274D84 = 230.0f;
float D_00274D88[3] = {15.0f, 0.0f, 0.100000001f};
float D_00274D94 = 1.39999998f;
float D_00274D98 = 1.39999998f;
float D_00274D9C = 0.25f;
float D_00274DA0 = 0.100000001f;
float D_00274DA4 = 0.400000006f;
float D_00274DA8 = 80.0f;
float D_00274DAC = 120.0f;
float D_00274DB0[4] = {1.0f, 0.0f, 0.100000001f, 0.0f};
float D_00274DC0[3] = {4.0f, 0.0f, 0.100000001f};
float D_00274DCC = 1.70000005f;
float D_00274DD0 = 3.0f;
float D_00274DD4 = 3.5f;
float D_00274DD8[2] = {-1.70000005f, 0.0f};
float D_00274DE0[3] = {3000.0f, 1000.0f, 0.150000006f};
float D_00274DF0[3] = {30.0f, 10.0f, 0.150000006f};

void func_00139038(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void** a7);
void func_001399F8(void* obj, s32 a1, s32 a2, void* a3);

struct ThreeBlendRecord { s32 f0; u8 pad0[0xC - 0x4]; s32 fC; u8 pad1[0x18 - 0x10]; f32 f18; };

void func_001CC410(void* a0, ThreeBlendRecord* a1, void** a2)
{
    void* tmp;
    a1->f0 = 0;
    a1->fC = 0;
    a1->f18 = 1.0f;
    func_00139038(a0, 12, 3, a1, 0, 0, 0, &tmp);
    func_001399F8(tmp, 12, 3, a1);
    if (a2 != 0) {
        *a2 = tmp;
    }
}

ASM_FUNC(func_001CC490);

ASM_FUNC(func_001CC818);

ASM_FUNC(func_001CCF98);

struct LinkTargetHolder { s32 pad0; void* target; };
void func_001B9AB0(void* target, void* slot);
void func_001B9AC8(void* target, void* slot);

void func_001CD088(Player* self)
{
    func_001B9AB0(((LinkTargetHolder*)self->f22AC)->target, (u8*)self + 0x22D0);
    func_001B9AC8(((LinkTargetHolder*)self->f22AC)->target, (u8*)self + 0x22E0);
}

ASM_FUNC(func_001CD0C8);

ASM_FUNC(func_001CD6C0);

s32 func_00182FC8(BaseObject* obj);
void func_001385A0(World* world, Contacts03* a, Contacts03* b, s32 set, s32 clr);

// Walks up the parents to the first object whose class has flag bit 2.
void func_001CD7E0(Collider* self, BaseObject* node, s32 flag)
{
    BaseObject* n = node;
    while (n != 0) {
        if ((n->desc->flags & 2) != 0) {
            break;
        }
        n = n->parent;
    }
    if (n != 0) {
        if (IsObjectAttached(n) != 0) {
            SetContactPairFlags(self->world, self->contacts,
                                ((Collider*)((PlacedObject*)n)->root)->contacts,
                                flag != 0 ? 0x40 : 0, flag != 0 ? 0 : 0x40);
        }
    }
    self->f4B8 = 0;
}

ASM_FUNC(func_001CD870);

struct HeadingVector {
    f32 x;
    f32 y;
};

void func_001280C0(void* a, s32 b, void* c, HeadingVector* d);
f32 func_00205778(f32 a, f32 b);

void func_001CDB28(u8* a0, f32* a1)
{
    HeadingVector v;
    void* owner = *(void**)(a0 + 0x2204);
    func_001280C0(*(void**)((u8*)owner + 0x18), 0, (u8*)owner + 0x50, &v);
    *a1 = ArctangentOfRatio(v.y, v.x);
}

ASM_FUNC(func_001CDB70);

ASM_FUNC(func_001CDD98);

void func_001225D0(Player* self, f32 t, void* out, void* extra);
void func_001C5DB8(Player* self, f32 t, void* out, void* extra);

void func_001CDF78(Player* self, f32 t, void* out, void* extra)
{
    if (self->f2220 == 3) {
        GetPlacedObjectRotationAt(self, t, out, extra);
    } else {
        func_001C5DB8(self, t, out, extra);
    }
}
