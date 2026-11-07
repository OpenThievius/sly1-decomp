// SPDX-License-Identifier: AGPL-3.0-or-later
// The parameters a thread is made from (MakeThread, func_001F6A10): its entry, stack, stack size,
// global pointer and priority. memory_card.cpp's background job (func_0018B670), movie_player.cpp's
// decode thread and the render thread (func_001E2398) clear 0x30 bytes of one on the stack and fill
// these. Written for this project from what retail's code does.
#ifndef THREAD_PARAMS_H
#define THREAD_PARAMS_H

#include "common.h"

struct ThreadParams {
    s32 f00;                // 0x00
    void (*entry)();        // 0x04: the thread's function
    void* stack;            // 0x08: its stack
    s32 stackSize;          // 0x0C
    void* gp;               // 0x10: the global pointer it runs with
    s32 priority;           // 0x14
    u8 pad18[0x18];         // 0x18
};

typedef char check_ThreadParams[sizeof(ThreadParams) == 0x30 ? 1 : -1];

#endif
