// SPDX-License-Identifier: AGPL-3.0-or-later
// From 0x1D62E0 to 0x1D8E40: classes 0x07 and 0x3F, the output buffer and the first of class
// 0x19's functions. Its .data runs from 0x275140 to 0x2754FC; its .rodata is the "%s" of
// func_001D72C8 and the float of func_001D8470 (0x24DC90 to 0x24DC98). Its start is an edge retail
// proves. Its end is a choice: the cut before path_follower_helpers.cpp, made on loop.c's threshold (that
// file's head), which no boundary signal shows. Between the two it could still be several files.
// Its name is ours, after its largest family, the path follower's start and steps (class 0x19),
// whose other functions follow in path_follower_helpers.cpp and world.cpp.
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "mul_rotation.h"
#include "pad_record.h"
#include "deferred_request.h"
#include "list_iter.h"
#include "switched_collider.h"
#include "state_trigger.h"
#include "child_group_object.h"
#include "screen_element.h"
#include "object_link.h"
#include "object_message.h"
#include "owner_message.h"
#include "output_buffer.h"
#include "shapes.h"
#include "globals.h"
#include "world.h"
#include "queued_call.h"
#include "effect.h"
#include "game_progress.h"
#include "buffered_stream.h"
#include "value_range.h"
#include "script_value.h"
#include "cone_volume.h"
#include "redirect_object.h"
#include "font.h"
#include "level_entry.h"
#include "message_body.h"
#include "path_curve_object.h"
#include "state_notifier.h"
#include "fpu.h"
#include "scope_marker.h"

extern f32 g_gameClock[];

typedef void (*VFnB)(void* self, void* arg);

s32 IsObjectAttached(void* node);

s32 TestCollidersMayContact(void* self, s32 value);

void InitSwitchedCollider(void* self);
void CopyMemory(void* dst, void* src, u32 size);
void ResetPathFollower(void* self);

void HandleChildGroupNotification(StandIn* self, s32 kind, ObjectMessage* ref);

void* FillMemory(void* p, s32 value, s32 size);

void FlushOutputBuffer(OutputBuffer* a0, s32 a1);
void FreeObjectMemory(OutputBuffer* a0);

void CopyMemory(void* dst, void* src, s32 bytes);
void PrintBuffered(void* a, void* b);
s32 WriteFile(s32 a, void* b, s32 n);

void CopyMemory(void* dst, void* src, s32 count);
void FlushOutputBuffer(OutputBuffer* self);

void StartPlacedObject(PathFollower* self);
void ResolveObjectLinks(PathFollower* self, s32 n, void* table);
f32 ArctangentOfRatio(f32 a, f32 b);
StateTrigger* CreateStateWalker(StateTrigger* a, PathFollower* self, s32 b, s32 c);
void SetStateWalkerTarget(StateTrigger* a, s32 b);
void StartSoundEffect(s32 id, void* a1, PathFollower* a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
f32 RandomFloatInRange(f32 a, f32 b);
void* FindFirstObjectById(World* host, s32 a1, s32 a2, PathFollower* ctx);
s32 GatherObjectsByMode(World* host, s32 a1, s32 a2, s32 a3, s32 a4, BaseObject** out);
void ResetPathFollower(PathFollower* self);

void* FillMemory(void* p, s32 value, s32 size);

void* FillMemory(void* p, s32 value, s32 size);

f32 GetWrappedDifference(f32 x, f32 lim, f32 base);

void TransformPointBetweenFrames(void* a0, void* a1, void* a2, void* a3);

void GetObjectWorldPosition(void* self, void* arg); // stays void: retail returns a value, but declared so func_001D66A8 and two more differs in registers

struct WalkerHolder { u8 pad[0x48]; void* f48; };

WalkerHolder* FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);

extern f32 g_gameClock[];

void* GetActiveSwitchedCollider(void);
f32 ApproachValueWithRamp(void* p, s32 zero, f32 a, f32 b, f32 c);
f32 RandomFloatInRange(f32 a, f32 b);

void GetObjectWorldPosition(void* item, void* out); // stays void: retail returns a value, but declared so func_001D66A8 and two more differs in registers

void* GetActiveSwitchedCollider(void);

void UpdatePathFollowerPace(PathFollower* self);
void AdvancePathFollowerAlongPath(PathFollower* self, s32* out);
void ComputePathFollowerHeadingTarget(PathFollower* self);
void SteerPathFollower(PathFollower* self);

s32 IsInsideAnyRange(s32 count, ValueRange* spans, f32 x);

// A quadratic by its three coefficients (func_001D8578).
struct QuadraticCurve {
    f32 c[3];
    f32 Eval(f32 t) { return c[0] + t * (c[1] + t * c[2]); }
};

struct WorldRecord { u8 b; };

#define SUB(off) ((WorldRecord*)((u8*)self + (off)))

extern f32 D_002754F8; extern f32 D_002754F4; extern f32 g_frameDt; extern f32 D_002754E8[3];
f32 ArctangentOfRatio(f32 a, f32 b); f32 WrapAngle(f32 a); f32 ClampToMagnitude(f32 a, f32 b); f32 ApproachAngleWithRamp(void* p, void* out, f32 a, f32 b, f32 c);

typedef int Quadword __attribute__((mode(TI)));

void *StoreFloatAsQuadword(void* out, f32 f);
void* CopyQuadword(void* out, void* in);
void* StoreQuadword(void* dst, Quadword v);

void* FillMemory(void* p, s32 value, s32 size);

f32 ArctangentOfRatio(f32 a, f32 b);
void BuildAxisAngleMatrix(const Vec02* t, void* out, f32 x);
void ResolveObjectLinks(void* self, s32 n, void* table);
void* CreateStateWalker(void* a, void* b, s32 c, s32 d);

extern f32 g_gameClock[];
void InitOwnerMessage(OwnerMessage* l, s32 zero, Collider* c);

extern f32 g_gameClock[];

void SetStateWalkerTarget(StateTrigger* h, s32 b);
void BuildAxisAngleMatrix(const Vec02* tab, void* out, f32 v);

extern f32 g_gameClock[];

float D_00275140[4] = {1.0f, 0.0f, -0.75f, 0.0f};
float D_00275150[4] = {0.699999988f, 0.300000012f, 0.0f, 0.0f};
float D_00275160 = 650.0f;
float D_00275164 = 100.0f;
float D_00275168 = -100.0f;
float D_0027516C = 50.0f;
float D_00275170[2] = {-10.0f, 0.0f};
float D_00275178[4] = {250.0f, 0.0f, 1.0f, 4500.0f};
float D_00275188 = 10.0f;
float D_0027518C = 50.0f;
float D_00275190[4] = {0.0f, 45.0f, 0.0f, 0.0f};
float D_002751A0[4] = {0.0f, 2.5f, 0.0f, 0.0f};
float D_002751B0[4] = {0.0f, 7.5f, 0.0f, 0.0f};
float D_002751C0[4] = {0.0f, 4.0f, 0.0f, 0.0f};
float D_002751D0 = 850.0f;
s32 D_002751D4 = 60;
float D_002751D8 = 1.25f;
float D_002751DC = 0.75f;
float D_002751E0[4] = {1.35000002f, 0.0f, -0.349999994f, 0.0f};
float D_002751F0[4] = {1.0f, 1.35000002f, 0.0f, 0.0f};
float D_00275200[4] = {1.5f, 0.0f, -0.5f, 0.0f};
float D_00275210[4] = {1.0f, 1.5f, 0.0f, 0.0f};
float D_00275220[4] = {9000.0f, 0.0f, -9000.0f, 0.0f};
float D_00275230[4] = {0.0f, 9000.0f, 0.0f, 0.0f};
float D_00275240[4] = {1.0f, -1.0f, 0.0f, 0.0f};
f32 D_00275250[16] = {
    1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f
};
f32 D_00275290[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
ObjectLink D_002752A0[20] = {
    { 4, 0x416, 0x6B0 }, { 4, 0x417, 0x710 }, { 4, 0x418, 0x770 }, { 4, 0x419, 0x7D0 },
    { 0, 0x41A, 0x6B8 }, { 0, 0x41B, 0x718 }, { 0, 0x41C, 0x778 }, { 0, 0x41D, 0x7D8 },
    { 6, 0x41E, 0x6B4 }, { 6, 0x41F, 0x714 }, { 6, 0x420, 0x774 }, { 6, 0x421, 0x7D4 },
    { 0, 0x422, 0x690 }, { 2, 0x428, 0xB28 }, { 2, 0x429, 0xB2C }, { 2, 0x42A, 0xB44 },
    { 2, 0x42B, 0xB4C }, { 0x22, 0x423, 0xB14 }, { 0x20, 0x424, 0xB18 }, { 0x20, 0x425, 0xB1C }
};
float D_00275390 = 1.0f;
f32 D_00275394 = 2.0f;
Vec02 D_002753A0 = { 0.0f, 30.0f, 3.0f, 0.0f };
float D_002753B0[4] = {0.0f, 0.00999999978f, 0.0f, 0.0f};
float D_002753C0[2] = {0.0f, 45.0f};
float D_002753C8 = 15.0f;
float D_002753CC = 90.0f;
float D_002753D0[4] = {0.0f, 0.25f, 0.75f, 0.0f};
float D_002753E0[4] = {0.0f, 0.0f, 1.0f, 0.0f};
float D_002753F0[4] = {0.0f, 0.0f, 1.0f, 0.0f};
float D_00275400[4] = {0.0f, 2.5f, 0.25f, 0.0f};
float D_00275410 = 6000.0f;
float D_00275414 = 11250.0f;
float D_00275418 = 7.0f;
float D_0027541C = 2500.0f;
f32 D_00275420[4] = { 1.0f, -1.0f, 0.0f, 0.0f };
f32 D_00275430[4] = { 0.5f, 1.0f, 0.0f, 0.0f };
f32 D_00275440[2] = { 0.5f, 1.0f };
f32 D_00275448[4] = { 4000.0f, 0.0f, 2.0f, 0.0f };
f32 D_00275458[6] = { 2000.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f };
f32 D_00275470[4] = { 0.0f, 0.0333333313f, 0.0f, 0.0f };
f32 D_00275480[2] = { 0.0f, 50.0f };
f32 D_00275488 = -10.0f;
f32 D_00275490[4] = { 0.05f, 0.0f, 0.25f, 0.0f };
f32 D_002754A0[4] = { 1.5f, 2.5f, 0.0f, 0.0f };
f32 D_002754B0[4] = { 1000.0f, -0.5f, 0.0f, 0.0f };
f32 D_002754C0[2] = { 0.0f, 625.0f };
ValueRange D_002754C8 = { -1300.0f, 1300.0f };
f32 D_002754D0[3] = { 1125.0f, 0.0f, 0.100000001f };
f32 D_002754DC = 750.0f;
f32 D_002754E0[2] = { 1.0f, 0.0f };
f32 D_002754E8[3] = { 8.0f, 0.0f, 0.25f };
f32 D_002754F4 = 0.7f;
f32 D_002754F8 = 0.5f;

struct RingSource {
    u8 pad00[0x40];
    Vec02 v40;              // 0x40
    u8 pad50[0x30];
    Vec02 v80;              // 0x80
};

typedef void (*RingDrawFn)(void* request);
void DrawPlayerMarkerRing1(DeferredRequest* request);
void DrawPlayerMarkerRing2(DeferredRequest* request);
void DrawPlayerMarkerRing3(DeferredRequest* request);
s32 MaskWorldBitsBySave(void);
void QueueDeferredRequest(DeferredRequest* src);
void SetObjectTreeRecordValue(void* obj, u32 value);
f32 Cosine(f32 x);
extern Rgba4 D_002623E0[];

struct RingClamp {
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        if (x < lo) {
            return lo;
        }
        if (hi < x) {
            return hi;
        }
        return x;
    }
};

void QueuePlayerMarkerRingDraw(Player* self, RingSource* a, void* b)
{
    s32 state = self->f2228;
    if (state >= 0x25 && (state < 0x27 || (state == 0x37 && (MaskWorldBitsBySave() & 0x400) != 0))) {
        DeferredRequest f;
        (void)FillMemory(&f, 0, 0x80);
        f.f04 = Vu0::ToFloat(Vu0::Dot(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(a->v40)), Vu0::Q(a->v80)));
        f.group = 0xD;
        f.arg = self;
        switch (self->f2228) {
        case 0x37:
            f.callback = (void*)DrawPlayerMarkerRing3;
            break;
        case 0x25:
            f.callback = (void*)DrawPlayerMarkerRing1;
            break;
        case 0x26:
            f.callback = (void*)DrawPlayerMarkerRing2;
            break;
        }
        QueueDeferredRequest(&f);
    }
    {
        Rgba4 c;
        u8 from[4];
        *(u32*)from = 0x800000A0;
        if (self->f26C4 != 0) {
            f32 t;
            if (self->f2220 != 4) {
                t = (g_gameClock[1] - self->f26CC) / self->f26D0;
            } else {
                t = 0.0f;
            }
            f32 s = Cosine((g_gameClock[1] - self->f26C8) * 10.0f);
            f32 p = D_00275140[0] + t * (D_00275140[1] + t * D_00275140[2]);
            f32 x = RingClamp::Of(p, g_unitRange.lo, g_unitRange.hi);
            f32 q = D_00275150[0] + s * (D_00275150[1] + s * D_00275150[2]);
            f32 y = RingClamp::Of(q, g_unitRange.lo, g_unitRange.hi);
            f32 w = x * y;
            f32 u = 1.0f - w;
            c.r = (u8)(u * D_002623E0[0].r + w * from[0]);
            c.g = (u8)(u * D_002623E0[0].g + w * from[1]);
            c.b = (u8)(u * D_002623E0[0].b + w * from[2]);
            c.a = D_002623E0[0].a;
        } else {
            c = D_002623E0[0];
        }
        SetObjectTreeRecordValue(self, *(u32*)&c);
    }
}

s32 GetPlayerRequestPhase(Player* self)
{
    if (self->f2220 != 4) {
        return self->f26C4 != 0;
    }
    if (self->f2228 < 45) {
        return 1;
    }
    return 2;
}

void FinishSwitchedCollider(Player* self);
void SetPlayerState(Player* self, s32 a, s32 b);

void FinishPlayerRequest(Player* self)
{
    if (self->f2730 != 0) {
        FinishSwitchedCollider(self);
        self->f2730 = 0;
    }
    if (self->f26B4.fn != 0) {
        s32 fn = self->f26B4.fn;
        self->f26B4.fn = 0;
        ((void (*)(s32, Player*))fn)(self->f26B4.data, self);
    } else {
        Vec02 v = self->v150;
        v.z = D_00275160 >? v.z;
        const Desc02* d = self->desc02();
        d->m20(self, &v);
        SetPlayerState(self, 2, 6);
    }
    self->f226C = 0.0f;
    self->f2498 = 0;
}

struct HitMessage {
    s32 kind;               // 0x00
    u8 pad04[0x20 - 0x04];
    Vec02 v20;              // 0x20
    f32 f30;                // 0x30
    u8 pad34[0x38 - 0x34];
    Collider* f38;          // 0x38
    u8 pad3C[0x50 - 0x3C];
};

void ComputeOscillatorDisplacement(void* osc, void* pos, f32 t, s32 a, Vec02* out, s32 b, s32 c);
s32 IsObjectOfKind(void* node, s32 kind);
s32 FindPlaneTreeNodeForPoint(void* a, s32 b);
s32 ProbeColliderBelowPoint(Player* self, Collider* col, Vec02* out);
void TransformPointAtTime(void* frame, s32 a, void* point, s32 b, s32 c, s32 d, f32 t);
typedef s32 (*MessageHandlerFn)(Collider* self, s32 a, OwnerMessage* msg);
typedef void (*HitFn)(Collider* self, HitMessage* msg);

void NotifyPlayerGroundObject(Player* self)
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
        i = FindPlaneTreeNodeForPoint(&p, (s32)self->f2438->tree.nodes) != 0;
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
    if (i == 0 || ProbeColliderBelowPoint(self, self->f2438, &out) == 0) {
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

s32 CollectTreeNodeSpans(void* nodes, void* a, void* b, s32 c, s32 d, void* out);

s32 ProbeColliderBelowPoint(Player* self, Collider* col, Vec02* out)
{
    Vec02 moved;
    Vec02 shift;
    Vec02 start;
    Vec02 end;
    ColliderSpan hit;
    if (col->f278 != 0) {
        ComputeOscillatorDisplacement(((void**)col->f278)[3], &self->v140, 50.0f, 0, &moved, 0, 0);
        Vu0::Q(shift) = Vu0::Sub(Vu0::Q(moved), Vu0::Q(self->v140));
    } else {
        shift = D_00248D30;
    }
    u128 base = Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(shift));
    Vu0::Q(end) = base;
    Vu0::Q(start) = base;
    end.z += D_00275164;
    start.z += D_00275168;
    if (CollectTreeNodeSpans(col->tree.nodes, &end, &start, 0, 1, &hit) == 0) {
        return 0;
    }
    Vu0::Q(*out) = Vu0::Add(Vu0::Q(hit.q[0]), Vu0::Q(shift));
    return 1;
}

void ApplyColliderAttachedSetContact(Player* self, void* other, f32 t);
void GetAttachedSetPointMotion(void* obj, Vec02* p, Vec02* out1, Vec02* out2);
f32 ApproachValueClampingVelocity(void* table, f32* out, f32 a, f32 b, f32 c, f32 d);
void AddColliderForce(void* a, void* b);

void ApplyPlayerAttachedSetContact(Player* self, Collider* other, f32 t)
{
    switch (self->f2228) {
    case 6:
    case 0x2B:
        if (self->v150.z < 0.0f) {
            ApplyColliderAttachedSetContact(self, other, t);
        }
        return;
    case 0x27:
    case 0x2F: {
        Vec02 point;
        Vec02 local;
        Vec02 q2;
        Vec02 q3;
        Vec02 force;
        Vec02 k;
        f32 next;
        if (ProbeColliderBelowPoint(self, other, &point) == 0) {
            return;
        }
        Vu0::Q(local) = Vu0::Rotate(self->m660, Vu0::Q(self->v640));
        GetAttachedSetPointMotion(other, &point, &q2, &q3);
        Vu0::Q(k) = Vu0::FromFloatAt(D_00275170[0]);
        Vu0::Set(force, Vu0::MulX(Vu0::Sub(Vu0::Add(Vu0::Q(self->v150), Vu0::Q(local)), Vu0::Q(q2)), Vu0::Q(k)));
        ApproachValueClampingVelocity(D_00275178, &next, self->v140.z + D_0027516C, self->v150.z - q2.z, point.z, t);
        force.z = (next - self->v150.z) / t - self->gravity.z >? force.z;
        AddColliderForce(self, &force);
        return;
    }
    }
    ApplyColliderAttachedSetContact(self, other, t);
}

void SwapInPlayerStandIn(Player* self)
{
    StandIn* obj = (StandIn*)self->f1518;
    if (obj != 0) {
        BaseObject* s0 = 0;
        u32 i = 0;
        while (i < 4) {
            s0 = (BaseObject*)self->f1508[i];
            if (s0 != 0 && IsObjectAttached(s0) != 0) {
                break;
            }
            i++;
        }
        if (i >= 4) {
            s0 = (BaseObject*)self->f1504;
        }
        obj->desc->m02(obj);
        ((VFnB)((void**)obj->desc)[25])(obj, 0);
        ((VFnB)((void**)obj->desc)[35])(obj, s0);
        obj->f690 = g_gameClock[1];
        obj->f694 = 1;
        if (s0 != self->f1504) {
            s0->desc->m03(s0);
        }
    }
}

s32 TestStandInMayContact(StandIn* self, s32 value)
{
    if (value == (s32)g_player) {
        return 1;
    }
    return TestCollidersMayContact(self, value);
}

Quadword ScaleQuadword(Quadword a, Quadword b);
void StepCollider(StandIn* self, f32 t);
void RotateMatrixUpright(Mat02* self, Mat02* scratch, Mat02* out);
void SteerColliderTowardRotation(StandIn* self, Mat02* rot, Vec02* a, Vec02* b, Vec02* c, f32 t);
void SteerColliderTowardPosition(StandIn* self, s32 a, s32 b, Vec02* pos, Vec02* c, f32 t);
extern Quad16 D_00275C40;

// k times the vector at p, into dst (the quadword helpers' product).
static inline void StoreScaledQuadword(Vec02* dst, f32 k, u8* p)
{
    Quadword t;
    StoreFloatAsQuadword(&t, k);
    Quadword tv = t;
    Quadword u;
    CopyQuadword(&u, p);
    StoreQuadword(dst, ScaleQuadword(tv, u));
}

void StepStandIn(StandIn* self, f32 t)
{
    Mat02 upright;
    Vec02 push;
    Vec02 spin;
    Vec02 q50;
    Vec02 q60;
    StepCollider(self, t);
    f32 since = g_gameClock[1] - self->f690;
    f32 age = g_unitRange.Limit(D_002751C0[0] + since * (D_002751C0[1] + since * D_002751C0[2]));
    RotateMatrixUpright(&self->rot, 0, &upright);
    StoreScaledQuadword(&q50, age, (u8*)D_00275190);
    StoreScaledQuadword(&q60, age, (u8*)D_002751A0);
    if (self->f694 != 0) {
        Vu0::Q(spin) = Vu0::MulX(Vu0::Q(self->rot.r[2]), Vu0::ScalarAt(D_00275188));
    } else {
        spin = D_00248D30;
        q50 = *(Vec02*)&D_00275C40;
    }
    SteerColliderTowardRotation(self, &upright, &q50, &spin, &q60, t);
    if (self->f694 != 0) {
        Vu0::Q(push) = Vu0::MulX(Vu0::Q(self->rot.r[0]), Vu0::ScalarAt(D_0027518C));
    } else {
        push = D_00248D30;
    }
    StoreScaledQuadword(&q60, age, (u8*)D_002751B0);
    SteerColliderTowardPosition(self, 0, 0, &push, &q60, t);
}

void StopStandIn(StandIn* self)
{
    HandleChildGroupObjectContact(self);
    self->f694 = 0;
}

void HandleStandInNotification(StandIn* self, s32 kind, ObjectMessage* ref)
{
    HandleChildGroupNotification(self, kind, ref);
    if (kind == 10 && ref->target == self) {
        ((StandIn*)ref->target)->f694 = 0;
    }
}

void InitOwnerMessage(OwnerMessage* self, s32 mode, s32 owner) { FillMemory(self, 0, 0x10); self->owner = owner; self->mode = mode; self->c = owner; }

LINKER_REMNANT(func_001D70E8);

OutputBuffer* InitOutputBuffer(OutputBuffer* self, s32 handle)
{
    self->handle = handle;
    self->targetWord = 0;
    self->capacity = 0;
    self->used = 0;
    self->count = 0;
    self->pending = 0;
    return self;
}

OutputBuffer* InitStringOutputBuffer(OutputBuffer* self, u8* target, s32 capacity) { self->target = target; self->capacity = capacity; self->used = 0; self->handle = -1; self->count = 0; self->pending = 0; return self; }

void DestroyOutputBuffer(OutputBuffer* a0, s32 a1)
{
    FlushOutputBuffer(a0, a1);
    if (a1 & 1) FreeObjectMemory(a0);
}

s32 AppendToOutputBuffer(OutputBuffer* self, void* src, s32 size)
{
    s32 n = size;
    s32 done = 0;

    if (self->target != 0 && self->capacity != 0 && n != 0) {
        s32 avail = self->capacity - self->used;
        if (avail < n) {
            n -= avail;
        }
    }
    if (n == 0) {
        return 0;
    }
    if (self->target != 0) {
        CopyMemory(self->target + self->used, src, n);
        self->used += n;
        done = n;
    } else if (n > 0) {
        do {
            s32 room = 0x400 - self->pending;
            s32 rem = n - done;
            s32 take = (room < rem) ? room : rem;
            if (take != 0) {
                CopyMemory((u8*)self + (self->pending + 0x18), (u8*)src + done, take);
                done += take;
                self->pending += take;
            }
            if (self->pending == 0x400) {
                FlushOutputBuffer(self);
            }
        } while (done < n);
    }
    self->count += done;
    return n;
}

void FlushOutputBuffer(OutputBuffer* self)
{
    u8 buf[0x90];
    s32 done;
    u8* p;
    s32 chunk;
    s32 rem;

    if (self->pending == 0) {
        return;
    }
    if (self->targetWord != 0) {
        return;
    }
    if (self->handle < 0) {
        p = self->buf;
        for (done = 0; done < self->pending; done += chunk) {
            rem = self->pending - done;
            chunk = 0x80;
            if (!(rem > 0x7F)) {
                chunk = rem;
            }
            CopyMemory(buf, p, chunk);
            p += chunk;
            buf[chunk] = 0;
            PrintBuffered((void*)"%s", buf);
        }
    } else {
        WriteFile(self->handle, self->buf, self->pending);
    }
    self->pending = 0;
}

void InitPathFollower(PathFollower* self)
{
    InitSwitchedCollider(self);
    self->f614 = 50.0f;
    self->f610 = 50.0f;
    self->f618 = 3000.0f;
    self->f61C = 1300.0f;
    self->f868 = 2.0f;
    self->fB04 = 3;
    (*(Quad16*)&self->v620) = *(Quad16*)D_00275290;
    CopyMemory(self->f630, D_00275250, 0x40);
    ResetPathFollower(self);
}

void StartPathFollower(PathFollower* self)
{
    BaseObject* buf[16];
    s32 id0;
    s32 id1;
    s32 id2;
    StartPlacedObject(self);
    ResolveObjectLinks(self, 0x14, D_002752A0);
    self->f694 = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    if (self->fB44 != 0) {
        StateTrigger* v = CreateStateWalker(self->fB44, self, -1, 0);
        self->fB48 = v;
        SetStateWalkerTarget(v, self->fB30 == 1 ? 0x484 : 0x384);
    }
    switch (g_currentWorld->f1D70) {
    case 3:
        id0 = self->f550 ? 0x1D2 : 0x1AD;
        id1 = 0x1BB;
        id2 = 0x1AF;
        goto spawn;
    case 5:
        id0 = self->f550 ? 0x2A6 : 0x280;
        id1 = 0x27F;
        id2 = 0x27D;
        goto spawn;
    case 6:
        id0 = self->f550 ? 0x2DE : 0x2DC;
        id1 = 0x2DB;
        id2 = 0x2DD;
    spawn:
        StartSoundEffect(id0, self->fB80, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        StartSoundEffect(id1, self->fB84, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        StartSoundEffect(id2, self->fB7C, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        {
            f32 r = RandomFloatInRange(-0.1f, 0.1f);
            self->fB8C = self->fB90 = self->fB94 = self->fB98 = r;
        }
        break;
    default:
        break;
    }
    {
        void* c = FindFirstObjectById(g_currentWorld, 0x104, 7, self);
        if (c != 0) {
            self->f594 = 200.0f;
            self->fB78 = c;
            self->f598 = c;
        }
    }
    if (self->fB30 == 1) {
        s32 n = GatherObjectsByMode(self->world, 0x105, 0x426, 0, 0x10, buf);
        for (s32 i = 0; i < n; i++) {
            buf[i]->desc->m17(buf[i], self);
        }
        T217D_E30* boxA = &D_00272430;
        T217D_E30* boxB = &D_002726B0;
        ((U32P*)&boxA->own)->v = 0;
        ((U32P*)&boxB->own)->v = 0;
        boxA->target = &boxA->own;
        boxB->target = &boxB->own;
    }
    for (s32 k = 0; k < 4; k++) {
        Slot19* s = &self->f6B0[k];
        s->v10 = s->obj->pos;
    }
    ResetPathFollower(self);
}

extern f32 g_gameClock[];
extern float D_002751D8;
extern float D_002751E0[];
extern float D_002751F0[];
extern float D_00275200[];
extern float D_00275210[];
extern float D_00275220[];
extern float D_00275230[];
extern float D_00275390;
extern f32 D_00275394;
extern Vec02 D_002753A0;
extern float D_002753B0[];
extern float D_002753C0[];
extern float D_002753C8;
extern float D_002753CC;
extern float D_002753D0[];
extern float D_002753E0[];
extern float D_002753F0[];
extern float D_00275400[];
extern float D_00275410;
extern float D_00275414;
extern float D_00275418;
extern float D_0027541C;
extern f32 D_00275420[];
extern f32 D_00275430[];
extern f32 D_00275440[];
extern f32 D_00275448[];
extern f32 D_00275458[];
extern f32 D_00275470[];
extern f32 D_00275480[];
extern f32 D_00275488;

void TransformPointBetweenFrames(void* a0, void* a1, void* a2, void* a3);
void AddColliderForce(void* a, void* b);
void BuildAxisAngleMatrix(const Vec02* t, void* out, f32 x);
f32 ClampToMagnitude(f32 a, f32 b);
void* StoreFloatAsQuadword(void* out, f32 f);
void* CopyQuadword(void* out, void* in);
void* StoreQuadword(void* dst, Quadword v);
void StepCollider(Collider* self, f32 t);
void SteerColliderTowardRotation(Collider* self, Mat02* target, Vec02* pull, const Vec02* aim, Vec02* turn, f32 limit);
void ComputeObjectMotionInFrame(void* obj, s32 z, void* point, Vec02* out, s32 a, s32 b, s32 c);
void ApplyColliderInverseInertia(Collider* self, Vec02* in, Vec02* out);
void AddColliderTorque(Collider* self, Vec02* torque);
Quadword ScaleQuadword(Quadword a, Quadword b);
void ComputePolarOffset(Vec02* out, f32 a, f32 b, f32 c);
void ClampVectorLength(Vec02* in, Vec02* out, f32 max);
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, void* table, f32* out);
void RotateMatrixUpright(Mat02* self, Mat02* scratch, Mat02* out);

// v made unit length into out; returns its length.
static inline f32 NormalizeInto(Vec02& out, Vec02 v)
{
    u128 len = Vu0::Length(Vu0::Q(v));
    Vu0::Q(out) = Vu0::DivX(Vu0::Q(v), len);
    return Vu0::ToFloat(len);
}

void StepPathFollower(PathFollower* self, f32 dt)
{
    StepCollider(self, dt);
    if (g_gameClock[1] - self->f850 > D_00275390 && g_gameClock[1] - self->f86C > D_00275394) {
        Mat02 upright;
        RotateMatrixUpright(&self->rot, 0, &upright);
        SteerColliderTowardRotation(self, &upright, &D_002753A0, 0, 0, dt);
    }
    f32 sum = 0.0f;
    u32 i;
    Slot19* s;
    for (i = 0; i < 4; i++) {
        s = &self->f6B0[i];
        if (s->f0C != self->f6A0) {
            continue;
        }
        Vec02 a;
        Vec02 b;
        Vec02 dir;
        Vec02 motion;
        Vec02 force;
        Vec02 torque;
        Vec02 accel;
        Vec02 spin;
        s32 front = (s32)i < 2;
        a = *(Vec02*)((u8*)s->obj8 + 0x40);
        a.z -= front ? self->f610 : self->f614;
        TransformPointBetweenFrames(self, 0, &a, &a);
        b = s->obj->v190;
        b.z -= front ? self->f610 : self->f614;
        TransformPointBetweenFrames(self, 0, &b, &b);
        Vu0::Q(dir) = Vu0::Sub(Vu0::Q(a), Vu0::Q(b));
        f32 len = NormalizeInto(dir, dir);
        ComputeObjectMotionInFrame(self, 0, &s->v20, &motion, 0, 0, 0);
        u128 axis = Vu0::Q(s->v30);
        u128 side = Vu0::Sub(Vu0::Q(motion), Vu0::MulX(axis, Vu0::Dot(Vu0::Q(motion), axis)));
        f32 slip = Vu0::ToFloatMoved(Vu0::Length(side));
        s->f5C += ((ValueRange*)D_002753C0)->Clamp(((QuadraticCurve*)D_002753B0)->Eval(slip)) * dt;
        f32 along = Vu0::ToFloat(Vu0::Dot(Vu0::Sub(Vu0::Q(s->v20), Vu0::Q(b)), Vu0::Q(dir))) / len;
        f32 one = 1.0f;
        f32 t;
        if (along < 0.0f) {
            t = 0.0f;
        } else if (one < along) {
            t = one;
        } else {
            t = along;
        }
        // The push's two curves are indexed in place: each address is then formed right before
        // its loads, a life of 3 that loop.c's first pass leaves and its second moves, after the
        // copy of &spin (docs/toolchain/loops.md, "Three invariants ranked by their place").
        f32 push = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vu0::Q(s->v40), Vu0::Q(motion)), Vu0::Q(dir)))
                       * (D_002753D0[0] + t * (D_002753D0[1] + t * D_002753D0[2])) * D_002753C8
                 + Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vu0::Q(s->v20), Vu0::Q(b)), Vu0::Q(dir)))
                       * (D_002753E0[0] + t * (D_002753E0[1] + t * D_002753E0[2])) * D_002753CC;
        if (push < 0.0f) {
            continue;
        }
        f32 mass = self->mass;
        push *= mass;
        Vu0::Q(force) = Vu0::MulX(Vu0::Q(dir), Vu0::Scalar(push));
        Vu0::Q(torque) = Vu0::Cross(Vu0::Sub(Vu0::Q(s->v20), Vu0::Q(self->v140)), Vu0::Q(force));
        *(u128*)&accel = Vu0::DivX(Vu0::Q(force), Vu0::Scalar(mass));
        ApplyColliderInverseInertia(self, &torque, &spin);
        AddColliderForce(self, &accel);
        AddColliderTorque(self, &spin);
        sum += Vu0::ToFloat(Vu0::Dot(Vu0::Q(force), Vu0::Q(self->rot.r[2])));
    }
    if (sum == 0.0f) {
        f32 t = (g_gameClock[1] - self->f86C) / D_00275394;
        f32 k = g_unitRange.Clamp(((QuadraticCurve*)D_002753F0)->Eval(t));
        u8* p = (u8*)D_00275400;
        Quadword q;
        StoreFloatAsQuadword(&q, k);
        Quadword qv = q;
        Quadword u;
        CopyQuadword(&u, p);
        Vec02 turn;
        StoreQuadword(&turn, ScaleQuadword(qv, u));
        SteerColliderTowardRotation(self, 0, 0, &D_00248D30, &turn, dt);
    }
    f32 one = 1.0f;
    f32 drive = sum / (self->mass * D_00275410);
    if (drive < 0.0f) {
        drive = 0.0f;
    } else if (one < drive) {
        drive = one;
    }
    self->fB9C = drive;
    f32 grip = self->fAFC != 0 ? self->fAFC->f18 : self->f868;
    f32 lap = (g_gameClock[1] - self->f854) / D_002751D8;
    f32 limit = D_00275414 <? grip * sum / self->mass;
    f32 w = ((ValueRange*)D_00275210)->Clamp(((QuadraticCurve*)D_00275200)->Eval(lap));
    if (1.0f < self->f85C) {
        w *= self->f85C * self->f85C;
    }
    limit *= w;
    Vec02 vel;
    Vu0::Q(vel) = Vu0::MulAddX(Vu0::Vec::Of(self->v150), Vu0::Vec::Of(self->v170), Vu0::Vec::ScalarInGpr(dt)).q;
    Vec02 local;
    Vu0::Q(local) = Vu0::RotateTransposed(self->rot, Vu0::Q(vel));
    f32 span = self->f6B0[0].obj->v190.x - self->f6B0[2].obj->v190.x;
    f32 rate = self->f698 / self->f618;
    f32 r;
    if (rate < 0.0f) {
        r = 0.0f;
    } else if (1.0f < rate) {
        r = 1.0f;
    } else {
        r = rate;
    }
    r *= g_unitRange.Clamp(((QuadraticCurve*)D_00275420)->Eval(local.x / self->f618));
    f32 yaw = (local.x <? D_0027541C) * self->f69C;
    f32 r2 = r * self->f69C;
    Vec02 spinL;
    Vu0::Q(spinL) = Vu0::RotateTransposed(self->rot, Vu0::Q(self->v160));
    f32 inertia = self->mass * __builtin_fabsf(self->f6B0[0].obj->v190.x) / self->inertia.r[2].z;
    Vec02 c;
    c.x = c.y = 0.0f;
    f32 tq = ClampToMagnitude((yaw / span + r2 * D_00275418 - spinL.z) / dt, inertia * limit);
    c.z = tq;
    inertia = tq / inertia;
    Vec02 torque2;
    Vu0::Q(torque2) = Vu0::Rotate(self->rot, Vu0::Q(c));
    limit -= __builtin_fabsf(inertia);
    AddColliderTorque(self, &torque2);
    f32 lean = ((ValueRange*)D_002751F0)->Clamp(((QuadraticCurve*)D_002751E0)->Eval(lap)) * self->f85C;
    f32 tilt = (D_002751F0[1] <? lean) / self->f85C;
    Vec02 heading;
    ComputePolarOffset(&heading, self->f694, 1.0f, 0.0f);
    f32 h = ((ValueRange*)D_00275440)->Limit(((QuadraticCurve*)D_00275430)->Eval(Vu0::ToFloatMoved(Vu0::Dot(Vu0::Q(heading), Vu0::Q(self->rot.r[0])))));
    Vec02 want;
    Mat02 roll;
    BuildAxisAngleMatrix(&g_unitZVector, &roll, (spinL.z + c.z * (dt * 0.5f)) * dt);
    f32 speed;
    if (1.0f < tilt) {
        speed = tilt * self->f618;
    } else {
        speed = tilt * h * self->f698;
    }
    Vu0::Q(want) = Vu0::FromFloats(speed, 0.0f, 0.0f);
    Vu0::Q(want) = Vu0::RotateUntied(roll, Vu0::Q(want));
    f32 maxAccel = ((ValueRange*)D_00275230)->Limit(((QuadraticCurve*)D_00275220)->Eval(lap));
    Vec02 delta;
    Vec02 world;
    Vec02 clamped;
    Vu0::Q(delta) = Vu0::DivX(Vu0::Sub(Vu0::Vec::Of(want), Vu0::Vec::Of(local)), Vu0::Vec::ScalarInGpr(dt)).q;
    delta.z = 0.0f;
    ClampVectorLength(&delta, &clamped, limit >? maxAccel);
    if (self->f698 != 0.0f && self->fB30 == 0) {
        f32 out;
        if (local.x < self->f698) {
            ApproachValueWithRamp(local.x, self->f698, dt, D_00275448, &out);
            clamped.x = (out >? maxAccel) <? clamped.x;
        } else {
            ApproachValueWithRamp(local.x, self->f698, dt, D_00275458, &out);
            clamped.x = out >? clamped.x;
        }
    }
    Vu0::Q(world) = Vu0::Rotate(self->rot, Vu0::Q(clamped));
    AddColliderForce(self, &world);
    for (i = 0; i < 4; i++) {
        s = &self->f6B0[i];
        if (s->f0C == self->f6A0) {
            f32 p = ((ValueRange*)D_00275480)->Limit(((QuadraticCurve*)D_00275470)->Eval(Vu0::ToFloat(Vu0::Length(Vu0::Q(delta))) * dt));
            s->f58 += p * g_gameClock[2];
        }
    }
    Vec02 tq3;
    Vu0::Q(tq3) = Vu0::Cross(Vu0::MulX(Vu0::Q(self->rot.r[2]), Vu0::ScalarAt(D_00275488)), Vu0::MulX(Vu0::Q(world), Vu0::ScalarAt(self->mass)));
    ApplyColliderInverseInertia(self, &tq3, &torque2);
    AddColliderTorque(self, &torque2);
}

f32 FindNearestValueOutsideSpans(s32 count, ValueRange* spans, f32 x)
{
    if (IsInsideAnyRange(count, spans, x) == 0) {
        return x;
    }
    f32 bestDist = 3.4028234663852886e+38f;
    f32 best = bestDist;
    if (count > 0) {
        ValueRange* s = spans;
        s32 n = count;
        do {
            f32 d = __builtin_fabsf(x - s->lo);
            if (d < bestDist) {
                if (IsInsideAnyRange(count, spans, s->lo) == 0) {
                    best = s->lo;
                    bestDist = d;
                }
            }
            d = __builtin_fabsf(x - s->hi);
            if (d < bestDist) {
                if (IsInsideAnyRange(count, spans, s->hi) == 0) {
                    best = s->hi;
                    bestDist = d;
                }
            }
            s++;
            n--;
        } while (n != 0);
    }
    return best;
}

void UpdatePathFollowerPace(PathFollower* self)
{
    if (self != GetActiveSwitchedCollider()) {
        self->f85C = ApproachValueWithRamp((u8*)D_00275490, 0, self->f85C, self->f860, g_gameClock[2]);
        if (!(g_gameClock[1] < self->f864)) {
            f32 one = 1.0f;  // hoisted: retail holds 1.0f in $f3 before the multiply
            s32 idx = 3 * (self->fB00 - 1) + self->fAF8->index;
            f32 t = (f32)idx * 0.1f;
            f32 w;
            if (t < 0.0f) {
                w = 0.0f;
            } else if (one < t) {
                w = one;
            } else {
                w = t;
            }
            f32 val = ((QuadraticCurve*)&self->f670)->Eval(w);
            f32 lo = self->f680;
            f32 hi = self->f684;
            if (val < lo) {
                val = lo;
            } else if (hi < val) {
                val = hi;
            }
            self->f860 = val;
            f32 r = RandomFloatInRange(-0.05f, 0.05f);
            self->f860 = self->f860 + r;
            f32 r2 = RandomFloatInRange(D_002754A0[0], D_002754A0[1]);
            self->f864 = g_gameClock[1] + r2;
        }
    }
}

f32 GetWrappedDifference(f32 x, f32 lim, f32 base)
{
    f32 d = lim - base;
    if (x * 0.5f < d)
        d = d - x;
    else if (d < x * -0.5f)
        d = d + x;
    return d;
}

s32 IsPathFollowerAhead(PathFollower* self, PathFollower* other)
{
    s32 d = self->fB00 - other->fB00;
    if (d > 0) return 1;
    if (d < 0) return 0;
    d = self->fAF8->index - other->fAF8->index;
    if (d > 0) return 1;
    if (d < 0) return 0;
    f32 r = GetWrappedDifference(self->f834, self->f83C, other->f83C);
    return 0.0f < r;
}

s32 GatherObjectsById(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
f32 WrapModulo(f32 x, f32 y);
s32 IsInsideRange(ValueRange* range, f32 x);
void FindPathCurveNearestTime(PathCurve* self, Vec02* lo, Vec02* hi, Vec02* out, s32 a4, f32* time,
                              f32* a6, f32 start);

void AdvancePathFollowerAlongPath(PathFollower* self, s32* nearby)
{
    PathFollower* list[16];
    ValueRange spans[16];
    Vec02 pos;
    Vec02 tangent;
    Vec02 dir;
    Vec02 lo;
    Vec02 hi;
    Vec02 out;
    s32 n = GatherObjectsById(self->world, 5, 0x19, 0, 0x10, list);
    s32 count = 0;
    s32 k = 0;
    for (s32 i = 0; i < n; i++) {
        PathFollower* o = list[i];
        if (o == self) {
            continue;
        }
        if (o->f830 != self->f830) {
            continue;
        }
        if (IsPathFollowerAhead(self, o)) {
            continue;
        }
        count++;
        f32 d = WrapModulo(o->f83C - self->f83C, o->f834);
        f32 r = ((ValueRange*)D_002754C0)->Limit(((QuadraticCurve*)D_002754B0)->Eval(d));
        if (r <= 0.0f) {
            continue;
        }
        ValueRange* s = &spans[k++];
        s->lo = o->f840 - r;
        s->hi = o->f840 + r;
    }
    *nearby = count;
    ValueRange* s = &spans[k++];
    s->lo = -1e6f;
    s->hi = -self->f61C;
    s = &spans[k++];
    s->lo = self->f61C;
    s->hi = 1e6f;
    PathCurve* c = self->f830->curve;
    c->vt->m06(c, self->f83C + D_002751D0);
    c = self->f830->curve;
    if (c->vt->m02) {
        ((void (*)(PathCurve*, f32, Vec02*, Vec02*))c->vt->m02)(c, self->f83C + D_002751D0, &pos, &tangent);
    }
    u128 side = Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(tangent));
    Vu0::Q(dir) = Vu0::DivX(side, Vu0::Length(side));
    Vu0::Q(lo) = Vu0::MulAddX(Vu0::Q(pos), Vu0::Q(dir), Vu0::ScalarAt(D_002754C8.lo));
    Vu0::Q(hi) = Vu0::MulAddX(Vu0::Q(pos), Vu0::Q(dir), Vu0::ScalarAt(D_002754C8.hi));
    FindPathCurveNearestTime(self->f848->curve, &lo, &hi, &out, 0, &self->f84C, 0, self->f84C);
    f32 ahead = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vu0::Q(out), Vu0::Q(pos)), Vu0::Q(dir)));
    f32 want = ApproachValueWithRamp(D_002754D0, 0, self->f844, ahead, g_gameClock[2]);
    f32 best = FindNearestValueOutsideSpans(k, spans, want);
    if (!IsInsideRange(&D_002754C8, best)) {
        best = want;
    } else {
        if (k > 0) {
            f32 cur = self->f840;
            ValueRange* s = spans;
            s32 j = k;
            do {
                if (cur < best && cur < s->lo && s->lo < best) {
                    best = s->lo;
                } else if (best < cur && s->hi < cur && best < s->lo) {
                    best = s->hi;
                }
                s++;
                j--;
            } while (j != 0);
        }
    }
    self->f844 = best;
}

f32 ComputeAngleBetweenVectors(Vec02* a, Vec02* b, Vec02* axis);

void ComputePathFollowerHeadingTarget(PathFollower* self)
{
    Vec02 pos;
    Vec02 tangent;
    Vec02 side;
    Vec02 w;
    Vec02 ahead;
    if (self->f830 != 0) {
        PathCurve* o = self->f830->curve;
        if (o->vt->m02 != 0) {
            ((void (*)(PathCurve*, f32, void*, void*))o->vt->m02)(o, self->f83C + D_002751D0, &pos, &tangent);
        }
        u128 base = Vu0::Q(pos);
        u128 c = Vu0::Cross(Vu0::Q(g_unitZVector), Vu0::Q(tangent));
        u128 k = Vu0::FromFloatAt(self->f844);
        Vu0::Q(side) = Vu0::DivX(c, Vu0::Length(c));
        Vu0::Set(ahead, k);
        u128 p2 = Vu0::MulAddX(base, Vu0::Q(side), k);
        Vu0::Q(w) = Vu0::Sub(p2, Vu0::Q(*(Vec02*)((u8*)self + 0x100)));
        Vu0::Q(pos) = p2;
        self->f694 = ArctangentOfRatio(w.y, w.x);
        o = self->f830->curve;
        if (o->vt->m02 != 0) {
            ((void (*)(PathCurve*, f32, void*, void*))o->vt->m02)(o, self->f83C + D_002751D0 + D_002754DC, 0, &ahead);
        }
        f32 turn = ComputeAngleBetweenVectors(&tangent, &ahead, 0);
        self->f698 = self->f85C * self->f618;
        u8* limit = *(u8**)((u8*)self + 0xAFC);
        if (limit != 0) {
            self->f698 = *(f32*)(limit + 0x1C) <? self->f698;
        }
        if (0.0f < turn) {
            f32 v = Fpu::Sqrt(D_002754E0[0] * (D_002754DC / turn) * self->f868 * -*(f32*)((u8*)self + 0x358));
            if (v < self->f698) {
                self->f698 = v;
            }
        }
    }
}

void SteerPathFollower(PathFollower* self)
{
    f32 a = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    f32 b = WrapAngle(self->f694 - a);
    f32 c = ClampToMagnitude(D_002754F8 * b, D_002754F4);
    self->f69C = ApproachAngleWithRamp((u8*)D_002754E8, 0, self->f69C, c, g_frameDt);
    for (u32 i = 0; i < 4; i++) {
        Slot19* s = &self->f6B0[i];
        if ((s32)i < 2) {
            s->f50 = self->f698 / self->f610;
        } else {
            s->f50 = self->f698 / self->f614;
        }

    }
}
