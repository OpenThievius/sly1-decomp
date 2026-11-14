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
#include "world5_boss.h"
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
#include "world3_timeline.h"
#include "functions/arc_element.h"
#include "functions/base_object.h"
#include "functions/camera.h"
#include "functions/child_group_object.h"
#include "functions/collider.h"
#include "functions/entry_queue.h"
#include "functions/flagged_object.h"
#include "functions/game_progress.h"
#include "functions/gauge_manager.h"
#include "functions/hit_count_collider.h"
#include "functions/mode_walker.h"
#include "functions/movie_player.h"
#include "functions/object_cycler.h"
#include "functions/object_gatherer.h"
#include "functions/object_host_functions.h"
#include "functions/object_pool.h"
#include "functions/object_properties.h"
#include "functions/on_off_object.h"
#include "functions/oscillator.h"
#include "functions/pair_controller.h"
#include "functions/path_follower.h"
#include "functions/path_speed_collider.h"
#include "functions/player.h"
#include "functions/player_mode.h"
#include "functions/player_path.h"
#include "functions/point_graph.h"
#include "functions/pooled_object.h"
#include "functions/sound_system.h"
#include "functions/state_notifier.h"
#include "functions/state_walker.h"
#include "functions/switched_collider.h"
#include "functions/target_follower.h"
#include "functions/timed_object.h"
#include "functions/tint_blend_collider.h"
#include "functions/turning_collider.h"
#include "functions/warp_menu.h"
#include "functions/world2_boss.h"
#include "functions/world5_boss.h"
#include "functions/zone_collider.h"
struct Animation;
struct World3Timeline;
struct Agent;
struct SeekingAgent;
struct ColorFade;


// Types other files define, named by the parameters of their functions declared here.
struct InteractTarget;

// The kinds a property's arguments are read as (func_001C23B0's fourth argument): one word per
// argument, copied from the file's .rodata into the frame as one block.
struct Kinds2 { s32 k[2]; };
struct Kinds3 { s32 k[3]; };
struct Kinds4 { s32 k[4]; };
struct Kinds5 { s32 k[5]; };
struct Kinds6 { s32 k[6]; };


void SetStateTriggerStateFromMessage(StateTrigger* object, s32 mode);
void AddStateTriggerTableEntry(StateTrigger* object, s32 a1, s32 a2, s32 a3, s32 a4);
void ClearObjectRecordValues(PlacedObject* records);
void FadeInPlacedObject(Collider* self, f32 time);
void FadeOutPlacedObject(Collider* self, f32 time);
void* FindObjectAnimationPlayer(PlacedObject* self, s32 key);
void* FindObjectHandle(PlacedObject* self, s32 key);
void* FindTrackPlayer(PlacedObject* node);
void ClearAimHold(PlacedObject* self);
void SetAimHold(PlacedObject* self);
void SetValueAttachment(PlacedObject* self, s32 a, f32 x, f32 y);
void SetElementsScrollScale(PlacedObject* self, f32 a, f32 b);
void SetCrossfadeRatioDeep(PlacedObject* self, f32 value);
void StartSoundWithParams(PlacedObject* self, s32 value, U64P* src, f32 x, f32 y, f32 z);
void StopPlayingSound(PlacedObject* self);
void SetFollowObjects(PlacedObject* self, void* a1, void* a2);
AnimationPlayer* CreateAnimationPlayerReturned(Animation* self, BaseObject* owner, f32 fa, f32 fb, s32 flags);
void* FindOrCreateSeekedAnimationPlayer(void* self, BaseObject* key, s32 a2, s32 a3, f32 fa, f32 fb);
f32 GetAnimationMarkerTime(Animation* self, s32 key);
void StopAnimationPlayer(AnimationPlayer* self);
void ReleasePlayerAttachment(void* a0, s32 owner, s32 how);
void SeekAnimationPlayer(AnimationPlayer* self, s32 a, f32 x, f32 y);
struct ObjectGatherer;
void ApplyListedPoseSources(AnimationPlayer* a0, s32 flag);
s32 IsObjectOfKind(BaseObject* list, s32 key);
void AddSpawnRangeEntry(EffectSpawner* self, s32 a, s32 b, f32 x, f32 y, f32 z, f32 w);
void SetEffectSpawnerActiveFor(EffectSpawner* self, f32 f);
void SetEffectSpawnerActiveForever(EffectSpawner* self);
void SetEffectSpawnerInactive(EffectSpawner* self);
void SendEmptyMessage(MemberObject* a0);
void SendTwoVectorMessage(MemberObject* a0, s32 a1, s32 a2, Quad16* a3, Quad16* a4, f32 x, f32 y);
void AddRecordMemberRangeEntry(RecordMember* self, s32 a, s32 b, f32 x, f32 y, f32 z, f32 w);
void StartColorFade(ColorFade* a0);
s32 IsPointInsideObjectFaces(ScalingVolume* self, void* point);
void ForceAgentState(Agent* self, s32 mode, void* value);
void SetAgentStateClipId(u8* self, s32 index, s32 value);
void SetAgentStateClip(Agent* self, s32 a, s32 b);
void* GetAgentStateClip(Agent* self, s32 index);
void AddAgentExtraClip(Agent* self, s32 a, s32 b);
void SetAgentSecondaryClipId(Agent* p, s32 a, s32 b);
void AddAgentMeshKey(Agent* self, s32 a, s32 b);
struct PathObject;
void AddAgentClipGroup(Agent* self, s32 a1, s32 a2, s32 a3, s32 a4);
void SetAgentMainClip(Agent* self, void* value);
void AddPathFollowerEntry(PathFollower* self, void* item);
void AddPathFollowerActiveEntry(PathFollower* item, void* a, f32 x, f32 y, s32 b, s32 c);
void ResetPathFollower(PathFollower* st);
void SetCachedVoiceParamBuiltin(void* self, s32 a, s32 b);
s32 GetCachedVoiceParamBuiltin(void*,s32);
void* RefreshCachedVoiceParamBuiltin(void* unused, s32 a1, s32 a2);
s32 TestLevelEntryFlag1(void* self, s32 obj);
s32 TestLevelEntryFlag2(void* self, s32 obj);
s32 TestLevelEntryFlag4(void* self, s32 obj);
s32 TestLevelEntryFlag8(void* self, s32 obj);
s32 CheckEntryOneBitRequirement(World* a0, s32 a1);
s32 CheckEntryTwoBitRequirement(void* x, s32 v);
s32 CheckEntryThreeBitRequirement(void* x, s32 v);
void SetEntrySlotValue(void* self, s32 obj, s32 key, s32 value);
s32 GetEntrySlotValue(void* self, s32 obj, s32 key);
s32 IsLevelRecordComplete(void* x, s32 v);
s32 IsLevelDone(void* self, s32 index);
s32 RecomputeSaveCompletion(void* self);
void ScatterRandomObjects(void* unused, s32 a, s32 b, void* c);
void AcquirePadSelectFlag(World* a0);
void ReleasePadSelectFlag(World* self);
void PopActiveSequenceElement(World* world);
void ShowPauseMenuPageWith(void* unused, s32 a1, s32 a2);
void ShowCountedScreenElement(World* self);
void HideCountedScreenElement(World* self);
s32 PushSoundLevelBuiltin(void* self, s32 p);
void RemoveSoundLevelBuiltin(void* unused, void* p);
void SetWorldFlagBit(World* self, s32 bit);
void ClearWorldFlagBit(World* self, s32 bit);


// The file's .rodata: the argument signatures its functions copy, in retail's order.
extern const s32 g_createScriptObjectCopyArgKinds[2] = { 0x2000, 0x2000 };
extern const s32 g_setScriptExtraObjectPropertyBoolArgKinds[2] = { 0x14, 0 };
extern const s32 g_setScriptExtraObjectPropertyIntArgKinds[2] = { 0x14, 5 };
extern const s32 g_setScriptExtraObjectPropertyFloatArgKinds[2] = { 0x14, 1 };
extern const s32 g_setScriptExtraObjectPropertyVectorBArgKinds[2] = { 0x14, 9 };
extern const s32 g_setScriptExtraObjectPropertyPairArgKinds[2] = { 0x14, 10 };
extern const s32 g_setScriptExtraObjectPropertyWordArgKinds[2] = { 0x14, 6 };
extern const s32 g_setScriptExtraObjectPropertyVectorAArgKinds[2] = { 0x14, 2 };
extern const s32 g_setScriptValueAttachmentArgKinds[4] = { 1, 1, 0x1000, 0 };
extern const s32 g_setScriptElementsScrollScaleArgKinds[2] = { 1, 1 };
extern const s32 g_startScriptSoundWithParamsArgKinds[6] = { 14, 1, 1, 1, 10, 0 };
extern const s32 g_setScriptTransformObjectKeyedValueArgKinds[4] = { 0, 6, 6, 6 };
extern const s32 g_createScriptAnimationPlayerArgKinds[4] = { 0x2000, 1, 1, 0x1000 };
extern const s32 g_findOrCreateScriptSeekedAnimationPlayerArgKinds[6] = { 0x2000, 0x1000, 1, 1, 0x1000, 0 };
extern const s32 g_seekScriptAnimationPlayerArgKinds[4] = { 0x1000, 1, 1, 0 };
extern const Kinds2 g_releaseScriptPlayerAttachmentArgKinds = { { 6, 0x1000 } };
extern const s32 g_addScriptSpawnRangeEntryArgKinds[6] = { 6, 6, 1, 1, 1, 1 };
extern const s32 g_sendScriptTwoVectorMessageC7AArgKinds[6] = { 0x1000, 0x2000, 2, 2, 1, 1 };
extern const s32 g_createScriptStateWalkerArgKinds[4] = { 0x2000, 6, 0x1000, 0 };
extern const s32 g_scatterScriptRandomObjectsArgKinds[4] = { 5, 5, 2, 0 };
extern const s32 g_setScriptIopChannel2SettingArgKinds[2] = { 0x1000, 5 };
extern const s32 g_setScriptEntrySlotValueArgKinds[4] = { 15, 6, 5, 0 };
extern const Kinds2 g_getScriptEntrySlotValueArgKinds = { { 0xF, 6 } };
extern const Kinds2 g_showScriptPauseMenuPageWithArgKinds = { { 0x1000, 0x2000 } };
extern const s32 g_setScriptCachedVoiceParamArgKinds[2] = { 5, 5 };
extern const s32 g_refreshScriptCachedVoiceParamArgKinds[2] = { 5, 0 };
extern const s32 g_setScriptCameraControllerSettingsArgKinds[4] = { 0x2000, 1, 1, 0 };
extern const s32 g_testScriptSphereInCameraViewArgKinds[4] = { 2, 1, 1, 0 };
extern const s32 g_setScriptAgentStateClipIdArgKinds[2] = { 0x1000, 6 };
extern const s32 g_addScriptAgentClipGroupArgKinds[4] = { 6, 6, 6, 6 };
extern const s32 g_setScriptAimBlendGridVectorArgKinds[4] = { 1, 1, 1, 0 };
extern const s32 g_addScriptObjectPoolEntryArgKinds[4] = { 6, 5, 0, 0 };
extern const s32 g_setScriptObjectPoolEntryCountArgKinds[2] = { 6, 5 };
extern const s32 g_addScriptOscillatorEntryVectorAArgKinds[4] = { 1, 1, 1, 1 };
extern const s32 g_addScriptPathFollowerActiveEntryArgKinds[6] = { 0x2000, 1, 1, 0x2000, 0x2000, 0 };
extern const s32 g_startScriptC24ObjectPathArgKinds[2] = { 0x2000, 1 };
extern const s32 g_addScriptQueueEntryKind4ArgKinds[2] = { 6, 1 };
extern const s32 g_addScriptQueueEntryKind5ArgKinds[4] = { 6, 0x1000, 0x1000, 0 };
extern const s32 g_addScriptQueueEntryKind6ArgKinds[4] = { 6, 1, 0, 0 };
extern const s32 g_addScriptQueueEntryKind8ArgKinds[4] = { 6, 0x1000, 0, 0 };
extern const s32 g_addScriptQueueEntryKind9ArgKinds[2] = { 6, 0 };
extern const s32 g_addScriptC13EntryArgKinds[2] = { 0x2000, 5 };
extern const s32 g_appendScriptWorld3TimelineKind0EntryArgKinds[4] = { 5, 1, 0x1000, 0 };
extern const s32 g_appendScriptWorld3TimelineKind1EntryArgKinds[4] = { 5, 1, 6, 0 };
extern const s32 g_appendScriptWorld3TimelineKind2EntryArgKinds[2] = { 5, 1 };
extern const s32 g_setScriptWorld4BossValuesArgKinds[4] = { 0x2000, 0x2000, 0x2000, 0 };
extern const s32 g_takeScriptCountedColliderTouchArgKinds[2] = { 0x2000, 0 };

// The file's .data: the property descriptors, filled at startup by func_00109488.
PropertyDescriptor g_objectPropertyDescriptors[1179];


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
    SetScriptValueBool(&q, IsObjectOfKind((BaseObject*)obj, out));
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
    World* o1;
    BaseObject* o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&g_createScriptObjectCopyArgKinds;
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
    BaseObject* out;
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
    kinds = *(Kinds2*)&g_setScriptExtraObjectPropertyBoolArgKinds;
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
    kinds = *(Kinds2*)&g_setScriptExtraObjectPropertyIntArgKinds;
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
    kinds = *(Kinds2*)&g_setScriptExtraObjectPropertyFloatArgKinds;
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
    kinds = *(Kinds2*)&g_setScriptExtraObjectPropertyVectorBArgKinds;
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
    kinds = *(Kinds2*)&g_setScriptExtraObjectPropertyPairArgKinds;
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
    kinds = *(Kinds2*)&g_setScriptExtraObjectPropertyWordArgKinds;
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
    kinds = *(Kinds2*)&g_setScriptExtraObjectPropertyVectorAArgKinds;
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
    kinds = *(Kinds3*)&g_setScriptValueAttachmentArgKinds;
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
    kinds = *(Kinds2*)&g_setScriptElementsScrollScaleArgKinds;
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
    kinds = *(Kinds5*)&g_startScriptSoundWithParamsArgKinds;
    StoreScriptArgumentsVa(&t, 5, args, &kinds, &i0, &f0, &f1, &f2, &vec);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    StartSoundWithParams(obj, i0, (U64P*)&vec, f0, f1, f2);
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
    FadeInPlacedObject((Collider*)obj, f0);
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
    (void)FadeOutPlacedObject((Collider*)obj, f0);
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
    BaseObject* o1;
    BaseObject* o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)&g_createScriptObjectCopyArgKinds;
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
    s32 r = IsPointInsideCollider(obj, (Vec02*)&vec);
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
    kinds = *(Kinds4*)g_setScriptTransformObjectKeyedValueArgKinds;
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
    PlaceAtArrivalPoint((TransformSet*)obj);
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
    BaseObject* o0;
    f32 o1;
    f32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds4*)&g_createScriptAnimationPlayerArgKinds;
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
    BaseObject* o1;
    s32 o2;
    f32 o3;
    f32 o4;
    s32 o5;
    InitScriptValue(&q);
    kinds = *(Kinds5*)&g_findOrCreateScriptSeekedAnimationPlayerArgKinds;
    (void)StoreScriptArgumentsVa(&t, 5, args, &kinds, &o1, &o2, &o3, &o4, &o5);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValuePointerB(&q, FindOrCreateSeekedAnimationPlayer(obj, o1, o2, o5, o3, o4));
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
    kinds = *(Kinds3*)&g_seekScriptAnimationPlayerArgKinds;
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
    StopAnimationPlayer((AnimationPlayer*)obj);
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
    ApplyListedPoseSources((AnimationPlayer*)obj, out);
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
    kinds = g_releaseScriptPlayerAttachmentArgKinds;
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
    kinds = *(Kinds4*)g_setScriptTransformObjectKeyedValueArgKinds;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetTriggerZoneEntry(obj, o0, o1, o2, o3);
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
    kinds = *(Kinds4*)g_setScriptTransformObjectKeyedValueArgKinds;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetZoneColliderEntry(obj, o0, o1, o2, o3);
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
    kinds = *(Kinds4*)g_setScriptTransformObjectKeyedValueArgKinds;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddStateTriggerTableEntry(obj, o0, o1, o2, o3);
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
    kinds = *(Kinds6*)&g_addScriptSpawnRangeEntryArgKinds;
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
    kinds = *(Kinds6*)&g_addScriptSpawnRangeEntryArgKinds;
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
    kinds = *(Kinds6*)&g_sendScriptTwoVectorMessageC7AArgKinds;
    (void)StoreScriptArgumentsVa(&t, 6, args, &kinds, pi0, pi1, &vec0, &vec1, &f0, &f1);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SendTwoVectorMessage(obj, i0, i1, (Quad16*)&vec0, (Quad16*)&vec1, f0, f1);
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
    kinds = *(Kinds6*)&g_sendScriptTwoVectorMessageC7AArgKinds;
    (void)StoreScriptArgumentsVa(&t, 6, args, &kinds, &i0, &i1, &vec0, &vec1, &f0, &f1);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SendTwoVectorMessage(obj, i0, i1, (Quad16*)&vec0, (Quad16*)&vec1, f0, f1);
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
    kinds = *(Kinds3*)&g_createScriptStateWalkerArgKinds;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    void* v = CreateStateWalker(obj, (void*)o1, o2, o3);
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
    DestroyStateWalker((StateWalker*)obj);
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
    kinds = *(Kinds3*)&g_scatterScriptRandomObjectsArgKinds;
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
    kinds = *(Kinds2*)&g_setScriptIopChannel2SettingArgKinds;
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
    kinds = *(Kinds2*)&g_setScriptIopChannel2SettingArgKinds;
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
    s32 o1;
    s32 o2;
    s32 o3;
    InitScriptValue(&q);
    kinds = *(Kinds3*)&g_setScriptEntrySlotValueArgKinds;
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
    kinds = *(Kinds2*)&g_getScriptEntrySlotValueArgKinds;
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
    kinds = *(Kinds2*)&g_showScriptPauseMenuPageWithArgKinds;
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
    void* out; // the handle PushScriptSoundLevel gave the script as an integer
    InitScriptValue(&q);
    kinds = 0x5;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    RemoveSoundLevelBuiltin(obj, out);
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
    kinds = *(Kinds2*)g_setScriptCachedVoiceParamArgKinds;
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
    kinds = *(Kinds2*)g_refreshScriptCachedVoiceParamArgKinds;
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
    kinds = *(Kinds3*)g_setScriptCameraControllerSettingsArgKinds;
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
    kinds = *(Kinds3*)g_testScriptSphereInCameraViewArgKinds;
    StoreScriptArgumentsVa(&t, 3, args, &kinds, &vec, &fx, &fy);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetScriptValueBool(&q, IsSphereInCameraView(obj, (Vec02*)&vec, fx, fy));
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
    kinds = *(Kinds2*)g_setScriptAgentStateClipIdArgKinds;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &out1, &out2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetAgentStateClipId((u8*)obj, out1, out2);
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
    kinds = *(Kinds2*)g_setScriptAgentStateClipIdArgKinds;
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
    kinds = *(Kinds4*)g_addScriptAgentClipGroupArgKinds;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddAgentClipGroup(obj, o0, o1, o2, o3);
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
    kinds = *(Kinds2*)&g_releaseScriptPlayerAttachmentArgKinds;
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
    kinds = *(Kinds2*)g_setScriptAgentStateClipIdArgKinds;
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
    void* o2;
    InitScriptValue(&q);
    kinds = g_showScriptPauseMenuPageWithArgKinds;
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
    kinds = *(Kinds2*)g_setScriptAgentStateClipIdArgKinds;
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
    void* out;
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
    kinds = *(Kinds2*)g_setScriptAgentStateClipIdArgKinds;
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
    kinds = *(Kinds3*)g_testScriptSphereInCameraViewArgKinds;
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
    PathObject* out;
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
    u8* out;
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
    InteractTarget* out;
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
    InteractTarget* out;
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
    kinds = *(Kinds3*)g_setScriptAimBlendGridVectorArgKinds;
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
    kinds = *(Kinds3*)g_setScriptAimBlendGridVectorArgKinds;
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
    BaseObject* out;
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
    kinds = *(Kinds4*)g_setScriptTransformObjectKeyedValueArgKinds;
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
    kinds = *(Kinds4*)g_addScriptObjectPoolEntryArgKinds;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &o0, &o1, &o2, &o3);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddObjectPoolEntry(obj, o0, o1, o2, o3);
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
    kinds = *(Kinds2*)g_setScriptObjectPoolEntryCountArgKinds;
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
    ResetPlacementRecord((u8*)obj);
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
    ClearObjectPoolHeadingRecord((u8*)obj);
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
    u32 o2;
    InitScriptValue(&q);
    kinds = g_getScriptEntrySlotValueArgKinds;
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
    kinds = *(Kinds4*)g_addScriptOscillatorEntryVectorAArgKinds;
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
    kinds = *(Kinds4*)g_addScriptOscillatorEntryVectorAArgKinds;
    StoreScriptArgumentsVa(&t, 4, args, &kinds, &x, &y, &z, &w);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddOscillatorEntryVectorB(obj, x, y, z, w);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AdvanceScriptWorld2BossPhase(ScriptValue* ret, World2Boss* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AdvanceWorld2BossPhase(obj);
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
    kinds = *(Kinds2*)g_setScriptAgentStateClipIdArgKinds;
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
    BaseObject* out;
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
    void* o1;
    f32 o2;
    f32 o3;
    s32 o4;
    s32 o5;
    InitScriptValue(&q);
    kinds = *(Kinds5*)g_addScriptPathFollowerActiveEntryArgKinds;
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
    SetScriptValueBool(&q, TestPointAgainstObjectShape((ObjectGatherer*)obj, &vec));
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
    Agent* out;
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
    PathCurveObject* a;
    f32 b;
    InitScriptValue(&q);
    kinds = *(Kinds2*)g_startScriptC24ObjectPathArgKinds;
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
    Player* out;
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
    kinds = *(Kinds2*)g_addScriptQueueEntryKind4ArgKinds;
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
    kinds = *(Kinds4*)g_addScriptQueueEntryKind5ArgKinds;
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
    kinds = *(Kinds3*)g_addScriptQueueEntryKind6ArgKinds;
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
    kinds = *(Kinds3*)g_addScriptQueueEntryKind6ArgKinds;
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
    kinds = *(Kinds3*)g_addScriptQueueEntryKind8ArgKinds;
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
    kinds = *(Kinds2*)g_addScriptQueueEntryKind9ArgKinds;
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
    StartColorFade((ColorFade*)obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* PlayScriptWorld5BossTarget(ScriptValue* ret, World5Boss* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    PlayWorld5BossTarget(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptWorld5BossTarget(ScriptValue* ret, World5Boss* obj, s32 unused, ScriptValue* args)
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
    (void)SetWorld5BossTarget(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* PlaceScriptWorld5ModeColliderAtAnchor(ScriptValue* ret, World5ModeCollider* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    PlaceWorld5ModeColliderAtAnchor(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptWorld3BossPendingTimeline(ScriptValue* ret, World3Boss* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    World3Timeline* out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)SetWorld3BossPendingTimeline(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* EndScriptHeldWorld3Timeline(ScriptValue* ret, World3Boss* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    EndHeldWorld3Timeline(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AddScriptC13Entry(ScriptValue* ret, World3Boss* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    AnimationPlayer* o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds2*)g_addScriptC13EntryArgKinds;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AddWorld3BossEntry(obj, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* RemoveScriptWorld3BossEntry(ScriptValue* ret, World3Boss* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    s32 kinds;
    AnimationPlayer* out;
    InitScriptValue(&q);
    kinds = 0x2000;
    StoreScriptArgumentsVa(&t, 1, args, &kinds, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    (void)RemoveWorld3BossEntry(obj, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* DecrementScriptWorld3BossGauge(ScriptValue* ret, World3Boss* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    ScriptValue t;
    InitScriptValue(&q);
    StoreScriptArgumentsVa(&t, 0, args, 0);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    DecrementWorld3BossGauge(obj);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AppendScriptWorld3TimelineKind0Entry(ScriptValue* ret, World3Timeline* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    s32 o0;
    f32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds3*)g_appendScriptWorld3TimelineKind0EntryArgKinds;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o0, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AppendWorld3TimelineKind0Entry(obj, o0, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AppendScriptWorld3TimelineKind1Entry(ScriptValue* ret, World3Timeline* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    s32 o0;
    f32 o1;
    s32 o2;
    InitScriptValue(&q);
    kinds = *(Kinds3*)g_appendScriptWorld3TimelineKind1EntryArgKinds;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o0, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AppendWorld3TimelineKind1Entry(obj, o0, o1, o2);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AppendScriptWorld3TimelineKind2Entry(ScriptValue* ret, World3Timeline* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 n;
    f32 out;
    InitScriptValue(&q);
    kinds = *(Kinds2*)g_appendScriptWorld3TimelineKind2EntryArgKinds;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &n, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AppendWorld3TimelineKind2Entry(obj, n, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AppendScriptWorld3TimelineKind3Entry(ScriptValue* ret, World3Timeline* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 n;
    f32 out;
    InitScriptValue(&q);
    kinds = *(Kinds2*)g_appendScriptWorld3TimelineKind2EntryArgKinds;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &n, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AppendWorld3TimelineKind3Entry(obj, n, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AppendScriptWorld3TimelineKind4Entry(ScriptValue* ret, World3Timeline* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 n;
    f32 out;
    InitScriptValue(&q);
    kinds = *(Kinds2*)g_appendScriptWorld3TimelineKind2EntryArgKinds;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &n, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AppendWorld3TimelineKind4Entry(obj, n, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* AppendScriptWorld3TimelineKind5Entry(ScriptValue* ret, World3Timeline* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds2 kinds;
    ScriptValue t;
    s32 n;
    f32 out;
    InitScriptValue(&q);
    kinds = *(Kinds2*)g_appendScriptWorld3TimelineKind2EntryArgKinds;
    (void)StoreScriptArgumentsVa(&t, 2, args, &kinds, &n, &out);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    AppendWorld3TimelineKind5Entry(obj, n, out);
    SetScriptValueTag(&q, 0x22);
    CopyConstructScriptValue(ret, &q);
    DestroyScriptValue(&q, 2);
    return ret;
}

ScriptValue* SetScriptWorld4BossValues(ScriptValue* ret, World4Boss* obj, s32 unused, ScriptValue* args)
{
    ScriptValue q;
    Kinds3 kinds;
    ScriptValue t;
    Animation* o0;
    Animation* o1;
    Animation* o2;
    InitScriptValue(&q);
    kinds = *(Kinds3*)g_setScriptWorld4BossValuesArgKinds;
    (void)StoreScriptArgumentsVa(&t, 3, args, &kinds, &o0, &o1, &o2);
    AssignScriptValue(&q, &t);
    DestroyScriptValue(&t, 2);
    SetWorld4BossValues(obj, o0, o1, o2);
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
    BaseObject* out;
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
    BaseObject* out;
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
    PlacedObject* out;
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
    void* o0;
    s32 o1;
    InitScriptValue(&q);
    (void)StoreScriptArgumentsVa(&t, 2, args, (kinds = *(Kinds2*)g_takeScriptCountedColliderTouchArgKinds, &kinds), &o0, &o1);
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
struct World5Countdown;
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
void StorePlacedObjectLocalVelocity();
void StorePlacedObjectLocalSpin();
AnimationStart* EnsureTimerRecord(PlacedObject* self);
void GetRotationDegrees(PlacedObject* self, f32* out);
void SetRotationDegrees(PlacedObject* self, f32* src);
void GetPlacedObjectLocalVelocity();
void SetPlacedObjectLocalVelocity(PlacedObject* self, const Vec02* local);
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
void SetRangeRecordFar(PlacedObject* self, f32 x);
void GetRangeRecordInner(void* self, f32* out);
void SetRangeRecordInner(PlacedObject* self, f32 x);
void GetRangeRecordOuter(PlacedObject* self, f32* out);
void SetRangeRecordOuter(PlacedObject* self, f32 x);
void GetRangeRecordAngle(void* self, f32* out);
void SetRangeRecordInnerAndOuter(PlacedObject* self, f32 x);
void GetRangeRecordVector(void* self, Vec02* out);
void SetRangeRecordVector(void* self, void* src);
void SetRangeRecordCode(void* self, s32 value);
void SetGroupActivityModeEnabled(void* self, s32 a1);
void GetGroupActivityMode(PlacedObject* self, u32* out);
void SetGroupActivityMode(PlacedObject* self, u32 value);
void SetPositionSourceEnabled(void* self, s32 value);
extern void SetPositionSourceMode(PlacedObject* self, s32 value);
void SetScaledPositionSpring(PlacedObject* self, f32 scale);
void SetPositionSpring(PlacedObject* self, Quad16* value);
void SetScaledVelocitySpring(PlacedObject* self, f32 scale);
void SetVelocitySpring(PlacedObject* self, Quad16* src);
void SetOrientationSourceEnabled(void* self, s32 a1);
void SetOrientationSourceMode(PlacedObject* self, s32 value);
void SetBaseAttachmentSortKey(PlacedObject* self, s32 value);
void SetScaledRotationSpring(PlacedObject* self, f32 scale);
void SetRotationSpring(PlacedObject* self, Quad16* src);
void SetScaledSpinSpring(PlacedObject* self, f32 scale);
void SetSpinSpring(PlacedObject* self, Quad16* src);
void SetScaledPositionRamp(PlacedObject* self, f32 scale);
void SetPositionRamp(PlacedObject* self, RampProfile* src);
void SetScaledRotationRamp(void* self, f32 s);
void SetRotationRamp(PlacedObject* self, RampProfile* src);
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
void SetAimTarget(PlacedObject* self, void* b);
s32 TestChildrenAccepted(PlacedObject* self, ScriptListBuilder* context);
void SetClass75ObjectCount(PlacedObject* self, s32 value);
void SetClass75ObjectScale(void* self, f32 value);
void SetClass75ObjectField90(void* self, s32 value);
void SetObjectRecordValue(PlacedObject* state, u32 value);
void SetObjectTreeRecordValue(PlacedObject* object, u32 value);
void GetColorPreset(PlacedObject* self, s32* out);
void SetColorPreset(PlacedObject* self, s32 a1);
void GetColorRecordFirstColor(PlacedObject* self, Quad16* out);
void SetColorRecordFirstColor(PlacedObject* self, Quad16* input);
void GetColorRecordSecondColor(PlacedObject* self, Quad16* out);
void SetColorRecordSecondColor(PlacedObject* self, Quad16* input);
void GetColorRecordFactor(PlacedObject* self, f32* out);
void SetColorRecordFactor(PlacedObject* self, f32 value);
void GetSoundRecordId(PlacedObject* self, s32* out);
void RestartSoundWithId(PlacedObject* self, s32 value);
void SetSoundRecordId(PlacedObject* self, s32 value);
void GetSoundOuterRange(PlacedObject* self, f32* out);
void SetSoundOuterRange(PlacedObject* self, f32 value);
void GetSoundInnerRange(PlacedObject* self, f32* out);
void SetSoundInnerRange(PlacedObject* self, f32 value);
void GetSoundRecordScale(PlacedObject* self, f32* out);
void SetPlayingSoundVolume(PlacedObject* self, f32 volume);
void SetSoundRecordScale(PlacedObject* self, f32 f);
void GetSoundStartPitch(PlacedObject* self, f32* out);
void SetPlayingSoundPitch(PlacedObject* self, f32 pitch);
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
void SelectValueEntryByKey(PlacedObject* self, s32 key);
void SetPlacedObjectFrameStepClock(PlacedObject* self, s32 flag);
void SetObjectCameraTracked(PlacedObject* self, s32 flag);
void GetPlacedObjectSpecialFlag(PlacedObject* ctx, s32* out);
void SetPlacedObjectSpecialFlag(PlacedObject* ctx, s32 on);
void SetAnimationPlayerSpeed(AnimationPlayer* t, f32 x);
void SetAnimationPlayerSpeedScale(AnimationPlayer* self, f32 x);
void SetAttachmentSortKeys(AnimationPlayer* owner, s32 value);
void SetAnimationPlayerPadSelect(AnimationPlayer* self, s32 v);
struct TimedStateObject;
void AddStateTriggerCountedId(StateTrigger* self, s32 value);
void AddStateTriggerItemId(StateTrigger* self, s32 value);
void AddStateTriggerAgentId(StateTrigger* self, s32 value);
s32 TestStateTriggerItemsAccepted(StateTrigger* self, void* arg);
void AddIdFilterObjectId(IdFilterObject* a0, s32 a1);
void AddIdFilterClassId(IdFilterObject* obj, s32 value);
void SetEffectSpawnerLimit(EffectSpawner* self, s32 a1);
void SetEffectSpawnerContinuous(EffectSpawner* a0, s32 a1);
EffectSpawner* MarkEffectSpawnerChanged(EffectSpawner* self, s32 value);
void GetEffectSpawnerInactive(EffectSpawner* self, s32* out);
void SetEffectSpawnerDisabled(EffectSpawner* self, s32 a1);
void GetEffectSpawnerActive(void* self,s32* out);
void* GetOwnSpawnRecord(EffectSpawner* self, s32 mode);
void SetEffectSpawnerKind(void* a0, s32 a1);
void SetOwnedSpawnRecordKind(void* a0, s32 a1);
s32 GetOrCreateSoundParams(void* self);
void SetConeVolumeVector340(ConeVolume* self, Quad16* src);
void SetWorldLightingParamA(World* self, f32 v);
void SetWorldLightingParamB(World* self, f32 v);
void SetWorldSoundLevel(void* self, f32 x);
void SetWorldValueAndTarget(World* self, f32 v);
void SetWorldValueTarget(World* self, f32 value);
void GetGameStateDeltaTime(void* unused, f32* out);
void SetScatterLevelBuiltin(f32 level);
void GetCurrentScatterLevel(void* unused, f32* out);
void SetCurrentScatterLevel(void* unused, f32 level);
void GetHasStreamVoice(void* self, s32* out);
void GetSaveSpareCount(void* self, s32* out);
void GetReserveUnitCount(void* unused, s32* out);
void SetAgentPathObjectId(Agent* self, s32 index);
void SetAgentAngleLimitDegrees(Agent* self, f32 value);
void StoreAgentTarget(Agent* self, s32* out);
void SetAgentSecondaryTarget(Agent* self, s32 value);
void SetAgentMemberGroupId(Agent* self, s32 v);
void SetAgentTargetSetId(Agent* self, s32 v);
void IsAgentNearPathEnd(Agent* self, s32* out);
void AddOwnedWantedId(ItemKeeper* self, s32 value);
void AddListedWantedId(ItemKeeper* self, s32 value);
void SetPathFollowerPath(PathFollower* self, PathCurveObject* arg);
void SetPathFollowerSecondPath(u8* self, PathCurveObject* obj);
void SetPathFollowerMode(PathFollower* self, s32 mode);

void FillObjectPropertyTable()
{
    PropertyDescriptor* p = g_objectPropertyDescriptors;

    p->type = 7; p->flags = 0x4; p->getter = (sptr)GetObjectClassId; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)TestScriptObjectOfKind; p->putter = 1; p++;
    p->type = 18; p->flags = 0x401; p->getter = (sptr)AddScriptObjectKeyToOwner; p->f10 = (sptr)RemoveScriptObjectFromParentList; p->putter = 0; p++;
    p->type = 10; p->flags = 0x100; p->offset = (sptr)AddObjectKeyIfLevelInRange; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)AddScriptObjectToParentList; p->putter = 0; p++;
    p->type = 8193; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)CreateScriptObjectCopy; p->putter = 2; p++;
    p->type = 8300; p->flags = 0x2; p->getter = 20; p++;
    p->type = 0; p->flags = 0x4; p->getter = (sptr)GetObjectAttached; p++;
    p->type = 8194; p->flags = 0x2; p->getter = 24; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ReparentScriptObject; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)TestScriptObjectDescendantOf; p->putter = 1; p++;
    p->type = 6; p->flags = 0x2; p->getter = 8; p++;
    p->type = 6; p->flags = 0x4; p->getter = (sptr)GetObjectAliasId; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)TestScriptObjectIdMatch; p->putter = 1; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)SetScriptExtraObjectPropertyBool; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)SetScriptExtraObjectPropertyInt; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)SetScriptExtraObjectPropertyFloat; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)SetScriptExtraObjectPropertyVectorB; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)SetScriptExtraObjectPropertyPair; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)SetScriptExtraObjectPropertyWord; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)SetScriptExtraObjectPropertyVectorA; p->f10 = 0; p->putter = 2; p++;
    p->type = 2; p->flags = 0x100; p->offset = (sptr)StorePlacedObjectLocalVelocity; p++;
    p->type = 2; p->flags = 0x100; p->offset = (sptr)StorePlacedObjectLocalSpin; p++;
    p->type = 6; p->flags = 0x1080; p->offset = 4; p->target = (PropertyTarget)EnsureTimerRecord; p++;
    p->type = 1; p->flags = 0x1080; p->offset = 12; p->target = (PropertyTarget)EnsureTimerRecord; p++;
    p->type = 1; p->flags = 0x1080; p->offset = 16; p->target = (PropertyTarget)EnsureTimerRecord; p++;
    p->type = 4172; p->flags = 0x1080; p->offset = 8; p->target = (PropertyTarget)EnsureTimerRecord; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ClearScriptObjectRecordValues; p->putter = 0; p++;
    p->type = 0; p->flags = 0x4; p->getter = (sptr)GetPlacedObjectFrozen; p++;
    p->type = 2; p->flags = 0x42; p->getter = 256; p->putter = 132; p++;
    p->type = 2; p->flags = 0x12; p->getter = 400; p->putter = 400; p++;
    p->type = 2; p->flags = 0x2; p->getter = 320; p++;
    p->type = 4; p->flags = 0x42; p->getter = 208; p->putter = 136; p++;
    p->type = 4; p->flags = 0x12; p->getter = 416; p->putter = 416; p++;
    p->type = 4; p->flags = 0x2; p->getter = 272; p++;
    p->type = 2; p->flags = 0x124; p->getter = (sptr)GetRotationDegrees; p->putter = (sptr)SetRotationDegrees; p->offset = (sptr)SetRotationDegrees; p++;
    p->type = 2; p->flags = 0x24; p->getter = (sptr)GetPlacedObjectLocalVelocity; p->putter = (sptr)SetPlacedObjectLocalVelocity; p++;
    p->type = 2; p->flags = 0x42; p->getter = 352; p->putter = 148; p++;
    p->type = 2; p->flags = 0x2; p->getter = 368; p++;
    p->type = 2; p->flags = 0x2; p->getter = 384; p++;
    p->type = 8194; p->flags = 0x2; p->getter = 80; p++;
    p->type = 1; p->flags = 0x124; p->getter = (sptr)GetPlacedObjectScaleXY; p->putter = (sptr)SetPlacedObjectScaleXY; p->offset = (sptr)SetPlacedObjectScaleXY; p++;
    p->type = 1; p->flags = 0x124; p->getter = (sptr)GetPlacedObjectScaleZ; p->putter = (sptr)SetPlacedObjectScaleZ; p->offset = (sptr)SetPlacedObjectScaleZ; p++;
    p->type = 0; p->flags = 0x124; p->getter = (sptr)GetRangeRecordPresent; p->putter = (sptr)SetRangeRecordPresent; p->offset = (sptr)SetRangeRecordPresent; p++;
    p->type = 6; p->flags = 0x124; p->getter = (sptr)GetRangeRecordKeyValue; p->putter = (sptr)SetRangeRecordKey; p->offset = (sptr)SetRangeRecordKey; p++;
    p->type = 1; p->flags = 0x124; p->getter = (sptr)GetRangeRecordNear; p->putter = (sptr)SetRangeRecordNear; p->offset = (sptr)SetRangeRecordNear; p++;
    p->type = 1; p->flags = 0x124; p->getter = (sptr)GetRangeRecordFar; p->putter = (sptr)SetRangeRecordFar; p->offset = (sptr)SetRangeRecordFar; p++;
    p->type = 1; p->flags = 0x124; p->getter = (sptr)GetRangeRecordInner; p->putter = (sptr)SetRangeRecordInner; p->offset = (sptr)SetRangeRecordInner; p++;
    p->type = 1; p->flags = 0x124; p->getter = (sptr)GetRangeRecordOuter; p->putter = (sptr)SetRangeRecordOuter; p->offset = (sptr)SetRangeRecordOuter; p++;
    p->type = 1; p->flags = 0x124; p->getter = (sptr)GetRangeRecordAngle; p->putter = (sptr)SetRangeRecordInnerAndOuter; p->offset = (sptr)SetRangeRecordInnerAndOuter; p++;
    p->type = 2; p->flags = 0x124; p->getter = (sptr)GetRangeRecordVector; p->putter = (sptr)SetRangeRecordVector; p->offset = (sptr)SetRangeRecordVector; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)SetRangeRecordCode; p++;
    p->type = 0; p->flags = 0x120; p->putter = (sptr)SetGroupActivityModeEnabled; p->offset = (sptr)SetGroupActivityModeEnabled; p++;
    p->type = 4196; p->flags = 0x124; p->getter = (sptr)GetGroupActivityMode; p->putter = (sptr)SetGroupActivityMode; p->offset = (sptr)SetGroupActivityMode; p++;
    p->type = 0; p->flags = 0x100; p->offset = (sptr)SetPositionSourceEnabled; p++;
    p->type = 4110; p->flags = 0x100; p->offset = (sptr)SetPositionSourceMode; p++;
    p->type = 1; p->flags = 0x120; p->putter = (sptr)SetScaledPositionSpring; p->offset = (sptr)SetScaledPositionSpring; p++;
    p->type = 9; p->flags = 0x120; p->putter = (sptr)SetPositionSpring; p->offset = (sptr)SetPositionSpring; p++;
    p->type = 1; p->flags = 0x120; p->putter = (sptr)SetScaledVelocitySpring; p->offset = (sptr)SetScaledVelocitySpring; p++;
    p->type = 9; p->flags = 0x120; p->putter = (sptr)SetVelocitySpring; p->offset = (sptr)SetVelocitySpring; p++;
    p->type = 0; p->flags = 0x100; p->offset = (sptr)SetOrientationSourceEnabled; p++;
    p->type = 4110; p->flags = 0x100; p->offset = (sptr)SetOrientationSourceMode; p++;
    p->type = 5; p->flags = 0x120; p->putter = (sptr)SetBaseAttachmentSortKey; p->offset = (sptr)SetBaseAttachmentSortKey; p++;
    p->type = 1; p->flags = 0x120; p->putter = (sptr)SetScaledRotationSpring; p->offset = (sptr)SetScaledRotationSpring; p++;
    p->type = 9; p->flags = 0x120; p->putter = (sptr)SetRotationSpring; p->offset = (sptr)SetRotationSpring; p++;
    p->type = 1; p->flags = 0x120; p->putter = (sptr)SetScaledSpinSpring; p->offset = (sptr)SetScaledSpinSpring; p++;
    p->type = 9; p->flags = 0x120; p->putter = (sptr)SetSpinSpring; p->offset = (sptr)SetSpinSpring; p++;
    p->type = 1; p->flags = 0x120; p->putter = (sptr)SetScaledPositionRamp; p->offset = (sptr)SetScaledPositionRamp; p++;
    p->type = 12; p->flags = 0x120; p->putter = (sptr)SetPositionRamp; p->offset = (sptr)SetPositionRamp; p++;
    p->type = 1; p->flags = 0x120; p->putter = (sptr)SetScaledRotationRamp; p->offset = (sptr)SetScaledRotationRamp; p++;
    p->type = 12; p->flags = 0x120; p->putter = (sptr)SetRotationRamp; p->offset = (sptr)SetRotationRamp; p++;
    p->type = 1; p->flags = 0x120; p->putter = (sptr)SetPositionRampAccelScale; p->offset = (sptr)SetPositionRampAccelScale; p++;
    p->type = 1; p->flags = 0x120; p->putter = (sptr)SetRotationRampAccelScale; p->offset = (sptr)SetRotationRampAccelScale; p++;
    p->type = 4110; p->flags = 0x100; p->offset = (sptr)SetDefaultPositionMode; p++;
    p->type = 4110; p->flags = 0x100; p->offset = (sptr)SetDefaultOrientationMode; p++;
    p->type = 3; p->flags = 0x0; p++;
    p->type = 4110; p->flags = 0x100; p->offset = (sptr)SetAimOrientationMode; p++;
    p->type = 1; p->flags = 0x124; p->getter = (sptr)GetAimRange; p->putter = (sptr)SetAimRange; p->offset = (sptr)SetAimRange; p++;
    p->type = 9; p->flags = 0x124; p->getter = (sptr)GetAimYawCurve; p->putter = (sptr)SetAimYawCurve; p->offset = (sptr)SetAimYawCurve; p++;
    p->type = 10; p->flags = 0x124; p->getter = (sptr)GetAimYawLimits; p->putter = (sptr)SetAimYawLimits; p->offset = (sptr)SetAimYawLimits; p++;
    p->type = 9; p->flags = 0x124; p->getter = (sptr)GetAimPitchCurve; p->putter = (sptr)SetAimPitchCurve; p->offset = (sptr)SetAimPitchCurve; p++;
    p->type = 10; p->flags = 0x124; p->getter = (sptr)GetAimPitchLimits; p->putter = (sptr)SetAimPitchLimits; p->offset = (sptr)SetAimPitchLimits; p++;
    p->type = 5; p->flags = 0x124; p->getter = (sptr)GetAimNearKey; p->putter = (sptr)SetAimNearKey; p->offset = (sptr)SetAimNearKey; p++;
    p->type = 5; p->flags = 0x124; p->getter = (sptr)GetAimFarKey; p->putter = (sptr)SetAimFarKey; p->offset = (sptr)SetAimFarKey; p++;
    p->type = 6; p->flags = 0x104; p->getter = (sptr)GetAimTargetId; p->offset = (sptr)SetAimTargetId; p++;
    p->type = 8194; p->flags = 0x24; p->getter = (sptr)GetAimTarget; p->putter = (sptr)SetAimTarget; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ClearScriptAimHold; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptAimHold; p->putter = 0; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)SetScriptValueAttachment; p->putter = 3; p++;
    p->type = -2147475455; p->flags = 0x4; p->getter = (sptr)TestChildrenAccepted; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptElementsScrollScale; p->putter = 2; p++;
    p->type = 4127; p->flags = 0x120; p->putter = (sptr)SetClass75ObjectCount; p->offset = (sptr)SetClass75ObjectCount; p++;
    p->type = 1; p->flags = 0x120; p->putter = (sptr)SetClass75ObjectScale; p->offset = (sptr)SetClass75ObjectScale; p++;
    p->type = 0; p->flags = 0x120; p->putter = (sptr)SetClass75ObjectField90; p->offset = (sptr)SetClass75ObjectField90; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptCrossfadeRatioDeep; p->putter = 1; p++;
    p->type = 5; p->flags = 0x120; p->putter = (sptr)SetObjectRecordValue; p->offset = (sptr)SetObjectRecordValue; p++;
    p->type = 5; p->flags = 0x20; p->putter = (sptr)SetObjectTreeRecordValue; p++;
    p->type = 4160; p->flags = 0x124; p->getter = (sptr)GetColorPreset; p->putter = (sptr)SetColorPreset; p->offset = (sptr)SetColorPreset; p++;
    p->type = 2; p->flags = 0x124; p->getter = (sptr)GetColorRecordFirstColor; p->putter = (sptr)SetColorRecordFirstColor; p->offset = (sptr)SetColorRecordFirstColor; p++;
    p->type = 2; p->flags = 0x124; p->getter = (sptr)GetColorRecordSecondColor; p->putter = (sptr)SetColorRecordSecondColor; p->offset = (sptr)SetColorRecordSecondColor; p++;
    p->type = 1; p->flags = 0x124; p->getter = (sptr)GetColorRecordFactor; p->putter = (sptr)SetColorRecordFactor; p->offset = (sptr)SetColorRecordFactor; p++;
    p->type = 14; p->flags = 0x124; p->getter = (sptr)GetSoundRecordId; p->putter = (sptr)RestartSoundWithId; p->offset = (sptr)SetSoundRecordId; p++;
    p->type = 1; p->flags = 0x104; p->getter = (sptr)GetSoundOuterRange; p->offset = (sptr)SetSoundOuterRange; p++;
    p->type = 1; p->flags = 0x104; p->getter = (sptr)GetSoundInnerRange; p->offset = (sptr)SetSoundInnerRange; p++;
    p->type = 1; p->flags = 0x124; p->getter = (sptr)GetSoundRecordScale; p->putter = (sptr)SetPlayingSoundVolume; p->offset = (sptr)SetSoundRecordScale; p++;
    p->type = 1; p->flags = 0x124; p->getter = (sptr)GetSoundStartPitch; p->putter = (sptr)SetPlayingSoundPitch; p->offset = (sptr)SetSoundStartPitch; p++;
    p->type = 10; p->flags = 0x104; p->getter = (sptr)GetSoundRecordPair; p->offset = (sptr)SetSoundRecordPair; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)StartScriptSoundWithParams; p->putter = 5; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)StopScriptPlayingSound; p->putter = 0; p++;
    p->type = 1; p->flags = 0x104; p->getter = (sptr)GetSoundStartParam; p->offset = (sptr)SetSoundStartParam; p++;
    p->type = 4163; p->flags = 0x124; p->getter = (sptr)GetTintRgb; p->putter = (sptr)SetTintRgb; p->offset = (sptr)SetTintRgb; p++;
    p->type = 4163; p->flags = 0x124; p->getter = (sptr)GetTintByte0; p->putter = (sptr)SetTintByte0; p->offset = (sptr)SetTintByte0; p++;
    p->type = 4163; p->flags = 0x124; p->getter = (sptr)GetTintByte1; p->putter = (sptr)SetTintByte1; p->offset = (sptr)SetTintByte1; p++;
    p->type = 4163; p->flags = 0x124; p->getter = (sptr)GetTintByte2; p->putter = (sptr)SetTintByte2; p->offset = (sptr)SetTintByte2; p++;
    p->type = 4163; p->flags = 0x124; p->getter = (sptr)GetTintByte3; p->putter = (sptr)SetTintByte3; p->offset = (sptr)SetTintByte3; p++;
    p->type = 4163; p->flags = 0x124; p->getter = (sptr)GetTintByte4; p->putter = (sptr)SetTintByte4; p->offset = (sptr)SetTintByte4; p++;
    p->type = 6; p->flags = 0x20; p->putter = (sptr)SelectValueEntryByKey; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)FadeInScriptPlacedObject; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)FadeOutScriptPlacedObject; p->putter = 1; p++;
    p->type = 0; p->flags = 0x102; p->getter = 660; p->offset = (sptr)SetPlacedObjectFrameStepClock; p++;
    p->type = 8339; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)FindScriptObjectHandle; p->putter = 1; p++;
    p->type = 8338; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)FindScriptObjectAnimationPlayer; p->putter = 1; p++;
    p->type = 8338; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)FindScriptTrackPlayer; p->putter = 0; p++;
    p->type = 0; p->flags = 0x120; p->putter = (sptr)SetObjectCameraTracked; p->offset = (sptr)SetObjectCameraTracked; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)CopyScriptPlacedObjectFrame; p->putter = 1; p++;
    p->type = 0; p->flags = 0x124; p->getter = (sptr)GetPlacedObjectSpecialFlag; p->putter = (sptr)SetPlacedObjectSpecialFlag; p->offset = (sptr)SetPlacedObjectSpecialFlag; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptFollowObjects; p->putter = 2; p++;
    p->type = 1; p->flags = 0x22; p->getter = 872; p->putter = (sptr)SetColliderMass; p++;
    p->type = 4111; p->flags = 0x120; p->putter = (sptr)SetColliderSurfaceKind; p->offset = (sptr)SetColliderSurfaceKind; p++;
    p->type = 2; p->flags = 0x92; p->getter = 848; p->putter = 848; p->offset = 848; p++;
    p->type = 0; p->flags = 0x100; p->offset = (sptr)ResetColliderAnchors; p++;
    p->type = 4096; p->flags = 0x120; p->putter = (sptr)SetColliderTurnAnchorPreset; p->offset = (sptr)SetColliderTurnAnchorPreset; p++;
    p->type = 4096; p->flags = 0x120; p->putter = (sptr)SetColliderMoveAnchorPreset; p->offset = (sptr)SetColliderMoveAnchorPreset; p++;
    p->type = 1; p->flags = 0x100; p->offset = (sptr)SetColliderOverrideRadius; p++;
    p->type = 1; p->flags = 0x892; p->getter = 864; p->putter = 864; p->offset = 864; p->floatValue = 0.5f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 868; p->putter = 868; p->offset = 868; p->floatValue = 1.0f; p++;
    p->type = 0; p->flags = 0x120; p->putter = (sptr)SetColliderFlagBit47; p->offset = (sptr)SetColliderFlagBit47; p++;
    p->type = 0; p->flags = 0x100; p->offset = (sptr)SetColliderFlagBit48; p++;
    p->type = 0; p->flags = 0x120; p->putter = (sptr)SetColliderGravityDisabled; p->offset = (sptr)SetColliderGravityDisabled; p++;
    p->type = 0; p->flags = 0x120; p->putter = (sptr)SetColliderTreeContactsDropped; p->offset = (sptr)SetColliderTreeContactsDropped; p++;
    p->type = 0; p->flags = 0x120; p->putter = (sptr)SetColliderContactsDropped; p->offset = (sptr)SetColliderContactsDropped; p++;
    p->type = 0; p->flags = 0x120; p->putter = (sptr)SetColliderKindContactsDropped; p->offset = (sptr)SetColliderKindContactsDropped; p++;
    p->type = -2147475453; p->flags = 0x4; p->getter = (sptr)CollectContactingPartsToScriptList; p++;
    p->type = 4129; p->flags = 0x92; p->getter = 1248; p->putter = 1248; p->offset = 1248; p++;
    p->type = 1; p->flags = 0x2; p->getter = 976; p++;
    p->type = 4132; p->flags = 0x100; p->offset = (sptr)SetColliderFlagNibble32; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)SetScriptColliderFlagNibble36; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)TestScriptPointInsideCollider; p->putter = 1; p++;
    p->type = 0; p->flags = 0x124; p->getter = (sptr)GetColliderFlagBit52; p->putter = (sptr)SetColliderFlagBit52; p->offset = (sptr)SetColliderFlagBit52; p++;
    p->type = 2; p->flags = 0x12; p->getter = 64; p->putter = 64; p++;
    p->type = 4; p->flags = 0x12; p->getter = 80; p->putter = 80; p++;
    p->type = 2; p->flags = 0x4; p->getter = (sptr)GetObjectWorldPosition; p++;
    p->type = 4; p->flags = 0x4; p->getter = (sptr)GetObjectWorldRotation; p++;
    p->type = 2; p->flags = 0x12; p->getter = 128; p->putter = 128; p++;
    p->type = 1; p->flags = 0x92; p->getter = 128; p->putter = 128; p->offset = 128; p++;
    p->type = 1; p->flags = 0x92; p->getter = 132; p->putter = 132; p->offset = 132; p++;
    p->type = 1; p->flags = 0x92; p->getter = 136; p->putter = 136; p->offset = 136; p++;
    p->type = 0; p->flags = 0x82; p->getter = 144; p->offset = 144; p++;
    p->type = 0; p->flags = 0x82; p->getter = 148; p->offset = 148; p++;
    p->type = 6; p->flags = 0x92; p->getter = 176; p->putter = 176; p->offset = 176; p++;
    p->type = 1; p->flags = 0x122; p->getter = 156; p->putter = (sptr)StoreValueAndMarkSet; p->offset = (sptr)StoreValueAndMarkSet; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)SetScriptTransformObjectKeyedValue; p->putter = 4; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)PlaceScriptAtArrivalPoint; p->putter = 0; p++;
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
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)StartScriptObjectSubGroupFinish; p->putter = 0; p++;
    p->type = 4200; p->flags = 0x22; p->getter = 740; p->putter = (sptr)SetObjectSubGroupState; p++;
    p->type = 2; p->flags = 0x12; p->getter = 64; p->putter = 64; p++;
    p->type = 2; p->flags = 0x4; p->getter = (sptr)ConvertPositionToWorld; p++;
    p->type = 4098; p->flags = 0x880; p->offset = 68; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x880; p->offset = 72; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x880; p->offset = 76; p->intValue = 0; p++;
    p->type = 5; p->flags = 0x80; p->offset = 120; p++;
    p->type = 1; p->flags = 0x892; p->getter = 124; p->putter = 124; p->offset = 124; p->floatValue = 1.0f; p++;
    p->type = 9; p->flags = 0x80; p->offset = 128; p++;
    p->type = 10; p->flags = 0x80; p->offset = 144; p++;
    p->type = 8338; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)CreateScriptAnimationPlayer; p->putter = 4; p++;
    p->type = 8338; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)FindOrCreateScriptSeekedAnimationPlayer; p->putter = 5; p++;
    p->type = 1; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)GetScriptAnimationMarkerTime; p->putter = 1; p++;
    p->type = 1; p->flags = 0x2; p->getter = 52; p++;
    p->type = 0; p->flags = 0x82; p->getter = 80; p->offset = 80; p++;
    p->type = 8323; p->flags = 0x2; p->getter = 8; p++;
    p->type = 8194; p->flags = 0x2; p->getter = 12; p++;
    p->type = 1; p->flags = 0x2; p->getter = 20; p++;
    p->type = 1; p->flags = 0x22; p->getter = 24; p->putter = (sptr)SetAnimationPlayerSpeed; p++;
    p->type = 1; p->flags = 0x22; p->getter = 28; p->putter = (sptr)SetAnimationPlayerSpeedScale; p++;
    p->type = 5; p->flags = 0x22; p->getter = 232; p->putter = (sptr)SetAttachmentSortKeys; p++;
    p->type = 0; p->flags = 0x22; p->getter = 36; p->putter = (sptr)SetAnimationPlayerPadSelect; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SeekScriptAnimationPlayer; p->putter = 3; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)StopScriptAnimationPlayer; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ApplyScriptListedPoseSources; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ReleaseScriptPlayerAttachment; p->putter = 2; p++;
    p->type = 0; p->flags = 0x892; p->getter = 1408; p->putter = 1408; p->offset = 1408; p->intValue = 1; p++;
    p->type = 0; p->flags = 0x892; p->getter = 1420; p->putter = 1420; p->offset = 1420; p->intValue = 1; p++;
    p->type = 2; p->flags = 0x92; p->getter = 1392; p->putter = 1392; p->offset = 1392; p++;
    p->type = 6; p->flags = 0x1100; p->offset = (sptr)AddTrackedKey; p->target = (PropertyTarget)GetAttachedSetTrackedNodes; p++;
    p->type = 8193; p->flags = 0x1020; p->putter = (sptr)AddTrackedNode; p->target = (PropertyTarget)GetAttachedSetTrackedNodes; p++;
    p->type = 8193; p->flags = 0x1020; p->putter = (sptr)RemoveTrackedNode; p->target = (PropertyTarget)GetAttachedSetTrackedNodes; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ClearScriptAttachedSetTrackedNodes; p->putter = 0; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1432; p->putter = 1432; p->offset = 1432; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1436; p->putter = 1436; p->offset = 1436; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1412; p->putter = 1412; p->offset = 1412; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1416; p->putter = 1416; p->offset = 1416; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddMaskedColliderKeyKind0; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddMaskedColliderKeyKind1; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddMaskedColliderKeyKind2; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddMaskedColliderKeyKind3; p++;
    p->type = 0; p->flags = 0x892; p->getter = 1660; p->putter = 1660; p->offset = 1660; p->intValue = 0; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1572; p->putter = 1572; p->offset = 1572; p++;
    p->type = 6; p->flags = 0x880; p->offset = 1592; p->intValue = -1; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1576; p->putter = 1576; p->offset = 1576; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1584; p->putter = 1584; p->offset = 1584; p->floatValue = 300.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1588; p->putter = 1588; p->offset = 1588; p->floatValue = 3.0f; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddAcceptedObjectId; p++;
    p->type = 7; p->flags = 0x100; p->offset = (sptr)AddAcceptedKind; p++;
    p->type = 7; p->flags = 0x100; p->offset = (sptr)AddMaskedColliderListEntry; p++;
    p->type = 0; p->flags = 0x124; p->getter = (sptr)GetAcceptsPlayer; p->putter = (sptr)SetAcceptsPlayer; p->offset = (sptr)SetAcceptsPlayer; p++;
    p->type = 0; p->flags = 0x124; p->getter = (sptr)GetAcceptsFlaggedObjects; p->putter = (sptr)SetAcceptsFlaggedObjects; p->offset = (sptr)SetAcceptsFlaggedObjects; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1676; p->putter = 1676; p->offset = 1676; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)HandleScriptMaskedColliderActivation; p->putter = 0; p++;
    p->type = 0; p->flags = 0x22; p->getter = 1664; p->putter = (sptr)SetObjectHold; p++;
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
    p->type = 4146; p->flags = 0x122; p->getter = 1360; p->putter = (sptr)SetTimedState; p->offset = (sptr)SetTimedState; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1380; p->putter = 1380; p->offset = 1380; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AppendTriggerZoneFirstQueue; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AppendTriggerZoneSecondQueue; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddIncludedId; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddExcludedId; p++;
    p->type = 7; p->flags = 0x100; p->offset = (sptr)AddIncludedKind; p++;
    p->type = 7; p->flags = 0x100; p->offset = (sptr)AddExcludedKind; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1660; p->putter = 1660; p->offset = 1660; p->floatValue = 1.0f; p++;
    p->type = 4105; p->flags = 0x880; p->offset = 1360; p->intValue = 0; p++;
    p->type = 1; p->flags = 0x880; p->offset = 1644; p->floatValue = 1.0f; p++;
    p->type = 0; p->flags = 0x880; p->offset = 1672; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x880; p->offset = 1676; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x880; p->offset = 1680; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x880; p->offset = 1648; p->intValue = 1; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)SetScriptTriggerZoneEntry; p->putter = 4; p++;
    p->type = 6; p->flags = 0x80; p->offset = 1684; p++;
    p->type = 4187; p->flags = 0x22; p->getter = 1664; p->putter = (sptr)SetTriggerZoneMode; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AppendZoneColliderFirstQueue; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AppendZoneColliderSecondQueue; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1768; p->putter = 1768; p->offset = 1768; p->floatValue = 1.0f; p++;
    p->type = 1; p->flags = 0x880; p->offset = 1752; p->floatValue = 1.0f; p++;
    p->type = 0; p->flags = 0x880; p->offset = 1780; p->intValue = 1; p++;
    p->type = 0; p->flags = 0x880; p->offset = 1784; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x880; p->offset = 1756; p->intValue = 0; p++;
    p->type = 0; p->flags = 0x892; p->getter = 1932; p->putter = 1932; p->offset = 1932; p->intValue = 1; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddZoneColliderId; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)SetScriptZoneColliderEntry; p->putter = 4; p++;
    p->type = 0; p->flags = 0x892; p->getter = 1936; p->putter = 1936; p->offset = 1936; p->intValue = 0; p++;
    p->type = -2147475455; p->flags = 0x4; p->getter = (sptr)TestListedEntriesAccepted; p++;
    p->type = 6; p->flags = 0x80; p->offset = 1792; p++;
    p->type = 4187; p->flags = 0x22; p->getter = 1772; p->putter = (sptr)SetZoneColliderMode; p++;
    p->type = 0; p->flags = 0x122; p->getter = 1360; p->putter = (sptr)SetSwitchedColliderEnabled; p->offset = (sptr)SetSwitchedColliderEnabled; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ActivateScriptSwitchedColliderUnlessActive; p->putter = 0; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)TestScriptRequestBlocked; p->putter = 1; p++;
    p->type = 4198; p->flags = 0x4; p->getter = (sptr)StoreSwitchedColliderAccepted; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddLookupId; p++;
    p->type = 1; p->flags = 0x880; p->offset = 1360; p->floatValue = 100.0f; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddObjectSetKey; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1368; p->putter = 1368; p->offset = 1368; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddStateTriggerCountedId; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddStateTriggerItemId; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddStateTriggerAgentId; p++;
    p->type = 0; p->flags = 0x892; p->getter = 1576; p->putter = 1576; p->offset = 1576; p->intValue = 0; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1376; p->putter = 1376; p->offset = 1376; p->intValue = 0; p++;
    p->type = 4137; p->flags = 0x2; p->getter = 1360; p++;
    p->type = -2147475408; p->flags = 0x4; p->getter = (sptr)TestStateTriggerItemsAccepted; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptStateTriggerStateFromMessage; p->putter = 1; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)AddScriptStateTriggerTableEntry; p->putter = 4; p++;
    p->type = 8239; p->flags = 0x2; p->getter = 1728; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddTimedObjectAcceptedObjectId; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddTimedObjectExcludedObjectId; p++;
    p->type = 7; p->flags = 0x100; p->offset = (sptr)AddTimedObjectAcceptedClassId; p++;
    p->type = 7; p->flags = 0x100; p->offset = (sptr)AddTimedObjectExcludedClassId; p++;
    p->type = 0; p->flags = 0x892; p->getter = 1460; p->putter = 1460; p->offset = 1460; p->intValue = 0; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1464; p->putter = 1464; p->offset = 1464; p->floatValue = 1.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1468; p->putter = 1468; p->offset = 1468; p->floatValue = 1.0f; p++;
    p->type = 4140; p->flags = 0x892; p->getter = 1376; p->putter = 1376; p->offset = 1376; p->intValue = 1; p++;
    p->type = 8239; p->flags = 0x2; p->getter = 1360; p++;
    p->type = 4140; p->flags = 0x2; p->getter = 1368; p++;
    p->type = 4139; p->flags = 0x2; p->getter = 1364; p++;
    p->type = 0; p->flags = 0x12; p->getter = 1472; p->putter = 1472; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptTimedObjectMode; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)RequestScriptTimedObjectEnd; p->putter = 0; p++;
    p->type = 4141; p->flags = 0x892; p->getter = 1488; p->putter = 1488; p->offset = 1488; p->intValue = 0; p++;
    p->type = 1; p->flags = 0x892; p->getter = 2796; p->putter = 2796; p->offset = 2796; p->floatValue = 0.25f; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptTimedGroupFadeInTime; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptTimedGroupFadeOutTime; p->putter = 1; p++;
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
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddIdFilterObjectId; p++;
    p->type = 7; p->flags = 0x100; p->offset = (sptr)AddIdFilterClassId; p++;
    p->type = 0; p->flags = 0x80; p->offset = 1360; p++;
    p->type = 6; p->flags = 0x80; p->offset = 1424; p++;
    p->type = 5; p->flags = 0x122; p->getter = 728; p->putter = (sptr)SetEffectSpawnerLimit; p->offset = (sptr)SetEffectSpawnerLimit; p++;
    p->type = 0; p->flags = 0x122; p->getter = 776; p->putter = (sptr)SetEffectSpawnerContinuous; p->offset = (sptr)SetEffectSpawnerContinuous; p++;
    p->type = 4148; p->flags = 0x1092; p->getter = 724; p->putter = 724; p->offset = 724; p->target = (PropertyTarget)MarkEffectSpawnerChanged; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 732; p->putter = 732; p->offset = 732; p->target = (PropertyTarget)MarkEffectSpawnerChanged; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 756; p->putter = 756; p->offset = 756; p->target = (PropertyTarget)MarkEffectSpawnerChanged; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 744; p->putter = 744; p->offset = 744; p->target = (PropertyTarget)MarkEffectSpawnerChanged; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 748; p->putter = 748; p->offset = 748; p->target = (PropertyTarget)MarkEffectSpawnerChanged; p++;
    p->type = 0; p->flags = 0x24; p->getter = (sptr)GetEffectSpawnerInactive; p->putter = (sptr)SetEffectSpawnerDisabled; p++;
    p->type = 0; p->flags = 0x82; p->getter = 740; p->offset = 740; p++;
    p->type = 6; p->flags = 0x82; p->getter = 760; p->offset = 760; p++;
    p->type = 6; p->flags = 0x82; p->getter = 764; p->offset = 764; p++;
    p->type = 6; p->flags = 0x82; p->getter = 768; p->offset = 768; p++;
    p->type = 6; p->flags = 0x82; p->getter = 772; p->offset = 772; p++;
    p->type = 6; p->flags = 0x82; p->getter = 784; p->offset = 784; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptEffectSpawnerActiveFor; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptEffectSpawnerActiveForever; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptEffectSpawnerInactive; p->putter = 0; p++;
    p->type = 0; p->flags = 0x4; p->getter = (sptr)GetEffectSpawnerActive; p++;
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
    p->type = 4115; p->flags = 0x100; p->offset = (sptr)SetEffectSpawnerKind; p++;
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
    p->type = 18; p->flags = 0x400; p->getter = (sptr)AddScriptSpawnRangeEntry; p->f10 = 0; p->putter = 6; p++;
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
    p->type = 18; p->flags = 0x400; p->getter = (sptr)AddScriptRecordMemberRangeEntry; p->f10 = 0; p->putter = 6; p++;
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
    p->type = 4115; p->flags = 0x100; p->offset = (sptr)SetOwnedSpawnRecordKind; p++;
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
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SendScriptEmptyMessageC7A; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SendScriptTwoVectorMessageC7A; p->putter = 6; p++;
    p->type = 6; p->flags = 0x1082; p->getter = 496; p->offset = 496; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 1; p->flags = 0x1082; p->getter = 500; p->offset = 500; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 1; p->flags = 0x1082; p->getter = 496; p->offset = 496; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 1; p->flags = 0x1082; p->getter = 500; p->offset = 500; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 1; p->flags = 0x1082; p->getter = 504; p->offset = 504; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 0; p->flags = 0x1082; p->getter = 496; p->offset = 496; p->target = (PropertyTarget)GetOwnedSpawnRecord; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SendScriptEmptyMessageC78; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SendScriptTwoVectorMessageC78; p->putter = 6; p++;
    p->type = 4122; p->flags = 0x122; p->getter = 720; p->putter = (sptr)SetConeVolumeMode; p->offset = (sptr)SetConeVolumeMode; p++;
    p->type = 2; p->flags = 0xA2; p->getter = 736; p->putter = (sptr)SetConeVolumeColor; p->offset = 736; p++;
    p->type = 1; p->flags = 0xA2; p->getter = 752; p->putter = (sptr)SetConeVolumeSecondLevel; p->offset = 752; p++;
    p->type = 1; p->flags = 0xA2; p->getter = 756; p->putter = (sptr)SetConeVolumeThirdLevel; p->offset = 756; p++;
    p->type = 1; p->flags = 0xA2; p->getter = 760; p->putter = (sptr)SetConeVolumeFirstAngle; p->offset = 760; p++;
    p->type = 1; p->flags = 0xA2; p->getter = 764; p->putter = (sptr)SetConeVolumeSecondAngle; p->offset = 764; p++;
    p->type = 1; p->flags = 0xA2; p->getter = 768; p->putter = (sptr)SetConeVolumeThirdAngle; p->offset = 768; p++;
    p->type = 2; p->flags = 0x122; p->getter = 784; p->putter = (sptr)SetConeVolumeDirection; p->offset = (sptr)SetConeVolumeDirection; p++;
    p->type = 0; p->flags = 0x122; p->getter = 772; p->putter = (sptr)SetConeVolumeValue; p->offset = (sptr)SetConeVolumeValue; p++;
    p->type = 0; p->flags = 0x122; p->getter = 772; p->putter = (sptr)SetConeVolumeValue; p->offset = (sptr)SetConeVolumeValue; p++;
    p->type = 0; p->flags = 0x92; p->getter = 776; p->putter = 776; p->offset = 776; p++;
    p->type = 10; p->flags = 0xA2; p->getter = 816; p->putter = (sptr)SetConeVolumeRange; p->offset = 816; p++;
    p->type = 1; p->flags = 0xA2; p->getter = 824; p->putter = (sptr)SetConeVolumeOuterAngle; p->offset = 824; p++;
    p->type = 1; p->flags = 0xA2; p->getter = 828; p->putter = (sptr)SetConeVolumeInnerAngle; p->offset = 828; p++;
    p->type = 2; p->flags = 0xA2; p->getter = 832; p->putter = (sptr)SetConeVolumeVector340; p->offset = 832; p++;
    p->type = 1; p->flags = 0x124; p->getter = (sptr)GetConeVolumeSecondLevel; p->putter = (sptr)SetConeVolumeOuterLevels; p->offset = (sptr)SetConeVolumeOuterLevels; p++;
    p->type = 2; p->flags = 0x124; p->getter = (sptr)GetConeVolumeColorRgb; p->putter = (sptr)SetConeVolumeColorRgb; p->offset = (sptr)SetConeVolumeColorRgb; p++;
    p->type = 0; p->flags = 0x0; p++;
    p->type = 1; p->flags = 0x0; p++;
    p->type = 1; p->flags = 0x0; p++;
    p->type = 1; p->flags = 0x0; p++;
    p->type = 1; p->flags = 0x0; p++;
    p->type = 0; p->flags = 0x80; p->offset = 68; p++;
    p->type = 8339; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)CreateScriptStateWalker; p->putter = 3; p++;
    p->type = 8194; p->flags = 0x2; p->getter = 28; p++;
    p->type = 6; p->flags = 0x24; p->getter = (sptr)GetStateWalkerTargetKey; p->putter = (sptr)SetStateWalkerTarget; p++;
    p->type = 6; p->flags = 0x4; p->getter = (sptr)GetStateWalkerCurrentKey; p++;
    p->type = 6; p->flags = 0x4; p->getter = (sptr)GetStateWalkerNextKey; p++;
    p->type = 1; p->flags = 0x22; p->getter = 56; p->putter = (sptr)SetStateWalkerSpeed; p++;
    p->type = 8338; p->flags = 0x2; p->getter = 36; p++;
    p->type = 6; p->flags = 0x20; p->putter = (sptr)TeleportStateWalker; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)DestroyScriptStateWalker; p->putter = 0; p++;
    p->type = 8328; p->flags = 0x2; p->getter = 24; p++;
    p->type = 0; p->flags = 0x880; p->offset = 7544; p->intValue = 1; p++;
    p->type = 1; p->flags = 0x880; p->offset = 7548; p->floatValue = 1.0f; p++;
    p->type = 1; p->flags = 0xA2; p->getter = 7532; p->putter = (sptr)SetWorldLightingParamA; p->offset = 7532; p++;
    p->type = 1; p->flags = 0xA2; p->getter = 7528; p->putter = (sptr)SetWorldLightingParamB; p->offset = 7528; p++;
    p->type = 13; p->flags = 0x80; p->offset = 7524; p++;
    p->type = 1; p->flags = 0x100; p->offset = (sptr)SnapCurrentCameraZoom; p++;
    p->type = 1; p->flags = 0x100; p->offset = (sptr)SetCurrentCameraNearDistance; p++;
    p->type = 1; p->flags = 0x100; p->offset = (sptr)SetCurrentCameraFarDistance; p++;
    p->type = 1; p->flags = 0x100; p->offset = (sptr)SetCurrentCameraFogNear; p++;
    p->type = 1; p->flags = 0x100; p->offset = (sptr)SetCurrentCameraFogFar; p++;
    p->type = 1; p->flags = 0x100; p->offset = (sptr)SetCurrentCameraFogStrength; p++;
    p->type = 13; p->flags = 0x100; p->offset = (sptr)SetCurrentCameraFogColor; p++;
    p->type = 1; p->flags = 0x100; p->offset = (sptr)SetCurrentCameraDistanceScale; p++;
    p->type = 1; p->flags = 0x892; p->getter = 8968; p->putter = 8968; p->offset = 8968; p->floatValue = 15.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 8972; p->putter = 8972; p->offset = 8972; p->floatValue = 180.0f; p++;
    p->type = 1; p->flags = 0x22; p->getter = 8984; p->putter = (sptr)SetWorldSoundLevel; p++;
    p->type = 1; p->flags = 0x22; p->getter = 9036; p->putter = (sptr)SetWorldValueAndTarget; p++;
    p->type = 1; p->flags = 0x22; p->getter = 9040; p->putter = (sptr)SetWorldValueTarget; p++;
    p->type = 5; p->flags = 0x1092; p->getter = 4; p->putter = 4; p->offset = 4; p->target = (PropertyTarget)GetScatterController; p++;
    p->type = 5; p->flags = 0x1092; p->getter = 8; p->putter = 8; p->offset = 8; p->target = (PropertyTarget)GetScatterController; p++;
    p->type = 5; p->flags = 0x1092; p->getter = 12; p->putter = 12; p->offset = 12; p->target = (PropertyTarget)GetScatterController; p++;
    p->type = 5; p->flags = 0x1092; p->getter = 16; p->putter = 16; p->offset = 16; p->target = (PropertyTarget)GetScatterController; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ScatterScriptRandomObjects; p->putter = 3; p++;
    p->type = 1; p->flags = 0x24; p->getter = (sptr)GetGameStateDeltaTime; p->putter = (sptr)SetScatterLevelBuiltin; p++;
    p->type = 1; p->flags = 0x24; p->getter = (sptr)GetCurrentScatterLevel; p->putter = (sptr)SetCurrentScatterLevel; p++;
    p->type = 14; p->flags = 0x120; p->putter = (sptr)AddWorldSoundEntry; p->offset = (sptr)AddWorldSoundEntry; p++;
    p->type = 10; p->flags = 0x120; p->putter = (sptr)SetLastWorldSoundEntryFromPoint; p->offset = (sptr)SetLastWorldSoundEntryFromPoint; p++;
    p->type = 10; p->flags = 0x120; p->putter = (sptr)SetLastWorldSoundEntryValues; p->offset = (sptr)SetLastWorldSoundEntryValues; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)SetScriptIopChannel2Setting; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)PushScriptIopChannel2Setting; p->putter = 2; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)PopScriptIopChannel2Setting; p->putter = 0; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)TestScriptLevelEntryFlag1; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)TestScriptLevelEntryFlag2; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)TestScriptLevelEntryFlag4; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)TestScriptLevelEntryFlag8; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)CheckScriptEntryOneBitRequirement; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)CheckScriptEntryTwoBitRequirement; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)CheckScriptEntryThreeBitRequirement; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptEntrySlotValue; p->putter = 3; p++;
    p->type = 5; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)GetScriptEntrySlotValue; p->putter = 2; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)IsScriptLevelRecordComplete; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)IsScriptLevelDone; p->putter = 1; p++;
    p->type = 5; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)RecomputeScriptSaveCompletion; p->putter = 0; p++;
    p->type = 0; p->flags = 0x4; p->getter = (sptr)GetHasStreamVoice; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)PopScriptActiveSequenceElement; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ShowScriptPauseMenuPageWith; p->putter = 2; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ShowScriptCountedScreenElement; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)HideScriptCountedScreenElement; p->putter = 0; p++;
    p->type = 0; p->flags = 0x92; p->getter = 9044; p->putter = 9044; p->offset = 9044; p++;
    p->type = 5; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)PushScriptSoundLevel; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)RemoveScriptSoundLevel; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptCachedVoiceParam; p->putter = 2; p++;
    p->type = 5; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)GetScriptCachedVoiceParam; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)RefreshScriptCachedVoiceParam; p->putter = 2; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)AcquireScriptPadSelectFlag; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ReleaseScriptPadSelectFlag; p->putter = 0; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)ClearScriptWorldFlagBit; p->putter = 1; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)SetScriptWorldFlagBit; p->putter = 1; p++;
    p->type = 5; p->flags = 0x4; p->getter = (sptr)GetSaveSpareCount; p++;
    p->type = 5; p->flags = 0x4; p->getter = (sptr)GetReserveUnitCount; p++;
    p->type = 2; p->flags = 0x22; p->getter = 64; p->putter = (sptr)SetCameraPosition; p++;
    p->type = 4; p->flags = 0x22; p->getter = 128; p->putter = (sptr)SetCameraOrientation; p++;
    p->type = 1; p->flags = 0x22; p->getter = 452; p->putter = (sptr)SnapCameraZoom; p++;
    p->type = 1; p->flags = 0x12; p->getter = 456; p->putter = 456; p++;
    p->type = 12; p->flags = 0x12; p->getter = 464; p->putter = 464; p++;
    p->type = 1; p->flags = 0x22; p->getter = 484; p->putter = (sptr)SetCameraNearDistance; p++;
    p->type = 1; p->flags = 0x22; p->getter = 488; p->putter = (sptr)SetCameraFarDistance; p++;
    p->type = 1; p->flags = 0x22; p->getter = 504; p->putter = (sptr)SetCameraFogNear; p++;
    p->type = 1; p->flags = 0x22; p->getter = 508; p->putter = (sptr)SetCameraFogFar; p++;
    p->type = 1; p->flags = 0x22; p->getter = 512; p->putter = (sptr)SetCameraFogStrength; p++;
    p->type = 1; p->flags = 0x22; p->getter = 448; p->putter = (sptr)SetCameraDistanceScale; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)PushScriptCameraStackValue; p->putter = 1; p++;
    p->type = 4177; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)PopScriptCameraStackValue; p->putter = 0; p++;
    p->type = 4177; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)PeekScriptCameraStackValue; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptCameraControllerSettings; p->putter = 3; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)RecordScriptCameraTimestamp; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)RequestScriptPlainCameraSnap; p->putter = 0; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)TestScriptSphereInCameraView; p->putter = 3; p++;
    p->type = 6; p->flags = 0x80; p->offset = 720; p++;
    p->type = 2; p->flags = 0x80; p->offset = 736; p++;
    p->type = 2; p->flags = 0x80; p->offset = 752; p++;
    p->type = 2; p->flags = 0x80; p->offset = 768; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)PushScriptObjectCameraController; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)RemoveScriptObjectCameraController; p->putter = 0; p++;
    p->type = 0; p->flags = 0x92; p->getter = 720; p->putter = 720; p->offset = 720; p++;
    p->type = 4124; p->flags = 0x92; p->getter = 1364; p->putter = 1364; p->offset = 1364; p++;
    p->type = 6; p->flags = 0x1100; p->offset = (sptr)AddTrackedKey; p->target = (PropertyTarget)GetContactTrackerRecord; p++;
    p->type = 8193; p->flags = 0x1020; p->putter = (sptr)AddTrackedNode; p->target = (PropertyTarget)GetContactTrackerRecord; p++;
    p->type = 8193; p->flags = 0x1020; p->putter = (sptr)RemoveTrackedNode; p->target = (PropertyTarget)GetContactTrackerRecord; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ClearScriptTrackedNodes; p->putter = 0; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1368; p->putter = 1368; p->offset = 1368; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1372; p->putter = 1372; p->offset = 1372; p++;
    p->type = 4127; p->flags = 0x92; p->getter = 136; p->putter = 136; p->offset = 136; p++;
    p->type = 1; p->flags = 0x92; p->getter = 140; p->putter = 140; p->offset = 140; p++;
    p->type = 0; p->flags = 0x92; p->getter = 144; p->putter = 144; p->offset = 144; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AppendFlaggedObjectIdB; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AppendFlaggedObjectIdA; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)SetFlaggedChildId; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)CollectScriptNumberedItem; p->putter = 0; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1448; p->putter = 1448; p->offset = 1448; p++;
    p->type = 0; p->flags = 0x4; p->getter = (sptr)GetNumberedItemFlag; p++;
    p->type = 1; p->flags = 0x122; p->getter = 1360; p->putter = (sptr)SetOffsetScale; p->offset = (sptr)SetOffsetScale; p++;
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
    p->type = 6; p->flags = 0xA2; p->getter = 2340; p->putter = (sptr)SetAgentPathObjectId; p->offset = 2340; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1848; p->putter = 1848; p->offset = 1848; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1856; p->putter = 1856; p->offset = 1856; p++;
    p->type = 1; p->flags = 0x112; p->getter = 1868; p->putter = 1868; p->offset = (sptr)SetAgentAngleLimitDegrees; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)SetScriptAgentStateClipId; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptAgentStateClip; p->putter = 2; p++;
    p->type = 8323; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)GetScriptAgentStateClip; p->putter = 1; p++;
    p->type = 1; p->flags = 0x92; p->getter = 2672; p->putter = 2672; p->offset = 2672; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)AddScriptAgentClipGroup; p->f10 = 0; p->putter = 4; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)AddScriptAgentMeshKey; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)AddScriptAgentExtraClip; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ForceScriptAgentState; p->putter = 2; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)SetScriptAgentSecondaryClipId; p->f10 = 0; p->putter = 2; p++;
    p->type = 5; p->flags = 0x92; p->getter = 2664; p->putter = 2664; p->offset = 2664; p++;
    p->type = 0; p->flags = 0x92; p->getter = 2668; p->putter = 2668; p->offset = 2668; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SteerScriptAgentAlongPath; p->putter = 0; p++;
    p->type = 10; p->flags = 0x92; p->getter = 2972; p->putter = 2972; p->offset = 2972; p++;
    p->type = 0; p->flags = 0x92; p->getter = 2944; p->putter = 2944; p->offset = 2944; p++;
    p->type = 6; p->flags = 0x92; p->getter = 2892; p->putter = 2892; p->offset = 2892; p++;
    p->type = 8195; p->flags = 0x24; p->getter = (sptr)StoreAgentTarget; p->putter = (sptr)SetAgentSecondaryTarget; p++;
    p->type = 0; p->flags = 0x92; p->getter = 2884; p->putter = 2884; p->offset = 2884; p++;
    p->type = 0; p->flags = 0x92; p->getter = 2844; p->putter = 2844; p->offset = 2844; p++;
    p->type = 1; p->flags = 0x92; p->getter = 2848; p->putter = 2848; p->offset = 2848; p++;
    p->type = 9; p->flags = 0x92; p->getter = 2864; p->putter = 2864; p->offset = 2864; p++;
    p->type = 4174; p->flags = 0x92; p->getter = 2336; p->putter = 2336; p->offset = 2336; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptAgentMainClip; p->putter = 1; p++;
    p->type = 5; p->flags = 0x92; p->getter = 2904; p->putter = 2904; p->offset = 2904; p++;
    p->type = 2; p->flags = 0x92; p->getter = 2912; p->putter = 2912; p->offset = 2912; p++;
    p->type = 0; p->flags = 0x92; p->getter = 2928; p->putter = 2928; p->offset = 2928; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)SetAgentMemberGroupId; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)SetAgentTargetSetId; p++;
    p->type = 1; p->flags = 0x80; p->offset = 2840; p++;
    p->type = 1; p->flags = 0x92; p->getter = 3024; p->putter = 3024; p->offset = 3024; p++;
    p->type = 0; p->flags = 0x92; p->getter = 3028; p->putter = 3028; p->offset = 3028; p++;
    p->type = 4133; p->flags = 0x2; p->getter = 1828; p++;
    p->type = 0; p->flags = 0x92; p->getter = 2752; p->putter = 2752; p->offset = 2752; p++;
    p->type = 0; p->flags = 0x4; p->getter = (sptr)IsAgentNearPathEnd; p++;
    p->type = 10; p->flags = 0x92; p->getter = 3040; p->putter = 3040; p->offset = 3040; p++;
    p->type = 0; p->flags = 0x92; p->getter = 3036; p->putter = 3036; p->offset = 3036; p++;
    p->type = 1; p->flags = 0x92; p->getter = 3048; p->putter = 3048; p->offset = 3048; p++;
    p->type = 0; p->flags = 0x92; p->getter = 3032; p->putter = 3032; p->offset = 3032; p++;
    p->type = 0; p->flags = 0x92; p->getter = 3080; p->putter = 3080; p->offset = 3080; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddOwnedWantedId; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddListedWantedId; p++;
    p->type = 1; p->flags = 0x92; p->getter = 3096; p->putter = 3096; p->offset = 3096; p++;
    p->type = 1; p->flags = 0x92; p->getter = 3100; p->putter = 3100; p->offset = 3100; p++;
    p->type = 1; p->flags = 0x92; p->getter = 3104; p->putter = 3104; p->offset = 3104; p++;
    p->type = 1; p->flags = 0x92; p->getter = 3108; p->putter = 3108; p->offset = 3108; p++;
    p->type = 6; p->flags = 0x92; p->getter = 3112; p->putter = 3112; p->offset = 3112; p++;
    p->type = 6; p->flags = 0x80; p->offset = 3088; p++;
    p->type = 8288; p->flags = 0x2; p->getter = 3092; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)SetScriptCompanionAgentLookId; p->f10 = 0; p->putter = 2; p++;
    p->type = 0; p->flags = 0x92; p->getter = 3272; p->putter = 3272; p->offset = 3272; p++;
    p->type = 0; p->flags = 0x92; p->getter = 3276; p->putter = 3276; p->offset = 3276; p++;
    p->type = 4197; p->flags = 0x92; p->getter = 3280; p->putter = 3280; p->offset = 3280; p++;
    p->type = 6; p->flags = 0x92; p->getter = 3052; p->putter = 3052; p->offset = 3052; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddCompanionAgentExcludedId; p++;
    p->type = 1; p->flags = 0x880; p->offset = 1740; p->floatValue = 35.0f; p++;
    p->type = 1; p->flags = 0x120; p->putter = (sptr)ScaleTurningColliderRamp; p->offset = (sptr)ScaleTurningColliderRamp; p++;
    p->type = 1; p->flags = 0x122; p->getter = 1792; p->putter = (sptr)SetTurningColliderGravityScale; p->offset = (sptr)SetTurningColliderGravityScale; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1372; p->putter = 1372; p->offset = 1372; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1376; p->putter = 1376; p->offset = 1376; p++;
    p->type = 4135; p->flags = 0x92; p->getter = 1360; p->putter = 1360; p->offset = 1360; p++;
    p->type = 4136; p->flags = 0x92; p->getter = 1544; p->putter = 1544; p->offset = 1544; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1380; p->putter = 1380; p->offset = 1380; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1384; p->putter = 1384; p->offset = 1384; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1396; p->putter = 1396; p->offset = 1396; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1388; p->putter = 1388; p->offset = 1388; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1472; p->putter = 1472; p->offset = 1472; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)StartScriptChildGroupDelay; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)StepScriptChildGroupObject; p->putter = 0; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1652; p->putter = 1652; p->offset = 1652; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1656; p->putter = 1656; p->offset = 1656; p++;
    p->type = 4124; p->flags = 0x92; p->getter = 1660; p->putter = 1660; p->offset = 1660; p++;
    p->type = 14; p->flags = 0x1092; p->getter = 0; p->putter = 0; p->offset = 0; p->target = (PropertyTarget)GetChildGroupSoundParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 4; p->putter = 4; p->offset = 4; p->target = (PropertyTarget)GetChildGroupSoundParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 8; p->putter = 8; p->offset = 8; p->target = (PropertyTarget)GetChildGroupSoundParams; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 12; p->putter = 12; p->offset = 12; p->target = (PropertyTarget)GetChildGroupSoundParams; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1368; p->putter = 1368; p->offset = 1368; p++;
    p->type = 0; p->flags = 0x82; p->getter = 1668; p->offset = 1668; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)PlaceScriptPlayerOnGround; p->putter = 3; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ReleaseScriptPlayerToState2; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)IgnoreScriptPlayerArgument; p->putter = 1; p++;
    p->type = 0; p->flags = 0x92; p->getter = 8640; p->putter = 8640; p->offset = 8640; p++;
    p->type = 4178; p->flags = 0x22; p->getter = 10008; p->putter = (sptr)SetPlayerPadSelectMode; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptPlayerPath; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SwitchScriptPlayerState11; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SeekScriptObjects105Animations; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SwapInScriptPlayerStandIn; p->putter = 0; p++;
    p->type = 0; p->flags = 0x92; p->getter = 11220; p->putter = 11220; p->offset = 11220; p++;
    p->type = 0; p->flags = 0xA2; p->getter = 11224; p->putter = (sptr)SetPlayerProbeContactsDisabled; p->offset = 11224; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)QueueScriptPlayerWalkerActivation; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)QueueScriptPlayerFirstActivation; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)QueueScriptPlayerSecondActivation; p->putter = 1; p++;
    p->type = 4144; p->flags = 0x80; p->offset = 68; p++;
    p->type = 6; p->flags = 0x80; p->offset = 52; p++;
    p->type = 6; p->flags = 0x80; p->offset = 56; p++;
    p->type = 4127; p->flags = 0x80; p->offset = 76; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)SetScriptAimBlendGridVector; p->f10 = 0; p->putter = 3; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)SetScriptAimBlendGridVectorFlagged; p->f10 = 0; p->putter = 3; p++;
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
    p->type = 6; p->flags = 0x100; p->offset = (sptr)SetPairControllerFirstTemplateId; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)SetPairControllerSecondTemplateId; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)SetPairControllerHostId; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)SetPairControllerExtraId; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AppendPairControllerId; p++;
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
    p->type = 4145; p->flags = 0x22; p->getter = 1360; p->putter = (sptr)SetPooledObjectState; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1368; p->putter = 1368; p->offset = 1368; p->floatValue = 2500.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1372; p->putter = 1372; p->offset = 1372; p->floatValue = 20.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1376; p->putter = 1376; p->offset = 1376; p->floatValue = 30.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1380; p->putter = 1380; p->offset = 1380; p->floatValue = 1.5f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1384; p->putter = 1384; p->offset = 1384; p->floatValue = 10.0f; p++;
    p->type = 6; p->flags = 0x80; p->offset = 1728; p++;
    p->type = 5; p->flags = 0x880; p->offset = 1732; p->intValue = 5; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1744; p->putter = 1744; p->offset = 1744; p->floatValue = 1.0f; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1748; p->putter = 1748; p->offset = 1748; p->floatValue = 20.0f; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddPooledHolderItem; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ResetScriptCollectedItems; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)CollectScriptItem; p->putter = 1; p++;
    p->type = 1; p->flags = 0x892; p->getter = 1680; p->putter = 1680; p->offset = 1680; p->floatValue = 800.0f; p++;
    p->type = 8194; p->flags = 0x12; p->getter = 1684; p->putter = 1684; p++;
    p->type = 2; p->flags = 0x12; p->getter = 1696; p->putter = 1696; p++;
    p->type = 0; p->flags = 0x92; p->getter = 1720; p->putter = 1720; p->offset = 1720; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)AddScriptContactListId; p->f10 = 0; p->putter = 1; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)AddScriptContactListKind; p->f10 = 0; p->putter = 1; p++;
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
    p->type = 18; p->flags = 0x400; p->getter = (sptr)AddScriptStateResetEntry; p->f10 = 0; p->putter = 4; p++;
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
    p->type = 1; p->flags = 0x122; p->getter = 864; p->putter = (sptr)SetOnOffObjectBlockValue; p->offset = (sptr)SetOnOffObjectBlockValue; p++;
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
    p->type = 4109; p->flags = 0xA2; p->getter = 920; p->putter = (sptr)SetOnOffObjectForcedState; p->offset = 920; p++;
    p->type = 1; p->flags = 0x92; p->getter = 880; p->putter = 880; p->offset = 880; p++;
    p->type = 1; p->flags = 0x92; p->getter = 884; p->putter = 884; p->offset = 884; p++;
    p->type = 6; p->flags = 0xA0; p->putter = (sptr)FollowObjectById; p->offset = 1400; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptCurrentTargetFollower; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ClearScriptCurrentTargetFollower; p->putter = 0; p++;
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
    p->type = 18; p->flags = 0x400; p->getter = (sptr)AddScriptObjectPoolEntry; p->f10 = 0; p->putter = 4; p++;
    p->type = 0; p->flags = 0x1082; p->getter = 4; p->offset = 4; p->target = (PropertyTarget)GetObjectPoolShare; p++;
    p->type = 4158; p->flags = 0x92; p->getter = 64; p->putter = 64; p->offset = 64; p++;
    p->type = 5; p->flags = 0x12; p->getter = 68; p->putter = 68; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)EnableScriptObjectPoolEntry; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)DisableScriptObjectPoolEntry; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptObjectPoolEntryCount; p->putter = 2; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ChooseScriptObjectPoolItem; p->putter = 0; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ReleaseScriptObjectPoolItem; p->putter = 1; p++;
    p->type = 8195; p->flags = 0x2; p->getter = 72; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ResetScriptPlacementRecord; p->putter = 0; p++;
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
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ResetScriptObjectPoolReleaseRecord; p->putter = 0; p++;
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
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ClearScriptObjectPoolHeadingRecord; p->putter = 0; p++;
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
    p->type = 4156; p->flags = 0x22; p->getter = 1364; p->putter = (sptr)SetObjectCyclerState; p++;
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
    p->type = 4167; p->flags = 0x22; p->getter = 724; p->putter = (sptr)SetStepSequenceState; p++;
    p->type = 6; p->flags = 0x80; p->offset = 768; p++;
    p->type = 0; p->flags = 0x92; p->getter = 804; p->putter = 804; p->offset = 804; p++;
    p->type = 0; p->flags = 0x92; p->getter = 808; p->putter = 808; p->offset = 808; p++;
    p->type = 0; p->flags = 0x92; p->getter = 812; p->putter = 812; p->offset = 812; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)SetScriptStepSequenceModeOne; p->f10 = 0; p->putter = 0; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)SetScriptStepSequenceCameraMode; p->f10 = 0; p->putter = 0; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)AddScriptSequenceExtraTarget; p->f10 = 0; p->putter = 2; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ChooseScriptStepSequenceState; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ResetScriptStepSequence; p->putter = 0; p++;
    p->type = 6; p->flags = 0x92; p->getter = 780; p->putter = 780; p->offset = 780; p++;
    p->type = 0; p->flags = 0x24; p->getter = (sptr)ReadSequenceTarget; p->putter = (sptr)WriteSequenceTarget; p++;
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
    p->type = 6; p->flags = 0xA0; p->putter = (sptr)SetObjectLinkId; p->offset = 812; p++;
    p->type = 2; p->flags = 0x92; p->getter = 784; p->putter = 784; p->offset = 784; p++;
    p->type = 1; p->flags = 0x92; p->getter = 808; p->putter = 808; p->offset = 808; p++;
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddStateWalkerGroupId; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)QueueScriptWalkerActivationOnPlayer; p->putter = 0; p++;
    p->type = 5; p->flags = 0x100; p->offset = (sptr)SetStateWalkerGroupMaskBit; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)AddScriptOscillatorXEntry; p->f10 = 0; p->putter = 0; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)AddScriptOscillatorYZEntry; p->f10 = 0; p->putter = 0; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 16; p->putter = 16; p->offset = 16; p->target = (PropertyTarget)GetOscillatorEntryForPeriod; p++;
    p->type = 1; p->flags = 0x124; p->getter = (sptr)GetOscillatorEntryPeriod; p->putter = (sptr)SetOscillatorEntryPeriod; p->offset = (sptr)SetOscillatorEntryPeriod; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 104; p->putter = 104; p->offset = 104; p->target = (PropertyTarget)GetOscillatorEntryForPeriod; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 108; p->putter = 108; p->offset = 108; p->target = (PropertyTarget)GetOscillatorEntryForPeriod; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 32; p->putter = 32; p->offset = 32; p->target = (PropertyTarget)GetOscillatorEntryForPeriod; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 64; p->putter = 64; p->offset = 64; p->target = (PropertyTarget)GetOscillatorEntryForPeriod; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 48; p->putter = 48; p->offset = 48; p->target = (PropertyTarget)GetOscillatorEntryForPeriod; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 80; p->putter = 80; p->offset = 80; p->target = (PropertyTarget)GetOscillatorEntryForPeriod; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 16; p->putter = 16; p->offset = 16; p->target = (PropertyTarget)GetOscillatorEntryForVectors; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 48; p->putter = 48; p->offset = 48; p->target = (PropertyTarget)GetOscillatorEntryForVectors; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 56; p->putter = 56; p->offset = 56; p->target = (PropertyTarget)GetOscillatorEntryForVectors; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)AddScriptOscillatorEntryVectorA; p->f10 = 0; p->putter = 4; p++;
    p->type = 2; p->flags = 0x1092; p->getter = 32; p->putter = 32; p->offset = 32; p->target = (PropertyTarget)GetOscillatorEntryForVectors; p++;
    p->type = 10; p->flags = 0x1092; p->getter = 128; p->putter = 128; p->offset = 128; p->target = (PropertyTarget)GetOscillatorEntryForVectors; p++;
    p->type = 1; p->flags = 0x1092; p->getter = 136; p->putter = 136; p->offset = 136; p->target = (PropertyTarget)GetOscillatorEntryForVectors; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)AddScriptOscillatorEntryVectorB; p->f10 = 0; p->putter = 4; p++;
    p->type = 5; p->flags = 0x2; p->getter = 56; p++;
    p->type = 5; p->flags = 0x12; p->getter = 1744; p->putter = 1744; p++;
    p->type = 0; p->flags = 0x92; p->getter = 3088; p->putter = 3088; p->offset = 3088; p++;
    p->type = 8339; p->flags = 0x2; p->getter = 3600; p++;
    p->type = 8307; p->flags = 0x92; p->getter = 3604; p->putter = 3604; p->offset = 3604; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)AdvanceScriptWorld2BossPhase; p->putter = 0; p++;
    p->type = 1; p->flags = 0x4; p->getter = (sptr)GetWorld2BossLevelFactor; p++;
    p->type = 4175; p->flags = 0x22; p->getter = 1824; p->putter = (sptr)SetTintBlendColliderState; p++;
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
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AddPlayerLinkedColliderId; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1616; p->putter = 1616; p->offset = 1616; p++;
    p->type = 10; p->flags = 0x92; p->getter = 1624; p->putter = 1624; p->offset = 1624; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1600; p->putter = 1600; p->offset = 1600; p++;
    p->type = 18; p->flags = 0x400; p->getter = (sptr)AddScriptEntryRecordKey; p->f10 = 0; p->putter = 2; p++;
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
    p->type = 6; p->flags = 0x100; p->offset = (sptr)AppendGaugeSlot; p++;
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
    p->type = 8302; p->flags = 0x22; p->getter = 2096; p->putter = (sptr)SetPathFollowerPath; p++;
    p->type = 8302; p->flags = 0x22; p->getter = 2120; p->putter = (sptr)SetPathFollowerSecondPath; p++;
    p->type = 5; p->flags = 0x92; p->getter = 2820; p->putter = 2820; p->offset = 2820; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)AddScriptPathFollowerEntry; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)AddScriptPathFollowerActiveEntry; p->putter = 5; p++;
    p->type = 8330; p->flags = 0x12; p->getter = 2876; p->putter = 2876; p++;
    p->type = 4183; p->flags = 0x122; p->getter = 2868; p->putter = (sptr)SetPathFollowerMode; p->offset = (sptr)SetPathFollowerMode; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)ResetScriptPathFollower; p->putter = 0; p++;
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
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)TestScriptPointAgainstObjectShape; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)TestScriptPointInsideFaceTreeObject; p->putter = 1; p++;
    p->type = 0; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)AddScriptSeekingAgentObject; p->putter = 1; p++;
    p->type = 8307; p->flags = 0x22; p->getter = 3112; p->putter = (sptr)SetSeekingAgentStateTarget; p++;
    p->type = 8307; p->flags = 0x22; p->getter = 3108; p->putter = (sptr)SetSeekingAgentTarget; p++;
    p->type = 2; p->flags = 0x4; p->getter = (sptr)PickRandomPointOnPointGraph; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1740; p->putter = 1740; p->offset = 1740; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1744; p->putter = 1744; p->offset = 1744; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1748; p->putter = 1748; p->offset = 1748; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1752; p->putter = 1752; p->offset = 1752; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)StartScriptC24ObjectPath; p->putter = 2; p++;
    p->type = 4176; p->flags = 0x22; p->getter = 2992; p->putter = (sptr)SetModeWalkerMode; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)ResetScriptEntryQueue; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)BindScriptEntryQueueToObject; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)UnbindScriptEntryQueue; p->putter = 0; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)AddScriptQueueEntryKind0; p->putter = 1; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)AddScriptQueueEntryKind1; p->putter = 1; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)AddScriptQueueEntryKind10; p->putter = 1; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)AddScriptQueueEntryKind2; p->putter = 1; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)AddScriptQueueEntryKind3; p->putter = 1; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)AddScriptQueueEntryKind4; p->putter = 2; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)AddScriptQueueEntryKind5; p->putter = 4; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)AddScriptQueueEntryKind6; p->putter = 3; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)AddScriptQueueEntryKind7; p->putter = 3; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)AddScriptQueueEntryKind8; p->putter = 3; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)AddScriptQueueEntryKind9; p->putter = 2; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)AddScriptQueueEntryKind11; p->putter = 1; p++;
    p->type = 0; p->flags = 0x92; p->getter = 104; p->putter = 104; p->offset = 104; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)AddScriptQueueEntryKind12; p->putter = 0; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)StartScriptColorFade; p->putter = 0; p++;
    p->type = 13; p->flags = 0x92; p->getter = 60; p->putter = 60; p->offset = 60; p++;
    p->type = 13; p->flags = 0x92; p->getter = 64; p->putter = 64; p->offset = 64; p++;
    p->type = 13; p->flags = 0x92; p->getter = 68; p->putter = 68; p->offset = 68; p++;
    p->type = 1; p->flags = 0x92; p->getter = 72; p->putter = 72; p->offset = 72; p++;
    p->type = 1; p->flags = 0x92; p->getter = 80; p->putter = 80; p->offset = 80; p++;
    p->type = 1; p->flags = 0x92; p->getter = 76; p->putter = 76; p->offset = 76; p++;
    p->type = 4188; p->flags = 0x92; p->getter = 88; p->putter = 88; p->offset = 88; p++;
    p->type = 8195; p->flags = 0x12; p->getter = 1544; p->putter = 1544; p++;
    p->type = 4190; p->flags = 0x22; p->getter = 1360; p->putter = (sptr)SetWorld5BossMode; p++;
    p->type = 0; p->flags = 0x20; p->putter = (sptr)PlayWorld5BossLoop; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)PlayScriptWorld5BossTarget; p->putter = 0; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptWorld5BossTarget; p->putter = 1; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1788; p->putter = 1788; p->offset = 1788; p++;
    p->type = 1; p->flags = 0x92; p->getter = 1792; p->putter = 1792; p->offset = 1792; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)PlaceScriptWorld5ModeColliderAtAnchor; p->putter = 0; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1368; p->putter = 1368; p->offset = 1368; p++;
    p->type = 4191; p->flags = 0xA2; p->getter = 1360; p->putter = (sptr)SetWorld5CountdownState; p->offset = 1360; p++;
    p->type = 5; p->flags = 0x122; p->getter = 3164; p->putter = (sptr)SetWorld3BossTempo; p->offset = (sptr)SetWorld3BossTempo; p++;
    p->type = 5; p->flags = 0x122; p->getter = 3168; p->putter = (sptr)SetWorld3BossSpanBeats; p->offset = (sptr)SetWorld3BossSpanBeats; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptWorld3BossPendingTimeline; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)EndScriptHeldWorld3Timeline; p->putter = 0; p++;
    p->type = 8339; p->flags = 0x2; p->getter = 3156; p++;
    p->type = 8307; p->flags = 0x12; p->getter = 3144; p->putter = 3144; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)AddScriptC13Entry; p->putter = 2; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)RemoveScriptWorld3BossEntry; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)DecrementScriptWorld3BossGauge; p->putter = 0; p++;
    p->type = 8307; p->flags = 0x12; p->getter = 1660; p->putter = 1660; p++;
    p->type = 8335; p->flags = 0x12; p->getter = 1576; p->putter = 1576; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)AppendScriptWorld3TimelineKind0Entry; p->putter = 3; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)AppendScriptWorld3TimelineKind1Entry; p->putter = 3; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)AppendScriptWorld3TimelineKind2Entry; p->putter = 2; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)AppendScriptWorld3TimelineKind3Entry; p->putter = 2; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)AppendScriptWorld3TimelineKind4Entry; p->putter = 2; p++;
    p->type = 18; p->flags = 0x401; p->getter = p->f10 = (sptr)AppendScriptWorld3TimelineKind5Entry; p->putter = 2; p++;
    p->type = 5; p->flags = 0x12; p->getter = 3088; p->putter = 3088; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SetScriptWorld4BossValues; p->putter = 3; p++;
    p->type = 0; p->flags = 0x12; p->getter = 3108; p->putter = 3108; p++;
    p->type = 4199; p->flags = 0x22; p->getter = 1552; p->putter = (sptr)SetHitCountColliderState; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)SendScriptHitCountColliderRequest; p->putter = 1; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1680; p->putter = 1680; p->offset = 1680; p++;
    p->type = 5; p->flags = 0x92; p->getter = 1684; p->putter = 1684; p->offset = 1684; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)AddScriptHitCountColliderId; p->putter = 1; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)AddScriptHitCountColliderItem; p->putter = 1; p++;
    p->type = 5; p->flags = 0x12; p->getter = 1360; p->putter = 1360; p++;
    p->type = 8311; p->flags = 0x12; p->getter = 1368; p->putter = 1368; p++;
    p->type = 18; p->flags = 0x1; p->getter = 0; p->f10 = (sptr)TakeScriptCountedColliderTouch; p->putter = 2;
}
