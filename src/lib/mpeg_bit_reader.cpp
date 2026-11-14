// SPDX-License-Identifier: AGPL-3.0-or-later
// The MPEG library's bit reader over a ring buffer, from 0x2115C0 to 0x2117D0, built whole
// (config/us/files.tsv): its set-up (func_002115C0), the peek at the next bits
// (func_002115F8), the advance that refills the 64-bit window a byte at a time, wrapping at the
// buffer's end (func_00211618), the read of n bits and of one bit (func_002116B0,
// func_00211700), the skip of whole bytes (func_00211748) and the position a number of bits
// ahead (func_002117A0). The demultiplexer (src/lib/mpeg_demultiplexer.cpp) is its only user; it reads
// no IPU register and has no data. Both edges are chosen: the MPEG library's DMA code before it
// never calls it and the IPU library's transfers after it start at 0x2117D0, but no data or
// padding decides either edge. Written for this project from
// retail's code.
#include "common.h"
#include "mpeg_bit_reader.h"


void InitBitReader(BitReader* self, u32 buf, u32 a, u32 b)
{
    self->origin = buf;
    self->next = buf;
    self->window = 0;
    self->loaded = 0;
    self->consumed = 0;
    self->bufStart = a;
    self->bufEnd = a + b;
    self->bufSize = b;
    AdvanceBits(self, 0);
}

s32 PeekBits(BitReader* self, s32 n)
{
    return self->window >> (64 - n);
}

// Returns the new count of consumed bits (retail leaves it in $v0; no caller reads it). The
// loop tests a local copy of the loaded count, and the byte is read into its own local: with
// the return, these are insns gcse still sees and later passes delete, and they give its
// expression table the 21 buckets whose order gives n's widening its register before the
// consumed count's (docs/TOOLCHAIN.md, "Sony's compiler: the same bucket order").
u64 AdvanceBits(BitReader* self, s32 n)
{
    self->window <<= n;
    u32 loaded = self->loaded -= n;
    while (loaded < 57) {
        u8* p = (u8*)self->next;
        u8 c = *p++;
        self->window |= (u64)c << (56 - self->loaded);
        self->next = (u32)p;
        if ((u32)p >= self->bufEnd) {
            self->next = self->bufStart;
        }
        loaded = self->loaded += 8;
    }
    return self->consumed += n;
}

u32 ReadBits(BitReader* self, s32 n)
{
    u32 r = PeekBits(self, n);
    AdvanceBits(self, n);
    return r;
}

s32 ReadBit(BitReader* self)
{
    s32 r = PeekBits(self, 1);
    AdvanceBits(self, 1);
    return r;
}

void SkipBytes(BitReader* self, s32 bytes)
{
    self->window = 0;
    self->loaded = 0;
    self->consumed += bytes << 3;
    self->next = self->origin + (s32)(self->consumed >> 3);
    if (self->next >= self->bufEnd) {
        self->next -= self->bufSize;
    }
    AdvanceBits(self, 0);
}

u32 GetPositionAhead(BitReader* stream, s32 amount)
{
    u32 position = stream->origin + (amount >> 3);
    if (position >= stream->bufEnd) {
        position -= stream->bufSize;
    }
    return position;
}
