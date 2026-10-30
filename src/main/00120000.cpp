// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

void func_0011F850(void* a, void* b);

void func_00120110(u8* self, void* p)
{
    func_0011F850(self + 0x20, p);
}

struct Owner_00120130 {
    u8 pad0[0xC];
    void* first;
    void* second;
};
struct Interface_00120130 { void** vtable; };
struct Buffer_00120130 { u8 bytes[0x20]; };
typedef void (*Finish_00120130)(void* self, void* output, void* state);
extern void func_0011F9F8(void*, void*, s32, void*, void*);
extern void func_00188A20(void*, void*);
extern void func_001EDE38(void*, void*, void*);

void func_00120130(Owner_00120130* self, Interface_00120130* parent, s32 mode,
                   void* output, void* state)
{
    Buffer_00120130 buffer;
    func_0011F9F8(self->first, self->second, mode,
                  output ? &buffer.bytes[0] : 0,
                  state ? &buffer.bytes[0x10] : 0);
    if (output) {
        func_00188A20(&buffer.bytes[0], output);
    }
    if (state) {
        func_001EDE38(&buffer.bytes[0], &buffer.bytes[0x10], state);
    }
    if (parent) {
        ((Finish_00120130)parent->vtable[0xB4 / 4])(parent, output, state);
    }
}

struct Arguments_001201D0 { u8 pad[0xC]; void* first; void* second; };
extern void func_0011F9F8(void*, void*);
extern void func_0011FB98(void*, void*, void*, void*);

void func_001201D0(Arguments_001201D0* args)
{
	func_0011F9F8(args->first, args->second);
}

struct Arguments_001202C0 { u8 pad[0xC]; void* first; void* second; };

void func_001202C0(Arguments_001202C0* args, void* value1, void* value2)
{
	func_0011FB98(args->first, args->second, value1, value2);
}

struct Result_001202F0 { f32 x; f32 y; f32 z; };
struct Output_001202F0 { f32 x; u8 pad4[0x10]; f32 y; u8 pad18[0x10]; f32 z; };
extern void func_0011F6B0(void*, void*, void*, void*, void*, s32, f32, f32);
extern void func_001F5C0C(void*, s32, s32);

void func_001202F0(void* first, void* second, void* third,
                   Output_001202F0* output, f32 factor)
{
    Result_001202F0 result;
    func_0011F6B0((u8*)first + 0x20, second, third, (u8*)first + 0x10,
                  output ? &result : 0, 0, factor, 1.0f);
    if (output) {
        func_001F5C0C(output, 0, 0x30);
        output->x = result.x;
        output->y = result.y;
        output->z = result.z;
    }
}

void func_0011F798(void* a, void* b, void* c);

void func_00120360(u8* self, void* p)
{
    func_0011F798(self + 0x20, self + 0x10, p);
}

void func_00120388(void* object, void* p)
{
	func_0011F850((u8*)object + 0x20, p);
}

struct Owner_001203A8 {
    u8 pad0[8];
    void* first;
    void* second;
};
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
extern void func_0011F9F8(void*, void*, void*, f32*, s32, f32, f32);
extern void func_001F5C0C(void*, s32, s32);

void func_001203A8(Owner_001203A8* self, void* unused, void* mode,
                   Output_001203A8* output, f32 factor)
{
    Result_001203A8 result;
    func_0011F9F8(self->first, self->second, mode,
                  output ? &result.first : 0, 0, factor, 1.0f);
    if (output) {
        func_001F5C0C(output, 0, 0x30);
        output->first = result.first;
        output->second = result.second;
        output->third = result.third;
    }
}

extern void func_0011FA88(void*, void*, void*);

void func_00120418(void* object, void* value)
{
	func_0011FA88((u8*)object + 8, (u8*)object + 0xC, value);
}

struct Arguments_00120440 { u8 pad[8]; void* first; void* second; };

void func_00120440(Arguments_00120440* args, void* value1, void* value2)
{
	func_0011FB98(args->first, args->second, value1, value2);
}

struct Root_00121228 { u8 pad[0x1B20]; };
struct CallbackObject_00121228 { void* callback; };
typedef void (*Callback_00121228)(void*, void*);
extern void* func_001B5EE0(void*);

void* func_00121228(Root_00121228* root, void* value, CallbackObject_00121228* callbackObject)
{
	void* node = func_001B5EE0((u8*)root + 0x1B20);
	*(void**)node = callbackObject;
	((Callback_00121228)callbackObject->callback)(node, value);
	return node;
}

struct __attribute__((packed)) Pair_1212D8 { s32 lo; s32 hi; };
struct Obj_1212D8 { u8 pad0[4]; s32 w4; Pair_1212D8 p8; };
struct Ctx_1212D8 { u8 pad[0x1B20]; s32 x; };
extern Ctx_1212D8* D_00275710;

void func_0018D800(Obj_1212D8* self, s32 a, s32 b);

void func_001212D8(Obj_1212D8* self, s32 a1)
{
    Pair_1212D8 tmp = self->p8;
    s32 saved = self->w4;
    func_0018D800(self, a1, D_00275710->x);
    self->p8 = tmp;
    self->w4 = saved;
}

struct Parent_00121568 { u8 pad[4]; void* child; };
struct Child_00121568 { u8 pad[0x224]; void* values; };
struct Value_00121568 { u8 pad[0x8C]; f32 value; };

void func_00121568(Parent_00121568* parent, f32* output, s32* clear)
{
	Value_00121568* value = (Value_00121568*)((u8*)((Child_00121568*)parent->child)->values);
	*output = value->value;
	*clear = 0;
}

struct Parent_001215A8 { u8 pad[4]; u8* data; };
struct Child_001215A8 { u8 pad[0x274]; f32* values; };

f32 func_001215A8(Parent_001215A8* parent, s32 index)
{
	return ((Child_001215A8*)parent->data)->values[index];
}

struct __attribute__((aligned(16))) Quad_121648 {
    s32 w[4];
};

struct Obj_121648 {
    void** vt;
    Obj_121648* parent;
    u8 pad0[8];
    s8 b10;
    s8 b11;
    u8 pad1[0x1EC - 0x12];
    Obj_121648* p1EC;
    Obj_121648* p1F0;
};

struct Locals_121648 {
    Quad_121648 l0;
    Quad_121648 l1;
    Quad_121648 l2;
    Quad_121648 spare[2];
};

void func_00121648(Obj_121648* self, s32 flag)
{
    Locals_121648 loc;
    Obj_121648* s2 = self->parent;

    if (self == s2->p1EC) {
        if (flag != 0 || self->b10 == 2) {
            ((void (*)(Obj_121648*, void*, void*, f32))self->vt[4])(self, &loc.l0, &loc.l1, 0.0f);
            ((void (*)(Obj_121648*, void*))s2->vt[0x84 / 4])(s2, &loc.l0);
            ((void (*)(Obj_121648*, void*))s2->vt[0x90 / 4])(s2, &loc.l1);
        }
    }
    if (self == s2->p1F0) {
        if (flag != 0 || self->b11 == 2) {
            ((void (*)(Obj_121648*, void*, void*, f32))self->vt[5])(self, &loc.l2, &loc.l0, 0.0f);
            ((void (*)(Obj_121648*, void*))s2->vt[0x88 / 4])(s2, &loc.l2);
            ((void (*)(Obj_121648*, void*))s2->vt[0x94 / 4])(s2, &loc.l0);
        }
    }
}

struct Flags_1226D8 {
    u8 pad[0x10];
    s8 a;
    s8 b;
};

void func_001226D8(Flags_1226D8* self)
{
    if (self->a == 7) {
        self->a = 3;
    }
    if (self->b == 7) {
        self->b = 3;
    }
}

struct __attribute__((aligned(16))) Quad_1227B0 {
    s32 w[4];
};

struct Vtbl_1227B0 {
    u8 pad[0xB0];
    void (*fn)(void*, Quad_1227B0*, Quad_1227B0*);
};

struct Obj_1227B0 {
    Vtbl_1227B0* vt;
};

struct Src_1227B0 {
    u8 pad0[4];
    Obj_1227B0* obj;
    u8 pad1[0x18];
    Quad_1227B0 lo;
    Quad_1227B0 hi;
};

void func_001227B0(Src_1227B0* src, Quad_1227B0* d0, Quad_1227B0* d1)
{
    *d0 = src->lo;
    *d1 = src->hi;
    Obj_1227B0* obj = src->obj;
    void (*fn)(void*, Quad_1227B0*, Quad_1227B0*) = obj->vt->fn;
    if (fn != 0) {
        fn(obj, d0, d1);
    }
}

struct __attribute__((aligned(16))) Quad_1227F0 {
    s32 w[4];
};

struct Block_1227F0 {
    Quad_1227F0 q[3];
};

struct Vtbl_1227F0 {
    u8 pad[0xB4];
    void (*fn)(void* self, Block_1227F0* b, Quad_1227F0* q);
};

struct Obj_1227F0 {
    Vtbl_1227F0* vt;
};

struct Src_1227F0 {
    u8 pad0[4];
    Obj_1227F0* obj;
    u8 pad1[0x38];
    Quad_1227F0 q40;
    Quad_1227F0 q50;
    Quad_1227F0 q60;
    Quad_1227F0 q70;
};

void func_001227F0(Src_1227F0* src, Block_1227F0* d0, Quad_1227F0* d1)
{
    d0->q[0] = src->q40;
    d0->q[1] = src->q50;
    d0->q[2] = src->q60;
    *d1 = src->q70;
    Obj_1227F0* obj = src->obj;
    void (*fn)(void*, Block_1227F0*, Quad_1227F0*) = obj->vt->fn;
    fn(obj, d0, d1);
}

struct Pair_00122840 { u8 pad[0x80]; f32 first; f32 second; };

void func_00122840(Pair_00122840* pair, f32* first, f32* second)
{
	*first = pair->first;
	*second = pair->second;
}

struct Quad_00122858 { s32 a, b, c, d; } __attribute__((aligned(16)));
struct Vectors_00122858 {
	u8 pad[0x90];
	Quad_00122858 first;
	Quad_00122858 second;
	Quad_00122858 third;
} __attribute__((aligned(16)));

void func_00122858(Vectors_00122858* vectors, Quad_00122858* output)
{
	output[0] = vectors->first;
	output[1] = vectors->second;
	output[2] = vectors->third;
}

struct Obj_122878 { u8 pad[0xC4]; f32* data; };

f32 func_00122878(Obj_122878* self, s32 i)
{
    return self->data[i];
}

struct Quad_00122920 { s32 a, b, c, d; } __attribute__((aligned(16)));
struct Interface_00122920 { void** vtable; };
struct Root_00122920 {
	u8 pad0[4];
	Interface_00122920* interface;
	u8 pad8[0x14];
	Quad_00122920* first;
	Quad_00122920* second;
};
typedef void (*Callback_00122920)(Interface_00122920*);

void func_00122920(Root_00122920* root, Quad_00122920* first, Quad_00122920* second)
{
	*first = *root->first;
	*second = *root->second;
	Callback_00122920 callback = (Callback_00122920)root->interface->vtable[44];
	if (callback)
		callback(root->interface);
}

struct __attribute__((aligned(16))) Quad_122968 { s32 a, b, c, d; };
typedef void (*VFn_122968)(void* self, void* a, void* b);
struct Obj_122968 { VFn_122968* vtbl; };
struct Self_122968 {
    u8 pad0[4];
    Obj_122968* obj;
    u8 pad1[0x1C];
    Quad_122968* src24;
    Quad_122968* src28;
};

void func_00122968(Self_122968* self, Quad_122968* d1, Quad_122968* d2)
{
    Quad_122968* s = self->src24;
    d1[0] = s[0];
    d1[1] = s[1];
    d1[2] = s[2];
    *d2 = *self->src28;
    self->obj->vtbl[45](self->obj, d1, d2);
}

struct Self_1229C0 {
    u8 pad[0x2C];
    f32* p2c;
    f32* p30;
};

void func_001229C0(Self_1229C0* self, f32* a, f32* b)
{
    *a = *self->p2c;
    *b = *self->p30;
}

struct __attribute__((aligned(16))) Quad_1229E0 { s32 a, b, c, d; };
struct Self_1229E0 {
    u8 pad[0x34];
    Quad_1229E0* src;
};

void func_001229E0(Self_1229E0* self, Quad_1229E0* dst)
{
    Quad_1229E0* s = self->src;
    dst[0] = s[0];
    dst[1] = s[1];
    dst[2] = s[2];
}

struct Self_122A00 {
    u8 pad[0x3C];
    f32* data;
};

f32 func_00122A00(Self_122A00* self, s32 i)
{
    return self->data[i];
}

f32 func_00122D90(void)
{
    return 0.0f;
}

struct Self_122DA0 {
    u8 pad0[0x1C];
    f32 f1c;
    f32 f20;
};

void func_00121338(void* self, s32 a1);

void func_00122DA0(Self_122DA0* self, s32 a1)
{
    func_00121338(self, a1);
    self->f1c = 1.0f;
    self->f20 = 0.25f;
}

struct Owner_122F28 {
    u8 pad0[0x28];
    void* p28;
};
struct Self_122F28 {
    u8 pad0[0x1C];
    Owner_122F28* owner;
};

void func_00152600(void* list, void* item);
void func_00121358(void* self, void* a1);

void func_00122F28(Self_122F28* self, void* a1)
{
    Owner_122F28* o = self->owner;
    func_00152600((u8*)o + 0x44, self);
    if (o->p28 == self) {
        o->p28 = 0;
    }
    func_00121358(self, a1);
}

typedef s32 (*VFn_122FE0)(void* self, void* a, s32 b, s32 c, s32 d, f32 e, f32 f);
struct Obj_122FE0 { VFn_122FE0* vtbl; };
struct Table_122FE0 { u8 pad[0x3C]; u8* base; };
struct Track_122FE0 { u8 pad0[8]; Table_122FE0* table; u8 pad1[4]; f32 c10; f32 c14; f32 c18; };
struct Entry_122FE0 { u8 pad0[4]; Obj_122FE0* obj; u8 pad1[0x14]; };
struct Self_122FE0 {
    u8 pad0[4];
    void* p4;
    u8 pad1[8];
    s8 kind;
    u8 pad2[7];
    f32 f18;
    Track_122FE0* track;
    u8 pad3[8];
    s32 index;
};

extern f32 D_0026185C[];
s32 func_001214B8(Self_122FE0* self, s32 a1, s32 a2);
s32 func_0012E9E0(Track_122FE0* t, f32* a, f32* b);

s32 func_00122FE0(Self_122FE0* self, s32 a1, s32 a2, f32 f)
{
    Track_122FE0* track = self->track;
    Entry_122FE0* e = (Entry_122FE0*)(track->table->base + self->index * 0x1C);
    if (e->obj != 0) {
        f32 tmp[2];
        if (f != 0.0f) {
            f32 c14 = track->c14;
            f32 c18 = track->c18;
            tmp[1] = c18;
            tmp[0] = c14 + f * c18;
            func_0012E9E0(track, &tmp[0], &tmp[1]);
        } else {
            tmp[0] = track->c14;
        }
        if (self->kind == 4) {
            f32 d = self->f18 - D_0026185C[0] - track->c10;
            if (0.0f < d) {
                tmp[0] = tmp[0] + d * track->c18;
            }
        }
        return e->obj->vtbl[0](e->obj, self->p4, 0, a1, a2, tmp[0], track->c18);
    }
    return func_001214B8(self, a1, a2);
}

typedef s32 (*VFn_123120)(void* self, void* a, s32 b, s32 c, s32 d, f32 e, f32 f);
struct Obj_123120 { VFn_123120* vtbl; };
struct Table_123120 { u8 pad[0x3C]; u8* base; };
struct Track_123120 { u8 pad0[8]; Table_123120* table; u8 pad1[4]; f32 c10; f32 c14; f32 c18; };
struct Entry_123120 { u8 pad0[8]; Obj_123120* obj; u8 pad1[16]; };
struct Self_123120 { u8 pad0[4]; void* p4; u8 pad1[9]; s8 kind; u8 pad2[6]; f32 f18; Track_123120* track; u8 pad3[8]; s32 index; };

extern f32 D_0026185C[];
s32 func_00121508(Self_123120* self, s32 a, s32 b);
s32 func_0012E9E0(Track_123120* t, f32* a, f32* b);

s32 func_00123120(Self_123120* self, s32 a1, s32 a2, f32 f)
{
    void* p4 = self->p4;
    Track_123120* track = self->track;
    Entry_123120* e = (Entry_123120*)(track->table->base + self->index * 0x1C);
    if (e->obj != 0) {
        f32 tmp[2];
        if (f != 0.0f) {
            f32 c14 = track->c14;
            f32 c18 = track->c18;
            tmp[1] = c18;
            tmp[0] = c14 + f * c18;
            func_0012E9E0(track, &tmp[0], &tmp[1]);
        } else {
            tmp[0] = track->c14;
        }
        if (self->kind == 4) {
            f32 d = self->f18 - D_0026185C[0] - track->c10;
            if (0.0f < d) {
                tmp[0] = tmp[0] + d * track->c18;
            }
        }
        return e->obj->vtbl[0](e->obj, p4, 0, a1, a2, tmp[0], track->c18);
    }
    return func_00121508(self, a1, a2);
}

typedef void (*GetValue_00123358)(void* self, void* owner, s32 zero1,
                                  f32* output, s32 zero2, f32 a, f32 b);
struct Object_00123358 { GetValue_00123358* vtable; };
struct Table_00123358 { u8 pad0[0x3C]; u8* base; };
struct Track_00123358 {
    u8 pad0[8];
    Table_00123358* table;
    u8 pad0C[8];
    f32 f14;
    f32 f18;
};
struct Owner_00123358 {
    u8 pad0[4];
    void* p4;
    u8 pad8[0x14];
    Track_00123358* track;
    u8 pad20[8];
    s32 row;
};

f32 func_00123358(Owner_00123358* self, s32 index)
{
    Track_00123358* track = self->track;
    u8* row = track->table->base + self->row * 0x1C;
    u8* values = *(u8**)(row + 0x18);
    Object_00123358* object = *(Object_00123358**)(values + index * 4);
    f32 result;
    object->vtable[0](object, self->p4, 0, &result, 0, track->f14, track->f18);
    return result;
}

struct Object_001233C0 {
	u8 pad0[0x680];
	s32 state;
	u8 pad684[0x3C];
	void* counter;
};
struct Counter_00123B18;
void func_00123B18(Counter_00123B18*);
extern void func_0013D278(void*);

void func_001233C0(Object_001233C0* object)
{
	if (!object->state)
		func_00123B18((Counter_00123B18*)object->counter);
	func_0013D278(object);
}

struct Value_00123400 { u8 pad[0x6C0]; s32 value; };

void func_00123400(Value_00123400* state, s32 value)
{
	state->value = value;
}

extern u8 D_00261420[];
void func_001B7968(void* self);
s32 func_00140FF8(void* p);

struct Obj_123408 {
    u8 pad0[0x550];
    s32 f550;
    u8 pad1[0x6B0 - 0x554];
    s32 f6B0;
};

void func_00123408(Obj_123408* self)
{
    func_001B7968(self);
    self->f550 = -1;
    self->f6B0 = func_00140FF8(D_00261420);
}

extern void func_001BA130(void*);
struct Object_00123540 { u8 pad[0x6B0]; s32 value; };

void func_00123540(Object_00123540* object)
{
	s32 value = object->value;
	func_001BA130(object);
	object->value = value;
}

typedef void (*VFn_123578)(void* self);
struct Obj_123578 { VFn_123578* vtbl; };
struct Self_123578 {
    u8 pad0[0x14];
    void* p14;
    u8 pad1[0x550 - 0x18];
    s32 f550;
    f32 f554;
    u8 pad2[0x560 - 0x558];
    f32 f560;
    s32 count;
    void* items[45];
    s32 f61C;
};
struct Ctx_123578 { u8 pad[0x2220]; s32 f2220; };

extern f32 D_0026185C[];
extern Ctx_123578* D_00262E10;

void func_001B93F8(Self_123578* self);
void func_00123888(Self_123578* self, s32 mode);
void* func_0015A418(void* a, s32 b, void* c, void* d);
s32 func_001300E8(void* node, s32 kind);

void func_00123578(Self_123578* self)
{
    func_001B93F8(self);
    if (self->f550 == 2 && self->f560 != 0.0f) {
        if (self->f560 < D_0026185C[0] - self->f554) {
            func_00123888(self, 0);
            goto done;
        }
    }
    if (self->count > 0) {
        if (self->f61C == self->count) {
            func_00123888(self, 1);
            goto done;
        }
    }
    if (self->f550 != 2) {
        goto done;
    }
    if (D_00262E10->f2220 != 9) {
        goto done;
    }
    for (s32 i = 0; i < self->count; i++) {
        void* p = func_0015A418(self->p14, 0x104, self->items[i], self);
        if (p != 0 && func_001300E8(p, 0x22) != 0) {
            Obj_123578* o = (Obj_123578*)p;
            o->vtbl[0x130 / 4](p);
        }
    }
done:
    ;
}

struct Counter_00123B18 { u8 pad[0x61C]; s32 value; };
struct Self_123578;
extern void func_00123888(Self_123578*, s32);

void func_00123AB0(Self_123578* object, s32 mode)
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


void func_00123B18(Counter_00123B18* counter)
{
	counter->value++;
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

struct Obj_123B28 {
    u8 pad0[0x5BC];
    s32 count5BC;
    Elem_123B28* items[1];
};

void func_00123B28(Obj_123B28* self)
{
    for (s32 i = 0; i < self->count5BC; i++) {
        Elem_123B28* e = self->items[i];
        if (e->f560 == -1 && e->vt->f134 != 0) {
            e->vt->f134(e, 0);
        }
    }
}

struct SlotList4_00123C90 { u8 pad0[0x564]; u32 count; s32 items[4]; };

void func_00123C90(SlotList4_00123C90* self, s32 value)
{
    u32 n = self->count;
    if (n < 4) {
        self->items[n] = value;
        self->count = n + 1;
    }
}

struct SlotList16_00123CB8 { u8 pad0[0x578]; u32 count; s32 items[16]; };

void func_00123CB8(SlotList16_00123CB8* self, s32 value)
{
    u32 n = self->count;
    if (n < 16) {
        self->items[n] = value;
        self->count = n + 1;
    }
}

struct SlotList6_00123CE0 { u8 pad0[0x600]; u32 count; s32 items[6]; };

void func_00123CE0(SlotList6_00123CE0* self, s32 value)
{
    u32 n = self->count;
    if (n < 6) {
        self->items[n] = value;
        self->count = n + 1;
    }
}

extern void func_0013EC00(void*, s32, void*, void*, void*, void*, void*);

void func_00123D08(void* object, void* a1, void* a2, void* a3, void* a4)
{
	func_0013EC00((u8*)object + 0x630, 8, (u8*)object + 0x62C,
			  a1, a2, a3, a4);
}

struct TestList_00123D40 { u8 pad0[0x5BC]; s32 count; void* items[1]; };

s32 func_001C1A28(void* a, void* b);

s32 func_00123D40(TestList_00123D40* self, void* arg)
{
    s32 i;
    for (i = 0; i < self->count; i++) {
        if (func_001C1A28(arg, &self->items[i]) == 0) {
            return 0;
        }
    }
    return 1;
}
struct Records_001250C8 {
    u8 pad0[0x238];
    s32 count;
    u8 pad1[4];
    u8* data;
};

struct Record_001250C8 { u8 pad[8]; s32 value; };

void func_001250C8(Records_001250C8* records)
{
    for (s32 i = 0; i < records->count; i++) {
        Record_001250C8* record = (Record_001250C8*)(records->data + i * 0x28);
        record->value = -1;
    }
}

struct Object_00126A48 {
    u32* vtable;
    u8 pad0[0x18];
    Object_00126A48* next;
    u8 pad1[0x14];
    Object_00126A48* child;
    u8 pad2[0x22C];
    u32 state_flags;
    u32 state;
};

void func_00126A48(Object_00126A48* object, u32 value)
{
    u32 scratch[4];
    (void)scratch;
    Object_00126A48* child = object->child;
    object->state = value;
    object->state_flags |= 2;
    while (child != 0) {
        if ((child->vtable[2] & 1) != 0)
            func_00126A48(child, value);
        child = child->next;
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
    s32 scratch[4];
    (void)scratch;
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

struct Flags_1215C0 { u8 pad0[8]; s32 w8; };
struct Node_1215C0 {
    Flags_1215C0* flags;
    u8 pad4[0x2C9 - 4];
    s8 b2C9;
    s8 b2CA;
    u8 pad2CB[0x450 - 0x2CB];
    s32 w450;
    u8 pad454[0x470 - 0x454];
    s32 w470;
};
struct Obj_1215C0 {
    u8 pad0[4];
    Node_1215C0* node;
    u8 pad8[8];
    s8 b10;
    s8 b11;
};

void func_001215C0(Obj_1215C0* obj)
{
    Node_1215C0* node = obj->node;
    Node_1215C0* a2 = (node->flags->w8 & 2) ? node : 0;
    s8 b2C9 = node->b2C9;
    if (b2C9 != -1) {
        obj->b10 = b2C9;
    } else {
        if (a2 == 0 || a2->w450 == 3) {
            obj->b10 = 2;
        } else {
            obj->b10 = 3;
        }
    }
    s8 b2CA = node->b2CA;
    if (b2CA != -1) {
        obj->b11 = b2CA;
        return;
    }
    if (a2 == 0 || a2->w470 == 3) {
        obj->b11 = 2;
    } else {
        obj->b11 = 3;
    }
}

struct __attribute__((packed)) Pair_122F88 { s32 lo; s32 hi; };
struct Obj_122F88 { u8 pad0[0x1C]; s32 w1C; Pair_122F88 p20; };

void func_001212D8(void* self, s32 a1);

void func_00122F88(Obj_122F88* self, s32 a1)
{
    s32 saved = self->w1C;
    Pair_122F88 tmp = self->p20;
    func_001212D8(self, a1);
    self->p20 = tmp;
    self->w1C = saved;
}

struct Child_00123BB0 { void** vt; };
struct Obj_00123BB0 {
    u8 pad0[0x5BC];
    s32 count;
    Child_00123BB0* items[1];
};

void func_00123BB0(Obj_00123BB0* self)
{
    s32 i;
    for (i = 0; i < self->count; i++) {
        Child_00123BB0* c = self->items[i];
        void* fn = c->vt[0x138 / 4];
        if (fn != 0) {
            ((void (*)(void*))fn)(c);
        }
    }
}

typedef void (*VFn_123C20)(void* self);
struct Item_123C20 { VFn_123C20* vtbl; };
struct Mgr_123C20 { u8 pad[0x5BC]; s32 count; Item_123C20* items[1]; };

void func_00123C20(Mgr_123C20* self)
{
    s32 i;
    for (i = 0; i < self->count; i++) {
        Item_123C20* it = self->items[i];
        VFn_123C20 fn = it->vtbl[79];
        if (fn != 0) {
            fn(it);
        }
    }
}

struct Self_001201F0 { u8 pad0[8]; s32 flag; s32 count; u8* items; };
struct Locals_001201F0 {
    u8 a[0x30];
    u8 b[0x30];
    u8 c[0x30];
    u8 d[0x10];
    f32 first;
};

extern void func_0011FA88(void*, void*, void*);
extern void func_00188A20(void*, void*);
extern void func_00189150(void*, void*, void*);
extern void func_00188D28(void*, void*, void*);

void func_001201F0(Self_001201F0* self, void* arg)
{
    Locals_001201F0 loc;
    s32 result;

    func_0011FA88(&self->count, &self->items, arg);
    if (self->count < 2) {
        result = 1;
    } else {
        func_00188A20(self->items + 0x10, loc.a);
        u8* tail = (u8*)((self->count << 6) + (s32)self->items) - 0x30;
        func_00188A20(tail, loc.b);
        func_00189150(loc.a, loc.b, loc.c);
        func_00188D28(loc.c, &loc.first, loc.d);
        result = (loc.first < 0.01f) ? 1 : 0;
    }
    self->flag = result;
}

struct Owner_122488 { u8 pad0[0x270]; f32* values; u8 pad1[0x20]; s32 flag; };
struct Self_122488 { void** vt; Owner_122488* owner; u8 pad0[0xB]; s8 kind; };
typedef f32 (*Get_122488)(void*, s32);

extern u8 D_00260E60[];
extern f32 D_0026186C;
extern f32 D_00261860;
extern f32 func_001EA4B8(void*, s32, f32, f32, f32);

void func_00122488(Self_122488* self, s32 val)
{
    f32 ret = ((Get_122488)self->vt[8])(self, val);
    switch (self->kind) {
    case 2:
        self->owner->values[val] = ret;
        break;
    case 3: {
        f32 cur = self->owner->values[val];
        f32 limit = self->owner->flag ? D_0026186C : D_00261860;
        self->owner->values[val] = func_001EA4B8(D_00260E60, 0, cur, ret, limit);
        break;
    }
    }
}

extern u8 D_0027B314[];

void func_001236C8(void* a, void* b);
void func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);
void func_00124A48(void* self);
s32 func_001300E8(void* node, s32 kind);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
void func_00182ED8(void* a);

struct Obj_123448 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x1C];
    void* f34;
    u8 pad2[0x4];
    s32 f3C;
    u8 pad3[0x518];
    void* f558;
    void* f55C;
};

struct Frame_123448 { s32 f00; s32 f04; s32 f08; s32 f0C; };

void func_00123448(Obj_123448* self)
{
    Frame_123448 fr;
    s32 s0;
    func_001DBCC8(self->f14, (void*)func_001236C8, self, 0, 0);
    func_00124A48(self);
    s32 e = (s32)&self->f34;
    fr.f04 = e;
    fr.f00 = e;
    s32 link = *(s32*)(e + 8);
    s32 old = *(s32*)D_0027B314;
    fr.f0C = old;
    fr.f08 = link;
    *(s32*)D_0027B314 = (s32)&fr;
    s32 head = *(s32*)e;
    fr.f04 = head + fr.f08;
    s0 = head;
    if (s0 != 0) {
        do {
            if (func_001300E8((void*)s0, 0x88) != 0) {
                if (self->f558 == 0) {
                    self->f558 = (void*)s0;
                }
            }
            s32 nx = *(s32*)fr.f04;
            fr.f04 = nx + fr.f08;
            s0 = nx;
        } while (s0 != 0);
    }
    if (self->f558 != 0) {
        self->f55C = func_001B6290(self->f558, self, -1, 1);
        func_00182ED8(self->f558);
    }
    *(s32*)D_0027B314 = fr.f0C;
}

struct Node_00122C48 {
    void** vt;
    u8 pad4[4];
    Node_00122C48* next;
    u8 pad0C[5];
    s8 flag11;
};
struct Obj_00122C48 { u8 pad0[8]; Node_00122C48* head; };

void func_00121568(void* parent, void* output, void* clear);

void func_00122C48(Node_00122C48* self, void* a1, void* a2)
{
    Node_00122C48* p = self;
    while ((p = p->next) != 0) {
        s8 f = p->flag11;
        if (f == 0) { p = 0; break; }
        if (f != -1) break;
    }
    if (p != 0) {
        ((void (*)(void*, void*, void*))p->vt[0x18 / 4])(p, a1, a2);
    } else {
        func_00121568(self, a1, a2);
    }
}

struct Pair_120AA8 { f32 a; f32 b; };
struct Seq_120AA8 { s32 f0; s32 f4; Pair_120AA8* f8; };
struct Rec_120AA8;
struct Tgt_120AA8;
struct Cam_120AA8 { u8 pad[0x224]; struct Cam2_120AA8* f224; };
struct Cam2_120AA8 { u8 pad[0x90]; f32 f90; };
typedef void (*VFn_120AA8)(Tgt_120AA8* self, Cam_120AA8* cam, s32 c, f32* o0, f32* o1, f32 x, f32 y);
struct Tgt_120AA8 { VFn_120AA8* vtbl; };
struct Sub_120AA8 { u8 pad[0x34]; f32 f34; };
struct Cfg_120AA8 {
    u8 pad[0x34];
    f32 f34;
    u8 pad2[0xB0 - 0x38];
    s32 stride;
    s32 count;
    u8* base;
};
struct Rec_120AA8 { f32 w; Sub_120AA8* sub; };
struct Obj_120AA8 {
    u8 pad[8];
    Cfg_120AA8* cfg;
    Seq_120AA8* seq;
    Tgt_120AA8** tgts;
};

s32 func_00139970(f32 x, f32 period, s32 count, Pair_120AA8* p, f32* out);
f32 func_001EA408(f32 a);

void func_00120AA8(Obj_120AA8* o, Cam_120AA8* cam, s32 c, f32* out0, f32* out1, f32 dt, f32 scale)
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
    Seq_120AA8* seq = o->seq;
    Cfg_120AA8* cfg = o->cfg;
    f32 w = 0.0f;
    f32 t;
    s32 idx;
    if (!seq) {
        t = dt / cfg->f34;
    } else {
        idx = func_00139970(dt, cfg->f34, seq->f4, seq->f8, &x2);
        t = x2 / seq->f8[idx].b;
    }
    for (s32 i = 0; i < cfg->count; i++) {
        Rec_120AA8* e = (Rec_120AA8*)(cfg->base + i * cfg->stride);
        if (e->w == 0.0f)
            continue;
        Tgt_120AA8* tg = o->tgts[i];
        if (!tg) {
            if (cam) {
                f32 r = func_001EA408(cam->f224->f90 - v0);
                v0 += r * e->w / (w + e->w);
            }
        } else {
            f32 a, b;
            if (!seq) {
                f32 s = e->sub->f34;
                b = s / cfg->f34;
                a = t * s;
            } else {
                Pair_120AA8* q = (Pair_120AA8*)((u8*)e + seq->f0 + idx * 8);
                b = q->b;
                a = q->a + t * b;
                if (e->sub->f34 < a)
                    a -= e->sub->f34;
                b = b / seq->f8[idx].b;
            }
            tg->vtbl[0](tg, cam, c, p0, p1, a, b * scale);
            if (w == 0.0f) {
                v0 = x0;
            } else {
                f32 r = func_001EA408(func_001EA408(x0) - v0);
                v0 += r * e->w / (w + e->w);
            }
            sum1 += e->w * x1;
        }
        w += e->w;
        v0 = func_001EA408(v0);
    }
    if (out0)
        *out0 = v0;
    if (out1)
        *out1 = sum1;
}

struct Pair_120D58 { f32 a; f32 b; };
struct Seq_120D58 { s32 f0; s32 f4; Pair_120D58* f8; };
struct Rec_120D58;
struct Tgt_120D58;
struct Cam_120D58 { u8 pad[0x274]; f32* f274; };
typedef void (*VFn_120D58)(Tgt_120D58* self, Cam_120D58* cam, s32 c, f32* o0, f32* o1, f32 x, f32 y);
struct Tgt_120D58 { VFn_120D58* vtbl; };
struct Sub_120D58 { u8 pad[0x34]; f32 f34; };
struct Cfg_120D58 {
    u8 pad[0x34];
    f32 f34;
    u8 pad2[0xB0 - 0x38];
    s32 stride;
    s32 count;
    u8* base;
};
struct Rec_120D58 { f32 w; Sub_120D58* sub; };
struct Obj_120D58 {
    u8 pad[8];
    Cfg_120D58* cfg;
    Seq_120D58* seq;
    Tgt_120D58** tgts;
    s32 idx;
};

s32 func_00139970(f32 x, f32 period, s32 count, Pair_120D58* p, f32* out);
f32 func_001EA408(f32 a);

void func_00120D58(Obj_120D58* o, Cam_120D58* cam, s32 c, f32* out0, f32* out1, f32 dt, f32 scale)
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
    Seq_120D58* seq = o->seq;
    Cfg_120D58* cfg = o->cfg;
    f32 t;
    s32 idx;
    if (!seq) {
        t = dt / cfg->f34;
    } else {
        idx = func_00139970(dt, cfg->f34, seq->f4, seq->f8, &x2);
        t = x2 / seq->f8[idx].b;
    }
    for (s32 i = 0; i < cfg->count; i++) {
        Rec_120D58* e = (Rec_120D58*)(cfg->base + i * cfg->stride);
        f32 zero = 0.0f;
        if (e->w == zero)
            continue;
        Tgt_120D58* tg = o->tgts[i];
        if (!tg) {
            if (cam)
                sum0 += e->w * cam->f274[o->idx];
        } else {
            f32 a, b;
            if (!seq) {
                f32 s = e->sub->f34;
                b = s / cfg->f34;
                a = t * s;
            } else {
                Pair_120D58* q = (Pair_120D58*)((u8*)e + seq->f0 + idx * 8);
                b = q->b;
                a = q->a + t * b;
                if (e->sub->f34 < a)
                    a -= e->sub->f34;
                b = b / seq->f8[idx].b;
            }
            tg->vtbl[0](tg, cam, c, p0, p1, a, b * scale);
            sum0 += e->w * x0;
            sum1 += e->w * x1;
        }
    }
    if (out0)
        *out0 = sum0;
    if (out1)
        *out1 = sum1;
}

struct Slot_00121338 {
	u8 pad0[4];
	s32 value;
	u8 pad1[8];
	s8 b10;
	s8 b11;
	s8 b12;
	s8 b13;
};

void func_00121338(Slot_00121338* self, s32 value)
{
	s8 m = -1;
	self->value = value;
	self->b12 = m;
	self->b13 = -1;
	self->b11 = m;
	self->b10 = m;
}

extern u8 D_002196E8[];
extern u8 D_002196F8[];
extern u8 D_00219708[];
void* func_0018D5C0(s32 bytes);

struct Obj_121050 {
    void* vt;
    s32 kind;
};

Obj_121050* func_00121050(s32 kind) {
    Obj_121050* p;
    switch (kind) {
    case 0:
        p = (Obj_121050*)func_0018D5C0(0x30);
        p->vt = D_002196E8;
        break;
    case 1:
        p = (Obj_121050*)func_0018D5C0(0x14);
        p->vt = D_002196F8;
        break;
    case 2:
        p = (Obj_121050*)func_0018D5C0(0x1C);
        p->vt = D_00219708;
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

struct Obj_1210F0 { void* vt; s32 kind; };
extern u8 D_00219718[];
extern u8 D_00219728[];
void* func_0018D5C0(u32 n);
Obj_1210F0* func_001210F0(s32 kind)
{
    Obj_1210F0* p;
    switch (kind) {
    case 0:
        p = (Obj_1210F0*)func_0018D5C0(0x30);
        p->vt = (void*)D_00219718;
        break;
    case 1:
        p = (Obj_1210F0*)func_0018D5C0(0x10);
        p->vt = (void*)D_00219728;
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

struct Root_00121280 { u8 pad[0x1B20]; };
struct Table_00121280 { u8 pad[4]; };
extern u8 D_00219560[];
void* func_00121228(Root_00121280* root, void* value, Table_00121280* table);

struct Vt_00121280 { void* slot0; void (*slot1)(void*, void*); };
struct Node_00121280 { Vt_00121280* vt; };

void* func_00121280(Root_00121280* self, void* a, void* b)
{
    Node_00121280* node = (Node_00121280*)func_00121228((Root_00121280*)a, b, (Table_00121280*)D_00219560);
    node->vt->slot1(node, self);
    return node;
}

struct __attribute__((aligned(16))) Quad_1214B8 { s32 v[4]; };
typedef void (*VFn_1214B8)(void* self, void* out);
struct Obj_1214B8 { VFn_1214B8* vt; u8 pad[0x18C]; Quad_1214B8 q190; };
struct Self_1214B8 { u8 pad[4]; Obj_1214B8* obj; };
extern u8 D_00248D30[];

void func_001214B8(Self_1214B8* self, void* out1, void* out2)
{
    *(Quad_1214B8*)out1 = self->obj->q190;
    *(Quad_1214B8*)out2 = *(Quad_1214B8*)D_00248D30;
    if (self->obj->vt[44] != 0) {
        self->obj->vt[44](self->obj, out1);
    }
}

struct __attribute__((aligned(16))) Quad_121580 { s32 a, b, c, d; };
struct Block_121580 { Quad_121580 q[3]; };
struct Unused_121580;

extern u8 D_002483D0[];

void func_00121580(Unused_121580* unused, Block_121580* out)
{
    Block_121580* src = (Block_121580*)D_002483D0;
    out->q[0] = src->q[0];
    out->q[1] = src->q[1];
    out->q[2] = src->q[2];
}

extern u8 D_00248D30[];
extern u8 D_002483D0[];

struct Dst_00122890 {
    u8 pad0[0x1C];
    void* f1C;
    void* f20;
    void* f24;
    void* f28;
    void* f2C;
    void* f30;
    void* f34;
    void* f38;
    s32 f3C;
};

struct Obj2_00122890 {
    u8 pad0[0x8C];
    u8 f8C;
    u8 pad1[0xB0 - 0x8D];
    s32 fB0;
};

struct Src_00122890 {
    u8 pad0[0x190];
    u8 f190;
    u8 pad1[0x1A0 - 0x191];
    u8 f1A0;
    u8 pad2[0x224 - 0x1A1];
    Obj2_00122890* f224;
    u8 pad3[0x26C - 0x228];
    u8 f26C;
    u8 pad4[0x274 - 0x26D];
    s32 f274;
};

void func_00121338(Src_00122890* self, Src_00122890* a1);

void func_00122890(Dst_00122890* self, Src_00122890* src)
{
    func_00121338((Src_00122890*)self, src);
    self->f1C = &src->f190;
    self->f24 = &src->f1A0;
    self->f38 = &src->f26C;
    self->f20 = D_00248D30;
    self->f28 = D_00248D30;
    self->f3C = src->f274;
    Obj2_00122890* o = src->f224;
    if (o != 0) {
        if (o->fB0 & 0x20) {
            self->f30 = D_00248D30;
            self->f2C = &o->f8C;
        }
    }
    self->f34 = D_002483D0;
}

struct __attribute__((aligned(16))) Quad_122A18 { u32 w[4]; };
struct Obj_122A18 { u8 pad0[0x40]; Quad_122A18 a40[3]; u8 pad1[0x20]; Quad_122A18 a90[3]; };

extern u8 D_002483D0[];
void func_00121338(Obj_122A18* self);

void func_00122A18(Obj_122A18* self)
{
    func_00121338(self);
    Quad_122A18* src = (Quad_122A18*)D_002483D0;
    Quad_122A18* d1 = self->a40;
    Quad_122A18* d2 = self->a90;
    self->a40[0] = src[0];
    d1[1] = src[1];
    d1[2] = src[2];
    self->a90[0] = src[0];
    d2[1] = src[1];
    d2[2] = src[2];
}

struct Obj_1236C8;
struct Vt_1236C8 {
    u8 pad[0x140];
    void (*f140)(Obj_1236C8* self, Obj_1236C8* owner);
};
struct Obj_1236C8 {
    Vt_1236C8* vt;
    u8 pad04[0x10];
    void* host;
    u8 pad18[0x564 - 0x18];
    s32 n564;
    s32 a568[4];
    s32 n578;
    s32 a57C[16];
    s32 n5BC;
    Obj_1236C8* a5C0[16];
    s32 n600;
    s32 a604[0x2B];
    s32 f6B0;
};

extern u8 D_00261420[];
s32 func_0015A418(Obj_1236C8* host, s32 a1, s32 a2, Obj_1236C8* ctx);
s32 func_001300E8(Obj_1236C8* n, s32 kind);
void func_00123400(Obj_1236C8* state, Obj_1236C8* value);
void func_001CAD40(Obj_1236C8* self, Obj_1236C8* value);
s32 func_00141008(u8* bits, s32 index);
void func_00123888(Obj_1236C8* self, s32 mode);

void func_001236C8(Obj_1236C8* self)
{
    s32 i;
    s32 n = 0;
    Obj_1236C8* o;
    for (i = 0; i < self->n564; i++) {
        o = (Obj_1236C8*)func_0015A418((Obj_1236C8*)self->host, 0x104, self->a568[i], self);
        if (o && func_001300E8(o, 0x22)) {
            func_00123400(o, self);
            n++;
        }
    }
    self->n564 = n;
    for (i = 0; i < self->n578; i++) {
        o = (Obj_1236C8*)func_0015A418((Obj_1236C8*)self->host, 0x104, self->a57C[i], self);
        if (o && func_001300E8(o, 0x30)) {
            self->a5C0[self->n5BC++] = o;
            o->vt->f140(o, self);
        }
    }
    for (i = 0; i < self->n600; i++) {
        o = (Obj_1236C8*)func_0015A418((Obj_1236C8*)self->host, 0x104, self->a604[i], self);
        if (o && func_001300E8(o, 8))
            func_001CAD40(o, self);
    }
    if (func_00141008(D_00261420, self->f6B0))
        func_00123888(self, 1);
    else
        func_00123888(self, 0);
}

struct Obj_123888 {
    u8 pad0[0x14];
    void* f14;
    u8 pad18[0x550 - 0x18];
    s32 f550;
    f32 f554;
    u8 pad558[4];
    void* f55C;
    u8 pad560[0x620 - 0x560];
    s32* f620;
    s32 f624;
    s32 f628;
    s32 f62C;
    s32 f630;
    u8 pad634[0x6B0 - 0x634];
    s32 f6B0;
};
enum Kind_123888 { K_123888_0 };

void func_001BF788(s32* p, s32 n);
void func_001BF048(s32 x);
void func_0013ECB0(void* a, s32 b, s32* c, Obj_123888* d, s32 e);
void func_00160D00(u8* p);
void func_00160CF0(u8* p);
void func_001B64D8(void* p, s32 n);
void func_001B6628(void* p, s32 n);
void func_00123B28(Obj_123888* self);
void func_00123BB0(Obj_123888* self);
void func_00123C20(Obj_123888* self);
s32 func_00141008(u8* a, s32 b);
void func_00141040(u8* a, s32 b);
void func_001837E0(Obj_123888* self, s32 a, s32 b, s32 c);
s32 func_001BEEF8(s32 a);
void func_001BFCD8(Kind_123888 a0, s32** a1, Obj_123888* a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
extern f32 D_0026185C[];
extern u8 D_002623D8[];
extern u8 D_00261420[];

void func_00123888(Obj_123888* self, s32 n)
{
    s32 old = self->f550;
    if (old == n) return;
    if (old >= 0) {
        if (old < 2) {
        } else if (old == 2) {
            func_001BF788(self->f620, 0);
            func_001BF048(self->f624);
            func_0013ECB0(self->f14, self->f62C, &self->f630, self, 0);
            if (n == 1) func_00160D00(D_002623D8);
        }
    }
    self->f550 = n;
    self->f554 = D_0026185C[0];
    switch (n) {
    case 0:
        if (self->f55C) func_001B64D8(self->f55C, 0x21A);
        func_00123B28(self);
        break;
    case 1:
        if (self->f55C) func_001B6628(self->f55C, 0x220);
        func_00123BB0(self);
        if (func_00141008(D_00261420, self->f6B0)) {
            func_001837E0(self, 0x16, 0, 0);
        } else {
            func_001837E0(self, 3, 0, 0);
        }
        func_00141040(D_00261420, self->f6B0);
        break;
    case 2:
        if (self->f55C) func_001B64D8(self->f55C, 0x21F);
        if (self->f628 == 0) {
            func_001BFCD8((Kind_123888)0x15, &self->f620, self, 0, 8000.0f, 5000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
        self->f624 = func_001BEEF8(0x6B);
        func_00123C20(self);
        func_0013ECB0(self->f14, self->f62C, &self->f630, self, 1);
        func_001837E0(self, 2, 0, 0);
        func_00160CF0(D_002623D8);
        break;
    }
}
