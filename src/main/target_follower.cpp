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

INCLUDE_RODATA(jtbl_0024A7F0);
ASM_FUNC(func_0016D128);

INCLUDE_RODATA(jtbl_0024A810);
ASM_FUNC(func_0016D1E0);

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

ASM_FUNC(func_0016D490);

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

ASM_FUNC(func_0016D828);

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

INCLUDE_RODATA(D_0024A824);
INCLUDE_RODATA(jtbl_0024A830);
ASM_FUNC(func_0016DAC0);

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

INCLUDE_RODATA(D_0024A844);
ASM_FUNC(func_0016DE20);

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
