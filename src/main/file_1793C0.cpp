// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "switched_collider.h"
#include "gauge_mode_object.h"
#include "countdown_collider.h"
#include "globals.h"
#include "object_link.h"
#include "message_body.h"
#include "object_event.h"
#include "shapes.h"
#include "screen_element.h"
#include "placed_object.h"
#include "asm_func.h"

// Classes 0x1B, 0x4A and 0x4B (the countdown). Its .rodata is func_0017ABE8's FLT_MAX literal
// at 0x24AFF4; its .data runs from 0x263AC0 to 0x263E34, in retail's order.

// The float func_0017AF38 reads as zero; the word after it is padding before the link table.
f32 D_00263AC0 = 0.0f;

ObjectLink g_modeColliderLinks[26] = {
    { 0, 0x453, 0x688 },
    { 0, 0x454, 0x694 },
    { 0, 0x455, 0x6A0 },
    { 0, 0x456, 0x6AC },
    { 0, 0x457, 0x6B8 },
    { 0, 0x458, 0x6C4 },
    { 0, 0x459, 0x6C8 },
    { 0, 0x45A, 0x6CC },
    { 0, 0x44E, 0x654 },
    { 4, 0x50, 0x67C },
    { 4, 0x45, 0x680 },
    { 4, 0x44C, 0x6E4 },
    { 4, 0x44D, 0x6E8 },
    { 0, 0x162, 0x58C },
    { 0, 0x163, 0x590 },
    { 4, 0x160, 0x584 },
    { 32, 0x18D, 0x604 },
    { 4, 0x45B, 0x674 },
    { 4, 0x45C, 0x678 },
    { 4, 0x465, 0x66C },
    { 4, 0x466, 0x670 },
    { 4, 0x45D, 0x650 },
    { 5, 0x461, 0x65C },
    { 5, 0x45F, 0x660 },
    { 5, 0x45E, 0x664 },
    { 5, 0x460, 0x668 }
};
f32 D_00263C00[4] = { 0.0f, -600.0f, 0.0f, 0.0f };
f32 D_00263C10[4] = { 0.0f, -300.0f, 0.0f, 0.0f };

f32 D_00263C20[4] = { 0.0f, 20.0f, 0.0f, 0.0f };
f32 D_00263C30[4] = { 0.0f, 10.0f, 0.0f, 0.0f };
f32 D_00263C40[3] = { 25.0f, 0.0f, 0.5f };
f32 D_00263C4C = 0.699999988f;
f32 D_00263C50[2] = { 0.150000006f, 0.0f };
f32 D_00263C58[4] = { 1.5f, 0.0f, 0.75f, 0.0f };
f32 D_00263C68[4] = { 20.0f, 0.0f, 0.100000001f, 0.0f };
f32 D_00263C78[2] = { -1.0f, 1.0f };
f32 D_00263C80[4] = { 10.0f, 0.0f, 0.100000001f, 0.0f };
f32 D_00263C90[4] = { -1.0f, 1.0f, 0.0f, 0.0f };
f32 D_00263CA0[4] = { 0.0f, -750.0f, 0.0f, 0.0f };
f32 D_00263CB0[4] = { 0.0f, -450.0f, 0.0f, 0.0f };
f32 D_00263CC0[4] = { 0.0f, 2.0f, -1.0f, 0.0f };
f32 D_00263CD0[4] = { 0.0f, 0.5f, 0.0f, 0.0f };
f32 D_00263CE0[4] = { 0.0f, 0.300000012f, 0.0f, 0.0f };
f32 D_00263CF0[4] = { 0.0f, 0.00100000005f, 0.0f, 0.0f };
f32 D_00263D00[2] = { 0.0f, 0.300000012f };
f32 D_00263D08[4] = { 30.0f, 0.0f, 0.5f, 0.0f };
f32 D_00263D18[6] = { 30.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f };

extern f32 g_gameClock[];
f32 D_00263D30[4] = { 1.0f, 0.0f, -0.75f, 0.0f };
f32 D_00263D40[6] = { 0.7f, 0.3f, 0.0f, 0.0f, 7e+02f, 6.5e+02f };

ObjectLink g_gaugeHolderLinks[13] = {
    { 0, 0x468, 0x584 },
    { 0, 0x469, 0x56C },
    { 0, 0x46A, 0x560 },
    { 0, 0x46B, 0x578 },
    { 0, 0x46C, 0x594 },
    { 0, 0x46D, 0x5A0 },
    { 0, 0x46E, 0x5AC },
    { 0, 0x46F, 0x5B8 },
    { 2, 0x470, 0x5C8 },
    { 2, 0x471, 0x5D4 },
    { 2, 0x472, 0x5E0 },
    { 2, 0x473, 0x5EC },
    { 2, 0x474, 0x5F8 }
};
f32 D_00263DF4 = 0.5f;
f32 D_00263DF8 = 1250.0f;
f32 D_00263DFC = 750.0f;
f32 D_00263E00 = 750.0f;

extern s32 D_00263E2C;
extern s32 g_timeoutFired;
f32 g_timeoutLimit = 3.0f;

ObjectLink g_countdownTable[3] = {
    { 0, 0x478, 0x55C },
    { 0, 0x479, 0x560 },
    { 0, 0x47A, 0x564 }
};
// size: s32, word load/store only
s32 D_00263E2C = 0;

extern s32 D_00263E2C;
s32 g_timeoutFired = 0;

void InitSwitchedCollider(void* self);

void InitModeCollider(ModeCollider* self)
{
    InitSwitchedCollider(self);
    self->f610 = -1;
}

struct Sub_1793F0 { u8 pad0[0xE0]; void* fE0; };

void StartPlacedObject(void* self);
void ResolveObjectLinks(void* self, s32 a1, void* a2);
void SetFollowObjects(void* a, s32 b, s32 c);
void* CreateStateWalker(void* a, void* b, s32 c, s32 d);
void BuildCombinedBlendAnimation(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void** a7);
void SetBlendItemWeights(void* obj, s32 a1, s32 a2, void* a3);
void SetModeColliderMode(void* self, s32 a1);
s32 FindAnimRecord(s32 key);

void StartModeCollider(ModeCollider* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 0x1A, g_modeColliderLinks);
    SetFollowObjects(self->f6E8, self->f680, self->f680);
    ((Sub_1793F0*)self->f650)->fE0 = self->f660;
    self->f658 = CreateStateWalker(self->f654, self, -1, 0);
    BuildCombinedBlendAnimation(self, 0xC, 5, &self->f684, 0, 0, 0, &self->f6C0);
    self->f684 = 1.0f;
    SetBlendItemWeights(self->f6C0, 0xC, 5, &self->f684);
    SetModeColliderMode(self, 2);
    T217D_BF0* base = &D_00270650;
    ((T217D_Float*)&base->f288)->v = 0.0f;
    base->icon = FindAnimRecord(0x36A);
}

ASM_FUNC(func_001794E0);

// NEAR: last call (func_001B9D10) loads a2 before $f12 is moved; retail moves $f12 first. Otherwise every instruction matches.

extern f32 D_00263C20[];
extern f32 D_00263C30[];
extern f32 D_00263C40[];

void StepCollider(ModeCollider* self, f32 t);
void ComputeModeColliderAnchors(ModeCollider* self, Vec02* a, Vec02* b);
void func_00127E60(void* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);
void SteerColliderTowardPosition(ModeCollider* self, void* buf, f32 f, void* d1, void* d2, void* d3);
void TurnColliderTowardRotation(ModeCollider* self, f32 scale, void* out, void* data);

void StepModeCollider(ModeCollider* self, f32 f)
{
    Vec02 a;
    Vec02 b;
    s32 mode = self->f610;
    if (mode < 2) {
        goto single;
    }
    if (mode < 4) {
        goto path2;
    }
    if (mode == 4) {
        goto path3;
    }
single:
    StepCollider(self, f);
    return;
path2:
    ComputeModeColliderAnchors(self, &a, &b);
    b = D_00248D30;
    func_00127E60(self->f668, 0, &a, 0, &b, 0);
    goto tail;
path3:
    a = *(Vec02*)&self->pos;
    b = D_00248D30;
tail:
    SteerColliderTowardPosition(self, &a, f, D_00263C20, &b, D_00263C30);
    TurnColliderTowardRotation(self, f, (u8*)self + 0x620, D_00263C40);
}

void MoveCollider(void* self, void* b);

void MoveModeCollider(ModeCollider* self)
{
    MoveCollider(self, 0);
    void (*fn)(BaseObject*) = self->desc->m12;
    if (fn != 0) fn(self);
}

ASM_FUNC(func_001796D0);

ASM_FUNC(func_00179A68);

void FinishSwitchedCollider(void* self);
void SetModeColliderMode(void* self, s32 a1);

void FinishModeCollider(ModeCollider* self)
{
    FinishSwitchedCollider(self);
    SetModeColliderMode(self, 2);
}

ASM_FUNC(func_0017A700);
extern f32 g_unitRange[];
extern Rgba4 D_002623E0;

f32 Cosine(f32 x);
void SetObjectTreeRecordValue(ModeCollider* o, u32 value);
void func_00125C90(ModeCollider* o, void* s, void* out);

void ApplyModeColliderTint(ModeCollider* self, void* s, void* out)
{
    Rgba4 res;
    f32 t;
    f32 u;
    f32 a;
    f32 b;
    f32 k;
    f32 c1;
    f32 lo;
    f32 hi;
    u8 col[4];

    if ((self->flags & 0x100000000ULL) != 0) return;
    *(u32*)col = 0x800000A0;
    if (self->f6D0 != 0) {
        if (self->f610 != 3) {
            t = (g_gameClock[1] - self->f6D8) * 0.5f;
        } else {
            t = 0.0f;
        }
        u = Cosine((g_gameClock[1] - self->f6D4) * 10.0f);
        a = D_00263D30[0] + t * (D_00263D30[1] + t * D_00263D30[2]);
        hi = g_unitRange[1];
        if (a < g_unitRange[0]) {
            c1 = g_unitRange[0];
        } else if (hi < a) {
            c1 = hi;
        } else {
            c1 = a;
        }
        b = D_00263D40[0] + u * (D_00263D40[1] + u * D_00263D40[2]);
        lo = g_unitRange[0];
        hi = g_unitRange[1];
        if (b < lo) {
            b = lo;
        } else if (hi < b) {
            b = hi;
        }
        k = c1 * b;
        res.r = (s32)((1.0f - k) * D_002623E0.r + k * col[0]);
        res.g = (s32)((1.0f - k) * D_002623E0.g + k * col[1]);
        res.b = (s32)((1.0f - k) * D_002623E0.b + k * col[2]);
        res.a = D_002623E0.a;
    } else {
        res = D_002623E0;
    }
    SetObjectTreeRecordValue(self, *(u32*)&res);
    func_00125C90(self, s, out);
}

// Matches retail's bytes (EXACT us and eu): the call result is tested directly with a goto to the zero return.

s32 IsPadSelectFlagHeld(World* world);
s32 IsModeColliderRequestBlocked(ModeCollider* self, s32 a1)
{
    if (a1 == 5) goto one;
    if (self->f610 == 3) goto one;
    if (self->f610 == 0) goto one;
    if (self->f610 == 4) goto one;
    if (self->f6D0 != 0) goto one;
    if (IsPadSelectFlagHeld(self->world) == 0) goto zero;
one:
    return 1;
zero:
    return 0;
}

// NEAR: the float store of f6D4 is scheduled before the li/sw of f6D0; retail stores f6D0 first

// What func_0017AA40 tells its listeners (kind 0x17): itself and the second word of its argument.
struct SenderValueMessage {
    void* self;
    s32 v;
};

s32 HasSpareCount(void);
void ComputeModeColliderAnchors(void* self, void* a, void* b);
void func_00127E60(void* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);
void SetModeColliderMode(void* self, s32 a1);

extern f32 g_gameTime;

s32 AcceptModeColliderRequest(ModeCollider* self, s32* arg)
{
    u8 bufA[16];
    u8 bufB[16];

    if (self->desc05()->m4B(self, *arg) != 0) {
        return 0;
    }
    if (HasSpareCount() != 0) {
        self->f6D0 = 1;
        self->f6D4 = *(f32*)&g_gameTime;
    }
    if (self->f6D0 != 0) {
        self->f704 = 0;
        self->f708 = 3.0f;
        ComputeModeColliderAnchors(self, bufA, bufB);
        func_00127E60(self->f668, 0, bufA, 0, bufB, 0);
        self->desc02()->m20(self, (Vec02*)bufB);
    }
    if (HasSpareCount() != 0) {
        SetModeColliderMode(self, 3);
    } else {
        SetModeColliderMode(self, 4);
    }
    {
        SenderValueMessage* m = (SenderValueMessage*)bufA;
        m->self = self;
        m->v = arg[1];
        self->desc->m0E(self, 0x17, bufA);
    }
    return 1;
}

void HandleSwitchedColliderNotification(void* self, s32 kind, MessageBody* rec);

void HandleModeColliderNotification(ModeCollider* self, s32 kind, MessageBody* rec)
{
    if (kind == 0x13 && rec->sourceId == self->f618) {
        switch (rec->code) {
        case 0x15E:
            self->f6E0 = 1;
            break;
        case 0x15F:
            self->f6E0 = 0;
            break;
        case 0x467:
            self->f70C = 1;
            break;
        }
    }
    HandleSwitchedColliderNotification(self, kind, rec);
}

s32 HasModeColliderAcceptedRequest(ModeCollider* self)
{
    return self->f6D0 != 0;
}

INCLUDE_RODATA(D_0024AFF4);
ASM_FUNC(func_0017ABE8);

void ComputeModeColliderAnchors(void* self, void* a, void* b);
void func_00127E60(void* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);

void PlaceModeColliderAtAnchor(ModeCollider* self)
{
    u8 bufA[16];
    u8 bufB[16];
    ComputeModeColliderAnchors(self, bufA, bufB);
    func_00127E60(self->f668, 0, bufA, 0, bufB, 0);
    self->desc02()->m1D(self, (Vec02*)bufA);
    self->desc02()->m20(self, (Vec02*)bufB);
}

void InitCollider(void* self);

void InitGaugeModeObject(GaugeModeObject* self)
{
    InitCollider(self);
    self->mode = -1;
}

void StartPlacedObject(void* self);
void ResolveObjectLinks(void* self, s32 a1, void* a2);
void BuildCombinedBlendAnimation(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void** a7);
void SetBlendItemWeights(void* obj, s32 a1, s32 a2, void* a3);
void SetGaugeModeObjectMode(GaugeModeObject* self, s32 a1);
s32 PlayGaugeModeObjectLoop(GaugeModeObject* self, s32 a1);

void StartGaugeModeObject(GaugeModeObject* self)
{
    StartPlacedObject(self);
    f32 one = 1.0f;
    ResolveObjectLinks(self, 13, g_gaugeHolderLinks);

    BuildCombinedBlendAnimation(self, 12, 4, self->grpA, 0, 0, 0, &self->mode0Handle);
    self->fA = one;
    SetBlendItemWeights(self->mode0Handle, 12, 4, self->grpA);

    BuildCombinedBlendAnimation(self, 12, 4, &self->fB, 0, 0, 0, &self->mode1Handle);
    self->fB = one;
    SetBlendItemWeights(self->mode1Handle, 12, 4, &self->fB);

    BuildCombinedBlendAnimation(self, 12, 5, &self->fC, 0, 0, 0, &self->loopHandle);
    self->fC = one;
    SetBlendItemWeights(self->loopHandle, 12, 5, &self->fC);

    SetGaugeModeObjectMode(self, 0);
    PlayGaugeModeObjectLoop(self, 1);
}

ASM_FUNC(func_0017AF38);

extern s32 D_00270458;
extern s32 D_00270B54;
extern s32 D_002717CC;
s32 AreMenusAndFadeClear(void* self);

void ShowGaugeModeObjectBar(GaugeModeObject* self)
{
    s32 busy = 0;
    s32 mode = self->mode;
    if (mode < 2) {
        if (mode >= 0) {
            if (AreMenusAndFadeClear(self) != 0) {
                if (D_00270458 != 3 || (D_00270B54 == 0 && D_002717CC == 0)) busy = 1;
            }
        }
    }
    if (busy) g_gaugeBarElement.vt->m14(&g_gaugeBarElement);
    else g_gaugeBarElement.vt->m15(&g_gaugeBarElement);
}

void DecrementGaugeCount(void* p);
void PlayGaugeModeObjectTarget(GaugeModeObject* self);
void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);

s32 HandleGaugeModeObjectEvent(GaugeModeObject* self, ObjectEvent* msg)
{
    if (msg->extraFlags & 0x10) {
        if (msg->id == self->f608) {
            DecrementGaugeCount(&g_gaugeBarElement);
            PlayGaugeModeObjectTarget(self);
            TriggerScriptEvent(self, 2, 0, 0);
        }
    }
    return 1;
}

extern f32 g_gameTime;

void SetWorldActiveFollower(void* a, void* b);
s32 ReplaceAnimationPlayer(void* a, void* b, s32 c, void* d, f32 e, f32 f);

void SetGaugeModeObjectMode(GaugeModeObject* self, s32 mode)
{
    void* x;
    if (mode == self->mode) {
        goto done;
    }
    x = 0;
    if (mode != 0) {
        if (mode == 1) {
            x = self->mode1Handle;
        }
    } else {
        x = self->mode0Handle;
    }
    if (mode >= 0) {
        if (mode < 2) {
            T217D_2E0* sys = &g_gaugeBarElement;
            sys->fillTarget = 1.0f;
            sys->f26C = sys->f260;
            sys->f270 = sys->f264;
            sys->fill = 0.0f;
            SetWorldActiveFollower(self->world, self);
        } else if (mode < 4) {
            T217D_2E0* sys = &g_gaugeBarElement;
            sys->vt->m15(sys);
            SetWorldActiveFollower(self->world, 0);
        }
    }
    (void)ReplaceAnimationPlayer(x, self, 1, self->modePlayer, 0.0f, 1.0f);
    *(s32*)((u8*)self + 0x550) = mode;
    self->modeTime = g_gameTime;
done:
    return;
}

s32 ReplaceAnimationPlayer(void* a, void* b, s32 c, void* d, f32 e, f32 f);

s32 PlayGaugeModeObjectLoop(GaugeModeObject* self, s32 flag)
{
    void* p = 0;
    if (flag != 0) {
        p = self->loopHandle;
    }
    return ReplaceAnimationPlayer(p, self, 1, self->loopPlayer, 0.0f, 1.0f);
}

s32 FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);

void SetGaugeModeObjectTarget(GaugeModeObject* self, s32 index)
{
    if (index == -1) {
        self->target = 0;
    } else {
        self->target = (void*)FindFirstObjectById(self->world, 0x101, index, self);
    }
}

void PlayGaugeModeObjectTarget(GaugeModeObject* self)
{
    ReplaceAnimationPlayer(self->target, self, 1, self->targetPlayer, 0.0f, 1.0f);
}

void InitCountdown(CountdownCollider* self)
{
    InitCollider(self);
    self->countdown = 0x10;
    D_00263E2C = -1;
    g_timeoutFired = 0;
}

void StartPlacedObject(void* self);
void ResolveObjectLinks(void* self, int n, void* table);

void StartCountdown(CountdownCollider* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 3, g_countdownTable);
}
extern f32 g_gameTime;

void UpdateCollider(void* self);
void StopAnimationPlayer(void* p);
void SetCountdownState(void* self, s32 state);
void FadeOutAndQueueMovie(s32 n);

void UpdateCountdown(CountdownCollider* self)
{
    CountdownRecord* p;

    UpdateCollider(self);
    p = self->record;
    if (p != 0) {
        if (p->remaining == 0.0f) {
            StopAnimationPlayer(p);
            self->record = 0;
        }
    }
    if (D_00263E2C != -1) {
        SetCountdownState(self, D_00263E2C);
    }
    if (self->mode == 2) {
        if (g_timeoutLimit < g_gameTime - self->startTime) {
            if (g_timeoutFired == 0) {
                g_timeoutFired = 1;
                FadeOutAndQueueMovie(2);
            }
        }
    }
}

extern s32 D_00270458;
extern s32 D_00270B54;
extern s32 D_002717CC;
s32 AreMenusAndFadeClear(void* self);

void UpdateCountdownVisibility(CountdownCollider* self)
{
    s32 busy = 0;
    if (self->mode == 1 && AreMenusAndFadeClear(self) != 0) {
        if (D_00270458 != 3 || (D_00270B54 == 0 && D_002717CC == 0)) busy = 1;
    }
    if (busy) g_gaugeBarElement.vt->m14(&g_gaugeBarElement);
    else g_gaugeBarElement.vt->m15(&g_gaugeBarElement);
}

// NEAR: 0x558 clamp uses movz with the operand order ours does not reproduce; msg->fC mask load goes to the other register

extern s32 D_00263E2C;

void DecrementGaugeCount(void* p);
void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);
void ReplaceAnimationPlayer(void* a, CountdownCollider* b, s32 c, void* d, f32 e, f32 f);
s32 HandleObjectEvent(void* self, ObjectEvent* msg);

s32 HandleCountdownObjectEvent(CountdownCollider* self, ObjectEvent* msg)
{
    void* p;
    if (msg->eventFlags & 0x20) {
        s32 n = self->countdown - 1;
        s32 pos = (0 < n);
        self->countdown = pos ? n : 0;
        DecrementGaugeCount(&g_gaugeBarElement);
        if (self->countdown == 0) {
            D_00263E2C = 2;
            p = 0;
        } else {
            s32 flags = msg->extraFlags;
            if (flags & 2) {
                if (g_player == 0) {
                    p = self->f55C;
                } else {
                    s32 t = g_player->f223C;
                    if (t == 4 || t == 6) {
                        p = self->f55C;
                    } else {
                        p = self->f560;
                    }
                }
            } else if (flags & 4) {
                p = self->f564;
            } else {
                p = self->f55C;
            }
        }
        ReplaceAnimationPlayer(p, self, 1, &self->record, 0.0f, 1.0f);
        msg->eventFlags &= ~0x20;
        TriggerScriptEvent(self, 2, 0, 0);
    }
    return HandleObjectEvent(self, msg);
}

INCLUDE_ASM(func_0017B8C0);
