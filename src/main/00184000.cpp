// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "fpu.h"
#include "collider.h"
#include "cone_volume.h"

struct Vec2_1840B8 { f32 x; f32 y; };

void func_00183F40(f32* out0, f32* out1, f32 a, f32 b, f32 c, f32 d);

void func_001840B8(Vec2_1840B8* self, f32* out0, f32* out1)
{
    FitLineThroughPoints(out0, out1, self->x, 1.0f, self->y, 0.0f);
}

extern s32 D_002622CC;
extern s32 D_00264260;

void func_001841B0(ConeVolume* self)
{
    if (self->value == 0) {
        D_00264260 = D_002622CC;
    }
}

void func_001841D0(void* self);
void func_00184B58(void* self);

void func_00184768(ConeVolume* self, s32 flag)
{
    self->mode = flag;
    if (flag == 0) {
        self->flags = (self->flags & ~(u64)0x30000000000) | ((u64)0x8000 << 25);
    } else {
        self->flags = self->flags & ~(u64)0x30000000000;
    }
    func_001841D0(self);
    func_00184B58(self);
}

struct Quad_001847F0 { u32 w[4]; } __attribute__((aligned(16)));

void func_001847F0(ConeVolume* self, Quad_001847F0* src)
{
    *(Quad_001847F0*)self->f2E0 = *src;
    func_001841D0(self);
}

void func_00184818(ConeVolume* self, f32 v)
{
    self->f2F0 = v;
    func_001841D0(self);
}

void func_00184838(ConeVolume* self, f32 v)
{
    self->f2F4 = v;
    func_001841D0(self);
}

void func_00184858(ConeVolume* self, f32 v)
{
    self->f2f8 = v;
    func_001841D0(self);
}

void func_00184878(ConeVolume* self, f32 v)
{
    self->f2fc = v;
    func_001841D0(self);
}

void func_00184898(ConeVolume* self, f32 v)
{
    self->f300 = v;
    func_001841D0(self);
}

void func_00184968(ConeVolume* self, s32 v)
{
    if (v != self->value) {
        self->value = v;
        func_001841D0(self);
    }
}

struct __attribute__((packed)) Packed8_184990 { u64 v; };

void func_00184990(ConeVolume* self, Packed8_184990* src)
{
    *(Packed8_184990*)&self->rangeMin = *src;
    func_001841D0(self);
    func_00184B58(self);
}

void func_00184A70(void* self);

void func_001849D0(ConeVolume* self, f32 v)
{
    self->outerAngle = v;
    UpdateConeVolumeTangents(self);
    func_001841D0(self);
    func_00184B58(self);
}

void func_00184A08(ConeVolume* self, f32 v)
{
    self->innerAngle = v;
    UpdateConeVolumeTangents(self);
    func_001841D0(self);
}

void func_00184A38(ConeVolume* self, Quad16* src)

{
    self->q340 = *src;
    func_001841D0(self);
    func_00184B58(self);
}

void func_00184CD0(ConeVolume* self, f32 v)
{
    func_00184818(self, v);
    func_00184838(self, v);
}

void func_00184D10(ConeVolume* self, f32* out)
{
    *out = self->f2F0;
}

struct __attribute__((aligned(16))) Quad_00184D20 { s32 a, b, c, d; };

void func_001B4600(void* a0, void* a1);
void func_001847F0(void* self, void* a1);

void func_00184D20(void* self, void* a1)
{
    Quad_00184D20 q;
    func_001B4600(a1, &q);
    func_001847F0(self, &q);
}

void func_001B4580(void* self);

void func_00184D58(u8* self)
{
    func_001B4580(self + 736);
}

void func_00121338(void* self);

struct IndexPair_185C18 { s32 a; s32 b; };

extern s32 D_00262C64;

struct IndexPair_185CA0 { s32 a; s32 b; };


void func_001B5F28(u8* a, void* b);

struct Ent_001879C0 { u8 pad0[0x20]; f32 f; s32 b; s32 c; u8 pad1[4]; };

s32 func_00187260(void* a0, void* a1, void* a2, void* a3, void* a4, s32 a5, Ent_001879C0* a6);
s32 func_00185D20(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);

struct Rec_00187C28 { u8 pad0[0x50]; void* p; u8 pad1[0x1C]; };
struct Vec_00187C28 { f32 x; f32 y; f32 z; f32 w; };

s32 func_0013DFD8(void* a0, void* a1, void* a2, s32 a3, s32 a4, void* a5);
void func_00187B60(void* a0, void* a1, void* a2, void* a3, f32 f);
s32 func_00185D20(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, void* a6, void* a7);

struct Loc_00187E88 { s32 a[4]; s32 b[4]; f32 fa; f32 fb; s32 pad[2]; };

s32 func_00187D08(void* a0, void* a1, void* a2, s32 a3, void* a4, void* a5, void* a6, f32 f);
void func_00187B60(void* a0, void* a1, void* a2, void* a3, f32 f);
s32 func_00185D20(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);

extern s32 D_00261F14;
extern u8 D_00211E10[];
void func_001F6C20(s32 unused);
void func_00202A80(void* dma, void* addr);
s32 func_00202C38(void* dma, s32 b, s32 c);

extern u8 D_00261F18[];
extern u8 D_00212110[];

void func_001F6C20(s32 a);
void func_00202A80(void* a, void* b);
s32 func_00202C38(void* a, s32 b, s32 c);

struct Self_186450 {
    u8 pad0[0x3AC];
    u8* base;
    u8 pad1[0x3B8 - 0x3B0];
    s32 count;
    u8* table;
};

struct Entry_186450 {
    s16 x;
    s16 y;
    u8 pad0[0x10 - 4];
};

struct Out_186450 {
    u8 pad0[0x58];
    Entry_186450* link;
    u8 pad1[0x70 - 0x5C];
};

s32 func_0013DFD8(void* a, u8* b, u8* c, s32 d, s32 e, Out_186450* f);

extern s32 D_00264838;
extern s32 D_00275AF0;
extern u8 D_00262C70[];
extern u8 D_00275BC0[];
extern u8 D_00264A40[];
extern void* D_00261990;
extern s32 D_002622CC;

void func_001FAE18(void);
void func_00185B38(void);
void func_0015F210(s32 flag);
void func_0018F148(void* p);
void func_001E4EA8(void* p);
void func_0016E238(void* p);
void func_0016F2E0(void);
void func_0018BDC8(void* p);
void func_001E9108(void* p);
void func_001607D0(f32 dt);
void func_00144270(void* p);
void func_0015E9F0(void);
void func_00142F10(void* p);
void func_001E9668(void* p);
void func_001E9648(void* p);
void func_0015EC68(void);

typedef void (*Fn_185B38)(void);

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern Fn_Table D_002647C0[];

s32 func_00193210(void* a, void* b, void* c, void* d, void* e);
void func_00191E70(s32 value);
void func_00193270(void* p);
void func_00193288(void* self, s32 value);
void func_00193300(void* p);
void func_00191EB0(s32 value);

s32 func_001925F0(void);

extern const char D_0024B248[16];
extern const u8* D_002647A8[6];
void func_00140B60(void* buf, const u8* name, s32 n);
void func_001F7BE8(s32 a);
s32 func_00203548(s32 a);
s32 func_00140968();
void func_001409A8();
s32 func_001F8BF8();
s32 func_001F9C50(void* buf);
s32 func_001F9C18();
s32 func_001F9820();
s32 func_00203828(s32 a);
s32 func_00140D68(s32 a);
void func_001F9A90(void* buf, s32 a, s32 b);

f32 func_002054F0(f32 a);

struct Clamp_184A70 {
    static f32 Of(f32 v, f32 lo, f32 hi)
    {
        if (v < lo)
            return lo;
        if (hi < v)
            return hi;
        return v;
    }
};

void func_00184A70(ConeVolume* self)
{
    f32 a = Clamp_184A70::Of(self->outerAngle, 0.0f, 175.0f);
    f32 b = Clamp_184A70::Of(self->innerAngle, 0.0f, a);
    f32 r = func_002054F0(a * 0.00872664712f);
    self->f354 = r;
    self->f350 = r;
    f32 q = func_002054F0(b * 0.00872664712f);
    self->f360 = q / self->f350;
    self->f368 = q / self->f354;
    self->f36C = self->f364 = 1.0f;
    self->f358 = Fpu::Sqrt(self->f360);
    self->f35C = 1.0f;
}

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_0011E560();
void func_0012B868();
void func_00139C38();
void func_00140790();
void func_001409D8();
void func_001430C8();
void func_00143140();
void func_00152810();
void func_0015C178();
void func_0015E810();
void func_00160070();
void func_001688B8();
void func_00169C58();
void func_0016E0B8();
void func_0016F588();
void func_0017FD48();
void func_0018B580();
void func_0018D430();
void func_0018E5E8();
void func_00191EC0();
void func_0019DF48();
void func_001A9C68();
void func_001BF130();
void func_001DFD48();
void func_001E2398();
void func_001E9088();

struct Out_1840F0;
f32 func_00205210(f32 value);
void func_00183F40(f32 a, f32 b, f32 c, f32 d, Out_1840F0* out0, void* out1);

void func_001840F0(f32 a, f32 b, f32 c, f32 d, Out_1840F0* out0, void* out1)
{
    f32 x = func_00205210(a * 0.0087266471f);
    x = x + x * x * x;
    f32 y = func_00205210(c * 0.0087266471f);
    y = y + y * y * y;
    FitLineThroughPoints(x, b * 0.003921569f, y, d * 0.003921569f, out0, out1);
}

struct Pair_00186A70 { u8 pad0[4]; s16 k1; s16 k2; };
struct Grp_00186A70 { u8 pad0[0x58]; Pair_00186A70* pair; u8 pad1[4]; Grp_00186A70* next; };
struct Item_00186A70 { u8 pad0[0x1C]; u16 flags; u8 pad1[2]; };
struct Rec_00186A70 { Rec_00186A70* parent; Grp_00186A70* node; s32 id; };

struct __attribute__((aligned(16))) Row_1867C8 {
    f32 v[4];
};

struct Pair_1867C8 {
    s16 v[2];
};

struct Edge_1867C8 {
    Row_1867C8 r0;
    Row_1867C8 r1;
    Row_1867C8 r2;
    Row_1867C8 r3;
    f32 f40;
    f32 f44;
    u8 pad48[0x50 - 0x48];
    s32 i50;
    s32 i54;
    Pair_1867C8* idx58;
    s32 slot5C;
    Edge_1867C8* next;
};

void func_001F5B08(void* dst, void* src, s32 size);

extern const char D_0024B1E8[];

