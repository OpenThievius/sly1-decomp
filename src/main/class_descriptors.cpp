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
typedef void (*PathM03)(PathCurve* self, s32 idx, void* a2, s32 a3, void* a4, s32 a5);
typedef void (*PathTransform)(PathCurve* self, void* a, void* b);
typedef f32 (*PathArcAt)(PathCurve* self, f32 t);
typedef f32 (*PathTimeAt)(PathCurve* self, f32 t);
typedef f32 (*PathLast)(PathCurve* self);
typedef f32 (*PathFill)(PathCurve* self);
typedef void (*PathM10)(PathCurve* self, void* a1, void* a2, void* a3, void* a4, f32* out0, f32* out1);
typedef void (*PathM11)(PathCurve* self, f32 t, void* a1, void* a2, f32* a3, f32* a4, f32* a5, f32* a6);

void ApplyObjectClassDefaults();
void EvaluateNoPositionCurve();
void GetNoPositionCurveTimes();
void EvaluateNoRotationCurve();
void GetNoRotationCurve();
void GetNoRotationCurveTimes();
void EvaluateNoScaleCurve();
void GetNoScaleCurveTimes();
void EvaluateNoWeightCurve();
void GetNoWeightCurveTimes();
void ReadTangentWeightCurve();
void EvaluateTangentWeightCurve();
void GetTangentWeightCurveTimes();
void ReadControlPointWeightCurve();
void EvaluateControlPointWeightCurve();
void GetControlPointWeightCurveTimes();
void EvaluateLinearWeightCurve();
void ReadLinearWeightCurve();
void GetLinearWeightCurveTimes();
void EvaluateAxisPositionCurve();
void ReadAxisPositionCurve();
void GetAxisPositionCurveTimes();
void EvaluateVectorKeyPositionCurve();
void ReadVectorKeyPositionCurve();
void GetVectorKeyPositionCurveTimes();
void EvaluateAxisRotationCurve();
void* GetAxisRotationCurve();
void ReadAxisRotationCurve();
void GetAxisRotationCurveKeyTimes();
void EvaluateKeyedRotationCurve();
void GetKeyedRotationCurve();
void ReadKeyedRotationCurve();
void GetKeyedRotationCurveKeyTimes();
void EvaluateAxisScaleCurve();
void ReadAxisScaleCurve();
void GetAxisScaleCurveKeyTimes();
void EvaluateKeyedScaleCurve();
void ReadKeyedScaleCurve();
void GetKeyedScaleCurveKeyTimes();
void EvaluateBlendedPositionCurve();
void EvaluateBlendedRotationCurve();
void EvaluateAngleBlendCurve();
void EvaluateValueBlendCurve();
void CopyPoseSource();
void InitPoseSource();
void ReleasePoseSource();
void GetOwnerPosition();
void GetOwnerRotation();
void GetOwnerValue();
void GetIdentityMatrix();
f32 GetOwnerIndexedValue();
void GetPlacedObjectPositionAt();
void GetPlacedObjectRotationAt();
void InitSnapshotPoseSource();
void GetSnapshotPosition();
void GetSnapshotRotation();
void GetSnapshotValue();
void GetSnapshotMatrix();
f32 GetSnapshotIndexedValue();
void InitLinkedPoseSource();
void GetLinkedPosition();
void GetLinkedRotation();
void GetLinkedValue();
void GetLinkedMatrix();
f32 GetLinkedIndexedValue();
void InitIdentityPoseSource();
void GetIdentityPosePosition();
void GetIdentityPoseRotation();
void GetNextPoseSourceValue();
void GetIdentityPoseMatrix();
f32 GetIdentityPoseIndexedValue();
void InitAimPoseSource();
void GetAimPoseRotation();
void ReleaseTrackPoseSource();
void CopyTrackPoseSource();
void GetTrackPosition();
void GetTrackRotation();
void GetTrackValue();
void GetTrackScaleMatrix();
f32 GetTrackIndexedValue();
void ReleaseCountedObject();
void InitStateTrigger();
void StartStateTrigger();
void CopyStateTrigger();
void UpdateStateTrigger();
void InitPlacedObject();
void AttachPlacedObject();
void RegisterPlacedObject();
void DetachPlacedObject();
void UnregisterPlacedObject();
void ReparentPlacedObject();
void ReframePlacedObject();
void PostLoadPlacedObject();
void StartPlacedObject();
void UpdatePlacedObject();
void RecomputePlacedObjectFrame();
void ComputePlacedObjectWorldFrame();
void BeginPlacedObjectMove();
void MovePlacedObject();
void ApplyPlacedObjectTransform();
void DrawPlacedObject();
void QueuePlacedObjectModelParts();
void ClonePlacedObject();
void CopyPlacedObject();
void HandlePlacedObjectNotification();
void SetPlacedObjectPosition();
void SetPlacedObjectRotation();
void SetPlacedObjectVelocity();
void SetPlacedObjectSpin();
void CopyPlacedObjectFrame();
void LoadPlacedObject();
void ApplyObjectFrameOffsetToPose();
void RemoveObjectFrameOffsetFromPose();
void ChooseActiveAttachments();
s32 TestOtherFlagged();
void InitCodeChecksum();
void UpdateCodeChecksum();
void InitAnimation();
void LoadAnimation();
void CopyAnimation();
void StartClampedKinematicValue();
void SkipAnimationPlayerLoad();
void SkipAnimationPlayerStart();
void SkipAnimationPlayerCopy();
void InitIdFilterObject();
void CopyIdFilterObject();
void StartIdFilterObject();
void UpdateIdFilterObject();
s32 TestIdFilterMatch();
void HandleIdFilterObjectContact();
void InitTextPanel();
void SetupTextPanel();
void SetTextPanelMode();
void UpdatePanelStick();
void SetTextPanelOpen();
void ResetTextPanel();
void SetTextPanelText();
f32 GetTextPanelSlideInTime();
f32 GetTextPanelSlideOutTime();
void DrawTextPanel();
void ChooseTextPanelState();
s32 EndTextPanelState();
void InitWorldListedObject();
void LeaveWorldLists();
void ReleaseWorldListedObject();
void UpdateWorldListedObject();
void CopyWorldListedObject();
void MoveWorldListedObject();
void SubmitWorldListedObjectBlock();
void InitChildGroupObject();
void LoadChildGroupObject();
void CopyChildGroupObject();
void StartChildGroupObject();
void HandleChildGroupNotification();
void UpdateChildGroupObject();
void RunKeyedChildGroupEntry();
void HandleChildGroupObjectContact();
s32 HandleChildGroupObjectEvent();
void InitMaskedCollider();
void LoadMaskedCollider();
void CopyMaskedCollider();
void StartMaskedCollider();
void UpdateMaskedCollider();
s32 HandleMaskedColliderEvent();
void HandleMaskedColliderActivation();
void UpdateTimedState();
void HandleTimedStateNotification();
s32 TestTimedStateContact();
void InitPlayerFlaggedCollider();
void InitMassScalingCollider();
void LatchContactObject();
void LatchAcceptedSwitchedCollider();
void UpdateLatchedSwitchCollider();
void InitTriggerZone();
void LoadTriggerZone();
void StartTriggerZone();
void CopyTriggerZone();
void StepTriggerZone();
void ReleaseTriggerZoneContacts();
void UpdateTriggerZone();
s32 HandleTriggerZoneEvent();
void InitZoneCollider();
void LoadZoneCollider();
void StartZoneCollider();
void CopyZoneCollider();
void UpdateZoneCollider();
void ReadObjectTransformAndTables();
void InitFlaggedObject();
void CollectChildLists();
void ResolveListIds();
void StartFlaggedObject();
void CopyFlaggedObject();
void UpdateFlaggedObject();
s32 HandleFlaggedObjectEvent();
void InitCamera();
void InitScaledOffsetObject();
void LoadScaledOffsetObject();
void StartScaledOffsetObject();
void ResolveScaledOffsetContact();
void InitStateNotifier();
void LoadStateNotifier();
void CopyStateNotifier();
void StartStateNotifier();
void MoveStateNotifier();
s32 HandleStateNotifierContact();
void UpdateStateNotifier();
void ApplyStateNotifierScale();
void SetStateNotifierState();
void InitTimeRangeNotifier();
void HandleTimeRangeNotifierNotification();
void UpdateTimeRangeNotifier();
void SetEffectNotifierState();
void InitSoundNotifier();
void SetSoundNotifierState();
void InitSaveNotifier();
void SetSaveNotifierState();
void InitDeadlineNotifier();
void StartDeadlineNotifier();
void HandleDeadlineNotifierNotification();
void UpdateNotifierWorldDeadline();
void SetDeadlineNotifierState();
void InitCountdownNotifier();
void HandleCountdownNotifierNotification();
void CountDownNotifierTimer();
void SetCountdownNotifierState();
void InitArmedStateNotifier();
void UpdateArmedNotifier();
void UpdateIdleCameraController();
void ActivateTargetCameraController();
void UpdateTargetCameraController();
void DeactivateTargetCameraController();
void ActivateFrameCameraController();
void UpdateFrameCameraController();
void ActivateValueCameraController();
void DeactivateValueCameraController();
void UpdateValueCameraController();
void InitItemColumn();
void SetupItemColumn();
void UpdateItemColumn();
void UpdateItemColumnSlide();
void DrawItemColumn();
void RegisterWorldListedAgent();
void UnregisterWorldListedAgent();
void CopyWorldListedAgent();
void InitNumberedAgent();
void StartNumberedAgent();
void UpdateNumberedAgentGoal();
s32 IsNumberedAgentFree();
s32 HandleNumberedAgentObjectEvent();
void EnterNumberedAgentState();
s32 ChooseAgentStateByContact();
s32 IsContactAgentFree();
s32 HandleContactAgentObjectEvent();
void EnterContactAgentState();
void InitGaugeManager();
void BlendParamSets();
void UpdateGaugeManager();
void ShowGaugeManagerDisplays();
void HandleGaugeManagerNotification();
f32 GetBaseCurveLengthAtTime();
f32 GetBaseCurveTimeAtLength();
f32 GetPathCurveEndTime();
f32 GetPathCurveEndLength();
void ReadPathCurve();
void SamplePathCurveAtTime();
void SamplePathCurveAtLength();
void DrawPathCurveSegment();
void TransformPathCurvePoints();
f32 GetPathCurveLengthAtTime();
f32 GetPathCurveTimeAtLength();
f32 FillPathCurveLengths();
void FindPathCurveNearestPoint();
void ProjectOntoPathCurveNearTime();
void ProjectOntoPathCurveNearLength();
void ReadSplinePathCurve();
void SampleSplinePathAtTime();
void SampleSplinePathAtLength();
void DrawSplinePathSegment();
void TransformSplinePathPoints();
f32 GetSplineLengthAtTime();
f32 GetSplineTimeAtLength();
void FillSplinePathLengths();
void FindSplinePathNearestPoint();
void FindSplinePathNearestTime();
void ProjectOntoSplinePathNearLength();
void InitPooledObject();
void RemoveFromWorldQueue();
void AddToWorldQueue();
void CopyPooledObject();
void LoadPooledObject();
void HandlePooledObjectNotification();
void StartPooledObject();
void UpdatePooledObject();
void InitPooledHolder();
void HandlePooledHolderNotification();
void PostLoadPooledHolder();
void StartPooledHolder();
void UpdatePooledHolder();
s32 TestPooledHolderMayContact();
void ReleasePooledHolder();
void InitStepSequence();
void LoadStepSequence();
void StartStepSequence();
void UpdateStepSequence();
void HandleStepSequenceNotification();
void InitTextureRenderObject();
void QueuePlacedObjectDraw();
void InitEffectSpawner();
void LoadEffectSpawner();
void CopyEffectSpawner();
void ResolveEffectSpawnerLinks();
void StartEffectSpawner();
void ReleaseEffectSpawnerHeld();
void UpdateEffectSpawner();
void StartMemberObject();
void SendMemberObjectMessage();
void LoadGroupMembers();
void CopyGroupMembers();
void ResolveGroupMembers();
void BroadcastMessageToMembers();
void InitRecordMember();
void LoadRecordMember();
void CopyRecordMember();
void ResolveRecordMemberTargets();
void SendRecordMemberMessage();
void InitHoldingMember();
void ResolveHoldingMemberTargets();
void ReleaseHeldObject();
void SendMessageAfterDelay();
void LoadCrossfadeAnimator();
void BindCrossfadeAnimator();
void StepCrossfadeAnimator();
void* FindCrossfadeCursor();
void InitScalingVolume();
void LoadScalingVolume();
void UpdateScalingVolume();
void DrawScalingVolume();
void InitObjectCycler();
void LoadObjectCycler();
void CopyObjectCycler();
void SetObjectCyclerHandle();
void StartObjectCycler();
void StepObjectCycler();
void UpdateObjectCycler();
void DrawObjectCycler();
s32 HandleObjectCyclerObjectEvent();
void SetPlacedObjectFrozen();
void SetColliderFrozen();
void ResolveLookupIds();
void UpdateLinkConstraint();
void UpdateAttachmentFrames();
void InitConeAgent();
void StartConeAgent();
void DrawConeAgent();
s32 IsConeAgentFree();
void InitTargetCurve();
void RegisterTargetCurve();
void UnregisterTargetCurve();
void PostLoadTargetCurve();
void CopyTargetCurve();
void InitTargetPoint();
void RegisterTargetPoint();
void UnregisterTargetPoint();
void PostLoadTargetPoint();
void CopyTargetPoint();
void InitListedCollisionPart();
void LoadListedCollisionPart();
void AddToPartList();
void RemoveFromPartList();
void CopyKeepingListLink();
s32 TestListedCollisionPartMayContact();
void StepListedCollisionPart();
void CallFlaggedParts();
void BecomeCurrentObject();
void InitSelectionCaption();
void UpdateSelectionCaption();
void HandleSelectionCaptionInput();
void SetSelectionCaptionOpen();
void DrawSelectionCaption();
void InitGridSelector();
void HandleGridSelectorInput();
void SetGridSelectorOpen();
void DrawGridSelector();
void InitC76Object();
void LoadC76Object();
void DrawC35Collider();
void DrawC52Object();
void InitTargetFollower();
void LoadTargetFollowerRecords();
void ResolveTargetFollowerLinks();
void StepTargetFollower();
void UpdateTargetFollower();
void HandleTargetFollowerNotification();
void InitEntryTableObject();
void LoadEntryTable();
void StartEntryTableObject();
void InitFollowableObject();
void ResolveFollowableObjectLinks();
void HandleFollowableObjectNotification();
void InitPlayer();
void LoadPlayer();
void StartPlayer();
void StepPlayer();
void ComputePlayerSlideRates();
void ClampPlayerContactLimit();
void ReleasePlayerContacts();
s32 IsPlayerGroundContact();
void ResolvePlayerContact();
void HandlePlayerNotification();
void BlendPlayerPose();
void RecomputePlayerFrame();
void DrawPlayer();
void PrunePlayerContacts();
void SavePlayerPreviousPosition();
void SetPlayerBoundsPoints();
void UpdatePlayerBounds();
void CollidePlayerWithObject();
s32 GetPlayerContactMode();
void CapturePlayerPose();
void SetPlayerTracked();
void ControlPlayer();
void UpdatePlayer();
s32 IsPlayerCameraFree();
void StartPlayerEffect();
void GetPlayerInteractFlags();
void ReceivePlayerNode();
void SetPlayerPosition();
void RegisterPlayer();
void InitModeCollider();
void StartModeCollider();
void StepModeCollider();
void MoveModeCollider();
void UpdateModeCollider();
void ControlModeCollider();
void FinishModeCollider();
void HandleModeColliderActivation();
void ApplyModeColliderTint();
s32 IsModeColliderRequestBlocked();
s32 AcceptModeColliderRequest();
void HandleModeColliderNotification();
s32 HasModeColliderAcceptedRequest();
void InitGaugeModeObject();
void StartGaugeModeObject();
void UpdateGaugeModeObject();
void ShowGaugeModeObjectBar();
s32 HandleGaugeModeObjectEvent();
void InitCountdown();
void StartCountdown();
void UpdateCountdown();
void UpdateCountdownVisibility();
s32 HandleCountdownObjectEvent();
void InitEntryQueue();
void RegisterPointObject();
void UnregisterPointObject();
void CopyPointObject();
void StartPointObject();
void InitColoredTriangles();
void LoadColoredTriangles();
void RegisterListedKeepObject();
void UnregisterListedKeepObject();
void CopyListedKeepObject();
void InitModeWalkerObject();
void StartModeWalkerObject();
void ControlModeWalker();
void UpdateModeWalkerObject();
void RecomputeModeWalker();
void HandleModeWalkerActivation();
void ApplyModeWalkerTint();
void CaptureModeWalkerTarget();
s32 IsModeWalkerRequestBlocked();
s32 HasModeWalkerAcceptedRequest();
void FinishModeWalker();
s32 AcceptModeWalkerRequest();
void HandleModeWalkerNotification();
void ExtractModeWalkerContacts();
void DrawSpinningSpriteElement();
void InitC24Object();
void StartC24Object();
void UpdateC24Object();
void MoveC24Object();
void InitObject();
void StartObject();
void AddObjectToParentList();
void AttachObject();
void RegisterObject();
void RemoveObjectFromParentList();
void DetachObject();
void UnregisterObject();
void ReparentObject();
void CloneObject();
void CopyObjectData();
void AddObjectCallback();
void RemoveObjectCallback();
void AddObjectListener();
void RemoveObjectListener();
void SendObjectNotification();
void LoadObjectProperties();
void InitConeVolume();
void RefreshConeVolume();
void RegisterConeVolume();
void UnregisterConeVolume();
void CopyConeVolume();
void InitAim();
void SwitchAimByTargetDistance();
void GetAimRotation();
void CollideColliderParts();
void InitGaugeAgent();
void LoadGaugeAgent();
void StartGaugeAgent();
void DrawGaugeAgent();
s32 HasGaugeAgentClearLine();
s32 IsGaugeAgentFree();
void EnterGaugeAgentState();
s32 ChooseGaugeAgentState();
void UpdateGaugeAgent();
void ShowGaugeAgentBar();
void UpdateGaugeAgentGoal();
void UpdateGaugeAgentState();
void LeaveGaugeAgentState();
void HandleGaugeAgentNotification();
void InitContactListObject();
void LoadContactListObject();
void UnregisterContactListObject();
void MoveContactListObject();
void LaunchContactListObject();
void ApplyContactListAttachments();
s32 TestContactListMayContact();
void InitContactListObjectWithoutGravity();
void LaunchContactListObjectWithoutGravity();
void StepContactListObjectWithoutGravity();
void LaunchTimedContactListObject();
void MoveTimedContactListObject();
void InitBoxCollider();
void QueueModelPartDraws();
void InitSeekingAgent();
void StartSeekingAgent();
void EnterSeekingAgentState();
void LeaveSeekingAgentState();
void UpdateSeekingAgentGoal();
void UpdateSeekingAgentState();
s32 IsSeekingAgentRequestBlocked();
s32 AcceptSeekingAgentRequest();
s32 HandleSeekingAgentObjectEvent();
s32 HasAttachedSeekingTarget();
s32 IsSeekingAgentTargetInRange();
void StartSeekingAgentEffect();
s32 GetSeekingAgentStateKind();
void HandleSeekingAgentNotification();
void LoadPointGraph();
void InitTargetVector();
void RegisterTargetVector();
void UnregisterTargetVector();
void StartTargetVector();
void CopyTargetVector();
void LoadPointObject();
void ReparentPointObject();
s32 ConvertPointObjectPosition();
void LoadTextPointObject();
void InitSwitchedCollider();
void CopySwitchedCollider();
void HandleSwitchedColliderNotification();
void HandleSwitchedColliderActivation();
void CaptureSwitchedColliderPose();
s32 IsSwitchedColliderCameraFree();
s32 IsSwitchedColliderRequestBlocked();
s32 AcceptSwitchedColliderRequest();
s32 HasSwitchedColliderAcceptedRequest();
void StartSwitchedColliderEffect();
void SetSwitchedColliderMode();
void RegisterSwitchedCollider();
void UnregisterSwitchedCollider();
void GetSwitchedColliderInteractFlags();
void ShowTypedTextCaptionBox();
void UpdateSwitchedCollider();
void FinishSwitchedCollider();
void* GetSwitchedColliderTarget();
void InitPauseMenu();
void SetPauseMenuOpen();
void UpdatePauseMenu();
void SetPauseMenuMode();
void ShowPauseMenu();
void HidePauseMenu();
void DrawPauseMenu();
void InitObjectGroup();
void LoadObjectGroup();
void CopyObjectGroup();
void StartObjectGroup();
void InitGaugeCollider();
void LoadGaugeCollider();
void StartGaugeCollider();
void StepGaugeCollider();
void UpdateGaugeCollider();
void HandleGaugeColliderActivation();
void ControlGaugeCollider();
void UpdateGaugeColliderVisibility();
void ComputeGaugeColliderContactValue();
void ApplyGaugeColliderAttachedSetContact();
void HandleGaugeColliderNotification();
void StartGaugeColliderAgent();
void StepGaugeColliderAgent();
s32 ChooseGaugeColliderAgentState();
void UpdateGaugeColliderAgentGoal();
void LeaveGaugeColliderAgentState();
void EnterGaugeColliderAgentState();
void UpdateGaugeColliderAgentState();
void HandleGaugeColliderAgentNotification();
void UpdateGaugeColliderAgent();
u32 IsGaugeColliderAgentTargetInRange();
s32 IsGaugeColliderAgentNear();
void StartGaugeCountedObject();
void InitObjectSet();
void LoadObjectSet();
void PostLoadObjectSet();
void StartObjectSet();
void UpdateObjectSet();
void CollectObjectSet();
void NotifyObjectSetTarget();
s32 GetObjectSetActivationState();
void HandleObjectSetNotification();
s32 TestObjectSetMayContact();
void LatchObjectSetContact();
void InitFlaggedObjectSet();
void CopyFlaggedObjectSet();
s32 GetFlaggedObjectSetActivationState();
void CollectFlaggedObjectSet();
void LoadStateWalkerObject();
void StartStateWalkerObject();
void LoadStateWalkerGroup();
void StartStateWalkerGroup();
void InitNumberedItem();
void LoadNumberedItem();
void CopyNumberedItem();
void StartNumberedItem();
void UpdateNumberedItem();
void CollectNumberedItem();
void ApplyNumberedItemPendingImpulse();
s32 HandleNumberedItemObjectEvent();
void SpinNumberedItemTransform();
void InitC17Collider();
void StartC17Collider();
void HandleC17ColliderActivation();
void ControlC17Collider();
void HandleC17ColliderNotification();
void InitC71Object();
void RegisterC71Object();
void UnregisterC71Object();
void StartC71Object();
void CopyC71Object();
void InitObjectGatherer();
void LoadObjectGatherer();
void StartObjectGatherer();
void AddObjectGatherer();
void RemoveObjectGatherer();
void CopyObjectGatherer();
void StepObjectGatherer();
void UpdateObjectGatherer();
void ComputeObjectGathererContactValues();
void ResolveObjectGathererContact();
void ApplyObjectGathererLodObject();
s32 HandleObjectGathererObjectEvent();
void RegisterC7CObject();
void UnregisterC7CObject();
void InitAimBlendGrid();
void LoadAimBlendGrid();
void StartAimBlendGrid();
void InitEffectOwner();
void ReleaseEffectOwner();
void MoveEffectsAndBounds();
void KeepEffectOwnerBounds();
void UpdateEffectOwner();
void DrawEffects();
void InitEffect();
void EndEffect();
s32 HandleEffectContact();
void MoveEffect();
void UpdateEffect();
void DrawEffect();
void InitFallingEffect();
void EndEffectWithImpact();
void InitRisingEffect();
void MoveDriftingEffect();
void EndEffectWithImpactOnExit();
void InitImpactEffect();
void InitGrowingEffect();
void InitShrinkingFallEffect();
void InitDroppingEffect();
void UpdateDroppingEffect();
void DrawDroppingEffect();
void EndDroppingEffect();
void InitStreakEffect();
void DrawStreakEffect();
void InitScaledEffect();
void InitTrailSegment();
void DetachTrailSegment();
void MoveTrailSegment();
void DrawTrailSegment();
void InitSpawningEffect();
void SpawnFollowUpEffect();
void InitFollowUpEffect();
void InitWideTrailSegment();
void InitShortFallingEffect();
void InitCameraSpaceEffect();
void MoveCameraSpaceEffect();
void DrawCameraSpaceEffect();
void RunEffectEndCallback();
void InitEmitterEffect();
void MoveEmitterEffect();
void UpdateEmitterEffect();
void DrawEmitterEffect();
void InitLongStreakEffect();
void InitPhasedEffect();
void KeepPhasedEffectStill();
void AdvanceEffectPhases();
void DrawPhasedEffect();
void CopyEffectSourceIds();
void DrawProjectileEffect();
s32 HandleEffectImpact();
void UpdateEffectUntilDetached();
void DrawHitMarkEffect();
void SetRandomEffectSpin();
void MoveTumblingEffect();
s32 HandleTumblingEffectImpact();
void AimEffectAtNearestObject();
void PlaceEffectAtSource();
void DrawStreakedEffect();
s32 HandleStreakedEffectImpact();
void RandomizeEffectSpin();
s32 HandleEffectContactUnlessKind6();
void DrawSpinningEffect();
void InitFacingEffect();
void DrawFacingEffect();
void InitDelayedEffect();
void MoveDelayedEffect();
void UpdateDelayedEffect();
void DrawDelayedEffect();
void ResolveEffectTarget();
void SendEffectMessagesAtRate();
void InitWalkerCollider();
void LoadWalkerCollider();
void StartWalkerCollider();
void ControlWalkerCollider();
void UpdateWalkerCollider();
void HandleWalkerColliderNotification();
void StepWalkerCollider();
void ResolveWalkerColliderContact();
void ComputeWalkerColliderContactValue();
void ComputeWalkerColliderImpulseResponse();
s32 IsWalkerColliderCameraFree();
void InitPairController();
void ResolvePairControllerLinks();
void BlendPairControllerPose();
void UpdatePairController();
void ShowPairControllerElement();
void InitPairedObject();
void LoadPairedObject();
void CopyPairedObject();
void StartPairedObject();
void UpdatePairedObject();
s32 HandlePairedHit();
void InitHitTarget();
void LoadHitTarget();
void CopyHitTarget();
void StartHitTarget();
void UpdateHitTarget();
void StepHitTarget();
void ComputeHitTargetContactValue();
s32 ApplyHitTargetHit();
void InitSoundStateObject();
void LoadSoundStateObject();
void CopySoundStateObject();
void StartSoundStateObject();
void UpdateSoundStateObject();
void InitObjectCreator();
void LoadObjectCreator();
void StartObjectCreator();
void UpdateObjectCreator();
void InitObjectPool();
void UnregisterObjectPool();
void CopyObjectPool();
void StartObjectPool();
void ClearObjectPoolChoiceIfFlag();
void StartGaugeBarAgent();
s32 IsGaugeBarAgentFree();
void UpdateGaugeBarAgentGoal();
void UpdateGaugeBarAgentState();
void EnterGaugeBarAgentState();
void UpdateGaugeBarAgent();
void UpdateGaugeBarAgentVisibility();
s32 HandleGaugeBarAgentObjectEvent();
void InitScreenElement();
void SetupScreenElementText(ScreenElement* self);
void UpdateScreenElementSlide(ScreenElement* self);
void SetScreenElementText();
void DrawScreenElementText();
void ResetScreenElement();
void ShowScreenElement();
void HideScreenElement();
void SetScreenElementMode();
void SetScreenElementClock();
void InitCounterCaption(T217D_E30* self);
void UpdateCounterCaption();
void DrawCounterCaption(T217D_E30* self);
f32 GetCaptionHoldTime(void);
void InitTimerElement(T217D_510* self);
void UpdateTimerElement(T217D_510* self);
void DrawTimerElement(T217D_510* self);
f32 GetPairCaptionHoldTime(void);
f32 GetGaugeAmountCaptionHoldTime(void);
f32 GetGaugeColliderCaptionHoldTime(void);
void InitGauge();
void DrawGauge();
void InitFramedElement();
void SetCaptionTextAndSize();
void DrawElementWithFadedFrame();
void InitPointerTextCaption();
void SetElementTextAfterSlideOut();
void SetElementModeApplyingPendingText();
s32 AreElementsTogetherOrPending();
void ShowElementUnlessTextPending();
void HideElementOrDropPendingText();
void DrawSlidingGlyphElement();
void InitCopiedTextCaption();
void SetElementTextCopiedAfterSlideOut();
void SetElementModeApplyingCopiedText();
void ShowElementUnlessCopiedTextPending();
void HideElementOrDropCopiedText();
void DrawMessageElement();
void InitHintGlyphElement();
void UpdateHintGlyphElement();
void DrawHintGlyphElement();
void InitLetterboxElement();
void SetElementModeFollowingFade();
void DrawLetterboxElement();
void InitTitleElement();
void DrawTitleElement();
void InitPromptElement();
void SetElementModeRebuildingText();
void UpdatePromptElement();
void DrawPromptElement();
void InitLetterGlyphElement();
void DrawLetterGlyphElement();
void InitCyclingGlyphElement();
void SetElementModeClearingFlag();
void InitTimedObject();
void SetTimedObjectTarget();
void EnterTimedObjectState();
void UpdateTimedObject();
void InitTimedGroup();
void LoadTimedGroup();
void PostLoadTimedGroup();
void CloneTimedGroupEntries();
void UpdateTimedGroup();
void SetStaggeredColliderFrozen();
void DrawTimedGroup();
void ChooseTimedGroupState();
void SetTimedGroupMode();
void RequestTimedGroupEnd();
void FinishTimedGroup();
void EnterTimedGroupState();
void InitSequencedObject();
void SetupSequencedObject();
void UpdateSequencedObject();
void DrawSequencedObject();
s32 TestSequencedObjectMayContact();
void ChooseSequencedObjectState();
void SetSequencedObjectMode();
void RequestSequencedObjectEnd();
void FinishSequencedObject();
void EnterSequencedObjectState();
void InitBlinkObject();
void SetupBlinkObject();
void UpdateBlinkObject();
void ChooseBlinkObjectState();
void SetBlinkObjectMode();
void RequestBlinkObjectEnd();
void FinishBlinkObject();
void EnterBlinkObjectState();
void LoadPathCurveObject();
void ReparentPathCurveObject();
void LoadAnimatorBase();
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
void UpdateTriangleAnimatorCursor();
void StartCameraPositionedObject();
void MoveObjectToCamera();
void LoadStateGraph();
void StartStateGraph();
void InitCompanionAgent();
void StartCompanionAgent();
s32 IsCompanionAgentTargetReachable();
void UpdateCompanionAgent();
void EnterCompanionAgentState();
s32 IsCompanionAgentTargetInRange();
s32 AnswerCompanionAgentRosterPoll();
void HandleCompanionAgentNotification();
void SetCompanionAgentFrozen();
void InitCollider();
void RegisterCollider();
void UnregisterCollider();
void ApplyColliderPendingMove();
void ApplyColliderPendingImpulse();
void ApplyColliderPendingImpulseHalfStep();
void UpdateColliderBounds();
void ComputeColliderWorldFrame();
void RecomputeColliderFrame();
s32 TestCollidersMayContact();
void NotifyContactHandlers();
void AddContactVertexBlendVelocity();
void StepCollider();
void DrawCollider();
void UpdateCollider();
void SaveColliderPreviousPosition();
void SetColliderPosition();
void SetColliderRotation();
void SetColliderVelocity();
void SetColliderSpin();
void ReparentCollider();
void ReframeColliderAnchors();
void CaptureColliderPose();
void CopyCollider();
void ApplyColliderAttachedSetContact();
void IgnoreColliderAttachmentStep();
void LoadCollider();
void SendColliderNotification();
s32 RequestColliderLaunch();
void MoveCollider();
s32 HandleObjectEvent();
void CopyColliderMeshesInFrame();
void NumberColliderParts();
void ComputeColliderImpulseResponse();
void AddParentVelocityToChildRows();
void InitIdLinkedObject();
void StartIdLinkedObject();
void InitListedPointObject();
void RegisterListedPointObject();
void UnregisterListedPointObject();
void CopyListedPointObject();
void InitHitCountCollider();
void StartHitCountCollider();
void UpdateHitCountCollider();
void ShowHitCountColliderCounters();
void ControlHitCountCollider();
void StepHitCountCollider();
void NoteHitCountColliderContact();
void ResolveHitCountColliderContact();
s32 IsHitCountColliderRequestBlocked();
s32 AcceptHitCountColliderRequest();
s32 HasHitCountColliderAcceptedRequest();
void FinishHitCountCollider();
void InitTurningCollider();
void StartTurningCollider();
void DrawTurningCollider();
void UpdateTurningCollider();
s32 GetTurningColliderContactMode();
void ComputeTurningColliderImpulseResponse();
void SetTurningColliderRotation();
void CopyTurningColliderMeshesInFrame();
void StepTurningCollider();
s32 IsTurningColliderGroundContact();
void ComputeTurningColliderContactValue();
void ClampTurningColliderContactLimit();
void BuildTurningColliderHeadingMatrix();
void ResolveTurningColliderContact();
void RecomputeTurningColliderFrame();
void CollectTurningColliderContacts();
void CollideTurningColliderWithObject();
void GetTurningColliderPose();
void SumChildPoseOffsets();
void CombineChildPoseRotations();
void InitAgent();
void LoadAgent();
void CopyAgent();
void PostLoadAgent();
void StartAgent();
s32 TestAgentMayContact();
void RegisterAgent();
void UnregisterAgent();
void StepAgent();
void UpdateAgent();
s32 ChooseAgentState();
void BuildAgentPath();
void UpdateAgentGoal();
void UpdateAgentState();
void LeaveAgentState();
void EnterAgentState();
s32 HandleAgentObjectEvent();
s32 AcceptAgentRequest();
s32 IsAgentRequestBlocked();
void SteerAgentAlongPath();
void RestartAgentClip();
void HandleAgentNotification();
s32 AnswerAgentRosterPoll();
s32 IsAgentTargetInRange();
void DrawAgent();
void* SelectAgentTarget();
void ComputeAgentContactValue();
void ClampAgentContactLimit();
void CollideAgentWithObject();
s32 RequestAgentLaunch();
s32 IsAgentFree();
void InitItemKeeper();
void FindWantedItems();
void SyncPlayerTarget();
void GetPlayerPose();
void StartCountedCollider();
void UpdateCountedCollider();
void StepCountedCollider();
void CollectCountedColliderContacts();
void* HandleCountedColliderEvent();
void ComputeCountedColliderWorldFrame();
void HandleCountedColliderNotification();
s32 AcceptPlayerRequest();
s32 IsPlayerRequestBlocked();
s32 GetPlayerRequestPhase();
void FinishPlayerRequest();
void ApplyPlayerAttachedSetContact();
s32 TestStandInMayContact();
void StepStandIn();
void StopStandIn();
void HandleStandInNotification();
void InitPathFollower();
void StartPathFollower();
void StepPathFollower();
void UpdatePathFollower();
void ControlPathFollower();
void UpdatePathFollowerScreenElements();
void ReleasePathFollowerContacts();
void CollidePathFollowerWithObject();
void ComputePathFollowerContactValue();
void UpdatePathFollowerAttachmentFrames();
void DrawPathFollower();
void UpdatePathFollowerBounds();
void StartPathFollowerEffect();
void RecomputePathFollowerFrame();
void CapturePathFollowerPose();
void HandlePathFollowerActivation();
void HandlePathFollowerNotification();
void InitWorldPools();
void LoadWorld();
void InitRedirectObject();
void StartRedirectObject();
void SimulateRedirectChain();
void MarkRedirectToSelf();
void InitTintBlendCollider();
void StartTintBlendCollider();
void UpdateTintBlendCollider();
void FinishTintBlendColliderRequest();
void ControlTintBlendCollider();
void SetTintBlendColliderTracked();
void ApplyTintBlendColliderTint();
void ApplyTintBlendColliderPendingImpulse();
s32 IsTintBlendColliderRequestBlocked();
s32 AcceptTintBlendColliderRequest();
void CollectTintBlendColliderContacts();
void ComputeTintBlendColliderContactValue();
void HandleTintBlendColliderNotification();
s32 GetTintBlendColliderRequestPhase();
void InitClass75Object();
void RegisterClass75Object();
void UnregisterClass75Object();
void CopyClass75ObjectData();
void InitCommentaryPromptElement();
void UpdateBestTimeState();
void DrawFramedText();
void InitOnOffObject();
void UnregisterOnOffObject();
void LoadOnOffObject();
void StartOnOffObject();
void UpdateOnOffObject();
void DrawOnOffObject();
void SetOnOffObjectFrozen();
void ActivateOnOffCameraController();
void DeactivateOnOffCameraController();
void NoteOnOffCameraControllerPushed();
void NoteOnOffCameraControllerRemoved();
void UpdateOnOffCameraController();
void InitPlayerLinkedCollider();
void StartPlayerLinkedCollider();
void UpdatePlayerLinkedCollider();
void ControlPlayerLinkedCollider();
void HandlePlayerLinkedColliderActivation();
void HandlePlayerLinkedColliderNotification();
s32 TestPlayerLinkedColliderMayContact();
void StartPlayerLinkedColliderEffect();
void GetPlayerLinkedColliderInteractFlags();
void* GetPlayerLinkedColliderTarget();
void InitArcPoints();
void CreateArcSprite();
void DrawArc();
void SetArcMode();
void UpdateArc();
void QueueArcDraw();
void ResetArc();
void InitKeyedConeAgent();
void StartKeyedConeAgent();
void EnterKeyedConeAgentState();
s32 ChooseKeyedConeAgentState();
s32 IsKeyedConeAgentFree();
s32 IsKeyedConeAgentTargetInRange();
void SteerKeyedConeAgentAlongPath();
void RestartKeyedConeAgentClip();
void UpdateKeyedConeAgentGoal();
void UpdateKeyedConeAgentState();
void ShowElementWhenMenusClear();
s32 TestAgentMayContactExceptKeys();
void UpdateWorld();
void InitBeatPressCollider();
void LoadBeatPressCollider();
void StartBeatPressCollider();
void HandleBeatPressColliderActivation();
void JudgeBeatPressInput();
s32 IsBeatPressColliderRequestBlocked();
s32 AcceptBeatPressColliderRequest();
void GetBeatPressColliderPositionAt();
void GetBeatPressColliderRotationAt();
void InitTempoAgent();
void LoadTempoAgent();
void StartTempoAgent();
void UnregisterTempoAgent();
void RegisterTempoAgent();
s32 IsTempoAgentTargetInRange();
s32 IsTempoAgentFree();
void ApplyTempoAgentTransform();
void DrawTempoAgent();
void LeaveTempoAgentState();
void EnterTempoAgentState();
void HandleTempoAgentNotification();
void UpdateTempoAgent();
void ShowTempoAgentGauge();
void UpdateTempoAgentGoal();
void UpdateTempoAgentState();
void InitTimeline();
void FindTimelineTarget();
void InitValueListObject();
void LoadValueList();
void InitAttachedSet();
void StartAttachedSet();
void UpdateAttachedSet();
void ForwardAttachedSetLinkStep();
void HandleAttachedSetNotification();
void UpdateAttachedSetBounds();
s32 RequestAttachedSetLaunch();
void InitStateResetObject();
void StartStateResetObject();
void UpdateStateResetObject();
void HandleStateResetNotification();
void StartWarpPage();
void PostLoadWarpPage();
void UpdateWarpPage();
void ApplyWarpPageTransform();
void HandleWarpPageNotification();
void InitWarpMenu();
void HandleWarpMenuInput();
void SetWarpMenuOpen();
void DrawWarpMenu();
void InitOscillator();
void InitTransformObject();
void ReadTransformObject();
void ReparentObjectKeepingTransform();
void TransformObjectIntoFrame();
void LoadArrivalPoint();
void CopyArrivalPoint();
void StartArrivalPoint();
void LoadObjectSubGroup();
void StartObjectSubGroup();
void UpdateObjectSubGroup();
void InitLookupObject();
void StartLookupObject();
void InitContactTracker();
void StartContactTracker();
void CollectTouchingObjects();
void CopyContactTracker();
void ApplyContactTrackerTransform();
int RequestContactTrackerLaunch();
void InitC37();
void UpdateC37();


extern const ClassDescriptor<2> D_00217380 = { 0x0, 0x0, 0x0, 0x0, {
    0, 0,
} };
extern const Fn_Table D_00217398[6] = { 0, 0, 0, 0, (Fn_Table)UpdateIdleCameraController, 0 };
extern const Fn_Table D_002173B0[6] = { (Fn_Table)ActivateTargetCameraController, (Fn_Table)DeactivateTargetCameraController, 0, 0, (Fn_Table)UpdateTargetCameraController, 0 };
extern const Fn_Table D_002173C8[6] = { (Fn_Table)ActivateFrameCameraController, 0, 0, 0, (Fn_Table)UpdateFrameCameraController, 0 };
extern const Fn_Table D_002173E0[6] = { (Fn_Table)ActivateValueCameraController, (Fn_Table)DeactivateValueCameraController, 0, 0, (Fn_Table)UpdateValueCameraController, 0 };
extern const Fn_Table D_002173F8[6] = { (Fn_Table)ActivateOnOffCameraController, (Fn_Table)DeactivateOnOffCameraController, (Fn_Table)NoteOnOffCameraControllerPushed, (Fn_Table)NoteOnOffCameraControllerRemoved, (Fn_Table)UpdateOnOffCameraController, 0 };
// The root every chain of parents ends at (tools/classes.py's `root`).
extern const ClassHead D_00217410 = { 0, 0 };
extern const ClassDescriptor<28> D_00217418 = { &D_00217410, 0x1, 0x0, 0x34, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadObjectProperties, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<48> D_00217498 = { &D_00217418, 0x2, 0x1, 0x2D0, {
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
extern const ClassDescriptor<86> D_00217568 = { &D_00217498, 0x3, 0x3, 0x550, {
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
extern const ClassDescriptor<28> D_00217740 = { &D_00217418, 0x6E, 0x0, 0x38, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadPathCurveObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentPathCurveObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> g_pointObjectClass = { &D_00217418, 0x7E, 0x0, 0x50, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadPointObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentPointObject, (Fn_Table)ConvertPointObjectPosition, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> D_00217840 = { &g_pointObjectClass, 0x82, 0x0, 0x60, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadTextPointObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentPointObject, (Fn_Table)ConvertPointObjectPosition, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> D_002178C0 = { &D_00217418, 0x73, 0x0, 0x80, {
    (Fn_Table)InitTransformObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)ReadTransformObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObjectKeepingTransform, (Fn_Table)TransformObjectIntoFrame, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> D_00217940 = { &D_002178C0, 0x74, 0x0, 0x100, {
    (Fn_Table)InitTransformObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyArrivalPoint, (Fn_Table)LoadArrivalPoint, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartArrivalPoint, 0, 0, 0,
    0, (Fn_Table)ReparentObjectKeepingTransform, (Fn_Table)TransformObjectIntoFrame, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<48> D_002179C0 = { &D_00217498, 0x7D, 0x1, 0x330, {
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
extern const ClassDescriptor<48> D_00217A90 = { &D_00217498, 0x4E, 0x1, 0x320, {
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
extern const ClassDescriptor<48> D_00217B60 = { &D_00217498, 0x51, 0x1, 0x620, {
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
extern const ClassDescriptor<124> D_00217C30 = { &D_00217568, 0x5, 0xB, 0x610, {
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
extern const T217D_Vt D_00217FC0 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetGaugeAmountCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00218010 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00218060 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_002180B0 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00218100 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00218150 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_002181A0 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetGaugeColliderCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_002181F0 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00218240 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00218290 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCounterCaption, (ElementFn)UpdateCounterCaption, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawCounterCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetCaptionHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_002182E0 = { (ElementIntFn)InitScreenElement, (ElementFn)InitGauge, (ElementFn)UpdateScreenElementSlide, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawGauge, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00218330 = {
    (ElementIntFn)InitScreenElement, (ElementFn)InitFramedElement, (ElementFn)UpdateScreenElementSlide, 0,
    0, (ElementFn)ResetScreenElement, 0, 0,
    (ElementTextFn)SetCaptionTextAndSize, (ElementFn)DrawElementWithFadedFrame, 0, (ElementTimeFn)GetScreenElementSlideInTime,
    (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement,
    (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0,
};
extern const T217D_Vt D_00218380 = { (ElementIntFn)InitScreenElement, (ElementFn)InitPointerTextCaption, (ElementFn)UpdateScreenElementSlide, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetElementTextAfterSlideOut, (ElementFn)DrawSlidingGlyphElement, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowElementUnlessTextPending, (ElementFn)HideElementOrDropPendingText, (ElementIntFn)SetElementModeApplyingPendingText, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreElementsTogetherOrPending, 0 };
extern const T217D_Vt D_002183D0 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCopiedTextCaption, (ElementFn)UpdateScreenElementSlide, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetElementTextCopiedAfterSlideOut, (ElementFn)DrawMessageElement, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowElementUnlessCopiedTextPending, (ElementFn)HideElementOrDropCopiedText, (ElementIntFn)SetElementModeApplyingCopiedText, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00218420 = { (ElementIntFn)InitScreenElement, (ElementFn)InitHintGlyphElement, (ElementFn)UpdateHintGlyphElement, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawHintGlyphElement, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00218470 = { (ElementIntFn)InitScreenElement, (ElementFn)InitTitleElement, (ElementFn)UpdateScreenElementSlide, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawTitleElement, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_002184C0 = { (ElementIntFn)InitScreenElement, (ElementFn)InitPromptElement, (ElementFn)UpdatePromptElement, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawPromptElement, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetElementModeRebuildingText, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00218510 = { (ElementIntFn)InitScreenElement, (ElementFn)InitTimerElement, (ElementFn)UpdateTimerElement, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawTimerElement, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00218560 = { (ElementIntFn)InitScreenElement, (ElementFn)InitLetterboxElement, (ElementFn)UpdateScreenElementSlide, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawLetterboxElement, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetElementModeFollowingFade, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_002185B0 = { (ElementIntFn)InitScreenElement, (ElementFn)InitLetterGlyphElement, (ElementFn)UpdateScreenElementSlide, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawLetterGlyphElement, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00218600 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCyclingGlyphElement, (ElementFn)UpdateScreenElementSlide, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawScreenElementText, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetElementModeClearingFlag, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const ClassDescriptor<28> g_coloredTriangleSetClass = { &D_00217418, 0x8E, 0x0, 0xA0, {
    (Fn_Table)InitColoredTriangles, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadColoredTriangles, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const T217D_Vt D_002186D0 = { (ElementIntFn)InitScreenElement, (ElementFn)InitPauseMenu, (ElementFn)UpdateScreenElementSlide, (ElementIntFn)SetPauseMenuOpen, (ElementPadFn)UpdatePauseMenu, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawPauseMenu, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowPauseMenu, (ElementFn)HidePauseMenu, (ElementIntFn)SetPauseMenuMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00218720 = { (ElementIntFn)InitItemColumn, (ElementFn)SetupItemColumn, (ElementFn)UpdateItemColumnSlide, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawItemColumn, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)UpdateItemColumn, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const ClassDescriptor<72> D_00218770 = { &D_00217568, 0x1F, 0x83, 0x6B0, {
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
extern const ClassDescriptor<48> D_002188A0 = { &D_00217498, 0x63, 0x1, 0x470, {
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
extern const ClassDescriptor<74> D_00218970 = { &D_00217568, 0x20, 0x3, 0x6C0, {
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
extern const ClassDescriptor<72> D_00218AA8 = { &D_00217568, 0x27, 0x3, 0x570, {
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
extern const ClassDescriptor<74> D_00218BD8 = { &D_00218970, 0x21, 0x13, 0x6C0, {
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
extern const ClassDescriptor<74> D_00218D10 = { &D_00218970, 0x25, 0x3, 0x6D0, {
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
extern const ClassDescriptor<74> D_00218E48 = { &D_00218D10, 0x26, 0x3, 0x6E0, {
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
extern const ClassDescriptor<72> D_00218F80 = { &D_00217568, 0x29, 0x3, 0x7A0, {
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
extern const ClassDescriptor<72> D_002190B0 = { &D_00217568, 0x28, 0x3, 0x890, {
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
extern const ClassDescriptor<28> D_002191E0 = { &D_00217418, 0x87, 0x0, 0x68, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadObjectProperties, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)ResolveLookupIds, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<48> D_00219260 = { &D_00217498, 0x4F, 0x1, 0x2D0, {
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
extern const ClassDescriptor<72> D_00219330 = { &D_00217568, 0x2B, 0x3, 0x550, {
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
extern const ClassDescriptor<28> D_00219460 = { &D_00217418, 0x86, 0x0, 0x44, {
    (Fn_Table)InitValueListObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadValueList, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> D_002194E0 = { &D_00217418, 0x85, 0x0, 0x34, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadObjectProperties, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const T2195_Vt D_00219560 = {
    (AttachInit)InitPoseSource, (AttachCopy)CopyPoseSource, (AttachRelease)ReleasePoseSource, 0,
    (AttachGetPos)GetOwnerPosition, (AttachGetRot)GetOwnerRotation, (AttachGetValue)GetOwnerValue, (AttachGetMatrix)GetIdentityMatrix,
    (AttachGetIndexed)GetOwnerIndexedValue, 0,
};
extern const T2195_Vt D_00219588 = {
    (AttachInit)InitSnapshotPoseSource, (AttachCopy)CopyPoseSource, (AttachRelease)ReleasePoseSource, 0,
    (AttachGetPos)GetSnapshotPosition, (AttachGetRot)GetSnapshotRotation, (AttachGetValue)GetSnapshotValue, (AttachGetMatrix)GetSnapshotMatrix,
    (AttachGetIndexed)GetSnapshotIndexedValue, 0,
};
extern const T2195_Vt D_002195B0 = { (AttachInit)InitLinkedPoseSource, (AttachCopy)CopyPoseSource, (AttachRelease)ReleasePoseSource, 0, (AttachGetPos)GetLinkedPosition, (AttachGetRot)GetLinkedRotation, (AttachGetValue)GetLinkedValue, (AttachGetMatrix)GetLinkedMatrix, (AttachGetIndexed)GetLinkedIndexedValue, 0 };
extern const T2195_Vt D_002195D8 = { (AttachInit)InitIdentityPoseSource, (AttachCopy)CopyPoseSource, (AttachRelease)ReleasePoseSource, 0, (AttachGetPos)GetIdentityPosePosition, (AttachGetRot)GetIdentityPoseRotation, (AttachGetValue)GetNextPoseSourceValue, (AttachGetMatrix)GetIdentityPoseMatrix, (AttachGetIndexed)GetIdentityPoseIndexedValue, 0 };
extern const AttachmentAndCurveBases D_00219600 = {
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
extern const ClassDescriptor<28> D_00219738 = { &D_00217418, 0x83, 0x40, 0xB0, {
    (Fn_Table)InitAnimation, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyAnimation, (Fn_Table)LoadAnimation, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartClampedKinematicValue, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassHead g_animationPlayerMethods = { &D_00217410, 0x92 };
extern const T2195_Vt D_002197C0 = { (AttachInit)InitPoseSource, (AttachCopy)CopyTrackPoseSource, (AttachRelease)ReleaseTrackPoseSource, 0, (AttachGetPos)GetTrackPosition, (AttachGetRot)GetTrackRotation, (AttachGetValue)GetTrackValue, (AttachGetMatrix)GetTrackScaleMatrix, (AttachGetIndexed)GetTrackIndexedValue, 0 };
extern const ClassDescriptor<28> D_002197E8 = { &D_00219738, 0x84, 0x40, 0xD0, {
    (Fn_Table)InitAnimation, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)SkipAnimationPlayerCopy, (Fn_Table)SkipAnimationPlayerLoad, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)SkipAnimationPlayerStart, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> D_00219868 = { &D_00217418, 0x88, 0x0, 0x54, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadStateGraph, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartStateGraph, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassHead g_stateWalkerMethods = { &D_00217410, 0x93 };
extern const ClassDescriptor<72> D_002198F0 = { &D_00217568, 0x35, 0x3, 0x550, {
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
extern const ClassDescriptor<48> D_00219A20 = { &D_00217498, 0x52, 0x1, 0x2D0, {
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
extern const ClassDescriptor<72> D_00219AF0 = { &D_00217568, 0x1E, 0x3, 0x570, {
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
// are in src/main/file_19E040.cpp.
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
extern const ClassDescriptor<48> D_00219F80 = { &D_00217498, 0x4D, 0x1, 0x640, {
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
extern const ClassDescriptor<48> D_0021A050 = { &D_00217498, 0x50, 0x1, 0x350, {
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
extern const ClassDescriptor<28> D_0021A120 = { &D_002178C0, 0x77, 0x0, 0x90, {
    (Fn_Table)InitTransformObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)ReadTransformObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartMemberObject, 0, 0, 0,
    0, (Fn_Table)ReparentObjectKeepingTransform, (Fn_Table)TransformObjectIntoFrame, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)SendMemberObjectMessage,
} };
extern const ClassDescriptor<28> D_0021A1A0 = { &D_0021A120, 0x78, 0x0, 0xC0, {
    (Fn_Table)InitTransformObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyGroupMembers, (Fn_Table)LoadGroupMembers, 0,
    0, 0, (Fn_Table)SendObjectNotification, (Fn_Table)ResolveGroupMembers,
    (Fn_Table)StartMemberObject, 0, 0, 0,
    0, (Fn_Table)ReparentObjectKeepingTransform, (Fn_Table)TransformObjectIntoFrame, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)BroadcastMessageToMembers,
} };
extern const ClassDescriptor<28> D_0021A220 = { &D_0021A120, 0x79, 0x0, 0xA0, {
    (Fn_Table)InitRecordMember, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyRecordMember, (Fn_Table)LoadRecordMember, 0,
    0, 0, (Fn_Table)SendObjectNotification, (Fn_Table)ResolveRecordMemberTargets,
    (Fn_Table)StartMemberObject, 0, 0, 0,
    0, (Fn_Table)ReparentObjectKeepingTransform, (Fn_Table)TransformObjectIntoFrame, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)SendRecordMemberMessage,
} };
extern const ClassDescriptor<28> D_0021A2A0 = { &D_0021A220, 0x7A, 0x0, 0xD0, {
    (Fn_Table)InitHoldingMember, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyRecordMember, (Fn_Table)LoadRecordMember, 0,
    0, (Fn_Table)ReleaseHeldObject, (Fn_Table)SendObjectNotification, (Fn_Table)ResolveHoldingMemberTargets,
    (Fn_Table)StartMemberObject, 0, 0, 0,
    0, (Fn_Table)ReparentObjectKeepingTransform, (Fn_Table)TransformObjectIntoFrame, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)SendMessageAfterDelay,
} };
extern const ClassDescriptor<48> D_0021A320 = { &D_00217498, 0x53, 0x101, 0x2F0, {
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
extern const T217D_Vt D_0021A3F0 = { (ElementIntFn)InitArcPoints, (ElementFn)CreateArcSprite, (ElementFn)UpdateArc, 0, 0, (ElementFn)ResetArc, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawArc, (ElementFn)QueueArcDraw, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetArcMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_0021A440 = { (ElementIntFn)InitTextPanel, (ElementFn)SetupTextPanel, (ElementFn)UpdateScreenElementSlide, (ElementIntFn)SetTextPanelOpen, (ElementPadFn)UpdatePanelStick, (ElementFn)ResetTextPanel, (ElementFn)ChooseTextPanelState, (ElementFn)EndTextPanelState, (ElementTextFn)SetTextPanelText, (ElementFn)DrawTextPanel, 0, (ElementTimeFn)GetTextPanelSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetTextPanelSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetTextPanelMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const ClassDescriptor<48> D_0021A490 = { &D_00217498, 0x65, 0x1, 0x340, {
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
extern const ClassDescriptor<28> D_0021A560 = { &D_00217740, 0x6F, 0x0, 0x60, {
    (Fn_Table)InitTargetCurve, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterTargetCurve, (Fn_Table)UnregisterTargetCurve,
    (Fn_Table)CloneObject, (Fn_Table)CopyTargetCurve, (Fn_Table)LoadPathCurveObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadTargetCurve,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentPathCurveObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> D_0021A5E0 = { &g_pointObjectClass, 0x7F, 0x0, 0x80, {
    (Fn_Table)InitTargetPoint, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterTargetPoint, (Fn_Table)UnregisterTargetPoint,
    (Fn_Table)CloneObject, (Fn_Table)CopyTargetPoint, (Fn_Table)LoadPointObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, (Fn_Table)PostLoadTargetPoint,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentPointObject, (Fn_Table)ConvertPointObjectPosition, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<72> D_0021A660 = { &D_00217568, 0x3A, 0x3, 0x570, {
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
extern const T2195_Vt D_0021A790 = {
    (AttachInit)InitAim, (AttachCopy)CopyPoseSource, (AttachRelease)ReleasePoseSource, (AttachUpdate)SwitchAimByTargetDistance,
    (AttachGetPos)GetOwnerPosition, (AttachGetRot)GetAimRotation, (AttachGetValue)GetOwnerValue, (AttachGetMatrix)GetIdentityMatrix,
    (AttachGetIndexed)GetOwnerIndexedValue, 0,
};
extern const ClassDescriptor<28> D_0021A7B8 = { &D_00217418, 0x8B, 0x0, 0x3F0, {
    (Fn_Table)InitAimBlendGrid, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadAimBlendGrid, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartAimBlendGrid, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<88> D_0021A838 = { &D_00217C30, 0x6, 0xB, 0x720, {
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
extern const T2195_Vt D_0021A9A8 = {
    (AttachInit)InitPoseSource, (AttachCopy)CopyPoseSource, (AttachRelease)ReleasePoseSource, 0,
    (AttachGetPos)SumChildPoseOffsets, (AttachGetRot)CombineChildPoseRotations, (AttachGetValue)GetOwnerValue, (AttachGetMatrix)GetIdentityMatrix,
    (AttachGetIndexed)GetOwnerIndexedValue, 0,
};
extern const ClassDescriptor<74> D_0021A9D0 = { &D_00218BD8, 0x22, 0x13, 0x6D0, {
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
extern const ClassDescriptor<72> D_0021AB08 = { &D_00217568, 0x2F, 0x3, 0x6C0, {
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
extern const ClassDescriptor<78> D_0021AC38 = { &D_00217568, 0x30, 0x3, 0x5D0, {
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
extern const ClassDescriptor<78> D_0021AD80 = { &D_0021AC38, 0x31, 0x3, 0xB10, {
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
extern const ClassDescriptor<78> D_0021AEC8 = { &D_0021AC38, 0x32, 0x3, 0x5F0, {
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
extern const ClassDescriptor<78> D_0021B010 = { &D_0021AC38, 0x33, 0x3, 0x620, {
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
extern const ClassDescriptor<28> D_0021B158 = { &D_002178C0, 0x75, 0x0, 0xA0, {
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
extern const ClassDescriptor<28> D_0021B258 = { &D_00217740, 0x70, 0x0, 0x70, {
    (Fn_Table)InitTargetVector, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterTargetVector, (Fn_Table)UnregisterTargetVector,
    (Fn_Table)CloneObject, (Fn_Table)CopyTargetVector, (Fn_Table)LoadPathCurveObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartTargetVector, 0, 0, 0,
    0, (Fn_Table)ReparentPathCurveObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<72> g_idFilterObjectClass = { &D_00217568, 0x34, 0x3, 0x5B0, {
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
extern const ClassDescriptor<48> g_redirectObjectClass = { &D_00217498, 0x5E, 0x1, 0x340, {
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
extern const ClassDescriptor<72> D_0021B4D8 = { &D_00217568, 0x3B, 0x23, 0x690, {
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
extern const ClassDescriptor<28> D_0021B608 = { &D_00217418, 0x8F, 0x0, 0x6C, {
    (Fn_Table)InitEntryQueue, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadObjectProperties, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<88> D_0021B688 = { &D_0021A838, 0x7, 0xB, 0x2BF0, {
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
extern const ClassDescriptor<72> D_0021B878 = { &D_0021B4D8, 0x3F, 0x23, 0x6A0, {
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
extern const ClassDescriptor<72> D_0021B9A8 = { &D_00217568, 0x4C, 0x3, 0x560, {
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
extern const ClassDescriptor<28> g_itemKeeperClass = { &D_00217418, 0x89, 0x0, 0x190, {
    (Fn_Table)InitItemKeeper, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadObjectProperties, 0,
    0, 0, (Fn_Table)SendObjectNotification, (Fn_Table)FindWantedItems,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<100> D_0021BB58 = { &D_0021A838, 0x8, 0xB, 0xC10, {
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
extern const ClassDescriptor<100> D_0021BCF8 = { &D_0021BB58, 0xA, 0xB, 0xC50, {
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
extern const ClassDescriptor<100> D_0021BE98 = { &D_0021BB58, 0x9, 0xB, 0xD00, {
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
extern const ClassDescriptor<72> D_0021C038 = { &D_00217568, 0x36, 0x3, 0x860, {
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
extern const ClassDescriptor<72> D_0021C168 = { &D_0021C038, 0x37, 0x3, 0x860, {
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
extern const ClassDescriptor<28> D_0021C298 = { &D_002178C0, 0x7B, 0x0, 0x90, {
    (Fn_Table)InitTransformObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)ReadObjectTransformAndTables, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObjectKeepingTransform, (Fn_Table)TransformObjectIntoFrame, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<72> g_flaggedObjectClass = { &D_00217568, 0x38, 0x3, 0x5C0, {
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
extern const ClassDescriptor<28> g_pointGraphObjectClass = { &D_00217418, 0x8A, 0x0, 0x58, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadPointGraph, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<48> D_0021C4C8 = { &D_00217498, 0x54, 0x1, 0x2E0, {
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
extern const ClassDescriptor<72> g_objectCyclerClass = { &D_00217568, 0x40, 0x3, 0x6A0, {
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
extern const ClassDescriptor<48> g_stateNotifierClass = { &D_00217498, 0x55, 0x1, 0x390, {
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
extern const ClassDescriptor<48> D_0021C798 = { &g_stateNotifierClass, 0x58, 0x1, 0x3A0, {
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
extern const ClassDescriptor<48> D_0021C868 = { &g_stateNotifierClass, 0x56, 0x1, 0x390, {
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
extern const ClassDescriptor<48> D_0021C938 = { &g_stateNotifierClass, 0x59, 0x1, 0x390, {
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
extern const ClassDescriptor<48> D_0021CA08 = { &g_stateNotifierClass, 0x5A, 0x1, 0x390, {
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
extern const ClassDescriptor<48> D_0021CAD8 = { &g_stateNotifierClass, 0x57, 0x1, 0x3A0, {
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
extern const ClassDescriptor<48> D_0021CBA8 = { &g_stateNotifierClass, 0x5B, 0x1, 0x390, {
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
extern const ClassDescriptor<76> D_0021CC78 = { &D_00217568, 0x2C, 0x3, 0x5A0, {
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
extern const ClassDescriptor<76> D_0021CDB8 = { &D_0021CC78, 0x2D, 0x3, 0x5B0, {
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
extern const ClassDescriptor<76> D_0021CEF8 = { &D_0021CC78, 0x2E, 0x3, 0x5C0, {
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
extern const ClassDescriptor<48> D_0021D038 = { &D_00217498, 0x5C, 0x1, 0x2E0, {
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
extern const ClassDescriptor<48> D_0021D108 = { &D_00217498, 0x5D, 0x1, 0x330, {
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
extern const ClassDescriptor<84> D_0021D1D8 = { &D_00217C30, 0x17, 0xB, 0x800, {
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
extern const ClassDescriptor<72> g_objectGathererClass = { &D_00217568, 0x41, 0x3, 0x670, {
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
extern const ClassDescriptor<48> g_pairControllerClass = { &D_00217498, 0x5F, 0x1, 0x660, {
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
extern const ClassDescriptor<84> D_0021D5B8 = { &D_00217C30, 0x15, 0xB, 0x690, {
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
extern const ClassDescriptor<72> g_pairedObjectClass = { &D_00217568, 0x42, 0x3, 0x5C0, {
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
extern const ClassDescriptor<72> g_hitTargetClass = { &D_00217568, 0x43, 0x3, 0x5B0, {
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
extern const ClassDescriptor<72> g_soundStateObjectClass = { &D_00217568, 0x44, 0x3, 0x570, {
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
extern const ClassDescriptor<72> g_objectCreatorClass = { &D_00217568, 0x45, 0x3, 0x570, {
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
extern const ClassDescriptor<72> D_0021DBD8 = { &D_00217568, 0x46, 0x3, 0x590, {
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
extern const ClassDescriptor<74> D_0021DD08 = { &D_00218BD8, 0x23, 0x13, 0x7C0, {
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
extern const ClassDescriptor<48> D_0021DE40 = { &D_00217498, 0x60, 0x1, 0x300, {
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
extern const ClassDescriptor<74> D_0021DF10 = { &D_0021B4D8, 0x3C, 0x23, 0x6F0, {
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
extern const ClassDescriptor<74> D_0021E048 = { &D_0021DF10, 0x3D, 0x23, 0x710, {
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
extern const ClassDescriptor<74> D_0021E180 = { &D_0021DF10, 0x3E, 0x23, 0x710, {
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
extern const ClassDescriptor<36> D_0021E2B8 = { &D_00217418, 0x8C, 0x0, 0x170, {
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
extern const ClassDescriptor<72> g_scaledOffsetObjectClass = { &D_00217568, 0x39, 0x3, 0x560, {
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
extern const ClassDescriptor<48> D_0021E588 = { &D_00217498, 0x61, 0x1, 0x2F0, {
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
extern const ClassDescriptor<48> D_0021E658 = { &D_00217498, 0x62, 0x1, 0x330, {
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
extern const ClassDescriptor<100> D_0021E728 = { &D_0021BCF8, 0xB, 0xB, 0xCA0, {
    (Fn_Table)InitKeyedConeAgent, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterAgent, (Fn_Table)UnregisterAgent,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyAgent, (Fn_Table)LoadAgent, 0,
    0, (Fn_Table)HandleAgentNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadAgent,
    (Fn_Table)StartKeyedConeAgent, (Fn_Table)UpdateAgent, (Fn_Table)RecomputeTurningColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
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
    (Fn_Table)BuildTurningColliderHeadingMatrix, (Fn_Table)GetTurningColliderContactMode, (Fn_Table)IsTurningColliderGroundContact, (Fn_Table)IsKeyedConeAgentFree,
    (Fn_Table)AnswerAgentRosterPoll, (Fn_Table)ChooseKeyedConeAgentState, (Fn_Table)UpdateKeyedConeAgentState, (Fn_Table)LeaveAgentState,
    (Fn_Table)EnterKeyedConeAgentState, (Fn_Table)IsKeyedConeAgentTargetInRange, (Fn_Table)UpdateKeyedConeAgentGoal, (Fn_Table)BuildAgentPath,
    (Fn_Table)RestartKeyedConeAgentClip, (Fn_Table)SteerKeyedConeAgentAlongPath, (Fn_Table)SelectAgentTarget, 0,
} };
extern const ClassDescriptor<100> D_0021E8C8 = { &D_0021BB58, 0xC, 0xB, 0xE50, {
    (Fn_Table)InitGaugeAgent, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterAgent, (Fn_Table)UnregisterAgent,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyAgent, (Fn_Table)LoadGaugeAgent, 0,
    0, (Fn_Table)HandleGaugeAgentNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadAgent,
    (Fn_Table)StartGaugeAgent, (Fn_Table)UpdateGaugeAgent, (Fn_Table)RecomputeTurningColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepAgent, (Fn_Table)SetColliderPosition, (Fn_Table)SetTurningColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetTurningColliderPose,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawGaugeAgent, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleAgentObjectEvent, (Fn_Table)ShowGaugeAgentBar, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyTurningColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeTurningColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestAgentMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)CollideAgentWithObject, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeAgentContactValue, (Fn_Table)ResolveTurningColliderContact, (Fn_Table)ClampAgentContactLimit, (Fn_Table)CollectTurningColliderContacts,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestAgentLaunch,
    (Fn_Table)HandleSwitchedColliderActivation, 0, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsAgentRequestBlocked,
    (Fn_Table)AcceptAgentRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
    (Fn_Table)BuildTurningColliderHeadingMatrix, (Fn_Table)GetTurningColliderContactMode, (Fn_Table)IsTurningColliderGroundContact, (Fn_Table)IsGaugeAgentFree,
    (Fn_Table)AnswerAgentRosterPoll, (Fn_Table)ChooseGaugeAgentState, (Fn_Table)UpdateGaugeAgentState, (Fn_Table)LeaveGaugeAgentState,
    (Fn_Table)EnterGaugeAgentState, (Fn_Table)HasGaugeAgentClearLine, (Fn_Table)UpdateGaugeAgentGoal, (Fn_Table)BuildAgentPath,
    (Fn_Table)RestartAgentClip, (Fn_Table)SteerAgentAlongPath, (Fn_Table)SelectAgentTarget, 0,
} };
extern const ClassDescriptor<100> D_0021EA68 = { &D_0021BB58, 0xD, 0xB, 0xC30, {
    (Fn_Table)InitAgent, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterAgent, (Fn_Table)UnregisterAgent,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyAgent, (Fn_Table)LoadAgent, 0,
    0, (Fn_Table)HandleAgentNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadAgent,
    (Fn_Table)StartGaugeBarAgent, (Fn_Table)UpdateGaugeBarAgent, (Fn_Table)RecomputeTurningColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepAgent, (Fn_Table)SetColliderPosition, (Fn_Table)SetTurningColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetTurningColliderPose,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawAgent, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleGaugeBarAgentObjectEvent, (Fn_Table)UpdateGaugeBarAgentVisibility, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyTurningColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeTurningColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestAgentMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)CollideAgentWithObject, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeAgentContactValue, (Fn_Table)ResolveTurningColliderContact, (Fn_Table)ClampAgentContactLimit, (Fn_Table)CollectTurningColliderContacts,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestAgentLaunch,
    (Fn_Table)HandleSwitchedColliderActivation, 0, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsAgentRequestBlocked,
    (Fn_Table)AcceptAgentRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
    (Fn_Table)BuildTurningColliderHeadingMatrix, (Fn_Table)GetTurningColliderContactMode, (Fn_Table)IsTurningColliderGroundContact, (Fn_Table)IsGaugeBarAgentFree,
    (Fn_Table)AnswerAgentRosterPoll, (Fn_Table)ChooseAgentState, (Fn_Table)UpdateGaugeBarAgentState, (Fn_Table)LeaveAgentState,
    (Fn_Table)EnterGaugeBarAgentState, (Fn_Table)IsAgentTargetInRange, (Fn_Table)UpdateGaugeBarAgentGoal, (Fn_Table)BuildAgentPath,
    (Fn_Table)RestartAgentClip, (Fn_Table)SteerAgentAlongPath, (Fn_Table)SelectAgentTarget, 0,
} };
extern const ClassDescriptor<84> D_0021EC08 = { &D_00217C30, 0x1C, 0xB, 0x690, {
    (Fn_Table)InitBeatPressCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterSwitchedCollider, (Fn_Table)UnregisterSwitchedCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopySwitchedCollider, (Fn_Table)LoadBeatPressCollider, 0,
    0, (Fn_Table)HandleSwitchedColliderNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartBeatPressCollider, (Fn_Table)UpdateSwitchedCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetBeatPressColliderPositionAt, (Fn_Table)GetBeatPressColliderRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)HandleBeatPressColliderActivation, (Fn_Table)JudgeBeatPressInput, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsBeatPressColliderRequestBlocked,
    (Fn_Table)AcceptBeatPressColliderRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
} };
extern const ClassDescriptor<100> D_0021ED68 = { &D_0021BB58, 0x13, 0xB, 0xCA0, {
    (Fn_Table)InitTempoAgent, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterTempoAgent, (Fn_Table)UnregisterTempoAgent,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyAgent, (Fn_Table)LoadTempoAgent, 0,
    0, (Fn_Table)HandleTempoAgentNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadAgent,
    (Fn_Table)StartTempoAgent, (Fn_Table)UpdateTempoAgent, (Fn_Table)RecomputeTurningColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepAgent, (Fn_Table)SetColliderPosition, (Fn_Table)SetTurningColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetTurningColliderPose,
    (Fn_Table)ApplyTempoAgentTransform, (Fn_Table)DrawTempoAgent, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleAgentObjectEvent, (Fn_Table)ShowTempoAgentGauge, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyTurningColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeTurningColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestAgentMayContact, (Fn_Table)CollideColliderParts, (Fn_Table)CollideAgentWithObject, (Fn_Table)AddContactVertexBlendVelocity,
    (Fn_Table)ComputeAgentContactValue, (Fn_Table)ResolveTurningColliderContact, (Fn_Table)ClampAgentContactLimit, (Fn_Table)CollectTurningColliderContacts,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestAgentLaunch,
    (Fn_Table)HandleSwitchedColliderActivation, 0, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsAgentRequestBlocked,
    (Fn_Table)AcceptAgentRequest, (Fn_Table)HasSwitchedColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishSwitchedCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
    (Fn_Table)BuildTurningColliderHeadingMatrix, (Fn_Table)GetTurningColliderContactMode, (Fn_Table)IsTurningColliderGroundContact, (Fn_Table)IsTempoAgentFree,
    (Fn_Table)AnswerAgentRosterPoll, (Fn_Table)ChooseAgentState, (Fn_Table)UpdateTempoAgentState, (Fn_Table)LeaveTempoAgentState,
    (Fn_Table)EnterTempoAgentState, (Fn_Table)IsTempoAgentTargetInRange, (Fn_Table)UpdateTempoAgentGoal, (Fn_Table)BuildAgentPath,
    (Fn_Table)RestartAgentClip, (Fn_Table)SteerAgentAlongPath, (Fn_Table)SelectAgentTarget, 0,
} };
extern const ClassDescriptor<28> D_0021EF08 = { &D_00217418, 0x90, 0x0, 0x48, {
    (Fn_Table)InitTimeline, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadObjectProperties, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)FindTimelineTarget, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<48> g_entryTableObjectClass = { &D_00217498, 0x64, 0x1, 0x340, {
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
extern const ClassDescriptor<72> D_0021F058 = { &D_00218F80, 0x2A, 0x3, 0x7C0, {
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
extern const ClassDescriptor<72> D_0021F188 = { &D_00217568, 0x47, 0x3, 0x5E0, {
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
extern const ClassDescriptor<28> D_0021F2B8 = { &g_pointObjectClass, 0x81, 0x0, 0x60, {
    (Fn_Table)InitListedPointObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterListedPointObject, (Fn_Table)UnregisterListedPointObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyListedPointObject, (Fn_Table)LoadPointObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentPointObject, (Fn_Table)ConvertPointObjectPosition, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> D_0021F338 = { &D_00217740, 0x71, 0x0, 0x5C, {
    (Fn_Table)InitC71Object, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterC71Object, (Fn_Table)UnregisterC71Object,
    (Fn_Table)CloneObject, (Fn_Table)CopyC71Object, (Fn_Table)LoadPathCurveObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartC71Object, 0, 0, 0,
    0, (Fn_Table)ReparentPathCurveObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> D_0021F3B8 = { &D_00217740, 0x72, 0x0, 0x40, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterListedKeepObject, (Fn_Table)UnregisterListedKeepObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyListedKeepObject, (Fn_Table)LoadPathCurveObject, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentPathCurveObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> D_0021F438 = { &D_00217418, 0x8D, 0x0, 0x8F0, {
    (Fn_Table)InitOscillator, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadObjectProperties, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<88> D_0021F4B8 = { &D_0021A838, 0x14, 0xB, 0x760, {
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
extern const ClassDescriptor<84> D_0021F628 = { &D_00217C30, 0x16, 0xB, 0x660, {
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
extern const ClassDescriptor<100> D_0021F788 = { &D_0021BB58, 0xE, 0xB, 0xC50, {
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
extern const ClassDescriptor<84> D_0021F928 = { &D_00217C30, 0x18, 0xB, 0x6C0, {
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
extern const ClassDescriptor<100> D_0021FA88 = { &D_0021BB58, 0xF, 0xB, 0xC20, {
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
extern const ClassDescriptor<72> D_0021FC28 = { &D_00217568, 0x48, 0x3, 0x560, {
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
extern const ClassDescriptor<72> D_0021FD58 = { &D_00217568, 0x49, 0x3, 0x570, {
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
extern const ClassDescriptor<100> D_0021FE88 = { &D_0021BB58, 0x10, 0xB, 0xC20, {
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
extern const ClassDescriptor<100> D_00220028 = { &D_0021FE88, 0x11, 0xB, 0xC30, {
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
extern const ClassDescriptor<100> D_002201C8 = { &D_0021FE88, 0x12, 0xB, 0xC30, {
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
extern const ClassDescriptor<48> D_00220368 = { &D_00217498, 0x68, 0x1, 0x6A0, {
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
extern const ClassDescriptor<84> D_00220438 = { &D_00217C30, 0x19, 0xB, 0xBB0, {
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
extern const ClassDescriptor<84> D_00220598 = { &D_00217C30, 0x1B, 0xB, 0x710, {
    (Fn_Table)InitModeCollider, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterSwitchedCollider, (Fn_Table)UnregisterSwitchedCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopySwitchedCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandleModeColliderNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartModeCollider, (Fn_Table)UpdateModeCollider, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveModeCollider,
    (Fn_Table)StepModeCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyModeColliderTint, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleObjectEvent, 0, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureSwitchedColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
    (Fn_Table)HandleModeColliderActivation, (Fn_Table)ControlModeCollider, (Fn_Table)IsSwitchedColliderCameraFree, (Fn_Table)IsModeColliderRequestBlocked,
    (Fn_Table)AcceptModeColliderRequest, (Fn_Table)HasModeColliderAcceptedRequest, (Fn_Table)StartSwitchedColliderEffect, (Fn_Table)SetSwitchedColliderMode,
    (Fn_Table)FinishModeCollider, (Fn_Table)GetSwitchedColliderInteractFlags, (Fn_Table)ShowTypedTextCaptionBox, (Fn_Table)GetSwitchedColliderTarget,
} };
extern const ClassDescriptor<72> D_002206F8 = { &D_00217568, 0x4A, 0x3, 0x620, {
    (Fn_Table)InitGaugeModeObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartGaugeModeObject, (Fn_Table)UpdateGaugeModeObject, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleGaugeModeObjectEvent, (Fn_Table)ShowGaugeModeObjectBar, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<72> g_countdownColliderClass = { &D_00217568, 0x4B, 0x3, 0x570, {
    (Fn_Table)InitCountdown, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachPlacedObject, (Fn_Table)DetachPlacedObject, (Fn_Table)RegisterCollider, (Fn_Table)UnregisterCollider,
    (Fn_Table)ClonePlacedObject, (Fn_Table)CopyCollider, (Fn_Table)LoadCollider, 0,
    0, (Fn_Table)HandlePlacedObjectNotification, (Fn_Table)SendColliderNotification, (Fn_Table)PostLoadPlacedObject,
    (Fn_Table)StartCountdown, (Fn_Table)UpdateCountdown, (Fn_Table)RecomputeColliderFrame, (Fn_Table)ComputeColliderWorldFrame,
    (Fn_Table)SetColliderFrozen, (Fn_Table)ReparentCollider, (Fn_Table)ReframeColliderAnchors, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, (Fn_Table)MoveCollider,
    (Fn_Table)StepCollider, (Fn_Table)SetColliderPosition, (Fn_Table)SetColliderRotation, (Fn_Table)CopyPlacedObjectFrame,
    (Fn_Table)SetColliderVelocity, (Fn_Table)SetColliderSpin, (Fn_Table)GetPlacedObjectPositionAt, (Fn_Table)GetPlacedObjectRotationAt,
    (Fn_Table)ApplyPlacedObjectTransform, (Fn_Table)DrawCollider, (Fn_Table)QueuePlacedObjectModelParts, (Fn_Table)UpdateAttachmentFrames,
    0, (Fn_Table)ApplyObjectFrameOffsetToPose, (Fn_Table)RemoveObjectFrameOffsetFromPose, (Fn_Table)ChooseActiveAttachments,
    (Fn_Table)UpdateLinkConstraint, (Fn_Table)HandleCountdownObjectEvent, (Fn_Table)UpdateCountdownVisibility, (Fn_Table)ApplyColliderPendingMove,
    (Fn_Table)ApplyColliderPendingImpulse, (Fn_Table)ApplyColliderPendingImpulseHalfStep, (Fn_Table)UpdateColliderBounds, (Fn_Table)IgnoreColliderAttachmentStep,
    (Fn_Table)CopyColliderMeshesInFrame, (Fn_Table)NumberColliderParts, (Fn_Table)ComputeColliderImpulseResponse, (Fn_Table)AddParentVelocityToChildRows,
    (Fn_Table)TestCollidersMayContact, (Fn_Table)CollideColliderParts, 0, (Fn_Table)AddContactVertexBlendVelocity,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)NotifyContactHandlers,
    (Fn_Table)SaveColliderPreviousPosition, (Fn_Table)CaptureColliderPose, (Fn_Table)ApplyColliderAttachedSetContact, (Fn_Table)RequestColliderLaunch,
} };
extern const ClassDescriptor<74> D_00220958 = { &D_00218BD8, 0x24, 0x13, 0x6F0, {
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
extern const ClassDescriptor<84> D_00220A90 = { &D_00220438, 0x1A, 0xB, 0xC10, {
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
extern const T217D_Vt D_00220BF0 = { (ElementIntFn)InitScreenElement, (ElementFn)SetupScreenElementText, (ElementFn)UpdateScreenElementSlide, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawSpinningSpriteElement, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const ClassDescriptor<28> D_00220C40 = { &D_00217418, 0x91, 0x0, 0x60, {
    (Fn_Table)InitObject, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadObjectProperties, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<84> D_00220CC0 = { &D_00217C30, 0x1D, 0xB, 0x760, {
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
extern const ClassDescriptor<72> D_00220E20 = { &D_00217568, 0x4, 0x3, 0x550, {
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
extern const ClassDescriptor<48> g_idLinkedObjectClass = { &D_00217498, 0x66, 0x1, 0x340, {
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
extern const ClassDescriptor<48> D_00221020 = { &D_00217498, 0x67, 0x1, 0x570, {
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
extern const T217D_Vt D_002210F0 = { (ElementIntFn)InitScreenElement, (ElementFn)InitWarpMenu, (ElementFn)UpdateScreenElementSlide, (ElementIntFn)SetWarpMenuOpen, (ElementPadFn)HandleWarpMenuInput, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawWarpMenu, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const ClassDescriptor<48> g_partHolderObjectClass = { &D_00217498, 0x6A, 0x1, 0x300, {
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
extern const ClassDescriptor<48> g_currentPlacedObjectClass = { &D_00217498, 0x69, 0x1, 0x350, {
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
extern const T217D_Vt D_002212E0 = { (ElementIntFn)InitScreenElement, (ElementFn)InitSelectionCaption, (ElementFn)UpdateSelectionCaption, (ElementIntFn)SetSelectionCaptionOpen, (ElementPadFn)HandleSelectionCaptionInput, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawSelectionCaption, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00221330 = { (ElementIntFn)InitScreenElement, (ElementFn)InitGridSelector, (ElementFn)UpdateScreenElementSlide, (ElementIntFn)SetGridSelectorOpen, (ElementPadFn)HandleGridSelectorInput, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawGridSelector, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const T217D_Vt D_00221380 = { (ElementIntFn)InitScreenElement, (ElementFn)InitCommentaryPromptElement, (ElementFn)UpdateBestTimeState, 0, 0, (ElementFn)ResetScreenElement, 0, 0, (ElementTextFn)SetScreenElementText, (ElementFn)DrawFramedText, 0, (ElementTimeFn)GetScreenElementSlideInTime, (ElementTimeFn)GetScreenElementHoldTime, (ElementTimeFn)GetScreenElementSlideOutTime, (ElementFn)ShowScreenElement, (ElementFn)HideScreenElement, (ElementIntFn)SetScreenElementMode, (ElementClockFn)SetScreenElementClock, (ElementPairFn)AreScreenElementsTogether, 0 };
extern const ClassDescriptor<48> g_codeChecksumClass = { &D_00217498, 0x6B, 0x1, 0x6E0, {
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
extern const ClassDescriptor<28> D_002214A0 = { &D_00217418, 0x6C, 0x0, 0x2360, {
    (Fn_Table)InitWorldPools, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadWorld, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, (Fn_Table)UpdateWorld, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
extern const ClassDescriptor<28> D_00221520 = { &D_00217418, 0x6D, 0x0, 0x590, {
    (Fn_Table)InitCamera, (Fn_Table)ApplyObjectClassDefaults, (Fn_Table)AddObjectToParentList, (Fn_Table)RemoveObjectFromParentList,
    (Fn_Table)AttachObject, (Fn_Table)DetachObject, (Fn_Table)RegisterObject, (Fn_Table)UnregisterObject,
    (Fn_Table)CloneObject, (Fn_Table)CopyObjectData, (Fn_Table)LoadObjectProperties, 0,
    0, 0, (Fn_Table)SendObjectNotification, 0,
    (Fn_Table)StartObject, 0, 0, 0,
    0, (Fn_Table)ReparentObject, 0, (Fn_Table)AddObjectListener,
    (Fn_Table)RemoveObjectListener, (Fn_Table)AddObjectCallback, (Fn_Table)RemoveObjectCallback, 0,
} };
