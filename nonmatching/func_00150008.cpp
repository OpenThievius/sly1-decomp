// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 654/656 (99.7%), checked 2026-11-08
// NEAR: identical but for the position of one load: retail loads the thrown object (lw v0,0x90(sp)) before the vmul.xyz of the first Length and makes the qmfc2 into v1 with the divisor loaded before it, ours loads it after the vmaddz and the qmfc2 takes v0; the second Length has the same difference. 8 lines in all. The fields f558, f55C, f580 and f584 of PooledObject are floats here (include/pooled_object.h has next at 0x558, a pad at 0x55C and s32 at 0x580 and 0x584); a typed field store is what lets the object pointer in its stack slot stay cached.
// Still differs (2026-11-08, night-close1): with the lengths through ToFloatMoved (the qmfc2 the compiler's reload) the first is retail's; the second's qmfc2 takes v0 where retail's takes v1 (ToFloat there gives the old order; the length in a u128 local or the division without a local leave v0).
#include "common.h"
#include "masked_collider.h"
#include "pooled_object.h"
#include "globals.h"
#include "vu0.h"

#define OBJV ((PooledView*)obj)
struct PooledView { u8 pad00[0x558]; f32 f558; f32 f55C; u8 pad560[0x580 - 0x560]; f32 f580; f32 f584; };
s32 IsObjectAttached(PooledObject* p);
void SetColliderAnchors(Collider* o, s32 a, s32 b, s32 c, s32 d);
void SetPooledObjectState(PooledObject* self, s32 state);
void BuildBasisFromX(Vec02* dir, Mat02* out);
void SendPointEventToWorldListener(Vec02* point, f32 radius);
void TriggerScriptEvent(PooledHolder* host, s32 a, s32 b, void** args);
void TransformDirectionBetweenFrames(void* frame, s32 zero, void* in, Vec02* out);

// A float read from memory as a weight: stored in a slot of its own that the next weight shares.
static inline u128 WeightAt(const f32& f)
{
    Vu0::Slot t;
    Vu0::Q(t) = Vu0::FromFloatAt(f);
    return Vu0::Q(t);
}

void func_00150008(PooledHolder* self)
{
    Vec02 pos;
    Vec02 d;
    Vec02 dir;
    Vec02 step;
    Vec02 vel;
    Mat02 basis;
    PooledObject* obj;
    void* args[1];
    PlacedObject* source;
    f32 speed;
    if (self->p6E0 != 0 && ((Held23*)self->p734->f200)->f1C != 0) {
        if (IsObjectAttached(self->p6E0) == 0 || self->p6E0->state == 3 || self->p6E0->state == 4) {
            self->p6E0 = 0;
            return;
        }
        speed = 15.0f;
        source = self->p6E0;
    } else {
        source = (PlacedObject*)self->f6DC;
        speed = *(f32*)((u8*)self + 0x6D4);
    }
    obj = (PooledObject*)self->p6C8;
    self->p6E0 = 0;
    self->p6C8 = 0;
    obj->desc->m15(obj, 0);
    SetColliderAnchors(obj, 0, 0, 0, 0);
    if (obj->f1FC != 0) {
        typedef void (*AttachedFn)(void* self, s32 arg);
        void* att = obj->f1FC;
        (*(AttachedFn**)att)[2](att, 7);
    }
    pos = source->v140;
    pos.z += speed;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(obj->v140));
    BuildBasisFromX(&d, &basis);
    obj->desc02()->m1E(obj, &basis);
    f32 len = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(d)));
    OBJV->f580 = len / OBJV->f558;
    TransformDirectionBetweenFrames(source->root, 0, &source->root->v150, &dir);
    Vu0::Q(step) = Vu0::MulX(Vu0::Q(dir), WeightAt(OBJV->f580));
    Vu0::Q(pos) = Vu0::Add(Vu0::Q(pos), Vu0::Q(step));
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(obj->v140));
    f32 len2 = Vu0::ToFloatMoved(Vu0::Length(Vu0::Q(d)));
    OBJV->f580 = len2 / OBJV->f558;
    Vu0::Q(d) = Vu0::DivX(Vu0::Q(d), Vu0::Length(Vu0::Q(d)));
    Vu0::Q(vel) = Vu0::MulX(Vu0::Q(d), WeightAt(OBJV->f558));
    obj->desc02()->m20(obj, &vel);
    SetPooledObjectState(obj, 2);
    obj->f57C = (s32)source;
    OBJV->f584 = speed;
    SendPointEventToWorldListener(&obj->v140, OBJV->f55C);
    args[0] = &obj;
    TriggerScriptEvent(self, 0xD, 1, args);
}
