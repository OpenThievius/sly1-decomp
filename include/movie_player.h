// SPDX-License-Identifier: AGPL-3.0-or-later
// The movie player (D_00269A00): the stream its data comes through, the two sinks a transfer
// goes to (a ring buffer in the IOP, and the IPU's DMA channel) and the player itself.
// src/main/movie_player.cpp defines the sinks' methods and the player; main_loop.cpp reads
// whether movies are queued. Written for this project from what retail's code does.
//
// TransferSink and its two classes have real virtual functions: their vtables and methods are
// compiler-generated in movie_player.cpp (config/us/generated.tsv), so their names stay.
#ifndef MOVIE_PLAYER_H
#define MOVIE_PLAYER_H

#include "common.h"
#include "ring_buffer.h"

struct IdentityKey;
struct StreamReaderWindow;

// Where a transfer's data goes: two virtual methods, which retail's vtables list in this order.
class TransferSink {
public:
    virtual s32 Put(s32 size, u8* buf) = 0;
    virtual s32 Idle() = 0;
};

// A ring buffer in the IOP's memory, read through the SIF.
class IopRingSink : public TransferSink {
public:
    s32 iopBase;
    s32 capacity;
    s32 writePosition;
    s32 readPosition;
    s32 freeBytes;
    s32 usedBytes;
    s32 totalWritten;
    s32 Put(s32 size, u8* buf);
    s32 Idle();
};

// The IPU's input DMA channel.
class IpuDmaSink : public TransferSink {
public:
    s32 Put(s32 size, u8* buf);
    s32 Idle();
};

// The stream the movie's data comes through (StartMovieStream, func_0018E940, opens it): its
// first 0x28 bytes come through the header ring, the rest through the data ring, which drains
// into the IOP's ring.
struct MovieStream {
    s32 state;              // 0x00: 0 closed, 1 reading the header, 2 filling, 3 playing
#ifdef VERSION_EU
    s32 streamId;           // 0x04: PAL only: the stream id the data must carry (-1 until known)
#endif
    u8 header[0x28];        // 0x04: the header ring's memory
    RingBuffer headerRing;  // 0x2C
    RingBuffer dataRing;    // 0x4C
    IopRingSink sink;       // 0x6C: where the data ring drains
    s32 savedVolume2;       // 0x8C: IOP volume channel 2 before the movie
    s32 savedVolume8;       // 0x90: IOP volume channel 8 before the movie
};

// The MPEG decoder's state (CreateMpegDecoder sets it up); the player reads the picture's size.
struct MovieDecoder {
    s32 width;              // 0x00: the picture's width (UploadMovieFrame, DrawMovieFrame)
    s32 height;             // 0x04: its height
    s32 f08;                // 0x08: zero when the decoded picture is to be shown
    u8 pad0C[0x48 - 0x0C];
};

struct MoviePlayer {
    u32 movieIndex;             // 0x00: the playing movie's index in g_movieKeys (PlayMovie)
    IdentityKey* queued;        // 0x04: the movie to play next; main_loop.cpp plays it when set
    IdentityKey* queuedNext;    // 0x08: the movie to play after it (QueueMovieWithSuccessor)
    StreamReaderWindow* reader; // 0x0C: the stream the movie is read from (InitMoviePlayback)
    MovieDecoder decoder;       // 0x10
    u8* decoderWork;            // 0x58: the decoder's work memory
    u8* picture;                // 0x5C: where a picture is decoded to
    RingBuffer videoRing;       // 0x60: the video data on its way to the IPU
    MovieStream stream;         // 0x80
    void* uploadPacket;         // 0x114: the GS packet that uploads a picture (UploadMovieFrame)
    void* drawPacket;           // 0x118: the GS packet that draws it (DrawMovieFrame)
    u8 pad11C[0x14];
    s32 frameSemaphore;         // 0x130: posted for each picture, which the decode thread sends
    volatile s32 threadStep;    // 0x134: the decode thread's step (0, 1, 2); FinishMovie waits for 0
    u32 crc;                    // 0x138: AdvanceCodeChecksum's running CRC-32
    u8* cur;                    // 0x13C: the next word it checks
    s32 remain;                 // 0x140: the bytes left to check
    u8 pad144[4];  // to the label after it, g_movieChecksumFailed
};

extern MoviePlayer g_moviePlayer;

#endif
