// SPDX-License-Identifier: AGPL-3.0-or-later
// Kind v24a2: the font, a C++ class with virtual functions (GCC vtable D_0024A220, 0x88 bytes).
// Written for this project from what retail's code does (config/us/tables.tsv, kinds.tsv).
//
// Retail's table has the vptr at +0x4C, and D_0024A220+0x58 is the vtable of the abstract base
// (its slots are the pure-virtual stub func_001FBDF8, except slot 4 = func_0015C2E8 and slot 7 =
// func_0015C3C0). The class is modelled as a plain struct with an explicit vptr whose entries are
// GCC 2.95's {s16 delta; s16 index; fn}: no `virtual`, so GCC emits no vtable or thunk of its own
// (the tables are defined in src/main/001E4000.cpp, the class's own methods in 0015C000.cpp). A
// call is `self->vt->fnN((u8*)self + self->vt->adjN, ...)`, the delta adjusting `this`.
// Entry 0 is {offset-to-top, rtti} = {0, 0, 0}, so the first virtual is entry 1.
#ifndef V24A2_H
#define V24A2_H

#include "common.h"

struct V24A2;

// Image record at +0x54 (func_0015D998 reads its width and its 64-bit register word;
// func_0015CAB8 sends the two words at +0x10 to the packet).
struct V24A2_ImgA {
    union {
        s32 w0;             // 0x0
        struct {
            u16 f0;         // 0x0
            u16 f2;         // 0x2
        };
    };
    u32 f4;                 // 0x4
    u8 f8;                  // 0x8
    u8 f9;                  // 0x9
    u16 f0A;            // 0x0A
    u32 bytes;          // 0x0C: its size (func_001B2CA8)
    s32 f10;            // 0x10: an offset, made absolute by func_001B2CA8
    s32 f14;            // 0x14: the size in 16-byte blocks (func_001B2CA8)
    u64 f18;            // 0x18
};
typedef char check_V24A2_ImgA[sizeof(V24A2_ImgA) == 0x20 ? 1 : -1];   // 32-byte records (D_00274504, func_0015D8A8)

// Second image record at +0x58 (a palette; same readers).
struct V24A2_ImgB {
    u32 f0;                 // 0x0
    u16 f4;                 // 0x4
    u16 f6;             // 0x06
    s32 f8;             // 0x08
    s32 fC;             // 0x0C
    u64 f10;            // 0x10
};
typedef char check_V24A2_ImgB[sizeof(V24A2_ImgB) == 0x18 ? 1 : -1];   // 24-byte records (D_0027450C, func_0015D8A8)

// A glyph of the table at +0x7C, 8 bytes, sorted by key (func_0015DAB8 searches it).
struct V24A2_Glyph {
    u16 key;            // 0x00
    u16 u;              // 0x02
    u16 v;              // 0x04
    u16 w;              // 0x06
};
typedef char check_V24A2_Glyph[sizeof(V24A2_Glyph) == 8 ? 1 : -1];   // `n << 3` bytes loaded (func_0015D8A8)

struct V24A2_Pt { f32 x, y; };

struct V24A2_Vt {
    s16 adj0; s16 idx0; void* fn0;                                              // 0x00
    s16 adj1; s16 idx1; V24A2* (*clone)(V24A2* self, f32 sx, f32 sy);           // 0x08
    s16 adj2; s16 idx2; s32 (*has)(V24A2* self, s32 key);                       // 0x10
    s16 adj3; s16 idx3; f32 (*width)(V24A2* self, s32 key);                     // 0x18
    s16 adj4; s16 idx4; void (*begin)(V24A2* self, s32 a, s32 b);               // 0x20
    s16 adj5; s16 idx5; void (*flush)(V24A2* self, s32 a);                      // 0x28
    s16 adj6; s16 idx6; f32 (*draw)(f32 x, f32 y, V24A2* self, s32 key, s32 color, s32 s);  // 0x30
    s16 adj7; s16 idx7; void (*end)(V24A2* self, s32 a, s32 b);                 // 0x38
    s16 adj8; s16 idx8; void (*drawTurned)(V24A2* self, s32 key, u32 color, void* s, f32 x, f32 y);  // 0x40
    s16 adj9; s16 idx9; void (*drawBox)(V24A2* self, void* item, void* rect, void* s);  // 0x48
};

// The object: its first 0x4C bytes are the font's metrics and a small stack of scales
// (func_0015C8B8 pushes, func_0015C900 pops, func_0015C260 copies), then the vptr.
// func_0015C930 (slot 1) allocates 0x88 bytes; func_0015DB28 builds one at +0x10 of the text
// state (its vptr store is at +0x5C).
struct V24A2 {
    s32 f00;                // 0x00
    s32 advance;            // 0x04: width of a character the table lacks (func_0015CA60, func_0015CD18)
    s32 height;             // 0x08: line height in texels
    s32 depth;              // 0x0C: how many scales the stack holds
    V24A2_Pt stack[4];      // 0x10: the pushed (x, y) scales
    s32 f30;                // 0x30
    u8 pad34[4];            // 0x34
    union {
        s64 f38;            // 0x38: a register word used when f30 is set (func_0015CB88)
        u64 f38u;
    };
    s32 f40;                // 0x40: the texture word passed to func_001618C0
    f32 sx;                 // 0x44: horizontal scale
    f32 sy;                 // 0x48: vertical scale
    const V24A2_Vt* vt;     // 0x4C
    s32 id;                 // 0x50: index in D_00262268 (func_0015D8A8)
    V24A2_ImgA* imgA;       // 0x54
    V24A2_ImgB* imgB;       // 0x58
    u8 pad5C[4];            // 0x5C
    union {
        s64 f60;            // 0x60: the 64-bit register word (bits 30..33 give the texture size)
        u64 f60u;
    };
    s32 f68;                // 0x68
    s32 f6C;                // 0x6C
    s32 f70;                // 0x70
    s32 f74;                // 0x74
    s32 glyphCount;         // 0x78
    V24A2_Glyph* glyphs;    // 0x7C
    u32 mask;               // 0x80: bit in D_002622D8->flags marking the state as sent
    u8 pad84[4];            // 0x84

    // Whether the font has a glyph for `c`, through its table's entry 2.
    s32 Has(s32 c) { return vt->has((V24A2*)((u8*)this + vt->adj2), c); }
};

typedef char check_V24A2[sizeof(V24A2) == 0x88 ? 1 : -1];

#endif
