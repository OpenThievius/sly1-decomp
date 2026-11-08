// SPDX-License-Identifier: AGPL-3.0-or-later
// The kernel library's system call stubs, their own object from 0x1F6900 to 0x1F6EE0, built whole
// (config/us/files.tsv): 68 stubs of four instructions each (the call number into $v1, syscall,
// return), func_001F6900 to func_001F6D30, and four wrappers, func_001F6D40 to func_001F6E78,
// which call a stub between func_001F9D60 and func_001F9DA8 when the status register's bit 16
// is set. The stubs are original assembly (config/us/original_asm.tsv); the wrappers are C around
// the system helpers (include/system.h). Its .data is the library's
// identification string, which func_001F9790 compares with the IOP's.
#include "common.h"
#include "asm_func.h"
#include "system.h"

ASM_FUNC(func_001F6900);

ASM_FUNC(func_001F6910);

ASM_FUNC(func_001F6920);

ASM_FUNC(func_001F6930);

ASM_FUNC(func_001F6940);

ASM_FUNC(func_001F6950);

ASM_FUNC(func_001F6960);

ASM_FUNC(func_001F6970);

ASM_FUNC(func_001F6980);

ASM_FUNC(func_001F6990);

ASM_FUNC(func_001F69A0);

ASM_FUNC(func_001F69B0);

ASM_FUNC(func_001F69C0);

ASM_FUNC(func_001F69D0);

ASM_FUNC(func_001F69E0);

ASM_FUNC(func_001F69F0);

ASM_FUNC(func_001F6A00);

ASM_FUNC(func_001F6A10);

ASM_FUNC(func_001F6A20);

ASM_FUNC(func_001F6A30);

ASM_FUNC(func_001F6A40);

ASM_FUNC(func_001F6A50);

ASM_FUNC(func_001F6A60);

ASM_FUNC(func_001F6A70);

ASM_FUNC(func_001F6A80);

ASM_FUNC(func_001F6A90);

ASM_FUNC(func_001F6AA0);

ASM_FUNC(func_001F6AB0);

ASM_FUNC(func_001F6AC0);

ASM_FUNC(func_001F6AD0);

ASM_FUNC(func_001F6AE0);

ASM_FUNC(func_001F6AF0);

ASM_FUNC(func_001F6B00);

ASM_FUNC(func_001F6B10);

ASM_FUNC(func_001F6B20);

ASM_FUNC(func_001F6B30);

ASM_FUNC(func_001F6B40);

ASM_FUNC(func_001F6B50);

ASM_FUNC(func_001F6B60);

ASM_FUNC(func_001F6B70);

ASM_FUNC(func_001F6B80);

ASM_FUNC(func_001F6B90);

ASM_FUNC(func_001F6BA0);

ASM_FUNC(func_001F6BB0);

ASM_FUNC(func_001F6BC0);

ASM_FUNC(func_001F6BD0);

ASM_FUNC(func_001F6BE0);

ASM_FUNC(func_001F6BF0);

ASM_FUNC(func_001F6C00);

ASM_FUNC(func_001F6C10);

ASM_FUNC(func_001F6C20);

ASM_FUNC(func_001F6C30);

ASM_FUNC(func_001F6C40);

ASM_FUNC(func_001F6C50);

ASM_FUNC(func_001F6C60);

ASM_FUNC(func_001F6C70);

ASM_FUNC(func_001F6C80);

ASM_FUNC(func_001F6C90);

ASM_FUNC(func_001F6CA0);

ASM_FUNC(func_001F6CB0);

ASM_FUNC(func_001F6CC0);

ASM_FUNC(func_001F6CD0);

ASM_FUNC(func_001F6CE0);

ASM_FUNC(func_001F6CF0);

ASM_FUNC(func_001F6D00);

ASM_FUNC(func_001F6D10);

ASM_FUNC(func_001F6D20);

ASM_FUNC(func_001F6D30);

s32 DisableInterrupts(void);
s32 EnableInterrupts(void);
s32 DisableInterruptCauseSyscall(s32 n);
s32 EnableInterruptCauseSyscall(s32 n);
s32 DisableDmaInterruptSyscall(s32 n);
s32 EnableDmaInterruptSyscall(s32 n);

s32 DisableInterruptCause(s32 n)
{
    u32 enabled = ReadCop0Status();
    enabled &= 0x10000;
    if (enabled) {
        DisableInterrupts();
    }
    s32 r = DisableInterruptCauseSyscall(n);
    Sync();
    if (enabled) {
        EnableInterrupts();
    }
    return r;
}

s32 EnableInterruptCause(s32 n)
{
    u32 enabled = ReadCop0Status();
    enabled &= 0x10000;
    if (enabled) {
        DisableInterrupts();
    }
    s32 r = EnableInterruptCauseSyscall(n);
    Sync();
    if (enabled) {
        EnableInterrupts();
    }
    return r;
}

s32 DisableDmaInterrupt(s32 n)
{
    u32 enabled = ReadCop0Status();
    enabled &= 0x10000;
    if (enabled) {
        DisableInterrupts();
    }
    s32 r = DisableDmaInterruptSyscall(n);
    Sync();
    if (enabled) {
        EnableInterrupts();
    }
    return r;
}

s32 EnableDmaInterrupt(s32 n)
{
    u32 enabled = ReadCop0Status();
    enabled &= 0x10000;
    if (enabled) {
        DisableInterrupts();
    }
    s32 r = EnableDmaInterruptSyscall(n);
    Sync();
    if (enabled) {
        EnableInterrupts();
    }
    return r;
}

char D_00276970[16] = { 'P', 's', 'I', 'I', 'l', 'i', 'b', 'k', 'e', 'r', 'n', 'l', '2', '4', '3', '0' };
