// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x1B7968 to 0x1BE1E8 (its .rodata from 0x24D280, its .data from 0x2746C0): the
// collider (class 0x03): its registration, bounds, motion, anchors, attachments, contacts and the
// solving of collider groups, then the heap sort of records (SwapSortRecords, HeapSortRecords)
// that other files call. It starts at an exact edge (state_walker.cpp's end). Its end is NOT
// proved by retail: the cut at 0x1BE1E8 follows the change of role only, from the collider to the
// sound system of sound_system.cpp. Retail's data allows it (this file's last .rodata, 0x24D2A0,
// is read by 0x1BB290 and its last .data, D_002746E0, by 0x1BB028; the next file's first,
// 0x24D2A8 and 0x274720, from 0x1BE1E8 on, with no gap of padding at either), so the cut could
// lie at any function start from 0x1BB378 to 0x1BE1E8 (0x1BE068 would give the sort to the next
// file), or the two could be one file. Its name is ours, after its class.
#include "common.h"
#include "sound_record.h"
#include "script_value.h"
#include "cursor_animator.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "collider.h"
#include "state_graph.h"
#include "camera_positioned_object.h"
#include "world.h"
#include "attachment.h"
#include "state_walker.h"
#include "globals.h"
#include "buffered_stream.h"
#include "object_event.h"
#include "key_record.h"
#include "key_id.h"
#include "base_object.h"
#include "fpu.h"
#include "asm_func.h"
#include "point_object.h"
#include "id_linked_object.h"
#include "game_progress.h"
#include "shapes.h"
#include "property_descriptor.h"
#include "vu0.h"
#include "mul_rotation.h"
#include "attached_set.h"
#include "active_set_solver.h"
#include "sound_level.h"
#include "functions/active_set_solver.h"
#include "functions/base_object.h"
#include "functions/camera.h"
#include "functions/collider.h"
#include "functions/collider_contact.h"
#include "functions/effect_spawner.h"
#include "functions/game_progress.h"
#include "functions/matrix.h"
#include "functions/object_properties.h"
#include "functions/oscillator.h"
#include "functions/placed_object.h"
#include "functions/pooled_object.h"
#include "functions/pose_source.h"
#include "functions/script_machine.h"
#include "functions/sound_system.h"
#include "functions/state_walker.h"
#include "functions/warp_menu.h"
#include "functions/world_contacts.h"
#include "functions/zone_collider.h"
struct TrackedNodeOffer;
struct Mat02;
struct Matrix3x4;

struct ScriptListBuilder;
struct ScriptValueFilter;

#define VA_ARG_WORD(ap, T) (*(T*)((ap += 8) - 8))

extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
extern f32 g_gameTime[];
u16 ReadBufferedU16(BufferedStream* self);
void* AllocateZeroedFrontMemory(s32 size);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
Contacts03* TakeContactTable(World* owner, Collider* self);
void ReleaseContactTable(World* owner, Contacts03* handle);
void FreeTouchNodes(World* owner, Touch03* node);
struct ClearedRecord;
struct ScriptScope;
void* AllocateFrontMemory(s32 size);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateBackMemory(u32 bytes);
void* AllocateBackMemory(s32 size);
s32 AppendPropertyToScriptList(ScriptListBuilder* self, void* value);
void AddColliderForce(void* a, void* b);
// What a vector is constrained by: an axis, and how (0 none, 1 the part along the axis removed,
// 2 only the part along it kept, 3 zero).
struct VectorConstraint {
    Vec02 axis;             // 0x00
    s32 kind;               // 0x10
};
// A quadword passed by value in one register (func_001B8820's position).
typedef u64 Qword128 __attribute__((mode(TI)));
void TransformMeshToWorld(Mesh03* a, Mesh03* b, Qword128 q, Mat02* c);
// An anchor preset (func_001BB028): a direction and a mode.
struct AnchorPreset { const Vec02* quad; s32 value; };
extern AnchorPreset g_anchorPresets[8];
void* AllocateBackMemory(s32 n);
// Matched by indexing the end as (u32)e + (i << 6).

void FreeTouchNodes(World* owner, Touch03* node);
Touch03* AllocateTouchNode(World* self);
// NEAR: 14 lines: retail preloads f400/f40C into s0 (lw s0 before loop and in the bnel delay slot), we load into v1; f408 loop test reload; last loop pointer s2 vs index


s32 ReadBufferedU8(BufferedStream* in);
void ReadMeshFromStream(BufferedStream* in, Mesh03* p);
void ReadFaceTree(BufferedStream* in, Mesh03* a, Tree03* out);
f32 ReadBufferedFloat(BufferedStream* in);
void ReadBufferedRotation3(BufferedStream* self, void* out);
void ReadBufferedVector3(BufferedStream* src, void* dst);
extern "C" void* CopyBytes(void* dst, void* src, s32 n);
u16 ReadBufferedU16(BufferedStream* self);
s32 ReadBufferedS16(BufferedStream* in);
s32 ReadBufferedU32(BufferedStream* in);
// What class 0x03's slot 69 (func_001B9F30) writes of a collider.
struct ColliderPose {
    s32 f00;                // 0x00: 0
    u8 pad04[0x0C];
    Vec02 position;         // 0x10: v140
    Vec02 v150;             // 0x20
    f32 heading;            // 0x30: from the first row of the matrix
    f32 f34;                // 0x34: 100.0
    f32 time;               // 0x38: g_gameTime
    s32 f3C;                // 0x3C: 0
};
extern "C" void SyncDataCache(s32 a);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
// A sound playing in the world: a 0x90-byte record of the pool at World 0x1BA0, kept on
// World::list1BAC. func_001BF6B8 takes one, func_001BF920 fills it, func_001BFAF8 starts its
// voice, func_001C0070 updates each one every frame and func_001BF728 gives it back.
struct PlayingSound {
    s32 entry;              // 0x00: its row of g_soundEntries, -2 for the stream voice
    s32 serial;             // 0x04: g_nextSoundRecordId when filled, checked by MarkSoundRecordIfIdMatches
    s32 bank;               // 0x08: the bank handle its voice starts from (StartSoundRecordVoice)
    PlayingSound** owner;   // 0x0C: the caller's pointer to it, cleared when it ends
    f32 startTime;          // 0x10: g_gameTime when its voice started
    f32 baseVolume;         // 0x14: the volume before distance; SetSoundRecordVolume rescales by it
    s32 voice;              // 0x18: the IOP voice handle, 0 while silent
    u8 pad1C[4];
    Quad16 position;        // 0x20: where it plays when it follows no object
    BaseObject* object;     // 0x30: the object it follows (its position at 0x140)
    f32 farRange;           // 0x34: beyond it the sound is silenced or ended (UpdateSoundEmitters)
    f32 nearRange;          // 0x38
    s32 keepWhenFar;        // 0x3C: silenced instead of ended out of range
    s32 silent;             // 0x40: no voice is playing
    s32 positional;         // 0x44: volume and pan follow the listener
    s32 finished;           // 0x48: its voice has ended (MarkSoundRecordIfIdMatches sets it)
    u8 pollTick;            // 0x4C: frames to the next end-of-voice query, modulo 4
    f32 volume;             // 0x50
    f32 pan;                // 0x54
    f32 pitch;              // 0x58: in octaves, 1524 units each (SetSoundRecordPitch)
    f32 dopplerScale;       // 0x5C
    s32 pitchOffset;        // 0x60: added to the pitch (SetSoundRecordPitch)
    U64P link;              // 0x64: kept when InitSoundRecord clears the record
    s32 pitchBaseValid;     // 0x6C
    s32 pitchBase;          // 0x70: the entry's pitch from GetSoundPitchBase, cached
    f32 nextTime;           // 0x74: when an ambient repeat plays next
    union { U64P bytes; f32 value; } interval;  // 0x78: the ambient repeat interval, < 0 for none
    union { U64P bytes; f32 value; } f80;       // 0x80
    u8 pad88[8];
    s32 Clamp(s32 v, s32 lo, s32 hi)
    {
        if (v < lo) {
            return lo;
        }
        if (hi < v) {
            return hi;
        }
        return v;
    }
};
extern "C" void* FillMemory(void* p, s32 value, s32 size);
void MovePlacedObject(Collider* self, f32 x, void* b);
typedef signed int s32;
typedef unsigned char u8;
void* AllocateZeroedFrontMemory(s32 bytes);
// The comparison func_001BE0A8's heap sort orders its records by.
typedef s32 (*SortCompareFn)(void* a, void* b);
void CopyMemory(void* dst, void* src, u32 size);
extern f32 g_gameClock[];
// The counts func_001BD678 fills for func_001BDD00 (its two lists of connected colliders).
struct ConnectedCounts { s32 pad; s32 n1; s32 n2; };
// What the update pass calls through slot 27 of a collider's class (func_001BDD00).
typedef void (*ColliderStepFn)(Collider* self, s32 a, f32 dt);
// The next object of World::list6C, at Collider::link414 read as one aligned word.
struct ListedCollider {
    u8 pad0[0x414];
    ListedCollider* next;
};
void PushBackMemoryMark();
void PopBackMemoryMark();
// The list walk of list_iter.h over a List01: push the frame, take each element, pop the frame.
struct ListWalk {
    static void Begin(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = it;
    }
    static u8* Next(ListFrame* it)
    {
        u8* obj = *(u8**)it->link;
        it->link = obj + it->offset;
        return obj;
    }
    static void End(ListFrame* it) { g_activeListFrames = it->prev; }
};
struct PooledContact;

extern "C" void* FillMemory(void* p, s32 value, s32 size);
// A script list being built (func_001C1530 hands one to a getter; func_001C1A28 appends a value
// of `type` to it).
struct ScriptListBuilder { s32 type; R11B008Node* head; R11B008Node* tail; };
extern "C" void* FillMemory(void* p, s32 value, s32 size);
s32 ReadBufferedU32(BufferedStream* self);
void* AllocateFrontMemory(u32 size);
// A type and a list of script values: func_001C1AD8 tells whether a value is among them.
struct ScriptValueFilter { u32 type; R11B008Node* list; };
s32 AppendPropertyToScriptList(ScriptListBuilder* self, void* value);


// The file's .data, in retail's order.
f32 g_colliderPositionGains[4] = { 0.0f, 3.0f, 0.0f, 0.0f };
f32 g_colliderRotationGains[4] = { 0.0f, 0.75f, 0.0f, 0.0f };
AnchorPreset g_anchorPresets[8] = {
    { &D_00248D30, 0 },
    { &D_00248D30, 3 },
    { &g_unitXVector, 2 },
    { &g_unitYVector, 2 },
    { &g_unitZVector, 2 },
    { &g_unitZVector, 1 },
    { &g_unitYVector, 1 },
    { &g_unitXVector, 1 },
};

void InitCollider(Collider* self)
{
    ScriptValue local;
    s32 s0;
    InitScriptValue(&local);
    SetListLinkOffset(&self->parts, 0x2E4);
    InitPlacedObject(self);
    ClearRecordBody((ClearedRecord*)&self->mesh);
    self->meshCopy = self->mesh;
    if (self->parent != 0) {
        SetColliderAnchors(self, 3, 0, 3, 0);
    }
    self->solverIndex = -1;
    self->index = -1;
    if (self->scriptScope != 0) {
        s0 = LookupScriptVariable((ScriptScope*)self->scriptScope, 6, 1, &local);
        s0 |= LookupScriptVariable((ScriptScope*)self->scriptScope, 7, 1, &local);
        if (s0 != 0) {
            self->flags538 |= (u64)0x8000 << 48;
        }
    }
    self->gravity = self->world->gravity;
    ResolveContactHandler(self);
    DestroyScriptValue(&local, 2);
}

void RegisterCollider(Collider* self)
{
    World* owner = self->world;
    owner->count34++;
    if (self->parent == 0) {
        AddColliderToSweepAxes(owner, self);
        self->contacts = TakeContactTable(owner, self);
        InitContactPairFlags(owner, self);
        owner->count38++;
        AppendToList(&owner->bodies, self);
    }
    RegisterPlacedObject(self);
    SetColliderPartListed(self, 1);
    self->desc03()->m44(self);
    if (!(self->flags538 & (1ULL << 54))) {
        UpdateAnchorModeFlags(self->root03());
    } else {
        UpdateAnchorModeFlags(self);
    }
    ResolveContactHandler(self);
}

void UnregisterCollider(Collider* self)
{
    Collider* old50 = self->root03();
    World* owner = self->world;
    SetColliderPartListed(self, 0);
    UnregisterPlacedObject(self);
    owner->count34--;
    if (self->parent == 0) {
        RemoveColliderFromSweepAxes(owner, self);
        ReleaseContactTable(owner, self->contacts);
        owner->count38--;
        RemoveFromList(&owner->bodies, self);
    }
    FreeTouchNodes(owner, self->touching);
    u64 flags = self->flags538;
    self->touching = 0;
    if (!(flags & (1ULL << 54)) && old50 != self) {
        UpdateAnchorModeFlags(old50);
    }
}

void SetColliderPartListed(Collider* self, s32 flag)
{
    if (flag == ((self->flags538 >> 50) & 1)) {
        return;
    }
    if (flag != 0) {
        AppendToList(&self->root03()->parts, self);
    } else {
        RemoveFromList(&self->root03()->parts, self);
    }
    self->flags538 = (self->flags538 & ~(1ULL << 50)) | ((u64)(flag & 1) << 50);
    ClearRootObjectStateBits(self->world, self, 7);
    Collider* sub = self->root03();
    sub->desc03()->m32(sub);
}


void ApplyColliderPendingMove(Collider* self, s32 quiet)
{
    Mat02 rot;
    Mat02 m;
    s32 moved = quiet;
    s32 still = 0;
    if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(self->v490))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(self->v490))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(self->v490))) < 0.0001f) {
        still = 1;
    }
    if (!still) {
        Vu0::Q(self->pos) = Vu0::Add(Vu0::Q(self->pos), Vu0::Q(self->v490));
        if (self->positionAttachment != 0) {
            SettlePoseSourceModes(self->positionAttachment);
        }
        Vu0::Q(self->v490) = Vu0::Zero();
        moved = 1;
    }
    still = 0;
    if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(self->spin4A0))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(self->spin4A0))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(self->spin4A0))) < 0.0001f) {
        still = 1;
    }
    if (!still) {
        BuildRotationFromVector(&self->spin4A0, &rot);
        MulRotationRowsIndexed(&m, rot, self->rot);
        self->rot = m;
        if (self->orientationAttachment != 0) {
            SettlePoseSourceModes(self->orientationAttachment);
        }
        Vu0::Q(self->spin4A0) = Vu0::Zero();
        moved = 1;
    }
    ListFrame it;
    ListWalk::Begin(&it, &self->children);
    for (PlacedObject* c = (PlacedObject*)ListWalk::Next(&it); c != 0; c = (PlacedObject*)ListWalk::Next(&it)) {
        if (c->desc->flags & 2) {
            c->desc02()->m2F(c, moved);
        }
    }
    if (moved && !quiet && self->desc->m12 != 0) {
        self->desc->m12(self);
    }
    ListWalk::End(&it);
}

void ApplyColliderPendingImpulse(Collider* self, s32 moved)
{
    s32 still = 0;
    if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(self->v490))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(self->v490))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(self->v490))) < 0.0001f) {
        still = 1;
    }
    if (!still) {
        Vu0::Q(self->v150) = Vu0::Add(Vu0::Q(self->v150), Vu0::Q(self->v490));
        if (self->positionAttachment != 0) {
            SettlePoseSourceModes(self->positionAttachment);
        }
        Vu0::Q(self->v490) = Vu0::Zero();
        moved = 1;
    }
    still = 0;
    if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(self->spin4A0))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(self->spin4A0))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(self->spin4A0))) < 0.0001f) {
        still = 1;
    }
    if (!still) {
        Vu0::Q(self->v160) = Vu0::Add(Vu0::Q(self->v160), Vu0::Q(self->spin4A0));
        if (self->orientationAttachment != 0) {
            SettlePoseSourceModes(self->orientationAttachment);
        }
        Vu0::Q(self->spin4A0) = Vu0::Zero();
        moved = 1;
    }
    ListFrame it;
    ListWalk::Begin(&it, &self->children);
    for (PlacedObject* c = (PlacedObject*)ListWalk::Next(&it); c != 0; c = (PlacedObject*)ListWalk::Next(&it)) {
        if (c->desc->flags & 2) {
            ((Collider*)c)->desc03()->m30((Collider*)c, moved);
        }
    }
    ListWalk::End(&it);
}

extern f32 g_frameDt[];

void ApplyColliderPendingImpulseHalfStep(Collider* self, s32 flag)
{
    s32 still = 0;
    s32 moved = flag;
    if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(self->v490))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(self->v490))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(self->v490))) < 0.0001f) {
        still = 1;
    }
    if (!still) {
        Vu0::Q(self->v150) = Vu0::Add(Vu0::Q(self->v150), Vu0::Q(self->v490));
        Vu0::Q(self->pos) = Vu0::MulAddX(Vu0::Q(self->pos), Vu0::Q(self->v490), Vu0::Scalar(g_frameDt[0] * 0.5f));
        if (self->positionAttachment != 0) {
            SettlePoseSourceModes(self->positionAttachment);
        }
        Vu0::Q(self->v490) = Vu0::Zero();
        moved = 1;
    }
    s32 spinStill = 0;
    if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(self->spin4A0))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(self->spin4A0))) < 0.0001f
        && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(self->spin4A0))) < 0.0001f) {
        spinStill = 1;
    }
    if (!spinStill) {
        Vec02 delta;
        Mat02 turn;
        *(Vu0::Vec*)&self->v160 = Vu0::Add(Vu0::Vec::Of(self->v160), Vu0::Vec::Of(self->spin4A0));
        Vu0::Q(delta) = Vu0::MulX(Vu0::Q(self->spin4A0), Vu0::Scalar(g_frameDt[0] * 0.5f));
        BuildRotationFromVector(&delta, &turn);
        MulRotationIntoRot(self, turn, self->rot);
        if (self->orientationAttachment != 0) {
            SettlePoseSourceModes(self->orientationAttachment);
        }
        Vu0::Q(self->spin4A0) = Vu0::Zero();
        moved = 1;
    }
    ListFrame it;
    ListWalk::Begin(&it, &self->children);
    PlacedObject* c;
    while ((c = (PlacedObject*)ListWalk::Next(&it)) != 0) {
        if (c->desc->flags & 2) {
            ((Collider*)c)->desc03()->m31((Collider*)c, moved);
        }
    }
    if (moved != 0) {
        if (flag == 0) {
            if (self->desc->m12 != 0) {
                self->desc->m12(self);
            }
        }
    }
    ListWalk::End(&it);
}

ASM_FUNC(func_001B8420);

ASM_FUNC(func_001B8540);

ASM_FUNC(func_001B8820);

void ComputeColliderWorldFrame(Collider* self)
{
    ComputePlacedObjectWorldFrame(self);
    TransformMeshToWorld(&self->mesh, &self->meshCopy, *(Qword128*)&self->v140, &self->m110);
    TransformMeshToWorld(&self->mesh2, &self->mesh2Copy, *(Qword128*)&self->v140, &self->m110);
}

void RecomputeColliderFrame(Collider* self)
{
    RecomputePlacedObjectFrame(self);
    self->root03()->desc03()->m32(self->root03());
    ClearRootObjectStateBits(self->world, self, 7);
    MarkSweepAxesUnsorted(self->world);
}

s32 TestCollidersMayContact(Collider* a, Collider* b)
{
    u64 m1 = 0x8080;
    s32 r = 0;
    m1 <<= 40;
    if ((a->flags538 & m1) != 0) {
        u64 bf = b->flags538;
        u64 m2 = 0x8000;
        m2 <<= 40;
        if ((bf & m2) != 0) {
            return 1;
        }
    }
    return r;
}

void NotifyContactHandlers(Collider* self)
{
    ContactRow03* node = self->contacts->head;
    while (node != 0) {
        Contact03* it = node->head;
        while (it != 0) {
            if (0.0001f < it->timer) {
                for (s32 i = 0; i < 2; i++) {
                    Collider* obj = FindHandlerForSlot(it->end[i].part, 0x114);
                    if (obj != 0) {
                        void (*fn)(Collider*, Contact03*, s32) = obj->desc03()->m41;
                        if (fn != 0) {
                            fn(obj, it, i);
                        }
                    }
                }
                *(s32*)&it->timer = 0;
            }
            if (node->head == 0) {
                break;
            }
            it = it->next;
        }
        node = node->next;
    }
}

f32 ComputeSegmentParameter(const Vec02* a, const Vec02* b, const Vec02* p)
{
    Vec02 ap;
    Vec02 ab;
    Vu0::Q(ap) = Vu0::Sub(Vu0::Q(*p), Vu0::Q(*a));
    Vu0::Q(ab) = Vu0::Sub(Vu0::Q(*b), Vu0::Q(*a));
    return Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(ap), Vu0::Q(ab))) / Vu0::ToFloat(Vu0::Dot(Vu0::Q(ab), Vu0::Q(ab)));
}

void CopyMemory(void* dst, void* src, u32 size);

// What Collider::hook points at for a mesh that blends per-vertex vectors (func_001B8B90): a
// vector for each vertex, and the three vertex indices of each face.
struct VertexBlend03 {
    Vec02* vectors;         // 0x00: one per vertex of the mesh copy, none to skip
    u8 pad04[0x08 - 0x04];
    s32 (*faceVerts)[3];    // 0x08: one triple per face
};

void AddContactVertexBlendVelocity(Collider* self, Contact03* c, s32 which)
{
    typedef Vu0::Vec Vec;
    if (self->hook == 0) {
        return;
    }
    s32 idx[3];
    f32 w[3];
    Vec02 sum;
    ContactEnd03* end = &c->end[which];
    s32 kind = 0;
    if (which == 0) {
        switch (c->kind) {
        case 1:
            kind = 1;
            idx[0] = (Vec02*)c->featureEnd0 - (Vec02*)self->meshCopy.verts;
            break;
        case 2:
        case 3:
            kind = 2;
            idx[0] = ((s16*)c->featureEnd0)[0];
            idx[1] = ((s16*)c->featureEnd0)[1];
            break;
        }
    } else {
        switch (c->kind) {
        case 4:
            kind = 1;
            idx[0] = (Vec02*)c->featureEnd1 - (Vec02*)self->meshCopy.verts;
            break;
        case 3:
        case 5:
            kind = 2;
            idx[0] = ((s16*)c->featureEnd1)[0];
            idx[1] = ((s16*)c->featureEnd1)[1];
            break;
        case 1:
        case 2:
        case 6:
        case 8:
            kind = 3;
            CopyMemory(idx, ((VertexBlend03*)self->hook)->faceVerts[(c->featureEnd1 - (s32)self->meshCopy.faces) >> 5], 12);
            break;
        }
    }
    switch (kind) {
    case 0:
        return;
    case 1:
        w[0] = 1.0f;
        break;
    case 2: {
        Vec02* verts = (Vec02*)self->meshCopy.verts;
        f32 t = ComputeSegmentParameter(&verts[idx[0]], &verts[idx[1]], &end->point);
        f32 lo = 0.0f;
        f32 hi = 1.0f;
        f32 r;
        if (t < lo) {
            r = lo;
        } else if (hi < t) {
            r = hi;
        } else {
            r = t;
        }
        w[1] = r;
        w[0] = 1.0f - r;
        break;
    }
    case 3: {
        Vec02* verts = (Vec02*)self->meshCopy.verts;
        for (s32 i = 0; i < 2; i++) {
            f32 t = ComputeSegmentParameter(&verts[idx[i]], &verts[idx[i + 1]], &verts[idx[(i + 2) % 3]]);
            Vec s = Vec::Scalar(t);
            Vec a = Vec::Of(verts[idx[i]]);
            Vec u = Vec::Scalar(-t);
            Vec b = Vec::Of(verts[idx[i + 1]]);
            Vec v = Vec::Scalar(1.0f);
            Vec c = Vec::Of(verts[idx[(i + 2) % 3]]);
            Vu0::Q(sum) = Vu0::MulXSum3(a, s, b, u, c, v).q;
            w[i] = ComputeSegmentParameter(&verts[idx[i]], &sum, &end->point);
        }
        f32 a = w[0];
        f32 lo = 0.0f;
        f32 hi = 1.0f;
        f32 r;
        if (a < lo) {
            r = lo;
        } else if (hi < a) {
            r = hi;
        } else {
            r = a;
        }
        w[0] = r;
        f32 b = w[1];
        f32 lo2 = 0.0f;
        f32 hi2 = 1.0f - r;
        f32 q;
        if (b < lo2) {
            q = lo2;
        } else if (hi2 < b) {
            q = hi2;
        } else {
            q = b;
        }
        w[1] = q;
        w[2] = 1.0f - w[0] - w[1];
        break;
    }
    }
    if (((VertexBlend03*)self->hook)->vectors == 0) {
        return;
    }
    Vu0::Q(sum) = Vec::Zero().q;
    for (s32 j = 0; j < kind; j++) {
        Vu0::Q(sum) = Vu0::MulAddX(Vu0::Q(sum), Vu0::Q(((VertexBlend03*)self->hook)->vectors[idx[j]]), Vu0::ScalarAt(w[j]));
    }
    TransformDirectionBetweenFrames(self, 0, &sum, &sum);
    Vu0::Q(end->v30) = Vu0::Add(Vec::Of(end->v30), Vec::Of(sum)).q;
}

LINKER_REMNANT(func_001B8FE0);

ASM_FUNC(func_001B8FE8);

void AddColliderForce(Collider* self, Vec02* force);

void SteerColliderTowardPosition(Collider* self, Vec02* target, f32* pull, Vec02* aim, f32* turn, f32 limit)
{
    Vec02 acc;
    Vec02 d;
    Vec02 k;
    Vu0::Q(acc) = Vu0::Zero();
    if (pull != 0) {
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(*target), Vu0::Q(self->pos));
        f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Q(d)));
        if (0.0001f < len) {
            Vu0::Q(k) = Vu0::FromFloat(pull[2] * len + pull[1] + pull[0] / len);
            Vu0::Q(acc) = Vu0::MulX(Vu0::Q(d), Vu0::Q(k));
        }
    }
    if (turn != 0) {
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(*aim), Vu0::Q(self->v150));
        f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Q(d)));
        if (0.0001f < len) {
            f32 amount = turn[2] * len + turn[1] + turn[0] / len;
            f32 cap = 1.0f / limit;
            if (cap < amount) {
                amount = cap;
            }
            Vu0::Q(k) = Vu0::FromFloat(amount);
            Vu0::Q(acc) = Vu0::MulAddX(Vu0::Q(acc), Vu0::Q(d), Vu0::Q(k));
        }
    }
    AddColliderForce(self, &acc);
}

void AddColliderTorque(Collider* self, Vec02* torque);

void SteerColliderTowardRotation(Collider* self, Mat02* target, f32* pull, Vec02* aim, f32* turn, f32 limit)
{
    Vec02 acc;
    Vu0::Q(acc) = Vu0::Zero();
    if (pull != 0) {
        Mat02 m;
        Vec02 axis;
        Vec02 k;
        f32 angle;
        MultiplyMatrices3x3(&self->rot, target, &m);
        MatrixToAxisAngle(&m, &angle, &axis);
        if (0.0001f < angle) {
            Vu0::Q(k) = Vu0::FromFloat(pull[2] * angle * angle + pull[1] * angle + pull[0]);
            Vu0::Q(acc) = Vu0::MulX(Vu0::Q(axis), Vu0::Q(k));
        }
    }
    if (turn != 0) {
        Vec02 d;
        Vec02 k;
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(*aim), Vu0::Q(self->v160));
        f32 len = Vu0::ToFloat(Vu0::Length(Vu0::Q(d)));
        if (0.0001f < len) {
            f32 amount = turn[2] * len + turn[1] + turn[0] / len;
            f32 cap = 1.0f / limit;
            if (cap < amount) {
                amount = cap;
            }
            Vu0::Q(k) = Vu0::FromFloat(amount);
            Vu0::Q(acc) = Vu0::MulAddX(Vu0::Q(acc), Vu0::Q(d), Vu0::Q(k));
        }
    }
    AddColliderTorque(self, &acc);
}

void StepCollider(Collider* self, f32 t)
{
    Vec4U local;
    Attach03* node;
    u64 m = 0x8000;
    m <<= 36;
    if (self->parent == 0) {
        if ((self->flags538 & m) == 0) {
            ConstrainColliderVector(self, &self->v440, &self->gravity, &local, 0);
            AddColliderForce(self, &local);
        }
    }
    node = self->attached;
    if (node != 0) {
        do {
            Collider* obj = node->owner;
            obj->desc03()->m33(obj, node, t);
            node = node->next;
        } while (node != 0);
    }
}

void DrawCollider(Collider* self, void* a, void* m)
{
    DrawPlacedObject(self, a, m);
}

void UpdateCollider(Collider* self, f32 dt)
{
    UpdatePlacedObject(self, dt);
}

void SetColliderMass(Collider* self, f32 v)
{
    f32 a = self->mass;
    f32 q = v / a;
    self->mass = a * q;
    ComputeColliderInverseInertia(self, q);
}

void ComputeColliderInverseInertia(Collider* self, f32 scale)
{
    Mat02 m;
    Vec02 k;
    Mat02 s;
    Vu0::Q(k) = Vu0::FromFloat(scale);
    Vu0::Q(s.r[0]) = Vu0::MulX(Vu0::Q(self->inertia.r[0]), Vu0::Q(k));
    Vu0::Q(s.r[1]) = Vu0::MulX(Vu0::Q(self->inertia.r[1]), Vu0::Q(k));
    Vu0::Q(s.r[2]) = Vu0::MulX(Vu0::Q(self->inertia.r[2]), Vu0::Q(k));
    CopyBytes(&m, &s, 0x30);
    self->inertia = m;
    if (!InvertMatrix3x3((Matrix3x4*)&self->inertia, (Matrix3x4*)&self->invInertia)) {
        FillMemory(&self->invInertia, 0, 0x30);
    }
}

void DropColliderContacts(Collider* self, s32 mode)
{
    Collider* ctx = self->root03();
    if (ctx == 0) {
        return;
    }
    if (mode != 0) {
        Contact03* freed = 0;
        for (ContactRow03* o = ctx->contacts->head; o != 0; o = o->next) {
            Contact03** pp = &o->head;
            Contact03* it;
            while ((it = *pp) != 0) {
                s32 other = it->end[0].body != ctx;
                ContactEnd03* p = &it->end[other];
                s32 hit;
                switch (mode) {
                case 1:
                    hit = IsObjectDescendantOf(p->part, self);
                    break;
                case 2:
                    hit = p->part == self;
                    break;
                case 3:
                    hit = 0;
                    if (p->part == self && other == 0) {
                        if (it->kind >= 8 && it->kind <= 9) {
                            hit = 1;
                        }
                    }
                    break;
                default:
                    hit = 0;
                    break;
                }
                if (hit != 0) {
                    *pp = it->next;
                    it->next = freed;
                    freed = it;
                } else {
                    pp = &it->next;
                }
            }
            *o->link = o->head;
        }
        FreePooledContactChain(self->world, freed);
    }
    ctx->f4B8 = 0;
}

void SaveColliderPreviousPosition(Collider* self)
{
    self->v370 = self->v140;
}

// What slot 13 of a moved collider is told (kind 3): the collider and where it was.
// The record a collider's position change hands to its event method (event 3). Its frame slot
// is 0x30 bytes where placed_object.cpp's MoveNotice, the same event's record there, is 0x20:
// SetColliderPosition writes only who and before, and leaves the third quadword as it is.
struct ColliderMoveNote {
    Collider* who;
    u8 pad04[0xC];
    Vec02 before;           // 0x10
    Vec02 q20;              // 0x20: not written by SetColliderPosition
};

void SetColliderPosition(Collider* self, Vec02* pos)
{
    ColliderMoveNote note;
    note.who = self;
    note.before = self->v140;
    if ((self->flags538 & ((u64)1 << 45)) != 0) {
        if (10.0f < Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(self->pos), Vu0::Q(*pos))))) {
            Camera* cam = g_camera;
            cam->currentTarget = 0;
            RequestCameraSnap(cam, 0);
        }
    }
    self->pos = *pos;
    if (self->root != 0) {
        if (self->desc->m12 != 0) {
            self->desc->m12(self);
        }
        DropColliderContacts(self, 1);
        Collider* root = (Collider*)self->root;
        Collider* part = (Collider*)root->parts.head;
        while (part != 0) {
            if (self == root || self == part || IsObjectDescendantOf(part, self) != 0) {
                ((Desc03*)part->desc)->m44(part);
            }
            part = (Collider*)part->link2E4.next;
        }
    }
    self->desc->m0E(self, 3, &note);
}

void SetColliderRotation(Collider* self, Mat02* src)
{
    self->rot.r[0] = src->r[0];
    self->rot.r[1] = src->r[1];
    self->rot.r[2] = src->r[2];
    if (self->root != 0) {
        if (self->desc->m12 != 0) {
            self->desc->m12(self);
        }
        DropColliderContacts(self, 1);
    }
    self->desc->m0E(self, 4, self);
}

void PlaceColliderClearOfContacts(Collider* self, Vec02* start, Vec02* step)
{
    Vec02 pos = *start;
    s32 i = 9;
    do {
        self->desc02()->m1D(self, &pos);
        UpdateWorldContacts(self->world, 0);
        for (ContactRow03* node = self->contacts->head; node != 0; node = node->next) {
            for (Contact03* c = node->head; c != 0; c = c->next) {
                if (c->depth < -2.0f) {
                    goto moved;
                }
            }
        }
        return;
    moved:
        Vu0::Q(pos) = Vu0::Add(Vu0::Q(pos), Vu0::Q(*step));
    } while (--i >= 0);
}

LINKER_REMNANT(func_001B9938);

void SetColliderVelocity(Collider* self, Vec02* v)
{
    SetPlacedObjectVelocity(self, v);
    Vec02 d;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(*v), Vu0::Q(self->v150));
    s32 small = 0;
    if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(d))) < 2.0f
        && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(d))) < 2.0f
        && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(d))) < 2.0f) {
        small = 1;
    }
    if (!small) {
        ClearRootObjectStateBits(self->world, self, 2);
    }
}

void SetColliderSpin(Collider* self, Vec02* v)
{
    SetPlacedObjectSpin(self, v);
    Vec02 d;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(*v), Vu0::Q(self->v160));
    s32 small = 0;
    if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(d))) < 0.02f
        && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(d))) < 0.02f
        && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(d))) < 0.02f) {
        small = 1;
    }
    if (!small) {
        ClearRootObjectStateBits(self->world, self, 2);
    }
}

LINKER_REMNANT(func_001B9AA8);

ASM_FUNC(func_001B9AB0);

ASM_FUNC(func_001B9AC8);

void SetColliderAnchors(Collider* self, s32 a1, Vec02* a2, s32 a3, Vec02* a4)
{
    self->mode450 = a1;
    u64 flag = (self->flags538 >> 54) & 1;
    if (a2 != 0) {
        self->v440 = *a2;
    }
    self->mode470 = a3;
    if (a4 != 0) {
        self->v460 = *a4;
    }
    Collider* sub = self->root03();
    if (sub != 0) {
        s32 f2 = 0;
        if (a1 == 3) {
            f2 = (a3 == 3);
        }
        if (flag != f2) {
            UpdateAnchorModeFlags(sub);
        }
    }
}

void ReparentCollider(Collider* self, BaseObject* p)
{
    Vec02 local0;
    Vec02 local1;
    if (self->parent == p) {
        return;
    }
    Collider* s5 = self->root03();
    TransformDirectionBetweenFrames((PlacedObject*)self->parent, 0, &self->v440, &local0);
    TransformDirectionBetweenFrames((PlacedObject*)self->parent, 0, &self->v460, &local1);
    ReparentPlacedObject(self, p);
    TransformDirectionBetweenFrames(0, (PlacedObject*)p, &local0, &self->v440);
    TransformDirectionBetweenFrames(0, (PlacedObject*)p, &local1, &self->v460);
    if (self->root != 0) {
        if ((self->flags538 & (1ULL << 54)) != 0 && s5 != 0) {
            UpdateAnchorModeFlags(s5);
        }
        Collider* f = self->root03();
        if ((f->flags538 & (1ULL << 55)) != 0) {
            UpdateAnchorModeFlags(f);
        } else {
            UpdateAnchorModeFlags(self);
        }
    }
    ResolveContactHandler(self);
}


void ReframeColliderAnchors(Collider* self, PlacedObject* frame)
{
    Vec02 a;
    Vec02 b;
    ReframePlacedObject(self, frame);
    Vu0::Q(a) = Vu0::Rotate(frame->rot, Vu0::Q(self->v440));
    Vu0::Q(b) = Vu0::Rotate(frame->rot, Vu0::Q(self->v460));
    SetColliderAnchors(self, self->mode450, &a, self->mode470, &b);
}

LINKER_REMNANT(func_001B9D08);


void TurnColliderTowardRotation(Collider* self, f32 dt, Mat02* target, f32* gain)
{
    Mat02 m;
    Vec02 axis;
    Vec02 want;
    Vec02 torque;
    Vec02 have;
    f32 angle;
    f32 limit = gain[0];
    f32 rate = (limit - gain[1]) / gain[2];
    f32 zone = limit * limit / (rate + rate);
    f32 speed = Vu0::ToFloat(Vu0::Length(Vu0::Q(self->v160)));
    if (limit < speed) {
        Vu0::Q(torque) = Vu0::MulX(Vu0::Q(self->v160), Vu0::Scalar((limit - speed) * 2.5f / speed));
        AddColliderTorque(self, &torque);
    }
    MultiplyMatrices3x3(&self->rot, target, &m);
    MatrixToAxisAngle(&m, &angle, &axis);
    f32 step = ClampToMagnitude(angle / zone * limit, limit);
    speed = Vu0::ToFloat(Vu0::Dot(Vu0::Q(self->v160), Vu0::Q(axis)));
    f32 rest = angle - (speed + step) * (dt * 0.5f);
    if (rest < zone) {
        step = ClampToMagnitude(rest / zone * limit, limit);
    }
    Vu0::Q(want) = Vu0::MulX(Vu0::Q(axis), Vu0::Scalar(step));
    Vu0::Q(have) = Vu0::MulAddX(Vu0::Q(self->v160), Vu0::Q(self->v180), Vu0::Scalar(dt));
    u128 diff = Vu0::Sub(Vu0::Q(want), Vu0::Q(have));
    Vu0::Q(torque) = diff;
    f32 error = Vu0::ToFloatMoved(Vu0::Length(diff));
    if (error < rate * dt) {
        Vu0::Q(torque) = Vu0::MulX(diff, Vu0::Scalar(1.0f / dt));
    } else {
        Vu0::Q(torque) = Vu0::MulX(diff, Vu0::Scalar(rate / error));
    }
    AddColliderTorque(self, &torque);
}

LINKER_REMNANT(func_001B9F28);

void CaptureColliderPose(Collider* self, ColliderPose* out)
{
    Vec02 tmp[3];
    out->position = self->v140;
    out->v150 = self->v150;
    RotateMatrixUpright(&self->m110, 0, (Mat02*)&tmp[0]);
    out->heading = ArctangentOfRatio(-tmp[0].y, -tmp[0].x);
    out->f34 = 100.0f;
    out->f00 = 0;
    out->time = g_gameTime[0];
    out->f3C = 0;
}

s32 IsContactBetweenParts(Collider* self, void* other)
{
    PlacedObject* key;
    Contact03* n;
    for (n = (Contact03*)GetContactRowHead(self, (Collider*)other), key = self->root; n != 0; n = n->next) {
        s32 s1 = key != n->end[0].body;
        s32 o0 = s1 * 64;
        if (IsObjectDescendantOf((BaseObject*)(*(void**)((u8*)n + o0 + 4)), self) != 0) {
            s32 o1 = (1 - s1) * 64;
            if (IsObjectDescendantOf((BaseObject*)(*(void**)((u8*)n + o1 + 4)), (BaseObject*)other) != 0) {
                return 1;
            }
        }
    }
    return 0;
}

void* FindContactingPart(Collider* self)
{
    Collider* s3 = self->root03();
    ContactRow03* s2 = s3->contacts->head;
    for (; s2 != 0; s2 = s2->next) {
        Contact03* s0 = s2->head;
        while (s0 != 0) {
            s32 s1 = ((u32)s3 ^ (u32)s0->end[0].body) != 0;
            if (IsObjectDescendantOf((BaseObject*)(*(void**)((u8*)(s0) + (s1 << 6) + 4)), self) != 0) {
                return *(void**)((u8*)(s0) + ((1 - s1) << 6) + 4);
            }
            s0 = s0->next;
        }
    }
    return 0;
}

void CopyCollider(Collider* self, Collider* other)
{
    u64 bit = (self->flags538 >> 50) & 1;
    Link02 a, c, d;
    List01 b;
    a = self->link2D0;
    b = self->parts;
    c = self->link2E4;
    Contacts03* s480 = self->contacts;
    Collider* s4E4 = self->handler;
    d = self->link414;
    CopyPlacedObject(self, other);
    self->contacts = s480;
    self->link2D0 = a;
    self->parts = b;
    self->link2E4 = c;
    self->link414 = d;
    self->handler = s4E4;
    self->attached = 0;
    self->f4B8 = 0;
    self->flags538 = (self->flags538 & 0xFFFBFFFFFFFFFFFFULL) | (bit << 50);
    SetColliderPartListed(self, 1);
    if (self->meshCopy.vertCount) CopyMeshTransformed(&other->meshCopy, 0, &self->meshCopy);
    if (self->tree.nodes) CloneTreeNodes(&other->meshCopy, &other->tree, &self->meshCopy, &self->tree);
    if (self->mesh2Copy.vertCount) CopyMeshTransformed(&other->mesh2Copy, 0, &self->mesh2Copy);
    if ((s32)self->flags538) CloneTreeNodes(&other->mesh2Copy, &other->tree2, &self->mesh2Copy, &self->tree2);
    self->touching = 0;
    self->flags538 |= 0x20000000000ULL;
}

void ConstrainVectorByParentAnchor(Collider* self, VectorConstraint* c, Vec02* in, Vec02* out, Vec02* rem)
{
    Vec02 axis;
    Vec02 tmp;
    if (out == 0) {
        out = &tmp;
    }
    switch (c->kind) {
    case 0:
        if (out != in) {
            *out = *in;
        }
        break;
    case 2: {
        Vec02* a;
        PlacedObject* parent = (PlacedObject*)self->parent;
        if (parent != 0) {
            Vu0::Q(axis) = Vu0::Rotate(parent->m110, Vu0::Q(c->axis));
            a = &axis;
        } else {
            a = &c->axis;
        }
        Vu0::Q(*out) = Vu0::MulX(Vu0::Q(*a), Vu0::Dot(Vu0::Q(*in), Vu0::Q(*a)));
        break;
    }
    case 1: {
        Vec02* a;
        PlacedObject* parent = (PlacedObject*)self->parent;
        if (parent != 0) {
            Vu0::Q(axis) = Vu0::Rotate(parent->m110, Vu0::Q(c->axis));
            a = &axis;
        } else {
            a = &c->axis;
        }
        Vu0::Q(*out) = Vu0::Sub(Vu0::Q(*in), Vu0::MulX(Vu0::Q(*a), Vu0::Dot(Vu0::Q(*in), Vu0::Q(*a))));
        break;
    }
    case 3:
        Vu0::Q(*out) = Vu0::Zero();
        break;
    }
    if (rem != 0) {
        Vu0::Q(*rem) = Vu0::Sub(Vu0::Q(*in), Vu0::Q(*out));
    }
}

void ConstrainVectorByAnchor(VectorConstraint* c, Vec02* in, Vec02* out, Vec02* rem)
{
    Vec02 tmp;
    if (out == 0) {
        out = &tmp;
    }
    switch (c->kind) {
    case 0:
        if (out != in) {
            *out = *in;
        }
        break;
    case 2:
        Vu0::Q(*out) = Vu0::MulX(Vu0::Q(c->axis), Vu0::Dot(Vu0::Q(*in), Vu0::Q(c->axis)));
        break;
    case 1:
        Vu0::Q(*out) = Vu0::Sub(Vu0::Q(*in), Vu0::MulX(Vu0::Q(c->axis), Vu0::Dot(Vu0::Q(*in), Vu0::Q(c->axis))));
        break;
    case 3:
        Vu0::Q(*out) = Vu0::Zero();
        break;
    }
    if (rem != 0) {
        Vu0::Q(*rem) = Vu0::Sub(Vu0::Q(*in), Vu0::Q(*out));
    }
}

void ConstrainColliderVector(void* self, void* a, void* b, void* c, s32 d)
{
    ConstrainVectorByAnchor((VectorConstraint*)a, (Vec02*)b, (Vec02*)c, (Vec02*)(s32)d);
}

void AddColliderAttachment(Collider* self, Attach03* node)
{
    node->next = self->attached;
    self->attached = node;
    ClearRootTries(self);
}

void RemoveColliderAttachment(Collider* o, Attach03* node)
{
    Attach03** link = &o->attached;
    if (*link == 0) {
        goto tail;
    }
    if (o->attached == node) {
        o->attached = node->next;
    } else {
        Attach03* prev;
        for (;;) {
            prev = *link;
            Attach03* nx = prev->next;
            link = &prev->next;
            if (nx == 0) {
                goto tail;
            }
            if (nx == node) {
                break;
            }
        }
        prev->next = node->next;
    }
    node->next = 0;
tail:
    ClearRootTries(o);
}

void BuildPerpendicularPair(Vec02* in, Vec02* out, const Vec02* a, const Vec02* b);
struct Oscillator;
f32 SplitVectorAlongAxis(Vec02* v, Vec02* axis, Vec02* along, Vec02* rest);
extern "C" f32 Arccosine(f32 x);

struct Oscillated_1BA5B0 { u8 pad00[0xC]; void* oscillator; };
struct SoundOwner_1BA5B0 { u8 pad00[0x574]; PlayingSound* sound; };

// The rows of m, each turned by r, returned by value (g++'s named return value): each row goes
// to the result as soon as it is made.
static inline Mat02 RotateRowsBy(const Mat02& r, const Mat02& m) return out
{
    Mat02 t;
    Vu0::Q(t.r[0]) = Vu0::RotateUntied(r, Vu0::Vec::Of(m.r[0])).q;
    out.r[0] = t.r[0];
    Vu0::Q(t.r[1]) = Vu0::RotateUntied(r, Vu0::Vec::Of(m.r[1])).q;
    out.r[1] = t.r[1];
    Vu0::Q(t.r[2]) = Vu0::RotateUntied(r, Vu0::Vec::Of(m.r[2])).q;
    out.r[2] = t.r[2];
}

void ApplyColliderAttachedSetContact(Collider* self, AttachedSet* other, f32 dt)
{
    Vec02 hit;
    Vec02 hitVel;
    Vec02 force;
    Vec02 spin;
    Vec02 point;
    Vec02 normal;
    f32 gains[3];
    f32 depth = MeasureAttachedSetContactDepth(other, (TurningCollider*)self, &point, &normal);
    if (depth < 0.0001f) {
        return;
    }
    if (other->f278 != 0) {
        Vec02 axes[2];
        Vec02 dir = normal;
        BuildPerpendicularPair(&dir, &axes[0], &g_unitXVector, &g_unitZVector);
        ComputeOscillatorDisplacement((Oscillator*)(((Oscillated_1BA5B0*)other->f278)->oscillator), 50.0f, &point, &axes[0], 0, &axes[0], 0);
        Vu0::Set(normal, Vu0::NormalizeOr(Vu0::Cross(Vu0::Q(axes[0]), Vu0::Q(axes[1])), Vu0::Q(g_unitZVector)));
    }
    f32 push;
    if ((self->flags538 & (0x8000ULL << 36)) == 0) {
        push = self->pushFactor * other->pushFactor;
    } else {
        push = 0.0f;
    }
    f32 drag = self->dragFactor * other->dragFactor;
    if (push != 0.0f) {
        Vu0::Q(force) = Vu0::MulX(Vu0::Q(self->gravity), Vu0::Scalar(-push * depth));
        ConstrainColliderVector(self, &self->v440, &force, &force, 0);
        AddColliderForce(self, &force);
    }
    if (drag != 0.0f) {
        Vec02 along;
        Vec02 rest;
        Vec02 target;
        Vec02 target2;
        Vec02 spinAlong;
        Vec02 spinRest;
        Vec02 target3;
        Vec02 target4;
        GetAttachedSetPointMotion(other, &self->v140, (Quad16*)&hit, (Quad16*)&hitVel);
        Vu0::Q(force) = Vu0::Sub(Vu0::Q(hit), Vu0::Q(self->v150));
        f32 dot = SplitVectorAlongAxis(&force, &normal, &along, &rest);
        f32 scale = 1.0f;
        if (depth != 1.0f && !(0.0f < dot)) {
            scale = depth * 0.5f + 0.5f;
        }
        for (s32 i = 0; i < 3; i++) {
            gains[i] = g_colliderPositionGains[i] * scale * drag;
        }
        Vu0::Q(target) = Vu0::Add(Vu0::Q(self->v150), Vu0::Q(along));
        SteerColliderTowardPosition(self, 0, 0, &target, gains, dt);
        for (s32 i = 0; i < 3; i++) {
            gains[i] = g_colliderPositionGains[i] * depth * drag;
        }
        Vu0::Q(target2) = Vu0::Add(Vu0::Q(self->v150), Vu0::Q(rest));
        SteerColliderTowardPosition(self, 0, 0, &target2, gains, dt);
        Vu0::Q(spin) = Vu0::Sub(Vu0::Q(D_00248D30), Vu0::Q(self->v160));
        SplitVectorAlongAxis(&spin, &normal, &spinAlong, &spinRest);
        for (s32 i = 0; i < 3; i++) {
            gains[i] = g_colliderRotationGains[i] * depth * drag;
        }
        Vu0::Q(target3) = Vu0::Add(Vu0::Q(self->v160), Vu0::Q(spinAlong));
        SteerColliderTowardRotation(self, 0, 0, &target3, gains, dt);
        for (s32 i = 0; i < 3; i++) {
            gains[i] = g_colliderRotationGains[i] * drag;
        }
        Vu0::Q(target4) = Vu0::Add(Vu0::Q(self->v160), Vu0::Q(spinRest));
        SteerColliderTowardRotation(self, 0, 0, &target4, gains, dt);
    }
    if (push != 0.0f) {
        Mat02 m = self->m1A0;
        Mat02 r;
        Vec02 axis;
        Vec02 torque;
        self->desc03()->m29(self, &m, 0);
        BuildShortestArcRotation(&g_unitZVector, &normal, &r);
        m = RotateRowsBy(r, m);
        f32 angle = Arccosine(Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(self->m110.r[2]), Vu0::Vec::Of(m.r[2]))));
        Vu0::Set(axis, Vu0::NormalizeOr(Vu0::Cross(Vu0::Q(self->m110.r[2]), Vu0::Q(m.r[2])), Vu0::Q(g_unitXVector)));
        Vu0::Q(torque) = Vu0::MulX(Vu0::Q(axis), Vu0::Scalar(angle * (push * 3.0f) * depth));
        AddColliderTorque(self, &torque);
    }
    if (0.0f < depth && depth < 1.0f && 0.9f < normal.z) {
        SpawnSurfaceContactEffects((BaseObject*)self, (u8*)other, (Quad16*)&hit, dt, (Quad16*)&point, 0.1f, ((self->boundsMax.x - self->boundsMin.x) + (self->boundsMax.y - self->boundsMin.y)) * 0.25f);
    } else if (self->desc->flags & 8) {
        StopSoundRecord(((SoundOwner_1BA5B0*)self)->sound, 0);
    }
}

void IgnoreColliderAttachmentStep(Collider* self, Attach03* node, f32 dt)
{
}

void LoadCollider(Collider* self, BufferedStream* in)
{
    s32 i;
    s32 j;
    s32 n;
    Pair03* e;
    u8 flag = ReadBufferedU8(in) & 1;
    self->flags = (self->flags & ~(1ULL << 33)) | ((u64)flag << 33);
    ReadMeshFromStream(in, &self->mesh);
    self->radius3D0 = self->mesh.radius;
    self->radius3CC = self->mesh.radius;
    if (self->flags & (1ULL << 33)) {
        self->meshCopy = self->mesh;
    } else {
        CopyMeshTransformed(&self->mesh, 0, &self->meshCopy);
    }
    ReadFaceTree(in, &self->meshCopy, &self->tree);
    i = 0;
    self->mass = ReadBufferedFloat(in);
    ReadBufferedRotation3(in, &self->inertia);
    ReadBufferedVector3(in, &self->offset);
    ComputeColliderInverseInertia(self, 1.0f);
    self->groupCount = ReadBufferedU16(in);
    self->groups = (Pair03*)AllocateFrontMemory(self->groupCount << 3);
    if (self->groupCount > 0) {
        do {
            e = self->groups;
            e += i++;
            e->a = ReadBufferedS16(in);
            e->b = ReadBufferedU16(in);
        } while (i < self->groupCount);
    }
    n = ReadBufferedU32(in);
    j = 0;
    self->nodeGroups = (s32*)AllocateFrontMemory(n << 2);
    if (n > 0) {
        do {
            s32 v = ReadBufferedS16(in);
            self->nodeGroups[j] = v;
            j++;
        } while (j < n);
    }
    self->refCount = ReadBufferedU32(in);
    i = 0;
    self->refs = (Pair03*)AllocateFrontMemory(self->refCount << 3);
    while (i < self->refCount) {
        e = self->refs;
        e += i++;
        e->a = ReadBufferedS16(in);
        e->b = ReadBufferedS16(in);
    }
    if (self->refCount > 0) {
        j = 0;
        self->faceStarts = (s32*)AllocateFrontMemory((self->meshCopy.faceCount + 1) << 2);
        if (self->meshCopy.faceCount >= 0) {
            do {
                s32 v = ReadBufferedS16(in);
                self->faceStarts[j] = v;
                j++;
            } while (self->meshCopy.faceCount >= j);
        }
    }
    ReadMeshFromStream(in, &self->mesh2);
    if (self->flags & (1ULL << 33)) {
        self->mesh2Copy = self->mesh2;
    } else {
        CopyMeshTransformed(&self->mesh2, 0, &self->mesh2Copy);
    }
    ReadFaceTree(in, &self->mesh2Copy, &self->tree2);
    LoadPlacedObject(self, in);
    SetColliderPartListed(self, 1);
    self->desc03()->m44(self);
    if (self->parent == 0) {
        self->desc03()->m32(self);
        InitContactPairFlags(self->world, self);
    }
}

void SetColliderOverrideRadius(Collider* self, f32 v)
{
    self->flags538 |= (u64)0x8000 << 25;
    self->radius3CC = v;
}

void ResetColliderAnchors(void* self)
{
    SetColliderAnchors((Collider*)self, 3, 0, 3, 0);
}

void GetAnchorPreset(s32 index, s32* out, Vec02* dst)
{
    *out = g_anchorPresets[index].value;
    *dst = *g_anchorPresets[index].quad;
}

void SetColliderTurnAnchorPreset(Collider* self, s32 index)
{
    Vec02 v;
    Vec02 local;
    s32 mode;
    GetAnchorPreset(index, &mode, &local);
    Vu0::Q(v) = Vu0::Rotate(self->rot, Vu0::Q(local));
    SetColliderAnchors(self, mode, &v, self->mode470, &self->v460);
}

void SetColliderMoveAnchorPreset(Collider* self, s32 index)
{
    Vec02 v;
    Vec02 local;
    s32 mode;
    GetAnchorPreset(index, &mode, &local);
    Vu0::Q(v) = Vu0::Rotate(self->rot, Vu0::Q(local));
    SetColliderAnchors(self, self->mode450, &self->v440, mode, &v);
}

void SetColliderFlagNibble32(Collider* self, u32 value) { self->flags538 = (self->flags538 & ~(0xFULL << 32)) | ((u64)(value & 0xF) << 32); }

void SetColliderFlagBit47(Collider* self, u32 value) { self->flags538 = (self->flags538 & ~(1ULL << 47)) | ((u64)(value & 1) << 47); }

void SetColliderFlagBit48(Collider* self, s32 flag)
{
    self->flags538 = (self->flags538 & 0xFFFEFFFFFFFFFFFFULL) | ((u64)(flag & 1) << 48);
}

void SetColliderSurfaceKind(Collider* self, u8 value) { self->b2C8 = value; }

void SetColliderFlagNibble36(Collider* self, u32 value) { self->flags538 = (self->flags538 & ~(0xFULL << 36)) | ((u64)(value & 0xF) << 36); }

void SendColliderNotification(Collider* self, s32 kind, void* arg)
{
    SendObjectNotification(self, kind, arg);
    Attach03* n = self->attached;
    if (n != 0) {
        do {
            Attach03* next = n->next;
            Collider* obj = n->owner;
            if (obj != self) {
                void (*fn)(BaseObject*, s32, void*) = obj->desc->m0D;
                if (fn != 0) {
                    fn(obj, kind, arg);
                }
            }
            n = next;
        } while (n != 0);
    }
}

void* FindColliderFloorContact(void* self, s32 key, s32* out)
{
    u8* n = *(u8**)(*(u8**)((u8*)self + 0x480));
    u8* bestIt = 0;
    s32 bestSel = 0;
    f32 bestF = 3.4028235e38f;
    while (n) {
        u8* nxt = *(u8**)(n + 4);
        for (u8* it = *(u8**)n; it; it = *(u8**)(it + 0xD0)) {
            s32 sel = *(u32*)it != (u32)self;
            if (key != 0) {
                if (*(s32*)(it + (sel << 6) + 4) != key) {
                    continue;
                }
            }
            f32 f0 = *(f32*)(it + 0x88);
            if (!(sel == 0 ? 0.7f < f0 : f0 < -0.7f)) {
                continue;
            }
            f0 = *(f32*)(it + (sel << 6) + 0x18);
            if (f0 < bestF) {
                bestF = f0;
                bestSel = sel;
                bestIt = it;
            }
        }
        n = nxt;
    }
    if (out != 0) {
        *out = bestSel;
    }
    return bestIt;
}

void SetColliderGravityDisabled(Collider* self, s32 flag)
{
    self->flags538 = (self->flags538 & ~(1ULL << 51)) | ((u64)(flag & 1) << 51);
}

void SetColliderTreeContactsDropped(Collider* self, s32 value)
{
    u64 bit = (u64)(value & 1) << 42;
    self->flags538 = (self->flags538 & ~(1ULL << 42)) | bit;
    DropColliderContacts(self, value != 0);
}

void SetColliderContactsDropped(Collider* self, s32 value)
{
    u64 bit = (u64)(value & 1) << 43;
    self->flags538 = (self->flags538 & ~(1ULL << 43)) | bit;
    DropColliderContacts(self, value != 0 ? 2 : 0);
}

void SetColliderKindContactsDropped(Collider* self, s32 value)
{
    u64 bit = (u64)(value & 1) << 44;
    self->flags538 = (self->flags538 & ~(1ULL << 44)) | bit;
    DropColliderContacts(self, value != 0 ? 3 : 0);
}

void ResolveContactHandler(Collider* self)
{
    ListFrame frame;
    const Desc03* info = self->desc03();
    if (info->m41 != 0 || info->m3C != 0 || info->m3D != 0) {
        self->handler = self;
    } else if (info->m3E != 0) {
        self->handler = self;
    } else {
        Collider* p = (Collider*)self->parent;
        if (p != 0) {
            self->handler = p->handler;
        } else {
            self->handler = 0;
        }
    }
    Collider* c = (Collider*)self->children.head;
    while (c != 0) {
        if (c->desc->flags & 2) ResolveContactHandler(c);
        c = (Collider*)c->next;
    }
}

Collider* FindHandlerForSlot(Collider* node, s32 offset)
{
    Collider* s;
    while (node != 0 && (s = node->handler) != 0) {
        if (*(s32*)((u8*)s->desc + offset) != 0) return s;
        node = (Collider*)s->parent;
    }
    return 0;
}

void UpdateAnchorModeFlags(Collider* self)
{
    ListFrame frame;
    s32 flag = 0;
    if (self->mode450 == 3) {
        flag = (self->mode470 == 3);
    }
    self->flags538 = (self->flags538 & ~(1ULL << 54)) | ((u64)flag << 54);
    s32 s2 = flag & 1;
    s32 a0 = 0;
    if (self->flags538 & (1ULL << 54)) {
        if (self->parent == 0 || (((Collider*)self->parent)->flags538 & (1ULL << 56)) != 0) a0 = 1;
    }
    self->flags538 = (self->flags538 & ~(1ULL << 56)) | ((u64)a0 << 56);
    Collider* c = (Collider*)self->children.head;
    while (c != 0) {
        if (c->desc->flags & 2) {
            UpdateAnchorModeFlags(c);
            if ((c->flags538 & (1ULL << 55)) == 0) s2 = 0;
        }
        c = (Collider*)c->next;
    }
    u64 bit = (self->flags538 >> 55) & 1;
    if (bit != (u64)s2) {
        self->flags538 = (self->flags538 & ~(1ULL << 55)) | ((u64)(s2 & 1) << 55);
        if (self->parent == 0 && self->root != 0) {
            InitContactPairFlags(self->world, self);
        }
    }
}

s32 CollectContactingPartsToScriptList(Collider* self, s32 value)
{
    Collider* ctx = self->root03();
    ContactRow03* n = ctx->contacts->head;
    while (n != 0) {
        Contact03* e = n->head;
        while (e != 0) {
            s32 idx = ((u32)e->end[0].body ^ (u32)ctx) != 0;
            ContactEnd03* s = &e->end[idx];
            if (s->part == self) {
                void* tmp = e->end[1 - idx].part;
                if (ScriptListContainsValue((ScriptValueFilter*)value, &tmp) == 0) {
                    if (AppendPropertyToScriptList((ScriptListBuilder*)value, &tmp) == 0) return 0;
                }
            }
            e = e->next;
        }
        n = n->next;
    }
    return 1;
}

s32 CollectContactingParts(Collider* obj, s32* outCount, void*** outArr)
{
    Collider* own = obj->root03();
    ContactRow03* nd;
    Contact03* it;
    s32 n = 0;
    for (nd = own->contacts->head; nd; nd = nd->next) {
        for (it = nd->head; it; it = it->next) {
            s32 g = it->end[0].body != own;
            if (IsObjectDescendantOf((BaseObject*)(*(void**)((u8*)it + (g << 6) + 4)), obj))
                n++;
        }
    }
    void** arr = (void**)AllocateBackMemory(n << 2);
    void** end = arr;
    for (nd = own->contacts->head; nd; nd = nd->next) {
        for (Contact03* it2 = nd->head; it2; it2 = it2->next) {
            s32 f = it2->end[0].body != own;
            if (IsObjectDescendantOf((BaseObject*)(*(void**)((u8*)it2 + (f << 6) + 4)), obj)) {
                void* v = *(void**)((u8*)it2 + ((1 - f) << 6) + 4);
                void** p;
                for (p = arr; p < end; p++)
                    if (*p == v) break;
                if (!(p < end)) {
                    *end = v;
                    end++;
                }
            }
        }
    }
    *outArr = arr;
    s32 cnt = end - arr;
    *outCount = cnt;
    return cnt;
}

s32 IsInTouchingList(Touch03* node, Collider* value)
{
    while (node != 0) {
        if (node->obj == value) return 1;
        node = node->next;
    }
    return 0;
}

void UpdateTouchingParts(Collider* self)
{
    Collider* core = self->root03();
    ContactRow03* o;
    Contact03* e;
    Touch03* m;
    Touch03* prev;
    Collider* other;
    void* args;
    for (o = core->contacts->head; o != 0; o = o->next) {
        for (e = o->head; e != 0; e = e->next) {
            s32 i = e->end[0].body != core;
            if (((ContactEnd03*)((u32)e + (i << 6)))->part == self) {
                other = ((ContactEnd03*)((u32)e + ((1 - i) << 6)))->part;
                if (!IsInTouchingList(self->touching, other)) {
                    args = &other;
                    TriggerScriptEvent(self, 6, 1, &args);
                }
            }
        }
    }
    for (m = self->touching; m != 0; m = m->next) {
        s32 found = 0;
        for (o = core->contacts->head; o != 0 && !found; o = o->next) {
            for (e = o->head; e != 0 && !found; e = e->next) {
                s32 i = e->end[0].body != core;
                if (((ContactEnd03*)((u32)e + (i << 6)))->part == self) {
                    other = ((ContactEnd03*)((u32)e + ((1 - i) << 6)))->part;
                    if (other == m->obj) found = 1;
                }
            }
        }
        if (!found) {
            args = m;
            TriggerScriptEvent(self, 7, 1, &args);
        }
    }
    FreeTouchNodes(self->world, self->touching);
    self->touching = 0;
    for (o = core->contacts->head; o != 0; o = o->next) {
        for (e = o->head; e != 0; e = e->next) {
            s32 i = e->end[0].body != core;
            if (((ContactEnd03*)((u32)e + (i << 6)))->part == self) {
                other = ((ContactEnd03*)((u32)e + ((1 - i) << 6)))->part;
                Touch03* n = AllocateTouchNode(self->world);
                n->obj = other;
                if (self->touching != 0) prev->next = n; else self->touching = n;
                prev = n;
            }
        }
    }
}

s32 RequestColliderLaunch(Collider* self, void* source, TrackedNodeOffer* offer)
{
    return 0;
}


struct MeshMotion {
    Vec02* velocity;
    Vec02* accel;
    struct Tri { s32 i[3]; } *tris;
};

struct MeshFace {
    Vec02 normal;
    f32 dist;
    u8 pad14[0xA];
    u16 ref;
};

// An edge of a collision mesh (Mesh03::edges, 0x10 bytes): its two vertices and the two
// faces it joins.
struct MeshEdge {
    s16 verts[2];           // 0x00
    s16 faces[2];           // 0x04
    u8 pad08[0x10 - 0x08];
};

void* AllocateZeroedBackMemory(s32 size);

// Builds the collider's hook: two zeroed vectors per vertex, and the three vertex indices of
// each face gathered from the edges that bound it, then wound to face along the face's
// normal.
void InitColliderMeshMotion(Collider* self)
{
    Vec02 e1;
    Vec02 e2;
    Vec02 n;
    if (self->hook != 0) {
        return;
    }
    PushBackMemoryMark();
    MeshMotion* h = (MeshMotion*)AllocateFrontMemory(0xC);
    self->hook = h;
    h->velocity = (Vec02*)AllocateZeroedFrontMemory(self->meshCopy.vertCount * 16);
    h->accel = (Vec02*)AllocateZeroedFrontMemory(self->meshCopy.vertCount * 16);
    h->tris = (MeshMotion::Tri*)AllocateZeroedFrontMemory(self->meshCopy.faceCount * 12);
    s32* counts = (s32*)AllocateZeroedBackMemory(self->meshCopy.faceCount * 4);
    MeshMotion::Tri* tri;
    s32 f;
    for (s32 i = 0; i < self->meshCopy.edgeCount; i++) {
        MeshEdge* e = &((MeshEdge*)self->meshCopy.edges)[i];
        for (s32 j = 0; j < 2; j++) {
            f = e->faces[j];
            tri = &h->tris[f];
            for (s32 k = 0; k < 2; k++) {
                s32 v = e->verts[k];
                s32 m;
                for (m = 0; m < counts[f]; m++) {
                    if (v == tri->i[m]) {
                        break;
                    }
                }
                if (m >= counts[f] && m < 3) {
                    tri->i[counts[f]] = v;
                    counts[f]++;
                }
            }
        }
    }
    Vec02* verts = (Vec02*)self->mesh.verts;
    for (f = 0; f < self->meshCopy.faceCount; f++) {
        tri = &h->tris[f];
        MeshFace* face = &((MeshFace*)self->mesh.faces)[f];
        Vu0::Q(e1) = Vu0::Sub(Vu0::Q(verts[tri->i[1]]), Vu0::Q(verts[tri->i[0]]));
        Vu0::Q(e2) = Vu0::Sub(Vu0::Q(verts[tri->i[2]]), Vu0::Q(verts[tri->i[0]]));
        Vu0::Q(n) = Vu0::Cross(Vu0::Q(e1), Vu0::Q(e2));
        if (Vu0::ToFloat(Vu0::Dot(Vu0::Q(n), Vu0::Q(face->normal))) < 0.0f) {
            s32 b = tri->i[1];
            tri->i[1] = tri->i[2];
            tri->i[2] = b;
        }
    }
    PopBackMemoryMark();
}

void AdvanceColliderMeshMotion(Collider* self, f32 dt)
{
    Vec02 a, b;
    Vec02* pts = (Vec02*)self->mesh.verts;
    Vec02* vel = ((MeshMotion*)self->hook)->velocity;
    Vec02* acc = ((MeshMotion*)self->hook)->accel;
    f32 big = 0.0f;
    for (s32 i = 0; i < self->mesh.vertCount; i++) {
        u128 p = Vu0::Q(pts[i]);
        u128 s = Vu0::Scalar(dt);
        u128 v = Vu0::Q(vel[i]);
        u128 t = Vu0::Scalar(dt * (dt * 0.5f));
        u128 c = Vu0::Q(acc[i]);
        Vu0::Q(pts[i]) = Vu0::MulAddX2(p, v, s, c, t);
        u128 v2 = Vu0::Q(vel[i]);
        u128 s2 = Vu0::Scalar(dt);
        u128 c2 = Vu0::Q(acc[i]);
        Vu0::Q(vel[i]) = Vu0::MulAddX(v2, c2, s2);
        f32 len = Vu0::ToFloat(Vu0::Dot(Vu0::Q(pts[i]), Vu0::Q(pts[i])));
        if (big < len) {
            big = len;
        }
    }
    self->radius3CC = Fpu::Sqrt(big);
    MeshFace* face = (MeshFace*)self->mesh.faces;
    MeshMotion::Tri* tri = ((MeshMotion*)self->hook)->tris;
    for (s32 i = 0; i < self->mesh.faceCount; i++) {
        MeshFace* f = &face[i];
        Vu0::Q(a) = Vu0::Sub(Vu0::Q(pts[tri[i].i[1]]), Vu0::Q(pts[tri[i].i[0]]));
        Vu0::Q(b) = Vu0::Sub(Vu0::Q(pts[tri[i].i[2]]), Vu0::Q(pts[tri[i].i[0]]));
        u128 n = Vu0::Cross(Vu0::Q(a), Vu0::Q(b));
        Vu0::Q(f->normal) = n;
        n = Vu0::DivX(Vu0::Q(f->normal), Vu0::Sqrt(Vu0::Dot(Vu0::Q(f->normal), Vu0::Q(f->normal))));
        Vu0::Q(f->normal) = n;
        *(u32*)&f->dist = Vu0::ToBits(Vu0::Dot(Vu0::Q(f->normal), Vu0::Q(pts[f->ref])));
    }
}

void MoveCollider(Collider* self, f32 x, void* b)
{
    if (self->hook != 0) {
        AdvanceColliderMeshMotion(self, x);
    }
    MovePlacedObject(self, x, b);
}


void ApplyColliderImpulseEvent(void* a0, f32 value, void* a1, void* a2)
{
    Collider* self = (Collider*)a0;
    Vec02* origin = (Vec02*)a1;
    Vec02* target = (Vec02*)a2;
    Vec02 vel;
    Vec02 dir;
    Contact03* contact;
    Collider* group[1];
    ComputeObjectMotionInFrame(self, 0, origin, &vel, 0, 0, 0);
    Vu0::Set(dir, Vu0::NormalizeOr(Vu0::Sub(Vu0::Q(*target), Vu0::Q(vel)), Vu0::Q(g_unitZVector)));
    f32 zero = 0.0f;
    contact = 0;
    CreatePooledContact(zero, self, 0, origin, &dir, 0xC, 0, 0, &contact);
    *(Vec02*)((u8*)&contact->end[1] + 0x30) = *target;
    contact->bounce = zero;
    contact->friction = 1.0f;
    *(f32*)&contact->featureEnd0 = value;
    NotifyContactEnds(self->world, 1, &contact);
    group[0] = (Collider*)self->root;
    SolveColliderGroupContacts(self->world, 1, group, 1, &contact, zero, 2);
    FreePooledContactChain(self->world, contact);
}


void ComputeColliderJumpVelocity(Collider* self, f32* p, f32* out, f32 a)
{
    f32 roots[4];
    f32 m = p[2] >? self->v140.z;
    out[2] = Fpu::Sqrt(self->gravity.z * ((m + a - self->v140.z) * -2.0f));
    SolveQuadratic(self->gravity.z * 0.5f, out[2], self->v140.z - p[2], roots);
    f32 dx = p[0] - self->v140.x;
    f32 r0 = roots[0];
    f32 r1 = roots[1];
    f32 t = r1 >? r0;
    out[0] = dx / t;
    out[1] = (p[1] - self->v140.y) / t;
}

s32 HandleObjectEvent(Collider* self, ObjectEvent* shape)
{
    if (shape->eventFlags & 0x8) {
        ApplyColliderImpulseEvent(self, shape->radius, (u8*)shape + 0x20, (u8*)shape + 0x30);
    }
    return shape->eventFlags != 0;
}

void CopyColliderMeshesInFrame(Collider* self, Collider* src, s32 extra)
{
    Vec02 m[4];
    Mesh03 tmp;
    BuildMatrixFromRotationAndTranslation(&src->pos, &src->rot, (Mat4A*)m);
    f32 maxDist = 0.0f;
    for (s32 i = 0; i < src->mesh.vertCount; i++) {
        f32 d = Vu0::ToFloat(Vu0::Dot(Vu0::Q(((Vec02*)src->mesh.verts)[i]), Vu0::Q(((Vec02*)src->mesh.verts)[i])));
        if (maxDist < d) {
            maxDist = d;
        }
    }
    self->radius3CC = Fpu::Sqrt(maxDist);
    tmp = src->mesh;
    tmp.vertCount = tmp.vertCount + extra;
    CopyMeshTransformed(&tmp, (s32)m, &self->mesh);
    BuildMatrixFromRotationAndTranslation(&self->v140, &self->m110, (Mat4A*)m);
    CopyMeshTransformed(&self->mesh, (s32)m, &self->meshCopy);
    self->f4B8 = 0;
    CloneTreeNodes(&src->meshCopy, &src->tree, &self->meshCopy, &self->tree);
    CloneTreeNodes(&src->mesh2Copy, &src->tree2, &self->mesh2Copy, &self->tree2);
    InitColliderMeshMotion(self);
}

void ExtractContactsByPartMode(Collider* self, Contact03** out)
{
    Contact03* freed = 0;
    if (self->root == self) {
        ContactRow03* h = self->contacts->head;
        if (h) {
            do {
                Contact03** pp = (Contact03**)h;
                Contact03* n;
                while ((n = *pp) != 0) {
                    int k = (n->end[0].body != self);
                    Collider* e = n->end[1 - k].part;
                    while (e && !e->partMode) e = (Collider*)e->parent;
                    if (e) {
                        switch (e->partMode) {
                        case 1: {
                            Contact03* c = (Contact03*)TakePoolSlot(&self->world->pool1AFC);
                            *c = *n;
                            c->next = *out;
                            *out = c;
                            break;
                        }
                        case 3:
                            *pp = n->next;
                            n->next = freed;
                            freed = n;
                            continue;
                        case 4:
                            *pp = n->next;
                            n->next = *out;
                            *out = n;
                            continue;
                        }
                    }
                    pp = &n->next;
                }
                *h->link = h->head;
                h = h->next;
            } while (h);
        }
        FreePooledContactChain((World*)self->world, freed);
    }
}

struct TreeNode03;
s32 FindPlaneTreeNodeForPoint(Vec02* pos, TreeNode03* nodes);

s32 IsPointInsideCollider(Collider* self, Vec02* p)
{
    if ((self->flags538 & ((u64)0x8000 << 25)) != 0) {
        s32 inside = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(*p), Vu0::Q(self->v140)))) < self->radius3CC;
        if (inside) {
            return 1;
        }
    }
    if (self->tree.nodes != 0 && FindPlaneTreeNodeForPoint((Vec02*)p, self->tree.nodes) != 0) {
        return 1;
    }
    return 0;
}

void SetColliderFlagBit52(Collider* self, u32 flag)
{
    self->flags538 = (self->flags538 & 0xFFEFFFFFFFFFFFFFULL) | ((u64)(flag & 1) << 52);
}

void GetColliderFlagBit52(Collider* self, u32* out)
{
    u32 bit = (u32)(self->flags538 >> 52) & 1;
    *out = bit;
}

void NumberColliderParts(Collider* self, s32* index, Collider** list)
{
    ListFrame frame;
    self->index = *index;
    list[*index] = self;
    (*index)++;
    for (Collider* item = (Collider*)self->children.head; item; item = (Collider*)item->next)
        if (item->desc->flags & 2)
            item->desc03()->m35(item, index, list);
}

ASM_FUNC(func_001BC7F8);

// A row of what ComputeColliderImpulseResponse writes, one per part (Collider::index): the
// change of velocity and of spin.
struct ImpulseRow {
    Vec02 linear;           // 0x00
    Vec02 angular;          // 0x10
};

void ApplyColliderInverseInertia(Collider* self, Vec02* in, Vec02* out);

void ComputeColliderImpulseResponse(void* self, s32 a1, Contact03* c, s32 idx, ContactEnd03* hit, ImpulseRow* rows)
{
    Vec02 dir;
    Vec02 v;
    Vec02 arm;
    Vec02 k;
    ContactEnd03* e = &c->end[idx];
    if (idx == 0) {
        dir = hit->point;
    } else {
        Vu0::Q(v) = Vu0::FromFloat(-1.0f);
        Vu0::Q(dir) = Vu0::MulX(Vu0::Q(hit->point), Vu0::Q(v));
    }
    for (Collider* b = c->end[idx].part; b != 0; b = (Collider*)b->parent) {
        if (b->flags538 & (1ULL << 54)) {
            if (b->flags538 & (1ULL << 56)) {
                break;
            }
            continue;
        }
        ImpulseRow* row = &rows[b->index];
        Vu0::Set(arm, Vu0::Cross(Vu0::Sub(Vu0::Q(e->point), Vu0::Q(b->v140)), Vu0::Q(dir)));
        ConstrainVectorByParentAnchor(b, (VectorConstraint*)&b->v440, &dir, &v, &dir);
        Vu0::Q(k) = Vu0::FromFloat(1.0f / b->mass);
        Vu0::Q(row->linear) = Vu0::MulX(Vu0::Q(v), Vu0::Q(k));
        ApplyColliderInverseInertia(b, &arm, &row->angular);
        ConstrainVectorByParentAnchor(b, (VectorConstraint*)&b->v460, &row->angular, &row->angular, 0);
    }
}

void ComputeColliderPointVelocity(Collider* body, Vec02* point, ImpulseRow* row, Vec02* out);

void AddParentVelocityToChildRows(void* unusedA, void* unusedB, s32 n, Collider** list, ImpulseRow* rows)
{
    Vec02 vel;
    Vec02 ang;
    Vec02 loc;
    Vec02 axis;
    Vec02 rn;
    Vec02 ro;
    Vec02 t;
    for (s32 i = 1; i < n; i++) {
        Collider* o = list[i];
        Collider* parent = (Collider*)o->parent;
        ImpulseRow* mine = &rows[o->index];
        ImpulseRow* par = &rows[parent->index];
        ComputeColliderPointVelocity(parent, &o->v140, par, &vel);
        if (o->flags538 & (1ULL << 54)) {
            Vu0::Q(mine->linear) = Vu0::Add(Vu0::Vec::Of(mine->linear), Vu0::Vec::Of(vel)).q;
            Vu0::Q(mine->angular) = Vu0::Add(Vu0::Vec::Of(mine->angular), Vu0::Vec::Of(par->angular)).q;
            continue;
        }
        ConstrainVectorByParentAnchor(o, (VectorConstraint*)&o->v440, &vel, 0, &vel);
        ConstrainVectorByParentAnchor(o, (VectorConstraint*)&o->v460, &par->angular, 0, &ang);
        if (o->mode470 != 3) {
            s32 still = __builtin_fabsf(Vu0::ToFloatMoved(Vu0::Vec::Of(o->offset))) < 0.0001f
                && __builtin_fabsf(Vu0::ToFloatY(Vu0::Vec::Of(o->offset))) < 0.0001f
                && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Vec::Of(o->offset))) < 0.0001f;
            if (!still) {
                const u128& fb = Vu0::Q(D_00248D30);
                Vu0::Q(loc) = Vu0::RotateTransposed(o->m110, Vu0::Vec::Of(vel)).q;
                Vu0::Q(axis) = Vu0::Cross(Vu0::Vec::Of(o->offset), Vu0::Vec::Of(loc)).q;
                Vu0::Vec l = Vu0::Length(Vu0::Vec::Of(axis));
                if (Vu0::ToFloatMoved(l) < 0.0001f) {
                    Vu0::Set(axis, fb);
                } else {
                    Vu0::Set(axis, Vu0::DivX(Vu0::Vec::Of(axis), l).q);
                }
                if (0.0001f < Vu0::ToFloat(l)) {
                    Vu0::Q(rn) = Vu0::RotateUntied(o->inertia, Vu0::Vec::Of(axis)).q;
                    f32 d = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(rn), Vu0::Vec::Of(axis)));
                    f32 offsetSq = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(o->offset), Vu0::Vec::Of(o->offset)));
                    f32 mass = o->mass;
                    Vu0::Q(ro) = Vu0::Rotate(o->m110, Vu0::Vec::Of(o->offset)).q;
                    f32 roSq = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Vec::Of(ro), Vu0::Vec::Of(ro)));
                    Vu0::Q(t) = Vu0::Cross(Vu0::Vec::Of(vel), Vu0::Vec::Of(ro)).q;
                    Vu0::Q(t) = Vu0::MulX(Vu0::Vec::Of(t), Vu0::Vec::Scalar(mass / (mass + d / offsetSq) / roSq)).q;
                    ConstrainVectorByParentAnchor(o, (VectorConstraint*)&o->v460, &t, &t, 0);
                    Vu0::Q(ang) = Vu0::Add(Vu0::Vec::Of(ang), Vu0::Vec::Of(t)).q;
                }
            }
        }
        Vu0::Q(mine->linear) = Vu0::Add(Vu0::Vec::Of(mine->linear), Vu0::Vec::Of(vel)).q;
        Vu0::Q(mine->angular) = Vu0::Add(Vu0::Vec::Of(mine->angular), Vu0::Vec::Of(ang)).q;
    }
}

// A Contact03 with the fields the group solve reads and writes.
struct SolveContact_1BCD00 {
    ContactEnd03 end[2];            // 0x00
    Vec02 normal;                   // 0x80
    f32 depth;                      // 0x90
    u8 pad94[0x98 - 0x94];
    f32 bounce;                     // 0x98
    s32 kind;                       // 0x9C
    f32 limit;                      // 0xA0
    u8 padA4[0xB0 - 0xA4];
    Vec02 relVel;                   // 0xB0
    f32 push;                       // 0xC0
    f32 impulse;                    // 0xC4
    f32 speed;                      // 0xC8
    s32 index;                      // 0xCC
};
struct SolveHandler_1BCD00;
struct SolveHandlerDesc_1BCD00 { u8 pad00[0x108]; void (*m108)(SolveHandler_1BCD00* self, s32 kind, ActiveSetItem* it, s32 end, f32 dt); };
struct SolveHandler_1BCD00 { SolveHandlerDesc_1BCD00* desc; };

void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateBackMemory(s32 size);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
// Left with pointers: RunActiveSetSolver takes the contact list, the counts and the lists as s32.
void RunActiveSetSolver(ActiveSetSolver* self, s32 flags, s32 n, SolveContact_1BCD00** contacts, s32* counts, void** lists);
void AddFrictionItemsAndSolve(f32 dt, ActiveSetSolver* loc, s32 flags, s32 n, SolveContact_1BCD00** contacts, s32* counts, void** lists);

void SolveColliderGroupContacts(World* world, s32 nParts, Collider** parts, s32 n, Contact03** list, f32 dt, s32 flags)
{
    SolveContact_1BCD00** contacts = (SolveContact_1BCD00**)list;
    ActiveSetSolver loc;
    s32 i;
    if (flags & 1) {
        if (n == 0) {
            return;
        }
    } else {
        if (flags & 4) {
            for (i = 0; i < n; i++) {
                SolveContact_1BCD00* c = contacts[i];
                if (c->kind == 11) {
                    if (0.1f < __builtin_fabsf(c->depth)) {
                        break;
                    }
                } else if (c->depth < -2.0f) {
                    break;
                }
            }
            if (!(i < n)) {
                flags &= ~4;
            }
        }
        if (flags & 2) {
            i = 0;
            if (i < n) {
                do {
                    SolveContact_1BCD00* c = contacts[i];
                    if (c->kind == 11) {
                        if (5.0f < __builtin_fabsf(Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(c->relVel), Vu0::Q(c->normal))))) {
                            break;
                        }
                    } else if (Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(c->relVel), Vu0::Q(c->normal))) < -5.0f) {
                        break;
                    }
                    i++;
                } while (i < n);
            }
            if (!(i < n)) {
                flags &= ~2;
            }
        }
        if (flags == 0) {
            return;
        }
    }
    PushBackMemoryMark();
    void** lists = (void**)AllocateBackMemory(nParts * 4);
    s32* counts = (s32*)AllocateBackMemory(nParts * 4);
    FillMemory(counts, 0, nParts * 4);
    for (s32 k = 0; k < nParts; k++) {
        Collider* part = parts[k];
        part->solverIndex = k;
        lists[k] = AllocateBackMemory(0xC0);
        part->desc03()->m35(part, &counts[k], (Collider**)lists[k]);
    }
    for (i = 0; i < n; i++) {
        contacts[i]->index = i;
    }
    InitActiveSetSolver(&loc, n);
    for (i = 0; i < n; i++) {
        SolveContact_1BCD00* c = contacts[i];
        ActiveSetItem* it = (ActiveSetItem*)(loc.items + i * 0x60);
        it->owner = c;
        *(Vec02*)it->axis = c->normal;
        switch (c->kind) {
        case 11:
            it->kind = 2;
            break;
        case 12:
            it->kind = 0;
            it->bounded = 1;
            it->limit = c->limit;
            break;
        default:
            it->kind = 0;
            break;
        }
        AddActiveSetItem(&loc, it);
    }
    if (flags & 4) {
        for (s32 j = 0; j < n; j++) {
            ActiveSetItem* it = (ActiveSetItem*)(loc.items + j * 0x60);
            SolveContact_1BCD00* c = contacts[j];
            if (it->kind == 2) {
                it->val = c->depth;
            } else {
                it->val = c->depth + 1.0f;
            }
            for (s32 e = 0; e < 2; e++) {
                SolveHandler_1BCD00* h = (SolveHandler_1BCD00*)FindHandlerForSlot(c->end[e].part, 0x108);
                if (h != 0 && h->desc->m108 != 0) {
                    h->desc->m108(h, 0xC, it, e, dt);
                }
            }
        }
        RunActiveSetSolver(&loc, 4, n, contacts, counts, lists);
        ApplySolvedImpulsesToParts(&loc, nParts, counts, (Collider***)lists, 100.0f, 1.0f);
        for (s32 j = 0; j < nParts; j++) {
            parts[j]->desc03()->m2F(parts[j], 0);
        }
        if (flags == 4) {
            goto done;
        }
        ResetActiveSetSolver(&loc);
    }
    if (flags & 1) {
        RefreshContactEndPoints(world, n, (Contact03**)contacts);
        NotifyContactEnds(world, n, list);
        for (s32 j = 0; j < n; j++) {
            ActiveSetItem* it = (ActiveSetItem*)(loc.items + j * 0x60);
            SolveContact_1BCD00* c = contacts[j];
            Vu0::StoreX(it->val, Vu0::Dot(Vu0::Q(c->relVel), Vu0::Q(c->normal)));
            for (s32 e = 0; e < 2; e++) {
                SolveHandler_1BCD00* h = (SolveHandler_1BCD00*)FindHandlerForSlot(c->end[e].part, 0x108);
                if (h != 0 && h->desc->m108 != 0) {
                    h->desc->m108(h, 9, it, e, dt);
                }
            }
        }
    } else {
        for (s32 j = flags & 1; j < n; j++) {
            SolveContact_1BCD00* c = contacts[j];
            ActiveSetItem* it = (ActiveSetItem*)(loc.items + j * 0x60);
            Vu0::StoreX(c->speed, Vu0::Dot(Vu0::Q(c->relVel), Vu0::Q(c->normal)));
            f32 r = RandomFloatInRange(0.9f, 1.1f);
            it->val = c->speed * (c->bounce * r + 1.0f);
            for (s32 e = 0; e < 2; e++) {
                SolveHandler_1BCD00* h = (SolveHandler_1BCD00*)FindHandlerForSlot(c->end[e].part, 0x108);
                if (h != 0 && h->desc->m108 != 0) {
                    h->desc->m108(h, 10, it, e, dt);
                }
            }
        }
    }
    AddFrictionItemsAndSolve(dt, &loc, flags & ~4, n, contacts, counts, lists);
    if (flags & 1) {
        ApplySolvedImpulsesToParts(&loc, nParts, counts, (Collider***)lists, 5000.0f, 50.0f);
    } else {
        ApplySolvedImpulsesToParts(&loc, nParts, counts, (Collider***)lists, 5000.0f, 50.0f);
    }
done:
    for (i = 0; i < nParts; i++) {
        Collider* part = parts[i];
        part->solverIndex = -1;
        if (flags & 1) {
            part->desc03()->m31(part, 0);
        } else if (flags & 2) {
            part->desc03()->m30(part, 0);
        }
        for (s32 j = 0; j < counts[i]; j++) {
            ((Collider**)lists[i])[j]->index = -1;
        }
    }
    if (flags & 1) {
        for (i = 0; i < n; i++) {
            contacts[i]->push = ((ActiveSetItem*)(loc.items + i * 0x60))->x;
        }
    } else if (flags & 2) {
        for (i = 0; i < n; i++) {
            contacts[i]->impulse = ((ActiveSetItem*)(loc.items + i * 0x60))->x;
        }
    }
    PopBackMemoryMark();
}

s32 CollectGroupItems(s32 count, Collider** roots, s32 cap, Contact03** out)
{
    s32 n = 0;
    s32 i;
    Collider* root;
    for (i = 0; i < count; i++) {
        root = roots[i];
        root->flags538 |= ((u64)1 << 58);
        for (Contact03* item = root->contacts4B4; item; item = item->next) {
            if (n >= cap) goto done;
            out[n++] = item;
        }
        Contacts03* gh = root->contacts;
        for (ContactRow03* g = gh->head; g; g = g->next) {
            if (g->other->flags538 & ((u64)1 << 58)) continue;
            for (Contact03* item = g->head; item; item = item->next) {
                if (n >= cap) goto done;
                out[n++] = item;
            }
        }
    }
done:
    {
        Collider** r = roots;
        if (count > 0) {
            i = count;
            do {
                root = *r;
                i--;
                r++;
                root->flags538 &= ~((u64)1 << 58);
            } while (i != 0);
        }
    }
    return n;
}

void CollectConnectedColliders(Collider* self, s32* outQueued, Collider** queue, s32* outFlagged, Collider** list)
{
    s32 nq = 1;
    s32 nl = 0;
    queue[0] = self;
    self->flags538 |= (u64)1 << 57;
    s32 qi;
    for (qi = 0; qi < nq; qi++) {
        Collider* x = queue[qi];
        ContactRow03* node = x->contacts->head;
        while (node != 0) {
            Collider* y = node->other;
            if ((y->flags538 & ((u64)1 << 57)) == 0 && node->head != 0) {
                if (y->flags538 & ((u64)1 << 55)) {
                    list[nl] = y;
                    nl++;
                } else {
                    queue[nq] = y;
                    nq++;
                }
                y->flags538 |= (u64)1 << 57;
            }
            node = node->next;
        }
    }
    if (nl > 0) {
        qi = nl;
        Collider** p = list;
        do {
            Collider* z = *p;
            p++;
            z->flags538 &= ~((u64)1 << 57);
        } while (--qi != 0);
    }
    *outQueued = nq;
    *outFlagged = nl;
}

void SetColliderForcedState(Collider* obj, s32 mode)
{
    if (mode) {
        u64 f = obj->flags538;
        u64 sv = obj->savedC0;
        sv &= ~(u64)1;
        sv |= (f >> 54) & 1;
        sv &= ~(u64)2;
        u64 b55 = (f >> 55) & 1;
        f |= (u64)1 << 54;
        s32 a = obj->mode450;
        s32 b = obj->mode470;
        f |= (u64)1 << 55;
        sv |= b55 << 1;
        obj->save90 = a;
        obj->save94 = b;
        obj->savedC0 = sv;
        obj->mode450 = 3;
        obj->mode470 = 3;
        obj->flags538 = f;
    } else {
        u64 bit0 = (s32)obj->savedC0 & 1;
        u64 bit1 = (u64)((s32)(obj->savedC0 >> 1) & 1);
        s32 a = obj->save90;
        s32 b = obj->save94;
        obj->mode450 = a;
        obj->mode470 = b;
        obj->flags538 = ((obj->flags538 & ~((u64)1 << 54)) | (bit0 << 54)) & ~((u64)1 << 55) | (bit1 << 55);
    }
}

void SortCollidersByContactCount(s32 n, Collider** objs)
{
    s32 local[5];
    Collider** sorted;
    s32* counts;
    s32 i;

    if (n < 2) {
        return;
    }
    PushBackMemoryMark();
    sorted = (Collider**)AllocateBackMemory(n * 4);
    counts = (s32*)AllocateBackMemory(n * 4);
    FillMemory(counts, 0, n * 4);
    FillMemory(local, 0, 20);
    for (i = 0; i < n; i++) {
        Collider* o = objs[i];
        u32 cnt = 0;
        ContactRow03* p = o->contacts->head;
        while (p != 0) {
            if (p->head != 0 && (o->flags538 & 0x0080000000000000ULL) != 0) {
                cnt++;
                if (cnt >= 4) {
                    break;
                }
            }
            p = p->next;
        }
        counts[i] = cnt;
        if (cnt < 4) {
            local[cnt + 1]++;
        }
    }
    i = 1;
    do {
        local[i] += local[i - 1];
        i++;
    } while ((u32)i < 5);
    for (i = 0; i < n; i++) {
        s32 cnt = counts[i];
        s32 idx = local[cnt];
        sorted[idx] = objs[i];
        local[cnt] = idx + 1;
    }
    CopyMemory(objs, sorted, n * 4);
    PopBackMemoryMark();
}

void ProcessColliderGroup(World* ctx, s32 n, Collider** arr, f32 f, s32 ex)
{
    Contact03* buf[0x40];
    ListFrame it;
    s32 v = CollectGroupItems(n, arr, 0x40, buf);
    if (v < 0x40 || n < 2) {
        SolveColliderGroupContacts(ctx, n, arr, v, buf, f, ex);
        return;
    }
    SortCollidersByContactCount(n, arr);
    s32 half = n / 2;
    s32 i;
    u8* p;
    for (i = 0; i < half; i++) {
        arr[i]->flags538 |= 1ULL << 58;
    }
    ProcessColliderGroup(ctx, n - half, arr + half, f, ex);
    for (i = 0; i < half; i++) {
        arr[i]->flags538 &= ~(1ULL << 58);
    }
    for (i = half; i < n; i++) {
        ListWalk::Begin(&it, &arr[i]->parts);
        for (p = ListWalk::Next(&it); p; p = ListWalk::Next(&it)) {
            SetColliderForcedState((Collider*)p, 1);
        }
        ListWalk::End(&it);
    }
    ProcessColliderGroup(ctx, half, arr, f, ex);
    for (i = half; i < n; i++) {
        ListWalk::Begin(&it, &arr[i]->parts);
        for (p = ListWalk::Next(&it); p; p = ListWalk::Next(&it)) {
            SetColliderForcedState((Collider*)p, 0);
        }
        ListWalk::End(&it);
    }
}

void ProcessColliderGroups(World* self, s32 flags, f32 f)
{
    ListFrame fr;
    ConnectedCounts c;
    Collider** arr1;
    Collider** arr2;
    s32 j;
    s32 i;
    Collider* s;
    PushBackMemoryMark();
    arr1 = (Collider**)AllocateBackMemory(self->count38 * 4);
    c.n1 = 0;
    arr2 = (Collider**)AllocateBackMemory(self->count38 * 4);
    c.n2 = 0;
    SyncDataCache(0);
    if (flags & 1) {
        s32 e = (s32)&self->list60;
        fr.link = (u8*)e;
        fr.list = (void*)e;
        s32 old = (s32)g_activeListFrames;
        s32 link = *(s32*)(e + 8);
        g_activeListFrames = &fr;
        fr.prev = (ListFrame*)old;
        s32 h = *(s32*)e;
        fr.offset = link;
        fr.link = (u8*)(h + link);
        s32 p = h;
        while (p != 0) {
            Collider* node = (Collider*)p;
            if (!(node->desc->flags & 2) || (node->flags538 & (1ULL << 55))) {
                if (node->tries < 2) {
                    ((ColliderStepFn)node->desc->m1B)(node, 0, g_gameClock[2]);
                }
            }
            s32 nx = *(s32*)fr.link;
            fr.link = (u8*)(nx + fr.offset);
            p = nx;
        }
        g_activeListFrames = fr.prev;
    }
    for (s = (Collider*)self->list6C.head; s != 0; s = (Collider*)((ListedCollider*)s)->next) {
        if (s->flags538 & (1ULL << 57)) continue;
        if (s->flags538 & (1ULL << 55)) continue;
        CollectConnectedColliders(s, &c.n1, arr1, &c.n2, arr2);
        if (flags & 1) {
            for (i = 0; i < c.n1; i++) {
                if (arr1[i]->tries < 2) break;
            }
            if (i >= c.n1) {
                for (j = 0; j < c.n2; j++) {
                    if (arr2[j]->tries < 2) break;
                }
                if (j >= c.n2) continue;
            }
            for (i = 0; i < c.n1; i++) {
                ((ColliderStepFn)arr1[i]->desc->m1B)(arr1[i], 0, g_gameClock[2]);
            }
        }
        ProcessColliderGroup(self, c.n1, arr1, f, flags);
        for (i = 0; i < c.n1; i++) {
            if (!IsObjectTreeAtRest((Actor6C*)arr1[i])) {
                ClearRootTries(arr1[i]);
            }
        }
    }
    for (s = (Collider*)self->bodies.head; s != 0; s = *(Collider**)((u8*)s + 0x2D0)) {
        s->flags538 &= ~(1ULL << 57);
    }
    PopBackMemoryMark();
}

void SwapSortRecords(u8* base, s32 stride, s32 rowB, s32 rowA)
{
    s32* b = (s32*)(base + rowB * stride);
    s32* a = (s32*)(base + rowA * stride);
    for (s32 n = stride; n > 0; n -= 4) {
        s32 y = *a;
        s32 x = *b;
        *b = y;
        *a = x;
        a++;
        b++;
    }
}

void HeapSortRecords(void* records, s32 n, s32 size, SortCompareFn cmp)
{
    u8* base = (u8*)records;
    if (n < 2) return;
    s32 end = n - 1;
    s32 start = n / 2;
    for (;;) {
        if (start > 0) {
            start--;
        } else {
            SwapSortRecords(base, size, end, 0);
            s32 t = end;
            end = t - 1;
            if (t < 2) return;
        }
        s32 i = start;
        s32 c = 2 * i + 1;
        if (end < c) continue;
        for (;;) {
            if (c < end) {
                s32 s0 = c + 1;
                if (cmp(base + c * size, base + s0 * size) < 0) c = s0;
            }
            if (cmp(base + i * size, base + c * size) < 0) {
                SwapSortRecords(base, size, i, c);
                i = c;
                c = c + (c + 1);
                if (end < c) break;
                continue;
            }
            break;
        }
    }
}