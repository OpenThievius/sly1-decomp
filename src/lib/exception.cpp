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
u8* GetActiveExceptionSlot(void);
struct Ctx_001FE978;
void* GetActiveExceptionSlot(Ctx_001FE978* self);

typedef void (*Handler_001FE8F0)(void) __attribute__((noreturn));
typedef void (*Handler_001FE938)(void) __attribute__((noreturn));

// The unexpected handler, at first func_001FE908 (defined below, after its first use).
extern s32 D_00278640;

void InvokeTerminateHandler(void) __attribute__((noreturn));

void InvokeTerminateHandler(void)
{
	((Handler_001FE8F0)D_00278048)();
}

void DefaultUnexpectedHandler(void) __attribute__((noreturn));

void DefaultUnexpectedHandler(void)
{
	InvokeTerminateHandler();
}

Handler_001FE8F0 ReplaceTerminateHandler(Handler_001FE8F0 handler)
{
	Handler_001FE8F0 old = (Handler_001FE8F0)D_00278048;
	D_00278048 = (void (*)())handler;
	return old;
}

s32 ReplaceUnexpectedHandler(s32 value)
{
    s32 previous = D_00278640;
    D_00278640 = value;
    return previous;
}

void InvokeUnexpectedHandler(void) __attribute__((noreturn));

void InvokeUnexpectedHandler(void)
{
	((Handler_001FE938)D_00278640)();
}

s32 GetThrownObjectAddress(void)
{
	return *(s32*)GetActiveExceptionSlot() + 8;
}

s32 GetActiveExceptionRecord(Ctx_001FE978* self)
{
	return *(s32*)GetActiveExceptionSlot(self);
}

struct Obj_001FE998 {
    u8 pad[0x14];
    s32 flag;
    u8 pad2[8];
    s64 count;
};

Obj_001FE998* BeginCatchHandler(void)
{
    Obj_001FE998* obj = *(Obj_001FE998**)GetActiveExceptionSlot();
    obj->flag = 1;
    obj->count++;
    return obj;
}

struct Arg_1FE9D0;
s32 EnterRuntimeLock(Arg_1FE9D0* size);

s32 AllocateRuntimeBlockOrTerminate(Arg_1FE9D0* size)
{
    s32 p = EnterRuntimeLock(size);
    if (p == 0)
        InvokeTerminateHandler();
    return p;
}

s32 LeaveRuntimeLock(void); // stays non-void: the C definition is void, and the caller here uses the value it leaves in the register

s32 FreeRuntimeBlock(void)
{
    return LeaveRuntimeLock();
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

s32 MatchThrownType(Res_001FEA18* a, s32 b, s32 c);

s32 MatchPendingThrowType(Node_001FEA18* self, void* fn, Hdr_001FEA18* a2)
{
    if (a2 != 0 && a2->kind != 4) {
        return 0;
    }
    if (fn == (void*)-1) {
        return self->f8;
    }
    s32 r = ((Fn_001FEA18)fn)();
    r = MatchThrownType((Res_001FEA18*)r, self->fC, self->f28);
    if (r != 0) {
        self->f8 = r;
    }
    return r;
}

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

void PushThrownException(s32 a0, s32 a1, s32 a2)
{
    struct Obj_1FEA88* obj = (struct Obj_1FEA88*)AllocateRuntimeBlockOrTerminate((Arg_1FE9D0*)0x30);
    obj->f0C = a1;
    obj->f10 = a2;
    obj->f08 = a0;
    obj->f28 = a0;
    obj->f20 = 0;
    obj->f14 = 0;
    obj->f00 = (void*)MatchPendingThrowType;
    obj->f04 = 4;
    obj->f06 = 1;
    s32* p = (s32*)GetActiveExceptionSlot();
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

s32 FreeRuntimeBlock(void*);
s32 IsPointerType(void*);

void PopThrownException(Handle_1FEB18* self)
{
    Handle_1FEB18** link = (Handle_1FEB18**)GetActiveExceptionSlot();
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
        InvokeTerminateHandler();
    }
    *link = self->next;
    if (self->callback != 0) {
        self->callback(self->object, 2);
    }
    if (IsPointerType(self->data) == 0) {
        FreeRuntimeBlock(self->buf);
    }
    FreeRuntimeBlock(self);
}

struct Node_1FEBE0 { u8 pad[0x14]; s32 flag; };
struct Head_1FEBE0 { Node_1FEBE0* node; };

void AbandonCatchHandler(void)
{
    Node_1FEBE0* n = ((Head_1FEBE0*)GetActiveExceptionSlot())->node;
    if (n == 0)
        InvokeTerminateHandler();
    n->flag = 0;
}

struct Info_001FEC10 {
    u8 pad[8];
    void* value;
    void* type;
};

void CheckExceptionSpecification(s32 count, void** allowed)
{
    Info_001FEC10* info = *(Info_001FEC10**)GetActiveExceptionSlot();
    s32 i;

    for (i = 0; i < count; i++) {
        if (MatchThrownType((Res_001FEA18*)allowed[i], (s32)info->type, (s32)info->value)) {
            throw;
        }
    }
    try {
        InvokeUnexpectedHandler();
    } catch (...) {
        if (info != (Info_001FEC10*)__exception_info) {
            info = (Info_001FEC10*)__exception_info;
            for (i = 0; i < count; i++) {
                if (MatchThrownType((Res_001FEA18*)allowed[i], (s32)info->type, (s32)info->value)) {
                    throw;
                }
            }
        }
        const type_info* type = &typeid(bad_exception);
        for (i = 0; i < count; i++) {
            if (MatchThrownType((Res_001FEA18*)allowed[i], (s32)type, (s32)info->value)) {
                throw bad_exception();
            }
        }
        InvokeTerminateHandler();
    }
}

void ThrowCastError()
{
    throw bad_cast();
}

void ThrowTypeidError()
{
    throw bad_typeid();
}

struct Obj_1FEEC8 { u8 pad[0x14]; s32 count; };
struct Slot_1FEEC8 { Obj_1FEEC8* obj; };

s32 HasUncaughtException(void)
{
    Obj_1FEEC8* obj = ((Slot_1FEEC8*)GetActiveExceptionSlot())->obj;
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

s32 D_00278640 = (s32)DefaultUnexpectedHandler;
