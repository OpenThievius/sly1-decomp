// SPDX-License-Identifier: AGPL-3.0-or-later
// The world-listed objects, 0x139B70 to 0x13B4C0 (its .rodata from 0x249D64, its .data from
// 0x261314): the two alpha state packets (BuildAlphaStatePacket, InitAlphaStatePackets), the
// owned records and the class 0x4D objects on the world's lists, their look, particles and
// packets. Its end is child_group_object.cpp's proved start; its start is not proved by
// retail, only by the change of role from the blend animations (blend_animation.cpp): no
// function before 0x139C38 reads .rodata or .data, so the cut could lie from 0x139B38 to
// 0x139C38. The alpha state packets belong here: their two words are this file's .data, which
// WriteListedObjectParticlePacket reads. The name is ours, after its role.
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
#include "buffered_stream.h"
#include "key_id.h"
#include "world_listed_object.h"
#include "effect_spawner.h"
#include "world.h"
#include "child_group_object.h"
#include "aim_blend_grid.h"
#include "packet_writer.h"
#include "owned_record.h"
#include "object_message.h"
#include "globals.h"
#include "anim_curve.h"
#include "attachment.h"
#include "cursor_animator.h"
#include "texture_table.h"
#include "vu0.h"
#include "placed_object.h"
#include "collider.h"
struct Mat4A;

struct DeferredRequest;


// The file's .data: the two words func_00139C38 registers with func_00139B70 (4-aligned, so
// the .data starts right after text_panel.cpp's; 0x26131C is padding before class 0x3B's).
s32 g_alphaStatePacket1 = 0;
s32 g_alphaStatePacket2 = 0;
extern "C" void* FillMemory(void* p, s32 value, s32 size);

void InitCollider(Collider* self);


struct ContactPairLink { s32 f0; s32 f4; ContactPairLink* f8; Collider* fC; };

struct ContactRowNode;
struct ContactRowList;
struct ContactRowSource;
ContactRowNode* PushContactRow(World* self, ContactRowList* list, ContactRowSource* src);
ContactRow03* UnlinkContactRow(void* unused, ContactRow03** head, Contacts03* key);
void FreePooledContactChain(World* world, Contact03* head);
void ClearRootTries(PlacedObject* self);
void PushFreeSlot(Pool6C* list, void* item);

struct ContactBody;
struct ContactPart;

struct ContactPartVt
{
    u8 pad0[0x10C];
    void (*f10C)(ContactPart* c);
    void (*f110)(ContactPart* c);
};

struct ContactPart
{
    ContactPartVt* vt;
    u8 pad[0x2E4 - 4];
    ContactPart* next;
};

struct ContactSlot
{
    Contact03* f0;
};

struct ContactNode
{
    Contact03* f0;
    ContactNode* f4;
    ContactSlot* f8;
    ContactBody* fC;
};

struct ContactNodeList
{
    ContactNode* head;
};

struct ContactBody
{
    u8 pad0[0x2C8];
    u64 bits2C8;
    u8 pad1[0x2D8 - 0x2D0];
    ContactPart* children;
    u8 pad2[0x414 - 0x2DC];
    ContactBody* next;
    u8 pad3[0x480 - 0x418];
    ContactNodeList* list;
    u8 pad4[0x4B8 - 0x484];
    s32 kind;
    u8 pad5[0x538 - 0x4BC];
    u64 bits538;
};
void ClearRootTries(PlacedObject* self);

void* InitGifPacket(PacketWriter* f);
void AllocatePacketBuffer(PacketWriter* f, s32 n);
void BeginGifTag(PacketWriter* f, s32 a, s32 b, u64 c);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);
void ReserveGifPackedData(PacketWriter* self, u64 prim, s32 nloop, s32 nreg, u64 data, u8** out);
void CloseDmaTag(PacketWriter* f);
void DetachPacketBuffer(PacketWriter* self, u32* outCount, u8** outBegin);

void BuildAlphaStatePacket(s32 idx, void* arg)
{
    PacketWriter f;

    InitGifPacket(&f);
    AllocatePacketBuffer(&f, 4);
    BeginGifTag(&f, 0, 1, 0xE);
    AddGifRegisterWrite(&f, 0x47, 0x7180B);
    AddGifRegisterWrite(&f, 0x42, ((u64)(s64)idx << 2) | 0x40);
    ReserveGifPackedData(&f, 0x54, 0, 0xA, 0x424242412EULL, 0);
    CloseDmaTag(&f);
    DetachPacketBuffer((PacketWriter*)&f, 0, (u8**)arg);
}


void BuildAlphaStatePacket(s32 idx, void* arg);

void InitAlphaStatePackets(void)
{
    BuildAlphaStatePacket(1, &g_alphaStatePacket1);
    BuildAlphaStatePacket(2, &g_alphaStatePacket2);
}

void* PopFreeSlot(Pool6C* pool);
void PushFreeSlot(Pool6C* list, void* item);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
void AppendToList(List01* self, void* item);

OwnedRecord* AcquireOwnedRecord(WorldListedObject* o)
{
    OwnedRecord* s = (OwnedRecord*)PopFreeSlot(&o->world->pool1B40);
    if (!s) {
        return 0;
    }
    FillMemory(s, 0, 0x10C0);
    if (o->mode != 2) {
        s->owner = o;
    } else {
        void* r = PopFreeSlot((Pool6C*)((u8*)o->world + 0x1B4C));
        s->extraRecord = r;
        if (r) {
            FillMemory(r, 0, 0x580);
            s->owner = o;
        } else {
            PushFreeSlot(&o->world->pool1B40, s);
            return 0;
        }
    }
    AppendToList((List01*)&o->members, s);
    return s;
}



void RemoveFromList(List01* list, void* item);
void AppendToList(List01* self, void* item);

void DetachOwnedRecord(OwnedRecord* o)
{
    RemoveFromList((List01*)(&((WorldListedObject*)o->owner)->members), o);
    AppendToList(&g_deferredReleaseListB, o);
}

WorldListedObject* ResetFirstListedObject(World* self)
{
    WorldListedObject* s0 = (WorldListedObject*)self->list1CC0.head;
    if (s0 != 0) {
        u64 b = ((s0->flags & 0xFFFFFFFFF3FFFFFFull) | 0x08000000ull) & 0xFFFFFFFFCFFFFFFFull | 0x20000000ull;
        s0->source = 0;
        s0->fadeDistanceFar = 1e10f;
        s0->flags = b;
        s0->particleCount = 0;
        s0->desc->m02(s0);
    }
    return s0;
}

void HandlePlacedObjectNotification(PlacedObject* self, s32 mode, void* arg);
void StartChildGroupDelay(ChildGroupObject* p, f32 delta);


void AppendToList(List01* self, void* item);
void SetListLinkOffset(List01* self, s32 offset);
void InitPlacedObject(PlacedObject* self);

void InitWorldListedObject(WorldListedObject* self)
{
    AppendToList(&self->world->list1CC0, self);
    InitPlacedObject(self);
    SetListLinkOffset((List01*)&self->members, 0x1090);
    u64 b = self->flags;
    b &= 0xFFFFFFFFCFFFFFFFull;
    b |= 0x20000000ull;
    b &= 0xFFFFFCFFFFFFFFFFull;
    self->fadeDistanceFar = 1e10f;
    b |= 0x10000000000ull;
    self->flags = b;
}

void RemoveFromList(List01* list, void* item);
void AppendToList(List01* self, void* item);
void RegisterPlacedObject(PlacedObject* self);

void LeaveWorldLists(WorldListedObject* self)
{
    RemoveFromList(&self->world->list1CC0, self);
    AppendToList(&self->world->list1CB4, self);
    RegisterPlacedObject(self);
}

void DetachOwnedRecord(OwnedRecord* o);
void RemoveFromList(List01* list, void* item);
void AppendToList(List01* self, void* item);
void UnregisterPlacedObject(PlacedObject* self);

void ReleaseWorldListedObject(WorldListedObject* self)
{
    WorldListedObject* obj = self;
    WordListFrame fr;
    sptr e = (sptr)&obj->members.head;
    fr.list = e;
    fr.link = e;
    sptr old = *(sptr*)&g_activeListFrames;
    s32 link = *(s32*)(e + 8);
    fr.prev = old;
    fr.offset = link;
    *(sptr*)&g_activeListFrames = (sptr)&fr;
    sptr head = obj->members.head;
    fr.link = head + fr.offset;
    sptr node = head;
    while (node != 0) {
        DetachOwnedRecord((OwnedRecord*)node);
        sptr nx = *(sptr*)fr.link;
        fr.link = nx + fr.offset;
        node = nx;
    }
    RemoveFromList(&obj->world->list1CB4, self);
    AppendToList(&g_deferredReleaseListA, self);

    UnregisterPlacedObject(self);
    *(sptr*)&g_activeListFrames = fr.prev;
}


extern s32 g_animRecords;
AnimRecord* FindAnimRecord(s32 key);
void RebuildAnimRecordEntries(WorldListedObject* self);

void AssignAnimRecord(WorldListedObject* self, s32 x)
{
    AnimRecord* r = FindAnimRecord(x);
    self->flagRecord = r;
    if (r == 0) {
        self->flagRecord = (AnimRecord*)g_animRecords;
    }
    if (self->colorCount == 0) {
        self->colorCount = 1;
        s32 i = 0;
        u8* dst = self->color[0];
        do {
            u8* src = (u8*)self->flagRecord + i;
            dst[i] = (u8)((src[4] + 1) >> 1);
            i++;
        } while (i < 4);
    }
    RebuildAnimRecordEntries(self);
}

struct PooledContact;
PooledContact* CreatePooledContact(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, void* a5, void* a6, void* a7);



u64 GetTextureRegisterBits(TextureTable* t, s32 i, s32 j);

void RebuildAnimRecordEntries(WorldListedObject* self)
{
    TextureTable* blk = self->flagRecord->elems;
    s32 a = 1;
    s32 s4 = 0;
    s32 t = blk->entryCount >> 1;
    s32 b;
    s32 i;
    TextureRegWrite* e;

    while (t != 0) {
        t >>= 1;
        a <<= 1;
    }
    a = a << (a < blk->entryCount);
    while (a >= 0x20) {
        a >>= 1;
    }
    b = blk->entryCount;
    if (b < a) {
        s4 = a - blk->entryCount;
    }
    self->regCount = a;
    e = self->regs;
    for (i = 0; i < b; i++) {
        e->value = GetTextureRegisterBits(blk, i, 0);
        e->reg = 6;
        if (i < s4) {
            e[1] = *e;
            e++;
        }
        e++;
    }
}

extern "C" void* FillMemory(void* p, s32 value, s32 size);

// The part of the record from +0x120 that func_0013A128 reads through one pointer.
struct LookSourceTail {
    u8 pad00[0x10];
    s32 still;          // 0x130
    s32 anim;           // 0x134: the anim record's key (AssignAnimRecord)
    u8 pad18[0x20 - 0x18];
    Vec3 curve140;      // 0x140: quadratic coefficients (RemapQuadraticParameter)
    u8 pad2C[0x30 - 0x2C];
    Quad16 q150;        // 0x150
    Vec3 curve160;      // 0x160
    u8 pad4C[0x50 - 0x4C];
    s32 rateOverDuration; // 0x170: non-zero: the rate is the register count over the source's duration
    f32 rateSpan;       // 0x174: the time the register count is spread over
    u8 pad58[0x5C - 0x58];
    s32 colorCount;     // 0x17C
    u8* colors;         // 0x180: colorCount colours of four bytes
    s32 f184;           // 0x184
    u8 pad68[0x70 - 0x68];
    s32 f190;           // 0x190
    f32 f194;           // 0x194
};

// The record func_0013A128 copies a world-listed object's look from (an effect spawner's
// +0x2D0), as far as it reads it.
struct LookSource {
    u8 pad00[0xB0];
    Vec02 vB0;              // 0xB0: a drift; the source is still when it and fC0, fC4 are 0
    f32 fC0;                // 0xC0
    f32 fC4;                // 0xC4
    u8 padC8[0xF4 - 0xC8];
    f32 duration;           // 0xF4: a time the curves and the rate are taken over
    u8 padF8[0x110 - 0xF8];
    Vec3 curve110;          // 0x110: quadratic coefficients (RemapQuadraticParameter)
    u8 pad11C[0x120 - 0x11C];
    LookSourceTail tail;    // 0x120
};

void RemapQuadraticParameter(Vec3* in, f32 s, f32 t, Vec3* out);
void FillLookDirectionBlock(void* out, LookSource* src);

void ApplyLookSourceToListedObject(WorldListedObject* self, LookSource* src)
{
    LookSourceTail* t = &src->tail;
    self->particleMode = src->tail.f190;
    self->f61C = src->tail.f194;
    self->colorCount = src->tail.colorCount;
    for (s32 i = 0; i < self->colorCount; i++) {
        s32 k = self->colorCount - i - 1;
        for (s32 j = 0; j < 4; j++) {
            self->color[k][j] = ((src->tail.colors + i * 4)[j] + 1) >> 1;
        }
    }
    self->f614 = src->tail.f184;
    AssignAnimRecord(self, t->anim);
    FillMemory(&self->q300, 0, 0x10);
    s32 n = self->regCount;
    if (n >= 2) {
        if (t->rateSpan != 0.0f) {
            self->f304 = (f32)n / t->rateSpan;
        } else if (t->rateOverDuration != 0) {
            self->f304 = (f32)n / src->duration;
        } else {
            self->q300 = t->q150;
        }
    }
    RemapQuadraticParameter(&src->curve110, 1.0f / src->duration, 0.0f, (Vec3*)self->curve2F0);
    RemapQuadraticParameter(&src->tail.curve140, 1.0f / src->duration, 0.0f, (Vec3*)self->curve2E0);
    RemapQuadraticParameter(&src->tail.curve160, 1.0f / src->duration, 0.0f, (Vec3*)self->curve310);
    s32 st = src->tail.still;
    self->mode = st;
    s32 still = 0;
    if (st == 0) {
        s32 slow = 0;
        if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(src->vB0))) < 0.0001f
            && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(src->vB0))) < 0.0001f
            && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(src->vB0))) < 0.0001f) {
            slow = 1;
        }
        if (slow && src->fC0 == 0.0f && src->fC4 == 0.0f) {
            still = 1;
        }
    }
    if (still) {
        self->mode = 1;
    }
    FillMemory(self->block330, 0, 0x50);
    if (self->mode == 0) {
        FillLookDirectionBlock(self->block330, src);
    }
}

void UpdatePlacedObject(PlacedObject* self, f32 f);
void ClearRootTries(PlacedObject* self);

void UpdateWorldListedObject(WorldListedObject* self, f32 dt)
{
    UpdatePlacedObject(self, dt);
    ClearRootTries(self);
    AnimRecord* sub = self->flagRecord;
    Camera* g = g_camera;
    s32 hit = 0;
    u32 flags = sub->maskC;
    u32 mask = g->f21C;

    if ((flags & 0x10000000) != 0 || (mask & flags) == mask)
        hit = 1;
    if (hit == 0)
        self->desc->m03(self);
}

void AddObjectListener(BaseObject* self, BaseObject* src);
s32 IsObjectOfKind(BaseObject* list, s32 key);
s32 IsListEmpty(List01* p);

void CopyWorldListedObject(WorldListedObject* self, BaseObject* src)
{
    AddObjectListener(self, src);
    if (IsObjectOfKind(src, 0x50) != 0) {
        EffectSpawner* from = (EffectSpawner*)src;
        self->source = from;
        self->fadeDistanceFar = from->fadeDistanceFar;
        if (IsListEmpty((List01*)from->list314) == 0) {
            self->flags &= 0xFFFFFFFFF3FFFFFFULL;
            self->flags &= 0xFFFFFFFFCFFFFFFFULL;
        }
    }
}

f32 WrapAngle(f32 x);
extern f32 g_gameTime;

// Runs the microprogram at 0x10 over count particles (Vu0::ParticleFilter): a particle whose
// extra.w has passed is dropped, the others are packed down in all three arrays with the
// microprogram's results, and the two bounds come back updated. Returns how many were dropped.
s32 FilterParticleVerticesVu0(const f32* m, u128 scaleBits, Vec02* pos, Vec02* extra, Vec02* items, s32 count, s32 mode,
                              void* boundA, void* boundB)
{
    s32 j = -1;
    s32 dropped = 0;
    f32 now = g_gameTime;
    Vu0::ParticleFilter::Start(*(u128*)m, *(u128*)(m + 4), *(u128*)(m + 8), *(u128*)(m + 12), scaleBits, *(u128*)boundA,
                               *(u128*)boundB, *(u128*)extra, *(u128*)pos);
    for (s32 i = 0; i < count; i++) {
        if (extra[i].w <= now) {
            dropped++;
            Vu0::ParticleFilter::Wait();
        } else {
            j++;
            items[j] = items[i];
            if (mode == 2) {
                items[j].w = WrapAngle(items[i].w + items[i].z * Vu0::ToFloatMoved(scaleBits));
            }
            Vu0::ParticleFilter::Wait();
            Vu0::ParticleFilter::Results(*(u128*)&extra[j], *(u128*)&pos[j]);
        }
        Vu0::ParticleFilter::Next(*(u128*)&extra[i + 1], *(u128*)&pos[i + 1]);
    }
    Vu0::ParticleFilter::Bounds(*(u128*)boundA, *(u128*)boundB);
    return dropped;
}

// One of the two scratchpad transfer buffers (object_properties.cpp): the blocks StartToSprChain sent.
struct SprTransfer {
    void* tags;             // 0x00
    s32 base;               // 0x04
    u32 addrs[8];           // 0x08: each block's scratchpad address
    s32 sizes[8];           // 0x28
    s32 count;              // 0x48
    s32 state;              // 0x4C: 2 while its blocks are worked on
};

extern s32 g_sprTransferIndex;
extern SprTransfer g_sprTransfers[2];
extern void* g_toSprChannel;

// Block n of the current scratchpad transfer.
struct SprBlock {
    static u32 Of(s32 n)
    {
        return g_sprTransfers[g_sprTransferIndex].addrs[n];
    }
};

struct SpinRecord_158480;
void TurnMatrixBySpin(SpinRecord_158480* spin, f32 dt, f32* out);
struct DmaChannel;
extern "C" s32 WaitDmaChannel(DmaChannel* ch, s32 mode, s32 timeout);
void StartToSprChain(s32 size, ...);
void StartFromSprChain(void* first, ...);

// The object's filter mode (0x618), read into the caller's variable.
static inline void GetParticleMode(const WorldListedObject* self, s32* mode)
{
    *mode = self->particleMode;
}

// Steps the object's particles: each owned record's three arrays go to the scratchpad (the
// next record's are sent while this one's are filtered), FilterParticleVerticesVu0 drops the
// expired particles and packs the rest into the record's other bank with the bounds updated,
// and an emptied record is detached. With no particle left the object ends itself (slot 3);
// otherwise its centre and radius are set from the bounds.
//
// The bounds are brace-initialised union-first vectors: the union member's CLOBBER orders each
// bound's stores (docs/toolchain/large-functions.md, "A brace initialiser's union member is a
// CLOBBER"). The loop's registers follow from loop.c's count of the body, 97 insns in its first
// pass (docs/toolchain/loops.md, "What loop.c counts"): the channel is read through a local (a
// load and a copy to the argument register), and the mode through GetParticleMode, whose
// out-parameter makes the variable an ADDRESSOF until purge_addressof, after cse1: its read is
// then a copy that loop.c counts and cse2 folds.
void StepListedObjectParticles(WorldListedObject* self, f32 dt)
{
    Quadratic16 lo = {{3.4028235e+38f}, 3.4028235e+38f, 3.4028235e+38f, 0.0f};
    Quadratic16 hi = {{-3.4028235e+38f}, -3.4028235e+38f, -3.4028235e+38f, 0.0f};
    Vec02 mat[4];
    WordListFrame fr;
    sptr e = (sptr)&self->members.head;
    fr.list = e;
    fr.link = e;
    sptr old = *(sptr*)&g_activeListFrames;
    s32 link = *(s32*)(e + 8);
    fr.prev = old;
    fr.offset = link;
    *(sptr*)&g_activeListFrames = (sptr)&fr;
    TurnMatrixBySpin((SpinRecord_158480*)((u8*)self + 0x330), dt, (f32*)mat);
    sptr head = *(sptr*)fr.link;
    fr.link = head + fr.offset;
    OwnedRecord* node = (OwnedRecord*)head;
    Vec02* p = node->points[node->bank];
    StartToSprChain(node->count * 16, p, node->count * 16, p + 0x2C, node->count * 16, p + 0x58, 0, 0);
    while (node != 0) {
        void* ch = g_toSprChannel;
        WaitDmaChannel((DmaChannel*)ch, 0, 0);
        g_sprTransferIndex = 1 - g_sprTransferIndex;
        SprTransfer* t = &g_sprTransfers[g_sprTransferIndex];
        t->state = 2;
        OwnedRecord* next = *(OwnedRecord**)fr.link;
        fr.link = (sptr)next + fr.offset;
        if (next != 0) {
            p = next->points[next->bank];
            StartToSprChain(next->count * 16, p, next->count * 16, p + 0x2C, next->count * 16, p + 0x58, 0, 0);
        }
        u128 w = Vu0::ScalarInGpr(dt);
        s32 mode;
        GetParticleMode(self, &mode);
        s32 used = FilterParticleVerticesVu0((const f32*)mat, w, (Vec02*)SprBlock::Of(0), (Vec02*)SprBlock::Of(1), (Vec02*)SprBlock::Of(2),
                                             node->count, mode, &lo, &hi);
        s32 nb = (node->bank + 1) & 1;
        p = node->points[nb];
        StartFromSprChain(p, p + 0x2C, p + 0x58, 0);
        node->count -= used;
        self->particleCount -= used;
        if (node->count <= 0) {
            DetachOwnedRecord(node);
        } else {
            node->bank = nb;
        }
        node = next;
    }
    if (self->particleCount <= 0) {
        self->desc->m03(self);
    } else {
        Vec02 center;
        Vu0::Q(center) = Vu0::MulXSum(Vu0::Q(lo), Vu0::Scalar(0.5f), Vu0::Q(hi), Vu0::Scalar(0.5f));
        self->desc02()->m1D(self, &center);
        self->f2A4 = self->boundRadius = Vu0::Distance(center, *(Vec02*)&hi);
    }
    *(sptr*)&g_activeListFrames = fr.prev;
}

extern f32 g_gameClock[];
void StepListedObjectParticles(WorldListedObject* self, f32 dt);
void EvaluateHermiteVectorSegment(f32 dur, const Vec02* p0, const Vec02* m0, const Vec02* p1, const Vec02* m1, f32 t, f32 k, Vec02* pos, Vec02* vel, Vec02* acc);

// One entry of a record's extra block: the two vectors a mode-2 point's segment ends on.
struct VecPair { Vec02 a; Vec02 b; };

// Class 0x4D's move slot. Mode 0 steps the particles (StepListedObjectParticles). Otherwise
// each member record's live points are copied from the bank in use to the other, closing the
// gaps of the points whose time has come: a mode-1 point moves by its velocity, a mode-2 point
// along its Hermite segment (its extra pair moves down with it); the w's and the third
// vector follow, the angle advanced when f618 is 2. The record then switches banks, or is
// detached when empty. The object's centre and radius are set from the points' bounds, or the
// object is removed when it has none left.
//
// The four pointers named at the top of the loop body and the two named before the third
// vector's copy are what loop.c's giv combination needs (docs/toolchain/loops.md, "Which giv
// absorbs the memory references"): each address of the body is then a pointer plus a
// constant, no `base + 16j` is computed twice, and the third vector's pointers, used more
// than once, take every memory reference of their array; the first two pairs are left as
// registers of their own for the call. The time left is the end's own variable, and the
// record's extra block is read from the record at each use.
void MoveWorldListedObject(WorldListedObject* self, f32 dt)
{
    if (self->mode == 0) {
        StepListedObjectParticles(self, dt);
        return;
    }
    Quadratic16 lo = {{3.4028235e+38f}, 3.4028235e+38f, 3.4028235e+38f, 0.0f};
    Quadratic16 hi = {{-3.4028235e+38f}, -3.4028235e+38f, -3.4028235e+38f, 0.0f};
    WordListFrame fr;
    sptr e = (sptr)&self->members.head;
    fr.list = e;
    fr.link = e;
    sptr old = *(sptr*)&g_activeListFrames;
    s32 link = *(s32*)(e + 8);
    fr.prev = old;
    fr.offset = link;
    *(sptr*)&g_activeListFrames = (sptr)&fr;
    sptr head = *(sptr*)fr.link;
    fr.link = head + fr.offset;
    OwnedRecord* node = (OwnedRecord*)head;
    while (node != 0) {
        Vec02* cur = node->points[node->bank];
        s32 out = 0;
        s32 removed = 0;
        s32 nb = (node->bank + 1) & 1;
        Vec02* nxt = node->points[nb];
        for (s32 j = 0; j < node->count; j++) {
            Vec02* pos = &cur[j];
            Vec02* vel = &cur[0x2C + j];
            Vec02* npos = &nxt[out];
            Vec02* nvel = &nxt[0x2C + out];
            f32 end = vel->w;
            if (end <= g_gameClock[1]) {
                removed++;
                continue;
            }
            switch (self->mode) {
            case 1: {
                Vu0::Vec v = Vu0::Vec::Of(*vel);
                *(Vu0::Vec*)nvel = v;
                *(Vu0::Vec*)npos = Vu0::MulAddX(Vu0::Vec::Of(*pos), v, Vu0::Vec::Scalar(dt));
                break;
            }
            case 2: {
                end -= g_gameClock[1];
                EvaluateHermiteVectorSegment(end, pos, vel, &((VecPair*)node->extraRecord)[j].a, &((VecPair*)node->extraRecord)[j].b, end <? dt, 1.0f, npos, nvel, 0);
                if (out != j) {
                    ((VecPair*)node->extraRecord)[out] = ((VecPair*)node->extraRecord)[j];
                }
                break;
            }
            }
            npos->w = pos->w;
            nvel->w = vel->w;
            Vec02* rec = &cur[0x58 + j];
            Vec02* nrec = &nxt[0x58 + out];
            *nrec = *rec;
            if (self->particleMode == 2) {
                nrec->w = WrapAngle(rec->w + rec->z * dt);
            }
            Vu0::Q(lo) = Vu0::Min(Vu0::Q(lo), Vu0::Q(*npos));
            Vu0::Q(hi) = Vu0::Max(Vu0::Q(hi), Vu0::Q(*npos));
            out++;
        }
        node->count -= removed;
        self->particleCount -= removed;
        if (node->count <= 0) {
            DetachOwnedRecord(node);
        } else {
            node->bank = nb;
        }
        sptr next = *(sptr*)fr.link;
        fr.link = next + fr.offset;
        node = (OwnedRecord*)next;
    }
    if (self->particleCount <= 0) {
        self->desc->m03(self);
    } else {
        Vec02 center;
        Vu0::Q(center) = Vu0::MulXSum(Vu0::Q(lo), Vu0::Scalar(0.5f), Vu0::Q(hi), Vu0::Scalar(0.5f));
        self->desc02()->m1D(self, &center);
        self->f2A4 = self->boundRadius = Vu0::Distance(center, *(Vec02*)&hi);
    }
    *(sptr*)&g_activeListFrames = fr.prev;
}

struct DeferredRadiusRequest { void (*fn)(void* self); s32 zero; s32 count; u8 pad0[0x50 - 0x0C]; f32 radius; u8 pad1[0x60 - 0x54]; void* owner; u8 pad2[0x80 - 0x64]; };
struct Src_13AD08 { u8 pad[0x40]; f32 scale; };

extern "C" void* FillMemory(void* p, s32 value, s32 size);
void QueueDeferredRequest(DeferredRequest* src);
void WriteListedObjectParticlePacket(void* self);

void SubmitWorldListedObjectBlock(WorldListedObject* owner, s32 unused, Src_13AD08* src)
{
    DeferredRadiusRequest blk;
    FillMemory(&blk, 0, (u32)0x80);
    blk.count = 0xF;
    blk.fn = WriteListedObjectParticlePacket;
    blk.zero = 0;
    if (src != 0) {
        blk.radius = src->scale;
    } else {
        blk.radius = 1.0f;
    }
    blk.owner = owner;
    QueueDeferredRequest((DeferredRequest*)&blk);
}

extern f32 g_gameClock[];
extern s32 g_alphaStatePacket1;
extern s32 g_alphaStatePacket2;
s32 IsListEmpty(List01* p);
void PopBackMemoryMark(void);

// An object of a spawner's list as func_0013AD80 draws it: the record whose 0x7C gives the frame.
struct Mat4x4Copy { u128 r[4]; };
struct ViewedPartRecord { u8 pad0[0x7C]; PlacedObject* frame; };
struct ViewedPart : PlacedObject { ViewedPartRecord* rec; };
// A mesh of a listed object's own list: two banks of vertex data, the bank in use and the count.
struct ListedMesh { u8 bank[2][0x840]; s32 current; s32 count; };
// A matrix the object is drawn at and its fade (0x50 bytes, AllocateBackMemory).
struct ViewedFrame { f32 m[4][4]; f32 fade; u8 pad44[0x50 - 0x44]; };

void PushBackMemoryMark();
void* AllocateBackMemory(s32 size);
s32 CountListItems(List01* list);
s32 IsObjectAttached(BaseObject* self);
s32 ComputeCameraDistanceFade(Camera* self, u128 d, f32* fade, f32 radius, f32 x);
void BuildMatrixFromRotationAndTranslation(const Vec02* pos, const Mat02* rot, Mat4A* out);
void BeginDmaTag(PacketWriter* w);
void CloseDmaTag(PacketWriter* w);
void FlipVifBaseOffset();
void ReserveVifUnpack(PacketWriter* s, s32 a, s32 size, s32 d, s32* outSize, u8** outCursor);
void CopyWordsToWriter(PacketWriter* s, s32 a1, s32 size, u32* src, s32 a4);
void WriteVifUnpack(PacketWriter* w, s32 tag, s32 size, void* src, s32 addr, s32 flag);
void WriteVifStcycl(PacketWriter* b, u32 x, u32 y);
void WriteVifMscal(PacketWriter* w, void* addr);
void WriteVifFlush(PacketWriter* w);
extern const f32 g_identityMatrix4[28];
extern u8 g_listedParticleProgram0[];
extern u8 g_listedParticleProgram1[];
extern u8 g_listedParticleProgram2[];

// A walk of a list on g_activeListFrames, popped when it ends.
struct ViewListWalk {
    void* list;
    u8* link;
    s32 offset;
    ViewListWalk* prev;
    ViewListWalk(void* l)
    {
        list = l;
        link = (u8*)l;
        offset = ((List01*)l)->offset;
        prev = (ViewListWalk*)g_activeListFrames;
        g_activeListFrames = (ListFrame*)this;
    }
    ~ViewListWalk() { g_activeListFrames = (ListFrame*)prev; }
    void* Next()
    {
        void* n = *(void**)link;
        link = (u8*)n + offset;
        return n;
    }
};

// The frames of the objects in view (or one identity frame), then one VIF packet per mesh: the
// shared words for the first two, and for each frame its matrix, fade and the mesh's three
// vertex banks. The frame loop's `&frames[i]` is reduced by loop.c's second pass, which this
// file's flags allow (config/cflags.tsv; docs/toolchain/loops.md, "A threshold of 94").
void WriteListedObjectParticlePacket(void* self)
{
    DeferredRadiusRequest* req = (DeferredRadiusRequest*)self;
    ViewedFrame one;
    ViewedFrame* frames;
    s32 count;
    PushBackMemoryMark();
    WorldListedObject* obj = (WorldListedObject*)req->owner;
    if (obj->source != 0 && IsListEmpty((List01*)(((EffectSpawner*)obj->source)->list314)) == 0) {
        count = 0;
        ViewListWalk walk(((EffectSpawner*)obj->source)->list314);
        frames = (ViewedFrame*)AllocateBackMemory(CountListItems((List01*)(((EffectSpawner*)obj->source)->list314)) * sizeof(ViewedFrame));
        ViewedFrame* cur = frames;
        ViewedPart* e;
        while ((e = (ViewedPart*)walk.Next()) != 0) {
            if ((e->visibilityMask & g_camera->f21C) == g_camera->f21C && IsObjectAttached(e)) {
                Vec02 pos;
                Mat02 rot;
                if (e->rec->frame != 0) {
                    pos = e->rec->frame->v140;
                    rot = e->rec->frame->m110;
                } else {
                    pos = e->v140;
                    if (e->parent != 0)
                        rot = ((PlacedObject*)e->parent)->m110;
                    else
                        rot = g_identityMatrix;
                }
                f32 radius = obj->boundRadius;
                Camera* cam = g_camera;
                u128 d = Vu0::Sub(Vu0::Add(Vu0::Rotate(rot, Vu0::Vec::Of(obj->pos)), Vu0::Vec::Of(pos)), Vu0::Vec::Of(cam->position)).q;
                u128 ones = Vu0::Ones();
                if ((Vu0::PlaneSigns(Vu0::Q(cam->planes[0]), Vu0::Q(cam->planes[1]), Vu0::Q(cam->planes[2]), d, ones, Vu0::Scalar(radius)) ^ 0xF0) == 0) {
                    if (ComputeCameraDistanceFade(cam, d, &cur->fade, radius, e->fadeDistanceFar) != 0) {
                        BuildMatrixFromRotationAndTranslation(&pos, &rot, (Mat4A*)cur);
                        cur++;
                        count++;
                    }
                }
            }
        }
        if (count == 0) {
            PopBackMemoryMark();
            return;
        }
    } else {
        frames = &one;
        count = 1;
        *(Mat4x4Copy*)one.m = *(const Mat4x4Copy*)g_identityMatrix4;
        one.fade = req->radius;
    }
    s32 sent = 0;
    BeginDmaTag(&g_vifPacketWriter);
    ViewListWalk walk(&obj->members);
    ListedMesh* mesh;
    while ((mesh = (ListedMesh*)walk.Next()) != 0) {
        FlipVifBaseOffset();
        if (sent++ < 2) {
            f32* p;
            s32* q;
            ReserveVifUnpack(&g_vifPacketWriter, 0xC, 1, 5, 0, (u8**)&p);
            Camera* cam = g_camera;
            p[0] = cam->fC0;
            p[1] = cam->fD4;
            p[2] = obj->f61C;
            p[3] = g_gameClock[1];
            ReserveVifUnpack(&g_vifPacketWriter, 0xC, 1, 6, 0, (u8**)&q);
            q[0] = 0;
            if (obj->f614 != 0)
                q[0] |= 1;
            q[1] = obj->colorCount;
            q[2] = obj->regCount;
            *(f32*)&q[3] = g_gameClock[5];
            CopyWordsToWriter(&g_vifPacketWriter, 0xE, obj->colorCount, (u32*)obj->color, 0x30 - obj->colorCount);
            CopyWordsToWriter(&g_vifPacketWriter, 8, 1, (u32*)obj->curve2F0, 1);
            CopyWordsToWriter(&g_vifPacketWriter, 8, 1, (u32*)obj->curve2E0, 2);
            CopyWordsToWriter(&g_vifPacketWriter, 8, 1, (u32*)&obj->q300, 3);
            CopyWordsToWriter(&g_vifPacketWriter, 8, 1, (u32*)obj->curve310, 4);
            CopyWordsToWriter(&g_vifPacketWriter, 0xC, 4, (u32*)((void*)((obj->flagRecord->flags & 1) != 0 ? g_alphaStatePacket2 : g_alphaStatePacket1)), 0x30);
            WriteVifUnpack(&g_vifPacketWriter, 0xC, obj->regCount, obj->regs, 0xF, 0);
        }
        u8* bank = mesh->bank[mesh->current];
        u16 hdr[3];
        hdr[0] = 0x34;
        hdr[1] = mesh->count * 10 + 0x34;
        hdr[2] = mesh->count;
        CopyWordsToWriter(&g_vifPacketWriter, 9, 1, (u32*)hdr, 0);
        for (s32 i = 0; i < count; i++) {
            ViewedFrame* f = &frames[i];
            Vec02 fade;
            CopyWordsToWriter(&g_vifPacketWriter, 0xC, 4, (u32*)f, 7);
            fade.x = f->fade;
            CopyWordsToWriter(&g_vifPacketWriter, 0xC, 1, (u32*)&fade, 0xB);
            WriteVifStcycl(&g_vifPacketWriter, 1, 10);
            if (obj->particleMode == 1)
                WriteVifUnpack(&g_vifPacketWriter, 0xC, mesh->count, bank + 0x2C0, hdr[0] + 1, 0);
            WriteVifUnpack(&g_vifPacketWriter, 0xC, mesh->count, bank + 0x580, hdr[0] + 2, 0);
            WriteVifUnpack(&g_vifPacketWriter, 0xC, mesh->count, bank, hdr[0] + 3, 0);
            WriteVifStcycl(&g_vifPacketWriter, 1, 1);
            switch (obj->particleMode) {
            case 0:
                WriteVifMscal(&g_vifPacketWriter, g_listedParticleProgram0);
                break;
            case 1:
                WriteVifMscal(&g_vifPacketWriter, g_listedParticleProgram1);
                break;
            case 2:
                WriteVifMscal(&g_vifPacketWriter, g_listedParticleProgram2);
                break;
            }
            WriteVifFlush(&g_vifPacketWriter);
        }
    }
    CloseDmaTag(&g_vifPacketWriter);
    PopBackMemoryMark();
}



void RebuildAnimRecordEntries(WorldListedObject* node);

void UpdateMatchingListedObjects(s32 mask)
{
    WorldListedObject* node;
    s32 v;
    s32 go;
    ListFrame frame;

    if (mask != 0) {
        node = (WorldListedObject*)g_currentWorld->list1CB4.head;

        if (node != 0) {
            do {
                v = node->flagRecord->maskC;
                go = 0;
                if ((v & 0x10000000) != 0 || (mask & v) == mask) {
                    go = 1;
                }
                if (go) {
                    RebuildAnimRecordEntries(node);
                }
                node = node->next;
            } while (node != 0);
        }
    }
}
