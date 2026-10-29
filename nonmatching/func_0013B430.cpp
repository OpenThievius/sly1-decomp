// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: object traversal and the mask conditions are modeled, but the
// compiler omits the retail 16-byte stack area and schedules the bit tests and
// branch delay slots differently.
#include "common.h"

struct Node_13B430 { u8 pad0[0xC]; u32 flags; };
struct Obj_13B430 { u8 pad0[0x380]; Node_13B430* node; u8 pad384[0x630 - 0x384]; Obj_13B430* next; };
extern u8* D_00275710;
void func_0013A008(void* self);

void func_0013B430(u32 mask)
{
    if (mask == 0) {
        return;
    }
    Obj_13B430* object = *(Obj_13B430**)(D_00275710 + 0x1CB4);
    while (object != 0) {
        Node_13B430* node = object->node;
        u32 flags = node->flags;
        if ((flags & 0x10000000) != 0 || (mask & flags) == mask) {
            func_0013A008(object);
        }
        object = object->next;
    }
}
