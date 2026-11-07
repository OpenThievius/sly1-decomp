// SPDX-License-Identifier: AGPL-3.0-or-later
// The record a new semaphore is made from (NewSemaphore, system call 0x40), as the libraries fill
// it: its count, maximum and initial count, the threads waiting on it, its attributes and an
// option word. Written for this project from retail's code.
#ifndef SEMAPHORE_PARAMS_H
#define SEMAPHORE_PARAMS_H

#include "common.h"

typedef struct SemaphoreParams {
    s32 count;       // 0x00
    s32 maxCount;    // 0x04
    s32 initCount;   // 0x08
    s32 waitThreads; // 0x0C
    u32 attr;        // 0x10
    u32 option;      // 0x14
} SemaphoreParams;

#endif
