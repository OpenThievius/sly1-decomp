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

// The library's identification string, 16 characters without a terminator.
char D_0027AEB8[16] = { 'P', 's', 'I', 'I', 'l', 'i', 'b', 'm', 'c', ' ', ' ', ' ', '2', '4', '3', '0' };

// The request in flight (0 when none) and the semaphore that serialises the requests.
s32 g_cardRequestInFlight = 0;
s32 g_cardSemaphore = -1;

// The remote call's client record, bound to the server.
static u8 g_cardClient[0x28] __attribute__((aligned(64)));
// Where func_00209C60 stores the results of the request func_00209CB8 sent.
static u32* D_0062AD68;
static u32* D_0062AD6C;
static u32* D_0062AD70;
// A 64-byte aligned buffer no code reads: the data of a function the linker stripped.
static u8 D_0062AD80[0x40] __attribute__((aligned(64)));
// The request sent to the server.
static u8 D_0062ADC0[0x30] __attribute__((aligned(64)));
// A request that carries a name: five words, then the name (func_002095B0 addresses the name).
static u8 D_0062ADF0[0x414];
// The transfer buffer the completion handlers read.
static u8 D_0062B240[0x10C0] __attribute__((aligned(64)));
// The server's reply.
static u8 D_0062C300[0x40] __attribute__((aligned(64)));

struct Req_2093F0 {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
};
struct Sema_2093F0 {
    u8 pad00[0x24];
    s32 f24;
};
struct Info_2093F0 {
    s32 f0;
    s32 f4;
    s32 f8;
};
struct Obj_209B80;

s32 NewSemaphore(Req_2093F0* r);
s32 SyncCardRequest(Obj_209B80* a0, s32* a1, s32* a2);
s32 AwaitSemaphore(s32 sema);
void InitRemoteCalls(s32 a);
s32 BindRemoteService(Sema_2093F0* p, u32 flags, s32 z);
s32 PrintFormatted(const char* msg);
s32 CallRemoteService(Sema_2093F0* p, s32 a1, s32 a2, u8* a3, s32 a4, Info_2093F0* a5, s32 a6, s32 a7, s32 a8);
void PostSemaphore(s32 sema);

s32 InitMemoryCardClient(void)
{
    if (g_cardSemaphore < 0) {
        Req_2093F0 req;
        req.f14 = 0;
        req.f08 = 1;
        req.f04 = 1;
        g_cardSemaphore = NewSemaphore(&req);
    }
    SyncCardRequest(0, 0, 0);
    AwaitSemaphore(g_cardSemaphore);
    InitRemoteCalls(0);
    for (;;) {
        if (BindRemoteService((Sema_2093F0*)g_cardClient, 0x80000400, 0) < 0) {
            PrintFormatted("bind error libmc \n");
            for (;;) {
            }
        }
        if (((Sema_2093F0*)g_cardClient)->f24 != 0) {
            break;
        }
        for (s32 i = 0x100000; i != 0; i--) {
        }
    }
    s32 r = CallRemoteService((Sema_2093F0*)g_cardClient, 0xFE, 0, D_0062ADC0, 0x30, (Info_2093F0*)D_0062C300, 0xC, 0, 0);
    PostSemaphore(g_cardSemaphore);
    if (r < 0) {
        ((Sema_2093F0*)g_cardClient)->f24 = 0;
        return r - 100;
    }
    if (((Info_2093F0*)D_0062C300)->f4 < 0x20A) {
        PrintFormatted("libmc: too old release of mcserv.irx\n");
        ((Sema_2093F0*)g_cardClient)->f24 = 0;
        return -0x78;
    }
    if (((Info_2093F0*)D_0062C300)->f8 < 0x20E) {
        PrintFormatted("libmc: too old release of mcman.irx\n");
        ((Sema_2093F0*)g_cardClient)->f24 = 0;
        return -0x79;
    }
    return ((Info_2093F0*)D_0062C300)->f0;
}

// The message of a function the linker stripped.
extern const char D_00250008[] = "sceMcUdCheckNewCard RPC faild\n";

LINKER_REMNANT(func_002095A8);

struct Rec_2095B0 { s32 f00; s32 f04; s32 f08; u8 pad0C[8]; u8 name[0x400]; };
struct Handle_2095B0;
struct Pool_2095B0;
struct Name_2095B0;

s32 TrySemaphore(Handle_2095B0* h);
void PostSemaphore(Handle_2095B0* h);
s32 CallRemoteService(Pool_2095B0* p, s32 a1, s32 a2, Rec_2095B0* r, s32 size, u8* desc, s32 a6, s32 a7, s32 extra);
s32 CopyStringBounded(Name_2095B0* dst, const char* src, s32 max);

s32 OpenCardFile(s32 a0, s32 a1, const char* a2, s32 a3)
{
    if (TrySemaphore((Handle_2095B0*)g_cardSemaphore) < 0) {
        return -200;
    }
    u8* pool = g_cardClient;
    if (*(s32*)(pool + 0x24) == 0) {
        PostSemaphore((Handle_2095B0*)g_cardSemaphore);
        return -100;
    }
    if (a2 == 0 || *a2 == 0) {
        PostSemaphore((Handle_2095B0*)g_cardSemaphore);
        return -210;
    }
    u8* name = D_0062ADF0 + 0x14;
    CopyStringBounded((Name_2095B0*)name, a2, 0x3FF);
    ((s32*)name)[-5] = a0;
    Rec_2095B0* r = (Rec_2095B0*)(name - 0x14);
    r->f08 = a3;
    r->f04 = a1;
    r->name[0x3FF] = 0;
    s32 result = CallRemoteService((Pool_2095B0*)pool, 2, 1, r, 0x414, D_0062C300, 4, 0, 0);
    if (result == 0) {
        g_cardRequestInFlight = 2;
    } else {
        PostSemaphore((Handle_2095B0*)g_cardSemaphore);
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

struct Hdl_209720 { s32 v; };
struct Elt_209720 { u8 pad[0x24]; s32 f24; };
struct Slot_209720 { s32 v; };

s32 TrySemaphore(Hdl_209720* h);
s32 PostSemaphore(Hdl_209720* h);
s32 CallRemoteService(Elt_209720* a, s32 b, s32 c, Slot_209720* d, s32 e, void* f, s32 g, s32 h, s32 i);

s32 CloseCardFile(s32 value)
{
    s32 r;
    Elt_209720* elt;
    if (TrySemaphore((*(Hdl_209720**)&g_cardSemaphore)) < 0) {
        return -200;
    }
    elt = (Elt_209720*)g_cardClient;
    if (elt->f24 == 0) {
        (void)PostSemaphore((*(Hdl_209720**)&g_cardSemaphore));
        return -100;
    }
    (*(Slot_209720*)&D_0062ADC0).v = value;
    r = CallRemoteService(elt, 3, 1, ((Slot_209720*)&D_0062ADC0), 0x30, D_0062C300, 4, 0, 0);
    if (r == 0) {
        g_cardRequestInFlight = 3;
    } else {
        (void)PostSemaphore((*(Hdl_209720**)&g_cardSemaphore));
    }
    return r;
}

LINKER_REMNANT(func_002097D8);

struct Pkt_2097E0 {
    s32 n0;
    s32 n1;
    u8* dst0;
    u8* dst1;
    u8 src0[0x40];
    u8 src1[0x40];
};

void CopyCardDirectoryReply(Pkt_2097E0* p)
{
    Pkt_2097E0* q = (Pkt_2097E0*)((u32)p | 0x20000000);
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

struct Dev_00209870 { u8 pad[0x4]; };
struct Ctl_00209870 { u8 pad[0x24]; s32 busy; };
struct Slot_00209870 { void* owner; u8 pad0[8]; void* arg2; u8 pad1[8]; void* arg1; void* tab; };

s32 TrySemaphore(Dev_00209870* d);
void PostSemaphore(Dev_00209870* d);
void WriteBackDataCacheRange(void* a, s32 b);
s32 CallRemoteService(Dev_00209870* a, s32 b, s32 c, void* d, s32 e, void* f, s32 g, void* h, void* i);

s32 ReadCardFile(void* a0, void* a1, void* a2)
{
    Ctl_00209870* ctl;
    Slot_00209870* slot;
    void* tab;
    s32 r;
    if (TrySemaphore((*(Dev_00209870**)&g_cardSemaphore)) < 0) {
        return -200;
    }
    ctl = (Ctl_00209870*)g_cardClient;
    if (ctl->busy == 0) {
        PostSemaphore((*(Dev_00209870**)&g_cardSemaphore));
        return -100;
    }
    tab = D_0062B240;
    slot = (Slot_00209870*)D_0062ADC0;
    slot->owner = a0;
    slot->tab = tab;
    slot->arg1 = a1;
    slot->arg2 = a2;
    WriteBackDataCacheRange(a1, (s32)a2);
    WriteBackDataCacheRange(tab, 0xC0);
    r = CallRemoteService((Dev_00209870*)ctl, 5, 1, slot, 0x30, D_0062C300, 4, (void*)CopyCardDirectoryReply, tab);
    if (r == 0) {
        g_cardRequestInFlight = 5;
    } else {
        PostSemaphore((*(Dev_00209870**)&g_cardSemaphore));
    }
    return r;
}

struct Pool_209990 { u8 pad000[0x24]; s32 f24; };
struct Obj_209990 { u8 pad000[0x20]; };
struct Ctx_209990 { s32 f00; u8 p04[8]; s32 f0C; u8 p10[4]; u32 f14; s32 f18; u8 p1C[4]; u8 buf[16]; };

s32 TrySemaphore(Obj_209990* a);
void PostSemaphore(Obj_209990* a);
void SyncDataCache(s32 a);
s32 CallRemoteService(Pool_209990* p, s32 a1, s32 a2, Ctx_209990* a3, s32 a4, u8* a5, s32 a6, s32 a7, s32 stk);

s32 WriteCardFile(s32 self, u32 src, s32 n)
{
    s32 r;
    if (TrySemaphore((*(Obj_209990**)&g_cardSemaphore)) < 0) {
        return -200;
    }
    if ((*(Pool_209990*)&g_cardClient).f24 == 0) {
        PostSemaphore((*(Obj_209990**)&g_cardSemaphore));
        return -100;
    }
    (*(Ctx_209990*)&D_0062ADC0).f00 = self;
    if (n < 17) {
        (*(Ctx_209990*)&D_0062ADC0).f14 = n;
        (*(Ctx_209990*)&D_0062ADC0).f0C = 0;
        (*(Ctx_209990*)&D_0062ADC0).f18 = 0;
    } else {
        u32 lo = src - 16;
        s32 off = ((src - 1) & ~0xF) - lo;
        (*(Ctx_209990*)&D_0062ADC0).f0C = n - off;
        (*(Ctx_209990*)&D_0062ADC0).f14 = off;
        (*(Ctx_209990*)&D_0062ADC0).f18 = src + off;
    }
    {
        u32 i;
        for (i = 0; i < (*(Ctx_209990*)&D_0062ADC0).f14; i++) {
            (*(Ctx_209990*)&D_0062ADC0).buf[i] = ((u8*)src)[i];
        }
    }
    SyncDataCache(0);
    r = CallRemoteService(((Pool_209990*)&g_cardClient), 6, 1, ((Ctx_209990*)&D_0062ADC0), 0x30, D_0062C300, 4, 0, 0);
    if (r == 0) {
        g_cardRequestInFlight = 6;
    } else {
        PostSemaphore((*(Obj_209990**)&g_cardSemaphore));
    }
    return r;
}

s32 QueueThreadRequest(s32 thread);

// The alarm handler of WaitCardTicks: wakes the waiting thread and ends the handler.
void WakeCardWaiter(s32 id, u16 time, s32 thread)
{
    QueueThreadRequest(thread);
    SyncAndEnableInterrupts();
}

s32 GetCurrentThreadId(void);
void ScheduleAlarm(s32 id, void (*cb)(s32 id, u16 time, s32 thread), s32 ctx);
void SleepCurrentThread(void);

void WaitCardTicks(u16 id)
{
    ScheduleAlarm(id, WakeCardWaiter, GetCurrentThreadId());
    SleepCurrentThread();
}

struct Q_209B80;
struct Dev_209B80;
s32 IsRemoteCallPending(Q_209B80* q);
s32 PostSemaphore(Dev_209B80* d);

s32 SyncCardRequest(Obj_209B80* a0, s32* a1, s32* a2)
{
    s32 ok;
    if (g_cardRequestInFlight == 0) {
        return -1;
    }
    ok = IsRemoteCallPending((Q_209B80*)g_cardClient);
    if (a0 == 0 && ok != 0) {
        while (IsRemoteCallPending((Q_209B80*)g_cardClient) != 0) {
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
            *a2 = (*(s32*)&D_0062C300);
        }
        (void)PostSemaphore((Dev_209B80*)g_cardSemaphore);
    }
    return ok;
}

void CopyCardInfoReply(u32 base)
{
    volatile u32* regs = (volatile u32*)(base | 0x20000000);
    if (D_0062AD68) *D_0062AD68 = regs[0];
    if (D_0062AD6C) *D_0062AD6C = regs[1];
    if (D_0062AD70) *D_0062AD70 = regs[0x24];
}

struct Rec_209CB8 { s32 f00; s32 f04; s32 f08; s32 f0C; s32 f10; s32 f14; s32 f18; s32 f1C; };
struct Handle_209CB8;
struct Pool_209CB8 { u8 pad[0x24]; s32 f24; };
struct Blk_209CB8;
typedef void (*Cb_209CB8)(u32 base);

s32 TrySemaphore(Handle_209CB8* h);
void PostSemaphore(Handle_209CB8* h);
s32 WriteBackDataCacheRange(Blk_209CB8* p, s32 size);
s32 CallRemoteService(Pool_209CB8* p, s32 a1, s32 a2, Rec_209CB8* r, s32 size, u8* desc, s32 a6, Cb_209CB8 cb, u8* extra);

s32 GetCardInfo(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4)
{
    if (TrySemaphore((Handle_209CB8*)g_cardSemaphore) < 0) {
        return -200;
    }
    if ((*(Pool_209CB8*)&g_cardClient).f24 == 0) {
        PostSemaphore((Handle_209CB8*)g_cardSemaphore);
        return -100;
    }
    (*(Rec_209CB8*)&D_0062ADC0).f04 = a0;
    (*(Rec_209CB8*)&D_0062ADC0).f08 = a1;
    (*(Rec_209CB8*)&D_0062ADC0).f1C = (s32)D_0062B240;
    if (a2) {
        (*(Rec_209CB8*)&D_0062ADC0).f14 = 1;
    } else {
        (*(Rec_209CB8*)&D_0062ADC0).f14 = 0;
    }
    if (a3) {
        (*(Rec_209CB8*)&D_0062ADC0).f10 = 1;
    } else {
        (*(Rec_209CB8*)&D_0062ADC0).f10 = 0;
    }
    if (a4) {
        (*(Rec_209CB8*)&D_0062ADC0).f0C = 1;
    } else {
        (*(Rec_209CB8*)&D_0062ADC0).f0C = 0;
    }
    (*(s32*)&D_0062AD68) = a2;
    (*(s32*)&D_0062AD6C) = a3;
    (*(s32*)&D_0062AD70) = a4;
    (void)WriteBackDataCacheRange((Blk_209CB8*)D_0062B240, 0xC0);
    s32 result = CallRemoteService(((Pool_209CB8*)&g_cardClient), 1, 1, ((Rec_209CB8*)&D_0062ADC0), 0x30, D_0062C300, 4, CopyCardInfoReply, D_0062B240);
    if (result == 0) {
        g_cardRequestInFlight = 1;
    } else {
        PostSemaphore((Handle_209CB8*)g_cardSemaphore);
    }
    return result;
}

LINKER_REMNANT(func_00209E40);

struct Lock_9E48;
struct Mgr_9E48;
struct Rec_9E48 { s32 f0; s32 f4; s32 f8; s32 fC; s32 f10; u8 name[0x400]; };

s32 TrySemaphore(Lock_9E48* lock);
void PostSemaphore(Lock_9E48* lock);
void* CopyStringBounded(u8* dst, const char* src, s32 max);
void WriteBackDataCacheRange(s32 a, s32 b);
s32 CallRemoteService(Mgr_9E48* a, s32 b, s32 c, Rec_9E48* d, s32 e, u8* f, s32 g, s32 h, s32 i);

s32 ReadCardDirectory(s32 a0, s32 a1, const char* name, s32 a3, s32 a4, s32 a5)
{
    s32 status = TrySemaphore((Lock_9E48*)g_cardSemaphore);
    if (status < 0) {
        return -200;
    }
    Mgr_9E48* mgr = (Mgr_9E48*)g_cardClient;
    if (*(s32*)(g_cardClient + 0x24) == 0) {
        PostSemaphore((Lock_9E48*)g_cardSemaphore);
        return -100;
    }
    if (name == 0 || *name == 0) {
        PostSemaphore((Lock_9E48*)g_cardSemaphore);
        return -210;
    }
    Rec_9E48* rec = (Rec_9E48*)D_0062ADF0;
    rec->f0 = a0;
    rec->f4 = a1;
    rec->f8 = a3;
    rec->fC = a4;
    rec->f10 = a5;
    CopyStringBounded((u8*)rec + 0x14, name, 0x3FF);
    ((u8*)rec)[0x413] = 0;
    if (a4 >= 0) {
        WriteBackDataCacheRange(a5, a4 << 6);
    }
    s32 r = CallRemoteService(mgr, 0xD, 1, rec, 0x414, D_0062C300, 4, 0, 0);
    if (r == 0) {
        g_cardRequestInFlight = 0xD;
    } else {
        PostSemaphore((Lock_9E48*)g_cardSemaphore);
    }
    return r;
}

LINKER_REMNANT(func_00209FA0);

struct Pool_209FA8 { u8 pad[0x24]; s32 busy; };
struct Req_209FA8 { s32 f0; s32 a; s32 b; };
struct Handle_209FA8 { s32 h; };

s32 TrySemaphore(Handle_209FA8* h);
void PostSemaphore(Handle_209FA8* h);
s32 CallRemoteService(Pool_209FA8* p, s32 a1, s32 a2, Req_209FA8* q, s32 a4, u8* a5, s32 a6, s32 a7, s32 a8);

s32 func_00209FA8(s32 a, s32 b)
{
    s32 r = TrySemaphore((Handle_209FA8*)(*(u32*)&g_cardSemaphore));
    s32 res;
    if (r < 0) {
        return -200;
    }
    if (((Pool_209FA8*)g_cardClient)->busy == 0) {
        PostSemaphore((Handle_209FA8*)(*(u32*)&g_cardSemaphore));
        return -100;
    }
    (*(Req_209FA8*)&D_0062ADC0).b = b;
    (*(Req_209FA8*)&D_0062ADC0).a = a;
    res = CallRemoteService(((Pool_209FA8*)&g_cardClient), 0x10, 1, ((Req_209FA8*)&D_0062ADC0), 0x30, D_0062C300, 4, 0, 0);
    if (res == 0) {
        (*(u32*)&g_cardRequestInFlight) = 0x10;
    } else {
        PostSemaphore((Handle_209FA8*)(*(u32*)&g_cardSemaphore));
    }
    return res;
}

LINKER_REMNANT(func_0020A070);

struct Reg_0020A078 {
    u8 pad0[0x24];
    s32 f24;
};

struct Buf_0020A078 {
    s32 f0;
    s32 f4;
    u8 pad8[0xC];
    s8 text14[0x400];
};

s32 TrySemaphore(s32 v);
void* CopyStringBounded(s8* dst, s8* src, s32 n);
Buf_0020A078* CallRemoteService(Reg_0020A078* self, s32 a1, s32 a2, Buf_0020A078* a3, s32 a4, u32* a5, s32 a6, s32 a7, s32 a8);

s32 func_0020A078(s32 a0, s32 a1, s8* a2)
{
    Reg_0020A078* reg;
    Buf_0020A078* buf;
    Buf_0020A078* res;

    if (TrySemaphore(g_cardSemaphore) < 0) {
        return -200;
    }
    reg = ((Reg_0020A078*)&g_cardClient);
    if (reg->f24 == 0) {
        PostSemaphore(g_cardSemaphore);
        return -100;
    }
    if (a2 == 0 || *a2 == 0) {
        PostSemaphore(g_cardSemaphore);
        return -210;
    }
    buf = ((Buf_0020A078*)&D_0062ADF0);
    buf->f0 = a0;
    buf->f4 = a1;
    CopyStringBounded(buf->text14, a2, 0x3FF);
    buf->text14[0x3FF] = 0;
    res = CallRemoteService(reg, 0x12, 1, buf, 0x414, ((u32*)&D_0062C300), 4, 0, 0);
    if (res == 0) {
        g_cardRequestInFlight = 0x12;
    } else {
        PostSemaphore(g_cardSemaphore);
    }
    return (s32)res;
}
