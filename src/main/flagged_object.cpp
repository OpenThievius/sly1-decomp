// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_functions.h"
#include "asm_func.h"
#include "list_iter.h"
#include "flagged_object.h"
#include "transform_object.h"
#include "object_gatherer.h"
#include "world.h"
#include "object_event.h"
#include "screen_fade.h"
#include "flag_table.h"
#include "vu0.h"
#include "object_finder.h"
#include "list_walk.h"
#include "functions/base_object.h"
#include "functions/buffered_stream.h"
#include "functions/collider.h"
#include "functions/flagged_object.h"
#include "functions/on_off_object.h"
#include "functions/oscillator.h"
#include "functions/pad_input.h"
#include "functions/placed_object.h"
#include "functions/pooled_object.h"
#include "functions/pose_source.h"
#include "functions/state_walker.h"
#include "functions/warp_menu.h"
struct BaseObject;
struct TransformObject;
struct Vec4;


// Types other files define, named by the parameters of their functions declared here.
struct ObjectLink;
struct AnimationPlayer;

// The file's .rodata: the FLT_MAX literal of ResetFlagTable (func_00140D90), then the literal of
// UpdateFlaggedObject (func_00141690).

// The file's .data, in retail's order: the loader's link table of class 0x38, then the flag
// table (its bitmap and the snapshot func_00140E10 saves, 0x430 bytes in two labels).
u32 g_flaggedObjectLinks[4] = { 2, 0x545, 0x5A8, 0 };
u8 g_flagTable[528] = {0};
u8 g_flagTableSaved[544] = {0};

extern "C" void* FillMemory(void* p, s32 value, s32 size);

// Clears the flag table: no live or saved flags, the index counter at 0, the point set to a
// huge value and no fade recorded.
void ResetFlagTable(FlagTable* r)
{
    r->nextIndex = 0;
    r->live.count = 0;
    FillMemory(r->live.bits, 0, sizeof(r->live.bits));
    r->changed = 0;
    Vu0::Q(r->point) = Vu0::FromFloats(3.4028235e+38f, 3.4028235e+38f, 3.4028235e+38f);
    FillMemory(&r->saved, 0, 0x20C);
    r->hasFade = 0;
    r->fadeA = -1;
    r->fadeB = -1;
}

// Saves a copy of the live flags (clearing the changed mark) together with the two fade values
// a and b, to be restored later by RestoreFlagTableSnapshot.
void SaveFlagTableSnapshot(FlagTable* r, s32 a, s32 b)
{
    r->changed = 0;
    r->saved = r->live;
    r->fadeA = a;
    r->fadeB = b;
    r->hasFade = 1;
}


// Starts a screen fade, using the fade values the table saved (flags 0x11) or none (flags
// 0x10).
void StartScreenFadeFromFlagTable(FlagTable* r)
{
    FadeRequest args;
    args.kind = 1;
    args.key = &D_00275B04;
    if (r->hasFade != 0) {
        args.f08 = r->fadeA;
        args.f0C = r->fadeB;
        args.flags = 0x11;
    } else {
        args.f08 = -1;
        args.f0C = -1;
        args.flags = 0x10;
    }
    StartScreenFade(&g_screenFade, &args, 1);
}

// Puts the saved flags back as the live ones and clears the changed mark and the index counter.
void RestoreFlagTableSnapshot(FlagTable* p)
{
    p->nextIndex = 0;
    p->live = p->saved;
    p->changed = 0;
}

// Gives the next free flag index of the table (counting from 1).
s32 TakeFlagTableIndex(FlagTable* c)
{
    c->nextIndex = c->nextIndex + 1;
    return c->nextIndex;
}

// Whether the flag with this index is set in the table's live flags.
s32 TestFlagTableBit(FlagTable* table, s32 index)
{
    u8* bits = (u8*)table;
    s32 mask = 1 << (index & 7);
    bits += index / 8;
    return (bits[0xC] & mask) != 0;
}

// Sets one flag of the table, raising the live count and marking the table changed when it was
// clear.
void SetFlagTableBit(FlagTable* self, s32 bit)
{
    u8* base = self->live.bits;
    u8* byte = base + bit / 8;
    s32 mask = 1 << (bit & 7);
    s32 cur = *byte & mask;
    if (cur == 0) {
        self->changed = 1;
        goto done;
    }
done:
    if (!(*byte & mask)) {
        *byte = (u8)(*byte | mask);
        self->live.count++;
    }
}

// Clears one flag of the table, lowering the live count and marking the table changed when it
// was set.
void ClearFlagTableBit(FlagTable* self, s32 bit)
{
    u8* base = self->live.bits;
    u8* byte = base + bit / 8;
    s32 mask = 1 << (bit & 7);
    s32 cur = *byte & mask;
    if (cur != 0) {
        self->changed = 1;
        goto done;
    }
done:
    if ((*byte & mask) != 0) {
        *byte = (u8)(*byte & ~mask);
        self->live.count--;
    }
}

struct BufferedStream;

// Reads an object's rotation (at +0x50), position (+0x40), four mesh tables (+0x80 to +0x8C)
// and its property records from the stream.
void ReadObjectTransformAndTables(MeshObject* self, BufferedStream* stream)
{
    ReadBufferedRotation3(stream, &self->rot);
    ReadBufferedVector3(stream, &self->pos);
    ReadMeshTables(stream, &self->pointCount, &self->points, &self->linkCount, &self->links);
    ReadPropertyRecords(self, stream);
}

struct __attribute__((aligned(16))) Quad_00141170 { f32 v[4]; };

// Whether a point lies inside the object's shape: converts it to the object's frame and tests
// it against the face tree.
s32 TestPointAgainstObjectShape(ObjectGatherer* self, void* value)
{
    Quad_00141170 local;
    ConvertPointIntoObjectFrame((TransformObject*)self, (Vec4*)value, (Vec4*)&local);
    return IsPointInsideFaceTree((TreeNode03*)self->f8C, (FacePoint*)&local);
}


// Initialises the collider, gives it a flag-table index and the next ordinal of the world's
// count at +0x2304, no child id and anchors of 3.
void InitFlaggedObject(FlaggedObject* self)
{
    InitCollider(self);
    self->flagIndex = TakeFlagTableIndex((FlagTable*)g_flagTable);
    self->childId = -1;
    World* in = self->world;
    s32 n = in->count2304;
    self->ordinal = n;
    n = n + 1;
    in->count2304 = n;
    SetColliderAnchors(self, 3, 0, 3, 0);
}



// Loads the flagged object (as a collider), resolves its links, and sorts its children into two
// lists: those of kind 0x7B into the B list and those of kind 0x83 into the A list, each resolved
// and started.
void CollectChildLists(FlaggedObject* self, BufferedStream* stream)
{
    LoadCollider(self, stream);
    ResolveObjectLinks(self, 1, (ObjectLink*)g_flaggedObjectLinks);

    ScopedListFrame frame(&self->children);
    // a field access here changes retail's code
    void* head = *(void**)((u8*)self + 0x34);
    frame.cursor = (void*)((s32)head + frame.next_off);
    void* node = head;
    if (node != 0) {
        do {
            if (IsObjectOfKind((BaseObject*)node, 0x7B)) {
                s32 n = self->countB;
                self->objsB[n] = node;
                self->countB = n + 1;
            } else {
                if (!IsObjectOfKind((BaseObject*)node, 0x83)) {
                    goto skip;
                }
                s32 n = self->countA;
                self->objsA[n] = node;
                self->countA = n + 1;
            }
            ResolveAndStartObject((BaseObject*)node);
skip:
            void* next = *(void**)frame.cursor;
            frame.cursor = (void*)((s32)next + frame.next_off);
            node = next;
        } while (node != 0);
    }
}


// After loading, appends to the A list and the B list the objects found by the ids stored for
// each (those that exist).
void ResolveListIds(FlaggedObject* self)
{
    PostLoadPlacedObject(self);
    s32 i = 0;
    while (i < self->nIdsA) {
        void* r = FindFirstObjectByIdMode4(self->world, self->idsA[i], self);
        if (r != 0) {
            s32 k = self->countA;
            self->objsA[k] = r;
            self->countA = k + 1;
        }
        i++;
    }
    i = 0;
    while (i < self->nIdsB) {
        void* r = FindFirstObjectByIdMode4(self->world, self->idsB[i], self);
        if (r != 0) {
            s32 k = self->countB;
            self->objsB[k] = r;
            self->countB = k + 1;
        }
        i++;
    }
}


struct StateGraph;

// Starts the flagged object: starts the objects of both lists, finds its child (by id, or the
// first child of kind 0x74 when it has none yet), and, when it has a state graph, creates its
// state walker, sending it to key 0x547 when its flag is already set in the flag table.
void StartFlaggedObject(FlaggedObject* self)
{
    StartPlacedObject(self);
    for (s32 i = 0; i < self->countA; i++)
        ResolveAndStartObject((BaseObject*)self->objsA[i]);
    for (s32 i = 0; i < self->countB; i++)
        ResolveAndStartObject((BaseObject*)self->objsB[i]);
    if (self->childId == -1) {
        ListFrame it;
        u8* obj;
        ListWalkBegin::Of(&it, (ObjectList*)&self->children);
        while ((obj = ListWalkNext::Of(&it)) != 0) {
            if (IsObjectOfKind((BaseObject*)obj, 0x74) != 0) {
                self->childId = GetAliasId((BaseObject*)obj);
                if (self->childId == -1)
                    self->childId = ((BaseObject*)obj)->id;
                self->child = obj;
            }
        }
        g_activeListFrames = (ListFrame*)it.prev;
    } else {
        self->child = FindFirstObjectByIdMode4(self->world, self->childId, self);
    }
    if (self->stateGraph != 0) {
        self->handle = (StateWalker*)CreateStateWalker((StateGraph*)self->stateGraph, self, 0x546, 0);

        if (TestFlagTableBit((FlagTable*)g_flagTable, self->flagIndex) != 0)
            SetStateWalkerTarget(self->handle, 0x547);
    }
}


// Copies the collider but keeps its own flag index and ordinal, and gives the copy its own
// copies of the objects in both of its lists.
void CopyFlaggedObject(FlaggedObject* self, FlaggedObject* src)
{
    s32 keepB = self->flagIndex;
    s32 keepA = self->ordinal;
    CopyCollider(self, src);
    self->flagIndex = keepB;
    self->ordinal = keepA;
    for (s32 i = 0; i < self->countA; i++) {
        self->objsA[i] = CreateObjectCopy((BaseObject*)self->objsA[i], self->world, self);
    }
    for (s32 j = 0; j < self->countB; j++) {
        self->objsB[j] = CreateObjectCopy((BaseObject*)self->objsB[j], self->world, self);
    }
}

extern s32 D_0026EC58;
PlacedObject* GetActiveSwitchedCollider();

// Per-frame update: when the active player enters the shape of one of the B objects and the
// object's flag is not yet set (or was set far away), it saves that object's position in the flag
// table and raises the flag.
void UpdateFlaggedObject(FlaggedObject* self, f32 dt)
{
    UpdateCollider(self, dt);
    if (D_0026EC58 >= 2) {
        self->desc->m03(self);
        return;
    }
    PlacedObject* player = GetActiveSwitchedCollider();
    if (player == 0) {
        return;
    }
    FlagTable* table = (FlagTable*)g_flagTable;
    if (TestFlagTableBit(table, self->flagIndex)) {
        if (table->changed == 0) {
            return;
        }
        u128 d = Vu0::Sub(Vu0::Q(table->point), Vu0::Q(player->v140));
        if (Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(d, d))) < 1000.0f) {
            return;
        }
        Vu0::Q(table->point) = Vu0::FromFloats(3.4028235e+38f, 3.4028235e+38f, 3.4028235e+38f);
    }
    for (s32 i = 0; i < self->countB; i++) {
        void* obj = self->objsB[i];
        if (TestPointAgainstObjectShape((ObjectGatherer*)obj, &player->v140)) {
            GetObjectWorldPosition((BaseObject*)obj, (Vec4*)g_flagTableSaved);
            RaiseObjectFlag(self);
            break;
        }
    }
}

extern u8 g_padRecord[];

struct PadRecord;

// An event from the active switched collider gives a short pad pattern (unless the event's flag
// 0x10 is set) and raises the object's flag, and counts as handled; any other event takes the
// base handling.
s32 HandleFlaggedObjectEvent(FlaggedObject* self, ObjectEvent* ev)
{
    void* r = GetActiveSwitchedCollider();
    if (ev->source == r) {
        if ((ev->extraFlags & 0x10) == 0) {
            StartPadRecordPattern((PadRecord*)g_padRecord, 2, 0.2f);
        }
        RaiseObjectFlag(self);
        return 1;
    }
    return HandleObjectEvent(self, ev);
}

extern u8 g_scatterController[];

struct ScatterController;
struct FlaggedObject;

// Sets the object's bit in the flag table: notes it to the scatter controller, saves a snapshot
// of the flag table with the child's id and the alias id of its tree, starts the animations of
// the A list and moves its state walker to key 0x548 or 0x549.
void RaiseObjectFlag(FlaggedObject* self)
{
    RaiseScatterLevelForObject((ScatterController*)g_scatterController, self);
    s32 sel;
    if (self->handle != 0) {
        sel = TestFlagTableBit((FlagTable*)g_flagTable, self->flagIndex) ? 0x549 : 0x548;
    }
    s32 idx = -1;
    SetFlagTableBit((FlagTable*)g_flagTable, self->flagIndex);
    if (IsObjectDescendantOf((BaseObject*)self->child, self)) {
        for (BaseObject* n = self; n != 0; n = n->parent) {
            ObjectAlias* sl = n->alias;
            if (sl != 0) {
                idx = sl->id;
            }
        }
        if (idx == -1) {
            idx = self->id;
        }
    }
    SaveFlagTableSnapshot((FlagTable*)g_flagTable, self->childId, idx);
    for (s32 i = 0; i < self->countA; i++) {
        CreateAnimationPlayerWithoutPresetTargets((Animation*)self->objsA[i], 0, 0, 0, 0.0f, 1.0f);
    }
    if (self->handle != 0) {
        SetStateWalkerTarget(self->handle, sel);
    }
}

// Adds an id to the object's second list of ids.
void AppendFlaggedObjectIdB(FlaggedObject* q, s32 value)
{
    q->idsB[q->nIdsB++] = value;
}

// Adds an id to the object's first list of ids.
void AppendFlaggedObjectIdA(FlaggedObject* obj, void* item)
{
    s32 n = obj->nIdsA;
    obj->idsA[n] = (s32)item;
    obj->nIdsA = n + 1;
}

void SetFlaggedChildId(FlaggedObject* self, s32 value)
{
    self->childId = value;
}
