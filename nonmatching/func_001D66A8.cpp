// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 872/876 (99.5%), checked 2026-11-07
// NEAR: every instruction is retail's but the register numbers of the two float constants of MulXSum's weights (retail: 2.0 in f0 and -1.0 in f1, here the other way round). Needs Player::f2438 and f26D8 (include/switched_collider.h).
#include "common.h"
#include "switched_collider.h"
#include "owner_message.h"
#include "globals.h"
#include "vu0.h"
#include "shapes.h"
extern f32 g_gameClock[];
extern float D_0027516C;
void InitOwnerMessage(OwnerMessage* l, s32 zero, Collider* c);
s32 IsObjectOfKind(void* node, s32 kind);
void CopyMemory(void* dst, void* src, u32 size);

struct HitMessage {
    s32 kind;               // 0x00
    u8 pad04[0x20 - 0x04];
    Vec02 v20;              // 0x20
    f32 f30;                // 0x30
    u8 pad34[0x38 - 0x34];
    Collider* f38;          // 0x38
    u8 pad3C[0x50 - 0x3C];
};

f32 ComputeOscillatorDisplacement(void* osc, void* pos, f32 t, s32 a, Vec02* out, s32 b, s32 c);
s32 IsObjectOfKind(void* node, s32 kind);
s32 func_0013E658(void* a, s32 b);
s32 func_001D6A18(Player* self, Collider* col, Vec02* out);
void GetObjectWorldPosition(void* obj, void* out);
void TransformPointAtTime(void* frame, s32 a, void* point, s32 b, s32 c, s32 d, f32 t);
typedef s32 (*MessageHandlerFn)(Collider* self, s32 a, OwnerMessage* msg);
typedef void (*HitFn)(Collider* self, HitMessage* msg);

void func_001D66A8(Player* self)
{
    u32 i;
    if (self->f2438 != 0 && *(s32*)((u8*)self->f2438 + 0x58C) != 0) {
        Vec02 p;
        Vec02 moved;
        p = self->v140;
        p.z = p.z + D_0027516C;
        if (self->f2228 == 0x27 || self->f2228 == 0x2F) {
            p.z = p.z - 10.0f;
        }
        if (self->f2438->f278 != 0) {
            ComputeOscillatorDisplacement(((void**)self->f2438->f278)[3], &p, 50.0f, 0, &moved, 0, 0);
            u128 s2 = Vu0::Scalar(2.0f);
            u128 s1 = Vu0::Scalar(-1.0f);
            Vu0::Q(p) = Vu0::MulXSum(Vu0::Q(p), s2, Vu0::Q(moved), s1);
        }
        i = func_0013E658(&p, (s32)self->f2438->tree.nodes) != 0;
    } else {
        i = 0;
    }
    if (i != 0 && (self->v150.z < 0.0f || !(self->f2220 == 2 || self->f2228 == 0x2C || self->f2228 == 0x2B))) {
        OwnerMessage msg;
        InitOwnerMessage(&msg, 3, self->f2438);
        if (((MessageHandlerFn)self->f2438->desc03()->m47)(self->f2438, 0, &msg) != 0) {
            self->desc05()->m4C(self, (void*)&msg);
        }
    }
    Vec02 out;
    if (i == 0 || func_001D6A18(self, self->f2438, &out) == 0) {
        return;
    }
    f32 fresh = 0.05f;
    for (i = 0; i < 8; i++) {
        HitStamp* rec = &self->f26D8[i];
        Collider* obj = rec->obj;
        if (obj == 0) {
            continue;
        }
        if (g_gameClock[1] - rec->time < fresh) {
            continue;
        }
        Collider* list[8];
        s32 count;
        if (IsObjectOfKind(obj, 0x78) != 0) {
            CopyMemory(list, (u8*)obj + 0x94, 0x20);
            count = *(s32*)((u8*)obj + 0x90);
        } else {
            list[0] = obj;
            count = 1;
        }
        for (s32 j = 0; j < count; j++) {
            Collider* o = list[j];
            Vec02 lo;
            Vec02 hi;
            s32 hit = 0;
            GetObjectWorldPosition(o, &lo);
            hi = *(Vec02*)((u8*)o + 0x40);
            TransformPointAtTime(*(void**)((u8*)obj + 0x18), 0, &hi, 0, 0, 0, g_gameClock[2]);
            if (out.z <= lo.z) {
                if (hi.z <= out.z) {
                    hit = 1;
                }
            } else if (out.z <= hi.z) {
                hit = 1;
            }
            if (hit != 0) {
                HitMessage m;
                m.v20 = lo;
                m.v20.z = out.z;
                m.kind = 4;
                u8* e = *(u8**)((u8*)o + 0x90);
                if (*(s32*)(e + 0x120) == 1 && *(s32*)(e + 0x1B0) == 2) {
                    m.kind = 0x24;
                    m.f38 = self->f2438;
                }
                ((HitFn*)o->desc)[31](o, &m);
                rec->time = g_gameClock[1];
            }
        }
    }
}
