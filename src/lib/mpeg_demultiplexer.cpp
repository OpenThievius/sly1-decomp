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

void func_002115C0(Bits_20A220* s, s32 a1, s32 a2, s32 a3);
s32 func_002115F8(Bits_20A220* s, s32 n);
u8* func_002117A0(Bits_20A220* s, s32 n);
s32 func_0020A630(Bits_20A220* s, Rec_20A220* r);
s32 func_0020A7F0(Prog_20A220* p, Bits_20A220* s, u64* r);

s32 func_0020A220(Ctx_20A220* ctx, s32 a1, s32 count, s32 a3, s32 a4)
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
    func_002115C0(&bits, a1, a3, a4);
    s = &bits;
    result = 0;
    for (; handler == 0 && i < prog->f48; i++) {
        if (table[i].f0 == 0xBDFF000000ULL) {
            handler = table[i].f10;
            handlerArg = table[i].f14;
        }
    }
    for (;;) {
        if (func_002115F8(s, 0x20) == 0x1BA) {
            func_0020A630(s, r);
        }
        kind = KIND_6_20A220;
        while (func_002115F8(s, 0x18) == 1 && func_002115F8(s, 0x20) != 0x1BA &&
               func_002115F8(s, 0x20) != 0x1B9 && s->f18 < count * 8 && ok != 0) {
            (void)func_0020A7F0(prog, s, &r->f18);
            if (s->f18 > count * 8) {
                continue;
            }
            for (i = 0; i < prog->f48; i++) {
                Ent_20A220* e = &table[i];
                if (e->f0 == (r->f18 & e->f8)) {
                    args.f0 = kind;
                    args.f4 = func_002117A0(s, r->f40);
                    args.f8 = func_002117A0(s, r->f38);
                    args.f10 = r->f28;
                    args.fC = r->f3C;
                    args.f18 = r->f30;
                    ok = e->f10(ctx, &args, e->f14);
                    break;
                }
            }
            if (i == prog->f48 && handler != 0) {
                args.f0 = kind;
                args.f4 = func_002117A0(s, r->f40);
                args.f8 = func_002117A0(s, r->f38);
                args.f10 = r->f28;
                args.fC = r->f3C;
                args.f18 = r->f30;
                ok = handler(ctx, &args, handlerArg);
            }
            if (ok != 0) {
                result = (s32)(s->f18 >> 3);
            }
        }
        if (s->f18 > count * 8 || func_002115F8(s, 0x20) != 0x1BA) {
            break;
        }
    }
    return result;
}

s32 func_0020A518(Ctx_20A220* ctx, s32 a, s32 b)
{
    return func_0020A220(ctx, a, b, 0, -1);
}

struct Ent_20A538 { u64 key; u64 data; s32 value; s32 extra; };
struct Ctx_20A538 { u8 pad[0x44]; struct Ent_20A538* ents; s32 count; };
struct Obj_20A538 { u8 pad[0x40]; struct Ctx_20A538* ctx; };
struct Pair_20A538 { u64 a; u64 b; };
// The stream ids the demultiplexer knows, each with the mask of its significant bits.
Pair_20A538 D_0027AED0[10] = {
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
u64 func_0020A190(s32 idx, u64 key);

s32 func_0020A538(struct Obj_20A538* self, s32 idx, u64 key, s32 a3, s32 a4)
{
    s32 result = 0;
    struct Ctx_20A538* ctx = self->ctx;
    struct Ent_20A538* ents = ctx->ents;
    u64 k = func_0020A190(idx, key);
    s32 count = ctx->count;
    s32 i;
    for (i = 0; i < count; i++) {
        if (k == ents[i].key) {
            result = ents[i].value;
            break;
        }
    }
    if (i < 0x40) {
        struct Ent_20A538* e = &ents[i];
        ctx->count = count + 1;
        e->key = k;
        e->extra = a4;
        e->value = a3;
        e->data = D_0027AED0[idx].b;
    }
    return result;
}

struct Reader_0020A630 { u8 pad[0x10]; };
struct Out_0020A630 { s32 w0; s32 w4; s32 w8; s32 wC; };

s32 func_002116B0(Reader_0020A630* r, s32 bits);
void func_00211700(Reader_0020A630* r);
s32 func_002115F8(Reader_0020A630* r, s32 bits);
s32 func_0020A780(Reader_0020A630* r, Out_0020A630* o);

s32 func_0020A630(Reader_0020A630* r, Out_0020A630* o)
{
    u32 i; u32 n; u32 a; u32 b; u32 c;
    i = 0;
    (void)func_002116B0(r, 0x22);
    a = func_002116B0(r, 3);
    func_00211700(r);
    b = func_002116B0(r, 0xF);
    func_00211700(r);
    c = func_002116B0(r, 0xF);
    func_00211700(r);
    o->w0 = func_002116B0(r, 9);
    (void)func_002116B0(r, 0x1E);
    n = func_002116B0(r, 3);
    o->w8 = (a >> 2) & 1;
    o->w4 = (a << 30) | (b << 15) | c;
    for (i = 0; i < n; i++) {
        (void)func_002116B0(r, 8);
    }
    if (func_002115F8(r, 0x20) == 0x1BB) {
        o->wC = 1;
        func_0020A780(r, o);
    } else {
        o->wC = 0;
    }
    return 1;
}

struct Obj_0020A780;

s64 func_002116B0(Obj_0020A780* self, s32 size);
s32 func_002115F8(Obj_0020A780* self, s32 n);

s32 func_0020A780(Obj_0020A780* self)
{
    func_002116B0(self, 0x38);
    func_002116B0(self, 0x28);
    while (func_002115F8(self, 1) == 1) {
        func_002116B0(self, 0x18);
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

u32 func_002116B0(Bits_20A7F0* bs, s32 n);
void func_00211700(Bits_20A7F0* bs);
void func_00211748(Bits_20A7F0* bs, s32 n);
s32 func_0020B978(Ctx_20A7F0* ctx, const char* msg);

s32 func_0020A7F0(Ctx_20A7F0* ctx, Bits_20A7F0* bs, Hdr_20A7F0* hdr)
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
    func_002116B0(bs, 0x18);
    hdr->id = (u64)func_002116B0(bs, 8) << 32;
    hdr->len = func_002116B0(bs, 16);
    hdr->dts = -1;
    hdr->pts = -1;
    if (hdr->id != (u64)0xBC << 32 && hdr->id != (u64)0xBE << 32 && hdr->id != (u64)0xBF << 32
        && hdr->id != (u64)0xF0 << 32 && hdr->id != (u64)0xF1 << 32 && hdr->id != (u64)0xFF << 32
        && hdr->id != (u64)0xF2 << 32 && hdr->id != (u64)0xF8 << 32)
    {
        func_002116B0(bs, 2);
        hdr->scramble = func_002116B0(bs, 2);
        func_002116B0(bs, 4);
        flags = func_002116B0(bs, 2);
        escr = func_002116B0(bs, 1);
        opt = func_002116B0(bs, 4);
        ext = func_002116B0(bs, 1);
        hdrlen = func_002116B0(bs, 8);
        start = bs->pos;
        if (flags & 2)
        {
            u32 a, b, c;
            func_002116B0(bs, 4);
            a = func_002116B0(bs, 3);
            func_00211700(bs);
            b = func_002116B0(bs, 15);
            func_00211700(bs);
            c = func_002116B0(bs, 15);
            func_00211700(bs);
            hdr->pts = ((u64)((a >> 2) & 1) << 32) | (u32)((a << 30) | (b << 15) | c);
        }
        if (flags == 3)
        {
            u32 a, b, c;
            func_002116B0(bs, 4);
            a = func_002116B0(bs, 3);
            func_00211700(bs);
            b = func_002116B0(bs, 15);
            func_00211700(bs);
            c = func_002116B0(bs, 15);
            func_00211700(bs);
            hdr->dts = ((u64)((a >> 2) & 1) << 32) | (u32)((a << 30) | (b << 15) | c);
        }
        if (escr == 1)
        {
            func_002116B0(bs, 0x30);
        }
        if (opt != 0)
        {
            func_002116B0(bs, tbl.bits[opt]);
        }
        if (ext == 1)
        {
            s32 priv = func_002116B0(bs, 1);
            s32 pack = func_002116B0(bs, 1);
            s32 seq = func_002116B0(bs, 1);
            s32 pstd = func_002116B0(bs, 1);
            s32 ext2;
            func_002116B0(bs, 3);
            ext2 = func_002116B0(bs, 1);
            if (priv == 1)
            {
                func_002116B0(bs, 0x30);
                func_002116B0(bs, 0x30);
                func_002116B0(bs, 0x20);
            }
            if (pack == 1)
            {
                func_0020B978(ctx, "pack_header_field_flag needs to be '0' in PS\n");
                return 0;
            }
            if (seq == 1)
            {
                func_002116B0(bs, 0x10);
            }
            if (pstd == 1)
            {
                func_002116B0(bs, 0x10);
            }
            if (ext2 == 1)
            {
                u32 i;
                u32 count;
                func_00211700(bs);
                count = func_002116B0(bs, 7);
                for (i = 0; i < count; i++)
                {
                    func_002116B0(bs, 8);
                }
            }
        }
        skip = hdrlen - (s32)((bs->pos - start) >> 3);
        if (skip != 0)
        {
            func_00211748(bs, skip);
        }
        rest = hdr->len - hdrlen;
        n = rest - 3;
        hdr->size = n;
        hdr->start = bs->pos;
        if (hdr->id == (u64)0xBD << 32)
        {
            hdr->id |= func_002116B0(bs, 32);
            n = rest - 7;
        }
        if (n != 0)
        {
            func_00211748(bs, n);
        }
    } else {
    if (hdr->id == (u64)0xBC << 32 || hdr->id == (u64)0xBF << 32 || hdr->id == (u64)0xF0 << 32
        || hdr->id == (u64)0xF1 << 32 || hdr->id == (u64)0xFF << 32 || hdr->id == (u64)0xF2 << 32
        || hdr->id == (u64)0xF8 << 32)
    {
        s32 m = hdr->len;
        if (hdr->id == (u64)0xBF << 32)
        {
            hdr->id |= func_002116B0(bs, 32);
            m -= 4;
        }
        if (m != 0)
        {
            func_00211748(bs, m);
        }
    }
    else if (hdr->id == (u64)0xBE << 32)
    {
        if (hdr->len != 0)
        {
            func_00211748(bs, hdr->len);
        }
    }
    }
    return 1;
}
