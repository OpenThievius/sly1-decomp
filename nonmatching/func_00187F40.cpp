// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 809/812 (99.6%), checked 2026-11-12
// NEAR: the control flow, the conditional moves (movz for the mesh contact's last two arguments),
//       the delay slots and both VU0 sequences are retail's; the registers are not. Retail keeps
//       the object in $s7, the two argument pointers in $s6 and $s5, the bit-53 constant in $s4 and
//       the bit-40 constant in $fp, and spills the sweep flag at 4(sp); ours puts the object in $s6
//       and both constants last, and the flag at 0(sp). About 30 compiles (a for loop whose
//       increment the continues share, the flags tested through a temporary, the select as a
//       ternary).
// GCSE (2026-11-10, -dG dump): PRE treats p->flags538 as one expression from the f load at the
//       top of the body, so the sweep's tests reuse it; retail reloads p->flags538 at every read
//       after the top, and other->flags538 at the second sweep and the final tail. `-fno-gcse`, as
//       a diagnostic only, gives retail's loads everywhere but one reuse.
// w15 (2026-11-10): AddMeshContacts declared pointer-first, as the file defines it (no change).
//       `u64 g = other->flags538;` read before the bit-47/56 test, not inside it, and tested at
//       the first sweep's bit-40 test: retail's `ld a1` in that test's delay slot and its reuse at
//       the sweep (176 differing lines to 152; with -fno-gcse the size is retail's 812). What is
//       left is PRE's sharing: "PRE: redundant insn" for p->flags538 at the first sweep's bit-44
//       test and the second sweep's bit-40 test (inserted at the top and after the first sweep's
//       calls), and for other->flags538 at the final tail (inserted after the second sweep's
//       calls). 2.95's PRE is lazy code motion over ANTLOC and TRANSP only (lcm.c), so no memory
//       set reproduces retail: a set between f and g makes the sweep's own load the new source
//       (diagnostic asm clobber: 812 bytes, the later reads shared again). Copies of p (CSE's
//       canon_reg, gcse's cprop), an inline accessor, an inline sweep helper (852 bytes, its
//       return value), bitfield reads and -fstrict-aliasing all give the same expression;
//       volatile reads give 836. Retail's ranking also puts the bit-53 constant above the a3/t0
//       copies (global-alloc priority, which needs about twice the weighted references ours has);
//       a named `u64 mark` makes it worse.
// w32 (2026-11-11): block alignment (registers abstracted) differs only at the PRE'd loads: (1)
//       the g load (ours ld a2 in the bit-40 bnezl slot and again at the 47/56 block head, then
//       move a0,a2: PRE's reaching-reg copy; retail one ld a1 in the 47/56 beqz slot), (2) the
//       first sweep's bit-44 test (retail ld v0,1336(s0), ours reuses f in v1), (3) the second
//       sweep's bit-40 test and (4) the tail's other->flags538 test (retail loads at the tail head,
//       copied by reorg into each beqzl/bnezl/bc1fl slot and shared with the |= block in the
//       beqz slot at 0x188208; ours inserts the load after each call). 2.95's PRE is block-based
//       (pre_insert at block ends, no edge splitting), MEM expressions are equal by address, mode
//       and alias set only, and any store or call in a block kills every MEM expression. So retail
//       had, at gcse time, a store or call on the path from the top's f load to the bit-44 test (or
//       a different address pseudo / mode for those reads). Also: retail's sweep spill slot is
//       4(sp), ours 0(sp): something else held 0(sp) in retail's frame (a slot allocated first and
//       left unused, or a 4-byte memory local). Not tried yet: a memory local whose store sits
//       before the sweep test.
// w40-fc (2026-11-12): 152 differing lines to 3. The hit test is written in each arm of both
//       sweeps (`if (AddSweptPartSphereContact(...) != 0) { p->flags538 |= bit 53; continue; }
//       else-arm the same with the mesh call), not once on a shared `hit`: jump2's cross-jumping
//       merges the two identical tails after sched2 (retail's `b join; nop` after the first call
//       is its mark). Until then each tail is its own block that begins after a call, so gcse
//       finds no load of flags538 anticipatable there and PRE shares nothing (every reload of
//       retail's), and the bit-53 constant has four uses at flow time, which ranks it above a3,
//       a4 and self: every register is retail's (docs/toolchain/gcse.md, "A test written in
//       each arm"). What is left is the sweep flag's spill slot, 4(sp) for ours 0(sp): a 4-byte
//       non-BLKmode frame object allocated before reload and never accessed. Probes: an unused
//       `volatile s32` at the top is EXACT (build/swarm/w40-fc/b4.cpp, not allowed); an unused
//       4-byte BLKmode struct takes 16 bytes (frame 208); an unused s32[1], SImode struct or
//       union takes no slot; a const f32& inline for the 1.0 compare keeps a store-flag (836).
#include "common.h"
#include "collider.h"
#include "placed_object.h"
#include "vu0.h"

struct PooledContact;
s32 AddSweptPartSphereContact(void* a0, void* a1, void* a2);
s32 AddSweptPartMeshContact(void* a0, void* a1, void* a2, void* a3, void* a4, void* a5);
void AddSphereSphereContact(Collider* self, Collider* other, void* a2);
void AddMeshContacts(void* a0, f32 radius, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6);
void CreateMeshPairContacts(Collider* self, Collider* other, void* a2, void* a3, u8* ctx, PooledContact** list);

void CollideColliderParts(Collider* self, Collider* other, s32 sweep, void* a3, void* a4, void* a5, void* a6)
{
    for (Collider* p = (Collider*)self->parts.head; p != 0; p = (Collider*)p->link2E4.next) {
        u64 f = p->flags538;
        if (f & (1ULL << 43)) {
            continue;
        }
        if (!(f & (1ULL << 40)) && p->tree.nodes == 0) {
            continue;
        }
        u64 g = other->flags538;
        if (f & ((1ULL << 47) | (1ULL << 56))) {
            if (g & ((1ULL << 47) | (1ULL << 56))) {
                if (f & (1ULL << 56)) {
                    continue;
                }
                if (g & (1ULL << 56)) {
                    continue;
                }
            }
        }
        if (sweep != 0) {
            if (!(p->flags538 & (1ULL << 44))) {
                u128 d = Vu0::Sub(Vu0::Q(p->v370), Vu0::Q(p->v140));
                if (1.0f < Vu0::ToFloat(Vu0::Dot(d, d))) {
                    if (g & (1ULL << 40)) {
                        if (AddSweptPartSphereContact(p, other, a6) != 0) {
                            p->flags538 |= (1ULL << 53);
                            continue;
                        }
                    } else {
                        if (AddSweptPartMeshContact(p, other, a3, a4, a5, a6) != 0) {
                            p->flags538 |= (1ULL << 53);
                            continue;
                        }
                    }
                }
            }
            if (!(other->flags538 & (1ULL << 44))) {
                u128 d = Vu0::Sub(Vu0::Q(other->v370), Vu0::Q(other->v140));
                if (1.0f < Vu0::ToFloat(Vu0::Dot(d, d))) {
                    if (p->flags538 & (1ULL << 40)) {
                        if (AddSweptPartSphereContact(other, p, a6) != 0) {
                            other->flags538 |= (1ULL << 53);
                            continue;
                        }
                    } else {
                        if (AddSweptPartMeshContact(other, p, (void*)p->tree.count, (void*)p->tree.nodes, (void*)p->tree.nodes, a6) != 0) {
                            other->flags538 |= (1ULL << 53);
                            continue;
                        }
                    }
                }
            }
        }
        if (other->flags538 & (1ULL << 40)) {
            if (p->flags538 & (1ULL << 40)) {
                AddSphereSphereContact(p, other, a6);
            } else {
                AddMeshContacts(other, other->radius3CC, &other->v140, p, (void*)p->tree.count2, (void*)p->tree.nodes, 0, a6);
            }
        } else if (p->flags538 & (1ULL << 40)) {
            s32 v = p != self || p->radius3CC != p->radius3D4;
            AddMeshContacts(p, p->radius3CC, &p->v140, other, a3, v ? a5 : a4, v ? (void*)0 : a5, a6);
        } else {
            CreateMeshPairContacts(p, other, a3, a4, (u8*)a5, (PooledContact**)a6);
        }
    }
}
