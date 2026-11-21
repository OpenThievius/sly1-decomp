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
#include "deferred_request.h"
#include "vu0.h"
#include "value_range.h"
#include "aim_blend_grid.h"
#include "camera.h"
#include "attachment.h"
#include "globals.h"
#include "ring_params.h"
#include "object_finder.h"
#include "functions/anim_record.h"
#include "functions/base_object.h"
#include "functions/blend_animation.h"
#include "functions/camera.h"
#include "functions/collider_span.h"
#include "functions/game_progress.h"
#include "functions/group_marker.h"
#include "functions/heap.h"
#include "functions/memory_card.h"
#include "functions/object_pool.h"
#include "functions/oscillator.h"
#include "functions/placed_object.h"
#include "functions/player_request.h"
#include "functions/screen_element.h"
#include "functions/state_walker.h"
#include "functions/warp_menu.h"
#include "functions/world.h"
#include "functions/world2_boss.h"
struct BaseObject;


// The methods of class 0x0C (0xE50 bytes, an agent): its links and clips, the search for the
// object it acts on, its states and the notifications it answers.

// The objects the gauge agent looks for (D_00264960, copied into fE24): an id, a float and
// the object found for the id.
struct GaugeTarget {
    s32 key;                // 0x00
    f32 f;                  // 0x04
    BaseObject* value;      // 0x08: FindFirstObjectById's result
};

ObjectLink g_world2BossLoadLinks[2] = { { 0, 0x82, 0xC24 }, { 0, 0x83, 0xC74 } };
ObjectLink g_world2BossStartLinks[3] = { { 1, 0x437, 0xE0C }, { 0, 0x440, 0xE18 }, { 0, 0x441, 0xE1C } };
s32 g_world2BossClipIds[4] = { 0x446, 0x447, 0x448, 0 };
GaugeTarget g_world2BossGaugeTargets[6] = {
    { 0x35, 50.0f, 0 }, { 0x36, 50.0f, 0 }, { 0x38, 80.0f, 0 },
    { 0x3B, 80.0f, 0 }, { 0x60, 70.0f, 0 }, { 0x50, 220.0f, 0 }
};

extern f32 g_gameTime;

void InitAgent(Agent* self);
void LoadAgent(Agent* self, void* reader);
struct BlendAnimationView;
struct PlayerBlendItem;
struct TurningCollider;
struct StateGraph;
void StartAgent(Agent* self);
void* ResolveAgentClip(Agent* self, s32 id);
void EnterAgentState(Agent* self, s32 evt, Animation* arg);
struct AgentNotification;
s32 GetAgentRosterState(Agent* self);
s32 ChooseAgentState(Agent* self);
void ChangeAgentState(Agent* self, s32 state, void* context);
void UpdateAgent(Agent* self, f32 dt);
void LeaveAgentState(Agent* self, s32 mode);
void HandleAgentNotification(Agent* self, s32 kind, AgentNotification* msg);

// Initialiser of the boss: an agent with its field at +0xE3C unset (-1).
void InitWorld2Boss(World2Boss* self)
{
	InitAgent(self);
	self->pendingWalkerTarget = -1;
}

// Loads the boss as an agent and resolves its two links.
void LoadWorld2Boss(World2Boss* self, void* reader)
{
    LoadAgent(self, reader);
    ResolveObjectLinks(self, 2, g_world2BossLoadLinks);
}

// Starts the boss agent: becomes the world's active follower, resolves its links, creates the
// six-entry blend and the state walker (starting at 0x438), looks up its three phase clips, and
// copies the table of six keyed objects, finding each by its id in the world.
void StartWorld2Boss(World2Boss* self)
{
    s32 n;
    s32 i;

    StartAgent(self);
    SetWorldActiveFollower(self->world, self);
    ResolveObjectLinks(self, 3, g_world2BossStartLinks);
    CreateSixEntryBlend(self, (PlayerBlendItem*)self->blendItems, &self->blendView);
    self->stateClips[12].obj = (void*)self->blendView;
    self->walker = CreateStateWalker((StateGraph*)self->walkerGraph, 0, 0x438, 0);
    for (n = 0; n < 3; n++)
        self->phaseClips[n] = ResolveAgentClip(self, g_world2BossClipIds[n]);
    self->keyedCount = 6;
    self->keyedObjects = (GaugeTarget*)CopyToFrontMemory(0x48, g_world2BossGaugeTargets);
    for (i = 0; i < self->keyedCount; i++) {
        GaugeTarget* e = ((GaugeTarget*)self->keyedObjects) + i;
        e->value = FindFirstObjectById(self->world, 1, e->key, self);
    }
}

extern f32 g_ringSevenPoints[14];

// DrawPlayerMarkerRing2's counterpart (player_request.cpp): the same block, built once as a
// function-local static with a brace initialiser (include/ring_params.h). DrawWorld2Boss queues
// it as a deferred request's callback, with the agent as the request's argument.
void DrawWorld2BossMarkerRing(DeferredRequest* request)
{
    World2Boss* agent = (World2Boss*)request->arg;
    static RingParams params = {
        1, 5.0f, 0.5f,
        {
            { { 0.0f, 0.0f, 0.0f }, 0.0f, 100.0f, RingColor(0x80FFFFFF) },
            { { 0.0f, 0.5f, 0.0f }, 0.0f, 50.0f, RingColor(0x80FFFFFF) },
            { { 75.0f, 1.0f, 0.0f }, 1.0f, -100.0f, RingColor(0x80FFFFFF) },
        },
    };
    AnimRecord* texture = FindAnimRecord(0x15D);
    params.textures[1] = texture;
    params.textures[0] = texture;
    DrawAngleSortedRing(&agent->v140, 7, (Point2*)g_ringSevenPoints, agent->keyedCount, (RingAnchor*)agent->keyedObjects, &params, request);
}

// The static's guard (D_002649A8) is written out with the function above, so the data below
// follows it.
s32 g_world2BossBlockerKinds[5] = { 4, 5, 60, 41, 76 };
f32 g_bossNearestHitRange = 1.5e+02f;
f32 D_002649C8 = 0.25f;
f32 D_002649D0[2] = { 0.0f, 0.25f };
s32 g_world2BossPhaseStates[4] = { 16, 16, 11, 0 };
s32 g_world2BossPhaseValues[6] = { 1083, 1085, 1087, 0, 0, 0 };
f32 g_bossNearCurve[4] = { 0.0f, 0.00125f, 0.0f, 0.0f };
f32 g_bossFarCurve[4] = { 0.0f, 0.0004f, 0.0f, 0.0f };
f32 D_00264A20[5] = { 1.3f, -0.2546479f, 0.0f, 0.0f, 0.1f };
f32 D_00264A34 = 20.0f;
f32 D_00264A38 = 20.0f;

// The record an agent's draw method is given: the point and the weights it measures against.
struct AgentDrawArgs {
    u8 pad00[0x40];
    Vec4 point;            // 0x40
    u8 pad50[0x80 - 0x50];
    Vec4 weights;          // 0x80
};

void DrawAgent(Agent* self, void* unused1, void* unused2);
extern "C" void* FillMemory(void* p, s32 value, s32 size);

// Draws the boss as an agent and, when it draws a ring, queues a deferred request (group 0xD,
// sorted by its distance along the view weights) for the marker ring.
void DrawWorld2Boss(World2Boss* self, AgentDrawArgs* args, void* arg2)
{
    DrawAgent(self, args, arg2);
    if (self->drawsRing) {
        DeferredRequest request;
        FillMemory(&request, 0, 0x80);
        request.group = 0xD;
        request.f04 = Vu0::ToFloatMoved(Vu0::Dot(Vu0::Sub(Vu0::Q(self->v140), Vu0::Q(args->point)), Vu0::Q(args->weights)));
        request.arg = self;
        request.callback = (void*)DrawWorld2BossMarkerRing;
        QueueDeferredRequest(&request);
    }
}

// A 0x70-byte hit func_00141D00 gives (collider_contact.cpp's MeshHit): its score at 0x40.
struct __attribute__((aligned(16))) HitCandidate { u8 pad0[0x40]; f32 score; u8 pad1[0x70 - 0x44]; };

// Tests the segment a1..a2 against each of the a3 colliders in the table a4 and gives back the one
// hit with the lowest score (0 if none), copying that hit's record to a5 if given. When bit 0 of a0
// is set, a first hit with a zero score is skipped in favour of the second.
s32 FindNearestHitObject(s32 a0, void* a1, void* a2, s32 a3, s32* a4, void* a5, f32 f)
{
    HitCandidate buf[2];
    s32* table = a4;
    s32 best = 0;
    f32 bestScore = 3.4028234663852886e+38f;
    s32 i;

    for (i = 0; i < a3; i++) {
        s32 self = table[i];
        s32 r = TestColliderSegmentHit((Collider*)self, a1, a2, f, 2, (ColliderSpan*)buf);
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
// What func_001DC238 hands its filter (IsWorld2BossBlocker): the object hit at 0x50.
struct BlockerQuery { u8 pad[0x50]; BaseObject* sub; };

// True when the object in the query would block the boss's line: it is not one of the five excluded
// kinds in a table, not of class id 3, not a kind-0x34 object that its own method says to ignore
// for the boss, and does not have object id 0x449 or 0x44A.
s32 IsWorld2BossBlocker(void* self, BlockerQuery* rec)
{
    s32* e = g_world2BossBlockerKinds;
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


// Whether something that IsWorld2BossBlocker accepts lies between points a1 and a2: gathers the
// colliders in the box and tests for a nearest hit along the line.
s32 IsWorld2BossLineBlocked(World2Boss* self, void* a1, void* a2)
{
    u8 buf[0x70];
    s32 x;
    s32* y;
    PushBackMemoryMark();
    GatherCollidersInBox(self->world, 0, (Vec4*)a1, (Vec4*)a2, (s32 (*)(void*, Collider*))IsWorld2BossBlocker, self, &x, (Collider***)&y);
    s32 r = FindNearestHitObject(0, a1, a2, x, y, buf, g_bossNearestHitRange);
    PopBackMemoryMark();
    return r != 0;
}


// func_0018A9A8's locals: a point and the walker's current key.
struct LineCheckFrame {
    u8 buf[0x10];
    s32 code;
};

// True when the boss may attack its target: not before the time stored at +0x748, and only if it
// has a target that is not marked in a way that excludes it. In the attack states 0x43A and 0x43C
// it needs a line to the target to be unblocked, now or to where the target will be a short time
// ahead; state 0x43E needs no check. Any other state gives 0.
s32 HasWorld2BossClearLine(World2Boss* self)
{
    LineCheckFrame loc;
    SwitchedCollider* sub;
    s32 code;

    if (g_gameTime < self->targetReadyTime) {
        return 0;
    }
    sub = (SwitchedCollider*)self->desc08()->m62(self);
    if (sub == 0) {
        return 0;
    }
    if (sub->desc->flags & 8) {
        if (sub->desc05()->m4D(sub)) {
            return 0;
        }
    }
    GetStateWalkerCurrentKey((StateWalker*)self->walker, &loc.code);
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
    if (IsWorld2BossLineBlocked(self, &self->v140, &sub->v140) != 0) {
        goto second;
    }
one:
    return 1;
second:
    ComputeObjectFrameAtTime((PlacedObject*)sub, 0, (Vec4*)loc.buf, 0, 0, 0, D_002649C8);
    if (IsWorld2BossLineBlocked(self, &self->v140, loc.buf) == 0) {
        goto one;
    }
    return 0;
}

typedef s32 (*VFnI_0018AAE0)(void* self);

// Whether the boss can take part in something: not while the pad select flag is held, it is
// flagged busy (fC10), in state 0xB or 0x10, or slot 0x66 of its descriptor says no, and only when
// its state walker is on key 0x43A, 0x43C or 0x43E.
s32 IsWorld2BossFree(World2Boss* self)
{
    s32 out;
    if (IsPadSelectFlagHeld(self->world) != 0) goto zero;
    if (self->busy != 0) goto zero;
    if (self->state == 0x10) goto zero;
    if (self->state == 0xB) goto zero;
    if (((VFnI_0018AAE0*)self->desc)[0x66](self) == 0) goto zero;
    GetStateWalkerCurrentKey((StateWalker*)self->walker, &out);
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

// State change of the boss: state 0xB marks level 2 done and starts a memory card save; state
// 0x10 re-enables contacts and counts one more hit left.
void EnterWorld2BossState(World2Boss* self, s32 evt, Animation* arg)
{
    EnterAgentState(self, evt, arg);
    s32 st = self->state;
    if (st != 0xB) {
        if (st == 0x10) {
            s32 n = self->hitsLeft;
            self->contactsDisabled = 0;
            self->hitsLeft = n + 1;
        }
    } else {
        MarkLevelDone(2);
        StartMemoryCardSave(&g_memoryCard);
    }
}

// Picks the boss's next state: 2 when it is in state 4 on walker key 0x438 and the roster state
// is 0, otherwise the common choice.
s32 ChooseWorld2BossState(World2Boss* self)
{
    if (self->state == 4) {
        s32 kind;
        GetStateWalkerCurrentKey((StateWalker*)self->walker, &kind);
        if (kind == 0x438) {
            if (GetAgentRosterState(self) == 0)
                return 2;
        }
    }
    return ChooseAgentState(self);
}

// Moves the boss on to its next phase: one less on the gauge count, a change to the phase's
// state with its clip, the walker token of that phase kept for later (applied when it leaves state
// 16), and the phase counter incremented.
void AdvanceWorld2BossPhase(World2Boss* self)
{
    DecrementGaugeCount((GaugeBar*)&g_gaugeBarElement);
    s32 idx = self->phase;
    ChangeAgentState(self, g_world2BossPhaseStates[idx], self->phaseClips[idx]);
    s32 n = self->phase;
    self->pendingWalkerTarget = g_world2BossPhaseValues[n];
    self->phase = n + 1;
}

void UpdateWorld2Boss(World2Boss* self, f32 dt)
{
    UpdateAgent(self, dt);
}

// Shows the shared gauge bar while the boss's state walker is on key 0x43A, 0x43C or 0x43E and
// nothing else covers the screen; hides it otherwise.
void ShowWorld2BossBar(World2Boss* self)
{
    s32 kind;
    GetStateWalkerCurrentKey((StateWalker*)self->walker, &kind);
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

void SetAgentGoalPoint(Agent* self, Vec4* p);
void UpdateAgentGoal(Agent* self, s32 flag);

// Sets the boss's goal point each update. In state 4 it chases the object it holds (fE14) when it
// has one, else the point its own state walker asks for: its own position in keys 0x438 and 0x439,
// the player's otherwise. Other states use the common agent goal.
void UpdateWorld2BossGoal(World2Boss* self, s32 flag)
{
    switch (self->state) {
    case 4:
        if (self->heldObject != 0) {
            Vec4 pos;
            GetObjectWorldPosition((BaseObject*)self->heldObject, &pos);
            SetAgentGoalPoint(self, &pos);
        } else {
            s32 key;
            GetStateWalkerCurrentKey((StateWalker*)self->walker, &key);
            switch (key) {
            case 0x438:
            case 0x439:
                SetAgentGoalPoint(self, &self->v140);
                break;
            default:
                SetAgentGoalPoint(self, &g_player->v140);
                break;
            }
        }
        break;
    default:
        UpdateAgentGoal(self, flag);
        break;
    }
}

#include "quadratic_curve.h"

extern ValueRange g_unitRange;
void UpdateAgentState(Agent* self);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
struct TurnBlendRecords;
struct BlendTimeScale;
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec4* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);
s32 IsAgentFacingBlocked(Agent* self);
void SetAgentFacingAngles(Agent* self, f32 x, f32 y);
typedef Agent* (*GaugeTargetFn)(World2Boss* self);

// Per-frame state update of the second world's boss after the generic agent update. In state 12
// (the paired attack animation) it sets the player blend weights from the target distance and the
// turn since the heading, and plays sound 0x1CC (with a camera timestamp) each time one of its two
// blended clips leaves its cyclic range. In state 14 it aims at where the target will be.
void UpdateWorld2BossState(World2Boss* self)
{
    typedef Vu0::Vec Vec;
    UpdateAgentState(self);
    switch (self->state) {
    case 12: {
        if (self->statePlayer == 0) {
            break;
        }
        if (g_player != 0 && g_player->animSeekValue != 0) {
            return;
        }
        Agent* tgt = (Agent*)self->desc08()->m62(self);
        f32 weight;
        if (tgt != 0) {
            f32 dist = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Sub(Vec::Of(self->v140), Vec::Of(tgt->v140)).q,
                                                        Vu0::Sub(Vec::Of(self->v140), Vec::Of(tgt->v140)).q)));
            f32 near = g_unitRange.Limit(((QuadraticCurve*)g_bossNearCurve)->Eval(dist));
            f32 far = g_unitRange.Limit(((QuadraticCurve*)g_bossFarCurve)->Eval(dist));
            f32 level;
            GetWorld2BossLevelFactor(self, &level);
            weight = level * far + (1.0f - level) * near;
        } else {
            weight = 1.0f;
        }
        f32 heading = ArctangentOfRatio(self->m110.r[0].y, self->m110.r[0].x);
        f32 turn = __builtin_fabsf(WrapAngle(heading - self->heading));
        f32 k = g_unitRange.Clamp(((QuadraticCurve*)D_00264A20)->Eval(turn));
        SetPlayerBlendWeights(self->heading, weight * k, self, (TurnBlendRecords*)self->blendItems, self->blendView);
        // One mover and one sequence variable for both objects: set twice, they are left to
        // global-alloc, which gives retail's v0 and a0 (docs/TOOLCHAIN.md, local-alloc).
        PoseSource* m;
        CyclicRanges* a;
        m = ((BlendSourceEntry*)FindEntryByObjectId(self->blendView, (BaseObject*)self->linkPartA))->mover;
        a = m->ranges;
        s32 offFirst = FindCyclicRangeIndex(self->statePlayer->time, self->blendView->blendedDuration, a->count, (BlendTimeScale*)a->pairs, 0) == 0;
        m = ((BlendSourceEntry*)FindEntryByObjectId(self->blendView, (BaseObject*)self->linkPartB))->mover;
        a = m->ranges;
        s32 offSecond = FindCyclicRangeIndex(self->statePlayer->time, self->blendView->blendedDuration, a->count, (BlendTimeScale*)a->pairs, 0) == 0;
        if (offFirst && self->firstInRange == 0) {
            RecordCameraTimestamp(g_camera);
            StartSoundEffect(0x1CC, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
        if (offSecond && self->secondInRange == 0) {
            RecordCameraTimestamp(g_camera);
            StartSoundEffect(0x1CC, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
        self->firstInRange = offFirst;
        self->secondInRange = offSecond;
        break;
    }
    case 14: {
        if (IsAgentFacingBlocked(self)) {
            return;
        }
        Vec4 to;
        Vec4 curve = { 0.0f, 0.00016666666f, 0.0f, 0.0f };
        f32 level;
        GetWorld2BossLevelFactor(self, &level);
        f32 rest = 1.0f - level;
        f32 limit = (1.0f - rest) * D_002649D0[0] + rest * D_002649D0[1];
        Agent* tgt = (Agent*)self->desc08()->m62(self);
        if (tgt != 0) {
            f32 dist = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(Vu0::Sub(Vec::Of(tgt->v140), Vec::Of(self->v140)).q,
                                                        Vu0::Sub(Vec::Of(tgt->v140), Vec::Of(self->v140)).q)));
            f32 t = g_unitRange.Clamp(((QuadraticCurve*)&curve)->Eval(dist));
            ComputeObjectFrameAtTime(tgt, 0, &self->launchPoint, 0, 0, 0, t <? limit);
            Vu0::Q(to) = Vu0::Sub(Vec::Of(self->launchPoint), Vec::Of(self->v140)).q;
            SetAgentFacingAngles(self, ArctangentOfRatio(to.y, to.x), 0.0f);
        }
        break;
    }
    }
}

// When leaving state 16, hands the stored walker token (if any) to the state walker as its
// target and clears it; the common leave runs first.
void LeaveWorld2BossState(World2Boss* self, s32 mode)
{
    LeaveAgentState(self, mode);
    if (self->state == 16) {
        s32 token = self->pendingWalkerTarget;
        if (token == -1) return;
        SetStateWalkerTarget((StateWalker*)self->walker, token);
        self->pendingWalkerTarget = -1;
    }
}

// Handles the boss's notifications. From its state player it reacts to code 0x442 or 0x443 by
// placing the matching pool object at the launch point (raised or lowered by a constant, by the
// current attack state) and launching it, and to 0x444 and 0x445 by switching the ring draw flag on
// and off. Everything else goes to the generic agent handler.
void HandleWorld2BossNotification(World2Boss* self, s32 a1, MessageBody* key)
{
    if (a1 == 0x13 && key->sourceId == (s32)self->statePlayer) {
        switch (key->code) {
        case 0x442:
        case 0x443: {
            ObjectPool* obj;
            if (key->code == 0x442) {
                obj = (ObjectPool*)self->firstPool;
            } else {
                obj = (ObjectPool*)self->secondPool;
            }
            s32 kind;
            GetStateWalkerCurrentKey((StateWalker*)self->walker, &kind);
            switch (kind) {
            case 0x43A:
            case 0x43C:
                obj->fF0 = (*(Quad16*)&self->launchPoint);
                obj->posF0[2] = self->v140.z + D_00264A34;
                break;
            case 0x43E:
                obj->fF0 = (*(Quad16*)&self->launchPoint);
                obj->posF0[2] = obj->posF0[2] + D_00264A38;
                break;
            }
            LaunchChosenPoolObject(obj, 1);
            return;
        }
        case 0x444:
            self->drawsRing = 1;
            break;
        case 0x445:
            self->drawsRing = 0;
            break;
        }
    }
    HandleAgentNotification(self, a1, (AgentNotification*)key);
}

// Hoisting 1.0f into a local `one` matched the constant scheduling.
void GetWorld2BossLevelFactor(World2Boss* a0, f32* a1)
{
    s32 kind;
    GetStateWalkerCurrentKey((StateWalker*)a0->walker, &kind);
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
