// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: buffer pointer updates and byte-load/word assembly order differ.
#include "common.h"
extern void func_00137A60(void*, s32, void*);
struct Reader_137BE0 { u8 pad0[0x18]; u8* ptr; s32 count; };
s32 func_00137BE0(Reader_137BE0* self)
{
    if (self->count >= 2) {
        u8* ptr = self->ptr;
        self->count -= 2;
        self->ptr = ptr + 2;
        return ptr[0] | (ptr[1] << 8);
    }
    s32 value;
    func_00137A60(self, 2, &value);
    return *(u16*)&value;
}
