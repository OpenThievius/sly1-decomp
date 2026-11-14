// SPDX-License-Identifier: AGPL-3.0-or-later
// The texture upload, 0x168D00 to 0x169C58 (its .data from 0x2626D0): the mesh queue and its
// bump allocator, the image and palette records' GS registers and transfers, the masked image
// packets, the mesh queue's entries and the texture render target. Its edges are not proved by
// retail, only by the change of role: the display before it (display.cpp) and the target lists
// after it (target_lists.cpp). Its .data (the mesh queue's count and the allocator) lies
// between theirs in the same order as the code, and none of the three reads another's, so the
// cut before could lie from 0x168B68 to 0x168D00 and the one after from 0x169B18 to 0x169C58.
// The name is ours, after its role.
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
struct FrameTarget;
struct ImageRecord;
struct PacketWriter;
struct PaletteRecord;


void PushBackMemoryMark(void);
void PopBackMemoryMark(void);

struct DmaChainBlock { u8 bytes[0x20]; };
void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);
void AddDmaRefTag(PacketWriter* self, s32 lo, s32 hi);
void AddDmaEndTag(PacketWriter* self);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);

struct TexturePacket : PacketWriter { u8* packet; };

extern s32 g_imageSlotsB;
extern s32 g_imageSlotsA;
extern s32 g_gifChannel;

void* InitGifPacket(PacketWriter* f);
void AllocateTempPacketBuffer(PacketWriter* buffer, u32 count);
void BeginDmaTag(PacketWriter* f);
s32 PlaceMaskedImages(s32 mask, BumpAllocator* b, PacketWriter* c);
void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);
void EndGifPacket(PacketWriter* f);
void AddDmaEndTag(PacketWriter* f);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);
void SendGsPacketAndWait(s32 channel, void* b);

extern FrameTarget g_meshQueueEntries[];

void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);
void AddGifImageTag(PacketWriter* self, s32 count);

// The GS register TEX0 an image or palette record keeps (ImageRecord at 0x18, PaletteRecord
// at 0x10), as func_00168E78 and func_00168FB0 fill it: the base, width and format, the size
// as powers of two, then the palette's base, format and load mode.
struct GsTex0 {
    u64 tbp : 14;
    u64 tbw : 6;
    u64 psm : 6;
    u64 tw : 4;
    u64 th : 4;
    u64 tcc : 1;
    u64 tfx : 2;
    u64 cbp : 14;
    u64 cpsm : 4;
    u64 csm : 1;
    u64 csa : 5;
    u64 cld : 3;
};

u32 CeilLog2(u32 n);

void BeginImageTransfer(u32 dbp, u32 dbw, u32 dpsm, u64 rrw, u32 rrh, s32 x, void* ctx);


// The file's .data (0x2626D0 to 0x2626E8): the mesh queue's count and the bump allocator.
s32 g_meshQueueCount = 0;
BumpAllocator g_bumpAllocator = { 0 };

void SubmitMeshQueueEntry(FrameTarget* self);
void* AllocateZeroedFrontMemory(u32 n);
void InitMeshQueue(void);

extern s32 g_gifChannel;

void InitBumpAllocator(BumpAllocator* p, s32 value, s32 other);

struct TextureUploadPacket : PacketWriter { u8 span[0x10]; s32 out; };

extern s32 g_imageSlotsB;
extern s32 g_imageSlotsA;

void InitBumpAllocator(BumpAllocator* p, s32 value, s32 other);
s32 PlaceMaskedImages(s32 mask, BumpAllocator* b, PacketWriter* c);
void DetachPacketBufferCopy(PacketWriter* self, s32* count, u32* begin, s32* out, s32 flags);
void BuildAnimRecordGifPackets(void* self);

extern s32 g_gifChannel;

void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);
void SendGsPacketAndWait(s32 channel, void* b);

extern s32 g_imageRecordCountA;
extern s32 g_imageRecordCountB;
s32 AllocateBump(s32* self,s32 size);
void BuildPaletteTexRegister(PaletteRecord* self, u32 a1);
void StartPaletteUpload(PaletteRecord* e, s32 v, void* ctx);
void AddDmaRefTag(PacketWriter* self, s32 lo, s32 hi);
void BuildImageTexRegister(ImageRecord* self, u32 a1);
void StartImageUpload(ImageRecord* d, u32 dbp, void* ctx);


// The start of what a queue entry copies: two GIF tags whose words func_001694A0 marks (bit
// 15) when the entry has a flag.
struct QueuedGifTags {
    s32 f0;
    u8 pad0[0xC];
    s32 f10;
};

void CopyMemory(void* dst, void* src, u32 size);
void* AllocateZeroedFrontMemory(s32 bytes);

struct TransferBase { s32 v; };

void BeginImageTransfer(TransferBase dbp, u32 dbw, u32 dpsm, u64 rrw, u32 rrh, s32 x, void* ctx);

void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);

extern s32 g_imageRecordCountB;
extern s32 g_imageRecordCountA;
extern s32 g_imageSlotsB;
extern s32 g_imageSlotsA;

void InitBumpAllocator(BumpAllocator* p, s32 value, s32 other);
void* InitPacketWriter(PacketWriter* f);
void WriteVifFlush(PacketWriter* f);
void RewindPacketBuffer(PacketWriter* f);
void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);
s32 AllocateBump(s32* self,s32 size);
void StartPaletteUpload(PaletteRecord* e, s32 v, void* ctx);
void StartImageUpload(ImageRecord* d, u32 dbp, void* ctx);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);
void WriteVifDirect(PacketWriter* f, s32 a, s32 b, s32 c);
void WriteVifDirectRef(PacketWriter* f, s32 a, s32 b, s32 c);
void CloseDmaTag(PacketWriter* f);
void DetachPacketBufferCopy(PacketWriter* self, s32* count, u32* begin, s32* out, s32 flags);
void BuildAnimRecordGifPackets(s32 mask);


void InitMeshQueue()
{
    InitBumpAllocator(&g_bumpAllocator,0x1E00,0x4000);
    g_meshQueueCount=0;
}

u32 CeilLog2(u32 n) { u32 count = 0; u32 value = 1; while (value < n && count < 31) { value <<= 1; count++; } return count; }

void InitBumpAllocator(BumpAllocator* p, s32 value, s32 other) { p->next = value; p->start = value; p->limit = other; }

void ResetBumpAllocator(BumpAllocator* p) { p->next = p->start; }

s32 AllocateBump(s32* self,s32 size)
{
    s32 old=self[1];
    self[1]=old+size;
    return old;
}

void BeginImageTransfer(u32 dbp, u32 dbw, u32 dpsm, u64 rrw, u32 rrh, s32 x, void* ctx)
{
    BeginGifTag((PacketWriter*)ctx, 0, 1, 0xE);
    AddGifRegisterWrite((PacketWriter*)ctx, 0x50, ((u64)dbp << 32) | ((u64)dbw << 48) | ((u64)dpsm << 56));
    AddGifRegisterWrite((PacketWriter*)ctx, 0x51, 0);
    AddGifRegisterWrite((PacketWriter*)ctx, 0x52, rrw | ((u64)rrh << 32));
    AddGifRegisterWrite((PacketWriter*)ctx, 0x53, 0);
    AddGifImageTag((PacketWriter*)ctx, x);
}

void BuildPaletteTexRegister(PaletteRecord* self, u32 a1){
 GsTex0* bits = (GsTex0*)&self->texWordBits;
 bits->cbp = a1;
 bits->psm = (self->f4 <= 0x10) ? 0x14 : 0x13;
 bits->cpsm=0; bits->csm=0; bits->csa=0; bits->cld=1;}

void StartPaletteUpload(PaletteRecord* e, s32 v, void* ctx)
{
    s32 step = (e->f4 > 16) ? 16 : 8;
    s32 n = e->f4 - 1;
    TransferBase p;
    p.v = v;
    BeginImageTransfer(p, 1, 0, step, ((n + step) & -step) / step, e->blockCount, ctx);
}

void BuildImageTexRegister(ImageRecord* self, u32 a1)
{
    GsTex0* bits = (GsTex0*)&self->texWord;
    bits->tbp = a1;
    bits->tbw = self->f9;
    bits->psm = self->f8;
    bits->tw = CeilLog2(self->f0) & 0xF;
    bits->th = CeilLog2(self->f2) & 0xF;
    bits->tcc = 1;
}

void StartImageUpload(ImageRecord* d, u32 dbp, void* ctx)
{
    BeginImageTransfer(dbp, d->f9, d->f8, d->f0, d->f2, d->blockCount, ctx);
}

s32 PlaceMaskedImages(s32 mask, BumpAllocator* b, PacketWriter* c)
{
    s32 saved;

    if (c != 0) {
        saved = c->curS;
    } else {
        saved = 0;
    }
    for (s32 i = 0; i < g_imageRecordCountB; i++) {
        PaletteRecord* e = &g_imageRecordsB[i];
        if ((e->f0 & mask) == mask) {
            s32 v = AllocateBump((s32*)b, e->bumpSize);
            BuildPaletteTexRegister(e, v);
            if (c != 0) {
                StartPaletteUpload(e, v, c);
                AddDmaRefTag(c, e->blockCount, e->data);
            }
        }
    }
    if ((b->next & 0x7F) != 0) {
        AllocateBump((s32*)b, 0x80 - (b->next & 0x7F));
    }
    for (s32 i = 0; i < g_imageRecordCountA; i++) {
        ImageRecord* e = &g_imageRecordsA[i];
        if ((e->f4 & mask) == mask) {
            s32 v;
            if (e->f8 == 0 && (b->next & 0x1F) != 0) {
                AllocateBump((s32*)b, 0x20 - (b->next & 0x1F));
            }
            v = AllocateBump((s32*)b, e->bumpSize);
            BuildImageTexRegister(e, v);
            if (c != 0) {
                StartImageUpload(e, v, c);
                AddDmaRefTag(c, e->blockCount, e->data);
            }
        }
    }
    if (c == 0) {
        return 0;
    }
    return (c->curS ^ saved) != 0;
}

void SendMaskedImagesToGif(s32 self, BumpAllocator* arg)
{
    TexturePacket f;

    if (self == 0) {
        return;
    }
    InitGifPacket(&f);
    PushBackMemoryMark();
    AllocateTempPacketBuffer(&f, ((g_imageSlotsB * 2 + g_imageSlotsB + g_imageSlotsA) * 8) | 4);
    BeginDmaTag(&f);
    if (PlaceMaskedImages(self, arg, &f) != 0) {
        BeginGifTag(&f, 0, 1, 0xE);
        AddGifRegisterWrite(&f, 0x3F, 0);
        AddGifRegisterWrite(&f, 0x61, 0);
        EndGifPacket(&f);
        AddDmaEndTag(&f);
        DetachPacketBuffer(&f, 0, &f.packet);
        SendGsPacketAndWait(g_gifChannel, f.packet);
    }
    PopBackMemoryMark();
}

s32 BuildMaskedImagesPacket(s32 self)
{
    TextureUploadPacket f;

    InitGifPacket(&f);
    f.out = 0;
    InitBumpAllocator((BumpAllocator*)f.span, 0x1400, 0x1E00);
    PushBackMemoryMark();
    AllocateTempPacketBuffer(&f, ((g_imageSlotsB * 2 + g_imageSlotsB + g_imageSlotsA) * 8) | 4);
    BeginDmaTag(&f);
    if (PlaceMaskedImages(self, (BumpAllocator*)f.span, &f) != 0) {
        BeginGifTag(&f, 0, 1, 0xE);
        AddGifRegisterWrite(&f, 0x3F, 0);
        EndGifPacket(&f);
        AddDmaEndTag(&f);
        DetachPacketBufferCopy(&f, 0, 0, &f.out, 7);
        BuildAnimRecordGifPackets(self);
    }
    PopBackMemoryMark();
    return f.out;
}

void SubmitMeshQueueEntry(FrameTarget* self)
{
    CopyMemory(self->dst, (void*)self->value, self->count);
    s32 flag = self->flag;
    if (flag != 0) {
        QueuedGifTags* d = self->dst;
        s32 a = d->f0;
        s32 b = d->f10;
        a = a | 0x8000;
        a = a | flag;
        b = b | 0x8000;
        d->f0 = a;
        d->f10 = b;
    }
}

void QueueMeshStrip(StripMesh* a0, FrameSource* a1, s32 a2, s32 a3, s32 a4, AnimCursor* a5)
{
    FrameTarget local;
    FrameTarget* e;
    s32 link;
    s32 idx;
    s32 count;
    s32 n;
    s32 scale;
    s32 base;
    s32 off;

    link = 0;
    if (a5 != 0) {
        link = a5->flags & 1;
    }
    count = g_meshQueueCount;
    if (count >= 0x4000) {
        goto local_path;
    }
    if (a0 == 0) {
        goto pool_path;
    }
    if ((a0->flags & 0x10000000) == 0) {
        goto pool_path;
    }
    if (link != 0) {
        goto pool_path;
    }
local_path:
    link = (count < 0x4000) ? link : 0;
    e = &local;
    goto store;
pool_path:
    n = g_meshQueueCount;
    e = &g_meshQueueEntries[n];
    n++;
    g_meshQueueCount = n;
store:
    e->count = a3;
    idx = 0;
    if (a5 != 0) {
        idx = a5->frame;
    }
    scale = a1->stride;
    base = a1->base;
    off = idx * scale;
    e->dstAddr = a2;
    e->flag = a4;
    e->value = base + (off << 4);
    SubmitMeshQueueEntry(e);
    if (link != 0) {
        FrameLink* p = (FrameLink*)AllocateZeroedFrontMemory(12);
        if (p != 0) {
            p->src = a1;
            p->dst = e;
            p->next = a5->links;
            a5->links = p;
        }
    }
}

void QueueNodeLink(s32 a0, s32 a1, AnimCursor* a2)
{
    FrameTarget local;
    FrameTarget* e;
    s32 count = g_meshQueueCount;

    if (count >= 0x4000) {
        e = &local;
    } else {
        e = &g_meshQueueEntries[count];
        g_meshQueueCount = count + 1;
    }
    e->count = a1;
    e->value = (s32)a2 + 0xC;
    e->dstAddr = a0;
    e->flag = 0;
    SubmitMeshQueueEntry(e);
    if (g_meshQueueCount < 0x4000) {
        FrameLink* p = (FrameLink*)AllocateZeroedFrontMemory(12);
        p->dst = e;
        p->src = 0;
        p->next = a2->links;
        a2->links = p;
    }
}

void RemapMeshQueueValues(s32 idx, u32 lo, u32 take, u32 give)
{
    u32 end = take + lo;

    if (idx < g_meshQueueCount) {
        FrameTarget* e = &g_meshQueueEntries[idx];
        s32 n = g_meshQueueCount - idx;

        do {
            if (e->dstAddr >= take && e->dstAddr < end) {
                e->dstAddr = give + (e->dstAddr - take);
            }
            e++;
            n--;
        } while (n != 0);
    }
}

void FlushMeshQueue(void)
{
    s32 i;

    for (i = 0; i < g_meshQueueCount; i++) {
        SubmitMeshQueueEntry(&g_meshQueueEntries[i]);
    }
}

s32 UploadImagesByMask(u32 mask)
{
    BumpAllocator span;
    PacketWriter fa;
    PacketWriter fb;
    u8 buf[0xA0];
    s32 o0;
    s32 o1;
    s32 res;
    s32 i;

    InitBumpAllocator(&span, 0x1400, 0x1E00);
    InitGifPacket(&fa);
    res = 0;
    InitPacketWriter(&fb);
    PushBackMemoryMark();
    AllocateTempPacketBuffer(&fb, (g_imageSlotsB * 2 + g_imageSlotsB + g_imageSlotsA) * 10 + 4);
    BeginDmaTag(&fb);
    WriteVifFlush(&fb);
    for (i = 0; i < g_imageRecordCountB; i++) {
        PaletteRecord* e = (PaletteRecord*)((*(u8**)&g_imageRecordsB) + i * 0x18);
        if ((e->f0 & mask) == mask) {
            RewindPacketBuffer(&fa);
            UsePacketBufferMemory(&fa, 0xA, buf);
            s32 n = AllocateBump((s32*)&span, e->bumpSize);
            BuildPaletteTexRegister(e, n);
            StartPaletteUpload(e, n, &fa);
            *(u64*)(fa.curS - 0x10) |= 0x8000;
            DetachPacketBuffer(&fa, (u32*)&o0, (u8**)&o1);
            WriteVifDirect(&fb, o0, o1, 0);
            WriteVifDirectRef(&fb, e->blockCount, e->data, 0);
            if (e->f0 & 0x40000000) {
                e->f0 = 0x40000000;
            }
        }
    }
    if (g_imageRecordCountA > 0) {
        i = 0;
        do {
            ImageRecord* e = (ImageRecord*)((*(u8**)&g_imageRecordsA) + i * 0x20);
            if ((e->f4 & mask) == mask) {
                RewindPacketBuffer(&fa);
                UsePacketBufferMemory(&fa, 0xA, buf);
                s32 n = AllocateBump((s32*)&span, e->bumpSize);
                BuildImageTexRegister(e, n);
                StartImageUpload(e, n, &fa);
                *(u64*)(fa.curS - 0x10) |= 0x8000;
                DetachPacketBuffer(&fa, (u32*)&o0, (u8**)&o1);
                WriteVifDirect(&fb, o0, o1, 0);
                WriteVifDirectRef(&fb, e->blockCount, e->data, 0);
                if (e->f4 & 0x40000000) {
                    e->f4 = 0x40000000;
                }
            }
            i++;
        } while (i < g_imageRecordCountA);
    }
    if (span.next > span.start) {
        RewindPacketBuffer(&fa);
        UsePacketBufferMemory(&fa, 0xA, buf);
        BeginGifTag(&fa, 0, 1, 0xE);
        AddGifRegisterWrite(&fa, 0x3F, 0);
        EndGifPacket(&fa);
        DetachPacketBuffer(&fa, (u32*)&o0, (u8**)&o1);
        WriteVifDirect(&fb, o0, o1, 0);
        WriteVifFlush(&fb);
        CloseDmaTag(&fb);
        *(u64*)fb.curS = 0x60000000;
        fb.curS += 0x10;
        DetachPacketBufferCopy(&fb, 0, 0, &res, 7);
        BuildAnimRecordGifPackets(mask);
    }
    PopBackMemoryMark();
    return res;
}

void SetupTextureRenderTarget(TextureHeader* src, void* dst)
{
    s32 w = 1 << (s32)((src->tex0 >> 26) & 0xF);
    s32 cap = 64;
    if (cap < w) cap = w;
    s32 f = (s32)(src->tex0 & 0x3FFF) >> 5;
    s32 m = 1 << (s32)((src->tex0 >> 30) & 0xF);
    BeginGifTag((PacketWriter*)dst, 0x200, 1, 0xE);
    AddGifRegisterWrite((PacketWriter*)dst, 0x4D, (u64)(cap / 64) << 16 | (u64)f);
    AddGifRegisterWrite((PacketWriter*)dst, 0x4F, 0x30000000 | (u64)f | (u64)0x8000 << 17);
    AddGifRegisterWrite((PacketWriter*)dst, 0x19, 0);
    AddGifRegisterWrite((PacketWriter*)dst, 0x41, (u64)(w - 1) << 16 | (u64)(m - 1) << 48);
    AddGifRegisterWrite((PacketWriter*)dst, 0x48, 0x31001);
    AddGifRegisterWrite((PacketWriter*)dst, 0x43, 0x44);
}
