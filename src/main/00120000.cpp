// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "placed_object.h"
#include "state_trigger.h"
#include "masked_collider.h"
#include "world.h"
#include "animation.h"
#include "attachment.h"
#include "t2196.h"

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

extern Ctx_123578* D_00262E10;

void func_001B93F8(Collider* self);
void* func_0015A418(void* a, s32 b, void* c, void* d);
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
void* func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
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

extern u8 D_00248D30[];
void func_00152600(void* a, void* b);
void func_001BA500(void* a, void* b, void* c, void* d, s32 e);
void func_001274F8(void* a, void* b);
void func_00127590(void* a, void* b);
void func_001B5F28(void* a, void* b);

extern u8 D_002483D0[];

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
extern const T2196_WeightVt D_00219668 = { (T2196_WeightEval)func_0011F0C8, (T2196_WeightRead)func_0011EFC8, (T2196_WeightTimes)func_0011F180, 0 };
extern const T2196_WeightVt D_00219678 = { (T2196_WeightEval)func_0011F320, (T2196_WeightRead)func_0011F210, (T2196_WeightTimes)func_0011F3E8, 0 };
extern const T2196_WeightVt D_00219688 = { (T2196_WeightEval)func_0011F478, (T2196_WeightRead)func_0011F568, (T2196_WeightTimes)func_0011F620, 0 };
extern const T2196_WeightVt D_00219698 = { (T2196_WeightEval)func_00120AA8, 0, (T2196_WeightTimes)func_0011EFB0, 0 };
extern const T2196_WeightVt D_002196A8 = { (T2196_WeightEval)func_00120D58, 0, (T2196_WeightTimes)func_0011EFB0, 0 };
void* func_0018D5C0(T2196_Weight* n);

typedef void (*Told_121508)(PlacedObject* self, Mat02* out1, Vec02* out2);

extern u8 D_00260E70[];
extern u8 D_00260E80[];
extern u8 D_00260E90[];
extern u8 D_00260EA0[];
extern u8 D_00260EB0[];
extern u8 D_00260EC0[];

void func_00152438(void* list, s32 n);
void func_00182C18(BaseObject* self);

// Two stores of the set-up written as small inline helpers, the shape that matches: a value
// passed as an int, and a matrix copied through its own pointer (as each copy's own register).
struct Init_00123ED0 {
    static void SetB2CA(PlacedObject* o, s32 value) { o->b2CA = value; }
    static void Copy(Mat02* dst, const Mat02* src) { *dst = *src; }
};

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_0011FC20();
void func_0011FC90();
void func_0011FDB8();
void func_0011FDD8();
void func_0011FE40();
void func_0011FED8();
void func_0011EF48();
void func_00120470();
void func_0011FF08();
void* func_0011FFA8();
void func_0011FFD8();
void func_0011EF68();
void func_0011EF70();
void func_00120700();
extern const T2196_PosVt D_002196B8 = { (T2196_PosEval)func_0011FC20, (T2196_PosRead)func_0011FC90, (T2196_PosTimes)func_0011FDB8, 0 };
extern const T2196_PosVt D_002196C8 = { (T2196_PosEval)func_0011FDD8, (T2196_PosRead)func_0011FE40, (T2196_PosTimes)func_0011FED8, 0 };
extern const T2196_PosVt D_002196D8 = { (T2196_PosEval)func_00120470, 0, (T2196_PosTimes)func_0011EF48, 0 };
extern const T2196_RotVt D_002196E8 = { (T2196_RotEval)func_0011FF08, (T2196_RotGet)func_0011FFA8, (T2196_RotRead)func_0011FFD8, (T2196_RotTimes)func_00120110 };
extern const T2196_RotVt D_002196F8 = { (T2196_RotEval)func_00120130, (T2196_RotGet)func_001201D0, (T2196_RotRead)func_001201F0, (T2196_RotTimes)func_001202C0 };
extern const T2196_RotVt D_00219708 = { (T2196_RotEval)func_00120700, (T2196_RotGet)func_0011EF68, 0, (T2196_RotTimes)func_0011EF70 };
extern const T2196_ScaleVt D_00219718 = { (T2196_ScaleEval)func_001202F0, (T2196_ScaleRead)func_00120360, (T2196_ScaleTimes)func_00120388, 0 };
extern const T2196_ScaleVt D_00219728 = { (T2196_ScaleEval)func_001203A8, (T2196_ScaleRead)func_00120418, (T2196_ScaleTimes)func_00120440, 0 };

