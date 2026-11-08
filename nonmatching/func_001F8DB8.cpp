// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 628/624, checked 2026-11-08
// NEAR: in its file, src/lib/iop_file_client.cpp (Sony's 2.9-ee-991111). Left: ours computes
//       mode & 0x8000 once, before NewSemaphore, and keeps it in $s8 for both tests; retail
//       computes it at each test and keeps the high half of D_006284C0's address in $s8 from
//       the end of the first test (in both of its arms) to the call, and so has 3 more
//       instructions. The reply's address in a local q assigned before the first test (as
//       CloseFile has one) is the closest: retail's $s8 placement then appears, but for
//       D_00628500's address. Tried: q at the top, before the cache write-back or at the call,
//       the semaphore registration as an inline function, mode as u32, the second test as != 0
//       and with its arms swapped; tools/permute.py --auto. Written for this project from
//       retail's code.
#include "common.h"
#include "remote_call_client.h"
#include "semaphore_params.h"

#define UNCACHED_1F84D8(p) ((void*)((u32)(p) | 0x20000000))

struct Handle_1F84D8 {
    s32 id;
    s32 used;
};

extern volatile s32 g_semaphoreSlots[32];
extern s32 g_fileClientOpen;
extern s32 D_002771C4;
static u8 D_00627880[0xC40] __attribute__((aligned(64)));
static u8 D_006284C0[0x40] __attribute__((aligned(64)));
static u8 D_00628500[0x440] __attribute__((aligned(64)));
static u8 D_00628940[0x200] __attribute__((aligned(64)));
static u8 g_fileClient[0x28] __attribute__((aligned(64)));

s32 NewSemaphore(SemaphoreParams* params);
void FreeSemaphore(s32 sema);
s32 PostSemaphore(s32 sema);
s32 AwaitSemaphore(s32 sema);
s32 CallRemoteService(RemoteCallClient* client, s32 cmd, s32 mode, void* send, s32 send_size, void* recv, s32 recv_size, s32 a7, s32 a8);
void WriteBackDataCacheRange(void* data, s32 size);
s32 FindFileHandle(s32 a0);
s32 LockFileRequests(s32 unused);
void UnlockFileRequests();
struct Lock_1F8C38 { static s32 Ready(s32 n) { LockFileRequests(n); return ((s32*)&g_fileClientOpen)[0]; } };

// The request func_001F8DB8 sends.
struct Read_1F8DB8 {
    s32 sema;
    s32 result;
    s32 result_size;
    s32 id;
    void* buf;
    s32 size;
    s32 f18;
    s32 index;
};

s32 ReadFile(s32 fd, void* buf, s32 size)
{
    Read_1F8DB8* g = (Read_1F8DB8*)D_00627880;
    Handle_1F84D8* p;
    s32 mode;
    s32 h;
    s32 v;
    s32 i;
    SemaphoreParams ctor;
    s32 out;
    u8* q;

    p = (Handle_1F84D8*)FindFileHandle(fd);
    if (Lock_1F8C38::Ready(2) == 0) {
        UnlockFileRequests();
        return -1;
    }
    if (p == 0 || (mode = p->used) == 0) {
        UnlockFileRequests();
        return -9;
    }
    g->id = p->id;
    g->index = ((s32)p - (s32)D_00628940) >> 4;
    g->buf = buf;
    g->size = size;
    ctor.maxCount = 1;
    ctor.initCount = 0;
    ctor.option = 0;
    h = NewSemaphore(&ctor);
    g->sema = h;
    g->result = (s32)&out;
    g->result_size = 4;
    q = D_006284C0;
    if (mode & 0x8000) {
        AwaitSemaphore(D_002771C4);
        for (i = 0; i < 32; i++) {
            if (g_semaphoreSlots[i] == -1) {
                g_semaphoreSlots[i] = g->sema;
                g->sema = -g->sema;
                break;
            }
        }
        PostSemaphore(D_002771C4);
    }
    if (!(mode & 0x20000000)) {
        WriteBackDataCacheRange(buf, size);
    }
    WriteBackDataCacheRange(D_00628500, 0xA4);
    WriteBackDataCacheRange(g, 0x20);
    if (CallRemoteService((RemoteCallClient*)g_fileClient, 2, 0, D_00627880, 0x20, q, 4, 0, 0) < 0) {
        FreeSemaphore(h);
        UnlockFileRequests();
        return -0xB;
    }
    v = *(s32*)((s32)q | 0x20000000);
    UnlockFileRequests();
    if (v == 0) {
        FreeSemaphore(h);
        return -0xB;
    }
    if (mode & 0x8000) {
        FreeSemaphore(h);
        return 0;
    }
    AwaitSemaphore(h);
    FreeSemaphore(h);
    return out;
}
