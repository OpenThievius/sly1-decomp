// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "base_object.h"
#include "switched_collider.h"
#include "globals.h"

// A quadratic in t (c[0] + t * (c[1] + t * c[2])), on 16 bytes: the file's four start on a
// 16-byte line, so 0x274A48 is padding after the float before the first.
struct __attribute__((aligned(16))) Quad_1C3390 { f32 c[3]; };

// The file's .data, in retail's order.
s32 D_002749B0[36] = { 4, 1317, 1632, 4, 1320, 1580, 2, 354, 1420, 2, 355, 1424, 6, 352, 1412, 0, 1319, 1636, 0, 1321, 1560, 0, 1322, 1564, 0, 1323, 1568, 0, 1324, 1572, 0, 1325, 1652, 0, 1326, 1656 };
char D_00274A40[4] = "\r";
f32 D_00274A44 = 150.0f;
Quad_1C3390 D_00274A50 = { { 0.2f, 0.0f, 0.0f } };
f32 D_00274A60[3] = { 40.0f, 0.0f, 0.3f };
Quad_1C3390 D_00274A70 = { { 1.0f, 0.0f, -0.75f } };
Quad_1C3390 D_00274A80 = { { 0.7f, 0.3f, 0.0f } };
f32 D_00274A90[2] = { 1200.0f, 1.0f };
f32 D_00274A98 = 0.25f;
f32 D_00274A9C = 3000.0f;
f32 D_00274AA0 = 0.1f;
f32 D_00274AA8[3] = { 20.0f, 0.0f, 0.3f };
f32 D_00274AB4 = 1000.0f;
f32 D_00274AB8[2] = { 0.0f, 300.0f };
Quad_1C3390 D_00274AC0 = { { -1.0f, 1.0f, 0.0f } };

void func_001921A8(void* self);

void func_001C3390(C1D* self)
{
    InitSwitchedCollider(self);
    self->f610 = -1;
    self->f694 = 5;
}

struct __attribute__((packed)) Pk8_1C33C8 { u64 v; };
struct __attribute__((packed)) Pp_1C33C8 { void* p; };

typedef void (*VFn_1C3928)(void*);
struct Obj_1C3928 { VFn_1C3928* vtbl; };
extern Obj_1C3928 D_0026DD48;
extern Obj_1C3928 D_0026DFC8;

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void* func_001B6290(void* a, void* self, s32 b, s32 c);
f32 func_00205778(f32 a, f32 b);
void func_001DDC38(void* sub, void* self);
void func_001C3FC8(void* self, s32 flag);

void func_001C33C8(C1D* self)
{
    StartPlacedObject(self);
    self->f68C = self->radius3CC;
    ResolveObjectLinks(self, 0xC, D_002749B0);
    self->f668 = CreateStateWalker(self->f664, self, -1, 0);
    self->f644 = func_00205778(self->rot.r[0].y, self->rot.r[0].x);
    PlacedObject* v = (PlacedObject*)self->f660;
    self->f648 = func_00205778(v->rot.r[0].y, v->rot.r[0].x);
    *(Pk8_1C33C8*)&self->f630 = *(Pk8_1C33C8*)((u8*)self->f62C + 0x2DC);
    u8* g1 = (u8*)&D_0026DD48;
    ((Pp_1C33C8*)(g1 + 0x264))->p = (u8*)self + 0x690;
    u8* g2 = (u8*)&D_0026DFC8;
    ((Pp_1C33C8*)(g2 + 0x264))->p = (u8*)self + 0x694;
    *(void**)(g1 + 0x268) = D_00274A40;
    *(f32*)(g2 + 0x26C) = 4.0f;
    func_001DDC38(self->world, self);
    s32 c = self->f71C;
    self->f720[c] = self;
    self->f71C = c + 1;
    func_001C3FC8(self, 1);
}

struct Vt_1C34C8 { void* pad[7]; void (*f1C)(void*); void* pad2[0x1A]; void (*f88)(void*, void*); };
struct Obj_1C34C8_Vt { Vt_1C34C8* vt; };
struct Sub_1C34C8 { u8 pad[8]; struct Sub2_1C34C8* p8; u8 padC[8]; f32 f14; f32 f18; };
struct Sub2_1C34C8 { u8 pad[0x34]; f32 f34; };
extern f32 D_00275C60[];
extern f32 D_0026185C[];
extern f32 D_00261854;
extern f32 D_00261858[];
extern s32 D_0026E228[8];

void func_00192B58(void* self, f32 t);
void* func_0015A838(void* a, s32 b, s32 c, s32 d);
void func_00158730(void* x);
void func_001C3F68(void* self, s32 v);
void func_0012E760(void* p);
void func_0012C7B0(void* a, void* b, s32 c, void* d, f32 fa, f32 fb);
f32 func_00205778(f32 a, f32 b);
void func_00188850(void* a, void* b, f32 f);
void func_001EA918(void* a, void* b, void* c, void* d, s32 e, f32 f);
f32 func_00205210(f32 a);
void func_00126A48(void* o, u32 v);

void func_001C34C8(C1D* self, f32 t)
{
    f32 buf[12];
    f32 buf2[12];
    u32 ca[4];
    u32 cb[4];
    UpdateSwitchedCollider(self, t);
    if (((Obj_1C34C8_Vt*)self->f688)) {
        void* h = FindFirstObjectByIdGathered(self->world, 0x101, 0x77, (s32)((Obj_1C34C8_Vt*)self->f688));
        if (h) SendEmptyMessage(h);
        self->f690 = self->f690 + 1;
        ((Obj_1C34C8_Vt*)self->f688)->vt->f1C(((Obj_1C34C8_Vt*)self->f688));
        self->f688 = 0;
    }
    if (self->f684) {
        func_001C3F68(self, self->f684);
        self->f684 = 0;
    }
    if (((Sub_1C34C8*)self->f67C)) {
        if (((Sub_1C34C8*)self->f67C)->f18 == 0.0f) {
            StopAnimationPlayer(((Sub_1C34C8*)self->f67C));
            self->f67C = 0;
        }
    } else if (self->f680) {
        CreateAnimationPlayerWithoutPresetTargets(self->f678, self, 0, &self->f67C, 0.0f, 1.0f);
        self->f694 = self->f694 - 1;
        D_0026E228[0] = -1;
    }
    self->f680 = 0;
    f32 u;
    if (((Sub_1C34C8*)self->f67C)) {
        f32* lim = g_unitRange;
        f32 r = ((Sub_1C34C8*)self->f67C)->f14 / ((Sub_1C34C8*)self->f67C)->p8->f34;
        f32* pp = D_00274A50.c;
        f32 lo = lim[0];
        f32 hi = lim[1];
        f32 v = pp[0] + r * (pp[1] + r * pp[2]);
        if (v < lo) v = lo;
        else if (hi < v) v = hi;
        g_stepScale = v;
        u = r;
    } else {
        g_stepScale = 1.0f;
        u = 0.0f;
    }
    f32 w = u * D_00274A44 + (1.0f - u) * self->f68C;
    self->radius3D0 = w;
    self->radius3CC = w;
    if (self->f638) {
        if (g_gameTime[0] - self->f640 > 2.0f) self->f638 = 0;
    }
    f32 ang = func_00205778(self->rot.r[0].y, self->rot.r[0].x);
    BuildAxisAngleMatrix((u8*)&g_unitZVector, buf, self->f648 - ang);
    func_001EA918((u8*)((Obj_1C34C8_Vt*)self->f660) + 0xD0, buf, D_00274A60, buf2, 0, t);
    ((Obj_1C34C8_Vt*)self->f660)->vt->f88(((Obj_1C34C8_Vt*)self->f660), buf2);
    ca[0] = 0x8010FF00;
    cb[0] = 0x800000FF;
    if (self->f638) {
        f32 q;
        if (self->f610 != 2) q = (g_gameClock[1] - self->f614) * 0.5f;
        else q = 0.0f;
        f32 z = func_00205210((g_gameClock[1] - self->f63C) * 10.0f);
        f32 x0 = D_00274A70.c[0] + q * (D_00274A70.c[1] + q * D_00274A70.c[2]);
        f32 lo = g_unitRange[0];
        f32 hi = g_unitRange[1];
        f32 x = x0 < lo ? lo : (hi < x0 ? hi : x0);
        f32 y = D_00274A80.c[0] + z * (D_00274A80.c[1] + z * D_00274A80.c[2]);
        f32 lo2 = g_unitRange[0];
        f32 hi2 = g_unitRange[1];
        if (y < lo2) y = lo2;
        else if (hi2 < y) y = hi2;
        f32 m = x * y;
        f32 n = 1.0f - m;
        f32 r0 = n * ((u8*)ca)[0] + m * ((u8*)cb)[0];
        f32 r1 = n * ((u8*)ca)[1] + m * ((u8*)cb)[1];
        f32 r2 = n * ((u8*)ca)[2] + m * ((u8*)cb)[2];
        ((u8*)ca)[0] = (s32)r0;
        ((u8*)ca)[2] = (s32)r2;
        ((u8*)ca)[1] = (s32)r1;
    }
    SetObjectTreeRecordValue(self, ca[0]);
    *(f32*)(((u8*)self->f62C) + 0x2DC) = self->f670 * self->f630;
    *(f32*)(((u8*)self->f62C) + 0x2E0) = self->f670 * self->f634;
    *(s32*)(((u8*)self->f62C) + 0x32C) = 0;
}

bool func_001E9970();

void func_001C3928()
{
    if (AreMenusAndFadeClear()) {
        D_0026DD48.vtbl[14]((void*)&D_0026DD48);
        D_0026DFC8.vtbl[14]((void*)&D_0026DFC8);
    } else {
        D_0026DD48.vtbl[15]((void*)&D_0026DD48);
        D_0026DFC8.vtbl[15]((void*)&D_0026DFC8);
    }
}

ASM_FUNC(func_001C39A0);

ASM_FUNC(func_001C3B40);

struct Entry_1C3C00 { s32 first; u8 pad[60]; };
s32 func_001300E8(s32 a, s32 b);
s32 func_001833F0(s32 a, s32 b);

void func_001C3C00(C1D* self, Entry_1C3C00* table, s32 idx)
{
    Entry_1C3C00* e = (Entry_1C3C00*)((u8*)table + ((1 - idx) << 6));
    if (IsObjectOfKind(e->first, 0x21)) {
        if (self->f694 > 0) {
            self->f680 = 1;
            return;
        }
        if (self->f67C == 0) self->f684 = e->first;
        return;
    }
    if (MatchesObjectId(e->first, 0x52F)) self->f688 = (void*)e->first;
}

ASM_FUNC(func_001C3C98);

extern s32 D_00262C64;
s32 func_001DDA80(void* p);

s32 func_001C3D28(C1D* self)
{ if ((g_buttonCodeFlags & 1) || func_001DDA80(self->world)) return 1; return 0; }

typedef s32 (*VFnA_1C3D60)(void* self, s32 v);
typedef void (*VFnB_1C3D60)(void* self, s32 v, void* data);
typedef void (*VFnC_1C3D60)(void* a0, void* self);
struct Arg_1C3D60 {
    s32 f0;
    s32 f4;
    void* f8;
    VFnC_1C3D60 fC;
};
struct Local_1C3D60 { void* self; s32 v; };
s32 func_00160C58();
void func_001C3FC8(void* self, s32 flag);

s32 func_001C3D60(C1D* self, Arg_1C3D60* arg)
{
    Local_1C3D60 local;
    s32 m;
    if (((VFnA_1C3D60)((void**)self->desc)[79])(self, arg->f0)) return 0;
    if (arg->f0 == 0) {
        if (arg->fC != 0) arg->fC(arg->f8, self);
    }
    m = self->f610;
    if (m < 5) {
        if (!(m < 2)) return 1;
    }
    if (self->f638 != 0) return 1;
    if (func_00160C58()) {
        func_001C3FC8(self, 2);
        self->f638 = 1;
        self->f63C = g_gameTime[0];
    } else {
        func_001C3FC8(self, 3);
    }
    local.self = self;
    local.v = arg->f4;
    ((VFnB_1C3D60)((void**)self->desc)[18])(self, 0x17, &local);
    return 1;
}

s32 func_001C3E50(C1D* self) { if (self->f610 < 5) { if (self->f610 >= 2) return 1; } return self->f638 != 0; }

void func_00192C58(void* self);
void func_001C3FC8(void* self, s32 flag);

void func_001C3E80(C1D* self)
{
    func_00192C58(self);
    func_001C3FC8(self, 1);
}

ASM_FUNC(func_001C3EB0);

typedef void (*VFn_1C3F68)(void*, void*);
struct Local_1C3F68 { s32 pad[2]; s32 value; VFn_1C3F68 fn; };
void func_001D7098(void* self, s32 a, s32 b);
void func_001C3EB0(void* self, void* data);

void func_001C3F68(C1D* self, s32 value)
{
    Local_1C3F68 local;
    InitOwnerMessage(&local, 0, value);
    local.value = value;
    local.fn = func_001C3EB0;
    self->desc05()->m4C(self, (void*)&local);
}

extern f32 D_00261858[];
extern s32 D_0026E228[8];
extern u8 D_00261EF0[];
extern u8 D_0026FF68[];

f32 func_00205778(f32 a, f32 b);
f32 func_001EA408(f32 a);
f32 func_001EA728(f32 x, f32 y, f32 z, u8* a, void* out);
void func_00151E20(u8* a, f32 b);
void func_00194D30(u8* a, s32 b, s32 c);
void func_0012C918(void* a, PlacedObject* b, s32 c, void* d, f32 e, f32 f);

#define F(o, off) (*(f32*)((u8*)(o) + (off)))
#define W(o, off) (*(s32*)((u8*)(o) + (off)))
#define P(o, off) (*(void**)((u8*)(o) + (off)))

void func_001C3FC8(PlacedObject* self, s32 state)
{
    void* s2;
    f32 f12;
    if (state == W(self, 0x610)) return;
    if (W(self, 0x610) == 2) {
        f32 t = g_gameClock[1];
        W(self, 0x694) = 3;
        F(self, 0x640) = t;
    }
    W(self, 0x670) = 0;
    if (state < 4) if (state >= 2) {
        Vec02 q;
        f32 a = func_00205778(F(self, 0x154), F(self, 0x150));
        f32 b = WrapAngle(a + 3.14159274f);
        F(self, 0x644) = b;
        F(self, 0x648) = b;
        q = D_00248D30;
        f32 r = func_00205778(F(self, 0xD4), F(self, 0xD0));
        ApproachAngleWithRamp(r, F(self, 0x644), 0.0f, (u8*)D_00274AA8, (u8*)&q + 8);
        self->desc02()->m21(self, (Vec02*)&q);
        W(self, 0x694) = 0;
        D_0026E228[0] = -1;
        if (state == 3) RaiseScatterLevels(g_scatterController, 1.0f);
    }
    f12 = 0.0f;
    switch (state) {
    case 0: s2 = P(self, 0x618); break;
    case 1: s2 = P(self, 0x61C); break;
    case 2: s2 = P(self, 0x620); F(self, 0x640) = 3.4028235e+38f; break;
    case 3: s2 = P(self, 0x624); break;
    case 4:
        SetPauseMenuLayerPage(g_pauseMenuElement, 0, 0x1A);
        s2 = P(self, 0x624);
        f12 = F(s2, 0x34);
        break;
    }
    ReplaceAnimationPlayer(s2, self, 1, (u8*)self + 0x628, f12, 1.0f);
    W(self, 0x610) = state;
    F(self, 0x614) = g_gameClock[1];
}

void func_001C4180(C1D* self, s32 value)
{
    s32 n = self->f698;
    self->f69C[n] = value;
    self->f698 = n + 1;
}

// The constant only the assembly function after it loads, in the file's .rodata after the
// jump table of func_001C3FC8.
extern const f32 D_0024D584 = 3.40282347e+38f;

ASM_FUNC(func_001C41A0);
