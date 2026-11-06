// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "c6e.h"
#include "cursor_animator.h"
#include "world.h"
#include "v24a0.h"
#include "v24a2.h"
#include "list_iter.h"
#include "shapes.h"
#include "globals.h"
#include "range_record.h"
#include "texture_table.h"
#include "bump_allocator.h"

typedef void (*VFn_1B0F70)(void* self, s32 arg);

void func_001B1BF0(RangeRecord* o);

struct Obj_1B2118 {
    u8 pad_0[0x410];
    u32 f410;
    u8 pad_414[0x538 - 0x414];
    u64 f538;
};


extern u32 D_00275718;
void func_00137A60(void* a, s32 b, void* c);

struct Bits_1B29E0 {
    u64 bits;
};

u64 func_001B2988(TextureTable* obj, s32 p1, s32 p2);
void func_00161708(void* ctx, s32 kind, u64 value);
void func_001F5C0C(void* p, s32 v, s32 n);

extern s32 D_00274508;
extern s32 D_00274514;

u16 func_00137BE0(void* self);
void* func_0018D5C0(s32 bytes);

void func_00137A60(void* self, s32 size, void* obj);

extern s32 D_00274500;
extern s32 D_00274510;

u16 func_00137BE0(void* self);
void* func_0018D5C0(s32 bytes);

extern s32 D_00274518;

void func_00168D68(void* dst, s32 size, s32 align);
void func_001692B0(s32 a, void* b);

void func_00124A48(void* self);

typedef void (*VFn_1B11A0)(void* self, s32 arg);

typedef void (*VFn_1B15D0)(void* self, s32 arg);

extern f32 D_0026185C;

typedef void (*VFn_1B1608)(void* self, s32 arg);

extern s32 D_002626D0;
extern u8 D_0027DC20[];

void func_001B1CF8(RangeRecord* self, s32 code);
s32 func_001B1D38(RangeRecord* self);
void func_001B1D70(RangeRecord* self, f32 v);
void func_001B1DA8(RangeRecord* self, f32 v);
void func_001F5C0C(void* p, s32 v, s32 n);

struct Hdr_1B1B38 {
    u8 pad0[0xC];
    s32 f0C;
};

void* func_001B4688(s32 key);

typedef void (*VFn_1B00E8)(void* self, s32 arg);

void func_001AECB0(void* self);

struct Entry_1B2988 { u8 pad[0x18]; u64 tail; };
struct Cell_1B2988 { u8 pad[0x10]; u64 value; };

typedef void (*VFn_1B0160)(void* self, s32 arg);

void func_001B1BF8(RangeRecord* o);

typedef void (*VFn_1B0EA8)(void* self, s32 arg);

s32 func_00137B90(void* src);
T2176* func_0014D9A8(s32 kind);
void func_0011EC40(void* self, void* obj);

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);

typedef void (*VFn_1B04D0)(void* self, s32 v);

typedef void (*VFn_1B0EE0)(void* self, s32 arg);

extern f32 D_0026185C;

struct Sub_1B2640 {
    u8 pad0[0xC];
    s32 f0C;
};

struct Obj_1B2640 {
    Sub_1B2640* f0;
    u8 pad4[0xBC];
    s32 fC0;
    u8 padC4[0xC];
};


void func_001B2358(void* o);

struct Node_1B2790;
struct Node_1B2790 { u8 pad[0xB8]; Node_1B2790* next; };

s32 func_001B26F8(Node_1B2790* node, void* a1, f32 f);

typedef void (*VFn_1B0120)(void* self, s32 arg);

struct Obj_1B2090 {
    u8 kind_0;
    u8 pad_1[0xB];
    u32 flags_C;
};

struct Obj_1B2F00 {
    u8 pad0[4];
    u8 countA;
    u8 countB;
    u8 pad6[6];
    u32* ptrC;
    u32* ptr10;
};

void func_00137A60(void* self, s32 size, void* obj);
u32* func_0018D500(s32 bytes);

s32 func_001925F0(void);
s32 func_001AEE50(void* self, void* other);

// Matched by a switch on f558 (cases 1 and 5).

typedef void (*VFn_1B1698)(void* self, s32 arg);

f32 func_002054F0(RangeRecord* o, f32 s);

struct Obj_1B3488;

extern s32 D_00274518;
extern s32 D_002626CC;

void func_001B47C0(void);
void func_00168D78(Obj_1B3488* p);
void func_001692B0(Obj_1B3488* self, u8* arg);
void func_001B3510(Obj_1B3488* self);
void func_00169718(void);
void func_0013B430(Obj_1B3488* mask);

extern u8 D_00248400[];

void func_00188B08(void* a, void* b, Mat4A* dst);
void func_00182F78(BaseObject* self, void* other);

extern s32 D_002744D0;
void func_001BF788(s32 a, s32 n);
void func_00155F90(s32 p);

struct Tgt_1B1710;
void func_001BF788(Tgt_1B1710* t, s32 n);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

extern f32 D_0026185C;

extern f32 D_0026185C;

// NEAR: float regs: case 0 wants t=$f4 zero=$f2 m=$f3; ours t=$f3 zero=$f4 m=$f2 (8 lines differ); delay-slot load of m fixed via local m

extern f32 D_0026185C;

// EXACT (us)

struct Ent_1B3040 {
    s32 type;
    s32 data;
};
struct Elem_1B3040 {
    u8 pad0[4];
    u8 f4;
    u8 pad5[3];
    AnimRecord* f8;
    u8 pad0C[8];
};
extern s32 D_002744F8;
extern AnimRecord* D_002744FC;
extern s32 D_0027453C;
extern CursorAnimator** D_00274540;
extern s32 D_00274520[];
extern s32 D_00274538;

void func_001B2BA8(void* self);
void func_001B2CF8(void* self);
void* func_0018D5C0(s32 bytes);
void func_00137A60(void* self, s32 key, AnimRecord* out);
CursorAnimator* func_001B4A10(void* self);
void func_001B2F00(void* self, Elem_1B3040* e);
void func_001B2DF8(void* self);
void func_00168D68(BumpAllocator* p, s32 a, s32 b);
s32 func_001690C0(s32 mask, BumpAllocator* arg, s32 f);
void func_001B3510(s32 mask);
void func_0015E5F0(void);
void func_001A9F78(void);
s32 func_00169780(s32 mask);
s32 func_001693A8(s32 mask);

struct Ent_1B3510 {
    s32 type;
    Quad4* data;
};
struct Elem_1B3510;
struct Rec_1B3510 {
    u8 kind;
    u8 f1;
    u8 pad2[6];
    u8 col[4];
    u32 mask;
    s16 f10;
    u8 pad12[2];
    Elem_1B3510* f14;
    s32 f18;
    Ent_1B3510* f1C;
    s32 f20;
    void* f24;
};
struct Glob_1B3510 {
    u8 pad0[0x204];
    u32 f204;
};

#define TEST_1B3510(ate, atst, aref, afail, date, datm, zte, ztst) \
    ((u64)(ate) | ((u64)(atst) << 1) | ((u64)(aref) << 4) | ((u64)(afail) << 12) | ((u64)(date) << 14) | \
     ((u64)(datm) << 15) | ((u64)(zte) << 16) | ((u64)(ztst) << 17))
#define ALPHA_1B3510(a, b, c, d, fix) \
    ((u64)(a) | ((u64)(b) << 2) | ((u64)(c) << 4) | ((u64)(d) << 6) | ((u64)(fix) << 32))

extern s32 D_002744F8;

void* func_001611B8(V24A0* b);
void func_001529C8(V24A0* b, s32 n, Quad4* q);
void func_001612F8(V24A0* b, s32 a, s32 c, s32 d, s32 e, s32 f);
void func_001613C0(V24A0* b, s32 a, s32 c, u64 d);
void func_00161708(V24A0* b, s32 reg, u64 v);
void func_001B29E0(Elem_1B3510* e, s32 j, s32 pass, s32 kind, V24A0* b);
void func_00152D70(V24A0* b);
void func_001528C8(V24A0* b);
void func_00161278(V24A0* b, s32 n);
void func_00161520(V24A0* b, f32 x, f32 y, f32 z);
void func_00161458(V24A0* b, u32 c);
void* func_001B4688(s32 key);

struct Ctx_1B2DF8;

extern u8 D_0024A220[];
void* func_001FD8A8(s32 size);

struct Ent_1B2DF8 {
    u8 pad00[0x4C];
    void* p4c;
    u8 pad50[0x30];
    s32 v80;
    u8 pad84[0x04];

    Ent_1B2DF8() { p4c = D_0024A220; }
    void* operator new[](__SIZE_TYPE__ size) { return func_001FD8A8(size); }
};

extern s32 D_00262260;
extern Ent_1B2DF8* D_00262264;
extern s32 D_0026227C;

s32 func_00137BE0(Ctx_1B2DF8* src);
void func_0015D8A8(Ent_1B2DF8* e, Ctx_1B2DF8* self);
s32 func_0015C1C0(s32 n);

extern f32 D_0026185C;
void func_001B46E0(s32 a, s32 frame);

struct Snd_1B1070;
enum Kind_1B1070 { KIND_1B1070_1B = 0x1B };

void func_001BF788(Snd_1B1070* p, s32 n);
void func_001BFCD8(Kind_1B1070 a0, Snd_1B1070** a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

