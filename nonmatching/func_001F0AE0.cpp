// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 976/984, checked 2026-11-08
// NEAR: one block of case 3. GCSE (PRE) takes the join's load of the cursor (for `back`) as
// available to `target = self->cursor` and to the f560 != 0 path, so ours keeps the cursor in a1
// (bnez/move s3,a1) where retail loads it again on the f560 path (bnezl delay) and for target
// (b; lw s3). The file built with -fno-gcse gives EXACT, but 26 other functions of the file need
// GCSE, so something in the original between the two reads kills memory (a store or an
// out-parameter): not found. Tried: `back` as one expression, target as a ternary.
#include "common.h"
#include "warp_page.h"
#include "screen_element.h"
#include "game_clock.h"
#include "ramp_profile.h"
#include "animation.h"
#include "vu0.h"

extern T217D_3D0 D_0026F138;
extern s32 D_00275BF0[10];
extern f32 D_00276258[4];
extern f32 D_00276268[4];
extern f32 D_00276278[4];
extern f32 D_00276288[4];
void SelectWarpPageEntry(WarpPage* self, s32 value);
s32 IsWarpEntryAvailable(WarpPage* self, s32 kind, s32* outA, s32* outB);
s32 GetCurrentWarpEntry(void);
void SetPendingWarpEntry(s32 unused, s32 a, s32 b);
void SetScreenElementHoldTime(void* self, f32 t);
void ReplaceAnimationPlayer(Animation* a, WarpPage* b, s32 c, void* d, f32 e, f32 f);
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, void* p, f32* out);
f32 WrapAngle(f32 a);
void UpdatePlacedObject(void* self, f32 dt);
void StopAnimationPlayer(s32 player);
u128 ApproachPointWithRamp(u128 cur, u128 target, const f32* ramp, s32 flag, f32 dt);

// Every frame: by mode, closes the page's animations (0), moves the highlight to the cursor's
// entry (2) or plays the opening of the chosen one (3); then eases every entry's values.
void UpdateWarpPage(WarpPage* self, f32 dt)
{
    UpdatePlacedObject(self, dt);
    switch (self->mode) {
    case 0:
        if (self->f2EC != 0) {
            StopAnimationPlayer(self->f2EC);
            self->f2EC = 0;
        }
        if (self->f2F0 != 0) {
            StopAnimationPlayer((s32)self->f2F0);
            self->f2F0 = 0;
        }
        if (self->f2EC == 0 && self->f2F0 == 0) {
            self->desc->m03(self);
        }
        break;
    case 2:
        if (self->f2D8 != self->cursor) {
            SelectWarpPageEntry(self, self->cursor);
            if (IsWarpEntryAvailable(self, self->f2D8, 0, 0) != 0) {
                self->entries[self->f2D8].f10 = 0.0f;
            }
            if (IsWarpEntryAvailable(self, self->cursor, 0, 0) != 0) {
                self->entries[self->cursor].f10 = 1.0f;
            }
            self->entries[9].f10 = self->entries[1].f10;
            self->f2D8 = self->cursor;
        }
        *(u128*)&self->q540 = ApproachPointWithRamp(*(u128*)&self->q540, *(u128*)&self->q550, D_00276258, 0, g_gameClock.step);
        break;
    case 3:
        if (self->f2D8 != self->cursor) {
            if (self->f560 == 0) {
                SelectWarpPageEntry(self, self->cursor);
                SetScreenElementHoldTime(&D_0026F138, 0.0f);
                D_0026F138.vt->m14(&D_0026F138);
            }
            s32 back = 0;
            if (self->cursor != 1 || self->f560 != 0) {
                back = 1;
            }
            s32 target;
            if (back != 0) {
                target = self->cursor;
            } else {
                target = GetCurrentWarpEntry();
            }
            Animation* anim = self->entries[target].f00;
            if (D_00275BF0[0] != 2) {
                self->entries[GetCurrentWarpEntry()].f10 = 0.0f;
                self->entries[self->cursor].f10 = 1.0f;
                self->entries[self->cursor].f08 = 1.0f;
                self->entries[9].f10 = self->entries[1].f10;
            }
            if (anim != 0) {
                f32 start = 0.0f;
                if (back != 0) {
                    start = anim->length;
                }
                f32 rate = 1.0f;
                if (back != 0) {
                    rate = -1.0f;
                }
                ReplaceAnimationPlayer(anim, self, 1, &self->f2F0, start, rate);
                SetPendingWarpEntry((s32)self, target, back);
            }
            self->f560 = 0;
            self->f2D8 = self->cursor;
        }
        break;
    }
    if (self->mode != 0) {
        for (s32 i = 0; i < 11; i++) {
            WarpEntry* e = &self->entries[i];
            e->f24 = ApproachValueWithRamp(e->f24, e->f28, g_gameClock.step, D_00276268, 0);
            e->phase = WrapAngle(e->phase + e->speed * g_gameClock.step);
            PlacedObject* a = (PlacedObject*)e->f04;
            PlacedObject* b = (PlacedObject*)e->f0C;
            if (a != 0) {
                a->f298->level = ApproachValueWithRamp(a->f298->level, e->f08, dt,
                                                       self->f2E0 == 2 ? D_00276278 : D_00276288, 0);
            }
            if (b != 0) {
                b->f298->level = ApproachValueWithRamp(b->f298->level, e->f10, dt,
                                                       self->f2E0 == 2 ? D_00276278 : D_00276288, 0);
            }
        }
    }
}
