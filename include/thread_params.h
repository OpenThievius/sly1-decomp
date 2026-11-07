// SPDX-License-Identifier: AGPL-3.0-or-later
// The record a new thread is made from (MakeThread, func_001F6A10), as the game fills it: its
// entry, stack, stack size, global pointer and priority (func_001E2398 starts the render thread
// from one, func_0018B670 a background job's). Written for this project from retail's code.
#ifndef THREAD_PARAMS_H
#define THREAD_PARAMS_H

#include "common.h"

struct ThreadParams {
    s32 f00;                // 0x00
    void (*entry)();        // 0x04
    void* stack;            // 0x08
    s32 stackSize;          // 0x0C
    void* gp;               // 0x10
    s32 priority;           // 0x14
    u8 pad18[0x18];         // 0x18
};

typedef char check_ThreadParams[sizeof(ThreadParams) == 0x30 ? 1 : -1];

#endif
