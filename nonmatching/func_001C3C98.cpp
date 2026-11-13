// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 114/144 (79.2%), checked 2026-11-13
// w44-fa (2026-11-12), 6 compiles: (a) p->anim cannot have a span of 7 in sched1: the length's lwc1 is ready two cycles after the load of p->anim and has the block's top priority, and two insns issue per cycle, so at most three come between (span 4, as now); sched1's trace of this file shows it (33 at t=3, 35 at t=5). (b) Retail's `move v1,v0` is the second add tied to the index: the index dies there, local-alloc's combine_regs gives the store's address the index's v1, and reload_cse turns `addu v1,v1,a1` into the move. So retail has two adds at local-alloc, and the first add's pseudo has no copy to count: its refs are its set and the two loads (3: priority 1666 over 9 insns against p->anim's 2500, the index's quantity 3529 with either form), unless the position's address is a third add that reload_cse deletes as a no-op (`v0 = v1 + a1` again while v0 still holds it), which leaves the first add 2 refs over 2 or 3 insns (3333 to 5000): that needs the velocity load issued before the position's add in sched1, not found. (c) Compiled: the velocity as Vec::Of (it waits for the slot store: 102 of 144); the store through Q or Set with the velocity as Vec::Of (three address registers, 148 bytes); the position as a u128 cast with the store through Q (one address, tied to the index: 136 bytes).
// Wave 23 (w23-vuD, 2026-11-11), 3 compiles: the position and velocity read through an inline's `const ContactEnd03&` parameter (Pushed(c->end[end], origin, k), the store through the expression or Q): 31 and 32 of 36 (worse; the reference's pseudo is one more register and the address is c first). The ranking wall stands.
#include "common.h"
#include "switched_collider.h"
#include "collider.h"
#include "attachment.h"
#include "animation.h"
#include "vu0.h"
// NEAR (2026-11-10, worker w10-1C3C98): the size is right and 26 of 37 instructions agree; what
// is left is one local-alloc ranking and the schedule it pulls with it.
//
// Found: the method is the class's slot 0x104, called only by func_001860A8 with (part,
// contact, end) like slot 0x100 (NoteHitCountColliderContact): the second argument is a
// Contact03 and the entry is c->end[end] (ContactEnd03), not an array of 64-byte records
// indexed by the caller. Retail's `addu v0, v1(index), a1(c)` is an address expanded inside a
// reference or memory operand (Q, Vec::Of, *(Vec*)&); a pointer or reference local
// (`ContactEnd03& e = c->end[end]`) gives `addu c, index` and one register for everything.
// Retail's extra `move v1, v0` is a second add of the same address that reload_cse turned into a
// copy: CSE never replaces a later address with an earlier one held in a user variable (an
// inline's reference parameter, as Q's), but it does replace a user variable's with an earlier
// temporary's (a plain cast), and then deletes it. The Scalar slot store (Vu0::Scalar, the
// scale named first) comes before the position's load, which waits for it (no alias flag:
// Of's or Q's cast), while the velocity's load does not (*(Vec*)&, a mem/s aggregate).
//
// Left: retail's local-alloc places the address (v0) before p->anim (a0); ours places p->anim
// first: priority 0.5 (2 refs over 4 insns) against the address's 0.333 (3 refs over 9 insns,
// its life to the position's load behind the slot store), so p->anim takes v0, the address a0,
// self's copy and the reload of the scale's mfc1 follow, and sched2 then puts the velocity load
// after the division instead of before the length's lwc1. Retail's address needs a fourth
// reference or a span of at most 5, or p->anim a span of at least 7.
//
// Re-scored 2026-11-10 (w16): the same 114 of 144. The span is not where it goes wrong: the
// position's load waits for the slot store in sched1 too, not only in sched2 (alias.c's
// find_base_value gives (plus index c) no base, the index being no pointer and c's base an
// argument ADDRESS that no rule of the PLUS case takes, so base_alias_check conflicts), and
// the forms that free it (a mem/s position) hoist it into the division's shadow in sched2,
// where retail's waits. sched1's order of the closest form (pos as a cast, vel as
// *(Vec*)&, store through Q in one statement) is retail's final order, insn for insn, so its
// spans are retail's: the address (3 refs over 9) loses to p->anim (2 over 4) on refs alone.
// Retail's address quantity has a fourth reference, or a second pseudo tied to it: a register
// copy of the address that stays (the store's base, `move v1, v0` being that copy rather than
// reload_cse's) gives 2*4/9 = 0.889 and retail's registers everywhere, but CSE folds every
// plain copy tried (a pointer or reference local to the end or to v30, Set, the sibling
// ResolveScaledOffsetContact's `Vec02* v = &c->end[end].v30`: one register, 36 differ), and
// re-reading self->f67C for p changes nothing.
// Tried (all with the c->end[end] signature, 2026-11-10): every combination of Q, a u128 cast
// and *(Vec*)& for the position load, the velocity load and the store, with the store in the
// same statement or after a named value (54 variants); the same with a Normalize helper
// (DivX(v, Length(v))) in one statement (27): the closest, pos as a cast, vel as *(Vec*)&, store
// as Q in one statement, gives retail's address structure (both loads on the first add, the
// store on the copy) but the same ranking; the scale named after the difference or inline in the
// MulAddX (slot store late: 25 differ); the length read into a local first; the velocity named
// first. The form below (Vec values, as collider_contact.cpp writes c->end[1].v10) scores the
// same 11 differing instructions.

extern f32 D_00274A44;

void ResolveHitCountColliderContact(HitCountCollider* self, Contact03* c, s32 end)
{
    AnimationPlayer* p = self->f67C;
    if (p != 0) {
        Vu0::Vec k = Vu0::Vec::Scalar((D_00274A44 - self->f68C) / p->anim->length);
        Vu0::Vec d = Vu0::Sub(Vu0::Vec::Of(c->end[end].v10), Vu0::Vec::Of(self->v140));
        *(Vu0::Vec*)&c->end[end].v30 = Vu0::MulAddX(*(Vu0::Vec*)&c->end[end].v30, Vu0::DivX(d, Vu0::Length(d)), k);
    }
}
