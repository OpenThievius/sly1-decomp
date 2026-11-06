/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The C++ runtime's throw and rethrow, from the toolchain's own runtime (config/us/libcalls.tsv).
 * C, built by cc1 with -fexceptions (config/cflags.tsv): the stub that returns into the handler
 * and the prologue that saves every register are __builtin_unwind_init's and
 * __builtin_eh_return's, which only GCC's C front end has, and without -fexceptions the stub
 * moves (func_001FE4C8) or cc1 fails (func_001FE6A8). Written for this project from retail's
 * code; the neighbouring runtime functions are C++ in src/lib/001FC000.cpp. */
#include "common.h"

/* A frame's unwind state, 0x2F0 bytes: its canonical frame address first. */
typedef struct UnwindFrame {
    s32 cfa;
    s32 pad4;
    s64 rest[0x2E8 / 8];
} UnwindFrame;

/* The runtime's exception context (func_001FD9E8's): the pending object at 8, its index at 0xC. */
typedef struct EhContext {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
} EhContext;

extern EhContext* (*D_0027804C)(void);
void func_001FD930(void);
UnwindFrame* func_001FFC80(void* pc, UnwindFrame* frame);
void* func_001FE198(EhContext* ctx, void* pc, UnwindFrame* frame, UnwindFrame** found);

/* Rethrow: unwind from the caller to the handler of the exception being handled. */
void func_001FE4C8(void)
{
    EhContext* ctx = (*D_0027804C)();
    UnwindFrame mine, copy;
    UnwindFrame* cur = &mine;
    UnwindFrame* cp = &copy;
    void* handler;
    s32 offset;

    if (ctx->f8 == 0)
        func_001FD930();

    __builtin_unwind_init();
here:
    cur = func_001FFC80(&&here, cur);
    if (cur == 0)
        func_001FD930();
    cur->cfa = (s32)__builtin_dwarf_cfa();
    *cp = *cur;
    handler = func_001FE198(ctx, (char*)__builtin_return_address(0) - 1, cp, &cur);
    offset = cur->cfa - cp->cfa;
    __builtin_eh_return(ctx, offset, handler);
}

/* Throw: the same, after recording the index the thrower passes. */
void func_001FE6A8(void* index)
{
    EhContext* ctx = (*D_0027804C)();
    UnwindFrame mine, copy;
    UnwindFrame* cur = &mine;
    UnwindFrame* cp = &copy;
    void* handler;
    s32 offset;

    if (ctx->f8 == 0)
        func_001FD930();
    ctx->fC = (s32)index;

    __builtin_unwind_init();
here:
    cur = func_001FFC80(&&here, cur);
    if (cur == 0)
        func_001FD930();
    cur->cfa = (s32)__builtin_dwarf_cfa();
    *cp = *cur;
    handler = func_001FE198(ctx, (char*)__builtin_return_address(0) - 1, cp, &cur);
    offset = cur->cfa - cp->cfa;
    __builtin_eh_return(ctx, offset, handler);
}
