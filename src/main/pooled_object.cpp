// SPDX-License-Identifier: AGPL-3.0-or-later
// 0x14EE40 to 0x1533A8 (its .rodata from 0x249FE0, its .data from 0x261CC8 to 0x261F28): the
// methods of classes 0x46, 0x23, 0x65 and 0x61, the threshold tables of ScatterController and the
// display-list writer (PacketWriter, with its base vtable D_0024A0E0). Its .rodata ends with
// that vtable at 0x24A100: GCC 2.95 writes a file's vtables after all of its functions' literals
// and jump tables, so PivotActiveSet's jump table after it starts the next file
// (active_set_solver.cpp, which says why its start in the code is a choice). Its .data ends with
// the fifth DMA channel word: DrawPlacedObjectParts' matrix D_00261F30, which MultiplyMatrices
// reads with lqc2, is 16-aligned and this file's .data starts at 8 mod 16, so the matrix starts
// the next file's .data. One file between two edges otherwise; it could be several. Its name is
// ours, after its first and largest family, the pooled objects and their holder; the step
// sequence is nearly as large, and none of its families names the whole.
#include "listed_collision_part.h"
#include "common.h"
#include "gauge_manager.h"
#include "asm_func.h"
#include "pooled_object.h"
#include "masked_collider.h"
#include "world.h"
#include "screen_element.h"
#include "object_link.h"
#include "scatter_controller.h"
#include "shapes.h"
#include "list_iter.h"
#include "texture_render_object.h"
#include "step_sequence.h"
#include "animation.h"
#include "attachment.h"
#include "camera.h"
#include "flagged_object.h"
#include "packet_writer.h"
#include "globals.h"
#include "game_progress.h"
#include "threshold_range.h"
#include "pad_record.h"
#include "active_set_solver.h"
#include "buffered_stream.h"
#include "texture_header.h"
#include "range_record.h"
#include "effect_spawner.h"
#include "effect_owner.h"
#include "effect.h"
#include "deferred_request.h"
#include "cursor_animator.h"
#include "texture_table.h"
#include "owner_message.h"
#include "switched_collider.h"
#include "vu0.h"
#include "fpu.h"
#include "object_finder.h"
#include "functions/active_set_solver.h"
#include "functions/agent.h"
#include "functions/arc_element.h"
#include "functions/base_object.h"
#include "functions/buffered_stream.h"
#include "functions/camera.h"
#include "functions/camera_controller.h"
#include "functions/collider.h"
#include "functions/curve_segment.h"
#include "functions/effect_spawner.h"
#include "functions/gauge_manager.h"
#include "functions/group_marker.h"
#include "functions/main_loop.h"
#include "functions/matrix.h"
#include "functions/movie_player.h"
#include "functions/oscillator.h"
#include "functions/pad_input.h"
#include "functions/path_curve.h"
#include "functions/path_follower.h"
#include "functions/placed_object.h"
#include "functions/player.h"
#include "functions/screen_element.h"
#include "functions/sound_system.h"
#include "functions/state_notifier.h"
#include "functions/state_walker.h"
#include "functions/symmetric_solve.h"
#include "functions/text_panel.h"
#include "functions/texture_upload.h"
#include "functions/zone_collider.h"
struct BufferedStream;
struct StateNotifier;
struct Vec4;

struct StateNotifier;

struct PlacedObject;

struct BaseObject;
struct Mat3;
struct Vec4;

struct Mat3;
struct Vec4;


// Types other files define, named by the parameters of their functions declared here.
struct ScaledTransform;
struct NodeQuery;




u8* AllocateFrontMemory(s32 size);




s32 IsInList(ObjectList* self, void* item);
void RemoveFromList(ObjectList* list, void* item);
extern ObjectLink g_pooledObjectLinks[1];


extern GaugeManager* g_gaugeManager;


extern f32 g_gameClock[];




s32 AreMenusAndFadeClear(void* zero);

extern f32 g_gameTime[];

f32 RandomFloatInRange(f32 a, f32 b);




// Slot 2 of the held record's table, as func_0014FC38 calls it.
typedef void (*Held23Slot2Fn)(void* self, s32 arg);





struct ClipPoint;
struct PackedColor;
void DrawProjectedLine(ClipPoint* a, ClipPoint* b, PackedColor* c, u8* obj, s32 k);

struct CurvePoint;
void SampleCurvePoints(f32 dur, const Vec4* p0, const Vec4* m0, const Vec4* p1, const Vec4* m1, s32 count,
                       CurvePoint* out, f32 start, f32 end);









u8* AllocateFrontMemory(s32 size);
void AppendToList(ObjectList* self, void* item);








extern ObjectLink g_takerLinks[3];

void SyncPooledHolderWithPlayer(PooledHolder* self);
struct StateGraph;
void* AppendQueuedCall(World* self, void* code, void* arg, s32 c, s32 d);



extern ObjectLink g_gaugeManagerLinks[3];


extern f32 g_gameTime[];



f32 RandomFloatInRange(f32 a, f32 b);



extern f32 g_gameTime[];


void RaiseScatterLevels(ScatterController* self, f32 amount);

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table g_pathCurveKind0Methods[];
extern const Fn_Table g_pathCurveKind1Methods[];

void* AllocateZeroedFrontMemory(u32 n);

// NEAR: the calls and branches match; the store of 1 into the inner object comes before the
// float load of D_0026185C in retail, ours schedules the float load first (5 instructions).

s32 AcquirePooledObject(PooledHolder* self);
PooledObject* FindFirstAttachedPooledObject(PooledHolder* self);

// NEAR: the tail stores differ in order and register: retail does sw f6C8, then lui v1 / li v0,1 / lwc1 v1, we do lui v0 before the sw and use v0 for the address.


u32 IsListEmpty(ObjectList* p);
void SelectEarliestPooledObject(PooledHolder* self);

// NEAR: the search index is kept in a0 where retail uses a2, and hi is saved in s3 before the call in retail; the loop shape is otherwise the same.



void UpdateHeldPooledObject(PooledObject* self, f32 f);

void UpdatePooledHolderAim(PooledHolder* self, s32* state);
void ThrowHeldPooledObject(PooledHolder* self);
void SetPooledHolderWalkerState(PooledHolder* self, s32 state);

extern const f32 D_00249FB8;

s32 RandomIntInRange(s32 a, s32 b);
f32 RandomFloatInRange(f32 a, f32 b);


void func_0014DB70(void);



extern const GaugeParams g_defaultGaugeParams;
extern const f32 D_00249FB0;



// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
// Defined in src/main/path_curve.cpp.
extern const Fn_Table g_pathCurveKind0Methods[14];
extern const Fn_Table g_pathCurveKind1Methods[14];


void SetWorldActiveFollower(World* self, void* v);




extern f32 g_gameClock[];
extern const GaugeParams g_defaultGaugeParams;


PooledObject* FindEarliestPooledChild(PlacedObject* self);




void ReadSequenceSteps(void* unused, BufferedStream* rd, s32* outCount, SequenceStep** outArr);

void* GetIndexedTargetSlot(void* self, s32 index);


extern u8 g_elementStack[];
void PushStackElement(ElementStack* self, ScreenElement* node);


// The caption box as func_00150790 clears its child (CaptionBox::child, +0x324): an unaligned
// store (swl/swr), so a packed view.
struct __attribute__((packed)) CaptionBoxPacked { u8 pad0[0x324]; void* child; };

void SetStepSequenceState(StepSequence* self, s32 arg);

extern void* GetLevelEntryByKey(s32 key);
extern void* GetIndexedTargetSlot(void* self, s32 index);

extern "C" void* FillMemory(void* p, s32 value, s32 size);

f32 ClampToRange(ValueRange* span, f32 x);
void SetScatterLevel(ScatterController* object, f32 unused);
f32 ClampToRange(ValueRange* span, f32 x);

extern f32 ClampToRange(ValueRange* span, f32 x);

// An item's link in a list (ObjectList::offset bytes into it): the next and the previous item.
struct ListLink { void* next; void* prev; };

void PrependToList(ObjectList*, u32);

extern "C" s32 ResetDmaController(s32 mode);
extern void ResetGsPaths();
struct DmaChannel;
extern "C" u32 GetDmaChannel(u32 index);
extern u32 g_vif0Channel, g_vif1Channel, g_gifChannel, g_fromSprChannel, g_toSprChannel;

u8* ReservePermanentMemory(s32 size);

extern u8* AllocateBackMemory(s32 size);

void CloseDmaTag(PacketWriter* self);

void CloseDmaTag(PacketWriter* self);
u32 CopyToFrontMemory(s32 size, void* src);

extern "C" void SyncDataCache(s32 unused);
struct DmaChannel;
extern "C" void StartDmaChain(DmaChannel* ch, void* tadr);

void CopyQuadwords(void* dst, void* src, s32 n);

void CloseDmaTag(PacketWriter* self);

struct SequenceMessage;
void HandleStepSequenceMessage(StepSequence* self, SequenceMessage* msg);
s32 TestStepWaitConditions(StepSequence* self);
void SkipRemainingSteps(StepSequence* self);


extern "C" void* FillMemory(void* p, s32 value, s32 size);


ListLink* GetListLinks(void* a, void* b);

extern "C" void* FillMemory(void* p, s32 value, s32 size);
void SetListLinkOffset(ObjectList* self, s32 offset);


extern s32 g_resumeSoundSetupDone;
void SetStepSequenceState(StepSequence* self, s32 mode);

ListLink* GetListLinks(ObjectList* node, u32 value);
void ClearList(ObjectList* node);


extern s32 D_00275B00;
void SetSpareCount(s32 value);
f32 ClampToRange(ValueRange* span, f32 x);
void SetScatterLevel(void*, f32);

// An entry of a GCC 2.95 vtable as this file defines D_0024A0E0 (packet_writer.h).
#include "vtable_entry.h"
void SkipDisplayListWriterSlot();
void ClearPacketBuffer(PacketWriter* p);


extern s32 g_controlBlockingElementCount;
extern f32 g_gameTime[];

void ReleasePadSelectFlag(World* self);
void AcquirePadSelectFlag(World* a0);

void RemoveFromList(ObjectList* list, void* item);
void AppendToList(ObjectList* self, void* item);
extern f32 D_BC23D70A;


void ClearList(ObjectList* p);
void AppendToList(ObjectList* self, void* item);


void* AllocateZeroedFrontMemory(s32 n);

extern u8 g_elementStack[];
void ShowCountedScreenElement(World* self);
void HideCountedScreenElement(World* self);
void PopStackElement(ElementStack* g);

extern s32 g_resumeSoundSetupDone;
extern s32 D_00270B30;
extern s32 D_002717A8;
extern u8 g_elementStack[];

void SetStepSequenceState(StepSequence* self, s32 mode);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
StepSequenceHost* GetActiveSwitchedCollider(void);
void ChooseStepSequenceState(StepSequence* self);
void ShowStepSequenceText(StepSequence* value, StepSequenceHost* object);
void SkipRemainingSteps(StepSequence* self);
void PopStackElement(ElementStack* g);
void RunStepSequence(StepSequence* self);


extern s32 g_padRouting;
extern u16 g_stepWaitButtonMasks[16];
extern u8 g_stepWaitButtonGlyphs[16];




void RemoveFromList(ObjectList* list, void* item);
void AppendToList(ObjectList* self, void* item);

// The object a caption is spoken by (kind 0x104, found by id by func_00150DC0): its colour
// becomes the caption box's highlight, its state walker (+0x334) is sent key 0x34C.
struct StateWalker;
struct CaptionSpeaker { u8 pad0[0x2D0]; Rgba4 color; u8 pad1[0x334 - 0x2D4]; StateWalker* walker; };
// A word of a step sequence's message, read as an id or a time.
struct KeyRecord;
union MessageWord { s32 i; f32 f; KeyRecord* key; void* p; };

// The message HandleStepSequenceMessage takes.
struct SequenceMessage {
    u32 type;
    MessageWord f4, f8;
    s32 fC, f10;
    s8* text;
    s32 f18, f1C, f20, f24;
};

extern u8 g_moviePlayer[];

extern "C" u32 GetStringLength(const char* s);
struct MoviePlayer;
void ShowCountedScreenElement(World* self);
void HideCountedScreenElement(World* self);


s32 RandomIntInRange(s32 lo, s32 hi);
f32 ClampToRange(ValueRange* span, f32 x);

// Draws a count between two bounds by the level (g_currentEntry->dt), rounding toward the second.
struct LevelLerp
{
    static s32 Get(s32 lo, s32 hi)
    {
        f32 s = g_currentEntry->dt;
        if (lo == hi) return hi;
        if (lo < hi) return lo + (s32)(s * ((f32)hi + 0.999f - (f32)lo));
        return hi + (s32)((1.0f - s) * ((f32)lo + 0.999f - (f32)hi));
    }
};


void* InitGifPacket(PacketWriter* p);
void* InitPacketWriter(PacketWriter* p);
void PushBackMemoryMark(void);
void AllocateTempPacketBuffer(PacketWriter* buffer, u32 count);
void WriteVifFlushE(PacketWriter* p);
void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRgbaEntry(PacketWriter* self, u32 value);
void AddGifXyzEntry(PacketWriter* p, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);
void EndGifPacket(PacketWriter* p);
void WriteVifDirectFromWriter(PacketWriter* p, PacketWriter* q);
void WriteVifBaseOffset(PacketWriter* s, u32 a, u32 b);
void CopyWordsToWriter(PacketWriter* s, s32 a1, s32 size, u32* src, s32 a4);
void ClearPacketBuffer(PacketWriter* p);
void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);
void ReserveGifPackedData(PacketWriter* self, u64 prim, s32 nloop, s32 nreg, u64 data, u8** out);
void DetachPacketBufferCopy(PacketWriter* self, s32* count, u32* begin, s32* out, s32 flags);
void PopBackMemoryMark(void);
void AddGifUvEntry(PacketWriter* p, s32 a, s32 b);
void WriteVifFlush(PacketWriter* p);





extern ScatterTable g_scatterTablesPlain[2];
extern ScatterTable g_scatterTableFlagged;
extern ScatterTable g_scatterTableEarlyGame;
s32 RandomIntInRange(s32 a, s32 b);




void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void CopyMemory(void* dst, void* src, s32 size);
void AppendToList(ObjectList* self, void* item);
// Initialises the collider and puts the state at -1 (none).
void InitPooledObject(PooledObject* self)
{
    InitCollider(self);
    SetPooledObjectState(self, -1);
}

// Takes the object out of the world's queue (list at 0x1C78), registers it as a collider, and sets
// a flag in its flags, in a different bit when its parent is of kind 0x3A.
void RemoveFromWorldQueue(PooledObject* self)
{
    RegisterCollider(self);
    if (IsInList(&self->world->list1C78, self)) RemoveFromList(&self->world->list1C78, self);
    if (self->parent != 0 && IsObjectOfKind(self->parent, 0x3A) != 0) {
        self->flags538 |= (u64)0x8000 << 28;
    } else {
        self->flags538 &= ~((u64)1 << 43);
    }
}

// Removes the object from its parent list, appends it to the world's queue (0x1C78) and sets state
// 0.
void AddToWorldQueue(PooledObject* self)
{
    RemoveObjectFromParentList(self);
    AppendToList(&self->world->list1C78, self);
    SetPooledObjectState(self, 0);
}

// Copies the collider part from other but keeps this object's own record at 0x56C.
void CopyPooledObject(PooledObject* self, Collider* other)
{
    PooledKeptPair save = self->keep56C;
    CopyCollider(self, other);
    self->keep56C = save;
}

// Loads the collider, then finds or builds the member group at 0x58C.
void LoadPooledObject(PooledObject* self, BufferedStream* stream)
{
    LoadCollider(self, stream);
    FindOrBuildMemberGroup(&self->member58C, self);
}

// Passes the notification on; when kind 6 is about the object it watches, forgets it and goes to
// state 4.
void HandlePooledObjectNotification(PooledObject* self, s32 kind, void* msg)
{
    HandlePlacedObjectNotification(self, kind, msg);
    if (kind == 6) {
        if (msg == self->watched) {
            self->watched = 0;
            SetPooledObjectState(self, 4);
        }
    }
}

// Starts the placed object and resolves its links through the pooled object's link table.
void StartPooledObject(PooledObject* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 1, g_pooledObjectLinks);
}

// Per-frame update: collider update, then by state. State 2 (held) updates as a held object; state
// 4 moves to 5 after the delay once the player no longer holds its parent.
void UpdatePooledObject(PooledObject* self, f32 f)
{
    UpdateCollider(self, f);
    switch (self->state) {
    case 0:
    case 1:
    case 3:
    case 5:
        break;
    case 2:
        UpdateHeldPooledObject(self, f);
        break;
    case 4:
        if (self->delay < g_gameTime[0] - self->stateTime) {
            if (g_player == 0 || self->parent != (BaseObject*)g_player->heldObject)
                SetPooledObjectState(self, 5);
        }
        break;
    }
}

// Changes the state (no-op when equal), stamps stateTime with the game time and, on leaving state
// 2, clears the held-object fields. State 5 starts the fade-out.
void SetPooledObjectState(PooledObject* self, s32 state)
{
    if (self->state != state) {
        if (self->state != 2) {
            self->state = state;
        } else {
            self->f57C = 0;
            self->f580 = 0;
            self->f584 = 0;
            self->taker = 0;
            self->state = state;
        }
        self->stateTime = g_gameTime[0];
        if (state == 5) {
            (void)FadeOutPlacedObject(self, self->fadeOutTime);
        }
    }
}

extern f32 g_launchHorizontalSpeed;
extern f32 g_launchLiftSpeed;

// The owner-message callback of a pooled object's launch: gives the other object, through its
// slot 36, the pooled object's horizontal direction (its velocity with z cleared, unit length,
// or X when it has none) times D_00261CD4 plus D_00261CD8 upward; a kind-7 object is put in
// state 0x2B.
// As ApplyChildGroupKnockback: the unit vector is stored through a pointer as a structure and
// the weights are read as the floats themselves, so the first weight's load does not wait for
// that store in sched2 (docs/toolchain/sched1.md, "Why the arms' stores cannot be written
// plainly").
void LaunchObjectFromPooledObject(PlacedObject* self, PlacedObject* other)
{
    Vec4 d = self->v150;
    d.z = 0.0f;
    Vec4* p = &d;
    Vec4 r;
    *(Vu0::Vec*)p = Vu0::NormalizeOr(Vu0::Vec::Of(d), Vu0::Vec::Of(g_unitXVector));
    const PlacedObjectDescriptor* desc = other->desc02();
    Vu0::Q(r) = Vu0::MulXSum(Vu0::Q(d), Vu0::ScalarAtValue(g_launchHorizontalSpeed), Vu0::Q(g_unitZVector), Vu0::ScalarAtValue(g_launchLiftSpeed));
    desc->m20(other, &r);
    if (IsObjectOfKind(other, 7) != 0) {
        SetPlayerState((Player*)other, 4, 0x2B);
    }
}

s32 CountHeldPooledChildren(PlacedObject* self);
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec4* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

// The query FindNodeForQuery takes for an object that touched a held one (func_0014F270).
struct HeldTouchQuery {
    PooledObject* self;     // 0x00
    Collider* other;        // 0x04
    u8 pad08[0x20 - 0x08];
    Vec4 pos;              // 0x20
    Vec4 vel;              // 0x30

    void Clear() { FillMemory(this, 0, (s32)sizeof(*this)); }
};

// What a group member's slot 0x7C is told when a held object lands (func_0014F270).
struct HeldLandEvent {
    s32 kind;               // 0x00: 4
    u8 pad04[0x20 - 0x04];
    Vec4 pos;              // 0x20
};

typedef void (*ObjFn)(void* self);
typedef void (*ObjPtrFn)(void* self, void* a);

// Per-frame update of a held pooled object: finds the part it touches and reacts. When it is the
// player (and not in state 6 with target mode 2) it asks the player to take the object; when it is
// another pooled holder (class 0x3A) it plays a sound, rumbles the pad, and frees the earliest
// child if the holder is full.
void UpdateHeldPooledObject(PooledObject* self, f32 dt)
{
    typedef Vu0::Vec Vec;
    Collider* c = (Collider*)FindContactingPart(self);
    if (c != 0) {
        s32 lands = 1;
        if (c == (Collider*)g_player && (g_player->state != 6 || g_player->targetMode != 2)) {
            OwnerMessage m;
            InitOwnerMessage(&m, 0, self);
            m.fn = (void (*)())LaunchObjectFromPooledObject;
            ((s32 (*)(void*, void*))((void**)g_player->desc)[0x140 / 4])(g_player, &m);
        } else if (IsObjectOfKind(c, 0x3A)) {
            StartSoundEffect(0x34, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            if (g_player != 0 && g_player->heldObject == c) {
                StartPadRecordPattern(&g_padRecord, 4, 0.25f);
            }
            if (!(CountHeldPooledChildren(c) < ((ListedCollisionPart*)c)->heldLimit)) {
                PooledObject* e = FindEarliestPooledChild((PooledObject*)c);
                if (e != 0) {
                    SetPooledObjectState(e, 5);
                }
            }
            ((ObjPtrFn)((void**)self->desc)[0x64 / 4])(self, c);
            ((ObjPtrFn)((void**)self->desc)[0x90 / 4])(self, (void*)&g_zeroVector);
            ((ObjPtrFn)((void**)self->desc)[0x94 / 4])(self, (void*)&g_zeroVector);
            SetColliderAnchors(self, 3, 0, 3, 0);
            SetPooledObjectState(self, 4);
            if (self->watchedAnimation != 0) {
                CreateAnimationPlayerWithoutPresetTargets((Animation*)self->watchedAnimation, self, 0, (AnimationPlayer**)&self->watched, 0.0f, 1.0f);
                if (self->watched != 0) {
                    SetPooledObjectState(self, 3);
                }
            }
            lands = 0;
        } else if (IsObjectOfKind(c, 0x46)) {
            switch (((PooledObject*)c)->state) {
            case 0:
            case 1:
            case 2:
                break;
            case 3:
            case 4:
            case 5:
                lands = 0;
                ((ObjPtrFn)((void**)c->desc)[0x64 / 4])(c, 0);
                ((ObjFn)((void**)c->desc)[0x1C / 4])(c);
                break;
            }
        } else {
            HeldTouchQuery q;
            q.Clear();
            q.other = c;
            q.pos = self->v140;
            q.vel = self->v150;
            q.self = self;
            FindNodeForQuery((NodeQuery*)&q, 0, 0);
        }
        if (lands) {
            StartSoundEffect(0x33, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            void* g = self->member58C;
            if (g != 0) {
                HeldLandEvent ev;
                ev.kind = 4;
                ev.pos = self->v140;
                ((ObjPtrFn)((void**)*(void**)g)[0x7C / 4])(g, &ev);
            } else {
                SendPointEventToWorldListener((Quad16*)&self->v140, self->landEventValue);
            }
            ((ObjPtrFn)((void**)self->desc)[0x64 / 4])(self, 0);
            ((ObjFn)((void**)self->desc)[0x1C / 4])(self);
        }
        return;
    }
    if (g_player != 0 && g_player->state == 4) {
        return;
    }
    Vec4 at;
    Vec4 dir;
    Mat3 basis;
    at = self->holder->v140;
    at.z = at.z + self->holdHeight;
    f32 t = Vu0::Distance(at, self->v140) / self->holdSpeed;
    f32 lo = 0.0f;
    f32 hi = 0.25f;
    if (t < lo) {
        t = lo;
    } else if (hi < t) {
        t = hi;
    }
    ComputeObjectFrameAtTime(self->holder, 0, &at, 0, 0, 0, t);
    at.z = at.z + self->holdHeight;
    u128 k = Vu0::ScalarAt(self->holdSpeed);
    Vu0::Set(dir, Vu0::MulX(Vu0::NormalizeOr(Vu0::Sub(Vec::Of(at), Vec::Of(self->v140)), Vec::Of(g_zeroVector)).q, k));
    ((ObjPtrFn)((void**)self->desc)[0x90 / 4])(self, &dir);
    BuildBasisFromX(&dir, &basis);
    ((ObjPtrFn)((void**)self->desc)[0x88 / 4])(self, &basis);
}

// Initialises the player-flagged collider and puts the template id at -1.
void InitPooledHolder(PooledHolder* self)
{
    InitPlayerFlaggedCollider(self);
    self->templateId = -1;
}

// Notification handler of the holder: after the placed object's handling, when the holder's state
// walker (message kind 0x14) reaches key 0x2B7 it destroys the walker if the holder holds
// something, otherwise resets its aim attachment and the two poses.
void HandlePooledHolderNotification(PooledHolder* self, s32 kind, void* msg)
{
    s32 result;

    HandlePlacedObjectNotification(self, kind, msg);
    if (kind == 0x14) {
        if (msg == self->walker) {
            GetStateWalkerTargetKey((StateWalker*)msg, &result);
            if (result == 0x2B7) {
                if (self->hold != 0) {
                    DestroyStateWalker((StateWalker*)self->walker);
                    self->walker = 0;
                } else {
                    ((HeldAimAttachment*)self->p734->aimAttachment)->f4C = 1;
                    ((HeldAimAttachment*)self->p734->aimAttachment)->aimAtTarget = 0;
                    self->p734->desc02()->m1D(self->p734, &self->p734->v190);
                    self->p734->desc02()->m1E(self->p734, &self->p734->m1A0);
                    self->p738->desc02()->m1E(self->p738, &self->p738->m1A0);
                }
            }
        }
    }
}

// After loading, resolves each stored id in items748 to an object and adds those of kind 0x41 to
// the holder's list of items (items76C).
void PostLoadPooledHolder(PooledHolder* self)
{
    s32 i = 0;
    PostLoadPlacedObject(self);
    if (self->count744 > 0) {
        do {
            void* p = FindFirstObjectByIdMode4(self->world, self->items748[i], self);
            if (p != 0) {
                if (IsObjectOfKind((BaseObject*)p, 0x41) != 0) {
                    s32 n = self->count768;
                    self->items76C[n] = p;
                    self->count768 = n + 1;
                }
            }
            i++;
        } while (i < self->count744);
    }
}

// Copies the player's rig object into the holder's throw target, if there is a player.
void SyncPooledHolderWithPlayer(PooledHolder* self)
{
    if (g_player != 0) {
        self->throwTarget = (s32)g_player->rigObject;
    }
}

// Start of a pooled holder: starts the collider, resolves its links, then takes the template object
// (looked up by templateId), saves its pose and parent and makes copies of it, up to cnt in all,
// which are started too.
void StartPooledHolder(PooledHolder* self)
{
    StartMaskedCollider(self);
    ResolveObjectLinks(self, 3, g_takerLinks);
    ((HeldAimAttachment*)self->p734->aimAttachment)->f4C = 1;
    PlacedObject* s2 = (PlacedObject*)FindFirstObjectByIdMode1(self->world, self->templateId, self);
    *(Quad16*)&self->savedPose[0] = *(Quad16*)&s2->v190;
    *(Quad16*)&self->savedPose[1] = *(Quad16*)&s2->m1A0.r[0];
    *(Quad16*)&self->savedPose[2] = *(Quad16*)&s2->m1A0.r[1];
    *(Quad16*)&self->savedPose[3] = *(Quad16*)&s2->m1A0.r[2];
    self->savedParent = s2->parent;
    s32 i = 1;
    if (i < self->cnt) {
        do {
            BaseObject* e = (BaseObject*)CreateObjectCopy(s2, s2->world, 0);
            if (e->desc->m0F != 0) {
                e->desc->m0F(e);
            }
            i++;
            e->desc->m10(e);
            e->desc->m03(e);
        } while (i < self->cnt);
    }
    s2->desc->m15(s2, 0);
    s2->desc->m03(s2);
    AppendQueuedCall(self->world, (void*)(void (*)(void*))SyncPooledHolderWithPlayer, self, 0, 0);
    self->walker = CreateStateWalker((StateGraph*)self->stateGraph, self, 0x2B7, 1);
}

// Per-frame update of a pooled holder: updates the collider and, when it holds nothing and has a
// throw target and state walker, moves the walker between its states (0x2B7 to 0x2BB) by whether it
// has an object, collected ones and an aim.
void UpdatePooledHolder(PooledHolder* self, f32 dt)
{
    s32 st[2];
    UpdateMaskedCollider(self, dt);
    if (self->hold == 0 && self->throwTarget != 0 && self->walker != 0) {
        GetStateWalkerCurrentKey((StateWalker*)self->walker, &st[0]);
        GetStateWalkerTargetKey((StateWalker*)self->walker, &st[1]);
        if (st[1] == -1) st[1] = st[0];
        if (st[0] == st[1]) {
            switch (st[0]) {
            case 0x2B7:
                if (self->f7B0 != 0) st[1] = 0x2B8;
                else if (self->collectedCount > 0) st[1] = 0x2B9;
                break;
            case 0x2B8:
                if (self->f7B0 == 0) {
                    if (self->collectedCount > 0) st[1] = 0x2B9;
                    else st[1] = 0x2B7;
                } else {
                    UpdatePooledHolderAim(self, &st[1]);
                }
                break;
            case 0x2B9:
                if (self->f7B0 != 0) st[1] = 0x2B8;
                else if (self->collectedCount <= 0) st[1] = 0x2B7;
                else UpdatePooledHolderAim(self, &st[1]);
                break;
            case 0x2BA:
                ThrowHeldPooledObject(self);
                st[1] = 0x2B8;
                break;
            case 0x2BB:
                ThrowHeldPooledObject(self);
                st[1] = 0x2B9;
                break;
            }
            if (st[1] != st[0]) SetPooledHolderWalkerState(self, st[1]);
        }
    }
}

// A kind 0x46 object the holder has taken always may contact; anything else uses the collider test.
s32 TestPooledHolderMayContact(PooledHolder* self, Collider* obj)
{
    if (IsObjectOfKind(obj, 0x46) != 0) {
        if (((PooledObject*)obj)->taker == self) {
            return 1;
        }
    }
    return TestCollidersMayContact(self, obj);
}

// Lets go of the held object (two of its methods are called), sends the state walker to 0x2B7 and
// destroys it once it gets there, and calls slot 2 of the aim attachment with 7.
void ReleasePooledHolder(PooledHolder* self)
{
    s32 status;

    if (self->heldObject != 0) {
        self->heldObject->desc->m15(self->heldObject, 0);
        self->heldObject->desc->m03(self->heldObject);
    }
    if (self->walker != 0) {
        TeleportStateWalker((StateWalker*)self->walker, 0x2B7);
        GetStateWalkerCurrentKey((StateWalker*)self->walker, &status);
        if (status == 0x2B7) {
            DestroyStateWalker((StateWalker*)self->walker);
            self->walker = 0;
        }
    }
    {
        HeldAimAttachment* o = (HeldAimAttachment*)self->p734->aimAttachment;
        ((Held23Slot2Fn)o->vtbl[2])(o, 7);
    }
    HandleMaskedColliderActivation(self);
}

// Asks the holder's state walker to move to state code unless it is already there (or heading
// there). Leaving 0x2B7 clears a field of the aim attachment; codes 0x2B8 and 0x2B9 set its aim
// flag.
void SetPooledHolderWalkerState(PooledHolder* self, s32 code)
{
    s32 r;

    GetStateWalkerTargetKey((StateWalker*)self->walker, &r);
    if (r == -1) {
        GetStateWalkerCurrentKey((StateWalker*)self->walker, &r);
    }
    if (code == r) {
        return;
    }
    if (r == 0x2B7) {
        ((HeldAimAttachment*)self->p734->aimAttachment)->f4C = 0;
    }
    if (code < 0x2BA) {
        if (code >= 0x2B8) {
            ((HeldAimAttachment*)self->p734->aimAttachment)->aimAtTarget = (code == 0x2B9);
            if (!((u32)(r - 0x2BA) < 2)) {
                self->acquireTime = 0;
            }
        }
    }
    SetStateWalkerTarget((StateWalker*)self->walker, code);
}

// Per-frame aim and take step of the holder: in state 0x2B8 it takes a pooled object once the
// acquire delay (seconds) has passed and moves to 0x2BA; otherwise it picks an attached target,
// points its aim attachment at it and, after the delay, takes an object and moves to 0x2BB.
void UpdatePooledHolderAim(PooledHolder* self, s32* state)
{
    if (*state == 0x2B8) {
        ((HeldAimAttachment*)self->p734->aimAttachment)->aimAtTarget = 0;
        if (self->acquireDelay < g_gameTime[0] - self->acquireTime) {
            if (AcquirePooledObject(self)) {
                *state = 0x2BA;
            }
        }
        return;
    }
    if (self->targetObject == 0 || IsObjectAttached(self->targetObject) == 0
        || self->targetObject->state == 3 || self->targetObject->state == 4) {
        self->targetObject = FindFirstAttachedPooledObject(self);
    }
    if (self->targetObject == 0) {
        return;
    }
    AssignAimTarget((AimAttachment*)self->p734->aimAttachment, self->targetObject, (Vec4*)&g_zeroVector);
    if (self->acquireDelay < g_gameTime[0] - self->acquireTime) {
        if (AcquirePooledObject(self)) {
            *state = 0x2BB;
        }
    }
}

// Takes the first object from the world's free pooled-object list for the holder: it is placed at
// the holder's saved pose with zero velocity and made held (state 1). Returns 1 when the holder has
// one already or now, 0 when none is free.
s32 AcquirePooledObject(PooledHolder* self) {
    PooledObject* s0;

    if (self->heldObject != 0) {
        return 1;
    }
    if (self->reservedObject != 0) {
        if (self->reservedObject->state != 5) {
            self->reservedObject = 0;
        }
    }
    if (IsListEmpty(&self->world->list1C78) != 0 || self->reservedObject != 0) {
        SelectEarliestPooledObject(self);
        return 0;
    }
    s0 = (PooledObject*)self->world->list1C78.head;
    s0->taker = self;
    s0->desc->m02(s0);
    s0->desc->m15(s0, self->savedParent);
    SetColliderAnchors(s0, 3, 0, 3, 0);
    s0->desc03()->m1D(s0, &self->savedPose[0]);
    s0->desc03()->m1E(s0, (Mat3*)&self->savedPose[1]);
    s0->desc03()->m20(s0, (Vec4*)&g_zeroVector);
    s0->desc03()->m21(s0, (Vec4*)&g_zeroVector);
    SetPooledObjectState(s0, 1);
    self->heldObject = s0;
    self->acquireTime = g_gameTime[0];
    return 1;
}

#define OBJV ((PooledView*)obj)
struct PooledView { u8 pad00[0x558]; f32 throwSpeed; f32 throwEventRadius; u8 pad560[0x580 - 0x560]; f32 flightTime; f32 throwHeight; };
void SetPooledObjectState(PooledObject* self, s32 state);

// Throws the object the holder holds: the speed and source are those of the aim target (speed 15)
// if it has one that is still attached, otherwise the holder's own; it works out the direction and
// the velocity, hands the object to it, sets its throw speed and flight time and sends the holder's
// script event.
void ThrowHeldPooledObject(PooledHolder* self)
{
    Vec4 pos;
    Vec4 d;
    Vec4 dir;
    Vec4 step;
    Vec4 vel;
    Mat3 basis;
    PooledObject* obj;
    void* args[1];
    PlacedObject* source;
    f32 speed;
    if (self->targetObject != 0 && ((HeldAimAttachment*)self->p734->aimAttachment)->aimAtTarget != 0) {
        if (IsObjectAttached(self->targetObject) == 0 || self->targetObject->state == 3 || self->targetObject->state == 4) {
            self->targetObject = 0;
            return;
        }
        speed = 15.0f;
        source = self->targetObject;
    } else {
        source = (PlacedObject*)self->throwTarget;
        speed = self->defaultThrowSpeed;
    }
    obj = (PooledObject*)self->heldObject;
    self->targetObject = 0;
    self->heldObject = 0;
    obj->desc->m15(obj, 0);
    SetColliderAnchors(obj, 0, 0, 0, 0);
    if (obj->baseAttachment != 0) {
        typedef void (*AttachedFn)(void* self, s32 arg);
        void* att = obj->baseAttachment;
        (*(AttachedFn**)att)[2](att, 7);
    }
    pos = source->v140;
    pos.z += speed;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(obj->v140));
    BuildBasisFromX(&d, &basis);
    obj->desc02()->m1E(obj, &basis);
    f32 len = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(d)));
    OBJV->flightTime = len / OBJV->throwSpeed;
    TransformDirectionBetweenFrames(source->root, 0, &source->root->v150, &dir);
    Vu0::Q(step) = Vu0::MulX(Vu0::Q(dir), Vu0::ScalarAt(OBJV->flightTime));
    Vu0::Q(pos) = Vu0::Add(Vu0::Q(pos), Vu0::Q(step));
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(obj->v140));
    f32 len2 = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(d)));
    OBJV->flightTime = len2 / OBJV->throwSpeed;
    Vu0::Q(d) = Vu0::DivX(Vu0::Q(d), Vu0::Length(Vu0::Q(d)));
    Vu0::Q(vel) = Vu0::MulX(Vu0::Q(d), Vu0::ScalarAt(OBJV->throwSpeed));
    obj->desc02()->m20(obj, &vel);
    SetPooledObjectState(obj, 2);
    obj->f57C = (s32)source;
    OBJV->throwHeight = speed;
    SendPointEventToWorldListener((Quad16*)&obj->v140, OBJV->throwEventRadius);
    args[0] = &obj;
    TriggerScriptEvent(self, 0xD, 1, args);
}

// Unless an object is already reserved, picks the pooled child in the part list with the earliest
// stateTime, puts it in state 5 and keeps it as the holder's reservedObject.
void SelectEarliestPooledObject(PooledHolder* self)
{
	ListFrame frame;
	if (self->reservedObject != 0) return;
	PooledObject* current = (PooledObject*)g_partList.head;
	PooledObject* best = 0;
	f32 minimum = 3.4028235e+38f;
	while (current != 0) {
		PooledObject* candidate = FindEarliestPooledChild(current);
		current = current->next;

		if (candidate != 0 && candidate->stateTime < minimum) { best = candidate; minimum = candidate->stateTime; }
	}
	if (best != 0) { SetPooledObjectState(best, 5); self->reservedObject = best; }
}

// Gives the first collected pooled object that is attached and not in state 3 or 4, or null.
PooledObject* FindFirstAttachedPooledObject(PooledHolder* state)
{
	for (s32 i = 0; i < state->collectedCount; ++i) {
		PooledObject* item = (PooledObject*)state->collected[i];
		if (IsObjectAttached(item) == 0) continue;
		if (item->state == 3) continue;
		if (item->state == 4) continue;
		return item;
	}
	return 0;
}

// Appends an item id to the holder's list (at most 8).
void AddPooledHolderItem(PooledHolder* self, s32 item)
{
    u32 n = (u32)self->count744;
    if (n < 8) {
        self->items748[n] = item;
        self->count744 = n + 1;
    }
}

// Empties the collected array and clears the flag at 0x7B0.
void ResetCollectedItems(PooledHolder* self)
{
    self->collectedCount = 0;
    self->f7B0 = 0;
}

// Called with an item the holder touched: kind 7 sets the holder's flag at 0x7B0, and a kind 0x41
// item that is one of its own listed items is added to the collected array (at most 8).
void RecordCollectedItem(PooledHolder* self, void* event)
{
    if (IsObjectOfKind((BaseObject*)event, 7)) {
        self->f7B0 = 1;
        return;
    }
    if (!IsObjectOfKind((BaseObject*)event, 0x41)) {
        return;
    }
    s32 found = 0;
    for (s32 i = 0; i < self->count768; i++) {
        if (self->items76C[i] == event) {
            found = 1;
            break;
        }
    }
    if (found) {
        u32 count = self->collectedCount;
        if (count < 8) {
            self->collected[count] = event;
            self->collectedCount = count + 1;
        }
    }
}

// Initialises the placed object, sets a flag and puts both target ids at -1 (unset).
void InitStepSequence(StepSequence* state)
{
	InitPlacedObject(state);
	state->flags |= ((u64)0x8000u << 17);
	state->second300 = -1;
	state->first30C = -1;
}

// Loads the placed object, then the step records into count and steps.
void LoadStepSequence(StepSequence* self, BufferedStream* arg)
{
    LoadPlacedObject(self, arg);
    ReadSequenceSteps(self, arg, &self->count2DC, (SequenceStep**)&self->steps2E0);
}

// Reads a step sequence's steps from the stream: a count byte, then per step (0x28 bytes) a type
// byte and the fields that type has (key blocks, 16-bit ids, floats).
void ReadSequenceSteps(void* unused, BufferedStream* rd, s32* outCount, SequenceStep** outArr)
{
    s32 i = 0;
    *outCount = ReadBufferedS8(rd);
    *outArr = (SequenceStep*)AllocateZeroedFrontMemory(*outCount * 0x28);
    for (i = 0; i < *outCount; i++) {
        SequenceStep* e = (SequenceStep*)((u8*)*outArr + i * 0x28);
        e->type = ReadBufferedS8(rd);
        switch (e->type) {
        case 0:
        case 7:
            ReadOptionalBufferedBlock(rd, (u8**)&e->w4);
            break;
        case 1:
        case 2:
            e->w4 = ReadBufferedS16(rd);
            e->w8 = ReadBufferedS16(rd);
            break;
        case 3:
            *(f32*)&e->w4 = ReadBufferedFloat(rd);
            *(f32*)&e->w8 = ReadBufferedFloat(rd);
            e->wC = ReadBufferedU8(rd);
            e->w10 = ReadBufferedU8(rd);
            e->w18 = ReadBufferedS16(rd);
            e->w1C = ReadBufferedS16(rd);
            e->w20 = ReadBufferedS16(rd);
            e->w24 = ReadBufferedS16(rd);
            ReadBufferedString(rd, (u8**)e->w14);
            break;
        case 4:
            e->w4 = ReadBufferedS16(rd);
            break;
        }
    }
}

// Starts the placed object; resolves the sequence's target slot (its own id if none was set) from
// the current entry, falling back to the stored default.
void StartStepSequence(StepSequence* self)
{
    StartPlacedObject(self);
    if (self->first30C == -1) {
        self->first30C = self->id;
    }
    void* v = GetIndexedTargetSlot(g_currentEntry, self->first30C);
    self->target304 = v;
    if (!v) {
        self->target304 = self->fallback308;
    }
}

void SetStepSequenceModeOne(StepSequence* self)
{
    self->mode2D0 = 1;
}

void SetStepSequenceCameraMode(StepSequence* self)
{
    self->mode2D0 = 2;
}

// Reads the word the sequence's target points at.
void ReadSequenceTarget(StepSequence* self, s32* out)
{
    *out = *(s32*)self->target304;
}

// Writes a word through the sequence's target pointer.
void WriteSequenceTarget(StepSequence* self, s32 value)
{
    *(s32*)self->target304 = value;
}

// Moves the step sequence to a new state, first undoing what the old one set up (the hint glyph's
// owner for 5, the count of waiting sequences for 1, the voice and target flag for 3), then setting
// up the new state.
void SetStepSequenceState(StepSequence* self, s32 next)
{
    s32 cur = self->state2D4;
    if (next == cur) {
        return;
    }
    switch (cur) {
    case 5:
        if (g_hintGlyphElement.owner == self) {
            g_hintGlyphElement.owner = 0;
        }
        break;
    case 1:
        if (self->mode2D0 != cur) {
            g_controlBlockingElementCount = g_controlBlockingElementCount - 1;
        }
        break;
    case 3:
        *(s32*)self->target304 = 1;
        StopStreamVoice();
        TriggerScriptEvent(self, 0x15, 0, 0);
        if (self->mode2D0 == 2) {
            RemoveCameraControllers(g_camera, 0xF, 6, &g_camera->ctl460, 0, 0);
            ReleasePadSelectFlag(g_currentWorld);
        }
        (void)PopStackValue(&g_camera->ctl460);
        if ((self->waitFlags & 0x10) != 0 && self->player2F8 != 0) {
            StopAnimationPlayer(self->player2F8);
        }
        if (self->mode2D0 == 2 && self->dimsVolume != 0) {
            f32 f = 1.0f;
            SetVolumeChannelFactor(9, 0, f);
            SetVolumeChannelFactor(9, 1, f);
        }
        break;
    case 4:
        ((CaptionBoxPacked*)&g_typedTextCaptionBox)->child = 0;
        SetTextPanelState(&g_typedTextCaptionBox, 0);
        break;
    }
    switch (next) {
    case 5:
        if (g_hintGlyphElement.owner != 0) {
            SetStepSequenceState(g_hintGlyphElement.owner, 0);
        }
        g_hintGlyphElement.owner = self;
        self->state2D4 = next;
        break;
    case 1:
        if (self->mode2D0 != next) {
            g_controlBlockingElementCount = g_controlBlockingElementCount + 1;
        }
        self->state2D4 = next;
        break;
    case 3:
        self->step2E4 = -1;
        self->waitFlags = 0;
        if (self->mode2D0 == 2) {
            PushStackValue(&g_camera->ctl460, 4);
            PushCameraController(g_camera, 6, &g_camera->ctl460, 0, 0);
            AcquirePadSelectFlag(g_currentWorld);
            SetTextPanelSubject(&g_typedTextCaptionBox, 0);
            if (self->dimsVolume != 0) {
                f32 f = 0.6f;
                SetVolumeChannelFactor(9, 0, f);
                SetVolumeChannelFactor(9, 1, f);
            }
        } else {
            PushStackValue(&g_camera->ctl460, 3);
            if (self->mode2D0 == 0) {
                if (self->second300 != -1) {
                    g_camera->ctl460.anchorObject = FindFirstObjectByIdMode4(self->world, self->second300, 0);
                } else {
                    g_camera->ctl460.anchorObject = 0;
                }
            }
        }
        self->state2D4 = next;
        break;
    case 4:
        SetArcTarget(&g_leftArcElement, 0);
        SetArcSpecialObject(&g_leftArcElement, 0);
        SetArcTarget(&g_rightArcElement, 0);
        SetArcSpecialObject(&g_rightArcElement, 0);
        self->state2D4 = next;
        break;
    default:
        self->state2D4 = next;
        break;
    }
    self->time2D8 = g_gameTime[0];
}

// Per-frame update of a step sequence: updates the placed object, drops back to state 0 when a
// caption, the timer or a voice is in the way, then (looks like) checks the active controller's
// buttons for a skip, tests the wait conditions, advances the steps and sets the next state.
void UpdateStepSequence(StepSequence* self, f32 dt)
{
    s32 q[2];
    s32 s1;
    StepSequenceHost* s2;

    UpdatePlacedObject(self, dt);
    if (!(g_timerCaption.state < 2 && g_timerCaption.pressed == 0 && IsStreamVoiceLocked() == 0 && g_resumeSoundSetupDone != 1)) {
        s32 st = self->state2D4;
        switch (st) {
        case 1:
        case 5:
        case 6:
            SetStepSequenceState(self, 0);
            return;
        }
    }
    FillMemory(q, 0, 8);
    s2 = GetActiveSwitchedCollider();
    if (IsTopCameraController(&g_camera->ctl454) != 0) {
        q[1] = 0;
        q[0] = 0;
    } else if (s2 != 0) {
        s2->vt->f154(s2, self, q);
    } else {
        q[1] = 1;
    }
    s1 = self->state2D4;
    switch (s1) {
    case 0:
        if (self->startPending != 0) {
            if (g_resumeSoundSetupDone == 0 && q[1] != 0) {
                self->startPending = 0;
                ChooseStepSequenceState(self);
                s1 = self->state2D4;
            }
        }
        break;
    case 5:
        if (q[0] == 0) {
            s1 = 6;
            break;
        }
        goto timer;
    case 6:
        if (q[0] != 0) {
            s1 = 5;
            break;
        }
        goto timer;
    case 1:
        if (q[1] != 0) {
            StepSequence* o = g_activeStepSequence;
            if (o == 0) {
                ShowStepSequenceText(self, s2);
                s1 = self->state2D4;
            } else if (o != self) {
                if (o->otherSkipBlocked == 0 && o->state2D4 == 3) {
                    SkipRemainingSteps(o);
                }
            }
            break;
        }
    timer:
        if (g_gameTime[0] - self->time2D8 >= 5.0f) s1 = 0;
        break;
    case 3:
        if (self->mode2D0 != 2) {
            if (!(self->step2E4 < self->count2DC) || g_resumeSoundSetupDone == 1) {
                PopStackElement((ElementStack*)g_elementStack);
                s1 = self->state2D4;
            }
        }
        break;
    case 4:
        if (D_00270B30 == 0) {
            if (D_002717A8 == 0) s1 = 0;
        }
        break;
    }
    SetStepSequenceState(self, s1);
    switch (self->state2D4) {
    case 0:
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
        break;
    case 3:
        RunStepSequence(self);
        break;
    }
}

// Handles one message of a step sequence (a scripted run of steps that shows captions, plays
// voice lines and starts movies), by the message's type. self->waitFlags collects the things the
// sequence must wait for before its next step (probably cleared as each finishes elsewhere).
//  0: opens the key record in the message and waits for it (flag 0x01).
//  1, 2: look up up to two caption speaker objects by id (type 0x104, -1 means none; searched
//     under the sequence's root or itself), send the first speaker's state walker to state 0x34C,
//     and set the speaker as the target and the second as the special object of the left (1,
//     arc D_002708E0, stored in p2F0, wait 0x02) or right (2, arc D_00271558, p2F4, wait 0x04) arc.
//  3: a caption step. Picks which stored speaker the id in the message names and fades that
//     speaker's arc in and the other out; finds an animation (type 2 by id, wait 0x10, or else
//     type 1 id 0x54A of the speaker) and starts it on the speaker as a player (player2F8) with a
//     record callback; if the message has text, sets it in the typed-text caption box, coloured
//     with the speaker's colour (grey 0x80808080 if none), with a typing speed of (length + 10)
//     over the duration (the animation's length or the message's time; 15 chars/s if no duration)
//     (wait 0x20); sets the panel's value percent if given (wait 0x40); sets a time deadline
//     (wait 0x80) and a subject object; sets the camera's anchor object from the message or the
//     sequence's own default (second300); waits for a key if asked (wait 0x100); always waits 0x08.
//  4: triggers script event 0x10 with the message's payload; 5, 6: show and hide the world's
//     counted screen element; 7: queues a movie on the movie player.
void HandleStepSequenceMessage(StepSequence* self, SequenceMessage* msg)
{
    CaptionSpeaker* s2;
    CaptionSpeaker* s4;
    s32 a2;
    BaseObject* a0;
    f32 f20;
    s8* nm;
    switch (msg->type) {
    case 0:
        OpenKeyRecord(msg->f4.key);
        self->waitFlags |= 1;
        break;
    case 1:
    case 2:
        if (msg->f4.i != -1) {
            s2 = (CaptionSpeaker*)FindFirstObjectById(self->world, 0x104, msg->f4.i, self->root ? self->root : self);
        } else {
            s2 = 0;
        }
        if (msg->f8.i != -1) {
            s4 = (CaptionSpeaker*)FindFirstObjectById(self->world, 0x104, msg->f8.i, self->root ? self->root : self);
        } else {
            s4 = 0;
        }
        if (s2 && s2->walker) {
            SetStateWalkerTarget(s2->walker, 0x34C);
        }
        switch (msg->type) {
        case 1:
            SetArcTarget(&g_leftArcElement, s2);
            SetArcSpecialObject(&g_leftArcElement, s4);
            self->p2F0 = s2;
            if (s2) {
                self->waitFlags |= 2;
            }
            break;
        case 2:
            SetArcTarget(&g_rightArcElement, s2);
            SetArcSpecialObject(&g_rightArcElement, s4);
            self->p2F4 = s2;
            if (s2) {
                self->waitFlags |= 4;
            }
            break;
        default:
            return;
        }
        break;
    case 3:
        if (self->p2F0 && MatchesObjectId((BaseObject*)self->p2F0, msg->f18)) {
            s2 = (CaptionSpeaker*)self->p2F0;
            SetArcFade(&g_leftArcElement, 1);
            SetArcFade(&g_rightArcElement, 0);
        } else if (self->p2F4 && MatchesObjectId((BaseObject*)self->p2F4, msg->f18)) {
            s2 = (CaptionSpeaker*)self->p2F4;
            SetArcFade(&g_rightArcElement, 1);
            SetArcFade(&g_leftArcElement, 0);
        } else {
            s2 = 0;
        }
        a2 = msg->f1C;
        a0 = 0;
        if (a2 != -1) {
            a0 = FindFirstObjectById(self->world, 2, a2, self);
            self->waitFlags |= 0x10;
        } else {
            if (s2) {
                a0 = FindFirstObjectById(self->world, 1, 0x54A, s2);
            }
        }
        if (a0) {
            CreateAnimationPlayerWithoutPresetTargets((Animation*)a0, (BaseObject*)s2, 1, &self->player2F8, 0.0f, 1.0f);
            AddAnimationPlayerRecordCallback(self->player2F8, (PlacedObject**)self);
        }
        nm = msg->text;
        if (nm && *nm) {
            g_typedTextCaptionBox.vt->m08(&g_typedTextCaptionBox, (const char*)nm);
            if (s2) {
                *(Rgba4*)&g_typedTextCaptionBox.highlight = s2->color;
            } else {
                g_typedTextCaptionBox.highlight = 0x80808080;
            }
            if (self->player2F8) {
                if (msg->f1C == -1) {
                    f20 = msg->f8.f;
                } else {
                    f20 = self->player2F8->anim->length;
                }
            } else {
                f20 = msg->f8.f;
            }
            if (0.0f < f20) {
                CaptionBox* h2 = &g_typedTextCaptionBox;
                h2->charsPerSecond = (f32)(GetStringLength((const char*)msg->text) + 10) / f20;
            } else {
                CaptionBox* h3 = &g_typedTextCaptionBox;
                h3->charsPerSecond = 15.0f;
            }
            self->waitFlags |= 0x20;
        }
        if (msg->f4.f >= 0.0f) {
            SetTextPanelValuePercent(&g_typedTextCaptionBox, msg->f4.f + 1.0f);
            self->waitFlags |= 0x40;
        }
        if (msg->f8.f >= 0.0f) {
            self->waitFlags |= 0x80;
            self->waitDeadline = g_gameTime[0] + msg->f8.f;
        }
        if (msg->f20 != -1) {
            BaseObject* r = FindFirstObjectById(self->world, 0x104, msg->f20, self->root ? self->root : self);
            SetTextPanelSubject(&g_typedTextCaptionBox, r);
        }
        if (msg->f24 != -1) {
            g_camera->ctl460.anchorObject = FindFirstObjectByIdMode4(self->world, msg->f24, 0);
        } else if (self->second300 != -1) {
            g_camera->ctl460.anchorObject = FindFirstObjectByIdMode4(self->world, self->second300, 0);
        } else {
            g_camera->ctl460.anchorObject = 0;
        }
        if (msg->fC) {
            self->waitFlags |= 0x100;
            self->waitKey = msg->f10;
        }
        self->waitFlags |= 8;
        break;
    case 4: {
        void* tmp = &msg->f4;
        TriggerScriptEvent(self, 0x10, 1, &tmp);
        break;
    }
    case 5:
        ShowCountedScreenElement(self->world);
        break;
    case 6:
        HideCountedScreenElement(self->world);
        break;
    case 7:
        QueueMovie((MoviePlayer*)g_moviePlayer, msg->f4.p);
        break;
    }
}


// Passes the notification on and forgets the animation player when kind 6 reports it gone.
void HandleStepSequenceNotification(StepSequence* state, s32 mode, void* value)
{
	HandlePlacedObjectNotification(state, mode, value);
	if (mode == 6 && value == state->player2F8)
		state->player2F8 = 0;
}

// Tests what a step sequence is waiting for, as bits of waitFlags: 1 for a streamed voice still
// pending, 2 and 4 for the two speakers' lines to finish, 8 for a voice stream that exists, and so
// on. Returns whether any condition is still unmet (non-zero), clearing the bits that are met.
s32 TestStepWaitConditions(StepSequence* self)
{
    s32 flags = self->waitFlags;
    if (flags & 2) {
        SequenceStep* e = self->step2E4 < self->count2DC - 1 ? &((SequenceStep*)self->steps2E0)[self->step2E4 + 1] : 0;
        if (e != 0 && e->type == 2) {
            if (flags == 2) return 0;
        }
        if (g_leftArcElement.target == self->p2F0 && g_leftArcElement.phase == 1) flags &= 0xFFFFFFFD;
    }
    if (flags & 4) {
        SequenceStep* e = self->step2E4 < self->count2DC - 1 ? &((SequenceStep*)self->steps2E0)[self->step2E4 + 1] : 0;
        if (e != 0 && e->type == 1 && flags == 4) return 0;
        if (g_rightArcElement.target == self->p2F4 && g_rightArcElement.phase == 1) flags &= 0xFFFFFFFB;
    }
    if (flags & 1) {
        if (CheckStreamVoicePending() == 0) flags &= 0xFFFFFFFE;
    }
    if (flags & 8) {
        if (HasStreamVoice() == 0) flags &= 0xFFFFFFF7;
    }
    if (flags & 0x10) {
        if (self->player2F8 == 0) flags &= 0xFFFFFFEF;
    }
    if (flags & 0x20) {
        if (IsTextPanelTextTyped(&g_typedTextCaptionBox) != 0) flags &= 0xFFFFFFDF;
    }
    if (flags & 0x40) {
        if (g_camera->ctl460.zoomFraction == g_typedTextCaptionBox.value) flags &= 0xFFFFFFBF;
    }
    if (flags & 0x80) {
        if (self->waitDeadline <= g_gameTime[0]) flags &= 0xFFFFFF7F;
    }
    g_typedTextCaptionBox.buttonGlyph = 0;
    if (flags == 0x100) {
        s32 r;
        PadRecord* in = (g_padRouting & 4) ? &g_padRecord : &g_blankPadRecord;
        s32 k = self->waitKey;
        r = 0;
        switch (k) {
        case 9:
            if (0.8f < in->stickMagnitude) r = 1;
            break;
        case 10:
            if (0.8f < in->secondStickMagnitude) r = 1;
            break;
        case 11:
            if (0.8f < __builtin_fabsf(in->stickX)) r = 1;
            break;
        case 12:
            if (0.8f < __builtin_fabsf(in->stickY)) r = 1;
            break;
        case 13:
            if (g_player != 0 && g_player->state == 2) r = g_player->subState == 3;
            break;
        case 14:
        {
            G27C230* fl = g_currentEntry;
            u32 t = fl->bits & 4;
            r = t != 0;
        }
            break;
        default:
            r = (in->flags & g_stepWaitButtonMasks[k]) != 0;
            break;
        }
        if (r != 0) {
            flags = 0;
        } else {
            g_typedTextCaptionBox.buttonGlyph = g_stepWaitButtonGlyphs[k];
        }
    }
    self->waitFlags = flags;
    return flags != 0;
}

// Skips to the end of the sequence: runs the side effects of every remaining step that has one
// (script event 0x10 for type 4, showing or hiding the counted screen element for 5 and 6) without
// playing the captions.
void SkipRemainingSteps(StepSequence* self)
{
    if (self->state2D4 != 4) {
        if (self->step2E4 < self->count2DC) {
            for (self->step2E4++; self->step2E4 < self->count2DC; self->step2E4++) {
                SequenceStep* it = &((SequenceStep*)self->steps2E0)[self->step2E4];
                switch (it->type) {
                case 0: case 1: case 2: case 3: case 7:
                    break;
                case 4: {
                    s32* p = &it->w4;
                    TriggerScriptEvent(self, 0x10, 1, &p);
                    break;
                }
                case 5:
                    ShowCountedScreenElement(self->world);
                    break;
                case 6:
                    HideCountedScreenElement(self->world);
                    break;
                }
            }
        }
        if (self->mode2D0 == 2)
            PopStackElement((ElementStack*)g_elementStack);
    }
}

// Runs the sequence's steps in order: while the current step's wait condition is over, stops its
// animation player, advances and starts the next; past the last step the rest are skipped.
void RunStepSequence(StepSequence* self)
{
    s32 index;

    if (self->step2E4 < self->count2DC) {
        for (;;) {
            if (TestStepWaitConditions(self) != 0) {
                return;
            }
            if (self->player2F8 != 0) {
                StopAnimationPlayer(self->player2F8);
                self->player2F8 = 0;
            }
            index = self->step2E4 + 1;
            self->step2E4 = index;
            if (!(index < self->count2DC)) {
                break;
            }
            HandleStepSequenceMessage(self, (SequenceMessage*)((u8*)self->steps2E0 + index * 0x28));
        }
        SkipRemainingSteps(self);
    }
}

// Shows the text step: through the given object's method if there is one, else by pushing the
// typed-text caption box on the element stack.
void ShowStepSequenceText(StepSequence* value, StepSequenceHost* object)
{
    if (object != 0) {
        object->vt->f158(object, value);
    } else {
        g_typedTextCaptionBox.child = value;
        PushStackElement((ElementStack*)g_elementStack, &g_typedTextCaptionBox);
    }
}

// Chooses the state a step sequence starts in when it is triggered: nothing happens when a caption
// is open, the timer is pressed, a voice is locked or it is the active sequence; otherwise state 1,
// or 5 when its target (or one of the extra targets) has been reached, or its current state in mode
// 2.
void ChooseStepSequenceState(StepSequence* self)
{
    SprintCaption* g = &g_timerCaption;
    if (g->state >= 2 || g->pressed != 0)
        return;
    if (IsStreamVoiceLocked() != 0)
        return;
    if (g_resumeSoundSetupDone == 1)
        return;
    if (self == g_activeStepSequence)
        return;
    s32 mode = 1;
    if (*(s32*)self->target304 != 0) {
        mode = (self->mode2D0 == 2) ? self->state2D4 : 5;
    } else {
        s32 n = self->extraTargetCount;
        if (n > 0) {
            for (s32 i = 0; i < n; i++) {
                if (*(s32*)self->extraTargets[i] != 0) {
                    mode = 5;
                    break;
                }
            }
        }
    }
    SetStepSequenceState(self, mode);
}

// Sets the sequence's state to 0 unless it is in state 1 or 3.
void ResetStepSequence(StepSequence* self)
{
    if (self->state2D4 != 1 && self->state2D4 != 3) {
        SetStepSequenceState(self, 0);
    }
}

// Looks up the level entry for key and its indexed target slot of kind, and appends it to the
// sequence's list of extra targets (at most 4).
void AddSequenceExtraTarget(StepSequence* collection, s32 key, u32 kind)
{
	if ((u32)collection->extraTargetCount >= 4) return;
	void* item = GetLevelEntryByKey(key);
	if (!item) return;
	void* value = GetIndexedTargetSlot(item, kind);
	if (!value) return;
	u32 count = collection->extraTargetCount;
	collection->extraTargets[count] = value;
	collection->extraTargetCount = count + 1;
}

void* GetScatterController(void)
{
    return &g_scatterController;
}

// Zeroes the controller's 0x24 bytes.
void ClearScatterController(void* state)
{
	FillMemory(state, 0, 0x24);
}

// Resets the scatter controller for a new level: refill and count ranges to defaults, the table
// chosen by the save data's level (an early-game table, or a plain or flagged one by the current
// entry's flags), the scatter level from the entry's progress value, and the starting counts
// interpolated between the table's start and end values.
void ResetScatterController(ScatterController* self)
{
    self->refillLo = 4;
    self->refillHi = 6;
    self->countLo = 1;
    self->countHi = 3;
    GameProgress* g = g_saveData;
    if (g->levelIndex == 0 || g->levelIndex == 5 || g->entryIndex == 1) self->table = &g_scatterTableEarlyGame;
    else if (!(g_currentEntry->flags & 2)) self->table = g_scatterTablesPlain;
    else self->table = &g_scatterTableFlagged;
    SetScatterLevel(self, g_currentEntry->dt);
    s32 a = ((ScatterTable*)self->table)->countLoStart;
    s32 b = ((ScatterTable*)self->table)->countLoEnd;
    f32 t = g_currentEntry->dt;
    s32 ra;
    if (a == b) ra = b;
    else if (a < b) ra = a + (s32)(t * ((f32)b + 0.99900001f - (f32)a));
    else ra = b + (s32)((1.0f - t) * ((f32)a + 0.99900001f - (f32)b));
    s32 c = ((ScatterTable*)self->table)->countHiStart;
    s32 d = ((ScatterTable*)self->table)->countHiEnd;
    t = g_currentEntry->dt;
    s32 rc;
    if (c == d) rc = d;
    else if (c < d) rc = c + (s32)(t * ((f32)d + 0.99900001f - (f32)c));
    else rc = d + (s32)((1.0f - t) * ((f32)c + 0.99900001f - (f32)d));
    s32 r = RandomIntInRange(ra, rc);
    s32 i = 0;
    ThresholdRange* e = 0;
    self->countdown = r;
    for (; i < ((ScatterTable*)self->table)->count; i++) {
        e = &((ScatterTable*)self->table)->ranges[i];
        if (e->threshold <= g_currentEntry->f10) break;
    }
    self->bandCountdown = RandomIntInRange(e->low, e->high);
    self->spareRaised = 0;
}

// Keeps the scatter level in step with the save: when the flag in D_00275B00 bit 3 is set, raises
// the spare count to the table's value for the band the entry is in; otherwise sets the scatter
// level from the entry's progress value through the table's range, and completes the sound
// notifiers.
void UpdateScatterLevelLimits(ScatterController* self)
{
    if (D_00275B00 & 8) {
                if (((ScatterTable*)self->table)->bandStart1 <= g_currentEntry->dt && g_currentEntry->dt < ((ScatterTable*)self->table)->bandStart2) {
            if (g_saveData->spareCount < ((ScatterTable*)self->table)->spareCount1) {
                SetSpareCount(((ScatterTable*)self->table)->spareCount1);
                self->spareRaised = 1;
            }
        } else if (((ScatterTable*)self->table)->bandStart2 <= g_currentEntry->dt) {
            if (g_saveData->spareCount < ((ScatterTable*)self->table)->spareCount2) {
                SetSpareCount(((ScatterTable*)self->table)->spareCount2);
                self->spareRaised = 1;
            }
        }
    } else {
        f32 v = ClampToRange((ValueRange*)((u8*)((ScatterTable*)self->table)->levelRange), g_currentEntry->dt);
        SetScatterLevel(self, v);
    }
    CompleteSoundNotifiers(g_currentWorld);
}

void NotifyScatterControllerLoaded(void* self)
{
}

// Raises the scatter level by amount scaled by the controller table's rate, and the second level of
// the current entry by amount times a rate that depends on the save's reserve count, clamped to
// 0..1.
void RaiseScatterLevels(ScatterController* self, f32 amount)
{
    f32 x = g_currentEntry->dt + amount * ((ScatterTable*)self->table)->levelScale;
    SetScatterLevel(self, x);
    s32 index = g_saveData->reserveCount;
    f32 y;
    if (index < 0) {
        y = ((ScatterTable*)self->table)->f40;
    } else {
        y = ((ScatterTable*)self->table)->f3C;
        if (index <= ((ScatterTable*)self->table)->f4C) {
            y += ((ScatterTable*)self->table)->f50;
        }
    }
    f32 result = ((f32 (*)(void*, f32))ClampToRange)(&g_unitRange, g_currentEntry->f10 + amount * y);
    g_currentEntry->f10 = result;
}

// Raises the scatter level for picking up an object: by the table's "seen" amount when the object's
// ordinal bit is already set in the entry's bits, else by the "new" amount, then sets that bit.
void RaiseScatterLevelForObject(ScatterController* obj, FlaggedObject* node)
{
    f32 value;
    if (node != 0) {
        s32 idx = node->ordinal;
        s32 bit = 1 << (idx & 7);
        if (g_currentEntry->bits74[idx / 8] & bit) {
            value = ((ScatterTable*)obj->table)->raiseSeen;
            goto have;
        }
    }
    value = ((ScatterTable*)obj->table)->raiseNew;
have:
    SetScatterLevel(obj, g_currentEntry->dt + value);
    if (node != 0) {
        G27C230* m = g_currentEntry;
        s32 idx = node->ordinal;
        s32 bit = 1 << (idx & 7);
        u8 cur = m->bits74[idx / 8];
        if (cur & bit) return;
        m->bits74[idx / 8] = cur | bit;
        m->count70 = m->count70 + 1;
    }
}

// Sets the scatter level to 0 and clears the current entry's second level, its count and its bit at
// 0x74.
void ResetScatterLevels(ScatterController* object)
{
	SetScatterLevel(object, 0.0f);
	G27C230* manager = g_currentEntry;
	manager->f10 = 0.0f;
	manager->count70 = 0;
	FillMemory(manager->bits74, 0, 1);
}

// Scatters n pooled objects around a point: with n above 0 it spreads them around a circle (class
// 0x58). With a negative n it lowers the controller's level by a band step once the countdowns run
// out, and moves the thresholds as the level crosses the table's ranges.
void ScatterObjectsAtPoint(ScatterController* self, void* p, s32 n, s32 flag)
{
    s32 did = 0;
    if ((g_currentWorld)->scatterCountEnabled != 0 && n != 0) {
        if (!flag) {
            self->bandCountdown--;
            self->countdown--;
        }
        if (n > 0) {
            ScatterObjectsAroundCircle(g_currentWorld, 0x58, (Vec4*)p, n, 0);
        } else {
            if (self->bandCountdown < 0) {
                if (g_currentEntry->f10 != 0.0f) {
                    did = 1;
                    g_currentEntry->f10 = ClampToRange(&g_unitRange, g_currentEntry->f10 + ((ScatterTable*)self->table)->bandLevelStep);
                }
                s32 i = 0;
                ThresholdRange* r = 0;
                while (i < ((ScatterTable*)self->table)->count) {
                    r = &((ScatterTable*)self->table)->ranges[i];
                    if (g_currentEntry->f10 >= r->threshold) break;
                    i++;
                }
                self->bandCountdown = RandomIntInRange(r->low, r->high);
            }
            if (!flag) {
                for (s32 i = 0; i < ((ScatterTable*)self->table)->count - 1; i++) {
                    if (((ScatterTable*)self->table)->ranges[i].threshold <= g_currentEntry->f10) {
                        s32 v = RandomIntInRange(((ScatterTable*)self->table)->ranges[i].low, ((ScatterTable*)self->table)->ranges[i].high);
                        self->bandCountdown = (self->bandCountdown < v) ? self->bandCountdown : v;
                        goto done;
                    }
                }
            done:;
            }
            if (did) {
                ScatterObjectsAroundCircle(g_currentWorld, 0x57, (Vec4*)p, 1, 0);
            } else {
                s32 a, b;
                if (self->countdown < 0) {
                    a = self->refillLo;
                    b = self->refillHi;
                    self->countdown = RandomIntInRange(LevelLerp::Get(((ScatterTable*)self->table)->countLoStart, ((ScatterTable*)self->table)->countLoEnd), LevelLerp::Get(((ScatterTable*)self->table)->countHiStart, ((ScatterTable*)self->table)->countHiEnd));
                } else {
                    a = self->countLo;
                    b = self->countHi;
                }
                n = RandomIntInRange(a, b);
                if (n) ScatterObjectsAroundCircle(g_currentWorld, 0x58, (Vec4*)p, n, 0);
            }
        }
    }
    if (!flag) {
        g_currentEntry->f10 = ClampToRange(&g_unitRange, g_currentEntry->f10 + ((ScatterTable*)self->table)->levelStep);
    }
}

// Stores the clamped level in the current entry's first level.
void SetScatterLevel(ScatterController* object, f32 unused)
{
	f32 value = ((f32 (*)(void*))ClampToRange)(object->table);
	g_currentEntry->dt = value;
}

void SetListLinkOffset(ObjectList* self, s32 offset)
{
    self->offset = offset;
}

// Empties the list (head and tail cleared).
void ClearList(ObjectList* p)
{
	p->tail = 0;
	p->head = 0;
}

// Clears an item's next and previous links.
void ClearListLinks(ListLink* p)
{
	p->prev = 0;
	p->next = 0;
}

ListLink* GetListLinks(ObjectList* p, void* item)
{
	return (ListLink*)((u8*)item + p->offset);
}

// Puts item at the tail of the list.
void AppendToList(ObjectList* self, void* item)
{
    ListLink* slot = GetListLinks(self, item);
    if (self->tail == 0) {
        self->head = item;
    } else {
        ListLink* oldTail = GetListLinks(self, self->tail);
        slot->prev = self->tail;
        oldTail->next = item;
    }
    self->tail = item;
}

// Puts item at the head of the list.
void PrependToList(ObjectList* self, void* item)
{
    ListLink* slot = GetListLinks(self, item);
    if (self->head == 0) {
        self->tail = item;
        self->head = item;
        return;
    }
    {
        ListLink* oldHead = GetListLinks(self, self->head);
        slot->next = self->head;
        oldHead->prev = item;
        self->head = item;
    }
}

// Inserts item into the list just before the item before; a null before appends, the head prepends.
void InsertBeforeInList(ObjectList* self, void* before, void* item)
{
    if (before == 0) {
        AppendToList(self, item);
        return;
    }
    if (before == self->head) {
        PrependToList(self, item);
        return;
    }
    ListLink* next = GetListLinks(self, item);
    ListLink* previous = GetListLinks(self, before);
    void* after = previous->prev;
    ListLink* afterSlot = GetListLinks(self, after);
    next->next = before;
    next->prev = after;
    previous->prev = item;
    afterSlot->next = item;
}

LINKER_REMNANT(func_001525F8);

// Unlinks item from the intrusive list. Any live list walk (ListFrame) that stands on it is first
// stepped back to the previous item, so the walk can go on safely; the item's links are cleared.
void RemoveFromList(ObjectList* list, void* item)
{
    ListLink* link = GetListLinks(list, item);
    ListFrame* e = g_activeListFrames;
    while (e != 0) {
        if (e->link != (u8*)link) {
            e = e->prev;
            continue;
        }
        if (link->prev != 0) e->link = (u8*)GetListLinks(list, link->prev);
        else e->link = (u8*)list;
        e = e->prev;
    }
    if (link->prev != 0) {
        GetListLinks(list, link->prev)->next = link->next;
    } else {
        list->head = link->next;
    }
    if (link->next != 0) {
        GetListLinks(list, link->next)->prev = link->prev;
    } else {
        list->tail = link->prev;
    }
    link->next = 0;
    link->prev = 0;
}

// True when item is linked in the list: it has a next link or is the tail.
s32 IsInList(ObjectList* self, void* item)
{
    ListLink* slot = GetListLinks(self, item);
    s32 result = 0;
    if (slot->next != 0) {
        goto matched;
    }
    if (self->tail != item) {
        goto done;
    }
matched:
    result = 1;
done:
    return result;
}

u32 IsListEmpty(ObjectList* p)
{
	return p->head == 0;
}

// Moves every item of src onto the end of dst and empties src.
void SpliceListToEnd(ObjectList* dst, ObjectList* src)
{
    if (src->head != 0) {
        if (dst->head == 0) {
            *dst = *src;
            ClearList(src);
        } else {
            ListLink* p1 = GetListLinks(dst, dst->tail);
            ListLink* p2 = GetListLinks(src, src->head);
            p1->next = src->head;
            p2->prev = dst->tail;
            dst->tail = src->tail;
            ClearList(src);
        }
    }
}

// Counts the items by walking the list's next links.
s32 CountListItems(ObjectList* list)
{
    s32 count = 0;
    u8* node = (u8*)list->head;
    if (node != 0) {
        s32 stride = list->offset;
        do {
            node = *(u8**)(node + stride);
            count++;
        } while (node != 0);
    }
    return count;
}

// Resets the DMA controller and GS paths and keeps the channel records of VIF0, VIF1, GIF, from-SPR
// and to-SPR (channels 0, 1, 2, 8 and 9).
void InitDmaChannels()
{
	ResetDmaController(1);
	ResetGsPaths();
	g_vif0Channel = GetDmaChannel(0);
	g_vif1Channel = GetDmaChannel(1);
	g_gifChannel = GetDmaChannel(2);
	g_fromSprChannel = GetDmaChannel(8);
	g_toSprChannel = GetDmaChannel(9);
}

extern const VtableEntry g_packetWriterVtable[4] = {{0, 0}, {0, SkipDisplayListWriterSlot}, {0, 0}, {0, 0}};

// Clears the buffer and installs the packet writer's method table.
PacketWriter* InitPacketBuffer(PacketWriter* self)
{
    self->padsOnClose = 0;
    self->closesThroughTable = 0;
    self->vt = (const PacketWriterVt*)g_packetWriterVtable;
    ClearPacketBuffer(self);
    return self;
}

// Forgets the buffer's memory: begin, cursor, end and open tag are zeroed.
void ClearPacketBuffer(PacketWriter* p)
{
	p->end = 0;
	p->begin = 0;
	p->openHeader = 0;
	p->cur = 0;
}

// Moves the cursor back to the start and forgets the open tag.
void RewindPacketBuffer(PacketWriter* p)
{
	u8* b = p->begin;
	p->openHeader = 0;
	p->cur = b;
}

// Reserves count quadwords of permanent memory for the buffer.
void AllocatePacketBuffer(PacketWriter* self, s32 count)
{
    s32 size = count << 4;
    u8* base = ReservePermanentMemory(size);
    self->cur = base;
    self->end = base + size;
    self->begin = base;
}

// Takes count quadwords from front memory for the buffer.
void AllocateQuadwordBuffer(PacketWriter* buffer, u32 count, u32 kind)
{
	u32 bytes = count << 4;
	u8* memory = AllocateFrontMemory(bytes);
	buffer->cur = memory;
	buffer->end = memory + bytes;
	buffer->begin = memory;
}

// Takes count quadwords from back (temporary) memory for the buffer.
void AllocateTempPacketBuffer(PacketWriter* buffer, u32 count)
{
	u32 bytes = count << 4;
	u8* memory = AllocateBackMemory(bytes);
	buffer->cur = memory;
	buffer->end = memory + bytes;
	buffer->begin = memory;
}

// Points the buffer at count quadwords of caller-provided memory.
void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory)
{
    u8* base = (u8*)memory;
    self->begin = base;
    self->cur = base;
    self->end = base + count * 16;
}

// Closes the buffer's tag, gives its quadword count and start address, and clears the buffer
// without freeing it.
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin)
{
    CloseDmaTag(self);
    if (outCount != 0) {
        *outCount = ((u32)self->cur - (u32)self->begin) >> 4;
    }
    if (outBegin != 0) {
        *outBegin = self->begin;
    }
    ClearPacketBuffer(self);
}

// Closes the buffer's tag and gives its quadword count and start; with out non-null a copy of the
// data in front memory. The buffer is then cleared.
void DetachPacketBufferCopy(PacketWriter* self, s32* count, u32* begin, s32* out, s32 flags)
{
    CloseDmaTag(self);
    u32 n = (self->curU - (u32)self->begin) >> 4;
    if (count != 0) {
        *count = n;
    }
    if (begin != 0) {
        *begin = (u32)self->begin;
    }
    if (out != 0) {
        *out = CopyToFrontMemory(n << 4, self->begin);
    }
    ClearPacketBuffer(self);
}

// Closes the buffer's tag, flushes the data cache, starts the DMA chain from the buffer's start on
// the given channel and rewinds the cursor.
void SubmitPacketBuffer(PacketWriter* self, DmaChannel* dma)
{
    CloseDmaTag(self);
    SyncDataCache(0);
    StartDmaChain(dma, self->begin);
    self->cur = self->begin;
}

LINKER_REMNANT(func_00152B30);

// Closes any open tag and opens a new count tag at the cursor; CloseDmaTag fills in its size
// later.
void BeginDmaTag(PacketWriter* self)
{
    CloseDmaTag(self);
    u8* q = self->cur;
    self->openHeader = (s32*)q;
    self->cur = q + 16;
    *(u64*)q = 0x10000000;
    *(u64*)((u8*)self->openHeader + 8) = 0;
}

// Appends a DMA ref tag (id 4) with the given address and size halves. If a tag was open it is
// closed first and a fresh count tag is opened after it.
void AddDmaRefTag(PacketWriter* self, s32 lo, s32 hi)
{
    s32 flag = 0;
    if (self->openHeader != 0) {
        CloseDmaTag(self);
        flag = 1;
    }
    u8* p = self->cur;
    self->cur = p + 16;
    *(u64*)p = (u64)lo | 0x40000000 | ((u64)hi << 32);
    // DMA tag record in the packet buffer, not an object
    *(u64*)(p + 8) = 0;
    if (flag != 0) {
        u8* q = self->cur;
        self->openHeader = (s32*)q;
        self->cur = q + 16;
        *(u64*)q = 0x10000000;
        // DMA tag record in the packet buffer, not an object
        *(u64*)((u8*)self->openHeader + 8) = 0;
    }
}

// Appends a DMA call tag (id 5) with the given address; an open tag is closed first and reopened
// after it.
void AddDmaCallTag(PacketWriter* self, s32 hi)
{
    s32 flag = 0;
    if (self->openHeader != 0) {
        CloseDmaTag(self);
        flag = 1;
    }
    u8* p = self->cur;
    self->cur = p + 16;
    *(u64*)p = ((u64)hi << 32) | 0x50000000;
    // DMA tag record in the packet buffer, not an object
    *(u64*)(p + 8) = 0;
    if (flag != 0) {
        u8* q = self->cur;
        self->openHeader = (s32*)q;
        self->cur = q + 16;
        *(u64*)q = 0x10000000;
        // DMA tag record in the packet buffer, not an object
        *(u64*)((u8*)self->openHeader + 8) = 0;
    }
}

// Closes the open tag and appends a DMA return tag (id 6).
void AddDmaReturnTag(PacketWriter* self)
{
    CloseDmaTag(self);
    u64* p = (u64*)self->cur;
    // packet buffer: the cursor steps over the 16-byte tag, not an object field
    self->cur = (u8*)p + 0x10;
    p[0] = 0x60000000ull;
    p[1] = 0;
}

// Copies n quadwords from src at the write cursor and advances it.
void AppendPacketQuadwords(PacketWriter* self, s32 n, void* src)
{
    CopyQuadwords(self->cur, src, n);
    self->cur += n * 16;
}

// Closes the open tag and appends a DMA end tag (id 7).
void AddDmaEndTag(PacketWriter* self)
{
    CloseDmaTag(self);
    u8* cursor = self->cur;
    self->cur = cursor + 0x10;
    *(u64*)cursor = 0x70000000;
    // DMA tag record in the packet buffer, not an object
    *(u64*)(cursor + 8) = 0;
}

// Ends the open DMA tag: pads the write cursor to 16 bytes, then stores the tag's quadword count in
// its low bits and clears it. A writer with a close method of its own calls that instead.
void CloseDmaTag(PacketWriter* self)
{
    if (self->padsOnClose != 0) {
        s32 p = self->curS;
        if ((p & 0xF) != 0) {
            *(s32*)p = 0;
            p += 4;
            while ((p & 0xF) != 0) { *(s32*)p = 0; p += 4; }
        }
        self->curS = p;
    } else if (self->closesThroughTable != 0) {
        const PacketWriterVt* t = self->vt;
        t->close((PacketWriter*)((u8*)self + t->adj1), 0);
    }
    s32* q = self->openHeader;
    if (q != 0) {
        *q = *q | (((self->curS - (s32)q) >> 4) - 1);
        self->openHeader = 0;
    }
}

void SkipDisplayListWriterSlot() {}

LINKER_REMNANT(func_00152E20);

void InitTextureRenderObject(TextureRenderObject* self)
{
    InitPlacedObject(self);
}

// Builds, for a texture render object, the two DMA packets that draw into the range record's
// texture: the first clears the texture's area and sets the frame, the second draws the sprites
// that render into it (GIF register writes, tags and vertices for a texture of tex->w by tex->h).
// They are kept in the object and sent when it renders.
void BuildTexturePackets(TextureRenderObject* self, RangeRecord* a)
{
    PacketWriter pa;
    PacketWriter pb;
    Vec4U v0;
    Vec4U v1;
    Quad4 q;
    TextureHeader* tex;
    s32 i;
    u64 bits;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;

    self->drawRange = a;
    if (a == 0) {
        return;
    }
    tex = (TextureHeader*)*a->link->elems->entries;
    InitGifPacket(&pa);
    InitPacketWriter(&pb);
    PushBackMemoryMark();
    AllocateTempPacketBuffer(&pa, 0x40);
    AllocateTempPacketBuffer(&pb, 0x40);
    WriteVifFlushE(&pb);
    SetupTextureRenderTarget(tex, &pa);
    BeginGifTag(&pa, 0x246, 3, 0x551);
    AddGifRgbaEntry(&pa, 0);
    AddGifXyzEntry(&pa, 0, 0, 0);
    AddGifXyzEntry(&pa, tex->w << 4, tex->h << 4, 0);
    BeginGifTag(&pa, 0x200, 1, 0xE);
    AddGifRegisterWrite(&pa, 0x41, ((u64)(tex->w - 2) << 16) | (((u64)(tex->h - 2) << 48) | 0x100000001ULL));
    EndGifPacket(&pa);
    WriteVifDirectFromWriter(&pb, &pa);
    v0.x = (f32)((tex->w - 1) * 8) * 1024.0f;
    v0.y = (f32)((tex->h - 1) * 8) * 1024.0f;
    v0.z = 0;
    v1.x = (f32)(tex->w * 8) * 1024.0f + 8589934592.0f;
    v1.y = (f32)(tex->h * 8) * 1024.0f + 8589934592.0f;
    v1.z = 0;
    WriteVifBaseOffset(&pb, 0, 0);
    CopyWordsToWriter(&pb, 8, 1, (u32*)&v0, 0);
    CopyWordsToWriter(&pb, 8, 1, (u32*)&v1, 1);
    ClearPacketBuffer(&pa);
    UsePacketBufferMemory(&pa, 1, &q);
    ReserveGifPackedData(&pa, 0x24D, 0, 3, 0x412, 0);
    CopyWordsToWriter(&pb, 0xC, 1, (u32*)&q, 0xC);
    DetachPacketBufferCopy(&pb, &self->firstPacket, 0, &self->firstPacketSize, 0x13);
    PopBackMemoryMark();
    PushBackMemoryMark();
    ClearPacketBuffer(&pa);
    ClearPacketBuffer(&pb);
    AllocateTempPacketBuffer(&pa, 0x80);
    AllocateTempPacketBuffer(&pb, 0x80);
    bits = (tex->tex0 & ~0x1800000000ULL) | 0x800000000ULL;
    BeginGifTag(&pa, 0x200, 1, 0xE);
    AddGifRegisterWrite(&pa, 0x3F, 0);
    AddGifRegisterWrite(&pa, 7, bits);
    AddGifRegisterWrite(&pa, 0x15, 0x61);
    AddGifRegisterWrite(&pa, 0x48, 0x31001);
    BeginGifTag(&pa, 0x316, 5, 0xE5353);
    x0 = tex->w << 4;
    y0 = tex->h << 4;
    x1 = x0 + 8;
    y1 = y0 + 8;
    for (i = 1; i >= 0; i--) {
        AddGifUvEntry(&pa, 0x10, 8);
        AddGifXyzEntry(&pa, 0, 0, 0);
        AddGifUvEntry(&pa, x0 + 0x10, y1);
        AddGifXyzEntry(&pa, x0, y0, 0);
        AddGifRegisterWrite(&pa, 0x3F, 0);
        AddGifUvEntry(&pa, 8, 0x10);
        AddGifXyzEntry(&pa, 0, 0, 0);
        AddGifUvEntry(&pa, x1, y0 + 0x10);
        AddGifXyzEntry(&pa, x0, y0, 0);
        AddGifRegisterWrite(&pa, 0x3F, 0);
        AddGifUvEntry(&pa, 8, 8);
        AddGifXyzEntry(&pa, 8, 8, 0);
        AddGifUvEntry(&pa, x1, y1);
        AddGifXyzEntry(&pa, x1, y1, 0);
        AddGifRegisterWrite(&pa, 0x3F, 0);
    }
    EndGifPacket(&pa);
    WriteVifFlush(&pb);
    WriteVifDirectFromWriter(&pb, &pa);
    DetachPacketBufferCopy(&pb, &self->secondPacket, 0, &self->secondPacketSize, 0x13);
    PopBackMemoryMark();
}

// If the object has a draw range, runs its slot-27 method and queues a deferred request that draws
// its parts with a transform built from the given matrix.
void QueuePlacedObjectDraw(TextureRenderObject* self, s32 unused, void* a2)
{
    (void)unused;
    if (self->drawRange != 0) {
        self->desc02()->m27(self, a2);
        DeferredRequest f;
        (void)FillMemory(&f, 0, 0x80);
        f.callback = (void*)DrawPlacedObjectParts;
        f.group = 0;
        BuildPlacedObjectTransform(self, (Quad16*)a2, (ScaledTransform*)&f.block);
        f.arg = self;
        QueueDeferredRequest(&f);
    }
}


// The file's .data, 0x261CC8 to 0x261F28, in retail's order: the globals its functions read
// (D_00261EF0 and the DMA channel words are read by many files, which keep them extern).
ObjectLink g_pooledObjectLinks[1] = { { 2, 0x2BC, 0x574 } };
f32 g_launchHorizontalSpeed = 500.0f;
f32 g_launchLiftSpeed = 800.0f;
ObjectLink g_takerLinks[3] = { { 4, 0x2B4, 0x734 }, { 4, 0x2B5, 0x738 }, { 0, 0x2B6, 0x73C } };
u16 g_stepWaitButtonMasks[16] = {0x40,0x40,0x80,0x20,0x10,4,1,8,2,0,0,0,0,0,0,0};
u8 g_stepWaitButtonGlyphs[16] = {0x58,0x58,0x53,0x4F,0x54,0x4C,0x6C,0x52,0x72,0x28,0x29,0x28,0x28,0x58,0,0};
// size: s32 counter (lw/sw), 4 bytes before an 8-aligned next label
s32 g_controlBlockingElementCount = 0;
ThresholdRange g_thresholdRanges[4] = {
    { 0.8f, 2, 5 }, { 0.4f, 6, 10 }, { 0.2f, 15, 25 }, { 0.0f, 50, 100 }
};
ScatterTable g_scatterTablesPlain[2] = {
    { 0, 1.0f, 0.0f, 0.6f, 0.1f, -0.8f, 0.0f, 4, 6, 0, 2, 0.399f, 1, 0.799f, 2, 0.075f, 0.25f, -0.2f, -0.003f, 2, 0.075f, 4, g_thresholdRanges, 0 },
    { 0, 0.5f, 0.0f, 0.2f, 0.1f, -0.4f, -0.4f, 4, 6, 0, 2, 0.399f, 0, 0.799f, 0, 0.075f, 0.25f, -0.2f, -0.003f, 2, 0.075f, 4, g_thresholdRanges, 0 },
};
ScatterTable g_scatterTableFlagged = { 0, 0.0f, 0.0f, 0.2f, 0.0f, 0.0f, 0.0f, 4, 6, 0, 2, 0.399f, 0, 0.799f, 0, 0.075f, 0.25f, -0.2f, -0.003f, 2, 0.075f, 4, g_thresholdRanges, 0 };
ScatterTable g_scatterTableEarlyGame = { 0, 1.0f, 0.0f, 0.0f, 0.1f, -0.8f, 0.0f, 4, 6, 0, 2, 0.399f, 1, 0.799f, 2, 0.075f, 0.25f, -0.2f, -0.003f, 2, 0.075f, 4, g_thresholdRanges, 0 };
// size: func_00151A68 clears 0x24 bytes of it
ScatterController g_scatterController = {};
// size: semaphore id from func_002027A0 (lw/sw), 4-byte label
u32 g_vif0Channel = 0;
u32 g_vif1Channel = 0;
u32 g_gifChannel = 0;
u32 g_fromSprChannel = 0;
// The file's last .data: the 8 zero bytes after it are the linker's padding before
// active_set_solver.cpp's 16-aligned .data (D_00261F30).
u32 g_toSprChannel = 0;
