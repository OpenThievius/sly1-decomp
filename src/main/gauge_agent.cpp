// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "object_pool.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "memory_card.h"
#include "game_progress.h"
#include "screen_element.h"
#include "object_link.h"
#include "message_body.h"
#include "shapes.h"

// The methods of class 0x0C (0xE50 bytes, an agent): its links and clips, the search for the
// object it acts on, its states and the notifications it answers.

// The objects the gauge agent looks for (D_00264960, copied into fE24): an id, a float and
// the object found for the id.
struct GaugeTarget {
    s32 key;                // 0x00
    f32 f;                  // 0x04
    s32 value;              // 0x08: FindFirstObjectById's result
};

ObjectLink D_00264910[2] = { { 0, 0x82, 0xC24 }, { 0, 0x83, 0xC74 } };
ObjectLink D_00264928[3] = { { 1, 0x437, 0xE0C }, { 0, 0x440, 0xE18 }, { 0, 0x441, 0xE1C } };
s32 D_00264950[4] = { 0x446, 0x447, 0x448, 0 };
GaugeTarget D_00264960[6] = {
    { 0x35, 50.0f, 0 }, { 0x36, 50.0f, 0 }, { 0x38, 80.0f, 0 },
    { 0x3B, 80.0f, 0 }, { 0x60, 70.0f, 0 }, { 0x50, 220.0f, 0 }
};
s32 D_002649A8 = 0;
s32 D_002649B0[5] = { 4, 5, 60, 41, 76 };
f32 D_002649C4 = 1.5e+02f;
f32 D_002649C8 = 0.25f;
f32 D_002649D0[2] = { 0.0f, 0.25f };
s32 D_002649D8[4] = { 16, 16, 11, 0 };
s32 D_002649E8[6] = { 1083, 1085, 1087, 0, 0, 0 };
f32 D_00264A00[4] = { 0.0f, 0.00125f, 0.0f, 0.0f };
f32 D_00264A10[4] = { 0.0f, 0.0004f, 0.0f, 0.0f };
f32 D_00264A20[5] = { 1.3f, -0.2546479f, 0.0f, 0.0f, 0.1f };
f32 D_00264A34 = 20.0f;
f32 D_00264A38 = 20.0f;

extern f32 g_gameTime;

void InitAgent(void*);
void LoadAgent(void*);
void ResolveObjectLinks(void* self, s32 n, void* table);
void StartAgent(void* self);
void SetWorldActiveFollower(void* sub, void* self);
void CreateSixEntryBlend(void* self, void* a, void* b);
void* CreateStateWalker(void* a, void* b, s32 c, s32 d);
s32 ResolveAgentClip(void* self, s32 id);
u8* CopyToFrontMemory(s32 size, void* src);
s32 FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);
s32 TestColliderSegmentHit(void* self, void* p1, void* p2, f32 x, s32 p3, void* p4);
s32 IsObjectOfKind(BaseObject* a, s32 b);
s32 MatchesObjectId(BaseObject* a, s32 b);
void PushBackMemoryMark(void* self, void* a1, void* a2);
void PopBackMemoryMark(void);
void ComputeObjectFrameAtTime(void* a, s32 b, void* c, s32 d, s32 e, s32 f, f32 g);
void GetStateWalkerCurrentKey(void* dev, s32* out);
s32 IsPadSelectFlagHeld(void* p);
void EnterAgentState(void* self);
void MarkLevelDone(s32 n);
void StartMemoryCardSave(MemoryCard* p);
s32 GetAgentRosterState(void* self);
s32 ChooseAgentState(void* self);
void DecrementGaugeCount(void* p);
void ChangeAgentState(void* node, s32 kind, s32 flag);
void UpdateAgent(void);
s32 AreMenusAndFadeClear(void);
void LeaveAgentState(void*);
void SetStateWalkerTarget(s32, s32);
s32 func_001A8C90(void* obj, s32 v);
void HandleAgentNotification(void* self, s32 code, void* req);

void InitGaugeAgent(GaugeAgent* self)
{
	InitAgent(self);
	*(s32*)((char*)self + 0xE3C) = -1;
}

void LoadGaugeAgent(GaugeAgent* self)
{
    LoadAgent(self);
    ResolveObjectLinks(self, 2, D_00264910);
}

void StartGaugeAgent(GaugeAgent* self)
{
    s32 n;
    s32 i;

    StartAgent(self);
    SetWorldActiveFollower(self->world, self);
    ResolveObjectLinks(self, 3, D_00264928);
    CreateSixEntryBlend(self, (u8*)self + 0xC20, (u8*)self + 0xE00);
    self->f758[12].obj = (void*)self->fE00;
    self->fE10 = CreateStateWalker(self->fE0C, 0, 0x438, 0);
    for (n = 0; n < 3; n++)
        self->fE30[n] = ResolveAgentClip(self, D_00264950[n]);
    self->fE20 = 6;
    self->fE24 = (GaugeTarget*)CopyToFrontMemory(0x48, D_00264960);
    for (i = 0; i < self->fE20; i++) {
        GaugeTarget* e = ((GaugeTarget*)self->fE24) + i;
        e->value = FindFirstObjectById(self->world, 1, e->key, self);
    }
}

INCLUDE_ASM(func_0018A510);

INCLUDE_ASM(func_0018A628);

// A 0x70-byte hit func_00141D00 gives (collider_contact.cpp's MeshHit): its score at 0x40.
struct __attribute__((aligned(16))) HitCandidate { u8 pad0[0x40]; f32 score; u8 pad1[0x70 - 0x44]; };

s32 FindNearestHitObject(s32 a0, void* a1, void* a2, s32 a3, s32 a4, void* a5, f32 f)
{
    HitCandidate buf[2];
    s32* table = (s32*)a4;
    s32 best = 0;
    f32 bestScore = 3.4028234663852886e+38f;
    s32 i;

    for (i = 0; i < a3; i++) {
        s32 self = table[i];
        s32 r = TestColliderSegmentHit((void*)self, a1, a2, f, 2, (void*)buf);
        s32 k = 0;
        if (r > 0) {
            if (buf[0].score == 0.0f && (a0 & 1)) {
                k = 1;
            }
        }
        if (k < r) {
            HitCandidate* c = &buf[k];
            if (c->score < bestScore) {
                bestScore = c->score;
                best = self;
                if (a5 != 0) {
                    *(HitCandidate*)a5 = *c;
                }
            }
        }
    }
    return best;
}

typedef s32 (*VFn_18A830)(BaseObject* self, void* arg);
// What func_001DC238 hands its filter (IsGaugeAgentBlocker): the object hit at 0x50.
struct BlockerQuery { u8 pad[0x50]; BaseObject* sub; };

s32 IsGaugeAgentBlocker(void* self, BlockerQuery* rec)
{
    s32* e = D_002649B0;
    u32 i;
    for (i = 0; i < 5; e++, i++) {
        if (IsObjectOfKind(rec->sub, *e) != 0) {
            break;
        }
    }
    if (i < 5) {
        return 0;
    }
    if (rec->sub->desc->id == 3) {
        return 0;
    }
    if (IsObjectOfKind(rec->sub, 0x34) != 0) {
        if (((VFn_18A830*)rec->sub->desc)[60](rec->sub, self) == 0) {
            return 0;
        }
    }
    if (MatchesObjectId(rec->sub, 0x449) != 0 || MatchesObjectId(rec->sub, 0x44A) != 0) {
        return 0;
    }
    return 1;
}

typedef s32 (*Cb_18A910)(void* self, BlockerQuery* ctx);

void GatherCollidersInBox(void* a0, s32 a1, void* a2, void* a3, Cb_18A910 a4, void* a5, s32* a6, s32* a7);

s32 IsGaugeAgentLineBlocked(GaugeAgent* self, void* a1, void* a2)
{
    u8 buf[0x70];
    s32 x;
    s32 y;
    PushBackMemoryMark(self, a1, a2);
    GatherCollidersInBox(self->world, 0, a1, a2, IsGaugeAgentBlocker, self, &x, &y);
    s32 r = FindNearestHitObject(0, a1, a2, x, y, buf, D_002649C4);
    PopBackMemoryMark();
    return r != 0;
}

typedef void* (*FnSelf_18A9A8)(void* self);
typedef s32 (*FnSub_18A9A8)(void* self);

// func_0018A9A8's locals: a point and the walker's current key.
struct LineCheckFrame {
    u8 buf[0x10];
    s32 code;
};

s32 HasGaugeAgentClearLine(GaugeAgent* self)
{
    u8* obj = (u8*)self;
    LineCheckFrame loc;
    void* sub;
    s32 code;

    if (g_gameTime < *(f32*)(obj + 0x748)) {
        return 0;
    }
    sub = ((FnSelf_18A9A8)(*(void***)obj)[0x198 / 4])(obj);
    if (sub == 0) {
        return 0;
    }
    if (*(u32*)((u8*)*(void**)sub + 8) & 8) {
        if (((FnSub_18A9A8)(*(void***)sub)[0x144 / 4])(sub)) {
            return 0;
        }
    }
    GetStateWalkerCurrentKey(*(void**)(obj + 0xE10), &loc.code);
    code = loc.code;
    if (code != 0x43C) {
        if (code < 0x43D) {
            if (code != 0x43A) {
                return 0;
            }
        } else {
            if (code == 0x43E) {
                goto one;
            }
            return 0;
        }
    }
    if (IsGaugeAgentLineBlocked((GaugeAgent*)obj, obj + 0x140, (u8*)sub + 0x140) != 0) {
        goto second;
    }
one:
    return 1;
second:
    ComputeObjectFrameAtTime(sub, 0, loc.buf, 0, 0, 0, D_002649C8);
    if (IsGaugeAgentLineBlocked((GaugeAgent*)obj, obj + 0x140, loc.buf) == 0) {
        goto one;
    }
    return 0;
}

typedef s32 (*VFnI_0018AAE0)(void* self);

s32 IsGaugeAgentFree(GaugeAgent* self)
{
    s32 out;
    if (IsPadSelectFlagHeld(self->world) != 0) goto zero;
    if (self->fC10 != 0) goto zero;
    if (self->f724 == 0x10) goto zero;
    if (self->f724 == 0xB) goto zero;
    if (((VFnI_0018AAE0*)self->desc)[0x66](self) == 0) goto zero;
    GetStateWalkerCurrentKey(self->fE10, &out);
    if (out == 0x43C) goto one;
    if (out < 0x43D) {
        if (out == 0x43A) goto one;
        goto zero;
    }
    if (out == 0x43E) goto one;
zero:
    return 0;
one:
    return 1;
}

void EnterGaugeAgentState(GaugeAgent* self)
{
    EnterAgentState(self);
    s32 st = self->f724;
    if (st != 0xB) {
        if (st == 0x10) {
            s32 n = self->fA68;
            self->fC04 = 0;
            self->fA68 = n + 1;
        }
    } else {
        MarkLevelDone(2);
        StartMemoryCardSave(&g_memoryCard);
    }
}

s32 ChooseGaugeAgentState(GaugeAgent* self)
{
    if (self->f724 == 4) {
        s32 kind;
        GetStateWalkerCurrentKey(self->fE10, &kind);
        if (kind == 0x438) {
            if (GetAgentRosterState(self) == 0)
                return 2;
        }
    }
    return ChooseAgentState(self);
}

void AdvanceGaugeAgentPhase(GaugeAgent* self)
{
    DecrementGaugeCount((u8*)&g_gaugeBarElement);
    s32 idx = self->fE28;
    ChangeAgentState(self, D_002649D8[idx], self->fE30[idx]);
    s32 n = self->fE28;
    self->fE3C = D_002649E8[n];
    self->fE28 = n + 1;
}

void UpdateGaugeAgent(void)
{
    UpdateAgent();
}

void ShowGaugeAgentBar(GaugeAgent* self)
{
    s32 kind;
    GetStateWalkerCurrentKey(self->fE10, &kind);
    s32 pick = 0;
    switch (kind) {
    case 0x43A:
    case 0x43C:
    case 0x43E:
        pick = AreMenusAndFadeClear();
        break;
    default:
        break;
    }
    if (pick)
        g_gaugeBarElement.vt->m14(&g_gaugeBarElement);
    else
        g_gaugeBarElement.vt->m15(&g_gaugeBarElement);
}

INCLUDE_ASM(func_0018AD88);

INCLUDE_ASM(func_0018AE38);

void LeaveGaugeAgentState(GaugeAgent* self)
{
    LeaveAgentState(self);
    if (self->f724 == 16) {
        s32 token = self->fE3C;
        if (token == -1) return;
        SetStateWalkerTarget((s32)self->fE10, token);
        self->fE3C = -1;
    }
}

void HandleGaugeAgentNotification(GaugeAgent* self, s32 a1, MessageBody* key)
{
    if (a1 == 0x13 && key->sourceId == (s32)self->f7E0) {
        switch (key->code) {
        case 0x442:
        case 0x443: {
            ObjectPool* obj;
            if (key->code == 0x442) {
                obj = (ObjectPool*)self->fE18;
            } else {
                obj = (ObjectPool*)self->fE1C;
            }
            s32 kind;
            GetStateWalkerCurrentKey(self->fE10, &kind);
            switch (kind) {
            case 0x43A:
            case 0x43C:
                obj->fF0 = (*(Quad16*)&self->vE40);
                obj->posF0[2] = self->v140.z + D_00264A34;
                break;
            case 0x43E:
                obj->fF0 = (*(Quad16*)&self->vE40);
                obj->posF0[2] = obj->posF0[2] + D_00264A38;
                break;
            }
            func_001A8C90(obj, 1);
            return;
        }
        case 0x444:
            self->fE2C = 1;
            break;
        case 0x445:
            self->fE2C = 0;
            break;
        }
    }
    HandleAgentNotification(self, a1, key);
}

// Hoisting 1.0f into a local `one` matched the constant scheduling.
void GetGaugeAgentLevelFactor(GaugeAgent* a0, f32* a1)
{
    s32 kind;
    GetStateWalkerCurrentKey(a0->fE10, &kind);
    switch (kind) {
    case 0x43A:
        {
            f32 v = g_currentEntry->dt * 1.3f - 0.3f;
            f32 one = 1.0f;
            if (v < 0.0f) {
                v = 0.0f;
            } else if (one < v) {
                v = one;
            }
            *a1 = v;
        }
        break;
    case 0x43C:
        {
            f32 v = g_currentEntry->dt * 1.3f - 0.3f;
            f32 one = 1.0f;
            if (v < 0.0f) {
                v = 0.0f;
            } else if (one < v) {
                v = one;
            }
            *a1 = v;
        }
        break;
    default:
        *a1 = g_currentEntry->dt * g_currentEntry->dt;
        break;
    }
}
