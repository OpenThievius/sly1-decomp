// SPDX-License-Identifier: AGPL-3.0-or-later
// The render frames, 0x15E6A8 to 0x15F678 (its .data from 0x262280; no .rodata or .bss of its
// own): the two render frames and their lists, building, closing and submitting a frame's GS
// and VIF buffers, the code checksum, the render thread and the blit to the display, ending with
// the static initialiser that sets up the GS and VIF packet writers, D_00262280 and D_002622A8,
// this file's first .data. Its end is exact (the constructor list names func_0015F658); its start
// is not proved by retail, only by the change of role from the fonts and text (font.cpp): the
// font's .data ends before D_00262280 and its functions read this file's packet writers only as
// globals, so the cut could lie from 0x15E5F0 to 0x15E6A8. The name is ours, after its role.
#include "common.h"
#include "effect_spawner.h"
#include "vu0.h"
#include "asm_func.h"
#include "system.h"
#include "effect_owner.h"
#include "effect.h"
#include "shapes.h"
#include "active_set_solver.h"
#include "list_iter.h"
#include "transform_object.h"
#include "object_group.h"
#include "cursor_animator.h"
#include "object_cycler.h"
#include "scaling_volume.h"
#include "world.h"
#include "deferred_request.h"
#include "color_fade.h"
#include "base_object.h"
#include "packet_writer.h"
#include "camera.h"
#include "font.h"
#include "render_frame.h"
#include "text_reader.h"
#include "layout_137228.h"
#include "scope_marker.h"
#include "vu0.h"

// The world and the camera (globals.h, which this file does not include: it defines the packet
// writers that header declares as PacketWriter, at their own sizes, below).
extern World* g_currentWorld;
extern Camera* g_camera;

// The two packet writers this file defines, as retail lays them out: labels of 0x28 and 0x24
// bytes. The GS writer is a GIF writer: InitGifPacket sets its fields through the entry count at
// 0x24 (CountGifEntry, CloseGifTag). The VIF writer ends with the count at 0x20 (InitPacketWriter
// sets it, SubmitDeferredRequests sets it to 1). The other files and the functions take both as
// PacketWriter (packet_writer.h), which has the stack frames' 0x30 bytes (UploadFontImages,
// FadeScreenToBlack, the masked-image packets); these are its first 0x28 and 0x24 bytes.
struct GsWriterState {
    u8* end;                    // 0x00
    u8* begin;                  // 0x04
    s32* packetHeader;          // 0x08
    u8* cur;                    // 0x0C
    s32 padsOnClose;            // 0x10
    s32 callsCloseHook;         // 0x14
    const PacketWriterVt* vt;   // 0x18
    u32* openHeader;            // 0x1C
    u32 elementCount;           // 0x20
    u32 entryCount;             // 0x24: the GIF entry count
};

struct VifWriterState {
    u8* end;                    // 0x00
    u8* begin;                  // 0x04
    s32* packetHeader;          // 0x08
    u8* cur;                    // 0x0C
    s32 padsOnClose;            // 0x10
    s32 callsCloseHook;         // 0x14
    const PacketWriterVt* vt;   // 0x18
    u32* openHeader;            // 0x1C
    u32 elementCount;           // 0x20
};

typedef char check_GsWriterState[sizeof(GsWriterState) == 0x28 ? 1 : -1];
typedef char check_VifWriterState[sizeof(VifWriterState) == 0x24 ? 1 : -1];

extern GsWriterState g_gsPacketWriter;
extern VifWriterState g_vifPacketWriter;

void SetListLinkOffset(List01* self, s32 offset);
s32 IsListEmpty(List01* p);
void AppendToList(List01* self, void* item);

// A message held back by SendMessageAfterDelay (a slot of the world's pool at +0x1BD0, in its
// list at +0x1BDC, linked at +0x64): the receiver, the 0x50-byte message, the time it is due.
struct DelayedMessageBody { Quad16 q[5]; };
struct DelayedMessage { void* owner; u8 pad0[0xC]; DelayedMessageBody body; f32 due; };
void AppendToList(List01* self, void* item);
void AppendToList(List01* self, void* item);



void RemoveFromList(List01* list, void* item);
void PushFreeSlot(Pool6C* list, void* item);
void PushFreeSlot(Pool6C* list, void* item);
void BeginDmaTag(PacketWriter* self);
void CloseDmaTag(PacketWriter* self);


void AppendToList(List01* self, void* item);
void RemoveFromList(List01* list, void* item);
void RemoveFromList(List01* list, void* item);
void RemoveFromList(List01* list, void* item);
void PushFreeSlot(Pool6C* list, void* item);


// A walk of a list that RemoveFromList keeps valid: the frame is pushed on g_activeListFrames
// (list_iter.h) and each step reads the next item through the link.
struct BeginListWalk {
    static void Of(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = it;
    }
};

template <class T> struct NextInList {
    static T* Of(ListFrame* it)
    {
        T* obj = *(T**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};
void RemoveFromList(List01* list, void* item);

// The packet memory a GIF writer fills: quadwords.
typedef u64 UQuadword128 __attribute__((mode(TI)));

extern u8 D_00212160[];
extern u8 D_00215C50[];

PacketWriter* InitGifPacket(PacketWriter* self);
void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);
void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);
void EndGifPacket(PacketWriter* self);
void WriteVifFlush(PacketWriter* b);
void WriteVifDirectFromWriter(PacketWriter* a0, PacketWriter* a1);
void AddDmaRefTagIfChanged(void* self, void* a, void* b);
void AddDmaEndTag(PacketWriter* self);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);

void CloseDmaTag(PacketWriter* self);
void AddDmaRefTag(void* obj, s32 a, s32 b);
void BeginDmaTag(PacketWriter* self);
void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);


extern s32 g_vif1Channel;
extern s32 g_gifChannel;

void SendGsPacketAndWait(s32 channel, void* b);
PacketWriter* InitGifPacket(PacketWriter* self);
void* InitPacketWriter(PacketWriter* self);
void ActivateRenderFrame(void* a, s32 b);


void ConstructPacketWriters(s32 flag, s32 code);

void AddDmaRefTag(void* list, u32 count, s32 value);
extern s32 D_0026230C;

void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);
void EndGifPacket(PacketWriter* self);
void AddDmaEndTag(PacketWriter* self);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);

void WriteGsFinishPacket(void* self, void* p, u8** n);
void CloseDrawBuffer(void* obj, void* a, u8** b);
void ClearList(List01* p);
extern "C" s32 PostSemaphore(void* a);

extern List01 D_002622E0;
extern List01 D_002622F0;
extern List01 g_deferredReleaseListC;
extern s32 g_buildFrameData;
extern void* g_frameReadySemaphore;



extern s32 g_drawFrameData;
extern s32 g_maskedImagesPacket;
extern s32 g_gifChannel;

void SwitchActiveImageMask(s32 value);
struct DmaChannel;
extern "C" void StartDmaChain(DmaChannel* ch, void* tadr);
PacketWriter* InitGifPacket(PacketWriter* self);
void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);



extern u32 D_002C3B00[];
extern u8 D_00148D74[];
extern s32 g_codeChecksumFailed;

extern void* g_frameDoneSemaphore;
extern volatile s32 g_renderThreadWaiting;
extern void* g_drawingFrame;
extern s32 D_002626CC;

extern "C" s32 AwaitSemaphore(void* a);
void SendRenderFrameToDma(RenderFrame* self, s32 flag);
void BlitFrameToDisplay(void);
void FlipDisplayFrame(void);
void ReleaseFrameNodes(RenderFrame* self);
void ClearScreenOwner(s32 owner);
void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);

// NEAR: CRC table loop: retail keeps inner counter k in v1 and n*4 in a1; ours swaps them (5 insns)

extern u8 D_003C3B00[], D_005C3B00[];
extern void* g_frameReadySemaphore;
extern void* g_frameDoneSemaphore;
extern s32 g_mainAndRenderThreads[];
void SetListLinkOffset(List01* self, s32 value);
void AddInterruptHandler(s32 a0, void (*fn)(void), s32 a2);
s32 EnableInterruptCause(s32 a0);
void* CreateLockSemaphore(s32 initCount, s32 maxCount);
void RunThread(s32 thread, void* arg);
void func_0015E678(void);

extern void* g_frameReadySemaphore;
extern void* g_frameDoneSemaphore;
extern u32 D_00262314;
extern s32 g_vif1Channel;
extern s32 g_gifChannel;
extern s32 D_002626CC;

void VerifyCodeChecksum(void);
extern "C" s32 AwaitSemaphore(void* p);
void ActivateRenderFrame(RenderFrame* f);
void ApplyPendingDisplayFlip(void);
void SendGsPacketAndWait(s32 channel, void* b);
void BlitFrameToDisplay(void);
extern "C" s32 WaitDmaChannel(DmaChannel* ch, s32 mode, s32 timeout);
void FlipDisplayFrame(void);


struct FrameNode {
    u8 pad0[0x14];
    u8* owner;
    u8 pad18[0x1088 - 0x18];
    void* pooledSlot;
};


s32 IsListEmpty(List01* l);
void RemoveFromList(List01* list, void* item);
void AppendToList(List01* self, void* item);
void ClearList(List01* l);
typedef signed long s64;
typedef unsigned long u64;
extern void* g_drawingFrame;
extern void* g_frameReadySemaphore;
extern volatile s32 g_renderThreadWaiting;

extern void* g_frameDoneSemaphore;
extern s32 g_nextBuildFrameIndex;
extern s32 g_buildFrameData;

void SetScreenOwner(s32 v);
extern "C" s32 AwaitSemaphore(void* a);
void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);
void BeginDmaTag(PacketWriter* self);


// A frame's colour record, as func_0015E6A8 reads it: 64-byte entries whose quadwords at +0x10
// and +0x20 hold colours as four words, a run of colour quadwords, and where the packed colours go.
struct ColorEntry_15E6A8 {
    u8 pad00[0x10];
    Quad16 c10;             // 0x10
    Quad16 c20;             // 0x20
    u8 pad30[0x40 - 0x30];
};

struct ColorOut_15E6A8 {
    u8 pad00[0x08];
    u32* out08;             // 0x08: the packed c10 of each entry
    u8 pad0C[0x14 - 0x0C];
    u32* out14;             // 0x14: the packed c20, then two words on, the packed run
};

struct ColorRecord_15E6A8 {
    ColorEntry_15E6A8* begin;   // 0x00
    ColorEntry_15E6A8* end;     // 0x04
    Quad16* run;                // 0x08: one quadword for each entry
    ColorOut_15E6A8* out;       // 0x0C
};

// A colour as four words, packed into one: each word a byte, the first lowest.
static inline u32 PackColor(Quad16 c)
{
    return c.w[0] | c.w[1] << 8 | c.w[2] << 16 | c.w[3] << 24;
}

// The interrupt handler that packs the colours of the frame's record (g_drawFrameData) and moves
// on to the next record, then lets the VIF1 go on (FBRST's STC) and ends the handler.
s32 PackFrameColors(s32 cause)
{
    ColorRecord_15E6A8* r = (ColorRecord_15E6A8*)g_drawFrameData;
    ColorEntry_15E6A8* begin = r->begin;
    ColorEntry_15E6A8* end = r->end;
    ColorOut_15E6A8* o = r->out;
    ColorEntry_15E6A8* e;
    u32* out = o->out08;
    for (e = begin; e < end; e++) {
        *out++ = PackColor(e->c10);
    }
    out = o->out14;
    for (e = begin; e < end; e++) {
        *out++ = PackColor(e->c20);
    }
    s32 n = end - begin;
    out += 2;
    Quad16* run = ((ColorRecord_15E6A8*)g_drawFrameData)->run;
    Quad16* qend = run + n;
    for (Quad16* q = run; q < qend; q++) {
        *out++ = PackColor(*q);
    }
    g_drawFrameData += 0x10;
    *(volatile u32*)0x10003C10 = 8;
    SyncAndEnableInterrupts();
    return -1;
}

void InitRenderFrames(void)
{
    for (u32 i = 0; i < 2; i++) {
        RenderFrame* r = &g_renderFrames[i];
        r->bufA = (u8*)D_002C3B00 + i * 0x80000;
        r->bufB = D_003C3B00 + i * 0x100000;
        r->frameData = D_005C3B00 + i * 0x10600;
        SetListLinkOffset(&r->releasedObjects, 0x630);
        SetListLinkOffset(&r->detachedRecords, 0x1090);
        SetListLinkOffset(&r->deferredReleases, 0xB8);
    }
    SetListLinkOffset(&D_002622E0, 0x630);
    SetListLinkOffset(&D_002622F0, 0x1090);
    SetListLinkOffset(&g_deferredReleaseListC, 0xB8);
    AddInterruptHandler(5, (void (*)(void))((u8*)func_0015E678 + 0x30), 0);
    EnableInterruptCause(5);
    g_frameReadySemaphore = CreateLockSemaphore(0, 2);
    g_frameDoneSemaphore = CreateLockSemaphore(2, 2);
    u32* tab = (u32*)D_002C3B00;
    s32 n = 0;
    do {
        u32 c = n;
        s32 off = n * 4;
        for (s32 k = 7; k >= 0; k--) {
            if (c & 1) c = (c >> 1) ^ 0xEDB88320;
            else c >>= 1;
        }
        *(u32*)((u8*)tab + off) = c;
        n++;
    } while (n < 256);
    RunThread(g_mainAndRenderThreads[1], 0);
}

void BeginRenderFrame(void)
{
    s32 idx;

    SetScreenOwner(3);
    AwaitSemaphore(g_frameDoneSemaphore);
    idx = g_nextBuildFrameIndex;
    g_nextBuildFrameIndex = idx + 1;
    g_buildFrame = &g_renderFrames[idx];
    if ((u32)(idx + 1) >= 2) {
        g_nextBuildFrameIndex = 0;
    }
    ReleaseFrameNodes(g_buildFrame);
    {
        RenderFrame* slot = g_buildFrame;
        s32 v = *(s32*)((u8*)g_camera + 0x21C);
        slot->flags = 0;
        slot->imageMask = v;
        slot->hasMaskedImages = 0;
        UsePacketBufferMemory((PacketWriter*)&g_gsPacketWriter, 0x8000, slot->bufA);
    }
    UsePacketBufferMemory((PacketWriter*)&g_vifPacketWriter, 0x10000, g_buildFrame->bufB);
    g_buildFrameData = g_buildFrame->frameDataWord;
    BeginDmaTag((PacketWriter*)&g_gsPacketWriter);
    BeginDmaTag((PacketWriter*)&g_vifPacketWriter);
}

void AddDmaRefTagIfChanged(void* list, s32 value, s32 end)
{
    if (D_0026230C != value) {
        D_0026230C = value;
        AddDmaRefTag(list, ((u32)(end - value) + 15) >> 4, value);
    }
}

void WriteGsFinishPacket(void* self, void* p, u8** n)
{
    UQuadword128 mem[8];
    PacketWriter gif;
    void* buf = &gif;
    InitGifPacket((PacketWriter*)buf);
    UsePacketBufferMemory((PacketWriter*)buf, 8, mem);
    BeginGifTag((PacketWriter*)buf, 0, 1, 0xE);
    AddGifRegisterWrite((PacketWriter*)buf, 0x61, 0);
    EndGifPacket((PacketWriter*)buf);
    WriteVifFlush((PacketWriter*)self);
    WriteVifDirectFromWriter((PacketWriter*)self, (PacketWriter*)buf);
    AddDmaRefTagIfChanged(self, D_00212160, D_00215C50);
    AddDmaEndTag((PacketWriter*)self);
    DetachPacketBuffer((PacketWriter*)self, (u32*)p, n);
}

void CloseDrawBuffer(void* obj, void* a, u8** b)
{
    BeginGifTag((PacketWriter*)obj, 0, 1, 0xE);
    AddGifRegisterWrite((PacketWriter*)obj, 0x61, 0);
    EndGifPacket((PacketWriter*)obj);
    AddDmaEndTag((PacketWriter*)obj);
    DetachPacketBuffer((PacketWriter*)obj, (u32*)a, b);
}

void SubmitRenderFrame(void)
{
    WriteGsFinishPacket((PacketWriter*)&g_vifPacketWriter, (u8*)g_buildFrame + 8, 0);
    CloseDrawBuffer((PacketWriter*)&g_gsPacketWriter, g_buildFrame, 0);
    g_buildFrame->releasedObjects = D_002622E0;
    ClearList(&D_002622E0);
    g_buildFrame->detachedRecords = D_002622F0;
    ClearList(&D_002622F0);
    g_buildFrame->deferredReleases = g_deferredReleaseListC;
    ClearList(&g_deferredReleaseListC);
    g_buildFrameData = 0;
    g_buildFrame = 0;
    PostSemaphore(g_frameReadySemaphore);
}

void ActivateRenderFrame(RenderFrame* self)
{
    g_drawFrameData = self->frameDataWord;
    SwitchActiveImageMask(self->imageMask);
    if (self->hasMaskedImages != 0 && g_maskedImagesPacket != 0) {
        *(volatile s32*)0x10003010 = 4;
        StartDmaChain((DmaChannel*)g_gifChannel, (void*)g_maskedImagesPacket);
    }
}

void VerifyCodeChecksum(void)
{
    const u8* table = (const u8*)D_002C3B00;
    s32 n = (s32)D_00148D74;
    u32 crc = 0xFFFFFFFF;
    u32* p = (u32*)0x00100000;
    if (n > 0) {
        do {
            u32 w = *p;
            n -= 4;
            p++;
            crc = *(u32*)(table + (((crc ^ w) & 0xFF) << 2)) ^ (crc >> 8);
            crc = *(u32*)(table + (((crc ^ (w >> 8)) & 0xFF) << 2)) ^ (crc >> 8);
            crc = *(u32*)(table + (((crc ^ (w >> 16)) & 0xFF) << 2)) ^ (crc >> 8);
            crc = *(u32*)(table + (((crc ^ (w >> 24)) & 0xFF) << 2)) ^ (crc >> 8);
        } while (n > 0);
    }
    if (crc != 0) {
        g_codeChecksumFailed = 1;
    }
}

void RunRenderThread(void)
{
    VerifyCodeChecksum();
    for (;;) {
        g_renderThreadWaiting = 1;
        AwaitSemaphore(g_frameReadySemaphore);
        g_renderThreadWaiting = 0;
        g_drawingFrame = &g_renderFrames[D_00262314];
        D_00262314++;
        if (D_00262314 >= 2) {
            D_00262314 = 0;
        }
        ActivateRenderFrame((RenderFrame*)g_drawingFrame);
        ApplyPendingDisplayFlip();
        SendGsPacketAndWait(g_vif1Channel, ((RenderFrame*)g_drawingFrame)->bufB);
        *(volatile s32*)0x10003010 = 0;
        SendGsPacketAndWait(g_gifChannel, ((RenderFrame*)g_drawingFrame)->bufA);
        BlitFrameToDisplay();
        WaitDmaChannel((DmaChannel*)g_vif1Channel, 0, 0);
        PostSemaphore(g_frameDoneSemaphore);
        FlipDisplayFrame();
        D_002626CC = 1;
    }
}

void SendRenderFrameToDma(RenderFrame* self, s32 flag)
{
    ActivateRenderFrame(self);
    SendGsPacketAndWait(g_vif1Channel, self->bufB);
    if (flag != 0) {
        *(volatile s32*)0x10003010 = 0;
        SendGsPacketAndWait(g_gifChannel, self->bufA);
    }
}

void ReleaseFrameNodes(RenderFrame* self)
{
    ListFrame it;
    FrameNode* n;
    if (IsListEmpty(&self->releasedObjects) == 0) {
        BeginListWalk::Of(&it, &self->releasedObjects);
        while ((n = NextInList<FrameNode>::Of(&it)) != 0) {
            RemoveFromList(&self->releasedObjects, n);
            AppendToList((List01*)(n->owner + 0x1CC0), n);
        }
        ClearList(&self->releasedObjects);
        g_activeListFrames = it.prev;
    }
    if (IsListEmpty(&self->detachedRecords) == 0) {
        BeginListWalk::Of(&it, &self->detachedRecords);
        while ((n = NextInList<FrameNode>::Of(&it)) != 0) {
            if (n->pooledSlot != 0) {
                PushFreeSlot((Pool6C*)((u8*)g_currentWorld + 0x1B4C), n->pooledSlot);
            }
            RemoveFromList(&self->detachedRecords, n);
            PushFreeSlot(&g_currentWorld->pool1B40, n);
        }
        ClearList(&self->detachedRecords);
        g_activeListFrames = it.prev;
    }
    if (IsListEmpty(&self->deferredReleases) == 0) {
        BeginListWalk::Of(&it, &self->deferredReleases);
        while ((n = NextInList<FrameNode>::Of(&it)) != 0) {
            RemoveFromList(&self->deferredReleases, n);
            PushFreeSlot(&g_currentWorld->pool1BF4, n);
        }
        g_activeListFrames = it.prev;
    }
}

void DrainRenderFrames(s32 flag)
{
    for (s32 i = 0; (u32)i < 2; i++) {
        AwaitSemaphore(g_frameDoneSemaphore);
    }
    for (s32 i = 0; (u32)i < 2; i++) {
        PostSemaphore(g_frameDoneSemaphore);
    }
    while (g_renderThreadWaiting == 0) {
    }
    if (flag != 0 && g_drawingFrame != 0) {
        s32 n = 2;
        do {
            SendRenderFrameToDma((RenderFrame*)g_drawingFrame, 1);
            BlitFrameToDisplay();
            FlipDisplayFrame();
        } while (--n >= 0);
        D_002626CC = 3;
    }
    u8* p = (u8*)g_renderFrames;
    u8* end = p + 0x90;
    do {
        ReleaseFrameNodes((RenderFrame*)p);
        p += 0x48;
    } while (p < end);
    ClearScreenOwner(3);
    g_drawingFrame = 0;
}

// The two display buffers' register records (display.cpp): FRAME at +0 and DISPFB-style
// words chosen by the frame counter's parity.
extern u8 D_002624F0[];
extern u8 D_00262500[];
extern u8 D_002625E0[];
extern u8 D_002625F0[];
extern s32 g_displayFrameCounter;
extern s32 D_002626C8;
void AddGifUvEntry(PacketWriter* p, s32 u, s32 v);
void AddGifXyzfEntry(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);

// A FRAME word's buffer base and the low bits of its pixel format, without width or mask.
static inline u64 FrameBits(const u64& f)
{
    return (f & 0x1FF) | (((f >> 24) & 0xF) << 24);
}

void BlitFrameToDisplay(void)
{
    PacketWriter w;
    Quad16 buf[100];
    InitGifPacket(&w);
    UsePacketBufferMemory(&w, 100, buf);
    BeginDmaTag(&w);
    BeginGifTag(&w, 0, 1, 0xE);
    u64 frame = *(u64*)((g_displayFrameCounter & 1) ? D_002625F0 : D_00262500);
    AddGifRegisterWrite(&w, 0x3F, (u64)0);
    AddGifRegisterWrite(&w, 0x4E, FrameBits(frame) | ((u64)1 << 32));
    u64 disp = *(u64*)((g_displayFrameCounter & 1) ? D_002624F0 : D_002625E0);
    AddGifRegisterWrite(&w, 6, ((disp & 0x1FF) << 5) | (((disp >> 16) & 0x3F) << 14) | (((disp >> 24) & 0x3F) << 20) | 0x2A8000000ULL);
    AddGifRegisterWrite(&w, 0x14, (u64)0x61);
    AddGifRegisterWrite(&w, 8, (u64)5);
    AddGifRegisterWrite(&w, 0x47, (u64)0x30002);
    AddGifRegisterWrite(&w, 0x42, 0x3000000064ULL);
    AddGifRegisterWrite(&w, 1, 0x3F80000080808080ULL);
    AddGifRegisterWrite(&w, 0x40, 0xDE0001027F0000ULL);
    BeginGifTag(&w, 0x156, 2, 0x43);
    s32 v = (D_002626C8 & 1) ? 0 : 8;
    for (s32 x = 0; x < 0x280; x += 0x20) {
        AddGifUvEntry(&w, x << 4, v);
        AddGifXyzfEntry(&w, (x + 0x6C0) << 4, 0x7900, 0, 0);
        AddGifUvEntry(&w, (x + 0x20) << 4, v + 0xE00);
        AddGifXyzfEntry(&w, (x + 0x6E0) << 4, 0x8700, 0, 0);
    }
    BeginGifTag(&w, 0, 1, 0xE);
    AddGifRegisterWrite(&w, 0x4E, FrameBits(frame));
    AddGifRegisterWrite(&w, 0x40, 0xDF0000027F0000ULL);
    BeginGifTag(&w, 0, 1, 0xE);
    AddGifRegisterWrite(&w, 0x61, (u64)0);
    EndGifPacket(&w);
    AddDmaEndTag(&w);
    CloseDmaTag(&w);
    SendGsPacketAndWait(g_gifChannel, buf);
}

void ConstructPacketWriters(s32 flag, s32 code)
{
    if (code == 0xFFFF && flag != 0) {
        InitGifPacket((PacketWriter*)&g_gsPacketWriter);
        InitPacketWriter((PacketWriter*)&g_vifPacketWriter);
    }
}

void ResetPacketWriters(void)
{
    ConstructPacketWriters(1, 0xFFFF);
}

// The file's .data, 0x262280 to 0x2623C0, in retail's order.
GsWriterState g_gsPacketWriter = {0};
VifWriterState g_vifPacketWriter = {0};
s32 g_frameCount = 1;
// size: s32 (lw/sw), 4-byte label
s32 g_buildFrameData = 0;
// size: s32 (lw/sw), 4-byte label
s32 g_drawFrameData = 0;
// size: pointer (lw/sw), 4 bytes before an 8-aligned next label
RenderFrame* g_buildFrame = 0;
// size: 12-byte record copied into Slot r20 by func_0015EC68, 4 bytes pad before 16-aligned next label
List01 D_002622E0 = {};
// size: 12-byte record copied into Slot r2C by func_0015EC68, 4 bytes pad before 16-aligned next label
List01 D_002622F0 = {};
// size: 12-byte record copied into Slot r38 by func_0015EC68
List01 g_deferredReleaseListC = {};
s32 D_0026230C = 0;
// size: s32 (sw), 4-byte label
s32 g_codeChecksumFailed = 0;
u32 D_00262314 = 0;
// size: s32 (lw/sw), 4-byte label
s32 g_nextBuildFrameIndex = 0;
void* g_drawingFrame = 0;
// size: func_0015E810 loops 2 records of stride 0x48 (end = base + 0x90)
RenderFrame g_renderFrames[2] = {};
void* g_frameReadySemaphore = 0;
// size: pointer (lw/sw), 4-byte label
void* g_frameDoneSemaphore = 0;
volatile s32 g_renderThreadWaiting = 0;
