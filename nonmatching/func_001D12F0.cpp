// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 368/388 (94.8%), checked 2026-11-07
#include "common.h"
#include "game_clock.h"
#include "globals.h"
#include "switched_collider.h"
#include "vu0.h"
extern float D_00274EF0[3];
// NEAR (2026-11-07, worker vu0-e6): the code is retail's but two scheduling points: retail loads
// the address of D_00274EF0 (addiu s0) and converts the second dot product (mtc1 f21) before the
// arguments of the first ApproachValueWithRamp are set, here after them (5 lines differ).
// Tried: the clock's step and the ramp in locals, the dot products in the other order (worse),
// the limit in a local.

struct TargetMover {
    struct Vt { u8 pad0[4]; void (*placeAt)(TargetMover* self, f32 angle, s32 flag, void* out); };
    const Vt* vt;           // 0x00
};
// What func_001D12F0 reads of the record at Player+0x23BC.
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
struct TargetPlayerView {
    u8 pad0[0x23BC];
    TargetFrameRecord* record;  // 0x23BC
};

void TransformDirectionBetweenFrames(void* frame, s32 a, void* in, void* out);
void ApproachValueWithRamp(f32 value, f32 target, f32 dt, float* ramp, f32* out);
void AddColliderForce(Player* self, void* v);
void func_0016FD70(Player* self);

void func_001D12F0(Player* self)
{
    Vec02 dir;
    Vec02 force;
    Vec02 k;
    f32 bounds[2];
    if (self->f239C == 4) {
        TargetFrameRecord* rec = ((TargetPlayerView*)self)->record;
        if (rec->active != 0) {
            TargetMover* m = rec->mover;
            if (m->vt->placeAt != 0) {
                m->vt->placeAt(m, *(f32*)((u8*)self + 0x23C0), 0, &dir);
            }
            TransformDirectionBetweenFrames(rec->frame, 0, &dir, &dir);
            f32 down = Vu0::ToFloat(Vu0::Dot(Vu0::Q(dir), Vu0::Q(self->gravity)));
            f32 along = Vu0::ToFloat(Vu0::Dot(Vu0::Q(dir), Vu0::Q(self->v150)));
            float* ramp = D_00274EF0;
            ApproachValueWithRamp(along, rec->limit, g_gameClock.dt, ramp, &bounds[0]);
            ApproachValueWithRamp(along, -rec->limit, g_gameClock.dt, ramp, &bounds[1]);
            f32 v = rec->scale * down;
            f32 hi = bounds[0];
            f32 lo = bounds[1];
            if (v < lo) {
                v = lo;
            } else if (hi < v) {
                v = hi;
            }
            Vu0::Q(k) = Vu0::FromFloat(v - down);
            Vu0::Q(force) = Vu0::MulX(Vu0::Q(dir), Vu0::Q(k));
            AddColliderForce(self, &force);
        }
    }
    func_0016FD70(self);
}
