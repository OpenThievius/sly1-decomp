// SPDX-License-Identifier: AGPL-3.0-or-later
// The movie player's data sink: a C++ class with two virtuals (GCC vtables D_0024B598, for the
// IPU's input DMA channel, and D_0024B5B8, for the ring buffer in the IOP's memory read through
// the SIF; vptr at +0). Written for this project from what retail's code does
// (config/us/tables.tsv, kinds.tsv).
//
// DrainRingBuffer (src/main/ring_buffer.cpp) calls the sink through its virtual methods, and
// src/main/movie_player.cpp defines the two classes derived from it (IopRingSink and IpuDmaSink,
// include/movie_player.h; their vtables and the Put/Idle methods are compiler-generated,
// config/us/generated.tsv). One declaration for both files: the compiler's own table is used
// everywhere, so the call is right with whatever layout the compiler gives it. On retail's
// compiler the entries are {s16 delta; s16 index; fn}, entry 0 being {offset-to-top, rtti} =
// {0, 0, 0}, and the virtual call adds the entry's delta to the sink.
#ifndef STREAM_SINK_H
#define STREAM_SINK_H

#include "common.h"

// Where a transfer's data goes: two virtual methods, which retail's vtables list in this order.
// Put moves up to `size` bytes and returns how many it took; Idle says whether the sink is idle.
class TransferSink {
public:
    virtual s32 Put(s32 size, u8* buf) = 0;
    virtual s32 Idle() = 0;
};

#endif
