// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "vu0.h"
#include "child_group_object.h"
#include "attachment.h"
#include "shapes.h"
#include "object_link.h"
#include "stream_reader.h"
#include "stream_reader_window.h"
#include "key_id.h"
#include "identity_key.h"
#include "pad_record.h"
#include "game_progress.h"
#include "globals.h"
#include "movie_player.h"
#include "thread_params.h"
#include "packet_writer.h"
#include "list_iter.h"
#include "functions/anim_record.h"
#include "functions/base_object.h"
#include "functions/collider.h"
#include "functions/collider_span.h"
#include "functions/disc_access.h"
#include "functions/display.h"
#include "functions/game_clock.h"
#include "functions/heap.h"
#include "functions/iop_commands.h"
#include "functions/matrix.h"
#include "functions/mpeg_decoder.h"
#include "functions/pad_input.h"
#include "functions/placed_object.h"
#include "functions/point_graph.h"
#include "functions/pooled_object.h"
#include "functions/ring_buffer.h"
#include "functions/sound_system.h"
#include "functions/text_format.h"
#include "functions/warp_menu.h"
struct BufferedStream;
struct Device_20B0B0;
struct MpegHandle;
struct Outer_20AE40;
struct S_20B0C0;

struct Mat02;
struct Vec02;


// Types other files define, named by the parameters of their functions declared here.
struct ScaledTransform;

ObjectLink g_contactListObjectLinks[1] = { { 2, 0x317, 0x6B0 } };
f32 g_movieFrameLookahead = 0.5f;
const char* g_movieTitles[16] = {
    "The Secret Police File",
    "The Tokyo Police File",
    "The Making Of Sly Cooper",
    "Commercials & Outtakes",
    "Tide of Terror",
    "Raleigh Hung out to Dry",
    "Sunset Snake Eyes",
    "Muggshot Busted",
    "Vicious Voodoo",
    "Mz Ruby Vexed",
    "Fire in the Sky",
    "The Panda King on Ice",
    "The Cold Heart of Hate",
    "Ten Seconds",
    "The Thievius Raccoonus",
    "Credits"
};
MoviePlayer g_moviePlayer;
s32 g_movieChecksumFailed;
s32 g_keyedMovieWatched;

extern u8 g_gameClock[];





// A transfer to the IOP's memory, as StartIopDma takes it.
struct IopDmaTransfer {
    s32 src;    // the EE address
    s32 dest;   // the IOP address
    void* size;
    s32 attr;
};

extern "C" void SyncDataCache(s32 a);
extern "C" void* StartIopDma(IopDmaTransfer* span, s32 n);
extern "C" s32 GetIopDmaStatus(void* obj);







extern u8 g_movieDataRingBuffer[];




// A block of data the decoder hands a stream callback.
struct MovieDataBlock { u8 pad0[8]; u8* data; s32 size; };

struct StreamSink;


void* InitGifPacket(PacketWriter* self);
void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);
void AddGifUvEntry(PacketWriter* self,s32 a,s32 b);
void AddGifXyzfEntry(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);
void EndGifPacket(PacketWriter* self);
void AddGifImageTag(PacketWriter* self, s32 count);

struct AttachedTransformFrame {
    Vec02 q00;
    Vec02 q10;
    Vec02 q20;
    Mat02 tbl30;
    Vec02 q60;
    u8 pad70[0xA0 - 0x70];
    Mat4A blkA0;
    u8 padE0[0xF0 - 0xE0];
    Mat4A blkF0;
};





void* MultiplyMatrices(void* out, void* b, void* in);

extern s32 g_gifChannel;

extern "C" s32 AwaitSemaphore(s32 a);

extern u8 g_movieCrcTable[];

extern s32 D_002626CC;

void ResetMpegDecoder(S_20B0C0* d);



extern const u32 g_movieKeys[128];

extern "C" void* FillMemory(void* p, s32 value, s32 size);

struct SameMovieKey {
    static s32 Of(IdentityKey* a, const IdentityKey* b)
    {
        if (a == b) return 1;
        if (!a) return 0;
        if (!b) return 0;
        return ((a->words[2] ^ a->words[6]) ^ (b->words[2] ^ b->words[6])) == 0;
    }
};
struct KeyIdOfMovie {
    static s32 Of(KeyId* p, IdentityKey* key)
    {
        ClearKeyId(p);
        s32 ok;
        if (!key) {
            ok = 0;
        } else {
            u32 t = key->words[1] ^ key->words[7];
            p->k1 = t;
            p->k0 = key->words[0] ^ key->words[5];
            ok = t != 0;
        }
        return ok;
    }
};

extern u8 g_packetBufferMemory[];
extern u8 g_screenFade[];
extern s32 g_discSectorCheckState;

struct GameClock;
struct ScreenFade;
s32 GetMpegDecoderStatus(Device_20B0B0* device);
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

extern u8 g_movieDecodeThreadStack[];
extern u8 g_globalPointer[];
extern s32 g_movieDecodeThread;

s32 MakeThread(ThreadParams* p);
void RunThread(s32 thread, void* arg);



struct ReaderEmpty {
    static bool Of(StreamReaderWindow* b) { return b->readyLength == b->usedLength; }
};
struct Ctx_20A220;
struct Args_20A220;
typedef s32 (*Handler_20A220)(Ctx_20A220* ctx, Args_20A220* args, void* arg);
s32 DemultiplexBuffer(Ctx_20A220* ctx, s32 a, s32 b);


extern "C" void PostSemaphore(s32 a);


extern u8 g_movieDecoderWork[];
extern u8 g_moviePictureBuffer[];
extern u8 g_movieVideoRingBuffer[];
extern u8 g_movieUploadPacket[];
extern u8 g_movieDrawPacket[];
extern u8 D_00148D68[];

s32 CreateMpegDecoder(void* self, void* a, s32 b);
Handler_20A220 SetStreamCallback(Ctx_20A220* self, s32 idx, s32 key, Handler_20A220 handler, void* arg);
s32 SetMpegCallback(void* self, s32 a, void* fn, void* arg);

s32 FindKeyIndex(IdentityKey* key);
u8* GetMovieTitle(s32 index);
void QueueMovieByIndex(s32 idx);
void QueueMovieWithSuccessor(s32 idx, u32 n);
void RunMovieDecodeThread(void);
void CreateMovieDecodeThread(void);
void InitIopRingSink(IopRingSink* self, s32 a1, s32 a2);
void ResetIopRingSink(IopRingSink* c);
s32 WriteIopRingBlock(IopRingSink* p, s32 size, u8* buf);
void UpdateIopRingSink(IopRingSink* self);
s32 StartMovieStream(MovieStream* self);
void ResetMovieStream(MovieStream* self);
void StopMovieStream(MovieStream* self);
s32 FeedMovieStream(MovieStream* self, s32 left, u8* right);
void UpdateMovieStream(MovieStream* self);
s32 AcceptMovieDataIntoRing(void* a0, MovieDataBlock* a1, MoviePlayer* a2);
void PassMovieDataToStream(void* a0, MovieDataBlock* a1, MoviePlayer* a2);
s32 FlushMovieToIpu(void* u0, void* u1, MoviePlayer* self);
s32 FeedMovieDecoderWithoutWaiting(void* a0, s32 a1, MoviePlayer* a2);
s32 AcceptMovieDecoderEvent(void);
void UploadMovieFrame(void* p, s32 addr, s32 w, s32 h);
void DrawMovieFrame(void* self, s32 a1, s32 a2);
void QueueMovie(MoviePlayer* self, void* p);
void PlayQueuedMovies(MoviePlayer* self);
void PlayMovie(MoviePlayer* self, IdentityKey* key);
void InitMoviePlayback(MoviePlayer* self, void* v);
void AdvanceCodeChecksum(MoviePlayer* self);
void StepMovieFrame(MoviePlayer* self);
void FinishMovie(MoviePlayer* self);
s32 FeedMovieDecoder(MoviePlayer* self, s32 wait);

void InitContactListObject(ContactListObject* self)
{
    InitChildGroupObject(self);
    self->ready = 1;
}

void LoadContactListObject(ContactListObject* self, BufferedStream* stream)
{
    u64 mask = (u64)(s64)-0x301;
    u64 set = 0x8000;
    LoadChildGroupObject(self, stream);
    ResolveObjectLinks(self, 1, g_contactListObjectLinks);
    mask <<= 16;
    mask |= 0xFFFF;
    mask <<= 16;
    mask |= 0xFFFF;
    set <<= 25;
    self->flags = (self->flags & mask) | set;
}

void UnregisterContactListObject(ContactListObject* self)
{
    UnregisterCollider(self);
    void* p = self->animationPlayer;
    if (p != 0) {
        StopAnimationPlayer((AnimationPlayer*)p);
        self->animationPlayer = 0;
    }
}

void MoveContactListObject(ContactListObject* self, void* b, f32 x)
{
    if (self->ready != 0) {
        BuildBasisFromX(&self->v150, &self->rot);
    }
    s32 s1 = (s32)self->positionAttachment;
    s32 s0 = (s32)self->orientationAttachment;
    self->positionAttachment = 0;
    self->orientationAttachment = 0;
    MoveCollider(self, x, b);
    self->positionAttachment = (Attachment*)s1;
    self->orientationAttachment = (Attachment*)s0;
}


void LaunchContactListObject(ContactListObject* self, PlacedObject* a, Vec02* v)
{
    self->anchorObject = a;
    self->anchorOffset = *v;
    if (self->animation != 0) {
        CreateAnimationPlayerWithoutPresetTargets(self->animation, self, 0, (AnimationPlayer**)&self->animationPlayer, 0.0f, 1.0f);
    }
    if (self->ready != 0) {
        s32 still = 0;
        if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(self->v150))) < 0.0001f
            && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(self->v150))) < 0.0001f
            && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(self->v150))) < 0.0001f) {
            still = 1;
        }
        if (!still) {
            Mat02 m;
            BuildBasisFromX(&self->v150, &m);
            self->desc02()->m1E(self, &m);
        }
    }
}

void ApplyContactListAttachments(ContactListObject* self, void* in1, void* in2)
{
    AttachedTransformFrame f;

    if ((self->flags & 0x100000000ULL) == 0) {
        if (self->positionAttachment == 0 && self->orientationAttachment == 0) {
            ApplyPlacedObjectTransform(self, (Camera*)in1, (ScaledTransform*)in2);
        } else {
            if (self->positionAttachment != 0) {
                self->positionAttachment->vt->getPos(self->positionAttachment, 0.0f, &f.q00, &f.q10);
            } else {
                f.q00 = D_00248D30;
            }
            if (self->orientationAttachment != 0) {
                self->orientationAttachment->vt->getRot(self->orientationAttachment, 0.0f, &f.tbl30, &f.q20);

            } else {
                f.tbl30 = g_identityMatrix;
            }
            BuildPlacedObjectTransform(self, (Quad16*)in2, (ScaledTransform*)&f.blkA0);
            BuildMatrixFromRotationAndTranslation((const Vec02*)&f, &f.tbl30, (Mat4A*)&f.q60);
            MultiplyMatrices(&f.blkF0, &f.blkA0, &f.q60);
            f.blkA0 = f.blkF0;
            ApplyPlacedObjectTransform(self, (Camera*)in1, (ScaledTransform*)&f.blkA0);
        }
    }
}

s32 TestContactListMayContact(ContactListObject* self, void* key)
{
    if (key == self->f6E4) {
        return 1;
    }
    for (s32 i = 0; i < self->count6BC; i++) {
        if (MatchesObjectId((BaseObject*)key, self->items6C0[i]) != 0) {
            return 1;
        }
    }
    for (s32 j = 0; j < self->count6D0; j++) {
        if (IsObjectOfKind((BaseObject*)key, self->items6D4[j]) != 0) {
            return 1;
        }
    }
    return TestCollidersMayContact(self, (Collider*)key);
}

void AddContactListId(ContactListObject* self, s32 item)
{
    u32 n = self->count6BC;
    if (n < 4) {
        self->items6C0[n] = item;
        self->count6BC = n + 1;
    }
}

void AddContactListKind(ContactListObject* self, s32 value)
{
    s32 n = self->count6D0;
    if ((u32)n < 4) {
        self->items6D4[n] = value;
        self->count6D0 = n + 1;
    }
}

// Class 0x3D, a contact-list object without gravity that keeps a velocity of its own.
struct ContactListGlider : ContactListObject {
    f32 speed6F0;           // 0x6F0: the speed of the velocity it keeps (func_0018DDD8)
    f32 rate6F4;            // 0x6F4: how fast it turns to that velocity (func_0018DE70)
    f32 f6F8;               // 0x6F8
    f32 time6FC;
    Vec02 v700;             // 0x700: the velocity it keeps
};

typedef char check_ContactListGlider[sizeof(ContactListGlider) == 0x710 ? 1 : -1];

void AddColliderForce(void* a, void* b);

void InitContactListObjectWithoutGravity(ContactListObject* self)
{
    InitContactListObject(self);
    self->gravity = D_00248D30;
}

void LaunchContactListObjectWithoutGravity(ContactListGlider* self, PlacedObject* target, Vec02* offset)
{
    LaunchContactListObject(self, target, offset);
    u128 speed = Vu0::ScalarAt(self->speed6F0);
    Vu0::Q(self->v700) = Vu0::MulX(Vu0::NormalizeOrMoved(Vu0::Q(self->v150), Vu0::Q(g_unitXVector)), speed);
}

void StepContactListObjectWithoutGravity(ContactListGlider* self, f32 dt)
{
    Vec02 accel;
    Vec02 t;
    StepCollider(self, dt);
    Vu0::Q(t) = Vu0::FromFloat(dt);
    Vu0::Q(accel) = Vu0::DivX(Vu0::Sub(Vu0::Q(self->v700), Vu0::Q(self->v150)), Vu0::Q(t));
    ClampVectorLength(&accel, &accel, self->rate6F4);
    AddColliderForce(self, &accel);
}

void LaunchContactListObject(ContactListObject* self);
extern f32 g_gameTime;

void LaunchTimedContactListObject(ContactListGlider* self, PlacedObject* target, Vec02* offset)
{
    Mat02 rot;
    Vec02 d;
    Vec02 e;
    Vec02 pos;
    ColliderSpan hit;
    LaunchContactListObject(self, target, offset);
    f32 speed = self->speed6F0;
    if (0.0f < speed) {
        self->time6FC = g_gameTime + speed;
    } else {
        ComputeObjectFrameAtTime(self->anchorObject, 0, &pos, &rot, 0, 0, g_movieFrameLookahead);
        Vu0::Q(pos) = Vu0::Add(Vu0::Rotate(rot, Vu0::Q(self->anchorOffset)), Vu0::Q(pos));
        Vu0::Q(d) = Vu0::MulX(Vu0::Q(self->v150), Vu0::Scalar(-0.5f));
        ClampVectorLength(&d, &d, self->rate6F4 * 0.75f);
        Vu0::Q(e) = Vu0::MulAddX(Vu0::Q(d), Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->pos)), Vu0::Scalar(1.5f));
        FindSegmentSphereSpan((Vec02*)&D_00248D30, &d, &e, self->rate6F4, 1, &hit);
        f32 x = hit.time[1];
        f32 m = 0.25f;
        m = m >? x;
        self->time6FC = g_gameTime + 1.0f / m;
    }
}

struct GliderListFrame {
    void* base;
    void* cur;
    s32 off;
    GliderListFrame* prev;
    GliderListFrame(List01* l)
    {
        cur = l;
        base = l;
        GliderListFrame* p = (GliderListFrame*)g_activeListFrames;
        off = l->offset;
        g_activeListFrames = (ListFrame*)this;
        prev = p;
    }
    ~GliderListFrame() { g_activeListFrames = (ListFrame*)prev; }
};

void EvaluateHermiteVectorSegment(f32 dur, f32 t, f32 k, const Vec02* p0, const Vec02* m0, const Vec02* p1, const Vec02* m1, Vec02* pos, Vec02* vel, Vec02* acc);
// The definition's parameters in the order the call below writes them: retail's caller
// evaluates its float arguments there, and only their place in the list decides that.
f32 SplitVectorAlongAxis(Vec02* v, Vec02* axis, Vec02* along, Vec02* rest);

void MoveTimedContactListObject(ContactListGlider* self, s32 hold, f32 dt)
{
    Vec02 accel;
    f32 now = *(f32*)(g_gameClock + 4);
    if (now < self->time6FC) {
        Vec02 pos;
        Vec02 vel;
        Mat02 rot;
        f32 remain = self->time6FC - now + dt;
        ComputeObjectFrameAtTime(self->anchorObject, 0, &pos, &rot, 0, 0, g_movieFrameLookahead <? remain);
        Vu0::Q(pos) = Vu0::Add(Vu0::Rotate(rot, Vu0::Q(self->anchorOffset)), Vu0::Q(pos));
        s32 still = 0;
        if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(self->v700))) < 0.0001f
            && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(self->v700))) < 0.0001f
            && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(self->v700))) < 0.0001f) {
            still = 1;
        }
        if (still) {
            Vu0::Q(vel) = Vu0::MulXSum(Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->pos)), Vu0::Scalar(1.5f / remain), Vu0::Q(self->v150), Vu0::Scalar(-0.5f));
        } else {
            vel = self->v700;
        }
        Vec02 outPos;
        Vec02 outVel;
        EvaluateHermiteVectorSegment(remain, dt, 1.0f, &self->pos, &self->v150, &pos, &vel, &outPos, &outVel, &accel);
        self->pos = outPos;
        self->v150 = outVel;
    } else {
        accel = D_00248D30;
        Vu0::Q(self->pos) = Vu0::MulAddX(Vu0::Q(self->pos), Vu0::Q(self->v150), Vu0::Scalar(dt));
    }
    if (self->ready != 0) {
        s32 still = 0;
        if (__builtin_fabsf(Vu0::ToFloatMoved(Vu0::Q(self->v150))) < 0.0001f
            && __builtin_fabsf(Vu0::ToFloatY(Vu0::Q(self->v150))) < 0.0001f
            && __builtin_fabsf(Vu0::ToFloatZ(Vu0::Q(self->v150))) < 0.0001f) {
            still = 1;
        }
        if (!still) {
            Vec02 dir;
            Vec02 rest;
            Vu0::Set(dir, Vu0::NormalizeOrMoved(Vu0::Q(self->v150), Vu0::Q(g_unitXVector)));
            SplitVectorAlongAxis(&accel, &self->rot.r[0], 0, &rest);
            u128 s = Vu0::Scalar(-1.0f);
            u128 b = Vu0::Q(rest);
            u128 a = Vu0::Q(g_currentWorld->gravity);
            u128 t = Vu0::ScalarAt(self->f6F8);
            Vu0::Q(rest) = Vu0::MulXSum(a, s, b, t);
            BuildBasisFromXAndZHint(&self->v150, &rest, &self->rot);
        }
    }
    GliderListFrame f(&self->children);
    void* n;
    void* t = *(void**)f.base;
    f.cur = (u8*)t + f.off;
    n = t;
    if (n != 0) {
        do {
            if (((PlacedObject*)n)->desc->flags & 1) {
                ((void (*)(void*, f32, s32))((PlacedObject*)n)->desc->m1B)(n, dt, 1);
            }
            void* c = f.cur;
            s32 o = f.off;
            void* a = *(void**)c;
            f.cur = (u8*)a + o;
            n = a;
        } while (n != 0);
    }
    if (hold == 0) {
        if (self->desc->m12 != 0) {
            self->desc->m12(self);
        }
    }
}

s32 FindKeyIndex(IdentityKey* key)
{
    IdentityKey* p = (IdentityKey*)(u8*)g_movieKeys;
    s32 i = 0;
    s32 m;

    do {
        if (p == key) {
            m = 1;
        } else if (p == 0 || key == 0) {
            m = 0;
        } else {
            m = ((p->signedWords[2] ^ p->signedWords[6]) ^ (key->signedWords[2] ^ key->signedWords[6])) == 0;
        }
        if (!m) {
            i++;
            p++;
        } else {
            return i;
        }
    } while (i < 16);
    return -1;
}

u8* GetMovieTitle(s32 index)
{
    if ((u32)index < 16) {
        return (u8*)g_movieTitles[index];
    }
    if (index == -1) {
        return (u8*)"Nil";
    }
    return (u8*)"(unknown)";
}

void QueueMovieByIndex(s32 idx)
{
    QueueMovie(&g_moviePlayer, (u8*)g_movieKeys + (idx << 5));
}

void QueueMovieWithSuccessor(s32 idx, u32 n)
{
    GameProgress* dev;
    s32 m;

    QueueMovieByIndex(idx);
    g_moviePlayer.queuedNext = (IdentityKey*)((u8*)g_movieKeys + (n << 5));
    if (n >= 16) { m = 0; } else { m = 1 << n; }
    dev = g_saveData;
    dev->u19F4 |= m;
}

void RunMovieDecodeThread(void)
{
    MoviePlayer* t = &g_moviePlayer;

    for (;;) {
        t->threadStep = 0;
        AwaitSemaphore(t->frameSemaphore);
        t->threadStep = 1;
        SendGsPacketAndWait(g_gifChannel, t->uploadPacket);
        t->threadStep = 2;
        ApplyPendingDisplayFlip();
        SendGsPacketAndWait(g_gifChannel, t->drawPacket);
        FlipDisplayFrame();
        SendGsPacketAndWait(g_gifChannel, t->drawPacket);
        FlipDisplayFrame();
    }
}

void CreateMovieDecodeThread(void)
{
    ThreadParams l;
    s32 v;

    g_moviePlayer.frameSemaphore = CreateLockSemaphore(0, 1);
    g_moviePlayer.reader = 0;
    (void)FillMemory(&l, 0, sizeof(l));
    l.entry = RunMovieDecodeThread;
    l.stack = g_movieDecodeThreadStack;
    l.gp = g_globalPointer;
    l.stackSize = 0x1000;
    l.priority = 2;
    v = MakeThread(&l);
    g_movieDecodeThread = v;
    RunThread(v, 0);
}

void InitIopRingSink(IopRingSink* self, s32 a1, s32 a2)
{
    self->iopBase = a2;
    self->capacity = a1;
    ResetIopRingSink(self);
}

void ResetIopRingSink(IopRingSink* c)
{
    c->freeBytes = c->capacity;
    c->usedBytes = 0;
    c->readPosition = 0;
    c->writePosition = 0;
    c->totalWritten = 0;
}

s32 IopRingSink::Put(s32 count, u8* dst)
{
    s32 n = count;
    s32 total = 0;
    s32 left = n;
    s32 r;

    if (left <= 0 || freeBytes < left) {
        left = freeBytes;
    }
    left &= -0x400;
    while (left != 0) {
        s32 avail = capacity - writePosition;
        r = WriteIopRingBlock(this, left < avail ? left : avail, dst + total);
        if (r == 0) {
            break;
        }
        total += r;
        left -= r;
        writePosition += r;
        writePosition = writePosition % capacity;
        usedBytes += r;
        freeBytes -= r;
        totalWritten += r;
        if (n <= 0) {
            break;
        }
    }
    return total;
}

s32 WriteIopRingBlock(IopRingSink* p, s32 size, u8* buf)
{
    IopDmaTransfer span;
    void* obj;

    span.src = (s32)buf;
    span.dest = p->iopBase + p->writePosition;
    span.size = (void*)size;
    span.attr = 0;
    SyncDataCache(0);
    obj = StartIopDma(&span, 1);
    while (GetIopDmaStatus(obj) >= 0) {
    }
    return size;
}

void UpdateIopRingSink(IopRingSink* self) { s32 raw = GetIopRingPosition(); s32 x = (raw & 0xFFFFFF) - self->iopBase; x = x - self->writePosition; x = x - 0x400; x = x + self->capacity; self->freeBytes = x; self->freeBytes = x % self->capacity; s32 d = self->capacity - self->freeBytes; self->usedBytes = d; s32 y = self->writePosition - d; y += self->capacity; self->readPosition = y; self->readPosition = y % self->capacity; }

s32 IopRingSink::Idle()
{
    return 0;
}

s32 IpuDmaSink::Put(s32 size, u8* buf)
{
    s32 n = size & 0xFFFFFFF0;
    if (n > 0x1000) n = 0x1000;
    u32 old = *(volatile u32*)0x1000F590;
    *(volatile u32*)0x1000F590 = 0x10000;
    *(volatile u32*)0x1000B420 = (u32)n >> 4;
    u32 addr = (u32)buf & 0x0FFFFFFF;
    *(volatile u32*)0x1000B410 = addr;
    *(volatile u32*)0x1000B400 = 0x101;
    *(volatile u32*)0x1000F590 = old;
    return n;
}

s32 IpuDmaSink::Idle()
{
    return 1;
}

// Declared to return a value it never sets: func_0018F448, its caller, is retail's only with a
// callee that returns one.
s32 StartMovieStream(MovieStream* self)
{
    s32 r;
    SuspendIopVoices(0xFFFFFFFF);
    PushIopChannel2Setting(g_currentWorld, 0, 0);
    StopAllIopSounds();
    while (PollIopCommands() != 0) {
    }
    WaitForIopSoundStop(1);
    SyncDiscRead(0);
    self->savedVolume2 = GetIopVolumeChannel(2);
    self->savedVolume8 = GetIopVolumeChannel(8);
    SetIopVolumeChannel(2, 0x400);
    SetIopVolumeChannel(8, 0x200);
    r = OpenIopRing(0x6000, 0x400, 0, 2, 2);
    if (r < 0) {
        self->state = 0;
    } else {
        self->state = 1;
        InitRingBuffer(&self->headerRing, 0x28, self->header);
        InitRingBuffer(&self->dataRing, 0xC000, g_movieDataRingBuffer);
        InitIopRingSink(&self->sink, 0x6000, r);
    }
}

void ResetMovieStream(MovieStream* self)
{
    if (self->state != 0) {
        ResetIopRing();
        self->state = 1;
        ResetRingBuffer(&self->headerRing);
        ResetRingBuffer(&self->dataRing);
        ResetIopRingSink(&self->sink);
    }
}

void StopMovieStream(MovieStream* self)
{
    self->state = 0;
    StopIopMovieStream();
    SetIopVolumeChannel(2, self->savedVolume2);
    SetIopVolumeChannel(8, self->savedVolume8);
    PopIopChannel2Setting(g_currentWorld);
    ResumeIopVoices(0xFFFFFFFF);
}

s32 FeedMovieStream(MovieStream* self, s32 left, u8* right)
{
    s32 n;

    if (self->state == 0) {
        goto zero;
    }
    left -= 4;
    right += 4;
    if (self->state == 1) {
        n = FillRingBufferFromMemory(&self->headerRing, left, right);
        left -= n;
        right += n;
        if (self->headerRing.space > 0) {
            goto one;
        }
        self->state = 2;
    }
    if (self->dataRing.space >= left) {
        goto call;
    }
zero:
    return 0;
call:
    FillRingBufferFromMemory(&self->dataRing, left, right);
one:
    return 1;
}

void UpdateMovieStream(MovieStream* self)
{
    switch (self->state) {
    case 2:
        DrainRingBuffer(&self->dataRing, self->sink.freeBytes, (StreamSink*)&self->sink);
        if (self->sink.freeBytes != 0) {
            break;
        }
        UpdateIopMovieStream(self->sink.iopBase, self->sink.capacity, self->sink.iopBase, 0, 0);
        self->state = 3;
        break;
    case 3: {
        IopRingSink* s0 = &self->sink;
        UpdateIopRingSink(s0);
        DrainRingBuffer(&self->dataRing, self->sink.freeBytes, (StreamSink*)s0);
        break;
    }
    }
}

s32 AcceptMovieDataIntoRing(void* a0, MovieDataBlock* a1, MoviePlayer* a2)
{
    if ((u32)a2->videoRing.space >= (u32)a1->size) {
        FillRingBufferFromMemory(&a2->videoRing, a1->size, a1->data);
        return 1;
    }
    return 0;
}

void PassMovieDataToStream(void* a0, MovieDataBlock* a1, MoviePlayer* a2)
{
    FeedMovieStream(&a2->stream, a1->size, a1->data);
}

s32 FlushMovieToIpu(void* u0, void* u1, MoviePlayer* self)
{
    s32 total = 0x40;
    while (self->videoRing.filled < 0x1000) {
        if (FeedMovieDecoder(self, 1) == 0) {
            u8 zero[0x40];
            FillMemory(zero, 0, 0x40);
            s32 k = self->videoRing.filled;
            FillRingBufferFromMemory(&self->videoRing, total - (k % 32), zero);
            break;
        }
    }
    {
        IpuDmaSink dma;
        ConsumeSpan(&self->videoRing, 0);
        DrainRingBuffer(&self->videoRing, 0, (StreamSink*)&dma);
    }
    return 1;
}

s32 FeedMovieDecoderWithoutWaiting(void* a0, s32 a1, MoviePlayer* a2)
{
    FeedMovieDecoder(a2, 0);
    return 1;
}

s32 AcceptMovieDecoderEvent(void)
{
    return 1;
}

void UploadMovieFrame(void* p, s32 addr, s32 w, s32 h)
{
    s32 ny = w / 16;
    s32 nx = h / 16;
    s32 x;
    s32 y;
    PacketWriter f;

    InitGifPacket(&f);
    UsePacketBufferMemory(&f, 0x1C28, p);
    BeginDmaTag(&f);
    BeginGifTag(&f, 0, 1, 0xE);
    AddGifRegisterWrite(&f, 0x50, (u64)0xA1E0 << 36);
    AddGifRegisterWrite(&f, 0x52, ((u64)0x10 << 32) | 0x10);
    for (y = 0; y < ny; y++) {
        for (x = 0; x < nx; x++) {
            BeginGifTag(&f, 0, 1, 0xE);
            AddGifRegisterWrite(&f, 0x51, ((u64)(y << 4) << 32) | ((u64)(x << 4) << 48));
            AddGifRegisterWrite(&f, 0x53, 0);
            AddGifImageTag(&f, 0x40);
            AddDmaRefTag(&f, 0x40, addr & 0xFFFFFFF);
            addr += 0x400;
        }
    }
    BeginGifTag(&f, 0, 1, 0xE);
    AddGifRegisterWrite(&f, 0x3F, 0);
    AddGifRegisterWrite(&f, 0x61, 0);
    EndGifPacket(&f);
    AddDmaEndTag(&f);
    DetachPacketBuffer(&f, 0, 0);
}

void DrawMovieFrame(void* self, s32 a1, s32 a2)
{
    PacketWriter buf;
    InitGifPacket(&buf);
    UsePacketBufferMemory(&buf, 0x12, self);
    BeginDmaTag(&buf);
    BeginGifTag(&buf, 6, 1, 0xE);
    AddGifRegisterWrite(&buf, 6, 0x0AA8029E00ULL);
    AddGifRegisterWrite(&buf, 0x14, 0x61);
    AddGifRegisterWrite(&buf, 8, 5);
    AddGifRegisterWrite(&buf, 0x42, 0x44);
    AddGifRegisterWrite(&buf, 0x47, 0x31001);
    BeginGifTag(&buf, 0x116, 5, 0xE4343);
    AddGifUvEntry(&buf, 8, 8);
    AddGifXyzfEntry(&buf, 0x6C00, 0x7900, 0, 0);
    AddGifUvEntry(&buf, (a1 << 4) | 8, (a2 << 4) | 8);
    AddGifXyzfEntry(&buf, 0x9400, 0x8700, 0, 0);
    AddGifRegisterWrite(&buf, 0x61, 0);
    EndGifPacket(&buf);
    AddDmaEndTag(&buf);
    DetachPacketBuffer(&buf, 0, 0);
}

void QueueMovie(MoviePlayer* self, void* p)
{
    s32 m;
    s32 v;

    if (self->queued != 0) {
        return;
    }
    self->queued = (IdentityKey*)p;
    v = FindKeyIndex((IdentityKey*)p);
    if ((u32)v >= 16) {
        m = 0;
    } else {
        m = 1 << v;
    }
    g_saveData->u19F4 |= m;
}

void PlayQueuedMovies(MoviePlayer* self)
{
    IdentityKey* pending = self->queuedNext;
    IdentityKey* first = self->queued;
    self->queued = 0;
    self->queuedNext = 0;
    PlayMovie(self, first);
    if (pending != 0) {
        PlayMovie(self, pending);
    }
}

void PlayMovie(MoviePlayer* self, IdentityKey* key)
{
    StreamReader loc;
    KeyId pr;
    SetScreenOwner(4);
    self->movieIndex = FindKeyIndex(key);
    InitStreamReader(&loc, g_packetBufferMemory);
    if (KeyIdOfMovie::Of(&pr, key) && OpenSectorStreamRange(&loc, &pr)) {
        InitMoviePlayback(self, &loc);
        while (!GetMpegDecoderStatus((Device_20B0B0*)&self->decoder)) {
            AdvanceGameClockElapsed((GameClock*)g_gameClock);
            UpdatePadConnection(&g_padRecord);
            s32 flag = 0;
            if (SameMovieKey::Of(key, &g_watchedMovieKey)) flag = g_keyedMovieWatched != 0;
            u32 m;
            if (self->movieIndex >= 16) m = 0;
            else m = 1u << self->movieIndex;
            if (g_saveData->movieBits & m) flag = 1;
            if (flag) {
                if (RestoreFadeRequest((ScreenFade*)g_screenFade, &g_padRecord, 2)) break;
                if (g_padRecord.flags & 0x91F) {
                    ClearPadPressedBits(&g_padRecord, 0x91F);
                    break;
                }
            }
            StepDiscSectorCheck();
            if (g_discSectorCheckState != 3) break;
            StepMovieFrame(self);
        }
        if (SameMovieKey::Of(key, &g_watchedMovieKey)) g_keyedMovieWatched = 1;
        FinishMovie(self);
        CloseStreamReader(&loc);
    } else {
        StartSoundEffect(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
    ClearScreenOwner(4);
    DestroyStreamReader(&loc, 2);
}

void InitMoviePlayback(MoviePlayer* self, void* v)
{
    s32 i;

    self->reader = (StreamReaderWindow*)v;
    self->decoderWork = g_movieDecoderWork;
    self->picture = g_moviePictureBuffer;
    InitRingBuffer(&self->videoRing, 0x30000, (u8*)((s32)g_movieVideoRingBuffer | 0x20000000));
    StartMovieStream(&self->stream);
    InitMpegLibrary();
    CreateMpegDecoder(&self->decoder, self->decoderWork, 0x152F68);
    SetStreamCallback((Ctx_20A220*)&self->decoder, 0, 0, (Handler_20A220)AcceptMovieDataIntoRing, self);
    SetStreamCallback((Ctx_20A220*)&self->decoder, 2, 0, (Handler_20A220)PassMovieDataToStream, self);
    SetMpegCallback(&self->decoder, 1, (void*)FlushMovieToIpu, self);
    SetMpegCallback(&self->decoder, 4, (void*)FeedMovieDecoderWithoutWaiting, self);
    SetMpegCallback(&self->decoder, 0, (void*)AcceptMovieDecoderEvent, self);
    while (FeedMovieDecoder(self, 1) != 0) {
    }
    self->uploadPacket = g_movieUploadPacket;
    self->drawPacket = g_movieDrawPacket;
    D_002626CC = 0;
    g_moviePlayer.cur = (u8*)0x100010;
    g_moviePlayer.remain = (s32)D_00148D68;
    g_moviePlayer.crc = 0xFFFFFFFF;
    u8* tb = g_movieCrcTable;
    i = 0;
    s32 j;
    do {
        u32 c = i;
        s32 k;
        s32 off = c * 4;
        j = c + 1;
        for (k = 7; k >= 0; k--) {
            if (c & 1) c = (c >> 1) ^ 0xEDB88320; else c = c >> 1;
        }
        *(u32*)(tb + off) = c;
        i = j;
    } while (j < 256);
}

void AdvanceCodeChecksum(MoviePlayer* self)
{
    if (self->remain > 0) {
        s32 n = self->remain - 4;
        u32* tab = (u32*)g_movieCrcTable;
        u8* p = self->cur;
        u8* nxt = p + 4;
        u32 c0 = self->crc;
        u32 c1, c2, c3;

        c1 = tab[(c0 ^ p[0]) & 0xff] ^ (c0 >> 8);
        self->crc = c1;
        c2 = tab[(c1 ^ p[1]) & 0xff] ^ (c1 >> 8);
        self->crc = c2;
        self->remain = n;
        c3 = tab[(c2 ^ p[2]) & 0xff] ^ (c2 >> 8);
        self->crc = c3;
        u32 t = tab[(c3 ^ p[3]) & 0xff];
        self->cur = nxt;
        u32 c = t ^ (c3 >> 8);
        self->crc = c;
        if (n == 0 && c != 0) {
            g_movieChecksumFailed = 1;
        }
    }
}

void StepMovieFrame(MoviePlayer* self)
{
    MovieStream* s1;
    if (self->threadStep == 1) {
        do {
            (void)FeedMovieDecoder(self, 0);
        } while (self->threadStep == 1);
    }
    if (DecodeMpegPicture((MpegHandle*)&self->decoder, self->picture, 0x4B0) < 0) {
        return;
    }
    if (self->decoder.f08 == 0) {
        UploadMovieFrame(self->uploadPacket, (s32)self->picture, self->decoder.width, self->decoder.height);
        DrawMovieFrame(self->drawPacket, self->decoder.width, self->decoder.height);
        SyncDataCache(0);
    }
    s1 = &self->stream;
    if (self->threadStep != 0) {
        do {
            (void)FeedMovieDecoder(self, 0);
            AdvanceCodeChecksum(self);
        } while (self->threadStep != 0);
    }
    PostSemaphore(self->frameSemaphore);
    UpdateMovieStream(s1);
}

void FinishMovie(MoviePlayer* self)
{
    s32 mask;

    self->reader = 0;
    ResetMovieStream(&self->stream);
    StopMovieStream(&self->stream);
    ResetMpegDecoder((S_20B0C0*)&self->decoder);
    (void)DeleteMpegDecoder((MpegHandle*)&self->decoder);
    if (self->threadStep != 0) {
        do {
        } while (self->threadStep != 0);
    }
    D_002626CC = 3;
    SendResidentImages();
    if (self->movieIndex >= 16) {
        mask = 0;
    } else {
        mask = 1 << self->movieIndex;
    }
    g_saveData->movieBits |= mask;
}

s32 FeedMovieDecoder(MoviePlayer* self, s32 wait)
{
    while (ReaderEmpty::Of(self->reader)) {
        PumpStreamReader(self->reader);
        if (ReaderEmpty::Of(self->reader) && !wait) return 0;
    }
    SyncDataCache(0);
    StreamReaderWindow* buffer = self->reader;
    s32 count = buffer->readyLength - buffer->usedLength;
    s32 result = DemultiplexBuffer((Ctx_20A220*)&self->decoder, buffer->readyStart + buffer->usedLength, count);
    ConsumeStreamBytes(self->reader, result);
    return result;
}

LINKER_REMNANT(func_0018F938);
