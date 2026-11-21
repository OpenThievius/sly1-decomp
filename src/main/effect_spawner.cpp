// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x1549C8 to 0x15AAE0 (its .rodata from 0x24A120, its .data from 0x261F70): the
// effect spawner (class 0x50) and its spawn helpers, the member objects (classes 0x77 to 0x7A)
// and their delayed messages, the crossfade animator, the colour fade, the object gathering by
// id and the scaling volume (class 0x60). Its start is exact; it ends where the object cycler
// begins (object_cycler.cpp), a cut by role only, which that file's head explains. The spawner
// and the member objects share the spawn record and its helpers, so they are not cut apart; the
// smaller groups after them could be files of their own. Its name is ours, after its largest
// family, the effect spawner, whose spawn record the member objects share.
#include "common.h"
#include "screen_element.h"
#include "asm_functions.h"
#include "effect_spawner.h"
#include "attached_set.h"
#include "switched_collider.h"
#include "vu0.h"
#include "asm_func.h"
#include "system.h"
#include "effect_owner.h"
#include "effect.h"
#include "shapes.h"
#include "active_set_solver.h"
#include "list_iter.h"
#include "owned_record.h"
#include "world_listed_object.h"
#include "transform_object.h"
#include "object_group.h"
#include "cursor_animator.h"
#include "object_cycler.h"
#include "scaling_volume.h"
#include "world.h"
#include "globals.h"
#include "deferred_request.h"
#include "color_fade.h"
#include "base_object.h"
#include "packet_writer.h"
#include "font.h"
#include "render_frame.h"
#include "text_reader.h"
#include "layout_137228.h"
#include "scope_marker.h"
#include "vu0.h"
#include "object_finder.h"
#include "list_walk.h"
#include "playing_sound.h"
#include "functions/active_set_solver.h"
#include "functions/anim_record.h"
#include "functions/collider.h"
#include "functions/display.h"
#include "functions/effect.h"
#include "functions/font.h"
#include "functions/group_marker.h"
#include "functions/matrix.h"
#include "functions/object_cycler.h"
#include "functions/on_off_object.h"
#include "functions/path_curve.h"
#include "functions/placed_object.h"
#include "functions/point_graph.h"
#include "functions/render_frame.h"
#include "functions/sound_system.h"
#include "functions/state_walker.h"
#include "functions/system_calls.h"
#include "functions/texture_upload.h"
#include "functions/world_listed_object.h"
struct CappedWordList;
struct EffectOwnerSlot;
struct PlacedObject;
struct SpawnSetup;
struct SpawnTargetOwner;
struct SpawnTargetRecord;

struct BumpAllocator;

struct Mat3;
struct Vec4;


// Types other files define, named by the parameters of their functions declared here.
struct ScaledTransform;



void SetEffectSpawnerActiveForever(EffectSpawner* self);
void SetEffectSpawnerInactive(EffectSpawner* self);

EffectSpawnerRecord* GetOwnSpawnRecord(EffectSpawner* self, s32 mode);
void SetSpawnRecordKind(EffectSpawnerRecord* self,s32 kind);

struct RecordMember;
struct TransformRecord;
TransformRecord* GetOwnedSpawnRecord(RecordMember* self, s32 own);
void SetSpawnRecordKind(EffectSpawnerRecord* self,s32 kind);

// The message SendPointEventToWorldListener sends (kind 12): a point and a float.
struct PointEventMessage {
    s32 kind;
    u8 pad0[0x20 - 4];
    Quad16 q;
    s32 zero;
    f32 f;
    u8 pad1[0x50 - 0x38];
};



extern f32 g_gameTime;

struct SpawnSetup {
    sptr out[4];
    s32 flag;
    s32 pad[3];
    sptr pair[2];
    u8 tail[0x18];
};

void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GenerateSpawnArrays(s32 n, void* b, sptr* out);

struct StreamWord {
    s32 value;
};


void* AllocateFrontMemory(s32 size);
struct BufferedStream;
s32 ReadBufferedU8(BufferedStream* self);
StreamWord ReadBufferedU32(BufferedStream* self);

void* AllocateFrontMemory(s32 size);
void InitSpawnRecord(void* mem);
s32 ReadBufferedS8(BufferedStream* self);
void ReadSpawnMesh(void* p, void* other);
u16 ReadBufferedU16(BufferedStream* self);
EffectSpawnerRecord* GetOwnSpawnRecord(EffectSpawner* self, s32 mode);
struct CappedWordList;
void ReadCappedWordList(CappedWordList* self, s32 count, void* unused, void* src);


struct SpawnerLinkedObject { u8 pad00[0x18]; void* target; u8 pad1C[0x18]; s32 value; };

EffectSpawnerRecord* GetOwnSpawnRecord(EffectSpawner* self, s32 mode);
void ResolveSpawnRecordTargets(SpawnTargetRecord* rec, SpawnTargetOwner* owner);
void AppendQueuedCall(World* self, void* code, void* arg, s32 c, s32 d);

void* CopyToFrontMemory(s32 size, void* owner);

extern f32 g_gameTime;




s32 IsEffectSpawnerActive(EffectSpawner* self);

void SetListLinkOffset(ObjectList* self, s32 offset);

struct RangeEmitter;
void AddRangeEntry(RangeEmitter* self, s32 a1, s32 a2, f32 f12, f32 f13, f32 f14, f32 f15, void* owner);

struct LookSource;
struct WorldListedObject;
f32 RandomFloatInRange(f32,f32);

extern "C" void* FillMemory(void* p, s32 value, s32 size);



void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateBackMemory(s32 size);
void CopyMemory(void* dst, void* src, u32 size);

struct EffectOwnerSlot { s32* particleOwnerCache; s32* effectOwnerCache; void* ownerArgument; };
f32 RandomFloatInRange(f32 a, f32 b);
s32 IsListEmpty(ObjectList* p);

typedef void (*VFn)();

struct SpawnSpan {
    f32 lo;
    f32 hi;
};

struct SpawnRing {
    s32 count;
    f32 step;
    f32 rate;
    f32 phase;
    f32 out10;
};

f32 WrapAngle(f32 x);
f32 RandomFloatInRange(f32 a, f32 b);


typedef void (*BroadcastFn)(void* self, void* frame);


struct BroadcastMessage {
    s32 kind;
    u8 pad0[0x1C];
    Quad16 pos;
    f32 value;
    s32 f34;
    void* object;
    u8 pad1[0xC];
};

struct BroadcastRecord { u8 pad0[0x120]; s32 f120; u8 pad1[0x8C]; s32 messageMode; };

struct KeyedObject { BroadcastFn* vtbl; u8 pad0[0x8C]; BroadcastRecord* f90; };

struct KeyedObjectList { u8 pad0[0x90]; s32 count; KeyedObject* items[1]; };

struct KeyedWorldView { u8 pad0[0x1CE8]; KeyedObjectList* list; };

struct __attribute__((aligned(16))) SpawnBlock { Quad16 q[8]; };
struct __attribute__((aligned(16))) SpawnTail { Quad16 q[4]; };
extern "C" void* FillMemory(void* p, s32 value, s32 size);
struct SpawnFlags { s32 z; s32 b; s32 c; SpawnFlags() { FillMemory(this, 0, sizeof(*this)); } };
struct __attribute__((aligned(16))) SpawnRecord { u8 pad0[0x20]; Quad16 self_copy; u8 pad1[0x30]; Quad16 a1_copy; u8 pad2[0x30]; SpawnBlock blk; s32 f120; u8 pad3[0x8C]; SpawnTail tail; u8 pad4[0x10]; };

void InitSpawnRecord(void* mem);
void SpawnEffectsFromRecord(s32 count, EffectSpawnerRecord* rec, void* flags);


struct BriefEffectParams { u8 pad0[0xC]; s32 fC; };
struct BriefEffectSource { u8 pad0[0x278]; BriefEffectParams* f278; };
typedef void (*EffectStartFn)(Effect* self, void* a, s32 z, f32 f);


void StartObject(BaseObject* self);

struct EmptyMessage { u8 data[0x50]; };


struct TwoVectorMessage {
    s32 a;
    s32 b;
    u8 pad0[8];
    Quad16 q1;
    Quad16 q2;
    f32 x;
    f32 y;
    u8 pad1[0x50 - 0x38];
};

void CopyObjectData(BaseObject* self, BaseObject* src);
MemberObject* CreateObjectCopy(BaseObject* self, World* world, BaseObject* parent);

void SetCrossfadeMode(CrossfadeAnimator* self, s32 mode);

s32 IsObjectAttached(BaseObject* self);
void RemoveObjectNodeFromWorld(WorldObjectNode* self);
extern PackedFloatPair g_cyclerTargetRadiusRange;
extern PackedFloatPair g_cyclerTargetHeightRange;
extern PackedFloatPair g_cyclerTangentRadiusRange;
extern PackedFloatPair g_cyclerTangentHeightRange;
extern PackedFloatPair g_cyclerCheckDelayRange;
extern PackedFloatPair g_cyclerHoldExtraRange;
extern PackedFloatPair g_cyclerAdvanceDelayRange;
extern PackedFloatPair g_cyclerWrapDelayRange;
extern PackedFloatPair g_cyclerMessageIntervalRange;

void AppendToList(ObjectList* self, void* item);

struct MemberTargetObject;

// A message held back by SendMessageAfterDelay (a slot of the world's pool at +0x1BD0, in its
// list at +0x1BDC, linked at +0x64): the receiver, the 0x50-byte message, the time it is due.
#include "delayed_message_body.h"
struct QueuedDelayedMessage { void* owner; u8 pad0[0xC]; DelayedMessageBody body; f32 due; u8 link[8]; /* 0x64: the link in World::list1BDC */ };

extern f32 g_gameClock[];

struct ListLink;
void ClearListLinks(ListLink* p);
void AppendToList(ObjectList* self, void* item);
void HandleSpawnMessage(void* self, void* body);



void* CreateTypedRecord(s32 index, void* a1, BaseObject* a2, s32 a3, s32 a4);
void CopyMemory(void* dst, void* src, u32 size);

struct MemberTargetObject {
    u8 pad0[0x18];
    void* target;
    u8 pad1[0x20 - 0x1c];
    s32 f20;
    u8 pad2[0x34 - 0x24];
    s32 value;
    u8 pad3[0x7c - 0x38];
    MemberTargetObject* f7c;
};

void ResolveSpawnRecordTargets(SpawnTargetRecord* rec, SpawnTargetOwner* owner);

extern f32 g_gameTime;
f32 RandomFloatInRange(f32 a, f32 b);

extern f32 g_gameTime;
f32 RandomFloatInRange(f32 a, f32 b);


void* AllocateZeroedFrontMemory(s32 size);
void InitSpawnRecord(void* p);
extern s32 g_objectCyclerStartLinks[6];

f32 RandomFloatInRange(f32 a, f32 b);



void AppendToList(ObjectList* self, void* item);



void RemoveFromList(ObjectList* list, void* item);

extern f32 g_frameDt;
struct RampProfile;

f32 ApproachValueWithRamp(f32 x, f32 y, f32 z, RampProfile* k, f32* out);
struct ScaledDrawFrame { Quad16 q0; u8 pad1[0x30]; Quad16 m40[4]; u8 pad2[0x10]; Quad16 m90[4]; };

Mat4A MultiplyMatrices(const Mat4A& a, const Mat4A& b);


struct ScreenFillPacket { u8 buf[0x2C0]; s32 value; };

void BeginDmaTag(PacketWriter* self);
void WriteVifDirect(PacketWriter* self, s32 n, void* buf, s32 flag);
void CloseDmaTag(PacketWriter* self);

extern f32 g_gameTime;


void AppendToList(ObjectList* self, void* item);




void AddRangeEntry(RangeEmitter* self, s32 a1, s32 a2, f32 f12, f32 f13, f32 f14, f32 f15, void* owner);

struct __attribute__((aligned(16))) GroupForwardMessage {
    s32 f0;
    u8 pad0[0x10 - 0x4];
    Quad16 f10;
    Quad16 f20;
    u8 pad1[0x50 - 0x30];
};


// NEAR: the last float zero (f16) is scheduled into the jal delay slot instead of before the integer argument moves.


s32 IsInList(ObjectList* self, void* item);
void RemoveFromList(ObjectList* list, void* item);
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec4* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

// NEAR: the last float zero (f16) is scheduled into the jal delay slot instead of before the integer argument moves.


void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec4* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

// The colour UpdateColorFade blends, word-aligned, and its request: DeferredRequest's layout
// with that colour at +0x60 (DeferredRequest's Rgba4 would copy it unaligned).
struct __attribute__((aligned(4))) FadeColor { u8 c[4]; };
struct FadeEffectRequest { void* fn; f32 f; s32 mode; u8 pad[0x54]; FadeColor col; u8 pad2[0x1C]; };

extern s32 g_displayMode;
extern f32 g_gameTime;
void RemoveFromList(ObjectList* list, void* item);
void DrawScreenFill(u8* a0);

struct RangeEntry {
    s32 a;
    s32 b;
    f32 c;
    f32 d;
    f32 e;
    f32 f;
    u8 pad0[0x10];
};

struct RangeEmitter {
    s32 kind;
    u8 pad0[0xC];
    s32 count;
    RangeEntry* entries;
};

void* AllocateZeroedFrontMemory(s32 bytes);


// A cell of a group's list (ObjectGroup::cells): the object and the next cell.

s32 ReadBufferedS16(BufferedStream* self);
void* CreateTypedRecord(s32 index, void* a1, BaseObject* a2, s32 a3, s32 a4);

struct ClassKindNode { ClassKindNode* next; s32 value; };

extern u8 g_classDescriptorTable[];

s32 IsObjectAttached(BaseObject* self);

typedef int Quadword128 __attribute__((mode(TI)));

extern f32 g_gameClock[];

s32 FindObjectCyclerGroundPoint(ObjectCycler* self, Quadword128* out);
f32 RandomFloatInRange(f32 a, f32 b);
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec4* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);


extern f32 g_gameClock[];


void HandleSpawnMessage(void* a, void* b);
void RemoveFromList(ObjectList* list, void* item);


// A walk of a list that RemoveFromList keeps valid: the frame is pushed on g_activeListFrames
// (list_iter.h) and each step reads the next item through the link.

template <class T> struct NextInList {
    static T* Of(ListFrame* it)
    {
        T* obj = *(T**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};
extern s32 g_objectCyclerLoadLinks[6];

struct BufferedStream;
void FindOrBuildMemberGroup(void** out, void* self);
s32 IsInList(ObjectList* self, void* item);
void RemoveFromList(ObjectList* list, void* item);

#include "cycler_draw_params.h"
extern f32 g_gameTime;
extern f32 g_cyclerShrinkCurve[4];
extern f32 g_cyclerGrowCurve[4];
extern f32 g_unitRange[];

s32 IsObjectAttached(BaseObject* self);
s32 IsClassOfKind(s32 index, s32 value);
void CollectObjectByMode(PlacedObject* obj, s32 kind, s32 all, s32 zero, PlacedObject* root, s32 max,
                   s32* countOut, PlacedObject** found, s32* minOut);



// An entry of a GCC 2.95 vtable as this file defines D_0024A220 (the font table).
#include "vtable_entry.h"
struct FloatPair2 { f32 x; f32 y; };
extern const VtableEntry g_fontMethods[22];
void* AllocateObjectMemory(u32);

extern Font* g_fonts[];
extern Font* g_defaultFont;



// The packet memory a GIF writer fills: quadwords.
typedef u64 UQuadword128 __attribute__((mode(TI)));

extern u8 g_groupMicroprogram[];
extern u8 g_groupMicroprogramEnd[];

void* InitGifPacket(void* p);
void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);
void BeginGifTag(void* p, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(void* p, s32 a, s32 b);
void EndGifPacket(void* p);
void WriteVifFlush(PacketWriter* b);
void WriteVifDirectFromWriter(PacketWriter* a0, PacketWriter* a1);
void AddDmaEndTag(PacketWriter* self);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);



void CloseDmaTag(PacketWriter* self);
void BeginDmaTag(PacketWriter* self);

void BeginGifTag(void* obj, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(void* obj, s32 tag, s64 value);
void BeginGifRegListTag(void* obj, s32 tag, s64 value);

extern Font* g_defaultFont;

void CopyMemory(void* dst, void* src, u32 size);


extern s32 g_vif1Channel;
extern s32 g_gifChannel;



void* InitGifPacket(void* p);
void* InitPacketWriter(PacketWriter* self);



extern f32 g_gameClock[];

typedef s32 (*ObjectFilterFn)(void* a, void* b);

struct GroundCandidate;
struct GroundFilterContext;
void PushBackMemoryMark(void* self);
Collider* FindNearestSpanObject(s32 flags, Vec4* a1, Vec4* a2, s32 count, Collider** list, ColliderSpan* out);
void PopBackMemoryMark(void);
void GatherCollidersInSphere(World* world, Collider* skip, f32 radius, Vec4* center, s32 (*filter)(void*, Collider*), void* arg, s32* count, Collider*** out);


void BeginGifTag(void* obj, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(void* obj, s32 a, s32 b);
void EndGifPacket(void* obj);
void AddDmaEndTag(PacketWriter* self);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);

void ClearList(ObjectList* p);
extern "C" s32 PostSemaphore(s32 sema);

extern ObjectList g_deferredReleaseListA;
extern ObjectList g_deferredReleaseListB;
extern ObjectList g_deferredReleaseListC;
extern s32 g_buildFrameData;
extern s32 g_frameReadySemaphore;



extern s32 g_drawFrameData;
extern void* g_maskedImagesPacket;
extern s32 g_gifChannel;

struct DmaChannel;
extern "C" void StartDmaChain(DmaChannel* ch, void* tadr);







extern s8 g_fontEscapeKeys[];
extern Font* g_fonts[];


// NEAR: the first load of self->p54 goes to $v0 (retail $v1), so two
// pointer loads differ in register choice; everything else matches.

#include "font_frame.h"
PacketWriter* InitGifPacket(PacketWriter* p);
void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);
void DetachPacketBufferCopy(PacketWriter* self, s32* count, u8** begin, void** out, s32 flags);

// Matched: for loop over i with D_00262264 + i * 0x88.

extern s32 g_fontCount;
extern u8* g_fontRecords;



void AddGifRegListFloat(PacketWriter* s, u32 tag, f32 value);
void AddGifUvRegListEntry(PacketWriter* s, s32 a, s32 b);
void AddGifXyzfRegListEntry(PacketWriter* s, s32 a, s32 b, s32 c, s32 d);





extern u32 g_packetBufferMemory[];
extern u8 g_codeChecksumSize[];
extern s32 g_codeChecksumFailed;

extern s32 g_frameDoneSemaphore;
extern volatile s32 g_renderThreadWaiting;
extern void* g_drawingFrame;
extern s32 g_fieldOffsetMode;

extern "C" s32 AwaitSemaphore(s32 sema);




void ReadBufferedStreamBytes(BufferedStream* self, s32 remaining, void* out);
void* AllocateFrontMemory(s32 n);
extern s32 g_glyphUOffset;
extern s32 g_glyphVOffset;

void BeginGifTag(PacketWriter* s, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(PacketWriter* s, s32 a, u64 b);
void BeginGifRegListTag(PacketWriter* s, s32 a, u64 b);
void AddGifRegListFloat(PacketWriter* s, u32 tag, f32 value);
void AddGifUvRegListEntry(PacketWriter* s, s32 a, s32 b);
void AddGifXyzfRegListEntry(PacketWriter* s, s32 a, s32 b, s32 c, s32 d);

// NEAR: CRC table loop: retail keeps inner counter k in v1 and n*4 in a1; ours swaps them (5 insns)

extern u8 g_vifPacketMemory[], g_renderFrameDataMemory[];
extern s32 g_frameReadySemaphore;
extern s32 g_frameDoneSemaphore;
extern s32 g_mainAndRenderThreads[];
void SetListLinkOffset(ObjectList* self, s32 value);
void AddInterruptHandler(s32 a0, void (*fn)(void), s32 a2);
s32 CreateLockSemaphore(s32 initCount, s32 maxCount);
void func_0015E678(void);



extern s32 g_frameReadySemaphore;
extern s32 g_frameDoneSemaphore;
extern u32 g_renderFrameIndex;
extern s32 g_vif1Channel;
extern s32 g_gifChannel;
extern s32 g_fieldOffsetMode;

extern "C" s32 AwaitSemaphore(s32 sema);
extern "C" s32 WaitDmaChannel(DmaChannel* ch, s32 mode, s32 timeout);




s32 IsListEmpty(ObjectList* l);
void RemoveFromList(ObjectList* list, void* item);
void AppendToList(ObjectList* self, void* item);
void ClearList(ObjectList* l);



typedef struct StringLayout StringLayout;
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;




// Inline text codes: ~RRGGBB / ~. colour, &<id> / &. font, ^<d><d> / ^. scale.




void DrawFontQuad(Font* self, u32 color, f32 x0, f32 y0, f32 x1, f32 y1,
                   f32 u0, f32 v0, f32 u1, f32 v1, PacketWriter* s);
extern void* g_drawingFrame;
extern s32 g_frameReadySemaphore;
extern volatile s32 g_renderThreadWaiting;

extern s32 g_frameDoneSemaphore;
extern s32 g_nextBuildFrameIndex;
extern s32 g_buildFrameData;

extern "C" s32 AwaitSemaphore(s32 sema);
void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);
void BeginDmaTag(PacketWriter* self);

// The spawn record (SpawnRecord above, 0x200 bytes) as InitSpawnRecord fills it: nine vectors,
// an effect's spawn block (EffectSpawnData, the block SpawnBlock is a view of) and a table of thirteen
// quadwords.
struct SpawnVectors {
    Quad16 q[9];
};
struct SpawnTable {
    Quad16 q[13];
};
struct SpawnRecordParts {
    s32 f0;                 // 0x00
    SpawnVectors vectors;   // 0x10
    EffectSpawnData block;            // 0xA0
    SpawnTable table;       // 0x120
    u8 pad1F0[0x200 - 0x1F0];
};
typedef char check_SpawnRecordParts[sizeof(SpawnRecordParts) == 0x200 ? 1 : -1];
extern SpawnTable g_spawnRecordDefaults;

// The vectors and the block are built once each, as function-local statics with brace
// initialisers: a vector copied from a global makes each run at run time, through a temporary
// (docs/toolchain/large-functions.md, "A brace initialiser's union member is a CLOBBER").
void InitSpawnRecord(void* mem)
{
    SpawnRecordParts* self = (SpawnRecordParts*)mem;
    static SpawnVectors vectors = { {
        { { 0, 0, 0, 0 } }, *(Quad16*)&g_zeroVector, { { 0, 0, 0, 0 } }, { { 0, 0, 0, 0 } }, { { 0, 0, 0, 0 } },
        *(Quad16*)&g_unitXVector, { { 0, 0, 0, 0 } }, { { 0, 0, 0, 0 } }, *(Quad16*)&g_zeroVector
    } };
    static EffectSpawnData block = {
        { 750.0f, 750.0f, 1.0f }, { 0.0f, 0.0f, -1500.0f }, { -1.0f, 0.0f, 0.0f }, *(Quad16*)&g_unitZVector, 0.0f, 0.0f, 0.0f, 200,
        { 1.0f, 1.0f, 0.0f }, { { 0, 0, 0, 0 } }, { 1.0f, 0.0f, -1.0f }
    };
    FillMemory(self, 0, 0x200);
    self->f0 = 1;
    self->vectors = vectors;
    self->block = block;
    self->table = g_spawnRecordDefaults;
}

// Initialises the placed object and puts every id and counter at its unset value (-1), with both
// delays at 10 and the list link offset at 0x320.
void InitEffectSpawner(EffectSpawner* self)
{
    InitPlacedObject(self);
    self->remaining=-1;
    self->delayMax=10.0f;
    self->id2F8[0]=-1;
    self->id2F8[1]=-1;
    self->id304=-1;
    self->id300=-1;
    self->id30C=-1;
    self->mode=-1;
    self->delayMin=10.0f;
    self->activeUntil=-1.0f;
    self->sharedId=-1;
    SetListLinkOffset((ObjectList*)self->list314,0x320);
}

f32 ReadBufferedFloat(BufferedStream* r);
struct BufferedStream;
void ReadBufferedVector3(BufferedStream* src, void* dst);

struct MeshTriangle {
    s32 corner[3];          // 0x00
    f32 area;               // 0x0C
};
struct MeshData {
    s32 vertexCount;        // 0x00
    Vec4* vertices;        // 0x04
    s32 triangleCount;      // 0x08
    MeshTriangle* triangles;    // 0x0C
    Vec4* normals;         // 0x10
    f32 totalArea;          // 0x14
    u8 pad18[0x20 - 0x18];
    Vec4 extent;           // 0x20
};

// Reads a mesh for spawning on its surface from the stream: the vertices, then each triangle with
// its three vertex indexes and area (the areas are summed, apparently so a random point can be
// chosen by area), and builds each triangle's normal.
void ReadSpawnMesh(void* p, void* other)
{
    MeshData* m = (MeshData*)p;
    s32 i;
    m->vertexCount = ReadBufferedU16((BufferedStream*)other);
    m->vertices = (Vec4*)AllocateFrontMemory(m->vertexCount << 4);
    m->normals = (Vec4*)AllocateZeroedFrontMemory(m->vertexCount << 4);
    for (i = 0; i < m->vertexCount; i++) {
        ReadBufferedVector3((BufferedStream*)other, &m->vertices[i]);
    }
    m->triangleCount = ReadBufferedU16((BufferedStream*)other);
    m->triangles = (MeshTriangle*)AllocateFrontMemory(m->triangleCount << 4);
    m->totalArea = 0.0f;
    for (s32 k = 0; k < m->triangleCount; k++) {
        MeshTriangle* t = &m->triangles[k];
        for (i = 0; i < 3; i++) {
            t->corner[i] = ReadBufferedU16((BufferedStream*)other);
        }
        t->area = ReadBufferedFloat((BufferedStream*)other);
        m->totalArea = m->totalArea + t->area;
        u128 first = Vu0::Q(m->vertices[t->corner[0]]);
        u128 e1 = Vu0::Sub(Vu0::Q(m->vertices[t->corner[1]]), first);
        u128 e2 = Vu0::Sub(Vu0::Q(m->vertices[t->corner[2]]), first);
        u128 n = Vu0::Cross(e1, e2);
        for (i = 0; i < 3; i++) {
            Vec4* v = &m->normals[t->corner[i]];
            Vu0::Q(*v) = Vu0::Add(Vu0::Q(*v), n);
        }
    }
    ReadBufferedVector3((BufferedStream*)other, &m->extent);
    for (i = 0; i < m->vertexCount; i++) {
        Vu0::Q(m->normals[i]) = Vu0::NormalizeOr(Vu0::Q(m->normals[i]), Vu0::Q(g_unitZVector));
    }
}

// Reads a source byte and count words from the stream, keeping the first 32 at most.
void ReadCappedWordList(CappedWordList* self, s32 count, void* unused, void* src)
{
    s32 limit = 31;
    s32 cap = (limit < count) ? 32 : count;
    self->cap = cap;
    self->items = (U32P*)AllocateFrontMemory(cap * 4);
    self->source = ReadBufferedU8((BufferedStream*)src);
    for (s32 i = 0; i < count; i++) {
        StreamWord tmp = ReadBufferedU32((BufferedStream*)src);
        if (i < self->cap) {
            self->items[i] = *(U32P*)&tmp;
        }
    }
}

// Loads an effect spawner from the stream: its record, the placed object's data, an optional path
// curve (index byte, -1 for none), a mesh for kind 4 and the capped word list.
void LoadEffectSpawner(EffectSpawner* self, BufferedStream* count)
{
    void* mem = AllocateFrontMemory(0x200);
    self->rec = (EffectSpawnerRecord*)mem;
    InitSpawnRecord(mem);
    LoadPlacedObject(self, count);
    s32 index = ReadBufferedS8(count);
    if (index != -1) {
        PathCurve* obj = CreatePathCurve(index);
        self->rec->curve20 = obj;
        void (*fn)(PathCurve* self, void* stream) = obj->vt->m00;
        if (fn != 0) {
            fn(obj, count);
        }
    }
    if (self->rec->kind == 4) {
        ReadSpawnMesh(&self->rec->curve20, count);
    }
    s32 n = ReadBufferedU16(count);
    if (n != 0) {
        EffectSpawnerRecord* b = GetOwnSpawnRecord(self, 1);
        ReadCappedWordList(&b->words130, n, self, count);
    }
}

// Copies the placed object and counts one more user on the shared spawn record.
void CopyEffectSpawner(EffectSpawner* self, EffectSpawner* src)
{
    CopyPlacedObject(self, src);
    self->rec->uses++;
}

// Calls slot 15 with the record's target, which looks like making the spawner a child of it.
void ReparentEffectSpawnerToSource(EffectSpawner* self)
{
    self->desc->m15(self, (BaseObject*)self->rec->target);
}

// After loading, finds the objects the spawner refers to by id (its target, the two ends, and a
// kind 3 object) and stores them in its own record; queues ReparentEffectSpawnerToSource when it
// has a source object. Does nothing for a spawner with no ids.
void ResolveEffectSpawnerLinks(EffectSpawner* self)
{
    EffectSpawnerRecord* s2;

    PostLoadPlacedObject(self);
    if (self->key2F8 == -1 && self->id304 == -1 && self->id30C == -1 && self->id300 == -1) {
        EffectSpawnerRecord* p = self->rec;
        if (p->kind != 3 && (p->effectMode != 0 || p->f188 == -1)) goto tail;
    }
    s2 = GetOwnSpawnRecord(self, 1);
    if (self->id2F8[0] != -1) {
        SpawnerLinkedObject* r = (SpawnerLinkedObject*)FindFirstObjectById(self->world, 0x104, self->id2F8[0], self);
        s2->target = r;
        if (r != 0) AppendQueuedCall(self->world, (void*)ReparentEffectSpawnerToSource, self, 0, 0);
    }
    if (self->id2F8[1] != -1) {
        s2->found[0] = FindFirstObjectById(self->world, 0x104, self->id2F8[1], self);
    }
    if (self->id304 != -1) {
        s2->found[1] = FindFirstObjectById(self->world, 0x104, self->id304, self);
    }
    if (self->id300 != -1) {
        SpawnerLinkedObject* s1 = (SpawnerLinkedObject*)FindFirstObjectById(self->world, 0x104, self->id300, self);
        if (IsObjectOfKind((BaseObject*)s1, 3) != 0) s2->found[2] = s1;
    }
    if (self->id30C != -1) {
        SpawnerLinkedObject* r = (SpawnerLinkedObject*)FindFirstObjectById(self->world, 0x104, self->id30C, self);
        s2->value20 = r->value;
        s2->target = r->target;
    }
tail:
    ResolveSpawnRecordTargets((SpawnTargetRecord*)self->rec, (SpawnTargetOwner*)self);
}

void SetEffectSpawnerActiveFor(EffectSpawner* self, f32 f);
void SetEffectSpawnerActiveForever(EffectSpawner* self);
void InheritFlaggedAncestorValue(EffectSpawner* self);

// Start: the record's flag, the mode and its first delay, the margin and rate from the record's
// box, then the copy the object named by f310 is made of it when there is none.
void StartEffectSpawner(EffectSpawner* self)
{
    StartPlacedObject(self);
    if (self->rec->effectKind != -1)
        self->rec->effectMode = 1;
    if (self->mode == -1) {
        if (self->chance != 0.0f || self->continuous != 0)
            self->mode = 3;
        else if (self->targetCount != 0.0f)
            self->mode = 1;
        else
            self->mode = 0;
    }
    switch (self->mode) {
    case 2:
        self->nextRateTime = 3.4028235e+38f;
        self->rate = RandomFloatInRange(self->delay.lo, self->delay.hi);
        if (self->continuous != 0)
            SetEffectSpawnerActiveForever(self);
        else if (RandomFloatInRange(0.0f, 1.0f) <= self->chance)
            SetEffectSpawnerActiveFor(self, RandomFloatInRange(self->active.lo, self->active.hi));
        break;
    case 3:
        self->nextRateTime = 3.4028235e+38f;
        self->rate = RandomFloatInRange(self->delay.lo, self->delay.hi) * 60.0f;
        if (self->continuous != 0)
            SetEffectSpawnerActiveForever(self);
        else if (RandomFloatInRange(0.0f, 1.0f) <= self->chance)
            SetEffectSpawnerActiveFor(self, RandomFloatInRange(self->active.lo, self->active.hi));
        break;
    case 0:
    case 1:
        self->nextRateTime = 1.0f;
        self->rateInterval = 1.0f;
        self->rate = RandomFloatInRange(self->delay.lo, self->delay.hi);
        break;
    }
    self->volumeScale = 1.0f;
    EffectSpawnerRecord* rec = self->rec;
    if (rec->kind == 1) {
        f32* box = rec->box20;
        if (self->id2F8[0] != -1) {
            f32 dx = __builtin_fabsf(box[4] - box[0]);
            f32 dy = __builtin_fabsf(box[5] - box[1]);
            f32 dz = __builtin_fabsf(box[6] - box[2]);
            f32 m = dy < dx ? (dz >? dx) : (dz >? dy);
            self->margin = m * 0.5f;
        }
        if (self->scaleByVolume != 0) {
            if (self->targetCount != 0.0f)
                self->volumeScale = (box[4] - box[0]) * (box[5] - box[1]) * (box[6] - box[2]) * 1e-6f;
            else
                self->volumeScale = (box[5] - box[1]) * (box[6] - box[2]) * 1e-4f;
        }
    }
    if (self->sharedId != -1) {
        EffectSpawner* copy = (EffectSpawner*)FindFirstObjectByIdMode1(self->world, self->sharedId, 0);
        if (copy == 0) {
            copy = (EffectSpawner*)CreateTypedRecord(0x50, self->world, 0, self->sharedId, -1);
            copy->rec = (EffectSpawnerRecord*)AllocateFrontMemory(0x200);
            *copy->rec = *self->rec;
            copy->rec->target = 0;
            copy->mode = self->mode;
            copy->remaining = self->remaining;
            copy->delay = self->delay;
            copy->scaleByVolume = self->scaleByVolume;
            copy->chance = self->chance;
            copy->active = self->active;
            copy->targetCount = self->targetCount;
            copy->continuous = self->continuous;
            copy->flags = ((copy->flags | (1ULL << 32)) & ~(3ULL << 40)) | (1ULL << 40);
            copy->rot = copy->m110 = self->rot;
            if (copy->desc->m0F != 0)
                copy->desc->m0F(copy);
        }
        self->changed = 0;
        AppendToList((ObjectList*)copy->list314, self);
        InheritFlaggedAncestorValue(self);
    }
}

// For notification kind 2 about one of the two held objects, tells it (slot 24) and forgets it.
void ReleaseEffectSpawnerHeld(EffectSpawner* self, s32 mode, BaseObject* p)
{
    if (mode == 2) {
        if (p == self->held344) {
            p->desc->m18(p, self);
            self->held344 = 0;
        } else if (p == self->held348) {
            p->desc->m18(p, self);
            self->held348 = 0;
        }
    }
}

// Gives a spawn record this owner may change: the record itself when only one owner uses it, else a
// copy (with its own copy of the 0x28-byte entries for kind 3) with the use counts adjusted.
EffectSpawnerRecord* CloneSharedSpawnRecord(EffectSpawnerRecord* self)
{
    EffectSpawnerRecord* n;
    if (self->uses < 2) return self;
    n = (EffectSpawnerRecord*)CopyToFrontMemory(0x200, self);
    if (self->kind == 3 && self->links != 0) {
        n->links = CopyToFrontMemory(0x28 * self->value20, self->links);
    }
    n->uses = 1;
    self->uses -= 1;
    return n;
}

// Gives the spawner's spawn record; with mode 1 it first makes it the spawner's own copy and marks
// the spawner changed.
EffectSpawnerRecord* GetOwnSpawnRecord(EffectSpawner* self, s32 mode)
{
    if (mode == 1) {
        self->changed = mode;
        self->rec = CloneSharedSpawnRecord(self->rec);
    }
    return self->rec;
}

// Marks the spawner changed when value is 1, and gives it back.
EffectSpawner* MarkEffectSpawnerChanged(EffectSpawner* self, s32 value)
{
    if (value == 1) {
        self->changed = value;
    }
    return self;
}

// Adds a range entry to the spawner's own (copied if shared) spawn record.
void AddSpawnRangeEntry(EffectSpawner* self, s32 a, s32 b, f32 x, f32 y, f32 z, f32 w)
{
    // the range emitter is a local view at 0x10 of the spawn record
    u8* p=(u8*)GetOwnSpawnRecord(self,1);
    AddRangeEntry((RangeEmitter*)(p+16),a,b,x,y,z,w,self);
}

f32 WrapModulo(f32 x, f32 m);

// Wraps the spawner's particles into a box of half-side `margin` around its target (or around
// the origin): every coordinate outside the box comes back in on the other side.
void WrapSpawnerParticlesIntoBox(EffectSpawner* self)
{
    if (!(1e-4f < self->margin)) {
        return;
    }
    Vec4 size;
    Vec4 lo;
    Vec4 hi;
    // One register value serves the box: the margin on every axis, then, with no target, its
    // negative for the low corner. The record is read between the splat and the copy
    // (docs/toolchain/gcse.md, "A splat split between a GPR and a VU0 copy").
    u128 margin = Vu0::Splat(self->margin);
    EffectSpawnerRecord* rec = self->rec;
    u128 half = margin;
    Vu0::Q(size) = half;
    if (rec->target != 0) {
        Vu0::Q(lo) = Vu0::Sub(Vu0::Q(((PlacedObject*)rec->target)->v140), half);
        Vu0::Q(hi) = Vu0::Add(Vu0::Q(((PlacedObject*)rec->target)->v140), half);
    } else {
        Vu0::Q(hi) = half;
        half = Vu0::MulX(half, Vu0::Scalar(-1.0f));
        Vu0::Q(lo) = half;
    }
    Vu0::Q(size) = Vu0::Splat(self->margin + self->margin);
    if (self->rec->effectMode != 0) {
        return;
    }
    WorldListedObject* w = (WorldListedObject*)self->held348;
    if (w == 0) {
        return;
    }
    for (OwnedRecord* r = (OwnedRecord*)w->members.head; r != 0; r = r->next) {
        Vec4* pts = r->points[r->bank];
        for (s32 i = 0; i < r->count; i++) {
            Vec4* p = &pts[i];
            Vec4 delta;
            ListFrame frame;
            if (p->x < lo.x || hi.x < p->x) {
                delta.x = lo.x + WrapModulo(p->x - lo.x, size.x) - p->x;
                p->x += delta.x;
            }
            if (p->y < lo.y || hi.y < p->y) {
                delta.y = lo.y + WrapModulo(p->y - lo.y, size.y) - p->y;
                p->y += delta.y;
            }
            if (p->z < lo.z || hi.z < p->z) {
                delta.z = lo.z + WrapModulo(p->z - lo.z, size.z) - p->z;
                p->z += delta.z;
            }
        }
    }
}

void RandomizeEffectSpawnerDelay(EffectSpawner* self);
s32 CountListItems(ObjectList* list);
void WrapSpawnerParticlesIntoBox(EffectSpawner* self);
void SetEffectSpawnerActiveFor(EffectSpawner* self, f32 f);
void SetEffectSpawnerActiveForever(EffectSpawner* self);
s32 IsEffectSpawnerActive(EffectSpawner* self);

// Per-frame update of an effect spawner: updates the placed object, then, when the spawner is
// active and one of its linked objects is attached (and near the camera), spawns effects from its
// record. It cycles the spawner between active and idle by random delays in seconds
// (delayMin..delayMax and active.lo..hi) and wraps its particles into the box.
void UpdateEffectSpawner(EffectSpawner* self, f32 dt)
{
    ListFrame frame;

    if (self->changed != 0) {
        RandomizeEffectSpawnerDelay(self);
    }
    UpdatePlacedObject(self, dt);
    if (self->sharedId != -1) {
        return;
    }
    if (!IsListEmpty((ObjectList*)self->list314)) {
        PlacedObject* o = *(PlacedObject**)self->list314;
        Camera* cam;
        s32 near;
        f32 r;
        u128 d;
        if (o == 0) {
            return;
        }
        do {
            if (!(o->flags & ((u64)0x8000 << 23)) && IsObjectAttached(o)) {
                if (o->parent == 0) {
                    goto spawn;
                }
                cam = g_camera;
                near = 1;
                r = o->fadeDistanceFar * cam->rangeScale;
                d = Vu0::Sub(Vu0::Q(o->v140), Vu0::Q(cam->position));
                if (!(r * r > Vu0::ToFloatMoved(Vu0::Dot(d, d)))) {
                    near = 0;
                }
                if (near) {
                    goto spawn;
                }
            }
            // the list link at 0x320 of the objects walked: their class is not known
            o = *(PlacedObject**)((u8*)o + 0x320);
        } while (o != 0);
        return;
    } else {
        if (self->parent != 0) {
            Camera* cam = g_camera;
            f32 r = self->fadeDistanceFar * cam->rangeScale;
            s32 far = 1;
            if (!(r * r < Vu0::ToFloat(Vu0::Dot(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(cam->position)),
                                                 Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(cam->position)))))) {
                far = 0;
            }
            if (far) {
                return;
            }
        }
    }
spawn:
    if (IsEffectSpawnerActive(self)) {
        return;
    }
    s32 n = 0;
    switch (self->mode) {
    case 3: {
        f32 acc = self->spawnRemainder + self->rate * self->volumeScale * dt;
        n = (s32)acc;
        self->spawnRemainder = acc - (f32)n;
        if (1.0f < (f32)n) {
            if (self->remaining >= 0) {
                if (!(n < self->remaining)) {
                    n = self->remaining;
                }
                self->remaining -= n;
            }
            if (self->continuous != 0) {
                SetEffectSpawnerActiveForever(self);
                self->rate = RandomFloatInRange(self->delayMin, self->delayMax) * 60.0f;
            } else if (RandomFloatInRange(0.0f, 1.0f) <= self->chance) {
                SetEffectSpawnerActiveFor(self, RandomFloatInRange(self->active.lo, self->active.hi));
                self->rate = RandomFloatInRange(self->delayMin, self->delayMax) * 60.0f;
            }
        }
        break;
    }
    case 2:
        n = (s32)self->rate;
        if (self->remaining >= 0) {
            if (!(n < self->remaining)) {
                n = self->remaining;
            }
            self->remaining -= n;
        }
        if (self->continuous != 0) {
            SetEffectSpawnerActiveForever(self);
        } else if (RandomFloatInRange(0.0f, 1.0f) <= self->chance) {
            SetEffectSpawnerActiveFor(self, RandomFloatInRange(self->active.lo, self->active.hi));
        }
        self->rate = RandomFloatInRange(self->delayMin, self->delayMax);
        break;
    case 0: {
        f32 acc = self->spawnRemainder + self->rate * self->volumeScale * dt;
        n = (s32)acc;
        self->spawnRemainder = acc - (f32)n;
        if (n == 0) {
            goto timer;
        }
        if (self->remaining >= 0) {
            if (!(n < self->remaining)) {
                n = self->remaining;
            }
            self->remaining -= n;
        }
        break;
    }
    case 1: {
        n = (s32)(self->targetCount * self->volumeScale);
        s32 have;
        BaseObject* held;
        if (self->rec->effectMode == 0) {
            held = self->held348;
            have = held != 0 ? ((WorldListedObject*)held)->particleCount : 0;
        } else {
            held = self->held344;
            have = held != 0 ? CountListItems(&((EffectOwner*)held)->list558) : 0;
        }
        s32 left = n - have;
        n = 0; if (left > n) { n = left; }
        break;
    }
    }
    if (n != 0) {
        SpawnFlags p;
        p.z = (s32)&self->held348;
        p.b = (s32)&self->held344;
        p.c = (s32)self;
        void* prev = self->rec->target;
        if (self->id2F8[0] == -1) {
            self->rec->target = self;
        }
        SpawnEffectsFromRecord(n, self->rec, &p);
        self->rec->target = prev;
    }
timer:
    if (self->nextRateTime <= g_gameClock[1]) {
        self->rate = RandomFloatInRange(self->delayMin, self->delayMax);
        self->nextRateTime = g_gameClock[1] + self->rateInterval;
    }
    WrapSpawnerParticlesIntoBox(self);
}

// Unless it has the flag itself, looks up the parents for the first with bits 0x0C000000 equal to
// 0x08000000 and takes its visibility mask.
void InheritFlaggedAncestorValue(EffectSpawner* self)
{
    if ((self->flags & 0x0C000000) == 0x08000000) {
        return;
    }
    PlacedObject* p = (PlacedObject*)self->parent;
    while (p != 0) {
        if ((p->flags & 0x0C000000) == 0x08000000) {
            break;
        }
        p = (PlacedObject*)p->parent;
    }
    if (p != 0) {
        self->visibilityMask = p->visibilityMask;
    }
}

// Keeps the spawner active until f from now (game time).
void SetEffectSpawnerActiveFor(EffectSpawner* self, f32 f)
{
    self->activeUntil = g_gameTime + f;
}

// Sets activeUntil to the largest float, so the spawner stays active for good.
void SetEffectSpawnerActiveForever(EffectSpawner* self)
{
    self->activeUntil = 3.4028234663852886e+38f;
}

// Ends the active period by setting activeUntil to -1.
void SetEffectSpawnerInactive(EffectSpawner* self)
{
    self->activeUntil = -1.0f;
}

// True while the game time is before activeUntil, or in mode 0 or 1 when the counter is 0.
s32 IsEffectSpawnerActive(EffectSpawner* self)
{
    if (g_gameTime < self->activeUntil) {
        return 1;
    }
    if (self->mode < 2) {
        if (self->mode >= 0) {
            if (self->remaining == 0) {
                return 1;
            }
        }
    }
    return 0;
}

// Turns the spawner off for a non-zero argument and on forever for zero.
void SetEffectSpawnerDisabled(EffectSpawner* self, s32 a1)
{
    if (a1 != 0) {
        SetEffectSpawnerInactive(self);
    } else {
        SetEffectSpawnerActiveForever(self);
    }
}

// Stores whether the spawner is inactive in *out.
void GetEffectSpawnerInactive(EffectSpawner* self, s32* out)
{
    *out = IsEffectSpawnerActive(self) == 0;
}

// Stores whether the spawner is active in *out.
void GetEffectSpawnerActive(void* self,s32* out)
{
    *out=IsEffectSpawnerActive((EffectSpawner*)self);
}

// Re-arms the spawner: clears its counter, passes the record's look source to the listed object and
// the margin to the effect owner if they exist, and draws a new random delay between delayMin and
// delayMax (in seconds, scaled by 60 for record kind 3).
void RandomizeEffectSpawnerDelay(EffectSpawner* self)
{
    self->changed=0;
    if (self->held348) ApplyLookSourceToListedObject((WorldListedObject*)self->held348,(LookSource*)self->rec);
    if (self->held344) CopyEffectOwnerMargin((EffectOwner*)self->held344,self->rec);
    f32 value;
    if (self->mode==3) value=RandomFloatInRange(self->delayMin,self->delayMax)*60.0f;
    else value=RandomFloatInRange(self->delayMin,self->delayMax);
    self->rate=value;
}

// Sets how many more spawns are allowed. In mode -1 that is the counter; in mode 0, 0 means active
// forever and -1 inactive. Marks the spawner changed.
void SetEffectSpawnerLimit(EffectSpawner* self, s32 a1)
{
    if (self->mode == -1) {
        self->remaining = a1;
    } else if (self->mode == 0) {
        if (a1 == 0) {
            // retail's call leaves self where it already is in a0 and does not set it again
            ((void (*)())SetEffectSpawnerActiveForever)();
        } else if (a1 == -1) {
            SetEffectSpawnerInactive(self);
        } else {
            self->remaining = a1;
        }
    }
    self->changed = 1;
}

// Sets the spawner's continuous flag and marks it changed.
void SetEffectSpawnerContinuous(EffectSpawner* a0, s32 a1)
{
    a0->continuous = a1;
    a0->changed = 1;
}

// Stores the effect kind in the record and resets its three kind parameters: kind 24 gets 25, 0.8,
// 0.8 and kind 27 gets -1 and 10.0; others get zeros.
void SetSpawnRecordKind(EffectSpawnerRecord* self,s32 kind)
{
    self->effectKind=kind;
    FillMemory(&self->f1F0,0,12);
    if (kind!=24) {
        if (kind==27) {
            self->f1F0=-1;
            self->f1F4=10.0f;
        }
    } else {
        self->f1F0f=25.0f;
        self->f1F4=0.8f;
        self->f1F8=0.8f;
    }
}

// Sets the effect kind on the spawner's own spawn record.
void SetEffectSpawnerKind(void* a0, s32 a1)
{
    void* r = GetOwnSpawnRecord((EffectSpawner*)a0, 1);
    SetSpawnRecordKind((EffectSpawnerRecord*)r, a1);
}

// Sets the effect kind on the member's own spawn record.
void SetOwnedSpawnRecordKind(void* a0, s32 a1)
{
    void* r = GetOwnedSpawnRecord((RecordMember*)a0, 1);
    SetSpawnRecordKind((EffectSpawnerRecord*)r, a1);
}

// The splash of an object on a surface: its sound by distance, the effect, and from 500 on a
// burst through SpawnEffectsAt. The burst's two records are brace initialisers
// (docs/toolchain/large-functions.md, "A brace initialiser's union member is a CLOBBER"): the
// tail's two float groups each start with a union's member, and the block is the spawn block
// (EffectSpawnData), built in a temporary and copied because two of its vectors are copied from memory;
// the position is a local of its own, which takes the temporary's slot.
struct __attribute__((aligned(16))) SplashTail {
    s32 f00;                // 0x00
    s32 f04;                // 0x04
    s32 f08;                // 0x08
    s32 f0C;                // 0x0C
    union {
        f32 f10;            // 0x10
        u32 f10Bits;
    };
    f32 f14;                // 0x14
    s32 f18;                // 0x18
    s32 f1C;                // 0x1C
    union {
        f32 f20;            // 0x20
        u32 f20Bits;
    };
    f32 f24;                // 0x24
    s32 f28;                // 0x28
    s32 f2C;                // 0x2C
    void* f30;              // 0x30
    s32 f34;                // 0x34
    s32 f38;                // 0x38
    s32 f3C;                // 0x3C
};
extern s32 g_surfaceContactSounds[74];
s32 RandomIntInRange(s32 a, s32 b);
void SpawnEffectsAt(Quad16* self, Quad16* a1, s32 a2, SpawnTail* a3, SpawnBlock* a4, s32 a5, s32 a6);

// A playing sound, as far as the surface-contact effects reach into it.

// Both callers (gauge_collider.cpp and collider.cpp) declare it with these parameters and are
// retail's code with them; a float takes its register wherever it is declared.
void SpawnSurfaceContactEffects(BaseObject* self, u8* cfg, Quad16* p, f32 chance, Quad16* at, f32 minScale, f32 size)
{
    AttachedSet* set = (AttachedSet*)cfg;
    if (set->tellsLanding == 0) {
        return;
    }
    f32 dist = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(*p), Vu0::Q(((PlacedObject*)self)->v150))));
    f32 zero = 0.0f;
    s32 go = RandomFloatInRange(zero, 3.0f) < chance;
    SwitchedCollider* snd = 0;
    if (self->desc->flags & 8) {
        snd = (SwitchedCollider*)self;
    }
    if (10.0f < dist || go) {
        f32 hi = 1.0f;
        f32 t = (dist - 10.0f) * 0.00126582279f;
        f32 k;
        if (t < zero) {
            k = zero;
        } else if (hi < t) {
            k = hi;
        } else {
            k = t;
        }
        if (snd != 0 && set->splashSoundEnabled != 0) {
            f32 vol = k * 0.9f + 0.1f;
            PlayingSound* rec = (PlayingSound*)snd->playingSound;
            if (rec != 0) {
                rec->baseVolume = vol;
            } else {
                StartSoundEffect(g_surfaceContactSounds[RandomIntInRange(0, 3)], (PlayingSound**)&snd->playingSound, (BaseObject*)snd, 0, 10.0f, 1.0f, vol,
                                 0.0f, 0.0f, 0, 0);
            }
        }
        if (!go) {
            f32 period = 1.0f - k * (1.0f - minScale);
            if (snd != 0) {
                go = period < g_gameTime - snd->surfaceEffectTime;
            } else {
                f32 now = g_gameTime;
                s32 a = (s32)(now / period);
                s32 b = (s32)((now + chance) / period);
                go = a != b;
            }
            if (!go) {
                return;
            }
        }
        Effect* e = (Effect*)CreateEffect(4, 0);
        if (e == 0) {
            return;
        }
        ((EffectStartFn)e->vt->m00)(e, at, 0, size);
        if (snd != 0) {
            snd->surfaceEffectTime = g_gameTime;
        }
        if (set->splashBurstEnabled != 0 && 500.0f < dist) {
            SplashTail tail = { 2, -1, 0, 0, 1.0f, 0.0f, 0, 0, 8.0f, 12.0f, 0, 0, cfg };
            EffectSpawnData block = {
                { dist * 0.5f, dist * 0.75f, 1.0f }, self->world->gravity, { 0.0f, 0.0f, 0.0f },
                *(Quad16*)&g_unitZVector, 0.0f, 0.392699093f, 1.04719758f, 0,
                { 1.0f, 5.0f, 0.0f }, { { 0, 0, 0, 0 } }, { 1.0f, 0.0f, -1.0f }
            };
            Vec4 pos = *(Vec4*)at;
            pos.z += 30.0f;
            SpawnEffectsAt((Quad16*)&pos, (Quad16*)&g_unitZVector, RandomIntInRange(4, 6), (SpawnTail*)&tail, (SpawnBlock*)&block, 0, 0);
        }
    } else if (snd != 0) {
        StopSoundRecord((PlayingSound*)snd->playingSound, 0);
    }
}

// Sends a point event (kind 12, the point and a value) to the world's listener in slot 9 if any.
void SendPointEventToWorldListener(Quad16* a0, f32 f)
{
    BaseObject* obj = g_currentWorld->slot1CE8[9];
    if (obj != 0) {
        PointEventMessage m;
        m.kind = 12;
        m.q = *a0;
        m.f = f;
        m.zero = 0;
        obj->desc->m1B(obj, &m);
    }
}

struct SpawnCurve;
typedef void (*CurveEvalFn)(SpawnCurve* self, f32 t, Vec4* pos, Vec4* dir);
struct SpawnCurveClass { u8 pad0[8]; CurveEvalFn eval; };
struct SpawnCurve {
    SpawnCurveClass* desc;  // 0x00
    u8 pad04[8];
    s32 count;              // 0x0C
    u8 pad10[4];
    f32* lengths;           // 0x14
};

// A piece of a ring of segments between two objects: the radii at its ends and its length.
struct SpawnSegment {
    u8 pad00[8];
    f32 widthStart;         // 0x08: the width at the segment's first end
    f32 widthEnd;           // 0x0C: the width at the segment's second end
    f32 r0;                 // 0x10
    f32 r1;                 // 0x14
    PlacedObject* from;     // 0x18
    PlacedObject* to;       // 0x1C
    f32 distance;           // 0x20: the distance between the two end objects
    f32 len;                // 0x24
};

struct SpawnTriangle {
    s32 v[3];               // 0x00
    f32 area;               // 0x0C
};

struct SpawnMesh {
    u8 pad00[4];
    Vec4* verts;           // 0x04
    s32 count;              // 0x08
    SpawnTriangle* tris;    // 0x0C
    Vec4* normals;         // 0x10
    f32 area;               // 0x14
};

// A range a random float is drawn from.
struct SpawnRange {
    f32 lo;
    f32 hi;
};

struct SpawnShape {
    s32 kind;               // 0x00
    u8 pad04[0xC];
    union {
        Vec4 point;        // 0x10
        struct {
            f32 lo[4];      // 0x10
            f32 hi[4];      // 0x20
        } box;
        SpawnCurve* curve;  // 0x10
        struct {
            s32 count;      // 0x10
            SpawnSegment* segs; // 0x14
            f32 len;        // 0x18
        } ring;
        SpawnMesh mesh;     // 0x10
    };
    u8 pad30[0x40 - 0x30];
    s32 mode;               // 0x40
    u8 pad44[0x50 - 0x44];
    Vec4 dir;              // 0x50
    SpawnRange jitter;      // 0x60
    u8 pad68[4];
    void* anchor;           // 0x6C
};

s32 SolveQuadratic(f32 a, f32 b, f32 c, f32* roots);
void ComputePolarOffset(Vec3* out, f32 angle, f32 scale, f32 z);

static inline f32 RandomInRange(const SpawnRange& r)
{
    return RandomFloatInRange(r.lo, r.hi);
}

static inline f32 RandomInRange(const ParticleRange& r)
{
    return RandomFloatInRange(r.lo, r.hi);
}

// v made unit length, or fallback when v is shorter than 0.0001: Vu0::NormalizeOr over vector
// values, the fallback returned as it is. In a function with a jump table, jump.c runs again
// after cse2 and turns the u128 form's arms into a preset of the fallback (docs/TOOLCHAIN.md,
// "A preset of the fallback after cse2"); the copies of the vector values keep the arms.
static inline Vu0::Vec NormalizedOr(Vu0::Vec v, Vu0::Vec fallback)
{
    u128 len = Vu0::Length(v.q);
    if (Vu0::ToFloatMoved(len) < 0.0001f) {
        return fallback;
    }
    Vu0::Vec r;
    r.q = Vu0::DivX(v.q, len);
    return r;
}

// The point of a spawn shape for the index-th of count spawns, and its direction: a point, a
// random point in a box, along a curve, on a ring of segments or on a mesh, the direction by the
// shape's mode, then made unit length and the point moved along it by a random jitter.
void ChooseSpawnPosition(SpawnShape* shape, s32 index, s32 count, Vec4* pos, Vec4* axis)
{
    switch (shape->kind) {
    case 0:
        *pos = shape->point;
        break;
    case 1:
        pos->x = RandomFloatInRange(shape->box.lo[0], shape->box.hi[0]);
        pos->y = RandomFloatInRange(shape->box.lo[1], shape->box.hi[1]);
        pos->z = RandomFloatInRange(shape->box.lo[2], shape->box.hi[2]);
        break;
    case 2: {
        SpawnCurve* curve = shape->curve;
        f32 step = curve->lengths[curve->count - 1] / (f32)count;
        f32 lo = (f32)index * step;
        f32 t = RandomFloatInRange(lo, lo + step);
        switch (shape->mode) {
        default:
            if (curve->desc->eval) {
                curve->desc->eval(curve, t, pos, 0);
            }
            break;
        case 2:
            if (curve->desc->eval) {
                curve->desc->eval(curve, t, pos, axis);
            }
            goto normalize;
        case 3: {
            Vec4 tangent;
            if (curve->desc->eval) {
                curve->desc->eval(curve, t, pos, &tangent);
            }
            Vu0::Set(*axis, Vu0::Cross(Vu0::Vec::Of(tangent), Vu0::Vec::Of(shape->dir)).q);
            goto normalize;
        }
        }
        break;
    }
    case 3: {
        f32 step = shape->ring.len / (f32)count;
        f32 d = RandomFloatInRange((f32)index * step, (f32)(index + 1) * step);
        SpawnSegment* seg;
        Vec4 offset;
        Mat3 frame;
        Vec4 at;
        Vec4 side;
        f32 roots[2];
        s32 i;
        for (i = 0; i < shape->ring.count; i++) {
            seg = &shape->ring.segs[i];
            d -= seg->len;
            if (d < 0.0f) {
                break;
            }
        }
        Vu0::Set(frame.r[2], NormalizedOr(Vu0::Sub(Vu0::Vec::Of(seg->to->v140), Vu0::Vec::Of(seg->from->v140)),
                                              Vu0::Vec::Of(g_unitXVector)).q);
        BuildPerpendicularPair(&frame.r[2], &frame.r[0], &g_unitXVector, &g_unitZVector);
        d += seg->len;
        if (seg->widthEnd != seg->widthStart) {
            SolveQuadratic((seg->widthEnd - seg->widthStart) * 0.5f / seg->distance, seg->widthStart, -d, roots);
        } else {
            roots[0] = d / seg->widthStart;
        }
        f32 u = roots[0] / seg->distance;
        ComputePolarOffset((Vec3*)&offset, RandomFloatInRange(-3.14159265f, 3.14159265f), (1.0f - u) * seg->r0 + u * seg->r1,
                           roots[0]);
        Vu0::Set(at, Vu0::Add(Vu0::Vec::Of(seg->from->v140), Vu0::Rotate(frame, Vu0::Vec::Of(offset))).q);
        TransformPointBetweenFrames(0, (PlacedObject*)shape->anchor, &at, pos);
        switch (shape->mode) {
        case 2:
            TransformDirectionBetweenFrames(0, (PlacedObject*)shape->anchor, &frame.r[2], axis);
            goto normalize;
        case 3: {
            Vu0::Set(side, NormalizedOr(Vu0::Cross(Vu0::Vec::Of(frame.r[2]), Vu0::Vec::Of(shape->dir)),
                                            Vu0::Vec::Of(g_unitXVector)).q);
            TransformDirectionBetweenFrames(0, (PlacedObject*)shape->anchor, &side, axis);
            goto normalize;
        }
        }
        break;
    }
    case 4: {
        SpawnMesh* mesh = &shape->mesh;
        f32 a = RandomFloatInRange(0.0f, 1.0f) * mesh->area;
        SpawnTriangle* tri;
        Vec4 p[3];
        s32 i;
        for (i = 0; i < mesh->count; i++) {
            tri = &mesh->tris[i];
            a -= tri->area;
            if (a <= 0.0f) {
                break;
            }
        }
        p[0] = mesh->verts[tri->v[0]];
        p[1] = mesh->verts[tri->v[1]];
        p[2] = mesh->verts[tri->v[2]];
        f32 s = RandomFloatInRange(0.0f, 1.0f);
        f32 t = RandomFloatInRange(0.0f, 1.0f - s);
        f32 w = 1.0f - s - t;
        Vu0::Set(*pos, Vu0::MulXSum3(Vu0::Vec::Of(p[0]), Vu0::Vec::Scalar(s), Vu0::Vec::Of(p[1]),
                                     Vu0::Vec::Scalar(t), Vu0::Vec::Of(p[2]), Vu0::Vec::Scalar(w)).q);
        if (shape->mode == 5) {
            Vec4 n[3];
            Vu0::Set(n[0], Vu0::Vec::Of(mesh->normals[tri->v[0]]).q);
            Vu0::Set(n[1], Vu0::Vec::Of(mesh->normals[tri->v[1]]).q);
            Vu0::Set(n[2], Vu0::Vec::Of(mesh->normals[tri->v[2]]).q);
            Vu0::Set(*axis, Vu0::MulXSum3(Vu0::Vec::Of(n[0]), Vu0::Vec::Scalar(s), Vu0::Vec::Of(n[1]),
                                          Vu0::Vec::Scalar(t), Vu0::Vec::Of(n[2]), Vu0::Vec::Scalar(w)).q);
            goto normalize;
        }
        break;
    }
    }
    switch (shape->mode) {
    case 0:
        *axis = shape->dir;
        break;
    case 1:
        Vu0::Set(*axis, Vu0::Sub(Vu0::Vec::Of(*pos), Vu0::Vec::Of(shape->dir)).q);
        break;
    case 4:
        if (shape->anchor != 0) {
            Vu0::Set(*axis, Vu0::RotateTransposed(((PlacedObject*)shape->anchor)->m110,
                                                  Vu0::Rotate(g_camera->rot80, Vu0::Vec::Of(shape->dir))).q);
        } else {
            Vu0::Set(*axis, Vu0::Rotate(g_camera->rot80, Vu0::Vec::Of(shape->dir)).q);
        }
        break;
    default:
        *axis = g_unitXVector;
        break;
    }
normalize:
    Vu0::Vec n = NormalizedOr(Vu0::Vec::Of(*axis), Vu0::Vec::Of(g_unitXVector));
    Vu0::Set(*axis, n.q);
    Vu0::Vec at = Vu0::Vec::Of(*pos);
    Vu0::Set(*pos, Vu0::Add(at, Vu0::MulX(n, Vu0::Vec::Scalar(RandomInRange(shape->jitter)))).q);
}

struct AnchoredSpawn {
    u8 pad00[0x6C];
    PlacedObject* anchor;   // 0x6C: the object whose frame the spawn is given in
    s32 mode;               // 0x70: 1, 2 and 3 take less of the anchor's motion
};


// Brings a spawn position and direction into the anchor's frame. Unless mode 3 the direction is
// turned too, and unless mode 2 the anchor's own motion at that point is added to it.
void ConvertSpawnToAnchorSpace(AnchoredSpawn* self, Vec4* pos, Vec4* dir)
{
    Vec4 motion;
    if (self->anchor) {
        TransformPointBetweenFrames(self->anchor, 0, pos, pos);
        if (self->mode != 3) {
            TransformDirectionBetweenFrames(self->anchor, 0, dir, dir);
            if (self->mode != 2) {
                Vec4* ref = pos;
                if (self->mode != 1)
                    ref = &self->anchor->v140;
                ComputeObjectMotionInFrame(self->anchor, 0, ref, &motion, 0, 0, 0);
                Vu0::Q(*dir) = Vu0::Add(Vu0::Q(*dir), Vu0::Q(motion));
            }
        }
    }
}

// Sets up an evenly spaced ring of angles over the span lo..hi: at most k slots, the rate (2 pi per
// slot), the step between rings, the first phase half a step in, and a random starting angle.
void InitSpawnRing(s32 n, SpawnSpan* span, s32 k, SpawnRing* out) { if (n > 0) { out->count = n < k ? n : k; } else { out->count = k; } s32 steps = k - 1; steps += out->count; steps = steps / out->count; f32 w = WrapAngle(span->hi - span->lo); f32 rate = 6.2831855f / (f32)out->count; f32 step = w / (f32)steps; out->rate = rate; out->step = step; out->phase = span->lo + step * 0.5f; out->out10 = RandomFloatInRange(0.0f, 6.2831855f); }

void ComputeDirectionFromAngles(Vec3* out, f32 first, f32 second, f32 scale);

// Gives the direction of particle number index of a ring spawn: the index is split into a step
// along the ring (index / count) and one across it (index % count), each adds an angle (with
// optional random jitter), the angles become a direction of a random length in the span, flattened
// in z, and turned into the frame of axis.
void ComputeSpawnRingDirection(SpawnRing* ring, SpawnSpan* range, Vec4* axis, s32 index, Vec4* out, f32 jitter, f32 flatten)
{
    Vec4 dir;
    Mat3 basis;
    s32 q = index / ring->count;
    s32 r = index % ring->count;
    f32 first = ring->phase + (f32)q * ring->step;
    f32 second = ring->out10 + (f32)r * ring->rate;
    if (jitter != 0.0f) {
        first += jitter * RandomFloatInRange(-0.5f, 0.5f) * ring->step;
        second += jitter * RandomFloatInRange(-0.5f, 0.5f) * ring->rate;
    }
    first = WrapAngle(first + 1.57079637f);
    second = WrapAngle(second);
    ComputeDirectionFromAngles((Vec3*)&dir, second, first, RandomFloatInRange(range->lo, range->hi));
    basis.r[2] = *axis;
    dir.z *= flatten;
    BuildPerpendicularPair(&basis.r[2], &basis.r[0], &g_unitXVector, &g_unitZVector);
    Vu0::Q(*out) = Vu0::Rotate(basis, Vu0::Q(dir));
}

struct SpawnPlacement {
    SpawnSpan range;        // 0x00: the distance from the point
    f32 flatten;            // 0x08: scales the z of the direction
    u8 pad0C[0x50 - 0x0C];
    f32 jitter;             // 0x50
    f32 life;               // 0x54: added to the start time for the end
    f32 lo58;               // 0x58: a distance along the direction, picked between lo58 and hi5C
    f32 hi5C;               // 0x5C
    f32 lo60;               // 0x60: how long before now it started, picked between lo60 and hi64
    f32 hi64;               // 0x64
};

// Picks a direction, start time and end time for particle index: the direction from the ring, a
// start time randomly before now, the end time start plus life, and a random push of the position
// along the direction.
void ChooseSpawnDirectionAndLifetime(SpawnPlacement* self, SpawnRing* ring, s32 unused, s32 index, Vec4* pos, Vec4* axis,
                   Vec4* dir, f32* start, f32* end)
{
    Vec4 k;
    ComputeSpawnRingDirection(ring, &self->range, axis, index, dir, self->jitter, self->flatten);
    *start = g_gameClock[1] - RandomFloatInRange(self->lo60, self->hi64);
    *end = *start + self->life;
    f32 along = RandomFloatInRange(self->lo58, self->hi5C);
    if (along != 0.0f) {
        Vu0::Q(k) = Vu0::FromFloat(along);
        Vu0::Q(*pos) = Vu0::MulAddX(Vu0::Q(*pos), Vu0::Q(*dir), Vu0::Q(k));
    }
}

// The part of the spawn record that SpawnRecordEffects reads, from 0x120 on (EffectSpawnerRecord, effect_spawner.h).
struct SpawnEffectParams {
    u8 pad00[0x90];
    s32 effectKind;         // 0x1B0: the kind of effect made for each point
    s32 trailKind;          // 0x1B4: the kind of effect that trails each one, -1 for none
    u8 pad98[0xA4 - 0x98];
    f32 poly1;              // 0x1C4: the second and third words of the quadratic at 0x1C0, put in each effect
    f32 poly2;              // 0x1C8
    u8 padAC[0xB0 - 0xAC];
    f32 scaleMin;           // 0x1D0: the range each effect's scale is drawn from
    f32 scaleMax;           // 0x1D4
    s32 found0;             // 0x1D8: the first object the ids name
    u8 padBC[0xC0 - 0xBC];
    s32 found2;             // 0x1E0: the third
    s32 ownerFlag;          // 0x1E4: the flag AcquireEffectOwner is asked with
};

// Spawns effects for a spawn record in its owner mode: finds (or acquires and caches in the slot h)
// the effect owner for the record, copies the record's margin into it, and gives it n entries with
// positions pos and the other arrays.
void SpawnRecordEffects(EffectSpawnerRecord* self, EffectOwnerSlot* h, s32 n, Quad16* pos, Quad16* q2, f32* v5, f32* v6)
{
    PlacedObject* s7 = (PlacedObject*)self->target;
    EffectOwner* node = 0;
    // a field access here changes retail's code: the part of the record from 0x120 is held in a register
    SpawnEffectParams* c = (SpawnEffectParams*)((u8*)self + 0x120);
    s32 i;
    if (h) {
        if (h->effectOwnerCache) node = (EffectOwner*)*h->effectOwnerCache;
    }
    if (!node) {
        node = AcquireEffectOwner((World*)g_currentWorld, c->ownerFlag);
        if (!node) return;
        if (h) {
            if (h->effectOwnerCache) *h->effectOwnerCache = (s32)node;
        }
        CopyEffectOwnerMargin(node, self);
        if (h) {
            if (h->ownerArgument) {
                typedef void (*F)(EffectOwner*, void*);
                ((F)node->desc->m17)(node, h->ownerArgument);
            }
        }
    }
    if (node) {
    for (i = 0; i < n; i++) {
        Effect* it = CreateEffect(c->effectKind, (EffectOwner*)node);
        if (!it) break;
        Quad16* s1 = pos + i;
        u8* cls = (u8*)it->vt;
        f32 f = RandomFloatInRange(c->scaleMin, c->scaleMax);
        typedef void (*F0)(Effect*, Quad16*, s32, f32);
        (*(F0*)cls)(it, s1, c->found2, f);
        f32 f1 = c->poly1;
        if (f1 != 0.0f || c->poly2 != 0.0f) {
            it->m30[1] = f1;
            it->m30[2] = c->poly2;
        }
        *(Quad16*)&it->qA0 = q2[i];
        it->start = v5[i];
        it->life = v6[i] - v5[i];
        *(Quad16*)&it->q40 = self->q110;
        FillLookDirectionBlock(&it->fB0, (LookSource*)self);
        if (c->found0) it->i20 = c->found0;
        if (s7) {
            it->rotation[0] = s7->m110.r[0];
            it->rotation[1] = s7->m110.r[1];
            it->rotation[2] = s7->m110.r[2];
        }
        if (c->trailKind != -1) {
            EffectOwner* o = (EffectOwner*)CreateEffect(c->trailKind, 0);
            if (!o) break;
            typedef void (*F1)(f32, EffectOwner*, void*, s32);
            F1 fn = (F1)((Effect*)o)->vt->m00;
            fn(it->m30[0] * 0.5f, o, &it->pos, 0);
            SetTrailSegmentAnchor(o, 1, it);
        }
        {
            if (it->vt->m01) ((void (*)(Effect*, EffectSpawnerRecord*))it->vt->m01)(it, self);
        }
    }
    if (IsListEmpty(&node->list558)) {
        typedef void (*F2)(EffectOwner*);
        node->desc->m03(node);
    }
    }
}

struct WorldListedObject;
struct OwnedRecord;
s32 RandomIntInRange(s32 a, s32 b);

// A chunk of particles an effect owner keeps (its 0x624 word, the next at 0x1090): this frame's
// positions, velocities and records and a copy of them for the frame before, 0x2C of each.
struct ParticleState {
    Quad16 pos[0x2C];       // 0x000: w is the size
    Quad16 vel[0x2C];       // 0x2C0: w is the spin
    Quad16 rec[0x2C];       // 0x580
};
struct ParticleExtra {
    Quad16 a;
    Quad16 b;
};
struct ParticleChunk {
    ParticleState cur;      // 0x000
    ParticleState prev;     // 0x840
    s32 f1080;
    u32 count;              // 0x1084
    ParticleExtra* extra;   // 0x1088
    s32 f108C;
    ParticleChunk* next;    // 0x1090
};

// Adds n particles to the owner the slot holds (or a fresh one), chunk after chunk; each gets its
// position and velocity, random frame numbers and spin, and the copy for the frame before.
// Each array is written through its own pointer, the copy through the chunk's previous state:
// loop.c then reduces the record's address and the copy's as two registers (docs/TOOLCHAIN.md).
void EmitParticleChunk(EffectSpawnerRecord* self, EffectOwnerSlot* h, s32 n, Quad16* pos, Quad16* vel, f32* size, f32* spin, Quad16* e, Quad16* g)
{
    WorldListedObject* set = 0;
    s32 i;
    ParticleChunk* chunk;
    if (h) {
        if (h->particleOwnerCache) set = (WorldListedObject*)*h->particleOwnerCache;
    }
    if (!set) {
        World* world = g_currentWorld;
        if (world->pool1B40.head == 0) return;
        if (self->f130 == 2) {
            if (world->pool1B4C.head == 0) return;
        }
        set = ResetFirstListedObject(world);
        if (!set) return;
        if (h) {
            if (h->particleOwnerCache) *h->particleOwnerCache = (s32)set;
        }
        ApplyLookSourceToListedObject(set, (LookSource*)self);
        if (h) {
            if (h->ownerArgument) {
                typedef void (*F)(WorldListedObject*, void*);
                ((F)set->desc->m17)(set, h->ownerArgument);
            }
        }
        if (!set) return;
    }
    chunk = (ParticleChunk*)set->members.head;
    i = 0;
    while (i < n && (chunk != 0 || (chunk = (ParticleChunk*)AcquireOwnedRecord(set)) != 0)) {
        u32 k = chunk->count;
        ParticleState* last = &chunk->prev;
        while (k < 0x2C && i < n) {
            Quad16* p = &chunk->cur.pos[k];
            Quad16* v = &chunk->cur.vel[k];
            Quad16* rec = &chunk->cur.rec[k];
            *p = pos[i];
            *(f32*)&p->w[3] = size[i];
            *v = vel[i];
            *(f32*)&v->w[3] = spin[i];
            FillMemory(rec, 0, 0x10);
            s32 r = RandomIntInRange(0, set->colorCount - 1);
            rec->w[0] = r;
            if (set->pairedColors != 0) rec->w[0] = r & 0xFFFFFFFE;
            if (self->randomSecondFrame != 0) rec->w[1] = RandomIntInRange(0, set->regCount - 1);
            if (set->particleMode == 2) {
                f32 f = RandomInRange(self->range19C);
                *(f32*)&rec->w[2] = f;
                if (self->skipCameraFacing == 0) {
                    if (0.0f < Vu0::ToFloat(Vu0::Dot(Vu0::Q(g_camera->rot80.r[1]), Vu0::Q(*v)))) *(f32*)&rec->w[2] = -f;
                }
                if (self->randomTurn != 0) *(f32*)&rec->w[3] = RandomFloatInRange(-3.14159274f, 3.14159274f);
            }
            if (set->mode == 2) {
                ParticleExtra* x = &chunk->extra[k];
                x->a = e[i];
                x->b = g[i];
            }
            last->pos[k] = *p;
            last->vel[k] = *v;
            last->rec[k] = *rec;
            chunk->count = chunk->count + 1;
            set->particleCount = set->particleCount + 1;
            i++;
            k++;
        }
        chunk = chunk->next;
    }
}

// The frame of the object a spawn record follows (at 0x78): its position, the rotation, and the
// velocity and spin it moves with.
struct SpawnFrame {
    Vec4 pos;              // 0x00
    Mat3 rot;              // 0x10
    Vec4 vel;              // 0x40
    Vec4 spin;             // 0x50
    SpawnFrame() { FillMemory(this, 0, sizeof(*this)); }
};

// Makes the count points of a spawn record, their directions and times, in the four arrays out
// holds (positions, directions, starts, ends), moved to the followed object's frame.
void GenerateSpawnArrays(s32 n, void* b, sptr* out)
{
    u8* rec = (u8*)b;
    // the record is viewed through local types at fixed offsets (ring 0xE4, shape 0x10, placement 0xA0):
    // no one type of ours covers them
    SpawnRing ring;
    Vec4 axis;
    out[0] = (sptr)AllocateBackMemory(n * 16);
    out[1] = (sptr)AllocateBackMemory(n * 16);
    out[2] = (sptr)AllocateBackMemory(n * 4);
    out[3] = (sptr)AllocateBackMemory(n * 4);
    InitSpawnRing(*(s32*)(rec + 0xEC), (SpawnSpan*)(rec + 0xE4), n, &ring);
    for (s32 i = 0; i < n; i++) {
        ChooseSpawnPosition((SpawnShape*)(rec + 0x10), i, n, (Vec4*)out[0] + i, &axis);
        ChooseSpawnDirectionAndLifetime((SpawnPlacement*)(rec + 0xA0), &ring, (s32)(rec + 0x10), i, (Vec4*)out[0] + i, &axis,
                      (Vec4*)out[1] + i, (f32*)out[2] + i, (f32*)out[3] + i);
        SpawnFrame* o = (SpawnFrame*)((EffectSpawnerRecord*)b)->frame;
        if (o != 0) {
            Vec4* pos = (Vec4*)(i * 16 + out[0]);
            Vu0::Q(*pos) = Vu0::Add(Vu0::Rotate(o->rot, Vu0::Q(*pos)), Vu0::Q(o->pos));
            Vec4* vel = (Vec4*)(i * 16 + out[1]);
            u128 rel = Vu0::Sub(Vu0::Q(*(Vec4*)(i * 16 + out[0])), Vu0::Q(o->pos));
            u128 spun = Vu0::Cross(Vu0::Q(o->spin), rel);
            u128 moved = Vu0::Add(Vu0::Rotate(o->rot, Vu0::Q(*vel)), Vu0::Q(o->vel));
            Vu0::Q(*vel) = Vu0::Add(moved, spun);
        }
        if (out[4] != 0) {
            ConvertSpawnToAnchorSpace((AnchoredSpawn*)(rec + 0x10), (Vec4*)out[0] + i, (Vec4*)out[1] + i);
        }
    }
}

s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 eps);
void ComputeChainedWorldFrame(void* a, void* frame, void* out);

// Generates two sets of spawn arrays for the record (for the effects that need a start and an end):
// the second set through the record's own sub-record, then, for each of the n entries, the pair of
// values the first set needs.
void GenerateSpawnSetupPair(s32 n, void* owner, SpawnSetup* first, SpawnSetup* second)
{
    SpawnFrame frame;
    Vec4 P;
    Vec4 V;
    Vec4 W;
    Mat3 M;
    Vec4 tmp;
    RecordMember* r = ((EffectSpawnerRecord*)owner)->member;
    EffectSpawnerRecord* sub = (EffectSpawnerRecord*)r->rec;
    void* saved = sub->target;
    if (r->id94 == -1) {
        sub->target = r->parent;
    }
    if (((EffectSpawnerRecord*)r->rec)->target == r->parent) {
        ComputeChainedWorldFrame(r, &frame.pos, &frame.rot);
        ((EffectSpawnerRecord*)r->rec)->frame = &frame;
    }
    second->flag = 0;
    GenerateSpawnArrays(n, (EffectSpawnerRecord*)r->rec, second->out);
    ((EffectSpawnerRecord*)r->rec)->frame = 0;
    f32 last = 3.40282347e+38f;
    for (s32 i = 0; i < n; i++) {
        if (((EffectSpawnerRecord*)r->rec)->target != 0) {
            f32 t = ((f32*)first->out[3])[i] - g_gameClock[1];
            if (!AreFloatsNearlyEqual(t, last, 0.0001f)) {
                last = t;
                // retail's caller evaluates the time before the pointers, as the third argument
                ((void (*)(PlacedObject*, PlacedObject*, f32, Vec4*, Mat3*, Vec4*, Vec4*))ComputeObjectFrameAtTime)((PlacedObject*)(((EffectSpawnerRecord*)r->rec)->target), 0, last, &P, &M, &V, &W);
            }
            Vec4* p = (Vec4*)(i * 16 + second->out[0]);
            Vu0::Set(tmp, Vu0::Rotate(M, Vu0::Q(*p)));
            Vu0::Q(*p) = Vu0::Add(Vu0::Q(P), *(u128*)&tmp);
            s32 kind = ((EffectSpawnerRecord*)r->rec)->secondVelocityMode;
            if (kind != 3) {
                Vec4* v = (Vec4*)(i * 16 + second->out[1]);
                Vu0::Q(*v) = Vu0::Rotate(M, Vu0::Q(*v));
                if (kind != 2) {
                    u128 moved = Vu0::Add(Vu0::Q(*(Vec4*)(i * 16 + second->out[1])), Vu0::Q(V));
                    u128 spin = Vu0::Q(W);
                    Vu0::Q(*(Vec4*)(i * 16 + second->out[1])) = Vu0::Add(moved,
                        Vu0::Cross(spin, Vu0::Q(kind == 1 ? *(Vec4*)(second->out[0] + i * 16) : tmp)));
                }
            }
        }
        Vu0::Vec neg = Vu0::Vec::FromFloat(-1.0f);
        u128 r = Vu0::MulX(Vu0::Q(*(Vec4*)(i * 16 + second->out[1])), neg.q);
        *(Vu0::Vec*)&tmp = neg;
        Vu0::Q(*(Vec4*)(i * 16 + second->out[1])) = r;
    }
    ((EffectSpawnerRecord*)r->rec)->target = saved;
}

// Generates the arrays for a spawn of "a" effects from record b, then spawns them as effect owners
// (record kind 1) or as particle chunks (otherwise, with a second setup pair for kind 2). Memory
// for the arrays is taken from the back-memory mark.
void SpawnEffectsFromRecord(s32 a, EffectSpawnerRecord* b, void* c)
{
    SpawnSetup f;
    if (a == 0) {
        return;
    }
    PushBackMemoryMark();
    f.flag = 1;
    GenerateSpawnArrays(a, b, f.out);
    if (b->effectMode == 1) {
        SpawnRecordEffects(b, (EffectOwnerSlot*)c, a, (Quad16*)f.out[0], (Quad16*)f.out[1], (f32*)f.out[2], (f32*)f.out[3]);
    } else {
        if (b->f130 == 2) {
            GenerateSpawnSetupPair(a, b, &f, (SpawnSetup*)f.pair);
        } else {
            f.pair[0] = 0;
            f.pair[1] = 0;
        }
        EmitParticleChunk(b, (EffectOwnerSlot*)c, a, (Quad16*)f.out[0], (Quad16*)f.out[1], (f32*)f.out[2], (f32*)f.out[3], (Quad16*)f.pair[0], (Quad16*)f.pair[1]);
    }
    PopBackMemoryMark();
}

// Spawns "a2" effects at a point without a spawner: builds a temporary spawn record from the given
// positions, block and tail (kind 1) and calls SpawnEffectsFromRecord with it.
void SpawnEffectsAt(Quad16* self, Quad16* a1, s32 a2, SpawnTail* a3, SpawnBlock* a4, s32 a5, s32 a6)
{
    SpawnRecord f;
    InitSpawnRecord(&f);
    SpawnFlags p;
    f.self_copy = *self;
    f.a1_copy = *a1;
    f.blk = *a4;
    p.b = a5;
    p.c = a6;
    f.f120 = 1;
    f.tail = *a3;
    SpawnEffectsFromRecord(a2, (EffectSpawnerRecord*)&f, &p);
}

LINKER_REMNANT(func_00157FF0);

// Sends every keyed object of the current world an event for the point self: kind 4 normally, 0x14
// (with value x) or 0x24 (with obj) when the object's record is in message mode 4 or 2.
void BroadcastPointEvent(void* self, void* obj, f32 x)
{
    BroadcastMessage frame;
    KeyedObjectList* list = (*(KeyedWorldView**)((u8*)&g_currentWorld))->list;

    if (list == 0) return;
    for (s32 i = 0; i < list->count; i++) {
        KeyedObject* e = list->items[i];
        frame.kind = 4;
        frame.pos = *(Quad16*)self;
        if (e->f90->f120 == 1) {
            switch (e->f90->messageMode) {
            case 4:
                frame.kind = 0x14;
                frame.value = x;
                break;
            case 2:
                frame.kind = 0x24;
                frame.object = obj;
                break;
            }
        }
        e->vtbl[31](e, &frame);
    }
}

// Creates effect type 4 at the given place and starts it with the given strength. It lives 0.75 and
// follows the source's oscillator if it has one.
void SpawnBriefEffectAt(void* a0, BriefEffectSource* a1, f32 f)
{
    Effect* o = (Effect*)CreateEffect(4, 0);
    if (o != 0) {
        ((EffectStartFn)o->vt->m00)(o, a0, 0, f);
        o->life = 0.75f;
        if (a1->f278 != 0) {
            o->oscillator = (void*)a1->f278->fC;
        }
    }
}

// Adds an entry to the range emitter (at most 0x20, allocating the 0x500-byte table on first use):
// the two ids, and the five floats, where a negative optional value takes the value of another (c).
void AddRangeEntry(RangeEmitter* self, s32 a1, s32 a2, f32 f12, f32 f13, f32 f14, f32 f15, void* owner)
{
    self->kind = 3;
    if (self->entries == 0) {
        self->entries = (RangeEntry*)AllocateZeroedFrontMemory(0x500);
    }
    if (self->count < 0x20) {
        s32 n = self->count;
        RangeEntry* e = self->entries + n;
        self->count = n + 1;
        e->a = a1;
        e->b = a2;
        e->c = f13;
        if (0.0f <= f15) {
            e->d = f15;
        } else {
            e->d = f13;
        }
        e->e = f12;
        if (0.0f <= f14) {
            e->f = f14;
        } else {
            e->f = f12;
        }
    }
}

// One target of a spawn record at 0x24 (0x28 bytes): two ids, the objects they name, and the
// distance between those objects with the weight made of it.
struct SpawnLink {
    s32 ids[2];             // 0x00
    f32 widthStart;         // 0x08: the width at the first object
    f32 widthEnd;           // 0x0C: the width at the second object
    u8 pad10[0x18 - 0x10];
    PlacedObject* objs[2];  // 0x18
    f32 distance;           // 0x20
    f32 weight;             // 0x24
};

struct SpawnTargetRecord {
    u8 pad00[0x10];
    s32 kind;               // 0x10
    u8 pad14[0x20 - 0x14];
    s32 count;              // 0x20
    SpawnLink* links;       // 0x24
    f32 total;              // 0x28
    u8 pad2C[0x120 - 0x2C];
    s32 f120;               // 0x120
    u8 pad124[0x188 - 0x124];
    s32 targetId;           // 0x188: the id of the target object
    MemberTargetObject* targetObject; // 0x18C: the object the id names
};

struct SpawnTargetOwner { u8 pad00[0x14]; void* world; };

// Looks up the objects a spawn record names: its target by id and, for kind 3 (strips between two
// objects), the two ends of each link, with the distance between them and a weight (average width
// times half the distance) summed into total.
void ResolveSpawnRecordTargets(SpawnTargetRecord* rec, SpawnTargetOwner* owner)
{
    if (rec->f120 == 0 && rec->targetId != -1) {
        rec->targetObject = (MemberTargetObject*)FindFirstObjectById((World*)owner->world, 0x104, rec->targetId, owner);
    }
    if (rec->kind == 3) {
        f32 total = 0.0f;
        for (s32 i = 0; i < rec->count; i++) {
            SpawnLink* link = &rec->links[i];
            for (s32 j = 0; j < 2; j++) {
                link->objs[j] = (PlacedObject*)FindFirstObjectById((World*)owner->world, 0x104, link->ids[j], owner);
            }
            f32 d = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(link->objs[0]->v140), Vu0::Q(link->objs[1]->v140))));
            link->distance = d;
            link->weight = (link->widthStart + link->widthEnd) * (d * 0.5f);
            total += link->weight;
        }
        rec->total = total;
    }
}

ASM_FUNC(func_001583E8);

// The spin record TurnMatrixBySpin reads (MoveEffect's at +0x100).
struct EffectSpinRecord {
    f32 scale;          // 0x00
    u8 pad4[0xC];
    f32 tx, ty, tz;     // 0x10
    u8 pad1C[4];
    f32 rate;           // 0x20
    u8 pad24[0xC];
    Quad16 axis;        // 0x30
    s32 mode;           // 0x40
    void* frame;        // 0x44
};
extern const Mat4A g_identityMatrix4;

// Builds the spawner's per-step transform: a scale and translation, turned by the spin's axis (in
// the spin frame's world axes when the mode is 1) at rate times dt, multiplied and scaled by dt;
// the result goes to out.
void TurnMatrixBySpin(EffectSpinRecord* spin, f32 dt, f32* out)
{
    Mat4A place = g_identityMatrix4;
    Mat4A turn;
    place.m[2][2] = place.m[1][1] = place.m[0][0] = spin->scale;
    place.m[3][0] = spin->tx;
    place.m[3][1] = spin->ty;
    place.m[3][2] = spin->tz;
    turn = g_identityMatrix4;
    if (spin->rate != 0.0f) {
        Quad16 axis;
        if (spin->mode == 1 && spin->frame != 0) {
            TransformDirectionBetweenFrames((PlacedObject*)spin->frame, 0, (Vec4*)&spin->axis, (Vec4*)&axis);
        } else {
            axis = spin->axis;
        }
        BuildAxisAngleMatrix((const Vec4*)&axis, (Mat3*)&turn, spin->rate * dt);
    }
    Mat4A term;
    Mat4A scaled;
    Mat4A* result = &scaled;
    Mat4A product = MultiplyMatrices(turn, place);
    ScaleMatrix(result, &product, Vu0::ScalarInGpr(dt));
    term = scaled;
    AddMatrices((f32*)&turn, (f32*)&term, out);
}

// Starts the object, then calls its slot 3.
void StartMemberObject(MemberObject* self)
{
    StartObject(self);
    self->desc->m03(self);
}

ASM_FUNC(func_00158630);

// Sends a zeroed 0x50-byte message through slot 27.
void SendEmptyMessage(MemberObject* a0)
{
    EmptyMessage b;
    FillMemory(&b, 0, 0x50);
    a0->desc->m1B(a0, &b);
}

// Sends a message carrying two ids, two vectors and two floats through slot 27.
void SendTwoVectorMessage(MemberObject* a0, s32 a1, s32 a2, Quad16* a3, Quad16* a4, f32 x, f32 y)
{
    TwoVectorMessage m;
    m.a = a1;
    m.b = a2;
    m.q1 = *a3;
    m.q2 = *a4;
    m.x = x;
    m.y = y;
    a0->desc->m1B(a0, &m);
}

void SendMemberObjectMessage()
{
}

// Reads a group of objects from the stream: the transform, then for each member three ids that
// create it (by type) as a child of the group, and its own data. Where a member is itself a group,
// up to 8 of its members are gathered and registered.
void LoadGroupMembers(MemberGroup* self, void* src)
{
    void* arr[8];
    s32 total;
    s32 i;
    ReadTransformObject(self, src);
    total = ReadBufferedS16((BufferedStream*)src);
    for (i = 0; i < total; i++) {
        s32 r1 = ReadBufferedS16((BufferedStream*)src);
        s32 r2 = ReadBufferedS16((BufferedStream*)src);
        s32 r3 = ReadBufferedS16((BufferedStream*)src);
        BaseObject* obj = (BaseObject*)CreateTypedRecord(r1, self->world, self->parent, r2, r3);
        s32 n;
        obj->desc->m0A(obj, src);
        if (obj->desc->flags & 0x100) {
            GroupCell* p = (GroupCell*)((ObjectGroup*)obj)->cells.first;
            n = 0;
            while (p != 0) {
                if ((u32)n < 8) {
                    arr[n] = p->node;
                    n++;
                }
                p = p->next;
            }
        } else {
            arr[0] = obj;
            n = 1;
        }
        if (n > 0) {
            void** dst = (void**)self->members;
            void** s = arr;
            s32 j;
            for (j = n; j != 0; j--, s++) {
                MemberObject* o = (MemberObject*)*s;
                if (IsObjectOfKind(o, 0x78) != 0 || IsObjectOfKind(o, 0x7A) != 0) {
                    o->desc->m03(o);
                    u32 c = self->count;
                    if (c < 8) {
                        // address arithmetic over a variable index
                        *(void**)((u8*)dst + (c << 2)) = o;
                        self->count = c + 1;
                        o->group = self;
                    }
                }
            }
        }
    }
}

// Copies the group's data, then replaces each member with a copy made on the group's world and
// parent, starts it and points it at this group.
void CopyGroupMembers(MemberGroup* self, MemberGroup* src)
{
    CopyObjectData(self, src);
    for (s32 i = 0; i < self->count; i++) {
        MemberObject* o = CreateObjectCopy(self->members[i], self->world, self->parent);
        o->desc->m03(o);
        self->members[i] = o;
        o->group = self;
    }
}

// Calls slot 15 of each member that has one.
void ResolveGroupMembers(MemberGroup* self)
{
    for (s32 i = 0; i < self->count; i++) {
        MemberObject* it = self->members[i];
        void (*fn)(BaseObject*) = it->desc->m0F;
        if (fn != 0) {
            fn(it);
        }
    }
}

// Sends the message to every member of the group through its slot-27 method.
void BroadcastMessageToMembers(MemberGroup* self, void* message)
{
    for (s32 i = 0; i < self->count; i++) {
        MemberObject* it = self->members[i];
        it->desc->m1B(it, message);
    }
}

// Initialises the transform object and puts both target ids at -1.
void InitRecordMember(RecordMember* self)
{
    InitTransformObject(self);
    self->id94 = -1;
    self->id98 = -1;
}

// Loads a record member object: allocates and initialises its spawn record, reads the transform, an
// optional path curve (index byte, -1 for none), a mesh for kind 4, and the capped word list (an id
// list read from the stream).
void LoadRecordMember(RecordMember* self, void* stream)
{
    TransformRecord* p = (TransformRecord*)AllocateZeroedFrontMemory(0x200);
    self->rec = p;
    InitSpawnRecord(p);
    ReadTransformObject(self, stream);
    s32 idx = ReadBufferedS8((BufferedStream*)stream);
    if (idx != -1) {
        TransformRecord* n = GetOwnedSpawnRecord(self, 1);
        n->curve20 = CreatePathCurve(idx);
        if (n->curve20->vt->m00 != 0) {
            n->curve20->vt->m00(n->curve20, stream);
        }
    }
    TransformRecord* q = self->rec;
    if (q->kind == 4) {
        ReadSpawnMesh(&q->curve20, stream);
    }
    s32 t = ReadBufferedU16((BufferedStream*)stream);
    if (t != 0) {
        TransformRecord* m = GetOwnedSpawnRecord(self, 1);
        ReadCappedWordList(&m->words130, t, self, stream);
    }
}

// Copies the object's data and counts one more user on the shared spawn record.
void CopyRecordMember(RecordMember* self, RecordMember* src)
{
    CopyObjectData(self, src);
    self->rec->uses += 1;
}

// Looks up the objects the member's ids 0x94 and 0x98 name and stores them in its owned spawn
// record (the second also supplies the value), then resolves the record's own targets. Skipped when
// both ids are unset and the record has nothing of its own to resolve.
void ResolveRecordMemberTargets(RecordMember* self)
{
    TransformRecord* r;
    TransformRecord* c;

    if (self->id94 == -1 && self->id98 == -1) {
        c = self->rec;
        if (c->kind != 3) {
            if (c->link120 != 0) goto tail_c;
            if (c->link188 == -1) goto tail;
        }
    }

    {
        s32 none = -1;

        r = GetOwnedSpawnRecord(self, 1);
        if (self->id94 != none) {
            r->target = FindFirstObjectById(self->world, 260, self->id94, self);
        }
        if (self->id98 != none) {
            MemberTargetObject* q = (MemberTargetObject*)FindFirstObjectById(self->world, 260, self->id98, self);
            r->value20 = q->value;
            r->target = q->target;
        }
    }

tail:
    c = self->rec;
tail_c:
    ResolveSpawnRecordTargets((SpawnTargetRecord*)c, (SpawnTargetOwner*)self);
}

void SendRecordMemberMessage(void)
{
}

// Adds a range entry to the member's own (copied if shared) spawn record.
void AddRecordMemberRangeEntry(RecordMember* self, s32 a, s32 b, f32 x, f32 y, f32 z, f32 w)
{
    // the range emitter is a local view at 0x10 of the spawn record
    u8* p = (u8*)GetOwnedSpawnRecord(self, 1);
    AddRangeEntry((RangeEmitter*)(p+16),a,b,x,y,z,w,self);
}

// Gives the member's spawn record; with own 1 it first makes it the member's own copy.
TransformRecord* GetOwnedSpawnRecord(RecordMember* self, s32 own)
{
    if (own == 1) {
        self->rec = (TransformRecord*)CloneSharedSpawnRecord((EffectSpawnerRecord*)self->rec);
    }
    return self->rec;
}

// Initialises the record member and puts its three held ids at -1.
void InitHoldingMember(HoldingMember* self)
{
    InitRecordMember(self);
    self->idAC = -1;
    self->idB0 = -1;
    self->idB4 = -1;
}

// Resolves the record member's targets, then the up to three objects it holds (ids 0xAC, 0xB0 and
// 0xB4, the last only if it is of kind 3) into the spawn record's found array.
void ResolveHoldingMemberTargets(HoldingMember* self)
{
    TransformRecord* s;
    void* p;

    ResolveRecordMemberTargets(self);
    if (self->idAC == -1 && *(s64*)&self->idB0 == -1) {
        return;
    }
    s = GetOwnedSpawnRecord(self, 1);
    if (self->idAC != -1) {
        s->found[0] = FindFirstObjectById(self->world, 0x104, self->idAC, self);
    }
    if (self->idB0 != -1) {
        s->found[1] = FindFirstObjectById(self->world, 0x104, self->idB0, self);
    }
    if (self->idB4 != -1) {
        p = FindFirstObjectById(self->world, 0x104, self->idB4, self);
        if (IsObjectOfKind((BaseObject*)p, 3) != 0) {
            s->found[2] = p;
        }
    }
}

// For notification kind 2 about one of the two held objects, tells it (slot 24) and forgets it.
void ReleaseHeldObject(HoldingMember* self, s32 kind, BaseObject* other)
{
    if (kind == 2) {
        if (other == self->heldC0) {
            other->desc->m18(other, self);
            self->heldC0 = 0;
        } else if (other == self->heldC4) {
            other->desc->m18(other, self);
            self->heldC4 = 0;
        }
    }
}

// Sends a spawn message to the member: queued with a due time of now plus its delay (in seconds)
// when the delay is positive and a pool slot is free, otherwise handled at once.
// DispatchDelayedMessages later handles the queued ones.
void SendMessageAfterDelay(HoldingMember* self, void* message)
{
    QueuedDelayedMessage* r;
    f32* k;
    s32 done = 0;

    if (0.0f < self->delay) {
        r = (QueuedDelayedMessage*)PopFreeSlot(&self->world->pool1BD0);
        if (r != 0) {
            r->owner = self;
            r->body = *(DelayedMessageBody*)message;
            done = 1;
            k = (f32*)g_gameClock;
            r->due = k[1] + self->delay;
            ClearListLinks((ListLink*)r->link);
            AppendToList(&self->world->list1BDC, r);
        }
    }
    if (done == 0) {
        HandleSpawnMessage(self, message);
    }
}

// Gives the member's sound record, creating it on first use.
s32 GetOrCreateSoundParams(void* self)
{
    HoldingMember* o = (HoldingMember*)self;
    if (o->soundParams == 0) {
        InitSoundParams((SoundRecord**)&o->soundParams);
    }
    return o->soundParams;
}

// The 0x200-byte spawn record (TransformRecord) as func_001590A0 changes its copy: the copy is written
// field by field, so each store is a structure member's and the message's flags word is read
// again after it (docs/TOOLCHAIN.md, "A store to a stack struct's member").
struct __attribute__((aligned(16))) SpawnRecordView {
    u8 pad00[0x10];
    s32 kind;               // 0x10: where the sound plays (the switch below)
    u8 pad14[0x20 - 0x14];
    union {
        Quad16 q20;         // 0x20: a point (kind 0), the first end (kind 1)
        Vec4 v20;
        u8* p20;            // 0x20: an object whose point at +0x18 is used (kind 2)
    };
    Vec4 v30;              // 0x30: the second end (kind 1)
    Vec4 v40;              // 0x40: kind 4's point
    u8 pad50[0x60 - 0x50];
    Quad16 q60;             // 0x60
    u8 pad70[0x78 - 0x70];
    void* frame;            // 0x78: a frame the point is placed in
    s32 target;             // 0x7C: the object whose frame the point is in
    u8 pad80[0xA0 - 0x80];
    f32 fA0;                // 0xA0
    f32 fA4;                // 0xA4
    u8 padA8[0x120 - 0xA8];
    s32 f120;               // 0x120
    u8 pad124[0x140 - 0x124];
    Quad16 q140;            // 0x140
    u8 pad150[0x1D0 - 0x150];
    f32 f1D0;               // 0x1D0
    f32 f1D4;               // 0x1D4
    u8 pad1D8[0x1E0 - 0x1D8];
    s32 f1E0;               // 0x1E0
    u8 pad1E4[0x200 - 0x1E4];
};

// The message func_001590A0 takes (a DelayedMessageBody): its flags say which fields to use.
struct SpawnMessage {
    s32 flags;              // 0x00
    s32 target;             // 0x04: flag 1
    u8 pad08[0x10 - 0x08];
    Quad16 q10;             // 0x10: flag 2
    Quad16 q20;             // 0x20: flag 4
    f32 scale;              // 0x30: flags 8 and 0x10
    f32 percent;            // 0x34: flag 8, when scale is 0
    s32 f38;                // 0x38: flag 0x20
    void* frame;            // 0x3C: flag 0x40
    s32 count;              // 0x40: flag 0x80
};

// The chained world frame func_00158630 writes: a position and the rotation after it.
struct __attribute__((aligned(16))) ChainFrame {
    u8 b[0x60];
    void Clear() { FillMemory(this, 0, sizeof(*this)); }
};

void *StoreFloatAsQuadword(u128* out, f32 f);
void* CopyQuadword(u128* out, void* src);
void* StoreQuadword(u128* out, u128 v);
struct ValueRange;
f32 ClampToRange(ValueRange* span, f32 x);
void ComputeChainedWorldFrame(void* a, void* frame, void* out);
extern f32 g_spawnScaleRatioRange[2];
extern const Vec4 g_zeroVector;

// The sound a spawner member plays (HoldingMember::soundParams): the sound, two radii, a volume and a pitch.
struct SpawnSoundParams {
    s32 id;
    f32 outerRange;
    f32 innerRange;
    f32 baseVolume;
    f32 pitch;
};

// Handles a spawn message: starts from a copy of the spawner's record, overrides it with what the
// message's flags carry (target, colour or placement, a frame, a count, a scale or percent), picks
// the particle count (the message's or random in the spawner's range), and then spawns the effects
// from the changed record.
void HandleSpawnMessage(void* self, void* body)
{
    SpawnMessage* m = (SpawnMessage*)body;
    SpawnRecordView rec;
    ChainFrame frame;
    void* chain[3];
    Vec4 v;
    Vec4 half;
    Vec4 qa;
    Vec4 qb;
    rec = *(SpawnRecordView*)((HoldingMember*)self)->rec;

    s32 count;
    if (m->flags & 0x80) {
        count = m->count;
    } else {
        count = (s32)RandomFloatInRange(((HoldingMember*)self)->countMin, ((HoldingMember*)self)->countMax);
    }
    if (m->flags & 1) rec.target = m->target;
    if (m->flags & 2) rec.q60 = m->q10;
    if (m->flags & 4) {
        rec.kind = 0;
        rec.q20 = m->q20;
    } else if (m->flags & 0x40) {
        rec.frame = m->frame;
        rec.target = (s32)((BaseObject*)self)->parent;
    } else {
        frame.Clear();
        // the second output is the rotation, at 0x10 of the chained frame record
        ComputeChainedWorldFrame(self, &frame, (u8*)&frame + 0x10);
        rec.frame = &frame;
        if (!(m->flags & 1)) rec.target = (s32)((BaseObject*)self)->parent;
    }
    if (m->flags & 8) {
        if (rec.f120 == 0) {
            f32 t = m->scale;
            f32 s;
            if (t == 0.0f) s = m->percent * 0.01f;
            else s = t;
            if (s < 1.0f) count = (s32)((f32)count * s);
            else count = (s32)((f32)count / s);
            s32 least = (s32)((HoldingMember*)self)->countMax / 2;
            count = least < count ? count : least;
            f32 r = ClampToRange((ValueRange*)g_spawnScaleRatioRange, s);
            rec.fA0 = rec.fA0 * r;
            rec.fA4 = rec.fA4 * r;
            f32 lowest = 0.5f;
            s = lowest >? s;
            Quad16* q = &rec.q140;
            StoreFloatAsQuadword((u128*)&qa, s);
            Quadword128 q0 = *(Quadword128*)&qa;
            CopyQuadword((u128*)&qb, q);
            StoreQuadword((u128*)q, ScaleQuadword(q0, *(Quadword128*)&qb));
        }
    }
    if (rec.f120 == 1) {
        if (m->flags & 0x10) {
            rec.f1D4 = rec.f1D0 = m->scale;
        }
        if (m->flags & 0x20) rec.f1E0 = m->f38;
    }
    void* cp;
    if (((HoldingMember*)self)->chained != 0) {
        chain[0] = &((HoldingMember*)self)->heldC4;
        chain[1] = &((HoldingMember*)self)->heldC0;
        chain[2] = self;
        cp = chain;
    } else {
        cp = 0;
    }
    SpawnEffectsFromRecord(count, (EffectSpawnerRecord*)&rec, cp);
    if (((HoldingMember*)self)->soundParams != 0) {
        switch (rec.kind) {
        case 0:
            v = rec.v20;
            break;
        case 1:
            Vu0::Q(half) = Vu0::FromFloat(0.5f);
            Vu0::Q(v) = Vu0::MulXSum(Vu0::Q(rec.v20), Vu0::Q(half), Vu0::Q(rec.v30), Vu0::Q(half));
            break;
        case 2:
            // the class of the object (kind 2) is not known: a pointer to its point at 0x18
            v = **(Vec4**)(rec.p20 + 0x18);
            break;
        case 3:
            v = g_zeroVector;
            break;
        case 4:
            v = rec.v40;
            break;
        }
        if (rec.frame != 0) {
            SpawnFrame* fr = (SpawnFrame*)rec.frame;
            Vu0::Q(v) = Vu0::Add(Vu0::Rotate(fr->rot, Vu0::Q(v)), Vu0::Q(fr->pos));
        }
        TransformPointBetweenFrames((PlacedObject*)rec.target, 0, &v, &v);
        SpawnSoundParams* snd = (SpawnSoundParams*)((HoldingMember*)self)->soundParams;
        StartSoundEffect(snd->id, 0, 0, &v, snd->outerRange, snd->innerRange, snd->baseVolume, snd->pitch, 0.0f, 0, 0);
    }
}

// Finds the member objects (class 0x77) below self: none gives *out = 0, one gives that one, and
// several are collected (up to 8 used) in a new group object (class 0x78) made as a child of self.
void FindOrBuildMemberGroup(void** out, void* self)
{
    BaseObject* o = (BaseObject*)self;
    void* arr[32];
    s32 n;
    s32 cnt;
    s32 i;
    MemberGroup* s2;

    n = GatherObjectsById(o->world, 0x202, 0x77, self, 0x20, arr);
    switch (n) {
    case 0:
        *out = 0;
        return;
    case 1:
        *out = arr[0];
        return;
    }
    s2 = (MemberGroup*)CreateTypedRecord(0x78, o->world, (BaseObject*)self, 0x202, -1);
    cnt = 8;
    if (n < 8) {
        cnt = n;
    }
    s2->count = cnt;
    CopyMemory(s2->members, arr, cnt * 4);
    for (i = 0; i < n; i++) {
        MemberObject* p = (MemberObject*)arr[i];
        if (i < s2->count) {
            p->group = s2;
        }
        p->desc->m03(p);
    }
    *out = s2;
}

// Handles every queued message whose due time has arrived (HandleSpawnMessage on its owner) and
// returns the slot to the pool.
void DispatchDelayedMessages(World* self)
{
    ListFrame it;
    BeginListWalk::Of(&it, &self->list1BDC);
    QueuedDelayedMessage* node;
    while ((node = NextInList<QueuedDelayedMessage>::Of(&it)) != 0) {
        if (!(g_gameClock[1] < node->due)) {
            HandleSpawnMessage(node->owner, &node->body);
            RemoveFromList(&self->list1BDC, node);
            PushFreeSlot(&self->pool1BD0, node);
        }
    }
    g_activeListFrames = it.prev;
}

LINKER_REMNANT(func_00159668);

// Loads the base animator, then the second record key, scale, low and high limits and the limit.
void LoadCrossfadeAnimator(CrossfadeAnimator* self, AnimatorParams* src)
{
    LoadAnimatorBase(self, src);
    self->cursor2.flags = self->cursor.flags;
    self->recordKey2 = src->s14;
    self->scale = src->f4;
    self->lo = src->f8;
    self->hi = src->fC;
    self->limit = src->f10;
}

// Binds the first record, then looks up the second by its key (claiming it if the first one's owner
// is this animator), sets the frame count to the larger of the two and starts in mode 0.
void BindCrossfadeAnimator(CrossfadeAnimator* self)
{
    BindAnimatorRecord(self);
    AnimRecord* a = FindAnimRecord(self->recordKey2);
    self->cursor2.record = a;
    if (a != 0) {
        if (a->owner == 0) {
            if (self->cursor.record->owner == self) {
                a->owner = self;
            }
        }
    }
    s32 lo = 0;
    if (self->cursor.record != 0) {
        lo = self->cursor.record->count;
    }
    s32 hi = 0;
    if (self->cursor2.record != 0) {
        hi = self->cursor2.record->count;
    }
    self->mode = -1;
    self->count = (hi < lo) ? lo : hi;
    SetCrossfadeMode(self, 0);
}

// Switches the crossfade animator to a new mode (0 to 3), setting the position, step and level the
// new mode starts from (some random in 0..1 against its limit).
void SetCrossfadeMode(CrossfadeAnimator* s, s32 mode)
{
    if (s->mode == mode) return;
    if (mode == 1) goto store;
    if (mode < 2) {
        if (mode == 0) goto zero;
        s->mode = mode;
        goto tail;
    }
    if (mode == 2) goto two;
    s->mode = mode;
    goto tail;

zero:
    {
        s32 n = s->count;
        f32 span = (f32)(n << 1) * (1.0f - s->ratio) / s->scale;
        s->pos = (f32)(n - 1) * s->ratio;
        s->step = span;
        f32 r = RandomFloatInRange(0.0f, 1.0f);
        if (r < s->limit) {
            s->level = 0.0f;
        } else {
            s->level = RandomFloatInRange(s->lo, s->hi);
        }
    }
    goto store;

two:
    {
        s32 last = s->count - 1;
        if ((s32)s->pos == last) {
            s->mode = mode;
            goto tail;
        }
        s->pos = (f32)last;
    }

store:
    s->mode = mode;

tail:
    s->stamp2 = g_gameTime;
}

// Per-frame step of a crossfade animator (count of 2 or more): its mode 0 waits level seconds, 1
// and 2 move the position along by step times dt (1 forwards, 2 back), 3 holds, and each can move
// on to another mode through SetCrossfadeMode.
void StepCrossfadeAnimator(CrossfadeAnimator* s, f32 dt)
{
    s32 count = s->count;
    if (count < 2) return;
    s32 mode = s->mode;
    if (mode == 1) goto m1;
    if (mode < 2) {
        if (mode == 0) goto m0;
        goto call;
    }
    if (mode == 2) goto m2;
    if (mode == 3) goto m3;
    goto call;

m0:
    if (s->level <= g_gameTime - s->stamp2) mode = 1;
    goto call;

m1:
    {
        f32 step = s->step * dt;
        f32 sum = s->pos + step;
        s->pos = sum;
        if ((f32)count <= sum) {
            f32 back = sum - step;
            s->pos = back;
            mode = ((s32)back == count - 1) ? 2 : 3;
        }
    }
    goto call;

m2:
    if (s->ratio < 1.0f) mode = 3;
    goto call;

m3:
    {
        f32 v = s->pos - s->step * dt;
        s->pos = v;
        if (v <= (f32)count * s->ratio) mode = 0;
    }

call:
    SetCrossfadeMode(s, mode);
    SetCursorFrame(&s->cursor, (s32)s->pos);
    SetCursorFrame(&s->cursor2, (s32)s->pos);
}

// Sets the crossfade ratio; at 1 or more the animator goes to mode 2, otherwise back to mode 0.
// Both cursors are put on the current frame.
void SetCrossfadeRatio(CrossfadeAnimator* a0, f32 f12)
{
    a0->ratio = f12;
    if (1.0f <= f12) {
        SetCrossfadeMode(a0, 2);
    } else {
        a0->mode = -1;
        SetCrossfadeMode(a0, 0);
    }
    SetCursorFrame(&a0->cursor, (s32)a0->pos);
    SetCursorFrame(&a0->cursor2, (s32)a0->pos);
}

// Finds the cursor for a record in the base animator, else the second cursor if the key matches the
// second record's.
AnimCursor* FindCrossfadeCursor(CrossfadeAnimator* self, const AnimRecord* key)
{
    AnimCursor* p = FindAnimatorCursor(self, key);
    if (p == 0) {
        p = &self->cursor2;
        if ((key->key ^ self->recordKey2) != 0) {
            p = 0;
        }
    }
    return p;
}

// Per-frame step of a ramp of an object's level: adds rate times dt; it ends (and leaves the world)
// when the level reaches 0 (the owner then gets its method m03 called), when it reaches 1, or when
// the owner is no longer attached.
void StepObjectLevelRamp(WorldObjectNode* self, f32 dt)
{
    if (self->rate != 0.0f) {
        if (IsObjectAttached(self->owner) == 0) {
            RemoveObjectNodeFromWorld(self);
            return;
        }
    }
    f32 old = self->level;
    self->level = old + self->rate * dt;
    if (self->level <= 0.0f && old > 0.0f) {
        PlacedObject* s = self->owner;
        s->desc->m03(s);
        RemoveObjectNodeFromWorld(self);
        return;
    }
    if (self->level >= 1.0f && old < 1.0f) {
        RemoveObjectNodeFromWorld(self);
    }
}

// Takes a node from the world's pool and appends it, with the object as owner, to the world's list
// for objects that run on the frame step clock or the one for those that do not.
WorldObjectNode* AddObjectNodeToWorld(PlacedObject* self)
{
    WorldObjectNode* node = (WorldObjectNode*)PopZeroedFreeSlot(&g_currentWorld->pool1C18);
    node->owner = self;
    if (self->frameStepClock != 0) {
        AppendToList(&g_currentWorld->list1C30, node);
    } else {
        AppendToList(&g_currentWorld->list1C24, node);
    }
    return node;
}

// Unlinks the node from the world's list it is on, clears the owner's ramp node and returns the
// node to the pool.
void RemoveObjectNodeFromWorld(WorldObjectNode* node)
{
    if (node->owner->frameStepClock != 0) {
        RemoveFromList(&g_currentWorld->list1C30, node);
    } else {
        RemoveFromList(&g_currentWorld->list1C24, node);
    }
    node->owner->rampNode = 0;
    PushFreeSlot(&g_currentWorld->pool1C18, node);
}

// Draws a full-screen colour fill: builds the packet from the colour at 0x60 and sends it to the
// VIF as a direct packet.
void DrawScreenFill(u8* a0)
{
    ScreenFillPacket f;
    f.value = *(s32*)&((DeferredRequest*)a0)->col;
    FillScreenColor(f.buf, (Rgba4*)&f.value, 0);
    PacketWriter* s = &g_vifPacketWriter;
    BeginDmaTag(s);
    WriteVifDirect(s, 0x2C, &f, 0);
    CloseDmaTag(s);
}

// Per-frame step of a timed colour fade: the colour goes from the start colour to the hold colour
// over fadeInTime, stays for holdTime, then fades out over fadeOutTime; at the end it stops and
// leaves the world's fade list. Does nothing unless the game is in state 3 and not in 1 or 2.
void UpdateColorFade(ColorFade* self)
{
    if (g_elementStack.state != 3) return;
    s32 g = g_displayMode;
    if (g == 1) return;
    if (g == 2) return;
    FadeColor out; Rgba4 a, b;

    f32 t = g_gameTime - self->startTime;
    f32 d;
    if (t < self->fadeInTime) {
        a = self->startColor; b = self->holdColor;
        d = self->fadeInTime;
    } else {
        t -= self->fadeInTime;
        if (t < self->holdTime) {
            a = self->holdColor; b = self->holdColor;
            d = self->holdTime;
        } else {
            t -= self->holdTime;
            if (!(t < self->fadeOutTime)) {
                self->running = 0;
                RemoveFromList(&g_currentWorld->list1CD8, self);
                return;
            }
            a = self->holdColor; b = self->endColor;
            d = self->fadeOutTime;
        }
    }
    f32 r = t / d;
    for (s32 i = 0; i < 4; i++)
        out.c[i] = (s32)((1.0f - r) * ((u8*)&a)[i] + r * ((u8*)&b)[i]);
    FadeEffectRequest q;
    q.f = -1.0f;

    q.fn = (void*)(void (*)(ColorFade*))DrawScreenFill;
    q.col = out;
    switch (self->mode) {
    case 0: q.mode = 1; break;
    case 1: q.mode = 0x10; break;
    }
    QueueDeferredRequest((DeferredRequest*)&q);
}

// Starts the fade if it is not running: stamps the game time and appends it to the world's list of
// fades.
void StartColorFade(ColorFade* a0)
{
    if (a0->running == 0) {
        a0->running = 1;
        a0->startTime = g_gameTime;
        AppendToList(&g_currentWorld->list1CD8, a0);
    }
}

// Gives the slot of n in a hash table of 512 twelve-byte entries that starts 0x84 bytes into base.
u8* GetHashedSlot(u8* base, s32 n)
{
    return (u8*)&((World*)base)->hashLists[(n * 0x95675) & 0x1FF];
}

// Tests one object found by id against the search mode (see GatherObjectsByMode) and, if it passes,
// appends it to arr (up to cap) and counts it. Mode 2 takes children of the root, 1 and 4 walk up
// the ancestors with their marks (4 picks the nearest group level), 3 takes objects flagged in bits
// 30..45, 5 takes all.
void CollectObjectByMode(PlacedObject* self, s32 mode, s32 a2, s32 a3, PlacedObject* a4, s32 cap,
                   s32* count, PlacedObject** arr, s32* lvlp)
{
    PlacedObject* a0;
    PlacedObject* prev;
    switch (mode) {
    case 2:
        if (self->alias != 0 && a3 == 0) return;
        if (self->parent == a4) goto add;
        return;
    case 1:
        if (self->alias != 0 && a3 == 0) return;
        a0 = (PlacedObject*)self->parent;
        if (a0 == 0) return;
        do {
            u64 lvl = a0->mark;
            if (lvl != 0) {
                if (lvl == 1) goto add;
                return;
            }
            if (a0->alias != 0) return;
            a0 = (PlacedObject*)a0->parent;
        } while (a0 != 0);
        return;
    case 3:
        if (self->desc->flags & 1) {
            if (self->flags & ((u64)0xF000 << 30)) goto add;
        }
        return;
    case 4:
        prev = 0;
        a0 = self;
        if ((self->desc->flags & 1) == 0) a0 = (PlacedObject*)self->parent;
        while (a0 != 0) {
            u64 f = a0->flags;
            if (f & ((u64)0xF000 << 30)) {
                s32 lvl = (s32)(a0->flags >> 42) & 0xF;
                u32 cur = *lvlp;
                if (!(cur < lvl)) {
                    if (!(lvl < cur)) goto add;
                    *lvlp = lvl;
                    *count = 0;
                    *arr = 0;
                    goto add;
                }
            }
            if (a0 == prev) return;
            if (a0->alias != 0 && (a0 != self || a3 == 0)) {
                s32 want = -1;
                if (a4 != 0) {
                    for (PlacedObject* v = a4; v; v = (PlacedObject*)v->parent) {
                        if (v->alias != 0) { want = v->alias->id; break; }
                    }
                }
                if (a0->alias->id != want) return;
                prev = (PlacedObject*)a0->parent;
            }
            a0 = (PlacedObject*)a0->parent;
        }
        if (*lvlp != 0x7FFFFFFF) return;
        goto add;
    case 5:
    add:
        if (a2 == 0 && IsObjectAttached(self) == 0) return;
        if (*count < cap) arr[*count] = self;
        (*count)++;
        return;
    default:
        return;
    }
}

// A member link of a group object's list at +0x2D0: the member and the next link.
struct GroupMemberLink {
    PlacedObject* obj;      // 0x00
    u8 pad04[4];
    GroupMemberLink* next;  // 0x08
};

// An object of a hashed id list (GetHashedSlot): its id, the next with the same hash, and for a
// group (its class flag 0x100) the list of its members.
struct HashedObject {
    const BaseObjectDescriptor* desc;     // 0x00
    u8 pad04[4];
    s32 id;                 // 0x08
    HashedObject* nextHashed; // 0x0C
    u8 pad10[0x30 - 0x10];
    ObjectAlias* alias;         // 0x30
    u8 pad34[0x2D0 - 0x34];
    GroupMemberLink* members; // 0x2D0
};

// Collects the objects that have the given object id (from the world's hash table, a group counting
// through its members) and lie in the scope that flags' low byte names, up to max, and returns the
// count. Marks the scope's ancestor chain for the duration so CollectObjectByMode can test it;
// 0x100 takes unattached objects, 0x200 returns the true count.
s32 GatherObjectsByMode(World* host, s32 flags, s32 id, void* rootp, s32 max, void* foundp)
{
    s32 count;
    s32 min;
    PlacedObject* mark;
    PlacedObject* p;
    ScopeMarker scope;
    GetHashedSlot((u8*)host, id);
    if (id == -1) {
        return 0;
    }
    s32 kind = flags & 0xFF;
    switch (kind) {
    case 1:
    case 3:
    case 4: {
        mark = (PlacedObject*)rootp;
        if (mark != 0 && !(mark->desc->flags & 1)) {
            mark = (PlacedObject*)mark->parent;
        }
        p = mark;
        s32 n = 0;
        while (p != 0) {
            n++;
            p->mark = n;
            p = (PlacedObject*)p->parent;
        }
        min = 0x7FFFFFFF;
        if (rootp == 0) {
            if (kind == 3) {
                return 0;
            }
            kind = 5;
        }
        break;
    }
    default:
        mark = 0;
        break;
    }
    count = 0;
    for (HashedObject* obj = *(HashedObject**)GetHashedSlot((u8*)host, id); obj != 0; obj = obj->nextHashed) {
        if (obj->id != id) {
            continue;
        }
        if (obj->desc->flags & 0x100) {
            for (GroupMemberLink* l = obj->members; l != 0; l = l->next) {
                CollectObjectByMode(l->obj, kind, flags & 0x100, 1, (PlacedObject*)rootp, max, &count, (PlacedObject**)foundp, &min);
            }
        } else if (obj->alias == 0 || obj->alias->id != obj->id) {
            CollectObjectByMode((PlacedObject*)obj, kind, flags & 0x100, 0, (PlacedObject*)rootp, max, &count, (PlacedObject**)foundp, &min);
        }
    }
    for (p = mark; p != 0; p = (PlacedObject*)p->parent) {
        p->mark = 0;
    }
    if (!(flags & 0x200) && max < count) {
        count = max;
    }
    return count;
}

// Gathers the first object that matches kind and arg with the given flags and 0x200; null if none.
BaseObject* FindFirstObjectById(World* self,s32 flags,s32 kind,void* arg)
{
    BaseObject* out=0;
    GatherObjectsByMode(self,flags|0x200,kind,arg,1,&out);
    return out;
}

// Gathers the first object that matches kind and arg with mode 0x204; null if none.
BaseObject* FindFirstObjectByIdMode4(World* self,s32 kind,void* arg)
{
    BaseObject* out=0;
    GatherObjectsByMode(self,0x204,kind,arg,1,&out);
    return out;
}

// Gathers the first object that matches kind and arg with mode 0x201; null if none.
BaseObject* FindFirstObjectByIdMode1(World* self,s32 kind,void* arg)
{
    BaseObject* out=0;
    GatherObjectsByMode(self,0x201,kind,arg,1,&out);
    return out;
}

// True when the class with this index in the class descriptor table has value in its chain of
// ancestors.
s32 IsClassOfKind(s32 index, s32 value)
{
    ClassKindNode* p = ((ClassKindNode**)g_classDescriptorTable)[index];
    while (p != 0) {
        if (p->value != value) {
            p = p->next;
        } else {
            return 1;
        }
    }
    return 0;
}

// Collects the objects of the class id (IsObjectOfKind) that the search scope allows, up to max,
// into found, and returns how many there are (more than max when flag 0x200 is set). Flags low
// byte: 3 walks the scope's ancestors, 2 its children, other values scan the world's per-class
// lists; 0x100 also takes unattached objects.
s32 GatherObjectsById(World* world, u32 flags, s32 id, void* scope, s32 max, void* foundp)
{
    PlacedObject* root = (PlacedObject*)scope;
    PlacedObject** found = (PlacedObject**)foundp;
    s32 c;
    s32 min;
    s32 kind;
    PlacedObject* obj;
    PlacedObject* mark;
    PlacedObject* p;
    s32 n;
    u32 i;

    if (id == -1) {
        return 0;
    }
    if (root == 0 && (flags & 5) == 0) {
        return 0;
    }
    kind = flags & 0xFF;
    c = 0;
    if (kind == 3) {
        // Retail reads obj here before anything sets it (lw 0($s0) with $s0 unset).
        if (!(obj->desc->flags & 1)) {
            obj = (PlacedObject*)obj->parent;
        }
        for (; obj != 0; obj = (PlacedObject*)obj->parent) {
            if (IsObjectOfKind(obj, id) != 0 && ((flags & 0x100) || IsObjectAttached(obj) != 0)) {
                if (c < max) {
                    found[c] = obj;
                }
                c++;
            }
        }
    } else if (kind == 2 && !(flags & 0x100)) {
        if (!(root->desc->flags & 1)) {
            return 0;
        }
        for (obj = (PlacedObject*)root->children.head; obj != 0; obj = (PlacedObject*)obj->next) {
            if (IsObjectOfKind(obj, id) == 0) {
                continue;
            }
            if (c < max) {
                found[c] = obj;
            }
            c++;
        }
    } else {
        switch (kind) {
        case 1:
        case 3:
        case 4:
            mark = root;
            if (mark != 0 && !(mark->desc->flags & 1)) {
                mark = (PlacedObject*)mark->parent;
            }
            p = mark;
            n = 0;
            while (p != 0) {
                n++;
                p->mark = n;
                p = (PlacedObject*)p->parent;
            }
            min = 0x7FFFFFFF;
            break;
        default:
            mark = 0;
            break;
        }
        for (i = id; i < 0x95 && IsClassOfKind(i, id); i++) {
            for (obj = (PlacedObject*)world->objectsById[i]; obj != 0; obj = (PlacedObject*)obj->nextById) {
                CollectObjectByMode(obj, kind, flags & 0x100, 0, root, max, &c, found, &min);
            }
        }
        for (p = mark; p != 0; p = (PlacedObject*)p->parent) {
            p->mark = 0;
        }
    }
    if (!(flags & 0x200) && max < c) {
        c = max;
    }
    return c;
}

// The same as FindFirstObjectById, through the id-based gather.
PlacedObject* FindFirstObjectByIdGathered(World* self,s32 flags,s32 kind,void* arg)
{
    PlacedObject* out=0;
    GatherObjectsById(self,flags|0x200,kind,arg,1,&out);
    return out;
}

// Gives the first object in the parent chain of list that is also in the parent chain of other.
BaseObject* FindCommonAncestor(BaseObject* list, BaseObject* other)
{
    for (BaseObject* p = list; p != 0; p = p->parent) {
        for (BaseObject* q = other; q != 0; q = q->parent) {
            if (p == q) {
                return p;
            }
        }
    }
    return 0;
}

LINKER_REMNANT(func_0015A8B0);

// Initialises the placed object with current and target scale 1 and a ramp profile of 1, 0.2, 0.1.
void InitScalingVolume(ScalingVolume* self)
{
    InitPlacedObject(self);
    f32* v = self->v;
    self->targetScale = 1.0f;
    self->currentScale = 1.0f;
    self->v[0] = 1.0f;
    v[1] = 0.2f;
    v[2] = 0.1f;
}

// Loads the placed object, then its mesh tables.
void LoadScalingVolume(ScalingVolume* self,void* other)
{
    LoadPlacedObject(self,other);
    ReadMeshTables(other,&self->out2D0,&self->out2D4,&self->out2D8,&self->out2DC);
}

// Updates the placed object and eases the scale toward its target with the ramp profile.
void UpdateScalingVolume(ScalingVolume* self, f32 dt)
{
    UpdatePlacedObject(self, dt);
    self->currentScale = ApproachValueWithRamp(self->currentScale, self->targetScale, g_frameDt, (RampProfile*)self->v, 0);
}

// Draws the placed object with its transform scaled uniformly by its current scale (at 0x2EC).
void DrawScalingVolume(ScalingVolume* self, void* arg1, void* arg2)
{
    ScaledDrawFrame f;
    BuildUniformScaleAboutPoint(0, &f.q0, self->currentScale);
    BuildPlacedObjectTransform(self, (Quad16*)arg2, (ScaledTransform*)f.m40);
    // retail's call passes the frame's own rows as the result's place, which an assignment of the
    // returned matrix does not
    ((void (*)(Quad16*, Quad16*, Quad16*))MultiplyMatrices)(f.m90, f.m40, &f.q0);
    f.m40[0] = f.m90[0];
    f.m40[1] = f.m90[1];
    f.m40[2] = f.m90[2];
    f.m40[3] = f.m90[3];
    DrawPlacedObject(self, arg1, f.m40);
}

struct TreeNode03;
struct FacePoint;

// Tests a world point against the volume's face tree: the point is moved into the volume's frame
// and divided by its scale; false if the scale is almost zero.
s32 IsPointInsideObjectFaces(ScalingVolume* self, void* point)
{
    Vec4 local;
    Vec4 k;
    if (self->currentScale < 0.0001f)
        return 0;
    TransformPointBetweenFrames(0, self, (Vec4*)point, &local);
    Vu0::Q(k) = Vu0::FromFloat(1.0f / self->currentScale);
    Vu0::Q(local) = Vu0::MulX(Vu0::Q(local), Vu0::Q(k));
    return IsPointInsideFaceTree((TreeNode03*)self->out2DC, (FacePoint*)&local);
}

extern f32 g_cyclerRotationRamp[6];
extern f32 g_cyclerFallPositionSteer[4];
extern f32 g_cyclerFallRotationSteer[4];

// The file's .data, 0x261F70 to 0x262180, in retail's order. The two packet streams
// (globals.h), whose labels are shorter than PacketWriter, are included from the disassembly.
// The spawn record's table, copied whole by InitSpawnRecord (func_001549C8), whose two statics'
// guards (D_00261F70, D_00261F74) the compiler writes out with the function, ahead of it.
SpawnTable g_spawnRecordDefaults = { {
    { { 0, 0, 0, 0 } },
    { { 0, 45, 0, 0 } },
    { { 0x41C80000, 0, 0, 0 } },
    { { 0, 0, 0, 0 } },
    { { 0, 0x3F800000, 0, 0 } },
    { { 1, 0, 0, 0 } },
    { { 0, 0, 0xFFFFFFFF, 0 } },
    { { 0, 0x3F800000, 0, 0 } },
    { { 0, 0, 0, 0 } },
    { { 0xFFFFFFFF, 0xFFFFFFFF, 0, 0 } },
    { { 0x3F800000, 0, 0, 0 } },
    { { 0x3F800000, 0x3F800000, 0, 0 } },
    { { 0, 0, 0, 0 } },
} };
s32 g_surfaceContactSounds[74] = { 82, 83, 84, 85, 0, 46, 0, 0, 0x41F00000, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F800000, 0, 0, 1, 0, 0, 0, 0, 0, 0xFFFFFFFF, 0, 0, 0x3F800000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50, 0, 0, 0x41A00000, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F800000, 0, 0, 1, 0, 0, 0, 0, 0, 0xFFFFFFFF, 0, 0, 0x3F800000, 0, 0, 0, 0, 0, 0, 0, 0 };
f32 g_spawnScaleRatioRange[2] = { 0.5f, 2.0f };
