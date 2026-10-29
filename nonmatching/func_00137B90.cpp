// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: buffer pointer updates and byte-load/store order differ.
#include "common.h"
extern void func_00137A60(void*, s32, void*);
struct Reader_137B90 { u8 pad0[0x18]; u8* ptr; s32 count; };
s32 func_00137B90(Reader_137B90* self)
{
    if (self->count > 0) {
        self->count--;
        u8* ptr = self->ptr;
        self->ptr = ptr + 1;
        return *ptr;
    }
    s32 value;
    func_00137A60(self, 1, &value);
    return *(u8*)&value;
}
