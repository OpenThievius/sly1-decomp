// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 536/556 (96.4%), checked 2026-11-07
// NEAR: right code everywhere but two places: the lui of D_0024A824 sits before the swc1 of f5A0 in retail (after it in ours), and the key of state 3 (0x2F1, or 0x2F2 when the entry table's +0x318 is 1) is chosen by branches in retail (beqz, then beql with the li in its delay slot) and by a movz in ours, whatever the source form (if chain, switch, preset key).
#include "common.h"
#include "switched_collider.h"
#include "c52.h"
#include "entry_table_object.h"
#include "zone_collider.h"
#include "target_follower.h"
#include "globals.h"
#include "game_clock.h"
#include "key_record.h"
#include "base_object.h"
#include "placed_object.h"
#include "world.h"
#include "game_progress.h"
#include "shapes.h"
#include "asm_func.h"
#include "vu0.h"

void PlaceTargetFollowerOnFollowed(TargetFollower* self);
f32 ArctangentOfRatio(f32 a, f32 b);
Collider* GetActiveSwitchedCollider(void);
s32 RandomIntInRange(s32 a, s32 b);
void ConvertPositionToWorld(void* arg, Vec3* out);

extern f32 D_0024A824[];
extern const Mat02 D_002483D0;
s32 GetObjectWorldPosition(void* p, Vec02* out);
f32 RandomFloatInRange(f32 a, f32 b);
s32 RandomIntInRange(s32 a, s32 b);
void SetStateWalkerTarget(void* p, s32 key);
void* ChooseEntryTableObject(EntryTableObject* self);
extern GameClock g_gameClock;

struct FollowerTrail { u8 pad00[0x40]; Vec02 v40; Vec02 v50; Vec02 v60; Vec02 v70; };

void func_0016DAC0(TargetFollower* self, s32 mode)
{
    s32 key;
    if (self->f598 == mode) {
        return;
    }
    if (self->f598 == 1) {
        PlaceTargetFollowerOnFollowed(self);
    }
    self->f598 = mode;
    self->f59C = g_gameClock.time;
    switch (mode) {
    case 0: {
        Vec02 pos;
        Vec02 d;
        key = 0x2EF;
        ConvertPositionToWorld(self->f558->f7A4, (Vec3*)&pos);
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->v140));
        self->f5A0 = ArctangentOfRatio(d.y, d.x);
        f32 big = D_0024A824[0];
        self->f5AC = big;
        self->f5A8 = big;
        break;
    }
    case 3: {
        Vec02 pos;
        Vec02 d;
        GetActiveSwitchedCollider();
        EntryTableObject* table = (EntryTableObject*)self->f558->f7AC;
        if (self->f5D4 <= 0) {
            self->f590 = self->f594;
            FollowerTrail* t = (FollowerTrail*)self->f594;
            t->v40 = g_player->v140;
            t = (FollowerTrail*)self->f594;
            t->v50 = D_002483D0.r[0];
            t->v60 = D_002483D0.r[1];
            t->v70 = D_002483D0.r[2];
            self->f5D4 = RandomIntInRange(1, 3);
        } else {
            self->f590 = ChooseEntryTableObject(table);
            self->f5D4--;
        }
        switch (table->mode318) {
        default:
            key = 0x2F1;
            break;
        case 0:
            key = 0x2F1;
            break;
        case 1:
            key = 0x2F2;
            break;
        }
        GetObjectWorldPosition(self->f590, &pos);
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->v140));
        self->f5A0 = ArctangentOfRatio(d.y, d.x);
        break;
    }
    case 1:
        self->f574 = g_gameClock.time + 1.0f;
        key = 0x2F0;
        break;
    case 2: {
        switch (((EntryTableObject*)self->f558->f7AC)->mode318) {
        default:
            key = 0x2F4;
            break;
        case 0:
            key = 0x2F5;
            if (RandomFloatInRange(0.0f, 1.0f) < 0.5f) {
                key = 0x2F4;
            }
            break;
        case 1:
            key = 0x2F6;
            break;
        }
        break;
    }
    case 4:
        key = 0x2F3;
        break;
    }
    SetStateWalkerTarget(self->f554, key);
}
