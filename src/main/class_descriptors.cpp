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
#include "functions/agent.h"
#include "functions/agent_registration.h"
#include "functions/anim_record.h"
#include "functions/arc_element.h"
#include "functions/base_object.h"
#include "functions/camera.h"
#include "functions/camera_controller.h"
#include "functions/child_group_object.h"
#include "functions/class75_list.h"
#include "functions/collider.h"
#include "functions/collider_contact.h"
#include "functions/colored_triangle_set.h"
#include "functions/commentary_best_time.h"
#include "functions/cone_agent.h"
#include "functions/effect.h"
#include "functions/effect_spawner.h"
#include "functions/entry_queue.h"
#include "functions/flagged_object.h"
#include "functions/game_progress.h"
#include "functions/gauge_collider.h"
#include "functions/gauge_manager.h"
#include "functions/hit_count_collider.h"
#include "functions/item_column.h"
#include "functions/link_constraint.h"
#include "functions/main_loop.h"
#include "functions/mode_walker.h"
#include "functions/movie_player.h"
#include "functions/object_cycler.h"
#include "functions/object_gatherer.h"
#include "functions/object_pool.h"
#include "functions/on_off_object.h"
#include "functions/oscillator.h"
#include "functions/pair_controller.h"
#include "functions/path_curve.h"
#include "functions/path_follower.h"
#include "functions/path_speed_collider.h"
#include "functions/placed_object.h"
#include "functions/placed_object_model.h"
#include "functions/player.h"
#include "functions/player_aim.h"
#include "functions/player_link.h"
#include "functions/player_mode.h"
#include "functions/player_request.h"
#include "functions/player_state2.h"
#include "functions/point_graph.h"
#include "functions/pooled_object.h"
#include "functions/pose_source.h"
#include "functions/range_record.h"
#include "functions/screen_element.h"
#include "functions/selection_menus.h"
#include "functions/sound_system.h"
#include "functions/state_notifier.h"
#include "functions/state_walker.h"
#include "functions/switched_collider.h"
#include "functions/target_follower.h"
#include "functions/target_lists.h"
#include "functions/text_panel.h"
#include "functions/timed_object.h"
#include "functions/tint_blend_collider.h"
#include "functions/turning_collider.h"
#include "functions/warp_menu.h"
#include "functions/world.h"
#include "functions/world2_boss.h"
#include "functions/world5_boss.h"
#include "functions/world_listed_object.h"
#include "functions/zone_collider.h"
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

void SetSwitchedColliderMode();
void InitPauseMenu(T217D_6D0* self);
void SetPauseMenuOpen(T217D_6D0* self, s32 mode);
void UpdatePauseMenu(T217D_6D0* self);
void SetPauseMenuMode(T217D_6D0* self, s32 v);
void ShowPauseMenu(T217D_6D0* self);
void HidePauseMenu(T217D_6D0* self);
void DrawPauseMenu(T217D_6D0* self);
void ComputeObjectGathererContactValues();
void ResolveObjectGathererContact();
void InitEffect(Effect* self, void* pos, f32 scale, s32 flags);
void UpdateColliderBounds(Collider* self);
void ComputePathFollowerContactValue();
void InitWarpMenu(T217D_0F0* self);
void HandleWarpMenuInput(T217D_0F0* self, PadRecord* t);
void SetWarpMenuOpen(T217D_0F0* self, s32 a1);
void DrawWarpMenu(T217D_0F0* self);


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
