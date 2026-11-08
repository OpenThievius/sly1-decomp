// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 155/172 (90.1%), checked 2026-11-08
// Still differs (2026-11-08, night-lwx): with FromFloatAt as "rV" both weights' lui/lw are retail's; left: retail loads the table (lw v1,0(s0)) before the vmulax and calls through v0, storing vf4's slot in the jalr's delay slot; here the table is loaded after the stores, into v0.
// NEAR: registers and order: retail loads weight t=D_00275CD4 with lw into vf4 first (FromFloatAt, stored in a Scalar-like slot after the arithmetic: needs a ScalarAt helper), s in vf2 and b in vf3; here s and b swap registers and the first lui pair differs.
// In the context of its file, src/main/file_1E88D0.cpp.
// The source file from 0x1E88D0 to 0x1F2758, built whole (config/us/files.tsv): it starts where
// file_1E5378.cpp's _GLOBAL_$I$ ends and ends with its own (func_001F2738, in retail's constructor
// list D_0027B130). Its .rodata runs 0x24E600-0x24E840 and its .data 0x275B60-0x276658, the
// zero-initialised D_00276654 last. Named after its first address until what it was is known.
#include "common.h"
#include "globals.h"
#include "vu0.h"

typedef void (*PlayerSlotFn)(Player* g, void* arg);
f32 ArctangentOfRatio(f32 a, f32 b);
f32 D_00275CD0 = 700.0f;
f32 D_00275CD4 = 650.0f;
s32 D_00276298[11][4] = {
    { 1, 10, 10, 5 },
    { 2, 0, 3, 5 },
    { -1, 1, 3, 5 },
    { 2, 10, -1, 1 },
    { 8, -1, 5, 7 },
    { 2, 0, 1, 4 },
    { -1, 7, 7, 8 },
    { 6, 8, 4, 6 },
    { 6, -1, 7, -1 },
    { -1, -1, -1, -1 },
    { 0, -1, -1, 0 }
};
f32 WrapAngle(f32 a);
void TurnColliderTowardHeading(Player* self);
void SetPlayerState(Player* self, s32 a, s32 b);

static inline u128 ScalarAt(const f32& f)
{
    Vu0::Slot t;
    Vu0::Q(t) = Vu0::FromFloatAt(f);
    return Vu0::Q(t);
}
void ContinueBeatPressColliderRequest(PlacedObject* from, Player* self)
{
    Vec02 dir;
    Vu0::Q(dir) = Vu0::MulXSum(Vu0::Q(from->m110.r[0]), Vu0::Scalar(-D_00275CD0), Vu0::Q(from->m110.r[2]), ScalarAt(D_00275CD4));
    ((PlayerSlotFn*)self->desc)[0x90 / 4](self, &dir);
    self->f638 = WrapAngle(ArctangentOfRatio(dir.y, dir.x) + 3.1415927f);
    TurnColliderTowardHeading(self);
    SetPlayerState(self, 4, 0x2B);
}
