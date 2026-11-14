// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x16CE00 to 0x16E0B8: the target follower (class 0x47, include/target_follower.h),
// the entry-table object (0x64) and the followable object (0x2A) that tells it what to follow.
// Its name is ours, after the follower that most of its code serves.
#include "common.h"
#include "switched_collider.h"
#include "c52.h"
#include "entry_table_object.h"
#include "zone_collider.h"
#include "target_follower.h"
#include "globals.h"
#include "game_clock.h"
#include "key_record.h"
#include "base_object.h"
#include "placed_object.h"
#include "world.h"
#include "game_progress.h"
#include "shapes.h"
#include "asm_func.h"
#include "vu0.h"
#include "object_finder.h"
#include "functions/collider.h"
#include "functions/matrix.h"
#include "functions/object_pool.h"
#include "functions/oscillator.h"
#include "functions/placed_object.h"
#include "functions/point_graph.h"
#include "functions/pooled_object.h"
#include "functions/sound_system.h"
#include "functions/state_walker.h"
#include "functions/warp_menu.h"
struct BufferedStream;

// Types other files define, named by the parameters of their functions declared here.
struct ObjectLink;

// The target follower (class 0x47), the entry-table object (0x64) and the followable object
// (0x2A). Its .data runs from 0x2629C8 to 0x262A30: the current follower, the two link tables of
// class 0x47 and the two floats func_0016D490 reads. Its .rodata, from 0x24A7F0, is the jump
// tables and FLT_MAX literals of its VU0 functions.

TargetFollower* g_currentTargetFollower = 0;
s32 g_targetFollowerLoadLinks[16] = { 0x0, 0x2EE, 0x550, 0x0, 0x2F8, 0x57C, 0x0, 0x2F9, 0x580, 0x0, 0x2FB, 0x588, 0x0, 0x2FC, 0x58C, 0x0 };
s32 g_targetFollowerResolveLinks[6] = { 0x0, 0x2FA, 0x584, 0x0, 0x2F7, 0x568 };
f32 D_00262A28[2] = { 1.25f, 1.5f };

struct StateGraph;

extern TargetFollower* g_currentTargetFollower;

// Initialises the collider and sets the follower's defaults (no followed id, no mode, 3000 and
// 1000 for f5C4 and f5C8, its tune values) and clears the current target follower.
void InitTargetFollower(TargetFollower* self)
{
    InitCollider(self);
    self->followedObjectId = -1;
    self->mode = -1;
    self->f5C4 = 3000.0f;
    self->f5C8 = 1000.0f;
    SetListLinkOffset(&self->list55C, 0x7B0);
    Tune47* q = &self->tune5B0;
    q->a = 25.0f;
    q->c = 0.25f;
    q->b = 0;
    g_currentTargetFollower = 0;
}

// Loads a target follower: the collider data, its links, and a scan of the state graph's
// transitions for the one between keys 0x2EF and 0x2F0.
void LoadTargetFollowerRecords(TargetFollower* self, BufferedStream* stream)
{
    s32 k1 = 0x2EF;
    s32 k2 = 0x2F0;
    s32 i = 0;
    s32 off = 0;
    LoadCollider(self, stream);
    ResolveObjectLinks(self, 5, (ObjectLink*)g_targetFollowerLoadLinks);
    for (;;) {
        if (i >= self->list550->count) {
            return;
        }
        // address arithmetic over a variable index
        Entry47* e = (Entry47*)((u8*)self->list550->items + off);
        if (GetStateEntryKey((StateGraph*)self->list550, e->a) == k1 && GetStateEntryKey((StateGraph*)self->list550, e->b) == k2) {
            break;
        }
        off += 0x14;
        i++;
    }
    if (i < self->list550->count) {
        // address arithmetic over a variable index
        Entry47* p = (Entry47*)((u8*)(i * 0x14) + (s32)self->list550->items);
        self->leadTime = p->ref->f34;
    }
}

void FollowObjectById(TargetFollower* self, s32 x);
void* CreateTypedRecord(s32 index, void* a1, BaseObject* a2, s32 a3, s32 a4);

// Starts the placed object and resolves its links: creates its state walker, finds the launch
// pool, works out the height offset of the follower above its anchor, and follows the object with
// the saved id if there is one.
void ResolveTargetFollowerLinks(TargetFollower* self)
{
    f32 scratch[4];

    StartPlacedObject(self);
    ResolveObjectLinks(self, 2, (ObjectLink*)g_targetFollowerResolveLinks);
    self->stateWalker = CreateStateWalker((StateGraph*)self->list550, self, -1, 1);
    self->launchPool = (Sub47*)FindFirstObjectByIdGathered(self->world, 1, 0x8C, self);
    ConvertPositionToWorld((BaseObject*)self->f568, (Vec02*)scratch);
    self->heightOffset = self->v140.z - scratch[2];
    if (self->followedObjectId != -1)
    {
        FollowObjectById(self, self->followedObjectId);
    }
    u64 m = 0x8000;
    s32 sh = 27;
    m <<= sh;
    self->flags538 |= m;
    self->trailObject = CreateTypedRecord(0x73, g_currentWorld, 0, 0x302, -1);
}

void SetFollowedObject(TargetFollower* self, FollowableObject* x);
void PlaceTargetFollowerOnFollowed(TargetFollower* self);
void SetTargetFollowerMode(TargetFollower* self, s32 mode);

// Remembers the id, finds that object and, if it exists, follows it and puts the follower on it,
// into mode 2 when the object has a tune object and mode 4 when it has none.
void FollowObjectById(TargetFollower* self, s32 x)
{
    self->followedObjectId = x;
    FollowableObject* p = (FollowableObject*)FindFirstObjectByIdMode4(self->world, x, self);
    if (p != 0) {
        SetFollowedObject(self, p);
        PlaceTargetFollowerOnFollowed(self);
        if (p->tuneObject != 0) {
            SetTargetFollowerMode(self, 2);
        } else {
            SetTargetFollowerMode(self, 4);
        }
    }
}

extern "C" void* FillMemory(void* p, s32 value, s32 size);


// Steps the collider and, unless stepping is halted, turns the collider toward a rotation about
// the up axis by the follower's heading.
void StepTargetFollower(TargetFollower* self, f32 t)
{
    Mat3U buf;

    StepCollider(self, t);
    if (self->stepHalted != 0) {
        return;
    }
    BuildAxisAngleMatrix(&g_unitZVector, (Mat02*)&buf, self->heading);
    TurnColliderTowardRotation((Collider*)self, t, (Mat02*)&buf, (f32*)self->sub5B0);
}

void PlayPendingFollowerSound(TargetFollower* self);
s32 ChooseTargetFollowerMode(TargetFollower* self);
void SetTargetFollowerMode(TargetFollower* self, s32 mode);
Collider* GetActiveSwitchedCollider(void);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

// Per-frame update: updates the collider and any pending sound; only the current target follower
// goes on, changing mode until the chosen mode is stable and, in modes 2 and 4, turning its
// heading toward the active switched collider.
void UpdateTargetFollower(TargetFollower* self, f32 dt)
{
    UpdateCollider(self, dt);
    PlayPendingFollowerSound(self);
    if (self != g_currentTargetFollower) {
        return;
    }
    s32 mode;
    while ((mode = ChooseTargetFollowerMode(self)) != self->mode) {
        SetTargetFollowerMode(self, mode);
    }
    switch (mode) {
    case 0:
    case 1:
    case 3:
        break;
    case 2:
    case 4:
        Collider* other = GetActiveSwitchedCollider();
        if (other == 0) {
            return;
        }
        Vec02 d;
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(other->v140), Vu0::Q(self->v140));
        self->heading = ArctangentOfRatio(d.y, d.x);
        break;
    }
}

extern f32 g_gameTime;
typedef s32 (*VFnRet_16D1E0)(void* self);
void* ChooseEntryTableObject(EntryTableObject* self);

// Chooses the follower's next mode from the current one: in modes 2 and 4 it compares the next
// entry of its followed list with the current followed object (mode 4 when there is none or it
// shares the anchor without tuning, else 2), and the other modes test their own exit conditions.
s32 ChooseTargetFollowerMode(TargetFollower* self)
{
    FollowableObject* next;
    Collider* c;
    s32 mode = self->mode;
    switch (mode) {
    case 2:
    case 4: {
        next = (FollowableObject*)self->list55C.tail;
        if (next != self->followedObject) {
            if (next == 0) {
                mode = 4;
            } else if (self->followedObject != 0 && next->anchor == self->followedObject->anchor) {
                mode = 4;
                if (next->tuneObject != 0) {
                    mode = 2;
                }
            } else {
                Vec02 v;
                ConvertPositionToWorld((BaseObject*)next->anchor, (Vec02*)&v);
                u128 d = Vu0::Sub(Vu0::Q(v), Vu0::Q(self->v140));
                f32 len = Vu0::ToFloat(Vu0::Sqrt(Vu0::DotXY(d, d)));
                if (len < 5.0f) {
                    mode = 4;
                    if (next->tuneObject != 0) {
                        mode = 2;
                    }
                } else {
                    mode = 0;
                }
            }
            SetFollowedObject(self, next);
        }
        next = (FollowableObject*)GetActiveSwitchedCollider();
        c = (Collider*)next;
        if (c != 0 && c == (Collider*)g_player) {
            if (((VFnRet_16D1E0*)c->desc)[81](c) == 0) {
                if (mode == 4 && self->followedObject != 0) {
                    if (self->followedObject->tuneObject != 0) {
                        mode = 2;
                    }
                }
            } else if (mode == 2) {
                mode = 4;
            }
        }
        if (c != 0 && mode == 2 && self->nextLaunchTime < g_gameTime) {
            if (self->launchPool == 0) {
                goto end;
            }
            if (HasObjectPoolChoice((ObjectPool*)self->launchPool) != 0) {
                void* t = ChooseEntryTableObject((EntryTableObject*)self->followedObject->tuneObject);
                if (t != 0) {
                    self->lookTarget = t;
                    mode = 3;
                    break;
                }
            }
        }
        break;
    }
    case 1:
        if (self->arrivalTime <= g_gameTime) {
            mode = 4;
            if (self->followedObject->tuneObject != 0) {
                mode = 2;
            }
        }
        break;
    case 0:
        if (self->phaseOneEndTime <= g_gameTime) {
            mode = 1;
        }
        break;
    case 3:
    default:
        break;
    }
    return mode;
end:;
}

extern s32 g_padSelectFlags;

extern s32 g_padSelectFlags;

extern "C" void* FillMemory(void* p, s32 value, s32 size);

struct Item_16D3F0 { u8 pad0[0x318]; s32 f318; };


// Makes x the followed object (nothing if it is already); when its tune object differs it records
// it and sets the trail countdown to 3, and passes the tune's value to the launch pool.
void SetFollowedObject(TargetFollower* self, FollowableObject* x)
{
    if (x == self->followedObject) {
        return;
    }
    void* v = 0;
    if (x != 0) {
        v = x->tuneObject;
    }
    if (v != self->lastTune) {
        self->lastTune = v;
        self->trailCountdown = 3;
    }
    self->followedObject = x;
    if (v != 0) {
        self->launchPool->f44 = ((Item_16D3F0*)x->tuneObject)->f318;
        ChooseObjectPoolItem((ObjectPool*)self->launchPool);
        if (self->soundLevel != 0) {
            return;
        }
        self->soundLevel = PushSoundLevel(0x6B);
    } else {
        if (self->soundLevel != 0) {
            RemoveSoundLevelAndRecompute(self->soundLevel);
            self->soundLevel = 0;
        }
    }
}

extern f32 g_gameTime;
extern const Vec02 g_unitZVector;

struct FollowPoseA {
    u8 pad00[0x50];
    Vec02 v50;              // 0x50
    u8 pad60[0x78 - 0x60];
    f32 life;               // 0x78: how long the launched item lives
    u8 pad7C[0x80 - 0x7C];
};

struct FollowPoseB {
    u8 pad00[0x10];
    Vec02 v10;              // 0x10
};

struct ChaseObject;

struct FollowObject {
    u8 pad00[0x48];
    ChaseObject* f48;       // 0x48
    u8 pad4C[0x60 - 0x4C];
    FollowPoseA poseA;      // 0x60: the record the placement is read from; its v50 is the velocity at 0xB0
    FollowPoseB poseB;      // 0xE0
};

struct ChaseObject {
    u8 pad00[0x350];
    Vec02 gravity;          // 0x350
    u8 pad360[0x690 - 0x360];
    f32 f690;               // 0x690
    u8 pad694[0x6F0 - 0x694];
    f32 f6F0;               // 0x6F0
    f32 f6F4;               // 0x6F4
    u8 pad6F8[0x700 - 0x6F8];
    Vec02 v700;             // 0x700
};

struct FollowTune {
    u8 pad00[0x31C];
    f32 launchInterval;     // 0x31C: the delay before the next launch
    f32 flightTime;         // 0x320: how long a launched item takes to reach the target
    f32 f324;               // 0x324
    f32 f328;               // 0x328
    f32 launchAngle;        // 0x32C: the angle of a ballistic launch
    f32 launchSpeed;        // 0x330: the speed along Z given to the launched object
    f32 f334;               // 0x334
};

struct PlacementRecord;

// Launches the item of the follower's pool at the object it looks at: takes the item's current
// chase target and pose, and when that target is of class 0x3D (or otherwise) computes a launch
// velocity from the follower's tuning toward the look target's position and gives it to the item.
void LaunchPoolItemAtTarget(TargetFollower* self)
{
    Vec02 a;
    Vec02 b;
    Mat02 c;
    GetObjectWorldPosition((BaseObject*)self->lookTarget, &a);
    FollowObject* obj = (FollowObject*)self->launchPool;
    ChaseObject* t = obj->f48;
    FollowPoseA* sa = &obj->poseA;
    FollowPoseB* sb = &obj->poseB;
    if (t == 0) {
        return;
    }
    GetPlacementRecordTransform((PlacementRecord*)sa, &b, c.r, 0);
    FollowTune* tune = (FollowTune*)self->followedObject->tuneObject;
    if (IsObjectOfKind((BaseObject*)t, 0x3D) != 0) {
        Vec02 dir;
        const Vec02* fb = &g_unitXVector;
        Vu0::Q(dir) = Vu0::Sub(Vu0::Q(a), Vu0::Q(b));
        u128 len = Vu0::Length(Vu0::Q(dir));
        if (Vu0::ToFloat(len) < 0.0001f) {
            dir = *fb;
        } else {
            Vu0::Q(dir) = Vu0::DivX(Vu0::Q(dir), len);
        }
        f32 e = tune->f328;
        f32 l = Vu0::ToFloat(len);
        f32 f5 = tune->f324;
        if (e == 1.0f) {
            f32 q = l / tune->flightTime;
            t->f6F4 = 0.0f;
            t->f6F0 = q;
            t->f690 = q;
        } else {
            f32 q = (l + l) / ((f5 - e * f5 + (e + e)) * tune->flightTime);
            t->f690 = q;
            t->f6F0 = q * e;
            t->f6F4 = (t->f6F0 - q) / (f5 * tune->flightTime);
        }
        Vu0::Q(sa->v50) = Vu0::MulX(Vu0::Q(dir), Vu0::ScalarAt(t->f690));
    } else if (IsObjectOfKind((BaseObject*)t, 0x3E) != 0) {
        Vu0::Q(obj->poseA.v50) = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::ScalarAt(tune->launchSpeed));
        Vu0::Q(t->v700) = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::Scalar(-tune->f334));
        t->f6F0 = tune->flightTime;
    } else {
        Vec02 dir;
        if (ComputeBallisticLaunchVelocity(&b, &a, &dir, 0, tune->launchAngle) == 0) {
            return;
        }
        u128 d1 = Vu0::Sub(Vu0::Q(b), Vu0::Q(a));
        f32 l1 = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(d1, d1)));
        f32 l2 = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(dir), Vu0::Q(dir))));
        f32 u = l1 / l2 / tune->flightTime;
        Vu0::Q(t->gravity) = Vu0::MulX(Vu0::Q(self->world->gravity), Vu0::Scalar(u * u));
        Vu0::Q(obj->poseA.v50) = Vu0::MulX(Vu0::Q(dir), Vu0::Scalar(u));
    }
    sa->life = tune->flightTime * D_00262A28[0];
    sb->v10 = a;
    if (LaunchChosenPoolObject((ObjectPool*)self->launchPool, 0) != 0) {
        self->nextLaunchTime = g_gameTime + ((FollowTune*)self->followedObject->tuneObject)->launchInterval;
    }
}

typedef void (*VFn_16D788)(TargetFollower* self, const void* arg);


// Puts the follower on the followed object's anchor: clears the anchors and velocities, and moves
// it to the anchor's world position raised by the height offset.
void PlaceTargetFollowerOnFollowed(TargetFollower* self) {
    Vec3 v;
    SetColliderAnchors(self, 3, 0, 3, 0);
    ((VFn_16D788*)self->desc)[36](self, &g_zeroVector);
    ((VFn_16D788*)self->desc)[37](self, &g_zeroVector);
    ConvertPositionToWorld((BaseObject*)self->followedObject->anchor, (Vec02*)&v);
    v.z = v.z + self->heightOffset;
    ((VFn_16D788*)self->desc)[33](self, &v);
}

extern f32 g_gameTime;

// Throws the follower at the followed object: the target is the anchor's position raised by
// heightOffset, the ballistic launch velocity to it is computed and applied, and the arrival time
// (now plus distance / speed) and the end of the first phase (arrival minus leadTime) are stored.
void LaunchTargetFollowerAtFollowed(TargetFollower* self)
{
    Vec02 target;
    Vec02 vel;
    Vec02 d;
    ConvertPositionToWorld((BaseObject*)self->followedObject->anchor, (Vec02*)&target);
    target.z = target.z + self->heightOffset;
    ComputeBallisticLaunchVelocity(&self->v140, &target, &vel, (u8*)self, 0.5f);
    SetColliderAnchors(self, 0, 0, 3, 0);
    ((VFn_16D788*)self->desc)[36](self, &vel);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(target), Vu0::Q(self->v140));
    f32 dist = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(d), Vu0::Q(d))));
    f32 speed = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(vel), Vu0::Q(vel))));
    f32 t = g_gameTime + dist / speed;
    self->arrivalTime = t;
    self->phaseOneEndTime = t - self->leadTime;
}

extern const KeyRecord g_streamVoiceKeys[7];


// With a 20 in 100 chance, when voices are enabled and none is playing, opens one of six stream
// voice keys at random and marks the voice pending.
void StartRandomStreamVoice(TargetFollower* self)
{
    s32 r;

    if (self->voiceEnabled == 0) {
        return;
    }
    if (HasStreamVoice() != 0) {
        return;
    }
    r = RandomIntInRange(0, 0x64);
    if (r >= 0x14) {
        return;
    }
    r = RandomIntInRange(0, 6);
    // address arithmetic over a variable index
    OpenKeyRecord((KeyRecord*)((u8*)g_streamVoiceKeys + (r << 5)));
    self->voicePending = 1;
}

struct PlayingSound;

// When a voice is pending and the stream voice has finished loading, clears the pending flag and
// plays the sound with the follower's volume and pan.
void PlayPendingFollowerSound(TargetFollower* self)
{
    if (self->voicePending != 0) {
        if (CheckStreamVoicePending() == 0) {
            self->voicePending = 0;
            PlaySoundAndApplyVolumePan(self, 0, self->f5C4, self->f5C8);
        }
    }
}

void LaunchPoolItemAtTarget(void* self);
void LaunchTargetFollowerAtFollowed(void* self);
void StartRandomStreamVoice(void* self);
void SetTargetFollowerMode(void* self, s32 mode);

// On notification 0x13 reacts to the message code: 0x2FD launches a pool item at the target,
// 0x2FE and 0x2FF are the cases handled by the calls at the end of the function (0x2FF sets mode
// 2), 0x300 launches the follower at the followed object.
void HandleTargetFollowerNotification(TargetFollower* self, s32 type, Packet47* packet)
{
    HandlePlacedObjectNotification(self, type, packet);
    if (type != 0x13) {
        return;
    }
    s32 code = packet->code;
    if (code == 0x2FE) {
        goto call928;
    }
    if (code < 0x2FF) {
        if (code == 0x2FD) {
            goto call490;
        }
        return;
    }
    if (code == 0x2FF) {
        goto callDAC0;
    }
    if (code == 0x300) {
        LaunchTargetFollowerAtFollowed(self);
    }
    return;
call490:
    LaunchPoolItemAtTarget(self);
    return;
callDAC0:
    SetTargetFollowerMode(self, 2);
    return;
call928:
    StartRandomStreamVoice(self);
}

void PlaceTargetFollowerOnFollowed(TargetFollower* self);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);
Collider* GetActiveSwitchedCollider(void);

extern const Mat02 g_identityMatrix;
void* ChooseEntryTableObject(EntryTableObject* self);
extern GameClock g_gameClock;

struct FollowerTrail { u8 pad00[0x40]; Vec02 v40; Vec02 v50; Vec02 v60; Vec02 v70; };

// Changes the follower's mode (0 to 4): leaving mode 1 puts it on the followed object, then it
// records the time, sets up what the new mode needs (the next launch time one second on for mode 1,
// positions for 0 and 3) and sets the state walker's target key (0x2EF to 0x2F6 by mode and sub-
// state).
void SetTargetFollowerMode(TargetFollower* self, s32 mode)
{
    s32 key;
    if (self->mode == mode) {
        return;
    }
    if (self->mode == 1) {
        PlaceTargetFollowerOnFollowed(self);
    }
    self->mode = mode;
    self->modeStartTime = g_gameClock.time;
    switch (mode) {
    case 0: {
        Vec02 pos;
        Vec02 d;
        key = 0x2EF;
        ConvertPositionToWorld((BaseObject*)self->followedObject->anchor, (Vec02*)&pos);
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->v140));
        self->heading = ArctangentOfRatio(d.y, d.x);
        f32 big = 3.4028234663852886e+38f;
        self->arrivalTime = big;
        self->phaseOneEndTime = big;
        break;
    }
    case 3: {
        Vec02 pos;
        Vec02 d;
        GetActiveSwitchedCollider();
        EntryTableObject* table = (EntryTableObject*)self->followedObject->tuneObject;
        if (self->trailCountdown <= 0) {
            self->lookTarget = self->trailObject;
            FollowerTrail* t = (FollowerTrail*)self->trailObject;
            t->v40 = g_player->v140;
            t = (FollowerTrail*)self->trailObject;
            t->v50 = g_identityMatrix.r[0];
            t->v60 = g_identityMatrix.r[1];
            t->v70 = g_identityMatrix.r[2];
            self->trailCountdown = RandomIntInRange(1, 3);
        } else {
            self->lookTarget = ChooseEntryTableObject(table);
            self->trailCountdown--;
        }
        switch (table->mode318) {
        case 0:
            key = 0x2F1;
            break;
        case 1:
            key = 0x2F2;
            break;
        default:
            key = 0x2F1;
            break;
        }
        GetObjectWorldPosition((BaseObject*)self->lookTarget, &pos);
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->v140));
        self->heading = ArctangentOfRatio(d.y, d.x);
        break;
    }
    case 1:
        self->nextLaunchTime = g_gameClock.time + 1.0f;
        key = 0x2F0;
        break;
    case 2: {
        switch (((EntryTableObject*)self->followedObject->tuneObject)->mode318) {
        default:
            key = 0x2F4;
            break;
        case 0:
            key = 0x2F5;
            if (RandomFloatInRange(0.0f, 1.0f) < 0.5f) {
                key = 0x2F4;
            }
            break;
        case 1:
            key = 0x2F6;
            break;
        }
        break;
    }
    case 4:
        key = 0x2F3;
        break;
    }
    SetStateWalkerTarget((StateWalker*)self->stateWalker, key);
}

extern TargetFollower* g_currentTargetFollower;

// Makes follower the current target follower (a global).
void SetCurrentTargetFollower(TargetFollower* follower)
{
    g_currentTargetFollower = follower;
}

extern TargetFollower* g_currentTargetFollower;

// Clears the current target follower, whichever it was.
void ClearCurrentTargetFollower(TargetFollower* follower)
{
    g_currentTargetFollower = 0;
}


// Initialises the placed object and sets its tuning values (2.25, 2, 0.8, 4, 0.5, 1000, 2000).
void InitEntryTableObject(EntryTableObject* self)
{
    InitPlacedObject(self);
    self->tune31C = 2.25f;
    self->tune320 = 2.0f;
    self->tune324 = 0.8f;
    self->tune328 = 4.0f;
    self->tune32C = 0.5f;
    self->tune330 = 1000.0f;
    self->tune334 = 2000.0f;
}


// Loads the placed object and gathers up to 16 objects of the entry kind (0x201, 0x73) into its
// entries, storing their count.
void LoadEntryTable(EntryTableObject* self, BufferedStream* stream)
{
    LoadPlacedObject(self, stream);
    s32 r = GatherObjectsById(self->world, 0x201, 0x73, self, 0x10, self->entries);
    self->entryCount = r;
    if ((u32)r >= 0x11) {
        self->entryCount = 0x10;
    }
}


// Starts the placed object and then calls the class's method 3 on it.
void StartEntryTableObject(EntryTableObject* self)
{
    StartPlacedObject(self);
    self->desc->m03(self);
}


// Picks an object from the entry table by its mode at 0x314: mode 1 a random one, mode 0 the one
// nearest the active switched collider (the player), any other mode gives 0.
void* ChooseEntryTableObject(EntryTableObject* self)
{
    if (self->entryCount > 0) {
        if (self->mode314 != 0) {
            if (self->mode314 != 1) {
                return 0;
            }
            s32 r = RandomIntInRange(0, self->entryCount - 1);
            void** base = (void**)self->entries;
            // address arithmetic over a variable index
            return *(void**)((u8*)base + r * 4);
        }
        f32 best = 3.40282347e+38f;
        void* found = 0;
        Collider* player = GetActiveSwitchedCollider();
        for (s32 i = 0; i < self->entryCount; i++) {
            void* obj = ((void**)self->entries)[i];
            Vec02 pos;
            GetObjectWorldPosition((BaseObject*)obj, &pos);
            u128 d = Vu0::Sub(Vu0::Q(pos), Vu0::Q(player->v140));
            f32 dist = Vu0::ToFloat(Vu0::Dot(d, d));
            if (dist < best) {
                best = dist;
                found = obj;
            }
        }
        return found;
    }
    return 0;
}

// Initialises the zone collider and clears the zone duration and the two ids (anchor and tune
// object) to -1.
void InitFollowableObject(FollowableObject* self)
{
    InitZoneCollider(self);
    self->zone.duration = 0;
    self->id7A0 = -1;
    self->id7A8 = -1;
}


// Finishes loading the placed object and finds its anchor (by its own id, or the first gathered
// object of the kind 0x7E when it has none) and its tune object.
void ResolveFollowableObjectLinks(FollowableObject* self)
{
    PostLoadPlacedObject(self);
    if (self->id7A0 != -1) {
        self->anchor = (void*)FindFirstObjectById(self->world, 4, self->id7A0, self);
    } else {
        self->anchor = (void*)FindFirstObjectByIdGathered(self->world, 2, 0x7E, self);
    }
    self->tuneObject = (void*)FindFirstObjectById(self->world, 4, self->id7A8, self);
}

extern TargetFollower* g_currentTargetFollower;


// Handles the placed-object notification and keeps the current target follower's list of
// followables in step: kind 0xC appends this object, kind 0xD removes it, and kind 2 removes it
// if it is listed.
void HandleFollowableObjectNotification(FollowableObject* self, s32 kind, void* arg)
{
    HandlePlacedObjectNotification(self, kind, arg);
    switch (kind)
    {
    case 2:
        if (g_currentTargetFollower != 0)
        {
            if (IsInList(&g_currentTargetFollower->list55C, self) != 0)
            {
                RemoveFromList(&g_currentTargetFollower->list55C, self);
            }
        }
        break;
    case 0xC:
        if (g_currentTargetFollower != 0)
        {
            AppendToList(&g_currentTargetFollower->list55C, self);
        }
        break;
    case 0xD:
        if (g_currentTargetFollower != 0)
        {
            RemoveFromList(&g_currentTargetFollower->list55C, self);
        }
        break;
    }
}
