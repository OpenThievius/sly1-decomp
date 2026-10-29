// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: buffer pointer updates and four-byte assembly order differ.
#include "common.h"
extern void func_00137A60(void*, s32, void*);
struct Reader_137C40 { u8 pad0[0x18]; u8* ptr; s32 count; };
s32 func_00137C40(Reader_137C40* self)
{
    if (self->count >= 4) {
        u8* ptr = self->ptr;
        self->count -= 4;
        self->ptr = ptr + 4;
        return ptr[0] | (ptr[1] << 8) | (ptr[2] << 16) | (ptr[3] << 24);
    }
    s32 value;
    func_00137A60(self, 4, &value);
    return value;
}
