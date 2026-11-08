// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 173/176 (98.3%), checked 2026-11-08
// NEAR (2026-11-08, night-gamec): three instructions: retail loads the state into v1 and 4 into v0, this the other way round; a case sharing the default gives retail's registers but adds a beqz
// In the context of its file, src/main/gauge_agent.cpp: its declarations before the function, bodies cut.
// Still differs (2026-11-08, night-close5): an if/else, `4 == state`, a state local and the default first leave state in v0 and 4 in v1.
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

void InitGaugeAgent(GaugeAgent* self);

void LoadGaugeAgent(GaugeAgent* self);

void StartGaugeAgent(GaugeAgent* self);

// A 0x70-byte hit func_00141D00 gives (collider_contact.cpp's MeshHit): its score at 0x40.
struct __attribute__((aligned(16))) HitCandidate { u8 pad0[0x40]; f32 score; u8 pad1[0x70 - 0x44]; };

s32 FindNearestHitObject(s32 a0, void* a1, void* a2, s32 a3, s32 a4, void* a5, f32 f);

typedef s32 (*VFn_18A830)(BaseObject* self, void* arg);
// What func_001DC238 hands its filter (IsGaugeAgentBlocker): the object hit at 0x50.
struct BlockerQuery { u8 pad[0x50]; BaseObject* sub; };

s32 IsGaugeAgentBlocker(void* self, BlockerQuery* rec);

typedef s32 (*Cb_18A910)(void* self, BlockerQuery* ctx);

void GatherCollidersInBox(void* a0, s32 a1, void* a2, void* a3, Cb_18A910 a4, void* a5, s32* a6, s32* a7);

s32 IsGaugeAgentLineBlocked(GaugeAgent* self, void* a1, void* a2);

typedef void* (*FnSelf_18A9A8)(void* self);
typedef s32 (*FnSub_18A9A8)(void* self);

// func_0018A9A8's locals: a point and the walker's current key.
struct LineCheckFrame {
    u8 buf[0x10];
    s32 code;
};

s32 HasGaugeAgentClearLine(GaugeAgent* self);

typedef s32 (*VFnI_0018AAE0)(void* self);

s32 IsGaugeAgentFree(GaugeAgent* self);

void EnterGaugeAgentState(GaugeAgent* self);

s32 ChooseGaugeAgentState(GaugeAgent* self);

void AdvanceGaugeAgentPhase(GaugeAgent* self);

void UpdateGaugeAgent(void);

void ShowGaugeAgentBar(GaugeAgent* self);

extern void* g_player;
void func_001C8418(void* self, void* p);
void GetObjectWorldPosition(void* obj, Vec02* out);
void UpdateAgentGoal(void* self);

void UpdateGaugeAgentGoal(GaugeAgent* self)
{
    switch (self->f724) {
    case 4:
        if (self->fE14 != 0) {
            Vec02 pos;
            GetObjectWorldPosition(self->fE14, &pos);
            func_001C8418(self, &pos);
        } else {
            s32 key;
            GetStateWalkerCurrentKey(self->fE10, &key);
            switch (key) {
            case 0x438:
            case 0x439:
                func_001C8418(self, (u8*)self + 0x140);
                break;
            default:
                func_001C8418(self, (u8*)g_player + 0x140);
                break;
            }
        }
        break;
    default:
        UpdateAgentGoal(self);
        break;
    }
}
