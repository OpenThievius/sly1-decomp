// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "listed_collision_part.h"
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

struct Ent_167E08 { u8 pad0[0x328]; s32 f328; };
struct Out_167E08 { s32 count; Ent_167E08** items; };

void func_001C72A0(void* self);
void* func_0015A448(void* a, s32 b, void* c);
void func_0018D608(void);
void func_0018D6F0(void);
void func_0012D1B0(void* a, void* b, s32* c, void** d);
void* func_001EFA30(void);
void func_001EFA60(void* a, void* b);

void func_001C6F48(void* self);
void func_00167D68(C0A* self);

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

struct Blob_168AF8 { u8 bytes[0x20]; };

extern u8 D_002BE1A0[];
void* func_00152888(Blob_168AF8* a);
void func_001529C8(Blob_168AF8* a, s32 n, Blob_168AF8* b);
void func_00152B80(Blob_168AF8* a, s32 n, void* table);
void func_00152D30(Blob_168AF8* a);
void func_001529E0(Blob_168AF8* a, s32 x, s32 y);
void func_00168A48(Blob_168AF8* b);

struct Frame_1692B0 : V24A0 { s32 value; };

extern s32 D_00274514;
extern s32 D_00274510;
extern s32 D_00261F1C;

void* func_001611B8(V24A0* f);
void func_00152980(V24A0* f, s32 size);
void func_00152B38(V24A0* f);
s32 func_001690C0(void* self, void* arg, Frame_1692B0* f);
void func_001613C0(V24A0* f, s32 a, s32 b, s32 c);
void func_00161708(V24A0* f, s32 a, u64 b);
void func_00161200(V24A0* f);
void func_00152D30(V24A0* f);
void func_001529E0(V24A0* f, s32 a, s32* out);
void func_001686E8(s32 a, s32 b);

struct Ent_1696B8 { s32 a; s32 b; u32 value; s32 d; };

extern Ent_1696B8 D_0027DC20[];

void func_00182D48(void* self);
void func_00152470(void* table, void* self);

void func_00182ED0(void* self);
void func_00152600(void* table, void* self);

struct Res_0015A448 {
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

struct Bits_168FB0 {
    u64 f0 : 14;
    u64 f14 : 6;
    u64 f20 : 6;
    u64 f26 : 4;
    u64 f30 : 4;
    u64 f34 : 1;
    u64 rest : 29;
};

u32 func_00168D30(u32 n);

void func_00168D98(u32 dbp, u32 dbw, u32 dpsm, u64 rrw, u32 rrh, s32 x, void* ctx);

void func_00152438(void* self, s32 value);

void func_00152440(void* self);

struct Pool_1694F8 { s32 f0; s32 f4; s32 f8; s32 fC; };
struct Link_1694F8 { MeshStrip* src; Pool_1694F8* dst; Link_1694F8* next; };

void func_001694A0(void* p);
void* func_0018D5C0(u32 n);

struct Pool_169608 { s32 f0; s32 f4; s32 f8; s32 fC; };
struct Link_169608 { s32 src; Pool_169608* dst; Link_169608* next; };

struct Quad_1688B8 { u8 b0; u8 b1; u8 b2; u8 b3; } __attribute__((packed));

extern u8 D_002BDC20[];
extern u8 D_002BE1A0[];
extern u8 D_002BDEE0[];

void func_00201D60(void* p, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_00168770(void* ctx, Quad_1688B8* v, s32 flag);
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

struct Frame_1693A8 : V24A0 { u8 span[0x10]; s32 out; };

extern s32 D_00274514;
extern s32 D_00274510;

void func_00168D68(void* p, s32 a, s32 b);
s32 func_001690C0(void* self, void* arg, Frame_1693A8* f);
void func_00152A50(V24A0* f, s32 a1, s32 a2, s32* out, s32 a4);
void func_001B3510(void* self);

struct Frame_168B68 : V24A0 { s32 value; u8 pad[0x3F0]; };

extern s32 D_00261F1C;

void func_001529C8(V24A0* f, s32 n, s32* p);
void func_0019DDA0(f32 x, f32 y, f32 z, f32 w, s32 a, s32 b, s32 c, s32 d, Frame_168B68* e);
void func_001529E0(V24A0* f, s32 a, s32 b);
void func_001686E8(s32 a, s32* b);
void func_001683E8(void);

extern s32 D_00274500;
extern s32 D_00274508;
s32 func_00168D88(void* self, s32 size);
void func_00168E78(V24A2_ImgB* e, s32 v);
void func_00168F48(V24A2_ImgB* e, s32 v, void* ctx);
void func_00152B80(void* self, s32 lo, s32 hi);
void func_00168FB0(V24A2_ImgA* e, s32 v);
void func_00169088(V24A2_ImgA* e, s32 v, void* ctx);

struct Bits_168E78 {
    u64 lo : 20;
    u64 f20 : 6;
    u64 mid : 11;
    u64 f37 : 14;
    u64 r51 : 4;
    u64 r55 : 1;
    u64 r56 : 5;
    u64 f61 : 3;
};

void* func_001300E8(void* node, s32 flags);

struct Walk_16A758 {
    List01* iter;
    void* cursor;
    s32 link;
    void* prev;

    Walk_16A758(List01* i)
    {
        cursor = i;
        iter = i;
        link = i->offset;
        prev = g_activeListFrames;
        g_activeListFrames = (ListFrame*)this;
    }
    ~Walk_16A758() { g_activeListFrames = (ListFrame*)prev; }
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

struct __attribute__((aligned(16))) Quad_169FC0 { s32 v[4]; };

struct Frame_169FC0 {
    Quad_169FC0 a;
    Quad_169FC0 b;
    s32 c;
    u8 pad[0xC];
    f32 x;
};

struct Obj_169FC0 {
    void** vt;
    u8 pad4[4];
    s32 f8;
};

struct Self_169FC0 {
    u8 pad0[0x18];
    s32 f18;
    u8 pad1[0x34 - 0x1C];
    Obj_169FC0* f34;
};

void* func_001925F0(void);
s32 func_00128018(void* a, s32 b, void* c, void* d);
void func_001280C0(void* a, s32 b, void* c, void* d);
void func_00169E20(void* a0, void* a1, void* a2, f32 f);

typedef void (*VFn_16A5F0)(void* self, void* a);

struct Obj_16A5F0 {
    VFn_16A5F0* vtbl;
    u8 pad4[0x224 - 4];
    s32 f224;
    u8 pad228[0x550 - 0x228];
    s32 f550;
    f32 f554;
};

struct Frame_16A5F0 {
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

struct Walk_16A820 {
    List01* iter;
    void* cursor;
    s32 link;
    void* prev;

    Walk_16A820(List01* i)
    {
        cursor = i;
        iter = i;
        link = i->offset;
        prev = g_activeListFrames;
        g_activeListFrames = (ListFrame*)this;
    }
    ~Walk_16A820() { g_activeListFrames = (ListFrame*)prev; }
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

struct Node_16A820 {
    u8 pad0[0x550];
    s32 f550;
    f32 f554;
};

struct Arg_001683B8;
s32 func_001F6B60(Arg_001683B8* a);

struct Dst_1694A0 {
    s32 f0;
    u8 pad0[0xC];
    s32 f10;
};

struct Rec_1694A0 {
    s32 f0;
    s32 f4;
    Dst_1694A0* f8;
    s32 fC;
};

void func_0018D800(Dst_1694A0* dst, void* src, s32 count);

struct Self_1686E8 {
    u8 pad0[4];
};

s32 func_00202120(void);
s32 func_00202058(s32 a);
void func_001F6C20(s32 a);
void func_00202A80(Self_1686E8* a, void* b);
s32 func_001F6B60(s32 a);

void func_001BAC30(Collider* self);
void* func_0018D5C0(s32 bytes);

void func_001B9338(Collider* self, f32 t);
void func_00189378(Mat02* sub, s32 zero, Mat3U* out);
void func_001B91A8(Collider* self, Mat3U* out, s32 a, void* table, s32 b, f32 t);
extern f32 D_0026185C[];

struct Dbp_168F48 { s32 v; };

void func_00168D98(Dbp_168F48 dbp, u32 dbw, u32 dpsm, u64 rrw, u32 rrh, s32 x, void* ctx);

void func_001529C8(V24A0* f, s32 n, V24A0* p);

struct Pm_168130 { u32 en1 : 1; u32 rest : 31; u32 hi : 32; };
struct Fb_168130 { u32 fbp : 9; u32 fbw : 6; u32 psm : 5; u32 pad0 : 12; u32 dbx : 11; u32 dby : 11; u32 pad1 : 10; };
struct Disp_168130 { u32 dx : 12; u32 dy : 11; u32 magh : 4; u32 magv : 2; u32 pad0 : 3; u32 dw : 12; u32 dh : 11; u32 pad1 : 9; };
struct Rec_168130 { Pm_168130 pmode; u64 pad; Fb_168130 dispfb; Disp_168130 display; u64 pad2; };
struct Gs_168130 {
    Pm_168130 pmode; u8 pad0[0x70 - 8];
    Fb_168130 dispfb2; u8 pad1[8];
    Disp_168130 display2; u8 pad2[0x1000 - 0x88];
    u32 csr;
};

struct Out_16B860;
void func_00137228(Out_16B860* out, f32 x, f32 y);
void func_00137238(Out_16B860* out, f32 x, f32 y);
void func_00137248(Out_16B860* out, s32* value);
void func_00137260(Out_16B860* out, s32 flag);
void func_00137268(Out_16B860* out, s32 flag);
struct Out_16B860 {
    u8 b[32];
    void Pos(f32 x, f32 y) { func_00137228(this, x, y); }
    void Size(f32 x, f32 y) { func_00137238(this, x, y); }
    void Color(s32* c) { func_00137248(this, c); }
    void FlagA(s32 f) { func_00137260(this, f); }
    void FlagB(s32 f) { func_00137268(this, f); }
};

extern s32 D_00274508;
extern s32 D_00274500;
extern s32 D_00274514;
extern s32 D_00274510;

void func_00168D68(BumpAllocator* p, s32 a, s32 b);
void* func_001EE318(V24A0* f);
void func_001EE450(V24A0* f);
void func_001528E0(V24A0* f);
void func_001529C8(V24A0* f, s32 n, u8* buf);
s32 func_00168D88(BumpAllocator* p, s32 size);
void func_00168F48(V24A2_ImgB* e, s32 v, V24A0* f);
void func_00169088(V24A2_ImgA* e, s32 v, V24A0* f);
void func_001529E0(V24A0* f, s32* o0, s32* o1);
void func_001EE7D0(V24A0* f, s32 a, s32 b, s32 c);
void func_001EE850(V24A0* f, s32 a, s32 b, s32 c);
void func_00152D70(V24A0* f);
void func_00152A50(V24A0* f, s32 a, s32 b, s32* out, s32 c);
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

void func_00167D68(C0A* self)
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

void func_00167E08(C0A* self)
{
    Out_167E08 out;
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
            Ent_167E08* e = out.items[i];
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
    Pm_168130 pm = ((Rec_168130*)&D_00262490)[i].pmode;

    if (field != (s32)((((Gs_168130*)0x12000000)->csr >> 13) & 1)) {
        Disp_168130 d = ((Rec_168130*)&D_00262490)[i].display;
        Fb_168130 fb = ((Rec_168130*)&D_00262490)[i].dispfb;
        d.dh = d.dh - 1;
        if (field != 0) {
            d.dy = d.dy + 1;
        } else {
            fb.dby = fb.dby + 1;
        }
        ((Gs_168130*)0x12000000)->display2 = d;
        ((Gs_168130*)0x12000000)->dispfb2 = fb;
        pm.en1 = 1;
    }
    ((Gs_168130*)0x12000000)->pmode = pm;
}

ASM_FUNC(func_001682C0);

void func_001683B8(void) {
    D_002BE46C = 1;
    AwaitSemaphore((Arg_001683B8*)D_002BE460);
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

void func_001686E8(Self_1686E8* self, void* b)
{
    D_002BE468 = 1;
    *(volatile u64*)0x12001000 |= 2;
    s32 r = GetGsInterruptMask();
    SwapGsInterruptMask(r & -0x201);
    SyncDataCache(0);
    StartDmaChain(self, b);
    AwaitSemaphore(D_002BE464);
}

void func_00168770(V24A0* self, u8* color, s32 flag)
{
    V24A0 f;
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
    Quad_1688B8 k;
    Quad_1688B8 t;

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
    k.b0 = 0;
    k.b1 = 0;
    k.b2 = 0;
    k.b3 = 0x80;
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

void func_00168A48(Blob_168AF8* b)
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
    Blob_168AF8 a;
    Blob_168AF8 b;

    InitPacketBuffer(&a);
    UsePacketBufferMemory(&a, 2, &b);
    AddDmaRefTag(&a, 0x2C, D_002BE1A0);
    AddDmaEndTag(&a);
    DetachPacketBuffer(&a, 0, 0);
    SendPacketToBothBuffers(&b);
}

void func_00168B68(f32 t)
{
    Frame_168B68 f;
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

void func_00168E78(V24A2_ImgB* self, u32 a1){
 Bits_168E78* bits = (Bits_168E78*)&self->f10;
 bits->f37 = a1;
 bits->f20 = (self->f4 <= 0x10) ? 0x14 : 0x13;
 bits->r51=0; bits->r55=0; bits->r56=0; bits->f61=1;}

void func_00168F48(V24A2_ImgB* e, s32 v, void* ctx)
{
    s32 step = (e->f4 > 16) ? 16 : 8;
    s32 n = e->f4 - 1;
    Dbp_168F48 p;
    p.v = v;
    BeginImageTransfer(p, 1, 0, step, ((n + step) & -step) / step, e->fC, ctx);
}

void func_00168FB0(V24A2_ImgA* self, u32 a1)
{
    Bits_168FB0* bits = (Bits_168FB0*)&self->f18;
    bits->f0 = a1;
    bits->f14 = self->f9;
    bits->f20 = self->f8;
    bits->f26 = CeilLog2(self->f0) & 0xF;
    bits->f30 = CeilLog2(self->f2) & 0xF;
    bits->f34 = 1;
}

void func_00169088(V24A2_ImgA* d, u32 dbp, void* ctx)
{
    BeginImageTransfer(dbp, d->f9, d->f8, d->f0, d->f2, d->f14, ctx);
}

s32 func_001690C0(s32 mask, BumpAllocator* b, V24A0* c)
{
    s32 saved;

    if (c != 0) {
        saved = c->curS;
    } else {
        saved = 0;
    }
    for (s32 i = 0; i < g_imageRecordCountB; i++) {
        V24A2_ImgB* e = &g_imageRecordsB[i];
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
        V24A2_ImgA* e = &g_imageRecordsA[i];
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
    Frame_1692B0 f;

    if (self == 0) {
        return;
    }
    InitGifPacket(&f);
    PushBackMemoryMark();
    AllocateTempPacketBuffer(&f, ((D_00274514 * 2 + D_00274514 + D_00274510) * 8) | 4);
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
    Frame_1693A8 f;

    InitGifPacket(&f);
    f.out = 0;
    InitBumpAllocator(f.span, 0x1400, 0x1E00);
    PushBackMemoryMark();
    AllocateTempPacketBuffer(&f, ((D_00274514 * 2 + D_00274514 + D_00274510) * 8) | 4);
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

void func_001694A0(Rec_1694A0* self)
{
    CopyMemory(self->f8, (void*)self->f4, self->f0);
    s32 flag = self->fC;
    if (flag != 0) {
        Dst_1694A0* d = self->f8;
        s32 a = d->f0;
        s32 b = d->f10;
        a = a | 0x8000;
        a = a | flag;
        b = b | 0x8000;
        d->f0 = a;
        d->f10 = b;
    }
}

void func_001694F8(StripMesh* a0, MeshStrip* a1, s32 a2, s32 a3, s32 a4, MeshNode* a5)
{
    Pool_1694F8 local;
    Pool_1694F8* e;
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
    e = (Pool_1694F8*)&D_0027DC20[n];
    n++;
    g_meshQueueCount = n;
store:
    e->f0 = a3;
    idx = 0;
    if (a5 != 0) {
        idx = a5->index;
    }
    scale = a1->count;
    base = a1->base;
    off = idx * scale;
    e->f8 = a2;
    e->fC = a4;
    e->f4 = base + (off << 4);
    SubmitMeshQueueEntry(e);
    if (link != 0) {
        Link_1694F8* p = (Link_1694F8*)AllocateZeroedFrontMemory(12);
        if (p != 0) {
            p->src = a1;
            p->dst = e;
            p->next = (Link_1694F8*)a5->links;
            a5->links = p;
        }
    }
}

void func_00169608(s32 a0, s32 a1, MeshNode* a2)
{
    Pool_169608 local;
    Pool_169608* e;
    s32 count = g_meshQueueCount;

    if (count >= 0x4000) {
        e = &local;
    } else {
        e = (Pool_169608*)&D_0027DC20[count];
        g_meshQueueCount = count + 1;
    }
    e->f0 = a1;
    e->f4 = (s32)a2 + 0xC;
    e->f8 = a0;
    e->fC = 0;
    SubmitMeshQueueEntry(e);
    if (g_meshQueueCount < 0x4000) {
        Link_169608* p = (Link_169608*)AllocateZeroedFrontMemory(12);
        p->dst = e;
        p->src = 0;
        p->next = (Link_169608*)a2->links;
        a2->links = p;
    }
}

void func_001696B8(s32 idx, u32 lo, u32 take, u32 give)
{
    u32 end = take + lo;

    if (idx < g_meshQueueCount) {
        Ent_1696B8* e = &D_0027DC20[idx];
        s32 n = g_meshQueueCount - idx;

        do {
            if (e->value >= take && e->value < end) {
                e->value = give + (e->value - take);
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
    V24A0 fa;
    V24A0 fb;
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
    AllocateTempPacketBuffer(&fb, (D_00274514 * 2 + D_00274514 + D_00274510) * 10 + 4);
    BeginDmaTag(&fb);
    WriteVifFlush(&fb);
    for (i = 0; i < g_imageRecordCountB; i++) {
        V24A2_ImgB* e = (V24A2_ImgB*)((*(u8**)&g_imageRecordsB) + i * 0x18);
        if ((e->f0 & mask) == mask) {
            RewindPacketBuffer(&fa);
            UsePacketBufferMemory(&fa, 0xA, buf);
            s32 n = AllocateBump(&span, e->f6);
            BuildPaletteTexRegister(e, n);
            StartPaletteUpload(e, n, &fa);
            *(u64*)(fa.curS - 0x10) |= 0x8000;
            DetachPacketBuffer(&fa, &o0, &o1);
            func_001EE7D0(&fb, o0, o1, 0);
            func_001EE850(&fb, e->fC, e->f8, 0);
            if (e->f0 & 0x40000000) {
                e->f0 = 0x40000000;
            }
        }
    }
    if (g_imageRecordCountA > 0) {
        i = 0;
        do {
            V24A2_ImgA* e = (V24A2_ImgA*)((*(u8**)&g_imageRecordsA) + i * 0x20);
            if ((e->f4 & mask) == mask) {
                RewindPacketBuffer(&fa);
                UsePacketBufferMemory(&fa, 0xA, buf);
                s32 n = AllocateBump(&span, e->f0A);
                BuildImageTexRegister(e, n);
                StartImageUpload(e, n, &fa);
                *(u64*)(fa.curS - 0x10) |= 0x8000;
                DetachPacketBuffer(&fa, &o0, &o1);
                func_001EE7D0(&fb, o0, o1, 0);
                func_001EE850(&fb, e->f14, e->f10, 0);
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
        func_001EE7D0(&fb, o0, o1, 0);
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
        Res_0015A448* r = (Res_0015A448*)FindFirstObjectByIdMode4(self->world, self->targetId, self->parent);
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

void func_00169FC0(Self_169FC0* self, f32* out, void* a2, void* a3)
{
    Frame_169FC0 f;
    u8* node = (u8*)GetActiveSwitchedCollider();
    Obj_169FC0* o = self->f34;
    f.c = 1;
    func_00128018(0, self->f18, node + 0x140, &f.a);
    func_001280C0(0, self->f18, (void*)&g_unitZVector, &f.b);
    if (o->vt[10] != 0) {
        ((void (*)(void*, void*, void*, s32, s32, s32, void*))o->vt[10])(o, &f.a, &f.b, 0, 0, 0, &f.x);
    }
    if (o->f8 == 0) {
        f32 k = 30.0f;
        f32 t = ((f32 (*)(void*))self->f34->vt[8])(self->f34) - k;
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

void func_0016A100(C7F* self)
{
    InitObject(self);
    f32 k = 3.4028235e+38f;
    self->targetId = -1;
    self->f68 = 1;
    self->f70 = k;
}

void func_0016A140(C7F* self)
{
    RegisterObject(self);
    AppendToList(&g_targetPointList, self);
}

void func_0016A178(C7F* self)
{
    UnregisterObject(self);
    RemoveFromList(&g_targetPointList, self);
}

void func_0016A1B0(C7F* self)
{
    if (self->targetId != -1) {
        Res_0015A448* r = (Res_0015A448*)FindFirstObjectByIdMode4(self->world, self->targetId, self->parent);
        self->target = r;
        r->f398 = 0;
    }
}

void func_0016A1F8(C7F* self)
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
    func_00189378((Mat02*)((u8*)self + 0xD0), 0, &buf);
    func_001B91A8(self, &buf, (s32)self->p214, (void*)&D_00248D30, (s32)self->p218, t);
}

void func_0016A5F0(Obj_16A5F0* self, s32 v)
{
    Frame_16A5F0 f;

    if (self->f550 == v) {
        return;
    }
    if (self->f550 == 1) {
        self->vtbl[25](self, 0);
        SetColliderAnchors(self, 0, 0, 0, 0);
        TriggerScriptEvent(self, 3, 0, 0);
    }
    if (v == 1) {
        self->vtbl[25](self, g_player);
        self->vtbl[36](self, (void*)&D_00248D30);
        self->vtbl[37](self, (void*)&D_00248D30);
        SetColliderAnchors(self, 3, 0, 3, 0);
        func_00189378((u8*)g_player + 0x110, 0, f.a);
        func_00189378((u8*)self + 0x110, f.c, f.b);
        MatrixToAxisAngle(f.c, f.e, f.d);
        MultiplyMatrices3x3(f.a, f.b, self->f224);
        TriggerScriptEvent(self, 2, 0, 0);
    }
    self->f550 = v;
    self->f554 = g_gameTime[0];
}

s32 func_0016A758(u8* self)
{
    Walk_16A758 w((List01*)(self + 0x34));
    s32 count = 0;
    void* node = w.First();
    while (node != 0) {
        if (IsObjectOfKind(node, 70)) {
            s32 x = *(s32*)((u8*)node + 0x550);
            if (1 < (u32)(x - 3)) {
            } else {
                count++;
            }
        }
        node = w.Next();
    }
    return count;
}

void* func_0016A820(u8* self)
{
    Walk_16A820 w((List01*)(self + 0x34));
    void* best = 0;
    f32 bestF = 3.4028235e+38f;
    void* node = w.First();
    while (node != 0) {
        if (IsObjectOfKind(node, 0x46)) {
            Node_16A820* n = (Node_16A820*)node;
            if (n->f550 == 4 && n->f554 < bestF) {
                best = node;
                bestF = n->f554;
            }
        }
        node = w.Next();
    }
    return best;
}

ASM_FUNC(func_0016A910);
