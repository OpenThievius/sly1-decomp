// SPDX-License-Identifier: AGPL-3.0-or-later
// Written for this project from what retail's code does (ring_buffer.cpp works on it,
// movie_player.cpp keeps three).
#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include "common.h"

// The ring buffer the movie player streams through (func_0018E940 and its neighbours keep two):
// InitRingBuffer gives it its memory and size, FillRingBuffer writes into it from a reader,
// DrainRingBuffer hands what it holds to a sink, and ConsumeSpan gives back the space of what a
// sink has taken but not yet released.
struct RingBuffer {
    u8* buf;                // 0x00: the memory (InitRingBuffer)
    s32 size;               // 0x04: its size
    s32 writePos;           // 0x08: where FillRingBuffer writes next
    s32 readPos;            // 0x0C: where DrainRingBuffer reads next
    s32 space;              // 0x10: the bytes free to fill (the size at reset)
    s32 filled;             // 0x14: the bytes filled and not drained yet
    s32 held;               // 0x18: drained to a sink that was not idle, until ConsumeSpan releases them
    s32 written;            // 0x1C: the bytes filled since the reset
};

typedef char check_RingBuffer[sizeof(RingBuffer) == 0x20 ? 1 : -1];

#endif
