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
#include "state_walker_group.h"
#include "scaling_volume.h"
#include "state_reset_object.h"
#include "step_sequence.h"
#include "camera.h"
#include "transform_object.h"
#include "object_sub_group.h"
#include "animation.h"
#include "state_graph.h"
#include "aim_blend_grid.h"
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
s32 AddStateTriggerTableEntry(StateTrigger* self, s32 a1, s32 a2, s32 a3, s32 a4); // stays non-void: the C definition is void, and the caller here uses the value it leaves in the register
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
void ApplyChildGroupRepulsion(void*);
s32 SetTriggerZoneEntry(TriggerZone* self, s32 a1, s32 a2, s32 a3, s32 a4); // stays non-void: the C definition is void, and the caller here uses the value it leaves in the register
s32 SetZoneColliderEntry(ZoneCollider* self, s32 a1, s32 a2, s32 a3, s32 a4); // stays non-void: the C definition is void, and the caller here uses the value it leaves in the register
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
s32 IsPointInsideObjectFaces(void*,void*);
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
void BuildPathSpeedProfile(void* a0, s32 a1, f32 x);
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
void InvokeNumberedItemCollect(void* p);
void AddEntryRecordKey(C17* p, s32 a, s32 b);
void SetAimBlendGridVector(AimBlendGrid* value, f32 x, f32 y, f32 z);
void SetAimBlendGridVectorFlagged(AimBlendGrid* self, f32 x, f32 y, f32 z);
s32 AddObjectPoolEntry(ObjectPool* self, s32 a1, s32 a2, s32 a3, s32 a4); // stays non-void: the C definition is void, and the caller here uses the value it leaves in the register
void EnableObjectPoolEntry(void*,s32);
void DisableObjectPoolEntry(void*,s32);
void SetObjectPoolEntryCount(ObjectPool* p, s32 a, s32 b);
void ChooseObjectPoolItem(void*);
s32 LaunchChosenPoolObject(void* obj, s32 v);
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
void PlaceHitCountColliderItem(void* self, s32 value);
void ForceAgentState(Agent* p, s32 a, s32 b);
void SetAgentStateClipId(Agent* self, s32 a, s32 b);
void SetAgentStateClip(Agent* self, s32 a, s32 b);
void* GetAgentStateClip(void* obj, s32 v);
void AddAgentExtraClip(Agent* self, s32 a, s32 b);
void SetAgentSecondaryClipId(Agent* p, s32 a, s32 b);
void AddAgentMeshKey(Agent* self, s32 a, s32 b);
s32 AddAgentClipGroup(Agent* self, s32 a1, s32 a2, s32 a3, s32 a4); // stays non-void: the C definition is void, and the caller here uses the value it leaves in the register
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
s32 AddStateResetEntry(StateResetObject* self, s32 a1, s32 a2, s32 a3, s32 a4);
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
ScriptValue* SetScriptAimBlendGridVector(ScriptValue* ret, AimBlendGrid* obj, s32 unused, ScriptValue* args);
ScriptValue* SetScriptAimBlendGridVectorFlagged(ScriptValue* ret, AimBlendGrid* obj, s32 unused, ScriptValue* args);
ScriptValue* ResetScriptCollectedItems(ScriptValue* ret, PooledHolder* obj, s32 unused, ScriptValue* args);
ScriptValue* CollectScriptItem(ScriptValue* ret, PooledHolder* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptContactListId(ScriptValue* ret, ContactListObject* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptContactListKind(ScriptValue* ret, ContactListObject* obj, s32 unused, ScriptValue* args);
ScriptValue* AddScriptStateResetEntry(ScriptValue* ret, StateResetObject* obj, s32 unused, ScriptValue* args);
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
ScriptValue* QueueScriptWalkerActivationOnPlayer(ScriptValue* ret, StateWalkerGroup* obj, s32 unused, ScriptValue* args);
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
ScriptValue* TestScriptPointInsideFaceTreeObject(ScriptValue* ret, ScalingVolume* obj, s32 unused, ScriptValue* args);
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
    InvokeNumberedItemCollect(obj);
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
    ApplyChildGroupRepulsion(obj);
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

ScriptValue* SetScriptAimBlendGridVector(ScriptValue* ret, AimBlendGrid* obj, s32 unused, ScriptValue* args)
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
    SetAimBlendGridVector(obj, o0, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptAimBlendGridVectorFlagged(ScriptValue* ret, AimBlendGrid* obj, s32 unused, ScriptValue* args)
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
    SetAimBlendGridVectorFlagged(obj, o0, o1, o2);
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

ScriptValue* AddScriptStateResetEntry(ScriptValue* ret, StateResetObject* obj, s32 unused, ScriptValue* args)
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
    s32 flag = LaunchChosenPoolObject(obj, out);
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

ScriptValue* QueueScriptWalkerActivationOnPlayer(ScriptValue* ret, StateWalkerGroup* obj, s32 unused, ScriptValue* args)
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

ScriptValue* TestScriptPointInsideFaceTreeObject(ScriptValue* ret, ScalingVolume* obj, s32 unused, ScriptValue* args)
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
    SetScriptValueBool(&q, IsPointInsideObjectFaces(obj, &vec));
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
    BuildPathSpeedProfile(obj, a, b);
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
    (void)PlaceHitCountColliderItem(obj, out);
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

// FillObjectPropertyTable (func_00109488) fills the 1,179 property descriptors of D_002505D8, one
// after another: the kind of value, the flags, then what the flags ask for (a field's offset or a
// function for reading, the script built-in, the same for writing, the field's offset, the
// function that finds the object holding the field), and last the default value. An entry
// stores only the fields it uses; the table starts as zeros.
//
// The entries are plain assignments, field by field in this order, and a descriptor that reads
// and calls the same function sets both fields in one assignment. That is what retail's code
// shows (docs/toolchain/long-block-constants.md, "The source form of func_00109488"): each
// constant is set just before its store, so the instruction counts that place CSE's flushes
// (every 1,001 insns in a block this long) are those of statements, not of a helper's
// arguments.

// The getters, setters and target functions of other files that the table names, declared as
// their files define them, after the types of theirs that this file does not use otherwise
// (U128 is placed_object.cpp's 128-bit word).
struct ConeVolume;
struct CountdownCollider;
struct FlaggedObject;
struct GaugeManager;
struct IdFilterObject;
struct IdLinkedObject;
struct IdLookupObject;
struct ObjectCycler;
struct PairController;
struct Pk8_2195;
struct Point2;
struct PointGraphObject;
struct RampProfile;
struct ScaledOffsetObject;
struct ScriptListBuilder;
struct TimedValue;
typedef u64 U128 __attribute__((mode(TI)));

void GetObjectClassId(BaseObject* self, s32* out);
void AddObjectKeyIfLevelInRange(void* self, void* target);
void GetObjectAttached(void* a0, s32* out);
void GetObjectAliasId(void* self, s32* out);
void StorePlacedObjectLocalVelocity();
void StorePlacedObjectLocalSpin();
AnimationStart* EnsureTimerRecord(PlacedObject* self);
s32 GetPlacedObjectFrozen(PlacedObject* self, s32* out);
void GetRotationDegrees(PlacedObject* self, f32* out);
void SetRotationDegrees(PlacedObject* self, f32* src);
void GetPlacedObjectLocalVelocity();
void SetPlacedObjectLocalVelocity(PlacedObject* self, Vec02* v);
void GetPlacedObjectScaleXY(PlacedObject* self, f32* out);
void SetPlacedObjectScaleXY(PlacedObject* self, f32 x);
void GetPlacedObjectScaleZ(PlacedObject* self, f32* out);
void SetPlacedObjectScaleZ(PlacedObject* self, f32 x);
void GetRangeRecordPresent(PlacedObject* self, s32* out);
void SetRangeRecordPresent(PlacedObject* self, s32 flag);
void GetRangeRecordKeyValue(PlacedObject* self, s32* out);
void SetRangeRecordKey(void* self, s32 value);
void GetRangeRecordNear(void* self, f32* out);
void SetRangeRecordNear(void* self, f32 x);
void GetRangeRecordFar(void* self, f32* out);
void SetRangeRecordFar(f32 x);
void GetRangeRecordInner(void* self, f32* out);
void SetRangeRecordInner(f32 x);
void GetRangeRecordOuter(PlacedObject* self, f32* out);
void SetRangeRecordOuter(f32 x);
void GetRangeRecordAngle(void* self, f32* out);
void SetRangeRecordInnerAndOuter(f32 x);
void GetRangeRecordVector(void* self, Vec02* out);
void SetRangeRecordVector(void* self, void* src);
void SetRangeRecordCode(void* self, s32 value);
void SetGroupActivityModeEnabled(void* self, s32 a1);
void GetGroupActivityMode(PlacedObject* self, u32* out);
void SetGroupActivityMode(void* self, s32 flag);
void SetPositionSourceEnabled(void* self, s32 value);
extern void SetPositionSourceMode(void*, s32);
void SetScaledPositionSpring(void* o, f32 v);
void SetPositionSpring(void* self, U128* v);
void SetScaledVelocitySpring(void* self, void* src);
void SetVelocitySpring(void* self, U128* src);
void SetOrientationSourceEnabled(void* self, s32 a1);
void SetOrientationSourceMode(void* self, s32 a1);
void SetBaseAttachmentSortKey(PlacedObject* self, s32 value);
void SetScaledRotationSpring(void* o, f32 v);
void SetRotationSpring(PlacedObject* self, U128* src);
void SetScaledSpinSpring(PlacedObject* self, void* src);
void SetSpinSpring(PlacedObject* self, U128* src);
void SetScaledPositionRamp(PlacedObject* self, f32 scale);
void SetPositionRamp(PlacedObject* self, RampProfile* src);
void SetScaledRotationRamp(void* self, f32 s);
void SetRotationRamp(void* self, f32* v);
void SetPositionRampAccelScale(PlacedObject* self, f32 scale);
void SetRotationRampAccelScale(PlacedObject* self, f32 scale);
void SetDefaultPositionMode(void* self, s8 value);
void SetDefaultOrientationMode(void* self, s8 value);
void SetAimOrientationMode(PlacedObject* self, s32 value);
void GetAimRange(PlacedObject* self, f32* out);
void SetAimRange(PlacedObject* self, f32 f);
void GetAimYawCurve(PlacedObject* self, Quad16* out);
void SetAimYawCurve(PlacedObject* self, Vec02* src);
void GetAimYawLimits(PlacedObject* self, U64P* out);
void SetAimYawLimits(PlacedObject* self, Pk8_2195* src);
void GetAimPitchCurve(PlacedObject* self, Quad16* out);
void SetAimPitchCurve(PlacedObject* self, Vec02* src);
void GetAimPitchLimits(PlacedObject* self, U64P* out);
void SetAimPitchLimits(PlacedObject* self, Pk8_2195* src);
void GetAimNearKey(PlacedObject* self, s32* out);
void SetAimNearKey(PlacedObject* self, s32 v);
void GetAimFarKey(PlacedObject* self, s32* out);
void SetAimFarKey(PlacedObject* self, s32 value);
void GetAimTargetId(PlacedObject* self, s32* out);
void SetAimTargetId(PlacedObject* self, s32 value);
void GetAimTarget(PlacedObject* self, void** out);
void SetAimTarget(void* self, void* v);
s32 TestChildrenAccepted(PlacedObject* self, ScriptListBuilder* context);
void SetClass75ObjectCount(PlacedObject* self, s32 value);
void SetClass75ObjectScale(void* self, f32 value);
void SetClass75ObjectField90(void* self, void* value);
void SetObjectRecordValue(PlacedObject* state, u32 value);
void SetObjectTreeRecordValue(ModeCollider* o, u32 value);
void GetColorPreset(PlacedObject* self, s32* out);
void SetColorPreset(PlacedObject* self, s32 a1);
void GetColorRecordFirstColor(PlacedObject* self, Quad16* out);
void SetColorRecordFirstColor(PlacedObject* self, Quad16* input);
void GetColorRecordSecondColor(PlacedObject* self, Quad16* out);
void SetColorRecordSecondColor(PlacedObject* self, Quad16* input);
void GetColorRecordFactor(PlacedObject* self, f32* out);
void SetColorRecordFactor(PlacedObject* self, f32 value);
void GetSoundRecordId(PlacedObject* self, s32* out);
void RestartSoundWithId(PlacedObject* self, void* value);
void SetSoundRecordId(PlacedObject* self, s32 value);
void GetSoundOuterRange(PlacedObject* self, f32* out);
void SetSoundOuterRange(PlacedObject* self, f32 value);
void GetSoundInnerRange(PlacedObject* self, f32* out);
void SetSoundInnerRange(PlacedObject* self, f32 value);
void GetSoundRecordScale(PlacedObject* self, f32* out);
void SetPlayingSoundVolume(PlacedObject* self);
void SetSoundRecordScale(PlacedObject* self, f32 f);
void GetSoundStartPitch(PlacedObject* self, f32* out);
void SetPlayingSoundPitch(PlacedObject* self);
void SetSoundStartPitch(PlacedObject* self, f32 f);
void GetSoundRecordPair(PlacedObject* self, U64P* out);
void SetSoundRecordPair(PlacedObject* self, U64P* src);
void GetSoundStartParam(PlacedObject* self, f32* out);
void SetSoundStartParam(PlacedObject* self, f32 value);
void GetTintRgb(PlacedObject* self, s32* out);
void SetTintRgb(PlacedObject* self, s32 v);
void GetTintByte0(PlacedObject* self, s32* out);
void SetTintByte0(PlacedObject* self, s32 v);
void GetTintByte1(PlacedObject* self, s32* out);
void SetTintByte1(PlacedObject* self, u8 value);
void GetTintByte2(PlacedObject* self, s32* out);
void SetTintByte2(PlacedObject* self, s32 v);
void GetTintByte3(PlacedObject* self, s32* out);
void SetTintByte3(PlacedObject* self, s32 value);
void GetTintByte4(PlacedObject* self, s32* out);
void SetTintByte4(PlacedObject* self, u8 v);
void SelectValueEntryByKey(Collider* t, s32 key);
void SetPlacedObjectFrameStepClock(PlacedObject* self, s32 flag);
void SetObjectCameraTracked(PlacedObject* self, s32 flag);
void GetPlacedObjectSpecialFlag(PlacedObject* ctx, s32* out);
void SetPlacedObjectSpecialFlag(PlacedObject* ctx, s32 on);
void SetColliderMass(Collider* self, f32 v);
void SetColliderSurfaceKind(Collider* self, u8 value);
void ResetColliderAnchors(void* self);
void SetColliderTurnAnchorPreset(Collider* self, s32 index);
void SetColliderMoveAnchorPreset(Collider* self, s32 index);
void SetColliderOverrideRadius(Collider* self, f32 v);
void SetColliderFlagBit47(Collider* self, u32 value);
void SetColliderFlagBit48(Collider* self, s32 flag);
void SetColliderGravityDisabled(Collider* self, s32 flag);
void SetColliderTreeContactsDropped(Collider* self, s32 value);
void SetColliderContactsDropped(Collider* self, s32 value);
void SetColliderKindContactsDropped(Collider* self, s32 value);
s32 CollectContactingPartsToScriptList(Collider* self, s32 value);
void SetColliderFlagNibble32(Collider* self, u32 value);
void GetColliderFlagBit52(Collider* self, u32* out);
void SetColliderFlagBit52(Collider* self, u32 flag);
s32 GetObjectWorldPosition(void* obj, void* out);
s32 GetObjectWorldRotation(void* obj, void* out);
void StoreValueAndMarkSet(TimedValue* self, f32 value);
void SetObjectSubGroupState(ObjectSubGroup* self, s32 state);
void ConvertPositionToWorld(void* n, void* out);
void SetAnimationPlayerSpeed(AnimationPlayer* t, f32 x);
void SetAnimationPlayerSpeedScale(AnimationPlayer* self, f32 x);
void SetAttachmentSortKeys(AnimationPlayer* owner, s32 value);
void SetAnimationPlayerPadSelect(AnimationPlayer* self, s32 v);
void AddTrackedKey(Rec36* self, void* entry);
void* GetAttachedSetTrackedNodes(AttachedSet* self);
void AddTrackedNode(Rec36* self, BaseObject* e);
void RemoveTrackedNode(Rec36* self, s32 value);
void AddMaskedColliderKeyKind0(MaskedCollider* q, s32 value);
void AddMaskedColliderKeyKind1(MaskedCollider* q, s32 value);
void AddMaskedColliderKeyKind2(MaskedCollider* self, s32 value);
void AddMaskedColliderKeyKind3(MaskedCollider* q, s32 value);
void AddAcceptedObjectId(MaskedCollider* obj, s32 value);
void AddAcceptedKind(MaskedCollider* r, s32 value);
void AddMaskedColliderListEntry(MaskedCollider* obj, s32 value);
void GetAcceptsPlayer(MaskedCollider* state, s32* result);
void SetAcceptsPlayer(MaskedCollider* self, s32 enabled);
void GetAcceptsFlaggedObjects(MaskedCollider* state, s32* result);
void SetAcceptsFlaggedObjects(MaskedCollider* self, s32 enabled);
void SetObjectHold(MaskedCollider* self, s32 v);
void* GetMaskedColliderSoundParams(MaskedCollider* self);
void SetTimedState(Collider* c, s32 state);
void AppendTriggerZoneFirstQueue(u8* self, s32 value);
void AppendTriggerZoneSecondQueue(TriggerZone* self, int value);
void AddIncludedId(TriggerZone* list, s32 value);
void AddExcludedId(TriggerZone* self, s32 value);
void AddIncludedKind(TriggerZone* self, s32 value);
void AddExcludedKind(TriggerZone* self, void* value);
void SetTriggerZoneMode(TriggerZone* state);
void AppendZoneColliderFirstQueue(void* self, int value);
void AppendZoneColliderSecondQueue(void* self, void* b);
void AddZoneColliderId(void* self, void* value);
s32 TestListedEntriesAccepted(ZoneCollider* self, void* arg);
void SetZoneColliderMode(ZoneCollider* self, s32 flag);
void SetSwitchedColliderEnabled(Agent* self, s32 a);
void StoreSwitchedColliderAccepted(SwitchedCollider* self, s32* out);
void AddLookupId(IdLookupObject* obj, s32 value);
void AddObjectSetKey(ObjectSet* queue, void* item);
void AddStateTriggerCountedId(StateTrigger* self, s32 value);
void AddStateTriggerItemId(StateTrigger* self, s32 value);
void AddStateTriggerAgentId(StateTrigger* self, s32 value);
s32 TestStateTriggerItemsAccepted(StateTrigger* self, void* arg);
void AddTimedObjectAcceptedObjectId(TimedObject* self, s32 value);
void AddTimedObjectExcludedObjectId(TimedObject* self, s32 item);
void AddTimedObjectAcceptedClassId(TimedObject* self, s32 item);
void AddTimedObjectExcludedClassId(TimedObject* q, u32 value);
void AddIdFilterObjectId(IdFilterObject* a0, s32 a1);
void AddIdFilterClassId(IdFilterObject* obj, s32 value);
void SetEffectSpawnerLimit(EffectSpawner* self, s32 a1);
void SetEffectSpawnerContinuous(EffectSpawner* a0, s32 a1);
EffectSpawner* MarkEffectSpawnerChanged(EffectSpawner* self, s32 value);
void GetEffectSpawnerInactive(EffectSpawner* self, s32* out);
void SetEffectSpawnerDisabled(EffectSpawner* self, s32 a1);
void GetEffectSpawnerActive(void* self,s32* out);
void* GetOwnSpawnRecord(void* a0, s32 a1);
void SetEffectSpawnerKind(void* a0, s32 a1);
void SetOwnedSpawnRecordKind(void* a0, s32 a1);
s32 GetOrCreateSoundParams(void* self);
void SetConeVolumeMode(ConeVolume* self, s32 flag);
void SetConeVolumeColor(void* self, void* a1);
void SetConeVolumeSecondLevel(ConeVolume* self, f32 v);
void SetConeVolumeThirdLevel(ConeVolume* self, f32 v);
void SetConeVolumeFirstAngle(ConeVolume* self, f32 v);
void SetConeVolumeSecondAngle(ConeVolume* self, f32 v);
void SetConeVolumeThirdAngle(ConeVolume* self, f32 v);
void SetConeVolumeDirection(ConeVolume* self, Quad16* dir);
void SetConeVolumeValue(ConeVolume* self, s32 v);
void SetConeVolumeRange(ConeVolume* self, U64P* src);
void SetConeVolumeOuterAngle(ConeVolume* self, f32 v);
void SetConeVolumeInnerAngle(ConeVolume* self, f32 v);
void SetConeVolumeVector340(ConeVolume* self, Quad16* src);
void GetConeVolumeSecondLevel(ConeVolume* self, f32* out);
void SetConeVolumeOuterLevels(ConeVolume* self, f32 v);
void GetConeVolumeColorRgb(u8* self);
void SetConeVolumeColorRgb(void* self, void* a1);
void GetStateWalkerTargetKey(StateWalker* a0, s32* out);
void SetStateWalkerTarget(void* dev, s32 value);
void GetStateWalkerCurrentKey(StateWalker* a0, s32* out);
void GetStateWalkerNextKey(StateWalker* self, s32* out);
void SetStateWalkerSpeed(StateWalker* self, f32 v);
void TeleportStateWalker(void* h, s32 arg);
void SetWorldLightingParamA(World* self, f32 v);
void SetWorldLightingParamB(World* self, f32 v);
void SnapCurrentCameraZoom(void);
void SetCurrentCameraNearDistance(void);
void SetCurrentCameraFarDistance(void);
void SetCurrentCameraFogNear(void);
void SetCurrentCameraFogFar(void);
void SetCurrentCameraFogStrength(void);
void SetCurrentCameraFogColor(void);
void SetCurrentCameraDistanceScale(void);
void SetWorldSoundLevel(void* self, f32 x);
void SetWorldValueAndTarget(World* self, f32 v);
void SetWorldValueTarget(World* self, f32 value);
void* GetScatterController(void);
void GetGameStateDeltaTime(void* unused, f32* out);
void SetScatterLevelBuiltin(void);
void GetCurrentScatterLevel(void* unused, f32* out);
void SetCurrentScatterLevel();
void AddWorldSoundEntry(World* self, s32 key);
void SetLastWorldSoundEntryFromPoint(World* self, Point2* p);
void SetLastWorldSoundEntryValues(World* self, U64P* item);
void GetHasStreamVoice(void* self, s32* out);
void GetSaveSpareCount(void* self, s32* out);
void GetReserveUnitCount(void* unused, s32* out);
void SetCameraPosition(void* self, void* value);
void SetCameraOrientation(void* arg, void* arg2);
void SnapCameraZoom(void* self);
void SetCameraNearDistance(void* arg);
void SetCameraFarDistance(void* self);
extern void SetCameraFogNear(void*);
extern void SetCameraFogFar(void*);
extern void SetCameraFogStrength(void*);
void SetCameraDistanceScale(void* arg);
void* GetContactTrackerRecord(void* self);
void AppendFlaggedObjectIdB(FlaggedObject* q, s32 value);
void AppendFlaggedObjectIdA(FlaggedObject* obj, void* item);
void SetFlaggedChildId(FlaggedObject* self, s32 value);
void GetNumberedItemFlag(void* obj, s32* out);
void SetOffsetScale(ScaledOffsetObject* self, f32 v);
void SetAgentPathObjectId(Agent* self, s32 index);
void SetAgentAngleLimitDegrees(Agent* self, f32 value);
void StoreAgentTarget(Agent* self, s32* out);
void SetAgentSecondaryTarget(Agent* self, s32 value);
void SetAgentMemberGroupId(Agent* self, s32 v);
void SetAgentTargetSetId(Agent* self, s32 v);
void IsAgentNearPathEnd(Agent* self, s32* out);
void AddOwnedWantedId(ItemKeeper* self, s32 value);
void AddListedWantedId(ItemKeeper* self, s32 value);
void AddCompanionAgentExcludedId(CompanionAgent* self, s32 value);
void ScaleTurningColliderRamp(void* self, f32 x);
void SetTurningColliderGravityScale(void* self, f32 v);
s32 GetChildGroupSoundParams(ChildGroupObject* self);
void SetPlayerPadSelectMode(Player* a0, s32 a1);
void SetPlayerProbeContactsDisabled(Player* self, s32 value);
void SetPairControllerFirstTemplateId(PairController* obj, s32 value);
void SetPairControllerSecondTemplateId(PairController* obj, s32 value);
void SetPairControllerHostId(u8* self, s32 value);
void SetPairControllerExtraId(PairController* obj, s32 value);
void AppendPairControllerId(PairController* list, s32 value);
void* GetPairControllerPose(void* self);
void SetPooledObjectState(PooledObject* self, s32 state);
void AddPooledHolderItem(PooledHolder* self, void* item);
void SetOnOffObjectBlockValue(OnOffObject* self, f32 value);
void SetOnOffObjectForcedState(void* p, s32 n);
void FollowObjectById(TargetFollower* self, void* x);
void* GetObjectPoolShare(void* self);
void SetObjectCyclerState(ObjectCycler* self, s32 x);
void SetStepSequenceState(void* obj, s32 mode);
void ReadSequenceTarget(StepSequence* self, s32* out);
void WriteSequenceTarget(StepSequence* self, s32 value);
void SetObjectLinkId(IdLinkedObject* self, s32 v);
void AddStateWalkerGroupId(StateWalkerGroup* queue, void* item);
void SetStateWalkerGroupMaskBit(StateWalkerGroup* flags, u32 bit);
void* GetOscillatorEntryForPeriod(void* self, s32 mode);
void GetOscillatorEntryPeriod(void* self, f32* out);
void SetOscillatorEntryPeriod(void* self, f32 x);
void* GetOscillatorEntryForVectors(void* self, s32 mode);
void GetGaugeAgentLevelFactor(GaugeAgent* a0, f32* a1);
void SetTintBlendColliderState(void* self, s32 flag);
void AddPlayerLinkedColliderId(PlayerLinkedCollider* self, void* value);
void AppendGaugeSlot(GaugeManager* self, s32 value);
void* GetGaugeParams(GaugeManager* self);
void SetPathFollowerPath(PathFollower* self, PathCurveObject* arg);
void SetPathFollowerSecondPath(u8* self, PathCurveObject* obj);
void SetPathFollowerMode(void* self, s32 mode);
void SetSeekingAgentStateTarget(SeekingAgent* self, s32 value);
void SetSeekingAgentTarget(SeekingAgent* self, s32 value);
void PickRandomPointOnPointGraph(PointGraphObject* self, Vec02* out);
void SetModeWalkerMode(ModeWalker* self, s32 n);
void SetGaugeModeObjectMode(GaugeModeObject* self, s32 a1);
s32 PlayGaugeModeObjectLoop(GaugeModeObject* self, s32 a1);
void SetCountdownState(CountdownCollider* self, s32 state);
void SetTempoAgentTempo(TempoAgent* self, s32 v);
void SetTempoAgentSpanBeats(TempoAgent* self, s32 v);
void SetHitCountColliderState(void* self, s32 flag);

void FillObjectPropertyTable()
{
    PropertyDescriptor* p = D_002505D8;

    p->type = 7; p->flags = 0x4; p->getter = (s32)GetObjectClassId; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (s32)TestScriptObjectOfKind; p->putter = 1; p++;
    p->type = 18; p->flags = 0x401; p->getter = (s32)AddScriptObjectKeyToOwner; p->f10 = (s32)RemoveScriptObjectFromParentList; p->putter = 0; p++;
    p->type = 10; p->flags = 0x100; p->offset = (s32)AddObjectKeyIfLevelInRange; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)AddScriptObjectToParentList; p->putter = 0; p++;
    p->type = 8193; p->flags = 0x1; p->getter = 0; p->f10 = (s32)CreateScriptObjectCopy; p->putter = 2; p++;
    p->type = 8300; p->flags = 0x2; p->getter = 20; p++;
    p->type = 0; p->flags = 0x4; p->getter = (s32)GetObjectAttached; p++;
    p->type = 8194; p->flags = 0x2; p->getter = 24; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ReparentScriptObject; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (s32)TestScriptObjectDescendantOf; p->putter = 1; p++;
    p->type = 6; p->flags = 0x2; p->getter = 8; p++;
    p->type = 6; p->flags = 0x4; p->getter = (s32)GetObjectAliasId; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (s32)TestScriptObjectIdMatch; p->putter = 1; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)SetScriptExtraObjectPropertyBool; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)SetScriptExtraObjectPropertyInt; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)SetScriptExtraObjectPropertyFloat; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)SetScriptExtraObjectPropertyVectorB; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)SetScriptExtraObjectPropertyPair; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)SetScriptExtraObjectPropertyWord; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)SetScriptExtraObjectPropertyVectorA; p->f10 = 0; p->putter = 2; p++;
    p->type = 2; p->flags = 0x100; p->offset = (s32)StorePlacedObjectLocalVelocity; p++;
    p->type = 2; p->flags = 0x100; p->offset = (s32)StorePlacedObjectLocalSpin; p++;
    p->type = 6; p->flags = 0x1080; p->offset = 4; p->target = (PropertyTarget)EnsureTimerRecord; p++;
    p->type = 1; p->flags = 0x1080; p->offset = 12; p->target = (PropertyTarget)EnsureTimerRecord; p++;
    p->type = 1; p->flags = 0x1080; p->offset = 16; p->target = (PropertyTarget)EnsureTimerRecord; p++;
    p->type = 4172; p->flags = 0x1080; p->offset = 8; p->target = (PropertyTarget)EnsureTimerRecord; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ClearScriptObjectRecordValues; p->putter = 0; p++;
    p->type = 0; p->flags = 0x4; p->getter = (s32)GetPlacedObjectFrozen; p++;
    p->type = 2; p->flags = 0x42; p->getter = 256; p->putter = 132; p++;
    p->type = 2; p->flags = 0x12; p->getter = 400; p->putter = 400; p++;
    p->type = 2; p->flags = 0x2; p->getter = 320; p++;
    p->type = 4; p->flags = 0x42; p->getter = 208; p->putter = 136; p++;
    p->type = 4; p->flags = 0x12; p->getter = 416; p->putter = 416; p++;
    p->type = 4; p->flags = 0x2; p->getter = 272; p++;
    p->type = 2; p->flags = 0x124; p->getter = (s32)GetRotationDegrees; p->putter = (s32)SetRotationDegrees; p->offset = (s32)SetRotationDegrees; p++;
    p->type = 2; p->flags = 0x24; p->getter = (s32)GetPlacedObjectLocalVelocity; p->putter = (s32)SetPlacedObjectLocalVelocity; p++;
    p->type = 2; p->flags = 0x42; p->getter = 352; p->putter = 148; p++;
    p->type = 2; p->flags = 0x2; p->getter = 368; p++;
    p->type = 2; p->flags = 0x2; p->getter = 384; p++;
    p->type = 8194; p->flags = 0x2; p->getter = 80; p++;
    p->type = 1; p->flags = 0x124; p->getter = (s32)GetPlacedObjectScaleXY; p->putter = (s32)SetPlacedObjectScaleXY; p->offset = (s32)SetPlacedObjectScaleXY; p++;
    p->type = 1; p->flags = 0x124; p->getter = (s32)GetPlacedObjectScaleZ; p->putter = (s32)SetPlacedObjectScaleZ; p->offset = (s32)SetPlacedObjectScaleZ; p++;
    p->type = 0; p->flags = 0x124; p->getter = (s32)GetRangeRecordPresent; p->putter = (s32)SetRangeRecordPresent; p->offset = (s32)SetRangeRecordPresent; p++;
    p->type = 6; p->flags = 0x124; p->getter = (s32)GetRangeRecordKeyValue; p->putter = (s32)SetRangeRecordKey; p->offset = (s32)SetRangeRecordKey; p++;
    p->type = 1; p->flags = 0x124; p->getter = (s32)GetRangeRecordNear; p->putter = (s32)SetRangeRecordNear; p->offset = (s32)SetRangeRecordNear; p++;
    p->type = 1; p->flags = 0x124; p->getter = (s32)GetRangeRecordFar; p->putter = (s32)SetRangeRecordFar; p->offset = (s32)SetRangeRecordFar; p++;
    p->type = 1; p->flags = 0x124; p->getter = (s32)GetRangeRecordInner; p->putter = (s32)SetRangeRecordInner; p->offset = (s32)SetRangeRecordInner; p++;
    p->type = 1; p->flags = 0x124; p->getter = (s32)GetRangeRecordOuter; p->putter = (s32)SetRangeRecordOuter; p->offset = (s32)SetRangeRecordOuter; p++;
    p->type = 1; p->flags = 0x124; p->getter = (s32)GetRangeRecordAngle; p->putter = (s32)SetRangeRecordInnerAndOuter; p->offset = (s32)SetRangeRecordInnerAndOuter; p++;
    p->type = 2; p->flags = 0x124; p->getter = (s32)GetRangeRecordVector; p->putter = (s32)SetRangeRecordVector; p->offset = (s32)SetRangeRecordVector; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)SetRangeRecordCode; p++;
    p->type = 0; p->flags = 0x120; p->putter = (s32)SetGroupActivityModeEnabled; p->offset = (s32)SetGroupActivityModeEnabled; p++;
    p->type = 4196; p->flags = 0x124; p->getter = (s32)GetGroupActivityMode; p->putter = (s32)SetGroupActivityMode; p->offset = (s32)SetGroupActivityMode; p++;
    p->type = 0; p->flags = 0x100; p->offset = (s32)SetPositionSourceEnabled; p++;
    p->type = 4110; p->flags = 0x100; p->offset = (s32)SetPositionSourceMode; p++;
    p->type = 1; p->flags = 0x120; p->putter = (s32)SetScaledPositionSpring; p->offset = (s32)SetScaledPositionSpring; p++;
    p->type = 9; p->flags = 0x120; p->putter = (s32)SetPositionSpring; p->offset = (s32)SetPositionSpring; p++;
    p->type = 1; p->flags = 0x120; p->putter = (s32)SetScaledVelocitySpring; p->offset = (s32)SetScaledVelocitySpring; p++;
    p->type = 9; p->flags = 0x120; p->putter = (s32)SetVelocitySpring; p->offset = (s32)SetVelocitySpring; p++;
    p->type = 0; p->flags = 0x100; p->offset = (s32)SetOrientationSourceEnabled; p++;
    p->type = 4110; p->flags = 0x100; p->offset = (s32)SetOrientationSourceMode; p++;
    p->type = 5; p->flags = 0x120; p->putter = (s32)SetBaseAttachmentSortKey; p->offset = (s32)SetBaseAttachmentSortKey; p++;
    p->type = 1; p->flags = 0x120; p->putter = (s32)SetScaledRotationSpring; p->offset = (s32)SetScaledRotationSpring; p++;
    p->type = 9; p->flags = 0x120; p->putter = (s32)SetRotationSpring; p->offset = (s32)SetRotationSpring; p++;
    p->type = 1; p->flags = 0x120; p->putter = (s32)SetScaledSpinSpring; p->offset = (s32)SetScaledSpinSpring; p++;
    p->type = 9; p->flags = 0x120; p->putter = (s32)SetSpinSpring; p->offset = (s32)SetSpinSpring; p++;
    p->type = 1; p->flags = 0x120; p->putter = (s32)SetScaledPositionRamp; p->offset = (s32)SetScaledPositionRamp; p++;
    p->type = 12; p->flags = 0x120; p->putter = (s32)SetPositionRamp; p->offset = (s32)SetPositionRamp; p++;
    p->type = 1; p->flags = 0x120; p->putter = (s32)SetScaledRotationRamp; p->offset = (s32)SetScaledRotationRamp; p++;
    p->type = 12; p->flags = 0x120; p->putter = (s32)SetRotationRamp; p->offset = (s32)SetRotationRamp; p++;
    p->type = 1; p->flags = 0x120; p->putter = (s32)SetPositionRampAccelScale; p->offset = (s32)SetPositionRampAccelScale; p++;
    p->type = 1; p->flags = 0x120; p->putter = (s32)SetRotationRampAccelScale; p->offset = (s32)SetRotationRampAccelScale; p++;
    p->type = 4110; p->flags = 0x100; p->offset = (s32)SetDefaultPositionMode; p++;
    p->type = 4110; p->flags = 0x100; p->offset = (s32)SetDefaultOrientationMode; p++;
    p->type = 3; p->flags = 0x0; p++;
    p->type = 4110; p->flags = 0x100; p->offset = (s32)SetAimOrientationMode; p++;
    p->type = 1; p->flags = 0x124; p->getter = (s32)GetAimRange; p->putter = (s32)SetAimRange; p->offset = (s32)SetAimRange; p++;
    p->type = 9; p->flags = 0x124; p->getter = (s32)GetAimYawCurve; p->putter = (s32)SetAimYawCurve; p->offset = (s32)SetAimYawCurve; p++;
    p->type = 10; p->flags = 0x124; p->getter = (s32)GetAimYawLimits; p->putter = (s32)SetAimYawLimits; p->offset = (s32)SetAimYawLimits; p++;
    p->type = 9; p->flags = 0x124; p->getter = (s32)GetAimPitchCurve; p->putter = (s32)SetAimPitchCurve; p->offset = (s32)SetAimPitchCurve; p++;
    p->type = 10; p->flags = 0x124; p->getter = (s32)GetAimPitchLimits; p->putter = (s32)SetAimPitchLimits; p->offset = (s32)SetAimPitchLimits; p++;
    p->type = 5; p->flags = 0x124; p->getter = (s32)GetAimNearKey; p->putter = (s32)SetAimNearKey; p->offset = (s32)SetAimNearKey; p++;
    p->type = 5; p->flags = 0x124; p->getter = (s32)GetAimFarKey; p->putter = (s32)SetAimFarKey; p->offset = (s32)SetAimFarKey; p++;
    p->type = 6; p->flags = 0x104; p->getter = (s32)GetAimTargetId; p->offset = (s32)SetAimTargetId; p++;
    p->type = 8194; p->flags = 0x24; p->getter = (s32)GetAimTarget; p->putter = (s32)SetAimTarget; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ClearScriptAimHold; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptAimHold; p->putter = 0; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)SetScriptValueAttachment; p->putter = 3; p++;
    p->type = -2147475455; p->flags = 0x4; p->getter = (s32)TestChildrenAccepted; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptElementsScrollScale; p->putter = 2; p++;
    p->type = 4127; p->flags = 0x120; p->putter = (s32)SetClass75ObjectCount; p->offset = (s32)SetClass75ObjectCount; p++;
    p->type = 1; p->flags = 0x120; p->putter = (s32)SetClass75ObjectScale; p->offset = (s32)SetClass75ObjectScale; p++;
    p->type = 0; p->flags = 0x120; p->putter = (s32)SetClass75ObjectField90; p->offset = (s32)SetClass75ObjectField90; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptCrossfadeRatioDeep; p->putter = 1; p++;
    p->type = 5; p->flags = 0x120; p->putter = (s32)SetObjectRecordValue; p->offset = (s32)SetObjectRecordValue; p++;
    p->type = 5; p->flags = 0x20; p->putter = (s32)SetObjectTreeRecordValue; p++;
    p->type = 4160; p->flags = 0x124; p->getter = (s32)GetColorPreset; p->putter = (s32)SetColorPreset; p->offset = (s32)SetColorPreset; p++;
    p->type = 2; p->flags = 0x124; p->getter = (s32)GetColorRecordFirstColor; p->putter = (s32)SetColorRecordFirstColor; p->offset = (s32)SetColorRecordFirstColor; p++;
    p->type = 2; p->flags = 0x124; p->getter = (s32)GetColorRecordSecondColor; p->putter = (s32)SetColorRecordSecondColor; p->offset = (s32)SetColorRecordSecondColor; p++;
    p->type = 1; p->flags = 0x124; p->getter = (s32)GetColorRecordFactor; p->putter = (s32)SetColorRecordFactor; p->offset = (s32)SetColorRecordFactor; p++;
    p->type = 14; p->flags = 0x124; p->getter = (s32)GetSoundRecordId; p->putter = (s32)RestartSoundWithId; p->offset = (s32)SetSoundRecordId; p++;
    p->type = 1; p->flags = 0x104; p->getter = (s32)GetSoundOuterRange; p->offset = (s32)SetSoundOuterRange; p++;
    p->type = 1; p->flags = 0x104; p->getter = (s32)GetSoundInnerRange; p->offset = (s32)SetSoundInnerRange; p++;
    p->type = 1; p->flags = 0x124; p->getter = (s32)GetSoundRecordScale; p->putter = (s32)SetPlayingSoundVolume; p->offset = (s32)SetSoundRecordScale; p++;
    p->type = 1; p->flags = 0x124; p->getter = (s32)GetSoundStartPitch; p->putter = (s32)SetPlayingSoundPitch; p->offset = (s32)SetSoundStartPitch; p++;
    p->type = 10; p->flags = 0x104; p->getter = (s32)GetSoundRecordPair; p->offset = (s32)SetSoundRecordPair; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)StartScriptSoundWithParams; p->putter = 5; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)StopScriptPlayingSound; p->putter = 0; p++;
    p->type = 1; p->flags = 0x104; p->getter = (s32)GetSoundStartParam; p->offset = (s32)SetSoundStartParam; p++;
    p->type = 4163; p->flags = 0x124; p->getter = (s32)GetTintRgb; p->putter = (s32)SetTintRgb; p->offset = (s32)SetTintRgb; p++;
    p->type = 4163; p->flags = 0x124; p->getter = (s32)GetTintByte0; p->putter = (s32)SetTintByte0; p->offset = (s32)SetTintByte0; p++;
    p->type = 4163; p->flags = 0x124; p->getter = (s32)GetTintByte1; p->putter = (s32)SetTintByte1; p->offset = (s32)SetTintByte1; p++;
    p->type = 4163; p->flags = 0x124; p->getter = (s32)GetTintByte2; p->putter = (s32)SetTintByte2; p->offset = (s32)SetTintByte2; p++;
    p->type = 4163; p->flags = 0x124; p->getter = (s32)GetTintByte3; p->putter = (s32)SetTintByte3; p->offset = (s32)SetTintByte3; p++;
    p->type = 4163; p->flags = 0x124; p->getter = (s32)GetTintByte4; p->putter = (s32)SetTintByte4; p->offset = (s32)SetTintByte4; p++;
    p->type = 6; p->flags = 0x20; p->putter = (s32)SelectValueEntryByKey; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)FadeInScriptPlacedObject; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)FadeOutScriptPlacedObject; p->putter = 1; p++;
    p->type = 0; p->flags = 0x102; p->getter = 660; p->offset = (s32)SetPlacedObjectFrameStepClock; p++;
    p->type = 8339; p->flags = 0x1; p->getter = 0; p->f10 = (s32)FindScriptObjectHandle; p->putter = 1; p++;
    p->type = 8338; p->flags = 0x1; p->getter = 0; p->f10 = (s32)FindScriptObjectAnimationPlayer; p->putter = 1; p++;
    p->type = 8338; p->flags = 0x1; p->getter = 0; p->f10 = (s32)FindScriptTrackPlayer; p->putter = 0; p++;
    p->type = 0; p->flags = 0x120; p->putter = (s32)SetObjectCameraTracked; p->offset = (s32)SetObjectCameraTracked; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)CopyScriptPlacedObjectFrame; p->putter = 1; p++;
    p->type = 0; p->flags = 0x124; p->getter = (s32)GetPlacedObjectSpecialFlag; p->putter = (s32)SetPlacedObjectSpecialFlag; p->offset = (s32)SetPlacedObjectSpecialFlag; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptFollowObjects; p->putter = 2; p++;
    p->type = 1; p->flags = 0x22; p->getter = 872; p->putter = (s32)SetColliderMass; p++;
    p->type = 4111; p->flags = 0x120; p->putter = (s32)SetColliderSurfaceKind; p->offset = (s32)SetColliderSurfaceKind; p++;
    p->type = 2; p->flags = 0x92; p->getter = 848; p->putter = 848; p->offset = 848; p++;
    p->type = 0; p->flags = 0x100; p->offset = (s32)ResetColliderAnchors; p++;
    p->type = 4096; p->flags = 0x120; p->putter = (s32)SetColliderTurnAnchorPreset; p->offset = (s32)SetColliderTurnAnchorPreset; p++;
    p->type = 4096; p->flags = 0x120; p->putter = (s32)SetColliderMoveAnchorPreset; p->offset = (s32)SetColliderMoveAnchorPreset; p++;
    p->type = 1; p->flags = 0x100; p->offset = (s32)SetColliderOverrideRadius; p++;
    p->type = 1; p->flags = 0x892; p->getter = 864; p->putter = 864; p->offset = 864; p->floatValue = 0.5f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 868; p->putter = 868; p->offset = 868; p->floatValue = 1.0f; p++;
    p->type = 0; p->flags = 0x120; p->putter = (s32)SetColliderFlagBit47; p->offset = (s32)SetColliderFlagBit47; p++;
    p->type = 0; p->flags = 0x100; p->offset = (s32)SetColliderFlagBit48; p++;
    p->type = 0; p->flags = 0x120; p->putter = (s32)SetColliderGravityDisabled; p->offset = (s32)SetColliderGravityDisabled; p++;
    p->type = 0; p->flags = 0x120; p->putter = (s32)SetColliderTreeContactsDropped; p->offset = (s32)SetColliderTreeContactsDropped; p++;
    p->type = 0; p->flags = 0x120; p->putter = (s32)SetColliderContactsDropped; p->offset = (s32)SetColliderContactsDropped; p++;
    p->type = 0; p->flags = 0x120; p->putter = (s32)SetColliderKindContactsDropped; p->offset = (s32)SetColliderKindContactsDropped; p++;
    p->type = -2147475453; p->flags = 0x4; p->getter = (s32)CollectContactingPartsToScriptList; p++;
    p->type = 4129; p->flags = 0x92; p->getter = 1248; p->putter = 1248; p->offset = 1248; p++;
    p->type = 1; p->flags = 0x2; p->getter = 976; p++;
    p->type = 4132; p->flags = 0x100; p->offset = (s32)SetColliderFlagNibble32; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)SetScriptColliderFlagNibble36; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (s32)TestScriptPointInsideCollider; p->putter = 1; p++;
    p->type = 0; p->flags = 0x124; p->getter = (s32)GetColliderFlagBit52; p->putter = (s32)SetColliderFlagBit52; p->offset = (s32)SetColliderFlagBit52; p++;
    p->type = 2; p->flags = 0x12; p->getter = 64; p->putter = 64; p++;
    p->type = 4; p->flags = 0x12; p->getter = 80; p->putter = 80; p++;
    p->type = 2; p->flags = 0x4; p->getter = (s32)GetObjectWorldPosition; p++;
    p->type = 4; p->flags = 0x4; p->getter = (s32)GetObjectWorldRotation; p++;
    p->type = 2; p->flags = 0x12; p->getter = 128; p->putter = 128; p++;
    p->type = 1; p->flags = 0x92; p->getter = 128; p->putter = 128; p->offset = 128; p++;
    p->type = 1; p->flags = 0x92; p->getter = 132; p->putter = 132; p->offset = 132; p++;
    p->type = 1; p->flags = 0x92; p->getter = 136; p->putter = 136; p->offset = 136; p++;
    p->type = 0; p->flags = 0x82; p->getter = 144; p->offset = 144; p++;
    p->type = 0; p->flags = 0x82; p->getter = 148; p->offset = 148; p++;
    p->type = 6; p->flags = 0x92; p->getter = 176; p->putter = 176; p->offset = 176; p++;
    p->type = 1; p->flags = 0x122; p->getter = 156; p->putter = (s32)StoreValueAndMarkSet; p->offset = (s32)StoreValueAndMarkSet; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)SetScriptTransformObjectKeyedValue; p->putter = 4; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)PlaceScriptAtArrivalPoint; p->putter = 0; p++;
    p->type = 6; p->flags = 0x892; p->getter = 768; p->putter = 768; p->offset = 768; p->intValue = -1; p++;
    p->type = 4159; p->flags = 0x892; p->getter = 772; p->putter = 772; p->offset = 772; p->intValue = -1; p++;
    p->type = 6; p->flags = 0x892; p->getter = 780; p->putter = 780; p->offset = 780; p->intValue = -1; p++;
    p->type = 4106; p->flags = 0x892; p->getter = 792; p->putter = 792; p->offset = 792; p->intValue = 0; p++;
    p->type = 1; p->flags = 0x892; p->getter = 800; p->putter = 800; p->offset = 800; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x892; p->getter = 720; p->putter = 720; p->offset = 720; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x892; p->getter = 724; p->putter = 724; p->offset = 724; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x892; p->getter = 736; p->putter = 736; p->offset = 736; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x892; p->getter = 728; p->putter = 728; p->offset = 728; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x892; p->getter = 732; p->putter = 732; p->offset = 732; p->intValue = 0; p++;
    p->type = 1; p->flags = 0x92; p->getter = 804; p->putter = 804; p->offset = 804; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)StartScriptObjectSubGroupFinish; p->putter = 0; p++;
    p->type = 4200; p->flags = 0x22; p->getter = 740; p->putter = (s32)SetObjectSubGroupState; p++;
    p->type = 2; p->flags = 0x12; p->getter = 64; p->putter = 64; p++;
    p->type = 2; p->flags = 0x4; p->getter = (s32)ConvertPositionToWorld; p++;
    p->type = 4098; p->flags = 0x880; p->offset = 68; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x880; p->offset = 72; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x880; p->offset = 76; p->intValue = 0; p++;
    p->type = 5; p->flags = 0x80; p->offset = 120; p++;
    p->type = 1; p->flags = 0x892; p->getter = 124; p->putter = 124; p->offset = 124; p->floatValue = 1.0f; p++;
    p->type = 9; p->flags = 0x80; p->offset = 128; p++;
    p->type = 10; p->flags = 0x80; p->offset = 144; p++;
    p->type = 8338; p->flags = 0x1; p->getter = 0; p->f10 = (s32)CreateScriptAnimationPlayer; p->putter = 4; p++;
    p->type = 8338; p->flags = 0x1; p->getter = 0; p->f10 = (s32)FindOrCreateScriptSeekedAnimationPlayer; p->putter = 5; p++;
    p->type = 1; p->flags = 0x1; p->getter = 0; p->f10 = (s32)GetScriptAnimationMarkerTime; p->putter = 1; p++;
    p->type = 1; p->flags = 0x2; p->getter = 52; p++;
    p->type = 0; p->flags = 0x82; p->getter = 80; p->offset = 80; p++;
    p->type = 8323; p->flags = 0x2; p->getter = 8; p++;
    p->type = 8194; p->flags = 0x2; p->getter = 12; p++;
    p->type = 1; p->flags = 0x2; p->getter = 20; p++;
    p->type = 1; p->flags = 0x22; p->getter = 24; p->putter = (s32)SetAnimationPlayerSpeed; p++;
    p->type = 1; p->flags = 0x22; p->getter = 28; p->putter = (s32)SetAnimationPlayerSpeedScale; p++;
    p->type = 5; p->flags = 0x22; p->getter = 232; p->putter = (s32)SetAttachmentSortKeys; p++;
    p->type = 0; p->flags = 0x22; p->getter = 36; p->putter = (s32)SetAnimationPlayerPadSelect; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SeekScriptAnimationPlayer; p->putter = 3; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)StopScriptAnimationPlayer; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ApplyScriptListedPoseSources; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ReleaseScriptPlayerAttachment; p->putter = 2; p++;
    p->type = 0; p->flags = 0x892; p->getter = 1408; p->putter = 1408; p->offset = 1408; p->intValue = 1; p++;
    p->type = 0; p->flags = 0x892; p->getter = 1420; p->putter = 1420; p->offset = 1420; p->intValue = 1; p++;
    p->type = 2; p->flags = 0x92; p->getter = 1392; p->putter = 1392; p->offset = 1392; p++;
    p->type = 6; p->flags = 0x1100; p->offset = (s32)AddTrackedKey; p->target = (PropertyTarget)GetAttachedSetTrackedNodes; p++;
    p->type = 8193; p->flags = 0x1020; p->putter = (s32)AddTrackedNode; p->target = (PropertyTarget)GetAttachedSetTrackedNodes; p++;
    p->type = 8193; p->flags = 0x1020; p->putter = (s32)RemoveTrackedNode; p->target = (PropertyTarget)GetAttachedSetTrackedNodes; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ClearScriptAttachedSetTrackedNodes; p->putter = 0; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1432; p->putter = 1432; p->offset = 1432; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1436; p->putter = 1436; p->offset = 1436; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1412; p->putter = 1412; p->offset = 1412; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1416; p->putter = 1416; p->offset = 1416; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddMaskedColliderKeyKind0; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddMaskedColliderKeyKind1; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddMaskedColliderKeyKind2; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddMaskedColliderKeyKind3; p++;
    p->type = 0; p->flags = 0x892; p->getter = 1660; p->putter = 1660; p->offset = 1660; p->intValue = 0; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1572; p->putter = 1572; p->offset = 1572; p++;
    p->type = 6; p->flags = 0x880; p->offset = 1592; p->intValue = -1; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1576; p->putter = 1576; p->offset = 1576; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1584; p->putter = 1584; p->offset = 1584; p->floatValue = 300.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1588; p->putter = 1588; p->offset = 1588; p->floatValue = 3.0f; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddAcceptedObjectId; p++;
    p->type = 7; p->flags = 0x100; p->offset = (s32)AddAcceptedKind; p++;
    p->type = 7; p->flags = 0x100; p->offset = (s32)AddMaskedColliderListEntry; p++;
    p->type = 0; p->flags = 0x124; p->getter = (s32)GetAcceptsPlayer; p->putter = (s32)SetAcceptsPlayer; p->offset = (s32)SetAcceptsPlayer; p++;
    p->type = 0; p->flags = 0x124; p->getter = (s32)GetAcceptsFlaggedObjects; p->putter = (s32)SetAcceptsFlaggedObjects; p->offset = (s32)SetAcceptsFlaggedObjects; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1676; p->putter = 1676; p->offset = 1676; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)HandleScriptMaskedColliderActivation; p->putter = 0; p++;
    p->type = 0; p->flags = 0x22; p->getter = 1664; p->putter = (s32)SetObjectHold; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1684; p->putter = 1684; p->offset = 1684; p++;
    p->type = 4162; p->flags = 0x892; p->getter = 1564; p->putter = 1564; p->offset = 1564; p->intValue = 1; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1568; p->putter = 1568; p->offset = 1568; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1688; p->putter = 1688; p->offset = 1688; p++;
    p->type = 2; p->flags = 0x92; p->getter = 1696; p->putter = 1696; p->offset = 1696; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1712; p->putter = 1712; p->offset = 1712; p++;
    p->type = 14; p->flags = 0x1092; p->getter = 0; p->putter = 0; p->offset = 0; p->target = (PropertyTarget)GetMaskedColliderSoundParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 4; p->putter = 4; p->offset = 4; p->target = (PropertyTarget)GetMaskedColliderSoundParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 8; p->putter = 8; p->offset = 8; p->target = (PropertyTarget)GetMaskedColliderSoundParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 12; p->putter = 12; p->offset = 12; p->target = (PropertyTarget)GetMaskedColliderSoundParams; p++;
    p->type = 6; p->flags = 0x80; p->offset = 1556; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1668; p->putter = 1668; p->offset = 1668; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1728; p->putter = 1728; p->offset = 1728; p++;
    p->type = 4096; p->flags = 0x92; p->getter = 1732; p->putter = 1732; p->offset = 1732; p++;
    p->type = 4096; p->flags = 0x92; p->getter = 1736; p->putter = 1736; p->offset = 1736; p++;
    p->type = 8195; p->flags = 0x12; p->getter = 1740; p->putter = 1740; p++;
    p->type = 4124; p->flags = 0x92; p->getter = 1744; p->putter = 1744; p->offset = 1744; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1372; p->putter = 1372; p->offset = 1372; p->floatValue = 1.5f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1368; p->putter = 1368; p->offset = 1368; p->floatValue = 10.0f; p++;
    p->type = 4146; p->flags = 0x122; p->getter = 1360; p->putter = (s32)SetTimedState; p->offset = (s32)SetTimedState; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1380; p->putter = 1380; p->offset = 1380; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AppendTriggerZoneFirstQueue; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AppendTriggerZoneSecondQueue; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddIncludedId; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddExcludedId; p++;
    p->type = 7; p->flags = 0x100; p->offset = (s32)AddIncludedKind; p++;
    p->type = 7; p->flags = 0x100; p->offset = (s32)AddExcludedKind; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1660; p->putter = 1660; p->offset = 1660; p->floatValue = 1.0f; p++;
    p->type = 4105; p->flags = 0x880; p->offset = 1360; p->intValue = 0; p++;
    p->type = 1; p->flags = 0x880; p->offset = 1644; p->floatValue = 1.0f; p++;
    p->type = 0; p->flags = 0x880; p->offset = 1672; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x880; p->offset = 1676; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x880; p->offset = 1680; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x880; p->offset = 1648; p->intValue = 1; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)SetScriptTriggerZoneEntry; p->putter = 4; p++;
    p->type = 6; p->flags = 0x80; p->offset = 1684; p++;
    p->type = 4187; p->flags = 0x22; p->getter = 1664; p->putter = (s32)SetTriggerZoneMode; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AppendZoneColliderFirstQueue; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AppendZoneColliderSecondQueue; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1768; p->putter = 1768; p->offset = 1768; p->floatValue = 1.0f; p++;
    p->type = 1; p->flags = 0x880; p->offset = 1752; p->floatValue = 1.0f; p++;
    p->type = 0; p->flags = 0x880; p->offset = 1780; p->intValue = 1; p++;
    p->type = 0; p->flags = 0x880; p->offset = 1784; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x880; p->offset = 1756; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x892; p->getter = 1932; p->putter = 1932; p->offset = 1932; p->intValue = 1; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddZoneColliderId; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)SetScriptZoneColliderEntry; p->putter = 4; p++;
    p->type = 0; p->flags = 0x892; p->getter = 1936; p->putter = 1936; p->offset = 1936; p->intValue = 0; p++;
    p->type = -2147475455; p->flags = 0x4; p->getter = (s32)TestListedEntriesAccepted; p++;
    p->type = 6; p->flags = 0x80; p->offset = 1792; p++;
    p->type = 4187; p->flags = 0x22; p->getter = 1772; p->putter = (s32)SetZoneColliderMode; p++;
    p->type = 0; p->flags = 0x122; p->getter = 1360; p->putter = (s32)SetSwitchedColliderEnabled; p->offset = (s32)SetSwitchedColliderEnabled; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ActivateScriptSwitchedColliderUnlessActive; p->putter = 0; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (s32)TestScriptRequestBlocked; p->putter = 1; p++;
    p->type = 4198; p->flags = 0x4; p->getter = (s32)StoreSwitchedColliderAccepted; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddLookupId; p++;
    p->type = 1; p->flags = 0x880; p->offset = 1360; p->floatValue = 100.0f; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddObjectSetKey; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1368; p->putter = 1368; p->offset = 1368; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddStateTriggerCountedId; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddStateTriggerItemId; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddStateTriggerAgentId; p++;
    p->type = 0; p->flags = 0x892; p->getter = 1576; p->putter = 1576; p->offset = 1576; p->intValue = 0; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1376; p->putter = 1376; p->offset = 1376; p->intValue = 0; p++;
    p->type = 4137; p->flags = 0x2; p->getter = 1360; p++;
    p->type = -2147475408; p->flags = 0x4; p->getter = (s32)TestStateTriggerItemsAccepted; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptStateTriggerStateFromMessage; p->putter = 1; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)AddScriptStateTriggerTableEntry; p->putter = 4; p++;
    p->type = 8239; p->flags = 0x2; p->getter = 1728; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddTimedObjectAcceptedObjectId; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddTimedObjectExcludedObjectId; p++;
    p->type = 7; p->flags = 0x100; p->offset = (s32)AddTimedObjectAcceptedClassId; p++;
    p->type = 7; p->flags = 0x100; p->offset = (s32)AddTimedObjectExcludedClassId; p++;
    p->type = 0; p->flags = 0x892; p->getter = 1460; p->putter = 1460; p->offset = 1460; p->intValue = 0; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1464; p->putter = 1464; p->offset = 1464; p->floatValue = 1.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1468; p->putter = 1468; p->offset = 1468; p->floatValue = 1.0f; p++;
    p->type = 4140; p->flags = 0x892; p->getter = 1376; p->putter = 1376; p->offset = 1376; p->intValue = 1; p++;
    p->type = 8239; p->flags = 0x2; p->getter = 1360; p++;
    p->type = 4140; p->flags = 0x2; p->getter = 1368; p++;
    p->type = 4139; p->flags = 0x2; p->getter = 1364; p++;
    p->type = 0; p->flags = 0x12; p->getter = 1472; p->putter = 1472; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptTimedObjectMode; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)RequestScriptTimedObjectEnd; p->putter = 0; p++;
    p->type = 4141; p->flags = 0x892; p->getter = 1488; p->putter = 1488; p->offset = 1488; p->intValue = 0; p++;
    p->type = 1; p->flags = 0x892; p->getter = 2796; p->putter = 2796; p->offset = 2796; p->floatValue = 0.25f; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptTimedGroupFadeInTime; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptTimedGroupFadeOutTime; p->putter = 1; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1504; p->putter = 1504; p->offset = 1504; p->floatValue = 0.25f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1508; p->putter = 1508; p->offset = 1508; p->floatValue = 1.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1512; p->putter = 1512; p->offset = 1512; p->floatValue = 0.75f; p++;
    p->type = 4142; p->flags = 0x2; p->getter = 1496; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1488; p->putter = 1488; p->offset = 1488; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1492; p->putter = 1492; p->offset = 1492; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1496; p->putter = 1496; p->offset = 1496; p++;
    p->type = 4143; p->flags = 0x892; p->getter = 1500; p->putter = 1500; p->offset = 1500; p->intValue = 0; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1504; p->putter = 1504; p->offset = 1504; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1508; p->putter = 1508; p->offset = 1508; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1512; p->putter = 1512; p->offset = 1512; p++;
    p->type = 4143; p->flags = 0x892; p->getter = 1516; p->putter = 1516; p->offset = 1516; p->intValue = 0; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1520; p->putter = 1520; p->offset = 1520; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1524; p->putter = 1524; p->offset = 1524; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1528; p->putter = 1528; p->offset = 1528; p++;
    p->type = 4143; p->flags = 0x892; p->getter = 1532; p->putter = 1532; p->offset = 1532; p->intValue = 0; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1536; p->putter = 1536; p->offset = 1536; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1540; p->putter = 1540; p->offset = 1540; p->floatValue = 8.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1544; p->putter = 1544; p->offset = 1544; p->floatValue = 2.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1548; p->putter = 1548; p->offset = 1548; p->floatValue = 2.0f; p++;
    p->type = 4113; p->flags = 0x82; p->getter = 160; p->offset = 160; p++;
    p->type = 1; p->flags = 0x92; p->getter = 164; p->putter = 164; p->offset = 164; p++;
    p->type = 14; p->flags = 0x92; p->getter = 168; p->putter = 168; p->offset = 168; p++;
    p->type = 14; p->flags = 0x92; p->getter = 172; p->putter = 172; p->offset = 172; p++;
    p->type = 1; p->flags = 0x92; p->getter = 176; p->putter = 176; p->offset = 176; p++;
    p->type = 0; p->flags = 0x92; p->getter = 184; p->putter = 184; p->offset = 184; p++;
    p->type = 1; p->flags = 0x92; p->getter = 180; p->putter = 180; p->offset = 180; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddIdFilterObjectId; p++;
    p->type = 7; p->flags = 0x100; p->offset = (s32)AddIdFilterClassId; p++;
    p->type = 0; p->flags = 0x80; p->offset = 1360; p++;
    p->type = 6; p->flags = 0x80; p->offset = 1424; p++;
    p->type = 5; p->flags = 0x122; p->getter = 728; p->putter = (s32)SetEffectSpawnerLimit; p->offset = (s32)SetEffectSpawnerLimit; p++;
    p->type = 0; p->flags = 0x122; p->getter = 776; p->putter = (s32)SetEffectSpawnerContinuous; p->offset = (s32)SetEffectSpawnerContinuous; p++;
    p->type = 4148; p->flags = 0x1092; p->getter = 724; p->putter = 724; p->offset = 724; p->target = (PropertyTarget)MarkEffectSpawnerChanged; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 732; p->putter = 732; p->offset = 732; p->target = (PropertyTarget)MarkEffectSpawnerChanged; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 756; p->putter = 756; p->offset = 756; p->target = (PropertyTarget)MarkEffectSpawnerChanged; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 744; p->putter = 744; p->offset = 744; p->target = (PropertyTarget)MarkEffectSpawnerChanged; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 748; p->putter = 748; p->offset = 748; p->target = (PropertyTarget)MarkEffectSpawnerChanged; p++;
    p->type = 0; p->flags = 0x24; p->getter = (s32)GetEffectSpawnerInactive; p->putter = (s32)SetEffectSpawnerDisabled; p++;
    p->type = 0; p->flags = 0x82; p->getter = 740; p->offset = 740; p++;
    p->type = 6; p->flags = 0x82; p->getter = 760; p->offset = 760; p++;
    p->type = 6; p->flags = 0x82; p->getter = 764; p->offset = 764; p++;
    p->type = 6; p->flags = 0x82; p->getter = 768; p->offset = 768; p++;
    p->type = 6; p->flags = 0x82; p->getter = 772; p->offset = 772; p++;
    p->type = 6; p->flags = 0x82; p->getter = 784; p->offset = 784; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptEffectSpawnerActiveFor; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptEffectSpawnerActiveForever; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptEffectSpawnerInactive; p->putter = 0; p++;
    p->type = 0; p->flags = 0x4; p->getter = (s32)GetEffectSpawnerActive; p++;
    p->type = 4118; p->flags = 0x1082; p->getter = 16; p->offset = 16; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 2; p->flags = 0x1082; p->getter = 32; p->offset = 32; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 2; p->flags = 0x1082; p->getter = 32; p->offset = 32; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 2; p->flags = 0x1082; p->getter = 48; p->offset = 48; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 6; p->flags = 0x82; p->getter = 780; p->offset = 780; p++;
    p->type = 4119; p->flags = 0x1092; p->getter = 80; p->putter = 80; p->offset = 80; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 96; p->putter = 96; p->offset = 96; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 96; p->putter = 96; p->offset = 96; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 96; p->putter = 96; p->offset = 96; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 112; p->putter = 112; p->offset = 112; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 4121; p->flags = 0x1092; p->getter = 128; p->putter = 128; p->offset = 128; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 160; p->putter = 160; p->offset = 160; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 168; p->putter = 168; p->offset = 168; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 176; p->putter = 176; p->offset = 176; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 192; p->putter = 192; p->offset = 192; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 196; p->putter = 196; p->offset = 196; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 208; p->putter = 208; p->offset = 208; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 4120; p->flags = 0x1092; p->getter = 224; p->putter = 224; p->offset = 224; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 228; p->putter = 228; p->offset = 228; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 5; p->flags = 0x1092; p->getter = 236; p->putter = 236; p->offset = 236; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 240; p->putter = 240; p->offset = 240; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 244; p->putter = 244; p->offset = 244; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 248; p->putter = 248; p->offset = 248; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 256; p->putter = 256; p->offset = 256; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 272; p->putter = 272; p->offset = 272; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 4117; p->flags = 0x1082; p->getter = 288; p->offset = 288; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 4115; p->flags = 0x100; p->offset = (s32)SetEffectSpawnerKind; p++;
    p->type = 4115; p->flags = 0x1082; p->getter = 436; p->offset = 436; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 464; p->putter = 464; p->offset = 464; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 448; p->putter = 448; p->offset = 448; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 4116; p->flags = 0x1082; p->getter = 484; p->offset = 484; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 488; p->putter = 488; p->offset = 488; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 6; p->flags = 0x1082; p->getter = 308; p->offset = 308; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 320; p->putter = 320; p->offset = 320; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 336; p->putter = 336; p->offset = 336; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 352; p->putter = 352; p->offset = 352; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 0; p->flags = 0x1092; p->getter = 368; p->putter = 368; p->offset = 368; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 372; p->putter = 372; p->offset = 372; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 0; p->flags = 0x1092; p->getter = 376; p->putter = 376; p->offset = 376; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 4149; p->flags = 0x1092; p->getter = 304; p->putter = 304; p->offset = 304; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 6; p->flags = 0x1082; p->getter = 392; p->offset = 392; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 4150; p->flags = 0x1092; p->getter = 400; p->putter = 400; p->offset = 400; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 404; p->putter = 404; p->offset = 404; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 4151; p->flags = 0x1092; p->getter = 408; p->putter = 408; p->offset = 408; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 412; p->putter = 412; p->offset = 412; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 0; p->flags = 0x1092; p->getter = 420; p->putter = 420; p->offset = 420; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)AddScriptSpawnRangeEntry; p->f10 = 0; p->putter = 6; p++;
    p->type = 0; p->flags = 0x1082; p->getter = 496; p->offset = 496; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 0; p->flags = 0x1082; p->getter = 500; p->offset = 500; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 6; p->flags = 0x1082; p->getter = 496; p->offset = 496; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 1; p->flags = 0x1082; p->getter = 500; p->offset = 500; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 1; p->flags = 0x1082; p->getter = 496; p->offset = 496; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 1; p->flags = 0x1082; p->getter = 500; p->offset = 500; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 1; p->flags = 0x1082; p->getter = 504; p->offset = 504; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 0; p->flags = 0x1082; p->getter = 496; p->offset = 496; p->target = (PropertyTarget)GetOwnSpawnRecord; p++;
    p->type = 4118; p->flags = 0x1092; p->getter = 16; p->putter = 16; p->offset = 16; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 32; p->putter = 32; p->offset = 32; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 32; p->putter = 32; p->offset = 32; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 48; p->putter = 48; p->offset = 48; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 6; p->flags = 0x82; p->getter = 148; p->offset = 148; p++;
    p->type = 6; p->flags = 0x82; p->getter = 152; p->offset = 152; p++;
    p->type = 4119; p->flags = 0x1092; p->getter = 80; p->putter = 80; p->offset = 80; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 96; p->putter = 96; p->offset = 96; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 96; p->putter = 96; p->offset = 96; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 96; p->putter = 96; p->offset = 96; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 112; p->putter = 112; p->offset = 112; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 4121; p->flags = 0x1092; p->getter = 128; p->putter = 128; p->offset = 128; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 160; p->putter = 160; p->offset = 160; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 168; p->putter = 168; p->offset = 168; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 228; p->putter = 228; p->offset = 228; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 5; p->flags = 0x1092; p->getter = 236; p->putter = 236; p->offset = 236; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 240; p->putter = 240; p->offset = 240; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 248; p->putter = 248; p->offset = 248; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)AddScriptRecordMemberRangeEntry; p->f10 = 0; p->putter = 6; p++;
    p->type = 10; p->flags = 0x92; p->getter = 164; p->putter = 164; p->offset = 164; p++;
    p->type = 6; p->flags = 0x82; p->getter = 172; p->offset = 172; p++;
    p->type = 6; p->flags = 0x82; p->getter = 180; p->offset = 180; p++;
    p->type = 6; p->flags = 0x82; p->getter = 176; p->offset = 176; p++;
    p->type = 1; p->flags = 0x92; p->getter = 184; p->putter = 184; p->offset = 184; p++;
    p->type = 0; p->flags = 0x92; p->getter = 188; p->putter = 188; p->offset = 188; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 176; p->putter = 176; p->offset = 176; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 192; p->putter = 192; p->offset = 192; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 196; p->putter = 196; p->offset = 196; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 208; p->putter = 208; p->offset = 208; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 4120; p->flags = 0x1092; p->getter = 224; p->putter = 224; p->offset = 224; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 244; p->putter = 244; p->offset = 244; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 256; p->putter = 256; p->offset = 256; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 272; p->putter = 272; p->offset = 272; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 4117; p->flags = 0x1082; p->getter = 288; p->offset = 288; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 4115; p->flags = 0x100; p->offset = (s32)SetOwnedSpawnRecordKind; p++;
    p->type = 4115; p->flags = 0x1082; p->getter = 436; p->offset = 436; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 464; p->putter = 464; p->offset = 464; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 448; p->putter = 448; p->offset = 448; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 4116; p->flags = 0x1082; p->getter = 484; p->offset = 484; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 488; p->putter = 488; p->offset = 488; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 6; p->flags = 0x1082; p->getter = 308; p->offset = 308; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 320; p->putter = 320; p->offset = 320; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 336; p->putter = 336; p->offset = 336; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 352; p->putter = 352; p->offset = 352; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 0; p->flags = 0x1092; p->getter = 368; p->putter = 368; p->offset = 368; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 372; p->putter = 372; p->offset = 372; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 0; p->flags = 0x1092; p->getter = 376; p->putter = 376; p->offset = 376; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 4149; p->flags = 0x1092; p->getter = 304; p->putter = 304; p->offset = 304; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 6; p->flags = 0x1082; p->getter = 392; p->offset = 392; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 4150; p->flags = 0x1092; p->getter = 400; p->putter = 400; p->offset = 400; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 404; p->putter = 404; p->offset = 404; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 4151; p->flags = 0x1092; p->getter = 408; p->putter = 408; p->offset = 408; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 412; p->putter = 412; p->offset = 412; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 0; p->flags = 0x1092; p->getter = 420; p->putter = 420; p->offset = 420; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 0; p->flags = 0x1082; p->getter = 496; p->offset = 496; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 0; p->flags = 0x1082; p->getter = 500; p->offset = 500; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 14; p->flags = 0x1092; p->getter = 0; p->putter = 0; p->offset = 0; p->target = (PropertyTarget)GetOrCreateSoundParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 4; p->putter = 4; p->offset = 4; p->target = (PropertyTarget)GetOrCreateSoundParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 8; p->putter = 8; p->offset = 8; p->target = (PropertyTarget)GetOrCreateSoundParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 12; p->putter = 12; p->offset = 12; p->target = (PropertyTarget)GetOrCreateSoundParams; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SendScriptEmptyMessageC7A; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SendScriptTwoVectorMessageC7A; p->putter = 6; p++;
    p->type = 6; p->flags = 0x1082; p->getter = 496; p->offset = 496; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 1; p->flags = 0x1082; p->getter = 500; p->offset = 500; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 1; p->flags = 0x1082; p->getter = 496; p->offset = 496; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 1; p->flags = 0x1082; p->getter = 500; p->offset = 500; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 1; p->flags = 0x1082; p->getter = 504; p->offset = 504; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 0; p->flags = 0x1082; p->getter = 496; p->offset = 496; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SendScriptEmptyMessageC78; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SendScriptTwoVectorMessageC78; p->putter = 6; p++;
    p->type = 4122; p->flags = 0x122; p->getter = 720; p->putter = (s32)SetConeVolumeMode; p->offset = (s32)SetConeVolumeMode; p++;
    p->type = 2; p->flags = 0xA2; p->getter = 736; p->putter = (s32)SetConeVolumeColor; p->offset = 736; p++;
    p->type = 1; p->flags = 0xA2; p->getter = 752; p->putter = (s32)SetConeVolumeSecondLevel; p->offset = 752; p++;
    p->type = 1; p->flags = 0xA2; p->getter = 756; p->putter = (s32)SetConeVolumeThirdLevel; p->offset = 756; p++;
    p->type = 1; p->flags = 0xA2; p->getter = 760; p->putter = (s32)SetConeVolumeFirstAngle; p->offset = 760; p++;
    p->type = 1; p->flags = 0xA2; p->getter = 764; p->putter = (s32)SetConeVolumeSecondAngle; p->offset = 764; p++;
    p->type = 1; p->flags = 0xA2; p->getter = 768; p->putter = (s32)SetConeVolumeThirdAngle; p->offset = 768; p++;
    p->type = 2; p->flags = 0x122; p->getter = 784; p->putter = (s32)SetConeVolumeDirection; p->offset = (s32)SetConeVolumeDirection; p++;
    p->type = 0; p->flags = 0x122; p->getter = 772; p->putter = (s32)SetConeVolumeValue; p->offset = (s32)SetConeVolumeValue; p++;
    p->type = 0; p->flags = 0x122; p->getter = 772; p->putter = (s32)SetConeVolumeValue; p->offset = (s32)SetConeVolumeValue; p++;
    p->type = 0; p->flags = 0x92; p->getter = 776; p->putter = 776; p->offset = 776; p++;
    p->type = 10; p->flags = 0xA2; p->getter = 816; p->putter = (s32)SetConeVolumeRange; p->offset = 816; p++;
    p->type = 1; p->flags = 0xA2; p->getter = 824; p->putter = (s32)SetConeVolumeOuterAngle; p->offset = 824; p++;
    p->type = 1; p->flags = 0xA2; p->getter = 828; p->putter = (s32)SetConeVolumeInnerAngle; p->offset = 828; p++;
    p->type = 2; p->flags = 0xA2; p->getter = 832; p->putter = (s32)SetConeVolumeVector340; p->offset = 832; p++;
    p->type = 1; p->flags = 0x124; p->getter = (s32)GetConeVolumeSecondLevel; p->putter = (s32)SetConeVolumeOuterLevels; p->offset = (s32)SetConeVolumeOuterLevels; p++;
    p->type = 2; p->flags = 0x124; p->getter = (s32)GetConeVolumeColorRgb; p->putter = (s32)SetConeVolumeColorRgb; p->offset = (s32)SetConeVolumeColorRgb; p++;
    p->type = 0; p->flags = 0x0; p++;
    p->type = 1; p->flags = 0x0; p++;
    p->type = 1; p->flags = 0x0; p++;
    p->type = 1; p->flags = 0x0; p++;
    p->type = 1; p->flags = 0x0; p++;
    p->type = 0; p->flags = 0x80; p->offset = 68; p++;
    p->type = 8339; p->flags = 0x1; p->getter = 0; p->f10 = (s32)CreateScriptStateWalker; p->putter = 3; p++;
    p->type = 8194; p->flags = 0x2; p->getter = 28; p++;
    p->type = 6; p->flags = 0x24; p->getter = (s32)GetStateWalkerTargetKey; p->putter = (s32)SetStateWalkerTarget; p++;
    p->type = 6; p->flags = 0x4; p->getter = (s32)GetStateWalkerCurrentKey; p++;
    p->type = 6; p->flags = 0x4; p->getter = (s32)GetStateWalkerNextKey; p++;
    p->type = 1; p->flags = 0x22; p->getter = 56; p->putter = (s32)SetStateWalkerSpeed; p++;
    p->type = 8338; p->flags = 0x2; p->getter = 36; p++;
    p->type = 6; p->flags = 0x20; p->putter = (s32)TeleportStateWalker; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)DestroyScriptStateWalker; p->putter = 0; p++;
    p->type = 8328; p->flags = 0x2; p->getter = 24; p++;
    p->type = 0; p->flags = 0x880; p->offset = 7544; p->intValue = 1; p++;
    p->type = 1; p->flags = 0x880; p->offset = 7548; p->floatValue = 1.0f; p++;
    p->type = 1; p->flags = 0xA2; p->getter = 7532; p->putter = (s32)SetWorldLightingParamA; p->offset = 7532; p++;
    p->type = 1; p->flags = 0xA2; p->getter = 7528; p->putter = (s32)SetWorldLightingParamB; p->offset = 7528; p++;
    p->type = 13; p->flags = 0x80; p->offset = 7524; p++;
    p->type = 1; p->flags = 0x100; p->offset = (s32)SnapCurrentCameraZoom; p++;
    p->type = 1; p->flags = 0x100; p->offset = (s32)SetCurrentCameraNearDistance; p++;
    p->type = 1; p->flags = 0x100; p->offset = (s32)SetCurrentCameraFarDistance; p++;
    p->type = 1; p->flags = 0x100; p->offset = (s32)SetCurrentCameraFogNear; p++;
    p->type = 1; p->flags = 0x100; p->offset = (s32)SetCurrentCameraFogFar; p++;
    p->type = 1; p->flags = 0x100; p->offset = (s32)SetCurrentCameraFogStrength; p++;
    p->type = 13; p->flags = 0x100; p->offset = (s32)SetCurrentCameraFogColor; p++;
    p->type = 1; p->flags = 0x100; p->offset = (s32)SetCurrentCameraDistanceScale; p++;
    p->type = 1; p->flags = 0x892; p->getter = 8968; p->putter = 8968; p->offset = 8968; p->floatValue = 15.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 8972; p->putter = 8972; p->offset = 8972; p->floatValue = 180.0f; p++;
    p->type = 1; p->flags = 0x22; p->getter = 8984; p->putter = (s32)SetWorldSoundLevel; p++;
    p->type = 1; p->flags = 0x22; p->getter = 9036; p->putter = (s32)SetWorldValueAndTarget; p++;
    p->type = 1; p->flags = 0x22; p->getter = 9040; p->putter = (s32)SetWorldValueTarget; p++;
    p->type = 5; p->flags = 0x1092; p->getter = 4; p->putter = 4; p->offset = 4; p->target = (PropertyTarget)GetScatterController; p++;
    p->type = 5; p->flags = 0x1092; p->getter = 8; p->putter = 8; p->offset = 8; p->target = (PropertyTarget)GetScatterController; p++;
    p->type = 5; p->flags = 0x1092; p->getter = 12; p->putter = 12; p->offset = 12; p->target = (PropertyTarget)GetScatterController; p++;
    p->type = 5; p->flags = 0x1092; p->getter = 16; p->putter = 16; p->offset = 16; p->target = (PropertyTarget)GetScatterController; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ScatterScriptRandomObjects; p->putter = 3; p++;
    p->type = 1; p->flags = 0x24; p->getter = (s32)GetGameStateDeltaTime; p->putter = (s32)SetScatterLevelBuiltin; p++;
    p->type = 1; p->flags = 0x24; p->getter = (s32)GetCurrentScatterLevel; p->putter = (s32)SetCurrentScatterLevel; p++;
    p->type = 14; p->flags = 0x120; p->putter = (s32)AddWorldSoundEntry; p->offset = (s32)AddWorldSoundEntry; p++;
    p->type = 10; p->flags = 0x120; p->putter = (s32)SetLastWorldSoundEntryFromPoint; p->offset = (s32)SetLastWorldSoundEntryFromPoint; p++;
    p->type = 10; p->flags = 0x120; p->putter = (s32)SetLastWorldSoundEntryValues; p->offset = (s32)SetLastWorldSoundEntryValues; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)SetScriptIopChannel2Setting; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)PushScriptIopChannel2Setting; p->putter = 2; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)PopScriptIopChannel2Setting; p->putter = 0; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (s32)TestScriptLevelEntryFlag1; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (s32)TestScriptLevelEntryFlag2; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (s32)TestScriptLevelEntryFlag4; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (s32)TestScriptLevelEntryFlag8; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (s32)CheckScriptEntryOneBitRequirement; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (s32)CheckScriptEntryTwoBitRequirement; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (s32)CheckScriptEntryThreeBitRequirement; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptEntrySlotValue; p->putter = 3; p++;
    p->type = 5; p->flags = 0x1; p->getter = 0; p->f10 = (s32)GetScriptEntrySlotValue; p->putter = 2; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (s32)IsScriptLevelRecordComplete; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (s32)IsScriptLevelDone; p->putter = 1; p++;
    p->type = 5; p->flags = 0x1; p->getter = 0; p->f10 = (s32)RecomputeScriptSaveCompletion; p->putter = 0; p++;
    p->type = 0; p->flags = 0x4; p->getter = (s32)GetHasStreamVoice; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)PopScriptActiveSequenceElement; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ShowScriptPauseMenuPageWith; p->putter = 2; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ShowScriptCountedScreenElement; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)HideScriptCountedScreenElement; p->putter = 0; p++;
    p->type = 0; p->flags = 0x92; p->getter = 9044; p->putter = 9044; p->offset = 9044; p++;
    p->type = 5; p->flags = 0x1; p->getter = 0; p->f10 = (s32)PushScriptSoundLevel; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)RemoveScriptSoundLevel; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptCachedVoiceParam; p->putter = 2; p++;
    p->type = 5; p->flags = 0x1; p->getter = 0; p->f10 = (s32)GetScriptCachedVoiceParam; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)RefreshScriptCachedVoiceParam; p->putter = 2; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)AcquireScriptPadSelectFlag; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ReleaseScriptPadSelectFlag; p->putter = 0; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)ClearScriptWorldFlagBit; p->putter = 1; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)SetScriptWorldFlagBit; p->putter = 1; p++;
    p->type = 5; p->flags = 0x4; p->getter = (s32)GetSaveSpareCount; p++;
    p->type = 5; p->flags = 0x4; p->getter = (s32)GetReserveUnitCount; p++;
    p->type = 2; p->flags = 0x22; p->getter = 64; p->putter = (s32)SetCameraPosition; p++;
    p->type = 4; p->flags = 0x22; p->getter = 128; p->putter = (s32)SetCameraOrientation; p++;
    p->type = 1; p->flags = 0x22; p->getter = 452; p->putter = (s32)SnapCameraZoom; p++;
    p->type = 1; p->flags = 0x12; p->getter = 456; p->putter = 456; p++;
    p->type = 12; p->flags = 0x12; p->getter = 464; p->putter = 464; p++;
    p->type = 1; p->flags = 0x22; p->getter = 484; p->putter = (s32)SetCameraNearDistance; p++;
    p->type = 1; p->flags = 0x22; p->getter = 488; p->putter = (s32)SetCameraFarDistance; p++;
    p->type = 1; p->flags = 0x22; p->getter = 504; p->putter = (s32)SetCameraFogNear; p++;
    p->type = 1; p->flags = 0x22; p->getter = 508; p->putter = (s32)SetCameraFogFar; p++;
    p->type = 1; p->flags = 0x22; p->getter = 512; p->putter = (s32)SetCameraFogStrength; p++;
    p->type = 1; p->flags = 0x22; p->getter = 448; p->putter = (s32)SetCameraDistanceScale; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)PushScriptCameraStackValue; p->putter = 1; p++;
    p->type = 4177; p->flags = 0x1; p->getter = 0; p->f10 = (s32)PopScriptCameraStackValue; p->putter = 0; p++;
    p->type = 4177; p->flags = 0x1; p->getter = 0; p->f10 = (s32)PeekScriptCameraStackValue; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptCameraControllerSettings; p->putter = 3; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)RecordScriptCameraTimestamp; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)RequestScriptPlainCameraSnap; p->putter = 0; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (s32)TestScriptSphereInCameraView; p->putter = 3; p++;
    p->type = 6; p->flags = 0x80; p->offset = 720; p++;
    p->type = 2; p->flags = 0x80; p->offset = 736; p++;
    p->type = 2; p->flags = 0x80; p->offset = 752; p++;
    p->type = 2; p->flags = 0x80; p->offset = 768; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)PushScriptObjectCameraController; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)RemoveScriptObjectCameraController; p->putter = 0; p++;
    p->type = 0; p->flags = 0x92; p->getter = 720; p->putter = 720; p->offset = 720; p++;
    p->type = 4124; p->flags = 0x92; p->getter = 1364; p->putter = 1364; p->offset = 1364; p++;
    p->type = 6; p->flags = 0x1100; p->offset = (s32)AddTrackedKey; p->target = (PropertyTarget)GetContactTrackerRecord; p++;
    p->type = 8193; p->flags = 0x1020; p->putter = (s32)AddTrackedNode; p->target = (PropertyTarget)GetContactTrackerRecord; p++;
    p->type = 8193; p->flags = 0x1020; p->putter = (s32)RemoveTrackedNode; p->target = (PropertyTarget)GetContactTrackerRecord; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ClearScriptTrackedNodes; p->putter = 0; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1368; p->putter = 1368; p->offset = 1368; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1372; p->putter = 1372; p->offset = 1372; p++;
    p->type = 4127; p->flags = 0x92; p->getter = 136; p->putter = 136; p->offset = 136; p++;
    p->type = 1; p->flags = 0x92; p->getter = 140; p->putter = 140; p->offset = 140; p++;
    p->type = 0; p->flags = 0x92; p->getter = 144; p->putter = 144; p->offset = 144; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AppendFlaggedObjectIdB; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AppendFlaggedObjectIdA; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)SetFlaggedChildId; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)CollectScriptNumberedItem; p->putter = 0; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1448; p->putter = 1448; p->offset = 1448; p++;
    p->type = 0; p->flags = 0x4; p->getter = (s32)GetNumberedItemFlag; p++;
    p->type = 1; p->flags = 0x122; p->getter = 1360; p->putter = (s32)SetOffsetScale; p->offset = (s32)SetOffsetScale; p++;
    p->type = 1; p->flags = 0x892; p->getter = 92; p->putter = 92; p->offset = 92; p->floatValue = 50.0f; p++;
    p->type = 4131; p->flags = 0x892; p->getter = 88; p->putter = 88; p->offset = 88; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x92; p->getter = 104; p->putter = 104; p->offset = 104; p++;
    p->type = 6; p->flags = 0x80; p->offset = 96; p++;
    p->type = 0; p->flags = 0x92; p->getter = 108; p->putter = 108; p->offset = 108; p++;
    p->type = 1; p->flags = 0x92; p->getter = 112; p->putter = 112; p->offset = 112; p++;
    p->type = 0; p->flags = 0x92; p->getter = 116; p->putter = 116; p->offset = 116; p++;
    p->type = 4131; p->flags = 0x892; p->getter = 64; p->putter = 64; p->offset = 64; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x92; p->getter = 76; p->putter = 76; p->offset = 76; p++;
    p->type = 6; p->flags = 0x80; p->offset = 68; p++;
    p->type = 4164; p->flags = 0x92; p->getter = 80; p->putter = 80; p->offset = 80; p++;
    p->type = 0; p->flags = 0x92; p->getter = 84; p->putter = 84; p->offset = 84; p++;
    p->type = 1; p->flags = 0x92; p->getter = 88; p->putter = 88; p->offset = 88; p++;
    p->type = 0; p->flags = 0x92; p->getter = 92; p->putter = 92; p->offset = 92; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1376; p->putter = 1376; p->offset = 1376; p->floatValue = 50.0f; p++;
    p->type = 5; p->flags = 0x892; p->getter = 1380; p->putter = 1380; p->offset = 1380; p->intValue = 10; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1384; p->putter = 1384; p->offset = 1384; p++;
    p->type = 2; p->flags = 0x92; p->getter = 64; p->putter = 64; p->offset = 64; p++;
    p->type = 14; p->flags = 0x92; p->getter = 80; p->putter = 80; p->offset = 80; p++;
    p->type = 14; p->flags = 0x92; p->getter = 84; p->putter = 84; p->offset = 84; p++;
    p->type = 4178; p->flags = 0x92; p->getter = 88; p->putter = 88; p->offset = 88; p++;
    p->type = 18; p->flags = 0x0; p++;
    p->type = 0; p->flags = 0x92; p->getter = 96; p->putter = 96; p->offset = 96; p++;
    p->type = 6; p->flags = 0x80; p->offset = 100; p++;
    p->type = 8302; p->flags = 0x12; p->getter = 104; p->putter = 104; p++;
    p->type = 1; p->flags = 0x92; p->getter = 92; p->putter = 92; p->offset = 92; p++;
    p->type = 6; p->flags = 0xA2; p->getter = 2340; p->putter = (s32)SetAgentPathObjectId; p->offset = 2340; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1848; p->putter = 1848; p->offset = 1848; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1856; p->putter = 1856; p->offset = 1856; p++;
    p->type = 1; p->flags = 0x112; p->getter = 1868; p->putter = 1868; p->offset = (s32)SetAgentAngleLimitDegrees; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)SetScriptAgentStateClipId; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptAgentStateClip; p->putter = 2; p++;
    p->type = 8323; p->flags = 0x1; p->getter = 0; p->f10 = (s32)GetScriptAgentStateClip; p->putter = 1; p++;
    p->type = 1; p->flags = 0x92; p->getter = 2672; p->putter = 2672; p->offset = 2672; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)AddScriptAgentClipGroup; p->f10 = 0; p->putter = 4; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)AddScriptAgentMeshKey; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)AddScriptAgentExtraClip; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ForceScriptAgentState; p->putter = 2; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)SetScriptAgentSecondaryClipId; p->f10 = 0; p->putter = 2; p++;
    p->type = 5; p->flags = 0x92; p->getter = 2664; p->putter = 2664; p->offset = 2664; p++;
    p->type = 0; p->flags = 0x92; p->getter = 2668; p->putter = 2668; p->offset = 2668; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SteerScriptAgentAlongPath; p->putter = 0; p++;
    p->type = 10; p->flags = 0x92; p->getter = 2972; p->putter = 2972; p->offset = 2972; p++;
    p->type = 0; p->flags = 0x92; p->getter = 2944; p->putter = 2944; p->offset = 2944; p++;
    p->type = 6; p->flags = 0x92; p->getter = 2892; p->putter = 2892; p->offset = 2892; p++;
    p->type = 8195; p->flags = 0x24; p->getter = (s32)StoreAgentTarget; p->putter = (s32)SetAgentSecondaryTarget; p++;
    p->type = 0; p->flags = 0x92; p->getter = 2884; p->putter = 2884; p->offset = 2884; p++;
    p->type = 0; p->flags = 0x92; p->getter = 2844; p->putter = 2844; p->offset = 2844; p++;
    p->type = 1; p->flags = 0x92; p->getter = 2848; p->putter = 2848; p->offset = 2848; p++;
    p->type = 9; p->flags = 0x92; p->getter = 2864; p->putter = 2864; p->offset = 2864; p++;
    p->type = 4174; p->flags = 0x92; p->getter = 2336; p->putter = 2336; p->offset = 2336; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptAgentMainClip; p->putter = 1; p++;
    p->type = 5; p->flags = 0x92; p->getter = 2904; p->putter = 2904; p->offset = 2904; p++;
    p->type = 2; p->flags = 0x92; p->getter = 2912; p->putter = 2912; p->offset = 2912; p++;
    p->type = 0; p->flags = 0x92; p->getter = 2928; p->putter = 2928; p->offset = 2928; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)SetAgentMemberGroupId; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)SetAgentTargetSetId; p++;
    p->type = 1; p->flags = 0x80; p->offset = 2840; p++;
    p->type = 1; p->flags = 0x92; p->getter = 3024; p->putter = 3024; p->offset = 3024; p++;
    p->type = 0; p->flags = 0x92; p->getter = 3028; p->putter = 3028; p->offset = 3028; p++;
    p->type = 4133; p->flags = 0x2; p->getter = 1828; p++;
    p->type = 0; p->flags = 0x92; p->getter = 2752; p->putter = 2752; p->offset = 2752; p++;
    p->type = 0; p->flags = 0x4; p->getter = (s32)IsAgentNearPathEnd; p++;
    p->type = 10; p->flags = 0x92; p->getter = 3040; p->putter = 3040; p->offset = 3040; p++;
    p->type = 0; p->flags = 0x92; p->getter = 3036; p->putter = 3036; p->offset = 3036; p++;
    p->type = 1; p->flags = 0x92; p->getter = 3048; p->putter = 3048; p->offset = 3048; p++;
    p->type = 0; p->flags = 0x92; p->getter = 3032; p->putter = 3032; p->offset = 3032; p++;
    p->type = 0; p->flags = 0x92; p->getter = 3080; p->putter = 3080; p->offset = 3080; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddOwnedWantedId; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddListedWantedId; p++;
    p->type = 1; p->flags = 0x92; p->getter = 3096; p->putter = 3096; p->offset = 3096; p++;
    p->type = 1; p->flags = 0x92; p->getter = 3100; p->putter = 3100; p->offset = 3100; p++;
    p->type = 1; p->flags = 0x92; p->getter = 3104; p->putter = 3104; p->offset = 3104; p++;
    p->type = 1; p->flags = 0x92; p->getter = 3108; p->putter = 3108; p->offset = 3108; p++;
    p->type = 6; p->flags = 0x92; p->getter = 3112; p->putter = 3112; p->offset = 3112; p++;
    p->type = 6; p->flags = 0x80; p->offset = 3088; p++;
    p->type = 8288; p->flags = 0x2; p->getter = 3092; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)SetScriptCompanionAgentLookId; p->f10 = 0; p->putter = 2; p++;
    p->type = 0; p->flags = 0x92; p->getter = 3272; p->putter = 3272; p->offset = 3272; p++;
    p->type = 0; p->flags = 0x92; p->getter = 3276; p->putter = 3276; p->offset = 3276; p++;
    p->type = 4197; p->flags = 0x92; p->getter = 3280; p->putter = 3280; p->offset = 3280; p++;
    p->type = 6; p->flags = 0x92; p->getter = 3052; p->putter = 3052; p->offset = 3052; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddCompanionAgentExcludedId; p++;
    p->type = 1; p->flags = 0x880; p->offset = 1740; p->floatValue = 35.0f; p++;
    p->type = 1; p->flags = 0x120; p->putter = (s32)ScaleTurningColliderRamp; p->offset = (s32)ScaleTurningColliderRamp; p++;
    p->type = 1; p->flags = 0x122; p->getter = 1792; p->putter = (s32)SetTurningColliderGravityScale; p->offset = (s32)SetTurningColliderGravityScale; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1372; p->putter = 1372; p->offset = 1372; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1376; p->putter = 1376; p->offset = 1376; p++;
    p->type = 4135; p->flags = 0x92; p->getter = 1360; p->putter = 1360; p->offset = 1360; p++;
    p->type = 4136; p->flags = 0x92; p->getter = 1544; p->putter = 1544; p->offset = 1544; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1380; p->putter = 1380; p->offset = 1380; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1384; p->putter = 1384; p->offset = 1384; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1396; p->putter = 1396; p->offset = 1396; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1388; p->putter = 1388; p->offset = 1388; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1472; p->putter = 1472; p->offset = 1472; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)StartScriptChildGroupDelay; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)StepScriptChildGroupObject; p->putter = 0; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1652; p->putter = 1652; p->offset = 1652; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1656; p->putter = 1656; p->offset = 1656; p++;
    p->type = 4124; p->flags = 0x92; p->getter = 1660; p->putter = 1660; p->offset = 1660; p++;
    p->type = 14; p->flags = 0x1092; p->getter = 0; p->putter = 0; p->offset = 0; p->target = (PropertyTarget)GetChildGroupSoundParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 4; p->putter = 4; p->offset = 4; p->target = (PropertyTarget)GetChildGroupSoundParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 8; p->putter = 8; p->offset = 8; p->target = (PropertyTarget)GetChildGroupSoundParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 12; p->putter = 12; p->offset = 12; p->target = (PropertyTarget)GetChildGroupSoundParams; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1368; p->putter = 1368; p->offset = 1368; p++;
    p->type = 0; p->flags = 0x82; p->getter = 1668; p->offset = 1668; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)PlaceScriptPlayerOnGround; p->putter = 3; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ReleaseScriptPlayerToState2; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)IgnoreScriptPlayerArgument; p->putter = 1; p++;
    p->type = 0; p->flags = 0x92; p->getter = 8640; p->putter = 8640; p->offset = 8640; p++;
    p->type = 4178; p->flags = 0x22; p->getter = 10008; p->putter = (s32)SetPlayerPadSelectMode; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptPlayerPath; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SwitchScriptPlayerState11; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SeekScriptObjects105Animations; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SwapInScriptPlayerStandIn; p->putter = 0; p++;
    p->type = 0; p->flags = 0x92; p->getter = 11220; p->putter = 11220; p->offset = 11220; p++;
    p->type = 0; p->flags = 0xA2; p->getter = 11224; p->putter = (s32)SetPlayerProbeContactsDisabled; p->offset = 11224; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)QueueScriptPlayerWalkerActivation; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)QueueScriptPlayerFirstActivation; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)QueueScriptPlayerSecondActivation; p->putter = 1; p++;
    p->type = 4144; p->flags = 0x80; p->offset = 68; p++;
    p->type = 6; p->flags = 0x80; p->offset = 52; p++;
    p->type = 6; p->flags = 0x80; p->offset = 56; p++;
    p->type = 4127; p->flags = 0x80; p->offset = 76; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)SetScriptAimBlendGridVector; p->f10 = 0; p->putter = 3; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)SetScriptAimBlendGridVectorFlagged; p->f10 = 0; p->putter = 3; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1552; p->putter = 1552; p->offset = 1552; p->floatValue = 500.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1556; p->putter = 1556; p->offset = 1556; p->floatValue = 500.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1520; p->putter = 1520; p->offset = 1520; p->floatValue = 15.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1560; p->putter = 1560; p->offset = 1560; p->floatValue = 1000.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1520; p->putter = 1520; p->offset = 1520; p->floatValue = 15.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1572; p->putter = 1572; p->offset = 1572; p->floatValue = 3000.0f; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1544; p->putter = 1544; p->offset = 1544; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1568; p->putter = 1568; p->offset = 1568; p->floatValue = 300.0f; p++;
    p->type = 4154; p->flags = 0x2; p->getter = 1360; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1636; p->putter = 1636; p->offset = 1636; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1640; p->putter = 1640; p->offset = 1640; p++;
    p->type = 1; p->flags = 0x880; p->offset = 736; p->floatValue = 50.0f; p++;
    p->type = 1; p->flags = 0x880; p->offset = 740; p->floatValue = 25.0f; p++;
    p->type = 1; p->flags = 0x880; p->offset = 744; p->intValue = 0; p++;
    p->type = 1; p->flags = 0x880; p->offset = 748; p->floatValue = 3.5f; p++;
    p->type = 5; p->flags = 0x880; p->offset = 752; p->intValue = 1; p++;
    p->type = 2; p->flags = 0x92; p->getter = 768; p->putter = 768; p->offset = 768; p++;
    p->type = 0; p->flags = 0x92; p->getter = 784; p->putter = 784; p->offset = 784; p++;
    p->type = 2; p->flags = 0x92; p->getter = 800; p->putter = 800; p->offset = 800; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)SetPairControllerFirstTemplateId; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)SetPairControllerSecondTemplateId; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)SetPairControllerHostId; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)SetPairControllerExtraId; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AppendPairControllerId; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 0; p->putter = 0; p->offset = 0; p->target = (PropertyTarget)GetPairControllerPose; p++;
    p->type = 1; p->flags = 0x1082; p->getter = 4; p->offset = 4; p->target = (PropertyTarget)GetPairControllerPose; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 16; p->putter = 16; p->offset = 16; p->target = (PropertyTarget)GetPairControllerPose; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 32; p->putter = 32; p->offset = 32; p->target = (PropertyTarget)GetPairControllerPose; p++;
    p->type = 1; p->flags = 0x1082; p->getter = 36; p->offset = 36; p->target = (PropertyTarget)GetPairControllerPose; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 48; p->putter = 48; p->offset = 48; p->target = (PropertyTarget)GetPairControllerPose; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 64; p->putter = 64; p->offset = 64; p->target = (PropertyTarget)GetPairControllerPose; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 72; p->putter = 72; p->offset = 72; p->target = (PropertyTarget)GetPairControllerPose; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 80; p->putter = 80; p->offset = 80; p->target = (PropertyTarget)GetPairControllerPose; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 96; p->putter = 96; p->offset = 96; p->target = (PropertyTarget)GetPairControllerPose; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 104; p->putter = 104; p->offset = 104; p->target = (PropertyTarget)GetPairControllerPose; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 112; p->putter = 112; p->offset = 112; p->target = (PropertyTarget)GetPairControllerPose; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 128; p->putter = 128; p->offset = 128; p->target = (PropertyTarget)GetPairControllerPose; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 132; p->putter = 132; p->offset = 132; p->target = (PropertyTarget)GetPairControllerPose; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 144; p->putter = 144; p->offset = 144; p->target = (PropertyTarget)GetPairControllerPose; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 160; p->putter = 160; p->offset = 160; p->target = (PropertyTarget)GetPairControllerPose; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 164; p->putter = 164; p->offset = 164; p->target = (PropertyTarget)GetPairControllerPose; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 176; p->putter = 176; p->offset = 176; p->target = (PropertyTarget)GetPairControllerPose; p++;
    p->type = 2; p->flags = 0x92; p->getter = 816; p->putter = 816; p->offset = 816; p++;
    p->type = 1; p->flags = 0x92; p->getter = 832; p->putter = 832; p->offset = 832; p++;
    p->type = 1; p->flags = 0x92; p->getter = 836; p->putter = 836; p->offset = 836; p++;
    p->type = 1; p->flags = 0x92; p->getter = 840; p->putter = 840; p->offset = 840; p++;
    p->type = 1; p->flags = 0x92; p->getter = 844; p->putter = 844; p->offset = 844; p++;
    p->type = 1; p->flags = 0x92; p->getter = 848; p->putter = 848; p->offset = 848; p++;
    p->type = 5; p->flags = 0x82; p->getter = 952; p->offset = 952; p++;
    p->type = 4147; p->flags = 0x82; p->getter = 1612; p->offset = 1612; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1568; p->putter = 1568; p->offset = 1568; p++;
    p->type = 9; p->flags = 0x92; p->getter = 976; p->putter = 976; p->offset = 976; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1576; p->putter = 1576; p->offset = 1576; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1412; p->putter = 1412; p->offset = 1412; p++;
    p->type = 5; p->flags = 0x80; p->offset = 1384; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1392; p->putter = 1392; p->offset = 1392; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1388; p->putter = 1388; p->offset = 1388; p++;
    p->type = 9; p->flags = 0x92; p->getter = 1424; p->putter = 1424; p->offset = 1424; p++;
    p->type = 4145; p->flags = 0x22; p->getter = 1360; p->putter = (s32)SetPooledObjectState; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1368; p->putter = 1368; p->offset = 1368; p->floatValue = 2500.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1372; p->putter = 1372; p->offset = 1372; p->floatValue = 20.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1376; p->putter = 1376; p->offset = 1376; p->floatValue = 30.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1380; p->putter = 1380; p->offset = 1380; p->floatValue = 1.5f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1384; p->putter = 1384; p->offset = 1384; p->floatValue = 10.0f; p++;
    p->type = 6; p->flags = 0x80; p->offset = 1728; p++;
    p->type = 5; p->flags = 0x880; p->offset = 1732; p->intValue = 5; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1744; p->putter = 1744; p->offset = 1744; p->floatValue = 1.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1748; p->putter = 1748; p->offset = 1748; p->floatValue = 20.0f; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddPooledHolderItem; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ResetScriptCollectedItems; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)CollectScriptItem; p->putter = 1; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1680; p->putter = 1680; p->offset = 1680; p->floatValue = 800.0f; p++;
    p->type = 8194; p->flags = 0x12; p->getter = 1684; p->putter = 1684; p++;
    p->type = 2; p->flags = 0x12; p->getter = 1696; p->putter = 1696; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1720; p->putter = 1720; p->offset = 1720; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)AddScriptContactListId; p->f10 = 0; p->putter = 1; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)AddScriptContactListKind; p->f10 = 0; p->putter = 1; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1776; p->putter = 1776; p->offset = 1776; p->floatValue = 2000.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1780; p->putter = 1780; p->offset = 1780; p->floatValue = 5000.0f; p++;
    p->type = 2; p->flags = 0x12; p->getter = 1792; p->putter = 1792; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1776; p->putter = 1776; p->offset = 1776; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1780; p->putter = 1780; p->offset = 1780; p->floatValue = 1500.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1784; p->putter = 1784; p->offset = 1784; p->floatValue = 1.0f; p++;
    p->type = 2; p->flags = 0x92; p->getter = 1792; p->putter = 1792; p->offset = 1792; p++;
    p->type = 1; p->flags = 0x892; p->getter = 88; p->putter = 88; p->offset = 88; p->floatValue = 100.0f; p++;
    p->type = 6; p->flags = 0x880; p->offset = 92; p->intValue = -1; p++;
    p->type = 1; p->flags = 0x92; p->getter = 728; p->putter = 728; p->offset = 728; p++;
    p->type = 6; p->flags = 0x82; p->getter = 736; p->offset = 736; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)AddScriptStateResetEntry; p->f10 = 0; p->putter = 4; p++;
    p->type = 1; p->flags = 0x92; p->getter = 3088; p->putter = 3088; p->offset = 3088; p++;
    p->type = 1; p->flags = 0x92; p->getter = 3092; p->putter = 3092; p->offset = 3092; p++;
    p->type = 6; p->flags = 0x80; p->offset = 3096; p++;
    p->type = 8315; p->flags = 0x12; p->getter = 3100; p->putter = 3100; p++;
    p->type = 10; p->flags = 0x92; p->getter = 3104; p->putter = 3104; p->offset = 3104; p++;
    p->type = 10; p->flags = 0x92; p->getter = 3112; p->putter = 3112; p->offset = 3112; p++;
    p->type = 6; p->flags = 0x80; p->offset = 3120; p++;
    p->type = 8315; p->flags = 0x12; p->getter = 3124; p->putter = 3124; p++;
    p->type = 0; p->flags = 0x92; p->getter = 3132; p->putter = 3132; p->offset = 3132; p++;
    p->type = 0; p->flags = 0x92; p->getter = 3136; p->putter = 3136; p->offset = 3136; p++;
    p->type = 1; p->flags = 0x92; p->getter = 752; p->putter = 752; p->offset = 752; p++;
    p->type = 9; p->flags = 0x92; p->getter = 768; p->putter = 768; p->offset = 768; p++;
    p->type = 10; p->flags = 0x92; p->getter = 816; p->putter = 816; p->offset = 816; p++;
    p->type = 9; p->flags = 0x92; p->getter = 784; p->putter = 784; p->offset = 784; p++;
    p->type = 10; p->flags = 0x92; p->getter = 824; p->putter = 824; p->offset = 824; p++;
    p->type = 9; p->flags = 0x92; p->getter = 800; p->putter = 800; p->offset = 800; p++;
    p->type = 10; p->flags = 0x92; p->getter = 832; p->putter = 832; p->offset = 832; p++;
    p->type = 1; p->flags = 0x92; p->getter = 912; p->putter = 912; p->offset = 912; p++;
    p->type = 1; p->flags = 0x92; p->getter = 840; p->putter = 840; p->offset = 840; p++;
    p->type = 1; p->flags = 0x92; p->getter = 844; p->putter = 844; p->offset = 844; p++;
    p->type = 1; p->flags = 0x92; p->getter = 848; p->putter = 848; p->offset = 848; p++;
    p->type = 1; p->flags = 0x92; p->getter = 852; p->putter = 852; p->offset = 852; p++;
    p->type = 1; p->flags = 0x92; p->getter = 856; p->putter = 856; p->offset = 856; p++;
    p->type = 1; p->flags = 0x122; p->getter = 864; p->putter = (s32)SetOnOffObjectBlockValue; p->offset = (s32)SetOnOffObjectBlockValue; p++;
    p->type = 2; p->flags = 0x92; p->getter = 864; p->putter = 864; p->offset = 864; p++;
    p->type = 0; p->flags = 0x92; p->getter = 896; p->putter = 896; p->offset = 896; p++;
    p->type = 4108; p->flags = 0x92; p->getter = 1044; p->putter = 1044; p->offset = 1044; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1048; p->putter = 1048; p->offset = 1048; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1052; p->putter = 1052; p->offset = 1052; p++;
    p->type = 5; p->flags = 0x92; p->getter = 904; p->putter = 904; p->offset = 904; p++;
    p->type = 0; p->flags = 0x92; p->getter = 900; p->putter = 900; p->offset = 900; p++;
    p->type = 4165; p->flags = 0x92; p->getter = 1072; p->putter = 1072; p->offset = 1072; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1056; p->putter = 1056; p->offset = 1056; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1060; p->putter = 1060; p->offset = 1060; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1064; p->putter = 1064; p->offset = 1064; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1068; p->putter = 1068; p->offset = 1068; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1076; p->putter = 1076; p->offset = 1076; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1080; p->putter = 1080; p->offset = 1080; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1088; p->putter = 1088; p->offset = 1088; p++;
    p->type = 8194; p->flags = 0x12; p->getter = 1092; p->putter = 1092; p++;
    p->type = 9; p->flags = 0x92; p->getter = 1104; p->putter = 1104; p->offset = 1104; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1120; p->putter = 1120; p->offset = 1120; p++;
    p->type = 4109; p->flags = 0x2; p->getter = 916; p++;
    p->type = 4109; p->flags = 0xA2; p->getter = 920; p->putter = (s32)SetOnOffObjectForcedState; p->offset = 920; p++;
    p->type = 1; p->flags = 0x92; p->getter = 880; p->putter = 880; p->offset = 880; p++;
    p->type = 1; p->flags = 0x92; p->getter = 884; p->putter = 884; p->offset = 884; p++;
    p->type = 6; p->flags = 0xA0; p->putter = (s32)FollowObjectById; p->offset = 1400; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptCurrentTargetFollower; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ClearScriptCurrentTargetFollower; p->putter = 0; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1472; p->putter = 1472; p->offset = 1472; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1476; p->putter = 1476; p->offset = 1476; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1480; p->putter = 1480; p->offset = 1480; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1496; p->putter = 1496; p->offset = 1496; p++;
    p->type = 6; p->flags = 0x80; p->offset = 1952; p++;
    p->type = 8318; p->flags = 0x12; p->getter = 1956; p->putter = 1956; p++;
    p->type = 6; p->flags = 0x80; p->offset = 1960; p++;
    p->type = 8292; p->flags = 0x12; p->getter = 1964; p->putter = 1964; p++;
    p->type = 4170; p->flags = 0x92; p->getter = 788; p->putter = 788; p->offset = 788; p++;
    p->type = 1; p->flags = 0x92; p->getter = 796; p->putter = 796; p->offset = 796; p++;
    p->type = 1; p->flags = 0x92; p->getter = 800; p->putter = 800; p->offset = 800; p++;
    p->type = 4171; p->flags = 0x92; p->getter = 792; p->putter = 792; p->offset = 792; p++;
    p->type = 1; p->flags = 0x92; p->getter = 804; p->putter = 804; p->offset = 804; p++;
    p->type = 1; p->flags = 0x92; p->getter = 808; p->putter = 808; p->offset = 808; p++;
    p->type = 1; p->flags = 0x92; p->getter = 812; p->putter = 812; p->offset = 812; p++;
    p->type = 1; p->flags = 0x92; p->getter = 816; p->putter = 816; p->offset = 816; p++;
    p->type = 1; p->flags = 0x92; p->getter = 820; p->putter = 820; p->offset = 820; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)AddScriptObjectPoolEntry; p->f10 = 0; p->putter = 4; p++;
    p->type = 0; p->flags = 0x1082; p->getter = 4; p->offset = 4; p->target = (PropertyTarget)GetObjectPoolShare; p++;
    p->type = 4158; p->flags = 0x92; p->getter = 64; p->putter = 64; p->offset = 64; p++;
    p->type = 5; p->flags = 0x12; p->getter = 68; p->putter = 68; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)EnableScriptObjectPoolEntry; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)DisableScriptObjectPoolEntry; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptObjectPoolEntryCount; p->putter = 2; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ChooseScriptObjectPoolItem; p->putter = 0; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ReleaseScriptObjectPoolItem; p->putter = 1; p++;
    p->type = 8195; p->flags = 0x2; p->getter = 72; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ResetScriptPlacementRecord; p->putter = 0; p++;
    p->type = 6; p->flags = 0x80; p->offset = 76; p++;
    p->type = 8194; p->flags = 0x12; p->getter = 104; p->putter = 104; p++;
    p->type = 8318; p->flags = 0x12; p->getter = 96; p->putter = 96; p++;
    p->type = 8307; p->flags = 0x12; p->getter = 100; p->putter = 100; p++;
    p->type = 2; p->flags = 0x92; p->getter = 112; p->putter = 112; p->offset = 112; p++;
    p->type = 4; p->flags = 0x92; p->getter = 128; p->putter = 128; p->offset = 128; p++;
    p->type = 2; p->flags = 0x92; p->getter = 176; p->putter = 176; p->offset = 176; p++;
    p->type = 2; p->flags = 0x92; p->getter = 192; p->putter = 192; p->offset = 192; p++;
    p->type = 10; p->flags = 0x92; p->getter = 208; p->putter = 208; p->offset = 208; p++;
    p->type = 1; p->flags = 0x92; p->getter = 216; p->putter = 216; p->offset = 216; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ResetScriptObjectPoolReleaseRecord; p->putter = 0; p++;
    p->type = 6; p->flags = 0x92; p->getter = 80; p->putter = 80; p->offset = 80; p++;
    p->type = 8194; p->flags = 0x12; p->getter = 224; p->putter = 224; p++;
    p->type = 8309; p->flags = 0x12; p->getter = 228; p->putter = 228; p++;
    p->type = 2; p->flags = 0x92; p->getter = 240; p->putter = 240; p->offset = 240; p++;
    p->type = 4166; p->flags = 0x92; p->getter = 256; p->putter = 256; p->offset = 256; p++;
    p->type = 9; p->flags = 0x92; p->getter = 304; p->putter = 304; p->offset = 304; p++;
    p->type = 9; p->flags = 0x92; p->getter = 304; p->putter = 304; p->offset = 304; p++;
    p->type = 10; p->flags = 0x92; p->getter = 320; p->putter = 320; p->offset = 320; p++;
    p->type = 9; p->flags = 0x92; p->getter = 272; p->putter = 272; p->offset = 272; p++;
    p->type = 10; p->flags = 0x92; p->getter = 288; p->putter = 288; p->offset = 288; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ClearScriptObjectPoolHeadingRecord; p->putter = 0; p++;
    p->type = 4153; p->flags = 0x92; p->getter = 336; p->putter = 336; p->offset = 336; p++;
    p->type = 6; p->flags = 0x80; p->offset = 84; p++;
    p->type = 8307; p->flags = 0x12; p->getter = 352; p->putter = 352; p++;
    p->type = 1; p->flags = 0x92; p->getter = 340; p->putter = 340; p->offset = 340; p++;
    p->type = 1; p->flags = 0x92; p->getter = 344; p->putter = 344; p->offset = 344; p++;
    p->type = 1; p->flags = 0x92; p->getter = 348; p->putter = 348; p->offset = 348; p++;
    p->type = 6; p->flags = 0x80; p->offset = 88; p++;
    p->type = 8194; p->flags = 0x2; p->getter = 92; p++;
    p->type = 4155; p->flags = 0x882; p->getter = 1360; p->offset = 1360; p->intValue = 0; p++;
    p->type = 4156; p->flags = 0x882; p->getter = 1376; p->offset = 1376; p->intValue = 0; p++;
    p->type = 4156; p->flags = 0x22; p->getter = 1364; p->putter = (s32)SetObjectCyclerState; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1552; p->putter = 1552; p->offset = 1552; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1560; p->putter = 1560; p->offset = 1560; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1568; p->putter = 1568; p->offset = 1568; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1576; p->putter = 1576; p->offset = 1576; p++;
    p->type = 6; p->flags = 0x80; p->offset = 1584; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1592; p->putter = 1592; p->offset = 1592; p->floatValue = 0.800000011920929f; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1596; p->putter = 1596; p->offset = 1596; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1604; p->putter = 1604; p->offset = 1604; p->floatValue = 0.019999999552965164f; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1616; p->putter = 1616; p->offset = 1616; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1624; p->putter = 1624; p->offset = 1624; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1632; p->putter = 1632; p->offset = 1632; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1648; p->putter = 1648; p->offset = 1648; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1668; p->putter = 1668; p->offset = 1668; p->floatValue = 300.0f; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1680; p->putter = 1680; p->offset = 1680; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1684; p->putter = 1684; p->offset = 1684; p++;
    p->type = 4167; p->flags = 0x22; p->getter = 724; p->putter = (s32)SetStepSequenceState; p++;
    p->type = 6; p->flags = 0x80; p->offset = 768; p++;
    p->type = 0; p->flags = 0x92; p->getter = 804; p->putter = 804; p->offset = 804; p++;
    p->type = 0; p->flags = 0x92; p->getter = 808; p->putter = 808; p->offset = 808; p++;
    p->type = 0; p->flags = 0x92; p->getter = 812; p->putter = 812; p->offset = 812; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)SetScriptStepSequenceModeOne; p->f10 = 0; p->putter = 0; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)SetScriptStepSequenceCameraMode; p->f10 = 0; p->putter = 0; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)AddScriptSequenceExtraTarget; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ChooseScriptStepSequenceState; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ResetScriptStepSequence; p->putter = 0; p++;
    p->type = 6; p->flags = 0x92; p->getter = 780; p->putter = 780; p->offset = 780; p++;
    p->type = 0; p->flags = 0x24; p->getter = (s32)ReadSequenceTarget; p->putter = (s32)WriteSequenceTarget; p++;
    p->type = 0; p->flags = 0x82; p->getter = 816; p->offset = 816; p++;
    p->type = 6; p->flags = 0x92; p->getter = 732; p->putter = 732; p->offset = 732; p++;
    p->type = 1; p->flags = 0x92; p->getter = 736; p->putter = 736; p->offset = 736; p++;
    p->type = 4169; p->flags = 0x42; p->getter = 720; p->putter = 204; p++;
    p->type = 0; p->flags = 0x92; p->getter = 820; p->putter = 820; p->offset = 820; p++;
    p->type = 1; p->flags = 0x92; p->getter = 904; p->putter = 904; p->offset = 904; p++;
    p->type = 0; p->flags = 0x92; p->getter = 832; p->putter = 832; p->offset = 832; p++;
    p->type = 10; p->flags = 0x92; p->getter = 912; p->putter = 912; p->offset = 912; p++;
    p->type = 10; p->flags = 0x92; p->getter = 912; p->putter = 912; p->offset = 912; p++;
    p->type = 0; p->flags = 0x0; p++;
    p->type = 13; p->flags = 0x92; p->getter = 720; p->putter = 720; p->offset = 720; p++;
    p->type = 1; p->flags = 0x92; p->getter = 724; p->putter = 724; p->offset = 724; p++;
    p->type = 1; p->flags = 0x92; p->getter = 728; p->putter = 728; p->offset = 728; p++;
    p->type = 1; p->flags = 0x92; p->getter = 732; p->putter = 732; p->offset = 732; p++;
    p->type = 1; p->flags = 0x92; p->getter = 736; p->putter = 736; p->offset = 736; p++;
    p->type = 2; p->flags = 0x92; p->getter = 752; p->putter = 752; p->offset = 752; p++;
    p->type = 2; p->flags = 0x92; p->getter = 768; p->putter = 768; p->offset = 768; p++;
    p->type = 1; p->flags = 0x92; p->getter = 800; p->putter = 800; p->offset = 800; p++;
    p->type = 1; p->flags = 0x92; p->getter = 804; p->putter = 804; p->offset = 804; p++;
    p->type = 6; p->flags = 0xA0; p->putter = (s32)SetObjectLinkId; p->offset = 812; p++;
    p->type = 2; p->flags = 0x92; p->getter = 784; p->putter = 784; p->offset = 784; p++;
    p->type = 1; p->flags = 0x92; p->getter = 808; p->putter = 808; p->offset = 808; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddStateWalkerGroupId; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)QueueScriptWalkerActivationOnPlayer; p->putter = 0; p++;
    p->type = 5; p->flags = 0x100; p->offset = (s32)SetStateWalkerGroupMaskBit; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)AddScriptOscillatorXEntry; p->f10 = 0; p->putter = 0; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)AddScriptOscillatorYZEntry; p->f10 = 0; p->putter = 0; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 16; p->putter = 16; p->offset = 16; p->target = (PropertyTarget)GetOscillatorEntryForPeriod; p++;
    p->type = 1; p->flags = 0x124; p->getter = (s32)GetOscillatorEntryPeriod; p->putter = (s32)SetOscillatorEntryPeriod; p->offset = (s32)SetOscillatorEntryPeriod; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 104; p->putter = 104; p->offset = 104; p->target = (PropertyTarget)GetOscillatorEntryForPeriod; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 108; p->putter = 108; p->offset = 108; p->target = (PropertyTarget)GetOscillatorEntryForPeriod; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 32; p->putter = 32; p->offset = 32; p->target = (PropertyTarget)GetOscillatorEntryForPeriod; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 64; p->putter = 64; p->offset = 64; p->target = (PropertyTarget)GetOscillatorEntryForPeriod; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 48; p->putter = 48; p->offset = 48; p->target = (PropertyTarget)GetOscillatorEntryForPeriod; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 80; p->putter = 80; p->offset = 80; p->target = (PropertyTarget)GetOscillatorEntryForPeriod; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 16; p->putter = 16; p->offset = 16; p->target = (PropertyTarget)GetOscillatorEntryForVectors; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 48; p->putter = 48; p->offset = 48; p->target = (PropertyTarget)GetOscillatorEntryForVectors; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 56; p->putter = 56; p->offset = 56; p->target = (PropertyTarget)GetOscillatorEntryForVectors; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)AddScriptOscillatorEntryVectorA; p->f10 = 0; p->putter = 4; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 32; p->putter = 32; p->offset = 32; p->target = (PropertyTarget)GetOscillatorEntryForVectors; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 128; p->putter = 128; p->offset = 128; p->target = (PropertyTarget)GetOscillatorEntryForVectors; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 136; p->putter = 136; p->offset = 136; p->target = (PropertyTarget)GetOscillatorEntryForVectors; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)AddScriptOscillatorEntryVectorB; p->f10 = 0; p->putter = 4; p++;
    p->type = 5; p->flags = 0x2; p->getter = 56; p++;
    p->type = 5; p->flags = 0x12; p->getter = 1744; p->putter = 1744; p++;
    p->type = 0; p->flags = 0x92; p->getter = 3088; p->putter = 3088; p->offset = 3088; p++;
    p->type = 8339; p->flags = 0x2; p->getter = 3600; p++;
    p->type = 8307; p->flags = 0x92; p->getter = 3604; p->putter = 3604; p->offset = 3604; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)AdvanceScriptGaugeAgentPhase; p->putter = 0; p++;
    p->type = 1; p->flags = 0x4; p->getter = (s32)GetGaugeAgentLevelFactor; p++;
    p->type = 4175; p->flags = 0x22; p->getter = 1824; p->putter = (s32)SetTintBlendColliderState; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1852; p->putter = 1852; p->offset = 1852; p++;
    p->type = 1; p->flags = 0x92; p->getter = 88; p->putter = 88; p->offset = 88; p++;
    p->type = 0; p->flags = 0x92; p->getter = 92; p->putter = 92; p->offset = 92; p++;
    p->type = 0; p->flags = 0x92; p->getter = 64; p->putter = 64; p->offset = 64; p++;
    p->type = 1; p->flags = 0x892; p->getter = 68; p->putter = 68; p->offset = 68; p->floatValue = 1000.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 72; p->putter = 72; p->offset = 72; p->floatValue = 2.0f; p++;
    p->type = 1; p->flags = 0x92; p->getter = 76; p->putter = 76; p->offset = 76; p++;
    p->type = 0; p->flags = 0x92; p->getter = 80; p->putter = 80; p->offset = 80; p++;
    p->type = 6; p->flags = 0x80; p->offset = 84; p++;
    p->type = 8302; p->flags = 0x12; p->getter = 88; p->putter = 88; p++;
    p->type = 8339; p->flags = 0x2; p->getter = 1556; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1584; p->putter = 1584; p->offset = 1584; p++;
    p->type = 4177; p->flags = 0x92; p->getter = 1604; p->putter = 1604; p->offset = 1604; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1588; p->putter = 1588; p->offset = 1588; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AddPlayerLinkedColliderId; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1616; p->putter = 1616; p->offset = 1616; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1624; p->putter = 1624; p->offset = 1624; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1600; p->putter = 1600; p->offset = 1600; p++;
    p->type = 18; p->flags = 0x400; p->getter = (s32)AddScriptEntryRecordKey; p->f10 = 0; p->putter = 2; p++;
    p->type = 6; p->flags = 0x80; p->offset = 1612; p++;
    p->type = 6; p->flags = 0x80; p->offset = 1604; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1620; p->putter = 1620; p->offset = 1620; p++;
    p->type = 1; p->flags = 0x80; p->offset = 1672; p++;
    p->type = 8339; p->flags = 0x2; p->getter = 1556; p++;
    p->type = 8339; p->flags = 0x2; p->getter = 1720; p++;
    p->type = 2; p->flags = 0x80; p->offset = 1360; p++;
    p->type = 1; p->flags = 0x80; p->offset = 1384; p++;
    p->type = 10; p->flags = 0x80; p->offset = 1376; p++;
    p->type = 5; p->flags = 0x92; p->getter = 724; p->putter = 724; p->offset = 724; p++;
    p->type = 1; p->flags = 0x92; p->getter = 728; p->putter = 728; p->offset = 728; p++;
    p->type = 6; p->flags = 0x100; p->offset = (s32)AppendGaugeSlot; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 0; p->putter = 0; p->offset = 0; p->target = (PropertyTarget)GetGaugeParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 4; p->putter = 4; p->offset = 4; p->target = (PropertyTarget)GetGaugeParams; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 16; p->putter = 16; p->offset = 16; p->target = (PropertyTarget)GetGaugeParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 64; p->putter = 64; p->offset = 64; p->target = (PropertyTarget)GetGaugeParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 32; p->putter = 32; p->offset = 32; p->target = (PropertyTarget)GetGaugeParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 40; p->putter = 40; p->offset = 40; p->target = (PropertyTarget)GetGaugeParams; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 48; p->putter = 48; p->offset = 48; p->target = (PropertyTarget)GetGaugeParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 68; p->putter = 68; p->offset = 68; p->target = (PropertyTarget)GetGaugeParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 76; p->putter = 76; p->offset = 76; p->target = (PropertyTarget)GetGaugeParams; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 96; p->putter = 96; p->offset = 96; p->target = (PropertyTarget)GetGaugeParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 112; p->putter = 112; p->offset = 112; p->target = (PropertyTarget)GetGaugeParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 116; p->putter = 116; p->offset = 116; p->target = (PropertyTarget)GetGaugeParams; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 128; p->putter = 128; p->offset = 128; p->target = (PropertyTarget)GetGaugeParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 144; p->putter = 144; p->offset = 144; p->target = (PropertyTarget)GetGaugeParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 148; p->putter = 148; p->offset = 148; p->target = (PropertyTarget)GetGaugeParams; p++;
    p->type = 9; p->flags = 0x1092; p->getter = 160; p->putter = 160; p->offset = 160; p->target = (PropertyTarget)GetGaugeParams; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1680; p->putter = 1680; p->offset = 1680; p++;
    p->type = 9; p->flags = 0x92; p->getter = 1136; p->putter = 1136; p->offset = 1136; p++;
    p->type = 8339; p->flags = 0x2; p->getter = 1068; p++;
    p->type = 5; p->flags = 0x92; p->getter = 3108; p->putter = 3108; p->offset = 3108; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1552; p->putter = 1552; p->offset = 1552; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1556; p->putter = 1556; p->offset = 1556; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1560; p->putter = 1560; p->offset = 1560; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1564; p->putter = 1564; p->offset = 1564; p++;
    p->type = 8302; p->flags = 0x22; p->getter = 2096; p->putter = (s32)SetPathFollowerPath; p++;
    p->type = 8302; p->flags = 0x22; p->getter = 2120; p->putter = (s32)SetPathFollowerSecondPath; p++;
    p->type = 5; p->flags = 0x92; p->getter = 2820; p->putter = 2820; p->offset = 2820; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)AddScriptPathFollowerEntry; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)AddScriptPathFollowerActiveEntry; p->putter = 5; p++;
    p->type = 8330; p->flags = 0x12; p->getter = 2876; p->putter = 2876; p++;
    p->type = 4183; p->flags = 0x122; p->getter = 2868; p->putter = (s32)SetPathFollowerMode; p->offset = (s32)SetPathFollowerMode; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)ResetScriptPathFollower; p->putter = 0; p++;
    p->type = 4184; p->flags = 0x92; p->getter = 2864; p->putter = 2864; p->offset = 2864; p++;
    p->type = 5; p->flags = 0x92; p->getter = 2820; p->putter = 2820; p->offset = 2820; p++;
    p->type = 8311; p->flags = 0x12; p->getter = 2840; p->putter = 2840; p++;
    p->type = 8311; p->flags = 0x12; p->getter = 2844; p->putter = 2844; p++;
    p->type = 8272; p->flags = 0x12; p->getter = 2836; p->putter = 2836; p++;
    p->type = 1; p->flags = 0x92; p->getter = 2152; p->putter = 2152; p->offset = 2152; p++;
    p->type = 5; p->flags = 0x92; p->getter = 2136; p->putter = 2136; p->offset = 2136; p++;
    p->type = 9; p->flags = 0x92; p->getter = 1584; p->putter = 1584; p->offset = 1584; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1600; p->putter = 1600; p->offset = 1600; p++;
    p->type = 9; p->flags = 0x92; p->getter = 1616; p->putter = 1616; p->offset = 1616; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1632; p->putter = 1632; p->offset = 1632; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (s32)TestScriptPointAgainstObjectShape; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (s32)TestScriptPointInsideFaceTreeObject; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (s32)AddScriptSeekingAgentObject; p->putter = 1; p++;
    p->type = 8307; p->flags = 0x22; p->getter = 3112; p->putter = (s32)SetSeekingAgentStateTarget; p++;
    p->type = 8307; p->flags = 0x22; p->getter = 3108; p->putter = (s32)SetSeekingAgentTarget; p++;
    p->type = 2; p->flags = 0x4; p->getter = (s32)PickRandomPointOnPointGraph; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1740; p->putter = 1740; p->offset = 1740; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1744; p->putter = 1744; p->offset = 1744; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1748; p->putter = 1748; p->offset = 1748; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1752; p->putter = 1752; p->offset = 1752; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)StartScriptC24ObjectPath; p->putter = 2; p++;
    p->type = 4176; p->flags = 0x22; p->getter = 2992; p->putter = (s32)SetModeWalkerMode; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)ResetScriptEntryQueue; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)BindScriptEntryQueueToObject; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)UnbindScriptEntryQueue; p->putter = 0; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)AddScriptQueueEntryKind0; p->putter = 1; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)AddScriptQueueEntryKind1; p->putter = 1; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)AddScriptQueueEntryKind10; p->putter = 1; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)AddScriptQueueEntryKind2; p->putter = 1; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)AddScriptQueueEntryKind3; p->putter = 1; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)AddScriptQueueEntryKind4; p->putter = 2; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)AddScriptQueueEntryKind5; p->putter = 4; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)AddScriptQueueEntryKind6; p->putter = 3; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)AddScriptQueueEntryKind7; p->putter = 3; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)AddScriptQueueEntryKind8; p->putter = 3; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)AddScriptQueueEntryKind9; p->putter = 2; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)AddScriptQueueEntryKind11; p->putter = 1; p++;
    p->type = 0; p->flags = 0x92; p->getter = 104; p->putter = 104; p->offset = 104; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)AddScriptQueueEntryKind12; p->putter = 0; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)StartScriptColorFade; p->putter = 0; p++;
    p->type = 13; p->flags = 0x92; p->getter = 60; p->putter = 60; p->offset = 60; p++;
    p->type = 13; p->flags = 0x92; p->getter = 64; p->putter = 64; p->offset = 64; p++;
    p->type = 13; p->flags = 0x92; p->getter = 68; p->putter = 68; p->offset = 68; p++;
    p->type = 1; p->flags = 0x92; p->getter = 72; p->putter = 72; p->offset = 72; p++;
    p->type = 1; p->flags = 0x92; p->getter = 80; p->putter = 80; p->offset = 80; p++;
    p->type = 1; p->flags = 0x92; p->getter = 76; p->putter = 76; p->offset = 76; p++;
    p->type = 4188; p->flags = 0x92; p->getter = 88; p->putter = 88; p->offset = 88; p++;
    p->type = 8195; p->flags = 0x12; p->getter = 1544; p->putter = 1544; p++;
    p->type = 4190; p->flags = 0x22; p->getter = 1360; p->putter = (s32)SetGaugeModeObjectMode; p++;
    p->type = 0; p->flags = 0x20; p->putter = (s32)PlayGaugeModeObjectLoop; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)PlayScriptGaugeModeObjectTarget; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptGaugeModeObjectTarget; p->putter = 1; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1788; p->putter = 1788; p->offset = 1788; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1792; p->putter = 1792; p->offset = 1792; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)PlaceScriptModeColliderAtAnchor; p->putter = 0; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1368; p->putter = 1368; p->offset = 1368; p++;
    p->type = 4191; p->flags = 0xA2; p->getter = 1360; p->putter = (s32)SetCountdownState; p->offset = 1360; p++;
    p->type = 5; p->flags = 0x122; p->getter = 3164; p->putter = (s32)SetTempoAgentTempo; p->offset = (s32)SetTempoAgentTempo; p++;
    p->type = 5; p->flags = 0x122; p->getter = 3168; p->putter = (s32)SetTempoAgentSpanBeats; p->offset = (s32)SetTempoAgentSpanBeats; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptTempoAgentPendingTimeline; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)EndScriptHeldTimeline; p->putter = 0; p++;
    p->type = 8339; p->flags = 0x2; p->getter = 3156; p++;
    p->type = 8307; p->flags = 0x12; p->getter = 3144; p->putter = 3144; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)AddScriptC13Entry; p->putter = 2; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)RemoveScriptTempoAgentEntry; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)DecrementScriptTempoAgentGauge; p->putter = 0; p++;
    p->type = 8307; p->flags = 0x12; p->getter = 1660; p->putter = 1660; p++;
    p->type = 8335; p->flags = 0x12; p->getter = 1576; p->putter = 1576; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)AppendScriptTimelineKind0Entry; p->putter = 3; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)AppendScriptTimelineKind1Entry; p->putter = 3; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)AppendScriptTimelineKind2Entry; p->putter = 2; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)AppendScriptTimelineKind3Entry; p->putter = 2; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)AppendScriptTimelineKind4Entry; p->putter = 2; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (s32)AppendScriptTimelineKind5Entry; p->putter = 2; p++;
    p->type = 5; p->flags = 0x12; p->getter = 3088; p->putter = 3088; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SetScriptGaugeBarAgentValues; p->putter = 3; p++;
    p->type = 0; p->flags = 0x12; p->getter = 3108; p->putter = 3108; p++;
    p->type = 4199; p->flags = 0x22; p->getter = 1552; p->putter = (s32)SetHitCountColliderState; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)SendScriptHitCountColliderRequest; p->putter = 1; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1680; p->putter = 1680; p->offset = 1680; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1684; p->putter = 1684; p->offset = 1684; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)AddScriptHitCountColliderId; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)AddScriptHitCountColliderItem; p->putter = 1; p++;
    p->type = 5; p->flags = 0x12; p->getter = 1360; p->putter = 1360; p++;
    p->type = 8311; p->flags = 0x12; p->getter = 1368; p->putter = 1368; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (s32)TakeScriptCountedColliderTouch; p->putter = 2;
}
