// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "memory_reader.h"
#include "stream_sink.h"
#include "ring_buffer.h"
#include "functions/ring_buffer.h"

// An entry of the file's two GCC vtables, written out as tables of functions.
typedef void (*Fn_Table)();

// The file's .rodata, in retail's order: the vtable of the reader's base (its one virtual,
// func_0013CCE8, returns 0; nothing builds that class) and the memory reader's (D_00249D98).
extern const Fn_Table g_baseReaderMethods[6] = { 0, 0, 0, (Fn_Table)ReadNothing, 0, 0 };
extern const Fn_Table g_memoryReaderMethods[6] = { 0, 0, 0, (Fn_Table)ReadMemoryReader, 0, 0 };


// Sets the ring's size and buffer and resets it.
void InitRingBuffer(RingBuffer* ring, s32 size, u8* buf) {
	ring->size = size;
	ring->buf = buf;
	ResetRingBuffer(ring);
}

// Empties the ring: all its space free and its positions at 0.
void ResetRingBuffer(RingBuffer* ring)
{
    ring->written = 0;
    ring->held = 0;
    ring->filled = 0;
    ring->readPos = 0;
    ring->writePos = 0;
    ring->space = ring->size;
}

// Reads up to n bytes (all of the free space where n is not positive or exceeds it) from the reader
// port into the ring buffer, one contiguous run at a time up to the wrap point. Advances writePos
// and the filled/written/space counters; gives back the bytes read. A non-positive n makes it do a
// single pass.
s32 FillRingBuffer(RingBuffer* self, s32 n, MemoryReader* port)
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

// Moves up to n bytes (all of the filled bytes where n is not positive or exceeds them) from the
// ring buffer into the sink o, one contiguous run at a time up to the wrap point. Advances readPos
// and updates the held/space counters by whether the sink reports itself idle; gives back the bytes
// moved. A non-positive n makes it do a single pass.
s32 DrainRingBuffer(RingBuffer* self, s32 n, TransferSink* o)
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
        s32 s0 = o->Put(chunk, self->buf + self->readPos);
        if (s0 == 0)
            break;
        self->readPos = (self->readPos += s0) % self->size;
        self->filled -= s0;
        if (o->Idle() != 0)
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

// Puts count bytes from memory into the ring buffer, through a memory reader; gives back the
// number taken, 0 for count 0.
s32 FillRingBufferFromMemory(RingBuffer* self, s32 count, void* src)
{
    if (count != 0) {
        MemoryReader arg;
        arg.methods = (const MemoryReaderMethods*)g_memoryReaderMethods;
        arg.base = (u8*)src;
        arg.remain = count;
        arg.size = count;
        arg.pos = 0;
        return FillRingBuffer(self, count, &arg);
    }
    return 0;
}

// Releases n held bytes (all of them for 0) back as free space.
void ConsumeSpan(RingBuffer* p, s32 n)
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

extern "C" void* CopyBytes(void* dst, const void* src, s32 n);

// Reads up to want bytes from the memory reader into dst, advances it and gives back the count
// read.
s32 ReadMemoryReader(MemoryReader* self, s32 want, void* dst)
{
    s32 n = self->remain;
    u8* base = self->base;
    s32 pos = self->pos;
    if (want < n) {
        n = want;
    }
    CopyBytes(dst, base + pos, n);
    self->pos += n;
    self->remain -= n;
    return n;
}

// A reader that gives back no data: always 0.
int ReadNothing() {
	return 0;
}

LINKER_REMNANT(func_0013CCF0);
