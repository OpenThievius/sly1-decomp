// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 324/344 (94.2%), checked 2026-11-07
// NEAR (2026-11-08, vu0w3-e1): registers and two orders only: retail keeps the speed in $f1 (here $f3) and the hit's time in $f3 with 0.25 in $f1 (here $f1 and $f2), and subtracts before it moves the 1.5 into the VU. The rest matches (frame, calls, the Scalar slot).
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

ObjectLink g_contactListObjectLinks[1] = { { 2, 0x317, 0x6B0 } };
f32 D_002699BC = 0.5f;
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




void ResolveObjectLinks(void* self, s32 mode, void* data);

struct IopDmaTransfer {
    s32 src;    // the EE address
    s32 dest;   // the IOP address
    void* size;
    s32 attr;
};

void SyncDataCache(s32 a);
void* StartIopDma(IopDmaTransfer* span, s32 n);
s32 GetIopDmaStatus(void* obj);


s32 MatchesObjectId(void* key, void* item);
s32 IsObjectOfKind(void* key, void* item);
s32 TestCollidersMayContact(void* self, void* key);



void ResetIopRing(void);
void ResetRingBuffer(void* state);

void UnregisterCollider(void* self);
void StopAnimationPlayer(void* obj);

extern u8 D_002CBB40[];

void SuspendIopVoices(u32 a0);
void ResumeIopVoices(u32 a0);
void StopAllIopSounds(void);
s32 PollIopCommands(void);
void WaitForIopSoundStop(s32 a0);
s32 SyncDiscRead(s32 flag);
s32 GetIopVolumeChannel(s32 arg);
void SetIopVolumeChannel(s32 a0, s32 a1);
s32 OpenIopRing(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
void PushIopChannel2Setting(void* p, s32 a, s32 b);
void InitRingBuffer(void* state, s32 size, void* buf);

void StopIopMovieStream(void);
void PopIopChannel2Setting(void* p);

s32 FillRingBufferFromMemory(void* queue, s32 size, void* data);

struct MovieDataBlock { u8 pad0[8]; u8* data; s32 size; };

s32 DrainRingBuffer(void* queue, s32 n, void* sink);
void UpdateIopMovieStream(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);


void* InitGifPacket(void* b);
void UsePacketBufferMemory(void* b, s32 a1, void* self);
void BeginDmaTag(void* b);
void BeginGifTag(void* b, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(void* b, s32 a1, u64 a2);
void AddGifUvEntry(void* b, s32 a1, s32 a2);
void AddGifXyzfEntry(void* b, s32 a1, s32 a2, s32 a3, s32 a4);
void EndGifPacket(void* b);
void AddDmaEndTag(void* b);
void DetachPacketBuffer(void* b, s32 a1, s32 a2);
void AddGifImageTag(void* f, s32 a);
void AddDmaRefTag(void* f, s32 a, s32 b);

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





void BuildPlacedObjectTransform(void* obj, void* c, void* out);
void BuildMatrixFromRotationAndTranslation(void* a, void* b, void* out);
void MultiplyMatrices(void* out, void* b, void* in);
void func_00125C90(void* obj, void* s, void* out);

extern s32 g_gifChannel;

s32 AwaitSemaphore(s32 a);
void SendGsPacketAndWait(s32 a, s32 b);
void ApplyPendingDisplayFlip(void);
void FlipDisplayFrame(void);

extern u8 D_005A2E60[];

extern s32 D_002626CC;

void ResetMpegDecoder(void* self);
s32 DeleteMpegDecoder(void* self);
void SendResidentImages(void);



extern const u32 g_movieKeys[128];

void* FillMemory(void* dst, s32 value, s32 size);
void ConsumeSpan(void* queue, s32 n);

void ClearKeyId(KeyId* p);
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

extern u8 D_002C3B00[];
extern u8 g_screenFade[];
extern s32 g_discSectorCheckState;

void SetScreenOwner(s32 v);
void* InitStreamReader(StreamReader* o, u8* d);
s32 OpenSectorStreamRange(StreamReader* o, KeyId* k);
void ClearPadPressedBits(PadRecord* d, s32 n);
void AdvanceGameClockElapsed(u8* t);
void UpdatePadConnection(PadRecord* d);
s32 RestoreFadeRequest(u8* a, PadRecord* b, s32 c);
void StepDiscSectorCheck();
s32 GetMpegDecoderStatus(void* l);
void CloseStreamReader(StreamReader* o);
void StartSoundEffect(s32 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void ClearScreenOwner(s32 v);
void DestroyStreamReader(StreamReader* o, s32 f);

extern u8 g_movieDecodeThreadStack[];
extern u8 D_002832F0[];
extern s32 g_movieDecodeThread;

s32 CreateLockSemaphore(void* a, void* b);
s32 MakeThread(ThreadParams* p);
void RunThread(s32 thread, s32 arg);

s32 GetIopRingPosition(void* self);

void BuildBasisFromX(void* a, void* b);
void MoveCollider(Collider* self, f32 x, void* b);

struct ReaderEmpty {
    static bool Of(StreamReaderWindow* b) { return b->readyLength == b->usedLength; }
};
void PumpStreamReader(StreamReaderWindow*);
s32 DemultiplexBuffer(void*, s32, s32);
void ConsumeStreamBytes(StreamReaderWindow*, s32);


s32 DecodeMpegPicture(void* a, s32 b, s32 c);
void PostSemaphore(s32 a);


extern u8 D_002D7B40[];
extern u8 D_0045AAC0[];
extern u8 D_0042AAC0[];
extern u8 D_00586AC0[];
extern u8 D_005A2D40[];
extern u8 D_00148D68[];

void InitMpegLibrary(void);
s32 CreateMpegDecoder(void* self, void* a, s32 b);
s32 SetStreamCallback(void* self, s32 a, s32 b, void* fn, void* arg);
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


// Class 0x3D, a contact-list object without gravity that keeps a velocity of its own.
struct ContactListGlider : ContactListObject {
    f32 speed6F0;           // 0x6F0: the speed of the velocity it keeps (func_0018DDD8)
    f32 rate6F4;            // 0x6F4: how fast it turns to that velocity (func_0018DE70)
    u8 pad6F8[4];
    f32 time6FC;
    Vec02 v700;             // 0x700: the velocity it keeps
};

typedef char check_ContactListGlider[sizeof(ContactListGlider) == 0x710 ? 1 : -1];

void StepCollider(Collider* self, f32 t);
void ClampVectorLength(Vec02* v, Vec02* out, f32 max);
void ComputeObjectFrameAtTime(void* object, s32 b, Vec02* pos, Mat02* rot, s32 e, s32 f, f32 t);
void func_00141D88(const Vec02* a0, void* a1, void* a2, s32 a3, ColliderSpan* out, f32 radius);
void LaunchContactListObject(ContactListObject* self);
extern f32 g_gameTime;

void LaunchTimedContactListObject(ContactListGlider* self)
{
    Mat02 rot;
    Vec02 d;
    Vec02 e;
    Vec02 pos;
    ColliderSpan hit;
    LaunchContactListObject(self);
    f32 time;
    f32 speed = self->speed6F0;
    if (0.0f < speed) {
        time = g_gameTime + speed;
    } else {
        ComputeObjectFrameAtTime(self->f694, 0, &pos, &rot, 0, 0, D_002699BC);
        Vu0::Q(pos) = Vu0::Add(Vu0::Rotate(rot, Vu0::Q(self->v6A0)), Vu0::Q(pos));
        Vu0::Q(d) = Vu0::MulX(Vu0::Q(self->v150), Vu0::Scalar(-0.5f));
        ClampVectorLength(&d, &d, self->rate6F4 * 0.75f);
        u128 diff = Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->pos));
        Vu0::Q(e) = Vu0::MulAddX(Vu0::Q(d), diff, Vu0::Scalar(1.5f));
        func_00141D88(&D_00248D30, &d, &e, 1, &hit, self->rate6F4);
        f32 ht = hit.time[1];
        f32 m = ht >? 0.25f;
        time = g_gameTime + 1.0f / m;
    }
    self->time6FC = time;
}

