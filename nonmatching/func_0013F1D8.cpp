// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 176/184, checked 2026-11-08
// NEAR (2026-11-08, night-gamec): one instruction: retail multiplies the count by 0x30 twice (mult v0 for the address, mult and mflo for the size); this computes it once
// In the context of its file, src/main/zone_collider.cpp: its declarations before the function, bodies cut.
#include "common.h"
#include "flag_table.h"
#include "asm_func.h"
#include "list_iter.h"
#include "timed_state_object.h"
#include "trigger_zone.h"
#include "zone_collider.h"
#include "masked_collider.h"
#include "child_group_object.h"
#include "switched_collider.h"
#include "object_message.h"
#include "world.h"
#include "object_event.h"
#include "vu0.h"

// The file's .data, in retail's order: two boxes (the corners 0 and the size -1e8 or 1e8) and
// the records that point at them, which func_0013E430 reads, then the disc code's sector check
// state (disc_access.cpp uses it; its own .data must start 8-aligned).
f32 D_00261390[8] = { 0.0f, 0.0f, 0.0f, 0.0f, -100000000.0f, 0.0f, 0.0f, 0.0f };
f32 D_002613B0[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 100000000.0f, 0.0f, 0.0f, 0.0f };
f32* D_002613D0[4] = { D_00261390, 0, 0, 0 };
f32* D_002613E0[3] = { D_002613B0, 0, 0 };
s32 g_discSectorCheckState = 0;
void TriggerScriptEvent(void* obj, s32 kind, s32 a, s32 b);

extern u8 g_flagTable[];
void InitCollider(void* self);
void* TakeFlagTableIndex(FlagTable* p);

void InitMaskedCollider(MaskedCollider* self);

void LoadCollider(void* self);
s32 FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);
void FindOrBuildMemberGroup(void* sub, void* self);
void ResolveAndStartObject(s32 a);

void LoadMaskedCollider(MaskedCollider* self);

void CopyCollider(MaskedCollider* self, MaskedCollider* other);
void* CopyToFrontMemory(s32 size, void* owner);

void CopyMaskedCollider(MaskedCollider* self, MaskedCollider* other);

#include "common.h"
#include "list_iter.h"
#include "timed_state_object.h"
#include "trigger_zone.h"
#include "masked_collider.h"
#include "child_group_object.h"
#include "switched_collider.h"
#include "memory_reader.h"
#include "object_message.h"

void InitSoundParams(void* p);

typedef void (*Hook_CE40)(void* self);

void StartPlacedObject(MaskedCollider* self);
void AttachMaskedColliderChildren(MaskedCollider* self);
void* AppendQueuedCall(void* target, Hook_CE40 fn, MaskedCollider* ctx, s32 a3, s32 a4);

void StartMaskedCollider(MaskedCollider* self);

extern u8 g_flagTable[];

// A list walk's frame (ListFrame's words) with one more word after it, the flag
// func_00199C10 reads for each child.
struct ListFrameWithFlag { s32 list; s32 cursor; s32 link; s32 prev; s32 out; };
s32 TestFlagTableBit(FlagTable* t, s32 v);
s32 IsObjectOfKind(MaskedCollider* n, s32 kind);
void GetNumberedItemFlag(MaskedCollider* n, s32* out);
s32 MatchesObjectId(MaskedCollider* n, s32 key);

void AttachMaskedColliderChildren(MaskedCollider* self);

void UpdateCollider(void* self);

void UpdateMaskedCollider(MaskedCollider* self);

extern u8 g_flagTable[];

void SetFlagTableBit(FlagTable* table, s32 v);
void ClearFlagTableBit(FlagTable* table, s32 v);

void SetObjectHold(MaskedCollider* self, s32 v);

void AddMaskedColliderKeyKind0(MaskedCollider* q, s32 value);

void AddMaskedColliderKeyKind1(MaskedCollider* q, s32 value);

void AddMaskedColliderKeyKind2(MaskedCollider* self, s32 value);

void AddMaskedColliderKeyKind3(MaskedCollider* q, s32 value);

void SetAcceptsPlayer(MaskedCollider* self, s32 enabled);

void GetAcceptsPlayer(MaskedCollider* state, s32* result);

void SetAcceptsFlaggedObjects(MaskedCollider* self, s32 enabled);

void GetAcceptsFlaggedObjects(MaskedCollider* state, s32* result);

void AddAcceptedObjectId(MaskedCollider* obj, s32 value);

void AddAcceptedKind(MaskedCollider* r, s32 value);

void AddMaskedColliderListEntry(MaskedCollider* obj, s32 value);

void* GetMaskedColliderSoundParams(MaskedCollider* self);

void* GetActiveSwitchedCollider(void);
s32 MatchesObjectId(void* msg, void* item);
s32 IsObjectOfKind(void* msg, void* item);

s32 IsObjectAccepted(MaskedCollider* self, PathFollower* msg);

extern f32 g_gameTime;
void UpdateCollider(Collider* self);

void UpdateTimedState(TimedStateObject* self);

void HandlePlacedObjectNotification(TimedStateObject* self, s32 kind, ObjectMessage* msg);

void HandleTimedStateNotification(TimedStateObject* self, s32 kind, ObjectMessage* msg);

s32 IsObjectOfKind(Collider* src, s32 kind);
s32 TestTimedStateContact(TimedStateObject* node, Collider* src);

extern f32 g_gameTime;
s32 FadeOutPlacedObject(f32 value);

void SetTimedState(TimedStateObject* self, s32 state);

void InitMaskedCollider(MaskedCollider* self);

void InitPlayerFlaggedCollider(PlayerFlaggedCollider* self);

void InitMassScalingCollider(MassScalingCollider* self);

s32 IsObjectAccepted(MaskedCollider* self, s32 value);
void SetColliderTurnAnchorPreset(MassScalingCollider* self, s32 sel);
void SetColliderMoveAnchorPreset(MassScalingCollider* self, s32 sel);
void LatchContactObject(MassScalingCollider* self, u8* table, s32 index);

void LatchContactObject(MassScalingCollider* self, u8* table, s32 index);
s32 IsObjectAccepted(MaskedCollider* self, s32 value);
s32 IsObjectOfKind(void* node, s32 kind);

void LatchAcceptedSwitchedCollider(LatchedSwitchCollider* self, u8* table, s32 index);

void UpdateMaskedCollider(MaskedCollider* self);
void* GetActiveSwitchedCollider(void);
void InitOwnerMessage(void* out, void* a1, void* self);

void UpdateLatchedSwitchCollider(LatchedSwitchCollider* self);

void* AllocateFrontMemory(s32 size);

void CloneTreeNodes(Mesh03* self, Tree03* src, Mesh03* base, Tree03* dst);

void* FindFirstObjectById(void*, s32, void*, void*);
bool AppendToQueuedObjects(Pair28*, void*);
void ResolveAndStartObject(void*);

void ResolveZoneObjects(void* self, Pair28* list, void* context);

s32 MatchesObjectId(void* key, s32 item);

s32 IsObjectInIdList(Queue28* set, void* key);

bool AppendToQueuedObjects(Pair28* pair, s32 value);

bool AppendToObjectQueue(Queue28* queue, s32 value);

extern u8 g_flagTable[];
void* TakeFlagTableIndex(FlagTable* p);

void InitZoneRecord(void* self);

s32 IsObjectInIdList(Queue28* set, void* key);
bool AppendToQueuedObjects(Pair28* pair, void* value);

struct ListWalkNext {
    static BaseObject* Of(ListFrame* it)
    {
        BaseObject* obj = *(BaseObject**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct ListWalkBegin {
    static void Of(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = (g_activeListFrames);
        g_activeListFrames = (ListFrame*)it;
    }
};

void CollectZoneChildren(Zone28* self, Collider* a1);

extern u8 g_flagTable[];

void ResolveZoneObjects(void* a, void* b, void* c);
s32 TestFlagTableBit(FlagTable* table, s32 v);
void* AppendQueuedCall(void* a, void* fn, void* c, s32 d, s32 e);
void DeferZoneRecordActivation(void* self, s32 mode);

void StartZoneRecord(Zone28* self);

void* AppendQueuedCall(void* a, void* fn, void* c, s32 d, s32 e);
void ActivateZoneRecord(void* self, s32 a, s32 b);

void DeferZoneRecordActivation(void* selfp, s32 mode);

s32 UpsertKeyedEntry(void* list, s32 size, void* count, s32 a, s32 b, s32 c, s32 d);
void SetZoneEntry(Zone28* self, s32 a, s32 b, s32 c, s32 d);

extern f32 g_gameTime;
void ClearRootTries(void* self);
void ActivateZoneRecord(void* self, s32 a, s32 b);
void DeactivateZoneRecord(void* self, void* p);

void SetZoneMode(void* a, s32 b);

// An entry of Zone28::table14C (func_0013EC00 adds or updates one, func_0013ECB0 applies a
// list of them): an object's id, a key it answers to (-1 any), and the states to set it to.
struct ZoneTargetEntry {
    s32 id;                 // 0x00
    s32 key;                // 0x04: -1 matches any
    s32 onState;            // 0x08: when the flag is set
    s32 offState;           // 0x0C: otherwise
};

s32 UpsertKeyedEntry(ZoneTargetEntry* tab, s32 cap, s32* count, s32 flag, s32 k1, s32 k2, s32 val);

s32 GatherObjectsByMode(void* self, s32 kind, s32 key, void* arg, s32 flags, void* out);
void* FindObjectHandle(void* a, s32 b);
void SetStateWalkerTarget(void* a, s32 b);

s32 SetGatheredWalkerTargets(void* self, s32 n, ZoneTargetEntry* ent, void* arg, s32 flag);

void* FindFirstObjectByIdMode4(void* world, s32 key, void* requester);
s32 MatchesObjectId(void* owner, s32 key);
void* FindOrCreateSeekedAnimationPlayer(void* obj, void* other, s32 a2, s32 a3, f32 fa, f32 fb);
void ChooseStepSequenceState(void* t);
void ResetStepSequence(void* t);

// An object queued in a zone (func_0013ED90): the id of the object it goes to and a flag.
struct ZoneQueuedObject { u8 pad[0x40]; s32 key40; s32 flag44; };

void RunZoneRecordEntries(Zone28* self, s32 mode, void* p, void* q);

enum Kind_13EF50 { kind_13EF50_2 = 2 };

extern u8 g_flagTable[];

void StartSoundEffect(Kind_13EF50 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void RunZoneRecordEntries(Zone28* self, s32 mode, void* p, void* q);
void SetZoneMode(Zone28* self, s32 k);
void SetFlagTableBit(FlagTable* t, s32 v);

void ActivateZoneRecord(Zone28* self, void* p, void* q);

void TriggerScriptEvent(void* obj, s32 kind, s32 a, s32 b);
void RunZoneRecordEntries(Zone28* self, s32 mode, void* p, void* q);

void DeactivateZoneRecord(Zone28* self, void* p);

void InitCollider(Collider* self);
void InitZoneRecord(void* p);

void InitTriggerZone(TriggerZone* self);

void LoadCollider(Collider* self);
void CollectZoneChildren(Zone28* p, Collider* self);

void LoadTriggerZone(TriggerZone* self);

s32 MatchesObjectId(void* a, s32 n);
void MoveMemory(void* end, void* begin, s32 bytes);

void AddTriggerZoneQuad(TriggerZone* self, void* a1, Quad28* q);

// The 0x30-byte entry copied as three quadwords.
struct __attribute__((aligned(16))) Rotation30 { u8 b[0x30]; };

void AddTriggerZoneRotation(TriggerZone* self, void* a1, Entry28* e)
{
    s32 n = self->count7E0;
    s32 idx;
    if (MatchesObjectId(a1, 0x200)) {
        idx = 0;
        if (n > 0) {
            s32 o = n * 0x30;
            MoveMemory((u8*)(o + (s32)self) + 0x7F0, &self->entries[0], o);
        }
    } else {
        idx = n;
    }
    *(Rotation30*)&self->entries[idx] = *(Rotation30*)e;
    self->count7E0++;
}
