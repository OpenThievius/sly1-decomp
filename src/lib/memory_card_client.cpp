// SPDX-License-Identifier: AGPL-3.0-or-later
// The memory card library's client, the whole object, 0x2093F0-0x20A190 (config/us/files.tsv):
// the binding to the IOP's memory card server and its version checks (func_002093F0), the calls
// that each send one request to the server through the SIF remote call (func_001F8290) and record
// it as the one in flight (D_0027AEC8), the wait for its end (func_00209B80), and the two
// completion handlers that copy the server's results out of uncached memory (func_002097E0,
// func_00209C60). Its .rodata is the binding's three messages and a fourth no code reads (the
// message of a function the linker stripped); its .data the library's identification string, the
// request in flight and the semaphore; its .bss the client record, the result pointers, and the
// 64-byte aligned request, name, transfer and reply buffers. The bytes of the stripped functions'
// last words (func_002095A8, ...) are linker remnants. Written for
// this project from retail's code.
#include "common.h"
#include "asm_func.h"
#include "system.h"
#include "remote_call_client.h"
#include "semaphore_params.h"

// The library's identification string, 16 characters without a terminator.
char g_cardLibraryIdentification[16] = { 'P', 's', 'I', 'I', 'l', 'i', 'b', 'm', 'c', ' ', ' ', ' ', '2', '4', '3', '0' };

// The request in flight (0 when none) and the semaphore that serialises the requests.
s32 g_cardRequestInFlight = 0;
s32 g_cardSemaphore = -1;

// The remote call's client record, bound to the server.
static RemoteCallClient g_cardClient __attribute__((aligned(64)));
// Where func_00209C60 stores the results of the request func_00209CB8 sent.
static u32* g_cardInfoOutputA;
static u32* g_cardInfoOutputB;
static u32* g_cardInfoOutputC;
// A 64-byte aligned buffer no code reads: the data of a function the linker stripped.
static u8 D_0062AD80[0x40] __attribute__((aligned(64)));

// The request sent to the server: 0x30 bytes, of which each command fills the words it uses.
// The read and close commands send the file's descriptor first; the read adds its length and the
// buffer and reply table.
struct CardReadRequest {
    s32 fd;           // 0x00
    u8 pad04[8];
    s32 size;         // 0x0C: the length asked for
    u8 pad10[8];
    void* buf;        // 0x18: the buffer the IOP fills
    void* tab;        // 0x1C: the reply table the completion handler reads
};
// The write sends the first bytes (up to 16, to align the rest) inside the request, and the
// address and length of the rest.
struct CardWriteRequest {
    s32 fd;           // 0x00
    u8 pad04[8];
    s32 restSize;     // 0x0C: the bytes after the head
    u8 pad10[4];
    u32 headSize;     // 0x14: the bytes carried in head
    s32 restAddr;     // 0x18: the address the IOP reads the rest from
    u8 pad1C[4];
    u8 head[16];      // 0x20
};
// The query of a card's information: which of three results the caller wants, and where the
// server writes them.
struct CardInfoRequest {
    s32 f00;
    s32 port;         // 0x04
    s32 slot;         // 0x08
    s32 wantThird;    // 0x0C: 1 when the caller gave a destination for the third result
    s32 wantSecond;   // 0x10
    s32 wantFirst;    // 0x14
    s32 f18;
    s32 table;        // 0x1C: the address of the transfer buffer
};
struct CardFormatRequest {
    s32 f0;
    s32 port;         // 0x04
    s32 slot;         // 0x08
};
union CardRequest {
    CardReadRequest read;
    CardWriteRequest write;
    CardInfoRequest info;
    CardFormatRequest format;
    u8 bytes[0x30];
};
static CardRequest g_cardRequestBuffer __attribute__((aligned(64)));

// A request that carries a name: five words, then the name.
struct CardNameRequest {
    s32 port;         // 0x00
    s32 slot;         // 0x04
    s32 f08;          // 0x08
    s32 entryCount;   // 0x0C: the entries a directory read asks for
    s32 entries;      // 0x10: the address the IOP writes the entries to
    char name[0x400]; // 0x14
};
static CardNameRequest g_cardPathRequestBuffer;

// The transfer buffer the completion handlers read.
static u8 g_cardReplyDirectoryBuffer[0x10C0] __attribute__((aligned(64)));

// The server's reply: the result of the call, then the versions in the binding's reply.
struct CardReply {
    s32 result;           // 0x00
    s32 serverVersion;    // 0x04
    s32 managerVersion;   // 0x08
    u8 pad0C[0x34];
};
static CardReply g_cardReplyBuffer __attribute__((aligned(64)));

extern "C" s32 NewSemaphore(SemaphoreParams* r);
void* CopyStringBounded(char* dst, const char* src, s32 max);
s32 SyncCardRequest(s32 noWait, s32* a1, s32* a2);
extern "C" s32 AwaitSemaphore(s32 sema);
extern "C" s32 TrySemaphore(s32 sema);
extern "C" void PostSemaphore(s32 sema);
extern "C" void InitRemoteCalls(s32 mode);
extern "C" s32 PrintFormatted(const char* fmt, ...);

s32 InitMemoryCardClient(void)
{
    if (g_cardSemaphore < 0) {
        SemaphoreParams req;
        req.option = 0;
        req.initCount = 1;
        req.maxCount = 1;
        g_cardSemaphore = NewSemaphore(&req);
    }
    SyncCardRequest(0, 0, 0);
    AwaitSemaphore(g_cardSemaphore);
    InitRemoteCalls(0);
    for (;;) {
        if (BindRemoteService(&g_cardClient, 0x80000400, 0) < 0) {
            PrintFormatted("bind error libmc \n");
            for (;;) {
            }
        }
        if (g_cardClient.server != 0) {
            break;
        }
        for (s32 i = 0x100000; i != 0; i--) {
        }
    }
    s32 r = CallRemoteService(&g_cardClient, 0xFE, 0, &g_cardRequestBuffer, 0x30, &g_cardReplyBuffer, 0xC, 0, 0);
    PostSemaphore(g_cardSemaphore);
    if (r < 0) {
        g_cardClient.server = 0;
        return r - 100;
    }
    if (g_cardReplyBuffer.serverVersion < 0x20A) {
        PrintFormatted("libmc: too old release of mcserv.irx\n");
        g_cardClient.server = 0;
        return -0x78;
    }
    if (g_cardReplyBuffer.managerVersion < 0x20E) {
        PrintFormatted("libmc: too old release of mcman.irx\n");
        g_cardClient.server = 0;
        return -0x79;
    }
    return g_cardReplyBuffer.result;
}

// The message of a function the linker stripped.
extern const char g_cardNewCardFailureMessage[] = "sceMcUdCheckNewCard RPC faild\n";

LINKER_REMNANT(func_002095A8);

s32 OpenCardFile(s32 a0, s32 a1, const char* a2, s32 a3)
{
    if (TrySemaphore(g_cardSemaphore) < 0) {
        return -200;
    }
    RemoteCallClient* pool = &g_cardClient;
    if (pool->server == 0) {
        PostSemaphore(g_cardSemaphore);
        return -100;
    }
    if (a2 == 0 || *a2 == 0) {
        PostSemaphore(g_cardSemaphore);
        return -210;
    }
    // The name is addressed first and the request through it: the original's pointer was the
    // name's, and the words before it the request's.
    char* name = g_cardPathRequestBuffer.name;
    CopyStringBounded(name, a2, 0x3FF);
    ((s32*)name)[-5] = a0;
    CardNameRequest* r = (CardNameRequest*)(name - 0x14);
    r->f08 = a3;
    r->slot = a1;
    r->name[0x3FF] = 0;
    s32 result = CallRemoteService(pool, 2, 1, r, 0x414, &g_cardReplyBuffer, 4, 0, 0);
    if (result == 0) {
        g_cardRequestInFlight = 2;
    } else {
        PostSemaphore(g_cardSemaphore);
    }
    return result;
}

s32 MakeCardDirectory(s32 a0, s32 a1, const char* a2)
{
    s32 r = OpenCardFile(a0, a1, a2, 0x40);
    if (r == 0) {
        g_cardRequestInFlight = 0xB;
    }
    return r;
}

s32 CloseCardFile(s32 value)
{
    s32 r;
    RemoteCallClient* elt;
    if (TrySemaphore(g_cardSemaphore) < 0) {
        return -200;
    }
    elt = &g_cardClient;
    if (elt->server == 0) {
        (void)PostSemaphore(g_cardSemaphore);
        return -100;
    }
    g_cardRequestBuffer.read.fd = value;
    r = CallRemoteService(elt, 3, 1, &g_cardRequestBuffer, 0x30, &g_cardReplyBuffer, 4, 0, 0);
    if (r == 0) {
        g_cardRequestInFlight = 3;
    } else {
        (void)PostSemaphore(g_cardSemaphore);
    }
    return r;
}

LINKER_REMNANT(func_002097D8);

// What the server leaves in the transfer buffer for the completion handler: two runs of bytes,
// each with its length and the destination it is copied to.
struct CardReplyCopy {
    s32 n0;
    s32 n1;
    u8* dst0;
    u8* dst1;
    u8 src0[0x40];
    u8 src1[0x40];
};

void CopyCardDirectoryReply(CardReplyCopy* p)
{
    CardReplyCopy* q = (CardReplyCopy*)((u32)p | 0x20000000);
    if (q->n0) {
        u8* d = q->dst0;
        for (s32 i = 0; i < q->n0; i++) {
            *d++ = q->src0[i];
        }
    }
    if (q->n1) {
        u8* d = q->dst1;
        for (s32 i = 0; i < q->n1; i++) {
            *d++ = q->src1[i];
        }
    }
}

extern "C" void WriteBackDataCacheRange(void* a, s32 b);

s32 ReadCardFile(s32 fd, void* buf, s32 size)
{
    RemoteCallClient* ctl;
    CardReadRequest* slot;
    void* tab;
    s32 r;
    if (TrySemaphore(g_cardSemaphore) < 0) {
        return -200;
    }
    ctl = &g_cardClient;
    if (ctl->server == 0) {
        PostSemaphore(g_cardSemaphore);
        return -100;
    }
    tab = g_cardReplyDirectoryBuffer;
    slot = &g_cardRequestBuffer.read;
    slot->fd = fd;
    slot->tab = tab;
    slot->buf = buf;
    slot->size = size;
    WriteBackDataCacheRange(buf, size);
    WriteBackDataCacheRange(tab, 0xC0);
    r = CallRemoteService(ctl, 5, 1, slot, 0x30, &g_cardReplyBuffer, 4, (RemoteCallEndFn)CopyCardDirectoryReply, tab);
    if (r == 0) {
        g_cardRequestInFlight = 5;
    } else {
        PostSemaphore(g_cardSemaphore);
    }
    return r;
}

extern "C" void SyncDataCache(s32 a);

s32 WriteCardFile(s32 self, const void* src, s32 n)
{
    s32 r;
    if (TrySemaphore(g_cardSemaphore) < 0) {
        return -200;
    }
    if (g_cardClient.server == 0) {
        PostSemaphore(g_cardSemaphore);
        return -100;
    }
    g_cardRequestBuffer.write.fd = self;
    if (n < 17) {
        g_cardRequestBuffer.write.headSize = n;
        g_cardRequestBuffer.write.restSize = 0;
        g_cardRequestBuffer.write.restAddr = 0;
    } else {
        u32 lo = (u32)src - 16;
        s32 off = (((u32)src - 1) & ~0xF) - lo;
        g_cardRequestBuffer.write.restSize = n - off;
        g_cardRequestBuffer.write.headSize = off;
        g_cardRequestBuffer.write.restAddr = (u32)src + off; // the address the IOP reads the rest from
    }
    {
        u32 i;
        for (i = 0; i < g_cardRequestBuffer.write.headSize; i++) {
            g_cardRequestBuffer.write.head[i] = ((const u8*)src)[i];
        }
    }
    SyncDataCache(0);
    r = CallRemoteService(&g_cardClient, 6, 1, &g_cardRequestBuffer, 0x30, &g_cardReplyBuffer, 4, 0, 0);
    if (r == 0) {
        g_cardRequestInFlight = 6;
    } else {
        PostSemaphore(g_cardSemaphore);
    }
    return r;
}

s32 QueueThreadRequest(s32 tid);

// The alarm handler of WaitCardTicks: wakes the waiting thread and ends the handler.
void WakeCardWaiter(s32 id, u16 time, s32 thread)
{
    QueueThreadRequest(thread);
    SyncAndEnableInterrupts();
}

extern "C" s32 GetCurrentThreadId(void);
extern "C" void ScheduleAlarm(s32 id, void (*cb)(s32 id, u16 time, s32 thread), s32 ctx);
void SleepCurrentThread(void);

void WaitCardTicks(u16 id)
{
    ScheduleAlarm(id, WakeCardWaiter, GetCurrentThreadId());
    SleepCurrentThread();
}

// With noWait zero it waits until the request in flight is done; with it set, it only tests.
s32 SyncCardRequest(s32 noWait, s32* a1, s32* a2)
{
    s32 ok;
    if (g_cardRequestInFlight == 0) {
        return -1;
    }
    ok = IsRemoteCallPending(&g_cardClient);
    if (noWait == 0 && ok != 0) {
        while (IsRemoteCallPending(&g_cardClient) != 0) {
            WaitCardTicks(60);
        }
        ok = 0;
    }
    ok = (ok == 0);
    if (a1 != 0) {
        *a1 = g_cardRequestInFlight;
    }
    if (ok != 0) {
        g_cardRequestInFlight = 0;
        if (a2 != 0) {
            *a2 = g_cardReplyBuffer.result;
        }
        (void)PostSemaphore(g_cardSemaphore);
    }
    return ok;
}

void CopyCardInfoReply(u32 base)
{
    volatile u32* regs = (volatile u32*)(base | 0x20000000);
    if (g_cardInfoOutputA) *g_cardInfoOutputA = regs[0];
    if (g_cardInfoOutputB) *g_cardInfoOutputB = regs[1];
    if (g_cardInfoOutputC) *g_cardInfoOutputC = regs[0x24];
}

s32 GetCardInfo(s32 a0, s32 a1, s32* a2, s32* a3, s32* a4)
{
    if (TrySemaphore(g_cardSemaphore) < 0) {
        return -200;
    }
    if (g_cardClient.server == 0) {
        PostSemaphore(g_cardSemaphore);
        return -100;
    }
    g_cardRequestBuffer.info.port = a0;
    g_cardRequestBuffer.info.slot = a1;
    g_cardRequestBuffer.info.table = (s32)g_cardReplyDirectoryBuffer;
    if (a2) {
        g_cardRequestBuffer.info.wantFirst = 1;
    } else {
        g_cardRequestBuffer.info.wantFirst = 0;
    }
    if (a3) {
        g_cardRequestBuffer.info.wantSecond = 1;
    } else {
        g_cardRequestBuffer.info.wantSecond = 0;
    }
    if (a4) {
        g_cardRequestBuffer.info.wantThird = 1;
    } else {
        g_cardRequestBuffer.info.wantThird = 0;
    }
    g_cardInfoOutputA = (u32*)a2;
    g_cardInfoOutputB = (u32*)a3;
    g_cardInfoOutputC = (u32*)a4;
    WriteBackDataCacheRange(g_cardReplyDirectoryBuffer, 0xC0);
    s32 result = CallRemoteService(&g_cardClient, 1, 1, &g_cardRequestBuffer, 0x30, &g_cardReplyBuffer, 4, (RemoteCallEndFn)CopyCardInfoReply, g_cardReplyDirectoryBuffer);
    if (result == 0) {
        g_cardRequestInFlight = 1;
    } else {
        PostSemaphore(g_cardSemaphore);
    }
    return result;
}

LINKER_REMNANT(func_00209E40);

s32 ReadCardDirectory(s32 a0, s32 a1, const char* name, s32 a3, s32 a4, void* a5)
{
    s32 status = TrySemaphore(g_cardSemaphore);
    if (status < 0) {
        return -200;
    }
    RemoteCallClient* mgr = &g_cardClient;
    if (g_cardClient.server == 0) {
        PostSemaphore(g_cardSemaphore);
        return -100;
    }
    if (name == 0 || *name == 0) {
        PostSemaphore(g_cardSemaphore);
        return -210;
    }
    CardNameRequest* rec = &g_cardPathRequestBuffer;
    rec->port = a0;
    rec->slot = a1;
    rec->f08 = a3;
    rec->entryCount = a4;
    rec->entries = (s32)a5;
    CopyStringBounded(rec->name, name, 0x3FF);
    rec->name[0x3FF] = 0;
    if (a4 >= 0) {
        WriteBackDataCacheRange(a5, a4 << 6);
    }
    s32 r = CallRemoteService(mgr, 0xD, 1, rec, 0x414, &g_cardReplyBuffer, 4, 0, 0);
    if (r == 0) {
        g_cardRequestInFlight = 0xD;
    } else {
        PostSemaphore(g_cardSemaphore);
    }
    return r;
}

LINKER_REMNANT(func_00209FA0);

s32 RequestCardFormat(s32 a, s32 b)
{
    s32 r = TrySemaphore(g_cardSemaphore);
    s32 res;
    if (r < 0) {
        return -200;
    }
    if (g_cardClient.server == 0) {
        PostSemaphore(g_cardSemaphore);
        return -100;
    }
    g_cardRequestBuffer.format.slot = b;
    g_cardRequestBuffer.format.port = a;
    res = CallRemoteService(&g_cardClient, 0x10, 1, &g_cardRequestBuffer, 0x30, &g_cardReplyBuffer, 4, 0, 0);
    if (res == 0) {
        (*(u32*)&g_cardRequestInFlight) = 0x10;
    } else {
        PostSemaphore(g_cardSemaphore);
    }
    return res;
}

LINKER_REMNANT(func_0020A070);

s32 RequestCardSpaceForPath(s32 a0, s32 a1, const char* a2)
{
    RemoteCallClient* reg;
    CardNameRequest* buf;
    s32 res;

    if (TrySemaphore(g_cardSemaphore) < 0) {
        return -200;
    }
    reg = (&g_cardClient);
    if (reg->server == 0) {
        PostSemaphore(g_cardSemaphore);
        return -100;
    }
    if (a2 == 0 || *a2 == 0) {
        PostSemaphore(g_cardSemaphore);
        return -210;
    }
    buf = &g_cardPathRequestBuffer;
    buf->port = a0;
    buf->slot = a1;
    CopyStringBounded(buf->name, a2, 0x3FF);
    buf->name[0x3FF] = 0;
    res = CallRemoteService(reg, 0x12, 1, buf, 0x414, &g_cardReplyBuffer, 4, 0, 0);
    if (res == 0) {
        g_cardRequestInFlight = 0x12;
    } else {
        PostSemaphore(g_cardSemaphore);
    }
    return res;
}
