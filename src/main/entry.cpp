// SPDX-License-Identifier: AGPL-3.0-or-later
// The first object of the game's code, from 0x100000 to 0x1000C8, built whole
// (config/us/files.tsv): the program's entry (func_00100008: it clears .bss from D_0027B300,
// sets up the main thread and the heap through two system calls, runs func_001F9EA8 and
// func_001F6C20, enables interrupts, calls func_00185758 with D_0027B380's count and words
// and leaves through func_001FA078 with its result), the exit func_001000B8 (func_001FA078
// with 0) and func_001000C0, the thread's return address set up by the entry, which ends it
// with a system call. All of it is original assembly (config/us/original_asm.tsv), with the
// two words of padding before the entry (func_00100000). No .rodata or .data of its own.
// Named after what it holds: the program's entry.
#include "asm_func.h"

LINKER_REMNANT(func_00100000);

ASM_FUNC(func_00100008);

ASM_FUNC(func_001000B8);

ASM_FUNC(func_001000C0);
