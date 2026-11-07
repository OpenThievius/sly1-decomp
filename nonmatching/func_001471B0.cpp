// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 397/556 (71.4%), checked 2026-11-07
// NEAR (2026-11-08, vu0w3-e1): structure right (frame 0x90, the calls, the fallback loaded into a GPR before the sqrt); one nop and a few schedule swaps differ: retail computes the squared radius before the position difference and fills the compare-to-branch gap before the NormalizeOr branch with the p1 - p0 vsub, here that vsub is hoisted above the compare and the slot is a nop (4 bytes more). NormalizeOr with the fallback passed as a j operand (Vu0::Q(D_00248D30)) makes the compiler loop; the fallback as a u128 loaded first compiles.
#include "common.h"
#include "vu0.h"
#include "asm_func.h"
#include "state_notifier.h"
#include "world.h"
#include "scaled_offset_object.h"
#include "game_progress.h"
#include "object_link.h"
#include "switched_collider.h"
#include "camera.h"
#include "effect.h"
#include "screen_element.h"
#include "font.h"
#include "flag_table.h"

void func_0012AA28(void* a, s32 b);
void LoadPlacedObject(void* a, void* b);
void ResolveObjectLinks(void* a, s32 b, void* c);
void CopyPlacedObject(void* a, void* b);
extern u8 g_flagTable[];
void StartPlacedObject(void* a);
void* FindFirstObjectByIdGathered(void* a, s32 b, s32 c, void* d);
s32 TestFlagTableBit(void* a, s32 b);

extern s32 D_00270458;
extern f32 g_frameDt;
void LoadCollider(Collider* self, void* p);
f32 ReadBufferedFloat(void* p);
void StartPlacedObject(void* self);
void ApplyScaledOffset(ScaledOffsetObject* self);
void ClearRootObjectStateBits(World* a, void* self, s32 n);
void ClearRootTries(void* self);
void InitCollider(Collider* self);
void HandlePlacedObjectNotification(void* self, s32 kind, void* msg);
void GetStateWalkerCurrentKey(void* sub, s32* out);
void* AppendQueuedCall(void* owner, void* fn, void* ctx, s32 a3, s32 a4);
void CompleteTimeRangeNotifier(void* self);

struct StateMessage {
    s32 state;              // 0x00
    void* sender;           // 0x04
};

struct NotifyFrame {
    StateMessage note;      // 0x00
    u8 pad08[0x50 - 0x08];
    s32 code;               // 0x50
    u8 pad54[0x60 - 0x54];
};

struct ListenerMessage {
    s32 state;              // 0x00
    void* sender;           // 0x04
    u8 pad08[0x50 - 0x08];
};

s32 IsObjectOfKind(void* node, s32 kind);
extern u8 g_flagTable[];
void InitPlacedObject(StateNotifier* self);
void AppendToList(List01* list, StateNotifier* item);
s32 TakeFlagTableIndex(FlagTable* p);

struct __attribute__((packed)) PSys_1481A0 {
    u8 pad0[0x26C];
    f32 f26C;
};

void PlaceSpareSoundNotifier(World* self);
void AddReserveUnit(void);
s32 GetSpareCountLimit(void);


extern s32 D_0026EC58;
s32 IsObjectOfKind(void* node, s32 kind);
SwitchedCollider* GetActiveSwitchedCollider(void);


extern s32 D_00275C34;
extern u8 g_scatterController[];
extern u8 g_memoryCard[];
void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);
void ResetScatterLevels(void* p);
void StartMemoryCardSave(void* p);
extern void* g_deadlineNotifier;
void HandlePlacedObjectNotification(void* self, s32 kind, void* msg);
void GetStateWalkerCurrentKey(void* dev, s32* out);
void* AppendQueuedCall(void* target, void* fn, void* ctx, s32 a, s32 b);

extern f32 g_gameTime;
void AppendToList(void* table, void* self);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);
void SetBestTimeState(T217D_1380* self, s32 n);

void HandlePlacedObjectNotification(void* self, s32 kind, void* msg);
void GetStateWalkerCurrentKey(void* dev, s32* out);
void* AppendQueuedCall(void* target, void* fn, void* ctx, s32 a, s32 b);
void CompleteCountdownNotifier(void* self);

extern s32 D_00270458;
extern f32 g_frameDt;

extern void* D_00261B60[28];
extern u8 g_flagTable[];
f32 RandomFloatInRange(f32 a, f32 b);
Effect* CreateEffect(s32 kind, EffectOwner* sys);
void SetFlagTableBit(void* table, s32 v);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void AddReserveUnitNow(void* self);

void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
extern u8 D_0026EC60[];

extern u8 g_camera[];
extern u8 g_identityMatrix[];

extern u8 g_identityMatrix[];
extern u8 D_00248D30[];
extern f32 D_00261B40;
void PushBackMemoryMark(void);
StateNotifier** AllocateBackMemory(s32 size);
s32 GatherObjectsOfKind(World* self, s32 a1, s32 n, StateNotifier** arr);
f32 RandomFloatInRange(f32 a, f32 b);
void ComputePolarOffset(void* out, f32 x, f32 y, f32 z);
void QueryValueListMask(World* a, f32 f, void* b, void* c);
void PopBackMemoryMark(void);


struct __attribute__((aligned(16))) Quad_148038 {
    s32 a, b, c, d;
};

struct Ctx_148038;
extern f32 D_00261AB0[4];
extern u8 g_identityMatrix[];
extern u8 D_00248D30[];
extern Quad_148038 D_00261AC0;
s32 GatherObjectsOfKind(World* self, s32 a1, s32 a2, void** out);
s32 GetSpareCountLimit(void);
void UnprojectCameraPoint(Ctx_148038* a, void* b, void* c);
s32 QueryValueListMask(Ctx_148038* self, f32 x, void* vec, void* out);

extern void* D_00261AD0[28];
Effect* CreateEffect(s32 kind, EffectOwner* sys);
void CountPickupTowardHundred(void* self);
f32 RandomFloatInRange(f32 a, f32 b);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

ObjectLink g_stateNotifierLinks[5] = {

    { 0, 0x25F, 0x2E4 },
    { 2, 0x25B, 0x324 },
    { 2, 0x25C, 0x328 },
    { 2, 0x25E, 0x380 },
    { 2, 0x25D, 0x384 },
};
f32 D_002619DC = -5.0f;
f32 D_002619E0 = 0.25f;
f32 D_002619E4 = 1.0f;
f32 D_002619E8 = 0.25f;
f32 D_002619EC = 5.0f;
f32 D_002619F0[4] = { 0.0f, 0.0f, -2250.0f, 0.0f };
f32 D_00261A00[4] = { 0.0f, 75.0f, 85.0f, 0.0f };
f32 D_00261A10[4] = { 10.0f, 0.0f, 0.25f, 0.0f };
f32 D_00261A20[12] = { 20.0f, 5.0f, 0.150000006f, 120.0f, 800.0f, 50.0f, 0.25f, 4500.0f, 800.0f, 50.0f, 0.25f, 4500.0f };
f32 D_00261A50 = 300.0f;
INCLUDE_DATA(D_00261A54);
f32 D_00261A60[4] = { 1.0f, 1.0f, 0.0f, 0.0f };
f32 D_00261A70[4] = { -250.0f, 0.0f, 600.0f, 0.0f };
f32 D_00261A80[4] = { 1.0f, -0.300000012f, 0.0f, 0.0f };
f32 D_00261A90[4] = { 0.699999988f, -0.400000006f, 0.0f, 0.0f };
f32 D_00261AA0[4] = { 0.0f, 800.0f, 1200.0f, 0.0f };
f32 D_00261AB0[4] = { -0.6f, 0.85f, 300.0f, 0.0f };
Quad_148038 D_00261AC0 = { 0x40A00000, (s32)0xC3FA0000, 0, 0 };
void* D_00261AD0[28] = {
    (void*)0xBF59999A, (void*)0x3F4CCCCD, (void*)0x42C80000, 0,
    (void*)0xBF800000, (void*)0xBF800000, 0, 0,
    (void*)0xBF800000, (void*)0x40000000, 0, 0,
    (void*)0x3F800000, (void*)0x40400000, 0, 0,
    0, 0, (void*)0x3F800000, 0,
    (void*)0x3F800000, (void*)0xBF4CCCCD, 0, 0,
    (void*)CountPickupTowardHundred, 0, 0, 0
};
f32 D_00261B40 = 0.05f;
f32 D_00261B48[2] = { 75.0f, 1e+02f };
f32 D_00261B50[4] = { 1e+03f, 1.3e+03f, 0.0f, 0.0f };
void* D_00261B60[28] = {
    (void*)0xBD4CCCCD, (void*)0x3F4CCCCD, (void*)0x42C80000, 0,
    (void*)0xBF800000, (void*)0xBF800000, 0, 0,
    (void*)0xBF800000, (void*)0x40000000, 0, 0,
    (void*)0x3F800000, (void*)0x40400000, 0, 0,
    0, 0, (void*)0x3F800000, 0,
    (void*)0x3F800000, (void*)0xBF4CCCCD, 0, 0,
    (void*)(void (*)(void))AddReserveUnitNow, 0, 0, 0
};
f32 D_00261BD0[4] = { 0.0f, 0.0f, 200.0f, 0.0f };
f32 D_00261BE0 = 0.75f;
INCLUDE_DATA(D_00261BE4);


struct ActiveNotifierData {
    s32 f00;
    u8 pad04[0x14 - 0x04];
    f32 f14;
    PlacedObject* f18;
};

void* GetActiveSwitchedColliderData(void);
s32 MaskWorldBitsBySave(void);
void ComputeObjectMotionInFrame(void* obj, s32 z, void* point, Vec02* out, s32 a, s32 b, s32 c);
s32 CollectMeshHits(void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, void* a6);

void func_001471B0(StateNotifier* self)
{
    Vec02 hit[3];
    Vec02 p0;
    Vec02 p1;
    if (self->armed != 0) {
        ActiveNotifierData* d = (ActiveNotifierData*)GetActiveSwitchedColliderData();
        if (d->f00 != 0 && d->f18 != 0) {
            Vec02* pos = &self->v140;
            f32 r = D_00261A50;
            u128 diff = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(d->f18->v140));
            f32 sq = Vu0::ToFloat(Vu0::Dot(diff, diff));
            if (!(r * r < sq)) {
                f32 reach = d->f14;
                if (sq < reach * reach) {
                    self->desc02()->m2F(self, 1);
                    return;
                }
                if ((MaskWorldBitsBySave() & 0x20) != 0 && IsObjectOfKind(self, 0x58) != 0) {
                    ComputeObjectMotionInFrame(d->f18, 0, &d->f18->v140, &p0, 0, 0, 0);
                    ComputeObjectMotionInFrame(self, 0, pos, &p1, 0, 0, 0);
                    u128 dd = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(d->f18->v140));
                    u128 fb = *(const u128*)&D_00248D30;
                    u128 rel = Vu0::Sub(Vu0::Q(p1), Vu0::Q(p0));
                    u128 dir = Vu0::NormalizeOr(dd, fb);
                    if (-50.0f < Vu0::ToFloat(Vu0::Dot(rel, dir))) {
                        self->desc02()->m2F(self, 1);
                        return;
                    }
                }
                PlacedObject* o = d->f18;
                if ((o->desc->flags & 2) != 0 && *(void**)((u8*)o + 0x3F8) != 0) {
                    if (CollectMeshHits(pos, *(void**)((u8*)o + 0x3F0), *(void**)((u8*)o + 0x3F8), 0, (u8*)o + 0x3A4, 1, hit) != 0) {
                        self->desc02()->m2F(self, 1);
                    }
                }
            }
        }
    }
}

