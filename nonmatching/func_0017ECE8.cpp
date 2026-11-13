// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 810/812 (99.8%), checked 2026-11-12
// NEAR: w11 (2026-11-10). 812 bytes, same code and frame; registers differ in one place only:
//       the copy of the spilled down vector into the sum after SolveActiveSetSystem (`lq v0,32(sp);
//       sq v0,0(sp)`, retail v1). That reload register comes from order_regs_for_reload, which
//       skips a hard register holding a live pseudo: retail's v1 means a value in v0 was live
//       across the copy, which is the self->contacts load (v0) of the sum loop's head scheduled
//       before the copy by sched1. Ours has the copy first: both are ready in the cycle after the
//       call with priority 5 (the copy's frame store is a true dependence of the row->head load,
//       an unflagged TImode frame store against a mem/s through a loaded pointer), and the tie
//       falls to INSN_REG_WEIGHT (the copy -1 for down's death, the load +1). Ruled out: acc as a
//       Vu0::Vec (coalesced with down, frame changes), down as a Vec02 in memory (slots swap),
//       acc declared at the copy (slot order), the copy after `p = sol`, the sum loop's
//       self->contacts in a named pointer (CSE folds it; the load still depends on the copy).
//       Confirmed: acc as a u128 whose address the z read takes (`((f32*)&acc)[2]`) makes the
//       copy's store MEM_SCALAR_P at a fixed address, which fixed_scalar_and_varying_struct_p
//       keeps apart from the mem/s load, and gives retail's `lq v1`; but purge_addressof then
//       allocates acc after the weight slot (acc 0x10, slot 0) and the frame grows to 0xA0.
// w15 (2026-11-10): re-scored, unchanged. Read in GCC's source, no other route to the order:
//       the loaded pointer has no alias base, INDIRECT_REF never makes the cast store scalar,
//       an addressable scalar's slot comes at purge time, the load is no birthing insn, the
//       store's weight is at most 0, and self->contacts never conflicts with the frame. acc as
//       a plain u128, or down as a Vec02, cascade (docs/toolchain/alias-classes.md).
// w19 (2026-11-10): re-scored, unchanged. tools/sched1.py on block 34 (the call's block): 871
//       (the copy's store) and 880 (self->contacts) tie at priority 5 at t=4 with one memory
//       unit; weight -1 vs +1 picks the copy. --prio 880=6 or --prio 871=4 gives 880 875 871
//       882, the order that leaves r307 in v0 across the copy. No other rank fits: weight can't
//       (a load is +1, the store at most 0), the birthing raise needs r307 live at the block's
//       end, and the block's insns are retail's. Reload's round robin is not it: the spill regs
//       are v0, v1, vf3 and the reload before 871 (down into vf3 in the rhs loop) starts the
//       rotation at v0 (docs/toolchain/sched1.md, "The copy and the list's load").
// w11 levers that closed the rest (from 46.1%): one row and one contact variable for every
//       loop (retail's a2 and a0 in all four: one pseudo each, as camera.cpp's sibling
//       func_00145B68 reuses i and j); the normals as Vu0::Vec values (the Gram loop's vf4 and
//       the vmove that loop.c hoists out of the inner loop: the Vec parameter copy of na); down
//       a Vu0::Vec; `return -0.1f < acc.z;` (retail's return-0 block after the f690 test); and
//       one u32 for the dots' bits in both loops: set twice, it is no local-alloc quantity, so
//       the Dot's block has two (product first: vf1, the 1.0 vf2) instead of three (the small
//       sort's creation order: the 1.0 first).
// w22 (2026-11-11): re-scored, unchanged. Still the sched1 tie at priority 5 decided by
// INSN_REG_WEIGHT (the copy's -1 against the load's +1); no allocator or GCSE-table lever applies
// (the difference is reload's register for the copy, chosen by what is live after sched1).
// w37-f1 (2026-11-12): re-scored, unchanged (2 words). Established: (1) the order needs no
// barrier. `ct = self->contacts; do { } while (0); Vu0::Q(acc) = down.q;` (a probe: the copy is
// then the first insn after a loop note and waits for the load) gives sched1's 880 before 871
// and reload's `lq v1`, but the note holds in sched2 too: the lw stays ahead of the lq/sq and
// the call's argument moves change order (7 lines), where retail has lq, sq, lw. So retail's
// sched1 had the load first with nothing between them that sched2 still sees. (2) down is a
// spilled pseudo, not a frame variable: with `Vec02 down` the product is written to vf1 by
// local-alloc's tie and the rhs loop's load moves (about 150 lines); retail's vf3 is the output
// reload's register. (3) The callee's return type (s32, f32*, void*, f32) changes nothing:
// a result nobody reads dies at the call. (4) The load's place in the source (`ct =
// self->contacts` before or after the copy, `row = self->contacts->head` before it) changes
// nothing or moves the head's load before the copy (5 lines): the tie is the weight. What is
// left, each needing an insn that leaves no code: a register copy between the contacts load and
// the head load (880's priority 6), a TImode copy feeding the store (871 ready a cycle late), or
// the contacts pointer live at the block's end and set once (the birthing raise). Not found
// in plain source; docs/toolchain/sched1.md, "The copy and the list's load after a call".
// w38-f6 (2026-11-12): audited for PRE's copy pattern (docs/toolchain/gcse.md, "One reaching
// register for every occurrence"): not present. Retail has no `move Y,X` answered by a later
// `move X,Y`, and the one difference is reload's register for the copy, not a pseudo's.
// `bits` (one u32 set in two loops) is the only variable here that carries two values; it
// is what gives the Dot block its two quantities, so it stays.
// w40-fa (2026-11-12): not closer (2 words); the recorded theory is refuted. (1) A CLOBBER
// before the copy does what the theory asked for: with acc a union declared at the copy and
// built in place from a const down (`AccU acc = { down };`, safe_from_p needs the source
// readonly or the constructor goes through a temporary), sched1 issues the CLOBBER and the
// contacts load in the cycle after the call, the store one cycle later, and reload takes v1.
// (2) But sched2 then keeps `lw v0,1152(s1)` ahead of `sq v1,0(sp)`: after reload the load
// through s1 and the frame store conflict (a hard register has no base), so whichever is
// first in sched1's order stays first (-dR trace: 856 lists 847 among its dependents; the
// near miss has the link the other way). Without the link the lw would still go between the
// lq and the sq (it is ready and the sq waits two cycles for the lq). Retail has lq, sq, lw:
// its sched1 kept the store ahead of the contacts load, as ours does. w37's loop-note probe
// showed the same and blamed the note. (3) So what is left is reload alone: at insn 871
// order_regs_for_reload must find v0 forbidden (the hard register live before or after the
// insn) or holding a pseudo that is live there, with r307 not yet set. Nothing visible in
// retail's code is in v0 between the jal and the lw. Not found: what that value is. Checked and
// not it: the copy as a struct assignment from down's storage (`acc = *(Vec02*)&down`: the same
// TImode move, v0); a union or compound-literal accumulator assigned after the call (two
// temporaries, 64 lines); acc declared at the copy takes the Scalar slot's freed sp+0 and
// moves that slot before the copy (6 lines). An empty union initialiser (`U e = {};`) hangs
// this compiler; do not try it.
#include "common.h"
#include "point_object.h"
#include "collider.h"
#include "globals.h"
#include "shapes.h"
#include "placed_object.h"
#include "asm_func.h"
#include "fpu.h"
#include "vu0.h"

extern f32 g_gameTime;
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateBackMemory(s32 size);
void SolveActiveSetSystem(s32 count, u8* data, f32* values, f32* out);
s32 ShouldPlayerLaunchAtTarget(Player* self)
{
    Vec02 acc;
    ContactRow03* row;
    Contact03* c;
    u32 bits;
    s32 n = 0;
    f32 now = g_gameTime;
    if (now - self->f222C < 1.0f) {
        return 0;
    }
    if (now - *(f32*)((u8*)self + 0x2238) < 1.0f) {
        return 0;
    }
    *(f32*)((u8*)self + 0x2238) = now;
    if (self->f690 != 0) {
        return 0;
    }
    Contacts03* ct = self->contacts;
    if (ct != 0) {
        for (row = ct->head; row != 0; row = row->next) {
            for (c = row->head; c != 0; c = c->next) {
                n++;
            }
        }
    }
    if (n == 0) {
        return 0;
    }
    PushBackMemoryMark();
    Vu0::Vec down = Vu0::MulX(Vu0::Vec::Of(g_unitZVector), Vu0::Vec::Scalar(-1.0f));
    f32* gram = (f32*)AllocateBackMemory(n * n * 4);
    f32* rhs = (f32*)AllocateBackMemory(n * 4);
    f32* sol = (f32*)AllocateBackMemory(n * 4);
    f32* p = gram;
    for (row = self->contacts->head; row != 0; row = row->next) {
        for (c = row->head; c != 0; c = c->next) {
            Vu0::Vec na = Vu0::Vec::Of(c->v80);
            if (c->end[0].body != (Collider*)self) {
                na = Vu0::MulX(na, Vu0::Vec::Scalar(-1.0f));
            }
            for (ContactRow03* rb = self->contacts->head; rb != 0; rb = rb->next) {
                for (Contact03* b = rb->head; b != 0; b = b->next) {
                    Vu0::Vec nb = Vu0::Vec::Of(b->v80);
                    if (b->end[0].body != (Collider*)self) {
                        nb = Vu0::MulX(nb, Vu0::Vec::Scalar(-1.0f));
                    }
                    bits = Vu0::ToBits(Vu0::Dot(na, nb).q);
                    *(u32*)p++ = bits;
                }
            }
        }
    }
    p = rhs;
    for (row = self->contacts->head; row != 0; row = row->next) {
        for (c = row->head; c != 0; c = c->next) {
            Vu0::Vec na = Vu0::Vec::Of(c->v80);
            if (c->end[0].body != (Collider*)self) {
                na = Vu0::MulX(na, Vu0::Vec::Scalar(-1.0f));
            }
            bits = Vu0::ToBits(Vu0::Dot(na, down).q);
            *(u32*)p++ = bits;
        }
    }
    SolveActiveSetSystem(n, (u8*)gram, rhs, sol);
    Vu0::Q(acc) = down.q;
    p = sol;
    for (row = self->contacts->head; row != 0; row = row->next) {
        for (c = row->head; c != 0; c = c->next) {
            Vu0::Vec na = Vu0::Vec::Of(c->v80);
            if (c->end[0].body != (Collider*)self) {
                na = Vu0::MulX(na, Vu0::Vec::Scalar(-1.0f));
            }
            Vu0::Q(acc) = Vu0::MulAddX(Vu0::Vec::Of(acc), na, Vu0::Vec::Scalar(*p++)).q;
        }
    }
    PopBackMemoryMark();
    return -0.1f < acc.z;
}
