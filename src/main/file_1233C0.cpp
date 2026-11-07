// SPDX-License-Identifier: AGPL-3.0-or-later
// 0x1233C0 to 0x130F48: the state triggers (classes 0x22 and 0x2F), the placed object's set-up,
// update and loading (func_00123ED0 to func_001289C0), its range, sound and colour records, the
// code checksum, the animation players and their events, the id filter object, the sector stream
// reader and the curve segment helpers. One file between two edges; it could be several.
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
#include "placed_object.h"
#include "state_trigger.h"
#include "masked_collider.h"
#include "world.h"
#include "animation.h"
#include "attachment.h"
#include "t2196.h"
#include "range_record.h"
#include "sound_record.h"
#include "object_link.h"
#include "target_binding.h"
#include "globals.h"
#include "object_cycler.h"
#include "paired_object.h"
#include "code_checksum.h"
#include "switched_collider.h"
#include "shapes.h"
#include "id_filter_object.h"
#include "c8b.h"
#include "s1dbbd8.h"
#include "stream_reader.h"
#include "key_id.h"
#include "game_progress.h"
#include "base_object.h"
#include "stream_reader_window.h"

f32 D_00260E70[4] = { 0.0f, 15.0f, 0.0149999997f, 0.0f };
f32 D_00260E80[4] = { 0.0f, 2.5f, 0.00249999994f, 0.0f };
f32 D_00260E90[4] = { 0.0f, 15.0f, 1.5f, 0.0f };
f32 D_00260EA0[4] = { 0.0f, 2.5f, 0.25f, 0.0f };
f32 D_00260EB0[4] = { 1500.0f, 0.0f, 0.5f, 4500.0f };
f32 D_00260EC0[4] = { 15.0f, 0.0f, 0.5f, 45.0f };
f32 D_00260ED0[4] = { 2.0f, 0.0f, 0.100000001f, 0.0f };
f32 D_00260EE0[4] = { -50.0f, 4.0f, 0.0f, 0.0f };
f32 D_00260EF0[4] = { 0.0f, 400.0f, 0.0f, 0.0f };

void* func_0015A418(void* world, s32 kind, s32 id, void* scope);
void* func_0015A448(void* world, s32 id, void* scope);
AnimationPlayer* func_0012D3F8(World* pool);
void func_0012FDE8(StreamReader* a0);

void func_0011F850(T2196_Weight** axis, s32* outCount, f32** outTimes);

struct Buffer_00120130 { u8 bytes[0x20]; };
typedef void (*Finish_00120130)(PlacedObject* self, void* output, void* state);
extern void func_0011F9F8(s32, Key2196_Vec*, s32, void*, void*);
extern void func_00188A20(void*, void*);
extern void func_001EDE38(void*, void*, void*);

extern void func_0011F9F8(s32, Key2196_Vec*);
extern void func_0011FB98(s32, Key2196_Vec*, s32*, f32**);

struct Result_001202F0 { f32 x; f32 y; f32 z; };
struct Output_001202F0 { f32 x; u8 pad4[0x10]; f32 y; u8 pad18[0x10]; f32 z; };
extern void func_0011F6B0(T2196_Weight**, PlacedObject*, void*, Vec02*, void*, s32, f32, f32);
extern void func_001F5C0C(void*, s32, s32);

void func_0011F798(T2196_Weight** a, Vec02* b, Stream83* c);

struct Result_001203A8 {
    f32 first;
    f32 second;
    f32 third;
};
struct Output_001203A8 {
    f32 first;
    u8 pad4[0x10];
    f32 second;
    u8 pad18[0x10];
    f32 third;
};
extern void func_0011F9F8(s32, Key2196_Vec*, void*, f32*, s32, f32, f32);

extern void func_0011FA88(s32*, Key2196_Vec**, Stream83*);

extern void* func_001B5EE0(void*);

extern World* D_00275710;

void func_0018D800(Attachment* self, Attachment* src, s32 size);

// Gives the owner the position and the orientation this attachment gives (slots 29, 30, 32, 33).
struct Locals_121648 {
    Vec02 pos;
    Vec02 vec;
    Mat02 rot;
};

// The owner's slot 44 (Desc02::m28) and 45 (m29) are told what was asked.
typedef void (*Told_1227B0)(PlacedObject* self, Vec02* a, Vec02* b);

typedef void (*Told_1227F0)(PlacedObject* self, Mat02* b, Vec02* q);

typedef void (*Told_122920)(PlacedObject* self);

void func_00121338(Attachment* self, PlacedObject* a1);

void func_00152600(void* list, void* item);
void func_00121358(Attachment* self, s32 flags);

extern f32 D_0026185C[];
void func_001214B8(Attachment* self, Vec02* a1, Vec02* a2);
s32 func_0012E9E0(AnimationPlayer* t, f32* a, f32* b);

void func_00121508(Attachment* self, Mat02* a, Vec02* b);

extern void func_0013D278(void*);

extern u8 D_00261420[];
void func_001B7968(Collider* self);
s32 func_00140FF8(void* p);

extern void func_001BA130(Collider*);

typedef void (*VFn_123578)(void* self);
struct Obj_123578 { VFn_123578* vtbl; };
struct Ctx_123578 { u8 pad[0x2220]; s32 f2220; };


void func_001B93F8(Collider* self);
s32 func_001300E8(void* node, s32 kind);

typedef void (*VFn_123B28)(void* self, s32 arg);

struct Vtbl_123B28 {
    u8 pad0[0x134];
    VFn_123B28 f134;
};

struct Elem_123B28 {
    Vtbl_123B28* vt;
    u8 pad1[0x560 - 4];
    s32 f560;
};

extern s32 func_0013EC00(void*, s32, void*, void*, void*, void*, void*);

s32 func_001C1A28(void* a, void* b);

struct Record_001250C8 { u8 pad[8]; s32 value; };

struct Object_00126BC0 {
    u32* vtable;
    u8 pad0[0x18];
    Object_00126BC0* next;
    u8 pad1[0x14];
    Object_00126BC0* child;
    u8 pad2[0x200];
    s32 count;
    u8* records;
};
struct Record_00126BC0 { u8 pad0[0x14]; s32 type; u8 pad1[0x54]; s32 value; };

struct Child_00123BB0 { void** vt; };

typedef void (*VFn_123C20)(void* self);
struct Item_123C20 { VFn_123C20* vtbl; };

struct Locals_001201F0 {
    u8 a[0x30];
    u8 b[0x30];
    u8 c[0x30];
    u8 d[0x10];
    f32 first;
};

extern void func_00189150(void*, void*, void*);
extern void func_00188D28(void*, void*, void*);

extern f32 D_00260E60[4];
extern f32 D_0026186C;
extern f32 D_00261860;
extern f32 func_001EA4B8(void*, s32, f32, f32, f32);

void* func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);
void func_00124A48(void* self);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
void func_00182ED8(void* a);

struct Frame_123448 { s32 f00; s32 f04; s32 f08; s32 f0C; };

void func_00121568(Attachment* self, f32* value, f32* slope);

extern void func_00121568(Attachment* self, f32* a1, f32* a2);

extern void func_00121580(Attachment* self, Mat02* a1);

typedef void (*VFn_1236C8)(void* self, void* arg);
struct Obj_1236C8 { VFn_1236C8* vt; };
void func_00123400(C22* node, StateTrigger* value);
void func_001CAD40(void* node, void* self);
s32 func_00141008(void* table, s32 v);

extern u8 D_002623D8[];

void func_001BF788(s32 a, s32 b);
void func_001BF048(s32 a);
void func_0013ECB0(void* a, s32 b, void* c, void* d, s32 e);
void func_00160D00(void* p);
void func_001B64D8(void* a, s32 b);
void func_001B6628(void* a, s32 b);
s32 func_00141008(void* a, s32 b);
void func_00141040(void* a, s32 b);
void func_001837E0(BaseObject* self, s32 a, s32 b, s32 c);
s32 func_001BEEF8(s32 a);
s32 func_00160CF0(void* p);
void func_001BFCD8(s32 a0, void* a1, StateTrigger* a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

// The position curves' tables, defined at the end of this file.
extern const T2196_PosVt D_002196B8;
extern const T2196_PosVt D_002196C8;
extern const T2196_PosVt D_002196D8;
void* func_0018D5C0(s32 bytes);

void func_00152600(void* a, void* b);
void func_001BA500(void* a, void* b, void* c, void* d, s32 e);
void func_001274F8(void* a, void* b);
void func_00127590(void* a, void* b);
void func_001B5F28(void* a, void* b);


s32 func_00139970(f32 x, f32 period, s32 count, Pair2196* p, f32* out);
f32 func_001EA408(f32 a);

extern const T2196_RotVt D_002196E8;
extern const T2196_RotVt D_002196F8;
extern const T2196_RotVt D_00219708;

extern const T2196_ScaleVt D_00219718;
extern const T2196_ScaleVt D_00219728;
void* func_0018D5C0(u32 n);

extern u8 D_00219560[];

typedef void (*Told_1214B8)(PlacedObject* self, Vec02* out);

void func_00121338(Attachment* self);

// The dispatch tables func_00121160 gives each kind of curve: three functions, or one and a
// shared one, each table followed by a zero word.
void func_0011F0C8();
void func_0011EFC8();
void func_0011F180();
void func_0011F320();
void func_0011F210();
void func_0011F3E8();
void func_0011F478();
void func_0011F568();
void func_0011F620();
void func_0011EFB0();
void func_00120AA8();
void func_00120D58();
void func_00120110();
void func_00120130();
void func_001201D0();
void func_001201F0();
void func_001202C0();
void func_001202F0();
void func_00120360();
void func_00120388();
void func_001203A8();
void func_00120418();
void func_00120440();
extern const T2196_WeightVt D_00219668;
extern const T2196_WeightVt D_00219678;
extern const T2196_WeightVt D_00219688;
extern const T2196_WeightVt D_00219698;
extern const T2196_WeightVt D_002196A8;
void* func_0018D5C0(T2196_Weight* n);

typedef void (*Told_121508)(PlacedObject* self, Mat02* out1, Vec02* out2);

void func_00152438(void* list, s32 n);
void func_00182C18(BaseObject* self);

// Two stores of the set-up written as small inline helpers, the shape that matches: a value
// passed as an int, and a matrix copied through its own pointer (as each copy's own register).
struct Init_00123ED0 {
    static void SetB2CA(PlacedObject* o, s32 value) { o->b2CA = value; }
    static void Copy(Mat02* dst, const Mat02* src) { *dst = *src; }
};

#include "world.h"
#include "object_cycler.h"
#include "paired_object.h"

void func_00182ED0(BaseObject* self);
void func_00152440(void* a);
void func_0015F710(World* world, void* b);
void func_00143B20(void* a, PlacedObject* b);
void func_00129DF8(PlacedObject* self);
void func_001837E0(PlacedObject* self, s32 a1, s32 a2, s32 a3);

extern void* func_00159BB0();
extern s32 func_00182FC8(void*);

extern void func_00188FD8(void*, void*);

void* func_00159BB0(void);
s32 func_00182FC8(void* self);

struct Sub_126C58 {
    s32 f0;
    f32 f4;
};

// What slot 29 tells the object's listeners (kind 3): the position before, and the object.
struct Frame_1273F0 {
    void* self;
    u8 pad[0xC];
    Vec02 q;
};

void func_001226D8(void* p);

s32 func_00123DC0(void* a);
void func_00129DF8(void* self);

s32 func_00123E00(void* a);

struct Vec3_127558 { f32 x; f32 y; f32 z; };

typedef void (*VFn0_124EE8)(void* self);

struct Info_124EE8 {
    u8 pad0[8];
    s32 flags;
};

struct Node_124EE8 {
    Info_124EE8* info;
};

struct List_124EE8 {
    s32 head;
    u8 pad4[0x4];
    s32 link;
};

struct Obj_124EE8 {
    void** vt;
    u8 pad4[0x30];
    List_124EE8 list;
};

struct Frame_124EE8 {
    s32 list;
    s32 cursor;
    s32 link;
    s32 prev;
};

void func_00124EE8(void* self, f32 f);

struct __attribute__((aligned(16))) Quad_1261C0 { s32 w[4]; };
struct Inner_1261C0 { u8 pad0[0x60]; Quad_1261C0 q60[4]; u8 pad1[4]; s32 fA4; u8 pad2[8]; s32 fB0; };

void func_00128DB8(void* self);
void func_00124540(void* self);
void func_0012A860(void* self, void* v);
void func_00165828(void* a, void* b);

struct Sub_1249A8 {
    u8 pad0[0x20];
    s32 f20;
};


void func_001BFCD8(s32 a0, void* a1, void* a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void* a4, s32 a5);

void func_00182D48(BaseObject* self);
void func_00152470(void* list, void* item);
void func_0015F7D8(World* world, PlacedObject* item);
void func_00143AF8(PlacedObject* a, PlacedObject* self);

struct Pair_124A48 {
    s32 a;
    s32 b;
};
struct Frame_124A48 {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
};

void func_00182C58(BaseObject* self);
void func_00124CC0(PlacedObject* self);
void* func_001DBCC8(void* owner, void* fn, PlacedObject* arg, s32 a3, s32 a4);
void func_00165728(void* a, PlacedObject* b);
s32 func_001B1D38(RangeRecord* p);
void func_001B1D70(RangeRecord* p, f32 v);
void func_001B1DA8(RangeRecord* p, f32 v);
void func_00152E48(void* a, RangeRecord* b);
void func_001B1B38(RangeRecord* p);
void func_001BFCD8(s32 a0, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void* a1, PlacedObject* a2, s32 a3, void* a4, s32 a5);
s32 func_001833F0(BaseObject* a, s32 b);
s32 func_00182FC8(BaseObject* p);

void func_001830D8(BaseObject* self, BaseObject* src);
void func_00165920(u8* a, PlacedObject* self, u8* src);
void* func_0018D568(s32 size, void* src);
void* func_00121280(void* src, World* world, PlacedObject* self);
void func_001299E0(PlacedObject* self, void* v);
u8* func_001B5EC0(Pool6C* pool);
void func_0018D800(u8* dst, void* src, s32 n);
void func_00152450(u8* p);
void func_00143AF8(void* list, PlacedObject* item);

// NEAR: the branches and the 0x40-byte copy loop match; retail loads both quads of a pair before
// storing them (and computes the loop end in $v0), ours interleaves load and store.

struct __attribute__((aligned(16))) Quad_00125B70 { s32 w[4]; };
struct Dst_00125B70 {
    Quad_00125B70 q[4];
    f32 f40;
    f32 f44;
    f32 f48;
    f32 f4c;
};

extern u8 D_00248D40[];

void func_00188C10(Vec02* a, Mat02* b, u8* c, void* d);

void func_00182ED8(void* node);
void func_001832F0(void* node, BaseObject* ctx);

struct Iter_00124050 { List01* list; u8* link; s32 offset; Iter_00124050* saved; };

struct Next_00124050 {
    static BaseObject* Of(Iter_00124050* it)
    {
        BaseObject* obj = *(BaseObject**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_00124050 {
    static void Of(Iter_00124050* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_00124050*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

struct Iter_00124338 { List01* list; u8* link; s32 offset; Iter_00124338* saved; };

struct Next_00124338 {
    static BaseObject* Of(Iter_00124338* it)
    {
        BaseObject* obj = *(BaseObject**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_00124338 {
    static void Of(Iter_00124338* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_00124338*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

struct Iter_00126F78 { List01* list; u8* link; s32 offset; Iter_00126F78* saved; };

struct Next_00126F78 {
    static BaseObject* Of(Iter_00126F78* it)
    {
        BaseObject* obj = *(BaseObject**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_00126F78 {
    static void Of(Iter_00126F78* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_00126F78*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

void* func_00183058(BaseObject* item, World* world, PlacedObject* parent);
void func_001BB580(PlacedObject* self);

struct Object_124FC0;
struct Vtable_124FC0 {
    u8 pad0[0xC];
    void (*update)(Object_124FC0*, f32);
};
struct Object_124FC0 { Vtable_124FC0* vtable; };
struct Iter_124FC0 { List01* list; u8* link; s32 offset; Iter_124FC0* saved; };

struct Next_124FC0 {
    static Object_124FC0* Of(Iter_124FC0* it)
    {
        Object_124FC0* obj = *(Object_124FC0**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_124FC0 {
    static void Of(Iter_124FC0* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = ((Iter_124FC0*)D_0027B314);
        D_0027B314 = (ListFrame*)it;
    }
};

void func_00165FE0(u8* sub, PlacedObject* self, f32 f);
void func_001B2140(void* p, f32 f);
void func_00126AC8(PlacedObject* self, f32 f);
void func_001837E0(PlacedObject* self, s32 a, s32 b, void** args);

struct Ctx_124CC0 { Animation* node; void* key; s32 mode; f32 value; f32 f10; };

void func_0012C9E8(Animation* a, PlacedObject* b, f32 c, void* d, f32* e, s32 f, s32 g);
void func_0012C288(Animation* a, PlacedObject* b, s32 c, TargetBinding* d, f32 e, f32 f, s32 g, s32 h);

struct Clamp_124CC0 {
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        if (x < lo) {
            return lo;
        }
        if (hi < x) {
            return hi;
        }
        return x;
    }
};

struct Find_124CC0 {
    static Animation* Of(PlacedObject* self, Ctx_124CC0* ctx)
    {
        if (ctx->node != 0) {
            return ctx->node;
        }
        return (Animation*)func_0015A418(self->world, 0x104, (s32)ctx->key, self);
    }
};

struct Frame_124CC0 : TargetBinding { u8 pad0[8]; f32 tmp; };

struct Fl_1276C0 {
    u8 pad0[0x90];
    f32 f90;
    f32 f94;
    u8 pad98[0xB0 - 0x98];
    s32 fB0;
};

struct Locals_1276C0 {
    u8 a20[16];
    u8 a30[16];
    u8 a40[16];
    u8 a50[16];
    u8 pad60[0x30];
};

void func_00128018(PlacedObject* z, BaseObject* frame, void* c, u8* d);
void func_00128150(PlacedObject* z, BaseObject* frame, void* c, u8* d);
void func_00128330(BaseObject* a, BaseObject* b, void* c, void* d, void* e, s32 f, s32 g, u8* h, u8* i, s32 j, s32 k);

typedef void (*Fn_2197C0)();
extern const Fn_2197C0 D_002197C0[10];
void* func_00121228(World* root, BaseObject* item, void* table);

void func_0012A4A0(void* self, s32 a1);

void func_00129730(void* self);

struct Sub_12A580 { u8 pad[0x40]; f32 f40; };

struct Sub_12A5B8 { u8 pad[0x40]; f32 f40; };

struct Vec16_12A5D0 { s32 v[4]; } __attribute__((aligned(16)));
struct Sub_12A5D0 { u8 pad[0x50]; Vec16_12A5D0 v50; };

extern u8 D_00275C40[];

struct __attribute__((packed)) U64_12A630 { u64 v; };
struct Sub_12A630 { u8 pad[0x60]; U64_12A630 v60; };

extern u8 D_00275C60[];

struct Vec16_12A6A0 { s32 v[4]; } __attribute__((aligned(16)));
struct Sub_12A6A0 { u8 pad[0x70]; Vec16_12A6A0 v70; };

void* func_001291D0(f32 x);
void func_001B1DA8(void* p, f32 x);

extern u8 D_0027B520[];
void func_001B1AC8(void* p);

struct Sub_129510 { u8 pad[0x44]; f32 f44; };

void* func_0018D500(s32 n);

struct __attribute__((aligned(16))) Quad_129F58 { s32 v[4]; };

void func_0012A320(void* self, f32* v);

void func_0012A3E8(void* self, s32 flag);

struct Sub_12A770 { u8 pad[0x44]; void* f44; };

void* func_00185468(void* p);

struct Ctx_12AA28 { u8 pad[0x90]; void* field; };

Ctx_12AA28* func_0012A970(void* self);

struct Inner_12AC88 { s32 value; };

struct Inner_12AD98 { u8 pad[0xC]; f32 value; };

void func_0012ABA8(void* self, f32 f);

struct Inner_12AEB0 { u8 pad[0x1C]; void* ptr; };

void func_001BF7F8(void* p);

struct Entry_12B0B0 { s32 w[16]; } __attribute__((aligned(16)));

extern Entry_12B0B0 D_00260F00[4];

void func_0012B040(void* self);

struct Obj_12B2E8 { u8 pad[0xC]; u32 value; };

struct Part_128DB8 {
    u8 pad0[0x60];
    BaseObject* p60;
    BaseObject* p64;
    u8 pad68[0x18];
    s32 f80;
    BaseObject* p84;
    void* p88;
    u8 pad8c[0xB0 - 0x8C];
    s32 flags;
};

void* func_0015A868(void* a0, s32 a1);

struct Timer_129108 { u8 pad0[4]; s32 f4; s32 f8; s32 fC; f32 f10; };

void* func_0018D5C0(s32 size);

void* func_001B5EE0(void* a0);
void func_001B1AC8(void* a0);
void func_00152470(void* a0, void* a1);

struct Sub_12A7F8 { u8 pad0[0x48]; s32 f48; };

struct Sub_12A810 { u8 pad0[0x20]; s32 f20; };

void func_00129730(PlacedObject* self);

struct Sub_12A848 { u8 pad0[0x20]; s32 f20; };

struct Sub_12A8B8 { u8 pad0[0x4C]; s32 f4C; };

struct Sub_12A8C8 { u8 pad0[0x4C]; s32 f4C; };

void* func_0011E580(s32 a0, s32 a1, void* a2, s32 a3, s32 a4);

void* func_001291D0(void* self);
void func_001B1CF8(void* self, s32 value);

void* func_001291D0(void* self, f32 x);
void func_001B1D70(void* self, f32 v);

struct __attribute__((aligned(16))) Quad_12A028 { s32 w[4]; };

struct __attribute__((aligned(16))) Quad_12A0F8 { s32 w[4]; };

struct Sub_12ACD8 { u8 pad0[4]; f32 value; };

struct Sub_12ACF8 { u8 pad0[8]; f32 value; };

void func_0012ABA8(PlacedObject* self);

struct __attribute__((packed)) Rec_12AD30 { s32 a; s32 b; };
struct Sub_12AD30 { u8 pad0[0x14]; Rec_12AD30 rec; };

struct Sub_12AD78 { u8 pad0[8]; f32 value; };

s32 func_00182FC8(PlacedObject* self);
void func_00143AF8(Camera* a, PlacedObject* self);
void func_00143B20(Camera* a, PlacedObject* self);

void func_001B1FB0(void* self, f32 x);

void func_001B1FE0(void* self, f32 x);

void func_001B2010(void* self, f32 x);

void func_001B2068(void* self, void* src);

typedef u64 Quad_129EE0 __attribute__((mode(TI)));
struct Frame_129EE0 { Quad_129EE0 r; Quad_129EE0 a; Quad_129EE0 b; };

void func_00118CF0(Quad_129EE0* out, void* src);
void* func_00118D10(Quad_129EE0* out, void* src);
Quad_129EE0 func_00118D30(Quad_129EE0 a, Quad_129EE0 b);
Quad_129EE0 func_00118D20(Quad_129EE0* out, Quad_129EE0 v);
void func_00129F58(void* self, Quad_129EE0* src);

struct __attribute__((packed)) Vec4_12A150 { f32 x, y, z, w; };
struct Vec4F_12A150 { f32 x, y, z, w; };

void func_0012A200(PlacedObject* self, Vec4_12A150* src);

void* func_0018D500(s32 size);

struct Part_0012AC08 { void* link; f32 f4; f32 f8; f32 fc; f32 f10; u8 sub14[8]; u8 sub1C[4]; f32 f20; };

struct __attribute__((packed)) Pack4_12A2C0 { f32 a, b, c, d; };

extern void func_0012A320(PlacedObject* self, Pack4_12A2C0* in);

struct __attribute__((packed)) Pack4_12A320 { f32 a, b, c, d; };

void* func_0018D500(u32 size);

struct Part_12AE20 { u8 pad0[0xC]; f32 weight; u8 pad1[0xC]; void* ptr; };

void func_001BF8E8(void* p);

struct Part_12AE58 { u8 pad0[0xC]; f32 weight; u8 pad1[0xC]; void* ptr; };

struct Node_129450 {
    u8 pad[2];
    s16 value_2;
};

struct Sub_129480 {
    u8 pad[4];
    f32 value_4;
};

void* func_00129400(void* self);

struct Node_129C20 {
    u8 pad0[0x10];
    Node_129C20* f10;
    u8 pad1[4];
    void* f18;
    void* f1C;
};

s32 func_001833F0(void* key, s32 item);

struct __attribute__((packed)) U64_12A700 { u64 v; };
struct Sub_12A700 { u8 pad[0x80]; U64_12A700 v80; };

struct Part_12AE78 { u8 pad[0x10]; f32 value; };

struct Part_12AEE8 { u8 pad[0x10]; f32 value; };

struct Inner_0012B238 { u8 pad[0x30]; f32 value; };

struct Sub_1294B0 { u8 pad[8]; f32 f8; };

struct Sub_1294E0 { u8 pad[0x40]; f32 f40; };

typedef u64 Quad_129E10 __attribute__((mode(TI)));
struct Frame_129E10 { Quad_129E10 r; Quad_129E10 a; Quad_129E10 b; };

void func_00118CF0(Quad_129E10* out, void* src);
void* func_00118D10(Quad_129E10* out, void* src);
Quad_129E10 func_00118D30(Quad_129E10 a, Quad_129E10 b);
Quad_129E10 func_00118D20(Quad_129E10* out, Quad_129E10 v);
void func_00129E88(void* self, Quad_129E10* v);

struct Sub_12A7A8 { u8 pad[0x44]; s32 v44; };

struct __attribute__((packed)) U64_12AF00 { u64 v; };
struct Sub_12AF00 { u8 pad[0x14]; U64_12AF00 p14; };

// Newly matched US functions from the small-function wave.
extern void func_0012A430(void*, s32);
extern void func_001BE4D8(void*);
struct Quad_129598 { s32 words[4]; } __attribute__((aligned(16)));
struct Result_129598 { u8 pad[0x30]; Quad_129598 value; };
struct Node_129B98 { u8 pad0[8]; void* item; void* owner; u8 pad2[0x34 - 0x10]; Node_129B98* next; };
extern s32 func_001833F0(void*, s32);
struct State_12A430 { u8 pad[0x10]; u8 value; };
extern void func_001296E0(void*);
struct State_12A4A0 { u8 pad[0x11]; u8 value; };
struct State_12A4E8 { u8 pad[0x14]; s32 value; };
extern void func_00129A58(void*);
struct State_12A7C0 { u8 pad[0x48]; s32 value; };
extern void func_00129730(void*);
extern void func_0012ABA8(void*);
struct Inner_12ABD0 { s32 value; };
extern void func_001BF788(void*, s32);
struct Inner_12B010 { u8 pad[0x1C]; void* resource; };
extern void func_0012B040(void*);
struct Vec_12B140 { s32 v[4]; } __attribute__((aligned(16)));
struct Vec_12B1A0 { s32 v[4]; } __attribute__((aligned(16)));

struct Sub_00129540 { u8 pad[4]; f32 value; u8 gap[0x38]; f32 scale; };
f32 func_00205778(f32 a, f32 b);

struct Sub_0012AA00 { u8 pad[0x8C]; f32 value; };

void func_001B5388(void* part, f32 a, f32 b);

void func_00159A00(void* part, f32 value);

extern Entry_12B0B0 D_00261000[2];

void func_001BF788(void* ptr, s32 value);

struct Node_1299E0 { u8 pad0[8]; Node_1299E0* next; u8 pad1[8]; s32 key; };

void func_00152540(void* list, Node_1299E0* before, Node_1299E0* value);

void func_00188FD8(void* a, f32* out);

struct Local_129648 { f32 tmp[4]; f32 out[4]; u8 pad[0x20]; };

void func_00188A20(void* a, void* b);

void func_00182C18(void* self);
void func_00152438(void* self, s32 value);

// NEAR: same bytes except the load order of the arguments to func_001BFCD8 (retail loads a0, a4, f12, a1, f13..f15 and f16 last, in the delay slot)
struct Part_0012AC08R { void* link; f32 f4; f32 f8; f32 fc; f32 f10; u8 sub14[8]; void* sub1C; f32 f20; };

void func_001BF788(void* self, s32 n);
void func_001BFCD8(void* a0, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void* a1, void* a2, s32 a3, void* a4, s32 a5);

// NEAR: same bytes except the load order of the arguments to func_001BFCD8 (retail loads a0, a4, f12, a1, f13..f15 and f16 last, in the delay slot)
struct __attribute__((packed)) Rec_0012AF38 { s32 a; s32 b; };
struct Part_0012AF38 { void* link; f32 f4; f32 f8; f32 fc; f32 f10; Rec_0012AF38 rec14; void* sub1C; f32 f20; };

// NEAR: same bytes except the prologue order: retail loads the crc word and the table base before the n > 0 test (lw v0, addiu t1, then blez); ours tests first
s32 D_00261080[4];

void func_001837E0(void* self, s32 a, s32 b, s32 c);

s32 func_00137D10(Stream83* p);
s32 func_00137BE0(Stream83* p);
s32 func_00137CC0(Stream83* p);
s32 func_00137B90(Stream83* p);
void func_0012D2A8(Animation* a, Track83* b);
void func_0012BC38(Animation* a, Stream83* b, s32 c, s32* d, s32* e);
void func_0011EC40(Animation* a, Stream83* b);
T2196_Pos* func_00120FB0(s32 cc);
T2196_Rot* func_00121050(s32 cc);
T2196_Scale* func_001210F0(s32 cc);
T2196_Weight* func_00121160(s32 cc);

struct Sub_12B5B8 {
    u8 pad0[0x60];
    void* f60;
    u8 pad1[0xB0 - 0x64];
    s32 fB0;
};

void func_00128018(void* a, void* b, void* c, void* d);
void func_00128150(void* a, void* b, void* c, void* d);

s32 func_00137C40(void* a);
void func_00137EB0(void* a, void* b);
s32 func_00137D10(void* a);
void func_00137E70(void* a, void* b);
f32 func_00137DF8(void* a);
s32 func_00137B90(void* a);

typedef u64 Quad_129FB0 __attribute__((mode(TI)));
struct Frame_129FB0 { Quad_129FB0 r; Quad_129FB0 a; Quad_129FB0 b; };

void func_00118CF0(Quad_129FB0* out, void* src);
void* func_00118D10(Quad_129FB0* out, void* src);
Quad_129FB0 func_00118D30(Quad_129FB0 a, Quad_129FB0 b);
Quad_129FB0 func_00118D20(Quad_129FB0* out, Quad_129FB0 v);
void func_0012A028(PlacedObject* self, Quad_129FB0* src);

typedef u64 Quad_12A080 __attribute__((mode(TI)));
struct Frame_12A080 { Quad_12A080 r; Quad_12A080 a; Quad_12A080 b; };

void func_00118CF0(Quad_12A080* out, void* src);
void* func_00118D10(Quad_12A080* out, void* src);
Quad_12A080 func_00118D30(Quad_12A080 a, Quad_12A080 b);
Quad_12A080 func_00118D20(Quad_12A080* out, Quad_12A080 v);
void func_0012A0F8(PlacedObject* self, Quad_12A080* src);

void func_001299E0(PlacedObject* self, void* src);

extern u8 D_0021A790[];

struct Node_129D00 { u8 pad0[0x14]; void* w14; };

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_002195D8[];
void func_001299E0(PlacedObject* self, Node_129D00* n);

void func_001853F0(void* a, void* b, void* c);

extern const Fn_Table D_00219600[];

struct Inner_0012A8D8 {
    u8 pad0[0x11];
    u8 f11;
    u8 pad1[0x1C - 0x12];
    f32 f1C;
    f32 f20;
};

void func_001299E0(PlacedObject* self, Inner_0012A8D8* src);

struct __attribute__((aligned(16))) Quad_12B180 { s32 a, b, c, d; };

struct __attribute__((aligned(16))) Quad_12B1E0 { s32 a, b, c, d; };

void func_001F5C0C(void** p, s32 v, s32 n);
void func_001226D8(Attachment* n);

struct Rd_12BC38;
struct Rec_12BC38 { f32 t; s32 kind; s32 w8; s32 wC; };
struct Sub_12BC38 { s32 w0; s32 w4; s32 w8; s32 wC; s32 w10; };
struct Ev_12BC38 {
    s16 h0, h2;
    u8 pad4[0xA];
    s16 hE, h10;
    u8 pad12[2];
    s32 w14, w18;
    f32 f1C, f20, f24;
};
struct Grp_12BC38 { s16 n; s16 h[1]; };

s32 func_00137CC0(Rd_12BC38* r);
void* func_0018D5C0(s32 n);
void func_00138550(Rd_12BC38* r, void* out);
s32 func_00137D10(Rd_12BC38* r);
s32 func_00137D78(Rd_12BC38* r);
f32 func_00137DF8(Rd_12BC38* r);
s32 func_00137B90(Rd_12BC38* r);
s32 func_00137BE0(Rd_12BC38* r);
void func_00137A60(Rd_12BC38* r, s32 n, void* dst);
void func_001384A0(Rd_12BC38* r, void* out);

#define F32(x) (*(f32*)&(x))
#define H0(x) (*(s16*)&(x))
#define H2(x) (*((s16*)&(x) + 1))

struct Entry_12B2F8 { s32 key; s32 val; };
struct St_12B2F8 {
    u8 pad0[0x13]; s8 f13; u8 pad14[0x24]; void* f38; s32 f3C;
    s32 Set(s32 v) { s32 o = f13; f13 = v; return o != v; }
};
extern const Fn_Table D_002195B0[];

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_001212D8();
void func_00121358();
void func_00122890();
void func_00122920();
void func_00122968();
void func_001229C0();
void func_001229E0();
f32 func_00122A00();
void func_00122A18();
void func_00122A80();
void func_00122B30();
void func_00122C48();
void func_00122CB0();
f32 func_00122D90();
void func_0011EF40();
void func_0011EF48();
void func_0011EF60();
void func_0011EF68();
void func_0011EF70();
void func_0011EF88();
void func_0011EF90();
void func_0011EFA8();
void func_001214B8();
void func_00121568();
void func_00121580();
f32 func_001215A8();
void func_00122DA0();
void func_00122DE0();
extern const Fn_Table D_002195B0[10];
extern const Fn_Table D_002195D8[10];
extern const Fn_Table D_00219600[26];

struct Context_001288F0;
struct List_001288F0 { u8* head; u8 pad4[4]; s32 offset; };
struct Iter_001288F0 { List_001288F0* list; u8* link; s32 offset; Iter_001288F0* saved; };
s32 func_001C1A28(Context_001288F0* context, PlacedObject** obj);

struct Next_001288F0 {
    static PlacedObject* Of(Iter_001288F0* it)
    {
        PlacedObject* obj = *(PlacedObject**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_001288F0 {
    static void Of(Iter_001288F0* it, List_001288F0* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_001288F0*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

struct Node_129A58 { u8 pad0[8]; Node_129A58* next; u8 padC[8]; s32 key; };

void func_00152600(List01* list, Node_129A58* node);
void func_00152540(List01* list, Node_129A58* at, Node_129A58* node);

struct Begin_129A58 {
    static void Of(Iter_001288F0* it, List01* list)
    {
        it->list = (List_001288F0*)list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = (Iter_001288F0*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

struct Next_129A58 {
    static Node_129A58* Of(Iter_001288F0* it)
    {
        Node_129A58* node = *(Node_129A58**)it->link;
        it->link = (u8*)node + it->offset;
        return node;
    }
};

Entry_12B0B0 D_00260F00[4] = {
    { { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x42F00000, 0x433E0000, 0x42E60000, 0x00000000, 0x42F00000, 0x433E0000, 0x42700000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } },
    { { 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x437F0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } },
    { { 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x42F00000, 0x437F0000, 0x437F0000, 0x00000000, 0x42F00000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } },
    { { 0x00000003, 0x00000000, 0x00000000, 0x00000000, 0x43700000, 0x437F0000, 0x437F0000, 0x00000000, 0x43700000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } }
};

Entry_12B0B0 D_00261000[2] = {
    { { 0x00000004, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x437F0000, 0x437F0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } },
    { { 0x00000005, 0x00000000, 0x00000000, 0x00000000, 0x43960000, 0x437F0000, 0x437F0000, 0x00000000, 0x43960000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x00000000, 0x00000000, 0x00000000 } }
};

void func_00121338();
void func_00122F88();
void func_00122F28();
void func_00122FE0();
void func_00123120();
void func_00123270();
void func_001232E8();
void func_00123358();

extern u8 D_00148D64[];
void func_00123ED0(void* self);

s32 func_0012C288(void* a, void* b, s32 c, s32 d, s32 e, s32 f);

void* func_0012CCE8(void);

s32 func_001833F0(void* a, void* b);

void func_00121648(void* n, void* b);

struct Mid_12F7E0 { u8 pad[0x14]; void* p14; };
struct Obj_12F7E0 { u8 pad[8]; Mid_12F7E0* mid; };

void func_001831E8(void* a, void* b, void* c, s32 d);

s32 func_0012FF10(StreamReader* self);
s32 func_001F8C38(s32 h);
s32 func_002032C8(s32 x);
void func_0012FFE8(StreamReader* self);

void func_001830D8(void);

void func_00182C58(void* self);
void func_0012C208(void* self);
void func_001DBC60(void* host, void* cb, void* ctx, s32 a3, s32 a4);

s32 func_0012C7B0(void* self, s32 a1, s32 a2, s32* out, f32 fa, f32 fb);

struct Obj_0012C208 {
    u8 pad0[0x14];
    void* host;
    u8 pad1[0x28];
    s32 id;
};

void func_0012C288(void* self, s32 a1, s32 a2, s32 a3, s32 a4, void** out);

struct Node_0012C808 {
    u8 pad0[0xC];
    s32 key;
    u8 pad1[0x2C];
    Node_0012C808* next;
};

struct Owner_0012C808 {
    u8 pad0[0x6C];
    Node_0012C808* head;
};

void* func_0012C808(void* self, s32 key);
s32 func_0012C7B0(void* self, s32 a1, s32 a2, void** out, f32 fa, f32 fb);
void func_0012F0A0(void* obj, s32 a1, f32 fa, f32 fb);

void func_0012C840(void* self, s32 key, s32 a2, s32 a3, void** out, f32 fa, f32 fb);

void func_0012F6B0(AnimationPlayer* self, f32 x);
void func_0012F190(AnimationPlayer* self, s32 zero);
void func_0012F1D8(AnimationPlayer* self);
void func_0012E4E0(AnimationPlayer* self, Animation* sub, s32* out);
void func_0012E760(AnimationPlayer* self);
void func_0012D4A8(AnimationPlayer* self);

struct Item_0012F1D8 { u8 pad[0x20]; Item_0012F1D8* next; };

void func_001226D8(Item_0012F1D8* item);

void func_00152600(u8* a, void* b);
void func_001B5F28(u8* a, void* b);

Attachment* func_0012D570(void* a0, void* a1);

struct Node_12F718 {
    u8 pad0[4];
    void* data4;
    u8 pad8[0xC];
    s32 value14;
    u8 pad18[8];
    Node_12F718* next;
};

struct Owner_12F718 {
    u8 pad0[0x44];
    Node_12F718* head;
};

void func_00129A58(void* p);

struct Obj_12F760 {
    void (**vtbl)(void* self);
};

void* func_0012CBE8(void);

void func_001831E8(void* a, void* b, void* c, void* d);

void func_001B9AE0(Collider* self, s32 a, Vec02* b, s32 c, Vec02* d);

void func_001BA130(Collider* self);
void func_00138F28(void* a, void* b);

s32 func_001F92E8(s32 a, s32 b, s32* c);
s32 func_00203D90(void);

void func_0018D778(void* self);

s32 func_0012FDA0(void* self, s32 a, s32 b);

void func_001DDA20(void* a);
void func_001DDA50(void* a);

void func_0012E760(void* obj);
s32 func_0012C7B0(void* self, void* a1, f32 fa, f32 fb, void* a2, void** out);

s32 func_001833F0(void* a, s32 b);

struct Entry_12CCE8 { s32 key; u8 pad[0x18]; };

s32 func_001B8A08(Collider* self, Collider* key);
s32 func_001300E8(void* key, s32 kind);

void func_0012FE70(StreamReader *self);

s32 func_0012FF20(StreamReader* a0);

struct Head_2197B8 { const void* tinfo; s32 f4; };
extern const Head_2197B8 D_002197B8;
void* func_001B5EE0(Pool6C* pool);
void func_00152438(List01* self, s32 value);

struct Quad_12F9B8 { s32 a, b, c, d; };

void func_00128018(void* a, s32 b, void* c, void* d);

struct Item_12E760 { s32 w[4]; };
struct Vt_12E760 { void* pad[2]; void (*fn8)(void* self, s32 a); };
struct Elem_12E760 { Vt_12E760* vt; };
struct Frame_12E760 { s32 f00; s32 f04; s32 f08; s32 f0C; };
struct Tmp_12E760 { s32 a; s32 b; };

void func_0012D5D0(AnimationPlayer* self, Item_12E760* item, Tmp_12E760* out);
void func_0012F760(AnimationPlayer* self, s32 a, AnimationPlayer* b);
void func_001DBC18(u8* self, void* node);
void func_0015F9A0(u8* a, u8* s);
void func_0012D448(AnimationPlayer* self, s32 v);
void func_001DBD40(u8* a, s32 b, s32 c, AnimationPlayer* d, s32 e, s32 f);
void func_00152600(u8* a, AnimationPlayer* b);
void func_00152470(u8* a, AnimationPlayer* b);
void func_001BF718(s32* slot);
void func_001837E0(Animation* self, s32 a, s32 b, s32* c);

f32 func_002058A0(f32 a, f32 b);
f32 func_001EAFE0(f32 a, f32 b);

void func_001F5B08(Track83* dst, Track83* src, s32 bytes);

struct Item_12E4E0 { f32 t; s32 type; s32 w2; s32 w3; };
void func_0012D5D0(AnimationPlayer* self, Item_12E4E0* item, s32* out);

// was NEAR: call result is stored directly (retail copies v0 to v1 first, then s1=v1 for the out pointer); 5 lines differ

struct Entry_12D1B0 { s32 f0; s32 type; s32 f8; s32 fC; };
struct Obj_12D1B0 {
    u8 pad0[0x14];
    void* host;
    u8 pad1[0x5C - 0x18];
    s32 count;
    Entry_12D1B0* items;
};

void* func_0018D658(s32 size);

struct World_12D5D0;
struct VObj_12D5D0 {
    void** vt;
};
struct Msg_12D5D0 {
    union {
        f32 f;
        s32 i;
    } a0;
    s32 kind;
    union {
        s32 i;
        f32 f;
        void* p;
        struct {
            s16 lo;
            s16 hi;
        } h;
    } a8;
    union {
        s32 i;
        f32 f;
        struct {
            s16 lo;
            s16 hi;
        } h;
    } aC;
};
struct Seq_12D5D0 {
    s16 count;
    s16 ids[6];
    s16 cur;
    s16 target;
    u8 pad12[2];
    s32 f14;
    s32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
};
struct Ent_12D5D0 {
    u8 pad0[4];
    VObj_12D5D0* f4;
    VObj_12D5D0* f8;
    s32 fC;
    u8 pad10[0x18 - 0x10];
    s32 f18;
};
struct Owner_12D5D0 {
    u8 pad0[0x14];
    World_12D5D0* world;
    void* f18;
    u8 pad1C[0x34 - 0x1C];
    f32 f34;
    u8 pad38[0x3C - 0x38];
    Ent_12D5D0* ents;
    u8 pad40[0x5C - 0x40];
    s32 nmsgs;
    Msg_12D5D0* msgs;
};
struct Info_12D5D0 {
    s32 f0;
    s32 f4;
    s32 f8;
    f32 fC;
};
struct Req_12D5D0 {
    s32 flags;
    void* f4;
    u8 pad8[0x20 - 0x8];
    Vec4U buf;
    f32 f30;
    u8 pad34[4];
    void* f38;
    u8 pad3C[0x50 - 0x3C];
};
union Scratch_12D5D0 {
    Req_12D5D0 req;
    Vec4U v[3];
    void* p[3];
    s32 w[3];
};
struct __attribute__((packed)) Word_12D5D0 { s32 v; };

typedef void (*VFn_12D5D0)(void* self);
typedef void (*VFnI_12D5D0)(void* self, s32 a);
typedef void (*VFnP_12D5D0)(void* self, void* a);
typedef void (*VFnIP_12D5D0)(void* self, s32 a, void* b);
typedef void (*VFnAim_12D5D0)(void* self, void* obj, s32 a, Vec4U* b, Vec4U* c, f32 x, f32 y);

extern u8 D_00275F80[];
extern u8 D_0026E760[];
extern u8 D_00262C70[];
extern u8 D_00269A00[];
extern VObj_12D5D0 D_00272E08;
extern u8 D_00275BC0[];

s32 func_001BE810(void);
void func_001BE728(void* p);
void func_001BE998(void);
s32 func_001EAA70(s32 lo, s32 hi);
s32 func_001BE568(s32 id);
void func_001BFCD8(s32 id, VObj_12D5D0** handle, Collider* target, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_001BF788(VObj_12D5D0* h, s32 n);
void func_001BED20(void);
void func_001BECF8(void);
void func_001518B8(Collider* t);
s32 func_00126CB8(Collider* t, f32 v);
s32 func_00126D60(Collider* t, f32 v);
void func_001B9AE0(Collider* t, s32 a, s32 b, s32 c, s32 d);
void func_001F4ED0(Collider* t);
void func_001F4F20(Collider* t);
void func_00177800(Player* g, s32 flag);
void func_0012F190(AnimationPlayer* self, s32 v);
// the node keeps the inline setter of its second mode byte that retail's code calls (see NOTES.md)
struct Node_12D5D0 : T2195_7C0 {
    void SetMode(s32 mode) { mode1 = mode; }
};
Node_12D5D0* func_0012D570(AnimationPlayer* self, s32 key);
void func_001215C0(Node_12D5D0* n);
void func_001EFFA0(u8* dst, s32 a, s32 b);
void func_001F00C0(u8* dst, s32 a, s32 b);
void func_001F4408(s32 a, s32 b);
void func_001AB890(u8* p, f32 x);
void func_001AB938(u8* p);
void func_001AB958(u8* p);
s32 func_0012C7B0(Collider* a, Collider* b, s32 c, s32 d, f32 x, f32 y);
void func_0016EC38(u8* p, s32 n, f32 f);
void func_001837E0(void* self, s32 a, s32 b, void* c);
void func_0012F760(AnimationPlayer* self, s32 a, void* b);
void func_0012B2F8(Collider* t, s32 key);
void* func_001B6388(Collider* a, Collider* b);
void* func_001B6290(Collider* a, Collider* b, s32 c, s32 d);
void func_001B6438(void* o);
s32 func_001300E8(Collider* n, s32 kind);
void func_001920B0(Collider* n, Vec4U* out);
s32 func_001F3BD8(Collider* n, Vec4U* out);
s32 func_00182FC8(void* p);
void func_001DDB58(World_12D5D0* w);
void func_001DDBB8(World_12D5D0* w);
void func_0018F0E8(u8* a, s32 b);
void func_0014AEA0(VObj_12D5D0* self, s32 n, f32 x, f32 y);
void func_0014AF10(VObj_12D5D0* self);
void func_0014AF38(VObj_12D5D0* self, s32 a, s32 b, f32 x);
void func_001E96F8(u8* obj, s32 mode);
void func_001DDAB8(World_12D5D0* w, f32 v);
void func_001DDAC8(World_12D5D0* w, f32 v);
void func_0017CE20(Collider* t, Player* g);

struct Clamp_12D5D0 {
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        if (x < lo) {
            return lo;
        }
        if (hi < x) {
            return hi;
        }
        return x;
    }
};

struct Range_12E968 { u32 field0; f32 minimum; f32 maximum; };
struct Obj_12E968 { u8 pad0[8]; Range_12E968* range; };

s32 func_001F8DB8(void* p, s32 a, s32 b);
void func_00140CC8(void* p, s32 n, s32 base);

struct Key_12D4A8 {
    f32 time;
    u8 pad[12];
};

struct Rec_12CBE8 {
    u32 f0;
    s32 f4;
    s32 f8;
    u32 fC;
};

struct Obj_12CBE8 {
    u8 pad0[0x54];
    s32 f54;
    Rec_12CBE8* f58;
    s32 f5C;
    Rec_12CBE8* f60;
    s32 f64;
    Rec_12CBE8* f68;
};

struct Iter_12F8C8 { List01* list; u8* link; s32 offset; Iter_12F8C8* saved; };

struct Next_12F8C8 {
    static PlacedObject* Of(Iter_12F8C8* it)
    {
        PlacedObject* obj = *(PlacedObject**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_12F8C8 {
    static void Of(Iter_12F8C8* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = ((Iter_12F8C8*)D_0027B314);
        D_0027B314 = (ListFrame*)it;
    }
};

void func_00124A48(PlacedObject* self);
s32 func_001300E8(void* n, s32 kind);

struct Entry_12E5D0 {
    f32 key;
    s32 a4;
    s32 a8;
    s32 aC;
};

void func_0012D5D0(AnimationPlayer* self, Entry_12E5D0* entry, s32* out);

// kept: the bitfields make `n->f10 = n->f11 = 3` store from two registers, as retail does
struct Node_12C288 {
    u8 pad0[0x10]; s32 f10 : 8; s32 f11 : 8; s32 f12 : 8; s32 f13 : 8; s32 f14;
    u8 pad1[0x1C - 0x18]; AnimationPlayer* f1C;
    u8 pad2[0x28 - 0x20]; s32 f28;
};
struct Item_12C288 { u8 pad[0x10]; };

void func_00152470(u8* list, AnimationPlayer* o);
void func_00152470(u8* list, Node_12C288* n);
void func_0018D608(void);
Node_12C288* func_00128998(PlacedObject* h);
void func_001B5F28(u8* list, Node_12C288* n);
void func_001215C0(Node_12C288* n);
void func_001299E0(PlacedObject* h, Node_12C288* n);
void func_0018D6F0(void);
void func_0015F8B0(World* w, u8* p);
void func_0012D5D0(AnimationPlayer* o, Item_12C288* item, s32* out);
void func_0012F190(AnimationPlayer* o, s32 flag);
void func_001837E0(Animation* self, s32 a, s32 b, AnimationPlayer*** c);

void func_00130B48(s32 a, s32 b, s32 c, s32 d, f32 x, f32 y, f32 z, s32 n, void* buf);
void func_0014D0A8(s32 n, void* buf, s32 zero);

struct Quad_130F48 {
    f32 c0, c1, c2, c3;
} __attribute__((aligned(16)));

typedef void (*VFn_131140)(void* self, s32 arg);

void func_001365A0(void* self, s32 arg);

void func_0012FE70(void* self);
void func_0012FFE8(void* self);

extern u8 D_00259F38[];
void* func_0011BF30(void);
void func_0011A708(void* dst, void* value);

struct Inner_130158 { s32 pad0; s32 value; };
struct Holder_130158 { Inner_130158* inner; };

struct Rgba_133B58
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    Rgba_133B58() {}
    Rgba_133B58(const Rgba_133B58& o) { *this = o; }
};
struct Gs_133B58;
struct Span_133B58;

extern Rgba_133B58 D_002610E0;
extern Rgba_133B58 D_002610D8;
extern Span_133B58 D_00261280;
extern Span_133B58 D_002612B0;

f32 func_00205210(f32 x);
f32 func_00131000(Span_133B58* s, s32 x);
void func_001613C0(Gs_133B58* gs, s32 a, s32 b, s32 c);
void func_00161458(Gs_133B58* gs, u32 c);
void func_00161670(Gs_133B58* gs, s32 x, s32 y, s32 a3, s32 a4);
void func_001615F0(Gs_133B58* gs, s32 x, s32 y, s32 a3, s32 a4);

struct Lerp_133B58
{
    static s32 Channel(s32 a, s32 b, f32 t)
    {
        if (a == b)
        {
            return b;
        }
        if (a < b)
        {
            return a + (s32)(t * ((f32)b + 0.999f - (f32)a));
        }
        return b + (s32)((1.0f - t) * ((f32)a + 0.999f - (f32)b));
    }

    static Rgba_133B58 Mix(Rgba_133B58 a, Rgba_133B58 b, f32 t)
    {
        Rgba_133B58 c;
        c.r = Channel(a.r, b.r, t);
        c.g = Channel(a.g, b.g, t);
        c.b = Channel(a.b, b.b, t);
        c.a = Channel(a.a, b.a, t);
        return c;
    }
};

struct Self_130B48;
struct Out_130B48 { u8 pad0[16]; };

void func_00130540(f32 f12, Self_130B48* a, u8* b, u8* c, u8* d, f32 f13, f32 f14, s32 a4, s32 a5, s32 a6);

void func_001233C0(C22* object)
{
	if (!object->hold)
		func_00123B18(object->counter);
	func_0013D278(object);
}

void func_00123400(C22* state, StateTrigger* value)
{
    state->counter = value;
}

void func_00123408(StateTrigger* self)
{
    InitCollider(self);
    self->state = -1;
    self->id6B0 = TakeFlagTableIndex(g_flagTable);
}

void func_00123448(StateTrigger* self)
{
    Frame_123448 fr;
    s32 s0;
    AppendQueuedCall(self->world, (void*)ResolveStateTriggerObjects, self, 0, 0);
    StartPlacedObject(self);
    s32 e = (s32)&self->children;
    fr.f04 = e;
    fr.f00 = e;
    s32 link = *(s32*)(e + 8);
    s32 old = (s32)g_activeListFrames;
    fr.f0C = old;
    fr.f08 = link;
    g_activeListFrames = (ListFrame*)&fr;
    s32 head = *(s32*)e;
    fr.f04 = head + fr.f08;
    s0 = head;
    if (s0 != 0) {
        do {
            if (IsObjectOfKind((void*)s0, 0x88) != 0) {
                if (self->found558 == 0) {
                    self->found558 = (void*)s0;
                }
            }
            s32 nx = *(s32*)fr.f04;
            fr.f04 = nx + fr.f08;
            s0 = nx;
        } while (s0 != 0);
    }
    if (self->found558 != 0) {
        self->f55C = (StateWalker*)CreateStateWalker(self->found558, self, -1, 1);
        func_00182ED8(self->found558);
    }
    g_activeListFrames = (ListFrame*)fr.f0C;
}

void func_00123540(StateTrigger* object)
{
	s32 value = object->id6B0;
	CopyCollider(object);
	object->id6B0 = value;
}

void func_00123578(StateTrigger* self)
{
    UpdateCollider(self);
    if (self->state == 2 && self->timeout != 0.0f) {
        if (self->timeout < g_gameTime[0] - self->stateTime) {
            SetStateTriggerState(self, 0);
            goto done;
        }
    }
    if (self->count1 > 0) {
        if (self->done == self->count1) {
            SetStateTriggerState(self, 1);
            goto done;
        }
    }
    if (self->state != 2) {
        goto done;
    }
    if (g_player->f2220 != 9) {
        goto done;
    }
    for (s32 i = 0; i < self->count1; i++) {
        void* p = FindFirstObjectById(self->world, 0x104, self->items1[i], self);
        if (p != 0 && IsObjectOfKind(p, 0x22) != 0) {
            Obj_123578* o = (Obj_123578*)p;
            o->vtbl[0x130 / 4](p);
        }
    }
done:
    ;
}

void func_001236C8(StateTrigger* self)
{
    s32 kept = 0;
    s32 i;
    for (i = 0; i < self->count1; i++) {
        void* node = FindFirstObjectById(self->world, 0x104, self->items1[i], self);
        if (node && IsObjectOfKind(node, 0x22)) {
            SetCountedObjectCounter((C22*)node, self);
            kept++;
        }
    }
    self->count1 = kept;
    for (i = 0; i < self->count2; i++) {
        void* node = FindFirstObjectById(self->world, 0x104, self->items2[i], self);
        if (node && IsObjectOfKind(node, 0x30)) {
            s32 idx = self->outCount;
            self->outItems[idx] = (Collider*)node;
            self->outCount = idx + 1;
            ((Obj_1236C8*)node)->vt[0x140 / 4](node, self);
        }
    }
    for (i = 0; i < self->count3; i++) {
        void* node = FindFirstObjectById(self->world, 0x104, self->items3[i], self);
        if (node && IsObjectOfKind(node, 8)) {
            func_001CAD40(node, self);
        }
    }
    if (TestFlagTableBit(g_flagTable, self->id6B0)) {
        SetStateTriggerState(self, 1);
    } else {
        SetStateTriggerState(self, 0);
    }
}

void func_00123888(StateTrigger* self, s32 mode)
{
    s32 cur = self->state;
    if (cur == mode) {
        return;
    }
    if (cur < 0) {
        goto store;
    }
    if (cur < 2) {
        goto store;
    }
    if (cur != 2) {
        goto store;
    }
    StopSoundRecord(self->f620, 0);
    ReleaseSoundLevel(self->f624);
    func_0013ECB0(self->world, self->count62C, self->table630, self, 0);
    if (mode == 1) {
        func_00160D00(D_002623D8);
    }
store:
    self->state = mode;
    self->stateTime = g_gameTime[0];
    if (mode == 1) {
        goto arm1;
    }
    if (mode < 2) {
        if (mode == 0) {
            goto arm0;
        }
        return;
    }
    if (mode == 2) {
        goto arm2;
    }
    return;
arm0:
    if (self->f55C != 0) {
        SetStateWalkerTarget(self->f55C, 0x21A);
    }
    func_00123B28(self);
    return;
arm1:
    if (self->f55C != 0) {
        TeleportStateWalker(self->f55C, 0x220);
    }
    func_00123BB0(self);
    if (TestFlagTableBit(g_flagTable, self->id6B0) != 0) {
        TriggerScriptEvent(self, 0x16, 0, 0);
    } else {
        TriggerScriptEvent(self, 3, 0, 0);
    }
    SetFlagTableBit(g_flagTable, self->id6B0);
    return;
arm2:
    if (self->f55C != 0) {
        SetStateWalkerTarget(self->f55C, 0x21F);
    }
    if (self->f628 == 0) {
        StartSoundEffect(0x15, &self->f620, self, 0, 8000.0f, 5000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
    self->f624 = PushSoundLevel(0x6B);
    func_00123C20(self);
    func_0013ECB0(self->world, self->count62C, self->table630, self, 1);
    TriggerScriptEvent(self, 2, 0, 0);
    func_00160CF0(D_002623D8);
}

void func_00123AB0(StateTrigger* object, s32 mode)
{
    s32 mapped;
    switch (mode) {
    case 0: mapped = 2; break;
    case 1: mapped = 0; break;
    case 2: mapped = 1; break;
    default: return;
    }
    SetStateTriggerState(object, mapped);
}

void func_00123B18(StateTrigger* counter)
{
	counter->done++;
}

void func_00123B28(StateTrigger* self)
{
    for (s32 i = 0; i < self->outCount; i++) {
        Elem_123B28* e = (Elem_123B28*)self->outItems[i];
        if (e->f560 == -1 && e->vt->f134 != 0) {
            e->vt->f134(e, 0);
        }
    }
}

void func_00123BB0(StateTrigger* self)
{
    s32 i;
    for (i = 0; i < self->outCount; i++) {
        Child_00123BB0* c = (Child_00123BB0*)self->outItems[i];
        void* fn = c->vt[0x138 / 4];
        if (fn != 0) {
            ((void (*)(void*))fn)(c);
        }
    }
}

void func_00123C20(StateTrigger* self)
{
    s32 i;
    for (i = 0; i < self->outCount; i++) {
        Item_123C20* it = (Item_123C20*)self->outItems[i];
        VFn_123C20 fn = it->vtbl[79];
        if (fn != 0) {
            fn(it);
        }
    }
}

void func_00123C90(StateTrigger* self, s32 value)
{
    u32 n = self->count1;
    if (n < 4) {
        self->items1[n] = value;
        self->count1 = n + 1;
    }
}

void func_00123CB8(StateTrigger* self, s32 value)
{
    u32 n = self->count2;
    if (n < 16) {
        self->items2[n] = value;
        self->count2 = n + 1;
    }
}

void func_00123CE0(StateTrigger* self, s32 value)
{
    u32 n = self->count3;
    if (n < 6) {
        self->items3[n] = value;
        self->count3 = n + 1;
    }
}

void func_00123D08(StateTrigger* object, void* a1, void* a2, void* a3, void* a4)
{
	UpsertKeyedEntry((u8*)object + 0x630, 8, (u8*)object + 0x62C,
			  a1, a2, a3, a4);
}

s32 func_00123D40(StateTrigger* self, void* arg)
{
    s32 i;
    for (i = 0; i < self->outCount; i++) {
        if (AppendPropertyToScriptList(arg, &self->outItems[i]) == 0) {
            return 0;
        }
    }
    return 1;
}

ASM_FUNC(func_00123DC0);

ASM_FUNC(func_00123E00);

ASM_FUNC(func_00123E48);

ASM_FUNC(func_00123E88);

void func_00123ED0(PlacedObject* self)
{
    SetListLinkOffset(&self->children, 0x1C);
    SetListLinkOffset(&self->list60, 0x58);
    if (self->parent != 0) {
        self->bits24 = 1;
        self->bits26 = 0;
    } else {
        self->bits24 = 2;
        self->bits26 = 2;
    }
    InitObject(self);
    self->f80 = 3.4028235e+38f;
    self->f88 = 0x0FFFFFFF;
    self->f84 = 3.4028235e+38f;
    Init_00123ED0::SetB2CA(self, -1);
    self->b2C9 = -1;
    self->p20C = (u8*)D_00260E70;
    self->p210 = (u8*)D_00260E80;
    self->p214 = (u8*)D_00260E90;
    self->p218 = (u8*)D_00260EA0;
    self->p21C = (u8*)D_00260EB0;
    self->p220 = (u8*)D_00260EC0;
    self->b2C8 = 0;
    Init_00123ED0::Copy(&self->rot, &g_identityMatrix);
    Init_00123ED0::Copy(&self->m110, &g_identityMatrix);
    Init_00123ED0::Copy(&self->m1A0, &g_identityMatrix);
    SetListLinkOffset(&self->list1E0, 8);
}

void func_00124050(PlacedObject* self)
{
    Iter_00124050 it;
    Begin_00124050::Of(&it, &self->children);
    self->desc->m06(self);
    BaseObject* obj;
    while ((obj = Next_00124050::Of(&it)) != 0) {
        obj->desc->m04(obj);
    }
    self->desc->m0E(self, 1, self);
    g_activeListFrames = (ListFrame*)it.saved;
}

void func_001240F8(PlacedObject* self)
{
    Vec02 v0;
    Vec02 v1;
    Mat02 rot;
    RegisterObject(self);
    World* ctx = self->world;
    if (!self->parent) {
        self->root = self;
        if (self->f294) {
            AppendToList(&ctx->list78, self);
        } else {
            AppendToList(&ctx->list54, self);
            self->flags |= 0x2000000000ULL;
            AppendToList(&ctx->list60, self);
            if (self->desc->flags & 2) AppendToList(&ctx->list6C, self);
            s32 n = self->count6C;
            self->f54 = self;
            self->list60.tail = self;
            n--;
            self->list60.head = self;
            for (; n >= 0; n--) MergeObjectGroupMembers(ctx, self->items70[n]);
        }
    } else {
        self->root = ((PlacedObject*)self->parent)->root;
        if (((PlacedObject*)self->parent)->flags & 0x4000000000ULL) {
            if (self->desc->m14) self->desc->m14(self, 1);
        }
    }
    if (self->f1EC) {
        self->f1EC->vt->getPos(self->f1EC, 0.0f, &v0, &v1);
        self->desc02()->m1D(self, &v0);
        self->desc02()->m20(self, &v1);
    }
    if (self->f1F0) {
        self->f1F0->vt->getRot(self->f1F0, 0.0f, &rot, &v0);
        self->desc02()->m1E(self, &rot);
        self->desc02()->m21(self, &v0);
    }
    if (self->flags & 0x1000000000ULL) AddCameraObject((PlacedObject*)g_camera, self);
    if (self->f284) AppendToList(&self->world->list1C00, self->f284);
    if (self->desc->m12) self->desc->m12(self);
    TriggerScriptEvent(self, 4, 0, 0);
    func_00129DF8(self);
}

void func_00124338(PlacedObject* self)
{
    Iter_00124338 it;
    Begin_00124338::Of(&it, &self->children);
    self->desc->m07(self);
    BaseObject* obj;
    while ((obj = Next_00124338::Of(&it)) != 0) {
        obj->desc->m05(obj);
    }
    self->desc->m0E(self, 2, self);
    g_activeListFrames = (ListFrame*)it.saved;
}

void func_001243E0(PlacedObject* self)
{
    UnregisterObject(self);
    World* s1 = self->world;
    if (self->parent == 0) {
        if (self->f294 != 0) {
            RemoveFromList(&s1->list78, self);
        } else {
            RemoveFromList(&s1->list54, self);
            u64 fl = self->flags;
            if ((fl & (1ull << 37)) != 0) {
                self->flags = fl & ~(1ull << 37);
                RemoveFromList(&s1->list60, self);
                if ((self->desc->flags & 2) != 0) {
                    RemoveFromList(&s1->list6C, self);
                }
            }
            DissolveObjectLinkList(s1, self->f54);
            self->f54 = 0;
            ClearList(&self->list60);
        }
    }
    if ((self->flags & (1ull << 36)) != 0) {
        RemoveCameraObject(g_camera, self);
    }
    if (self->f284 != 0) {
        RemoveFromList(&self->world->list1C00, self->f284);
    }
    if ((self->flags & (1ull << 38)) != 0) {
        void (*fn)(BaseObject* self, s32 on) = self->desc->m14;
        if (fn != 0) {
            fn(self, 0);
        }
    }
    func_00129DF8(self);
    self->root = 0;
    TriggerScriptEvent(self, 5, 0, 0);
}

void func_00124540(PlacedObject* object)
{
	object->v190 = object->pos;
	object->m1A0.r[0] = object->rot.r[0];
	object->m1A0.r[1] = object->rot.r[1];
	object->m1A0.r[2] = object->rot.r[2];
	object->desc02()->m2A(object, &object->m1A0);
	MatrixToEulerAngles(&object->m1A0, &object->v1D0);
}

ASM_FUNC(func_001245A8);

ASM_FUNC(func_00124868);

void func_001249A8(PlacedObject* self)
{
    ListFrame frame;
    ResolveFollowRecordObjects(self);
    SavePlacedObjectInitialFrame(self);
    Sub_1249A8* sub = (Sub_1249A8*)self->f200;
    if (sub != 0 && sub->f20 != -1) {
        void* v = FindFirstObjectByIdMode4(self->world, sub->f20, self);
        if (v != 0) {
            SetAimTarget(self, v);
        }
    }
    BindAttachmentTargets(self->sub22C, self);
    for (BaseObject* p = (BaseObject*)self->children.head; p != 0; p = p->next) {
        void (*fn)(BaseObject* self) = p->desc->m0F;
        if (fn != 0) {
            fn(p);
        }
    }
}

void func_00124A48(PlacedObject* self)
{
    Frame_124A48 fr;
    Key02* k;
    BaseObject* s0;
    s32 old = (s32)g_activeListFrames;
    s32 e = (s32)&self->children;
    fr.f00 = e;
    fr.f04 = e;
    fr.f08 = *(s32*)(e + 8);
    fr.f0C = old;
    g_activeListFrames = (ListFrame*)&fr;
    StartObject(self);
    if (self->f2A0 != 0) {
        if (((Pair_124A48*)self->f2A0)->a != 0 || ((Pair_124A48*)self->f2A0)->b != -1) {
            AppendQueuedCall(self->world, (void*)StartAnimationFromContext, self, 0, 0);
        }
    }
    StartAttachments(self->sub22C, self);
    if (self->f284 != 0) {
        if (func_001B1D38(self->f284) == 0) {
            func_001B1D70(self->f284, self->f2A8);
            func_001B1DA8(self->f284, self->f2A8 * 0.5f);
        }
        if ((self->f284)->fB0 != -1) {
            (self->f284)->fB4 = FindFirstObjectByIdMode4(self->world, (self->f284)->fB0, self);
            if ((self->f284)->fB4 != 0) {
                BuildTexturePackets((self->f284)->fB4, self->f284);
            }
        }
        func_001B1B38(self->f284);
    }
    if (self->f2AC != 0) {
        if (self->f2AC->f00 == -1) {
            self->f2AC = 0;
        }
        if (self->f2AC != 0) {
            SoundRecord* q = self->f2AC;
            StartSoundEffect(q->f00, q->f04, q->f08, q->f0C, q->f10, q->f20, &q->f1C, self, 0, q->b14, 0);
        }
    }
    if (self->f26C != 0) {
        self->f1F8 = (void**)AllocateZeroedFrontMemory(self->f26C << 2);
    }
    for (k = self->keys; k != 0; k = k->next) {
        if (MatchesObjectId(self, k->key) != 0) {
            s0 = self;
        } else {
            s0 = (BaseObject*)FindFirstObjectById(self->world, 1, k->key, self);
            if (s0 == 0) {
                continue;
            }
        }
        if (IsObjectAttached(s0) != 0 && s0 != self) {
            s0->desc->m10(s0);
        }
        s0->desc->m03(s0);
    }
    self->keys = 0;
    {
        s32 head = *(s32*)fr.f04;
        s32 p;
        fr.f04 = head + fr.f08;
        p = head;
        while (p != 0) {
            ((BaseObject*)p)->desc->m10((BaseObject*)p);
            s32 nx = *(s32*)fr.f04;
            fr.f04 = nx + fr.f08;
            p = nx;
        }
    }
    g_activeListFrames = (ListFrame*)fr.f0C;
}

void func_00124CC0(PlacedObject* self)
{
    Ctx_124CC0* ctx = (Ctx_124CC0*)self->f2A0;
    Animation* node = Find_124CC0::Of(self, ctx);
    if (node == 0) {
        return;
    }
    Frame_124CC0 fr;
    switch (ctx->mode) {
    case 0:
        fr.tmp = ctx->value;
        break;
    case 1:
        fr.tmp = Clamp_124CC0::Of(ctx->value, 0.0f, 1.0f) * node->length;
        break;
    case 2:
        func_0012C9E8(node, self, 0.0f, (u8*)self + 0x100, &fr.tmp, 0, 0);
        break;
    default:
        return;
    }
    fr.key = node->id;
    fr.object = self;
    CreateAnimationPlayer(node, self, 1, &fr, fr.tmp, ctx->f10, 0, 0);
}

void func_00124DF8(BaseObject* self, s32 count, ObjectLink* item)
{
    World* host = self->world;
    if (count <= 0) {
        return;
    }
    ObjectLink* it = item;
    s32 n = count;
    do {
        u32 f = it->flags;
        s32 kind = (f & 1) ? 5 : 1;
        if (f & 0x20) {
            kind |= 0x100;
        }
        void* node = FindFirstObjectById(host, kind, it->id, self);
        if (node) {
            if (!(it->flags & 8)) {
                *(void**)((u8*)self + it->offset) = node;
            }
            if (!(it->flags & 4)) {
                func_00182ED8(node);
            }
            if (it->flags & 0x10) {
                AddObjectListener(node, self);
            }
        }
        n--;
        it++;
    } while (n != 0);
}

void func_00124EE8(void* self, f32 f)
{
    Obj_124EE8* obj = (Obj_124EE8*)self;
    Frame_124EE8 fr;
    f32 saved = f;
    VFn0_124EE8 pre = (VFn0_124EE8)obj->vt[21];
    if (pre != 0) {
        pre(self);
    }
    if (IsObjectAttached(self) == 0) {
        return;
    }
    s32 e = (s32)&obj->list;
    fr.list = e;
    fr.cursor = e;
    s32 old = *(s32*)&g_activeListFrames;
    s32 link = *(s32*)(e + 8);
    fr.prev = old;
    fr.link = link;
    *(s32*)&g_activeListFrames = (s32)&fr;
    s32 head = obj->list.head;
    fr.cursor = head + fr.link;
    Node_124EE8* node = (Node_124EE8*)head;
    while (node != 0) {
        if ((node->info->flags & 1) != 0) {
            func_00124EE8(node, saved);
        }
        s32 nx = *(s32*)fr.cursor;
        fr.cursor = nx + fr.link;
        node = (Node_124EE8*)nx;
    }
    *(s32*)&g_activeListFrames = fr.prev;
}

void func_00124FC0(PlacedObject* self, f32 f)
{
    UpdateAttachments(self->sub22C, self, f);
    if (self->f284 != 0) {
        func_001B2140(self->f284, f);
    }
    if (self->f288 != 0) {
        func_00126AC8(self, f);
    }
    Iter_124FC0 it;
    Begin_124FC0::Of(&it, &self->list1E0);
    Object_124FC0* obj;
    while ((obj = Next_124FC0::Of(&it)) != 0) {
        if (obj->vtable->update != 0) {
            obj->vtable->update(obj, f);
        }
    }
    g_activeListFrames = (ListFrame*)it.saved;
    void* args[1];
    args[0] = &f;
    TriggerScriptEvent(self, 1, 1, args);
}

void func_001250C8(PlacedObject* records)
{
    for (s32 i = 0; i < *(s32*)(records->sub22C + 0xC); i++) {
        Record_001250C8* record = (Record_001250C8*)(*(u8**)(records->sub22C + 0x14) + i * 0x28);
        record->value = -1;
    }
}

void func_00125108(PlacedObject* self)
{
    void (*fn)(BaseObject* self) = self->desc->m13;
    if (fn != 0) {
        fn(self);
    }
}

ASM_FUNC(func_00125138);

void func_00125438(PlacedObject* self)
{
    (void)self;
}

ASM_FUNC(func_00125440);

ASM_FUNC(func_00125750);

ASM_FUNC(func_001259D8);

void func_00125B70(PlacedObject* self, Quad_00125B70* src, Dst_00125B70* dst)
{
    if (src != 0) {
        if (src != (Quad_00125B70*)dst) {
            *dst = *(Dst_00125B70*)src;
        }
    } else {
        BuildScaledTransformMatrix(&self->v140, &self->m110, D_00248D40, dst);
        dst->f44 = 1.0f;
        dst->f40 = 1.0f;
    }
}

ASM_FUNC(func_00125BF0);

ASM_FUNC(func_00125C90);

void func_001261C0(PlacedObject* self, void* b, void* m)
{
    Quad_1261C0* src = (Quad_1261C0*)m;
    self->desc02()->m2C(self);
    Inner_1261C0* in = (Inner_1261C0*)self->f224;
    if (in != 0 && (in->fB0 & 0x80) != 0) {
        if (src != 0) {
            in->fA4 = 1;
            Inner_1261C0* p = (Inner_1261C0*)self->f224;
            p->q60[0] = src[0];
            p->q60[1] = src[1];
            p->q60[2] = src[2];
            p->q60[3] = src[3];
        } else {
            in->fA4 = 0;
        }
    }
    self->desc02()->m26(self, b, src);
}

INCLUDE_RODATA(D_002499F4);

INCLUDE_RODATA(jtbl_00249A00);

ASM_FUNC(func_00126270);

ASM_FUNC(func_001268B8);

void func_00126A48(PlacedObject* object, u32 value)
{
    ListFrame frame;
    PlacedObject* child = (PlacedObject*)object->children.head;
    *(u32*)(object->sub22C + 0x3C) = value;
    *(u32*)(object->sub22C + 0x38) |= 2;
    while (child != 0) {
        if ((child->desc->flags & 1) != 0)
            SetObjectTreeRecordValue(child, value);
        child = (PlacedObject*)child->next;
    }
}

void func_00126AB0(PlacedObject* state, u32 value)
{
	*(u32*)(state->sub22C + 0x3C) = value;
	*(u32*)(state->sub22C + 0x38) |= 2;
}

ASM_FUNC(func_00126AC8);

void func_00126BC0(Object_00126BC0* object, s32 value)
{
    ListFrame frame;
    for (s32 i = 0; i < object->count; i++) {
        Record_00126BC0* record = (Record_00126BC0*)(object->records + i * 0x70);
        record->type = 2;
        record->value = value;
    }
    Object_00126BC0* child = object->child;
    while (child != 0) {
        if ((child->vtable[2] & 1) != 0)
            SetObjectTreeRecordsValue(child, value);
        child = child->next;
    }
}

void func_00126C58(PlacedObject* self)
{
    if (self->f298 == 0) {
        self->f298 = AddObjectNodeToWorld();
        if (IsObjectAttached(self) != 0) {
            ((Sub_126C58*)self->f298)->f4 = 1.0f;
        } else {
            ((Sub_126C58*)self->f298)->f4 = 0.0f;
        }
    }
}

ASM_FUNC(func_00126CB8);

ASM_FUNC(func_00126D60);

ASM_FUNC(func_00126DE8);

void func_00126F78(PlacedObject* self, PlacedObject* owner)
{
    Iter_00126F78 it;
    Begin_00126F78::Of(&it, &owner->children);
    self->desc->m09(self, owner);
    BaseObject* obj = Next_00126F78::Of(&it);
    while (obj != 0) {
        (void)CreateObjectCopy(obj, self->world, self);
        obj = Next_00126F78::Of(&it);
    }
    if ((self->desc->flags & 2) && self->parent == 0) {
        UpdateAnchorModeFlags(self);
    }
    g_activeListFrames = (ListFrame*)it.saved;
}

void func_00127048(PlacedObject* self, PlacedObject* src)
{
    void* s54 = self->f54;
    PlacedObject* s50 = self->root;
    Link02 t48 = self->link48;
    u64 bit = (self->flags >> 37) & 1;
    Link02 t40 = self->link40;
    Link02 t58 = self->link58;
    List01 t60 = self->list60;
    List01 t1E0 = self->list1E0;
    CopyObjectData(self, src);
    CopyAttachmentBlock(self->sub22C, self, src->sub22C);
    if (self->f224) {
        self->f224 = (Rec2195_224*)CopyToFrontMemory(0xC0, self->f224);
    }
    ClearList(&self->children);
    self->link48 = t48;
    self->link40 = t40;
    self->link58 = t58;
    self->list60 = t60;
    self->f54 = s54;
    self->root = s50;
    self->flags = (self->flags & ~(1ULL << 37)) | ((u64)bit << 37);
    self->list1E0 = t1E0;
    self->desc02()->m2B(self);
    if (src->f1FC) {
        self->f1FC = ClonePoseSource(src->f1FC, self->world, self);
        InsertAttachment(self, self->f1FC);
    }
    if (src->f200) {
        self->f200 = ClonePoseSource(src->f200, self->world, self);
        InsertAttachment(self, self->f200);
    }
    if (src->f204) {
        self->f204 = ClonePoseSource(src->f204, self->world, self);
        InsertAttachment(self, self->f204);
    }
    if (src->f284) {
        u8* p = func_001B5EC0(&self->world->pool1BF4);
        CopyMemory(p, src->f284, 0x2E0);
        ClearListLinks(p + 0xB8);
        self->f284 = (RangeRecord*)p;
        AppendToList(&self->world->list1C00, p);
    }
    if (src->f2AC) {
        self->f2AC = (SoundRecord*)CopyToFrontMemory(0x24, src->f2AC);

    }
    if (src->f288) {
        self->f288 = CopyToFrontMemory(0x40, src->f288);
    }
    if (self->flags & (1ULL << 36)) {
        if (IsObjectAttached(self)) {
            AddCameraObject(g_camera, self);
        }
    }
    if (self->p20C != (u8*)D_00260E70) self->p20C = (u8*)CopyToFrontMemory(0x10, self->p20C);
    if (self->p210 != (u8*)D_00260E80) self->p210 = (u8*)CopyToFrontMemory(0x10, self->p210);
    if (self->p214 != (u8*)D_00260E90) self->p214 = (u8*)CopyToFrontMemory(0x10, self->p214);
    if (self->p218 != (u8*)D_00260EA0) self->p218 = (u8*)CopyToFrontMemory(0x10, self->p218);
}

void func_00127378(PlacedObject* self, s32 mode)
{
    if (mode == 1) {
        SoundRecord* s = self->f2AC;
        if (s != 0) {
            if (g_gameTime[0] != 0.0f) {
                if (s->f1C == 0) {
                    StartSoundEffect(s->f00, &s->f1C, self, 0, s->f04, s->f08, s->f0C, s->f10, s->f20, &s->b14, 0);
                }
            }
        }
    }
}

void func_001273F0(PlacedObject* self, Vec02* src)
{
    Frame_1273F0 f;
    f.q = self->v140;
    f.self = self;
    self->pos = *src;
    if (self->desc->m12 != 0) {
        self->desc->m12(self);
    }
    if (self->f1EC != 0) {
        SettlePoseSourceModes(self->f1EC);
    }
    self->desc->m0E(self, 3, &f);
}

LINKER_REMNANT(func_00127468);

void func_00127478(PlacedObject* self, Mat02* src)
{
    self->rot = *src;
    if (self->desc->m12)
        self->desc->m12(self);
    if (self->f1F0)
        SettlePoseSourceModes(self->f1F0);
    self->desc->m0E(self, 4, self);
}

void func_001274F8(PlacedObject* self, Vec02* src)
{
    self->v150 = *src;
    if (self->f1EC != 0) {
        SettlePoseSourceModes(self->f1EC);
    }
    if (func_00123DC0(src) == 0) {
        func_00129DF8(self);
    }
}

void func_00127558(ObjectCycler* self, f32 x, f32 y, f32 z)
{
    Vec3_127558 v;
    v.x = x;
    v.y = y;
    v.z = z;
    self->desc02()->m20(self, (Vec02*)&v);
}

void func_00127590(PlacedObject* self, Vec02* src)
{
    self->v160 = *src;
    if (self->f1F0 != 0) {
        SettlePoseSourceModes(self->f1F0);
    }
    if (func_00123E00(src) == 0) {
        func_00129DF8(self);
    }
}

void func_001275F0(PairedObject* self, f32 x, f32 y, f32 z)
{
    f32 v[3];
    v[0] = x;
    v[1] = y;
    v[2] = z;
    self->desc02()->m21(self, (Vec02*)v);
}

ASM_FUNC(func_00127628);

ASM_FUNC(func_00127678);

void func_001276C0(PlacedObject* self, PlacedObject* other)
{
    Locals_1276C0 L;
    func_00128018(0, self->parent, &other->v140, L.a20);
    func_00128150(0, self->parent, &other->m110, L.a50);
    func_00128330(other->parent, self->parent, &other->v140, &other->v150, &other->v160, 0, 0, L.a30, L.a40, 0, 0);
    self->desc02()->m1D(self, (Vec02*)L.a20);
    self->desc02()->m1E(self, (Mat02*)L.a50);
    self->desc02()->m20(self, (Vec02*)L.a30);
    self->desc02()->m21(self, (Vec02*)L.a40);
    Fl_1276C0* a = (Fl_1276C0*)self->f224;
    if (a != 0 && (a->fB0 & 0x20)) {
        Fl_1276C0* b = (Fl_1276C0*)other->f224;
        if (b != 0 && (b->fB0 & 0x20)) {
            a->f90 = b->f90;
            ((Fl_1276C0*)self->f224)->f94 = ((Fl_1276C0*)other->f224)->f94;
        }
    }
    PlacedObject* n = (PlacedObject*)self->children.head;
    if (n != 0) {
        do {
            if ((n->desc->flags ^ 1) & 1)
                continue;
            PlacedObject* h = (PlacedObject*)FindFirstObjectById(self->world, 2, n->id, other);
            if (h == 0)
                continue;
            if ((h->desc->flags ^ 1) & 1)
                continue;
            if (n->f224 != 0 && (((Fl_1276C0*)n->f224)->fB0 & 0xC))
                continue;
            n->desc02()->m1F(n, h);
        } while ((n = (PlacedObject*)n->next) != 0);
    }
}

ASM_FUNC(func_001278A8);

ASM_FUNC(func_00127B20);

ASM_FUNC(func_00127E60);

ASM_FUNC(func_00128018);

ASM_FUNC(func_001280C0);

ASM_FUNC(func_00128150);

s32 func_00128230(SwitchedCollider *self) {
    Attachment *p = self->f1EC;
    if (p != 0 && p->mode0 == 5) {
        return 1;
    }
    p = self->f1F0;
    if (p != 0) {
        if (p->mode1 == 5) {
            return 1;
        }
    }
    return 0;
}

void func_00128278(Player* self)
{
    Attachment* a = self->f1EC;
    if (a != 0 && a->mode0 == 5) {
        do {
            a->vt->release(a, 0);
            a = self->f1EC;
        } while (a != 0 && a->mode0 == 5);
    }
    Attachment* b = self->f1F0;
    if (b != 0 && b->mode1 == 5) {
        do {
            b->vt->release(b, 0);
            b = self->f1F0;
        } while (b != 0 && b->mode1 == 5);
    }
}

ASM_FUNC(func_00128330);

ASM_FUNC(func_00128598);

s32 func_001288F0(PlacedObject* self, Context_001288F0* context)
{
    Iter_001288F0 it;
    Begin_001288F0::Of(&it, (List_001288F0*)&self->children);
    PlacedObject* obj;
    for (obj = Next_001288F0::Of(&it); obj != 0; obj = Next_001288F0::Of(&it)) {
        if (AppendPropertyToScriptList(context, &obj) == 0) {
            g_activeListFrames = (ListFrame*)it.saved;
            return 0;
        }
    }
    g_activeListFrames = (ListFrame*)it.saved;
    return 1;
}

void func_00128998(BaseObject* item)
{
    CreatePoseSource(item->world, item, (void*)D_002197C0);
}

INCLUDE_RODATA(D_00249A1C);

ASM_FUNC(func_001289C0);

void func_00128C10(PlacedObject* self, void* a1)
{
    s32 flags = ReadBufferedU32(a1);
    if (flags) {
        u8* p = (u8*)AllocateZeroedFrontMemory(0xC0);
        self->f224 = (Rec2195_224*)p;
        *(s32*)(p + 0xB0) = flags;

        u8* q = p + 0x30;
        *(Mat02*)p = g_identityMatrix;
        *(Mat02*)q = g_identityMatrix;
        if (flags & 1) ReadBufferedRotation3(a1, p);
        if (flags & 2) ReadBufferedRotation3(a1, q);
        if (flags & 0xC) {
            s32 r = ReadBufferedS16(a1);
            if (r != -1) {
                *(s32*)(p + 0x60) = (s32)FindFirstObjectById(self->world, 3, r, self);
            }
        }
        if (flags & 0x10) {
            *(s32*)(p + 0x60) = ReadBufferedS16(a1);
        }
        if (flags & 0x20) {
            *(s32*)(p + 0x84) = ReadBufferedS16(a1);
            ReadBufferedVector3(a1, p + 0x60);
            ReadBufferedVector3(a1, p + 0x70);
            f32 f = WrapAngle(ReadBufferedFloat(a1));
            *(s32*)(p + 0x98) = 0;
            *(f32*)(p + 0x8C) = f;
            *(f32*)(p + 0x90) = f;
        }
        if (flags & 0x40) {
            *(s32*)(p + 0x60) = ReadBufferedS16(a1);
            *(s32*)(p + 0x64) = ReadBufferedS16(a1);
        }
        if (flags & 0x80) {
            *(s32*)(p + 0xA0) = ReadBufferedU8(a1);
        }
    }
}

void func_00128DB8(PlacedObject* self)
{
    Part_128DB8* p = (Part_128DB8*)self->f224;
    if (p == 0) return;
    s32 v = p->flags | 0x8000;
    p->flags = v;
    if (v & 0x10) {
        p->p60 = (BaseObject*)FindFirstObjectByIdMode4(self->world, (s32)p->p60, self);
        p->p64 = (BaseObject*)1;
    }
    if (p->flags & 0x20) {
        BaseObject* r = (BaseObject*)FindFirstObjectByIdMode4(self->world, (s32)p->p84, self);
        p->p84 = r;
        s32 x = (s32)r->parent;
        p->f80 = x;
        p->p88 = FindCommonAncestor(self, x);
    }
    if (p->flags & 0x40) {
        p->p60 = (BaseObject*)FindFirstObjectByIdMode4(self->world, (s32)p->p60, self);
        p->p64 = (BaseObject*)FindFirstObjectByIdMode4(self->world, (s32)p->p64, self);
    }
}

ASM_FUNC(func_00128E88);

ASM_FUNC(func_00128FD0);

ASM_FUNC(func_001290B8);

ASM_FUNC(func_001290E0);

Timer_129108* func_00129108(PlacedObject* self)
{
    if (self->f2A0 == 0) {
        Timer_129108* t = (Timer_129108*)AllocateZeroedFrontMemory(0x14);
        self->f2A0 = t;
        t->f4 = -1;
        ((Timer_129108*)self->f2A0)->f8 = 0;
        ((Timer_129108*)self->f2A0)->fC = 0;
        ((Timer_129108*)self->f2A0)->f10 = 1.0f;
    }
    return (Timer_129108*)self->f2A0;
}

void func_00129170(PlacedObject* self, f32 x)
{
    self->f28C = x * 0.01f;
}

void func_00129188(PlacedObject* self, f32* out)
{
    *out = self->f28C * 100.0f;
}

void func_001291A0(PlacedObject* self, f32 x)
{
    self->f290 = x * 0.01f;
}

void func_001291B8(PlacedObject* self, f32* out)
{
    *out = self->f290 * 100.0f;
}

void* func_001291D0(PlacedObject* self)
{
    if (self->f284 == 0) {
        void* o = PopZeroedFreeSlot((u8*)self->world + 0x1BF4);
        self->f284 = (RangeRecord*)o;
        func_001B1AC8(o);
        AppendToList((u8*)self->world + 0x1C00, self->f284);
    }
    return self->f284;
}

void func_00129228(PlacedObject* self, s32 flag)
{
    if (flag != 0) {
        EnsureRangeRecord(self);
        return;
    }
    if (self->f284 == 0) {
        return;
    }
    RemoveFromList((u8*)self->world + 0x1C00, self->f284);
    AppendToList(&g_deferredReleaseListC, self->f284);
    self->f284 = 0;
}

void func_00129288(void* self, s32 value)
{
    func_001B1CF8(EnsureRangeRecord(self), value);
}

void func_001292B8(void* self, f32 x)
{
    func_001B1D70(EnsureRangeRecord(self, x), x);
}

void func_001292E8(f32 x)
{
    func_001B1DA8(EnsureRangeRecord(x), x);
}

void func_00129318(f32 x)
{
    func_001B1FB0(EnsureRangeRecord(x), x);
}

void func_00129348(f32 x)
{
    func_001B1FE0(EnsureRangeRecord(x), x);
}

void func_00129378(f32 x)
{
    func_001B2010(EnsureRangeRecord(x), x);
}

void func_001293A8(void* self, void* src)
{
    func_001B2068(EnsureRangeRecord(self), src);
}

void func_001293D8(void* self, s32 value)
{
    ((RangeRecord*)EnsureRangeRecord(self))->fB0 = value;
}

void* func_00129400(PlacedObject* self)
{
    if (self->f284 != 0) return self->f284;
    func_001B1AC8(D_0027B520);
    return D_0027B520;
}

void func_00129440(PlacedObject* self, s32* out)
{
    *out = self->f284 != 0;
}

void func_00129450(PlacedObject* self, s32* out)
{
    void* p = self->f284;
    if (p == 0) {
        goto fail;
    }
    {
        Node_129450* n = *(Node_129450**)p;
        if (n == 0) {
            goto fail;
        }
        *out = n->value_2;
        return;
    }
fail:
    *out = -1;
}

void func_00129480(void* self, f32* out)
{
    Sub_129480* s = (Sub_129480*)GetRangeRecord(self);
    *out = s->value_4;
}

void func_001294B0(void* self, f32* out)
{
    *out = ((Sub_1294B0*)GetRangeRecord(self))->f8;
}

void func_001294E0(void* self, f32* out)
{
    *out = ((Sub_1294E0*)GetRangeRecord(self))->f40;
}

void func_00129510(PlacedObject* self, f32* out)
{
    *out = ((Sub_129510*)GetRangeRecord(self))->f44;
}

void func_00129540(void* self, f32* out)
{
    Sub_00129540* sub = (Sub_00129540*)GetRangeRecord(self);
    f32 value = func_00205778(sub->value / sub->scale, 1.0f) * 57.2957763671875f;
    *out = value + value;
}

void func_00129598(void* self, Quad_129598* out)
{
    *out = ((Result_129598*)GetRangeRecord(self))->value;
}

void func_001295C8(PlacedObject* self, f32* out)
{
    Vec02 a[3];
    a[0] = self->rot.r[0];
    a[1] = self->rot.r[1];
    a[2] = self->rot.r[2];
    self->desc02()->m2A(self, a);
    MatrixToEulerAngles(a, out);
    s32 n = 2;
    f32* p = out;
    do {
        n--;
        *p = *p * 57.295776f;
        p++;
    } while (n >= 0);
}

void func_00129648(PlacedObject* self, f32* src)
{
    Local_129648 l;
    f32* out = l.out;
    f32* dst = l.tmp;
    f32 k = 0.01745329424738884f;
    s32 i = 2;
    do {
        *dst = *src * k;
        i--;
        src++;
        dst++;
    } while (i >= 0);
    BuildEulerRotationMatrix(l.tmp, out);
    self->desc02()->m29(self, (Mat02*)out, 0);
    self->desc02()->m1E(self, (Mat02*)out);
}

void func_001296E0(PlacedObject* self)
{
    if (self->f1FC == 0) {
        void* v = CreatePoseSource(self->world, self, D_00219560);
        self->f1FC = v;
        InsertAttachment(self, v);
    }
}

void func_00129730(PlacedObject* self)
{
    if (self->f200 == 0) {
        void* v = CreatePoseSource(self->world, self, D_0021A790);
        self->f200 = v;
        InsertAttachment(self, v);
    }
}

void func_00129780(PlacedObject* self)
{
    Attachment* s3 = 0;
    Attachment* s2 = 0;
    Attachment* s1 = 0;
    s32 i;
    if (self->f1F8) func_001F5C0C(self->f1F8, 0, self->f26C << 2);
    for (Attachment* n = (Attachment*)self->list1E0.head; n != 0; n = n->link.next) {
        if (s1 == 0) if (n->mode0 != -1) s1 = n;
        if (s2 == 0) if (n->mode1 != -1) s2 = n;
        if (s3 == 0) if (n->mode2 != -1) s3 = n;
        if (n->mode3 == -1) continue;
        if (n->vt == (const T2195_Vt*)D_002197C0) {
            Track83* e = &((T2195_7C0*)n)->player->anim->tracks[((T2195_7C0*)n)->index];
            for (i = 0; i < e->morphCount; i++) {
                if (e->morph[i] != 0) {
                    if (self->f1F8[i] == 0) self->f1F8[i] = n;
                }
            }
        } else {
            for (i = 0; i < self->f26C; i++) {
                if (self->f1F8[i] == 0) self->f1F8[i] = n;
            }
        }
    }
    if (s1 && s1->mode0 == 0) s1 = 0;
    if (s2 && s2->mode1 == 0) s2 = 0;
    if (s3 && s3->mode2 == 0) s3 = 0;
    if (self->f1F8) {
        for (i = 0; i < self->f26C; i++) {
            if (self->f1F8[i] != 0) {
                if (((Attachment*)self->f1F8[i])->mode3 == 0) self->f1F8[i] = 0;
            }
        }
    }
    self->f1F4 = s3;
    if (s1 != self->f1EC || s2 != self->f1F0) {
        func_00129DF8(self);
        if (s1 != self->f1EC) {
            self->f1EC = s1;
            if (s1) SettlePoseSourceModes(s1);
        }
        if (s2 != self->f1F0) {
            self->f1F0 = s2;
            if (s2) SettlePoseSourceModes(s2);
        }
    }
}

void func_001299E0(PlacedObject* self, Node_1299E0* src)
{
    ListFrame frame;
    Node_1299E0* node = (Node_1299E0*)self->list1E0.head;
    if (node != 0 && node->key > src->key) {
        node = node->next;
        while (node != 0 && node->key > src->key) {
            node = node->next;
        }
    }
    InsertBeforeInList(&self->list1E0, node, src);
    self->desc02()->m2B(self);
}

void func_00129A58(PlacedObject* self)
{
    Iter_001288F0 it;
    Node_129A58* nodes[20];
    s32 n = 0;
    Node_129A58* node;
    Begin_129A58::Of(&it, &self->list1E0);
    for (node = Next_129A58::Of(&it); node != 0; node = Next_129A58::Of(&it)) {
        nodes[n] = node;
        RemoveFromList(&self->list1E0, node);
        n++;
    }
    while (--n >= 0) {
        Node_129A58* c = (Node_129A58*)self->list1E0.head;
        node = nodes[n];
        while (c != 0 && c->key > node->key) c = c->next;
        InsertBeforeInList(&self->list1E0, c, node);
    }
    self->desc02()->m2B(self);
    g_activeListFrames = (ListFrame*)it.saved;
}

Node_129B98* func_00129B98(PlacedObject* self, s32 key)
{
    ListFrame frame;
    Node_129B98* node = (Node_129B98*)self->world->f1B64;
    while (node != 0) {
        if (node->owner == self) {
            if (key == -1) return node;
            if (MatchesObjectId(node->item, key) != 0) return node;
        }
        node = node->next;
    }
    return 0;
}

Node_129C20* func_00129C20(PlacedObject* self, s32 key)
{
    ListFrame frame;
    Node_129C20* n = (Node_129C20*)self->world->list1B94.head;

    while (n != 0) {
        if (n->f1C == self) {
            if (key == -1) return n;
            if (MatchesObjectId(n->f18, key) != 0) return n;
        }
        n = n->f10;
    }
    return 0;
}

void* func_00129CA8(PlacedObject* node)
{
    while (node != 0) {
        Attachment* a = node->f1EC;
        if (a != 0 && a->vt == (const T2195_Vt*)D_002197C0) {
            return ((T2195_7C0*)a)->player;
        }
        a = node->f1F0;
        if (a != 0 && a->vt == (const T2195_Vt*)D_002197C0) {
            return ((T2195_7C0*)a)->player;
        }
        node = (PlacedObject*)node->parent;
    }
    return 0;
}

void func_00129D00(PlacedObject* self, void* v, Node_129D00** out)
{
    Node_129D00* n;

    if (self != 0) {
        n = (Node_129D00*)CreatePoseSource(self->world, self, ((u8*)D_002195D8));
        n->w14 = v;
        InsertAttachment(self, n);
        *out = n;
    }
}

s32 func_00129D70(Actor6C* self)
{
    Actor6C* n;
    if (func_00123DC0((u8*)self + 0x150) == 0) return 0;
    if (func_00123E00((u8*)self + 0x160) != 0) goto body;
    return 0;
body:
    n = (Actor6C*)self->f34;
    while (n != 0) {
        if ((n->vtable->f8 & 1) != 0) {
            if (func_00129D70(n) == 0) return 0;
        }
        n = (Actor6C*)n->f1C;
    }
    return 1;
}

void func_00129DF8(PlacedObject* self)
{
    if (self->root != 0) self->root->tries = 0;
}

void func_00129E10(void* self, void* src)
{
    Frame_129E10 f;
    u8* p = (u8*)D_00260E70;
    func_00118CF0(&f.a, src);
    Quad_129E10 av = f.a;
    CopyQuadword(&f.b, p);
    (void)StoreQuadword(&f.r, func_00118D30(av, f.b));
    func_00129E88(self, &f.r);
}

void func_00129E88(PlacedObject* self, Vec16_12A5D0* value)
{
    if (self->p20C == (u8*)D_00260E70)
        self->p20C = (u8*)AllocateFrontMemory(16);
    *(Vec16_12A5D0*)self->p20C = *value;
}

void func_00129EE0(void* self, void* src)
{
    Frame_129EE0 f;
    u8* p = (u8*)D_00260E80;
    func_00118CF0(&f.a, src);
    Quad_129EE0 av = f.a;
    CopyQuadword(&f.b, p);
    (void)StoreQuadword(&f.r, func_00118D30(av, f.b));
    func_00129F58(self, &f.r);
}

void func_00129F58(PlacedObject* self, Quad_129F58* src)
{
    if (self->p210 == (u8*)D_00260E80) self->p210 = (u8*)AllocateFrontMemory(16);
    *(Quad_129F58*)self->p210 = *src;
}

void func_00129FB0(PlacedObject* self, void* src)
{
    Frame_129FB0 f;
    u8* p = (u8*)D_00260E90;
    func_00118CF0(&f.a, src);
    Quad_129FB0 av = f.a;
    CopyQuadword(&f.b, p);
    (void)StoreQuadword(&f.r, func_00118D30(av, f.b));
    func_0012A028(self, &f.r);
}

void func_0012A028(PlacedObject* self, Quad_12A028* src)
{
    if (self->p214 == (u8*)D_00260E90) self->p214 = (u8*)AllocateFrontMemory(16);
    *(Quad_12A028*)self->p214 = *src;
}

void func_0012A080(PlacedObject* self, void* src)
{
    Frame_12A080 f;
    u8* p = (u8*)D_00260EA0;
    func_00118CF0(&f.a, src);
    Quad_12A080 av = f.a;
    CopyQuadword(&f.b, p);
    (void)StoreQuadword(&f.r, func_00118D30(av, f.b));
    func_0012A0F8(self, &f.r);
}

void func_0012A0F8(PlacedObject* self, Quad_12A0F8* src)
{
    if (self->p218 == (u8*)D_00260EA0) self->p218 = (u8*)AllocateFrontMemory(16);
    *(Quad_12A0F8*)self->p218 = *src;
}

void func_0012A150(PlacedObject* self, f32 scale)
{
    Vec4F_12A150 tmp;
    tmp.x = D_00260EB0[0] * scale;
    tmp.y = D_00260EB0[1] * scale;
    tmp.z = D_00260EB0[2];
    tmp.w = D_00260EB0[3] * scale;
    func_0012A200(self, (Vec4_12A150*)&tmp);
}

void func_0012A1A0(PlacedObject* self, f32 scale)
{
    Vec4_12A150 tmp = *(Vec4_12A150*)self->p21C;
    tmp.w = scale * (tmp.x - tmp.y) / tmp.z;
    func_0012A200(self, &tmp);
}

void func_0012A200(PlacedObject* self, Vec4_12A150* src)
{
    if (self->p21C == (u8*)D_00260EB0) {
        self->p21C = (u8*)AllocateFrontMemory(16);
    }
    *(Vec4_12A150*)self->p21C = *src;
}

void func_0012A270(void* self, f32 s)
{
    f32 v[4];
    f32* m = (f32*)D_00260EC0;
    v[0] = m[0] * s;
    v[1] = m[1] * s;
    v[2] = m[2];
    v[3] = m[3] * s;
    func_0012A320(self, v);
}

void func_0012A2C0(PlacedObject* self, f32 scale)
{
    Pack4_12A2C0 tmp;
    tmp = *(Pack4_12A2C0*)self->p220;
    tmp.d = scale * (tmp.a - tmp.b) / tmp.c;
    func_0012A320(self, &tmp);
}

void func_0012A320(PlacedObject* self, Pack4_12A320* src)
{
    if (self->p220 == (u8*)D_00260EC0) {
        self->p220 = (u8*)AllocateFrontMemory(0x10);
    }
    *(Pack4_12A320*)self->p220 = *src;
}

void func_0012A390(void* self, s8 value) { *((s8*)((u8*)self + 0x2C9)) = value; }

void func_0012A398(void* self, s8 value) { *((s8*)((u8*)self + 0x2CA)) = value; }

void func_0012A3A0(void* self, s32 value) { SetPositionSourceMode(self, value ? 1 : -1); }

void func_0012A3C8(void* self, s32 a1)
{
    func_0012A3E8(self, a1 != 0);
}

void func_0012A3E8(PlacedObject* self, u32 value)
{
    self->flags = (self->flags & ~(3ull << 40)) | ((u64)(value & 3) << 40);
}

void func_0012A418(PlacedObject* self, u32* out)
{
    u32 value = (u32)(self->flags >> 40);
    value &= 3;
    *out = value;
}

void func_0012A430(PlacedObject* self, s32 value)
{
    EnsureBaseAttachment(self);
    ((State_12A430*)self->f1FC)->value = value;
    self->desc02()->m2B(self);
}

void func_0012A478(void* self, s32 a1)
{
    SetOrientationSourceMode(self, a1 != 0 ? 1 : -1);
}

void func_0012A4A0(PlacedObject* self, s32 value)
{
    EnsureBaseAttachment(self);
    ((State_12A4A0*)self->f1FC)->value = value;
    self->desc02()->m2B(self);
}

void func_0012A4E8(PlacedObject* self, s32 value)
{
    EnsureBaseAttachment(self);
    ((State_12A4E8*)self->f1FC)->value = value;
    SortAttachments(self);
}

void func_0012A528(PlacedObject* self, s32 value)
{
    EnsureAimAttachment(self);
    if (value == 3) value = 9;
    ((u8*)self->f200)[0x11] = value;
    self->desc02()->m2B(self);
}

void func_0012A580(PlacedObject* self, f32 f)
{
    EnsureAimAttachment(self);
    ((Sub_12A580*)self->f200)->f40 = f;
}

void func_0012A5B8(PlacedObject* self, f32* out)
{
    f32 r = 0.0f;
    if (self->f200 != 0) r = ((Sub_12A5B8*)self->f200)->f40;
    *out = r;
}

void func_0012A5D0(PlacedObject* self, Vec16_12A5D0* src)
{
    EnsureAimAttachment(self);
    ((Sub_12A5D0*)self->f200)->v50 = *src;
}

void func_0012A610(PlacedObject* self, Quad16* out)
{
    Quad16* src = self->f200 != 0 ? (Quad16*)((u8*)self->f200 + 0x50) : (Quad16*)D_00275C40;
    *out = *src;
}

void func_0012A630(PlacedObject* self, U64_12A630* src)
{
    EnsureAimAttachment(self);
    ((Sub_12A630*)self->f200)->v60 = *src;
}

void func_0012A678(PlacedObject* self, U64P* out)
{
    U64P* src = self->f200 != 0 ? (U64P*)((u8*)self->f200 + 0x60) : (U64P*)g_unitRange;
    *out = *src;
}

void func_0012A6A0(PlacedObject* self, Vec16_12A6A0* src)
{
    EnsureAimAttachment(self);
    ((Sub_12A6A0*)self->f200)->v70 = *src;
}

void func_0012A6E0(PlacedObject* self, Quad16* out)
{
    Quad16* src = self->f200 != 0 ? (Quad16*)((u8*)self->f200 + 0x70) : (Quad16*)D_00275C40;
    *out = *src;
}

void func_0012A700(PlacedObject* self, U64_12A700* src)
{
    EnsureAimAttachment(self);
    ((Sub_12A700*)self->f200)->v80 = *src;
}

void func_0012A748(PlacedObject* self, U64P* out)
{
    U64P* src = self->f200 != 0 ? (U64P*)((u8*)self->f200 + 0x80) : (U64P*)g_unitRange;
    *out = *src;
}

void func_0012A770(PlacedObject* self, void* v)
{
    EnsureAimAttachment(self);
    ((Sub_12A770*)self->f200)->f44 = v;
}

void func_0012A7A8(PlacedObject* self, s32* out)
{
    s32 r = 0;
    if (self->f200 != 0) r = ((Sub_12A7A8*)self->f200)->v44;
    *out = r;
}

void func_0012A7C0(PlacedObject* self, s32 value)
{
    EnsureAimAttachment(self);
    ((State_12A7C0*)self->f200)->value = value;
}

void func_0012A7F8(PlacedObject* self, s32* out)
{
    s32 v = 0;
    if (self->f200 != 0) {
        v = ((Sub_12A7F8*)self->f200)->f48;
    }
    *out = v;
}

void func_0012A810(PlacedObject* self, s32 value)
{
    EnsureAimAttachment(self);
    ((Sub_12A810*)self->f200)->f20 = value;
}

void func_0012A848(PlacedObject* self, s32* out)
{
    s32 v = -1;
    if (self->f200 != 0) {
        v = ((Sub_12A848*)self->f200)->f20;
    }
    *out = v;
}

void func_0012A860(PlacedObject* self, void* b)
{
    AssignAimTarget(self->f200, b, (void*)&D_00248D30);
}

void func_0012A888(PlacedObject* self, void** out)
{
    *out = ResolveAimTarget(self->f200);
}

void func_0012A8B8(PlacedObject* self)
{
    ((Sub_12A8B8*)self->f200)->f4C = 0;
}

void func_0012A8C8(PlacedObject* self)
{
    ((Sub_12A8C8*)self->f200)->f4C = 1;
}

void func_0012A8D8(PlacedObject* self, s32 a1, f32 x, f32 y)
{
    if (self->f204 == 0) {
        Inner_0012A8D8* r = (Inner_0012A8D8*)CreatePoseSource(self->world, self, ((u8*)D_00219600));
        self->f204 = r;
        InsertAttachment(self, r);
    }
    ((Inner_0012A8D8*)self->f204)->f11 = a1;
    ((Inner_0012A8D8*)self->f204)->f1C = x;
    ((Inner_0012A8D8*)self->f204)->f20 = y;
    self->desc02()->m2B(self);
}

void* func_0012A970(PlacedObject* self)
{
    void* r = FindFirstObjectById(self->world, 0x102, 0x22A, self);
    if (r != 0) {
        return r;
    }
    return CreateTypedRecord(0x75, (s32)self->world, self, 0x22A, -1);
}

void func_0012A9C8(PlacedObject* self, s32 value)
{
    PlacedObject* o = (PlacedObject*)func_0012A970(self);
    if (value != -1) {
        o->f88 = value;
    }
}

void func_0012AA00(void* self, f32 value)
{
    ((Sub_0012AA00*)func_0012A970(self))->value = value;
}

void func_0012AA28(void* self, void* value)
{
    Ctx_12AA28* ctx = func_0012A970(self);
    ctx->field = value;
}

void func_0012AA50(PlacedObject* self, f32 a, f32 b)
{
    for (s32 i = 0; i < self->elemCount; i++) {
        Elem02* p = self->elems[i];
        if (p->kind == 6) SetScrollScale(p, a, b);
    }
}

void func_0012AAE8(PlacedObject* self, f32 value)
{
    ListFrame frame;
    for (s32 i = 0; i < self->elemCount; i++) {
        Elem02* p = self->elems[i];
        if (p->kind == 5) SetCrossfadeRatio(p, value);
    }
    for (PlacedObject* child = (PlacedObject*)self->children.head; child; child = (PlacedObject*)child->next) {
        if (child->desc->flags & 1) func_0012AAE8(child, value);
    }
}

void func_0012ABA8(PlacedObject* self)
{
    if (self->f2AC == 0) InitSoundParams(&self->f2AC);
}

void func_0012ABD0(PlacedObject* self, s32 value)
{
    EnsureSoundRecord(self);
    ((Inner_12ABD0*)self->f2AC)->value = value;
}

void func_0012AC08(PlacedObject* self, void* value)
{
    EnsureSoundRecord(self);
    StopSoundRecord(((Part_0012AC08R*)self->f2AC)->sub1C, 0);
    ((Part_0012AC08R*)self->f2AC)->link = value;
    Part_0012AC08R* p = (Part_0012AC08R*)self->f2AC;
    StartSoundEffect(p->link, p->f4, p->f8, p->fc, p->f10, p->f20, &p->sub1C, self, 0, p->sub14, 0);
}

void func_0012AC88(PlacedObject* self, s32* out)
{
    s32 v = -1;
    if (self->f2AC != 0) v = ((Inner_12AC88*)self->f2AC)->value;
    *out = v;
}

void func_0012ACA0(PlacedObject* self, f32 value)
{
    EnsureSoundRecord(self);
    ((Part_0012AC08*)self->f2AC)->f4 = value;
}

void func_0012ACD8(PlacedObject* self, f32* out)
{
    Sub_12ACD8* s = (Sub_12ACD8*)self->f2AC;
    f32 v = 3000.0f;
    if (s != 0) v = s->value;
    *out = v;
}

void func_0012ACF8(PlacedObject* self, f32 value)
{
    EnsureSoundRecord(self);
    ((Sub_12ACF8*)self->f2AC)->value = value;
}

void func_0012AD30(PlacedObject* self, Rec_12AD30* src)
{
    EnsureSoundRecord(self);
    ((Sub_12AD30*)self->f2AC)->rec = *src;
}

void func_0012AD78(PlacedObject* self, f32* out)
{
    Sub_12AD78* s = (Sub_12AD78*)self->f2AC;
    f32 v = 300.0f;
    if (s != 0) v = s->value;
    *out = v;
}

void func_0012AD98(PlacedObject* self, f32 f)
{
    EnsureSoundRecord(self, f);
    ((Inner_12AD98*)self->f2AC)->value = f;
}

void func_0012ADD0(PlacedObject* self, f32 value)
{
    EnsureSoundRecord(self);
    ((Part_0012AC08*)self->f2AC)->f20 = value;
}

void func_0012AE08(PlacedObject* self, f32* out)
{
    f32 r = 0.0f;
    if (self->f2AC != 0) {
        r = ((Part_0012AC08*)self->f2AC)->f20;
    }
    *out = r;
}

void func_0012AE20(PlacedObject* self)
{
    Part_12AE20* part = (Part_12AE20*)self->f2AC;
    if (part != 0) {
        void* p = part->ptr;
        if (p != 0) {
            SetSoundRecordVolume(p);
        }
    }
}

void func_0012AE58(PlacedObject* self, f32* out)
{
    f32 v = 1.0f;
    if (self->f2AC != 0) {
        v = ((Part_12AE58*)self->f2AC)->weight;
    }
    *out = v;
}

void func_0012AE78(PlacedObject* self, f32 f)
{
    EnsureSoundRecord(self, f);
    ((Part_12AE78*)self->f2AC)->value = f;
}

void func_0012AEB0(PlacedObject* self)
{
    Inner_12AEB0* in = (Inner_12AEB0*)self->f2AC;
    if (in != 0) {
        if (in->ptr != 0) SetSoundRecordPitch(in->ptr);
    }
}

void func_0012AEE8(PlacedObject* self, f32* out)
{
    f32 r = 0.0f;
    if (self->f2AC != 0) {
        r = ((Part_12AEE8*)self->f2AC)->value;
    }
    *out = r;
}

void func_0012AF00(PlacedObject* self, U64_12AF00* out)
{
    Sub_12AF00* s = (Sub_12AF00*)self->f2AC;
    if (s != 0) {
        *out = s->p14;
    } else {
        f32* f = (f32*)out;
        f[0] = -1.0f;
        f[1] = -1.0f;
    }
}

void func_0012AF38(PlacedObject* self, void* value, Rec_0012AF38* src, f32 x, f32 y, f32 z)
{
    EnsureSoundRecord(self);
    ((Part_0012AF38*)self->f2AC)->link = value;
    ((Part_0012AF38*)self->f2AC)->f4 = x;
    ((Part_0012AF38*)self->f2AC)->f8 = y;
    ((Part_0012AF38*)self->f2AC)->fc = z;
    ((Part_0012AF38*)self->f2AC)->rec14 = *src;
    StopSoundRecord(((Part_0012AF38*)self->f2AC)->sub1C, 0);
    Part_0012AF38* p = (Part_0012AF38*)self->f2AC;
    StartSoundEffect(p->link, p->f4, p->f8, p->fc, p->f10, p->f20, &p->sub1C, self, 0, &p->rec14, 0);
}

void func_0012B010(PlacedObject* self)
{
    Inner_12B010* inner = (Inner_12B010*)self->f2AC;
    if (inner != 0) StopSoundRecord(inner->resource, 0);
}

void func_0012B040(void* ptr)
{
    PlacedObject* self = (PlacedObject*)ptr;
    if (!self->f288) {
        self->f288 = (Entry_12B0B0*)AllocateFrontMemory(64);
        *(Entry_12B0B0*)self->f288 = D_00261000[0];
        ((Entry_12B0B0*)self->f288)->w[0] = -1;
    }
}

void func_0012B0B0(PlacedObject* self, s32 a1)
{
    EnsureColorRecord(self);
    ((Entry_12B0B0*)self->f288)->w[0] = a1;
    Entry_12B0B0* e = (Entry_12B0B0*)self->f288;
    s32 k = e->w[0];
    if (k != -1) *e = D_00260F00[k];
}

void func_0012B128(PlacedObject* self, s32* out) { *out = self->f288 ? *(s32*)self->f288 : -1; }

void func_0012B140(PlacedObject* self, Vec_12B140* input)
{
    EnsureColorRecord(self);
    *(Vec_12B140*)((u8*)self->f288 + 0x10) = *input;
}

void func_0012B180(PlacedObject* self, Quad_12B180* out)
{
    u8* src = self->f288 ? (u8*)self->f288 + 0x10 : (u8*)&D_00248D30;
    *out = *(Quad_12B180*)src;
}

void func_0012B1A0(PlacedObject* self, Vec_12B1A0* input)
{
    EnsureColorRecord(self);
    *(Vec_12B1A0*)((u8*)self->f288 + 0x20) = *input;
}

void func_0012B1E0(PlacedObject* self, Quad_12B1E0* out)
{
    u8* src = self->f288 ? (u8*)self->f288 + 0x20 : (u8*)&D_00248D30;
    *out = *(Quad_12B1E0*)src;
}

void func_0012B200(PlacedObject* self, f32 value)
{
    EnsureColorRecord(self);
    ((Inner_0012B238*)self->f288)->value = value;
}

void func_0012B238(PlacedObject* self, f32* out)
{
    f32 v = 0.0f;
    Inner_0012B238* p = (Inner_0012B238*)self->f288;
    if (p != 0) v = p->value;
    *out = v;
}

void func_0012B250(PlacedObject* self, s32 v)
{
    self->tint[2] = v;
    self->tint[1] = v;
    self->tint[0] = v;
}

void func_0012B260(PlacedObject* self, s32* out)
{
    *out = self->tint[0];
}

void func_0012B270(PlacedObject* self, s32 v)
{
    self->tint[0] = v;
}

void func_0012B278(PlacedObject* self, s32* out)
{
    *out = self->tint[0];
}

void func_0012B288(PlacedObject* self, u8 value) { self->tint[1] = value; }

void func_0012B290(PlacedObject* self, s32* out)
{
    *out = self->tint[1];
}

void func_0012B2A0(PlacedObject* self, s32 v)
{
    self->tint[2] = v;
}

void func_0012B2A8(PlacedObject* self, s32* out)
{
    *out = self->tint[2];
}

void func_0012B2B8(PlacedObject* self, s32 value)
{
    self->tint[3] = value;
}

void func_0012B2C0(PlacedObject* self, s32* out)
{
    *out = self->tint[3];
}

void func_0012B2D0(PlacedObject* self, u8 v)
{
    self->f2B4 = v;
}

void func_0012B2D8(PlacedObject* self, s32* out)
{
    *out = self->f2B4;
}

s32 func_0012B2E8(PlacedObject* self, Obj_12B2E8* a1)
{
    return a1->value != 0;
}

void func_0012B2F8(PlacedObject* self, s32 key)
{
    s32 callVt = 0;
    s32 i;
    St_12B2F8* st;

    if (key == -1) {
        st = (St_12B2F8*)self->f2C0;
        if (st != 0) {
            callVt = st->Set(-1);
        }
    } else {
        for (i = 0; i < self->f2B8; i++) {
            if (((Entry_12B2F8*)self->f2BC)[i].key == key) {
                break;
            }
        }
        if (i < self->f2B8) {
            if (self->f2C0 == 0) {
                self->f2C0 = (St_12B2F8*)CreatePoseSource(self->world, self, ((u8*)D_002195B0));
                InsertAttachment(self, self->f2C0);
            }
            callVt = ((St_12B2F8*)self->f2C0)->Set(3);
            ((St_12B2F8*)self->f2C0)->f38 = (u8*)self + 0x26C;
            ((St_12B2F8*)self->f2C0)->f3C = ((Entry_12B2F8*)self->f2BC)[i].val;
        }
    }
    if (callVt != 0) {
        self->desc02()->m2B(self);
    }
}

void func_0012B420(PlacedObject* self, s32 flag)
{
    u64 want = flag != 0;
    if (want != (((self->flags >> 36) ^ 1) & 1)) {
        return;
    }
    u64 bit = (u64)(flag & 1) << 36;
    self->flags = (self->flags & 0xFFFFFFEFFFFFFFFFULL) | bit;
    if (IsObjectAttached(self) == 0) {
        return;
    }
    if (flag != 0) {
        AddCameraObject(g_camera, self);
    } else {
        RemoveCameraObject(g_camera, self);
    }
}

void func_0012B4C8(PlacedObject* self, s32 flag)
{
    if ((0 < (u32)flag) != (self->f294 == 0)) {
        goto done;
    }
    if (IsObjectAttached(self) == 0) {
        goto store;
    }
    if (self->parent != 0) {
        goto store;
    }
    self->desc->m03(self);
    self->f294 = flag;
    self->desc->m02(self);
    goto done;
store:
    self->f294 = flag;
done:
    return;
}

void func_0012B550(PlacedObject* ctx, s32 on)
{
    if (on != 0) {
        ctx->flags |= (u64)1 << 32;
    } else {
        ctx->flags &= ~((u64)1 << 32);
    }
}

void func_0012B590(PlacedObject* ctx, s32* out)
{
    if ((ctx->flags & ((u64)1 << 32)) != 0) {
        *out = 1;
    } else {
        *out = 0;
    }
}

void func_0012B5B8(PlacedObject* self, void* a1, void* a2)
{
    void* t = self->parent;
    if (a1 == t || a2 == t || a1 == a2) {
        if (a1 != 0 || a2 != 0) {
            if (self->f224 == 0) {
                self->f224 = (Rec2195_224*)AllocateZeroedFrontMemory(0xC0);
            }
        }
        Sub_12B5B8* p = (Sub_12B5B8*)self->f224;
        if (a1 != self->parent) {
            p->f60 = a1;
            p->fB0 = p->fB0 | 4;
        } else {
            p->fB0 = p->fB0 & 4;
        }
        if (a2 != self->parent) {
            p->f60 = a2;
            p->fB0 = p->fB0 | 8;
        } else {
            p->fB0 = p->fB0 & 8;
        }
        func_00128018(0, a1, (u8*)self + 0x140, (u8*)self + 0x100);
        func_00128150(0, a2, (u8*)self + 0x110, (u8*)self + 0xD0);
    }
}

ASM_FUNC(func_0012B6A0);

void func_0012B6B8(CodeChecksum* self)
{
    u32 c;
    InitPlacedObject(self);
    self->start = 0x100018;
    self->end = D_00148D64;
    self->crc = 0xFFFFFFFF;
    for (s32 i = 0; i < 256; i++) {
        c = (u32)i;
        s32 k = 7;
        do {
            if (c & 1) {
                c = (c >> 1) ^ 0xEDB88320;
            } else {
                c >>= 1;
            }
        } while (--k >= 0);
        self->table[i] = c;
    }
}

void func_0012B760(CodeChecksum* self)
{
    if (self->remaining != 0) {
        s32 n = self->remaining;
        u32* p = self->cursor;
        u32 crc = self->crc;
        u8* tbl = (u8*)self->table;
        s32 i = 0;
        if (n > 0) {
            do {
                u32 w = *p;
                i++;
                n -= 4;
                crc = *(u32*)(tbl + (((crc ^ w) & 0xFF) << 2)) ^ (crc >> 8);
                crc = *(u32*)(tbl + (((crc ^ (w >> 8)) & 0xFF) << 2)) ^ (crc >> 8);
                crc = *(u32*)(tbl + (((crc ^ (w >> 16)) & 0xFF) << 2)) ^ (crc >> 8);
                crc = *(u32*)(tbl + (((crc ^ (w >> 24)) & 0xFF) << 2)) ^ (crc >> 8);
                p++;
                if (i >= 64) break;
            } while (n > 0);
        }
        self->cursor = p;
        self->crc = crc;
        self->remaining = n;
        if (n == 0 && crc != 0) {
            g_checksumMismatch[0] = 1;
            TriggerScriptEvent(self, 2, 0, 0);
        }
    }
}

void func_0012B868(void) {}

void func_0012B870(Animation* self)
{
    InitObject(self);
    SetListLinkOffset(&self->props6C, 0x3C);
    Kin83* k = &self->kin;
    k->pos = 1.0f;
    k->vel = 0.0f;
    k->acc = 0.0f;
    self->lo = 0.0f;
    self->hi = 1.0f;
    self->out = 1.0f;
}

void func_0012B8C8(Animation* self, Stream83* other)
{
    s32 k;
    Track83* sel = 0;
    Track83* e;
    T2196_Pos* qp;
    T2196_Rot* qr;
    T2196_Scale* qs;
    T2196_Weight* qw;
    s32 i;
    s32 j;
    s32 t;
    s32 flags;

    t = ReadBufferedS16(other);
    self->id = t;
    t = ReadBufferedS16(other);
    self->length = (f32)t * 0.01666666753590107f;
    t = ReadBufferedU16(other);
    self->targetCount = t;
    self->targets = (s32*)AllocateFrontMemory(t << 2);
    for (k = 0; k < self->targetCount; k++) {
        self->targets[k] = ReadBufferedS16(other);
    }
    t = ReadBufferedS8(other);
    self->trackCount = t;
    self->tracks = (Track83*)AllocateZeroedFrontMemory(t * 28);
    for (i = 0; i < self->trackCount; i++) {
        e = &self->tracks[i];
        e->target = ReadBufferedS16(other);
        flags = ReadBufferedS8(other);
        if (flags & 1) {
            qp = CreatePositionCurve(ReadBufferedS8(other));
            e->pos = qp;
            if (qp->vt->read) qp->vt->read(qp, other);
        }
        if (flags & 2) {
            qr = CreateRotationCurve(ReadBufferedS8(other));
            e->rot = qr;
            if (qr->vt->read) qr->vt->read(qr, other);
        }
        if (flags & 4) {
            qs = CreateScaleCurve(ReadBufferedS8(other));
            e->scale = qs;
            if (qs->vt->read) qs->vt->read(qs, other);
        }
        if (flags & 8) {
            qw = CreateWeightCurve(ReadBufferedS8(other));
            e->weight = qw;
            if (qw->vt->read) qw->vt->read(qw, other);
        }
        if (flags & 0x10) {
            e->morphCount = ReadBufferedU8(other);
            e->morph = (T2196_Weight**)AllocateZeroedFrontMemory(e->morphCount << 2);
            for (j = 0; j < e->morphCount; j++) {
                t = ReadBufferedS8(other);
                if (t != -1) {
                    e->morph[j] = CreateWeightCurve(t);
                    qw = e->morph[j];
                    if (qw->vt->read) qw->vt->read(qw, other);
                }
            }
        }
        sel = (flags & 0x20) ? e : sel;
    }
    if (sel != 0) MoveAnimationTrackToEnd(self, sel);
    ReadAnimationEvents(self, other, 0, &self->startCount, &self->startList);
    ReadAnimationEvents(self, other, 1, &self->timedCount, &self->timedList);
    ReadAnimationEvents(self, other, 0, &self->endCount, &self->endList);
    ReadPropertyRecords(self, other);
}

void func_0012BC38(void* unused, Rd_12BC38* r, s32 flag, s32* count, Rec_12BC38** out)
{
    Rec_12BC38* e;
    s32 i;
    s32 merged;
    *count = ReadBufferedS8(r);
    *out = (Rec_12BC38*)AllocateZeroedFrontMemory(*count * 16);
    for (i = 0; i < *count; i++) {
        e = &(*out)[i];
        e->kind = ReadBufferedS8(r);
        if (flag) e->t = (f32)ReadBufferedS16(r) * 0.016666668f;
        switch (e->kind) {
        case 44:
        case 51:
            ReadOptionalBufferedBlock(r, &e->w8);
            break;
        case 0: {
            Ev_12BC38 t;
            Grp_12BC38* g;
            s32 j;
            s32 k;
            Rec_12BC38* q;
            merged = 0;
            t.h2 = ReadBufferedS16(r);
            t.h10 = ReadBufferedS16(r);
            t.w14 = ReadBufferedS32(r);
            t.w18 = ReadBufferedS32(r);
            t.f24 = ReadBufferedFloat(r);
            t.f1C = ReadBufferedFloat(r);
            t.f20 = ReadBufferedFloat(r);
            t.h0 = 1;
            t.hE = 0;
            k = i - 1;
            do {
                j = k;
                goto test;
            ins:
                g->h[g->n++] = t.h2;
                goto done;
            } while (0);
        test:
            q = &(*out)[j];
            if (q->t != e->t) goto done;
            if (j < 0) goto done;
            if (q->kind != 0) {
                j--;
                goto test;
            }
            *count = *count - 1;
            i = k;
            merged = 1;
            g = (Grp_12BC38*)q->w8;
            if (g->n < 6) goto ins;
        done:
            if (!merged) {
                e->w8 = (s32)AllocateFrontMemory(0x28);
                *(Ev_12BC38*)e->w8 = t;
            }
            break;
        }
        case 4:
        case 7:
            F32(e->w8) = (f32)ReadBufferedS16(r) * 0.016666668f;
            F32(e->wC) = ReadBufferedFloat(r);
            break;
        case 19:
        case 20:
            e->w8 = ReadBufferedS16(r);
            e->wC = ReadBufferedU8(r);
            break;
        case 16:
            e->w8 = ReadBufferedS16(r);
            H0(e->wC) = ReadBufferedS8(r);
            H2(e->wC) = ReadBufferedS8(r);
            break;
        case 21:
        case 23:
            e->w8 = (s32)AllocateZeroedFrontMemory(0xC);
            ((Sub_12BC38*)e->w8)->w0 = ReadBufferedS16(r);
            F32(((Sub_12BC38*)e->w8)->w4) = ReadBufferedFloat(r);
            F32(((Sub_12BC38*)e->w8)->w8) = ReadBufferedFloat(r);
            break;
        case 25:
        case 26:
            H0(e->w8) = ReadBufferedS16(r);
            e->wC = (s32)AllocateZeroedFrontMemory(0x14);
            ((Sub_12BC38*)e->wC)->w0 = 1;
            ((Sub_12BC38*)e->wC)->w8 = ReadBufferedS16(r);
            ((Sub_12BC38*)e->wC)->wC = -1;
            ((Sub_12BC38*)e->wC)->w10 = 0;
            ((Sub_12BC38*)e->wC)->w4 = (s32)AllocateZeroedFrontMemory(0x20);
            ReadBufferedStreamBytes(r, 0x20, (void*)((Sub_12BC38*)e->wC)->w4);
            break;
        case 27:
            e->w8 = ReadBufferedU8(r);
            e->wC = ReadBufferedS16(r);
            break;
        case 28:
            e->w8 = (s32)AllocateZeroedFrontMemory(0x10);
            ((Sub_12BC38*)e->w8)->w0 = ReadBufferedS16(r);
            ((Sub_12BC38*)e->w8)->w4 = ReadBufferedS16(r);
            F32(((Sub_12BC38*)e->w8)->w8) = ReadBufferedFloat(r);
            F32(((Sub_12BC38*)e->w8)->wC) = ReadBufferedFloat(r);
            break;
        case 37:
            H0(e->w8) = ReadBufferedS16(r);
            H2(e->w8) = ReadBufferedS16(r);
            break;
        case 6: case 12: case 13: case 17: case 18: case 22: case 24:
        case 29: case 30: case 31: case 32: case 35: case 36: case 39:
        case 41: case 59:
            e->w8 = ReadBufferedS16(r);
            break;
        case 40:
            e->w8 = ReadBufferedU16(r);
            break;
        case 38:
        case 45:
        case 47:
            e->w8 = ReadBufferedS16(r);
            e->wC = ReadBufferedS16(r);
            break;
        case 48:
            e->w8 = (s32)AllocateZeroedFrontMemory(0x10);
            ((Sub_12BC38*)e->w8)->w0 = ReadBufferedS16(r);
            ((Sub_12BC38*)e->w8)->w4 = ReadBufferedS16(r);
            ((Sub_12BC38*)e->w8)->w8 = ReadBufferedS16(r);
            F32(((Sub_12BC38*)e->w8)->wC) = ReadBufferedFloat(r);
            break;
        case 9:
        case 10:
            e->w8 = ReadBufferedS16(r);
            F32(e->wC) = ReadBufferedFloat(r);
            break;
        case 46:
        case 52:
            H0(e->w8) = ReadBufferedS16(r);
            H2(e->w8) = ReadBufferedS16(r);
            H0(e->wC) = ReadBufferedS16(r);
            break;
        case 54:
            H0(e->w8) = ReadBufferedS16(r);
            H2(e->w8) = ReadBufferedS16(r);
            ReadBufferedString(r, &e->wC);
            break;
        case 5:
        case 33:
        case 57:
        case 58:
            F32(e->w8) = ReadBufferedFloat(r);
            break;
        }
    }
}

void func_0012C140(void)
{
    CopyObjectData();
}

void func_0012C160(Animation* self)
{
    StartObject(self);
    Kin83* k = &self->kin;
    f32 t = g_currentEntry->dt;
    f32 v = k->pos + t * (k->vel + t * k->acc);
    f32 lo = self->lo;
    f32 hi = self->hi;
    if (v < lo) {
        v = lo;
    } else if (hi < v) {
        v = hi;
    }
    self->out = v;
    if (self->enabled) {
        AppendQueuedCallOnce(self->world, (void*)StartLinkedObjectAnimation, self, 0, 0);
    }
}

void func_0012C208(Obj_0012C208* self)
{
    s32 scratch[4];
    s32 v;
    if (self->id != -1) {
        v = (s32)FindFirstObjectById(self->host, 4, self->id, self);
        if (v == 0) {
            v = (s32)FindFirstObjectById(self->host, 0x104, self->id, self);
        }
    } else {
        v = 0;
    }
    CreateAnimationPlayerWithoutPresetTargets(self, v, 0, scratch, 0.0f, 1.0f);
}

void func_0012C288(Animation* self, Animation* alt, s32 npairs, TargetBinding* pairs, s32 flags, AnimationPlayer** out, f32 fa, f32 fb)
{
    s32 tmp;
    AnimationPlayer* obj;
    AnimationPlayer** pobj;
    World* world = self->world;
    obj = NewAnimationPlayer(world);
    if (out != 0) *out = obj;
    obj->time = fa;
    obj->anim = self;
    obj->fC = alt;
    obj->f1C = *(f32*)((u8*)self + 0x7C);
    SetAnimationPlayerSpeed(obj, fb);
    AppendToList(self->props6C, obj);
    if (self->f50 != 0) {
        AppendToList((u8*)&world->f1B70, obj);
    } else {
        AppendToList((u8*)&world->f1B64, obj);
    }
    PushBackMemoryMark();
    Animation* ctx;
    if (alt == 0) ctx = self; else ctx = alt;
    PlacedObject** hosts = (PlacedObject**)AllocateBackMemory(self->targetCount * 4);
    s32 i;
    for (i = 0; i < self->targetCount; i++) {
        hosts[i] = (PlacedObject*)FindFirstObjectById(world, 4, self->targets[i], ctx);
    }
    s32 count = self->trackCount + (self->f9C != 0);
    for (s32 k = 0; k < count; k++) {
        Track83* e = &self->tracks[k];
        s32 key = e->target;
        PlacedObject* h;
        s32 j;
        for (j = 0; j < npairs; j++) {
            if (key == pairs[j].key) {
                h = (PlacedObject*)pairs[j].object;
                goto found;
            }
        }
        h = (PlacedObject*)FindFirstObjectById(world, 4, key, ctx);
        if (h == 0) {
            for (i = 0; i < self->targetCount; i++) {
                h = (PlacedObject*)FindFirstObjectById(world, 1, key, hosts[i]);
                if (h != 0) break;
            }
            if (h == 0) {
                h = (PlacedObject*)FindFirstObjectById(world, 0x104, key, ctx);
                if (h == 0) continue;
            }
        }
    found:
        Node_12C288* n = CreateTrackAttachment(h);
        n->f28 = k;
        n->f1C = obj;
        n->f14 = *(s32*)((u8*)self + 0x78);
        if (k >= self->trackCount) {
            if (e->scale == 0 && e->morph == 0) {
                PushFreeSlot((u8*)&self->world->pool1B20, n);
                continue;
            }
        } else {
            if (flags & 1) {
                n->f10 = n->f11 = 3;
            } else {
                ChoosePoseSourceModes(n);
            }
            if (e->pos == 0) n->f10 = -1;
            if (e->rot == 0 && e->weight == 0) n->f11 = -1;
        }
        if (e->scale != 0) n->f12 = 2;
        if (e->morph != 0) n->f13 = 2;
        AppendToList((u8*)&obj->list44, n);
        InsertAttachment(h, n);
        PlacedObject* r = h->root;
        if (r == 0) {
            r = h;
            while (r->parent != 0) r = (PlacedObject*)r->parent;
        }
        if (!(r->flags & 0x400000000000)) {
            if ((u32)obj->f5C < 0x20) {
                r->flags |= 0x400000000000;
                ((PlacedObject**)obj->f60)[obj->f5C++] = r;
            }
        }
    }
    PopBackMemoryMark();
    for (s32 j = 0; j < obj->f5C; j++) {
        ((PlacedObject**)obj->f60)[j]->flags &= ~0x400000000000;
    }
    RegisterObjectGroup(world, obj->f54);
    if (self->f4C != 0) func_0012D448(obj, 1);
    tmp = 0;
    for (s32 m = 0; m < self->startCount; m++) {
        RunAnimationEvent(obj, &((Item_12C288*)self->startList)[m], &tmp);
    }
    ApplyListedPoseSources(obj, flags & 4);
    if (flags & 2) {
        RunSeekAnimationEvents(obj, self, &tmp);
    } else {
        SeekAnimationEventCursor(obj);
    }
    pobj = &obj;
    TriggerScriptEvent(self, 9, 1, &pobj);
}

s32 func_0012C7B0(void* a, void* b, s32 c, s32 d)
{
    return CreateAnimationPlayer(a, b, 0, 0, c, d);
}

void* func_0012C7D8(void* self, s32 key, s32 a2)
{
    void* out;
    CreateAnimationPlayer(self, key, 0, 0, a2, &out);
    return out;
}

Node_0012C808* func_0012C808(Owner_0012C808* self, s32 key)
{
    ListFrame frame;
    Node_0012C808* node = self->head;
    if (node != 0) {
        do {
            if (node->key == key) {
                return node;
            }
            node = node->next;
        } while (node != 0);
    }
    return 0;
}

void func_0012C840(void* self, s32 key, s32 a2, s32 a3, void** out, f32 fa, f32 fb)
{
    void* hit;
    void** dst = out ? out : &hit;
    hit = FindAnimationPlayerByScope(self, key);
    if (hit) {
        *dst = hit;
    } else {
        CreateAnimationPlayerWithoutPresetTargets(self, key, a3, dst, 0.0f, 1.0f);
    }
    SeekAnimationPlayer(*dst, a2, fa, fb);
}

void* func_0012C8F8(void* self, s32 key, s32 a2, s32 a3, f32 fa, f32 fb)
{
    void* out;
    FindOrCreateAnimationPlayerAndSeek(self, key, a2, a3, &out, fa, fb);
    return out;
}

void func_0012C918(void* self, void* a1, void* a2, void** out, f32 fa, f32 fb)
{
    if (*out != 0) {
        StopAnimationPlayer(*out);
        *out = 0;
    }
    if (self != 0) {
        CreateAnimationPlayerWithoutPresetTargets(self, a1, fa, fb, a2, out);
    }
}

s32 func_0012C9A8(Animation* a0)
{
    s32 n = a0->timedCount;
    if (n > 0) {
        s32 i = 0;
        u8* p = (u8*)a0->timedList + 4;
        do {
            i++;
            if (*(s32*)p == 0x19) return 1;
            p += 0x10;
        } while (i < n);
    }
    return 0;
}

INCLUDE_RODATA(D_00249B10);

ASM_FUNC(func_0012C9E8);

Rec_12CBE8* func_0012CBE8(Obj_12CBE8* self, s32 key) {
    s32 i;
    Rec_12CBE8* p;
    for (i = 0; i < self->f54; i++) {
        p = &self->f58[i];
        if (p->f4 == 0x27 && p->f8 == key) {
            return p;
        }
    }
    for (i = 0; i < self->f5C; i++) {
        p = &self->f60[i];
        if (p->f4 == 0x27 && p->f8 == key) {
            return p;
        }
    }
    for (i = 0; i < self->f64; i++) {
        p = &self->f68[i];
        if (p->f4 == 0x27 && p->f8 == key) {
            return p;
        }
    }
    return 0;
}

f32 func_0012CCC0(void)
{
    f32* p = (f32*)func_0012CBE8();
    f32 r = 0.0f;
    if (p != 0) {
        r = *p;
    }
    return r;
}

void* func_0012CCE8(Gr8B* self, void* key)
{
    for (s32 i = 0; i < self->f38; i++) {
        Entry_12CCE8* e = (Entry_12CCE8*)(self->f3C + i * 0x1C);
        if (MatchesObjectId(key, e->key) != 0) {
            return e;
        }
    }
    return 0;
}

ASM_FUNC(func_0012CD78);

void func_0012D1B0(Obj_12D1B0* self, void* ctx, s32* outCount, s32** outArr)
{
    s32 n = 0;
    s32 i;
    u8* p;
    if (self->count > 0) {
        i = self->count;
        p = (u8*)self->items + 4;
        do {
            if (*(s32*)p == 0x29) n++;
            p += 16;
        } while (--i != 0);
    }
    if (outCount != 0) {
        *outCount = n;
    }
    if (outArr != 0) {
        s32* res = (s32*)AllocateBackMemory(n * 4);
        *outArr = res;
        i = 0;
        if (i < self->count) {
            s32* out = res;
            do {
                Entry_12D1B0* e = (Entry_12D1B0*)(i * 16 + (u8*)self->items);
                if (e->type == 0x29) {
                    *out = (s32)FindFirstObjectById(self->host, 0x104, e->f8, ctx);
                    out++;
                }
                i++;
            } while (i < self->count);
        }
    }
}

void func_0012D2A8(Animation* self, Track83* p)
{
    Track83 tmp = *p;
    s32 idx = p - self->tracks;
    self->trackCount = self->trackCount - 1;
    if (idx < self->trackCount) {
        func_001F5B08(p, p + 1, (self->trackCount - idx) * 0x1C);
    }
    p = self->tracks + self->trackCount;

    *p = tmp;
    self->f9C = p;
}

void func_0012D398(Animation* a0)
{
    if (a0->f9C == 0) {
        void* r = FindEntryByObjectId();
        if (r) MoveAnimationTrackToEnd(a0, (Track83*)r);
    }
}

void func_0012D3E0() {}

void func_0012D3E8() {}

void func_0012D3F0() {}

AnimationPlayer* func_0012D3F8(World* pool)
{
    AnimationPlayer* o = (AnimationPlayer*)PopZeroedFreeSlot(&pool->pool1B58);

    o->vt = &g_animationPlayerMethods;
    SetListLinkOffset(&o->list44, 0x20);
    o->f60 = (u8*)o + 0x64;

    return o;
}

void func_0012D448(AnimationPlayer* self, s32 v)
{
    if (v == self->state24) {
        return;
    }
    if (v != 0) {
        AcquirePadSelectFlag(g_currentWorld);
    } else {
        ReleasePadSelectFlag(g_currentWorld);
    }
    self->state24 = (s8)v;
}

void func_0012D4A8(AnimationPlayer* self)
{
    Animation* track = self->anim;
    s32 n = track->timedCount;
    s32 i;
    if (n == 0) {
        return;
    }
    if (self->speed >= 0.0f) {
        i = 0;
        if (n > 0) {
            Key_12D4A8* keys = (Key_12D4A8*)track->timedList;
            for (i = 0; i < track->timedCount; i++) {
                if (keys[i].time >= self->time) {
                    break;
                }
            }
        }
        self->f20 = i;
    } else {
        for (i = n - 1; i >= 0; i--) {
            Key_12D4A8* k = &((Key_12D4A8*)track->timedList)[i];
            if (k->time <= self->time) {
                break;
            }
        }
        self->f20 = i + 1;
    }
}

T2195_7C0* func_0012D570(AnimationPlayer* a0, void* a1)
{
    ListFrame frame;
    T2195_7C0* n = (T2195_7C0*)a0->list44.head;
    while (n) {
        if (MatchesObjectId(n->owner, a1)) return n;
        n = (T2195_7C0*)n->w20.lo;
    }
    return 0;
}

LINKER_REMNANT(func_0012D5C8);

void func_0012D5D0(AnimationPlayer* self, Msg_12D5D0* msg, s32* out)
{
    Scratch_12D5D0 u;
    s32 rev = 0;
    Owner_12D5D0* owner = (Owner_12D5D0*)self->anim;
    World_12D5D0* world = owner->world;

    if (self->speed < 0.0f && msg >= owner->msgs) {
        rev = msg < &owner->msgs[owner->nmsgs];
    }
    switch (msg->kind) {
    case 42:
        if (func_001BE810() != 0) {
            self->time = Clamp_12D5D0::Of(msg->a0.f, 0.0f, owner->f34);
            self->f20--;
            *out = 1;
        }
        break;
    case 44:
        OpenKeyRecord(msg->a8.p);
        break;
    case 43:
        StopStreamVoice();
        break;
    case 0: {
#define Q_12D5D0 ((Seq_12D5D0*)msg->a8.p)
        s32 idx;
        s32 busy;
        s32 id;
        Collider* tgt;
        if (Q_12D5D0->count < 2) {
            idx = 0;
        } else {
            s32 r = RandomIntInRange(0, Q_12D5D0->count - 2);
            idx = (Q_12D5D0->cur + r + 1) % Q_12D5D0->count;
            Q_12D5D0->cur = idx;
        }
        id = Q_12D5D0->ids[idx];
        if (id == -1) {
            return;
        }
        busy = IsSoundEntryAvailable(id);
        if (self->p50 != 0 && busy != 0) {
            return;
        }
        if (Q_12D5D0->target != -1) {
            tgt = (Collider*)FindFirstObjectById(world, 0x104, Q_12D5D0->target, self->fC ? self->fC : (void*)self->anim);
        } else {
            tgt = (Collider*)self->fC;
        }
        if (tgt != 0) {
            StartSoundEffect(id, busy ? (VObj_12D5D0**)&self->p50 : 0, tgt, 0, (f32)Q_12D5D0->f18, (f32)Q_12D5D0->f14, Q_12D5D0->f24,
                          Q_12D5D0->f1C, Q_12D5D0->f20, 0, 0);
            if (busy && self->p50 != 0) {
                tgt->desc->m0E(tgt, 8, self->p50);
            }
        } else {
            StartSoundEffect(id, busy ? (VObj_12D5D0**)&self->p50 : 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
#undef Q_12D5D0
        break;
    }
    case 1:
        if (self->p50 != 0) {
            StopSoundRecord((VObj_12D5D0*)self->p50, 0);
        }
        break;
    case 2:
        func_001BED20();
        break;
    case 3:
        func_001BECF8();
        break;
    case 11:
        self->time = Clamp_12D5D0::Of(msg->a0.f, 0.0f, owner->f34);
        self->speed = 0.0f;
        break;
    case 4:
    case 7:
        self->time = msg->a8.f;
        SetAnimationPlayerSpeed(self, msg->aC.f);
        SeekAnimationEventCursor(self);
        SettleListedPoseSources(self);
        break;
    case 5:
        SetAnimationPlayerSpeed(self, msg->a8.f);
        break;
    case 6: {
        Collider* t = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.i, self->fC ? self->fC : (void*)owner);
        if (t != 0) {
            ChooseStepSequenceState(t);
        }
        break;
    }
    case 8:
        StopAnimationPlayer(self);
        *out = 1;
        break;
    case 9:
    case 10: {
        s32 on = msg->kind == 9;
        if (rev) {
            on = !on;
        }
        Collider* t = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.i, self->fC ? self->fC : (void*)owner);
        if (t == 0) {
            return;
        }
        if (msg->aC.f != 0.0f) {
            if (on) {
                func_00126CB8(t, msg->aC.f);
            } else {
                func_00126D60(t, msg->aC.f);
            }
        } else {
            if (on) {
                t->desc->m02(t);
            } else {
                t->desc->m03(t);
            }
        }
        break;
    }
    case 16: {
        Collider* t = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.i, self->fC ? self->fC : (void*)self->anim);
        if (t != 0) {
            SetColliderAnchors(t, msg->aC.h.lo < 0 ? t->mode450 : msg->aC.h.lo, 0, msg->aC.h.hi < 0 ? t->mode470 : msg->aC.h.hi, 0);
        }
        break;
    }
    case 12:
    case 13: {
        s32 on = msg->kind == 12;
        Collider* t;
        if (rev) {
            on = !on;
        }
        t = (Collider*)FindFirstObjectById(world, 4, msg->a8.i, self->anim);
        if (t != 0) {
            if (on) {
                PushObjectCameraController(t);
            } else {
                RemoveObjectCameraController(t);
            }
        }
        break;
    }
    case 14:
    case 15:
    {
        s32 on = msg->kind == 14;
        if (rev) {
            on = !on;
        }
        func_0012D448(self, on);
    }
        break;
    case 19:
    case 20: {
        s32 on = msg->kind == 19;
        if (rev) {
            on = !on;
        }
        func_00177800(g_player, on);
        if (on && msg->aC.i != 0) {
            ApplyListedPoseSources(self, 1);
        }
        break;
    }
    case 17:
    case 18: {
        Node_12D5D0* n = FindPlayerAttachmentByOwner(self, msg->a8.i);
        if (n != 0) {
            if ((msg->kind != 17) != !rev) {
                n->SetMode(5);
                n->mode0 = 5;
            } else {
                ChoosePoseSourceModes(n);
            }
        }
        break;
    }
    case 21:
    case 22:
    case 23:
    case 24: {
        Node_12D5D0* n;
        s32 key;
        if (msg->kind == 21 || msg->kind == 23) {
            key = *(s32*)msg->a8.p;
        } else {
            key = msg->a8.i;
        }
        n = FindPlayerAttachmentByOwner(self, key);
        if (n == 0) {
            break;
        }
        switch (msg->kind) {
        case 21:
            self->driven = n;
            self->f2C = msg;
            break;
        case 22:
            self->f2C = 0;
            if (self->f30 == 0) {
                self->driven = 0;
            }
            break;
        case 23:
            self->driven = n;
            self->f30 = msg;
            break;
        case 24:
            self->f30 = 0;
            if (self->f2C == 0) {
                self->driven = 0;
            }
            break;
        }
        break;
    }
    case 25:
        StartScreenFade(g_screenFade, msg->aC.i, msg->a8.h.lo);
        break;
    case 26:
        SaveFadeRequest(g_screenFade, msg->aC.i, msg->a8.h.lo);
        break;
    case 27: {
        Player* g = g_player;
        if (g != 0 && *(s32*)((u8*)g + 0x2220) == 9 && *(s32*)((u8*)g + 0x2228) == 0x1C && g_currentEntry == g_currentLevelRecord) {
            return;
        }
        func_001F4408(msg->a8.i, msg->aC.i);
        break;
    }
    case 33:
        StartTimer(g_timerElement, msg->a8.f);
        StartTimerCounting(g_timerElement);
        break;
    case 34:
        StopTimer(g_timerElement);
        break;
    case 28: {
        Collider* a = (Collider*)FindFirstObjectByIdMode4(world, ((Info_12D5D0*)msg->a8.p)->f0, owner->f18);
        Collider* b;
        if (((Info_12D5D0*)msg->a8.p)->f4 != -1) {
            b = (Collider*)FindFirstObjectByIdMode4(owner->world, ((Info_12D5D0*)msg->a8.p)->f4, owner->f18);
        } else {
            b = 0;
        }
        if (a != 0) {
            CreateAnimationPlayerWithoutPresetTargets(a, b, 0, 0, *(f32*)&((Info_12D5D0*)msg->a8.p)->f8, ((Info_12D5D0*)msg->a8.p)->fC);
        }
        break;
    }
    case 29:
    case 30:
    case 31:
    case 32: {
        Node_12D5D0* n = FindPlayerAttachmentByOwner(self, msg->a8.i);
        u8 go = 0;
        if (n != 0) {
            Ent_12D5D0* e = &owner->ents[n->index];
            switch (msg->kind) {
            case 29:
                if (e->fC != 0) {
                    u8 v = n->mode2;
                    n->mode2 = 2;
                    go = (u8)(v + 1) < 2;
                }
                break;
            case 30:
                if (e->fC != 0) {
                    s8 v = n->mode2;
                    n->mode2 = -1;
                    go = v != -1;
                }
                break;
            case 31:
                if (e->f18 != 0) {
                    u8 v = n->mode3;
                    n->mode3 = 2;
                    go = (u8)(v + 1) < 2;
                }
                break;
            case 32:
                if (e->f18 != 0) {
                    s8 v = n->mode3;
                    n->mode3 = -1;
                    go = v != -1;
                }
                break;
            }
        }
        if (go) {
            n->owner->desc02()->m2B(n->owner);
        }
        break;
    }
    case 35:
    case 36: {
        Node_12D5D0* n = FindPlayerAttachmentByOwner(self, msg->a8.i);
        if (n == 0) {
            break;
        }
        Ent_12D5D0* e = &owner->ents[n->index];
        PlacedObject* o = n->owner;
        if (msg->kind == 35) {
            ((VFnAim_12D5D0)e->f4->vt[0])(e->f4, o, 0, &u.v[0], &u.v[1], msg->a0.f, self->speed);
            o->desc02()->m1D(o, (Vec02*)&u.v[0]);
            o->desc02()->m20(o, (Vec02*)&u.v[1]);
        } else {
            ((VFnAim_12D5D0)e->f8->vt[0])(e->f8, o, 0, &u.v[2], &u.v[0], msg->a0.f, self->speed);
            o->desc02()->m1E(o, (Mat02*)&u.v[2]);
            o->desc02()->m21(o, (Vec02*)&u.v[0]);
        }
        break;
    }
    case 37:
        StartPadRecordPattern(g_padRecord, msg->a8.h.hi, (f32)msg->a8.h.lo * 0.016666668f);
        break;
    case 38: {
        Collider* t;
        if (msg->a8.i == -1) {
            t = (Collider*)self->fC;
        } else {
            t = (Collider*)FindFirstObjectByIdMode4(world, msg->a8.i, self->fC);
        }
        if (t == 0) {
            break;
        }
        u.p[1] = (void*)msg->aC.i;
        u.p[0] = self;
        t->desc->m0E(t, 0x12, u.p);
        break;
    }
    case 39: {
        *(f32*)&u.w[1] = msg->a0.f;
        u.w[2] = msg->a8.i;
        u.p[0] = self;
        NotifyAnimationPlayerCallbacks(self, 0x13, u.w);
        break;
    }
    case 40: {
        u.p[1] = &msg->a8;
        u.p[0] = &self;
        TriggerScriptEvent(self->anim, 0xA, 2, u.p);
        break;
    }
    case 41: {
        Collider* t;
        if (self->fC == 0) {
            break;
        }
        t = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.i, self->fC);
        if (t == 0) {
            break;
        }
        u.p[1] = t;
        *(f32*)&u.w[2] = msg->a0.f;
        u.p[0] = self;
        NotifyAnimationPlayerCallbacks(self, 0x15, u.w);
        break;
    }
    case 45: {
        Collider* t = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.i, self->fC);
        if (t != 0) {
            SelectValueEntryByKey(t, msg->aC.i);
        }
        break;
    }
    case 46: {
        void* scope = self->fC ? self->fC : (void*)self->anim;
        Collider* a = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.h.lo, scope);
        Collider* b;
        void* link;
        if (a == 0) {
            break;
        }
        b = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.h.hi, scope);
        link = FindListNodeByKey(a, b);
        if (link == 0) {
            link = CreateStateWalker(a, b, msg->aC.h.lo, 1);
        }
        SetStateWalkerTarget(link, msg->aC.h.lo);
        break;
    }
    case 47: {
        void* link = 0;
        void* scope = self->fC;
        if (scope == 0) {
            scope = self->anim;
        }
        Collider* a = (Collider*)FindFirstObjectByIdMode4(world, msg->a8.i, scope);
        if (a != 0) {
            link = FindListNodeByKey(a, (Collider*)FindFirstObjectByIdMode4(world, msg->aC.i, scope));
        }
        if (link != 0) {
            DestroyStateWalker(link);
        }
        break;
    }
    case 48: {
        Info_12D5D0* in = (Info_12D5D0*)msg->a8.p;
        void* scope = self->fC ? self->fC : (void*)owner;
        Collider* t = (Collider*)FindFirstObjectById(world, 0x104, in->f0, scope);
        if (t == 0) {
            break;
        }
        u.req.flags = 0;
        if (in->f4 != -1) {
            Collider* s = (Collider*)FindFirstObjectById(world, 4, in->f4, scope);
            if (s != 0) {
                if (IsObjectOfKind(s, 2) != 0) {
                    u.req.f4 = s;
                    u.req.flags |= 1;
                } else if (IsObjectOfKind(s, 0x7E) != 0) {
                    u.req.flags |= 4;
                    func_001920B0(s, &u.req.buf);
                } else if (IsObjectOfKind(s, 0x73) != 0) {
                    u.req.flags |= 4;
                    GetObjectWorldPosition(s, &u.req.buf);
                }
            }
        }
        if (u.req.flags == 0) {
            if (t->parent != 0 && IsObjectAttached(t->parent) != 0) {
                u.req.flags |= 1;
                u.req.f4 = t->parent;
            } else {
                u.req.flags |= 4;
                GetObjectWorldPosition(t, &u.req.buf);
            }
        }
        if (in->f8 != -1) {
            Collider* s = (Collider*)FindFirstObjectById(world, 4, in->f8, scope);
            if (s != 0) {
                u.req.f38 = s;
                u.req.flags |= 0x20;
            }
        }
        if (in->fC != 1.0f) {
            u.req.flags |= 0x18;
            u.req.f30 = in->fC;
        }
        t->desc->m1B(t, &u.req);
        break;
    }
    case 49:
        ShowCountedScreenElement(world);
        break;
    case 50:
        HideCountedScreenElement(world);
        break;
    case 51:
        QueueMovie(g_moviePlayer, msg->a8.i);
        break;
    case 52:
        ((VFnP_12D5D0)g_stackedCaptionGroup.vt[17])(&g_stackedCaptionGroup, &self->time);
        ResizeItemColumn(&g_stackedCaptionGroup, msg->aC.h.lo, (f32)msg->a8.h.lo, (f32)msg->a8.h.hi);
        break;
    case 53:
        ((VFnP_12D5D0)g_stackedCaptionGroup.vt[17])(&g_stackedCaptionGroup, 0);
        ClearItemColumn(&g_stackedCaptionGroup);
        break;
    case 54:
        PostItemColumnEntry(&g_stackedCaptionGroup, msg->a8.h.lo, msg->aC.i, (f32)msg->a8.h.hi * 0.00390625f);
        break;
    case 55:
    {
        u8* sys = g_elementStack;
        ((Word_12D5D0*)(sys + 0x30))->v = 0;
        SetElementStackState(sys, 0);
    }
        break;
    case 56:
    {
        u8* sys = g_elementStack;
        *(s32*)(sys + 0x30) = 1;
        SetElementStackState(sys, 1);
    }
        break;
    case 57:
        func_001DDAB8(world, msg->a8.f);
        break;
    case 58:
        func_001DDAC8(world, msg->a8.f);
        break;
    case 59: {
        Collider* t = (Collider*)FindFirstObjectById(world, 0x104, msg->a8.i, self->fC ? self->fC : (void*)owner);
        if (t != 0) {
            BindEntryQueueToObject(t, g_player);
        }
        break;
    }
    }
}

void func_0012E4E0(AnimationPlayer* self, Animation* sub, s32* out)
{
    f32 limit = self->time + 0.0001f;
    if (sub->timedCount != 0) {
    while (self->f20 < sub->timedCount && ((Item_12E4E0*)sub->timedList)[self->f20].t < limit) {
        Item_12E4E0* it = &((Item_12E4E0*)sub->timedList)[self->f20++];
        switch (it->type) {
        case 8:
            self->time = it->t;
            self->speed = 0;
            *out = 1;
            return;
        case 9:
        case 10:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 28:
        case 39:
            RunAnimationEvent(self, it, out);
            break;
        }
    }
    }
}

void func_0012E5D0(AnimationPlayer* self, Animation* list, s32* out)
{
    if (list->timedCount == 0) return;
    for (;;) {
        if (self->f20 < list->timedCount) {
            if (((Entry_12E5D0*)list->timedList)[self->f20].key < self->time || (self->time == ((Entry_12E5D0*)list->timedList)[self->f20].key && 0.0f < self->speed)) {
                Entry_12E5D0* e = &((Entry_12E5D0*)list->timedList)[self->f20];
                self->f20 = self->f20 + 1;
                RunAnimationEvent(self, e, out);
                if (*out != 0) return;
                continue;
            }
        }
        if (self->f20 <= 0) return;
        if (self->time < ((Entry_12E5D0*)list->timedList)[self->f20 - 1].key || (self->time == ((Entry_12E5D0*)list->timedList)[self->f20 - 1].key && self->speed < 0.0f)) {
            self->f20 = self->f20 - 1;
            RunAnimationEvent(self, &((Entry_12E5D0*)list->timedList)[self->f20], out);
            if (*out != 0) return;
            continue;
        }
        return;
    }
}

void func_0012E710(void* a0)
{
    RemoveFromList((u8*)&g_currentWorld->list1B7C, a0);
    PushFreeSlot((u8*)&g_currentWorld->pool1B58, a0);
}

void func_0012E760(AnimationPlayer* self)
{
    Frame_12E760 fr;
    Tmp_12E760 tmp;
    s32 i = 0;
    Animation* sub = self->anim;
    u8* base = (u8*)sub->world;
    for (i = 0; i < sub->endCount; i++) {
        Item_12E760* it = (Item_12E760*)((u8*)sub->endList + i * 16);
        tmp.a = 0;
        RunAnimationEvent(self, it, &tmp);
    }
    NotifyAnimationPlayerCallbacks(self, 6, self);
    ReleaseCallRecords(base, self->fE4);
    self->fE4 = 0;
    UnregisterObjectGroup(base, self->f54);
    func_0012D448(self, 0);
    RemoveQueuedCalls(base, 2, 0, self, -1, 0);
    RemoveFromList(sub->props6C, self);
    if (sub->f50 != 0) {
        RemoveFromList(base + 0x1B70, self);
    } else {
        RemoveFromList(base + 0x1B64, self);
    }
    AppendToList(base + 0x1B7C, self);
    s32 s0 = (s32)self + 0xC;
    s32 e = (s32)self + 0x44;
    fr.f04 = e;
    fr.f00 = e;
    s32 link = *(s32*)(e + 8);
    fr.f0C = (s32)g_activeListFrames;
    g_activeListFrames = (ListFrame*)&fr;
    fr.f08 = link;
    s32 head = *(s32*)e;
    fr.f04 = head + fr.f08;
    s32 a = head;
    if (a != 0) {
        do {
            Elem_12E760* el = (Elem_12E760*)a;
            el->vt->fn8(el, 7);
            s32 nx = *(s32*)fr.f04;
            fr.f04 = nx + fr.f08;
            a = nx;
        } while (a != 0);
    }
    if (self->f50 != 0)
        ClearSoundRecordHandle(&self->f50);
    tmp.b = s0;
    TriggerScriptEvent(sub, 0xB, 1, &tmp.b);
    g_activeListFrames = (ListFrame*)fr.f0C;
}

void func_0012E928(void* a0, void* a1, void* a2)
{
    Attachment* n = FindPlayerAttachmentByOwner(a0, a1);
    if (n) n->vt->release(n, (s32)a2);
}

f32 func_0012E968(Obj_12E968* self, f32 value)
{
    Range_12E968* range = self->range;
    f32 r;
    if (value < range->minimum) {
        r = 1.0f;
    } else if (range->maximum <= value) {
        r = 0.15f;
    } else {
        r = (value - range->maximum) / (range->minimum - range->maximum);
        r = r * 0.85f + 0.15f;
    }
    return r;
}

s32 func_0012E9E0(AnimationPlayer* o, f32* pos, f32* vel)
{
    s32 r = 0;
    Animation* l = o->anim;
    f32 x = *pos;
    f32 lim = l->length;
    if (lim <= x) {
        switch (l->f44) {
        case 0:
            if (lim < x) {
                *pos = lim;
                *vel = 0.0f;
            }
            break;
        case 1:
            *pos = func_002058A0(x, lim);
            break;
        case 2: {
            f32 d = lim + lim;
            s32 flag = 1;
            if (d <= x) {
                *pos = func_002058A0(x, d);
                if (*pos < l->length) flag = 0;
                *vel = __builtin_fabsf(*vel);
            }
            if (flag) {
                *pos = d - *pos;
                *vel = -*vel;
            }
            break;
        }
        }
        r = 1;
    } else if (x < 0.0f) {
        switch (l->f44) {
        case 0:
            *pos = 0.0f;
            *vel = 0.0f;
            break;
        case 1:
            *pos = WrapModulo(x, lim);
            break;
        case 2: {
            x = -x;
            if (x <= lim) {
                *pos = x;
                *vel = -*vel;
            } else {
                f32 d = lim + lim;
                *vel = __builtin_fabsf(*vel);
                f32 q = WrapModulo(*pos, d);
                *pos = q;
                if (l->length <= q) {
                    *pos = d - q;
                    *vel = -*vel;
                }
            }
            break;
        }
        }
        r = 1;
    }
    return r;
}

ASM_FUNC(func_0012EBD8);

void func_0012F0A0(AnimationPlayer* self, s32 mode, f32 a, f32 b)
{
    s32 flag = 0;
    f32 t;
    f32 base;
    switch (mode) {
    case 0:
        t = a;
        goto call;
    case 1:
        base = self->time;
        break;
    case 2:
    case 3:
        base = self->anim->length;
        break;
    default:
        goto call;
    }
    t = base + a;
call:
    SetAnimationPlayerSpeed(self, b);
    if (t == self->time) {
        return;
    }
    self->time = t;
    if (mode == 3) {
        RunSeekAnimationEvents(self, self->anim, &flag);
    } else {
        SeekAnimationEventCursor(self);
    }
    ApplyListedPoseSources(self, 0);
    SettleListedPoseSources(self);
    if (flag != 0) {
        StopAnimationPlayer(self);
    }
}

void func_0012F190(AnimationPlayer* a0, void* a1)
{
    ListFrame frame;
    T2195_7C0* n = (T2195_7C0*)a0->list44.head;
    while (n) {
        ApplyPoseSource(n, a1);
        n = (T2195_7C0*)n->w20.lo;
    }
}

void func_0012F1D8(AnimationPlayer* self)
{
    ListFrame frame;
    for (Item_0012F1D8* p = (Item_0012F1D8*)self->list44.head; p != 0; p = p->next) {
        SettlePoseSourceModes(p);
    }
}

ASM_FUNC(func_0012F210);

void func_0012F6B0(AnimationPlayer* self, f32 x)
{
    self->speed = x * self->f1C * self->anim->out;
}

void func_0012F6D0(AnimationPlayer* self, f32 x)
{
    f32 denom = self->f1C * self->anim->out;
    f32 r = self->speed;
    if (denom != 0.0f) {
        r = r / denom;
    }
    self->f1C = x;

    SetAnimationPlayerSpeed(self, r);
}

void func_0012F718(Owner_12F718* owner, s32 value)
{
    s32 frame[4];
    (void)frame;
    Node_12F718* node = owner->head;
    while (node != 0) {
        node->value14 = value;
        SortAttachments(node->data4);
        node = node->next;
    }
}

void func_0012F760(AnimationPlayer* self, s32 a1, s32 a2)
{
    Obj_12F760* obj = (Obj_12F760*)self->fC;
    if (obj != 0) {
        obj->vtbl[18](obj);
    }
    S1DBBD8* node = self->fE4;
    while (node != 0) {
        S1DBBD8* next = node->next;
        node->fn(node->k1, a1, a2);
        node = next;
    }
}

void func_0012F7E0(Obj_12F7E0* a0, void* a1, s32 a2)
{
    AddCallbackNode(a0->mid->p14, (u8*)a0 + 0xE4, a1, a2);
}

void func_0012F810(AnimationPlayer* a0, PlacedObject** a1)
{
    AddCallbackNode(a0->anim->world, &a0->fE4, (void*)(*a1)->link40.prev, a1);
}

void func_0012F840(IdFilterObject* self)
{
    InitCollider(self);
    SetColliderAnchors(self, 3, 0, 3, 0);
    self->id = -1;
}

void func_0012F888(IdFilterObject* self)
{
    CopyCollider(self);
    if (self->parent == 0) {
        InitContactPairFlags(self->world, self);
    }
}

void func_0012F8C8(IdFilterObject* self)
{
    StartPlacedObject(self);
    if (self->id != -1) {
        self->id = (s32)FindFirstObjectByIdMode4(self->world, self->id, self);
        self->mode = 2;
        return;
    }
    Iter_12F8C8 it;
    Begin_12F8C8::Of(&it, &self->children);
    PlacedObject* n = Next_12F8C8::Of(&it);
    if (n == 0 || IsObjectOfKind(n, 0x7E) == 0) {
        g_activeListFrames = (ListFrame*)it.saved;
        return;
    }
    if (Next_12F8C8::Of(&it) != 0) {
        g_activeListFrames = (ListFrame*)it.saved;
        return;
    }
    func_00128018(self, 0, (u8*)n + 0x40, &self->pos);
    self->mode = 1;
    n->desc->m03(n);
    g_activeListFrames = (ListFrame*)it.saved;
}

void func_0012F9B8(IdFilterObject* self)
{
    Quad_12F9B8 loc;
    PlacedObject* cur;
    UpdateCollider(self);
    if (self->pendingTarget != 0) {
        self->pendingTarget->desc02()->m20(self->pendingTarget, (Vec02*)&D_00248D30);
        self->pendingTarget->desc02()->m21(self->pendingTarget, (Vec02*)&D_00248D30);
        switch (self->mode) {
        case 1:
            self->pendingTarget->desc02()->m1D(self->pendingTarget, &self->pos);
            break;
        case 2: {
            PlacedObject* node = self->found;
            func_00128018(node->parent, 0, &node->link40, &loc);
            self->pendingTarget->desc02()->m1D(self->pendingTarget, (Vec02*)&loc);
            break;
        }
        }
        cur = self->pendingTarget;
        self->pendingTarget = 0;
        self->placedTarget = cur;
    }
}

s32 func_0012FA88(IdFilterObject* self, Collider* key)
{
    s32 hit;
    s32 i;
    s32 j;

    if (TestCollidersMayContact(self, key) != 0) {
        return 1;
    }
    for (i = 0; i < self->objectIds.count; i++) {
        if (MatchesObjectId(key, self->objectIds.items[i]) != 0) {
            break;
        }
    }
    if (i < self->objectIds.count) {
        hit = 1;
        goto tail;
    }
    for (j = 0; j < self->classIds.count; j++) {
        if (IsObjectOfKind(key, self->classIds.items[j]) != 0) {
            break;
        }
    }
    hit = j < self->classIds.count;
tail:
    if (self->acceptsListed != 0) {
        return hit;
    }
    return hit ^ 1;
}

ASM_FUNC(func_0012FB68);

void func_0012FCB0(IdFilterObject* a0, s32 a1)
{
    a0->objectIds.items[a0->objectIds.count++] = a1;
}

void func_0012FCD0(IdFilterObject* obj, s32 value) { obj->classIds.items[obj->classIds.count++] = value; }

StreamReader* func_0012FCF0(StreamReader* obj, s32 value)
{
    obj->sector = 0;
    obj->buffer = (value + 0x3F) & -64;
    obj->fileHandle = -1;
    obj->pendingDest = 0;
    obj->readyStart = 0;
    obj->total = 0;
    obj->remaining = 0;
    obj->pendingLength = 0;
    obj->usedLength = 0;
    obj->readyLength = 0;
    return obj;
}

void func_0012FD30(void* self, s32 flags)
{
    CloseStreamReader((StreamReader*)self);
    if (flags & 1) func_0018D778(self);
}

s32 func_0012FD78(void* self, KeyId* pair)
{
    return OpenSectorStream(self, pair->first, pair->second);
}

LINKER_REMNANT(func_0012FD98);

s32 func_0012FDA0(StreamReader *self, s32 a1, s32 a2) {
    self->sector = a1;
    s32 t = self->buffer;
    self->total = a2;
    self->remaining = a2;
    self->sourceKind = 1;
    self->readyStart = t;
    self->readyLength = 0;
    self->usedLength = 0;
    StartChunkRead(self);
    return 1;
}

void func_0012FDE8(StreamReader* a0)
{
    switch (a0->sourceKind) {
    case 0:
        if (a0->fileHandle >= 0) func_001F8C38(a0->fileHandle);
        a0->fileHandle = -1;
        break;
    case 1:
        if (IsReadPending(a0)) {
            func_002032C8(0);
            CommitChunk(a0);
        }
        a0->sector = 0;
        break;
    }
    a0->sourceKind = -1;
}

void func_0012FE70(StreamReader* self)
{
    if (IsReadPending(self) != 0) {
        return;
    }
    s32 size = self->remaining;
    if (size == 0) {
        return;
    }
    s32 clamp = 0x4000;
    if (!(size > 0x3FFF)) {
        clamp = size;
    }
    s32 base = self->buffer;
    if (self->readyStart == base) {
        base += 0x4000;
    }
    self->pendingLength = clamp;
    self->pendingDest = base;
    switch (self->sourceKind) {
    case 0:
        func_001F8DB8(self->fileRef, base, clamp);
        break;
    case 1:
        StartLowLevelDiscReadUntilAccepted(self->sectorRef, (s32)((u32)(clamp + 0x7FF) >> 11), base);
        break;
    }
}

s32 func_0012FF10(StreamReader* a0)
{
    return a0->pendingLength != 0;
}

s32 func_0012FF20(StreamReader* a0)
{
    s32 r = 0;
    s32 done = 0;
    if (a0->readyLength == a0->usedLength && IsReadPending(a0)) {
        switch (a0->sourceKind) {
        case 0: {
            s32 tmp;
            done = func_001F92E8(a0->fileHandle, 1, &tmp);
            r = tmp == 0;
            break;
        }
        case 1:
            r = func_002032C8(1) == 0;
            if (r) done = func_00203D90();
            break;
        }
    }
    if (done) {
        a0->pendingLength = 0;
        a0->pendingDest = 0;
        r = 0;
    }
    return r;
}

void func_0012FFE8(StreamReader* self)
{
    if (PollChunkRead(self) == 0) {
        return;
    }
    if (self->sourceKind == 1) {
        self->sector += self->pendingLength / 2048;
    }
    s32 v = self->pendingLength;
    self->remaining -= v;
    self->readyLength = v;
    self->readyStart = self->pendingDest;
    self->pendingLength = 0;
    self->pendingDest = 0;
    self->usedLength = 0;
}

void func_00130070(StreamReaderWindow* self)
{
    switch (self->sourceKind) {
    case 0:
        StartChunkRead(self);
        CommitChunk(self);
        break;
    case 1:
        CommitChunk(self);
        StartChunkRead(self);
        break;
    }
}

void func_001300D8(StreamReaderWindow* a0, s32 a1)
{
    a0->usedLength += a1;
}

s32 func_001300E8(BaseObject* list, s32 key)
{
    const Desc01* node = list->desc;
    while (node != 0) {
        if (node->id == key) {
            return 1;
        }
        node = (const Desc01*)node->parent;
    }
    return 0;
}

void func_00130110(BaseObject* self)
{
    if (self->f04 == 0) {
        void* v = NewKeyedList();
        self->f04 = v;
        AddMarkRootList(D_00259F38, v);

    }
}

void func_00130158(Holder_130158* holder, s32* out)
{
    *out = holder->inner->value;
}

void func_00130168(f32 delta, f32 diff, f32 scale, f32 p4, f32 p18, f32 p1C, f32 p24, f32 p2C, f32 p30, f32* outF, f32* outI, s32 zero)
{
    f32 c[4];
    if (diff < 0.0001f) {
        diff = 0.0f;
    } else if (delta - diff < 0.0001f) {
        diff = 1.0f;
    } else {
        f32 d3 = (delta - p2C) * 3.0f;
        f32 g3 = p18 * 3.0f;
        f32 lo = 0.0f;
        f32 hi = 1.0f;
        s32 k = 0;
        c[2] = g3;
        c[3] = -diff;
        f32 a = g3 - d3;
        f32 b = d3 - g3;
        b = b - g3;
        a = a + delta;
        c[1] = b;
        c[0] = a;
        do {
            f32 m = lo + 1.0f / (f32)(1 << (k + 1));
            f32 v = m * (m * (m * c[0] + c[1]) + c[2]) + c[3];
            if (v < 0.0f) {
                lo = m;
            } else if (0.0f < v) {
                hi = m;
            } else {
                break;
            }
        } while (++k < 16);
        diff = (lo + hi) * 0.5f;
    }
    if (outF != 0) {
        f32 a3 = p1C * 3.0f;
        f32 b3 = p30 * 3.0f;
        c[3] = p4;
        c[0] = a3 - p4 - b3 + p24;
        c[1] = p4 * 3.0f - p1C * 6.0f + b3;
        c[2] = p4 * -3.0f + a3;
        *outF = diff * (diff * (diff * c[0] + c[1]) + c[2]) + p4;
    }
    if (outI != 0) {
        c[0] = p4 * -3.0f + p1C * 9.0f - p30 * 9.0f + p24 * 3.0f;
        c[1] = p4 * 6.0f - p1C * 12.0f + p30 * 6.0f;
        c[2] = p4 * -3.0f + p1C * 3.0f;
        f32 num = diff * (diff * c[0] + c[1]) + c[2];
        f32 d3 = (delta - p2C) * 3.0f;
        f32 g3 = p18 * 3.0f;
        c[2] = g3;
        c[0] = g3 * 3.0f - d3 * 3.0f + delta * 3.0f;
        c[1] = g3 * -4.0f + (d3 + d3);
        f32 den = diff * (diff * c[0] + c[1]) + c[2];
        *outI = num * scale / den;
    }
}

void func_001303F0(f32* p0, f32* p1, f32* p2, f32 dur, f32 t, f32 e, f32 a, f32 b, f32 c, f32 dd)
{
    f32 u = t / dur;
    f32 v = 1.0f - u;
    f32 span = c - a;
    if (p0 != 0) {
        f32 uv = u * v;
        f32 vv = v * v;
        f32 uu = u * u;
        f32 uvv = uv * v;
        f32 vvv = vv * v;
        f32 uuv = uu * v;
        f32 t5 = uvv * 3.0f;
        f32 uvd = uvv * dur;
        f32 t4 = uuv * 3.0f;
        f32 t0 = vvv + t5;
        f32 uuu = uu * u;
        f32 p2b = uvd * b;
        f32 p1a = t0 * a;
        f32 q = uuv * dur;
        f32 t3 = uuu + t4;
        f32 s = p1a + p2b;
        f32 qd = q * dd;
        f32 t3c = t3 * c;
        f32 r = s - qd;
        *p0 = r + t3c;
    }
    if (p1 != 0) {
        f32 t1 = (u * (6.0f * v)) / dur * span;
        f32 t2 = (1.0f - (u * (4.0f - 3.0f * u))) * b;
        f32 w2 = 3.0f * u + -2.0f;
        f32 t3 = (u * w2) * dd;
        *p1 = ((t1 + t2) + t3) * e;
    }
    if (p2 != 0) {
        f32 dd2 = dur * dur;
        f32 ee = e * e;
        f32 s1 = (6.0f - 12.0f * u) / dd2 * span;
        f32 s2 = (6.0f * u - 4.0f) / dur * b;
        f32 s3 = (6.0f * u - 2.0f) / dur * dd;
        *p2 = ((s1 + s2) + s3) * ee;
    }
}

ASM_FUNC(func_00130540);

ASM_FUNC(func_00130748);

void func_00130B48(f32 k, Self_130B48* self, u8* a1, u8* a2, u8* a3, s32 count, Out_130B48* out, f32 start, f32 end)
{
    f32 step = (end - start) / (f32)(count - 1);
    f32 cur = start;
    s32 i;
    for (i = 0; i < count; i++) {
        func_00130540(k, self, a1, a2, a3, cur, 1.0f, (s32)(out + i), 0, 0);
        cur += step;
    }
}

void func_00130C20(s32 a, s32 b, s32 c, s32 d, f32 x, f32 y)
{
    u8 buf[0x140];
    SampleCurvePoints(a, b, c, d, x, 0.0f, y, 20, buf);
    AccumulateSegmentLengths(20, buf, 0);
}

INCLUDE_RODATA(D_00249C90);

INCLUDE_ASM(func_00130C58);
