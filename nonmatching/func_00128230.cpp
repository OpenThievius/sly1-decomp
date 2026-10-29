// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: the second conditional path uses a different compare and return sequence.
#include "common.h"
struct Elem_12A230 { u8 pad[0x10]; s8 first; s8 second; };
struct Obj_12A230 { u8 pad[0x1EC]; Elem_12A230* first; Elem_12A230* second; };
s32 func_00128230(Obj_12A230* self)
{
    Elem_12A230* item = self->first;
    if (item != 0 && item->first == 5) return 1;
    item = self->second;
    if (item == 0) return 0;
    s8 expected = 5;
    if (item->second == expected) return 1;
    return 0;
}
