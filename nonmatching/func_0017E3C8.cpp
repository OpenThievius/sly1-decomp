// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 714/772 (92.5%), checked 2026-11-08
// NEAR: the same size as retail now, the VU0 registers retail's (MulAddX2 in its own order gives the result a's register, vf2).
//       Fixed on the way: the parent walk is one while from the part itself (so the mask 0xF000 << 24 is held in s7), the
//       probe is tested against other->tree.nodes (0x3F8), the end tested for bit 2 is end[1 - side], the cases are written
//       1, 3, 2, best is set after the early return and the nearest test reads end[1 - side].v10.z. Still differs: the
//       schedule before the MulAddX2 (retail loads tmp after the start point and forms %hi(D_00264024) in v1, here a0) and
//       the register of *outEnd's reload (retail v1, here a0). Named arguments in every order and the three stores of the
//       new nearest in every order: no closer.
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
    if (D_0026185C - self->f2224 < 0.15f) {
        return 0;
    }
    Contact03* best = 0;
    for (ContactRow03* row = self->contacts->head; row != 0; row = row->next) {
        for (c = row->head; c != 0; c = c->next) {
            s32 side = (Collider*)self != c->end[0].body;
            Collider* other = c->end[1 - side].part;
            Collider* v = other;
            while (v != 0 && (v->flags538 & (0xF000ULL << 24)) == 0) {
                v = (Collider*)v->parent;
            }
            if (v != 0 && (v->flags538 & (0xF000ULL << 24)) == (0x8000ULL << 22)) {
                continue;
            }
            s32 extra;
            switch (c->kind) {
            case 1:
                if (side == 0) {
                    continue;
                }
                extra = c->fA0;
                break;
            case 3:
                if (side == 0) {
                    extra = c->fA4;
                } else {
                    extra = c->fA0;
                }
                break;
            case 2:
                if (side == 1) {
                    continue;
                }
                extra = c->fA4;
                break;
            default:
                continue;
            }
            if (func_0017E088(self, other, &c->end[1 - side].v10, c->kind, extra, &tmp) == 0) {
                continue;
            }
            if ((self->f4B8 & 2) == 0 || (c->end[1 - side].body->f4B8 & 2) == 0) {
                func_001860A8(self->world, 1, &c);
            }
            if (0.0f < D_00274AD0[side] * *(f32*)((u8*)c + 0xB8)) {
                continue;
            }
            u128 from = Vu0::Q(c->end[1 - side].v10);
            Vu0::Q(p) = Vu0::MulAddX2(from, Vu0::Q(tmp), Vu0::Scalar(-D_00264020), Vu0::Q(g_unitZVector), Vu0::ScalarAt(D_00264024));
            if (func_0013E658(&p, other->tree.nodes) != 0) {
                continue;
            }
            if (best == 0 || !(c->end[1 - side].v10.z < best->end[1 - side].v10.z)) {
                *outEnd = side;
                *outPos = tmp;
                best = c;
            }
        }
    }
    return best;
}
