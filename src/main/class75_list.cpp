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


// Slot 0 of class 0x75: transform object init, a count of 30 and a scale of 25.0.
void InitClass75Object(void* self)
{
    Class75Object* o = (Class75Object*)self;
    InitTransformObject((TransformObject*)self);
    o->count = 30;
    o->scale = 25.0f;
}


// Slot 6 of class 0x75: registers the object and appends it to the class's list.
void RegisterClass75Object(void* self)
{
    RegisterObject((BaseObject*)self);
    AppendToList((List01*)g_class75List, self);
}


// Slot 7 of class 0x75: unregisters the object and removes it from the class's list.
void UnregisterClass75Object(void* self)
{
    UnregisterObject((BaseObject*)self);
    RemoveFromList((List01*)g_class75List, self);
}


// Slot 9 of class 0x75: copies the object data but keeps its own list link.
void CopyClass75ObjectData(Class75Object* self, Class75Object* src)
{
    Class75Link tmp;
    tmp = self->link;
    CopyObjectData(self, src);
    self->link = tmp;
}
