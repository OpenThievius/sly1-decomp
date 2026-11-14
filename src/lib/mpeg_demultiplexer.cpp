// SPDX-License-Identifier: AGPL-3.0-or-later
// The MPEG library's program stream demultiplexer, the whole object, 0x20A190-0x20ADA0
// (config/us/files.tsv): the table of stream ids (D_0027AED0) and the lookup that turns a stream
// number into its id (func_0020A190), the registration of a callback for a stream
// (func_0020A538), the walk over a buffer of packs that hands each packet to its stream's callback
// (func_0020A220, and func_0020A518 over a whole buffer), and the parsers of a pack header
// (func_0020A630), a system header (func_0020A780) and a packet header (func_0020A7F0). Its
// .rodata is the packet header's table of field lengths and its one message, its .data the stream
// table. Written for this project from retail's code.
#include "common.h"
#include "asm_func.h"
#include "mpeg_bit_reader.h"
#include "mpeg_decoder.h"

// A stream id and the mask of its significant bits.
struct StreamIdMask { u64 id; u64 mask; };
extern StreamIdMask g_streamIds[10];

u64 GetStreamId(u32 idx, s32 key)
{
    u64 r = 0;
    s32 sh = 0;
    if (idx < 10) {
        StreamIdMask e;
        switch (g_streamIds[idx].mask) {
        case 0xFFFFFFFFFFULL:
            sh = 0;
            break;
        case 0xFFFF000000ULL:
            sh = 24;
            break;
        case 0xFF00000000ULL:
            sh = 32;
            break;
        }
        r = g_streamIds[idx].id | ((u64)key << sh);
    }
    return r;
}

LINKER_REMNANT(func_0020A218);

// What the pack header yields: its clock's 9-bit extension, its low 32 bits and its top bit, and
// whether a system header follows.
struct PackHeaderInfo {
    s32 clockExtension;     // 0x00
    s32 clockLow;           // 0x04
    s32 clockHigh;          // 0x08
    s32 hasSystemHeader;    // 0x0C
};

// A packet's header: its stream id, its length, its scrambling, its time stamps (-1 when it has
// none), and the positions, in bits, of its payload and of the header itself.
struct PacketHeader
{
    u64 id;                 // 0x00
    s32 length;             // 0x08
    s32 scrambling;         // 0x0C
    s64 pts;                // 0x10
    s64 dts;                // 0x18
    s32 payloadPosition;    // 0x20
    s32 payloadSize;        // 0x24
    s32 position;           // 0x28
};

// What DemultiplexPacks keeps of the pack and the packet it is on.
struct DemuxRecord {
    PackHeaderInfo pack;    // 0x00
    u8 pad10[0x18 - 0x10];
    PacketHeader packet;    // 0x18
};

s32 ParsePackHeader(BitReader* r, PackHeaderInfo* o);
s32 ParsePacketHeader(MpegDecoder* decoder, BitReader* bs, PacketHeader* hdr);

s32 DemultiplexPacks(MpegHandle* ctx, s32 a1, s32 count, s32 a3, s32 a4)
{
    BitReader bits;
    DemuxRecord rec;
    MpegStreamPacket args;
    BitReader* s;
    DemuxRecord* r;
    MpegStreamFn handler;
    void* handlerArg;
    MpegStreamEntry* table;
    s32 result;
    MpegDecoder* prog;
    s32 ok;
    MpegStreamEvent kind;
    s32 i;

    r = &rec;
    prog = ctx->decoder;
    handler = 0;
    handlerArg = 0;
    ok = 1;
    i = 0;
    table = prog->streamTable;
    InitBitReader(&bits, a1, a3, a4);
    s = &bits;
    result = 0;
    for (; handler == 0 && i < prog->streamCount; i++) {
        if (table[i].id == 0xBDFF000000ULL) {
            handler = table[i].handler;
            handlerArg = table[i].arg;
        }
    }
    for (;;) {
        if (PeekBits(s, 0x20) == 0x1BA) {
            ParsePackHeader(s, &r->pack);
        }
        kind = MPEG_STREAM_PACKET;
        while (PeekBits(s, 0x18) == 1 && PeekBits(s, 0x20) != 0x1BA &&
               PeekBits(s, 0x20) != 0x1B9 && s->consumed < count * 8 && ok != 0) {
            (void)ParsePacketHeader(prog, s, &r->packet);
            if (s->consumed > count * 8) {
                continue;
            }
            for (i = 0; i < prog->streamCount; i++) {
                MpegStreamEntry* e = &table[i];
                if (e->id == (r->packet.id & e->mask)) {
                    args.kind = kind;
                    args.packet = (u8*)GetPositionAhead(s, r->packet.position);
                    args.payload = (u8*)GetPositionAhead(s, r->packet.payloadPosition);
                    args.pts = r->packet.pts;
                    args.payloadSize = r->packet.payloadSize;
                    args.dts = r->packet.dts;
                    ok = e->handler(ctx, &args, e->arg);
                    break;
                }
            }
            if (i == prog->streamCount && handler != 0) {
                args.kind = kind;
                args.packet = (u8*)GetPositionAhead(s, r->packet.position);
                args.payload = (u8*)GetPositionAhead(s, r->packet.payloadPosition);
                args.pts = r->packet.pts;
                args.payloadSize = r->packet.payloadSize;
                args.dts = r->packet.dts;
                ok = handler(ctx, &args, handlerArg);
            }
            if (ok != 0) {
                result = (s32)(s->consumed >> 3);
            }
        }
        if (s->consumed > count * 8 || PeekBits(s, 0x20) != 0x1BA) {
            break;
        }
    }
    return result;
}

s32 DemultiplexBuffer(MpegHandle* ctx, s32 a, s32 b)
{
    return DemultiplexPacks(ctx, a, b, 0, -1);
}

// The stream ids the demultiplexer knows, each with the mask of its significant bits.
StreamIdMask g_streamIds[10] = {
    { 0xE000000000ULL, 0xFF00000000ULL },
    { 0xBDFFC00000ULL, 0xFFFFFFFFFFULL },
    { 0xBDFFA00000ULL, 0xFFFFFFFFFFULL },
    { 0xBDFFA10000ULL, 0xFFFFFFFFFFULL },
    { 0xBDFF900000ULL, 0xFFFFFFFFFFULL },
    { 0xC000000000ULL, 0xFF00000000ULL },
    { 0xBD80000000ULL, 0xFFFF000000ULL },
    { 0xBDA0000000ULL, 0xFFFF000000ULL },
    { 0xBD88000000ULL, 0xFFFF000000ULL },
    { 0xBD90000000ULL, 0xFFFF000000ULL },
};

// Registers a handler and its argument for the stream's id in the table the demultiplexer looks
// packets up in (the entries DemultiplexPacks runs), and returns the handler it replaces.
MpegStreamFn SetStreamCallback(MpegHandle* self, s32 idx, s32 key, MpegStreamFn handler, void* arg)
{
    MpegStreamFn result = 0;
    MpegDecoder* ctx = self->decoder;
    MpegStreamEntry* ents = ctx->streamTable;
    u64 k = GetStreamId(idx, key);
    s32 count = ctx->streamCount;
    s32 i;
    for (i = 0; i < count; i++) {
        if (k == ents[i].id) {
            result = ents[i].handler;
            break;
        }
    }
    if (i < 0x40) {
        MpegStreamEntry* e = &ents[i];
        ctx->streamCount = count + 1;
        e->id = k;
        e->arg = arg;
        e->handler = handler;
        e->mask = g_streamIds[idx].mask;
    }
    return result;
}

s32 ParseSystemHeader(BitReader* self, PackHeaderInfo* info);

s32 ParsePackHeader(BitReader* r, PackHeaderInfo* o)
{
    u32 i; u32 n; u32 a; u32 b; u32 c;
    i = 0;
    (void)ReadBits(r, 0x22);
    a = ReadBits(r, 3);
    ReadBit(r);
    b = ReadBits(r, 0xF);
    ReadBit(r);
    c = ReadBits(r, 0xF);
    ReadBit(r);
    o->clockExtension = ReadBits(r, 9);
    (void)ReadBits(r, 0x1E);
    n = ReadBits(r, 3);
    o->clockHigh = (a >> 2) & 1;
    o->clockLow = (a << 30) | (b << 15) | c;
    for (i = 0; i < n; i++) {
        (void)ReadBits(r, 8);
    }
    if (PeekBits(r, 0x20) == 0x1BB) {
        o->hasSystemHeader = 1;
        ParseSystemHeader(r, o);
    } else {
        o->hasSystemHeader = 0;
    }
    return 1;
}

s32 ParseSystemHeader(BitReader* self, PackHeaderInfo* info)
{
    ReadBits(self, 0x38);
    ReadBits(self, 0x28);
    while (PeekBits(self, 1) == 1) {
        ReadBits(self, 0x18);
    }
    return 1;
}

// The lengths of the optional fields.
struct FieldLengths
{
    u8 bits[16];
};

// The length of each optional field the header's flags announce.
extern const FieldLengths g_packetOptionalFieldLengths = { { 0x00, 0x10, 0x08, 0x18, 0x08, 0x18, 0x10, 0x20, 0x18, 0x28, 0x20, 0x30, 0x20, 0x30, 0x28, 0x38 } };

void ReportMpegError(MpegDecoder* self, const char* value);

s32 ParsePacketHeader(MpegDecoder* decoder, BitReader* bs, PacketHeader* hdr)
{
    FieldLengths tbl;
    s32 flags;
    s32 escr;
    s32 opt;
    s32 ext;
    s32 hdrlen;
    s32 start;
    s32 n;
    s32 skip;
    s32 rest;

    hdr->position = bs->consumed;
    tbl = g_packetOptionalFieldLengths;
    ReadBits(bs, 0x18);
    hdr->id = (u64)ReadBits(bs, 8) << 32;
    hdr->length = ReadBits(bs, 16);
    hdr->dts = -1;
    hdr->pts = -1;
    if (hdr->id != (u64)0xBC << 32 && hdr->id != (u64)0xBE << 32 && hdr->id != (u64)0xBF << 32
        && hdr->id != (u64)0xF0 << 32 && hdr->id != (u64)0xF1 << 32 && hdr->id != (u64)0xFF << 32
        && hdr->id != (u64)0xF2 << 32 && hdr->id != (u64)0xF8 << 32)
    {
        ReadBits(bs, 2);
        hdr->scrambling = ReadBits(bs, 2);
        ReadBits(bs, 4);
        flags = ReadBits(bs, 2);
        escr = ReadBits(bs, 1);
        opt = ReadBits(bs, 4);
        ext = ReadBits(bs, 1);
        hdrlen = ReadBits(bs, 8);
        start = bs->consumed;
        if (flags & 2)
        {
            u32 a, b, c;
            ReadBits(bs, 4);
            a = ReadBits(bs, 3);
            ReadBit(bs);
            b = ReadBits(bs, 15);
            ReadBit(bs);
            c = ReadBits(bs, 15);
            ReadBit(bs);
            u32 lo = (a << 30) | (b << 15) | c;
            hdr->pts = ((u64)((a >> 2) & 1) << 32) | lo;
        }
        if (flags == 3)
        {
            u32 a, b, c;
            ReadBits(bs, 4);
            a = ReadBits(bs, 3);
            ReadBit(bs);
            b = ReadBits(bs, 15);
            ReadBit(bs);
            c = ReadBits(bs, 15);
            ReadBit(bs);
            u32 lo = (a << 30) | (b << 15) | c;
            hdr->dts = ((u64)((a >> 2) & 1) << 32) | lo;
        }
        if (escr == 1)
        {
            ReadBits(bs, 0x30);
        }
        if (opt != 0)
        {
            ReadBits(bs, tbl.bits[opt]);
        }
        if (ext == 1)
        {
            s32 priv = ReadBits(bs, 1);
            s32 pack = ReadBits(bs, 1);
            s32 seq = ReadBits(bs, 1);
            s32 pstd = ReadBits(bs, 1);
            s32 ext2;
            ReadBits(bs, 3);
            ext2 = ReadBits(bs, 1);
            if (priv == 1)
            {
                ReadBits(bs, 0x30);
                ReadBits(bs, 0x30);
                ReadBits(bs, 0x20);
            }
            if (pack == 1)
            {
                ReportMpegError(decoder, "pack_header_field_flag needs to be '0' in PS\n");
                return 0;
            }
            if (seq == 1)
            {
                ReadBits(bs, 0x10);
            }
            if (pstd == 1)
            {
                ReadBits(bs, 0x10);
            }
            if (ext2 == 1)
            {
                u32 i;
                u32 count;
                ReadBit(bs);
                count = ReadBits(bs, 7);
                for (i = 0; i < count; i++)
                {
                    ReadBits(bs, 8);
                }
            }
        }
        skip = hdrlen - (s32)((bs->consumed - start) >> 3);
        if (skip != 0)
        {
            SkipBytes(bs, skip);
        }
        rest = hdr->length - hdrlen;
        n = rest - 3;
        hdr->payloadSize = n;
        hdr->payloadPosition = bs->consumed;
        if (hdr->id == (u64)0xBD << 32)
        {
            hdr->id |= ReadBits(bs, 32);
            n = rest - 7;
        }
        if (n != 0)
        {
            SkipBytes(bs, n);
        }
    } else {
    if (hdr->id == (u64)0xBC << 32 || hdr->id == (u64)0xBF << 32 || hdr->id == (u64)0xF0 << 32
        || hdr->id == (u64)0xF1 << 32 || hdr->id == (u64)0xFF << 32 || hdr->id == (u64)0xF2 << 32
        || hdr->id == (u64)0xF8 << 32)
    {
        s32 m = hdr->length;
        if (hdr->id == (u64)0xBF << 32)
        {
            hdr->id |= ReadBits(bs, 32);
            m -= 4;
        }
        if (m != 0)
        {
            SkipBytes(bs, m);
        }
    }
    else if (hdr->id == (u64)0xBE << 32)
    {
        if (hdr->length != 0)
        {
            SkipBytes(bs, hdr->length);
        }
    }
    }
    return 1;
}
