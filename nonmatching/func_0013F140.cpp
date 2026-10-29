// SPDX-License-Identifier: AGPL-3.0-or-later
// Near miss: the copy and append logic is modeled, but the compiler uses an
// 8-byte smaller frame and assigns the saved count, index, and value pointer
// differently from retail.
#include "common.h"

typedef u64 Quad_13F140 __attribute__((mode(TI)));
struct Obj_13F140 { u8 pad0[0x7B4]; s32 count; u8 pad7B8[8]; Quad_13F140 values[1]; };
s32 func_001833F0(void* key, s32 kind);
void func_001F5B08(void* dst, void* src, u32 size);

void func_0013F140(Obj_13F140* self, void* key, Quad_13F140* value)
{
    s32 found = func_001833F0(key, 0x200);
    s32 count = self->count;
    s32 index = count;
    if (found != 0) {
        if (count <= 0) {
            index = 0;
        } else {
            func_001F5B08((u8*)self + 0x7C0 + count * 16,
                          (u8*)self + 0x7C0, count << 4);
        }
    }
    *(Quad_13F140*)((u8*)self + 0x7C0 + index * 16) = *value;
    self->count++;
}
