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

extern u8 D_00261420[];
void func_001B7968(Collider* self);
s32 func_00140FF8(void* p);

void func_00123408(StateTrigger* self)
{
    InitCollider(self);
    self->state = -1;
    self->id6B0 = TakeFlagTableIndex(g_flagTable);
}

extern void func_001BA130(Collider*);

void func_00123540(StateTrigger* object)
{
	s32 value = object->id6B0;
	CopyCollider(object);
	object->id6B0 = value;
}

typedef void (*VFn_123578)(void* self);
struct Obj_123578 { VFn_123578* vtbl; };
struct Ctx_123578 { u8 pad[0x2220]; s32 f2220; };

extern Ctx_123578* D_00262E10;

void func_001B93F8(Collider* self);
void* func_0015A418(void* a, s32 b, void* c, void* d);
s32 func_001300E8(void* node, s32 kind);

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
        void* p = FindFirstObjectById(self->world, 0x104, (void*)self->items1[i], self);
        if (p != 0 && IsObjectOfKind(p, 0x22) != 0) {
            Obj_123578* o = (Obj_123578*)p;
            o->vtbl[0x130 / 4](p);
        }
    }
done:
    ;
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

void func_00123B28(StateTrigger* self)
{
    for (s32 i = 0; i < self->outCount; i++) {
        Elem_123B28* e = (Elem_123B28*)self->outItems[i];
        if (e->f560 == -1 && e->vt->f134 != 0) {
            e->vt->f134(e, 0);
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

extern s32 func_0013EC00(void*, s32, void*, void*, void*, void*, void*);

void func_00123D08(StateTrigger* object, void* a1, void* a2, void* a3, void* a4)
{
	UpsertKeyedEntry((u8*)object + 0x630, 8, (u8*)object + 0x62C,
			  a1, a2, a3, a4);
}

s32 func_001C1A28(void* a, void* b);

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

struct Record_001250C8 { u8 pad[8]; s32 value; };

void func_001250C8(PlacedObject* records)
{
    for (s32 i = 0; i < *(s32*)(records->sub22C + 0xC); i++) {
        Record_001250C8* record = (Record_001250C8*)(*(u8**)(records->sub22C + 0x14) + i * 0x28);
        record->value = -1;
    }
}

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

struct Child_00123BB0 { void** vt; };

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

typedef void (*VFn_123C20)(void* self);
struct Item_123C20 { VFn_123C20* vtbl; };

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

void func_00121568(Attachment* self, f32* value, f32* slope);

extern void func_00121568(Attachment* self, f32* a1, f32* a2);

extern void func_00121580(Attachment* self, Mat02* a1);

typedef void (*VFn_1236C8)(void* self, void* arg);
struct Obj_1236C8 { VFn_1236C8* vt; };
void* func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_00123400(C22* node, StateTrigger* value);
void func_001CAD40(void* node, void* self);
s32 func_00141008(void* table, s32 v);

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

extern const f32 D_002499F0 = 3.4028235e+38f;
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

void func_00123ED0(PlacedObject* self)
{
    func_00152438(&self->children, 0x1C);
    func_00152438(&self->list60, 0x58);
    if (self->parent != 0) {
        self->bits24 = 1;
        self->bits26 = 0;
    } else {
        self->bits24 = 2;
        self->bits26 = 2;
    }
    InitObject(self);
    self->f80 = D_002499F0;
    self->f88 = 0x0FFFFFFF;
    self->f84 = D_002499F0;
    Init_00123ED0::SetB2CA(self, -1);
    self->b2C9 = -1;
    self->p20C = D_00260E70;
    self->p210 = D_00260E80;
    self->p214 = D_00260E90;
    self->p218 = D_00260EA0;
    self->p21C = D_00260EB0;
    self->p220 = D_00260EC0;
    self->b2C8 = 0;
    Init_00123ED0::Copy(&self->rot, (const Mat02*)g_identityMatrix);
    Init_00123ED0::Copy(&self->m110, (const Mat02*)g_identityMatrix);
    Init_00123ED0::Copy(&self->m1A0, (const Mat02*)g_identityMatrix);
    func_00152438(&self->list1E0, 8);
}

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

