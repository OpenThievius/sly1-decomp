// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 182/320 (56.9%), checked 2026-11-07
// NEAR: same instructions and VU0 arithmetic; differs in registers and one spill: retail hoists s4+0xD0 (the rotation's address, for rows 1 and 2) into s8 before the loop and keeps the vertex counter in a spill slot, with the current/target pointers in s1/s0; ours recomputes the address in a3 each iteration and spills it. A Mat02* local for the rotation gave a worse result (all three rows through the pointer).
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "fpu.h"
#include "vu0.h"
#include "globals.h"
#include "object_link.h"
#include "attachment.h"
#include "pad_record.h"
#include "game_clock.h"

extern f32 D_00274B68[3];
f32 ApproachValueWithRamp(void* p, s32 zero, f32 a, f32 b, f32 c);

void func_001C4C20(TurningCollider* self)
{
    Collider* other = (Collider*)self->f6DC;
    if (other != 0) {
        Vec02* src = (Vec02*)other->mesh.verts;
        Vec02* cur = (Vec02*)self->mesh.verts;
        Vec02* dst = *(Vec02**)self->hook;
        for (s32 i = other->mesh.vertCount - 1; i >= 0; i--) {
            Vec02 world;
            Vu0::Q(world) = Vu0::Add(Vu0::Q(other->pos), Vu0::Rotate(other->rot, Vu0::Q(*src)));
            f32* w = (f32*)&world;
            f32* c = (f32*)cur;
            f32* d = (f32*)dst;
            for (s32 k = 2; k >= 0; k--) {
                f32 t = ApproachValueWithRamp(D_00274B68, 0, *c, *w, g_gameClock.dt);
                *d = (t - *c) / g_gameClock.dt;
                c++;
                d++;
                w++;
            }
            src++;
            cur++;
            dst++;
        }
    }
}
