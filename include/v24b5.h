// SPDX-License-Identifier: AGPL-3.0-or-later
// Kind v24b5: the movie player's data sinks, two C++ classes with two virtuals each (GCC vtables
// D_0024B598 and D_0024B5B8, vptr at +0). Written for this project from what retail's code does
// (config/us/tables.tsv, kinds.tsv).
//
// src/main/file_18D8E0.cpp is a whole file and defines both classes with real virtual functions
// (Sink_18E6C0 with its Ring_18E6C0 and Dma_18E8C8; their vtables and the Put/Idle methods are
// compiler-generated, config/us/generated.tsv): that file keeps them, and nothing includes this
// header yet. It documents the layouts as plain structs for the callers outside that file
// (func_0013C9D0 reads a sink through entry 1), whose entries are GCC 2.95's
// {s16 delta; s16 index; fn}, entry 0 being {offset-to-top, rtti} = {0, 0, 0}.
#ifndef V24B5_H
#define V24B5_H

#include "common.h"

struct V24B5;

struct V24B5_Vt {
    s16 adj0; s16 idx0; void* fn0;                                              // 0x00
    s16 adj1; s16 idx1; s32 (*put)(V24B5* self, s32 size, u8* buf);             // 0x08: moves up to `size` bytes
    s16 adj2; s16 idx2; s32 (*idle)(V24B5* self);                               // 0x10
};

// D_0024B598, the IPU's input DMA channel (Dma_18E8C8: Put starts a transfer of up to 0x1000
// bytes and returns its size, Idle returns 1). func_0018ECA8 keeps one on its stack.
struct V24B5 {
    const V24B5_Vt* vt;     // 0x00
};

// D_0024B5B8, a ring buffer in the IOP's memory read through the SIF (Ring_18E6C0). The movie
// player's stream embeds one at +0x6C of its 0x94 bytes, which is the global D_00269AEC. Put
// reads up to `avail14` bytes in pieces of func_0018E7C0, never past the end of the ring.
struct V24B5_5B8 : V24B5 {
    s32 iop04;              // 0x04: the ring's address in the IOP
    s32 size08;             // 0x08: its size
    s32 rd0C;               // 0x0C: the read position
    s32 f10;                // 0x10: the write position (func_0018E838)
    s32 avail14;            // 0x14: the bytes ready (the size at reset, func_0018E6A0)
    s32 used18;             // 0x18: the bytes taken since the reset
    s32 total1C;            // 0x1C: the bytes taken in all
};

typedef char check_V24B5[sizeof(V24B5) == 0x4 ? 1 : -1];
typedef char check_V24B5_5B8[sizeof(V24B5_5B8) == 0x20 ? 1 : -1];

#endif
