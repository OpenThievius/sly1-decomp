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
char D_00279400[16] __attribute__((aligned(64))) = "PsIIlibcdvd 2420";
s32 D_00279410 = 0;
s32 D_00279414 = 0;
u32 D_00279418 = 0;
u32 D_0027941C = 0;
s32 D_00279420 = -1;
s32 D_00279424 = 0;
s32 g_discNSemaphore = -1;
s32 g_discSSemaphore = -1;
volatile s32 D_00279430 = 0;
u32 D_00279434 = 0;
s32 D_00279438 = -1;
s32 D_0027943C = -1;
s32 D_00279440 = -1;
s32 D_00279444 = -1;
s32 D_00279448 = -1;
s32 D_0027944C = -1;
u32 D_00279450 = 0;
volatile s32 D_00279454 = 0;
volatile s32 D_00279458 = 0;
u8 D_00279480[128] __attribute__((aligned(64))) = { 0 };
u8 D_00279500[0x1000] __attribute__((aligned(64))) = { 0 };
u8 D_0027A500[192] __attribute__((aligned(64))) = { 0 };
u32 D_0027A5C0[4] __attribute__((aligned(64))) = { 0 };
RemoteCallClient g_discNClient = { 0 };
u8 D_0027A600[1088] __attribute__((aligned(64))) = { 0 };
u32 D_0027AA40[0x102] __attribute__((aligned(64))) = { 0 };
RemoteCallClient g_discSClient = { 0 };

static s32 D_0062A7C0;
static void (*D_0062A7C4)(s32);
/* The callback's argument: 8 bytes in retail, of which only the first word is read. */
static s32 D_0062A7C8[2];
static s32 D_0062A7D0;
static u8 D_0062A7D8[0x210];
static RemoteCallClient D_0062A9E8;
static RemoteCallClient D_0062AA10;
static s32 D_0062AA40[4] __attribute__((aligned(64)));
static RemoteCallClient D_0062AA50;

s32 ScheduleAlarm(u16 ticks, void (*handler)(s32, u16, s32), s32 arg);
s32 GetCurrentThreadId(void);
s32 QueryThreadStatus(s32 thread, void* status);
s32 NewSemaphore(SemaphoreParams* param);
s32 FreeSemaphore(s32 sema);
s32 PostSemaphore(s32 sema);
s32 PostSemaphoreFromInterrupt(s32 sema);
s32 AwaitSemaphore(s32 sema);
s32 TrySemaphore(s32 sema);
s32 PrintBuffered(const char* format, ...);
void InitRemoteCalls(s32 mode);
s32 BindRemoteService(RemoteCallClient* client, u32 server, s32 mode);
s32 CallRemoteService(RemoteCallClient* client, s32 function, s32 mode, void* send, s32 send_size, void* receive,
                  s32 receive_size, void (*end)(void*), void* end_arg);
s32 IsRemoteCallPending(RemoteCallClient* client);
s32 DisableInterrupts(void);
s32 EnableInterrupts(void);
s32 SetCommandHandler(s32 cause, void (*handler)(void), s32 next);
s32 ClearCommandHandler(s32 cause);
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

INCLUDE_ASM(func_00202D08);

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
    D_00279454 = *code;
    D_00279458 = D_00279454;
    if (D_00279454 == 11) {
        D_00279454 = 0;
        D_00279430 = 0;
    } else {
        PostSemaphoreFromInterrupt(*(volatile s32*)&g_discNSemaphore);
        if (D_00279414 && D_0062A7C0) {
            PostSemaphoreFromInterrupt(*(volatile s32*)&D_00279420);
        } else {
            D_00279430 = 0;
        }
        D_00279454 = 0;
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
    EndDiscCommand((s32*)&D_00279454);
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
        *(volatile s32*)&D_00279420 = NewSemaphore(&param);
        D_00279430 = 0;
    }
}

void DeleteDiscSemaphores(void)
{
    if (D_00279414) {
        /* A bare do/while(0), allowed for this function alone by the project's decision: retail
         * stores -1 here before loading D_00279420, and only this keeps the compiler from moving
         * the load first. */
        do { D_00279454 = -1; } while (0);
        PostSemaphore(D_00279420);
    }
    FreeSemaphore(g_discNSemaphore);
    FreeSemaphore(g_discSSemaphore);
    FreeSemaphore(D_00279420);
    DisableInterrupts();
    ClearCommandHandler(0x80000012);
    EnableInterrupts();
}

LINKER_REMNANT(func_00203008);

void RunDiscCallback(void)
{
    if (D_0062A7C4 && !D_00279424) {
        D_0062A7C4(D_0062A7C8[0]);
    }
}

s32 InstallDiscCallbackHandler(void)
{
    D_00279424 = 1;
    DisableInterrupts();
    SetCommandHandler(0x80000012, RunDiscCallback, 0);
    EnableInterrupts();
    D_00279424 = 0;
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
        if (D_00279410 > 0) {
            PrintBuffered("Ncmd fail sema cur_cmd:%d keep_cmd:%d\n", command, D_0027941C);
        }
        return 0;
    }
    D_0027941C = command;
    QueryThreadStatus(D_0062A7D0, D_0062A7D8);
    if (SyncDiscNCommand(1)) {
        PostSemaphore(*(volatile s32*)&g_discNSemaphore);
        return 0;
    }
    InitRemoteCalls(0);
    if (D_00279438 < 0) {
        while (1) {
            if (BindRemoteService(&g_discNClient, 0x80000595, 0) < 0) {
                if (D_00279410 > 0) {
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

s32 func_00203230(void)
{
    u32 recv;

    if (BeginDiscNCommand(2) == 0) {
        return 0;
    }
    recv = (u32)D_00279480;
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
        if (D_00279410 > 0) {
            PrintBuffered("N cmd wait\n");
        }
        while (D_00279430 != 0 || IsRemoteCallPending(&g_discNClient) != 0) {
            WaitDiscTicks(60);
        }
        return 0;
    }
    if (D_00279430 != 0 || IsRemoteCallPending(&g_discNClient)) {
        return 1;
    }
    return 0;
}

s32 SyncDiscSCommand(s32 mode)
{
    if (mode == 0) {
        if (D_00279410 > 0) {
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
        if (D_00279410 > 0) {
            PrintBuffered("Scmd fail sema cur_cmd:%d keep_cmd:%d\n", command, D_00279418);
        }
        return 0;
    }
    D_00279418 = command;
    QueryThreadStatus(D_0062A7D0, D_0062A7D8);
    if (SyncDiscSCommand(1)) {
        PostSemaphore(*(volatile s32*)&g_discSSemaphore);
        return 0;
    }
    InitRemoteCalls(0);
    if (D_00279448 < 0) {
        while (1) {
            if (BindRemoteService(&g_discSClient, 0x80000593, 0) < 0) {
                if (D_00279410 > 0) {
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

INCLUDE_ASM(func_00203548);
INCLUDE_ASM(func_00203828);

/* The messages of func_00203548 and func_00203828, defined here while they are assembly (after
 * the last of them: a definition before an included function would leave the compiler in .rodata
 * for the next one's). */
const char D_0024F698[] = "Libcdvd bind err %d CD_Init %d\n";
const char D_0024F6B8[] = "Libcdvd Exit\n";
const char D_0024F6C8[] = "DiskReady 0\n";
const char D_0024F6D8[] = "Libcdvd bind err CdDiskReady\n";
const char D_0024F6F8[] = "DiskReady ended\n";

u32 func_00203A20(u32 value)
{
    u32* send = D_0027AA40;
    u32 recv;
    s32 r;

    if (BeginDiscSCommand(0x22) != 0) {
        D_0027AA40[0] = value;
    } else {
        return 0;
    }
    WriteBackDataCacheRange(send, 4);
    recv = (u32)D_0027A600;
    r = CallRemoteService(&g_discSClient, 0x22, 0, send, 4, D_0027A600, 4, 0, 0);
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
    if (D_00279454 == 1)
        return *(u32*)((u32)D_0027A5C0 | 0x20000000);
    return 0;
}

INCLUDE_ASM(func_00203B18);

/* The messages of func_00203B18, defined here while it is assembly. */
const char D_0024F710[] = "call cdread cmd\n";
const char D_0024F728[] = "cdread end\n";

s32 GetDiscStatus(void)
{
    u32 base;
    s32 v;

    if (!BeginDiscSCommand(1))
        return 0;
    base = (u32)D_0027A600;
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
    base = (u32)D_0027A600;
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
    *(volatile s32*)&D_00279454 = 8;
    if (CallRemoteService(&g_discSClient, 0x16, 0, 0, 0, D_0027A600, 4, 0, 0) < 0) {
        PostSemaphore(*(volatile s32*)&g_discSSemaphore);
        *(volatile s32*)&D_00279454 = 0;
        return 0;
    }
    *(volatile s32*)&D_00279454 = 0;
    r = *(s32*)((u32)D_0027A600 | 0x20000000);
    PostSemaphore(*(volatile s32*)&g_discSSemaphore);
    return r;
}

s32 CheckDiscChanged(s32 value, s32* out)
{
    s32 base;
    s32 r;
    u32* send = D_0027AA40;

    if (BeginDiscSCommand(0x1A) != 0) {
        D_0027AA40[0] = value;
    } else {
        return -1;
    }
    WriteBackDataCacheRange(send, 4);
    base = (s32)D_0027A600;
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
