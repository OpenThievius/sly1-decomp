// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1080/1084 (99.6%), checked 2026-11-12
// w37-f3 (2026-11-12): 30 lines to 2. The two records are brace initialisers (docs/toolchain/large-functions.md, "A brace initialiser's union member is a CLOBBER"): the tail with the first float of each of its two float groups (0x10 and 0x20) a union's member, as a Quadratic16's is (scanned: of the 42 choices of up to three union members, only f10+f20 or f04+f20, each also with f24 or f30, leave 2 lines), the block the spawn block of func_001930B8 and func_001549C8 with Quadratic16s at 0x00 and 0x70 (scanned: the other seven choices leave 15 to 28), built in a temporary and copied because the gravity and the up vector are copied from memory; the position is a local of its own, which takes the temporary's slot. Left: retail stores the up vector (sq v1,240(sp)) before the gravity (sq v0,208(sp)); ours has them in member order. In sched1 both stores have priority 4 and weight 0, so LUID decides; retail's order needs the gravity's load issued after the three single-use constants (its priority 5, not 6) or its store not ready when the up vector's goes. Tried: the gravity as a Quad16 or a Quadratic16 member, the up vector as a Vec02 member (20 lines), the world pointer in a local (55), the block built in place with the two vectors assigned after it (40 to 42).
// DECLS (2026-11-11, w28-nmdecls): TransformPointBetweenFrames now void (defined void): neutral, order 260/271.
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
// w15 (2026-11-10, emulated: docs/toolchain/sched1.md "A burst's two records, emulated"): with the
// four constants loaded in the block, retail's shared $f0 for 5.0 and -1.0 is impossible (every
// constant load outranks every store behind the gravity load); a -1.0 set in an earlier block and
// used once (update_equiv_regs moves it to the store) gives retail's FP registers (`f32 m1 = -1.0f;`
// at the top: 32 lines, store order off). The tail is retail's when its 1.0 store carries a death
// (a dying 1.0 variable: retail's single $f20 for both records leaves that open). The copy's a0 needs
// sp+64 born after the world pointer dies (blk.up before blk.gravity gives it, breaking the FP regs).
// W23 (2026-11-11): re-scored, unchanged (order 260/271). tools/sched1.py --check replays every block of
// it (the burst's 50-insn block included) as the trace, so w15's emulated walls stand; no VU0 conversion
// or Scalar slot is involved there, so wave 20's "*r" lever does not apply. No new lever found.
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
#include "vu0.h"


void TransformPointBetweenFrames(void* from, void* to, void* point, Vec02* out);

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
void GenerateSpawnArrays(void* a, void* b, s32* out);
void SpawnRecordEffects(void* b, void* c, void* a, s32 o0, s32 o1, s32 o2, s32 o3);
void GenerateSpawnSetupPair(void* a, void* b, s32* out, s32* pair);
void EmitParticleChunk(void* b, void* c, void* a, s32 o0, s32 o1, s32 o2, s32 o3, s32 p0, s32 p1);

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
void ReadSpawnMesh(void* self, s32 count);
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

void ApplyLookSourceToListedObject(void*,void*);
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
void FillLookDirectionBlock(Effect* a, Rec50* b);
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

// The burst's two records as the brace initialisers they are (w37-f3): the block has the layout
// of Blk05 (include/switched_collider.h; its 0x40 group's floats are named here), its first and
// last vectors Quadratic16s; the tail's two float groups each start with a union's member.
struct SplashBlock {
    Quadratic16 v00; Vec02 v10; Vec02 v20; Quad16 q30; f32 f40; f32 f44; f32 f48; s32 f4C; Vec02 v50; Quad16 q60; Quadratic16 v70;
};
struct __attribute__((aligned(16))) SplashTail {
    s32 f00; s32 f04; s32 f08; s32 f0C; union { f32 f10; u32 f10Bits; }; f32 f14; s32 f18; s32 f1C; union { f32 f20; u32 f20Bits; }; f32 f24; s32 f28; s32 f2C; void* f30; s32 f34; s32 f38; s32 f3C;
};
void SpawnSurfaceContactEffects(BaseObject* self, u8* cfg, Quad16* p, Quad16* at, f32 chance, f32 minScale, f32 size)
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
            SplashTail tail = { 2, -1, 0, 0, 1.0f, 0.0f, 0, 0, 8.0f, 12.0f, 0, 0, cfg };
            SplashBlock block = {
                { dist * 0.5f, dist * 0.75f, 1.0f }, AT(Vec02, self->world, 0x1EE0), { 0.0f, 0.0f, 0.0f },
                *(Quad16*)&g_unitZVector, 0.0f, 0.392699093f, 1.04719758f, 0,
                { 1.0f, 5.0f, 0.0f }, { { 0, 0, 0, 0 } }, { 1.0f, 0.0f, -1.0f }
            };
            Vec02 pos = *(Vec02*)at;
            pos.z += 30.0f;
            SpawnEffectsAt((Quad16*)&pos, (Quad16*)&g_unitZVector, (void*)RandomIntInRange(4, 6), (SpawnTail*)&tail, (SpawnBlock*)&block, 0, 0);
        }
    } else if (snd != 0) {
        StopSoundRecord(AT(void*, snd, 0x574), 0);
    }
}
