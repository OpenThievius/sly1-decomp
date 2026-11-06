// SPDX-License-Identifier: AGPL-3.0-or-later
// The C++ runtime's allocation support, the whole object, 0x1FFFD0-0x200080: the handler an
// allocation failure calls, the two placement allocations, and the allocation failure's class
// (include/new.h), whose inline member, vtable, type information and destructor the compiler
// writes out here (`#pragma implementation`), and the empty tag object of the allocations that do
// not throw. C++, built by the Linux cc1plus of 2.9-ee-991111 (config/cflags.tsv,
// docs/TOOLCHAIN.md); the functions the compiler makes keep retail's names (config/us/generated.tsv).
// Written for this project from retail's code.
#include "common.h"
#pragma implementation "new.h"
#include "new.h"

// The tag an allocation that must not throw takes: an empty object.
struct NoThrow {};
extern const NoThrow D_0024F1F0 = {};

typedef void (*NewHandler)(void);

// What an allocation calls when it runs out of memory.
NewHandler D_002789D8 = 0;

NewHandler func_001FFFD0(NewHandler handler)
{
    NewHandler previous = D_002789D8;
    D_002789D8 = handler;
    return previous;
}

// Placement allocations: the memory is given.
void* func_001FFFE0(u32 size, void* place)
{
    return place;
}

void* func_001FFFE8(u32 size, void* place)
{
    return place;
}
