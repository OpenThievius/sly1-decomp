/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The C library's signals, its own object in retail: the table of 32 handlers a state record
 * keeps at +0x1D4, made on first use, and the raising of a signal through it (0 the default,
 * which sends the signal to this process; 1 ignored; -1 an error; else the handler, reset to
 * the default before it is called). The linker stripped the object's other functions and left
 * two remnants of them. C, built by the Linux cc1 of 2.9-ee-991111 (config/cflags.tsv,
 * docs/TOOLCHAIN.md). Written for this project from retail's code. */
#include "common.h"
#include "asm_func.h"

typedef void (*SignalHandler)(s32 sig);

struct LibcState {
    s32 error;
    u8 pad4[0x1D0];
    s32* handlers;
};

extern struct LibcState* D_0027696C;

void* func_0018D748(struct LibcState* state, s32 size);
s32 func_002016A0(struct LibcState* state, s32 pid, s32 sig);
s32 func_00201700(struct LibcState* state);

s32 func_00201500(struct LibcState* state)
{
    s32 i;

    if (state->handlers == 0) {
        state->handlers = (s32*)func_0018D748(state, 0x80);
        if (state->handlers == 0)
            return -1;
        for (i = 31; i >= 0; i--)
            state->handlers[i] = 0;
    }
    return 0;
}

LINKER_REMNANT(func_00201570);

s32 func_00201578(struct LibcState* state, s32 sig)
{
    s32 ret = 0;
    SignalHandler handler;

    if ((u32)sig >= 0x20) {
        state->error = 0x16;
        return -1;
    }
    if (state->handlers == 0) {
        if (func_00201500(state) != 0)
            return -1;
    }
    switch (state->handlers[sig]) {
    case 0:
        return func_002016A0(state, func_00201700(state), sig);
    case 1:
        break;
    case -1:
        state->error = 0x16;
        ret = 1;
        break;
    default:
        handler = (SignalHandler)state->handlers[sig];
        state->handlers[sig] = 0;
        handler(sig);
        break;
    }
    return ret;
}

s32 func_00201668(s32 sig)
{
    return func_00201578(D_0027696C, sig);
}

LINKER_REMNANT(func_00201690);
