// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 376/384, checked 2026-11-08
// NEAR: identical but for the 0.0f: retail keeps it in $f20 (mtc1 zero,$f20 once, then mov.s $f12,$f20 for the two calls and swc1 $f20 for the store at +0x98) and the radius in $f21; here the zero is a constant (mtc1 zero,$f12 / sw zero) and the radius takes $f20. Also the pooled float constants of the three calls. Tried a float local, which the compiler propagates as a constant.
// night-size2 (2026-11-08): EXACT in tools/check.py with three changes, but the whole file's build then fails: zero declared after the normalisation (retail's mtc1 zero,f20 in the join block), dir stored with Vu0::Set, and CreatePooledContact declared float first (retail's mov.s f12 before move t2). Assembled whole, the .p2align 2 cc1plus emits before the normalisation's divide label makes the assembler pad StartSoundEffect's 16-byte copy loop (0x1BFE44) with five short-loop nops, so func_001BFFC8 lands 0x18 late; deleting that one directive from the unit's assembly makes the file place right. The C is in build/swarm/night-size2/func_001BC0E0.exact.cpp of the night-size2 worktree.
#include "common.h"
#include "collider.h"
#include "globals.h"
#include "vu0.h"

void ComputeObjectMotionInFrame(PlacedObject* self, PlacedObject* top, Vec02* origin, Vec02* vel, Vec02* velSum, Vec02* spin, Vec02* spinSum);
void CreatePooledContact(Collider* self, s32 a, Vec02* origin, Vec02* dir, s32 kind, s32 b, s32 c, Contact03** out, f32 z);
void NotifyContactEnds(World* world, s32 n, Contact03** list);
void SolveColliderGroupContacts(World* ctx, s32 n, Collider** arr, s32 v, Contact03** buf, f32 f, s32 ex);
void FreePooledContactChain(void* pool, Contact03* head);

void func_001BC0E0(void* a0, f32 value, void* a1, void* a2)
{
    Collider* self = (Collider*)a0;
    Vec02* origin = (Vec02*)a1;
    Vec02* target = (Vec02*)a2;
    Vec02 vel;
    Vec02 dir;
    Contact03* contact;
    Collider* group[1];
    f32 zero = 0.0f;
    ComputeObjectMotionInFrame(self, 0, origin, &vel, 0, 0, 0);
    Vu0::Q(dir) = Vu0::NormalizeOr(Vu0::Sub(Vu0::Q(*target), Vu0::Q(vel)), Vu0::Q(g_unitZVector));
    contact = 0;
    CreatePooledContact(self, 0, origin, &dir, 0xC, 0, 0, &contact, zero);
    *(Vec02*)((u8*)&contact->end[1] + 0x30) = *target;
    contact->f98 = zero;
    contact->f94 = 1.0f;
    *(f32*)&contact->fA0 = value;
    NotifyContactEnds(self->world, 1, &contact);
    group[0] = (Collider*)self->root;
    SolveColliderGroupContacts(self->world, 1, group, 1, &contact, zero, 2);
    FreePooledContactChain(self->world, contact);
}
