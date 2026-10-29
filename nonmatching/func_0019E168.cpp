// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: stack-local/global chain setup, call flow, and global restore sequence still differ from retail.
#include "common.h"
struct Object_19E168 { u8 pad[0x558]; s32 count; u8 pad55C[8]; void* owner; u8 pad568[0x1AD0]; };
struct Node_19E168 { Node_19E168* next; };
extern void* D_0027B314;
void func_0019EBE8(void*);
void func_001B7B78(void*);
void func_0019E168(Object_19E168* self)
{
    Node_19E168* local = (Node_19E168*)((u8*)self + 0x558);
    void* old = D_0027B314;
    D_0027B314 = &local;
    Node_19E168* n = local;
    while (n) { func_0019EBE8(n); n = n->next; }
    self->owner = *(void**)((u8*)self->owner + 0x1B38);
    func_001B7B78(self);
    D_0027B314 = old;
}
