// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 671/676 (99.3%), checked 2026-11-08
// NEAR (2026-11-08, night-gamec): the f26A0 max: retail loads f26A0 into f0 and the limit into f1 (max.s f0,f0,f1); every form tried gives the two the other way round
// In the context of its file, src/main/player_target.cpp: its declarations before the function, bodies cut.
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "on_off_object.h"
#include "game_clock.h"
#include "item_keeper.h"
#include "shapes.h"
#include "vu0.h"
#include "globals.h"

// The file's .rodata, in retail's order: the constants and jump tables only its assembly reads.
extern const f32 D_0024DAA0 = -3.40282347e+38f;
extern const f32 D_0024DAD0 = -3.40282347e+38f;

struct __attribute__((aligned(16))) OnOffDefaultsBlock { f32 f[36]; };

// The file's .data, in retail's order.
float D_00274E00 = 150.0f;
float D_00274E04 = 50.0f;
float D_00274E08 = 250.0f;
float D_00274E0C = 1000.0f;
float D_00274E10 = 1.25f;
float D_00274E14 = 2.0f;
float D_00274E18 = 250.0f;
float D_00274E1C = 0.200000003f;
float D_00274E20 = 2500.0f;
float D_00274E24 = -250.0f;
f32 D_00274E28 = 0;
f32 D_00274E2C = 0;
float D_00274E30 = 1250.0f;
float D_00274E34 = 500.0f;
float D_00274E38 = 500.0f;
f32 D_00274E3C = 1e+03f;
float D_00274E40 = 100.0f;
float D_00274E44 = 100.0f;
float D_00274E48 = 0.300000012f;
float D_00274E4C = 25.0f;
float D_00274E50 = 1.5f;
float D_00274E54 = 0.25f;
float D_00274E58 = 0.5f;
float D_00274E5C = 0.200000003f;
OnOffDefaultsBlock g_onOffObjectDefaults = {
    { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      -225.0f, 1.0f, 0.0f, 0.0f, 20.0f, 1.0f, 0.0f, 0.0f,
      -3.40282347e+38f, 3.40282347e+38f, -3.40282347e+38f, 3.40282347e+38f, -3.40282347e+38f, 3.40282347e+38f,
      0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f }
};
float D_00274EF0[3] = {2500.0f, 0.0f, 1.0f};

// What a target cost search passes to its scorer: the player, the target, and the record at
// +0x10 the scorer hands on.
struct TargetCostContext { void* p0; BaseObject* p4; u8 pad1[0x10 - 8]; };
struct ObjectPlacementScore { u8 vecA[0x10]; u8 vecB[0x10]; f32 result; };

void PlaceOnTargetObject(void* a0, void* a1, void* a2, void* a3);
void ScorePlayerTargetPlacement(void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, void* a6, s32 a7, s32 stack);

f32 ScoreTargetObjectAt(TargetCostContext* self);

struct PointPlacementScore { u8 vecA[0x10]; f32 result; };

void PlaceOnTargetPoint(void* a0, void* a1, s32 a2);
void ScorePlayerTargetPlacement(void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, void* a6, s32 a7, s32 stack);

f32 ScoreTargetPointAt(TargetCostContext* self);

void PlaceOnTargetCurve(void* a0, void* a1, s32 a2);
void ScorePlayerTargetPlacement(void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, void* a6, s32 a7, s32 stack);

f32 ScoreTargetCurveAt(TargetCostContext* self);

// func_001CEB18 also takes a float in $f12 (it reads $f12 at entry); this
// function passes its own float parameter straight through.
struct PathScoreArgs { s32 a; s32 b; s32 pad[2]; s32 c[4]; };
void func_001CEB18(f32 t, s32 a, s32 b, s32* c, f32* out, s32 d, s32 e);

f32 ScoreTargetPathAt(PathScoreArgs* o, f32 t);

typedef void (*PathShapeFn)(void* self, void* out, s32 x);

struct PathShape {
    PathShapeFn* vtbl;
};

struct PathTarget {
    u8 pad0[0x18];
    s32 f18;
    u8 pad1C[0x34 - 0x1C];
    PathShape* f34;
};

struct PathScoreContext {
    s32 f0;
    PathTarget* node;
};

struct PathScoreFrame {
    Quad16 a;
    s32 b[2];
    u8 pad18[8];
    Quad16 c;
    f32 out;
};

void FindLocalMinimum(f32 f12, f32 f13, f32 f14, f32 f15, void* fn, void* b, s32 c, void* out);

f32 ScoreTargetPathNearest(PathScoreContext* self);

struct TargetSpanHit {
    Vec02 point;
    u8 pad10[0x34];
    f32 f44;
    u8 pad48[0x28];
};
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInBox(World* world, BaseObject* self, Vec02* lo, Vec02* hi, void* a, void* b, s32* n0, s32* n1);
void EvaluateHermiteVectorSegment(f32 t, f32 u, f32 v, void* a, void* b, void* c, void* d, Vec02* out, void* e, void* f);
s32 FindNearestSpanObject(s32 zero, Vec02* in, void* out, s32 n0, s32 n1, TargetSpanHit* hit);

s32 AddTargetObstructionCost(f32 limit, BaseObject* self, void* a1, void* a2, void* pa, void* pb, Vec02* pc, void* pd, Vec02* pe);

f32 AddRepeatTargetPenalty(Player* self, s32 id, f32 a, f32 b);

// What func_001D0B20 reads: the player's record at +0x23BC (a frame at +0x18 and a mover at
// +0x34), the angle at +0x23C4 and its flip flag at +0x23C8, and the target (a flag at +0x04,
// the radius at +0x08, a point at +0x10, a pair of points at +0x20).
struct TargetMover {
    struct Vt { u8 pad0[4]; void (*placeAt)(TargetMover* self, f32 angle, s32 flag, void* out); void (*place)(TargetMover* self, f32 angle, void* out, s32 flag); u8 pad0C[0x20 - 0x0C]; f32 (*limit)(TargetMover* self); };
    const Vt* vt;           // 0x00
    u8 pad04[4];
    s32 wraps;              // 0x08
    u8 pad0C[0x14 - 0x0C];
    const f32* low;         // 0x14
};
// func_001D12F0 reads the record's active flag (+0x40), its limit (+0x44) and scale (+0x48), and
// the player's float at +0x23C0.
struct TargetFrameRecord {
    u8 pad0[0x18];
    void* frame;            // 0x18
    u8 pad1C[0x34 - 0x1C];
    TargetMover* mover;     // 0x34
    u8 pad38[0x40 - 0x38];
    s32 active;             // 0x40
    f32 limit;              // 0x44
    f32 scale;              // 0x48
};
struct TargetPlayerView { u8 pad0[0x23BC]; TargetFrameRecord* record; f32 f23C0; f32 angle; s32 flip; };
struct TargetProbe { u8 pad0[4]; s32 active; f32 radius; u8 pad0C[4]; Vec02 point; Vec02 end; };

f32 WrapModulo(f32 x, f32 y);
void TransformPointBetweenFrames(void* frame, void* player, void* in, void* out);
s32 CollectBoundsSpans(void* a, void* b, void* c, s32 d, void* e, f32 x);

static inline f32 ClampBetween(f32 v, f32 lo, f32 hi);

void func_001D0B20(TargetPlayerView* self, TargetProbe* t, u8* out);

// The phase clip a player's sub-states 0x11 and 0x14 advance (+0x2230): its clip, whose length
// is at +0x34, the time and the speed.
struct PhaseClip {
    u8 pad00[0x34];
    f32 length;             // 0x34
};
struct PhasePlayer {
    u8 pad00[8];
    PhaseClip* clip;        // 0x08
    u8 pad0C[0x14 - 0x0C];
    f32 time;               // 0x14
    f32 speed;              // 0x18
};

extern f32 D_00274B64;
void UpdateEightEntryBlendWeights(Player* self, void* slots, s32 n);
void UpdateSixEntryBlendWeights(Player* self, void* slots, s32 n, void* phase);
void PlayPhaseCrossingSound(Player* self, void* sounds, f32 t);
void func_001719E8(void* self, s32 a, s32 b, void* part, f32 k, void* d);

void UpdatePlayerTargetPhase(Player* self)
{
    switch (self->f2228) {
    case 0x11: {
        void* slots;
        s32 n;
        void* sounds;
        switch (self->f239C) {
        case 0:
            slots = (u8*)self + 0xA20;
            n = *(s32*)((u8*)self + 0xB20);
            sounds = (u8*)self + 0x2470;
            break;
        case 1:
            slots = (u8*)self + 0xB30;
            n = *(s32*)((u8*)self + 0xC30);
            sounds = (u8*)self + 0x2480;
            break;
        case 3:
            slots = (u8*)self + 0x910;
            n = self->fA10;
            sounds = (u8*)self + 0x2450;
            break;
        }
        UpdateEightEntryBlendWeights(self, slots, n);
        PhasePlayer* ph = (PhasePlayer*)self->watched2230;
        f32 t = WrapModulo((ph->time + D_00274B64 * ph->speed) / ph->clip->length, 1.0f);
        if (self->f2674 == (s32)self->f2678) {
            s32 m = self->f2684;
            if (m < 3) {
                if (m > 0) {
                    *(f32*)&self->f26A0 >?= (m == 1 ? *(f32*)((u8*)self + 0xA40) : *(f32*)((u8*)self + 0xA20));
                }
            }
        }
        PlayPhaseCrossingSound(self, sounds, t);
        break;
    }
    case 0x14: {
        switch (self->f239C) {
        case 4:
            UpdateSixEntryBlendWeights(self, (u8*)self + 0xE30, *(s32*)((u8*)self + 0x1010), self->watched2230);
            break;
        case 2:
            UpdateSixEntryBlendWeights(self, (u8*)self + 0xC40, *(s32*)((u8*)self + 0xE20), self->watched2230);
            break;
        case 3:
            UpdateSixEntryBlendWeights(self, (u8*)self + 0x720, self->f900, self->watched2230);
            break;
        }
        PhasePlayer* ph = (PhasePlayer*)self->watched2230;
        f32 t = WrapModulo((ph->time + D_00274B64 * ph->speed) / ph->clip->length, 1.0f);
        PlayPhaseCrossingSound(self, (u8*)self + 0x2440, t);
        break;
    }
    case 0x10:
        if (self->f239C == 4) {
            f32 k = 5.0f;
            u8* p1 = (u8*)self + 0x1190;
            func_001719E8(self, (s32)self->f628, (s32)self->f620, self->f250C, k, p1);
            u8* p2 = (u8*)self + 0x1290;
            func_001719E8(self, (s32)self->f62C, (s32)self->f624, self->f2510, k, p2);
            CollectPlayerTargetSpans((TargetPlayerView*)self, (TargetProbe*)p1, (u8*)self->f250C);
            CollectPlayerTargetSpans((TargetPlayerView*)self, (TargetProbe*)p2, (u8*)self->f2510);
        }
        break;
    }
}
