// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 160/164, checked 2026-11-01
// NEAR: loop body matches; remaining differences are top-level register/load ordering, folded float-global address arithmetic, and a store-base register.
#include "common.h"

struct Node_16F238 {
    u16* values;
    s32 length;
    u8 pad08[8];
    s32 cursor;
    u8 pad14[4];
    Node_16F238* next;
};
extern Node_16F238* D_00262DFC;
extern u8 D_00262C70[];
extern u8 D_00261858[];
extern f32 D_00262E00;

void func_0016F238(void* self, s32 value)
{
    u16 id = (u16)value;
    Node_16F238* node = D_00262DFC;
    if (node == 0) return;
    if (self != D_00262C70) return;
    u16 previous = *(u16*)((u8*)self + 0xA8);
    if (id == previous || previous == 0) return;
    do {
        s32 index = node->cursor;
        if (index < node->length) {
            if (*(u16*)((u8*)self + 0xA8) == node->values[index])
                node->cursor = index + 1;
            else
                node->cursor = 0;
        }
        node = node->next;
    } while (node);
    D_00262E00 = *(f32*)(D_00261858 + 0x10) + 1.0f;
}
