// SPDX-License-Identifier: AGPL-3.0-or-later
// The source file from 0x19D410 to 0x19E040, built whole (config/us/files.tsv): the deferred
// requests (func_0019D410 queues one in D_005E4700, func_0019D4B0 sorts them by group), the VIF
// set-up each group's marker runs (func_0019DA30 ... func_0019DBB0), a GS sprite writer
// (func_0019DDA0) and the init function of the game's table D_002647C0 that fills the 18 group
// markers (func_0019DF48). No .rodata. Its .data (0x26ABF0 to 0x26B530) is the two projection
// vectors below, then three uninitialised globals, which GCC writes at the end of the file's
// .data in the order they are first declared (group_marker.h): D_0026AC10, D_0026AC20 and the
// group markers D_0026AC30, after which it is named.
#include "common.h"
#include "world.h"
#include "list_iter.h"
#include "globals.h"
#include "camera.h"
#include "packet_writer.h"
#include "group_marker.h"
#include "deferred_request.h"
#include "color_fade.h"
#include "render_frame.h"
#include "warp_page.h"
#include "asm_func.h"

// The scale and offset the projection constants upload (func_0019D860); func_001DD3E0 reads
// them too.
f32 g_projectionScale[4] = { 33218888.0f, 33218888.0f, 4.2520177e+09f, 0.0f };
f32 g_projectionOffset[4] = { 8.623489e+09f, 8.623489e+09f, 1.2884902e+10f, 0.0f };

// The next free entry of D_005E4700, a GIF tag and the group markers: no initialiser.
u8 g_nextDeferredRequest[16];
s32 g_projectionExtraConstants[4];
GroupMarker g_groupMarkers[18];

void* InitGifPacket(PacketWriter* self);
void UsePacketBufferMemory(PacketWriter* self, s32 count, void* memory);
void ReserveGifPackedData(PacketWriter* self, u64 prim, s32 nloop, s32 nreg, u64 data, u8** out);
void PrepareBasicGroup(void);
void PrepareFlushedGroup(void);
void PrepareGroupWithoutCamera(void);
void PrepareStandardGroup(void);
void PrepareAlternateBlockGroup(void);
void PrepareUnzoomedGroup(void);
struct ColorFade;
typedef void (*DrawHook)(ColorFade* self, void* arg, s32 z);
void UpdateColorFade(ColorFade* n);
extern u8 g_projectionConstantsUploaded[];
void BeginDmaTag(PacketWriter* self);
void CloseDmaTag(PacketWriter* self);
void WriteVifBaseOffset(PacketWriter* s, u32 a, u32 b);
void CopyWordsToWriter(PacketWriter* s, s32 a1, s32 size, u32* src, s32 a4);
extern s32 g_groupConstantsUploaded;
extern s32 g_groupConstantsCurrent;
extern u8 g_screenClearPacketA[];
extern u8 g_screenClearPacketB[];
void WriteVifDirect(PacketWriter* self, s32 n, void* buf, s32 flag);
void WriteVifFlush(PacketWriter* b);
extern u8 g_groupMicroprogram[];
extern u8 g_groupMicroprogramEnd[];
void UploadProjectionConstants(void);
void UploadCameraOncePerFrame(void);
void AddDmaRefTagIfChanged(void* self, void* a, void* b);
void WriteVifFlushA(PacketWriter* b);
extern WarpPage* D_0026FA68;   // the warp page on view (warp_menu sets its mode and cursor)
extern s32 g_maskImageUploads[];
extern Camera* g_camera;
void SnapCameraZoom(void* self, f32 x);
void WriteCameraMatricesPacket(Camera* self);
typedef s32 (*SortCompareFn)(void* a, void* b);
void HeapSortRecords(void* records, s32 n, s32 size, SortCompareFn cmp);
void BeginGifTag(PacketWriter* self, s32 a1, s32 a2, u64 a3);
void AddGifRegisterWrite(PacketWriter* self, u64 a1, u64 a2);
void AddGifRgbaEntry(PacketWriter* p, u32 c);
void AddGifXyzfEntry(PacketWriter* self, u32 a1, u32 a2, u32 a3, u32 a4);
void WriteCameraMatricesPacket(Camera* self);
void AddDmaRefTagIfChanged(void*, void*, void*);
void UploadGroupConstants(void);
extern u32 g_cameraUploadedThisFrame;
extern u8 D_00215C60[];
extern u8 D_00217348[];

// D_0026AC10 points at the next free 128-byte entry of D_005E4700 (1024 of them).
void QueueDeferredRequest(DeferredRequest* src)
{
    DeferredRequest* cur = *(DeferredRequest**)g_nextDeferredRequest;
    if ((u32)(cur - g_deferredRequests) < 0x400) {
        *(DeferredRequest**)g_nextDeferredRequest = cur + 1;
        *(DeferredRequest*)((u32)cur | 0x20000000) = *src;
    }
}

int CompareEntriesByValueDescending(DeferredRequest** a, DeferredRequest** b)
{
    DeferredRequest* left = *a;
    DeferredRequest* right = *b;
    if (right->f04 < left->f04) return -1;
    if (left->f04 < right->f04) return 1;
    return ((s32)left - (s32)right) >> 7;
}

s32 BucketDeferredRequests(s32 n, DeferredRequest* items, void** out)
{
    s32 start[18];
    s32 pos[18];
    s32 cnt[18];
    s32 j;
    s32 i;
    for (i = 0; i < 18; i++) cnt[i] = 0;
    for (j = 0; j < n; j++) cnt[items[j].group]++;
    pos[0] = 0;
    if (cnt[0] > 0 && g_groupMarkers[0].handlerWord != 0) {
        out[0] = &g_groupMarkers[0];
        pos[0] = 1;
        cnt[0]++;
    }
    start[0] = pos[0];
    for (i = 1; i < 18; i++) {
        pos[i] = cnt[i - 1];
        if (cnt[i] > 0 && g_groupMarkers[i].handlerWord != 0) {
            out[pos[i]] = &g_groupMarkers[i];
            pos[i]++;
        }
        cnt[i] += pos[i];
        start[i] = pos[i];
    }
    for (j = 0; j < n; j++, items++) {
        s32 b = items->group;
        out[start[b]++] = items;
    }
    {
        s32 c = cnt[4] - pos[4];
        HeapSortRecords(&out[pos[4]], c, 4, (SortCompareFn)CompareEntriesByValueDescending);
    }
    {
        s32 c = cnt[8] - pos[8];
        HeapSortRecords(&out[pos[8]], c, 4, (SortCompareFn)CompareEntriesByValueDescending);
    }
    {
        s32 c = cnt[13] - pos[13];
        HeapSortRecords(&out[pos[13]], c, 4, (SortCompareFn)CompareEntriesByValueDescending);
    }
    {
        s32 c = cnt[1] - pos[1];
        HeapSortRecords(&out[pos[1]], c, 4, (SortCompareFn)CompareEntriesByValueDescending);
    }
    return cnt[17];
}

void RunWorldFrameLists(World* self, void* arg)
{
    ListFrame f1;
    ListFrame f2;
    ListFrame f3;
    s32 e = (s32)self + 0x60;
    f1.link = (u8*)e;
    f1.list = (void*)e;
    s32 old = (s32)g_activeListFrames;
    s32 link = *(s32*)(e + 8);
    *(s32*)g_nextDeferredRequest = (s32)g_deferredRequests;
    g_activeListFrames = &f1;
    f1.prev = (ListFrame*)old;
    f1.offset = link;
    s32 h = *(s32*)e;
    f1.link = (u8*)(h + link);
    s32 n = h;
    while (n != 0) {
        ColorFade* node = (ColorFade*)n;
        ((DrawHook*)node->obj)[40](node, arg, 0);
        s32 nx = *(s32*)f1.link;
        f1.link = (u8*)(nx + f1.offset);
        n = nx;
    }
    s32 e2 = (s32)self + 0x78;
    s32 old2 = (s32)g_activeListFrames;
    f2.link = (u8*)e2;
    f2.list = (void*)e2;
    s32 link2 = *(s32*)(e2 + 8);
    g_activeListFrames = &f2;
    f2.prev = (ListFrame*)old2;
    s32 h2 = *(s32*)((s32)self + 0x78);
    f2.offset = link2;
    f2.link = (u8*)(h2 + link2);
    n = h2;
    while (n != 0) {
        ColorFade* node = (ColorFade*)n;
        ((DrawHook*)node->obj)[40](node, arg, 0);
        s32 nx = *(s32*)f2.link;
        f2.link = (u8*)(nx + f2.offset);
        n = nx;
    }
    s32 e3 = (s32)self + 0x1CD8;
    s32 old3 = (s32)g_activeListFrames;
    s32 link3 = *(s32*)(e3 + 8);
    f3.prev = (ListFrame*)old3;
    g_activeListFrames = &f3;
    f3.list = (void*)e3;
    s32 h3 = *(s32*)((s32)self + 0x1CD8);
    f3.offset = link3;
    f3.link = (u8*)(h3 + link3);
    n = h3;
    while (n != 0) {
        UpdateColorFade((ColorFade*)n);
        s32 nx = *(s32*)f3.link;
        f3.link = (u8*)(nx + f3.offset);
        n = nx;
    }
    g_activeListFrames = f1.prev;
}

void UploadProjectionConstants(void)
{
    if (*(s32*)g_projectionConstantsUploaded == 0) {
        *(s32*)g_projectionConstantsUploaded = 1;
        void* obj = &g_vifPacketWriter;
        BeginDmaTag((PacketWriter*)obj);
        WriteVifBaseOffset((PacketWriter*)obj, 0, 0);
        CopyWordsToWriter((PacketWriter*)obj, 8, 1, (u32*)g_projectionScale, 0);
        CopyWordsToWriter((PacketWriter*)obj, 8, 1, (u32*)g_projectionOffset, 1);
        CopyWordsToWriter((PacketWriter*)obj, 0xC, 1, (u32*)g_projectionExtraConstants, 0xC);
        CopyWordsToWriter((PacketWriter*)obj, 4, 1, (u32*)&g_currentWorld->f1D68, 3);
        CloseDmaTag((PacketWriter*)obj);
    }
}

void UploadCameraOncePerFrame(void)
{
    if (!g_cameraUploadedThisFrame) {
        g_cameraUploadedThisFrame = 1;
        WriteCameraMatricesPacket(g_camera);
    }
}

void UploadGroupConstants(void)
{
    if (g_groupConstantsUploaded == 0) {
        void* self = &g_vifPacketWriter;
        BeginDmaTag((PacketWriter*)self);
        WriteVifDirect((PacketWriter*)self, 0x2C, g_screenClearPacketA, 0);
        CloseDmaTag((PacketWriter*)self);
        g_groupConstantsUploaded = 1;
        g_groupConstantsCurrent = 1;
    } else if (g_groupConstantsCurrent == 0) {
        void* self = &g_vifPacketWriter;
        BeginDmaTag((PacketWriter*)self);
        WriteVifFlush((PacketWriter*)self);
        WriteVifDirect((PacketWriter*)self, 0x2C, g_screenClearPacketB, 0);
        CloseDmaTag((PacketWriter*)self);
        g_groupConstantsCurrent = 1;
    }
}

void PrepareBasicGroup(void)
{
    AddDmaRefTagIfChanged(&g_vifPacketWriter, g_groupMicroprogram, g_groupMicroprogramEnd);
}

void PrepareFlushedGroup(void)
{
    UploadProjectionConstants();
    UploadCameraOncePerFrame();
    void* self = &g_vifPacketWriter;
    AddDmaRefTagIfChanged(self, g_groupMicroprogram, g_groupMicroprogramEnd);
    g_groupConstantsUploaded = 1;
    g_buildFrame->hasMaskedImages = 1;
    BeginDmaTag((PacketWriter*)self);
    WriteVifFlushA((PacketWriter*)self);
    CloseDmaTag((PacketWriter*)self);
}

void PrepareGroupWithoutCamera(void)
{
    UploadProjectionConstants();
    UploadGroupConstants();
    AddDmaRefTagIfChanged(&g_vifPacketWriter, g_groupMicroprogram, g_groupMicroprogramEnd);
    g_cameraUploadedThisFrame = 0;
}

void PrepareStandardGroup(void)
{
    UploadProjectionConstants();
    UploadCameraOncePerFrame();
    UploadGroupConstants();
    AddDmaRefTagIfChanged(&g_vifPacketWriter, g_groupMicroprogram, g_groupMicroprogramEnd);
}

void PrepareAlternateBlockGroup(void)
{
    UploadProjectionConstants();
    UploadCameraOncePerFrame();
    UploadGroupConstants();
    AddDmaRefTagIfChanged(&g_vifPacketWriter, D_00215C60, D_00217348);
}

void PrepareUnzoomedGroup(void)
{
    PacketWriter* self = &g_vifPacketWriter;
    AddDmaRefTagIfChanged(self, g_groupMicroprogram, g_groupMicroprogramEnd);
    UploadProjectionConstants();
    UploadCameraOncePerFrame();

    if (D_0026FA68 != 0) {
        s32 v = g_maskImageUploads[D_0026FA68->slot];
        if (v != 0) {
            *(u64*)self->cur = ((u64)v << 32) | 0x50000000;
            self->cur = self->cur + 0x10;
        }
    }

    {
        Camera* o = g_camera;
        f32 keep20 = o->zoom;
        f32 keep21 = o->zoomGoal;
        SnapCameraZoom(o, 1.0f);
        WriteCameraMatricesPacket(g_camera);
        SnapCameraZoom(g_camera, keep20);
        g_camera->zoomGoal = keep21;
    }
}

void UploadLightVolumes(World* world);
extern s32 D_00262474;

// The caller passes the camera too, unused here; the world goes on to UploadLightVolumes. The
// four words at D_00604780 are cleared in address order.
void SubmitDeferredRequests(World* world, void* camera)
{
    DeferredRequest* list[0x412];
    UploadLightVolumes(world);
    s32 n = *(DeferredRequest**)g_nextDeferredRequest - g_deferredRequests;
    g_groupConstantsUploaded = 0;
    g_groupConstantsCurrent = 0;
    g_cameraUploadedThisFrame = 0;
    *(u32*)g_projectionConstantsUploaded = 0;
    D_00262474 = 0x214;
    s32 count = BucketDeferredRequests(n, g_deferredRequests, (void**)list);
    g_vifPacketWriter.registerCount = 1;
    CloseDmaTag(&g_vifPacketWriter);
    for (s32 i = 0; i < count; i++) {
        ((void (*)(DeferredRequest*))list[i]->callback)(list[i]);
    }
    BeginDmaTag(&g_vifPacketWriter);
    if (count == 0) {
        WriteVifDirect(&g_vifPacketWriter, 0x2C, g_screenClearPacketA, 0);
    }
    *(DeferredRequest**)g_nextDeferredRequest = 0;
}

void WriteColoredSpritePacket(f32 x0, f32 y0, f32 x1, f32 y1, s32 r, s32 g, s32 b, s32 a, PacketWriter* p)
{
    u32 col;
    BeginGifTag(p, a <= 0xFE ? 0x46 : 6, 5, 0x441EE);
    col = (((a + 1) & 0x1FE) << 23) | (b << 16) | (g << 8) | r;
    AddGifRegisterWrite(p, 0x47, 0x31001);
    AddGifRegisterWrite(p, 0x42, 0x44);
    AddGifRgbaEntry(p, col);
    AddGifXyzfEntry(p, (s32)((x0 + 1728.0f) * 16.0f), (s32)((y0 * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
    AddGifXyzfEntry(p, (s32)((x1 + 1728.0f) * 16.0f), (s32)((y1 * 0.45454547f + 1936.0f) * 16.0f), 0, 0);
}

void InitGroupMarkers(void)
{
    PacketWriter buf;
    GroupMarker* rows;
    u8* p;
    s32 i;

    InitGifPacket(&buf);
    UsePacketBufferMemory(&buf, 1, g_projectionExtraConstants);
    ReserveGifPackedData(&buf, 0x7D, 0, 3, 0x412, 0);
    rows = g_groupMarkers;

    rows[0].handler = PrepareBasicGroup;
    rows[1].handler = PrepareFlushedGroup;
    rows[2].handler = PrepareGroupWithoutCamera;
    rows[3].handler = PrepareStandardGroup;
    rows[4].handler = PrepareStandardGroup;
    rows[5].handler = PrepareAlternateBlockGroup;
    rows[6].handler = PrepareStandardGroup;
    rows[7].handler = PrepareStandardGroup;
    rows[8].handler = PrepareStandardGroup;
    rows[9].handler = PrepareAlternateBlockGroup;
    rows[12].handler = PrepareStandardGroup;
    rows[11].handler = PrepareStandardGroup;
    rows[10].handler = PrepareStandardGroup;
    rows[13].handler = PrepareStandardGroup;
    rows[14].handler = PrepareAlternateBlockGroup;
    rows[15].handler = PrepareAlternateBlockGroup;
    rows[16].handler = PrepareStandardGroup;
    rows[17].handler = PrepareUnzoomedGroup;

    p = (u8*)g_groupMarkers + 0x888;
    i = 17;
    do {
        *(s32*)p = -1;
        i--;
        p -= 0x80;
    } while (i >= 0);
}
