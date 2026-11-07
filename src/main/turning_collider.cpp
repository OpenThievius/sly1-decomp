// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "fpu.h"
#include "globals.h"
#include "object_link.h"
#include "attachment.h"


// The file's .rodata: the constants only its assembly reads.
extern const f32 D_0024D588 = 3.40282347e+38f;
extern const f32 D_0024D58C = 3.40282347e+38f;
extern const f32 D_0024D590 = 3.40282347e+38f;
extern const f32 D_0024D594 = 3.40282347e+38f;

// The file's .data, in retail's order.
f32 D_00274AD0[2] = { 1.0f, -1.0f };
ObjectLink g_turningColliderLinks[6] = { {6, 0x36, 0x61C}, {6, 0x35, 0x618}, {6, 0x37, 0x628}, {6, 0x3A, 0x62C}, {6, 0x38, 0x620}, {6, 0x3B, 0x624} };
f32 D_00274B20 = 0.5f;
Vec02 D_00274B30 = { 1.0f, -1.0f, 0.0f, 0.0f };
s32 D_00274B40[3] = { 0x453B8000, 0, 0x40000000 };
s32 D_00274B50[3] = { 0x453B8000, 0, 0x3E800000 };
f32 D_00274B5C = 0;
f32 D_00274B60[1] = { 0.1f };
f32 D_00274B64 = -0.033f;
f32 D_00274B68[3] = { 300.0f, 0.0f, 0.25f };
f32 D_00274B74 = 1.5f;
f32 D_00274B78 = 2.0f;
f32 D_00274B7C = 0.0333333351f;
f32 D_00274B80[3] = { 25.0f, 0.0f, 0.25f };

// Three words copied whole from .data to a place only 4-aligned: the first two as one
// unaligned doubleword.
struct __attribute__((packed)) UnalignedPair { u64 v; };
struct ThreeWords { UnalignedPair a; s32 b; };

void InitSwitchedCollider(void* self);
void ScaleTurningColliderRamp(void* self, f32 x);

void InitTurningCollider(TurningCollider* self)
{
    InitSwitchedCollider(self);
    self->f700 = 1.0f;
    self->f360 = D_00274B20;
    ScaleTurningColliderRamp(self, 1.0f);
    self->v6F0 = D_00274B30;
    *(ThreeWords*)self->f710 = *(ThreeWords*)D_00274B40;
    *(ThreeWords*)self->f704 = *(ThreeWords*)D_00274B50;
}

void StartPlacedObject(void* self);
void ResolveObjectLinks(void* self, s32 a1, void* table);
void SetTurningColliderLinkFlag(void* self, s32 a1);

void StartTurningCollider(TurningCollider* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 6, g_turningColliderLinks);
    SetTurningColliderLinkFlag(self, 1);
    if (self->f628 == 0) {
        self->f610 = self->f620;
    } else {
        self->f610 = self->f628;
    }
    if (self->f62C == 0) {
        self->f614 = self->f624;
    } else {
        self->f614 = self->f62C;
    }
    Mat02* dst = &self->m660;
    *dst = g_identityMatrix;
}

void SetTurningColliderLinkFlag(TurningCollider* self, s32 a1)
{
    PlacedObject* h = (PlacedObject*)self->f61C;
    if (h != 0) {
        Rec2195_224* s = h->f224;
        if (s != 0 && (s->fB0 & 0x20) != 0) {
            if (a1 != 0) s->f98 |= 2;
            else s->f98 &= ~2;
        }
    }
    PlacedObject* v = (PlacedObject*)self->f618;
    if (v != 0) {
        Rec2195_224* s = v->f224;
        if (s != 0 && (s->fB0 & 0x20) != 0) {
            if (a1 != 0) s->f98 |= 2;
            else ((PlacedObject*)self->f61C)->f224->f98 &= ~2;
        }
    }
}

INCLUDE_ASM(func_001C4618);

s32 CollectColliderSpansInTree(void* self, void* a1, void* a2, void* a3, s32 a4, void* a5);

void KeepNearestPartSpan(void* unused, void* a1, void* a2, Part07* self)
{
    ColliderSpan ents[2];
    s32 n;
    s32 idx;
    if (self->f50 == 0) return;
    n = CollectColliderSpansInTree(a1, a2, &self->v70, &self->v60, 2, ents);
    idx = 0;
    if (n > 0) {
        if (ents[0].time[0] == 0.0f) idx = 1;
    }
    if (!(idx < n)) return;
    if (ents[idx].time[0] < self->span.time[0]) {
        self->span = ents[idx];
    }
}

INCLUDE_ASM(func_001C4848);

void DrawCollider(void);

void DrawTurningCollider(void)
{
    DrawCollider();
}

INCLUDE_ASM(func_001C49E8);

extern f32 g_gameTime[];
extern s32 D_00605548;
f32 WrapModulo(f32 x, f32 y);
s32 RandomIntInRange(s32 a, s32 b);
void StartSoundEffect(s32 a0, void* a1, s32 a2, u8* a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void PlaySoundWithWanderingPitch();

void PlayPhaseCrossingSound(Player* self, f32* p, f32 f) {
    f32 old = self->f6C4;
    f32 ang;
    self->f6C4 = f;
    if (g_gameTime[0] - self->f6C8 < D_00274B60[0]) return;
    if (WrapModulo(f - p[0], 1.0f) < 0.5f && 0.5f < WrapModulo(old - p[0], 1.0f)) {
        ang = p[2];
    } else if (WrapModulo(self->f6C4 - p[1], 1.0f) < 0.5f && 0.5f < WrapModulo(old - p[1], 1.0f)) {
        ang = p[3];
    } else {
        return;
    }
    s32 idx = RandomIntInRange(0x47, 0x4A);
    if (idx == D_00605548) {
        s32 x = idx - 0x46;
        idx = x % 4 + 0x47;
    }
    D_00605548 = idx;
    StartSoundEffect(idx, 0, 0, (u8*)&self->v140, 0, 0, 1000.0f, 200.0f, ang, 0.0f, 0.0f);
    PlaySoundWithWanderingPitch();
}

INCLUDE_ASM(func_001C4C20);

INCLUDE_ASM(func_001C4D60);


void UpdateSwitchedCollider(void* self);
void func_001C4C20(void* self);

void UpdateTurningCollider(TurningCollider* self)
{
    UpdateSwitchedCollider(self);
    func_001C4C20(self);
}

s32 GetTurningColliderContactMode(void) { return 3; }

void ComputeColliderImpulseResponse(void* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void ComputeTurningColliderImpulseResponse(TurningCollider* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5)
{
    s32 old = self->mode470;
    self->mode470 = self->desc06()->m55(self);
    ComputeColliderImpulseResponse(self, a1, a2, a3, a4, a5);
    self->mode470 = old;
}

void SetColliderRotation(void* self, void* src);
f32 ArctangentOfRatio(f32 a, f32 b);

void SetTurningColliderRotation(TurningCollider* self, Mat02* rot)
{
    SetColliderRotation(self, rot);
    f32 r = ArctangentOfRatio(rot->r[0].y, rot->r[0].x);
    self->f638 = r;
    self->f630 = r;
    self->desc06()->m54(self);
}

INCLUDE_ASM(func_001C4FF8);

void StepCollider(void* self);
void ApplyTurningColliderDrive(void* self);

void StepTurningCollider(TurningCollider* self)
{
    StepCollider(self);
    ApplyTurningColliderDrive(self);
}

INCLUDE_ASM(func_001C5148);

s32 IsTurningColliderGroundContact(TurningCollider* self, Contact03* a, s32 idx)
{
    if (self->f6DC == 0) {
        return 0;
    }
    if (a->v80.z * D_00274AD0[idx] < 0.7f) {
        return 0;
    }
    s32 kind = a->kind;
    switch (kind) {
    case 1: {
        s32 r = 0;
        if (idx == 0 && a->fA0 == self->f6D4) {
            r = 1;
        }
        return r;
    }
    case 4: {
        s32 r = 0;
        if (idx == 1 && a->fA4 == self->f6D4) {
            r = 1;
        }
        return r;
    }
    case 10: {
        s32 r = 0;
        if (idx == 0) {
            r = a->fA0 == self->f6D4;
        }
        return r;
    }
    }
    return 0;
}

// Slot 86 (func_001C5248: does a contact hold the body up), called with the caller's own
// arguments left in place.
typedef s32 (*ContactTestFn)(void* self);
void ComputeTurningColliderContactValue(TurningCollider* self, Contact03* out)
{
    if (((ContactTestFn*)self->desc)[0x168 / 4](self)) {
        f32 d = D_00274B74;
        out->f98 = 0;
        out->f94 = d;
    } else {
        out->f94 = 0.0f;
        out->f98 = 0;
    }
}

void ClampColliderContactLimit(void);

void ClampTurningColliderContactLimit(void)
{
    ClampColliderContactLimit();
}

void ClampColliderContactLimit(void)
{
}

void BuildAxisAngleMatrix(const Vec02* t, f32 x, void* p);

void BuildTurningColliderHeadingMatrix(TurningCollider* self)
{
    BuildAxisAngleMatrix(&g_unitZVector, self->f638, (u8*)self + 0x660);
}

void ResolveTurningColliderGroundContact(TurningCollider* self, void* b, s32 c);

void ResolveTurningColliderContact(TurningCollider* self, void* b, s32 c)
{
    if (((ContactTestFn*)self->desc)[90](self)) {
        ResolveTurningColliderGroundContact(self, b, c);
    }
}

extern f32 g_unitRange[];

void RecomputeColliderFrame(TurningCollider* self);
f32 ArctangentOfRatio(f32 a, f32 b);
f32 WrapAngle(f32 a);

void RecomputeTurningColliderFrame(TurningCollider* self)
{
    RecomputeColliderFrame(self);
    f32 t = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    f32 ay = __builtin_fabsf(WrapAngle(self->f638 - t));
    f32* lim = g_unitRange;
    Vec02* p = &self->v6F0;
    f32 v = self->v6F0.x + ay * (p->y + ay * p->z);
    f32 lo = lim[0];
    f32 hi = lim[1];
    if (v < lo) {
        v = lo;
    } else if (hi < v) {
        v = hi;
    }
    self->f63C = v;
}

INCLUDE_ASM(func_001C54D0);

INCLUDE_ASM(func_001C57C8);

void AddTurningColliderProbeContact(void* a, s32 b, s32 c, s32 d);

void CollideTurningColliderWithObject(TurningCollider* a0, s32 a1, s32 unused2, s32 unused3, s32 a4, s32 a5)
{
    AddTurningColliderProbeContact(a0, a1, a4, a5);
}

INCLUDE_ASM(func_001C5C10);

f32 ArctangentOfRatio(f32 a, f32 b);
f32 ApproachAngleWithRamp(void* p, void* out, f32 a, f32 b, f32 c);

void TurnColliderTowardHeading(TurningCollider* self)
{
    Vec02 q = self->v160;
    f32 r = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    ApproachAngleWithRamp((u8*)self + 0x6E0, &q.z, r, self->f638, 0.0f);
    self->desc02()->m21(self, &q);
}

INCLUDE_ASM(func_001C5DB8);


void ScaleTurningColliderRamp(TurningCollider* self, f32 s)
{
    *(ThreeWords*)&self->f6E0 = *(ThreeWords*)D_00274B80;
    self->f6E0 *= s;
    self->f6E4 *= s;
    self->f6E8 *= 1.0f / Fpu::Sqrt(s);
}

INCLUDE_ASM(func_001C5EA8);
