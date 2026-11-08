// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 0/0, checked 2026-11-07
// NEAR (2026-11-07, worker night-large1): the turning collider's ground contacts: the highest
// contact that holds it up (slot 86) becomes the pivot (f690, v6A0, v6B0), then its own contacts
// with the ground are dropped, kept, or turned into a level contact (kind 10). The code is
// retail's but for loop.c: the inner loop of the second walk is 152 insns at the second loop pass
// here (-dL), under the 160 that lets the compare with 6 (life 2) out of the loop, so 6 takes s5
// and the rest of the callee-saved registers and the frame (a spill of &D_00274AD0) follow. The
// u128 helpers give 119; Vec values with Vu0::Set stores 151.
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "vu0.h"
#include "globals.h"
#include "game_clock.h"

extern const f32 D_0024D594;
extern f32 D_00274AD0[2];

s32 CreatePooledContact(f32 depth, TurningCollider* self, Collider* part, Vec02* point, Vec02* normal, s32 kind,
                        s32 a, s32 b, Contact03** link);
void FreePooledContactChain(World* w, Contact03* head);

void func_001C57C8(TurningCollider* self)
{
    Contact03* freed = 0;
    Contact03* best = 0;
    f32 bestHeight = D_0024D594;
    self->f690 = 0;
    ContactRow03* row = self->contacts->head;
    for (;;) {
        Contact03* c = row != 0 ? row->head : self->contacts4B4;
        for (; c != 0; c = c->next) {
            s32 j = (self != c->end[0].body);
            if (((s32 (*)(TurningCollider*, Contact03*, s32))self->desc06()->m56)(self, c, j) != 0) {
                Vec02 arm;
                Vu0::Q(arm) = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(c->end[1 - j].v10));
                f32 h = Vu0::ToFloat(Vu0::Dot(Vu0::Q(arm), Vu0::Q(self->m110.r[2])));
                if (h < bestHeight) {
                    self->f690 = 1;
                    bestHeight = h;
                    best = c;
                    self->f694 = g_gameClock.time;
                    self->v6A0 = c->end[1 - j].v10;
                    Vu0::Q(self->v6B0) = Vu0::MulX(Vu0::Q(c->v80), Vu0::ScalarAt(D_00274AD0[j]));
                    self->f6C0 = c->end[1 - j].part;
                }
            }
        }
        if (row == 0) {
            break;
        }
        row = row->next;
    }
    if (self->f6DC == 0) {
        return;
    }
    row = self->contacts->head;
    for (;;) {
        Contact03** link = row != 0 ? &row->head : &self->contacts4B4;
        Contact03* c;
        while ((c = *link) != 0) {
            s32 j = (self != c->end[0].body);
            if (c->end[j].part != self) {
                link = &c->next;
                continue;
            }
            s32 kind = c->kind;
            if ((kind == 1 && c->fA0 == (s32)self->f6D8) || (kind == 4 && c->fA4 == (s32)self->f6D8)) {
                if (self->f690 != 0) {
                    goto drop;
                }
            } else {
                if ((kind == 1 && c->fA0 == self->f6D4) || (kind == 4 && c->fA4 == self->f6D4) ||
                    (kind == 10 && c->fA0 == self->f6D4)) {
                    if (c != best) {
                        goto drop;
                    }
                }
                if (kind == 3 || (j == 1 && (kind == 1 || kind == 4 || kind == 5 || kind == 6))) {
                    f32 sign = D_00274AD0[j];
                    if (0.0f < sign * c->v80.z) {
                        Vec02 n;
                        Vec02 d;
                        Vec02 p;
                        Vu0::Q(n) = Vu0::MulX(Vu0::Vec::Of(c->v80), Vu0::Vec::Scalar(sign)).q;
                        n.z = 0.0f;
                        Vu0::Q(n) = Vu0::NormalizeOr(Vu0::Vec::Of(n), Vu0::Vec::Of(g_unitXVector)).q;
                        Vu0::Q(d) = Vu0::Sub(Vu0::Vec::Of(c->end[j].v10), Vu0::Vec::Of(c->end[1 - j].v10)).q;
                        f32 depth = Vu0::ToFloat(Vu0::Dot(Vu0::Vec::Of(d), Vu0::Vec::Of(n)));
                        Vu0::Q(p) = Vu0::MulAddX(Vu0::Vec::Of(c->end[1 - j].v10), Vu0::Vec::Of(n),
                                                 Vu0::Vec::Scalar(depth)).q;
                        CreatePooledContact(depth, self, c->end[1 - j].part, &p, &n, 10, 0, 0, &c->next);
                    }
                }
            }
        
            link = &c->next;
            continue;
        drop:
            *link = c->next;
            c->next = freed;
            freed = c;
        }
        if (row == 0) {
            break;
        }
        *row->link = row->head;
        row = row->next;
    }
    FreePooledContactChain(self->world, freed);
}
