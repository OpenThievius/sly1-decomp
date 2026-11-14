// SPDX-License-Identifier: AGPL-3.0-or-later
// The source file from 0x1F2758 to 0x1F59C4, built whole (config/us/files.tsv): it starts where
// warp_menu.cpp's _GLOBAL_$I$ ends and ends where the libraries begin (config/us/layout.tsv).
// Its .rodata is the two jump tables of its assembly at 0x24E840 and 0x24E860; it has no .data
// or .bss. Its .rodata range runs to 0x24E980, where src/lib/library_state.c's begins, and holds
// after the jump tables the character class table (0x24E878 to 0x24E979, from the disassembly),
// which could be this file's, library_state.c's or a library file's of its own. Its name is ours,
// after its first and largest family, the oscillator; the transform objects, arrival points,
// object sub-groups and contact trackers after it are smaller.
#include "transform_object.h"
#include "warp_page.h"
#include "oscillator.h"
#include "camera.h"
#include "game_clock.h"
#include "list_iter.h"
#include "screen_element.h"
#include "shapes.h"
#include "globals.h"
#include "game_progress.h"
#include "screen_fade.h"
#include "pad_record.h"
#include "object_link.h"
#include "contact_tracker.h"
#include "lookup_object.h"
#include "object_sub_group.h"
#include "switched_collider.h"
#include "animation.h"
#include "object_gatherer.h"
#include "asm_func.h"
#include "vu0.h"
#include "fpu.h"
#include "hit_target.h"
#include "value_range.h"
#include "common.h"
#include "object_finder.h"
#include "functions/buffered_stream.h"
#include "functions/camera.h"
#include "functions/collider.h"
#include "functions/collider_contact.h"
#include "functions/command_channel.h"
#include "functions/commentary_best_time.h"
#include "functions/on_off_object.h"
#include "functions/path_follower.h"
#include "functions/placed_object.h"
#include "functions/screen_element.h"
#include "functions/switched_collider.h"
#include "functions/warp_menu.h"
#include "functions/world.h"
#include "functions/zone_collider.h"
struct PlacedObject;
struct World;

struct VectorList4;


// Types other files define, named by the parameters of their functions declared here.
struct TargetArcSource;
struct TargetHit;
struct NodeQuery;

struct NoiseOctave { f32 w; f32 x; f32 y; f32 z; };
struct NoiseBlend { f32 lo; f32 hi; f32 scale; s32 count; NoiseOctave items[1]; };

f32 SampleSmoothNoise(f32 a, f32 b, f32 c);
f32 ApplyBiasCurve(f32 a, f32 b);

struct VectorListItem { f32 a; f32 b; f32 c; f32 d; };
struct VectorList4 { u8 pad[0xC]; u32 count; VectorListItem items[4]; };

void* GetOscillatorCurrentEntry(Oscillator* obj, s32 value, s32 flag);

// The scale (the reciprocal of the period) of an oscillator entry.
struct OscillatorEntryScale { u8 pad[0x64]; f32 scale; };

void* GetOscillatorEntryForPeriod(Oscillator* self, s32 mode);


void* GetOscillatorEntryForPeriod(Oscillator* self, s32 mode);

void* GetOscillatorEntryForVectors(void* self, s32 mode);
void AppendVector4ToBuffer(VectorList4* buf, f32 x, f32 y, f32 z, f32 w);

void* GetOscillatorEntryForVectors(void* self, s32 mode);
void AppendVector4ToBuffer(VectorList4* buf, f32 x, f32 y, f32 z, f32 w);

struct BufferedStream;
void ReadPropertyRecords(void* a, void* b);

void ReparentObject(BaseObject* self, BaseObject* parent);



void InitObject(void* self);

struct OwnedNode { u8 pad0[0xC]; void* owner0C; u8 pad1[0x84 - 0x10]; OwnedNode* next84; };
struct OwnerSlot { s32 link; u8 pad0[0x3C]; };
struct SlotPointers { u8 pad0[4]; void* listA[4]; void* listB[1]; };
struct AttachmentElement { u8 pad0[0x20]; SlotPointers* sub20; u8 pad1[0x2C]; };
struct NodeAttachment { u8 pad0[0x54]; OwnedNode* node54; s32 count58; AttachmentElement* elems5C; };
struct NodeOwner { u8 pad0[0x3C]; s32 count3C; u8 pad1[0x6E0 - 0x40]; OwnerSlot items6E0[4]; OwnerSlot items7E0[1]; u8 pad2[0x8E0 - 0x820]; OwnedNode* head8E0; };


void ReadPropertyRecords(void* a, void* b);
void* AllocateFrontMemory(int size);
void* CreateTypedRecord(s32 index, void* a1, BaseObject* a2, s32 a3, s32 a4);
struct BufferedStream;


void StartObject(BaseObject* self);
void ResolveAndStartObject(BaseObject* self);

void* GetOscillatorCurrentEntry(Oscillator* obj, s32 value, s32 flag);


struct OscillatorAxisEntry {
    s32 kind;
    s32 frame;
    u8 pad8[0x8];
    Quad16 q10;
    u8 pad20[0x40];
    s32 row;
};

void InitObject(BaseObject* self);

// NEAR: the two counter increments (0x38 and 0x6D0) are computed in the reverse
// order of retail (addiu v0 before addiu v1); no statement order tried changed it.

struct OscillatorPlaneEntry {
    s32 a;
    u8 pad0[0x0C];
    Quad16 q10;
    Quad16 q20;
    u8 pad1[0x08];
    f32 secondBlendScale;
    u8 pad2[0x4C];
    f32 firstBlendScale;
};

void CopyObjectData(BaseObject* self, BaseObject* src);
BaseObject* CreateObjectCopy(BaseObject* self, World* world, BaseObject* parent);

extern f32 g_gameTime;

f32 HashToUnitFloat(s32 i);



struct MinOf {
    static s32 Of(s32 a, s32 b) { return a < b ? a : b; }
};

extern s32 (*g_warpCursorTables[6])[4];



#include "common.h"
struct KeyedEntry;
struct TrackedNodeOffer;
struct ScaledTransform;
struct Mat02;
struct Vec02;


struct Rec36;
void OfferTrackedNodeLaunch(Rec36* self, void* a1, TrackedNodeOffer* out);
struct TimedValue { u8 pad[0x98]; s32 state; f32 value; };





struct ZoneTargetEntry;
void FillTrackedNodes(Rec36* self);



HoldingMember* FindArrivalPoint(s32 id, s32 parent);
void PlaceAtArrivalPoint(TransformSet* self);

// NEAR: only the vtbl[19] load differs: retail loads it into $v1 (lw v1,76(v1)), we use $v0 for the test and the call.



extern f32 g_gameTime;

s32 GetEntryIdByKey(KeyedEntry* key);
s32 GetLevelEntryWord(s32 a0);








// The offer func_001F57E0 fills: the tracker's word, the tracker, and the launch to call.
struct TrackedNodeOffer { s32 f0; s32 f4; Rec36* tracker; void* launch; };

void TriggerScriptEvent(BaseObject* self, s32 idx, s32 flag, void* out);

void CopyMemory(void* dst, void* src, u32 size);

extern u8 g_objectFadeIn[];

// The word at 0x78 of the current level's record (G27C230): bit 0 picks the level's own fade.
struct LevelRecordWord78 {
    u8 pad00[0x78];
    s32 flags;
};

// What StartObjectFade (func_001F0428) fades: the entry LookupEntryById gives for a level.
struct LevelFadeEntry { s32 unused; };
LevelFadeEntry* LookupEntryById(s32 k);
void StartObjectSubGroupFinish(ObjectSubGroup* self);

struct TrackedTargetChoice {
    u8 pad00[0x0C];
    s32 cnt;            // 0x0C
    u8 pad10[0x84];
    s32 s94;            // 0x94
};
struct TargetLaunchFrame {
    s32 a[4];           // 0x00
    u8 pad10[0x10];
    s32 b[4];           // 0x20
    s32 c[4];           // 0x30
    u8 pad40[0x20];
    f32 distance;       // 0x60: the distance of the best target candidate
};


void ChooseBestTargetCandidate(Player* self, s32 n, BaseObject** items, TargetHit* out, f32* outf);
void ComputeTargetArc(Player* self, TargetArcSource* src, f32 dt, Vec02* vel, Vec02* pos, Vec02* acc);
void BuildAxisAngleMatrix(const Vec02* v, Mat02* out, f32 angle);
void SetPlayerState(Player* self, s32 a, s32 b);
void LaunchPlayerAtTarget(Player* self, TargetHit* s2, f32 f);

struct BufferedStream;
void ReadPropertyRecords(void* a, void* b);
void* AllocateFrontMemory(s32 size);
void* CreateTypedRecord(s32 index, void* a1, BaseObject* a2, s32 a3, s32 a4);


struct NextListed {
    static BaseObject* Of(ListFrame* it)
    {
        BaseObject* obj = *(BaseObject**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct BeginListWalk {
    static void Of(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = it;
    }
};

void AddTrackedNode(Rec36* self, BaseObject* n);


s32 IsObjectDescendantOf(BaseObject* node, BaseObject* target);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
s32 FindNodeForQuery(NodeQuery* q, s32 n, PlacedObject** list);

struct GathererQuery {
    ContactTracker* self;
    ObjectGatherer* obj;
    u8 pad[0x18];
    Vec02 q20;
    Vec02 q30;
};

struct AddGathererContact {
    static void Of(ContactTracker* self, ObjectGatherer* p, Vec02* a, Vec02* b)
    {
        s32 c = self->count;
        if ((u32)c < 10) {
            if (p->state != 3) {
                Slot36* s = &self->slots[c];
                self->count = c + 1;
                s->obj = (Collider*)p;
                s->point = *a;
                s->normal = *b;
            }
        }
    }
};



s32 GetEntryIdByKey(KeyedEntry* key);
void SetObjectSubGroupState(ObjectSubGroup* self, s32 state);
void BeginLevelExit(s32 flag, s32 n);
void TriggerScriptEvent(BaseObject* self, s32 idx, s32 flag, void* out);

void InitOscillator(Oscillator* self)
{
    InitObject(self);
    self->pendingId = -1;
    self->lastTime = -1.0f;
    self->currentEntry = -1;
}

void AttachNodeToOwner(NodeOwner* self, void* unused, NodeAttachment* ctx)
{
    OwnedNode* node = ctx->node54;
    node->next84 = self->head8E0;
    self->head8E0 = node;
    node->owner0C = self;
    for (s32 i = 0; i < ctx->count58; i++) {
        AttachmentElement* elem = ctx->elems5C + i;
        SlotPointers* sub = elem->sub20;
        for (s32 j = 0; j < self->count3C; j++) {
            if (sub->listA[j]) {
                *(void**)sub->listA[j] = &self->items6E0[j];
            }
            if (sub->listB[j]) {
                *(void**)sub->listB[j] = &self->items7E0[j];
            }
        }
    }
}

// A part an oscillator moves (the list at +0x8E0, AttachNodeToOwner): the object, its mesh, how
// the vertices' weights are taken (f20: -1 all 1, 0 to 3 the distance from the part's frame with
// an axis left out, 4 to 6 one axis), the distances between which the weight goes from f30 to f28
// (f2C and f24), and the frame (m40).
struct OscPart {
    PlacedObject* obj;      // 0x00
    struct OscMesh* mesh;   // 0x04
    u8 pad08[0x20 - 0x08];
    s32 mode;               // 0x20
    f32 endDistance;        // 0x24: the distance at which the vertex weight is endWeight
    f32 endWeight;          // 0x28: the weight at endDistance
    f32 startDistance;      // 0x2C: the distance at which the vertex weight is startWeight
    f32 startWeight;        // 0x30: the weight at startDistance
    u8 pad34[0x40 - 0x34];
    Vec02 m40[4];           // 0x40
    u8 pad80[0x84 - 0x80];
    OscPart* next;          // 0x84
};
// A block of a mesh's vertices: the range of the vertex data and its stride (u16s).
struct OscVertexRange { u16 start; u16 end; u8 pad04[0x10 - 0x04]; u16 stride; };
// The vertex data and, for each oscillator entry's output, a pointer to the four floats a vertex.
// A vertex's output: four floats, the entries' cosine and sine weights at their index.
struct OscOut { f32 f[4]; };
struct OscVertexData { Vec02* verts; u8 pad04[0x24 - 0x04]; OscOut* outs[1]; };
struct OscBlock { u8 pad00[0x1C]; OscVertexRange* range; OscVertexData* data; u8 pad24[0x50 - 0x24]; };
struct OscMesh { u8 pad00[0x58]; s32 blockCount; OscBlock* blocks; u8 pad60[0x68 - 0x60]; void* matrix; };
// An oscillator entry as func_001F2840 reads it (0xD0 bytes from +0x50).
struct OscEntry { s32 mode; s32 out; u8 pad08[0x10 - 0x08]; Vec02 axis; u8 pad20[0x60 - 0x20]; s32 index; f32 rate; u8 pad68[0xD0 - 0x68]; };
struct Mat4R { Vec02 r[4]; };

static inline f32 MinA(f32 a, f32 b) { return a <? b; }
static inline f32 MinB(f32 a, f32 b) { return b <? a; }
static inline f32 MaxA(f32 a, f32 b) { return a >? b; }
static inline f32 MaxB(f32 a, f32 b) { return b >? a; }
void InitIdentityMatrix(Mat4* self);
void* InvertMatrix4x4(void* a0, void* a1);
Mat4R MultiplyMatrices(const Mat4R& a, const Mat4R& b);
void BuildMatrixFromRotationAndTranslation(const Vec02* pos, const Mat02* rot, Mat4A* out);

void RefreshOscillatorFrames(Oscillator* self)
{
    for (OscPart* part = *(OscPart**)((u8*)self + 0x8E0); part != 0; part = part->next) {
        PlacedObject* obj = part->obj;
        OscMesh* mesh = part->mesh;
        Mat4R m;
        TimePolynomial poly;
        ValueRange range;
        u128 dir;
        if (part->mode == -1) {
            InitIdentityMatrix((Mat4*)&m);
            dir = Vu0::Q(D_00248D30);
        } else {
            m = *(Mat4R*)part->m40;
            range.lo = MinB(part->endWeight, part->startWeight);
            range.hi = MaxB(part->endWeight, part->startWeight);
            poly.y = (part->endWeight - part->startWeight) / (part->endDistance - part->startDistance);
            poly.x = part->endWeight - poly.y * part->endDistance;
            poly.z = 0.0f;
            switch (part->mode) {
            case 4:
                dir = Vu0::MulX(Vu0::Q(g_unitXVector), Vu0::Scalar((part->endDistance + part->startDistance) * 0.5f));
                break;
            case 5:
                dir = Vu0::MulX(Vu0::Q(g_unitYVector), Vu0::Scalar((part->endDistance + part->startDistance) * 0.5f));
                break;
            case 6:
                dir = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::Scalar((part->endDistance + part->startDistance) * 0.5f));
                break;
            default:
                dir = Vu0::Q(D_00248D30);
                break;
            }
            Mat4R inv;
            InvertMatrix4x4(&m, &inv);
            dir = Vu0::TransformRows(Vu0::Q(inv.r[0]), Vu0::Q(inv.r[1]), Vu0::Q(inv.r[2]), Vu0::Q(inv.r[3]), dir, 1.0f);
            if (mesh->matrix != 0) {
                m = MultiplyMatrices(*(Mat4R*)part->m40, *(Mat4R*)mesh->matrix);
            }
        }
        for (s32 i = 0; i < mesh->blockCount; i++) {
            OscBlock* block = &mesh->blocks[i];
            OscVertexData* data = block->data;
            OscVertexRange* r = block->range;
            Vec02 verts[0x100];
            f32 weights[0x100];
            s32 n = (r->end - r->start) / r->stride;
            Vec02* end = verts + n;
            CopyMemory(verts, data->verts, n * sizeof(Vec02));
            Vec02* v;
            f32* w = weights;
            for (v = verts; v < end; v++, w++) {
                Vec02 p;
                f32 weight;
                f32 d;
                Vu0::Q(p) = Vu0::Transform(m, Vu0::Q(*v), 1.0f);
                switch (part->mode) {
                case -1:
                default:
                    weight = 1.0f;
                    break;
                case 0:
                    d = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(p)));
                    goto curve;
                case 1:
                    p.z = 0.0f;
                    d = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(p)));
                    goto curve;
                case 2:
                    p.y = 0.0f;
                    d = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(p)));
                    goto curve;
                case 3:
                    p.x = 0.0f;
                    d = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(p)));
                    goto curve;
                case 4:
                    d = p.x;
                    goto curve;
                case 5:
                    d = p.y;
                    goto curve;
                case 6:
                    d = p.z;
                curve:
                    weight = range.Clamp(poly.Eval(d));
                    break;
                }
                *w = weight;
            }
            Mat4R mat;
            BuildMatrixFromRotationAndTranslation(&obj->v140, &obj->m110, (Mat4A*)&mat);
            if (mesh->matrix != 0) {
                mat = MultiplyMatrices(mat, *(Mat4R*)mesh->matrix);
            }
            u128 pivot = Vu0::Add(Vu0::Q(obj->v140), Vu0::RotateUntied(obj->m110, dir));
            for (s32 j = 0; j < self->entryCount; j++) {
                OscEntry* ent = &((OscEntry*)((u8*)self + 0x50))[j];
                OscOut* out = data->outs[ent->out];
                w = weights;
                for (v = verts; v < end; v++, out++, w++) {
                    u128 q = Vu0::TransformRows(Vu0::Q(mat.r[0]), Vu0::Q(mat.r[1]), Vu0::Q(mat.r[2]), Vu0::Q(mat.r[3]), Vu0::Q(*v), 1.0f);
                    u128 qc = Vu0::Copy(q);
                    switch (ent->mode) {
                    case 0: {
                        f32 sn, cs;
                        s32 k;
                        Vu0::Vec qv; qv.q = qc;
                        f32 a = Vu0::ToFloatMoved(Vu0::Dot(qv, Vu0::Vec::Of(ent->axis))) * (ent->rate * 6.2831855f);
                        k = ent->index;
                        ComputeSinCos(&sn, &cs, a);
                        out->f[k++] = cs * *w;
                        out->f[k] = sn * *w;
                        break;
                    }
                    case 1: {
                        Vec02 d;
                        Vu0::Vec qv, pv; qv.q = q; pv.q = pivot;
                        Vu0::Q(d) = Vu0::Sub(qv, pv).q;
                        out->f[0] = *w * d.x;
                        out->f[1] = *w * d.y;
                        out->f[2] = *w * d.z;
                        out->f[3] = 1.0f;
                        break;
                    }
                    }
                }
            }
        }
    }
    *(s32*)((u8*)self + 0x8E4) = 0;
}

struct OscillatorSweepEntry {
    s32 kind;               // 0x00: 0 for an axis entry
    u8 pad04[0x10 - 0x04];
    Vec02 v10;              // 0x10: the axis
    Vec02 v20;              // 0x20
    u8 pad30[0x40 - 0x30];
    Vec02 v40;              // 0x40
    u8 pad50[0x64 - 0x50];
    f32 scale;              // 0x64
    f32 frequency;          // 0x68: how fast the phase advances with the game clock
    f32 phaseOffset;        // 0x6C: the phase added to the clock term
    u8 pad70[0xD0 - 0x70];
};


// A weight already in a VU0 register, stored to a slot of its own as Scalar's is.
static inline Vu0::Vec WeightOf(u128 w)
{
    Vu0::Slot t;
    Vu0::Q(t) = w;
    Vu0::Vec r;
    r.q = Vu0::Q(t);
    return r;
}

void ComputeOscillatorDisplacement(Oscillator* self, f32 time, Vec02* in, Vec02* deltas, Vec02* outA, Vec02* outDeltas, Vec02* outB)
{
    Vu0::Vec pos = Vu0::Vec::Of(*in);
    Vu0::Vec other = Vu0::Vec::Of(D_00248D30);
    Vu0::Vec base = pos;
    for (s32 i = 0; i < self->entryCount; i++) {
        OscillatorSweepEntry* e = (OscillatorSweepEntry*)((u8*)self + 0x50) + i;
        if (e->kind != 0) {
            continue;
        }
        f32 period = e->scale == 0.0f ? 0.0f : 1.0f / e->scale;
        f32 scale = e->scale;
        if (period < time) {
            continue;
        }
        f32 phase = Vu0::ToFloatMoved(Vu0::Dot(base, Vu0::Vec::Of(e->v10))) * scale + g_gameClock.time * e->frequency + e->phaseOffset;
        f32 sn, cs;
        ComputeSinCos(&sn, &cs, phase * 6.2831855f);
        u128 c = Vu0::FromFloatAt(cs);
        pos = Vu0::MulAddX2(pos, Vu0::Vec::Of(e->v20), WeightOf(c), Vu0::Vec::Of(e->v40), Vu0::Vec::Scalar(sn));
        if (outB != 0) {
            other = Vu0::MulAddX2(other, Vu0::Vec::Of(e->v20), Vu0::Vec::FromFloat(-sn), Vu0::Vec::Of(e->v40), WeightOf(c));
        }
    }
    if (outA != 0) {
        Vu0::Q(*outA) = pos.q;
    }
    if (outB != 0) {
        Vu0::Q(*outB) = other.q;
    }
    if (deltas != 0 && outDeltas != 0) {
        for (s32 k = 0; k < 3; k++) {
            Vec02 t;
            Vu0::Set(t, Vu0::Add(Vu0::Q(*in), Vu0::Q(deltas[k])));
            ComputeOscillatorDisplacement(self, time, &t, 0, &t, 0, 0);
            Vu0::Q(outDeltas[k]) = Vu0::Sub(Vu0::Q(t), pos.q);
        }
    }
}

// The kind-0 (sine) entries' amplitudes, per axis: a noise blend (kind 1) adds no fixed bound.
void ComputeOscillatorMaxDisplacement(Oscillator* self, Vec02* out)
{
    Vec02 sum;
    Vec02 span;
    sum = D_00248D30;
    for (s32 i = 0; i < self->entryCount; i++) {
        OscillatorSweepEntry* e = (OscillatorSweepEntry*)((u8*)self + 0x50) + i;
        switch (e->kind) {
        case 0: {
            f32* d = &span.x;
            f32* a = &e->v20.x;
            f32* b = &e->v40.x;
            for (s32 k = 0; k < 3; k++) {
                d[k] = Fpu::Sqrt(a[k] * a[k] + b[k] * b[k]);
            }
            Vu0::Q(sum) = Vu0::Add(Vu0::Q(sum), Vu0::Q(span));
            break;
        }
        case 1:
            break;
        }
    }
    *out = sum;
}

f32 HashToUnitFloat(s32 a0)
{
    s32 n = a0;
    n ^= n << 13;
    n = n * (n * n * 0x3D73 + 0xC0AE5) + 0x5208DD0D & 0x7FFFFFFF;
    return (f32)n * 4.656612873077393e-10f;
}

f32 SampleSmoothNoise(f32 x, f32 y, f32 z)
{
    f32 t = (x + x) * g_gameTime + y;
    s32 i = (s32)t;
    f32 a = HashToUnitFloat(i);
    f32 b = HashToUnitFloat(i + 1);
    if (i & 1) {
        a = a * z;
        b = z * (b - 1.0f) + 1.0f;
    } else {
        b = b * z;
        a = z * (a - 1.0f) + 1.0f;
    }
    f32 u = t - (f32)i;
    u = (u * u) * (3.0f - (u + u));
    return a + u * (b - a);
}

f32 ApplyBiasCurve(f32 value, f32 denominator)
{
    return value / (1.0f + (1.0f / denominator - 2.0f) * (1.0f - value));
}

f32 EvaluateNoiseBlend(NoiseBlend* obj)
{
    f32 num = 0.0f;
    f32 den = 0.0f;
    for (s32 i = 0; i < obj->count; i++) {
        NoiseOctave* e = &obj->items[i];
        f32 r = SampleSmoothNoise(e->x, e->y, e->z);
        num += e->w * r;
        den += e->w;
    }
    f32 t = ApplyBiasCurve(num / den, obj->scale);
    return obj->lo + t * (obj->hi - obj->lo);
}

// An entry of the oscillator (0xD0 bytes at +0x50): a sine (kind 0) turns the frame rows it owns
// by the sine and cosine of the clock times f68 plus f6C; a noise blend (kind 1) sets its frame
// to an axis-angle matrix of two noise values, less the identity.
struct OscillatorEntry {
    s32 kind;               // 0x00: 0 a sine, 1 a noise blend
    s32 frame;              // 0x04: the frames it writes (Oscillator's framesA and framesB)
    u8 pad08[0x10 - 0x08];
    Vec02 v10;              // 0x10: kind 1: the axis turned by the first matrix
    Vec02 v20;              // 0x20: kind 1: the first matrix's axis
    Vec02 v30;              // 0x30: kind 1: a NoiseBlend (the second angle)
    Vec02 v40;              // 0x40
    Vec02 v50;              // 0x50
    s32 row;                // 0x60: kind 0: the first of the two rows it writes
    f32 scale;              // 0x64
    f32 frequency;          // 0x68: how fast the phase advances with the game clock
    f32 phaseOffset;        // 0x6C: the phase added to the clock term
    u8 pad70[0x80 - 0x70];
    u8 blend80[0xD0 - 0x80]; // 0x80: kind 1: a NoiseBlend (the first angle)
};

void RefreshOscillatorFrames(Oscillator* self);

void EvaluateOscillator(Oscillator* self)
{
    if (g_gameClock.time == self->lastTime) {
        return;
    }
    if (self->framesDirty != 0) {
        RefreshOscillatorFrames(self);
    }
    for (s32 i = 0; i < self->entryCount; i++) {
        OscillatorEntry* e = (OscillatorEntry*)((u8*)self + 0x50) + i;
        OscillatorFrame* fa = &self->framesA[e->frame];
        OscillatorFrame* fb = &self->framesB[e->frame];
        switch (e->kind) {
        case 0: {
            f32 phase = g_gameClock.time * e->frequency + e->phaseOffset;
            f32 sn, cs;
            ComputeSinCos(&sn, &cs, phase * 6.2831855f);
            u128 c = Vu0::FromFloatAt(cs);
            Vec02 a;
            Vec02 b;
            s32 row = e->row;
            Vu0::Set(a, Vu0::MulXSum(Vu0::Vec::Of(e->v20), WeightOf(c), Vu0::Vec::Of(e->v40), Vu0::Vec::Scalar(sn)).q);
            fa->r[row].x = a.x;
            fa->r[row].y = a.y;
            fa->r[row].z = a.z;
            Vu0::Set(a, Vu0::MulXSum(Vu0::Vec::Of(e->v20), Vu0::Vec::FromFloat(-sn), Vu0::Vec::Of(e->v40), WeightOf(c)).q);
            fa->r[row + 1].x = a.x;
            fa->r[row + 1].y = a.y;
            fa->r[row + 1].z = a.z;
            Vu0::Set(b, Vu0::MulXSum(Vu0::Vec::Of(e->v30), WeightOf(c), Vu0::Vec::Of(e->v50), Vu0::Vec::Scalar(sn)).q);
            fb->r[row].x = b.x;
            fb->r[row].y = b.y;
            Vu0::Vec p = Vu0::Vec::Of(e->v30);
            Vu0::Vec w = WeightOf(c);
            Vu0::Set(b, Vu0::MulXSum(p, Vu0::Vec::FromFloat(-sn), Vu0::Vec::Of(e->v50), w).q);
            fb->r[row + 1].x = b.x;
            fb->r[row + 1].y = b.y;
            break;
        }
        case 1: {
            f32 angle = EvaluateNoiseBlend((NoiseBlend*)&e->v30);
            Mat02 m;
            Mat02 turn;
            Vec02 axis;
            f32 tilt = EvaluateNoiseBlend((NoiseBlend*)e->blend80);
            BuildAxisAngleMatrix(&e->v20, &turn, tilt);
            Vu0::Set(axis, Vu0::Rotate(turn, Vu0::Vec::Of(e->v10)).q);
            BuildAxisAngleMatrix(&axis, &m, angle);
            fa->r[0].x = m.r[0].x - 1.0f;
            fa->r[0].y = m.r[0].y;
            fa->r[0].z = m.r[0].z;
            fa->r[1].x = m.r[1].x;
            fa->r[1].y = m.r[1].y - 1.0f;
            fa->r[1].z = m.r[1].z;
            fa->r[2].x = m.r[2].x;
            fa->r[2].y = m.r[2].y;
            fa->r[2].z = m.r[2].z - 1.0f;
            break;
        }
        }
    }
    self->lastTime = g_gameClock.time;
}

void AddOscillatorXEntry(Oscillator* o)
{
    s32 n = o->entryCount;
    s32 off;
    OscillatorAxisEntry* node;

    o->entryCount = n + 1;
    o->currentEntry = o->currentEntry + 1;
    off = n * 0xD0;
    off += 0x50;
    node = (OscillatorAxisEntry*)((u8*)o + off);
    node->kind = 0;
    node->q10 = *(Quad16*)&g_unitXVector;
    if (o->pendingId >= 0) {
        node->frame = o->pendingId;
        o->pendingId = -1;
        node->row = 2;
    } else {
        s32 v = o->nextId;
        node->frame = v;
        v++;
        o->nextId = v;
        o->pendingId = node->frame;
        node->row = 0;
    }
}

void AddOscillatorYZEntry(Oscillator* self)
{
    s32 n6 = self->currentEntry;
    s32 idx = self->entryCount;
    OscillatorPlaneEntry* e = (OscillatorPlaneEntry*)((u8*)self + 0x50 + 0xD0 * idx);
    n6 = n6 + 1;
    idx = idx + 1;
    self->entryCount = idx;
    self->currentEntry = n6;
    e->a = 1;
    e->q10 = *(Quad16*)&g_unitYVector;
    e->q20 = *(Quad16*)&g_unitZVector;
    e->secondBlendScale = 0.5f;
    e->firstBlendScale = 0.5f;
    self->nextId = self->nextId + 1;
}

void* GetOscillatorCurrentEntry(Oscillator* obj, s32 value, s32 flag)
{
    if (obj->entryCount == 0) {
        return 0;
    }
    if (value == 1) {
        obj->framesDirty = value;
    }
    return (u8*)obj + (obj->currentEntry * 0xD0 + 0x50);
}

void* GetOscillatorEntryForPeriod(Oscillator* self, s32 mode)
{
    return GetOscillatorCurrentEntry(self, mode, 0);
}

void* GetOscillatorEntryForVectors(void* self, s32 mode)
{
    return GetOscillatorCurrentEntry((Oscillator*)self, mode, 1);
}

void SetOscillatorEntryPeriod(void* self, f32 x)
{
    OscillatorEntryScale* s = (OscillatorEntryScale*)GetOscillatorEntryForPeriod((Oscillator*)self, 1);
    if (x == 0.0f) s->scale = 0.0f;
    else s->scale = 1.0f / x;
}

void GetOscillatorEntryPeriod(void* self, f32* out)
{
    OscillatorEntryScale* s = (OscillatorEntryScale*)GetOscillatorEntryForPeriod((Oscillator*)self, 1);
    f32 v = s->scale;
    if (v == 0.0f) *out = 0.0f;
    else *out = 1.0f / v;
}

void AppendVector4ToBuffer(VectorList4* buf, f32 x, f32 y, f32 z, f32 w)
{
    u32 n = buf->count;
    if (n < 4) {
        VectorListItem* e = &buf->items[n];
        buf->count = n + 1;
        e->a = x;
        e->b = y;
        e->c = z;
        e->d = w;
    }
}

void AddOscillatorEntryVectorA(void* self, f32 a, f32 b, f32 c, f32 d)
{
    u8* p = (u8*)GetOscillatorEntryForVectors(self, 1);
    AppendVector4ToBuffer((VectorList4*)(p + 0x30), a, b, c, d);
}

void AddOscillatorEntryVectorB(void* self, f32 a, f32 b, f32 c, f32 d)
{
    u8* p = (u8*)GetOscillatorEntryForVectors(self, 1);
    AppendVector4ToBuffer((VectorList4*)(p + 0x80), a, b, c, d);
}

void InitTransformObject(TransformObject* self)
{
    InitObject(self);
    Mat3_73* dst = &self->rot;
    *dst = *(Mat3_73*)&g_identityMatrix;
}

void ReadTransformObject(TransformObject* self, void* stream)
{
    ReadBufferedRotation3((BufferedStream*)stream, &self->rot);
    ReadBufferedVector3((BufferedStream*)stream, &self->pos);
    ReadPropertyRecords(self, stream);
}

void ReparentObjectKeepingTransform(TransformObject* self, BaseObject* other)
{
    TransformPointBetweenFrames((PlacedObject*)self->parent, (PlacedObject*)other, (Vec02*)&self->pos, (Vec02*)&self->pos);
    TransformRotationBetweenFrames((PlacedObject*)self->parent, (PlacedObject*)other, (Mat02*)&self->rot, (Mat02*)&self->rot);
    ReparentObject(self, other);
}

void TransformObjectIntoFrame(TransformObject* self, BaseObject* other)
{
    TransformPointBetweenFrames((PlacedObject*)other, 0, (Vec02*)&self->pos, (Vec02*)&self->pos);
    TransformRotationBetweenFrames((PlacedObject*)other, 0, (Mat02*)&self->rot, (Mat02*)&self->rot);
}

// The world point p in the object's own frame: into its parent's frame, less the position,
// through the transpose of the rotation.
void ConvertPointIntoObjectFrame(TransformObject* self, Vec02* p, Vec02* out)
{
    Vec02 t;
    TransformPointBetweenFrames(0, (PlacedObject*)self->parent, p, &t);
    Vu0::Q(t) = Vu0::Sub(Vu0::Q(t), Vu0::Q(self->pos));
    Vu0::Q(*out) = Vu0::RotateTransposed(self->rot, Vu0::Q(t));
}

void GetObjectWorldPosition(BaseObject* self, Vec02* out)
{
    TransformPointBetweenFrames((PlacedObject*)self->parent, 0, (Vec02*)((u8*)self + 0x40), out);
}

void GetObjectWorldRotation(BaseObject* self, Mat02* out)
{
    TransformRotationBetweenFrames((PlacedObject*)self->parent, 0, (Mat02*)((u8*)self + 0x50), out);
}

HoldingMember* FindArrivalPoint(s32 id, s32 parent)
{
    HoldingMember* found = 0;
    HoldingMember* buf[64];
    HoldingMember* other;
    HoldingMember* any;
    s32 n;
    s32 i;

    if (id != -1) {
        found = (HoldingMember*)FindFirstObjectById(g_currentWorld, 0x101, id, FindFirstObjectById(g_currentWorld, 0x101, parent, 0));
    }
    if (found == 0) {
        any = 0;
        other = 0;
        n = GatherObjectsById(g_currentWorld, 0x205, 0x74, 0, 0x100, buf);
        n = MinOf::Of(n, 0x40);
        for (i = 0; i < n; i++) {
            HoldingMember* e = buf[i];
            if (id != -1 && id == e->idB0) {
                found = e;
                break;
            }
            if (g_screenFade.mode != 0 && g_screenFade.style == 2 && e->id94 != 0) {
                other = e;
            }
            if (e->rec != 0) {
                any = e;
            }
        }
        if (found == 0) {
            found = other;
        }
        if (found == 0) {
            found = any;
        }
    }
    return found;
}

void LoadArrivalPoint(TransformSet* self, void* other)
{
    ReadBufferedRotation3((BufferedStream*)other, &self->rot);
    ReadBufferedVector3((BufferedStream*)other, &self->pos);
    ReadPropertyRecords(self, other);
    self->count = ReadBufferedS16((BufferedStream*)other);
    self->objects = (BaseObject**)AllocateFrontMemory(self->count << 2);
    for (s32 i = 0; i < self->count; i++) {
        s32 a = ReadBufferedS16((BufferedStream*)other);
        s32 b = ReadBufferedS16((BufferedStream*)other);
        s32 c = ReadBufferedS16((BufferedStream*)other);
        BaseObject* it = (BaseObject*)CreateTypedRecord(a, self->world, 0, b, c);
        self->objects[i] = it;
        it->desc->m0A(it, other);
    }
    SkipBufferedBlock((BufferedStream*)other);
    self->idCount = ReadBufferedS16((BufferedStream*)other);
    self->ids = (s32*)AllocateFrontMemory(self->idCount << 2);
    for (s32 i = 0; i < self->idCount; i++) {
        self->ids[i] = ReadBufferedS16((BufferedStream*)other);
    }
}

void CopyArrivalPoint(TransformSet* self, TransformSet* other)
{
    CopyObjectData(self, other);
    self->objects = (BaseObject**)AllocateFrontMemory(self->count << 2);
    for (s32 i = 0; i < self->count; i++) {
        self->objects[i] = CreateObjectCopy(other->objects[i], self->world, 0);
    }
}

void StartArrivalPoint(TransformSet* self)
{
    StartObject(self);
    for (s32 i = 0; i < self->count; i++) {
        BaseObject* item = self->objects[i];
        item->desc->m15(item, self->parent);
        ResolveAndStartObject(item);
    }
}

// The player-like object func_001F4008 hands the arrival point's pose to (class 0x16's slots 34
// to 37 take a direction, a velocity, a position and a spin).
struct ArrivingObject {
    struct Vt {
        u8 pad0[0x88];
        void (*getDir)(ArrivingObject* self, void* out);        // 0x88
        u8 pad8C[4];
        void (*setVel)(ArrivingObject* self, void* in);         // 0x90
        void (*setSpin)(ArrivingObject* self, void* in);        // 0x94
    };
    const Vt* vt;
    u8 pad04[0x538 - 4];
    u64 flags538;
};
struct ArrivalWatcher {
    struct Vt { u8 pad0[0x1C]; void (*start)(ArrivalWatcher* self); };
    const Vt* vt;
};

void SetObjectSubGroupState(ObjectSubGroup* self, s32 state);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

void PlaceAtArrivalPoint(TransformSet* self)
{
    Vec02 pos;
    Mat02 rot;
    Vec02 look;
    Vec02 k;
    ArrivalWatcher* found[0x40];
    f32 angle;
    ArrivingObject* who = (ArrivingObject*)GetCurrentSwitchedCollider();
    GetObjectWorldPosition(self, &pos);
    GetObjectWorldRotation(self, &rot);
    if (who == 0) {
        Vu0::Q(k) = Vu0::FromFloat(-300.0f);
        Vu0::Q(look) = Vu0::MulAddX(Vu0::Q(pos), Vu0::Q(rot.r[0]), Vu0::Q(k));
        PlaceCameraLookingAt(g_camera, &look, &pos);
        RequestCameraSnap(g_camera, 0);
        return;
    }
    who->vt->getDir(who, &rot);
    PlaceColliderClearOfContacts((Collider*)who, &pos, (Vec02*)&g_unitZVector);
    who->vt->setVel(who, (u8*)self + 0x80);
    who->vt->setSpin(who, (void*)&D_00248D30);
    ActivateSwitchedCollider(who);
    for (s32 i = 0; i < self->count; i++) {
        CreateAnimationPlayerWithoutPresetTargets((Animation*)self->objects[i], 0, 0, 0, 0.0f, 1.0f);
    }
    SetGatheredWalkerTargets(self->world, *(s32*)((u8*)self + 0xB4), (ZoneTargetEntry*)((u8*)self + 0xB8), self, 1);
    for (s32 i = 0; i < self->idCount; i++) {
        ArrivalWatcher* w = (ArrivalWatcher*)FindFirstObjectById(self->world, 0x104, self->ids[i], self);
        if (w != 0) {
            w->vt->start(w);
        }
    }
    s32 n = GatherObjectsById(self->world, 0x205, 0x7D, 0, 0x40, found);
    n = MinOf::Of(n, 0x40);
    for (n = n - 1; n >= 0; n--) {
        if (*(s32*)((u8*)found[n] + 0x2E4) != 2) {
            SetObjectSubGroupState((ObjectSubGroup*)found[n], 0);
        }
    }
    if (who->flags538 & (0x8000ULL << 30)) {
        if (*(s32*)((u8*)self + 0x98) != 0) {
            angle = WrapAngle(ArctangentOfRatio(rot.r[0].y, rot.r[0].x) + *(f32*)((u8*)self + 0x9C));
            RequestCameraSnap(g_camera, &angle);
        } else {
            RequestCameraSnap(g_camera, 0);
        }
    }
    TriggerScriptEvent(self, 2, 0, 0);
}

s32 SetTransformObjectKeyedValue(TransformObject* self, s32 flag, s32 k1, s32 k2, s32 val) { return UpsertKeyedEntry((ZoneTargetEntry*)((u8*)self + 0xB8), 4, (s32*)((u8*)self + 0xB4), flag, k1, k2, val); }

void StoreValueAndMarkSet(TimedValue* self, f32 value) { self->value = value; self->state = 1; }

void FindOrActivateSwitchedCollider(World* unused, s32 a, s32 b)
{
    void* r = FindArrivalPoint(a, b);
    if (r != 0) {
        PlaceAtArrivalPoint((TransformSet*)r);
    } else if (GetActiveSwitchedCollider() == 0) {
        r = GetCurrentSwitchedCollider();
        if (r != 0) {
            ActivateSwitchedCollider(r);
        }
    }
}

ObjectSubGroup* FindActiveObjectSubGroup(void)
{
    void* arr[64];
    ObjectSubGroup* found = 0;
    s32 n = GatherObjectsById(g_currentWorld, 0x205, 0x7D, 0, 0x100, arr);
    s32 cap = 0x40;
    s32 lim = 0x3F;
    n = (lim < n) ? cap : n;
    for (s32 i = 0; i < n; i++) {
        ObjectSubGroup* o = (ObjectSubGroup*)arr[i];
        if (o->selected != 0) {
            found = o;
            break;
        }
    }
    return found;
}

void BeginLevelExit(s32 flag, s32 n)
{
    GameProgress* ctx = g_saveData;
    LevelRecordWord78* o;
    ObjectSubGroup* v;
    LevelFadeEntry* k;
    FadeRequest args;
    if (ctx->levelIndex == 5) {
        goto lm1;
    }
    if (ctx->entryIndex != 0) {
        goto l4490;
    }
    o = (LevelRecordWord78*)g_currentLevelRecord;
    if ((o->flags & 1) != 0) {
        goto l4470;
    }
lm1:
    StartObjectFade((IdentityKey*)g_objectFadeIn, -1, n);
    return;
l4470:
    k = LookupEntryById((ctx->levelIndex << 8) | 1);
    StartObjectFade((IdentityKey*)k, 0x1BD, n);
    return;
l4490:
    v = (ObjectSubGroup*)FindActiveObjectSubGroup();
    if (v == 0) {
        goto larg;
    }
    if (flag != 0) {
        v->count = 0;
    }
    StartObjectSubGroupFinish(v);
    return;
larg:
    args.kind = 1;
    args.key = &D_00275B04;
    args.f08 = -1;
    args.f0C = -1;
    args.flags = 0;
    StartScreenFade(&g_screenFade, &args, n);
}

void LoadObjectSubGroup(ObjectSubGroup* self, void* s3)
{
    ReadOptionalBufferedBlock((BufferedStream*)s3, (u32*)((u8*)self + 0x2FC));
    ReadOptionalBufferedBlock((BufferedStream*)s3, (u32*)((u8*)self + 0x308));
    ReadBufferedRotation3((BufferedStream*)s3, &self->rot);
    ReadBufferedVector3((BufferedStream*)s3, &self->pos);
    void (*f)(BaseObject* self) = self->desc->m12;
    if (f != 0) {
        f(self);
    }
    self->state = 0;
    ReadMeshTables(s3, &self->f2EC, &self->f2F0, &self->f2F4, &self->faceTree);
    s32 i = 0;
    ReadPropertyRecords(self, s3);
    s32 n = ReadBufferedS16((BufferedStream*)s3);
    self->count = n;
    self->items = (BaseObject**)AllocateFrontMemory(n * 4);
    while (i < self->count) {
        s32 a = ReadBufferedS16((BufferedStream*)s3);
        s32 b = ReadBufferedS16((BufferedStream*)s3);
        s32 c = ReadBufferedS16((BufferedStream*)s3);
        BaseObject* o = (BaseObject*)CreateTypedRecord(a, self->world, self->parent, b, c);
        self->items[i++] = o;
        o->desc->m0A(o, s3);
        o->desc->m03(o);
    }
}

void StartObjectSubGroup(ObjectSubGroup* self)
{
    StartPlacedObject(self);
    for (s32 i = 0; i < self->count; i++) {
        BaseObject* e = self->items[i];
        const Desc01* vt = e->desc;
        if (vt->m0F != 0) {
            vt->m0F(e);
        }
        BaseObject* e2 = self->items[i];
        e2->desc->m10(e2);
    }
    if (self->f2D4 != 0) {
        s32* g = (s32*)(void*)g_currentEntry;
        if ((g[0] & 2) == 0) {
            BaseObject* a = self;
            while (a->parent != 0) {
                a = a->parent;
            }
            a->desc->m03(a);
        }
    }
}

void SetObjectSubGroupState(ObjectSubGroup* self, s32 state)
{
    if (state != self->state) {
        if (self->state == 4 && state != 5)
            g_copiedTextCaption.vt->m15(&g_copiedTextCaption);
        if (state == 5) {
            self->flags = (self->flags & ~0x30000000000ULL) | 0x10000000000ULL;
            AcquirePadSelectFlag(self->world);
            self->state = state;
        } else {
            self->state = state;
        }
        self->stateStartTime = g_gameTime;
    }
}

void StartObjectSubGroupFinish(ObjectSubGroup* self)
{
    BaseObject* key;
    s32 i;
    s32 found = 0;
    s32 next;
    Animation* it;

    key = (BaseObject*)GetActiveSwitchedCollider();
    if (g_timerCaption.state == 2
        && (self->f2E0 != 0 || self->f2D4 != 0
            || (g_saveData->entryIndex == 0 && (u8)GetEntryIdByKey(self->levelEntry) == 1))) {
        FinishBestTimeRun(&g_timerCaption);
        SetObjectSubGroupState(self, 2);
        goto tail;
    }
    if (g_timerCaption.state >= 2) {
        SetBestTimeState(&g_timerCaption, 4);
    }
    if (self->exitsLevel != 0) {
        BeginLevelExit(1, self->exitTarget);
        SetObjectSubGroupState(self, 0);
        return;
    }
    if (key == 0 || IsObjectOfKind(key, 0x16) == 0) {
        RemoveCameraControllers(g_camera, 2, 0, (CameraController*)((u8*)g_camera + 0x460), 0, 0);
    }
    SetObjectSubGroupState(self, 5);
    for (i = 0; i < self->count; i++) {
        it = (Animation*)self->items[i];
        CreateAnimationPlayerWithoutPresetTargets(it, 0, 0, 0, 0.0f, 1.0f);
        next = 0;
        if (found != 0 || HasAnimationEventKind19(it) != 0) {
            next = 1;
        }
        found = next;
    }
    if (found == 0) {
        if (self->fadeDelay > 0.0f) {
            self->fadeTime = ((f32*)&g_gameTime)[0] + self->fadeDelay;
        } else if (self->count > 0) {
            self->fadeTime = ((f32*)&g_gameTime)[0] + ((Animation*)self->items[0])->length;
        } else {
            self->fadeTime = ((f32*)&g_gameTime)[0];
        }
    }
tail:
    TriggerScriptEvent(self, 2, 0, 0);
}

void StartObjectSubGroupFade(ObjectSubGroup* self)
{
    FadeRequest m;
    s32 ok = 0;
    m.kind = 1;
    switch (self->f304) {
    case 0: ok = GetLevelEntryWord(GetEntryIdByKey(self->levelEntry)) >> 1; goto fin;
    case 1: ok = g_currentEntry->flags >> 1;
    fin: ok &= 1;
    }
    if (ok) {
        m.text = (u8*)self->f308;
        m.f08 = self->f30C;
    } else {
        m.text = (u8*)self->levelEntry;
        m.f08 = self->f300;
    }
    m.f0C = -1;
    m.flags = 0;
    StartScreenFade(&g_screenFade, &m, self->exitTarget);
}

extern s32 D_0026FA64;
extern s32 D_002701C4;
extern s32 D_0026F388;
extern T217D_3D0 g_copiedTextCaption;
extern T217D_440 g_typedTextCaptionBox;
s32 GetEntryIdByKey(KeyedEntry* key);
struct TreeNode03;
struct FacePoint;
s32 IsPointInsideFaceTree(TreeNode03* self, FacePoint* value);
void StartObjectSubGroupFinish(ObjectSubGroup* self);

void UpdateObjectSubGroup(ObjectSubGroup* self, f32 dt)
{
    Vec02 local;
    Vec02 radius;
    UpdatePlacedObject(self, dt);
    switch (self->state) {
    case 5: {
        f32 t = self->fadeTime;
        f32 zero = 0.0f;
        if (zero < t) {
            if (t < g_gameClock.time) {
                StartObjectSubGroupFade(self);
                self->fadeTime = zero;
            }
        }
        return;
    }
    case 4:
        if (D_0026FA64 == 0) {
            if (D_002701C4 != 0 || g_typedTextCaptionBox.state == 1 || g_typedTextCaptionBox.state == 2
                || (g_typedTextCaptionBox.state == 3 && g_typedTextCaptionBox.text[0] != 0)) {
                g_copiedTextCaption.vt->m15(&g_copiedTextCaption);
            } else {
                SetScreenElementHoldTime(&g_copiedTextCaption, 0.0f);
                SetElementTextFromPackedEntry(&g_copiedTextCaption, GetEntryIdByKey(self->levelEntry));
                g_copiedTextCaption.announce = 0;
                g_copiedTextCaption.vt->m14(&g_copiedTextCaption);
            }
        }
    case 0:
    case 1:
    case 3:
        break;
    default:
        return;
    }
    Collider* player = (Collider*)GetActiveSwitchedCollider();
    if (player == 0) {
        return;
    }
    TransformPointBetweenFrames(0, self, &player->v140, &local);
    s32 inside = IsPointInsideFaceTree((TreeNode03*)self->faceTree, (FacePoint*)&local);
    s32 near = 0;
    if (inside == 0 && self->nearCheck != 0 && __builtin_fabsf(local.z) < 300.0f) {
        if (Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(local), Vu0::Q(local)))) <= 1000.0f) {
            near = 1;
        }
    }
    switch (self->state) {
    case 3:
        if (inside != 0) {
            StartObjectSubGroupFinish(self);
        } else if (near != 0) {
            if (D_0026F388 == 0) {
                Camera* c = g_camera;
                u128 d = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(c->position));
                u128 ones = Vu0::Ones();
                Vu0::Q(radius) = Vu0::FromFloat(100.0f);
                if ((Vu0::PlaneSigns(Vu0::Q(c->planes[0]), Vu0::Q(c->planes[1]), Vu0::Q(c->planes[2]), d, ones, Vu0::Q(radius)) ^ 0xF0) == 0) {
                    SetObjectSubGroupState(self, 4);
                }
            }
        }
        break;
    case 4:
        if (inside != 0) {
            StartObjectSubGroupFinish(self);
        } else if (near == 0) {
            SetObjectSubGroupState(self, 3);
        }
        break;
    case 1:
        if (inside != 0) {
            SetObjectSubGroupState(self, 0);
        } else if (self->nearWaitTime < g_gameClock.time - self->stateStartTime) {
            SetObjectSubGroupState(self, 3);
        }
        break;
    case 0:
        if (inside == 0) {
            SetObjectSubGroupState(self, 1);
        }
        break;
    }
}

void InitLookupObject(LookupObject* self) { InitPlacedObject(self); self->id = -1; }

void StartLookupObject(LookupObject* self)
{
    StartPlacedObject(self);
    if (self->id != -1) {
        BaseObject* c = FindFirstObjectById(self->world, 0x104, self->id, self);
        if (c) {
            if (c->desc->flags & 1) {
                self->found2D8 = c;
            } else if (IsObjectOfKind(c, 0x7E)) {
                self->found2D4 = c;
            }
        }
    }
}

void PushObjectCameraController(void* self) { if (!*(s32*)((u8*)self + 0x310)) { PushCameraController(g_camera, 7, (CameraController*)((u8*)g_camera + 0x510), 0, self); *(s32*)((u8*)self + 0x310) = 1; } }

void RemoveObjectCameraController(void* self) { if (*(s32*)((u8*)self + 0x310)) { RemoveCameraControllers(g_camera, 0xB, 7, (CameraController*)((u8*)g_camera + 0x510), 0, self); *(s32*)((u8*)self + 0x310) = 0; } }

void InitTrackedNodes(Rec36* a, ContactTracker* b);

void InitContactTracker(ContactTracker* self)
{
    InitCollider(self);
    InitTrackedNodes(&self->rec, self);
    self->partMode = 1;
    self->flags538 = (self->flags538 & ~0xF000000000ULL) | 0x2000000000ULL;
}

void StartContactTracker(ContactTracker* self) { StartPlacedObject(self); FillTrackedNodes(&self->rec); }

void CollectTouchingObjects(ContactTracker* self, f32 dt) {
    GathererQuery tmp;
    ObjectGatherer* p;
    UpdateCollider(self, dt);
    self->count = 0;
    Collider* owner = self->root03();
    for (ContactRow03* g = owner->contacts->head; g; g = g->next) {
        for (Contact03* it = g->head; it; it = it->next) {
            s32 side = (owner != it->end[0].body);
            Collider* near = it->end[side].part;
            if (IsObjectDescendantOf(near, self)) {
                ContactEnd03* far = &it->end[1 - side];
                Collider* o = far->part;
                if (IsObjectOfKind(o, 0x41)) {
                    p = (ObjectGatherer*)o; AddGathererContact::Of(self, p, &far->point, &it->normal);
                }
            }
        }
    }
    FillMemory(&tmp, 0, 0x40);
    for (s32 i = 0; i < self->count; i++) {
        Slot36* s = &self->slots[i];
        p = (ObjectGatherer*)s->obj;
        tmp.self = self;
        tmp.obj = p;
        tmp.q20 = *(Vec02*)((u8*)p + 0x140);
        tmp.q30 = *(Vec02*)((u8*)p + 0x150);
        FindNodeForQuery((NodeQuery*)&tmp, 0, 0);
    }
}

void CopyContactTracker(ContactTracker* self, ContactTracker* src) { CopyCollider(self, src); self->rec.owner = self; }

void ApplyContactTrackerTransform(ContactTracker* self, Camera* cam, ScaledTransform* xf) { ApplyPlacedObjectTransform(self, cam, xf); }

int RequestContactTrackerLaunch(ContactTracker* self, void* source, TrackedNodeOffer* offer) { OfferTrackedNodeLaunch(&self->rec, source, offer); return 1; }

void* GetContactTrackerRecord(void* self) { return (u8*)self + 0x550; }

void ClearTrackedNodes(ContactTracker* self) { self->rec.found = 0; }

void InitC37(C37* o) {
    InitContactTracker(o);
    o->flags538 |= ((u64)0x8000 << 28);
    SetColliderAnchors(o, 3, 0, 3, 0);
}

struct TrackerHit {
    u8 pad00[0x30];
    u8 span[0x50];
    s32 f80;
    s32 f84;
    u8 pad88[0x18];
};

typedef s32 (*TargetHitFn)(Collider* self, s32 kind);
typedef void (*TargetNotifyFn)(Collider* self, TrackerHit* hit);
struct FaceRef;
struct Mesh03;
struct MeshHitEntry;
struct PooledContact;
struct OwnerMessage;
void OfferTrackedNodeLaunch(Rec36* self, void* a1, TrackedNodeOffer* out);
struct TreeNode03;
s32 FindPlaneTreeNodeForPoint(Vec02* pos, TreeNode03* nodes);

void UpdateC37(C37* self, f32 dt)
{
    TrackerHit hit;
    PooledContact* result;
    UpdateCollider(self, dt);
    Collider* target = (Collider*)GetActiveSwitchedCollider();
    if (target == 0) {
        return;
    }
    if (self->partMode != 1 && self->partMode != 4) {
        return;
    }
    if ((*(TargetHitFn*)((u8*)target->desc + 0x13C))(target, self->rec.f04) != 0) {
        return;
    }
    s32 far = 1;
    f32 r = self->radius3CC;
    f32 sum = r + target->radius3CC;
    Vec02* pos = &target->v140;
    u128 mine = Vu0::Q(self->v140);
    u128 gap = Vu0::Sub(mine, Vu0::Q(target->v140));
    if (!(sum * sum < Vu0::ToFloatMoved(Vu0::Dot(gap, gap)))) {
        far = 0;
    }
    if (far != 0) {
        return;
    }
    result = 0;
    if (self->rec.f04 == 5) {
        if (0.0f < ((f32*)target)[0x158 / 4]) {
            return;
        }
        if (FindPlaneTreeNodeForPoint((Vec02*)pos, self->tree.nodes) == 0) {
            return;
        }
        if ((target->flags538 & ((u64)0x8000 << 25)) != 0) {
            if (CollectMeshHits(pos, target->radius3CC, (s32)self->tree.count2, (FaceRef*)self->tree.nodes, 0, &self->meshCopy, 1, (MeshHitEntry*)&hit) > 0) {
                return;
            }
        } else {
            for (s32 i = 0; i < target->meshCopy.edgeCount; i++) {
                s16* edge = (s16*)((u8*)target->meshCopy.edges + i * 16);
                Quad16* verts = (Quad16*)target->meshCopy.verts;
                if (CollectTreeNodeSpans(self->tree.nodes, (Vec02*)&verts[edge[0]], (Vec02*)&verts[edge[1]], 0, 1, (ColliderSpan*)hit.span) == 0) {
                    return;
                }
                if (hit.f80 != 0) {
                    return;
                }
                if (hit.f84 != 0) {
                    return;
                }
            }
        }
    } else {
        s32 inside;
        if ((self->flags538 & ((u64)0x8000 << 25)) != 0) {
            u128 d = Vu0::Sub(Vu0::Q(target->v140), mine);
            inside = 1;
            if (!(Vu0::ToFloat(Vu0::Length(d)) < r)) {
                inside = 0;
            }
        } else {
            inside = FindPlaneTreeNodeForPoint((Vec02*)pos, self->tree.nodes);
        }
        if (inside == 0) {
            if ((target->flags538 & ((u64)0x8000 << 25)) != 0) {
                if ((self->flags538 & ((u64)0x8000 << 25)) != 0) {
                    AddSphereSphereContact(target, self, &result);
                } else {
                    AddMeshContacts(target, target->radius3CC, pos, self, self->tree.count2, (FaceRef*)self->tree.nodes, 0, &result);
                }
            } else if ((self->flags538 & ((u64)0x8000 << 25)) != 0) {
                AddMeshContacts(self, self->radius3CC, &self->v140, target, target->tree.count2, (FaceRef*)target->tree.nodes, 0, &result);
            } else {
                FaceRef* nodes = (FaceRef*)self->tree.nodes;
                if (nodes != 0) {
                    CreateMeshPairContacts(target, self, self->tree.count2, nodes, (u8*)nodes, &result);
                }
            }
            if (result == 0) {
                return;
            }
        }
    }
    InitOwnerMessage((OwnerMessage*)&hit, self->rec.f04, self);
    OfferTrackedNodeLaunch(&self->rec, (void*)result, (TrackedNodeOffer*)&hit);
    (*(TargetNotifyFn*)((u8*)target->desc + 0x140))(target, &hit);
    FreePooledContactChain((World*)self->world, (Contact03*)result);
}

void InitTrackedNodes(Rec36* a, ContactTracker* b) { a->owner = b; a->f04 = 0; a->f08 = 150.0f; }

void FillTrackedNodes(Rec36* self)
{
    ListFrame it;
    BaseObject* n;
    s32 i;

    BeginListWalk::Of(&it, &self->owner->children);
    while ((n = NextListed::Of(&it)) != 0) {
        s32 t = n->desc->id;
        if (t == 0x7E || t == 0x6E) {
            if (self->found < 0x20) {
                self->nodes[self->found++] = n;
            }
        }
    }
    for (i = 0; i < self->count; i++) {
        n = FindFirstObjectById(self->owner->world, 0x104, self->keys[i], self->owner);
        if (n != 0) {
            AddTrackedNode(self, n);
        }
    }
    g_activeListFrames = it.prev;
}

void LaunchPlayerAtTrackedNode(TrackedTargetChoice* ctx, Player* self)
{
    TargetLaunchFrame f;
    ChooseBestTargetCandidate(self, ctx->s94, (BaseObject**)((u8*)ctx + 0x98), (TargetHit*)f.a, &f.distance);
    if (ctx->cnt != 0) {
        ComputeTargetArc(self, (TargetArcSource*)f.a, 0.0f, 0, (Vec02*)f.b, 0);
        self->desc02()->m1D(self, (Vec02*)f.b);
        self->desc02()->m20(self, (Vec02*)&D_00248D30);
        self->desc02()->m21(self, (Vec02*)&D_00248D30);
        BuildAxisAngleMatrix((const Vec02*)&g_unitZVector, (Mat02*)f.c, self->heading);
        self->desc02()->m1E(self, (Mat02*)f.c);
        SetPlayerState(self, 2, 2);
    } else {
        LaunchPlayerAtTarget(self, (TargetHit*)f.a, f.distance);
    }
}

void OfferTrackedNodeLaunch(Rec36* self, void* a1, TrackedNodeOffer* out)
{
    GetActiveSwitchedCollider();
    s32 v = self->f04;
    out->tracker = self;
    out->f0 = v;
    out->launch = (void*)LaunchPlayerAtTrackedNode;
    TriggerScriptEvent(self->owner, 2, 0, 0);
}

void AddTrackedKey(Rec36* self, s32 entry) { u32 n = self->count; if (n < 32) { self->keys[n] = entry; self->count = n + 1; } }

void AddTrackedNode(Rec36* self, BaseObject* e) {
    if (self->found < 0x20) {
        if (IsObjectOfKind(e, 0x7E) || IsObjectOfKind(e, 0x6E) || IsObjectOfKind(e, 0x76) ||
            IsObjectOfKind(e, 0x70) || IsObjectOfKind(e, 0x71) || IsObjectOfKind(e, 0x81)) {
            self->nodes[self->found++] = e;
        }
    }
}

void RemoveTrackedNode(Rec36* self, s32 value)
{
    s32 i;
    for (i = 0; i < (s32)self->found; i++) {
        if ((s32)self->nodes[i] == value) {
            break;
        }
    }
    if (i < (s32)self->found) {
        s32* p = (s32*)&self->nodes[i];
        CopyMemory(p, p + 1, ((s32)self->found - i - 1) * 4);
        self->found = (s32)self->found - 1;
    }
}
