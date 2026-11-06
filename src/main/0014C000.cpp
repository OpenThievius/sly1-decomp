// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "gauge_manager.h"
#include "pooled_object.h"
#include "masked_collider.h"
#include "world.h"
#include "screen_element.h"
#include "object_link.h"
#include "g261ef0.h"
#include "shapes.h"

s32 func_0014D1A0(s32 n, f32* arr, void* p2, f32* lo, f32* hi);

s32 func_00137B90(void* src);
f32 func_00137DF8(void* src);
void func_00137E70(void* src, void* dst);
void* func_0018D500(s32 size);

void func_0014D680(void* a0, void* a1, s32 a2, void* a3, s32 idx, s32 a5, f32* a6, f32* a7, s32* p9, f32* p10);

void func_001B7A98(Collider* self);
s32 func_001526D0(void* a, void* b);
void func_00152600(void* a, void* b);
s32 func_001300E8(void* a, s32 b);

ObjectLink D_00261CC8[1] = { { 2, 0x2BC, 0x574 } };
void func_00124A48(void* self);
void func_00124DF8(void* self, s32 idx, void* table);

extern u8* D_00262E10;



void func_001B6568(void* dev, s32* out);
void func_001B6598(void* dev, s32* out);
void func_001B64D8(void* dev, s32 value);

extern f32 D_00261858[];

void* func_001925F0(void);

extern f32 D_0026185C[];

f32 func_001EAAE0(f32 a, f32 b);

void func_001249A8(void* self);
void* func_0015A448(void* a, void* b, void* c);
s32 func_001300E8(void* obj, s32 kind);

s32 func_001B8A08(void* self, void* obj);

typedef void (*VFn2_0014FC38)(void* self, s32 arg);

void func_001B6628(void* h, s32 arg);
void func_001B6598(void* h, s32* out);
void func_001B6438(void* h);
void func_0013D278(void* self);

void func_001B6568(void* h, s32* out);
void func_001B64D8(void* h, s32 code);

void func_0014D280(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_0014D280(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_00188700(void* a, void* b, void* c, f32 w);

void func_001B7968(Collider* self);

void func_00188700(void* a, void* b, void* c, f32 w);

void func_0013DDB8(void* self);

s32 func_0014D1A0(s32 n, f32* arr, void* p2, f32* lo, f32* hi);

s32 func_0014D1A0(s32 n, f32* arr, void* p2, f32* lo, f32* hi);
void func_0014D680(void* a0, void* a1, s32 a2, void* a3, s32 idx, s32 a5, f32* a6, f32* a7, s32* p9, f32* p10);

s32 func_00137B90(void* src);
f32 func_00137DF8(void* src);
void func_00137E70(void* src, void* dst);
void* func_0018D500(s32 size);

void func_00182D50(void*);
void func_00152470(void*,void*);

void func_001BA130(Collider* self, Collider* other);

void func_001BAC30(Collider* self);
void func_00159478(void** out, void* self);

void func_00127378(void* self, s32 kind, void* msg);

void func_00127378(void* self, s32 kind, void* msg);
void func_001B6568(void* dev, s32* out);
void func_001B6438(void* h);

s32 func_0014D1A0(f32 x, s32 n, f32* arr, void* p2, f32* lo, f32* hi);

struct Src_14F920 { void** vtbl; u8 pad0[0x14 - 4]; void* p14; BaseObject* f18; u8 pad1[0x190 - 0x1C]; Quad16 q190[4];
 };
typedef void (*VFn_14F920)(void* self);
typedef void (*VFn_14F920Arg)(void* self, s32 x);

ObjectLink D_00261CE0[3] = { { 4, 0x2B4, 0x734 }, { 4, 0x2B5, 0x738 }, { 0, 0x2B6, 0x73C } };

void func_0013CE40(void* self);
void func_00124DF8(void* self, s32 n, void* table);
Src_14F920* func_0015A480(void* a, s32 kind, void* arg);
void* func_00183058(void* item, void* x, void* self);
void func_0014F900(C23* self);
void* func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);
void* func_001B6290(void* a, void* b, s32 c, s32 d);




extern f32 D_00275C60[];

void func_00124A48(GaugeManager* self);
void func_00124DF8(GaugeManager* self, s32 n, void* table);
void* func_001B6290(void* a, s32 b, s32 c, s32 d);
void func_001B6598(void* a, void* b);
void func_0014C2F0(GaugeManager* self);

extern f32 D_0026185C[];

f32 func_001EAAE0(f32 a, f32 b);
void func_001B6568(void* dev, s32* out);
void func_001B6598(void* dev, s32* out);
void* func_001925F0(void);
void func_001B64D8(void* dev, s32 value);
void func_0014C2F0(GaugeManager* self);

struct Sub_14F110;

extern f32 D_0026185C[];

s32 func_00126D60(Sub_14F110* sub, f32 value);

{
    }
}


{
    }
}

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_002176D0[];
extern const Fn_Table D_00217708[];

// NEAR: the calls and branches match; the store of 1 into the inner object comes before the
// float load of D_0026185C in retail, ours schedules the float load first (5 instructions).
extern u8 D_00248D30[];

s32 func_0014FEC0(C23* self);
PooledObject* func_00150338(C23* self);
s32 func_00182FC8(PooledObject* p);
void func_001853F0(Held23* a, PooledObject* b, u8* c);

// NEAR: the tail stores differ in order and register: retail does sw f6C8, then lui v1 / li v0,1 / lwc1 v1, we do lui v0 before the sw and use v0 for the address.

extern u8 D_00248D30[];

s32 func_00152720(void* p);
void func_00150298(C23* self);
void func_001B9AE0(Collider* o, s32 a, s32 b, s32 c, s32 d);

// NEAR: the search index is kept in a0 where retail uses a2, and hi is saved in s3 before the call in retail; the loop shape is otherwise the same.

void func_001B93F8(Collider* self);
void func_0014F270(PooledObject* self, f32 f);

void func_0013D068(C23* self);
void func_001B6598(void* p, s32* out);
void func_001B6568(void* p, s32* out);
void func_0014FDA8(C23* self, s32* state);
void func_00150008(C23* self);
void func_0014FCE8(C23* self, s32 state);

struct Slot_14CBA8 {
    void* p0;
    void* obj;
    void* p8;
    void* pc;
    s32 flag;
};
struct Ctl_14CBA8;
struct VT_14CBA8 {
    u8 pad[0x84];
    void (*f84)(Ctl_14CBA8* self, f32* v);
    void (*f88)(Ctl_14CBA8* self, f32* v);
    void (*f8c)(Ctl_14CBA8* self, f32* v);
    void (*f90)(Ctl_14CBA8* self, u8* v);
    void (*f94)(Ctl_14CBA8* self, u8* v);
};
struct Ctl_14CBA8 {
    VT_14CBA8* vt;
    u8 pad[0xC24];
    Slot_14CBA8* cur;
};
extern u8 D_00248D30[];

f32 func_001EAAE0(f32 a, f32 b);

struct __attribute__((aligned(16))) Vec_14DB78 { f32 v[4]; };
struct Src_14DB78;
struct VT_14DB78 {
    void* slot0;
    void (*f4)(Src_14DB78* self, Vec_14DB78* out, s32 flag);
};
struct Src_14DB78 { VT_14DB78* vt; };

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
// Defined in src/main/file_14D0A8.cpp.
f32 func_0014DB40();
f32 func_0014DB58();
void func_0014DD28();
void func_0014DE08();
void func_0014DE40();
void func_0014DE78();
void func_0014DF68();
f32 func_0014DF98();
f32 func_0014E000();
f32 func_0014E068();
void func_0014E090();
void func_0014E170();
void func_0014E2A0();
void func_0014E3D0();
void func_0014E5B8();
void func_0014E6A8();
void func_0014E710();
void func_0014E828();
f32 func_0014E910();
f32 func_0014E990();
void func_0014EA48();
void func_0014EB10();
void func_0014EC70();
void func_0014ED98();
extern const Fn_Table D_002176D0[14] = { (Fn_Table)func_0014DD28, (Fn_Table)func_0014DE08, (Fn_Table)func_0014DE40, (Fn_Table)func_0014DE78, (Fn_Table)func_0014DF68, (Fn_Table)func_0014DF98, (Fn_Table)func_0014E000, (Fn_Table)func_0014DB40, (Fn_Table)func_0014DB58, (Fn_Table)func_0014E068, (Fn_Table)func_0014E090, (Fn_Table)func_0014E170, (Fn_Table)func_0014E2A0, 0 };
extern const Fn_Table D_00217708[14] = { (Fn_Table)func_0014E3D0, (Fn_Table)func_0014E5B8, (Fn_Table)func_0014E6A8, (Fn_Table)func_0014E710, (Fn_Table)func_0014E828, (Fn_Table)func_0014E910, (Fn_Table)func_0014E990, (Fn_Table)func_0014DB40, (Fn_Table)func_0014DB58, (Fn_Table)func_0014EA48, (Fn_Table)func_0014EB10, (Fn_Table)func_0014EC70, (Fn_Table)func_0014ED98, 0 };

void func_00127378(GaugeManager* self, s32 kind, void* key);
void func_001B6598(void* key, s32* out);

extern f32 D_00275C60[];
extern f32 D_00261858[];

