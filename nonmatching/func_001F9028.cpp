// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 692/704, checked 2026-11-08
// NEAR: in its file, src/lib/iop_file_client.cpp (Sony's 2.9-ee-991111). The same miss as
//       ReadFile's (nonmatching/func_001F8DB8.cpp): ours keeps mode & 0x8000 in $s8 from
//       before NewSemaphore, where retail computes it at each test and holds the high half of
//       D_006284C0's address there; and the head's length is the other way round (retail's
//       bnez to the computation, ((buf >> 4) << 4) - (buf - 16), against ours reassociated to
//       ((buf >> 4) << 4) + 16 - buf). Written for this project from retail's code.
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

// The request func_001F9028 sends: the bytes before the buffer's first 16-byte boundary go with it.
struct Write_1F9028 {
    s32 sema;
    s32 result;
    s32 result_size;
    s32 id;
    void* buf;
    s32 size;
    s32 head;
    u8 bytes[16];
    s32 index;
};

s32 WriteFile(s32 fd, void* buf, s32 size)
{
    Write_1F9028* g = (Write_1F9028*)D_00627880;
    Handle_1F84D8* p;
    s32 mode;
    s32 h;
    s32 v;
    s32 i;
    SemaphoreParams ctor;
    s32 out;
    s32 head;
    u8* src;
    u8* q;

    p = (Handle_1F84D8*)FindFileHandle(fd);
    if (Lock_1F8C38::Ready(3) == 0) {
        UnlockFileRequests();
        return -1;
    }
    if (p == 0 || (mode = p->used) == 0) {
        UnlockFileRequests();
        return -9;
    }
    g->id = p->id;
    g->index = ((s32)p - (s32)D_00628940) >> 4;
    g->size = size;
    g->buf = buf;
    ctor.maxCount = 1;
    ctor.initCount = 0;
    ctor.option = 0;
    h = NewSemaphore(&ctor);
    g->sema = h;
    g->result = (s32)&out;
    g->result_size = 4;
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
    if (((u32)buf & 0xF) != 0)
        head = (((u32)buf >> 4) << 4) - ((u32)buf - 16);
    else
        head = 0;
    if (size < head)
        head = size;
    if (!(mode & 0x20000000))
        WriteBackDataCacheRange(buf, size);
    src = (u8*)UNCACHED_1F84D8(buf);
    g->head = head;
    for (i = 0; i < head; i++)
        g->bytes[i] = src[i];
    q = D_006284C0;
    if (CallRemoteService((RemoteCallClient*)g_fileClient, 3, 0, D_00627880, 0x30, q, 4, 0, 0) < 0) {
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
