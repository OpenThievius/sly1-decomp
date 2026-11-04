// SPDX-License-Identifier: AGPL-3.0-or-later
// Kind t2196: the animation curves of a class 0x83 (c83.h), four families of objects with a
// table of functions each. Written for this project from what retail's code does
// (config/us/tables.tsv, docs/DISC.md "Animations").
//
// Four factories make them, each by the curve's kind (stored at +4): func_00120FB0 the
// position curves (tables D_002196B8, D_002196C8, D_002196D8), func_00121050 the rotation
// curves (D_002196E8, D_002196F8, D_00219708), func_001210F0 the scale curves (D_00219718,
// D_00219728) and func_00121160 the weight curves (D_00219668 ... D_002196A8). Track83 holds
// them (func_0012B8C8). Each family has its own base table (D_00219600's words 10..25: four
// tables of four slots nothing refers to), so the families are four classes of their own, with
// no common type but the prefix every curve begins with, {table, kind}: T2196.
//
// Every field line ends with its offset; the sizes are the factories' allocations.
#ifndef T2196_H
#define T2196_H

#include "c02.h"

struct Stream83;     // the level stream a curve is read from (func_00137D10 and friends)
struct C83;
struct T2196_Pos;
struct T2196_Rot;
struct T2196_Scale;
struct T2196_Weight;

// The prefix of every curve.
struct T2196 {
    const void* vt;         // 0x00: the family's table
    s32 kind;               // 0x04: the kind the factory was asked for
};

// ---------------------------------------------------------------------------------------------
// The weight curves: one float over time. func_00121160 makes them, by kind 0..4.

// Slot 0 evaluates at `key` (the value and its slope, either may be 0), slot 1 reads the
// curve from the stream (0 for the blends), slot 2 gives the key times (a count and a new
// array, which may be 0).
typedef void (*T2196_WeightEval)(T2196_Weight* self, C02* owner, s32 flags, f32* outValue, f32* outSlope, f32 key, f32 scale);
typedef void (*T2196_WeightRead)(T2196_Weight* self, Stream83* stream);
typedef void (*T2196_WeightTimes)(T2196_Weight* self, s32* outCount, f32** outTimes);
struct T2196_WeightVt {
    T2196_WeightEval eval;      // 0x00
    T2196_WeightRead read;      // 0x04
    T2196_WeightTimes times;    // 0x08
    void* m3;                   // 0x0C: 0
};

struct T2196_Weight {
    const T2196_WeightVt* vt;   // 0x00
    s32 kind;                   // 0x04: 0..4
};

// A key of a kind 0 curve (D_00219668): a value with a kind (5: a constant to the next key)
// and its tangents (func_0011EFC8 reads, func_0011F0C8 evaluates).
struct Key2196_668 {
    f32 time;               // 0x00: seconds (the stream's 1/60 s count times 1/60)
    f32 value;              // 0x04
    s32 c;                  // 0x08
    f32 d;                  // 0x0C
    s32 kind;               // 0x10
    f32 f;                  // 0x14
};

// A key of a kind 1 curve (D_00219678), with the tangents on both sides (func_0011F210).
struct Key2196_678 {
    f32 time;               // 0x00
    f32 value;              // 0x04
    s32 c;                  // 0x08
    f32 d;                  // 0x0C
    f32 e;                  // 0x10
    s32 kind;               // 0x14
    f32 g;                  // 0x18
    f32 h;                  // 0x1C
};

// A key of a kind 2 curve (D_00219688): linear (func_0011F568, func_0011F478).
struct Key2196_688 {
    f32 time;               // 0x00
    f32 value;              // 0x04
};

// Kinds 0..2: a count and the keys.
struct T2196_668 : T2196_Weight {
    s32 count;              // 0x08
    Key2196_668* keys;      // 0x0C
};
struct T2196_678 : T2196_Weight {
    s32 count;              // 0x08
    Key2196_678* keys;      // 0x0C
};
struct T2196_688 : T2196_Weight {
    s32 count;              // 0x08
    Key2196_688* keys;      // 0x0C
};

// What a blend (kinds 3 and 4) is made of: an animation-like record with a length at +0x34
// and a table of (weight, record) pairs at +0xB8 (stride +0xB0, count +0xB4).
struct BlendSub2196 {
    u8 pad00[0x34]; // 0x00
    f32 length;             // 0x34
};
struct BlendRec2196 {
    f32 weight;             // 0x00
    BlendSub2196* sub;      // 0x04
};
struct BlendCfg2196 {
    u8 pad00[0x34]; // 0x00
    f32 length;             // 0x34
    u8 pad38[0xB0 - 0x38]; // 0x38
    s32 stride;             // 0xB0
    s32 count;              // 0xB4
    u8* base;               // 0xB8: count records of `stride` bytes (BlendRec2196 first)
};
struct Pair2196 {
    f32 a;                  // 0x00
    f32 b;                  // 0x04
};
struct BlendSeq2196 {
    s32 stride;             // 0x00: the offset of a record's (start, scale) pairs
    s32 count;              // 0x04
    Pair2196* pairs; // 0x08
};

// Kinds 3 and 4: a weighted mix of other weight curves, one for each record of the config
// (func_00120AA8 mixes angles, func_00120D58 sums values).
struct T2196_698 : T2196_Weight {
    BlendCfg2196* cfg;      // 0x08
    BlendSeq2196* seq;      // 0x0C
    T2196_Weight** targets; // 0x10: one for each record of cfg
};
struct T2196_6A8 : T2196_698 {
    s32 index;              // 0x14
};

// ---------------------------------------------------------------------------------------------
// The position curves: a vector over time. func_00120FB0 makes them, by kind 0..2.

// Slot 0 evaluates (owner, mode, out value, out slope, key, scale), then tells the owner
// (its slot 44); slot 1 reads the curve; slot 2 gives the key times.
typedef void (*T2196_PosEval)(T2196_Pos* self, C02* owner, s32 mode, void* outValue, void* outSlope, f32 key, f32 scale);
typedef void (*T2196_PosRead)(T2196_Pos* self, Stream83* stream);
typedef void (*T2196_PosTimes)(T2196_Pos* self, s32* outCount, f32** outTimes);
struct T2196_PosVt {
    T2196_PosEval eval;         // 0x00
    T2196_PosRead read;         // 0x04
    T2196_PosTimes times;       // 0x08
    void* m3;                   // 0x0C: 0
};

struct T2196_Pos {
    const T2196_PosVt* vt;      // 0x00
    s32 kind;                   // 0x04: 0..2
};

// A key of a kind 1 curve: a time and three vectors (func_0011FA88 reads it, func_0011F9F8
// evaluates it).
struct __attribute__((aligned(16))) Key2196_Vec {
    f32 time;               // 0x00
    u8 pad04[0x10 - 0x04]; // 0x04
    Vec02 v0;               // 0x10
    Vec02 v1;               // 0x20
    Vec02 v2;               // 0x30
};

// Kind 0 (D_002196B8, 0x30 bytes): a base vector and a weight curve for each axis (func_0011F798
// reads them, func_0011F850 gathers their key times).
struct T2196_6B8 : T2196_Pos {
    u8 pad08[0x10 - 0x08]; // 0x08
    Vec02 base;                 // 0x10
    T2196_Weight* axis[3];      // 0x20
    u8 pad2C[0x30 - 0x2C]; // 0x2C
};

// Kind 1 (D_002196C8, 0x14 bytes).
struct T2196_6C8 : T2196_Pos {
    u8 pad08[0x0C - 0x08]; // 0x08
    s32 count;                  // 0x0C
    Key2196_Vec* keys;          // 0x10
};

// Kind 2 (D_002196D8, 0x18 bytes): nothing read yet.
struct T2196_6D8 : T2196_Pos {
    s32 f8;                 // 0x8
    s32 fC;                 // 0xC
    s32 f10;                // 0x10
    s32 f14;                // 0x14
};

// ---------------------------------------------------------------------------------------------
// The rotation curves: an orientation over time. func_00121050 makes them, by kind 0..2.
// Slot 0 evaluates the matrix (slot 1 of kind 0 gives the orientation), slot 3 gives the key
// times (kind 0 and 1), and slot 2 reads the curve from the stream.
typedef void (*T2196_RotEval)(T2196_Rot* self, C02* owner, s32 mode, void* outRot, void* outVec, f32 key, f32 scale);
typedef void* (*T2196_RotGet)(T2196_Rot* self, u32 a1, u32 a2, u32 a3, u32 a4);
typedef void (*T2196_RotRead)(T2196_Rot* self, Stream83* stream);
typedef void (*T2196_RotTimes)(T2196_Rot* self, s32* outCount, f32** outTimes);
struct T2196_RotVt {
    T2196_RotEval eval;         // 0x00
    T2196_RotGet get;           // 0x04
    T2196_RotRead read;         // 0x08
    T2196_RotTimes times;       // 0x0C
};

struct T2196_Rot {
    const T2196_RotVt* vt;      // 0x00
    s32 kind;                   // 0x04: 0..2
};

// Kind 0 (D_002196E8, 0x30 bytes): as the position curves' kind 0, and a flag set when the
// curve ends where it began (func_0011FFD8).
struct T2196_6E8 : T2196_Rot {
    s32 closed;                 // 0x08
    u8 pad0C[0x10 - 0x0C]; // 0x0C
    Vec02 base;                 // 0x10
    T2196_Weight* axis[3];      // 0x20
    u8 pad2C[0x30 - 0x2C]; // 0x2C
};

// Kind 1 (D_002196F8, 0x14 bytes): keys as the position curves' kind 1.
struct T2196_6F8 : T2196_Rot {
    s32 closed;                 // 0x08: set by func_001201F0 as func_0011FFD8 does
    s32 count;                  // 0x0C
    Key2196_Vec* keys;          // 0x10
};

// Kind 2 (D_00219708, 0x1C bytes): nothing read yet.
struct T2196_708 : T2196_Rot {
    u8 pad08[0x1C - 0x08]; // 0x08
};

// ---------------------------------------------------------------------------------------------
// The scale curves: func_001210F0 makes them, by kind 0..1.
typedef void (*T2196_ScaleEval)(T2196_Scale* self, C02* owner, void* mode, void* out, f32 factor);
typedef void (*T2196_ScaleRead)(T2196_Scale* self, Stream83* stream);
typedef void (*T2196_ScaleTimes)(T2196_Scale* self, s32* outCount, f32** outTimes);
struct T2196_ScaleVt {
    T2196_ScaleEval eval;       // 0x00
    T2196_ScaleRead read;       // 0x04
    T2196_ScaleTimes times;     // 0x08
    void* m3;                   // 0x0C: 0
};

struct T2196_Scale {
    const T2196_ScaleVt* vt;    // 0x00
    s32 kind;                   // 0x04: 0..1
};

// Kind 0 (D_00219718, 0x30 bytes): as the position curves' kind 0.
struct T2196_718 : T2196_Scale {
    u8 pad08[0x10 - 0x08]; // 0x08
    Vec02 base;                 // 0x10
    T2196_Weight* axis[3];      // 0x20
    u8 pad2C[0x30 - 0x2C]; // 0x2C
};

// Kind 1 (D_00219728, 0x10 bytes): keys as the position curves' kind 1.
struct T2196_728 : T2196_Scale {
    s32 count;                  // 0x08
    Key2196_Vec* keys;          // 0x0C
};

typedef char check_T2196[sizeof(T2196) == 0x08 ? 1 : -1];
typedef char check_Key2196_668[sizeof(Key2196_668) == 0x18 ? 1 : -1];
typedef char check_Key2196_678[sizeof(Key2196_678) == 0x20 ? 1 : -1];
typedef char check_Key2196_688[sizeof(Key2196_688) == 0x08 ? 1 : -1];
typedef char check_Key2196_Vec[sizeof(Key2196_Vec) == 0x40 ? 1 : -1];
typedef char check_T2196_668[sizeof(T2196_668) == 0x10 ? 1 : -1];
typedef char check_T2196_678[sizeof(T2196_678) == 0x10 ? 1 : -1];
typedef char check_T2196_688[sizeof(T2196_688) == 0x10 ? 1 : -1];
typedef char check_T2196_698[sizeof(T2196_698) == 0x14 ? 1 : -1];
typedef char check_T2196_6A8[sizeof(T2196_6A8) == 0x18 ? 1 : -1];
typedef char check_T2196_6B8[sizeof(T2196_6B8) == 0x30 ? 1 : -1];
typedef char check_T2196_6C8[sizeof(T2196_6C8) == 0x14 ? 1 : -1];
typedef char check_T2196_6D8[sizeof(T2196_6D8) == 0x18 ? 1 : -1];
typedef char check_T2196_6E8[sizeof(T2196_6E8) == 0x30 ? 1 : -1];
typedef char check_T2196_6F8[sizeof(T2196_6F8) == 0x14 ? 1 : -1];
typedef char check_T2196_708[sizeof(T2196_708) == 0x1C ? 1 : -1];
typedef char check_T2196_718[sizeof(T2196_718) == 0x30 ? 1 : -1];
typedef char check_T2196_728[sizeof(T2196_728) == 0x10 ? 1 : -1];

#endif
