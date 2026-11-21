// SPDX-License-Identifier: AGPL-3.0-or-later
// 0x1233C0 to 0x130168: the state triggers (classes 0x22 and 0x2F), the placed object's set-up,
// update and loading (func_00123ED0 to func_001289C0), its range, sound and colour records, the
// code checksum, the animation players and their events, the id filter object, the sector stream
// reader and three object helpers. Its .rodata runs from 0x2499F0 to 0x249C90, its .data from
// 0x260E70. Its start is an edge retail proves; its end is a choice, the cut before
// curve_segment.cpp made on loop.c's threshold (that file's head), which no boundary signal shows.
// Between the two it could still be several files.
#include "common.h"
#include "asm_functions.h"
#include "asm_func.h"
#include "vu0.h"
#include "mul_rotation.h"
#include "game_clock.h"
#include "list_iter.h"
#include "placed_object.h"
#include "state_trigger.h"
#include "timed_object.h"
#include "transform_object.h"
#include "state_walker.h"
#include "screen_element.h"
#include "masked_collider.h"
#include "world.h"
#include "animation.h"
#include "attachment.h"
#include "anim_curve.h"
#include "range_record.h"
#include "cursor_animator.h"
#include "sound_record.h"
#include "screen_fade.h"
#include "object_link.h"
#include "target_binding.h"
#include "globals.h"
#include "object_cycler.h"
#include "paired_object.h"
#include "buffered_stream.h"
#include "ring_params.h"
#include "flag_table.h"
#include "id_lookup_object.h"
#include "key_record.h"
#include "object_pool.h"
#include "script_value.h"
#include "sound_level.h"
#include "effect.h"
#include "texture_render_object.h"
#include "value_list_object.h"
#include "shapes.h"
#include "anim_curve.h"
#include "object_finder.h"
#include "list_walk.h"
#include "model_part.h"
#include "scaled_transform.h"
#include "functions/agent.h"
#include "functions/anim_record.h"
#include "functions/base_object.h"
#include "functions/blend_animation.h"
#include "functions/camera.h"
#include "functions/collider.h"
#include "functions/disc_access.h"
#include "functions/effect_spawner.h"
#include "functions/entry_queue.h"
#include "functions/flagged_object.h"
#include "functions/game_progress.h"
#include "functions/group_marker.h"
#include "functions/iop_file_client.h"
#include "functions/item_column.h"
#include "functions/main_loop.h"
#include "functions/matrix.h"
#include "functions/movie_player.h"
#include "functions/oscillator.h"
#include "functions/pad_input.h"
#include "functions/placed_object_model.h"
#include "functions/player.h"
#include "functions/point_graph.h"
#include "functions/pooled_object.h"
#include "functions/range_record.h"
#include "functions/screen_element.h"
#include "functions/sound_system.h"
#include "functions/state_walker.h"
#include "functions/text_panel.h"
#include "functions/warp_menu.h"
#include "functions/world_contacts.h"
#include "functions/zone_collider.h"

// Types other files define, named by the parameters of their functions declared here.
struct AnimatorOwner;
struct AttachmentBlock;
struct AttachmentCopy;
struct AttachmentTargets;
struct Counter;
struct FadeRequestBlock;
struct PartDrawRequest;
struct ListLink;
struct MarkStacks;
struct ModelRecord;
struct MoviePlayer;
struct PlayingSound;
struct Quad_001B4580;
struct PackedRampProfile;
struct RampProfile;
struct RefCounted;
struct ScriptListBuilder;
struct ValueRange;
struct ZoneTargetEntry;
#include "code_checksum.h"
#include "switched_collider.h"
#include "shapes.h"
#include "id_filter_object.h"
#include "aim_blend_grid.h"
#include "object_message.h"
#include "queued_call.h"
#include "stream_reader.h"
#include "key_id.h"
#include "game_progress.h"
#include "base_object.h"
#include "stream_reader_window.h"

f32 g_defaultPositionSpring[4] = { 0.0f, 15.0f, 0.0149999997f, 0.0f };
f32 g_defaultVelocitySpring[4] = { 0.0f, 2.5f, 0.00249999994f, 0.0f };
f32 g_defaultRotationSpring[4] = { 0.0f, 15.0f, 1.5f, 0.0f };
f32 g_defaultSpinSpring[4] = { 0.0f, 2.5f, 0.25f, 0.0f };
f32 g_defaultPositionRamp[4] = { 1500.0f, 0.0f, 0.5f, 4500.0f };
f32 g_defaultRotationRamp[4] = { 15.0f, 0.0f, 0.5f, 45.0f };
f32 g_fadeRampProfile[4] = { 2.0f, 0.0f, 0.100000001f, 0.0f };
f32 g_steeringHeadingCurve[4] = { -50.0f, 4.0f, 0.0f, 0.0f };
f32 g_steeringHeadingLimits[4] = { 0.0f, 400.0f, 0.0f, 0.0f };

AnimationPlayer* NewAnimationPlayer(World* pool);
void CloseStreamReader(StreamReader* a0);

void GatherAxisCurveTimes(WeightCurve** axis, s32* outCount, f32** outTimes);

extern void EvaluateVectorKeyCurve(s32, VectorKey*, s32, void*, void*);

extern void EvaluateVectorKeyCurve(s32, VectorKey*);
extern void GetVectorKeyTimes(s32, VectorKey*, s32*, f32**);

extern void EvaluateAxisCurves(WeightCurve**, PlacedObject*, void*, Vec4*, void*, s32, f32, f32);
extern "C" void* FillMemory(void* p, s32 value, s32 size);

void ReadAxisCurves(WeightCurve** a, Vec4* b, Stream83* c);

extern void EvaluateVectorKeyCurve(s32, VectorKey*, void*, f32*, s32, f32, f32);

extern void ReadVectorKeys(s32*, VectorKey**, Stream83*);


extern World* g_currentWorld;

void CopyMemory(void* dst, void* src, u32 size);

void InitPoseSource(Attachment* self, PlacedObject* value);

void ReleasePoseSource(Attachment* self, s32 flags);

extern f32 g_gameTime[];
void GetOwnerPosition(Attachment* self, Vec4* a1, Vec4* a2);
s32 ApplyAnimationLoopMode(AnimationPlayer* t, f32* a, f32* b);

void GetOwnerRotation(Attachment* self, Mat3* a, Vec4* b);


extern u8 g_flagTable[];



s32 IsObjectOfKind(BaseObject* list, s32 key);


s32 AppendPropertyToScriptList(ScriptListBuilder* self, void* value);

// An entry of PlacedObject::partStates: its word at +8.
struct PartState { u8 pad[8]; s32 value; };

// One of the 0x70-byte parts at PlacedObject::drawParts: the kind and the value
// func_00126BC0 gives each.
struct DrawPart {
    u8 pad00[0x14];
    s32 type;               // 0x14
    u8 pad18[0x6C - 0x18];
    union {
        s32 value;          // 0x6C
        void* object;       // 0x6C: type 2's, the object drawing it (func_00126BC0)
    };
};


extern f32 g_valueRampProfile[4];
extern f32 g_frameStep;
extern f32 g_frameDt;

void AppendQueuedCall(World* self, void* code, void* arg, s32 c, s32 d);
void StartPlacedObject(void* self);

void GetOwnerValue(Attachment* self, f32* value, f32* slope);

extern void GetOwnerValue(Attachment* self, f32* a1, f32* a2);

extern void GetIdentityMatrix(Attachment* self, Mat3* a1);

void SetCountedObjectCounter(CountedObject* node, StateTrigger* value);

extern u8 D_002623D8[];

void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec4* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

// The position curves' tables, defined at the end of this file.
extern const PositionCurveVt g_positionCurveKind0Methods;
extern const PositionCurveVt g_positionCurveKind1Methods;
extern const PositionCurveVt g_positionCurveKind2Methods;
void* AllocateZeroedFrontMemory(s32 n);

void SetPlacedObjectVelocity(void* a, void* b);
void SetPlacedObjectSpin(void* a, void* b);



extern const RotationCurveVt g_rotationCurveKind0Methods;
extern const RotationCurveVt g_rotationCurveKind1Methods;
extern const RotationCurveVt g_rotationCurveKind2Methods;

extern const ScaleCurveVt g_scaleCurveKind0Methods;
extern const ScaleCurveVt g_scaleCurveKind1Methods;
void* AllocateZeroedFrontMemory(s32 n);

extern u8 g_ownerPoseSourceMethods[];


// The dispatch tables func_00121160 gives each kind of curve: three functions, or one and a
// shared one, each table followed by a zero word.
void EvaluateTangentWeightCurve();
void ReadTangentWeightCurve();
void GetTangentWeightCurveTimes();
void EvaluateControlPointWeightCurve();
void ReadControlPointWeightCurve();
void GetControlPointWeightCurveTimes();
void EvaluateLinearWeightCurve();
void ReadLinearWeightCurve();
void GetLinearWeightCurveTimes();
void GetNoWeightCurveTimes();
void EvaluateAngleBlendCurve();
void EvaluateValueBlendCurve();
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
extern const WeightCurveVt g_weightCurveKind0Methods;
extern const WeightCurveVt g_weightCurveKind1Methods;
extern const WeightCurveVt g_weightCurveKind2Methods;
extern const WeightCurveVt g_weightCurveKind3Methods;
extern const WeightCurveVt g_weightCurveKind4Methods;
void* AllocateZeroedFrontMemory(s32 n);


// Two stores of the set-up written as small inline helpers, the shape that matches: a value
// passed as an int, and a matrix copied through its own pointer (as each copy's own register).
struct SetupStores {
    static void SetB2CA(PlacedObject* o, s32 value) { o->b2CA = value; }
    static void Copy(Mat3* dst, const Mat3* src) { *dst = *src; }
};

#include "world.h"
#include "object_cycler.h"
#include "paired_object.h"
struct BufferedStream;

void ClearRootTries(PlacedObject* self);





// What slot 29 tells the object's listeners (kind 3): the position before, and the object.
struct MoveNotice {
    void* self;
    u8 pad[0xC];
    Vec4 q;
};

void SettlePoseSourceModes(Attachment* self);

s32 IsVelocityNegligible(void* a);
void ClearRootTries(void* self);

s32 IsSpinNegligible(void* a);



void UpdateObjectTree(void* self, f32 f);


void ResolveFollowRecordObjects(PlacedObject* self);
void SavePlacedObjectInitialFrame(void* self);
void SetAimTarget(PlacedObject* self, void* b);


void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec4* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);



void StartAnimationFromContext(PlacedObject* self);
void AppendQueuedCall(World* self, void* code, void* arg, s32 c, s32 d);
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec4* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

void* CopyToFrontMemory(s32 size, void* src);
Attachment* ClonePoseSource(Attachment* src, World* world, PlacedObject* self);
void InsertAttachment(PlacedObject* self, Attachment* src);
void CopyMemory(void* dst, void* src, u32 size);

// NEAR: the branches and the 0x40-byte copy loop match; retail loads both quads of a pair before
// storing them (and computes the loop end in $v0), ours interleaves load and store.


extern u8 g_unitScale[];










void ApplyPulsingColorToObjectTree(PlacedObject* self, f32 dt);

void FindNearestAnimationPathTime(Animation* self, PlacedObject* owner, f32 start, Vec4* point, f32* outT, Vec4* outPos,
                   Vec4* outDir);
void CreateAnimationPlayer(Animation* self, BaseObject* alt, s32 npairs, TargetBinding* pairs, s32 flags, AnimationPlayer** out, f32 fa, f32 fb);

// A value kept within [lo, hi].
struct ClampRange {
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        if (x < lo) {
            return lo;
        }
        if (hi < x) {
            return hi;
        }
        return x;
    }
};

struct FindStartAnimation {
    static Animation* Of(PlacedObject* self, AnimationStart* ctx)
    {
        if (ctx->anim != 0) {
            return ctx->anim;
        }
        return (Animation*)FindFirstObjectById(self->world, 0x104, ctx->key, self);
    }
};

struct StartBindingFrame : TargetBinding { u8 pad0[8]; f32 tmp; };

struct TakeFrameLocals {
    u8 a20[16];
    u8 a30[16];
    u8 a40[16];
    u8 a50[16];
    u8 pad60[0x30];
};

void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);
void TransformRotationBetweenFrames(PlacedObject* from, PlacedObject* to, Mat3* in, Mat3* out);
void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);
void ComputeObjectMotionInFrame(PlacedObject* self, PlacedObject* top, Vec4* origin, Vec4* vel, Vec4* velSum, Vec4* spin, Vec4* spinSum);
void ConvertVectorsBetweenObjectFrames(BaseObject* a, BaseObject* b, void* c, void* d, void* e, s32 f, s32 g, u8* h, u8* i, s32 j, s32 k);

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table g_trackPoseSourceMethods[10];
Attachment* CreatePoseSource(World* root, PlacedObject* value, const T2195_Vt* table);

void SetOrientationSourceMode(PlacedObject* self, s32 value);

void EnsureAimAttachment(void* self);

extern u8 g_zeroQuad[];

extern u8 g_unitRange[];


extern RangeRecord g_sharedRangeRecord;
void InitRangeRecord(void* p);

void* AllocateFrontMemory(s32 n);


void SetRotationRamp(PlacedObject* self, PackedRampProfile* src);

void SetGroupActivityMode(PlacedObject* self, u32 value);


Class75Object* FindOrCreateClass75Object(PlacedObject* self);




extern ColorRecord g_colorPresets[4];

void EnsureColorRecord(void* self);




void* AllocateZeroedFrontMemory(s32 n);

void InitRangeRecord(void* a0);

void EnsureAimAttachment(PlacedObject* self);

void* CreateTypedRecord(s32 index, void* a1, BaseObject* a2, s32 a3, s32 a4);

void* EnsureRangeRecord(PlacedObject* self);






void EnsureSoundRecord(PlacedObject* self);






// A quadword moved whole (lq/sq), and the frame of the four scaled-spring setters: the
// default profile, the argument as a quadword and their product.
typedef u64 U128 __attribute__((mode(TI)));
struct ScaledSpringFrame { U128 r; U128 a; U128 b; };

void *StoreFloatAsQuadword(U128* out, f32 value);
void* CopyQuadword(u128* out, void* src);
U128 StoreQuadword(u128* out, u128 v);
void SetVelocitySpring(PlacedObject* self, Quad16* src);

// A ramp profile (+0x21C, +0x220) as the setters copy it: four floats at an address they do not
// trust to be aligned.
struct __attribute__((packed)) PackedRampProfile { f32 x, y, z, w; };

void SetPositionRamp(PlacedObject* self, PackedRampProfile* src);

void* AllocateFrontMemory(s32 size);


extern void SetRotationRamp(PlacedObject* self, PackedRampProfile* src);

void* AllocateFrontMemory(u32 size);



RangeRecord* GetRangeRecord(PlacedObject* self);






void SetPositionSpring(PlacedObject* self, Quad16* value);


// Newly matched US functions from the small-function wave.
extern void SetPositionSourceMode(PlacedObject* self, s32 value);
extern void EnsureBaseAttachment(void*);
extern void SortAttachments(void*);
extern void EnsureAimAttachment(void*);
extern void EnsureSoundRecord(PlacedObject* self);
extern void EnsureColorRecord(void*);

extern "C" f32 ArctangentOfRatio(f32 y, f32 x);



extern ColorRecord g_defaultColorRecord[2];




struct EulerLocals { f32 tmp[4]; f32 out[4]; u8 pad[0x20]; };



// NEAR: same bytes except the load order of the arguments to func_001BFCD8 (retail loads a0, a4, f12, a1, f13..f15 and f16 last, in the delay slot)

void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec4* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

// NEAR: same bytes except the load order of the arguments to func_001BFCD8 (retail loads a0, a4, f12, a1, f13..f15 and f16 last, in the delay slot)

// NEAR: same bytes except the prologue order: retail loads the crc word and the table base before the n > 0 test (lw v0, addiu t1, then blez); ours tests first
s32 g_checksumMismatch[4];


s32 ReadBufferedS16(BufferedStream* self);
u16 ReadBufferedU16(BufferedStream* self);
s32 ReadBufferedS8(BufferedStream* self);
s32 ReadBufferedU8(BufferedStream* self);
void MoveAnimationTrackToEnd(Animation* a, AnimationTrack* b);
void ReadAnimationEvents(void* unused, Stream83* r, s32 flag, s32* count, AnimEvent** out);
void ReadPropertyRecords(void* self, void* obj);
PositionCurve* CreatePositionCurve(s32 cc);
RotationCurve* CreateRotationCurve(s32 cc);
ScaleCurve* CreateScaleCurve(s32 cc);
WeightCurve* CreateWeightCurve(u32 kind);

void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);
void TransformRotationBetweenFrames(PlacedObject* from, PlacedObject* to, Mat3* in, Mat3* out);

s32 ReadBufferedU32(BufferedStream* self);
void ReadBufferedRotation3(BufferedStream* self, void* out);
s32 ReadBufferedS16(BufferedStream* self);
void ReadBufferedVector3(BufferedStream* src, void* dst);
f32 ReadBufferedFloat(BufferedStream* r);
s32 ReadBufferedU8(BufferedStream* self);

void SetRotationSpring(PlacedObject* self, Quad16* src);

void SetSpinSpring(PlacedObject* self, Quad16* src);

void InsertAttachment(PlacedObject* self, Attachment* src);

extern u8 g_aimSwitchPoseSourceMethods[];

extern const Fn_Table g_identityPoseSourceMethods[];


extern const Fn_Table g_aimPoseSourceBases[];




extern "C" void* FillMemory(void* p, s32 value, s32 size);
void SettlePoseSourceModes(Attachment* self);

// The 0xC-byte payload of kinds 21 and 23: the owner id of the attachment the event drives
// (RunAnimationEvent reads it first), then two floats.
struct EventAttachmentDrive { s32 owner; f32 f4; f32 f8; };
// The 0x28-byte record of a kind 0 event (a sound): up to six sound ids, one picked at random
// each time other than the last (func_0012D5D0), the object it plays on, and its ranges.
struct SoundChoice {
    s16 count;
    s16 ids[6];
    s16 cur;
    s16 target;
    u8 pad12[2];
    s32 nearRange;
    s32 farRange;
    f32 pitch;
    f32 startParam;
    f32 baseVolume;
};

s32 ReadBufferedS8(BufferedStream* self);
void* AllocateZeroedFrontMemory(s32 n);
void ReadOptionalBufferedBlock(BufferedStream* self, u8** out);
s32 ReadBufferedS16(BufferedStream* self);
s32 ReadBufferedS32(BufferedStream* self);
f32 ReadBufferedFloat(BufferedStream* r);
s32 ReadBufferedU8(BufferedStream* self);
u16 ReadBufferedU16(BufferedStream* self);
void ReadBufferedStreamBytes(BufferedStream* self, s32 remaining, void* out);
void ReadBufferedString(BufferedStream* self, u8** out);

#define F32(x) (*(f32*)&(x))
#define H0(x) (*(s16*)&(x))
#define H2(x) (*((s16*)&(x) + 1))

// An entry of the table at PlacedObject::keyedValues (f2B8 of them): a key and the values it selects.
struct KeyedValues { s32 key; f32* values; };

// Sets an attachment's mode3 and tells whether it changed.
struct SetMode3 {
    static s32 Of(Attachment* a, s32 v) { s32 o = a->mode3; a->mode3 = v; return o != v; }
};
extern const Fn_Table g_linkedPoseSourceMethods[];

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void CopyPoseSource();
void ReleasePoseSource();
void InitLinkedPoseSource();
void GetLinkedPosition();
void GetLinkedRotation();
void GetLinkedValue();
void GetLinkedMatrix();
f32 GetLinkedIndexedValue();
void InitIdentityPoseSource(IdentityMatrixAttachment* self, PlacedObject* owner);
void GetIdentityPosePosition();
void GetIdentityPoseRotation();
void GetNextPoseSourceValue();
void GetIdentityPoseMatrix();
f32 GetIdentityPoseIndexedValue();
void EvaluateNoPositionCurve();
void GetNoPositionCurveTimes();
void EvaluateNoRotationCurve();
void GetNoRotationCurve();
void GetNoRotationCurveTimes();
void EvaluateNoScaleCurve();
void GetNoScaleCurveTimes();
void EvaluateNoWeightCurve();
void GetOwnerPosition();
void GetOwnerValue();
void GetIdentityMatrix();
f32 GetOwnerIndexedValue();
void InitAimPoseSource();
void GetAimPoseRotation();
extern const Fn_Table g_linkedPoseSourceMethods[10];
extern const Fn_Table g_identityPoseSourceMethods[10];
extern const Fn_Table g_aimPoseSourceBases[26];

// The script list a property getter fills (object_properties defines it; AppendPropertyToScriptList).
struct ScriptListBuilder;
s32 AppendPropertyToScriptList(ScriptListBuilder* self, void* value);

struct ListWalkNextPlaced {
    static PlacedObject* Of(ListFrame* it)
    {
        PlacedObject* obj = *(PlacedObject**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};


struct NextAttachment {
    static Attachment* Of(ListFrame* it)
    {
        Attachment* node = *(Attachment**)it->link;
        it->link = (u8*)node + it->offset;
        return node;
    }
};

ColorRecord g_colorPresets[4] = {
    { { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x42F00000, 0x433E0000, 0x42E60000, 0x00000000, 0x42F00000, 0x433E0000, 0x42700000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } },
    { { 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x437F0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } },
    { { 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x42F00000, 0x437F0000, 0x437F0000, 0x00000000, 0x42F00000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } },
    { { 0x00000003, 0x00000000, 0x00000000, 0x00000000, 0x43700000, 0x437F0000, 0x437F0000, 0x00000000, 0x43700000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } }
};

ColorRecord g_defaultColorRecord[2] = {
    { { 0x00000004, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x437F0000, 0x437F0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } },
    { { 0x00000005, 0x00000000, 0x00000000, 0x00000000, 0x43960000, 0x437F0000, 0x437F0000, 0x00000000, 0x43960000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } }
};

void CopyTrackPoseSource();
void ReleaseTrackPoseSource();
void GetTrackPosition();
void GetTrackRotation();
void GetTrackValue();
void GetTrackScaleMatrix();
f32 GetTrackIndexedValue();

extern u8 g_codeChecksumEnd[];
void InitPlacedObject(void* self);




void ApplyPoseSource(Attachment* self, s32 flag);



s32 IsReadPending(StreamReader* self);
extern "C" s32 SyncDiscNCommand(s32 mode);
void CommitChunk(StreamReader* self);


void StartLinkedObjectAnimation(Animation* self);
void AppendQueuedCallOnce(World* self, void* a1, void* a2, s32 a3, s32 a4);

void CreateAnimationPlayerWithoutPresetTargets(Animation* self, BaseObject* alt, s32 flags, AnimationPlayer** out, f32 fa, f32 fb);


AnimationPlayer* FindAnimationPlayerByScope(Animation* self, s32 key);
void CreateAnimationPlayerWithoutPresetTargets(Animation* self, BaseObject* alt, s32 flags, AnimationPlayer** out, f32 fa, f32 fb);
void SeekAnimationPlayer(AnimationPlayer* self, s32 mode, f32 a, f32 b);

void FindOrCreateAnimationPlayerAndSeek(void* self, BaseObject* key, s32 a2, s32 a3, void** out, f32 fa, f32 fb);

void SetAnimationPlayerSpeed(AnimationPlayer* self, f32 x);
void ApplyListedPoseSources(AnimationPlayer* a0, s32 flag);
void SettleListedPoseSources(AnimationPlayer* self);
void RunSeekAnimationEvents(AnimationPlayer* self, Animation* sub, s32* out);
void StopAnimationPlayer(AnimationPlayer* self);
void SeekAnimationEventCursor(AnimationPlayer* self);

void SettlePoseSourceModes(Attachment* self);


TrackFollowAttachment* FindPlayerAttachmentByOwner(AnimationPlayer* a0, s32 owner);

void SortAttachments(void* p);






extern "C" s32 GetDiscError();

void FreeObjectMemory(void* self);

s32 OpenSectorStream(StreamReader *self, s32 a1, s32 a2);

void AcquirePadSelectFlag(World* a0);
void ReleasePadSelectFlag(World* self);

void StopAnimationPlayer(AnimationPlayer* self);



s32 IsObjectOfKind(BaseObject* list, s32 key);

void StartChunkRead(StreamReader* self);

s32 PollChunkRead(StreamReader* a0);

struct AnimationPlayerTable { const void* tinfo; s32 f4; };
extern const AnimationPlayerTable g_animationPlayerMethods;


void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);

struct EndEventLocals { s32 a; s32 b; };

void RunAnimationEvent(AnimationPlayer* self, AnimEvent* msg, s32* out);
void NotifyAnimationPlayerCallbacks(AnimationPlayer* self, s32 a1, void* a2);
void ReleaseCallRecords(World* self, T219CHook* node);
void SetAnimationPlayerPadSelect(AnimationPlayer* self, s32 v);
void RemoveQueuedCalls(World* self, u32 mask, void* code, void* arg, s32 k2, s32 k3);

extern "C" f32 FloatRemainder(f32 x, f32 y);



// was NEAR: call result is stored directly (retail copies v0 to v1 first, then s1=v1 for the out pointer); 5 lines differ


void* AllocateBackMemory(s32 size);

struct EventObjectPair {
    s32 animationId;
    s32 targetId;
    s32 f8;
    f32 fC;
};
union EventScratch {
    SlotMessage req;
    Vec4U v[3];
    void* p[3];
    s32 w[3];
};



extern u8 g_padRecord[];
extern u8 g_moviePlayer[];

void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec4* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
void FadeInPlacedObject(Collider* t, f32 v);
void FadeOutPlacedObject(Collider* t, f32 v);
void ApplyListedPoseSources(AnimationPlayer* a0, s32 flag);
// the node keeps the inline setter of its second mode byte that retail's code calls (see NOTES.md)
struct TrackAttachment : TrackFollowAttachment {
    void SetMode(s32 mode) { mode1 = mode; }
};
void ChoosePoseSourceModes(Attachment* obj);
void CreateAnimationPlayerWithoutPresetTargets(Animation* self, BaseObject* alt, s32 flags, AnimationPlayer** out, f32 fa, f32 fb);
void NotifyAnimationPlayerCallbacks(AnimationPlayer* self, s32 a1, void* a2);
void SelectValueEntryByKey(PlacedObject* self, s32 key);
s32 IsObjectOfKind(BaseObject* list, s32 key);
void ShowCountedScreenElement(World* w);
void HideCountedScreenElement(World* w);
void SetWorldValueAndTarget(World* w, f32 v);
void SetWorldValueTarget(World* w, f32 v);

struct FalloffRange { u32 field0; f32 minimum; f32 maximum; };
struct RangeFalloffOwner { u8 pad0[8]; FalloffRange* range; };




void StartPlacedObject(PlacedObject* self);
s32 IsObjectOfKind(BaseObject* list, s32 key);


// kept: the bitfields make `n->f10 = n->f11 = 3` store from two registers, as retail does
struct TrackAttachmentBits {
    u8 pad0[0x10]; s32 mode0 : 8; s32 mode1 : 8; s32 mode2 : 8; s32 mode3 : 8; s32 key;
    u8 pad1[0x1C - 0x18]; AnimationPlayer* player;
    u8 pad2[0x28 - 0x20]; s32 index;
};

void PushBackMemoryMark(void);
Attachment* CreateTrackAttachment(BaseObject* item);
void ChoosePoseSourceModes(Attachment* obj);
void InsertAttachment(PlacedObject* self, Attachment* src);
void PopBackMemoryMark(void);
void RunAnimationEvent(AnimationPlayer* self, AnimEvent* msg, s32* out);
void ApplyListedPoseSources(AnimationPlayer* a0, s32 flag);


void StartChunkRead(StreamReader* self);
void CommitChunk(StreamReader* self);

extern u8 g_markStacks[];
void AddMarkRootList(MarkStacks* self, R11B008List* list);

// When the object does not hold its count, tells its counter that one more is done; then runs the
// masked collider's activation handling.
void ReleaseCountedObject(CountedObject* object)
{
	if (!object->hold)
		CountStateTriggerDone(object->counter);
	HandleMaskedColliderActivation(object);
}

void SetCountedObjectCounter(CountedObject* state, StateTrigger* value)
{
    state->counter = value;
}

// Initialises the collider with state -1 and takes an index from the flag table.
void InitStateTrigger(StateTrigger* self)
{
    InitCollider(self);
    self->state = -1;
    self->id6B0 = TakeFlagTableIndex((FlagTable*)g_flagTable);
}

// Start of a state trigger: queues ResolveStateTriggerObjects, starts the placed object, and scans
// its children, remembering the first of the kind 0x88 as found558.
void StartStateTrigger(StateTrigger* self)
{
    WordListFrame fr;
    sptr s0;
    AppendQueuedCall(self->world, (void*)ResolveStateTriggerObjects, self, 0, 0);
    StartPlacedObject(self);
    sptr e = (sptr)&self->children;
    fr.link = e;
    fr.list = e;
    s32 link = ((ObjectList*)e)->offset;
    sptr old = (sptr)g_activeListFrames;
    fr.prev = old;
    fr.offset = link;
    g_activeListFrames = (ListFrame*)&fr;
    sptr head = *(sptr*)e;
    fr.link = head + fr.offset;
    s0 = head;
    if (s0 != 0) {
        do {
            if (IsObjectOfKind((BaseObject*)s0, 0x88) != 0) {
                if (self->found558 == 0) {
                    self->found558 = (void*)s0;
                }
            }
            sptr nx = *(sptr*)fr.link;
            fr.link = nx + fr.offset;
            s0 = nx;
        } while (s0 != 0);
    }
    if (self->found558 != 0) {
        self->walker = (StateWalker*)CreateStateWalker((StateGraph*)self->found558, self, -1, 1);
        ResolveAndStartObject((BaseObject*)self->found558);
    }
    g_activeListFrames = (ListFrame*)fr.prev;
}

// Copies the collider but keeps the trigger's own flag-table index.
void CopyStateTrigger(StateTrigger* object, StateTrigger* src)
{
	s32 value = object->id6B0;
	CopyCollider(object, src);
	object->id6B0 = value;
}

// Per-frame update of the trigger: while active (state 2) it falls back to state 0 when the timeout
// has passed. It goes to state 1 once all its counted objects are done, and while the player is in
// state 9 it sends each counted object a call (its method m48).
void UpdateStateTrigger(StateTrigger* self, f32 dt)
{
    UpdateCollider(self, dt);
    if (self->state == 2 && self->timeout != 0.0f) {
        if (self->timeout < g_gameTime[0] - self->stateTime) {
            SetStateTriggerState(self, 0);
            goto done;
        }
    }
    if (self->count1 > 0) {
        if (self->done == self->count1) {
            SetStateTriggerState(self, 1);
            goto done;
        }
    }
    if (self->state != 2) {
        goto done;
    }
    if (g_player->state != 9) {
        goto done;
    }
    for (s32 i = 0; i < self->count1; i++) {
        void* p = FindFirstObjectById(self->world, 0x104, self->items1[i], self);
        if (p != 0 && IsObjectOfKind((BaseObject*)p, 0x22) != 0) {
            CountedObject* o = (CountedObject*)p;
            o->desc20()->m48(o);
        }
    }
done:
    ;
}

// Looks up the trigger's three id lists in the world (counters of kind 0x22, timed outputs of kind
// 0x30, agents of kind 8), registers the trigger with each found, and starts in state 1 when its
// flag-table bit is set, otherwise 0.
void ResolveStateTriggerObjects(StateTrigger* self)
{
    s32 kept = 0;
    s32 i;
    for (i = 0; i < self->count1; i++) {
        void* node = FindFirstObjectById(self->world, 0x104, self->items1[i], self);
        if (node && IsObjectOfKind((BaseObject*)node, 0x22)) {
            SetCountedObjectCounter((CountedObject*)node, self);
            kept++;
        }
    }
    self->count1 = kept;
    for (i = 0; i < self->count2; i++) {
        void* node = FindFirstObjectById(self->world, 0x104, self->items2[i], self);
        if (node && IsObjectOfKind((BaseObject*)node, 0x30)) {
            s32 idx = self->outCount;
            self->outItems[idx] = (TimedObject*)node;
            self->outCount = idx + 1;
            ((TimedObject*)node)->desc30()->m4C((TimedObject*)node, self);
        }
    }
    for (i = 0; i < self->count3; i++) {
        void* node = FindFirstObjectById(self->world, 0x104, self->items3[i], self);
        if (node && IsObjectOfKind((BaseObject*)node, 8)) {
            AddAgentStateTrigger((Agent*)node, self);
        }
    }
    if (TestFlagTableBit((FlagTable*)g_flagTable, self->id6B0)) {
        SetStateTriggerState(self, 1);
    } else {
        SetStateTriggerState(self, 0);
    }
}

// Switches the trigger to state mode (0, 1 or 2) and records the game time. Leaving state 2 stops
// its sound and releases its walker targets. Each state sets the walker's target and outputs; state
// 1 fires script event 0x16 when the flag-table bit of its id was already set, else 3, then sets
// the bit.
void SetStateTriggerState(StateTrigger* self, s32 mode)
{
    s32 cur = self->state;
    if (cur == mode) {
        return;
    }
    if (cur < 0) {
        goto store;
    }
    if (cur < 2) {
        goto store;
    }
    if (cur != 2) {
        goto store;
    }
    StopSoundRecord((PlayingSound*)self->sound, 0);
    ReleaseSoundLevel((SoundLevelEntry*)self->soundLevel);
    SetGatheredWalkerTargets(self->world, self->count62C, (ZoneTargetEntry*)self->table630, self, 0);
    if (mode == 1) {
        ReleaseCounterRef((RefCounted*)D_002623D8);
    }
store:
    self->state = mode;
    self->stateTime = g_gameTime[0];
    if (mode == 1) {
        goto arm1;
    }
    if (mode < 2) {
        if (mode == 0) {
            goto arm0;
        }
        return;
    }
    if (mode == 2) {
        goto arm2;
    }
    return;
arm0:
    if (self->walker != 0) {
        SetStateWalkerTarget(self->walker, 0x21A);
    }
    ResetStateTriggerOutputModes(self);
    return;
arm1:
    if (self->walker != 0) {
        TeleportStateWalker(self->walker, 0x220);
    }
    EndStateTriggerOutputs(self);
    if (TestFlagTableBit((FlagTable*)g_flagTable, self->id6B0) != 0) {
        TriggerScriptEvent(self, 0x16, 0, 0);
    } else {
        TriggerScriptEvent(self, 3, 0, 0);
    }
    SetFlagTableBit((FlagTable*)g_flagTable, self->id6B0);
    return;
arm2:
    if (self->walker != 0) {
        SetStateWalkerTarget(self->walker, 0x21F);
    }
    if (self->f628 == 0) {
        StartSoundEffect(0x15, (PlayingSound**)&self->sound, self, 0, 8000.0f, 5000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
    self->soundLevel = PushSoundLevel(0x6B);
    FinishStateTriggerOutputs(self);
    SetGatheredWalkerTargets(self->world, self->count62C, (ZoneTargetEntry*)self->table630, self, 1);
    TriggerScriptEvent(self, 2, 0, 0);
    IncrementCounter((Counter*)D_002623D8);
}

// Maps a message's mode (0, 1, 2) to the trigger state 2, 0 or 1 and sets it; other modes do
// nothing.
void SetStateTriggerStateFromMessage(StateTrigger* object, s32 mode)
{
    s32 mapped;
    switch (mode) {
    case 0: mapped = 2; break;
    case 1: mapped = 0; break;
    case 2: mapped = 1; break;
    default: return;
    }
    SetStateTriggerState(object, mapped);
}

void CountStateTriggerDone(StateTrigger* counter)
{
	counter->done++;
}

// For each output item with no initial state (-1) that has method 0x49, calls it with 0.
void ResetStateTriggerOutputModes(StateTrigger* self)
{
    for (s32 i = 0; i < self->outCount; i++) {
        TimedObject* e = self->outItems[i];
        if (e->initialState == -1 && e->desc30()->m49 != 0) {
            e->desc30()->m49(e, 0);
        }
    }
}

// Calls method 0x4A (when it has one) of each of the trigger's output items.
void EndStateTriggerOutputs(StateTrigger* self)
{
    s32 i;
    for (i = 0; i < self->outCount; i++) {
        TimedObject* c = self->outItems[i];
        void (*fn)(TimedObject*) = c->desc30()->m4A;
        if (fn != 0) {
            fn(c);
        }
    }
}

// Calls method 0x4B (when it has one) of each of the trigger's output items.
void FinishStateTriggerOutputs(StateTrigger* self)
{
    s32 i;
    for (i = 0; i < self->outCount; i++) {
        TimedObject* it = self->outItems[i];
        void (*fn)(TimedObject*) = it->desc30()->m4B;
        if (fn != 0) {
            fn(it);
        }
    }
}

// Appends an id to the trigger's first id list (4 at most).
void AddStateTriggerCountedId(StateTrigger* self, s32 value)
{
    u32 n = self->count1;
    if (n < 4) {
        self->items1[n] = value;
        self->count1 = n + 1;
    }
}

// Appends an id to the trigger's second id list (16 at most).
void AddStateTriggerItemId(StateTrigger* self, s32 value)
{
    u32 n = self->count2;
    if (n < 16) {
        self->items2[n] = value;
        self->count2 = n + 1;
    }
}

// Appends an id to the trigger's third id list (6 at most).
void AddStateTriggerAgentId(StateTrigger* self, s32 value)
{
    u32 n = self->count3;
    if (n < 6) {
        self->items3[n] = value;
        self->count3 = n + 1;
    }
}

// Adds or updates an entry (key a1 and values a2 to a4) in the trigger's table of up to 8 entries.
void AddStateTriggerTableEntry(StateTrigger* object, s32 a1, s32 a2, s32 a3, s32 a4)
{
	UpsertKeyedEntry((ZoneTargetEntry*)object->table630, 8, &object->count62C,
			  a1, a2, a3, a4);
}

// Appends each output item to the script list being built; false as soon as one is refused.
s32 TestStateTriggerItemsAccepted(StateTrigger* self, void* arg)
{
    s32 i;
    for (i = 0; i < self->outCount; i++) {
        if (AppendPropertyToScriptList((ScriptListBuilder*)arg, &self->outItems[i]) == 0) {
            return 0;
        }
    }
    return 1;
}

ASM_FUNC(func_00123DC0);

ASM_FUNC(func_00123E00);

ASM_FUNC(func_00123E48);

ASM_FUNC(func_00123E88);

// Constructor body of the placed object: sets the link offsets of its lists, the cull modes (a root
// object starts with mode 2, a child with 1 and 0), the "unset" fade distances (3.4e38), the full
// visibility mask, and its default tables.
void InitPlacedObject(PlacedObject* self)
{
    SetListLinkOffset(&self->children, 0x1C);
    SetListLinkOffset(&self->list60, 0x58);
    if (self->parent != 0) {
        self->bits24 = 1;
        self->bits26 = 0;
    } else {
        self->bits24 = 2;
        self->bits26 = 2;
    }
    InitObject(self);
    self->fadeDistanceFar = 3.4028235e+38f;
    self->visibilityMask = 0x0FFFFFFF;
    self->fadeDistanceNear = 3.4028235e+38f;
    SetupStores::SetB2CA(self, -1);
    self->b2C9 = -1;
    self->p20C = (u8*)g_defaultPositionSpring;
    self->p210 = (u8*)g_defaultVelocitySpring;
    self->p214 = (u8*)g_defaultRotationSpring;
    self->p218 = (u8*)g_defaultSpinSpring;
    self->p21C = (u8*)g_defaultPositionRamp;
    self->p220 = (u8*)g_defaultRotationRamp;
    self->b2C8 = 0;
    SetupStores::Copy(&self->rot, &g_identityMatrix);
    SetupStores::Copy(&self->m110, &g_identityMatrix);
    SetupStores::Copy(&self->m1A0, &g_identityMatrix);
    SetListLinkOffset(&self->list1E0, 8);
}

// Attach method: runs the object's own attach (method 6), attaches each child (method 4) and sends
// notification 1.
void AttachPlacedObject(PlacedObject* self)
{
    ListFrame it;
    ListWalkBegin::Of(&it, &self->children);
    self->desc->m06(self);
    BaseObject* obj;
    while ((obj = ListWalkNextBase::Of(&it)) != 0) {
        obj->desc->m04(obj);
    }
    self->desc->m0E(self, 1, self);
    g_activeListFrames = (ListFrame*)it.prev;
}

// Registers the object with its world: root objects go in the world's lists (a different list for
// objects with a frame-step clock), a child takes its parent's root. It then seeds the pose from
// the attachments, adds the camera if flagged, adds the range record and fires script event 4.
void RegisterPlacedObject(PlacedObject* self)
{
    Vec4 v0;
    Vec4 v1;
    Mat3 rot;
    RegisterObject(self);
    World* ctx = self->world;
    if (!self->parent) {
        self->root = self;
        if (self->frameStepClock) {
            AppendToList(&ctx->list78, self);
        } else {
            AppendToList(&ctx->list54, self);
            self->flags |= 0x2000000000ULL;
            AppendToList((ObjectList*)&ctx->list60, self);
            if (self->desc->flags & 2) AppendToList((ObjectList*)&ctx->list6C, self);
            s32 n = self->count6C;
            self->linkListOwner = self;
            self->list60.tail = self;
            n--;
            self->list60.head = self;
            for (; n >= 0; n--) MergeObjectGroupMembers(ctx, self->items70[n]);
        }
    } else {
        self->root = ((PlacedObject*)self->parent)->root;
        if (((PlacedObject*)self->parent)->flags & 0x4000000000ULL) {
            if (self->desc->m14) self->desc->m14(self, 1);
        }
    }
    if (self->positionAttachment) {
        self->positionAttachment->vt->getPos(self->positionAttachment, 0.0f, &v0, &v1);
        self->desc02()->m1D(self, &v0);
        self->desc02()->m20(self, &v1);
    }
    if (self->orientationAttachment) {
        self->orientationAttachment->vt->getRot(self->orientationAttachment, 0.0f, &rot, &v0);
        self->desc02()->m1E(self, &rot);
        self->desc02()->m21(self, &v0);
    }
    if (self->flags & 0x1000000000ULL) AddCameraObject((Camera*)g_camera, self);
    if (self->rangeRecord) AppendToList(&self->world->list1C00, self->rangeRecord);
    if (self->desc->m12) self->desc->m12(self);
    TriggerScriptEvent(self, 4, 0, 0);
    ClearRootTries(self);
}

// Detach method: the object's own detach (method 7), each child's (method 5) and notification 2.
void DetachPlacedObject(PlacedObject* self)
{
    ListFrame it;
    ListWalkBegin::Of(&it, &self->children);
    self->desc->m07(self);
    BaseObject* obj;
    while ((obj = ListWalkNextBase::Of(&it)) != 0) {
        obj->desc->m05(obj);
    }
    self->desc->m0E(self, 2, self);
    g_activeListFrames = (ListFrame*)it.prev;
}

// Undoes RegisterPlacedObject: takes the object out of the world's lists (a root only), dissolves
// its group link list and clears its own lists, then unregisters it as an object.
void UnregisterPlacedObject(PlacedObject* self)
{
    UnregisterObject(self);
    World* s1 = self->world;
    if (self->parent == 0) {
        if (self->frameStepClock != 0) {
            RemoveFromList((ObjectList*)&s1->list78, self);
        } else {
            RemoveFromList((ObjectList*)&s1->list54, self);
            u64 fl = self->flags;
            if ((fl & (1ull << 37)) != 0) {
                self->flags = fl & ~(1ull << 37);
                RemoveFromList((ObjectList*)&s1->list60, self);
                if ((self->desc->flags & 2) != 0) {
                    RemoveFromList((ObjectList*)&s1->list6C, self);
                }
            }
            DissolveObjectLinkList(s1, (PlacedObject*)self->linkListOwner);
            self->linkListOwner = 0;
            ClearList(&self->list60);
        }
    }
    if ((self->flags & (1ull << 36)) != 0) {
        RemoveCameraObject(g_camera, self);
    }
    if (self->rangeRecord != 0) {
        RemoveFromList((ObjectList*)&self->world->list1C00, self->rangeRecord);
    }
    if ((self->flags & (1ull << 38)) != 0) {
        void (*fn)(BaseObject* self, s32 on) = self->desc->m14;
        if (fn != 0) {
            fn(self, 0);
        }
    }
    ClearRootTries(self);
    self->root = 0;
    TriggerScriptEvent(self, 5, 0, 0);
}

// Saves the object's current position, rotation matrix and the Euler angles of the rotation as its
// initial frame (0x190, 0x1A0, 0x1D0).
void SavePlacedObjectInitialFrame(PlacedObject* object)
{
	object->v190 = object->pos;
	object->m1A0.r[0] = object->rot.r[0];
	object->m1A0.r[1] = object->rot.r[1];
	object->m1A0.r[2] = object->rot.r[2];
	object->desc02()->m2A(object, &object->m1A0);
	MatrixToEulerAngles((Mat4*)&object->m1A0, (Vec3*)&object->v1D0);
}

// Moves the object under a new parent (or none) while keeping its world position, orientation,
// velocity and spin: they are converted into the new parent's frame and given to the object's
// setters. Switching between root and non-root also changes its draw-culling modes.
void ReparentPlacedObject(PlacedObject* self, BaseObject* parent)
{
    Vec4 pos;
    Vec4 vel;
    Vec4 spin;
    Mat3 rot;
    Vec4 velDir;
    Vec4 spinDir;
    Vec4 velDiff;
    Vec4 spinDiff;
    Vec4* pv;
    Vec4* ps;
    if (self->parent == parent) {
        return;
    }
    pos = self->v140;
    rot.r[0] = self->m110.r[0];
    rot.r[1] = self->m110.r[1];
    rot.r[2] = self->m110.r[2];
    if (self->parent != 0) {
        ComputeObjectMotionInFrame(self, 0, &self->v140, &vel, &spin, 0, 0);
        pv = &vel;
        ps = &spin;
    } else {
        vel = self->v150;
        spin = self->v160;
        pv = &vel;
        ps = &spin;
    }
    self->desc->m03(self);
    TransformPointBetweenFrames(0, (PlacedObject*)parent, &pos, &self->pos);
    TransformRotationBetweenFrames(0, (PlacedObject*)parent, &rot, &self->rot);
    if (parent != 0) {
        ComputeObjectMotionInFrame((PlacedObject*)parent, 0, &self->v140, &velDiff, &spinDiff, 0, 0);
        Vu0::Q(vel) = Vu0::Sub(Vu0::Q(vel), Vu0::Q(velDiff));
        Vu0::Q(spin) = Vu0::Sub(Vu0::Q(spin), Vu0::Q(spinDiff));
    }
    TransformDirectionBetweenFrames(0, (PlacedObject*)parent, pv, &velDir);
    self->desc02()->m20(self, &velDir);
    TransformDirectionBetweenFrames(0, (PlacedObject*)parent, ps, &spinDir);
    self->desc02()->m21(self, &spinDir);
    if ((parent == 0) != (self->parent == 0)) {
        if (parent == 0) {
            self->bits24 = 2;
            if (self->bits26 != 1) {
                self->bits26 = 2;
            }
            if (self->bits28 != 1) {
                self->bits28 = 2;
            }
        } else {
            self->bits24 = 1;
            if (self->bits26 != 1) {
                self->bits26 = 0;
            }
            if (self->bits28 != 1) {
                if (self->bits28 != 2 || self->fadeDistanceFar == 1.0e10f) {
                    self->bits28 = 0;
                }
            }
        }
    }
    SavePlacedObjectInitialFrame(self);
    self->parent = parent;
    self->desc->m02(self);
}

// Makes the object a child of frame without moving it in the world: its position, rotation,
// velocity and spin are expressed in the frame's coordinates, adding the frame parent's motion, and
// are given to its setters; it ends by saving its pose into the previous-pose copy.
void ReframePlacedObject(PlacedObject* self, BaseObject* frame)
{
    Vec4 pos;
    Mat3 rot;
    Vec4 vel;
    Vec4 spin;
    Vec4 velDir;
    Vec4 spinDir;
    Vec4 sums[2];
    TransformPointBetweenFrames((PlacedObject*)frame, 0, &self->pos, &pos);
    self->desc02()->m1D(self, &pos);
    TransformRotationBetweenFrames((PlacedObject*)frame, 0, &self->rot, &rot);
    self->desc02()->m1E(self, &rot);
    ComputeObjectMotionInFrame((PlacedObject*)frame->parent, 0, &pos, &vel, &spin, 0, 0);
    TransformDirectionBetweenFrames((PlacedObject*)frame, 0, &self->v150, &velDir);
    TransformDirectionBetweenFrames((PlacedObject*)frame, 0, &self->v160, &spinDir);
    Vu0::Set(sums[0], Vu0::Add(Vu0::Q(vel), Vu0::Q(velDir)));
    Vu0::Set(sums[1], Vu0::Add(Vu0::Q(spin), Vu0::Q(spinDir)));
    self->desc02()->m20(self, &sums[0]);
    self->desc02()->m21(self, &sums[1]);
    self->v190 = self->pos;
    self->m1A0.r[0] = self->rot.r[0];
    self->m1A0.r[1] = self->rot.r[1];
    self->m1A0.r[2] = self->rot.r[2];
}

// After loading: resolves the follow record, saves the initial frame, finds the aim target by its
// id (if set), binds the attachment targets and runs each child's post-load method (0xF).
void PostLoadPlacedObject(PlacedObject* self)
{
    ListFrame frame;
    ResolveFollowRecordObjects(self);
    SavePlacedObjectInitialFrame(self);
    AimAttachment* sub = self->aimAttachment;
    if (sub != 0 && sub->targetId != -1) {
        void* v = FindFirstObjectByIdMode4(self->world, sub->targetId, self);
        if (v != 0) {
            SetAimTarget(self, v);
        }
    }
    BindAttachmentTargets((AttachmentTargets*)self->sub22C, self);
    for (BaseObject* p = (BaseObject*)self->children.head; p != 0; p = p->next) {
        void (*fn)(BaseObject* self) = p->desc->m0F;
        if (fn != 0) {
            fn(p);
        }
    }
}

// Start-up of the object once its world is loaded: starts the base object and its attachments,
// queues the animation start, sets up the range record, starts its sound effect, allocates the
// indexed attachment slots, and resolves the keyed objects it must start or attach.
void StartPlacedObject(PlacedObject* self)
{
    WordListFrame fr;
    StartKeyNode* k;
    BaseObject* s0;
    sptr old = (sptr)g_activeListFrames;
    sptr e = (sptr)&self->children;
    fr.list = e;
    fr.link = e;
    fr.offset = ((ObjectList*)e)->offset;
    fr.prev = old;
    g_activeListFrames = (ListFrame*)&fr;
    StartObject(self);
    if (self->animationStart != 0) {
        if (self->animationStart->anim != 0 || self->animationStart->key != -1) {
            AppendQueuedCall(self->world, (void*)StartAnimationFromContext, self, 0, 0);
        }
    }
    StartAttachments((AttachmentBlock*)self->sub22C, self);
    if (self->rangeRecord != 0) {
        if (HasRangeRecordRanges(self->rangeRecord) == 0) {
            StoreRangeRecordNear(self->rangeRecord, self->boundRadius);
            StoreRangeRecordFar(self->rangeRecord, self->boundRadius * 0.5f);
        }
        if ((self->rangeRecord)->textureObjectId != -1) {
            (self->rangeRecord)->textureObject = FindFirstObjectByIdMode4(self->world, (self->rangeRecord)->textureObjectId, self);
            if ((self->rangeRecord)->textureObject != 0) {
                BuildTexturePackets((TextureRenderObject*)((self->rangeRecord)->textureObject), self->rangeRecord);
            }
        }
        PrepareRangeRecord(self->rangeRecord);
    }
    if (self->soundRecord != 0) {
        if (self->soundRecord->soundId == -1) {
            self->soundRecord = 0;
        }
        if (self->soundRecord != 0) {
            SoundRecord* q = self->soundRecord;
            StartSoundEffect(q->soundId, (PlayingSound**)&q->soundWord, self, 0, q->outerRange, q->innerRange, q->baseVolume, q->pitch, q->startParam, (f32*)&q->b14, 0);
        }
    }
    if (self->valueCount != 0) {
        self->indexedAttachments = (void**)AllocateZeroedFrontMemory(self->valueCount << 2);
    }
    for (k = self->keys; k != 0; k = k->next) {
        if (MatchesObjectId(self, k->key) != 0) {
            s0 = self;
        } else {
            s0 = (BaseObject*)FindFirstObjectById(self->world, 1, k->key, self);
            if (s0 == 0) {
                continue;
            }
        }
        if (IsObjectAttached(s0) != 0 && s0 != self) {
            s0->desc->m10(s0);
        }
        s0->desc->m03(s0);
    }
    self->keys = 0;
    {
        sptr head = *(sptr*)fr.link;
        sptr p;
        fr.link = head + fr.offset;
        p = head;
        while (p != 0) {
            ((BaseObject*)p)->desc->m10((BaseObject*)p);
            sptr nx = *(sptr*)fr.link;
            fr.link = nx + fr.offset;
            p = nx;
        }
    }
    g_activeListFrames = (ListFrame*)fr.prev;
}

// Starts the animation named by the object's start record: the start time is a value in seconds
// (mode 0), a 0..1 fraction of the length (mode 1) or the nearest point on the animation's path to
// the object (mode 2). Queued by StartPlacedObject.
void StartAnimationFromContext(PlacedObject* self)
{
    AnimationStart* ctx = self->animationStart;
    Animation* node = FindStartAnimation::Of(self, ctx);
    if (node == 0) {
        return;
    }
    StartBindingFrame fr;
    switch (ctx->mode) {
    case 0:
        fr.tmp = ctx->value;
        break;
    case 1:
        fr.tmp = ClampRange::Of(ctx->value, 0.0f, 1.0f) * node->length;
        break;
    case 2:
        FindNearestAnimationPathTime(node, self, 0.0f, &self->pos, &fr.tmp, 0, 0);
        break;
    default:
        return;
    }
    fr.key = node->id;
    fr.object = self;
    CreateAnimationPlayer(node, self, 1, &fr, 0, 0, fr.tmp, ctx->speedScale);
}

// Resolves a table of links on self: each finds an object by id in the world (the flags choose the
// lookup kind and whether a pointer is stored at the link's offset, the object is started, or self
// is added as its listener).
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item)
{
    World* host = self->world;
    if (count <= 0) {
        return;
    }
    ObjectLink* it = item;
    s32 n = count;
    do {
        u32 f = it->flags;
        s32 kind = (f & 1) ? 5 : 1;
        if (f & 0x20) {
            kind |= 0x100;
        }
        void* node = FindFirstObjectById(host, kind, it->id, self);
        if (node) {
            if (!(it->flags & 8)) {
                // address arithmetic over a variable index
                *(void**)((u8*)self + it->offset) = node;
            }
            if (!(it->flags & 4)) {
                ResolveAndStartObject((BaseObject*)node);
            }
            if (it->flags & 0x10) {
                AddObjectListener((BaseObject*)node, self);
            }
        }
        n--;
        it++;
    } while (n != 0);
}

// Per-frame update of an object and its children: runs the object's pre-update method (slot 0x11)
// with the frame time and, if the object is still attached, updates each child whose descriptor has
// flag 1 (a placed-object kind) the same way.
void UpdateObjectTree(void* self, f32 f)
{
    PlacedObject* obj = (PlacedObject*)self;
    WordListFrame fr;
    f32 saved = f;
    void (*pre)(BaseObject* self, f32 dt) = obj->desc->m11;
    if (pre != 0) {
        pre(obj, f);
    }
    if (IsObjectAttached((BaseObject*)self) == 0) {
        return;
    }
    sptr e = (sptr)&obj->children;
    fr.list = e;
    fr.link = e;
    sptr old = *(sptr*)&g_activeListFrames;
    s32 link = ((ObjectList*)e)->offset;
    fr.prev = old;
    fr.offset = link;
    *(sptr*)&g_activeListFrames = (sptr)&fr;
    sptr head = (sptr)obj->children.head;
    fr.link = head + fr.offset;
    BaseObject* node = (BaseObject*)head;
    while (node != 0) {
        if ((node->desc->flags & 1) != 0) {
            UpdateObjectTree(node, saved);
        }
        sptr nx = *(sptr*)fr.link;
        fr.link = nx + fr.offset;
        node = (BaseObject*)nx;
    }
    *(sptr*)&g_activeListFrames = fr.prev;
}

// Per-frame update of the object: updates its attachments and range record, pulses its colour,
// calls each attachment's update, and sends script event 1 with the frame time.
void UpdatePlacedObject(PlacedObject* self, f32 f)
{
    UpdateAttachments((AnimatorOwner*)self->sub22C, self, f);
    if (self->rangeRecord != 0) {
        UpdateRangeRecord(self->rangeRecord, f);
    }
    if (self->colorRecord != 0) {
        ApplyPulsingColorToObjectTree(self, f);
    }
    ListFrame it;
    ListWalkBegin::Of(&it, &self->list1E0);
    Attachment* obj;
    while ((obj = NextAttachment::Of(&it)) != 0) {
        if (obj->vt->update != 0) {
            obj->vt->update(obj, f);
        }
    }
    g_activeListFrames = (ListFrame*)it.prev;
    void* args[1];
    args[0] = &f;
    TriggerScriptEvent(self, 1, 1, args);
}

// Sets the value of each of the object's draw part states (0x28 bytes each) to -1.
void ClearObjectRecordValues(PlacedObject* records)
{
    for (s32 i = 0; i < records->drawPartCount; i++) {
        // address arithmetic over a variable index
        PartState* record = (PartState*)((u8*)records->partStates + i * 0x28);
        record->value = -1;
    }
}

// Calls the object's method 0x13 when it has one.
void RecomputePlacedObjectFrame(PlacedObject* self)
{
    void (*fn)(BaseObject* self) = self->desc->m13;
    if (fn != 0) {
        fn(self);
    }
}

struct ValueListObject;

// The product a b into the object's world matrix (m110), written through the object: b's rows
// read by index (MulRotationRowsIndexed), each result row stored to its vector local and to the
// matrix local. The helper's frame is 16 bytes bigger than the other products': g++ saves an
// inline function as RTL before optimising it and gives each call one stack temporary of that
// saved frame's size (integrate.c), so a vector local declared after the matrix and never used
// still takes its 16 bytes above r in each call's frame (retail's 160-byte frame, its unused
// 0x60..0x70). Here it is the fourth row, w, which a rotation product leaves unset.
static inline void MulRotationIntoWorld(PlacedObject* o, const Mat3& a, const Mat3& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    const u128* q = (const u128*)&b;
    Vec4 x;
    Vec4 y;
    Vec4 z;
    Mat3 r;
    Vec4 w;    // the fourth row: never set (see above)
    Vu0::Q(x) = Vu0::RotateRows(a0, a1, a2, q[0]);
    r.r[0] = x;
    Vu0::Q(y) = Vu0::RotateRows(a0, a1, a2, q[1]);
    r.r[1] = y;
    Vu0::Q(z) = Vu0::Q(r.r[2]) = Vu0::RotateRows(a0, a1, a2, q[2]);
    o->m110 = r;
}

// Recomputes the world position (v140) and rotation (m110) from the local pose and the parent, or
// from the link record's frames when its flags 0xC are set. It also refreshes the visibility mask,
// the range record's position and direction, and calls each child's own update.
void ComputePlacedObjectWorldFrame(PlacedObject* self)
{
    Rec2195_224* rec = self->linkRecord;
    PlacedObject* par;
    if (rec != 0 && (rec->flags & 0xC) != 0) {
        par = (rec->flags & 4) ? (PlacedObject*)rec->p60 : (PlacedObject*)self->parent;
        if (par != 0) {
            Vu0::Q(self->v140) = Vu0::Add(Vu0::Rotate(par->m110, Vu0::Q(self->pos)), Vu0::Q(par->v140));
        } else {
            self->v140 = self->pos;
        }
        rec = self->linkRecord;
        par = (rec->flags & 8) ? (PlacedObject*)rec->p60 : (PlacedObject*)self->parent;
        if (par != 0) {
            MulRotationIntoWorld(self, par->m110, self->rot);
        } else {
            self->m110 = self->rot;
        }
    } else {
        PlacedObject* parent = (PlacedObject*)self->parent;
        if (parent != 0) {
            Vu0::Q(self->v140) = Vu0::Add(Vu0::Rotate(parent->m110, Vu0::Q(self->pos)), Vu0::Q(parent->v140));
            MulRotationIntoWorld(self, parent->m110, self->rot);
        } else {
            self->v140 = self->pos;
            self->m110 = self->rot;
        }
    }
    u32 kind = self->bits24;
    if (kind == 2) {
        if (self->world->valueListObject != 0) {
            QueryValueListMask((ValueListObject*)self->world->valueListObject, self->boundRadius, (u128*)&self->v140, &self->visibilityMask);
        } else {
            self->visibilityMask = 0x0FFFFFFF;
        }
    }
    if (self->rangeRecord != 0) {
        SetRangeRecordPosition(self->rangeRecord, &self->v140);
        if (self->rangeRecord->link != 0 && *(u8*)self->rangeRecord->link == 3) {
            Vec4 dir;
            Vu0::Q(dir) = Vu0::MulX(Vu0::Q(self->m110.r[2]), Vu0::Scalar(-1.0f));
            SetRangeRecordDirection(self->rangeRecord, &dir);
            StoreRangeRecordVector(self->rangeRecord, (Quad16*)&self->m110.r[1]);
        }
    }
    for (BaseObject* n = (BaseObject*)self->children.head; n != 0; n = n->next) {
        if (n->desc->m13 != 0) {
            n->desc->m13(n);
        }
    }
    Rec2195_224* last = self->linkRecord;
    if (last != 0 && (last->flags & 0x8020) == 0x8020) {
        ((PlacedObject*)last->linkParent)->linkRecord->p64 = (BaseObject*)1;
        ((PlacedObject*)last->p84)->linkRecord->p64 = (BaseObject*)1;
    }
}

// Empty: the move method has nothing to do for a plain placed object.
void BeginPlacedObjectMove(PlacedObject* self)
{
    (void)self;
}

void ApplyPoseSourcePosition(TrackFollowAttachment* self);
void ApplyPoseSourceRotation(Attachment* a);
s32 IsAccelerationNegligible(void* a);
s32 IsSpinAccelerationNegligible(void* a);
void OrthonormalizeMatrix(Mat3* m);

// Advances the object by one step: takes the position and rotation from its attachments, or
// integrates velocity, acceleration and spin over the frame time, then moves each child that wants
// it (desc flag 1). If anything moved and flag is 0, it calls the object's moved callback.
void MovePlacedObject(PlacedObject* self, s32 flag, f32 dt)
{
    Attachment* pa = self->positionAttachment;
    Attachment* ra = self->orientationAttachment;
    s32 moved = flag;
    if (pa == 0 || pa->mode0 == 5 || ra == 0 || ra->mode1 == 5) {
        Vu0::Q(self->v180) = Vu0::Q(self->v170) = Vu0::Zero();
        ((void (*)(PlacedObject*, f32))self->desc02()->m1C)(self, g_frameDt);
    }
    if (pa != 0 && pa->mode0 != 5) {
        ApplyPoseSourcePosition((TrackFollowAttachment*)pa);
        moved = 1;
    } else if (IsVelocityNegligible(&self->v150) == 0 || IsAccelerationNegligible(&self->v170) == 0) {
        moved = 1;
        GameClock* clk = &g_gameClock;
        Vu0::Q(self->pos) = Vu0::MulAddX2(Vu0::Q(self->pos), Vu0::Q(self->v150), Vu0::Scalar(clk->dt), Vu0::Q(self->v170), Vu0::Scalar(clk->dt * (clk->dt * 0.5f)));
        Vu0::Q(self->v150) = Vu0::MulAddX(Vu0::Q(self->v150), Vu0::Q(self->v170), Vu0::ScalarAt(clk->dt));
    }
    if (ra != 0 && ra->mode1 != 5) {
        ApplyPoseSourceRotation(ra);
        moved = 1;
    } else if (IsSpinNegligible(&self->v160) == 0 || IsSpinAccelerationNegligible(&self->v180) == 0) {
        GameClock* clk = &g_gameClock;
        Vec4 prev;
        Vec4 w;
        Mat3 rot;
        Vu0::Q(prev) = Vu0::Q(self->v160);
        Vu0::Q(self->v160) = Vu0::MulAddX(Vu0::Q(self->v160), Vu0::Q(self->v180), Vu0::ScalarAt(clk->dt));
        moved = 1;
        Vu0::Q(w) = Vu0::MulXSum(Vu0::Q(prev), Vu0::Scalar(clk->dt * 0.5f), Vu0::Q(self->v160), Vu0::Scalar(clk->dt * 0.5f));
        BuildRotationFromVector(&w, (Mat3*)&rot);
        MulRotationIntoRot(self, rot, self->rot);
        OrthonormalizeMatrix(&self->rot);
    }
    ListFrame it;
    ListWalkBegin::Of(&it, &self->children);
    BaseObject* obj;
    while ((obj = ListWalkNextBase::Of(&it)) != 0) {
        if ((obj->desc->flags & 1) != 0) {
            obj->desc->step(obj, dt, moved);
        }
    }
    if (moved != 0) {
        if (flag == 0) {
            if (self->desc->m12 != 0) {
                self->desc->m12(self);
            }
        }
    }
    g_activeListFrames = (ListFrame*)it.prev;
}

typedef void (*PositionAtFn)(PlacedObject* self, f32 t, Vec4* pos, Vec4* vel);
typedef void (*RotationAtFn)(PlacedObject* self, f32 t, Mat3* rot, Vec4* spin);

// Like AccumulateFrameChain, but each object's position and rotation come from its own methods
// evaluated at time t. Gives the combined position, rotation, velocity and spin of self relative to
// top (any output may be null).
void ComputeObjectFrameAtTime(PlacedObject* self, PlacedObject* top, Vec4* pos, Mat3* rot, Vec4* vel, Vec4* spin, f32 t)
{
    PlacedObject* chain[16];
    Vec4 P;
    Vec4 V;
    Vec4 W;
    Mat3 M;
    Mat3 R;
    Vec4 p;
    Vec4 v;
    Vec4 w;
    s32 n = 0;
    while (self != top) {
        chain[n] = self;
        n++;
        Rec2195_224* rec = self->linkRecord;
        if (rec != 0 && (rec->flags & 0xC)) {
            self = (PlacedObject*)rec->p60;
        } else {
            self = (PlacedObject*)self->parent;
        }
    }
    M = g_identityMatrix;
    P = g_zeroVector;
    V = g_zeroVector;
    W = g_zeroVector;
    for (n--; n >= 0; n--) {
        PlacedObject* o = self = chain[n];
        if (pos != 0 || vel != 0) {
            ((PositionAtFn)o->desc02()->m22)(o, t, &p, &v);
            Vu0::Q(p) = Vu0::RotateUntied(M, Vu0::Q(p));
            Vu0::Q(P) = Vu0::Add(Vu0::Q(P), Vu0::Q(p));
            if (vel != 0) {
                Vu0::Q(V) = Vu0::Add(Vu0::Add(Vu0::Q(V), Vu0::Rotate(M, Vu0::Q(v))), Vu0::Cross(Vu0::Q(W), Vu0::Q(p)));
            }
        }
        ((RotationAtFn)o->desc02()->m23)(o, t, &R, &w);
        if (spin != 0 || vel != 0) {
            Vu0::Q(W) = Vu0::Add(Vu0::Q(W), Vu0::Rotate(M, Vu0::Q(w)));
        }
        MulRotation(&M, M, R);
    }
    if (pos != 0) {
        *pos = P;
    }
    if (rot != 0) {
        *rot = M;
    }
    if (vel != 0) {
        *vel = V;
    }
    if (spin != 0) {
        *spin = W;
    }
}

// Converts a position, rotation, velocity and spin from self's frame to top's frame as they are at
// time t, using ComputeObjectFrameAtTime (any argument may be null).
void TransformPointAtTime(PlacedObject* self, PlacedObject* top, Vec4* pos, Mat3* rot, Vec4* vel, Vec4* spin, f32 t)
{
    Mat3 m;
    Vec4 p;
    Vec4 v;
    Vec4 w;
    Vec4 r;
    ComputeObjectFrameAtTime(self, top, (pos != 0 || vel != 0) ? &p : 0, &m, vel != 0 ? &v : 0,
                             (spin != 0 || vel != 0) ? &w : 0, t);
    if (pos != 0 || vel != 0) {
        if (pos != 0) {
            Vu0::Q(r) = Vu0::Rotate(m, Vu0::Q(*pos));
            Vu0::Q(*pos) = Vu0::Add(Vu0::Q(p), Vu0::Q(r));
        } else {
            r = g_zeroVector;
        }
    }
    if (vel != 0) {
        Vu0::Q(*vel) = Vu0::Add(Vu0::Add(Vu0::Q(v), Vu0::Rotate(m, Vu0::Q(*vel))), Vu0::Cross(Vu0::Q(w), Vu0::Q(r)));
    }
    if (spin != 0) {
        Vu0::Q(*spin) = Vu0::Add(Vu0::Q(w), Vu0::Rotate(m, Vu0::Q(*spin)));
    }
    if (rot != 0) {
        MulRotation(rot, m, *rot);
    }
}

// Gives the transform to draw: the one passed in (copied unless it is dst itself) or the object's
// own position and rotation with fades of 1.
void BuildPlacedObjectTransform(PlacedObject* self, Quad16* src, ScaledTransform* dst)
{
    if (src != 0) {
        if (src != (Quad16*)dst) {
            *dst = *(ScaledTransform*)src;
        }
    } else {
        BuildScaledTransformMatrix((f32*)&self->v140, (float (*)[4])&self->m110, (f32*)g_unitScale, (float (*)[4])dst);
        dst->innerFade = 1.0f;
        dst->outerFade = 1.0f;
    }
}

// Builds the object's transform with its x/y and z scales and passes it to the world's hook object
// (slot 17) through its method 0x26, when there is one.
void SubmitScaledPlacedObjectTransform(PlacedObject* self, void* a, Quad16* src)
{
    Quad16 scale;
    ScaledTransform t;
    Vu0::Q(scale) = Vu0::FromFloats(self->xyScale, self->xyScale, self->zScale);
    BuildPlacedObjectTransform(self, src, &t);
    BuildScaledTransformMatrix((f32*)&t.q[3], (float (*)[4])&g_identityMatrix, (f32*)&scale, (float (*)[4])&t);
    PlacedObject* hook = (PlacedObject*)self->world->slot1CE8[17];
    if (hook != 0) {
        hook->desc02()->m26(hook, a, &t);
    }
}

// PlacedObject's slot 36 (0xA0), the base draw: the culling by the camera's planes and the
// distance fades (into the transform's two scales), the world node's level, the parent's
// unscaling, the attachment's matrix, slot 37, then each child drawn with its transform. The
// child's matrix is MultiplyMatrices by value, nested where the child is relative to its parent:
// the outer call's return slot is a temporary whose address the call and the copy into ct use,
// so loop.c moves it (retail's s7).
//
// The offset from the camera is in two variables, d and its copy q. Retail spills d (the vsub's
// output reload, 0x1C0, read again for the second fade call) and holds q in $vf6 for the plane
// test and the first fade call (`lqc2 $vf6,448(sp)`, `qmfc2 a1,$vf6`). cse keeps a copy only
// while it is its class's first register: q has to be named after d's last use, and its
// equivalence has to end between the two calls (docs/toolchain/cse.md, "A copy that must
// outlive its source"). The two assignments to q marked DEAD below do that and nothing else:
// each recomputes the offset from the rebuilt transform, as the statement that sets d does, and
// is never read, so flow deletes it. No live form was found (docs/toolchain/cse.md lists what
// was tried: an inline's by-value parameter, a reference to a temporary, a record, one variable
// recomputed), and the maintainer allowed these two dead stores for this function on
// 2026-11-12 (AGENTS.md).
s32 ComputeCameraDistanceFade(Camera* self, u128 d, f32* fade, f32 radius, f32 x);
Mat4A MultiplyMatrices(const Mat4A& a, const Mat4A& b);

// The parent's rotation, its scale divided out, times the transform's (MulRotationRowsX), with
// the fourth row w that MulRotationIntoWorld's frame shows: never set, it makes the saved frame
// 112 bytes, and the child walk's locals sit after it (docs/TOOLCHAIN.md, "Stack slots").
static inline void MulRotationRowsXW(Mat3* out, const Mat3& a, const Mat3& b)
{
    const u128* p = (const u128*)&a;
    u128 a0 = p[0];
    u128 a1 = p[1];
    u128 a2 = p[2];
    Vec4 x;
    Vec4 y;
    Vec4 z;
    Mat3 r;
    Vec4 w;    // the fourth row: never set
    Vu0::Q(x) = Vu0::Q(r.r[0]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[0]));
    Vu0::Q(y) = Vu0::Q(r.r[1]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[1]));
    Vu0::Q(z) = Vu0::Q(r.r[2]) = Vu0::RotateRows(a0, a1, a2, Vu0::Q(b.r[2]));
    *out = r;
}

// Decides whether the object is drawn this frame for the camera: gives up when it is hidden,
// outside its visibility mask or its sphere is outside the camera planes. Otherwise it works out
// the far and near distance fades, building a faded copy of the transform when the fade is not 1,
// and draws the object's parts with it.
void ApplyPlacedObjectTransform(PlacedObject* self, Camera* cam, ScaledTransform* xf)
{
    ScaledTransform t;
    if (self->flags & ((u64)0x8000 << 17)) {
        return;
    }
    if ((self->flags & 0xC000000) == 0x8000000) {
        if ((self->visibilityMask & cam->areaMask) != cam->areaMask) {
            return;
        }
    }
    if ((self->flags & 0x30000000) == 0x20000000) {
        Vec4 r;
        f32 fade;
        Vec4* p = &self->v140;
        if (xf != 0) {
            p = (Vec4*)&xf->q[3];
        }
        u128 d = Vu0::Sub(Vu0::Q(*p), Vu0::Q(*(Vec4*)cam->position));
        u128 ones = Vu0::Ones();
        Vu0::Q(r) = Vu0::FromFloat(self->boundRadius);
        u128 q = d;
        if ((Vu0::PlaneSigns(Vu0::Q(cam->planes[0]), Vu0::Q(cam->planes[1]), Vu0::Q(cam->planes[2]), q, ones, Vu0::Q(r)) ^ 0xF0) != 0) {
            return;
        }
        if (ComputeCameraDistanceFade(cam, q, &fade, self->boundRadius, self->fadeDistanceFar) == 0) {
            return;
        }
        if (fade != 1.0f) {
            BuildPlacedObjectTransform(self, (Quad16*)xf, &t);
            xf = &t;
            t.outerFade *= fade;
            // DEAD: ends q's equivalence with d before the second call (see above).
            q = Vu0::Sub(Vu0::Q(*(Vec4*)&xf->q[3]), Vu0::Q(*(Vec4*)cam->position));
        }
        if (self->fadeDistanceNear < self->fadeDistanceFar) {
            if (ComputeCameraDistanceFade(cam, d, &fade, self->boundRadius, self->fadeDistanceNear) == 0) {
                fade = 0.0f;
            }
            if (fade != 1.0f) {
                BuildPlacedObjectTransform(self, (Quad16*)xf, &t);
                xf = &t;
                t.innerFade *= fade;
                // DEAD: names q after d's last use (see above).
                q = Vu0::Sub(Vu0::Q(*(Vec4*)&xf->q[3]), Vu0::Q(*(Vec4*)cam->position));
            }
        }
    }
    if (self->rampNode != 0) {
        BuildPlacedObjectTransform(self, (Quad16*)xf, &t);
        xf = &t;
        t.outerFade *= self->rampNode->level;
    }
    if (xf != 0) {
        Rec2195_224* rec = self->linkRecord;
        if (rec != 0 && (rec->flags & 0x80) && rec->unscaleByParent != 0) {
            PlacedObject* parent = (PlacedObject*)self->parent;
            if (parent != 0) {
                Attachment* a = (Attachment*)parent->matrixAttachment;
                if (a != 0 && parent->linkRecord != 0 && (parent->linkRecord->flags & 0x80)) {
                    Mat3 m;
                    Mat3 rot;
                    a->vt->getMatrix(a, &m);
                    m.r[0].x = 1.0f / m.r[0].x;
                    m.r[1].y = 1.0f / m.r[1].y;
                    m.r[2].z = 1.0f / m.r[2].z;
                    BuildPlacedObjectTransform(self, (Quad16*)xf, &t);
                    MulRotationRowsXW(&rot, m, *(Mat3*)&t);
                    BuildMatrixFromRotationAndTranslation((const Vec4*)&t.q[3], (const Mat3*)&rot, (Mat4A*)&t);
                    xf = &t;
                }
            }
        }
    }
    Attachment* a = (Attachment*)self->matrixAttachment;
    if (a != 0) {
        Mat3 m;
        Mat4A m4;
        a->vt->getMatrix(a, &m);
        BuildMatrixFromRotationAndTranslation((const Vec4*)&g_zeroVector, (const Mat3*)&m, (Mat4A*)&m4);
        BuildPlacedObjectTransform(self, (Quad16*)xf, &t);
        *(Mat4A*)&t = MultiplyMatrices(*(Mat4A*)&t, m4);
        xf = &t;
    }
    self->desc02()->m25(self, cam, xf);
    PlacedObject* o = (PlacedObject*)self->children.head;
    if (xf == 0) {
        for (; o != 0; o = (PlacedObject*)o->next) {
            if (o->desc->flags & 1) {
                o->desc02()->m24(o, cam, 0);
            }
        }
    } else {
        for (; o != 0; o = (PlacedObject*)o->next) {
            if (o->desc->flags & 1) {
                ScaledTransform ct;
                Mat4A local;
                ScaledTransform inv;
                if (o->linkRecord != 0 && (o->linkRecord->flags & 0xC)) {
                    BuildMatrixFromRotationAndTranslation((const Vec4*)&o->v140, (const Mat3*)&o->m110, (Mat4A*)&local);
                    InvertRigidTransform(&self->v140, &self->m110, (Quad16*)&inv);
                    *(Mat4A*)&ct = MultiplyMatrices(MultiplyMatrices(*(Mat4A*)xf, *(Mat4A*)&inv), local);
                } else {
                    BuildMatrixFromRotationAndTranslation((const Vec4*)&o->pos, (const Mat3*)&o->rot, (Mat4A*)&local);
                    *(Mat4A*)&ct = MultiplyMatrices(*(Mat4A*)xf, local);
                }
                ct.outerFade = xf->outerFade;
                ct.innerFade = xf->innerFade;
                o->desc02()->m24(o, cam, &ct);
            }
        }
    }
    if (0.0f < self->xyScale) {
        SubmitScaledPlacedObjectTransform(self, cam, (Quad16*)xf);
    }
}

// Draw method: runs method 0x2C, notes the draw matrix in the link record when its flag 0x80 is set
// (and marks it unused when there is none), then calls the draw method 0x26 with the matrix.
void DrawPlacedObject(PlacedObject* self, void* b, void* m)
{
    Quad16* src = (Quad16*)m;
    self->desc02()->m2C(self);
    Rec2195_224* in = self->linkRecord;
    if (in != 0 && (in->flags & 0x80) != 0) {
        if (src != 0) {
            in->hasDrawQuads = 1;
            Rec2195_224* p = self->linkRecord;
            p->q60[0] = src[0];
            p->q60[1] = src[1];
            p->q60[2] = src[2];
            p->q60[3] = src[3];
        } else {
            in->hasDrawQuads = 0;
        }
    }
    self->desc02()->m26(self, b, src);
}

// A part of a placed object's model (drawParts, 0x70 bytes each): what func_00126270 reads of it.
// The 0x80-byte request func_00126270 queues for each part it draws (DrawModelPart).
struct __attribute__((aligned(16))) ModelPartRequest {
    void* fn;               // 0x00
    f32 dist;               // 0x04
    s32 kind;               // 0x08
    u8 pad0C[0x10 - 0x0C];
    ScaledTransform block;  // 0x10
    Vec4 pos;              // 0x60
    PlacedObject* obj;      // 0x70
    void* sub;              // 0x74
    ModelPart* part;        // 0x78
    ModelPartState* state;  // 0x7C
};

s32 ComputeCameraDistanceFade(Camera* self, u128 d, f32* fade, f32 radius, f32 x);
void ApplyPoseSourceIndexedValue(Attachment* self, s32 val);
void BuildCameraFacingMatrix(void* unused0, Camera* cam, void* unused2, f32* pos, Mat4A* m);

// Queues one draw request (DrawModelPart) for each visible model part of the object: builds the
// object's transform, skips parts hidden by the camera mask or outside the camera planes, and
// scales the block's fades by the per-part distance fade.
void QueuePlacedObjectModelParts(PlacedObject* self, Camera* cam, Quad16* src)
{
    ModelPartRequest rec;
    ModelPartState* state = 0;
    s32 drawn = 0;
    FillMemory(&rec, 0, 0x80);
    BuildPlacedObjectTransform(self, src, &rec.block);
    rec.fn = (void*)DrawModelPart;
    rec.obj = self;
    rec.sub = self->sub22C;
    f32 alpha = rec.block.outerFade;
    f32 glow = rec.block.innerFade;
    for (s32 i = 0; i < self->drawPartCount; i++) {
        ModelPart* part = &((ModelPart*)self->drawParts)[i];
        rec.part = part;
        if (self->partStates != 0) {
            state = rec.state = &((ModelPartState*)self->partStates)[i];
            if (self->bits26 == 1 && (state->mask & cam->areaMask) != (u32)cam->areaMask) {
                continue;
            }
        }
        if (self->flags & 0x200000000ULL) {
            rec.pos = part->pos;
        } else {
            TransformByMatrixWithW((const Quad16*)&rec.block, (const Vec4*)part, 1.0f, (Vec4*)&rec.pos);
        }
        u128 d = Vu0::Sub(Vu0::Q(rec.pos), Vu0::Q(cam->position));
        if (self->bits28 == 1) {
            Vec4 r;
            f32 fade;
            f32 radius = part->radius;
            u128 ones = Vu0::Ones();
            Vu0::Q(r) = Vu0::FromFloat(radius);
            if ((Vu0::PlaneSigns(Vu0::Q(cam->planes[0]), Vu0::Q(cam->planes[1]), Vu0::Q(cam->planes[2]), d, ones, Vu0::Q(r)) ^ 0xF0) != 0) {
                continue;
            }
            if (ComputeCameraDistanceFade(cam, d, &fade, radius, part->nearFade) == 0) {
                continue;
            }
            rec.block.outerFade = alpha * fade;
            if (part->usesFarFade != 0) {
                if (part->farFade < part->nearFade) {
                    if (ComputeCameraDistanceFade(cam, d, &fade, part->radius, part->farFade) == 0) {
                        rec.block.innerFade = 0.0f;
                    } else {
                        rec.block.innerFade = glow * fade;
                    }
                }
            }
        } else {
            if (src == 0) {
                Vec4 r;
                u128 ones = Vu0::Ones();
                Vu0::Q(r) = Vu0::FromFloatAt(part->radius);
                if ((Vu0::PlaneSigns(Vu0::Q(cam->planes[0]), Vu0::Q(cam->planes[1]), Vu0::Q(cam->planes[2]), d, ones, Vu0::Q(r)) ^ 0xF0) != 0) {
                    continue;
                }
            }
            rec.block.outerFade = alpha;
            rec.block.innerFade = glow;
        }
        if (part->fade != 0) {
            Vec4 n;
            ScaledTransform* m = &rec.block;
            u128 fb = Vu0::Q(g_zeroVector);
            u128 v = Vu0::Rotate(*m, Vu0::Q(part->fade->axis));
            u128 len = Vu0::Length(v);
            if (Vu0::ToFloatMoved(len) < 0.0001f) {
                v = fb;
            } else {
                v = Vu0::DivX(v, len);
            }
            Vu0::Set(n, v);
            // ToFloatMoved: the mtc1 is the asm (cost 1), so abs.s issues the cycle after it,
            // ahead of the cubic's loads (ToFloat's mtc1 is reload's, with a latency of 2).
            f32 t = __builtin_fabsf(Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(n), Vu0::Q(g_camera->rotation))));
            rec.block.outerFade = rec.block.outerFade * ClampToRange((ValueRange*)g_unitRange, part->fade->cubic.Eval(t));
        }
        if (state != 0) {
            f32 goal = 1.0f;
            if (g_gameClock.elapsed < state->until) {
                goal = 0.5f;
            }
            if (goal != state->fade) {
                state->fade = ApproachValueWithRamp(state->fade, goal, g_gameClock.dt, (RampProfile*)g_fadeRampProfile, 0);
            }
            rec.block.outerFade = rec.block.outerFade * state->fade;
        }
        if (rec.block.outerFade <= 0.0f) {
            continue;
        }
        drawn = 1;
        if (part->dist != 3.402823466e+38f) {
            rec.dist = part->dist;
        } else {
            rec.dist = Vu0::ToFloat(Vu0::Dot(d, d));
        }
        rec.kind = part->kind;
        rec.block.innerFade = rec.block.innerFade * rec.block.outerFade;
        s32 kind = rec.kind;
        if (rec.block.outerFade != 1.0f) {
            switch (kind) {
            case 3:
            case 4:
            case 7:
            case 8:
                rec.kind = 0xD;
                break;
            case 5:
            case 9:
                rec.kind = 0xE;
                break;
            }
        }
        ModelPartHook* hook = part->hook;
        if (hook != 0 && hook->vt->m04 != 0) {
            hook->vt->m04(hook, self, &rec);
        }
        if (part->matrix != 0 || part->cameraFacing != 0) {
            Mat4A saved = *(Mat4A*)&rec.block;
            if (part->matrix != 0) {
                *(Mat4A*)&rec.block = MultiplyMatrices(*(Mat4A*)&rec.block, *(Mat4A*)part->matrix);
            }
            if (part->cameraFacing != 0) {
                BuildCameraFacingMatrix(self, cam, part->cameraFacing, (f32*)&rec.pos, (Mat4A*)&rec.block);
            }
            QueueDeferredRequest((DeferredRequest*)&rec);
            *(Mat4A*)&rec.block = saved;
        } else {
            QueueDeferredRequest((DeferredRequest*)&rec);
        }
    }
    if (drawn != 0) {
        self->desc02()->m27(self, src);
        if (self->indexedAttachments != 0) {
            for (s32 j = 0; j < self->valueCount; j++) {
                if (self->indexedAttachments[j] != 0) {
                    ApplyPoseSourceIndexedValue((Attachment*)self->indexedAttachments[j], j);
                } else {
                    self->currentValues[j] = (self->defaultValues)[j];
                }
            }
        }
    }
}


// Draws a flat beam (a quad strip) from p to q: it builds a basis whose long axis is q - p and
// whose width axis is perpendicular to the direction from the camera, scales it by sx and sy, and
// draws it as a transform. Falls back to a fixed axis when the beam points at the camera.
void DrawBeamBetweenPoints(PlacedObject* self, PlacedObject* b, Vec4* p, Vec4* q, f32 sx, f32 sy)
{
    Mat3 m;
    Vec4 e;
    ScaledTransform out;
    const Vec4* fallback = &g_zeroVector;
    Vu0::Q(m.r[2]) = Vu0::Sub(Vu0::Q(*q), Vu0::Q(*p));
    Vu0::Q(e) = Vu0::Sub(Vu0::Q(*p), Vu0::Q(*(Vec4*)&b->link40));
    u128 c = Vu0::Cross(Vu0::Q(e), Vu0::Q(m.r[2]));
    Vu0::Q(m.r[1]) = c;
    u128 len = Vu0::Length(c);
    if (Vu0::ToFloat(len) < 0.0001f) {
        m.r[1] = *fallback;
    } else {
        Vu0::Q(m.r[1]) = Vu0::DivX(c, len);
    }
    f32 minLen = 0.01f;
    if (minLen < Vu0::ToFloatMoved(len)) {
        u128 c2 = Vu0::Cross(Vu0::Q(m.r[1]), Vu0::Q(m.r[2]));
        Vu0::Q(m.r[0]) = c2;
        Vu0::Q(m.r[0]) = Vu0::DivX(c2, Vu0::Length(c2));
        Vu0::Q(m.r[1]) = Vu0::MulX(Vu0::Q(m.r[1]), Vu0::Scalar(sx));
        Vu0::Q(m.r[2]) = Vu0::MulX(Vu0::Q(m.r[2]), Vu0::Scalar(minLen));
        BuildMatrixFromRotationAndTranslation((const Vec4*)p, (const Mat3*)&m, (Mat4A*)&out);
        out.innerFade = sy;
        out.outerFade = sy;
        self->desc02()->m26(self, b, &out);
    }
}

// Stores value in the object's record at 0x22C (offset 0x3C, with bit 2 set in its flags at 0x38),
// and in those of its placed-object children.
void SetObjectTreeRecordValue(PlacedObject* object, u32 value)
{
    ListFrame frame;
    PlacedObject* child = (PlacedObject*)object->children.head;
    object->recordValue = value;
    object->recordFlags |= 2;
    while (child != 0) {
        if ((child->desc->flags & 1) != 0)
            SetObjectTreeRecordValue(child, value);
        child = (PlacedObject*)child->next;
    }
}

// Stores value in the object's record at 0x22C (offset 0x3C) and sets bit 2 of that record's flags.
void SetObjectRecordValue(PlacedObject* state, u32 value)
{
    state->recordValue = value;
    state->recordFlags |= 2;
}

extern "C" f32 Sine(f32 x);

// Pulses the object's colour: blends the colour record's two colours by a sine of the game time
// (period r->factor seconds), converts the result from hue/saturation/value to RGB with alpha 0x80,
// and stores it on the object tree.
void ApplyPulsingColorToObjectTree(PlacedObject* self, f32 dt)
{
    Vec4 hsv;
    ColorRecord* r = self->colorRecord;
    f32 c = Sine(FloatRemainder(g_gameTime[0], r->factor) * 6.2831855f / r->factor) * 0.5f + 0.5f;
    Vu0::Q(hsv) = Vu0::Add(Vu0::MulX(Vu0::Q(r->c10), Vu0::Scalar(c)), Vu0::MulX(Vu0::Q(r->c20), Vu0::Scalar(1.0f - c)));
    f32 rgb[4];
    u8 color[4];
    ConvertHsv255ToRgb255((Quad_001B4580*)&hsv, rgb);
    color[0] = (s32)rgb[0];
    color[1] = (s32)rgb[1];
    color[2] = (s32)rgb[2];
    color[3] = 0x80;
    SetObjectTreeRecordValue(self, *(u32*)color);
}

// Sets every draw part of the object and its placed-object children to type 2 with the given value.
void SetObjectTreeRecordsValue(PlacedObject* object, void* value)
{
    ListFrame frame;
    for (s32 i = 0; i < object->drawPartCount; i++) {
        // address arithmetic over a variable index
        DrawPart* record = (DrawPart*)((u8*)object->drawParts + i * 0x70);
        record->type = 2;
        record->object = value;
    }
    PlacedObject* child = (PlacedObject*)object->children.head;
    while (child != 0) {
        if ((child->desc->flags & 1) != 0)
            SetObjectTreeRecordsValue(child, value);
        child = (PlacedObject*)child->next;
    }
}

// Gives the object a node in the world (the ramp node) if it has none, at level 1 when the object
// is attached and 0 otherwise.
void EnsureObjectWorldNode(PlacedObject* self)
{
    if (self->rampNode == 0) {
        self->rampNode = AddObjectNodeToWorld(self);
        if (IsObjectAttached(self) != 0) {
            self->rampNode->level = 1.0f;
        } else {
            self->rampNode->level = 0.0f;
        }
    }
}

// Each arm stores the rate itself: with one store after the join, GCSE copies the node pointer
// into a pseudo for it, and that copy, scheduled between the level's load and its use, gives the
// level the longer span in local-alloc and the constant takes $f1 first.
void FadeInPlacedObject(Collider* self, f32 time)
{
    if (!IsObjectAttached(self) || self->rampNode != 0) {
        EnsureObjectWorldNode(self);
        self->desc->m02(self);
        if (time == 0.0f) {
            f32 zero = 0.0f;
            self->rampNode->rate = zero >? 1.0f - self->rampNode->level + 0.0001f;
        } else {
            self->rampNode->rate = 1.0f / time;
        }
    }
}

// Starts fading the object out: its ramp node's rate becomes -1/time (a rate that clears it within
// a frame when time is 0).
void FadeOutPlacedObject(Collider* self, f32 time)
{
    if (IsObjectAttached(self)) {
        EnsureObjectWorldNode(self);
        f32 rate;
        if (time == 0.0f) {
            f32 zero = 0.0f;
            rate = zero <? -self->rampNode->level - 0.0001f;
        } else {
            rate = -1.0f / time;
        }
        self->rampNode->rate = rate;
    }
}


// k, the vector the second rotation starts from, is written as a quadword at its own address:
// a store through Vu0::Q or Set leaves the address in a pseudo that CSE keeps in a saved register
// for the later &k, where retail forms it again for the call. Each product is a matrix made where
// it is declared, so MultiplyMatrices builds it in place; the first lives in its own block, and
// the second takes its stack slot, as retail's frame shows.
void BuildCameraFacingMatrix(void* unused0, Camera* cam, void* unused2, f32* pos, Mat4A* m)
{
    Vec4 a;
    Mat3 rot;
    Mat4A t;
    Mat4A local;
    Vec4 k;
    *(u128*)&k = Vu0::FromFloat(-1.0f);
    Vu0::Q(a) = Vu0::MulX(Vu0::Q(cam->rotation), *(u128*)&k);
    BuildShortestArcRotation((const Vec4*)m, &a, &rot);
    local = *m;
    local.m[3][0] -= pos[0];
    local.m[3][1] -= pos[1];
    local.m[3][2] -= pos[2];
    BuildMatrixFromRotationAndTranslation((const Vec4*)&g_zeroVector, (const Mat3*)&rot, (Mat4A*)&t);
    {
        Mat4A r = MultiplyMatrices(t, local);
        *m = r;
        *(u128*)&k = Vu0::Sub(Vu0::Q(r.m[2]), Vu0::MulX(Vu0::Q(a), Vu0::Dot(Vu0::Q(r.m[2]), Vu0::Q(a))));
    }
    BuildShortestArcRotation(&k, (const Vec4*)&cam->rotationRow2, &rot);
    BuildMatrixFromRotationAndTranslation((const Vec4*)pos, (const Mat3*)&rot, (Mat4A*)&t);
    Mat4A r = MultiplyMatrices(t, *m);
    *m = r;
}

// Copy method: lets the object copy from its owner (method 9), creates a copy of each of the
// owner's children under it, and, for a collider-flagged root (flag 2, no parent), updates its
// anchor-mode flags.
void ClonePlacedObject(PlacedObject* self, PlacedObject* owner)
{
    ListFrame it;
    ListWalkBegin::Of(&it, &owner->children);
    self->desc->m09(self, owner);
    BaseObject* obj = ListWalkNextBase::Of(&it);
    while (obj != 0) {
        (void)CreateObjectCopy(obj, self->world, self);
        obj = ListWalkNextBase::Of(&it);
    }
    if ((self->desc->flags & 2) && self->parent == 0) {
        UpdateAnchorModeFlags((Collider*)self);
    }
    g_activeListFrames = (ListFrame*)it.prev;
}

// Makes self a copy of src: the data is copied, then self's own list links, parent and root, flags
// bit 37 and children list are put back. Attachments, the link record and the range record are
// cloned, and the model's attachment block is copied.
void CopyPlacedObject(PlacedObject* self, PlacedObject* src)
{
    PlacedObject* s54 = self->linkListOwner;
    PlacedObject* s50 = self->root;
    ObjectListLink t48 = self->link48;
    u64 bit = (self->flags >> 37) & 1;
    ObjectListLink t40 = self->link40;
    ObjectListLink t58 = self->link58;
    ObjectList t60 = self->list60;
    ObjectList t1E0 = self->list1E0;
    CopyObjectData(self, src);
    CopyAttachmentBlock((AttachmentCopy*)self->sub22C, self, src->sub22C);
    if (self->linkRecord) {
        self->linkRecord = (Rec2195_224*)CopyToFrontMemory(0xC0, self->linkRecord);
    }
    ClearList(&self->children);
    self->link48 = t48;
    self->link40 = t40;
    self->link58 = t58;
    self->list60 = t60;
    self->linkListOwner = s54;
    self->root = s50;
    self->flags = (self->flags & ~(1ULL << 37)) | ((u64)bit << 37);
    self->list1E0 = t1E0;
    self->desc02()->m2B(self);
    if (src->baseAttachment) {
        self->baseAttachment = ClonePoseSource(src->baseAttachment, self->world, self);
        InsertAttachment(self, self->baseAttachment);
    }
    if (src->aimAttachment) {
        self->aimAttachment = (AimAttachment*)ClonePoseSource(src->aimAttachment, self->world, self);
        InsertAttachment(self, self->aimAttachment);
    }
    if (src->ownValueAttachment) {
        self->ownValueAttachment = (TiltValueAttachment*)ClonePoseSource(src->ownValueAttachment, self->world, self);
        InsertAttachment(self, self->ownValueAttachment);
    }
    if (src->rangeRecord) {
        u8* p = (u8*)TakePoolSlot(&self->world->pool1BF4);
        CopyMemory(p, src->rangeRecord, 0x2E0);
        ClearListLinks((ListLink*)&((RangeRecord*)p)->next);
        self->rangeRecord = (RangeRecord*)p;
        AppendToList(&self->world->list1C00, p);
    }
    if (src->soundRecord) {
        self->soundRecord = (SoundRecord*)CopyToFrontMemory(0x24, src->soundRecord);

    }
    if (src->colorRecord) {
        self->colorRecord = (ColorRecord*)CopyToFrontMemory(0x40, src->colorRecord);
    }
    if (self->flags & (1ULL << 36)) {
        if (IsObjectAttached(self)) {
            AddCameraObject(g_camera, self);
        }
    }
    if (self->p20C != (u8*)g_defaultPositionSpring) self->p20C = (u8*)CopyToFrontMemory(0x10, self->p20C);
    if (self->p210 != (u8*)g_defaultVelocitySpring) self->p210 = (u8*)CopyToFrontMemory(0x10, self->p210);
    if (self->p214 != (u8*)g_defaultRotationSpring) self->p214 = (u8*)CopyToFrontMemory(0x10, self->p214);
    if (self->p218 != (u8*)g_defaultSpinSpring) self->p218 = (u8*)CopyToFrontMemory(0x10, self->p218);
}

// On notification 1 (attached), starts the object's sound if it has a record, is not yet playing
// and the game time is not 0.
void HandlePlacedObjectNotification(PlacedObject* self, s32 mode, void* arg)
{
    if (mode == 1) {
        SoundRecord* s = self->soundRecord;
        if (s != 0) {
            if (g_gameTime[0] != 0.0f) {
                if (s->soundWord == 0) {
                    StartSoundEffect(s->soundId, (PlayingSound**)&s->soundWord, self, 0, s->outerRange, s->innerRange, s->baseVolume, s->pitch, s->startParam, (f32*)&s->b14, 0);
                }
            }
        }
    }
}

// Stores the position, runs the moved method (0x12), settles the position attachment's modes and
// sends notification 3 with the old position.
void SetPlacedObjectPosition(PlacedObject* self, Vec4* src)
{
    MoveNotice f;
    f.q = self->v140;
    f.self = self;
    self->pos = *src;
    if (self->desc->m12 != 0) {
        self->desc->m12(self);
    }
    if (self->positionAttachment != 0) {
        SettlePoseSourceModes(self->positionAttachment);
    }
    self->desc->m0E(self, 3, &f);
}

LINKER_REMNANT(func_00127468);

// Stores the rotation, runs the moved method (0x12), settles the orientation attachment's modes and
// sends notification 4.
void SetPlacedObjectRotation(PlacedObject* self, Mat3* src)
{
    self->rot = *src;
    if (self->desc->m12)
        self->desc->m12(self);
    if (self->orientationAttachment)
        SettlePoseSourceModes(self->orientationAttachment);
    self->desc->m0E(self, 4, self);
}

// Stores the velocity, settles the position attachment's modes and, when the velocity is not
// negligible, clears the root tries.
void SetPlacedObjectVelocity(PlacedObject* self, Vec4* src)
{
    self->v150 = *src;
    if (self->positionAttachment != 0) {
        SettlePoseSourceModes(self->positionAttachment);
    }
    if (IsVelocityNegligible(src) == 0) {
        ClearRootTries(self);
    }
}

// Sets the velocity from three floats through method 0x20.
void SetPlacedObjectVelocityFromFloats(ObjectCycler* self, f32 x, f32 y, f32 z)
{
    Vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    self->desc02()->m20(self, (Vec4*)&v);
}

// Stores the spin, settles the orientation attachment's modes and, when the spin is not negligible,
// clears the root tries.
void SetPlacedObjectSpin(PlacedObject* self, Vec4* src)
{
    self->v160 = *src;
    if (self->orientationAttachment != 0) {
        SettlePoseSourceModes(self->orientationAttachment);
    }
    if (IsSpinNegligible(src) == 0) {
        ClearRootTries(self);
    }
}

// Sets the spin from three floats through method 0x21.
void SetPlacedObjectSpinFromFloats(PairedObject* self, f32 x, f32 y, f32 z)
{
    f32 v[3];
    v[0] = x;
    v[1] = y;
    v[2] = z;
    self->desc02()->m21(self, (Vec4*)v);
}

// Sets the velocity from a vector in the object's own frame, rotated into world space, through
// method 0x20.
void SetPlacedObjectLocalVelocity(PlacedObject* self, const Vec4* local)
{
    Vec4 v;
    Vu0::Q(v) = Vu0::Rotate(self->rot, Vu0::Q(*local));
    self->desc02()->m20(self, &v);
}

ASM_FUNC(func_00127678);

// Makes self take other's world position, rotation, velocity and spin, converted into self's parent
// frame, and copies the link record's angle when both have flag 0x20. Children are then given the
// same frame from the child of other with the same id.
void CopyPlacedObjectFrame(PlacedObject* self, PlacedObject* other)
{
    TakeFrameLocals L;
    TransformPointBetweenFrames(0, (PlacedObject*)self->parent, &other->v140, (Vec4*)L.a20);
    TransformRotationBetweenFrames(0, (PlacedObject*)self->parent, &other->m110, (Mat3*)L.a50);
    ConvertVectorsBetweenObjectFrames(other->parent, self->parent, &other->v140, &other->v150, &other->v160, 0, 0, L.a30, L.a40, 0, 0);
    self->desc02()->m1D(self, (Vec4*)L.a20);
    self->desc02()->m1E(self, (Mat3*)L.a50);
    self->desc02()->m20(self, (Vec4*)L.a30);
    self->desc02()->m21(self, (Vec4*)L.a40);
    Rec2195_224* a = self->linkRecord;
    if (a != 0 && (a->flags & 0x20)) {
        Rec2195_224* b = other->linkRecord;
        if (b != 0 && (b->flags & 0x20)) {
            a->angle = b->angle;
            self->linkRecord->angleSlope = other->linkRecord->angleSlope;
        }
    }
    PlacedObject* n = (PlacedObject*)self->children.head;
    if (n != 0) {
        do {
            if ((n->desc->flags ^ 1) & 1)
                continue;
            PlacedObject* h = (PlacedObject*)FindFirstObjectById(self->world, 2, n->id, other);
            if (h == 0)
                continue;
            if ((h->desc->flags ^ 1) & 1)
                continue;
            if (n->linkRecord != 0 && (n->linkRecord->flags & 0xC))
                continue;
            n->desc02()->m1F(n, h);
        } while ((n = (PlacedObject*)n->next) != 0);
    }
}

void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);

// Gives the linear velocity (vel, velSum) and spin (spin, spinSum) of the frame chain self up to
// top at the point origin, adding each level's own motion plus the cross-product terms of the
// rotating levels above it.
void ComputeObjectMotionInFrame(PlacedObject* self, PlacedObject* top, Vec4* origin, Vec4* vel, Vec4* velSum, Vec4* spin, Vec4* spinSum)
{
    PlacedObject* chain[16];
    Vec4 V;
    Vec4 W;
    Vec4 d;
    Vec4 c1;
    Vec4 t;
    Vec4 c2;
    Vec4 c3;
    u128 zero = Vu0::Zero();
    if (vel != 0) {
        Vu0::Q(*vel) = zero;
    }
    if (spin != 0) {
        Vu0::Q(*spin) = zero;
    }
    Vu0::Q(V) = zero;
    Vu0::Q(W) = zero;
    PlacedObject* o = self;
    PlacedObject** p = chain;
    while (o != top) {
        *p = o;
        p++;
        Rec2195_224* rec = o->linkRecord;
        if (rec != 0 && (rec->flags & 0xC)) {
            o = (PlacedObject*)rec->p60;
        } else {
            o = (PlacedObject*)o->parent;
        }
    }
    PlacedObject* prev = 0;
    for (p--; p >= chain; p--) {
        o = *p;
        if (vel != 0 || velSum != 0 || spin != 0) {
            TransformDirectionBetweenFrames(prev, top, &o->v160, &d);
            Vu0::Q(V) = Vu0::Add(Vu0::Q(V), Vu0::Q(d));
        }
        if (spinSum != 0 || spin != 0) {
            TransformDirectionBetweenFrames(prev, top, &o->v180, &d);
            Vu0::Q(W) = Vu0::Add(Vu0::Q(W), Vu0::Q(d));
        }
        if (vel != 0 || spin != 0) {
            Vec4* at = p > chain ? &p[-1]->v140 : origin;
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(*at), Vu0::Q(o->v140));
            TransformDirectionBetweenFrames(0, top, &d, &d);
            Vu0::Q(c1) = Vu0::Cross(Vu0::Q(V), Vu0::Q(d));
            if (vel != 0) {
                Vu0::Q(*vel) = Vu0::Add(Vu0::Q(*vel), Vu0::Q(c1));
                TransformDirectionBetweenFrames(prev, top, &o->v150, &t);
                Vu0::Q(*vel) = Vu0::Add(Vu0::Q(*vel), Vu0::Q(t));
            }
            if (spin != 0) {
                Vu0::Q(c2) = Vu0::Cross(Vu0::Q(V), Vu0::Q(c1));
                Vu0::Q(*spin) = Vu0::Add(Vu0::Q(*spin), Vu0::Q(c2));
                Vu0::Q(c3) = Vu0::Cross(Vu0::Q(W), Vu0::Q(d));
                Vu0::Q(*spin) = Vu0::Add(Vu0::Q(*spin), Vu0::Q(c3));
                TransformDirectionBetweenFrames(prev, top, &o->v170, &t);
                Vu0::Q(*spin) = Vu0::Add(Vu0::Q(*spin), Vu0::Q(t));
            }
        }
        prev = o;
    }
    if (velSum != 0) {
        *velSum = V;
    }
    if (spinSum != 0) {
        *spinSum = W;
    }
}


// Composes the position, rotation, velocity and spin of every frame from self up to top (following
// a link record's linked object when flags 0xC are set, otherwise the parent), writing each depth's
// accumulated value to the arrays at index 0..n-1 (any may be null).
void AccumulateFrameChain(PlacedObject* self, PlacedObject* top, s32 n, Vec4* pos, Mat3* rot, Vec4* vel, Vec4* spin)
{
    PlacedObject* chain[16];
    Vec4 P;
    Vec4 V;
    Vec4 W;
    Mat3 M;
    Mat3 N;
    Vec4 x;
    Vec4 y;
    Vec4 z;
    Mat3 r;
    s32 i = 0;
    while (self != top) {
        chain[i] = self;
        i++;
        Rec2195_224* rec = self->linkRecord;
        if (rec != 0 && (rec->flags & 0xC)) {
            self = (PlacedObject*)rec->p60;
        } else {
            self = (PlacedObject*)self->parent;
        }
    }
    P = g_zeroVector;
    M = g_identityMatrix;
    V = g_zeroVector;
    W = g_zeroVector;
    while (i < n) {
        n--;
        if (pos != 0) {
            pos[n] = P;
        }
        if (rot != 0) {
            rot[n] = M;
        }
        if (vel != 0) {
            vel[n] = V;
        }
        if (spin != 0) {
            spin[n] = W;
        }
    }
    for (i--; i >= 0; i--) {
        self = chain[i];
        if (pos != 0 || vel != 0) {
            Vu0::Q(x) = Vu0::RotateUntied(M, Vu0::Q(self->pos));
            Vu0::Q(P) = Vu0::Add(Vu0::Q(P), Vu0::Q(x));
            if (vel != 0) {
                Vu0::Q(y) = Vu0::Rotate(M, Vu0::Q(self->v150));
                Vu0::Q(z) = Vu0::Cross(Vu0::Q(W), Vu0::Q(x));
                Vu0::Q(V) = Vu0::Add(Vu0::Q(V), Vu0::Q(y));
                Vu0::Q(V) = Vu0::Add(Vu0::Q(V), Vu0::Q(z));
            }
        }
        if (spin != 0 || vel != 0) {
            Vu0::Q(x) = Vu0::Rotate(M, Vu0::Q(self->v160));
            Vu0::Q(W) = Vu0::Add(Vu0::Q(W), Vu0::Q(x));
        }
        const u128* q = (const u128*)&self->rot;
        u128 a0 = Vu0::Q(M.r[0]);
        u128 a1 = Vu0::Q(M.r[1]);
        u128 a2 = Vu0::Q(M.r[2]);
        Vu0::Q(x) = Vu0::RotateRows(a0, a1, a2, q[0]);
        r.r[0] = x;
        Vu0::Q(y) = Vu0::RotateRows(a0, a1, a2, q[1]);
        r.r[1] = y;
        Vu0::Q(z) = Vu0::Q(r.r[2]) = Vu0::RotateRows(a0, a1, a2, q[2]);
        N = r;
        M = r;
        if (i < n) {
            if (pos != 0) {
                pos[i] = P;
            }
            if (rot != 0) {
                rot[i] = M;
            }
            if (vel != 0) {
                vel[i] = V;
            }
            if (spin != 0) {
                spin[i] = W;
            }
        }
        IgnoreStackLocal(&P);
    }
}

// Converts a position, rotation, velocity and spin given in self's frame into the frame of the
// ancestor top (any may be null), using AccumulateFrameChain for the frame between them: positions
// are rotated and offset, velocities also get the spin-times-offset term.
void TransformStateToAncestorFrame(PlacedObject* self, PlacedObject* top, Vec4* pos, Mat3* rot, Vec4* vel, Vec4* spin)
{
    Mat3 m;
    Vec4 p;
    Vec4 v;
    Vec4 w;
    Mat3 x;
    AccumulateFrameChain(self, top, 1, (pos != 0 || vel != 0) ? &p : 0, &m, vel != 0 ? &v : 0,
                  (spin != 0 || vel != 0) ? &w : 0);
    if (pos != 0 || vel != 0) {
        if (pos != 0) {
            Vu0::Q(x.r[0]) = Vu0::Rotate(m, Vu0::Q(*pos));
            Vu0::Q(*pos) = Vu0::Add(Vu0::Q(p), Vu0::Q(x.r[0]));
        } else {
            x.r[0] = g_zeroVector;
        }
    }
    if (vel != 0) {
        Vu0::Q(x.r[1]) = Vu0::Rotate(m, Vu0::Q(*vel));
        Vu0::Q(x.r[2]) = Vu0::Cross(Vu0::Q(w), Vu0::Q(x.r[0]));
        Vu0::Q(v) = Vu0::Add(Vu0::Q(v), Vu0::Q(x.r[1]));
        Vu0::Q(*vel) = Vu0::Add(Vu0::Q(v), Vu0::Q(x.r[2]));
    }
    if (spin != 0) {
        Vu0::Q(x.r[0]) = Vu0::Rotate(m, Vu0::Q(*spin));
        Vu0::Q(*spin) = Vu0::Add(Vu0::Q(w), Vu0::Q(x.r[0]));
    }
    if (rot != 0) {
        MulRotation(&x, m, *rot);
        *rot = x;
    }
}

// The point in from's frame (the world's for none) in to's frame: through from's rotation and
// position, then less to's position and through the transpose of to's rotation.
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out)
{
    Vec4 world;
    Vec4 local;
    if (from != to) {
        if (from != 0) {
            Vu0::Q(world) = Vu0::Rotate(from->m110, Vu0::Q(*in));
            Vu0::Q(world) = Vu0::Add(Vu0::Q(from->v140), Vu0::Q(world));
            in = &world;
        }
        if (to != 0) {
            Vu0::Q(local) = Vu0::Sub(Vu0::Q(*in), Vu0::Q(to->v140));
            Vu0::Q(*out) = Vu0::RotateTransposed(to->m110, Vu0::Q(local));
            return;
        }
    }
    *out = *in;
}

// The direction in from's frame (the world's for none) in to's frame: through from's rotation,
// then through the transpose of to's.
void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out)
{
    Vec4 world;
    Vec4 local;
    if (from != to) {
        if (from != 0) {
            Vu0::Q(world) = Vu0::Rotate(from->m110, Vu0::Q(*in));
            in = &world;
        }
        if (to != 0) {
            Vu0::Q(local) = Vu0::RotateTransposed(to->m110, Vu0::Q(*in));
            *out = local;
            return;
        }
    }
    *out = *in;
}


// The rotation in from's frame (the world's for none) in to's frame: through from's rotation,
// then the product with the transpose of to's.
void TransformRotationBetweenFrames(PlacedObject* from, PlacedObject* to, Mat3* in, Mat3* out)
{
    Mat3 world;
    Mat3 t;
    if (from != to) {
        if (from != 0) {
            MulRotationRows(&world, from->m110, *in);
            in = &world;
        }
        if (to != 0) {
            t = MultiplyByTransposedMatrix3x3(to->m110, *in);
            *out = t;
            return;
        }
    }
    *out = *in;
}

// True when the position attachment is in mode 5 or the orientation attachment is
// (animation-driven).
s32 HasAnimationDrivenAttachment(SwitchedCollider *self) {
    Attachment *p = self->positionAttachment;
    if (p != 0 && p->mode0 == 5) {
        return 1;
    }
    p = self->orientationAttachment;
    if (p != 0) {
        if (p->mode1 == 5) {
            return 1;
        }
    }
    return 0;
}

// Releases every position and orientation attachment of the player that is in mode 5 (driven by an
// animation), one at a time from the front of each list.
void ReleaseAnimationDrivenAttachments(Player* self)
{
    Attachment* a = self->positionAttachment;
    if (a != 0 && a->mode0 == 5) {
        do {
            a->vt->release(a, 0);
            a = self->positionAttachment;
        } while (a != 0 && a->mode0 == 5);
    }
    Attachment* b = self->orientationAttachment;
    if (b != 0 && b->mode1 == 5) {
        do {
            b->vt->release(b, 0);
            b = self->orientationAttachment;
        } while (b != 0 && b->mode1 == 5);
    }
}

// Converts up to four vectors from frame from to frame to via their common ancestor: each is
// rotated into the ancestor, the motion of from at point pt is added, the motion of to is
// subtracted, and the result rotated into to. Null vectors are skipped.
void ConvertVectorsBetweenObjectFrames(BaseObject* from, BaseObject* to, void* pt, void* d, void* e, s32 f, s32 g, u8* h, u8* i, s32 j, s32 k)
{
    Vec4 a[4];
    Vec4 b[4];
    BaseObject* root = FindCommonAncestor(from, to);
    if (d != 0) {
        TransformDirectionBetweenFrames((PlacedObject*)from, (PlacedObject*)root, (Vec4*)d, &a[0]);
    }
    if (e != 0) {
        TransformDirectionBetweenFrames((PlacedObject*)from, (PlacedObject*)root, (Vec4*)e, &a[1]);
    }
    if (f != 0) {
        TransformDirectionBetweenFrames((PlacedObject*)from, (PlacedObject*)root, (Vec4*)f, &a[2]);
    }
    if (g != 0) {
        TransformDirectionBetweenFrames((PlacedObject*)from, (PlacedObject*)root, (Vec4*)g, &a[3]);
    }
    if (from != 0) {
        ComputeObjectMotionInFrame((PlacedObject*)from, (PlacedObject*)root, (Vec4*)pt, d != 0 ? &b[0] : 0, e != 0 ? &b[1] : 0, f != 0 ? &b[2] : 0, g != 0 ? &b[3] : 0);
        if (d != 0) {
            Vu0::Q(a[0]) = Vu0::Add(Vu0::Q(a[0]), Vu0::Q(b[0]));
        }
        if (e != 0) {
            Vu0::Q(a[1]) = Vu0::Add(Vu0::Q(a[1]), Vu0::Q(b[1]));
        }
        if (f != 0) {
            Vu0::Q(a[2]) = Vu0::Add(Vu0::Q(a[2]), Vu0::Q(b[2]));
        }
        if (g != 0) {
            Vu0::Q(a[3]) = Vu0::Add(Vu0::Q(a[3]), Vu0::Q(b[3]));
        }
    }
    if (to != 0) {
        ComputeObjectMotionInFrame((PlacedObject*)to, (PlacedObject*)root, (Vec4*)pt, h != 0 ? &b[0] : 0, i != 0 ? &b[1] : 0, j != 0 ? &b[2] : 0, k != 0 ? &b[3] : 0);
        if (h != 0) {
            Vu0::Q(a[0]) = Vu0::Sub(Vu0::Q(a[0]), Vu0::Q(b[0]));
        }
        if (i != 0) {
            Vu0::Q(a[1]) = Vu0::Sub(Vu0::Q(a[1]), Vu0::Q(b[1]));
        }
        if (j != 0) {
            Vu0::Q(a[2]) = Vu0::Sub(Vu0::Q(a[2]), Vu0::Q(b[2]));
        }
        if (k != 0) {
            Vu0::Q(a[3]) = Vu0::Sub(Vu0::Q(a[3]), Vu0::Q(b[3]));
        }
    }
    if (h != 0) {
        TransformDirectionBetweenFrames((PlacedObject*)root, (PlacedObject*)to, &a[0], (Vec4*)h);
    }
    if (i != 0) {
        TransformDirectionBetweenFrames((PlacedObject*)root, (PlacedObject*)to, &a[1], (Vec4*)i);
    }
    if (j != 0) {
        TransformDirectionBetweenFrames((PlacedObject*)root, (PlacedObject*)to, &a[2], (Vec4*)j);
    }
    if (k != 0) {
        TransformDirectionBetweenFrames((PlacedObject*)root, (PlacedObject*)to, &a[3], (Vec4*)k);
    }
}


// Works out a steering heading for the object from its position and orientation attachments (or its
// own pose), the displacement and the speed. A small state machine on bits30 switches on thresholds
// (25 distance, 10 speed). Results go to out0..out2; p1 and p3 default to two global vectors.
void ComputeObjectSteeringHeading(f32 a, f32 b, PlacedObject* self, f32* p1, f32* p3, f32* out0, f32* out1, f32* out2)
{
    Vec4 d;
    Vec4 g;
    Vec4 tgt;
    Vec4 pos;
    Vec4 vel;
    Vec4 w;
    Mat3 R;
    if (p1 == 0) {
        p1 = g_steeringHeadingCurve;
    }
    if (p3 == 0) {
        p3 = g_steeringHeadingLimits;
    }
    Attachment* pa = self->positionAttachment;
    Attachment* ra = self->orientationAttachment;
    if (pa != 0) {
        pa->vt->getPos(pa, 0.0f, &pos, &vel);
    } else {
        pos = self->pos;
        vel = g_zeroVector;
    }
    if (ra != 0) {
        ra->vt->getRot(ra, 0.0f, &R, &w);
    } else {
        R = self->rot;
        w = g_zeroVector;
    }
    Vu0::Set(d, Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->pos)));
    if (out1 == 0) {
        d.z = 0.0f;
    }
    f32 len1 = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(d)));
    f32 len2 = Vu0::ToFloat(Vu0::Length(Vu0::Q(vel)));
    switch (self->bits30) {
    case 0:
        if (len1 < 25.0f) {
            if (len2 < 10.0f) {
                self->bits30 = 1;
            }
        }
        break;
    case 1:
        if (50.0f < len1 || 10.0f < len2) {
            self->bits30 = 0;
        }
        break;
    }
    switch (self->bits30) {
    case 0: {
        if (0.0001f < len1) {
            f32 v = ClampRange::Of(p1[0] + len1 * (p1[1] + len1 * p1[2]), p3[0], p3[1]);
            Vu0::Q(g) = Vu0::MulX(Vu0::Q(d), Vu0::Scalar(v / len1));
        } else {
            Vu0::Q(g) = Vu0::Zero();
        }
        Vu0::Q(tgt) = Vu0::Add(Vu0::Q(g), Vu0::Q(vel));
        ConvertOffsetToSpherical(&tgt, 0, out0, out1, out2);
        break;
    }
    case 1:
        if (ra != 0) {
            ConvertOffsetToSpherical((Vec4*)&R, 0, out0, out1, 0);
            *out2 = 0.0f;
        } else {
            *out0 = b;
            if (out1 != 0) {
                *out1 = 0.0f;
            }
            *out2 = 0.0f;
        }
        break;
    }
}

// Appends each child to the script list being built; false as soon as one is refused, else true.
s32 TestChildrenAccepted(PlacedObject* self, ScriptListBuilder* context)
{
    ListFrame it;
    ListWalkBegin::Of(&it, (ObjectList*)&self->children);
    PlacedObject* obj;
    for (obj = ListWalkNextPlaced::Of(&it); obj != 0; obj = ListWalkNextPlaced::Of(&it)) {
        if (AppendPropertyToScriptList(context, &obj) == 0) {
            g_activeListFrames = (ListFrame*)it.prev;
            return 0;
        }
    }
    g_activeListFrames = (ListFrame*)it.prev;
    return 1;
}

// Creates a track pose source (an attachment driven by an animation track) for the object.
Attachment* CreateTrackAttachment(BaseObject* item)
{
    return CreatePoseSource(item->world, (PlacedObject*)item, (const T2195_Vt*)g_trackPoseSourceMethods);
}

void LoadFollowRecord(PlacedObject* self, void* a1);
void ReadSlotObjects(World* self, void* a1, void* a2);
struct BakedRow {
    s32 id;
    f32* values;
};

// Reads the object's saved data: rotation, position, three culling mode bytes, visibility mask, far
// and near fade distances (3.4e38 meaning unset: 1e10, and 2000 or the far one, whichever is
// lower), bounding radius, property records, model, follow record, per-id baked value rows and slot
// objects.
void LoadPlacedObject(PlacedObject* self, void* r)
{
    ReadBufferedRotation3((BufferedStream*)r, (u8*)&self->rot);
    ReadBufferedVector3((BufferedStream*)r, &self->pos);
    self->bits24 = ReadBufferedU8((BufferedStream*)r);
    self->bits26 = ReadBufferedU8((BufferedStream*)r);
    self->bits28 = ReadBufferedU8((BufferedStream*)r);
    self->visibilityMask = ReadBufferedU32((BufferedStream*)r);
    self->fadeDistanceFar = ReadBufferedFloat((BufferedStream*)r);
    self->fadeDistanceNear = ReadBufferedFloat((BufferedStream*)r);
    self->f2A4 = ReadBufferedFloat((BufferedStream*)r);
    self->boundRadius = ReadBufferedFloat((BufferedStream*)r);
    if (self->fadeDistanceFar == 3.4028235e+38f) {
        self->fadeDistanceFar = 10000000000.0f;
    }
    if (self->fadeDistanceNear == 3.4028235e+38f) {
        f32 m = self->fadeDistanceFar;
        f32 c = 2000.0f;
        self->fadeDistanceNear = c <? m;
    }
    ReadPropertyRecords((Animation*)self, (Stream83*)r);
    ReadPlacedObjectModel((ModelRecord*)self->sub22C, r, self);
    LoadFollowRecord(self, r);
    if (self->desc->m12 != 0) {
        self->desc->m12(self);
    }
    self->keyedValueCount = ReadBufferedU8((BufferedStream*)r);
    BakedRow* rows = (BakedRow*)AllocateFrontMemory(self->keyedValueCount << 3);
    self->keyedValues = rows;
    for (s32 i = 0; i < self->keyedValueCount; i++) {
        BakedRow* row = &((BakedRow*)self->keyedValues)[i];
        row->id = ReadBufferedS16((BufferedStream*)r);
        row->values = (f32*)AllocateFrontMemory(self->valueCount << 2);
        for (s32 j = 0; j < self->valueCount; j++) {
            row->values[j] = ReadBufferedFloat((BufferedStream*)r);
        }
    }
    ReadSlotObjects(self->world, self, r);
}

// Reads the object's follow (link) record: a flag word, and if it is non-zero a 0xC0-byte record is
// allocated holding two optional rotations, the object the object follows (by id, kind 3, or a raw
// index for flag 0x10) and the other values the flags say are present.
void LoadFollowRecord(PlacedObject* self, void* a1)
{
    s32 flags = ReadBufferedU32((BufferedStream*)a1);
    if (flags) {
        Rec2195_224* p = (Rec2195_224*)AllocateZeroedFrontMemory(0xC0);
        self->linkRecord = p;
        p->flags = flags;

        u8* q = (u8*)&p->m[1];
        p->m[0] = g_identityMatrix;
        *(Mat3*)q = g_identityMatrix;
        if (flags & 1) ReadBufferedRotation3((BufferedStream*)a1, (u8*)&p->m[0]);
        if (flags & 2) ReadBufferedRotation3((BufferedStream*)a1, q);
        if (flags & 0xC) {
            s32 r = ReadBufferedS16((BufferedStream*)a1);
            if (r != -1) {
                p->p60 = (BaseObject*)FindFirstObjectById(self->world, 3, r, self);
            }
        }
        if (flags & 0x10) {
            p->p60 = (BaseObject*)ReadBufferedS16((BufferedStream*)a1);
        }
        if (flags & 0x20) {
            p->p84 = (BaseObject*)ReadBufferedS16((BufferedStream*)a1);
            ReadBufferedVector3((BufferedStream*)a1, &p->q60[0]);
            ReadBufferedVector3((BufferedStream*)a1, &p->q60[1]);
            f32 f = WrapAngle(ReadBufferedFloat((BufferedStream*)a1));
            p->linkFlags = 0;
            p->initialAngle = f;
            p->angle = f;
        }
        if (flags & 0x40) {
            p->p60 = (BaseObject*)ReadBufferedS16((BufferedStream*)a1);
            p->p64 = (BaseObject*)ReadBufferedS16((BufferedStream*)a1);
        }
        if (flags & 0x80) {
            p->unscaleByParent = ReadBufferedU8((BufferedStream*)a1);
        }
    }
}

// After loading, turns the object ids stored in its link record into objects, by the record's
// flags: 0x10 one followed object, 0x20 a target whose parent and common ancestor with this object
// are also stored, 0x40 two objects; sets flag 0x8000.
void ResolveFollowRecordObjects(PlacedObject* self)
{
    Rec2195_224* p = self->linkRecord;
    if (p == 0) return;
    s32 v = p->flags | 0x8000;
    p->flags = v;
    if (v & 0x10) {
        p->p60 = (BaseObject*)FindFirstObjectByIdMode4(self->world, (s32)p->p60, self);
        p->p64 = (BaseObject*)1;
    }
    if (p->flags & 0x20) {
        BaseObject* r = (BaseObject*)FindFirstObjectByIdMode4(self->world, (s32)p->p84, self);
        p->p84 = r;
        s32 x = (s32)r->parent;
        p->linkParent = x;
        p->p88 = FindCommonAncestor(self, (BaseObject*)x);
    }
    if (p->flags & 0x40) {
        p->p60 = (BaseObject*)FindFirstObjectByIdMode4(self->world, (s32)p->p60, self);
        p->p64 = (BaseObject*)FindFirstObjectByIdMode4(self->world, (s32)p->p64, self);
    }
}

// Applies the follow record's two fixed offsets to a pose: flag 1 multiplies the rotation m by the
// record's first rotation, flag 2 applies the record's second rotation to both m and the vector v.
// Does nothing with no link record.
void ApplyObjectFrameOffsetToPose(PlacedObject* self, Mat3* m, Vec4* v)
{
    Rec2195_224* p = self->linkRecord;
    if (p != 0) {
        Mat3 t;
        if ((p->flags & 1) && m != 0) {
            MulRotationRows(&t, *m, *(Mat3*)p);
            *m = t;
        }
        if (p->flags & 2) {
            if (m != 0) {
                MulRotationRowsX(&t, p->m[1], *m);
                *m = t;
            }
            if (v != 0) {
                Vu0::Q(t.r[0]) = Vu0::Rotate(p->m[1], Vu0::Q(*v));
                *v = t.r[0];
            }
        }
    }
}


// Applies the record's matrices (+0x224) to m: with its flag 1, the first one's transpose
// times m; with flag 2, the second one (MultiplyByTransposedMatrix3x3, which returns a 3x3
// matrix by value: retail's `daddu v0, a0`).
void RemoveObjectFrameOffsetFromPose(PlacedObject* self, Mat3* m)
{
    Mat3 t;
    Rec2195_224* p = self->linkRecord;
    if (p != 0) {
        if (p->flags & 1) {
            Mat3 u;
            Vu0::MulTransposed(u, *(Mat3*)p, *m);
            t = u;
            *m = t;
        }
        if (p->flags & 2) {
            t = MultiplyByTransposedMatrix3x3(*(Mat3*)&p->m[1], *m);
            *m = t;
        }
    }
}

ASM_FUNC(func_001290B8);

ASM_FUNC(func_001290E0);

// Gives the object its 0x14-byte animation start record (no key, mode 0, speed scale 1) if it has
// none, and gives it back.
AnimationStart* EnsureTimerRecord(PlacedObject* self)
{
    if (self->animationStart == 0) {
        AnimationStart* t = (AnimationStart*)AllocateZeroedFrontMemory(0x14);
        self->animationStart = t;
        t->key = -1;
        self->animationStart->mode = 0;
        self->animationStart->value = 0;
        self->animationStart->speedScale = 1.0f;
    }
    return self->animationStart;
}

// Sets the x/y scale from a percentage (stored as a fraction, x / 100).
void SetPlacedObjectScaleXY(PlacedObject* self, f32 x)
{
    self->xyScale = x * 0.01f;
}

// Gives the x/y scale as a percentage.
void GetPlacedObjectScaleXY(PlacedObject* self, f32* out)
{
    *out = self->xyScale * 100.0f;
}

// Sets the z scale from a percentage (stored as a fraction).
void SetPlacedObjectScaleZ(PlacedObject* self, f32 x)
{
    self->zScale = x * 0.01f;
}

// Gives the z scale as a percentage.
void GetPlacedObjectScaleZ(PlacedObject* self, f32* out)
{
    *out = self->zScale * 100.0f;
}

// Gives the object a range record from the world's pool, initialised and on the world's list at
// 0x1C00, if it has none; gives it back.
void* EnsureRangeRecord(PlacedObject* self)
{
    if (self->rangeRecord == 0) {
        void* o = PopZeroedFreeSlot(&self->world->pool1BF4);
        self->rangeRecord = (RangeRecord*)o;
        InitRangeRecord(o);
        AppendToList(&self->world->list1C00, self->rangeRecord);
    }
    return self->rangeRecord;
}

// With flag, makes sure the object has a range record; without, takes it out of the world's list
// and queues it on the deferred-release list.
void SetRangeRecordPresent(PlacedObject* self, s32 flag)
{
    if (flag != 0) {
        EnsureRangeRecord((PlacedObject*)self);
        return;
    }
    if (self->rangeRecord == 0) {
        return;
    }
    RemoveFromList(&self->world->list1C00, self->rangeRecord);
    AppendToList(&g_deferredReleaseListC, self->rangeRecord);
    self->rangeRecord = 0;
}

// Links the object's range record (made if needed) to the record for key.
void SetRangeRecordKey(void* self, s32 value)
{
    LinkRangeRecord((RangeRecord*)EnsureRangeRecord((PlacedObject*)self), value);
}

// Sets the range record's near range (made if needed).
void SetRangeRecordNear(void* self, f32 x)
{
    StoreRangeRecordNear((RangeRecord*)EnsureRangeRecord((PlacedObject*)self), x);
}

// Sets the range record's far range (made if needed).
void SetRangeRecordFar(PlacedObject* self, f32 x)
{
    StoreRangeRecordFar((RangeRecord*)EnsureRangeRecord(self), x);
}

// Sets the range record's inner distance (made if needed).
void SetRangeRecordInner(PlacedObject* self, f32 x)
{
    StoreRangeRecordInner((RangeRecord*)EnsureRangeRecord(self), x);
}

// Sets the range record's outer distance (made if needed).
void SetRangeRecordOuter(PlacedObject* self, f32 x)
{
    StoreRangeRecordOuter((RangeRecord*)EnsureRangeRecord(self), x);
}

// Sets the near and far ranges of the range record from an angle in degrees
// (ScaleRangeRecordByAngle).
void SetRangeRecordInnerAndOuter(PlacedObject* self, f32 x)
{
    ScaleRangeRecordByAngle((RangeRecord*)EnsureRangeRecord(self), x);
}

// Stores the range record's vector (made if needed).
void SetRangeRecordVector(void* self, void* src)
{
    StoreRangeRecordVector((RangeRecord*)EnsureRangeRecord((PlacedObject*)self), (Quad16*)src);
}

// Stores a code at 0xB0 of the range record (made if needed).
void SetRangeRecordCode(void* self, s32 value)
{
    ((RangeRecord*)EnsureRangeRecord((PlacedObject*)self))->textureObjectId = value;
}

// The object's range record or, when it has none, a shared default one (re-initialised each time).
RangeRecord* GetRangeRecord(PlacedObject* self)
{
    if (self->rangeRecord != 0) return self->rangeRecord;
    InitRangeRecord(&g_sharedRangeRecord);
    return &g_sharedRangeRecord;
}

void GetRangeRecordPresent(PlacedObject* self, s32* out)
{
    *out = self->rangeRecord != 0;
}

// Gives the key of the range record's link, or -1 when it has no record or link.
void GetRangeRecordKeyValue(PlacedObject* self, s32* out)
{
    RangeRecord* p = self->rangeRecord;
    if (p == 0) {
        goto fail;
    }
    {
        AnimRecord* n = p->link;
        if (n == 0) {
            goto fail;
        }
        *out = n->key;
        return;
    }
fail:
    *out = -1;
}

// Gives the range record's near range (the default record's when the object has none).
void GetRangeRecordNear(void* self, f32* out)
{
    RangeRecord* s = GetRangeRecord((PlacedObject*)self);
    *out = s->nearRange;
}

// Gives the range record's far range (default record when none).
void GetRangeRecordFar(void* self, f32* out)
{
    *out = GetRangeRecord((PlacedObject*)self)->farRange;
}

// Gives the range record's inner distance (default record when none).
void GetRangeRecordInner(void* self, f32* out)
{
    *out = GetRangeRecord((PlacedObject*)self)->innerDistance;
}

// Gives the range record's outer distance (default record when none).
void GetRangeRecordOuter(PlacedObject* self, f32* out)
{
    *out = GetRangeRecord(self)->outerDistance;
}

// Gives the angle in degrees the range record's near range and inner distance make: twice atan(near
// / inner), in *out.
void GetRangeRecordAngle(void* self, f32* out)
{
    RangeRecord* sub = GetRangeRecord((PlacedObject*)self);
    f32 value = ArctangentOfRatio(sub->nearRange / sub->innerDistance, 1.0f) * 57.2957763671875f;
    *out = value + value;
}

// Gives the range record's vector (default record when none).
void GetRangeRecordVector(void* self, Vec4* out)
{
    *out = GetRangeRecord((PlacedObject*)self)->v30;
}

// Gives the object's rotation as three Euler angles in degrees.
void GetRotationDegrees(PlacedObject* self, f32* out)
{
    Vec4 a[3];
    a[0] = self->rot.r[0];
    a[1] = self->rot.r[1];
    a[2] = self->rot.r[2];
    self->desc02()->m2A(self, a);
    MatrixToEulerAngles((Mat4*)a, (Vec3*)out);
    s32 n = 2;
    f32* p = out;
    do {
        n--;
        *p = *p * 57.295776f;
        p++;
    } while (n >= 0);
}

// Sets the object's rotation from three Euler angles in degrees (converted to radians) through the
// rotation set methods.
void SetRotationDegrees(PlacedObject* self, f32* src)
{
    EulerLocals l;
    f32* out = l.out;
    f32* dst = l.tmp;
    f32 k = 0.01745329424738884f;
    s32 i = 2;
    do {
        *dst = *src * k;
        i--;
        src++;
        dst++;
    } while (i >= 0);
    BuildEulerRotationMatrix(l.tmp, out);
    self->desc02()->m29(self, (Mat3*)out, 0);
    self->desc02()->m1E(self, (Mat3*)out);
}

// Creates the object's base attachment (an owner pose source) and inserts it, if it has none.
void EnsureBaseAttachment(PlacedObject* self)
{
    if (self->baseAttachment == 0) {
        Attachment* v = CreatePoseSource(self->world, self, (const T2195_Vt*)g_ownerPoseSourceMethods);
        self->baseAttachment = v;
        InsertAttachment(self, v);
    }
}

// Creates the object's aim attachment (an aim-switch pose source) and inserts it, if it has none.
void EnsureAimAttachment(PlacedObject* self)
{
    if (self->aimAttachment == 0) {
        AimAttachment* v = (AimAttachment*)CreatePoseSource(self->world, self, (const T2195_Vt*)g_aimSwitchPoseSourceMethods);
        self->aimAttachment = v;
        InsertAttachment(self, v);
    }
}

// Chooses which of the object's attachments drive it: the first one with a position mode, an
// orientation mode and a matrix mode set (ignoring mode 0), plus one per value slot. When the
// position or orientation attachment changes it clears the root tries and settles the new
// attachment's modes.
void ChooseActiveAttachments(PlacedObject* self)
{
    Attachment* s3 = 0;
    Attachment* s2 = 0;
    Attachment* s1 = 0;
    s32 i;
    if (self->indexedAttachments) FillMemory(self->indexedAttachments, 0, self->valueCount << 2);
    for (Attachment* n = (Attachment*)self->list1E0.head; n != 0; n = n->link.next) {
        if (s1 == 0) if (n->mode0 != -1) s1 = n;
        if (s2 == 0) if (n->mode1 != -1) s2 = n;
        if (s3 == 0) if (n->mode2 != -1) s3 = n;
        if (n->mode3 == -1) continue;
        if (n->vt == (const T2195_Vt*)g_trackPoseSourceMethods) {
            AnimationTrack* e = &((TrackFollowAttachment*)n)->player->anim->tracks[((TrackFollowAttachment*)n)->index];
            for (i = 0; i < e->morphCount; i++) {
                if (e->morph[i] != 0) {
                    if (self->indexedAttachments[i] == 0) self->indexedAttachments[i] = n;
                }
            }
        } else {
            for (i = 0; i < self->valueCount; i++) {
                if (self->indexedAttachments[i] == 0) self->indexedAttachments[i] = n;
            }
        }
    }
    if (s1 && s1->mode0 == 0) s1 = 0;
    if (s2 && s2->mode1 == 0) s2 = 0;
    if (s3 && s3->mode2 == 0) s3 = 0;
    if (self->indexedAttachments) {
        for (i = 0; i < self->valueCount; i++) {
            if (self->indexedAttachments[i] != 0) {
                if (((Attachment*)self->indexedAttachments[i])->mode3 == 0) self->indexedAttachments[i] = 0;
            }
        }
    }
    self->matrixAttachment = s3;
    if (s1 != self->positionAttachment || s2 != self->orientationAttachment) {
        ClearRootTries(self);
        if (s1 != self->positionAttachment) {
            self->positionAttachment = s1;
            if (s1) SettlePoseSourceModes(s1);
        }
        if (s2 != self->orientationAttachment) {
            self->orientationAttachment = s2;
            if (s2) SettlePoseSourceModes(s2);
        }
    }
}

// Inserts the attachment into the object's list, which is ordered by key (highest first), and
// notifies method 0x2B.
void InsertAttachment(PlacedObject* self, Attachment* src)
{
    ListFrame frame;
    Attachment* node = (Attachment*)self->list1E0.head;
    if (node != 0 && node->key > src->key) {
        node = node->link.next;
        while (node != 0 && node->key > src->key) {
            node = node->link.next;
        }
    }
    InsertBeforeInList(&self->list1E0, node, src);
    self->desc02()->m2B(self);
}

// Re-inserts the object's attachments into its list so they are ordered by key, largest first
// (equal keys stay in their old order); then calls the object's attachment-changed method (m2B).
void SortAttachments(PlacedObject* self)
{
    ListFrame it;
    Attachment* nodes[20];
    s32 n = 0;
    Attachment* node;
    ListWalkBegin::Of(&it, &self->list1E0);
    for (node = NextAttachment::Of(&it); node != 0; node = NextAttachment::Of(&it)) {
        nodes[n] = node;
        RemoveFromList((ObjectList*)&self->list1E0, node);
        n++;
    }
    while (--n >= 0) {
        Attachment* c = (Attachment*)self->list1E0.head;
        node = nodes[n];
        while (c != 0 && c->key > node->key) c = c->link.next;
        InsertBeforeInList(&self->list1E0, c, node);
    }
    self->desc02()->m2B(self);
    g_activeListFrames = (ListFrame*)it.prev;
}

// The world's animation player for the object, any when key is -1 or the one whose animation
// matches the id; 0 when none.
AnimationPlayer* FindObjectAnimationPlayer(PlacedObject* self, s32 key)
{
    ListFrame frame;
    AnimationPlayer* node = (AnimationPlayer*)self->world->animationPlayers;
    while (node != 0) {
        if (node->object == self) {
            if (key == -1) return node;
            if (MatchesObjectId(node->anim, key) != 0) return node;
        }
        node = node->next;
    }
    return 0;
}

// The state walker in the world's list 0x1B94 for the object, any when key is -1 or the one whose
// owner matches the id; 0 when none.
StateWalker* FindObjectHandle(PlacedObject* self, s32 key)
{
    ListFrame frame;
    StateWalker* n = (StateWalker*)self->world->list1B94.head;

    while (n != 0) {
        if (n->object == self) {
            if (key == -1) return n;
            if (MatchesObjectId((BaseObject*)n->owner, key) != 0) return n;
        }
        n = n->worldNext;
    }
    return 0;
}

// Walks up from the object through its parents to the first one with a track pose source on its
// position or orientation, and gives back that source's animation player; 0 if none.
void* FindTrackPlayer(PlacedObject* node)
{
    while (node != 0) {
        Attachment* a = node->positionAttachment;
        if (a != 0 && a->vt == (const T2195_Vt*)g_trackPoseSourceMethods) {
            return ((TrackFollowAttachment*)a)->player;
        }
        a = node->orientationAttachment;
        if (a != 0 && a->vt == (const T2195_Vt*)g_trackPoseSourceMethods) {
            return ((TrackFollowAttachment*)a)->player;
        }
        node = (PlacedObject*)node->parent;
    }
    return 0;
}

// Creates an identity-matrix pose source for the object with the given sort key, inserts it into
// the object's attachments and gives it back in *out.
void AddMatrixAttachment(PlacedObject* self, s32 key, Attachment** out)
{
    Attachment* n;

    if (self != 0) {
        n = CreatePoseSource(self->world, self, (const T2195_Vt*)(((u8*)g_identityPoseSourceMethods)));
        n->key = key;
        InsertAttachment(self, n);
        *out = n;
    }
}

// True when the object's velocity and spin are negligible and so are those of all its placed-object
// children.
s32 IsObjectTreeAtRest(UpdatedObject* self)
{
    UpdatedObject* n;
    if (IsVelocityNegligible(&((PlacedObject*)self)->v150) == 0) return 0;
    if (IsSpinNegligible(&((PlacedObject*)self)->v160) != 0) goto body;
    return 0;
body:
    n = (UpdatedObject*)self->firstChild;
    while (n != 0) {
        if ((n->vtable->f8 & 1) != 0) {
            if (IsObjectTreeAtRest(n) == 0) return 0;
        }
        n = (UpdatedObject*)n->nextSibling;
    }
    return 1;
}

// Resets the try count of the object's root, if it has one.
void ClearRootTries(PlacedObject* self)
{
    if (self->root != 0) self->root->tries = 0;
}

// Sets the position spring to the default one (D_00260E70) with every component multiplied by
// scale.
void SetScaledPositionSpring(PlacedObject* self, f32 scale)
{
    ScaledSpringFrame f;
    u8* p = (u8*)g_defaultPositionSpring;
    StoreFloatAsQuadword(&f.a, scale);
    U128 av = f.a;
    CopyQuadword((u128*)&f.b, p);
    (void)StoreQuadword((u128*)&f.r, ScaleQuadword(av, f.b));
    SetPositionSpring(self, (Quad16*)&f.r);
}

// Stores the position spring; its own 16-byte copy on first use, as SetPositionRamp.
void SetPositionSpring(PlacedObject* self, Quad16* value)
{
    if (self->p20C == (u8*)g_defaultPositionSpring)
        self->p20C = (u8*)AllocateFrontMemory(16);
    *(Quad16*)self->p20C = *value;
}

// Sets the velocity spring to the default one (D_00260E80) with every component multiplied by
// scale.
void SetScaledVelocitySpring(PlacedObject* self, f32 scale)
{
    ScaledSpringFrame f;
    u8* p = (u8*)g_defaultVelocitySpring;
    StoreFloatAsQuadword(&f.a, scale);
    U128 av = f.a;
    CopyQuadword((u128*)&f.b, p);
    (void)StoreQuadword((u128*)&f.r, ScaleQuadword(av, f.b));
    SetVelocitySpring(self, (Quad16*)&f.r);
}

// Stores the velocity spring (own copy on first use).
void SetVelocitySpring(PlacedObject* self, Quad16* src)
{
    if (self->p210 == (u8*)g_defaultVelocitySpring) self->p210 = (u8*)AllocateFrontMemory(16);
    *(Quad16*)self->p210 = *src;
}

// Sets the rotation spring to the default one (D_00260E90) with every component multiplied by
// scale.
void SetScaledRotationSpring(PlacedObject* self, f32 scale)
{
    ScaledSpringFrame f;
    u8* p = (u8*)g_defaultRotationSpring;
    StoreFloatAsQuadword(&f.a, scale);
    U128 av = f.a;
    CopyQuadword((u128*)&f.b, p);
    (void)StoreQuadword((u128*)&f.r, ScaleQuadword(av, f.b));
    SetRotationSpring(self, (Quad16*)&f.r);
}

// Stores the rotation spring (own copy on first use).
void SetRotationSpring(PlacedObject* self, Quad16* src)
{
    if (self->p214 == (u8*)g_defaultRotationSpring) self->p214 = (u8*)AllocateFrontMemory(16);
    *(Quad16*)self->p214 = *src;
}

// Sets the spin spring to the default one (D_00260EA0) with every component multiplied by scale.
void SetScaledSpinSpring(PlacedObject* self, f32 scale)
{
    ScaledSpringFrame f;
    u8* p = (u8*)g_defaultSpinSpring;
    StoreFloatAsQuadword(&f.a, scale);
    U128 av = f.a;
    CopyQuadword((u128*)&f.b, p);
    (void)StoreQuadword((u128*)&f.r, ScaleQuadword(av, f.b));
    SetSpinSpring(self, (Quad16*)&f.r);
}

// Stores the spin spring (own copy on first use).
void SetSpinSpring(PlacedObject* self, Quad16* src)
{
    if (self->p218 == (u8*)g_defaultSpinSpring) self->p218 = (u8*)AllocateFrontMemory(16);
    *(Quad16*)self->p218 = *src;
}

// Sets the position ramp to the default one (D_00260EB0) with its first, second and fourth values
// multiplied by scale.
void SetScaledPositionRamp(PlacedObject* self, f32 scale)
{
    Vec4U tmp;
    tmp.x = g_defaultPositionRamp[0] * scale;
    tmp.y = g_defaultPositionRamp[1] * scale;
    tmp.z = g_defaultPositionRamp[2];
    tmp.w = g_defaultPositionRamp[3] * scale;
    SetPositionRamp(self, (PackedRampProfile*)&tmp);
}

// Recomputes the position ramp's fourth value as scale * (x - y) / z of the ramp and stores it.
void SetPositionRampAccelScale(PlacedObject* self, f32 scale)
{
    PackedRampProfile tmp = *(PackedRampProfile*)self->p21C;
    tmp.w = scale * (tmp.x - tmp.y) / tmp.z;
    SetPositionRamp(self, &tmp);
}

// Stores the ramp profile used for the object's position; the object gets its own 16-byte copy the
// first time (it points to a shared default until then).
void SetPositionRamp(PlacedObject* self, PackedRampProfile* src)
{
    if (self->p21C == (u8*)g_defaultPositionRamp) {
        self->p21C = (u8*)AllocateFrontMemory(16);
    }
    *(PackedRampProfile*)self->p21C = *src;
}

// Sets the rotation ramp to the default one (D_00260EC0) with its first, second and fourth values
// multiplied by scale.
void SetScaledRotationRamp(void* self, f32 s)
{
    f32 v[4];
    f32* m = (f32*)g_defaultRotationRamp;
    v[0] = m[0] * s;
    v[1] = m[1] * s;
    v[2] = m[2];
    v[3] = m[3] * s;
    SetRotationRamp((PlacedObject*)self, (PackedRampProfile*)v);
}

// Recomputes the rotation ramp's fourth value as scale * (x - y) / z of the ramp and stores it.
void SetRotationRampAccelScale(PlacedObject* self, f32 scale)
{
    PackedRampProfile tmp;
    tmp = *(PackedRampProfile*)self->p220;
    tmp.w = scale * (tmp.x - tmp.y) / tmp.z;
    SetRotationRamp(self, &tmp);
}

// Stores the ramp profile used for the object's rotation; own 16-byte copy on first use, as
// SetPositionRamp.
void SetRotationRamp(PlacedObject* self, PackedRampProfile* src)
{
    if (self->p220 == (u8*)g_defaultRotationRamp) {
        self->p220 = (u8*)AllocateFrontMemory(0x10);
    }
    *(PackedRampProfile*)self->p220 = *src;
}

// Stores the default position mode (byte at 0x2C9).
void SetDefaultPositionMode(void* self, s8 value) { ((PlacedObject*)self)->b2C9 = value; }

// Stores the default orientation mode (byte at 0x2CA).
void SetDefaultOrientationMode(void* self, s8 value) { ((PlacedObject*)self)->b2CA = value; }

// Sets the base attachment's position mode to 1 when value is non-zero and to -1 otherwise.
void SetPositionSourceEnabled(void* self, s32 value) { SetPositionSourceMode((PlacedObject*)self, value ? 1 : -1); }

// Sets the group activity mode to 1 when a1 is non-zero and to 0 otherwise.
void SetGroupActivityModeEnabled(void* self, s32 a1)
{
    SetGroupActivityMode((PlacedObject*)self, a1 != 0);
}

// Stores the low two bits of value in flag bits 40 and 41 of the object.
void SetGroupActivityMode(PlacedObject* self, u32 value)
{
    self->flags = (self->flags & ~(3ull << 40)) | ((u64)(value & 3) << 40);
}

// Gives the two-bit group activity mode from flag bits 40 and 41.
void GetGroupActivityMode(PlacedObject* self, u32* out)
{
    u32 value = (u32)(self->flags >> 40);
    value &= 3;
    *out = value;
}

// Sets the base attachment's position mode (creating it if needed) and notifies method 0x2B.
void SetPositionSourceMode(PlacedObject* self, s32 value)
{
    EnsureBaseAttachment(self);
    self->baseAttachment->mode0 = value;
    self->desc02()->m2B(self);
}

// Sets the base attachment's orientation mode to 1 when a1 is non-zero and to -1 otherwise.
void SetOrientationSourceEnabled(void* self, s32 a1)
{
    SetOrientationSourceMode((PlacedObject*)self, a1 != 0 ? 1 : -1);
}

// Sets the base attachment's orientation mode (creating it if needed) and notifies method 0x2B.
void SetOrientationSourceMode(PlacedObject* self, s32 value)
{
    EnsureBaseAttachment(self);
    self->baseAttachment->mode1 = value;
    self->desc02()->m2B(self);
}

// Sets the base attachment's key (creating it if needed) and sorts the object's attachments again.
void SetBaseAttachmentSortKey(PlacedObject* self, s32 value)
{
    EnsureBaseAttachment(self);
    self->baseAttachment->key = value;
    SortAttachments(self);
}

// Sets the aim attachment's orientation mode (3 is stored as 9) and notifies method 0x2B.
void SetAimOrientationMode(PlacedObject* self, s32 value)
{
    EnsureAimAttachment(self);
    if (value == 3) value = 9;
    self->aimAttachment->mode1 = value;
    self->desc02()->m2B(self);
}

// Stores the aim attachment's range (creating the attachment if needed).
void SetAimRange(PlacedObject* self, f32 f)
{
    EnsureAimAttachment(self);
    self->aimAttachment->aimRange = f;
}

// Gives the aim attachment's range, 0 when the object has none.
void GetAimRange(PlacedObject* self, f32* out)
{
    f32 r = 0.0f;
    if (self->aimAttachment != 0) r = self->aimAttachment->aimRange;
    *out = r;
}

// Stores the aim attachment's yaw curve vector (creating the attachment if needed).
void SetAimYawCurve(PlacedObject* self, Vec4* src)
{
    EnsureAimAttachment(self);
    self->aimAttachment->v50 = *src;
}

// Gives the aim attachment's yaw curve vector, or zero when the object has none.
void GetAimYawCurve(PlacedObject* self, Quad16* out)
{
    Quad16* src = self->aimAttachment != 0 ? (Quad16*)&self->aimAttachment->v50 : (Quad16*)g_zeroQuad;
    *out = *src;
}

// Stores the aim attachment's yaw limits (creating the attachment if needed).
void SetAimYawLimits(PlacedObject* self, Pk8_2195* src)
{
    EnsureAimAttachment(self);
    self->aimAttachment->p60 = *src;
}

// Gives the aim attachment's yaw limits, or the default unit range when the object has none.
void GetAimYawLimits(PlacedObject* self, U64P* out)
{
    U64P* src = self->aimAttachment != 0 ? (U64P*)&self->aimAttachment->p60 : (U64P*)g_unitRange;
    *out = *src;
}

// Stores the aim attachment's pitch curve vector (creating the attachment if needed).
void SetAimPitchCurve(PlacedObject* self, Vec4* src)
{
    EnsureAimAttachment(self);
    self->aimAttachment->v70 = *src;
}

// Gives the aim attachment's pitch curve vector, or zero when the object has none.
void GetAimPitchCurve(PlacedObject* self, Quad16* out)
{
    Quad16* src = self->aimAttachment != 0 ? (Quad16*)&self->aimAttachment->v70 : (Quad16*)g_zeroQuad;
    *out = *src;
}

// Stores the aim attachment's pitch limits (creating the attachment if needed).
void SetAimPitchLimits(PlacedObject* self, Pk8_2195* src)
{
    EnsureAimAttachment(self);
    self->aimAttachment->p80 = *src;
}

// Gives the aim attachment's pitch limits, or the default unit range when the object has none.
void GetAimPitchLimits(PlacedObject* self, U64P* out)
{
    U64P* src = self->aimAttachment != 0 ? (U64P*)&self->aimAttachment->p80 : (U64P*)g_unitRange;
    *out = *src;
}

// Stores the aim attachment's near key.
void SetAimNearKey(PlacedObject* self, s32 v)
{
    EnsureAimAttachment(self);
    self->aimAttachment->nearKey = v;
}

// Gives the aim attachment's near key, 0 when the object has none.
void GetAimNearKey(PlacedObject* self, s32* out)
{
    s32 r = 0;
    if (self->aimAttachment != 0) r = self->aimAttachment->nearKey;
    *out = r;
}

// Stores the aim attachment's far key.
void SetAimFarKey(PlacedObject* self, s32 value)
{
    EnsureAimAttachment(self);
    self->aimAttachment->farKey = value;
}

// Gives the aim attachment's far key, 0 when the object has none.
void GetAimFarKey(PlacedObject* self, s32* out)
{
    s32 v = 0;
    if (self->aimAttachment != 0) {
        v = self->aimAttachment->farKey;
    }
    *out = v;
}

// Stores the id of the aim attachment's target (which PostLoadPlacedObject resolves).
void SetAimTargetId(PlacedObject* self, s32 value)
{
    EnsureAimAttachment(self);
    self->aimAttachment->targetId = value;
}

// Gives the id of the aim attachment's target, -1 when the object has none.
void GetAimTargetId(PlacedObject* self, s32* out)
{
    s32 v = -1;
    if (self->aimAttachment != 0) {
        v = self->aimAttachment->targetId;
    }
    *out = v;
}

// Makes b the aim attachment's target, with the default offset.
void SetAimTarget(PlacedObject* self, void* b)
{
    AssignAimTarget(self->aimAttachment, b, (Vec4*)&g_zeroVector);
}

// Gives the object the aim attachment currently targets (resolved from its id), in *out.
void GetAimTarget(PlacedObject* self, void** out)
{
    *out = ResolveAimTarget(self->aimAttachment);
}

// Clears the aim attachment's hold flag.
void ClearAimHold(PlacedObject* self)
{
    self->aimAttachment->hold = 0;
}

// Sets the aim attachment's hold flag.
void SetAimHold(PlacedObject* self)
{
    self->aimAttachment->hold = 1;
}

// Creates the object's own value attachment on first use (and inserts it in the attachment list),
// then sets its mode and two values and notifies method 0x2B.
void SetValueAttachment(PlacedObject* self, s32 a1, f32 x, f32 y)
{
    if (self->ownValueAttachment == 0) {
        TiltValueAttachment* r = (TiltValueAttachment*)CreatePoseSource(self->world, self, (const T2195_Vt*)(((u8*)g_aimPoseSourceBases)));
        self->ownValueAttachment = r;
        InsertAttachment(self, r);
    }
    self->ownValueAttachment->mode1 = a1;
    self->ownValueAttachment->tiltScale = x;
    self->ownValueAttachment->sampleTime = y;
    self->desc02()->m2B(self);
}

// The first object of id 0x22A in class 0x102 of the world, or a new class 0x75 object with that
// id.
Class75Object* FindOrCreateClass75Object(PlacedObject* self)
{
    void* r = FindFirstObjectById(self->world, 0x102, 0x22A, self);
    if (r != 0) {
        return (Class75Object*)r;
    }
    return (Class75Object*)CreateTypedRecord(0x75, self->world, self, 0x22A, -1);
}

// Sets the count of the object's class 0x75 record (made if needed), unless value is -1.
void SetClass75ObjectCount(PlacedObject* self, s32 value)
{
    Class75Object* o = FindOrCreateClass75Object(self);
    if (value != -1) {
        o->count = value;
    }
}

// Sets the scale of the object's class 0x75 record (made if needed).
void SetClass75ObjectScale(void* self, f32 value)
{
    FindOrCreateClass75Object((PlacedObject*)self)->scale = value;
}

// Sets the field at 0x90 of the object's class 0x75 record (made if needed).
void SetClass75ObjectField90(void* self, s32 value)
{
    Class75Object* ctx = FindOrCreateClass75Object((PlacedObject*)self);
    ctx->enabled = value;
}

// Sets the scroll scale (a, b) of every scroll animator (element kind 6) of the object.
void SetElementsScrollScale(PlacedObject* self, f32 a, f32 b)
{
    for (s32 i = 0; i < self->elemCount; i++) {
        PlacedObjectElement* p = self->elems[i];
        if (p->kind == 6) SetScrollScale((ScrollAnimator*)p, a, b);
    }
}

// Sets the crossfade ratio of every crossfade animator (element kind 5) of the object and,
// recursively, of its placed-object children.
void SetCrossfadeRatioDeep(PlacedObject* self, f32 value)
{
    ListFrame frame;
    for (s32 i = 0; i < self->elemCount; i++) {
        PlacedObjectElement* p = self->elems[i];
        if (p->kind == 5) SetCrossfadeRatio((CrossfadeAnimator*)p, value);
    }
    for (PlacedObject* child = (PlacedObject*)self->children.head; child; child = (PlacedObject*)child->next) {
        if (child->desc->flags & 1) SetCrossfadeRatioDeep(child, value);
    }
}

// Gives the object a sound record with default parameters if it has none.
void EnsureSoundRecord(PlacedObject* self)
{
    if (self->soundRecord == 0) InitSoundParams(&self->soundRecord);
}

// Stores the sound id of the object's sound record (made if needed) without restarting the sound.
void SetSoundRecordId(PlacedObject* self, s32 value)
{
    EnsureSoundRecord(self);
    self->soundRecord->soundId = value;
}

// Stops the object's sound, changes the sound record's id to value and starts the sound again with
// the record's ranges, volume and pitch.
void RestartSoundWithId(PlacedObject* self, s32 value)
{
    EnsureSoundRecord(self);
    StopSoundRecord((PlayingSound*)self->soundRecord->sound, 0);
    self->soundRecord->soundId = value;
    SoundRecord* p = self->soundRecord;
    StartSoundEffect(p->soundId, (PlayingSound**)&p->sound, self, 0, p->outerRange, p->innerRange, p->baseVolume, p->pitch, p->startParam, (f32*)&p->b14, 0);
}

// Gives the sound's id, -1 when the object has no sound record.
void GetSoundRecordId(PlacedObject* self, s32* out)
{
    s32 v = -1;
    if (self->soundRecord != 0) v = self->soundRecord->soundId;
    *out = v;
}

// Stores the sound's outer range.
void SetSoundOuterRange(PlacedObject* self, f32 value)
{
    EnsureSoundRecord(self);
    self->soundRecord->outerRange = value;
}

// Gives the sound's outer range, 3000 when the object has no sound record.
void GetSoundOuterRange(PlacedObject* self, f32* out)
{
    SoundRecord* s = self->soundRecord;
    f32 v = 3000.0f;
    if (s != 0) v = s->outerRange;
    *out = v;
}

// Stores the sound's inner range.
void SetSoundInnerRange(PlacedObject* self, f32 value)
{
    EnsureSoundRecord(self);
    self->soundRecord->innerRange = value;
}

// Stores the pair of values at 0x14 of the object's sound record (made if needed).
void SetSoundRecordPair(PlacedObject* self, U64P* src)
{
    EnsureSoundRecord(self);
    self->soundRecord->b14 = *src;
}

// Gives the sound's inner range, 300 when the object has no sound record.
void GetSoundInnerRange(PlacedObject* self, f32* out)
{
    SoundRecord* s = self->soundRecord;
    f32 v = 300.0f;
    if (s != 0) v = s->innerRange;
    *out = v;
}

// Stores the sound's base volume.
void SetSoundRecordScale(PlacedObject* self, f32 f)
{
    EnsureSoundRecord(self);
    self->soundRecord->baseVolume = f;
}

// Stores the sound's start parameter.
void SetSoundStartParam(PlacedObject* self, f32 value)
{
    EnsureSoundRecord(self);
    self->soundRecord->startParam = value;
}

// Gives the sound's start parameter, 0 when the object has no sound record.
void GetSoundStartParam(PlacedObject* self, f32* out)
{
    f32 r = 0.0f;
    if (self->soundRecord != 0) {
        r = self->soundRecord->startParam;
    }
    *out = r;
}

// Changes the volume of the object's sound while it is playing.
void SetPlayingSoundVolume(PlacedObject* self, f32 volume)
{
    SoundRecord* part = self->soundRecord;
    if (part != 0) {
        void* p = part->sound;
        if (p != 0) {
            SetSoundRecordVolume((PlayingSound*)p, volume);
        }
    }
}

// Gives the sound's base volume, 1 when the object has no sound record.
void GetSoundRecordScale(PlacedObject* self, f32* out)
{
    f32 v = 1.0f;
    if (self->soundRecord != 0) {
        v = self->soundRecord->baseVolume;
    }
    *out = v;
}

// Stores the sound's start pitch.
void SetSoundStartPitch(PlacedObject* self, f32 f)
{
    EnsureSoundRecord(self);
    self->soundRecord->pitch = f;
}

// Changes the pitch of the object's sound while it is playing.
void SetPlayingSoundPitch(PlacedObject* self, f32 pitch)
{
    SoundRecord* in = self->soundRecord;
    if (in != 0) {
        if (in->sound != 0) SetSoundRecordPitch((PlayingSound*)in->sound, pitch);
    }
}

// Gives the sound's start pitch, 0 when the object has no sound record.
void GetSoundStartPitch(PlacedObject* self, f32* out)
{
    f32 r = 0.0f;
    if (self->soundRecord != 0) {
        r = self->soundRecord->pitch;
    }
    *out = r;
}

// Gives the pair at 0x14 of the sound record, or (-1, -1) when the object has none.
void GetSoundRecordPair(PlacedObject* self, U64P* out)
{
    SoundRecord* s = self->soundRecord;
    if (s != 0) {
        *out = s->b14;
    } else {
        f32* f = (f32*)out;
        f[0] = -1.0f;
        f[1] = -1.0f;
    }
}

// Sets the object's sound record (sound id, outer and inner range, base volume and a 64-bit value),
// stops any sound that is playing and starts it again with the new values.
void StartSoundWithParams(PlacedObject* self, s32 value, U64P* src, f32 x, f32 y, f32 z)
{
    EnsureSoundRecord(self);
    self->soundRecord->soundId = value;
    self->soundRecord->outerRange = x;
    self->soundRecord->innerRange = y;
    self->soundRecord->baseVolume = z;
    self->soundRecord->b14 = *src;
    StopSoundRecord((PlayingSound*)self->soundRecord->sound, 0);
    SoundRecord* p = self->soundRecord;
    StartSoundEffect(p->soundId, (PlayingSound**)&p->sound, self, 0, p->outerRange, p->innerRange, p->baseVolume, p->pitch, p->startParam, (f32*)&p->b14, 0);
}

// Stops the object's sound if it has a sound record.
void StopPlayingSound(PlacedObject* self)
{
    SoundRecord* inner = self->soundRecord;
    if (inner != 0) StopSoundRecord((PlayingSound*)inner->sound, 0);
}

// Gives the object a 64-byte colour record, copied from the default record with no preset, if it
// has none.
void EnsureColorRecord(void* ptr)
{
    PlacedObject* self = (PlacedObject*)ptr;
    if (!self->colorRecord) {
        self->colorRecord = (ColorRecord*)AllocateFrontMemory(64);
        *self->colorRecord = g_defaultColorRecord[0];
        self->colorRecord->preset = -1;
    }
}

// Sets the colour record's preset and, unless it is -1, loads the record from that preset.
void SetColorPreset(PlacedObject* self, s32 a1)
{
    EnsureColorRecord(self);
    self->colorRecord->preset = a1;
    ColorRecord* e = self->colorRecord;
    s32 k = e->preset;
    if (k != -1) *e = g_colorPresets[k];
}

// Gives the colour record's preset, -1 when the object has no record.
void GetColorPreset(PlacedObject* self, s32* out) { *out = self->colorRecord ? *(s32*)self->colorRecord : -1; }

// Stores the colour record's first colour (made if needed).
void SetColorRecordFirstColor(PlacedObject* self, Quad16* input)
{
    EnsureColorRecord(self);
    *(Quad16*)&self->colorRecord->c10 = *input;
}

// Gives the colour record's first colour (a default vector when none).
void GetColorRecordFirstColor(PlacedObject* self, Quad16* out)
{
    u8* src = self->colorRecord ? (u8*)&self->colorRecord->c10 : (u8*)&g_zeroVector;
    *out = *(Quad16*)src;
}

// Stores the colour record's second colour (made if needed).
void SetColorRecordSecondColor(PlacedObject* self, Quad16* input)
{
    EnsureColorRecord(self);
    *(Quad16*)&self->colorRecord->c20 = *input;
}

// Gives the colour record's second colour (a default vector when none).
void GetColorRecordSecondColor(PlacedObject* self, Quad16* out)
{
    u8* src = self->colorRecord ? (u8*)&self->colorRecord->c20 : (u8*)&g_zeroVector;
    *out = *(Quad16*)src;
}

// Stores the colour record's factor (made if needed).
void SetColorRecordFactor(PlacedObject* self, f32 value)
{
    EnsureColorRecord(self);
    self->colorRecord->factor = value;
}

// Gives the colour record's factor, 0 when the object has no record.
void GetColorRecordFactor(PlacedObject* self, f32* out)
{
    f32 v = 0.0f;
    ColorRecord* p = self->colorRecord;
    if (p != 0) v = p->factor;
    *out = v;
}

// Sets the first three tint bytes to v.
void SetTintRgb(PlacedObject* self, s32 v)
{
    self->tint[2] = v;
    self->tint[1] = v;
    self->tint[0] = v;
}

void GetTintRgb(PlacedObject* self, s32* out)
{
    *out = self->tint[0];
}

void SetTintByte0(PlacedObject* self, s32 v)
{
    self->tint[0] = v;
}

void GetTintByte0(PlacedObject* self, s32* out)
{
    *out = self->tint[0];
}

void SetTintByte1(PlacedObject* self, u8 value) { self->tint[1] = value; }

void GetTintByte1(PlacedObject* self, s32* out)
{
    *out = self->tint[1];
}

void SetTintByte2(PlacedObject* self, s32 v)
{
    self->tint[2] = v;
}

void GetTintByte2(PlacedObject* self, s32* out)
{
    *out = self->tint[2];
}

void SetTintByte3(PlacedObject* self, s32 value)
{
    self->tint[3] = value;
}

void GetTintByte3(PlacedObject* self, s32* out)
{
    *out = self->tint[3];
}

void SetTintByte4(PlacedObject* self, u8 v)
{
    self->tintByte4 = v;
}

void GetTintByte4(PlacedObject* self, s32* out)
{
    *out = self->tintByte4;
}

s32 TestOtherFlagged(PlacedObject* self, BaseObject* a1)
{
    return a1->f0C != 0;
}

// Selects the baked per-key value row whose key equals key (-1 switches the values off) on the
// object's keyed-value attachment, creating and inserting that attachment on first use.
void SelectValueEntryByKey(PlacedObject* self, s32 key)
{
    s32 callVt = 0;
    s32 i;
    OwnerPointerAttachment* st;

    if (key == -1) {
        st = self->keyedValueAttachment;
        if (st != 0) {
            callVt = SetMode3::Of(st, -1);
        }
    } else {
        for (i = 0; i < self->keyedValueCount; i++) {
            if (((KeyedValues*)self->keyedValues)[i].key == key) {
                break;
            }
        }
        if (i < self->keyedValueCount) {
            if (self->keyedValueAttachment == 0) {
                self->keyedValueAttachment = (OwnerPointerAttachment*)CreatePoseSource(self->world, self, (const T2195_Vt*)(((u8*)g_linkedPoseSourceMethods)));
                InsertAttachment(self, self->keyedValueAttachment);
            }
            callVt = SetMode3::Of(self->keyedValueAttachment, 3);
            self->keyedValueAttachment->count = &self->valueCount;
            self->keyedValueAttachment->values = ((KeyedValues*)self->keyedValues)[i].values;
        }
    }
    if (callVt != 0) {
        self->desc02()->m2B(self);
    }
}

// Sets or clears flag bit 36 (tracked by the camera) and, if the object is attached, adds it to or
// removes it from the camera's object list. Does nothing when the flag already has the requested
// value.
void SetObjectCameraTracked(PlacedObject* self, s32 flag)
{
    u64 want = flag != 0;
    if (want != (((self->flags >> 36) ^ 1) & 1)) {
        return;
    }
    u64 bit = (u64)(flag & 1) << 36;
    self->flags = (self->flags & 0xFFFFFFEFFFFFFFFFULL) | bit;
    if (IsObjectAttached(self) == 0) {
        return;
    }
    if (flag != 0) {
        AddCameraObject(g_camera, self);
    } else {
        RemoveCameraObject(g_camera, self);
    }
}

// Sets the frame-step clock flag; on an attached root object it is taken off the tree and put back
// on around the change (methods 3 and 2).
void SetPlacedObjectFrameStepClock(PlacedObject* self, s32 flag)
{
    if ((0 < (u32)flag) != (self->frameStepClock == 0)) {
        goto done;
    }
    if (IsObjectAttached(self) == 0) {
        goto store;
    }
    if (self->parent != 0) {
        goto store;
    }
    self->desc->m03(self);
    self->frameStepClock = flag;
    self->desc->m02(self);
    goto done;
store:
    self->frameStepClock = flag;
done:
    return;
}

// Sets or clears flag bit 32 of the object.
void SetPlacedObjectSpecialFlag(PlacedObject* ctx, s32 on)
{
    if (on != 0) {
        ctx->flags |= (u64)1 << 32;
    } else {
        ctx->flags &= ~((u64)1 << 32);
    }
}

// Gives flag bit 32 of the object as 0 or 1.
void GetPlacedObjectSpecialFlag(PlacedObject* ctx, s32* out)
{
    if ((ctx->flags & ((u64)1 << 32)) != 0) {
        *out = 1;
    } else {
        *out = 0;
    }
}

// Sets the two objects the follow record follows, one for position and one for rotation (0xC flags;
// the parent when one equals it), allocating the record if needed. The object's local pose is then
// recomputed in the new frames, keeping its world pose.
void SetFollowObjects(PlacedObject* self, void* a1, void* a2)
{
    void* t = self->parent;
    if (a1 == t || a2 == t || a1 == a2) {
        if (a1 != 0 || a2 != 0) {
            if (self->linkRecord == 0) {
                self->linkRecord = (Rec2195_224*)AllocateZeroedFrontMemory(0xC0);
            }
        }
        Rec2195_224* p = self->linkRecord;
        if (a1 != self->parent) {
            p->p60 = (BaseObject*)a1;
            p->flags = p->flags | 4;
        } else {
            p->flags = p->flags & 4;
        }
        if (a2 != self->parent) {
            p->p60 = (BaseObject*)a2;
            p->flags = p->flags | 8;
        } else {
            p->flags = p->flags & 8;
        }
        TransformPointBetweenFrames(0, (PlacedObject*)a1, &self->v140, &self->pos);
        TransformRotationBetweenFrames(0, (PlacedObject*)a2, &self->m110, &self->rot);
    }
}

LINKER_REMNANT(func_0012B6A0);

// Initialises an object that checksums the game's code: the range from 0x100018 to the end, an
// initial CRC of 0xFFFFFFFF and the 256-entry CRC-32 table for the polynomial 0xEDB88320.
void InitCodeChecksum(CodeChecksum* self)
{
    u32 c;
    InitPlacedObject(self);
    self->start = 0x100018;
    self->end = g_codeChecksumEnd;
    self->crc = 0xFFFFFFFF;
    for (s32 i = 0; i < 256; i++) {
        c = (u32)i;
        s32 k = 7;
        do {
            if (c & 1) {
                c = (c >> 1) ^ 0xEDB88320;
            } else {
                c >>= 1;
            }
        } while (--k >= 0);
        self->table[i] = c;
    }
}

// Per-frame step of a CRC-32 over a block of memory, table driven: 64 words per call, until none
// remain. If the final CRC is non-zero it sets a mismatch flag and sends script event 2.
void UpdateCodeChecksum(CodeChecksum* self, f32 dt)
{
    if (self->remaining != 0) {
        s32 n = self->remaining;
        u32* p = self->cursor;
        u32 crc = self->crc;
        u8* tbl = (u8*)self->table;
        s32 i = 0;
        if (n > 0) {
            do {
                u32 w = *p;
                i++;
                n -= 4;
                crc = *(u32*)(tbl + (((crc ^ w) & 0xFF) << 2)) ^ (crc >> 8);
                crc = *(u32*)(tbl + (((crc ^ (w >> 8)) & 0xFF) << 2)) ^ (crc >> 8);
                crc = *(u32*)(tbl + (((crc ^ (w >> 16)) & 0xFF) << 2)) ^ (crc >> 8);
                crc = *(u32*)(tbl + (((crc ^ (w >> 24)) & 0xFF) << 2)) ^ (crc >> 8);
                p++;
                if (i >= 64) break;
            } while (n > 0);
        }
        self->cursor = p;
        self->crc = crc;
        self->remaining = n;
        if (n == 0 && crc != 0) {
            g_checksumMismatch[0] = 1;
            TriggerScriptEvent(self, 2, 0, 0);
        }
    }
}

// Empty: the module has no set-up of its own.
void InitPlacedObjectModule(void) {}

// Initialises an animation: the link offset of its property list (0x3C) and its kinematic value at
// 1 (velocity and acceleration 0), limits 0 and 1 and output 1.
void InitAnimation(Animation* self)
{
    InitObject(self);
    SetListLinkOffset((ObjectList*)&self->props6C, 0x3C);
    MotionState* k = &self->kin;
    k->pos = 1.0f;
    k->vel = 0.0f;
    k->acc = 0.0f;
    self->lo = 0.0f;
    self->hi = 1.0f;
    self->out = 1.0f;
}

// Reads an animation from the stream: id, length (16-bit, 1/60 s ticks), the target ids, then each
// track's target and flag bits that say which position, rotation, scale and weight curves it has.
// Each curve is created by its type byte and reads its own keys.
void LoadAnimation(Animation* self, Stream83* other)
{
    s32 k;
    AnimationTrack* sel = 0;
    AnimationTrack* e;
    PositionCurve* qp;
    RotationCurve* qr;
    ScaleCurve* qs;
    WeightCurve* qw;
    s32 i;
    s32 j;
    s32 t;
    s32 flags;

    t = ReadBufferedS16((BufferedStream*)other);
    self->id = t;
    t = ReadBufferedS16((BufferedStream*)other);
    self->length = (f32)t * 0.01666666753590107f;
    t = ReadBufferedU16((BufferedStream*)other);
    self->targetCount = t;
    self->targets = (s32*)AllocateFrontMemory(t << 2);
    for (k = 0; k < self->targetCount; k++) {
        self->targets[k] = ReadBufferedS16((BufferedStream*)other);
    }
    t = ReadBufferedS8((BufferedStream*)other);
    self->trackCount = t;
    self->tracks = (AnimationTrack*)AllocateZeroedFrontMemory(t * 28);
    for (i = 0; i < self->trackCount; i++) {
        e = &self->tracks[i];
        e->target = ReadBufferedS16((BufferedStream*)other);
        flags = ReadBufferedS8((BufferedStream*)other);
        if (flags & 1) {
            qp = CreatePositionCurve(ReadBufferedS8((BufferedStream*)other));
            e->pos = qp;
            if (qp->vt->read) qp->vt->read(qp, other);
        }
        if (flags & 2) {
            qr = CreateRotationCurve(ReadBufferedS8((BufferedStream*)other));
            e->rot = qr;
            if (qr->vt->read) qr->vt->read(qr, other);
        }
        if (flags & 4) {
            qs = CreateScaleCurve(ReadBufferedS8((BufferedStream*)other));
            e->scale = qs;
            if (qs->vt->read) qs->vt->read(qs, other);
        }
        if (flags & 8) {
            qw = CreateWeightCurve(ReadBufferedS8((BufferedStream*)other));
            e->weight = qw;
            if (qw->vt->read) qw->vt->read(qw, other);
        }
        if (flags & 0x10) {
            e->morphCount = ReadBufferedU8((BufferedStream*)other);
            e->morph = (WeightCurve**)AllocateZeroedFrontMemory(e->morphCount << 2);
            for (j = 0; j < e->morphCount; j++) {
                t = ReadBufferedS8((BufferedStream*)other);
                if (t != -1) {
                    e->morph[j] = CreateWeightCurve(t);
                    qw = e->morph[j];
                    if (qw->vt->read) qw->vt->read(qw, other);
                }
            }
        }
        sel = (flags & 0x20) ? e : sel;
    }
    if (sel != 0) MoveAnimationTrackToEnd(self, sel);
    ReadAnimationEvents(self, other, 0, &self->startCount, &self->startList);
    ReadAnimationEvents(self, other, 1, &self->timedCount, &self->timedList);
    ReadAnimationEvents(self, other, 0, &self->endCount, &self->endList);
    ReadPropertyRecords(self, other);
}

// Reads an animation's event list from the stream: a count, then per event a kind byte, a time
// (16-bit, 1/60 s ticks, when flag is set) and a kind-specific payload. Consecutive sound events
// (kind 0) with the same parameters are merged into one SoundChoice that holds several sound ids.
void ReadAnimationEvents(void* unused, Stream83* r, s32 flag, s32* count, AnimEvent** out)
{
    AnimEvent* e;
    s32 i;
    s32 merged;
    *count = ReadBufferedS8((BufferedStream*)r);
    *out = (AnimEvent*)AllocateZeroedFrontMemory(*count * 16);
    for (i = 0; i < *count; i++) {
        e = &(*out)[i];
        e->kind = ReadBufferedS8((BufferedStream*)r);
        if (flag) e->a0.f = (f32)ReadBufferedS16((BufferedStream*)r) * 0.016666668f;
        switch (e->kind) {
        case 44:
        case 51:
            ReadOptionalBufferedBlock((BufferedStream*)r, (u8**)&e->a8.i);
            break;
        case 0: {
            SoundChoice t;
            SoundChoice* g;
            s32 j;
            s32 k;
            AnimEvent* q;
            merged = 0;
            t.ids[0] = ReadBufferedS16((BufferedStream*)r);
            t.target = ReadBufferedS16((BufferedStream*)r);
            t.nearRange = ReadBufferedS32((BufferedStream*)r);
            t.farRange = ReadBufferedS32((BufferedStream*)r);
            t.baseVolume = ReadBufferedFloat((BufferedStream*)r);
            t.pitch = ReadBufferedFloat((BufferedStream*)r);
            t.startParam = ReadBufferedFloat((BufferedStream*)r);
            t.count = 1;
            t.cur = 0;
            k = i - 1;
            do {
                j = k;
                goto test;
            ins:
                g->ids[g->count++] = t.ids[0];
                goto done;
            } while (0);
        test:
            q = &(*out)[j];
            if (q->a0.f != e->a0.f) goto done;
            if (j < 0) goto done;
            if (q->kind != 0) {
                j--;
                goto test;
            }
            *count = *count - 1;
            i = k;
            merged = 1;
            g = (SoundChoice*)q->a8.i;
            if (g->count < 6) goto ins;
        done:
            if (!merged) {
                e->a8.i = (s32)AllocateFrontMemory(0x28);
                *(SoundChoice*)e->a8.i = t;
            }
            break;
        }
        case 4:
        case 7:
            F32(e->a8.i) = (f32)ReadBufferedS16((BufferedStream*)r) * 0.016666668f;
            F32(e->aC.i) = ReadBufferedFloat((BufferedStream*)r);
            break;
        case 19:
        case 20:
            e->a8.i = ReadBufferedS16((BufferedStream*)r);
            e->aC.i = ReadBufferedU8((BufferedStream*)r);
            break;
        case 16:
            e->a8.i = ReadBufferedS16((BufferedStream*)r);
            H0(e->aC.i) = ReadBufferedS8((BufferedStream*)r);
            H2(e->aC.i) = ReadBufferedS8((BufferedStream*)r);
            break;
        case 21:
        case 23:
            e->a8.i = (s32)AllocateZeroedFrontMemory(0xC);
            ((EventAttachmentDrive*)e->a8.i)->owner = ReadBufferedS16((BufferedStream*)r);
            ((EventAttachmentDrive*)e->a8.i)->f4 = ReadBufferedFloat((BufferedStream*)r);
            ((EventAttachmentDrive*)e->a8.i)->f8 = ReadBufferedFloat((BufferedStream*)r);
            break;
        case 25:
        case 26:
            H0(e->a8.i) = ReadBufferedS16((BufferedStream*)r);
            e->aC.i = (s32)AllocateZeroedFrontMemory(0x14);
            ((FadeRequest*)e->aC.i)->kind = 1;
            ((FadeRequest*)e->aC.i)->f08 = ReadBufferedS16((BufferedStream*)r);
            ((FadeRequest*)e->aC.i)->f0C = -1;
            ((FadeRequest*)e->aC.i)->flags = 0;
            ((FadeRequest*)e->aC.i)->text = (u8*)AllocateZeroedFrontMemory(0x20);
            ReadBufferedStreamBytes((BufferedStream*)r, 0x20, ((FadeRequest*)e->aC.i)->text);
            break;
        case 27:
            e->a8.i = ReadBufferedU8((BufferedStream*)r);
            e->aC.i = ReadBufferedS16((BufferedStream*)r);
            break;
        case 28:
            e->a8.i = (s32)AllocateZeroedFrontMemory(0x10);
            ((EventObjectPair*)e->a8.i)->animationId = ReadBufferedS16((BufferedStream*)r);
            ((EventObjectPair*)e->a8.i)->targetId = ReadBufferedS16((BufferedStream*)r);
            F32(((EventObjectPair*)e->a8.i)->f8) = ReadBufferedFloat((BufferedStream*)r);
            ((EventObjectPair*)e->a8.i)->fC = ReadBufferedFloat((BufferedStream*)r);
            break;
        case 37:
            H0(e->a8.i) = ReadBufferedS16((BufferedStream*)r);
            H2(e->a8.i) = ReadBufferedS16((BufferedStream*)r);
            break;
        case 6: case 12: case 13: case 17: case 18: case 22: case 24:
        case 29: case 30: case 31: case 32: case 35: case 36: case 39:
        case 41: case 59:
            e->a8.i = ReadBufferedS16((BufferedStream*)r);
            break;
        case 40:
            e->a8.i = ReadBufferedU16((BufferedStream*)r);
            break;
        case 38:
        case 45:
        case 47:
            e->a8.i = ReadBufferedS16((BufferedStream*)r);
            e->aC.i = ReadBufferedS16((BufferedStream*)r);
            break;
        case 48:
            e->a8.i = (s32)AllocateZeroedFrontMemory(0x10);
            ((EventObjectPair*)e->a8.i)->animationId = ReadBufferedS16((BufferedStream*)r);
            ((EventObjectPair*)e->a8.i)->targetId = ReadBufferedS16((BufferedStream*)r);
            ((EventObjectPair*)e->a8.i)->f8 = ReadBufferedS16((BufferedStream*)r);
            ((EventObjectPair*)e->a8.i)->fC = ReadBufferedFloat((BufferedStream*)r);
            break;
        case 9:
        case 10:
            e->a8.i = ReadBufferedS16((BufferedStream*)r);
            F32(e->aC.i) = ReadBufferedFloat((BufferedStream*)r);
            break;
        case 46:
        case 52:
            H0(e->a8.i) = ReadBufferedS16((BufferedStream*)r);
            H2(e->a8.i) = ReadBufferedS16((BufferedStream*)r);
            H0(e->aC.i) = ReadBufferedS16((BufferedStream*)r);
            break;
        case 54:
            H0(e->a8.i) = ReadBufferedS16((BufferedStream*)r);
            H2(e->a8.i) = ReadBufferedS16((BufferedStream*)r);
            ReadBufferedString((BufferedStream*)r, (u8**)&e->aC.i);
            break;
        case 5:
        case 33:
        case 57:
        case 58:
            F32(e->a8.i) = ReadBufferedFloat((BufferedStream*)r);
            break;
        }
    }
}

void CopyAnimation(Animation* self, Animation* src)
{
    CopyObjectData(self, src);
}

// Starts the object, then computes its output as position + t*(velocity + t*acceleration) at the
// entry's dt, clamped to its low and high limits; when enabled, queues StartLinkedObjectAnimation
// for it.
void StartClampedKinematicValue(Animation* self)
{
    StartObject(self);
    MotionState* k = &self->kin;
    f32 t = g_currentEntry->dt;
    f32 v = k->pos + t * (k->vel + t * k->acc);
    f32 lo = self->lo;
    f32 hi = self->hi;
    if (v < lo) {
        v = lo;
    } else if (hi < v) {
        v = hi;
    }
    self->out = v;
    if (self->enabled) {
        AppendQueuedCallOnce(self->world, (void*)StartLinkedObjectAnimation, self, 0, 0);
    }
}

// Finds the object the animation names (an object with its id in class 4 or, failing that, 0x104)
// and starts a player of the animation for it, without preset targets.
void StartLinkedObjectAnimation(Animation* self)
{
    s32 scratch[4];
    BaseObject* v;
    if (self->id != -1) {
        v = (BaseObject*)FindFirstObjectById(self->world, 4, self->id, self);
        if (v == 0) {
            v = (BaseObject*)FindFirstObjectById(self->world, 0x104, self->id, self);
        }
    } else {
        v = 0;
    }
    CreateAnimationPlayerWithoutPresetTargets(self, v, 0, (AnimationPlayer**)scratch, 0.0f, 1.0f);
}

// Makes a player for the animation starting at time fa with speed fb, and links it into the
// animation's list and the world's (listed or unlisted) player list. Each target of its tracks is
// then resolved to an object, from the explicit key/object pairs first, otherwise by searching the
// world by id.
void CreateAnimationPlayer(Animation* self, BaseObject* alt, s32 npairs, TargetBinding* pairs, s32 flags, AnimationPlayer** out, f32 fa, f32 fb)
{
    s32 tmp;
    AnimationPlayer* obj;
    AnimationPlayer** pobj;
    World* world = self->world;
    obj = NewAnimationPlayer(world);
    if (out != 0) *out = obj;
    obj->time = fa;
    obj->anim = self;
    obj->object = alt;
    obj->speedScale = self->speedScale;
    SetAnimationPlayerSpeed(obj, fb);
    AppendToList((ObjectList*)self->props6C, obj);
    if (self->listedInWorld != 0) {
        AppendToList((ObjectList*)&world->listedAnimationPlayers, obj);
    } else {
        AppendToList((ObjectList*)&world->animationPlayers, obj);
    }
    PushBackMemoryMark();
    BaseObject* ctx;
    if (alt == 0) ctx = self; else ctx = alt;
    PlacedObject** hosts = (PlacedObject**)AllocateBackMemory(self->targetCount * 4);
    s32 i;
    for (i = 0; i < self->targetCount; i++) {
        hosts[i] = (PlacedObject*)FindFirstObjectById(world, 4, self->targets[i], ctx);
    }
    s32 count = self->trackCount + (self->movedTrack != 0);
    for (s32 k = 0; k < count; k++) {
        AnimationTrack* e = &self->tracks[k];
        s32 key = e->target;
        PlacedObject* h;
        s32 j;
        for (j = 0; j < npairs; j++) {
            if (key == pairs[j].key) {
                h = (PlacedObject*)pairs[j].object;
                goto found;
            }
        }
        h = (PlacedObject*)FindFirstObjectById(world, 4, key, ctx);
        if (h == 0) {
            for (i = 0; i < self->targetCount; i++) {
                h = (PlacedObject*)FindFirstObjectById(world, 1, key, hosts[i]);
                if (h != 0) break;
            }
            if (h == 0) {
                h = (PlacedObject*)FindFirstObjectById(world, 0x104, key, ctx);
                if (h == 0) continue;
            }
        }
    found:
        TrackAttachmentBits* n = (TrackAttachmentBits*)CreateTrackAttachment(h);
        n->index = k;
        n->player = obj;
        n->key = self->key;
        if (k >= self->trackCount) {
            if (e->scale == 0 && e->morph == 0) {
                PushFreeSlot((FreeListPool*)&self->world->pool1B20, (Attachment*)n);
                continue;
            }
        } else {
            if (flags & 1) {
                n->mode0 = n->mode1 = 3;
            } else {
                ChoosePoseSourceModes((Attachment*)n);
            }
            if (e->pos == 0) n->mode0 = -1;
            if (e->rot == 0 && e->weight == 0) n->mode1 = -1;
        }
        if (e->scale != 0) n->mode2 = 2;
        if (e->morph != 0) n->mode3 = 2;
        AppendToList((ObjectList*)&obj->list44, n);
        InsertAttachment(h, (Attachment*)n);
        PlacedObject* r = h->root;
        if (r == 0) {
            r = h;
            while (r->parent != 0) r = (PlacedObject*)r->parent;
        }
        if (!(r->flags & 0x400000000000)) {
            if ((u32)obj->rootCount < 0x20) {
                r->flags |= 0x400000000000;
                ((PlacedObject**)obj->roots)[obj->rootCount++] = r;
            }
        }
    }
    PopBackMemoryMark();
    for (s32 j = 0; j < obj->rootCount; j++) {
        ((PlacedObject**)obj->roots)[j]->flags &= ~0x400000000000;
    }
    RegisterObjectGroup(world, (FoundList*)obj->f54);
    if (self->padSelect != 0) SetAnimationPlayerPadSelect(obj, 1);
    tmp = 0;
    for (s32 m = 0; m < self->startCount; m++) {
        RunAnimationEvent(obj, &self->startList[m], &tmp);
    }
    ApplyListedPoseSources(obj, flags & 4);
    if (flags & 2) {
        RunSeekAnimationEvents(obj, self, &tmp);
    } else {
        SeekAnimationEventCursor(obj);
    }
    pobj = &obj;
    TriggerScriptEvent(self, 9, 1, &pobj);
}

// CreateAnimationPlayer with no preset target lists (0, 0).
void CreateAnimationPlayerWithoutPresetTargets(Animation* self, BaseObject* alt, s32 flags, AnimationPlayer** out, f32 fa, f32 fb)
{
    CreateAnimationPlayer(self, alt, 0, 0, flags, out, fa, fb);
}

// CreateAnimationPlayer with no preset targets, giving the new player back instead of through a
// pointer.
AnimationPlayer* CreateAnimationPlayerReturned(Animation* self, BaseObject* owner, f32 fa, f32 fb, s32 flags)
{
    AnimationPlayer* out;
    CreateAnimationPlayer(self, owner, 0, 0, flags, &out, fa, fb);
    return out;
}

// The player of the animation's list whose object is key; 0 when none.
AnimationPlayer* FindAnimationPlayerByScope(Animation* self, BaseObject* key)
{
    ListFrame frame;
    AnimationPlayer* node = *(AnimationPlayer**)self->props6C;
    if (node != 0) {
        do {
            if (node->object == key) {
                return node;
            }
            node = node->animNext;
        } while (node != 0);
    }
    return 0;
}

// Finds the animation's player for key (or makes one, without preset targets) and seeks it to the
// given positions; the player goes to *out when out is set.
void FindOrCreateAnimationPlayerAndSeek(void* self, BaseObject* key, s32 a2, s32 a3, void** out, f32 fa, f32 fb)
{
    void* hit;
    void** dst = out ? out : &hit;
    hit = FindAnimationPlayerByScope((Animation*)self, key);
    if (hit) {
        *dst = hit;
    } else {
        CreateAnimationPlayerWithoutPresetTargets((Animation*)self, key, a3, (AnimationPlayer**)dst, 0.0f, 1.0f);
    }
    SeekAnimationPlayer((AnimationPlayer*)*dst, a2, fa, fb);
}

// FindOrCreateAnimationPlayerAndSeek giving the player back.
void* FindOrCreateSeekedAnimationPlayer(void* self, BaseObject* key, s32 a2, s32 a3, f32 fa, f32 fb)
{
    void* out;
    FindOrCreateAnimationPlayerAndSeek(self, key, a2, a3, &out, fa, fb);
    return out;
}


// Stops and clears *out's player and, if anim is non-null, creates a new player for it without
// preset targets.
void ReplaceAnimationPlayer(Animation* anim, BaseObject* owner, s32 flags, AnimationPlayer** out, f32 fa, f32 fb)
{
    if (*out != 0) {
        StopAnimationPlayer(*out);
        *out = 0;
    }
    if (anim != 0) {
        // retail's call sets the floats up before the last two arguments
        ((void (*)(Animation*, BaseObject*, f32, f32, s32, AnimationPlayer**))CreateAnimationPlayerWithoutPresetTargets)(anim, owner, fa, fb, flags, out);
    }
}

// True when any of the animation's timed events is of kind 0x19.
s32 HasAnimationEventKind19(Animation* a0)
{
    s32 n = a0->timedCount;
    if (n > 0) {
        s32 i = 0;
        // a field access here changes retail's code
        u8* p = (u8*)a0->timedList + 4;
        do {
            i++;
            if (*(s32*)p == 0x19) return 1;
            p += 0x10;
        } while (i < n);
    }
    return 0;
}

void* FindEntryByObjectId(BlendAnimationView* self, BaseObject* key);
void RefineNearestAnimationPathTime(f32 end, f32 radius, AnimationTrack* track, PlacedObject* owner, Vec4* point, f32 t, f32* outT,
                   Vec4* outPos, Vec4* outDir);

// The time on an animation's path for the owner nearest the point: the curve of the owner's track
// sampled from 0 to the length in steps of a tenth of it (at least 0.5), then refined from the best
// time with func_0012F210. With no track, the owner's position, time 0 and the default direction.
void FindNearestAnimationPathTime(Animation* self, PlacedObject* owner, f32 start, Vec4* point, f32* outT, Vec4* outPos,
                   Vec4* outDir)
{
    Vec4 sampled;
    f32 limit = self->length;
    f32 tenth = limit * 0.1f;
    f32 step = tenth >? 0.5f;
    AnimationTrack* track = (AnimationTrack*)FindEntryByObjectId((BlendAnimationView*)self, owner);
    if (track->pos == 0) {
        if (outT != 0) {
            *outT = 0.0f;
        }
        if (outPos != 0) {
            *outPos = owner->pos;
        }
        if (outDir != 0) {
            *outDir = g_zeroVector;
        }
        return;
    }
    track->pos->vt->eval(track->pos, owner, start, 1.0f, 0, &sampled, 0);
    f32 bestT = start;
    f32 t = 0.0f;
    u128 diff = Vu0::Sub(Vu0::Q(sampled), Vu0::Q(*point));
    f32 best = Vu0::ToFloat(Vu0::Dot(diff, diff));
    if (t < limit) {
        do {
            track->pos->vt->eval(track->pos, owner, t, 1.0f, 0, &sampled, 0);
            u128 d = Vu0::Sub(Vu0::Q(sampled), Vu0::Q(*point));
            f32 dist = Vu0::ToFloat(Vu0::Dot(d, d));
            if (dist < best) {
                best = dist;
                bestT = t;
            }
            t = limit <? t + step;
        } while (t < limit);
    }
    RefineNearestAnimationPathTime(self->length, 3.40282347e+38f, track, owner, point, bestT, outT, outPos, outDir);
}

// Searches an animation's start, timed and end event lists, in that order, for the first marker
// event (kind 0x27) with the given key; 0 when there is none.
AnimEvent* FindAnimationMarkerEvent(Animation* self, s32 key) {
    s32 i;
    AnimEvent* p;
    for (i = 0; i < self->startCount; i++) {
        p = &self->startList[i];
        if (p->kind == 0x27 && p->a8.i == key) {
            return p;
        }
    }
    for (i = 0; i < self->timedCount; i++) {
        p = &self->timedList[i];
        if (p->kind == 0x27 && p->a8.i == key) {
            return p;
        }
    }
    for (i = 0; i < self->endCount; i++) {
        p = &self->endList[i];
        if (p->kind == 0x27 && p->a8.i == key) {
            return p;
        }
    }
    return 0;
}

// The time of the animation's marker event for key, or 0 when there is none.
f32 GetAnimationMarkerTime(Animation* self, s32 key)
{
    f32* p = (f32*)FindAnimationMarkerEvent(self, key);
    f32 r = 0.0f;
    if (p != 0) {
        r = *p;
    }
    return r;
}

// The entry of the blend view's list (0x1C bytes each) whose key matches the object id, or 0.
void* FindEntryByObjectId(BlendAnimationView* self, BaseObject* key)
{
    for (s32 i = 0; i < self->sourceCount; i++) {
        BlendSourceEntry* e = (BlendSourceEntry*)(self->sourceTable + i * 0x1C);
        if (MatchesObjectId(key, e->key) != 0) {
            return e;
        }
    }
    return 0;
}

// A source of an object's pose (BlendSourceEntry's mover and sub): its first method gives the pose at a
// time and scale, a vector and a second value (func_0012CD78).
typedef void (*PoseSampleFn)(void* src, PlacedObject* o, f32 t, f32 scale, s32 z, void* a, Vec4* b);

// Fills per-depth arrays (position, rotation, velocity, spin; any may be null) of the frame chain
// from o up to top at animation time t, composing each ancestor's pose, scaled by the player's
// speed factors. Ancestors whose link record has flags 0xC are skipped.
void SampleAnimationFrameChain(BlendAnimationView* self, f32 t, f32 scale, PlacedObject* o, PlacedObject* top, s32 n, Vec4* pos, Mat3* rot,
                   Vec4* vel, Vec4* spin)
{
    typedef Vu0::Vec Vec;
    PlacedObject* chain[16];
    Vec4 P;
    Vec4 V;
    Vec4 W;
    Mat3 M;
    Vec4 p;
    Vec4 v;
    Vec4 w;
    Mat3 R;
    Mat3 N;
    f32 s = scale * (self->f7C * self->f98);
    s32 k = 0;
    while (o != top) {
        if (o->linkRecord == 0 || (o->linkRecord->flags & 0xC) == 0) {
            chain[k++] = o;
        }
        o = (PlacedObject*)o->parent;
    }
    P = g_zeroVector;
    M = g_identityMatrix;
    V = g_zeroVector;
    W = g_zeroVector;
    while (k < n) {
        n--;
        if (pos != 0) {
            pos[n] = P;
        }
        if (rot != 0) {
            rot[n] = M;
        }
        if (vel != 0) {
            vel[n] = V;
        }
        if (spin != 0) {
            spin[n] = W;
        }
    }
    for (k--; k >= 0; k--) {
        o = chain[k];
        BlendSourceEntry* e = (BlendSourceEntry*)FindEntryByObjectId(self, o);
        void* a;
        void* b;
        if (e != 0) {
            a = e->mover;
            b = e->sub;
        } else {
            a = 0;
            b = 0;
        }
        if (pos != 0 || vel != 0) {
            if (a != 0) {
                (*(PoseSampleFn*)*(void**)a)(a, o, t, s, 0, &p, &v);
            } else {
                p = o->pos;
                v = o->v150;
            }
        }
        if (b != 0) {
            (*(PoseSampleFn*)*(void**)b)(b, o, t, s, 0, &R, &w);
        } else {
            R = o->rot;
            w = o->v160;
        }
        if (pos != 0 || vel != 0) {
            Vec4 d;
            Vu0::Q(d) = Vu0::RotateUntied(M, Vec::Of(p)).q;
            Vu0::Q(P) = Vu0::Add(Vec::Of(P), Vec::Of(d)).q;
            if (vel != 0) {
                Vec4 f;
                Vec4 g;
                Vu0::Q(f) = Vu0::Rotate(M, Vec::Of(v)).q;
                Vu0::Q(V) = Vu0::Add(Vec::Of(V), Vec::Of(f)).q;
                Vu0::Q(g) = Vu0::Cross(Vec::Of(W), Vec::Of(d)).q;
                Vu0::Q(V) = Vu0::Add(Vec::Of(V), Vec::Of(g)).q;
            }
        }
        if (spin != 0 || vel != 0) {
            Vec4 d;
            Vu0::Q(d) = Vu0::Rotate(M, Vec::Of(w)).q;
            Vu0::Q(W) = Vu0::Add(Vec::Of(W), Vec::Of(d)).q;
        }
        // The product of the rotations, written out here rather than through MulRotation: its
        // matrix takes the freed slots of the rotated vectors above and its rows come after
        // them, which an inline's frame (one temporary for all its locals) does not give.
        {
            Mat3 r;
            Vec4 x;
            Vec4 y;
            Vec4 z;
            Vu0::Q(x) = Vu0::RotateUntied(M, Vu0::Q(R.r[0]));
            r.r[0] = x;
            Vu0::Q(y) = Vu0::RotateUntied(M, Vu0::Q(R.r[1]));
            r.r[1] = y;
            Vu0::Q(z) = Vu0::RotateUntied(M, Vu0::Q(R.r[2]));
            r.r[2] = z;
            N = r;
        }
        M = N;
        if (k < n) {
            if (pos != 0) {
                pos[k] = P;
            }
            if (rot != 0) {
                rot[k] = M;
            }
            if (vel != 0) {
                vel[k] = V;
            }
            if (spin != 0) {
                spin[k] = W;
            }
        }
    }
}

// Finds the objects named by the animation's kind 0x29 timed events: counts them into *outCount
// and, if outArr is given, fills a back-memory array with each one looked up by id in the world.
void GatherAnimationEventObjects(Animation* self, BaseObject* ctx, s32* outCount, BaseObject*** outArr)
{
    s32 n = 0;
    s32 i;
    u8* p;
    if (self->timedCount > 0) {
        i = self->timedCount;
        // a field access here changes retail's code
        p = (u8*)self->timedList + 4;
        do {
            if (*(s32*)p == 0x29) n++;
            p += 16;
        } while (--i != 0);
    }
    if (outCount != 0) {
        *outCount = n;
    }
    if (outArr != 0) {
        BaseObject** res = (BaseObject**)AllocateBackMemory(n * 4);
        *outArr = res;
        i = 0;
        if (i < self->timedCount) {
            BaseObject** out = res;
            do {
                AnimEvent* e = (AnimEvent*)(i * 16 + (u8*)self->timedList);
                if (e->kind == 0x29) {
                    *out = (BaseObject*)FindFirstObjectById(self->world, 0x104, e->a8.i, ctx);
                    out++;
                }
                i++;
            } while (i < self->timedCount);
        }
    }
}

// Moves track p to the end of the animation's track array (after the counted tracks), shifting the
// later ones down, and records it as the animation's movedTrack.
void MoveAnimationTrackToEnd(Animation* self, AnimationTrack* p)
{
    AnimationTrack tmp = *p;
    s32 idx = p - self->tracks;
    self->trackCount = self->trackCount - 1;
    if (idx < self->trackCount) {
        MoveMemory(p, p + 1, (self->trackCount - idx) * 0x1C);
    }
    p = self->tracks + self->trackCount;

    *p = tmp;
    self->movedTrack = p;
}

// Moves the owner's track to the end of the animation's list, unless a track was already moved.
void MoveObjectAnimationTrackToEnd(Animation* a0, BaseObject* owner)
{
    if (a0->movedTrack == 0) {
        void* r = FindEntryByObjectId((BlendAnimationView*)a0, owner);
        if (r) MoveAnimationTrackToEnd(a0, (AnimationTrack*)r);
    }
}

// Empty load method: an animation player is not read from a stream.
void SkipAnimationPlayerLoad(AnimationPlayer* self, BufferedStream* stream) {}

// Empty start method.
void SkipAnimationPlayerStart() {}

// Empty copy method.
void SkipAnimationPlayerCopy(AnimationPlayer* self, AnimationPlayer* src) {}

// Takes a cleared animation player from the world's pool and sets its methods, the link offset of
// its list (0x20) and its roots pointer.
AnimationPlayer* NewAnimationPlayer(World* pool)
{
    AnimationPlayer* o = (AnimationPlayer*)PopZeroedFreeSlot(&pool->pool1B58);

    o->vt = &g_animationPlayerMethods;
    SetListLinkOffset(&o->list44, 0x20);
    o->roots = (u8*)o->pad64;

    return o;
}

// Sets the player's pad-select state; the world's pad-select flag is acquired when it turns on and
// released when it turns off.
void SetAnimationPlayerPadSelect(AnimationPlayer* self, s32 v)
{
    if (v == self->state24) {
        return;
    }
    if (v != 0) {
        AcquirePadSelectFlag(g_currentWorld);
    } else {
        ReleasePadSelectFlag(g_currentWorld);
    }
    self->state24 = (s8)v;
}

// Puts the player's timed-event cursor (f20) at the first event not before the current time (or,
// when playing backwards, just after the last one not after it).
void SeekAnimationEventCursor(AnimationPlayer* self)
{
    Animation* track = self->anim;
    s32 n = track->timedCount;
    s32 i;
    if (n == 0) {
        return;
    }
    if (self->speed >= 0.0f) {
        i = 0;
        if (n > 0) {
            AnimEvent* keys = track->timedList;
            for (i = 0; i < track->timedCount; i++) {
                if (keys[i].a0.f >= self->time) {
                    break;
                }
            }
        }
        self->nextEventIndex = i;
    } else {
        for (i = n - 1; i >= 0; i--) {
            AnimEvent* k = &track->timedList[i];
            if (k->a0.f <= self->time) {
                break;
            }
        }
        self->nextEventIndex = i + 1;
    }
}

// The attachment in the player's list whose owner matches the id; 0 when none.
TrackFollowAttachment* FindPlayerAttachmentByOwner(AnimationPlayer* a0, s32 owner)
{
    ListFrame frame;
    TrackFollowAttachment* n = (TrackFollowAttachment*)a0->list44.head;
    while (n) {
        if (MatchesObjectId(n->owner, owner)) return n;
        n = (TrackFollowAttachment*)n->w20.lo;
    }
    return 0;
}

LINKER_REMNANT(func_0012D5C8);

// Runs one event of an animation player (self) as its time passes the event, switched on the
// event's kind. Objects named by an id are searched in the world under the player's object (or
// the animation). `rev` is set when the player runs backwards over a timed event, which flips
// the on/off sense of the paired kinds below. *out = 1 asks the caller to stop stepping.
// 0 plays a sound chosen at random from a SoundChoice (never the same twice, skipped if still
// playing in p50), at a target object or with default ranges; 1 stops that sound; 2 / 3 restore /
// silence volume channel 2; 4 and 7 set the time and speed, then re-seek the event cursor and
// settle the pose sources; 5 sets the speed; 6 chooses a step sequence's state; 8 stops the player
// (*out = 1); 9 / 10 show / hide an object, with a fade if a time is given; 11 jumps to a time and
// stops (speed 0); 12 / 13 push / remove an object's camera controller; 14 / 15 set the player's
// pad select; 16 sets a collider's two anchor modes; 17 / 18 set an attachment to mode 5 or
// restore its modes; 19 / 20 switch the player to / from state 11 (applying pose sources);
// 21 to 24 set or clear one of the two driven attachments (f2C, f30); 25 / 26 start / save a
// screen fade; 27 starts a level exit unless the player is already in one; 33 / 34 start / stop
// the timer; 28 starts another animation on an object pair; 29 to 32 set a track's scale or morph
// mode (2 on, -1 off) and notify the object when it changed; 35 / 36 evaluate a track's position
// or rotation at a time and apply it; 37 starts a pad record pattern; 38 to 41 send callbacks
// (0x12, 0x13, 0x15) or script event 0xA to an object or the player's listeners; 42 holds the
// player while a streamed voice is pending (time = event time, counter f20 stepped back); 43 stops
// the streamed voice; 44 opens a key record; 45 selects a value entry by key; 46 / 47 create /
// destroy a state walker between two objects; 48 starts a request on an object (anchored to an
// owner or a world position, with optional extra object and scale, method 0x1B); 49 / 50 show /
// hide the counted screen element; 51 queues a movie; 52 to 54 resize, clear, or post to the
// stacked caption group; 55 / 56 set the element stack state 0 / 1; 57 / 58 set the world's value
// with / without its target; 59 binds an entry queue to the player.
void RunAnimationEvent(AnimationPlayer* self, AnimEvent* msg, s32* out)
{
    EventScratch u;
    s32 rev = 0;
    Animation* owner = self->anim;
    World* world = owner->world;

    if (self->speed < 0.0f && msg >= owner->timedList) {
        rev = msg < &owner->timedList[owner->timedCount];
    }
    switch (msg->kind) {
    case 42:
        if (CheckStreamVoicePending() != 0) {
            self->time = ClampRange::Of(msg->a0.f, 0.0f, owner->length);
            self->nextEventIndex--;
            *out = 1;
        }
        break;
    case 44:
        OpenKeyRecord((KeyRecord*)msg->a8.p);
        break;
    case 43:
        StopStreamVoice();
        break;
    case 0: {
#define Q_12D5D0 ((SoundChoice*)msg->a8.p)
        s32 idx;
        s32 busy;
        s32 id;
        Collider* tgt;
        if (Q_12D5D0->count < 2) {
            idx = 0;
        } else {
            s32 r = RandomIntInRange(0, Q_12D5D0->count - 2);
            idx = (Q_12D5D0->cur + r + 1) % Q_12D5D0->count;
            Q_12D5D0->cur = idx;
        }
        id = Q_12D5D0->ids[idx];
        if (id == -1) {
            return;
        }
        busy = IsSoundEntryLooping(id);
        if (self->p50 != 0 && busy != 0) {
            return;
        }
        if (Q_12D5D0->target != -1) {
            tgt = (Collider*)FindFirstObjectById(world, 0x104, Q_12D5D0->target, self->object ? self->object : (void*)self->anim);
        } else {
            tgt = (Collider*)self->object;
        }
        if (tgt != 0) {
            StartSoundEffect(id, busy ? (PlayingSound**)&self->p50 : 0, tgt, 0, (f32)Q_12D5D0->farRange, (f32)Q_12D5D0->nearRange, Q_12D5D0->baseVolume,
                          Q_12D5D0->pitch, Q_12D5D0->startParam, 0, 0);
            if (busy && self->p50 != 0) {
                tgt->desc->m0E(tgt, 8, self->p50);
            }
        } else {
            StartSoundEffect(id, busy ? (PlayingSound**)&self->p50 : 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
#undef Q_12D5D0
        break;
    }
    case 1:
        if (self->p50 != 0) {
            StopSoundRecord((PlayingSound*)self->p50, 0);
        }
        break;
    case 2:
        RestoreVolumeChannel2();
        break;
    case 3:
        SilenceVolumeChannel2();
        break;
    case 11:
        self->time = ClampRange::Of(msg->a0.f, 0.0f, owner->length);
        self->speed = 0.0f;
        break;
    case 4:
    case 7:
        self->time = msg->a8.f;
        SetAnimationPlayerSpeed(self, msg->aC.f);
        SeekAnimationEventCursor(self);
        SettleListedPoseSources(self);
        break;
    case 5:
        SetAnimationPlayerSpeed(self, msg->a8.f);
        break;
    case 6: {
        Collider* t = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.i, self->object ? self->object : (void*)owner);
        if (t != 0) {
            ChooseStepSequenceState((StepSequence*)t);
        }
        break;
    }
    case 8:
        StopAnimationPlayer(self);
        *out = 1;
        break;
    case 9:
    case 10: {
        s32 on = msg->kind == 9;
        if (rev) {
            on = !on;
        }
        Collider* t = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.i, self->object ? self->object : (void*)owner);
        if (t == 0) {
            return;
        }
        if (msg->aC.f != 0.0f) {
            if (on) {
                FadeInPlacedObject(t, msg->aC.f);
            } else {
                FadeOutPlacedObject(t, msg->aC.f);
            }
        } else {
            if (on) {
                t->desc->m02(t);
            } else {
                t->desc->m03(t);
            }
        }
        break;
    }
    case 16: {
        Collider* t = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.i, self->object ? self->object : (void*)self->anim);
        if (t != 0) {
            SetColliderAnchors(t, msg->aC.h.lo < 0 ? t->mode450 : msg->aC.h.lo, 0, msg->aC.h.hi < 0 ? t->mode470 : msg->aC.h.hi, 0);
        }
        break;
    }
    case 12:
    case 13: {
        s32 on = msg->kind == 12;
        Collider* t;
        if (rev) {
            on = !on;
        }
        t = (Collider*)FindFirstObjectById(world, 4, msg->a8.i, self->anim);
        if (t != 0) {
            if (on) {
                PushObjectCameraController(t);
            } else {
                RemoveObjectCameraController(t);
            }
        }
        break;
    }
    case 14:
    case 15:
    {
        s32 on = msg->kind == 14;
        if (rev) {
            on = !on;
        }
        SetAnimationPlayerPadSelect(self, on);
    }
        break;
    case 19:
    case 20: {
        s32 on = msg->kind == 19;
        if (rev) {
            on = !on;
        }
        SwitchPlayerState11(g_player, on);
        if (on && msg->aC.i != 0) {
            ApplyListedPoseSources(self, 1);
        }
        break;
    }
    case 17:
    case 18: {
        TrackAttachment* n = (TrackAttachment*)FindPlayerAttachmentByOwner(self, msg->a8.i);
        if (n != 0) {
            if ((msg->kind != 17) != !rev) {
                n->SetMode(5);
                n->mode0 = 5;
            } else {
                ChoosePoseSourceModes(n);
            }
        }
        break;
    }
    case 21:
    case 22:
    case 23:
    case 24: {
        TrackAttachment* n;
        s32 key;
        if (msg->kind == 21 || msg->kind == 23) {
            key = *(s32*)msg->a8.p;
        } else {
            key = msg->a8.i;
        }
        n = (TrackAttachment*)FindPlayerAttachmentByOwner(self, key);
        if (n == 0) {
            break;
        }
        switch (msg->kind) {
        case 21:
            self->driven = n;
            self->positionFalloff = msg;
            break;
        case 22:
            self->positionFalloff = 0;
            if (self->rotationFalloff == 0) {
                self->driven = 0;
            }
            break;
        case 23:
            self->driven = n;
            self->rotationFalloff = msg;
            break;
        case 24:
            self->rotationFalloff = 0;
            if (self->positionFalloff == 0) {
                self->driven = 0;
            }
            break;
        }
        break;
    }
    case 25:
        StartScreenFade(&g_screenFade, (FadeRequest*)msg->aC.i, msg->a8.h.lo);
        break;
    case 26:
        SaveFadeRequest(&g_screenFade, (FadeRequestBlock*)msg->aC.i, msg->a8.h.lo);
        break;
    case 27: {
        Player* g = g_player;
        if (g != 0 && g->state == 9 && g->subState == 0x1C && g_currentEntry == g_currentLevelRecord) {
            return;
        }
        BeginLevelExit(msg->a8.i, msg->aC.i);
        break;
    }
    case 33:
        StartTimer(&g_timerElement, msg->a8.f);
        StartTimerCounting(&g_timerElement);
        break;
    case 34:
        StopTimer(&g_timerElement);
        break;
    case 28: {
        Collider* a = (Collider*)FindFirstObjectByIdMode4(world, ((EventObjectPair*)msg->a8.p)->animationId, owner->parent);
        Collider* b;
        if (((EventObjectPair*)msg->a8.p)->targetId != -1) {
            b = (Collider*)FindFirstObjectByIdMode4(owner->world, ((EventObjectPair*)msg->a8.p)->targetId, owner->parent);
        } else {
            b = 0;
        }
        if (a != 0) {
            CreateAnimationPlayerWithoutPresetTargets((Animation*)a, b, 0, 0, *(f32*)&((EventObjectPair*)msg->a8.p)->f8, ((EventObjectPair*)msg->a8.p)->fC);
        }
        break;
    }
    case 29:
    case 30:
    case 31:
    case 32: {
        TrackAttachment* n = (TrackAttachment*)FindPlayerAttachmentByOwner(self, msg->a8.i);
        u8 go = 0;
        if (n != 0) {
            AnimationTrack* e = &owner->tracks[n->index];
            switch (msg->kind) {
            case 29:
                if (e->scale != 0) {
                    u8 v = n->mode2;
                    n->mode2 = 2;
                    go = (u8)(v + 1) < 2;
                }
                break;
            case 30:
                if (e->scale != 0) {
                    s8 v = n->mode2;
                    n->mode2 = -1;
                    go = v != -1;
                }
                break;
            case 31:
                if (e->morph != 0) {
                    u8 v = n->mode3;
                    n->mode3 = 2;
                    go = (u8)(v + 1) < 2;
                }
                break;
            case 32:
                if (e->morph != 0) {
                    s8 v = n->mode3;
                    n->mode3 = -1;
                    go = v != -1;
                }
                break;
            }
        }
        if (go) {
            n->owner->desc02()->m2B(n->owner);
        }
        break;
    }
    case 35:
    case 36: {
        TrackAttachment* n = (TrackAttachment*)FindPlayerAttachmentByOwner(self, msg->a8.i);
        if (n == 0) {
            break;
        }
        AnimationTrack* e = &owner->tracks[n->index];
        PlacedObject* o = n->owner;
        if (msg->kind == 35) {
            e->pos->vt->eval(e->pos, o, msg->a0.f, self->speed, 0, &u.v[0], &u.v[1]);
            o->desc02()->m1D(o, (Vec4*)&u.v[0]);
            o->desc02()->m20(o, (Vec4*)&u.v[1]);
        } else {
            e->rot->vt->eval(e->rot, o, 0, &u.v[2], &u.v[0], msg->a0.f, self->speed);
            o->desc02()->m1E(o, (Mat3*)&u.v[2]);
            o->desc02()->m21(o, (Vec4*)&u.v[0]);
        }
        break;
    }
    case 37:
        StartPadRecordPattern((PadRecord*)g_padRecord, msg->a8.h.hi, (f32)msg->a8.h.lo * 0.016666668f);
        break;
    case 38: {
        Collider* t;
        if (msg->a8.i == -1) {
            t = (Collider*)self->object;
        } else {
            t = (Collider*)FindFirstObjectByIdMode4(world, msg->a8.i, self->object);
        }
        if (t == 0) {
            break;
        }
        u.p[1] = (void*)msg->aC.i;
        u.p[0] = self;
        t->desc->m0E(t, 0x12, u.p);
        break;
    }
    case 39: {
        *(f32*)&u.w[1] = msg->a0.f;
        u.w[2] = msg->a8.i;
        u.p[0] = self;
        NotifyAnimationPlayerCallbacks(self, 0x13, u.w);
        break;
    }
    case 40: {
        u.p[1] = &msg->a8;
        u.p[0] = &self;
        TriggerScriptEvent(self->anim, 0xA, 2, u.p);
        break;
    }
    case 41: {
        Collider* t;
        if (self->object == 0) {
            break;
        }
        t = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.i, self->object);
        if (t == 0) {
            break;
        }
        u.p[1] = t;
        *(f32*)&u.w[2] = msg->a0.f;
        u.p[0] = self;
        NotifyAnimationPlayerCallbacks(self, 0x15, u.w);
        break;
    }
    case 45: {
        Collider* t = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.i, self->object);
        if (t != 0) {
            SelectValueEntryByKey(t, msg->aC.i);
        }
        break;
    }
    case 46: {
        void* scope = self->object ? self->object : (void*)self->anim;
        Collider* a = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.h.lo, scope);
        Collider* b;
        void* link;
        if (a == 0) {
            break;
        }
        b = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.h.hi, scope);
        link = FindListNodeByKey((StateGraph*)a, b);
        if (link == 0) {
            link = CreateStateWalker((StateGraph*)a, b, msg->aC.h.lo, 1);
        }
        SetStateWalkerTarget((StateWalker*)link, msg->aC.h.lo);
        break;
    }
    case 47: {
        void* link = 0;
        void* scope = self->object;
        if (scope == 0) {
            scope = self->anim;
        }
        Collider* a = (Collider*)FindFirstObjectByIdMode4(world, msg->a8.i, scope);
        if (a != 0) {
            link = FindListNodeByKey((StateGraph*)a, (Collider*)FindFirstObjectByIdMode4(world, msg->aC.i, scope));
        }
        if (link != 0) {
            DestroyStateWalker((StateWalker*)link);
        }
        break;
    }
    case 48: {
        EventObjectPair* in = (EventObjectPair*)msg->a8.p;
        void* scope = self->object ? self->object : (void*)owner;
        Collider* t = (Collider*)FindFirstObjectById(world, 0x104, in->animationId, scope);
        if (t == 0) {
            break;
        }
        u.req.flags = 0;
        if (in->targetId != -1) {
            Collider* s = (Collider*)FindFirstObjectById(world, 4, in->targetId, scope);
            if (s != 0) {
                if (IsObjectOfKind(s, 2) != 0) {
                    u.req.owner = s;
                    u.req.flags |= 1;
                } else if (IsObjectOfKind(s, 0x7E) != 0) {
                    u.req.flags |= 4;
                    ConvertPositionToWorld(s, (Vec4*)&u.req.qb);
                } else if (IsObjectOfKind(s, 0x73) != 0) {
                    u.req.flags |= 4;
                    GetObjectWorldPosition(s, (Vec4*)&u.req.qb);
                }
            }
        }
        if (u.req.flags == 0) {
            if (t->parent != 0 && IsObjectAttached(t->parent) != 0) {
                u.req.flags |= 1;
                u.req.owner = t->parent;
            } else {
                u.req.flags |= 4;
                GetObjectWorldPosition(t, (Vec4*)&u.req.qb);
            }
        }
        if (in->f8 != -1) {
            Collider* s = (Collider*)FindFirstObjectById(world, 4, in->f8, scope);
            if (s != 0) {
                u.req.f38 = s;
                u.req.flags |= 0x20;
            }
        }
        if (in->fC != 1.0f) {
            u.req.flags |= 0x18;
            u.req.f30 = in->fC;
        }
        t->desc->m1B(t, &u.req);
        break;
    }
    case 49:
        ShowCountedScreenElement(world);
        break;
    case 50:
        HideCountedScreenElement(world);
        break;
    case 51:
        QueueMovie((MoviePlayer*)g_moviePlayer, (void*)msg->a8.i);
        break;
    case 52:
        g_stackedCaptionGroup.vt->m17(&g_stackedCaptionGroup, &self->time);
        ResizeItemColumn(&g_stackedCaptionGroup, msg->aC.h.lo, (f32)msg->a8.h.lo, (f32)msg->a8.h.hi);
        break;
    case 53:
        g_stackedCaptionGroup.vt->m17(&g_stackedCaptionGroup, 0);
        ClearItemColumn(&g_stackedCaptionGroup);
        break;
    case 54:
        PostItemColumnEntry(&g_stackedCaptionGroup, msg->a8.h.lo, (char*)msg->aC.i, (f32)msg->a8.h.hi * 0.00390625f);
        break;
    case 55:
    {
        ElementStack* sys = &g_elementStack;
        ((U32P*)&sys->resumeState)->v = 0;
        SetElementStackState(sys, 0);
    }
        break;
    case 56:
    {
        ElementStack* sys = &g_elementStack;
        sys->resumeState = 1;
        SetElementStackState(sys, 1);
    }
        break;
    case 57:
        SetWorldValueAndTarget(world, msg->a8.f);
        break;
    case 58:
        SetWorldValueTarget(world, msg->a8.f);
        break;
    case 59: {
        EntryQueue* t = (EntryQueue*)FindFirstObjectById(world, 0x104, msg->a8.i, self->object ? self->object : (void*)owner);
        if (t != 0) {
            BindEntryQueueToObject(t, g_player);
        }
        break;
    }
    }
}

// Used when a player jumps to a new time: runs the events up to that time that matter for a seek
// (kinds 9, 10, 14 to 18, 28 and 39), and for kind 8 stops the player at that event's time with
// speed 0 and sets *out.
void RunSeekAnimationEvents(AnimationPlayer* self, Animation* sub, s32* out)
{
    f32 limit = self->time + 0.0001f;
    if (sub->timedCount != 0) {
    while (self->nextEventIndex < sub->timedCount && sub->timedList[self->nextEventIndex].a0.f < limit) {
        AnimEvent* it = &sub->timedList[self->nextEventIndex++];
        switch (it->kind) {
        case 8:
            self->time = it->a0.f;
            self->speed = 0;
            *out = 1;
            return;
        case 9:
        case 10:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 28:
        case 39:
            RunAnimationEvent(self, it, out);
            break;
        }
    }
    }
}

// Runs the animation's timed events that lie between the player's event index and its current time,
// forward when it plays forward and backward when it plays backward, stepping the index as it goes.
// Stops early when an event sets *out.
void RunAnimationEventsToTime(AnimationPlayer* self, Animation* list, s32* out)
{
    if (list->timedCount == 0) return;
    for (;;) {
        if (self->nextEventIndex < list->timedCount) {
            if (list->timedList[self->nextEventIndex].a0.f < self->time || (self->time == list->timedList[self->nextEventIndex].a0.f && 0.0f < self->speed)) {
                AnimEvent* e = &list->timedList[self->nextEventIndex];
                self->nextEventIndex = self->nextEventIndex + 1;
                RunAnimationEvent(self, e, out);
                if (*out != 0) return;
                continue;
            }
        }
        if (self->nextEventIndex <= 0) return;
        if (self->time < list->timedList[self->nextEventIndex - 1].a0.f || (self->time == list->timedList[self->nextEventIndex - 1].a0.f && self->speed < 0.0f)) {
            self->nextEventIndex = self->nextEventIndex - 1;
            RunAnimationEvent(self, &list->timedList[self->nextEventIndex], out);
            if (*out != 0) return;
            continue;
        }
        return;
    }
}

// Removes the entry from the current world's list at 0x1B7C and returns it to the pool at 0x1B58.
void ReleaseWorldListEntry(void* a0)
{
    RemoveFromList((ObjectList*)&g_currentWorld->list1B7C, a0);
    PushFreeSlot((FreeListPool*)&g_currentWorld->pool1B58, (Attachment*)a0);
}

// Ends an animation player: runs the animation's end events, notifies callbacks, frees its call
// records and sound group, removes it from the animation's and the world's lists, releases its
// attachments and sends script event 0xB.
void StopAnimationPlayer(AnimationPlayer* self)
{
    WordListFrame fr;
    EndEventLocals tmp;
    s32 i = 0;
    Animation* sub = self->anim;
    u8* base = (u8*)sub->world;
    for (i = 0; i < sub->endCount; i++) {
        // address arithmetic over a variable index
        AnimEvent* it = (AnimEvent*)((u8*)sub->endList + i * 16);
        tmp.a = 0;
        RunAnimationEvent(self, it, (s32*)&tmp);
    }
    NotifyAnimationPlayerCallbacks(self, 6, self);
    ReleaseCallRecords((World*)base, (T219CHook*)self->callbacks);
    self->callbacks = 0;
    UnregisterObjectGroup((World*)base, (FoundList*)self->f54);
    SetAnimationPlayerPadSelect(self, 0);
    RemoveQueuedCalls((World*)base, 2, 0, self, -1, 0);
    RemoveFromList((ObjectList*)sub->props6C, self);
    if (sub->listedInWorld != 0) {
        RemoveFromList((ObjectList*)&((World*)base)->listedAnimationPlayers, self);
    } else {
        RemoveFromList((ObjectList*)&((World*)base)->animationPlayers, self);
    }
    AppendToList((ObjectList*)&((World*)base)->list1B7C, self);
    sptr s0 = (sptr)&self->object;
    sptr e = (sptr)&self->list44;
    fr.link = e;
    fr.list = e;
    s32 link = ((ObjectList*)e)->offset;
    fr.prev = (sptr)g_activeListFrames;
    g_activeListFrames = (ListFrame*)&fr;
    fr.offset = link;
    sptr head = *(sptr*)e;
    fr.link = head + fr.offset;
    sptr a = head;
    if (a != 0) {
        do {
            Attachment* el = (Attachment*)a;
            el->vt->release(el, 7);
            sptr nx = *(sptr*)fr.link;
            fr.link = nx + fr.offset;
            a = nx;
        } while (a != 0);
    }
    if (self->soundHandle != 0)
        ClearSoundRecordHandle((PlayingSound**)&self->soundHandle);
    tmp.b = s0;
    TriggerScriptEvent(sub, 0xB, 1, &tmp.b);
    g_activeListFrames = (ListFrame*)fr.prev;
}

// Releases the player's attachment of the given owner (with the given mode), if it has one.
void ReleasePlayerAttachment(void* a0, s32 owner, s32 how)
{
    Attachment* n = FindPlayerAttachmentByOwner((AnimationPlayer*)a0, owner);
    if (n) n->vt->release(n, how);
}

// A scale from 1 down to 0.15 for a distance: 1 below the range's minimum, 0.15 from its maximum
// on, linear in between.
f32 GetRangeFalloffScale(RangeFalloffOwner* self, f32 value)
{
    FalloffRange* range = self->range;
    f32 r;
    if (value < range->minimum) {
        r = 1.0f;
    } else if (range->maximum <= value) {
        r = 0.15f;
    } else {
        r = (value - range->maximum) / (range->minimum - range->maximum);
        r = r * 0.85f + 0.15f;
    }
    return r;
}

// Brings a player's time *pos back into the animation's range by its end mode (0 stops at the ends,
// 1 loops, 2 ping-pongs, flipping the sign of *vel). Returns 1 when the time was past either end.
s32 ApplyAnimationLoopMode(AnimationPlayer* o, f32* pos, f32* vel)
{
    s32 r = 0;
    Animation* l = o->anim;
    f32 x = *pos;
    f32 lim = l->length;
    if (lim <= x) {
        switch (l->endMode) {
        case 0:
            if (lim < x) {
                *pos = lim;
                *vel = 0.0f;
            }
            break;
        case 1:
            *pos = FloatRemainder(x, lim);
            break;
        case 2: {
            f32 d = lim + lim;
            s32 flag = 1;
            if (d <= x) {
                *pos = FloatRemainder(x, d);
                if (*pos < l->length) flag = 0;
                *vel = __builtin_fabsf(*vel);
            }
            if (flag) {
                *pos = d - *pos;
                *vel = -*vel;
            }
            break;
        }
        }
        r = 1;
    } else if (x < 0.0f) {
        switch (l->endMode) {
        case 0:
            *pos = 0.0f;
            *vel = 0.0f;
            break;
        case 1:
            *pos = WrapModulo(x, lim);
            break;
        case 2: {
            x = -x;
            if (x <= lim) {
                *pos = x;
                *vel = -*vel;
            } else {
                f32 d = lim + lim;
                *vel = __builtin_fabsf(*vel);
                f32 q = WrapModulo(*pos, d);
                *pos = q;
                if (l->length <= q) {
                    *pos = d - q;
                    *vel = -*vel;
                }
            }
            break;
        }
        }
        r = 1;
    }
    return r;
}

extern "C" f32 Arccosine(f32 x);

// One frame of an animation player. While an attachment that follows it belongs to an object
// with flag bit 38 set (and the world's f2358 is clear) the player only stops its sound. The time
// advances by dt times the speed, weighted by how near the driven attachment's object is to its
// track's position and orientation (the two falloff ranges), after the delay at +0x10 has used
// up its part of dt; the events up to the new time run, the loop mode is applied (mode 0 ends the
// player, mode 1 loops it), and the events run again. A looping player puts the followers whose
// curves do not close back at their tracks' start.
void UpdateAnimationPlayer(AnimationPlayer* self, f32 dt)
{
    ListFrame frame;
    Animation* anim = self->anim;
    TrackFollowAttachment* n;
    f32 weight;
    s32 stop;
    s32 looped;
    s32 ended;
    s32 i;

    if (anim->world->f2358 == 0) {
        for (n = (TrackFollowAttachment*)self->list44.head; n != 0; n = (TrackFollowAttachment*)n->w20.lo) {
            if (n->owner->flags & ((u64)0x8000 << 23)) {
                StopSoundRecord((PlayingSound*)self->soundHandle, 0);
                return;
            }
        }
    }
    if (__builtin_fabsf(self->speed) < 0.0001f) {
        return;
    }
    weight = 1.0f;
    if (self->driven != 0) {
        RangeFalloffOwner* near = (RangeFalloffOwner*)self->positionFalloff;
        if (near != 0) {
            n = (TrackFollowAttachment*)self->driven;
            Vec4 pos;
            Vec4 d;
            f32 w;
            n->vt->getPos(n, 0.0f, &pos, 0);
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(n->owner->pos), Vu0::Q(pos));
            if (n->mode0 == 5) {
                d.z = 0.0f;
            }
            w = GetRangeFalloffScale(near, Vu0::ToFloat(Vu0::Length(Vu0::Q(d))));
            if (w < weight) {
                weight = w;
            }
        }
        RangeFalloffOwner* turn = (RangeFalloffOwner*)self->rotationFalloff;
        if (turn != 0) {
            n = (TrackFollowAttachment*)self->driven;
            Mat3 rot;
            Mat3 rel;
            f32 w;
            n->vt->getRot(n, 0.0f, &rot, 0);
            MultiplyMatrices3x3(&n->owner->rot, &rot, &rel);
            w = GetRangeFalloffScale(turn, Arccosine(GetMatrixRotationCosine((f32*)&rel)));
            if (w < weight) {
                weight = w;
            }
        }
        weight = ClampRange::Of(weight, 0.0f, 1.0f);
        if (weight < 0.0001f) {
            return;
        }
    }
    if (0.0f < self->delay) {
        f32 left = self->delay - dt;
        self->delay = left;
        if (left <= 0.0f) {
            dt = -left;
            self->delay = 0.0f;
        } else {
            dt = 0.0f;
        }
    }
    self->time = self->time + dt * self->speed * weight;
    stop = 0;
    looped = 0;
    ended = 0;
    RunAnimationEventsToTime(self, anim, &stop);
    if (stop != 0) {
        return;
    }
    if (ApplyAnimationLoopMode(self, &self->time, &self->speed) != 0) {
        switch (anim->endMode) {
        case 0:
            ended = 1;
            break;
        case 1:
            looped = 1;
            self->nextEventIndex = self->speed <= 0.0f ? anim->timedCount : 0;
            break;
        }
    }
    RunAnimationEventsToTime(self, anim, &stop);
    if (stop != 0) {
        return;
    }
    for (i = 0; i < self->rootCount; i++) {
        ClearRootTries(((PlacedObject**)self->roots)[i]);
    }
    if (looped != 0) {
        for (n = (TrackFollowAttachment*)self->list44.head; n != 0; n = (TrackFollowAttachment*)n->w20.lo) {
            AnimationTrack* track = &anim->tracks[n->index];
            if (track->pos != 0 && ((VectorKeyPositionCurve*)track->pos)->closed == 0 && (Attachment*)n == n->owner->positionAttachment) {
                Vec4 pos;
                Vec4 vec;
                n->vt->getPos(n, 0.0f, &pos, &vec);
                n->owner->desc02()->m1D(n->owner, &pos);
                n->owner->desc02()->m20(n->owner, &vec);
            }
            if (track->rot != 0 && ((KeyedRotationCurve*)track->rot)->closed == 0 && (Attachment*)n == n->owner->orientationAttachment) {
                Mat3 rot;
                Vec4 vec;
                n->vt->getRot(n, 0.0f, &rot, &vec);
                n->owner->desc02()->m1E(n->owner, &rot);
                n->owner->desc02()->m21(n->owner, &vec);
            }
        }
    }
    if (ended != 0 || looped != 0) {
        NotifyAnimationPlayerCallbacks(self, ended != 0 ? 5 : 7, self);
    }
}

// Jumps a player to a time: a is absolute (mode 0), added to the current time (mode 1) or to the
// animation's length (modes 2 and 3), and b is the new speed. It then runs the seek events (mode 3)
// or moves the event cursor, re-poses the listed attachments and stops the player if an event asked
// for it.
void SeekAnimationPlayer(AnimationPlayer* self, s32 mode, f32 a, f32 b)
{
    s32 flag = 0;
    f32 t;
    f32 base;
    switch (mode) {
    case 0:
        t = a;
        goto call;
    case 1:
        base = self->time;
        break;
    case 2:
    case 3:
        base = self->anim->length;
        break;
    default:
        goto call;
    }
    t = base + a;
call:
    SetAnimationPlayerSpeed(self, b);
    if (t == self->time) {
        return;
    }
    self->time = t;
    if (mode == 3) {
        RunSeekAnimationEvents(self, self->anim, &flag);
    } else {
        SeekAnimationEventCursor(self);
    }
    ApplyListedPoseSources(self, 0);
    SettleListedPoseSources(self);
    if (flag != 0) {
        StopAnimationPlayer(self);
    }
}

// Applies each pose source of the player's list with the given flag.
void ApplyListedPoseSources(AnimationPlayer* a0, s32 flag)
{
    ListFrame frame;
    TrackFollowAttachment* n = (TrackFollowAttachment*)a0->list44.head;
    while (n) {
        ApplyPoseSource(n, flag);
        n = (TrackFollowAttachment*)n->w20.lo;
    }
}

// Settles the modes of each pose source of the player's list.
void SettleListedPoseSources(AnimationPlayer* self)
{
    ListFrame frame;
    for (TrackFollowAttachment* p = (TrackFollowAttachment*)self->list44.head; p != 0; p = (TrackFollowAttachment*)p->w20.lo) {
        SettlePoseSourceModes(p);
    }
}

// The time on a track's position curve, from t on, at which the point is level with the curve:
// where the point's offset from the curve's position turns from ahead of its direction to
// behind it (or back), unless the point is farther than the radius at t. A step of 0.2 either
// way brackets it, halving narrows the bracket to 0.05, and a linear step between its ends
// gives the time. The time, position and direction found are given where asked.
void RefineNearestAnimationPathTime(f32 end, f32 radius, AnimationTrack* track, PlacedObject* owner, Vec4* point, f32 t, f32* outT,
                   Vec4* outPos, Vec4* outDir)
{
    Vec4 pos;
    Vec4 dir;
    Vec4 d;
    Vec4 loPos;
    Vec4 hiPos;
    Vec4 loDir;
    Vec4 hiDir;
    f32 loT;
    f32 hiT;
    f32 loDot;
    f32 step;
    f32 hiDot;
    f32 dot;
    s32 behind;
    s32 far;

    track->pos->vt->eval(track->pos, owner, t, 1.0f, 0, &pos, &dir);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(*point), Vu0::Q(pos));
    far = radius * radius < Vu0::ToFloat(Vu0::Dot(Vu0::Q(d), Vu0::Q(d)));
    if (!far) {
        dot = Vu0::ToFloat(Vu0::Dot(Vu0::Q(d), Vu0::Q(dir)));
        if (__builtin_fabsf(dot) < 0.0001f) {
            goto done;
        }
        if (0.0f < dot) {
            loDot = dot;
            Vu0::Q(loPos) = Vu0::Q(pos);
            Vu0::Q(loDir) = Vu0::Q(dir);
            step = 0.2f;
            loT = t;
            behind = 0;
        } else {
            Vu0::Q(hiPos) = Vu0::Q(pos);
            hiDot = dot;
            Vu0::Q(hiDir) = Vu0::Q(dir);
            hiT = t;
            step = -0.2f;
            behind = 1;
        }
        t = ClampRange::Of(t + step, 0.0f, end);
        for (;;) {
            track->pos->vt->eval(track->pos, owner, t, 1.0f, 0, &pos, &dir);
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(*point), Vu0::Q(pos));
            dot = Vu0::ToFloat(Vu0::Dot(Vu0::Q(d), Vu0::Q(dir)));
            if (behind != 0) {
                if (0.0f < dot || t == 0.0f) {
                    Vu0::Q(loPos) = Vu0::Q(pos);
                    loT = t;
                    Vu0::Q(loDir) = Vu0::Q(dir);
                    loDot = dot;
                    break;
                }
            } else if (dot < 0.0f || end - 0.0001f < t) {
                hiT = t;
                hiDot = dot;
                Vu0::Q(hiPos) = Vu0::Q(pos);
                Vu0::Q(hiDir) = Vu0::Q(dir);
                break;
            }
            t = ClampRange::Of(t + step, 0.0f, end);
        }
        while (0.05f < hiT - loT) {
            t = (hiT + loT) * 0.5f;
            track->pos->vt->eval(track->pos, owner, t, 1.0f, 0, &pos, &dir);
            Vu0::Q(d) = Vu0::Sub(Vu0::Q(*point), Vu0::Q(pos));
            dot = Vu0::ToFloat(Vu0::Dot(Vu0::Q(d), Vu0::Q(dir)));
            if (0.0f < dot) {
                loT = t;
                loDot = dot;
                Vu0::Q(loPos) = Vu0::Q(pos);
                Vu0::Q(loDir) = Vu0::Q(dir);
            } else {
                Vu0::Q(hiPos) = Vu0::Q(pos);
                hiT = t;
                Vu0::Q(hiDir) = Vu0::Q(dir);
                hiDot = dot;
            }
        }
        f32 span = hiDot - loDot;
        if (0.0001f < __builtin_fabsf(span)) {
            f32 u = ClampRange::Of(hiDot / span, 0.0f, 1.0f);
            t = loT * u + (1.0f - u) * hiT;
            track->pos->vt->eval(track->pos, owner, t, 1.0f, 0, &pos, &dir);
        } else {
            t = loT;
            pos = loPos;
            dir = loDir;
        }
    }
done:
    if (outT != 0) {
        *outT = t;
    }
    if (outPos != 0) {
        *outPos = pos;
    }
    if (outDir != 0) {
        *outDir = dir;
    }
}

// Sets the playing speed to x times the player's speed scale times the animation's output.
void SetAnimationPlayerSpeed(AnimationPlayer* self, f32 x)
{
    self->speed = x * self->speedScale * self->anim->out;
}

// Changes the speed scale while keeping the playing speed in step: the speed is divided by the old
// scale times the animation's output and set again through SetAnimationPlayerSpeed.
void SetAnimationPlayerSpeedScale(AnimationPlayer* self, f32 x)
{
    f32 denom = self->speedScale * self->anim->out;
    f32 r = self->speed;
    if (denom != 0.0f) {
        r = r / denom;
    }
    self->speedScale = x;

    SetAnimationPlayerSpeed(self, r);
}

// Gives every attachment of the player's list the sort key and sorts the attachments of its owner
// again.
void SetAttachmentSortKeys(AnimationPlayer* owner, s32 value)
{
    ListFrame frame;
    TrackFollowAttachment* node = (TrackFollowAttachment*)owner->list44.head;
    while (node != 0) {
        node->key = value;
        SortAttachments(node->owner);
        node = (TrackFollowAttachment*)node->w20.lo;
    }
}

// Sends the notification to the player's object and then calls every callback registered on the
// player.
void NotifyAnimationPlayerCallbacks(AnimationPlayer* self, s32 a1, void* a2)
{
    BaseObject* obj = (BaseObject*)self->object;
    if (obj != 0) {
        obj->desc->m0E(obj, a1, a2);
    }
    QueuedCall* node = self->callbacks;
    while (node != 0) {
        QueuedCall* next = node->next;
        node->notify(node->arg, a1, a2);
        node = next;
    }
}

// Registers a callback (a1 and its argument a2) on the player.
void AddAnimationPlayerCallback(AnimationPlayer* a0, void* a1, void* a2)
{
    AddCallbackNode(a0->anim->world, (ObjectCallback**)&a0->callbacks, a1, a2);
}

// Registers on the player the callback taken from the object a1 points to, with a1 as argument.
void AddAnimationPlayerRecordCallback(AnimationPlayer* a0, PlacedObject** a1)
{
    AddCallbackNode(a0->anim->world, (ObjectCallback**)&a0->callbacks, (void*)(*a1)->link40.prev, a1);
}

// Initialises the collider with anchors (3, 0, 3, 0) and no id.
void InitIdFilterObject(IdFilterObject* self)
{
    InitCollider(self);
    SetColliderAnchors(self, 3, 0, 3, 0);
    self->id = -1;
}

// Copies the collider and, for a root object, sets its contact-pair flags.
void CopyIdFilterObject(IdFilterObject* self, IdFilterObject* src)
{
    CopyCollider(self, src);
    if (self->parent == 0) {
        InitContactPairFlags(self->world, self);
    }
}

// Start of an id filter: either looks up the object its id names (mode 2), or, with no id, takes
// the position of its single child of kind 0x7E as a fixed point (mode 1).
void StartIdFilterObject(IdFilterObject* self)
{
    StartPlacedObject(self);
    if (self->id != -1) {
        self->found = (PlacedObject*)FindFirstObjectByIdMode4(self->world, self->id, self);
        self->mode = 2;
        return;
    }
    ListFrame it;
    ListWalkBegin::Of(&it, &self->children);
    PlacedObject* n = ListWalkNextPlaced::Of(&it);
    if (n == 0 || IsObjectOfKind(n, 0x7E) == 0) {
        g_activeListFrames = (ListFrame*)it.prev;
        return;
    }
    if (ListWalkNextPlaced::Of(&it) != 0) {
        g_activeListFrames = (ListFrame*)it.prev;
        return;
    }
    TransformPointBetweenFrames(self, 0, (Vec4*)&n->link40, &self->pos);
    self->mode = 1;
    n->desc->m03(n);
    g_activeListFrames = (ListFrame*)it.prev;
}

// Updates the collider and then, once a pending target exists, zeroes its velocity and spin and
// puts it at the filter's position (mode 1) or at the found object's position in world space (mode
// 2); the target then becomes the placed target.
void UpdateIdFilterObject(IdFilterObject* self, f32 dt)
{
    Quad4 loc;
    PlacedObject* cur;
    UpdateCollider(self, dt);
    if (self->pendingTarget != 0) {
        self->pendingTarget->desc02()->m20(self->pendingTarget, (Vec4*)&g_zeroVector);
        self->pendingTarget->desc02()->m21(self->pendingTarget, (Vec4*)&g_zeroVector);
        switch (self->mode) {
        case 1:
            self->pendingTarget->desc02()->m1D(self->pendingTarget, &self->pos);
            break;
        case 2: {
            PlacedObject* node = self->found;
            TransformPointBetweenFrames((PlacedObject*)node->parent, 0, (Vec4*)&node->link40, (Vec4*)&loc);
            self->pendingTarget->desc02()->m1D(self->pendingTarget, (Vec4*)&loc);
            break;
        }
        }
        cur = self->pendingTarget;
        self->pendingTarget = 0;
        self->placedTarget = cur;
    }
}

// True when the filter lets key through: the collider can contact it, its id is in the filter's
// object id list, or it is of one of the classes in its class id list.
s32 TestIdFilterMatch(IdFilterObject* self, Collider* key)
{
    s32 hit;
    s32 i;
    s32 j;

    if (TestCollidersMayContact(self, key) != 0) {
        return 1;
    }
    for (i = 0; i < self->objectIds.count; i++) {
        if (MatchesObjectId(key, self->objectIds.items[i]) != 0) {
            break;
        }
    }
    if (i < self->objectIds.count) {
        hit = 1;
        goto tail;
    }
    for (j = 0; j < self->classIds.count; j++) {
        if (IsObjectOfKind(key, self->classIds.items[j]) != 0) {
            break;
        }
    }
    hit = j < self->classIds.count;
tail:
    if (self->acceptsListed != 0) {
        return hit;
    }
    return hit ^ 1;
}

void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec4* in, Vec4* out);

// Called when something touches the filter object: fires script events 2 and 0x1D (with the other
// party's data), then, when it has a mode and no pending target, checks the distance from the
// placed target to the filter's location (its own position or a found node's).
void HandleIdFilterObjectContact(IdFilterObject* self, u8* table, s32 which)
{
    Vec4 loc;
    u8* arg;
    TriggerScriptEvent(self, 2, 0, 0);
    arg = table + ((1 - which) << 6) + 4;
    TriggerScriptEvent(self, 0x1D, 1, &arg);
    if (self->mode != 0) {
        if (self->pendingTarget == 0) {
            if (self->placedTarget != 0) {
                s32 close;
                switch (self->mode) {
                case 1:
                    *(Quad16*)&loc = *(Quad16*)&self->pos;
                    break;
                case 2: {
                    PlacedObject* node = self->found;
                    TransformPointBetweenFrames((PlacedObject*)node->parent, 0, (Vec4*)&node->link40, &loc);
                    break;
                }
                }
                f32 d = Vu0::ToFloatMoved(Vu0::Length(Vu0::Sub(Vu0::Q(self->placedTarget->v140), Vu0::Q(loc))));
                close = d <= ((Collider*)self->placedTarget)->radius3D0 * 2.0f;
                if (close) {
                    return;
                }
            }
            self->pendingTarget = *(PlacedObject**)(table + ((1 - which) << 6));
        }
    }
}

// Appends an object id to the filter's list of object ids.
void AddIdFilterObjectId(IdFilterObject* a0, s32 a1)
{
    a0->objectIds.items[a0->objectIds.count++] = a1;
}

// Appends a class id to the filter's list of class ids.
void AddIdFilterClassId(IdFilterObject* obj, s32 value) { obj->classIds.items[obj->classIds.count++] = value; }

// Clears the reader and sets its buffer to value rounded up to 64 bytes, with no file handle (-1).
StreamReader* InitStreamReader(StreamReader* obj, u8* value)
{
    obj->sector = 0;
    obj->buffer = ((sptr)value + 0x3F) & -64;
    obj->fileHandle = -1;
    obj->pendingDest = 0;
    obj->readyStart = 0;
    obj->total = 0;
    obj->remaining = 0;
    obj->pendingLength = 0;
    obj->usedLength = 0;
    obj->readyLength = 0;
    return obj;
}

// Closes the reader and, when bit 0 of flags is set, frees it.
void DestroyStreamReader(StreamReader* self, s32 flags)
{
    CloseStreamReader(self);
    if (flags & 1) FreeObjectMemory(self);
}

// Opens the sector stream from a pair of (first sector, byte count).
s32 OpenSectorStreamRange(StreamReader* self, KeyId* pair)
{
    return OpenSectorStream(self, pair->first, pair->second);
}

LINKER_REMNANT(func_0012FD98);

// Starts a stream of a bytes' worth of disc data beginning at sector a1 (total a2) and starts
// reading its first chunk; always returns 1.
s32 OpenSectorStream(StreamReader *self, s32 a1, s32 a2) {
    self->sector = a1;
    sptr t = self->buffer;
    self->total = a2;
    self->remaining = a2;
    self->sourceKind = 1;
    self->readyStart = t;
    self->readyLength = 0;
    self->usedLength = 0;
    StartChunkRead(self);
    return 1;
}

// Closes the stream's source: the file for kind 0, or the pending disc read (cancelled and
// committed) for kind 1; the kind becomes -1.
void CloseStreamReader(StreamReader* a0)
{
    switch (a0->sourceKind) {
    case 0:
        if (a0->fileHandle >= 0) CloseFile(a0->fileHandle);
        a0->fileHandle = -1;
        break;
    case 1:
        if (IsReadPending(a0)) {
            SyncDiscNCommand(0);
            CommitChunk(a0);
        }
        a0->sector = 0;
        break;
    }
    a0->sourceKind = -1;
}

// Starts reading the next chunk (at most 0x4000 bytes) of the stream into the half of its buffer
// that is not in use, from a file or from a disc sector by source kind; does nothing while a read
// is pending or nothing remains.
void StartChunkRead(StreamReader* self)
{
    if (IsReadPending(self) != 0) {
        return;
    }
    s32 size = self->remaining;
    if (size == 0) {
        return;
    }
    s32 clamp = 0x4000;
    if (!(size > 0x3FFF)) {
        clamp = size;
    }
    sptr base = self->buffer;
    if (self->readyStart == base) {
        base += 0x4000;
    }
    self->pendingLength = clamp;
    self->pendingDest = base;
    switch (self->sourceKind) {
    case 0:
        ReadFile(self->fileHandle, (void*)base, clamp);
        break;
    case 1:
        StartLowLevelDiscReadUntilAccepted(self->sector, (s32)((u32)(clamp + 0x7FF) >> 11), (void*)base);
        break;
    }
}

s32 IsReadPending(StreamReader* a0)
{
    return a0->pendingLength != 0;
}

// Checks whether the stream reader's pending chunk read has finished (file control or disc sync, by
// source kind) and returns true when it has; an error from the disc cancels the pending read.
s32 PollChunkRead(StreamReader* a0)
{
    s32 r = 0;
    s32 done = 0;
    if (a0->readyLength == a0->usedLength && IsReadPending(a0)) {
        switch (a0->sourceKind) {
        case 0: {
            s32 tmp;
            done = ControlFile(a0->fileHandle, 1, (u32*)&tmp);
            r = tmp == 0;
            break;
        }
        case 1:
            r = SyncDiscNCommand(1) == 0;
            if (r) done = GetDiscError();
            break;
        }
    }
    if (done) {
        a0->pendingLength = 0;
        a0->pendingDest = 0;
        r = 0;
    }
    return r;
}

// When the pending read has finished, makes its data the ready chunk: advances the sector, lowers
// the remaining count and resets the used length.
void CommitChunk(StreamReader* self)
{
    if (PollChunkRead(self) == 0) {
        return;
    }
    if (self->sourceKind == 1) {
        self->sector += self->pendingLength / 2048;
    }
    s32 v = self->pendingLength;
    self->remaining -= v;
    self->readyLength = v;
    self->readyStart = self->pendingDest;
    self->pendingLength = 0;
    self->pendingDest = 0;
    self->usedLength = 0;
}

// Keeps a stream reader going: for a file source starts the next chunk and then commits the
// finished one, for a disc source commits first and then starts.
void PumpStreamReader(StreamReaderWindow* self)
{
    switch (self->sourceKind) {
    case 0:
        StartChunkRead((StreamReader*)self);
        CommitChunk((StreamReader*)self);
        break;
    case 1:
        CommitChunk((StreamReader*)self);
        StartChunkRead((StreamReader*)self);
        break;
    }
}

void ConsumeStreamBytes(StreamReaderWindow* a0, s32 a1)
{
    a0->usedLength += a1;
}

// True when key is the id of the object's class or of any of its parent classes.
s32 IsObjectOfKind(BaseObject* list, s32 key)
{
    const BaseObjectDescriptor* node = list->desc;
    while (node != 0) {
        if (node->id == key) {
            return 1;
        }
        node = (const BaseObjectDescriptor*)node->parent;
    }
    return 0;
}

// Gives the object a keyed list if it has none and registers it as a root of the mark stacks.
void EnsureKeyedList(BaseObject* self)
{
    if (self->keyedList == 0) {
        void* v = NewKeyedList();
        self->keyedList = v;
        AddMarkRootList((MarkStacks*)g_markStacks, (R11B008List*)v);

    }
}

// A property getter (func_00109488 installs it): the object's class id.
void GetObjectClassId(BaseObject* self, s32* out)
{
    *out = self->desc->id;
}
