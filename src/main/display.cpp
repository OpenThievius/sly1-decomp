// SPDX-License-Identifier: AGPL-3.0-or-later
// The display, 0x168130 to 0x168D00 (its .data from 0x262480, its .bss from 0x2BE460): the
// field and flip handling, the vertical-blank and GS interrupt handlers with their semaphores,
// the GS packets sent and waited on, the screen fill and the fade to black. Its edges are not
// proved by retail, only by the change of role: the cone agent's methods before it
// (cone_agent.cpp) and the texture upload after it (texture_upload.cpp) read no .data of this
// file, and this file's .data and .bss (the display records, the flip state, the semaphores)
// are read by its functions only, in their order; the cut before lies at 0x168130 or a function
// before it, the one after from 0x168B68 to 0x168D00. The name is ours, after its role.
#include "common.h"
#include "asm_func.h"
#include "system.h"
#include "listed_collision_part.h"
#include "pooled_object.h"
#include "path_curve_object.h"
#include "point_object.h"
#include "list_iter.h"
#include "attachment.h"
#include "globals.h"
#include "strip_mesh.h"
#include "bump_allocator.h"
#include "texture_header.h"
#include "shapes.h"
#include "vu0.h"


void SendDisplayResetPacket(void);
void SignalDisplaySync(void);
void ResetGs(s32 a0, s32 a1, s32 a2, s32 a3);
void SetFieldDrawOffset(void* p, s32 a1, s32 a2, s32 a3);
void SyncDataCache(s32 a0);
s32 SwapDoubleBuffer(void* p, s32 a1);

struct DmaChainBlock { u8 bytes[0x20]; };

extern u8 D_002BE1A0[];
void* InitPacketBuffer(DmaChainBlock* a);
void UsePacketBufferMemory(DmaChainBlock* a, s32 n, DmaChainBlock* b);
void AddDmaRefTag(DmaChainBlock* a, s32 n, void* table);
void AddDmaEndTag(DmaChainBlock* a);
void DetachPacketBuffer(DmaChainBlock* a, s32 x, s32 y);
void SendPacketToBothBuffers(DmaChainBlock* b);
extern s32 g_gifChannel;

void* InitGifPacket(PacketWriter* f);
void BeginDmaTag(PacketWriter* f);
void BeginGifTag(PacketWriter* f, s32 a, s32 b, s32 c);
void AddGifRegisterWrite(PacketWriter* f, s32 a, u64 b);
void EndGifPacket(PacketWriter* f);
void AddDmaEndTag(PacketWriter* f);
void DetachPacketBuffer(PacketWriter* f, s32 a, s32* out);
void SendGsPacketAndWait(s32 a, s32 b);

void BeginGifTag(void* p, s32 a, s32 b, s32 c);
void AddGifRegisterWrite(void* p, s32 a, u64 b);


extern u8 D_002BDC20[];
extern u8 D_002BE1A0[];
extern u8 D_002BDEE0[];

void SetUpDoubleBuffer(void* p, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void FillScreenColor(void* ctx, Rgba4* v, s32 flag);
s32 CreateLockSemaphore(void* a, void* b);
void AddInterruptHandler(s32 a0, void (*fn)(void), s32 a2);
s32 EnableInterruptCause(s32 a0);
void InitMeshQueue(void);
void ResetDisplayBuffers(void);
s32 HandleVblankStart(s32 cause);
s32 HandleGsFinish(s32 cause);

extern s32 g_gifChannel;

s32 SendDrawEnvironment(void* p);
void StartDmaChain(s32 a, void* b);
s32 WaitDmaChannel(s32 a, s32 b, s32 c);

// The file's .data, in retail's order (0x262480 to 0x2626D0): the word func_001682C0 reads,
// the display's two records (0x28 bytes each, read by func_00168130; retail puts them on 16
// after the 4-byte D_00262484) and its two pairs of packets, the frame counter and modes. Then
// its .bss (0x2BE460 to 0x2BE478), the statics the display code shares with func_001682C0 and
// func_00168698.
s32 D_00262480 = 0xF;
s32 D_00262484 = 0;
u8 D_00262490[0x50] __attribute__((aligned(16))) = { 0 };
u8 D_002624E0[16] = { 0 };
u8 D_002624F0[16] = { 0 };
u8 D_00262500[208] = { 0 };
u8 D_002625D0[16] = { 0 };
u8 D_002625E0[16] = { 0 };
u8 D_002625F0[208] = { 0 };
s32 g_displayFrameCounter = 0;
s32 D_002626C4 = 0;
s32 D_002626C8 = 0;
s32 D_002626CC = 0;

static s32 D_002BE460;
static s32 D_002BE464;
static s32 D_002BE468;
static s32 D_002BE46C;
static s32 D_002BE470;
static s32 D_002BE474;

void ApplyFieldDisplayOffset(void);
s32 WaitGsPaths(s32 a0, s32 a1);

struct FadePacket : PacketWriter { s32 value; u8 pad[0x3F0]; };

extern s32 g_gifChannel;

void UsePacketBufferMemory(PacketWriter* f, s32 n, s32* p);
void WriteColoredSpritePacket(f32 x, f32 y, f32 z, f32 w, s32 a, s32 b, s32 c, s32 d, FadePacket* e);
void DetachPacketBuffer(PacketWriter* f, s32 a, s32 b);
void SendGsPacketAndWait(s32 a, s32* b);
void FlipDisplayFrame(void);
void AddDmaRefTag(void* self, s32 lo, s32 hi);

s32 GetGsInterruptMask(void);
s32 SwapGsInterruptMask(s32 a);
void SyncDataCache(s32 a);
s32 AwaitSemaphore(s32 a);

void UsePacketBufferMemory(PacketWriter* f, s32 n, PacketWriter* p);

struct GsPmode { u32 en1 : 1; u32 rest : 31; u32 hi : 32; };
struct GsDispFb { u32 fbp : 9; u32 fbw : 6; u32 psm : 5; u32 pad0 : 12; u32 dbx : 11; u32 dby : 11; u32 pad1 : 10; };
struct GsDisplay { u32 dx : 12; u32 dy : 11; u32 magh : 4; u32 magv : 2; u32 pad0 : 3; u32 dw : 12; u32 dh : 11; u32 pad1 : 9; };
struct DisplayRegs { GsPmode pmode; u64 pad; GsDispFb dispfb; GsDisplay display; u64 pad2; };
struct GsPrivRegs {
    GsPmode pmode; u8 pad0[0x70 - 8];
    GsDispFb dispfb2; u8 pad1[8];
    GsDisplay display2; u8 pad2[0x1000 - 0x88];
    u32 csr;
};
void UsePacketBufferMemory(PacketWriter* f, s32 n, u8* buf);
void DetachPacketBuffer(PacketWriter* f, s32* o0, s32* o1);


void ApplyFieldDisplayOffset(void)
{
    s32 i = g_displayFrameCounter & 1;
    s32 field = D_002626C8;
    GsPmode pm = ((DisplayRegs*)&D_00262490)[i].pmode;

    if (field != (s32)((((GsPrivRegs*)0x12000000)->csr >> 13) & 1)) {
        GsDisplay d = ((DisplayRegs*)&D_00262490)[i].display;
        GsDispFb fb = ((DisplayRegs*)&D_00262490)[i].dispfb;
        d.dh = d.dh - 1;
        if (field != 0) {
            d.dy = d.dy + 1;
        } else {
            fb.dby = fb.dby + 1;
        }
        ((GsPrivRegs*)0x12000000)->display2 = d;
        ((GsPrivRegs*)0x12000000)->dispfb2 = fb;
        pm.en1 = 1;
    }
    ((GsPrivRegs*)0x12000000)->pmode = pm;
}

void PostSemaphoreFromInterrupt(s32 sema);
void WriteDisplayRegisters(void* self);

// The vertical blank start handler: wakes a waiter of the next blank, then by the display's
// mode puts the field offset or the next frame's display registers; then ends the handler.
s32 HandleVblankStart(s32 cause)
{
    if (D_002BE46C != 0) {
        D_002BE46C = 0;
        PostSemaphoreFromInterrupt(D_002BE460);
    }
    switch (D_002626CC) {
    case 1:
        if (D_002BE470 == 0) {
            D_00262484 = D_00262480;
            ApplyFieldDisplayOffset();
        }
        break;
    case 2:
        if (D_002BE470 == 0) {
            ApplyFieldDisplayOffset();
        }
        break;
    case 3: {
        s32 n = g_displayFrameCounter + 1;
        D_002BE474 = 1;
        g_displayFrameCounter = n;
        WriteDisplayRegisters(D_00262490 + (n & 1) * 0x28);
        break;
    }
    }
    SyncAndEnableInterrupts();
    return 0;
}

void SignalDisplaySync(void) {
    D_002BE46C = 1;
    AwaitSemaphore(D_002BE460);
}

void FlipDisplayFrame(void)
{
    D_002BE470 = 1;
    SignalDisplaySync();
    s32 a0 = D_002626C4;
    s32 a1 = D_00262484;
    D_002626C8 = a0;
    D_002BE470 = 0;
    if (a1 > 0) {
        D_002626C4 = 0;
        D_00262484 = a1 - 1;
    } else {
        u32 flag = (*(u32*)0x12001000 >> 13) & 1;
        D_002626C4 = (flag == 0);
    }
    u8* ptr;
    if (g_displayFrameCounter & 1) {
        ptr = D_002624F0;
    } else {
        ptr = D_002625E0;
    }
    s16 half = *(s16*)&D_002626C4;
    SetFieldDrawOffset(ptr, 0x800, 0x800, half);
    SyncDataCache(0);
    g_displayFrameCounter = g_displayFrameCounter + 1;
    SwapDoubleBuffer(D_00262490, g_displayFrameCounter);
    if ((u32)(D_002626CC - 1) < 2) {
        ApplyFieldDisplayOffset();
    }
    WaitGsPaths(0, 0);
}

void ApplyPendingDisplayFlip(void)
{
    if (D_002626CC == 3) {
        D_002626CC = 2;
    }
    if (D_002BE474 != 0) {
        u32 flag = (*(u32*)0x12001000 >> 13) & 1;
        s32 cnt = g_displayFrameCounter;
        D_002BE474 = 0;
        D_002626C4 = (flag == 0);
        u8* ptr;
        if (cnt & 1) {
            ptr = D_002625E0;
        } else {
            ptr = D_002624F0;
        }
        s16 half = *(s16*)&D_002626C4;
        SetFieldDrawOffset(ptr, 0x800, 0x800, half);
        SyncDataCache(0);
        u8* ptr2;
        if (g_displayFrameCounter & 1) {
            ptr2 = D_002625D0;
        } else {
            ptr2 = D_002624E0;
        }
        SendDrawEnvironment(ptr2);
    }
}

void ResetDisplayBuffers(void)
{
    D_002BE470 = 1;
    SendDisplayResetPacket();
    SignalDisplaySync();
    D_002BE470 = 0;
    ResetGs(0, 1, 2, 1);
    u32 flag = (*(u32*)0x12001000 >> 13) & 1;
    s32 cnt = g_displayFrameCounter;
    D_002626CC = 0;
    D_00262484 = 0;
    D_002626C8 = flag;
    D_002626C4 = (flag == 0);
    u8* ptr;
    if (cnt & 1) {
        ptr = D_002624F0;
    } else {
        ptr = D_002625E0;
    }
    s16 half = *(s16*)&D_002626C4;
    SetFieldDrawOffset(ptr, 0x800, 0x800, half);
    SyncDataCache(0);
    g_displayFrameCounter = g_displayFrameCounter + 1;
    SwapDoubleBuffer(D_00262490, g_displayFrameCounter);
}

void PostSemaphoreFromInterrupt(s32 sema);

// The GS FINISH interrupt handler: when SendGsPacketAndWait is waiting and the CSR shows FINISH,
// clears the wait and posts its semaphore; then ends the handler.
s32 HandleGsFinish(s32 cause)
{
    if (D_002BE468 != 0 && (*(volatile u64*)0x12001000 & 2)) {
        D_002BE468 = 0;
        PostSemaphoreFromInterrupt(D_002BE464);
    }
    SyncAndEnableInterrupts();
    return -1;
}

void SendGsPacketAndWait(s32 channel, void* b)
{
    D_002BE468 = 1;
    *(volatile u64*)0x12001000 |= 2;
    s32 r = GetGsInterruptMask();
    SwapGsInterruptMask(r & -0x201);
    SyncDataCache(0);
    StartDmaChain(channel, b);
    AwaitSemaphore(D_002BE464);
}

void FillScreenColor(PacketWriter* self, u8* color, s32 flag)
{
    PacketWriter f;
    s32 x;

    InitGifPacket(&f);
    UsePacketBufferMemory(&f, 0x2C, self);
    BeginGifTag(&f, (s8)color[3] >= 0 ? 0x46 : 6, 1, 0xE);
    AddGifRegisterWrite(&f, 1, (u64)color[0] | ((u64)color[1] << 8) | ((u64)color[2] << 16) | ((u64)color[3] << 24));
    AddGifRegisterWrite(&f, 0x47, flag != 0 ? 0x32001 : 0x32000);
    for (x = 0; x < 0x280; x += 0x20) {
        AddGifRegisterWrite(&f, 5, (u64)((0x6C0 + x) << 4) | ((u64)(0x790 << 4) << 16));
        AddGifRegisterWrite(&f, 5, (u64)((0x6E0 + x) << 4) | ((u64)(0x870 << 4) << 16));
    }
    AddGifRegisterWrite(&f, 0x47, 0x70000);
    EndGifPacket(&f);
}

void InitDisplay(void)
{
    Rgba4 k;
    Rgba4 t;

    ResetGs(0, 1, 2, 1);
    u8* s0 = D_00262490;
    SetUpDoubleBuffer(s0, 0, 0x280, 0xE0, 3, 0x30, 0);
    u8* p = s0;
    s32 end = (s32)s0 + 0x50;
    do {
        *(s32*)p &= -2;
        p[1] = 0x80;
        *(s32*)p |= 0x20;
        p += 0x28;
    } while ((s32)p < end);
    k.r = 0;
    k.g = 0;
    k.b = 0;
    k.a = 0x80;
    t = k;
    FillScreenColor(D_002BDC20, &t, 0);
    t = k;
    FillScreenColor(D_002BE1A0, &t, 0);
    t = k;
    FillScreenColor(D_002BDEE0, &t, 1);
    D_002BE460 = CreateLockSemaphore((void*)0, (void*)1);
    D_002BE464 = CreateLockSemaphore((void*)0, (void*)1);
    AddInterruptHandler(2, (void (*)(void))HandleVblankStart, 0);
    EnableInterruptCause(2);
    AddInterruptHandler(0, (void (*)(void))HandleGsFinish, 0);
    EnableInterruptCause(0);
    InitMeshQueue();
    ResetDisplayBuffers();
}

void SendPacketToBothBuffers(DmaChainBlock* b)
{
    s32 i = 0;
    SyncDataCache(0);
    do {
        void* p;
        if (((i + g_displayFrameCounter) & 1) != 0) {
            p = D_002624E0;
        } else {
            p = D_002625D0;
        }
        SendDrawEnvironment(p);
        i++;
        StartDmaChain(g_gifChannel, b);
    } while (i < 2);
    WaitDmaChannel(g_gifChannel, 0, 0);
}

void SendDisplayResetPacket(void)
{
    DmaChainBlock a;
    DmaChainBlock b;

    InitPacketBuffer(&a);
    UsePacketBufferMemory(&a, 2, &b);
    AddDmaRefTag(&a, 0x2C, D_002BE1A0);
    AddDmaEndTag(&a);
    DetachPacketBuffer(&a, 0, 0);
    SendPacketToBothBuffers(&b);
}

void FadeScreenToBlack(f32 t)
{
    FadePacket f;
    s32 i = 0;
    s32 n;

    InitGifPacket(&f);
    n = (s32)(t * 59.999996f);
    SignalDisplaySync();
    D_002626CC = 0;
    if (n > 0) {
        do {
            f32 x = ((f32)i + 1.0f) / (f32)n;
            f32 y = x * 255.0f;
            s32 v = (s32)(x * y);
            i++;
            UsePacketBufferMemory(&f, 0x40, &f.value);
            BeginDmaTag(&f);
            WriteColoredSpritePacket(0.0f, 0.0f, 640.0f, 492.80002f, 0, 0, 0, v, &f);
            BeginGifTag(&f, 0, 1, 0xE);
            AddGifRegisterWrite(&f, 0x61, 0);
            EndGifPacket(&f);
            AddDmaEndTag(&f);
            DetachPacketBuffer(&f, 0, 0);
            SendGsPacketAndWait(g_gifChannel, &f.value);
            FlipDisplayFrame();
        } while (i < n);
    }
}
