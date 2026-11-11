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

INCLUDE_ASM(func_0020A190);

LINKER_REMNANT(func_0020A218);

struct Ctx_20A220;
enum Kind_20A220 { KIND_6_20A220 = 6 };
struct Args_20A220 {
    Kind_20A220 f0;
    u8* f4;
    u8* f8;
    s32 fC;
    u64 f10;
    u64 f18;
};
typedef s32 (*Handler_20A220)(Ctx_20A220* ctx, Args_20A220* args, void* arg);
struct Ent_20A220 {
    u64 f0;
    u64 f8;
    Handler_20A220 f10;
    void* f14;
};
struct Prog_20A220 {
    u8 pad[0x44];
    Ent_20A220* f44;
    s32 f48;
};
struct Ctx_20A220 {
    u8 pad[0x40];
    Prog_20A220* f40;
};
struct Bits_20A220 {
    u64 f0;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    u64 f18;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
};
struct Rec_20A220 {
    u8 pad[0x18];
    u64 f18;
    u64 f20;
    u64 f28;
    u64 f30;
    s32 f38;
    s32 f3C;
    s32 f40;
    s32 f44;
    s32 f48;
    s32 f4C;
};

void InitBitReader(Bits_20A220* s, s32 a1, s32 a2, s32 a3);
s32 PeekBits(Bits_20A220* s, s32 n);
u8* GetPositionAhead(Bits_20A220* s, s32 n);
s32 ParsePackHeader(Bits_20A220* s, Rec_20A220* r);
s32 ParsePacketHeader(Prog_20A220* p, Bits_20A220* s, u64* r);

s32 DemultiplexPacks(Ctx_20A220* ctx, s32 a1, s32 count, s32 a3, s32 a4)
{
    Bits_20A220 bits;
    Rec_20A220 rec;
    Args_20A220 args;
    Bits_20A220* s;
    Rec_20A220* r;
    Handler_20A220 handler;
    void* handlerArg;
    Ent_20A220* table;
    s32 result;
    Prog_20A220* prog;
    s32 ok;
    Kind_20A220 kind;
    s32 i;

    r = &rec;
    prog = ctx->f40;
    handler = 0;
    handlerArg = 0;
    ok = 1;
    i = 0;
    table = prog->f44;
    InitBitReader(&bits, a1, a3, a4);
    s = &bits;
    result = 0;
    for (; handler == 0 && i < prog->f48; i++) {
        if (table[i].f0 == 0xBDFF000000ULL) {
            handler = table[i].f10;
            handlerArg = table[i].f14;
        }
    }
    for (;;) {
        if (PeekBits(s, 0x20) == 0x1BA) {
            ParsePackHeader(s, r);
        }
        kind = KIND_6_20A220;
        while (PeekBits(s, 0x18) == 1 && PeekBits(s, 0x20) != 0x1BA &&
               PeekBits(s, 0x20) != 0x1B9 && s->f18 < count * 8 && ok != 0) {
            (void)ParsePacketHeader(prog, s, &r->f18);
            if (s->f18 > count * 8) {
                continue;
            }
            for (i = 0; i < prog->f48; i++) {
                Ent_20A220* e = &table[i];
                if (e->f0 == (r->f18 & e->f8)) {
                    args.f0 = kind;
                    args.f4 = GetPositionAhead(s, r->f40);
                    args.f8 = GetPositionAhead(s, r->f38);
                    args.f10 = r->f28;
                    args.fC = r->f3C;
                    args.f18 = r->f30;
                    ok = e->f10(ctx, &args, e->f14);
                    break;
                }
            }
            if (i == prog->f48 && handler != 0) {
                args.f0 = kind;
                args.f4 = GetPositionAhead(s, r->f40);
                args.f8 = GetPositionAhead(s, r->f38);
                args.f10 = r->f28;
                args.fC = r->f3C;
                args.f18 = r->f30;
                ok = handler(ctx, &args, handlerArg);
            }
            if (ok != 0) {
                result = (s32)(s->f18 >> 3);
            }
        }
        if (s->f18 > count * 8 || PeekBits(s, 0x20) != 0x1BA) {
            break;
        }
    }
    return result;
}

s32 DemultiplexBuffer(Ctx_20A220* ctx, s32 a, s32 b)
{
    return DemultiplexPacks(ctx, a, b, 0, -1);
}

struct Pair_20A538 { u64 a; u64 b; };
// The stream ids the demultiplexer knows, each with the mask of its significant bits.
Pair_20A538 g_streamIds[10] = {
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
u64 GetStreamId(s32 idx, u64 key);

// Registers a handler and its argument for the stream's id in the table the demultiplexer looks
// packets up in (the entries DemultiplexPacks runs), and returns the handler it replaces.
s32 SetStreamCallback(Ctx_20A220* self, s32 idx, u64 key, s32 a3, s32 a4)
{
    s32 result = 0;
    Prog_20A220* ctx = self->f40;
    Ent_20A220* ents = ctx->f44;
    u64 k = GetStreamId(idx, key);
    s32 count = ctx->f48;
    s32 i;
    for (i = 0; i < count; i++) {
        if (k == ents[i].f0) {
            result = (s32)ents[i].f10;
            break;
        }
    }
    if (i < 0x40) {
        Ent_20A220* e = &ents[i];
        ctx->f48 = count + 1;
        e->f0 = k;
        e->f14 = (void*)a4;
        e->f10 = (Handler_20A220)a3;
        e->f8 = g_streamIds[idx].b;
    }
    return result;
}

// The bit reader as func_0020A630 sees it. The pack header's reader and the system header's
// (SystemHeaderReader below) are separate types because their callers declare ReadBits with
// different results (s32 here, s64 there), as retail's registers want, and one name cannot be
// declared both ways on one type.
struct PackHeaderReader { u8 pad[0x10]; };
// What the pack header yields: its clock's 9-bit extension, its low 32 bits and its top bit, and
// whether a system header follows.
struct PackHeaderInfo {
    s32 clockExtension;     // 0x00
    s32 clockLow;           // 0x04
    s32 clockHigh;          // 0x08
    s32 hasSystemHeader;    // 0x0C
};

s32 ReadBits(PackHeaderReader* r, s32 bits);
s64 ReadBit(PackHeaderReader* r);
s32 PeekBits(PackHeaderReader* r, s32 bits);
s32 ParseSystemHeader(PackHeaderReader* r, PackHeaderInfo* o);

s32 ParsePackHeader(PackHeaderReader* r, PackHeaderInfo* o)
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

// The system header's bit reader (see PackHeaderReader).
struct SystemHeaderReader;

s64 ReadBits(SystemHeaderReader* self, s32 size);
s32 PeekBits(SystemHeaderReader* self, s32 n);

s32 ParseSystemHeader(SystemHeaderReader* self)
{
    ReadBits(self, 0x38);
    ReadBits(self, 0x28);
    while (PeekBits(self, 1) == 1) {
        ReadBits(self, 0x18);
    }
    return 1;
}

struct Ctx_20A7F0;

struct Bits_20A7F0
{
    u8 pad00[0x18];
    s64 pos;
};

struct Hdr_20A7F0
{
    u64 id;
    s32 len;
    s32 scramble;
    s64 pts;
    s64 dts;
    s32 start;
    s32 size;
    s32 at;
};

struct Table_20A7F0
{
    u8 bits[16];
};

// The length of each optional field the header's flags announce.
extern const Table_20A7F0 D_00250028 = { { 0x00, 0x10, 0x08, 0x18, 0x08, 0x18, 0x10, 0x20, 0x18, 0x28, 0x20, 0x30, 0x20, 0x30, 0x28, 0x38 } };

u32 ReadBits(Bits_20A7F0* bs, s32 n);
void ReadBit(Bits_20A7F0* bs); // stays void: retail returns a value, but declared so func_0020A7F0 differs in registers
void SkipBytes(Bits_20A7F0* bs, s32 n);
s32 ReportMpegError(Ctx_20A7F0* ctx, const char* msg);

s32 ParsePacketHeader(Ctx_20A7F0* ctx, Bits_20A7F0* bs, Hdr_20A7F0* hdr)
{
    Table_20A7F0 tbl;
    s32 flags;
    s32 escr;
    s32 opt;
    s32 ext;
    s32 hdrlen;
    s32 start;
    s32 n;
    s32 skip;
    s32 rest;

    hdr->at = bs->pos;
    tbl = D_00250028;
    ReadBits(bs, 0x18);
    hdr->id = (u64)ReadBits(bs, 8) << 32;
    hdr->len = ReadBits(bs, 16);
    hdr->dts = -1;
    hdr->pts = -1;
    if (hdr->id != (u64)0xBC << 32 && hdr->id != (u64)0xBE << 32 && hdr->id != (u64)0xBF << 32
        && hdr->id != (u64)0xF0 << 32 && hdr->id != (u64)0xF1 << 32 && hdr->id != (u64)0xFF << 32
        && hdr->id != (u64)0xF2 << 32 && hdr->id != (u64)0xF8 << 32)
    {
        ReadBits(bs, 2);
        hdr->scramble = ReadBits(bs, 2);
        ReadBits(bs, 4);
        flags = ReadBits(bs, 2);
        escr = ReadBits(bs, 1);
        opt = ReadBits(bs, 4);
        ext = ReadBits(bs, 1);
        hdrlen = ReadBits(bs, 8);
        start = bs->pos;
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
            hdr->pts = ((u64)((a >> 2) & 1) << 32) | (u32)((a << 30) | (b << 15) | c);
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
            hdr->dts = ((u64)((a >> 2) & 1) << 32) | (u32)((a << 30) | (b << 15) | c);
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
                ReportMpegError(ctx, "pack_header_field_flag needs to be '0' in PS\n");
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
        skip = hdrlen - (s32)((bs->pos - start) >> 3);
        if (skip != 0)
        {
            SkipBytes(bs, skip);
        }
        rest = hdr->len - hdrlen;
        n = rest - 3;
        hdr->size = n;
        hdr->start = bs->pos;
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
        s32 m = hdr->len;
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
        if (hdr->len != 0)
        {
            SkipBytes(bs, hdr->len);
        }
    }
    }
    return 1;
}
