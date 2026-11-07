// SPDX-License-Identifier: AGPL-3.0-or-later
// The C++ runtime's allocation, the whole object 0x1FD8A8-0x1FD920: it takes the memory from the
// game's allocator (func_0018D758) and may throw only bad_alloc, an exception specification that
// gives the object its .gcc_except_table and frame tables. Its .rodata is the "bad_alloc" literal
// of include/new.h. C++, built by the Linux cc1plus of 2.9-ee-991111 (config/cflags.tsv,
// docs/TOOLCHAIN.md). Written for this project from retail's code.
#include "common.h"
#include "new.h"

void* AllocateObjectMemory(u32 size);

void* AllocateOrThrow(u32 size) throw(bad_alloc)
{
    return AllocateObjectMemory(size);
}
