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
extern "C" u8* GetActiveExceptionSlot();
// The argument GetActiveExceptionRecord passes through to the slot lookup, which ignores it.
struct ExceptionLookupArg;

typedef void (*TerminateHandler)(void) __attribute__((noreturn));
typedef void (*UnexpectedHandler)(void) __attribute__((noreturn));

// The unexpected handler, at first func_001FE908 (defined below, after its first use).
extern s32 D_00278640;

void InvokeTerminateHandler(void) __attribute__((noreturn));

void InvokeTerminateHandler(void)
{
	((TerminateHandler)D_00278048)();
}

void DefaultUnexpectedHandler(void) __attribute__((noreturn));

void DefaultUnexpectedHandler(void)
{
	InvokeTerminateHandler();
}

TerminateHandler ReplaceTerminateHandler(TerminateHandler handler)
{
	TerminateHandler old = (TerminateHandler)D_00278048;
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
	((UnexpectedHandler)D_00278640)();
}

void* GetThrownObjectAddress(void)
{
	return *(u8**)GetActiveExceptionSlot() + 8;
}

void* GetActiveExceptionRecord(ExceptionLookupArg* self)
{
	return *(void**)GetActiveExceptionSlot();
}

// The 0x30-byte record of a thrown exception (PushThrownException makes it and puts it on the
// slot's chain, GetActiveExceptionSlot): the function that tests whether a handler takes it
// (MatchPendingThrowType), the type it carries, the next record, and the count
// HasUncaughtException tests.
struct ThrownException {
    void* f00;              // 0x00: MatchPendingThrowType
    u16 f04;                // 0x04: 4
    u16 f06;                // 0x06: 1
    void* f08;              // 0x08: the object the handler matched (set by MatchPendingThrowType)
    const type_info* f0C;   // 0x0C: the thrown type
    void* f10;              // 0x10: the cleanup
    s32 f14;                // 0x14: the count HasUncaughtException tests
    ThrownException* f18;   // 0x18: the next record in the chain
    u8 pad1C[4];
    u64 f20;                // 0x20
    void* f28;              // 0x28: the thrown value
    u8 pad2C[4];
};

typedef char check_ThrownException[sizeof(ThrownException) == 0x30 ? 1 : -1];

ThrownException* BeginCatchHandler(void)
{
    ThrownException* obj = *(ThrownException**)GetActiveExceptionSlot();
    obj->f14 = 1;
    obj->f20++;
    return obj;
}

extern "C" void* EnterRuntimeLock(u32 size);

void* AllocateRuntimeBlockOrTerminate(u32 size)
{
    void* p = EnterRuntimeLock(size);
    if (p == 0)
        InvokeTerminateHandler();
    return p;
}

extern "C" void LeaveRuntimeLock(void* p);

void FreeRuntimeBlock(void* block)
{
    LeaveRuntimeLock(block);
}

// What MatchPendingThrowType is handed with the handler: a record whose kind, at 0x04 as in
// ThrownException's, must be 4.
struct ThrowMatchHeader {
    u8 pad0[4];
    s16 kind;
};

// The function a handler gives, which returns the type it takes.
typedef const type_info* (*HandlerTypeFn)();

extern "C" void* MatchThrownType(const type_info* want, const type_info* have, void* object);

void* MatchPendingThrowType(ThrownException* self, void* fn, ThrowMatchHeader* a2)
{
    if (a2 != 0 && a2->kind != 4) {
        return 0;
    }
    if (fn == (void*)-1) {
        return self->f08;
    }
    void* r = MatchThrownType(((HandlerTypeFn)fn)(), self->f0C, self->f28);
    if (r != 0) {
        self->f08 = r;
    }
    return r;
}

void PushThrownException(void* a0, const type_info* a1, void* a2)
{
    ThrownException* obj = (ThrownException*)AllocateRuntimeBlockOrTerminate(0x30);
    obj->f0C = a1;
    obj->f10 = a2;
    obj->f08 = a0;
    obj->f28 = a0;
    obj->f20 = 0;
    obj->f14 = 0;
    obj->f00 = (void*)MatchPendingThrowType;
    obj->f04 = 4;
    obj->f06 = 1;
    ThrownException** p = (ThrownException**)GetActiveExceptionSlot();
    obj->f18 = *p;
    *p = obj;
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

void FreeRuntimeBlock(void* block);
extern "C" bool IsPointerType(const type_info* type);

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
    if (IsPointerType((const type_info*)self->data) == 0) {
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

void CheckExceptionSpecification(s32 count, void** allowed)
{
    ThrownException* info = *(ThrownException**)GetActiveExceptionSlot();
    s32 i;

    for (i = 0; i < count; i++) {
        if (MatchThrownType((const type_info*)allowed[i], info->f0C, info->f08)) {
            throw;
        }
    }
    try {
        InvokeUnexpectedHandler();
    } catch (...) {
        if (info != (ThrownException*)__exception_info) {
            info = (ThrownException*)__exception_info;
            for (i = 0; i < count; i++) {
                if (MatchThrownType((const type_info*)allowed[i], info->f0C, info->f08)) {
                    throw;
                }
            }
        }
        const type_info* type = &typeid(bad_exception);
        for (i = 0; i < count; i++) {
            if (MatchThrownType((const type_info*)allowed[i], type, info->f08)) {
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

struct Slot_1FEEC8 { ThrownException* obj; };

s32 HasUncaughtException(void)
{
    ThrownException* obj = ((Slot_1FEEC8*)GetActiveExceptionSlot())->obj;
    s32 result = 0;
    if (obj != 0) {
        result = obj->f14 == 0;
    }
    return result;
}

const char* exception::what() const
{
    return typeid(*this).name();
}

s32 D_00278640 = (s32)DefaultUnexpectedHandler;
