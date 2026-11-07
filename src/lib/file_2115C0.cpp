// SPDX-License-Identifier: AGPL-3.0-or-later
// The MPEG library's bit reader over a ring buffer, from 0x2115C0 to 0x2117D0, built whole
// (config/us/files.tsv): its set-up (func_002115C0), the peek at the next bits
// (func_002115F8), the advance that refills the 64-bit window a byte at a time, wrapping at the
// buffer's end (func_00211618), the read of n bits and of one bit (func_002116B0,
// func_00211700), the skip of whole bytes (func_00211748) and the position a number of bits
// ahead (func_002117A0). The demultiplexer (src/lib/file_20A190.cpp) is its only user; it reads
// no IPU register and has no data. Both edges are chosen: the MPEG library's DMA code before it
// never calls it and the IPU library's transfers after it start at 0x2117D0, but no data or
// padding decides either edge. Named after its first address. Written for this project from
// retail's code.
#include "common.h"
#include "asm_func.h"

// The reader: the 64-bit window of bits not yet consumed, the byte the count of consumed bits
// starts from, the next byte to load, how many bits of the window are loaded, the count of bits
// consumed, and the ring buffer (its start, end and size).
struct BitReader_2115C0 {
    u64 window;
    u32 origin;
    u32 next;
    u32 loaded;
    u32 pad14;
    u64 consumed;
    u32 bufStart;
    u32 bufEnd;
    u32 bufSize;
};

s64 func_002115F8(BitReader_2115C0* self, s32 n);
void func_00211618(BitReader_2115C0* self, s32 n);

void func_002115C0(BitReader_2115C0* self, u32 buf, u32 a, u32 b)
{
    self->origin = buf;
    self->next = buf;
    self->window = 0;
    self->loaded = 0;
    self->consumed = 0;
    self->bufStart = a;
    self->bufEnd = a + b;
    self->bufSize = b;
    func_00211618(self, 0);
}

INCLUDE_ASM(func_002115F8);

INCLUDE_ASM(func_00211618);

s64 func_002116B0(BitReader_2115C0* self, s32 n)
{
    s64 r = func_002115F8(self, n);
    func_00211618(self, n);
    return r;
}

s64 func_00211700(BitReader_2115C0* self)
{
    s64 r = func_002115F8(self, 1);
    func_00211618(self, 1);
    return r;
}

void func_00211748(BitReader_2115C0* self, s32 bytes)
{
    self->window = 0;
    self->loaded = 0;
    self->consumed += bytes << 3;
    self->next = self->origin + (s32)(self->consumed >> 3);
    if (self->next >= self->bufEnd) {
        self->next -= self->bufSize;
    }
    func_00211618(self, 0);
}

u32 func_002117A0(BitReader_2115C0* stream, s32 amount)
{
    u32 position = stream->origin + (amount >> 3);
    if (position >= stream->bufEnd) {
        position -= stream->bufSize;
    }
    return position;
}
