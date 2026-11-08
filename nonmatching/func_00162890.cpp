// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 4207/4264 (98.7%), checked 2026-11-08
// NEAR (2026-11-08, worker large-162890): every instruction is retail's and every register but
// two; left: the spill slots 0x138-0x168 hold the same values in another order, and the morph
// loop's weights size multiplies in v0 where retail's uses s0.
// Found: the bit locals declared after the if/else on `flags & 1` (GCSE's PRE copies them into
// both arms, as retail's); declared 1, 2, 0x200, 4, ..., 0x80, 0x100 they get retail's order and
// registers (the 0x100 and, which kills flags, is scheduled first). `outs` as an object whose
// inline constructor clears it gives retail's addiu sp,192 at each use (an array cleared by a
// FillMemory call is hoisted out of the loop by PRE). The three writers as an array of a class
// whose constructor calls InitPacketWriter give the countdown loop (to -1); the morph loop's one
// writer needs InitPacketWriter(&pw) called directly for retail's addiu sp,80 (with the inline
// constructor it is a hoisted pseudo). C-style declarations at the top of each loop body give
// the spill order of 0x100-0x134 (the reference count after the uv pointer, ents before verts).
// Still differs: 0x138-0x168 are PRE's reaching registers, laid out in pseudo order, and PRE
// makes them in hash-bucket order. hash(plus R C) = (13258+R+C) mod T, hash(and R C) =
// (13266+R+C) mod T, ours T=481 (gcse dump). Retail's order (&m->addr, flags&0x100, pw,
// &pw.begin, &pw.cur, i+1, j+1, k+1, flags&1, &start, &part->fog, t+1, &m->qwc) needs T=483 with
// j and k declared before flags (done here) and the morph index t at pseudo 718-721 (ours 664,
// m = t+3): about 54 more pseudos before the morph loop and 2-4 more insns at gcse. Not found
// (build/swarm/large-162890/model.py and probe.py compute and read the order).
#include "common.h"
#include "strip_mesh.h"
#include "shapes.h"

void* AllocateFrontMemory(s32 size);
void* AllocateZeroedFrontMemory(s32 bytes);
void PushBackMemoryMark(void);
u8* AllocateBackMemory(s32 size);
void PopBackMemoryMark(void);
void* FillMemory(void* p, s32 value, s32 size);

struct PacketSlot {
    u8* end;
    u8* begin;
    s32* f08;
    u8* cur;
    u8 pad10[0x24 - 0x10];
};
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
struct StripExtra {
    s32 f0;
    s32 a4[4];
    s32 a14[4];
    s32 a24[4];
};
struct StripUnpack {
    u16 off[4];
    u16 strip[4];
    u16 f10;
    u16 f12;
    u16 pad14[2];
};

// A placed object's model, read from the level stream (func_00162890).
struct ModelLink;
struct ModelPart;
struct ModelStrip;
struct ModelRecord;

// The 0x90-byte record a part with flag 0x100 links to its model.
struct ModelLink {
    s32 owner;              // 0x00
    ModelPart* part;        // 0x04
    s32 id;                 // 0x08
    u8 pad0C[4];
    s32 f10;                // 0x10
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
    f32 f10;                // 0x10
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
    void* f0;
    void* f4;
    void* f8;
    void* fC;
    void* f10;
    void* f14;
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

void InitPacketWriter(PacketSlot* p);

// A packet buffer of the model reader, set up where it is declared.
struct StripPacket : PacketSlot {
    StripPacket() { InitPacketWriter(this); }
};

struct StripOutputs {
    s32* p[3];
    StripOutputs() { FillMemory(this, 0, sizeof(*this)); }
};

// A pointer into a packet buffer moved with its copy.
struct MovedPointer {
    static void Fix(s32* p, u32 start, u32 size, u32 to)
    {
        if (p) {
            u32 v = *p;
            if (v >= start && v < start + size)
                *p = v + (to - start);
        }
    }
};

s32 ReadBufferedU8(void* stream);
s32 ReadBufferedU16(void* stream);
s32 ReadBufferedS16(void* stream);
s32 ReadBufferedS8(void* stream);
u32 ReadBufferedU32(void* stream);
f32 ReadBufferedFloat(void* stream);
void ReadBufferedStreamBytes(void* stream, s32 size, void* dst);
void ReadBufferedMatrix4(void* stream, void* dst);
void ReadBufferedVector3(void* stream, void* dst);
void ReadBufferedVector4(void* stream, void* dst);
void AlignBufferedStreamPosition(void* stream, s32 n);
ModelAnimator* ReadAnimator(void* stream);
void* CopyToFrontMemory(s32 size, void* src);
void ComputeCameraFogTerms(u8* camera, f32* out, f32 p);
void CopyAttachmentPart(ModelRecord* self, ModelPart* part, ModelPose* pose);
void CollectNonNullRefs(ModelRecord* self);
void InitPacketWriter(PacketSlot* p);
void AllocateTempPacketBuffer(PacketSlot* p, s32 size);
void DetachPacketBufferCopy(PacketSlot* p, s32* qwc, u32* start, u32* addr, s32 flags);
void RemapMeshQueueValues(s32 idx, u32 lo, u32 take, u32 give);
void BuildStripMeshPacket(ModelRecord* self, ModelPart* obj, s32 mode, ModelStrip* hdr, StripMesh* mesh,
                   Vec3* vecs, Vec3* nrms, u8 (*tints)[4], MeshUv* uvs, s32 n, VertexRefs* recs,
                   WeightIndices* ents, Vec3* verts, Vec3* vnrms, f32* weights, PacketSlot* pkt,
                   s32** outs);
void BuildLitStripMeshPacket(ModelRecord* self, ModelPart* obj, s32 unused2, s32 mode, ModelStrip* hdr,
                   StripMesh* mesh, Vec3* vecs, Vec3* nrms, u8 (*tints)[4], MeshUv* uvs,
                   s32 n, VertexRefs* recs, WeightIndices* ents, Vec3* verts, Vec3* vnrms,
                   f32* weights, PacketSlot* pkt, s32** outs);
void BuildMorphTargetPacket(ModelRecord* self, s32 mode, ModelMorph* hdr, s32 n, Vec3* vecs, s32 extra,
                   void* extraData, WeightIndices* ents, Vec3* verts, f32* data, PacketSlot* pkt);
void BuildPartVifPackets(ModelPart* a, ModelStrip* b, StripPackets* c);
extern u8* g_camera;
extern s32 g_meshQueueCount;
extern u8* g_animRecords;

void ReadPlacedObjectModel(ModelRecord* self, void* stream, s32 owner)
{
    s32 i;
    s32 a;
    s32 b;

    self->nanimators = 0;
    a = ReadBufferedU8(stream);
    b = ReadBufferedU8(stream);
    self->nids = ReadBufferedU8(stream);
    self->links = AllocateZeroedFrontMemory(self->nids * 0x90);
    self->ids = (s32*)AllocateZeroedFrontMemory(self->nids << 2);
    for (s32 n = 0; n < self->nids; n++) {
        self->ids[n] = ReadBufferedS16(stream);
    }
    self->nweights = ReadBufferedU8(stream);
    self->weights = AllocateZeroedFrontMemory(self->nweights << 2);
    ReadBufferedStreamBytes(stream, self->nweights << 2, self->weights);
    self->weightsCopy = CopyToFrontMemory(self->nweights << 2, self->weights);
    self->count = ReadBufferedU16(stream);
    self->parts = (ModelPart*)AllocateZeroedFrontMemory(self->count * 0x70);
    self->poses = (ModelPose*)AllocateZeroedFrontMemory(self->count * 0x28);
    for (i = 0; i < self->count; i++) {
        ModelPart* part = &self->parts[i];
        ModelPose* pose = &self->poses[i];
        s32 j;
        s32 k;
        s32 flags = ReadBufferedU16(stream);
        if (flags & 1) {
            s32 idx = ReadBufferedS16(stream);
            *part = self->parts[idx];
            *pose = self->poses[idx];
            part->matrix = AllocateFrontMemory(0x40);
            ReadBufferedMatrix4(stream, part->matrix);
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
            pose->f0 = ReadBufferedU32(stream);
        }
        if (hasF50) {
            part->f50 = ReadBufferedFloat(stream);
        }
        if (hasScale) {
            f32 v = ReadBufferedFloat(stream);
            if (v == 3.402823466e+38f) {
                part->f24 = 3.402823466e+38f;
            } else {
                part->f24 = v * __builtin_fabsf(v);
            }
        }
        if (hasF3C) {
            part->f3C = ReadBufferedFloat(stream);
        }
        if (hasFar) {
            part->far = ReadBufferedFloat(stream);
            if (part->far == 3.402823466e+38f) {
                part->far = 1.0e10f;
            }
        }
        if (hasNear) {
            part->near = ReadBufferedFloat(stream);
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
            ReadBufferedVector3(stream, part->vecs);
            ReadBufferedVector4(stream, part->vecs + 4);
        } else {
            part->vecs = 0;
        }
        if (hasLink) {
            ModelLink* link = (ModelLink*)AllocateZeroedFrontMemory(0x90);
            link->owner = owner;
            link->part = part;
            link->id = ReadBufferedS16(stream);
            link->bone = ReadBufferedS8(stream);
            if (link->bone != -1) {
                link->f24 = ReadBufferedFloat(stream);
                link->f28 = ReadBufferedFloat(stream);
                link->f2C = ReadBufferedFloat(stream);
                link->f30 = ReadBufferedFloat(stream);
                ReadBufferedMatrix4(stream, link->matrix);
            }
            link->f10 = ReadBufferedU8(stream);
            link->f14 = ReadBufferedU8(stream);
            link->f18 = ReadBufferedU8(stream);
            part->link = link;
            link->next = self->head;
            self->head = link;
        } else {
            part->link = 0;
        }
        ReadBufferedVector3(stream, part);
        part->f10 = ReadBufferedFloat(stream);
        ReadBufferedS16(stream);
        part->f34 = ReadBufferedU8(stream);
        part->f14 = ReadBufferedU8(stream);
        part->f2C = ReadBufferedU8(stream);
        ComputeCameraFogTerms(g_camera, part->fog, part->f3C);
        if (copied) {
            CopyAttachmentPart(self, part, pose);
        } else {
            k = 0;
            part->nstrips = ReadBufferedU16(stream);
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
                s32 size;
                PushBackMemoryMark();
                ReadBufferedVector3(stream, strip);
                strip->f10 = ReadBufferedFloat(stream);
                nvecs = ReadBufferedU8(stream);
                nnrms = ReadBufferedU8(stream);
                ntints = ReadBufferedU8(stream);
                nuvs = ReadBufferedU8(stream);
                nrefs = ReadBufferedU8(stream);
                AlignBufferedStreamPosition(stream, 4);
                vecs = (Vec3*)AllocateBackMemory(nvecs * 12);
                ReadBufferedStreamBytes(stream, nvecs * 12, vecs);
                nrms = (Vec3*)AllocateBackMemory(nnrms * 12);
                ReadBufferedStreamBytes(stream, nnrms * 12, nrms);
                tints = (u8 (*)[4])AllocateBackMemory(ntints * 4);
                ReadBufferedStreamBytes(stream, ntints * 4, tints);
                uvs = (MeshUv*)AllocateBackMemory(nuvs * 8);
                ReadBufferedStreamBytes(stream, nuvs * 8, uvs);
                refs = (VertexRefs*)AllocateBackMemory(nrefs * 4);
                ReadBufferedStreamBytes(stream, nrefs * 4, refs);
                mesh = (StripMesh*)(g_animRecords + ReadBufferedU16(stream) * 0x28);
                strip->mesh = mesh;
                strip->f14 = ReadBufferedU8(stream);
                strip->nkeys = ReadBufferedU8(stream);
                for (s32 n = 0; n < strip->nkeys; n++) {
                    strip->keys[n] = ReadBufferedU8(stream);
                }
                size = strip->nkeys * nvecs << 2;
                weights = (f32*)AllocateBackMemory(size);
                ReadBufferedStreamBytes(stream, size, weights);
                if (self->nweights != 0) {
                    s32 w;
                    size = ReadBufferedU16(stream) * 12;
                    verts = (Vec3*)AllocateBackMemory(size);
                    ReadBufferedStreamBytes(stream, size, verts);
                    size = ReadBufferedU16(stream) * 12;
                    vnrms = (Vec3*)AllocateBackMemory(size);
                    ReadBufferedStreamBytes(stream, size, vnrms);
                    ents = (WeightIndices*)AllocateBackMemory(self->nweights << 3);
                    for (w = 0; w < self->nweights; w++) {
                        ents[w].pos = (u16*)AllocateBackMemory(nrefs << 1);
                        ReadBufferedStreamBytes(stream, nrefs << 1, ents[w].pos);
                        ents[w].nrm = (u16*)AllocateBackMemory(nrefs << 1);
                        ReadBufferedStreamBytes(stream, nrefs << 1, ents[w].nrm);
                    }
                }
                StripPacket pw[3];
                s32 queued = g_meshQueueCount;
                for (s32 n = 0; n < 3; n++) {
                    AllocateTempPacketBuffer(&pw[n], 0x400);
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
                    BuildStripMeshPacket(self, part, k++, strip, mesh, vecs, nrms, tints, uvs, nrefs, refs,
                                         ents, verts, vnrms, weights, pw, outs.p);
                    break;
                case 0:
                    BuildLitStripMeshPacket(self, part, b, k++, strip, mesh, vecs, nrms, tints, uvs, nrefs,
                                            refs, ents, verts, vnrms, weights, pw, outs.p);
                    break;
                }
                u32 starts[3];
                for (s32 n = 0; n < 3; n++) {
                    if (pw[n].cur != pw[n].begin) {
                        DetachPacketBufferCopy(&pw[n], &strip->qwc[n], &starts[n], &strip->addr[n], 0x13);
                        RemapMeshQueueValues(queued, strip->qwc[n] << 4, starts[n], strip->addr[n]);
                        MovedPointer::Fix(outs.p[1], starts[n], strip->qwc[n] << 4, strip->addr[n]);
                        MovedPointer::Fix(outs.p[2], starts[n], strip->qwc[n] << 4, strip->addr[n]);
                        StripExtra* e = strip->extra;
                        if (e != 0) {
                            MovedPointer::Fix(&e->f0, starts[n], strip->qwc[n] << 4, strip->addr[n]);
                            for (s32 m = 0; m < part->link->f10; m++) {
                                MovedPointer::Fix(&e->a4[m], starts[n], strip->qwc[n] << 4, strip->addr[n]);
                                MovedPointer::Fix(&e->a14[m], starts[n], strip->qwc[n] << 4, strip->addr[n]);
                                MovedPointer::Fix(&e->a24[m], starts[n], strip->qwc[n] << 4, strip->addr[n]);
                            }
                        }
                    }
                }
                strip->unpack = (StripUnpack*)((u8*)strip->unpack + (strip->addr[0] - starts[0]));
                BuildPartVifPackets(part, strip, pp);
                PopBackMemoryMark();
            }
            part->nmorphs = ReadBufferedU16(stream);
            part->morphs = (ModelMorph*)AllocateZeroedFrontMemory(part->nmorphs << 5);
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
                s32 size;
                PushBackMemoryMark();
                nvecs = ReadBufferedU8(stream);
                vecs = (Vec3*)AllocateBackMemory(nvecs * 12);
                ReadBufferedStreamBytes(stream, nvecs * 12, vecs);
                nextra = ReadBufferedU8(stream);
                extra = AllocateBackMemory(nextra << 2);
                ReadBufferedStreamBytes(stream, nextra << 2, extra);
                m->nkeys = ReadBufferedU8(stream);
                for (n = 0; n < m->nkeys; n++) {
                    m->keys[n] = ReadBufferedU8(stream);
                }
                size = m->nkeys * nvecs << 2;
                weights = (f32*)AllocateBackMemory(size);
                ReadBufferedStreamBytes(stream, size, weights);
                if (self->nweights != 0) {
                    s32 w;
                    size = ReadBufferedU16(stream) * 12;
                    verts = (Vec3*)AllocateBackMemory(size);
                    ReadBufferedStreamBytes(stream, size, verts);
                    ents = (WeightIndices*)AllocateBackMemory(self->nweights << 3);
                    for (w = 0; w < self->nweights; w++) {
                        ents[w].pos = (u16*)AllocateBackMemory(nvecs << 1);
                        ReadBufferedStreamBytes(stream, nvecs << 1, ents[w].pos);
                        ents[w].nrm = 0;
                    }
                }
                PacketSlot pw;
                InitPacketWriter(&pw);
                s32 queued = g_meshQueueCount;
                AllocateTempPacketBuffer(&pw, (self->nweights << 7) + 0x400);
                BuildMorphTargetPacket(self, k++, m, nvecs, vecs, nextra, extra, ents, verts, weights, &pw);
                u32 start;
                DetachPacketBufferCopy(&pw, &m->qwc, &start, &m->addr, 0x13);
                RemapMeshQueueValues(queued, m->qwc << 4, start, m->addr);
                m->p = (u16*)((u8*)m->p + (m->addr - start));
                PopBackMemoryMark();
            }
        }
    }
    CollectNonNullRefs(self);
}
