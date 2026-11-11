// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x1921A8 to 0x193210 (its .data from 0x269BC0, its .bss from 0x604700): the
// switched collider (class 0x05), the list of up to 16 of
// them and the active one, the typed caption box and step skipping it drives, and the static
// initialiser (func_001930B8, its _GLOBAL_$I$ func_001931F0 in retail's constructor list). Its
// .data provably starts at 0x269BC0: the global before it, g_targetVectors (D_00269BA8), is a
// list head of 0xC bytes like every other (include/globals.h), so D_00269BC0 (f32[3], aligned to
// 8) would follow it at 0x269BB8 in one file; retail has 8 more bytes of zeros and puts it on 16,
// the linker's padding before a new file's .data (aligned to 16 by Blk05's vectors). Its start in
// the code is a choice: any function start from 0x191FD8 to 0x192380 (file_18F988.cpp says why);
// the cut is at 0x1921A8, the first switched collider function. Its name is ours, after the class.
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "box_collider.h"
#include "object_link.h"
#include "path_curve_object.h"
#include "point_object.h"
#include "point_graph_object.h"
#include "world.h"
#include "step_sequence.h"
#include "screen_element.h"
#include "globals.h"
#include "pad_record.h"
#include "effect.h"
#include "vu0.h"
#include "object_message.h"
void InitCollider(void* self);
s32 IsObjectAttached();
s32 FindSwitchedColliderIndex(SwitchedCollider* value);
s32 FindSwitchedColliderIndex(void* value);
void ActivateSwitchedColliderIndex(s32 index);
void* MoveMemory(void* dst, void* src, s32 size);
void RegisterCollider(void* self);
void AddToSwitchedColliderList(void* self);
void UnregisterCollider(void* self);
void RemoveFromSwitchedColliderList(void* self);
void AddToSwitchedColliderList(SwitchedCollider* self);
void RemoveFromSwitchedColliderList(SwitchedCollider* self);
void* GetActiveSwitchedCollider();
// The two interaction flags GetSwitchedColliderInteractFlags gives.
struct InteractFlags {
    s32 a;
    s32 b;
};
s32 FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);
extern s32 g_buttonCodeFlags;
s32 IsPadSelectFlagHeld(void* p);
void* CreateEffect(s32 kind, s32 zero);
void AddEffectListener(void* node, void* owner);
f32 GetAnimationMarkerTime(void* obj, s32 id);
// Descriptor slot 72 as func_00192880 calls it, with the collider switched from or to.
typedef void (*ActivationHook)(void* self, s32 mode, void* other);
extern u8 g_elementStack[];
void PushStackElement(void* a, void* b);
extern s32 g_padRouting;
extern u8* D_0026F800;
// A record whose 16-bit flags sit at 0xAA.


s32 IsTopCameraController(void* p);
void SkipRemainingSteps(StepSequence* ctx, PadRecord* rec);
void SetStepSequenceState(void* p, s32 n);
void ClearPadPressedBits(PadRecord* rec, s32 n);
s32 IsObjectAttached(void* p);
void InitCollider(void* self);
void SetSwitchedColliderEnabled(SwitchedCollider* self, s32 value);
void CopyCollider(SwitchedCollider* self);
void SetSwitchedColliderEnabled(SwitchedCollider* self, s32 mode);
void PushCameraController(void* mgr, s32 a1, void* a2, SwitchedCollider* self, s32 a4);
void RemoveCameraControllers(void* mgr, s32 a1, s32 a2, s32 a3, SwitchedCollider* self, s32 a5);
void* GetActiveSwitchedCollider(void);
void ActivateSwitchedCollider(void* value);
s32 FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);
s32 IsPadSelectFlagHeld(void* p);
void CaptureColliderPose(void);
// func_001EA4B8 takes its float arguments first: the caller then sets $f14 before $a0.
f32 ApproachValueWithRamp(f32 a, f32 b, f32 c, Quad16* p, s32 zero);
extern s32 g_buttonCodeFlags;
extern u8* g_saveData;
// The parameters SpawnEffectsAt is given (word 0x28 set by the caller).
struct EffectSpawnParams { s32 f0, f4, f8, fC; f32 f10, f14; s32 f18, f1C; f32 f20, f24; s32 f28, f2C, f30, f34, f38, f3C; };
void RotateMatrixUpright(void* sub, s32 zero, void* out);
s32 CreateAnimationPlayerWithoutPresetTargets(void* a, void* b, s32 c, s32 d, f32 fa, f32 fb);
void SpawnEffectsAt(void* a, void* b, s32 c, void* d, void* e, s32 f, s32 g);
void* GetActiveSwitchedCollider(void);
// kind==0x10 loop test at the top (retail tests it with the first slot peeled) and
// keeps one more register (frame 64 bytes as retail, but a different loop shape).

void HandlePlacedObjectNotification(SwitchedCollider* self, s32 kind, void* msg);
void StopSoundRecord(void* self, s32 n);
s32 IsObjectAttached(void* p);
typedef void (*SlotFn)(void* self);
extern u8* g_saveData;
void UpdateCollider(SwitchedCollider* self);
void EmitSwitchedColliderTrailPoints(SwitchedCollider* self);
struct ClampInt {
    static s32 Of(s32 v, s32 lo, s32 hi)
    {
        if (v < lo) return lo;
        if (hi < v) return hi;
        return v;
    }
};

void StartSwitchedColliderEffect(SwitchedCollider* self, s32 mode, PlacedObject* other);
s32 ConstructSwitchedColliderDefaults(s32 a, s32 b);
f32 D_00269BC0[3] = { 1000.0f, 10.0f, 1.0f };
s32 g_activeSwitchedCollider = -1;
EffectSpawnParams D_00269BD0 = { 0x18, -1, 0, 0, 1.0f, 2.0f, 0, 0, 1.0f, 2.0f, 0, 0, 0, 1, 0, 0 };
// Built by the static initialiser (func_001930B8, still assembly below): each as a whole block,
// D_00604700 zero but its last vector, D_00269C10 with its own values. Until that C matches they
// are defined without their initialisers, which leaves them where retail has them: the static in
// .bss, the global with the uninitialised ones at the end of .data.
static Blk05 D_00604700;
Blk05 D_00269C10;
s32 g_switchedColliderCount;
void* g_switchedColliders[16];
extern f32 g_gameClock[];

void InitSwitchedCollider(SwitchedCollider* self)
{
    InitCollider(self);
    self->f598 = self;
    self->f580 = 1;
    SetSwitchedColliderEnabled(self, 1);
}

void CopySwitchedCollider(SwitchedCollider* self)
{
    CopyCollider(self);
    if (self->f550 != 0) {
        return;
    }
    self->f550 = 1;
    SetSwitchedColliderEnabled(self, 0);
}

void HandleSwitchedColliderNotification(SwitchedCollider* self, s32 kind, void* msg)
{
    HandlePlacedObjectNotification(self, kind, msg);
    switch (kind) {
    case 0xB:
        StopSoundRecord(self->f574, 0);
        break;
    case 0x10: {
        s32 i;
        for (i = 0; i < self->f5D0; i++) {
            if (self->f5AC[i] == msg) {
                self->f5AC[i] = 0;
                break;
            }
        }
        break;
    }
    }
}

void HandleSwitchedColliderActivation(SwitchedCollider* self, s32 mode)
{
    if (mode != 0) {
        self->v560 = self->v140;
        PushCameraController(g_camera, 1, &g_camera->ctl520, self, 0);
        return;
    }
    for (s32 i = 1; i < 7; i++) {
        RemoveCameraControllers(g_camera, 5, i, 0, self, 0);
    }
}

void CaptureSwitchedColliderPose(SwitchedCollider* self, u8* out, f32 a)
{
    CaptureColliderPose();
    if (self->f554 != 0) {
        *(Quad16*)(out + 0x10) = *(Quad16*)((u8*)self + 0x560);
        return;
    }
    Camera* base = g_camera;
    if (base->f224 == 0) {
        *(f32*)(out + 0x18) = ApproachValueWithRamp(self->v560.z, self->v140.z, a, (Quad16*)D_00269BC0, 0);
    }
    *(Quad16*)((u8*)self + 0x560) = *(Quad16*)(out + 0x10);
}

s32 IsSwitchedColliderCameraFree(void)
{
    return 1;
}

void ActivateSwitchedColliderUnlessActive(void* self)
{
    if (self != GetActiveSwitchedCollider()) ActivateSwitchedCollider(self);
}

s32 IsSwitchedColliderRequestBlocked(SwitchedCollider* self)
{
    if ((g_buttonCodeFlags & 1) || IsPadSelectFlagHeld(self->world)) return 1;
    return 0;
}

s32 AcceptSwitchedColliderRequest(SwitchedCollider* self)
{
    return 0;
}

s32 HasSwitchedColliderAcceptedRequest(void)
{
    return 0;
}

void StoreSwitchedColliderAccepted(SwitchedCollider* self, s32* out)
{
    *out = ((s32 (*)(SwitchedCollider*, s32*))self->desc05()->m4D)(self, out);
}

void StartSwitchedColliderEffect(SwitchedCollider* self, s32 mode, PlacedObject* other)
{
    switch (mode) {
    case 0:
        if (self->f5F0 == 0)
            return;
        {
            Effect* n = (Effect*)CreateEffect(0x1A, 0);
            self->f5AC[0] = n;
            self->f5D0 = 1;
            if (n != 0) {
                void (*init)(Effect* self, void* pos, f32 scale, s32 flags) = n->vt->m00;
                init(n, (u8*)other + 0x140, 1.0f, 0);
                AddEffectListener(n, self);
                f32 r = GetAnimationMarkerTime(self->f5F0, 0x13F);
                n->life = r;
                n->i20 = self->f59C;
                n->vC0 = other->world->gravity;
                n->p134 = other;
            }
        }
        self->desc05()->m4F(self, 1);
        break;
    case 1:
        self->desc05()->m4F(self, 2);
        break;
    }
}

ASM_FUNC(func_001925C0);

void* GetActiveSwitchedCollider()
{
    s32 i = g_activeSwitchedCollider;
    if (i < 0) return 0;
    return g_switchedColliders[i];
}

void* GetCurrentSwitchedCollider(void)
{
    void* r = GetActiveSwitchedCollider();
    if (r == 0) {
        Player* q = g_player;
        if (q != 0) {
            s32 t = q->f550;
            if (t != 0) r = q;
        }
    }
    if (r == 0 && g_switchedColliderCount != 0) {
        r = g_switchedColliders[0];
    }
    return r;
}

s32 FindSwitchedColliderIndex(s32 key)
{
    s32 i;
    for (i = 0; i < g_switchedColliderCount; i++) {
        if (key == (s32)g_switchedColliders[i]) {
            return i;
        }
    }
    return -1;
}

void AddToSwitchedColliderList(SwitchedCollider* self)
{
    if (self->f550 == 0) return;
    if (self->parent != 0) return;
    if (!IsObjectAttached()) return;
    if (FindSwitchedColliderIndex(self) >= 0) return;
    s32 n = g_switchedColliderCount;
    if ((u32)n < 16) {
        g_switchedColliders[n] = self;
        g_switchedColliderCount = n + 1;
    } else if (self->id == 5 && g_player == 0) {
        g_switchedColliders[0] = self;
    }
}

void RemoveFromSwitchedColliderList(void* value)
{
    s32 idx = FindSwitchedColliderIndex(value);
    if (idx < 0) return;
    if (idx == g_activeSwitchedCollider) ActivateSwitchedColliderIndex(-1);
    s32 n = g_switchedColliderCount;
    MoveMemory(&g_switchedColliders[idx], &g_switchedColliders[idx + 1], (n - idx) * 4 - 4);
    if (idx < g_activeSwitchedCollider) g_activeSwitchedCollider = g_activeSwitchedCollider - 1;
    g_switchedColliderCount = g_switchedColliderCount - 1;
}

void RegisterSwitchedCollider(SwitchedCollider* self)
{
    RegisterCollider(self);
    AddToSwitchedColliderList(self);
}

void UnregisterSwitchedCollider(SwitchedCollider* self)
{
    UnregisterCollider(self);
    RemoveFromSwitchedColliderList(self);
}

void ActivateSwitchedColliderIndex(s32 index)
{
    if (index == g_activeSwitchedCollider)
        return;
    if (g_activeSwitchedCollider >= 0) {
        u64 mask = (u64)(s64)-8193;
        mask = (mask << 16) | 0xFFFF;
        mask = (mask << 16) | 0xFFFF;
        SwitchedCollider** slot = (SwitchedCollider**)&g_switchedColliders[g_activeSwitchedCollider];
        (*slot)->flags538 &= mask;
        ActivationHook* vt = (ActivationHook*)(*slot)->desc;
        SwitchedCollider* next = index >= 0 ? (SwitchedCollider*)g_switchedColliders[index] : 0;
        vt[0x130 / 4]((*slot), 0, next);
    }
    s32 old = g_activeSwitchedCollider;
    g_activeSwitchedCollider = index;
    if (index >= 0) {
        SwitchedCollider** slot = (SwitchedCollider**)&g_switchedColliders[index];
        (*slot)->flags538 |= 1ULL << 45;
        ActivationHook* vt = (ActivationHook*)(*slot)->desc;
        SwitchedCollider* prev = old >= 0 ? (SwitchedCollider*)g_switchedColliders[old] : 0;
        vt[0x130 / 4]((*slot), 1, prev);
    }
}

LINKER_REMNANT(func_00192988);

void SetSwitchedColliderEnabled(SwitchedCollider* self, s32 value)
{
    if (self->f550 == value) return;
    self->f550 = value;
    if (value) AddToSwitchedColliderList(self);
    else RemoveFromSwitchedColliderList(self);
}

void ActivateSwitchedCollider(void* value)
{
    ActivateSwitchedColliderIndex(FindSwitchedColliderIndex(value));
}

void* GetActiveSwitchedColliderData()
{
    void* r = GetActiveSwitchedCollider();
    if (r) return (u8*)r + 0x580;
    return &D_00604700;
}

void GetSwitchedColliderInteractFlags(s32, s32, InteractFlags* out)
{
    out->b = 1;
    out->a = 1;
}

void ShowTypedTextCaptionBox(SwitchedCollider* self, u32 value)
{
    T217D_440* block = &g_typedTextCaptionBox;
    ((T217D_Word*)&block->child)->v = value;
    PushStackElement(g_elementStack, &g_typedTextCaptionBox);
}

void HandleStepSequenceSkipButtons(void* self, PadRecord* rec)
{
    if (IsTopCameraController(&g_camera->ctl454) != 0)
        return;
    PadRecord* a1 = (g_padRouting & 4) ? &g_padRecord : &g_blankPadRecord;
    StepSequence* ctx = D_0027051C;
    if (ctx != 0 && ctx->state2D4 == 3 && ctx->f32C == 0 && (a1->flags & 0xC) != 0
        && *(s32*)ctx->target304 != 0) {
        SkipRemainingSteps(ctx, a1);
    } else if ((rec->flags & 0xC) != 0 && D_0026F800 != 0) {
        SetStepSequenceState(D_0026F800, 1);
    }
    ClearPadPressedBits(rec, 0xC);
}

void UpdateSwitchedCollider(SwitchedCollider* self)
{
    UpdateCollider(self);

    u8* ctx = g_saveData;
    s32 cnt = *(s32*)(ctx + 0x19E4);
    s32 lim = ClampInt::Of(cnt, 0, 2);

    for (s32 i = 0; i < 3; i++) {
        void* e = self->f588[i];
        if ((self->flags & ((u64)1 << 32)) == 0 && i == lim) {
            if (e != 0) {
                (*(SlotFn**)e)[6](e);
            }
        } else {
            if (e != 0) {
                (*(SlotFn**)e)[7](e);
            }
        }
    }

    if (self->f600 == 1 || self->f600 == 3) {
        EmitSwitchedColliderTrailPoints(self);
    }
}

void FinishSwitchedCollider(SwitchedCollider* self)
{
    s32 flags = g_buttonCodeFlags & 2;
    if (flags == 0) {
        u8* g = g_saveData;
        s32 n = *(s32*)(g + 0x19E4) - 1;
        *(s32*)(g + 0x19E4) = flags < n ? n : 0;
    }

    PlacedObject* s1 = self->f604;
    if (s1 != 0) {
        Mat02 tmp;
        s1->desc->m02(s1);
        s1->desc->m15(s1, 0);
        RotateMatrixUpright(((u8*)self->f584) + 0x110, 0, &tmp);
        s1->desc02()->m1D(s1, (Vec02*)(((u8*)self->f584) + 0x140));
        s1->desc02()->m1E(s1, &tmp);
        s1->desc02()->m20(s1, (Vec02*)&D_00248D30);
        s1->desc02()->m21(s1, (Vec02*)&D_00248D30);
        void* r = (void*)FindFirstObjectById(self->world, 1, 0x18C, s1);
        if (r != 0) {
            CreateAnimationPlayerWithoutPresetTargets(r, s1, 0, 0, 0.0f, 1.0f);
        }
    } else {
        s32 v = (s32)self->f588[1];
        if (v != 0) {
            u8* g = (u8*)&D_00269BD0;
            *(s32*)(g + 0x28) = v;
            SpawnEffectsAt(((u8*)self->f584) + 0x140, (void*)&g_unitZVector, 1, g, &D_00269C10, 0, 0);
        }
    }
}

// A trail node of a switched collider's list at 0x5AC: when it was laid and the segment it spans.
struct TrailNode {
    u8 pad00[0x18];
    f32 time;               // 0x18
    u8 pad1C[0x80 - 0x1C];
    Vec02 v80;              // 0x80
    Vec02 v90;              // 0x90
};

// Sends the sink a message for each point along the segments to the attached node (or along
// the trail), one every 5 units. The segment loop's size decides what loop.c moves out: with
// the vectors as Vu0::Vec values and the walk a `for` from step to 1.0, pass 1 sees 82 insns and
// moves only the guard's 1.0 (jump.c's copy, life 2), pass 2 sees 79 and moves 0.0001; 5.0
// stays, as retail's (docs/TOOLCHAIN.md, "Loops").
void EmitSwitchedColliderTrailPoints(SwitchedCollider* self)
{
    Vec02 from[9];
    Vec02 to[9];
    SlotMessage msg;
    Vec02 a;
    Vec02 b;
    BaseObject* sink = *(BaseObject**)((u8*)self->world + 0x1D5C);
    s32 count;
    if (sink != 0) {
        PlacedObject* target = 0;
        void** nodes = (void**)((u8*)self + 0x59C);
        for (u32 k = 0; k < 4; k++) {
            if (nodes[k] != 0 && IsObjectAttached(nodes[k]) != 0) {
                target = (PlacedObject*)nodes[k];
                break;
            }
        }
        if (target != 0) {
            count = 1;
            s32 still = 0;
            if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(*(Vec02*)((u8*)self + 0x5E0)))) < 0.0001f
                && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(*(Vec02*)((u8*)self + 0x5E0)))) < 0.0001f
                && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(*(Vec02*)((u8*)self + 0x5E0)))) < 0.0001f) {
                still = 1;
            }
            if (still) {
                from[0] = target->v140;
            } else {
                from[0] = (*(Vec02*)((u8*)self + 0x5E0));
            }
            to[0] = target->v140;
        } else {
            count = 0;
            for (s32 k = 0; k < self->f5D0; k++) {
                TrailNode* n = (TrailNode*)self->f5AC[k];
                if (n != 0 && g_gameClock[1] >= n->time) {
                    from[count] = n->v90;
                    to[count] = n->v80;
                    count++;
                }
            }
        }
        msg.kind = 4;
        for (s32 i = 0; i < count; i++) {
            a = from[i];
            b = to[i];
            f32 len = Vu0::Distance(a, b);
            f32 step;
            if (len < 0.0001f) {
                step = 1.0f;
            } else {
                step = 5.0f / len;
            }
            for (f32 t = step; t < 1.0f; t += step) {
                *(Vu0::Vec*)&msg.vb = Vu0::MulXSum(Vu0::Vec::Of(a), Vu0::Vec::Scalar(1.0f - t), Vu0::Vec::Of(b), Vu0::Vec::Scalar(t));
                sink->desc->m1B(sink, &msg);
            }
            *(Vu0::Vec*)&msg.vb = Vu0::Vec::Of(b);
            sink->desc->m1B(sink, &msg);
            (*(Vec02*)((u8*)self + 0x5E0)) = b;
        }
    }
}

void* GetSwitchedColliderTarget(SwitchedCollider* p)
{
    return p;
}

// The static initialiser, which builds D_00604700 and D_00269C10 (nonmatching/func_001930B8.cpp).
INCLUDE_ASM(func_001930B8);

s32 ConstructSwitchedColliderDefaultsAtStartup(void)
{
    return ConstructSwitchedColliderDefaults(1, 0xFFFF);
}