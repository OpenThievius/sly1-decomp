// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 561/604 (92.9%), checked 2026-11-07
// NEAR: registers only: the same instructions, with the vertex counter in s0 where retail has s1 and the triangle record in s1 where retail has s2.
#include "common.h"
#include "effect_spawner.h"
#include "vu0.h"
#include "asm_func.h"
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
#include "vu0.h"
s32 TransformPointBetweenFrames(void* from, void* to, void* point, Vec02* out);
void SetEffectSpawnerActiveForever();
void SetEffectSpawnerInactive(EffectSpawner* self);
void* GetOwnSpawnRecord(void* a0, s32 a1);
void SetSpawnRecordKind(void* self, s32 a1);
void* GetOwnedSpawnRecord(void* a0, s32 a1);
void SetSpawnRecordKind(void* self, s32 a1);
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
void CopyCollider();
s32 IsInList(void* sub, ObjectCycler* self);
void RemoveFromList(void* data, ObjectCycler* self);
void StartSoundEffect(f32 f12, f32 f13, f32 f14, f32 f15, s32 a0, void* a1, void* a2, s32 a3, f32 f16, s32 a4, s32 a5);
void StopSoundRecord(void* self, s32 n);
void StartSoundEffect(f32 f12, f32 f13, f32 f14, f32 f15, s32 a0, void* a1, void* a2, s32 a3, f32 f16, s32 a4, s32 a5);
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
struct FontUploadFrame { PacketWriter a; u8 buf[0x100]; };
PacketWriter* InitGifPacket(PacketWriter* p);
s32 AllocateBump(void* self, s32 size);
void BuildImageTexRegister(void* self, s32 v);
void UsePacketBufferMemory(void* self, s32 count, void* base);
void StartImageUpload(void* self, s32 dbp, void* ctx);
void DetachPacketBufferCopy(void* self, s32* count, u32* begin, s32* out, s32 flag);
void BuildPaletteTexRegister(void* self, s32 v);
void StartPaletteUpload(void* self, s32 v, void* ctx);
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

f32 ReadBufferedFloat(void* stream);
void ReadBufferedVector3(void* stream, Vec02* out);

// A mesh read from a stream: its vertices, its triangles (three vertex numbers and an area) and
// the vertex normals made of the triangles' normals.
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
    for (s32 i = 0; i < m->triangleCount; i++) {
        MeshTriangle* t = &m->triangles[i];
        for (s32 j = 0; j < 3; j++) {
            t->corner[j] = (s32)ReadBufferedU16(other);
        }
        t->area = ReadBufferedFloat(other);
        m->totalArea = m->totalArea + t->area;
        u128 first = Vu0::Q(m->vertices[t->corner[0]]);
        u128 e1 = Vu0::Sub(Vu0::Q(m->vertices[t->corner[1]]), first);
        u128 e2 = Vu0::Sub(Vu0::Q(m->vertices[t->corner[2]]), first);
        u128 n = Vu0::Cross(e1, e2);
        for (s32 j = 0; j < 3; j++) {
            Vec02* v = &m->normals[t->corner[j]];
            Vu0::Q(*v) = Vu0::Add(Vu0::Q(*v), n);
        }
    }
    ReadBufferedVector3(other, &m->extent);
    for (i = 0; i < m->vertexCount; i++) {
        Vu0::Q(m->normals[i]) = Vu0::NormalizeOr(Vu0::Q(m->normals[i]), Vu0::Q(g_unitZVector));
    }
}
