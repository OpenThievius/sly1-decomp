// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 769/848 (90.7%), checked 2026-11-08
// NIGHT-LOW2 (2026-11-08): the pass and made counters are s32 (retail's slti), the slot of the search loop is a variable of its own (cand: one variable across the loop and the pick kept the slot table's base in s3), made is declared before the rotation pointer, and the wait's low bound is read as self->f43C (loaded before the f458 store, as retail's). Still differs: the prologue's order (retail forms posp in v1 first and stores it last), the length's qmfc2 (v1 in retail), the 20 of the pick's index product and the end's constant 1 and clock address (v0/v1 swapped).
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "state_notifier.h"
#include "world.h"
#include "camera.h"
#include "game_progress.h"
#include "effect.h"
#include "screen_element.h"
#include "font.h"
#include "gauge_manager.h"
#include "pooled_object.h"
#include "masked_collider.h"
#include "object_link.h"
#include "scatter_controller.h"
#include "shapes.h"
#include "object_pool.h"
#include "owner_message.h"
#include "vu0.h"
// NEAR (2026-11-08, worker vu0w4-e1): the logic, the frame (288 bytes), the stack slots of the three
// pointers and every call are retail's. Differing: the callee-saved registers (retail: slot s0,
// index s1, pass s3, best s4, player s5, constant 1 in s6, count s7, the camera's high half in s8; here
// the slot table's address is kept in s3 across the pass and the rest shift by one), and the
// order of the prologue's address computations. Tried: a slot pointer stepped with the index
// (adds another register), pointer variables in other orders.
extern f32 g_gameClock[];
extern u8 g_camera[];
extern u8 D_00248D30[];
void ChooseObjectPoolItem(ObjectPool* p);
s32 func_001A8C90(ObjectPool* h, s32 v);
s32 GetObjectWorldPosition(void* p, f32* out);
s32 GetObjectWorldRotation(void* p, f32* out);
s32 CreateAnimationPlayerWithoutPresetTargets(void* a, void* b, s32 c, void* out, f32 fa, f32 fb);
void AddAnimationPlayerRecordCallback(void* a, GaugeManager* self);
f32 RandomFloatInRange(f32 a, f32 b);
s32 ProjectPointToCamera(void* cam, void* point, f32* out);
void* GetActiveSwitchedCollider(void);
extern const f32 D_00249FB4;

void func_0014C858(GaugeManager* self)
{
    Vec02 anchor;
    Vec02 pos;
    f32 screen[2];
    Vec02 rot[3];
    Vec02* posp = &pos;
    s32 made = 0;
    Vec02* rotp = &rot[0];
    f32* wait = &self->f43C;
    s32 pass;
    s32 best;
    s32 i;
    f32 bestDist;
    GaugeSlot* slot;
    void* player;

    do {
        if (self->f458 >= 2) {
            self->f45C = D_00249FB4;
            return;
        }
        ChooseObjectPoolItem((ObjectPool*)self->f420);
        if (((ObjectPool*)self->f420)->f48 == 0) {
            return;
        }
        player = GetActiveSwitchedCollider();
        best = -1;
        bestDist = 0.0f;
        pass = 0;
        do {
            for (i = 0; i < self->slotCount; i++) {
                GaugeSlot* cand = &self->slots[i];
                if (cand->taken != 0 || cand->key != 0) {
                    continue;
                }
                GetObjectWorldPosition(cand->f4, (f32*)&pos);
                if (pass == 0) {
                    ProjectPointToCamera(*(void**)g_camera, (u8*)cand->obj + 0x140, screen);
                    if (screen[0] < -1.0f || 1.0f < screen[0] || screen[1] < -1.0f || 1.0f < screen[1]) {
                        continue;
                    }
                }
                f32 dist = Vu0::ToFloatMoved(Vu0::Length(Vu0::Sub(Vu0::Q(((PlacedObject*)player)->v140), Vu0::Q(pos))));
                if (made == 1) {
                    dist = dist + Vu0::ToFloatMoved(Vu0::Length(Vu0::Sub(Vu0::Q(anchor), Vu0::Q(pos))));
                }
                if (bestDist < dist) {
                    bestDist = dist;
                    best = i;
                }
            }
            if (best >= 0) {
                break;
            }
            pass++;
        } while (pass < 2);
        if (best < 0) {
            return;
        }
        ObjectPool* h = (ObjectPool*)self->f420;
        ContactAgent* agent = (ContactAgent*)h->f48;
        slot = &self->slots[best];
        func_001A8C90(h, 0);
        GetObjectWorldPosition(slot->f4, (f32*)posp);
        GetObjectWorldRotation(slot->f4, (f32*)rotp);
        agent->desc02()->m1D(agent, posp);
        agent->desc02()->m1E(agent, (Mat02*)rotp);
        agent->desc02()->m20(agent, (Vec02*)D_00248D30);
        agent->desc02()->m21(agent, (Vec02*)D_00248D30);
        if (made == 0) {
            anchor = pos;
        }
        CreateAnimationPlayerWithoutPresetTargets(slot->f8, slot->obj, 0, &slot->key, 0.0f, 1.0f);
        made++;
        AddAnimationPlayerRecordCallback(slot->key, self);
        self->f458 = self->f458 + 1;
        self->f45C = g_gameClock[1] + RandomFloatInRange(self->f43C, wait[1]);
        agent->fC20 = slot;
        slot->taken = 1;
        agent->fC24 = *(f32*)(self->buf430 + 0x14);
    } while (made < 2);
}
