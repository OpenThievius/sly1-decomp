// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: remaining differences include frame/register allocation and call operand scheduling in the data-read path.
#include "common.h"
struct Buffer_18F890 { u8 pad00[0x18]; s32 read; s32 end; s32 size; };
struct Object_18F890 { u8 pad00[0x0C]; Buffer_18F890* buffer; u8 pad10[4]; };
s32 func_00130070(void*);
void func_001F6C20(s32);
s32 func_0020A518(void*, s32, s32);
void func_001300D8(void*, void*);
s32 func_0018F890(Object_18F890* self, s32 wait)
{
    Buffer_18F890* buffer = self->buffer;
    while (buffer->read == buffer->end) {
        if (!wait) return 0;
        func_00130070(buffer);
        buffer = self->buffer;
    }
    func_001F6C20(0);
    buffer = self->buffer;
    s32 result = func_0020A518(&self->pad10, buffer->size + buffer->end, buffer->read - buffer->end);
    func_001300D8(buffer, (void*)result);
    return result;
}
