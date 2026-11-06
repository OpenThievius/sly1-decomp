// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 107/120 (89.2%), checked 2026-11-05
#include "common.h"
// NEAR: the list search matches; retail tail-calls func_002014D0 with j and an inlined epilogue, ours emits jal then a branch to the shared epilogue

struct Node_1FFC08 { s32 first; s32 second; s32 value; s32 link; s32 flag; Node_1FFC08* previous; };
extern Node_1FFC08* D_0062A7B8;

void func_0018D750(s32 link);
Node_1FFC08* func_002014D0(s32 value);

Node_1FFC08* func_001FFC08(s32 value)
{
    Node_1FFC08** slot;
    Node_1FFC08* node;

    for (slot = &D_0062A7B8; *slot != 0; slot = &node->previous) {
        node = *slot;
        if (node->value == value) {
            *slot = node->previous;
            if (node->first != 0) {
                func_0018D750(node->link);
            }
            return node;
        }
    }
    return func_002014D0(value);
}
