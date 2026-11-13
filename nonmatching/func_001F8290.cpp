// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 488/492 (99.2%), checked 2026-11-12
// NEAR: in its file, src/lib/remote_call.cpp (Sony's 2.9-ee-991111). Left: only the packet's
//       and the id's stores are swapped (retail: argument, packet, id, callback); every register
//       and every other instruction is retail's. The client's packet and callback words are
//       u32 here, as the packet's own self and client words are: as pointer types (their own
//       alias classes) neither store depends on the packet's int stores, so both fall to priority
//       2 and come out after them. The id is read into a local first, so its load passes the
//       argument's store (sched2 issues it while the argument's load is in flight).
// Mechanism (2026-11-09, docs/TOOLCHAIN.md, "sched1's weight puts a dying value's store
//       first"): sched1 issues the id's load at t=1 (priority 9) and its store is ready at t=3;
//       there it beats the packet's store on INSN_REG_WEIGHT (0, its value dies, against +1),
//       and the argument's store (weight 0 too) has taken t=2. sched2 then keeps id before
//       packet on LUID. Proved by experiment: one more later use of the id
//       (`packet->f38 = id;` after the packet's stores) makes the id's store weigh +1, and the
//       client's four stores and all their registers come out exactly as retail's. So in the
//       original the id's value outlives its store in sched1 (or a barrier separates the
//       packet's store from the id's), and retail's final code shows no such use: it is an
//       insn deleted after sched1 (a move reload drops, a set flow2 deletes) or something not
//       yet identified. Swept: the client's packet, callback and argument words as int, their
//       pointer type or void*, the id read in place or into a local, all 24 store orders
//       (864 compiles): nothing under these 8 bytes; -O3, -fno-gcse, -fno-strict-aliasing,
//       -fno-sched-interblock, -fno-regmove, -fno-rerun-cse-after-loop change nothing or worse.
// 2026-11-10 (docs/toolchain/alias-classes.md, "What retail's order needs, and a lever that
//       proves it"): sched2 picks the argument's store first by its dependents ($v0 is loaded
//       again for the server word), so sched1 only has to issue packet before id before
//       callback. Written through volatile lvalues (argument, packet and id or callback, with
//       the callback an int word) the function is EXACT: an ordering edge between the client's
//       stores is all that is missing. Not landable: a volatile client breaks
//       HandleRemoteCallReply, whose delay slots hold the callback's argument and the packet,
//       which a volatile reference never fills. A nested header struct for the first four
//       words, and a loop note around the id's store, do not help.
// w37-f1 (2026-11-12): re-scored, unchanged. Two facts for the next attempt. (1) This near miss
// cannot land as it is: include/remote_call_client.h, which BindRemoteService and
// HandleRemoteCallReply match with, has the packet as a RemoteCallPacket* and the callback as
// a function pointer. Written with those types in src/lib/remote_call.cpp (stores in member
// order: packet, id, callback, argument) the size is retail's and 11 lines differ: the packet's
// and the callback's stores fall behind the packet's int stores (priority 2), as the first line
// above says. (2) With this file's u32 words and the stores in member order (`self->packet`
// before `self->id = packet->id`), sched1 gives retail's relative order (packet, argument, id,
// callback) but the int load now waits for the packet's store, sched2 issues that store first
// and reorg takes it into the entry test's delay slot (`bnezl s0; sw s0,0(s1)`, 496 bytes). So
// retail's packet store is int-class for the later stores yet does not hold the id's load:
// the load's LUID is before it, and the wall is the id store's weight, as recorded. No source
// form found for an id that outlives its store; not searched: the client's words read through
// a second type (a union or a cast at the store) in this function only.
// w38-f6 (2026-11-12): not closer (2 words). With the header's types, each store's class set
// by a cast at the store: 10,368 forms (the 24 orders of the client's four stores, the id read
// in place or into a local first, the client's packet word as its pointer or void*, the
// callback as its type or void*, the packet's f28, self, f34 and client words as int, their
// pointer type or void*): 5 words at best (callback or packet written before the argument and
// the id read in place), never the near miss's 2. Why, from the near miss's own -dR trace
// (block 2): sched2 issues the argument's load and the andi at t=1, the id's load at t=2, the
// argument's store at t=3 (nine dependents: the server word's `lw v0` too), and at t=4 the
// packet's, the id's and the callback's stores are all ready with priority 7 and eight
// dependents each, so the LUID decides. A pointer-class store has no dependent (priority 2):
// it is issued only in a cycle with nothing else ready, and the id's store is ready at t=4
// and the command word's at t=6. So retail's packet and callback stores each have a
// dependence into the packet's stores, which the header's types cannot give them, and with
// one the weight wall above is what is left. BindRemoteService does not decide the types
// either way: with the packet word a u32 and member order it is 324 bytes (the store ahead
// of the id's load, taken into the entry test's slot), with the pointer type the store is a
// filler between the id's load and store. Not tried: a second use of the id or the argument
// that a pass after sched1 deletes; `packet->id = id` written back stays in the code (496
// bytes) and a second `self->id = id` is gone before sched1 (cse1), changing nothing.
// w40-fa (2026-11-12): not closer (2 words). A third way to retail's order, replayed by hand
// on the near miss's table and not yet seen in a compile: the id's load one cycle late. If the
// load (priority 9) cannot issue at t=1, the argument's store takes t=1 (weight 0), the load
// t=2, the packet's store t=3 (the id's store is ready at t=4 only), then id, callback:
// retail's order with the weights as they are, and the argument still dies right before the
// id is born (v0, v1). It needs an insn of no code, issued at t=1, that the load depends on
// with a cost of one. Tried: (1) a `(clobber (reg))` from the id read through a union-typed
// local (`IdWord id = { packet->id };`): the constructor loads into a temporary and copies,
// cse1 makes the temporary canonical, the copy and then the CLOBBER are deleted by flow before
// sched1 (2 words, unchanged). (2) The packet as a checked pointer copied into the variable
// (`void* p = Take(); if (p == 0) return -1; packet = (Packet*)p;`): cse1 folds the copy the
// same way (written in member order the store lands in the entry test's slot, 496 bytes).
// (3) The stack argument's variable reused for the id (`self->callback_arg = callback_arg;
// callback_arg = packet->id; self->id = callback_arg;`, the load anti-dependent on the
// store): set twice, the variable is global-alloc's, takes a saved register across the first
// call and pushes mode to the stack (125 lines). Not tried: the file built as C (a C record
// constructor that lists every field emits a CLOBBER, a C++ one never does).
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
    u32 packet;
    s32 id;
    s32 sema;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    u32 callback;
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
    s32 id = packet->id;
    self->callback_arg = callback_arg;
    self->packet = (u32)packet;
    self->id = id;
    self->callback = (u32)callback;
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
