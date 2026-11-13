// SPDX-License-Identifier: AGPL-3.0-or-later
// The packet writer (PacketWriter), the display-list writer (a C++ object with one virtual, vptr at +0x18), two GCC
// vtables: D_0024A0E0 (the base: func_00152888 and func_001EE318 store it) and D_0024A6F8 (the
// writer func_001611B8 makes). Written for this project from what retail's code does
// (config/us/tables.tsv, kinds.tsv).
//
// A plain struct with an explicit vptr: the entries are GCC 2.95's {s16 delta; s16 index; fn},
// entry 0 being {offset-to-top, rtti} = {0, 0, 0}, so the one virtual is entry 1, called as
// `vt->close.fn((u8*)self + vt->adj1, flag)`. No `virtual`, so GCC emits no vtable of its own
// (the tables are defined in pooled_object.cpp and game_progress.cpp).
//
// The writer appends 64-bit words at `cur`; a packet starts with a header word whose count
// func_00161278 patches when the packet is closed.
#ifndef PACKET_WRITER_H
#define PACKET_WRITER_H

#include "common.h"

struct PacketWriter;

struct PacketWriterVt {
    s16 adj0; s16 idx0; void* fn0;                                              // 0x00
    s16 adj1; s16 idx1; void (*close)(PacketWriter* self, s32 flag);                   // 0x08
};

// Two of these sit on a caller's stack as 0x30 bytes (Pkt_152E48 in func_00152E48, Frame_15D998 in
// func_0015D998), so the object is 0x30 bytes with the last 8 unused.
struct PacketWriter {
    u8* end;                // 0x00: end of the buffer (func_001529C8 sets begin and cur to its base)
    u8* begin;              // 0x04: start of the buffer
    s32* f08;               // 0x08: the open packet's header word (func_00152D70)
    union {
        u8* cur;            // 0x0C: where the next word goes
        u64* cur64;
        u32 curU;           // (func_00161278 pads it as an address)
        s32 curS;           // (func_00152D70)
    };
    s32 f10;                // 0x10: nonzero: closing pads `cur` to 16 bytes (func_00152D70)
    s32 f14;                // 0x14: nonzero (set by func_001611B8): closing calls the virtual (func_00152D70)
    const PacketWriterVt* vt;     // 0x18
    union {
        u32* f1C;           // 0x1C: the open packet's header word (func_00161278)
        u8* block;          // (func_001613C0)
        u64* last;          // (func_00161768)
        s32 mask;           // the VIF writer (D_0024A0E0): the mask func_001EE528 set, which func_001EE560 marks its unpacks with
    };
    u32 f20;                // 0x20: the packet's element count (func_00161278's divisor)
    u32 f24;                // 0x24: the words written
    u8 pad28[8];            // 0x28

    // The one virtual, through its table's entry 1 (func_00161958 calls it with 0).
    void Close(s32 flag) { vt->close((PacketWriter*)((u8*)this + vt->adj1), flag); }
};

typedef char check_PacketWriter[sizeof(PacketWriter) == 0x30 ? 1 : -1];

#endif
