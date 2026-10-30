// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: remaining differences are branch and call ordering around func_0013CC00 and the loop control flow.
#include "common.h"

struct Object_18EAF8 {
    s32 state;
    u8 pad04[0x28];
    u8* first;
    u8 pad30[0x0C];
    s32 first_count;
    u8 pad40[0x0C];
    u8* second;
    u8 pad50[0x0C];
    s32 second_count;
};
s32 func_0013CC00(void*, s32, void*);

s32 func_0018EAF8(Object_18EAF8* self, s32 size, u8* input)
{
    if (self->state == 0) return 0;
    size -= 4;
    if (self->state == 1) {
        input += 4;
        s32 copied = func_0013CC00(self->first, size, input);
        input += copied;
        size -= copied;
        if (self->first_count <= 0) self->state = 2;
    }
    if (self->second_count >= size) return 0;
    func_0013CC00(self->second, size, input);
    return 1;
}
