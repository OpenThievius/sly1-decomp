// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 176/180, checked 2026-11-01
// NEAR: field offsets and prologue match closely; remaining differences are branch/CFG layout and loop/call scheduling.
#include "common.h"

struct Entry_17C660 { u8 pad[8]; s32 state; u8 tail[8]; };
struct Object_17C660 {
    u8 pad00[0x34];
    s32 limit;
    Entry_17C660* entries;
    u8 pad3C[4];
    s32 index;
    u8 pad44[4];
    void* pending;
};
void func_0017BCD0(Object_17C660* self);
s32 func_0017C428(Object_17C660* self);

void func_0017C660(Object_17C660* self)
{
    if (self->index < 0 && self->limit > 0)
        func_0017BCD0(self);
    while (self->index < self->limit) {
        Entry_17C660* entry = (Entry_17C660*)((u8*)self->entries + self->index * 20);
        if (entry->state != 0 || func_0017C428(self)) {
            func_0017BCD0(self);
            continue;
        }
        break;
    }
    if (self->pending && func_0017C428(self))
        self->pending = 0;
}
