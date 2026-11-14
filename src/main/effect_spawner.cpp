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
#include "effect_spawner.h"
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
struct CappedWordList;
struct EffectOwnerSlot;
struct PlacedObject;
struct SpawnSetup;
struct SpawnTargetOwner;
struct SpawnTargetRecord;

struct BumpAllocator;

struct Mat02;
struct Vec02;


// Types other files define, named by the parameters of their functions declared here.
struct ScaledTransform;


void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);

void SetEffectSpawnerActiveForever(EffectSpawner* self);
void SetEffectSpawnerInactive(EffectSpawner* self);

Rec50* GetOwnSpawnRecord(EffectSpawner* self, s32 mode);
void SetSpawnRecordKind(u8* self,s32 kind);

void* GetOwnedSpawnRecord(void* a0, s32 a1);
void SetSpawnRecordKind(u8* self,s32 kind);

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
    s32 out[4];
    s32 flag;
    s32 pad[3];
    s32 pair[2];
    u8 tail[0x18];
};

void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GenerateSpawnArrays(s32 n, void* b, s32* out);
void SpawnRecordEffects(void* b, void* c, s32 n, s32 o0, s32 o1, s32 o2, s32 o3);
void GenerateSpawnSetupPair(s32 n, void* b, s32* out, s32* pair);
void EmitParticleChunk(void* b, void* c, s32 n, s32 o0, s32 o1, s32 o2, s32 o3, s32 p0, s32 p1);

struct StreamWord {
    s32 value;
};

struct CappedWordList {
    u8 pad0[0x4C];
    s32 cap;
    U32P* items;
    void* source;
};

void* AllocateFrontMemory(s32 size);
struct BufferedStream;
void* ReadBufferedU8(BufferedStream* self);
StreamWord ReadBufferedU32(BufferedStream* self);

void* AllocateFrontMemory(s32 size);
void InitSpawnRecord(void* mem);
void LoadPlacedObject(PlacedObject* self, void* r);
s32 ReadBufferedS8(BufferedStream* self);
PathCurve* CreatePathCurve(s32 kind);
void ReadSpawnMesh(void* p, void* other);
u16 ReadBufferedU16(BufferedStream* self);
Rec50* GetOwnSpawnRecord(EffectSpawner* self, s32 mode);
struct CappedWordList;
void ReadCappedWordList(CappedWordList* self, s32 count, void* unused, void* src);

void CopyPlacedObject(PlacedObject* self, PlacedObject* src);

struct SpawnerLinkedObject { u8 pad00[0x18]; void* f18; u8 pad1C[0x18]; s32 f34; };

void PostLoadPlacedObject(PlacedObject* self);
Rec50* GetOwnSpawnRecord(EffectSpawner* self, s32 mode);
void ResolveSpawnRecordTargets(SpawnTargetRecord* rec, SpawnTargetOwner* owner);
s32 IsObjectOfKind(BaseObject* list, s32 key);
void* AppendQueuedCall(World* self, void* code, void* arg, s32 c, s32 d);

void* CopyToFrontMemory(s32 size, void* owner);

extern f32 g_gameTime;


void SetEffectSpawnerActiveForever(); // stays without its argument: SetEffectSpawnerLimit leaves self in a0 and retail does not set it again


s32 IsEffectSpawnerActive(EffectSpawner* self);

void InitPlacedObject(PlacedObject* self);
void SetListLinkOffset(List01* self, s32 offset);

struct RangeEmitter;
void AddRangeEntry(RangeEmitter* self, s32 a1, s32 a2, f32 f12, f32 f13, f32 f14, f32 f15, void* owner);

struct LookSource;
struct WorldListedObject;
void ApplyLookSourceToListedObject(WorldListedObject* self, LookSource* src);
void CopyEffectOwnerMargin(EffectOwner* a, Rec50* b);
f32 RandomFloatInRange(f32,f32);

extern "C" void* FillMemory(void* p, s32 value, s32 size);



void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateBackMemory(s32 size);
void CopyMemory(void* dst, void* src, u32 size);
void InitActiveSetSolver(ActiveSetSolver* loc, s32 count);
void RunActiveSetSolver(ActiveSetSolver* self, s32 a1, s32 a3, s32 a4, s32 a5, s32 a6);

struct EffectOwnerSlot { s32* f0; s32* f4; s32 f8; };
EffectOwner* AcquireEffectOwner(World* self, s32 flag);
void CopyEffectOwnerMargin(EffectOwner* a, Rec50* b);
Effect* CreateEffect(s32 kind, EffectOwner* sys);
void SetTrailSegmentAnchor(void* selfv, s32 kind, void* extra);
void FillLookDirectionBlock(Effect* a, Rec50* b);
f32 RandomFloatInRange(f32 a, f32 b);
s32 IsListEmpty(List01* p);

#define AT(T, p, o) (*(T*)((u8*)(p) + (o)))
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
    f32 f30;
    s32 f34;
    void* f38;
    u8 pad1[0xC];
};

struct BroadcastRecord { u8 pad0[0x120]; s32 f120; u8 pad1[0x8C]; s32 f1B0; };

struct KeyedObject { BroadcastFn* vtbl; u8 pad0[0x8C]; BroadcastRecord* f90; };

struct KeyedObjectList { u8 pad0[0x90]; s32 count; KeyedObject* items[1]; };

struct KeyedWorldView { u8 pad0[0x1CE8]; KeyedObjectList* list; };

struct __attribute__((aligned(16))) SpawnBlock { Quad16 q[8]; };
struct __attribute__((aligned(16))) SpawnTail { Quad16 q[4]; };
extern "C" void* FillMemory(void* p, s32 value, s32 size);
struct SpawnFlags { s32 z; s32 b; s32 c; SpawnFlags() { FillMemory(this, 0, sizeof(*this)); } };
struct __attribute__((aligned(16))) SpawnRecord { u8 pad0[0x20]; Quad16 self_copy; u8 pad1[0x30]; Quad16 a1_copy; u8 pad2[0x30]; SpawnBlock blk; s32 f120; u8 pad3[0x8C]; SpawnTail tail; u8 pad4[0x10]; };

void InitSpawnRecord(void* mem);
void SpawnEffectsFromRecord(s32 count, Rec50* rec, void* flags);


struct BriefEffectParams { u8 pad0[0xC]; s32 fC; };
struct BriefEffectSource { u8 pad0[0x278]; BriefEffectParams* f278; };
typedef void (*EffectStartFn)(Effect* self, void* a, s32 z, f32 f);

Effect* CreateEffect(s32 kind, EffectOwner* sys);

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

void BindAnimatorRecord(CursorAnimator* self);
AnimRecord* FindAnimRecord(s32 key);
void SetCrossfadeMode(CrossfadeAnimator* self, s32 mode);

s32 IsObjectAttached(BaseObject* self);
void RemoveObjectNodeFromWorld(WorldObjectNode* self);
extern PackedFloatPair D_00262180;
extern PackedFloatPair D_00262188;
extern PackedFloatPair D_00262190;
extern PackedFloatPair D_00262198;
extern PackedFloatPair D_002621A0;
extern PackedFloatPair D_002621A8;
extern PackedFloatPair D_002621B0;
extern PackedFloatPair D_002621B8;
extern PackedFloatPair D_002621C0;

void InitCollider(Collider* self);
void AppendToList(List01* self, void* item);

void* CloneSharedSpawnRecord(void* x);

struct MemberTargetObject;
s32 IsObjectOfKind(BaseObject* list, s32 key);

// A message held back by SendMessageAfterDelay (a slot of the world's pool at +0x1BD0, in its
// list at +0x1BDC, linked at +0x64): the receiver, the 0x50-byte message, the time it is due.
struct DelayedMessageBody { Quad16 q[5]; };
struct DelayedMessage { void* owner; u8 pad0[0xC]; DelayedMessageBody body; f32 due; };

extern f32 g_gameClock[];

struct ListLink;
void* PopFreeSlot(Pool6C* pool);
void ClearListLinks(ListLink* p);
void AppendToList(List01* self, void* item);
void HandleSpawnMessage(void* self, void* body);

void InitSoundParams(SoundRecord** self);


void* CreateTypedRecord(s32 index, void* a1, BaseObject* a2, s32 a3, s32 a4);
void CopyMemory(void* dst, void* src, u32 size);

struct MemberTargetObject {
    u8 pad0[0x18];
    void* f18;
    u8 pad1[0x20 - 0x1c];
    s32 f20;
    u8 pad2[0x34 - 0x24];
    s32 f34;
    u8 pad3[0x7c - 0x38];
    MemberTargetObject* f7c;
};

void ResolveSpawnRecordTargets(SpawnTargetRecord* rec, SpawnTargetOwner* owner);

extern f32 g_gameTime;
f32 RandomFloatInRange(f32 a, f32 b);

extern f32 g_gameTime;
f32 RandomFloatInRange(f32 a, f32 b);
void SetCursorFrame(AnimCursor* cur, s32 idx);


void* AllocateZeroedFrontMemory(s32 size);
void InitSpawnRecord(void* p);
PathCurve* CreatePathCurve(s32 kind);
extern s32 g_objectCyclerStartLinks[6];

void ResolveObjectLinks(void* self, s32 n, void* p);
f32 RandomFloatInRange(f32 a, f32 b);
void SetObjectCyclerState(ObjectCycler* self, s32 x);
void StartPlacedObject(PlacedObject* self);



void* PopZeroedFreeSlot(Pool6C* pool);
void AppendToList(List01* self, void* item);



void RemoveFromList(List01* list, void* item);
void PushFreeSlot(Pool6C* list, void* item);
void PushFreeSlot(Pool6C* list, void* item);

extern f32 g_frameDt;
void UpdatePlacedObject(void* self, f32 dt);
struct RampProfile;
f32 ApproachValueWithRamp(RampProfile* k, f32* out, f32 x, f32 y, f32 z);

struct ScaledDrawFrame { Quad16 q0; u8 pad1[0x30]; Quad16 m40[4]; u8 pad2[0x10]; Quad16 m90[4]; };

void BuildUniformScaleAboutPoint(void* point, void* out, f32 s);
void BuildPlacedObjectTransform(PlacedObject* self, Quad16* src, ScaledTransform* dst);
void* MultiplyMatrices(Quad16* out, void* b, Quad16* in);
Mat4A MultiplyMatrices(const Mat4A& a, const Mat4A& b);
void DrawPlacedObject(PlacedObject* self, void* b, void* m);


struct ScreenFillPacket { u8 buf[0x2C0]; s32 value; };

void FillScreenColor(u8* buffer, Rgba4* color, s32 flag);
void BeginDmaTag(PacketWriter* self);
void WriteVifDirect(PacketWriter* self, s32 n, void* buf, s32 flag);
void CloseDmaTag(PacketWriter* self);

extern f32 g_gameTime;


void AppendToList(List01* self, void* item);


void LoadPlacedObject(PlacedObject* self, void* r);
void ReadMeshTables(void*,void*,void*,void*,void*);

AnimCursor* FindAnimatorCursor(CursorAnimator* self, const AnimRecord* key);

void AddRangeEntry(RangeEmitter* self, s32 a1, s32 a2, f32 f12, f32 f13, f32 f14, f32 f15, void* owner);

struct CyclerEventMessage {
    u8 pad0[0x8];
    f32 f8;
    s32 fC;
    u8 pad1[0x20 - 0x10];
    Quad16 f20;
    Quad16 f30;
};
struct __attribute__((aligned(16))) GroupForwardMessage {
    s32 f0;
    u8 pad0[0x10 - 0x4];
    Quad16 f10;
    Quad16 f20;
    u8 pad1[0x50 - 0x30];
};

void SetObjectCyclerState(ObjectCycler* self, s32 state);
void ApplyColliderImpulseEvent(void* a0, f32 x, void* a1, void* a2);

// NEAR: the last float zero (f16) is scheduled into the jal delay slot instead of before the integer argument moves.


void CopyCollider(Collider* self, Collider* other);
s32 IsInList(List01* self, void* item);
void RemoveFromList(List01* list, void* item);
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

// NEAR: the last float zero (f16) is scheduled into the jal delay slot instead of before the integer argument moves.


void StopSoundRecord(PlayingSound* self, s32 n);
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

// The colour UpdateColorFade blends, word-aligned, and its request: DeferredRequest's layout
// with that colour at +0x60 (DeferredRequest's Rgba4 would copy it unaligned).
struct __attribute__((aligned(4))) FadeColor { u8 c[4]; };
struct FadeRequest { void* fn; f32 f; s32 mode; u8 pad[0x54]; FadeColor col; u8 pad2[0x1C]; };
extern s32 D_00275BC4;

extern s32 D_00270458;
extern f32 g_gameTime;
void RemoveFromList(List01* list, void* item);
void DrawScreenFill(u8* a0);
void QueueDeferredRequest(DeferredRequest* src);

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
s32 IsObjectOfKind(BaseObject* list, s32 key);
void* CreateTypedRecord(s32 index, void* a1, BaseObject* a2, s32 a3, s32 a4);

struct ClassKindNode { ClassKindNode* next; s32 value; };

extern u8 D_00247448[];

s32 IsObjectAttached(BaseObject* self);

typedef int Quadword128 __attribute__((mode(TI)));

extern f32 g_gameClock[];

void UpdateCollider(Collider* self, f32 dt);
void SetObjectCyclerState(ObjectCycler* self, s32 mode);
s32 ChooseObjectCyclerNextState(ObjectCycler* self);
s32 FindObjectCyclerGroundPoint(ObjectCycler* self, Quadword128* out);
void SendObjectCyclerMessage(ObjectCycler* self);
s32 IsObjectCyclerUnsupported(ObjectCycler* self);
s32 IsActiveColliderNearObjectCycler(ObjectCycler* self);
f32 RandomFloatInRange(f32 a, f32 b);
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

void InitPlacedObject(PlacedObject* self);

extern f32 g_gameClock[];


void HandleSpawnMessage(void* a, void* b);
void RemoveFromList(List01* list, void* item);
void PushFreeSlot(Pool6C* list, void* item);


// A walk of a list that RemoveFromList keeps valid: the frame is pushed on g_activeListFrames
// (list_iter.h) and each step reads the next item through the link.
struct BeginListWalk {
    static void Of(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = g_activeListFrames;
        g_activeListFrames = it;
    }
};

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
void LoadCollider(Collider* self, BufferedStream* in);
void ResolveObjectLinks(ObjectCycler* self, s32 n, void* table);
void FindOrBuildMemberGroup(void** out, void* self);
s32 IsInList(List01* self, void* item);
void RemoveFromList(List01* list, void* item);

struct CyclerDrawParams { u8 pad[0x40]; f32 scale; u8 pad2[0x10 - 4]; };
extern f32 g_gameTime;
extern f32 D_00262230[4];
extern f32 D_00262240[4];
extern f32 g_unitRange[];
void BuildPlacedObjectTransform(PlacedObject* self, Quad16* src, ScaledTransform* dst);

s32 IsObjectOfKind(BaseObject* list, s32 key);
s32 IsObjectAttached(BaseObject* self);
s32 IsClassOfKind(s32 index, s32 value);
void CollectObjectByMode(PlacedObject* obj, s32 kind, s32 all, s32 zero, PlacedObject* root, s32 max,
                   s32* countOut, PlacedObject** found, s32* minOut);

void LoadAnimatorBase(CursorAnimator* self, const AnimatorParams* src);


// An entry of a GCC 2.95 vtable as this file defines D_0024A220 (the font table).
struct VtableEntry { s32 delta; void (*fn)(); };
struct FloatPair2 { f32 x; f32 y; };
extern const VtableEntry g_fontMethods[22];
void* AllocateObjectMemory(u32);
void CopyFont(Font*, Font*);

extern s32 g_fonts[];
extern s32 g_defaultFont;

FontGlyph* FindFontGlyph(Font* a, s32 b);

void RewindTextReader(TextReader* self);
s32 ReadTextChar(TextReader* self);

// The packet memory a GIF writer fills: quadwords.
typedef u64 UQuadword128 __attribute__((mode(TI)));

extern u8 D_00212160[];
extern u8 D_00215C50[];

void* InitGifPacket(void* p);
void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);
void BeginGifTag(void* p, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(void* p, s32 a, s32 b);
void EndGifPacket(void* p);
void WriteVifFlush(PacketWriter* b);
void WriteVifDirectFromWriter(PacketWriter* a0, PacketWriter* a1);
void AddDmaRefTagIfChanged(void* self, void* a, void* b);
void AddDmaEndTag(PacketWriter* self);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);

void CopyFontMetrics(Font* self, Font* dst);

FontGlyph* FindFontGlyph(Font* table, s8 key);

void CloseDmaTag(PacketWriter* self);
void AddDmaRefTag(void* obj, s32 a, s32 b);
void BeginDmaTag(PacketWriter* self);

void SetFontClipRect(Font* unused, Vec4U* v, PacketWriter* obj);
s32 AddFontImagesToFrame(Font* self, void* obj);
void BeginGifTag(void* obj, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(void* obj, s32 tag, s64 value);
void BeginGifRegListTag(void* obj, s32 tag, s64 value);

extern s32 g_defaultFont;

void CopyMemory(void* dst, void* src, u32 size);


extern s32 g_vif1Channel;
extern s32 g_gifChannel;

void SendGsPacketAndWait(s32 channel, void* b);
void ActivateRenderFrame(void* a, s32 b);


void* InitGifPacket(void* p);
void* InitPacketWriter(PacketWriter* self);

void ConstructPacketWriters(s32 flag, s32 code);

struct GroundProbe {
    Vec02 q;
    s32 a;
    s32 b;
};

extern f32 g_gameClock[];

typedef s32 (*ObjectFilterFn)(void* a, void* b);

struct GroundCandidate;
struct GroundFilterContext;
s32 IsCyclerGroundCandidate(GroundFilterContext* a0, GroundCandidate* a1);
void PushBackMemoryMark(void* self);
s32 FindNearestSpanObject(s32 flags, Vec02* a1, Vec02* a2, s32 count, Collider** list, ColliderSpan* out);
void PopBackMemoryMark(void);
void GatherCollidersInSphere(World* world, Collider* skip, f32 radius, Vec02* center, s32 (*filter)(void*, Collider*), void* arg, s32* count, Collider*** out);

void AddDmaRefTag(void* list, u32 count, s32 value);
extern s32 D_0026230C;

void BeginGifTag(void* obj, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(void* obj, s32 a, s32 b);
void EndGifPacket(void* obj);
void AddDmaEndTag(PacketWriter* self);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);

void WriteGsFinishPacket(void* self, void* p, u8** n);
void CloseDrawBuffer(void* obj, void* a, u8** b);
void ClearList(List01* p);
extern "C" s32 PostSemaphore(void* a);

extern List01 D_002622E0;
extern List01 D_002622F0;
extern List01 g_deferredReleaseListC;
extern s32 g_buildFrameData;
extern void* g_frameReadySemaphore;



extern s32 g_drawFrameData;
extern s32 g_maskedImagesPacket;
extern s32 g_gifChannel;

void SwitchActiveImageMask(s32 value);
struct DmaChannel;
extern "C" void StartDmaChain(DmaChannel* ch, void* tadr);


void RewindTextReader(TextReader* self);
s32 ReadTextChar(TextReader* self);

void RewindTextReader(TextReader* self);
s32 ReadTextChar(TextReader* self);


void RewindTextReader(TextReader* self);
s32 ReadTextChar(TextReader* self);

s32 WrapTextLines(TextReader* self, f32 limit);

extern s8 g_fontEscapeKeys[];
extern s32 g_fonts[];

s32 WrapFontString(Font* self, u8* s, f32 w);

// NEAR: the first load of self->p54 goes to $v0 (retail $v1), so two
// pointer loads differ in register choice; everything else matches.

struct FontUploadFrame { PacketWriter a; u8 buf[0x100]; };
PacketWriter* InitGifPacket(PacketWriter* p);
s32 AllocateBump(s32* self,s32 size);
void BuildImageTexRegister(ImageRecord* self, u32 a1);
void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);
void StartImageUpload(ImageRecord* d, u32 dbp, void* ctx);
void DetachPacketBufferCopy(PacketWriter* self, s32* count, u32* begin, s32* out, s32 flags);
void BuildPaletteTexRegister(PaletteRecord* self, u32 a1);
void StartPaletteUpload(PaletteRecord* e, s32 v, void* ctx);

// Matched: for loop over i with D_00262264 + i * 0x88.

extern s32 g_fontCount;
extern u8* g_fontRecords;

void InitBumpAllocator(BumpAllocator* p, s32 value, s32 other);
void UploadFontImages(Font* self, void* arg);


void AddGifRegListFloat(PacketWriter* s, u32 tag, f32 value);
void AddGifUvRegListEntry(PacketWriter* s, s32 a, s32 b);
void AddGifXyzfRegListEntry(PacketWriter* s, s32 a, s32 b, s32 c, s32 d);

FontGlyph* FindFontGlyph(Font* self, s8 key);

s32 WrapTextLines(TextReader* self, f32 limit);
f32 MeasureTextWidth(TextReader* self);



extern u32 D_002C3B00[];
extern u8 D_00148D74[];
extern s32 g_codeChecksumFailed;

extern void* g_frameDoneSemaphore;
extern volatile s32 g_renderThreadWaiting;
extern void* g_drawingFrame;
extern s32 D_002626CC;

extern "C" s32 AwaitSemaphore(void* a);
void SendRenderFrameToDma(RenderFrame* self, s32 flag);
void BlitFrameToDisplay(void);
void FlipDisplayFrame(void);
void ReleaseFrameNodes(RenderFrame* self);
void ClearScreenOwner(s32 owner);

struct FontHeader {
    u16 u0;
    u16 u2;
    u8 b4;
    u8 b5;
    u8 b6;
    u8 b7;
    f32 f8;
    u16 uC;
    u16 padE;
};



void ReadBufferedStreamBytes(BufferedStream* self, s32 remaining, void* out);
void* AllocateFrontMemory(s32 n);
extern s32 D_00262258;
extern s32 D_0026225C;

FontGlyph* FindFontGlyph(Font* self, s8 key);
s32 AddFontImagesToFrame(Font* self, void* obj);
void BeginGifTag(PacketWriter* s, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(PacketWriter* s, s32 a, u64 b);
void BeginGifRegListTag(PacketWriter* s, s32 a, u64 b);
void AddGifRegListFloat(PacketWriter* s, u32 tag, f32 value);
void AddGifUvRegListEntry(PacketWriter* s, s32 a, s32 b);
void AddGifXyzfRegListEntry(PacketWriter* s, s32 a, s32 b, s32 c, s32 d);

// NEAR: CRC table loop: retail keeps inner counter k in v1 and n*4 in a1; ours swaps them (5 insns)

extern u8 D_003C3B00[], D_005C3B00[];
extern void* g_frameReadySemaphore;
extern void* g_frameDoneSemaphore;
extern s32 g_mainAndRenderThreads[];
void SetListLinkOffset(List01* self, s32 value);
void AddInterruptHandler(s32 a0, void (*fn)(void), s32 a2);
s32 EnableInterruptCause(s32 a0);
void* CreateLockSemaphore(s32 initCount, s32 maxCount);
void RunThread(void* a, s32 b);
void func_0015E678(void);

void RewindTextReader(TextReader* self);

struct GroundFilterContext { u8 pad[0x50]; s32 f50; };
struct GroundCandidate { u8 pad0[0x50]; s32 f50; u8 pad1[0x278]; u32 f2CC; u8 pad2[0x268]; u64 f538; };

extern void* g_frameReadySemaphore;
extern void* g_frameDoneSemaphore;
extern u32 D_00262314;
extern s32 g_vif1Channel;
extern s32 g_gifChannel;
extern s32 D_002626CC;

void VerifyCodeChecksum(void);
extern "C" s32 AwaitSemaphore(void* p);
void ActivateRenderFrame(RenderFrame* f);
void ApplyPendingDisplayFlip(void);
void SendGsPacketAndWait(s32 channel, void* b);
void BlitFrameToDisplay(void);
extern "C" s32 WaitDmaChannel(DmaChannel* ch, s32 mode, s32 timeout);
void FlipDisplayFrame(void);


struct FrameNode {
    u8 pad0[0x14];
    u8* f14;
    u8 pad18[0x1088 - 0x18];
    void* f1088;
};


s32 IsListEmpty(List01* l);
void RemoveFromList(List01* list, void* item);
void AppendToList(List01* self, void* item);
void ClearList(List01* l);



typedef struct StringLayout StringLayout;
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long s64;
typedef unsigned long u64;
typedef float f32;
struct StringLayout
{
  f32 f0;
  f32 f4;
  f32 f8;
  f32 fC;
  s32 f10;
  s32 f14;
  s32 f18;
};


void RewindTextReader(TextReader* self);
s32 ReadTextChar(TextReader* self);
void SetTextDefaultColor(TextReader* self, Rgba_137248* p);

// Inline text codes: ~RRGGBB / ~. colour, &<id> / &. font, ^<d><d> / ^. scale.
s32 FindFontByKeyChar(s32 id);
void CopyFont(Font* font, Font* out);
void PopFontScale(Font* font);
void PushFontScale(Font* font, f32 a, f32 b);

struct FrameGlyph {
    Font* f0;
    s8 key;
    u8 p5[3];
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    u32 color;
};
struct FrameRect { f32 x, y, w, h; };

FontGlyph* FindFontGlyph(Font* self, s8 key);
void PushFontScale(Font* p, f32 a, f32 b);
void PopFontScale(Font* p);
void DrawFontQuad(Font* self, u32 color, f32 x0, f32 y0, f32 x1, f32 y1,
                   f32 u0, f32 v0, f32 u1, f32 v1, PacketWriter* s);
extern void* g_drawingFrame;
extern void* g_frameReadySemaphore;
extern volatile s32 g_renderThreadWaiting;

extern void* g_frameDoneSemaphore;
extern s32 g_nextBuildFrameIndex;
extern s32 g_buildFrameData;

void SetScreenOwner(s32 v);
extern "C" s32 AwaitSemaphore(void* a);
void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);
void BeginDmaTag(PacketWriter* self);

// The spawn record (SpawnRecord above, 0x200 bytes) as InitSpawnRecord fills it: nine vectors,
// an effect's spawn block (Blk05, the block SpawnBlock is a view of) and a table of thirteen
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
    Blk05 block;            // 0xA0
    SpawnTable table;       // 0x120
    u8 pad1F0[0x200 - 0x1F0];
};
typedef char check_SpawnRecordParts[sizeof(SpawnRecordParts) == 0x200 ? 1 : -1];
extern SpawnTable D_00261F80;

// The vectors and the block are built once each, as function-local statics with brace
// initialisers: a vector copied from a global makes each run at run time, through a temporary
// (docs/toolchain/large-functions.md, "A brace initialiser's union member is a CLOBBER").
void InitSpawnRecord(void* mem)
{
    SpawnRecordParts* self = (SpawnRecordParts*)mem;
    static SpawnVectors vectors = { {
        { { 0, 0, 0, 0 } }, *(Quad16*)&D_00248D30, { { 0, 0, 0, 0 } }, { { 0, 0, 0, 0 } }, { { 0, 0, 0, 0 } },
        *(Quad16*)&g_unitXVector, { { 0, 0, 0, 0 } }, { { 0, 0, 0, 0 } }, *(Quad16*)&D_00248D30
    } };
    static Blk05 block = {
        { 750.0f, 750.0f, 1.0f }, { 0.0f, 0.0f, -1500.0f }, { -1.0f, 0.0f, 0.0f }, *(Quad16*)&g_unitZVector, 0.0f, 0.0f, 0.0f, 200,
        { 1.0f, 1.0f, 0.0f }, { { 0, 0, 0, 0 } }, { 1.0f, 0.0f, -1.0f }
    };
    FillMemory(self, 0, 0x200);
    self->f0 = 1;
    self->vectors = vectors;
    self->block = block;
    self->table = D_00261F80;
}

void InitEffectSpawner(EffectSpawner* self)
{
    InitPlacedObject(self);
    self->f2D8=-1;
    self->f2E0=10.0f;
    self->id2F8[0]=-1;
    self->id2F8[1]=-1;
    self->id304=-1;
    self->id300=-1;
    self->id30C=-1;
    self->f2D4=-1;
    self->f2DC=10.0f;
    self->f340=-1.0f;
    self->f310=-1;
    SetListLinkOffset((List01*)self->list314,0x320);
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
    Vec02* vertices;        // 0x04
    s32 triangleCount;      // 0x08
    MeshTriangle* triangles;    // 0x0C
    Vec02* normals;         // 0x10
    f32 totalArea;          // 0x14
    u8 pad18[0x20 - 0x18];
    Vec02 extent;           // 0x20
};

void ReadSpawnMesh(void* p, void* other)
{
    MeshData* m = (MeshData*)p;
    s32 i;
    m->vertexCount = ReadBufferedU16((BufferedStream*)other);
    m->vertices = (Vec02*)AllocateFrontMemory(m->vertexCount << 4);
    m->normals = (Vec02*)AllocateZeroedFrontMemory(m->vertexCount << 4);
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
            Vec02* v = &m->normals[t->corner[i]];
            Vu0::Q(*v) = Vu0::Add(Vu0::Q(*v), n);
        }
    }
    ReadBufferedVector3((BufferedStream*)other, &m->extent);
    for (i = 0; i < m->vertexCount; i++) {
        Vu0::Q(m->normals[i]) = Vu0::NormalizeOr(Vu0::Q(m->normals[i]), Vu0::Q(g_unitZVector));
    }
}

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

void LoadEffectSpawner(EffectSpawner* self, BufferedStream* count)
{
    void* mem = AllocateFrontMemory(0x200);
    self->rec = (Rec50*)mem;
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
        void* b = GetOwnSpawnRecord(self, 1);
        ReadCappedWordList((CappedWordList*)((u8*)b + 0x130), n, self, count);
    }
}

void CopyEffectSpawner(EffectSpawner* self, EffectSpawner* src)
{
    CopyPlacedObject(self, src);
    self->rec->uses++;
}

void ReparentEffectSpawnerToSource(EffectSpawner* self)
{
    self->desc->m15(self, (BaseObject*)self->rec->target);
}

void ResolveEffectSpawnerLinks(EffectSpawner* self)
{
    Rec50* s2;

    PostLoadPlacedObject(self);
    if (self->key2F8 == -1 && self->id304 == -1 && self->id30C == -1 && self->id300 == -1) {
        Rec50* p = self->rec;
        if (p->kind != 3 && (p->f120 != 0 || p->f188 == -1)) goto tail;
    }
    s2 = GetOwnSpawnRecord(self, 1);
    if (self->id2F8[0] != -1) {
        SpawnerLinkedObject* r = (SpawnerLinkedObject*)FindFirstObjectById(self->world, 0x104, self->id2F8[0], self);
        s2->target = r;
        if (r != 0) AppendQueuedCall(self->world, (void (*)(void))ReparentEffectSpawnerToSource, self, 0, 0);
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
        s2->value20 = r->f34;
        s2->target = r->f18;
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
    if (self->rec->f1B0 != -1)
        self->rec->f120 = 1;
    if (self->f2D4 == -1) {
        if (self->chance != 0.0f || self->continuous != 0)
            self->f2D4 = 3;
        else if (self->f2F4 != 0.0f)
            self->f2D4 = 1;
        else
            self->f2D4 = 0;
    }
    switch (self->f2D4) {
    case 2:
        self->f330 = 3.4028235e+38f;
        self->f328 = RandomFloatInRange(self->delay.lo, self->delay.hi);
        if (self->continuous != 0)
            SetEffectSpawnerActiveForever(self);
        else if (RandomFloatInRange(0.0f, 1.0f) <= self->chance)
            SetEffectSpawnerActiveFor(self, RandomFloatInRange(self->active.lo, self->active.hi));
        break;
    case 3:
        self->f330 = 3.4028235e+38f;
        self->f328 = RandomFloatInRange(self->delay.lo, self->delay.hi) * 60.0f;
        if (self->continuous != 0)
            SetEffectSpawnerActiveForever(self);
        else if (RandomFloatInRange(0.0f, 1.0f) <= self->chance)
            SetEffectSpawnerActiveFor(self, RandomFloatInRange(self->active.lo, self->active.hi));
        break;
    case 0:
    case 1:
        self->f330 = 1.0f;
        self->f32C = 1.0f;
        self->f328 = RandomFloatInRange(self->delay.lo, self->delay.hi);
        break;
    }
    self->f334 = 1.0f;
    Rec50* rec = self->rec;
    if (rec->kind == 1) {
        f32* box = (f32*)((u8*)rec + 0x20);
        if (self->id2F8[0] != -1) {
            f32 dx = __builtin_fabsf(box[4] - box[0]);
            f32 dy = __builtin_fabsf(box[5] - box[1]);
            f32 dz = __builtin_fabsf(box[6] - box[2]);
            f32 m = dy < dx ? (dz >? dx) : (dz >? dy);
            self->margin = m * 0.5f;
        }
        if (self->f2E4 != 0) {
            if (self->f2F4 != 0.0f)
                self->f334 = (box[4] - box[0]) * (box[5] - box[1]) * (box[6] - box[2]) * 1e-6f;
            else
                self->f334 = (box[5] - box[1]) * (box[6] - box[2]) * 1e-4f;
        }
    }
    if (self->f310 != -1) {
        EffectSpawner* copy = (EffectSpawner*)FindFirstObjectByIdMode1(self->world, self->f310, 0);
        if (copy == 0) {
            copy = (EffectSpawner*)CreateTypedRecord(0x50, self->world, 0, self->f310, -1);
            copy->rec = (Rec50*)AllocateFrontMemory(0x200);
            *copy->rec = *self->rec;
            copy->rec->target = 0;
            copy->f2D4 = self->f2D4;
            copy->f2D8 = self->f2D8;
            copy->delay = self->delay;
            copy->f2E4 = self->f2E4;
            copy->chance = self->chance;
            copy->active = self->active;
            copy->f2F4 = self->f2F4;
            copy->continuous = self->continuous;
            copy->flags = ((copy->flags | (1ULL << 32)) & ~(3ULL << 40)) | (1ULL << 40);
            copy->rot = copy->m110 = self->rot;
            if (copy->desc->m0F != 0)
                copy->desc->m0F(copy);
        }
        self->f34C = 0;
        AppendToList((List01*)copy->list314, self);
        InheritFlaggedAncestorValue(self);
    }
}

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

Rec50* CloneSharedSpawnRecord(Rec50* self)
{
    Rec50* n;
    if (self->uses < 2) return self;
    n = (Rec50*)CopyToFrontMemory(0x200, self);
    if (self->kind == 3 && self->f24 != 0) {
        n->f24 = CopyToFrontMemory(0x28 * self->value20, self->f24);
    }
    n->uses = 1;
    self->uses -= 1;
    return n;
}

Rec50* GetOwnSpawnRecord(EffectSpawner* self, s32 mode)
{
    if (mode == 1) {
        self->f34C = mode;
        self->rec = CloneSharedSpawnRecord(self->rec);
    }
    return self->rec;
}

EffectSpawner* MarkEffectSpawnerChanged(EffectSpawner* self, s32 value)
{
    if (value == 1) {
        self->f34C = value;
    }
    return self;
}

void AddSpawnRangeEntry(EffectSpawner* self, s32 a, s32 b, f32 x, f32 y, f32 z, f32 w)
{
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
    Vec02 size;
    Vec02 lo;
    Vec02 hi;
    // One register value serves the box: the margin on every axis, then, with no target, its
    // negative for the low corner. The record is read between the splat and the copy
    // (docs/toolchain/gcse.md, "A splat split between a GPR and a VU0 copy").
    u128 margin = Vu0::Splat(self->margin);
    Rec50* rec = self->rec;
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
    if (self->rec->f120 != 0) {
        return;
    }
    WorldListedObject* w = (WorldListedObject*)self->held348;
    if (w == 0) {
        return;
    }
    for (OwnedRecord* r = (OwnedRecord*)w->members.head; r != 0; r = r->next) {
        Vec02* pts = r->points[r->bank];
        for (s32 i = 0; i < r->count; i++) {
            Vec02* p = &pts[i];
            Vec02 delta;
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

void RandomizeEffectSpawnerDelay(u8* self);
void UpdatePlacedObject(PlacedObject* self, f32 f);
s32 CountListItems(List01* list);
void WrapSpawnerParticlesIntoBox(EffectSpawner* self);
void SetEffectSpawnerActiveFor(EffectSpawner* self, f32 f);
void SetEffectSpawnerActiveForever(EffectSpawner* self);
s32 IsEffectSpawnerActive(EffectSpawner* self);

void UpdateEffectSpawner(EffectSpawner* self, f32 dt)
{
    ListFrame frame;

    if (self->f34C != 0) {
        RandomizeEffectSpawnerDelay((u8*)self);
    }
    UpdatePlacedObject(self, dt);
    if (self->f310 != -1) {
        return;
    }
    if (!IsListEmpty((List01*)self->list314)) {
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
                r = o->f80 * cam->fB0;
                d = Vu0::Sub(Vu0::Q(o->v140), Vu0::Q(cam->f40));
                if (!(r * r > Vu0::ToFloatMoved(Vu0::Dot(d, d)))) {
                    near = 0;
                }
                if (near) {
                    goto spawn;
                }
            }
            o = *(PlacedObject**)((u8*)o + 0x320);
        } while (o != 0);
        return;
    } else {
        if (self->parent != 0) {
            Camera* cam = g_camera;
            f32 r = self->f80 * cam->fB0;
            s32 far = 1;
            if (!(r * r < Vu0::ToFloat(Vu0::Dot(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(cam->f40)),
                                                 Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(cam->f40)))))) {
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
    switch (self->f2D4) {
    case 3: {
        f32 acc = self->f33C + self->f328 * self->f334 * dt;
        n = (s32)acc;
        self->f33C = acc - (f32)n;
        if (1.0f < (f32)n) {
            if (self->f2D8 >= 0) {
                if (!(n < self->f2D8)) {
                    n = self->f2D8;
                }
                self->f2D8 -= n;
            }
            if (self->continuous != 0) {
                SetEffectSpawnerActiveForever(self);
                self->f328 = RandomFloatInRange(self->f2DC, self->f2E0) * 60.0f;
            } else if (RandomFloatInRange(0.0f, 1.0f) <= self->chance) {
                SetEffectSpawnerActiveFor(self, RandomFloatInRange(self->active.lo, self->active.hi));
                self->f328 = RandomFloatInRange(self->f2DC, self->f2E0) * 60.0f;
            }
        }
        break;
    }
    case 2:
        n = (s32)self->f328;
        if (self->f2D8 >= 0) {
            if (!(n < self->f2D8)) {
                n = self->f2D8;
            }
            self->f2D8 -= n;
        }
        if (self->continuous != 0) {
            SetEffectSpawnerActiveForever(self);
        } else if (RandomFloatInRange(0.0f, 1.0f) <= self->chance) {
            SetEffectSpawnerActiveFor(self, RandomFloatInRange(self->active.lo, self->active.hi));
        }
        self->f328 = RandomFloatInRange(self->f2DC, self->f2E0);
        break;
    case 0: {
        f32 acc = self->f33C + self->f328 * self->f334 * dt;
        n = (s32)acc;
        self->f33C = acc - (f32)n;
        if (n == 0) {
            goto timer;
        }
        if (self->f2D8 >= 0) {
            if (!(n < self->f2D8)) {
                n = self->f2D8;
            }
            self->f2D8 -= n;
        }
        break;
    }
    case 1: {
        n = (s32)(self->f2F4 * self->f334);
        s32 have;
        BaseObject* held;
        if (self->rec->f120 == 0) {
            held = self->held348;
            have = held != 0 ? *(s32*)((u8*)held + 0x620) : 0;
        } else {
            held = self->held344;
            have = held != 0 ? CountListItems((List01*)((u8*)held + 0x558)) : 0;
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
    if (self->f330 <= g_gameClock[1]) {
        self->f328 = RandomFloatInRange(self->f2DC, self->f2E0);
        self->f330 = g_gameClock[1] + self->f32C;
    }
    WrapSpawnerParticlesIntoBox(self);
}

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
        self->f88 = p->f88;
    }
}

void SetEffectSpawnerActiveFor(EffectSpawner* self, f32 f)
{
    self->f340 = g_gameTime + f;
}

void SetEffectSpawnerActiveForever(EffectSpawner* self)
{
    self->f340 = 3.4028234663852886e+38f;
}

void SetEffectSpawnerInactive(EffectSpawner* self)
{
    self->f340 = -1.0f;
}

s32 IsEffectSpawnerActive(EffectSpawner* self)
{
    if (g_gameTime < self->f340) {
        return 1;
    }
    if (self->f2D4 < 2) {
        if (self->f2D4 >= 0) {
            if (self->f2D8 == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void SetEffectSpawnerDisabled(EffectSpawner* self, s32 a1)
{
    if (a1 != 0) {
        SetEffectSpawnerInactive(self);
    } else {
        SetEffectSpawnerActiveForever(self);
    }
}

void GetEffectSpawnerInactive(EffectSpawner* self, s32* out)
{
    *out = IsEffectSpawnerActive(self) == 0;
}

void GetEffectSpawnerActive(void* self,s32* out)
{
    *out=IsEffectSpawnerActive((EffectSpawner*)self);
}

void RandomizeEffectSpawnerDelay(u8* self)
{
    *(s32*)(self+0x34C)=0;
    if (*(void**)(self+0x348)) ApplyLookSourceToListedObject((WorldListedObject*)(*(void**)(self+0x348)),(LookSource*)(*(void**)(self+0x2D0)));
    if (*(void**)(self+0x344)) CopyEffectOwnerMargin((EffectOwner*)(*(void**)(self+0x344)),(Rec50*)(*(void**)(self+0x2D0)));
    f32 value;
    if (*(s32*)(self+0x2D4)==3) value=RandomFloatInRange(*(f32*)(self+0x2DC),*(f32*)(self+0x2E0))*60.0f;
    else value=RandomFloatInRange(*(f32*)(self+0x2DC),*(f32*)(self+0x2E0));
    *(f32*)(self+0x328)=value;
}

void SetEffectSpawnerLimit(EffectSpawner* self, s32 a1)
{
    if (self->f2D4 == -1) {
        self->f2D8 = a1;
    } else if (self->f2D4 == 0) {
        if (a1 == 0) {
            SetEffectSpawnerActiveForever();
        } else if (a1 == -1) {
            SetEffectSpawnerInactive(self);
        } else {
            self->f2D8 = a1;
        }
    }
    self->f34C = 1;
}

void SetEffectSpawnerContinuous(EffectSpawner* a0, s32 a1)
{
    a0->continuous = a1;
    a0->f34C = 1;
}

void SetSpawnRecordKind(u8* self,s32 kind)
{
    *(s32*)(self+0x1B0)=kind;
    FillMemory(self+0x1F0,0,12);
    if (kind!=24) {
        if (kind==27) {
            *(s32*)(self+0x1F0)=-1;
            *(f32*)(self+0x1F4)=10.0f;
        }
    } else {
        *(f32*)(self+0x1F0)=25.0f;
        *(f32*)(self+0x1F4)=0.8f;
        *(f32*)(self+0x1F8)=0.8f;
    }
}

void SetEffectSpawnerKind(void* a0, s32 a1)
{
    void* r = GetOwnSpawnRecord((EffectSpawner*)a0, 1);
    SetSpawnRecordKind((u8*)r, a1);
}

void SetOwnedSpawnRecordKind(void* a0, s32 a1)
{
    void* r = GetOwnedSpawnRecord(a0, 1);
    SetSpawnRecordKind((u8*)r, a1);
}

// The splash of an object on a surface: its sound by distance, the effect, and from 500 on a
// burst through SpawnEffectsAt. The burst's two records are brace initialisers
// (docs/toolchain/large-functions.md, "A brace initialiser's union member is a CLOBBER"): the
// tail's two float groups each start with a union's member, and the block is the spawn block
// (Blk05), built in a temporary and copied because two of its vectors are copied from memory;
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
extern s32 D_00262050[74];
s32 RandomIntInRange(s32 a, s32 b);
void SpawnEffectsAt(Quad16* self, Quad16* a1, s32 a2, SpawnTail* a3, SpawnBlock* a4, s32 a5, s32 a6);

// Both callers (gauge_collider.cpp and collider.cpp) declare it with these parameters and are
// retail's code with them; a float takes its register wherever it is declared.
void SpawnSurfaceContactEffects(BaseObject* self, u8* cfg, Quad16* p, f32 chance, Quad16* at, f32 minScale, f32 size)
{
    if (AT(s32, cfg, 0x580) == 0) {
        return;
    }
    f32 dist = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(*p), Vu0::Q(AT(Quad16, self, 0x150)))));
    f32 zero = 0.0f;
    s32 go = RandomFloatInRange(zero, 3.0f) < chance;
    u8* snd = 0;
    if (self->desc->flags & 8) {
        snd = (u8*)self;
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
        if (snd != 0 && AT(s32, cfg, 0x584) != 0) {
            f32 vol = k * 0.9f + 0.1f;
            void* rec = AT(void*, snd, 0x574);
            if (rec != 0) {
                AT(f32, rec, 0x14) = vol;
            } else {
                StartSoundEffect(D_00262050[RandomIntInRange(0, 3)], (PlayingSound**)(snd + 0x574), (BaseObject*)snd, 0, 10.0f, 1.0f, vol,
                                 0.0f, 0.0f, 0, 0);
            }
        }
        if (!go) {
            f32 period = 1.0f - k * (1.0f - minScale);
            if (snd != 0) {
                go = period < g_gameTime - AT(f32, snd, 0x570);
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
            AT(f32, snd, 0x570) = g_gameTime;
        }
        if (AT(s32, cfg, 0x588) != 0 && 500.0f < dist) {
            SplashTail tail = { 2, -1, 0, 0, 1.0f, 0.0f, 0, 0, 8.0f, 12.0f, 0, 0, cfg };
            Blk05 block = {
                { dist * 0.5f, dist * 0.75f, 1.0f }, AT(Vec02, self->world, 0x1EE0), { 0.0f, 0.0f, 0.0f },
                *(Quad16*)&g_unitZVector, 0.0f, 0.392699093f, 1.04719758f, 0,
                { 1.0f, 5.0f, 0.0f }, { { 0, 0, 0, 0 } }, { 1.0f, 0.0f, -1.0f }
            };
            Vec02 pos = *(Vec02*)at;
            pos.z += 30.0f;
            SpawnEffectsAt((Quad16*)&pos, (Quad16*)&g_unitZVector, RandomIntInRange(4, 6), (SpawnTail*)&tail, (SpawnBlock*)&block, 0, 0);
        }
    } else if (snd != 0) {
        StopSoundRecord((PlayingSound*)(AT(void*, snd, 0x574)), 0);
    }
}

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
typedef void (*CurveEvalFn)(SpawnCurve* self, f32 t, Vec02* pos, Vec02* dir);
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
    f32 f08;                // 0x08
    f32 f0C;                // 0x0C
    f32 r0;                 // 0x10
    f32 r1;                 // 0x14
    PlacedObject* from;     // 0x18
    PlacedObject* to;       // 0x1C
    f32 f20;                // 0x20
    f32 len;                // 0x24
};

struct SpawnTriangle {
    s32 v[3];               // 0x00
    f32 area;               // 0x0C
};

struct SpawnMesh {
    u8 pad00[4];
    Vec02* verts;           // 0x04
    s32 count;              // 0x08
    SpawnTriangle* tris;    // 0x0C
    Vec02* normals;         // 0x10
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
        Vec02 point;        // 0x10
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
    Vec02 dir;              // 0x50
    SpawnRange jitter;      // 0x60
    u8 pad68[4];
    void* anchor;           // 0x6C
};

s32 SolveQuadratic(f32 a, f32 b, f32 c, f32* roots);
void BuildPerpendicularPair(Vec02* in, Vec02* out, const Vec02* a, const Vec02* b);
void ComputePolarOffset(Vec3* out, f32 angle, f32 scale, f32 z);
void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);

static inline f32 RandomInRange(const SpawnRange& r)
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
void ChooseSpawnPosition(SpawnShape* shape, s32 index, s32 count, Vec02* pos, Vec02* axis)
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
            Vec02 tangent;
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
        Vec02 offset;
        Mat02 frame;
        Vec02 at;
        Vec02 side;
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
        if (seg->f0C != seg->f08) {
            SolveQuadratic((seg->f0C - seg->f08) * 0.5f / seg->f20, seg->f08, -d, roots);
        } else {
            roots[0] = d / seg->f08;
        }
        f32 u = roots[0] / seg->f20;
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
        Vec02 p[3];
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
            Vec02 n[3];
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
            Vu0::Set(*axis, Vu0::RotateTransposed(*(Mat02*)((u8*)shape->anchor + 0x110),
                                                  Vu0::Rotate(*(Mat02*)((u8*)g_camera + 0x80), Vu0::Vec::Of(shape->dir))).q);
        } else {
            Vu0::Set(*axis, Vu0::Rotate(*(Mat02*)((u8*)g_camera + 0x80), Vu0::Vec::Of(shape->dir)).q);
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

void TransformDirectionBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
void ComputeObjectMotionInFrame(PlacedObject* self, PlacedObject* top, Vec02* origin, Vec02* vel, Vec02* velSum, Vec02* spin, Vec02* spinSum);

void ConvertSpawnToAnchorSpace(AnchoredSpawn* self, Vec02* pos, Vec02* dir)
{
    Vec02 motion;
    if (self->anchor) {
        TransformPointBetweenFrames(self->anchor, 0, pos, pos);
        if (self->mode != 3) {
            TransformDirectionBetweenFrames(self->anchor, 0, dir, dir);
            if (self->mode != 2) {
                Vec02* ref = pos;
                if (self->mode != 1)
                    ref = &self->anchor->v140;
                ComputeObjectMotionInFrame(self->anchor, 0, ref, &motion, 0, 0, 0);
                Vu0::Q(*dir) = Vu0::Add(Vu0::Q(*dir), Vu0::Q(motion));
            }
        }
    }
}

void InitSpawnRing(s32 n, SpawnSpan* span, s32 k, SpawnRing* out) { if (n > 0) { out->count = n < k ? n : k; } else { out->count = k; } s32 steps = k - 1; steps += out->count; steps = steps / out->count; f32 w = WrapAngle(span->hi - span->lo); f32 rate = 6.2831855f / (f32)out->count; f32 step = w / (f32)steps; out->rate = rate; out->step = step; out->phase = span->lo + step * 0.5f; out->out10 = RandomFloatInRange(0.0f, 6.2831855f); }

void ComputeDirectionFromAngles(Vec3* out, f32 first, f32 second, f32 scale);
void BuildPerpendicularPair(Vec02* in, Vec02* out, const Vec02* a, const Vec02* b);

void ComputeSpawnRingDirection(SpawnRing* ring, SpawnSpan* range, Vec02* axis, s32 index, Vec02* out, f32 jitter, f32 flatten)
{
    Vec02 dir;
    Mat02 basis;
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

void ChooseSpawnDirectionAndLifetime(SpawnPlacement* self, SpawnRing* ring, s32 unused, s32 index, Vec02* pos, Vec02* axis,
                   Vec02* dir, f32* start, f32* end)
{
    Vec02 k;
    ComputeSpawnRingDirection(ring, &self->range, axis, index, dir, self->jitter, self->flatten);
    *start = g_gameClock[1] - RandomFloatInRange(self->lo60, self->hi64);
    *end = *start + self->life;
    f32 along = RandomFloatInRange(self->lo58, self->hi5C);
    if (along != 0.0f) {
        Vu0::Q(k) = Vu0::FromFloat(along);
        Vu0::Q(*pos) = Vu0::MulAddX(Vu0::Q(*pos), Vu0::Q(*dir), Vu0::Q(k));
    }
}

void SpawnRecordEffects(Rec50* self, EffectOwnerSlot* h, s32 n, Quad16* pos, Quad16* q2, f32* v5, f32* v6)
{
    u8* s7 = AT(u8*, self, 0x7C);
    EffectOwner* node = 0;
    u8* c = (u8*)self + 0x120;
    s32 i;
    if (h) {
        if (h->f4) node = (EffectOwner*)*h->f4;
    }
    if (!node) {
        node = AcquireEffectOwner((World*)g_currentWorld, AT(s32, c, 0xC4));
        if (!node) return;
        if (h) {
            if (h->f4) *h->f4 = (s32)node;
        }
        CopyEffectOwnerMargin(node, self);
        if (h) {
            if (h->f8) {
                typedef void (*F)(EffectOwner*, s32);
                (*(F*)(AT(u8*, node, 0) + 0x6C))(node, h->f8);
            }
        }
    }
    if (node) {
    for (i = 0; i < n; i++) {
        Effect* it = CreateEffect(AT(s32, c, 0x90), (EffectOwner*)node);
        if (!it) break;
        Quad16* s1 = pos + i;
        u8* cls = AT(u8*, it, 0);
        f32 f = RandomFloatInRange(AT(f32, c, 0xB0), AT(f32, c, 0xB4));
        typedef void (*F0)(Effect*, Quad16*, s32, f32);
        (*(F0*)cls)(it, s1, AT(s32, c, 0xC0), f);
        f32 f1 = AT(f32, c, 0xA4);
        if (f1 != 0.0f || AT(f32, c, 0xA8) != 0.0f) {
            AT(f32, it, 0x34) = f1;
            AT(f32, it, 0x38) = AT(f32, c, 0xA8);
        }
        AT(Quad16, it, 0xA0) = q2[i];
        AT(f32, it, 0x18) = v5[i];
        AT(f32, it, 0x1C) = v6[i] - v5[i];
        AT(Quad16, it, 0x40) = AT(Quad16, self, 0x110);
        FillLookDirectionBlock((Effect*)((u8*)it + 0xB0), self);
        if (AT(s32, c, 0xB8)) AT(s32, it, 0x20) = AT(s32, c, 0xB8);
        if (s7) {
            AT(Quad16, it, 0x50) = AT(Quad16, s7, 0x110);
            AT(Quad16, it, 0x60) = AT(Quad16, s7, 0x120);
            AT(Quad16, it, 0x70) = AT(Quad16, s7, 0x130);
        }
        if (AT(s32, c, 0x94) != -1) {
            EffectOwner* o = (EffectOwner*)CreateEffect(AT(s32, c, 0x94), 0);
            if (!o) break;
            typedef void (*F1)(f32, EffectOwner*, void*, s32);
            F1 fn = *(F1*)(*(u8**)o);
            fn(AT(f32, it, 0x30) * 0.5f, o, (u8*)it + 0x80, 0);
            SetTrailSegmentAnchor(o, 1, it);
        }
        {
            u8* cl = AT(u8*, it, 0);
            VFn* p = (VFn*)(cl + 4);
            if (*p) ((void (*)(Effect*, Rec50*))*p)(it, self);
        }
    }
    if (IsListEmpty((List01*)((u8*)node + 0x558))) {
        typedef void (*F2)(EffectOwner*);
        (*(F2*)(AT(u8*, node, 0) + 0x1C))(node);
    }
    }
}

struct WorldListedObject;
struct OwnedRecord;
WorldListedObject* ResetFirstListedObject(World* self);
OwnedRecord* AcquireOwnedRecord(WorldListedObject* o);
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
void EmitParticleChunk(Rec50* self, EffectOwnerSlot* h, s32 n, Quad16* pos, Quad16* vel, f32* size, f32* spin, Quad16* e, Quad16* g)
{
    EffectOwner* set = 0;
    s32 i;
    ParticleChunk* chunk;
    if (h) {
        if (h->f0) set = (EffectOwner*)*h->f0;
    }
    if (!set) {
        World* world = g_currentWorld;
        if (AT(s32, world, 0x1B48) == 0) return;
        if (AT(s32, self, 0x130) == 2) {
            if (AT(s32, world, 0x1B54) == 0) return;
        }
        set = (EffectOwner*)ResetFirstListedObject(world);
        if (!set) return;
        if (h) {
            if (h->f0) *h->f0 = (s32)set;
        }
        ApplyLookSourceToListedObject((WorldListedObject*)set, (LookSource*)self);
        if (h) {
            if (h->f8) {
                typedef void (*F)(EffectOwner*, s32);
                (*(F*)(AT(u8*, set, 0) + 0x6C))(set, h->f8);
            }
        }
        if (!set) return;
    }
    chunk = AT(ParticleChunk*, set, 0x624);
    i = 0;
    while (i < n && (chunk != 0 || (chunk = (ParticleChunk*)AcquireOwnedRecord((WorldListedObject*)set)) != 0)) {
        u32 k = chunk->count;
        ParticleState* last = &chunk->prev;
        while (k < 0x2C && i < n) {
            Quad16* p = &chunk->cur.pos[k];
            Quad16* v = &chunk->cur.vel[k];
            Quad16* rec = &chunk->cur.rec[k];
            *p = pos[i];
            AT(f32, p, 0xC) = size[i];
            *v = vel[i];
            AT(f32, v, 0xC) = spin[i];
            FillMemory(rec, 0, 0x10);
            s32 r = RandomIntInRange(0, AT(s32, set, 0x590) - 1);
            AT(s32, rec, 0) = r;
            if (AT(s32, set, 0x614) != 0) AT(s32, rec, 0) = r & 0xFFFFFFFE;
            if (AT(s32, self, 0x178) != 0) AT(s32, rec, 4) = RandomIntInRange(0, AT(s32, set, 0x384) - 1);
            if (AT(s32, set, 0x618) == 2) {
                f32 f = RandomInRange(AT(SpawnRange, self, 0x19C));
                AT(f32, rec, 8) = f;
                if (AT(s32, self, 0x198) == 0) {
                    if (0.0f < Vu0::ToFloat(Vu0::Dot(Vu0::Q(AT(Quad16, g_camera, 0x90)), Vu0::Q(*v)))) AT(f32, rec, 8) = -f;
                }
                if (AT(s32, self, 0x1A4) != 0) AT(f32, rec, 0xC) = RandomFloatInRange(-3.14159274f, 3.14159274f);
            }
            if (AT(s32, set, 0x320) == 2) {
                ParticleExtra* x = &chunk->extra[k];
                x->a = e[i];
                x->b = g[i];
            }
            last->pos[k] = *p;
            last->vel[k] = *v;
            last->rec[k] = *rec;
            chunk->count = chunk->count + 1;
            AT(s32, set, 0x620) = AT(s32, set, 0x620) + 1;
            i++;
            k++;
        }
        chunk = chunk->next;
    }
}

// The frame of the object a spawn record follows (at 0x78): its position, the rotation, and the
// velocity and spin it moves with.
struct SpawnFrame {
    Vec02 pos;              // 0x00
    Mat02 rot;              // 0x10
    Vec02 vel;              // 0x40
    Vec02 spin;             // 0x50
    SpawnFrame() { FillMemory(this, 0, sizeof(*this)); }
};

// Makes the count points of a spawn record, their directions and times, in the four arrays out
// holds (positions, directions, starts, ends), moved to the followed object's frame.
void GenerateSpawnArrays(s32 n, void* b, s32* out)
{
    u8* rec = (u8*)b;
    SpawnRing ring;
    Vec02 axis;
    out[0] = (s32)AllocateBackMemory(n * 16);
    out[1] = (s32)AllocateBackMemory(n * 16);
    out[2] = (s32)AllocateBackMemory(n * 4);
    out[3] = (s32)AllocateBackMemory(n * 4);
    InitSpawnRing(*(s32*)(rec + 0xEC), (SpawnSpan*)(rec + 0xE4), n, &ring);
    for (s32 i = 0; i < n; i++) {
        ChooseSpawnPosition((SpawnShape*)(rec + 0x10), i, n, (Vec02*)out[0] + i, &axis);
        ChooseSpawnDirectionAndLifetime((SpawnPlacement*)(rec + 0xA0), &ring, (s32)(rec + 0x10), i, (Vec02*)out[0] + i, &axis,
                      (Vec02*)out[1] + i, (f32*)out[2] + i, (f32*)out[3] + i);
        SpawnFrame* o = *(SpawnFrame**)(rec + 0x78);
        if (o != 0) {
            Vec02* pos = (Vec02*)(i * 16 + out[0]);
            Vu0::Q(*pos) = Vu0::Add(Vu0::Rotate(o->rot, Vu0::Q(*pos)), Vu0::Q(o->pos));
            Vec02* vel = (Vec02*)(i * 16 + out[1]);
            u128 rel = Vu0::Sub(Vu0::Q(*(Vec02*)(i * 16 + out[0])), Vu0::Q(o->pos));
            u128 spun = Vu0::Cross(Vu0::Q(o->spin), rel);
            u128 moved = Vu0::Add(Vu0::Rotate(o->rot, Vu0::Q(*vel)), Vu0::Q(o->vel));
            Vu0::Q(*vel) = Vu0::Add(moved, spun);
        }
        if (out[4] != 0) {
            ConvertSpawnToAnchorSpace((AnchoredSpawn*)(rec + 0x10), (Vec02*)out[0] + i, (Vec02*)out[1] + i);
        }
    }
}

s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 eps);
void ComputeChainedWorldFrame(void* a, void* frame, void* out);
// Left in this order: retail's call here evaluates the time before the pointers.
void ComputeObjectFrameAtTime(PlacedObject* self, PlacedObject* top, f32 t, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin);

void GenerateSpawnSetupPair(s32 n, void* owner, SpawnSetup* first, SpawnSetup* second)
{
    SpawnFrame frame;
    Vec02 P;
    Vec02 V;
    Vec02 W;
    Mat02 M;
    Vec02 tmp;
    Rec50* r = AT(Rec50*, owner, 0x18C);
    Rec50* sub = AT(Rec50*, r, 0x90);
    void* saved = sub->target;
    if (AT(s32, r, 0x94) == -1) {
        sub->target = AT(void*, r, 0x18);
    }
    if (AT(Rec50*, r, 0x90)->target == AT(void*, r, 0x18)) {
        ComputeChainedWorldFrame(r, &frame.pos, &frame.rot);
        AT(SpawnFrame*, AT(Rec50*, r, 0x90), 0x78) = &frame;
    }
    second->flag = 0;
    GenerateSpawnArrays(n, AT(Rec50*, r, 0x90), second->out);
    AT(SpawnFrame*, AT(Rec50*, r, 0x90), 0x78) = 0;
    f32 last = 3.40282347e+38f;
    for (s32 i = 0; i < n; i++) {
        if (AT(Rec50*, r, 0x90)->target != 0) {
            f32 t = ((f32*)first->out[3])[i] - g_gameClock[1];
            if (!AreFloatsNearlyEqual(t, last, 0.0001f)) {
                last = t;
                ComputeObjectFrameAtTime((PlacedObject*)(AT(Rec50*, r, 0x90)->target), 0, last, &P, &M, &V, &W);
            }
            Vec02* p = (Vec02*)(i * 16 + second->out[0]);
            Vu0::Set(tmp, Vu0::Rotate(M, Vu0::Q(*p)));
            Vu0::Q(*p) = Vu0::Add(Vu0::Q(P), *(u128*)&tmp);
            s32 kind = AT(s32, AT(Rec50*, r, 0x90), 0x80);
            if (kind != 3) {
                Vec02* v = (Vec02*)(i * 16 + second->out[1]);
                Vu0::Q(*v) = Vu0::Rotate(M, Vu0::Q(*v));
                if (kind != 2) {
                    u128 moved = Vu0::Add(Vu0::Q(*(Vec02*)(i * 16 + second->out[1])), Vu0::Q(V));
                    u128 spin = Vu0::Q(W);
                    Vu0::Q(*(Vec02*)(i * 16 + second->out[1])) = Vu0::Add(moved,
                        Vu0::Cross(spin, Vu0::Q(kind == 1 ? *(Vec02*)(second->out[0] + i * 16) : tmp)));
                }
            }
        }
        Vu0::Vec neg = Vu0::Vec::FromFloat(-1.0f);
        u128 r = Vu0::MulX(Vu0::Q(*(Vec02*)(i * 16 + second->out[1])), neg.q);
        *(Vu0::Vec*)&tmp = neg;
        Vu0::Q(*(Vec02*)(i * 16 + second->out[1])) = r;
    }
    AT(Rec50*, r, 0x90)->target = saved;
}

void SpawnEffectsFromRecord(s32 a, Rec50* b, void* c)
{
    SpawnSetup f;
    if (a == 0) {
        return;
    }
    PushBackMemoryMark();
    f.flag = 1;
    GenerateSpawnArrays(a, b, f.out);
    if (b->f120 == 1) {
        SpawnRecordEffects(b, c, a, f.out[0], f.out[1], f.out[2], f.out[3]);
    } else {
        if (b->f130 == 2) {
            GenerateSpawnSetupPair(a, b, f.out, f.pair);
        } else {
            f.pair[0] = 0;
            f.pair[1] = 0;
        }
        EmitParticleChunk(b, c, a, f.out[0], f.out[1], f.out[2], f.out[3], f.pair[0], f.pair[1]);
    }
    PopBackMemoryMark();
}

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
    SpawnEffectsFromRecord(a2, (Rec50*)&f, &p);
}

LINKER_REMNANT(func_00157FF0);

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
            switch (e->f90->f1B0) {
            case 4:
                frame.kind = 0x14;
                frame.f30 = x;
                break;
            case 2:
                frame.kind = 0x24;
                frame.f38 = obj;
                break;
            }
        }
        e->vtbl[31](e, &frame);
    }
}

void SpawnBriefEffectAt(void* a0, BriefEffectSource* a1, f32 f)
{
    Effect* o = (Effect*)CreateEffect(4, 0);
    if (o != 0) {
        ((EffectStartFn)o->vt->m00)(o, a0, 0, f);
        o->life = 0.75f;
        if (a1->f278 != 0) {
            o->p114 = (void*)a1->f278->fC;
        }
    }
}

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
    f32 f08;                // 0x08
    f32 f0C;                // 0x0C
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
    s32 f188;               // 0x188
    MemberTargetObject* f18C;   // 0x18C
};

struct SpawnTargetOwner { u8 pad00[0x14]; void* world; };

void ResolveSpawnRecordTargets(SpawnTargetRecord* rec, SpawnTargetOwner* owner)
{
    if (rec->f120 == 0 && rec->f188 != -1) {
        rec->f18C = (MemberTargetObject*)FindFirstObjectById((World*)owner->world, 0x104, rec->f188, owner);
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
            link->weight = (link->f08 + link->f0C) * (d * 0.5f);
            total += link->weight;
        }
        rec->total = total;
    }
}

ASM_FUNC(func_001583E8);

// The spin record TurnMatrixBySpin reads (MoveEffect's at +0x100).
struct SpinRecord_158480 {
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
extern const Mat4A D_00248400;
void BuildAxisAngleMatrix(const Vec02* v, Mat02* out, f32 angle);
s32 ScaleMatrix(Mat4A* out, Mat4A* in, u128 scale);
void AddMatrices(f32* a, f32* b, f32* out);

void TurnMatrixBySpin(SpinRecord_158480* spin, f32 dt, f32* out)
{
    Mat4A place = D_00248400;
    Mat4A turn;
    place.m[2][2] = place.m[1][1] = place.m[0][0] = spin->scale;
    place.m[3][0] = spin->tx;
    place.m[3][1] = spin->ty;
    place.m[3][2] = spin->tz;
    turn = D_00248400;
    if (spin->rate != 0.0f) {
        Quad16 axis;
        if (spin->mode == 1 && spin->frame != 0) {
            TransformDirectionBetweenFrames((PlacedObject*)spin->frame, 0, (Vec02*)&spin->axis, (Vec02*)&axis);
        } else {
            axis = spin->axis;
        }
        BuildAxisAngleMatrix((const Vec02*)&axis, (Mat02*)&turn, spin->rate * dt);
    }
    Mat4A term;
    Mat4A scaled;
    Mat4A* result = &scaled;
    Mat4A product = MultiplyMatrices(turn, place);
    ScaleMatrix(result, &product, Vu0::ScalarInGpr(dt));
    term = scaled;
    AddMatrices((f32*)&turn, (f32*)&term, out);
}

void StartMemberObject(MemberObject* self)
{
    StartObject(self);
    self->desc->m03(self);
}

ASM_FUNC(func_00158630);

void SendEmptyMessage(MemberObject* a0)
{
    EmptyMessage b;
    FillMemory(&b, 0, 0x50);
    a0->desc->m1B(a0, &b);
}

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
                        *(void**)((u8*)dst + (c << 2)) = o;
                        self->count = c + 1;
                        o->group = self;
                    }
                }
            }
        }
    }
}

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

void BroadcastMessageToMembers(MemberGroup* self, void* message)
{
    for (s32 i = 0; i < self->count; i++) {
        MemberObject* it = self->members[i];
        it->desc->m1B(it, message);
    }
}

void InitRecordMember(RecordMember* self)
{
    InitTransformObject(self);
    self->id94 = -1;
    self->id98 = -1;
}

void LoadRecordMember(RecordMember* self, void* stream)
{
    Rec79* p = (Rec79*)AllocateZeroedFrontMemory(0x200);
    self->rec = p;
    InitSpawnRecord(p);
    ReadTransformObject(self, stream);
    s32 idx = ReadBufferedS8((BufferedStream*)stream);
    if (idx != -1) {
        Rec79* n = GetOwnedSpawnRecord(self, 1);
        n->curve20 = CreatePathCurve(idx);
        if (n->curve20->vt->m00 != 0) {
            n->curve20->vt->m00(n->curve20, stream);
        }
    }
    Rec79* q = self->rec;
    if (q->kind == 4) {
        ReadSpawnMesh(&q->curve20, stream);
    }
    s32 t = ReadBufferedU16((BufferedStream*)stream);
    if (t != 0) {
        Rec79* m = GetOwnedSpawnRecord(self, 1);
        ReadCappedWordList((CappedWordList*)((u8*)m + 0x130), t, self, stream);
    }
}

void CopyRecordMember(RecordMember* self, RecordMember* src)
{
    CopyObjectData(self, src);
    self->rec->uses += 1;
}

void ResolveRecordMemberTargets(RecordMember* self)
{
    Rec79* r;
    Rec79* c;

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
            r->value20 = q->f34;
            r->target = q->f18;
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

void AddRecordMemberRangeEntry(RecordMember* self, s32 a, s32 b, f32 x, f32 y, f32 z, f32 w)
{
    u8* p = (u8*)GetOwnedSpawnRecord(self, 1);
    AddRangeEntry((RangeEmitter*)(p+16),a,b,x,y,z,w,self);
}

Rec79* GetOwnedSpawnRecord(RecordMember* self, s32 own)
{
    if (own == 1) {
        self->rec = (Rec79*)CloneSharedSpawnRecord(self->rec);
    }
    return self->rec;
}

void InitHoldingMember(HoldingMember* self)
{
    InitRecordMember(self);
    self->idAC = -1;
    self->idB0 = -1;
    self->idB4 = -1;
}

void ResolveHoldingMemberTargets(HoldingMember* self)
{
    Rec79* s;
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

void SendMessageAfterDelay(HoldingMember* self, void* message)
{
    DelayedMessage* r;
    f32* k;
    s32 done = 0;

    if (0.0f < self->delay) {
        r = (DelayedMessage*)PopFreeSlot(&self->world->pool1BD0);
        if (r != 0) {
            r->owner = self;
            r->body = *(DelayedMessageBody*)message;
            done = 1;
            k = (f32*)g_gameClock;
            r->due = k[1] + self->delay;
            ClearListLinks((ListLink*)((u8*)r + 0x64));
            AppendToList(&self->world->list1BDC, r);
        }
    }
    if (done == 0) {
        HandleSpawnMessage(self, message);
    }
}

s32 GetOrCreateSoundParams(void* self)
{
    HoldingMember* o = (HoldingMember*)self;
    if (o->fA0 == 0) {
        InitSoundParams((SoundRecord**)&o->fA0);
    }
    return o->fA0;
}

// The 0x200-byte spawn record (Rec79) as func_001590A0 changes its copy: the copy is written
// field by field, so each store is a structure member's and the message's flags word is read
// again after it (docs/TOOLCHAIN.md, "A store to a stack struct's member").
struct __attribute__((aligned(16))) SpawnRecordView {
    u8 pad00[0x10];
    s32 kind;               // 0x10: where the sound plays (the switch below)
    u8 pad14[0x20 - 0x14];
    union {
        Quad16 q20;         // 0x20: a point (kind 0), the first end (kind 1)
        Vec02 v20;
        u8* p20;            // 0x20: an object whose point at +0x18 is used (kind 2)
    };
    Vec02 v30;              // 0x30: the second end (kind 1)
    Vec02 v40;              // 0x40: kind 4's point
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
Quadword128 ScaleQuadword(Quadword128 a, Quadword128 b);
void* StoreQuadword(u128* out, u128 v);
struct ValueRange;
f32 ClampToRange(ValueRange* span, f32 x);
void ComputeChainedWorldFrame(void* a, void* frame, void* out);
void TransformPointBetweenFrames(PlacedObject* from, PlacedObject* to, Vec02* in, Vec02* out);
extern f32 D_00262178[2];
extern const Vec02 D_00248D30;

void HandleSpawnMessage(void* self, void* body)
{
    SpawnMessage* m = (SpawnMessage*)body;
    SpawnRecordView rec;
    ChainFrame frame;
    void* chain[3];
    Vec02 v;
    Vec02 half;
    Vec02 qa;
    Vec02 qb;
    rec = *AT(SpawnRecordView*, self, 0x90);

    s32 count;
    if (m->flags & 0x80) {
        count = m->count;
    } else {
        count = (s32)RandomFloatInRange(AT(f32, self, 0xA4), AT(f32, self, 0xA8));
    }
    if (m->flags & 1) rec.target = m->target;
    if (m->flags & 2) rec.q60 = m->q10;
    if (m->flags & 4) {
        rec.kind = 0;
        rec.q20 = m->q20;
    } else if (m->flags & 0x40) {
        rec.frame = m->frame;
        rec.target = AT(s32, self, 0x18);
    } else {
        frame.Clear();
        ComputeChainedWorldFrame(self, &frame, (u8*)&frame + 0x10);
        rec.frame = &frame;
        if (!(m->flags & 1)) rec.target = AT(s32, self, 0x18);
    }
    if (m->flags & 8) {
        if (rec.f120 == 0) {
            f32 t = m->scale;
            f32 s;
            if (t == 0.0f) s = m->percent * 0.01f;
            else s = t;
            if (s < 1.0f) count = (s32)((f32)count * s);
            else count = (s32)((f32)count / s);
            s32 least = (s32)AT(f32, self, 0xA8) / 2;
            count = least < count ? count : least;
            f32 r = ClampToRange((ValueRange*)D_00262178, s);
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
    if (AT(s32, self, 0xBC) != 0) {
        chain[0] = (u8*)self + 0xC4;
        chain[1] = (u8*)self + 0xC0;
        chain[2] = self;
        cp = chain;
    } else {
        cp = 0;
    }
    SpawnEffectsFromRecord(count, (Rec50*)&rec, cp);
    if (AT(s32, self, 0xA0) != 0) {
        switch (rec.kind) {
        case 0:
            v = rec.v20;
            break;
        case 1:
            Vu0::Q(half) = Vu0::FromFloat(0.5f);
            Vu0::Q(v) = Vu0::MulXSum(Vu0::Q(rec.v20), Vu0::Q(half), Vu0::Q(rec.v30), Vu0::Q(half));
            break;
        case 2:
            v = *AT(Vec02*, rec.p20, 0x18);
            break;
        case 3:
            v = D_00248D30;
            break;
        case 4:
            v = rec.v40;
            break;
        }
        if (rec.frame != 0) {
            u8* fr = (u8*)rec.frame;
            Vu0::Q(v) = Vu0::Add(Vu0::Rotate(AT(Mat02, fr, 0x10), Vu0::Q(v)), Vu0::Q(AT(Vec02, fr, 0)));
        }
        TransformPointBetweenFrames((PlacedObject*)rec.target, 0, &v, &v);
        u8* snd = AT(u8*, self, 0xA0);
        StartSoundEffect(AT(s32, snd, 0), 0, 0, &v, AT(f32, snd, 4), AT(f32, snd, 8), AT(f32, snd, 0xC), AT(f32, snd, 0x10), 0.0f, 0, 0);
    }
}

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

void DispatchDelayedMessages(World* self)
{
    ListFrame it;
    BeginListWalk::Of(&it, &self->list1BDC);
    DelayedMessage* node;
    while ((node = NextInList<DelayedMessage>::Of(&it)) != 0) {
        if (!(g_gameClock[1] < node->due)) {
            HandleSpawnMessage(node->owner, &node->body);
            RemoveFromList(&self->list1BDC, node);
            PushFreeSlot(&self->pool1BD0, node);
        }
    }
    g_activeListFrames = it.prev;
}

LINKER_REMNANT(func_00159668);

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

WorldObjectNode* AddObjectNodeToWorld(PlacedObject* self)
{
    WorldObjectNode* node = (WorldObjectNode*)PopZeroedFreeSlot((Pool6C*)((u8*)g_currentWorld + 0x1C18));
    node->owner = self;
    if (self->f294 != 0) {
        AppendToList((List01*)((u8*)g_currentWorld + 0x1C30), node);
    } else {
        AppendToList((List01*)((u8*)g_currentWorld + 0x1C24), node);
    }
    return node;
}

void RemoveObjectNodeFromWorld(WorldObjectNode* node)
{
    if (node->owner->f294 != 0) {
        RemoveFromList((List01*)((u8*)g_currentWorld + 0x1C30), node);
    } else {
        RemoveFromList((List01*)((u8*)g_currentWorld + 0x1C24), node);
    }
    node->owner->f298 = 0;
    PushFreeSlot((Pool6C*)((u8*)g_currentWorld + 0x1C18), node);
}

void DrawScreenFill(u8* a0)
{
    ScreenFillPacket f;
    f.value = *(s32*)(a0 + 0x60);
    FillScreenColor(f.buf, (Rgba4*)&f.value, 0);
    PacketWriter* s = &g_vifPacketWriter;
    BeginDmaTag(s);
    WriteVifDirect(s, 0x2C, &f, 0);
    CloseDmaTag(s);
}

void UpdateColorFade(ColorFade* self)
{
    if (D_00275BC4 != 3) return;
    s32 g = D_00270458;
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
                u8* p = (u8*)g_currentWorld + 0x1CD8;
                self->running = 0;
                RemoveFromList((List01*)p, self);
                return;
            }
            a = self->holdColor; b = self->endColor;
            d = self->fadeOutTime;
        }
    }
    f32 r = t / d;
    for (s32 i = 0; i < 4; i++)
        out.c[i] = (s32)((1.0f - r) * ((u8*)&a)[i] + r * ((u8*)&b)[i]);
    FadeRequest q;
    q.f = -1.0f;

    q.fn = (void*)(void (*)(ColorFade*))DrawScreenFill;
    q.col = out;
    switch (self->mode) {
    case 0: q.mode = 1; break;
    case 1: q.mode = 0x10; break;
    }
    QueueDeferredRequest((DeferredRequest*)&q);
}

void StartColorFade(ColorFade* a0)
{
    if (a0->running == 0) {
        a0->running = 1;
        a0->startTime = g_gameTime;
        AppendToList((List01*)((u8*)g_currentWorld + 0x1CD8), a0);
    }
}

u8* GetHashedSlot(u8* base, s32 n)
{
    return base + (((n * 0x95675) & 0x1FF) * 12 + 0x84);
}

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
    const Desc01* desc;     // 0x00
    u8 pad04[4];
    s32 id;                 // 0x08
    HashedObject* nextHashed; // 0x0C
    u8 pad10[0x30 - 0x10];
    Alias01* alias;         // 0x30
    u8 pad34[0x2D0 - 0x34];
    GroupMemberLink* members; // 0x2D0
};

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

BaseObject* FindFirstObjectById(World* self,s32 flags,s32 kind,void* arg)
{
    BaseObject* out=0;
    GatherObjectsByMode(self,flags|0x200,kind,arg,1,&out);
    return out;
}

BaseObject* FindFirstObjectByIdMode4(World* self,s32 kind,void* arg)
{
    BaseObject* out=0;
    GatherObjectsByMode(self,0x204,kind,arg,1,&out);
    return out;
}

BaseObject* FindFirstObjectByIdMode1(World* self,s32 kind,void* arg)
{
    BaseObject* out=0;
    GatherObjectsByMode(self,0x201,kind,arg,1,&out);
    return out;
}

s32 IsClassOfKind(s32 index, s32 value)
{
    ClassKindNode* p = ((ClassKindNode**)D_00247448)[index];
    while (p != 0) {
        if (p->value != value) {
            p = p->next;
        } else {
            return 1;
        }
    }
    return 0;
}

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
            for (obj = (PlacedObject*)world->f1884[i]; obj != 0; obj = (PlacedObject*)obj->nextById) {
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

PlacedObject* FindFirstObjectByIdGathered(World* self,s32 flags,s32 kind,void* arg)
{
    PlacedObject* out=0;
    GatherObjectsById(self,flags|0x200,kind,arg,1,&out);
    return out;
}

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

void InitScalingVolume(ScalingVolume* self)
{
    InitPlacedObject(self);
    f32* v = self->v;
    self->f2F0 = 1.0f;
    self->f2EC = 1.0f;
    self->v[0] = 1.0f;
    v[1] = 0.2f;
    v[2] = 0.1f;
}

void LoadScalingVolume(ScalingVolume* self,void* other)
{
    LoadPlacedObject(self,other);
    ReadMeshTables(other,&self->out2D0,&self->out2D4,&self->out2D8,&self->out2DC);
}

void UpdateScalingVolume(ScalingVolume* self, f32 dt)
{
    UpdatePlacedObject(self, dt);
    self->f2EC = ApproachValueWithRamp((RampProfile*)self->v, 0, self->f2EC, self->f2F0, g_frameDt);
}

void DrawScalingVolume(ScalingVolume* self, void* arg1, void* arg2)
{
    ScaledDrawFrame f;
    BuildUniformScaleAboutPoint(0, &f.q0, self->f2EC);
    BuildPlacedObjectTransform(self, (Quad16*)arg2, (ScaledTransform*)f.m40);
    MultiplyMatrices(f.m90, f.m40, &f.q0);
    f.m40[0] = f.m90[0];
    f.m40[1] = f.m90[1];
    f.m40[2] = f.m90[2];
    f.m40[3] = f.m90[3];
    DrawPlacedObject(self, arg1, f.m40);
}

struct TreeNode03;
struct FacePoint;
s32 IsPointInsideFaceTree(TreeNode03* self, FacePoint* value);

s32 IsPointInsideObjectFaces(ScalingVolume* self, void* point)
{
    Vec02 local;
    Vec02 k;
    if (self->f2EC < 0.0001f)
        return 0;
    TransformPointBetweenFrames(0, self, (Vec02*)point, &local);
    Vu0::Q(k) = Vu0::FromFloat(1.0f / self->f2EC);
    Vu0::Q(local) = Vu0::MulX(Vu0::Q(local), Vu0::Q(k));
    return IsPointInsideFaceTree((TreeNode03*)self->out2DC, (FacePoint*)&local);
}

extern f32 D_002621F8[6];
extern f32 D_00262210[4];
extern f32 D_00262220[4];

// The file's .data, 0x261F70 to 0x262180, in retail's order. The two packet streams
// (globals.h), whose labels are shorter than PacketWriter, are included from the disassembly.
// The spawn record's table, copied whole by InitSpawnRecord (func_001549C8), whose two statics'
// guards (D_00261F70, D_00261F74) the compiler writes out with the function, ahead of it.
SpawnTable D_00261F80 = { {
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
s32 D_00262050[74] = { 82, 83, 84, 85, 0, 46, 0, 0, 0x41F00000, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F800000, 0, 0, 1, 0, 0, 0, 0, 0, 0xFFFFFFFF, 0, 0, 0x3F800000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50, 0, 0, 0x41A00000, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F800000, 0, 0, 1, 0, 0, 0, 0, 0, 0xFFFFFFFF, 0, 0, 0x3F800000, 0, 0, 0, 0, 0, 0, 0, 0 };
f32 D_00262178[2] = { 0.5f, 2.0f };
