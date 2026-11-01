// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 156/148, checked 2026-11-01
// NEAR: The body and control flow match, but the configured compiler saves
//        registers with sq/lq instead of retail sd/ld.
#include "common.h"
extern s32 func_002000B0(void*, void*);
struct VTable {
    u8 pad[0x10];
    s16 offset;
    u8 pad2[2];
    s32 (*method)(void*, void*, void*, void*, void*, void*);
};
struct Object { u8 pad[4]; VTable* vtable; };
struct Handler { u8 pad[8]; Object* object; };
s32 func_00200188(Handler* handler, void* first, void* second, s32 fallback,
                  void* arg4, void* last)
{
    if (!func_002000B0(handler, first)) {
        Object* object = handler->object;
        VTable* vtable = object->vtable;
        void* self = (u8*)object + vtable->offset;
        return vtable->method(self, first, second, (void*)fallback, arg4, last);
    }
    return fallback;
}
