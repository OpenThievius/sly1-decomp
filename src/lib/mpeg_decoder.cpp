// SPDX-License-Identifier: AGPL-3.0-or-later
// The MPEG library's decoder front end, from 0x20ADA0 to 0x20C1A0, built whole
// (config/us/files.tsv): the library's initialisation (func_0020ADA0), the decoder's creation,
// reset and deletion and the setters the game calls (func_0020AE40 to func_0020B168), its message
// queue, ring buffer and error reporting, the picture loop (func_0020B2E8 to func_0020B790), the
// sequence header and the extensions it reads (func_0020B9F0 to func_0020C168), and the IPU's DMA
// stop and restart around a picture (func_0020C178, func_0020C188). One file between two edges,
// with no evidence of a boundary inside it; it could be several. Its .rodata is its messages and
// the jump table of func_0020B2E8, its .data the library's identification string and the default
// quantiser matrices. Written for this project from retail's code.
#include "common.h"
#include "asm_func.h"
#include "mpeg_decoder.h"

// The library's identification string, 16 characters without a terminator.
char D_0027AF70[16] = { 'P', 's', 'I', 'I', 'l', 'i', 'b', 'm', 'p', 'e', 'g', ' ', '2', '4', '2', '0' };

// The default quantiser matrices: intra, and non-intra (all 16).
u8 D_0027AF80[64] = { 0x08, 0x10, 0x10, 0x13, 0x10, 0x13, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x1a, 0x18, 0x1a, 0x1b, 0x1b, 0x1b, 0x1a, 0x1a, 0x1a, 0x1a, 0x1b, 0x1b, 0x1b, 0x1d, 0x1d, 0x1d, 0x22, 0x22, 0x22, 0x1d, 0x1d, 0x1d, 0x1b, 0x1b, 0x1d, 0x1d, 0x20, 0x20, 0x22, 0x22, 0x25, 0x26, 0x25, 0x23, 0x23, 0x22, 0x23, 0x26, 0x26, 0x28, 0x28, 0x28, 0x30, 0x30, 0x2e, 0x2e, 0x38, 0x38, 0x3a, 0x45, 0x45, 0x53 };
u8 D_0027AFC0[64] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };

extern "C" s32 DisableInterrupts(void);
extern "C" s32 EnableInterrupts(void);
void ResetIpu(void);

void InitMpegLibrary(void) {
    DisableInterrupts();
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
    *(volatile u32*)0x1000B000 &= 0xFFFFFEFF;
    *(volatile u32*)0x1000B400 &= 0xFFFFFEFF;
    *(u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
    EnableInterrupts();
    *(volatile u32*)0x1000B020 = 0;
    *(volatile u32*)0x1000B420 = 0;
    ResetIpu();
}

extern "C" void* FillMemory(s32 dst, s32 c, u32 n);
void ReportMpegError(MpegDecoder* self, const char* value);
void InitMpegRing(MpegRing* r, u32 start, u32 size);
s32 AllocateFromMpegRing(MpegDecoder* owner, MpegRing* pool, u32 offset, u32 align);
void SetUpMpegScratchpadBuffers(MpegDecoder* self);
void ResetMpegDecoder(MpegHandle* d);
s32 ReleaseMpegPictures(MpegHandle* device);
void MarkMpegRing(MpegRing* r); // stays void: retail returns a value, but declared so func_0020AE40 differs in registers
void SaveMpegDmaState(MpegHandle* self);
void RestoreMpegDmaState(MpegHandle* self);

s32 CreateMpegDecoder(MpegHandle* out, s32 mem, u32 size)
{
    FillMemory(mem, 0, size);
    u32 base = ((u32)(mem + 3) >> 2) << 2;
    MpegDecoder* in = (MpegDecoder*)base;
    s32 diff = base - mem;
    u32 rest = size - diff;
    if (rest < 0x10C0) {
        ReportMpegError(in, "The size of work area is too small");
        return 0;
    }
    out->decoder = in;
    rest -= 0x10C0;
    InitMpegRing(&in->ring, base + 0x10C0, rest);
    out->pictureWidth = 0;
    out->pictureHeight = 0;
    out->pictureIndex = 0;
    out->info[0].pts = -1;
    out->info[0].dts = -1;
    out->info[0].flags = 0;
    out->info[1].pts = -1;
    out->info[1].dts = -1;
    out->info[1].flags = 0;
    in->outputCentreHorizontal[0] = 0;
    in->outputCentreHorizontal[1] = 0;
    in->outputCentreHorizontal[2] = 0;
    in->outputCentreVertical[0] = 0;
    in->outputCentreVertical[1] = 0;
    in->outputCentreVertical[2] = 0;
    in->outputDisplayWidth = 0;
    in->outputDisplayHeight = 0;
    in->firstStructure = 0;
    in->outputBuffer = 0;
    in->outputWidth = 0;
    in->outputHeight = 0;
    in->outputMacroblocks = 0;
    in->fE8 = 0;
    in->fF8 = 0;
    in->callbacks[0].fn = 0;
    in->callbacks[1].fn = 0;
    in->callbacks[4].fn = 0;
    in->callbacks[5].fn = 0;
    in->callbacks[6].fn = 0;
    in->fF0 = -1;
    in->callbacks[2].fn = (MpegCallbackFn)SaveMpegDmaState;
    in->callbacks[3].fn = (MpegCallbackFn)RestoreMpegDmaState;
    u32 table = AllocateFromMpegRing(in, &in->ring, 0x600, 8);
    in->streamCount = 0;
    in->frameBuffer[0] = 0;
    in->frameBuffer[1] = 0;
    in->frameBuffer[2] = 0;
    in->f70 = 0;
    in->f78 = 0;
    in->f80 = -1;
    in->f88 = 0;
    in->f90 = 0;
    in->firstPictureNumber = 0;
    in->pictureLimit[0] = -1;
    in->pictureLimit[1] = -1;
    in->pictureLimit[2] = -1;
    in->handle = out;
    in->streamTable = (MpegStreamEntry*)table;
    in->convertColours = 1;
    SetUpMpegScratchpadBuffers(in);
    ResetMpegDecoder(out);
    ReleaseMpegPictures(out);
    in->pictures[0] = &in->views[0];
    in->pictures[1] = &in->views[1];
    in->pictures[3] = &in->views[2];
    in->pictures[4] = &in->views[3];
    in->pictures[5] = &in->views[4];
    in->pictures[7] = &in->views[5];
    in->pictures[8] = &in->views[6];
    in->pictures[9] = &in->views[7];
    in->pictures[11] = &in->views[8];
    MarkMpegRing(&in->ring);
    in->maxOrder = -1;
    in->gopStart = 0;
    in->orderBase = 0;
    in->scratchDestination = 0x70003600;
}

s32 DeleteMpegDecoder(MpegHandle* self) {
	return 1;
}

LINKER_REMNANT(func_0020B050);


s32 RunMpegPictureLoop(MpegHandle* self);

s32 DecodeMpegPicture(MpegHandle* obj, void* picture, s32 a2)
{
    MpegDecoder* st = obj->decoder;
    st->convertColours = 1;
    st->outputBuffer = ((u32)picture & 0xFFFFFFFu) | 0x20000000u;
    st->outputMacroblocks = a2;
    st->outputHeight = 0;
    st->outputWidth = 0;
    return RunMpegPictureLoop(obj);
}

LINKER_REMNANT(func_0020B0A0);

s32 GetMpegDecoderStatus(MpegHandle* device) {
	return device->decoder->ended;
}

void ResetMpegPictureMode(MpegDecoder* s);
void ResetMpegDmaAndIpu(MpegDecoder* c);
void ResetMpegDecoder(MpegHandle* d) {
    MpegDecoder* s = d->decoder;
    s->ended = 0;
    s->pending = 0;
    s->phase = 0;
    d->pictureIndex = 0;
    s->firstPictureNumber = 0;
    s->f80 = -1;
    ResetMpegDmaAndIpu(s);
    s->pictureNumber = 0;
    ResetMpegPictureMode(s);
}

s32 ReleaseMpegPictures(MpegHandle* device) {
	MpegDecoder* state = device->decoder;
	if (state->pictures[0]) state->pictures[0]->decoded = 0;
	if (state->pictures[4]) state->pictures[4]->decoded = 0;
	if (state->pictures[8]) state->pictures[8]->decoded = 0;
	if (state->pictures[1]) state->pictures[1]->decoded = 0;
	if (state->pictures[5]) state->pictures[5]->decoded = 0;
	if (state->pictures[9]) state->pictures[9]->decoded = 0;
	return 1;
}


// Sets the callback of an index (func_0020B190 runs it) and returns the one it replaces. Retail
// addresses the function and its argument from two bases (the table's start, and its start moved
// by the function's offset), which the words of the table's entries give where one
// MpegCallback pointer would be a single base: the table is walked as words, as the original did.
s32 SetMpegCallback(MpegHandle* obj, s32 index, s32 value, s32 second)
{
    u32* array = (u32*)obj->decoder;
    u32* current = array + 3;
    u32 offset = index * 2;
    current += offset;
    array += offset;
    array[4] = second;
    s32 old = *current;
    *current = value;
    return old;
}

s32 RunMpegCallback(MpegHandle* p, s32* idx) {
    s32 r = 0;
    if (p != 0) {
        MpegDecoder* t = p->decoder;
        if (t != 0) {
            MpegCallbackFn fn = t->callbacks[*idx].fn;
            if (fn != 0) {
                r = fn(p, idx, t->callbacks[*idx].arg);
            }
        }
    }
    return r;
}

s32 RunMpegStallCallback(MpegHandle* q)
{
    s32 flag[8];
    flag[0] = 1;
    return RunMpegCallback(q, flag);
}

LINKER_REMNANT(func_0020B208);

void InitMpegRing(MpegRing* ring, u32 start, u32 size)
{
    ring->start = start;
    ring->size = size;
    ring->cursor = start;
    ring->mark = start;
}

void MarkMpegRing(MpegRing* ring) {
	ring->mark = ring->cursor;
}

s32 RewindMpegRingToMark(MpegRing* ring)
{
    s32 value = ring->mark;
    ring->cursor = value;
    return value;
}

void ReportMpegError(MpegDecoder* self, const char* value);

s32 AllocateFromMpegRing(MpegDecoder* owner, MpegRing* pool, u32 offset, u32 align)
{
    u32 base;
    u32 end;

    base = (pool->cursor + align - 1) / align;
    base = base * align;
    end = base + offset;
    if (pool->start + pool->size >= end) {
        pool->cursor = end;
        return base;
    }
    (void)ReportMpegError(owner, "work area size is too small");
    return 0;
}

void ReportMpegErrorFormat(MpegDecoder* c, const char* fmt, s32 value);
s32 ParseMpegHeaders(MpegDecoder* self);
s32 DecodePictureByStructure(MpegHandle* self, s32 a, s32 b);
s32 FlushPendingPicture(MpegHandle* self);

s32 RunMpegPictureLoop(MpegHandle* self)
{
    s32 s3 = 1;
    s32 s2 = 0;
    MpegDecoder* c = self->decoder;
    c->ended = 0;
    if ((c->outputBuffer & 0x3F) != 0) {
        ReportMpegErrorFormat(c, "image buffer needs to be aligned to 64byte boundary(0x%08x)", c->outputBuffer);
        return -1;
    }
    c->pictureReady = 0;
    for (;;) {
        if (s2 != -1) {
            do {
                s3 = ParseMpegHeaders(c);
                if (s3 == 0) break;
                if (c->pictureStructure == c->firstStructure) break;
            } while (c->mpeg2 != 0);
        }
        switch (s3) {
        case 0:
            (void)FlushPendingPicture(self);
            c->ended = 1; 
            break;
        case 1:
            c->pictureCount[2] = 0;
            c->pictureCount[1] = 0;
            c->pictureCount[0] = 0;
            s2 = DecodePictureByStructure(self, 0, c->pictureLimit[0]);
            c->pictureCount[0]++;
            break;
        case 2:
            s2 = DecodePictureByStructure(self, c->pictureCount[1], c->pictureLimit[1]);
            c->pictureCount[1]++;
            break;
        case 3:
        case 4:
            s2 = DecodePictureByStructure(self, c->pictureCount[2], c->pictureLimit[2]);
            c->pictureCount[2]++;
            break;
        }
        if (c->pictureReady != 0 || c->ended != 0) break;
    }
    return 1;
}

extern s32 SelectPictureBuffer(MpegDecoder* p, s32 flag);
extern s32 DecodePictureData(MpegDecoder* self);
extern void OutputPictureIfDecoded(MpegDecoder* self, s32 count, s32 flag);
extern s32 RunMpegStallCallback(MpegHandle* q);

struct FramePictureStep {
    static s8 Ready(MpegDecoder* e)
    {
        s32 t = SelectPictureBuffer(e, 0);
        s8 r = 0;
        if (t != 0) {
            r = DecodePictureData(e) != 0;
        }
        return r;
    }
};

s32 DecodeFramePicture(MpegHandle* s1, s32 a1, s32 a2)
{
    s32 s2;
    MpegDecoder* s0 = s1->decoder;
    s32 s3 = 0;

    if (a2 == -1 || a1 < a2) {
        if (s0->phase == 0) {
            s1->pictureIndex = 0;
            s0->phase = 1;
        }
        s2 = FramePictureStep::Ready(s0);
    } else {
        s2 = SelectPictureBuffer(s0, 0);
        s3 = 1;
        (void)RunMpegStallCallback(s1);
    }
    OutputPictureIfDecoded(s0, s0->pictureNumber, s0->pending);
    if (s0->pictureStructure == 3) {
        ;
    } else if (s3 == 0) {
        s0->secondField = (s0->secondField == 0);
    }
    s1->pictureIndex = s0->pictureNumber - s0->firstPictureNumber;
    if (s0->secondField == 0) {
        s0->pictureNumber = s0->pictureNumber + 1;
        s0->pending = s0->pending + 1;
    }
    return s2;
}

s32 DecodeFieldPicture(MpegHandle* self, s32 a1, s32 a2);

s32 DecodePictureByStructure(MpegHandle* self, s32 a, s32 b)
{
    if (self->decoder->pictureStructure != 3) {
        return DecodeFieldPicture(self, a, b);
    }
    return DecodeFramePicture(self, a, b);
}

s32 DecodeFieldPicture(MpegHandle* self, s32 a1, s32 a2)
{
    s32 s3 = 0;
    MpegDecoder* s0;
    s32 s1;
    s32 s4;
    s32 t;
    s32 r;

    s0 = self->decoder;
    s0->secondField = 0;
    if (a2 == -1 || a1 < a2) {
        s3 = 1;
    }
    if (s0->phase == 0) {
        self->pictureIndex = 0;
        s0->phase = 1;
    }
    if (SelectPictureBuffer(s0, 0) != 0) {
        if (s3 != 0) {
            (void)DecodePictureData(s0);
        }
    }
    s1 = 1;
    s0->secondField = s1;
    if (ParseMpegHeaders(s0) == 0) {
        (void)FlushPendingPicture(self);
        s0->ended = s1;
        return 0;
    }
    t = (s0->firstStructure ^ 1) != 0 ? s1 : 2;
    if (s0->pictureStructure != t) {
        return -1;
    }
    r = SelectPictureBuffer(s0, 1);
    s32 u = 0;
    if (r != 0) {
        u = s1;
    }
    s4 = 0;
    if (u != 0) {
        if (s3 != 0) {
            s4 = (DecodePictureData(s0) != 0) ? s1 : 0;
        }
    }
    OutputPictureIfDecoded(s0, s0->pictureNumber, s0->pending);
    s0->secondField = 0;
    self->pictureIndex = s0->pictureNumber - s0->firstPictureNumber;
    s0->pictureNumber = s0->pictureNumber + 1;
    s0->pending = s0->pending + 1;
    if (s3 == 0) {
        RunMpegStallCallback(self);
    }
    return s4;
}

extern void OutputPendingPicture(MpegDecoder* self);

s32 FlushPendingPicture(MpegHandle* self)
{
    s32 r = 0;
    MpegDecoder* in = self->decoder;

    if (in->pending != 0) {
        if (in->phase != 0) {
            OutputPendingPicture(in);
            self->pictureIndex = in->pictureNumber - in->firstPictureNumber;
            in->pending = 0;
            r = 1;
        }
    }
    return r;
}

void SetIpuMpeg1Mode(u32 value);
void ResetMpegPictureMode(MpegDecoder* s) {
    s->mpeg2 = 0;
    SetIpuMpeg1Mode(1);
}

void ReportMpegError(MpegDecoder* self, const char* value);
void OutputFramePicture(MpegDecoder* c, MpegPicture* s, s32 count);
void OutputFieldPicturePair(MpegDecoder* c, MpegPicture* a, MpegPicture* b, s32 count);

void OutputPendingPicture(MpegDecoder *self)
{
    s32 n = self->pictureNumber;
    if (self->secondField != 0)
        ReportMpegError(self, "the second field is missing");
    else if (self->pictureStructure == 3)
        OutputFramePicture(self, self->pictures[1], n - 1);
    else
        OutputFieldPicturePair(self, self->pictures[5], self->pictures[9], n - 1);
    self->secondField = 0;
}

void SetIpuMpeg1Mode(u32 value);

void SetUpMpegScratchpadBuffers(MpegDecoder* self)
{
    u32 spr = 0x70000000;
    SetIpuMpeg1Mode(1);
    self->macroblock[0].work = spr;
    self->macroblock[0].output = spr + 0x1800;
    self->macroblock[1].work = spr + 0x1B00;
    self->macroblock[1].output = spr + 0x3300;
    self->currentMacroblock = 0;
}

extern "C" s32 DisableInterrupts(void);
extern "C" s32 EnableInterrupts(void);
u32 SyncIpu(s32 a, s32 b);

void ResetMpegDmaAndIpu(MpegDecoder* c) {
    c->windowInvalid = 1;
    c->dcReset = 0;
    DisableInterrupts();
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
    *(volatile u32*)0x1000B000 = 0;
    *(volatile u32*)0x1000B400 = 0;
    *(volatile u32*)0x1000D400 = 0;
    *(u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
    EnableInterrupts();
    *(volatile u32*)0x1000B020 = 0;
    *(volatile u32*)0x1000B420 = 0;
    *(volatile u32*)0x1000D420 = 0;
    *(volatile u32*)0x10002010 = 0x40000000;
    SyncIpu(0, 0);
}

extern "C" s32 PrintFormatted(const char* fmt, ...);

void PrintMpegError(const char* msg) {
    PrintFormatted("[MPEG ERROR]%s\n", msg);
}

s32 FormatToString(char* dst, const char* fmt, ...);

void ReportMpegErrorFormat(MpegDecoder* self, const char* fmt, s32 value)
{
    char buf[0x100];
    FormatToString(buf, fmt, value);
    ReportMpegError(self, buf);
}

struct MpegErrorMessage {
    s32 kind;
    const char* text;
};

s32 RunMpegCallback(MpegHandle* sub, MpegErrorMessage* message);

void ReportMpegError(MpegDecoder* self, const char* value)
{
    MpegErrorMessage message;

    if (self->handle != 0 && self != 0 && self->callbacks[0].fn != 0) {
        message.kind = 0;
        message.text = value;
        RunMpegCallback(self->handle, &message);
        return;
    }
    PrintMpegError(value);
}

s32 SetPictureDimensions(MpegPicture* picture, s32 x, s32 y)
{
    picture->width = x;
    picture->height = y;
    picture->mbWidth = x >> 4;
    picture->mbHeight = y >> 4;
    return 1;
}

u32 ReadIpuBits(MpegDecoder* obj, s32 a1);
void WaitIpuCommandDone(MpegDecoder* d);
void SendIpuCommand(MpegDecoder* obj, u32 value);
void LoadIpuQuantiserMatrix(MpegDecoder* d, u32 value, u8* table);
void ReadExtensionsAndUserData(MpegDecoder* self);
void AllocatePictureBuffers(MpegHandle* handle);

void ReadSequenceHeader(MpegDecoder* d) {
    d->firstStructure = 0;
    u32 v = ReadIpuBits(d, 0x20);
    d->width = v >> 20;
    d->height = (v >> 8) & 0xFFF;
    if (d->height > 0xAF0) {
        ReportMpegError(d, "vertical size > 2800");
    }
    v = ReadIpuBits(d, 0x1E);
    d->bitRate = v >> 12;
    d->vbvBufferSize = (v >> 1) & 0x3FF;
    d->loadIntraMatrix = ReadIpuBits(d, 1);
    if (d->loadIntraMatrix) {
        WaitIpuCommandDone(d);
        SendIpuCommand(d, 0x50000000);
        WaitIpuCommandDone(d);
    } else {
        LoadIpuQuantiserMatrix(d, 0x50000000, D_0027AF80);
    }
    d->loadNonIntraMatrix = ReadIpuBits(d, 1);
    if (d->loadNonIntraMatrix) {
        WaitIpuCommandDone(d);
        SendIpuCommand(d, 0x58000000);
        WaitIpuCommandDone(d);
    } else {
        LoadIpuQuantiserMatrix(d, 0x58000000, D_0027AFC0);
    }
    ReadExtensionsAndUserData(d);
    AllocatePictureBuffers(d->handle);
}

void SetUpPictureBufferAddresses(u32* a0, u32* a1, u32* a2, u32* a3, u32* a4, u32* a5, u32* a6, u32* a7, u32* p9, u32 p10, u32 p11, u32 p12, s32 p13, s32 p14);

void AllocatePictureBuffers(MpegHandle* handle)
{
    MpegDecoder* st = handle->decoder;
    s32 w;
    s32 h;
    u32 size;
    s32 rows;
    u32* p3;

    if (st->mpeg2 == 0) {
        st->pictureStructure = 3;
        st->progressiveSequence = 1;
        st->chromaFormat = 1;
        st->progressiveFrame = 1;
        st->framePredFrameDct = 1;
        st->f144 = 5;
    }
    st->mbWidth = (st->width + 15) >> 4;
    if (st->mpeg2 != 0 && st->progressiveSequence == 0)
        rows = ((st->height + 31) >> 5) << 1;
    else
        rows = (st->height + 15) >> 4;
    st->mbHeight = rows;
    h = rows << 4;
    w = st->mbWidth << 4;
    if (w == handle->pictureWidth && h == handle->pictureHeight)
        return;
    // NOT THE ORIGINAL'S STATEMENT: a stand-in for it. This test reads p3 before it has a
    // value and is never true (w is a multiple of 16), and it leaves no instruction. Retail's
    // code shows that the original had, at this point, a test only combine could fold whose
    // condition held the last reference to a variable that later lives on the stack: combine
    // then leaves a USE of that variable at the body's head, which the two picture stores
    // must wait for, so the last plane's address issues alone in the body's first cycle
    // (docs/toolchain/sched1.md, "A block whose first cycle holds one insn"). Eight passes,
    // an independent re-decompilation and a sweep of 2,247 build settings found no other
    // form; what the original's statement was is not known. Allowed for this one function
    // (AGENTS.md's named exceptions).
    if ((u32)p3 & (w & 15))
        handle->pictureWidth = 0;
    handle->pictureWidth = w;
    handle->pictureHeight = h;
    size = (u32)(w * 0x180 * h) >> 8;
    p3 = &st->views[3].address;
    RewindMpegRingToMark(&st->ring);
    st->frameBuffer[0] = AllocateFromMpegRing(st, &st->ring, size, 0x40);
    st->frameBuffer[1] = AllocateFromMpegRing(st, &st->ring, size, 0x40);
    st->frameBuffer[2] = AllocateFromMpegRing(st, &st->ring, size, 0x40);
    SetUpPictureBufferAddresses(&st->views[0].address, &st->views[1].address, &st->views[2].address, p3,
                  &st->views[4].address, &st->views[5].address, &st->views[6].address, &st->views[7].address,
                  &st->views[8].address, st->frameBuffer[0], st->frameBuffer[1], st->frameBuffer[2], w, h);
    SetPictureDimensions(&st->views[0], w, h);
    SetPictureDimensions(&st->views[1], w, h);
    SetPictureDimensions(&st->views[2], w, h);
    SetPictureDimensions(&st->views[3], w, h >> 1);
    SetPictureDimensions(&st->views[4], w, h >> 1);
    SetPictureDimensions(&st->views[5], w, h >> 1);
    SetPictureDimensions(&st->views[6], w, h >> 1);
    SetPictureDimensions(&st->views[7], w, h >> 1);
    SetPictureDimensions(&st->views[8], w, h >> 1);
}

void SetUpPictureBufferAddresses(u32* a0, u32* a1, u32* a2, u32* a3, u32* a4, u32* a5, u32* a6, u32* a7, u32* p9, u32 p10, u32 p11, u32 p12, s32 p13, s32 p14)
{
    u32 mask = 0x0FFFFFFF;
    u32 bits = 0x20000000;
    s32 n = (p13 * p14) / 512;
    *a0 = (p10 & mask) | bits;
    *a1 = (p11 & mask) | bits;
    *a2 = (p12 & mask) | bits;
    *a3 = (p10 & mask) | bits;
    *a4 = (p11 & mask) | bits;
    *a5 = (p12 & mask) | bits;
    u32 y2 = n * 0x180;
    y2 = ((y2 + p10) & mask) | bits;
    u32 u2 = n * 0x180;
    u2 = ((u2 + p11) & mask) | bits;
    u32 v2 = n * 0x180;
    v2 = ((v2 + p12) & mask) | bits;
    *a6 = y2;
    *a7 = u2;
    *p9 = v2;
}

s32 RunMpegCallback(MpegHandle* h, MpegMessage* out);
void WaitIpuCommandDone(MpegDecoder* self); // stays void: retail returns a value, but declared so func_0020BEA0 differs in registers
void SendIpuCommand(MpegDecoder* obj, u32 value);
extern "C" s32 DisableInterrupts(void);
extern "C" s32 EnableInterrupts(void);

void LoadIpuQuantiserMatrix(MpegDecoder* obj, u32 value, u32 mask)
{
    MpegMessage req;
    req.kind = 2;

    RunMpegCallback(obj->handle, &req);
    WaitIpuCommandDone(obj);
    *(volatile u32*)0x10002000 = 0;
    WaitIpuCommandDone(obj);
    (void)DisableInterrupts();
    *(volatile u32*)0x1000B410 = mask & 0x0FFFFFFF;
    *(volatile u32*)0x1000B420 = 4;
    *(volatile u32*)0x1000B400 = 0x101;
    (void)EnableInterrupts();
    SendIpuCommand(obj, value);
    WaitIpuCommandDone(obj);
    req.kind = 3;
    RunMpegCallback(obj->handle, &req);
}


void SetIpuMpeg1Mode(u32 value);
u32 ReadIpuBits(MpegDecoder* obj, s32 a1);
void ReportMpegError(MpegDecoder* self, const char* value);

void ReadSequenceExtension(MpegDecoder *self)
{
    u32 s2;
    u32 s0;
    u32 s3;
    u32 s4;
    u32 s5;

    self->mpeg2 = 1;
    SetIpuMpeg1Mode(0);
    s2 = ReadIpuBits(self, 0x1C);
    s5 = (s2 >> 1) & 0xFFF;
    self->chromaFormat = (s2 >> 17) & 3;
    s4 = (s2 >> 13) & 3;
    s3 = (s2 >> 15) & 3;
    if (self->chromaFormat != 1) {
        ReportMpegError(self, "_chroma_format needs to be 1: 420");
    }
    self->progressiveSequence = (s2 >> 19) & 1;
    s0 = s2 >> 20;
    s2 = ReadIpuBits(self, 0x10) >> 8;
    if (s0 != 0x48 && s0 != 0x58 && s0 != 0x44) {
        ReportMpegError(self, "Unsupported profile/level");
    }
    self->width = (s3 << 12) | (self->width & 0xFFF);
    self->height = (s4 << 12) | (self->height & 0xFFF);
    self->bitRate += s5 << 18;
    self->vbvBufferSize += s2 << 10;
}

void ReadSequenceDisplayExtension(MpegDecoder* self)
{
    ReadIpuBits(self, 3);
    if (ReadIpuBits(self, 1) != 0) {
        ReadIpuBits(self, 8);
        ReadIpuBits(self, 8);
        self->f144 = ReadIpuBits(self, 8);
    }
    self->displayWidth = ReadIpuBits(self, 0xE);
    ReadIpuBits(self, 1);
    self->displayHeight = ReadIpuBits(self, 0xE);
}

void ReportMpegError(MpegDecoder* self, const char* value);

void RejectSequenceScalableExtension(MpegDecoder* self)
{
    ReportMpegError(self, "_sequenceScalableExtension() is not implemented");
}

void ReportMpegError(MpegDecoder* self, const char* value);

void RejectUnknownExtension(MpegDecoder* self)
{
    ReportMpegError(self, "Unknown Extension");
}

void ReportMpegError(MpegDecoder* self, const char* value);

void RejectSpatialScalableExtension(MpegDecoder* self)
{
    ReportMpegError(self, "_pictureSpatialScalableExtension is not supported");
}

void ReportMpegError(MpegDecoder* self, const char* value);

void RejectTemporalScalableExtension(MpegDecoder* self)
{
    ReportMpegError(self, "_pictureTemporalScalableExtension is not supported");
}

void SaveIpuDmaChannels(IpuDmaState* out);

void SaveMpegDmaState(MpegHandle* self)
{
    SaveIpuDmaChannels(&self->decoder->dmaState);
}

void RestoreIpuDmaChannels(IpuDmaState* s0);

void RestoreMpegDmaState(MpegHandle* self)
{
    RestoreIpuDmaChannels(&self->decoder->dmaState);
}
