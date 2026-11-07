// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 560/552, checked 2026-11-07
#include "common.h"
#include "base_object.h"
#include "collider.h"
#include "placed_object.h"
#include "vu0.h"
struct SurfacePair { s32 a; s32 b; };
f32 GetSurfacePairBounce(SurfacePair* p);
// NEAR (2026-11-08, wave 3 retry): Scalar(-f) in place of the k local gives the same code (the
// lever is not what blocks it): retail stores the arguments a5 and a6 at 36 and 40(sp) and a
// third word at 44(sp), and keeps a2, a3, a4 and a7 in s4, s5, s6 and s7; here a5 stays in s8
// and only a6 is stored, which shifts the registers of the prologue and 8 bytes of code.
// A pooled contact as func_00185D20 fills it: two ends of 0x40 bytes (the body and the part, a
// surface number, the point and its two transforms), the normal, then the numbers.
struct PooledEnd {
    Collider* body;         // 0x00
    Collider* part;         // 0x04
    s32 surface;            // 0x08
    u8 pad0C[4];
    Vec02 v10;              // 0x10
    Vec02 v20;              // 0x20
    Vec02 v30;              // 0x30
};
struct PooledContact {
    PooledEnd end[2];       // 0x00
    Vec02 v80;              // 0x80
    f32 f90;                // 0x90
    f32 f94;                // 0x94
    f32 f98;                // 0x98
    s32 kind;               // 0x9C
    s32 fA0;                // 0xA0
    s32 fA4;                // 0xA4
    u8 padA8[0xD0 - 0xA8];
    PooledContact* next;    // 0xD0
};

void* PopZeroedFreeSlot(void* pool);
void TransformPointBetweenFrames(void* frame, void* part, void* in, void* out);
Collider* FindHandlerForSlot(Collider* node, s32 offset);
f32 GetSurfacePairFriction(SurfacePair* p);
void func_001860A8(void* a0, s32 n, Contact03** list);

s32 CreatePooledContact(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7)
{
    s32 surfaces[2];
    Vec02 k;
    PooledContact* c;
    c = (PooledContact*)PopZeroedFreeSlot((u8*)((BaseObject*)a0)->world + 0x1AFC);
    c->f90 = f;
    PooledEnd* end = c->end;
    c->v80 = *(Vec02*)a3;
    for (s32 e = 0; e < 2; e++) {
        Collider* part = (e != 0) ? (Collider*)a1 : (Collider*)a0;
        end->part = part;
        if (part != 0) {
            end->body = *(Collider**)((u8*)part + 0x50);
        } else {
            Vu0::Q(end->v30) = Vu0::Zero();
            end->body = 0;
        }
        end++;
    }
    c->end[0].v10 = *(Vec02*)a2;
    Vu0::Q(k) = Vu0::FromFloat(-f);
    Vu0::Q(c->end[1].v10) = Vu0::MulAddX(Vu0::Q(*(Vec02*)a2), Vu0::Q(*(Vec02*)a3), Vu0::Q(k));
    c->kind = a4;
    for (s32 e = 0; e < 2; e++) {
        PooledEnd* pe = &c->end[e];
        if (pe->part == 0) {
            pe->v20 = pe->v10;
            surfaces[e] = 0;
            pe->surface = 0;
        } else {
            TransformPointBetweenFrames(0, pe->part, &pe->v10, &pe->v20);
            s32 surface = *(s8*)((u8*)pe->part + 0x2C8);
            surfaces[e] = surface;
            pe->surface = surface;
        }
    }
    c->f94 = GetSurfacePairFriction((SurfacePair*)surfaces);
    c->f98 = GetSurfacePairBounce((SurfacePair*)surfaces);
    c->fA4 = a6;
    c->fA0 = a5;
    for (s32 e = 0; e < 2; e++) {
        Collider* obj = FindHandlerForSlot(c->end[e].part, 0x100);
        if (obj != 0) {
            void (*fn)(Collider*, PooledContact*, s32) = (void (*)(Collider*, PooledContact*, s32))((s32*)obj->desc)[0x100 / 4];
            if (fn != 0) {
                fn(obj, c, e);
            }
        }
    }
    func_001860A8(((BaseObject*)a0)->world, 1, (Contact03**)&c);
    c->next = *(PooledContact**)a7;
    *(PooledContact**)a7 = c;
    return (s32)c;
}
