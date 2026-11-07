// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "game_clock.h"
#include "globals.h"
#include "vu0.h"

// The file's .data, in retail's order; the label only its assembly reads is included.
float D_00274F00 = 35.0f;
float D_00274F04 = 100.0f;
float D_00274F08 = 0.5f;
INCLUDE_DATA(D_00274F0C);
float D_00274F14 = 50.0f;
float D_00274F18 = 1.0f;
float D_00274F1C = 0.400000006f;
float D_00274F20[2] = {10.0f, 0.0f};
float D_00274F28[4] = {1500.0f, 0.0f, 0.5f, 0.0f};

struct TwoEntryBlendEntry {
    u8 pad0[4];
    void* p4;
    u8 pad8[4];
    f32 fC;
};

void BuildCombinedBlendAnimation(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);
void func_0012CD78(f32 f12, f32 f13, void* a0, void* a1, void* a2, s32 a3, void* a4, s32 a5, void* a6, s32 a7);

void CreatePlayerTwoEntryBlend(Player* self)
{
    f32 out[4];
    TwoEntryBlendEntry* e = (TwoEntryBlendEntry*)self->f103C;
    s32 i = 1;
    do {
        func_0012CD78(0.0f, 1.0f, e->p4, self->f614, self, 1, 0, 0, out, 0);
        e->fC = out[2];
        e++;
        i--;
    } while (i >= 0);
    BuildCombinedBlendAnimation(self, 0x10, 2, self->f103C, 0, 0, 0, &self->f105C);
    func_0012CD78(0.0f, 1.0f, self->f1064, self->f618, self, 1, &self->f23E0, 0, 0, 0);
    func_0012CD78(0.0f, 1.0f, self->f1064, self->f614, self, 1, &self->f23F0, 0, 0, 0);
    f32 avg = (self->f23E0 + self->f23F0) * 0.5f;
    self->f23F4 = 0.0f;
    self->f23E4 = 0.0f;
    self->f23F0 = avg;
    self->f23E0 = avg;
}

INCLUDE_ASM(func_001D1630);

// What the player watches while it follows the path (+0x2230) in states 0x17 and 0x1B: a record
// whose second word points to an object with a float at +0x34, and a float at +0x14.
struct PathWatch { u8 pad00[8]; struct PathWatchTarget* target; u8 pad0C[8]; f32 f14; };
struct PathWatchTarget { u8 pad00[0x34]; f32 f34; };

void func_001D1630(Player* self, void* path, Mat02* out, f32 length);
void func_00130748(f32 a, f32 b, f32 c, Mat02* rot, Vec02* vel, Mat02* target, const Vec02* zero, Mat02* out, s32 d, s32 e);
void MultiplyMatrices3x3(Mat02* a, Mat02* b, Mat02* out);
void MatrixToAxisAngle(Mat02* m, Vec02* angle, Vec02* axis);

void func_001D1A80(Player* self)
{
    Mat02 placed;
    Mat02 goal;
    Mat02 delta;
    Vec02 axis;
    Vec02 k;
    Vec02 angle;
    func_001D1630(self, (void*)self->f2208, &placed, self->f2410);
    if (self->f2228 == 0x17 || self->f2228 == 0x1B) {
        PathWatch* w = (PathWatch*)self->watched2230;
        f32 dt = g_gameClock.dt;
        f32 t = w->target->f34 - w->f14;
        func_00130748(dt >? t, dt, 1.0f, &self->rot, &self->v160, &placed, &D_00248D30, &goal, 0, 0);
    } else {
        goal = placed;
    }
    MultiplyMatrices3x3(&self->rot, &goal, &delta);
    MatrixToAxisAngle(&delta, &angle, &axis);
    Vu0::Q(k) = Vu0::FromFloat(angle.x / g_gameClock.dt);
    Vu0::Q(self->v160) = Vu0::MulX(Vu0::Q(axis), Vu0::Q(k));
}

INCLUDE_ASM(func_001D1BB0);

INCLUDE_ASM(func_001D2518);

void AcquirePadSelectFlag(void* a);
void ShowCountedScreenElement(void* a);
void ReleasePadSelectFlag(void* a);
void HideCountedScreenElement(void* a);

void SetPlayerPadSelectMode(Player* a0, s32 a1)
{
    if (a0->f2718 != a1) {
        if (a0->f2718 == -1) {
            AcquirePadSelectFlag(a0->world);
            ShowCountedScreenElement(a0->world);
        }
        a0->f2718 = a1;
        if (a1 == -1) {
            ReleasePadSelectFlag(a0->world);
            HideCountedScreenElement(a0->world);
        }
    }
}

INCLUDE_ASM(func_001D2830);
