// SPDX-License-Identifier: AGPL-3.0-or-later
// The runtime's exception classes keep their vtables where retail has them (config/us/libcalls.tsv):
// with `#pragma interface` the compiler refers to them by name instead of writing its own.
#pragma interface
#include "common.h"

// SPDX-License-Identifier: AGPL-3.0-or-later

#include "common.h"

extern s32 D_00278640;

s32 func_001FE928(s32 value)
{
    s32 previous = D_00278640;
    D_00278640 = value;
    return previous;
}

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_0024F0C0[];

void* func_001FEF58(void* self)
{
    *(void**)self = ((u8*)D_0024F0C0);
    return self;
}

extern u8 D_0024F0D8[];

void* func_001FEFF0(void* self)
{
    *(void**)self = D_0024F0D8;
    return self;
}

extern void (*D_00278048)();

u8* func_001FDA10(void);

// NEAR: retail saves $ra with sd, default compiler with sq; body identical
struct Ctx_001FE978;
void* func_001FDA10(Ctx_001FE978* self);

s32 func_001FE978(Ctx_001FE978* self)
{
	return *(s32*)func_001FDA10(self);
}

// NEAR: default 2.95.3 saves $ra with sq/lq where retail has sd/ld; EXACT with SLY1_COMPILER=2.9-ee-991111

struct Obj_001FE998 {
    u8 pad[0x14];
    s32 flag;
    u8 pad2[8];
    s64 count;
};


Obj_001FE998* func_001FE998(void)
{
    Obj_001FE998* obj = *(Obj_001FE998**)func_001FDA10();
    obj->flag = 1;
    obj->count++;
    return obj;
}

// NEAR: retail saves s0..s3 and ra with 8-byte sd/ld (the default compiler: 16-byte sq/lq); and retail stores the function pointer at +0 before the two halfword stores, and computes its address before the `li v1,1`, where ours keeps the halfword stores first. Otherwise identical

struct Size_1FEA88;
struct Fn_1FEA88;

struct Obj_1FEA88 {
    void* f00;
    u16 f04;
    u16 f06;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    u64 f20;
    s32 f28;
};

struct Obj_1FEA88* func_001FE9D0(struct Size_1FEA88* n);
s32 func_001FEA18(struct Fn_1FEA88* self);

void func_001FEA88(s32 a0, s32 a1, s32 a2)
{
    struct Obj_1FEA88* obj = func_001FE9D0((struct Size_1FEA88*)0x30);
    obj->f0C = a1;
    obj->f10 = a2;
    obj->f08 = a0;
    obj->f28 = a0;
    obj->f20 = 0;
    obj->f14 = 0;
    obj->f00 = (void*)func_001FEA18;
    obj->f04 = 4;
    obj->f06 = 1;
    s32* p = (s32*)func_001FDA10();
    obj->f18 = *p;
    *p = (s32)obj;
}

// NEAR: retail is library code (0x1F59C4 onward, Sony's 2.9-ee-991111) and saves $ra with sd, 8 bytes; the default compiler saves it with sq, 16 bytes. The body matches.

struct Obj_1FEEC8 { u8 pad[0x14]; s32 count; };
struct Slot_1FEEC8 { Obj_1FEEC8* obj; };


s32 func_001FEEC8(void)
{
    Obj_1FEEC8* obj = ((Slot_1FEEC8*)func_001FDA10())->obj;
    s32 result = 0;
    if (obj != 0) {
        result = obj->count == 0;
    }
    return result;
}

// NEAR: ra is saved with sq/lq, retail sd/ld (Sony 2.9-ee-991111 lib build); body otherwise EXACT

struct Obj_001FEF00;

struct Vtbl_001FEF00 {
    void* slot0;
    void* (*slot1)(Obj_001FEF00* self);
};

struct Obj_001FEF00 {
    Vtbl_001FEF00* vtbl;
};

s32 func_001FEF00(Obj_001FEF00* self)
{
    return *(s32*)self->vtbl->slot1(self);
}

// NEAR: only the $ra and $s0 saves differ: retail sd/ld, ours sq/lq

extern u8 D_0062C5A8[];
extern const char D_0024F0F0[16];
extern u8 D_0027B318[];

struct Node_1FEF70 {
    void *field0;
};

void func_00200118(struct Node_1FEF70 *self, void *a1, void *a2);

void* func_001FF008(void);
void* func_001FEF70(void) {
    struct Node_1FEF70 *node = (struct Node_1FEF70 *)D_0062C5A8;
    if (node->field0 == 0) {
        func_001FF008();
        func_00200118(node, (void*)D_0024F0F0, D_0027B318);
    }
    return node;
}

// NEAR: only the s0 and ra saves differ: retail saves ra and s0 with sd (8 bytes), the SN builds with sq; the 8-byte save is the Sony 2.9-ee-991111 form (docs/TOOLCHAIN.md), not used here.

extern u8 D_0027B318[];
extern const char D_0024F100[16];

struct Node_1FF008 {
    void *field0;
    void *vtbl;
};

void func_00200138(struct Node_1FF008 *self, void *value);

void *func_001FF008(void) {
    struct Node_1FF008 *node = (struct Node_1FF008 *)D_0027B318;
    if (*(void **)D_0027B318 == 0) {
        func_00200138(node, (void*)D_0024F100);
    }
    return node;
}

s32 func_0018D750(void);

s32 func_001FE9F8(void)
{
    return func_0018D750();
}

struct Obj_001FEF28 { u8* f0; };

s32 func_0018D778(Obj_001FEF28* self);
extern u8 D_0024F0D8[];

u8* func_001FEF28(Obj_001FEF28* self, s32 flag)
{
    u8* value = D_0024F0D8;
    self->f0 = value;
    if (flag & 1) {
        return (u8*)func_0018D778(self);
    }
    return value;
}

extern u8 D_0024F0D8[];

s32 func_0018D778(void* self);

s32 func_001FEFC0(void* self, s32 flags)
{
    void* v = D_0024F0D8;
    *(void**)self = v;
    if (flags & 1) {
        return func_0018D778(self);
    }
    return (s32)v;
}

// NEAR: retail saves with sd/ld (ours sq/lq); jalr's delay slot is a nop in retail, ours moves a0 there

struct Node_001FEA18 {
    u8 pad0[8];
    s32 f8;
    s32 fC;
    u8 pad1[0x18];
    s32 f28;
};

struct Hdr_001FEA18 {
    u8 pad0[4];
    s16 kind;
};

struct Res_001FEA18;

typedef s32 (*Fn_001FEA18)();

s32 func_00200778(Res_001FEA18* a, s32 b, s32 c);

s32 func_001FEA18(Node_001FEA18* self, void* fn, Hdr_001FEA18* a2)
{
    if (a2 != 0 && a2->kind != 4) {
        return 0;
    }
    if (fn == (void*)-1) {
        return self->f8;
    }
    s32 r = ((Fn_001FEA18)fn)();
    r = func_00200778((Res_001FEA18*)r, self->fC, self->f28);
    if (r != 0) {
        self->f8 = r;
    }
    return r;
}

struct Node_1FEBE0 { u8 pad[0x14]; s32 flag; };
struct Head_1FEBE0 { Node_1FEBE0* node; };

extern void func_001FE8F0(void) __attribute__((noreturn));

void func_001FEBE0(void)
{
    Node_1FEBE0* n = ((Head_1FEBE0*)func_001FDA10())->node;
    if (n == 0)
        func_001FE8F0();
    n->flag = 0;
}

void func_002014D0(void) __attribute__((noreturn));

struct Info_001FEC10 {
    u8 pad[8];
    void* value;
    void* type;
};

extern void func_001FE938() __attribute__((noreturn));

// The runtime's exceptions: a base class with a description, and the classes thrown below.
class exception {
public:
    exception() {}
    virtual ~exception() {}
    virtual const char* Describe() const;
};

class bad_exception : public exception {
public:
    bad_exception() {}
    virtual ~bad_exception() {}
};

class bad_cast : public exception {
public:
    bad_cast() {}
    virtual ~bad_cast() {}
};

class bad_typeid : public exception {
public:
    bad_typeid() {}
    virtual ~bad_typeid() {}
};

void func_001FEC10(s32 count, void** allowed)
{
    Info_001FEC10* info = *(Info_001FEC10**)func_001FDA10();
    s32 i;

    for (i = 0; i < count; i++) {
        if (func_00200778((Res_001FEA18*)allowed[i], (s32)info->type, (s32)info->value)) {
            throw;
        }
    }
    try {
        func_001FE938();
    } catch (...) {
        if (info != (Info_001FEC10*)__exception_info) {
            info = (Info_001FEC10*)__exception_info;
            for (i = 0; i < count; i++) {
                if (func_00200778((Res_001FEA18*)allowed[i], (s32)info->type, (s32)info->value)) {
                    throw;
                }
            }
        }
        void* type = func_001FEF70();
        for (i = 0; i < count; i++) {
            if (func_00200778((Res_001FEA18*)allowed[i], (s32)type, (s32)info->value)) {
                throw bad_exception();
            }
        }
        func_001FE8F0();
    }
}

void func_001FEDC8()
{
    throw bad_cast();
}

void func_001FEE48()
{
    throw bad_typeid();
}

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
extern const Fn_Table D_0024F0C0[6] = { 0, (Fn_Table)func_001FEF70, 0, (Fn_Table)func_001FEF28, 0, (Fn_Table)func_001FEF00 };

typedef void (*Handler_001FE8F0)(void) __attribute__((noreturn));

void func_001FE8F0(void) __attribute__((noreturn));

void func_001FE8F0(void)
{
	((Handler_001FE8F0)D_00278048)();
}

void func_001FE908(void) __attribute__((noreturn));

void func_001FE908(void)
{
	func_001FE8F0();
}

Handler_001FE8F0 func_001FE918(Handler_001FE8F0 handler)
{
	Handler_001FE8F0 old = (Handler_001FE8F0)D_00278048;
	D_00278048 = (void (*)())handler;
	return old;
}

typedef void (*Handler_001FE938)(void) __attribute__((noreturn));

void func_001FE938(void) __attribute__((noreturn));

void func_001FE938(void)
{
	((Handler_001FE938)D_00278640)();
}

s32 func_001FE950(void)
{
	return *(s32*)func_001FDA10() + 8;
}

struct Arg_1FE9D0;
s32 func_0018D740(Arg_1FE9D0* size);
extern void func_001FE8F0(void) __attribute__((noreturn));

s32 func_001FE9D0(Arg_1FE9D0* size)
{
    s32 p = func_0018D740(size);
    if (p == 0)
        func_001FE8F0();
    return p;
}

struct Handle_1FEB18 {
    u8 pad_00[0x8];
    void* object;
    void* data;
    void (*callback)(void*, s32);
    s32 state;
    Handle_1FEB18* next;
    u8 pad_1C[4];
    s64 refs;
    void* buf;
};

extern void func_001FE8F0(void) __attribute__((noreturn));
s32 func_001FE9F8(void*);
s32 func_00200C40(void*);

void func_001FEB18(Handle_1FEB18* self)
{
    Handle_1FEB18** link = (Handle_1FEB18**)func_001FDA10();
    if (--self->refs != 0) {
        return;
    }
    if (self == *link && self->state == 0) {
        return;
    }
    for (; *link != 0; link = &(*link)->next) {
        if (*link == self) {
            break;
        }
    }
    if (*link == 0) {
        func_001FE8F0();
    }
    *link = self->next;
    if (self->callback != 0) {
        self->callback(self->object, 2);
    }
    if (func_00200C40(self->data) == 0) {
        func_001FE9F8(self->buf);
    }
    func_001FE9F8(self);
}

// Globals defined from C.
s32 D_00278640 = (s32)func_001FE908;
extern const char D_0024F0F0[16] = "13bad_exception";
extern const char D_0024F100[16] = "9exception";
