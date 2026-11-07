/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The two system calls the C library's signals make for a state record, its own object in
 * retail after the signals: send a signal to a process, keeping the error number the call
 * left in the record, and the process's id. C, built by the Linux cc1 of 2.9-ee-991111
 * (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"

struct LibcState {
    s32 error;
};

extern s32 D_0027B328;

s32 func_001FA0E0(s32 pid, s32 sig);
s32 func_001FA0D8(void);

s32 func_002016A0(struct LibcState* state, s32 pid, s32 sig)
{
    s32 ret;

    g_systemCallError = 0;
    ret = SignalProcess(pid, sig);
    if (ret == -1 && g_systemCallError != 0)
        state->error = g_systemCallError;
    return ret;
}

s32 func_00201700(struct LibcState* state)
{
    return GetProcessId();
}
