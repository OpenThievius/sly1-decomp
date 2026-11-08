// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 309/332 (93.1%), checked 2026-11-08
// Wave 4 (night-lever1, 4 compiles): with D_00261950/70/80 defined in camera.cpp and Vu0::ScalarAt it differs only in the order of the prologue saves, the head (retail: origin vf1, high-corner constant vf2, dest vf3, low constant vf4; ours: origin vf2, constant vf1) and the last weight's register (retail lw s0, ours v0). Statement orders hi/dir/lo, lo/hi/dir and the origin in a shared local: no better.
// NEAR: The camera's sweep probe. The frame (0xB0), the vectors and the calls are retail's; differs in the order of the prologue saves and in two register choices: retail keeps &g_gameClock in s0 across the call and reloads the step into s0 for the last weight (`lw s0,0x14(s0)`), ours loads it into v0; and retail computes the high corner before the low one with the offset constants in v1/v0 (ours has them swapped). Needs D_00261950 (a float pair), D_00261970 and D_00261980 (Vec02 constants) defined in C, as below, instead of INCLUDE_DATA.
#include "common.h"
#include "vu0.h"
#include "placed_object.h"
#include "world.h"
#include "collider.h"
#include "game_clock.h"
#include "shapes.h"

extern World* g_currentWorld;
extern f32 D_0026194C;
f32 D_00261950[2] = { 1500.0f, 0.0f };
Vec02 D_00261970 = { -250.0f, -250.0f, -250.0f, 0.0f };
Vec02 D_00261980 = { 250.0f, 250.0f, 250.0f, 0.0f };
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void GatherCollidersInBox(World* world, s32 p1, Vec02* lo, Vec02* hi, s32 (*filter)(void*, Collider*), s32 p4, s32* n, Collider*** list);
s32 HasColliderSecondTree(void* unused, Collider* other);
struct Camera;
struct Heading_00145DE8 {
    u8 pad0[0x10];
    Quad16 dir;
    f32 dist;
};
f32 func_00145DE8(Camera* self, void* unused, Quad16* v, Heading_00145DE8* h);
void func_00145B68(void* self, s32 count, Collider** list, f32 (*cb)(Camera*, void*, Quad16*, Heading_00145DE8*), Quad16* origin, Vec02* dir, Vec02* out, f32 radius, f32 maxLength);

// Vu0::Scalar for a float in memory: FromFloatAt into a slot of its own.
static inline u128 ScalarAt(const f32& f)
{
    Vu0::Slot t;
    Vu0::Q(t) = Vu0::FromFloatAt(f);
    return Vu0::Q(t);
}

void func_00145E68(Camera* self, Quad16* origin, Quad16* dest, Vec02* out)
{
    Vec02 dir;
    Vec02 hit;
    Vec02 lo;
    Vec02 hi;
    s32 n;
    Collider** list;
    GameClock* clock = &g_gameClock;
    Vu0::Set(dir, Vu0::DivX(Vu0::Sub(Vu0::Q(*dest), Vu0::Q(*origin)), ScalarAt(clock->step)));
    Vu0::Set(hi, Vu0::Add(Vu0::Q(*origin), Vu0::Q(D_00261980)));
    Vu0::Set(lo, Vu0::Add(Vu0::Q(*origin), Vu0::Q(D_00261970)));
    PushBackMemoryMark();
    GatherCollidersInBox(g_currentWorld, 0, &lo, &hi, HasColliderSecondTree, 0, &n, &list);
    func_00145B68(self, n, list, func_00145DE8, origin, &dir, &hit, D_0026194C, Vu0::ToFloat(Vu0::Length(Vu0::Q(dir))) + D_00261950[0]);
    Vu0::Q(*out) = Vu0::MulAddX(Vu0::Q(*origin), Vu0::Q(hit), ScalarAt(clock->step));
    PopBackMemoryMark();
}
