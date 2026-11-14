/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The two system calls the C library's signals make for a state record, its own object in
 * retail after the signals: send a signal to a process, keeping the error number the call
 * left in the record, and the process's id. C, built by the Linux cc1 of 2.9-ee-991111
 * (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"

struct LibcState {
    s32 error;
};

extern s32 g_systemCallError;

s32 SignalProcess(s32 mode, s32 status);
s32 GetProcessId(void);

/* Sends signal sig to process pid through SignalProcess (which ends the program with the signal
 * as its status when pid is 1), clearing g_systemCallError first and copying it into state->error
 * when the call returns -1 with an error set; returns the call's result. */
s32 SendSignalFor(struct LibcState* state, s32 pid, s32 sig)
{
    s32 ret;

    g_systemCallError = 0;
    ret = SignalProcess(pid, sig);
    if (ret == -1 && g_systemCallError != 0)
        state->error = g_systemCallError;
    return ret;
}

/* The current process's id (the kernel call GetProcessId); the state record is not used. */
s32 GetProcessIdFor(struct LibcState* state)
{
    return GetProcessId();
}
