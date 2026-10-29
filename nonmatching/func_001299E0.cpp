// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: the loop exit and insertion call are scheduled through a different branch path.
#include "common.h"
struct Node_1299E0 { u8 pad[8]; Node_1299E0* next; u8 pad1[8]; s32 key; };
struct Pair_1299E0 { Node_1299E0* first; Node_1299E0* second; u32 base; };
struct Vtbl_1299E0 { u8 pad[0xBC]; void (*notify)(void*); };
struct Obj_1299E0 { Vtbl_1299E0* vtbl; u8 pad[0x1E0 - 4]; Pair_1299E0 pair; };
extern void func_00152540(Pair_1299E0*, Node_1299E0*, Node_1299E0*);
void func_001299E0(Obj_1299E0* self, Node_1299E0* item)
{
    s32 scratch[4];
    (void)scratch;
    Node_1299E0* current = self->pair.first;
    if (current != 0 && item->key < current->key) {
        do {
            current = current->next;
            if (current == 0) goto insert;
        } while (item->key < current->key);
    }
insert:
    func_00152540(&self->pair, current, item);
    self->vtbl->notify(self);
}
