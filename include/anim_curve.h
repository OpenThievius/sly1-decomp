// SPDX-License-Identifier: AGPL-3.0-or-later
// Animation curves (AnimCurve): the curves of a class 0x83 (c83.h), four families of objects with a
// table of functions each. Written for this project from what retail's code does
// (config/us/tables.tsv, docs/DISC.md "Animations").
//
// Four factories make them, each by the curve's kind (stored at +4): func_00120FB0 the
// position curves (tables D_002196B8, D_002196C8, D_002196D8), func_00121050 the rotation
// curves (D_002196E8, D_002196F8, D_00219708), func_001210F0 the scale curves (D_00219718,
// D_00219728) and func_00121160 the weight curves (D_00219668 ... D_002196A8). Track83 holds
// them (func_0012B8C8). Each family has its own base table (D_00219600's words 10..25: four
// tables of four slots nothing refers to), so the families are four classes of their own, with
// no common type but the prefix every curve begins with, {table, kind}: AnimCurve.
//
// Every field line ends with its offset; the sizes are the factories' allocations.
#ifndef ANIM_CURVE_H
#define ANIM_CURVE_H

#include "placed_object.h"

struct Stream83;     // the level stream a curve is read from (func_00137D10 and friends)
struct Animation;
struct PositionCurve;
struct RotationCurve;
struct ScaleCurve;
struct WeightCurve;

// The prefix of every curve.
struct AnimCurve {
    const void* vt;         // 0x00: the family's table
    s32 kind;               // 0x04: the kind the factory was asked for
};

// ---------------------------------------------------------------------------------------------
// The weight curves: one float over time. func_00121160 makes them, by kind 0..4.

// Slot 0 evaluates at `key` (the value and its slope, either may be 0), slot 1 reads the
// curve from the stream (0 for the blends), slot 2 gives the key times (a count and a new
// array, which may be 0). The floats come right after the owner: retail's callers set $f12
// and $f13 before $a2 (func_0011F6B0).
typedef void (*WeightCurveEval)(WeightCurve* self, PlacedObject* owner, f32 key, f32 scale, s32 flags, f32* outValue, f32* outSlope);
typedef void (*WeightCurveRead)(WeightCurve* self, Stream83* stream);
typedef void (*WeightCurveTimes)(WeightCurve* self, s32* outCount, f32** outTimes);
struct WeightCurveVt {
    WeightCurveEval eval;      // 0x00
    WeightCurveRead read;      // 0x04
    WeightCurveTimes times;    // 0x08
    void* m3;                   // 0x0C: 0
};

struct WeightCurve {
    const WeightCurveVt* vt;   // 0x00
    s32 kind;                   // 0x04: 0..4
};

// A key of a kind 0 curve (D_00219668): a value with a kind (5: a constant to the next key)
// and its tangents (func_0011EFC8 reads, func_0011F0C8 evaluates).
struct TangentWeightKey {
    f32 time;               // 0x00: seconds (the stream's 1/60 s count times 1/60)
    f32 value;              // 0x04
    s32 c;                  // 0x08
    f32 d;                  // 0x0C
    s32 kind;               // 0x10
    f32 f;                  // 0x14
};

// A key of a kind 1 curve (D_00219678), with the tangents on both sides (func_0011F210).
struct ControlPointWeightKey {
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
struct LinearWeightKey {
    f32 time;               // 0x00
    f32 value;              // 0x04
};

// Kinds 0..2: a count and the keys.
struct TangentWeightCurve : WeightCurve {
    s32 count;              // 0x08
    TangentWeightKey* keys;      // 0x0C
};
struct ControlPointWeightCurve : WeightCurve {
    s32 count;              // 0x08
    ControlPointWeightKey* keys;      // 0x0C
};
struct LinearWeightCurve : WeightCurve {
    s32 count;              // 0x08
    LinearWeightKey* keys;      // 0x0C
};

// What a blend (kinds 3 and 4) is made of: an animation-like record with a length at +0x34
// and a table of (weight, record) pairs at +0xB8 (stride +0xB0, count +0xB4).
struct BlendSource {
    u8 pad00[0x34]; // 0x00
    f32 length;             // 0x34
};
struct BlendEntry {
    f32 weight;             // 0x00
    BlendSource* sub;      // 0x04
};
struct BlendConfig {
    u8 pad00[0x34]; // 0x00
    f32 length;             // 0x34
    u8 pad38[0xB0 - 0x38]; // 0x38
    s32 stride;             // 0xB0
    s32 count;              // 0xB4
    u8* base;               // 0xB8: count records of `stride` bytes (BlendEntry first)
};
struct BlendTimeScale {
    f32 a;                  // 0x00
    f32 b;                  // 0x04
};
struct BlendSequence {
    s32 stride;             // 0x00: the offset of a record's (start, scale) pairs
    s32 count;              // 0x04
    BlendTimeScale* pairs; // 0x08
};

// Kinds 3 and 4: a weighted mix of other weight curves, one for each record of the config
// (func_00120AA8 mixes angles, func_00120D58 sums values).
struct AngleBlendWeightCurve : WeightCurve {
    BlendConfig* cfg;      // 0x08
    BlendSequence* seq;      // 0x0C
    WeightCurve** targets; // 0x10: one for each record of cfg
};
struct ValueBlendWeightCurve : AngleBlendWeightCurve {
    s32 index;              // 0x14
};

// ---------------------------------------------------------------------------------------------
// The position curves: a vector over time. func_00120FB0 makes them, by kind 0..2.

// Slot 0 evaluates (owner, mode, key, scale, out value, out slope), then tells the owner
// (its slot 44); slot 1 reads the curve; slot 2 gives the key times. The floats come before
// the out pointers: retail's callers set $f12 and $f13 before $a3 (func_0011FC90).
typedef void (*PositionCurveEval)(PositionCurve* self, PlacedObject* owner, s32 mode, f32 key, f32 scale, void* outValue, void* outSlope);
typedef void (*PositionCurveRead)(PositionCurve* self, Stream83* stream);
typedef void (*PositionCurveTimes)(PositionCurve* self, s32* outCount, f32** outTimes);
struct PositionCurveVt {
    PositionCurveEval eval;         // 0x00
    PositionCurveRead read;         // 0x04
    PositionCurveTimes times;       // 0x08
    void* m3;                   // 0x0C: 0
};

struct PositionCurve {
    const PositionCurveVt* vt;      // 0x00
    s32 kind;                   // 0x04: 0..2
};

// A key of a kind 1 curve: a time and three vectors (func_0011FA88 reads it, func_0011F9F8
// evaluates it).
struct __attribute__((aligned(16))) VectorKey {
    f32 time;               // 0x00
    u8 pad04[0x10 - 0x04]; // 0x04
    Vec02 v0;               // 0x10
    Vec02 v1;               // 0x20
    Vec02 v2;               // 0x30
};

// Kind 0 (D_002196B8, 0x30 bytes): a base vector and a weight curve for each axis (func_0011F798
// reads them, func_0011F850 gathers their key times).
struct AxisPositionCurve : PositionCurve {
    u8 pad08[0x10 - 0x08]; // 0x08
    Vec02 base;                 // 0x10
    WeightCurve* axis[3];      // 0x20
    u8 pad2C[0x30 - 0x2C]; // 0x2C
};

// Kind 1 (D_002196C8, 0x14 bytes).
struct VectorKeyPositionCurve : PositionCurve {
    s32 closed;                 // 0x08: the last key is within 1.0 of the first (squared) or there is one key
    s32 count;                  // 0x0C
    VectorKey* keys;          // 0x10
};

// Kind 2 (D_002196D8, 0x18 bytes): nothing read yet.
struct PositionCurveKind2 : PositionCurve {
    s32 f8;                 // 0x8
    BlendConfig* cfg;       // 0xC: the records it mixes (func_00120470)
    BlendSequence* seq;     // 0x10: the time map, or 0
    PositionCurve** targets; // 0x14: one for each record of cfg
};

// ---------------------------------------------------------------------------------------------
// The rotation curves: an orientation over time. func_00121050 makes them, by kind 0..2.
// Slot 0 evaluates the matrix (slot 1 of kind 0 gives the orientation), slot 3 gives the key
// times (kind 0 and 1), and slot 2 reads the curve from the stream.
typedef void (*RotationCurveEval)(RotationCurve* self, PlacedObject* owner, s32 mode, void* outRot, void* outVec, f32 key, f32 scale);
typedef void* (*RotationCurveGet)(RotationCurve* self, u32 a1, u32 a2, u32 a3, u32 a4);
typedef void (*RotationCurveRead)(RotationCurve* self, Stream83* stream);
typedef void (*RotationCurveTimes)(RotationCurve* self, s32* outCount, f32** outTimes);
struct RotationCurveVt {
    RotationCurveEval eval;         // 0x00
    RotationCurveGet get;           // 0x04
    RotationCurveRead read;         // 0x08
    RotationCurveTimes times;       // 0x0C
};

struct RotationCurve {
    const RotationCurveVt* vt;      // 0x00
    s32 kind;                   // 0x04: 0..2
};

// Kind 0 (D_002196E8, 0x30 bytes): as the position curves' kind 0, and a flag set when the
// curve ends where it began (func_0011FFD8).
struct AxisRotationCurve : RotationCurve {
    s32 closed;                 // 0x08
    u8 pad0C[0x10 - 0x0C]; // 0x0C
    Vec02 base;                 // 0x10
    WeightCurve* axis[3];      // 0x20
    u8 pad2C[0x30 - 0x2C]; // 0x2C
};

// Kind 1 (D_002196F8, 0x14 bytes): keys as the position curves' kind 1.
struct KeyedRotationCurve : RotationCurve {
    s32 closed;                 // 0x08: set by func_001201F0 as func_0011FFD8 does
    s32 count;                  // 0x0C
    VectorKey* keys;          // 0x10
};

// Kind 2 (D_00219708, 0x1C bytes): nothing read yet.
struct RotationCurveKind2 : RotationCurve {
    u8 pad08[0x1C - 0x08]; // 0x08
};

// ---------------------------------------------------------------------------------------------
// The scale curves: func_001210F0 makes them, by kind 0..1.
typedef void (*ScaleCurveEval)(ScaleCurve* self, PlacedObject* owner, void* mode, void* out, f32 factor);
typedef void (*ScaleCurveRead)(ScaleCurve* self, Stream83* stream);
typedef void (*ScaleCurveTimes)(ScaleCurve* self, s32* outCount, f32** outTimes);
struct ScaleCurveVt {
    ScaleCurveEval eval;       // 0x00
    ScaleCurveRead read;       // 0x04
    ScaleCurveTimes times;     // 0x08
    void* m3;                   // 0x0C: 0
};

struct ScaleCurve {
    const ScaleCurveVt* vt;    // 0x00
    s32 kind;                   // 0x04: 0..1
};

// Kind 0 (D_00219718, 0x30 bytes): as the position curves' kind 0.
struct AxisScaleCurve : ScaleCurve {
    u8 pad08[0x10 - 0x08]; // 0x08
    Vec02 base;                 // 0x10
    WeightCurve* axis[3];      // 0x20
    u8 pad2C[0x30 - 0x2C]; // 0x2C
};

// Kind 1 (D_00219728, 0x10 bytes): keys as the position curves' kind 1.
struct KeyedScaleCurve : ScaleCurve {
    s32 count;                  // 0x08
    VectorKey* keys;          // 0x0C
};

typedef char check_AnimCurve[sizeof(AnimCurve) == 0x08 ? 1 : -1];
typedef char check_TangentWeightKey[sizeof(TangentWeightKey) == 0x18 ? 1 : -1];
typedef char check_ControlPointWeightKey[sizeof(ControlPointWeightKey) == 0x20 ? 1 : -1];
typedef char check_LinearWeightKey[sizeof(LinearWeightKey) == 0x08 ? 1 : -1];
typedef char check_VectorKey[sizeof(VectorKey) == 0x40 ? 1 : -1];
typedef char check_TangentWeightCurve[sizeof(TangentWeightCurve) == 0x10 ? 1 : -1];
typedef char check_ControlPointWeightCurve[sizeof(ControlPointWeightCurve) == 0x10 ? 1 : -1];
typedef char check_LinearWeightCurve[sizeof(LinearWeightCurve) == 0x10 ? 1 : -1];
typedef char check_AngleBlendWeightCurve[sizeof(AngleBlendWeightCurve) == 0x14 ? 1 : -1];
typedef char check_ValueBlendWeightCurve[sizeof(ValueBlendWeightCurve) == 0x18 ? 1 : -1];
typedef char check_AxisPositionCurve[sizeof(AxisPositionCurve) == 0x30 ? 1 : -1];
typedef char check_VectorKeyPositionCurve[sizeof(VectorKeyPositionCurve) == 0x14 ? 1 : -1];
typedef char check_PositionCurveKind2[sizeof(PositionCurveKind2) == 0x18 ? 1 : -1];
typedef char check_AxisRotationCurve[sizeof(AxisRotationCurve) == 0x30 ? 1 : -1];
typedef char check_KeyedRotationCurve[sizeof(KeyedRotationCurve) == 0x14 ? 1 : -1];
typedef char check_RotationCurveKind2[sizeof(RotationCurveKind2) == 0x1C ? 1 : -1];
typedef char check_AxisScaleCurve[sizeof(AxisScaleCurve) == 0x30 ? 1 : -1];
typedef char check_KeyedScaleCurve[sizeof(KeyedScaleCurve) == 0x10 ? 1 : -1];

#endif
