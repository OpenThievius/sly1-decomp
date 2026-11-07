// SPDX-License-Identifier: AGPL-3.0-or-later
// The kernel library's request thread, its own object from 0x1F7020 to 0x1F7270, built whole
// (config/us/files.tsv): the thread func_001F7020, which waits on the semaphore D_00625B70 and
// carries out the requests of the ring D_00625B78 (the system calls 0x33, 0x2B and 0x37 on
// their argument, a message for any other kind); the set-up func_001F70F8, which creates the
// semaphore and the thread on the stack D_00625770 and starts it once; and func_001F71D0
// (original assembly, compiled with an inline system call: config/us/original_asm.tsv), which
// queues a request and signals the semaphore, with the word the linker left after it. Its
// .rodata is the message, its .data the thread id D_00277128 and its .bss the stack, the
// semaphore id and the ring, 0x625770 to 0x625F80.
#include "common.h"
#include "asm_func.h"

struct Entry_1F7020 { u8 kind; u8 arg; };
struct Queue_1F7020 { u32 head; u32 tail; Entry_1F7020 e[0x200]; };

static u8 D_00625770[0x400];
static s32 D_00625B70;
static Queue_1F7020 D_00625B78;

s32 func_001F6B60(s32 h);
void func_001F6A70(s32 v);
void func_001F6AC0(s32 v);
void func_001F6AF0(s32 v);
s32 func_001F7B50(const char* fmt, ...);

extern const char D_0024E988[40] = "## internel error in libkernl.a!\n";

void func_001F7020(Queue_1F7020* q)
{
    for (;;) {
        func_001F6B60(D_00625B70);
        u32 i = q->head & 0x1FF;
        q->head = i + 1;
        switch (q->e[i].kind) {
        case 0:
            func_001F6AC0(q->e[i].arg);
            break;
        case 1:
            func_001F6A70(q->e[i].arg);
            break;
        case 2:
            func_001F6AF0(q->e[i].arg);
            break;
        default:
            func_001F7B50(D_0024E988);
            break;
        }
    }
}

struct Ctx_1F70F8 { s32 f0; void* f4; void* f8; s32 fC; void* f10; s32 f14; };
struct Init_1F70F8 { s32 a; s32 b; s32 c; };
struct Frame_1F70F8 { Ctx_1F70F8 ctx; u8 pad[0x18]; Init_1F70F8 init; u8 pad2[0x14]; };

s32 D_00277128 = 0;
extern u8 D_002832F0[];

s32 func_001F6B20(Init_1F70F8* p);
s32 func_001F6A10(Ctx_1F70F8* p);
void func_001F6B30(s32 h);
void func_001F6A20(s32 h, Queue_1F7020* q);
s32 func_001F6A90(void);
void func_001F6A50(s32 h, s32 v);

s32 func_001F70F8(void)
{
    Frame_1F70F8 f;
    if (D_00277128 > 0) {
        return -1;
    }
    f.init.c = 0;
    f.init.b = 0xFF;
    D_00625B70 = func_001F6B20(&f.init);
    if (D_00625B70 < 0) {
        return -1;
    }
    f.ctx.f4 = (void*)func_001F7020;
    f.ctx.f8 = D_00625770;
    f.ctx.fC = 0x400;
    f.ctx.f10 = D_002832F0;
    f.ctx.f14 = 0;
    D_00277128 = func_001F6A10(&f.ctx);
    if (D_00277128 < 0) {
        func_001F6B30(D_00625B70);
        return -1;
    }
    D_00625B78.head = 0;
    D_00625B78.tail = 0;
    func_001F6A20(D_00277128, &D_00625B78);
    func_001F6A50(func_001F6A90(), 1);
    return D_00277128;
}

ASM_FUNC(func_001F71D0);

LINKER_REMNANT(func_001F7268);
