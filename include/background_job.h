// SPDX-License-Identifier: AGPL-3.0-or-later
// The 0x14-byte record at D_00269990 (memory_card.cpp defines it as zeros), read by func_0018B5C0,
// func_0018B600 (memory_card.cpp) and func_001943E8, func_00195958 (file_193210.cpp). Written for
// this project from what retail's code does (globals.tsv). The size is the label's (0x14).
//
// A job that runs on a thread of its own: func_0018B670 stores the job and its argument and
// starts a thread at func_0018B600, which calls the job, keeps its result and clears the thread.
#ifndef BACKGROUND_JOB_H
#define BACKGROUND_JOB_H

#include "common.h"

struct BackgroundJob {
    union {
        void* semaphore;    // 0x00: func_0018B600
        s32 semaphoreId;    // 0x00: func_0018B5C0 stores the semaphore it creates
    };
    s32 thread;             // 0x04: func_0018B5C0, func_0018B600 (-1 when no thread runs)
    s32 (*job)(void* a);    // 0x08: func_0018B600 calls it
    void* arg;              // 0x0C: func_0018B600
    s32 result;             // 0x10: func_0018B5C0, func_0018B600, func_001943E8
};

typedef char check_BackgroundJob[sizeof(BackgroundJob) == 0x14 ? 1 : -1];

extern BackgroundJob D_00269990;      // memory_card.cpp

#endif
