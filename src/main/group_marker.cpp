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
#include "asm_func.h"

// The scale and offset the projection constants upload (func_0019D860); func_001DD3E0 reads
// them too.
f32 D_0026ABF0[4] = { 33218888.0f, 33218888.0f, 4.2520177e+09f, 0.0f };
f32 D_0026AC00[4] = { 8.623489e+09f, 8.623489e+09f, 1.2884902e+10f, 0.0f };

// The next free entry of D_005E4700, a GIF tag and the group markers: no initialiser.
u8 D_0026AC10[16];
s32 D_0026AC20[4];
GroupMarker D_0026AC30[18];

struct Buf_19DF48 { u8 raw[0x30]; };
void* func_001611B8(void* self);
void func_001529C8(void* self, s32 a, void* b);
void func_001612F8(void* self, s32 a, s32 b, s32 c, s32 d, s32 e);
void func_0019DA30(void);
void func_0019DA60(void);
void func_0019DAD8(void);
void func_0019DB20(void);
void func_0019DB68(void);
void func_0019DBB0(void);
struct ColorFade;
typedef void (*VFn_19D6C0)(ColorFade* self, void* arg, s32 z);
struct Frame_19D6C0 {
    s32 list;
    s32 cursor;
    s32 link;
    s32 prev;
};
void func_00159D00(ColorFade* n);
extern u8 D_0060478C[];
void func_00152B38(void* self);
void func_00152D70(void* self);
void func_001EE3B8(void* obj, s32 size, s32 flags);
void func_001EE668(void* obj, s32 size, s32 count, void* data, s32 flags);
extern s32 D_00604780;
extern s32 D_00604784;
extern u8 D_002BDC20[];
extern u8 D_002BDEE0[];
void func_001EE7D0(void* self, s32 n, void* buf, s32 flag);
void func_001EE450(void* self);
struct Slot_2622D8 { u8 pad00[0x1C]; s32 r1C; };
extern u8 D_00212160[];
extern u8 D_00215C50[];
extern Slot_2622D8* D_002622D8;
void func_0019D860(void);
void func_0019D930(void);
void func_0015EAE0(void* self, void* a, void* b);
void func_001EE468(void* self);
struct Ctx_19DBB0 { u8 pad0[0x2F4]; s32 idx2F4; };
extern Ctx_19DBB0* D_0026FA68;
extern s32 D_00274520[];
extern Camera* D_00261990;
void func_00143940(Camera* self, f32 v);
void func_00144848(Camera* self);
void func_001BE0A8(void** base, s32 count, s32 size, void* cmp);
struct Pkt_19DDA0;
void func_001613C0(Pkt_19DDA0* p, s32 a, s32 b, u64 c);
void func_00161708(Pkt_19DDA0* p, s32 reg, u64 value);
void func_00161458(Pkt_19DDA0* p, u32 c);
void func_001615F0(Pkt_19DDA0* p, s32 a, s32 b, s32 c, s32 d);
void func_00144848(void*);
void func_0015EAE0(void*, void*, void*);
void func_0019D968(void);
struct Val_0019D468 { u8 pad[4]; f32 value; };
extern u32 D_00604788;
extern u8 D_00215C60[];
extern u8 D_00217348[];

// D_0026AC10 points at the next free 128-byte entry of D_005E4700 (1024 of them).
void func_0019D410(DeferredRequest* src)
{
    DeferredRequest* cur = *(DeferredRequest**)g_nextDeferredRequest;
    if ((u32)(cur - g_deferredRequests) < 0x400) {
        *(DeferredRequest**)g_nextDeferredRequest = cur + 1;
        *(DeferredRequest*)((u32)cur | 0x20000000) = *src;
    }
}

int func_0019D468(Val_0019D468** a, Val_0019D468** b)
{
    Val_0019D468* left = *a;
    Val_0019D468* right = *b;
    if (right->value < left->value) return -1;
    if (left->value < right->value) return 1;
    return ((s32)left - (s32)right) >> 7;
}

s32 func_0019D4B0(s32 n, DeferredRequest* items, void** out)
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
        HeapSortRecords(&out[pos[4]], c, 4, (void*)CompareEntriesByValueDescending);
    }
    {
        s32 c = cnt[8] - pos[8];
        HeapSortRecords(&out[pos[8]], c, 4, (void*)CompareEntriesByValueDescending);
    }
    {
        s32 c = cnt[13] - pos[13];
        HeapSortRecords(&out[pos[13]], c, 4, (void*)CompareEntriesByValueDescending);
    }
    {
        s32 c = cnt[1] - pos[1];
        HeapSortRecords(&out[pos[1]], c, 4, (void*)CompareEntriesByValueDescending);
    }
    return cnt[17];
}

void func_0019D6C0(World* self, void* arg)
{
    Frame_19D6C0 f1;
    Frame_19D6C0 f2;
    Frame_19D6C0 f3;
    s32 e = (s32)self + 0x60;
    f1.cursor = e;
    f1.list = e;
    s32 old = (s32)g_activeListFrames;
    s32 link = *(s32*)(e + 8);
    *(s32*)g_nextDeferredRequest = (s32)g_deferredRequests;
    g_activeListFrames = (ListFrame*)&f1;
    f1.prev = old;
    f1.link = link;
    s32 h = *(s32*)e;
    f1.cursor = h + link;
    s32 n = h;
    while (n != 0) {
        ColorFade* node = (ColorFade*)n;
        ((VFn_19D6C0*)node->obj)[40](node, arg, 0);
        s32 nx = *(s32*)f1.cursor;
        f1.cursor = nx + f1.link;
        n = nx;
    }
    s32 e2 = (s32)self + 0x78;
    s32 old2 = (s32)g_activeListFrames;
    f2.cursor = e2;
    f2.list = e2;
    s32 link2 = *(s32*)(e2 + 8);
    g_activeListFrames = (ListFrame*)&f2;
    f2.prev = old2;
    s32 h2 = *(s32*)((s32)self + 0x78);
    f2.link = link2;
    f2.cursor = h2 + link2;
    n = h2;
    while (n != 0) {
        ColorFade* node = (ColorFade*)n;
        ((VFn_19D6C0*)node->obj)[40](node, arg, 0);
        s32 nx = *(s32*)f2.cursor;
        f2.cursor = nx + f2.link;
        n = nx;
    }
    s32 e3 = (s32)self + 0x1CD8;
    s32 old3 = (s32)g_activeListFrames;
    s32 link3 = *(s32*)(e3 + 8);
    f3.prev = old3;
    g_activeListFrames = (ListFrame*)&f3;
    f3.list = e3;
    s32 h3 = *(s32*)((s32)self + 0x1CD8);
    f3.link = link3;
    f3.cursor = h3 + link3;
    n = h3;
    while (n != 0) {
        UpdateColorFade((ColorFade*)n);
        s32 nx = *(s32*)f3.cursor;
        f3.cursor = nx + f3.link;
        n = nx;
    }
    g_activeListFrames = (ListFrame*)f1.prev;
}

void func_0019D860(void)
{
    if (*(s32*)D_0060478C == 0) {
        *(s32*)D_0060478C = 1;
        void* obj = &g_vifPacketWriter;
        BeginDmaTag(obj);
        WriteVifBaseOffset(obj, 0, 0);
        CopyWordsToWriter(obj, 8, 1, g_projectionScale, 0);
        CopyWordsToWriter(obj, 8, 1, g_projectionOffset, 1);
        CopyWordsToWriter(obj, 0xC, 1, D_0026AC20, 0xC);
        CopyWordsToWriter(obj, 4, 1, &g_currentWorld->f1D68, 3);
        CloseDmaTag(obj);
    }
}

void func_0019D930(void)
{
    if (!g_cameraUploadedThisFrame) {
        g_cameraUploadedThisFrame = 1;
        func_00144848((void*)g_camera);
    }
}

void func_0019D968(void)
{
    if (D_00604780 == 0) {
        void* self = &g_vifPacketWriter;
        BeginDmaTag(self);
        func_001EE7D0(self, 0x2C, D_002BDC20, 0);
        CloseDmaTag(self);
        D_00604780 = 1;
        D_00604784 = 1;
    } else if (D_00604784 == 0) {
        void* self = &g_vifPacketWriter;
        BeginDmaTag(self);
        WriteVifFlush(self);
        func_001EE7D0(self, 0x2C, D_002BDEE0, 0);
        CloseDmaTag(self);
        D_00604784 = 1;
    }
}

void func_0019DA30(void)
{
    AddDmaRefTagIfChanged(&g_vifPacketWriter, D_00212160, D_00215C50);
}

void func_0019DA60(void)
{
    UploadProjectionConstants();
    UploadCameraOncePerFrame();
    void* self = &g_vifPacketWriter;
    AddDmaRefTagIfChanged(self, D_00212160, D_00215C50);
    D_00604780 = 1;
    g_buildFrame->r1C = 1;
    BeginDmaTag(self);
    WriteVifFlushA(self);
    CloseDmaTag(self);
}

void func_0019DAD8(void)
{
    UploadProjectionConstants();
    UploadGroupConstants();
    AddDmaRefTagIfChanged(&g_vifPacketWriter, D_00212160, D_00215C50);
    g_cameraUploadedThisFrame = 0;
}

void func_0019DB20(void)
{
    UploadProjectionConstants();
    UploadCameraOncePerFrame();
    UploadGroupConstants();
    AddDmaRefTagIfChanged(&g_vifPacketWriter, D_00212160, D_00215C50);
}

void func_0019DB68(void)
{
    UploadProjectionConstants();
    UploadCameraOncePerFrame();
    UploadGroupConstants();
    AddDmaRefTagIfChanged(&g_vifPacketWriter, D_00215C60, D_00217348);
}

void func_0019DBB0(void)
{
    PacketWriter* self = &g_vifPacketWriter;
    AddDmaRefTagIfChanged(self, D_00212160, D_00215C50);
    UploadProjectionConstants();
    UploadCameraOncePerFrame();

    if (D_0026FA68 != 0) {
        s32 v = D_00274520[D_0026FA68->idx2F4];
        if (v != 0) {
            *(u64*)self->cur = ((u64)v << 32) | 0x50000000;
            self->cur = self->cur + 0x10;
        }
    }

    {
        Camera* o = g_camera;
        f32 keep20 = o->f1C4;
        f32 keep21 = o->f1C8;
        SnapCameraZoom(o, 1.0f);
        func_00144848(g_camera);
        SnapCameraZoom(g_camera, keep20);
        g_camera->f1C8 = keep21;
    }
}

INCLUDE_ASM(func_0019DC98);

void func_0019DDA0(f32 x0, f32 y0, f32 x1, f32 y1, s32 r, s32 g, s32 b, s32 a, Pkt_19DDA0* p)
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

void func_0019DF48(void)
{
    Buf_19DF48 buf;
    GroupMarker* rows;
    u8* p;
    s32 i;

    InitGifPacket(buf.raw);
    UsePacketBufferMemory(buf.raw, 1, D_0026AC20);
    ReserveGifPackedData(buf.raw, 0x7D, 0, 3, 0x412, 0);
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
