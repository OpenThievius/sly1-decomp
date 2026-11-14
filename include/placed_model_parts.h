// SPDX-License-Identifier: AGPL-3.0-or-later
// Records of the placed-object model code (attachments, framed objects, strips, quad helpers).
#ifndef PLACED_MODEL_PARTS_H
#define PLACED_MODEL_PARTS_H

#include "common.h"
#include "model_build.h"

struct RefItem { u8 pad[0x38]; void* ref; u8 rest[0x70 - 0x3C]; };
struct RefOwner
{
    u8 pad0[0xC];
    s32 count;
    RefItem* items;
    u8 pad1[0x50 - 0x14];
    s32 capacity;
    void** refs;
};
extern "C" void* FillMemory(void* p, s32 value, s32 size);
struct MorphTargetHeader
{
    u16* p;
    s32 count;
};
struct ColorWord
{
    union {
        struct { u8 r, g, b, a; };
        u32 rgba;
    };
    ColorWord(u32 v) { rgba = v; }
};
struct QuadClear
{
    static void Clear(u32* q)
    {
        FillMemory(q, 0, 0x10);
    }
};
struct __attribute__((packed)) BatchVertexWords {
    u64 q0;
    u64 q8;
    u64 q10;
    u64 q18;
    s32 f20;
    s32 value;
    BatchVertexWords() {}
};
struct CopiedGifTags { u32 w[8]; };
struct ByteSpan { u8 b[1]; };
struct MeshUv {
    f32 u;
    f32 v;
};
struct VertexRefs {
    u8 pos;
    u8 nrm;
    u8 uv;
    u8 flags;
};
struct WeightIndices {
    u16* pos;
    u16* nrm;
};
struct CursorHook;
typedef AnimCursor* (*CursorHookFn)(CursorHook* self, StripMesh* mesh);
struct CursorHook {
    CursorHookFn* vt;
};
struct StripUnpack {
    u16 off[4];
    u16 strip[4];
    u16 f10;
    u16 f12;
    u16 pad14[2];
};
struct StripHeader {
    u8 pad00[0x14];
    u32 f14;
    u8 pad18[0x1C - 0x18];
    StripUnpack* p;
    StripExtra* extra;
    s32 count;
};
typedef void (*AttachmentHandlerFn)(void* self);
struct AttachmentHandler { AttachmentHandlerFn* vtbl; };
struct QuadMatrix { Quad16 q[4]; };
struct TargetObject { u8 pad0[0x110]; u8 sub110[0x30]; u8 sub140[0x40]; };
struct AttachmentTarget { TargetObject* p0; u8 pad0[0xC]; QuadMatrix m; u8 tail[0x90 - 0x50]; };
struct AttachmentTargets { s32 count; AttachmentTarget* elems; s32* keys; };
struct AnimatorOwner {
    u8 pad0[0x4C];
    AnimatorStep* head4C;
};
struct PartRange { u16 lo; u16 hi; };
struct AttachmentPartInfo { u8 pad[0x10]; u32 flags; };
struct AttachmentPart { u8 pad[0x38]; AttachmentPartInfo* a; u8 pad3C[0x18]; void* b; };
struct AttachmentCopy { s32 n0; void* p4; u8 pad8[4]; s32 count; AttachmentPart* recs; void* p14; u8 pad18[0x28]; s32 n40; void* p44; u8 pad48[4]; AttachmentLink* head; s32 f50; };
struct FramedObject;
typedef void (*FramedObjectFn)(FramedObject* self);
struct FramedObjectVt { u8 pad[0xC0]; FramedObjectFn f; };
struct FrameLinkConstraint { u8 pad0[0x60]; QuadMatrix m60; u8 pad[4]; s32 a4; u8 pad2[8]; u32 flags; };
struct FramedObject { FramedObjectVt* vt; u8 pad0[0x10C]; u8 sub110[0x30]; u8 sub140[0x40]; u8 pad180[0xA4]; FrameLinkConstraint* link; };
struct FramedAttachment { FramedObject* obj; u8 pad[0xC]; Quad16 q10[4]; QuadMatrix m50;  };
struct FramedAttachmentList { s32 count; FramedAttachment* items; };
struct PacketSlot {
    u8 pad[0x24];
};
struct QuadLanes {
    f32 x[4];
    f32 y[4];
    f32 z[4];
    f32 w[4];
};

#endif
