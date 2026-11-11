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

// A transfer to the IOP: the data, where it goes, its size and its flags.
struct Span_1F9AD8 {
    void* a;
    s32 b;
    s32 c;
    s32 d;
};

// The reset command: the channel's header, the command, the argument's length and the argument
// (the 0x68 bytes sent), then the rest of the label, which no code reads.
struct Cmd_1F9AD8 {
    union {
        u64 hdr;
        s32 w[2];
    };
    s32 w8;
    s32 padC;
    s32 len;
    void* q;
    u8 text[0x50];
    u8 rest[0x418];
};

// The kernel's semaphore parameters (func_001F6B20 creates one), two of them side by side.
struct Frame_001F9DC0 { s32 w[16]; };

// A system call to install: its number and its handler.
struct Syscall_1F9E50 {
    s32 num;
    s32* (*handler)(s32 value);
    s32 f8;
};

s32* FindKernelWord(s32 value);

Syscall_1F9E50 D_002771D8 = { 0x83, FindKernelWord, 0 };
s32 D_002771E4;
s32 D_002771E8;

static Cmd_1F9AD8 D_00628E40 __attribute__((aligned(64)));

void StopIopDma(char* text, void* q);
s32 ReadIopRegister(u32 a0);
u32 WriteIopRegister(u32 reg, u32 value);
s32 StartIopDma(Span_1F9AD8* span, s32 n);
s32 NewSemaphore(Frame_001F9DC0* q);
void InstallFirstKernelPatch();
s32 StartRequestThread();
void PrintBuffered(const char* fmt, ...);
void InitRemoteCalls(s32 a);
void ShutDownRemoteCalls(void);
void SetSystemCallHandlerForWordSearch(s32 num, s32* (*handler)(s32 value));
s32 RunKernelWordSearchSyscall(s32* (*handler)(s32 value));
void InstallSecondKernelPatch();
void func_001FA0A0(void);
void WriteBackDataCacheRange(Cmd_1F9AD8* a0, s32 a1);
void InstallThirdKernelPatch();

s32 SendIopReset(char* text, void* q)
{
    Span_1F9AD8 span;
    s32 len;
    s32 w;

    StopIopDma(text, q);
    w = ReadIopRegister(0x80000000);
    D_00628E40.q = q;
    len = 0;
    if (text[0] != 0) {
        do {
            D_00628E40.text[len] = (u8)text[len];
            len++;
        } while (text[len] != 0);
    }
    D_00628E40.w[1] = 0;
    D_00628E40.len = len;
    D_00628E40.w8 = (s32)0x80000003;
    D_00628E40.hdr = D_00628E40.hdr & 0xFFFFFFFF000000FFULL;
    *(u8*)&D_00628E40 = 0x68;
    span.a = &D_00628E40;
    span.b = w;
    span.c = 0x68;
    span.d = 0x44;
    WriteBackDataCacheRange(&D_00628E40, 0x68);
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
        func_001FA0A0();
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
extern const char D_0024EBC0[] = "TTY: packet size larger than expect\n";
extern const char D_0024EBE8[] = "TTY: receive error";
extern const char D_0024EC00[] = "TTY: send err %d\n";
extern const char D_0024EC18[] = "TTY: err ti->wlen=%08x\n";

ASM_FUNC(func_001F9D60);

ASM_FUNC(func_001F9DA8);

void CreateLibrarySemaphores(void)
{
    Frame_001F9DC0 f;
    f.w[1] = 1;
    f.w[2] = 1;
    f.w[9] = 1;
    f.w[10] = 1;
    D_002771E4 = NewSemaphore(&f);
    D_002771E8 = NewSemaphore((Frame_001F9DC0*)&f.w[8]);
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
    SetSystemCallHandlerForWordSearch(D_002771D8.num, D_002771D8.handler);
    s32 r = RunKernelWordSearchSyscall(FindKernelWord);
    return r - 0x20C;
}

ASM_FUNC(func_001F9E90);

LINKER_REMNANT(func_001F9EA0);

void InitKernelLibrary()
{
    CreateLibrarySemaphores();
    InstallKernelWordSearch();
    InstallFirstKernelPatch();
    StartRequestThread();
    InstallSecondKernelPatch();
    InstallThirdKernelPatch();
}
