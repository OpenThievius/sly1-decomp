// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 800/812, checked 2026-11-07
// NEAR: the control flow, the conditional moves (movz for the mesh contact's last two arguments),
//       the delay slots and both VU0 sequences are retail's; the registers are not. Retail keeps
//       the object in $s7, the two argument pointers in $s6 and $s5, the bit-53 constant in $s4 and
//       the bit-40 constant in $fp, and spills the sweep flag at 4(sp); ours puts the object in $s6
//       and both constants last, and the flag at 0(sp). About 30 compiles (a for loop whose
//       increment the continues share, the flags tested through a temporary, the select as a
//       ternary).
#include "common.h"
#include "collider.h"
#include "placed_object.h"
#include "vu0.h"

s32 AddSweptPartSphereContact(void* a0, void* a1, void* a2);
s32 AddSweptPartMeshContact(void* a0, void* a1, void* a2, void* a3, void* a4, void* a5);
void AddSphereSphereContact(void* a0, void* a1, void* a2);
void AddMeshContacts(void* a0, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, f32 radius);
void func_00186BA8(void* a0, void* a1, void* a2, void* a3, void* a4, void* a5);

void func_00187F40(Collider* self, Collider* other, s32 sweep, void* a3, void* a4, void* a5, void* a6)
{
    for (Collider* p = (Collider*)self->parts.head; p != 0; p = (Collider*)p->link2E4.next) {
        u64 f = p->flags538;
        if (f & (1ULL << 43)) {
            continue;
        }
        if (!(f & (1ULL << 40)) && p->tree.nodes == 0) {
            continue;
        }
        if (f & ((1ULL << 47) | (1ULL << 56))) {
            u64 g = other->flags538;
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
                    s32 hit;
                    if (other->flags538 & (1ULL << 40)) {
                        hit = AddSweptPartSphereContact(p, other, a6);
                    } else {
                        hit = AddSweptPartMeshContact(p, other, a3, a4, a5, a6);
                    }
                    if (hit != 0) {
                        p->flags538 |= (1ULL << 53);
                        continue;
                    }
                }
            }
            if (!(other->flags538 & (1ULL << 44))) {
                u128 d = Vu0::Sub(Vu0::Q(other->v370), Vu0::Q(other->v140));
                if (1.0f < Vu0::ToFloat(Vu0::Dot(d, d))) {
                    s32 hit;
                    if (p->flags538 & (1ULL << 40)) {
                        hit = AddSweptPartSphereContact(other, p, a6);
                    } else {
                        hit = AddSweptPartMeshContact(other, p, (void*)p->tree.count, (void*)p->tree.nodes, (void*)p->tree.nodes, a6);
                    }
                    if (hit != 0) {
                        other->flags538 |= (1ULL << 53);
                        continue;
                    }
                }
            }
        }
        if (other->flags538 & (1ULL << 40)) {
            if (p->flags538 & (1ULL << 40)) {
                AddSphereSphereContact(p, other, a6);
            } else {
                AddMeshContacts(other, &other->v140, p, (void*)p->tree.count2, (void*)p->tree.nodes, 0, a6, other->radius3CC);
            }
        } else if (p->flags538 & (1ULL << 40)) {
            s32 v = p != self || p->radius3CC != p->radius3D4;
            AddMeshContacts(p, &p->v140, other, a3, v ? a5 : a4, v ? (void*)0 : a5, a6, p->radius3CC);
        } else {
            func_00186BA8(p, other, a3, a4, a5, a6);
        }
    }
}
