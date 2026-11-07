// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "listed_collision_part.h"
#include "pooled_object.h"
#include "path_curve_object.h"
#include "point_object.h"
#include "list_iter.h"
#include "attachment.h"
#include "globals.h"
#include "strip_mesh.h"
#include "bump_allocator.h"
#include "texture_header.h"
#include "shapes.h"

void func_001CA5E0(void);

struct GatheredEventObject { u8 pad0[0x328]; s32 f328; };
struct GatheredObjects { s32 count; GatheredEventObject** items; };

void func_001C72A0(void* self);
void* func_0015A448(void* a, s32 b, void* c);
void func_0018D608(void);
void func_0018D6F0(void);
void func_0012D1B0(void* a, void* b, s32* c, void** d);
void* func_001EFA30(void);
void func_001EFA60(void* a, void* b);

void func_001C6F48(void* self);
void func_00167D68(ConeAgent* self);

void func_001B7B78(void* self);
void func_00152600(void* data, void* self);

void func_001BA130(void* self);

s32 func_001B8A08(Collider* a, Collider* b);

void* func_0015A448(void* obj, s32 id, s32 flags);

void func_00168AF8(void);
void func_001683B8(void);
void func_00201A18(s32 a0, s32 a1, s32 a2, s32 a3);
void func_00202098(void* p, s32 a1, s32 a2, s32 a3);
void func_001F6C20(s32 a0);
s32 func_00201FF8(void* p, s32 a1);

struct DmaChainBlock { u8 bytes[0x20]; };

extern u8 D_002BE1A0[];
void* func_00152888(DmaChainBlock* a);
void func_001529C8(DmaChainBlock* a, s32 n, DmaChainBlock* b);
void func_00152B80(DmaChainBlock* a, s32 n, void* table);
void func_00152D30(DmaChainBlock* a);
void func_001529E0(DmaChainBlock* a, s32 x, s32 y);
void func_00168A48(DmaChainBlock* b);

struct TexturePacket : PacketWriter { s32 value; };

extern s32 D_00274514;
extern s32 D_00274510;
extern s32 D_00261F1C;

void* func_001611B8(PacketWriter* f);
void func_00152980(PacketWriter* f, s32 size);
void func_00152B38(PacketWriter* f);
s32 func_001690C0(void* self, void* arg, TexturePacket* f);
void func_001613C0(PacketWriter* f, s32 a, s32 b, s32 c);
void func_00161708(PacketWriter* f, s32 a, u64 b);
void func_00161200(PacketWriter* f);
void func_00152D30(PacketWriter* f);
void func_001529E0(PacketWriter* f, s32 a, s32* out);
void func_001686E8(s32 a, s32 b);

extern FrameTarget D_0027DC20[];

void func_00182D48(void* self);
void func_00152470(void* table, void* self);

void func_00182ED0(void* self);
void func_00152600(void* table, void* self);

struct TargetedObject {
    u8 pad_00[0x398];
    s32 f398;
};

void* func_0015A448(void* a, s32 b, s32 c);

void func_001830D8(void* self);

void func_001B7968(void* self);
void func_00129FB0(void* self, f32 k);
void func_0012A080(void* self, f32 k);
void func_0012A150(void* self, f32 k);
void func_0012A270(void* self, f32 k);

void func_001B7A98(void* self);

void func_001613C0(void* p, s32 a, s32 b, s32 c);
void func_00161708(void* p, s32 a, u64 b);
void func_00161958(void* p, s32 x);

// The GS register TEX0 an image or palette record keeps (ImageRecord at 0x18, PaletteRecord
// at 0x10), as func_00168E78 and func_00168FB0 fill it: the base, width and format, the size
// as powers of two, then the palette's base, format and load mode.
struct GsTex0 {
    u64 tbp : 14;
    u64 tbw : 6;
    u64 psm : 6;
    u64 tw : 4;
    u64 th : 4;
    u64 tcc : 1;
    u64 tfx : 2;
    u64 cbp : 14;
    u64 cpsm : 4;
    u64 csm : 1;
    u64 csa : 5;
    u64 cld : 3;
};

u32 func_00168D30(u32 n);

void func_00168D98(u32 dbp, u32 dbw, u32 dpsm, u64 rrw, u32 rrh, s32 x, void* ctx);

void func_00152438(void* self, s32 value);

void func_00152440(void* self);


void func_001694A0(void* p);
void* func_0018D5C0(u32 n);


extern u8 D_002BDC20[];
extern u8 D_002BE1A0[];
extern u8 D_002BDEE0[];

void func_00201D60(void* p, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_00168770(void* ctx, Rgba4* v, s32 flag);
s32 func_001E2268(void* a, void* b);
void func_001F6950(s32 a0, void (*fn)(void), s32 a2);
void func_001F6DA8(s32 a0);
void func_00168D00(void);
void func_001685B8(void);
void func_001682C0(void);
void func_00168698(void);

extern s32 D_00261F1C;

s32 func_00201C78(void* p);
void func_00202A80(s32 a, void* b);
s32 func_00202C38(s32 a, s32 b, s32 c);

void func_00168D68(BumpAllocator*,s32,s32);

void func_00168130(void);
void func_00201988(s32 a0, s32 a1);

struct TextureUploadPacket : PacketWriter { u8 span[0x10]; s32 out; };

extern s32 D_00274514;
extern s32 D_00274510;

void func_00168D68(void* p, s32 a, s32 b);
s32 func_001690C0(void* self, void* arg, TextureUploadPacket* f);
void func_00152A50(PacketWriter* f, s32 a1, s32 a2, s32* out, s32 a4);
void func_001B3510(void* self);

struct FadePacket : PacketWriter { s32 value; u8 pad[0x3F0]; };

extern s32 D_00261F1C;

void func_001529C8(PacketWriter* f, s32 n, s32* p);
void func_0019DDA0(f32 x, f32 y, f32 z, f32 w, s32 a, s32 b, s32 c, s32 d, FadePacket* e);
void func_001529E0(PacketWriter* f, s32 a, s32 b);
void func_001686E8(s32 a, s32* b);
void func_001683E8(void);

extern s32 D_00274500;
extern s32 D_00274508;
s32 func_00168D88(void* self, s32 size);
void func_00168E78(PaletteRecord* e, s32 v);
void func_00168F48(PaletteRecord* e, s32 v, void* ctx);
void func_00152B80(void* self, s32 lo, s32 hi);
void func_00168FB0(ImageRecord* e, s32 v);
void func_00169088(ImageRecord* e, s32 v, void* ctx);


void* func_001300E8(void* node, s32 flags);

struct ChildListWalk {
    List01* iter;
    void* cursor;
    s32 link;
    void* prev;

    ChildListWalk(List01* i)
    {
        cursor = i;
        iter = i;
        link = i->offset;
        prev = g_activeListFrames;
        g_activeListFrames = (ListFrame*)this;
    }
    ~ChildListWalk() { g_activeListFrames = (ListFrame*)prev; }
    void* First()
    {
        void* n = *(void**)cursor;
        cursor = (u8*)n + link;
        return n;
    }
    void* Next()
    {
        void* n = *(void**)cursor;
        cursor = (u8*)n + link;
        return n;
    }
};

void func_00182C18(void* self);

// What FindTargetCurveLengthNearCollider asks the curve (slot 10): a point and a direction in
// the curve's parent's frame, and the arc length it answers.
struct CurveProbe {
    Quad16 a;
    Quad16 b;
    s32 c;
    u8 pad[0xC];
    f32 x;
};

void* func_001925F0(void);
s32 func_00128018(void* a, s32 b, void* c, void* d);
void func_001280C0(void* a, s32 b, void* c, void* d);
void func_00169E20(void* a0, void* a1, void* a2, f32 f);

struct HoldMatrices {
    u8 a[0x30];
    u8 b[0x30];
    u8 c[0x30];
    u8 d[0x10];
    u8 e[0x10];
};

extern f32 D_0026185C[];

void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);
void func_001837E0(void* obj, s32 kind, s32 a, s32 b);
void func_00189378(void* sub, void* a, void* out);
void func_00188D28(void* a, void* b, void* c);
void func_00189150(void* a, void* b, s32 c);


// The start of what a queue entry copies: two GIF tags whose words func_001694A0 marks (bit
// 15) when the entry has a flag.
struct QueuedGifTags {
    s32 f0;
    u8 pad0[0xC];
    s32 f10;
};

void func_0018D800(QueuedGifTags* dst, void* src, s32 count);

s32 func_00202120(void);
s32 func_00202058(s32 a);
void func_001F6C20(s32 a);
s32 func_001F6B60(s32 a);

void func_001BAC30(Collider* self);
void* func_0018D5C0(s32 bytes);

void func_001B9338(Collider* self, f32 t);
void func_00189378(Mat02* sub, s32 zero, Mat3U* out);
void func_001B91A8(Collider* self, Mat3U* out, s32 a, void* table, s32 b, f32 t);
extern f32 D_0026185C[];

struct TransferBase { s32 v; };

void func_00168D98(TransferBase dbp, u32 dbw, u32 dpsm, u64 rrw, u32 rrh, s32 x, void* ctx);

void func_001529C8(PacketWriter* f, s32 n, PacketWriter* p);

struct GsPmode { u32 en1 : 1; u32 rest : 31; u32 hi : 32; };
struct GsDispFb { u32 fbp : 9; u32 fbw : 6; u32 psm : 5; u32 pad0 : 12; u32 dbx : 11; u32 dby : 11; u32 pad1 : 10; };
struct GsDisplay { u32 dx : 12; u32 dy : 11; u32 magh : 4; u32 magv : 2; u32 pad0 : 3; u32 dw : 12; u32 dh : 11; u32 pad1 : 9; };
struct DisplayRegs { GsPmode pmode; u64 pad; GsDispFb dispfb; GsDisplay display; u64 pad2; };
struct GsPrivRegs {
    GsPmode pmode; u8 pad0[0x70 - 8];
    GsDispFb dispfb2; u8 pad1[8];
    GsDisplay display2; u8 pad2[0x1000 - 0x88];
    u32 csr;
};

extern s32 D_00274508;
extern s32 D_00274500;
extern s32 D_00274514;
extern s32 D_00274510;

void func_00168D68(BumpAllocator* p, s32 a, s32 b);
void* func_001EE318(PacketWriter* f);
void func_001EE450(PacketWriter* f);
void func_001528E0(PacketWriter* f);
void func_001529C8(PacketWriter* f, s32 n, u8* buf);
s32 func_00168D88(BumpAllocator* p, s32 size);
void func_00168F48(PaletteRecord* e, s32 v, PacketWriter* f);
void func_00169088(ImageRecord* e, s32 v, PacketWriter* f);
void func_001529E0(PacketWriter* f, s32* o0, s32* o1);
void func_001EE7D0(PacketWriter* f, s32 a, s32 b, s32 c);
void func_001EE850(PacketWriter* f, s32 a, s32 b, s32 c);
void func_00152D70(PacketWriter* f);
void func_00152A50(PacketWriter* f, s32 a, s32 b, s32* out, s32 c);
void func_001B3510(u32 mask);

// The file's .data, in retail's order (0x262480 to 0x262714): the word func_001682C0 reads,
// the display's two records (0x28 bytes each, read by func_00168130; retail puts them on 16
// after the 4-byte D_00262484) and its two pairs of packets, the frame counter and modes, the
// mesh queue's count and allocator, and the three object lists. Then its .bss (0x2BE460 to
// 0x2BE478), the statics the display code shares with func_001682C0 and func_00168698.
s32 D_00262480 = 0xF;
s32 D_00262484 = 0;
u8 D_00262490[0x50] __attribute__((aligned(16))) = { 0 };
u8 D_002624E0[16] = { 0 };
u8 D_002624F0[16] = { 0 };
u8 D_00262500[208] = { 0 };
u8 D_002625D0[16] = { 0 };
u8 D_002625E0[16] = { 0 };
u8 D_002625F0[208] = { 0 };
s32 D_002626C0 = 0;
s32 D_002626C4 = 0;
s32 D_002626C8 = 0;
s32 D_002626CC = 0;
s32 D_002626D0 = 0;
BumpAllocator D_002626D8 = { 0 };
List01 D_002626E8 = { 0 };
List01 D_002626F8 = { 0 };
List01 D_00262708 = { 0 };

static s32 D_002BE460;
static s32 D_002BE464;
static s32 D_002BE468;
static s32 D_002BE46C;
static s32 D_002BE470;
static s32 D_002BE474;

void func_00167D68(ConeAgent* self)
{
    InitAgent(self);
    self->fC20 = 1000.0f;
    self->fC24 = 1500.0f;
    self->fC28 = 0.78539816f;
    self->fC2C = 3.14159265f;
    self->fC10 = 2000.0f;
    self->fC30 = -1;
    self->fC14 = 300.0f;
    self->fC18 = -1;
    self->f73C = 300.0f;
    self->f738 = 0;
    self->f74C = 1.04719755f;
}

void func_00167E08(ConeAgent* self)
{
    GatheredObjects out;
    s32 i;

    StartAgent(self);
    if (self->fC18 != -1) {
        self->fC1C = (s32)FindFirstObjectByIdMode4(self->world, self->fC18, self);
    }
    if (self->fC30 != -1) {
        self->fC34 = (s32)FindFirstObjectByIdMode4(self->world, self->fC30, self);
    }
    if (self->f750 != 0) {
        PushBackMemoryMark();
        GatherAnimationEventObjects(self->f750, self, &out.count, (void**)&out.items);
        for (i = 0; i < out.count; i++) {
            GatheredEventObject* e = out.items[i];
            if (e->f328 == 0) {
                void* t = CreateRecord2505C0();
                e->f328 = (s32)t;
                AppendToSmallList(t, e);
            }
        }
        PopBackMemoryMark();
    }
}

void func_00167EF0(void)
{
    DrawAgent();
}

ASM_FUNC(func_00167F10);

void func_00168130(void)
{
    s32 i = g_displayFrameCounter & 1;
    s32 field = D_002626C8;
    GsPmode pm = ((DisplayRegs*)&D_00262490)[i].pmode;

    if (field != (s32)((((GsPrivRegs*)0x12000000)->csr >> 13) & 1)) {
        GsDisplay d = ((DisplayRegs*)&D_00262490)[i].display;
        GsDispFb fb = ((DisplayRegs*)&D_00262490)[i].dispfb;
        d.dh = d.dh - 1;
        if (field != 0) {
            d.dy = d.dy + 1;
        } else {
            fb.dby = fb.dby + 1;
        }
        ((GsPrivRegs*)0x12000000)->display2 = d;
        ((GsPrivRegs*)0x12000000)->dispfb2 = fb;
        pm.en1 = 1;
    }
    ((GsPrivRegs*)0x12000000)->pmode = pm;
}

ASM_FUNC(func_001682C0);

void func_001683B8(void) {
    D_002BE46C = 1;
    AwaitSemaphore(D_002BE460);
}

void func_001683E8(void)
{
    D_002BE470 = 1;
    SignalDisplaySync();
    s32 a0 = D_002626C4;
    s32 a1 = D_00262484;
    D_002626C8 = a0;
    D_002BE470 = 0;
    if (a1 > 0) {
        D_002626C4 = 0;
        D_00262484 = a1 - 1;
    } else {
        u32 flag = (*(u32*)0x12001000 >> 13) & 1;
        D_002626C4 = (flag == 0);
    }
    u8* ptr;
    if (g_displayFrameCounter & 1) {
        ptr = D_002624F0;
    } else {
        ptr = D_002625E0;
    }
    s16 half = *(s16*)&D_002626C4;
    SetFieldDrawOffset(ptr, 0x800, 0x800, half);
    SyncDataCache(0);
    g_displayFrameCounter = g_displayFrameCounter + 1;
    SwapDoubleBuffer(D_00262490, g_displayFrameCounter);
    if ((u32)(D_002626CC - 1) < 2) {
        ApplyFieldDisplayOffset();
    }
    WaitGsPaths(0, 0);
}

void func_001684E8(void)
{
    if (D_002626CC == 3) {
        D_002626CC = 2;
    }
    if (D_002BE474 != 0) {
        u32 flag = (*(u32*)0x12001000 >> 13) & 1;
        s32 cnt = g_displayFrameCounter;
        D_002BE474 = 0;
        D_002626C4 = (flag == 0);
        u8* ptr;
        if (cnt & 1) {
            ptr = D_002625E0;
        } else {
            ptr = D_002624F0;
        }
        s16 half = *(s16*)&D_002626C4;
        SetFieldDrawOffset(ptr, 0x800, 0x800, half);
        SyncDataCache(0);
        u8* ptr2;
        if (g_displayFrameCounter & 1) {
            ptr2 = D_002625D0;
        } else {
            ptr2 = D_002624E0;
        }
        SendDrawEnvironment(ptr2);
    }
}

void func_001685B8(void)
{
    D_002BE470 = 1;
    SendDisplayResetPacket();
    SignalDisplaySync();
    D_002BE470 = 0;
    ResetGs(0, 1, 2, 1);
    u32 flag = (*(u32*)0x12001000 >> 13) & 1;
    s32 cnt = g_displayFrameCounter;
    D_002626CC = 0;
    D_00262484 = 0;
    D_002626C8 = flag;
    D_002626C4 = (flag == 0);
    u8* ptr;
    if (cnt & 1) {
        ptr = D_002624F0;
    } else {
        ptr = D_002625E0;
    }
    s16 half = *(s16*)&D_002626C4;
    SetFieldDrawOffset(ptr, 0x800, 0x800, half);
    SyncDataCache(0);
    g_displayFrameCounter = g_displayFrameCounter + 1;
    SwapDoubleBuffer(D_00262490, g_displayFrameCounter);
}

ASM_FUNC(func_00168698);

void func_001686E8(s32 channel, void* b)
{
    D_002BE468 = 1;
    *(volatile u64*)0x12001000 |= 2;
    s32 r = GetGsInterruptMask();
    SwapGsInterruptMask(r & -0x201);
    SyncDataCache(0);
    StartDmaChain(channel, b);
    AwaitSemaphore(D_002BE464);
}

void func_00168770(PacketWriter* self, u8* color, s32 flag)
{
    PacketWriter f;
    s32 x;

    InitGifPacket(&f);
    UsePacketBufferMemory(&f, 0x2C, self);
    BeginGifTag(&f, (s8)color[3] >= 0 ? 0x46 : 6, 1, 0xE);
    AddGifRegisterWrite(&f, 1, (u64)color[0] | ((u64)color[1] << 8) | ((u64)color[2] << 16) | ((u64)color[3] << 24));
    AddGifRegisterWrite(&f, 0x47, flag != 0 ? 0x32001 : 0x32000);
    for (x = 0; x < 0x280; x += 0x20) {
        AddGifRegisterWrite(&f, 5, (u64)((0x6C0 + x) << 4) | ((u64)(0x790 << 4) << 16));
        AddGifRegisterWrite(&f, 5, (u64)((0x6E0 + x) << 4) | ((u64)(0x870 << 4) << 16));
    }
    AddGifRegisterWrite(&f, 0x47, 0x70000);
    EndGifPacket(&f);
}

void func_001688B8(void)
{
    Rgba4 k;
    Rgba4 t;

    ResetGs(0, 1, 2, 1);
    u8* s0 = D_00262490;
    SetUpDoubleBuffer(s0, 0, 0x280, 0xE0, 3, 0x30, 0);
    u8* p = s0;
    s32 end = (s32)s0 + 0x50;
    do {
        *(s32*)p &= -2;
        p[1] = 0x80;
        *(s32*)p |= 0x20;
        p += 0x28;
    } while ((s32)p < end);
    k.r = 0;
    k.g = 0;
    k.b = 0;
    k.a = 0x80;
    t = k;
    FillScreenColor(D_002BDC20, &t, 0);
    t = k;
    FillScreenColor(D_002BE1A0, &t, 0);
    t = k;
    FillScreenColor(D_002BDEE0, &t, 1);
    D_002BE460 = CreateLockSemaphore((void*)0, (void*)1);
    D_002BE464 = CreateLockSemaphore((void*)0, (void*)1);
    AddInterruptHandler(2, HandleVblankStart, 0);
    EnableInterruptCause(2);
    AddInterruptHandler(0, HandleGsFinish, 0);
    EnableInterruptCause(0);
    InitMeshQueue();
    ResetDisplayBuffers();
}

void func_00168A48(DmaChainBlock* b)
{
    s32 i = 0;
    SyncDataCache(0);
    do {
        void* p;
        if (((i + g_displayFrameCounter) & 1) != 0) {
            p = D_002624E0;
        } else {
            p = D_002625D0;
        }
        SendDrawEnvironment(p);
        i++;
        StartDmaChain(g_gifChannel, b);
    } while (i < 2);
    WaitDmaChannel(g_gifChannel, 0, 0);
}

void func_00168AF8(void)
{
    DmaChainBlock a;
    DmaChainBlock b;

    InitPacketBuffer(&a);
    UsePacketBufferMemory(&a, 2, &b);
    AddDmaRefTag(&a, 0x2C, D_002BE1A0);
    AddDmaEndTag(&a);
    DetachPacketBuffer(&a, 0, 0);
    SendPacketToBothBuffers(&b);
}

void func_00168B68(f32 t)
{
    FadePacket f;
    s32 i = 0;
    s32 n;

    InitGifPacket(&f);
    n = (s32)(t * 59.999996f);
    SignalDisplaySync();
    D_002626CC = 0;
    if (n > 0) {
        do {
            f32 x = ((f32)i + 1.0f) / (f32)n;
            f32 y = x * 255.0f;
            s32 v = (s32)(x * y);
            i++;
            UsePacketBufferMemory(&f, 0x40, &f.value);
            BeginDmaTag(&f);
            WriteColoredSpritePacket(0.0f, 0.0f, 640.0f, 492.80002f, 0, 0, 0, v, &f);
            BeginGifTag(&f, 0, 1, 0xE);
            AddGifRegisterWrite(&f, 0x61, 0);
            EndGifPacket(&f);
            AddDmaEndTag(&f);
            DetachPacketBuffer(&f, 0, 0);
            SendGsPacketAndWait(g_gifChannel, &f.value);
            FlipDisplayFrame();
        } while (i < n);
    }
}

void func_00168D00()
{
    InitBumpAllocator(&g_bumpAllocator,0x1E00,0x4000);
    g_meshQueueCount=0;
}

u32 func_00168D30(u32 n) { u32 count = 0; u32 value = 1; while (value < n && count < 31) { value <<= 1; count++; } return count; }

void func_00168D68(BumpAllocator* p, s32 value, s32 other) { p->next = value; p->start = value; p->limit = other; }

void func_00168D78(BumpAllocator* p) { p->next = p->start; }

s32 func_00168D88(s32* self,s32 size)
{
    s32 old=self[1];
    self[1]=old+size;
    return old;
}

void func_00168D98(u32 dbp, u32 dbw, u32 dpsm, u64 rrw, u32 rrh, s32 x, void* ctx)
{
    BeginGifTag(ctx, 0, 1, 0xE);
    AddGifRegisterWrite(ctx, 0x50, ((u64)dbp << 32) | ((u64)dbw << 48) | ((u64)dpsm << 56));
    AddGifRegisterWrite(ctx, 0x51, 0);
    AddGifRegisterWrite(ctx, 0x52, rrw | ((u64)rrh << 32));
    AddGifRegisterWrite(ctx, 0x53, 0);
    AddGifImageTag(ctx, x);
}

void func_00168E78(PaletteRecord* self, u32 a1){
 GsTex0* bits = (GsTex0*)&self->f10;
 bits->cbp = a1;
 bits->psm = (self->f4 <= 0x10) ? 0x14 : 0x13;
 bits->cpsm=0; bits->csm=0; bits->csa=0; bits->cld=1;}

void func_00168F48(PaletteRecord* e, s32 v, void* ctx)
{
    s32 step = (e->f4 > 16) ? 16 : 8;
    s32 n = e->f4 - 1;
    TransferBase p;
    p.v = v;
    BeginImageTransfer(p, 1, 0, step, ((n + step) & -step) / step, e->fC, ctx);
}

void func_00168FB0(ImageRecord* self, u32 a1)
{
    GsTex0* bits = (GsTex0*)&self->f18;
    bits->tbp = a1;
    bits->tbw = self->f9;
    bits->psm = self->f8;
    bits->tw = CeilLog2(self->f0) & 0xF;
    bits->th = CeilLog2(self->f2) & 0xF;
    bits->tcc = 1;
}

void func_00169088(ImageRecord* d, u32 dbp, void* ctx)
{
    BeginImageTransfer(dbp, d->f9, d->f8, d->f0, d->f2, d->f14, ctx);
}

s32 func_001690C0(s32 mask, BumpAllocator* b, PacketWriter* c)
{
    s32 saved;

    if (c != 0) {
        saved = c->curS;
    } else {
        saved = 0;
    }
    for (s32 i = 0; i < g_imageRecordCountB; i++) {
        PaletteRecord* e = &g_imageRecordsB[i];
        if ((e->f0 & mask) == mask) {
            s32 v = AllocateBump(b, e->f6);
            BuildPaletteTexRegister(e, v);
            if (c != 0) {
                StartPaletteUpload(e, v, c);
                AddDmaRefTag(c, e->fC, e->f8);
            }
        }
    }
    if ((b->next & 0x7F) != 0) {
        AllocateBump(b, 0x80 - (b->next & 0x7F));
    }
    for (s32 i = 0; i < g_imageRecordCountA; i++) {
        ImageRecord* e = &g_imageRecordsA[i];
        if ((e->f4 & mask) == mask) {
            s32 v;
            if (e->f8 == 0 && (b->next & 0x1F) != 0) {
                AllocateBump(b, 0x20 - (b->next & 0x1F));
            }
            v = AllocateBump(b, e->f0A);
            BuildImageTexRegister(e, v);
            if (c != 0) {
                StartImageUpload(e, v, c);
                AddDmaRefTag(c, e->f14, e->f10);
            }
        }
    }
    if (c == 0) {
        return 0;
    }
    return (c->curS ^ saved) != 0;
}

void func_001692B0(void* self, void* arg)
{
    TexturePacket f;

    if (self == 0) {
        return;
    }
    InitGifPacket(&f);
    PushBackMemoryMark();
    AllocateTempPacketBuffer(&f, ((g_imageSlotsB * 2 + g_imageSlotsB + g_imageSlotsA) * 8) | 4);
    BeginDmaTag(&f);
    if (PlaceMaskedImages(self, arg, &f) != 0) {
        BeginGifTag(&f, 0, 1, 0xE);
        AddGifRegisterWrite(&f, 0x3F, 0);
        AddGifRegisterWrite(&f, 0x61, 0);
        EndGifPacket(&f);
        AddDmaEndTag(&f);
        DetachPacketBuffer(&f, 0, &f.value);
        SendGsPacketAndWait(g_gifChannel, f.value);
    }
    PopBackMemoryMark();
}

s32 func_001693A8(void* self)
{
    TextureUploadPacket f;

    InitGifPacket(&f);
    f.out = 0;
    InitBumpAllocator(f.span, 0x1400, 0x1E00);
    PushBackMemoryMark();
    AllocateTempPacketBuffer(&f, ((g_imageSlotsB * 2 + g_imageSlotsB + g_imageSlotsA) * 8) | 4);
    BeginDmaTag(&f);
    if (PlaceMaskedImages(self, f.span, &f) != 0) {
        BeginGifTag(&f, 0, 1, 0xE);
        AddGifRegisterWrite(&f, 0x3F, 0);
        EndGifPacket(&f);
        AddDmaEndTag(&f);
        DetachPacketBufferCopy(&f, 0, 0, &f.out, 7);
        BuildAnimRecordGifPackets(self);
    }
    PopBackMemoryMark();
    return f.out;
}

void func_001694A0(FrameTarget* self)
{
    CopyMemory(self->dst, (void*)self->value, self->count);
    s32 flag = self->flag;
    if (flag != 0) {
        QueuedGifTags* d = self->dst;
        s32 a = d->f0;
        s32 b = d->f10;
        a = a | 0x8000;
        a = a | flag;
        b = b | 0x8000;
        d->f0 = a;
        d->f10 = b;
    }
}

void func_001694F8(StripMesh* a0, FrameSource* a1, s32 a2, s32 a3, s32 a4, AnimCursor* a5)
{
    FrameTarget local;
    FrameTarget* e;
    s32 link;
    s32 idx;
    s32 count;
    s32 n;
    s32 scale;
    s32 base;
    s32 off;

    link = 0;
    if (a5 != 0) {
        link = a5->flags & 1;
    }
    count = g_meshQueueCount;
    if (count >= 0x4000) {
        goto local_path;
    }
    if (a0 == 0) {
        goto pool_path;
    }
    if ((a0->flags & 0x10000000) == 0) {
        goto pool_path;
    }
    if (link != 0) {
        goto pool_path;
    }
local_path:
    link = (count < 0x4000) ? link : 0;
    e = &local;
    goto store;
pool_path:
    n = g_meshQueueCount;
    e = &D_0027DC20[n];
    n++;
    g_meshQueueCount = n;
store:
    e->count = a3;
    idx = 0;
    if (a5 != 0) {
        idx = a5->frame;
    }
    scale = a1->stride;
    base = a1->base;
    off = idx * scale;
    e->dstAddr = a2;
    e->flag = a4;
    e->value = base + (off << 4);
    SubmitMeshQueueEntry(e);
    if (link != 0) {
        FrameLink* p = (FrameLink*)AllocateZeroedFrontMemory(12);
        if (p != 0) {
            p->src = a1;
            p->dst = e;
            p->next = a5->links;
            a5->links = p;
        }
    }
}

void func_00169608(s32 a0, s32 a1, AnimCursor* a2)
{
    FrameTarget local;
    FrameTarget* e;
    s32 count = g_meshQueueCount;

    if (count >= 0x4000) {
        e = &local;
    } else {
        e = &D_0027DC20[count];
        g_meshQueueCount = count + 1;
    }
    e->count = a1;
    e->value = (s32)a2 + 0xC;
    e->dstAddr = a0;
    e->flag = 0;
    SubmitMeshQueueEntry(e);
    if (g_meshQueueCount < 0x4000) {
        FrameLink* p = (FrameLink*)AllocateZeroedFrontMemory(12);
        p->dst = e;
        p->src = 0;
        p->next = a2->links;
        a2->links = p;
    }
}

void func_001696B8(s32 idx, u32 lo, u32 take, u32 give)
{
    u32 end = take + lo;

    if (idx < g_meshQueueCount) {
        FrameTarget* e = &D_0027DC20[idx];
        s32 n = g_meshQueueCount - idx;

        do {
            if (e->dstAddr >= take && e->dstAddr < end) {
                e->dstAddr = give + (e->dstAddr - take);
            }
            e++;
            n--;
        } while (n != 0);
    }
}

void func_00169718(void)
{
    s32 i;

    for (i = 0; i < g_meshQueueCount; i++) {
        SubmitMeshQueueEntry(&D_0027DC20[i]);
    }
}

s32 func_00169780(u32 mask)
{
    BumpAllocator span;
    PacketWriter fa;
    PacketWriter fb;
    u8 buf[0xA0];
    s32 o0;
    s32 o1;
    s32 res;
    s32 i;

    InitBumpAllocator(&span, 0x1400, 0x1E00);
    InitGifPacket(&fa);
    res = 0;
    InitPacketWriter(&fb);
    PushBackMemoryMark();
    AllocateTempPacketBuffer(&fb, (g_imageSlotsB * 2 + g_imageSlotsB + g_imageSlotsA) * 10 + 4);
    BeginDmaTag(&fb);
    WriteVifFlush(&fb);
    for (i = 0; i < g_imageRecordCountB; i++) {
        PaletteRecord* e = (PaletteRecord*)((*(u8**)&g_imageRecordsB) + i * 0x18);
        if ((e->f0 & mask) == mask) {
            RewindPacketBuffer(&fa);
            UsePacketBufferMemory(&fa, 0xA, buf);
            s32 n = AllocateBump(&span, e->f6);
            BuildPaletteTexRegister(e, n);
            StartPaletteUpload(e, n, &fa);
            *(u64*)(fa.curS - 0x10) |= 0x8000;
            DetachPacketBuffer(&fa, &o0, &o1);
            WriteVifDirect(&fb, o0, o1, 0);
            WriteVifDirectRef(&fb, e->fC, e->f8, 0);
            if (e->f0 & 0x40000000) {
                e->f0 = 0x40000000;
            }
        }
    }
    if (g_imageRecordCountA > 0) {
        i = 0;
        do {
            ImageRecord* e = (ImageRecord*)((*(u8**)&g_imageRecordsA) + i * 0x20);
            if ((e->f4 & mask) == mask) {
                RewindPacketBuffer(&fa);
                UsePacketBufferMemory(&fa, 0xA, buf);
                s32 n = AllocateBump(&span, e->f0A);
                BuildImageTexRegister(e, n);
                StartImageUpload(e, n, &fa);
                *(u64*)(fa.curS - 0x10) |= 0x8000;
                DetachPacketBuffer(&fa, &o0, &o1);
                WriteVifDirect(&fb, o0, o1, 0);
                WriteVifDirectRef(&fb, e->f14, e->f10, 0);
                if (e->f4 & 0x40000000) {
                    e->f4 = 0x40000000;
                }
            }
            i++;
        } while (i < g_imageRecordCountA);
    }
    if (span.next > span.start) {
        RewindPacketBuffer(&fa);
        UsePacketBufferMemory(&fa, 0xA, buf);
        BeginGifTag(&fa, 0, 1, 0xE);
        AddGifRegisterWrite(&fa, 0x3F, 0);
        EndGifPacket(&fa);
        DetachPacketBuffer(&fa, &o0, &o1);
        WriteVifDirect(&fb, o0, o1, 0);
        WriteVifFlush(&fb);
        CloseDmaTag(&fb);
        *(u64*)fb.curS = 0x60000000;
        fb.curS += 0x10;
        DetachPacketBufferCopy(&fb, 0, 0, &res, 7);
        BuildAnimRecordGifPackets(mask);
    }
    PopBackMemoryMark();
    return res;
}

void func_00169B18(TextureHeader* src, void* dst)
{
    s32 w = 1 << (s32)((src->tex0 >> 26) & 0xF);
    s32 cap = 64;
    if (cap < w) cap = w;
    s32 f = (s32)(src->tex0 & 0x3FFF) >> 5;
    s32 m = 1 << (s32)((src->tex0 >> 30) & 0xF);
    BeginGifTag(dst, 0x200, 1, 0xE);
    AddGifRegisterWrite(dst, 0x4D, (u64)(cap / 64) << 16 | (u64)f);
    AddGifRegisterWrite(dst, 0x4F, 0x30000000 | (u64)f | (u64)0x8000 << 17);
    AddGifRegisterWrite(dst, 0x19, 0);
    AddGifRegisterWrite(dst, 0x41, (u64)(w - 1) << 16 | (u64)(m - 1) << 48);
    AddGifRegisterWrite(dst, 0x48, 0x31001);
    AddGifRegisterWrite(dst, 0x43, 0x44);
}

void func_00169C58()
{
    SetListLinkOffset(&g_targetCurveList, 0x38);
    SetListLinkOffset(&g_targetPointList, 0x50);
    SetListLinkOffset(&g_partList, 0x558);
}

void func_00169CA0()
{
    ClearList(&g_targetCurveList);
    ClearList(&g_targetPointList);
    ClearList(&g_partList);
}

void func_00169CD8(TargetCurve* self)
{
    InitObject(self);
    self->targetId = -1;
    self->f4C = 1;
    self->f50 = 3;
    self->f58 = 3.4028235e+38f;
}

void func_00169D20(TargetCurve* self)
{
    RegisterObject(self);
    AppendToList(&g_targetCurveList, self);
}

void func_00169D58(TargetCurve* self)
{
    UnregisterObject(self);
    RemoveFromList(&g_targetCurveList, self);
}

void func_00169D90(TargetCurve* self)
{
    if (self->targetId != -1) {
        TargetedObject* r = (TargetedObject*)FindFirstObjectByIdMode4(self->world, self->targetId, self->parent);
        self->target = r;
        r->f398 = 0;
    }
}

void func_00169DD8(TargetCurve* self)
{
    PathCurveKeptBits saved = self->keep;
    CopyObjectData(self);
    self->keep = saved;
}

ASM_FUNC(func_00169E20);

void func_00169FC0(TargetCurve* self, f32* out, void* a2, void* a3)
{
    CurveProbe f;
    u8* node = (u8*)GetActiveSwitchedCollider();
    PathCurve* o = self->curve;
    f.c = 1;
    func_00128018(0, (s32)self->parent, node + 0x140, &f.a);
    func_001280C0(0, (s32)self->parent, (void*)&g_unitZVector, &f.b);
    if (o->vt->m10 != 0) {
        o->vt->m10(o, &f.a, &f.b, 0, 0, 0, &f.x);
    }
    if (o->wrap == 0) {
        f32 k = 30.0f;
        f32 t = self->curve->vt->m08(self->curve) - k;
        f32 r = f.x;
        if (r < k) {
            r = k;
        } else if (t < r) {
            r = t;
        }
        f.x = r;
    }
    PlaceOnTargetCurve(self, a2, a3, f.x);
    *out = f.x;
}

void func_0016A100(TargetPoint* self)
{
    InitObject(self);
    f32 k = 3.4028235e+38f;
    self->targetId = -1;
    self->f68 = 1;
    self->f70 = k;
}

void func_0016A140(TargetPoint* self)
{
    RegisterObject(self);
    AppendToList(&g_targetPointList, self);
}

void func_0016A178(TargetPoint* self)
{
    UnregisterObject(self);
    RemoveFromList(&g_targetPointList, self);
}

void func_0016A1B0(TargetPoint* self)
{
    if (self->targetId != -1) {
        TargetedObject* r = (TargetedObject*)FindFirstObjectByIdMode4(self->world, self->targetId, self->parent);
        self->target = r;
        r->f398 = 0;
    }
}

void func_0016A1F8(TargetPoint* self)
{
    KeptBits saved = self->keep;
    CopyObjectData(self);
    self->keep = saved;
}

ASM_FUNC(func_0016A240);

ASM_FUNC(func_0016A320);

void func_0016A3A8(ListedCollisionPart* self)
{
    f32 k = 3.0f;
    InitCollider(self);
    func_00129FB0(self, k);
    func_0012A080(self, k);
    func_0012A150(self, k);
    func_0012A270(self, 2.0f);
    self->f568 = 300.0f;
}

void func_0016A420(ListedCollisionPart* self)
{
    Rec2195_224* b;
    Quad16* dst;
    Quad16* src;

    LoadCollider(self);
    if (self->f224 == 0) {
        self->f224 = (Rec2195_224*)AllocateZeroedFrontMemory(0xC0);

    }
    b = self->f224;
    b->fB0 |= 1;
    dst = (Quad16*)self->f224;
    src = (Quad16*)&g_identityMatrix;
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

void func_0016A490(ListedCollisionPart* self)
{
    RegisterCollider(self);
    AppendToList(&g_partList, self);
}

void func_0016A4C8(ListedCollisionPart* self)
{
    UnregisterCollider(self);
    RemoveFromList(&g_partList, self);
}

void func_0016A500(ListedCollisionPart* self)
{
    Link02 tmp = self->listLink;
    CopyCollider(self);
    self->listLink = tmp;
}

s32 func_0016A548(Collider* a0, Collider* a1)
{
    if ((void*)a1 == g_player && (void*)a0 == ((Player*)a1)->heldObject) {
        return 1;
    }
    return TestCollidersMayContact(a0, a1);
}

void func_0016A580(ListedCollisionPart* self, f32 t)
{
    Mat3U buf;

    StepCollider(self, t);
    if (self->f550 != 0) {
        return;
    }
    RotateMatrixUpright((Mat02*)((u8*)self + 0xD0), 0, &buf);
    func_001B91A8(self, &buf, (s32)self->p214, (void*)&D_00248D30, (s32)self->p218, t);
}

void func_0016A5F0(PooledObject* self, s32 v)
{
    HoldMatrices f;

    if (self->state == v) {
        return;
    }
    if (self->state == 1) {
        self->desc->m15(self, 0);
        SetColliderAnchors(self, 0, 0, 0, 0);
        TriggerScriptEvent(self, 3, 0, 0);
    }
    if (v == 1) {
        self->desc->m15(self, (BaseObject*)g_player);
        self->desc02()->m20(self, (Vec02*)&D_00248D30);
        self->desc02()->m21(self, (Vec02*)&D_00248D30);
        SetColliderAnchors(self, 3, 0, 3, 0);
        RotateMatrixUpright((u8*)g_player + 0x110, 0, f.a);
        RotateMatrixUpright((u8*)self + 0x110, f.c, f.b);
        MatrixToAxisAngle(f.c, f.e, f.d);
        MultiplyMatrices3x3(f.a, f.b, (s32)self->f224);
        TriggerScriptEvent(self, 2, 0, 0);
    }
    self->state = v;
    self->stateTime = g_gameTime[0];
}

s32 func_0016A758(PlacedObject* self)
{
    ChildListWalk w(&self->children);
    s32 count = 0;
    void* node = w.First();
    while (node != 0) {
        if (IsObjectOfKind(node, 70)) {
            s32 x = ((PooledObject*)node)->state;
            if (1 < (u32)(x - 3)) {
            } else {
                count++;
            }
        }
        node = w.Next();
    }
    return count;
}

void* func_0016A820(PlacedObject* self)
{
    ChildListWalk w(&self->children);
    void* best = 0;
    f32 bestF = 3.4028235e+38f;
    void* node = w.First();
    while (node != 0) {
        if (IsObjectOfKind(node, 0x46)) {
            PooledObject* n = (PooledObject*)node;
            if (n->state == 4 && n->stateTime < bestF) {
                best = node;
                bestF = n->stateTime;
            }
        }
        node = w.Next();
    }
    return best;
}

ASM_FUNC(func_0016A910);
