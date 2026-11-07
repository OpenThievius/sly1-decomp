// SPDX-License-Identifier: AGPL-3.0-or-later
// The objects of class 0x75 and the list they register in: func_001DFD48 sets the list up,
// func_001DFD70 empties it, and the class's methods add and remove themselves.
#include "common.h"
#include "switched_collider.h"
#include "world.h"
#include "globals.h"
#include "transform_object.h"

u8 D_002758D0[16] = {0};


void func_00152438(void* p, s32 n);

void func_001DFD48()
{
    SetListLinkOffset(g_class75List, 0x80);
}


void func_00152440(void* p);

void func_001DFD70()
{
    ClearList(g_class75List);
}

void func_001F39F8(void* self);

void func_001DFD90(void* self)
{
    Class75Object* o = (Class75Object*)self;
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

void func_001830D8(void* self);

void func_001DFE38(Class75Object* self)
{
    Class75Link tmp;
    tmp = self->link;
    CopyObjectData(self);
    self->link = tmp;
}
