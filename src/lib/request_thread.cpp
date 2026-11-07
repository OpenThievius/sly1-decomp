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
static s32 g_requestSemaphore;
static Queue_1F7020 g_requestRing;

s32 AwaitSemaphore(s32 h);
void RotateReadyThreads(s32 v);
void WakeThread(s32 v);
void PauseThread(s32 v);
s32 PrintToOutputHook(const char* fmt, ...);

extern const char D_0024E988[40] = "## internel error in libkernl.a!\n";

void RunRequestThread(Queue_1F7020* q)
{
    for (;;) {
        AwaitSemaphore(g_requestSemaphore);
        u32 i = q->head & 0x1FF;
        q->head = i + 1;
        switch (q->e[i].kind) {
        case 0:
            WakeThread(q->e[i].arg);
            break;
        case 1:
            RotateReadyThreads(q->e[i].arg);
            break;
        case 2:
            PauseThread(q->e[i].arg);
            break;
        default:
            PrintToOutputHook(D_0024E988);
            break;
        }
    }
}

struct Ctx_1F70F8 { s32 f0; void* f4; void* f8; s32 fC; void* f10; s32 f14; };
struct Init_1F70F8 { s32 a; s32 b; s32 c; };
struct Frame_1F70F8 { Ctx_1F70F8 ctx; u8 pad[0x18]; Init_1F70F8 init; u8 pad2[0x14]; };

s32 g_requestThreadId = 0;
extern u8 D_002832F0[];

s32 NewSemaphore(Init_1F70F8* p);
s32 MakeThread(Ctx_1F70F8* p);
void FreeSemaphore(s32 h);
void RunThread(s32 h, Queue_1F7020* q);
s32 GetCurrentThreadId(void);
void SetThreadPriority(s32 h, s32 v);

s32 StartRequestThread(void)
{
    Frame_1F70F8 f;
    if (g_requestThreadId > 0) {
        return -1;
    }
    f.init.c = 0;
    f.init.b = 0xFF;
    g_requestSemaphore = NewSemaphore(&f.init);
    if (g_requestSemaphore < 0) {
        return -1;
    }
    f.ctx.f4 = (void*)RunRequestThread;
    f.ctx.f8 = D_00625770;
    f.ctx.fC = 0x400;
    f.ctx.f10 = D_002832F0;
    f.ctx.f14 = 0;
    g_requestThreadId = MakeThread(&f.ctx);
    if (g_requestThreadId < 0) {
        FreeSemaphore(g_requestSemaphore);
        return -1;
    }
    g_requestRing.head = 0;
    g_requestRing.tail = 0;
    RunThread(g_requestThreadId, &g_requestRing);
    SetThreadPriority(GetCurrentThreadId(), 1);
    return g_requestThreadId;
}

INCLUDE_ASM(func_001F71D0);

LINKER_REMNANT(func_001F7268);
