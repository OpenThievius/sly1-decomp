// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: check.py reports DIFFER; candidate is larger than retail (188 vs 180 bytes), with local frame/register allocation differences.
#include "common.h"

struct Interface_1E7460 { void* vtbl; };
struct StateObject_1E7460 { u8 pad00[0x2C8]; u64 flags; };
struct Self_1E7460 { u8 pad00[0x270]; Interface_1E7460* current; Interface_1E7460* next; Interface_1E7460* other; };
extern s32 D_00270458;
void func_00126BC0(void*, void*);

void func_001E7460(Self_1E7460* self)
{
    if (self->current == self->next) return;
    if (self->next != 0) {
        if (D_00270458 != 4 || self->other != self->next)
            ((void (*)(Interface_1E7460*))((void**)self->next->vtbl)[7])(self->next);
    }
    Interface_1E7460* next = self->current;
    if (next == 0) return;
    self->next = next;
    ((void (*)(Interface_1E7460*))((void**)next->vtbl)[6])(next);
    if (D_00270458 != 4) func_00126BC0(next, self);
    ((StateObject_1E7460*)next)->flags |= (u64)0x8000 << 17;
}
