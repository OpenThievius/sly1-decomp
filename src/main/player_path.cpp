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

// The path object (+0x2208): a frame at +0x18, a holder at +0x34 whose descriptor has the
// methods the player calls (slots 1, 2, 8 and 10), and an offset at +0x40 (func_001D1630).
struct PathHolder;
struct PathHolderDesc {
    u8 pad00[4];
    void (*m1)(PathHolder* self, Vec02* pos, f32 t, Vec02* tangent);  // 0x04
    void (*m2)(PathHolder* self, Vec02* out, f32 t, s32 a);           // 0x08
    u8 pad0C[0x20 - 0x0C];
    f32 (*m8)(PathHolder* self);                                      // 0x20: the length
    u8 pad24[0x28 - 0x24];
    void (*m10)(PathHolder* self, Vec02* in, s32 a, s32 b, s32 c, s32 d, f32* out);
};
struct PathHolder {
    PathHolderDesc* desc;
    u8 pad04[4];
    s32 closed;             // 0x08: set, a length wraps around the path (func_001D1630)
    u8 pad0C[4];
    f32* start;             // 0x10: the length the path starts at (func_001D1630)
    f32* first;             // 0x14: the smallest length it takes (func_001D1630)
};
struct PathObject { const Desc01* desc; u8 pad04[0x14]; void* frame; u8 pad1C[0x34 - 0x1C]; PathHolder* holder; u8 pad38[0x40 - 0x38]; Vec02 v40; };

void func_001D1630(Player* self, PathObject* path, Mat02* out, f32 length);

INCLUDE_ASM(func_001D1630);

// What the player watches while it follows the path (+0x2230) in states 0x17 and 0x1B: a record
// whose second word points to an object with a float at +0x34, and a float at +0x14.
struct PathWatch { u8 pad00[8]; struct PathWatchTarget* target; u8 pad0C[8]; f32 f14; };
struct PathWatchTarget { u8 pad00[0x34]; f32 f34; };

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
    func_001D1630(self, (PathObject*)self->f2208, &placed, self->f2410);
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

void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);
void TransformPointBetweenFrames(void* a, void* b, void* c, void* d);
void SetPlayerState(void* self, s32 mode, s32 count);

void func_001D2830(Player* self, PathObject* path)
{
    Vec02 pos;
    Mat02 rot;
    Vec02 local;
    Vec02 world;
    if ((PathObject*)self->f2208 != path) {
        if (self->f2220 == 7) {
            TriggerScriptEvent((void*)self->f2208, 3, 0, 0);
            ((PathObject*)self->f2208)->desc->m18((BaseObject*)self->f2208, self);
            TriggerScriptEvent(path, 2, 0, 0);
            path->desc->m17((BaseObject*)path, self);
        }
        self->f2208 = (s32)path;
        self->f2204 = 0;
        self->f2200 = 0;
        TransformPointBetweenFrames(0, path->frame, &self->v140, &pos);
        if (path->holder->desc->m10 != 0) {
            path->holder->desc->m10(path->holder, &pos, 0, 0, 0, 0, (f32*)((u8*)self + 0x220C));
        }
    }
    func_001D1630(self, path, &rot, *(f32*)((u8*)self + 0x220C));
    self->desc02()->m1E(self, &rot);
    if (path->holder->desc->m2 != 0) {
        path->holder->desc->m2(path->holder, &pos, *(f32*)((u8*)self + 0x220C), 0);
    }
    TransformPointBetweenFrames(path->frame, self, &pos, &local);
    Vu0::Q(local) = Vu0::Sub(Vu0::Q(local), Vu0::Q(*(Vec02*)((u8*)self + 0x23E0)));
    TransformPointBetweenFrames(self, 0, &local, &world);
    self->desc02()->m1D(self, &world);
    SetPlayerState(self, 7, 0x17);
}
