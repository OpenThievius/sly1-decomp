// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x184D78 to 0x185C18: an object sort, the aim helpers, the main loop with the
// IOP modules it loads and the startup initializers it runs. Its name is ours, after the loop.
#include "common.h"
#include "asm_func.h"

#include "fpu.h"
#include "attachment.h"
#include "globals.h"
#include "game_clock.h"
#include "pad_record.h"
#include "memory_card.h"
#include "placed_object.h"
#include "value_range.h"
#include "screen_fade.h"
#include "movie_player.h"
#include "word_copy.h"
#include "list_iter.h"
#include "vu0.h"


// The objects func_00184D78 orders: by the words at 0x304 and 0x308, then flag bit 38, then
// the word at 0x2D0 (a placed object's subclass).
struct SortKeyedObject : PlacedObject {
    s32 f2D0;               // 0x2D0
    s32 f2D4;               // 0x2D4: a light's mode, of which CollectLightsForSphere returns the highest
    u8 pad2D8[0x304 - 0x2D8];
    s32 f304;               // 0x304
    s32 f308;               // 0x308
};




void InitPoseSource(Attachment* self);



extern s32 g_vif0Channel;
extern u8 D_00211E10[];
void SyncDataCache(s32 unused);
void StartDmaChain(void* dma, void* addr);
s32 WaitDmaChannel(void* dma, s32 b, s32 c);



extern u8 g_vif1Channel[];
extern u8 D_00212110[];

void SyncDataCache(s32 a);
void StartDmaChain(void* a, void* b);
s32 WaitDmaChannel(void* a, s32 b, s32 c);

// The first word of a DMA channel's register block (CHCR), which g_vif1Channel points to.
struct DmaChannelFlags {
    s32 flags;
};



extern s32 g_worldLoadRequest;
extern u8 g_elementStack[];
extern s32 g_frameCount;

void RunConstructorsOnce(void);
void RunStartupInitializers(void);
void DrainRenderFrames(s32 flag);
void PlayQueuedMovies(MoviePlayer* self);
void RunPendingWorldLoad(void* p);
void UpdatePadConnection(void* p);
void RunCompletedButtonCode(void);
void UpdateMemoryCard(void* p);
void UpdateElementStack(void* p);
void AddElapsedTime(f32 dt);
void UpdateCameraLocation(void* p);
void BeginRenderFrame(void);
void AdvanceGameClock(void* p);
void RunWorldFrameLists(World* o, void* a);
void QueueScreenElementDraws(void* p);
void SubmitDeferredRequests(World* o, void* a);
void DrawAllScreenElements(void* p);
void SubmitRenderFrame(void);



// func_00185B38's locals: the load progress record (load_progress.h) and the four colours
// InitLoadProgress takes, in one frame.
struct ProgressFrame { s32 w[28]; };
typedef void (*StartupFn)(void);

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();

s32 InitLoadProgress(void* a, void* b, void* c, void* d, void* e);
void SetScreenOwner(s32 value);
void BeginLoadProgress(void* p);
void UpdateLoadProgress(void* self, s32 value);
void EndLoadProgress(void* p);
void ClearScreenOwner(s32 value);



s32 GetActiveSwitchedCollider(void);






void FormatDiscPath(void* buf, const u8* name, s32 n);
void InitRemoteCalls(s32 a);
s32 InitDiscLibrary(s32 a);
s32 RefreshDiscStatus();
void SendDiscCommand22WhenReady();
s32 ForgetFileClient();
s32 ResetIop(void* buf);
s32 IsIopResetDone();
s32 ForgetModuleLoader();
s32 WaitDiscReady(s32 a);
s32 TestDiscReadDone(s32 a);
s32 LoadIopModuleFile(void* buf, s32 a, s32 b);

s32 CompareObjectsForSort(SortKeyedObject** a, SortKeyedObject** b);
void InitAim(T2195_790* self);
void AssignAimTarget(T2195_790* self, void* obj, Vec02* src);
s32 ResolveAimTarget(T2195_790* a0);
void RunMainLoop(s32 a, s32 b);
void LoadIopModules();
void SendVif0StartupPacket(void);
void SendVif1StartupPacket();
void RunStartupInitializers(void);

void InitPlacedObjectModule();
void InitAlphaStatePackets();
void ResetDiscSectorCheck();
void InitDiscAccessModule();
void InitObjectBuiltinTable();
void ResetGameClockTick();
void InitCameraModule();
void InitDmaChannels();
void ClearDefaultFont();
void InitRenderFrames();
void RunResetGameSession();
void InitDisplay();
void SetObjectListLinkOffsets();
void InitPadSystem();
void RegisterButtonCodes();
void SetPointObjectListLinkOffset();
void InitMemoryCardSystem();
void InitHeap();
void CreateMovieDecodeThread();
void SetTargetVectorListLinkOffset();
void InitGroupMarkers();
void InstallScreenElements();
void InitSoundSystem();
void InitClass75List();
void CreateRenderThread();
void InitGlobalElementStack();

// A run of lights of one kind in g_sortedLights, as UploadLightVolumes groups them for
// CollectLightsForSphere: the first light, the count, the flag bits a caller can mask out and
// the kind that picks the VU0 test.
struct LightGroup { void** lights; s32 count; s32 flags; u16 kind; s16 fE; };

s32 g_lightingChangeFrame = 0;
s32 g_lightCount = 0;
void* g_sortedLights[256] = {0};
s32 g_lightGroupCount = 0;
LightGroup g_lightGroups[16] = {};
Vec02 D_00264770 = { 0.0f, 1.0f, 0.0f, 0.0f };
Vec02 D_00264780 = { -3.4028234663852886e38f, 3.4028234663852886e38f, 0.0f, 0.0f };
Vec02 D_00264790 = { 0.0f, 1.0f, 0.0f, 0.0f };
ValueRange D_002647A0 = { -1.0f, 1.0f };
const u8* g_iopModuleNames[6] = {
    (const u8*)"sio2man.irx", (const u8*)"padman.irx", (const u8*)"mcman.irx",
    (const u8*)"mcserv.irx", (const u8*)"libsd.irx", (const u8*)"989snd.irx",
};
Fn_Table g_startupInitializers[29] = { (Fn_Table)InitPlacedObjectModule, (Fn_Table)InitHeap, (Fn_Table)InitDmaChannels, (Fn_Table)CreateRenderThread, (Fn_Table)InitDisplay, (Fn_Table)LoadIopModules, (Fn_Table)InitDiscAccessModule, (Fn_Table)ResetDiscSectorCheck, (Fn_Table)InitPadSystem, (Fn_Table)RegisterButtonCodes, (Fn_Table)InitRenderFrames, (Fn_Table)ClearDefaultFont, (Fn_Table)InitObjectBuiltinTable, (Fn_Table)InitCameraModule, (Fn_Table)InitSoundSystem, (Fn_Table)InstallScreenElements, (Fn_Table)InitGlobalElementStack, (Fn_Table)InitClass75List, (Fn_Table)SetPointObjectListLinkOffset, (Fn_Table)SetTargetVectorListLinkOffset, (Fn_Table)SetObjectListLinkOffsets, (Fn_Table)SendVif0StartupPacket, (Fn_Table)SendVif1StartupPacket, (Fn_Table)InitAlphaStatePackets, (Fn_Table)InitGroupMarkers, (Fn_Table)ResetGameClockTick, (Fn_Table)InitMemoryCardSystem, (Fn_Table)RunResetGameSession, (Fn_Table)CreateMovieDecodeThread };
s32 D_00264834;
s32 D_00264838;

s32 CompareObjectsForSort(SortKeyedObject** a, SortKeyedObject** b)
{
    SortKeyedObject* x = *a;
    SortKeyedObject* y = *b;
    s32 d;

    d = x->f304 - y->f304;
    if (d != 0) {
        return d;
    }
    d = x->f308 - y->f308;
    if (d != 0) {
        return d;
    }
    d = ((s32)(x->flags >> 38) & 1) - ((s32)(y->flags >> 38) & 1);
    if (d != 0) {
        return d;
    }
    return x->f2D0 - y->f2D0;
}

// A light (class 0x51) as UploadLightVolumes reads it: the sort keys, its direction, the word
// it sends with it, the 0x60 bytes it sends for a volume, and its link in the world's list.
struct LightVector { f32 x, y, z, w; };
struct LightVolume { f32 w[24]; };
struct LightObject : SortKeyedObject {
    u8 pad310[0x334 - 0x310];
    f32 f334;               // 0x334
    u8 pad338[0x370 - 0x338];
    LightVolume volume;     // 0x370
    u8 pad3D0[0x410 - 0x3D0];
    LightObject* next;      // 0x410
};

void HeapSortRecords(void* base, s32 count, s32 size, s32 (*cmp)(SortKeyedObject**, SortKeyedObject**));
void* InitPacketWriter(PacketWriter* p);
void PushBackMemoryMark(void);
void PopBackMemoryMark(void);
void AllocateTempPacketBuffer(PacketWriter* p, s32 n);
void BeginDmaTag(PacketWriter* p);
void ReserveVifUnpack(PacketWriter* s, s32 tag, s32 size, s32 a3, void* a4, void* a5);
void AddDmaEndTag(PacketWriter* p);
void SubmitPacketBuffer(PacketWriter* p, s32 dma);
s32 WaitDmaChannel(s32 dma, s32 b, s32 c);

// Sorts the world's lights, groups the runs of one kind and flags (at most 16 to a group) and
// sends each light's direction or volume to VU0 in one unpack.
void UploadLightVolumes(World* world)
{
    ListFrame frame;        // the list walk's frame: retail's 16 unused bytes under the writer
    PacketWriter pw;
    LightVector dir;
    s32 base;
    u8* out;
    s32 count = 0;
    s32 slots = 0;
    LightGroup* group = 0;
    LightObject* l;
    for (l = (LightObject*)world->list1BE8.head;
         l != 0 && count < sizeof(g_sortedLights) / sizeof(g_sortedLights[0]); l = l->next) {
        g_sortedLights[count++] = l;
    }
    HeapSortRecords(g_sortedLights, count, 4, CompareObjectsForSort);
    g_lightGroupCount = 0;
    g_lightCount = 0;
    s32 i;
    for (i = 0; i < count; i++) {
        l = (LightObject*)g_sortedLights[i];
        s32 kind = l->f2D0;
        if (kind == 3) {
            kind = 2;
        }
        s32 flags = 0;
        if (l->f304 == 0) {
            flags |= 1;
        }
        if (l->f308 != 0) {
            flags |= 2;
        }
        if ((l->flags & (1ULL << 38)) != 0) {
            flags |= 4;
        }
        if (group != 0 && group->count < 16 && group->kind == kind && group->flags == flags) {
            group->count++;
        } else {
            if (g_lightGroupCount >= sizeof(g_lightGroups) / sizeof(g_lightGroups[0])) {
                break;
            }
            group = &g_lightGroups[g_lightGroupCount++];
            group->flags = flags;
            group->count = 1;
            group->kind = kind;
            group->lights = &g_sortedLights[i];
            group->fE = slots;
            if (l->f304 != 0) {
                g_lightCount = 1;
            }
        }
        switch (kind) {
        case 1:
            slots += 1;
            break;
        case 2:
            slots += 6;
            break;
        }
    }
    InitPacketWriter(&pw);
    PushBackMemoryMark();
    AllocateTempPacketBuffer(&pw, 0x102);
    BeginDmaTag(&pw);
    ReserveVifUnpack(&pw, 0xC, slots, 0, &base, &out);
    for (i = 0; i < count; i++) {
        l = (LightObject*)g_sortedLights[i];
        switch (l->f2D0) {
        case 1:
            dir.x = -l->v140.x;
            dir.y = -l->v140.y;
            dir.z = -l->v140.z;
            dir.w = l->f334;
            WordCopy::Words(out, &dir, sizeof(dir) / 4);
            out += sizeof(LightVector);
            break;
        case 2:
        case 3:
            WordCopy::Words(out, &l->volume, sizeof(l->volume) / 4);
            out += sizeof(LightVolume);
            break;
        }
    }
    AddDmaEndTag(&pw);
    SubmitPacketBuffer(&pw, g_vif0Channel);
    WaitDmaChannel(g_vif0Channel, 0, 0);
    PopBackMemoryMark();
}

// The lights that reach a sphere: each group's lights are tested on VU0 (the microprogram at
// 0x60 for kind 1, at 0x168 for kind 2; kind 0 passes them all), a group whose flags meet
// skipMask is left out, and the mask of a group is read when the next one is set up, or
// after the last. Writes up to maxLights lights, their number, and how many have the flag
// bit 0; returns the highest mode among them (at least 1 when the world's +0x1D6C is set).
s32 CollectLightsForSphere(World* world, const Vec02* centre, f32 radius, u32 skipMask, s32 maxLights, s32* flagged, s32* outCount,
                  LightObject** out)
{
    u32 keepOut = ~skipMask;
    s32 num = 0;
    s32 flaggedCount = 0;
    LightGroup* prev = 0;
    u32 mask;
    s32 strongest = world->f1D6C != 0.0f;
    Vec02 sphere = *centre;
    sphere.w = radius;
    Vu0::LoadVf<31>(&sphere);
    for (s32 i = 0; i < g_lightGroupCount + 1; i++) {
        LightGroup* grp;
        if (i == g_lightGroupCount) {
            mask = Vu0::ReadViWait<2>();
        } else {
            grp = &g_lightGroups[i];
            if (grp->flags & keepOut) {
                continue;
            }
            mask = Vu0::NextLightGroup((u16)grp->fE, grp->count);
            switch (grp->kind) {
            case 0:
                Vu0::MoveToVi<2>(0xFFFF);
                break;
            case 1:
                Vu0::CallMs<0x60>();
                break;
            case 2:
                Vu0::CallMs<0x168>();
                break;
            }
        }
        if (prev) {
            s32 bit = 1 << prev->count;
            for (s32 k = 0; k < prev->count; k++) {
                bit >>= 1;
                if (((s32)mask & bit) && num < maxLights) {
                    LightObject* l = (LightObject*)prev->lights[k];
                    out[num++] = l;
                    if (strongest < l->f2D4) {
                        strongest = l->f2D4;
                    }
                    flaggedCount += prev->flags & 1;
                }
            }
        }
        prev = grp;
    }
    *outCount = num;
    if (flagged) {
        *flagged = flaggedCount;
    }
    return strongest;
}

void InitAim(T2195_790* self)
{
    InitPoseSource(self);
    self->f20 = -1;
    self->f40 = 800.0f;
    self->v50 = *(Vec02*)&D_00264770;
    self->p60 = *(Pk8_2195*)&D_00264780;
    self->v70 = *(Vec02*)&D_00264790;
    self->p80 = *(Pk8_2195*)&D_002647A0;
    self->f44 = 1;
    self->f48 = -1;
}

void AssignAimTarget(T2195_790* self, void* obj, Vec02* src)
{
    if (obj == 0 || obj == (void*)GetActiveSwitchedCollider()) {
        self->hasTarget = 0;
        self->target = 0;
        self->point = D_00248D30;
    } else {
        self->target = obj;
        self->hasTarget = 1;
        self->point = *src;
    }
}

s32 ResolveAimTarget(T2195_790* a0) {
    if (a0->hasTarget == 0) {
        return GetActiveSwitchedCollider();
    }
    return (s32)a0->target;
}

void ClearRootTries(PlacedObject* o);
void SortAttachments(PlacedObject* o);

// The aim attachment's key from the owner's distance to the target: the far key beyond the
// range at +0x40, else the near key, after clearing the root's tries. The owner is resorted in
// its list when the key changes.
void SwitchAimByTargetDistance(T2195_790* self)
{
    PlacedObject* owner = self->owner;
    PlacedObject* target = (PlacedObject*)ResolveAimTarget(self);
    if (target != 0) {
        u128 d = Vu0::Sub(Vu0::Q(owner->v140), Vu0::Q(target->v140));
        s32 key;
        if (self->f40 * self->f40 < Vu0::ToFloatMoved(Vu0::Dot(d, d))) {
            key = self->f48;
        } else {
            key = self->f44;
            ClearRootTries(owner);
        }
        if (key != self->key) {
            self->key = key;
            SortAttachments(self->owner);
        }
    }
}

// One axis of an aim (T2195_790 has the yaw's at +0x50 and the pitch's at +0x70): a quadratic
// (a, b, c) applied to the angle toward the target and the range the result is clamped to.
// GetAimRotation gives both axes the same code, one inline per axis.
struct AimAxis {
    f32 a;                  // 0x00
    f32 b;                  // 0x04
    f32 c;                  // 0x08
    u8 pad0C[0x10 - 0x0C]; // 0x0C
    ValueRange limits;      // 0x10
    u8 pad18[0x20 - 0x18]; // 0x18

    f32 Apply(f32 x) { return limits.Limit(a + x * (b + x * c)); }
};

typedef char check_AimAxis[sizeof(AimAxis) == 0x20 ? 1 : -1];

void ComputeObjectFrameAtTime(void* object, s32 b, Vec02* pos, Mat02* rot, s32 e, s32 f, f32 t);
void TransformPointBetweenFrames(void* a0, void* a1, void* a2, void* a3);
void GetVectorAngles(Vec02* v, f32* yaw, f32* pitch);
void BuildYawPitchMatrix(f32 yaw, f32 pitch, Mat02* out);

// The aim's rotation: the owner's own while the aim is held, its +0x1A0 matrix when the target
// is beyond the range at +0x40, else a yaw and pitch toward the target, each through its axis's
// quadratic and clamp (AimAxis). d's stores are written to its address (`*(u128*)&d`): through
// Q(d) the inline's address of d stays in a pseudo the later &d reuses (a0 set before the range
// test instead of in the branch's delay slot).
void GetAimRotation(T2195_790* self, f32 dt, Mat02* rot, Vec02* vec)
{
    Vec02 pos;
    Vec02 d;
    Mat02 m;
    f32 angles[2];
    PlacedObject* owner = self->owner;
    *vec = D_00248D30;
    if (self->hold != 0) {
        *rot = owner->rot;
        return;
    }
    ComputeObjectFrameAtTime((void*)ResolveAimTarget(self), 0, &pos, &m, 0, 0, dt);
    Vu0::Q(pos) = Vu0::Add(Vu0::Rotate(m, Vu0::Q(self->point)), Vu0::Q(pos));
    TransformPointBetweenFrames(0, self->owner->parent, &pos, &pos);
    *(u128*)&d = Vu0::Sub(Vu0::Q(pos), Vu0::Q(self->owner->pos));
    s32 outside = self->f40 < Vu0::ToFloat(Vu0::Length(*(u128*)&d));
    if (outside) {
        *rot = owner->m1A0;
        return;
    }
    GetVectorAngles(&d, &angles[0], &angles[1]);
    angles[0] = ((AimAxis*)&self->v50)->Apply(angles[0]);
    angles[1] = ((AimAxis*)&self->v70)->Apply(angles[1]);
    BuildYawPitchMatrix(angles[0], angles[1], rot);
}

void RunMainLoop(s32 a, s32 b)
{
    RunConstructorsOnce();
    D_00264834 = a;
    D_00264838 = b;
    RunStartupInitializers();
    while (1) {
        if (g_moviePlayer.queued != 0 && g_screenFade.mode != 1) {
            DrainRenderFrames(1);
            PlayQueuedMovies(&g_moviePlayer);
        }
        if (g_worldLoadRequest != 0) {
            DrainRenderFrames(1);
            RunPendingWorldLoad(&g_worldLoadRequest);
        }
        if (g_moviePlayer.queued != 0 && g_screenFade.mode != 1) {
            DrainRenderFrames(1);
            PlayQueuedMovies(&g_moviePlayer);
        }
        UpdatePadConnection(&g_padRecord);
        RunCompletedButtonCode();
        UpdateMemoryCard(&g_memoryCard);
        UpdateElementStack(g_elementStack);
        AddElapsedTime(g_gameClock.dt);
        if (g_currentWorld != 0) {
            UpdateCameraLocation(g_camera);
            BeginRenderFrame();
            AdvanceGameClock(&g_gameClock);
            if (g_currentWorld->desc->m11 != 0)
                g_currentWorld->desc->m11(g_currentWorld, g_gameClock.dt);
            RunWorldFrameLists(g_currentWorld, g_camera);
            QueueScreenElementDraws(g_elementStack);
            SubmitDeferredRequests(g_currentWorld, g_camera);
            DrawAllScreenElements(g_elementStack);
            SubmitRenderFrame();
        }
        g_frameCount++;
    }
}

void LoadIopModules()
{
    u8 buf[0x100];
    FormatDiscPath(buf, (const u8*)"ioprp243.img", 1);
    InitRemoteCalls(0);
    InitDiscLibrary(0);
    if (RefreshDiscStatus() == 0) {
        for (;;) {
        }
    }
    SendDiscCommand22WhenReady();
    ForgetFileClient();
    while (ResetIop(buf) == 0) {
    }
    while (IsIopResetDone() == 0) {
    }
    InitRemoteCalls(0);
    ForgetModuleLoader();
    InitDiscLibrary(0);
    if (RefreshDiscStatus() == 0) {
        for (;;) {
        }
    }
    SendDiscCommand22WhenReady();
    ForgetFileClient();
    WaitDiscReady(0);
    TestDiscReadDone(1);
    for (u32 i = 0; i < 6; i++) {
        FormatDiscPath(buf, g_iopModuleNames[i], 1);
        while (LoadIopModuleFile(buf, 0, 0) < 0) {
        }
    }
}

void SendVif0StartupPacket(void)
{
    s32* p = (s32*)g_vif0Channel;
    *p |= 0x40;
    SyncDataCache(0);
    StartDmaChain((void*)g_vif0Channel, D_00211E10);
    WaitDmaChannel((void*)g_vif0Channel, 0, 0);
    s32* q = (s32*)g_vif0Channel;
    *q &= ~0x40;
}

void SendVif1StartupPacket()
{
    DmaChannelFlags* p = *(DmaChannelFlags**)g_vif1Channel;
    p->flags |= 0x40;
    SyncDataCache(0);
    StartDmaChain(*(void**)g_vif1Channel, D_00212110);
    WaitDmaChannel(*(void**)g_vif1Channel, 0, 0);
    (*(DmaChannelFlags**)g_vif1Channel)->flags &= ~0x40;
}

void RunStartupInitializers(void)
{
    ProgressFrame fr;
    u32 i;
    s32 idx;
    StartupFn* tbl;

    fr.w[12] = 0x7F0000;
    fr.w[16] = 0x3F3F3F;
    fr.w[20] = 0x3F3F;
    fr.w[24] = 0x3F;
    (void)InitLoadProgress(&fr, &fr.w[12], &fr.w[16], &fr.w[20], &fr.w[24]);
    idx = 0x1A;
    SetScreenOwner(1);
    BeginLoadProgress(&fr);
    tbl = (StartupFn*)((u8*)g_startupInitializers);
    i = 0;
    do {
        if ((s32)i >= 3) {
            UpdateLoadProgress(&fr, idx);
        }
        tbl[i]();
        i++;
        idx--;
    } while (i < 0x1D);
    UpdateLoadProgress(&fr, 0);
    EndLoadProgress(&fr);
    ClearScreenOwner(1);
}
