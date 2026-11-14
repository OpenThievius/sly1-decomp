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
#include "functions/anim_record.h"
#include "functions/display.h"
#include "functions/heap.h"
#include "functions/pooled_object.h"
#include "functions/texture_upload.h"
struct FrameTarget;
struct ImageRecord;
#include "texture_upload_packet.h"
struct PaletteRecord;



#include "dma_chain_block.h"

struct TexturePacketBuffer : PacketWriter { u8* packet; };

extern s32 g_imageSlotsB;
extern s32 g_imageSlotsA;
extern s32 g_gifChannel;

void* InitGifPacket(PacketWriter* f);
void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);
void EndGifPacket(PacketWriter* f);

extern FrameTarget g_meshQueueEntries[];

void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);
void AddGifImageTag(PacketWriter* self, s32 count);

// The GS register TEX0 an image or palette record keeps (ImageRecord at 0x18, PaletteRecord
// at 0x10), as func_00168E78 and func_00168FB0 fill it: the base, width and format, the size
// as powers of two, then the palette's base, format and load mode.



void BeginImageTransfer(u32 dbp, u32 dbw, u32 dpsm, u64 rrw, u32 rrh, s32 x, void* ctx);


// The file's .data (0x2626D0 to 0x2626E8): the mesh queue's count and the bump allocator.
s32 g_meshQueueCount = 0;
BumpAllocator g_bumpAllocator = { 0 };


extern s32 g_gifChannel;




extern s32 g_imageSlotsB;
extern s32 g_imageSlotsA;


extern s32 g_gifChannel;


extern s32 g_imageRecordCountA;
extern s32 g_imageRecordCountB;


// The start of what a queue entry copies: two GIF tags whose words func_001694A0 marks (bit
// 15) when the entry has a flag.





void BeginImageTransfer(TransferBase dbp, u32 dbw, u32 dpsm, u64 rrw, u32 rrh, s32 x, void* ctx);


extern s32 g_imageRecordCountB;
extern s32 g_imageRecordCountA;
extern s32 g_imageSlotsB;
extern s32 g_imageSlotsA;

void* InitPacketWriter(PacketWriter* f);
void WriteVifFlush(PacketWriter* f);
void WriteVifDirect(PacketWriter* f, s32 a, s32 b, s32 c);
void WriteVifDirectRef(PacketWriter* f, s32 a, s32 b, s32 c);


// Sets up the bump allocator (0x1E00 to 0x4000) and empties the mesh queue.
void InitMeshQueue()
{
    InitBumpAllocator(&g_bumpAllocator,0x1E00,0x4000);
    g_meshQueueCount=0;
}

// The smallest n (at most 31) with 1 << n not below the argument; used for texture width and height
// exponents.
u32 CeilLog2(u32 n) { u32 count = 0; u32 value = 1; while (value < n && count < 31) { value <<= 1; count++; } return count; }

// Sets the allocator's start and cursor to value and its limit to other.
void InitBumpAllocator(BumpAllocator* p, s32 value, s32 other) { p->next = value; p->start = value; p->limit = other; }

// Puts the cursor back at the start.
void ResetBumpAllocator(BumpAllocator* p) { p->next = p->start; }

// Returns the allocator's cursor and moves it on by size.
s32 AllocateBump(s32* self,s32 size)
{
    s32 old=self[1];
    self[1]=old+size;
    return old;
}

// Starts an image transfer to the GS: writes the BITBLTBUF (destination base, width and pixel
// format), TRXPOS, TRXREG (width rrw, height rrh) and TRXDIR registers and the IMAGE tag for x
// quadwords.
void BeginImageTransfer(u32 dbp, u32 dbw, u32 dpsm, u64 rrw, u32 rrh, s32 x, void* ctx)
{
    BeginGifTag((PacketWriter*)ctx, 0, 1, 0xE);
    AddGifRegisterWrite((PacketWriter*)ctx, 0x50, ((u64)dbp << 32) | ((u64)dbw << 48) | ((u64)dpsm << 56));
    AddGifRegisterWrite((PacketWriter*)ctx, 0x51, 0);
    AddGifRegisterWrite((PacketWriter*)ctx, 0x52, rrw | ((u64)rrh << 32));
    AddGifRegisterWrite((PacketWriter*)ctx, 0x53, 0);
    AddGifImageTag((PacketWriter*)ctx, x);
}

// Sets a palette's TEX0 fields: its VRAM address, a pixel format by whether it has at most 16
// colours, and the palette load flag.
void BuildPaletteTexRegister(PaletteRecord* self, u32 a1){
 GsTex0* bits = (GsTex0*)&self->texWordBits;
 bits->cbp = a1;
 bits->psm = (self->f4 <= 0x10) ? 0x14 : 0x13;
 bits->cpsm=0; bits->csm=0; bits->csa=0; bits->cld=1;}

// Starts uploading a palette to VRAM address v, as an image 16 or 8 wide by the colour count and
// tall enough to hold them.
void StartPaletteUpload(PaletteRecord* e, s32 v, void* ctx)
{
    s32 step = (e->f4 > 16) ? 16 : 8;
    s32 n = e->f4 - 1;
    TransferBase p;
    p.v = v;
    BeginImageTransfer(p, 1, 0, step, ((n + step) & -step) / step, e->blockCount, ctx);
}

// Fills the image record's TEX0 word: the base at a1, the buffer width and pixel format from the
// record, texture width and height as the log2 of its sizes, and the colour component bit set.
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

// Starts uploading an image record to VRAM address dbp with its format, buffer width and size.
void StartImageUpload(ImageRecord* d, u32 dbp, void* ctx)
{
    BeginImageTransfer(dbp, d->f9, d->f8, d->f0, d->f2, d->blockCount, ctx);
}

// Gives every palette and image record whose mask contains mask its place in the bump allocator b
// (builds its texture register) and, when the packet c is given, adds each one's upload to it.
// Returns whether anything was placed.
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

// Sends the images selected by mask to the GS: PlaceMaskedImages into the given bump allocator and
// a packet that the GIF reads (the closing register writes included). Nothing is done for a zero
// mask.
void SendMaskedImagesToGif(s32 self, BumpAllocator* arg)
{
    TexturePacketBuffer f;

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

// Builds a stand-alone DMA packet that uploads the images selected by mask (PlaceMaskedImages in a
// fresh bump allocator, then a GS register write and the end tag) and keeps it in the frame's out
// pointer; returns that packet, or 0 when nothing was placed.
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

// Copies the entry's source block to its destination and, when it has a flag, ORs 0x8000 and the
// flag into two words of the destination.
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

// Queues one mesh strip for the vector unit: picks a queue entry (the pool of 0x4000, or a local
// one when the strip is shared with an animation cursor) and fills it with the count, destination
// address, flag and the strip's data pointer at the cursor's frame, submits it and, for a linked
// entry, records the link on the cursor.
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

// Adds a copy entry (count, source and destination address) to the mesh queue, or uses a local one
// when the queue is full, submits it and links the entry into the node's list.
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

// For the queue entries from idx on, moves destination addresses in [take, take + lo) to the same
// offset from give.
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

// Submits every entry of the mesh queue.
void FlushMeshQueue(void)
{
    s32 i;

    for (i = 0; i < g_meshQueueCount; i++) {
        SubmitMeshQueueEntry(&g_meshQueueEntries[i]);
    }
}

// Uploads, by the DMA, every palette and image record whose mask bits include mask: for each it
// gives the record space in a bump allocator (0x1400 to 0x1E00), builds its texture register and an
// upload packet, and sends it together with the record's data. The records' masks are then reset to
// the loaded flag (0x40000000). Returns the result flag.
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

// Writes the GS registers that make a texture the render target: the frame and z buffers at the
// texture's base (in 64-word blocks), the scissor from its width and height, and the test and alpha
// state.
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
