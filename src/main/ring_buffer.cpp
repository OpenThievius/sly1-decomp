// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "memory_reader.h"
#include "stream_sink.h"

// An entry of the file's two GCC vtables, written out as tables of functions.
typedef void (*Fn_Table)();
s32 func_0013CC80(MemoryReader* self, s32 want, void* dst);
int func_0013CCE8();

// The file's .rodata, in retail's order: the vtable of the reader's base (its one virtual,
// func_0013CCE8, returns 0; nothing builds that class) and the memory reader's (D_00249D98).
extern const Fn_Table D_00249D80[6] = { 0, 0, 0, (Fn_Table)func_0013CCE8, 0, 0 };
extern const Fn_Table D_00249D98[6] = { 0, 0, 0, (Fn_Table)func_0013CC80, 0, 0 };

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

extern void func_0013C9B0(RingBuffer* ring);

void func_0013C988(RingBuffer* ring, s32 size, u8* buf) {
	ring->size = size;
	ring->buf = buf;
	ResetRingBuffer(ring);
}

void func_0013C9B0(RingBuffer* ring)
{
    ring->written = 0;
    ring->held = 0;
    ring->filled = 0;
    ring->readPos = 0;
    ring->writePos = 0;
    ring->space = ring->size;
}

s32 func_0013C9D0(RingBuffer* self, s32 n, MemoryReader* port)
{
    s32 total = 0;
    s32 rem = n;
    if (n <= 0 || self->space < n) {
        rem = self->space;
    }
    while (rem != 0) {
        s32 avail = self->size - self->writePos;
        s32 cnt = rem < avail ? rem : avail;
        s32 r = port->methods->read((MemoryReader*)((u8*)port + port->methods->adj1), cnt, self->buf + self->writePos);
        if (r == 0) {
            break;
        }
        total += r;
        rem -= r;
        self->writePos += r;
        self->writePos %= self->size;
        self->filled += r;
        self->space -= r;
        self->written += r;
        if (n <= 0) {
            break;
        }
    }
    return total;
}

s32 func_0013CAD8(RingBuffer* self, s32 n, StreamSink* o)
{
    s32 total = 0;
    s32 rem = n;
    if (rem <= 0 || self->filled < rem)
        rem = self->filled;
    for (;;) {
        if (rem == 0)
            break;
        s32 chunk = self->size - self->readPos;
        if (rem < chunk)
            chunk = rem;
        s32 s0 = o->methods->put((StreamSink*)((u8*)o + o->methods->adj1), chunk, self->buf + self->readPos);
        if (s0 == 0)
            break;
        self->readPos = (self->readPos += s0) % self->size;
        self->filled -= s0;
        if (o->methods->idle((StreamSink*)((u8*)o + o->methods->adj2)) != 0)
            self->held += s0;
        else
            self->space += s0;
        rem -= s0;
        total += s0;
        if (n <= 0)
            break;
    }
    return total;
}

s32 func_0013CC00(RingBuffer* self, void* a1, void* a2)
{
    if (a1 != 0) {
        MemoryReader arg;
        arg.methods = (const MemoryReaderMethods*)g_memoryReaderMethods;
        arg.base = (u8*)a2;
        arg.f10 = a1;
        arg.f08 = a1;
        arg.pos = 0;
        return FillRingBuffer(self, (s32)a1, &arg);
    }
    return 0;
}

void func_0013CC48(RingBuffer* p, s32 n)
{
    if (n == 0) {
        n = p->held;
        if (n == 0) {
            return;
        }
    }
    p->space += n;
    p->held -= n;
}

void func_001F5A58(void* dst, void* src, s32 n);

s32 func_0013CC80(MemoryReader* self, s32 want, void* dst)
{
    s32 n = self->remain;
    u8* base = self->base;
    s32 pos = self->pos;
    if (want < n) {
        n = want;
    }
    func_001F5A58(dst, base + pos, n);
    self->pos += n;
    self->remain -= n;
    return n;
}

int func_0013CCE8() {
	return 0;
}

LINKER_REMNANT(func_0013CCF0);
