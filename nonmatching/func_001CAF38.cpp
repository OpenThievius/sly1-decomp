// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1004/1008 (99.6%), checked 2026-11-08
// BYTES 0/0, checked 2026-11-07
// NEAR (2026-11-07, worker night-large1): all but two instructions: in the query branch retail
// loads the agent's position into v1 and forms &c->end[j] in v0; here the two registers are swapped
// (lq v0 / addu v1). The orders of the query's three stores (tools/permute.py), the position
// stored after the set-up, a Vec copy and a member Init all leave it.
// Still differs (2026-11-08, night-close6): the end's part through a local or a pointer to the end, the other end written c->end[1 - j], the query cleared inline in the caller (frame grows), pos through a Vec02 local: the same swap.
#include "common.h"
#include "shapes.h"
#include "vu0.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "fpu.h"
#include "globals.h"
#include "item_keeper.h"
#include "flag_table.h"
#include "node_query.h"
#include "c62.h"
#include "animation.h"
#include "attachment.h"
#include "c8b.h"
#include "owner_message.h"
#include "vu0.h"

extern f32 g_gameTime[];
extern float D_00274CFC;
extern float D_00274D00;
extern float D_00274D04;
s32 IsObjectAttached(Collider* a);
s32 IsObjectOfKind(Collider* a, s32 b);
void FillMemory(void* p, s32 v, s32 n);
s32 FindNodeForQuery(void* p, s32 a, s32 b);
void LaunchObjectWithAgentVelocity(u8* self, PlacedObject* other);

void InitOwnerMessage(void* out, s32 mode, Agent* owner);
void ComputeObjectMotionInFrame(void* a, s32 b, void* c, void* d, s32 e, s32 f, s32 g);
void ClampVectorLength(Vec02* in, Vec02* out, f32 max);
void FreePooledContactChain(World* w, Contact03* head);

// A query for the node an agent's contact leads to: the agent, the part it touched and where
// the agent is.
inline void InitAgentContactQuery(NodeQuery* q, Agent* self, Collider* part)
{
    FillMemory(q, 0, 0x40);
    q->pos = self->v140;
    q->hold = part;
    q->p00 = self;
}

void func_001CAF38(Agent* self)
{
    void* target = self->desc08()->m62(self);
    if (target == 0) {
        return;
    }
    if (self->fC04 == 0) {
        Contact03* head = self->fAAC;
        if (head == 0) {
            goto out;
        }
        Player* p = g_player;
        if (target == p || target == self->fB50) {
            if (self->fAC0 == 0) {
                void* h = p->f2200;
                if (h != 0) {
                    h = *(void**)((u8*)h + 0x18);
                    if (h != 0 && *(Agent**)((u8*)h + 0x50) == self) {
                        switch (p->f223C) {
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                            if (g_gameTime[0] - p->f2240 < 0.25f) {
                                goto out;
                            }
                        }
                        if (g_player->f2220 == 10 && g_gameTime[0] - g_player->f2224 < 0.25f) {
                            goto out;
                        }
                        switch (g_player->f2228) {
                        case 7:
                        case 8:
                            if (g_gameTime[0] - g_player->f222C < 0.25f) {
                                goto out;
                            }
                        }
                    }
                }
            }
        }
        for (Contact03* c = head; c != 0; c = c->next) {
            s32 j = (c->end[0].body != (Collider*)self);
            s32 i;
            Elem08* e;
            for (i = 0; i < self->fA78; i++) {
                e = &self->fA7C[i];
                if (e->obj == c->end[j].part && IsObjectAttached((Collider*)e->obj) != 0) {
                    break;
                }
            }
            if (i < self->fA78) {
                ContactEnd03* other = &c->end[1 - j];
                Collider* part = other->part;
                OwnerMessage msg;
                Vec02 vel;
                if (IsObjectOfKind(part, 5) != 0) {
                    InitOwnerMessage(&msg, e->f08, self);
                    switch (msg.mode) {
                    case 6:
                        if (self->fB1C != 0) {
                            msg.fn = (void (*)(void))LaunchObjectWithAgentVelocity;
                            self->vAB0 = D_00248D30;
                            break;
                        }
                    case 0:
                        ComputeObjectMotionInFrame(c->end[j].part, 0, &c->end[1 - j].v10, &vel, 0, 0, 0);
                        Vu0::Q(vel) = Vu0::MulX(Vu0::Vec::Of(vel), Vu0::Vec::Scalar(D_00274CFC + 1.0f)).q;
                        ClampVectorLength(&vel, &vel, D_00274D04);
                        vel.z = D_00274D00 >? vel.z;
                        msg.fn = (void (*)(void))LaunchObjectWithAgentVelocity;
                        self->vAB0 = vel;
                        break;
                    }
                    ((SwitchedCollider*)part)->desc05()->m4C((SwitchedCollider*)part, &msg);
                } else {
                    NodeQuery q;
                    InitAgentContactQuery(&q, self, part);
                    ComputeObjectMotionInFrame(c->end[j].part, 0, &other->v10, &q.dir, 0, 0, 0);
                    q.kind = 2;
                    FindNodeForQuery(&q, 0, 0);
                }
                for (i = 0; i < self->fA78; i++) {
                    ((BaseObject*)self->fA7C[i].obj)->desc->m03((BaseObject*)self->fA7C[i].obj);
                }
                break;
            }
        }
    }
out:
    FreePooledContactChain(self->world, self->fAAC);
    self->fAAC = 0;
}
