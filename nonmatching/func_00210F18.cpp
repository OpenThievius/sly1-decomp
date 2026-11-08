// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 370/372 (99.5%), checked 2026-11-08
#include "common.h"
#include "system.h"
// NEAR (2026-11-08, worker night-mmi): the compiler's code is retail's; two words differ, and
// they are the assembler's: each store to 0x1000B000 (the DMA channel's control word, written
// `sw $3,0x1000b000` as a macro) is filled into the delay slot of the
// jal EnableInterrupts after it, and this toolchain's as (2.9-ee-991111b) then emits its high
// half as lui at, 0x1000 where retail has 0x1001 (the carry of the low half 0xB000, a negative
// offset, lost when the macro's store moves into the slot); the same store outside a delay slot
// (0x1000B020 just before) assembles right. No C form gives retail's bytes with this assembler.

// The record of a decode's input transfer in chunks of 0x3FF quadwords (func_00211090 fills it).
struct Xfer_211090 {
    volatile s32 done;      // 0x00: the chunks done
    s32 error;              // 0x04: set when the IPU was still busy
    s32 size;               // 0x08: the quadwords left
    s32 addr;               // 0x0C: the next chunk's address
    s32 total;              // 0x10: the chunks in all
};

s32 DisableInterrupts(void);
s32 EnableInterrupts(void);

// The DMA handler of the IPU's input channel: after each chunk, starts the next one (the last
// with what is left), or marks an error when the channel was still busy; then ends the handler.
s32 func_00210F18(s32 channel, void* arg)
{
    Xfer_211090* x = (Xfer_211090*)arg;
    *(volatile u32*)0x1000E010 = 8;
    x->done++;
    if (*(volatile u32*)0x1000B020 != 0 || (*(volatile u32*)0x1000B000 & 0x100)) {
        x->error = 1;
        return 0;
    }
    s32 last = x->total - 1;
    if (x->done < last) {
        DisableInterrupts();
        *(volatile u32*)0x1000B010 = x->addr;
        *(volatile u32*)0x1000B020 = 0xFFC0;
        *(volatile u32*)0x1000B000 = 0x100;
        EnableInterrupts();
        *(volatile u32*)0x10002000 = 0x700003FF;
        x->addr = (x->addr + 0xFFC00) & 0xFFFFFFF;
    } else if (x->done == last) {
        x->size = x->size - x->done * 0x3FF;
        DisableInterrupts();
        *(volatile u32*)0x1000B010 = x->addr;
        *(volatile u32*)0x1000B020 = x->size << 6;
        *(volatile u32*)0x1000B000 = 0x100;
        EnableInterrupts();
        *(volatile u32*)0x10002000 = x->size | 0x70000000;
    }
    SyncAndEnableInterrupts();
    return 0;
}
