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

s32* func_001F9E08(s32 value);

Syscall_1F9E50 D_002771D8 = { 0x83, func_001F9E08, 0 };
s32 D_002771E4;
s32 D_002771E8;

static Cmd_1F9AD8 D_00628E40 __attribute__((aligned(64)));

void func_001F6C40(char* text, void* q);
s32 func_001F6CF0(u32 a0);
u32 func_001F6CE0(u32 reg, u32 value);
s32 func_001F6CA0(Span_1F9AD8* span, s32 n);
s32 func_001F6B20(Frame_001F9DC0* q);
void func_001F6F48();
void func_001F70F8();
s32 func_001F7B88(const char* fmt, ...);
s32 func_001F7BE8(s32 a);
void func_001F7D88(void);
void func_001F9E90(s32 num, s32* (*handler)(s32 value));
s32 func_001F9E40(s32* (*handler)(s32 value));
void func_001F9FB8();
void func_001FA0A0(void);
void func_001FA7D8(Cmd_1F9AD8* a0, s32 a1);
void func_001FA8F8();

s32 func_001F9AD8(char* text, void* q)
{
    Span_1F9AD8 span;
    s32 len;
    s32 w;

    func_001F6C40(text, q);
    w = func_001F6CF0(0x80000000);
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
    func_001FA7D8(&D_00628E40, 0x68);
    func_001F6CE0(4, 0x40000);
    if (func_001F6CA0(&span, 1) != 0) {
        func_001F6CE0(4, 0x10000);
        func_001F6CE0(4, 0x20000);
        func_001F6CE0(0x80000002, 0);
        func_001F6CE0(0x80000000, 0);
        return 1;
    }
    return 0;
}

s32 func_001F9C18(void)
{
    if ((func_001F6CF0(4) & 0x40000) != 0) {
        func_001FA0A0();
        return 1;
    }
    return 0;
}

s32 func_001F9C50(char* arg)
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
        func_001F7B88("too long parameter '%s'\n", arg);
        return 0;
    }
    func_001F7BE8(0);
    func_001F7D88();
    d = buf;
    while (*pre != 0) {
        *d++ = *pre++;
    }
    while (*arg != 0) {
        *d++ = *arg++;
    }
    *d = 0;
    return func_001F9AD8(buf, 0);
}

// The messages of the IOP's terminal, which no code reads.
extern const char D_0024EBC0[] = "TTY: packet size larger than expect\n";
extern const char D_0024EBE8[] = "TTY: receive error";
extern const char D_0024EC00[] = "TTY: send err %d\n";
extern const char D_0024EC18[] = "TTY: err ti->wlen=%08x\n";

ASM_FUNC(func_001F9D60);

ASM_FUNC(func_001F9DA8);

void func_001F9DC0(void)
{
    Frame_001F9DC0 f;
    f.w[1] = 1;
    f.w[2] = 1;
    f.w[9] = 1;
    f.w[10] = 1;
    D_002771E4 = func_001F6B20(&f);
    D_002771E8 = func_001F6B20((Frame_001F9DC0*)&f.w[8]);
}

s32* func_001F9E08(s32 value)
{
    s32* p = (s32*)0x80000000;
    while (*p != value)
        p++;
    return p;
}

ASM_FUNC(func_001F9E40);

s32 func_001F9E50(void)
{
    func_001F9E90(D_002771D8.num, D_002771D8.handler);
    s32 r = func_001F9E40(func_001F9E08);
    return r - 0x20C;
}

ASM_FUNC(func_001F9E90);

LINKER_REMNANT(func_001F9EA0);

void func_001F9EA8()
{
    func_001F9DC0();
    func_001F9E50();
    func_001F6F48();
    func_001F70F8();
    func_001F9FB8();
    func_001FA8F8();
}
