// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "vu0.h"
#include "asm_func.h"
#include "counted_collider.h"
#include "switched_collider.h"
#include "globals.h"
#include "game_progress.h"
#include "pad_record.h"
#include "object_message.h"
#include "screen_element.h"
#include "game_clock.h"
#include "vu0.h"
#include "object_finder.h"
struct MemberObject;
struct PlacedObject;
struct World;

struct Mat02;


// Types other files define, named by the parameters of their functions declared here.
struct ObjectLink;

s32 g_modeMasks[8] = { 0x12, 0x404, 0x1008, 0x40, 0x80, 0x200, 0x8000, 0 };
const char* g_modeLabels[7] = { "&2T&.: Dive", "&2T&.: Roll", "&2T&.: Slow", "&2T&.: Mine", "&2T&.: Fast", "&2T&.: Decoy", "&2T&.: Stun" };
s32 g_currentMode = -1;
float D_00274F78[3] = {2.0f, 0.0f, 0.100000001f};
float D_00274F84 = 1.5f;
float D_00274F88[2] = {0.25f, 0.0f};
s32 g_countedColliderLinkIds[4] = { 0x22, 0x152, 0x558, 0 };

struct ContactObject;

struct ContactEvent {
    ContactObject* ref;
    u8 pad0[0xC - 4];
    s32 flags;
};

struct ContactObject {
    s32* vtbl;
    u8 pad0[0x18 - 4];
    ContactObject* parent;
    u8 pad1[0x50 - 0x1C];
    s32 root;
};


void* HandleObjectEvent(Collider* a, void* event);
void FreePooledContactChain(World* world, Contact03* head);

void ExtractContactsByPartMode(Collider* self, Contact03** out);

void StartPlacedObject(PlacedObject* self);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);

struct CountedTouchMessage {
    void* self;
    void* v;
};

void SendEmptyMessage(MemberObject* a0);
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
void TriggerScriptEvent(BaseObject* self, s32 idx, s32 flag, void* out);

struct AnimatedObject105 { u8 pad[0x7E0]; void* obj; };


void SeekAnimationPlayer(AnimationPlayer* self, s32 mode, f32 a, f32 b);


void StepCollider(Collider* self, f32 t);
void RotateMatrixUpright(Mat02* self, Mat02* scratch, Mat02* out);
void SteerColliderTowardRotation(Collider* self, Mat02* target, f32* pull, Vec02* aim, f32* turn, f32 limit);


struct PooledContact;
void HandlePlacedObjectNotification(PlacedObject* self, s32 mode, void* arg);
PooledContact* CreatePooledContact(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, void* a5, void* a6, void* a7);

void ClearPadPressedBits(PadRecord* self, u32 mask);
s32 MaskWorldBitsBySave(void);

struct PlayerHeldObject;
extern f32 g_stepScale;

void SetPlayerState(Player* self, s32 a, s32 b);
s32 IsObjectAttached(BaseObject* self);
void FadeOutPlacedObject(Collider* self, f32 time);
void TakeCountedColliderTouch(CountedCollider* self, void* v, s32 flag);
void SeekObjects105Animations(Player* self, s32 value);
void* GetActiveSwitchedCollider(void);

void ShowModeLabel(s32 mode);
s32 FindNextTableIndexMatchingMask(PadRecord* self, s32 start, s32 count, s32* table);
void TakeCountedColliderTouch(CountedCollider* self, void* v, s32 flag);
void* HandleCountedColliderEvent(CountedCollider* a0, ContactEvent* a1);
void HandleCountedColliderNotification(CountedCollider* self, s32 kind, ObjectMessage* msg);

void ShowModeLabel(s32 mode)
{
    switch (g_currentMode) {
    case 1:
        if (g_player == 0)
            goto tail;
        if (g_player->state == 0xD)
            SetPlayerState(g_player, 0, -1);
        break;
    case 3:
        if (g_player == 0)
            goto tail;
        if (((PlayerHeldObject*)g_player->f1518) != 0) {
            if (IsObjectAttached((BaseObject*)g_player->f1518) != 0)
                FadeOutPlacedObject((Collider*)((g_player->f1518)), 0.5f);
        }
        break;
    }
    if (g_player != 0) {
        g_stepScale = 1.0f;
        if (((PlayerHeldObject*)g_player->contactOwner) != 0) {
            if (IsObjectAttached((BaseObject*)g_player->contactOwner) != 0)
                TakeCountedColliderTouch((CountedCollider*)g_player->contactOwner, g_player, 1);
        }
        SeekObjects105Animations(g_player, 0);
        if (g_player != 0) {
            if ((void*)g_player == GetActiveSwitchedCollider())
                g_currentMode = mode;
        }
    }
tail:
    if (mode != g_saveData->lastHintMode && (u32)mode < 7) {
        SetScreenElementHoldTime(&g_buttonHintElement, (g_player != 0 && (void*)g_player == GetActiveSwitchedCollider()) ? 3.0f : 8.0f);
        SetScreenElementScale(&g_buttonHintElement, 0.6f);
        g_buttonHintElement.vt->m08(&g_buttonHintElement, g_modeLabels[mode]);
        g_buttonHintElement.vt->m14(&g_buttonHintElement);
        g_saveData->lastHintMode = mode;
    }
}

extern f32 g_frameStep;
extern s32 g_padSelectFlags;
void ShowModeLabel(s32 mode);
s32 AreFloatsNearlyEqual(f32 a, f32 b, f32 eps);
struct RampProfile;
f32 ApproachValueWithRamp(RampProfile* k, f32* out, f32 x, f32 y, f32 z);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
void TurnColliderTowardHeading(TurningCollider* self);

void UpdateModeSelection(Player* self, PadRecord* pad)
{
    s32 ok;
    if (g_currentMode >= 0) {
        if ((g_modeMasks[g_currentMode] & MaskWorldBitsBySave()) == 0) {
            ShowModeLabel(-1);
            g_saveData->lastHintMode = -1;
        }
    }
    switch (g_currentMode) {
    case -1:
        ok = 1;
        break;
    case 2:
    case 4:
        ok = AreFloatsNearlyEqual(g_stepScale, 1.0f, 0.0001f);
        break;
    case 1:
        ok = 0;
        if (g_player == 0 || g_player->state != 13) {
            ok = 1;
        }
        break;
    case 0:
        ok = 0;
        if (g_player == 0) {
            ok = 1;
            break;
        }
        {
            s32 state = g_player->state;
            if (state == 10) {
                break;
            }
            if (state == 2 && g_player->subState == 8) {
                break;
            }
        }
        ok = 1;
        break;
    case 5:
        ok = g_player->state != 14;
        break;
    case 6:
        ok = 0;
        if (g_player->state != 15) {
            ok = g_player->animSeekValue == 0;
        }
        break;
    case 3:
        ok = g_player->state != 16;
        break;
    }
    if (g_player != 0 && g_player->state == 4) {
        ok = 0;
    }
    if (g_typedTextCaptionBox.mode != 0) {
        ok = 0;
    }
    if (ok && (pad->flags & 3)) {
        s32 m = FindNextTableIndexMatchingMask(pad, g_currentMode, 7, g_modeMasks);
        g_saveData->lastHintMode = -1;
        ShowModeLabel(m);
    }
    switch (g_currentMode) {
    case 4:
        if (g_typedTextCaptionBox.state == 3) {
            self->speedUpAmount = 0.0f;
        } else if (pad->buttons & 0x10) {
            self->speedUpAmount = 1.0f;
        } else {
            self->speedUpAmount = ApproachValueWithRamp((RampProfile*)D_00274F78, 0, self->speedUpAmount, 0.0f, g_frameStep);
        }
        g_stepScale = self->speedUpAmount * D_00274F84 + (1.0f - self->speedUpAmount);
        break;
    case 2:
        if (g_padSelectFlags & 3) {
            self->slowDownHeld = 0;
        } else if (g_typedTextCaptionBox.state == 3) {
            self->slowDownHeld = 0;
        } else if (self->state == 2) {
            if (pad->flags & 0x10) {
                ClearPadPressedBits(pad, 0x10);
                self->slowDownHeld = 1;
            }
        } else if (pad->buttons & 0x10) {
            if (MaskWorldBitsBySave() & 0x1000) {
                self->slowDownHeld = 1;
            } else {
                self->slowDownHeld = 0;
            }
        } else {
            self->slowDownHeld = 0;
        }
        if (self->slowDownHeld != 0) {
            g_stepScale = D_00274F88[0];
        } else {
            g_stepScale = 1.0f;
        }
        break;
    case 1:
        switch (self->state) {
        case 0:
        case 1:
        case 2:
            if (pad->flags & 0x10) {
                ClearPadPressedBits(pad, 0x10);
                if (self->groundContact != 0) {
                    SetPlayerState(self, 13, 0x37);
                } else {
                    SetPlayerState(self, 13, 0x36);
                }
            }
        }
        break;
    case 5:
        if ((u32)self->state < 2 && (pad->flags & 0x10) && self->contactOwner != 0) {
            ClearPadPressedBits(pad, 0x10);
            SetPlayerState(self, 14, -1);
        }
        break;
    case 6:
        if ((u32)self->state < 2) {
            if (pad->flags & 0x10) {
                ClearPadPressedBits(pad, 0x10);
                SetPlayerState(self, 15, -1);
            }
        }
        if (self->animSeekValue != 0 && 3.0f < g_gameClock.time - self->animSeekTime) {
            SeekObjects105Animations(self, 0);
        }
        break;
    case 3:
        if ((u32)self->state < 2 && (pad->flags & 0x10) && self->f1518 != 0) {
            ClearPadPressedBits(pad, 0x10);
            if (IsObjectAttached((BaseObject*)self->f1518)) {
                Vec02 d;
                Vu0::Q(d) = Vu0::Sub(Vu0::Q(((PlacedObject*)self->f1518)->v140), Vu0::Q(self->v140));
                self->heading = ArctangentOfRatio(d.y, d.x);
                TurnColliderTowardHeading(self);
                SetPlayerState(self, 16, 0x3A);
            } else {
                SetPlayerState(self, 16, 0x39);
            }
        }
        break;
    }
}

s32 FindNextTableIndexMatchingMask(PadRecord* self, s32 start, s32 count, s32* table)
{
    s32 step;
    s32 left;
    s32 idx;

    if ((self->flags & 3) == 0) {
        return start;
    }
    step = (self->flags & 1) ? -1 : 1;
    ClearPadPressedBits(self, 3);
    idx = start;
    left = count;
    do {
        if (--left < 0) {
            return start;
        }
        idx += step;
        if (idx < 0) {
            idx = count - 1;
        } else if (idx >= count) {
            idx = 0;
        }
    } while (!(MaskWorldBitsBySave() & table[idx]));
    return idx;
}

void SeekObjects105Animations(Player* self, s32 value)
{
    void* buf[0x100];
    if (value == self->animSeekValue) {
        return;
    }
    s32 n = GatherObjectsById(self->world, 0x105, 8, 0, 0x100, buf);
    for (s32 i = 0; i < n; i++) {
        AnimatedObject105* item = (AnimatedObject105*)buf[i];
        if (item->obj != 0) {
            SeekAnimationPlayer((AnimationPlayer*)item->obj, 1, 0.0f, value != 0 ? 0.0f : 1.0f);
        }
    }
    self->animSeekValue = value;
    self->animSeekTime = g_gameClock.time;
}

void StartCountedCollider(CountedCollider* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 1, (ObjectLink*)g_countedColliderLinkIds);
    self->desc->m03(self);
}

void TakeCountedColliderTouch(CountedCollider* self, void* v, s32 flag)
{
    if (flag == 0) {
        CountedTouchMessage msg;
        msg.v = v;
        msg.self = self;
        self->desc->m0E(self, 0x17, &msg);
        self->touchesLeft = self->touchesLeft - 1;
        if (self->touchesLeft > 0) {
            return;
        }
    }
    SendEmptyMessage((MemberObject*)self->target);
    StartSoundEffect(0x67, 0, 0, &self->v140, 4000.0f, 750.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    TriggerScriptEvent(self, 2, 0, 0);
    self->desc->m03(self);
}

void UpdateCollider(Collider* self, f32 dt);

void UpdateCountedCollider(CountedCollider* self, f32 dt)
{
    UpdateCollider(self, dt);
    if (g_player != 0 && 2000.0f < Vu0::ToFloat(Vu0::Length(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(g_player->v140))))) {
        TakeCountedColliderTouch(self, g_player, 1);
    } else if (self->parent == 0) {
        Contact03* c = (Contact03*)self->contacts;
        if (c != 0) {
            s32 i = self->root == c->end[0].body;
            TakeCountedColliderTouch(self, c->end[i].part, 0);
        }
    }
    FreePooledContactChain(self->world, self->contacts);
    self->contacts = 0;
}

void StepCountedCollider(CountedCollider* self, f32 t)
{
    u8 buf[0x30];

    StepCollider(self, t);
    if (self->parent == 0) {
        RotateMatrixUpright(&self->rot, 0, (Mat02*)buf);
        SteerColliderTowardRotation(self, (Mat02*)buf, (f32*)self->p214, (Vec02*)&D_00248D30, (f32*)self->p218, t);
    }
}

void CollectCountedColliderContacts(CountedCollider* self)
{
    ExtractContactsByPartMode(self, (Contact03**)&self->contacts);
}

void* HandleCountedColliderEvent(CountedCollider* a0, ContactEvent* a1)
{
    void* r = HandleObjectEvent(a0, a1);
    if (r != 0 && (a1->flags & 0x20)) {
        ContactObject* a2 = a1->ref;
        s32 v1;
        if (a2->vtbl[2] & 1) {
            v1 = a2->root;
        } else {
            v1 = a2->parent->root;
        }
        TakeCountedColliderTouch(a0, a1->ref, (v1 ^ (s32)g_player) == 0);
        FreePooledContactChain(a0->world, a0->contacts);
        a0->contacts = 0;
    }
    return r;
}

struct FrameSource;
struct FrameSourceDesc { u8 pad00[0x1C]; void (*getFrame)(FrameSource* self, Mat02* out); };
struct FrameSource { FrameSourceDesc* desc; };
typedef u64 Qword128 __attribute__((mode(TI)));
void ComputePlacedObjectWorldFrame(PlacedObject* self);
void ComputeColliderWorldFrame(Collider* self);
void TransformMeshToWorld(Mesh03* a, Mesh03* b, Qword128 q, Mat02* c);

void ComputeCountedColliderWorldFrame(CountedCollider* self)
{
    if (self->matrixAttachment != 0) {
        Mat02 world;
        Mat02 frame;
        Mat02 copyA;
        Mat02 copyB;
        ComputePlacedObjectWorldFrame(self);
        FrameSource* src = (FrameSource*)self->matrixAttachment;
        src->desc->getFrame(src, &frame);
        u128 r0 = Vu0::RotateUntied(self->m110, Vu0::Q(frame.r[0]));
        u128 r1 = Vu0::RotateUntied(self->m110, Vu0::Q(frame.r[1]));
        u128 r2 = Vu0::RotateUntied(self->m110, Vu0::Q(frame.r[2]));
        Vu0::Q(copyB.r[0]) = r0;
        Vu0::Q(copyA.r[0]) = r0;
        Vu0::Q(copyB.r[1]) = r1;
        Vu0::Q(copyA.r[1]) = r1;
        Vu0::Q(copyB.r[2]) = r2;
        Vu0::Q(copyA.r[2]) = r2;
        Vu0::Q(world.r[0]) = r0;
        Vu0::Q(world.r[1]) = r1;
        Vu0::Q(world.r[2]) = r2;
        TransformMeshToWorld(&self->mesh, &self->meshCopy, *(Qword128*)&self->v140, &world);
    } else {
        ComputeColliderWorldFrame(self);
    }
}

void HandleCountedColliderNotification(CountedCollider* self, s32 kind, ObjectMessage* msg)
{
    HandlePlacedObjectNotification(self, kind, msg);
    if (kind == 10) {
        CreatePooledContact(0.0f, self, (void*)msg->kind, &self->v140, (void*)&g_unitZVector, 10, 0, 0, &self->contacts);
    }
}
