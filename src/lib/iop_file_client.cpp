// SPDX-License-Identifier: AGPL-3.0-or-later
// An object of the kernel library from 0x1F84D8 to 0x1F9690, built whole (config/us/files.tsv):
// the client of the IOP's file service over the command channel. func_001F8A28 opens it once
// (the flag D_002771B8): the reply handler func_001F85A8 and the original assembly func_001F89F8
// are set for the commands 0x80000011 and 0x80000013, the client D_00628B40 is bound to the
// service, the table of 32 open handles D_00628940 is cleared and the reply buffer D_00628500 is
// handed over. func_001F84D8 and func_001F8968 create the two semaphores (D_002771C0 and
// D_002771C4, D_002771BC) that guard the table and the requests; func_001F89B8 and func_001F89E8
// take and release the request lock. func_001F8C38, func_001F8DB8, func_001F9028 and func_001F92E8
// send a request on a handle and wait for its reply; func_001F8538 gives a handle's entry. The
// reply handler copies the reply out of D_00628500's uncached address and frees the waiter's
// slot in g_semaphoreSlots. Its .data ends with the pointer D_002771C8 to its string "....",
// which no code reads.
#include "common.h"
#include "asm_func.h"

#define UNCACHED_1F84D8(p) ((void*)((u32)(p) | 0x20000000))

// The kernel's semaphore parameters (func_001F6B20 creates one).
struct SemaParams_1F84D8 {
    s32 count;
    s32 max_count;
    s32 init_count;
    s32 wait_threads;
    u32 attr;
    u32 option;
};

// A client of the command channel (src/lib/remote_call.cpp): 0x24 is set once it is bound.
struct Client_1F84D8 {
    s32 pad[9];
    s32 bound;
};

// An open handle of the table D_00628940: the IOP's handle and whether it is in use.
struct Handle_1F84D8 {
    s32 id;
    s32 used;
};

// The request func_001F8C38 sends.
struct Close_1F84D8 {
    s32 sema;
    s32 result;
    s32 result_size;
    s32 id;
    s32 index;
};

// The request func_001F92E8 sends.
struct Block_1F92E8 {
    u8 b[0x400];
};

struct Ioctl_1F92E8 {
    s32 sema;
    s32 result;
    s32 result_size;
    s32 id;
    s32 mode;
    Block_1F92E8 blk;
    s32 f414;
    s32 f418;
    s32 size;
};

// The handler of the command 0x80000013 and its argument.
struct Callback_1F84D8 {
    void (*func)(s32);
    s32 arg;
};

volatile s32 D_00277138[32] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
s32 D_002771B8 = 0;
s32 D_002771BC = -1;
s32 D_002771C0 = -1;
s32 D_002771C4 = -1;

static u8* D_00627840;
static u32* D_00627844;
static u8 D_00627880[0xC40] __attribute__((aligned(64)));
static u8 D_006284C0[0x40] __attribute__((aligned(64)));
static u8 D_00628500[0x440] __attribute__((aligned(64)));
static u8 D_00628940[0x200] __attribute__((aligned(64)));
static u8 D_00628B40[0x28] __attribute__((aligned(64)));
static s32 D_00628B68;
static u8 D_00628B80[0x40] __attribute__((aligned(64)));
static Callback_1F84D8 D_00628BC0 __attribute__((aligned(64)));

s32 func_001F6B20(SemaParams_1F84D8* params);
void func_001F6B30(s32 sema);
s32 func_001F6B40(s32 sema);
void func_001F6B50(s32 sema);
s32 func_001F6B60(s32 sema);
void* func_001F5A58(void* dst, const void* src, s32 n);
void func_001F5C0C(void* p, s32 value, s32 size);
s32 func_001F7BE8(s32 a);
s32 func_001F80C0(Client_1F84D8* client, u32 cmd, s32 mode);
s32 func_001F8290(Client_1F84D8* client, s32 cmd, s32 mode, void* send, s32 send_size, void* recv, s32 recv_size, s32 a7, s32 a8);
s32 func_001F9D60(void);
s32 func_001F9DA8(void);
void func_001FA4A0(u32 cmd, void* handler, void* arg);
void func_001FA7D8(void* data, s32 size);
void func_001F89F8();

void func_001F84D8(void)
{
    if (D_002771C0 == -1) {
        SemaParams_1F84D8 b;
        b.init_count = 1;
        b.option = 0;
        b.max_count = 1;
        D_002771C0 = func_001F6B20(&b);
        D_002771C4 = func_001F6B20(&b);
    }
}

s32 func_001F8538(s32 a0)
{
    s32 s = a0;
    func_001F84D8();
    func_001F6B60(D_002771C0);
    if ((u32)a0 >= 0x20u) {
        func_001F6B40(D_002771C0);
        return 0;
    }
    s32 t = s << 4;
    t += (s32)D_00628940;
    func_001F6B40(D_002771C0);
    return t;
}

struct __attribute__((packed)) Word_1F85A8 {
    u32 v;
    static void Read(void* dst, void* src) { *(Word_1F85A8*)dst = *(Word_1F85A8*)UNCACHED_1F84D8(src); }
};

struct Bytes_1F85A8 {
    s32 count0;
    s32 count1;
    u8 *dst0;
    u8 *dst1;
    u8 buf0[0x40];
    u8 buf1[0x40];
};

struct Block144_1F85A8 {
    u8 b[0x144];
};

struct Block40_1F85A8 {
    u8 b[0x40];
};

void func_001F85A8(void) {
    s32 sema;
    s32 type;
    void *dst;
    s32 size;
    void *pdst;
    u32 psize;
    s32 i;

    Word_1F85A8::Read(&sema, D_00628500);
    Word_1F85A8::Read(&type, D_00628500 + 4);
    Word_1F85A8::Read(&dst, D_00628500 + 8);
    Word_1F85A8::Read(&size, D_00628500 + 12);
    if (sema >= 0) {
        func_001F5A58(dst, UNCACHED_1F84D8(D_00628500 + 16), size);
    }
    switch (type) {
    case 2: {
        struct Bytes_1F85A8 *b = (struct Bytes_1F85A8 *)UNCACHED_1F84D8(D_00628500 + 20);
        if (b->count0 > 0) {
            u8 *d = b->dst0;
            for (i = 0; i < b->count0; i++) {
                d[i] = b->buf0[i];
            }
        }
        if (b->count1 > 0) {
            u8 *d = b->dst1;
            for (i = 0; i < b->count1; i++) {
                d[i] = b->buf1[i];
            }
        }
        break;
    }
    case 11:
        Word_1F85A8::Read(&pdst, D_00628500 + 20);
        *(struct Block144_1F85A8 *)pdst = *(struct Block144_1F85A8 *)UNCACHED_1F84D8(D_00628500 + 24);
        break;
    case 12:
        Word_1F85A8::Read(&pdst, D_00628500 + 20);
        *(struct Block40_1F85A8 *)pdst = *(struct Block40_1F85A8 *)UNCACHED_1F84D8(D_00628500 + 24);
        break;
    case 23:
    case 25:
    case 26:
        Word_1F85A8::Read(&pdst, D_00628500 + 20);
        Word_1F85A8::Read(&psize, D_00628500 + 24);
        if (psize > 0x400) {
            psize = 0x400;
        }
        func_001F5A58(pdst, UNCACHED_1F84D8(D_00628500 + 28), psize);
        break;
    }
    if (sema < 0) {
        sema = -sema;
        i = 0;
        for (;;) {
            if (g_semaphoreSlots[i] == sema) {
                g_semaphoreSlots[i] = -1;
                break;
            }
            if (++i >= 32) return;
        }
    } else {
        func_001F6B50(sema);
    }
}

void func_001F8968(void)
{
    if (D_002771BC == -1) {
        SemaParams_1F84D8 d;
        d.init_count = 1;
        d.max_count = 1;
        d.option = 0;
        D_002771BC = func_001F6B20(&d);
    }
}

s32 func_001F89B8(s32 unused)
{
    func_001F8968();
    func_001F6B60(D_002771BC);
    return 0;
}

void func_001F89E8() { func_001F6B40(D_002771BC); }

ASM_FUNC(func_001F89F8);

s32 func_001F8A28(void)
{
    s32 i;
    Client_1F84D8* q;
    Callback_1F84D8* g = &D_00628BC0;
    (s32)func_001F7BE8(0);
    D_00628BC0.func = 0;
    g->arg = 0;
    func_001F9D60();
    func_001FA4A0(0x80000011, (void*)&func_001F85A8, D_00628B80);
    func_001FA4A0(0x80000013, (void*)&func_001F89F8, (void*)g);
    (s32)func_001F9DA8();
    for (;;) {
        q = (Client_1F84D8*)D_00628B40;
        if (func_001F80C0(q, 0x80000001, 0) < 0) return -1;
        if (q->bound != 0) break;
        for (i = 0x100000; i != -1; ) i--;
    }
    func_001F84D8();
    func_001F6B60(D_002771C0);
    for (u8* p = D_00628940; p < D_00628940 + 0x200; p += 0x10) *(s32*)(p + 4) = 0;
    func_001F6B40(D_002771C0);
    D_00627840 = D_00628500;
    if (func_001F8290((Client_1F84D8*)D_00628B40, 0xFF, 0, &D_00627840, 4, D_006284C0, 4, 0, 0) < 0) return 0xFFFEFFFF;
    *(Word_1F85A8*)&D_00628B68 = *(Word_1F85A8*)UNCACHED_1F84D8(D_006284C0);
    D_002771B8 = 1;
    return 0;
}

LINKER_REMNANT(func_001F8BF0);

s32 func_001F8BF8(void)
{
    D_002771B8 = 0;
    func_001F5C0C(&D_00628B68, 0, 4);
    return 0;
}

LINKER_REMNANT(func_001F8C30);

struct Lock_1F8C38 { static s32 Ready(s32 n) { func_001F89B8(n); return ((s32*)&D_002771B8)[0]; } };
struct Min_1F8C38 { static s32 Of(s32 a, s32 b) { return a < b ? a : b; } };

s32 func_001F8C38(s32 a0)
{
    Close_1F84D8* g = (Close_1F84D8*)D_00627880;
    Handle_1F84D8* p;
    s32 h;
    s32 out;
    s32 v;
    SemaParams_1F84D8 ctor;
    u8* q;

    p = (Handle_1F84D8*)func_001F8538(a0);
    if (Lock_1F8C38::Ready(1) == 0) {
        func_001F89E8();
        return -1;
    }
    if (p == 0 || p->used == 0) {
        func_001F89E8();
        return -9;
    }
    g->id = p->id;
    g->index = ((s32)p - (s32)D_00628940) >> 4;
    ctor.max_count = 1;
    ctor.init_count = 0;
    ctor.option = 0;
    h = func_001F6B20(&ctor);
    g->sema = h;
    g->result = (s32)&out;
    g->result_size = 4;
    q = D_006284C0;
    v = func_001F8290((Client_1F84D8*)D_00628B40, 1, 0, g, 0x14, q, 4, 0, 0);
    if (v >= 0) {
        p->used = 0;
    } else {
        func_001F6B30(h);
        func_001F89E8();
        return -0xB;
    }
    v = *(s32*)((s32)q | 0x20000000);
    func_001F89E8();
    if (v == 0) {
        func_001F6B30(h);
        return -0xB;
    }
    func_001F6B60(h);
    func_001F6B30(h);
    return Min_1F8C38::Of(out, 0);
}

INCLUDE_ASM(func_001F8DB8);

INCLUDE_ASM(func_001F9028);

s32 func_001F92E8(s32 a0, s32 mode, u32* out)
{
    Ioctl_1F92E8* g = (Ioctl_1F92E8*)D_00627880;
    s32 ret = 1;
    Handle_1F84D8* ent = (Handle_1F84D8*)func_001F8538(a0);
    (void)func_001F89B8(5);
    D_00627844 = out;
    if (D_002771B8 == 0) {
        (void)func_001F8A28();
    }
    if (ent == 0 || ent->used == 0) {
        func_001F89E8();
        return -9;
    }
    g->f414 = 0;
    g->f418 = 0;
    switch (mode) {
    case 1: {
        (void)func_001F6B60(D_002771C4);
        s32 i = 0;
        while (i < 32 && g_semaphoreSlots[i] == -1) {
            i++;
        }
        if (i == 32) {
            *D_00627844 = 0;
        } else {
            *D_00627844 = 1;
        }
        (void)func_001F6B40(D_002771C4);
        func_001F89E8();
        return 0;
    }
    case 2:
        *out = *(u32*)((u32)(D_00628500 + 0x10) | 0x20000000);
        func_001F89E8();
        return 0;
    case 3:
        *(u64*)out = *(u64*)((u32)(D_00628500 + 0x10) | 0x20000000);
        func_001F89E8();
        return 0;
    default:
        break;
    }
    g->id = ent->id;
    g->mode = mode;
    SemaParams_1F84D8 r;
    s32 sp30;
    if (out == 0) {
        g->size = 0;
    } else {
        g->size = 0x400;
        g->blk = *(Block_1F92E8*)out;
    }
    r.max_count = 1;
    r.init_count = 0;
    r.option = 0;
    s32 h = func_001F6B20(&r);
    g->sema = h;
    g->result = (s32)&sp30;
    g->result_size = 4;
    func_001FA7D8(D_00627880, 0x420);
    if (func_001F8290((Client_1F84D8*)D_00628B40, 5, 0, D_00627880, 0x420, D_006284C0, 4, 0, 0) < 0) {
        func_001F6B30(h);
        func_001F89E8();
        return -0xB;
    }
    u32 res = *(u32*)((u32)D_006284C0 | 0x20000000);
    func_001F89E8();
    if (res == 0) {
        func_001F6B30(h);
        return -0xB;
    }
    (void)func_001F6B60(h);
    func_001F6B30(h);
    ret = sp30;
    return ret;
}

LINKER_REMNANT(func_001F9638);

// Its last word of .data, after the reply handler's jump table in .rodata: no code reads it.
const char* D_002771C8 = "....";
