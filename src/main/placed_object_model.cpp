// SPDX-License-Identifier: AGPL-3.0-or-later
// The placed objects' models, 0x162890 to 0x167D68 (its .rodata from 0x24A710, its .data from
// 0x2623E0): ReadPlacedObjectModel reads a model from the level stream, the strip-mesh and
// morph-target packet builders, the attachments (start, bind, copy, update, their DMA chain),
// UpdateLinkConstraint and DrawModelPart, ending with the static initialiser that builds the
// default colour D_002623E0 (config/us/generated.tsv). Its .rodata provably starts a file:
// game_progress.cpp's range holds the GIF writer's GCC vtable D_0024A6F8 (its one virtual is
// CloseGifTag), and after it ReadPlacedObjectModel's FLT_MAX at 0x24A710 and the jump tables of
// BuildStripMeshPacket and DrawModelPart; GCC 2.95 writes a file's vtables after all of its
// functions' literals and jump tables (docs/AGENT_WORKFLOW.md, "Finding and proving a file"),
// so the vtable ends game_progress.cpp's .rodata. Its start in the code is a choice: any function
// start from 0x1612E8 (after CloseGifTag) to 0x162890 links to the same bytes, since the
// functions between read no .rodata or .data of either file. The cut is at
// ReadPlacedObjectModel, where this file's data provably begins (gauge_manager.cpp's precedent);
// the vertex batch before it (0x1619C0 to 0x162890) could belong to either file or to a third.
// The name is ours, after its role.
#include "common.h"
#include "cone_volume.h"
#include "attachment.h"
#include "id_lookup_object.h"
#include "placed_object.h"
#include "model_build.h"
#include "world.h"
#include "animation.h"
#include "sound_record.h"
#include "asm_func.h"
#include "vu0.h"
#include "collider.h"
#include "list_iter.h"
#include "packet_writer.h"
#include "game_progress.h"
#include "screen_fade.h"
#include "keyed_entry.h"
#include "identity_key.h"
#include "strip_mesh.h"
#include "vertex_batch.h"
#include "shapes.h"
#include "word_copy.h"
#include "camera.h"
#include "object_finder.h"
#include "functions/camera.h"
#include "functions/game_progress.h"
#include "functions/link_constraint.h"
#include "functions/matrix.h"
#include "functions/oscillator.h"
#include "functions/pooled_object.h"
#include "functions/range_record.h"
#include "functions/texture_upload.h"
#include "functions/warp_menu.h"
struct NodeAttachment;
struct NodeOwner;
struct Oscillator;


void* AllocateFrontMemory(s32 size);


void* AllocateFrontMemory(s32 size);

#include "placed_model_parts.h"






extern World* g_currentWorld;


void PushBackMemoryMark(void);
u8* AllocateBackMemory(s32 size);
void PopBackMemoryMark(void);

extern u8 g_flushBatchProgram[];
extern u8 g_stripMeshMode1Program[];

void WriteVifMscal(void* s, s32 n);

extern u8 g_morphTargetMode0Program[];
extern u8 g_morphTargetMode1Program[];

void WriteVifMscal(void* s, s32 n);

extern u8 g_morphTargetMode0Program[];
extern u8 g_morphTargetMode1Program[];

void WriteVifMscal(void* obj, void* data);

extern u8 g_flushBatchProgram[];
extern u8 g_stripMeshMode1Program[];

void WriteVifMscal(void* obj, void* text);

extern u8 g_flushBatchProgram[];
extern u8 g_stripMeshMode1Program[];

void WriteVifMscal(void* s, s32 n);

extern u8 g_morphTargetMode0Program[];
extern u8 g_morphTargetMode1Program[];

void WriteVifMscal(void* s, s32 n);

// EXACT: self->block store ahead of self->f20 store.


// Built at startup: the compiler's initialiser and constructor for this file are func_00167D20
// and func_00167D48 (config/us/generated.tsv).

extern u8 g_morphTargetBlendProgram[];
extern u8 g_morphTargetTailProgram[];
extern u8 g_morphTargetEndProgram[];

extern "C" void* FillMemory(void* p, s32 value, s32 size);
void WriteVifMscal(PacketWriter* s, void* data);
void WriteMorphTargetMscal(s32 mode, void* obj);



extern PacketWriter g_vifPacketWriter;
extern u8 g_flushBatchProgram[];

void FlipVifBaseOffset(void);



void CopyMemory(void* dst, void* src, u32 size);


extern "C" void* FillMemory(void* p, s32 value, s32 size);
extern u8 g_unlitBatchProgram[];
extern u8 g_unlitBatchFinishProgram[];
void CopyMemory(void* dst, void* src, u32 size);

// A run of bytes, for the fill and copy calls.


extern u8 g_litBatchProgram[];
extern u8 g_litBatchSecondProgram[];
extern u8 g_litBatchThirdProgram[];
extern u8 g_litBatchFinishProgram[];

extern "C" void* FillMemory(void* p, s32 value, s32 size);
void WriteVifMscal(PacketWriter* s, void* data);
void WriteVifMscalf(PacketWriter* s, void* data);
void AddDmaRefTag(PacketWriter* s, s32 n, void* data);
void CopyMemory(void* dst, void* src, u32 size);


// A vertex's indices into the position, normal and uv arrays, and its flags.

// A weight's two index lists: the positions it moves, then the normals.

extern u8 g_unlitBatchFinishProgram[];
extern u8 g_unlitBatchProgram[];
extern u8 g_unlitKind4BatchFinishProgram[];
extern u8 g_unlitKind4BatchProgram[];
extern u8 g_nodeLinkProgram[];
extern u8 g_skinWeightProgram[];
extern u8 g_positionDeltaProgram[];
extern u8 g_extraStreamFirstProgram[];
extern u8 g_unlitExtraStreamSecondProgram[];

extern "C" void* FillMemory(void* p, s32 value, s32 size);
void WriteVifMscal(PacketWriter* s, void* data);
void WriteVifMscalf(PacketWriter* s, void* data);
void WriteVifUnpack(PacketWriter* s, s32 a, s32 b, s32 c, s32 d, s32* out);
void* AllocateZeroedFrontMemory(s32 bytes);
void WriteStripMeshMscal(s32 mode, void* obj);




void BuildAttachmentDmaChain(void* self, void* entry, void* sub, void* ctx);

// Four quadwords: a matrix as the attachment code copies it.





QuadMatrix MultiplyMatrices(const QuadMatrix& a, const QuadMatrix& b);






s32 ClaimAnimatorStep(CursorAnimator* a0);

extern u8 g_litBatchFinishProgram[];
extern u8 g_litBatchSecondFinishProgram[];


void CopyMemory(void* dst, void* src, u32 size);
void* AllocateZeroedFrontMemory(s32 n);
void* CopyToFrontMemory(s32 size, void* src);
void CopyAttachmentPart(AttachmentCopy* o, void* a, void* b);

// Index written (i << 4) * 9: a plain &items[i] gives a mult that loop.c does not strength-reduce (no s4 offset giv).

QuadMatrix MultiplyMatrices(QuadMatrix a, void* q);

// The lit strip builder's packets: 0x24-byte slots, written two apart.



extern u8 g_litBatchProgram[];
extern u8 g_litBatchThirdProgram[];
extern u8 g_skinWeightProgram[];
extern u8 g_litSkinWeightProgram[];
extern u8 g_positionDeltaProgram[];
extern u8 g_normalDeltaProgram[];
extern u8 g_normalDeltaFinishProgram[];
extern u8 g_nodeLinkProgram[];
extern u8 g_extraStreamFirstProgram[];
extern u8 g_litExtraStreamSecondProgram[];

extern "C" void* FillMemory(void* p, s32 value, s32 size);
void WriteVifMscal(PacketSlot* s, void* data);
void WriteVifUnpack(PacketSlot* s, s32 a, s32 b, s32 c, s32 d, s32* out);
void* AllocateZeroedFrontMemory(s32 bytes);
void WriteStripMeshMscal(s32 mode, void* obj);
void WriteStripMeshMscal(s32 mode, void* obj);
void WriteMorphTargetMscal(s32 mode, void* obj);
void BuildMorphTargetPacket(MeshBuildState* self, s32 mode, MorphTargetHeader* hdr, s32 n, Vec3* vecs, s32 extra,
                   void* extraData, WeightIndices* ents, Vec3* verts, void* data, PacketWriter* pkt);
void BuildStripMeshPacket(MeshBuildState* self, StripMeshOwner* obj, s32 mode, StripHeader* hdr, StripMesh* mesh,
                   Vec3* vecs, Vec3* nrms, u8 (*tints)[4], MeshUv* uvs, s32 n, VertexRefs* recs,
                   WeightIndices* ents, Vec3* verts, Vec3* vnrms, f32* weights, PacketWriter* pkt,
                   s32** outs);
void BuildLitStripMeshPacket(MeshBuildState* self, StripMeshOwner* obj, s32 unused2, s32 mode, StripHeader* hdr,
                   StripMesh* mesh, Vec3* vecs, Vec3* nrms, u8 (*tints)[4], MeshUv* uvs,
                   s32 n, VertexRefs* recs, WeightIndices* ents, Vec3* verts, Vec3* vnrms,
                   f32* weights, PacketSlot* pkt, s32** outs);
void BuildPartVifPackets(PartPacketContext* a, PartPacketSource* b, PartPackets* c);
void StartAttachments(AttachmentBlock* self, PlacedObject* ctx);
void BindAttachmentTargets(AttachmentTargets* self, PlacedObject* ctx);
void CopyAttachmentBlock(AttachmentCopy* self, PlacedObject* owner, void* src);
void UpdateAttachments(AnimatorOwner* self, PlacedObject* sub, f32 f);
void UpdateLinkConstraint(PlacedObject* self);
void UpdateAttachmentFrames(PlacedObject* self, ParentFrame* par);
void FlipVifBaseOffset(void);

extern u8* g_camera;

// The lights a batch is lit by: CollectLightsForSphere (main_loop.cpp) takes the world, the
// sphere's centre in a1 and its radius in $f12, which this function passes on untouched (the
// caller, trail_ribbon.cpp's builder, sets both), then a mask, a maximum and the three outputs.
struct LightObject;
s32 CollectLightsForSphere(World* world, const Vec4* centre, f32 radius, u32 skipMask, s32 maxLights, s32* flagged, s32* outCount,
                  LightObject** out);


// A packet buffer this reader fills (0x24 bytes: the three are 0x24 apart).
struct ModelPacket {
    u8* end;
    u8* begin;
    s32* f08;
    u8* cur;
    u8 pad10[0x24 - 0x10];
};

// A placed object's model, read from the level stream (func_00162890).
struct ModelLink;
struct ModelPart;
struct ModelStrip;
struct ModelRecord;

// The 0x90-byte record a part with flag 0x100 links to its model.
struct ModelLink {
    PlacedObject* owner;    // 0x00
    ModelPart* part;        // 0x04
    s32 id;                 // 0x08
    u8 pad0C[4];
    s32 extraCount;         // 0x10
    s32 f14;                // 0x14
    s32 f18;                // 0x18
    u8 pad1C[4];
    s32 bone;               // 0x20
    f32 f24;                // 0x24
    f32 f28;                // 0x28
    f32 f2C;                // 0x2C
    f32 f30;                // 0x30
    u8 pad34[0xC];
    u8 matrix[0x40];        // 0x40
    ModelLink* next;        // 0x80
    u8 pad84[0xC];
};

struct ModelAnimator;
struct ModelAnimatorVt {
    void* slots[6];
    void (*bind)(ModelAnimator* self, s32** outs, ModelRecord* model, ModelPart* part, ModelStrip* strip);
};
struct ModelAnimator { ModelAnimatorVt* vt; };

// One strip of a part's mesh.
struct ModelStrip {
    Vec3 pos;               // 0x00
    u8 pad0C[4];
    f32 radius;             // 0x10
    s32 f14;                // 0x14
    StripMesh* mesh;        // 0x18
    StripUnpack* unpack;    // 0x1C
    StripExtra* extra;      // 0x20
    s32 nkeys;              // 0x24
    s32 keys[4];            // 0x28
    s32 qwc[3];             // 0x38
    u32 addr[3];            // 0x44
};

// One morph target of a part.
struct ModelMorph {
    u16* p;                 // 0x00
    s32 nkeys;              // 0x04
    s32 keys[4];            // 0x08
    s32 qwc;                // 0x18
    u32 addr;               // 0x1C
};

struct __attribute__((aligned(16))) ModelPart {
    Vec3 pos;               // 0x00
    u8 pad0C[4];
    f32 f10;                // 0x10
    s32 f14;                // 0x14
    u8 pad18[4];
    f32 far;                // 0x1C
    f32 near;               // 0x20
    f32 f24;                // 0x24
    s32 f28;                // 0x28
    s32 f2C;                // 0x2C
    f32* vecs;              // 0x30
    s32 f34;                // 0x34
    ModelAnimator* animator;    // 0x38
    f32 f3C;                // 0x3C
    f32 fog[4];             // 0x40
    f32 f50;                // 0x50
    ModelLink* link;        // 0x54
    s32 nstrips;            // 0x58
    ModelStrip* strips;     // 0x5C
    s32 nmorphs;            // 0x60
    ModelMorph* morphs;     // 0x64
    void* matrix;           // 0x68
    u8 pad6C[4];
};

// A strip's packets (BuildPartVifPackets fills the first six words).
struct StripPackets {
    void* firstQwc;
    void* firstBuffer;
    void* firstUnpackCursor;
    void* secondQwc;
    void* secondBuffer;
    void* secondUnpackCursor;
    u8 pad18[0x18];
};

struct ModelPose {
    u32 f0;                 // 0x00
    StripPackets* packets;  // 0x04
    u8 pad08[8];
    f32 f10;                // 0x10
    u8 pad14[0x14];
};

struct ModelRecord {
    s32 nids;               // 0x00
    void* links;            // 0x04
    s32* ids;               // 0x08
    s32 count;              // 0x0C
    ModelPart* parts;       // 0x10
    ModelPose* poses;       // 0x14
    u8 pad18[0x28];
    s32 nweights;           // 0x40
    void* weights;          // 0x44
    void* weightsCopy;      // 0x48
    ModelLink* head;        // 0x4C
    s32 nanimators;         // 0x50
};


// A packet buffer of the model reader, set up where it is declared.
struct StripPacket : ModelPacket {
    StripPacket() { InitPacketWriter((PacketWriter*)this); }
};

struct StripOutputs {
    s32* p[3];
    StripOutputs() { FillMemory(this, 0, sizeof(*this)); }
};

// A pointer into a packet buffer moved with its copy.
// Its arguments are in RemapMeshQueueValues's order (size, start, to).
struct MovedPointer {
    static void Fix(s32* p, u32 size, u32 start, u32 to)
    {
        if (p) {
            u32& v = *(u32*)p;
            if (v >= start && v < start + size)
                v += to - start;
        }
    }
};

struct BufferedStream;
s32 ReadBufferedU8(BufferedStream* self);
s32 ReadBufferedU16(BufferedStream* self);
s32 ReadBufferedS16(BufferedStream* self);
s32 ReadBufferedS8(BufferedStream* self);
u32 ReadBufferedU32(BufferedStream* self);
f32 ReadBufferedFloat(BufferedStream* r);
void ReadBufferedStreamBytes(BufferedStream* self, s32 remaining, void* out);
void ReadBufferedMatrix4(BufferedStream* self, void* out);
struct BufferedStream;
void ReadBufferedVector3(BufferedStream* src, void* dst);
void ReadBufferedVector4(BufferedStream* self, void* out);
void AlignBufferedStreamPosition(BufferedStream* self, s32 n);
ModelAnimator* ReadAnimator(void* stream);
void CopyAttachmentPart(AttachmentCopy* owner, void* partp, void* recp);
void BuildStripMeshPacket(MeshBuildState* self, StripMeshOwner* obj, s32 mode, StripHeader* hdr, StripMesh* mesh,
                   Vec3* vecs, Vec3* nrms, u8 (*tints)[4], MeshUv* uvs, s32 n, VertexRefs* recs,
                   WeightIndices* ents, Vec3* verts, Vec3* vnrms, f32* weights, PacketWriter* pkt,
                   s32** outs);
void BuildLitStripMeshPacket(MeshBuildState* self, StripMeshOwner* obj, s32 unused2, s32 mode, StripHeader* hdr,
                   StripMesh* mesh, Vec3* vecs, Vec3* nrms, u8 (*tints)[4], MeshUv* uvs,
                   s32 n, VertexRefs* recs, WeightIndices* ents, Vec3* verts, Vec3* vnrms,
                   f32* weights, PacketSlot* pkt, s32** outs);
void BuildMorphTargetPacket(MeshBuildState* self, s32 mode, MorphTargetHeader* hdr, s32 n, Vec3* vecs, s32 extra,
                   void* extraData, WeightIndices* ents, Vec3* verts, void* data, PacketWriter* pkt);
void BuildPartVifPackets(PartPacketContext* a, PartPacketSource* b, PartPackets* c);
extern s32 g_meshQueueCount;
extern u8* g_animRecords;

// The file's .data, in retail's order, from 0x2623E0.
ColorWord g_defaultModelColor(0x80101010);
s32 D_002623E4 = 1;
s32 g_morphStmasks[6] = { 0, 1414812756, 1347440720, 1077952576, 0, 0 };
s32 g_morphUnpackAddresses[6] = { -1, 0, 4, 8, 12, 0 };
s32 g_stripStmasks[6] = { 0, 1414812756, 1347440720, 1077952576, 0, 0 };
s32 g_stripUnpackAddresses[6] = { -1, 0, 4, 8, 12, 0 };
s32 g_litStripStmasks[6] = { 0, 1414812756, 1347440720, 1077952576, 0, 0 };
s32 g_litStripUnpackAddresses[5] = { -1, 0, 4, 8, 12 };
s32 D_00262474 = 0x28;

// Reads a placed object's model from the stream and builds its draw packets; everything is
// allocated in front memory, the per-strip scratch in back memory (marked and popped per strip).
//  1. Header: two bytes (the first becomes each new part's default f28, the second is passed to
//     the lit strip builder), the id count, a link table (0x90 bytes per id) and the ids
//     (s16 each), then the weight table (count byte, raw words, and a front-memory copy).
//  2. Parts (a u16 count; 0x70-byte parts and 0x28-byte poses, in parallel). Each starts with a
//     flag word: bit 0 copies another part and pose by index and reads a new matrix, otherwise the
//     defaults are set (far 1e10, near 2000, f24 = float max); the optional fields follow in order,
//     0x02 a word of the pose, 0x200 f50, 0x04 a scale (stored squared with its sign kept, float
//     max kept as is), 0x08 f3C, 0x10 far, 0x20 near (float max means the default; near is then
//     clamped to far), 0x40 an animator (counted in nanimators), 0x80 two vectors, 0x100 a
//     link record (owner, id, bone and, when the bone is not -1, four floats and a matrix, three
//     counts), pushed on the model's link list. Then the part's position, f10, an ignored s16,
//     three bytes, and the camera's fog terms for the part.
//  3. A copied part calls CopyAttachmentPart and is done. Otherwise it reads its strips: for each
//     (0x50 bytes) the vectors, normals, tints, UVs and vertex refs, the mesh record (from
//     g_animRecords), up to nkeys morph key weights and, when the model has weights, per-vertex
//     weight indices; it then binds the part's animator, builds the strip's packets in three
//     temporary buffers (BuildLitStripMeshPacket for mesh kind 0, BuildStripMeshPacket for the
//     other kinds), detaches each into front memory and fixes every pointer into the moved
//     packets (the mesh queue, the animator outputs and the strip's extra tables), and builds the
//     VIF packets of the strip.
//  4. Then the part's morph targets (32 bytes each): vectors, extra words, key weights and weight
//     indices, built by BuildMorphTargetPacket the same way.
//  5. At the end CollectNonNullRefs gathers the model's references.
void ReadPlacedObjectModel(ModelRecord* self, void* stream, PlacedObject* owner)
{
    s32 i;
    s32 a;
    s32 b;

    self->nanimators = 0;
    a = ReadBufferedU8((BufferedStream*)stream);
    b = ReadBufferedU8((BufferedStream*)stream);
    self->nids = ReadBufferedU8((BufferedStream*)stream);
    self->links = AllocateZeroedFrontMemory(self->nids * 0x90);
    self->ids = (s32*)AllocateZeroedFrontMemory(self->nids * 4);
    for (s32 n = 0; n < self->nids; n++) {
        self->ids[n] = ReadBufferedS16((BufferedStream*)stream);
    }
    self->nweights = ReadBufferedU8((BufferedStream*)stream);
    self->weights = AllocateZeroedFrontMemory(self->nweights * 4);
    ReadBufferedStreamBytes((BufferedStream*)stream, self->nweights * 4, self->weights);
    self->weightsCopy = CopyToFrontMemory(self->nweights * 4, self->weights);
    self->count = ReadBufferedU16((BufferedStream*)stream);
    self->parts = (ModelPart*)AllocateZeroedFrontMemory(self->count * 0x70);
    self->poses = (ModelPose*)AllocateZeroedFrontMemory(self->count * 0x28);
    for (i = 0; i < self->count; i++) {
        ModelPart* part = &self->parts[i];
        ModelPose* pose = &self->poses[i];
        s32 j;
        s32 k;
        s32 flags = ReadBufferedU16((BufferedStream*)stream);
        if (flags & 1) {
            s32 idx = ReadBufferedS16((BufferedStream*)stream);
            *part = self->parts[idx];
            *pose = self->poses[idx];
            part->matrix = AllocateFrontMemory(0x40);
            ReadBufferedMatrix4((BufferedStream*)stream, part->matrix);
        } else {
            part->far = 1.0e10f;
            part->near = 2000.0f;
            part->f24 = 3.402823466e+38f;
            part->f3C = 1.0f;
            part->f50 = 1.0f;
            part->f28 = a;
            pose->f10 = 1.0f;
        }
        s32 copied = flags & 1;
        s32 hasWord = flags & 2;
        s32 hasF50 = flags & 0x200;
        s32 hasScale = flags & 4;
        s32 hasF3C = flags & 8;
        s32 hasFar = flags & 0x10;
        s32 hasNear = flags & 0x20;
        s32 hasAnimator = flags & 0x40;
        s32 hasVecs = flags & 0x80;
        s32 hasLink = flags & 0x100;
        if (hasWord) {
            pose->f0 = ReadBufferedU32((BufferedStream*)stream);
        }
        if (hasF50) {
            part->f50 = ReadBufferedFloat((BufferedStream*)stream);
        }
        if (hasScale) {
            f32 v = ReadBufferedFloat((BufferedStream*)stream);
            if (v == 3.402823466e+38f) {
                part->f24 = 3.402823466e+38f;
            } else {
                part->f24 = v * __builtin_fabsf(v);
            }
        }
        if (hasF3C) {
            part->f3C = ReadBufferedFloat((BufferedStream*)stream);
        }
        if (hasFar) {
            part->far = ReadBufferedFloat((BufferedStream*)stream);
            if (part->far == 3.402823466e+38f) {
                part->far = 1.0e10f;
            }
        }
        if (hasNear) {
            part->near = ReadBufferedFloat((BufferedStream*)stream);
            if (part->near == 3.402823466e+38f) {
                part->near = 2000.0f;
            }
        }
        part->near = part->far <? part->near;
        if (hasAnimator) {
            part->animator = ReadAnimator(stream);
            self->nanimators++;
        }
        if (hasVecs) {
            part->vecs = (f32*)AllocateFrontMemory(0x20);
            ReadBufferedVector3((BufferedStream*)stream, part->vecs);
            ReadBufferedVector4((BufferedStream*)stream, part->vecs + 4);
        } else {
            part->vecs = 0;
        }
        if (hasLink) {
            ModelLink* link = (ModelLink*)AllocateZeroedFrontMemory(0x90);
            link->owner = owner;
            link->part = part;
            link->id = ReadBufferedS16((BufferedStream*)stream);
            link->bone = ReadBufferedS8((BufferedStream*)stream);
            if (link->bone != -1) {
                link->f24 = ReadBufferedFloat((BufferedStream*)stream);
                link->f28 = ReadBufferedFloat((BufferedStream*)stream);
                link->f2C = ReadBufferedFloat((BufferedStream*)stream);
                link->f30 = ReadBufferedFloat((BufferedStream*)stream);
                ReadBufferedMatrix4((BufferedStream*)stream, link->matrix);
            }
            link->extraCount = ReadBufferedU8((BufferedStream*)stream);
            link->f14 = ReadBufferedU8((BufferedStream*)stream);
            link->f18 = ReadBufferedU8((BufferedStream*)stream);
            part->link = link;
            link->next = self->head;
            self->head = link;
        } else {
            part->link = 0;
        }
        ReadBufferedVector3((BufferedStream*)stream, part);
        part->f10 = ReadBufferedFloat((BufferedStream*)stream);
        ReadBufferedS16((BufferedStream*)stream);
        part->f34 = ReadBufferedU8((BufferedStream*)stream);
        part->f14 = ReadBufferedU8((BufferedStream*)stream);
        part->f2C = ReadBufferedU8((BufferedStream*)stream);
        ComputeCameraFogTerms((Camera*)g_camera, part->fog, part->f3C);
        if (copied) {
            CopyAttachmentPart((AttachmentCopy*)self, part, pose);
        } else {
            k = 0;
            part->nstrips = ReadBufferedU16((BufferedStream*)stream);
            part->strips = (ModelStrip*)AllocateZeroedFrontMemory(part->nstrips * 0x50);
            pose->packets = (StripPackets*)AllocateZeroedFrontMemory(part->nstrips * 0x30);
            for (j = 0; j < part->nstrips; j++) {
                ModelStrip* strip = &part->strips[j];
                StripPackets* pp = &pose->packets[j];
                s32 nvecs;
                s32 nnrms;
                s32 ntints;
                s32 nuvs;
                Vec3* vecs;
                Vec3* nrms;
                u8 (*tints)[4];
                MeshUv* uvs;
                s32 nrefs;
                VertexRefs* refs;
                WeightIndices* ents;
                Vec3* verts;
                Vec3* vnrms;
                StripMesh* mesh;
                f32* weights;
                PushBackMemoryMark();
                ReadBufferedVector3((BufferedStream*)stream, strip);
                strip->radius = ReadBufferedFloat((BufferedStream*)stream);
                nvecs = ReadBufferedU8((BufferedStream*)stream);
                nnrms = ReadBufferedU8((BufferedStream*)stream);
                ntints = ReadBufferedU8((BufferedStream*)stream);
                nuvs = ReadBufferedU8((BufferedStream*)stream);
                nrefs = ReadBufferedU8((BufferedStream*)stream);
                AlignBufferedStreamPosition((BufferedStream*)stream, 4);
                vecs = (Vec3*)AllocateBackMemory(nvecs * 12);
                ReadBufferedStreamBytes((BufferedStream*)stream, nvecs * 12, vecs);
                nrms = (Vec3*)AllocateBackMemory(nnrms * 12);
                ReadBufferedStreamBytes((BufferedStream*)stream, nnrms * 12, nrms);
                tints = (u8 (*)[4])AllocateBackMemory(ntints * 4);
                ReadBufferedStreamBytes((BufferedStream*)stream, ntints * 4, tints);
                uvs = (MeshUv*)AllocateBackMemory(nuvs * 8);
                ReadBufferedStreamBytes((BufferedStream*)stream, nuvs * 8, uvs);
                refs = (VertexRefs*)AllocateBackMemory(nrefs * 4);
                ReadBufferedStreamBytes((BufferedStream*)stream, nrefs * 4, refs);
                mesh = (StripMesh*)(g_animRecords + ReadBufferedU16((BufferedStream*)stream) * 0x28);
                strip->mesh = mesh;
                strip->f14 = ReadBufferedU8((BufferedStream*)stream);
                strip->nkeys = ReadBufferedU8((BufferedStream*)stream);
                for (s32 n = 0; n < strip->nkeys; n++) {
                    strip->keys[n] = ReadBufferedU8((BufferedStream*)stream);
                }
                s32 size = strip->nkeys * nvecs * 4;
                weights = (f32*)AllocateBackMemory(size);
                ReadBufferedStreamBytes((BufferedStream*)stream, size, weights);
                if (self->nweights != 0) {
                    s32 w;
                    s32 nverts = ReadBufferedU16((BufferedStream*)stream);
                    verts = (Vec3*)AllocateBackMemory(nverts * 12);
                    ReadBufferedStreamBytes((BufferedStream*)stream, nverts * 12, verts);
                    s32 nvnrms = ReadBufferedU16((BufferedStream*)stream);
                    vnrms = (Vec3*)AllocateBackMemory(nvnrms * 12);
                    ReadBufferedStreamBytes((BufferedStream*)stream, nvnrms * 12, vnrms);
                    ents = (WeightIndices*)AllocateBackMemory(self->nweights * 8);
                    for (w = 0; w < self->nweights; w++) {
                        ents[w].pos = (u16*)AllocateBackMemory(nrefs * 2);
                        ReadBufferedStreamBytes((BufferedStream*)stream, nrefs * 2, ents[w].pos);
                        ents[w].nrm = (u16*)AllocateBackMemory(nrefs * 2);
                        ReadBufferedStreamBytes((BufferedStream*)stream, nrefs * 2, ents[w].nrm);
                    }
                }
                StripPacket pw[3];
                s32 queued = g_meshQueueCount;
                for (s32 n = 0; n < 3; n++) {
                    AllocateTempPacketBuffer((PacketWriter*)&pw[n], 0x400);
                }
                StripOutputs outs;
                ModelAnimator* anim = part->animator;
                if (anim != 0 && anim->vt->bind != 0) {
                    anim->vt->bind(anim, outs.p, self, part, strip);
                }
                switch (mesh->kind) {
                case 1:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                    BuildStripMeshPacket((MeshBuildState*)self, (StripMeshOwner*)part, k++, (StripHeader*)strip, mesh,
                                         vecs, nrms, tints, uvs, nrefs, refs, ents, verts, vnrms, weights,
                                         (PacketWriter*)pw, outs.p);
                    break;
                case 0:
                    BuildLitStripMeshPacket((MeshBuildState*)self, (StripMeshOwner*)part, b, k++, (StripHeader*)strip,
                                            mesh, vecs, nrms, tints, uvs, nrefs, refs, ents, verts, vnrms, weights,
                                            (PacketSlot*)pw, outs.p);
                    break;
                }
                u32 starts[3];
                for (s32 n = 0; n < 3; n++) {
                    if (pw[n].cur != pw[n].begin) {
                        DetachPacketBufferCopy((PacketWriter*)&pw[n], &strip->qwc[n], &starts[n], (s32*)&strip->addr[n], 0x13);
                        RemapMeshQueueValues(queued, strip->qwc[n] * 16, starts[n], strip->addr[n]);
                        MovedPointer::Fix(outs.p[1], strip->qwc[n] * 16, starts[n], strip->addr[n]);
                        MovedPointer::Fix(outs.p[2], strip->qwc[n] * 16, starts[n], strip->addr[n]);
                        if (strip->extra != 0) {
                            StripExtra* e = strip->extra;
                            MovedPointer::Fix(&e->positions, strip->qwc[n] * 16, starts[n], strip->addr[n]);
                            for (s32 m = 0; m < part->link->extraCount; m++) {
                                MovedPointer::Fix(&e->a4[m], strip->qwc[n] * 16, starts[n], strip->addr[n]);
                                MovedPointer::Fix(&e->a14[m], strip->qwc[n] * 16, starts[n], strip->addr[n]);
                                MovedPointer::Fix(&e->a24[m], strip->qwc[n] * 16, starts[n], strip->addr[n]);
                            }
                        }
                    }
                }
                // address arithmetic over a variable index
                strip->unpack = (StripUnpack*)((u8*)strip->unpack + (strip->addr[0] - starts[0]));
                BuildPartVifPackets((PartPacketContext*)part, (PartPacketSource*)strip, (PartPackets*)pp);
                PopBackMemoryMark();
            }
            part->nmorphs = ReadBufferedU16((BufferedStream*)stream);
            part->morphs = (ModelMorph*)AllocateZeroedFrontMemory(part->nmorphs * 32);
            for (s32 t = 0; t < part->nmorphs; t++) {
                ModelMorph* m = &part->morphs[t];
                s32 n;
                s32 nvecs;
                Vec3* vecs;
                s32 nextra;
                void* extra;
                f32* weights;
                WeightIndices* ents;
                Vec3* verts;
                PushBackMemoryMark();
                nvecs = ReadBufferedU8((BufferedStream*)stream);
                vecs = (Vec3*)AllocateBackMemory(nvecs * 12);
                ReadBufferedStreamBytes((BufferedStream*)stream, nvecs * 12, vecs);
                nextra = ReadBufferedU8((BufferedStream*)stream);
                extra = AllocateBackMemory(nextra * 4);
                ReadBufferedStreamBytes((BufferedStream*)stream, nextra * 4, extra);
                m->nkeys = ReadBufferedU8((BufferedStream*)stream);
                for (n = 0; n < m->nkeys; n++) {
                    m->keys[n] = ReadBufferedU8((BufferedStream*)stream);
                }
                s32 size = m->nkeys * nvecs * 4;
                weights = (f32*)AllocateBackMemory(size);
                ReadBufferedStreamBytes((BufferedStream*)stream, size, weights);
                if (self->nweights != 0) {
                    s32 w;
                    s32 nverts = ReadBufferedU16((BufferedStream*)stream);
                    verts = (Vec3*)AllocateBackMemory(nverts * 12);
                    ReadBufferedStreamBytes((BufferedStream*)stream, nverts * 12, verts);
                    ents = (WeightIndices*)AllocateBackMemory(self->nweights * 8);
                    for (w = 0; w < self->nweights; w++) {
                        ents[w].pos = (u16*)AllocateBackMemory(nvecs * 2);
                        ReadBufferedStreamBytes((BufferedStream*)stream, nvecs * 2, ents[w].pos);
                        ents[w].nrm = 0;
                    }
                }
                ModelPacket pw;
                InitPacketWriter((PacketWriter*)&pw);
                s32 queued = g_meshQueueCount;
                AllocateTempPacketBuffer((PacketWriter*)&pw, self->nweights * 128 + 0x400);
                BuildMorphTargetPacket((MeshBuildState*)self, k++, (MorphTargetHeader*)m, nvecs, vecs, nextra, extra, ents, verts, weights, (PacketWriter*)&pw);
                u32 start;
                DetachPacketBufferCopy((PacketWriter*)&pw, &m->qwc, &start, (s32*)&m->addr, 0x13);
                RemapMeshQueueValues(queued, m->qwc * 16, start, m->addr);
                // address arithmetic over a variable index
                m->p = (u16*)((u8*)m->p + (m->addr - start));
                PopBackMemoryMark();
            }
        }
    }
    CollectNonNullRefs((RefOwner*)self);
}

// Writes the VIF MSCAL that starts a strip-mesh microprogram for a drawn part: mode 0 starts one
// program, mode 1 another; any other mode writes nothing.
void WriteStripMeshMscal(s32 mode, void* obj)
{
    switch (mode) {
    case 0:
        WriteVifMscal(obj, g_flushBatchProgram);
        break;
    case 1:
        WriteVifMscal(obj, g_stripMeshMode1Program);
        break;
    }
}

// Writes the VIF MSCAL that starts a morph-target microprogram for a drawn part: mode 0 and mode 1
// start different programs; any other mode writes nothing.
void WriteMorphTargetMscal(s32 mode, void* obj)
{
    switch (mode) {
    case 0:
        WriteVifMscal(obj, g_morphTargetMode0Program);
        break;
    case 1:
        WriteVifMscal(obj, g_morphTargetMode1Program);
        break;
    }
}

// Builds the packet of a morph target: a header and a GIF tag, then the target's vectors for the
// vertices it moves (through the weight entries), so the microprogram can blend them.
void BuildMorphTargetPacket(MeshBuildState* self, s32 mode, MorphTargetHeader* hdr, s32 n, Vec3* vecs, s32 extra,
                   void* extraData, WeightIndices* ents, Vec3* verts, void* data, PacketWriter* pkt)
{
    PacketWriter f;
    u32 buf[4];
    s32 i;
    Vec3* out;
    s32 off = 0x2B;

    ReserveVifUnpack(pkt, 0xD, 2, 0x16, 0, (u8**)hdr);
    FillMemory(hdr->p, 0, 0x10);
    InitGifPacket(&f);
    AllocateTempPacketBuffer(&f, 8);
    BeginGifTag(&f, 0, 1, 0xE);
    AddGifRegisterWrite(&f, 0x42, 0x44);
    AddGifRegisterWrite(&f, 1, (u64)g_defaultModelColor.r | ((u64)g_defaultModelColor.g << 8) | ((u64)g_defaultModelColor.b << 16)
                             | ((u64)g_defaultModelColor.a << 24) | (1ULL << 32));
    CloseGifTag(&f, 1);
    CopyWordsToWriter(pkt, 0xC, 2, (u32*)f.begin, 0x18);
    RewindPacketBuffer(&f);
    BeginGifTag(&f, 0xC1, 3, 0x44E);
    AddGifRegisterWrite(&f, 0x47, 0x70000);
    AddGifXyzfEntry(&f, 0, 0, 0, 0);
    AddGifXyzfEntry(&f, 0, 0, 0, 0);
    CloseGifTag(&f, 0);
    BeginGifTag(&f, 1, 3, 0x44E);
    AddGifRegisterWrite(&f, 0x47, 0x72001);
    AddGifXyzfEntry(&f, 0, 0, 0, 0);
    AddGifXyzfEntry(&f, 0, 0, 0, 0);
    CloseGifTag(&f, 1);
    CopyWordsToWriter(pkt, 0xC, 2, (u32*)f.begin, 0x1B);
    // packet record, not an object
    CopyWordsToWriter(pkt, 0xC, 2, (u32*)(f.begin + 0x40), 0x1F);
    CopyWordsToWriter(pkt, 0xC, 2, (u32*)f.begin, 0x23);
    // packet record, not an object
    CopyWordsToWriter(pkt, 0xC, 2, (u32*)(f.begin + 0x40), 0x27);

    hdr->p[0] = off;
    off += n;
    hdr->p[1] = off;
    CopyWordsToWriter(pkt, 8, n, (u32*)vecs, hdr->p[0]);
    if (hdr->count > 0)
    {
        hdr->p[4] = off;
        off += hdr->count * 4;
        hdr->p[5] = off;
        QuadClear::Clear(buf);
        off += n;
        WriteVifStrow(pkt, buf);
        WriteVifStmask(pkt, g_morphStmasks[hdr->count]);
        CopyWordsToWriter(pkt, g_morphUnpackAddresses[hdr->count], n, (u32*)data, hdr->p[5]);
        WriteVifStmask(pkt, 0);
    }
    s32 end = off + extra;
    if (self->nweights != 0)
    {
        hdr->p[5] = off;
        hdr->p[6] = self->nweights + off;
        for (i = 0; i < self->nweights; i++)
        {
            CopyWordsToWriter(pkt, 0, 1, (u32*)&i, 0x1D);
            ReserveVifUnpack(pkt, 8, n, hdr->p[6], 0, (u8**)&out);
            u16* idx = ents[i].pos;
            for (s32 k = 0; k < n; k++)
            {
                Vec3* v = &verts[idx[k]];
                out[k].x = v->x - vecs[k].x;
                out[k].y = v->y - vecs[k].y;
                out[k].z = v->z - vecs[k].z;
            }
            WriteVifMscal(pkt, g_morphTargetBlendProgram);
            WriteVifFlushE(pkt);
        }
    }
    hdr->p[2] = off;
    hdr->p[3] = end;
    CopyWordsToWriter(pkt, 0xE, extra, (u32*)extraData, hdr->p[2]);
    WriteMorphTargetMscal(mode, pkt);
    WriteVifMscal(pkt, g_morphTargetTailProgram);
    WriteVifMscal(pkt, g_morphTargetEndProgram);
}

// Builds the VIF packets of an unlit strip mesh (the lit one is BuildLitStripMeshPacket): the
// unpack header, then the vertex positions, colours and UVs, with weights and deltas when skinned,
// per the mesh's kind.
void BuildStripMeshPacket(MeshBuildState* self, StripMeshOwner* obj, s32 mode, StripHeader* hdr, StripMesh* mesh,
                   Vec3* vecs, Vec3* nrms, u8 (*tints)[4], MeshUv* uvs, s32 n, VertexRefs* recs,
                   WeightIndices* ents, Vec3* verts, Vec3* vnrms, f32* weights, PacketWriter* pkt,
                   s32** outs)
{
    u32 buf[4];
    f32* uvOut;
    f32* posOut;
    s32 a;
    s32 b;
    f32* wOut;
    s32 k;
    Vec3* dOut;
    u8* cOut;
    s32 c;
    s32 d;
    s32 off;
    s32 hasUv;
    s32 tinted;
    void* tail;
    void* head;
    AnimCursor* node;
    s32 i;
    VertexRefs* r;

    if (obj->link != 0) {
        BeginDmaTag(pkt);
    }
    ReserveVifUnpack(pkt, 0xD, 3, 0xB, 0, (u8**)&hdr->p);
    off = 0x24;
    FillMemory(hdr->p, 0, 0x18);
    hdr->p->f10 = 3;
    hdr->p->off[0] = off;
    off = n * 3 + 0x24;
    hdr->p->off[1] = off;
    switch (mesh->kind) {
    case 1:
    case 5:
    case 6:
    case 7:
    case 8:
    case 10:
        head = g_unlitBatchFinishProgram;
        tail = g_unlitBatchProgram;
        tinted = 1;
        hasUv = 1;
        break;
    case 4:
        head = g_unlitKind4BatchFinishProgram;
        tail = g_unlitKind4BatchProgram;
        hasUv = mesh->mode & 2;
        tinted = hasUv;
        break;
    case 9:
        head = g_unlitBatchFinishProgram;
        tail = g_unlitBatchProgram;
        hasUv = 0;
        tinted = 1;
        break;
    }
    cOut = 0;
    uvOut = 0;
    WriteVifStcycl(pkt, 1, 3);
    if (hasUv) {
        ReserveVifUnpack(pkt, 8, n, hdr->p->off[0], 0, (u8**)&uvOut);
    }
    ReserveVifUnpack(pkt, 0xC, n, hdr->p->off[0] + 2, 0, (u8**)&posOut);
    WriteVifStcycl(pkt, 1, 1);
    if (outs[0] != 0) {
        *outs[0] = n;
    }
    if (outs[1] != 0) {
        *outs[1] = (s32)posOut;
    }
    if (outs[2] != 0) {
        *outs[2] = (s32)uvOut;
    }
    if (obj->link != 0) {
        StripExtra* e = (StripExtra*)AllocateZeroedFrontMemory(0x34);
        hdr->extra = e;
        e->positions = (s32)posOut;
    }
    for (i = 0; i < n; i++) {
        r = &recs[i];
        if (hasUv) {
            if (r->uv == 0xFF) {
                uvOut[0] = uvOut[1] = 0.0f;
            } else {
                uvOut[0] = uvs[r->uv].u;
                uvOut[1] = uvs[r->uv].v;
            }
            uvOut[2] = 1.0f;
            uvOut += 3;
        }
        *(Vec3*)posOut = vecs[recs[i].pos];
        if (recs[i].flags >> 7) {
            posOut[3] = obj->fogBias + 32768.0f;
        } else {
            posOut[3] = obj->fogBias + 28672.0f;
        }
        posOut += 4;
    }
    node = 0;
    if (obj->animator != 0) {
        node = obj->animator->vt[5](obj->animator, mesh);
    }
    if (node == 0 && mesh->hook != 0) {
        node = ((CursorHook*)mesh->hook)->vt[5]((CursorHook*)mesh->hook, mesh);
    }
    WriteStripMeshMscal(mode, pkt);
    if (node != 0 && (node->flags & 2)) {
        ReserveVifUnpack(pkt, 4, 1, 0x16, &a, (u8**)&b);
        QueueNodeLink(b, a, node);
        WriteVifMscal(pkt, g_nodeLinkProgram);
    }
    if (hdr->count > 0) {
        hdr->p->off[2] = off;
        off += hdr->count * 4;
        hdr->p->off[3] = off;
        off += n;
        FillMemory(buf, 0, 0x10);
        WriteVifStrow(pkt, buf);
        WriteVifStmask(pkt, g_stripStmasks[hdr->count]);
        ReserveVifUnpack(pkt, g_stripUnpackAddresses[hdr->count], n, hdr->p->off[3], 0, (u8**)&wOut);
        WriteVifStmask(pkt, 0);
        for (i = 0; i < n; i++) {
            r = &recs[i];
            for (s32 j = 0; j < hdr->count; j++) {
                *wOut++ = weights[r->pos * hdr->count + j];
            }
        }
        WriteVifMscal(pkt, g_skinWeightProgram);
    }
    if (self->nweights != 0) {
        hdr->p->off[3] = off;
        off += self->nweights;
        hdr->p->strip[3] = off;
        for (k = 0; k < self->nweights; k++) {
            if (k > 0) {
                WriteVifFlushE(pkt);
            }
            CopyWordsToWriter(pkt, 0, 1, (u32*)&k, 0x16);
            ReserveVifUnpack(pkt, 8, n, hdr->p->strip[3], 0, (u8**)&dOut);
            u16* idx = ents[k].pos;
            for (i = 0; i < n; i++) {
                r = &recs[i];
                Vec3* v = &verts[idx[i]];
                dOut[i].x = v->x - vecs[r->pos].x;
                dOut[i].y = v->y - vecs[r->pos].y;
                dOut[i].z = v->z - vecs[r->pos].z;
            }
            WriteVifMscal(pkt, g_positionDeltaProgram);
        }
    }
    if (hdr->extra != 0) {
        StripExtra* e = hdr->extra;
        for (s32 i = 0; i < obj->link->extraCount; i++) {
            ReserveVifUnpack(pkt, 0xC, n, off, 0, (u8**)&e->a24[i]);
            if (obj->link->f18 != 0) {
                WriteVifUnpack(pkt, 0xC, 4, 0, 0x16, &e->a14[i]);
                WriteVifMscal(pkt, g_extraStreamFirstProgram);
                WriteVifFlushE(pkt);
            }
            if (obj->link->f14 != 0) {
                WriteVifUnpack(pkt, 0xC, 4, 0, 0x16, &e->a4[i]);
                WriteVifMscal(pkt, g_unlitExtraStreamSecondProgram);
                WriteVifFlushE(pkt);
            }
        }
        hdr->p->off[3] = off;
        off += n;
    }
    WriteVifMscal(pkt, tail);
    if (tinted) {
        WriteVifStcycl(pkt, 1, 3);
        ReserveVifUnpack(pkt, 0xE, n, hdr->p->off[0] + 1, 0, &cOut);
        WriteVifStcycl(pkt, 1, 1);
        for (i = 0; i < n; i++) {
            s32 j;
            r = &recs[i];
            if ((r->flags & 0x7F) == 0x7F) {
                for (j = 0; j < 4; j++) {
                    cOut[j] = (mesh->color[j] + 1) >> 1;
                }
            } else {
                for (j = 0; j < 4; j++) {
                    cOut[j] = (mesh->color[j] * tints[r->flags & 0x7F][j] + 0x100) / 0x1FE;
                }
            }
            cOut += 4;
        }
    }
    for (s32 i = 0; i < mesh->nstrips; i++) {
        FrameSource* s = &mesh->strips[i];
        ReserveVifUnpack(pkt, 0xC, s->stride, off, &c, (u8**)&d);
        QueueMeshStrip(mesh, s, d, c, n, node);
        hdr->p->strip[i] = off;
        off += s->stride;
    }
    WriteVifMscalf(pkt, head);
    if (obj->link != 0) {
        CloseDmaTag(pkt);
        AddDmaReturnTag(pkt);
    }
}

// Builds the VIF packets of a lit strip mesh: the unpack header, then the vertex positions,
// normals, colours and UVs of the strip (with the skin weights and their deltas when the mesh is
// skinned or morphs), marking the owner lit.
void BuildLitStripMeshPacket(MeshBuildState* self, StripMeshOwner* obj, s32 unused2, s32 mode, StripHeader* hdr,
                   StripMesh* mesh, Vec3* vecs, Vec3* nrms, u8 (*tints)[4], MeshUv* uvs,
                   s32 n, VertexRefs* recs, WeightIndices* ents, Vec3* verts, Vec3* vnrms,
                   f32* weights, PacketSlot* pkt, s32** outs)
{
    u32 buf[4];
    f32* posOut;
    f32* wOut;
    s32 k;
    Vec3* dOut;
    QuadLanes* quads;
    f32* nOut;
    u8* cOut;
    Vec3* nDelta;
    f32* uvOut;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 off;
    AnimCursor* node;
    s32 i;
    VertexRefs* r;

    if (obj->link != 0) {
        BeginDmaTag((PacketWriter*)&pkt[2]);
    }
    obj->lit = 1;
    ReserveVifUnpack((PacketWriter*)&pkt[0], 0xD, 3, 0xB, 0, (u8**)&hdr->p);
    off = 0x24;
    FillMemory(hdr->p, 0, 0x18);
    hdr->p->f10 = 4;
    hdr->p->f12 = hdr->f14 * 0x7FA6 / 0xFF;
    hdr->p->off[0] = off;
    off = n * 4 + 0x24;
    hdr->p->off[1] = off;
    if (hdr->count != 0 || self->nweights != 0) {
        obj->skinned = 1;
    }
    if (obj->skinned != 0) {
        off += (((n + 3) & ~3) - n) * 4;
    }
    hdr->p->strip[3] = off;
    off += n;
    WriteVifStcycl((PacketWriter*)&pkt[0], 1, 4);
    ReserveVifUnpack((PacketWriter*)&pkt[0], 0xC, n, hdr->p->off[0] + 3, 0, (u8**)&posOut);
    WriteVifStcycl((PacketWriter*)&pkt[0], 1, 1);
    if (outs[0] != 0) {
        *outs[0] = n;
    }
    if (outs[1] != 0) {
        *outs[1] = (s32)posOut;
    }
    if (obj->link != 0) {
        StripExtra* e = (StripExtra*)AllocateZeroedFrontMemory(0x34);
        hdr->extra = e;
        e->positions = (s32)posOut;
    }
    for (i = 0; i < n; i++) {
        r = &recs[i];
        *(Vec3*)posOut = vecs[r->pos];
        if (r->flags >> 7) {
            posOut[3] = obj->fogBias + 32768.0f;
        } else {
            posOut[3] = obj->fogBias + 28672.0f;
        }
        posOut += 4;
    }
    WriteStripMeshMscal(mode, &pkt[0]);
    if (hdr->count > 0) {
        hdr->p->off[2] = off;
        off += hdr->count * 4;
        hdr->p->off[3] = off;
        off += n;
        FillMemory(buf, 0, 0x10);
        WriteVifStrow((PacketWriter*)&pkt[0], buf);
        WriteVifStmask((PacketWriter*)&pkt[0], g_litStripStmasks[hdr->count]);
        ReserveVifUnpack((PacketWriter*)&pkt[0], g_litStripUnpackAddresses[hdr->count], n, hdr->p->off[3], 0, (u8**)&wOut);
        WriteVifStmask((PacketWriter*)&pkt[0], 0);
        for (i = 0; i < n; i++) {
            r = &recs[i];
            for (s32 j = 0; j < hdr->count; j++) {
                *wOut++ = weights[r->pos * hdr->count + j];
            }
        }
        WriteVifMscal(&pkt[0], g_skinWeightProgram);
    }
    if (self->nweights != 0) {
        hdr->p->off[3] = off;
        off += self->nweights;
        for (k = 0; k < self->nweights; k++) {
            CopyWordsToWriter((PacketWriter*)&pkt[0], 0, 1, (u32*)&k, 0x16);
            ReserveVifUnpack((PacketWriter*)&pkt[0], 8, n, hdr->p->strip[3], 0, (u8**)&dOut);
            u16* idx = ents[k].pos;
            for (i = 0; i < n; i++) {
                r = &recs[i];
                Vec3* v = &verts[idx[i]];
                dOut[i].x = v->x - vecs[r->pos].x;
                dOut[i].y = v->y - vecs[r->pos].y;
                dOut[i].z = v->z - vecs[r->pos].z;
            }
            WriteVifMscal(&pkt[0], g_positionDeltaProgram);
            WriteVifFlushE((PacketWriter*)&pkt[0]);
        }
    }
    WriteVifStcycl((PacketWriter*)&pkt[1], 1, 4);
    if (obj->skinned != 0 && hdr->count == 0 && self->nweights == 0) {
        ReserveVifUnpack((PacketWriter*)&pkt[1], 0xC, (n + 3) & ~3, hdr->p->off[0], 0, (u8**)&quads);
        nOut = 0;
    } else {
        ReserveVifUnpack((PacketWriter*)&pkt[1], 0xC, n, hdr->p->off[0], 0, (u8**)&nOut);
        quads = 0;
    }
    ReserveVifUnpack((PacketWriter*)&pkt[1], 0xE, n, hdr->p->off[0] + 1, 0, &cOut);
    WriteVifStcycl((PacketWriter*)&pkt[1], 1, 1);
    if (hdr->count > 0) {
        WriteVifMscal(&pkt[1], g_litSkinWeightProgram);
    }
    if (self->nweights > 0) {
        for (s32 m = 0; m < self->nweights; m++) {
            if (m > 0) {
                WriteVifFlushE((PacketWriter*)&pkt[1]);
            }
            ReserveVifUnpack((PacketWriter*)&pkt[1], 8, n, hdr->p->strip[3], 0, (u8**)&nDelta);
            u16* idx = ents[m].nrm;
            for (i = 0; i < n; i++) {
                r = &recs[i];
                Vec3* v = &vnrms[idx[i]];
                nDelta[i].x = v->x - nrms[r->nrm].x;
                nDelta[i].y = v->y - nrms[r->nrm].y;
                nDelta[i].z = v->z - nrms[r->nrm].z;
            }
            WriteVifMscal(&pkt[1], g_normalDeltaProgram);
        }
        WriteVifMscal(&pkt[1], g_normalDeltaFinishProgram);
    }
    WriteVifMscal(&pkt[1], g_litBatchProgram);
    for (i = 0; i < n; i++) {
        s32 j;
        r = &recs[i];
        if ((r->flags & 0x7F) == 0x7F) {
            for (j = 0; j < 4; j++) {
                cOut[j] = (mesh->color[j] + 1) >> 1;
            }
        } else {
            for (j = 0; j < 4; j++) {
                cOut[j] = (mesh->color[j] * tints[r->flags & 0x7F][j] + 0x100) / 0x1FE;
            }
        }
        if (nOut != 0) {
            if (r->nrm == 0xFF) {
                nOut[0] = nOut[1] = nOut[2] = 0.0f;
            } else {
                *(Vec3*)nOut = nrms[r->nrm];
            }
            nOut[3] = (cOut[0] + cOut[1] + cOut[2]) * 0.33333334f;
            nOut += 4;
        }
        cOut += 4;
    }
    if (quads != 0) {
        for (i = 0; i < n; i += 4) {
            for (s32 j = 0; j < 4; j++) {
                if (i + j < n) {
                    quads->x[j] = nrms[recs[i + j].nrm].x;
                    quads->y[j] = nrms[recs[i + j].nrm].y;
                    quads->z[j] = nrms[recs[i + j].nrm].z;
                } else {
                    quads->x[j] = quads->y[j] = quads->z[j] = 0.0f;
                }
            }
            FillMemory(quads->w, 0, 0x10);
            quads++;
        }
    }
    WriteVifStcycl((PacketWriter*)&pkt[2], 1, 4);
    ReserveVifUnpack((PacketWriter*)&pkt[2], 8, n, hdr->p->off[0], 0, (u8**)&uvOut);
    WriteVifStcycl((PacketWriter*)&pkt[2], 1, 1);
    if (outs[2] != 0) {
        *outs[2] = (s32)uvOut;
    }
    for (i = 0; i < n; i++) {
        r = &recs[i];
        if (r->uv == 0xFF) {
            uvOut[0] = uvOut[1] = 0.0f;
        } else {
            uvOut[0] = uvs[r->uv].u;
            uvOut[1] = uvs[r->uv].v;
        }
        uvOut[2] = 1.0f;
        uvOut += 3;
    }
    node = 0;
    if (obj->animator != 0) {
        node = obj->animator->vt[5](obj->animator, mesh);
    }
    if (node == 0 && mesh->hook != 0) {
        node = ((CursorHook*)mesh->hook)->vt[5]((CursorHook*)mesh->hook, mesh);
    }
    if (node != 0 && (node->flags & 2)) {
        ReserveVifUnpack((PacketWriter*)&pkt[2], 4, 1, 0x16, &a, (u8**)&b);
        QueueNodeLink(b, a, node);
        WriteVifMscal(&pkt[2], g_nodeLinkProgram);
    }
    if (hdr->extra != 0) {
        StripExtra* e = hdr->extra;
        for (s32 i = 0; i < obj->link->extraCount; i++) {
            ReserveVifUnpack((PacketWriter*)&pkt[2], 0xC, n, off, 0, (u8**)&e->a24[i]);
            if (obj->link->f18 != 0) {
                WriteVifUnpack(&pkt[2], 0xC, 4, 0, 0x16, &e->a14[i]);
                WriteVifMscal(&pkt[2], g_extraStreamFirstProgram);
                WriteVifFlushE((PacketWriter*)&pkt[2]);
            }
            if (obj->link->f14 != 0) {
                WriteVifUnpack(&pkt[2], 0xC, 4, 0, 0x16, &e->a4[i]);
                WriteVifMscal(&pkt[2], g_litExtraStreamSecondProgram);
                WriteVifFlushE((PacketWriter*)&pkt[2]);
            }
        }
        hdr->p->off[3] = off;
        off += n;
    }
    WriteVifMscal(&pkt[2], g_litBatchThirdProgram);
    s32 slot = 0;
    for (s32 i = 0; i < mesh->nstrips; i++) {
        FrameSource* s = &mesh->strips[i];
        ReserveVifUnpack((PacketWriter*)&pkt[2], 0xC, s->stride, off, &c, (u8**)&d);
        QueueMeshStrip(mesh, s, d, c, n, node);
        hdr->p->strip[slot++] = off;
        off += s->stride;
    }
    if (obj->link != 0) {
        CloseDmaTag((PacketWriter*)&pkt[2]);
        AddDmaReturnTag((PacketWriter*)&pkt[2]);
    }
}

// Builds the VIF packets of a part that is not skinned: a STCYCL, an unpack of the part's data (its
// range divided by 4) and a MSCAL that starts the lit batch microprogram.
void BuildPartVifPackets(PartPacketContext* a, PartPacketSource* b, PartPackets* c)
{
    u8 buf[0x30];
    s32 s0;

    if (*b->mesh != 0) return;
    if (a->skinned != 0) return;
    InitPacketWriter((PacketWriter*)buf);
    s0 = (b->unpack->hi - b->unpack->lo) / 4;
    AllocateQuadwordBuffer((PacketWriter*)buf, (u32)((s0 + 7) / 4), 0x1A);
    WriteVifStcycl((PacketWriter*)buf, 1, 4);
    ReserveVifUnpack((PacketWriter*)buf, 0xE, s0, b->unpack->lo + 1, 0, (u8**)&c->firstUnpackCursor);
    WriteVifStcycl((PacketWriter*)buf, 1, 1);
    WriteVifMscal(buf, g_litBatchFinishProgram);
    DetachPacketBuffer((PacketWriter*)buf, (u32*)&c->firstQwc, (u8**)&c->firstBuffer);
    AllocateQuadwordBuffer((PacketWriter*)buf, (u32)((s0 + 4) / 2), 0x1A);
    WriteVifStcycl((PacketWriter*)buf, 1, 4);
    ReserveVifUnpack((PacketWriter*)buf, 0xE, s0, b->unpack->lo + 2, 0, (u8**)&c->secondUnpackCursor);
    WriteVifStcycl((PacketWriter*)buf, 1, 1);
    ReserveVifUnpack((PacketWriter*)buf, 0xE, s0, b->unpack->hi, 0, 0);
    WriteVifMscal(buf, g_litBatchSecondFinishProgram);
    DetachPacketBuffer((PacketWriter*)buf, (u32*)&c->secondQwc, (u8**)&c->secondBuffer);
}

// Starts the object's attachments: each entry's handler is started and its DMA chain is built, then
// the attachment nodes are started.
void StartAttachments(AttachmentBlock* self, PlacedObject* ctx)
{
    for (s32 i = 0; i < self->count0C; i++)
    {
        AttachmentEntry* e = self->entries + i;
        AttachmentHandler* o = e->handler;
        if (o != 0)
        {
            o->vtbl[1](o);
        }
        BuildAttachmentDmaChain(self, e, self->chainData + i * 0x28, ctx);
    }
    AttachmentNode* n = self->nodes;
    if (n != 0)
    {
        do
        {
            void* v = FindFirstObjectById(ctx->world, 0x104, n->targetId, ctx);
            if (v != 0)
            {
                AttachNodeToOwner((NodeOwner*)v, ctx, (NodeAttachment*)n->attachment);
            }
            n = n->next80;
        } while (n != 0);
    }
}

// Binds each attachment target to the object it names (found by key in the world): the target's
// matrix is the product of the inverse of that object's frame and the owner's frame.
void BindAttachmentTargets(AttachmentTargets* self, PlacedObject* ctx)
{
    QuadMatrix a;
    QuadMatrix b;
    s32 i;

    for (i = 0; i < self->count; i++) {
        AttachmentTarget* e = &self->elems[i];
        TargetObject* r = (TargetObject*)FindFirstObjectByIdMode4(ctx->world, self->keys[i], ctx);
        e->p0 = r;
        if (r != 0) {
            BuildMatrixFromRotationAndTranslation(&ctx->v140, &ctx->m110, (Mat4A*)&a);
            InvertRigidTransform(&e->p0->sub140, &e->p0->sub110, (Quad16*)&b);
            e->m = MultiplyMatrices(b, a);
        }
    }
}

// Copies an object's attachment block from src (0x58 bytes), giving the copy its own tables and
// records (duplicating the parts that have a handler or a second link) and links them to owner.
void CopyAttachmentBlock(AttachmentCopy* self, PlacedObject* owner, void* src)
{
    s32 i = 0;
    AttachmentLink** link;
    CopyMemory(self, src, 0x58);
    self->f50 = 0;
    self->p4 = AllocateZeroedFrontMemory(self->n0 * 0x90);
    self->p44 = CopyToFrontMemory(self->n40 << 2, self->p44);
    self->p14 = CopyToFrontMemory(self->count * 0x28, self->p14);
    AttachmentPart* old = self->recs;
    for (; i < self->count; i++) {
        // address arithmetic over a variable index
        AttachmentPart* r = (AttachmentPart*)((u8*)self->recs + i * 0x70);
        if ((r->a && (r->a->flags & 4)) || r->b) {
            self->recs = (AttachmentPart*)CopyToFrontMemory(self->count * 0x70, self->recs);
            break;
        }
    }
    link = &self->head;
    AttachmentLink* s = self->head;
    if (s) {
        do {
            AttachmentLink* n = (AttachmentLink*)CopyToFrontMemory(0x90, s);
            n->owner = owner;
            AttachmentLink** pf = &n->p4;
            u32 sz = self->count * 0x70;
            u32 nb = (u32)self->recs;
            if (pf) {
                u32 v = (u32)n->p4;
                if (!(v < (u32)old) && v < (u32)old + sz)
                    n->p4 = (AttachmentLink*)(v + (nb - (u32)old));
            }
            ((AttachmentPart*)n->p4)->b = n;
            *link = n;
            link = &n->next;
            s = n->next;
        } while (s);
    }
    *link = 0;
    i = 0;
    if (self->count > 0) {
        s32 b = 0, a = 0;
        do {
            i++;
            // address arithmetic over a variable index
            CopyAttachmentPart(self, (u8*)self->recs + a, (u8*)self->p14 + b);
            a += 0x70;
            b += 0x28;
        } while (i < self->count);
    }
    CollectNonNullRefs((RefOwner*)self);
}

// What CopyAttachmentPart copies: a part's 0x50-byte entries (the mesh, a record of pointers
// into its three buffers, the buffers' sizes and the buffers) and the 0x28-byte record built
// for the part.
struct PartPointers {
    void* positions;        // 0x00
    void* a[4];             // 0x04
    void* b[4];             // 0x14
    void* c[4];             // 0x24
};
struct PartEntry {
    u8 pad00[0x18];
    StripMesh* mesh;        // 0x18
    u8 pad1C[0x20 - 0x1C];
    PartPointers* pointers; // 0x20
    u8 pad24[0x38 - 0x24];
    s32 sizes[3];           // 0x38: quadwords
    void* buffers[3];       // 0x44
    u8 pad50[0x50 - 0x50];
};
struct CopiedPart {
    u8 pad00[0x38];
    CursorAnimator* animator;   // 0x38
    u8 pad3C[0x54 - 0x3C];
    void* link;             // 0x54
    s32 count;              // 0x58
    PartEntry* entries;     // 0x5C
};
struct PartRecord {
    u8 pad00[0x04];
    u8* packets;            // 0x04: 0x30 bytes an entry
};
extern FrameTarget g_meshQueueEntries[];
s32 GetAnimatorSize(s32 type);

// Moves a pointer that points into the block at `from` (`size` bytes) to the same place in the
// block at `to`.
static inline void MovePointerInto(void** p, u8* from, s32 size, u8* to)
{
    if (p != 0 && !((u8*)*p < from) && (u8*)*p < from + size) {
        // address arithmetic over a variable index
        *p = (u8*)*p + (to - from);
    }
}

// Retail reads part->animator again after the count's store, so the count is its own statement;
// the detached list is walked through a variable of its own (`lw v0; move s0,v0`: the load can't
// pass the store of 0 into the loop's variable); and the strip search reads e->mesh at each use:
// PRE then loads it once in the loop's entry, after NOTE_INSN_LOOP_BEG, and loop.c calls the loop
// phony and moves nothing out of it (retail reloads the count, the strips and the frame each time).
void CopyAttachmentPart(AttachmentCopy* owner, void* partp, void* recp)
{
    CopiedPart* part = (CopiedPart*)partp;
    PartRecord* rec = (PartRecord*)recp;
    rec->packets = (u8*)CopyToFrontMemory(part->count * 0x30, rec->packets);
    if (part->animator != 0) {
        owner->f50++;
    }
    s32 animated = part->animator != 0 && (part->animator->cursor.flags & 4) != 0;
    s32 linked = part->link != 0;
    s32 first;
    if (animated || linked) {
        first = g_meshQueueCount;
        part->entries = (PartEntry*)CopyToFrontMemory(part->count * 0x50, part->entries);
        if (part->animator != 0) {
            part->animator = (CursorAnimator*)CopyToFrontMemory(GetAnimatorSize(part->animator->type), part->animator);
            AnimCursor* cursor = &part->animator->cursor;
            FrameLink* links = cursor->links;
            cursor->links = 0;
            for (FrameLink* link = links; link != 0; link = link->next) {
                FrameTarget* t = link->dst;
                if (link->src != 0) {
                    QueueMeshStrip((StripMesh*)cursor->record, link->src, t->dstAddr, t->count, t->flag, cursor);
                } else {
                    QueueNodeLink(t->dstAddr, t->count, cursor);
                }
            }
        }
    }
    for (s32 i = 0; i < part->count; i++) {
        PartEntry* e = &part->entries[i];
        u8* packets = rec->packets + i * 0x30;
        if (animated || linked) {
            for (s32 j = 0; j < 3; j++) {
                u8* old = (u8*)e->buffers[j];
                if (old != 0) {
                    s32 size = e->sizes[j] << 4;
                    u8* end = old + size;
                    e->buffers[j] = CopyToFrontMemory(size, old);
                    for (s32 k = 0; k < first; k++) {
                        FrameTarget* t = &g_meshQueueEntries[k];
                        if (!((u8*)t->dstAddr < old) && (u8*)t->dstAddr < end) {
                            s32 again = 0;
                            for (s32 m = first; m < g_meshQueueCount; m++) {
                                FrameTarget* q = &g_meshQueueEntries[m];
                                if (q->dstAddr == t->dstAddr) {
                                    again = 1;
                                    break;
                                }
                            }
                            if (again == 0) {
                                FrameSource* strip = 0;
                                for (s32 n = 0; n < e->mesh->nstrips; n++) {
                                    FrameSource* s = &e->mesh->strips[n];
                                    u32 limit = (u32)s->base + ((e->mesh->frameCount * s->stride) << 4);
                                    if (!((u32)t->value < (u32)s->base) && (u32)t->value < limit) {
                                        strip = s;
                                        break;
                                    }
                                }
                                QueueMeshStrip(e->mesh, strip, t->dstAddr, t->count, t->flag, 0);
                            }
                        }
                    }
                    RemapMeshQueueValues(first, size, (u32)old, (u32)e->buffers[j]);
                    if (linked) {
                        e->pointers = (PartPointers*)CopyToFrontMemory(0x34, e->pointers);
                        MovePointerInto(&e->pointers->positions, old, e->sizes[j] << 4, (u8*)e->buffers[j]);
                        for (s32 k = 0; k < 4; k++) {
                            MovePointerInto(&e->pointers->a[k], old, e->sizes[j] << 4, (u8*)e->buffers[j]);
                            MovePointerInto(&e->pointers->b[k], old, e->sizes[j] << 4, (u8*)e->buffers[j]);
                            MovePointerInto(&e->pointers->c[k], old, e->sizes[j] << 4, (u8*)e->buffers[j]);
                        }
                    }
                }
            }
        }
        BuildPartVifPackets((PartPacketContext*)part, (PartPacketSource*)e, (PartPackets*)packets);
    }
}

// Per-frame update of an animator's steps: calls slot 2 of every element the step claims (with the
// frame time f), then evaluates the oscillator of each entry of the owner's list at head4C.
void UpdateAttachments(AnimatorOwner* self, PlacedObject* sub, f32 f)
{
    AnimatorStep* e;
    s32 i;

    for (i = 0; i < sub->elemCount; i++) {
        e = ((AnimatorStep**)sub->elems)[i];
        if (ClaimAnimatorStep((CursorAnimator*)e) != 0) {
            AnimatorStepFn fn = e->vtbl[2];
            if (fn != 0) {
                fn(e, f);
            }
        }
    }
    for (e = self->head4C; e != 0; e = e->next80) {
        EvaluateOscillator((Oscillator*)e->oscillator);
    }
}

// The update method that applies the object's link constraint: when its link record has flag bit 4
// (0x10) set and a linked object, ApplyLinkConstraint is run on that object.
void UpdateLinkConstraint(PlacedObject* self)
{
    Rec2195_224* p = self->linkRecord;
    if (p && (p->flags & 16) && p->p64) ApplyLinkConstraint((PlacedObject*)p->p60);
}

// Updates the frames of the object's attachments: from the inverse of the object's own and its
// parent's rigid transform, each attachment gets its matrix in the object's space.
void UpdateAttachmentFrames(PlacedObject* self, ParentFrame* par)
{
    QuadMatrix a;
    QuadMatrix b;
    QuadMatrix c;
    QuadMatrix e;
    s32 i;
    FramedAttachmentList* l = (FramedAttachmentList*)self->sub22C;

    if (l->count > 0) {
        InvertRigidTransform(&self->v140, &self->m110, (Quad16*)&a);
        if (par != 0) {
            InvertRigidTransform(&par->pos, &par->rot, (Quad16*)&b);
        } else {
            b = a;
        }
        for (i = 0; i < l->count; i++) {
            // address arithmetic over a variable index
            FramedAttachment* el = (FramedAttachment*)((u8*)l->items + (i << 4) * 9);
            if (el->obj != 0) {
                el->obj->vt->f(el->obj);
                FrameLinkConstraint* t = el->obj->link;
                if (t != 0 && (t->flags & 0x80) && t->a4 != 0) {
                    c = t->m60;
                    e = MultiplyMatrices(b, &c);
                } else {
                    BuildMatrixFromRotationAndTranslation((const Vec4*)el->obj->sub140, (const Mat3*)el->obj->sub110, (Mat4A*)&c);
                    e = MultiplyMatrices(a, &c);
                }
                el->m50 = MultiplyMatrices(e, &el->q10);
            }
        }
    }
}

struct LocalPacketWriter { u8 pad[0x30]; };
struct ModelDmaQuadword { u64 a; u64 b; };
struct AttachmentStripRecord {
    u8 pad0[0x18]; u8* f18; u8 pad1C[0x24 - 0x1C]; s32 nkeys; u8 pad28[0x38 - 0x28];
    s32 qwc0; u8 pad3C[4]; s32 qwc2; s32 addr0; u8 pad48[4]; s32 addr2;
};
struct DmaPacketRow { s32 f0, f4, f8, fC, secondBuffer; u8 pad14[0x30 - 0x14]; };
struct MorphEntry { u8 pad0[4]; s32 nkeys; u8 pad8[0x18 - 8]; s32 f18, addr; };
struct AttachmentModelPart {
    u8 pad0[0x28]; s32 skinned; u8 pad2C[0x54 - 0x2C]; s32 link; s32 nstrips; AttachmentStripRecord* strips; s32 nmorphs; MorphEntry* morphs;
};
struct AttachmentDmaResult { u8 pad0[4]; DmaPacketRow* packets; u8 pad8[0x18 - 8]; s32 qwc[2]; s32 addr[2]; };
struct WeightedModelPart { u8 pad[0x40]; s32 nweights; };

void AddDmaRefTag(LocalPacketWriter* b, s32 x, s32 y);

// Builds, for an attachment entry that is not skinned, the DMA chain the model draws from: the VIF
// packets of each pass copied into a buffer and chained with the entry's own tags (the result is
// kept in out).
void BuildAttachmentDmaChain(void* selfArg, void* cfgArg, void* outArg, void* ctx)
{
    WeightedModelPart* self = (WeightedModelPart*)selfArg;
    AttachmentModelPart* cfg = (AttachmentModelPart*)cfgArg;
    AttachmentDmaResult* out = (AttachmentDmaResult*)outArg;
    LocalPacketWriter buf;
    ModelDmaQuadword q;
    s32 pass;
    s32 i, k;
    s32 n;
    s32 sz;

    InitPacketWriter((PacketWriter*)&buf);
    if (cfg->skinned) return;
    if (!out) return;
    if (self->nweights) return;
    for (i = 0; i < cfg->nstrips; i++) {
        if (cfg->strips[i].nkeys) return;
    }
    for (k = 0; k < cfg->nmorphs; k++) {
        if (cfg->morphs[k].nkeys) return;
    }
    for (pass = 0; pass < 2; pass++) {
        s32 total = 0x23C;
        sz = 0x214;
        PushBackMemoryMark();
        AllocateTempPacketBuffer((PacketWriter*)&buf, 0x1000);
        n = 0;
        if (pass == 0) sz = 0x28;
        s32 co, ro;
        i = 0;
        if (i < cfg->nstrips) {
        ro = 0; co = 0;
        do {
            AttachmentStripRecord* c;
            DmaPacketRow* r;
            s32 prev;
            // address arithmetic over a variable index
            c = (AttachmentStripRecord*)((u8*)cfg->strips + co);
            r = (DmaPacketRow*)((u8*)out->packets + ro);
            sz = total - sz;
            if (n++ > 0) {
                BeginDmaTag((PacketWriter*)&buf);
                WriteVifBaseOffset((PacketWriter*)&buf, sz, 0);
                CloseDmaTag((PacketWriter*)&buf);
            }
            switch (*c->f18) {
            case 0:
                AddDmaRefTag(&buf, c->qwc0, c->addr0);
                if (cfg->link) {
                    AddDmaCallTag((PacketWriter*)&buf, c->addr2);
                } else {
                    AddDmaRefTag(&buf, c->qwc2, c->addr2);
                }
                AddDmaRefTag(&buf, r->f0, r->f4);
                AddDmaRefTag(&buf, r->fC, r->secondBuffer);
                break;
            case 1:
            case 4: case 5: case 6: case 7: case 8: case 9: case 10:
                if (cfg->link) {
                    AddDmaCallTag((PacketWriter*)&buf, c->addr0);
                } else {
                    AddDmaRefTag(&buf, c->qwc0, c->addr0);
                }
                break;
            }
            i++; ro += sizeof(DmaPacketRow); co += sizeof(AttachmentStripRecord);
        } while (i < cfg->nstrips);
        }
        for (k = 0; k < cfg->nmorphs; k++) {
            MorphEntry* s = &cfg->morphs[k];
            sz = total - sz;
            BeginDmaTag((PacketWriter*)&buf);
            if (n++ > 0) WriteVifBaseOffset((PacketWriter*)&buf, sz, 0);
            q.b = 1;
            q.a = (u64)g_defaultModelColor.r | ((u64)g_defaultModelColor.g << 8) | ((u64)g_defaultModelColor.b << 16) | ((u64)g_defaultModelColor.a << 24) | ((u64)1 << 32);
            CopyWordsToWriter((PacketWriter*)&buf, 0xC, 1, (u32*)&q, 0x1A);
            CloseDmaTag((PacketWriter*)&buf);
            AddDmaRefTag(&buf, s->f18, s->addr);
        }
        AddDmaReturnTag((PacketWriter*)&buf);
        DetachPacketBufferCopy((PacketWriter*)&buf, &out->qwc[pass], 0, &out->addr[pass], 0x19);
        PopBackMemoryMark();
        if (n < 2) {
            out->qwc[1] = out->qwc[0];
            out->addr[1] = out->addr[0];
            return;
        }
    }
}

// Toggles the VIF double-buffer base between its two halves (0x23C minus the current offset) and
// writes the new base offset into the VIF packet.
void FlipVifBaseOffset(void)
{
    s32 v = 0x23C - D_00262474;
    D_00262474 = v;
    WriteVifBaseOffset(&g_vifPacketWriter, v, 0);
}

// The part drawer func_001533A8 runs for each 0x70-byte part of a placed object: it writes the
// part's header block, its bone matrices and weights and the DMA references of its meshes.
struct ModelBone { u8 pad0[0x50]; Mat4 m; };
struct PartSkin {
    u8 pad0[4];
    ModelBone* bones;     // 0x04
    u8 pad8[0x38 - 0x8];
    u32 flags;              // 0x38
    u8 r, g, b, a;          // 0x3C
    s32 count;              // 0x40
    s32* words;             // 0x44
};
struct PartSlotIds { u16 f0; u16 f2; u16 meshBoneSlot; u16 meshSkinSlot; u16 stripBoneSlot; u16 stripSkinSlot; u16 fC; u16 fE; };
struct PartMesh {
    Quad16 pos;             // 0x00
    f32 radius;             // 0x10
    u8 pad14[4];
    u8* kind;               // 0x18
    PartSlotIds* slots;    // 0x1C
    u8 pad20[4];
    s32 nbones;             // 0x24
    s32 bones[4];           // 0x28
    s32 qwc0;               // 0x38
    s32 qwc1;               // 0x3C
    s32 qwc2;               // 0x40
    s32 addr0;              // 0x44
    s32 addr1;              // 0x48
    s32 addr2;              // 0x4C
};
struct PartStrip {
    PartSlotIds* slots;    // 0x00
    s32 nbones;             // 0x04
    s32 bones[4];           // 0x08
    s32 qwc;                // 0x18
    s32 addr;               // 0x1C
};
struct PartLight { u8 pad0[0x27C]; void* f27C; };
struct DrawnModelPart {
    u8 pad0[0x10];
    f32 radius;             // 0x10
    u8 pad14[4];
    s32 lit;                // 0x18
    u8 pad1C[0x28 - 0x1C];
    s32 skinned;            // 0x28
    u32 flags;              // 0x2C
    u8 pad30[0x40 - 0x30];
    QuadP fog;              // 0x40
    f32 radiusScale;        // 0x50
    s32 link;               // 0x54
    s32 nmeshes;            // 0x58
    PartMesh* meshes;    // 0x5C
    s32 nstrips;            // 0x60
    PartStrip* strips;   // 0x64
    u8 pad68[4];
    PartLight* light;    // 0x6C
};
struct MeshRangeCache {
    s32 f00;                // 0x00
    s32 f04;                // 0x04
    u8 pad08[4];
    s32 f0C;                // 0x0C
    s32 f10;                // 0x10
    u8 pad14[4];
    f32 lastTime;           // 0x18
    s32 count;              // 0x1C
    void* nodes[4];         // 0x20
};
struct PartLightCache {
    u8 pad0[4];
    MeshRangeCache* items;    // 0x04
    s32 lightFrame;         // 0x08
    s32 lightCount;         // 0x0C
    u8 pad10[0x18 - 0x10];
    s32 f18;                // 0x18
    u8 pad1C[0x20 - 0x1C];
    s32 refs[2];            // 0x20
};
struct PartOwnerClass { u8 pad0[8]; u32 flags; };
struct PartOwner { PartOwnerClass* cls; u8 pad4[0x410 - 4]; s32 f410; };
struct PartDrawRequest {
    u8 pad0[0x10];
    Mat4A m;                // 0x10
    f32 f50;                // 0x50
    f32 alpha;              // 0x54
    u8 pad58[8];
    Quad16 center;          // 0x60
    PartOwner* owner;    // 0x70
    PartSkin* skin;      // 0x74
    DrawnModelPart* part;      // 0x78
    PartLightCache* cache; // 0x7C
};
struct PartHeaderBatch {
    Mat4A m;                // 0x00
    Mat4A m40;              // 0x40
    QuadP fog;              // 0x80
    f32 f90;                // 0x90
    s32 mode;               // 0x94
    s32 f98;                // 0x98
    s32 lightCount;         // 0x9C
    union {
        Quad16 center;      // 0xA0
        struct { f32 pad[3]; f32 fAC; } w;
    };
};
struct ModelVifQuadword { u64 lo; u64 hi; };
struct ModelWorldView { u8 pad0[0x234C]; f32 f234C; };
extern s32 g_lightingChangeFrame;
extern s32 g_lightCount;
extern s32 g_frameCount;
extern Quad4* g_buildFrameData;
extern f32 g_gameClock[];
extern f32 g_gameTime;
s32 RangeRecordReachesSphere(void* node, void* v, f32 f);
struct VifPacketWriter {
    static u32* Open(PacketWriter* w)
    {
        u32* tag = (u32*)w->cur;
        *(u64*)w->cur = 0x10000000;
        w->cur += 16;
        return tag;
    }
    static void Cnt1(PacketWriter* w)
    {
        *(u64*)w->cur = 0x10000001;
        w->cur += 16;
    }
    static void Word(PacketWriter* w, u32 v)
    {
        *(u32*)w->cur = v;
        w->cur += 4;
    }
    static void Copy(PacketWriter* w, void* src, s32 size)
    {
        WordCopy::Words(w->cur, src, size >> 2);
        w->cur += size;
    }
    static void Pad(PacketWriter* w)
    {
        while (w->curU & 0xF) {
            *(u32*)w->cur = 0;
            w->cur += 4;
        }
    }
    static void Close(PacketWriter* w, u32* tag)
    {
        *tag |= ((w->cur - (u8*)tag) >> 4) - 1;
    }
    static void Refs(PacketWriter* w, s32 qwc, s32 addr)
    {
        *(u64*)w->cur = (s64)(qwc | 0x40000000) | ((s64)addr << 32);
        w->cur += 16;
    }
    static void Call(PacketWriter* w, s32 addr)
    {
        *(u64*)w->cur = ((s64)addr << 32) | 0x50000000;
        w->cur += 16;
    }
    static void Mscal(PacketWriter* w, u8* addr)
    {
        Word(w, ((u32)addr >> 3) | 0x14000000);
    }
    static void Mscalf(PacketWriter* w, u8* addr)
    {
        Word(w, ((u32)addr >> 3) | 0x15000000);
    }
    // A V4-32 unpack of num quadwords to addr (flags 0xC000): the command word is formed at its
    // store from the literal, so loop.c leaves the constant in the strip loop as retail does
    // (passed in as a parameter it lives from the inline's entry and is hoisted).
    static void UnpackV4(PacketWriter* w, void* src, s32 num, u32 addr)
    {
        *(u32*)w->cur = (num << 16) | addr | 0x6C00C000;
        w->cur += 4;
        Copy(w, src, num << 4);
    }
    // An unpack of size bytes with its command word and address: the source first, so its
    // address is expanded before the command (the bone loops' preheaders, in retail's order).
    static void UnpackAt(PacketWriter* w, void* src, s32 size, u32 cmd, u32 addr)
    {
        Word(w, cmd | addr);
        Copy(w, src, size);
    }
};
static inline u8 Alpha_166690(u8 a)
{
    if (a <= 0x40) {
        return a;
    }
    if ((s8)a >= 0) {
        return 0x40;
    }
    return 0x80;
}
static inline u64 Rgbaq_166690(u8 a, u8 r, u8 g, u8 b)
{
    return (u64)r | ((u64)g << 8) | ((u64)b << 16) | ((u64)a << 24) | (1ULL << 32);
}
// Draw callback of one model part (queued by QueuePlacedObjectModelParts): builds the DMA/VIF
// packets that draw the part's meshes and strips. Parts, in order:
//  1. Header batch: the part's matrix and its inverse, fog and the sphere centre.
//  2. Lighting mode b.mode, from the part's flags and its light cache: -1 unlit; 4 the part has its
//     own light, or is skinned (lights collected for the sphere); 2 no cache, collect fresh;
//     0 cache still valid and no dynamic light reaches the part (reuse the cached count);
//     1 cache valid plus dynamic lights; 3 cache stale, recollect and stamp it with the frame
//     (2 when only dynamic lights were found). The collected lights are in lights[].
//  3. Range records (collected when part->flags & 3 and the object has no per-mesh cache): the
//     records in reach of the sphere are queued after each mesh that passes the sphere test.
//  4. Fast path: with a cache holding a prebuilt call (cache->f18), unlit or cache-lit, an
//     unskinned part sends only the header and calls the cached packet; it flips the packet buffer
//     selector D_00262474 (0x28 or 0x214, i.e. 0x23C minus the other) back as needed. It is
//     skipped when any mesh's cache was used this game tick (goes to the slow path).
//  5. Meshes: each opens a packet with its bone matrices and skin words, then by kind (*e->kind)
//     sends the mesh data and, for kind 0, the lights per mode (refs to each light's data and
//     microprogram starts with the lit-batch programs); kinds 1, 6-10 send the data only; kinds 4
//     and 5 are sent and then skip the range records.
//  6. Strips (skipped when the skin hides the part or the alpha is <= 0): each opens a packet with
//     its bones and skin, the colour (the skin's, or the default colour D_002623E0) scaled by the
//     request's alpha, and refs the strip data.
// Packet data is either called (shared in front memory when part->link) or sent by reference.
void DrawModelPart(PartDrawRequest* self)
{
    PartHeaderBatch b;
    void* lights[128];
    void* nodes[16];
    ModelVifQuadword q;
    s32 n300;
    s32 n304;
    s32 n308;
    DrawnModelPart* part = self->part;
    PartOwner* owner = self->owner;
    PartLightCache* cache = self->cache;
    PartSkin* skin = self->skin;
    s32 useCache;
    s32 count;
    s32 i;
    s32 t;
    u32* tag;
    PartMesh* e;
    MeshRangeCache* c;
    f32 r;

    b.m = self->m;
    InvertRigidTransform(&self->m.m[3], &self->m, (Quad16*)&b.m40);
    b.fog = part->fog;
    n300 = 0;
    n304 = 0;
    if (part->lit != 0) {
        if (part->light != 0) {
            n304 = 1;
            n300 = 1;
            lights[0] = part->light->f27C;
            b.center = self->center;
            b.mode = 4;
            b.lightCount = 2;
        } else if (part->skinned != 0) {
            b.lightCount = CollectLightsForSphere(g_currentWorld, (const Vec4*)&self->center, part->radius, 1, 0x80, &n300, &n304, (LightObject**)lights);
            b.center = self->center;
            b.mode = 4;
        } else if (cache == 0) {
            b.lightCount = CollectLightsForSphere(g_currentWorld, (const Vec4*)&self->center, part->radius, 3, 0x80, &n300, &n304, (LightObject**)lights);
            b.mode = 2;
        } else if (cache->lightFrame >= g_lightingChangeFrame) {
            if (g_lightCount != 0) {
                b.lightCount = CollectLightsForSphere(g_currentWorld, (const Vec4*)&self->center, part->radius, 2, 0x80, 0, &n304, (LightObject**)lights);
            }
            if (n304 != 0) {
                b.mode = 1;
                if (b.lightCount < cache->lightCount) {
                    b.lightCount = cache->lightCount;
                }
            } else {
                b.mode = 0;
                b.lightCount = cache->lightCount;
            }
        } else {
            b.lightCount = CollectLightsForSphere(g_currentWorld, (const Vec4*)&self->center, part->radius, 7, 0x80, &n300, &n304, (LightObject**)lights);
            if (n300 == 0 && n304 > 0) {
                b.mode = 2;
            } else {
                b.mode = 3;
                cache->lightFrame = g_frameCount;
            }
            cache->lightCount = b.lightCount;
        }
    } else {
        b.mode = -1;
        b.lightCount = 2;
    }

    useCache = cache != 0 && (owner->cls->flags & 2) && owner->f410 != 0;
    n308 = 0;
    if (!useCache && (part->flags & 3)) {
        CollectRangeRecordsInReach(g_currentWorld, &self->center, 0x10, &n308, (RangeRecord**)nodes, part->radius);
    }
    b.f90 = self->f50;
    b.f98 = 1;
    if (part->flags & 4) {
        b.w.fAC = 1.0f;
    } else {
        b.w.fAC = ((ModelWorldView*)g_currentWorld)->f234C;
    }
    count = 0;

    if (cache != 0 && cache->f18 != 0 && (b.mode == -1 || b.mode == 0)
        && (useCache || n308 == 0) && !(skin->flags & 3)) {
        if (useCache) {
            for (i = 0; i < part->nmeshes; i++) {
                MeshRangeCache* t = &cache->items[i];
                if (t->count != 0 && t->lastTime == g_gameClock[1]) {
                    goto slow;
                }
            }
        }
        {
            s32 half = D_00262474 != 0x28;
            D_00262474 = 0x23C - D_00262474;
            tag = VifPacketWriter::Open(&g_vifPacketWriter);
            VifPacketWriter::Word(&g_vifPacketWriter, D_00262474 | 0x03000000);
            VifPacketWriter::Word(&g_vifPacketWriter, 0x02000000);
            VifPacketWriter::UnpackV4(&g_vifPacketWriter, &b, 0xB, 0);
            VifPacketWriter::Pad(&g_vifPacketWriter);
            VifPacketWriter::Close(&g_vifPacketWriter, tag);
            VifPacketWriter::Call(&g_vifPacketWriter, cache->refs[half]);
            if ((part->nmeshes + part->nstrips) & 1) {
                return;
            }
            D_00262474 = 0x23C - D_00262474;
            return;
        }
    }
slow:
    for (i = 0; i < part->nmeshes; i++) {
        s32 k;
        s32 j;
        s32 n;
        e = &part->meshes[i];
        if (cache != 0) {
            c = &cache->items[i];
        } else {
            c = 0;
        }
        D_00262474 = 0x23C - D_00262474;
        tag = VifPacketWriter::Open(&g_vifPacketWriter);
        count++;
        VifPacketWriter::Word(&g_vifPacketWriter, D_00262474 | 0x03000000);
        VifPacketWriter::Word(&g_vifPacketWriter, 0x02000000);
        if (count == 1) {
            VifPacketWriter::UnpackV4(&g_vifPacketWriter, &b, 0xB, 0);
        }
        if (e->nbones > 0) {
            u32 addr = e->slots->meshBoneSlot;
            for (k = 0; k < e->nbones; k++) {
                VifPacketWriter::UnpackAt(&g_vifPacketWriter, &skin->bones[e->bones[k]].m, 0x40, 0x6C04C000, addr);
                addr += 4;
            }
        }
        n = skin->count;
        if (n > 0) {
            VifPacketWriter::UnpackAt(&g_vifPacketWriter, skin->words, n << 2, (n << 16) | 0x6000C000, e->slots->meshSkinSlot);
        }
        VifPacketWriter::Pad(&g_vifPacketWriter);
        VifPacketWriter::Close(&g_vifPacketWriter, tag);

        switch (*e->kind) {
        case 0:
            VifPacketWriter::Refs(&g_vifPacketWriter, e->qwc0, e->addr0);
            switch (b.mode) {
            case 0:
                if (part->link) {
                    VifPacketWriter::Call(&g_vifPacketWriter, e->addr2);
                } else {
                    VifPacketWriter::Refs(&g_vifPacketWriter, e->qwc2, e->addr2);
                }
                VifPacketWriter::Refs(&g_vifPacketWriter, c->f00, c->f04);
                VifPacketWriter::Refs(&g_vifPacketWriter, c->f0C, c->f10);
                break;
            case 1:
                VifPacketWriter::Refs(&g_vifPacketWriter, c->f0C, c->f10);
                VifPacketWriter::Refs(&g_vifPacketWriter, e->qwc1, e->addr1);
                for (k = 0; k < n304; k++) {
                    ConeVolume* l = (ConeVolume*)lights[k];
                    VifPacketWriter::Refs(&g_vifPacketWriter, l->packetSize, (s32)l->packet);
                }
                VifPacketWriter::Cnt1(&g_vifPacketWriter);
                VifPacketWriter::Mscal(&g_vifPacketWriter, g_litBatchSecondProgram);
                VifPacketWriter::Word(&g_vifPacketWriter, 0x10000000);
                VifPacketWriter::Word(&g_vifPacketWriter, 0);
                VifPacketWriter::Word(&g_vifPacketWriter, 0);
                if (part->link) {
                    VifPacketWriter::Call(&g_vifPacketWriter, e->addr2);
                } else {
                    VifPacketWriter::Refs(&g_vifPacketWriter, e->qwc2, e->addr2);
                }
                VifPacketWriter::Cnt1(&g_vifPacketWriter);
                VifPacketWriter::Mscal(&g_vifPacketWriter, g_litBatchFinishProgram);
                VifPacketWriter::Word(&g_vifPacketWriter, 0x10000000);
                VifPacketWriter::Word(&g_vifPacketWriter, 0);
                VifPacketWriter::Word(&g_vifPacketWriter, 0);
                break;
            case 2:
            case 4:
                VifPacketWriter::Refs(&g_vifPacketWriter, e->qwc1, e->addr1);
                for (k = 0; k < n304; k++) {
                    ConeVolume* l = (ConeVolume*)lights[k];
                    VifPacketWriter::Refs(&g_vifPacketWriter, l->packetSize, (s32)l->packet);
                }
                VifPacketWriter::Cnt1(&g_vifPacketWriter);
                VifPacketWriter::Mscal(&g_vifPacketWriter, g_litBatchSecondProgram);
                VifPacketWriter::Word(&g_vifPacketWriter, 0x10000000);
                VifPacketWriter::Word(&g_vifPacketWriter, 0);
                VifPacketWriter::Word(&g_vifPacketWriter, 0);
                if (part->link) {
                    VifPacketWriter::Call(&g_vifPacketWriter, e->addr2);
                } else {
                    VifPacketWriter::Refs(&g_vifPacketWriter, e->qwc2, e->addr2);
                }
                VifPacketWriter::Cnt1(&g_vifPacketWriter);
                VifPacketWriter::Mscalf(&g_vifPacketWriter, g_litBatchFinishProgram);
                VifPacketWriter::Word(&g_vifPacketWriter, 0);
                VifPacketWriter::Word(&g_vifPacketWriter, 0);
                VifPacketWriter::Word(&g_vifPacketWriter, 0);
                break;
            case 3: {
                VifPacketWriter::Refs(&g_vifPacketWriter, e->qwc1, e->addr1);
                for (k = 0; k < n300; k++) {
                    ConeVolume* l = (ConeVolume*)lights[k];
                    VifPacketWriter::Refs(&g_vifPacketWriter, l->packetSize, (s32)l->packet);
                }
                VifPacketWriter::Cnt1(&g_vifPacketWriter);
                VifPacketWriter::Mscal(&g_vifPacketWriter, g_litBatchSecondProgram);
                VifPacketWriter::Word(&g_vifPacketWriter, 0x90000000);
                VifPacketWriter::Word(&g_vifPacketWriter, 0);
                VifPacketWriter::Word(&g_vifPacketWriter, 0);
                {
                    s32 base = D_00262474;
                    u32* p = (u32*)g_buildFrameData++;
                    p[0] = ((base + e->slots->f0) << 4) + 0x1100C000;
                    p[1] = ((base + e->slots->f2) << 4) + 0x1100C000;
                    p[2] = ((base + e->slots->fE) << 4) + 0x1100C000;
                    p[3] = (u32)c;
                }
                if (k < n304) {
                    VifPacketWriter::Refs(&g_vifPacketWriter, e->qwc1, e->addr1);
                    for (k = 0; k < n304; k++) {
                        ConeVolume* l = (ConeVolume*)lights[k];
                        VifPacketWriter::Refs(&g_vifPacketWriter, l->packetSize, (s32)l->packet);
                    }
                    VifPacketWriter::Cnt1(&g_vifPacketWriter);
                    VifPacketWriter::Mscal(&g_vifPacketWriter, g_litBatchSecondProgram);
                    VifPacketWriter::Word(&g_vifPacketWriter, 0);
                    VifPacketWriter::Word(&g_vifPacketWriter, 0);
                    VifPacketWriter::Word(&g_vifPacketWriter, 0);
                }
                if (part->link) {
                    VifPacketWriter::Call(&g_vifPacketWriter, e->addr2);
                } else {
                    VifPacketWriter::Refs(&g_vifPacketWriter, e->qwc2, e->addr2);
                }
                VifPacketWriter::Cnt1(&g_vifPacketWriter);
                VifPacketWriter::Mscalf(&g_vifPacketWriter, g_litBatchFinishProgram);
                VifPacketWriter::Word(&g_vifPacketWriter, 0);
                VifPacketWriter::Word(&g_vifPacketWriter, 0);
                VifPacketWriter::Word(&g_vifPacketWriter, 0);
                break;
            }
            }
            break;
        case 1:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            if (part->link) {
                VifPacketWriter::Call(&g_vifPacketWriter, e->addr0);
            } else {
                VifPacketWriter::Refs(&g_vifPacketWriter, e->qwc0, e->addr0);
            }
            break;
        case 4:
            if (part->link) {
                VifPacketWriter::Call(&g_vifPacketWriter, e->addr0);
            } else {
                VifPacketWriter::Refs(&g_vifPacketWriter, e->qwc0, e->addr0);
            }
            continue;
        case 5:
            if (part->link) {
                VifPacketWriter::Call(&g_vifPacketWriter, e->addr0);
            } else {
                VifPacketWriter::Refs(&g_vifPacketWriter, e->qwc0, e->addr0);
            }
            continue;
        default:
            continue;
        }

        if (useCache) {
            if (c->lastTime == g_gameTime) {
                n308 = c->count;
            } else {
                n308 = 0;
            }
        }
        if (n308 != 0) {
            TransformByMatrixWithW((const Quad16*)&b, (const Vec4*)e, 1.0f, (Vec4*)&q);
            r = e->radius * part->radiusScale;
        }
        for (j = 0; j < n308; j++) {
            void* node;
            if (useCache) {
                node = c->nodes[j];
            } else {
                node = nodes[j];
                if (RangeRecordMatchesKinds((RangeRecord*)node, part->flags) == 0) {
                    continue;
                }
            }
            if (RangeRecordReachesSphere(node, &q, r) != 0) {
                QueueRangeRecordPacket((RangeRecord*)node);
            }
        }
    }

    if (skin != 0 && (skin->flags & 1)) {
        return;
    }
    if (self->alpha <= 0.0f) {
        return;
    }
    for (t = 0; t < part->nstrips; t++) {
        PartStrip* s = &part->strips[t];
        s32 n;
        if (skin != 0 && (skin->flags & 2)) {
            u8 a = Alpha_166690((s32)(skin->a * self->alpha));
            q.hi = 1;
            q.lo = Rgbaq_166690(a, skin->r, skin->g, skin->b);
        } else {
            q.lo = Rgbaq_166690(Alpha_166690((s32)(g_defaultModelColor.a * self->alpha)), g_defaultModelColor.r, g_defaultModelColor.g, g_defaultModelColor.b);
            q.hi = 1;
        }
        D_00262474 = 0x23C - D_00262474;
        tag = VifPacketWriter::Open(&g_vifPacketWriter);
        count++;
        VifPacketWriter::Word(&g_vifPacketWriter, D_00262474 | 0x03000000);
        VifPacketWriter::Word(&g_vifPacketWriter, 0x02000000);
        if (count == 1) {
            VifPacketWriter::UnpackV4(&g_vifPacketWriter, &b, 0xB, 0);
        }
        if (s->nbones > 0) {
            u32 addr = s->slots->stripBoneSlot;
            s32 k;
            for (k = 0; k < s->nbones; k++) {
                VifPacketWriter::UnpackAt(&g_vifPacketWriter, &skin->bones[s->bones[k]].m, 0x40, 0x6C04C000, addr);
                addr += 4;
            }
        }
        n = skin->count;
        if (n > 0) {
            VifPacketWriter::UnpackAt(&g_vifPacketWriter, skin->words, n << 2, (n << 16) | 0x6000C000, s->slots->stripSkinSlot);
        }
        VifPacketWriter::UnpackV4(&g_vifPacketWriter, &q, 1, 0x1A);
        VifPacketWriter::Pad(&g_vifPacketWriter);
        VifPacketWriter::Close(&g_vifPacketWriter, tag);
        VifPacketWriter::Refs(&g_vifPacketWriter, s->qwc, s->addr);
    }
}
