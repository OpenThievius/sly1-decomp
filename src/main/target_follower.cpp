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

void LoadCollider(Collider* self, BufferedStream* in);
struct StateGraph;
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);
u32 GetStateEntryKey(StateGraph* a0, s32 a1);
void InitCollider(Collider* self);
void SetListLinkOffset(List01* self, s32 offset);

extern TargetFollower* g_currentTargetFollower;

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
        Entry47* e = (Entry47*)((u8*)self->list550->items + off);
        if (GetStateEntryKey((StateGraph*)self->list550, e->a) == k1 && GetStateEntryKey((StateGraph*)self->list550, e->b) == k2) {
            break;
        }
        off += 0x14;
        i++;
    }
    if (i < self->list550->count) {
        Entry47* p = (Entry47*)((u8*)(i * 0x14) + (s32)self->list550->items);
        self->leadTime = p->ref->f34;
    }
}

void StartPlacedObject(PlacedObject* self);
void ResolveObjectLinks(BaseObject* self, s32 count, ObjectLink* item);
StateWalker* CreateStateWalker(StateGraph* self, void* a1, s32 a2, s32 a3);
void ConvertPositionToWorld(BaseObject* self, Vec02* out);
void FollowObjectById(TargetFollower* self, s32 x);
void* CreateTypedRecord(s32 index, void* a1, BaseObject* a2, s32 a3, s32 a4);

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

void StepCollider(Collider* self, f32 t);
void BuildAxisAngleMatrix(const Vec02* v, Mat02* out, f32 angle);
void TurnColliderTowardRotation(Collider* self, f32 dt, Mat02* target, f32* gain);

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

void UpdateCollider(Collider* self, f32 dt);
void PlayPendingFollowerSound(TargetFollower* self);
s32 ChooseTargetFollowerMode(TargetFollower* self);
void SetTargetFollowerMode(TargetFollower* self, s32 mode);
Collider* GetActiveSwitchedCollider(void);
extern "C" f32 ArctangentOfRatio(f32 y, f32 x);

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
s32 HasObjectPoolChoice(ObjectPool* self);
typedef s32 (*VFnRet_16D1E0)(void* self);
void* ChooseEntryTableObject(EntryTableObject* self);

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

void ChooseObjectPoolItem(ObjectPool* self);
SoundLevelEntry* PushSoundLevel(s32 kind);
void RemoveSoundLevelAndRecompute(SoundLevelEntry* p);

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
void GetObjectWorldPosition(BaseObject* self, Vec02* out);
s32 ComputeBallisticLaunchVelocity(Vec02* from, Vec02* to, Vec02* out, u8* rec, f32 angle);
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
    u8 pad4C[0xB0 - 0x4C];
    Vec02 vB0;              // 0xB0
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

struct FrameSource;
void GetPlacementRecordTransform(FrameSource* self, Vec02* a1, Vec02* a2, void* a3);
s32 IsObjectOfKind(BaseObject* list, s32 key);
s32 LaunchChosenPoolObject(ObjectPool* pool, s32 aim);

void LaunchPoolItemAtTarget(TargetFollower* self)
{
    Vec02 a;
    Vec02 b;
    Mat02 c;
    GetObjectWorldPosition((BaseObject*)self->lookTarget, &a);
    FollowObject* obj = (FollowObject*)self->launchPool;
    ChaseObject* t = obj->f48;
    FollowPoseA* sa = (FollowPoseA*)((u8*)obj + 0x60);
    FollowPoseB* sb = (FollowPoseB*)((u8*)obj + 0xE0);
    if (t == 0) {
        return;
    }
    GetPlacementRecordTransform((FrameSource*)sa, &b, c.r, 0);
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
        Vu0::Q(obj->vB0) = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::ScalarAt(tune->launchSpeed));
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
        Vu0::Q(obj->vB0) = Vu0::MulX(Vu0::Q(dir), Vu0::Scalar(u));
    }
    sa->life = tune->flightTime * D_00262A28[0];
    sb->v10 = a;
    if (LaunchChosenPoolObject((ObjectPool*)self->launchPool, 0) != 0) {
        self->nextLaunchTime = g_gameTime + ((FollowTune*)self->followedObject->tuneObject)->launchInterval;
    }
}

typedef void (*VFn_16D788)(TargetFollower* self, const void* arg);

void SetColliderAnchors(Collider* self, s32 a1, Vec02* a2, s32 a3, Vec02* a4);
void ConvertPositionToWorld(BaseObject* self, Vec02* out);

void PlaceTargetFollowerOnFollowed(TargetFollower* self) {
    Vec3 v;
    SetColliderAnchors(self, 3, 0, 3, 0);
    ((VFn_16D788*)self->desc)[36](self, &D_00248D30);
    ((VFn_16D788*)self->desc)[37](self, &D_00248D30);
    ConvertPositionToWorld((BaseObject*)self->followedObject->anchor, (Vec02*)&v);
    v.z = v.z + self->heightOffset;
    ((VFn_16D788*)self->desc)[33](self, &v);
}

s32 ComputeBallisticLaunchVelocity(Vec02* from, Vec02* to, Vec02* out, u8* rec, f32 angle);
extern f32 g_gameTime;

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

s32 HasStreamVoice(void);
s32 RandomIntInRange(s32 a, s32 b);
void OpenKeyRecord(KeyRecord* slot);

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
    OpenKeyRecord((KeyRecord*)((u8*)g_streamVoiceKeys + (r << 5)));
    self->voicePending = 1;
}

s32 CheckStreamVoicePending(void);
struct PlayingSound;
void PlaySoundAndApplyVolumePan(BaseObject* a0, PlayingSound** a1, f32 f12, f32 f13);

void PlayPendingFollowerSound(TargetFollower* self)
{
    if (self->voicePending != 0) {
        if (CheckStreamVoicePending() == 0) {
            self->voicePending = 0;
            PlaySoundAndApplyVolumePan(self, 0, self->f5C4, self->f5C8);
        }
    }
}

void HandlePlacedObjectNotification(PlacedObject* self, s32 mode, void* arg);
void LaunchPoolItemAtTarget(void* self);
void LaunchTargetFollowerAtFollowed(void* self);
void StartRandomStreamVoice(void* self);
void SetTargetFollowerMode(void* self, s32 mode);

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
s32 RandomIntInRange(s32 a, s32 b);
void ConvertPositionToWorld(BaseObject* self, Vec02* out);

extern const Mat02 g_identityMatrix;
void GetObjectWorldPosition(BaseObject* self, Vec02* out);
f32 RandomFloatInRange(f32 a, f32 b);
s32 RandomIntInRange(s32 a, s32 b);
void SetStateWalkerTarget(StateWalker* self, s32 key);
void* ChooseEntryTableObject(EntryTableObject* self);
extern GameClock g_gameClock;

struct FollowerTrail { u8 pad00[0x40]; Vec02 v40; Vec02 v50; Vec02 v60; Vec02 v70; };

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

void SetCurrentTargetFollower(TargetFollower* follower)
{
    g_currentTargetFollower = follower;
}

extern TargetFollower* g_currentTargetFollower;

void ClearCurrentTargetFollower(TargetFollower* follower)
{
    g_currentTargetFollower = 0;
}

void InitPlacedObject(PlacedObject* self);

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

void LoadPlacedObject(PlacedObject* self, void* r);

void LoadEntryTable(EntryTableObject* self, BufferedStream* stream)
{
    LoadPlacedObject(self, stream);
    s32 r = GatherObjectsById(self->world, 0x201, 0x73, self, 0x10, self->entries);
    self->entryCount = r;
    if ((u32)r >= 0x11) {
        self->entryCount = 0x10;
    }
}

void StartPlacedObject(PlacedObject* self);

void StartEntryTableObject(EntryTableObject* self)
{
    StartPlacedObject(self);
    self->desc->m03(self);
}

void GetObjectWorldPosition(BaseObject* self, Vec02* out);

void* ChooseEntryTableObject(EntryTableObject* self)
{
    if (self->entryCount > 0) {
        if (self->mode314 != 0) {
            if (self->mode314 != 1) {
                return 0;
            }
            s32 r = RandomIntInRange(0, self->entryCount - 1);
            void** base = (void**)self->entries;
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

void InitFollowableObject(FollowableObject* self)
{
    InitZoneCollider(self);
    self->zone.duration = 0;
    self->id7A0 = -1;
    self->id7A8 = -1;
}

void PostLoadPlacedObject(PlacedObject* self);

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

void HandlePlacedObjectNotification(PlacedObject* self, s32 mode, void* arg);
s32 IsInList(List01* self, void* item);
void AppendToList(List01* self, void* item);
void RemoveFromList(List01* list, void* item);

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
