// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 579/624 (92.8%), checked 2026-11-07
// NEAR: wave 4 e3. 624 bytes, same size and structure; about 190 words, 27 differ and all but a few are registers.
//       The first loop keeps the list in s0 and the count in s1 (retail s1 and s0); the address of the sum is formed after
//       the third allocation's move (retail: before it, in a3); the dot loop's temporaries and its two VU0 registers are
//       swapped (retail loads the second row first, vf1, and multiplies in vf2). ~20 compiles (declaration orders, loop forms).
#include "common.h"
#include "shapes.h"
#include "collider.h"
#include "world.h"
#include "camera.h"
#include "pad_record.h"
#include "fpu.h"
#include "asm_func.h"
#include "vu0.h"
#include "ramp_profile.h"
#include "placed_object.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "game_clock.h"

extern const Vec02 D_00248D30;

struct MeshHit {
    u8 pad0[0x10];
    Vec02 point;
    u8 pad20[0x10];
};

typedef f32 (*MeshHitWeigh)(void* ctx, void* a, void* b, MeshHit* hit);
s32 CollectMeshHits(void* a0, f32 r, s32 a1, TreeNode03* a2, s32 a3, void* a4, s32 a5, MeshHit* a6);
void* AllocateBackMemory(s32 size);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void SolveActiveSetSystem(s32 count, u8* data, f32* values, f32* out);
void ClampVectorLength(Vec02* in, Vec02* out, f32 limit);
void func_00145B68(void* ctx, s32 count, Collider** objs, MeshHitWeigh fn, f32 r, f32 limit, void* a4, Vec02* origin, Vec02* out)
{
    MeshHit hits[64];
    Vec02 sum;
    s32 total = 0;
    s32 i;
    s32 j;
    f32* p;
    for (i = 0; i < count; i++) {
        Collider* c = objs[i];
        if (c->tree2.nodes != 0) {
            total += CollectMeshHits(a4, r, c->tree2.count2, c->tree2.nodes, 0, &c->mesh2Copy, 0x40 - total, &hits[total]);
        }
    }
    if (total == 0) {
        *out = *origin;
        return;
    }
    PushBackMemoryMark();
    f32* dots = (f32*)AllocateBackMemory(total * total * 4);
    f32* rhs = (f32*)AllocateBackMemory(total * 4);
    f32* weights = (f32*)AllocateBackMemory(total * 4);
    p = dots;
    for (i = 0; i < total; i++) {
        for (j = 0; j < total; j++) {
            *(u32*)p++ = Vu0::ToBits(Vu0::Dot(Vu0::Q(hits[i].point), Vu0::Q(hits[j].point)));
        }
    }
    p = rhs;
    for (i = 0; i < total; i++) {
        *p++ = fn(ctx, a4, origin, &hits[i]);
    }
    SolveActiveSetSystem(total, (u8*)dots, rhs, weights);
    sum = D_00248D30;
    p = weights;
    for (i = 0; i < total; i++) {
        Vu0::Q(sum) = Vu0::MulAddX(Vu0::Q(sum), Vu0::Q(hits[i].point), Vu0::Scalar(*p++));
    }
    ClampVectorLength(&sum, &sum, limit);
    PopBackMemoryMark();
    Vu0::Q(*out) = Vu0::Add(Vu0::Q(*origin), Vu0::Q(sum));
}
