// SPDX-License-Identifier: AGPL-3.0-or-later
// The objects of class 0x75 and the list they register in: func_001DFD48 sets the list up,
// func_001DFD70 empties it, and the class's methods add and remove themselves.
#include "common.h"
#include "switched_collider.h"
#include "world.h"
#include "globals.h"

u8 D_002758D0[16] = {0};


void func_00152438(void* p, s32 n);

void func_001DFD48()
{
    func_00152438(g_class75List, 0x80);
}


void func_00152440(void* p);

void func_001DFD70()
{
    ClearList(g_class75List);
}

struct Obj_001DFD90 { u8 pad[0x88]; s32 count; f32 scale; };

void func_001F39F8(void* self);

void func_001DFD90(void* self)
{
    Obj_001DFD90* o = (Obj_001DFD90*)self;
    InitTransformObject(self);
    o->count = 30;
    o->scale = 25.0f;
}

void func_00182D48(void* self);
void func_00152470(void* table, void* self);

void func_001DFDC8(void* self)
{
    RegisterObject(self);
    AppendToList(g_class75List, self);
}

void func_00182ED0(void* self);
void func_00152600(void* table, void* self);

void func_001DFE00(void* self)
{
    UnregisterObject(self);
    RemoveFromList(g_class75List, self);
}

struct __attribute__((packed)) Pk8_001DFE38 {
    s64 v;
};

struct Obj_001DFE38 {
    u8 pad0[0x80];
    Pk8_001DFE38 f80;
};

void func_001830D8(void* self);

void func_001DFE38(Obj_001DFE38* self)
{
    Pk8_001DFE38 tmp;
    tmp = self->f80;
    CopyObjectData(self);
    self->f80 = tmp;
}
