// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 281/364 (77.2%), checked 2026-11-08
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "fpu.h"
#include "globals.h"
#include "object_link.h"
#include "attachment.h"
#include "pad_record.h"
#include "vu0.h"
// NEAR (2026-11-08, night-lever1): Vu0::Copy of the point inside the `all == 0` branch gives retail's vmove and the point in vf4;
// what still differs is the first and third item below (the bnezl shape, and the face count: retail loads it into v0, tests it,
// then moves it to a3 for the loop; ours loads a3 directly; a local n, a while loop and swapping the if/else: no change or worse).
// NEAR (2026-11-07, worker vu0-c): the same instructions but for three things. Retail tests the
// object with bnezl (the hook's load in its slot) and reaches the tail with `b` and li t2,1 in
// the slot; here beqz with li t2,1 in the slot. Before the plane loop retail copies the point
// (vmove.xyzw vf3, vf4) and the face count (lw v0 then move a3, v0), so the point stays in vf4
// for the store; here the point is vf3 throughout, the count is loaded straight into a3 and the
// registers after shift. Tried: the if and else swapped (worse), the point recomputed in the
// plane loop (worse).

// A face of a collision mesh as func_001C4D60 reads it: its plane, the normal and the distance.
struct MeshFace {
    Vec02 normal;           // 0x00
    f32 d;                  // 0x10
    u8 pad14[0x20 - 0x14];
};

void ClearRootObjectStateBits(World* a, void* self, s32 n);
void func_001BBEB8(TurningCollider* self, f32 t);

void func_001C4D60(TurningCollider* self, Collider* other, s32 all)
{
    if (other == self->f6DC) {
        return;
    }
    s32 changed;
    if (other == 0) {
        changed = 1;
    } else {
        changed = 0;
        Vec02* vel = *(Vec02**)self->hook;
        Vec02* out = (Vec02*)self->mesh.verts;
        Vec02* in = (Vec02*)other->mesh.verts;
        for (s32 i = 0; i < other->mesh.vertCount; i++) {
            u128 p = Vu0::Add(Vu0::Q(other->pos), Vu0::Rotate(other->rot, Vu0::Q(in[i])));
            if (all == 0) {
                u128 c = Vu0::Copy(p);
                MeshFace* f = (MeshFace*)self->mesh.faces;
                for (s32 j = 0; j < other->mesh.faceCount; j++, f++) {
                    if (Vu0::ToFloat(Vu0::Dot(c, Vu0::Q(f->normal))) - f->d > 1.0f) {
                        goto next;
                    }
                }
            }
            changed = 1;
            Vu0::Q(out[i]) = p;
            vel[i] = D_00248D30;
        next:;
        }
    }
    if (changed) {
        ClearRootObjectStateBits(self->world, self, 7);
        if (self->hook != 0) {
            func_001BBEB8(self, 0.0f);
        }
    }
    self->f6DC = other;
}
