// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: the callback and parameter flow are modeled, but the candidate is 204 bytes versus retail 196 and list traversal/register/frame choices differ.
// NEAR: best C build is 204 bytes vs retail 196; list traversal and saved-register setup still differ.
#include "common.h"

struct Handle_1FEB18 {
    u8 pad_00[0x8];
    void* object;
    void* data;
    void (*callback)(void*, s32);
    s32 state;
    void* next;
    u8 pad_1C[4];
    s64 refs;
    u8 pad_28[8];
};

void* func_001FDA10(void*);
void* func_001FE8F0(void*);
void func_001FE9F8(void*);
s32 func_00200C40(void*);

void func_001FEB18(Handle_1FEB18* self)
{
    void* head = func_001FDA10(self);
    if (--self->refs != 0) {
        return;
    }
    void** link = (void**)head;
    void* item = *link;
    if (item == self && self->state == 0) {
        return;
    }
    while (item != 0 && item != self) {
        link = (void**)((u8*)item + 0x18);
        item = *link;
    }
    if (item == 0) {
        *link = func_001FE8F0(link);
    } else {
        *link = self->next;
    }
    if (self->callback != 0) {
        self->callback(self->object, 2);
    }
    if (func_00200C40(self->data) == 0) {
        func_001FE9F8((u8*)self + 0x28);
    }
    func_001FE9F8(self);
}
