// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 107/120 (89.2%), checked 2026-11-06
#include "common.h"
// NEAR: the list search matches; retail tail-calls func_002014D0 with j and an inlined epilogue, ours emits jal then a branch to the shared epilogue.
//       Sony's compiler tail-jumps only to a void call that ends a void function in every matched
//       case (func_001FA078, func_001F72A8); retail never sets a0 for this one, and the other
//       declarations of func_002014D0 take nothing. Tried: return f(value), f(value)/f() at the
//       end with and without return 0, callee void/noreturn/Node*, the miss path before or after
//       the found path, a for loop: all keep jal.

struct Node_1FFC08 { s32 first; s32 second; s32 value; s32 link; s32 flag; Node_1FFC08* previous; };
extern Node_1FFC08* D_0062A7B8;

void func_0018D750(s32 link);
Node_1FFC08* func_002014D0(s32 value);

Node_1FFC08* func_001FFC08(s32 value)
{
    Node_1FFC08** slot = &D_0062A7B8;
    Node_1FFC08* node;

    if (D_0062A7B8 == 0) {
        goto tail;
    }
    do {
        node = *slot;
        if (node->value == value) {
            *slot = node->previous;
            if (node->first != 0) {
                func_0018D750(node->link);
            }
            goto done;
        }
        slot = &node->previous;
    } while (node->previous != 0);
tail:
    return func_002014D0(value);
done:
    return node;
}
