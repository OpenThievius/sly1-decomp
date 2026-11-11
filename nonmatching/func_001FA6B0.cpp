// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 252/296 (85.1%), checked 2026-11-11
#include "common.h"
#include "system.h"
// w23-vuE (2026-11-11): 296 bytes, retail's size, with the registers still differing (97% by regdiff, 72 of 74 insns equal by
// shape). Retail reads the command word at 8(sp) at each use (`lw v1,8(sp); bgez`, then `lw v0,8(sp)` in the system arm and
// `lw a1,8(sp)` in the user arm, and reorg leaves the user arm's first load out of the bgez slot): the reads of the copied
// packet are volatile. With `volatile Packet* packet` the whole dispatch is retail's; without it CSE merges the three reads.
// The loop as pointers (`*dst++ = *src++`, the source copied from the buffer pointer before the sb, as retail's move a2,a3)
// gives retail's head order. Left: retail's count guard is blez (n not known non-negative to combine; a variable set twice
// loses it: `size = (size + 15) / 16` gives blez but the loop then counts with size itself, retail copies the count: move a0,a1),
// and the registers (retail n = a1 = size's register, counter a0, src a2, buffer a3). Needs a ruling on volatile for the packet:
// it is an interrupt handler's own copy, but retail's reads are volatile.
// NEAR (2026-11-08, worker night-mmi): the receive buffer read as volatile gives retail's
// lbu and andi; still different: retail keeps the packet count's guard as blez (ours beqz: the
// compiler here knows the count is not negative), copies the buffer pointer for the copy loop,
// and reads the command word at 8(sp) twice (once for its sign, once for the index) where ours
// reads it once; the registers of the dispatch follow.

struct Packet_1FA068 {
    s32 head[4];
    s32 index;
    s32 value;
};

struct Channel_1FA068;
typedef void (*Handler_1FA068)(Packet_1FA068* packet, Channel_1FA068* channel);

struct Slot_1FA068 {
    Handler_1FA068 handler;
    void* arg;
};

// The channel's control record: the receive buffers' uncached addresses, the IOP's address, the
// system and user handler tables, the table of words, and two words no code reads (its label
// is 0x28 bytes).
struct Channel_1FA068 {
    u32 buffer;
    u32 buffer2;
    s32 iop;
    Slot_1FA068* system;
    s32 system_count;
    Slot_1FA068* user;
    s32 user_count;
    s32* words;
    s32 f20;
    s32 f24;
};

extern Channel_1FA068 D_00629398;
s32 EnableInterrupts(void);

void ArmIopDmaChainFromInterrupt(void);

// A quadword, moved with lq and sq.
typedef unsigned int Quad_1FA6B0 __attribute__((mode(TI)));


// The DMA interrupt handler of the command channel: with interrupts enabled again, takes the
// packet from the receive buffer (the low byte of its first word is its size; zero when none
// came), frees the buffer, re-arms the DMA chain and runs the handler of the packet's command,
// a system command (the top bit set) or a user one, then ends the handler.
s32 HandleCommandInterrupt(s32 cause)
{
    Quad_1FA6B0 local[7];
    EnableInterrupts();
    Channel_1FA068* ch = &D_00629398;
    volatile u8* buffer = (volatile u8*)ch->buffer;
    u8 size = buffer[0];
    if (size == 0) {
        return 0;
    }
    s32 n = (size + 15) / 16;
    Quad_1FA6B0* src = (Quad_1FA6B0*)buffer;
    buffer[0] = 0;
    Quad_1FA6B0* dst = local;
    for (s32 i = 0; i < n; i++, dst++, src++) {
        *dst = *src;
    }
    ArmIopDmaChainFromInterrupt();
    volatile Packet_1FA068* packet = (volatile Packet_1FA068*)local;
    if (packet->head[2] < 0) {
        s32 index = packet->head[2] & 0x7FFFFFFF;
        if (index < ch->system_count) {
            Slot_1FA068* slot = &ch->system[index];
            if (slot->handler != 0) {
                slot->handler((Packet_1FA068*)packet, (Channel_1FA068*)slot->arg);
            }
        }
    } else {
        s32 index = packet->head[2];
        if (index < ch->user_count) {
            Slot_1FA068* slot = &ch->user[index];
            if (slot->handler != 0) {
                slot->handler((Packet_1FA068*)packet, (Channel_1FA068*)slot->arg);
            }
        }
    }
    SyncAndEnableInterrupts();
    return 0;
}
