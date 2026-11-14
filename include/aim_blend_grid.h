// SPDX-License-Identifier: AGPL-3.0-or-later
// Role: the player's aim blend grid: pose records on a grid of points, blended into 24 weights for the aimed point (BlendCellCornerRecords), with a plane tree that limits the aim (FindNearestAcceptedPointOnSegment).
// Class 0x8B (descriptor D_0021A7B8, 0x3F0 bytes), a child of the root: an object read from a
// level stream (func_0019C470) that is made of a grid of positions, a list of points on it, and
// triangles linked to their neighbours; after loading (func_0019C728) it finds its
// objects, fills a table of 24 slots, and measures it. Written for this project from what
// retail's code does (config/us/classes.tsv).
//
// The slots are 0x20 bytes each from 0xE4; the stream's 24 ids land in their last word
// (0xF0, stride 0x20), so the loader's own fields (0xA0..0xE0) end where the first slot starts.
#ifndef AIM_BLEND_GRID_H
#define AIM_BLEND_GRID_H

#include "base_object.h"

#include "shapes.h"   // Quad16
#include "collider.h"  // CollisionMesh

struct SlotObject;
typedef void (*SlotObjectFn)(SlotObject* n);
struct SlotObject { SlotObjectFn* vtbl; };

struct AimPlaneNode { u8* a; u8* b; u8* c; };
struct AimPlaneEdge { u8* a; u8* b; };
struct GridRecord { s32 id; u8 pos[96]; };

// An entry of a BlendAnimationView's table at +0x3C (0x1C bytes each, f38 of them), found by object id
// (FindEntryByObjectId, func_0012CCE8): the id, an object whose first method moves a body
// (func_001C8C08), and a record whose flag at 0x18 func_00139B38 sets.
struct PoseSource;
typedef void (*PoseSourceFn)(PoseSource* m, void* body, f32 x, f32 y, s32 z, void* out, s32 w);
// The sequence a mover holds at 0x10 (func_0018AE38): FindCyclicRangeIndex's pairs.
struct CyclicRanges {
    u8 pad00[0x04];
    s32 count;              // 0x04
    void* pairs;            // 0x08
};
struct PoseSource {
    PoseSourceFn* vtbl;
    u8 pad04[0x10 - 0x04];
    CyclicRanges* ranges;   // 0x10: of a clip's mover (func_0018AE38)
};
struct FlaggedSource { u8 pad[0x18]; s32 flag; };
struct BlendSourceEntry {
    s32 key;                // 0x00: the object id func_0012CCE8 matches
    PoseSource* mover;         // 0x04
    FlaggedSource* sub;         // 0x08
    u8 pad0C[0x1C - 0x0C];
};

struct AnimTiming { u8 pad[8]; f32 f8; };
struct AnimTimingRef { u8 pad[8]; AnimTiming* p8; };
struct BlendAnimationView {
    u8 pad0[0x34];
    f32 blendedDuration;    // 0x34: the duration of the blend
    s32 sourceCount;        // 0x38: number of entries of the table at f3C
    u8* sourceTable;        // 0x3C: the table of BlendSourceEntry, 0x1C bytes each
    u8 pad40[0x6C - 0x40];
    void* playerList;       // 0x6C: head of the list of playing animation players
    u8 pad70[0x78 - 0x70];
    s32 f78;                // 0x78
    f32 f7C;                // 0x7C: a scale of the poses (func_0012CD78, with f98)
    u8 pad80[0x98 - 0x80];
    f32 f98;                // 0x98
    u8 pad9C[0xB8 - 0x9C];
    void* itemWeights;      // 0xB8: the item weights buffer
    s32 sequenceCount;      // 0xBC: number of key sequences of pC0
    AnimTimingRef* pC0;              // 0xC0
};

// Samples the chain of objects from o up to top (not included) at time t and scale: the n
// positions, rotations, velocities and spins, each output optional (placed_object.cpp). The
// floats come after self: SampleScriptAnimation's argument moves need that order.
struct PlacedObject;
struct Vec4;
struct Mat3;
void SampleAnimationFrameChain(BlendAnimationView* self, f32 t, f32 scale, PlacedObject* o, PlacedObject* top, s32 n, Vec4* pos, Mat3* rot,
                   Vec4* vel, Vec4* spin);

struct GridBlendSlot {
    u8 pad0[4];
    SlotObject* object;         // 0x04: the object named by the id
    u8 pad8[4];
    s32 id;                 // 0x0C: the id read from the stream
    u8 pad10[0x10];
};

struct AimBlendGrid : BaseObject {
    s32 first34;            // 0x34: -1 at construction
    s32 second38;           // 0x38: -1 at construction
    void* rootObject;       // 0x3C
    void* sampledObject;    // 0x40
    u8 pad44[0x48 - 0x44];
    s32 resolution;         // 0x48: grid size, read from the stream
    u8 pad4C[0x50 - 0x4C];
    s32 f50;                // 0x50
    f32 blendX;             // 0x54
    f32 blendY;             // 0x58
    f32 blendZ;             // 0x5C
    f32 sampleTime;         // 0x60
    u8 pad64[0x70 - 0x64];
    Quad16 blendPoint;      // 0x70
    s32 hasSecondVector;    // 0x80
    f32 secondBlendX;       // 0x84
    f32 secondBlendY;       // 0x88
    f32 secondBlendZ;       // 0x8C
    Quad16 originPoint;     // 0x90
    CollisionMesh mesh;            // 0xA0: the grid's points (vertCount, verts at 0xA8) and faces (0xB0), as read by func_00137FB0
    GridRecord* pointRecords;    // 0xC4: fA4 records of 100 bytes
    s32 cellCount;          // 0xC8
    u8* cells;              // 0xCC: fC8 records of 16 bytes
    s32 nodeCount;          // 0xD0
    s32 fD4;                // 0xD4
    AimPlaneNode* nodes;           // 0xD8
    AimPlaneEdge* leaves;         // 0xDC
    f32 fE0;                // 0xE0
    GridBlendSlot slots[24];       // 0xE4
    BlendAnimationView* blendAnimation;   // 0x3E4
    u8 pad3E8[0x3F0 - 0x3E8];
};

typedef char check_AimBlendGrid[sizeof(AimBlendGrid) == 0x3F0 ? 1 : -1];

void InitAimBlendGrid(AimBlendGrid* self);                  // 0x8B slot 0
// func_0019C470 (slot 10) takes the level stream the source file declares.
void StartAimBlendGrid(AimBlendGrid* self);                  // 0x8B slot 16

#endif
