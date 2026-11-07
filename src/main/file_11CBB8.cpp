// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "t2196.h"
#include "world.h"
#include "entry_pool.h"
#include "buffered_stream.h"
#include "script_value.h"

// The IOP command and sound channel file, 0x11CBB8-0x11E560: its .rodata (the strings, among
// them those of functions the linker stripped) runs from 0x249428 to 0x249868, its .data from
// 0x25C340 to 0x260E60. Its assert strings name it "989snd.c".

extern const char D_00249428[40] = "error: sceSifBindRpc in %s, at line %d\n";
extern const char D_00249450[16] = "989snd.c";
extern const char D_00249460[136] = "989snd.c: Sif says RPC isn't busy, but we still don't have returns from the IOP!\n\000\000\000\000\000\000\000snd_BankLoad: Load already in progress!\n";
extern const char D_002494E8[136] = "989snd.c: RPC collision!\n\000\000\000\000\000\000\000989snd.c: RPC call has failed inside snd_BankLoad\n\000\000\000\000\000\000snd_BankLoad_CB: Load already in progress!\n";
extern const char D_00249570[48] = "snd_BankLoadByLoc: Load already in progress!\n";
extern const char D_002495A0[32] = "snd_BankLoadByLoc: CD BUSY!\n";
extern const char D_002495C0[536] = "989snd.c: RPC call has failed inside snd_BankLoadByLoc\n\000snd_BankLoadFromEE: Load already in progress!\n\000\000snd_BankLoadFromEE: CD BUSY!\n\000\000\000989snd.c: RPC call has failed inside snd_BankLoadFromEE\n\000\000\000\000\000\000\000\000snd_BankLoadFromEE_CB: Load already in progress!\n\000\000\000\000\000\000\000snd_BankLoadFromEE_CB: CD BUSY!\n\000\000\000\000\000\000\000\000snd_BankLoadFromIOP: Load already in progress!\n\000snd_BankLoadFromIOP: CD BUSY!\n\000\000989snd.c: RPC call has failed inside snd_BankLoadFromIOP\n\000\000\000\000\000\000\000snd_BankLoadFromIOP_CB: Load already in progress!\n\000\000\000\000\000\000snd_BankLoadFromIOP_CB: CD BUSY!\n";
extern const char D_002497D8[96] = "snd_SendIOPCommandNoWait: BUFFER %d FULL(%d)! Sound stalled waiting for IOP comands to finish!\n";
extern const char D_00249838[56] = "snd_SendIOPCommandNoWait: continueing (%d).\n";

// D_0025C360 and D_0025C378 are arrays of buffer pointers, one per IOP command buffer.
extern s32 D_0025C540[1024];
extern s32 D_0025D540[1024];
extern s32 D_0025E540[1024];
extern s32 D_0025F540[1024];
extern s32 D_00260540[272];
extern s32 D_00260980[272];

struct Flag_25C388 { s32 busy; s32 pad; };
struct Pend_11CE30 { s32 fn; s32 pad; u64 arg; };
struct Cb_25C3A0 { s32 fn; s32 pad; };
struct Reply_25C3C0 { s32 head; s32 result; s32 pad[14]; };
struct Rpc_260E00 { s32 result; s32 pad[15]; };
struct Packet_0011CBB8 { s32 f00; u8 pad[0xC]; s32 f10; u8 pad2[0x2C]; };

s32* D_0025C340 = 0;
s32 D_0025C344 = 0;
s32 D_0025C348 = 0;
s32 D_0025C34C = 0;
s32 D_0025C350 = 0;
s32 D_0025C354 = 0;
s32 D_0025C358 = 0;
s32 D_0025C35C = 0;
s32* D_0025C360[2] = { D_0025C540, D_0025D540 };
s32 D_0025C368[2] = { 0xFFC, 0xFFC };
s32* D_0025C370[2] = { D_0025E540, D_0025F540 };
s32* D_0025C378[2] = { D_00260540, D_00260980 };
s32 D_0025C380 = 0;
s32 D_0025C384 = 0;
Flag_25C388 D_0025C388 = { 0, 0 };
Pend_11CE30 D_0025C390 = { 0, 0, 0 };
Cb_25C3A0 D_0025C3A0 = { 0, 0 };
u64 D_0025C3A8[3] = { 0, 0, 0 };
Reply_25C3C0 D_0025C3C0 = { 0 };
u8 D_0025C400[320] = { 0 };
s32 D_0025C540[1024] = { 0 };
s32 D_0025D540[1024] = { 0 };
s32 D_0025E540[1024] = { 0 };
s32 D_0025F540[1024] = { 0 };
s32 D_00260540[272] = { 0 };
s32 D_00260980[272] = { 0 };
volatile Packet_0011CBB8 D_00260DC0 = { 0 };
Rpc_260E00 D_00260E00 = { 0 };
s32 D_00260E40[8] = { 0 };

extern u8 D_0027B4C8[];
extern u8 D_0027B4F0[];
s32 func_001E1F10(const char* fmt, ...);

struct Rpc_0011CBB8 { u8 pad[0x24]; s32 f24; };
void func_001F7BE8(s32 mode);
s32 func_001F80C0(Rpc_0011CBB8* rpc, u32 id, s32 mode);
s32 func_0011D968(s32 id, s32 size, void* data);

#define ASSERT_0011CBB8(cond, line) \
    if (!(cond)) { \
        func_001E1F10(D_00249428, D_00249450, line); \
        for (;;) { \
        } \
    }

void func_0011CBB8(void)
{
    s32 n;

    D_0025C360[0] = (s32*)D_0025C540;
    D_0025C360[1] = (s32*)D_0025D540;
    D_0025C378[0] = D_00260540;
    D_0025C378[1] = D_00260980;
    D_0025C370[0] = D_0025E540;
    D_0025C370[1] = D_0025F540;
    func_001F7BE8(0);
    do {
        ASSERT_0011CBB8(func_001F80C0((Rpc_0011CBB8*)D_0027B4C8, 0x123456, 0) >= 0, 0x6E);
        for (n = 10000; --n != -1;) {
        }
    } while (((Rpc_0011CBB8*)D_0027B4C8)->f24 == 0);
    D_0025C388.busy = 0;
    D_0025C390.fn = 0;
    D_0025C390.arg = 0;
    g_iopChannel2Result.result = 0;
    do {
        ASSERT_0011CBB8(func_001F80C0((Rpc_0011CBB8*)D_0027B4F0, 0x123457, 0) >= 0, 0x83);
        for (n = 10000; --n != -1;) {
        }
    } while (((Rpc_0011CBB8*)D_0027B4F0)->f24 == 0);
    g_iopSharedPacket.f00 = 0;
    D_0025C540[0] = 0;
    D_0025D540[0] = 0;
    D_0025C368[0] = 0xFFC;
    D_0025C368[1] = 0xFFC;
    g_iopSharedPacket.f10 = 0;
    n = (s32)&g_iopSharedPacket;
    SendIopCommandAndWait(0, 4, &n);
}

struct Entry_11CE30 { s32 fn; s32 pad; u64 arg; };
typedef s32 (*Cb_11CE30)(s32 ctx, u64 arg);
typedef void (*Cb1_11CE30)(s32 a0);
s32 func_0011D078(void);
void func_0011DE18(void);
s32 func_0011E1F8(s32 flag);
void func_001F6C20(s32 a0);

s32 func_0011CE30(void)
{
    s32 i;
    s32 idx;
    s32 k;
    Cb_11CE30 f;
    if (g_iopReplyBuffer != 0 && IsIopReplyReady() != 0) {
        if (D_0025C35C != 0) {
            if (D_0025C3A0.fn != 0)
                ((Cb_11CE30)D_0025C3A0.fn)(D_0025C3C0.result, D_0025C3A8[0]);
            D_0025C3A0.fn = 0;
            D_0025C35C = 0;
        } else {
            idx = g_iopBufferIndex != 1;
            i = 0;
            if (D_0025C360[idx][0] > 0) {
                do {
                    Entry_11CE30* e = (Entry_11CE30*)(i * 16 + (s32)D_0025C370[idx]);
                    if (e->fn != 0)
                        ((Cb_11CE30)e->fn)(D_0025C378[idx][i + 1], e->arg);
                    i++;
                } while (i < D_0025C360[idx][0]);
            }
        }
    }
    if (D_0025C388.busy != 0) {
        func_001F6C20(0);
        k = g_iopChannel2Result.result;
        if ((u32)k != 0xFFFFFFFFu) {
            if (D_0025C390.fn != 0) {
                u64 a = D_0025C390.arg;
                Cb_11CE30 g = (Cb_11CE30)D_0025C390.fn;
                D_0025C390.fn = 0;
                D_0025C390.arg = 0;
                g(k, a);
            }
            g_iopChannel2Result.result = 0;
            D_0025C388.busy = 0;
        }
    }
    if (g_iopReplyBuffer == 0) {
        s32* p = D_0025C360[g_iopBufferIndex];
        if (p[0] != 0 && D_0025C384 == 0)
            FlushIopCommandBuffer();
    }
    if (D_0025C354 != 0) {
        SyncDiscRead(1);
        if (D_0025C358 != 0) {
            D_0025C354 = 0;
            f = (Cb_11CE30)D_0025C350;
            D_0025C358 = 0;
            if (f != 0)
                ((Cb1_11CE30)f)(1);
        }
    }
    if (g_iopReplyBuffer != 0 || D_0025C388.busy != 0)
        return 1;
    return 0;
}

LINKER_REMNANT(func_0011D060);

extern u8 D_0027B4C8[];
struct Arg_0011D078;
void func_001F6C20(Arg_0011D078* a);
s32 func_001F8480(Arg_0011D078* a);
s32 func_001E1F10(Arg_0011D078* a);

s32 func_0011D078(void)
{
    u32* table;

    func_001F6C20(0);
    if (g_iopReplyBuffer == 0) {
        return 1;
    }
    if (func_001F8480((Arg_0011D078*)D_0027B4C8) != 0) {
        return 0;
    }
    table = (u32*)g_iopReplyBuffer;
    if (table[0] == 0xFFFFFFFF) {
        if (table[D_0025C344 + 1] == table[0]) {
            g_iopReplyBuffer = 0;
            return 1;
        }
    }
    PrintFormatted((Arg_0011D078*)D_00249460);
    return 0;
}

void func_0011D110(s32* ptr, s32 count)
{
    D_0025C344 = count;
    g_iopReplyBuffer = ptr;
    ptr[count + 1] = 0;
    ptr[0] = 0;
}

LINKER_REMNANT(func_0011D138);

struct Ptr_11D140 { s32 field0; };
extern u8 D_0027B4F0[];
s32 func_001E1F10(struct Ptr_11D140 *fmt, ...);
s32 func_0011CE30(void);
s32 func_001F8480(struct Ptr_11D140 *p);
s32 func_001F8290(struct Ptr_11D140 *a, s32 b, s32 c, s32 *d, s32 e, s32 *f, s32 g, s32 h, s32 i);

s32 func_0011D140(s32 a0, s32 a1)
{
    s32 v;
    s32 w;
    s32 v1;
    u32 m;

    D_0025C348 = 0;
    if (D_0025C388.busy != 0) {
        PrintFormatted((struct Ptr_11D140 *)D_00249570);
        return 0;
    }
    v = SyncDiscRead(1);
    if (v == 1) {
        PrintFormatted((struct Ptr_11D140 *)D_002495A0);
        return 0;
    }
    s32* p = &g_iopChannel2Result.result;
    m = 0xFFFFFFFFu;
    *p = (s32)m;
    g_iopChannel2Args[1] = a1;
    g_iopChannel2Args[0] = a0;
    while (func_001F8480((struct Ptr_11D140 *)D_0027B4F0)) {
        PrintFormatted((struct Ptr_11D140 *)D_002494E8);
        PollIopCommands();
        func_001F6C20(0);
    }
    w = func_001F8290((struct Ptr_11D140 *)D_0027B4F0, 3, 1, g_iopChannel2Args, 8, &g_iopChannel2Result.result, 4, 0, 0);
    v1 = g_iopChannel2Result.result;
    if (w < 0) {
        PrintFormatted((struct Ptr_11D140 *)D_002495C0);
        D_0025C348 = 0x106;
        return 0;
    }
    if ((u32)v1 == 0xFFFFFFFFu) {
        do {
            func_001F6C20(0);
        } while ((u32)g_iopChannel2Result.result == 0xFFFFFFFFu);
    }
    return g_iopChannel2Result.result;
}

struct Ctx_0011D2A8;
struct Pair_11D2A8 { s32 a; s32 b; };
struct Args_11D2A8 { s32 a; s32 pad; s64 c; };
s32 func_001E1F10(Ctx_0011D2A8* p);
s32 func_001F8480(Ctx_0011D2A8* p);
void func_001F6C20(s32 a);
s32 func_001F8290(Ctx_0011D2A8* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5, s32 a6, s32 a7, s32 a8);

void func_0011D2A8(void* a0, s32 a1, s32 a2, s64 a3)
{
    D_0025C348 = 0;
    if (D_0025C388.busy != 0) {
        PrintFormatted((Ctx_0011D2A8*)D_00249570);
        return;
    }
    if (SyncDiscRead(1) == 1) {
        PrintFormatted((Ctx_0011D2A8*)D_002495A0);
        return;
    }
    (*(u32*)&g_iopChannel2Result.result) = 0xFFFFFFFF;
    (*(Pair_11D2A8*)&g_iopChannel2Args).a = (s32)a0;
    (*(Pair_11D2A8*)&g_iopChannel2Args).b = a1;
    (*(Args_11D2A8*)&D_0025C390).a = a2;
    (*(Args_11D2A8*)&D_0025C390).c = a3;
    while (func_001F8480((Ctx_0011D2A8*)D_0027B4F0)) {
        PrintFormatted((Ctx_0011D2A8*)D_002494E8);
        PollIopCommands();
        func_001F6C20(0);
    }
    D_0025C388.busy = 1;
    func_001F8290((Ctx_0011D2A8*)D_0027B4F0, 3, 1, ((Pair_11D2A8*)&g_iopChannel2Args), 8, ((u32*)&g_iopChannel2Result.result), 4, 0, 0);
}

LINKER_REMNANT(func_0011D3E8);

s32 func_0011DB00(s32 id, s32 a1, void* a2, s32 a3, s32 a4);

void func_0011D420(void)
{
    QueueIopCommand(0x8, 0, 0, 0, 0);
}


void func_0011D450(s32 arg)
{
    s32 local = arg;
    QueueIopCommand(6, 4, &local, 0, 0);
}

void func_0011D480(s32 a0, s32 a1)
{
    s32 buf[2];
    buf[0] = a0;
    buf[1] = a1;
    QueueIopCommand(0x9, 0x8, buf, 0, 0);
}

void func_0011D4B8(s32 arg)
{
    s32 local = arg;
    SendIopCommandAndWait(10, 4, &local);
}


s32 func_0011D4E0(s32 arg)
{
    s32 local = arg;
    return QueueIopCommand(11, 4, &local, 0, 0);
}

LINKER_REMNANT(func_0011D510);

void func_0011DB00(s32 a, s32 b, void* args, void* c, void* d);

void func_0011D520(s32 x, s32 y)
{
    s32 args[2];
    args[0] = x;
    args[1] = y;
    QueueIopCommand(0xD, 8, args, 0, 0);
}

struct Args_11D558
{
    void* a0;
    s32 a1;
    s32 a2;
};

void func_0011D558(void* a0, s32 a1, s32 a2)
{
    Args_11D558 args;
    args.a0 = a0;
    args.a1 = a1;
    args.a2 = a2;
    QueueIopCommand(0x4E, 0xC, &args, 0, 0);
}

s32 func_0011D968(s32 a, s32 b, void* args);

void func_0011D598(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5)
{
    s32 args[6];
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    args[3] = a3;
    args[4] = a4;
    args[5] = a5;
    SendIopCommandAndWait(0x11, 0x18, args);
}

LINKER_REMNANT(func_0011D5D8);

void func_0011D600(s32 value)
{
    s32 buf = value;
    QueueIopCommand(0x15, 4, &buf, 0, 0);
}

LINKER_REMNANT(func_0011D630);

void func_0011D640(s32 value)
{
    s32 local = value;
    QueueIopCommand(0x13, 4, &local, 0, 0);
}

struct Args_11D670
{
    void* a0;
};

void func_0011D670(void* a0)
{
    Args_11D670 args;
    args.a0 = a0;
    QueueIopCommand(0x14, 4, &args, 0, 0);
}

LINKER_REMNANT(func_0011D6A0);

void func_0011D6A8(s32 a0)
{
    s32 buf = a0;
    QueueIopCommand(0x16, 4, &buf, 0, 0);
}

void func_0011D6D8(s32 a0)
{
    s32 buf = a0;
    QueueIopCommand(0x17, 4, &buf, 0, 0);
}

void func_0011D708(s32 a0)
{
    s32 buf = a0;
    SendIopCommandAndWait(0x19, 4, &buf);
}

void func_0011D730(s32 value, s32 a1, s32 a2)
{
    s32 local = value;
    QueueIopCommand(0x19, 4, &local, a1, a2);
}

void func_0011D760(s32 a0, s32 a1)
{
    s32 local[2];
    local[0] = a0;
    local[1] = a1;
    SendIopCommandAndWait(0x1A, 8, local);
}

LINKER_REMNANT(func_0011D790);

struct Args_11D798
{
    void* a0;
    s32 a1;
    s32 a2;
};

void func_0011D798(void* a0, s32 a1, s32 a2)
{
    Args_11D798 args;
    args.a0 = a0;
    args.a1 = a1;
    args.a2 = a2;
    QueueIopCommand(0x1B, 0xC, &args, 0, 0);
}

s32 func_0011D968(s32 kind, s32 count, void* words);
struct Words_11D7D8 { s32 a; s32 b; };

s32 func_0011D7D8(s32 a, s32 b)
{
    Words_11D7D8 w;
    w.a = a;
    w.b = b;
    return SendIopCommandAndWait(0x1C, 8, &w);
}

LINKER_REMNANT(func_0011D808);

void func_0011D810(s32 x, s32 y)
{
    s32 args[2];
    args[0] = x;
    args[1] = y;
    QueueIopCommand(0x1E, 8, args, 0, 0);
}

LINKER_REMNANT(func_0011D848);

void func_0011D860(s32 a0, s32 a1, s32 a2, s32 a3)
{
    s32 local[4];
    local[0] = a0;
    local[1] = a1;
    local[2] = a2;
    local[3] = a3;
    QueueIopCommand(0x22, 16, local, 0, 0);
}

LINKER_REMNANT(func_0011D8A0);

struct Args_11D8B0
{
    void* a0;
    s32 a1;
    s32 a2;
};

void func_0011D8B0(void* a0, s32 a1, s32 a2)
{
    Args_11D8B0 args;
    args.a0 = a0;
    args.a1 = a1;
    args.a2 = a2;
    QueueIopCommand(0x29, 0xC, &args, 0, 0);
}

struct Words_11D8F0 { s32 a; s32 b; };

void func_0011D8F0(s32 a, s32 b)
{
    Words_11D8F0 w;
    w.a = a;
    w.b = b;
    SendIopCommandAndWait(0x28, 8, &w);
}

LINKER_REMNANT(func_0011D920);

struct Word_11D928 { s32 a; };

void func_0011D928(s32 a)
{
    Word_11D928 w;
    w.a = a;
    QueueIopCommand(0x27, 4, &w, 0, 0);
}

LINKER_REMNANT(func_0011D958);

void func_0011D110(void* p, s32 n);
s32 func_001F8480(void* p);
s32 func_001E1F10(void* self, ...);
s32 func_001F8290(void* a, s32 b, s32 c, void* d, s32 e, void* f, s32 g, s32 h, s32 i);

s32 func_0011D968(s32 id, s32 size, void* data)
{
    s32 i;
    s32 r;
    for (i = 0; i < size; i++)
        g_iopCommandArgs[i] = ((u8*)data)[i];
    while ((s32)g_iopReplyBuffer) {
        PollIopCommands();
        func_001F6C20(0);
    }
    ArmIopReplyBuffer(&D_0025C3C0, 1);
    while (func_001F8480(D_0027B4C8)) {
        PrintFormatted((void*)D_002494E8);
        PollIopCommands();
        func_001F6C20(0);
    }
    if (size)
        func_001F8290(D_0027B4C8, id, 1, g_iopCommandArgs, size, &D_0025C3C0, 0xC, 0, 0);
    else
        func_001F8290(D_0027B4C8, id, 1, 0, 0, &D_0025C3C0, 0xC, 0, 0);
    while (!IsIopReplyReady()) {
    }
    r = D_0025C3C0.result;
    if (*D_0025C360[g_iopBufferIndex] != 0 && D_0025C384 == 0)
        FlushIopCommandBuffer();
    return r;
}

void func_0011D110(void* ptr, s32 count);
s32 func_001E1F10(const char* fmt, ...);
s32 func_001F8290(void* a, s32 b, s32 c, s32 d, s32 e, void* f, s32 g, s32 h, s32 i);
void func_0011DDD8(void);

void func_0011DB00(s32 cmd, s32 len, u8* data, s32 arg, u64 val)
{
    s32 flag = 0;
    s32 i;

    if (D_0025C384 == 0 && g_iopReplyBuffer == 0 && len == 0 && arg == 0) {
        ArmIopReplyBuffer((&D_0025C3C0), 1);
        while (func_001F8480(D_0027B4C8) != 0) {
            PrintFormatted((void*)D_002494E8);
            PollIopCommands();
            func_001F6C20(0);
        }
        func_001F8290(D_0027B4C8, cmd, 1, 0, 0, (&D_0025C3C0), 12, 0, 0);
        return;
    }

    s32 size = len + 4;
    i = 0;
    if ((size & 3) != 0)
    {
        s32 t = len + 8;
        size = t - size % 4;
    }

    for (;; i++) {
        if (*D_0025C360[g_iopBufferIndex] != 0x100 && D_0025C368[g_iopBufferIndex] >= size)
            break;
        if (D_0025C384 != 0) {
            D_0025C384 = 0;
            flag = 1;
        }
        PollIopCommands();
        if (i == 1)
            PrintFormatted((void*)D_002497D8, g_iopBufferIndex, *D_0025C360[g_iopBufferIndex]);
    }
    if (i != 0)
        PrintFormatted((void*)D_00249838, i);
    if (flag != 0)
        D_0025C384 = 1;

    {
        s16* p = (s16*)(((u8*)D_0025C360[g_iopBufferIndex]) - (D_0025C368[g_iopBufferIndex] - 0x1000));
        s32 j;
        *p = cmd;
        p++;
        *p = len;
        p++;
        for (j = 0; j < len; j++)
            ((u8*)p)[j] = data[j];
    }
    {
        s32 k = g_iopBufferIndex;
        D_0025C368[k] -= size;
        *(s32*)(((u8**)D_0025C370)[k] + *D_0025C360[k] * 16) = arg;
        *(u64*)(((u8**)D_0025C370)[k] + *D_0025C360[k] * 16 + 8) = val;
    }
    CommitQueuedIopCommand();
}

void func_0011DDD8()
{
    s32* p = D_0025C360[g_iopBufferIndex];
    p[0]++;
    PollIopCommands();
}

struct Sync_11DE18;
struct Cfg_11DE18;
void func_0011D110(s32* ptr, s32 count);
s32 func_001F8480(Sync_11DE18* p);
s32 func_001E1F10(Cfg_11DE18* p);
s32 func_001F8290(Sync_11DE18* a0, s32 a1, s32 a2, s32* a3, s32 a4, s32* a5, s32 a6, s32 a7, s32 a8);

void func_0011DE18(void)
{
    ArmIopReplyBuffer(D_0025C378[g_iopBufferIndex], *D_0025C360[g_iopBufferIndex]);
    while (func_001F8480((Sync_11DE18*)D_0027B4C8)) {
        PrintFormatted((Cfg_11DE18*)D_002494E8);
        func_001F6C20(0);
    }
    (void)func_001F8290((Sync_11DE18*)D_0027B4C8, 0x4D, 1, D_0025C360[g_iopBufferIndex],
                  0x1000 - D_0025C368[g_iopBufferIndex], D_0025C378[g_iopBufferIndex],
                  *D_0025C360[g_iopBufferIndex] * 4 + 8, 0, 0);
    s32 n = (g_iopBufferIndex ^ 1) != 0;
    g_iopBufferIndex = n;
    *D_0025C360[n] = 0;
    D_0025C368[n] = 0xFFC;
}

s32 func_0011DF58(s32 a, s32 b, s32 c, s32 d)
{
    s32 buf[4];
    s32 r;
    if (g_iopDiscAccess == 1)
        return 0;
    if (D_0025C388.busy) {
        do {
        } while (PollIopCommands());
    }
    SyncDiscRead(0);
    buf[0] = a;
    buf[1] = b;
    buf[2] = c;
    buf[3] = d;
    r = SendIopCommandAndWait(0x2A, 0x10, buf);
    g_iopDiscAccess = r;
    return r;
}

void func_0011E010()
{
    QueueIopCommand(0x34, 0, 0, 0, 0);
}

LINKER_REMNANT(func_0011E040);

struct Pack7_11E048 { void* w0; s32 w1; s32 w2; s32 w3; s32 w4; s32 w5; s32 w6; };

s32 func_0011E048(void* a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8)
{
    Pack7_11E048 buf;
    buf.w0 = a0;
    buf.w1 = a1;
    buf.w2 = (a4 << 16) | (a2 & 0xFFFF);
    buf.w3 = (a5 << 16) | (a3 & 0xFFFF);
    buf.w4 = a6;
    buf.w5 = a7;
    buf.w6 = a8;
    return SendIopCommandAndWait(0x2C, 0x1C, &buf);
}

LINKER_REMNANT(func_0011E0A8);

void func_0011E0B0(s32 a0)
{
    s32 buf = a0;
    QueueIopCommand(0x2E, 4, &buf, 0, 0);
}

void func_0011E0E0(s32 a0, s32 a1, s32 a2)
{
    s32 buf = a0;
    QueueIopCommand(0x4F, 4, &buf, a1, a2);
}

void func_0011E110(s32 a0)
{
    s32 buf = a0;
    SendIopCommandAndWait(0x36, 4, &buf);
}

// The RPC completion flag: func_0011E1F8 waits for another thread to clear it.
struct Sync_11E138 {
    s32 busy;
    s32 pad[3];
    s32 result;
};

s32 func_00203B18(s32 a0, s32 a1, s32 a2, u8* a3);

s32 func_0011E138(s32 a0, s32 a1, s32 a2, u8* a3)
{
    void QueueIopCommand(s32 id, s32 size, s32* args, s32 a3, s32 a4);  // the argument words
    if (g_iopDiscAccess == 0) {
        return func_00203B18(a0, a1, a2, a3);
    }
    if (SyncDiscRead(1) == 1) {
        return 0;
    }
    s32 args[3];
    args[0] = a0;
    (*(volatile Sync_11E138*)&g_iopSharedPacket).busy = 1;
    (*(volatile Sync_11E138*)&g_iopSharedPacket).result = 0;
    args[1] = a1;
    args[2] = a2;
    QueueIopCommand(0x38, 0xC, args, 0, 0);
    D_0025C354 = 1;
    D_0025C358 = 0;
    return 1;
}

s32 func_002032C8(s32 value);
void func_001F6C20(s32 value);

s32 func_0011E1F8(s32 flag)
{
    if (g_iopDiscAccess == 0) {
        return func_002032C8(flag);
    }
    func_001F6C20(0);
    u32 ready = (*(volatile u32*)&g_iopSharedPacket) < 1;
    (*(u32*)&D_0025C358) = ready;
    if (ready == 1) {
        return 0;
    }
    if (flag == 1) {
        return 1;
    }
    while ((*(u32*)&D_0025C358) == 0) {
        PollIopCommands();
        func_001F6C20(0);
        (*(u32*)&D_0025C358) = (*(volatile u32*)&g_iopSharedPacket) < 1;
    }
    return 0;
}

s32 func_00203E28(void);

s32 func_0011E2A0()
{
    if (g_iopDiscAccess == 0)
        return func_00203E28();
    QueueIopCommand(0x37, 0, 0, 0, 0);
    return 1;
}

// D_00260DC0 is the RPC packet shared with the IOP, declared volatile above; the volatile
// access keeps lui+addiu+lw 16(base).
s32 func_00203D90();

s32 func_0011E2E8()
{
    if (g_iopDiscAccess == 0)
        return func_00203D90();
    return g_iopSharedPacket.f10;
}

void func_0011E328(s32 a0, s32 a1)
{
    s32 local[2];
    local[0] = a0;
    local[1] = a1;
    QueueIopCommand(0xE, 8, local, 0, 0);
}

void func_0011E360(s32 a0, s32 a1, s32 a2)
{
    s32 local[3];
    local[0] = a0;
    local[1] = a1;
    local[2] = a2;
    QueueIopCommand(0xF, 12, local, 0, 0);
}

void func_0011E3A0(s32 a0, s32 a1)
{
    s32 local[2];
    local[0] = a0;
    local[1] = a1;
    QueueIopCommand(0x51, 8, local, 0, 0);
}

LINKER_REMNANT(func_0011E3D8);

s32 func_0011D968(s32 id, s32 flags, void* args);

void func_0011E428(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4)
{
    s32 args[5];
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    args[3] = a3;
    args[4] = a4;
    SendIopCommandAndWait(0x3B, 0x14, args);
}

void func_0011E460(void)
{
    SendIopCommandAndWait(0x3D, 0, 0);
}

LINKER_REMNANT(func_0011E488);

void func_0011E498(void)
{
    SendIopCommandAndWait(0x3C, 0, 0);
}

void func_0011E4C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4)
{
    s32 args[5];
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    args[3] = a3;
    args[4] = a4;
    SendIopCommandAndWait(0x3E, 0x14, args);
}

s32 func_0011D968(s32 kind, s32 a1, s32 a2);

void func_0011E4F8()
{
    SendIopCommandAndWait(0x40, 0, 0);
}

LINKER_REMNANT(func_0011E520);

s32 func_0011E538(s32 a0)
{
    return (a0 * 0x5F4) / 0x2E5;
}
