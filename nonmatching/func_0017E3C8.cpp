// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 776/772, checked 2026-11-07
// NEAR: wave 4 e3. 772 bytes; ours is 776. The contact walk (ends, kinds 1 to 3, the two probes, the nearest) is retail's in structure.
//       Two things differ. (1) retail holds the flag mask 0xF000 << 24 in s7 (hoisted out of the contact loop for its first and
//       last tests and rematerialised for the parent walk) and spills the out-index pointer to 0x34(sp) so the out-point pointer takes
//       s8; ours rematerialises the mask three times, keeps both pointers in s7 and s8 (4 bytes more). (2) the MulAddX2 of
//       the probe point (tmp in vf4, unit Z in vf1, v10 in vf2, the two weights in vf3 and vf5) puts its result in a's register
//       (vf2); the helper gives it c's (the unit Z, vf1), as func_00198BD8 needs. ~8 compiles.
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
extern f32 D_00264020;
extern f32 D_00264024;
extern f32 D_00274AD0[];
s32 func_0017E088(Player* self, Collider* other, Vec02* point, s32 kind, s32 extra, Vec02* out);
void func_001860A8(void* world, s32 n, Contact03** list);
s32 func_0013E658(Vec02* p, void* tree);
Contact03* func_0017E3C8(Player* self, s32* outEnd, Vec02* outPos)
{
    Vec02 tmp;
    Vec02 p;
    Contact03* c;
    Contact03* best = 0;
    if (D_0026185C - self->f2224 < 0.15f) {
        return 0;
    }
    for (ContactRow03* row = self->contacts->head; row != 0; row = row->next) {
        for (c = row->head; c != 0; c = c->next) {
            s32 side = (Collider*)self != c->end[0].body;
            Collider* other = c->end[1 - side].part;
            if (other != 0) {
                Collider* v = other;
                if ((v->flags538 & (0xF000ULL << 24)) == 0) {
                    v = (Collider*)v->parent;
                    while (v != 0 && (v->flags538 & (0xF000ULL << 24)) == 0) {
                        v = (Collider*)v->parent;
                    }
                }
                if (v != 0 && (v->flags538 & (0xF000ULL << 24)) == (0x8000ULL << 22)) {
                    continue;
                }
            }
            s32 extra;
            switch (c->kind) {
            case 1:
                if (side == 0) {
                    continue;
                }
                extra = c->fA0;
                break;
            case 2:
                if (side == 1) {
                    continue;
                }
                extra = c->fA4;
                break;
            case 3:
                if (side == 0) {
                    extra = c->fA4;
                } else {
                    extra = c->fA0;
                }
                break;
            default:
                continue;
            }
            if (func_0017E088(self, other, &c->end[1 - side].v10, c->kind, extra, &tmp) == 0) {
                continue;
            }
            if ((self->f4B8 & 2) == 0 || (c->end[side].body->f4B8 & 2) == 0) {
                func_001860A8(self->world, 1, &c);
            }
            if (0.0f < D_00274AD0[side] * *(f32*)((u8*)c + 0xB8)) {
                continue;
            }
            Vu0::Q(p) = Vu0::MulAddX2(Vu0::Q(c->end[1 - side].v10), Vu0::Q(tmp), Vu0::Scalar(-D_00264020), Vu0::Q(g_unitZVector), Vu0::ScalarAt(D_00264024));
            if (func_0013E658(&p, other->tree2.nodes) != 0) {
                continue;
            }
            if (best == 0 || !(*(f32*)((u8*)c + (1 - side) * 0x40 + 0x18) < *(f32*)((u8*)best + (1 - side) * 0x40 + 0x18))) {
                *outEnd = side;
                *outPos = tmp;
                best = c;
            }
        }
    }
    return best;
}
