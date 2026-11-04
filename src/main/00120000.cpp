// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "c02.h"
#include "c2f.h"
#include "c20.h"
#include "c6c.h"
#include "c83.h"
#include "t2195.h"
#include "t2196.h"

void func_0011F850(T2196_Weight** axis, s32* outCount, f32** outTimes);

void func_00120110(T2196_6E8* self, s32* outCount, f32** outTimes)
{
    func_0011F850(self->axis, outCount, outTimes);
}

struct Buffer_00120130 { u8 bytes[0x20]; };
typedef void (*Finish_00120130)(C02* self, void* output, void* state);
extern void func_0011F9F8(s32, Key2196_Vec*, s32, void*, void*);
extern void func_00188A20(void*, void*);
extern void func_001EDE38(void*, void*, void*);

void func_00120130(T2196_6F8* self, C02* parent, s32 mode,
                   void* output, void* state)
{
    Buffer_00120130 buffer;
    func_0011F9F8(self->count, self->keys, mode,
                  output ? &buffer.bytes[0] : 0,
                  state ? &buffer.bytes[0x10] : 0);
    if (output) {
        func_00188A20(&buffer.bytes[0], output);
    }
    if (state) {
        func_001EDE38(&buffer.bytes[0], &buffer.bytes[0x10], state);
    }
    if (parent) {
        ((Finish_00120130)parent->desc02()->m29)(parent, output, state);
    }
}

extern void func_0011F9F8(s32, Key2196_Vec*);
extern void func_0011FB98(s32, Key2196_Vec*, s32*, f32**);

void func_001201D0(T2196_6F8* self)
{
	func_0011F9F8(self->count, self->keys);
}

void func_001202C0(T2196_6F8* self, s32* outCount, f32** outTimes)
{
	func_0011FB98(self->count, self->keys, outCount, outTimes);
}

struct Result_001202F0 { f32 x; f32 y; f32 z; };
struct Output_001202F0 { f32 x; u8 pad4[0x10]; f32 y; u8 pad18[0x10]; f32 z; };
extern void func_0011F6B0(T2196_Weight**, C02*, void*, Vec02*, void*, s32, f32, f32);
extern void func_001F5C0C(void*, s32, s32);

void func_001202F0(T2196_718* self, C02* second, void* third,
                   Output_001202F0* output, f32 factor)
{
    Result_001202F0 result;
    func_0011F6B0(self->axis, second, third, &self->base,
                  output ? &result : 0, 0, factor, 1.0f);
    if (output) {
        func_001F5C0C(output, 0, 0x30);
        output->x = result.x;
        output->y = result.y;
        output->z = result.z;
    }
}

void func_0011F798(T2196_Weight** a, Vec02* b, Stream83* c);

void func_00120360(T2196_718* self, Stream83* p)
{
    func_0011F798(self->axis, &self->base, p);
}

void func_00120388(T2196_718* self, s32* outCount, f32** outTimes)
{
	func_0011F850(self->axis, outCount, outTimes);
}

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
extern void func_001F5C0C(void*, s32, s32);

void func_001203A8(T2196_728* self, C02* unused, void* mode,
                   Output_001203A8* output, f32 factor)
{
    Result_001203A8 result;
    func_0011F9F8(self->count, self->keys, mode,
                  output ? &result.first : 0, 0, factor, 1.0f);
    if (output) {
        func_001F5C0C(output, 0, 0x30);
        output->first = result.first;
        output->second = result.second;
        output->third = result.third;
    }
}

extern void func_0011FA88(s32*, Key2196_Vec**, Stream83*);

void func_00120418(T2196_728* self, Stream83* stream)
{
	func_0011FA88(&self->count, &self->keys, stream);
}

void func_00120440(T2196_728* self, s32* outCount, f32** outTimes)
{
	func_0011FB98(self->count, self->keys, outCount, outTimes);
}

extern void* func_001B5EE0(void*);

T2195* func_00121228(C6C* root, C02* value, const T2195_Vt* table)
{
	T2195* node = (T2195*)func_001B5EE0(&root->pool1B20);
	node->vt = table;
	table->init(node, value);
	return node;
}

extern C6C* D_00275710;

void func_0018D800(T2195* self, T2195* src, s32 size);

void func_001212D8(T2195* self, T2195* src)
{
    Link2195 tmp = self->link;
    C02* saved = self->owner;
    func_0018D800(self, src, D_00275710->pool1B20.size);
    self->link = tmp;
    self->owner = saved;
}

void func_00121568(T2195* self, f32* value, f32* slope)
{
	Rec2195_224* rec = (Rec2195_224*)self->owner->f224;
	*value = rec->f8C;
	*slope = 0.0f;
}

f32 func_001215A8(T2195* self, s32 index)
{
	return (*(f32**)((u8*)self->owner + 0x274))[index];
}

// Gives the owner the position and the orientation this attachment gives (slots 29, 30, 32, 33).
struct Locals_121648 {
    Vec02 pos;
    Vec02 vec;
    Mat02 rot;
};

void func_00121648(T2195* self, s32 flag)
{
    Locals_121648 loc;
    C02* s2 = self->owner;

    if (self == s2->f1EC) {
        if (flag != 0 || self->mode0 == 2) {
            self->vt->getPos(self, &loc.pos, &loc.vec, 0.0f);
            s2->desc02()->m1D(s2, &loc.pos);
            s2->desc02()->m20(s2, &loc.vec);
        }
    }
    if (self == s2->f1F0) {
        if (flag != 0 || self->mode1 == 2) {
            self->vt->getRot(self, &loc.rot, &loc.pos, 0.0f);
            s2->desc02()->m1E(s2, &loc.rot);
            s2->desc02()->m21(s2, &loc.pos);
        }
    }
}

void func_001226D8(T2195* self)
{
    if (self->mode0 == 7) {
        self->mode0 = 3;
    }
    if (self->mode1 == 7) {
        self->mode1 = 3;
    }
}

// The owner's slot 44 (Desc02::m28) and 45 (m29) are told what was asked.
typedef void (*Told_1227B0)(C02* self, Vec02* a, Vec02* b);

void func_001227B0(T2195_588* src, Vec02* d0, Vec02* d1)
{
    *d0 = src->pos;
    *d1 = src->vec;
    C02* obj = src->owner;
    Told_1227B0 fn = (Told_1227B0)obj->desc02()->m28;
    if (fn != 0) {
        fn(obj, d0, d1);
    }
}

typedef void (*Told_1227F0)(C02* self, Mat02* b, Vec02* q);

void func_001227F0(T2195_588* src, Mat02* d0, Vec02* d1)
{
    d0->r[0] = src->rot.r[0];
    d0->r[1] = src->rot.r[1];
    d0->r[2] = src->rot.r[2];
    *d1 = src->v70;
    C02* obj = src->owner;
    Told_1227F0 fn = (Told_1227F0)obj->desc02()->m29;
    fn(obj, d0, d1);
}

void func_00122840(T2195_588* self, f32* first, f32* second)
{
	*first = self->f80;
	*second = self->f84;
}

void func_00122858(T2195_588* self, Mat02* output)
{
	output->r[0] = self->m90.r[0];
	output->r[1] = self->m90.r[1];
	output->r[2] = self->m90.r[2];
}

f32 func_00122878(T2195_588* self, s32 i)
{
    return self->valuesC4[i];
}

typedef void (*Told_122920)(C02* self);

void func_00122920(T2195_5B0* self, Vec02* first, Vec02* second)
{
	*first = *self->pos;
	*second = *self->vec;
	Told_122920 callback = (Told_122920)self->owner->desc02()->m28;
	if (callback)
		callback(self->owner);
}

typedef void (*Told_122968)(C02* self, Mat02* a, Vec02* b);

void func_00122968(T2195_5B0* self, Mat02* d1, Vec02* d2)
{
    Mat02* s = self->rot;
    d1->r[0] = s->r[0];
    d1->r[1] = s->r[1];
    d1->r[2] = s->r[2];
    *d2 = *self->vec2;
    ((Told_122968)self->owner->desc02()->m29)(self->owner, d1, d2);
}

void func_001229C0(T2195_5B0* self, f32* a, f32* b)
{
    *a = *self->p2C;
    *b = *self->p30;
}

void func_001229E0(T2195_5B0* self, Mat02* dst)
{
    Mat02* s = self->ident;
    dst->r[0] = s->r[0];
    dst->r[1] = s->r[1];
    dst->r[2] = s->r[2];
}

f32 func_00122A00(T2195_5B0* self, s32 i)
{
    return self->values[i];
}

f32 func_00122D90(void)
{
    return 0.0f;
}

void func_00121338(T2195* self, C02* a1);

void func_00122DA0(T2195_600* self, C02* a1)
{
    func_00121338(self, a1);
    self->f1C = 1.0f;
    self->f20 = 0.25f;
}

void func_00152600(void* list, void* item);
void func_00121358(T2195* self, s32 flags);

void func_00122F28(T2195_7C0* self, s32 a1)
{
    Player2195* o = self->player;
    func_00152600(&o->list44, self);
    if (o->driven == self) {
        o->driven = 0;
    }
    func_00121358(self, a1);
}

extern f32 D_0026185C[];
void func_001214B8(T2195* self, Vec02* a1, Vec02* a2);
s32 func_0012E9E0(Player2195* t, f32* a, f32* b);

void func_00122FE0(T2195_7C0* self, Vec02* a1, Vec02* a2, f32 f)
{
    Player2195* track = self->player;
    Track83* e = &track->anim->tracks[self->index];
    if (e->pos != 0) {
        f32 tmp[2];
        if (f != 0.0f) {
            f32 c14 = track->time;
            f32 c18 = track->speed;
            tmp[1] = c18;
            tmp[0] = c14 + f * c18;
            func_0012E9E0(track, &tmp[0], &tmp[1]);
        } else {
            tmp[0] = track->time;
        }
        if (self->mode0 == 4) {
            f32 d = self->f18 - D_0026185C[0] - track->f10;
            if (0.0f < d) {
                tmp[0] = tmp[0] + d * track->speed;
            }
        }
        e->pos->vt->eval(e->pos, self->owner, 0, a1, a2, tmp[0], track->speed);
        return;
    }
    func_001214B8(self, a1, a2);
}

extern f32 D_0026185C[];
void func_00121508(T2195* self, Mat02* a, Vec02* b);
s32 func_0012E9E0(Player2195* t, f32* a, f32* b);

void func_00123120(T2195_7C0* self, Mat02* a1, Vec02* a2, f32 f)
{
    C02* p4 = self->owner;
    Player2195* track = self->player;
    Track83* e = &track->anim->tracks[self->index];
    if (e->rot != 0) {
        f32 tmp[2];
        if (f != 0.0f) {
            f32 c14 = track->time;
            f32 c18 = track->speed;
            tmp[1] = c18;
            tmp[0] = c14 + f * c18;
            func_0012E9E0(track, &tmp[0], &tmp[1]);
        } else {
            tmp[0] = track->time;
        }
        if (self->mode1 == 4) {
            f32 d = self->f18 - D_0026185C[0] - track->f10;
            if (0.0f < d) {
                tmp[0] = tmp[0] + d * track->speed;
            }
        }
        e->rot->vt->eval(e->rot, p4, 0, a1, a2, tmp[0], track->speed);
        return;
    }
    func_00121508(self, a1, a2);
}

f32 func_00123358(T2195_7C0* self, s32 index)
{
    Player2195* track = self->player;
    Track83* row = &track->anim->tracks[self->index];
    T2196_Weight** values = row->morph;
    T2196_Weight* object = values[index];
    f32 result;
    object->vt->eval(object, self->owner, 0, &result, 0, track->time, track->speed);
    return result;
}

extern void func_0013D278(void*);

void func_001233C0(C22* object)
{
	if (!object->hold)
		func_00123B18(object->counter);
	func_0013D278(object);
}

void func_00123400(C22* state, C2F* value)
{
    state->counter = value;
}

extern u8 D_00261420[];
void func_001B7968(C03* self);
s32 func_00140FF8(void* p);

void func_00123408(C2F* self)
{
    func_001B7968(self);
    self->state = -1;
    self->id6B0 = func_00140FF8(D_00261420);
}

extern void func_001BA130(C03*);

void func_00123540(C2F* object)
{
	s32 value = object->id6B0;
	func_001BA130(object);
	object->id6B0 = value;
}

typedef void (*VFn_123578)(void* self);
struct Obj_123578 { VFn_123578* vtbl; };
struct Ctx_123578 { u8 pad[0x2220]; s32 f2220; };

extern f32 D_0026185C[];
extern Ctx_123578* D_00262E10;

void func_001B93F8(C03* self);
void* func_0015A418(void* a, s32 b, void* c, void* d);
s32 func_001300E8(void* node, s32 kind);

void func_00123578(C2F* self)
{
    func_001B93F8(self);
    if (self->state == 2 && self->timeout != 0.0f) {
        if (self->timeout < D_0026185C[0] - self->stateTime) {
            func_00123888(self, 0);
            goto done;
        }
    }
    if (self->count1 > 0) {
        if (self->done == self->count1) {
            func_00123888(self, 1);
            goto done;
        }
    }
    if (self->state != 2) {
        goto done;
    }
    if (D_00262E10->f2220 != 9) {
        goto done;
    }
    for (s32 i = 0; i < self->count1; i++) {
        void* p = func_0015A418(self->world, 0x104, (void*)self->items1[i], self);
        if (p != 0 && func_001300E8(p, 0x22) != 0) {
            Obj_123578* o = (Obj_123578*)p;
            o->vtbl[0x130 / 4](p);
        }
    }
done:
    ;
}

void func_00123AB0(C2F* object, s32 mode)
{
    s32 mapped;
    switch (mode) {
    case 0: mapped = 2; break;
    case 1: mapped = 0; break;
    case 2: mapped = 1; break;
    default: return;
    }
    func_00123888(object, mapped);
}

void func_00123B18(C2F* counter)
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

void func_00123B28(C2F* self)
{
    for (s32 i = 0; i < self->outCount; i++) {
        Elem_123B28* e = (Elem_123B28*)self->outItems[i];
        if (e->f560 == -1 && e->vt->f134 != 0) {
            e->vt->f134(e, 0);
        }
    }
}

void func_00123C90(C2F* self, s32 value)
{
    u32 n = self->count1;
    if (n < 4) {
        self->items1[n] = value;
        self->count1 = n + 1;
    }
}

void func_00123CB8(C2F* self, s32 value)
{
    u32 n = self->count2;
    if (n < 16) {
        self->items2[n] = value;
        self->count2 = n + 1;
    }
}

void func_00123CE0(C2F* self, s32 value)
{
    u32 n = self->count3;
    if (n < 6) {
        self->items3[n] = value;
        self->count3 = n + 1;
    }
}

extern void func_0013EC00(void*, s32, void*, void*, void*, void*, void*);

void func_00123D08(C2F* object, void* a1, void* a2, void* a3, void* a4)
{
	func_0013EC00((u8*)object + 0x630, 8, (u8*)object + 0x62C,
			  a1, a2, a3, a4);
}

s32 func_001C1A28(void* a, void* b);

s32 func_00123D40(C2F* self, void* arg)
{
    s32 i;
    for (i = 0; i < self->outCount; i++) {
        if (func_001C1A28(arg, &self->outItems[i]) == 0) {
            return 0;
        }
    }
    return 1;
}

struct Record_001250C8 { u8 pad[8]; s32 value; };

void func_001250C8(C02* records)
{
    for (s32 i = 0; i < *(s32*)(records->sub22C + 0xC); i++) {
        Record_001250C8* record = (Record_001250C8*)(*(u8**)(records->sub22C + 0x14) + i * 0x28);
        record->value = -1;
    }
}

void func_00126A48(C02* object, u32 value)
{
    ListFrame frame;
    C02* child = (C02*)object->children.head;
    *(u32*)(object->sub22C + 0x3C) = value;
    *(u32*)(object->sub22C + 0x38) |= 2;
    while (child != 0) {
        if ((child->desc->flags & 1) != 0)
            func_00126A48(child, value);
        child = (C02*)child->next;
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
            func_00126BC0(child, value);
        child = child->next;
    }
}

void func_001215C0(T2195* obj)
{
    C02* node = obj->owner;
    C03* a2 = (node->desc->flags & 2) ? (C03*)node : 0;
    s8 b2C9 = node->b2C9;
    if (b2C9 != -1) {
        obj->mode0 = b2C9;
    } else {
        if (a2 == 0 || a2->mode450 == 3) {
            obj->mode0 = 2;
        } else {
            obj->mode0 = 3;
        }
    }
    s8 b2CA = node->b2CA;
    if (b2CA != -1) {
        obj->mode1 = b2CA;
        return;
    }
    if (a2 == 0 || a2->mode470 == 3) {
        obj->mode1 = 2;
    } else {
        obj->mode1 = 3;
    }
}

void func_00122F88(T2195_7C0* self, T2195* a1)
{
    Player2195* saved = self->player;
    Pair2195 tmp = self->w20;
    func_001212D8(self, a1);
    self->w20 = tmp;
    self->player = saved;
}

struct Child_00123BB0 { void** vt; };

void func_00123BB0(C2F* self)
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

void func_00123C20(C2F* self)
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

extern void func_00188A20(void*, void*);
extern void func_00189150(void*, void*, void*);
extern void func_00188D28(void*, void*, void*);

void func_001201F0(T2196_6F8* self, Stream83* arg)
{
    Locals_001201F0 loc;
    s32 result;

    func_0011FA88(&self->count, &self->keys, arg);
    if (self->count < 2) {
        result = 1;
    } else {
        func_00188A20((u8*)self->keys + 0x10, loc.a);
        u8* tail = (u8*)((self->count << 6) + (s32)self->keys) - 0x30;
        func_00188A20(tail, loc.b);
        func_00189150(loc.a, loc.b, loc.c);
        func_00188D28(loc.c, &loc.first, loc.d);
        result = (loc.first < 0.01f) ? 1 : 0;
    }
    self->closed = result;
}

struct Owner_122488 { u8 pad0[0x270]; f32* values; u8 pad1[0x20]; s32 flag; };

extern f32 D_00260E60[4];
extern f32 D_0026186C;
extern f32 D_00261860;
extern f32 func_001EA4B8(void*, s32, f32, f32, f32);

void func_00122488(T2195* self, s32 val)
{
    f32 ret = self->vt->getIndexed(self, val);
    switch (self->mode3) {
    case 2:
        ((Owner_122488*)self->owner)->values[val] = ret;
        break;
    case 3: {
        f32 cur = ((Owner_122488*)self->owner)->values[val];
        f32 limit = ((Owner_122488*)self->owner)->flag ? D_0026186C : D_00261860;
        ((Owner_122488*)self->owner)->values[val] = func_001EA4B8(D_00260E60, 0, cur, ret, limit);
        break;
    }
    }
}


void func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);
void func_00124A48(void* self);
s32 func_001300E8(void* node, s32 kind);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
void func_00182ED8(void* a);

struct Frame_123448 { s32 f00; s32 f04; s32 f08; s32 f0C; };

void func_00123448(C2F* self)
{
    Frame_123448 fr;
    s32 s0;
    func_001DBCC8(self->world, (void*)func_001236C8, self, 0, 0);
    func_00124A48(self);
    s32 e = (s32)&self->children;
    fr.f04 = e;
    fr.f00 = e;
    s32 link = *(s32*)(e + 8);
    s32 old = (s32)D_0027B314;
    fr.f0C = old;
    fr.f08 = link;
    D_0027B314 = (ListFrame*)&fr;
    s32 head = *(s32*)e;
    fr.f04 = head + fr.f08;
    s0 = head;
    if (s0 != 0) {
        do {
            if (func_001300E8((void*)s0, 0x88) != 0) {
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
        self->f55C = func_001B6290(self->found558, self, -1, 1);
        func_00182ED8(self->found558);
    }
    D_0027B314 = (ListFrame*)fr.f0C;
}

void func_00121568(T2195* self, f32* value, f32* slope);

void func_00122C48(T2195* self, f32* a1, f32* a2)
{
    T2195* p = self;
    while ((p = p->link.next) != 0) {
        s8 f = p->mode1;
        if (f == 0) { p = 0; break; }
        if (f != -1) break;
    }
    if (p != 0) {
        p->vt->getValue(p, a1, a2);
    } else {
        func_00121568(self, a1, a2);
    }
}

extern void func_00121568(T2195* self, f32* a1, f32* a2);

void func_00123270(T2195_7C0* self, f32* a1, f32* a2)
{
    f32* saved = a1;
    C02* f4 = self->owner;
    Player2195* player = self->player;
    Track83* e = &player->anim->tracks[self->index];
    T2196_Weight* target = e->weight;
    if (target) {
        target->vt->eval(target, f4, 0, saved, a2, player->time, player->speed);
    } else {
        func_00121568(self, saved, a2);
    }
}

extern void func_00121580(T2195* self, Mat02* a1);

void func_001232E8(T2195_7C0* self, Mat02* a1)
{
    Mat02* saved = a1;
    C02* f4 = self->owner;
    Player2195* player = self->player;
    Track83* e = &player->anim->tracks[self->index];
    T2196_Scale* target = e->scale;
    if (target) {
        target->vt->eval(target, f4, 0, saved, player->time);
    } else {
        func_00121580(self, saved);
    }
}

typedef void (*VFn_1236C8)(void* self, void* arg);
struct Obj_1236C8 { VFn_1236C8* vt; };
extern u8 D_00261420[];
void* func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
s32 func_001300E8(void* node, s32 kind);
void func_00123400(C22* node, C2F* value);
void func_001CAD40(void* node, void* self);
s32 func_00141008(void* table, s32 v);

void func_001236C8(C2F* self)
{
    s32 kept = 0;
    s32 i;
    for (i = 0; i < self->count1; i++) {
        void* node = func_0015A418(self->world, 0x104, self->items1[i], self);
        if (node && func_001300E8(node, 0x22)) {
            func_00123400((C22*)node, self);
            kept++;
        }
    }
    self->count1 = kept;
    for (i = 0; i < self->count2; i++) {
        void* node = func_0015A418(self->world, 0x104, self->items2[i], self);
        if (node && func_001300E8(node, 0x30)) {
            s32 idx = self->outCount;
            self->outItems[idx] = (C03*)node;
            self->outCount = idx + 1;
            ((Obj_1236C8*)node)->vt[0x140 / 4](node, self);
        }
    }
    for (i = 0; i < self->count3; i++) {
        void* node = func_0015A418(self->world, 0x104, self->items3[i], self);
        if (node && func_001300E8(node, 8)) {
            func_001CAD40(node, self);
        }
    }
    if (func_00141008(D_00261420, self->id6B0)) {
        func_00123888(self, 1);
    } else {
        func_00123888(self, 0);
    }
}

extern f32 D_0026185C[];
extern u8 D_002623D8[];
extern u8 D_00261420[];

void func_001BF788(s32 a, s32 b);
void func_001BF048(s32 a);
void func_0013ECB0(void* a, s32 b, void* c, void* d, s32 e);
void func_00160D00(void* p);
void func_001B64D8(void* a, s32 b);
void func_001B6628(void* a, s32 b);
s32 func_00141008(void* a, s32 b);
void func_00141040(void* a, s32 b);
void func_001837E0(C01* self, s32 a, s32 b, s32 c);
s32 func_001BEEF8(s32 a);
void func_00160CF0(void* p);
void func_001BFCD8(s32 a0, void* a1, C2F* a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

void func_00123888(C2F* self, s32 mode)
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
    func_001BF788(self->f620, 0);
    func_001BF048(self->f624);
    func_0013ECB0(self->world, self->count62C, self->table630, self, 0);
    if (mode == 1) {
        func_00160D00(D_002623D8);
    }
store:
    self->state = mode;
    self->stateTime = D_0026185C[0];
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
        func_001B64D8(self->f55C, 0x21A);
    }
    func_00123B28(self);
    return;
arm1:
    if (self->f55C != 0) {
        func_001B6628(self->f55C, 0x220);
    }
    func_00123BB0(self);
    if (func_00141008(D_00261420, self->id6B0) != 0) {
        func_001837E0(self, 0x16, 0, 0);
    } else {
        func_001837E0(self, 3, 0, 0);
    }
    func_00141040(D_00261420, self->id6B0);
    return;
arm2:
    if (self->f55C != 0) {
        func_001B64D8(self->f55C, 0x21F);
    }
    if (self->f628 == 0) {
        func_001BFCD8(0x15, &self->f620, self, 0, 8000.0f, 5000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
    self->f624 = func_001BEEF8(0x6B);
    func_00123C20(self);
    func_0013ECB0(self->world, self->count62C, self->table630, self, 1);
    func_001837E0(self, 2, 0, 0);
    func_00160CF0(D_002623D8);
}

// The position curves' tables, defined at the end of this file.
extern const T2196_PosVt D_002196B8;
extern const T2196_PosVt D_002196C8;
extern const T2196_PosVt D_002196D8;
void* func_0018D5C0(s32 bytes);

T2196_Pos* func_00120FB0(s32 kind)
{
    T2196_Pos* p;
    switch (kind) {
    case 0:
        p = (T2196_Pos*)func_0018D5C0(0x30);
        p->vt = &D_002196B8;
        break;
    case 1:
        p = (T2196_Pos*)func_0018D5C0(0x14);
        p->vt = &D_002196C8;
        break;
    case 2:
        p = (T2196_Pos*)func_0018D5C0(0x18);
        p->vt = &D_002196D8;
        break;
    default:
        p = 0;
        break;
    }
    if (p != 0) {
        p->kind = kind;
    }
    return p;
}

extern u8 D_00248D30[];
void func_00152600(void* a, void* b);
void func_001BA500(void* a, void* b, void* c, void* d, s32 e);
void func_001274F8(void* a, void* b);
void func_00127590(void* a, void* b);
void func_001B5F28(void* a, void* b);

void func_00121358(T2195* self, s32 flags)
{
    C02* m = self->owner;
    s32 local[4];
    func_00152600(&m->list1E0, self);
    T2195* a = m->f1EC;
    T2195* b = m->f1F0;
    m->desc02()->m2B(m);
    if (self == a && m->f1EC == 0 && (flags & 1) != 0) {
        if ((m->desc->flags & 2) != 0) {
            func_001BA500(m, (u8*)m + 0x440, (u8*)m + 0x150, local, 0);
            m->desc02()->m20(m, (Vec02*)local);
        } else {
            func_001274F8(m, D_00248D30);
        }
    }
    if (self == b && m->f1F0 == 0 && (flags & 2) != 0) {
        if ((m->desc->flags & 2) != 0) {
            func_001BA500(m, (u8*)m + 0x460, (u8*)m + 0x160, local, 0);
            m->desc02()->m21(m, (Vec02*)local);
        } else {
            func_00127590(m, D_00248D30);
        }
    }
    func_001B5F28(&m->world->pool1B20, self);
}

extern u8 D_002483D0[];
void func_00121338(T2195* self, C02* a1);

void func_00122708(T2195_588* self, C02* src)
{
    func_00121338(self, src);
    self->pos = src->v190;
    self->rot.r[0] = src->m1A0.r[0];
    self->rot.r[1] = src->m1A0.r[1];
    self->rot.r[2] = src->m1A0.r[2];
    Rec2195_224* p = (Rec2195_224*)src->f224;
    if (p != 0) {
        if (p->fB0 & 0x20) {
            self->f80 = p->f8C;
        }
    }
    Vec02* table = (Vec02*)D_002483D0;
    self->m90.r[0] = table[0];
    self->m90.r[1] = table[1];
    self->m90.r[2] = table[2];
    self->countC0 = src->f26C;
    self->valuesC4 = *(f32**)((u8*)src + 0x274);
}

s32 func_00139970(f32 x, f32 period, s32 count, Pair2196* p, f32* out);
f32 func_001EA408(f32 a);

void func_00120AA8(T2196_698* o, C02* cam, s32 c, f32* out0, f32* out1, f32 dt, f32 scale)
{
    f32 sum1 = 0.0f;
    f32 v0 = sum1;
    f32 x0;
    f32 x1;
    f32 x2;
    f32* p0;
    f32* p1;
    if (out0) {
        p0 = &x0;
    } else {
        x0 = sum1;
        p0 = 0;
    }
    if (out1) {
        p1 = &x1;
    } else {
        x1 = 0.0f;
        p1 = 0;
    }
    BlendSeq2196* seq = o->seq;
    BlendCfg2196* cfg = o->cfg;
    f32 w = 0.0f;
    f32 t;
    s32 idx;
    if (!seq) {
        t = dt / cfg->length;
    } else {
        idx = func_00139970(dt, cfg->length, seq->count, seq->pairs, &x2);
        t = x2 / seq->pairs[idx].b;
    }
    for (s32 i = 0; i < cfg->count; i++) {
        BlendRec2196* e = (BlendRec2196*)(cfg->base + i * cfg->stride);
        if (e->weight == 0.0f)
            continue;
        T2196_Weight* tg = o->targets[i];
        if (!tg) {
            if (cam) {
                f32 r = func_001EA408(((Rec2195_224*)cam->f224)->f90 - v0);
                v0 += r * e->weight / (w + e->weight);
            }
        } else {
            f32 a, b;
            if (!seq) {
                f32 s = e->sub->length;
                b = s / cfg->length;
                a = t * s;
            } else {
                Pair2196* q = (Pair2196*)((u8*)e + seq->stride + idx * 8);
                b = q->b;
                a = q->a + t * b;
                if (e->sub->length < a)
                    a -= e->sub->length;
                b = b / seq->pairs[idx].b;
            }
            tg->vt->eval(tg, cam, c, p0, p1, a, b * scale);
            if (w == 0.0f) {
                v0 = x0;
            } else {
                f32 r = func_001EA408(func_001EA408(x0) - v0);
                v0 += r * e->weight / (w + e->weight);
            }
            sum1 += e->weight * x1;
        }
        w += e->weight;
        v0 = func_001EA408(v0);
    }
    if (out0)
        *out0 = v0;
    if (out1)
        *out1 = sum1;
}

s32 func_00139970(f32 x, f32 period, s32 count, Pair2196* p, f32* out);
f32 func_001EA408(f32 a);

void func_00120D58(T2196_6A8* o, C02* cam, s32 c, f32* out0, f32* out1, f32 dt, f32 scale)
{
    f32 sum1 = 0.0f;
    f32 sum0 = sum1;
    f32 x0;
    f32 x1;
    f32 x2;
    f32* p0;
    f32* p1;
    if (out0) {
        p0 = &x0;
    } else {
        x0 = sum1;
        p0 = 0;
    }
    if (out1) {
        p1 = &x1;
    } else {
        x1 = 0.0f;
        p1 = 0;
    }
    BlendSeq2196* seq = o->seq;
    BlendCfg2196* cfg = o->cfg;
    f32 t;
    s32 idx;
    if (!seq) {
        t = dt / cfg->length;
    } else {
        idx = func_00139970(dt, cfg->length, seq->count, seq->pairs, &x2);
        t = x2 / seq->pairs[idx].b;
    }
    for (s32 i = 0; i < cfg->count; i++) {
        BlendRec2196* e = (BlendRec2196*)(cfg->base + i * cfg->stride);
        f32 zero = 0.0f;
        if (e->weight == zero)
            continue;
        T2196_Weight* tg = o->targets[i];
        if (!tg) {
            if (cam)
                sum0 += e->weight * (*(f32**)((u8*)cam + 0x274))[o->index];
        } else {
            f32 a, b;
            if (!seq) {
                f32 s = e->sub->length;
                b = s / cfg->length;
                a = t * s;
            } else {
                Pair2196* q = (Pair2196*)((u8*)e + seq->stride + idx * 8);
                b = q->b;
                a = q->a + t * b;
                if (e->sub->length < a)
                    a -= e->sub->length;
                b = b / seq->pairs[idx].b;
            }
            tg->vt->eval(tg, cam, c, p0, p1, a, b * scale);
            sum0 += e->weight * x0;
            sum1 += e->weight * x1;
        }
    }
    if (out0)
        *out0 = sum0;
    if (out1)
        *out1 = sum1;
}

void func_00121338(T2195* self, C02* value)
{
	s8 m = -1;
	self->owner = value;
	self->mode2 = m;
	self->mode3 = -1;
	self->mode1 = m;
	self->mode0 = m;
}

extern const T2196_RotVt D_002196E8;
extern const T2196_RotVt D_002196F8;
extern const T2196_RotVt D_00219708;
void* func_0018D5C0(s32 bytes);

T2196_Rot* func_00121050(s32 kind) {
    T2196_Rot* p;
    switch (kind) {
    case 0:
        p = (T2196_Rot*)func_0018D5C0(0x30);
        p->vt = &D_002196E8;
        break;
    case 1:
        p = (T2196_Rot*)func_0018D5C0(0x14);
        p->vt = &D_002196F8;
        break;
    case 2:
        p = (T2196_Rot*)func_0018D5C0(0x1C);
        p->vt = &D_00219708;
        break;
    default:
        p = 0;
        break;
    }
    if (p) {
        p->kind = kind;
    }
    return p;
}

extern const T2196_ScaleVt D_00219718;
extern const T2196_ScaleVt D_00219728;
void* func_0018D5C0(u32 n);
T2196_Scale* func_001210F0(s32 kind)
{
    T2196_Scale* p;
    switch (kind) {
    case 0:
        p = (T2196_Scale*)func_0018D5C0(0x30);
        p->vt = &D_00219718;
        break;
    case 1:
        p = (T2196_Scale*)func_0018D5C0(0x10);
        p->vt = &D_00219728;
        break;
    default:
        p = 0;
        break;
    }
    if (p != 0) {
        p->kind = kind;
    }
    return p;
}

extern u8 D_00219560[];

T2195* func_00121280(T2195* self, C6C* a, C02* b)
{
    T2195* node = func_00121228(a, b, (const T2195_Vt*)D_00219560);
    node->vt->copy(node, self);
    return node;
}

typedef void (*Told_1214B8)(C02* self, Vec02* out);
extern u8 D_00248D30[];

void func_001214B8(T2195* self, Vec02* out1, Vec02* out2)
{
    *out1 = self->owner->v190;
    *out2 = *(Vec02*)D_00248D30;
    if (self->owner->desc02()->m28 != 0) {
        ((Told_1214B8)self->owner->desc02()->m28)(self->owner, out1);
    }
}

extern u8 D_002483D0[];

void func_00121580(T2195* unused, Mat02* out)
{
    Mat02* src = (Mat02*)D_002483D0;
    out->r[0] = src->r[0];
    out->r[1] = src->r[1];
    out->r[2] = src->r[2];
}

extern u8 D_00248D30[];
extern u8 D_002483D0[];

void func_00121338(T2195* self, C02* a1);

void func_00122890(T2195_5B0* self, C02* src)
{
    func_00121338(self, src);
    self->pos = &src->v190;
    self->rot = &src->m1A0;
    self->count = &src->f26C;
    self->vec = (Vec02*)D_00248D30;
    self->vec2 = (Vec02*)D_00248D30;
    self->values = *(f32**)((u8*)src + 0x274);
    Rec2195_224* o = (Rec2195_224*)src->f224;
    if (o != 0) {
        if (o->fB0 & 0x20) {
            self->p30 = (f32*)D_00248D30;
            self->p2C = &o->f8C;
        }
    }
    self->ident = (Mat02*)D_002483D0;
}

void func_00121338(T2195* self);

void func_00122A18(T2195_5D8* self)
{
    func_00121338(self);
    Vec02* src = (Vec02*)D_002483D0;
    Vec02* d1 = self->m40.r;
    Vec02* d2 = self->m90.r;
    self->m40.r[0] = src[0];
    d1[1] = src[1];
    d1[2] = src[2];
    self->m90.r[0] = src[0];
    d2[1] = src[1];
    d2[2] = src[2];
}

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
extern const T2196_WeightVt D_00219668 = { (T2196_WeightEval)func_0011F0C8, (T2196_WeightRead)func_0011EFC8, (T2196_WeightTimes)func_0011F180, 0 };
extern const T2196_WeightVt D_00219678 = { (T2196_WeightEval)func_0011F320, (T2196_WeightRead)func_0011F210, (T2196_WeightTimes)func_0011F3E8, 0 };
extern const T2196_WeightVt D_00219688 = { (T2196_WeightEval)func_0011F478, (T2196_WeightRead)func_0011F568, (T2196_WeightTimes)func_0011F620, 0 };
extern const T2196_WeightVt D_00219698 = { (T2196_WeightEval)func_00120AA8, 0, (T2196_WeightTimes)func_0011EFB0, 0 };
extern const T2196_WeightVt D_002196A8 = { (T2196_WeightEval)func_00120D58, 0, (T2196_WeightTimes)func_0011EFB0, 0 };
void* func_0018D5C0(T2196_Weight* n);

T2196_Weight* func_00121160(u32 kind)
{
    T2196_Weight* o;
    switch (kind) {
    case 0:
        o = (T2196_Weight*)func_0018D5C0((T2196_Weight*)0x10);
        o->vt = &D_00219668;
        break;
    case 1:
        o = (T2196_Weight*)func_0018D5C0((T2196_Weight*)0x10);
        o->vt = &D_00219678;
        break;
    case 3:
        o = (T2196_Weight*)func_0018D5C0((T2196_Weight*)0x14);
        o->vt = &D_00219698;
        break;
    case 4:
        o = (T2196_Weight*)func_0018D5C0((T2196_Weight*)0x18);
        o->vt = &D_002196A8;
        break;
    case 2:
        o = (T2196_Weight*)func_0018D5C0((T2196_Weight*)0x10);
        o->vt = &D_00219688;
        break;
    default:
        o = 0;
    }
    if (o)
        o->kind = kind;
    return o;
}

typedef void (*Told_121508)(C02* self, Mat02* out1, Vec02* out2);

extern u8 D_00248D30[];

void func_00121508(T2195* self, Mat02* out1, Vec02* out2)
{
    *out1 = self->owner->m1A0;
    *out2 = *(Vec02*)D_00248D30;
    ((Told_121508)self->owner->desc02()->m29)(self->owner, out1, out2);
}

extern const f32 D_002499F0 = 3.4028235e+38f;
extern u8 D_00260E70[];
extern u8 D_00260E80[];
extern u8 D_00260E90[];
extern u8 D_00260EA0[];
extern u8 D_00260EB0[];
extern u8 D_00260EC0[];

void func_00152438(void* list, s32 n);
void func_00182C18(C01* self);

// Two stores of the set-up written as small inline helpers, the shape that matches: a value
// passed as an int, and a matrix copied through its own pointer (as each copy's own register).
struct Init_00123ED0 {
    static void SetB2CA(C02* o, s32 value) { o->b2CA = value; }
    static void Copy(Mat02* dst, const Mat02* src) { *dst = *src; }
};

void func_00123ED0(C02* self)
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
    func_00182C18(self);
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
    Init_00123ED0::Copy(&self->rot, (const Mat02*)D_002483D0);
    Init_00123ED0::Copy(&self->m110, (const Mat02*)D_002483D0);
    Init_00123ED0::Copy(&self->m1A0, (const Mat02*)D_002483D0);
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
void func_0011FFA8();
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

f32 D_00260E60[4] = { 3.0f, 1.0f, 0.1f, 0.0f };
