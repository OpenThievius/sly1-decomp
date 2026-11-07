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


// The objects func_00184D78 orders: by the words at 0x304 and 0x308, then flag bit 38, then
// the word at 0x2D0 (a placed object's subclass).
struct SortKeyedObject : PlacedObject {
    s32 f2D0;               // 0x2D0
    u8 pad2D4[0x304 - 0x2D4];
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
struct LightGroup { void* lights; s32 count; s32 flags; s16 kind; s16 fE; };

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

INCLUDE_ASM(func_00184DE8);

ASM_FUNC(func_00185150);

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

ASM_FUNC(func_00185498);

ASM_FUNC(func_00185538);

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
