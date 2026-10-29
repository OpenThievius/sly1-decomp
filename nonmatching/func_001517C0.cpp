// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: The comparison and loop are close, but operand register order and
//        loop layout differ.
#include "common.h"

struct Queue_1517C0 {
    u8 pad0[0x2DC];
    s32 end;
    u8* records;
    s32 index;
    u8 pad1[0x10];
    void* pending;
};

void func_00150DC0(void* self, void* record);
s32 func_00151300(void* self);
void func_0012E760(void* object);
void func_001516C0(void* self);

void func_001517C0(Queue_1517C0* self)
{
    s32 index = self->index;
    if (self->end > index) {
        do {
            func_00150DC0(self, self->records + index * 0x28);
            if (func_00151300(self)) {
                return;
            }
            if (self->pending) {
                func_0012E760(self->pending);
                self->pending = 0;
            }
            index = self->index + 1;
            self->index = index;
        } while (index < self->end);
        func_001516C0(self);
    }
}
