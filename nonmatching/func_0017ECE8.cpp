// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 810/812 (99.8%), checked 2026-11-11
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
#include "common.h"
#include "point_object.h"
#include "collider.h"
#include "globals.h"
#include "shapes.h"
#include "placed_object.h"
#include "asm_func.h"
#include "fpu.h"
#include "vu0.h"

extern f32 D_0026185C;
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void* AllocateBackMemory(s32 size);
void SolveActiveSetSystem(s32 count, u8* data, f32* values, f32* out);
s32 func_0017ECE8(Player* self)
{
    Vec02 acc;
    ContactRow03* row;
    Contact03* c;
    u32 bits;
    s32 n = 0;
    f32 now = D_0026185C;
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
