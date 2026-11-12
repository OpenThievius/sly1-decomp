// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 572/580, checked 2026-11-12
// w32-sizeA (2026-11-11): first differing block is the head after bc1f (block 2, the splat and the target test); the loop, the doubled splat and the tail align. Retail's head ends with S (GPR v0, the pextlw output) still live into both arms and a VU copy V (vf2) set from it in the head and stored to size; the then arm reads vf2, the else arm stores hi from S (sq v0) and gets a fresh qmtc2 (vf3, raised into the beqz slot by reorg). Ours keeps one pseudo (the asm output, TI 123 in the cse dump) that global-alloc puts in vf2, so every use is vf2. What it needs: a VU pseudo distinct from the asm's output whose only head use is size's store, with the else arm's uses left on the output. Hypothesis, not tested: cprop rewrites the arms' uses of V back to S (other blocks), and reload then reuses vf2 for the fall-through arm by find_equiv_reg (the copy is in the same extended block), giving retail's code. Two more forms ruled out here (both 127/145, the same code): `u128 s = Vu0::Splat(...)` stored to size and read by both arms, and the else arm as `Q(hi) = Splat(self->margin); lo = MulX(Q(hi), ...)` (CSE'd into the first splat).
// BYTES 0/580, checked 2026-11-07
// NEAR: the loop and the tail are retail's instruction for instruction (the points taken by index from pts, so loop.c's reduced pointer is copied in the preheader: addu v1; move s0,v1). One instruction short in the head: retail keeps the splat in a GPR pseudo (pextlw v0,v1,v1), copies it to vf2 for the size store and the then arm, and in the else arm stores hi from v0 and copies it again to vf3 for the MulX; here one VU0 pseudo serves all. cse1 does make that split for a named splat, and gcse's copy propagation folds it (docs/TOOLCHAIN.md, "A splat split between a GPR and a VU0 copy"). Tried the splat as a u128 or Vu0::Vec read by either arm, Vec::Of reads, a second Splat, hi = size after the MulX, MulX of hi, s reassigned, the arms swapped, Set. 2026-11-10: with -fno-gcse (diagnostic) the named form keeps two VU0 pseudos (vmove vf3,vf2 in the beqz slot), so cprop alone merges them, and retail's GPR needs the else pseudo to carry the size store too (asm -> S; H = S; size = S; then: H; else: S); cprop folds any then-arm use of H to S unless it sits in a PARALLEL or a block that sets S first (docs/toolchain/gcse.md). Also tried: f32 m named before the test, one u128 reused for both splats (both VU0, worse).
// In the context of its file, src/main/file_1549C8.cpp.
#include "common.h"
#include "effect_spawner.h"
#include "world_listed_object.h"
#include "owned_record.h"
#include "list_iter.h"
#include "vu0.h"

f32 WrapModulo(f32 x, f32 m);

void WrapSpawnerParticlesIntoBox(EffectSpawner* self)
{
    if (!(1e-4f < self->margin)) {
        return;
    }
    Vec02 size;
    Vec02 lo;
    Vec02 hi;
    Vu0::Q(size) = Vu0::Splat(self->margin);
    if (self->rec->target != 0) {
        Vu0::Q(lo) = Vu0::Sub(Vu0::Q(((PlacedObject*)self->rec->target)->v140), Vu0::Q(size));
        Vu0::Q(hi) = Vu0::Add(Vu0::Q(((PlacedObject*)self->rec->target)->v140), Vu0::Q(size));
    } else {
        hi = size;
        Vu0::Q(lo) = Vu0::MulX(Vu0::Q(size), Vu0::Scalar(-1.0f));
    }
    Vu0::Q(size) = Vu0::Splat(self->margin + self->margin);
    if (self->rec->f120 != 0) {
        return;
    }
    WorldListedObject* w = (WorldListedObject*)self->held348;
    if (w == 0) {
        return;
    }
    for (OwnedRecord* r = (OwnedRecord*)w->members.head; r != 0; r = r->next) {
        Vec02* pts = r->points[r->bank];
        for (s32 i = 0; i < r->count; i++) {
            Vec02* p = &pts[i];
            Vec02 delta;
            ListFrame frame;
            if (p->x < lo.x || hi.x < p->x) {
                delta.x = lo.x + WrapModulo(p->x - lo.x, size.x) - p->x;
                p->x += delta.x;
            }
            if (p->y < lo.y || hi.y < p->y) {
                delta.y = lo.y + WrapModulo(p->y - lo.y, size.y) - p->y;
                p->y += delta.y;
            }
            if (p->z < lo.z || hi.z < p->z) {
                delta.z = lo.z + WrapModulo(p->z - lo.z, size.z) - p->z;
                p->z += delta.z;
            }
        }
    }
}
