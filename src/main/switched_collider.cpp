// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x1921A8 to 0x193210 (its .data from 0x269BC0, its .bss from 0x604700): the
// switched collider (class 0x05), the list of up to 16 of
// them and the active one, the typed caption box and step skipping it drives, and the static
// initialiser (func_001930B8, its _GLOBAL_$I$ func_001931F0 in retail's constructor list). Its
// .data provably starts at 0x269BC0: the global before it, g_targetVectors (D_00269BA8), is a
// list head of 0xC bytes like every other (include/globals.h), so D_00269BC0 (f32[3], aligned to
// 8) would follow it at 0x269BB8 in one file; retail has 8 more bytes of zeros and puts it on 16,
// the linker's padding before a new file's .data (aligned to 16 by Blk05's vectors). Its start in
// the code is a choice: any function start from 0x191FD8 to 0x192380 (point_graph.cpp says why);
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
#include "game_progress.h"
#include "pad_record.h"
#include "effect.h"
#include "vu0.h"
#include "object_message.h"
#include "object_finder.h"
#include "functions/base_object.h"
#include "functions/camera.h"
#include "functions/camera_controller.h"
#include "functions/collider.h"
#include "functions/effect_spawner.h"
#include "functions/matrix.h"
#include "functions/pad_input.h"
#include "functions/placed_object.h"
#include "functions/pooled_object.h"
#include "functions/sound_system.h"
#include "functions/warp_menu.h"
#include "functions/world.h"
struct ColliderPose;
struct Quad16;
struct SpawnBlock;
struct SpawnTail;
struct Mat02;

s32 FindSwitchedColliderIndex(void* obj);
s32 FindSwitchedColliderIndex(void* value);
void ActivateSwitchedColliderIndex(s32 index);
void* MoveMemory(void* dst, void* src, s32 size);
void AddToSwitchedColliderList(void* self);
void RemoveFromSwitchedColliderList(SwitchedCollider* value);
void AddToSwitchedColliderList(SwitchedCollider* self);
void RemoveFromSwitchedColliderList(SwitchedCollider* self);
void* GetActiveSwitchedCollider();
// The two interaction flags GetSwitchedColliderInteractFlags gives.
struct InteractFlags {
    s32 a;
    s32 b;
};
extern s32 g_buttonCodeFlags;
void* CreateEffect(s32 kind, EffectOwner* sys);
void AddEffectListener(void* node, void* owner);
// Descriptor slot 72 as func_00192880 calls it, with the collider switched from or to.
typedef void (*ActivationHook)(void* self, s32 mode, void* other);
extern u8 g_elementStack[];
extern s32 g_padRouting;
extern u8* g_playerStepSequence;
// A record whose 16-bit flags sit at 0xAA.


void SetSwitchedColliderEnabled(SwitchedCollider* self, s32 value);
void SetSwitchedColliderEnabled(SwitchedCollider* self, s32 mode);
void* GetActiveSwitchedCollider(void);
void ActivateSwitchedCollider(void* value);
// func_001EA4B8 takes its float arguments first: the caller then sets $f14 before $a0.
struct RampProfile;
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
f32 ApproachValueWithRamp(f32 x, f32 y, f32 z, RampProfile* k, f32* out);
extern s32 g_buttonCodeFlags;
// The parameters SpawnEffectsAt is given (word 0x28 set by the caller).
struct EffectSpawnParams { s32 f0, f4, f8, fC; f32 f10, f14; s32 f18, f1C; f32 f20, f24; s32 f28, f2C, f30, f34, f38, f3C; };
struct SpawnTail;
struct SpawnBlock;
void* GetActiveSwitchedCollider(void);
// kind==0x10 loop test at the top (retail tests it with the first slot peeled) and
// keeps one more register (frame 64 bytes as retail, but a different loop shape).

struct PlayingSound;
typedef void (*SlotFn)(void* self);
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
f32 g_followZRamp[3] = { 1000.0f, 10.0f, 1.0f };
s32 g_activeSwitchedCollider = -1;
EffectSpawnParams g_switchedEffectParams = { 0x18, -1, 0, 0, 1.0f, 2.0f, 0, 0, 1.0f, 2.0f, 0, 0, 0, 1, 0, 0 };
// Built by the file's static initialiser (func_001930B8, which the compiler makes from these two
// brace initialisers): a vector member copied from a global makes an initialiser run at run
// time, into a temporary that is then copied whole. Both stay where retail has them: the static
// in .bss, the global with the uninitialised ones at the end of .data.
static Blk05 g_defaultSwitchedColliderData = {
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { { 0, 0, 0, 0 } }, 0.0f, 0.0f, 0.0f, 0,
    { 0.0f, 0.0f, 0.0f }, *(Quad16*)&D_00248D30, { 0.0f, 0.0f, 0.0f }
};
Blk05 g_switchedEffectBlock = {
    { 1000.0f, 1200.0f, 1.0f }, { 0.0f, 0.0f, -1750.0f }, { -0.5f, 0.0f, 0.0f }, *(Quad16*)&g_unitZVector, 0.0f, 0.0f, 0.0f, 1,
    { 0.5f, 2.0f, 0.0f }, { { 0, 0, 0, 0 } }, { 1.0f, -1.0f, 0.0f }
};
s32 g_switchedColliderCount;
void* g_switchedColliders[16];
extern f32 g_gameClock[];

// Initialises the collider, points f598 at itself, sets f580 to 1 and enables it.
void InitSwitchedCollider(SwitchedCollider* self)
{
    InitCollider(self);
    self->f598 = self;
    self->f580 = 1;
    SetSwitchedColliderEnabled(self, 1);
}

// Copies the collider and, if the copy is not enabled, sets it enabled and then disabled again, so
// that it ends up off the list.
void CopySwitchedCollider(SwitchedCollider* self, SwitchedCollider* src)
{
    CopyCollider(self, src);
    if (self->enabled != 0) {
        return;
    }
    self->enabled = 1;
    SetSwitchedColliderEnabled(self, 0);
}

// After the placed object's handling: kind 0xB stops the collider's playing sound; kind 0x10
// removes the message's object from the collider's effect list (its slot is cleared).
void HandleSwitchedColliderNotification(SwitchedCollider* self, s32 kind, void* msg)
{
    HandlePlacedObjectNotification(self, kind, msg);
    switch (kind) {
    case 0xB:
        StopSoundRecord((PlayingSound*)self->playingSound, 0);
        break;
    case 0x10: {
        s32 i;
        for (i = 0; i < self->effectCount; i++) {
            if (self->effects[i] == msg) {
                self->effects[i] = 0;
                break;
            }
        }
        break;
    }
    }
}

// With an activator, remembers the collider's position as the focus point and pushes a camera
// controller for it; without one (deactivation), removes the camera controllers of kinds 1 to 6.
void HandleSwitchedColliderActivation(SwitchedCollider* self, void* activator)
{
    if (activator != 0) {
        self->focusPoint = self->v140;
        PushCameraController(g_camera, 1, &g_camera->ctl520, self, 0);
        return;
    }
    for (s32 i = 1; i < 7; i++) {
        RemoveCameraControllers(g_camera, 5, i, 0, self, 0);
    }
}

// Captures the collider's pose for the camera; unless it holds its focus, eases the focus point's z
// toward the collider's z while the camera is not snapping, and stores the pose's focus back at
// 0x560.
void CaptureSwitchedColliderPose(SwitchedCollider* self, u8* out, f32 a)
{
    CaptureColliderPose(self, (ColliderPose*)out);
    if (self->holdFocus != 0) {
        *(Quad16*)(out + 0x10) = *(Quad16*)&self->focusPoint;
        return;
    }
    Camera* base = g_camera;
    if (base->snapping == 0) {
        *(f32*)(out + 0x18) = ApproachValueWithRamp(self->focusPoint.z, self->v140.z, a, (RampProfile*)g_followZRamp, 0);
    }
    *(Quad16*)&self->focusPoint = *(Quad16*)(out + 0x10);
}

// Always 1: the base collider does not hold the camera.
s32 IsSwitchedColliderCameraFree(void)
{
    return 1;
}

// Makes the collider the active one unless it already is.
void ActivateSwitchedColliderUnlessActive(void* self)
{
    if (self != GetActiveSwitchedCollider()) ActivateSwitchedCollider(self);
}

// A request is blocked while button-code flag bit 1 is set or the pad-select flag is held.
s32 IsSwitchedColliderRequestBlocked(SwitchedCollider* self)
{
    if ((g_buttonCodeFlags & 1) || IsPadSelectFlagHeld(self->world)) return 1;
    return 0;
}

// Always refuses a request (0); the subclasses override it.
s32 AcceptSwitchedColliderRequest(SwitchedCollider* self)
{
    return 0;
}

// Always 0 in the base class.
s32 HasSwitchedColliderAcceptedRequest(void)
{
    return 0;
}

// Stores the result of the collider's method 0x4D (called with out) in *out.
void StoreSwitchedColliderAccepted(SwitchedCollider* self, s32* out)
{
    *out = ((s32 (*)(SwitchedCollider*, s32*))self->desc05()->m4D)(self, out);
}

// Starts the collider's effect for a mode: in mode 0 it creates an effect (class 0x1A) at the other
// object, registers the collider as its listener and sets its life from the animation's marker
// 0x13F; the other modes start theirs.
void StartSwitchedColliderEffect(SwitchedCollider* self, s32 mode, PlacedObject* other)
{
    switch (mode) {
    case 0:
        if (self->f5F0 == 0)
            return;
        {
            Effect* n = (Effect*)CreateEffect(0x1A, 0);
            self->effects[0] = n;
            self->effectCount = 1;
            if (n != 0) {
                void (*init)(Effect* self, void* pos, f32 scale, s32 flags) = n->vt->m00;
                init(n, (u8*)&other->v140, 1.0f, 0);
                AddEffectListener(n, self);
                f32 r = GetAnimationMarkerTime((Animation*)self->f5F0, 0x13F);
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

// The active collider (the global active index into the list), or 0 when none is active.
void* GetActiveSwitchedCollider()
{
    s32 i = g_activeSwitchedCollider;
    if (i < 0) return 0;
    return g_switchedColliders[i];
}

// The active switched collider, else the player when it is enabled, else the first of the list,
// else 0.
void* GetCurrentSwitchedCollider(void)
{
    void* r = GetActiveSwitchedCollider();
    if (r == 0) {
        Player* q = g_player;
        if (q != 0) {
            s32 t = q->enabled;
            if (t != 0) r = q;
        }
    }
    if (r == 0 && g_switchedColliderCount != 0) {
        r = g_switchedColliders[0];
    }
    return r;
}

// The index of obj in the global list of switched colliders, or -1.
s32 FindSwitchedColliderIndex(void* obj)
{
    s32 i;
    for (i = 0; i < g_switchedColliderCount; i++) {
        if (obj == g_switchedColliders[i]) {
            return i;
        }
    }
    return -1;
}

// Adds an enabled, parentless, attached collider to the global list of switched colliders (16 at
// most) unless it is already there; when the list is full, the collider with id 5 takes slot 0
// while there is no player.
void AddToSwitchedColliderList(SwitchedCollider* self)
{
    if (self->enabled == 0) return;
    if (self->parent != 0) return;
    if (!IsObjectAttached(self)) return;
    if (FindSwitchedColliderIndex(self) >= 0) return;
    s32 n = g_switchedColliderCount;
    if ((u32)n < 16) {
        g_switchedColliders[n] = self;
        g_switchedColliderCount = n + 1;
    } else if (self->id == 5 && g_player == 0) {
        g_switchedColliders[0] = self;
    }
}

// Removes the collider from the global list, deactivating it first if it is the active one, closing
// the gap and keeping the active index pointing at the same entry.
void RemoveFromSwitchedColliderList(SwitchedCollider* value)
{
    s32 idx = FindSwitchedColliderIndex(value);
    if (idx < 0) return;
    if (idx == g_activeSwitchedCollider) ActivateSwitchedColliderIndex(-1);
    s32 n = g_switchedColliderCount;
    MoveMemory(&g_switchedColliders[idx], &g_switchedColliders[idx + 1], (n - idx) * 4 - 4);
    if (idx < g_activeSwitchedCollider) g_activeSwitchedCollider = g_activeSwitchedCollider - 1;
    g_switchedColliderCount = g_switchedColliderCount - 1;
}

// Registers the collider as a collider and adds it to the switched list.
void RegisterSwitchedCollider(SwitchedCollider* self)
{
    RegisterCollider(self);
    AddToSwitchedColliderList(self);
}

// Unregisters the collider and removes it from the switched list.
void UnregisterSwitchedCollider(SwitchedCollider* self)
{
    UnregisterCollider(self);
    RemoveFromSwitchedColliderList(self);
}

// Makes the switched collider with this index the active one (-1 for none): the old one loses flag
// bit 45 and gets its activation method (slot 0x130) called with 0, and the new one gets the bit
// and the call with 1, each told the other.
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

// Changes the enabled flag, adding the collider to the global list when it turns on and removing it
// when it turns off.
void SetSwitchedColliderEnabled(SwitchedCollider* self, s32 value)
{
    if (self->enabled == value) return;
    self->enabled = value;
    if (value) AddToSwitchedColliderList(self);
    else RemoveFromSwitchedColliderList(self);
}

// Makes the collider the active one (by its index in the list; -1 if it is not in it).
void ActivateSwitchedCollider(void* value)
{
    ActivateSwitchedColliderIndex(FindSwitchedColliderIndex(value));
}

// The data block at 0x580 of the active collider, or a default block when none is active.
void* GetActiveSwitchedColliderData()
{
    void* r = GetActiveSwitchedCollider();
    if (r) return &((SwitchedCollider*)r)->blk580;
    return &g_defaultSwitchedColliderData;
}

// Gives back interact flags a and b both set to 1.
void GetSwitchedColliderInteractFlags(s32, s32, InteractFlags* out)
{
    out->b = 1;
    out->a = 1;
}

// Stores value in the typed-text caption box and pushes the box on the element stack.
void ShowTypedTextCaptionBox(SwitchedCollider* self, u32 value)
{
    T217D_440* block = &g_typedTextCaptionBox;
    ((T217D_Word*)&block->child)->v = value;
    PushStackElement((ElementStack*)g_elementStack, &g_typedTextCaptionBox);
}

// Skip handling for step sequences: unless a camera controller is on top, a press of the buttons
// 0xC while the active sequence is in state 3 (and its target is reached) skips its remaining
// steps; otherwise the player's own sequence goes to state 1. The pressed bits are then cleared.
void HandleStepSequenceSkipButtons(void* self, PadRecord* rec)
{
    if (IsTopCameraController(&g_camera->ctl454) != 0)
        return;
    PadRecord* a1 = (g_padRouting & 4) ? &g_padRecord : &g_blankPadRecord;
    StepSequence* ctx = g_activeStepSequence;
    if (ctx != 0 && ctx->state2D4 == 3 && ctx->f32C == 0 && (a1->flags & 0xC) != 0
        && *(s32*)ctx->target304 != 0) {
        SkipRemainingSteps(ctx);
    } else if ((rec->flags & 0xC) != 0 && g_playerStepSequence != 0) {
        SetStepSequenceState((StepSequence*)g_playerStepSequence, 1);
    }
    ClearPadPressedBits(rec, 0xC);
}

// Per-frame update of a switched collider: updates it as a collider, then, of its three slot
// objects, calls slot method 6 on the one at the level read from the save's counter (0 to 2) unless
// it is hidden, and method 7 on the others; in states 1 and 3 it emits trail points.
void UpdateSwitchedCollider(SwitchedCollider* self, f32 dt)
{
    UpdateCollider(self, dt);

    s32 cnt = g_saveData->spareCount;
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

// Ends a switched collider's turn: lowers the save's counter at 0x19E4 by one (not below 0) unless
// button code flag 2 is set, then, when it has an object f604, places that object at the collider's
// frame and starts its animation (found by id 0x18C), otherwise spawns an effect at the collider
// with the object in slot 1.
void FinishSwitchedCollider(SwitchedCollider* self)
{
    s32 flags = g_buttonCodeFlags & 2;
    if (flags == 0) {
        s32 n = g_saveData->spareCount - 1;
        g_saveData->spareCount = flags < n ? n : 0;
    }

    PlacedObject* s1 = self->f604;
    if (s1 != 0) {
        Mat02 tmp;
        s1->desc->m02(s1);
        s1->desc->m15(s1, 0);
        RotateMatrixUpright(&((PlacedObject*)self->f584)->m110, 0, &tmp);
        s1->desc02()->m1D(s1, &((PlacedObject*)self->f584)->v140);
        s1->desc02()->m1E(s1, &tmp);
        s1->desc02()->m20(s1, (Vec02*)&D_00248D30);
        s1->desc02()->m21(s1, (Vec02*)&D_00248D30);
        void* r = (void*)FindFirstObjectById(self->world, 1, 0x18C, s1);
        if (r != 0) {
            CreateAnimationPlayerWithoutPresetTargets((Animation*)r, s1, 0, 0, 0.0f, 1.0f);
        }
    } else {
        s32 v = (s32)self->f588[1];
        if (v != 0) {
            u8* g = (u8*)&g_switchedEffectParams;
            *(s32*)(g + 0x28) = v;
            SpawnEffectsAt((Quad16*)&((PlacedObject*)self->f584)->v140, (Quad16*)&g_unitZVector, 1, (SpawnTail*)g, (SpawnBlock*)&g_switchedEffectBlock, 0, 0);
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
    BaseObject* sink = self->world->slot1CE8[29];
    s32 count;
    if (sink != 0) {
        PlacedObject* target = 0;
        void** nodes = (void**)&self->f59C;
        for (u32 k = 0; k < 4; k++) {
            if (nodes[k] != 0 && IsObjectAttached((BaseObject*)nodes[k]) != 0) {
                target = (PlacedObject*)nodes[k];
                break;
            }
        }
        if (target != 0) {
            count = 1;
            s32 still = 0;
            if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(self->f5E0))) < 0.0001f
                && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(self->f5E0))) < 0.0001f
                && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(self->f5E0))) < 0.0001f) {
                still = 1;
            }
            if (still) {
                from[0] = target->v140;
            } else {
                from[0] = (self->f5E0);
            }
            to[0] = target->v140;
        } else {
            count = 0;
            for (s32 k = 0; k < self->effectCount; k++) {
                TrailNode* n = (TrailNode*)self->effects[k];
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
            (self->f5E0) = b;
        }
    }
}

// The collider's own target is itself.
void* GetSwitchedColliderTarget(SwitchedCollider* p)
{
    return p;
}

// The file's static initialiser (func_001930B8) and its _GLOBAL_$I$ (func_001931F0) follow: the
// compiler makes them from D_00604700's and D_00269C10's initialisers (config/us/generated.tsv).