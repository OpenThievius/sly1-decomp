// SPDX-License-Identifier: AGPL-3.0-or-later
// The objects of class 0x75 and the list they register in: func_001DFD48 sets the list up,
// func_001DFD70 empties it, and the class's methods add and remove themselves.
#include "common.h"
#include "switched_collider.h"
#include "world.h"
#include "globals.h"
#include "transform_object.h"

u8 g_class75List[16] = {0};


void SetListLinkOffset(void* p, s32 n);

void InitClass75List()
{
    SetListLinkOffset(g_class75List, 0x80);
}


void ClearList(void* p);

void ClearClass75List()
{
    ClearList(g_class75List);
}

void InitTransformObject(void* self);

void InitClass75Object(void* self)
{
    Class75Object* o = (Class75Object*)self;
    InitTransformObject(self);
    o->count = 30;
    o->scale = 25.0f;
}

void RegisterObject(void* self);
void AppendToList(void* table, void* self);

void RegisterClass75Object(void* self)
{
    RegisterObject(self);
    AppendToList(g_class75List, self);
}

void UnregisterObject(void* self);
void RemoveFromList(void* table, void* self);

void UnregisterClass75Object(void* self)
{
    UnregisterObject(self);
    RemoveFromList(g_class75List, self);
}

void CopyObjectData(void* self);

void CopyClass75ObjectData(Class75Object* self)
{
    Class75Link tmp;
    tmp = self->link;
    CopyObjectData(self);
    self->link = tmp;
}
