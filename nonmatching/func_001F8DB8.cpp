// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 612/624, checked 2026-11-06
// NEAR: in its file, src/lib/file_1F84D8.cpp (Sony's 2.9-ee-991111). Left: ours keeps
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

extern volatile s32 D_00277138[32];
extern s32 D_002771B8;
extern s32 D_002771C4;
extern u8 D_00627880[0xC40];
extern u8 D_006284C0[0x40];
extern u8 D_00628500[0x440];
extern u8 D_00628940[0x200];
extern u8 D_00628B40[0x28];

s32 func_001F6B20(SemaParams_1F84D8* params);
void func_001F6B30(s32 sema);
s32 func_001F6B40(s32 sema);
s32 func_001F6B60(s32 sema);
s32 func_001F8290(Client_1F84D8* client, s32 cmd, s32 mode, void* send, s32 send_size, void* recv, s32 recv_size, s32 a7, s32 a8);
void func_001FA7D8(void* data, s32 size);
s32 func_001F8538(s32 a0);
s32 func_001F89B8(s32 unused);
void func_001F89E8();

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

s32 func_001F8DB8(s32 fd, void* buf, s32 size)
{
    Read_1F8DB8* g = (Read_1F8DB8*)D_00627880;
    Handle_1F84D8* p;
    s32 mode;
    s32 h;
    s32 v;
    s32 i;
    SemaParams_1F84D8 r;
    s32 out;

    p = (Handle_1F84D8*)func_001F8538(fd);
    func_001F89B8(2);
    if (D_002771B8 == 0) {
        func_001F89E8();
        return -1;
    }
    if (p == 0 || (mode = p->used) == 0) {
        func_001F89E8();
        return -9;
    }
    g->id = p->id;
    g->index = ((s32)p - (s32)D_00628940) >> 4;
    g->buf = buf;
    g->size = size;
    r.max_count = 1;
    r.init_count = 0;
    r.option = 0;
    h = func_001F6B20(&r);
    g->sema = h;
    g->result = (s32)&out;
    g->result_size = 4;
    if (mode & 0x8000) {
        func_001F6B60(D_002771C4);
        for (i = 0; i < 32; i++) {
            if (g_semaphoreSlots[i] == -1) {
                g_semaphoreSlots[i] = g->sema;
                g->sema = -g->sema;
                break;
            }
        }
        func_001F6B40(D_002771C4);
    }
    if (!(mode & 0x20000000)) {
        func_001FA7D8(buf, size);
    }
    func_001FA7D8(D_00628500, 0xA4);
    func_001FA7D8(g, 0x20);
    if (func_001F8290((Client_1F84D8*)D_00628B40, 2, 0, D_00627880, 0x20, D_006284C0, 4, 0, 0) < 0) {
        func_001F6B30(h);
        func_001F89E8();
        return -0xB;
    }
    v = *(s32*)((u32)D_006284C0 | 0x20000000);
    func_001F89E8();
    if (v == 0) {
        func_001F6B30(h);
        return -0xB;
    }
    if (mode & 0x8000) {
        func_001F6B30(h);
        return 0;
    }
    func_001F6B60(h);
    func_001F6B30(h);
    return out;
}
