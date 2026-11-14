// SPDX-License-Identifier: AGPL-3.0-or-later
// An object of the kernel library from 0x1F84D8 to 0x1F9690, built whole (config/us/files.tsv):
// the client of the IOP's file service over the command channel. func_001F8A28 opens it once
// (the flag D_002771B8): the reply handler func_001F85A8 and the command handler func_001F89F8
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
#include "remote_call_client.h"
#include "semaphore_params.h"
#include "asm_func.h"
#include "system.h"

#define UNCACHED(p) ((void*)((u32)(p) | 0x20000000))

// An open handle of the table D_00628940: the IOP's handle and whether it is in use.
struct FileHandleEntry {
    s32 id;       // 0x00
    s32 used;     // 0x04: 0 when free, else the open flags
    u8 pad08[8];
};

// The request CloseFile sends.
struct FileCloseRequest {
    s32 sema;
    s32 result;
    s32 resultSize;
    s32 id;
    s32 index;
};

// The request ControlFile sends: the control block goes with it.
struct FileControlBlock {
    u8 b[0x400];
};

struct FileControlRequest {
    s32 sema;
    s32 result;
    s32 resultSize;
    s32 id;
    s32 mode;
    FileControlBlock blk;
    s32 f414;
    s32 f418;
    s32 size;
};

// The request ReadFile sends.
struct FileReadRequest {
    s32 sema;
    s32 result;
    s32 resultSize;
    s32 id;
    void* buf;
    s32 size;
    s32 f18;
    s32 index;
};

// The request WriteFile sends: the bytes before the buffer's first 16-byte boundary go with it.
struct FileWriteRequest {
    s32 sema;
    s32 result;
    s32 resultSize;
    s32 id;
    void* buf;
    s32 size;
    s32 head;
    u8 bytes[16];
    s32 index;
};

// The request buffer of the file client: each call fills the layout of its own request in it,
// which all begin with the reply slot (the semaphore it waits on, where the result goes and its
// size) and the IOP's handle.
union FileRequest {
    FileCloseRequest close;
    FileReadRequest read;
    FileWriteRequest write;
    FileControlRequest control;
    u8 bytes[0xC40];
};

// What the handler of the command 0x80000013 is given with a command: a function and its argument.
struct FileCommandCall {
    void (*fn)(void* arg);  // 0x00: run when set
    void* arg;              // 0x04
};

volatile s32 g_semaphoreSlots[32] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
s32 g_fileClientOpen = 0;
s32 D_002771BC = -1;
s32 D_002771C0 = -1;
s32 D_002771C4 = -1;

static u8* D_00627840;
static u32* D_00627844;
static FileRequest D_00627880 __attribute__((aligned(64)));
static u8 D_006284C0[0x40] __attribute__((aligned(64)));
static u8 D_00628500[0x440] __attribute__((aligned(64)));
static FileHandleEntry D_00628940[32] __attribute__((aligned(64)));
static RemoteCallClient g_fileClient __attribute__((aligned(64)));
static s32 D_00628B68;
static u8 D_00628B80[0x40] __attribute__((aligned(64)));
static FileCommandCall D_00628BC0 __attribute__((aligned(64)));

extern "C" s32 NewSemaphore(SemaphoreParams* params);
extern "C" s32 FreeSemaphore(s32 sema);
extern "C" s32 PostSemaphore(s32 sema);
extern "C" void PostSemaphoreFromInterrupt(s32 sema);
extern "C" s32 AwaitSemaphore(s32 sema);
extern "C" void* CopyBytes(void* dst, const void* src, s32 n);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
extern "C" void InitRemoteCalls(s32 mode);
extern "C" s32 DisableInterrupts(void);
extern "C" s32 EnableInterrupts(void);
struct CommandPacket;
struct CommandChannel;
typedef void (*CommandHandler)(CommandPacket* packet, CommandChannel* channel);
extern "C" void SetCommandHandler(s32 cmd, CommandHandler handler, void* arg);
extern "C" void WriteBackDataCacheRange(void* data, s32 size);
void RunFileClientCallback(void* packet, FileCommandCall* call);

void CreateFileTableLock(void)
{
    if (D_002771C0 == -1) {
        SemaphoreParams b;
        b.initCount = 1;
        b.option = 0;
        b.maxCount = 1;
        D_002771C0 = NewSemaphore(&b);
        D_002771C4 = NewSemaphore(&b);
    }
}

s32 FindFileHandle(s32 a0)
{
    s32 s = a0;
    CreateFileTableLock();
    AwaitSemaphore(D_002771C0);
    if ((u32)a0 >= 0x20u) {
        PostSemaphore(D_002771C0);
        return 0;
    }
    s32 t = s << 4;
    t += (s32)D_00628940;
    PostSemaphore(D_002771C0);
    return t;
}

struct __attribute__((packed)) UnalignedWord {
    u32 v;
    static void Read(void* dst, void* src) { *(UnalignedWord*)dst = *(UnalignedWord*)UNCACHED(src); }
};

struct FileReplyCopy {
    s32 count0;
    s32 count1;
    u8 *dst0;
    u8 *dst1;
    u8 buf0[0x40];
    u8 buf1[0x40];
};

struct ReplyBlock144 {
    u8 b[0x144];
};

struct ReplyBlock40 {
    u8 b[0x40];
};

void HandleFileReply(void) {
    s32 sema;
    s32 type;
    void *dst;
    s32 size;
    void *pdst;
    u32 psize;
    s32 i;

    UnalignedWord::Read(&sema, D_00628500);
    UnalignedWord::Read(&type, D_00628500 + 4);
    UnalignedWord::Read(&dst, D_00628500 + 8);
    UnalignedWord::Read(&size, D_00628500 + 12);
    if (sema >= 0) {
        CopyBytes(dst, UNCACHED(D_00628500 + 16), size);
    }
    switch (type) {
    case 2: {
        struct FileReplyCopy *b = (struct FileReplyCopy *)UNCACHED(D_00628500 + 20);
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
        UnalignedWord::Read(&pdst, D_00628500 + 20);
        *(struct ReplyBlock144 *)pdst = *(struct ReplyBlock144 *)UNCACHED(D_00628500 + 24);
        break;
    case 12:
        UnalignedWord::Read(&pdst, D_00628500 + 20);
        *(struct ReplyBlock40 *)pdst = *(struct ReplyBlock40 *)UNCACHED(D_00628500 + 24);
        break;
    case 23:
    case 25:
    case 26:
        UnalignedWord::Read(&pdst, D_00628500 + 20);
        UnalignedWord::Read(&psize, D_00628500 + 24);
        if (psize > 0x400) {
            psize = 0x400;
        }
        CopyBytes(pdst, UNCACHED(D_00628500 + 28), psize);
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
        PostSemaphoreFromInterrupt(sema);
    }
}

void CreateFileRequestLock(void)
{
    if (D_002771BC == -1) {
        SemaphoreParams d;
        d.initCount = 1;
        d.maxCount = 1;
        d.option = 0;
        D_002771BC = NewSemaphore(&d);
    }
}

s32 LockFileRequests(s32 unused)
{
    CreateFileRequestLock();
    AwaitSemaphore(D_002771BC);
    return 0;
}

void UnlockFileRequests() { PostSemaphore(D_002771BC); }

// The handler of command 0x80000013: runs the call it is given, if any, and ends the handler.
void RunFileClientCallback(void* packet, FileCommandCall* call)
{
    if (call->fn != 0) {
        call->fn(call->arg);
    }
    SyncAndEnableInterrupts();
}

s32 OpenFileClient(void)
{
    s32 i;
    RemoteCallClient* q;
    FileCommandCall* g = &D_00628BC0;
    InitRemoteCalls(0);
    D_00628BC0.fn = 0;
    g->arg = 0;
    DisableInterrupts();
    SetCommandHandler(0x80000011, (CommandHandler)&HandleFileReply, D_00628B80);
    SetCommandHandler(0x80000013, (CommandHandler)&RunFileClientCallback, (void*)g);
    (s32)EnableInterrupts();
    for (;;) {
        q = &g_fileClient;
        if (BindRemoteService(q, 0x80000001, 0) < 0) return -1;
        if (q->server != 0) break;
        for (i = 0x100000; i != -1; ) i--;
    }
    CreateFileTableLock();
    AwaitSemaphore(D_002771C0);
    for (FileHandleEntry* p = D_00628940; p < D_00628940 + 32; p++) p->used = 0;
    PostSemaphore(D_002771C0);
    D_00627840 = D_00628500;
    if (CallRemoteService(&g_fileClient, 0xFF, 0, &D_00627840, 4, D_006284C0, 4, 0, 0) < 0) return 0xFFFEFFFF;
    *(UnalignedWord*)&D_00628B68 = *(UnalignedWord*)UNCACHED(D_006284C0);
    g_fileClientOpen = 1;
    return 0;
}

LINKER_REMNANT(func_001F8BF0);

s32 ForgetFileClient(void)
{
    g_fileClientOpen = 0;
    FillMemory(&D_00628B68, 0, 4);
    return 0;
}

LINKER_REMNANT(func_001F8C30);

struct FileRequestGate { static s32 Ready(s32 n) { LockFileRequests(n); return ((s32*)&g_fileClientOpen)[0]; } };
struct MinOf { static s32 Of(s32 a, s32 b) { return a < b ? a : b; } };

s32 CloseFile(s32 a0)
{
    FileCloseRequest* g = &D_00627880.close;
    FileHandleEntry* p;
    s32 h;
    s32 out;
    s32 v;
    SemaphoreParams ctor;
    u8* q;

    p = (FileHandleEntry*)FindFileHandle(a0);
    if (FileRequestGate::Ready(1) == 0) {
        UnlockFileRequests();
        return -1;
    }
    if (p == 0 || p->used == 0) {
        UnlockFileRequests();
        return -9;
    }
    g->id = p->id;
    g->index = ((s32)p - (s32)D_00628940) >> 4;
    ctor.maxCount = 1;
    ctor.initCount = 0;
    ctor.option = 0;
    h = NewSemaphore(&ctor);
    g->sema = h;
    g->result = (s32)&out;
    g->resultSize = 4;
    q = D_006284C0;
    v = CallRemoteService(&g_fileClient, 1, 0, g, 0x14, q, 4, 0, 0);
    if (v >= 0) {
        p->used = 0;
    } else {
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
    AwaitSemaphore(h);
    FreeSemaphore(h);
    return MinOf::Of(out, 0);
}


s32 ReadFile(s32 fd, void* buf, s32 size)
{
    FileReadRequest* g = &D_00627880.read;
    FileHandleEntry* p;
    s32 mode;
    s32 h;
    s32 v;
    s32 i;
    SemaphoreParams ctor;
    s32 out;

    p = (FileHandleEntry*)FindFileHandle(fd);
    if (FileRequestGate::Ready(2) == 0) {
        UnlockFileRequests();
        return -1;
    }
    if (p == 0 || p->used == 0) {
        UnlockFileRequests();
        return -9;
    }
    mode = p->used;
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
    g->resultSize = 4;
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
    if (CallRemoteService(&g_fileClient, 2, 0, &D_00627880, 0x20, D_006284C0, 4, 0, 0) < 0) {
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


s32 WriteFile(s32 fd, void* buf, s32 size)
{
    FileWriteRequest* g = &D_00627880.write;
    FileHandleEntry* p;
    s32 mode;
    s32 h;
    s32 v;
    s32 i;
    SemaphoreParams ctor;
    s32 out;
    s32 head;

    p = (FileHandleEntry*)FindFileHandle(fd);
    if (FileRequestGate::Ready(3) == 0) {
        UnlockFileRequests();
        return -1;
    }
    if (p == 0 || p->used == 0) {
        UnlockFileRequests();
        return -9;
    }
    mode = p->used;
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
    g->resultSize = 4;
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
    if (((u32)buf & 0xF) == 0)
        head = 0;
    else
        head = (((u32)buf >> 4) << 4) + 16 - (u32)buf;
    if (size < head)
        head = size;
    if (!(mode & 0x20000000))
        WriteBackDataCacheRange(buf, size);
    buf = UNCACHED(buf);
    g->head = head;
    for (s32 j = 0; j < head; j++)
        g->bytes[j] = ((u8*)buf)[j];
    if (CallRemoteService(&g_fileClient, 3, 0, &D_00627880, 0x30, D_006284C0, 4, 0, 0) < 0) {
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

s32 ControlFile(s32 a0, s32 mode, u32* out)
{
    FileControlRequest* g = &D_00627880.control;
    s32 ret = 1;
    FileHandleEntry* ent = (FileHandleEntry*)FindFileHandle(a0);
    (void)LockFileRequests(5);
    D_00627844 = out;
    if (g_fileClientOpen == 0) {
        (void)OpenFileClient();
    }
    if (ent == 0 || ent->used == 0) {
        UnlockFileRequests();
        return -9;
    }
    g->f414 = 0;
    g->f418 = 0;
    switch (mode) {
    case 1: {
        (void)AwaitSemaphore(D_002771C4);
        s32 i = 0;
        while (i < 32 && g_semaphoreSlots[i] == -1) {
            i++;
        }
        if (i == 32) {
            *D_00627844 = 0;
        } else {
            *D_00627844 = 1;
        }
        (void)PostSemaphore(D_002771C4);
        UnlockFileRequests();
        return 0;
    }
    case 2:
        *out = *(u32*)((u32)(D_00628500 + 0x10) | 0x20000000);
        UnlockFileRequests();
        return 0;
    case 3:
        *(u64*)out = *(u64*)((u32)(D_00628500 + 0x10) | 0x20000000);
        UnlockFileRequests();
        return 0;
    default:
        break;
    }
    g->id = ent->id;
    g->mode = mode;
    SemaphoreParams r;
    s32 sp30;
    if (out == 0) {
        g->size = 0;
    } else {
        g->size = 0x400;
        g->blk = *(FileControlBlock*)out;
    }
    r.maxCount = 1;
    r.initCount = 0;
    r.option = 0;
    s32 h = NewSemaphore(&r);
    g->sema = h;
    g->result = (s32)&sp30;
    g->resultSize = 4;
    WriteBackDataCacheRange(&D_00627880, 0x420);
    if (CallRemoteService(&g_fileClient, 5, 0, &D_00627880, 0x420, D_006284C0, 4, 0, 0) < 0) {
        FreeSemaphore(h);
        UnlockFileRequests();
        return -0xB;
    }
    u32 res = *(u32*)((u32)D_006284C0 | 0x20000000);
    UnlockFileRequests();
    if (res == 0) {
        FreeSemaphore(h);
        return -0xB;
    }
    (void)AwaitSemaphore(h);
    FreeSemaphore(h);
    ret = sp30;
    return ret;
}

LINKER_REMNANT(func_001F9638);

// Its last word of .data, after the reply handler's jump table in .rodata: no code reads it.
const char* D_002771C8 = "....";
