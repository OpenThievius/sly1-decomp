// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "counted_collider.h"
#include "switched_collider.h"
#include "globals.h"
#include "game_progress.h"
#include "pad_record.h"
#include "object_message.h"
#include "screen_element.h"
#include "game_clock.h"

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
    ContactObject* f18;
    u8 pad1[0x50 - 0x1C];
    s32 f50;
};


void* HandleObjectEvent(Collider* a);
void FreePooledContactChain(void* a, s32 b);

void ExtractContactsByPartMode(void* self, void* sub);

void StartPlacedObject(void* self);
void ResolveObjectLinks(void* self, s32 a1, void* a2);

struct CountedTouchMessage {
    void* self;
    void* v;
};

void SendEmptyMessage(void* x);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);

struct AnimatedObject105 { u8 pad[0x7E0]; void* obj; };


s32 GatherObjectsById(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void SeekAnimationPlayer(void* obj, s32 a1, f32 fa, f32 fb);


void StepCollider(Collider* self, f32 t);
void RotateMatrixUpright(Mat02* sub, s32 zero, void* out);
void SteerColliderTowardRotation(Collider* self, void* buf, s32 a, void* p, s32 b, f32 t);


void HandlePlacedObjectNotification(PlacedObject* self, s32 kind, ObjectMessage* msg);
s32 CreatePooledContact(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);

void ClearPadPressedBits(PadRecord* self, s32 mask);
s32 MaskWorldBitsBySave(void);

struct PlayerHeldObject;
extern f32 g_stepScale;

void SetPlayerState(Player* self, s32 a, s32 b);
s32 IsObjectAttached(PlayerHeldObject* self);
void FadeOutPlacedObject(PlayerHeldObject* self, f32 v);
void TakeCountedColliderTouch(PlayerHeldObject* self, Player* a, s32 b);
void SeekObjects105Animations(Player* self, s32 a);
void* GetActiveSwitchedCollider(void);

void ShowModeLabel(u32 mode);
s32 FindNextTableIndexMatchingMask(PadRecord* self, s32 start, s32 count, s32* table);
void TakeCountedColliderTouch(CountedCollider* self, void* v, s32 flag);
void* HandleCountedColliderEvent(CountedCollider* a0, ContactEvent* a1);
void HandleCountedColliderNotification(CountedCollider* self, s32 kind, ObjectMessage* msg);

void ShowModeLabel(u32 mode)
{
    switch (g_currentMode) {
    case 1:
        if (g_player == 0)
            goto tail;
        if (g_player->f2220 == 0xD)
            SetPlayerState(g_player, 0, -1);
        break;
    case 3:
        if (g_player == 0)
            goto tail;
        if (((PlayerHeldObject*)g_player->f1518) != 0) {
            if (IsObjectAttached(((PlayerHeldObject*)g_player->f1518)) != 0)
                FadeOutPlacedObject(((PlayerHeldObject*)g_player->f1518), 0.5f);
        }
        break;
    }
    if (g_player != 0) {
        g_stepScale = 1.0f;
        if (((PlayerHeldObject*)g_player->f2750) != 0) {
            if (IsObjectAttached(((PlayerHeldObject*)g_player->f2750)) != 0)
                TakeCountedColliderTouch(((PlayerHeldObject*)g_player->f2750), g_player, 1);
        }
        SeekObjects105Animations(g_player, 0);
        if (g_player != 0) {
            if ((void*)g_player == GetActiveSwitchedCollider())
                g_currentMode = mode;
        }
    }
tail:
    if (mode != g_saveData->f19FC && mode < 7) {
        SetScreenElementHoldTime(&g_buttonHintElement, (g_player != 0 && (void*)g_player == GetActiveSwitchedCollider()) ? 3.0f : 8.0f);
        SetScreenElementScale(&g_buttonHintElement, 0.6f);
        g_buttonHintElement.vt->m08(&g_buttonHintElement, g_modeLabels[mode]);
        g_buttonHintElement.vt->m14(&g_buttonHintElement);
        g_saveData->f19FC = mode;
    }
}

INCLUDE_RODATA(jtbl_0024DB90);
INCLUDE_RODATA(jtbl_0024DBB0);
ASM_FUNC(func_001D2BB8);

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
    if (value == self->f275C) {
        return;
    }
    s32 n = GatherObjectsById(self->world, 0x105, 8, 0, 0x100, buf);
    for (s32 i = 0; i < n; i++) {
        AnimatedObject105* item = (AnimatedObject105*)buf[i];
        if (item->obj != 0) {
            SeekAnimationPlayer(item->obj, 1, 0.0f, value != 0 ? 0.0f : 1.0f);
        }
    }
    self->f275C = value;
    self->f2758 = g_gameClock.time;
}

void StartCountedCollider(CountedCollider* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 1, g_countedColliderLinkIds);
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
    SendEmptyMessage(self->target);
    StartSoundEffect(0x67, 0, 0, (s32)&self->v140, 0, 0, 4000.0f, 750.0f, 1.0f, 0.0f, 0.0f);
    TriggerScriptEvent(self, 2, 0, 0);
    self->desc->m03(self);
}

ASM_FUNC(func_001D3398);

void StepCountedCollider(CountedCollider* self, f32 t)
{
    u8 buf[0x30];

    StepCollider(self, t);
    if (self->parent == 0) {
        RotateMatrixUpright(&self->rot, 0, buf);
        SteerColliderTowardRotation(self, buf, (s32)self->p214, (void*)&D_00248D30, (s32)self->p218, t);
    }
}

void CollectCountedColliderContacts(CountedCollider* self)
{
    ExtractContactsByPartMode(self, &self->contacts);
}

void* HandleCountedColliderEvent(CountedCollider* a0, ContactEvent* a1)
{
    void* r = HandleObjectEvent(a0);
    if (r != 0 && (a1->flags & 0x20)) {
        ContactObject* a2 = a1->ref;
        s32 v1;
        if (a2->vtbl[2] & 1) {
            v1 = a2->f50;
        } else {
            v1 = a2->f18->f50;
        }
        TakeCountedColliderTouch(a0, a1->ref, (v1 ^ (s32)g_player) == 0);
        FreePooledContactChain(a0->world, a0->contacts);
        a0->contacts = 0;
    }
    return r;
}

ASM_FUNC(func_001D35A8);

void HandleCountedColliderNotification(CountedCollider* self, s32 kind, ObjectMessage* msg)
{
    HandlePlacedObjectNotification(self, kind, msg);
    if (kind == 10) {
        CreatePooledContact(0.0f, self, (void*)msg->kind, &self->v140, (void*)&g_unitZVector, 10, 0, 0, &self->contacts);
    }
}
