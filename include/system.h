// SPDX-License-Identifier: AGPL-3.0-or-later
// The system instructions the libraries' C (and a few game functions) used through
// inline-assembly helpers, around frames the compiler made. Written for this project from
// retail's code (docs/TOOLCHAIN.md, "The MMI and system helpers").
//
// Each helper is one __asm__ statement for an instruction or a short sequence that recurs across
// retail's functions and that the compiler cannot emit. They are volatile, as AGENTS.md allows
// hardware access to be: each reads or changes the processor's state (the COP0 registers, the
// interrupt enable, the order of memory operations), so the compiler must neither drop nor
// move them, and retail never schedules anything across them. C and C++ both include it (the
// libraries have .c files), so the helpers are plain static inline functions.
#ifndef SYSTEM_H
#define SYSTEM_H

#include "common.h"

// sync: waits until every earlier load and store has completed. An interrupt handler ends with
// it before ei (SyncAndEnableInterrupts); alone it follows a write to a device or a system call
// whose effects the code must see (func_001F6D40's wrappers, func_00202478, func_00210C38).
static __inline__ void Sync(void)
{
    __asm__ volatile("sync");
}

// sync; ei: the end of an interrupt handler, which ran with interrupts disabled: the handler's
// stores complete, then interrupts are enabled again (eight handlers, game and library).
static __inline__ void SyncAndEnableInterrupts(void)
{
    __asm__ volatile("sync\n\tei");
}

// mfc0 r, $12: the COP0 Status register, read into the register of the value that keeps it
// (bit 16, EIE, says whether interrupts are enabled: the four wrappers of system_calls.cpp and
// func_00204EC8 disable them around their call only when it is set).
static __inline__ u32 ReadCop0Status(void)
{
    u32 r;
    __asm__ volatile("mfc0 %0, $12" : "=r"(r));
    return r;
}

// mfc0 r, $9: the COP0 Count register, the processor's cycle counter (game_clock.cpp's start
// time). The same instruction as ReadCop0Status, on another register. mfc0 sign-extends the
// 32-bit register into the GPR, and retail stores the result as a doubleword straight away
// (sd, no extension of its own), so the value is a 64-bit one.
static __inline__ u64 ReadCop0Count(void)
{
    u64 r;
    __asm__ volatile("mfc0 %0, $9" : "=r"(r));
    return r;
}

#endif
