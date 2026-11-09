// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "base_object.h"
#include "switched_collider.h"
#include "globals.h"
#include "screen_element.h"
#include "attachment.h"
#include "animation.h"
#include "owner_message.h"

// A quadratic in t (c[0] + t * (c[1] + t * c[2])), on 16 bytes: the file's four start on a
// 16-byte line, so 0x274A48 is padding after the float before the first.
struct __attribute__((aligned(16))) PaddedQuadratic { f32 c[3]; };

// The file's .data, in retail's order.
s32 D_002749B0[36] = { 4, 1317, 1632, 4, 1320, 1580, 2, 354, 1420, 2, 355, 1424, 6, 352, 1412, 0, 1319, 1636, 0, 1321, 1560, 0, 1322, 1564, 0, 1323, 1568, 0, 1324, 1572, 0, 1325, 1652, 0, 1326, 1656 };
char D_00274A40[4] = "\r";
f32 D_00274A44 = 150.0f;
PaddedQuadratic D_00274A50 = { { 0.2f, 0.0f, 0.0f } };
f32 D_00274A60[3] = { 40.0f, 0.0f, 0.3f };
PaddedQuadratic D_00274A70 = { { 1.0f, 0.0f, -0.75f } };
PaddedQuadratic D_00274A80 = { { 0.7f, 0.3f, 0.0f } };
f32 D_00274A90[2] = { 1200.0f, 1.0f };
f32 D_00274A98 = 0.25f;
f32 D_00274A9C = 3000.0f;
f32 D_00274AA0 = 0.1f;
f32 D_00274AA8[3] = { 20.0f, 0.0f, 0.3f };
f32 D_00274AB4 = 1000.0f;
f32 D_00274AB8[2] = { 0.0f, 300.0f };
PaddedQuadratic D_00274AC0 = { { -1.0f, 1.0f, 0.0f } };

void InitSwitchedCollider(void* self);

void InitHitCountCollider(HitCountCollider* self)
{
    InitSwitchedCollider(self);
    self->f610 = -1;
    self->f694 = 5;
}

// Two floats (+0x2DC, +0x2E0 of f62C) copied as one unaligned doubleword, and a pointer stored
// unaligned into a screen element.
struct __attribute__((packed)) UnalignedFloatPair { u64 v; };
struct __attribute__((packed)) UnalignedPointer { void* p; };


void StartPlacedObject(void* self);
void ResolveObjectLinks(void* self, s32 n, void* table);
void* CreateStateWalker(void* a, void* self, s32 b, s32 c);
f32 ArctangentOfRatio(f32 a, f32 b);
void SetWorldActiveFollower(void* sub, void* self);
void SetHitCountColliderState(void* self, s32 flag);

void StartHitCountCollider(HitCountCollider* self)
{
    StartPlacedObject(self);
    self->f68C = self->radius3CC;
    ResolveObjectLinks(self, 0xC, D_002749B0);
    self->f668 = CreateStateWalker(self->f664, self, -1, 0);
    self->f644 = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    PlacedObject* v = self->f660;
    self->f648 = ArctangentOfRatio(v->rot.r[0].y, v->rot.r[0].x);
    *(UnalignedFloatPair*)&self->f630 = *(UnalignedFloatPair*)((u8*)self->f62C + 0x2DC);
    u8* g1 = (u8*)&D_0026DD48;
    ((UnalignedPointer*)(g1 + 0x264))->p = (u8*)self + 0x690;
    u8* g2 = (u8*)&D_0026DFC8;
    ((UnalignedPointer*)(g2 + 0x264))->p = (u8*)self + 0x694;
    *(void**)(g1 + 0x268) = D_00274A40;
    *(f32*)(g2 + 0x26C) = 4.0f;
    SetWorldActiveFollower(self->world, self);
    s32 c = self->f71C;
    self->f720[c] = self;
    self->f71C = c + 1;
    SetHitCountColliderState(self, 1);
}

extern f32 g_unitRange[];
extern f32 g_gameTime[];
extern f32 g_stepScale;
extern f32 g_gameClock[];
extern s32 D_0026E228[8];

void UpdateSwitchedCollider(void* self, f32 t);
void* FindFirstObjectByIdGathered(void* a, s32 b, s32 c, s32 d);
void SendEmptyMessage(void* x);
void SendHitCountColliderRequest(void* self, s32 v);
void StopAnimationPlayer(void* p);
void CreateAnimationPlayerWithoutPresetTargets(void* a, void* b, s32 c, void* d, f32 fa, f32 fb);
f32 ArctangentOfRatio(f32 a, f32 b);
void BuildAxisAngleMatrix(void* a, void* b, f32 f);
void ApproachRotationWithRamp(void* a, void* b, void* c, void* d, s32 e, f32 f);
f32 Cosine(f32 a);
void SetObjectTreeRecordValue(void* o, u32 v);

void UpdateHitCountCollider(HitCountCollider* self, f32 t)
{
    f32 buf[12];
    f32 buf2[12];
    u32 ca[4];
    u32 cb[4];
    UpdateSwitchedCollider(self, t);
    if (self->f688) {
        void* h = FindFirstObjectByIdGathered(self->world, 0x101, 0x77, (s32)self->f688);
        if (h) SendEmptyMessage(h);
        self->f690 = self->f690 + 1;
        self->f688->desc->m03(self->f688);
        self->f688 = 0;
    }
    if (self->f684) {
        SendHitCountColliderRequest(self, self->f684);
        self->f684 = 0;
    }
    if (self->f67C) {
        if (self->f67C->speed == 0.0f) {
            StopAnimationPlayer(self->f67C);
            self->f67C = 0;
        }
    } else if (self->f680) {
        CreateAnimationPlayerWithoutPresetTargets(self->f678, self, 0, &self->f67C, 0.0f, 1.0f);
        self->f694 = self->f694 - 1;
        D_0026E228[0] = -1;
    }
    self->f680 = 0;
    f32 u;
    if (self->f67C) {
        f32* lim = g_unitRange;
        f32 r = self->f67C->time / self->f67C->anim->length;
        f32* pp = D_00274A50.c;
        f32 lo = lim[0];
        f32 hi = lim[1];
        f32 v = pp[0] + r * (pp[1] + r * pp[2]);
        if (v < lo) v = lo;
        else if (hi < v) v = hi;
        g_stepScale = v;
        u = r;
    } else {
        g_stepScale = 1.0f;
        u = 0.0f;
    }
    f32 w = u * D_00274A44 + (1.0f - u) * self->f68C;
    self->radius3D0 = w;
    self->radius3CC = w;
    if (self->f638) {
        if (g_gameTime[0] - self->f640 > 2.0f) self->f638 = 0;
    }
    f32 ang = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    BuildAxisAngleMatrix((u8*)&g_unitZVector, buf, self->f648 - ang);
    ApproachRotationWithRamp(&self->f660->rot, buf, D_00274A60, buf2, 0, t);
    self->f660->desc02()->m1E(self->f660, (Mat02*)buf2);
    ca[0] = 0x8010FF00;
    cb[0] = 0x800000FF;
    if (self->f638) {
        f32 q;
        if (self->f610 != 2) q = (g_gameClock[1] - self->f614) * 0.5f;
        else q = 0.0f;
        f32 z = Cosine((g_gameClock[1] - self->f63C) * 10.0f);
        f32 x0 = D_00274A70.c[0] + q * (D_00274A70.c[1] + q * D_00274A70.c[2]);
        f32 lo = g_unitRange[0];
        f32 hi = g_unitRange[1];
        f32 x = x0 < lo ? lo : (hi < x0 ? hi : x0);
        f32 y = D_00274A80.c[0] + z * (D_00274A80.c[1] + z * D_00274A80.c[2]);
        f32 lo2 = g_unitRange[0];
        f32 hi2 = g_unitRange[1];
        if (y < lo2) y = lo2;
        else if (hi2 < y) y = hi2;
        f32 m = x * y;
        f32 n = 1.0f - m;
        f32 r0 = n * ((u8*)ca)[0] + m * ((u8*)cb)[0];
        f32 r1 = n * ((u8*)ca)[1] + m * ((u8*)cb)[1];
        f32 r2 = n * ((u8*)ca)[2] + m * ((u8*)cb)[2];
        ((u8*)ca)[0] = (s32)r0;
        ((u8*)ca)[2] = (s32)r2;
        ((u8*)ca)[1] = (s32)r1;
    }
    SetObjectTreeRecordValue(self, ca[0]);
    *(f32*)(((u8*)self->f62C) + 0x2DC) = self->f670 * self->f630;
    *(f32*)(((u8*)self->f62C) + 0x2E0) = self->f670 * self->f634;
    *(s32*)(((u8*)self->f62C) + 0x32C) = 0;
}

bool AreMenusAndFadeClear();

void ShowHitCountColliderCounters()
{
    if (AreMenusAndFadeClear()) {
        D_0026DD48.vt->m14(&D_0026DD48);
        D_0026DFC8.vt->m14(&D_0026DFC8);
    } else {
        D_0026DD48.vt->m15(&D_0026DD48);
        D_0026DFC8.vt->m15(&D_0026DFC8);
    }
}

#define F(o, off) (*(f32*)((u8*)(o) + (off)))
#define W(o, off) (*(s32*)((u8*)(o) + (off)))
#define P(o, off) (*(void**)((u8*)(o) + (off)))

void func_00144FF8(Camera* cam, void* ev, s32 n, f32* out);
void func_001B64D8(void* walker, s32 id);
void func_00192A70(void* self, void* ev);
void func_00129DF8(void* self);
void func_001ED650(void* out, f32 a, f32 b, f32 c);
void func_001C3FC8(void* self, s32 state);

void func_001C39A0(HitCountCollider* self, void* ev)
{
    void* obj = P(self, 0x628);
    if (obj != 0 && F(obj, 0x18) == 0.0f) {
        switch (self->f610) {
        case 2:
            self->desc05()->m50(self);
            break;
        case 3:
            func_001C3FC8(self, 4);
            break;
        }
    }
    if (self->f610 != 1) {
        F(self, 0x66C) = D_00274A98;
        *(Vec02*)((u8*)self + 0x650) = D_00248D30;
    } else {
        if (0.0f < F(ev, 0x48)) {
            func_00144FF8(g_camera, ev, 0, &self->f644);
        }
        f32 k = D_00274A90[0];
        f32 m = D_00274A98;
        m = m >? F(ev, 0x48);
        F(self, 0x66C) = m;
        func_001ED650((u8*)self + 0x650, self->f644, k * F(ev, 0x48), 0.0f);
        self->f670 = (D_00274AA0 >? F(ev, 0x48));
        if (0.0f < F(ev, 0x7C)) {
            func_00144FF8(g_camera, ev, 1, &self->f648);
            if (self->f668 != 0) {
                func_001B64D8(self->f668, 0x485);
            }
        } else if (self->f668 != 0) {
            func_001B64D8(self->f668, 0x484);
        }
    }
    func_00192A70(self, ev);
    func_00129DF8(self);
}


void StepCollider(Collider* self, f32 t);
void BuildYawPitchMatrix(Mat02* out, f32 yaw, f32 pitch);
void TurnColliderTowardRotation(Collider* self, f32 scale, Mat02* rot, f32* data);
void ClampVectorLength(Vec02* v, Vec02* out, f32 max);
void AddColliderForce(void* a, void* b);

void func_001C3B40(HitCountCollider* self, f32 dt)
{
    Mat02 rot;
    Vec02 accel;
    Vec02 t;
    StepCollider(self, dt);
    BuildYawPitchMatrix(&rot, self->f644, 0.0f);
    TurnColliderTowardRotation(self, dt, &rot, D_00274AA8);
    Vu0::Q(accel) = Vu0::Sub(Vu0::Q(*(Vec02*)((u8*)self + 0x650)), Vu0::Q(self->v150));
    ClampVectorLength(&accel, &accel, D_00274A9C * F(self, 0x66C) * dt);
    Vu0::Q(t) = Vu0::FromFloat(dt);
    Vu0::Q(accel) = Vu0::DivX(Vu0::Q(accel), Vu0::Q(t));
    AddColliderForce(self, &accel);
}

s32 IsObjectOfKind(s32 a, s32 b);
s32 MatchesObjectId(s32 a, s32 b);

void NoteHitCountColliderContact(HitCountCollider* self, Contact03* c, s32 end)
{
    ContactEnd03* e = &c->end[1 - end];
    if (IsObjectOfKind((s32)e->body, 0x21)) {
        if (self->f694 > 0) {
            self->f680 = 1;
            return;
        }
        if (self->f67C == 0) self->f684 = (s32)e->body;
        return;
    }
    if (MatchesObjectId((s32)e->body, 0x52F)) self->f688 = e->body;
}

INCLUDE_ASM(func_001C3C98);

extern s32 g_buttonCodeFlags;
s32 IsPadSelectFlagHeld(void* p);

s32 IsHitCountColliderRequestBlocked(HitCountCollider* self)
{ if ((g_buttonCodeFlags & 1) || IsPadSelectFlagHeld(self->world)) return 1; return 0; }

// What slot 76 tells its own slot 14 (kind 0x17) when it is hit: itself and the message's owner.
struct OwnerNotice { void* sender; s32 owner; };
s32 HasSpareCount();
void SetHitCountColliderState(void* self, s32 flag);

s32 AcceptHitCountColliderRequest(HitCountCollider* self, OwnerMessage* arg)
{
    OwnerNotice local;
    s32 m;
    if (self->desc05()->m4B(self, arg->mode)) return 0;
    if (arg->mode == 0) {
        if (arg->reply != 0) arg->reply(arg->c, self);
    }
    m = self->f610;
    if (m < 5) {
        if (!(m < 2)) return 1;
    }
    if (self->f638 != 0) return 1;
    if (HasSpareCount()) {
        SetHitCountColliderState(self, 2);
        self->f638 = 1;
        self->f63C = g_gameTime[0];
    } else {
        SetHitCountColliderState(self, 3);
    }
    local.sender = self;
    local.owner = arg->owner;
    self->desc->m0E(self, 0x17, &local);
    return 1;
}

s32 HasHitCountColliderAcceptedRequest(HitCountCollider* self) { if (self->f610 < 5) { if (self->f610 >= 2) return 1; } return self->f638 != 0; }

void FinishSwitchedCollider(void* self);
void SetHitCountColliderState(void* self, s32 flag);

void FinishHitCountCollider(HitCountCollider* self)
{
    FinishSwitchedCollider(self);
    SetHitCountColliderState(self, 1);
}

void func_001C3EB0(s32 c, void* receiver)
{
    PlacedObject* from = (PlacedObject*)c;
    PlacedObject* to = (PlacedObject*)receiver;
    Vec02 d;
    Vec02 v;
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(to->v140), Vu0::Q(from->v140));
    d.z = 0.0f;
    u128 s = Vu0::ScalarAt(D_00274AB4);
    Vu0::Set(v, Vu0::MulX(Vu0::NormalizeOr(Vu0::Q(d), Vu0::Q(g_unitXVector)), s));
    to->desc02()->m20(to, &v);
}

void InitOwnerMessage(void* self, s32 a, s32 b);

void SendHitCountColliderRequest(HitCountCollider* self, s32 value)
{
    OwnerMessage local;
    InitOwnerMessage(&local, 0, value);
    local.c = value;
    local.reply = func_001C3EB0;
    self->desc05()->m4C(self, (void*)&local);
}

extern f32 g_gameClock[];
extern s32 D_0026E228[8];
extern u8 g_scatterController[];

f32 ArctangentOfRatio(f32 a, f32 b);
f32 WrapAngle(f32 a);
f32 ApproachAngleWithRamp(f32 x, f32 y, f32 z, u8* a, void* out);
void RaiseScatterLevels(u8* a, f32 b);
void SetPauseMenuLayerPage(T217D_6D0* a, s32 b, s32 c);
void ReplaceAnimationPlayer(void* a, PlacedObject* b, s32 c, void* d, f32 e, f32 f);

void SetHitCountColliderState(PlacedObject* self, s32 state)
{
    void* s2;
    f32 f12;
    if (state == W(self, 0x610)) return;
    if (W(self, 0x610) == 2) {
        f32 t = g_gameClock[1];
        W(self, 0x694) = 3;
        F(self, 0x640) = t;
    }
    W(self, 0x670) = 0;
    if (state < 4) if (state >= 2) {
        Vec02 q;
        f32 a = ArctangentOfRatio(F(self, 0x154), F(self, 0x150));
        f32 b = WrapAngle(a + 3.14159274f);
        F(self, 0x644) = b;
        F(self, 0x648) = b;
        q = D_00248D30;
        f32 r = ArctangentOfRatio(F(self, 0xD4), F(self, 0xD0));
        ApproachAngleWithRamp(r, F(self, 0x644), 0.0f, (u8*)D_00274AA8, (u8*)&q + 8);
        self->desc02()->m21(self, (Vec02*)&q);
        W(self, 0x694) = 0;
        D_0026E228[0] = -1;
        if (state == 3) RaiseScatterLevels(g_scatterController, 1.0f);
    }
    f12 = 0.0f;
    switch (state) {
    case 0: s2 = P(self, 0x618); break;
    case 1: s2 = P(self, 0x61C); break;
    case 2: s2 = P(self, 0x620); F(self, 0x640) = 3.4028235e+38f; break;
    case 3: s2 = P(self, 0x624); break;
    case 4:
        SetPauseMenuLayerPage(&g_pauseMenuElement, 0, 0x1A);
        s2 = P(self, 0x624);
        f12 = F(s2, 0x34);
        break;
    }
    ReplaceAnimationPlayer(s2, self, 1, (u8*)self + 0x628, f12, 1.0f);
    W(self, 0x610) = state;
    F(self, 0x614) = g_gameClock[1];
}

void AddHitCountColliderId(HitCountCollider* self, s32 value)
{
    s32 n = self->f698;
    self->f69C[n] = value;
    self->f698 = n + 1;
}

s32 IsObjectAttached(void* p);
void ConvertPositionToWorld(void* obj, Vec02* out);
void FadeInPlacedObject(PlacedObject* self, f32 t);
s32 IsObjectOfKind(void* obj, s32 kind);
f32 RandomFloatInRange(f32 a, f32 b);

void func_001C41A0(HitCountCollider* self, PlacedObject* obj)
{
    s32 i;
    for (i = 0; i < self->f71C; i++) {
        if (self->f720[i] == obj) {
            break;
        }
    }
    s32 n = i + 1;
    if (!IsObjectAttached(obj)) {
        Vec02 p;
        Vec02 best;
        best = D_00248D30;
        f32 bestDist = 0.0f;
        for (s32 j = 0; j < self->f698; j++) {
            ConvertPositionToWorld((void*)self->f69C[j], &p);
            f32 nearest = 3.40282347e+38f;
            for (s32 k = 0; k < self->f71C; k++) {
                PlacedObject* o = (PlacedObject*)self->f720[k];
                if (IsObjectAttached(o)) {
                    u128 d = Vu0::Sub(Vu0::Q(p), Vu0::Q(o->pos));
                    nearest = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(d, d))) <? nearest;
                }
            }
            if (bestDist < nearest) {
                bestDist = nearest;
                best = p;
            }
        }
        FadeInPlacedObject(obj, 1.0f);
        best.z = obj->pos.z;
        obj->desc02()->m1D(obj, &best);
        if (IsObjectOfKind(obj, 0x21)) {
            Vec02 vel;
            Vec02 spin;
            ComputePolarOffset(&vel, RandomFloatInRange(-3.1415927f, 3.1415927f), RandomFloatInRange(D_00274AB8[0], D_00274AB8[1]), 0.0f);
            obj->desc02()->m20(obj, &vel);
            Vu0::Set(spin, Vu0::FromFloats(0.0f, 0.0f, RandomFloatInRange(D_00274AC0.c[0], D_00274AC0.c[1])));
            obj->desc02()->m21(obj, &spin);
        }
    }
    self->f720[i] = obj;
    self->f71C = n >? self->f71C;
}
