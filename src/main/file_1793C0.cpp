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

ObjectLink D_00263AC8[26] = {
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

extern f32 D_00261858[];
f32 D_00263D30[4] = { 1.0f, 0.0f, -0.75f, 0.0f };
f32 D_00263D40[6] = { 0.7f, 0.3f, 0.0f, 0.0f, 7e+02f, 6.5e+02f };

ObjectLink D_00263D58[13] = {
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
extern s32 D_00263E30;
f32 D_00263E04 = 3.0f;

ObjectLink D_00263E08[3] = {
    { 0, 0x478, 0x55C },
    { 0, 0x479, 0x560 },
    { 0, 0x47A, 0x564 }
};
// size: s32, word load/store only
s32 D_00263E2C = 0;

extern s32 D_00263E2C;
s32 D_00263E30 = 0;

void func_001921A8(void* self);

void func_001793C0(C1B* self)
{
    InitSwitchedCollider(self);
    self->f610 = -1;
}

struct Sub_1793F0 { u8 pad0[0xE0]; void* fE0; };
struct Packed_1793F0 { f32 v; } __attribute__((packed));

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a1, void* a2);
void func_0012B5B8(void* a, s32 b, s32 c);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
void func_00139038(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void** a7);
void func_001399F8(void* obj, s32 a1, s32 a2, void* a3);
void func_0017ABE8(void* self, s32 a1);
s32 func_001B4688(s32 key);

void func_001793F0(C1B* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 0x1A, g_modeColliderLinks);
    SetFollowObjects(self->f6E8, self->f680, self->f680);
    ((Sub_1793F0*)self->f650)->fE0 = self->f660;
    self->f658 = CreateStateWalker(self->f654, self, -1, 0);
    func_00139038(self, 0xC, 5, &self->f684, 0, 0, 0, &self->f6C0);
    self->f684 = 1.0f;
    func_001399F8(self->f6C0, 0xC, 5, &self->f684);
    SetModeColliderMode(self, 2);
    u8* base = (u8*)&D_00270650;
    ((Packed_1793F0*)(base + 0x288))->v = 0.0f;
    *(s32*)(base + 0x284) = FindAnimRecord(0x36A);
}

ASM_FUNC(func_001794E0);

// NEAR: last call (func_001B9D10) loads a2 before $f12 is moved; retail moves $f12 first. Otherwise every instruction matches.

struct Sub_179590;
extern f32 D_00263C20[];
extern f32 D_00263C30[];
extern f32 D_00263C40[];

void func_001B9338(C1B* self, f32 t);
void func_001794E0(C1B* self, Vec02* a, Vec02* b);
void func_00127E60(Sub_179590* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);
void func_001B9058(C1B* self, void* buf, f32 f, void* d1, void* d2, void* d3);
void func_001B9D10(C1B* self, f32 scale, void* out, void* data);

void func_00179590(C1B* self, f32 f)
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
    func_00127E60(((Sub_179590*)self->f668), 0, &a, 0, &b, 0);
    goto tail;
path3:
    a = *(Vec02*)&self->pos;
    b = D_00248D30;
tail:
    func_001B9058(self, &a, f, D_00263C20, &b, D_00263C30);
    func_001B9D10(self, f, (u8*)self + 0x620, D_00263C40);
}

typedef void (*VFn_179690)(void*);

void func_001BC088(void* self, void* b);

void func_00179690(C1B* self)
{
    func_001BC088(self, 0);
    VFn_179690 fn = (VFn_179690)((void**)((void**)self->desc))[0x58 / 4];
    if (fn != 0) fn(self);
}

ASM_FUNC(func_001796D0);

ASM_FUNC(func_00179A68);

void func_00192C58(void* self);
void func_0017ABE8(void* self, s32 a1);

void func_0017A6D0(C1B* self)
{
    func_00192C58(self);
    SetModeColliderMode(self, 2);
}

ASM_FUNC(func_0017A700);
extern f32 D_00275C60[];
extern Rgba4 D_002623E0;

f32 func_00205210(f32 x);
void func_00126A48(C1B* o, u32 value);
void func_00125C90(C1B* o, void* s, void* out);

void func_0017A788(C1B* self, void* s, void* out)
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

struct Vt_17B9D0
{
    u8 pad0[0x28];
    void (*f28)(void* self, Vec02* a, s32 b, Vec02* c, Vec02* d, s32 e, s32 f);
};

struct Node_17B9D0
{
    u8 pad0[0x18];
    void* f18;
    u8 pad1c[0x18];
    struct { Vt_17B9D0* vt; }* f34;
    u8 pad38[0x108];
    Vec02 f140;
};

struct Self_17B9D0
{
    u8 pad0[0x3C];
    u8* f3C;
};

// Matches retail's bytes (EXACT us and eu): the call result is tested directly with a goto to the zero return.

struct Ptr_17A9E0;
s32 func_001DDA80(Ptr_17A9E0* p);
s32 func_0017A9E0(C1B* self, s32 a1)
{
    if (a1 == 5) goto one;
    if (self->f610 == 3) goto one;
    if (self->f610 == 0) goto one;
    if (self->f610 == 4) goto one;
    if (self->f6D0 != 0) goto one;
    if (IsPadSelectFlagHeld((Ptr_17A9E0*)self->world) == 0) goto zero;
one:
    return 1;
zero:
    return 0;
}

// NEAR: the float store of f6D4 is scheduled before the li/sw of f6D0; retail stores f6D0 first

typedef s32 (*VFn_17AA40_A)(void* self, s32 v);
typedef void (*VFn_17AA40_B)(void* self, void* p);
typedef void (*VFn_17AA40_C)(void* self, s32 a, void* b);

struct Msg_17AA40 {
    void* self;
    s32 v;
};

s32 func_00160C58(void);
void func_001794E0(void* self, void* a, void* b);
void func_00127E60(void* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);
void func_0017ABE8(void* self, s32 a1);

extern f32 D_0026185C;

s32 func_0017AA40(C1B* self, s32* arg)
{
    u8 bufA[16];
    u8 bufB[16];

    if (((VFn_17AA40_A)((void**)self->desc)[79])(self, *arg) != 0) {
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
        ((VFn_17AA40_B)((void**)self->desc)[36])(self, bufB);
    }
    if (HasSpareCount() != 0) {
        SetModeColliderMode(self, 3);
    } else {
        SetModeColliderMode(self, 4);
    }
    {
        Msg_17AA40* m = (Msg_17AA40*)bufA;
        m->self = self;
        m->v = arg[1];
        ((VFn_17AA40_C)((void**)self->desc)[18])(self, 0x17, bufA);
    }
    return 1;
}

void func_00192230(void* self, s32 kind, MessageBody* rec);

void func_0017AB58(C1B* self, s32 kind, MessageBody* rec)
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

s32 func_0017ABD8(C1B* self)
{
    return self->f6D0 != 0;
}

INCLUDE_RODATA(D_0024AFF4);
ASM_FUNC(func_0017ABE8);

void func_001794E0(void* self, void* a, void* b);
void func_00127E60(void* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);

void func_0017AD50(C1B* self)
{
    u8 bufA[16];
    u8 bufB[16];
    ComputeModeColliderAnchors(self, bufA, bufB);
    func_00127E60(self->f668, 0, bufA, 0, bufB, 0);
    self->desc02()->m1D(self, (Vec02*)bufA);
    self->desc02()->m20(self, (Vec02*)bufB);
}

void func_001B7968(void* self);

void func_0017ADD0(GaugeModeObject* self)
{
    InitCollider(self);
    self->mode = -1;
}

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a1, void* a2);
void func_00139038(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void** a7);
void func_001399F8(void* obj, s32 a1, s32 a2, void* a3);
void func_0017B410(GaugeModeObject* self, s32 a1);
s32 func_0017B510(GaugeModeObject* self, s32 a1);

void func_0017AE00(GaugeModeObject* self)
{
    StartPlacedObject(self);
    f32 one = 1.0f;
    ResolveObjectLinks(self, 13, g_gaugeHolderLinks);

    func_00139038(self, 12, 4, self->grpA, 0, 0, 0, &self->mode0Handle);
    self->fA = one;
    func_001399F8(self->mode0Handle, 12, 4, self->grpA);

    func_00139038(self, 12, 4, &self->fB, 0, 0, 0, &self->mode1Handle);
    self->fB = one;
    func_001399F8(self->mode1Handle, 12, 4, &self->fB);

    func_00139038(self, 12, 5, &self->fC, 0, 0, 0, &self->loopHandle);
    self->fC = one;
    func_001399F8(self->loopHandle, 12, 5, &self->fC);

    SetGaugeModeObjectMode(self, 0);
    PlayGaugeModeObjectLoop(self, 1);
}

ASM_FUNC(func_0017AF38);

extern s32 D_00270458;
extern s32 D_00270B54;
extern s32 D_002717CC;
s32 func_001E9970(void* self);

void func_0017B308(GaugeModeObject* self)
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

struct Msg_17B3A8 {
    u8 pad0[4];
    s32 f4;
    u8 pad1[8];
    u32 f10;
};

void func_001AC060(void* p);
void func_0017B598(GaugeModeObject* self);
void func_001837E0(void* self, s32 a, s32 b, s32 c);

s32 func_0017B3A8(GaugeModeObject* self, Msg_17B3A8* msg)
{
    if (msg->f10 & 0x10) {
        if (msg->f4 == self->f608) {
            DecrementGaugeCount(&g_gaugeBarElement);
            PlayGaugeModeObjectTarget(self);
            TriggerScriptEvent(self, 2, 0, 0);
        }
    }
    return 1;
}

typedef void (*Fn_17B410)(void* self);

struct Sys_17B410 {
    Fn_17B410* vtbl;
    u8 pad0[0x260 - 4];
    s32 f260;
    s32 f264;
    u8 pad1[0x26C - 0x268];
    s32 f26C;
    s32 f270;
    s32 f274;
    f32 f278;
};

extern f32 D_0026185C;

void func_001DDC38(void* a, void* b);
s32 func_0012C918(void* a, void* b, s32 c, void* d, f32 e, f32 f);

void func_0017B410(GaugeModeObject* self, s32 mode)
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
            Sys_17B410* sys = (Sys_17B410*)&g_gaugeBarElement;
            sys->f278 = 1.0f;
            sys->f26C = sys->f260;
            sys->f270 = sys->f264;
            sys->f274 = 0;
            SetWorldActiveFollower(self->world, self);
        } else if (mode < 4) {
            Sys_17B410* sys = (Sys_17B410*)&g_gaugeBarElement;
            sys->vtbl[15](sys);
            SetWorldActiveFollower(self->world, 0);
        }
    }
    (void)ReplaceAnimationPlayer(x, self, 1, self->modePlayer, 0.0f, 1.0f);
    *(s32*)((u8*)self + 0x550) = mode;
    self->modeTime = g_gameTime;
done:
    return;
}

s32 func_0012C918(void* a, void* b, s32 c, void* d, f32 e, f32 f);

s32 func_0017B510(GaugeModeObject* self, s32 flag)
{
    void* p = 0;
    if (flag != 0) {
        p = self->loopHandle;
    }
    return ReplaceAnimationPlayer(p, self, 1, self->loopPlayer, 0.0f, 1.0f);
}

s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);

void func_0017B550(GaugeModeObject* self, s32 index)
{
    if (index == -1) {
        self->target = 0;
    } else {
        self->target = (void*)FindFirstObjectById(self->world, 0x101, index, self);
    }
}

typedef void (*VFn_17BC20)(void* self);

struct Comp_17BC20 {
    VFn_17BC20* vtbl;
    u8 pad0[0x2D0 - 4];
    s32 f2D0;
};

struct Obj_17BC20 {
    u8 pad0[0x3C];
    s32 f3C;
    u8 pad1[0x58 - 0x40];
    Comp_17BC20* f58;
    s32 f5C;
};

void func_0017B598(GaugeModeObject* self)
{
    ReplaceAnimationPlayer(self->target, self, 1, self->targetPlayer, 0.0f, 1.0f);
}

void func_0017B5D0(CountdownCollider* self)
{
    InitCollider(self);
    self->countdown = 0x10;
    D_00263E2C = -1;
    g_timeoutFired = 0;
}

void func_00124A48(void* self);
void func_00124DF8(void* self, int n, void* table);

void func_0017B610(CountdownCollider* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 3, g_countdownTable);
}
extern f32 D_0026185C;

void func_001B93F8(void* self);
void func_0012E760(void* p);
void func_0017B8C0(void* self, s32 state);
void func_00160578(s32 n);

void func_0017B648(CountdownCollider* self)
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
s32 func_001E9970(void* self);

void func_0017B710(CountdownCollider* self)
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

void func_001AC060(void* p);
void func_001837E0(void* self, s32 a, s32 b, s32 c);
void func_0012C918(void* a, CountdownCollider* b, s32 c, void* d, f32 e, f32 f);
s32 func_001BC320(void* self, ObjectEvent* msg);

s32 func_0017B7A8(CountdownCollider* self, ObjectEvent* msg)
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
