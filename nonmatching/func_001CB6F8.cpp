// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: check.py reports DIFFER; frame matches, but index/count allocation and helper/copy/branch schedule differ.
#include "common.h"

struct Owner_1CB6F8 { u8 pad00[0x58]; s32 count; void* items[1]; };
void func_0018D800(void*, void*, s32);
void func_001CBEE8(void*, s32);

void func_001CB6F8(Owner_1CB6F8* self, void* item)
{
    if (self->count > 0) {
        s32 index = 0;
        if (self->items[0] != item) {
            do {
                index++;
                if (index >= self->count) return;
            } while (self->items[index] != item);
        }
        self->count--;
        func_0018D800(&self->items[index], &self->items[index + 1], (self->count - index) * 4);
        if (self->count <= 0) func_001CBEE8(self, 3);
    }
}
