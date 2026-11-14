// SPDX-License-Identifier: AGPL-3.0-or-later
// The kernel library's request thread, its own object from 0x1F7020 to 0x1F7270, built whole
// (config/us/files.tsv): the thread func_001F7020, which waits on the semaphore D_00625B70 and
// carries out the requests of the ring D_00625B78 (the system calls 0x33, 0x2B and 0x37 on
// their argument, a message for any other kind); the set-up func_001F70F8, which creates the
// semaphore and the thread on the stack D_00625770 and starts it once; and func_001F71D0
// (C with the kernel's interrupt-time thread-id call: docs/ASM_CLASSIFICATION.md), which
// queues a request and signals the semaphore, with the word the linker left after it. Its
// .rodata is the message, its .data the thread id D_00277128 and its .bss the stack, the
// semaphore id and the ring, 0x625770 to 0x625F80.
#include "common.h"
#include "asm_func.h"
#include "system.h"
#include "semaphore_params.h"

// One request of the ring: what to do (0 wakes a thread, 1 rotates the ready threads, 2 pauses a
// thread) and the thread it is for.
struct RequestEntry { u8 kind; u8 arg; };
// The ring of requests: the index of the next to carry out, the index of the next free entry.
struct RequestRing { u32 head; u32 tail; RequestEntry e[0x200]; };

static u8 D_00625770[0x400];
static s32 g_requestSemaphore;
static RequestRing g_requestRing;

extern "C" s32 AwaitSemaphore(s32 h);
void RotateReadyThreads(s32 v);
void WakeThread(s32 v);
void PauseThread(s32 v);
void PrintToOutputHook(const char* fmt, ...);

extern const char D_0024E988[40] = "## internel error in libkernl.a!\n";

void RunRequestThread(RequestRing* q)
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

// What MakeThread creates a thread from: the function it runs, its stack and the stack's size.
struct ThreadParams { s32 f0; void* entry; void* stack; s32 stackSize; void* f10; s32 f14; };
struct StartFrame { ThreadParams ctx; u8 pad[0x18]; SemaphoreParams init; };

s32 g_requestThreadId = 0;
extern u8 D_002832F0[];

extern "C" s32 NewSemaphore(SemaphoreParams* p);
s32 MakeThread(ThreadParams* p);
extern "C" s32 FreeSemaphore(s32 h);
void RunThread(s32 h, RequestRing* q);
extern "C" s32 GetCurrentThreadId(void);
void SetThreadPriority(s32 h, s32 v);

s32 StartRequestThread(void)
{
    StartFrame f;
    if (g_requestThreadId > 0) {
        return -1;
    }
    f.init.initCount = 0;
    f.init.maxCount = 0xFF;
    g_requestSemaphore = NewSemaphore(&f.init);
    if (g_requestSemaphore < 0) {
        return -1;
    }
    f.ctx.entry = (void*)RunRequestThread;
    f.ctx.stack = D_00625770;
    f.ctx.stackSize = 0x400;
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

s32 WakeThreadFromInterrupt(s32 tid);
extern "C" s32 PostSemaphoreFromInterrupt(s32 h);

// From an interrupt handler: wakes thread tid unless it is the current one; for the current
// one, queues an empty request carrying its id and signals the request semaphore. Returns the
// wake's result, -1 when there is no request thread, or the id.
s32 QueueThreadRequest(s32 tid)
{
    s32 self = CurrentThreadIdFromInterrupt();
    if (self != tid) {
        return WakeThreadFromInterrupt(tid);
    }
    if ((u32)self >= 0x100 || g_requestThreadId == 0) {
        return -1;
    }
    u32 t = g_requestRing.tail & 0x1FF;
    g_requestRing.tail = t + 1;
    g_requestRing.e[t].kind = 0;
    g_requestRing.e[t].arg = self;
    PostSemaphoreFromInterrupt(g_requestSemaphore);
    return self;
}

LINKER_REMNANT(func_001F7268);
