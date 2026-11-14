// SPDX-License-Identifier: AGPL-3.0-or-later
// A file of data only, the first of .rodata (0x217380 to 0x2215A0): the class descriptors
// (include/class_descriptor.h) and the method tables of the other objects, those of animation
// curves, attachments, paths, screen elements, cursor animators and effects. Each class's group
// sits with the other classes whose methods are in the same file, but the groups are not in the
// order of those files: the compiler puts all of a file's read-only data in its .rodata, so these
// were defined in a file of their own, linked before every file with code (its empty code range in
// config/us/files.tsv is where it sits in the link; docs/AGENT_WORKFLOW.md, "Finding and proving
// a file"). Named after what it holds.
#include "common.h"
#include "class_descriptor.h"
#include "anim_curve.h"
#include "attachment.h"
#include "path_curve.h"
#include "screen_element.h"
#include "cursor_animator.h"
struct TrackedNodeOffer;

// The types the method declarations below take, defined in the files of their methods.
struct Agent;
struct AgentDrawArgs;
struct AgentEvent;
struct AgentHit;
struct AgentNotification;
struct AgentRequest;
struct AgentValueNotice;
struct AimBlendGrid;
struct ArmedStateNotifier;
struct Attach03;
struct AttachedSet;
struct BlinkObject;
struct BoxCollider;
struct BufferedStream;
struct C17;
struct C24;
struct C35;
struct C37;
struct C52;
struct C71;
struct C80;
struct Camera;
struct CameraController;
struct CameraPlacement;
struct CameraPositionedObject;
struct ChildGroupObject;
struct ChildPoseSource;
struct Class75Object;
struct CodeChecksum;
struct Collider;
struct ColliderPose;
struct ColoredTriangleSet;
struct CompanionAgent;
struct ConeAgent;
struct ConeVolume;
struct Contact03;
struct ContactAgent;
struct ContactEnd03;
struct ContactEvent;
struct ContactEvent_0013D0B0;
struct ContactLimit03;
struct ContactListGlider;
struct ContactListObject;
struct ContactObject;
struct ContactPair;
struct ContactTracker;
union Contact_001A4538;
struct CountdownNotifier;
struct CountedCollider;
struct CountedNotice;
struct CountedObject;
struct CurrentPlacedObject;
struct CyclerEventMessage;
struct DeadlineNotifier;
struct DrawScale;
struct Effect;
struct EffectOwner;
struct EffectSpawner;
struct EntryQueue;
struct EntryTableObject;
struct Ev07;
struct FaceRef;
struct FlaggedObject;
struct FlaggedObjectSet;
struct FollowableObject;
struct FrameCameraController;
struct GatherTrigger;
struct GaugeCollider;
struct GaugeColliderAgent;
struct GaugeCountedObject;
struct GaugeManager;
struct HitCountCollider;
struct HitTarget;
struct HoldingMember;
struct IdFilterObject;
struct IdLinkedObject;
struct IdLookupObject;
struct ImpulseRow;
struct InteractFlags;
struct InteractTarget;
struct ItemKeeper;
struct LatchedSwitchCollider;
struct ListedAgentView;
struct ListedCollisionPart;
struct ListedKeepObject;
struct ListedPointObject;
struct LoadStream;
struct LookupObject;
struct MaskedCollider;
struct MassScalingCollider;
struct MemberGroup;
struct MemberObject;
struct MessageBody;
struct ModeWalker;
struct NumberedAgent;
struct NumberedItem;
struct ObjectCreator;
struct ObjectCycler;
struct ObjectEvent;
struct ObjectGatherer;
struct ObjectGroup;
struct ObjectMessage;
struct ObjectPool;
struct ObjectSet;
struct ObjectSubGroup;
struct OnOffCameraController;
struct OnOffObject;
struct Oscillator;
struct OwnerMessage;
struct Packet47;
struct PadStick;
struct PairController;
struct PairedObject;
struct ParentFrame;
struct PartHolderObject;
struct PathCurveObject;
struct PathFollower;
struct Player;
struct PlayerFlaggedCollider;
struct PlayerLinkedCollider;
struct PlayerNotification;
struct PointGraphObject;
struct PointObject;
struct PooledContact;
struct PooledHolder;
struct PooledObject;
struct Rec50;
struct RecordMember;
struct RedirectObject;
struct SaveNotifier;
struct ScaledOffsetObject;
struct ScaledTransform;
struct ScalingVolume;
struct SeekingAgent;
struct SequencedObject;
struct SoundNotifier;
struct SoundStateObject;
struct SourceNotice;
struct Src_13AD08;
struct StandIn;
struct StateGraph;
struct StateNotifier;
struct StateResetMsg;
struct StateResetObject;
struct StateTrigger;
struct StateWalkerGroup;
struct StateWalkerObject;
struct Stream8A;
struct Stream8E;
struct SwitchedCollider;
struct TargetCameraController;
struct TargetCurve;
struct TargetFollower;
struct TargetPoint;
struct TargetVector;
struct TempoNoticeRec;
struct TextPointObject;
struct TextureRenderObject;
struct TimeRangeNotifier;
struct TimedGroup;
struct TimedObject;
struct TimedStateObject;
struct TintBlendCollider;
struct TransformObject;
struct TransformSet;
struct TriggerZone;
struct TurningCollider;
struct ValueCameraController;
struct ValueListObject;
struct WalkerCollider;
struct Walker_001A4538;
struct World1Boss;
struct World2Boss;
struct World3BeatPressCollider;
struct World3Boss;
struct World3Timeline;
struct World4Boss;
struct World5Boss;
struct World5Countdown;
struct World5ModeCollider;
struct WorldListedAgent;
struct WorldListedObject;
struct ZeroPair;
struct ZoneCollider;

// D_00219600: an attachment's table, then the base tables of the four families of animation
// curves (anim_curve.h), in the order of their factories; nothing refers to those four.
struct AttachmentAndCurveBases {
    T2195_Vt attachment;        // 0x00
    PositionCurveVt position;   // 0x28
    RotationCurveVt rotation;   // 0x38
    ScaleCurveVt scale;         // 0x48
    WeightCurveVt weight;       // 0x58
};

// Defined in src/main/anim_record.cpp.
struct DrawnPart;

// The types of PathCurveVt's slots.
typedef void (*PathLoad)(PathCurve* self, void* stream);
typedef void (*PathM01)(PathCurve* self, s32 a1, s32 a2);
typedef void (*PathM02)(PathCurve* self, s32 a1, s32 a2);
typedef void (*PathM03)(PathCurve* self, s32 idx, void* a2, u8* a3, void* a4, s32 a5);
typedef void (*PathTransform)(PathCurve* self, void* a, void* b);
typedef f32 (*PathArcAt)(PathCurve* self, f32 t);
typedef f32 (*PathTimeAt)(PathCurve* self, f32 t);
typedef f32 (*PathLast)(PathCurve* self);
typedef f32 (*PathFill)(PathCurve* self);
typedef void (*PathM10)(PathCurve* self, void* a1, void* a2, void* a3, void* a4, f32* out0, f32* out1);
typedef void (*PathM11)(PathCurve* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6);

void ApplyObjectClassDefaults(BaseObject* self);
void EvaluateNoPositionCurve();
void GetNoPositionCurveTimes(PositionCurve* unused, s32* a, s32* b);
void EvaluateNoRotationCurve();
void GetNoRotationCurve();
void GetNoRotationCurveTimes(RotationCurve* self, s32* first, s32* second);
void EvaluateNoScaleCurve();
void GetNoScaleCurveTimes(ScaleCurve* a0, s32* a1, s32* a2);
void EvaluateNoWeightCurve();
void GetNoWeightCurveTimes(WeightCurve* unused, s32* a, s32* b);
void ReadTangentWeightCurve(TangentWeightCurve* self, Stream83* src);
void EvaluateTangentWeightCurve(TangentWeightCurve* self, s32 unused, s32 flags, f32* outF, f32* outI, f32 key, f32 scale);
void GetTangentWeightCurveTimes(TangentWeightCurve* src, s32* outCount, f32** outValues);
void ReadControlPointWeightCurve(ControlPointWeightCurve* self, Stream83* src);
void EvaluateControlPointWeightCurve(ControlPointWeightCurve* self, s32 unused, s32 flags, f32* outF, f32* outI, f32 key, f32 scale);
void GetControlPointWeightCurveTimes(ControlPointWeightCurve* self, s32* outCount, f32** outArr);
void EvaluateLinearWeightCurve(LinearWeightCurve* self, s32 unused, s32 flags, f32* outF, f32* outI, f32 key, f32 scale);
void ReadLinearWeightCurve(LinearWeightCurve* self, Stream83* src);
void GetLinearWeightCurveTimes(LinearWeightCurve* self, s32* count, f32** out);
void EvaluateAxisPositionCurve(AxisPositionCurve* self, PlacedObject* other, s32 c, f32* e, f32* f, f32 p12, f32 p13);
void ReadAxisPositionCurve(AxisPositionCurve* self, Stream83* arg);
void GetAxisPositionCurveTimes(AxisPositionCurve* self, s32* outCount, f32** outTimes);
void EvaluateVectorKeyPositionCurve(VectorKeyPositionCurve* self, PlacedObject* other, s32 a2, f32* a3, f32* a4, f32 p12, f32 p13);
void ReadVectorKeyPositionCurve(VectorKeyPositionCurve* self, Stream83* arg);
void GetVectorKeyPositionCurveTimes(VectorKeyPositionCurve* self, s32* outCount, f32** outArr);
void EvaluateAxisRotationCurve(AxisRotationCurve* self, PlacedObject* other, s32 c, void* p3, void* p4, f32 key, f32 scale);
void* GetAxisRotationCurve(AxisRotationCurve* self, PlacedObject* other, s32 flags, f32* values, f32* slopes, f32 key, f32 scale);
void ReadAxisRotationCurve(AxisRotationCurve* self, Stream83* arg);
void GetAxisRotationCurveKeyTimes(AxisRotationCurve* self, s32* outCount, f32** outTimes);
void EvaluateKeyedRotationCurve(KeyedRotationCurve* self, PlacedObject* parent, s32 mode, void* output, void* state, f32 key, f32 scale);
void GetKeyedRotationCurve(KeyedRotationCurve* self, PlacedObject* other, s32 flags, f32* values, f32* slopes, f32 key, f32 scale);
void ReadKeyedRotationCurve(KeyedRotationCurve* self, Stream83* arg);
void GetKeyedRotationCurveKeyTimes(KeyedRotationCurve* self, s32* outCount, f32** outTimes);
void EvaluateAxisScaleCurve(AxisScaleCurve* self, PlacedObject* second, s32 third, Mat3U* output, f32 factor);
void ReadAxisScaleCurve(AxisScaleCurve* self, Stream83* p);
void GetAxisScaleCurveKeyTimes(AxisScaleCurve* self, s32* outCount, f32** outTimes);
void EvaluateKeyedScaleCurve(KeyedScaleCurve* self, PlacedObject* unused, s32 mode, Mat3U* output, f32 factor);
void ReadKeyedScaleCurve(KeyedScaleCurve* self, Stream83* stream);
void GetKeyedScaleCurveKeyTimes(KeyedScaleCurve* self, s32* outCount, f32** outTimes);
void EvaluateBlendedPositionCurve(PositionCurveKind2* o, PlacedObject* cam, s32 c, Vec02* out0, Vec02* out1, f32 dt, f32 scale);
void EvaluateBlendedRotationCurve(RotationCurveKind2* o, PlacedObject* cam, s32 c, Mat02* out0, Vec02* out1, f32 dt, f32 scale);
void EvaluateAngleBlendCurve(AngleBlendWeightCurve* o, PlacedObject* cam, s32 c, f32* out0, f32* out1, f32 dt, f32 scale);
void EvaluateValueBlendCurve(ValueBlendWeightCurve* o, PlacedObject* cam, s32 c, f32* out0, f32* out1, f32 dt, f32 scale);
void CopyPoseSource(Attachment* self, Attachment* src);
void InitPoseSource(Attachment* self, PlacedObject* value);
void ReleasePoseSource(Attachment* self, s32 flags);
void GetOwnerPosition(Attachment* self, Vec02* out1, Vec02* out2);
void GetOwnerRotation(Attachment* self, Mat02* out1, Vec02* out2);
void GetOwnerValue(Attachment* self, f32* value, f32* slope);
void GetIdentityMatrix(Attachment* unused, Mat02* out);
f32 GetOwnerIndexedValue(Attachment* self, s32 index);
void GetPlacedObjectPositionAt(PlacedObject* self, f32 t, Vec02* pos, Vec02* vec);
void GetPlacedObjectRotationAt(PlacedObject* self, f32 t, Mat02* rot, Vec02* vec);
void InitSnapshotPoseSource(T2195_588* self, PlacedObject* src);
void GetSnapshotPosition(T2195_588* src, Vec02* d0, Vec02* d1);
void GetSnapshotRotation(T2195_588* src, Mat02* d0, Vec02* d1);
void GetSnapshotValue(T2195_588* self, f32* first, f32* second);
void GetSnapshotMatrix(T2195_588* self, Mat02* output);
f32 GetSnapshotIndexedValue(T2195_588* self, s32 i);
void InitLinkedPoseSource(T2195_5B0* self, PlacedObject* src);
void GetLinkedPosition(T2195_5B0* self, Vec02* first, Vec02* second);
void GetLinkedRotation(T2195_5B0* self, Mat02* d1, Vec02* d2);
void GetLinkedValue(T2195_5B0* self, f32* a, f32* b);
void GetLinkedMatrix(T2195_5B0* self, Mat02* dst);
f32 GetLinkedIndexedValue(T2195_5B0* self, s32 i);
void InitIdentityPoseSource(T2195_5D8* self, PlacedObject* owner);
void GetIdentityPosePosition(T2195_588* self, f32 t, Vec02* pos, Vec02* vec);
void GetIdentityPoseRotation(T2195_588* self, f32 t, Mat02* rot, Vec02* vec);
void GetNextPoseSourceValue(Attachment* self, f32* a1, f32* a2);
void GetIdentityPoseMatrix(T2195_588* self, Mat02* out);
f32 GetIdentityPoseIndexedValue();
void InitAimPoseSource(T2195_600* self, PlacedObject* a1);
void GetAimPoseRotation(T2195_600* self, Mat02* out, Vec02* vec);
void ReleaseTrackPoseSource(T2195_7C0* self, s32 a1);
void CopyTrackPoseSource(T2195_7C0* self, Attachment* a1);
void GetTrackPosition(T2195_7C0* self, Vec02* a1, Vec02* a2, f32 f);
void GetTrackRotation(T2195_7C0* self, Mat02* a1, Vec02* a2, f32 f);
void GetTrackValue(T2195_7C0* self, f32* a1, f32* a2);
void GetTrackScaleMatrix(T2195_7C0* self, Mat02* a1);
f32 GetTrackIndexedValue(T2195_7C0* self, s32 index);
void ReleaseCountedObject(CountedObject* object);
void InitStateTrigger(StateTrigger* self);
void StartStateTrigger(StateTrigger* self);
void CopyStateTrigger(StateTrigger* object, StateTrigger* src);
void UpdateStateTrigger(StateTrigger* self, f32 dt);
void InitPlacedObject(PlacedObject* self);
void AttachPlacedObject(PlacedObject* self);
void RegisterPlacedObject(PlacedObject* self);
void DetachPlacedObject(PlacedObject* self);
void UnregisterPlacedObject(PlacedObject* self);
void ReparentPlacedObject(PlacedObject* self, BaseObject* parent);
void ReframePlacedObject(PlacedObject* self, BaseObject* frame);
void PostLoadPlacedObject(PlacedObject* self);
void StartPlacedObject(PlacedObject* self);
void UpdatePlacedObject(PlacedObject* self, f32 f);
void RecomputePlacedObjectFrame(PlacedObject* self);
void ComputePlacedObjectWorldFrame(PlacedObject* self);
void BeginPlacedObjectMove(PlacedObject* self);
void MovePlacedObject(PlacedObject* self, s32 flag, f32 dt);
void ApplyPlacedObjectTransform(PlacedObject* self, Camera* cam, ScaledTransform* xf);
void DrawPlacedObject(PlacedObject* self, void* b, void* m);
void QueuePlacedObjectModelParts(PlacedObject* self, Camera* cam, Quad16* src);
void ClonePlacedObject(PlacedObject* self, PlacedObject* owner);
void CopyPlacedObject(PlacedObject* self, PlacedObject* src);
void HandlePlacedObjectNotification(PlacedObject* self, s32 mode, void* arg);
void SetPlacedObjectPosition(PlacedObject* self, Vec02* src);
void SetPlacedObjectRotation(PlacedObject* self, Mat02* src);
void SetPlacedObjectVelocity(PlacedObject* self, Vec02* src);
void SetPlacedObjectSpin(PlacedObject* self, Vec02* src);
void CopyPlacedObjectFrame(PlacedObject* self, PlacedObject* other);
void LoadPlacedObject(PlacedObject* self, void* r);
void ApplyObjectFrameOffsetToPose(PlacedObject* self, Mat02* m, Vec02* v);
void RemoveObjectFrameOffsetFromPose(PlacedObject* self, Mat02* m);
void ChooseActiveAttachments(PlacedObject* self);
s32 TestOtherFlagged(PlacedObject* self, BaseObject* a1);
void InitCodeChecksum(CodeChecksum* self);
void UpdateCodeChecksum(CodeChecksum* self, f32 dt);
void InitAnimation(Animation* self);
void LoadAnimation(Animation* self, Stream83* other);
void CopyAnimation(Animation* self, Animation* src);
void StartClampedKinematicValue(Animation* self);
void SkipAnimationPlayerLoad(AnimationPlayer* self, BufferedStream* stream);
void SkipAnimationPlayerStart();
void SkipAnimationPlayerCopy(AnimationPlayer* self, AnimationPlayer* src);
void InitIdFilterObject(IdFilterObject* self);
void CopyIdFilterObject(IdFilterObject* self, IdFilterObject* src);
void StartIdFilterObject(IdFilterObject* self);
void UpdateIdFilterObject(IdFilterObject* self, f32 dt);
s32 TestIdFilterMatch(IdFilterObject* self, Collider* key);
void HandleIdFilterObjectContact(IdFilterObject* self, u8* table, s32 which);
void InitTextPanel(T217D_440* self, s32 a1);
void SetupTextPanel(T217D_440* self);
void SetTextPanelMode(T217D_440* self, s32 value);
void UpdatePanelStick(T217D_440* self, PadRecord* p);
void SetTextPanelOpen(T217D_440* self, s32 on);
void ResetTextPanel(T217D_440* self);
void SetTextPanelText(T217D_440* self, const char* name);
f32 GetTextPanelSlideInTime(T217D_440* self);
f32 GetTextPanelSlideOutTime(T217D_440* s);
void DrawTextPanel(T217D_440* self);
void ChooseTextPanelState(T217D_440* self);
void EndTextPanelState(T217D_440* self);
void InitWorldListedObject(WorldListedObject* self);
void LeaveWorldLists(WorldListedObject* self);
void ReleaseWorldListedObject(WorldListedObject* self);
void UpdateWorldListedObject(WorldListedObject* self, f32 dt);
void CopyWorldListedObject(WorldListedObject* self, BaseObject* src);
void MoveWorldListedObject(WorldListedObject* self, f32 dt);
void SubmitWorldListedObjectBlock(WorldListedObject* owner, s32 unused, Src_13AD08* src);
void InitChildGroupObject(ChildGroupObject* self);
void LoadChildGroupObject(ChildGroupObject* self, BufferedStream* stream);
void CopyChildGroupObject(ChildGroupObject* self, ChildGroupObject* other);
void StartChildGroupObject(ChildGroupObject* self);
void HandleChildGroupNotification(ChildGroupObject* self, s32 kind, ObjectMessage* msg);
void UpdateChildGroupObject(ChildGroupObject* self, f32 dt);
void RunKeyedChildGroupEntry(ChildGroupObject* self, s32 key, s32 a2, s32 a3, s32 a4, void* arg5);
void HandleChildGroupObjectContact(ChildGroupObject* self, ContactPair* pair, s32 which);
s32 HandleChildGroupObjectEvent(ChildGroupObject* self, ObjectEvent* ev);
void InitMaskedCollider(MaskedCollider* self);
void LoadMaskedCollider(MaskedCollider* self, BufferedStream* stream);
void CopyMaskedCollider(MaskedCollider* self, MaskedCollider* other);
void StartMaskedCollider(MaskedCollider* self);
void UpdateMaskedCollider(MaskedCollider* self, f32 dt);
s32 HandleMaskedColliderEvent(MaskedCollider* self, ContactEvent_0013D0B0* ev);
void HandleMaskedColliderActivation(MaskedCollider* self);
void UpdateTimedState(TimedStateObject* self, f32 dt);
void HandleTimedStateNotification(TimedStateObject* self, s32 kind, ObjectMessage* msg);
s32 TestTimedStateContact(TimedStateObject* node, Collider* src);
void InitPlayerFlaggedCollider(PlayerFlaggedCollider* self);
void InitMassScalingCollider(MassScalingCollider* self);
void LatchContactObject(MassScalingCollider* self, u8* table, s32 index);
void LatchAcceptedSwitchedCollider(LatchedSwitchCollider* self, u8* table, s32 index);
void UpdateLatchedSwitchCollider(LatchedSwitchCollider* self, f32 dt);
void InitTriggerZone(TriggerZone* self);
void LoadTriggerZone(TriggerZone* self, BufferedStream* stream);
void StartTriggerZone(TriggerZone* self);
void CopyTriggerZone(TriggerZone* self, TriggerZone* src);
void StepTriggerZone(TriggerZone* self, f32 t);
void ReleaseTriggerZoneContacts(TriggerZone* self);
void UpdateTriggerZone(TriggerZone* self, f32 dt);
s32 HandleTriggerZoneEvent(TriggerZone* a0, void* a1);
void InitZoneCollider(ZoneCollider* self);
void LoadZoneCollider(ZoneCollider* self, BufferedStream* stream);
void StartZoneCollider(ZoneCollider* self);
void CopyZoneCollider(ZoneCollider* self, ZoneCollider* src);
void UpdateZoneCollider(ZoneCollider* self, f32 dt);
void ReadObjectTransformAndTables(void* a0, void* a1);
void InitFlaggedObject(FlaggedObject* self);
void CollectChildLists(FlaggedObject* self, BufferedStream* stream);
void ResolveListIds(FlaggedObject* self);
void StartFlaggedObject(FlaggedObject* self);
void CopyFlaggedObject(FlaggedObject* self, FlaggedObject* src);
void UpdateFlaggedObject(FlaggedObject* self, f32 dt);
s32 HandleFlaggedObjectEvent(FlaggedObject* self, ObjectEvent* ev);
void InitCamera(Camera* self);
void InitScaledOffsetObject(ScaledOffsetObject* self);
void LoadScaledOffsetObject(ScaledOffsetObject* self, void* p);
void StartScaledOffsetObject(ScaledOffsetObject* self);
void ResolveScaledOffsetContact(ScaledOffsetObject* self, Contact03* c, s32 end);
void InitStateNotifier(StateNotifier* self);
void LoadStateNotifier(StateNotifier* self, void* arg);
void CopyStateNotifier(StateNotifier* self, void* arg);
void StartStateNotifier(StateNotifier* self);
void MoveStateNotifier(StateNotifier* self, f32 dt, s32 quiet);
s32 HandleStateNotifierContact(StateNotifier* self, ContactObject* b);
void UpdateStateNotifier(StateNotifier* self, f32 dt);
void ApplyStateNotifierScale(StateNotifier* self, void* a, void* m);
void SetStateNotifierState(Camera* self, s32 state);
void InitTimeRangeNotifier(TimeRangeNotifier* self);
void HandleTimeRangeNotifierNotification(TimeRangeNotifier* self, s32 kind, void* target);
void UpdateTimeRangeNotifier(TimeRangeNotifier* self, f32 dt);
void SetEffectNotifierState(TimeRangeNotifier* self, s32 mode);
void InitSoundNotifier(SoundNotifier* self);
void SetSoundNotifierState(SoundNotifier* self, s32 mode);
void InitSaveNotifier(SaveNotifier* self);
void SetSaveNotifierState(SaveNotifier* self, s32 mode);
void InitDeadlineNotifier(DeadlineNotifier* self);
void StartDeadlineNotifier(DeadlineNotifier* self);
void HandleDeadlineNotifierNotification(DeadlineNotifier* self, s32 kind, void* msg);
void UpdateNotifierWorldDeadline(DeadlineNotifier* self, f32 dt);
void SetDeadlineNotifierState(DeadlineNotifier* self, s32 mode);
void InitCountdownNotifier(CountdownNotifier* self);
void HandleCountdownNotifierNotification(CountdownNotifier* self, s32 kind, void* msg);
void CountDownNotifierTimer(CountdownNotifier* self, f32 dt);
void SetCountdownNotifierState(CountdownNotifier* self, s32 mode);
void InitArmedStateNotifier(ArmedStateNotifier* self);
void UpdateArmedNotifier(ArmedStateNotifier* self, f32 dt);
void UpdateIdleCameraController(CameraController* self, u8* eye, u8* tail, f32 dt);
void ActivateTargetCameraController(TargetCameraController* self);
void UpdateTargetCameraController(TargetCameraController* self, u8* eye0, PadRecord* pad, f32 dt);
void DeactivateTargetCameraController(TargetCameraController* self);
void ActivateFrameCameraController(FrameCameraController* self);
void UpdateFrameCameraController(FrameCameraController* self, f32 dt);
void ActivateValueCameraController(ValueCameraController* obj, s32 value);
void DeactivateValueCameraController(ValueCameraController* obj);
void UpdateValueCameraController(ValueCameraController* ctl);
void InitItemColumn(T217D_720* self);
void SetupItemColumn(T217D_720* self);
void UpdateItemColumn(T217D_720* self, f32* clock);
void UpdateItemColumnSlide(T217D_720* self);
void DrawItemColumn(T217D_720* self);
void RegisterWorldListedAgent(WorldListedAgent* self);
void UnregisterWorldListedAgent(WorldListedAgent* self);
void CopyWorldListedAgent(WorldListedAgent* self, void* other);
void InitNumberedAgent(NumberedAgent* self);
void StartNumberedAgent(NumberedAgent* self);
void UpdateNumberedAgentGoal(NumberedAgent* self, s32 flag);
s32 IsNumberedAgentFree(NumberedAgent* self);
s32 HandleNumberedAgentObjectEvent(NumberedAgent* self, void* event);
void EnterNumberedAgentState(NumberedAgent* self, s32 evt, Animation* arg);
s32 ChooseAgentStateByContact(ContactAgent* self);
s32 IsContactAgentFree(ContactAgent* self);
s32 HandleContactAgentObjectEvent(ContactAgent* self, ListedAgentView** slot);
void EnterContactAgentState(ContactAgent* self, s32 evt, Animation* arg);
void InitGaugeManager(GaugeManager* self);
void BlendParamSets(GaugeManager* self);
void UpdateGaugeManager(GaugeManager* self, f32 dt);
void ShowGaugeManagerDisplays(GaugeManager* self);
void HandleGaugeManagerNotification(GaugeManager* self, s32 kind, void* key);
f32 GetBaseCurveLengthAtTime();
f32 GetBaseCurveTimeAtLength();
f32 GetPathCurveEndTime(PathCurve* obj);
f32 GetPathCurveEndLength(PathCurve* obj);
void ReadPathCurve(PathCurve* self, void* src);
void SamplePathCurveAtTime(PathCurve* self, f32 t, Vec02* pos, Vec02* tan);
void SamplePathCurveAtLength(PathCurve* self, f32 t, Vec02* pos, Vec02* tan);
void DrawPathCurveSegment(PathCurve* self, s32 idx, void* a2, u8* a3, void* a4, s32 a5);
void TransformPathCurvePoints(PathCurve* self,void* a,void* b);
f32 GetPathCurveLengthAtTime(PathCurve* self, f32 t0);
f32 GetPathCurveTimeAtLength(PathCurve* self, f32 t0);
f32 FillPathCurveLengths(PathCurve* self);
void FindPathCurveNearestPoint(PathCurve* self, void* a1, void* a2, void* a3, void* a4, f32* out0, f32* out1);
void ProjectOntoPathCurveNearTime(PathCurve* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6);
void ProjectOntoPathCurveNearLength(PathCurve* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6);
void ReadSplinePathCurve(SplinePathCurve* self, void* src);
void SampleSplinePathAtTime(SplinePathCurve* self, f32 t, void* a1, Vec02* a2);
void SampleSplinePathAtLength(SplinePathCurve* self, s32 a1, void* a2);
void DrawSplinePathSegment(SplinePathCurve* self, s32 idx, Quad16* m, u8* a3, void* a4);
void TransformSplinePathPoints(SplinePathCurve* self, void* a, void* b);
f32 GetSplineLengthAtTime(SplinePathCurve* self, f32 t0);
f32 GetSplineTimeAtLength(SplinePathCurve* self, f32 t0);
void FillSplinePathLengths(SplinePathCurve* self);
void FindSplinePathNearestPoint(SplinePathCurve* self, Vec02* pos, void* anchor, s32 a3, s32 a4, f32* a5, f32* a6);
void FindSplinePathNearestTime(SplinePathCurve* self, s32 a1, s32 a2, s32 a3, s32 a4, f32* a5, f32* a6, f32 f12);
void ProjectOntoSplinePathNearLength(SplinePathCurve* self, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6);
void InitPooledObject(PooledObject* self);
void RemoveFromWorldQueue(PooledObject* self);
void AddToWorldQueue(PooledObject* self);
void CopyPooledObject(PooledObject* self, Collider* other);
void LoadPooledObject(PooledObject* self, BufferedStream* stream);
void HandlePooledObjectNotification(PooledObject* self, s32 kind, void* msg);
void StartPooledObject(PooledObject* self);
void UpdatePooledObject(PooledObject* self, f32 f);
void InitPooledHolder(PooledHolder* self);
void HandlePooledHolderNotification(PooledHolder* self, s32 kind, void* msg);
void PostLoadPooledHolder(PooledHolder* self);
void StartPooledHolder(PooledHolder* self);
void UpdatePooledHolder(PooledHolder* self, f32 dt);
s32 TestPooledHolderMayContact(PooledHolder* self, Collider* obj);
void ReleasePooledHolder(PooledHolder* self);
void InitStepSequence(StepSequence* state);
void LoadStepSequence(StepSequence* self, BufferedStream* arg);
void StartStepSequence(StepSequence* self);
void UpdateStepSequence(StepSequence* self, f32 dt);
void HandleStepSequenceNotification(StepSequence* state, s32 mode, void* value);
void InitTextureRenderObject(TextureRenderObject* self);
void QueuePlacedObjectDraw(TextureRenderObject* self, s32 unused, void* a2);
void InitEffectSpawner(EffectSpawner* self);
void LoadEffectSpawner(EffectSpawner* self, BufferedStream* stream);
void CopyEffectSpawner(EffectSpawner* self, EffectSpawner* src);
void ResolveEffectSpawnerLinks(EffectSpawner* self);
void StartEffectSpawner(EffectSpawner* self);
void ReleaseEffectSpawnerHeld(EffectSpawner* self, s32 mode, BaseObject* p);
void UpdateEffectSpawner(EffectSpawner* self, f32 dt);
void StartMemberObject(MemberObject* self);
void SendMemberObjectMessage();
void LoadGroupMembers(MemberGroup* self, void* src);
void CopyGroupMembers(MemberGroup* self, MemberGroup* src);
void ResolveGroupMembers(MemberGroup* self);
void BroadcastMessageToMembers(MemberGroup* self, void* message);
void InitRecordMember(RecordMember* self);
void LoadRecordMember(RecordMember* self, void* stream);
void CopyRecordMember(RecordMember* self, RecordMember* src);
void ResolveRecordMemberTargets(RecordMember* self);
void SendRecordMemberMessage();
void InitHoldingMember(HoldingMember* self);
void ResolveHoldingMemberTargets(HoldingMember* self);
void ReleaseHeldObject(HoldingMember* self, s32 kind, BaseObject* other);
void SendMessageAfterDelay(HoldingMember* self, void* message);
void LoadCrossfadeAnimator(CrossfadeAnimator* self, AnimatorParams* src);
void BindCrossfadeAnimator(CrossfadeAnimator* self);
void StepCrossfadeAnimator(CrossfadeAnimator* s, f32 dt);
AnimCursor* FindCrossfadeCursor(CrossfadeAnimator* self, const AnimRecord* key);
void InitScalingVolume(ScalingVolume* self);
void LoadScalingVolume(ScalingVolume* self,void* other);
void UpdateScalingVolume(ScalingVolume* self, f32 dt);
void DrawScalingVolume(ScalingVolume* self, void* arg1, void* arg2);
void InitObjectCycler(ObjectCycler* self);
void LoadObjectCycler(ObjectCycler* self, void* arg);
void CopyObjectCycler(ObjectCycler* self, ObjectCycler* src);
void SetObjectCyclerHandle(ObjectCycler* self, s32 flag);
void StartObjectCycler(ObjectCycler* self);
void StepObjectCycler(ObjectCycler* self, f32 dt);
void UpdateObjectCycler(ObjectCycler* self, f32 dt);
void DrawObjectCycler(ObjectCycler* self, void* a1, void* a2);
s32 HandleObjectCyclerObjectEvent(ObjectCycler* self, CyclerEventMessage* r);
void SetPlacedObjectFrozen(PlacedObject* self, s32 flag);
void SetColliderFrozen(Collider* self, s32 flag);
void ResolveLookupIds(IdLookupObject* self);
void UpdateLinkConstraint(PlacedObject* self);
void UpdateAttachmentFrames(PlacedObject* self, ParentFrame* par);
void InitConeAgent(ConeAgent* self);
void StartConeAgent(ConeAgent* self);
void DrawConeAgent(ConeAgent* self, void* arg1, void* arg2);
s32 IsConeAgentFree(ConeAgent* self);
void InitTargetCurve(TargetCurve* self);
void RegisterTargetCurve(TargetCurve* self);
void UnregisterTargetCurve(TargetCurve* self);
void PostLoadTargetCurve(TargetCurve* self);
void CopyTargetCurve(TargetCurve* self, TargetCurve* src);
void InitTargetPoint(TargetPoint* self);
void RegisterTargetPoint(TargetPoint* self);
void UnregisterTargetPoint(TargetPoint* self);
void PostLoadTargetPoint(TargetPoint* self);
void CopyTargetPoint(TargetPoint* self, TargetPoint* src);
void InitListedCollisionPart(ListedCollisionPart* self);
void LoadListedCollisionPart(ListedCollisionPart* self, BufferedStream* stream);
void AddToPartList(ListedCollisionPart* self);
void RemoveFromPartList(ListedCollisionPart* self);
void CopyKeepingListLink(ListedCollisionPart* self, ListedCollisionPart* src);
s32 TestListedCollisionPartMayContact(Collider* a0, Collider* a1);
void StepListedCollisionPart(ListedCollisionPart* self, f32 t);
void CallFlaggedParts(PartHolderObject* self);
void BecomeCurrentObject(CurrentPlacedObject* self);
void InitSelectionCaption(T217D_12E0* self);
void UpdateSelectionCaption(T217D_12E0* self);
void HandleSelectionCaptionInput(T217D_12E0* self, PadRecord* arg);
void SetSelectionCaptionOpen(T217D_12E0* self, s32 v);
void DrawSelectionCaption(T217D_12E0* self);
void InitGridSelector(T217D_1330* self);
void HandleGridSelectorInput(T217D_1330* ctx, PadRecord* o);
void SetGridSelectorOpen(T217D_1330* self, s32 flag);
void DrawGridSelector(T217D_1330* self);
void InitC76Object(void* a0);
void LoadC76Object(TransformObject* self, void* stream);
void DrawC35Collider(C35* self, void* arg1, void* arg2);
void DrawC52Object(C52* self, void* arg1, void* arg2);
void InitTargetFollower(TargetFollower* self);
void LoadTargetFollowerRecords(TargetFollower* self, BufferedStream* stream);
void ResolveTargetFollowerLinks(TargetFollower* self);
void StepTargetFollower(TargetFollower* self, f32 t);
void UpdateTargetFollower(TargetFollower* self, f32 dt);
void HandleTargetFollowerNotification(TargetFollower* self, s32 type, Packet47* packet);
void InitEntryTableObject(EntryTableObject* self);
void LoadEntryTable(EntryTableObject* self, BufferedStream* stream);
void StartEntryTableObject(EntryTableObject* self);
void InitFollowableObject(FollowableObject* self);
void ResolveFollowableObjectLinks(FollowableObject* self);
void HandleFollowableObjectNotification(FollowableObject* self, s32 kind, void* arg);
void InitPlayer(Player* self);
void LoadPlayer(Player* self, BufferedStream* stream);
void StartPlayer(Player* self);
void StepPlayer(Player* self, f32 t);
void ComputePlayerSlideRates(Player* self, Contact03* out);
void ClampPlayerContactLimit(Player* self, s32 flags, ContactLimit03* out);
void ReleasePlayerContacts(Player* self);
s32 IsPlayerGroundContact(Player* self, Contact03* e, s32 idx);
void ResolvePlayerContact(Player* self, Contact03* c, s32 idx);
void HandlePlayerNotification(Player* self, s32 kind, PlayerNotification* msg);
void BlendPlayerPose(Player* self, void* a, void* b);
void RecomputePlayerFrame(Player* self);
void DrawPlayer(Player* self, void* a, void* b);
void PrunePlayerContacts(Player* self);
void SavePlayerPreviousPosition(Player* self);
void SetPlayerBoundsPoints(Player* self);
void UpdatePlayerBounds(Player* self);
void CollidePlayerWithObject(Player* self, Collider* a1, s32 a2, void* a3, void* a4, void* a5);
s32 GetPlayerContactMode(Player* self);
void CapturePlayerPose(Player* self, ColliderPose* pose, f32 dt);
void SetPlayerTracked(Player* a, void* b);
void ControlPlayer(Player* self, PadRecord* pad, f32 dt);
void UpdatePlayer(Player* self, f32 dt);
s32 IsPlayerCameraFree(Player* self);
void StartPlayerEffect(Player* self, s32 mode, PlacedObject* other);
void GetPlayerInteractFlags(Player* self, InteractTarget* other, s32* out);
void ReceivePlayerNode(Player* self, InteractTarget* node);
void SetPlayerPosition(Player* self, Vec02* pos);
void RegisterPlayer(Player* self);
void InitWorld5ModeCollider(World5ModeCollider* self);
void StartWorld5ModeCollider(World5ModeCollider* self);
void StepWorld5ModeCollider(World5ModeCollider* self, f32 f);
void MoveWorld5ModeCollider(World5ModeCollider* self, f32 t, void* arg);
void UpdateWorld5ModeCollider(World5ModeCollider* self, f32 dt);
void ControlWorld5ModeCollider(World5ModeCollider* self, f32 dt, PadRecord* pad);
void FinishWorld5ModeCollider(World5ModeCollider* self);
void HandleWorld5ModeColliderActivation(World5ModeCollider* self, void* active);
void ApplyWorld5ModeColliderTint(World5ModeCollider* self, void* s, void* out);
s32 IsWorld5ModeColliderRequestBlocked(World5ModeCollider* self, s32 a1);
s32 AcceptWorld5ModeColliderRequest(World5ModeCollider* self, s32* arg);
void HandleWorld5ModeColliderNotification(World5ModeCollider* self, s32 kind, MessageBody* rec);
s32 HasWorld5ModeColliderAcceptedRequest(World5ModeCollider* self);
void InitWorld5Boss(World5Boss* self);
void StartWorld5Boss(World5Boss* self);
void UpdateWorld5Boss(World5Boss* self, f32 dt);
void ShowWorld5BossBar(World5Boss* self);
s32 HandleWorld5BossEvent(World5Boss* self, ObjectEvent* msg);
void InitWorld5Countdown(World5Countdown* self);
void StartWorld5Countdown(World5Countdown* self);
void UpdateWorld5Countdown(World5Countdown* self, f32 dt);
void UpdateWorld5CountdownVisibility(World5Countdown* self);
s32 HandleWorld5CountdownObjectEvent(World5Countdown* self, ObjectEvent* msg);
void InitEntryQueue(EntryQueue* self);
void RegisterPointObject(C80* self);
void UnregisterPointObject(C80* self);
void CopyPointObject(C80* self, C80* src);
void StartPointObject(C80* self);
void InitColoredTriangles(ColoredTriangleSet* self);
void LoadColoredTriangles(ColoredTriangleSet* self, Stream8E* rd);
void RegisterListedKeepObject(ListedKeepObject* self);
void UnregisterListedKeepObject(ListedKeepObject* self);
void CopyListedKeepObject(ListedKeepObject* self, ListedKeepObject* src);
void InitModeWalkerObject(ModeWalker* self);
void StartModeWalkerObject(ModeWalker* self);
void ControlModeWalker(ModeWalker* self, PadStick* pad, f32 dt);
void UpdateModeWalkerObject(ModeWalker* self, f32 dt);
void RecomputeModeWalker(ModeWalker* self);
void HandleModeWalkerActivation(ModeWalker* self, void* active);
void ApplyModeWalkerTint(ModeWalker* o, void* a, void* b);
void CaptureModeWalkerTarget(ModeWalker* self, void* outv);
s32 IsModeWalkerRequestBlocked(ModeWalker* self);
s32 HasModeWalkerAcceptedRequest(ModeWalker* p);
void FinishModeWalker(ModeWalker* self);
s32 AcceptModeWalkerRequest(ModeWalker* self, s32* arg);
void HandleModeWalkerNotification(ModeWalker* self, s32 code, MessageBody* rec);
void ExtractModeWalkerContacts(ModeWalker* self);
void DrawSpinningSpriteElement(T217D_BF0* self);
void InitC24Object(C24* self);
void StartC24Object(C24* self);
void UpdateC24Object(C24* self, f32 dt);
void MoveC24Object(C24* self, s32 a1, f32 dt);
void InitObject(BaseObject* self);
void StartObject(BaseObject* self);
void AddObjectToParentList(BaseObject* self);
void AttachObject(BaseObject* self);
void RegisterObject(BaseObject* self);
void RemoveObjectFromParentList(BaseObject* self);
void DetachObject(BaseObject* self);
void UnregisterObject(BaseObject* self);
void ReparentObject(BaseObject* self, BaseObject* parent);
void CloneObject(BaseObject* self, BaseObject* src);
void CopyObjectData(BaseObject* self, BaseObject* src);
void AddObjectCallback(BaseObject* self, void* fn, void* ctx);
void RemoveObjectCallback(BaseObject* self, void* fn, void* ctx);
void AddObjectListener(BaseObject* self, BaseObject* src);
void RemoveObjectListener(BaseObject* self, BaseObject* src);
void SendObjectNotification(BaseObject* self, s32 kind, void* arg);
void LoadObjectProperties(BaseObject* self, void* stream);
void InitConeVolume(ConeVolume* self);
void RefreshConeVolume(ConeVolume* self);
void RegisterConeVolume(ConeVolume* self);
void UnregisterConeVolume(ConeVolume* self);
void CopyConeVolume(ConeVolume* self, ConeVolume* other);
void InitAim(T2195_790* self, PlacedObject* owner);
void SwitchAimByTargetDistance(T2195_790* self);
void GetAimRotation(T2195_790* self, f32 dt, Mat02* rot, Vec02* vec);
void CollideColliderParts(Collider* self, Collider* other, s32 sweep, s32 a3, FaceRef* a4, FaceRef* a5, PooledContact** a6);
void InitWorld2Boss(World2Boss* self);
void LoadWorld2Boss(World2Boss* self, void* reader);
void StartWorld2Boss(World2Boss* self);
void DrawWorld2Boss(World2Boss* self, AgentDrawArgs* args, void* arg2);
s32 HasWorld2BossClearLine(World2Boss* self);
s32 IsWorld2BossFree(World2Boss* self);
void EnterWorld2BossState(World2Boss* self, s32 evt, Animation* arg);
s32 ChooseWorld2BossState(World2Boss* self);
void UpdateWorld2Boss(World2Boss* self, f32 dt);
void ShowWorld2BossBar(World2Boss* self);
void UpdateWorld2BossGoal(World2Boss* self, s32 flag);
void UpdateWorld2BossState(World2Boss* self);
void LeaveWorld2BossState(World2Boss* self, s32 mode);
void HandleWorld2BossNotification(World2Boss* self, s32 a1, MessageBody* key);
void InitContactListObject(ContactListObject* self);
void LoadContactListObject(ContactListObject* self, BufferedStream* stream);
void UnregisterContactListObject(ContactListObject* self);
void MoveContactListObject(ContactListObject* self, void* b, f32 x);
void LaunchContactListObject(ContactListObject* self, PlacedObject* a, Vec02* v);
void ApplyContactListAttachments(ContactListObject* self, void* in1, void* in2);
s32 TestContactListMayContact(ContactListObject* self, void* key);
void InitContactListObjectWithoutGravity(ContactListObject* self);
void LaunchContactListObjectWithoutGravity(ContactListGlider* self, PlacedObject* target, Vec02* offset);
void StepContactListObjectWithoutGravity(ContactListGlider* self, f32 dt);
void LaunchTimedContactListObject(ContactListGlider* self, PlacedObject* target, Vec02* offset);
void MoveTimedContactListObject(ContactListGlider* self, s32 hold, f32 dt);
void InitBoxCollider(BoxCollider* self);
void QueueModelPartDraws(PlacedObject* self, Camera* cam);
void InitSeekingAgent(SeekingAgent* self);
void StartSeekingAgent(SeekingAgent* self);
void EnterSeekingAgentState(SeekingAgent* self, s32 a1, s32 a2);
void LeaveSeekingAgentState(SeekingAgent* self, s32 mode);
void UpdateSeekingAgentGoal(SeekingAgent* self, s32 flag);
void UpdateSeekingAgentState(SeekingAgent* self);
s32 IsSeekingAgentRequestBlocked(SeekingAgent* self, s32 a1);
s32 AcceptSeekingAgentRequest(SeekingAgent* self, AgentRequest* arg);
s32 HandleSeekingAgentObjectEvent(SeekingAgent* self, AgentEvent* msg);
s32 HasAttachedSeekingTarget(SeekingAgent* self);
s32 IsSeekingAgentTargetInRange();
void StartSeekingAgentEffect(SeekingAgent* self, s32 flag, PlacedObject* extra);
s32 GetSeekingAgentStateKind(SeekingAgent* self);
void HandleSeekingAgentNotification(SeekingAgent* self, s32 code, SourceNotice* req);
void LoadPointGraph(PointGraphObject* o, Stream8A* in);
void InitTargetVector(TargetVector* self);
void RegisterTargetVector(TargetVector* self);
void UnregisterTargetVector(TargetVector* self);
void StartTargetVector(TargetVector* self);
void CopyTargetVector(TargetVector* self, TargetVector* src);
void LoadPointObject(PointObject* self, void* other);
void ReparentPointObject(PointObject* self, BaseObject* value);
s32 ConvertPointObjectPosition(PointObject* self, void* other);
void LoadTextPointObject(TextPointObject* self, void* other);
void InitSwitchedCollider(SwitchedCollider* self);
void CopySwitchedCollider(SwitchedCollider* self, SwitchedCollider* src);
void HandleSwitchedColliderNotification(SwitchedCollider* self, s32 kind, void* msg);
void HandleSwitchedColliderActivation(SwitchedCollider* self, void* activator);
void CaptureSwitchedColliderPose(SwitchedCollider* self, u8* out, f32 a);
s32 IsSwitchedColliderCameraFree();
s32 IsSwitchedColliderRequestBlocked(SwitchedCollider* self);
s32 AcceptSwitchedColliderRequest(SwitchedCollider* self);
s32 HasSwitchedColliderAcceptedRequest();
void StartSwitchedColliderEffect(SwitchedCollider* self, s32 mode, PlacedObject* other);
void SetSwitchedColliderMode();
void RegisterSwitchedCollider(SwitchedCollider* self);
void UnregisterSwitchedCollider(SwitchedCollider* self);
void GetSwitchedColliderInteractFlags(s32, s32, InteractFlags* out);
void ShowTypedTextCaptionBox(SwitchedCollider* self, u32 value);
void UpdateSwitchedCollider(SwitchedCollider* self, f32 dt);
void FinishSwitchedCollider(SwitchedCollider* self);
void* GetSwitchedColliderTarget(SwitchedCollider* p);
void InitPauseMenu(T217D_6D0* self);
void SetPauseMenuOpen(T217D_6D0* self, s32 mode);
void UpdatePauseMenu(T217D_6D0* self);
void SetPauseMenuMode(T217D_6D0* self, s32 v);
void ShowPauseMenu(T217D_6D0* self);
void HidePauseMenu(T217D_6D0* self);
void DrawPauseMenu(T217D_6D0* self);
void InitObjectGroup(ObjectGroup* self);
void LoadObjectGroup(ObjectGroup* self, LoadStream* rd);
void CopyObjectGroup(ObjectGroup* self, ObjectGroup* src);
void StartObjectGroup(ObjectGroup* self);
void InitGaugeCollider(GaugeCollider* self);
void LoadGaugeCollider(GaugeCollider* self, BufferedStream* stream);
void StartGaugeCollider(GaugeCollider* self);
void StepGaugeCollider(GaugeCollider* self, f32 dt);
void UpdateGaugeCollider(GaugeCollider* self, f32 dt);
void HandleGaugeColliderActivation(GaugeCollider* a, void* b);
void ControlGaugeCollider(GaugeCollider* self, PadRecord* pad, f32 dt);
void UpdateGaugeColliderVisibility(GaugeCollider* self);
void ComputeGaugeColliderContactValue(GaugeCollider* ctx, Contact03* out);
void ApplyGaugeColliderAttachedSetContact(GaugeCollider* self, AttachedSet* set, f32 dt);
void HandleGaugeColliderNotification(GaugeCollider* self, s32 kind, void* rec);
void StartGaugeColliderAgent(GaugeColliderAgent* self);
void StepGaugeColliderAgent(GaugeColliderAgent* self, f32 dt);
s32 ChooseGaugeColliderAgentState(GaugeColliderAgent* self);
void UpdateGaugeColliderAgentGoal(GaugeColliderAgent* self, s32 pick);
void LeaveGaugeColliderAgentState(GaugeColliderAgent* self, s32 arg);
void EnterGaugeColliderAgentState(GaugeColliderAgent* self, s32 evt, Animation* arg);
void UpdateGaugeColliderAgentState(GaugeColliderAgent* self);
void HandleGaugeColliderAgentNotification(GaugeColliderAgent* self, s32 code, AgentValueNotice* req);
void UpdateGaugeColliderAgent(GaugeColliderAgent* s1, f32 f);
u32 IsGaugeColliderAgentTargetInRange();
s32 IsGaugeColliderAgentNear(GaugeColliderAgent* self);
void StartGaugeCountedObject(GaugeCountedObject* self);
void InitObjectSet(ObjectSet* self);
void LoadObjectSet(ObjectSet* self, BufferedStream* stream);
void PostLoadObjectSet(ObjectSet* self);
void StartObjectSet(ObjectSet* self);
void UpdateObjectSet(ObjectSet* self, f32 dt);
void CollectObjectSet(ObjectSet* self);
void NotifyObjectSetTarget(ObjectSet* self);
s32 GetObjectSetActivationState(ObjectSet* self);
void HandleObjectSetNotification(ObjectSet* self, s32 msg, ObjectMessage* m);
s32 TestObjectSetMayContact(ObjectSet* unused, void* obj);
void LatchObjectSetContact(ObjectSet* self, Contact03* elems, s32 idx);
void InitFlaggedObjectSet(FlaggedObjectSet* self);
void CopyFlaggedObjectSet(FlaggedObjectSet* obj, FlaggedObjectSet* src);
s32 GetFlaggedObjectSetActivationState(FlaggedObjectSet* self);
void CollectFlaggedObjectSet(FlaggedObjectSet* self);
void LoadStateWalkerObject(StateWalkerObject* self, BufferedStream* stream);
void StartStateWalkerObject(StateWalkerObject* self);
void LoadStateWalkerGroup(StateWalkerGroup* self, BufferedStream* stream);
void StartStateWalkerGroup(StateWalkerGroup* self);
void InitNumberedItem(NumberedItem* obj);
void LoadNumberedItem(NumberedItem* self, BufferedStream* stream);
void CopyNumberedItem(NumberedItem* obj, NumberedItem* src);
void StartNumberedItem(NumberedItem* self);
void UpdateNumberedItem(NumberedItem* self, f32 dt);
void CollectNumberedItem(NumberedItem* self);
void ApplyNumberedItemPendingImpulse(NumberedItem* self, s32 moved);
s32 HandleNumberedItemObjectEvent(NumberedItem* self, ObjectEvent* a1);
void SpinNumberedItemTransform(NumberedItem* self, void* a1, void* a2);
void InitC17Collider(C17* self);
void StartC17Collider(C17* o);
void HandleC17ColliderActivation(C17* self, void* flag);
void ControlC17Collider(C17* self, PadRecord* pad, f32 dt);
void HandleC17ColliderNotification(C17* self, s32 msg, s32* rec);
void InitC71Object(C71* self);
void RegisterC71Object(C71* obj);
void UnregisterC71Object(C71* obj);
void StartC71Object(C71* obj);
void CopyC71Object(C71* self, C71* src);
void InitObjectGatherer(ObjectGatherer* self);
void LoadObjectGatherer(ObjectGatherer* self, BufferedStream* stream);
void StartObjectGatherer(ObjectGatherer* self);
void AddObjectGatherer(ObjectGatherer* obj);
void RemoveObjectGatherer(ObjectGatherer* obj);
void CopyObjectGatherer(ObjectGatherer* self, ObjectGatherer* src);
void StepObjectGatherer(ObjectGatherer* self, f32 dt);
void UpdateObjectGatherer(ObjectGatherer* self, f32 dt);
void ComputeObjectGathererContactValues();
void ResolveObjectGathererContact();
void ApplyObjectGathererLodObject(ObjectGatherer* self, void* a1, void* a2);
s32 HandleObjectGathererObjectEvent(ObjectGatherer* self, GatherTrigger* src);
void RegisterC7CObject(BaseObject* obj);
void UnregisterC7CObject(BaseObject* obj);
void InitAimBlendGrid(AimBlendGrid* obj);
void LoadAimBlendGrid(AimBlendGrid* o, LoadStream* in);
void StartAimBlendGrid(AimBlendGrid* self);
void InitEffectOwner(EffectOwner* self);
void ReleaseEffectOwner(EffectOwner* self);
void MoveEffectsAndBounds(EffectOwner* self, f32 dt);
void KeepEffectOwnerBounds();
void UpdateEffectOwner(EffectOwner* self, f32 t);
void DrawEffects(EffectOwner* self, void* arg, void* arg2);
void InitEffect(Effect* self, void* pos, f32 scale, s32 flags);
void EndEffect(Effect* value, s32 enabled);
s32 HandleEffectContact(Effect* self, void* b, void* c, void* d);
void MoveEffect(Effect* self, f32 dt);
void UpdateEffect(Effect* self, f32 dt);
void DrawEffect(Effect* self, void* a1);
void InitFallingEffect(Effect* self, void* pos, f32 scale, s32 flags);
void EndEffectWithImpact(Effect* self, s32 flag);
void InitRisingEffect(Effect* self, void* pos, f32 scale, s32 flags);
void MoveDriftingEffect(Effect* self, f32 dt);
void EndEffectWithImpactOnExit(Effect* value, u32 enabled);
void InitImpactEffect(Effect* self, void* pos, f32 limit, s32 flags);
void InitGrowingEffect(Effect* self, void* pos, f32 scale, s32 flags);
void InitShrinkingFallEffect(Effect* self, void* pos, f32 scale, s32 flags);
void InitDroppingEffect(Effect* self, void* pos, f32 scale, s32 flags);
void UpdateDroppingEffect(Effect* self, f32 dt);
void DrawDroppingEffect(Effect* self, void* a1);
void EndDroppingEffect(Effect* self, void* other);
void InitStreakEffect(Effect* self, void* pos, f32 scale, s32 flags);
void DrawStreakEffect(Effect* self, void* a1);
void InitScaledEffect(Effect* self, void* pos, f32 scale, s32 flags);
void InitTrailSegment(Effect* self, void* pos, f32 scale, s32 flags);
void DetachTrailSegment(Effect* self);
void MoveTrailSegment(Effect* self, f32 dt);
void DrawTrailSegment(Effect* self, Camera* cam);
void InitSpawningEffect(Effect* self, void* pos, f32 scale, s32 flags);
void SpawnFollowUpEffect(Effect* self, f32 arg);
void InitFollowUpEffect(Effect* self, void* pos, f32 scale, s32 flags);
void InitWideTrailSegment(Effect* self, void* pos, f32 scale, s32 flags);
void InitShortFallingEffect(Effect* self, void* pos, f32 scale, s32 flags);
void InitCameraSpaceEffect(Effect* self, void* pos, f32 scale, s32 flags);
void MoveCameraSpaceEffect(Effect* self, f32 f);
void DrawCameraSpaceEffect(Effect* self, Camera* cam);
void RunEffectEndCallback(Effect* self);
void InitEmitterEffect(Effect* self, void* pos, f32 scale, s32 flags);
void MoveEmitterEffect(Effect* self, f32 dt);
void UpdateEmitterEffect(Effect* self, f32 dt);
void DrawEmitterEffect(Effect* self, void* a1);
void InitLongStreakEffect(Effect* self, void* pos, f32 scale, s32 flags);
void InitPhasedEffect(Effect* self, void* pos, f32 scale, s32 flags);
void KeepPhasedEffectStill(Effect* self);
void AdvanceEffectPhases(Effect* c, f32 dt);
void DrawPhasedEffect(Effect* self, Camera* cam);
void CopyEffectSourceIds(Effect* self, Rec50* src);
void DrawProjectileEffect(Effect* self, void* a1);
s32 HandleEffectImpact(Effect* self, PlacedObject* other, void* a2, void* a3);
void UpdateEffectUntilDetached(Effect* self, f32 dt);
void DrawHitMarkEffect(Effect* self, void* a1);
void SetRandomEffectSpin(Effect* self);
void MoveTumblingEffect(Effect* self, f32 dt);
s32 HandleTumblingEffectImpact(Effect* self, void* a1, void* a2, void* a3);
void AimEffectAtNearestObject(Effect* self, Rec50* src);
void PlaceEffectAtSource(Effect* dst, void* a1);
void DrawStreakedEffect(Effect* self, void* a1);
s32 HandleStreakedEffectImpact(Effect* self, void* hold, Vec02* where, Vec02* dir);
void RandomizeEffectSpin(Effect* self, Rec50* src);
s32 HandleEffectContactUnlessKind6(Effect* a0, PlacedObject* a1, void* a2, void* a3);
void DrawSpinningEffect(Effect* self, void* a1);
void InitFacingEffect(Effect* self, void* pos, f32 scale, s32 flags);
void DrawFacingEffect(Effect* self, Camera* cam);
void InitDelayedEffect(Effect* self, void* pos, f32 scale, s32 flags);
void MoveDelayedEffect(Effect* self, f32 f);
void UpdateDelayedEffect(Effect* self);
void DrawDelayedEffect(Effect* self, void* a1);
void ResolveEffectTarget(Effect* self, void* otherv);
void SendEffectMessagesAtRate(Effect* self, f32 scale);
void InitWalkerCollider(WalkerCollider* self);
void LoadWalkerCollider(WalkerCollider* self, BufferedStream* stream);
void StartWalkerCollider(WalkerCollider* self);
void ControlWalkerCollider(WalkerCollider* self, PadRecord* src, f32 dt);
void UpdateWalkerCollider(WalkerCollider* self, f32 dt);
void HandleWalkerColliderNotification(WalkerCollider* self, s32 code, MessageBody* rec);
void StepWalkerCollider(WalkerCollider* self, f32 dt);
void ResolveWalkerColliderContact(Walker_001A4538* self, Contact_001A4538* c, s32 i);
void ComputeWalkerColliderContactValue(WalkerCollider* ctx, Contact03* obj);
void ComputeWalkerColliderImpulseResponse(WalkerCollider* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
s32 IsWalkerColliderCameraFree();
void InitPairController(PairController* self);
void ResolvePairControllerLinks(PairController* self);
void BlendPairControllerPose(PairController* self);
void UpdatePairController(PairController* self, f32 dt);
void ShowPairControllerElement(PairController* self);
void InitPairedObject(PairedObject* self);
void LoadPairedObject(PairedObject* self, BufferedStream* stream);
void CopyPairedObject(PairedObject* self, PairedObject* src);
void StartPairedObject(PairedObject* self);
void UpdatePairedObject(PairedObject* self, f32 dt);
s32 HandlePairedHit(PairedObject* o, ObjectEvent* ev);
void InitHitTarget(HitTarget* self);
void LoadHitTarget(HitTarget* self, BufferedStream* stream);
void CopyHitTarget(HitTarget* self, HitTarget* src);
void StartHitTarget(HitTarget* self);
void UpdateHitTarget(HitTarget* self, f32 dt);
void StepHitTarget(HitTarget* self, f32 dt);
void ComputeHitTargetContactValue(HitTarget* self, Contact03* obj);
s32 ApplyHitTargetHit(HitTarget* self, ObjectEvent* ev);
void InitSoundStateObject(SoundStateObject* self);
void LoadSoundStateObject(SoundStateObject* self, BufferedStream* stream);
void CopySoundStateObject(SoundStateObject* self, SoundStateObject* src);
void StartSoundStateObject(SoundStateObject* self);
void UpdateSoundStateObject(SoundStateObject* self, f32 dt);
void InitObjectCreator(ObjectCreator* self);
void LoadObjectCreator(ObjectCreator* self, BufferedStream* stream);
void StartObjectCreator(ObjectCreator* self);
void UpdateObjectCreator(ObjectCreator* self, f32 dt);
void InitObjectPool(ObjectPool* self);
void UnregisterObjectPool(ObjectPool* self);
void CopyObjectPool(ObjectPool* self, ObjectPool* other);
void StartObjectPool(ObjectPool* self);
void ClearObjectPoolChoiceIfFlag(ObjectPool* self, s32 flag);
void StartWorld4Boss(World4Boss* self);
s32 IsWorld4BossFree(World4Boss* self);
void UpdateWorld4BossGoal(World4Boss* self, s32 flag);
void UpdateWorld4BossState(World4Boss* self);
void EnterWorld4BossState(World4Boss* self, s32 evt, Animation* arg);
void UpdateWorld4Boss(World4Boss* self, f32 dt);
void UpdateWorld4BossVisibility();
s32 HandleWorld4BossObjectEvent(World4Boss* self, ObjectEvent* ev);
void InitScreenElement(ScreenElement* self, s32 index);
void SetupScreenElementText(ScreenElement* self);
void UpdateScreenElementSlide(ScreenElement* self);
void SetScreenElementText(ScreenElement* self, const char* arg);
void DrawScreenElementText(ScreenElement* self);
void ResetScreenElement(ScreenElement* self);
void ShowScreenElement(ScreenElement* self);
void HideScreenElement(ScreenElement* self);
void SetScreenElementMode(ScreenElement* self, s32 mode);
void SetScreenElementClock(ScreenElement* self, f32* p);
void InitCounterCaption(T217D_E30* self);
void UpdateCounterCaption(T217D_E30* self);
void DrawCounterCaption(T217D_E30* self);
f32 GetCaptionHoldTime(void);
void InitTimerElement(T217D_510* self);
void UpdateTimerElement(T217D_510* self);
void DrawTimerElement(T217D_510* self);
f32 GetPairCaptionHoldTime(void);
f32 GetGaugeAmountCaptionHoldTime(void);
f32 GetGaugeColliderCaptionHoldTime(void);
void InitGauge(T217D_2E0* self);
void DrawGauge(T217D_2E0* self);
void InitFramedElement(T217D_330* self);
void SetCaptionTextAndSize(T217D_330* self, const char* p);
void DrawElementWithFadedFrame(T217D_330* self);
void InitPointerTextCaption(T217D_380* self);
void SetElementTextAfterSlideOut(T217D_380* self, const char* v);
void SetElementModeApplyingPendingText(T217D_380* self, s32 v);
s32 AreElementsTogetherOrPending(T217D_380* self, ScreenElement* other);
void ShowElementUnlessTextPending(T217D_380* self);
void HideElementOrDropPendingText(T217D_380* self);
void DrawSlidingGlyphElement(T217D_380* self);
void InitCopiedTextCaption(T217D_3D0* self);
void SetElementTextCopiedAfterSlideOut(T217D_3D0* self, const char* v);
void SetElementModeApplyingCopiedText(T217D_3D0* self, s32 flag);
void ShowElementUnlessCopiedTextPending(T217D_3D0* self);
void HideElementOrDropCopiedText(T217D_3D0* self);
void DrawMessageElement(T217D_3D0* self);
void InitHintGlyphElement(T217D_420* self);
void UpdateHintGlyphElement(T217D_420* self);
void DrawHintGlyphElement(T217D_420* self);
void InitLetterboxElement(T217D_560* self);
void SetElementModeFollowingFade(T217D_560* self, s32 newval);
void DrawLetterboxElement(T217D_560* self);
void InitTitleElement(T217D_470* self);
void DrawTitleElement(T217D_470* self);
void InitPromptElement(T217D_4C0* self);
void SetElementModeRebuildingText(T217D_4C0* self, s32 force);
void UpdatePromptElement(T217D_4C0* self);
void DrawPromptElement(T217D_4C0* self);
void InitLetterGlyphElement(T217D_5B0* self);
void DrawLetterGlyphElement(ScreenElement* self);
void InitCyclingGlyphElement(T217D_600* self);
void SetElementModeClearingFlag(T217D_600* self, s32 flag);
void InitTimedObject(TimedObject* a0);
void SetTimedObjectTarget(TimedObject* self, s32 value);
void EnterTimedObjectState(TimedObject* self, s32 state);
void UpdateTimedObject(TimedObject* self, f32 dt);
void InitTimedGroup(TimedGroup* self);
void LoadTimedGroup(TimedGroup* self, BufferedStream* stream);
void PostLoadTimedGroup(TimedGroup* self);
void CloneTimedGroupEntries(TimedGroup* self);
void UpdateTimedGroup(TimedGroup* self, f32 amount);
void SetStaggeredColliderFrozen(TimedGroup* self, s32 p);
void DrawTimedGroup(TimedGroup* self, void* a1, void* a2);
void ChooseTimedGroupState(TimedGroup* self, s32* state);
void SetTimedGroupMode(TimedGroup* self, s32 flag);
void RequestTimedGroupEnd(TimedGroup* self);
void FinishTimedGroup(TimedGroup* self);
void EnterTimedGroupState(TimedGroup* self, s32 s);
void InitSequencedObject(SequencedObject* o);
void SetupSequencedObject(SequencedObject* self);
void UpdateSequencedObject(SequencedObject* self, f32 dt);
void DrawSequencedObject(SequencedObject* self, void* a1, Quad16* a2);
s32 TestSequencedObjectMayContact();
void ChooseSequencedObjectState(TimedObject* self, s32* state);
void SetSequencedObjectMode(SequencedObject* self, s32 value);
void RequestSequencedObjectEnd(SequencedObject* self);
void FinishSequencedObject(SequencedObject* o);
void EnterSequencedObjectState(SequencedObject* self, s32 s);
void InitBlinkObject(BlinkObject* self);
void SetupBlinkObject(BlinkObject* self);
void UpdateBlinkObject(BlinkObject* self, f32 dt);
void ChooseBlinkObjectState(BlinkObject* self, s32* out);
void SetBlinkObjectMode(BlinkObject* self, s32 mode);
void RequestBlinkObjectEnd(BlinkObject* self);
void FinishBlinkObject(BlinkObject* self);
void EnterBlinkObjectState(BlinkObject* self, s32 n);
void LoadPathCurveObject(PathCurveObject* self, void* obj);
void ReparentPathCurveObject(PathCurveObject* self, BaseObject* other);
void LoadAnimatorBase(CursorAnimator* self, const AnimatorParams* src);
void BindAnimatorRecord(CursorAnimator* self);
f32 GetAnimatorZeroProgress(void);
AnimCursor* FindAnimatorCursor(CursorAnimator* self, const AnimRecord* key);
void LoadFrameRunAnimator(FrameRunAnimator* p, AnimatorParams* s);
void BindFrameRunAnimator(FrameRunAnimator* p);
void StepFrameRunAnimator(FrameRunAnimator* p, f32 dt);
f32 GetFrameRunProgress(FrameRunAnimator* p);
void LoadFramePingPongAnimator(FramePingPongAnimator* p, AnimatorParams* s);
void BindFramePingPongAnimator(FramePingPongAnimator* p);
void StepFramePingPongAnimator(FramePingPongAnimator* p, f32 dt);
f32 GetFramePingPongProgress(FramePingPongAnimator* p);
void LoadRandomJumpAnimator(RandomJumpAnimator* p, AnimatorParams* s);
void StepRandomJumpAnimator(RandomJumpAnimator* self, f32 x);
void LoadAngleFrameAnimator(AngleFrameAnimator* self, AnimatorParams* key);
void BindAngleFrameAnimator(AngleFrameAnimator* p);
void FollowObjectAngle(AngleFrameAnimator* p, void* unused, DrawnPart* q);
void LoadScrollAnimator(ScrollAnimator* p, AnimatorParams* s);
void StepScrollAnimator(ScrollAnimator* p, f32 t);
f32 GetScrollProgress(ScrollAnimator* p);
void LoadCircleAnimator(CircleAnimator* p, AnimatorParams* s);
void StepCircleAnimator(CircleAnimator* self);
f32 GetCircleProgress(CircleAnimator* p);
void LoadTriangleAnimator(TriangleAnimator* self, AnimatorParams* src);
void GetTriangleOutputs(TriangleAnimator* self, void** out);
void UpdateTriangleAnimatorCursor(TriangleAnimator* self, PlacedObject* obj, void** part);
void StartCameraPositionedObject(CameraPositionedObject* self);
void MoveObjectToCamera(CameraPositionedObject* self, f32 dt);
void LoadStateGraph(StateGraph* self, BufferedStream* s);
void StartStateGraph(StateGraph* self);
void InitCompanionAgent(CompanionAgent* self);
void StartCompanionAgent(CompanionAgent* self);
s32 IsCompanionAgentTargetReachable(CompanionAgent* self);
void UpdateCompanionAgent(CompanionAgent* self, f32 dt);
void EnterCompanionAgentState(CompanionAgent* self, s32 evt, Animation* arg);
s32 IsCompanionAgentTargetInRange(CompanionAgent* self);
s32 AnswerCompanionAgentRosterPoll(CompanionAgent* self);
void HandleCompanionAgentNotification(CompanionAgent* self, s32 code, void* req);
void SetCompanionAgentFrozen(CompanionAgent* self, s32 p);
void InitCollider(Collider* self);
void RegisterCollider(Collider* self);
void UnregisterCollider(Collider* self);
void ApplyColliderPendingMove(Collider* self, s32 quiet);
void ApplyColliderPendingImpulse(Collider* self, s32 moved);
void ApplyColliderPendingImpulseHalfStep(Collider* self, s32 flag);
void UpdateColliderBounds(Collider* self);
void ComputeColliderWorldFrame(Collider* self);
void RecomputeColliderFrame(Collider* self);
s32 TestCollidersMayContact(Collider* a, Collider* b);
void NotifyContactHandlers(Collider* self);
void AddContactVertexBlendVelocity(Collider* self, Contact03* c, s32 which);
void StepCollider(Collider* self, f32 t);
void DrawCollider(Collider* self, void* a, void* m);
void UpdateCollider(Collider* self, f32 dt);
void SaveColliderPreviousPosition(Collider* self);
void SetColliderPosition(Collider* self, Vec02* pos);
void SetColliderRotation(Collider* self, Mat02* src);
void SetColliderVelocity(Collider* self, Vec02* v);
void SetColliderSpin(Collider* self, Vec02* v);
void ReparentCollider(Collider* self, BaseObject* p);
void ReframeColliderAnchors(Collider* self, PlacedObject* frame);
void CaptureColliderPose(Collider* self, ColliderPose* out);
void CopyCollider(Collider* self, Collider* other);
void ApplyColliderAttachedSetContact(Collider* self, AttachedSet* other, f32 dt);
void IgnoreColliderAttachmentStep(Collider* self, Attach03* node, f32 dt);
void LoadCollider(Collider* self, BufferedStream* in);
void SendColliderNotification(Collider* self, s32 kind, void* arg);
s32 RequestColliderLaunch(Collider* self, void* source, TrackedNodeOffer* offer);
void MoveCollider(Collider* self, f32 x, void* b);
s32 HandleObjectEvent(Collider* self, ObjectEvent* shape);
void CopyColliderMeshesInFrame(Collider* self, Collider* src, s32 extra);
void NumberColliderParts(Collider* self, s32* index, Collider** list);
void ComputeColliderImpulseResponse(void* self, s32 a1, Contact03* c, s32 idx, ContactEnd03* hit, ImpulseRow* rows);
void AddParentVelocityToChildRows(void* unusedA, void* unusedB, s32 n, Collider** list, ImpulseRow* rows);
void InitIdLinkedObject(IdLinkedObject* self);
void StartIdLinkedObject(IdLinkedObject* self);
void InitListedPointObject(ListedPointObject* self);
void RegisterListedPointObject(ListedPointObject* self);
void UnregisterListedPointObject(ListedPointObject* self);
void CopyListedPointObject(ListedPointObject* self, ListedPointObject* src);
void InitHitCountCollider(HitCountCollider* self);
void StartHitCountCollider(HitCountCollider* self);
void UpdateHitCountCollider(HitCountCollider* self, f32 t);
void ShowHitCountColliderCounters();
void ControlHitCountCollider(HitCountCollider* self, void* ev, f32 dt);
void StepHitCountCollider(HitCountCollider* self, f32 dt);
void NoteHitCountColliderContact(HitCountCollider* self, Contact03* c, s32 end);
void ResolveHitCountColliderContact(HitCountCollider* self, Contact03* c, s32 end);
s32 IsHitCountColliderRequestBlocked(HitCountCollider* self);
s32 AcceptHitCountColliderRequest(HitCountCollider* self, OwnerMessage* arg);
s32 HasHitCountColliderAcceptedRequest(HitCountCollider* self);
void FinishHitCountCollider(HitCountCollider* self);
void InitTurningCollider(TurningCollider* self);
void StartTurningCollider(TurningCollider* self);
void DrawTurningCollider(TurningCollider* self, void* unused1, void* unused2);
void UpdateTurningCollider(TurningCollider* self, f32 dt);
s32 GetTurningColliderContactMode();
void ComputeTurningColliderImpulseResponse(TurningCollider* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
void SetTurningColliderRotation(TurningCollider* self, Mat02* rot);
void CopyTurningColliderMeshesInFrame(TurningCollider* self, Collider* other, s32 mode);
void StepTurningCollider(TurningCollider* self, f32 dt);
s32 IsTurningColliderGroundContact(TurningCollider* self, Contact03* a, s32 idx);
void ComputeTurningColliderContactValue(TurningCollider* self, Contact03* out);
void ClampTurningColliderContactLimit(TurningCollider* self, s32 flags, ContactLimit03* limit);
void BuildTurningColliderHeadingMatrix(TurningCollider* self);
void ResolveTurningColliderContact(TurningCollider* self, void* b, s32 c);
void RecomputeTurningColliderFrame(TurningCollider* self);
void CollectTurningColliderContacts(TurningCollider* self);
void CollideTurningColliderWithObject(TurningCollider* self, Collider* obj, void* unused2, void* unused3, void* filter, void* out);
void GetTurningColliderPose(TurningCollider* self, void* matrix, Vec02* out, f32 limit);
void SumChildPoseOffsets(ChildPoseSource* self, f32 t, Vec02* pos, Vec02* vec);
void CombineChildPoseRotations(ChildPoseSource* self, Mat02* outRot, Vec02* outVec, f32 t);
void InitAgent(Agent* self);
void LoadAgent(Agent* self, void* a1);
void CopyAgent(Agent* self, void* src);
void PostLoadAgent(Agent* self);
void StartAgent(Agent* self);
s32 TestAgentMayContact(Agent* self, Collider* obj);
void RegisterAgent(Agent* self);
void UnregisterAgent(Agent* self);
void StepAgent(Agent* self, f32 dt);
void UpdateAgent(Agent* self, f32 dt);
s32 ChooseAgentState(Agent* self);
void BuildAgentPath(Agent* self);
void UpdateAgentGoal(Agent* self, s32 flag);
void UpdateAgentState(Agent* self);
void LeaveAgentState(Agent* self, s32 mode);
void EnterAgentState(Agent* self, s32 evt, Animation* arg);
s32 HandleAgentObjectEvent(Agent* self, AgentHit* ev);
s32 AcceptAgentRequest(Agent* self, AgentRequest* req);
s32 IsAgentRequestBlocked(Agent* self, s32 unused1);
void SteerAgentAlongPath(Agent* self);
void RestartAgentClip(Agent* self);
void HandleAgentNotification(Agent* self, s32 kind, AgentNotification* msg);
s32 AnswerAgentRosterPoll();
s32 IsAgentTargetInRange(Agent* self);
void DrawAgent(Agent* self, void* unused1, void* unused2);
void* SelectAgentTarget(Agent* self);
void ComputeAgentContactValue(Agent* self, Contact03* out);
void ClampAgentContactLimit(Agent* self, s32 flags, ContactLimit03* out);
void CollideAgentWithObject(Agent* a0, Collider* a1, s32 a2, s32 a3, s32 a4, s32 a5);
s32 RequestAgentLaunch(Agent* self, void* source, TrackedNodeOffer* offer);
s32 IsAgentFree();
void InitItemKeeper(ItemKeeper* self);
void FindWantedItems(ItemKeeper* a0);
void SyncPlayerTarget(Player* self);
void GetPlayerPose(Player* self, f32 t, void* out, void* extra);
void StartCountedCollider(CountedCollider* self);
void UpdateCountedCollider(CountedCollider* self, f32 dt);
void StepCountedCollider(CountedCollider* self, f32 t);
void CollectCountedColliderContacts(CountedCollider* self);
void* HandleCountedColliderEvent(CountedCollider* a0, ContactEvent* a1);
void ComputeCountedColliderWorldFrame(CountedCollider* self);
void HandleCountedColliderNotification(CountedCollider* self, s32 kind, ObjectMessage* msg);
s32 AcceptPlayerRequest(Player* self, Ev07* msg);
s32 IsPlayerRequestBlocked(Player* self, s32 n);
s32 GetPlayerRequestPhase(Player* self);
void FinishPlayerRequest(Player* self);
void ApplyPlayerAttachedSetContact(Player* self, Collider* other, f32 t);
s32 TestStandInMayContact(StandIn* self, Collider* value);
void StepStandIn(StandIn* self, f32 t);
void StopStandIn(StandIn* self, ContactPair* pair, s32 kind);
void HandleStandInNotification(StandIn* self, s32 kind, ObjectMessage* ref);
void InitPathFollower(PathFollower* self);
void StartPathFollower(PathFollower* self);
void StepPathFollower(PathFollower* self, f32 dt);
void UpdatePathFollower(PathFollower* self, f32 t);
void ControlPathFollower(PathFollower* self, PadRecord* pad, f32 dt);
void UpdatePathFollowerScreenElements(PathFollower* self);
void ReleasePathFollowerContacts(PathFollower* self);
void CollidePathFollowerWithObject(PathFollower* self, Collider* other, s32 a2, void* a3, void* a4);
void ComputePathFollowerContactValue();
void UpdatePathFollowerAttachmentFrames(PathFollower* self, ParentFrame* parent);
void DrawPathFollower(PathFollower* self, void* a, DrawScale* b);
void UpdatePathFollowerBounds(PathFollower* self);
void StartPathFollowerEffect(PathFollower* self, s32 a, PlacedObject* b);
void RecomputePathFollowerFrame(PathFollower* self);
void CapturePathFollowerPose(PathFollower* self, ColliderPose* pose);
void HandlePathFollowerActivation(PathFollower* self, void* v);
void HandlePathFollowerNotification(PathFollower* self, s32 code, CountedNotice* rec);
void InitWorldPools(World* self);
void LoadWorld(World* self, BufferedStream* s);
void InitRedirectObject(RedirectObject* self);
void StartRedirectObject(RedirectObject* self);
void SimulateRedirectChain(RedirectObject* self);
void MarkRedirectToSelf(RedirectObject* self, PlacedObject* other);
void InitTintBlendCollider(TintBlendCollider* self);
void StartTintBlendCollider(TintBlendCollider* self);
void UpdateTintBlendCollider(TintBlendCollider* self, f32 dt);
void FinishTintBlendColliderRequest(TintBlendCollider* self);
void ControlTintBlendCollider(TintBlendCollider* self, f32 dt, PadRecord* pad);
void SetTintBlendColliderTracked(TintBlendCollider* self, void* p);
void ApplyTintBlendColliderTint(TintBlendCollider* self, void* a1, void* a2);
void ApplyTintBlendColliderPendingImpulse(TintBlendCollider* self, s32 moved);
s32 IsTintBlendColliderRequestBlocked(TintBlendCollider* self, s32 mode);
s32 AcceptTintBlendColliderRequest(TintBlendCollider* self, OwnerMessage* req);
void CollectTintBlendColliderContacts(TintBlendCollider* self);
void ComputeTintBlendColliderContactValue(TintBlendCollider* self, void* out);
void HandleTintBlendColliderNotification(TintBlendCollider* self, s32 code, MessageBody* rec);
s32 GetTintBlendColliderRequestPhase(TintBlendCollider* self);
void InitClass75Object(void* self);
void RegisterClass75Object(void* self);
void UnregisterClass75Object(void* self);
void CopyClass75ObjectData(Class75Object* self, Class75Object* src);
void InitCommentaryPromptElement(T217D_1380* self);
void UpdateBestTimeState(T217D_1380* self);
void DrawFramedText(T217D_1380* self);
void InitOnOffObject(OnOffObject* self);
void UnregisterOnOffObject(OnOffObject* self);
void LoadOnOffObject(OnOffObject* self, void* a1);
void StartOnOffObject(OnOffObject* self);
void UpdateOnOffObject(OnOffObject* self, f32 dt);
void DrawOnOffObject(OnOffObject* self, void* arg1, void* arg2);
void SetOnOffObjectFrozen(OnOffObject* self, s32 p);
void ActivateOnOffCameraController(OnOffCameraController* self, OnOffObject* object);
void DeactivateOnOffCameraController(OnOffCameraController* self);
void NoteOnOffCameraControllerPushed(OnOffCameraController* self, s32 arg);
void NoteOnOffCameraControllerRemoved(OnOffCameraController* self, s32 arg);
void UpdateOnOffCameraController(OnOffCameraController* self, CameraPlacement* eye, PadRecord* pad, f32 dt);
void InitPlayerLinkedCollider(PlayerLinkedCollider* self);
void StartPlayerLinkedCollider(PlayerLinkedCollider* self);
void UpdatePlayerLinkedCollider(PlayerLinkedCollider* self, f32 dt);
void ControlPlayerLinkedCollider(PlayerLinkedCollider* self, void* obj, f32 t);
void HandlePlayerLinkedColliderActivation(PlayerLinkedCollider* self, u8* p);
void HandlePlayerLinkedColliderNotification(PlayerLinkedCollider* self, s32 kind, MessageBody* rec);
s32 TestPlayerLinkedColliderMayContact(PlayerLinkedCollider* self, void* arg);
void StartPlayerLinkedColliderEffect(PlayerLinkedCollider* self, s32 mode, PlacedObject* other);
void GetPlayerLinkedColliderInteractFlags(PlayerLinkedCollider* a0, void* a1, ZeroPair* out);
void* GetPlayerLinkedColliderTarget(PlayerLinkedCollider* self);
void InitArcPoints(T217D_3F0* self, s32 kind);
void CreateArcSprite(T217D_3F0* self);
void DrawArc(T217D_3F0* self);
void SetArcMode(T217D_3F0* self, s32 value);
void UpdateArc(T217D_3F0* self);
void QueueArcDraw(T217D_3F0* self);
void ResetArc(T217D_3F0* self);
void InitWorld1Boss(World1Boss* self);
void StartWorld1Boss(World1Boss* self);
void EnterWorld1BossState(World1Boss* self, s32 a, Animation* b);
s32 ChooseWorld1BossState(World1Boss* self);
s32 IsWorld1BossFree(World1Boss* a0);
s32 IsWorld1BossTargetInRange(World1Boss* a0);
void SteerWorld1BossAlongPath(World1Boss* a0);
void RestartWorld1BossClip(World1Boss* self);
void UpdateWorld1BossGoal(World1Boss* self, s32 flag);
void UpdateWorld1BossState(World1Boss* self);
void ShowElementWhenMenusClear();
s32 TestAgentMayContactExceptKeys(World1Boss* self, Collider* probe);
void UpdateWorld(World* self, f32 dt);
void InitWorld3BeatPressCollider(World3BeatPressCollider* self);
void LoadWorld3BeatPressCollider(World3BeatPressCollider* self, BufferedStream* stream);
void StartWorld3BeatPressCollider(World3BeatPressCollider* self);
void HandleWorld3BeatPressColliderActivation(World3BeatPressCollider* self, void* p);
void JudgeWorld3BeatPressInput(World3BeatPressCollider* self, PadRecord* in, f32 dt);
s32 IsWorld3BeatPressColliderRequestBlocked(World3BeatPressCollider* self);
s32 AcceptWorld3BeatPressColliderRequest();
void GetWorld3BeatPressColliderPositionAt(World3BeatPressCollider* self, f32 t, Vec02* pos, Vec02* vel);
void GetWorld3BeatPressColliderRotationAt(World3BeatPressCollider* self, f32 t, Mat02* rot, Vec02* spin);
void InitWorld3Boss(World3Boss* self);
void LoadWorld3Boss(World3Boss* self, void* reader);
void StartWorld3Boss(World3Boss* self);
void UnregisterWorld3Boss(World3Boss* self);
void RegisterWorld3Boss(World3Boss* self);
s32 IsWorld3BossTargetInRange(World3Boss* self);
s32 IsWorld3BossFree();
void ApplyWorld3BossTransform(World3Boss* self, void* s, void* c);
void DrawWorld3Boss(World3Boss* self, Camera* cam, void* arg2);
void LeaveWorld3BossState(World3Boss* self, s32 arg);
void EnterWorld3BossState(World3Boss* self, s32 a, s32 b);
void HandleWorld3BossNotification(World3Boss* self, s32 kind, TempoNoticeRec* rec);
void UpdateWorld3Boss(World3Boss* self, f32 dt);
void ShowWorld3BossGauge(World3Boss* self);
void UpdateWorld3BossGoal(World3Boss* self, s32 flag);
void UpdateWorld3BossState(World3Boss* self);
void InitWorld3Timeline(World3Timeline* self);
void FindWorld3TimelineTarget(World3Timeline* self);
void InitValueListObject(ValueListObject* self);
void LoadValueList(ValueListObject* self, void* src);
void InitAttachedSet(AttachedSet* self);
void StartAttachedSet(AttachedSet* self);
void UpdateAttachedSet(AttachedSet* self, f32 dt);
void ForwardAttachedSetLinkStep(AttachedSet* self, Attach03* link);
void HandleAttachedSetNotification(AttachedSet* self, s32 kind, void* msg);
void UpdateAttachedSetBounds(AttachedSet* self);
s32 RequestAttachedSetLaunch(AttachedSet* self, void* source, TrackedNodeOffer* offer);
void InitStateResetObject(StateResetObject* self);
void StartStateResetObject(StateResetObject* self);
void UpdateStateResetObject(StateResetObject* self, f32 dt);
void HandleStateResetNotification(StateResetObject* self, s32 kind, StateResetMsg* msg);
void StartWarpPage(WarpPage* o);
void PostLoadWarpPage(WarpPage* self);
void UpdateWarpPage(WarpPage* self, f32 dt);
void ApplyWarpPageTransform(WarpPage* obj, u8* s, void* c);
void HandleWarpPageNotification(WarpPage* self, s32 kind, void* msg);
void InitWarpMenu(T217D_0F0* self);
void HandleWarpMenuInput(T217D_0F0* self, PadRecord* t);
void SetWarpMenuOpen(T217D_0F0* self, s32 a1);
void DrawWarpMenu(T217D_0F0* self);
void InitOscillator(Oscillator* self);
void InitTransformObject(TransformObject* self);
void ReadTransformObject(TransformObject* self, void* stream);
void ReparentObjectKeepingTransform(TransformObject* self, BaseObject* other);
void TransformObjectIntoFrame(TransformObject* self, BaseObject* other);
void LoadArrivalPoint(TransformSet* self, void* other);
void CopyArrivalPoint(TransformSet* self, TransformSet* other);
void StartArrivalPoint(TransformSet* self);
void LoadObjectSubGroup(ObjectSubGroup* self, void* s3);
void StartObjectSubGroup(ObjectSubGroup* self);
void UpdateObjectSubGroup(ObjectSubGroup* self, f32 dt);
void InitLookupObject(LookupObject* self);
void StartLookupObject(LookupObject* self);
void InitContactTracker(ContactTracker* self);
void StartContactTracker(ContactTracker* self);
void CollectTouchingObjects(ContactTracker* self, f32 dt);
void CopyContactTracker(ContactTracker* self, ContactTracker* src);
void ApplyContactTrackerTransform(ContactTracker* self, Camera* cam, ScaledTransform* xf);
int RequestContactTrackerLaunch(ContactTracker* self, void* source, TrackedNodeOffer* offer);
void InitC37(C37* o);
void UpdateC37(C37* self, f32 dt);


extern const ClassDescriptor<2> D_00217380 = { 0x0, 0x0, 0x0, 0x0, {
    0, 0,
} };
extern const Fn_Table g_cameraControllerMethods[6] = { 0, 0, 0, 0, (Fn_Table)UpdateIdleCameraController, 0 };
extern const Fn_Table g_targetCameraControllerMethods[6] = { (Fn_Table)ActivateTargetCameraController, (Fn_Table)DeactivateTargetCameraController, 0, 0, (Fn_Table)UpdateTargetCameraController, 0 };
extern const Fn_Table g_frameCameraControllerMethods[6] = { (Fn_Table)ActivateFrameCameraController, 0, 0, 0, (Fn_Table)UpdateFrameCameraController, 0 };
extern const Fn_Table g_valueCameraControllerMethods[6] = { (Fn_Table)ActivateValueCameraController, (Fn_Table)DeactivateValueCameraController, 0, 0, (Fn_Table)UpdateValueCameraController, 0 };
extern const Fn_Table g_onOffCameraControllerMethods[6] = { (Fn_Table)ActivateOnOffCameraController, (Fn_Table)DeactivateOnOffCameraController, (Fn_Table)NoteOnOffCameraControllerPushed, (Fn_Table)NoteOnOffCameraControllerRemoved, (Fn_Table)UpdateOnOffCameraController, 0 };
// The root every chain of parents ends at (tools/classes.py's `root`).
extern const ClassHead g_classRoot = { 0, 0 };
extern const ClassDescriptor<28> g_objectClass = { &g_classRoot, 0x1, 0x0, 0x34, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadObjectProperties, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<48> g_placedObjectClass = { &g_objectClass, 0x2, 0x1, 0x2D0, {
    (Fn_Table)InitPlacedObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadPlacedObject, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPlacedObject, (Fn_Table)UpdatePlacedObject, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<86> g_colliderClass = { &g_placedObjectClass, 0x3, 0x3, 0x550, {
    (Fn_Table)InitCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPlacedObject, (Fn_Table)UpdateCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    0, 0, 0, 0,
    0, (Fn_Table)GetBaseCurveLengthAtTime, (Fn_Table)GetBaseCurveTimeAtLength, (Fn_Table)GetPathCurveEndTime,
    (Fn_Table)GetPathCurveEndLength, 0, 0, 0,
    0, 0,
} };
extern const PathCurveVt g_pathCurveKind0Methods = { (PathLoad)ReadPathCurve, (PathM01)SamplePathCurveAtTime, (PathM02)SamplePathCurveAtLength, (PathM03)DrawPathCurveSegment, (PathTransform)TransformPathCurvePoints, (PathArcAt)GetPathCurveLengthAtTime, (PathTimeAt)GetPathCurveTimeAtLength, (PathLast)GetPathCurveEndTime, (PathLast)GetPathCurveEndLength, (PathFill)FillPathCurveLengths, (PathM10)FindPathCurveNearestPoint, (PathM11)ProjectOntoPathCurveNearTime, (PathM11)ProjectOntoPathCurveNearLength, 0 };
extern const PathCurveVt g_pathCurveKind1Methods = { (PathLoad)ReadSplinePathCurve, (PathM01)SampleSplinePathAtTime, (PathM02)SampleSplinePathAtLength, (PathM03)DrawSplinePathSegment, (PathTransform)TransformSplinePathPoints, (PathArcAt)GetSplineLengthAtTime, (PathTimeAt)GetSplineTimeAtLength, (PathLast)GetPathCurveEndTime, (PathLast)GetPathCurveEndLength, (PathFill)FillSplinePathLengths, (PathM10)FindSplinePathNearestPoint, (PathM11)FindSplinePathNearestTime, (PathM11)ProjectOntoSplinePathNearLength, 0 };
extern const ClassDescriptor<28> g_pathCurveObjectClass = { &g_objectClass, 0x6E, 0x0, 0x38, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadPathCurveObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentPathCurveObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> g_pointObjectClass = { &g_objectClass, 0x7E, 0x0, 0x50, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadPointObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentPointObject, (Fn_Table)ConvertPointObjectPosition, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> g_textPointObjectClass = { &g_pointObjectClass, 0x82, 0x0, 0x60, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadTextPointObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentPointObject, (Fn_Table)ConvertPointObjectPosition, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> g_transformObjectClass = { &g_objectClass, 0x73, 0x0, 0x80, {
    (Fn_Table)InitTransformObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)ReadTransformObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObjectKeepingTransform, (Fn_Table)TransformObjectIntoFrame, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> g_arrivalPointClass = { &g_transformObjectClass, 0x74, 0x0, 0x100, {
    (Fn_Table)InitTransformObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyArrivalPoint, (Fn_Table)LoadArrivalPoint, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartArrivalPoint, 0, 0, 0,
    0, (Fn_Table)ReparentObjectKeepingTransform, (Fn_Table)TransformObjectIntoFrame, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<48> g_objectSubGroupClass = { &g_placedObjectClass, 0x7D, 0x1, 0x330, {
    (Fn_Table)InitPlacedObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadObjectSubGroup, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartObjectSubGroup, (Fn_Table)UpdateObjectSubGroup, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<48> g_lookupObjectClass = { &g_placedObjectClass, 0x4E, 0x1, 0x320, {
    (Fn_Table)InitLookupObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadPlacedObject, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartLookupObject, (Fn_Table)UpdatePlacedObject, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<48> g_coneVolumeClass = { &g_placedObjectClass, 0x51, 0x1, 0x620, {
    (Fn_Table)InitConeVolume, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterConeVolume, (Fn_Table)UnregisterConeVolume,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyConeVolume, (Fn_Table)LoadPlacedObject, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPlacedObject, (Fn_Table)UpdatePlacedObject, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)RefreshConeVolume,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<124> g_switchedColliderClass = { &g_colliderClass, 0x5, 0xB, 0x610, {
    (Fn_Table)InitSwitchedCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterSwitchedCollider, (Fn_Table)UnregisterSwitchedCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopySwitchedCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandleSwitchedColliderNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPlacedObject, (Fn_Table)UpdateSwitchedCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)HandleSwitchedColliderActivation, 0, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsSwitchedColliderRequestBlocked,
    (Fn_Table)AcceptSwitchedColliderRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
    (Fn_Table)InitScreenElement, (Fn_Table)SetupScreenElementText, (Fn_Table)UpdateScreenElementSlide, 0,
    0, (Fn_Table)ResetScreenElement, 0, 0,
    (Fn_Table)SetScreenElementText, (Fn_Table)DrawScreenElementText, 0, (Fn_Table)GetScreenElementSlideInTime,
    (Fn_Table)GetScreenElementHoldTime, (Fn_Table)GetScreenElementSlideOutTime, (Fn_Table)ShowScreenElement, (Fn_Table)HideScreenElement,
    (Fn_Table)SetScreenElementMode, (Fn_Table)SetScreenElementClock, (Fn_Table)AreScreenElementsTogether, 0,
    (Fn_Table)InitScreenElement, (Fn_Table)InitCounterCaption, (Fn_Table)UpdateCounterCaption, 0,
    0, (Fn_Table)ResetScreenElement, 0, 0,
    (Fn_Table)SetScreenElementText, (Fn_Table)DrawCounterCaption, 0, (Fn_Table)GetScreenElementSlideInTime,
    (Fn_Table)GetCaptionHoldTime, (Fn_Table)GetScreenElementSlideOutTime, (Fn_Table)ShowScreenElement, (Fn_Table)HideScreenElement,
    (Fn_Table)SetScreenElementMode, (Fn_Table)SetScreenElementClock, (Fn_Table)AreScreenElementsTogether, 0,
} };
extern const T217D_Vt D_00217E30 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00217E80 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00217ED0 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00217F20 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00217F70 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetPairCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt g_gaugeAmountCaptionMethods = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetGaugeAmountCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00218010 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00218060 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_002180B0 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00218100 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00218150 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_002181A0 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetGaugeColliderCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_002181F0 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00218240 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00218290 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt g_gaugeBarElementMethods = { (ElementIntFn)InitScreenElement, (ElementFn)InitGauge, (ElementFn)UpdateScreenElementSlide, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawGauge, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00218330 = {
    (ElementIntFn)InitScreenElement, (ElementFn)InitFramedElement, (ElementFn)UpdateScreenElementSlide, 0,
    0, (ElementFn)ResetScreenElement, 0, 0,
    (ElementTextFn)SetCaptionTextAndSize, (ElementFn)DrawElementWithFadedFrame, 0, (ElementTimeFn)GetScreenElementSlideInTime,
    (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement,
    (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0,
};
extern const T217D_Vt g_pointerTextCaptionMethods = { (ElementIntFn)InitScreenElement, (ElementFn)InitPointerTextCaption, (ElementFn)UpdateScreenElementSlide, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetElementTextAfterSlideOut, (ElementFn)DrawSlidingGlyphElement, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowElementUnlessTextPending, (ElementFn)HideElementOrDropPendingText, (ElementIntFn)SetElementModeApplyingPendingText, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreElementsTogetherOrPending, 0 };
extern const T217D_Vt g_copiedTextCaptionMethods = { (ElementIntFn)InitScreenElement, (ElementFn)InitCopiedTextCaption, (ElementFn)UpdateScreenElementSlide, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetElementTextCopiedAfterSlideOut, (ElementFn)DrawMessageElement, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowElementUnlessCopiedTextPending, (ElementFn)HideElementOrDropCopiedText, (ElementIntFn)SetElementModeApplyingCopiedText, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt g_hintGlyphElementMethods = { (ElementIntFn)InitScreenElement, (ElementFn)InitHintGlyphElement, (ElementFn)UpdateHintGlyphElement, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawHintGlyphElement, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt g_titleElementMethods = { (ElementIntFn)InitScreenElement, (ElementFn)InitTitleElement, (ElementFn)UpdateScreenElementSlide, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawTitleElement, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt g_promptElementMethods = { (ElementIntFn)InitScreenElement, (ElementFn)InitPromptElement, (ElementFn)UpdatePromptElement, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawPromptElement, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetElementModeRebuildingText, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt g_timerElementMethods = { (ElementIntFn)InitScreenElement, (ElementFn)InitTimerElement, (ElementFn)UpdateTimerElement, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawTimerElement, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt g_letterboxElementMethods = { (ElementIntFn)InitScreenElement, (ElementFn)InitLetterboxElement, (ElementFn)UpdateScreenElementSlide, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawLetterboxElement, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetElementModeFollowingFade, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt g_letterGlyphElementMethods = { (ElementIntFn)InitScreenElement, (ElementFn)InitLetterGlyphElement, (ElementFn)UpdateScreenElementSlide, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawLetterGlyphElement, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt g_cyclingGlyphElementMethods = { (ElementIntFn)InitScreenElement, (ElementFn)InitCyclingGlyphElement, (ElementFn)UpdateScreenElementSlide, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawScreenElementText, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetElementModeClearingFlag, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const ClassDescriptor<28> g_coloredTriangleSetClass = { &g_objectClass, 0x8E, 0x0, 0xA0, {
    (Fn_Table)InitColoredTriangles, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadColoredTriangles, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const T217D_Vt g_pauseMenuElementMethods = { (ElementIntFn)InitScreenElement, (ElementFn)InitPauseMenu, (ElementFn)UpdateScreenElementSlide, (ElementIntFn)SetPauseMenuOpen, (ElementPadFn)UpdatePauseMenu, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawPauseMenu, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowPauseMenu, (ElementFn)HidePauseMenu, (ElementIntFn)SetPauseMenuMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt g_stackedCaptionGroupMethods = { (ElementIntFn)InitItemColumn, (ElementFn)SetupItemColumn, (ElementFn)UpdateItemColumnSlide, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawItemColumn, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)UpdateItemColumn, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const ClassDescriptor<72> g_attachedSetClass = { &g_colliderClass, 0x1F, 0x83, 0x6B0, {
    (Fn_Table)InitAttachedSet, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandleAttachedSetNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartAttachedSet, (Fn_Table)UpdateAttachedSet, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateAttachedSetBounds, (Fn_Table)ForwardAttachedSetLinkStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestAttachedSetLaunch,
} };
extern const ClassDescriptor<48> g_onOffObjectClass = { &g_placedObjectClass, 0x63, 0x1, 0x470, {
    (Fn_Table)InitOnOffObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterOnOffObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadOnOffObject, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartOnOffObject, (Fn_Table)UpdateOnOffObject, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetOnOffObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawOnOffObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<74> g_maskedColliderClass = { &g_colliderClass, 0x20, 0x3, 0x6C0, {
    (Fn_Table)InitMaskedCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyMaskedCollider, (Fn_Table)LoadMaskedCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartMaskedCollider, (Fn_Table)UpdateMaskedCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleMaskedColliderEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)HandleMaskedColliderActivation, 0,
} };
extern const ClassDescriptor<72> g_timedStateClass = { &g_colliderClass, 0x27, 0x3, 0x570, {
    (Fn_Table)InitCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandleTimedStateNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPlacedObject, (Fn_Table)UpdateTimedState, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestTimedStateContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<74> g_playerFlaggedColliderClass = { &g_maskedColliderClass, 0x21, 0x13, 0x6C0, {
    (Fn_Table)InitPlayerFlaggedCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyMaskedCollider, (Fn_Table)LoadMaskedCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartMaskedCollider, (Fn_Table)UpdateMaskedCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleMaskedColliderEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)HandleMaskedColliderActivation, 0,
} };
extern const ClassDescriptor<74> g_massScalingColliderClass = { &g_maskedColliderClass, 0x25, 0x3, 0x6D0, {
    (Fn_Table)InitMassScalingCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyMaskedCollider, (Fn_Table)LoadMaskedCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartMaskedCollider, (Fn_Table)UpdateMaskedCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleMaskedColliderEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)LatchContactObject, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)HandleMaskedColliderActivation, 0,
} };
extern const ClassDescriptor<74> g_latchedSwitchColliderClass = { &g_massScalingColliderClass, 0x26, 0x3, 0x6E0, {
    (Fn_Table)InitMassScalingCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyMaskedCollider, (Fn_Table)LoadMaskedCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartMaskedCollider, (Fn_Table)UpdateLatchedSwitchCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleMaskedColliderEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)LatchAcceptedSwitchedCollider, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)HandleMaskedColliderActivation, 0,
} };
extern const ClassDescriptor<72> g_zoneColliderClass = { &g_colliderClass, 0x29, 0x3, 0x7A0, {
    (Fn_Table)InitZoneCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyZoneCollider, (Fn_Table)LoadZoneCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartZoneCollider, (Fn_Table)UpdateZoneCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<72> g_triggerZoneClass = { &g_colliderClass, 0x28, 0x3, 0x890, {
    (Fn_Table)InitTriggerZone, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyTriggerZone, (Fn_Table)LoadTriggerZone, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartTriggerZone, (Fn_Table)UpdateTriggerZone, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepTriggerZone, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleTriggerZoneEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    (Fn_Table)ReleaseTriggerZoneContacts, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<28> D_002191E0 = { &g_objectClass, 0x87, 0x0, 0x68, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadObjectProperties, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)ResolveLookupIds, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<48> D_00219260 = { &g_placedObjectClass, 0x4F, 0x1, 0x2D0, {
    (Fn_Table)InitPlacedObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadPlacedObject, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPlacedObject, (Fn_Table)UpdatePlacedObject, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<72> D_00219330 = { &g_colliderClass, 0x2B, 0x3, 0x550, {
    (Fn_Table)InitCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPlacedObject, (Fn_Table)UpdateCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<28> g_valueListObjectClass = { &g_objectClass, 0x86, 0x0, 0x44, {
    (Fn_Table)InitValueListObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadValueList, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> D_002194E0 = { &g_objectClass, 0x85, 0x0, 0x34, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadObjectProperties, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const T2195_Vt g_ownerPoseSourceMethods = {
    (AttachInit)InitPoseSource, (AttachCopy)CopyPoseSource, (AttachRelease)ReleasePoseSource, 0,
    (AttachGetPos)GetOwnerPosition, (AttachGetRot)GetOwnerRotation, (AttachGetValue)GetOwnerValue, (AttachGetMatrix)GetIdentityMatrix,
    (AttachGetIndexed)GetOwnerIndexedValue, 0,
};
extern const T2195_Vt g_snapshotPoseSourceMethods = {
    (AttachInit)InitSnapshotPoseSource, (AttachCopy)CopyPoseSource, (AttachRelease)ReleasePoseSource, 0,
    (AttachGetPos)GetSnapshotPosition, (AttachGetRot)GetSnapshotRotation, (AttachGetValue)GetSnapshotValue, (AttachGetMatrix)GetSnapshotMatrix,
    (AttachGetIndexed)GetSnapshotIndexedValue, 0,
};
extern const T2195_Vt g_linkedPoseSourceMethods = { (AttachInit)InitLinkedPoseSource, (AttachCopy)CopyPoseSource, (AttachRelease)ReleasePoseSource, 0, (AttachGetPos)GetLinkedPosition, (AttachGetRot)GetLinkedRotation, (AttachGetValue)GetLinkedValue, (AttachGetMatrix)GetLinkedMatrix, (AttachGetIndexed)GetLinkedIndexedValue, 0 };
extern const T2195_Vt g_identityPoseSourceMethods = { (AttachInit)InitIdentityPoseSource, (AttachCopy)CopyPoseSource, (AttachRelease)ReleasePoseSource, 0, (AttachGetPos)GetIdentityPosePosition, (AttachGetRot)GetIdentityPoseRotation, (AttachGetValue)GetNextPoseSourceValue, (AttachGetMatrix)GetIdentityPoseMatrix, (AttachGetIndexed)GetIdentityPoseIndexedValue, 0 };
extern const AttachmentAndCurveBases g_aimPoseSourceBases = {
    { (AttachInit)InitAimPoseSource, (AttachCopy)CopyPoseSource, (AttachRelease)ReleasePoseSource, 0, (AttachGetPos)GetOwnerPosition, (AttachGetRot)GetAimPoseRotation, (AttachGetValue)GetOwnerValue, (AttachGetMatrix)GetIdentityMatrix, (AttachGetIndexed)GetOwnerIndexedValue, 0 },
    { (PositionCurveEval)EvaluateNoPositionCurve, 0, (PositionCurveTimes)GetNoPositionCurveTimes, 0 },
    { (RotationCurveEval)EvaluateNoRotationCurve, (RotationCurveGet)GetNoRotationCurve, 0, (RotationCurveTimes)GetNoRotationCurveTimes },
    { (ScaleCurveEval)EvaluateNoScaleCurve, 0, (ScaleCurveTimes)GetNoScaleCurveTimes, 0 },
    { (WeightCurveEval)EvaluateNoWeightCurve, 0, (WeightCurveTimes)GetNoWeightCurveTimes, 0 },
};
extern const WeightCurveVt g_weightCurveKind0Methods = { (WeightCurveEval)EvaluateTangentWeightCurve, (WeightCurveRead)ReadTangentWeightCurve, (WeightCurveTimes)GetTangentWeightCurveTimes, 0 };
extern const WeightCurveVt g_weightCurveKind1Methods = { (WeightCurveEval)EvaluateControlPointWeightCurve, (WeightCurveRead)ReadControlPointWeightCurve, (WeightCurveTimes)GetControlPointWeightCurveTimes, 0 };
extern const WeightCurveVt g_weightCurveKind2Methods = { (WeightCurveEval)EvaluateLinearWeightCurve, (WeightCurveRead)ReadLinearWeightCurve, (WeightCurveTimes)GetLinearWeightCurveTimes, 0 };
extern const WeightCurveVt g_weightCurveKind3Methods = { (WeightCurveEval)EvaluateAngleBlendCurve, 0, (WeightCurveTimes)GetNoWeightCurveTimes, 0 };
extern const WeightCurveVt g_weightCurveKind4Methods = { (WeightCurveEval)EvaluateValueBlendCurve, 0, (WeightCurveTimes)GetNoWeightCurveTimes, 0 };
extern const PositionCurveVt g_positionCurveKind0Methods = { (PositionCurveEval)EvaluateAxisPositionCurve, (PositionCurveRead)ReadAxisPositionCurve, (PositionCurveTimes)GetAxisPositionCurveTimes, 0 };
extern const PositionCurveVt g_positionCurveKind1Methods = { (PositionCurveEval)EvaluateVectorKeyPositionCurve, (PositionCurveRead)ReadVectorKeyPositionCurve, (PositionCurveTimes)GetVectorKeyPositionCurveTimes, 0 };
extern const PositionCurveVt g_positionCurveKind2Methods = { (PositionCurveEval)EvaluateBlendedPositionCurve, 0, (PositionCurveTimes)GetNoPositionCurveTimes, 0 };
extern const RotationCurveVt g_rotationCurveKind0Methods = { (RotationCurveEval)EvaluateAxisRotationCurve, (RotationCurveGet)GetAxisRotationCurve, (RotationCurveRead)ReadAxisRotationCurve, (RotationCurveTimes)GetAxisRotationCurveKeyTimes };
extern const RotationCurveVt g_rotationCurveKind1Methods = { (RotationCurveEval)EvaluateKeyedRotationCurve, (RotationCurveGet)GetKeyedRotationCurve, (RotationCurveRead)ReadKeyedRotationCurve, (RotationCurveTimes)GetKeyedRotationCurveKeyTimes };
extern const RotationCurveVt g_rotationCurveKind2Methods = { (RotationCurveEval)EvaluateBlendedRotationCurve, (RotationCurveGet)GetNoRotationCurve, 0, (RotationCurveTimes)GetNoRotationCurveTimes };
extern const ScaleCurveVt g_scaleCurveKind0Methods = { (ScaleCurveEval)EvaluateAxisScaleCurve, (ScaleCurveRead)ReadAxisScaleCurve, (ScaleCurveTimes)GetAxisScaleCurveKeyTimes, 0 };
extern const ScaleCurveVt g_scaleCurveKind1Methods = { (ScaleCurveEval)EvaluateKeyedScaleCurve, (ScaleCurveRead)ReadKeyedScaleCurve, (ScaleCurveTimes)GetKeyedScaleCurveKeyTimes, 0 };
extern const ClassDescriptor<28> g_animationClass = { &g_objectClass, 0x83, 0x40, 0xB0, {
    (Fn_Table)InitAnimation, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyAnimation, (Fn_Table)LoadAnimation, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartClampedKinematicValue, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassHead g_animationPlayerMethods = { &g_classRoot, 0x92 };
extern const T2195_Vt g_trackPoseSourceMethods = { (AttachInit)InitPoseSource, (AttachCopy)CopyTrackPoseSource, (AttachRelease)ReleaseTrackPoseSource, 0, (AttachGetPos)GetTrackPosition, (AttachGetRot)GetTrackRotation, (AttachGetValue)GetTrackValue, (AttachGetMatrix)GetTrackScaleMatrix, (AttachGetIndexed)GetTrackIndexedValue, 0 };
extern const ClassDescriptor<28> g_skipAnimationPlayerClass = { &g_animationClass, 0x84, 0x40, 0xD0, {
    (Fn_Table)InitAnimation, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)SkipAnimationPlayerCopy, (Fn_Table)SkipAnimationPlayerLoad, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)SkipAnimationPlayerStart, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> g_stateGraphClass = { &g_objectClass, 0x88, 0x0, 0x54, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadStateGraph, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartStateGraph, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassHead g_stateWalkerMethods = { &g_classRoot, 0x93 };
extern const ClassDescriptor<72> D_002198F0 = { &g_colliderClass, 0x35, 0x3, 0x550, {
    (Fn_Table)InitCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPlacedObject, (Fn_Table)UpdateCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawC35Collider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<48> D_00219A20 = { &g_placedObjectClass, 0x52, 0x1, 0x2D0, {
    (Fn_Table)InitPlacedObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadPlacedObject, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPlacedObject, (Fn_Table)UpdatePlacedObject, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawC52Object, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<72> g_effectOwnerClass = { &g_colliderClass, 0x1E, 0x3, 0x570, {
    (Fn_Table)InitEffectOwner, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)ReleaseEffectOwner,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPlacedObject, (Fn_Table)UpdateEffectOwner, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveEffectsAndBounds,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawEffects, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)KeepEffectOwnerBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
// The effect kinds' tables of functions (func_0019E908 returns one per kind); their functions
// are in src/main/effect.cpp.
extern const Fn_Table g_basicEffectMethods[8] = { (Fn_Table)InitEffect, 0, 0, (Fn_Table)MoveEffect, (Fn_Table)UpdateEffect, (Fn_Table)DrawEffect, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_fallingEffectMethods[8] = { (Fn_Table)InitFallingEffect, 0, 0, (Fn_Table)MoveEffect, (Fn_Table)UpdateEffect, (Fn_Table)DrawEffect, (Fn_Table)EndEffectWithImpact, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_risingEffectMethods[8] = { (Fn_Table)InitRisingEffect, 0, 0, (Fn_Table)MoveDriftingEffect, (Fn_Table)UpdateEffect, (Fn_Table)DrawEffect, (Fn_Table)EndEffectWithImpactOnExit, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_impactEffectMethods[8] = { (Fn_Table)InitImpactEffect, 0, 0, (Fn_Table)MoveEffect, (Fn_Table)UpdateEffect, (Fn_Table)DrawEffect, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_growingEffectMethods[8] = { (Fn_Table)InitGrowingEffect, 0, 0, (Fn_Table)MoveEffect, (Fn_Table)UpdateEffect, (Fn_Table)DrawEffect, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_shrinkingFallEffectMethods[8] = { (Fn_Table)InitShrinkingFallEffect, 0, 0, (Fn_Table)MoveEffect, (Fn_Table)UpdateEffect, (Fn_Table)DrawEffect, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_droppingEffectMethods[8] = { (Fn_Table)InitDroppingEffect, 0, 0, (Fn_Table)MoveEffect, (Fn_Table)UpdateDroppingEffect, (Fn_Table)DrawDroppingEffect, (Fn_Table)EndDroppingEffect, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_streakEffectMethods[8] = { (Fn_Table)InitStreakEffect, 0, 0, (Fn_Table)MoveEffect, (Fn_Table)UpdateEffect, (Fn_Table)DrawStreakEffect, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_scaledEffectMethods[8] = { (Fn_Table)InitScaledEffect, 0, 0, (Fn_Table)MoveEffect, (Fn_Table)UpdateEffect, (Fn_Table)DrawEffect, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_trailSegmentEffectMethods[8] = { (Fn_Table)InitTrailSegment, 0, (Fn_Table)DetachTrailSegment, (Fn_Table)MoveTrailSegment, (Fn_Table)UpdateEffect, (Fn_Table)DrawTrailSegment, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_spawningEffectMethods[8] = { (Fn_Table)InitSpawningEffect, 0, 0, (Fn_Table)MoveEffect, (Fn_Table)SpawnFollowUpEffect, (Fn_Table)DrawEffect, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_followUpEffectMethods[8] = { (Fn_Table)InitFollowUpEffect, 0, 0, (Fn_Table)MoveEffect, (Fn_Table)UpdateEffect, (Fn_Table)DrawEffect, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_wideTrailSegmentEffectMethods[8] = { (Fn_Table)InitWideTrailSegment, 0, (Fn_Table)DetachTrailSegment, (Fn_Table)MoveTrailSegment, (Fn_Table)UpdateEffect, (Fn_Table)DrawTrailSegment, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_shortFallingEffectMethods[8] = { (Fn_Table)InitShortFallingEffect, 0, 0, (Fn_Table)MoveEffect, (Fn_Table)UpdateEffect, (Fn_Table)DrawEffect, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_emitterEffectMethods[8] = {
    (Fn_Table)InitEmitterEffect, 0, 0, (Fn_Table)MoveEmitterEffect,
    (Fn_Table)UpdateEmitterEffect, (Fn_Table)DrawEmitterEffect, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContact,
};
extern const Fn_Table g_cameraSpaceEffectMethods[8] = { (Fn_Table)InitCameraSpaceEffect, 0, 0, (Fn_Table)MoveCameraSpaceEffect, (Fn_Table)RunEffectEndCallback, (Fn_Table)DrawCameraSpaceEffect, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_longStreakEffectMethods[8] = { (Fn_Table)InitLongStreakEffect, 0, 0, (Fn_Table)MoveEffect, (Fn_Table)UpdateEffect, (Fn_Table)DrawStreakEffect, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_phasedEffectMethods[8] = { (Fn_Table)InitPhasedEffect, 0, 0, (Fn_Table)KeepPhasedEffectStill, (Fn_Table)AdvanceEffectPhases, (Fn_Table)DrawPhasedEffect, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_projectileEffectMethods[8] = { (Fn_Table)InitEffect, (Fn_Table)CopyEffectSourceIds, 0, (Fn_Table)MoveEffect, (Fn_Table)UpdateEffect, (Fn_Table)DrawProjectileEffect, (Fn_Table)EndEffect, (Fn_Table)HandleEffectImpact };
extern const Fn_Table g_hitMarkEffectMethods[8] = { (Fn_Table)InitEffect, 0, 0, (Fn_Table)MoveEffect, (Fn_Table)UpdateEffectUntilDetached, (Fn_Table)DrawHitMarkEffect, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_tumblingEffectMethods[8] = { (Fn_Table)InitEffect, (Fn_Table)SetRandomEffectSpin, 0, (Fn_Table)MoveTumblingEffect, (Fn_Table)UpdateEffect, (Fn_Table)DrawEffect, (Fn_Table)EndEffect, (Fn_Table)HandleTumblingEffectImpact };
extern const Fn_Table g_aimedEffectMethods[8] = { (Fn_Table)InitEffect, (Fn_Table)AimEffectAtNearestObject, 0, (Fn_Table)MoveEffect, (Fn_Table)UpdateEffect, (Fn_Table)DrawEffect, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_streakedEffectMethods[8] = { (Fn_Table)InitEffect, (Fn_Table)PlaceEffectAtSource, 0, (Fn_Table)MoveEffect, (Fn_Table)UpdateEffect, (Fn_Table)DrawStreakedEffect, (Fn_Table)EndEffect, (Fn_Table)HandleStreakedEffectImpact };
extern const Fn_Table g_spinningEffectMethods[8] = { (Fn_Table)InitEffect, (Fn_Table)RandomizeEffectSpin, 0, (Fn_Table)MoveEffect, (Fn_Table)UpdateEffect, (Fn_Table)DrawSpinningEffect, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContactUnlessKind6 };
extern const Fn_Table g_facingEffectMethods[8] = { (Fn_Table)InitFacingEffect, 0, 0, (Fn_Table)MoveEffect, (Fn_Table)UpdateEffect, (Fn_Table)DrawFacingEffect, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_delayedEffectMethods[8] = { (Fn_Table)InitDelayedEffect, 0, 0, (Fn_Table)MoveDelayedEffect, (Fn_Table)UpdateDelayedEffect, (Fn_Table)DrawDelayedEffect, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContact };
extern const Fn_Table g_messageEffectMethods[8] = { (Fn_Table)InitEffect, (Fn_Table)ResolveEffectTarget, 0, (Fn_Table)MoveEffect, (Fn_Table)SendEffectMessagesAtRate, (Fn_Table)DrawEffect, (Fn_Table)EndEffect, (Fn_Table)HandleEffectContact };
extern const ClassDescriptor<48> g_worldListedObjectClass = { &g_placedObjectClass, 0x4D, 0x1, 0x640, {
    (Fn_Table)InitWorldListedObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)LeaveWorldLists, (Fn_Table)ReleaseWorldListedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadPlacedObject, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPlacedObject, (Fn_Table)UpdateWorldListedObject, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)CopyWorldListedObject,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveWorldListedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)SubmitWorldListedObjectBlock, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<48> g_effectSpawnerClass = { &g_placedObjectClass, 0x50, 0x1, 0x350, {
    (Fn_Table)InitEffectSpawner, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyEffectSpawner, (Fn_Table)LoadEffectSpawner, 0,
    0, (Fn_Table)ReleaseEffectSpawnerHeld, (Fn_Table)SendObjectNotification, (Fn_Table)ResolveEffectSpawnerLinks,
    (Fn_Table)StartEffectSpawner, (Fn_Table)UpdateEffectSpawner, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<28> g_memberObjectClass = { &g_transformObjectClass, 0x77, 0x0, 0x90, {
    (Fn_Table)InitTransformObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)ReadTransformObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartMemberObject, 0, 0, 0,
    0, (Fn_Table)ReparentObjectKeepingTransform, (Fn_Table)TransformObjectIntoFrame, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)SendMemberObjectMessage,
} };
extern const ClassDescriptor<28> g_groupMembersClass = { &g_memberObjectClass, 0x78, 0x0, 0xC0, {
    (Fn_Table)InitTransformObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyGroupMembers, (Fn_Table)LoadGroupMembers, 0,
    0, 0, (Fn_Table)SendObjectNotification, (Fn_Table)ResolveGroupMembers,
    (Fn_Table)StartMemberObject, 0, 0, 0,
    0, (Fn_Table)ReparentObjectKeepingTransform, (Fn_Table)TransformObjectIntoFrame, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)BroadcastMessageToMembers,
} };
extern const ClassDescriptor<28> g_recordMemberClass = { &g_memberObjectClass, 0x79, 0x0, 0xA0, {
    (Fn_Table)InitRecordMember, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyRecordMember, (Fn_Table)LoadRecordMember, 0,
    0, 0, (Fn_Table)SendObjectNotification, (Fn_Table)ResolveRecordMemberTargets,
    (Fn_Table)StartMemberObject, 0, 0, 0,
    0, (Fn_Table)ReparentObjectKeepingTransform, (Fn_Table)TransformObjectIntoFrame, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)SendRecordMemberMessage,
} };
extern const ClassDescriptor<28> g_holdingMemberClass = { &g_recordMemberClass, 0x7A, 0x0, 0xD0, {
    (Fn_Table)InitHoldingMember, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyRecordMember, (Fn_Table)LoadRecordMember, 0,
    0, (Fn_Table)ReleaseHeldObject, (Fn_Table)SendObjectNotification, (Fn_Table)ResolveHoldingMemberTargets,
    (Fn_Table)StartMemberObject, 0, 0, 0,
    0, (Fn_Table)ReparentObjectKeepingTransform, (Fn_Table)TransformObjectIntoFrame, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)SendMessageAfterDelay,
} };
extern const ClassDescriptor<48> g_objectGroupClass = { &g_placedObjectClass, 0x53, 0x101, 0x2F0, {
    (Fn_Table)InitObjectGroup, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyObjectGroup, (Fn_Table)LoadObjectGroup, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartObjectGroup, (Fn_Table)UpdatePlacedObject, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const T217D_Vt g_arcElementMethods = { (ElementIntFn)InitArcPoints, (ElementFn)CreateArcSprite, (ElementFn)UpdateArc, 0, 0, (ElementFn)ResetArc, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawArc, (ElementFn)QueueArcDraw, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetArcMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt g_typedTextCaptionBoxMethods = { (ElementIntFn)InitTextPanel, (ElementFn)SetupTextPanel, (ElementFn)UpdateScreenElementSlide, (ElementIntFn)SetTextPanelOpen, (ElementPadFn)UpdatePanelStick, (ElementFn)ResetTextPanel, (ElementFn)ChooseTextPanelState, (ElementFn)EndTextPanelState, (ElementTextFn)SetTextPanelText, (ElementFn)DrawTextPanel, 0, (ElementTimeFn)GetTextPanelSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetTextPanelSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetTextPanelMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const ClassDescriptor<48> g_stepSequenceClass = { &g_placedObjectClass, 0x65, 0x1, 0x340, {
    (Fn_Table)InitStepSequence, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadStepSequence, 0,
    0, (Fn_Table)HandleStepSequenceNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartStepSequence, (Fn_Table)UpdateStepSequence, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<28> g_targetCurveClass = { &g_pathCurveObjectClass, 0x6F, 0x0, 0x60, {
    (Fn_Table)InitTargetCurve, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterTargetCurve, (Fn_Table)UnregisterTargetCurve,
    (Fn_Table)CloneObject, (Fn_Table)CopyTargetCurve, (Fn_Table)LoadPathCurveObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadTargetCurve,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentPathCurveObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> g_targetPointClass = { &g_pointObjectClass, 0x7F, 0x0, 0x80, {
    (Fn_Table)InitTargetPoint, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterTargetPoint, (Fn_Table)UnregisterTargetPoint,
    (Fn_Table)CloneObject, (Fn_Table)CopyTargetPoint, (Fn_Table)LoadPointObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadTargetPoint,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentPointObject, (Fn_Table)ConvertPointObjectPosition, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<72> g_listedCollisionPartClass = { &g_colliderClass, 0x3A, 0x3, 0x570, {
    (Fn_Table)InitListedCollisionPart, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)AddToPartList, (Fn_Table)RemoveFromPartList,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyKeepingListLink, (Fn_Table)LoadListedCollisionPart, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPlacedObject, (Fn_Table)UpdateCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepListedCollisionPart, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestListedCollisionPartMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const T2195_Vt g_aimSwitchPoseSourceMethods = {
    (AttachInit)InitAim, (AttachCopy)CopyPoseSource, (AttachRelease)ReleasePoseSource, (AttachUpdate)SwitchAimByTargetDistance,
    (AttachGetPos)GetOwnerPosition, (AttachGetRot)GetAimRotation, (AttachGetValue)GetOwnerValue, (AttachGetMatrix)GetIdentityMatrix,
    (AttachGetIndexed)GetOwnerIndexedValue, 0,
};
extern const ClassDescriptor<28> g_aimBlendGridClass = { &g_objectClass, 0x8B, 0x0, 0x3F0, {
    (Fn_Table)InitAimBlendGrid, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadAimBlendGrid, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartAimBlendGrid, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<88> g_turningColliderClass = { &g_switchedColliderClass, 0x6, 0xB, 0x720, {
    (Fn_Table)InitTurningCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterSwitchedCollider, (Fn_Table)UnregisterSwitchedCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopySwitchedCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandleSwitchedColliderNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartTurningCollider, (Fn_Table)UpdateTurningCollider, (Fn_Table)RecomputeTurningColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepTurningCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetTurningColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetTurningColliderPose,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawTurningCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyTurningColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeTurningColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)CollideTurningColliderWithObject, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeTurningColliderContactValue, (Fn_Table)ResolveTurningColliderContact, (Fn_Table)ClampTurningColliderContactLimit, (Fn_Table)CollectTurningColliderContacts,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)HandleSwitchedColliderActivation, 0, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsSwitchedColliderRequestBlocked,
    (Fn_Table)AcceptSwitchedColliderRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
    (Fn_Table)BuildTurningColliderHeadingMatrix, (Fn_Table)GetTurningColliderContactMode, (Fn_Table)IsTurningColliderGroundContact, 0,
} };
extern const T2195_Vt g_childSumPoseSourceMethods = {
    (AttachInit)InitPoseSource, (AttachCopy)CopyPoseSource, (AttachRelease)ReleasePoseSource, 0,
    (AttachGetPos)SumChildPoseOffsets, (AttachGetRot)CombineChildPoseRotations, (AttachGetValue)GetOwnerValue, (AttachGetMatrix)GetIdentityMatrix,
    (AttachGetIndexed)GetOwnerIndexedValue, 0,
};
extern const ClassDescriptor<74> D_0021A9D0 = { &g_playerFlaggedColliderClass, 0x22, 0x13, 0x6D0, {
    (Fn_Table)InitPlayerFlaggedCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyMaskedCollider, (Fn_Table)LoadMaskedCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartMaskedCollider, (Fn_Table)UpdateMaskedCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleMaskedColliderEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)ReleaseCountedObject, 0,
} };
extern const ClassDescriptor<72> g_stateTriggerClass = { &g_colliderClass, 0x2F, 0x3, 0x6C0, {
    (Fn_Table)InitStateTrigger, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyStateTrigger, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartStateTrigger, (Fn_Table)UpdateStateTrigger, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<78> g_timedObjectClass = { &g_colliderClass, 0x30, 0x3, 0x5D0, {
    (Fn_Table)InitTimedObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPlacedObject, (Fn_Table)UpdateTimedObject, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    0, 0, 0, 0,
    (Fn_Table)SetTimedObjectTarget, (Fn_Table)EnterTimedObjectState,
} };
extern const ClassDescriptor<78> g_timedGroupClass = { &g_timedObjectClass, 0x31, 0x3, 0xB10, {
    (Fn_Table)InitTimedGroup, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadTimedGroup, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadTimedGroup,
    (Fn_Table)CloneTimedGroupEntries, (Fn_Table)UpdateTimedGroup, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetStaggeredColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawTimedGroup, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)ChooseTimedGroupState, (Fn_Table)SetTimedGroupMode, (Fn_Table)RequestTimedGroupEnd, (Fn_Table)FinishTimedGroup,
    (Fn_Table)SetTimedObjectTarget, (Fn_Table)EnterTimedGroupState,
} };
extern const ClassDescriptor<78> g_sequencedObjectClass = { &g_timedObjectClass, 0x32, 0x3, 0x5F0, {
    (Fn_Table)InitSequencedObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)SetupSequencedObject, (Fn_Table)UpdateSequencedObject, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawSequencedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestSequencedObjectMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)ChooseSequencedObjectState, (Fn_Table)SetSequencedObjectMode, (Fn_Table)RequestSequencedObjectEnd, (Fn_Table)FinishSequencedObject,
    (Fn_Table)SetTimedObjectTarget, (Fn_Table)EnterSequencedObjectState,
} };
extern const ClassDescriptor<78> g_blinkObjectClass = { &g_timedObjectClass, 0x33, 0x3, 0x620, {
    (Fn_Table)InitBlinkObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)SetupBlinkObject, (Fn_Table)UpdateBlinkObject, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)ChooseBlinkObjectState, (Fn_Table)SetBlinkObjectMode, (Fn_Table)RequestBlinkObjectEnd, (Fn_Table)FinishBlinkObject,
    (Fn_Table)SetTimedObjectTarget, (Fn_Table)EnterBlinkObjectState,
} };
extern const ClassDescriptor<28> D_0021B158 = { &g_transformObjectClass, 0x75, 0x0, 0xA0, {
    (Fn_Table)InitClass75Object, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterClass75Object, (Fn_Table)UnregisterClass75Object,
    (Fn_Table)CloneObject, (Fn_Table)CopyClass75ObjectData, (Fn_Table)ReadTransformObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObjectKeepingTransform, (Fn_Table)TransformObjectIntoFrame, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> D_0021B1D8 = { &D_0021B158, 0x76, 0x0, 0xC0, {
    (Fn_Table)InitC76Object, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterClass75Object, (Fn_Table)UnregisterClass75Object,
    (Fn_Table)CloneObject, (Fn_Table)CopyClass75ObjectData, (Fn_Table)LoadC76Object, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObjectKeepingTransform, (Fn_Table)TransformObjectIntoFrame, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> g_targetVectorClass = { &g_pathCurveObjectClass, 0x70, 0x0, 0x70, {
    (Fn_Table)InitTargetVector, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterTargetVector, (Fn_Table)UnregisterTargetVector,
    (Fn_Table)CloneObject, (Fn_Table)CopyTargetVector, (Fn_Table)LoadPathCurveObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartTargetVector, 0, 0, 0,
    0, (Fn_Table)ReparentPathCurveObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<72> g_idFilterObjectClass = { &g_colliderClass, 0x34, 0x3, 0x5B0, {
    (Fn_Table)InitIdFilterObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyIdFilterObject, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartIdFilterObject, (Fn_Table)UpdateIdFilterObject, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestIdFilterMatch, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, (Fn_Table)HandleIdFilterObjectContact, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<48> g_redirectObjectClass = { &g_placedObjectClass, 0x5E, 0x1, 0x340, {
    (Fn_Table)InitRedirectObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadPlacedObject, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartRedirectObject, (Fn_Table)UpdatePlacedObject, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)MarkRedirectToSelf,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)SimulateRedirectChain, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<72> g_childGroupObjectClass = { &g_colliderClass, 0x3B, 0x23, 0x690, {
    (Fn_Table)InitChildGroupObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyChildGroupObject, (Fn_Table)LoadChildGroupObject, 0,
    0, (Fn_Table)HandleChildGroupNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartChildGroupObject, (Fn_Table)UpdateChildGroupObject, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleChildGroupObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)RunKeyedChildGroupEntry, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)HandleChildGroupObjectContact, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<28> g_entryQueueClass = { &g_objectClass, 0x8F, 0x0, 0x6C, {
    (Fn_Table)InitEntryQueue, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadObjectProperties, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<88> g_playerClass = { &g_turningColliderClass, 0x7, 0xB, 0x2BF0, {
    (Fn_Table)InitPlayer, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlayer, (Fn_Table)UnregisterSwitchedCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopySwitchedCollider, (Fn_Table)LoadPlayer, 0,
    0, (Fn_Table)HandlePlayerNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPlayer, (Fn_Table)UpdatePlayer, (Fn_Table)RecomputePlayerFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)SetPlayerBoundsPoints,
    (Fn_Table)StepPlayer, (Fn_Table)SetPlayerPosition, (Fn_Table)SetTurningColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlayerPose,
    (Fn_Table)BlendPlayerPose, (Fn_Table)DrawPlayer, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdatePlayerBounds, (Fn_Table)SyncPlayerTarget,
    (Fn_Table)CopyTurningColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeTurningColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)CollidePlayerWithObject, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputePlayerSlideRates, (Fn_Table)ResolvePlayerContact, (Fn_Table)ClampPlayerContactLimit, (Fn_Table)PrunePlayerContacts,
    (Fn_Table)ReleasePlayerContacts, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SavePlayerPreviousPosition, (Fn_Table)CapturePlayerPose, (Fn_Table)ApplyPlayerAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)SetPlayerTracked, (Fn_Table)ControlPlayer, (Fn_Table)IsPlayerCameraFree, (Fn_Table)IsPlayerRequestBlocked,
    (Fn_Table)AcceptPlayerRequest, (Fn_Table)GetPlayerRequestPhase, (Fn_Table)StartPlayerEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishPlayerRequest, (Fn_Table)GetPlayerInteractFlags, (Fn_Table)ReceivePlayerNode, (Fn_Table)GetSwitchedColliderTarget,
    (Fn_Table)BuildTurningColliderHeadingMatrix, (Fn_Table)GetPlayerContactMode, (Fn_Table)IsPlayerGroundContact, 0,
} };
extern const ClassDescriptor<28> D_0021B7F8 = { &g_pointObjectClass, 0x80, 0x0, 0x70, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterPointObject, (Fn_Table)UnregisterPointObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyPointObject, (Fn_Table)LoadPointObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartPointObject, 0, 0, 0,
    0, (Fn_Table)ReparentPointObject, (Fn_Table)ConvertPointObjectPosition, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<72> g_standInClass = { &g_childGroupObjectClass, 0x3F, 0x23, 0x6A0, {
    (Fn_Table)InitChildGroupObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyChildGroupObject, (Fn_Table)LoadChildGroupObject, 0,
    0, (Fn_Table)HandleStandInNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartChildGroupObject, (Fn_Table)UpdateChildGroupObject, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepStandIn, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleChildGroupObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestStandInMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)RunKeyedChildGroupEntry, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)StopStandIn, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<72> g_countedColliderClass = { &g_colliderClass, 0x4C, 0x3, 0x560, {
    (Fn_Table)InitCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandleCountedColliderNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartCountedCollider, (Fn_Table)UpdateCountedCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeCountedColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCountedCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleCountedColliderEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, (Fn_Table)CollectCountedColliderContacts,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<28> g_itemKeeperClass = { &g_objectClass, 0x89, 0x0, 0x190, {
    (Fn_Table)InitItemKeeper, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadObjectProperties, 0,
    0, 0, (Fn_Table)SendObjectNotification, (Fn_Table)FindWantedItems,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<100> g_agentClass = { &g_turningColliderClass, 0x8, 0xB, 0xC10, {
    (Fn_Table)InitAgent, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterAgent, (Fn_Table)UnregisterAgent,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyAgent, (Fn_Table)LoadAgent, 0,
    0, (Fn_Table)HandleAgentNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadAgent,
    (Fn_Table)StartAgent, (Fn_Table)UpdateAgent, (Fn_Table)RecomputeTurningColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepAgent, (Fn_Table)SetColliderPosition, (Fn_Table)SetTurningColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetTurningColliderPose,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawAgent, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleAgentObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyTurningColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeTurningColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestAgentMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)CollideAgentWithObject, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeAgentContactValue, (Fn_Table)ResolveTurningColliderContact, (Fn_Table)ClampAgentContactLimit, (Fn_Table)CollectTurningColliderContacts,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestAgentLaunch,
    (Fn_Table)HandleSwitchedColliderActivation, 0, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsAgentRequestBlocked,
    (Fn_Table)AcceptAgentRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
    (Fn_Table)BuildTurningColliderHeadingMatrix, (Fn_Table)GetTurningColliderContactMode, (Fn_Table)IsTurningColliderGroundContact, (Fn_Table)IsAgentFree,
    (Fn_Table)AnswerAgentRosterPoll, (Fn_Table)ChooseAgentState, (Fn_Table)UpdateAgentState, (Fn_Table)LeaveAgentState,
    (Fn_Table)EnterAgentState, (Fn_Table)IsAgentTargetInRange, (Fn_Table)UpdateAgentGoal, (Fn_Table)BuildAgentPath,
    (Fn_Table)RestartAgentClip, (Fn_Table)SteerAgentAlongPath, (Fn_Table)SelectAgentTarget, 0,
} };
extern const ClassDescriptor<100> g_coneAgentClass = { &g_agentClass, 0xA, 0xB, 0xC50, {
    (Fn_Table)InitConeAgent, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterAgent, (Fn_Table)UnregisterAgent,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyAgent, (Fn_Table)LoadAgent, 0,
    0, (Fn_Table)HandleAgentNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadAgent,
    (Fn_Table)StartConeAgent, (Fn_Table)UpdateAgent, (Fn_Table)RecomputeTurningColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepAgent, (Fn_Table)SetColliderPosition, (Fn_Table)SetTurningColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetTurningColliderPose,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawConeAgent, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleAgentObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyTurningColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeTurningColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestAgentMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)CollideAgentWithObject, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeAgentContactValue, (Fn_Table)ResolveTurningColliderContact, (Fn_Table)ClampAgentContactLimit, (Fn_Table)CollectTurningColliderContacts,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestAgentLaunch,
    (Fn_Table)HandleSwitchedColliderActivation, 0, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsAgentRequestBlocked,
    (Fn_Table)AcceptAgentRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
    (Fn_Table)BuildTurningColliderHeadingMatrix, (Fn_Table)GetTurningColliderContactMode, (Fn_Table)IsTurningColliderGroundContact, (Fn_Table)IsConeAgentFree,
    (Fn_Table)AnswerAgentRosterPoll, (Fn_Table)ChooseAgentState, (Fn_Table)UpdateAgentState, (Fn_Table)LeaveAgentState,
    (Fn_Table)EnterAgentState, (Fn_Table)IsAgentTargetInRange, (Fn_Table)UpdateAgentGoal, (Fn_Table)BuildAgentPath,
    (Fn_Table)RestartAgentClip, (Fn_Table)SteerAgentAlongPath, (Fn_Table)SelectAgentTarget, 0,
} };
extern const ClassDescriptor<100> g_companionAgentClass = { &g_agentClass, 0x9, 0xB, 0xD00, {
    (Fn_Table)InitCompanionAgent, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterAgent, (Fn_Table)UnregisterAgent,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyAgent, (Fn_Table)LoadAgent, 0,
    0, (Fn_Table)HandleCompanionAgentNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadAgent,
    (Fn_Table)StartCompanionAgent, (Fn_Table)UpdateCompanionAgent, (Fn_Table)RecomputeTurningColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetCompanionAgentFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepAgent, (Fn_Table)SetColliderPosition, (Fn_Table)SetTurningColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetTurningColliderPose,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawAgent, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleAgentObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyTurningColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeTurningColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestAgentMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)CollideAgentWithObject, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeAgentContactValue, (Fn_Table)ResolveTurningColliderContact, (Fn_Table)ClampAgentContactLimit, (Fn_Table)CollectTurningColliderContacts,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestAgentLaunch,
    (Fn_Table)HandleSwitchedColliderActivation, 0, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsAgentRequestBlocked,
    (Fn_Table)AcceptAgentRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
    (Fn_Table)BuildTurningColliderHeadingMatrix, (Fn_Table)GetTurningColliderContactMode, (Fn_Table)IsTurningColliderGroundContact, (Fn_Table)IsCompanionAgentTargetReachable,
    (Fn_Table)AnswerCompanionAgentRosterPoll, (Fn_Table)ChooseAgentState, (Fn_Table)UpdateAgentState, (Fn_Table)LeaveAgentState,
    (Fn_Table)EnterCompanionAgentState, (Fn_Table)IsCompanionAgentTargetInRange, (Fn_Table)UpdateAgentGoal, (Fn_Table)BuildAgentPath,
    (Fn_Table)RestartAgentClip, (Fn_Table)SteerAgentAlongPath, (Fn_Table)SelectAgentTarget, 0,
} };
extern const ClassDescriptor<72> g_contactTrackerClass = { &g_colliderClass, 0x36, 0x3, 0x860, {
    (Fn_Table)InitContactTracker, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyContactTracker, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartContactTracker, (Fn_Table)CollectTouchingObjects, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyContactTrackerTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestContactTrackerLaunch,
} };
extern const ClassDescriptor<72> D_0021C168 = { &g_contactTrackerClass, 0x37, 0x3, 0x860, {
    (Fn_Table)InitC37, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyContactTracker, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartContactTracker, (Fn_Table)UpdateC37, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyContactTrackerTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestContactTrackerLaunch,
} };
extern const ClassDescriptor<28> D_0021C298 = { &g_transformObjectClass, 0x7B, 0x0, 0x90, {
    (Fn_Table)InitTransformObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)ReadObjectTransformAndTables, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObjectKeepingTransform, (Fn_Table)TransformObjectIntoFrame, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<72> g_flaggedObjectClass = { &g_colliderClass, 0x38, 0x3, 0x5C0, {
    (Fn_Table)InitFlaggedObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyFlaggedObject, (Fn_Table)CollectChildLists, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)ResolveListIds,
    (Fn_Table)StartFlaggedObject, (Fn_Table)UpdateFlaggedObject, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleFlaggedObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<28> g_pointGraphObjectClass = { &g_objectClass, 0x8A, 0x0, 0x58, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadPointGraph, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<48> g_cameraPositionedObjectClass = { &g_placedObjectClass, 0x54, 0x1, 0x2E0, {
    (Fn_Table)InitPlacedObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadPlacedObject, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartCameraPositionedObject, (Fn_Table)MoveObjectToCamera, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<72> g_objectCyclerClass = { &g_colliderClass, 0x40, 0x3, 0x6A0, {
    (Fn_Table)InitObjectCycler, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyObjectCycler, (Fn_Table)LoadObjectCycler, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartObjectCycler, (Fn_Table)UpdateObjectCycler, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetObjectCyclerHandle, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepObjectCycler, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawObjectCycler, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectCyclerObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<48> g_stateNotifierClass = { &g_placedObjectClass, 0x55, 0x1, 0x390, {
    (Fn_Table)InitStateNotifier, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyStateNotifier, (Fn_Table)LoadStateNotifier, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartStateNotifier, (Fn_Table)UpdateStateNotifier, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveStateNotifier,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyStateNotifierScale, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleStateNotifierContact, 0, (Fn_Table)SetStateNotifierState,
} };
extern const ClassDescriptor<48> g_timeRangeNotifierClass = { &g_stateNotifierClass, 0x58, 0x1, 0x3A0, {
    (Fn_Table)InitTimeRangeNotifier, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyStateNotifier, (Fn_Table)LoadStateNotifier, 0,
    0, (Fn_Table)HandleTimeRangeNotifierNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartStateNotifier, (Fn_Table)UpdateTimeRangeNotifier, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveStateNotifier,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyStateNotifierScale, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleStateNotifierContact, 0, (Fn_Table)SetEffectNotifierState,
} };
extern const ClassDescriptor<48> g_soundNotifierClass = { &g_stateNotifierClass, 0x56, 0x1, 0x390, {
    (Fn_Table)InitSoundNotifier, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyStateNotifier, (Fn_Table)LoadStateNotifier, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartStateNotifier, (Fn_Table)UpdateStateNotifier, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveStateNotifier,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyStateNotifierScale, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleStateNotifierContact, 0, (Fn_Table)SetSoundNotifierState,
} };
extern const ClassDescriptor<48> g_saveNotifierClass = { &g_stateNotifierClass, 0x59, 0x1, 0x390, {
    (Fn_Table)InitSaveNotifier, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyStateNotifier, (Fn_Table)LoadStateNotifier, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartStateNotifier, (Fn_Table)UpdateStateNotifier, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveStateNotifier,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyStateNotifierScale, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleStateNotifierContact, 0, (Fn_Table)SetSaveNotifierState,
} };
extern const ClassDescriptor<48> g_deadlineNotifierClass = { &g_stateNotifierClass, 0x5A, 0x1, 0x390, {
    (Fn_Table)InitDeadlineNotifier, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyStateNotifier, (Fn_Table)LoadStateNotifier, 0,
    0, (Fn_Table)HandleDeadlineNotifierNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartDeadlineNotifier, (Fn_Table)UpdateNotifierWorldDeadline, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveStateNotifier,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyStateNotifierScale, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleStateNotifierContact, 0, (Fn_Table)SetDeadlineNotifierState,
} };
extern const ClassDescriptor<48> g_countdownNotifierClass = { &g_stateNotifierClass, 0x57, 0x1, 0x3A0, {
    (Fn_Table)InitCountdownNotifier, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyStateNotifier, (Fn_Table)LoadStateNotifier, 0,
    0, (Fn_Table)HandleCountdownNotifierNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartStateNotifier, (Fn_Table)CountDownNotifierTimer, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveStateNotifier,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyStateNotifierScale, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleStateNotifierContact, 0, (Fn_Table)SetCountdownNotifierState,
} };
extern const ClassDescriptor<48> g_armedStateNotifierClass = { &g_stateNotifierClass, 0x5B, 0x1, 0x390, {
    (Fn_Table)InitArmedStateNotifier, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyStateNotifier, (Fn_Table)LoadStateNotifier, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartStateNotifier, (Fn_Table)UpdateArmedNotifier, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveStateNotifier,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyStateNotifierScale, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleStateNotifierContact, 0, (Fn_Table)SetStateNotifierState,
} };
extern const ClassDescriptor<76> g_objectSetClass = { &g_colliderClass, 0x2C, 0x3, 0x5A0, {
    (Fn_Table)InitObjectSet, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadObjectSet, 0,
    0, (Fn_Table)HandleObjectSetNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadObjectSet,
    (Fn_Table)StartObjectSet, (Fn_Table)UpdateObjectSet, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestObjectSetMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)LatchObjectSetContact, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)GetObjectSetActivationState, (Fn_Table)CollectObjectSet, (Fn_Table)NotifyObjectSetTarget, 0,
} };
extern const ClassDescriptor<76> g_flaggedObjectSetClass = { &g_objectSetClass, 0x2D, 0x3, 0x5B0, {
    (Fn_Table)InitFlaggedObjectSet, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyFlaggedObjectSet, (Fn_Table)LoadObjectSet, 0,
    0, (Fn_Table)HandleObjectSetNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadObjectSet,
    (Fn_Table)StartObjectSet, (Fn_Table)UpdateObjectSet, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestObjectSetMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)LatchObjectSetContact, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)GetFlaggedObjectSetActivationState, (Fn_Table)CollectFlaggedObjectSet, (Fn_Table)NotifyObjectSetTarget, 0,
} };
extern const ClassDescriptor<76> g_numberedItemClass = { &g_objectSetClass, 0x2E, 0x3, 0x5C0, {
    (Fn_Table)InitNumberedItem, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyNumberedItem, (Fn_Table)LoadNumberedItem, 0,
    0, (Fn_Table)HandleObjectSetNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadObjectSet,
    (Fn_Table)StartNumberedItem, (Fn_Table)UpdateNumberedItem, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)SpinNumberedItemTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleNumberedItemObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyNumberedItemPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestObjectSetMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)LatchObjectSetContact, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)GetObjectSetActivationState, (Fn_Table)CollectNumberedItem, (Fn_Table)NotifyObjectSetTarget, 0,
} };
extern const ClassDescriptor<48> g_stateWalkerObjectClass = { &g_placedObjectClass, 0x5C, 0x1, 0x2E0, {
    (Fn_Table)InitPlacedObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadStateWalkerObject, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartStateWalkerObject, (Fn_Table)UpdatePlacedObject, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<48> g_stateWalkerGroupClass = { &g_placedObjectClass, 0x5D, 0x1, 0x330, {
    (Fn_Table)InitPlacedObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadStateWalkerGroup, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartStateWalkerGroup, (Fn_Table)UpdatePlacedObject, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<84> D_0021D1D8 = { &g_switchedColliderClass, 0x17, 0xB, 0x800, {
    (Fn_Table)InitC17Collider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterSwitchedCollider, (Fn_Table)UnregisterSwitchedCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopySwitchedCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandleC17ColliderNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartC17Collider, (Fn_Table)UpdateSwitchedCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)HandleC17ColliderActivation, (Fn_Table)ControlC17Collider, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsSwitchedColliderRequestBlocked,
    (Fn_Table)AcceptSwitchedColliderRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
} };
extern const ClassDescriptor<28> D_0021D338 = { &D_0021C298, 0x7C, 0x0, 0xA0, {
    (Fn_Table)InitTransformObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterC7CObject, (Fn_Table)UnregisterC7CObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)ReadObjectTransformAndTables, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObjectKeepingTransform, (Fn_Table)TransformObjectIntoFrame, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<72> g_objectGathererClass = { &g_colliderClass, 0x41, 0x3, 0x670, {
    (Fn_Table)InitObjectGatherer, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)AddObjectGatherer, (Fn_Table)RemoveObjectGatherer,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyObjectGatherer, (Fn_Table)LoadObjectGatherer, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartObjectGatherer, (Fn_Table)UpdateObjectGatherer, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepObjectGatherer, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyObjectGathererLodObject, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectGathererObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeObjectGathererContactValues, (Fn_Table)ResolveObjectGathererContact, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<48> g_pairControllerClass = { &g_placedObjectClass, 0x5F, 0x1, 0x660, {
    (Fn_Table)InitPairController, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadPlacedObject, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)ResolvePairControllerLinks,
    (Fn_Table)BlendPairControllerPose, (Fn_Table)UpdatePairController, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, (Fn_Table)ShowPairControllerElement, 0,
} };
extern const ClassDescriptor<84> g_walkerColliderClass = { &g_switchedColliderClass, 0x15, 0xB, 0x690, {
    (Fn_Table)InitWalkerCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterSwitchedCollider, (Fn_Table)UnregisterSwitchedCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopySwitchedCollider, (Fn_Table)LoadWalkerCollider, 0,
    0, (Fn_Table)HandleWalkerColliderNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartWalkerCollider, (Fn_Table)UpdateWalkerCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepWalkerCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeWalkerColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeWalkerColliderContactValue, (Fn_Table)ResolveWalkerColliderContact, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)HandleSwitchedColliderActivation, (Fn_Table)ControlWalkerCollider, (Fn_Table)IsWalkerColliderCameraFree, (Fn_Table)IsSwitchedColliderRequestBlocked,
    (Fn_Table)AcceptSwitchedColliderRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
} };
extern const ClassDescriptor<72> g_pairedObjectClass = { &g_colliderClass, 0x42, 0x3, 0x5C0, {
    (Fn_Table)InitPairedObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPairedObject, (Fn_Table)LoadPairedObject, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPairedObject, (Fn_Table)UpdatePairedObject, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandlePairedHit, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<72> g_hitTargetClass = { &g_colliderClass, 0x43, 0x3, 0x5B0, {
    (Fn_Table)InitHitTarget, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyHitTarget, (Fn_Table)LoadHitTarget, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartHitTarget, (Fn_Table)UpdateHitTarget, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepHitTarget, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)ApplyHitTargetHit, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeHitTargetContactValue, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<72> g_soundStateObjectClass = { &g_colliderClass, 0x44, 0x3, 0x570, {
    (Fn_Table)InitSoundStateObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopySoundStateObject, (Fn_Table)LoadSoundStateObject, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartSoundStateObject, (Fn_Table)UpdateSoundStateObject, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<72> g_objectCreatorClass = { &g_colliderClass, 0x45, 0x3, 0x570, {
    (Fn_Table)InitObjectCreator, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadObjectCreator, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartObjectCreator, (Fn_Table)UpdateObjectCreator, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<72> g_pooledObjectClass = { &g_colliderClass, 0x46, 0x3, 0x590, {
    (Fn_Table)InitPooledObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)AddToWorldQueue,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RemoveFromWorldQueue, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPooledObject, (Fn_Table)LoadPooledObject, 0,
    0, (Fn_Table)HandlePooledObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPooledObject, (Fn_Table)UpdatePooledObject, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<74> g_pooledHolderClass = { &g_playerFlaggedColliderClass, 0x23, 0x13, 0x7C0, {
    (Fn_Table)InitPooledHolder, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyMaskedCollider, (Fn_Table)LoadMaskedCollider, 0,
    0, (Fn_Table)HandlePooledHolderNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPooledHolder,
    (Fn_Table)StartPooledHolder, (Fn_Table)UpdatePooledHolder, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleMaskedColliderEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestPooledHolderMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)ReleasePooledHolder, 0,
} };
extern const ClassDescriptor<48> g_scalingVolumeClass = { &g_placedObjectClass, 0x60, 0x1, 0x300, {
    (Fn_Table)InitScalingVolume, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadScalingVolume, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPlacedObject, (Fn_Table)UpdateScalingVolume, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawScalingVolume, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<74> g_contactListObjectClass = { &g_childGroupObjectClass, 0x3C, 0x23, 0x6F0, {
    (Fn_Table)InitContactListObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterContactListObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyChildGroupObject, (Fn_Table)LoadContactListObject, 0,
    0, (Fn_Table)HandleChildGroupNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartChildGroupObject, (Fn_Table)UpdateChildGroupObject, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveContactListObject,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyContactListAttachments, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleChildGroupObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestContactListMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)RunKeyedChildGroupEntry, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)HandleChildGroupObjectContact, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)LaunchContactListObject, 0,
} };
extern const ClassDescriptor<74> g_contactListObjectWithoutGravityClass = { &g_contactListObjectClass, 0x3D, 0x23, 0x710, {
    (Fn_Table)InitContactListObjectWithoutGravity, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterContactListObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyChildGroupObject, (Fn_Table)LoadContactListObject, 0,
    0, (Fn_Table)HandleChildGroupNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartChildGroupObject, (Fn_Table)UpdateChildGroupObject, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveContactListObject,
    (Fn_Table)StepContactListObjectWithoutGravity, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyContactListAttachments, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleChildGroupObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestContactListMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)RunKeyedChildGroupEntry, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)HandleChildGroupObjectContact, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)LaunchContactListObjectWithoutGravity, 0,
} };
extern const ClassDescriptor<74> g_timedContactListObjectClass = { &g_contactListObjectClass, 0x3E, 0x23, 0x710, {
    (Fn_Table)InitContactListObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterContactListObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyChildGroupObject, (Fn_Table)LoadContactListObject, 0,
    0, (Fn_Table)HandleChildGroupNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartChildGroupObject, (Fn_Table)UpdateChildGroupObject, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveTimedContactListObject,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyContactListAttachments, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleChildGroupObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestContactListMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)RunKeyedChildGroupEntry, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)HandleChildGroupObjectContact, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)LaunchTimedContactListObject, 0,
} };
extern const ClassDescriptor<36> g_objectPoolClass = { &g_objectClass, 0x8C, 0x0, 0x170, {
    (Fn_Table)InitObjectPool, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObjectPool,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectPool, (Fn_Table)LoadObjectProperties, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObjectPool, 0, 0, 0,
    (Fn_Table)ClearObjectPoolChoiceIfFlag, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
    (Fn_Table)LoadAnimatorBase, (Fn_Table)BindAnimatorRecord, 0, (Fn_Table)GetAnimatorZeroProgress,
    0, (Fn_Table)FindAnimatorCursor, 0, 0,
} };
extern const CursorAnimatorMethods g_frameRunAnimatorMethods = { (AnimLoad)LoadFrameRunAnimator, (AnimBind)BindFrameRunAnimator, (AnimStep)StepFrameRunAnimator, (AnimProgress)GetFrameRunProgress, 0, (AnimFind)FindAnimatorCursor, 0, 0 };
extern const CursorAnimatorMethods g_framePingPongAnimatorMethods = { (AnimLoad)LoadFramePingPongAnimator, (AnimBind)BindFramePingPongAnimator, (AnimStep)StepFramePingPongAnimator, (AnimProgress)GetFramePingPongProgress, 0, (AnimFind)FindAnimatorCursor, 0, 0 };
extern const CursorAnimatorMethods g_randomJumpAnimatorMethods = { (AnimLoad)LoadRandomJumpAnimator, (AnimBind)BindAnimatorRecord, (AnimStep)StepRandomJumpAnimator, (AnimProgress)GetAnimatorZeroProgress, 0, (AnimFind)FindAnimatorCursor, 0, 0 };
extern const CursorAnimatorMethods g_angleFrameAnimatorMethods = { (AnimLoad)LoadAngleFrameAnimator, (AnimBind)BindAngleFrameAnimator, 0, (AnimProgress)GetAnimatorZeroProgress, (AnimFollow)FollowObjectAngle, (AnimFind)FindAnimatorCursor, 0, 0 };
extern const CursorAnimatorMethods g_scrollAnimatorMethods = { (AnimLoad)LoadScrollAnimator, (AnimBind)BindAnimatorRecord, (AnimStep)StepScrollAnimator, (AnimProgress)GetScrollProgress, 0, (AnimFind)FindAnimatorCursor, 0, 0 };
extern const CursorAnimatorMethods g_circleAnimatorMethods = { (AnimLoad)LoadCircleAnimator, (AnimBind)BindAnimatorRecord, (AnimStep)StepCircleAnimator, (AnimProgress)GetCircleProgress, 0, (AnimFind)FindAnimatorCursor, 0, 0 };
extern const CursorAnimatorMethods g_triangleAnimatorMethods = { (AnimLoad)LoadTriangleAnimator, (AnimBind)BindAnimatorRecord, 0, (AnimProgress)GetAnimatorZeroProgress, (AnimFollow)UpdateTriangleAnimatorCursor, (AnimFind)FindAnimatorCursor, (AnimOutputs)GetTriangleOutputs, 0 };
extern const CursorAnimatorMethods g_crossfadeAnimatorMethods = {
    (AnimLoad)LoadCrossfadeAnimator, (AnimBind)BindCrossfadeAnimator, (AnimStep)StepCrossfadeAnimator, (AnimProgress)GetAnimatorZeroProgress,
    0, (AnimFind)FindCrossfadeCursor, 0, 0,
};
extern const ClassDescriptor<72> g_scaledOffsetObjectClass = { &g_colliderClass, 0x39, 0x3, 0x560, {
    (Fn_Table)InitScaledOffsetObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadScaledOffsetObject, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartScaledOffsetObject, (Fn_Table)UpdateCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, (Fn_Table)ResolveScaledOffsetContact, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<48> g_textureRenderObjectClass = { &g_placedObjectClass, 0x61, 0x1, 0x2F0, {
    (Fn_Table)InitTextureRenderObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadPlacedObject, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPlacedObject, (Fn_Table)UpdatePlacedObject, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)QueuePlacedObjectDraw, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<48> g_stateResetObjectClass = { &g_placedObjectClass, 0x62, 0x1, 0x330, {
    (Fn_Table)InitStateResetObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadPlacedObject, 0,
    0, (Fn_Table)HandleStateResetNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartStateResetObject, (Fn_Table)UpdateStateResetObject, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<100> g_world1BossClass = { &g_coneAgentClass, 0xB, 0xB, 0xCA0, {
    (Fn_Table)InitWorld1Boss, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterAgent, (Fn_Table)UnregisterAgent,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyAgent, (Fn_Table)LoadAgent, 0,
    0, (Fn_Table)HandleAgentNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadAgent,
    (Fn_Table)StartWorld1Boss, (Fn_Table)UpdateAgent, (Fn_Table)RecomputeTurningColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepAgent, (Fn_Table)SetColliderPosition, (Fn_Table)SetTurningColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetTurningColliderPose,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawConeAgent, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleAgentObjectEvent, (Fn_Table)ShowElementWhenMenusClear, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyTurningColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeTurningColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestAgentMayContactExceptKeys, (Fn_Table)CollideColliderParts, (Fn_Table)CollideAgentWithObject, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeAgentContactValue, (Fn_Table)ResolveTurningColliderContact, (Fn_Table)ClampAgentContactLimit, (Fn_Table)CollectTurningColliderContacts,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestAgentLaunch,
    (Fn_Table)HandleSwitchedColliderActivation, 0, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsAgentRequestBlocked,
    (Fn_Table)AcceptAgentRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
    (Fn_Table)BuildTurningColliderHeadingMatrix, (Fn_Table)GetTurningColliderContactMode, (Fn_Table)IsTurningColliderGroundContact, (Fn_Table)IsWorld1BossFree,
    (Fn_Table)AnswerAgentRosterPoll, (Fn_Table)ChooseWorld1BossState, (Fn_Table)UpdateWorld1BossState, (Fn_Table)LeaveAgentState,
    (Fn_Table)EnterWorld1BossState, (Fn_Table)IsWorld1BossTargetInRange, (Fn_Table)UpdateWorld1BossGoal, (Fn_Table)BuildAgentPath,
    (Fn_Table)RestartWorld1BossClip, (Fn_Table)SteerWorld1BossAlongPath, (Fn_Table)SelectAgentTarget, 0,
} };
extern const ClassDescriptor<100> g_world2BossClass = { &g_agentClass, 0xC, 0xB, 0xE50, {
    (Fn_Table)InitWorld2Boss, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterAgent, (Fn_Table)UnregisterAgent,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyAgent, (Fn_Table)LoadWorld2Boss, 0,
    0, (Fn_Table)HandleWorld2BossNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadAgent,
    (Fn_Table)StartWorld2Boss, (Fn_Table)UpdateWorld2Boss, (Fn_Table)RecomputeTurningColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepAgent, (Fn_Table)SetColliderPosition, (Fn_Table)SetTurningColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetTurningColliderPose,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawWorld2Boss, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleAgentObjectEvent, (Fn_Table)ShowWorld2BossBar, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyTurningColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeTurningColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestAgentMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)CollideAgentWithObject, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeAgentContactValue, (Fn_Table)ResolveTurningColliderContact, (Fn_Table)ClampAgentContactLimit, (Fn_Table)CollectTurningColliderContacts,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestAgentLaunch,
    (Fn_Table)HandleSwitchedColliderActivation, 0, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsAgentRequestBlocked,
    (Fn_Table)AcceptAgentRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
    (Fn_Table)BuildTurningColliderHeadingMatrix, (Fn_Table)GetTurningColliderContactMode, (Fn_Table)IsTurningColliderGroundContact, (Fn_Table)IsWorld2BossFree,
    (Fn_Table)AnswerAgentRosterPoll, (Fn_Table)ChooseWorld2BossState, (Fn_Table)UpdateWorld2BossState, (Fn_Table)LeaveWorld2BossState,
    (Fn_Table)EnterWorld2BossState, (Fn_Table)HasWorld2BossClearLine, (Fn_Table)UpdateWorld2BossGoal, (Fn_Table)BuildAgentPath,
    (Fn_Table)RestartAgentClip, (Fn_Table)SteerAgentAlongPath, (Fn_Table)SelectAgentTarget, 0,
} };
extern const ClassDescriptor<100> g_world4BossClass = { &g_agentClass, 0xD, 0xB, 0xC30, {
    (Fn_Table)InitAgent, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterAgent, (Fn_Table)UnregisterAgent,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyAgent, (Fn_Table)LoadAgent, 0,
    0, (Fn_Table)HandleAgentNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadAgent,
    (Fn_Table)StartWorld4Boss, (Fn_Table)UpdateWorld4Boss, (Fn_Table)RecomputeTurningColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepAgent, (Fn_Table)SetColliderPosition, (Fn_Table)SetTurningColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetTurningColliderPose,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawAgent, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleWorld4BossObjectEvent, (Fn_Table)UpdateWorld4BossVisibility, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyTurningColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeTurningColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestAgentMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)CollideAgentWithObject, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeAgentContactValue, (Fn_Table)ResolveTurningColliderContact, (Fn_Table)ClampAgentContactLimit, (Fn_Table)CollectTurningColliderContacts,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestAgentLaunch,
    (Fn_Table)HandleSwitchedColliderActivation, 0, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsAgentRequestBlocked,
    (Fn_Table)AcceptAgentRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
    (Fn_Table)BuildTurningColliderHeadingMatrix, (Fn_Table)GetTurningColliderContactMode, (Fn_Table)IsTurningColliderGroundContact, (Fn_Table)IsWorld4BossFree,
    (Fn_Table)AnswerAgentRosterPoll, (Fn_Table)ChooseAgentState, (Fn_Table)UpdateWorld4BossState, (Fn_Table)LeaveAgentState,
    (Fn_Table)EnterWorld4BossState, (Fn_Table)IsAgentTargetInRange, (Fn_Table)UpdateWorld4BossGoal, (Fn_Table)BuildAgentPath,
    (Fn_Table)RestartAgentClip, (Fn_Table)SteerAgentAlongPath, (Fn_Table)SelectAgentTarget, 0,
} };
extern const ClassDescriptor<84> g_world3BeatPressColliderClass = { &g_switchedColliderClass, 0x1C, 0xB, 0x690, {
    (Fn_Table)InitWorld3BeatPressCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterSwitchedCollider, (Fn_Table)UnregisterSwitchedCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopySwitchedCollider, (Fn_Table)LoadWorld3BeatPressCollider, 0,
    0, (Fn_Table)HandleSwitchedColliderNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartWorld3BeatPressCollider, (Fn_Table)UpdateSwitchedCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetWorld3BeatPressColliderPositionAt, (Fn_Table)GetWorld3BeatPressColliderRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)HandleWorld3BeatPressColliderActivation, (Fn_Table)JudgeWorld3BeatPressInput, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsWorld3BeatPressColliderRequestBlocked,
    (Fn_Table)AcceptWorld3BeatPressColliderRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
} };
extern const ClassDescriptor<100> g_world3BossClass = { &g_agentClass, 0x13, 0xB, 0xCA0, {
    (Fn_Table)InitWorld3Boss, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterWorld3Boss, (Fn_Table)UnregisterWorld3Boss,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyAgent, (Fn_Table)LoadWorld3Boss, 0,
    0, (Fn_Table)HandleWorld3BossNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadAgent,
    (Fn_Table)StartWorld3Boss, (Fn_Table)UpdateWorld3Boss, (Fn_Table)RecomputeTurningColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepAgent, (Fn_Table)SetColliderPosition, (Fn_Table)SetTurningColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetTurningColliderPose,
    (Fn_Table)ApplyWorld3BossTransform, (Fn_Table)DrawWorld3Boss, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleAgentObjectEvent, (Fn_Table)ShowWorld3BossGauge, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyTurningColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeTurningColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestAgentMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)CollideAgentWithObject, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeAgentContactValue, (Fn_Table)ResolveTurningColliderContact, (Fn_Table)ClampAgentContactLimit, (Fn_Table)CollectTurningColliderContacts,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestAgentLaunch,
    (Fn_Table)HandleSwitchedColliderActivation, 0, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsAgentRequestBlocked,
    (Fn_Table)AcceptAgentRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
    (Fn_Table)BuildTurningColliderHeadingMatrix, (Fn_Table)GetTurningColliderContactMode, (Fn_Table)IsTurningColliderGroundContact, (Fn_Table)IsWorld3BossFree,
    (Fn_Table)AnswerAgentRosterPoll, (Fn_Table)ChooseAgentState, (Fn_Table)UpdateWorld3BossState, (Fn_Table)LeaveWorld3BossState,
    (Fn_Table)EnterWorld3BossState, (Fn_Table)IsWorld3BossTargetInRange, (Fn_Table)UpdateWorld3BossGoal, (Fn_Table)BuildAgentPath,
    (Fn_Table)RestartAgentClip, (Fn_Table)SteerAgentAlongPath, (Fn_Table)SelectAgentTarget, 0,
} };
extern const ClassDescriptor<28> g_world3TimelineClass = { &g_objectClass, 0x90, 0x0, 0x48, {
    (Fn_Table)InitWorld3Timeline, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadObjectProperties, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)FindWorld3TimelineTarget, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<48> g_entryTableObjectClass = { &g_placedObjectClass, 0x64, 0x1, 0x340, {
    (Fn_Table)InitEntryTableObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadEntryTable, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartEntryTableObject, (Fn_Table)UpdatePlacedObject, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<72> g_followableObjectClass = { &g_zoneColliderClass, 0x2A, 0x3, 0x7C0, {
    (Fn_Table)InitFollowableObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyZoneCollider, (Fn_Table)LoadZoneCollider, 0,
    0, (Fn_Table)HandleFollowableObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)ResolveFollowableObjectLinks,
    (Fn_Table)StartZoneCollider, (Fn_Table)UpdateZoneCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<72> g_targetFollowerClass = { &g_colliderClass, 0x47, 0x3, 0x5E0, {
    (Fn_Table)InitTargetFollower, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadTargetFollowerRecords, 0,
    0, (Fn_Table)HandleTargetFollowerNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)ResolveTargetFollowerLinks, (Fn_Table)UpdateTargetFollower, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepTargetFollower, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<28> g_listedPointObjectClass = { &g_pointObjectClass, 0x81, 0x0, 0x60, {
    (Fn_Table)InitListedPointObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterListedPointObject, (Fn_Table)UnregisterListedPointObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyListedPointObject, (Fn_Table)LoadPointObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentPointObject, (Fn_Table)ConvertPointObjectPosition, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> D_0021F338 = { &g_pathCurveObjectClass, 0x71, 0x0, 0x5C, {
    (Fn_Table)InitC71Object, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterC71Object, (Fn_Table)UnregisterC71Object,
    (Fn_Table)CloneObject, (Fn_Table)CopyC71Object, (Fn_Table)LoadPathCurveObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartC71Object, 0, 0, 0,
    0, (Fn_Table)ReparentPathCurveObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> g_listedKeepObjectClass = { &g_pathCurveObjectClass, 0x72, 0x0, 0x40, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterListedKeepObject, (Fn_Table)UnregisterListedKeepObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyListedKeepObject, (Fn_Table)LoadPathCurveObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentPathCurveObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> g_oscillatorClass = { &g_objectClass, 0x8D, 0x0, 0x8F0, {
    (Fn_Table)InitOscillator, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadObjectProperties, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<88> g_tintBlendColliderClass = { &g_turningColliderClass, 0x14, 0xB, 0x760, {
    (Fn_Table)InitTintBlendCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterSwitchedCollider, (Fn_Table)UnregisterSwitchedCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopySwitchedCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandleTintBlendColliderNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartTintBlendCollider, (Fn_Table)UpdateTintBlendCollider, (Fn_Table)RecomputeTurningColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepTurningCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetTurningColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetTurningColliderPose,
    (Fn_Table)ApplyTintBlendColliderTint, (Fn_Table)DrawTurningCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyTintBlendColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyTurningColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeTurningColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)CollideTurningColliderWithObject, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeTintBlendColliderContactValue, (Fn_Table)ResolveTurningColliderContact, (Fn_Table)ClampTurningColliderContactLimit, (Fn_Table)CollectTintBlendColliderContacts,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)SetTintBlendColliderTracked, (Fn_Table)ControlTintBlendCollider, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsTintBlendColliderRequestBlocked,
    (Fn_Table)AcceptTintBlendColliderRequest, (Fn_Table)GetTintBlendColliderRequestPhase, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishTintBlendColliderRequest, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
    (Fn_Table)BuildTurningColliderHeadingMatrix, (Fn_Table)GetTurningColliderContactMode, (Fn_Table)IsTurningColliderGroundContact, 0,
} };
extern const ClassDescriptor<84> g_playerLinkedColliderClass = { &g_switchedColliderClass, 0x16, 0xB, 0x660, {
    (Fn_Table)InitPlayerLinkedCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterSwitchedCollider, (Fn_Table)UnregisterSwitchedCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopySwitchedCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandlePlayerLinkedColliderNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPlayerLinkedCollider, (Fn_Table)UpdatePlayerLinkedCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestPlayerLinkedColliderMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)HandlePlayerLinkedColliderActivation, (Fn_Table)ControlPlayerLinkedCollider, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsSwitchedColliderRequestBlocked,
    (Fn_Table)AcceptSwitchedColliderRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartPlayerLinkedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetPlayerLinkedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetPlayerLinkedColliderTarget,
} };
extern const ClassDescriptor<100> g_seekingAgentClass = { &g_agentClass, 0xE, 0xB, 0xC50, {
    (Fn_Table)InitSeekingAgent, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterAgent, (Fn_Table)UnregisterAgent,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyAgent, (Fn_Table)LoadAgent, 0,
    0, (Fn_Table)HandleSeekingAgentNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadAgent,
    (Fn_Table)StartSeekingAgent, (Fn_Table)UpdateAgent, (Fn_Table)RecomputeTurningColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepAgent, (Fn_Table)SetColliderPosition, (Fn_Table)SetTurningColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetTurningColliderPose,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawAgent, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleSeekingAgentObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyTurningColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeTurningColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestAgentMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)CollideAgentWithObject, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeAgentContactValue, (Fn_Table)ResolveTurningColliderContact, (Fn_Table)ClampAgentContactLimit, (Fn_Table)CollectTurningColliderContacts,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestAgentLaunch,
    (Fn_Table)HandleSwitchedColliderActivation, 0, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsSeekingAgentRequestBlocked,
    (Fn_Table)AcceptSeekingAgentRequest, (Fn_Table)GetSeekingAgentStateKind, (Fn_Table)StartSeekingAgentEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
    (Fn_Table)BuildTurningColliderHeadingMatrix, (Fn_Table)GetTurningColliderContactMode, (Fn_Table)IsTurningColliderGroundContact, (Fn_Table)HasAttachedSeekingTarget,
    (Fn_Table)AnswerAgentRosterPoll, (Fn_Table)ChooseAgentState, (Fn_Table)UpdateSeekingAgentState, (Fn_Table)LeaveSeekingAgentState,
    (Fn_Table)EnterSeekingAgentState, (Fn_Table)IsSeekingAgentTargetInRange, (Fn_Table)UpdateSeekingAgentGoal, (Fn_Table)BuildAgentPath,
    (Fn_Table)RestartAgentClip, (Fn_Table)SteerAgentAlongPath, (Fn_Table)SelectAgentTarget, 0,
} };
extern const ClassDescriptor<84> g_gaugeColliderClass = { &g_switchedColliderClass, 0x18, 0xB, 0x6C0, {
    (Fn_Table)InitGaugeCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterSwitchedCollider, (Fn_Table)UnregisterSwitchedCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopySwitchedCollider, (Fn_Table)LoadGaugeCollider, 0,
    0, (Fn_Table)HandleGaugeColliderNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartGaugeCollider, (Fn_Table)UpdateGaugeCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepGaugeCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, (Fn_Table)UpdateGaugeColliderVisibility, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeGaugeColliderContactValue, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyGaugeColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)HandleGaugeColliderActivation, (Fn_Table)ControlGaugeCollider, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsSwitchedColliderRequestBlocked,
    (Fn_Table)AcceptSwitchedColliderRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
} };
extern const ClassDescriptor<100> g_gaugeColliderAgentClass = { &g_agentClass, 0xF, 0xB, 0xC20, {
    (Fn_Table)InitAgent, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterAgent, (Fn_Table)UnregisterAgent,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyAgent, (Fn_Table)LoadAgent, 0,
    0, (Fn_Table)HandleGaugeColliderAgentNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadAgent,
    (Fn_Table)StartGaugeColliderAgent, (Fn_Table)UpdateGaugeColliderAgent, (Fn_Table)RecomputeTurningColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepGaugeColliderAgent, (Fn_Table)SetColliderPosition, (Fn_Table)SetTurningColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetTurningColliderPose,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawAgent, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleAgentObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyTurningColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeTurningColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestAgentMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)CollideAgentWithObject, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeAgentContactValue, (Fn_Table)ResolveTurningColliderContact, (Fn_Table)ClampAgentContactLimit, (Fn_Table)CollectTurningColliderContacts,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestAgentLaunch,
    (Fn_Table)HandleSwitchedColliderActivation, 0, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsAgentRequestBlocked,
    (Fn_Table)AcceptAgentRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
    (Fn_Table)BuildTurningColliderHeadingMatrix, (Fn_Table)GetTurningColliderContactMode, (Fn_Table)IsTurningColliderGroundContact, (Fn_Table)IsGaugeColliderAgentNear,
    (Fn_Table)AnswerAgentRosterPoll, (Fn_Table)ChooseGaugeColliderAgentState, (Fn_Table)UpdateGaugeColliderAgentState, (Fn_Table)LeaveGaugeColliderAgentState,
    (Fn_Table)EnterGaugeColliderAgentState, (Fn_Table)IsGaugeColliderAgentTargetInRange, (Fn_Table)UpdateGaugeColliderAgentGoal, (Fn_Table)BuildAgentPath,
    (Fn_Table)RestartAgentClip, (Fn_Table)SteerAgentAlongPath, (Fn_Table)SelectAgentTarget, 0,
} };
extern const ClassDescriptor<72> g_gaugeCountedObjectClass = { &g_colliderClass, 0x48, 0x3, 0x560, {
    (Fn_Table)InitCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartGaugeCountedObject, (Fn_Table)UpdateCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<72> g_boxColliderClass = { &g_colliderClass, 0x49, 0x3, 0x570, {
    (Fn_Table)InitBoxCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPlacedObject, (Fn_Table)UpdateCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<100> g_worldListedAgentClass = { &g_agentClass, 0x10, 0xB, 0xC20, {
    (Fn_Table)InitAgent, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterWorldListedAgent, (Fn_Table)UnregisterWorldListedAgent,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyWorldListedAgent, (Fn_Table)LoadAgent, 0,
    0, (Fn_Table)HandleAgentNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadAgent,
    (Fn_Table)StartAgent, (Fn_Table)UpdateAgent, (Fn_Table)RecomputeTurningColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepAgent, (Fn_Table)SetColliderPosition, (Fn_Table)SetTurningColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetTurningColliderPose,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawAgent, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleAgentObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyTurningColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeTurningColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestAgentMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)CollideAgentWithObject, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeAgentContactValue, (Fn_Table)ResolveTurningColliderContact, (Fn_Table)ClampAgentContactLimit, (Fn_Table)CollectTurningColliderContacts,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestAgentLaunch,
    (Fn_Table)HandleSwitchedColliderActivation, 0, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsAgentRequestBlocked,
    (Fn_Table)AcceptAgentRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
    (Fn_Table)BuildTurningColliderHeadingMatrix, (Fn_Table)GetTurningColliderContactMode, (Fn_Table)IsTurningColliderGroundContact, (Fn_Table)IsAgentFree,
    (Fn_Table)AnswerAgentRosterPoll, (Fn_Table)ChooseAgentState, (Fn_Table)UpdateAgentState, (Fn_Table)LeaveAgentState,
    (Fn_Table)EnterAgentState, (Fn_Table)IsAgentTargetInRange, (Fn_Table)UpdateAgentGoal, (Fn_Table)BuildAgentPath,
    (Fn_Table)RestartAgentClip, (Fn_Table)SteerAgentAlongPath, (Fn_Table)SelectAgentTarget, 0,
} };
extern const ClassDescriptor<100> g_numberedAgentClass = { &g_worldListedAgentClass, 0x11, 0xB, 0xC30, {
    (Fn_Table)InitNumberedAgent, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterWorldListedAgent, (Fn_Table)UnregisterWorldListedAgent,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyWorldListedAgent, (Fn_Table)LoadAgent, 0,
    0, (Fn_Table)HandleAgentNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadAgent,
    (Fn_Table)StartNumberedAgent, (Fn_Table)UpdateAgent, (Fn_Table)RecomputeTurningColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepAgent, (Fn_Table)SetColliderPosition, (Fn_Table)SetTurningColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetTurningColliderPose,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawAgent, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleNumberedAgentObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyTurningColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeTurningColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestAgentMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)CollideAgentWithObject, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeAgentContactValue, (Fn_Table)ResolveTurningColliderContact, (Fn_Table)ClampAgentContactLimit, (Fn_Table)CollectTurningColliderContacts,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestAgentLaunch,
    (Fn_Table)HandleSwitchedColliderActivation, 0, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsAgentRequestBlocked,
    (Fn_Table)AcceptAgentRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
    (Fn_Table)BuildTurningColliderHeadingMatrix, (Fn_Table)GetTurningColliderContactMode, (Fn_Table)IsTurningColliderGroundContact, (Fn_Table)IsNumberedAgentFree,
    (Fn_Table)AnswerAgentRosterPoll, (Fn_Table)ChooseAgentState, (Fn_Table)UpdateAgentState, (Fn_Table)LeaveAgentState,
    (Fn_Table)EnterNumberedAgentState, (Fn_Table)IsAgentTargetInRange, (Fn_Table)UpdateNumberedAgentGoal, (Fn_Table)BuildAgentPath,
    (Fn_Table)RestartAgentClip, (Fn_Table)SteerAgentAlongPath, (Fn_Table)SelectAgentTarget, 0,
} };
extern const ClassDescriptor<100> g_contactAgentClass = { &g_worldListedAgentClass, 0x12, 0xB, 0xC30, {
    (Fn_Table)InitAgent, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterWorldListedAgent, (Fn_Table)UnregisterWorldListedAgent,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyWorldListedAgent, (Fn_Table)LoadAgent, 0,
    0, (Fn_Table)HandleAgentNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadAgent,
    (Fn_Table)StartAgent, (Fn_Table)UpdateAgent, (Fn_Table)RecomputeTurningColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepAgent, (Fn_Table)SetColliderPosition, (Fn_Table)SetTurningColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetTurningColliderPose,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawAgent, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleContactAgentObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyTurningColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeTurningColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestAgentMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)CollideAgentWithObject, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeAgentContactValue, (Fn_Table)ResolveTurningColliderContact, (Fn_Table)ClampAgentContactLimit, (Fn_Table)CollectTurningColliderContacts,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestAgentLaunch,
    (Fn_Table)HandleSwitchedColliderActivation, 0, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsAgentRequestBlocked,
    (Fn_Table)AcceptAgentRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
    (Fn_Table)BuildTurningColliderHeadingMatrix, (Fn_Table)GetTurningColliderContactMode, (Fn_Table)IsTurningColliderGroundContact, (Fn_Table)IsContactAgentFree,
    (Fn_Table)AnswerAgentRosterPoll, (Fn_Table)ChooseAgentStateByContact, (Fn_Table)UpdateAgentState, (Fn_Table)LeaveAgentState,
    (Fn_Table)EnterContactAgentState, (Fn_Table)IsAgentTargetInRange, (Fn_Table)UpdateAgentGoal, (Fn_Table)BuildAgentPath,
    (Fn_Table)RestartAgentClip, (Fn_Table)SteerAgentAlongPath, (Fn_Table)SelectAgentTarget, 0,
} };
extern const ClassDescriptor<48> g_gaugeManagerClass = { &g_placedObjectClass, 0x68, 0x1, 0x6A0, {
    (Fn_Table)InitGaugeManager, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadPlacedObject, 0,
    0, (Fn_Table)HandleGaugeManagerNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)BlendParamSets, (Fn_Table)UpdateGaugeManager, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, (Fn_Table)ShowGaugeManagerDisplays, 0,
} };
extern const ClassDescriptor<84> g_pathFollowerClass = { &g_switchedColliderClass, 0x19, 0xB, 0xBB0, {
    (Fn_Table)InitPathFollower, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterSwitchedCollider, (Fn_Table)UnregisterSwitchedCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopySwitchedCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandlePathFollowerNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPathFollower, (Fn_Table)UpdatePathFollower, (Fn_Table)RecomputePathFollowerFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepPathFollower, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPathFollower, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdatePathFollowerAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, (Fn_Table)UpdatePathFollowerScreenElements, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdatePathFollowerBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)CollidePathFollowerWithObject, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputePathFollowerContactValue, 0, 0, 0,
    (Fn_Table)ReleasePathFollowerContacts, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CapturePathFollowerPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)HandlePathFollowerActivation, (Fn_Table)ControlPathFollower, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsSwitchedColliderRequestBlocked,
    (Fn_Table)AcceptSwitchedColliderRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartPathFollowerEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
} };
extern const ClassDescriptor<84> g_world5ModeColliderClass = { &g_switchedColliderClass, 0x1B, 0xB, 0x710, {
    (Fn_Table)InitWorld5ModeCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterSwitchedCollider, (Fn_Table)UnregisterSwitchedCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopySwitchedCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandleWorld5ModeColliderNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartWorld5ModeCollider, (Fn_Table)UpdateWorld5ModeCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveWorld5ModeCollider,
    (Fn_Table)StepWorld5ModeCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyWorld5ModeColliderTint, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)HandleWorld5ModeColliderActivation, (Fn_Table)ControlWorld5ModeCollider, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsWorld5ModeColliderRequestBlocked,
    (Fn_Table)AcceptWorld5ModeColliderRequest, (Fn_Table)HasWorld5ModeColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishWorld5ModeCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
} };
extern const ClassDescriptor<72> g_world5BossClass = { &g_colliderClass, 0x4A, 0x3, 0x620, {
    (Fn_Table)InitWorld5Boss, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartWorld5Boss, (Fn_Table)UpdateWorld5Boss, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleWorld5BossEvent, (Fn_Table)ShowWorld5BossBar, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<72> g_countdownColliderClass = { &g_colliderClass, 0x4B, 0x3, 0x570, {
    (Fn_Table)InitWorld5Countdown, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartWorld5Countdown, (Fn_Table)UpdateWorld5Countdown, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleWorld5CountdownObjectEvent, (Fn_Table)UpdateWorld5CountdownVisibility, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<74> D_00220958 = { &g_playerFlaggedColliderClass, 0x24, 0x13, 0x6F0, {
    (Fn_Table)InitC24Object, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyMaskedCollider, (Fn_Table)LoadMaskedCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartC24Object, (Fn_Table)UpdateC24Object, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveC24Object,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleMaskedColliderEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)HandleMaskedColliderActivation, 0,
} };
extern const ClassDescriptor<84> g_modeWalkerObjectClass = { &g_pathFollowerClass, 0x1A, 0xB, 0xC10, {
    (Fn_Table)InitModeWalkerObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterSwitchedCollider, (Fn_Table)UnregisterSwitchedCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopySwitchedCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandleModeWalkerNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartModeWalkerObject, (Fn_Table)UpdateModeWalkerObject, (Fn_Table)RecomputeModeWalker, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepPathFollower, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyModeWalkerTint, (Fn_Table)DrawPathFollower, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdatePathFollowerAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, (Fn_Table)UpdatePathFollowerScreenElements, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdatePathFollowerBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)CollidePathFollowerWithObject, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputePathFollowerContactValue, 0, 0, (Fn_Table)ExtractModeWalkerContacts,
    (Fn_Table)ReleasePathFollowerContacts, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureModeWalkerTarget, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)HandleModeWalkerActivation, (Fn_Table)ControlModeWalker, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsModeWalkerRequestBlocked,
    (Fn_Table)AcceptModeWalkerRequest, (Fn_Table)HasModeWalkerAcceptedRequest, (Fn_Table)StartPathFollowerEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishModeWalker, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
} };
extern const T217D_Vt g_spinningSpriteElementMethods = { (ElementIntFn)InitScreenElement, (ElementFn)SetupScreenElementText, (ElementFn)UpdateScreenElementSlide, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawSpinningSpriteElement, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const ClassDescriptor<28> D_00220C40 = { &g_objectClass, 0x91, 0x0, 0x60, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadObjectProperties, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<84> g_hitCountColliderClass = { &g_switchedColliderClass, 0x1D, 0xB, 0x760, {
    (Fn_Table)InitHitCountCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterSwitchedCollider, (Fn_Table)UnregisterSwitchedCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopySwitchedCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandleSwitchedColliderNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartHitCountCollider, (Fn_Table)UpdateHitCountCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepHitCountCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, (Fn_Table)ShowHitCountColliderCounters, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)NoteHitCountColliderContact, (Fn_Table)ResolveHitCountColliderContact, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)HandleSwitchedColliderActivation, (Fn_Table)ControlHitCountCollider, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsHitCountColliderRequestBlocked,
    (Fn_Table)AcceptHitCountColliderRequest, (Fn_Table)HasHitCountColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishHitCountCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
} };
extern const ClassDescriptor<72> D_00220E20 = { &g_colliderClass, 0x4, 0x3, 0x550, {
    (Fn_Table)InitCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPlacedObject, (Fn_Table)UpdateCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueueModelPartDraws, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<48> g_idLinkedObjectClass = { &g_placedObjectClass, 0x66, 0x1, 0x340, {
    (Fn_Table)InitIdLinkedObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadPlacedObject, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartIdLinkedObject, (Fn_Table)UpdatePlacedObject, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<48> g_warpPageClass = { &g_placedObjectClass, 0x67, 0x1, 0x570, {
    (Fn_Table)InitPlacedObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadPlacedObject, 0,
    0, (Fn_Table)HandleWarpPageNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadWarpPage,
    (Fn_Table)StartWarpPage, (Fn_Table)UpdateWarpPage, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyWarpPageTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const T217D_Vt g_mapScreenListMethods = { (ElementIntFn)InitScreenElement, (ElementFn)InitWarpMenu, (ElementFn)UpdateScreenElementSlide, (ElementIntFn)SetWarpMenuOpen, (ElementPadFn)HandleWarpMenuInput, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawWarpMenu, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const ClassDescriptor<48> g_partHolderObjectClass = { &g_placedObjectClass, 0x6A, 0x1, 0x300, {
    (Fn_Table)InitPlacedObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadPlacedObject, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)CallFlaggedParts, (Fn_Table)UpdatePlacedObject, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<48> g_currentPlacedObjectClass = { &g_placedObjectClass, 0x69, 0x1, 0x350, {
    (Fn_Table)InitPlacedObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadPlacedObject, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)BecomeCurrentObject, (Fn_Table)UpdatePlacedObject, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const T217D_Vt g_selectionCaptionMethods = { (ElementIntFn)InitScreenElement, (ElementFn)InitSelectionCaption, (ElementFn)UpdateSelectionCaption, (ElementIntFn)SetSelectionCaptionOpen, (ElementPadFn)HandleSelectionCaptionInput, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawSelectionCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt g_gridSelectorMethods = { (ElementIntFn)InitScreenElement, (ElementFn)InitGridSelector, (ElementFn)UpdateScreenElementSlide, (ElementIntFn)SetGridSelectorOpen, (ElementPadFn)HandleGridSelectorInput, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawGridSelector, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt g_timerCaptionMethods = { (ElementIntFn)InitScreenElement, (ElementFn)InitCommentaryPromptElement, (ElementFn)UpdateBestTimeState, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawFramedText, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const ClassDescriptor<48> g_codeChecksumClass = { &g_placedObjectClass, 0x6B, 0x1, 0x6E0, {
    (Fn_Table)InitCodeChecksum, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterPlacedObject, (Fn_Table)UnregisterPlacedObject,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyPlacedObject, (Fn_Table)LoadPlacedObject, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartPlacedObject, (Fn_Table)UpdateCodeChecksum, (Fn_Table)RecomputePlacedObjectFrame, (Fn_Table)ComputePlacedObjectWorldFrame,
    (Fn_Table)SetPlacedObjectFrozen, (Fn_Table)ReparentPlacedObject, (Fn_Table)ReframePlacedObject, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MovePlacedObject,
    (Fn_Table)BeginPlacedObjectMove, (Fn_Table)SetPlacedObjectPosition, (Fn_Table)SetPlacedObjectRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetPlacedObjectVelocity, (Fn_Table)SetPlacedObjectSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawPlacedObject, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)TestOtherFlagged, 0, 0,
} };
extern const ClassDescriptor<28> g_worldClass = { &g_objectClass, 0x6C, 0x0, 0x2360, {
    (Fn_Table)InitWorldPools, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadWorld, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, (Fn_Table)UpdateWorld, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> g_cameraClass = { &g_objectClass, 0x6D, 0x0, 0x590, {
    (Fn_Table)InitCamera, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadObjectProperties, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
