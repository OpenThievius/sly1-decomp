// SPDX-License-Identifier: AGPL-3.0-or-later
// The objects of class 0x75 and the list they register in: func_001DFD48 sets the list up,
// func_001DFD70 empties it, and the class's methods add and remove themselves. Its name is ours,
// after that list; what class 0x75 is for is not known yet.
#include "common.h"
#include "switched_collider.h"
#include "world.h"
#include "globals.h"
#include "transform_object.h"
#include "functions/base_object.h"
#include "functions/oscillator.h"
#include "functions/pooled_object.h"

u8 g_class75List[16] = {0};



void InitClass75List()
{
    SetListLinkOffset((List01*)g_class75List, 0x80);
}



void ClearClass75List()
{
    ClearList((List01*)g_class75List);
}


void InitClass75Object(void* self)
{
    Class75Object* o = (Class75Object*)self;
    InitTransformObject((TransformObject*)self);
    o->count = 30;
    o->scale = 25.0f;
}


void RegisterClass75Object(void* self)
{
    RegisterObject((BaseObject*)self);
    AppendToList((List01*)g_class75List, self);
}


void UnregisterClass75Object(void* self)
{
    UnregisterObject((BaseObject*)self);
    RemoveFromList((List01*)g_class75List, self);
}


void CopyClass75ObjectData(Class75Object* self, Class75Object* src)
{
    Class75Link tmp;
    tmp = self->link;
    CopyObjectData(self, src);
    self->link = tmp;
}
