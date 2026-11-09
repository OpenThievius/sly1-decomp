// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1015/1084 (93.6%), checked 2026-11-09
// NEAR (2026-11-08, worker night-large1): an effect spawner's splash (its sound by distance, the
// effect, and a burst through SpawnEffectsAt at 500 and beyond), retail's code up to the burst's
// two records: there the stores of the tail and the block are scheduled otherwise (the order of
// the constants' loads and of the block's stores; the block copy takes a1/a2 where retail has
// a0/a1). tools/permute.py's best orders of the tail's six stores and of five of the block's are
// kept here (69 bytes off).
// Still differs (2026-11-09, worker w7, from the -dS -fsched-verbose-6 and -dl dumps; all 720
// orders of the tail's six stores give 69 bytes at best; docs/TOOLCHAIN.md "A burst's two
// records (func_00156288)"):
// - the tail's 8.0/12.0 take f0/f1 where retail has f1/f0: local-alloc ties their equal spans by
//   birth. Storing f20 and f24 first (or naming lo/hi and storing hi first) gives retail's
//   registers, but then sched2's LUID order of the tail's stores is not retail's.
// - retail's f10 store goes before the cfg store (cfg in the delay slot): in sched1 the cfg store
//   weighs 0 (cfg's death) and the f10 store +1 (`one` lives on), so it always goes first; with
//   cfg kept live past it (an experiment) retail's order comes out. No plain form found.
// - the block's 5.0 and -1.0 share f0 in retail, so -1.0's load follows 5.0's store in sched1;
//   here the four constant loads (priority 4) all issue before the stores (priority 2), which
//   wait for the gravity load (no base: conflicts with the frame stores), so -1.0 takes f3.
// - the copy loop's dest (sp+64) is born before the world pointer dies (a0 taken): a1/a2/a3 for
//   retail's a0/a1/a2.
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

// The block of a burst SpawnEffectsAt is given (func_00156288 fills these fields).
struct __attribute__((aligned(16))) SpawnBlock {
    union {
        Quad16 q[8];
        struct {
            f32 f00, f04, f08;      // 0x00: the position (sizes in func_00156288's copy)
            u8 pad0C[4];
            Vec02 gravity;          // 0x10: the world's (+0x1EE0)
            u8 pad20[0x10];
            Vec02 up;               // 0x30
            u8 pad40[4];
            f32 f44, f48;           // 0x44
            u8 pad4C[4];
            f32 f50, f54;           // 0x50
            u8 pad58[0x18];
            f32 f70;                // 0x70
            u8 pad74[4];
            f32 f78;                // 0x78
            u8 pad7C[4];
        };
    };
};
// Its tail (func_00156288 fills these fields).
struct __attribute__((aligned(16))) SpawnTail {
    union {
        Quad16 q[4];
        struct {
            s32 f00, f04;           // 0x00
            u8 pad08[8];
            f32 f10;                // 0x10
            u8 pad14[0xC];
            f32 f20, f24;           // 0x20
            u8 pad28[8];
            void* f30;              // 0x30
            u8 pad34[0xC];
        };
    };
};
void* FillMemory(void* p, s32 v, u32 n);
typedef void (*EffectStartFn)(Effect* self, void* a, s32 z, f32 f);
void* CreateEffect(s32 a, s32 b);
extern f32 g_gameTime;

extern s32 D_00262050[];
f32 RandomFloatInRange(f32 a, f32 b);
s32 RandomIntInRange(s32 a, s32 b);
void StartSoundEffect(s32 a0, void* a1, void* a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void StopSoundRecord(void* self, s32 n);
void SpawnEffectsAt(Quad16* self, Quad16* a1, void* a2, SpawnTail* a3, SpawnBlock* a4, s32 a5, s32 a6);

void func_00156288(BaseObject* self, u8* cfg, Quad16* p, Quad16* at, f32 chance, f32 minScale, f32 size)
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
                StartSoundEffect(D_00262050[RandomIntInRange(0, 3)], snd + 0x574, snd, 0, 10.0f, 1.0f, vol,
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
            SpawnTail tail;
            SpawnBlock copy;
            SpawnBlock blk;
            f32 one = 1.0f;
            FillMemory(&tail, 0, 0x40);
            tail.f04 = -1;
            tail.f00 = 2;
            tail.f10 = one;
            tail.f30 = cfg;
            tail.f20 = 8.0f;
            tail.f24 = 12.0f;
            FillMemory(&blk, 0, 0x80);
            blk.f08 = one;
            blk.f00 = dist * 0.5f;
            blk.f04 = dist * 0.75f;
            blk.gravity = AT(Vec02, self->world, 0x1EE0);
            blk.up = g_unitZVector;
            blk.f54 = 5.0f;
            blk.f48 = 1.04719758f;
            blk.f44 = 0.392699093f;
            blk.f50 = one;
            blk.f70 = one;
            blk.f78 = -1.0f;
            copy = blk;
            blk.q[0] = *at;
            blk.f08 += 30.0f;
            SpawnEffectsAt(&blk.q[0], (Quad16*)&g_unitZVector, (void*)RandomIntInRange(4, 6), &tail, &copy, 0, 0);
        }
    } else if (snd != 0) {
        StopSoundRecord(AT(void*, snd, 0x574), 0);
    }
}
