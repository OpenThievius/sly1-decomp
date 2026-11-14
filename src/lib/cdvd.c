/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The CD/DVD library, one object in retail from 0x202D08 to the pad library (0x203FD0), as its
 * identification string names it: the remote calls to the IOP's CD/DVD modules (bind, the
 * commands of its two clients, the read and its end callback), the semaphores that keep one
 * command of each kind at a time, the wait on an alarm, and the handler of the interrupt it
 * installs. Its .data begins with the identification string, then the library's state words and
 * the buffers it sends and receives (on 64 bytes); its .bss holds the callback, the thread's
 * status and the other clients. Its .rodata holds the messages of its functions, after those of
 * functions the linker stripped (their remnants are here too). C, built by the cc1 of
 * 2.9-ee-991111 (config/cflags.tsv, docs/TOOLCHAIN.md). Written for this project from retail's
 * code. */
#include "common.h"
#include "remote_call_client.h"
#include "semaphore_params.h"
#include "asm_func.h"
#include "system.h"

/* What the read's end callback receives, in uncached memory: two byte counts, where each
 * goes and the bytes. */
typedef struct ReadTail {
    s32 n0;
    s32 n1;
    u8* dst0;
    u8* dst1;
    u8 src0[0x40];
    u8 src1[0x40];
} ReadTail;

/* The .data starts on 64 bytes (0x14 bytes of padding after the DMA library's); the words the
 * end callback writes in the interrupt (whether a command is busy, its status) are volatile. */
char g_discLibraryIdentification[16] __attribute__((aligned(64))) = "PsIIlibcdvd 2420";
s32 g_discMessagesEnabled = 0;
s32 D_00279414 = 0;
u32 g_discSLastCommand = 0;
u32 g_discNLastCommand = 0;
s32 g_discCallbackSemaphore = -1;
s32 g_discCallbackSuppressed = 0;
s32 g_discNSemaphore = -1;
s32 g_discSSemaphore = -1;
volatile s32 g_discNCommandBusy = 0;
volatile u32 D_00279434 = 0;
s32 D_00279438 = -1;
s32 D_0027943C = -1;
s32 D_00279440 = -1;
s32 D_00279444 = -1;
s32 D_00279448 = -1;
s32 D_0027944C = -1;
u32 g_discInitCount = 0;
volatile s32 g_discCommandResult = 0;
volatile s32 g_discLastCommandResult = 0;
u8 g_discNReceiveBuffer[128] __attribute__((aligned(64))) = { 0 };
u8 g_discReadRequest[0x1000] __attribute__((aligned(64))) = { 0 };
u8 g_discReadTail[192] __attribute__((aligned(64))) = { 0 };
u32 g_discReadResult[4] __attribute__((aligned(64))) = { 0 };
RemoteCallClient g_discNClient = { 0 };
u8 g_discReceiveBuffer[1088] __attribute__((aligned(64))) = { 0 };
u32 g_discSendBuffer[0x102] __attribute__((aligned(64))) = { 0 };
RemoteCallClient g_discSClient = { 0 };

static s32 D_0062A7C0;
static void (*g_discCallback)(s32);
/* The callback's argument: 8 bytes in retail, of which only the first word is read. */
static s32 g_discCallbackArguments[2];
static s32 g_discThreadId;
static u8 g_discThreadStatus[0x210];
static RemoteCallClient g_discInitClient;
static RemoteCallClient g_discModeClient;
static s32 g_discInitModeBuffer[4] __attribute__((aligned(64)));
/* What WaitDiscReady sends: its one word, in a buffer that runs to the pad library's .bss. */
static s32 g_discModeBuffer[12];

s32 ScheduleAlarm(u16 ticks, void (*handler)(s32, u16, s32), s32 arg);
s32 GetCurrentThreadId(void);
s32 QueryThreadStatus(s32 thread, void* status);
s32 NewSemaphore(SemaphoreParams* param);
s32 FreeSemaphore(s32 sema);
s32 PostSemaphore(s32 sema);
s32 PostSemaphoreFromInterrupt(s32 sema);
s32 AwaitSemaphore(s32 sema);
s32 TrySemaphore(s32 sema);
void PrintBuffered(const char* fmt, ...);
void InitRemoteCalls(s32 mode);
s32 DisableInterrupts(void);
s32 EnableInterrupts(void);
struct Packet_1FA068;
struct Channel_1FA068;
void SetCommandHandler(s32 cmd, void (*handler)(struct Packet_1FA068* packet, struct Channel_1FA068* channel), void* arg);
void ClearCommandHandler(s32 cmd);
void WriteBackDataCacheRange(void* start, s32 size);

void WakeDiscWaiter(s32 id, u16 time, s32 sema);
void EndDiscCommand(s32* code);
void CopyDiscReadTail(ReadTail* tail);
void CreateDiscSemaphores(void);
void RunDiscCallback(void);
s32 BeginDiscNCommand(s32 command);
s32 SyncDiscNCommand(s32 mode);
s32 SyncDiscSCommand(s32 mode);
s32 BeginDiscSCommand(s32 command);

/* The alarm handler of WaitDiscTicks: posts the waiter's semaphore and ends the handler. */
void WakeDiscWaiter(s32 id, u16 time, s32 sema)
{
    PostSemaphoreFromInterrupt(sema);
    SyncAndEnableInterrupts();
}

void WaitDiscTicks(u16 ticks)
{
    SemaphoreParams param;
    s32 sema;

    param.maxCount = 1;
    param.initCount = 0;
    param.option = 0;
    sema = NewSemaphore(&param);
    ScheduleAlarm(ticks, WakeDiscWaiter, sema);
    AwaitSemaphore(sema);
    FreeSemaphore(sema);
}

LINKER_REMNANT(func_00202D98);

/* The end of a command: called from the remote call's end callback, in the interrupt, with the
 * status it received. It releases the command's semaphore, and the callback's when one is set;
 * the words it reads and writes are shared with the threads, read and written as volatile. */
void EndDiscCommand(s32* code)
{
    g_discCommandResult = *code;
    g_discLastCommandResult = g_discCommandResult;
    if (g_discCommandResult == 11) {
        g_discCommandResult = 0;
        g_discNCommandBusy = 0;
    } else {
        PostSemaphoreFromInterrupt(*(volatile s32*)&g_discNSemaphore);
        if (D_00279414 && D_0062A7C0) {
            PostSemaphoreFromInterrupt(*(volatile s32*)&g_discCallbackSemaphore);
        } else {
            g_discNCommandBusy = 0;
        }
        g_discCommandResult = 0;
    }
}

LINKER_REMNANT(func_00202E40);

void CopyDiscReadTail(ReadTail* tail)
{
    ReadTail* q = (ReadTail*)((u32)tail | 0x20000000);
    s32 i;

    if (q->n0 > 0) {
        u8* d = q->dst0;
        for (i = 0; i < q->n0; i++) {
            d[i] = q->src0[i];
        }
    }
    if (q->n1 > 0) {
        u8* d = q->dst1;
        for (i = 0; i < q->n1; i++) {
            d[i] = q->src1[i];
        }
    }
    EndDiscCommand((s32*)&g_discCommandResult);
}

/* Creates the semaphores of the two clients' commands and of the callback, once. */
void CreateDiscSemaphores(void)
{
    SemaphoreParams param;

    if (*(volatile s32*)&g_discNSemaphore == -1 || *(volatile s32*)&g_discSSemaphore == -1) {
        param.option = 0;
        param.initCount = 1;
        param.maxCount = 1;
        *(volatile s32*)&g_discNSemaphore = NewSemaphore(&param);
        *(volatile s32*)&g_discSSemaphore = NewSemaphore(&param);
        param.initCount = 0;
        *(volatile s32*)&g_discCallbackSemaphore = NewSemaphore(&param);
        g_discNCommandBusy = 0;
    }
}

void DeleteDiscSemaphores(void)
{
    if (D_00279414) {
        /* A bare do/while(0), allowed for this function alone by the project's decision: retail
         * stores -1 here before loading D_00279420, and only this keeps the compiler from moving
         * the load first. */
        do { g_discCommandResult = -1; } while (0);
        PostSemaphore(g_discCallbackSemaphore);
    }
    FreeSemaphore(g_discNSemaphore);
    FreeSemaphore(g_discSSemaphore);
    FreeSemaphore(g_discCallbackSemaphore);
    DisableInterrupts();
    ClearCommandHandler(0x80000012);
    EnableInterrupts();
}

LINKER_REMNANT(func_00203008);

void RunDiscCallback(void)
{
    if (g_discCallback && !g_discCallbackSuppressed) {
        g_discCallback(g_discCallbackArguments[0]);
    }
}

s32 InstallDiscCallbackHandler(void)
{
    g_discCallbackSuppressed = 1;
    DisableInterrupts();
    SetCommandHandler(0x80000012, (void (*)(struct Packet_1FA068*, struct Channel_1FA068*))RunDiscCallback, 0);
    EnableInterrupts();
    g_discCallbackSuppressed = 0;
    D_0027943C = 1;
    return 1;
}

LINKER_REMNANT(func_002030B8);
/* The messages of functions the linker stripped, which no code reads. */
const char D_0024F560[] = "sceCdCbfunc= %d sceCdCbfunc_num= %d\n";
const char D_0024F588[] = "Libcdvd bind err CdSearchFile\n";
const char D_0024F5A8[] = "ee call cmd search %s\n";
const char D_0024F5C0[] = "search name %s\n";
const char D_0024F5D0[] = "search size %d\n";
const char D_0024F5E0[] = "search loc lbn %d\n";

/* Takes the semaphore of the first client's commands for `command` and binds the client once,
 * retrying after a busy wait (cc1 pads the one-instruction wait loop with four nops, for the
 * R5900's short-loop erratum). The semaphore word is read as volatile, as the end callback
 * releases it. */
s32 BeginDiscNCommand(s32 command)
{
    s32 i;

    CreateDiscSemaphores();
    if (*(volatile s32*)&g_discNSemaphore != TrySemaphore(*(volatile s32*)&g_discNSemaphore)) {
        if (g_discMessagesEnabled > 0) {
            PrintBuffered("Ncmd fail sema cur_cmd:%d keep_cmd:%d\n", command, g_discNLastCommand);
        }
        return 0;
    }
    g_discNLastCommand = command;
    QueryThreadStatus(g_discThreadId, g_discThreadStatus);
    if (SyncDiscNCommand(1)) {
        PostSemaphore(*(volatile s32*)&g_discNSemaphore);
        return 0;
    }
    InitRemoteCalls(0);
    if (D_00279438 < 0) {
        while (1) {
            if (BindRemoteService(&g_discNClient, 0x80000595, 0) < 0) {
                if (g_discMessagesEnabled > 0) {
                    PrintBuffered("Libcdvd bind err N CMD\n");
                }
                for (i = 0x100000; i != -1; i--) {
                }
                continue;
            }
            if (g_discNClient.server != 0)
                break;
            for (i = 0x100000; i != -1; i--) {
            }
        }
        D_00279438 = 0;
    }
    return 1;
}

s32 GetDiscDriveState(void)
{
    u32 recv;

    if (BeginDiscNCommand(2) == 0) {
        return 0;
    }
    recv = (u32)g_discNReceiveBuffer;
    if (CallRemoteService(&g_discNClient, 0xE, 0, 0, 0, (void*)recv, 4, 0, 0) < 0) {
        PostSemaphore(g_discNSemaphore);
        return 0;
    }
    recv = *(u32*)(recv | 0x20000000);
    PostSemaphore(g_discNSemaphore);
    return recv;
}

s32 SyncDiscNCommand(s32 mode)
{
    if (mode == 0) {
        if (g_discMessagesEnabled > 0) {
            PrintBuffered("N cmd wait\n");
        }
        while (g_discNCommandBusy != 0 || IsRemoteCallPending(&g_discNClient) != 0) {
            WaitDiscTicks(60);
        }
        return 0;
    }
    if (g_discNCommandBusy != 0 || IsRemoteCallPending(&g_discNClient)) {
        return 1;
    }
    return 0;
}

s32 SyncDiscSCommand(s32 mode)
{
    if (mode == 0) {
        if (g_discMessagesEnabled > 0) {
            PrintBuffered("S cmd wait\n");
        }
        while (IsRemoteCallPending(&g_discSClient) != 0) {
            WaitDiscTicks(60);
        }
        return 0;
    }
    return IsRemoteCallPending(&g_discSClient);
}

/* The same for the second client's commands. */
s32 BeginDiscSCommand(s32 command)
{
    s32 i;

    CreateDiscSemaphores();
    if (*(volatile s32*)&g_discSSemaphore != TrySemaphore(*(volatile s32*)&g_discSSemaphore)) {
        if (g_discMessagesEnabled > 0) {
            PrintBuffered("Scmd fail sema cur_cmd:%d keep_cmd:%d\n", command, g_discSLastCommand);
        }
        return 0;
    }
    g_discSLastCommand = command;
    QueryThreadStatus(g_discThreadId, g_discThreadStatus);
    if (SyncDiscSCommand(1)) {
        PostSemaphore(*(volatile s32*)&g_discSSemaphore);
        return 0;
    }
    InitRemoteCalls(0);
    if (D_00279448 < 0) {
        while (1) {
            if (BindRemoteService(&g_discSClient, 0x80000593, 0) < 0) {
                if (g_discMessagesEnabled > 0) {
                    PrintBuffered("Libcdvd bind err S cmd\n");
                }
                for (i = 0x100000; i != -1; i--) {
                }
                continue;
            }
            if (g_discSClient.server != 0)
                break;
            for (i = 0x100000; i != -1; i--) {
            }
        }
        D_00279448 = 0;
    }
    return 1;
}

/* Binds the first client to the IOP's disc service and sends it the mode; mode 5 ends the library
 * (its semaphores and handler), the others set them up. The callback's busy flag, which the
 * interrupt's callback reads, and the semaphore ids, which the end callback posts in the
 * interrupt, are written as volatile, as CreateDiscSemaphores writes them. */
s32 InitDiscLibrary(s32 mode)
{
    s32 r;
    s32 i;
    s32 result;
    s32 status;
    s32 a;
    s32 b;
    u32 recv;

    if (SyncDiscSCommand(1) != 0) {
        return 0;
    }
    InitRemoteCalls(0);
    g_discThreadId = GetCurrentThreadId();
    *(volatile s32*)&g_discCallbackSuppressed = 1;
    D_00279440 = -1;
    D_00279438 = -1;
    D_00279448 = -1;
    D_00279444 = -1;
    D_0027944C = -1;
    D_0027943C = -1;
    D_00279434 = 0;
    g_discInitCount++;
    while (1) {
        r = BindRemoteService(&g_discInitClient, 0x80000592, 0);
        if (r < 0) {
            if (g_discMessagesEnabled > 0) {
                PrintBuffered("Libcdvd bind err %d CD_Init %d\n", r, g_discInitCount);
            }
            for (i = 0x100000; i != -1; i--) {
            }
            continue;
        }
        if (g_discInitClient.server != 0) {
            g_discInitModeBuffer[0] = mode;
            D_0027944C = 0;
            WriteBackDataCacheRange(g_discInitModeBuffer, 4);
            recv = (u32)g_discReceiveBuffer;
            if (CallRemoteService(&g_discInitClient, 0, 0, g_discInitModeBuffer, 4, (void*)recv, 0x10, 0, 0) < 0) {
                *(volatile s32*)&g_discCallbackSuppressed = 0;
                return 0;
            }
            break;
        }
        for (i = 0x100000; i != -1; i--) {
        }
    }
    a = *(s32*)((recv + 4) | 0x20000000);
    b = *(s32*)((recv + 8) | 0x20000000);
    status = *(s32*)((recv + 12) | 0x20000000);
    result = 1;
    if (status != 0xFF) {
        if (status == 0xFE) {
            g_discMessagesEnabled = 1;
        } else if (a / 256 < 2 || b / 256 < 2) {
            result = 2;
        }
    }
    *(volatile s32*)&g_discCallbackSuppressed = 0;
    switch (mode) {
    case 5:
        if (g_discMessagesEnabled > 0) {
            PrintBuffered("Libcdvd Exit\n");
        }
        DeleteDiscSemaphores();
        *(volatile s32*)&g_discNSemaphore = -1;
        *(volatile s32*)&g_discSSemaphore = -1;
        *(volatile s32*)&g_discCallbackSemaphore = -1;
        break;
    case 0:
    case 1:
    default:
        CreateDiscSemaphores();
        InstallDiscCallbackHandler();
        break;
    }
    return result;
}

/* Waits until the drive is ready: binds the first client's ready service once (the flag set
 * inside the retry loop, which is written as an endless do-while), sends it the mode and returns
 * the reply's word, read uncached; 6 (or -1 for mode 8) when the semaphore is taken or a call
 * fails. */
s32 WaitDiscReady(s32 mode)
{
    s32 i;
    s32 r;
    s32 v;

    if (g_discMessagesEnabled > 0) {
        PrintBuffered("DiskReady 0\n");
    }
    CreateDiscSemaphores();
    if (*(volatile s32*)&g_discSSemaphore != TrySemaphore(*(volatile s32*)&g_discSSemaphore)) {
        return 6;
    }
    if (SyncDiscSCommand(1)) {
        PostSemaphore(*(volatile s32*)&g_discSSemaphore);
        return mode != 8 ? 6 : -1;
    }
    InitRemoteCalls(0);
    if (D_00279444 < 0) {
        do {
            if (BindRemoteService(&g_discModeClient, 0x8000059A, 0) < 0) {
                if (g_discMessagesEnabled > 0) {
                    PrintBuffered("Libcdvd bind err CdDiskReady\n");
                }
                for (i = 0x100000; i != -1; i--) {
                }
                continue;
            }
            if (g_discModeClient.server != 0) {
                D_00279444 = 0;
                break;
            }
            for (i = 0x100000; i != -1; i--) {
            }
        } while (1);
    }
    g_discModeBuffer[0] = mode;
    WriteBackDataCacheRange(g_discModeBuffer, 4);
    r = (s32)g_discReceiveBuffer;
    if (CallRemoteService(&g_discModeClient, 0, 0, g_discModeBuffer, 4, (void*)r, 4, 0, 0) < 0) {
        PostSemaphore(*(volatile s32*)&g_discSSemaphore);
        return mode != 8 ? 6 : -1;
    }
    if (g_discMessagesEnabled > 0) {
        PrintBuffered("DiskReady ended\n");
    }
    v = *(s32*)((u32)r | 0x20000000);
    PostSemaphore(g_discSSemaphore);
    return v;
}

u32 SendDiscSCommand22(u32 value)
{
    u32* send = g_discSendBuffer;
    u32 recv;
    s32 r;

    if (BeginDiscSCommand(0x22) != 0) {
        g_discSendBuffer[0] = value;
    } else {
        return 0;
    }
    WriteBackDataCacheRange(send, 4);
    recv = (u32)g_discReceiveBuffer;
    r = CallRemoteService(&g_discSClient, 0x22, 0, send, 4, g_discReceiveBuffer, 4, 0, 0);
    if (r < 0) {
        PostSemaphore(g_discSSemaphore);
        return 0;
    }
    recv = *(u32*)(recv | 0x20000000);
    PostSemaphore(g_discSSemaphore);
    return recv;
}

s32 GetDiscReadPosition(void)
{
    if (g_discCommandResult == 1)
        return *(u32*)((u32)g_discReadResult | 0x20000000);
    return 0;
}

/* A read's request: where and how many sectors, the buffer, the read mode's three bytes, and
 * where the IOP puts the tail and the result. */
typedef struct ReadRequest {
    s32 lsn;
    s32 sectors;
    void* buffer;
    u8 tries;
    u8 speed;
    u8 pattern;
    u8 pad0F;
    u8* tail;
    u32* result;
} ReadRequest;

/* The read mode: tries, speed and the sector pattern (2048, 2328 or 2340 bytes). */
typedef struct ReadMode {
    u8 tries;
    u8 speed;
    u8 pattern;
} ReadMode;

/* Starts a read of sectors into a buffer, the buffer and the request written back from the
 * data cache first; the end callback copies the tail. */
s32 ReadDiscSectors(s32 lsn, s32 sectors, void* buffer, ReadMode* mode)
{
    ReadRequest* r = (ReadRequest*)g_discReadRequest;
    s32 size;

    if (!(D_00279434 & 1)) {
        if (GetDiscDriveState() == 6)
            return 0;
    }
    if (BeginDiscNCommand(4) == 0)
        return 0;
    r->lsn = lsn;
    r->sectors = sectors;
    r->buffer = buffer;
    r->tries = mode->tries;
    r->speed = mode->speed;
    r->pattern = mode->pattern;
    r->tail = g_discReadTail;
    r->result = g_discReadResult;
    switch (mode->pattern) {
    case 1:
        size = sectors * 0x918;
        break;
    case 0:
        size = sectors << 11;
        break;
    case 2:
        size = sectors * 0x924;
        break;
    default:
        size = sectors << 11;
        break;
    }
    g_discReadResult[0] = 0;
    if (!(D_00279434 & 2))
        WriteBackDataCacheRange(buffer, size);
    WriteBackDataCacheRange(g_discReadTail, 0x90);
    WriteBackDataCacheRange(r, 0x18);
    WriteBackDataCacheRange(g_discReadResult, 4);
    if (g_discMessagesEnabled > 0)
        PrintBuffered("call cdread cmd\n");
    g_discCommandResult = 1;
    g_discNCommandBusy = 1;
    if (CallRemoteService(&g_discNClient, 1, 1, r, 0x18, 0, 0, (void (*)(void*))CopyDiscReadTail, g_discReadTail) < 0) {
        g_discCommandResult = 0;
        g_discNCommandBusy = 0;
        PostSemaphore(*(volatile s32*)&g_discNSemaphore);
        return 0;
    }
    if (g_discMessagesEnabled > 0)
        PrintBuffered("cdread end\n");
    return 1;
}

s32 GetDiscStatus(void)
{
    u32 base;
    s32 v;

    if (!BeginDiscSCommand(1))
        return 0;
    base = (u32)g_discReceiveBuffer;
    if (CallRemoteService(&g_discSClient, 3, 0, 0, 0, (void*)base, 4, 0, 0) < 0) {
        PostSemaphore(g_discSSemaphore);
        return 0;
    }
    v = *(s32*)(base | 0x20000000);
    PostSemaphore(g_discSSemaphore);
    return v;
}

s32 GetDiscError(void)
{
    u32 base;
    s32 v;

    if (!BeginDiscSCommand(3))
        return -1;
    base = (u32)g_discReceiveBuffer;
    if (CallRemoteService(&g_discSClient, 4, 0, 0, 0, (void*)base, 4, 0, 0) < 0) {
        PostSemaphore(g_discSSemaphore);
        return -1;
    }
    v = *(s32*)(base | 0x20000000);
    PostSemaphore(g_discSSemaphore);
    return v;
}

s32 StopDiscRead(void)
{
    s32 r;

    if (BeginDiscSCommand(0x1E) == 0) {
        return 0;
    }
    *(volatile s32*)&g_discCommandResult = 8;
    if (CallRemoteService(&g_discSClient, 0x16, 0, 0, 0, g_discReceiveBuffer, 4, 0, 0) < 0) {
        PostSemaphore(*(volatile s32*)&g_discSSemaphore);
        *(volatile s32*)&g_discCommandResult = 0;
        return 0;
    }
    *(volatile s32*)&g_discCommandResult = 0;
    r = *(s32*)((u32)g_discReceiveBuffer | 0x20000000);
    PostSemaphore(*(volatile s32*)&g_discSSemaphore);
    return r;
}

s32 CheckDiscChanged(s32 value, s32* out)
{
    s32 base;
    s32 r;
    u32* send = g_discSendBuffer;

    if (BeginDiscSCommand(0x1A) != 0) {
        g_discSendBuffer[0] = value;
    } else {
        return -1;
    }
    WriteBackDataCacheRange(send, 4);
    base = (s32)g_discReceiveBuffer;
    r = CallRemoteService(&g_discSClient, 5, 0, send, 4, (void*)base, 8, 0, 0);
    if (r < 0) {
        PostSemaphore(*(volatile s32*)&g_discSSemaphore);
        return -1;
    }
    if (out != 0) {
        *out = *(s32*)((u32)(base + 4) | 0x20000000);
    }
    base = *(s32*)((u32)base | 0x20000000);
    PostSemaphore(*(volatile s32*)&g_discSSemaphore);
    return base;
}
