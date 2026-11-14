// SPDX-License-Identifier: AGPL-3.0-or-later
// The records the placed objects' model builders and attachments read (placed_object_model.cpp,
// and the declarations of game_progress.cpp, whose range holds the same prototypes): the mesh
// build state, a strip mesh's owner and info, the attachment lists and a part's packets.
#ifndef MODEL_BUILD_H
#define MODEL_BUILD_H

#include "common.h"
#include "placed_object.h"

struct CursorHook;
struct PartRange;
struct AttachmentHandler;
struct AttachmentPart;

struct MeshBuildState {
    u8 pad00[0x40];
    s32 nweights;
};
struct StripMeshInfo {
    u8 pad00[0x10];
    s32 extraCount;
    s32 f14;
    s32 f18;
};
struct StripMeshOwner {
    u8 pad00[0x18];
    s32 lit;
    u8 pad1C[0x28 - 0x1C];
    s32 skinned;
    u8 pad2C[0x38 - 0x2C];
    CursorHook* animator;
    u8 pad3C[0x40 - 0x3C];
    f32 fogBias;
    u8 pad44[0x54 - 0x44];
    StripMeshInfo* link;
};
struct StripExtra {
    s32 positions;
    s32 a4[4];
    s32 a14[4];
    s32 a24[4];
};

struct AttachmentEntry { u8 pad0[0x38]; AttachmentHandler* handler; u8 pad1[0x70 - 0x3C]; };
struct AttachmentNode { u8 pad0[4]; void* attachment; s32 targetId; u8 pad1[0x80 - 0xC]; AttachmentNode* next80; };
struct AttachmentBlock { u8 pad0[0xC]; s32 count0C; AttachmentEntry* entries; u8* chainData; u8 pad1[0x4C - 0x18]; AttachmentNode* nodes; };

typedef void (*AnimatorStepFn)(void* self, f32 f);
struct AnimatorStep {
    AnimatorStepFn* vtbl;
    u8 pad4[0x8];
    void* oscillator;
    u8 pad10[0x70];
    AnimatorStep* next80;
};

struct PartPacketContext { u8 pad0[0x28]; s32 skinned; };
struct PartPacketSource { u8 pad0[0x18]; u8* mesh; PartRange* unpack; };
struct PartPackets { void* firstQwc; void* firstBuffer; void* firstUnpackCursor; void* secondQwc; void* secondBuffer; void* secondUnpackCursor; };

struct AttachmentLink { PlacedObject* owner; AttachmentLink* p4; u8 pad8[0x48]; void* p50; void* p54; u8 pad58[0x28]; AttachmentLink* next; u8 pad84[0xC]; };
struct ParentFrame { Mat3 rot; Vec4 pos; };

#endif
