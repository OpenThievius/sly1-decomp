// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 482/492 (98.0%), checked 2026-11-07
// NEAR: in its file, src/lib/remote_call.cpp (Sony's 2.9-ee-991111). Left: retail loads the
//       packet's id first and stores the client's fields in the order argument, packet, id,
//       callback, and tests mode & 2 into $a0; ours stores the callback before loading the id,
//       and the test lands in $v1. Tried: every order of the client's four stores and of the
//       packet's last three, the callback argument as void* (worse), the tails rearranged until
//       retail's branches matched.
#include "common.h"

struct Client_1F7BE8;

// A packet of the command channel: the channel's header, then the request.
struct Packet_1F7BE8 {
    u32 head[4];
    u32 flags;
    u32 self;
    s32 id;
    u32 client;
    u32 cmd;
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
};

typedef void (*Callback_1F7BE8)(s32 arg);

// What a caller opens: its packet, the packet's id, the semaphore it waits on, the results.
struct Client_1F7BE8 {
    Packet_1F7BE8* packet;
    s32 id;
    s32 sema;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    Callback_1F7BE8 callback;
    s32 callback_arg;
    s32 f24;
};

// An IOP-side list the command 0x80000009 searches: groups of entries, each entry keyed by its
// first word.
struct Entry_1F7FC0 {
    u32 key;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    u8 f18[0x20];
    Entry_1F7FC0* next;
};

struct Group_1F7FC0 {
    s32 f0;
    s32 f4;
    Entry_1F7FC0* entries;
    s32 fC;
    s32 f10;
    Group_1F7FC0* next;
};

// The client's state: the next packet id, the pool of request packets, the reply ring.
struct Pools_1F7BE8 {
    s32 next_id;
    Packet_1F7BE8* packets;
    s32 packet_count;
    s32 fC;
    s32 f10;
    Packet_1F7BE8* replies;
    s32 reply_count;
    Packet_1F7BE8* f1C;
    s32 f20;
    s32 cursor;
    Group_1F7FC0* groups;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
};

// The kernel's semaphore parameters (func_001F6B20 creates one).
struct SemaParams_1F80C0 {
    s32 count;
    s32 max_count;
    s32 init_count;
    s32 wait_threads;
    u32 attr;
    u32 option;
};

extern Pools_1F7BE8 g_remoteCallState;

Packet_1F7BE8* TakeRequestPacket(Pools_1F7BE8* self);
void FreeRequestPacket(Packet_1F7BE8* packet);
s32 NewSemaphore(SemaParams_1F80C0* params);
void FreeSemaphore(s32 sema);
s32 AwaitSemaphore(s32 sema);
s32 SendCommand(u32 cmd, void* data, s32 size, s32 a3, s32 a4, s32 a5);

void WriteBackDataCacheRange(void* data, s32 size);

s32 CallRemoteService(Client_1F7BE8* self, u32 cmd, u32 mode, void* send, s32 send_size, void* recv, s32 recv_size, Callback_1F7BE8 callback, s32 callback_arg)
{
    SemaParams_1F80C0 params;
    Packet_1F7BE8* packet;
    s32 sema;

    packet = TakeRequestPacket(&g_remoteCallState);
    if (packet == 0) return -1;
    self->callback_arg = callback_arg;
    self->id = packet->id;
    self->callback = callback;
    self->packet = packet;
    packet->cmd = cmd;
    packet->f24 = send_size;
    packet->f28 = (s32)recv;
    packet->f2C = recv_size;
    packet->self = (u32)packet;
    packet->f34 = self->f24;
    packet->client = (u32)self;
    if ((mode & 2) == 0) {
        if (send == recv) {
            WriteBackDataCacheRange(send, send_size < recv_size ? recv_size : send_size);
        } else {
            if (send_size > 0) WriteBackDataCacheRange(send, send_size);
            if (recv_size > 0) WriteBackDataCacheRange(recv, recv_size);
        }
    }
    if (mode & 1) {
        if (callback == 0) {
            packet->f30 = 0;
        } else {
            packet->f30 = 1;
        }
        self->sema = -1;
        if (SendCommand(0x8000000A, packet, 0x40, (s32)send, self->f14, send_size) != 0) {
            return 0;
        }
        FreeRequestPacket(packet);
        return -2;
    }
    params.init_count = 0;
    params.max_count = 1;
    sema = NewSemaphore(&params);
    self->sema = sema;
    if (sema < 0) {
        FreeRequestPacket(packet);
        return -3;
    }
    packet->f30 = 1;
    if (SendCommand(0x8000000A, packet, 0x40, (s32)send, self->f14, send_size) == 0) {
        FreeSemaphore(self->sema);
        FreeRequestPacket(packet);
        return -2;
    }
    AwaitSemaphore(self->sema);
    FreeSemaphore(self->sema);
    return 0;
}
