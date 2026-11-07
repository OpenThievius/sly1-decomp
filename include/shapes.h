// SPDX-License-Identifier: AGPL-3.0-or-later
// The small shapes many files declare for themselves: blocks of four words, vectors and
// matrices of floats, an unaligned word and a colour. Written for this project from what
// retail's code does with them (build/swarm/st3/PLAN.md, section 6).
//
// The alignment is part of each shape: GCC 2.95 copies a 16-aligned block with lq/sq, a
// 4-aligned one with four lw/sw, a packed one with lwl/lwr (ldl/ldr for a doubleword), and it
// gives a 16-aligned local a 16-aligned stack slot. So a view takes the shape whose alignment
// it has, never another one of the same size. The 16-aligned four floats and the three-row
// matrix are Vec02 and Mat02 (c02.h); this header does not repeat them.
#ifndef SHAPES_H
#define SHAPES_H

#include "common.h"

// Four words moved as one quadword (the 105 views of this shape that copy with lq/sq).
struct __attribute__((aligned(16))) Quad16 {
    s32 w[4];               // 0x00
};

// Four words moved one by one (the views that copy with four lw/sw).
struct Quad4 {
    s32 w[4];               // 0x00
};

// Sixteen bytes at an address the code does not trust to be aligned: two doublewords, as the
// views read them (ldl/ldr; Pair16_1F00F0, Pk16_001DCD28).
struct __attribute__((packed)) QuadP {
    u64 lo;                 // 0x00
    u64 hi;                 // 0x08
};

// One word read and written with lwl/lwr (a colour or a key at an unaligned address:
// Unaligned_15DBB8, U4_15E318, Unaligned_1626A8, Word_193210, Packed_154EE0).
struct __attribute__((packed)) U32P {
    u32 v;                  // 0x00
};

// A doubleword read and written with ldl/ldr (U64_12A678, U64_1626C0, Pk8_2195).
struct __attribute__((packed)) U64P {
    u64 v;                  // 0x00
};

// A colour, one byte per channel (D_002623E0, D_002610D8, D_002610E0 and the views of them).
struct Rgba4 {
    u8 r;                   // 0x00
    u8 g;                   // 0x01
    u8 b;                   // 0x02
    u8 a;                   // 0x03
};

// Three floats: a point or a direction without the fourth word (24 views).
struct Vec3 {
    f32 x;                  // 0x00
    f32 y;                  // 0x04
    f32 z;                  // 0x08
};

// Four floats at 4-byte alignment (the 26 views that are not Vec02: lwc1/swc1 one by one).
struct Vec4U {
    f32 x;                  // 0x00
    f32 y;                  // 0x04
    f32 z;                  // 0x08
    f32 w;                  // 0x0C
};

// Three rows of four floats at 4-byte alignment (Buf_16A580, Buf_16D0C0, Mat_1EB748,
// Loc_13F940): the shape of Mat02 where the code does not align it.
struct Mat3U {
    f32 m[3][4];            // 0x00
};

// Four rows of four floats at 4-byte alignment (Mat_188850, Mat_1442C8,
// Mat_161F70: all the 4-row views are 4-aligned).
struct Mat4 {
    f32 m[4][4];            // 0x00
};

// Four rows moved as quadwords: the layout of four Vec02 (the 16-aligned 4-row blocks,
// Blk4_18DB20, Tail_157EF8, Dst_188B08).
struct __attribute__((aligned(16))) Mat4A {
    f32 m[4][4];            // 0x00
};

typedef char check_Quad16[sizeof(Quad16) == 0x10 && __alignof__(Quad16) == 16 ? 1 : -1];
typedef char check_Quad4[sizeof(Quad4) == 0x10 && __alignof__(Quad4) == 4 ? 1 : -1];
typedef char check_QuadP[sizeof(QuadP) == 0x10 && __alignof__(QuadP) == 1 ? 1 : -1];
typedef char check_U32P[sizeof(U32P) == 4 && __alignof__(U32P) == 1 ? 1 : -1];
typedef char check_U64P[sizeof(U64P) == 8 && __alignof__(U64P) == 1 ? 1 : -1];
typedef char check_Rgba4[sizeof(Rgba4) == 4 ? 1 : -1];
typedef char check_Vec3[sizeof(Vec3) == 0xC ? 1 : -1];
typedef char check_Vec4U[sizeof(Vec4U) == 0x10 && __alignof__(Vec4U) == 4 ? 1 : -1];
typedef char check_Mat3U[sizeof(Mat3U) == 0x30 && __alignof__(Mat3U) == 4 ? 1 : -1];
typedef char check_Mat4[sizeof(Mat4) == 0x40 && __alignof__(Mat4) == 4 ? 1 : -1];
typedef char check_Mat4A[sizeof(Mat4A) == 0x40 && __alignof__(Mat4A) == 16 ? 1 : -1];

#endif
