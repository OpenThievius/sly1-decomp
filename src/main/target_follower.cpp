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

// The target follower (class 0x47), the entry-table object (0x64) and the followable object
// (0x2A). Its .data runs from 0x2629C8 to 0x262A30: the current follower, the two link tables of
// class 0x47 and the two floats func_0016D490 reads. Its .rodata, from 0x24A7F0, is the jump
// tables and FLT_MAX literals of its VU0 functions.

s32 g_currentTargetFollower = 0;
s32 g_targetFollowerLoadLinks[16] = { 0x0, 0x2EE, 0x550, 0x0, 0x2F8, 0x57C, 0x0, 0x2F9, 0x580, 0x0, 0x2FB, 0x588, 0x0, 0x2FC, 0x58C, 0x0 };
s32 g_targetFollowerResolveLinks[6] = { 0x0, 0x2FA, 0x584, 0x0, 0x2F7, 0x568 };
f32 D_00262A28[2] = { 1.25f, 1.5f };

void LoadCollider(void* self);
void ResolveObjectLinks(void* self, s32 id, void* table);
s32 GetStateEntryKey(void* a, s32 b);
s32 FindFirstObjectById(void* a0, s32 a1, s32 a2, void* a3);
s32 FindFirstObjectByIdGathered(void* a0, s32 a1, s32 a2, void* a3);

void InitCollider(void* self);
void SetListLinkOffset(void* self, s32 value);
extern s32 g_currentTargetFollower;

void InitTargetFollower(TargetFollower* self)
{
    InitCollider(self);
    self->f578 = -1;
    self->f598 = -1;
    self->f5C4 = 3000.0f;
    self->f5C8 = 1000.0f;
    SetListLinkOffset(&self->list55C, 0x7B0);
    Tune47* q = &self->tune5B0;
    q->a = 25.0f;
    q->c = 0.25f;
    q->b = 0;
    g_currentTargetFollower = 0;
}

void LoadTargetFollowerRecords(TargetFollower* self)
{
    s32 k1 = 0x2EF;
    s32 k2 = 0x2F0;
    s32 i = 0;
    s32 off = 0;
    LoadCollider(self);
    ResolveObjectLinks(self, 5, g_targetFollowerLoadLinks);
    for (;;) {
        if (i >= self->list550->count) {
            return;
        }
        Entry47* e = (Entry47*)((u8*)self->list550->items + off);
        if (GetStateEntryKey(self->list550, e->a) == k1 && GetStateEntryKey(self->list550, e->b) == k2) {
            break;
        }
        off += 0x14;
        i++;
    }
    if (i < self->list550->count) {
        Entry47* p = (Entry47*)((u8*)(i * 0x14) + (s32)self->list550->items);
        self->f5A4 = p->ref->f34;
    }
}

void StartPlacedObject(void* self);
void ResolveObjectLinks(void* self, s32 n, void* table);
void* CreateStateWalker(void* a, void* b, s32 c, s32 d);
void ConvertPositionToWorld(void* self, f32* arg);
void FollowObjectById(TargetFollower* self, void* x);
void* CreateTypedRecord(s32 a, void* b, s32 c, s32 d, s32 e);

void ResolveTargetFollowerLinks(TargetFollower* self)
{
    f32 scratch[4];

    StartPlacedObject(self);
    ResolveObjectLinks(self, 2, g_targetFollowerResolveLinks);
    self->f554 = CreateStateWalker(self->list550, self, -1, 1);
    self->f570 = (Sub47*)FindFirstObjectByIdGathered(self->world, 1, 0x8C, self);
    ConvertPositionToWorld(self->f568, scratch);
    self->f56C = self->v140.z - scratch[2];
    if (self->f578 != -1)
    {
        FollowObjectById(self, (void*)self->f578);
    }
    u64 m = 0x8000;
    s32 sh = 27;
    m <<= sh;
    self->flags538 |= m;
    self->f594 = CreateTypedRecord(0x73, g_currentWorld, 0, 0x302, -1);
}

void* FindFirstObjectByIdMode4(void* obj, void* id, void* owner);
void SetFollowedObject(TargetFollower* self, FollowableObject* x);
void PlaceTargetFollowerOnFollowed(TargetFollower* self);
void SetTargetFollowerMode(TargetFollower* self, s32 mode);

void FollowObjectById(TargetFollower* self, void* x)
{
    self->f578 = (s32)x;
    FollowableObject* p = (FollowableObject*)FindFirstObjectByIdMode4(self->world, x, self);
    if (p != 0) {
        SetFollowedObject(self, p);
        PlaceTargetFollowerOnFollowed(self);
        if (p->f7AC != 0) {
            SetTargetFollowerMode(self, 2);
        } else {
            SetTargetFollowerMode(self, 4);
        }
    }
}

void FillMemory(u8* p, s32 a, s32 b);

void StepCollider(Collider* self, f32 t);
void BuildAxisAngleMatrix(const Vec02* tab, Mat3U* out, f32 v);
void TurnColliderTowardRotation(Collider* self, f32 t, Mat3U* out, void* data);

void StepTargetFollower(TargetFollower* self, f32 t)
{
    Mat3U buf;

    StepCollider(self, t);
    if (self->w5D8 != 0) {
        return;
    }
    BuildAxisAngleMatrix(&g_unitZVector, &buf, self->f5A0);
    TurnColliderTowardRotation(self, t, &buf, self->sub5B0);
}

void UpdateCollider(Collider* self);
void PlayPendingFollowerSound(TargetFollower* self);
s32 ChooseTargetFollowerMode(TargetFollower* self);
void SetTargetFollowerMode(TargetFollower* self, s32 mode);
Collider* GetActiveSwitchedCollider(void);
f32 ArctangentOfRatio(f32 a, f32 b);

void func_0016D128(TargetFollower* self)
{
    UpdateCollider(self);
    PlayPendingFollowerSound(self);
    if ((s32)self != g_currentTargetFollower) {
        return;
    }
    s32 mode;
    while ((mode = ChooseTargetFollowerMode(self)) != self->f598) {
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
        self->f5A0 = ArctangentOfRatio(d.y, d.x);
        break;
    }
}

INCLUDE_RODATA(jtbl_0024A810);
INCLUDE_ASM(func_0016D1E0);

extern s32 g_padSelectFlags;

extern s32 g_padSelectFlags;

void FillMemory(void* p, s32 value, s32 size);

struct Item_16D3F0 { u8 pad0[0x318]; s32 f318; };

void ChooseObjectPoolItem(void* p);
Obj_1BF0D8* PushSoundLevel(s32 kind);
void RemoveSoundLevelAndRecompute(Obj_1BF0D8* p);

void SetFollowedObject(TargetFollower* self, FollowableObject* x)
{
    if (x == self->f558) {
        return;
    }
    void* v = 0;
    if (x != 0) {
        v = x->f7AC;
    }
    if (v != self->f5D0) {
        self->f5D0 = v;
        self->f5D4 = 3;
    }
    self->f558 = x;
    if (v != 0) {
        self->f570->f44 = ((Item_16D3F0*)x->f7AC)->f318;
        ChooseObjectPoolItem(self->f570);
        if (self->f5BC != 0) {
            return;
        }
        self->f5BC = PushSoundLevel(0x6B);
    } else {
        if (self->f5BC != 0) {
            RemoveSoundLevelAndRecompute(self->f5BC);
            self->f5BC = 0;
        }
    }
}

extern f32 g_gameTime;
s32 GetObjectWorldPosition(void* p, Vec02* out);
s32 ComputeBallisticLaunchVelocity(f32 t, Vec02* from, Vec02* to, Vec02* out, void* self);
extern const Vec02 D_00248D20;

struct FollowPoseA {
    u8 pad00[0x50];
    Vec02 v50;              // 0x50
    u8 pad60[0x78 - 0x60];
    f32 f78;                // 0x78
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
    f32 f31C;               // 0x31C
    f32 f320;               // 0x320
    f32 f324;               // 0x324
    f32 f328;               // 0x328
    f32 f32C;               // 0x32C
    f32 f330;               // 0x330
    f32 f334;               // 0x334
};

void GetPlacementRecordTransform(void* rec, Vec02* a, Mat02* b, s32 zero);
s32 IsObjectOfKind(void* obj, s32 kind);
s32 func_001A8C90(void* obj, s32 zero);

void func_0016D490(TargetFollower* self)
{
    Vec02 a;
    Vec02 b;
    Mat02 c;
    GetObjectWorldPosition(self->f590, &a);
    FollowObject* obj = (FollowObject*)self->f570;
    ChaseObject* t = obj->f48;
    FollowPoseA* sa = (FollowPoseA*)((u8*)obj + 0x60);
    FollowPoseB* sb = (FollowPoseB*)((u8*)obj + 0xE0);
    if (t == 0) {
        return;
    }
    GetPlacementRecordTransform(sa, &b, &c, 0);
    FollowTune* tune = (FollowTune*)self->f558->f7AC;
    if (IsObjectOfKind(t, 0x3D) != 0) {
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
            f32 q = l / tune->f320;
            t->f6F4 = 0.0f;
            t->f6F0 = q;
            t->f690 = q;
        } else {
            f32 q = (l + l) / ((f5 - e * f5 + (e + e)) * tune->f320);
            t->f690 = q;
            t->f6F0 = q * e;
            t->f6F4 = (t->f6F0 - q) / (f5 * tune->f320);
        }
        Vu0::Q(sa->v50) = Vu0::MulX(Vu0::Q(dir), Vu0::ScalarAt(t->f690));
    } else if (IsObjectOfKind(t, 0x3E) != 0) {
        Vu0::Q(obj->vB0) = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::ScalarAt(tune->f330));
        Vu0::Q(t->v700) = Vu0::MulX(Vu0::Q(g_unitZVector), Vu0::Scalar(-tune->f334));
        t->f6F0 = tune->f320;
    } else {
        Vec02 dir;
        if (ComputeBallisticLaunchVelocity(tune->f32C, &b, &a, &dir, 0) == 0) {
            return;
        }
        u128 d1 = Vu0::Sub(Vu0::Q(b), Vu0::Q(a));
        f32 l1 = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(d1, d1)));
        f32 l2 = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(dir), Vu0::Q(dir))));
        f32 u = l1 / l2 / tune->f320;
        Vu0::Q(t->gravity) = Vu0::MulX(Vu0::Q(*(Vec02*)((u8*)self->world + 0x1EE0)), Vu0::Scalar(u * u));
        Vu0::Q(obj->vB0) = Vu0::MulX(Vu0::Q(dir), Vu0::Scalar(u));
    }
    sa->f78 = tune->f320 * D_00262A28[0];
    sb->v10 = a;
    if (func_001A8C90(self->f570, 0) != 0) {
        self->f574 = g_gameTime + ((FollowTune*)self->f558->f7AC)->f31C;
    }
}

typedef void (*VFn_16D788)(TargetFollower* self, const void* arg);

void SetColliderAnchors(Collider* self, s32 a, s32 b, s32 c, s32 d);
void ConvertPositionToWorld(void* arg, Vec3* out);

void PlaceTargetFollowerOnFollowed(TargetFollower* self) {
    Vec3 v;
    SetColliderAnchors(self, 3, 0, 3, 0);
    ((VFn_16D788*)self->desc)[36](self, &D_00248D30);
    ((VFn_16D788*)self->desc)[37](self, &D_00248D30);
    ConvertPositionToWorld(self->f558->f7A4, &v);
    v.z = v.z + self->f56C;
    ((VFn_16D788*)self->desc)[33](self, &v);
}

s32 ComputeBallisticLaunchVelocity(f32 t, Vec02* from, Vec02* to, Vec02* out, void* self);
extern f32 g_gameTime;

void LaunchTargetFollowerAtFollowed(TargetFollower* self)
{
    Vec02 target;
    Vec02 vel;
    Vec02 d;
    ConvertPositionToWorld(self->f558->f7A4, (Vec3*)&target);
    target.z = target.z + self->f56C;
    ComputeBallisticLaunchVelocity(0.5f, &self->v140, &target, &vel, self);
    SetColliderAnchors(self, 0, 0, 3, 0);
    ((VFn_16D788*)self->desc)[36](self, &vel);
    Vu0::Q(d) = Vu0::Sub(Vu0::Q(target), Vu0::Q(self->v140));
    f32 dist = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(d), Vu0::Q(d))));
    f32 speed = Vu0::ToFloatMoved(Vu0::Sqrt(Vu0::DotXY(Vu0::Q(vel), Vu0::Q(vel))));
    f32 t = g_gameTime + dist / speed;
    self->f5AC = t;
    self->f5A8 = t - self->f5A4;
}

extern const KeyRecord g_streamVoiceKeys[7];

s32 HasStreamVoice(void);
s32 RandomIntInRange(void* a, s32 b);
void OpenKeyRecord(KeyRecord* slot);

void StartRandomStreamVoice(TargetFollower* self)
{
    s32 r;

    if (self->f5C0 == 0) {
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
    self->f5CC = 1;
}

s32 CheckStreamVoicePending(void* self);
void PlaySoundAndApplyVolumePan(void* self, s32 mode, f32 a, f32 b);

void PlayPendingFollowerSound(TargetFollower* self)
{
    if (self->f5CC != 0) {
        if (CheckStreamVoicePending(self) == 0) {
            self->f5CC = 0;
            PlaySoundAndApplyVolumePan(self, 0, self->f5C4, self->f5C8);
        }
    }
}

void HandlePlacedObjectNotification(void* self, s32 type, void* packet);
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
f32 ArctangentOfRatio(f32 a, f32 b);
Collider* GetActiveSwitchedCollider(void);
s32 RandomIntInRange(s32 a, s32 b);
void ConvertPositionToWorld(void* arg, Vec3* out);

extern const Mat02 D_002483D0;
s32 GetObjectWorldPosition(void* p, Vec02* out);
f32 RandomFloatInRange(f32 a, f32 b);
s32 RandomIntInRange(s32 a, s32 b);
void SetStateWalkerTarget(void* p, s32 key);
void* ChooseEntryTableObject(EntryTableObject* self);
extern GameClock g_gameClock;

struct FollowerTrail { u8 pad00[0x40]; Vec02 v40; Vec02 v50; Vec02 v60; Vec02 v70; };

void func_0016DAC0(TargetFollower* self, s32 mode)
{
    s32 key;
    if (self->f598 == mode) {
        return;
    }
    if (self->f598 == 1) {
        PlaceTargetFollowerOnFollowed(self);
    }
    self->f598 = mode;
    self->f59C = g_gameClock.time;
    switch (mode) {
    case 0: {
        Vec02 pos;
        Vec02 d;
        key = 0x2EF;
        ConvertPositionToWorld(self->f558->f7A4, (Vec3*)&pos);
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->v140));
        self->f5A0 = ArctangentOfRatio(d.y, d.x);
        f32 big = 3.4028234663852886e+38f;
        self->f5AC = big;
        self->f5A8 = big;
        break;
    }
    case 3: {
        Vec02 pos;
        Vec02 d;
        GetActiveSwitchedCollider();
        EntryTableObject* table = (EntryTableObject*)self->f558->f7AC;
        if (self->f5D4 <= 0) {
            self->f590 = self->f594;
            FollowerTrail* t = (FollowerTrail*)self->f594;
            t->v40 = g_player->v140;
            t = (FollowerTrail*)self->f594;
            t->v50 = D_002483D0.r[0];
            t->v60 = D_002483D0.r[1];
            t->v70 = D_002483D0.r[2];
            self->f5D4 = RandomIntInRange(1, 3);
        } else {
            self->f590 = ChooseEntryTableObject(table);
            self->f5D4--;
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
        GetObjectWorldPosition(self->f590, &pos);
        Vu0::Q(d) = Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->v140));
        self->f5A0 = ArctangentOfRatio(d.y, d.x);
        break;
    }
    case 1:
        self->f574 = g_gameClock.time + 1.0f;
        key = 0x2F0;
        break;
    case 2: {
        switch (((EntryTableObject*)self->f558->f7AC)->mode318) {
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
    SetStateWalkerTarget(self->f554, key);
}

extern s32 g_currentTargetFollower;

void SetCurrentTargetFollower(s32 value)
{
    g_currentTargetFollower = value;
}

extern s32 g_currentTargetFollower;

void ClearCurrentTargetFollower(void)
{
    g_currentTargetFollower = 0;
}

void InitPlacedObject(void* self);

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

void LoadPlacedObject(void* self);
s32 GatherObjectsById(s32 a, s32 b, s32 c, void* d, s32 e, void* f);

void LoadEntryTable(EntryTableObject* self)
{
    LoadPlacedObject(self);
    s32 r = GatherObjectsById((s32)self->world, 0x201, 0x73, self, 0x10, self->entries);
    self->entryCount = r;
    if ((u32)r >= 0x11) {
        self->entryCount = 0x10;
    }
}

void StartPlacedObject(void* self);

void StartEntryTableObject(EntryTableObject* self)
{
    StartPlacedObject(self);
    self->desc->m03(self);
}

s32 GetObjectWorldPosition(void* p, Vec02* out);

void* func_0016DE20(EntryTableObject* self)
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
            GetObjectWorldPosition(obj, &pos);
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

void PostLoadPlacedObject(void* self);
s32 FindFirstObjectById(void* a0, s32 a1, s32 a2, void* a3);
s32 FindFirstObjectByIdGathered(void* a0, s32 a1, s32 a2, void* a3);

void ResolveFollowableObjectLinks(FollowableObject* self)
{
    PostLoadPlacedObject(self);
    if (self->id7A0 != -1) {
        self->f7A4 = (void*)FindFirstObjectById(self->world, 4, self->id7A0, self);
    } else {
        self->f7A4 = (void*)FindFirstObjectByIdGathered(self->world, 2, 0x7E, self);
    }
    self->f7AC = (void*)FindFirstObjectById(self->world, 4, self->id7A8, self);
}

extern s32 g_currentTargetFollower;

void HandlePlacedObjectNotification(void* self, s32 kind);
s32 IsInList(void* a, void* b);
void AppendToList(void* list, void* item);
void RemoveFromList(void* table, void* self);

void HandleFollowableObjectNotification(FollowableObject* self, s32 kind)
{
    HandlePlacedObjectNotification(self, kind);
    switch (kind)
    {
    case 2:
        if (g_currentTargetFollower != 0)
        {
            if (IsInList(&((TargetFollower*)g_currentTargetFollower)->list55C, self) != 0)
            {
                RemoveFromList(&((TargetFollower*)g_currentTargetFollower)->list55C, self);
            }
        }
        break;
    case 0xC:
        if (g_currentTargetFollower != 0)
        {
            AppendToList(&((TargetFollower*)g_currentTargetFollower)->list55C, self);
        }
        break;
    case 0xD:
        if (g_currentTargetFollower != 0)
        {
            RemoveFromList(&((TargetFollower*)g_currentTargetFollower)->list55C, self);
        }
        break;
    }
}
