// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: buffer pointer updates and byte-load/store order differ.
#include "common.h"
extern void func_00137A60(void*, s32, void*);
struct Reader_137CC0 { u8 pad0[0x18]; s8* ptr; s32 count; };
s32 func_00137CC0(Reader_137CC0* self)
{
    if (self->count > 0) {
        self->count--;
        s8* ptr = self->ptr;
        self->ptr = ptr + 1;
        return *ptr;
    }
    s32 value;
    func_00137A60(self, 1, &value);
    return *(s8*)&value;
}
