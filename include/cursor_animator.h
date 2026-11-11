// SPDX-License-Identifier: AGPL-3.0-or-later
// Kind 0x21E3: cursor animators, objects that move a cursor (a frame index or a pair of
// coordinates) over a record (src/main/anim_record.cpp and file_1549C8.cpp). Each is read from the
// level stream by func_001B4A10: a type (1 to 8), an
// object of func_001B4920(type) bytes on the heap whose table func_001B4980(type) is stored at
// +0 and the type at +8, then slot 0 with the 0x1C-byte block the stream holds. func_001B3040
// (anim_record.cpp) keeps the objects in D_00274540 and each owns a record (AnimRecord) it binds
// with slot 1; func_001B4878 calls slot 2 on them every frame.
//
// The 0x2C-byte base is the same for all eight tables: a frame stamp, the type, the id of the
// record, and a cursor (the animated position the object drives: a frame index, or a pair of
// texture coordinates). Each variant adds its own parameters after it. Written for this
// project from what retail's code does.
#ifndef CURSOR_ANIMATOR_H
#define CURSOR_ANIMATOR_H

#include "common.h"

struct CursorAnimator;
struct AnimRecord;
struct TextureTable;

// The 0x1C bytes slot 0 reads from the stream (func_00137A60(stream, 0x1C, block)).
struct AnimatorParams {
    s16 recordKey;          // 0x00: the record's key (func_001B4AA0)
    u16 flag;               // 0x02: nonzero sets bit 2 of the cursor's flags
    f32 f4;                 // 0x04
    union {
        f32 f8;             // 0x08
        s32 i8;             // 0x08: type 4 (func_001B5060), read as unsigned
    };
    f32 fC;                 // 0x0C
    f32 f10;                // 0x10
    union {
        u16 u14;            // 0x14: types 1 to 3, as a number
        s16 s14;            // 0x14: type 5 (func_00159680)
        f32 f14;            // 0x14: type 8 (func_001B54D0)
    };
    f32 f18;                // 0x18: type 8
};

// What a cursor writes when it moves (func_001B47C0): value = base + ((index * stride) << 4).
struct FrameSource {
    s32 stride;             // 0x00
    s32 base;               // 0x04
};
// An entry of the mesh queue (D_0027DC20, 0x4000 of them; texture_upload.cpp): func_001694A0
// copies count quadwords from value to dst and, with a flag, marks the copy's GIF tags.
struct FrameTarget {
    s32 count;              // 0x00: the quadwords to copy
    s32 value;              // 0x04: where they come from
    union {
        struct QueuedGifTags* dst;  // 0x08: where they go (func_001694A0)
        u32 dstAddr;        // 0x08: func_001696B8 moves the ones inside a range
    };
    s32 flag;               // 0x0C: or-ed into the first tag (func_001694A0)
};
struct FrameLink {
    FrameSource* src;      // 0x00
    FrameTarget* dst;       // 0x04
    FrameLink* next;       // 0x08
};

// The animated position of an object (0x1C bytes at +0x10). func_001B46E0 (a frame index) and
// func_001B4750 (a pair of coordinates) change it and link it into the list D_0027451C of the
// cursors to flush (D_00274544 is the list's first); func_001B47C0 flushes them at the end of
// the frame.
struct AnimCursor {
    s32 flags;              // 0x00: bit 0 frames, bit 1 coordinates, bit 2 set by the stream
    AnimRecord* record;     // 0x04: the record (null until it is bound)
    s32 frame;              // 0x08: the frame index
    f32 u;                  // 0x0C
    f32 v;                  // 0x10
    FrameLink* links;      // 0x14
    AnimCursor* next;     // 0x18: in the list to flush
};

struct Quad4;           // a quadword (shapes.h)

// An entry of an AnimRecord's list (func_001B3040 allocates them): a count of quadwords per
// frame and the buffer of them that func_001B3510 sends to the GIF.
struct AnimRecordEntry {
    s32 type;               // 0x00
    union {
        s32 addr;           // 0x04: func_001B3040 stores the allocation
        Quad4* data;        // 0x04: func_001B3510 reads it
    };
};

// A record of D_002744FC (0x28 bytes each, func_001B3040 reads them): func_001B4688 finds one
// by its key. Its owner is the object that binds it.
struct AnimRecord {
    u8 kind;                // 0x00
    u8 flags;               // 0x01
    s16 key;                // 0x02
    u8 pad04[0x08 - 0x04];
    u8 color[4];            // 0x08: halved into the GIF packet of a kind 4 record (func_001B3510)
    u32 maskC;              // 0x0C: a range record that links it is drawn when it has 0x10000000 or every bit of the camera's mask (func_001B2090)
    s16 linkKey;            // 0x10: the key of the record a kind 0 record takes its third pass's textures from (func_001B3510)
    u8 pad12[0x13 - 0x12];
    u8 nelem;               // 0x13: the elements at 0x14
    TextureTable* elems;    // 0x14: nelem texture tables of 0x14 bytes (func_001B2F00 reads them)
    s32 entCount;           // 0x18: the number of entries at 0x1C
    AnimRecordEntry* ents;  // 0x1C: entCount entries
    s32 count;              // 0x20: frames (the first element's second word)
    CursorAnimator* owner;  // 0x24
};

struct CursorAnimatorMethods {
    void (*load)(CursorAnimator* self, const AnimatorParams* src);   // 0x00: set up from the stream's block
    void (*bind)(CursorAnimator* self);                          // 0x04: bind the record (func_001B4AD0 caches it)
    void (*step)(CursorAnimator* self, f32 dt);                  // 0x08: step; called every frame
    f32 (*getProgress)(CursorAnimator* self);                           // 0x0C: a value in [0, 1] (func_001B4B38: 0)
    void (*followObject)(CursorAnimator* self, void* unused, void* other);  // 0x10: type 4's (func_001B5160)
    AnimCursor* (*findCursor)(CursorAnimator* self, const AnimRecord* rec);  // 0x14: the cursor of a record, or 0
    void (*getOutputs)(CursorAnimator* self, void** out);              // 0x18: type 8: pointers to its outputs
    void* m07;                                         // 0x1C
};

// The types of the table's slots, to define a table with.
typedef void (*AnimLoad)(CursorAnimator* self, const AnimatorParams* src);
typedef void (*AnimBind)(CursorAnimator* self);
typedef void (*AnimStep)(CursorAnimator* self, f32 dt);
typedef f32 (*AnimProgress)(CursorAnimator* self);
typedef void (*AnimFollow)(CursorAnimator* self, void* unused, void* other);
typedef AnimCursor* (*AnimFind)(CursorAnimator* self, const AnimRecord* rec);
typedef void (*AnimOutputs)(CursorAnimator* self, void** out);

// The base (0x2C bytes).
struct CursorAnimator {
    const CursorAnimatorMethods* methods;   // 0x00
    f32 stamp;              // 0x04: D_0026185C when last stepped (func_001B4B08)
    s32 type;               // 0x08: 1 to 8, selects the table and the size
    s32 recordKey;          // 0x0C: the key of its record
    AnimCursor cursor;      // 0x10
};

// Type 1 (table D_0021E358, 0x4C bytes): runs through the frames, then waits.
struct FrameRunAnimator : CursorAnimator {
    f32 durMin;             // 0x2C: seconds for a run, from (durMin, durMax)
    f32 durMax;             // 0x30
    f32 waitMin;            // 0x34: seconds to wait after one
    f32 waitMax;            // 0x38
    f32 rate;               // 0x3C: frames per second
    f32 pos;                // 0x40: the frame, as a float
    f32 wait0;              // 0x44: the wait chosen at binding
    f32 wait;               // 0x48: what is left of it
};

// Type 2 (D_0021E378, 0x4C): the same, forwards and back.
struct FramePingPongAnimator : CursorAnimator {
    f32 durMin;             // 0x2C
    f32 durMax;             // 0x30
    f32 waitMin;            // 0x34
    f32 waitMax;            // 0x38
    f32 rate;               // 0x3C
    f32 pos;                // 0x40
    f32 wait0;              // 0x44
    f32 wait;               // 0x48
};

// Type 3 (D_0021E398, 0x38): jumps to a random other frame after a random wait.
struct RandomJumpAnimator : CursorAnimator {
    f32 waitMin;            // 0x2C
    f32 waitMax;            // 0x30
    f32 wait;               // 0x34
};

// Type 4 (D_0021E3B8, 0x38): the frame follows the angle of another object (slot 4).
struct AngleFrameAnimator : CursorAnimator {
    f32 phase;              // 0x2C: from the stream, or random when it is the largest float
    f32 sector;             // 0x30: 2 pi over the stream's count
    f32 step;               // 0x34: sector over the number of frames
};

// Type 6 (D_0021E3D8, 0x44): scrolls the coordinates.
struct ScrollAnimator : CursorAnimator {
    f32 velU;               // 0x2C
    f32 velV;               // 0x30
    f32 wrapU;              // 0x34
    f32 wrapV;              // 0x38
    f32 mulU;               // 0x3C: 1.0 at setup (func_001B5388 sets both)
    f32 mulV;               // 0x40
};

// Type 7 (D_0021E3F8, 0x3C): moves the coordinates on a circle.
struct CircleAnimator : CursorAnimator {
    f32 omega;              // 0x2C: radians per second
    f32 radius;             // 0x30
    f32 centerU;            // 0x34
    f32 centerV;            // 0x38
};

// A point of the triangle strip a type 8 animator follows (0x10 bytes; func_001B55C0).
struct StripPoint {
    f32 x, y, z;            // 0x00
    u32 flags;              // 0x0C: 0x8000, no triangle ends at this point
};
// The texture coordinates of a point of the strip (0xC bytes; func_001B55C0 reads u and v).
struct StripCoord {
    f32 u, v;               // 0x00
    u8 pad08[0x0C - 0x08];
};

// Type 8 (D_0021E418, 0x50): the coordinates of the point where a segment between two objects
// crosses a triangle strip (slot 4, func_001B55C0), offset and clamped.
struct TriangleAnimator : CursorAnimator {
    f32 u0;                 // 0x2C: subtracted from 1 - u
    f32 v0;                 // 0x30
    f32 uMin;               // 0x34
    f32 uMax;               // 0x38
    f32 vMin;               // 0x3C
    f32 vMax;               // 0x40
    s32 count;              // 0x44: the strip's points; slot 6 returns the addresses of these three
    StripCoord* coords;     // 0x48
    StripPoint* points;     // 0x4C
};

// Type 5 (D_0021E438, 0x78): fades between two records (frames in, frames out) with a mode.
struct CrossfadeAnimator : CursorAnimator {
    f32 scale;              // 0x2C
    f32 lo;                 // 0x30
    f32 hi;                 // 0x34
    f32 limit;              // 0x38
    s32 recordKey2;         // 0x3C: the key of the second record
    AnimCursor cursor2;     // 0x40
    s32 count;              // 0x5C: the larger of the two records' frames
    s32 mode;               // 0x60: -1 at binding, 0 to 3 (func_00159770)
    f32 stamp2;             // 0x64: D_0026185C when the mode last changed
    f32 level;              // 0x68
    f32 step;               // 0x6C
    f32 pos;                // 0x70
    f32 ratio;              // 0x74
};

typedef char check_AnimatorParams[sizeof(AnimatorParams) == 0x1C ? 1 : -1];
typedef char check_AnimCursor[sizeof(AnimCursor) == 0x1C ? 1 : -1];
typedef char check_AnimRecord[sizeof(AnimRecord) == 0x28 ? 1 : -1];
typedef char check_CursorAnimator[sizeof(CursorAnimator) == 0x2C ? 1 : -1];
typedef char check_FrameRunAnimator[sizeof(FrameRunAnimator) == 0x4C ? 1 : -1];
typedef char check_FramePingPongAnimator[sizeof(FramePingPongAnimator) == 0x4C ? 1 : -1];
typedef char check_RandomJumpAnimator[sizeof(RandomJumpAnimator) == 0x38 ? 1 : -1];
typedef char check_AngleFrameAnimator[sizeof(AngleFrameAnimator) == 0x38 ? 1 : -1];
typedef char check_ScrollAnimator[sizeof(ScrollAnimator) == 0x44 ? 1 : -1];
typedef char check_CircleAnimator[sizeof(CircleAnimator) == 0x3C ? 1 : -1];
typedef char check_TriangleAnimator[sizeof(TriangleAnimator) == 0x50 ? 1 : -1];
typedef char check_CrossfadeAnimator[sizeof(CrossfadeAnimator) == 0x78 ? 1 : -1];

#endif
