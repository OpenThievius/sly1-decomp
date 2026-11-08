// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1136/1140 (99.6%), checked 2026-11-08
// NEAR (2026-11-08, worker night-large1): an effect spawner's update (the delay, the check that
// it or one of its listed objects is near the camera, then the count each mode spawns, the burst
// and the rate's redraw), retail's code but for one pair of loads: in mode 3 the bounds of the
// active time are loaded f13 first where this C loads f12 first (mode 2's same call matches).
// The list walk is a guarded do-while with gotos, as the only form found that gives retail's
// rotated loop; the frame needs ListFrame's 16 bytes.
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

void* FillMemory(void* p, s32 v, u32 n);
f32 RandomFloatInRange(f32 a, f32 b);
s32 IsObjectAttached(void* obj);
extern f32 g_gameClock[];
s32 IsListEmpty(List01* l);
struct SpawnFlags { s32 z; s32 b; s32 c; SpawnFlags() { FillMemory(this, 0, sizeof(*this)); } };

void RandomizeEffectSpawnerDelay(EffectSpawner* self);
void UpdatePlacedObject(void* self, f32 dt);
s32 CountListItems(void* list);
void func_00155868(EffectSpawner* self);
void SetEffectSpawnerActiveFor(EffectSpawner* self, f32 f);
void SetEffectSpawnerActiveForever(EffectSpawner* self);
s32 IsEffectSpawnerActive(EffectSpawner* self);
void SpawnEffectsFromRecord(s32 count, Rec50* rec, SpawnFlags* p);

void func_00155AB0(EffectSpawner* self, f32 dt)
{
    ListFrame frame;

    if (self->f34C != 0) {
        RandomizeEffectSpawnerDelay(self);
    }
    UpdatePlacedObject(self, dt);
    if (self->f310 != -1) {
        return;
    }
    if (!IsListEmpty((List01*)self->list314)) {
        PlacedObject* o = *(PlacedObject**)self->list314;
        Camera* cam;
        s32 near;
        f32 r;
        u128 d;
        if (o == 0) {
            return;
        }
        do {
            if (!(o->flags & ((u64)0x8000 << 23)) && IsObjectAttached(o)) {
                if (o->parent == 0) {
                    goto spawn;
                }
                cam = g_camera;
                near = 1;
                r = o->f80 * cam->fB0;
                d = Vu0::Sub(Vu0::Q(o->v140), Vu0::Q(cam->f40));
                if (!(r * r > Vu0::ToFloatMoved(Vu0::Dot(d, d)))) {
                    near = 0;
                }
                if (near) {
                    goto spawn;
                }
            }
            o = *(PlacedObject**)((u8*)o + 0x320);
        } while (o != 0);
        return;
    } else {
        if (self->parent != 0) {
            Camera* cam = g_camera;
            f32 r = self->f80 * cam->fB0;
            s32 far = 1;
            if (!(r * r < Vu0::ToFloat(Vu0::Dot(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(cam->f40)),
                                                 Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(cam->f40)))))) {
                far = 0;
            }
            if (far) {
                return;
            }
        }
    }
spawn:
    if (IsEffectSpawnerActive(self)) {
        return;
    }
    s32 n = 0;
    switch (self->f2D4) {
    case 3: {
        f32 acc = self->f33C + self->f328 * self->f334 * dt;
        n = (s32)acc;
        self->f33C = acc - (f32)n;
        if (1.0f < (f32)n) {
            if (self->f2D8 >= 0) {
                if (!(n < self->f2D8)) {
                    n = self->f2D8;
                }
                self->f2D8 -= n;
            }
            if (self->continuous != 0) {
                SetEffectSpawnerActiveForever(self);
            } else if (RandomFloatInRange(0.0f, 1.0f) <= self->chance) {
                SetEffectSpawnerActiveFor(self, RandomFloatInRange(self->active.lo, self->active.hi));
            } else {
                break;
            }
            self->f328 = RandomFloatInRange(self->f2DC, self->f2E0) * 60.0f;
        }
        break;
    }
    case 2:
        n = (s32)self->f328;
        if (self->f2D8 >= 0) {
            if (!(n < self->f2D8)) {
                n = self->f2D8;
            }
            self->f2D8 -= n;
        }
        if (self->continuous != 0) {
            SetEffectSpawnerActiveForever(self);
        } else if (RandomFloatInRange(0.0f, 1.0f) <= self->chance) {
            SetEffectSpawnerActiveFor(self, RandomFloatInRange(self->active.lo, self->active.hi));
        }
        self->f328 = RandomFloatInRange(self->f2DC, self->f2E0);
        break;
    case 0: {
        f32 acc = self->f33C + self->f328 * self->f334 * dt;
        n = (s32)acc;
        self->f33C = acc - (f32)n;
        if (n == 0) {
            goto timer;
        }
        if (self->f2D8 >= 0) {
            if (!(n < self->f2D8)) {
                n = self->f2D8;
            }
            self->f2D8 -= n;
        }
        break;
    }
    case 1: {
        n = (s32)(self->f2F4 * self->f334);
        s32 have;
        BaseObject* held;
        if (self->rec->f120 == 0) {
            held = self->held348;
            have = held != 0 ? *(s32*)((u8*)held + 0x620) : 0;
        } else {
            held = self->held344;
            have = held != 0 ? CountListItems((u8*)held + 0x558) : 0;
        }
        s32 left = n - have;
        n = 0; if (left > n) { n = left; }
        break;
    }
    }
    if (n != 0) {
        SpawnFlags p;
        p.z = (s32)&self->held348;
        p.b = (s32)&self->held344;
        p.c = (s32)self;
        void* prev = self->rec->target;
        if (self->id2F8[0] == -1) {
            self->rec->target = self;
        }
        SpawnEffectsFromRecord(n, self->rec, &p);
        self->rec->target = prev;
    }
timer:
    if (self->f330 <= g_gameClock[1]) {
        self->f328 = RandomFloatInRange(self->f2DC, self->f2E0);
        self->f330 = g_gameClock[1] + self->f32C;
    }
    func_00155868(self);
}
