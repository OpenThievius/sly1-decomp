// SPDX-License-Identifier: AGPL-3.0-or-later
// The C library's pseudo-random numbers, their own object from 0x1F66F8 to 0x1F6738
// (config/us/files.tsv): the seed setter and the generator, word for word a member of the
// toolchain's libc.a built from a .c source. The seed lives at +0x58 of the record
// g_libraryState points to. No data of its own.
#include "common.h"

// The part of the library state the generator uses: its seed, at 0x58.
struct LibraryState { u8 pad[0x58]; u32 randomSeed; };
extern LibraryState* g_libraryState;

// Sets the pseudo-random generator's seed, the word at +0x58 of the library state record.
void SeedRandom(u32 value)
{
    g_libraryState->randomSeed = value;
}

// The next pseudo-random number: a linear congruential step (seed * 0x41C64E6D + 0x3039), stored
// back as the seed, giving the low 31 bits (0 to 0x7FFFFFFF).
u32 NextRandom(void)
{
    u32 state = g_libraryState->randomSeed * 0x41C64E6Du + 0x3039u;
    g_libraryState->randomSeed = state;
    return state & 0x7FFFFFFFu;
}
