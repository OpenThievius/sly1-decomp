// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR: append/copy behavior is modeled, but the candidate is larger and its frame and argument scheduling differ.
#include "common.h"

struct Header_13F1D8 { s32 words[12]; };
struct Object_13F1D8 { u8 pad000[0x7E0]; s32 count; u8 pad7E4[0xC]; u8 entries[1]; };
s32 func_001833F0(void*, s32);
void func_001F5B08(void*, void*, s32);
void func_0013F1D8(Object_13F1D8* self, void* input, Header_13F1D8* header)
{
    s32 index = self->count;
    s32 available = func_001833F0(input, 0x200);
    if (available && index > 0) {
        func_001F5B08(self->entries, self->entries, index * 0x30);
        index = 0;
    }
    Header_13F1D8* slot = (Header_13F1D8*)(self->entries + index * 0x30);
    *slot = *header;
    ++self->count;
}
