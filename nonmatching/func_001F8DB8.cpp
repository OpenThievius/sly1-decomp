// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 612/624, checked 2026-11-07
// NEAR: in its file, src/lib/iop_file_client.cpp (Sony's 2.9-ee-991111). Left: ours keeps
//       mode & 0x8000 in $s8 for both tests, where retail computes it twice and keeps the high
//       half of D_006284C0's address in $s8 instead (hoisted into both arms of the first test);
//       the slot search's first iteration then schedules differently. Tried: mode as u32, the
//       second test as != 0 and with its arms swapped, the reply buffer through a local pointer
//       before or after the first flush.
#include "common.h"

struct SemaParams_1F84D8 {
    s32 count;
    s32 max_count;
    s32 init_count;
    s32 wait_threads;
    u32 attr;
    u32 option;
};

struct Client_1F84D8 {
    s32 pad[9];
    s32 bound;
};

struct Handle_1F84D8 {
    s32 id;
    s32 used;
};

extern volatile s32 g_semaphoreSlots[32];
extern s32 g_fileClientOpen;
extern s32 D_002771C4;
extern u8 D_00627880[0xC40];
extern u8 D_006284C0[0x40];
extern u8 D_00628500[0x440];
extern u8 D_00628940[0x200];
extern u8 g_fileClient[0x28];

s32 NewSemaphore(SemaParams_1F84D8* params);
void FreeSemaphore(s32 sema);
s32 PostSemaphore(s32 sema);
s32 AwaitSemaphore(s32 sema);
s32 CallRemoteService(Client_1F84D8* client, s32 cmd, s32 mode, void* send, s32 send_size, void* recv, s32 recv_size, s32 a7, s32 a8);
void WriteBackDataCacheRange(void* data, s32 size);
s32 FindFileHandle(s32 a0);
s32 LockFileRequests(s32 unused);
void UnlockFileRequests();

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
    SemaParams_1F84D8 r;
    s32 out;

    p = (Handle_1F84D8*)FindFileHandle(fd);
    LockFileRequests(2);
    if (g_fileClientOpen == 0) {
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
    r.max_count = 1;
    r.init_count = 0;
    r.option = 0;
    h = NewSemaphore(&r);
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
    if (!(mode & 0x20000000)) {
        WriteBackDataCacheRange(buf, size);
    }
    WriteBackDataCacheRange(D_00628500, 0xA4);
    WriteBackDataCacheRange(g, 0x20);
    if (CallRemoteService((Client_1F84D8*)g_fileClient, 2, 0, D_00627880, 0x20, D_006284C0, 4, 0, 0) < 0) {
        FreeSemaphore(h);
        UnlockFileRequests();
        return -0xB;
    }
    v = *(s32*)((u32)D_006284C0 | 0x20000000);
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
