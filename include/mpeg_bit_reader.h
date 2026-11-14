// SPDX-License-Identifier: AGPL-3.0-or-later
// The MPEG library's bit reader over a ring buffer (src/lib/mpeg_bit_reader.cpp), which the
// demultiplexer (src/lib/mpeg_demultiplexer.cpp) reads its streams with. Written for this project
// from what retail's code does.
#ifndef MPEG_BIT_READER_H
#define MPEG_BIT_READER_H

#include "common.h"

// The 64-bit window of bits not yet consumed, the byte the count of consumed bits starts from,
// the next byte to load, how many bits of the window are loaded, the count of bits consumed, and
// the ring buffer (its start, end and size).
struct BitReader {
    u64 window;             // 0x00
    u32 origin;             // 0x08
    u32 next;               // 0x0C
    u32 loaded;             // 0x10
    u32 pad14;              // 0x14
    u64 consumed;           // 0x18
    u32 bufStart;           // 0x20
    u32 bufEnd;             // 0x24
    u32 bufSize;            // 0x28
};

typedef char check_BitReader[sizeof(BitReader) == 0x30 ? 1 : -1];

void InitBitReader(BitReader* self, u32 buf, u32 a, u32 b);
s32 PeekBits(BitReader* self, s32 n);
u64 AdvanceBits(BitReader* self, s32 n);
u32 ReadBits(BitReader* self, s32 n);
s32 ReadBit(BitReader* self);
void SkipBytes(BitReader* self, s32 bytes);
u32 GetPositionAhead(BitReader* stream, s32 amount);

#endif
