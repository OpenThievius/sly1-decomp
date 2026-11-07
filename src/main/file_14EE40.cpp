// SPDX-License-Identifier: AGPL-3.0-or-later
// 0x14EE40 to 0x1549C8: the methods of classes 0x46, 0x23, 0x65 and 0x61, the threshold
// tables of G261EF0, the display-list writer (V24A0, with its base vtable D_0024A0E0) and the
// active-set solver (func_00153528 to func_00154880). One file between two edges: its .rodata,
// 0x249FE0 to 0x24A114, is followed by 12 bytes of padding before the next file's.
#include "common.h"
#include "gauge_manager.h"
#include "asm_func.h"
#include "pooled_object.h"
#include "masked_collider.h"
#include "world.h"
#include "screen_element.h"
#include "object_link.h"
#include "g261ef0.h"
#include "shapes.h"
#include "list_iter.h"
#include "c61.h"
#include "step_sequence.h"
#include "animation.h"
#include "attachment.h"
#include "camera.h"
#include "flagged_object.h"
#include "v24a0.h"
#include "globals.h"
#include "game_progress.h"
#include "threshold_range.h"
#include "pad_record.h"
#include "active_set_solver.h"
#include "buffered_stream.h"
#include "texture_header.h"
#include "range_record.h"
#include "effect_spawner.h"
#include "effect_owner.h"
#include "effect.h"


s32 func_0014D1A0(s32 n, f32* arr, void* p2, f32* lo, f32* hi);

typedef void (*Fn_14DD28)(void* self);

s32 func_00137B90(void* src);
f32 func_00137DF8(void* src);
void func_00137E70(void* src, void* dst);
void* func_0018D500(s32 size);

s32 func_0014DA38(void* self, f32* a, f32* b);

void func_0014D680(void* a0, void* a1, s32 a2, void* a3, s32 idx, s32 a5, f32* a6, f32* a7, s32* p9, f32* p10);

void func_00130C20(void* p0, void* p1, void* p2, void* p3, f32 x, f32 y);

void func_001B7A98(Collider* self);
s32 func_001526D0(void* a, void* b);
void func_00152600(void* a, void* b);
s32 func_001300E8(void* a, s32 b);
extern ObjectLink D_00261CC8[1];
void func_00124A48(void* self);
void func_00124DF8(void* self, s32 idx, void* table);


extern GaugeManager* D_0027C00C;

void func_001B6568(void* dev, s32* out);
void func_001B6598(void* dev, s32* out);
void func_001B64D8(void* dev, s32 value);
void func_0014C5E8(GaugeManager* self);

extern f32 D_00261858[];

void func_00124FC0(void* self);
void func_0014C858(void* self);
void func_0014CBA8(void* self);

typedef void (*VFn_14C6E0)(void* self);
struct Obj_14C6E0 { VFn_14C6E0* vtbl; };


void* func_001E9970(void* zero);

extern f32 D_0026185C[];

f32 func_001EAAE0(f32 a, f32 b);

struct Mgr_14CD70 {
    u8 pad_00[0x43C];
    f32 f43C;
    f32 f440;
    u8 pad_444[0x450 - 0x444];
    s32 f450;
    u8 pad_454[0x458 - 0x454];
    s32 f458;
    f32 f45C;
};

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
void func_001DD3E0(void* a, void* b, void* c, s32 d, s32 e);

void func_00130B48(void* a, void* b, void* c, void* d, f32 x, f32 y, f32 z, s32 n, void* buf);
f32 func_0014D0A8(s32 n, void* buf, void* other);

typedef f32 (*Fn_14E6A8)(void* self);
typedef void (*Fn2_14E6A8)(void* self, f32 t, s32 a1, void* a2);

void func_001B7968(Collider* self);

void func_00188700(void* a, void* b, void* c, f32 w);

void func_0014D3A8(void* a0, void* a1, s32 count, void* a3, void* a4, void* a5, s32* outIdx, f32* outT);

void func_0013DDB8(void* self);

s32 func_0014D1A0(s32 n, f32* arr, void* p2, f32* lo, f32* hi);

s32 func_0014D1A0(s32 n, f32* arr, void* p2, f32* lo, f32* hi);
void func_0014D680(void* a0, void* a1, s32 a2, void* a3, s32 idx, s32 a5, f32* a6, f32* a7, s32* p9, f32* p10);

typedef void (*Fn_14E3D0)(void* self);

s32 func_00137B90(void* src);
f32 func_00137DF8(void* src);
void func_00137E70(void* src, void* dst);
void* func_0018D500(s32 size);
void func_0014E500(void* self);

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
extern ObjectLink D_00261CE0[3];

void func_0013CE40(void* self);
void func_00124DF8(void* self, s32 n, void* table);
Src_14F920* func_0015A480(void* a, s32 kind, void* arg);
void* func_00183058(void* item, void* x, void* self);
void func_0014F900(C23* self);
void* func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);
void* func_001B6290(void* a, void* b, s32 c, s32 d);

struct Step_14C138 {
    u8 pad0[0xC];
    f32 dt;
};

struct Node_14C138 {
    u8 pad[0x14];
    void* f14;
};

extern ObjectLink D_00261CA0[3];

void func_00124A48(GaugeManager* self);
void func_00124DF8(GaugeManager* self, s32 n, void* table);
void* func_001B6290(void* a, s32 b, s32 c, s32 d);
void func_001B6598(void* a, void* b);
void func_001B6DF8(void* a, void* b);
void func_0014C2F0(GaugeManager* self);

extern f32 D_0026185C[];

struct Arg_14CDC8 {
    u8 pad_00[0xC24];
    s32 fC24;
};

typedef s32 (*VFnI_14CDC8)(void* self);
struct Obj_14CDC8 { VFnI_14CDC8* vtbl; };

f32 func_001EAAE0(f32 a, f32 b);
void func_001B6568(void* dev, s32* out);
void func_001B6598(void* dev, s32* out);
void func_001B64D8(void* dev, s32 value);
s32 func_0015A4F0(void* obj, s32 a1, s32 a2, s32 a3, s32 a4, s32* out);
void func_001C8F20(s32 value, s32 a1, s32 a2);
void func_001AB958(void* obj);
void func_0014C2F0(GaugeManager* self);

typedef f32 (*Slot6_14ED98)(void* self);
typedef void (*Slot11_14ED98)(void* self, s32 p1, f32 x, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6);

struct Sub_14F110;

extern f32 D_0026185C[];

s32 func_00126D60(Sub_14F110* sub, f32 value);

void func_00151E20(void* self, f32 amount);

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_002176D0[];
extern const Fn_Table D_00217708[];

void* func_0018D5C0(u32 n);

// NEAR: the calls and branches match; the store of 1 into the inner object comes before the
// float load of D_0026185C in retail, ours schedules the float load first (5 instructions).

s32 func_0014FEC0(C23* self);
PooledObject* func_00150338(C23* self);
s32 func_00182FC8(PooledObject* p);
void func_001853F0(Held23* a, PooledObject* b, u8* c);

// NEAR: the tail stores differ in order and register: retail does sw f6C8, then lui v1 / li v0,1 / lwc1 v1, we do lui v0 before the sw and use v0 for the address.


s32 func_00152720(void* p);
void func_00150298(C23* self);
void func_001B9AE0(Collider* o, s32 a, s32 b, s32 c, s32 d);

// NEAR: the search index is kept in a0 where retail uses a2, and hi is saved in s3 before the call in retail; the loop shape is otherwise the same.

struct Tab_14D1A0;

f32 func_0014D138(Tab_14D1A0* count, f32* table, void* wrap, f32 x);

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
struct Holder_14CBA8 {
    u8 pad0[0x48];
    Ctl_14CBA8* ctl;
};
extern const f32 D_00249FB8;

void func_001A8AF8(Holder_14CBA8* p);
s32 func_001EAA70(s32 a, s32 b);
s32 func_001A8C90(Holder_14CBA8* h, s32 v);
s32 func_001F3BD8(void* p, f32* out);
s32 func_001F3C08(void* p, f32* out);
s32 func_0012C7B0(void* a, void* b, s32 c, void* out, f32 fa, f32 fb);
void func_0012F810(void* a, GaugeManager* self);
f32 func_001EAAE0(f32 a, f32 b);

struct Obj_14DBD0 { void** vt; s32 f4; s32 f8; s32 fC; f32* f10; };

void func_0014DB70(void);
struct Step_14DBD0;

struct Obj_14EC70 { void** vt; s32 f4; s32 f8; s32 fC; f32* f10; };

void func_0014DA98(void);
struct Step_14EC70;

extern const GaugeParams D_00249F00;
extern const f32 D_00249FB0;

void func_00123ED0(GaugeManager* self);

struct __attribute__((aligned(16))) Vec_14DB78 { f32 v[4]; };
struct Src_14DB78;
struct VT_14DB78 {
    void* slot0;
    void (*f4)(Src_14DB78* self, Vec_14DB78* out, s32 flag);
};
struct Src_14DB78 { VT_14DB78* vt; };

void func_00186320(Vec_14DB78* p, Vec_14DB78* a, Vec_14DB78* b, f32* o1, f32* o2);

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
// Defined in src/main/path_curve.cpp.
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
extern const Fn_Table D_002176D0[14];
extern const Fn_Table D_00217708[14];

typedef void (*Cb_14CF30)(void* self);

void func_00127378(GaugeManager* self, s32 kind, void* key);
void func_001B6598(void* key, s32* out);
void func_001DDC38(void* sub, GaugeManager* self);
void func_001AB890(T217D_510* self, f32 v);
void func_001AB928(T217D_510* self, f32 v, Cb_14CF30 cb);
void func_001AB938(T217D_510* self);
void func_0014C668(void* self);

struct Clq_14C2F0 {
    f32 a;
    f32 b;
    f32 c;
};

struct Util_14C2F0 {
    static f32 Eval(Clq_14C2F0* q, f32 t) { return q->a + t * (q->b + t * q->c); }
    static f32 Limit(f32 g, f32 lo, f32 hi)
    {
        if (g < lo) return lo;
        if (hi < g) return hi;
        return g;
    }
    static f32 Lerp(f32 s, f32 a, f32 b) { return (1.0f - s) * a + s * b; }
};

struct Params_14C2F0 {
    f32 f00;
    f32 f04;
    u8 pad08[8];
    Clq_14C2F0 q10;
    u8 pad1C[4];
    f32 f20;
    f32 f24;
    f32 f28;
    f32 f2C;
    Clq_14C2F0 q30;
    u8 pad3C[4];
    f32 f40;
    f32 f44;
    f32 f48;
    f32 f4C;
    f32 f50;
    u8 pad54[0xC];
    Clq_14C2F0 q60;
    u8 pad6C[4];
    f32 f70;
    f32 f74;
    u8 pad78[8];
    Clq_14C2F0 q80;
    u8 pad8C[4];
    f32 f90;
    f32 f94;
    u8 pad98[8];
    Clq_14C2F0 qA0;
};

extern f32 D_00261858[];
extern const GaugeParams D_00249F00;


PooledObject* func_0016A820(PooledObject*);

extern s32 func_00182FC8(void*);

s32 func_001300E8(void* event, s32 kind);

extern void func_00123ED0();

void func_001289C0(void* self, void* arg);
void func_00150570(void* self, void* arg, void* a, void* b);

void func_00124A48(void* self);
void* func_00160CA0(void* base, s32 index);

extern void func_00127378(void*, u32, u32);

extern u8 D_00275BC0[];
void func_001E9498(void* a, void* b);

typedef void (*Callback_151860)(void* self, void* value);
struct VTable_151860 {
    u8 pad[0x158];
    Callback_151860 callback;
};
struct Object_151860 {
    VTable_151860* vtable;
};

void func_00150790(StepSequence* self, s32 arg);

extern void* func_00160810(const char*);
extern void* func_00160CA0(void*, u32);

extern void func_001F5C0C(void*, u32, u32);

f32 func_001EB0F8(void*, f32);
void func_00152410(G261EF0* object, f32 unused);
f32 func_001EB0F8(void*, f32);

extern f32 func_001EB0F8(void*, f32);

struct Pair_00152450 { u32 first, second; };

void func_001524D8(List01*, u32);

extern u32 func_002027C8(u32);
extern void func_002018E8();
extern u32 func_002027A0(u32);
extern u32 D_00261F14, D_00261F18, D_00261F1C, D_00261F20, D_00261F24;

u8* func_0018D4B0(s32 size);

extern u8* func_0018D500(u32);
struct Buffer_00152938 { u8* end; u8* current; u8 pad[4]; u8* allocated; };

extern u8* func_0018D658(u32);

void func_00152D70(V24A0* self);

void func_00152D70(void* self);
u32 func_0018D568(u32 size, u32 src);

void func_001F6C20(s32 unused);
void func_00202A80(void* dma, void* addr);

void func_0018D780(void* cursor, s32 count, s32 index);

void func_00152D70(void* self);

void func_00150DC0(StepSequence* self, u8* item);
s32 func_00151300(StepSequence* self);
void func_0012E760(void* obj);
void func_001516C0(StepSequence* self);

struct Frame_153328 {
    void* fn;
    s32 f04;
    s32 f08;
    u8 pad0[4];
    u8 out[0x50];
    void* self;
    u8 pad1[0x1C];
};

struct Self_1533A8;
void func_001533A8(Self_1533A8* self);
s32 func_001F5C0C(void* p, s32 zero, s32 size);
void func_00125B70(void* obj, void* c, void* out);
void func_0019D410(void* p);

struct Part_151ED8 { u8 pad0[0x14]; f32 f14; f32 f18; };

struct Link_00152600 { s32 f0; s32 f4; };
void* func_00152460(void* a, void* b);

s32 func_001F5C0C(void* p, s32 zero, s32 size);
void func_00152438(List01* self, s32 offset);

struct Gl_0026E9F8 { u8 pad0[0x260]; s32 f260; u8 pad1[0x8]; s32 f26C; };

extern s32 D_00275F84;
s32 func_001BE5E8(void);
void func_00150790(StepSequence* self, s32 mode);

u32 func_00152460(List01* node, u32 value);
void func_00152440(List01* node);

struct Obj_151D28 { u8 pad0[0x2C]; f32 f2C; s32 f30; f32 f34; s32 f38; };
struct Self_151D28 { u8 pad0[0x1C]; Obj_151D28* field_1C; s32 field_20; };

extern s32 D_00275B00;
void func_00160C48(s32 value);
f32 func_001EB0F8(void*, f32);
void func_00152410(void*, f32);
void func_00148CE0(void*);

struct VEnt_0024A0E0 { s32 delta; void (*fn)(); };
void func_00152E18();
void func_001528C8(V24A0* p);

struct __attribute__((packed)) Blk_150790 { u8 pad0[0x324]; s32 f324; };
struct Glob_150790 { u8 pad0[0x260]; StepSequence* f260; };

extern s32 D_00261D38;
extern f32 D_0026185C[];

void func_001BE998(void);
void func_001837E0(StepSequence* self, s32 a, s32 b, s32 c);
void func_001451F0(Camera* m, s32 a, s32 b, void* c, s32 d, s32 e);
void func_001DDA50(void* a);
void func_001DDA20(void* a);
s32 func_00149610(void* a);
void func_001495E8(void* a, s32 b);
void func_00145088(Camera* m, s32 a, void* b, s32 c, s32 d);
void func_0012E760(void* a);
void func_001C06A0(s32 a, s32 b, f32 f);
void func_001356C0(T217D_440* a, s32 b);
void func_001365A0(T217D_440* a, s32 b);
void* func_0015A448(void* a, s32 b, s32 c);
void func_001E86E0(T217D_3F0* a, s32 b);
void func_001E87F0(T217D_3F0* a, s32 b);

struct Node_153EC0 {
    u8 pad_00[0x28];
    s32 f28;
    u8 pad_2C[0x38 - 0x2C];
    f32 f38;
    u8 pad_3C[0x44 - 0x3C];
    s32 f44;
    u8 pad_48[4];
    Node_153EC0* next;
};
struct Frame_153EC0 {
    s32 list;
    s32 cursor;
    s32 link;
    s32 prev;
};

void func_00153780(ActiveSetSolver* self, s32 a1, Node_153EC0* n, s32 a3, s32 a4, s32 a5, s32 a6);
void func_00152600(void* list, Node_153EC0* n);
void func_00152470(void* list, Node_153EC0* n);
extern f32 D_BC23D70A;

struct Elem_153608 { u8 pad0[0x34]; f32 f34; f32 f38; u8 pad1[0x4C - 0x3C]; u8 f4C[8]; };
struct Self_153608 { u8 pad0[4]; s32 count; u8* items; u8 f0C[0xC]; u8 f18[0xC]; u8 f24[0xC]; u8 f30[0xC]; s32 f3C; };

void func_00152440(void* p);
void func_00152470(void* list, void* item);

struct Ent_150570 {
    s32 type;
    s32 w4;
    s32 w8;
    s32 wC;
    s32 w10;
    s32 w14[1];
    s32 w18;
    s32 w1C;
    s32 w20;
    s32 w24;
};

s32 func_00137CC0(BufferedStream* r);
void* func_0018D5C0(s32 n);
void func_00138550(BufferedStream* r, void* out);
s32 func_00137D10(BufferedStream* r);
f32 func_00137DF8(BufferedStream* r);
s32 func_00137B90(BufferedStream* r);
void func_001384A0(BufferedStream* r, void* out);

struct Item_1516C0 { s32 kind; s32 data[9]; };
extern u8 D_00275BC0[];
void func_001837E0(StepSequence* self, s32 a, s32 b, s32* c);
void func_001DDB58(void* a);
void func_001DDBB8(void* a);
void func_001E9570(void* p);

struct Gl_150AE8 { u8 pad0[0x260]; s32 f260; u8 pad1[8]; s32 f26C; };
extern s32 D_00275F84;
extern s32 D_00270B30;
extern s32 D_002717A8;
extern u8 D_00275BC0[];

void func_00124FC0(StepSequence* self);
s32 func_001BE5E8(void);
void func_00150790(StepSequence* self, s32 mode);
void func_001F5C0C(s32* p, s32 v, s32 n);
Ent65* func_001925F0(void);
s32 func_001493A0(T2173* p);
void func_001518B8(StepSequence* self);
void func_00151860(StepSequence* value, Ent65* object);
void func_001516C0(StepSequence* self);
void func_001E9570(void* p);
void func_001517C0(StepSequence* self);

struct Ent_151300 { s32 f0; u8 pad[0x24]; };
struct Hld_151300 { u8 pad[0x268]; s32 f268; u8 pad2[4]; s32 f270; };
struct Mgr_151300 { u8 pad[0x478]; f32 f478; };
struct Ctx_151300 { u8 pad[0x2220]; s32 f2220; u8 pad2[4]; s32 f2228; };

extern s32 D_00262C68;
extern u16 D_00261D08[16];
extern u8 D_00261D28[16];

s32 func_001BE810(void);
s32 func_001BE980(void);
s32 func_00136530(T217D_440* p);

struct Node_153A50 {
    u8 pad0[0x28];
    s32 kind;
    s32 flag;
    f32 hi;
    f32 lo;
    f32 val;
    f32 rate;
    u8 pad1[4];
    f32* vec;
    u8 pad2[4];
    Node_153A50* next;
    u8 pad3[0x10];
};


void func_00152600(List01* list, Node_153A50* n);
void func_00152470(List01* list, Node_153A50* n);
void func_0014B0C0(s32 n, f32* mat, f32* vec);
void func_0014B3E0(s32 n, f32* a, f32* b, f32* c);

struct Raw4_150DC0 { u8 b[4]; };
struct Slot_150DC0 { u8 pad0[0x2D0]; Raw4_150DC0 f2D0; u8 pad1[0x334 - 0x2D4]; s32 f334; };
union W_150DC0 { s32 i; f32 f; };

struct Msg_150DC0 {
    u32 type;
    W_150DC0 f4, f8;
    s32 fC, f10;
    s8* f14;
    s32 f18, f1C, f20, f24;
};

extern u8 D_00269A00[];

void func_001BE728(s32 a);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_001B64D8(s32 a, s32 b);
void func_001E86E0(T217D_3F0* a, Slot_150DC0* b);
void func_001E87F0(T217D_3F0* a, Slot_150DC0* b);
s32 func_001833F0(Slot_150DC0* a, s32 b);
void func_001E7440(T217D_3F0* a, s32 b);
s32 func_0012C7B0(f32 e, f32 f, Slot_150DC0* a, s32 b, s32 c, AnimationPlayer** d);
void func_0012F810(AnimationPlayer* a, StepSequence* b);
u32 func_001E2100(s8* a);
void func_001365A8(T217D_440* a, f32 b);
void func_001365A0(T217D_440* a, s32 b);
void* func_0015A448(void* a, s32 b, s32 c);
void func_001837E0(StepSequence* a, s32 b, s32 c, void* d);
void func_001DDB58(void* a);
void func_001DDBB8(void* a);
void func_0018F0E8(u8* a, s32 b);

struct Range_152010 { f32 threshold; s32 lo; s32 hi; };
struct Table_152010 {
    u8 pad0[0x1C]; s32 f1C; s32 f20; s32 f24; s32 f28;
    u8 pad2C[0x44 - 0x2C]; f32 f44; f32 f48;
    u8 pad4C[0x54 - 0x4C]; s32 count; Range_152010* ranges;
};

s32 func_001EAA70(s32 lo, s32 hi);
f32 func_001EB0F8(void* p, f32 v);
s32 func_00148AC0(World* mgr, s32 kind, void* p, s32 n, void* arr);

struct Lerp_152010
{
    static s32 Get(s32 lo, s32 hi)
    {
        f32 s = g_currentEntry->dt;
        if (lo == hi) return hi;
        if (lo < hi) return lo + (s32)(s * ((f32)hi + 0.999f - (f32)lo));
        return hi + (s32)((1.0f - s) * ((f32)lo + 0.999f - (f32)hi));
    }
};

struct Vec_152E48 { f32 x, y, z, w; };
struct C_152E48 { u8 pad[0xC]; TextureHeader** tex; };
struct B_152E48 { u8 pad[0x14]; C_152E48* c; };
struct Self_152E48 {
    u8 pad[0x2D0];
    RangeRecord* f2D0;
    s32 f2D4;
    s32 f2D8;
    s32 f2DC;
    s32 f2E0;
};

void* func_001611B8(V24A0* p);
void* func_001EE318(V24A0* p);
void func_0018D608(void);
void func_00152980(V24A0* p, s32 size);
void func_001EE480(V24A0* p);
void func_00169B18(TextureHeader* t, V24A0* p);
void func_001613C0(V24A0* p, s32 a, s32 b, u64 c);
void func_00161458(V24A0* p, s32 a);
void func_00161588(V24A0* p, s32 a, s32 b, u64 c);
void func_00161708(V24A0* p, s32 a, u64 v);
void func_00161200(V24A0* p);
void func_001EE8D0(V24A0* p, V24A0* q);
void func_001EE3B8(V24A0* p, s32 a, s32 b);
void func_001EE668(V24A0* p, s32 size, s32 count, void* data, s32 flags);
void func_001528C8(V24A0* p);
void func_001529C8(V24A0* p, s32 n, Quad4* q);
void func_001612F8(V24A0* p, s32 a, s32 b, s32 c, u64 d, s32 e);
void func_00152A50(V24A0* p, s32* a, s32 b, s32* c, s32 d);
void func_0018D6F0(void);
void func_001614C8(V24A0* p, s32 a, s32 b);
void func_001EE450(V24A0* p);

struct Sub_1533A8 {
    u8 pad0[0x238];
    s32 f238;
    void* f23C;
    u8 pad1[0x2D0 - 0x240];
    void* f2D0;
    s32 f2D4;
    s32 f2D8;
    s32 f2DC;
    s32 f2E0;
};

struct Block_1533A8 { Quad16 q[5]; };

struct Self_1533A8 {
    u8 pad0[0x10];
    Block_1533A8 copy;
    Sub_1533A8* f60;
};

struct Frame_1533A8 {
    void* fn;
    u8 pad0[4];
    s32 f08;
    u8 pad1[0x10 - 0x0C];
    Block_1533A8 copy;
    u8 pad2[0x70 - 0x60];
    Sub_1533A8* f70;
    void* f74;
    void* f78;
    u8 pad3[0x80 - 0x7C];
    Quad16 q80[4];
    Quad16 qC0[4];
};

struct Gfx_1533A8;
extern f32 D_00261F30[16];

void func_00152B80(Gfx_1533A8* obj, s32 a, s32 b);
void func_001F5C0C(Frame_1533A8* p, s32 zero, s32 size);
void func_00188668(Quad16* out, void* b, void* in);
void func_00152B38(Gfx_1533A8* self);
void func_001EE3B8(Gfx_1533A8* obj, s32 a, s32 b);
void func_001EE668(Gfx_1533A8* obj, s32 a, s32 b, void* c, s32 d);
void func_00152D70(Gfx_1533A8* self);
void func_00166690(Frame_1533A8* frame);

struct Tab_151A88 { u8 pad0[0x1C]; s32 f1C; s32 f20; s32 f24; s32 f28; u8 pad2C[0x54 - 0x2C]; s32 count; ThresholdRange* list; };
struct Tab_261D70 { u32 w[21]; s32 count; ThresholdRange* list; s32 f5C; };
extern Tab_261D70 D_00261D70[2];
extern Tab_261D70 D_00261E30;
extern Tab_261D70 D_00261E90;
s32 func_001EAA70(s32 a, s32 b);

void func_00123ED0(void* self);

struct Item_154880 {
    u8 pad0[0x34];
    f32 f34;
    f32 f38;
    u8 pad1[0x44 - 0x3C];
    void* p44;
    u8 pad2[0x60 - 0x48];
};


void func_0018D608(void);
void func_0018D6F0(void);
void func_0018D800(void* dst, void* src, s32 size);
void func_00153528(ActiveSetSolver* loc, s32 count);
void func_00152470(void* tmp, Item_154880* item);
void func_00153EC0(ActiveSetSolver* loc, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
void func_0014EE40(PooledObject* self)
{
    InitCollider(self);
    SetPooledObjectState(self, -1);
}

void func_0014EE70(PooledObject* self)
{
    RegisterCollider(self);
    if (IsInList(&self->world->list1C78, self)) RemoveFromList(&self->world->list1C78, self);
    if (self->parent != 0 && IsObjectOfKind(self->parent, 0x3A) != 0) {
        self->flags538 |= (u64)0x8000 << 28;
    } else {
        self->flags538 &= ~((u64)1 << 43);
    }
}

void func_0014EF00(PooledObject* self)
{
    RemoveObjectFromParentList(self);
    AppendToList(&self->world->list1C78, self);
    SetPooledObjectState(self, 0);
}

void func_0014EF40(PooledObject* self, Collider* other)
{
    Keep46 save = self->keep56C;
    CopyCollider(self, other);
    self->keep56C = save;
}

void func_0014EF88(PooledObject* self)
{
    LoadCollider(self);
    FindOrBuildMemberGroup(&self->member58C, self);
}

void func_0014EFB8(PooledObject* self, s32 kind, void* msg)
{
    HandlePlacedObjectNotification(self, kind, msg);
    if (kind == 6) {
        if (msg == self->watched) {
            self->watched = 0;
            SetPooledObjectState(self, 4);
        }
    }
}

void func_0014F020(PooledObject* self)
{
    StartPlacedObject(self);
    ResolveObjectLinks(self, 1, g_pooledObjectLinks);
}

void func_0014F058(PooledObject* self, f32 f)
{
    UpdateCollider(self);
    switch (self->state) {
    case 0:
    case 1:
    case 3:
    case 5:
        break;
    case 2:
        UpdateHeldPooledObject(self, f);
        break;
    case 4:
        if (self->delay < g_gameTime[0] - self->stateTime) {
            if (g_player == 0 || self->parent != (BaseObject*)g_player->heldObject)
                SetPooledObjectState(self, 5);
        }
        break;
    }
}

void func_0014F110(PooledObject* self, s32 state)
{
    if (self->state != state) {
        if (self->state != 2) {
            self->state = state;
        } else {
            self->f57C = 0;
            self->f580 = 0;
            self->f584 = 0;
            self->taker = 0;
            self->state = state;
        }
        self->stateTime = g_gameTime[0];
        if (state == 5) {
            (void)func_00126D60((Sub_14F110*)self, self->f564);
        }
    }
}

ASM_FUNC(func_0014F168);

ASM_FUNC(func_0014F270);

void func_0014F740(C23* self)
{
    InitPlayerFlaggedCollider(self);
    self->f6C0 = -1;
}

void func_0014F770(C23* self, s32 kind, void* msg)
{
    s32 result;

    HandlePlacedObjectNotification(self, kind, msg);
    if (kind == 0x14) {
        if (msg == self->p740) {
            func_001B6568(msg, &result);
            if (result == 0x2B7) {
                if (self->hold != 0) {
                    DestroyStateWalker(self->p740);
                    self->p740 = 0;
                } else {
                    ((Held23*)self->p734->f200)->f4C = 1;
                    ((Held23*)self->p734->f200)->f1C = 0;
                    self->p734->desc02()->m1D(self->p734, &self->p734->v190);
                    self->p734->desc02()->m1E(self->p734, &self->p734->m1A0);
                    self->p738->desc02()->m1E(self->p738, &self->p738->m1A0);
                }
            }
        }
    }
}

void func_0014F850(C23* self)
{
    s32 i = 0;
    PostLoadPlacedObject(self);
    if (self->count744 > 0) {
        do {
            void* p = FindFirstObjectByIdMode4(self->world, self->items748[i], self);
            if (p != 0) {
                if (IsObjectOfKind(p, 0x41) != 0) {
                    s32 n = self->count768;
                    self->items76C[n] = p;
                    self->count768 = n + 1;
                }
            }
            i++;
        } while (i < self->count744);
    }
}

void func_0014F900(C23* self)
{
    if (g_player != 0) {
        self->f6DC = (s32)g_player->f24F8;
    }
}

void func_0014F920(C23* self)
{
    StartMaskedCollider(self);
    ResolveObjectLinks(self, 3, g_takerLinks);
    ((Held23*)self->p734->f200)->f4C = 1;
    Src_14F920* s2 = FindFirstObjectByIdMode1(self->world, self->f6C0, self);
    *(Quad16*)&self->q6F0[0] = s2->q190[0];
    *(Quad16*)&self->q6F0[1] = s2->q190[1];
    *(Quad16*)&self->q6F0[2] = s2->q190[2];
    *(Quad16*)&self->q6F0[3] = s2->q190[3];
    self->f730 = s2->f18;
    s32 i = 1;
    if (i < self->cnt) {
        do {
            BaseObject* e = (BaseObject*)CreateObjectCopy(s2, s2->p14, 0);
            if (e->desc->m0F != 0) {
                e->desc->m0F(e);
            }
            i++;
            e->desc->m10(e);
            e->desc->m03(e);
        } while (i < self->cnt);
    }
    ((VFn_14F920Arg)s2->vtbl[25])(s2, 0);
    ((VFn_14F920)s2->vtbl[7])(s2);
    AppendQueuedCall(self->world, (void*)(void (*)(void*))SyncPooledHolderWithPlayer, self, 0, 0);
    self->p740 = CreateStateWalker(self->p73C, self, 0x2B7, 1);
}

void func_0014FA88(C23* self)
{
    s32 st[2];
    UpdateMaskedCollider(self);
    if (self->hold == 0 && self->f6DC != 0 && self->p740 != 0) {
        func_001B6598(self->p740, &st[0]);
        func_001B6568(self->p740, &st[1]);
        if (st[1] == -1) st[1] = st[0];
        if (st[0] == st[1]) {
            switch (st[0]) {
            case 0x2B7:
                if (self->f7B0 != 0) st[1] = 0x2B8;
                else if (self->f78C > 0) st[1] = 0x2B9;
                break;
            case 0x2B8:
                if (self->f7B0 == 0) {
                    if (self->f78C > 0) st[1] = 0x2B9;
                    else st[1] = 0x2B7;
                } else {
                    UpdatePooledHolderAim(self, &st[1]);
                }
                break;
            case 0x2B9:
                if (self->f7B0 != 0) st[1] = 0x2B8;
                else if (self->f78C <= 0) st[1] = 0x2B7;
                else UpdatePooledHolderAim(self, &st[1]);
                break;
            case 0x2BA:
                func_00150008(self);
                st[1] = 0x2B8;
                break;
            case 0x2BB:
                func_00150008(self);
                st[1] = 0x2B9;
                break;
            }
            if (st[1] != st[0]) SetPooledHolderWalkerState(self, st[1]);
        }
    }
}

s32 func_0014FBE0(C23* self, Collider* obj)
{
    if (IsObjectOfKind(obj, 0x46) != 0) {
        if (((PooledObject*)obj)->taker == self) {
            return 1;
        }
    }
    return TestCollidersMayContact(self, obj);
}

void func_0014FC38(C23* self)
{
    s32 status;

    if (self->p6C8 != 0) {
        self->p6C8->desc->m15(self->p6C8, 0);
        self->p6C8->desc->m03(self->p6C8);
    }
    if (self->p740 != 0) {
        TeleportStateWalker(self->p740, 0x2B7);
        func_001B6598(self->p740, &status);
        if (status == 0x2B7) {
            DestroyStateWalker(self->p740);
            self->p740 = 0;
        }
    }
    {
        Held23* o = (Held23*)self->p734->f200;
        ((VFn2_0014FC38)o->vtbl[2])(o, 7);
    }
    func_0013D278(self);
}

void func_0014FCE8(C23* self, s32 code)
{
    s32 r;

    func_001B6568(self->p740, &r);
    if (r == -1) {
        func_001B6598(self->p740, &r);
    }
    if (code == r) {
        return;
    }
    if (r == 0x2B7) {
        ((Held23*)self->p734->f200)->f4C = 0;
    }
    if (code < 0x2BA) {
        if (code >= 0x2B8) {
            ((Held23*)self->p734->f200)->f1C = (code == 0x2B9);
            if (!((u32)(r - 0x2BA) < 2)) {
                self->f6D8 = 0;
            }
        }
    }
    SetStateWalkerTarget(self->p740, code);
}

void func_0014FDA8(C23* self, s32* state)
{
    if (*state == 0x2B8) {
        ((Held23*)self->p734->f200)->f1C = 0;
        if (self->f6D0 < g_gameTime[0] - self->f6D8) {
            if (AcquirePooledObject(self)) {
                *state = 0x2BA;
            }
        }
        return;
    }
    if (self->p6E0 == 0 || IsObjectAttached(self->p6E0) == 0
        || self->p6E0->state == 3 || self->p6E0->state == 4) {
        self->p6E0 = FindFirstAttachedPooledObject(self);
    }
    if (self->p6E0 == 0) {
        return;
    }
    AssignAimTarget((Held23*)self->p734->f200, self->p6E0, (u8*)&D_00248D30);
    if (self->f6D0 < g_gameTime[0] - self->f6D8) {
        if (AcquirePooledObject(self)) {
            *state = 0x2BB;
        }
    }
}

s32 func_0014FEC0(C23* self) {
    PooledObject* s0;

    if (self->p6C8 != 0) {
        return 1;
    }
    if (self->p6CC != 0) {
        if (self->p6CC->state != 5) {
            self->p6CC = 0;
        }
    }
    if (IsListEmpty(&self->world->list1C78) != 0 || self->p6CC != 0) {
        SelectEarliestPooledObject(self);
        return 0;
    }
    s0 = (PooledObject*)self->world->list1C78.head;
    s0->taker = self;
    s0->desc->m02(s0);
    s0->desc->m15(s0, self->f730);
    SetColliderAnchors(s0, 3, 0, 3, 0);
    s0->desc03()->m1D(s0, &self->q6F0[0]);
    s0->desc03()->m1E(s0, (Mat02*)&self->q6F0[1]);
    s0->desc03()->m20(s0, (Vec02*)&D_00248D30);
    s0->desc03()->m21(s0, (Vec02*)&D_00248D30);
    SetPooledObjectState(s0, 1);
    self->p6C8 = s0;
    self->f6D8 = g_gameTime[0];
    return 1;
}

ASM_FUNC(func_00150008);

void func_00150298(C23* self)
{
	ListFrame frame;
	if (self->p6CC != 0) return;
	PooledObject* current = (PooledObject*)g_partList.head;
	PooledObject* best = 0;
	f32 minimum = 3.4028235e+38f;
	while (current != 0) {
		PooledObject* candidate = FindEarliestPooledChild(current);
		current = current->next;

		if (candidate != 0 && candidate->stateTime < minimum) { best = candidate; minimum = candidate->stateTime; }
	}
	if (best != 0) { SetPooledObjectState(best, 5); self->p6CC = best; }
}

PooledObject* func_00150338(C23* state)
{
	for (s32 i = 0; i < state->f78C; ++i) {
		PooledObject* item = (PooledObject*)state->f790[i];
		if (IsObjectAttached(item) == 0) continue;
		if (item->state == 3) continue;
		if (item->state == 4) continue;
		return item;
	}
	return 0;
}

void func_001503E0(C23* self, void* item)
{
    u32 n = (u32)self->count744;
    if (n < 8) {
        self->items748[n] = item;
        self->count744 = n + 1;
    }
}

void func_00150408(C23* self)
{
    self->f78C = 0;
    self->f7B0 = 0;
}

void func_00150418(C23* self, void* event)
{
    if (IsObjectOfKind(event, 7)) {
        self->f7B0 = 1;
        return;
    }
    if (!IsObjectOfKind(event, 0x41)) {
        return;
    }
    s32 found = 0;
    for (s32 i = 0; i < self->count768; i++) {
        if (self->items76C[i] == event) {
            found = 1;
            break;
        }
    }
    if (found) {
        u32 count = self->f78C;
        if (count < 8) {
            self->f790[count] = event;
            self->f78C = count + 1;
        }
    }
}

void func_001504E0(StepSequence* state)
{
	InitPlacedObject();
	state->flags |= ((u64)0x8000u << 17);
	state->second300 = -1;
	state->first30C = -1;
}

void func_00150528(StepSequence* self, void* arg)
{
    LoadPlacedObject(self, arg);
    ReadSequenceSteps(self, arg, &self->count2DC, &self->steps2E0);
}

void func_00150570(void* unused, BufferedStream* rd, s32* outCount, Ent_150570** outArr)
{
    s32 i = 0;
    *outCount = ReadBufferedS8(rd);
    *outArr = (Ent_150570*)AllocateZeroedFrontMemory(*outCount * 0x28);
    for (i = 0; i < *outCount; i++) {
        Ent_150570* e = (Ent_150570*)((u8*)*outArr + i * 0x28);
        e->type = ReadBufferedS8(rd);
        switch (e->type) {
        case 0:
        case 7:
            ReadOptionalBufferedBlock(rd, &e->w4);
            break;
        case 1:
        case 2:
            e->w4 = ReadBufferedS16(rd);
            e->w8 = ReadBufferedS16(rd);
            break;
        case 3:
            *(f32*)&e->w4 = ReadBufferedFloat(rd);
            *(f32*)&e->w8 = ReadBufferedFloat(rd);
            e->wC = ReadBufferedU8(rd);
            e->w10 = ReadBufferedU8(rd);
            e->w18 = ReadBufferedS16(rd);
            e->w1C = ReadBufferedS16(rd);
            e->w20 = ReadBufferedS16(rd);
            e->w24 = ReadBufferedS16(rd);
            ReadBufferedString(rd, e->w14);
            break;
        case 4:
            e->w4 = ReadBufferedS16(rd);
            break;
        }
    }
}

void func_001506F0(StepSequence* self)
{
    StartPlacedObject(self);
    if (self->first30C == -1) {
        self->first30C = self->id;
    }
    void* v = GetIndexedTargetSlot(g_currentEntry, self->first30C);
    self->target304 = v;
    if (!v) {
        self->target304 = self->fallback308;
    }
}

void func_00150750(StepSequence* self)
{
    self->mode2D0 = 1;
}

void func_00150760(StepSequence* self)
{
    self->mode2D0 = 2;
}

void func_00150770(StepSequence* self, s32* out)
{
    *out = *(s32*)self->target304;
}

void func_00150780(StepSequence* self, s32 value)
{
    *(s32*)self->target304 = value;
}

void func_00150790(StepSequence* self, s32 next)
{
    s32 cur = self->state2D4;
    if (next == cur) {
        return;
    }
    switch (cur) {
    case 5:
        if (((Glob_150790*)&D_0026F5A0)->f260 == self) {
            ((Glob_150790*)&D_0026F5A0)->f260 = 0;
        }
        break;
    case 1:
        if (self->mode2D0 != cur) {
            D_00261D38 = D_00261D38 - 1;
        }
        break;
    case 3:
        *(s32*)self->target304 = 1;
        StopStreamVoice();
        TriggerScriptEvent(self, 0x15, 0, 0);
        if (self->mode2D0 == 2) {
            RemoveCameraControllers(g_camera, 0xF, 6, &g_camera->ctl460, 0, 0);
            ReleasePadSelectFlag(g_currentWorld);
        }
        (void)PopStackValue(&g_camera->ctl460);
        if ((self->f2E8 & 0x10) != 0 && self->value2F8 != 0) {
            StopAnimationPlayer((void*)self->value2F8);
        }
        if (self->mode2D0 == 2 && self->f330 != 0) {
            f32 f = 1.0f;
            SetVolumeChannelFactor(9, 0, f);
            SetVolumeChannelFactor(9, 1, f);
        }
        break;
    case 4:
        ((Blk_150790*)&g_typedTextCaptionBox)->f324 = 0;
        SetTextPanelState(&g_typedTextCaptionBox, 0);
        break;
    }
    switch (next) {
    case 5:
        if (((Glob_150790*)&D_0026F5A0)->f260 != 0) {
            SetStepSequenceState(((Glob_150790*)&D_0026F5A0)->f260, 0);
        }
        ((Glob_150790*)&D_0026F5A0)->f260 = self;
        self->state2D4 = next;
        break;
    case 1:
        if (self->mode2D0 != next) {
            D_00261D38 = D_00261D38 + 1;
        }
        self->state2D4 = next;
        break;
    case 3:
        self->step2E4 = -1;
        self->f2E8 = 0;
        if (self->mode2D0 == 2) {
            PushStackValue(&g_camera->ctl460, 4);
            PushCameraController(g_camera, 6, &g_camera->ctl460, 0, 0);
            AcquirePadSelectFlag(g_currentWorld);
            func_001365A0(&g_typedTextCaptionBox, 0);
            if (self->f330 != 0) {
                f32 f = 0.6f;
                SetVolumeChannelFactor(9, 0, f);
                SetVolumeChannelFactor(9, 1, f);
            }
        } else {
            PushStackValue(&g_camera->ctl460, 3);
            if (self->mode2D0 == 0) {
                if (self->second300 != -1) {
                    g_camera->ctl460.f5C = FindFirstObjectByIdMode4(self->world, self->second300, 0);
                } else {
                    g_camera->ctl460.f5C = 0;
                }
            }
        }
        self->state2D4 = next;
        break;
    case 4:
        SetArcTarget(&D_002708E0, 0);
        SetArcSpecialObject(&D_002708E0, 0);
        SetArcTarget(&D_00271558, 0);
        SetArcSpecialObject(&D_00271558, 0);
        self->state2D4 = next;
        break;
    default:
        self->state2D4 = next;
        break;
    }
    self->time2D8 = g_gameTime[0];
}

void func_00150AE8(StepSequence* self)
{
    s32 q[2];
    s32 s1;
    Ent65* s2;

    UpdatePlacedObject(self);
    if (!(((Gl_150AE8*)&g_timerCaption)->f260 < 2 && ((Gl_150AE8*)&g_timerCaption)->f26C == 0 && IsStreamVoiceLocked() == 0 && D_00275F84 != 1)) {
        s32 st = self->state2D4;
        switch (st) {
        case 1:
        case 5:
        case 6:
            SetStepSequenceState(self, 0);
            return;
        }
    }
    FillMemory(q, 0, 8);
    s2 = GetActiveSwitchedCollider();
    if (IsTopCameraController(&g_camera->ctl454) != 0) {
        q[1] = 0;
        q[0] = 0;
    } else if (s2 != 0) {
        s2->vt->f154(s2, self, q);
    } else {
        q[1] = 1;
    }
    s1 = self->state2D4;
    switch (s1) {
    case 0:
        if (self->f324 != 0) {
            if (D_00275F84 == 0 && q[1] != 0) {
                self->f324 = 0;
                ChooseStepSequenceState(self);
                s1 = self->state2D4;
            }
        }
        break;
    case 5:
        if (q[0] == 0) {
            s1 = 6;
            break;
        }
        goto timer;
    case 6:
        if (q[0] != 0) {
            s1 = 5;
            break;
        }
        goto timer;
    case 1:
        if (q[1] != 0) {
            StepSequence* o = D_0027051C;
            if (o == 0) {
                ShowStepSequenceText(self, s2);
                s1 = self->state2D4;
            } else if (o != self) {
                if (o->f328 == 0 && o->state2D4 == 3) {
                    SkipRemainingSteps(o);
                }
            }
            break;
        }
    timer:
        if (g_gameTime[0] - self->time2D8 >= 5.0f) s1 = 0;
        break;
    case 3:
        if (self->mode2D0 != 2) {
            if (!(self->step2E4 < self->count2DC) || D_00275F84 == 1) {
                PopStackElement(g_elementStack);
                s1 = self->state2D4;
            }
        }
        break;
    case 4:
        if (D_00270B30 == 0) {
            if (D_002717A8 == 0) s1 = 0;
        }
        break;
    }
    SetStepSequenceState(self, s1);
    switch (self->state2D4) {
    case 0:
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
        break;
    case 3:
        RunStepSequence(self);
        break;
    }
}

void func_00150DC0(StepSequence* self, Msg_150DC0* msg)
{
    Slot_150DC0* s2;
    Slot_150DC0* s4;
    s32 a2;
    s32 a0;
    f32 f20;
    s8* nm;
    switch (msg->type) {
    case 0:
        OpenKeyRecord(msg->f4.i);
        self->f2E8 |= 1;
        break;
    case 1:
    case 2:
        if (msg->f4.i != -1) {
            s2 = (Slot_150DC0*)FindFirstObjectById(self->world, 0x104, msg->f4.i, self->root ? self->root : self);
        } else {
            s2 = 0;
        }
        if (msg->f8.i != -1) {
            s4 = (Slot_150DC0*)FindFirstObjectById(self->world, 0x104, msg->f8.i, self->root ? self->root : self);
        } else {
            s4 = 0;
        }
        if (s2 && s2->f334) {
            SetStateWalkerTarget(s2->f334, 0x34C);
        }
        switch (msg->type) {
        case 1:
            SetArcTarget(&D_002708E0, s2);
            SetArcSpecialObject(&D_002708E0, s4);
            self->p2F0 = s2;
            if (s2) {
                self->f2E8 |= 2;
            }
            break;
        case 2:
            SetArcTarget(&D_00271558, s2);
            SetArcSpecialObject(&D_00271558, s4);
            self->p2F4 = s2;
            if (s2) {
                self->f2E8 |= 4;
            }
            break;
        default:
            return;
        }
        break;
    case 3:
        if (self->p2F0 && MatchesObjectId((Slot_150DC0*)self->p2F0, msg->f18)) {
            s2 = (Slot_150DC0*)self->p2F0;
            SetArcFade(&D_002708E0, 1);
            SetArcFade(&D_00271558, 0);
        } else if (self->p2F4 && MatchesObjectId((Slot_150DC0*)self->p2F4, msg->f18)) {
            s2 = (Slot_150DC0*)self->p2F4;
            SetArcFade(&D_00271558, 1);
            SetArcFade(&D_002708E0, 0);
        } else {
            s2 = 0;
        }
        a2 = msg->f1C;
        a0 = 0;
        if (a2 != -1) {
            a0 = FindFirstObjectById(self->world, 2, a2, self);
            self->f2E8 |= 0x10;
        } else {
            if (s2) {
                a0 = FindFirstObjectById(self->world, 1, 0x54A, s2);
            }
        }
        if (a0) {
            CreateAnimationPlayerWithoutPresetTargets(0.0f, 1.0f, (Slot_150DC0*)a0, (s32)s2, 1, &self->player2F8);
            func_0012F810(self->player2F8, self);
        }
        nm = msg->f14;
        if (nm && *nm) {
            g_typedTextCaptionBox.vt->m08(&g_typedTextCaptionBox, (const char*)nm);
            if (s2) {
                *(Raw4_150DC0*)&g_typedTextCaptionBox.highlight = s2->f2D0;
            } else {
                g_typedTextCaptionBox.highlight = 0x80808080;
            }
            if (self->player2F8) {
                if (msg->f1C == -1) {
                    f20 = msg->f8.f;
                } else {
                    f20 = self->player2F8->anim->length;
                }
            } else {
                f20 = msg->f8.f;
            }
            if (0.0f < f20) {
                T217D_440* h2 = &g_typedTextCaptionBox;
                h2->charsPerSecond = (f32)(GetStringLength(msg->f14) + 10) / f20;
            } else {
                T217D_440* h3 = &g_typedTextCaptionBox;
                h3->charsPerSecond = 15.0f;
            }
            self->f2E8 |= 0x20;
        }
        if (msg->f4.f >= 0.0f) {
            SetTextPanelValuePercent(&g_typedTextCaptionBox, msg->f4.f + 1.0f);
            self->f2E8 |= 0x40;
        }
        if (msg->f8.f >= 0.0f) {
            self->f2E8 |= 0x80;
            self->f2FC = g_gameTime[0] + msg->f8.f;
        }
        if (msg->f20 != -1) {
            s32 r = FindFirstObjectById(self->world, 0x104, msg->f20, self->root ? self->root : self);
            func_001365A0(&g_typedTextCaptionBox, r);
        }
        if (msg->f24 != -1) {
            g_camera->ctl460.f5C = FindFirstObjectByIdMode4(self->world, msg->f24, 0);
        } else if (self->second300 != -1) {
            g_camera->ctl460.f5C = FindFirstObjectByIdMode4(self->world, self->second300, 0);
        } else {
            g_camera->ctl460.f5C = 0;
        }
        if (msg->fC) {
            self->f2E8 |= 0x100;
            self->f2EC = msg->f10;
        }
        self->f2E8 |= 8;
        break;
    case 4: {
        void* tmp = &msg->f4;
        TriggerScriptEvent(self, 0x10, 1, &tmp);
        break;
    }
    case 5:
        ShowCountedScreenElement(self->world);
        break;
    case 6:
        HideCountedScreenElement(self->world);
        break;
    case 7:
        QueueMovie(g_moviePlayer, msg->f4.i);
        break;
    }
}

void func_001512A8(StepSequence* state, u32 mode, u32 value)
{
	HandlePlacedObjectNotification(state, mode, value);
	if (mode == 6 && value == state->value2F8)
		state->value2F8 = 0;
}

s32 func_00151300(StepSequence* self)
{
    s32 flags = self->f2E8;
    if (flags & 2) {
        Ent_151300* e = self->step2E4 < self->count2DC - 1 ? &((Ent_151300*)self->steps2E0)[self->step2E4 + 1] : 0;
        if (e != 0 && e->f0 == 2) {
            if (flags == 2) return 0;
        }
        if (((Hld_151300*)&D_002708E0)->f270 == self->f2F0 && ((Hld_151300*)&D_002708E0)->f268 == 1) flags &= 0xFFFFFFFD;
    }
    if (flags & 4) {
        Ent_151300* e = self->step2E4 < self->count2DC - 1 ? &((Ent_151300*)self->steps2E0)[self->step2E4 + 1] : 0;
        if (e != 0 && e->f0 == 1 && flags == 4) return 0;
        if (((Hld_151300*)&D_00271558)->f270 == self->f2F4 && ((Hld_151300*)&D_00271558)->f268 == 1) flags &= 0xFFFFFFFB;
    }
    if (flags & 1) {
        if (func_001BE810() == 0) flags &= 0xFFFFFFFE;
    }
    if (flags & 8) {
        if (HasStreamVoice() == 0) flags &= 0xFFFFFFF7;
    }
    if (flags & 0x10) {
        if (self->value2F8 == 0) flags &= 0xFFFFFFEF;
    }
    if (flags & 0x20) {
        if (IsTextPanelTextTyped(&g_typedTextCaptionBox) != 0) flags &= 0xFFFFFFDF;
    }
    if (flags & 0x40) {
        if (((Mgr_151300*)g_camera)->f478 == g_typedTextCaptionBox.value) flags &= 0xFFFFFFBF;
    }
    if (flags & 0x80) {
        if (self->f2FC <= g_gameTime[0]) flags &= 0xFFFFFF7F;
    }
    g_typedTextCaptionBox.f2F8 = 0;
    if (flags == 0x100) {
        s32 r;
        PadRecord* in = (g_padRouting & 4) ? &g_padRecord : &g_blankPadRecord;
        s32 k = self->f2EC;
        r = 0;
        switch (k) {
        case 9:
            if (0.8f < in->f48) r = 1;
            break;
        case 10:
            if (0.8f < in->f7C) r = 1;
            break;
        case 11:
            if (0.8f < __builtin_fabsf(in->f40)) r = 1;
            break;
        case 12:
            if (0.8f < __builtin_fabsf(in->f44)) r = 1;
            break;
        case 13:
            if (g_player != 0 && ((Ctx_151300*)g_player)->f2220 == 2) r = ((Ctx_151300*)g_player)->f2228 == 3;
            break;
        case 14:
        {
            G27C230* fl = g_currentEntry;
            u32 t = fl->bits & 4;
            r = t != 0;
        }
            break;
        default:
            r = (in->flags & D_00261D08[k]) != 0;
            break;
        }
        if (r != 0) {
            flags = 0;
        } else {
            g_typedTextCaptionBox.f2F8 = D_00261D28[k];
        }
    }
    self->f2E8 = flags;
    return flags != 0;
}

void func_001516C0(StepSequence* self)
{
    if (self->state2D4 != 4) {
        if (self->step2E4 < self->count2DC) {
            for (self->step2E4++; self->step2E4 < self->count2DC; self->step2E4++) {
                Item_1516C0* it = &((Item_1516C0*)self->steps2E0)[self->step2E4];
                switch (it->kind) {
                case 0: case 1: case 2: case 3: case 7:
                    break;
                case 4: {
                    s32* p = it->data;
                    TriggerScriptEvent(self, 0x10, 1, (s32*)&p);
                    break;
                }
                case 5:
                    ShowCountedScreenElement(self->world);
                    break;
                case 6:
                    HideCountedScreenElement(self->world);
                    break;
                }
            }
        }
        if (self->mode2D0 == 2)
            PopStackElement(g_elementStack);
    }
}

void func_001517C0(StepSequence* self)
{
    s32 index;

    if (self->step2E4 < self->count2DC) {
        for (;;) {
            if (TestStepWaitConditions(self) != 0) {
                return;
            }
            if (self->value2F8 != 0) {
                StopAnimationPlayer((void*)self->value2F8);
                self->value2F8 = 0;
            }
            index = self->step2E4 + 1;
            self->step2E4 = index;
            if (!(index < self->count2DC)) {
                break;
            }
            HandleStepSequenceMessage(self, (u8*)self->steps2E0 + index * 0x28);
        }
        SkipRemainingSteps(self);
    }
}

void func_00151860(void* value, Object_151860* object)
{
    if (object != 0) {
        object->vtable->callback(object, value);
    } else {
        g_typedTextCaptionBox.child = value;
        PushStackElement(g_elementStack, &g_typedTextCaptionBox);
    }
}

void func_001518B8(StepSequence* self)
{
    Gl_0026E9F8* g = (Gl_0026E9F8*)&g_timerCaption;
    if (g->f260 >= 2 || g->f26C != 0)
        return;
    if (IsStreamVoiceLocked() != 0)
        return;
    if (D_00275F84 == 1)
        return;
    if (self == D_0027051C)
        return;
    s32 mode = 1;
    if (*(s32*)self->target304 != 0) {
        mode = (self->mode2D0 == 2) ? self->state2D4 : 5;
    } else {
        s32 n = self->f310;
        if (n > 0) {
            for (s32 i = 0; i < n; i++) {
                if (*(s32*)self->f314[i] != 0) {
                    mode = 5;
                    break;
                }
            }
        }
    }
    SetStepSequenceState(self, mode);
}

void func_001519A8(StepSequence* self)
{
    if (self->state2D4 != 1 && self->state2D4 != 3) {
        SetStepSequenceState(self, 0);
    }
}

void func_001519E0(StepSequence* collection, const char* name, u32 kind)
{
	if ((u32)collection->f310 >= 4) return;
	void* item = GetLevelEntryByKey(name);
	if (!item) return;
	void* value = GetIndexedTargetSlot(item, kind);
	if (!value) return;
	u32 count = collection->f310;
	collection->f314[count] = value;
	collection->f310 = count + 1;
}

void* func_00151A58(void)
{
    return &g_scatterController;
}

void func_00151A68(void* state)
{
	FillMemory(state, 0, 0x24);
}

void func_00151A88(G261EF0* self)
{
    self->f04 = 4;
    self->f08 = 6;
    self->f0C = 1;
    self->f10 = 3;
    GameProgress* g = g_saveData;
    if (g->f19D8 == 0 || g->f19D8 == 5 || g->f19DC == 1) self->table = &D_00261E90;
    else if (!(g_currentEntry->flags & 2)) self->table = D_00261D70;
    else self->table = &D_00261E30;
    SetScatterLevel(self, g_currentEntry->dt);
    s32 a = ((Tab_151A88*)self->table)->f1C;
    s32 b = ((Tab_151A88*)self->table)->f24;
    f32 t = g_currentEntry->dt;
    s32 ra;
    if (a == b) ra = b;
    else if (a < b) ra = a + (s32)(t * ((f32)b + 0.99900001f - (f32)a));
    else ra = b + (s32)((1.0f - t) * ((f32)a + 0.99900001f - (f32)b));
    s32 c = ((Tab_151A88*)self->table)->f20;
    s32 d = ((Tab_151A88*)self->table)->f28;
    t = g_currentEntry->dt;
    s32 rc;
    if (c == d) rc = d;
    else if (c < d) rc = c + (s32)(t * ((f32)d + 0.99900001f - (f32)c));
    else rc = d + (s32)((1.0f - t) * ((f32)c + 0.99900001f - (f32)d));
    s32 r = RandomIntInRange(ra, rc);
    s32 i = 0;
    ThresholdRange* e = 0;
    self->f14 = r;
    for (; i < ((Tab_151A88*)self->table)->count; i++) {
        e = &((Tab_151A88*)self->table)->list[i];
        if (e->threshold <= g_currentEntry->f10) break;
    }
    self->f18 = RandomIntInRange(e->low, e->high);
    self->f20 = 0;
}

void func_00151D28(Self_151D28* self)
{
    if (D_00275B00 & 8) {
                if (self->field_1C->f2C <= g_currentEntry->dt && g_currentEntry->dt < self->field_1C->f34) {
            if (g_saveData->f19E4 < self->field_1C->f30) {
                SetSpareCount(self->field_1C->f30);
                self->field_20 = 1;
            }
        } else if (self->field_1C->f34 <= g_currentEntry->dt) {
            if (g_saveData->f19E4 < self->field_1C->f38) {
                SetSpareCount(self->field_1C->f38);
                self->field_20 = 1;
            }
        }
    } else {
        f32 v = ClampToRange((u8*)self->field_1C + 8, g_currentEntry->dt);
        SetScatterLevel(self, v);
    }
    CompleteSoundNotifiers(g_currentWorld);
}

void func_00151E18(void* self)
{
}

void func_00151E20(G261EF0* self, f32 amount)
{
    f32 x = g_currentEntry->dt + amount * *(f32*)((u8*)self->table + 0x10);
    SetScatterLevel(self, x);
    s32 index = g_saveData->f19E0;
    f32 y;
    if (index < 0) {
        y = *(f32*)((u8*)self->table + 0x40);
    } else {
        y = *(f32*)((u8*)self->table + 0x3C);
        if (index <= *(s32*)((u8*)self->table + 0x4C)) {
            y += *(f32*)((u8*)self->table + 0x50);
        }
    }
    f32 result = ((f32 (*)(void*, f32))ClampToRange)(&g_unitRange, g_currentEntry->f10 + amount * y);
    g_currentEntry->f10 = result;
}

void func_00151ED8(G261EF0* obj, FlaggedObject* node)
{
    f32 value;
    if (node != 0) {
        s32 idx = node->ordinal;
        s32 bit = 1 << (idx & 7);
        if (g_currentEntry->bits74[idx / 8] & bit) {
            value = ((Part_151ED8*)obj->table)->f18;
            goto have;
        }
    }
    value = ((Part_151ED8*)obj->table)->f14;
have:
    SetScatterLevel(obj, g_currentEntry->dt + value);
    if (node != 0) {
        G27C230* m = g_currentEntry;
        s32 idx = node->ordinal;
        s32 bit = 1 << (idx & 7);
        u8 cur = m->bits74[idx / 8];
        if (cur & bit) return;
        m->bits74[idx / 8] = cur | bit;
        m->count70 = m->count70 + 1;
    }
}

void func_00151FC8(G261EF0* object)
{
	SetScatterLevel(object, 0.0f);
	G27C230* manager = g_currentEntry;
	manager->f10 = 0.0f;
	manager->count70 = 0;
	FillMemory(manager->bits74, 0, 1);
}

void func_00152010(G261EF0* self, void* p, s32 n, s32 flag)
{
    s32 did = 0;
    if ((g_currentWorld)->f2354 != 0 && n != 0) {
        if (!flag) {
            self->f18--;
            self->f14--;
        }
        if (n > 0) {
            ScatterObjectsAroundCircle(g_currentWorld, 0x58, p, n, 0);
        } else {
            if (self->f18 < 0) {
                if (g_currentEntry->f10 != 0.0f) {
                    did = 1;
                    g_currentEntry->f10 = ClampToRange(&g_unitRange, g_currentEntry->f10 + ((Table_152010*)self->table)->f44);
                }
                s32 i = 0;
                Range_152010* r = 0;
                while (i < ((Table_152010*)self->table)->count) {
                    r = &((Table_152010*)self->table)->ranges[i];
                    if (g_currentEntry->f10 >= r->threshold) break;
                    i++;
                }
                self->f18 = RandomIntInRange(r->lo, r->hi);
            }
            if (!flag) {
                for (s32 i = 0; i < ((Table_152010*)self->table)->count - 1; i++) {
                    if (((Table_152010*)self->table)->ranges[i].threshold <= g_currentEntry->f10) {
                        s32 v = RandomIntInRange(((Table_152010*)self->table)->ranges[i].lo, ((Table_152010*)self->table)->ranges[i].hi);
                        self->f18 = (self->f18 < v) ? self->f18 : v;
                        goto done;
                    }
                }
            done:;
            }
            if (did) {
                ScatterObjectsAroundCircle(g_currentWorld, 0x57, p, 1, 0);
            } else {
                s32 a, b;
                if (self->f14 < 0) {
                    a = self->f04;
                    b = self->f08;
                    self->f14 = RandomIntInRange(Lerp_152010::Get(((Table_152010*)self->table)->f1C, ((Table_152010*)self->table)->f24), Lerp_152010::Get(((Table_152010*)self->table)->f20, ((Table_152010*)self->table)->f28));
                } else {
                    a = self->f0C;
                    b = self->f10;
                }
                n = RandomIntInRange(a, b);
                if (n) ScatterObjectsAroundCircle(g_currentWorld, 0x58, p, n, 0);
            }
        }
    }
    if (!flag) {
        g_currentEntry->f10 = ClampToRange(&g_unitRange, g_currentEntry->f10 + ((Table_152010*)self->table)->f48);
    }
}

void func_00152410(G261EF0* object, f32 unused)
{
	f32 value = ((f32 (*)(void*))ClampToRange)(object->table);
	g_currentEntry->dt = value;
}

void func_00152438(List01* self, s32 offset)
{
    self->offset = offset;
}

void func_00152440(List01* p)
{
	p->tail = 0;
	p->head = 0;
}

void func_00152450(Pair_00152450* p)
{
	p->second = 0;
	p->first = 0;
}

u32 func_00152460(List01* p, u32 value)
{
	return value + p->offset;
}

void func_00152470(List01* self, u32 value)
{
    u32* slot = (u32*)GetListLinks(self, value);
    if (self->tail == 0) {
        self->head = (void*)value;
    } else {
        u32* oldTail = (u32*)GetListLinks(self, (u32)self->tail);
        slot[1] = (u32)self->tail;
        oldTail[0] = value;
    }
    self->tail = (void*)value;
}

void func_001524D8(List01* self, u32 value)
{
    u32* slot = (u32*)GetListLinks(self, value);
    if (self->head == 0) {
        *(u32*)((u8*)self + 4) = value;
        *(u32*)self = value;
        return;
    }
    {
        u32* oldHead = (u32*)GetListLinks(self, (u32)self->head);
        slot[0] = (u32)self->head;
        oldHead[1] = value;
        self->head = (void*)value;
    }
}

void func_00152540(List01* self, u32 before, u32 value)
{
    if (before == 0) {
        AppendToList(self, value);
        return;
    }
    if (before == (u32)self->head) {
        PrependToList(self, value);
        return;
    }
    u32* next = (u32*)GetListLinks(self, value);
    u32* previous = (u32*)GetListLinks(self, before);
    u32 after = previous[1];
    u32* afterSlot = (u32*)GetListLinks(self, after);
    next[0] = before;
    next[1] = after;
    previous[1] = value;
    afterSlot[0] = value;
}

LINKER_REMNANT(func_001525F8);

void func_00152600(u8* a, void* b)
{
    Link_00152600* link = (Link_00152600*)GetListLinks(a, b);
    ListFrame* e = g_activeListFrames;
    while (e != 0) {
        if ((s32)e->link != (s32)link) {
            e = e->prev;
            continue;
        }
        if (link->f4 != 0) e->link = (u8*)GetListLinks(a, (void*)link->f4);
        else e->link = a;
        e = e->prev;
    }
    if (link->f4 != 0) {
        *(s32*)GetListLinks(a, (void*)link->f4) = link->f0;
    } else {
        *(s32*)a = link->f0;
    }
    if (link->f0 != 0) {
        *(s32*)((u8*)GetListLinks(a, (void*)link->f0) + 4) = link->f4;
    } else {
        *(s32*)(a + 4) = link->f4;
    }
    link->f0 = 0;
    link->f4 = 0;
}

s32 func_001526D0(void* self, u8* item)
{
    u8* slot = (u8*)GetListLinks((List01*)self, (u32)item);
    s32 result = 0;
    if (*(void**)slot != 0) {
        goto matched;
    }
    if (*(void**)((u8*)self + 4) != item) {
        goto done;
    }
matched:
    result = 1;
done:
    return result;
}

u32 func_00152720(List01* p)
{
	return p->head == 0;
}

void func_00152730(List01* dst, List01* src)
{
    if (src->head != 0) {
        if (dst->head == 0) {
            *dst = *src;
            ClearList(src);
        } else {
            u32 p1 = GetListLinks(dst, (u32)dst->tail);
            u32 p2 = GetListLinks(src, (u32)src->head);
            *(u32*)p1 = (u32)src->head;
            *(u32*)(p2 + 4) = (u32)dst->tail;
            dst->tail = src->tail;
            ClearList(src);
        }
    }
}

s32 func_001527D8(List01* list)
{
    s32 count = 0;
    u8* node = (u8*)list->head;
    if (node != 0) {
        s32 stride = list->offset;
        do {
            node = *(u8**)(node + stride);
            count++;
        } while (node != 0);
    }
    return count;
}

void func_00152810()
{
	ResetDmaController(1);
	ResetGsPaths();
	g_vif0Channel = GetDmaChannel(0);
	g_vif1Channel = GetDmaChannel(1);
	g_gifChannel = GetDmaChannel(2);
	g_fromSprChannel = GetDmaChannel(8);
	g_toSprChannel = GetDmaChannel(9);
}

extern const VEnt_0024A0E0 D_0024A0E0[4] = {{0, 0}, {0, func_00152E18}, {0, 0}, {0, 0}};

V24A0* func_00152888(V24A0* self)
{
    self->f10 = 0;
    self->f14 = 0;
    self->vt = (const V24A0_Vt*)D_0024A0E0;
    ClearPacketBuffer(self);
    return self;
}

void func_001528C8(V24A0* p)
{
	p->end = 0;
	p->begin = 0;
	p->f08 = 0;
	p->cur = 0;
}

void func_001528E0(V24A0* p)
{
	u8* b = p->begin;
	p->f08 = 0;
	p->cur = b;
}

void func_001528F0(V24A0* self, s32 count)
{
    s32 size = count << 4;
    u8* base = ReservePermanentMemory(size);
    self->cur = base;
    self->end = base + size;
    self->begin = base;
}

void func_00152938(Buffer_00152938* buffer, u32 count)
{
	u32 bytes = count << 4;
	u8* memory = AllocateFrontMemory(bytes);
	buffer->allocated = memory;
	buffer->end = memory + bytes;
	buffer->current = memory;
}

void func_00152980(V24A0* buffer, u32 count)
{
	u32 bytes = count << 4;
	u8* memory = AllocateBackMemory(bytes);
	buffer->cur = memory;
	buffer->end = memory + bytes;
	buffer->begin = memory;
}

void func_001529C8(V24A0* self, s32 count, u8* base)
{
    self->begin = base;
    self->cur = base;
    self->end = base + count * 16;
}

void func_001529E0(V24A0* self, u32* outCount, u8** outBegin)
{
    CloseDmaTag(self);
    if (outCount != 0) {
        *outCount = ((u32)self->cur - (u32)self->begin) >> 4;
    }
    if (outBegin != 0) {
        *outBegin = self->begin;
    }
    ClearPacketBuffer(self);
}

void func_00152A50(V24A0* self, u32* count, u32* begin, u32* out)
{
    CloseDmaTag(self);
    u32 n = (self->curU - (u32)self->begin) >> 4;
    if (count != 0) {
        *count = n;
    }
    if (begin != 0) {
        *begin = (u32)self->begin;
    }
    if (out != 0) {
        *out = CopyToFrontMemory(n << 4, (u32)self->begin);
    }
    ClearPacketBuffer(self);
}

void func_00152AE0(V24A0* self, void* dma)
{
    CloseDmaTag(self);
    SyncDataCache(0);
    StartDmaChain(dma, self->begin);
    self->cur = self->begin;
}

LINKER_REMNANT(func_00152B30);

void func_00152B38(V24A0* self)
{
    CloseDmaTag(self);
    u8* q = self->cur;
    self->f08 = (s32*)q;
    self->cur = q + 16;
    *(u64*)q = 0x10000000;
    *(u64*)((u8*)self->f08 + 8) = 0;
}

void func_00152B80(V24A0* self, s32 lo, s32 hi)
{
    s32 flag = 0;
    if (self->f08 != 0) {
        CloseDmaTag(self);
        flag = 1;
    }
    u8* p = self->cur;
    self->cur = p + 16;
    *(u64*)p = (u64)lo | 0x40000000 | ((u64)hi << 32);
    *(u64*)(p + 8) = 0;
    if (flag != 0) {
        u8* q = self->cur;
        self->f08 = (s32*)q;
        self->cur = q + 16;
        *(u64*)q = 0x10000000;
        *(u64*)((u8*)self->f08 + 8) = 0;
    }
}

void func_00152C18(V24A0* self, s32 hi)
{
    s32 flag = 0;
    if (self->f08 != 0) {
        CloseDmaTag(self);
        flag = 1;
    }
    u8* p = self->cur;
    self->cur = p + 16;
    *(u64*)p = ((u64)hi << 32) | 0x50000000;
    *(u64*)(p + 8) = 0;
    if (flag != 0) {
        u8* q = self->cur;
        self->f08 = (s32*)q;
        self->cur = q + 16;
        *(u64*)q = 0x10000000;
        *(u64*)((u8*)self->f08 + 8) = 0;
    }
}

void func_00152CA0(V24A0* self)
{
    CloseDmaTag(self);
    u64* p = (u64*)self->cur;
    self->cur = (u8*)p + 0x10;
    p[0] = 0x60000000ull;
    p[1] = 0;
}

void func_00152CE0(void* self, s32 index, s32 count)
{
    CopyQuadwords(*(void**)((u8*)self + 0xC), count, index);
    *(u8**)((u8*)self + 0xC) += index * 16;
}

void func_00152D30(void* self)
{
    CloseDmaTag(self);
    u8* cursor = *(u8**)((u8*)self + 0xC);
    *(u8**)((u8*)self + 0xC) = cursor + 0x10;
    *(u64*)cursor = 0x70000000;
    *(u64*)(cursor + 8) = 0;
}

void func_00152D70(V24A0* self)
{
    if (self->f10 != 0) {
        s32 p = self->curS;
        if ((p & 0xF) != 0) {
            *(s32*)p = 0;
            p += 4;
            while ((p & 0xF) != 0) { *(s32*)p = 0; p += 4; }
        }
        self->curS = p;
    } else if (self->f14 != 0) {
        const V24A0_Vt* t = self->vt;
        t->close((V24A0*)((u8*)self + t->adj1), 0);
    }
    s32* q = self->f08;
    if (q != 0) {
        *q = *q | (((self->curS - (s32)q) >> 4) - 1);
        self->f08 = 0;
    }
}

void func_00152E18() {}

LINKER_REMNANT(func_00152E20);

void func_00152E28(C61* self)
{
    InitPlacedObject(self);
}

void func_00152E48(Self_152E48* self, RangeRecord* a)
{
    V24A0 pa;
    V24A0 pb;
    Vec_152E48 v0;
    Vec_152E48 v1;
    Quad4 q;
    TextureHeader* tex;
    s32 i;
    u64 bits;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;

    self->f2D0 = a;
    if (a == 0) {
        return;
    }
    tex = *((B_152E48*)a->link)->c->tex;
    InitGifPacket(&pa);
    InitPacketWriter(&pb);
    PushBackMemoryMark();
    AllocateTempPacketBuffer(&pa, 0x40);
    AllocateTempPacketBuffer(&pb, 0x40);
    WriteVifFlushE(&pb);
    SetupTextureRenderTarget(tex, &pa);
    BeginGifTag(&pa, 0x246, 3, 0x551);
    AddGifRgbaEntry(&pa, 0);
    AddGifXyzEntry(&pa, 0, 0, 0);
    AddGifXyzEntry(&pa, tex->w << 4, tex->h << 4, 0);
    BeginGifTag(&pa, 0x200, 1, 0xE);
    AddGifRegisterWrite(&pa, 0x41, ((u64)(tex->w - 2) << 16) | (((u64)(tex->h - 2) << 48) | 0x100000001ULL));
    EndGifPacket(&pa);
    WriteVifDirectFromWriter(&pb, &pa);
    v0.x = (f32)((tex->w - 1) * 8) * 1024.0f;
    v0.y = (f32)((tex->h - 1) * 8) * 1024.0f;
    v0.z = 0;
    v1.x = (f32)(tex->w * 8) * 1024.0f + 8589934592.0f;
    v1.y = (f32)(tex->h * 8) * 1024.0f + 8589934592.0f;
    v1.z = 0;
    WriteVifBaseOffset(&pb, 0, 0);
    CopyWordsToWriter(&pb, 8, 1, &v0, 0);
    CopyWordsToWriter(&pb, 8, 1, &v1, 1);
    ClearPacketBuffer(&pa);
    UsePacketBufferMemory(&pa, 1, &q);
    ReserveGifPackedData(&pa, 0x24D, 0, 3, 0x412, 0);
    CopyWordsToWriter(&pb, 0xC, 1, &q, 0xC);
    DetachPacketBufferCopy(&pb, &self->f2D4, 0, &self->f2D8, 0x13);
    PopBackMemoryMark();
    PushBackMemoryMark();
    ClearPacketBuffer(&pa);
    ClearPacketBuffer(&pb);
    AllocateTempPacketBuffer(&pa, 0x80);
    AllocateTempPacketBuffer(&pb, 0x80);
    bits = (tex->tex0 & ~0x1800000000ULL) | 0x800000000ULL;
    BeginGifTag(&pa, 0x200, 1, 0xE);
    AddGifRegisterWrite(&pa, 0x3F, 0);
    AddGifRegisterWrite(&pa, 7, bits);
    AddGifRegisterWrite(&pa, 0x15, 0x61);
    AddGifRegisterWrite(&pa, 0x48, 0x31001);
    BeginGifTag(&pa, 0x316, 5, 0xE5353);
    x0 = tex->w << 4;
    y0 = tex->h << 4;
    x1 = x0 + 8;
    y1 = y0 + 8;
    for (i = 1; i >= 0; i--) {
        AddGifUvEntry(&pa, 0x10, 8);
        AddGifXyzEntry(&pa, 0, 0, 0);
        AddGifUvEntry(&pa, x0 + 0x10, y1);
        AddGifXyzEntry(&pa, x0, y0, 0);
        AddGifRegisterWrite(&pa, 0x3F, 0);
        AddGifUvEntry(&pa, 8, 0x10);
        AddGifXyzEntry(&pa, 0, 0, 0);
        AddGifUvEntry(&pa, x1, y0 + 0x10);
        AddGifXyzEntry(&pa, x0, y0, 0);
        AddGifRegisterWrite(&pa, 0x3F, 0);
        AddGifUvEntry(&pa, 8, 8);
        AddGifXyzEntry(&pa, 8, 8, 0);
        AddGifUvEntry(&pa, x1, y1);
        AddGifXyzEntry(&pa, x1, y1, 0);
        AddGifRegisterWrite(&pa, 0x3F, 0);
    }
    EndGifPacket(&pa);
    WriteVifFlush(&pb);
    WriteVifDirectFromWriter(&pb, &pa);
    DetachPacketBufferCopy(&pb, &self->f2DC, 0, &self->f2E0, 0x13);
    PopBackMemoryMark();
}

void func_00153328(C61* self, s32 unused, void* a2)
{
    (void)unused;
    if (self->f2D0 != 0) {
        self->desc02()->m27(self, a2);
        Frame_153328 f;
        (void)FillMemory(&f, 0, 0x80);
        f.fn = (void*)DrawPlacedObjectParts;
        f.f08 = 0;
        BuildPlacedObjectTransform(self, a2, f.out);
        f.self = self;
        QueueDeferredRequest(&f);
    }
}

void func_001533A8(Self_1533A8* self)
{
    Frame_1533A8 f;
    s32 i;
    u8* base = (u8*)&g_vifPacketWriter;
    Sub_1533A8* s1 = self->f60;
    AddDmaRefTag((Gfx_1533A8*)base, s1->f2D4, s1->f2D8);
    FillMemory(&f, 0, 0x80);
    f.f08 = 3;
    f.fn = (void*)DrawModelPart;
    f.copy = self->copy;
    f.f70 = s1;
    f.f74 = (u8*)s1 + 0x22C;
    i = 0;
    MultiplyMatrices(f.qC0, D_00261F30, (u8*)s1->f2D0 + 0x70);
    f.q80[0] = f.qC0[0];
    f.q80[1] = f.qC0[1];
    f.q80[2] = f.qC0[2];
    f.q80[3] = f.qC0[3];
    BeginDmaTag((Gfx_1533A8*)&g_vifPacketWriter);
    WriteVifBaseOffset((Gfx_1533A8*)&g_vifPacketWriter, 0, 0);
    CopyWordsToWriter((Gfx_1533A8*)&g_vifPacketWriter, 0xC, 4, f.q80, 4);
    CloseDmaTag((Gfx_1533A8*)&g_vifPacketWriter);
    if (s1->f238 > 0) {
        s32 off = 0;
        do {
            i++;
            f.f78 = (u8*)s1->f23C + off;
            DrawModelPart(&f);
            off += 0x70;
        } while (i < s1->f238);
    }
    AddDmaRefTag((Gfx_1533A8*)&g_vifPacketWriter, s1->f2DC, s1->f2E0);
}

void func_00153528(ActiveSetSolver* self, s32 count)
{
	(void)FillMemory(self, 0, 0x50);
	s32 n = count << 1;
	self->slots = n;
	s32 size = 0x60 * n;
	self->items = AllocateBackMemory(size);
	(void)FillMemory(self->items, 0, size);
	SetListLinkOffset(&self->active, 0x4C);
	SetListLinkOffset(&self->atLow, 0x4C);
	SetListLinkOffset(&self->atHigh, 0x4C);
	SetListLinkOffset(&self->pending, 0x4C);
	s32 sq = (n * n) << 2;
	self->matrix = (f32*)AllocateBackMemory(sq);
	self->factor = (f32*)AllocateBackMemory(sq);
	self->rhs = (f32*)AllocateBackMemory(count << 3);
	self->solution = (f32*)AllocateBackMemory(count << 3);
}

void func_00153608(Self_153608* self)
{
    s32 i;
    self->f3C = 0;
    ClearList(self->f0C);
    ClearList(self->f18);
    ClearList(self->f24);
    ClearList(self->f30);
    for (i = 0; i < self->count; i++) {
        Elem_153608* e = (Elem_153608*)(self->items + i * 0x60);
        e->f34 = e->f38 = 0.0f;
        (void)FillMemory(e->f4C, 0, 8);
        AppendToList(self->f30, e);
    }
}

ASM_FUNC(func_001536C8);

ASM_FUNC(func_00153780);

void func_00153A50(ActiveSetSolver* self, Node_153A50* x)
{
    s32 iter;
    Node_153A50* p;
    Node_153A50* q;
    f32* w;
    s32 i;
    if (x) {
        RemoveFromList(&self->pending, x);
        AppendToList(&self->active, x);
        self->activeCount++;
    }
    iter = 0;
    do {
        {
            f32* out = self->matrix;
            for (p = (Node_153A50*)self->active.head; p; p = p->next) {
                for (q = (Node_153A50*)self->active.head; q; q = q->next) {
                    *out = p->vec[q - (Node_153A50*)self->items];
                    out++;
                }
            }
        }
        FactorSymmetricMatrix(self->activeCount, self->matrix, self->factor);
        {
            f32* out = self->rhs;
            for (p = (Node_153A50*)self->active.head; p; p = p->next) {
                *out = -p->val;
                out++;
            }
        }
        SolveFactoredSystem(self->activeCount, self->factor, self->rhs, self->solution);
        for (i = 0; i < self->count; i++) {
            f32 sum = 0.0f;
            w = self->solution;
            for (p = (Node_153A50*)self->active.head; p; p = p->next) {
                sum += *w * p->vec[i];
                w++;
            }
            ((Node_153A50*)self->items)[i].rate = sum;
        }

        Node_153A50* best = 0;
        f32 bestT = 1.0f;
        s32 code = 0;
        w = self->solution;
        for (p = (Node_153A50*)self->active.head; p; p = p->next) {
            f32 f = *w;
            w++;
            if (p->kind != 2) {
                if (0.0001f < f) {
                    if (p->flag != 0) {
                        f32 t = (p->hi - p->lo) / f;
                        if (t < bestT) {
                            bestT = t;
                            best = p;
                            code = 4;
                        }
                    }
                } else if (f < -0.0001f) {
                    f32 t = -p->lo / f;
                    if (t < bestT) {
                        bestT = t;
                        best = p;
                        code = 2;
                    }
                }
            }
        }
        for (Node_153A50* n = (Node_153A50*)self->atLow.head; n; n = n->next) {
            f32 f = n->rate;
            if (!(-0.0001f < f)) {
                f32 t = -n->val / f;
                if (t < bestT) {
                    bestT = t;
                    best = n;
                    code = 1;
                }
            }
        }
        for (Node_153A50* n = (Node_153A50*)self->atHigh.head; n; n = n->next) {
            f32 f = n->rate;
            if (!(f < 0.0001f)) {
                f32 t = -n->val / f;
                if (t < bestT) {
                    bestT = t;
                    best = n;
                    code = 3;
                }
            }
        }
        for (i = 0; i < self->count; i++) {
            Node_153A50* r = (Node_153A50*)self->items + i;
            r->val += bestT * r->rate;
        }
        {
            w = self->solution;
            for (p = (Node_153A50*)self->active.head; p; p = p->next) {
                p->lo += bestT * *w;
                w++;
            }
        }
        switch (code) {
        case 0:
            return;
        case 2:
            self->activeCount--;
            RemoveFromList(&self->active, best);
            AppendToList(&self->atLow, best);
            if (best == x) return;
            break;
        case 1:
            self->activeCount++;
            RemoveFromList(&self->atLow, best);
            AppendToList(&self->active, best);
            break;
        case 4:
            self->activeCount--;
            RemoveFromList(&self->active, best);
            AppendToList(&self->atHigh, best);
            if (best == x) return;
            break;
        case 3:
            self->activeCount++;
            RemoveFromList(&self->atHigh, best);
            AppendToList(&self->active, best);
            break;
        }
        iter++;
    } while (iter < 10);
}

void func_00153EC0(ActiveSetSolver* self, s32 a1, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7)
{
    Frame_153EC0 fr;
    ListFrame frame;
    s32 e = (s32)&self->pending;
    fr.cursor = e;
    fr.list = e;
    s32 old = (s32)g_activeListFrames;
    s32 link = *(s32*)(e + 8);
    g_activeListFrames = (ListFrame*)&fr;
    fr.prev = old;
    s32 h = *(s32*)e;
    fr.link = link;
    fr.cursor = h + link;
    Node_153EC0* node = (Node_153EC0*)h;
    while (node != 0) {
        if (node->f28 == 2) {
            if (node->f44 == 0) {
                func_00153780(self, a1, node, a3, a4, a5, a6);
            }
            RemoveFromList(&self->pending, node);
            AppendToList(&self->active, node);
            self->activeCount++;
        }
        Node_153EC0* nx = *(Node_153EC0**)fr.cursor;
        s32 lk = fr.link;
        fr.cursor = (s32)nx + lk;
        node = nx;
    }
    PivotActiveSet(self, (Node_153A50*)0);
    g_activeListFrames = (ListFrame*)fr.prev;
    for (;;) {
        f32 best = -0.01f;
        Node_153EC0* sel = 0;
        for (Node_153EC0* p = (Node_153EC0*)self->pending.head; p != 0; p = p->next) {
            if (p->f38 < best) {
                best = p->f38;
                sel = p;
            }
        }
        if (!sel) break;
        if (sel->f44 == 0) {
            func_00153780(self, a1, sel, a3, a4, a5, a6);
        }
        PivotActiveSet(self, (Node_153A50*)sel);
    }
}

ASM_FUNC(func_00154088);

ASM_FUNC(func_00154370);

void func_00154880(s32 count, u8* data, f32* values, f32* out)
{
    ActiveSetSolver loc;
    s32 i;

    PushBackMemoryMark();
    InitActiveSetSolver(&loc, count);
    for (i = 0; i < count; i++) {
        Item_154880* item = (Item_154880*)(loc.items + i * 0x60);
        item->p44 = AllocateBackMemory(count * 4);
        CopyMemory(item->p44, data + i * count * 4, count * 4);
        item->f38 = values[i];
        AppendToList(&loc.pending, item);
    }
    loc.count = count;
    RunActiveSetSolver(&loc, 0, 0, 0, 0, 0);
    for (i = 0; i < count; i++)
        out[i] = *(f32*)(loc.items + i * 0x60 + 0x34);
    PopBackMemoryMark();
}
