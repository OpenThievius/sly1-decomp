// SPDX-License-Identifier: AGPL-3.0-or-later
// 0x1000C8 to 0x112698 (.rodata from 0x248D80, .data from 0x2505D8): the script host functions
// on objects (each a tag 0x21 function taking its object, the argument count and the arguments)
// and FillObjectPropertyTable (func_00109488), which fills the property records of D_002505D8,
// this file's .data, with them and the property setters. Named after what it holds.
#include "common.h"
#include "asm_func.h"
#include "property_descriptor.h"
#include "script_value.h"
#include "shapes.h"
#include "base_object.h"
#include "placed_object.h"
#include "collider.h"
#include "switched_collider.h"
#include "attached_set.h"
#include "masked_collider.h"
#include "trigger_zone.h"
#include "zone_collider.h"
#include "object_set.h"
#include "timed_object.h"
#include "contact_tracker.h"
#include "child_group_object.h"
#include "target_follower.h"
#include "gauge_mode_object.h"
#include "counted_collider.h"
#include "lookup_object.h"
#include "effect_spawner.h"
#include "c5d.h"
#include "c60.h"
#include "c62.h"
#include "step_sequence.h"
#include "camera.h"
#include "transform_object.h"
#include "object_sub_group.h"
#include "animation.h"
#include "state_graph.h"
#include "c8b.h"
#include "object_pool.h"
#include "oscillator.h"
#include "entry_queue.h"
#include "timeline.h"

// The kinds a property's arguments are read as (func_001C23B0's fourth argument): one word per
// argument, copied from the file's .rodata into the frame as one block.
struct Kinds2 { s32 k[2]; };
struct Kinds3 { s32 k[3]; };
struct Kinds4 { s32 k[4]; };
struct Kinds5 { s32 k[5]; };
struct Kinds6 { s32 k[6]; };


void SetStateTriggerStateFromMessage(void* object, s32 mode);
s32 AddStateTriggerTableEntry(StateTrigger* self, s32 a1, s32 a2, s32 a3, s32 a4);
void ClearObjectRecordValues(void* p);
void FadeInPlacedObject(void* self, f32 value);
void FadeOutPlacedObject(void* self, f32 value);
void* FindObjectAnimationPlayer(void* self, s32 key);
void* FindObjectHandle(void* self, s32 key);
void* FindTrackPlayer(void* self);
void ClearAimHold(void* p);
void SetAimHold(void* p);
void SetValueAttachment(PlacedObject* self, s32 a, f32 x, f32 y);
void SetElementsScrollScale(void* self, f32 a, f32 b);
void SetCrossfadeRatioDeep(void* self, f32 value);
void StartSoundWithParams(PlacedObject* self, s32 value, Quad16* src, f32 x, f32 y, f32 z);
void StopPlayingSound(void* p);
void SetFollowObjects(PlacedObject* x, s32 a, s32 b);
void* CreateAnimationPlayerReturned(Animation* self, s32 a1, f32 f1, f32 f2, s32 a2);
void* FindOrCreateSeekedAnimationPlayer(Animation* item, s32 a, f32 x, f32 y, s32 b, s32 c);
f32 GetAnimationMarkerTime(void* obj, s32 id);
void StopAnimationPlayer(void* obj);
void ReleasePlayerAttachment(void* obj, s32 a, s32 b);
void SeekAnimationPlayer(AnimationPlayer* self, s32 a, f32 x, f32 y);
void ApplyListedPoseSources(void* obj, s32 v);
s32 IsObjectOfKind(void* list, s32 value);
void StartChildGroupDelay(void* p, f32 x);
void func_0013BF68(void*);
s32 SetTriggerZoneEntry(TriggerZone* self, s32 a1, s32 a2, s32 a3, s32 a4);
s32 SetZoneColliderEntry(ZoneCollider* self, s32 a1, s32 a2, s32 a3, s32 a4);
s32 TestPointAgainstObjectShape(void*,void*);
void RequestPlainCameraSnap(void* p);
void PushCameraStackValue(void*,s32);
s32 PopCameraStackValue(void*);
s32 PeekCameraStackValue(void* x);
void SetCameraControllerSettings(Camera* obj, s32 value, f32 first, f32 second);
void RecordCameraTimestamp(void* x);
s32 IsSphereInCameraView(void* obj, void* p, f32 x, f32 y);
void ResetCollectedItems(void*);
void RecordCollectedItem(void*,s32);
void SetStepSequenceModeOne(void* x);
void SetStepSequenceCameraMode(void* x);
void ChooseStepSequenceState(void* x);
void ResetStepSequence(void* x);
void AddSequenceExtraTarget(StepSequence* p, s32 a, s32 b);
void AddSpawnRangeEntry(void* self, s32 a, s32 b, f32 x, f32 y, f32 z, f32 w);
void SetEffectSpawnerActiveFor(void* p, f32 x);
void SetEffectSpawnerActiveForever(void* x);
void SetEffectSpawnerInactive(void* x);
void SendEmptyMessage(void* x);
void SendTwoVectorMessage(MemberObject* self, s32 a, s32 b, Quad4* u, Quad4* v, f32 x, f32 y);
void AddRecordMemberRangeEntry(void* self, s32 a, s32 b, f32 x, f32 y, f32 z, f32 w);
void StartColorFade(void* x);
s32 func_0015AA50(void*,void*);
void SetCurrentTargetFollower(void*);
void ClearCurrentTargetFollower(void*);
void PlacePlayerOnGround(void* self, void* v, f32 x, f32 y);
void ReleasePlayerToState2(void*);
void IgnorePlayerArgument(void*,s32);
void SwitchPlayerState11(void*,s32);
void QueuePlayerWalkerActivation(void* obj, s32 v);
void QueuePlayerFirstActivation(void* obj, s32 v);
void QueuePlayerSecondActivation(void*,s32);
void PlaceModeColliderAtAnchor(void* x);
void SetGaugeModeObjectTarget(void* self, s32 index);
void PlayGaugeModeObjectTarget(void* x);
void ResetEntryQueue(void*);
void BindEntryQueueToObject(void* x, s32 v);
void UnbindEntryQueue(void*);
void* AddQueueEntryKind0(void* x, s32 v);
void* AddQueueEntryKind1(void* x, s32 v);
void* AddQueueEntryKind10(void* x, s32 v);
void AddQueueEntryKind2(void* self, s32 value);
void* AddQueueEntryKind3(void* self, s32 value);
void AddQueueEntryKind4(void* self, s32 a, f32 value);
void* AddQueueEntryKind9(EntryQueue* p, s32 a, s32 b);
void AddQueueEntryKind5(EntryQueue* self, s32 b, s32 c, s32 d, s32 e);
void AddQueueEntryKind6(EntryQueue* self, s32 a, s32 b, f32 value);
void AddQueueEntryKind7(EntryQueue* self, s32 a, s32 b, f32 value);
void AddQueueEntryKind8(void* self, s32 b, s32 c, s32 d);
void AddQueueEntryKind11(void* x, f32 f);
s32 AddQueueEntryKind12(void* x);
void func_00182948(void* a0, s32 a1, f32 x);
void AddObjectKeyToOwner(void* p);
s32 IsObjectDescendantOf(void* e, s32 v);
void* CreateObjectCopy(BaseObject* x, s32 a, s32 b);
s32 MatchesObjectId(void* key, s32 item);
void SetExtraObjectPropertyBool(BaseObject* x, s32 a, s32 b);
void SetExtraObjectPropertyInt(BaseObject* x, s32 a, s32 b);
void SetExtraObjectPropertyFloat(void* a0, s32 a1, f32 x);
void SetExtraObjectPropertyVectorB(void* a0, s32 a1, Quad16* a2);
void SetExtraObjectPropertyPair(void* a0, s32 a1, Quad16* a2);
void SetExtraObjectPropertyWord(BaseObject* x, s32 a, s32 b);
void SetExtraObjectPropertyVectorA(void* a0, s32 a1, Quad16* a2);
void AdvanceGaugeAgentPhase(GaugeAgent* st);
void AddContactListId(void*,s32);
void AddContactListKind(void*,s32);
s32 AddSeekingAgentObject(void* x, s32 v);
void ActivateSwitchedColliderUnlessActive(void* o);
void QueueWalkerActivationOnPlayer(void* x);
void func_00199AF0(void* p);
void AddEntryRecordKey(C17* p, s32 a, s32 b);
void SetC8BObjectVector(C8B* value, f32 x, f32 y, f32 z);
void SetC8BObjectVectorFlagged(C8B* self, f32 x, f32 y, f32 z);
s32 AddObjectPoolEntry(ObjectPool* self, s32 a1, s32 a2, s32 a3, s32 a4);
void EnableObjectPoolEntry(void*,s32);
void DisableObjectPoolEntry(void*,s32);
void SetObjectPoolEntryCount(ObjectPool* p, s32 a, s32 b);
void ChooseObjectPoolItem(void*);
s32 func_001A8C90(void* obj, s32 v);
void ResetPlacementRecord(void* x);
void ResetObjectPoolReleaseRecord(void* x);
void ClearObjectPoolHeadingRecord(void*);
void SetGaugeBarAgentValues(GaugeBarAgent* self, s32 a, s32 b, s32 c);
void SetTimedGroupFadeOutTime(void* p, f32 x);
void SetTimedGroupFadeInTime(void* p, f32 x);
void* CreateStateWalker(StateGraph* a, s32 b, s32 c, s32 d);
void DestroyStateWalker(void* x);
void SetCompanionAgentLookId(CompanionAgent* p, s32 a, s32 b);
void SetColliderFlagNibble36(void* self, u32 value);
s32 IsPointInsideCollider(void* x, void* out);
void PushIopChannel2Setting(World* x, s32 a, s32 b);
void PopIopChannel2Setting(void* p);
void SetIopChannel2Setting(World* x, s32 a, s32 b);
void SendHitCountColliderRequest(void* self, s32 value);
void AddHitCountColliderId(void* self, s32 value);
void func_001C41A0(void* self, s32 value);
void ForceAgentState(Agent* p, s32 a, s32 b);
void SetAgentStateClipId(Agent* self, s32 a, s32 b);
void SetAgentStateClip(Agent* self, s32 a, s32 b);
void* GetAgentStateClip(void* obj, s32 v);
void AddAgentExtraClip(Agent* self, s32 a, s32 b);
void SetAgentSecondaryClipId(Agent* p, s32 a, s32 b);
void AddAgentMeshKey(Agent* self, s32 a, s32 b);
s32 AddAgentClipGroup(Agent* self, s32 a1, s32 a2, s32 a3, s32 a4);
void SetAgentMainClip(void*, s32);
void SetPlayerPath(void*,s32);
void SeekObjects105Animations(void*,s32);
void TakeCountedColliderTouch(CountedCollider* self, s32 a, s32 b);
void SwapInPlayerStandIn(void* obj);
void AddPathFollowerEntry(void*,s32);
void AddPathFollowerActiveEntry(PathFollower* item, s32 a, f32 x, f32 y, s32 b, s32 c);
void ResetPathFollower(PathFollower* st);
void SetCachedVoiceParamBuiltin(World* self, s32 a, s32 b);
s32 GetCachedVoiceParamBuiltin(void*,s32);
void* RefreshCachedVoiceParamBuiltin(World* self, s32 a, s32 b);
s32 TestLevelEntryFlag1(void* self, s32 obj);
s32 TestLevelEntryFlag2(void* self, s32 obj);
s32 TestLevelEntryFlag4(void* self, s32 obj);
s32 TestLevelEntryFlag8(void* self, s32 obj);
s32 CheckEntryOneBitRequirement(void* x, s32 v);
s32 CheckEntryTwoBitRequirement(void* x, s32 v);
s32 CheckEntryThreeBitRequirement(void* x, s32 v);
void SetEntrySlotValue(World* self, void* obj, s32 key, s32 value);
s32 GetEntrySlotValue(World* self, s32 a, s32 b);
s32 IsLevelRecordComplete(void* x, s32 v);
s32 IsLevelDone(void* self, s32 index);
s32 RecomputeSaveCompletion(void* self);
void ScatterRandomObjects(World* unused, s32 a, s32 b, void* c);
void AcquirePadSelectFlag(void* a);
void ReleasePadSelectFlag(void*);
void PopActiveSequenceElement(void* x);
void ShowPauseMenuPageWith(World* self, s32 a, s32 b);
void ShowCountedScreenElement(void* x);
void HideCountedScreenElement(void* x);
s32 PushSoundLevelBuiltin(void*,s32);
s32 RemoveSoundLevelBuiltin(void* unused, s32 p);
void SetWorldFlagBit(void*,s32);
void ClearWorldFlagBit(void*,s32);
void DecrementTempoAgentGauge(void* x);
void SetTempoAgentPendingTimeline(void* self, s32 value);
void EndHeldTimeline(void* x);
void AddTempoAgentEntry(TempoAgent* p, s32 a, s32 b);
void RemoveTempoAgentEntry(void* self, s32 value);
void AppendTimelineKind0Entry(Timeline* self, s32 p, f32 f, s32 q);
void AppendTimelineKind1Entry(Timeline* self, s32 p, f32 f, s32 q);
void AppendTimelineKind2Entry(Timeline* self, s32 p, f32 v);
void AppendTimelineKind3Entry(Timeline* self, s32 p, f32 v);
void AppendTimelineKind4Entry(Timeline* self, s32 p, f32 v);
void AppendTimelineKind5Entry(Timeline* self, s32 p, f32 v);
void ClearAttachedSetTrackedNodes(void* o);
s32 AddStateResetEntry(C62* self, s32 a1, s32 a2, s32 a3, s32 a4);
void AddOscillatorXEntry(void*);
void AddOscillatorYZEntry(void* x);
void AddOscillatorEntryVectorA(void* self, f32 a, f32 b, f32 c, f32 d);
void AddOscillatorEntryVectorB(void* self, f32 a, f32 b, f32 c, f32 d);
void PlaceAtArrivalPoint(void* x);
s32 SetTransformObjectKeyedValue(TransformObject* self, s32 a1, s32 a2, s32 a3, s32 a4);
void StartObjectSubGroupFinish(void* x);
void PushObjectCameraController(void*);
void RemoveObjectCameraController(void* p);
void ClearTrackedNodes(void* p);

// Reads a property call's arguments: count values of args, each as its kind in kinds, through
// the pointers that follow (func_001C1BF8, src/main/file_1C05D0.cpp); gives back a value.
ScriptValue* StoreScriptArgumentsVa(ScriptValue* ret, s32 count, ScriptValue* args, const void* kinds, ...);

// The file's .rodata: the argument signatures its functions copy, in retail's order.
extern const s32 D_00248D80[2] = { 0x2000, 0x2000 };
extern const s32 D_00248D88[2] = { 0x14, 0 };
extern const s32 D_00248D90[2] = { 0x14, 5 };
extern const s32 D_00248D98[2] = { 0x14, 1 };
extern const s32 D_00248DA0[2] = { 0x14, 9 };
extern const s32 D_00248DA8[2] = { 0x14, 10 };
extern const s32 D_00248DB0[2] = { 0x14, 6 };
extern const s32 D_00248DB8[2] = { 0x14, 2 };
extern const s32 D_00248DC0[4] = { 1, 1, 0x1000, 0 };
extern const s32 D_00248DD0[2] = { 1, 1 };
extern const s32 D_00248DD8[6] = { 14, 1, 1, 1, 10, 0 };
extern const s32 D_00248DF0[4] = { 0, 6, 6, 6 };
extern const s32 D_00248E00[4] = { 0x2000, 1, 1, 0x1000 };
extern const s32 D_00248E10[6] = { 0x2000, 0x1000, 1, 1, 0x1000, 0 };
extern const s32 D_00248E28[4] = { 0x1000, 1, 1, 0 };
extern const Kinds2 D_00248E38 = { { 6, 0x1000 } };
extern const s32 D_00248E40[6] = { 6, 6, 1, 1, 1, 1 };
extern const s32 D_00248E58[6] = { 0x1000, 0x2000, 2, 2, 1, 1 };
extern const s32 D_00248E70[4] = { 0x2000, 6, 0x1000, 0 };
extern const s32 D_00248E80[4] = { 5, 5, 2, 0 };
extern const s32 D_00248E90[2] = { 0x1000, 5 };
extern const s32 D_00248E98[4] = { 15, 6, 5, 0 };
extern const Kinds2 D_00248EA8 = { { 0xF, 6 } };
extern const Kinds2 D_00248EB0 = { { 0x1000, 0x2000 } };
extern const s32 D_00248EB8[2] = { 5, 5 };
extern const s32 D_00248EC0[2] = { 5, 0 };
extern const s32 D_00248EC8[4] = { 0x2000, 1, 1, 0 };
extern const s32 D_00248ED8[4] = { 2, 1, 1, 0 };
extern const s32 D_00248EE8[2] = { 0x1000, 6 };
extern const s32 D_00248EF0[4] = { 6, 6, 6, 6 };
extern const s32 D_00248F00[4] = { 1, 1, 1, 0 };
extern const s32 D_00248F10[4] = { 6, 5, 0, 0 };
extern const s32 D_00248F20[2] = { 6, 5 };
extern const s32 D_00248F28[4] = { 1, 1, 1, 1 };
extern const s32 D_00248F38[6] = { 0x2000, 1, 1, 0x2000, 0x2000, 0 };
extern const s32 D_00248F50[2] = { 0x2000, 1 };
extern const s32 D_00248F58[2] = { 6, 1 };
extern const s32 D_00248F60[4] = { 6, 0x1000, 0x1000, 0 };
extern const s32 D_00248F70[4] = { 6, 1, 0, 0 };
extern const s32 D_00248F80[4] = { 6, 0x1000, 0, 0 };
extern const s32 D_00248F90[2] = { 6, 0 };
extern const s32 D_00248F98[2] = { 0x2000, 5 };
extern const s32 D_00248FA0[4] = { 5, 1, 0x1000, 0 };
extern const s32 D_00248FB0[4] = { 5, 1, 6, 0 };
extern const s32 D_00248FC0[2] = { 5, 1 };
extern const s32 D_00248FC8[4] = { 0x2000, 0x2000, 0x2000, 0 };
extern const s32 D_00248FD8[2] = { 0x2000, 0 };

// The file's .data: the property descriptors, filled at startup by func_00109488.
PropertyDescriptor D_002505D8[1179];

ScriptValue* TestScriptObjectOfKind(ScriptValue* ret, void* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptObjectKeyToOwner(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* RemoveScriptObjectFromParentList(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptObjectToParentList(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* CreateScriptObjectCopy(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* ReparentScriptObject(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* TestScriptObjectDescendantOf(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* TestScriptObjectIdMatch(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptExtraObjectPropertyBool(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptExtraObjectPropertyInt(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptExtraObjectPropertyFloat(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptExtraObjectPropertyVectorB(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptExtraObjectPropertyPair(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptExtraObjectPropertyWord(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptExtraObjectPropertyVectorA(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* ClearScriptObjectRecordValues(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* ClearScriptAimHold(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptAimHold(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptValueAttachment(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptElementsScrollScale(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptCrossfadeRatioDeep(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* StartScriptSoundWithParams(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* StopScriptPlayingSound(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* FadeInScriptPlacedObject(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* FadeOutScriptPlacedObject(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* FindScriptObjectHandle(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* FindScriptObjectAnimationPlayer(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* FindScriptTrackPlayer(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* CopyScriptPlacedObjectFrame(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptFollowObjects(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptColliderFlagNibble36(ScriptValue* ret, Collider* obj, s32 unused, ScriptValue* args);
ScriptValue* TestScriptPointInsideCollider(ScriptValue* ret, Collider* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptTransformObjectKeyedValue(ScriptValue* ret, TransformObject* obj, s32 unused, ScriptValue* args);
ScriptValue* PlaceScriptAtArrivalPoint(ScriptValue* ret, TransformObject* obj, s32 unused, ScriptValue* args);
ScriptValue* StartScriptObjectSubGroupFinish(ScriptValue* ret, ObjectSubGroup* obj, s32 unused, ScriptValue* args);
ScriptValue* CreateScriptAnimationPlayer(ScriptValue* ret, Animation* obj, s32 unused, ScriptValue* args);
ScriptValue* FindOrCreateScriptSeekedAnimationPlayer(ScriptValue* ret, Animation* obj, s32 unused, ScriptValue* args);
ScriptValue* GetScriptAnimationMarkerTime(ScriptValue* ret, Animation* obj, s32 unused, ScriptValue* args);
ScriptValue* SeekScriptAnimationPlayer(ScriptValue* ret, AnimationPlayer* obj, s32 unused, ScriptValue* args);
ScriptValue* StopScriptAnimationPlayer(ScriptValue* ret, void* obj, s32 unused, ScriptValue* args);
ScriptValue* ApplyScriptListedPoseSources(ScriptValue* ret, void* obj, s32 unused, ScriptValue* args);
ScriptValue* ReleaseScriptPlayerAttachment(ScriptValue* ret, void* obj, s32 unused, ScriptValue* args);
ScriptValue* ClearScriptAttachedSetTrackedNodes(ScriptValue* ret, AttachedSet* obj, s32 unused, ScriptValue* args);
ScriptValue* HandleScriptMaskedColliderActivation(ScriptValue* ret, MaskedCollider* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptTriggerZoneEntry(ScriptValue* ret, TriggerZone* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptZoneColliderEntry(ScriptValue* ret, ZoneCollider* obj, s32 unused, ScriptValue* args);
ScriptValue* ActivateScriptSwitchedColliderUnlessActive(ScriptValue* ret, SwitchedCollider* obj, s32 unused, ScriptValue* args);
ScriptValue* TestScriptRequestBlocked(ScriptValue* ret, SwitchedCollider* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptStateTriggerStateFromMessage(ScriptValue* ret, StateTrigger* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptStateTriggerTableEntry(ScriptValue* ret, StateTrigger* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptTimedObjectMode(ScriptValue* ret, TimedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* RequestScriptTimedObjectEnd(ScriptValue* ret, TimedObject* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptTimedGroupFadeInTime(ScriptValue* ret, TimedGroup* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptTimedGroupFadeOutTime(ScriptValue* ret, TimedGroup* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptEffectSpawnerActiveFor(ScriptValue* ret, EffectSpawner* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptEffectSpawnerActiveForever(ScriptValue* ret, EffectSpawner* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptEffectSpawnerInactive(ScriptValue* ret, EffectSpawner* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptSpawnRangeEntry(ScriptValue* ret, EffectSpawner* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptRecordMemberRangeEntry(ScriptValue* ret, RecordMember* obj, s32 unused, ScriptValue* args);
ScriptValue* SendScriptEmptyMessageC7A(ScriptValue* ret, HoldingMember* obj, s32 unused, ScriptValue* args);
ScriptValue* SendScriptTwoVectorMessageC7A(ScriptValue* ret, HoldingMember* obj, s32 unused, ScriptValue* args);
ScriptValue* SendScriptEmptyMessageC78(ScriptValue* ret, MemberGroup* obj, s32 unused, ScriptValue* args);
ScriptValue* SendScriptTwoVectorMessageC78(ScriptValue* ret, MemberGroup* obj, s32 unused, ScriptValue* args);
ScriptValue* CreateScriptStateWalker(ScriptValue* ret, StateGraph* obj, s32 unused, ScriptValue* args);
ScriptValue* DestroyScriptStateWalker(ScriptValue* ret, void* obj, s32 unused, ScriptValue* args);
ScriptValue* ScatterScriptRandomObjects(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptIopChannel2Setting(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* PushScriptIopChannel2Setting(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* PopScriptIopChannel2Setting(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* TestScriptLevelEntryFlag1(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* TestScriptLevelEntryFlag2(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* TestScriptLevelEntryFlag4(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* TestScriptLevelEntryFlag8(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* CheckScriptEntryOneBitRequirement(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* CheckScriptEntryTwoBitRequirement(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* CheckScriptEntryThreeBitRequirement(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptEntrySlotValue(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* GetScriptEntrySlotValue(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* IsScriptLevelRecordComplete(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* IsScriptLevelDone(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* RecomputeScriptSaveCompletion(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* PopScriptActiveSequenceElement(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* ShowScriptPauseMenuPageWith(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* ShowScriptCountedScreenElement(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* HideScriptCountedScreenElement(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* PushScriptSoundLevel(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* RemoveScriptSoundLevel(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptCachedVoiceParam(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* GetScriptCachedVoiceParam(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* RefreshScriptCachedVoiceParam(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* AcquireScriptPadSelectFlag(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* ReleaseScriptPadSelectFlag(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* ClearScriptWorldFlagBit(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptWorldFlagBit(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args);
ScriptValue* PushScriptCameraStackValue(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args);
ScriptValue* PopScriptCameraStackValue(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args);
ScriptValue* PeekScriptCameraStackValue(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptCameraControllerSettings(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args);
ScriptValue* RecordScriptCameraTimestamp(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args);
ScriptValue* RequestScriptPlainCameraSnap(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args);
ScriptValue* TestScriptSphereInCameraView(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args);
ScriptValue* PushScriptObjectCameraController(ScriptValue* ret, LookupObject* obj, s32 unused, ScriptValue* args);
ScriptValue* RemoveScriptObjectCameraController(ScriptValue* ret, LookupObject* obj, s32 unused, ScriptValue* args);
ScriptValue* ClearScriptTrackedNodes(ScriptValue* ret, ContactTracker* obj, s32 unused, ScriptValue* args);
ScriptValue* CollectScriptNumberedItem(ScriptValue* ret, NumberedItem* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptAgentStateClipId(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptAgentStateClip(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args);
ScriptValue* GetScriptAgentStateClip(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptAgentClipGroup(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptAgentMeshKey(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptAgentExtraClip(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args);
ScriptValue* ForceScriptAgentState(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptAgentSecondaryClipId(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args);
ScriptValue* SteerScriptAgentAlongPath(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptAgentMainClip(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptCompanionAgentLookId(ScriptValue* ret, CompanionAgent* obj, s32 unused, ScriptValue* args);
ScriptValue* StartScriptChildGroupDelay(ScriptValue* ret, ChildGroupObject* obj, s32 unused, ScriptValue* args);
ScriptValue* StepScriptChildGroupObject(ScriptValue* ret, ChildGroupObject* obj, s32 unused, ScriptValue* args);
ScriptValue* PlaceScriptPlayerOnGround(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args);
ScriptValue* ReleaseScriptPlayerToState2(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args);
ScriptValue* IgnoreScriptPlayerArgument(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptPlayerPath(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args);
ScriptValue* SwitchScriptPlayerState11(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args);
ScriptValue* SeekScriptObjects105Animations(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args);
ScriptValue* SwapInScriptPlayerStandIn(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args);
ScriptValue* QueueScriptPlayerWalkerActivation(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args);
ScriptValue* QueueScriptPlayerFirstActivation(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args);
ScriptValue* QueueScriptPlayerSecondActivation(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptC8BObjectVector(ScriptValue* ret, C8B* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptC8BObjectVectorFlagged(ScriptValue* ret, C8B* obj, s32 unused, ScriptValue* args);
ScriptValue* ResetScriptCollectedItems(ScriptValue* ret, PooledHolder* obj, s32 unused, ScriptValue* args);
ScriptValue* CollectScriptItem(ScriptValue* ret, PooledHolder* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptContactListId(ScriptValue* ret, ContactListObject* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptContactListKind(ScriptValue* ret, ContactListObject* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptStateResetEntry(ScriptValue* ret, C62* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptCurrentTargetFollower(ScriptValue* ret, TargetFollower* obj, s32 unused, ScriptValue* args);
ScriptValue* ClearScriptCurrentTargetFollower(ScriptValue* ret, TargetFollower* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptObjectPoolEntry(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args);
ScriptValue* EnableScriptObjectPoolEntry(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args);
ScriptValue* DisableScriptObjectPoolEntry(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptObjectPoolEntryCount(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args);
ScriptValue* ChooseScriptObjectPoolItem(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args);
ScriptValue* ReleaseScriptObjectPoolItem(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args);
ScriptValue* ResetScriptPlacementRecord(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args);
ScriptValue* ResetScriptObjectPoolReleaseRecord(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args);
ScriptValue* ClearScriptObjectPoolHeadingRecord(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptStepSequenceModeOne(ScriptValue* ret, StepSequence* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptStepSequenceCameraMode(ScriptValue* ret, StepSequence* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptSequenceExtraTarget(ScriptValue* ret, StepSequence* obj, s32 unused, ScriptValue* args);
ScriptValue* ChooseScriptStepSequenceState(ScriptValue* ret, StepSequence* obj, s32 unused, ScriptValue* args);
ScriptValue* ResetScriptStepSequence(ScriptValue* ret, StepSequence* obj, s32 unused, ScriptValue* args);
ScriptValue* QueueScriptWalkerActivationOnPlayer(ScriptValue* ret, C5D* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptOscillatorXEntry(ScriptValue* ret, Oscillator* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptOscillatorYZEntry(ScriptValue* ret, Oscillator* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptOscillatorEntryVectorA(ScriptValue* ret, Oscillator* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptOscillatorEntryVectorB(ScriptValue* ret, Oscillator* obj, s32 unused, ScriptValue* args);
ScriptValue* AdvanceScriptGaugeAgentPhase(ScriptValue* ret, GaugeAgent* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptEntryRecordKey(ScriptValue* ret, C17* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptPathFollowerEntry(ScriptValue* ret, PathFollower* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptPathFollowerActiveEntry(ScriptValue* ret, PathFollower* obj, s32 unused, ScriptValue* args);
ScriptValue* ResetScriptPathFollower(ScriptValue* ret, PathFollower* obj, s32 unused, ScriptValue* args);
ScriptValue* TestScriptPointAgainstObjectShape(ScriptValue* ret, TransformObject* obj, s32 unused, ScriptValue* args);
ScriptValue* TestScriptPointInsideFaceTreeObject(ScriptValue* ret, C60* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptSeekingAgentObject(ScriptValue* ret, SeekingAgent* obj, s32 unused, ScriptValue* args);
ScriptValue* StartScriptC24ObjectPath(ScriptValue* ret, C24* obj, s32 unused, ScriptValue* args);
ScriptValue* ResetScriptEntryQueue(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* BindScriptEntryQueueToObject(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* UnbindScriptEntryQueue(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptQueueEntryKind0(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptQueueEntryKind1(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptQueueEntryKind10(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptQueueEntryKind2(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptQueueEntryKind3(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptQueueEntryKind4(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptQueueEntryKind5(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptQueueEntryKind6(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptQueueEntryKind7(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptQueueEntryKind8(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptQueueEntryKind9(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptQueueEntryKind11(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptQueueEntryKind12(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args);
ScriptValue* StartScriptColorFade(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args);
ScriptValue* PlayScriptGaugeModeObjectTarget(ScriptValue* ret, GaugeModeObject* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptGaugeModeObjectTarget(ScriptValue* ret, GaugeModeObject* obj, s32 unused, ScriptValue* args);
ScriptValue* PlaceScriptModeColliderAtAnchor(ScriptValue* ret, ModeCollider* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptTempoAgentPendingTimeline(ScriptValue* ret, TempoAgent* obj, s32 unused, ScriptValue* args);
ScriptValue* EndScriptHeldTimeline(ScriptValue* ret, TempoAgent* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptC13Entry(ScriptValue* ret, TempoAgent* obj, s32 unused, ScriptValue* args);
ScriptValue* RemoveScriptTempoAgentEntry(ScriptValue* ret, TempoAgent* obj, s32 unused, ScriptValue* args);
ScriptValue* DecrementScriptTempoAgentGauge(ScriptValue* ret, TempoAgent* obj, s32 unused, ScriptValue* args);
ScriptValue* AppendScriptTimelineKind0Entry(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args);
ScriptValue* AppendScriptTimelineKind1Entry(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args);
ScriptValue* AppendScriptTimelineKind2Entry(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args);
ScriptValue* AppendScriptTimelineKind3Entry(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args);
ScriptValue* AppendScriptTimelineKind4Entry(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args);
ScriptValue* AppendScriptTimelineKind5Entry(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptGaugeBarAgentValues(ScriptValue* ret, GaugeBarAgent* obj, s32 unused, ScriptValue* args);
ScriptValue* SendScriptHitCountColliderRequest(ScriptValue* ret, HitCountCollider* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptHitCountColliderId(ScriptValue* ret, HitCountCollider* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptHitCountColliderItem(ScriptValue* ret, HitCountCollider* obj, s32 unused, ScriptValue* args);
ScriptValue* TakeScriptCountedColliderTouch(ScriptValue* ret, CountedCollider* obj, s32 unused, ScriptValue* args);

ScriptValue* TestScriptObjectOfKind(ScriptValue* ret, void* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 7;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, IsObjectOfKind(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptObjectKeyToOwner(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddObjectKeyToOwner(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* RemoveScriptObjectFromParentList(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    obj->desc->m03(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptObjectToParentList(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    obj->desc->m02(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* CreateScriptObjectCopy(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248D80;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValuePointerB(&q, CreateObjectCopy(obj, o1, o2));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ReparentScriptObject(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    BaseObject* out;
    InitScriptValue(&q);
    kinds = 0x2000;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    obj->desc->m15(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* TestScriptObjectDescendantOf(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 flag = IsObjectDescendantOf(obj, out);
    SetScriptValueBool(&q, flag);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* TestScriptObjectIdMatch(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x6;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 flag = MatchesObjectId(obj, out);
    SetScriptValueBool(&q, flag);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptExtraObjectPropertyBool(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248D88;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetExtraObjectPropertyBool(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptExtraObjectPropertyInt(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248D90;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetExtraObjectPropertyInt(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptExtraObjectPropertyFloat(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 a;
    f32 b;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248D98;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &a, &b);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetExtraObjectPropertyFloat(obj, a, b);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptExtraObjectPropertyVectorB(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    Quad16 vec;
    ScriptValue t;
    s32 out;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248DA0;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &out, &vec);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetExtraObjectPropertyVectorB(obj, out, &vec);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptExtraObjectPropertyPair(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    Quad16 vec;
    ScriptValue t;
    s32 out;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248DA8;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &out, &vec);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetExtraObjectPropertyPair(obj, out, &vec);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptExtraObjectPropertyWord(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248DB0;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetExtraObjectPropertyWord(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptExtraObjectPropertyVectorA(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    Quad16 vec;
    ScriptValue t;
    s32 out;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248DB8;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &out, &vec);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetExtraObjectPropertyVectorA(obj, out, &vec);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ClearScriptObjectRecordValues(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ClearObjectRecordValues(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ClearScriptAimHold(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ClearAimHold(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptAimHold(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetAimHold(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptValueAttachment(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    f32 o0;
    f32 o1;
    s32 o2;
    Kinds3* np;
    f32* o0p;
    f32* o1p;
    s32* o2p;
    InitScriptValue(&q);
    np = &kinds;
    o0p = &o0;
    o1p = &o1;
    o2p = &o2;
    kinds = *(Kinds3*)&D_00248DC0;
    (void)StoreScriptArgumentsVa(&t, 3, args, np, o0p, o1p, o2p);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetValueAttachment(obj, o2, o0, o1);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptElementsScrollScale(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    f32 x;
    f32 y;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248DD0;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &x, &y);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetElementsScrollScale(obj, x, y);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptCrossfadeRatioDeep(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    f32 f0;
    InitScriptValue(&q);
    kinds = 1;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &f0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetCrossfadeRatioDeep(obj, f0);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* StartScriptSoundWithParams(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds5 kinds;
    Quad16 vec;
    ScriptValue t;
    s32 i0;
    f32 f0, f1, f2;
    InitScriptValue(&q);
    kinds = *(Kinds5*)&D_00248DD8;
    StoreScriptArgumentsVa(&t, 5, args, &kinds, &i0, &f0, &f1, &f2, &vec);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    StartSoundWithParams(obj, i0, &vec, f0, f1, f2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* StopScriptPlayingSound(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    StopPlayingSound(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* FadeInScriptPlacedObject(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    f32 f0;
    InitScriptValue(&q);
    kinds = 1;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &f0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    FadeInPlacedObject(obj, f0);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* FadeOutScriptPlacedObject(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    f32 f0;
    InitScriptValue(&q);
    kinds = 1;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &f0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)FadeOutPlacedObject(obj, f0);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* FindScriptObjectHandle(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x6;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValuePointerB(&q, FindObjectHandle(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* FindScriptObjectAnimationPlayer(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 y;
    InitScriptValue(&q);
    s32* px = &kinds;
    s32* py = &y;
    *px = 6;
    StoreScriptArgumentsVa(&t, 1, args, px, py);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValuePointerB(&q, FindObjectAnimationPlayer(obj, y));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* FindScriptTrackPlayer(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValuePointerB(&q, FindTrackPlayer(obj));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* CopyScriptPlacedObjectFrame(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    PlacedObject* y;
    InitScriptValue(&q);
    s32* px = &kinds;
    PlacedObject** py = &y;
    *px = 0x2000;
    (void)StoreScriptArgumentsVa(&t, 1, args, px, py);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    obj->desc02()->m1F(obj, y);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptFollowObjects(ScriptValue* ret, PlacedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248D80;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetFollowObjects(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptColliderFlagNibble36(ScriptValue* ret, Collider* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 y;
    InitScriptValue(&q);
    s32* px = &kinds;
    s32* py = &y;
    *px = 0x1000;
    (void)StoreScriptArgumentsVa(&t, 1, args, px, py);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetColliderFlagNibble36(obj, y);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* TestScriptPointInsideCollider(ScriptValue* ret, Collider* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Quad4 vec;
    ScriptValue t;
    s32 kinds;
    InitScriptValue(&q);
    kinds = 2;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &vec);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 r = IsPointInsideCollider(obj, &vec);
    SetScriptValueBool(&q, r);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptTransformObjectKeyedValue(ScriptValue* ret, TransformObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds4*)D_00248DF0;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 r = SetTransformObjectKeyedValue(obj, o0, o1, o2, o3);
    (void)r;
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* PlaceScriptAtArrivalPoint(ScriptValue* ret, TransformObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    PlaceAtArrivalPoint(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* StartScriptObjectSubGroupFinish(ScriptValue* ret, ObjectSubGroup* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    StartObjectSubGroupFinish(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* CreateScriptAnimationPlayer(ScriptValue* ret, Animation* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    s32 o0;
    f32 o1;
    f32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds4*)&D_00248E00;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    void* r = CreateAnimationPlayerReturned(obj, o0, o1, o2, o3);
    SetScriptValuePointerB(&q, r);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* FindOrCreateScriptSeekedAnimationPlayer(ScriptValue* ret, Animation* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds5 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    f32 o3;
    f32 o4;
    s32 o5;
    InitScriptValue(&q);
    kinds = *(Kinds5*)&D_00248E10;
    (void)StoreScriptArgumentsVa(&t, 5, args, &kinds, &o1, &o2, &o3, &o4, &o5);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValuePointerB(&q, FindOrCreateSeekedAnimationPlayer(obj, o1, o3, o4, o2, o5));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* GetScriptAnimationMarkerTime(ScriptValue* ret, Animation* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 v;
    InitScriptValue(&q);
    kinds = 6;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &v);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    f32 r = GetAnimationMarkerTime(obj, v);
    SetScriptValueFloat(&q, r);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SeekScriptAnimationPlayer(ScriptValue* ret, AnimationPlayer* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    s32 o0;
    f32 o1;
    f32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds3*)&D_00248E28;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o0, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SeekAnimationPlayer(obj, o0, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* StopScriptAnimationPlayer(ScriptValue* ret, void* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    StopAnimationPlayer(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ApplyScriptListedPoseSources(ScriptValue* ret, void* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 5;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ApplyListedPoseSources(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ReleaseScriptPlayerAttachment(ScriptValue* ret, void* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = D_00248E38;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)ReleasePlayerAttachment(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ClearScriptAttachedSetTrackedNodes(ScriptValue* ret, AttachedSet* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ClearAttachedSetTrackedNodes(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* HandleScriptMaskedColliderActivation(ScriptValue* ret, MaskedCollider* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    obj->desc20()->m48(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptTriggerZoneEntry(ScriptValue* ret, TriggerZone* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds4*)D_00248DF0;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 r = SetTriggerZoneEntry(obj, o0, o1, o2, o3);
    (void)r;
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptZoneColliderEntry(ScriptValue* ret, ZoneCollider* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds4*)D_00248DF0;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 r = SetZoneColliderEntry(obj, o0, o1, o2, o3);
    (void)r;
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ActivateScriptSwitchedColliderUnlessActive(ScriptValue* ret, SwitchedCollider* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ActivateSwitchedColliderUnlessActive(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* TestScriptRequestBlocked(ScriptValue* ret, SwitchedCollider* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x1000;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 flag = obj->desc05()->m4B(obj, out);
    SetScriptValueBool(&q, flag);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptStateTriggerStateFromMessage(ScriptValue* ret, StateTrigger* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x1000;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetStateTriggerStateFromMessage(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptStateTriggerTableEntry(ScriptValue* ret, StateTrigger* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds4*)D_00248DF0;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 r = AddStateTriggerTableEntry(obj, o0, o1, o2, o3);
    (void)r;
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptTimedObjectMode(ScriptValue* ret, TimedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x1000;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    void (*fn)(TimedObject*, s32) = obj->desc30()->m49;
    if (fn != 0) {
        fn(obj, out);
    }
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* RequestScriptTimedObjectEnd(ScriptValue* ret, TimedObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    void (*fn)(TimedObject*) = obj->desc30()->m4A;
    if (fn != 0) {
        fn(obj);
    }
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptTimedGroupFadeInTime(ScriptValue* ret, TimedGroup* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    f32 out;
    InitScriptValue(&q);
    kinds = 1;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetTimedGroupFadeInTime(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptTimedGroupFadeOutTime(ScriptValue* ret, TimedGroup* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    f32 out;
    InitScriptValue(&q);
    kinds = 1;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetTimedGroupFadeOutTime(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptEffectSpawnerActiveFor(ScriptValue* ret, EffectSpawner* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    f32 out;
    InitScriptValue(&q);
    kinds = 1;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetEffectSpawnerActiveFor(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptEffectSpawnerActiveForever(ScriptValue* ret, EffectSpawner* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetEffectSpawnerActiveForever(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptEffectSpawnerInactive(ScriptValue* ret, EffectSpawner* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetEffectSpawnerInactive(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptSpawnRangeEntry(ScriptValue* ret, EffectSpawner* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds6 kinds;
    ScriptValue t;
    s32 i0, i1;
    f32 f0, f1, f2, f3;
    InitScriptValue(&q);
    kinds = *(Kinds6*)&D_00248E40;
    (void)StoreScriptArgumentsVa(&t, 6, args, &kinds, &i0, &i1, &f0, &f1, &f2, &f3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddSpawnRangeEntry(obj, i0, i1, f0, f1, f2, f3);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptRecordMemberRangeEntry(ScriptValue* ret, RecordMember* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds6 kinds;
    ScriptValue t;
    s32 i0, i1;
    f32 f0, f1, f2, f3;
    InitScriptValue(&q);
    kinds = *(Kinds6*)&D_00248E40;
    (void)StoreScriptArgumentsVa(&t, 6, args, &kinds, &i0, &i1, &f0, &f1, &f2, &f3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddRecordMemberRangeEntry(obj, i0, i1, f0, f1, f2, f3);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SendScriptEmptyMessageC7A(ScriptValue* ret, HoldingMember* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SendEmptyMessage(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SendScriptTwoVectorMessageC7A(ScriptValue* ret, HoldingMember* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds6 kinds;
    Quad4 vec0;
    Quad4 vec1;
    ScriptValue t;
    s32 i0;
    s32 i1;
    f32 f0;
    f32 f1;

    InitScriptValue(&q);
    s32* pi0 = &i0;
    s32* pi1 = &i1;
    kinds = *(Kinds6*)&D_00248E58;
    (void)StoreScriptArgumentsVa(&t, 6, args, &kinds, pi0, pi1, &vec0, &vec1, &f0, &f1);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SendTwoVectorMessage(obj, i0, i1, &vec0, &vec1, f0, f1);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SendScriptEmptyMessageC78(ScriptValue* ret, MemberGroup* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SendEmptyMessage(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SendScriptTwoVectorMessageC78(ScriptValue* ret, MemberGroup* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds6 kinds;
    Quad4 vec0;
    Quad4 vec1;
    ScriptValue t;
    s32 i0;
    s32 i1;
    f32 f0;
    f32 f1;

    InitScriptValue(&q);
    kinds = *(Kinds6*)&D_00248E58;
    (void)StoreScriptArgumentsVa(&t, 6, args, &kinds, &i0, &i1, &vec0, &vec1, &f0, &f1);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SendTwoVectorMessage(obj, i0, i1, &vec0, &vec1, f0, f1);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* CreateScriptStateWalker(ScriptValue* ret, StateGraph* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds3*)&D_00248E70;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    void* v = CreateStateWalker(obj, o1, o2, o3);
    SetScriptValuePointerB(&q, v);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* DestroyScriptStateWalker(ScriptValue* ret, void* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    DestroyStateWalker(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ScatterScriptRandomObjects(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    Quad4 vec;
    ScriptValue t;
    s32 a;
    s32 b;
    InitScriptValue(&q);
    kinds = *(Kinds3*)&D_00248E80;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &a, &b, &vec);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ScatterRandomObjects(obj, a, b, &vec);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptIopChannel2Setting(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248E90;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetIopChannel2Setting(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* PushScriptIopChannel2Setting(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248E90;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)PushIopChannel2Setting(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* PopScriptIopChannel2Setting(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    PopIopChannel2Setting(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* TestScriptLevelEntryFlag1(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0xF;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, TestLevelEntryFlag1(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* TestScriptLevelEntryFlag2(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0xF;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, TestLevelEntryFlag2(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* TestScriptLevelEntryFlag4(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0xF;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, TestLevelEntryFlag4(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* TestScriptLevelEntryFlag8(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0xF;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, TestLevelEntryFlag8(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* CheckScriptEntryOneBitRequirement(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0xF;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, CheckEntryOneBitRequirement(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* CheckScriptEntryTwoBitRequirement(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0xF;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, CheckEntryTwoBitRequirement(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* CheckScriptEntryThreeBitRequirement(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0xF;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, CheckEntryThreeBitRequirement(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptEntrySlotValue(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    void* o1;
    s32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds3*)&D_00248E98;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetEntrySlotValue(obj, o1, o2, o3);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* GetScriptEntrySlotValue(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 out1;
    s32 out2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248EA8;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &out1, &out2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 r = GetEntrySlotValue(obj, out1, out2);
    SetScriptValueInt(&q, r);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* IsScriptLevelRecordComplete(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x1000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, IsLevelRecordComplete(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* IsScriptLevelDone(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x1000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, IsLevelDone(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* RecomputeScriptSaveCompletion(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueInt(&q, RecomputeSaveCompletion(obj));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* PopScriptActiveSequenceElement(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    PopActiveSequenceElement(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ShowScriptPauseMenuPageWith(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 out1;
    s32 out2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248EB0;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &out1, &out2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ShowPauseMenuPageWith(obj, out1, out2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ShowScriptCountedScreenElement(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ShowCountedScreenElement(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* HideScriptCountedScreenElement(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    HideCountedScreenElement(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* PushScriptSoundLevel(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 5;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 v = PushSoundLevelBuiltin(obj, out);
    SetScriptValueInt(&q, v);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* RemoveScriptSoundLevel(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x5;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)RemoveSoundLevelBuiltin(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptCachedVoiceParam(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 out1;
    s32 out2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248EB8;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &out1, &out2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetCachedVoiceParamBuiltin(obj, out1, out2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* GetScriptCachedVoiceParam(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 5;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 v = GetCachedVoiceParamBuiltin(obj, out);
    SetScriptValueInt(&q, v);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* RefreshScriptCachedVoiceParam(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 out1;
    s32 out2;
    Kinds2* pp;
    s32* o1;
    s32* o2;
    InitScriptValue(&q);
    pp = &kinds;
    o1 = &out1;
    o2 = &out2;
    kinds = *(Kinds2*)D_00248EC0;
    (void)StoreScriptArgumentsVa(&t, 2, args, pp, o1, o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    RefreshCachedVoiceParamBuiltin(obj, out1, out2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AcquireScriptPadSelectFlag(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AcquirePadSelectFlag(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ReleaseScriptPadSelectFlag(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ReleasePadSelectFlag(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ClearScriptWorldFlagBit(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x1000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ClearWorldFlagBit(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptWorldFlagBit(ScriptValue* ret, World* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x1000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetWorldFlagBit(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* PushScriptCameraStackValue(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x1000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    PushCameraStackValue(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* PopScriptCameraStackValue(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueInt(&q, PopCameraStackValue(obj));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* PeekScriptCameraStackValue(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 v = PeekCameraStackValue(obj);
    SetScriptValueInt(&q, v);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptCameraControllerSettings(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    s32 o0;
    f32 o1;
    f32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds3*)D_00248EC8;
    StoreScriptArgumentsVa(&t, 3, args, &kinds, &o0, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetCameraControllerSettings(obj, o0, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* RecordScriptCameraTimestamp(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    RecordCameraTimestamp(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* RequestScriptPlainCameraSnap(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    RequestPlainCameraSnap(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* TestScriptSphereInCameraView(ScriptValue* ret, Camera* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    Quad4 vec;
    ScriptValue t;
    f32 fx;
    f32 fy;
    InitScriptValue(&q);
    kinds = *(Kinds3*)D_00248ED8;
    StoreScriptArgumentsVa(&t, 3, args, &kinds, &vec, &fx, &fy);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, IsSphereInCameraView(obj, &vec, fx, fy));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* PushScriptObjectCameraController(ScriptValue* ret, LookupObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    PushObjectCameraController(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* RemoveScriptObjectCameraController(ScriptValue* ret, LookupObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    RemoveObjectCameraController(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ClearScriptTrackedNodes(ScriptValue* ret, ContactTracker* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ClearTrackedNodes(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* CollectScriptNumberedItem(ScriptValue* ret, NumberedItem* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_00199AF0(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptAgentStateClipId(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 out1;
    s32 out2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248EE8;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &out1, &out2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetAgentStateClipId(obj, out1, out2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptAgentStateClip(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 out1;
    s32 out2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248EE8;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &out1, &out2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetAgentStateClip(obj, out1, out2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* GetScriptAgentStateClip(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x1000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValuePointerB(&q, GetAgentStateClip(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptAgentClipGroup(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds4*)D_00248EF0;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 r = AddAgentClipGroup(obj, o0, o1, o2, o3);
    (void)r;
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptAgentMeshKey(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 out1;
    s32 out2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&D_00248E38;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &out1, &out2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddAgentMeshKey(obj, out1, out2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptAgentExtraClip(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 out1;
    s32 out2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248EE8;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &out1, &out2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddAgentExtraClip(obj, out1, out2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ForceScriptAgentState(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = D_00248EB0;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ForceAgentState(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptAgentSecondaryClipId(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    Kinds2* kp;
    s32* o1p;
    s32* o2p;
    InitScriptValue(&q);
    kp = &kinds;
    o1p = &o1;
    o2p = &o2;
    kinds = *(Kinds2*)D_00248EE8;
    (void)StoreScriptArgumentsVa(&t, 2, args, kp, o1p, o2p);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetAgentSecondaryClipId(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SteerScriptAgentAlongPath(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ((void (*)(void*))obj->desc08()->m61)(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptAgentMainClip(ScriptValue* ret, Agent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetAgentMainClip(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptCompanionAgentLookId(ScriptValue* ret, CompanionAgent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248EE8;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetCompanionAgentLookId(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* StartScriptChildGroupDelay(ScriptValue* ret, ChildGroupObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    f32 out;
    InitScriptValue(&q);
    kinds = 1;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)StartChildGroupDelay(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* StepScriptChildGroupObject(ScriptValue* ret, ChildGroupObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_0013BF68(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* PlaceScriptPlayerOnGround(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    Quad4 vec;
    ScriptValue t;
    f32 fx;
    f32 fy;
    Kinds3* kp;
    Quad4* vecp;
    f32* fxp;
    f32* fyp;
    InitScriptValue(&q);
    kp = &kinds;
    vecp = &vec;
    fxp = &fx;
    fyp = &fy;
    kinds = *(Kinds3*)D_00248ED8;
    (void)StoreScriptArgumentsVa(&t, 3, args, kp, vecp, fxp, fyp);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    PlacePlayerOnGround(obj, &vec, fx, fy);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ReleaseScriptPlayerToState2(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ReleasePlayerToState2(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* IgnoreScriptPlayerArgument(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    IgnorePlayerArgument(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptPlayerPath(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetPlayerPath(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SwitchScriptPlayerState11(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SwitchPlayerState11(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SeekScriptObjects105Animations(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SeekObjects105Animations(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SwapInScriptPlayerStandIn(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SwapInPlayerStandIn(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* QueueScriptPlayerWalkerActivation(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)QueuePlayerWalkerActivation(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* QueueScriptPlayerFirstActivation(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)QueuePlayerFirstActivation(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* QueueScriptPlayerSecondActivation(ScriptValue* ret, Player* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    QueuePlayerSecondActivation(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptC8BObjectVector(ScriptValue* ret, C8B* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    f32 o0;
    f32 o1;
    f32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds3*)D_00248F00;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o0, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetC8BObjectVector(obj, o0, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptC8BObjectVectorFlagged(ScriptValue* ret, C8B* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    f32 o0;
    f32 o1;
    f32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds3*)D_00248F00;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o0, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetC8BObjectVectorFlagged(obj, o0, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ResetScriptCollectedItems(ScriptValue* ret, PooledHolder* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ResetCollectedItems(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* CollectScriptItem(ScriptValue* ret, PooledHolder* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    RecordCollectedItem(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptContactListId(ScriptValue* ret, ContactListObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 6;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddContactListId(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptContactListKind(ScriptValue* ret, ContactListObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 7;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddContactListKind(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptStateResetEntry(ScriptValue* ret, C62* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds4*)D_00248DF0;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 r = AddStateResetEntry(obj, o0, o1, o2, o3);
    (void)r;
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptCurrentTargetFollower(ScriptValue* ret, TargetFollower* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetCurrentTargetFollower(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ClearScriptCurrentTargetFollower(ScriptValue* ret, TargetFollower* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ClearCurrentTargetFollower(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptObjectPoolEntry(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    s32 o0;
    s32 o1;
    s32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds4*)D_00248F10;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 r = AddObjectPoolEntry(obj, o0, o1, o2, o3);
    (void)r;
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* EnableScriptObjectPoolEntry(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 6;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    EnableObjectPoolEntry(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* DisableScriptObjectPoolEntry(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 6;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    DisableObjectPoolEntry(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptObjectPoolEntryCount(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248F20;
    StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetObjectPoolEntryCount(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ChooseScriptObjectPoolItem(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ChooseObjectPoolItem(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ReleaseScriptObjectPoolItem(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    s32 flag = func_001A8C90(obj, out);
    SetScriptValueBool(&q, flag);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ResetScriptPlacementRecord(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ResetPlacementRecord(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ResetScriptObjectPoolReleaseRecord(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ResetObjectPoolReleaseRecord(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ClearScriptObjectPoolHeadingRecord(ScriptValue* ret, ObjectPool* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ClearObjectPoolHeadingRecord(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptStepSequenceModeOne(ScriptValue* ret, StepSequence* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetStepSequenceModeOne(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptStepSequenceCameraMode(ScriptValue* ret, StepSequence* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetStepSequenceCameraMode(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptSequenceExtraTarget(ScriptValue* ret, StepSequence* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = D_00248EA8;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddSequenceExtraTarget(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ChooseScriptStepSequenceState(ScriptValue* ret, StepSequence* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ChooseStepSequenceState(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ResetScriptStepSequence(ScriptValue* ret, StepSequence* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ResetStepSequence(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* QueueScriptWalkerActivationOnPlayer(ScriptValue* ret, C5D* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    QueueWalkerActivationOnPlayer(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptOscillatorXEntry(ScriptValue* ret, Oscillator* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddOscillatorXEntry(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptOscillatorYZEntry(ScriptValue* ret, Oscillator* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddOscillatorYZEntry(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptOscillatorEntryVectorA(ScriptValue* ret, Oscillator* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    InitScriptValue(&q);
    kinds = *(Kinds4*)D_00248F28;
    (void)StoreScriptArgumentsVa(&t, 4, args, &kinds, &x, &y, &z, &w);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddOscillatorEntryVectorA(obj, x, y, z, w);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptOscillatorEntryVectorB(ScriptValue* ret, Oscillator* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    InitScriptValue(&q);
    kinds = *(Kinds4*)D_00248F28;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &x, &y, &z, &w);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddOscillatorEntryVectorB(obj, x, y, z, w);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AdvanceScriptGaugeAgentPhase(ScriptValue* ret, GaugeAgent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AdvanceGaugeAgentPhase(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptEntryRecordKey(ScriptValue* ret, C17* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248EE8;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddEntryRecordKey(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptPathFollowerEntry(ScriptValue* ret, PathFollower* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddPathFollowerEntry(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptPathFollowerActiveEntry(ScriptValue* ret, PathFollower* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds5 kinds;
    ScriptValue t;
    s32 o1;
    f32 o2;
    f32 o3;
    s32 o4;
    s32 o5;
    InitScriptValue(&q);
    kinds = *(Kinds5*)D_00248F38;
    (void)StoreScriptArgumentsVa(&t, 5, args, &kinds, &o1, &o2, &o3, &o4, &o5);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddPathFollowerActiveEntry(obj, o1, o2, o3, o4, o5);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ResetScriptPathFollower(ScriptValue* ret, PathFollower* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ResetPathFollower(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* TestScriptPointAgainstObjectShape(ScriptValue* ret, TransformObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Quad4 vec;
    ScriptValue t;
    s32 kinds;
    InitScriptValue(&q);
    kinds = 2;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &vec);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, TestPointAgainstObjectShape(obj, &vec));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* TestScriptPointInsideFaceTreeObject(ScriptValue* ret, C60* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Quad4 vec;
    ScriptValue t;
    s32 kinds;
    InitScriptValue(&q);
    kinds = 2;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &vec);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, func_0015AA50(obj, &vec));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptSeekingAgentObject(ScriptValue* ret, SeekingAgent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, AddSeekingAgentObject(obj, out));
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* StartScriptC24ObjectPath(ScriptValue* ret, C24* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 a;
    f32 b;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248F50;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &a, &b);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    func_00182948(obj, a, b);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* ResetScriptEntryQueue(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q, t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    ResetEntryQueue(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* BindScriptEntryQueueToObject(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    BindEntryQueueToObject(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* UnbindScriptEntryQueue(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q, t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    UnbindEntryQueue(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptQueueEntryKind0(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x6;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind0(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptQueueEntryKind1(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x6;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind1(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptQueueEntryKind10(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x6;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind10(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptQueueEntryKind2(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 6;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)AddQueueEntryKind2(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptQueueEntryKind3(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 6;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)AddQueueEntryKind3(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptQueueEntryKind4(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 a;
    f32 b;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248F58;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &a, &b);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind4(obj, a, b);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptQueueEntryKind5(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds4 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    s32 o3;
    s32 o4;
    InitScriptValue(&q);
    kinds = *(Kinds4*)D_00248F60;
    (void)StoreScriptArgumentsVa(&t, 4, args, &kinds, &o1, &o2, &o3, &o4);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind5(obj, o1, o2, o3, o4);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptQueueEntryKind6(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    s32 o1;
    f32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds3*)D_00248F70;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind6(obj, o1, o3, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptQueueEntryKind7(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    s32 o1;
    f32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds3*)D_00248F70;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind7(obj, o1, o3, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptQueueEntryKind8(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    s32 o0;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds3*)D_00248F80;
    StoreScriptArgumentsVa(&t, 3, args, &kinds, &o0, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind8(obj, o0, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptQueueEntryKind9(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248F90;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind9(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptQueueEntryKind11(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    f32 out;
    InitScriptValue(&q);
    kinds = 1;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind11(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptQueueEntryKind12(ScriptValue* ret, EntryQueue* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddQueueEntryKind12(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* StartScriptColorFade(ScriptValue* ret, BaseObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    StartColorFade(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* PlayScriptGaugeModeObjectTarget(ScriptValue* ret, GaugeModeObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    PlayGaugeModeObjectTarget(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptGaugeModeObjectTarget(ScriptValue* ret, GaugeModeObject* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 6;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetGaugeModeObjectTarget(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* PlaceScriptModeColliderAtAnchor(ScriptValue* ret, ModeCollider* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    PlaceModeColliderAtAnchor(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptTempoAgentPendingTimeline(ScriptValue* ret, TempoAgent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetTempoAgentPendingTimeline(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* EndScriptHeldTimeline(ScriptValue* ret, TempoAgent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    EndHeldTimeline(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptC13Entry(ScriptValue* ret, TempoAgent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248F98;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddTempoAgentEntry(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* RemoveScriptTempoAgentEntry(ScriptValue* ret, TempoAgent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)RemoveTempoAgentEntry(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* DecrementScriptTempoAgentGauge(ScriptValue* ret, TempoAgent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    DecrementTempoAgentGauge(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AppendScriptTimelineKind0Entry(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    s32 o0;
    f32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds3*)D_00248FA0;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o0, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AppendTimelineKind0Entry(obj, o0, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AppendScriptTimelineKind1Entry(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    s32 o0;
    f32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds3*)D_00248FB0;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o0, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AppendTimelineKind1Entry(obj, o0, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AppendScriptTimelineKind2Entry(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 n;
    f32 out;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248FC0;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &n, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AppendTimelineKind2Entry(obj, n, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AppendScriptTimelineKind3Entry(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 n;
    f32 out;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248FC0;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &n, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AppendTimelineKind3Entry(obj, n, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AppendScriptTimelineKind4Entry(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 n;
    f32 out;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248FC0;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &n, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AppendTimelineKind4Entry(obj, n, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AppendScriptTimelineKind5Entry(ScriptValue* ret, Timeline* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 n;
    f32 out;
    InitScriptValue(&q);
    kinds = *(Kinds2*)D_00248FC0;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &n, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AppendTimelineKind5Entry(obj, n, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptGaugeBarAgentValues(ScriptValue* ret, GaugeBarAgent* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    s32 o0;
    s32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds3*)D_00248FC8;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o0, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetGaugeBarAgentValues(obj, o0, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SendScriptHitCountColliderRequest(ScriptValue* ret, HitCountCollider* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SendHitCountColliderRequest(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptHitCountColliderId(ScriptValue* ret, HitCountCollider* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)AddHitCountColliderId(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptHitCountColliderItem(ScriptValue* ret, HitCountCollider* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    s32 out;
    InitScriptValue(&q);
    kinds = 0x2000;
    (void)StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)func_001C41A0(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* TakeScriptCountedColliderTouch(ScriptValue* ret, CountedCollider* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 o0;
    s32 o1;
    InitScriptValue(&q);
    (void)StoreScriptArgumentsVa(&t, 2, args, (kinds = *(Kinds2*)D_00248FD8, &kinds), &o0, &o1);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    TakeCountedColliderTouch(obj, o0, o1);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

INCLUDE_ASM(func_00109488);
