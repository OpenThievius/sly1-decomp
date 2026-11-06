// SPDX-License-Identifier: AGPL-3.0-or-later
// The C++ runtime's exception handling, the whole object 0x1FE8F0-0x1FF048: terminate and
// unexpected and their setters, the routines the compiler's throw, catch and exception
// specifications call (the current exception, its allocation, push and pop, the handler entry,
// the specification check), the throws of bad_cast and bad_typeid, uncaught_exception and
// exception::what; the compiler writes out (`#pragma implementation`) the inline members of
// include/exception.h, the vtables of exception and bad_exception and their type information.
// C++, built by the Linux cc1plus of 2.9-ee-991111 (config/cflags.tsv, docs/TOOLCHAIN.md); the
// functions the compiler makes keep retail's names (config/us/generated.tsv). Written for this
// project from retail's code.
#include "common.h"
#pragma implementation "exception.h"
#include "exception.h"
#include "typeinfo.h"

extern void (*D_00278048)();
u8* func_001FDA10(void);
struct Ctx_001FE978;
void* func_001FDA10(Ctx_001FE978* self);

typedef void (*Handler_001FE8F0)(void) __attribute__((noreturn));
typedef void (*Handler_001FE938)(void) __attribute__((noreturn));

// The unexpected handler, at first func_001FE908 (defined below, after its first use).
extern s32 D_00278640;

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

s32 func_001FE928(s32 value)
{
    s32 previous = D_00278640;
    D_00278640 = value;
    return previous;
}

void func_001FE938(void) __attribute__((noreturn));

void func_001FE938(void)
{
	((Handler_001FE938)D_00278640)();
}

s32 func_001FE950(void)
{
	return *(s32*)func_001FDA10() + 8;
}

s32 func_001FE978(Ctx_001FE978* self)
{
	return *(s32*)func_001FDA10(self);
}

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

struct Arg_1FE9D0;
s32 func_0018D740(Arg_1FE9D0* size);

s32 func_001FE9D0(Arg_1FE9D0* size)
{
    s32 p = func_0018D740(size);
    if (p == 0)
        func_001FE8F0();
    return p;
}

s32 func_0018D750(void);

s32 func_001FE9F8(void)
{
    return func_0018D750();
}

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

struct Size_1FEA88;

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

struct Node_1FEBE0 { u8 pad[0x14]; s32 flag; };
struct Head_1FEBE0 { Node_1FEBE0* node; };

void func_001FEBE0(void)
{
    Node_1FEBE0* n = ((Head_1FEBE0*)func_001FDA10())->node;
    if (n == 0)
        func_001FE8F0();
    n->flag = 0;
}

struct Info_001FEC10 {
    u8 pad[8];
    void* value;
    void* type;
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
        const type_info* type = &typeid(bad_exception);
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

const char* exception::what() const
{
    return typeid(*this).name();
}

s32 D_00278640 = (s32)func_001FE908;
