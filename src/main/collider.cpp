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
#include "asm_functions.h"
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
#include "list_walk.h"
#include "collider_pose.h"
#include "playing_sound.h"
#include "mesh_collision.h"
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
struct Mat3;
struct Matrix3x4;

struct ScriptListBuilder;
struct ScriptValueFilter;

#define VA_ARG_WORD(ap, T) (*(T*)((ap += 8) - 8))

extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
extern f32 g_gameTime[];
u16 ReadBufferedU16(BufferedStream* self);
void* AllocateZeroedFrontMemory(s32 size);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
BodyContactTable* TakeContactTable(World* owner, Collider* self);
void ReleaseContactTable(World* owner, BodyContactTable* handle);
void FreeTouchNodes(World* owner, TouchedObjectLink* node);
struct ClearedRecord;
struct ScriptScope;
void* AllocateFrontMemory(s32 size);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateBackMemory(u32 bytes);
void* AllocateBackMemory(s32 size);
s32 AppendPropertyToScriptList(ScriptListBuilder* self, void* value);
// What a vector is constrained by: an axis, and how (0 none, 1 the part along the axis removed,
// 2 only the part along it kept, 3 zero).
struct VectorConstraint {
    Vec4 axis;             // 0x00
    s32 kind;               // 0x10
};
// A quadword passed by value in one register (func_001B8820's position).
typedef u64 Qword128 __attribute__((mode(TI)));
void TransformMeshToWorld(CollisionMesh* a, CollisionMesh* b, Qword128 q, Mat3* c);
// An anchor preset (func_001BB028): a direction and a mode.
struct AnchorPreset { const Vec4* quad; s32 value; };
extern AnchorPreset g_anchorPresets[8];
void* AllocateBackMemory(s32 n);
// Matched by indexing the end as (u32)e + (i << 6).

void FreeTouchNodes(World* owner, TouchedObjectLink* node);
TouchedObjectLink* AllocateTouchNode(World* self);
// NEAR: 14 lines: retail preloads f400/f40C into s0 (lw s0 before loop and in the bnel delay slot), we load into v1; f408 loop test reload; last loop pointer s2 vs index


s32 ReadBufferedU8(BufferedStream* in);
void ReadMeshFromStream(BufferedStream* in, CollisionMesh* p);
void ReadFaceTree(BufferedStream* in, CollisionMesh* a, MeshTree* out);
f32 ReadBufferedFloat(BufferedStream* in);
void ReadBufferedRotation3(BufferedStream* self, void* out);
void ReadBufferedVector3(BufferedStream* src, void* dst);
extern "C" void* CopyBytes(void* dst, const void* src, s32 n);
u16 ReadBufferedU16(BufferedStream* self);
s32 ReadBufferedS16(BufferedStream* in);
s32 ReadBufferedU32(BufferedStream* in);
// What class 0x03's slot 69 (func_001B9F30) writes of a collider.
extern "C" void SyncDataCache(s32 a);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
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
// The list walk of list_iter.h over a ObjectList: push the frame, take each element, pop the frame.
struct PooledContact;

extern "C" void* FillMemory(void* p, s32 value, s32 size);
// A script list being built (func_001C1530 hands one to a getter; func_001C1A28 appends a value
// of `type` to it).
#include "script_list.h"
extern "C" void* FillMemory(void* p, s32 value, s32 size);
s32 ReadBufferedU32(BufferedStream* self);
void* AllocateFrontMemory(u32 size);
// A type and a list of script values: func_001C1AD8 tells whether a value is among them.

s32 AppendPropertyToScriptList(ScriptListBuilder* self, void* value);


// The file's .data, in retail's order.
f32 g_colliderPositionGains[4] = { 0.0f, 3.0f, 0.0f, 0.0f };
f32 g_colliderRotationGains[4] = { 0.0f, 0.75f, 0.0f, 0.0f };
AnchorPreset g_anchorPresets[8] = {
    { &g_zeroVector, 0 },
    { &g_zeroVector, 3 },
    { &g_unitXVector, 2 },
    { &g_unitYVector, 2 },
    { &g_unitZVector, 2 },
    { &g_unitZVector, 1 },
    { &g_unitYVector, 1 },
    { &g_unitXVector, 1 },
};

// Set-up of a collider's own state: links its part list, clears and copies its mesh record, gives
// a child the free anchors (mode 3), marks its solver index and index unused (-1), sets flag bit
// 63 when its script scope defines variables 6 or 7, and takes the world's gravity.
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

// Adds a collider to its world: counts it, and for a body (no parent) adds it to the sweep axes,
// gives it a contact table and puts it on the world's body list. Also lists it as a part,
// refreshes the anchor-mode flags of its body and resolves its contact handler.
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

// Takes a collider out of the world: unlists it as a part, unregisters the placed object, and for
// a body without parent removes it from the sweep axes, frees its contact table and body list
// entry; frees its touch nodes and refreshes the anchor flags of its old root.
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

// Lists or unlists the collider among its root's parts (flag bit 50), clears the root's state
// bits and calls the root's method 0x32 when the flag changes.
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


// Applies the move and the spin queued in v490 and spin4A0 to the position and rotation (rotating
// by the axis-times-angle vector), clears them, settles the attachments and tells each child.
// Calls the class's slot 18 when anything moved and quiet is 0.
void ApplyColliderPendingMove(Collider* self, s32 quiet)
{
    Mat3 rot;
    Mat3 m;
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
    ListWalkSteps::Begin(&it, &self->children);
    for (PlacedObject* c = (PlacedObject*)ListWalkSteps::Next(&it); c != 0; c = (PlacedObject*)ListWalkSteps::Next(&it)) {
        if (c->desc->flags & 2) {
            c->desc02()->m2F(c, moved);
        }
    }
    if (moved && !quiet && self->desc->m12 != 0) {
        self->desc->m12(self);
    }
    ListWalkSteps::End(&it);
}

// Folds the queued v490 and spin4A0 into the velocity (v150) and the spin (v160) instead of the
// position and rotation, clears them, settles the attachments and passes whether anything changed
// to each child.
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
    ListWalkSteps::Begin(&it, &self->children);
    for (PlacedObject* c = (PlacedObject*)ListWalkSteps::Next(&it); c != 0; c = (PlacedObject*)ListWalkSteps::Next(&it)) {
        if (c->desc->flags & 2) {
            ((Collider*)c)->desc03()->m30((Collider*)c, moved);
        }
    }
    ListWalkSteps::End(&it);
}

extern f32 g_frameDt[];

// Like ApplyColliderPendingImpulse, but also advances the position and rotation by half a frame
// (g_frameDt * 0.5) of the queued change, so the integration is centred in the step; calls slot
// 18 when something moved and flag is 0.
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
        Vec4 delta;
        Mat3 turn;
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
    ListWalkSteps::Begin(&it, &self->children);
    PlacedObject* c;
    while ((c = (PlacedObject*)ListWalkSteps::Next(&it)) != 0) {
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
    ListWalkSteps::End(&it);
}

ASM_FUNC(func_001B8420);

ASM_FUNC(func_001B8540);

ASM_FUNC(func_001B8820);

// Computes the placed object's world frame and moves both of the collider's meshes into the world
// with it.
void ComputeColliderWorldFrame(Collider* self)
{
    ComputePlacedObjectWorldFrame(self);
    TransformMeshToWorld(&self->mesh, &self->meshCopy, *(Qword128*)&self->v140, &self->m110);
    TransformMeshToWorld(&self->mesh2, &self->mesh2Copy, *(Qword128*)&self->v140, &self->m110);
}

// Recomputes the placed object's frame, calls the root's method 0x32, clears its state bits and
// marks the sweep axes as unsorted.
void RecomputeColliderFrame(Collider* self)
{
    RecomputePlacedObjectFrame(self);
    self->root03()->desc03()->m32(self->root03());
    ClearRootObjectStateBits(self->world, self, 7);
    MarkSweepAxesUnsorted(self->world);
}

// Whether a and b may touch: only when a has flag 47 or 55 set and b has flag 55 set.
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

// For every contact of the collider whose timer is above 0.0001, calls the contact handler (slot
// 65 of the class) of the object at each end, if it has one, and clears the timer.
void NotifyContactHandlers(Collider* self)
{
    ContactRow03* node = self->contacts->head;
    while (node != 0) {
        BodyContact* it = node->head;
        while (it != 0) {
            if (0.0001f < it->timer) {
                for (s32 i = 0; i < 2; i++) {
                    Collider* obj = FindHandlerForSlot(it->end[i].part, 0x114);
                    if (obj != 0) {
                        void (*fn)(Collider*, BodyContact*, s32) = obj->desc03()->m41;
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

// Where the point p projects onto the line a to b, as a fraction of its length (0 at a, 1 at b).
f32 ComputeSegmentParameter(const Vec4* a, const Vec4* b, const Vec4* p)
{
    Vec4 ap;
    Vec4 ab;
    Vu0::Q(ap) = Vu0::Sub(Vu0::Q(*p), Vu0::Q(*a));
    Vu0::Q(ab) = Vu0::Sub(Vu0::Q(*b), Vu0::Q(*a));
    return Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(ap), Vu0::Q(ab))) / Vu0::ToFloat(Vu0::Dot(Vu0::Q(ab), Vu0::Q(ab)));
}

void CopyMemory(void* dst, void* src, u32 size);

// What Collider::hook points at for a mesh that blends per-vertex vectors (func_001B8B90): a
// vector for each vertex, and the three vertex indices of each face.
struct VertexBlend03 {
    Vec4* vectors;         // 0x00: one per vertex of the mesh copy, none to skip
    u8 pad04[0x08 - 0x04];
    s32 (*faceVerts)[3];    // 0x08: one triple per face
};

// For a contact on a mesh that moves per vertex (hook), works out which vertex, edge or face the
// contact touches, blends that feature's per-vertex vectors by barycentric weights and adds the
// result, brought into the world frame, to the contact end's velocity (v30).
void AddContactVertexBlendVelocity(Collider* self, BodyContact* c, s32 which)
{
    typedef Vu0::Vec Vec;
    if (self->hook == 0) {
        return;
    }
    s32 idx[3];
    f32 w[3];
    Vec4 sum;
    ContactEnd03* end = &c->end[which];
    s32 kind = 0;
    if (which == 0) {
        switch (c->kind) {
        case 1:
            kind = 1;
            idx[0] = (Vec4*)c->featureEnd0 - (Vec4*)self->meshCopy.verts;
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
            idx[0] = (Vec4*)c->featureEnd1 - (Vec4*)self->meshCopy.verts;
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
        Vec4* verts = (Vec4*)self->meshCopy.verts;
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
        Vec4* verts = (Vec4*)self->meshCopy.verts;
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


// Adds a force that pulls the collider's position toward target and one that pulls its velocity
// toward aim. Each uses a gain triple (c2*x + c1 + c0/x of the distance); the velocity pull is
// capped at 1/limit.
void SteerColliderTowardPosition(Collider* self, Vec4* target, f32* pull, Vec4* aim, f32* turn, f32 limit)
{
    Vec4 acc;
    Vec4 d;
    Vec4 k;
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


// Adds a torque that turns the collider toward the rotation target (the gain triple applied to
// the angle) and one that pulls its spin toward aim (the velocity-style gain capped at 1/limit).
void SteerColliderTowardRotation(Collider* self, Mat3* target, f32* pull, Vec4* aim, f32* turn, f32 limit)
{
    Vec4 acc;
    Vu0::Q(acc) = Vu0::Zero();
    if (pull != 0) {
        Mat3 m;
        Vec4 axis;
        Vec4 k;
        f32 angle;
        MultiplyMatrices3x3(&self->rot, target, &m);
        MatrixToAxisAngle(&m, &angle, &axis);
        if (0.0001f < angle) {
            Vu0::Q(k) = Vu0::FromFloat(pull[2] * angle * angle + pull[1] * angle + pull[0]);
            Vu0::Q(acc) = Vu0::MulX(Vu0::Q(axis), Vu0::Q(k));
        }
    }
    if (turn != 0) {
        Vec4 d;
        Vec4 k;
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

// Per-step work of a collider: for a body without parent and without flag 0x8000<<36 adds the
// gravity, limited by the anchor, as a force; then calls method 0x33 of each attached object with
// the time step.
void StepCollider(Collider* self, f32 t)
{
    Vec4U local;
    ColliderAttachment* node;
    u64 m = 0x8000;
    m <<= 36;
    if (self->parent == 0) {
        if ((self->flags538 & m) == 0) {
            ConstrainColliderVector(self, &self->v440, &self->gravity, &local, 0);
            AddColliderForce(self, (Vec4*)&local);
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

// Sets the mass to v and scales the inertia by the same ratio.
void SetColliderMass(Collider* self, f32 v)
{
    f32 a = self->mass;
    f32 q = v / a;
    self->mass = a * q;
    ComputeColliderInverseInertia(self, q);
}

// Scales the inertia matrix by scale and recomputes its inverse (zeros when it cannot be
// inverted).
void ComputeColliderInverseInertia(Collider* self, f32 scale)
{
    Mat3 m;
    Vec4 k;
    Mat3 s;
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

// Removes contacts from the collider's body: mode 1 those whose other end is the object or one of
// its descendants, mode 2 those at exactly the object, mode 3 only those of kind 8 or 9 at it;
// frees them, and clears field 0x4B8.
void DropColliderContacts(Collider* self, s32 mode)
{
    Collider* ctx = self->root03();
    if (ctx == 0) {
        return;
    }
    if (mode != 0) {
        BodyContact* freed = 0;
        for (ContactRow03* o = ctx->contacts->head; o != 0; o = o->next) {
            BodyContact** pp = &o->head;
            BodyContact* it;
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
    ctx->stateBits = 0;
}

// Copies the current position into the previous one (v370).
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
    Vec4 before;           // 0x10
    Vec4 q20;              // 0x20: not written by SetColliderPosition
};

// Moves the collider to a new position: snaps the camera when a camera-followed collider jumps
// more than 10 units, drops its contacts, refreshes its parts and sends event 3 with the previous
// position.
void SetColliderPosition(Collider* self, Vec4* pos)
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
                ((ColliderDescriptor*)part->desc)->m44(part);
            }
            part = (Collider*)part->link2E4.next;
        }
    }
    self->desc->m0E(self, 3, &note);
}

// Sets the rotation matrix; when the collider is in a world it calls method 0x12 and drops its
// contacts (mode 1), and in any case sends notification 4.
void SetColliderRotation(Collider* self, Mat3* src)
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

// Tries up to ten positions starting at start and moving by step each time: puts the collider
// there, updates the world's contacts and stops at the first position where none of its contacts
// is deeper than 2 units.
void PlaceColliderClearOfContacts(Collider* self, Vec4* start, Vec4* step)
{
    Vec4 pos = *start;
    s32 i = 9;
    do {
        self->desc02()->m1D(self, &pos);
        UpdateWorldContacts(self->world, 0);
        for (ContactRow03* node = self->contacts->head; node != 0; node = node->next) {
            for (BodyContact* c = node->head; c != 0; c = c->next) {
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

// Sets the velocity; when it differs from the old one by 2 or more in some axis, clears the
// root's state bits 2 (the body is no longer at rest).
void SetColliderVelocity(Collider* self, Vec4* v)
{
    SetPlacedObjectVelocity(self, v);
    Vec4 d;
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

// Sets the spin; when it differs from the old one by 0.02 or more in some axis, clears the root's
// state bits 2 (the body is no longer at rest).
void SetColliderSpin(Collider* self, Vec4* v)
{
    SetPlacedObjectSpin(self, v);
    Vec4 d;
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

// Sets the two anchors (mode and vector each, the vector left alone when null) and refreshes the
// root's anchor flags if flag 54 no longer says whether both modes are 3.
void SetColliderAnchors(Collider* self, s32 a1, Vec4* a2, s32 a3, Vec4* a4)
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

// Gives the collider a new parent while keeping its anchor vectors: they are taken to the world
// frame and back into the new parent's. Updates the anchor flags of the old and new bodies and
// resolves the contact handler.
void ReparentCollider(Collider* self, BaseObject* p)
{
    Vec4 local0;
    Vec4 local1;
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


// Reframes the placed object against frame and rotates both anchor vectors by the frame's
// rotation, keeping their modes.
void ReframeColliderAnchors(Collider* self, PlacedObject* frame)
{
    Vec4 a;
    Vec4 b;
    ReframePlacedObject(self, frame);
    Vu0::Q(a) = Vu0::Rotate(frame->rot, Vu0::Q(self->v440));
    Vu0::Q(b) = Vu0::Rotate(frame->rot, Vu0::Q(self->v460));
    SetColliderAnchors(self, self->mode450, &a, self->mode470, &b);
}

LINKER_REMNANT(func_001B9D08);


// Adds a torque that turns the collider toward the target rotation without overshooting, in the
// manner of a motor with a speed limit (gain[0]), a rate set by gain[1] and gain[2] and a braking
// zone; also brakes the spin when it is above the limit.
void TurnColliderTowardRotation(Collider* self, f32 dt, Mat3* target, f32* gain)
{
    Mat3 m;
    Vec4 axis;
    Vec4 want;
    Vec4 torque;
    Vec4 have;
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

// Writes a small pose record for the collider (position, velocity, a heading angle taken from its
// matrix, 100.0 and the game time).
void CaptureColliderPose(Collider* self, ColliderPose* out)
{
    Vec4 tmp[3];
    out->position = self->v140;
    out->dir = self->v150;
    RotateMatrixUpright(&self->m110, 0, (Mat3*)&tmp[0]);
    out->heading = ArctangentOfRatio(-tmp[0].y, -tmp[0].x);
    out->weight = 100.0f;
    out->flags = 0;
    out->stampTime = g_gameTime[0];
    out->f3C = 0;
}

// Whether there is a contact between a descendant of this collider and a descendant of other.
s32 IsContactBetweenParts(Collider* self, void* other)
{
    PlacedObject* key;
    BodyContact* n;
    for (n = (BodyContact*)GetContactRowHead(self, (Collider*)other), key = self->root; n != 0; n = n->next) {
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

// Walks the contacts of the collider's root and gives the object at the far end of the first one
// whose near end is the collider or one of its descendants; 0 if none.
void* FindContactingPart(Collider* self)
{
    Collider* s3 = self->root03();
    ContactRow03* s2 = s3->contacts->head;
    for (; s2 != 0; s2 = s2->next) {
        BodyContact* s0 = s2->head;
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

// Copies another collider's data into this one (CopyPlacedObject), keeping this one's own links,
// contact table, part list and handler; then copies the meshes and their plane trees and relists
// the part.
void CopyCollider(Collider* self, Collider* other)
{
    u64 bit = (self->flags538 >> 50) & 1;
    ObjectListLink a, c, d;
    ObjectList b;
    a = self->link2D0;
    b = self->parts;
    c = self->link2E4;
    BodyContactTable* s480 = self->contacts;
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
    self->stateBits = 0;
    self->flags538 = (self->flags538 & 0xFFFBFFFFFFFFFFFFULL) | (bit << 50);
    SetColliderPartListed(self, 1);
    if (self->meshCopy.vertCount) CopyMeshTransformed(&other->meshCopy, 0, &self->meshCopy);
    if (self->tree.nodes) CloneTreeNodes(&other->meshCopy, &other->tree, &self->meshCopy, &self->tree);
    if (self->mesh2Copy.vertCount) CopyMeshTransformed(&other->mesh2Copy, 0, &self->mesh2Copy);
    if ((s32)self->flags538) CloneTreeNodes(&other->mesh2Copy, &other->tree2, &self->mesh2Copy, &self->tree2);
    self->touching = 0;
    self->flags538 |= 0x20000000000ULL;
}

// Restricts a vector by an anchor constraint (kind 0 none, 1 removes the part along the axis, 2
// keeps only that part, 3 zero); the axis is rotated by the parent's frame when there is a
// parent. Writes the result to out and what was taken off to rem.
void ConstrainVectorByParentAnchor(Collider* self, VectorConstraint* c, Vec4* in, Vec4* out, Vec4* rem)
{
    Vec4 axis;
    Vec4 tmp;
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
        Vec4* a;
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
        Vec4* a;
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

// Limits the vector in by the anchor's kind: 0 keeps it, 1 removes its part along the axis, 2
// keeps only that part, 3 gives zero. The result goes in out (or a scratch vector) and what was
// removed in rem if given.
void ConstrainVectorByAnchor(VectorConstraint* c, Vec4* in, Vec4* out, Vec4* rem)
{
    Vec4 tmp;
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

// Calls ConstrainVectorByAnchor with the arguments passed as untyped pointers (rem as a number),
// for the class tables.
void ConstrainColliderVector(void* self, void* a, void* b, void* c, s32 d)
{
    ConstrainVectorByAnchor((VectorConstraint*)a, (Vec4*)b, (Vec4*)c, (Vec4*)(s32)d);
}

// Puts the node at the head of the collider's attached list and resets the root's tries.
void AddColliderAttachment(Collider* self, ColliderAttachment* node)
{
    node->next = self->attached;
    self->attached = node;
    ClearRootTries(self);
}

// Removes the node from the collider's attached list, if it is on it, and resets the root's
// tries.
void RemoveColliderAttachment(Collider* o, ColliderAttachment* node)
{
    ColliderAttachment** link = &o->attached;
    if (*link == 0) {
        goto tail;
    }
    if (o->attached == node) {
        o->attached = node->next;
    } else {
        ColliderAttachment* prev;
        for (;;) {
            prev = *link;
            ColliderAttachment* nx = prev->next;
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

struct Oscillator;
extern "C" f32 Arccosine(f32 x);

struct OscillatorHolder { u8 pad00[0xC]; void* oscillator; };
struct SoundHoldingObject { u8 pad00[0x574]; PlayingSound* sound; };

// The rows of m, each turned by r, returned by value (g++'s named return value): each row goes
// to the result as soon as it is made.
static inline Mat3 RotateRowsBy(const Mat3& r, const Mat3& m) return out
{
    Mat3 t;
    Vu0::Q(t.r[0]) = Vu0::RotateUntied(r, Vu0::Vec::Of(m.r[0])).q;
    out.r[0] = t.r[0];
    Vu0::Q(t.r[1]) = Vu0::RotateUntied(r, Vu0::Vec::Of(m.r[1])).q;
    out.r[1] = t.r[1];
    Vu0::Q(t.r[2]) = Vu0::RotateUntied(r, Vu0::Vec::Of(m.r[2])).q;
    out.r[2] = t.r[2];
}

// Reacts to a collider touching an attached set: measures the penetration depth, then adds a push
// against gravity, drag-like pulls of the position and spin toward the set's own motion, a torque
// that tilts the collider onto the surface normal, and spawns surface contact effects or stops
// its sound.
void ApplyColliderAttachedSetContact(Collider* self, AttachedSet* other, f32 dt)
{
    Vec4 hit;
    Vec4 hitVel;
    Vec4 force;
    Vec4 spin;
    Vec4 point;
    Vec4 normal;
    f32 gains[3];
    f32 depth = MeasureAttachedSetContactDepth(other, (TurningCollider*)self, &point, &normal);
    if (depth < 0.0001f) {
        return;
    }
    if (other->oscillatorBlock != 0) {
        Vec4 axes[3];  // the oscillator reads three offsets: the pair and the normal itself
        axes[2] = normal;
        BuildPerpendicularPair(&axes[2], &axes[0], &g_unitXVector, &g_unitZVector);
        ComputeOscillatorDisplacement((Oscillator*)(((OscillatorHolder*)other->oscillatorBlock)->oscillator), 50.0f, &point, &axes[0], 0, &axes[0], 0);
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
        Vec4 along;
        Vec4 rest;
        Vec4 target;
        Vec4 target2;
        Vec4 spinAlong;
        Vec4 spinRest;
        Vec4 target3;
        Vec4 target4;
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
        Vu0::Q(spin) = Vu0::Sub(Vu0::Q(g_zeroVector), Vu0::Q(self->v160));
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
        Mat3 m = self->m1A0;
        Mat3 r;
        Vec4 axis;
        Vec4 torque;
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
        StopSoundRecord(((SoundHoldingObject*)self)->sound, 0);
    }
}

// Empty: this collider takes no part in an attachment's step.
void IgnoreColliderAttachmentStep(Collider* self, ColliderAttachment* node, f32 dt)
{
}

// Reads a collider from a stream: the mesh and its face tree, mass, inertia, offset, the groups
// and face references, a second mesh with its tree, then the placed object's own part; lists it
// as a part and, for a body, adds its contact pair flags.
void LoadCollider(Collider* self, BufferedStream* in)
{
    s32 i;
    s32 j;
    s32 n;
    CollisionRefPair* e;
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
    self->groups = (CollisionRefPair*)AllocateFrontMemory(self->groupCount << 3);
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
    self->refs = (CollisionRefPair*)AllocateFrontMemory(self->refCount << 3);
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

// Sets the bounding radius and flag 0x8000<<25 which makes it count.
void SetColliderOverrideRadius(Collider* self, f32 v)
{
    self->flags538 |= (u64)0x8000 << 25;
    self->radius3CC = v;
}

// Gives both anchors mode 3 and leaves their vectors.
void ResetColliderAnchors(void* self)
{
    SetColliderAnchors((Collider*)self, 3, 0, 3, 0);
}

// Gives the mode and the vector of anchor preset index (a table of eight).
void GetAnchorPreset(s32 index, s32* out, Vec4* dst)
{
    *out = g_anchorPresets[index].value;
    *dst = *g_anchorPresets[index].quad;
}

// Takes preset index for the turn anchor (the first one): its mode and its vector rotated by the
// collider's rotation; the move anchor stays.
void SetColliderTurnAnchorPreset(Collider* self, s32 index)
{
    Vec4 v;
    Vec4 local;
    s32 mode;
    GetAnchorPreset(index, &mode, &local);
    Vu0::Q(v) = Vu0::Rotate(self->rot, Vu0::Q(local));
    SetColliderAnchors(self, mode, &v, self->mode470, &self->v460);
}

// Takes preset index for the move anchor (the second one): its mode and its vector rotated by the
// collider's rotation; the turn anchor stays.
void SetColliderMoveAnchorPreset(Collider* self, s32 index)
{
    Vec4 v;
    Vec4 local;
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

// Sends the notification to the collider and then to the notification method of every other
// object attached to it.
void SendColliderNotification(Collider* self, s32 kind, void* arg)
{
    SendObjectNotification(self, kind, arg);
    ColliderAttachment* n = self->attached;
    if (n != 0) {
        do {
            ColliderAttachment* next = n->next;
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

// Gives back the contact of the collider (optionally only with the object key) that best looks
// like ground: its normal's z component is above 0.7 (or below -0.7 at the other end) and its
// float at +0x18 of the end is the smallest; out gets which end.
void* FindColliderFloorContact(void* self, s32 key, s32* out)
{
    ContactRow03* n = ((Collider*)self)->contacts->head;
    BodyContact* bestIt = 0;
    s32 bestSel = 0;
    f32 bestF = 3.4028235e38f;
    while (n) {
        ContactRow03* nxt = n->next;
        for (BodyContact* it = n->head; it; it = it->next) {
            s32 sel = (u32)it->end[0].body != (u32)self;
            if (key != 0) {
                if ((s32)it->end[sel].part != key) {
                    continue;
                }
            }
            f32 f0 = it->normal.z;
            if (!(sel == 0 ? 0.7f < f0 : f0 < -0.7f)) {
                continue;
            }
            f0 = it->end[sel].point.z;
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

// Sets flag 42 and drops the contacts of the object and its descendants (mode 1) when set.
void SetColliderTreeContactsDropped(Collider* self, s32 value)
{
    u64 bit = (u64)(value & 1) << 42;
    self->flags538 = (self->flags538 & ~(1ULL << 42)) | bit;
    DropColliderContacts(self, value != 0);
}

// Sets flag 43 and drops the contacts at exactly this object (mode 2) when set.
void SetColliderContactsDropped(Collider* self, s32 value)
{
    u64 bit = (u64)(value & 1) << 43;
    self->flags538 = (self->flags538 & ~(1ULL << 43)) | bit;
    DropColliderContacts(self, value != 0 ? 2 : 0);
}

// Sets flag 44 and drops the contacts of kind 8 or 9 at this object (mode 3) when set.
void SetColliderKindContactsDropped(Collider* self, s32 value)
{
    u64 bit = (u64)(value & 1) << 44;
    self->flags538 = (self->flags538 & ~(1ULL << 44)) | bit;
    DropColliderContacts(self, value != 0 ? 3 : 0);
}

// Works out which collider handles this one's contacts: itself when its class has handler methods
// (0x3C, 0x3D, 0x3E or 0x41), otherwise its parent's handler (none without parent); then does the
// same for the children that are colliders.
void ResolveContactHandler(Collider* self)
{
    ListFrame frame;
    const ColliderDescriptor* info = self->desc03();
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

// Walks from node through each handler and its parent until one whose class has a method at
// offset in its table, and gives that handler; 0 if none.
Collider* FindHandlerForSlot(Collider* node, s32 offset)
{
    Collider* s;
    while (node != 0 && (s = node->handler) != 0) {
        if (*(s32*)((u8*)s->desc + offset) != 0) return s;
        node = (Collider*)s->parent;
    }
    return 0;
}

// Recomputes the anchor flags of a collider and, recursively, of its children: bit 54 when both
// anchor modes are 3, bit 56 when that holds up to the body, bit 55 when it holds for it and all
// of its children. Refreshes the pair flags of a body when bit 55 changes.
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

// Adds to a script list each object touching this collider (without repeats); gives 1 when all
// fit and 0 when appending fails.
s32 CollectContactingPartsToScriptList(Collider* self, void* value)
{
    Collider* ctx = self->root03();
    ContactRow03* n = ctx->contacts->head;
    while (n != 0) {
        BodyContact* e = n->head;
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

// Gives back the count and an array (back memory) of the distinct objects in contact with this
// collider or its descendants.
s32 CollectContactingParts(Collider* obj, s32* outCount, void*** outArr)
{
    Collider* own = obj->root03();
    ContactRow03* nd;
    BodyContact* it;
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
        for (BodyContact* it2 = nd->head; it2; it2 = it2->next) {
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

// Whether value is on the touching list.
s32 IsInTouchingList(TouchedObjectLink* node, Collider* value)
{
    while (node != 0) {
        if (node->obj == value) return 1;
        node = node->next;
    }
    return 0;
}

// Compares the collider's touching list with the contacts it has now and sends script events: 6
// for each object newly touching, 7 for each one no longer touching; then rebuilds the touching
// list from the contacts.
void UpdateTouchingParts(Collider* self)
{
    Collider* core = self->root03();
    ContactRow03* o;
    BodyContact* e;
    TouchedObjectLink* m;
    TouchedObjectLink* prev;
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
                TouchedObjectLink* n = AllocateTouchNode(self->world);
                n->obj = other;
                if (self->touching != 0) prev->next = n; else self->touching = n;
                prev = n;
            }
        }
    }
}

// Always 0: a plain collider does not take the offer of a launch.
s32 RequestColliderLaunch(Collider* self, void* source, TrackedNodeOffer* offer)
{
    return 0;
}


struct MeshMotion {
    Vec4* velocity;
    Vec4* accel;
    struct Tri { s32 i[3]; } *tris;
};



void* AllocateZeroedBackMemory(s32 size);

// Builds the collider's hook: two zeroed vectors per vertex, and the three vertex indices of
// each face gathered from the edges that bound it, then wound to face along the face's
// normal.
void InitColliderMeshMotion(Collider* self)
{
    Vec4 e1;
    Vec4 e2;
    Vec4 n;
    if (self->hook != 0) {
        return;
    }
    PushBackMemoryMark();
    MeshMotion* h = (MeshMotion*)AllocateFrontMemory(0xC);
    self->hook = h;
    h->velocity = (Vec4*)AllocateZeroedFrontMemory(self->meshCopy.vertCount * 16);
    h->accel = (Vec4*)AllocateZeroedFrontMemory(self->meshCopy.vertCount * 16);
    h->tris = (MeshMotion::Tri*)AllocateZeroedFrontMemory(self->meshCopy.faceCount * 12);
    s32* counts = (s32*)AllocateZeroedBackMemory(self->meshCopy.faceCount * 4);
    MeshMotion::Tri* tri;
    s32 f;
    for (s32 i = 0; i < self->meshCopy.edgeCount; i++) {
        MeshEdge* e = &((MeshEdge*)self->meshCopy.edges)[i];
        for (s32 j = 0; j < 2; j++) {
            f = e->face[j];
            tri = &h->tris[f];
            for (s32 k = 0; k < 2; k++) {
                s32 v = e->v[k];
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
    Vec4* verts = (Vec4*)self->mesh.verts;
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

// Moves the vertices of a collider whose mesh deforms (hook): each vertex advances by its
// velocity and acceleration over dt, the velocity by the acceleration; then recomputes the radius
// and every face's normal and plane distance.
void AdvanceColliderMeshMotion(Collider* self, f32 dt)
{
    Vec4 a, b;
    Vec4* pts = (Vec4*)self->mesh.verts;
    Vec4* vel = ((MeshMotion*)self->hook)->velocity;
    Vec4* acc = ((MeshMotion*)self->hook)->accel;
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

// Advances the mesh motion when the collider has a hook, then moves the placed object by x.
void MoveCollider(Collider* self, f32 x, s32 flag)
{
    if (self->hook != 0) {
        AdvanceColliderMeshMotion(self, x);
    }
    MovePlacedObject(self, x, flag);
}


// Applies an impulse event to the collider: builds a contact at origin pushing along the
// direction from the object's velocity toward target, solves it for the collider's body
// (SolveColliderGroupContacts) and frees it.
void ApplyColliderImpulseEvent(void* a0, f32 value, void* a1, void* a2)
{
    Collider* self = (Collider*)a0;
    Vec4* origin = (Vec4*)a1;
    Vec4* target = (Vec4*)a2;
    Vec4 vel;
    Vec4 dir;
    BodyContact* contact;
    Collider* group[1];
    ComputeObjectMotionInFrame(self, 0, origin, &vel, 0, 0, 0);
    Vu0::Set(dir, Vu0::NormalizeOr(Vu0::Sub(Vu0::Q(*target), Vu0::Q(vel)), Vu0::Q(g_unitZVector)));
    f32 zero = 0.0f;
    contact = 0;
    CreatePooledContact(self, 0, origin, &dir, zero, 0xC, 0, 0, &contact);
    *(Vec4*)((u8*)&contact->end[1] + 0x30) = *target;
    contact->bounce = zero;
    contact->friction = 1.0f;
    *(f32*)&contact->featureEnd0 = value;
    NotifyContactEnds(self->world, 1, &contact);
    group[0] = (Collider*)self->root;
    SolveColliderGroupContacts(self->world, 1, group, 1, &contact, zero, 2);
    FreePooledContactChain(self->world, contact);
}


// Works out the velocity that takes the collider from where it is to the point p, rising a above
// the higher of the two heights under its own gravity: z from the height to climb, x and y from
// the horizontal distance over the flight time.
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

// Applies an impulse from the event when its flag 8 is set (position and direction at 0x20 and
// 0x30); gives whether the event had any flags.
s32 HandleObjectEvent(Collider* self, ObjectEvent* shape)
{
    if (shape->eventFlags & 0x8) {
        ApplyColliderImpulseEvent(self, shape->radius, &shape->pos, &shape->v30);
    }
    return shape->eventFlags != 0;
}

// Rebuilds this collider's meshes from another's, transformed by its position and rotation (with
// extra vertices), copies the face trees and sets up the per-vertex motion.
void CopyColliderMeshesInFrame(Collider* self, Collider* src, s32 extra)
{
    Vec4 m[4];
    CollisionMesh tmp;
    BuildMatrixFromRotationAndTranslation(&src->pos, &src->rot, (Mat4A*)m);
    f32 maxDist = 0.0f;
    for (s32 i = 0; i < src->mesh.vertCount; i++) {
        f32 d = Vu0::ToFloat(Vu0::Dot(Vu0::Q(((Vec4*)src->mesh.verts)[i]), Vu0::Q(((Vec4*)src->mesh.verts)[i])));
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
    self->stateBits = 0;
    CloneTreeNodes(&src->meshCopy, &src->tree, &self->meshCopy, &self->tree);
    CloneTreeNodes(&src->mesh2Copy, &src->tree2, &self->mesh2Copy, &self->tree2);
    InitColliderMeshMotion(self);
}

// For a body, goes through its contacts: those whose other part (or its nearest ancestor with a
// partMode) has mode 1 are copied to *out, mode 4 moved to *out, mode 3 freed.
void ExtractContactsByPartMode(Collider* self, BodyContact** out)
{
    BodyContact* freed = 0;
    if (self->root == self) {
        ContactRow03* h = self->contacts->head;
        if (h) {
            do {
                BodyContact** pp = (BodyContact**)h;
                BodyContact* n;
                while ((n = *pp) != 0) {
                    int k = (n->end[0].body != self);
                    Collider* e = n->end[1 - k].part;
                    while (e && !e->partMode) e = (Collider*)e->parent;
                    if (e) {
                        switch (e->partMode) {
                        case 1: {
                            BodyContact* c = (BodyContact*)TakePoolSlot(&self->world->pool1AFC);
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

// Whether the point lies inside the collider: within the bounding radius when flag 0x8000<<25 is
// set, or inside its plane tree.
s32 IsPointInsideCollider(Collider* self, Vec4* p)
{
    if ((self->flags538 & ((u64)0x8000 << 25)) != 0) {
        s32 inside = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(*p), Vu0::Q(self->v140)))) < self->radius3CC;
        if (inside) {
            return 1;
        }
    }
    if (self->tree.nodes != 0 && FindPlaneTreeNodeForPoint((Vec4*)p, self->tree.nodes) != 0) {
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

// Gives the collider the next index, enters it in list and does the same for its collider
// children (class flag 2), in order.
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
    Vec4 linear;           // 0x00
    Vec4 angular;          // 0x10
};


// For one end of a contact, fills the rows (indexed by part) with the change of velocity and spin
// the unit impulse along the contact makes on that part and each of its ancestors, up to a rigid
// one, honouring each part's anchor constraints.
void ComputeColliderImpulseResponse(void* self, s32 a1, BodyContact* c, s32 idx, ContactEnd03* hit, ImpulseRow* rows)
{
    Vec4 dir;
    Vec4 v;
    Vec4 arm;
    Vec4 k;
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


// For each part below the root, adds to its impulse row the motion it gets from its parent's row
// (the point velocity at the part's position and the parent's spin), honouring the anchor
// constraints and the part's offset.
void AddParentVelocityToChildRows(void* unusedA, void* unusedB, s32 n, Collider** list, ImpulseRow* rows)
{
    Vec4 vel;
    Vec4 ang;
    Vec4 loc;
    Vec4 axis;
    Vec4 rn;
    Vec4 ro;
    Vec4 t;
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
                const u128& fb = Vu0::Q(g_zeroVector);
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

// A BodyContact with the fields the group solve reads and writes.
struct GroupSolveContact {
    ContactEnd03 end[2];            // 0x00
    Vec4 normal;                   // 0x80
    f32 depth;                      // 0x90
    u8 pad94[0x98 - 0x94];
    f32 bounce;                     // 0x98
    s32 kind;                       // 0x9C
    f32 limit;                      // 0xA0
    u8 padA4[0xB0 - 0xA4];
    Vec4 relVel;                   // 0xB0
    f32 push;                       // 0xC0
    f32 impulse;                    // 0xC4
    f32 speed;                      // 0xC8
    s32 index;                      // 0xCC
};
struct GroupSolveHandler;
struct GroupSolveHandlerClass { u8 pad00[0x108]; void (*m108)(GroupSolveHandler* self, s32 kind, ActiveSetItem* it, s32 end, f32 dt); };
struct GroupSolveHandler { GroupSolveHandlerClass* desc; };

void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateBackMemory(s32 size);
extern "C" void* FillMemory(void* p, s32 value, s32 size);

// Solves a group of contacts for a set of parts with the active-set solver (InitActiveSetSolver,
// RunActiveSetSolver). flags: 4 is a position-correction pass (depths), 1 a solve for the half-step
// integration (slot 49 of the parts) that stores each contact's push, 2 a velocity solve (slot 48)
// that stores each contact's impulse; passes nothing needs are dropped first. Friction is added.
void SolveColliderGroupContacts(World* world, s32 nParts, Collider** parts, s32 n, BodyContact** list, f32 dt, s32 flags)
{
    GroupSolveContact** contacts = (GroupSolveContact**)list;
    ActiveSetSolver loc;
    s32 i;
    if (flags & 1) {
        if (n == 0) {
            return;
        }
    } else {
        if (flags & 4) {
            for (i = 0; i < n; i++) {
                GroupSolveContact* c = contacts[i];
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
                    GroupSolveContact* c = contacts[i];
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
        GroupSolveContact* c = contacts[i];
        ActiveSetItem* it = (ActiveSetItem*)(loc.items + i * 0x60);
        it->owner = c;
        *(Vec4*)it->axis = c->normal;
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
            GroupSolveContact* c = contacts[j];
            if (it->kind == 2) {
                it->val = c->depth;
            } else {
                it->val = c->depth + 1.0f;
            }
            for (s32 e = 0; e < 2; e++) {
                GroupSolveHandler* h = (GroupSolveHandler*)FindHandlerForSlot(c->end[e].part, 0x108);
                if (h != 0 && h->desc->m108 != 0) {
                    h->desc->m108(h, 0xC, it, e, dt);
                }
            }
        }
        RunActiveSetSolver(&loc, 4, n, (BodyContact**)contacts, counts, lists);
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
        RefreshContactEndPoints(world, n, (BodyContact**)contacts);
        NotifyContactEnds(world, n, list);
        for (s32 j = 0; j < n; j++) {
            ActiveSetItem* it = (ActiveSetItem*)(loc.items + j * 0x60);
            GroupSolveContact* c = contacts[j];
            Vu0::StoreX(it->val, Vu0::Dot(Vu0::Q(c->relVel), Vu0::Q(c->normal)));
            for (s32 e = 0; e < 2; e++) {
                GroupSolveHandler* h = (GroupSolveHandler*)FindHandlerForSlot(c->end[e].part, 0x108);
                if (h != 0 && h->desc->m108 != 0) {
                    h->desc->m108(h, 9, it, e, dt);
                }
            }
        }
    } else {
        for (s32 j = flags & 1; j < n; j++) {
            GroupSolveContact* c = contacts[j];
            ActiveSetItem* it = (ActiveSetItem*)(loc.items + j * 0x60);
            Vu0::StoreX(c->speed, Vu0::Dot(Vu0::Q(c->relVel), Vu0::Q(c->normal)));
            f32 r = RandomFloatInRange(0.9f, 1.1f);
            it->val = c->speed * (c->bounce * r + 1.0f);
            for (s32 e = 0; e < 2; e++) {
                GroupSolveHandler* h = (GroupSolveHandler*)FindHandlerForSlot(c->end[e].part, 0x108);
                if (h != 0 && h->desc->m108 != 0) {
                    h->desc->m108(h, 10, it, e, dt);
                }
            }
        }
    }
    AddFrictionItemsAndSolve(&loc, flags & ~4, n, (BodyContact**)contacts, counts, lists, dt);
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

// Gathers up to cap contacts of the given bodies (their loose ones, then those of each contact
// row whose other body is not already marked) into out, marking and unmarking the bodies with
// flag bit 58; gives the count.
s32 CollectGroupItems(s32 count, Collider** roots, s32 cap, BodyContact** out)
{
    s32 n = 0;
    s32 i;
    Collider* root;
    for (i = 0; i < count; i++) {
        root = roots[i];
        root->flags538 |= ((u64)1 << 58);
        for (BodyContact* item = root->contacts4B4; item; item = item->next) {
            if (n >= cap) goto done;
            out[n++] = item;
        }
        BodyContactTable* gh = root->contacts;
        for (ContactRow03* g = gh->head; g; g = g->next) {
            if (g->other->flags538 & ((u64)1 << 58)) continue;
            for (BodyContact* item = g->head; item; item = item->next) {
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

// Starting from one collider, follows its contact rows to find the bodies connected to it. Bodies
// with flag 55 go to the second list, others to the queue; gives both counts.
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

// Mode 1 makes the collider look rigid for a solve (anchor modes forced to 3, flags 54 and 55
// set), saving the old values; mode 0 restores them.
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

// Sorts the colliders by how many of their rows have contacts (0 to 3, capped at 4) with a
// counting sort, stable, in place.
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

// Solves one connected group. When it has fewer than 64 contacts (or fewer than 2 bodies) it is
// solved directly; otherwise the group is sorted, split in halves, the second half solved with
// the first marked and then the first with the second forced rigid.
void ProcessColliderGroup(World* ctx, s32 n, Collider** arr, f32 f, s32 ex)
{
    BodyContact* buf[0x40];
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
        ListWalkSteps::Begin(&it, &arr[i]->parts);
        for (p = ListWalkSteps::Next(&it); p; p = ListWalkSteps::Next(&it)) {
            SetColliderForcedState((Collider*)p, 1);
        }
        ListWalkSteps::End(&it);
    }
    ProcessColliderGroup(ctx, half, arr, f, ex);
    for (i = half; i < n; i++) {
        ListWalkSteps::Begin(&it, &arr[i]->parts);
        for (p = ListWalkSteps::Next(&it); p; p = ListWalkSteps::Next(&it)) {
            SetColliderForcedState((Collider*)p, 0);
        }
        ListWalkSteps::End(&it);
    }
}

// Per frame, for each group of connected colliders in the world: when flags has bit 0, steps
// (slot 27) the colliders that have not settled, then solves the group (ProcessColliderGroup) and
// clears the retry count of those not at rest.
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
            if (!IsObjectTreeAtRest((UpdatedObject*)arr1[i])) {
                ClearRootTries(arr1[i]);
            }
        }
    }
    for (s = (Collider*)self->bodies.head; s != 0; s = (Collider*)s->link2D0.next) {
        s->flags538 &= ~(1ULL << 57);
    }
    PopBackMemoryMark();
}

// Swaps two records of stride bytes at rows rowA and rowB of a table, word by word (the swap the
// sort uses).
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

// Heap sort of n records of size bytes (a multiple of 4) in place, ordered by cmp; called with
// other files' tables.
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