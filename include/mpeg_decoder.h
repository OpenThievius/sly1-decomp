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

// A message the decoder passes to the callback of its kind (func_0020B190 runs it): the kind
// first, then whatever that kind carries; the kinds that carry nothing leave the rest unused.
struct MpegMessage {
    s32 kind;               // 0x00
    s32 pad04[7];           // 0x04
};

// A packet the demultiplexer hands to its stream's handler (src/lib/mpeg_demultiplexer.cpp): what
// kind of event it is, where the packet and its payload start in the ring buffer, the payload's
// size and the packet's two time stamps.
enum MpegStreamEvent { MPEG_STREAM_PACKET = 6 };

struct MpegStreamPacket {
    MpegStreamEvent kind;   // 0x00: always MPEG_STREAM_PACKET here
    u8* packet;             // 0x04
    u8* payload;            // 0x08
    s32 payloadSize;        // 0x0C
    u64 pts;                // 0x10
    u64 dts;                // 0x18
};

// A stream's handler: the handle, the packet and the argument registered with the handler.
typedef s32 (*MpegStreamFn)(MpegHandle*, MpegStreamPacket*, void*);

// One entry of the table the demultiplexer looks packets up in: the stream id, the mask of its
// significant bits, and the handler with its argument.
struct MpegStreamEntry {
    u64 id;                 // 0x00
    u64 mask;               // 0x08
    MpegStreamFn handler;   // 0x10
    void* arg;              // 0x14
};

// The two words the decoder keeps for one picture it outputs: its time stamps and the flags of
// its structure (func_00210160's FillPictureOutputInfo writes them).
struct MpegPictureInfo {
    s64 pts;                // 0x00
    s64 dts;                // 0x08
    s64 flags;              // 0x10
};

// What the library hands out: the decoder state at +0x40 and the information about the last
// pictures output.
struct MpegHandle {
    s32 pictureWidth;       // 0x00: the size the picture buffers were laid out for
    s32 pictureHeight;      // 0x04
    s32 pictureIndex;       // 0x08: the output picture's number, cleared by func_0020B0C0 (the reset)
    u8 pad0C[0x10 - 0x0C];
    MpegPictureInfo info[2];  // 0x10: the first picture (or field) and the second field
    MpegDecoder* decoder;   // 0x40
};

// A picture buffer of the decoder, in three views of each of its three frames (the frame, its
// top field, its bottom field): its address, its size in pixels and in macroblocks, its time
// stamps, whether it has been decoded, and the sequence's and picture's parameters that were in
// force when it was (func_002101F0, where SelectPictureBuffer fills them in).
struct MpegPicture {
    u32 address;            // 0x00
    s32 width;              // 0x04
    s32 height;             // 0x08
    s32 mbWidth;            // 0x0C
    s32 mbHeight;           // 0x10
    u8 pad14[0x18 - 0x14];
    s64 pts;                // 0x18
    s64 dts;                // 0x20
    s32 decoded;            // 0x28: cleared when the pictures are released (func_0020B110)
    s32 pictureType;        // 0x2C
    s32 pictureStructure;   // 0x30
    s32 progressiveSequence;  // 0x34
    s32 progressiveFrame;   // 0x38
    s32 topFieldFirst;      // 0x3C
    s32 repeatFirstField;   // 0x40
    s32 centreHorizontal[3];  // 0x44
    s32 centreVertical[3];  // 0x50
    s32 displayWidth;       // 0x5C
    s32 displayHeight;      // 0x60
    u8 pad64[0x68 - 0x64];
};

// A motion vector: its horizontal and vertical components, in half pixels.
struct MpegMotionVector {
    s32 x;                  // 0x00
    s32 y;                  // 0x04
};

// A block of the macroblock being decoded, which the prediction and the residual's addition work
// on: where it goes, its sub-position, the rows before and after the source block's edge, the
// source's row stride and its two source rows.
struct MpegBlockPart {
    u8* dst;                // 0x00
    s32 offset;             // 0x04
    s32 rows;               // 0x08
    s32 rest;               // 0x0C
    s32 stride;             // 0x10
    u8* src0;               // 0x14
    u8* src1;               // 0x18
};

typedef void (*MpegBlockFn)(MpegBlockPart*);

// One of the two macroblocks the decoder works on, one being predicted while the other has its
// residual added (the decoder's current one at +0x810): its two scratchpad buffers, the sources
// of its predictions, the routines that predict (and add) and their luma and chroma blocks, then
// the picture's address it goes to and the flags of what was decoded.
struct MpegMacroblock {
    u32 work;               // 0x000: the scratchpad buffer the predictions are fetched to
    u32 output;             // 0x004: the scratchpad buffer the IPU's output goes to
    u8* src0[4];            // 0x008: the source of each prediction's first transfer
    u8* src1[4];            // 0x018: and of its second
    MpegBlockFn luma[4];    // 0x028
    MpegBlockFn chroma[4];  // 0x038
    MpegBlockPart lumaPart[4];  // 0x048
    MpegBlockPart chromaPart[4];  // 0x0B8
    s32 destination;        // 0x128: where the macroblock goes in the picture
    s32 count;              // 0x12C: the predictions
    s32 intra;              // 0x130
    s32 f134;               // 0x134
    s32 coded;              // 0x138
    s32 skipped;            // 0x13C
};

// The state of one decoder: the sequence and picture headers it has read, its pictures, and the
// IPU's registers as it last left them.
struct MpegDecoder {
    s32 ended;              // 0x000: the sequence's end code was read
    s32 pending;            // 0x004: pictures decoded and not yet output
    s32 phase;              // 0x008: 0 before the first picture, 1 once one is decoded, 2 once one is output
    MpegCallback callbacks[7];  // 0x00C: the table func_0020B168 fills in and func_0020B190 runs
    MpegStreamEntry* streamTable;  // 0x044: the demultiplexer's table (0x40 entries)
    s32 streamCount;        // 0x048
    IpuDmaState dmaState;   // 0x04C: saved and restored around the IPU's use (func_0020C178, func_0020C188)
    s32 f70;                // 0x070
    u8 pad74[0x078 - 0x074];
    s64 f78;                // 0x078
    s32 f80;                // 0x080
    u8 pad84[0x088 - 0x084];
    s64 f88;                // 0x088
    s32 f90;                // 0x090
    s32 pictureLimit[3];    // 0x094: how many frames, top fields and bottom fields to decode (-1: all)
    s32 pictureCount[3];    // 0x0A0: how many of each have been decoded
    s32 firstPictureNumber; // 0x0AC
    s32 convertColours;     // 0x0B0: set by func_0020B058 before it runs the picture loop
    s32 outputCentreHorizontal[3];  // 0x0B4: the output picture's display extension
    s32 outputCentreVertical[3];  // 0x0C0
    s32 outputDisplayWidth; // 0x0CC
    s32 outputDisplayHeight;  // 0x0D0
    s32 firstStructure;     // 0x0D4: the first picture's structure
    u32 outputBuffer;       // 0x0D8: where the picture is written (func_0020B058 sets it)
    s32 outputWidth;        // 0x0DC
    s32 outputHeight;       // 0x0E0
    s32 outputMacroblocks;  // 0x0E4
    s32 fE8;                // 0x0E8
    u8 padEC[0x0F0 - 0x0EC];
    s64 fF0;                // 0x0F0
    s32 fF8;                // 0x0F8
    u32 frameBuffer[3];     // 0x0FC: the three frames' addresses
    MpegRing ring;          // 0x108
    s32 pictureNumber;      // 0x118
    s32 errored;            // 0x11C
    s32 secondField;        // 0x120: a first field was decoded and its second has not been
    s32 width;              // 0x124
    s32 height;             // 0x128
    s32 mbWidth;            // 0x12C
    s32 mbHeight;           // 0x130
    u32 bitRate;            // 0x134
    u32 vbvBufferSize;      // 0x138
    s32 progressiveSequence;  // 0x13C
    s32 chromaFormat;       // 0x140
    s32 f144;               // 0x144
    s32 displayWidth;       // 0x148
    s32 displayHeight;      // 0x14C
    s32 pictureType;        // 0x150: 1 intra, 2 predicted, 3 bidirectional
    s32 fullPelForward;     // 0x154
    s32 forwardFCode;       // 0x158
    s32 fullPelBackward;    // 0x15C
    s32 backwardFCode;      // 0x160
    s32 fCode[4];           // 0x164
    s32 pictureStructure;   // 0x174: 1 top field, 2 bottom field, 3 frame
    s32 topFieldFirst;      // 0x178
    s32 framePredFrameDct;  // 0x17C
    s32 concealmentMotionVectors;  // 0x180
    s32 repeatFirstField;   // 0x184
    s32 progressiveFrame;   // 0x188
    s32 centreHorizontal[3];  // 0x18C: the picture display extension's offsets (func_0020FF08)
    s32 centreVertical[3];  // 0x198
    s32 closedGop;          // 0x1A4
    s32 brokenLink;         // 0x1A8
    s32 pictureOrder;       // 0x1AC
    s32 dcReset;            // 0x1B0
    s32 quantiserScale;     // 0x1B4
    MpegPicture* pictures[12];  // 0x1B8
    MpegPicture views[9];   // 0x1E8
    MpegMacroblock macroblock[2];  // 0x590
    s32 currentMacroblock;  // 0x810
    s32 f814;               // 0x814
    u32 windowInvalid;      // 0x818: the IPU's setting, as func_0020F0C0 last wrote it
    u32 scratchDestination; // 0x81C: the scratchpad buffer the macroblock is assembled in
    s32 pictureReady;       // 0x820
    u8 pad824[0x828 - 0x824];
    s64 pts;                // 0x828: the picture's time stamps, as the callback of kind 5 gave them (-1: none)
    s64 dts;                // 0x830
    s32 window;             // 0x838
    s32 windowBits;         // 0x83C
    s32 loadIntraMatrix;    // 0x840
    s32 loadNonIntraMatrix; // 0x844
    s32 mpeg2;              // 0x848
    s32 orderBase;          // 0x84C: the first picture order of the group of pictures
    s32 maxOrder;           // 0x850: the highest picture order so far
    s32 gopStart;           // 0x854: set by a group of pictures header, cleared by the first picture after it
    MpegHandle* handle;     // 0x858: the handle the decoder belongs to
};

typedef char check_MpegPicture[sizeof(MpegPicture) == 0x68 ? 1 : -1];
typedef char check_MpegBlockPart[sizeof(MpegBlockPart) == 0x1C ? 1 : -1];
typedef char check_MpegMacroblock[sizeof(MpegMacroblock) == 0x140 ? 1 : -1];
typedef char check_MpegHandle[sizeof(MpegHandle) == 0x48 ? 1 : -1];
typedef char check_MpegDecoder[sizeof(MpegDecoder) == 0x860 ? 1 : -1];

#endif
