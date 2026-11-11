// SPDX-License-Identifier: AGPL-3.0-or-later
// The MPEG library's decoder (src/lib/mpeg_decoder.cpp, mpeg_ipu_decode.cpp): the handle the
// game's code calls it by, and the decoder state that handle keeps at +0x40. The fields are the
// ones the library's functions read; the state's first words are also the table of callbacks
// (func_0020B168 sets one, func_0020B190 runs one), and its last pointer leads back to the
// handle. Written for this project from what retail's code does.
#ifndef MPEG_DECODER_H
#define MPEG_DECODER_H

#include "common.h"

struct MpegHandle;
struct MpegDecoder;

// The IPU and its DMA channels as func_002118A0 saves them (and func_00211988 restores them): the
// input channel's address, tag address, quadword count and control, the output channel's
// address, count and control, then the IPU's bit position and control registers.
struct IpuDmaState {
    u32 inAddress;          // 0x00
    u32 inTagAddress;       // 0x04
    u32 inCount;            // 0x08
    u32 inControl;          // 0x0C
    u32 outAddress;         // 0x10
    u32 outCount;           // 0x14
    u32 outControl;         // 0x18
    u32 bitPosition;        // 0x1C
    u32 control;            // 0x20
};

// The ring the decoder allocates its work memory from: the area, how big it is, where the next
// allocation starts and the mark func_0020B258 sets and func_0020B268 returns to.
struct MpegRing {
    u32 start;              // 0x00
    u32 size;               // 0x04
    u32 cursor;             // 0x08
    u32 mark;               // 0x0C
};

// A callback of the decoder's table: func_0020B190 runs the one at an index with its argument.
typedef s32 (*MpegCallbackFn)(MpegHandle*, s32*, s32);
struct MpegCallback {
    MpegCallbackFn fn;      // 0x00
    s32 arg;                // 0x04
};

// What the library hands out: the decoder state at +0x40 and an output word at +0x08.
struct MpegHandle {
    u8 pad00[0x08];
    s32 f08;                // 0x08: cleared by func_0020B0C0 (the reset)
    u8 pad0C[0x40 - 0x0C];
    MpegDecoder* decoder;   // 0x40
};

// A picture buffer of the decoder (six of them, in pairs, among the twelve slots from 0x1B8): its
// use flag at 0x28 is cleared when the pictures are released (func_0020B110), and the rest is
// what the picture decoder fills in (func_002101F0).
struct MpegPicture {
    u8 pad00[0x18];
    u64 f18;                // 0x18
    u64 f20;                // 0x20
    s32 f28;                // 0x28
    s32 f2C;                // 0x2C
    s32 f30;                // 0x30
    s32 f34;                // 0x34
    s32 f38;                // 0x38
    s32 f3C;                // 0x3C
    s32 f40;                // 0x40
    s32 f44;                // 0x44
    s32 f48;                // 0x48
    s32 f4C;                // 0x4C
    s32 f50;                // 0x50
    s32 f54;                // 0x54
    s32 f58;                // 0x58
    s32 f5C;                // 0x5C
    s32 f60;                // 0x60
};

// What the macroblock predictor keeps for one block: its output address and its count, in a
// record of 0x140 bytes (func_0020C1A0, func_0020C3F0).
struct MpegBlockChannel {
    s32 f00;                // 0x00
    s32 f04;                // 0x04
    u8 pad08[0x140 - 0x08];
};

// The state of one decoder: the sequence and picture headers it has read, its pictures, and the
// IPU's registers as it last left them.
struct MpegDecoder {
    s32 f00;               // 0x000
    s32 f04;               // 0x004
    s32 f08;               // 0x008
    MpegCallback callbacks[8];  // 0x00C: the table func_0020B168 fills in and func_0020B190 runs
    IpuDmaState dmaState;   // 0x04C: saved and restored around the IPU's use (func_0020C178, func_0020C188)
    s32 f70;               // 0x070
    u8 pad74[0x078 - 0x074];
    s64 f78;               // 0x078
    s32 f80;               // 0x080
    u8 pad84[0x088 - 0x084];
    s64 f88;               // 0x088
    s32 f90;               // 0x090
    u8 pad94[0x0A0 - 0x094];
    s32 fA0;               // 0x0A0
    s32 fA4;               // 0x0A4
    u8 padA8[0x0AC - 0x0A8];
    s32 fAC;               // 0x0AC
    s32 fB0;               // 0x0B0: set by func_0020B058 before it runs the picture loop
    u8 padB4[0x0D4 - 0x0B4];
    s32 fD4;               // 0x0D4
    u32 fD8;               // 0x0D8: the picture's start code word (func_0020B058 sets it)
    s32 fDC;               // 0x0DC
    s32 fE0;               // 0x0E0
    s32 fE4;               // 0x0E4
    s32 fE8;               // 0x0E8
    u8 padEC[0x0F0 - 0x0EC];
    s64 fF0;               // 0x0F0
    s32 fF8;               // 0x0F8
    u8 padFC[0x118 - 0x0FC];
    s32 f118;               // 0x118
    s32 f11C;               // 0x11C
    s32 f120;               // 0x120
    u32 f124;               // 0x124
    u32 f128;               // 0x128
    u8 pad12C[0x134 - 0x12C];
    u32 f134;               // 0x134
    u32 f138;               // 0x138
    u32 f13C;               // 0x13C
    u32 f140;               // 0x140
    u8 pad144[0x148 - 0x144];
    s32 f148;               // 0x148
    s32 f14C;               // 0x14C
    s32 f150;               // 0x150
    s32 f154;               // 0x154
    s32 f158;               // 0x158
    s32 f15C;               // 0x15C
    s32 f160;               // 0x160
    u8 pad164[0x174 - 0x164];
    s32 f174;               // 0x174
    s32 f178;               // 0x178
    u8 pad17C[0x184 - 0x17C];
    s32 f184;               // 0x184
    s32 f188;               // 0x188
    s32 centreHorizontal[3];  // 0x18C: the picture display extension's offsets (func_0020FF08)
    s32 centreVertical[3];  // 0x198
    s32 f1A4;               // 0x1A4
    s32 f1A8;               // 0x1A8
    s32 f1AC;               // 0x1AC
    u8 pad1B0[0x1B4 - 0x1B0];
    s32 f1B4;               // 0x1B4
    MpegPicture* pictures[12];  // 0x1B8
    u8 pad1E8[0x6B8 - 0x1E8];
    MpegBlockChannel channel[1];  // 0x6B8
    u8 pad7F8[0x810 - 0x7F8];
    s32 f810;               // 0x810: the channel func_0020C3F0 writes to
    u8 pad814[0x818 - 0x814];
    u32 f818;               // 0x818: the IPU's setting, as func_0020F0C0 last wrote it
    u8 pad81C[0x828 - 0x81C];
    u64 f828;               // 0x828
    u64 f830;               // 0x830
    s32 f838;               // 0x838
    s32 f83C;               // 0x83C
    s32 f840;               // 0x840
    s32 f844;               // 0x844
    u32 f848;               // 0x848
    s32 f84C;               // 0x84C
    s32 f850;               // 0x850
    s32 f854;               // 0x854
    MpegHandle* handle;     // 0x858: the handle the decoder belongs to
};

typedef char check_MpegHandle[sizeof(MpegHandle) == 0x44 ? 1 : -1];
typedef char check_MpegDecoder[sizeof(MpegDecoder) == 0x860 ? 1 : -1];

#endif
