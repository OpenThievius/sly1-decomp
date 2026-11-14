// SPDX-License-Identifier: AGPL-3.0-or-later
// The kernel library from 0x1F9AD8 to 0x1F9EE8, built whole (config/us/files.tsv) as one file
// between two exact edges; it could be several objects. func_001F9AD8 sends the IOP a reset
// command (0x80000003) with its argument in the packet D_00628E40 and waits for the IOP to come
// back; func_001F9C18 tells whether it has; func_001F9C50 resets it with "rom0:UDNL " followed by
// an argument of up to 69 characters. The original assembly func_001F9D60 and func_001F9DA8
// disable and enable the interrupts. func_001F9DC0 creates two semaphores (D_002771E4,
// D_002771E8); func_001F9E50 installs func_001F9E08, which finds a word in the kernel's memory,
// as the system call D_002771D8 names (0x83), through the file-local system call stubs
// func_001F9E90 (0x74) and func_001F9E40 (0x83); func_001F9EA8 runs the library's set-ups. Its
// .rodata holds four "TTY:" messages no code reads.
#include "common.h"
#include "asm_func.h"
#include "semaphore_params.h"

// A transfer to the IOP: the data, where it goes, its size and its flags (the command channel's
// DmaTransfer, which holds the address as a word).
struct IopTransfer {
    void* src;
    s32 dst;
    s32 size;
    s32 mode;
};

// The reset command: the channel's header, the command, the argument's length and the argument
// (the 0x68 bytes sent), then the rest of the label, which no code reads.
struct IopResetCommand {
    union {
        u64 hdr;
        s32 w[2];
    };
    s32 cmd;      // 0x08
    s32 padC;
    s32 len;      // 0x10: the argument's length
    void* q;      // 0x14: the second argument
    u8 text[0x50];
    u8 rest[0x418];
};

// Two semaphore parameter records side by side, eight words apart: kept as one frame, which is
// what the compiler gives the two records declared together.
struct SemaphoreParamsPair {
    SemaphoreParams first;
    u8 pad18[8];
    SemaphoreParams second;
};

// A system call to install: its number and its handler.
struct SyscallEntry {
    s32 num;
    s32* (*handler)(s32 value);
    s32 f8;
};

s32* FindKernelWord(s32 value);

SyscallEntry g_kernelWordSearchCall = { 0x83, FindKernelWord, 0 };
s32 g_librarySemaphore0;
s32 g_librarySemaphore1;

static IopResetCommand g_iopResetPacket __attribute__((aligned(64)));

void StopIopDma(char* text, void* q);
s32 ReadIopRegister(u32 a0);
u32 WriteIopRegister(u32 reg, u32 value);
extern "C" s32 StartIopDma(IopTransfer* span, s32 n);
extern "C" s32 NewSemaphore(SemaphoreParams* q);
void InstallFirstKernelPatch();
s32 StartRequestThread();
extern "C" void PrintBuffered(const char* fmt, ...);
extern "C" void InitRemoteCalls(s32 mode);
void ShutDownRemoteCalls(void);
void SetSystemCallHandlerForWordSearch(s32 num, s32* (*handler)(s32 value));
s32 RunKernelWordSearchSyscall(s32* (*handler)(s32 value));
void InstallSecondKernelPatch();
void ClearImageEndRecordWord(void);
extern "C" void WriteBackDataCacheRange(IopResetCommand* a0, s32 a1);
void InstallThirdKernelPatch();

s32 SendIopReset(char* text, void* q)
{
    IopTransfer span;
    s32 len;
    s32 w;

    StopIopDma(text, q);
    w = ReadIopRegister(0x80000000);
    g_iopResetPacket.q = q;
    len = 0;
    if (text[0] != 0) {
        do {
            g_iopResetPacket.text[len] = (u8)text[len];
            len++;
        } while (text[len] != 0);
    }
    g_iopResetPacket.w[1] = 0;
    g_iopResetPacket.len = len;
    g_iopResetPacket.cmd = (s32)0x80000003;
    g_iopResetPacket.hdr = g_iopResetPacket.hdr & 0xFFFFFFFF000000FFULL;
    *(u8*)&g_iopResetPacket = 0x68;
    span.src = &g_iopResetPacket;
    span.dst = w;
    span.size = 0x68;
    span.mode = 0x44;
    WriteBackDataCacheRange(&g_iopResetPacket, 0x68);
    WriteIopRegister(4, 0x40000);
    if (StartIopDma(&span, 1) != 0) {
        WriteIopRegister(4, 0x10000);
        WriteIopRegister(4, 0x20000);
        WriteIopRegister(0x80000002, 0);
        WriteIopRegister(0x80000000, 0);
        return 1;
    }
    return 0;
}

s32 IsIopResetDone(void)
{
    if ((ReadIopRegister(4) & 0x40000) != 0) {
        ClearImageEndRecordWord();
        return 1;
    }
    return 0;
}

s32 ResetIop(char* arg)
{
    char buf[80];
    char* e = arg;
    const char* pre = "rom0:UDNL ";
    char* d;
    char* base;

    while (*e != 0) {
        e++;
    }
    base = arg - 11;
    if ((u32)(e - base) > 80) {
        PrintBuffered("too long parameter '%s'\n", arg);
        return 0;
    }
    InitRemoteCalls(0);
    ShutDownRemoteCalls();
    d = buf;
    while (*pre != 0) {
        *d++ = *pre++;
    }
    while (*arg != 0) {
        *d++ = *arg++;
    }
    *d = 0;
    return SendIopReset(buf, 0);
}

// The messages of the IOP's terminal, which no code reads.
extern const char g_ttyPacketSizeText[] = "TTY: packet size larger than expect\n";
extern const char g_ttyReceiveErrorText[] = "TTY: receive error";
extern const char g_ttySendErrorText[] = "TTY: send err %d\n";
extern const char g_ttyWordLengthErrorText[] = "TTY: err ti->wlen=%08x\n";

ASM_FUNC(func_001F9D60);

ASM_FUNC(func_001F9DA8);

void CreateLibrarySemaphores(void)
{
    SemaphoreParamsPair f;
    f.first.maxCount = 1;
    f.first.initCount = 1;
    f.second.maxCount = 1;
    f.second.initCount = 1;
    g_librarySemaphore0 = NewSemaphore(&f.first);
    g_librarySemaphore1 = NewSemaphore(&f.second);
}

s32* FindKernelWord(s32 value)
{
    s32* p = (s32*)0x80000000;
    while (*p != value)
        p++;
    return p;
}

ASM_FUNC(func_001F9E40);

s32 InstallKernelWordSearch(void)
{
    SetSystemCallHandlerForWordSearch(g_kernelWordSearchCall.num, g_kernelWordSearchCall.handler);
    s32 r = RunKernelWordSearchSyscall(FindKernelWord);
    return r - 0x20C;
}

ASM_FUNC(func_001F9E90);

LINKER_REMNANT(func_001F9EA0);

extern "C" void InitKernelLibrary()
{
    CreateLibrarySemaphores();
    InstallKernelWordSearch();
    InstallFirstKernelPatch();
    StartRequestThread();
    InstallSecondKernelPatch();
    InstallThirdKernelPatch();
}
