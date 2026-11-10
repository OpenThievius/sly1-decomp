// SPDX-License-Identifier: AGPL-3.0-or-later
// 0x1549C8 to 0x15F678: the methods of classes 0x50, 0x77 to 0x7A, 0x60 and 0x40, the effect
// helpers between them, the font and text drawing (its GCC vtable D_0024A220) and the packet
// writers' frame code, ending with the static initialiser func_0015F618 and _GLOBAL_$I$
// func_0015F658. One file between two edges; it could be several.
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
#include "transform_object.h"
#include "object_group.h"
#include "cursor_animator.h"
#include "object_cycler.h"
#include "c60.h"
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


s32 TransformPointBetweenFrames(void* from, void* to, void* point, Vec02* out);

void SetEffectSpawnerActiveForever();
void SetEffectSpawnerInactive(EffectSpawner* self);

void* GetOwnSpawnRecord(void* a0, s32 a1);
void SetSpawnRecordKind(void* self, s32 a1);

void* GetOwnedSpawnRecord(void* a0, s32 a1);
void SetSpawnRecordKind(void* self, s32 a1);

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
void func_001579B0(void* a, void* b, s32* out);
void SpawnRecordEffects(void* b, void* c, void* a, s32 o0, s32 o1, s32 o2, s32 o3);
void func_00157B88(void* a, void* b, s32* out, s32* pair);
void func_001575D8(void* b, void* c, void* a, s32 o0, s32 o1, s32 o2, s32 o3, s32 p0, s32 p1);

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
void* ReadBufferedU8(void* src);
StreamWord ReadBufferedU32(void* src);

void* AllocateFrontMemory(s32 size);
void InitSpawnRecord(void* mem);
void LoadPlacedObject(void* self, s32 count);
s32 ReadBufferedS8(s32 count);
PathCurve* CreatePathCurve(s32 kind);
void func_00154C80(void* self, s32 count);
s32 ReadBufferedU16(s32 count);
void* GetOwnSpawnRecord(void* self, s32 flag);
void ReadCappedWordList(void* self, s32 count, void* unused, s32 src);

void CopyPlacedObject(void* self);

struct SpawnerLinkedObject { u8 pad00[0x18]; void* f18; u8 pad1C[0x18]; s32 f34; };

void PostLoadPlacedObject(EffectSpawner* self);
Rec50* GetOwnSpawnRecord(EffectSpawner* self, s32 mode);
void ResolveSpawnRecordTargets(Rec50* p, EffectSpawner* self);
SpawnerLinkedObject* FindFirstObjectById(void* a0, s32 a1, s32 a2, EffectSpawner* a3);
s32 IsObjectOfKind(SpawnerLinkedObject* p, s32 k);
void* AppendQueuedCall(void* a0, void (*cb)(void), EffectSpawner* a2, s32 a3, s32 a4);

void* CopyToFrontMemory(s32 size, void* owner);

extern f32 g_gameTime;


void SetEffectSpawnerActiveForever();


s32 IsEffectSpawnerActive(EffectSpawner* self);

void InitPlacedObject(void*);
void SetListLinkOffset(void*,s32);

void AddRangeEntry(void*,void*,void*,f32,f32,f32,f32,void*);

void func_0013A128(void*,void*);
void CopyEffectOwnerMargin(void*,void*);
f32 RandomFloatInRange(f32,f32);

void* FillMemory(void*,s32,s32);



void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateBackMemory(s32 size);
void CopyMemory(void* dst, void* src, s32 size);
void InitActiveSetSolver(ActiveSetSolver* loc, s32 count);
void RunActiveSetSolver(ActiveSetSolver* loc, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

struct EffectOwnerSlot { u8 pad[4]; s32* f4; s32 f8; };
EffectOwner* AcquireEffectOwner(u8* ctx, s32 flag);
void CopyEffectOwnerMargin(EffectOwner* a, Rec50* b);
Effect* CreateEffect(s32 a, EffectOwner* b);
void SetTrailSegmentAnchor(EffectOwner* self, s32 kind, Effect* extra);
void func_001583E8(Effect* a, Rec50* b);
f32 RandomFloatInRange(f32 a, f32 b);
s32 IsListEmpty(void* p);

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
void* FillMemory(void* p, s32 v, u32 n);
struct SpawnFlags { s32 z; s32 b; s32 c; SpawnFlags() { FillMemory(this, 0, sizeof(*this)); } };
struct __attribute__((aligned(16))) SpawnRecord { u8 pad0[0x20]; Quad16 self_copy; u8 pad1[0x30]; Quad16 a1_copy; u8 pad2[0x30]; SpawnBlock blk; s32 f120; u8 pad3[0x8C]; SpawnTail tail; u8 pad4[0x10]; };

void InitSpawnRecord(void* mem);
void SpawnEffectsFromRecord(void* a, void* b, void* c);


struct BriefEffectParams { u8 pad0[0xC]; s32 fC; };
struct BriefEffectSource { u8 pad0[0x278]; BriefEffectParams* f278; };
typedef void (*EffectStartFn)(Effect* self, void* a, s32 z, f32 f);

void* CreateEffect(s32 a, s32 b);

void StartObject(void* a0);

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

void CopyObjectData(void* self);
MemberObject* CreateObjectCopy(void* a, void* b, void* c);

void BindAnimatorRecord(CursorAnimator* self);
AnimRecord* FindAnimRecord(s32 key);
void SetCrossfadeMode(CrossfadeAnimator* self, s32 mode);

s32 IsObjectAttached(void* obj);
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
void AppendToList(List01* a, ObjectCycler* b);

void* CloneSharedSpawnRecord(void* x);

struct MemberTargetObject;
MemberTargetObject* FindFirstObjectById(void* a0, s32 a1, s32 a2, void* a3);
s32 IsObjectOfKind(void* self, s32 kind);

// A message held back by SendMessageAfterDelay (a slot of the world's pool at +0x1BD0, in its
// list at +0x1BDC, linked at +0x64): the receiver, the 0x50-byte message, the time it is due.
struct DelayedMessageBody { Quad16 q[5]; };
struct DelayedMessage { void* owner; u8 pad0[0xC]; DelayedMessageBody body; f32 due; };

extern f32 g_gameClock[];

void* PopFreeSlot(void* p);
void ClearListLinks(void* p);
void AppendToList(void* list, void* item);
void func_001590A0(void* self, void* body);

void InitSoundParams(void* p);


void* CreateTypedRecord(s32 a0, void* a1, void* a2, s32 a3, s32 a4);
void CopyMemory(void* dst, void* src, s32 size);
s32 GatherObjectsById(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);

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

MemberTargetObject* FindFirstObjectById(void* a0, s32 a1, s32 a2, void* a3);
void ResolveSpawnRecordTargets(Rec79* rec, RecordMember* self);

extern f32 g_gameTime;
f32 RandomFloatInRange(f32 a, f32 b);

extern f32 g_gameTime;
f32 RandomFloatInRange(f32 a, f32 b);
void SetCursorFrame(AnimCursor* cur, s32 idx);


void* AllocateZeroedFrontMemory(s32 size);
void InitSpawnRecord(void* p);
s32 ReadBufferedS8(void* other);
PathCurve* CreatePathCurve(s32 kind);
void* ReadBufferedU16(void* other);
void func_00154C80(void* p, void* other);
void ReadCappedWordList(void* a, void* b, void* c, void* d);
extern s32 g_objectCyclerStartLinks[6];

void ResolveObjectLinks(void* self, s32 n, void* p);
f32 RandomFloatInRange(f32 a, f32 b);
void SetObjectCyclerState(ObjectCycler* self, s32 x);
void StartPlacedObject(void* self);



void* PopZeroedFreeSlot(void* where);
void AppendToList(void* where, WorldObjectNode* node);



void RemoveFromList(void* where, WorldObjectNode* node);
void PushFreeSlot(void* where, WorldObjectNode* node);
void PushFreeSlot(void* l, void* n);

extern f32 g_frameDt;
void UpdatePlacedObject(void* self);
f32 ApproachValueWithRamp(void* p, s32 zero, f32 a, f32 b, f32 c);

struct ScaledDrawFrame { Quad16 q0; u8 pad1[0x30]; Quad16 m40[4]; u8 pad2[0x10]; Quad16 m90[4]; };

void BuildUniformScaleAboutPoint(s32 zero, void* out, f32 v);
void BuildPlacedObjectTransform(void* obj, void* c, void* out);
void MultiplyMatrices(Quad16* out, void* b, Quad16* in);
void DrawPlacedObject(void* obj, void* b, void* m);


struct ScreenFillPacket { u8 buf[0x2C0]; s32 value; };

void FillScreenColor(void* buf, s32* value, s32 flag);
void BeginDmaTag(void* self);
void WriteVifDirect(void* self, s32 n, void* buf, s32 flag);
void CloseDmaTag(void* self);

extern f32 g_gameTime;


void AppendToList(void* list, void* item);

s32 GatherObjectsByMode(void*,s32,s32,void*,s32,void*);

void LoadPlacedObject(void*,void*);
s32 ReadMeshTables(void*,void*,void*,void*,void*);

AnimCursor* FindAnimatorCursor(CursorAnimator* self, const AnimRecord* key);

void AddRangeEntry(void*,void*,void*,f32,f32,f32,f32,void*);

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

void SetObjectCyclerState(void* self, s32 x);
void func_001BC0E0(void* a0, f32 x, void* a1, void* a2);

// NEAR: the last float zero (f16) is scheduled into the jal delay slot instead of before the integer argument moves.


void CopyCollider();
s32 IsInList(void* sub, ObjectCycler* self);
void RemoveFromList(void* data, ObjectCycler* self);
void StartSoundEffect(f32 f12, f32 f13, f32 f14, f32 f15, s32 a0, void* a1, void* a2, s32 a3, f32 f16, s32 a4, s32 a5);

// NEAR: the last float zero (f16) is scheduled into the jal delay slot instead of before the integer argument moves.


void StopSoundRecord(void* self, s32 n);
void StartSoundEffect(f32 f12, f32 f13, f32 f14, f32 f15, s32 a0, void* a1, void* a2, s32 a3, f32 f16, s32 a4, s32 a5);

// The colour UpdateColorFade blends, word-aligned, and its request: DeferredRequest's layout
// with that colour at +0x60 (DeferredRequest's Rgba4 would copy it unaligned).
struct __attribute__((aligned(4))) FadeColor { u8 c[4]; };
struct FadeRequest { void* fn; f32 f; s32 mode; u8 pad[0x54]; FadeColor col; u8 pad2[0x1C]; };
extern s32 D_00275BC4;

extern s32 D_00270458;
extern f32 g_gameTime;
void RemoveFromList(u8* a, ColorFade* b);
void DrawScreenFill(ColorFade* o);
void QueueDeferredRequest(FadeRequest* r);

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

s32 ReadBufferedS16(void* src);
s32 IsObjectOfKind(void* node, s32 kind);
void* CreateTypedRecord(s32 a0, void* a1, void* a2, s32 a3, s32 a4);

struct ClassKindNode { ClassKindNode* next; s32 value; };

extern u8 D_00247448[];

s32 IsObjectAttached(PlacedObject* o);

typedef int Quadword128 __attribute__((mode(TI)));

extern f32 g_gameClock[];

void UpdateCollider(ObjectCycler* self);
void SetObjectCyclerState(ObjectCycler* self, s32 mode);
s32 func_0015BEF0(ObjectCycler* self);
s32 func_0015BD48(ObjectCycler* self, Quadword128* out);
void func_0015BC78(ObjectCycler* self);
s32 IsObjectCyclerUnsupported(ObjectCycler* self);
s32 func_0015BFC0(ObjectCycler* self);
f32 RandomFloatInRange(f32 a, f32 b);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

void InitPlacedObject(void* self);

extern f32 g_gameClock[];


void func_001590A0(void* a, void* b);
void RemoveFromList(List01* list, DelayedMessage* node);
void PushFreeSlot(Pool6C* set, DelayedMessage* node);


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

void LoadCollider(ObjectCycler* self, void* arg);
void ResolveObjectLinks(ObjectCycler* self, s32 n, void* table);
void FindOrBuildMemberGroup(void** out, ObjectCycler* self);
s32 FindFirstObjectByIdMode1(u8* self, s32 kind, ObjectCycler* arg);
void ResolveAndStartObject(s32 a);
s32 IsInList(List01* sub, ObjectCycler* self);
void RemoveFromList(List01* data, ObjectCycler* self);

struct CyclerDrawParams { u8 pad[0x40]; f32 scale; u8 pad2[0x10 - 4]; };
extern f32 g_gameTime;
extern f32 D_00262230[4];
extern f32 D_00262240[4];
extern f32 g_unitRange[];
void BuildPlacedObjectTransform(ObjectCycler* self, void* c, void* out);

s32 IsObjectOfKind(PlacedObject* obj, s32 id);
s32 IsObjectAttached(PlacedObject* obj);
s32 IsClassOfKind(u32 i, s32 id);
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

void RewindTextReader(void* self);
s32 ReadTextChar(void* self);

// The packet memory a GIF writer fills: quadwords.
typedef u64 UQuadword128 __attribute__((mode(TI)));

extern u8 D_00212160[];
extern u8 D_00215C50[];

void* InitGifPacket(void* p);
void UsePacketBufferMemory(void* p, s32 n, void* q);
void BeginGifTag(void* p, s32 a, s32 b, s32 c);
void AddGifRegisterWrite(void* p, s32 a, s32 b);
void EndGifPacket(void* p);
void WriteVifFlush(void* self);
void WriteVifDirectFromWriter(void* self, void* p);
void AddDmaRefTagIfChanged(void* self, void* a, void* b);
void AddDmaEndTag(void* self);
void DetachPacketBuffer(void* self, void* p, s32 n);

void CopyFontMetrics(Font* self, Font* dst);

FontGlyph* FindFontGlyph(Font* table, s8 key);

void CloseDmaTag(void* obj);
void AddDmaRefTag(void* obj, s32 a, s32 b);
void BeginDmaTag(void* obj);

void SetFontClipRect(Font* a0, s32 a1, void* a2);
s32 AddFontImagesToFrame(Font* self, void* obj);
void BeginGifTag(void* obj, s32 a, s32 b, s32 c);
void AddGifRegisterWrite(void* obj, s32 tag, s64 value);
void BeginGifRegListTag(void* obj, s32 tag, s64 value);

extern s32 g_defaultFont;

void CopyMemory(void* dst, void* src, s32 size);


extern s32 g_vif1Channel;
extern s32 g_gifChannel;

void ActivateRenderFrame(void* a, s32 b);
void SendGsPacketAndWait(s32 a, s32 b);


void* InitGifPacket(void* p);
void* InitPacketWriter(void* p);

void ConstructPacketWriters(s32 flag, s32 code);

struct GroundProbe {
    Vec02 q;
    s32 a;
    s32 b;
};

extern f32 g_gameClock[];

typedef s32 (*ObjectFilterFn)(void* a, void* b);

s32 IsCyclerGroundCandidate(void* a, void* b);
void PushBackMemoryMark(void* self);
s32 FindNearestSpanObject(s32 zero, void* p, void* q, s32 a, s32 b, s32 c);
void PopBackMemoryMark(void);
void GatherCollidersInSphere(s32 a0, s32 a1, void* a2, ObjectFilterFn a3, void* a4, s32* a5, s32* a6, f32 f12);

void AddDmaRefTag(void* list, u32 count, s32 value);
extern s32 D_0026230C;

void BeginGifTag(void* obj, s32 a, s32 b, s32 c);
void AddGifRegisterWrite(void* obj, s32 a, s32 b);
void EndGifPacket(void* obj);
void AddDmaEndTag(void* obj);
void DetachPacketBuffer(void* obj, void* a, s32 b);

void WriteGsFinishPacket(void* list, void* a, s32 b);
void CloseDrawBuffer(void* obj, void* a, s32 b);
void ClearList(void* p);
s32 PostSemaphore(void* a);

extern List01 D_002622E0;
extern List01 D_002622F0;
extern List01 g_deferredReleaseListC;
extern s32 g_buildFrameData;
extern void* g_frameReadySemaphore;



extern s32 g_drawFrameData;
extern s32 g_maskedImagesPacket;
extern s32 g_gifChannel;

void SwitchActiveImageMask(s32 value);
void StartDmaChain(s32 a, s32 b);


void RewindTextReader(void* self);
s32 ReadTextChar(void* self);

void RewindTextReader(void* self);
s32 ReadTextChar(void* self);


void RewindTextReader(void* self);
s32 ReadTextChar(void* self);

s32 WrapTextLines(void* self);

extern s8 g_fontEscapeKeys[];
extern s32 g_fonts[];

s32 WrapFontString(Font* self, u8* s);

// NEAR: the first load of self->p54 goes to $v0 (retail $v1), so two
// pointer loads differ in register choice; everything else matches.

struct FontUploadFrame { PacketWriter a; u8 buf[0x100]; };
PacketWriter* InitGifPacket(PacketWriter* p);
s32 AllocateBump(void* self, s32 size);
void BuildImageTexRegister(void* self, s32 v);
void UsePacketBufferMemory(void* self, s32 count, void* base);
void StartImageUpload(void* self, s32 dbp, void* ctx);
void DetachPacketBufferCopy(void* self, s32* count, u32* begin, s32* out, s32 flag);
void BuildPaletteTexRegister(void* self, s32 v);
void StartPaletteUpload(void* self, s32 v, void* ctx);

// Matched: for loop over i with D_00262264 + i * 0x88.

extern s32 g_fontCount;
extern u8* g_fontRecords;

void InitBumpAllocator(void* dst, s32 size, s32 align);
void UploadFontImages(void* item, void* buf);


void AddGifRegListFloat(PacketWriter* s, u32 tag, f32 value);
void AddGifUvRegListEntry(PacketWriter* s, s32 a, s32 b);
void AddGifXyzfRegListEntry(PacketWriter* s, s32 a, s32 b, s32 c, s32 d);

FontGlyph* FindFontGlyph(Font* self, s8 key);

s32 WrapTextLines(void* self, f32 f);
f32 MeasureTextWidth(void* self);



extern u32 D_002C3B00[];
extern u8 D_00148D74[];
extern s32 g_codeChecksumFailed;

extern void* g_frameDoneSemaphore;
extern volatile s32 g_renderThreadWaiting;
extern void* g_drawingFrame;
extern s32 D_002626CC;

s32 AwaitSemaphore(void* a);
void SendRenderFrameToDma(void* self, s32 flag);
void BlitFrameToDisplay(void);
void FlipDisplayFrame(void);
void ReleaseFrameNodes(void* p);
void ClearScreenOwner(s32 a);

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



void ReadBufferedStreamBytes(void* src, s32 n, void* dst);
void* AllocateFrontMemory(s32 n);
extern s32 D_00262258;
extern s32 D_0026225C;

FontGlyph* FindFontGlyph(Font* self, s8 key);
s32 AddFontImagesToFrame(Font* self, PacketWriter* s);
void BeginGifTag(PacketWriter* s, s32 a, s32 b, s32 c);
void AddGifRegisterWrite(PacketWriter* s, s32 a, u64 b);
void BeginGifRegListTag(PacketWriter* s, s32 a, u64 b);
void AddGifRegListFloat(PacketWriter* s, u32 tag, f32 value);
void AddGifUvRegListEntry(PacketWriter* s, s32 a, s32 b);
void AddGifXyzfRegListEntry(PacketWriter* s, s32 a, s32 b, s32 c, s32 d);

// NEAR: CRC table loop: retail keeps inner counter k in v1 and n*4 in a1; ours swaps them (5 insns)

extern u8 D_003C3B00[], D_005C3B00[];
extern void* g_frameReadySemaphore;
extern void* g_frameDoneSemaphore;
extern void* g_mainAndRenderThreads[];
void SetListLinkOffset(List01* self, s32 value);
void AddInterruptHandler(s32 a0, void (*fn)(void), s32 a2);
void EnableInterruptCause(s32 a0);
void* CreateLockSemaphore(s32 a, s32 b);
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
s32 AwaitSemaphore(void* p);
void ActivateRenderFrame(RenderFrame* f);
void ApplyPendingDisplayFlip(void);
void SendGsPacketAndWait(s32 a, s32 b);
void BlitFrameToDisplay(void);
s32 WaitDmaChannel(s32 a, s32 b, s32 c);
void FlipDisplayFrame(void);


struct FrameNode {
    u8 pad0[0x14];
    u8* f14;
    u8 pad18[0x1088 - 0x18];
    void* f1088;
};


s32 IsListEmpty(List01* l);
void RemoveFromList(List01* l, FrameNode* n);
void AppendToList(u8* l, FrameNode* n);
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
s32 AwaitSemaphore(void* a);
void UsePacketBufferMemory(void* self, s32 count, void* base);
void BeginDmaTag(void* self);

INCLUDE_ASM(func_001549C8);

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
    SetListLinkOffset(self->list314,0x320);
}

f32 ReadBufferedFloat(void* stream);
void ReadBufferedVector3(void* stream, Vec02* out);

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

void func_00154C80(void* p, void* other)
{
    MeshData* m = (MeshData*)p;
    s32 i;
    m->vertexCount = (s32)ReadBufferedU16(other);
    m->vertices = (Vec02*)AllocateFrontMemory(m->vertexCount << 4);
    m->normals = (Vec02*)AllocateZeroedFrontMemory(m->vertexCount << 4);
    for (i = 0; i < m->vertexCount; i++) {
        ReadBufferedVector3(other, &m->vertices[i]);
    }
    m->triangleCount = (s32)ReadBufferedU16(other);
    m->triangles = (MeshTriangle*)AllocateFrontMemory(m->triangleCount << 4);
    m->totalArea = 0.0f;
    for (s32 k = 0; k < m->triangleCount; k++) {
        MeshTriangle* t = &m->triangles[k];
        for (i = 0; i < 3; i++) {
            t->corner[i] = (s32)ReadBufferedU16(other);
        }
        t->area = ReadBufferedFloat(other);
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
    ReadBufferedVector3(other, &m->extent);
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
    self->source = ReadBufferedU8(src);
    for (s32 i = 0; i < count; i++) {
        StreamWord tmp = ReadBufferedU32(src);
        if (i < self->cap) {
            self->items[i] = *(U32P*)&tmp;
        }
    }
}

void LoadEffectSpawner(EffectSpawner* self, s32 count)
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
            fn(obj, (void*)count);
        }
    }
    if (self->rec->kind == 4) {
        func_00154C80(&self->rec->curve20, count);
    }
    s32 n = ReadBufferedU16(count);
    if (n != 0) {
        void* b = GetOwnSpawnRecord(self, 1);
        ReadCappedWordList((u8*)b + 0x130, n, self, count);
    }
}

void CopyEffectSpawner(EffectSpawner* self)
{
    CopyPlacedObject(self);
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
        SpawnerLinkedObject* r = FindFirstObjectById(self->world, 0x104, self->id2F8[0], self);
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
        SpawnerLinkedObject* s1 = FindFirstObjectById(self->world, 0x104, self->id300, self);
        if (IsObjectOfKind(s1, 3) != 0) s2->found[2] = s1;
    }
    if (self->id30C != -1) {
        SpawnerLinkedObject* r = FindFirstObjectById(self->world, 0x104, self->id30C, self);
        s2->value20 = r->f34;
        s2->target = r->f18;
    }
tail:
    ResolveSpawnRecordTargets(self->rec, self);
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
        EffectSpawner* copy = (EffectSpawner*)FindFirstObjectByIdMode1((u8*)self->world, self->f310, (ObjectCycler*)0);
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
        AppendToList(copy->list314, self);
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

void AddSpawnRangeEntry(void* self,void* a,void* b,f32 x,f32 y,f32 z,f32 w)
{
    u8* p=(u8*)GetOwnSpawnRecord(self,1);
    AddRangeEntry(p+16,a,b,x,y,z,w,self);
}

INCLUDE_ASM(func_00155868);

void RandomizeEffectSpawnerDelay(EffectSpawner* self);
void UpdatePlacedObject(void* self, f32 dt);
s32 CountListItems(void* list);
void func_00155868(EffectSpawner* self);
void SetEffectSpawnerActiveFor(EffectSpawner* self, f32 f);
void SetEffectSpawnerActiveForever(EffectSpawner* self);
s32 IsEffectSpawnerActive(EffectSpawner* self);
void SpawnEffectsFromRecord(s32 count, Rec50* rec, SpawnFlags* p);

void func_00155AB0(EffectSpawner* self, f32 dt)
{
    ListFrame frame;

    if (self->f34C != 0) {
        RandomizeEffectSpawnerDelay(self);
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
            have = held != 0 ? CountListItems((u8*)held + 0x558) : 0;
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
    func_00155868(self);
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
        SetEffectSpawnerActiveForever();
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
    if (*(void**)(self+0x348)) func_0013A128(*(void**)(self+0x348),*(void**)(self+0x2D0));
    if (*(void**)(self+0x344)) CopyEffectOwnerMargin(*(void**)(self+0x344),*(void**)(self+0x2D0));
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
    void* r = GetOwnSpawnRecord(a0, 1);
    SetSpawnRecordKind(r, a1);
}

void SetOwnedSpawnRecordKind(void* a0, s32 a1)
{
    void* r = GetOwnedSpawnRecord(a0, 1);
    SetSpawnRecordKind(r, a1);
}

INCLUDE_ASM(func_00156288);

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
void ComputePolarOffset(Vec02* out, f32 angle, f32 a, f32 b);
void TransformDirectionBetweenFrames(void* from, void* to, void* dir, Vec02* out);

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
void func_00156718(SpawnShape* shape, s32 index, s32 count, Vec02* pos, Vec02* axis)
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
        ComputePolarOffset(&offset, RandomFloatInRange(-3.14159265f, 3.14159265f), (1.0f - u) * seg->r0 + u * seg->r1,
                           roots[0]);
        Vu0::Set(at, Vu0::Add(Vu0::Vec::Of(seg->from->v140), Vu0::Rotate(frame, Vu0::Vec::Of(offset))).q);
        TransformPointBetweenFrames(0, shape->anchor, &at, pos);
        switch (shape->mode) {
        case 2:
            TransformDirectionBetweenFrames(0, shape->anchor, &frame.r[2], axis);
            goto normalize;
        case 3: {
            Vu0::Set(side, NormalizedOr(Vu0::Cross(Vu0::Vec::Of(frame.r[2]), Vu0::Vec::Of(shape->dir)),
                                            Vu0::Vec::Of(g_unitXVector)).q);
            TransformDirectionBetweenFrames(0, shape->anchor, &side, axis);
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

void TransformDirectionBetweenFrames(void* from, void* to, void* dir, Vec02* out);
void ComputeObjectMotionInFrame(void* obj, s32 z, void* point, Vec02* out, s32 a, s32 b, s32 c);

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

void ComputeDirectionFromAngles(Vec02* out, f32 first, f32 second, f32 scale);
void BuildPerpendicularPair(Vec02* in, Vec02* out, const Vec02* a, const Vec02* b);

void func_00157098(SpawnRing* ring, SpawnSpan* range, Vec02* axis, s32 index, Vec02* out, f32 jitter, f32 flatten)
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
    ComputeDirectionFromAngles(&dir, second, first, RandomFloatInRange(range->lo, range->hi));
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

void func_00157248(SpawnPlacement* self, SpawnRing* ring, s32 unused, s32 index, Vec02* pos, Vec02* axis,
                   Vec02* dir, f32* start, f32* end)
{
    Vec02 k;
    func_00157098(ring, &self->range, axis, index, dir, self->jitter, self->flatten);
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
        node = AcquireEffectOwner((u8*)g_currentWorld, AT(s32, c, 0xC4));
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
        Effect* it = CreateEffect(AT(s32, c, 0x90), node);
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
        func_001583E8((Effect*)((u8*)it + 0xB0), self);
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
    if (IsListEmpty((u8*)node + 0x558)) {
        typedef void (*F2)(EffectOwner*);
        (*(F2*)(AT(u8*, node, 0) + 0x1C))(node);
    }
    }
}

INCLUDE_ASM(func_001575D8);

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
void func_001579B0(void* a, void* b, s32* out)
{
    s32 n = (s32)a;
    u8* rec = (u8*)b;
    SpawnRing ring;
    Vec02 axis;
    out[0] = (s32)AllocateBackMemory(n * 16);
    out[1] = (s32)AllocateBackMemory(n * 16);
    out[2] = (s32)AllocateBackMemory(n * 4);
    out[3] = (s32)AllocateBackMemory(n * 4);
    InitSpawnRing(*(s32*)(rec + 0xEC), (SpawnSpan*)(rec + 0xE4), n, &ring);
    for (s32 i = 0; i < n; i++) {
        func_00156718((SpawnShape*)(rec + 0x10), i, n, (Vec02*)out[0] + i, &axis);
        func_00157248((SpawnPlacement*)(rec + 0xA0), &ring, (s32)(rec + 0x10), i, (Vec02*)out[0] + i, &axis,
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
void ComputeObjectFrameAtTime(void* self, void* top, f32 t, Vec02* pos, Mat02* rot, Vec02* vel, Vec02* spin);

void func_00157B88(s32 n, void* owner, SpawnSetup* first, SpawnSetup* second)
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
    func_001579B0((void*)n, AT(Rec50*, r, 0x90), second->out);
    AT(SpawnFrame*, AT(Rec50*, r, 0x90), 0x78) = 0;
    f32 last = 3.40282347e+38f;
    for (s32 i = 0; i < n; i++) {
        if (AT(Rec50*, r, 0x90)->target != 0) {
            f32 t = ((f32*)first->out[3])[i] - g_gameClock[1];
            if (!AreFloatsNearlyEqual(t, last, 0.0001f)) {
                last = t;
                ComputeObjectFrameAtTime(AT(Rec50*, r, 0x90)->target, 0, last, &P, &M, &V, &W);
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

void SpawnEffectsFromRecord(void* a, Rec50* b, void* c)
{
    SpawnSetup f;
    if (a == 0) {
        return;
    }
    PushBackMemoryMark();
    f.flag = 1;
    func_001579B0(a, b, f.out);
    if (b->f120 == 1) {
        SpawnRecordEffects(b, c, a, f.out[0], f.out[1], f.out[2], f.out[3]);
    } else {
        if (b->f130 == 2) {
            func_00157B88(a, b, f.out, f.pair);
        } else {
            f.pair[0] = 0;
            f.pair[1] = 0;
        }
        func_001575D8(b, c, a, f.out[0], f.out[1], f.out[2], f.out[3], f.pair[0], f.pair[1]);
    }
    PopBackMemoryMark();
}

void SpawnEffectsAt(Quad16* self, Quad16* a1, void* a2, SpawnTail* a3, SpawnBlock* a4, s32 a5, s32 a6)
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
    SpawnEffectsFromRecord(a2, &f, &p);
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

void AddRangeEntry(RangeEmitter* self, s32 a1, s32 a2, f32 f12, f32 f13, f32 f14, f32 f15)
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
        rec->f18C = FindFirstObjectById(owner->world, 0x104, rec->f188, owner);
    }
    if (rec->kind == 3) {
        f32 total = 0.0f;
        for (s32 i = 0; i < rec->count; i++) {
            SpawnLink* link = &rec->links[i];
            for (s32 j = 0; j < 2; j++) {
                link->objs[j] = (PlacedObject*)FindFirstObjectById(owner->world, 0x104, link->ids[j], owner);
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
void BuildAxisAngleMatrix(void* axis, Mat4A* out, f32 angle);
void ScaleMatrix(Mat4A* out, Mat4A* in, u128 scale);
void AddMatrices(f32* a, f32* b, f32* out);

void TurnMatrixBySpin(SpinRecord_158480* spin, f32* out, f32 dt)
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
            TransformDirectionBetweenFrames(spin->frame, 0, &spin->axis, (Vec02*)&axis);
        } else {
            axis = spin->axis;
        }
        BuildAxisAngleMatrix(&axis, &turn, spin->rate * dt);
    }
    Mat4A term;
    Mat4A scaled;
    Mat4A product;
    Mat4A* result = &scaled;
    MultiplyMatrices((Quad16*)&product, &turn, (Quad16*)&place);
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
    total = ReadBufferedS16(src);
    for (i = 0; i < total; i++) {
        s32 r1 = ReadBufferedS16(src);
        s32 r2 = ReadBufferedS16(src);
        s32 r3 = ReadBufferedS16(src);
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

void CopyGroupMembers(MemberGroup* self)
{
    CopyObjectData(self);
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
    s32 idx = ReadBufferedS8(stream);
    if (idx != -1) {
        Rec79* n = GetOwnedSpawnRecord(self, 1);
        n->curve20 = CreatePathCurve(idx);
        if (n->curve20->vt->m00 != 0) {
            n->curve20->vt->m00(n->curve20, stream);
        }
    }
    Rec79* q = self->rec;
    if (q->kind == 4) {
        func_00154C80(&q->curve20, stream);
    }
    void* t = ReadBufferedU16(stream);
    if (t != 0) {
        Rec79* m = GetOwnedSpawnRecord(self, 1);
        ReadCappedWordList((u8*)m + 0x130, t, self, stream);
    }
}

void CopyRecordMember(RecordMember* self)
{
    CopyObjectData(self);
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
            MemberTargetObject* q = FindFirstObjectById(self->world, 260, self->id98, self);
            r->value20 = q->f34;
            r->target = q->f18;
        }
    }

tail:
    c = self->rec;
tail_c:
    ResolveSpawnRecordTargets(c, self);
}

void SendRecordMemberMessage(void)
{
}

void AddRecordMemberRangeEntry(RecordMember* self, void* a, void* b, f32 x, f32 y, f32 z, f32 w)
{
    u8* p = (u8*)GetOwnedSpawnRecord(self, 1);
    AddRangeEntry(p+16,a,b,x,y,z,w,self);
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
        if (IsObjectOfKind(p, 3) != 0) {
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
            ClearListLinks((u8*)r + 0x64);
            AppendToList(&self->world->list1BDC, r);
        }
    }
    if (done == 0) {
        func_001590A0(self, message);
    }
}

s32 GetOrCreateSoundParams(void* self)
{
    HoldingMember* o = (HoldingMember*)self;
    if (o->fA0 == 0) {
        InitSoundParams(&o->fA0);
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

void StoreFloatAsQuadword(void* out, f32 f);
void* CopyQuadword(void* out, void* in);
Quadword128 ScaleQuadword(Quadword128 a, Quadword128 b);
void* StoreQuadword(void* dst, Quadword128 v);
f32 ClampToRange(void* range, f32 x);
void ComputeChainedWorldFrame(void* a, void* frame, void* out);
void SpawnEffectsFromRecord(s32 count, void* rec, void* chain);
void TransformPointBetweenFrames(void* from, s32 to, Vec02* point, Vec02* out);
extern f32 D_00262178[2];
extern const Vec02 D_00248D30;

void func_001590A0(void* self, void* body)
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
            f32 r = ClampToRange(D_00262178, s);
            rec.fA0 = rec.fA0 * r;
            rec.fA4 = rec.fA4 * r;
            f32 lowest = 0.5f;
            s = lowest >? s;
            Quad16* q = &rec.q140;
            StoreFloatAsQuadword(&qa, s);
            Quadword128 q0 = *(Quadword128*)&qa;
            CopyQuadword(&qb, q);
            StoreQuadword(q, ScaleQuadword(q0, *(Quadword128*)&qb));
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
    SpawnEffectsFromRecord(count, &rec, cp);
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
        TransformPointBetweenFrames((void*)rec.target, 0, &v, &v);
        u8* snd = AT(u8*, self, 0xA0);
        StartSoundEffect(AT(s32, snd, 0), 0, 0, (s32)&v, AT(f32, snd, 4), AT(f32, snd, 8), AT(f32, snd, 0xC), AT(f32, snd, 0x10), 0.0f, 0, 0);
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
    s2 = (MemberGroup*)CreateTypedRecord(0x78, o->world, self, 0x202, -1);
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
            func_001590A0(node->owner, &node->body);
            RemoveFromList(&self->list1BDC, node);
            PushFreeSlot(&self->pool1BD0, node);
        }
    }
    g_activeListFrames = it.prev;
}

ASM_FUNC(func_00159668);

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
    WorldObjectNode* node = (WorldObjectNode*)PopZeroedFreeSlot((u8*)g_currentWorld + 0x1C18);
    node->owner = self;
    if (self->f294 != 0) {
        AppendToList((u8*)g_currentWorld + 0x1C30, node);
    } else {
        AppendToList((u8*)g_currentWorld + 0x1C24, node);
    }
    return node;
}

void RemoveObjectNodeFromWorld(WorldObjectNode* node)
{
    if (node->owner->f294 != 0) {
        RemoveFromList((u8*)g_currentWorld + 0x1C30, node);
    } else {
        RemoveFromList((u8*)g_currentWorld + 0x1C24, node);
    }
    node->owner->f298 = 0;
    PushFreeSlot((u8*)g_currentWorld + 0x1C18, node);
}

void DrawScreenFill(u8* a0)
{
    ScreenFillPacket f;
    f.value = *(s32*)(a0 + 0x60);
    FillScreenColor(&f, &f.value, 0);
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
                RemoveFromList(p, self);
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
    QueueDeferredRequest(&q);
}

void StartColorFade(ColorFade* a0)
{
    if (a0->running == 0) {
        a0->running = 1;
        a0->startTime = g_gameTime;
        AppendToList((u8*)g_currentWorld + 0x1CD8, a0);
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

s32 GatherObjectsByMode(void* host, s32 flags, s32 id, void* rootp, s32 max, void* foundp)
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

MemberTargetObject* FindFirstObjectById(void* self,s32 flags,s32 kind,void* arg)
{
    s32 out=0;
    GatherObjectsByMode(self,flags|0x200,kind,arg,1,&out);
    return (MemberTargetObject*)out;
}

s32 FindFirstObjectByIdMode4(void* self,s32 kind,void* arg)
{
    s32 out=0;
    GatherObjectsByMode(self,0x204,kind,arg,1,&out);
    return out;
}

s32 FindFirstObjectByIdMode1(void* self,s32 kind,void* arg)
{
    s32 out=0;
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

s32 GatherObjectsById(World* world, u32 flags, s32 id, PlacedObject* root, s32 max, PlacedObject** found)
{
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

s32 FindFirstObjectByIdGathered(void* self,s32 flags,s32 kind,void* arg)
{
    s32 out=0;
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

void InitC60Object(C60* self)
{
    InitPlacedObject(self);
    f32* v = self->v;
    self->f2F0 = 1.0f;
    self->f2EC = 1.0f;
    self->v[0] = 1.0f;
    v[1] = 0.2f;
    v[2] = 0.1f;
}

void LoadC60Object(C60* self,void* other)
{
    LoadPlacedObject(self,other);
    ReadMeshTables(other,&self->out2D0,&self->out2D4,&self->out2D8,&self->out2DC);
}

void UpdateC60Object(C60* self)
{
    UpdatePlacedObject(self);
    self->f2EC = ApproachValueWithRamp(self->v, 0, self->f2EC, self->f2F0, g_frameDt);
}

void DrawC60Object(C60* self, void* arg1, void* arg2)
{
    ScaledDrawFrame f;
    BuildUniformScaleAboutPoint(0, &f.q0, self->f2EC);
    BuildPlacedObjectTransform(self, arg2, f.m40);
    MultiplyMatrices(f.m90, f.m40, &f.q0);
    f.m40[0] = f.m90[0];
    f.m40[1] = f.m90[1];
    f.m40[2] = f.m90[2];
    f.m40[3] = f.m90[3];
    DrawPlacedObject(self, arg1, f.m40);
}

s32 IsPointInsideFaceTree(s32 tree, Vec02* point);

s32 func_0015AA50(C60* self, void* point)
{
    Vec02 local;
    Vec02 k;
    if (self->f2EC < 0.0001f)
        return 0;
    TransformPointBetweenFrames(0, self, point, &local);
    Vu0::Q(k) = Vu0::FromFloat(1.0f / self->f2EC);
    Vu0::Q(local) = Vu0::MulX(Vu0::Q(local), Vu0::Q(k));
    return IsPointInsideFaceTree(self->out2DC, &local);
}

void InitObjectCycler(ObjectCycler* self)
{
    InitCollider(self);
    self->state = -1;
    self->p610.pk = D_00262180;
    self->p618.pk = D_00262188;
    self->p620.pk = D_00262190;
    self->p628.pk = D_00262198;
    self->swapKind = -1;
    self->checkDelay.pk = D_002621A0;
    self->p650.pk = D_002621A8;
    self->p658.pk = D_002621B0;
    self->p660.pk = D_002621B8;
    self->p670.pk = D_002621C0;
    self->indexStep = 1;
    self->f690 = -1;
    AppendToList(&self->world->list1C48, self);
}

void LoadObjectCycler(ObjectCycler* self, void* arg)
{
    u32 i;
    LoadCollider(self, arg);
    ResolveObjectLinks(self, 2, g_objectCyclerLoadLinks);
    FindOrBuildMemberGroup((void**)&self->group, self);
    for (i = 0; i < 16; i++) {
        s32 kind = i + 0x23C;
        s32 p = FindFirstObjectByIdMode1((u8*)self->world, kind, self);
        if (!p)
            continue;
        ResolveAndStartObject(p);
        if (self->mode == 1) {
            if (self->swapKind == kind)
                self->swapIndex = self->count;
        }
        self->objs[self->count++] = (PlacedObject*)p;
    }
    if (self->mode == 1) {
        for (i = 0; i < 8; i++) {
            s32 p = FindFirstObjectByIdMode1((u8*)self->world, i + 0x24D, self);
            if (p) {
                ResolveAndStartObject(p);
                self->altObjects[self->altCount++] = (PlacedObject*)p;
            }
        }
    }
    if (self->mode) {
        if (IsInList(&self->world->list1C48, self))
            RemoveFromList(&self->world->list1C48, self);
    }
}

void CopyObjectCycler(ObjectCycler* self)
{
    PackedFloatPair tmp;
    tmp = self->f5DC;
    CopyCollider();
    self->f5DC = tmp;
    if (self->mode == 0) {
        StartSoundEffect(700.0f, 10.0f, 1.0f, 0.0f, 0x41, &self->handle, self, 0, 0.0f, 0, 0);
    } else {
        if (IsInList(&self->world->list1C48, self) != 0) {
            RemoveFromList(&self->world->list1C48, self);
        }
    }
}

void SetObjectCyclerHandle(ObjectCycler* self, s32 flag)
{
    if (self->mode == 0) {
        if (flag != 0) {
            StopSoundRecord(self->handle, 0);
        } else {
            StartSoundEffect(700.0f, 10.0f, 1.0f, 0.0f, 0x41, &self->handle, self, 0, 0.0f, 0, 0);
        }
    }
}

void StartObjectCycler(ObjectCycler* self)
{
    ResolveObjectLinks(self, 2, g_objectCyclerStartLinks);
    if (self->mode == 1) {
        f32 t = RandomFloatInRange(self->checkDelay.a, self->checkDelay.b);
        self->nextCheckTime = g_gameClock[1] + t;
        t = RandomFloatInRange(self->p670.a, self->p670.b);
        self->f680 = g_gameClock[1] + t;
    }
    SetObjectCyclerState(self, self->startState);
    StartPlacedObject(self);
    self->f64C = self->radius3CC + self->radius3CC;
}

extern f32 D_002621F8[6];
extern f32 D_00262210[4];
extern f32 D_00262220[4];
void EvaluateHermiteVectorSegment(f32 t, f32 dt, f32 scale, Vec02* p0, Vec02* v0, Vec02* p1, void* v1, Vec02* outPos, Vec02* outVel, s32 zero);
void ClampVectorLength(Vec02* out, Vec02* in, f32 limit);
void AddColliderForce(Collider* self, Vec02* force);
void BuildBasisFromXAndZHint(Vec02* x, Vec02* zHint, Mat02* out);
void ApproachRotationWithRamp(Mat02* current, Mat02* target, const f32* ramp, f32 dt, s32 zero, Vec02* out);
void SteerColliderTowardPosition(Collider* self, void* a, void* b, const Vec02* zero, const f32* ramp, f32 dt);
void SteerColliderTowardRotation(Collider* self, void* a, void* b, const Vec02* zero, const f32* ramp, f32 dt);
void StepCollider(Collider* self, f32 dt);

// k, the ramp's output, is read and written at its own address (*(u128*)&k): through Vu0::Q
// its address stays in a saved register, where retail forms it again for each call.
void func_0015AF50(ObjectCycler* self, f32 dt)
{
    switch (self->state) {
    case 0:
    case 3:
    case 5: {
        Vec02 pos;
        Vec02 vel;
        Vec02 accel;
        Vec02 k;
        Mat02 basis;
        f32 t = self->stateEnd + dt - g_gameClock[1];
        EvaluateHermiteVectorSegment(t, dt, 1.0f, &self->pos, &self->v150, &self->v5F0, (u8*)self + 0x600, &pos, &vel, 0);
        Vu0::Q(accel) = Vu0::Sub(Vu0::Q(vel), Vu0::Q(self->v150));
        *(u128*)&k = Vu0::FromFloat(1.0f / dt);
        Vu0::Q(accel) = Vu0::MulX(Vu0::Q(accel), *(u128*)&k);
        ClampVectorLength(&accel, &accel, 3000.0f);
        AddColliderForce(self, &accel);
        Vu0::Q(accel) = Vu0::Sub(Vu0::Q(accel), Vu0::Q(self->gravity));
        BuildBasisFromXAndZHint(&vel, &accel, &basis);
        ApproachRotationWithRamp(&self->rot, &basis, D_002621F8, dt, 0, &k);
        self->desc02()->m21(self, &k);
        break;
    }
    case 1:
        AddColliderForce(self, &self->gravity);
        SteerColliderTowardPosition(self, 0, 0, &D_00248D30, D_00262210, dt);
        SteerColliderTowardRotation(self, 0, 0, &D_00248D30, D_00262220, dt);
        break;
    case 6:
        StepCollider(self, dt);
        break;
    }
}

void UpdateObjectCycler(ObjectCycler* self)
{
    UpdateCollider(self);
    if (self->stateEnd <= g_gameClock[1]) {
        s32 a1 = self->state;
        switch (a1) {
        case 0:
        case 3:
            SetObjectCyclerState(self, -1);
            a1 = 0;
            break;
        case 1:
            a1 = 2;
            break;
        case 5:
            a1 = func_0015BEF0(self);
            break;
        case 6:
            a1 = 0;
            break;
        default:
            break;
        }
        SetObjectCyclerState(self, a1);
    }
    s32 st = self->state;
    switch (st) {
    case 0:
    case 3:
    case 5: {
        s32 sub = self->mode;
        switch (sub) {
        case 0:
            if (self->handle == 0) {
                StartSoundEffect(0x41, &self->handle, (s32)self, 0, 700.0f, 10.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
            self->index = (self->index + 1) % self->count;
            break;
        case 1:
            if (st == 0) {
                if (self->nextCheckTime <= g_gameClock[1]) {
                    Quadword128 tmp;
                    if (func_0015BD48(self, &tmp)) {
                        *(Quadword128*)&self->v5F0 = tmp;
                        SetObjectCyclerState(self, 5);
                    } else {
                        self->nextCheckTime = g_gameClock[1] + RandomFloatInRange(self->checkDelay.a, self->checkDelay.b);
                    }
                }
            }
            if (self->nextStepTime <= g_gameClock[1]) {
                s32 n = self->count;
                if (n >= 2) {
                    s32 v = self->index + self->indexStep;
                    self->index = v;
                    if (v >= n) {
                        self->index = n - 2;
                        self->indexStep = -1;
                    } else if (v < 0) {
                        self->index = 1;
                        self->indexStep = 1;
                    }
                    self->nextStepTime = g_gameClock[1] + self->stepInterval;
                }
            }
            break;
        }
        if (0.15f < g_gameClock[1] - self->stateStart) {
            ContactRow03* n = self->contacts->head;
            if (n != 0) {
                for (; n != 0; n = n->next) {
                    if (n->head != 0) {
                        self->stateEnd = g_gameClock[1];
                        break;
                    }
                }
            }
        }
        break;
    }
    case 6:
        if (IsObjectCyclerUnsupported(self) || func_0015BFC0(self)) {
            SetObjectCyclerState(self, 0);
        } else if (self->nextAdvanceTime <= g_gameClock[1]) {
            s32 idx = (self->index + 1) % self->altCount;
            self->index = idx;
            self->nextAdvanceTime = g_gameClock[1];
            f32 x, y;
            if (idx == 0) {
                x = self->p660.a;
                y = self->p660.b;
            } else {
                x = self->p658.a;
                y = self->p658.b;
            }
            self->nextAdvanceTime += RandomFloatInRange(x, y);
        }
        break;
    }
    if (self->mode == 1) {
        s32 s = self->state;
        if (s == 0 || s == 5) {
            func_0015BC78(self);
        }
    }
}

void DrawObjectCycler(ObjectCycler* self, void* a1, void* a2)
{
    CyclerDrawParams out;
    BuildPlacedObjectTransform(self, a2, &out);
    switch (self->state) {
    case 1: {
        f32 base = self->stateStart;
        f32 num = g_gameTime - base;
        f32 den = self->stateEnd - base;
        f32 t = num / den;
        f32 v = D_00262230[0] + t * (D_00262230[1] + t * D_00262230[2]);
        f32 lo = g_unitRange[0];
        f32 hi = g_unitRange[1];
        if (v < lo) v = lo;
        else if (hi < v) v = hi;
        out.scale = out.scale * v;
        self->obj5D0->desc02()->m24(self->obj5D0, a1, &out);
        break;
    }
    case 3: {
        f32 base = self->stateStart;
        f32 num = g_gameTime - base;
        f32 den = self->stateEnd - base;
        f32 t = num / den;
        f32 v = D_00262240[0] + t * (D_00262240[1] + t * D_00262240[2]);
        f32 lo = g_unitRange[0];
        f32 hi = g_unitRange[1];
        if (v < lo) v = lo;
        else if (hi < v) v = hi;
        out.scale = out.scale * v;
        self->objs[self->index]->desc02()->m24(self->objs[self->index], a1, &out);
        break;
    }
    case 6: {
        self->altObjects[self->index]->desc02()->m24(self->altObjects[self->index], a1, &out);
        break;
    }
    default: {
        s32 idx = self->index;
        if (self->mode == 1 && self->swapKind != -1) {
            f32 t = (g_gameTime - self->stateStart) / (self->stateEnd - self->stateStart);
            if (1.0f - self->swapTail < t) idx = self->swapIndex;
        }
        self->objs[idx]->desc02()->m24(self->objs[idx], a1, &out);
        break;
    }
    }
}

s32 HandleObjectCyclerObjectEvent(ObjectCycler* self, CyclerEventMessage* r)
{
    if (self->state != 1) {
        SetObjectCyclerState(self, 1);
        if ((r->fC & 8) != 0) {
            func_001BC0E0(self, r->f8, &r->f20, &r->f30);
        }
        if (self->group != 0) {
            GroupForwardMessage loc;
            loc.f0 = 6;
            loc.f20 = r->f20;
            loc.f10 = r->f30;
            self->group->desc->m1B(self->group, &loc);
        }
    }
    return 1;
}

void SetColliderAnchors(void* self, s32 a, s32 b, s32 c, s32 d);
void ComputePolarOffset(Vec02* out, f32 angle, f32 a, f32 b);
void func_00130C58(s32 n, f32* a, double ka, f32* b, double kb, f32* c, double kc, f32* out);
void SetPlacedObjectVelocityFromFloats(PlacedObject* self, f32 x, f32 y, f32 z);
void ScatterObjectsAtPoint(void* scatter, Vec02* at, s32 a, s32 b);
void RotateMatrixUpright(Mat02* m, s32 zero, Mat02* out);
extern u8 D_00261EF0[];
void StartSoundEffect(s32 a0, void* a1, void* a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

void func_0015B7B8(ObjectCycler* self, s32 state)
{
    if (self->state == state) {
        return;
    }
    switch (self->state) {
    case 0:
    case 3:
    case 5:
        self->b2C8 = 0;
        break;
    case 2:
        self->desc->m02(self);
        break;
    case 6:
        SetColliderAnchors(self, 0, 0, 0, 0);
        self->index = 0;
        self->f680 = g_gameClock[1] + RandomFloatInRange(self->p670.a, self->p670.b);
        break;
    }
    (*(PlacedObject**)((u8*)self + 0x5D8))->f88 = 14;
    self->stateEnd = g_gameClock[1];
    switch (state) {
    case 0:
    case 3:
    case 5: {
        self->b2C8 = 11;
        if (state != 5) {
            f32 a = RandomFloatInRange(-3.14159274f, 3.14159274f);
            f32 b = RandomFloatInRange(self->p610.a, self->p610.b);
            ComputePolarOffset(&self->v5F0, a, b, RandomFloatInRange(self->p618.a, self->p618.b));
            Vu0::Q(self->v5F0) = Vu0::Add(Vu0::Q(self->v5F0), Vu0::Q(self->v190));
        }
        if (state == 5) {
            u128 d = Vu0::Sub(Vu0::Q(self->v5F0), Vu0::Q(self->pos));
            Vu0::Q(self->v600) = Vu0::MulX(Vu0::DivX(d, Vu0::Length(d)), Vu0::Scalar(50.0f));
        } else {
            f32 a = RandomFloatInRange(-3.14159274f, 3.14159274f);
            f32 b = RandomFloatInRange(self->p620.a, self->p620.b);
            ComputePolarOffset(&self->v600, a, b, RandomFloatInRange(self->p628.a, self->p628.b));
        }
        f32 m[3][4];
        f32 t;
        f32* p = &self->pos.x;
        f32* q = &self->v150.x;
        f32* r = &self->v5F0.x;
        f32* s = &self->v600.x;
        for (s32 i = 0; i < 3; i++) {
            m[i][0] = p[i];
            m[i][1] = q[i];
            m[i][2] = r[i];
            m[i][3] = s[i];
        }
        func_00130C58(3, m[0], 1500.0, m[1], 1500.0, m[2], 1500.0, &t);
        t = (f32)((s32)(t * 60.0f) + 1) * 0.0166666675f;
        self->stateEnd += t;
        if (self->state == 6 && state == 0) {
            SetPlacedObjectVelocityFromFloats(self, self->v600.x, self->v600.y, 400.0f);
            self->nextCheckTime = g_gameClock[1] + RandomFloatInRange(self->checkDelay.a, self->checkDelay.b);
        }
        break;
    }
    case 1:
        StartSoundEffect(0x3A, 0, 0, &self->v140, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        ScatterObjectsAtPoint(D_00261EF0, &self->v140, self->f690, *(s32*)((u8*)self + 0x694));
        self->stateEnd += 2.0f;
        break;
    case 2:
        self->desc->m03(self);
        self->state = state;
        self->stateStart = g_gameClock[1];
        return;
    case 6: {
        Mat02 m;
        RotateMatrixUpright(&self->m110, 0, &m);
        self->desc02()->m1E(self, &m);
        self->desc02()->m20(self, (Vec02*)&D_00248D30);
        self->desc02()->m21(self, (Vec02*)&D_00248D30);
        SetColliderAnchors(self, 3, 0, 3, 0);
        self->index = 0;
        self->nextAdvanceTime = g_gameClock[1] + RandomFloatInRange(self->p658.a, self->p658.b);
        self->f66C = g_gameClock[1];
        self->stateEnd += RandomFloatInRange(self->p650.a, self->p650.b);
        break;
    }
    }
    self->state = state;
    self->stateStart = g_gameClock[1];
}

extern const f32 D_0024A218[2] = {3.4028235e+38f, 0.0f};

void ConvertPositionToWorld(BaseObject* self, Quad16* out);

void func_0015BC78(ObjectCycler* self)
{
    GroupForwardMessage loc;
    if (self->receiver678 && self->f680 <= g_gameClock[1]) {
        loc.f0 = 6;
        if (self->source67C)
            ConvertPositionToWorld(self->source67C, &loc.f20);
        else
            loc.f20 = *(Quad16*)&self->v140;
        Vu0::Q(loc.f10) = Vu0::MulX(Vu0::Q(self->v150), Vu0::Scalar(-1.0f));
        ((f32*)&loc.f10)[2] = 0.0f;
        self->receiver678->desc->m1B(self->receiver678, &loc);
        self->f680 = g_gameClock[1] + RandomFloatInRange(self->p670.a, self->p670.b);
    }
}

struct ListedFrameItem {
    u8 pad00[0x18];
    void* frame;            // 0x18
    u8 pad1C[0x34 - 0x1C];
    BaseObject* item;       // 0x34
    ListedFrameItem* next;  // 0x38
};
typedef void (*ItemPointFn)(BaseObject* self, Vec02* in, s32 a, Vec02* out, s32 b, s32 c, s32 d);

// nearest is read at its own address (*(u128*)&nearest): through Vu0::Q the address stays in
// a pseudo that CSE keeps in a saved register across the walk, where retail forms it again.
s32 func_0015BD48(ObjectCycler* self, Quadword128* out)
{
    ListFrame frame;
    Vec02 hit;
    f32 best = D_0024A218[0];
    for (ListedFrameItem* n = (ListedFrameItem*)self->world->list1C9C.head; n != 0; n = n->next) {
        Vec02 from;
        Vec02 nearest;
        TransformPointBetweenFrames(0, n->frame, &self->v140, &from);
        ItemPointFn fn = (ItemPointFn)((void**)n->item->desc)[10];
        if (fn != 0) {
            fn(n->item, &from, 0, &nearest, 0, 0, 0);
        }
        f32 d = Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(from), *(u128*)&nearest)));
        if (d < best) {
            best = d;
            TransformPointBetweenFrames(n->frame, 0, &nearest, &hit);
        }
    }
    if (best < D_0024A218[0]) {
        ColliderSpan span;
        Vec02 below;
        s32 count;
        s32 list;
        PushBackMemoryMark();
        GatherCollidersInSphere((s32)self->world, (s32)self, &hit, 0, 0, &count, &list, 500.0f);
        below = hit;
        below.z = below.z - 500.0f;
        s32 r = FindNearestSpanObject(0, &hit, &below, count, list, (s32)&span);
        PopBackMemoryMark();
        if (r != 0) {
            *out = *(Quadword128*)&span;
            return 1;
        }
        return 0;
    }
    return 0;
}

s32 func_0015BEF0(ObjectCycler* self)
{
    s32 touching = 0;
    s32 next;
    for (ContactRow03* n = self->contacts->head; n != 0; n = n->next) {
        if (n->head != 0) {
            touching = 1;
            break;
        }
    }
    if (Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(self->v5F0)))) < self->f64C) {
        next = 6;
    } else if (touching) {
        next = 0;
        self->nextCheckTime = g_gameTime + RandomFloatInRange(self->checkDelay.a, self->checkDelay.b);
    } else {
        SetObjectCyclerState(self, -1);
        next = 5;
    }
    return next;
}

void* GetActiveSwitchedCollider(void);

// The squared length of d. ToFloatMoved: the qmfc2 is the compiler's and the mtc1 the helper's
// (one cycle each, where the compiler's mtc1 costs two), so in sched2 the difference's load has
// f684's priority, not one more, and f684's load and square come before it, as in retail.
static inline f32 LengthSquared(u128 d)
{
    return Vu0::ToFloatMoved(Vu0::Dot(d, d));
}

// Whether the active collider's point (its position plus half its velocity) is within f684 of
// the cycler. The position is named first: its load is expanded before the weight's slot store
// and passes it in both schedules, while the velocity, read inside the sum after the Scalar,
// waits for the store, as retail's lqc2 order shows.
s32 func_0015BFC0(ObjectCycler* self)
{
    Vec02 point;
    PlacedObject* active = (PlacedObject*)GetActiveSwitchedCollider();
    if (active != 0) {
        Vu0::Vec pos = Vu0::Vec::Of(active->v140);
        Vu0::Q(point) = Vu0::MulAddX(pos.q, Vu0::Q(active->v150), Vu0::Scalar(0.5f));
        s32 inside = LengthSquared(Vu0::Sub(Vu0::Q(point), Vu0::Q(self->v140))) < self->f684 * self->f684;
        if (inside) {
            return 1;
        }
    }
    return 0;
}

s32 IsCyclerGroundCandidate(GroundFilterContext* a0, GroundCandidate* a1)
{
    if ((a1->f538 & 0x80000000000ULL) || a1->f50 == a0->f50) return 0;
    u64 v = a1->f2CC;
    return ((s32)v ^ 1) & 1;
}

s32 IsObjectCyclerUnsupported(ObjectCycler* self)
{
    f32* tbl = g_gameClock;
    if (tbl[1] - self->f66C < 0.05f) {
        return 0;
    }
    PushBackMemoryMark(self);
    GroundProbe fr;
    GatherCollidersInSphere((s32)self->world, 0, &self->v140, IsCyclerGroundCandidate, self, &fr.a, &fr.b, self->f64C);
    fr.q = self->v140;
    fr.q.z = fr.q.z - self->f64C;
    s32 r = FindNearestSpanObject(0, &self->v140, &fr.q, fr.a, fr.b, 0);
    PopBackMemoryMark();
    self->f66C = tbl[1];
    return r == 0;
}

void ClearDefaultFont(void)
{
    g_defaultFont = 0;
}

s32 IsFontLoaded(s32 a0)
{
    if (a0 == -1) {
        goto none;
    }
    if (((s32*)g_fonts)[a0] != 0) {
        goto some;
    }
none:
    return 0;
some:
    return 1;
}

s32 GetFontById(s32 a)
{
    if (a == -1) {
        return 0;
    }
    s32 v = g_fonts[a];
    if (v != 0) {
        return v;
    }
    return g_defaultFont;
}

s32 FindFontByKeyChar(s32 a0)
{
    s8 key = (s8)a0;
    s32 i = 0;
    while (i < 5 && key != g_fontEscapeKeys[i]) {
        i++;
    }
    if (i < 5) {
        return g_fonts[i];
    }
    return 0;
}

void CopyFontMetrics(Font* src, Font* dst)
{
    dst->f00 = src->f00;
    dst->advance = src->advance;
    dst->height = src->height;
    dst->sx = src->sx;
    dst->sy = src->sy;
    dst->depth = src->depth;
    CopyMemory(dst->stack, src->stack, src->depth << 3);
    dst->f30 = src->f30;
    dst->f38 = src->f38;
    dst->f40 = src->f40;
}

void SetFontClipRect(Font* unused, Vec4U* v, PacketWriter* obj)
{
    if (v != 0) {
        s32 pw = (s32)(v->x + v->z) - 1;
        s32 pz = (s32)((v->y + v->w) * 0.454545468f) - 1;
        s32 py = (s32)(v->y * 0.454545468f);
        s32 px = (s32)v->x;
        BeginGifTag(obj, 0, 1, 0xE);
        u64 key = (u64)px | ((u64)pw << 16) | ((u64)py << 32) | ((u64)pz << 48);
        AddGifRegisterWrite(obj, 0x40, key);
    }
}

void ResetFontClipRect(Font* unused, s32 flag, PacketWriter* obj)
{
    if (flag != 0) {
        BeginGifTag(obj, 0, 1, 0xE);
        AddGifRegisterWrite(obj, 0x40, 0xDF0000027F0000UL);
    }
}

f32 MeasureFontString(Font* self, s8* s)
{
    f32 acc;
    s8* p;
    if (s == 0) {
        return 0.0f;
    }
    p = s;
    acc = 0.0f;
    while (*p != 0) {
        const FontVt* n = self->vt;
        acc = acc + n->width((Font*)((u8*)self + n->adj3), (s8)(u8)*p++);
    }
    return acc;
}

f32 MeasureFontStringHeight(Font* self, u8* s)
{
    f32 a = (f32)self->height * self->sy;
    s32 n = WrapFontString(self, s);
    return a * (f32)n;
}

s32 WrapFontString(Font* self, u8* s, f32 w)
{
    s32 count = 1;
    s8* cur = (s8*)s;
    f32 acc = 0.0f;
    while (*cur != 0) {
        s32 c = (s8)(s32)*(u8*)cur;
        if (c == 10) {
            acc = 0.0f;
            count++;
        } else {
            const FontVt* t = self->vt;
            acc += t->width((Font*)((u8*)self + t->adj3), c);
        }
        if (w != 0.0f && w < acc) {
            s8* p = cur;
            while (p >= (s8*)s) {
                s8 c2 = *p;
                if (c2 == 10) {
                    break;
                }
                if (c2 == 32 || c2 == 9) {
                    cur = p;
                    acc = 0.0f;
                    *cur = 10;
                    count++;
                    break;
                }
                p--;
            }
            if (acc != 0.0f) {
                *cur = 10;
                count++;
                acc = 0.0f;
            }
        }
        cur++;
    }
    return count;
}

LINKER_REMNANT(func_0015C630);

void DrawFontString(Font *self, char *str, StringLayout *par, s32 a3, s32 a4)
{
  char *p;
  char *next;
  s32 pending = 1;
  f32 x;
  f32 y;
  self->vt->begin((Font *) (((u8 *) self) + self->vt->adj4), a3, a4);
  if (par->f18 == 0)
  {
    y = par->f4;
  }
  else
  {
    f32 sc = self->sy;
    f32 h = ((f32) self->height) * sc;
    char *q = str;
    if ((*q) != 0)
    {
      do
      {
        if ((*(q++)) == '\n')
        {
          h += ((f32) self->height) * sc;
        }
      }
      while ((*q) != 0);
    }
    if (par->f18 == 2)
    {
      y = (par->f4 + par->fC) - h;
    }
    else
    {
      y = par->f4 + ((par->fC - h) * 0.5f);
    }
  }
  for (p = str; (*p) != 0; p = next)
  {
    f32 half = 0.5f;
    s32 right = 2;
    char c = *((u8 *) p);
    next = p + 1;
    if (c == '\n')
    {
      pending = 1;
      y += ((f32) self->height) * self->sy;
    }
    else
    {
      if (pending != 0)
      {
        if (par->f14 == 0)
        {
          x = par->f0;
        }
        else
        {
          char *q;
          x = 0.0f;
          for (q = p; (*q != 0) && (*q != '\n'); q++)
          {
            x += self->vt->width((Font *) (((u8 *) self) + self->vt->adj3), *q);
          }
          if (par->f14 == right)
          {
            x = (par->f0 + par->f8) - x;
          }
          else
          {
            x = par->f0 + ((par->f8 - x) * half);
          }
        }
        pending = 0;
      }
      x += self->vt->draw(x, y, (Font *) (((u8 *) self) + self->vt->adj6), *p, par->f10, a4);
    }
  }

  self->vt->end((Font *) (((u8 *) self) + self->vt->adj7), a3, a4);
}

// Points recorded in order, the first of them scaled into u and v.
void PushFontScale(Font* trail, f32 su, f32 sv)
{
    FontScale* point = &trail->stack[trail->depth++];
    point->x = trail->sx;
    point->y = trail->sx;
    trail->sx = trail->stack[0].x * su;
    trail->sy = trail->stack[0].y * sv;
}

void PopFontScale(Font* obj) { obj->depth--; FontScale* item = &obj->stack[obj->depth]; obj->sx = item->x; obj->sy = item->y; }

Font* CloneFont(Font* owner, f32 x, f32 y)
{
	Font* out = (Font*)AllocateObjectMemory(0x88);
	out->vt = (const FontVt*)&g_fontMethods;
	CopyFont(owner, out);
	out->sx *= x;
	out->sy *= y;
	return out;
}

void CopyFont(Font* self, Font* dst)
{
    CopyFontMetrics(self, dst);
    dst->id = self->id;
    dst->imgA = self->imgA;
    dst->imgB = self->imgB;
    dst->f60 = self->f60;
    dst->f68 = self->f68;
    dst->f6C = self->f6C;
    dst->f70 = self->f70;
    dst->f74 = self->f74;
    dst->glyphCount = self->glyphCount;
    dst->glyphs = self->glyphs;
    dst->mask = self->mask;
}

s32 HasFontGlyph(Font* a, s32 b)
{
    return FindFontGlyph(a, (s8)b) != 0;
}

f32 GetFontCharWidth(Font* self, s8 key)
{
    FontGlyph* e = FindFontGlyph(self, key);
    f32 x;
    f32 y;
    if (e == 0) {
        x = self->sx;
        y = (f32)self->advance;
    } else {
        x = (f32)(e->w + 1);
        y = self->sx;
    }
    return x * y;
}

s32 AddFontImagesToFrame(Font* self, void* obj)
{
    s32 r = (g_buildFrame->flags & self->mask) == 0;
    if (r != 0) {
        CloseDmaTag(obj);
        AddDmaRefTag(obj, self->f68, self->f6C);
        AddDmaRefTag(obj, self->imgA->f14, self->imgA->f10);
        if (self->imgB != 0) {
            AddDmaRefTag(obj, self->f70, self->f74);
            AddDmaRefTag(obj, self->imgB->fC, self->imgB->f8);
        }
        BeginDmaTag(obj);
        g_buildFrame->flags |= self->mask;
    }
    return r;
}

void BeginFontDraw(Font* self, s32 a1, void* obj)
{
    SetFontClipRect(self, a1, obj);
    s32 ok = AddFontImagesToFrame(self, obj);
    BeginGifTag(obj, 6, 1, 0xE);
    if (ok != 0) {
        AddGifRegisterWrite(obj, 0x3F, 0);
    }
    s64 v = 0x31001;
    if (self->f30 != 0) {
        v = self->f38;
    }
    AddGifRegisterWrite(obj, 0x47, v);
    AddGifRegisterWrite(obj, 0x42, 0x44);
    AddGifRegisterWrite(obj, 6, self->f60);
    AddGifRegisterWrite(obj, 0x14, 0x60);
    AddGifRegisterWrite(obj, 8, 5);
    AddGifRegisterWrite(obj, 0, 0x1D6);
    BeginGifRegListTag(obj, 5, 0x43431);
}

void BeginFontGlyphPacket(Font* self, void* obj)
{
    s32 ok = AddFontImagesToFrame(self, obj);
    BeginGifTag(obj, 6, 1, 0xE);
    if (ok != 0) {
        AddGifRegisterWrite(obj, 0x3F, 0);
    }
    AddGifRegisterWrite(obj, 6, self->f60);
    AddGifRegisterWrite(obj, 0, 0x1D6);
    BeginGifRegListTag(obj, 5, 0x43431);
}

f32 DrawFontGlyph(f32 x, f32 y, Font* self, s8 key, u32 color, PacketWriter* s)
{
    FontGlyph* e = FindFontGlyph(self, key);
    if (e != 0) {
        s32 shift = (s32)((self->f60u >> 30) & 0xF);
        s32 s4 = 1 << shift;
        f32 h = (f32)self->height * self->sy;
        f32 w = (f32)e->w * self->sx;
        f32 px = x + w;
        f32 py = y + h;
        if (0.0f <= px && x <= 640.0f && 0.0f <= py && y <= 492.80002f) {
            u32 tag = (color & 0xFFFFFF) | ((((color >> 24) + 1) & 0x1FE) << 23);
            AddGifRegListFloat(s, tag, 0.0f);
            AddGifUvRegListEntry(s, e->u << 4, (s4 - e->v) << 4);
            AddGifXyzfRegListEntry(s, (s32)((x + 1728.0f) * 16.0f),
                          (s32)((y * 0.45454547f + 1936.0f) * 16.0f), self->f40, 0);
            AddGifUvRegListEntry(s, (e->u + e->w) << 4, (s4 - (e->v + self->height)) << 4);
            AddGifXyzfRegListEntry(s, (s32)((px + 1728.0f) * 16.0f),
                          (s32)((py * 0.45454547f + 1936.0f) * 16.0f), self->f40, 0);
        }
        return (f32)(e->w + 1) * self->sx;
    }
    return (f32)self->advance * self->sx;
}

void DrawFontGlyphTurned(Font* self, s8 key, u32 color, PacketWriter* s, f32 x, f32 y)
{
    FontGlyph* e = FindFontGlyph(self, key);
    if (e != 0) {
        s32 shift = (s32)((self->f60u >> 30) & 0xF);
        s32 s4 = 1 << shift;
        f32 h = (f32)self->height * self->sy;
        f32 w = (f32)e->w * self->sx;
        f32 px = x + h;
        f32 py = y + w;
        if (0.0f <= px && x <= 640.0f && 0.0f <= py && y <= 492.80002f) {
            s32 u0 = (e->u << 4) + D_00262258;
            s32 v0 = ((s4 - e->v) << 4) + D_0026225C;
            s32 u1 = ((e->u + e->w) << 4) + D_00262258;
            s32 v1 = ((s4 - (e->v + self->height)) << 4) + D_0026225C;
            s32 ok = AddFontImagesToFrame(self, s);
            BeginGifTag(s, 6, 1, 0xE);
            if (ok != 0) {
                AddGifRegisterWrite(s, 0x3F, (u64)0);
            }
            u64 v = 0x31001;
            if (self->f30 != 0) {
                v = self->f38;
            }
            AddGifRegisterWrite(s, 0x47, (u64)v);
            AddGifRegisterWrite(s, 0x42, (u64)0x44);
            AddGifRegisterWrite(s, 6, (u64)self->f60u);
            AddGifRegisterWrite(s, 0x14, (u64)0x60);
            AddGifRegisterWrite(s, 8, (u64)5);
            AddGifRegisterWrite(s, 0, (u64)0x1D4);
            BeginGifRegListTag(s, 9, 0x434343431ULL);
            u32 tag = (color & 0xFFFFFF) | ((((color >> 24) + 1) & 0x1FE) << 23);
            AddGifRegListFloat(s, tag, 0.0f);
            AddGifUvRegListEntry(s, u0, v0);
            s32 sx = (s32)((x + 1728.0f) * 16.0f);
            s32 sy = (s32)((py * 0.45454547f + 1936.0f) * 16.0f);
            AddGifXyzfRegListEntry(s, sx, sy, self->f40, 0);
            AddGifUvRegListEntry(s, u1, v0);
            s32 sy2 = (s32)((y * 0.45454547f + 1936.0f) * 16.0f);
            AddGifXyzfRegListEntry(s, sx, sy2, self->f40, 0);
            AddGifUvRegListEntry(s, u0, v1);
            s32 sx2 = (s32)((px + 1728.0f) * 16.0f);
            AddGifXyzfRegListEntry(s, sx2, sy, self->f40, 0);
            AddGifUvRegListEntry(s, u1, v1);
            AddGifXyzfRegListEntry(s, sx2, sy2, self->f40, 0);
            self->vt->end((Font*)((u8*)self + self->vt->adj7), 0, (s32)&g_gsPacketWriter);
        }
    }
}

void DrawFontQuad(Font* self, u32 color, f32 x0, f32 y0, f32 x1, f32 y1,
                   f32 u0, f32 v0, f32 u1, f32 v1, PacketWriter* s)
{
    color = (color & 0xFFFFFF) | ((((color >> 24) + 1) & 0x1FE) << 23);
    AddGifRegListFloat(s, color, 0.0f);
    AddGifUvRegListEntry(s, (s32)(u0 * 16.0f), (s32)(v0 * 16.0f));
    AddGifXyzfRegListEntry(s, (s32)((x0 + 1728.0f) * 16.0f), (s32)((y0 * 0.45454547f + 1936.0f) * 16.0f), self->f40, 0);
    AddGifUvRegListEntry(s, (s32)(u1 * 16.0f), (s32)(v1 * 16.0f));
    AddGifXyzfRegListEntry(s, (s32)((x1 + 1728.0f) * 16.0f), (s32)((y1 * 0.45454547f + 1936.0f) * 16.0f), self->f40, 0);
}

void DrawFontFrame(Font* self, FrameGlyph* item, FrameRect* r, PacketWriter* s)
{
    FontGlyph* e = FindFontGlyph(self, item->key);
    if (e != 0) {
        PushFontScale(item->f0, item->f10, item->f14);
        f32 top = r->y;
        f32 sx = self->sx;
        f32 left = r->x;
        s32 u2i = e->u + e->w;
        f32 x2 = left + r->w + item->f8 * sx;
        f32 cw = (f32)e->w * sx;
        f32 x1 = left - item->f8 * sx;
        s32 sz = 1 << (s32)((self->f60u >> 30) & 0xF);
        s32 height = self->height;
        f32 sy = self->sy;
        s32 v0i = sz - e->v;
        f32 x0 = x1 - cw;
        s32 v2i = sz - (e->v + height);
        f32 u1 = (f32)((e->u + u2i) / 2);
        f32 v1 = (f32)((v0i + v2i) / 2);
        f32 u0 = (f32)e->u;
        f32 y1 = top - item->fC * sy;
        f32 v0 = (f32)v0i;
        f32 x3 = x2 + cw;
        f32 y2 = top + r->h + item->fC * sy;
        f32 y0 = y1 - (f32)height * sy;
        f32 y3 = y2 + (f32)height * sy;
        self->vt->begin((Font*)((u8*)self + self->vt->adj4), 0, (s32)s);
        f32 v2 = (f32)v2i;
        f32 u2 = (f32)u2i;
        DrawFontQuad(self, item->color, x0, y0, x1, y1, u0, v0, u1, v1, s);
        DrawFontQuad(self, item->color, x2, y0, x3, y1, u1, v0, u2, v1, s);
        DrawFontQuad(self, item->color, x0, y2, x1, y3, u0, v1, u1, v2, s);
        DrawFontQuad(self, item->color, x2, y2, x3, y3, u1, v1, u2, v2, s);
        DrawFontQuad(self, item->color, x1, y0, x2, y1, u1, v0, u1, v1, s);
        DrawFontQuad(self, item->color, x1, y2, x2, y3, u1, v1, u1, v2, s);
        DrawFontQuad(self, item->color, x0, y1, x1, y2, u0, v1, u1, v1, s);
        DrawFontQuad(self, item->color, x2, y1, x3, y2, u1, v1, u2, v1, s);
        DrawFontQuad(self, item->color, x1, y1, x2, y2, u1, v1, u1, v1, s);
        PopFontScale(item->f0);
        self->vt->end((Font*)((u8*)self + self->vt->adj7), 0, (s32)s);
    }
}

void SetFontClipRect();
void ResetFontClipRect();
void CloneFont();
void HasFontGlyph();
void GetFontCharWidth();
void BeginFontDraw();
void BeginFontGlyphPacket();
void DrawFontGlyph();
void DrawFontGlyphTurned();
void DrawFontFrame();
void HandleAbstractCall();
extern const VtableEntry g_fontMethods[22] = {{0, 0}, {0, CloneFont}, {0, HasFontGlyph}, {0, GetFontCharWidth}, {0, BeginFontDraw}, {0, BeginFontGlyphPacket}, {0, DrawFontGlyph}, {0, ResetFontClipRect}, {0, DrawFontGlyphTurned}, {0, DrawFontFrame}, {0, 0}, {0, 0}, {0, HandleAbstractCall}, {0, HandleAbstractCall}, {0, HandleAbstractCall}, {0, SetFontClipRect}, {0, HandleAbstractCall}, {0, HandleAbstractCall}, {0, ResetFontClipRect}, {0, HandleAbstractCall}, {0, HandleAbstractCall}, {0, 0}};

void LoadFont(Font* obj, void* src)
{
    FontHeader l;
    ReadBufferedStreamBytes(src, 0x10, &l);
    s32 idx = l.b7;
    obj->id = idx;
    g_fonts[idx] = (s32)obj;
    obj->imgA = (ImageRecord*)((u8*)g_imageRecordsA + l.u0 * 32);
    void* t;
    if (l.u2 != 0xFFFF) {
        t = (u8*)g_imageRecordsB + l.u2 * 24;
    } else {
        t = 0;
    }
    obj->imgB = (PaletteRecord*)t;
    s32 n = l.uC;
    s32 A = l.b4, B = l.b5, C = l.b6; f32 F = l.f8;
    obj->f00 = A;
    obj->sx = F;
    obj->glyphCount = n;
    obj->height = C;
    obj->advance = B;
    obj->sy = F;
    obj->glyphs = (FontGlyph*)AllocateFrontMemory(n << 3);
    ReadBufferedStreamBytes(src, obj->glyphCount << 3, obj->glyphs);
}

void UploadFontImages(Font* self, void* arg)
{
    FontUploadFrame f;
    s32 n;

    (void)InitGifPacket(&f.a);
    ImageRecord* q = self->imgA;
    n = AllocateBump(arg, q->f0A);
    BuildImageTexRegister(self->imgA, n);
    self->f60u = self->imgA->f18;
    UsePacketBufferMemory(&f.a, 16, f.buf);
    StartImageUpload(self->imgA, n, &f.a);
    DetachPacketBufferCopy(&f.a, &self->f68, 0, &self->f6C, 7);
    if (self->imgB != 0) {
        n = AllocateBump(arg, self->imgB->f6);
        BuildPaletteTexRegister(self->imgB, n);
        u64 t = self->f60u;
        t |= self->imgB->f10;
        self->f60u = t;
        UsePacketBufferMemory(&f.a, 16, f.buf);
        StartPaletteUpload(self->imgB, n, &f.a);
        DetachPacketBufferCopy(&f.a, &self->f70, 0, &self->f74, 7);
    }
}

// EXACT: element address written as off + (u32)entries

FontGlyph* FindFontGlyph(Font* self, u8 key)
{
    s32 lo = 0;
    s32 hi = self->glyphCount - 1;

    if (hi >= 0) {
        do {
            s32 mid = (hi + lo) / 2;
            s32 off = mid * 8;
            FontGlyph* e = (FontGlyph*)(off + (u32)self->glyphs);
            s32 d = key - e->key;

            if (d == 0) {
                return e;
            }
            if (d > 0) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        } while (!(hi < lo));
    }
    return 0;
}

TextReader* InitTextReader(TextReader* self, s32 a1, s32 a2)
{
    self->inlineFont.vt = (const FontVt*)&g_fontMethods;
    self->text = a1;
    self->defaultFont = (Font*)a2;
    self->inlineFontColorBits = 0xFF808080;
    self->defaultColorBits = 0xFF808080;
    self->baseColorBits = 0xFF808080;
    self->colorBits = 0xFF808080;
    RewindTextReader(self);
    return self;
}

void RewindTextReader(TextReader* self)
{
    s32 t;
    self->cur = (char*)self->text;
    self->font = self->defaultFont;
    t = ((U32P*)((u8*)self + 0xA4))->v;
    ((U32P*)((u8*)self + 0xA0))->v = t;
    t = ((U32P*)((u8*)self + 0xA0))->v;
    ((U32P*)((u8*)self + 0x9C))->v = t;
    self->fontChanged = 0;
}

void SetTextDefaultColor(u8* dst, u8* src)
{
    s32 v = ((U32P*)src)->v;
    ((U32P*)(dst + 0xA4))->v = v;
    v = ((U32P*)(dst + 0xA4))->v;
    ((U32P*)(dst + 0x9C))->v = v;
}

s32 ReadTextChar(TextReader* self)
{
    s32 done = 0;
    s32 changed = 1;
    Font* inl = &self->inlineFont;
    do {
        char* p = self->cur;
        switch (*p) {
        case '~':
            if (p[1] == '~') {
                self->cur = (char*)p + 1;
                done = 1;
            } else if (p[1] == '.') {
                self->baseColor = self->defaultColor;
                self->color = self->baseColor;
                self->cur += 2;
            } else {
                char* q = p + 1;
                u32 acc = 0;
                while (*q != 0 && q - self->cur < 7) {
                    u32 ch = (u8)*q;
                    u32 d;
                    if (ch - '0' < 10)
                        d = (s8)ch - '0';
                    else if (ch - 'A' < 6)
                        d = (s8)ch - 55;
                    else if (ch - 'a' < 6)
                        d = (s8)ch - 87;
                    else
                        break;
                    q++;
                    acc = (acc << 4) + d;
                }
                if (q - self->cur >= 7) {
                    self->baseColor.r = ((acc >> 16) & 0xFF) + 1 >> 1;
                    self->baseColor.g = ((acc & 0xFF00) >> 8) + 1 >> 1;
                    self->baseColor.b = (acc & 0xFF) + 1 >> 1;
                    self->color = self->baseColor;
                    self->cur += 7;
                } else {
                    self->font = self->defaultFont;
                    self->color = self->defaultColor;
                    done = 1;
                }
            }
            break;
        case '&':
            if (p[1] == '&') {
                self->cur = (char*)p + 1;
                done = 1;
            } else if (p[1] == '.') {
                self->font = self->defaultFont;
                self->color = self->baseColor;
                self->fontChanged = changed;
                self->cur += 2;
            } else {
                Font* nf = (Font*)FindFontByKeyChar(p[1]);
                if (nf != 0) {
                    CopyFont(nf, inl);
                    self->cur += 2;
                    Font* d = self->defaultFont;
                    f32 ratio = ((f32)d->height * d->sy) / ((f32)inl->height * inl->sy);
                    self->font = inl;
                    u8 al = self->color.a;
                    self->inlineFont.sx *= ratio;
                    self->inlineFont.sy *= ratio;
                    Rgba4 t = self->inlineFontColor;
                    t.a = al;
                    self->color = t;
                    self->fontChanged = changed;
                } else {
                    self->font = self->defaultFont;
                    done = 1;
                    self->color = self->defaultColor;
                    self->fontChanged = changed;
                }
            }
            break;
        case '^':
            if (p[1] == '^') {
                self->cur = (char*)p + 1;
                done = 1;
            } else if (p[1] == '.') {
                PopFontScale(self->font);
                self->cur += 2;
            } else {
                f32 a = (f32)(p[1] - '0') + (f32)(p[2] - '0') * 0.1f;
                Font* f = self->font;
                PushFontScale(f, a * f->sx, a * f->sy);
                self->cur += 3;
            }
            break;
        default:
            done = 1;
            break;
        }
    } while (done == 0);
    char* e = self->cur;
    char r = *e;
    self->cur = e + 1;
    return r;
}

s32 CountTextChars(void* self)
{
    s32 n = 0;
    RewindTextReader(self);
    while (ReadTextChar(self) != 0) {
        n++;
    }
    return n;
}

void SeekTextReader(TextReader* self, s32 n)
{
    RewindTextReader(self);
    for (;;) {
        if (ReadTextChar(self) == 0) {
            break;
        }
        if (n == 0) {
            break;
        }
        n--;
    }
    *self->cur = 0;
}

f32 SumTextWidth(TextReader* self)
{
    f32 acc = 0.0f;
    RewindTextReader(self);
    s32 item;
    while ((item = ReadTextChar(self)) != 0) {
        Font* holder = self->font;
        const FontVt* disp = holder->vt;
        acc += disp->width((Font*)((u8*)holder + disp->adj3), item);
    }
    return acc;
}

s32 WrapTextLines(TextReader* self, f32 limit)
{
    s32 lines = 1;
    f32 width = 0.0f;
    s32 newline = 10;
    s32 space = 32;
    s32 tab = 9;
    RewindTextReader(self);
    s32 c;
    while ((c = ReadTextChar(self)) != 0) {
        if (c == newline) {
            width = 0.0f;
            lines++;
        } else {
            Font* holder = self->font;
            const FontVt* glyph = holder->vt;
            width += glyph->width((Font*)((u8*)holder + glyph->adj3), c);
        }
        if (limit != 0.0f && limit < width) {
            s8* p = (s8*)self->cur - 1;
            while (p >= (s8*)self->start) {
                if (*p == 10) {
                    break;
                }
                if (*p == space || *p == tab) {
                    width = 0.0f;
                    self->cur = (char*)p + 1;
                    lines++;
                    *p = 10;
                    break;
                }
                p--;
            }
            if (width != 0.0f) {
                *self->cur = (s8)newline;
                lines++;
                width = 0.0f;
            }
        }
    }
    return lines;
}

f32 MeasureTextHeight(TextReader* self)
{
    Font* holder = self->defaultFont;
    f32 width = (f32)holder->height * holder->sy;
    s32 lines = WrapTextLines(self);
    return width * (f32)lines;
}

f32 func_0015E1F0(TextReader* self)
{
    f32 best = 0.0f;
    s32 newline = 10;
    func_0015DB80(self);
    f32 width = best;
    s32 c;
    while ((c = func_0015DBE0(self)) != 0) {
        if (c == newline) {
            best = (width >? best);
            width = 0.0f;
        } else {
            Font* holder = self->font;
            const FontVt* glyph = holder->vt;
            width += glyph->width((Font*)((u8*)holder + glyph->adj3), c);
        }
    }
    best = (width >? best);
    return best;
}

void MeasureText(void* self, f32 f, f32* out1, f32* out2)
{
    s32 n = WrapTextLines(self, f);
    f32 g = MeasureTextWidth(self);
    TextReader* o = (TextReader*)self;
    f32 k = (f32)o->defaultFont->height * o->defaultFont->sy;
    f32 t = (f32)n * k;
    if (out1 != 0) {
        *out1 = g;
    }
    if (out2 != 0) {
        *out2 = t;
    }
}

void DrawAlignedText(TextReader* self, Layout_137228* p, s32 x, s32 y)
{
    f32 f[64];
    Rgba_137248 u;
    s32 first = 1;
    s32 n = 0;
    f32 top;
    f32 left;
    s32 c;
    FillMemory(f, 0, 0x100);
    RewindTextReader(self);
    while ((c = ReadTextChar(self)) != 0) {
        if (c == 10) {
            n++;
        } else {
            f[n] += self->font->Width(c);
        }
    }
    c = (s32)p->f18;
    if (c == 0) {
        top = p->y;
    } else {
        f32 tot = (f32)(n + 1) * ((f32)self->defaultFont->height * self->defaultFont->sy);
        if (c == 2)
            top = (p->y + p->h) - tot;
        else
            top = p->y + (p->h - tot) * 0.5f;
    }
    u = p->color;
    SetTextDefaultColor(self, &u);
    Font* started = 0;
    f32 half = 0.5f;
    RewindTextReader(self);
    f32* fp = f;
    while ((n = ReadTextChar(self)) != 0) {
        if (n == 10) {
            first = 1;
            fp++;
            top += (f32)self->defaultFont->height * self->defaultFont->sy;
            continue;
        }
        if (first) {
            if (p->f14 == 0) {
                left = p->x;
            } else {
                f32 g = *fp;
                if (p->f14 == 2)
                    left = (p->x + p->w) - g;
                else
                    left = p->x + (p->w - g) * half;
            }
            first = 0;
        }
        if (started == 0) {
            self->font->Begin(x, y);
            started = self->font;
        } else if (self->fontChanged != 0) {
            self->font->Flush(y);
            self->fontChanged = 0;
        }
        left += self->font->Draw(left, top, n, self->colorBits, y);
    }
    self->font->End(x, y);
}

void UploadAllFontImages(void)
{
    u8 buf[16];
    InitBumpAllocator(buf, 0x1400, 0x1E00);
    for (s32 i = 0; i < g_fontCount; i++) {
        UploadFontImages(g_fontRecords + i * 0x88, buf);
    }
}

LINKER_REMNANT(func_0015E678);

// A frame's colour record, as func_0015E6A8 reads it: 64-byte entries whose quadwords at +0x10
// and +0x20 hold colours as four words, a run of colour quadwords, and where the packed colours go.
struct ColorEntry_15E6A8 {
    u8 pad00[0x10];
    Quad16 c10;             // 0x10
    Quad16 c20;             // 0x20
    u8 pad30[0x40 - 0x30];
};

struct ColorOut_15E6A8 {
    u8 pad00[0x08];
    u32* out08;             // 0x08: the packed c10 of each entry
    u8 pad0C[0x14 - 0x0C];
    u32* out14;             // 0x14: the packed c20, then two words on, the packed run
};

struct ColorRecord_15E6A8 {
    ColorEntry_15E6A8* begin;   // 0x00
    ColorEntry_15E6A8* end;     // 0x04
    Quad16* run;                // 0x08: one quadword for each entry
    ColorOut_15E6A8* out;       // 0x0C
};

// A colour as four words, packed into one: each word a byte, the first lowest.
static inline u32 PackColor(Quad16 c)
{
    return c.w[0] | c.w[1] << 8 | c.w[2] << 16 | c.w[3] << 24;
}

// The interrupt handler that packs the colours of the frame's record (g_drawFrameData) and moves
// on to the next record, then lets the VIF1 go on (FBRST's STC) and ends the handler.
s32 func_0015E6A8(s32 cause)
{
    ColorRecord_15E6A8* r = (ColorRecord_15E6A8*)g_drawFrameData;
    ColorEntry_15E6A8* begin = r->begin;
    ColorEntry_15E6A8* end = r->end;
    ColorOut_15E6A8* o = r->out;
    ColorEntry_15E6A8* e;
    u32* out = o->out08;
    for (e = begin; e < end; e++) {
        *out++ = PackColor(e->c10);
    }
    out = o->out14;
    for (e = begin; e < end; e++) {
        *out++ = PackColor(e->c20);
    }
    s32 n = end - begin;
    out += 2;
    Quad16* run = ((ColorRecord_15E6A8*)g_drawFrameData)->run;
    Quad16* qend = run + n;
    for (Quad16* q = run; q < qend; q++) {
        *out++ = PackColor(*q);
    }
    g_drawFrameData += 0x10;
    *(volatile u32*)0x10003C10 = 8;
    SyncAndEnableInterrupts();
    return -1;
}

void InitRenderFrames(void)
{
    for (u32 i = 0; i < 2; i++) {
        RenderFrame* r = &g_renderFrames[i];
        r->bufA = (u8*)D_002C3B00 + i * 0x80000;
        r->bufB = D_003C3B00 + i * 0x100000;
        r->f10 = D_005C3B00 + i * 0x10600;
        SetListLinkOffset(&r->l20, 0x630);
        SetListLinkOffset(&r->l2C, 0x1090);
        SetListLinkOffset(&r->l38, 0xB8);
    }
    SetListLinkOffset(&D_002622E0, 0x630);
    SetListLinkOffset(&D_002622F0, 0x1090);
    SetListLinkOffset(&g_deferredReleaseListC, 0xB8);
    AddInterruptHandler(5, (void (*)(void))((u8*)func_0015E678 + 0x30), 0);
    EnableInterruptCause(5);
    g_frameReadySemaphore = CreateLockSemaphore(0, 2);
    g_frameDoneSemaphore = CreateLockSemaphore(2, 2);
    u32* tab = (u32*)D_002C3B00;
    s32 n = 0;
    do {
        u32 c = n;
        s32 off = n * 4;
        for (s32 k = 7; k >= 0; k--) {
            if (c & 1) c = (c >> 1) ^ 0xEDB88320;
            else c >>= 1;
        }
        *(u32*)((u8*)tab + off) = c;
        n++;
    } while (n < 256);
    RunThread(g_mainAndRenderThreads[1], 0);
}

void BeginRenderFrame(void)
{
    s32 idx;

    SetScreenOwner(3);
    AwaitSemaphore(g_frameDoneSemaphore);
    idx = g_nextBuildFrameIndex;
    g_nextBuildFrameIndex = idx + 1;
    g_buildFrame = &g_renderFrames[idx];
    if ((u32)(idx + 1) >= 2) {
        g_nextBuildFrameIndex = 0;
    }
    ReleaseFrameNodes(g_buildFrame);
    {
        RenderFrame* slot = g_buildFrame;
        s32 v = *(s32*)((u8*)g_camera + 0x21C);
        slot->flags = 0;
        slot->f44 = v;
        slot->f1C = 0;
        UsePacketBufferMemory(&g_gsPacketWriter, 0x8000, slot->bufA);
    }
    UsePacketBufferMemory(&g_vifPacketWriter, 0x10000, g_buildFrame->bufB);
    g_buildFrameData = g_buildFrame->i10;
    BeginDmaTag(&g_gsPacketWriter);
    BeginDmaTag(&g_vifPacketWriter);
}

void AddDmaRefTagIfChanged(void* list, s32 value, s32 end)
{
    if (D_0026230C != value) {
        D_0026230C = value;
        AddDmaRefTag(list, ((u32)(end - value) + 15) >> 4, value);
    }
}

void WriteGsFinishPacket(void* self, void* p, s32 n)
{
    UQuadword128 mem[8];
    PacketWriter gif;
    void* buf = &gif;
    InitGifPacket(buf);
    UsePacketBufferMemory(buf, 8, mem);
    BeginGifTag(buf, 0, 1, 0xE);
    AddGifRegisterWrite(buf, 0x61, 0);
    EndGifPacket(buf);
    WriteVifFlush(self);
    WriteVifDirectFromWriter(self, buf);
    AddDmaRefTagIfChanged(self, D_00212160, D_00215C50);
    AddDmaEndTag(self);
    DetachPacketBuffer(self, p, n);
}

void CloseDrawBuffer(void* obj, void* a, s32 b)
{
    BeginGifTag(obj, 0, 1, 0xE);
    AddGifRegisterWrite(obj, 0x61, 0);
    EndGifPacket(obj);
    AddDmaEndTag(obj);
    DetachPacketBuffer(obj, a, b);
}

void SubmitRenderFrame(void)
{
    WriteGsFinishPacket(&g_vifPacketWriter, (u8*)g_buildFrame + 8, 0);
    CloseDrawBuffer(&g_gsPacketWriter, g_buildFrame, 0);
    g_buildFrame->l20 = D_002622E0;
    ClearList(&D_002622E0);
    g_buildFrame->l2C = D_002622F0;
    ClearList(&D_002622F0);
    g_buildFrame->l38 = g_deferredReleaseListC;
    ClearList(&g_deferredReleaseListC);
    g_buildFrameData = 0;
    g_buildFrame = 0;
    PostSemaphore(g_frameReadySemaphore);
}

void ActivateRenderFrame(RenderFrame* self)
{
    g_drawFrameData = self->i10;
    SwitchActiveImageMask(self->f44);
    if (self->f1C != 0 && g_maskedImagesPacket != 0) {
        *(volatile s32*)0x10003010 = 4;
        StartDmaChain(g_gifChannel, g_maskedImagesPacket);
    }
}

void VerifyCodeChecksum(void)
{
    const u8* table = (const u8*)D_002C3B00;
    s32 n = (s32)D_00148D74;
    u32 crc = 0xFFFFFFFF;
    u32* p = (u32*)0x00100000;
    if (n > 0) {
        do {
            u32 w = *p;
            n -= 4;
            p++;
            crc = *(u32*)(table + (((crc ^ w) & 0xFF) << 2)) ^ (crc >> 8);
            crc = *(u32*)(table + (((crc ^ (w >> 8)) & 0xFF) << 2)) ^ (crc >> 8);
            crc = *(u32*)(table + (((crc ^ (w >> 16)) & 0xFF) << 2)) ^ (crc >> 8);
            crc = *(u32*)(table + (((crc ^ (w >> 24)) & 0xFF) << 2)) ^ (crc >> 8);
        } while (n > 0);
    }
    if (crc != 0) {
        g_codeChecksumFailed = 1;
    }
}

void RunRenderThread(void)
{
    VerifyCodeChecksum();
    for (;;) {
        g_renderThreadWaiting = 1;
        AwaitSemaphore(g_frameReadySemaphore);
        g_renderThreadWaiting = 0;
        g_drawingFrame = &g_renderFrames[D_00262314];
        D_00262314++;
        if (D_00262314 >= 2) {
            D_00262314 = 0;
        }
        ActivateRenderFrame((RenderFrame*)g_drawingFrame);
        ApplyPendingDisplayFlip();
        SendGsPacketAndWait(g_vif1Channel, ((RenderFrame*)g_drawingFrame)->bufBAddr);
        *(volatile s32*)0x10003010 = 0;
        SendGsPacketAndWait(g_gifChannel, ((RenderFrame*)g_drawingFrame)->bufAAddr);
        BlitFrameToDisplay();
        WaitDmaChannel(g_vif1Channel, 0, 0);
        PostSemaphore(g_frameDoneSemaphore);
        FlipDisplayFrame();
        D_002626CC = 1;
    }
}

void SendRenderFrameToDma(RenderFrame* self, s32 flag)
{
    ActivateRenderFrame(self, flag);
    SendGsPacketAndWait(g_vif1Channel, self->bufBAddr);
    if (flag != 0) {
        *(volatile s32*)0x10003010 = 0;
        SendGsPacketAndWait(g_gifChannel, self->bufAAddr);
    }
}

void ReleaseFrameNodes(RenderFrame* self)
{
    ListFrame it;
    FrameNode* n;
    if (IsListEmpty(&self->l20) == 0) {
        BeginListWalk::Of(&it, &self->l20);
        while ((n = NextInList<FrameNode>::Of(&it)) != 0) {
            RemoveFromList(&self->l20, n);
            AppendToList(n->f14 + 0x1CC0, n);
        }
        ClearList(&self->l20);
        g_activeListFrames = it.prev;
    }
    if (IsListEmpty(&self->l2C) == 0) {
        BeginListWalk::Of(&it, &self->l2C);
        while ((n = NextInList<FrameNode>::Of(&it)) != 0) {
            if (n->f1088 != 0) {
                PushFreeSlot((u8*)g_currentWorld + 0x1B4C, n->f1088);
            }
            RemoveFromList(&self->l2C, n);
            PushFreeSlot((u8*)g_currentWorld + 0x1B40, n);
        }
        ClearList(&self->l2C);
        g_activeListFrames = it.prev;
    }
    if (IsListEmpty(&self->l38) == 0) {
        BeginListWalk::Of(&it, &self->l38);
        while ((n = NextInList<FrameNode>::Of(&it)) != 0) {
            RemoveFromList(&self->l38, n);
            PushFreeSlot((u8*)g_currentWorld + 0x1BF4, n);
        }
        g_activeListFrames = it.prev;
    }
}

void DrainRenderFrames(s32 flag)
{
    for (s32 i = 0; (u32)i < 2; i++) {
        AwaitSemaphore(g_frameDoneSemaphore);
    }
    for (s32 i = 0; (u32)i < 2; i++) {
        PostSemaphore(g_frameDoneSemaphore);
    }
    while (g_renderThreadWaiting == 0) {
    }
    if (flag != 0 && g_drawingFrame != 0) {
        s32 n = 2;
        do {
            SendRenderFrameToDma(g_drawingFrame, 1);
            BlitFrameToDisplay();
            FlipDisplayFrame();
        } while (--n >= 0);
        D_002626CC = 3;
    }
    u8* p = (u8*)g_renderFrames;
    u8* end = p + 0x90;
    do {
        ReleaseFrameNodes(p);
        p += 0x48;
    } while (p < end);
    ClearScreenOwner(3);
    g_drawingFrame = 0;
}

INCLUDE_ASM(func_0015F320);

void ConstructPacketWriters(s32 flag, s32 code)
{
    if (code == 0xFFFF && flag != 0) {
        InitGifPacket(&g_gsPacketWriter);
        InitPacketWriter(&g_vifPacketWriter);
    }
}

void ResetPacketWriters(void)
{
    ConstructPacketWriters(1, 0xFFFF);
}

// The file's .data, 0x261F70 to 0x2623BC, in retail's order. The labels only func_001549C8 (not
// matched yet) and the original assembly func_00156288 use, and the two packet streams
// (globals.h), whose labels are shorter than PacketWriter, are included from the disassembly.
// size: s32 (lw/sw), 4-byte label
s32 D_00261F70 = 0;
INCLUDE_DATA(D_00261F74);
INCLUDE_DATA(D_00261F80);
INCLUDE_DATA(D_00262050);
f32 D_00262178[2] = { 0.5f, 2.0f };
PackedFloatPair D_00262180 = { 0x4348000043480000ULL };
PackedFloatPair D_00262188 = { 0x42C8000042C80000ULL };
PackedFloatPair D_00262190 = { 0x4448000043FA0000ULL };
PackedFloatPair D_00262198 = { 0x43960000C3960000ULL };
PackedFloatPair D_002621A0 = { 0x4270000041700000ULL };
PackedFloatPair D_002621A8 = { 0x42F0000041F00000ULL };
PackedFloatPair D_002621B0 = { 0x3E4CCCCD3D4CCCCDULL };
PackedFloatPair D_002621B8 = { 0x3F4CCCCD3DCCCCCDULL };
PackedFloatPair D_002621C0 = { 0x4170000040A00000ULL };
s32 g_objectCyclerLoadLinks[6] = { 0, 0x256, 0x5D0, 2, 0x259, 0x678 };
s32 g_objectCyclerStartLinks[6] = { 4, 0x258, 0x5D8, 2, 0x25A, 0x67C };
f32 D_002621F8[6] = { 7.0f, 1.0f, 0.25f, 0.0f, 0.0f, 0.0f };
f32 D_00262210[4] = { 0.0f, 0.25f, 0.000250000012f, 0.0f };
f32 D_00262220[4] = { 0.0f, 0.25f, 0.0250000004f, 0.0f };
f32 D_00262230[4] = { 1.0f, 1.5f, -2.5f, 0.0f };
f32 D_00262240[4] = { 0.0f, 2.0f, 0.0f, 0.0f };
s8 g_fontEscapeKeys[8] = "02134";
s32 D_00262258 = -8;
s32 D_0026225C = -8;
// size: s32 (lw/sw), 4-byte label
s32 g_fontCount = 0;
// size: pointer to array allocated by new Ent[D_00262260] (lw/sw), 4-byte label
u8* g_fontRecords = 0;
// size: loop bound 5, stride 4 in func_0015C200
s32 g_fonts[5] = {0};
// size: s32 (lw/sw), 4-byte label
s32 g_defaultFont = 0;
INCLUDE_DATA(D_00262280);
INCLUDE_DATA(D_002622A8);
s32 g_frameCount = 1;
// size: s32 (lw/sw), 4-byte label
s32 g_buildFrameData = 0;
// size: s32 (lw/sw), 4-byte label
s32 g_drawFrameData = 0;
// size: pointer (lw/sw), 4 bytes before an 8-aligned next label
RenderFrame* g_buildFrame = 0;
// size: 12-byte record copied into Slot r20 by func_0015EC68, 4 bytes pad before 16-aligned next label
List01 D_002622E0 = {};
// size: 12-byte record copied into Slot r2C by func_0015EC68, 4 bytes pad before 16-aligned next label
List01 D_002622F0 = {};
// size: 12-byte record copied into Slot r38 by func_0015EC68
List01 g_deferredReleaseListC = {};
s32 D_0026230C = 0;
// size: s32 (sw), 4-byte label
s32 g_codeChecksumFailed = 0;
u32 D_00262314 = 0;
// size: s32 (lw/sw), 4-byte label
s32 g_nextBuildFrameIndex = 0;
void* g_drawingFrame = 0;
// size: func_0015E810 loops 2 records of stride 0x48 (end = base + 0x90)
RenderFrame g_renderFrames[2] = {};
void* g_frameReadySemaphore = 0;
// size: pointer (lw/sw), 4-byte label
void* g_frameDoneSemaphore = 0;
volatile s32 g_renderThreadWaiting = 0;
