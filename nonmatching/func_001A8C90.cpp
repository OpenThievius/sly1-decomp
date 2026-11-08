// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 1840/1848, checked 2026-11-08
// NEAR (2026-11-08, night-large3): func_001A8C90, the object pool's release of its chosen object
// (93.7% of the words, same frame). Left: after the normalisation's join retail forms the poly
// pointer (addiu v0, s2, 0x110) before its qmfc2 of the length and moves it to $f2 after the
// first coefficient's load, where ours does qmfc2 then mtc1 first; and the random spin's upper
// bound is loaded into $f1 for the test and copied to $f13 (mov.s) for the call, where ours
// loads it into $f13 (a local for it does not change that), which leaves the tail 4 bytes short.
#include "common.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "world.h"
#include "object_pool.h"
#include "screen_element.h"
#include "font.h"
#include "shapes.h"
#include "game_clock.h"
#include "game_progress.h"
#include "text_reader.h"
#include "globals.h"
#include "asm_func.h"
#include "vu0.h"
#include "placed_object.h"
#include "object_event.h"
#include "object_message.h"

extern f32 g_gameTime;
f32 ArctangentOfRatio(f32 x, f32 y);
s32 IsObjectOfKind(void* node, s32 kind);
void ChooseObjectPoolItem(ObjectPool* self);
extern const Vec02 g_unitXVector;
struct Released_1A8C90;
typedef void (*ReleasedFn_1A8C90)(Released_1A8C90* self, void* a, void* b);
struct ReleasedDesc_1A8C90 {
    u8 pad00[8];
    u32 flags;                      // 0x08
    u8 pad0C[0x18 - 0x0C];
    void (*m18)(Released_1A8C90* self);                 // 0x18: into the parent's list
    u8 pad1C[0x84 - 0x1C];
    void (*m84)(Released_1A8C90* self, Vec02* pos);     // 0x84: the position
    void (*m88)(Released_1A8C90* self, void* rot);      // 0x88: the orientation
    void (*m8C)(Released_1A8C90* self, Vec02* v);
    void (*m90)(Released_1A8C90* self, Vec02* vel);     // 0x90: the velocity
    void (*m94)(Released_1A8C90* self, Vec02* spin);    // 0x94: the spin
    u8 pad98[0x130 - 0x98];
    void (*m130)(Released_1A8C90* self, void* frame, void* at);  // 0x130
};
struct ReleasedTrack_1A8C90 { u8 pad00[0x60]; void* frame; u8 pad64[0xB0 - 0x64]; u32 flags; };
struct Released_1A8C90 {
    ReleasedDesc_1A8C90* desc;
    u8 pad004[0x190 - 0x004];
    Vec02 v190;                     // 0x190
    u8 pad1A0[0x1D0 - 0x1A0];
    Vec02 v1D0;                     // 0x1D0
    u8 pad1E0[0x224 - 0x1E0];
    ReleasedTrack_1A8C90* track;    // 0x224
    u8 pad228[0x554 - 0x228];
    f32 f554;                       // 0x554
    u8 pad558[0x690 - 0x558];
    f32 speed;                      // 0x690
    u8 pad694[0x6E4 - 0x694];
    void* f6E4;                     // 0x6E4
    u8 pad6E8[0xC3C - 0x6E8];
    s32 fC3C;                       // 0xC3C
};
struct ReleaseHeading_1A8C90 { u32 flags; u8 pad04[0xC - 4]; f32 speed; };
struct PoolOwner_1A8C90 { u8 pad00[8]; u32 flags; };
struct PoolParent_1A8C90 { u8 pad00[0x50]; PoolOwner_1A8C90** root; };
struct PoolView_1A8C90 {
    u8 pad000[0x18];
    PoolParent_1A8C90* parent;      // 0x18
    u8 pad01C[0x3C - 0x1C];
    Sub8C* sub;                     // 0x3C
    u8 pad040[0x48 - 0x40];
    Released_1A8C90* chosen;        // 0x48
    u8 pad04C[0x5C - 0x4C];
    void* frame;                    // 0x5C
    u8 pad060[0x68 - 0x60];
    void* mover;                    // 0x68
    u8 pad06C[0xB0 - 0x6C];
    Vec02 velocity;                 // 0xB0
    Vec02 spin;                     // 0xC0
    f32 spinLo;                     // 0xD0
    f32 spinHi;                     // 0xD4
    f32 life;                       // 0xD8
    u8 padDC[0xE0 - 0xDC];
    void* targetFrame;              // 0xE0
    PlacedObject* target;           // 0xE4
    u8 padE8[0xF0 - 0xE8];
    Vec02 at;                       // 0xF0
    s32 aimMode;                    // 0x100
    u8 pad104[0x110 - 0x104];
    f32 poly[3];                    // 0x110
    u8 pad11C[0x120 - 0x11C];
    f32 lo;                         // 0x120
    f32 hi;                         // 0x124
    u8 pad128[0x150 - 0x128];
    ReleaseHeading_1A8C90 heading;  // 0x150
};

void GetPlacementRecordTransform(void* self, Vec02* a1, void* a2, void* a3);
void func_001A95D0(void* self, Vec02* target, Vec02* out, void* to);
void* AllocateZeroedFrontMemory(s32 size);
void SetColliderAnchors(void* self, s32 a, s32 b, s32 c, s32 d);
void ComputeObjectMotionInFrame(void* obj, s32 z, void* point, Vec02* out, Vec02* spin, s32 b, s32 c);
void GetPlacementRecordAngle(void* self, f32* out, void* x);
void func_001A9868(void* self, f32* out, void* x);
void BuildYawPitchMatrix(Mat02* out, f32 yaw, f32 pitch);
f32 WrapAngle(f32 a);
s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 c);
void ForwardBallisticLaunchVelocity(f32 t, Vec02* from, Vec02* to, Vec02* out, void* obj);
void func_001EE090(f32 t, Vec02* from, Vec02* to, Vec02* out, void* obj);
void ComputeBallisticLaunchVelocity(f32 t, Vec02* from, Vec02* to, Vec02* out, void* obj);
f32 RandomFloatInRange(f32 a, f32 b);
void ChangeAgentState(void* node, s32 kind, s32 flag);
void TriggerScriptEvent(void* self, s32 a, s32 b, void* c);
void ClearObjectPoolChoice(void* self);

// v made a unit vector, or the fallback when shorter than 1e-4; its length.
static inline u128 NormalizeVectorOr(Vec02& v, const Vec02& fallback)
{
    u128 len = Vu0::Length(Vu0::Q(v));
    if (Vu0::ToFloatMoved(len) < 0.0001f) {
        v = fallback;
    } else {
        Vu0::Q(v) = Vu0::DivX(Vu0::Q(v), len);
    }
    return len;
}

s32 func_001A8C90(PoolView_1A8C90* self, s32 aim)
{
    Vec02 pos;
    Vec02 to;
    Vec02 dir;
    Mat02 rot;
    Released_1A8C90* obj = self->chosen;
    if (obj == 0) {
        ChooseObjectPoolItem((ObjectPool*)self);
        if (self->chosen == 0) {
            return 0;
        }
        obj = self->chosen;
    }
    GetPlacementRecordTransform((u8*)self + 0x60, &pos, &rot, self->frame);
    func_001A95D0((u8*)self + 0xE0, &pos, &to, self->frame);
    Vu0::Q(dir) = Vu0::Sub(Vu0::Q(to), Vu0::Q(pos));
    u128 len = NormalizeVectorOr(dir, g_unitXVector);
    f32* p = self->poly;
    f32 d = Vu0::ToFloat(len);
    f32 reach = self->poly[0] + d * (p[1] + d * p[2]);
    f32 lo = self->lo;
    f32 hi = self->hi;
    if (reach < lo) {
        reach = lo;
    } else if (hi < reach) {
        reach = hi;
    }
    Vu0::Q(to) = Vu0::Add(Vu0::Q(pos), Vu0::MulX(Vu0::Q(dir), Vu0::Scalar(reach)));
    if (self->parent != 0 && self->parent->root != 0 && ((*self->parent->root)->flags & 2) && IsObjectOfKind(obj, 0x3C)) {
        obj->f6E4 = self->parent->root;
    }
    if (self->frame != 0) {
        if (obj->track == 0) {
            obj->track = (ReleasedTrack_1A8C90*)AllocateZeroedFrontMemory(0xC0);
        }
        obj->track->flags |= 0xC;
        obj->track->frame = self->frame;
    }
    obj->desc->m18(obj);
    SetColliderAnchors(obj, 0, 0, 0, 0);
    obj->desc->m84(obj, &pos);
    obj->desc->m88(obj, &rot);
    if (self->sub != 0 && self->sub->f4 != 0) {
        Vec02* q = (Vec02*)self->sub->f10;
        obj->v190 = q[0];
        obj->v1D0 = q[1];
    }
    if (self->mover != 0) {
        Vec02 vel;
        Vec02 spin;
        ComputeObjectMotionInFrame(self->mover, 0, (u8*)self->mover + 0x140, &vel, &spin, 0, 0);
        obj->desc->m90(obj, &vel);
        obj->desc->m94(obj, &spin);
    } else {
        Vec02* vel = vel;
        if (aim != 0) {
            ReleaseHeading_1A8C90* h = &self->heading;
            if (IsObjectOfKind(obj, 0x3E) || IsObjectOfKind(obj, 0x3D)) {
                Vec02 delta;
                Vec02 scale;
                Mat02 m;
                f32 yaw;
                f32 pitch;
                Vu0::Q(delta) = Vu0::Sub(Vu0::Q(to), Vu0::Q(pos));
                if (h->flags & 2) {
                    GetPlacementRecordAngle(h, &yaw, self->frame);
                } else {
                    yaw = ArctangentOfRatio(delta.y, delta.x);
                }
                if (h->flags & 1) {
                    func_001A9868(h, &pitch, self->frame);
                } else {
                    pitch = ArctangentOfRatio(delta.z, Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(delta), Vu0::Q(delta)))));
                }
                f32 speed;
                if (h->flags & 4) {
                    speed = h->speed;
                } else {
                    speed = obj->speed;
                }
                BuildYawPitchMatrix(&m, yaw, pitch);
                Vu0::Q(scale) = Vu0::FromFloat(speed);
                Vu0::Q(self->velocity) = Vu0::MulX(Vu0::Q(m.r[0]), Vu0::Q(scale));
            } else {
                Vec02 delta;
                Vu0::Q(delta) = Vu0::Sub(Vu0::Q(to), Vu0::Q(pos));
                if (h->flags & 2) {
                    f32 yaw;
                    f32 a = ArctangentOfRatio(delta.y, delta.x);
                    GetPlacementRecordAngle(h, &yaw, self->frame);
                    a = WrapAngle(a);
                    AreFloatsNearlyEqual(a, WrapAngle(yaw), 0.0001f);
                }
                if (self->heading.flags & 1) {
                    f32 t;
                    func_001A9868(h, &t, self->frame);
                    ForwardBallisticLaunchVelocity(t, &pos, &to, &self->velocity, obj);
                } else if (self->heading.flags & 4) {
                    func_001EE090(h->speed, &pos, &to, &self->velocity, obj);
                } else {
                    ComputeBallisticLaunchVelocity(0.5f, &pos, &to, &self->velocity, obj);
                }
            }
        }
        obj->desc->m90(obj, &self->velocity);
        if (0.0f < self->spinHi) {
            Vec02 spin;
            f32 m = RandomFloatInRange(self->spinLo, self->spinHi);
            spin.x = RandomFloatInRange(-1.0f, 1.0f);
            spin.y = RandomFloatInRange(-1.0f, 1.0f);
            spin.z = RandomFloatInRange(-1.0f, 1.0f);
            Vu0::Set(spin, Vu0::MulX(Vu0::NormalizeOr(Vu0::Q(spin), Vu0::Q(g_unitXVector)), Vu0::Scalar(m)));
            obj->desc->m94(obj, &spin);
        } else {
            obj->desc->m94(obj, &self->spin);
        }
    }
    if (0.0f < self->life && IsObjectOfKind(obj, 0x3B)) {
        obj->f554 = g_gameTime + self->life;
    }
    if (IsObjectOfKind(obj, 0x3C)) {
        switch (self->aimMode) {
        case 2: {
            void* frame = self->targetFrame;
            void* at = &self->at;
            if (frame == 0 && self->target != 0) {
                frame = self->target->parent;
                at = &self->target->link40;
            }
            obj->desc->m130(obj, frame, at);
            break;
        }
        case 0:
        case 1:
        default:
            obj->desc->m130(obj, 0, &to);
            break;
        }
    }
    if (IsObjectOfKind(obj, 8)) {
        ChangeAgentState(obj, 0x10, 0);
        if (IsObjectOfKind(obj, 0xA)) {
            obj->fC3C = 1;
        }
    }
    Released_1A8C90** held = &obj;
    TriggerScriptEvent(self, 0xD, 1, &held);
    ClearObjectPoolChoice(self);
    return 1;
}
