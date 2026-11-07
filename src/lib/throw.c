/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* The C++ runtime's exception support, the whole object, 0x1FD920-0x1FE890 (config/us/libcalls.tsv):
 * the terminate hook, the per-thread exception context, the handler chain's throw and unwind, the
 * unwind tables' range lookup and the throw and rethrow entry points.
 * C, built by the Linux cc1 with -fexceptions (config/cflags.tsv): the stub that returns into the
 * handler and the prologue that saves every register are __builtin_unwind_init's and
 * __builtin_eh_return's, which only GCC's C front end has, and without -fexceptions the stub
 * moves (func_001FE4C8) or cc1 fails (func_001FE6A8). Written for this project from retail's
 * code. */
#include "common.h"

/* A frame's unwind state, 0x2F0 bytes: its canonical frame address first. */
typedef struct UnwindFrame {
    s32 cfa;
    s32 pad4;
    s64 rest[0x2E8 / 8];
} UnwindFrame;

/* The runtime's exception context (func_001FD9E8's): the pending object at 8, its index at 0xC. */
typedef struct EhContext {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
} EhContext;

UnwindFrame* func_001FFC80(void* pc, UnwindFrame* frame);
void* func_001F5C0C(void* dst, s32 c, u32 n);
s32 func_001F5A58(void* dst, void* src, s32 n);
s32 func_001F6738(void* self, s32 v);
void* func_0018D740(s32 size);
void func_002014D0(void) __attribute__((noreturn));

void func_001FD920(void);
EhContext* func_001FDA60(void);
void func_001FDA38(void);

/* The terminate hook, and the function that returns the exception context. */
void (*D_00278048)(void) = func_001FD920;
EhContext* (*D_0027804C)(void) = (EhContext* (*)(void))func_001FDA38;

void func_001FD920(void)
{
    AbortProgram();
}

void func_001FD930(void)
{
    (*D_00278048)();
}

typedef struct Obj_1FD958 Obj_1FD958;

s32 func_001FD958(Obj_1FD958* self, s32 v, s32 fallback)
{
    s32 result = fallback;
    if (CompareStrings(self, v) != 0) {
        result = 0;
    }
    return result;
}

void func_001FD988(void) {}

typedef struct Node_001FD990 {
    s32 f0;
    u8* f4;
    s32 f8;
    s32 fc;
    s32 f10;
    s32 f14;
} Node_001FD990;

Node_001FD990* func_001FD990(void)
{
    Node_001FD990* p = (Node_001FD990*)func_0018D740(0x18);
    if (p == 0) {
        func_001FD930();
    }
    (void)FillMemory(p, 0, 0x18);
    p->f4 = (u8*)p + 0x10;
    return p;
}

s32 func_001FD9E8(void)
{
    return (s32)(*D_0027804C)();
}

u8* func_001FDA10(void)
{
    return (u8*)(*D_0027804C)() + 8;
}

void func_001FDA38(void)
{
    void (*f)(void) = (void (*)(void))func_001FDA60;
    D_0027804C = (EhContext* (*)(void))f;
    f();
}

typedef struct Once_1FDA60 {
    s32 a;
    void* b;
    u8 pad8[8];
} Once_1FDA60;

static Once_1FDA60 D_0062A798;
static s32 D_0062A7A8;
static void* D_0062A7B0[2];

EhContext* func_001FDA60(void)
{
    if (D_0062A7A8 == 0) {
        D_0062A7A8 = 1;
        (void)FillMemory(&D_0062A798, 0, 0x10);
        D_0062A798.b = D_0062A7B0;
    }
    return (EhContext*)&D_0062A798;
}

u8* func_001FDAC8(void)
{
    return (u8*)(*D_0027804C)() + 4;
}

/* The runtime's exception context: the handler chain at +4, the active exception at +8. */
typedef struct Ctx_1FDAF0 {
    s32 f0;
    void** chain;
    void* active;
} Ctx_1FDAF0;

void func_001FDAF0(void) __attribute__((noreturn));

/* Throws: runs the cleanups registered in the top handler, then jumps to that handler. */
void func_001FDAF0(void)
{
    Ctx_1FDAF0* ctx = (Ctx_1FDAF0*)(*D_0027804C)();
    void*** chain = &ctx->chain;
    void*** cleanups = (void***)&(*chain)[1];
    void* buf;

    if (cleanups[0] != 0) {
        double space[200];
        void** frame = (void**)space;
        frame[1] = 0;
        frame[0] = *chain;
        if (!__builtin_setjmp(&frame[2])) {
            *chain = frame;
            while (cleanups[0] != 0) {
                void (*fn)(void*, s32) = (void (*)(void*, s32))cleanups[0][1];
                void* arg = cleanups[0][2];
                cleanups[0] = (void**)cleanups[0][0];
                fn(arg, 2);
            }
            *chain = (void**)frame[0];
        } else {
            func_001FD930();
        }
    }

    if (ctx->active == 0 || (*chain)[0] == 0) {
        func_001FD930();
    }

    buf = &(*chain)[2];
    *chain = (void**)(*chain)[0];
    __builtin_longjmp(buf, 1);
}

/* Pops the top handler after running its cleanups, then throws again. */
void func_001FDC68(void)
{
    Ctx_1FDAF0* ctx = (Ctx_1FDAF0*)(*D_0027804C)();
    void*** chain = &ctx->chain;
    void*** cleanups = (void***)&(*chain)[1];

    if (cleanups[0] != 0) {
        double space[200];
        void** frame = (void**)space;
        frame[1] = 0;
        frame[0] = *chain;
        if (!__builtin_setjmp(&frame[2])) {
            *chain = frame;
            while (cleanups[0] != 0) {
                void (*fn)(void*, s32) = (void (*)(void*, s32))cleanups[0][1];
                void* arg = cleanups[0][2];
                cleanups[0] = (void**)cleanups[0][0];
                fn(arg, 2);
            }
            *chain = (void**)frame[0];
        } else {
            func_001FD930();
        }
    }

    *chain = (void**)(*chain)[0];
    func_001FDAF0();
}

/* The active exception, asked whether it matches a runtime type through its matcher. */
typedef struct Info_1FDD80 Info_1FDD80;
struct Info_1FDD80 {
    void* (*match)(Info_1FDD80* info, void* type, void* extra);
};

s32 func_001FDD80(void* type)
{
    Info_1FDD80* info = *(Info_1FDD80**)func_001FDA10();
    void* (*match)(Info_1FDD80*, void*, void*) = info->match;
    if (match == 0) {
        return 0;
    }
    return match(info, type, 0) != 0;
}

s16 func_001FDDC8(void* object)
{
    return *(s16*)((u8*)object + 6);
}

s16 func_001FDDD0(void* object)
{
    return *(s16*)((u8*)object + 4);
}

typedef struct Range_1FDDD8 {
    u32 lo;
    u32 hi;
    s32 value;
} Range_1FDDD8;

s32 func_001FDDD8(u32 key, Range_1FDDD8* t)
{
    s32 best, i;
    if (t == 0) goto none;
    best = -1;
    i = 0;
    if (t[0].lo == 0xFFFFFFFF) goto check;
    do {
        if (key >= t[i].lo && key < t[i].hi) {
            if (best == -1 || (t[best].hi >= t[i].hi && t[best].lo <= t[i].lo)) best = i;
        } else if (best >= 0 && key < t[i].lo) {
            break;
        }
        i++;
    } while (t[i].lo != 0xFFFFFFFF);
check:
    if (best == -1) goto none;
    return t[best].value;
none:
    return 0;
}

typedef struct Span_001FDEB0 {
    u32 lo;
    u32 hi;
    s32 value;
    void* cb;
} Span_001FDEB0;
typedef struct Ctx_001FDEB0 {
    void* fn;
} Ctx_001FDEB0;
typedef struct Cur_001FDEB0 {
    s32 pad0;
    s32 count;
} Cur_001FDEB0;

s32 func_001FDEB0(s32 a0, void* a1, Ctx_001FDEB0* a2, s32 a3, s32* a4)
{
    s32 result = 0;
    s32 key = a0;
    Span_001FDEB0* base;
    s32 idx;
    s32 r;

    *a4 = 1;
    if (a1 != 0) {
        idx = 0;
        base = (Span_001FDEB0*)((u8*)a1 + 8);
        if (a3 != 0) {
            idx = ((u8*)a0 - (u8*)base) >> 4;
            key = ((Cur_001FDEB0*)a0)->count - 1;
            if (base[idx].lo != 0xFFFFFFFF) {
                idx++;
            }
        } else {
            key = key - 1;
        }
        while (base[idx].lo != 0xFFFFFFFF) {
            if ((u32)key >= base[idx].lo && (u32)key < base[idx].hi) {
                if (base[idx].cb != 0) {
                    if (a2->fn != 0) {
                        r = ((s32 (*)(Ctx_001FDEB0*, void*, void*))a2->fn)(a2, base[idx].cb, a1);
                        if (r != 0) {
                            if (result == 0) {
                                result = base[idx].value;
                            }
                            *a4 = 0;
                            return result;
                        }
                    }
                } else {
                    if (result == 0) {
                        result = base[idx].value;
                    }
                }
            }
            idx++;
        }
    }
    return result;
}

typedef struct Obj_1FDFF8 {
    u8* f0;
    u8 pad[0x14];
    s64 tbl[80];
    s32 pad2;
    s8 st[64];
} Obj_1FDFF8;

u8* func_001FDFF8(u32 idx, Obj_1FDFF8* self, Obj_1FDFF8* other)
{
    while (self->st[idx] == 2) {
        idx = self->tbl[idx];
    }
    if (self->st[idx] == 1) {
        return self->f0 + self->tbl[idx];
    }
    AbortProgram();
}

s32 func_001FE080(s32 a0, u32 a1, u32 a2)
{
    u8* r1 = func_001FDFF8(a0, (Obj_1FDFF8*)a1, 0);
    u8* r2 = func_001FDFF8(a0, (Obj_1FDFF8*)a2, 0);
    s32 n;
    if (a0 >= 0x1F) {
        n = 8;
        if (!(0x3F < a0)) {
            n = 4;
        }
    } else {
        n = 16;
    }
    return CopyBytes(r2, r1, n);
}

/* A frame being unwound: the unwind table entry at 4, the register slots from 0x10. */
typedef struct Tag_1FE198 {
    u32 word;
} Tag_1FE198;

typedef struct __attribute__((aligned(8))) Frame_1FE198 {
    s32 f0;
    Tag_1FE198* f4;
    s32 f8;
    s32 fC;
    s32 f10[0xA2];
    u16 f298;
    u16 f29A;
    s8 f29C[0x54];
} Frame_1FE198;

typedef struct Pc_1FE198 Pc_1FE198;

Frame_1FE198* func_001FE100(Pc_1FE198* a0, Frame_1FE198* a1, Frame_1FE198* a2)
{
    Frame_1FE198* s0 = (Frame_1FE198*)func_001FFC80(a0, (UnwindFrame*)a2);
    u16 idx;
    if (s0 == 0) {
        return 0;
    }
    idx = s0->f298;
    if (*(s8*)((u8*)a1 + idx + 0x29C) != 0) {
        s64 v = *(s64*)func_001FDFF8(idx, (Obj_1FDFF8*)a1, 0);
        s0->f0 = (s32)v;
    } else {
        s0->f0 = a1->f0;
    }
    s0->f0 += s0->f8;
    return s0;
}

void func_001FE190(void) {}

typedef struct Obj_1FE198 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
} Obj_1FE198;

static inline Pc_1FE198* ReturnAddr_1FE198(Frame_1FE198* f, Frame_1FE198* g)
{
    s64 w = *(s64*)func_001FDFF8(f->f29A, (Obj_1FDFF8*)f, (Obj_1FDFF8*)g);
    return (Pc_1FE198*)(s32)w;
}

static inline s32 RegWindow_1FE198_In(s32 i, Frame_1FE198* f)
{
    return 0;
}

void* func_001FE198(EhContext* eh, void* pc_, UnwindFrame* fb_, UnwindFrame** pout_)
{
    Obj_1FE198* obj = (Obj_1FE198*)eh;
    Pc_1FE198* pc = (Pc_1FE198*)pc_;
    Frame_1FE198* fb = (Frame_1FE198*)fb_;
    Frame_1FE198** pout = (Frame_1FE198**)pout_;
    Frame_1FE198 sub;
    Frame_1FE198 saved;
    Frame_1FE198* udata = *pout;
    Frame_1FE198* subp = &sub;
    Pc_1FE198* startPc = pc;
    s32 res = 0;
    s32 pending = obj->fC != 0;
    Ctx_001FDEB0* a8 = (Ctx_001FDEB0*)obj->f8;
    s32 cleanup;
    s32 savedRes;
    Pc_1FE198* savedPc;
    s32 onlyCleanup;
    s32 savedState;
    s32 i;

    onlyCleanup = 0;
    savedState = 0;
    cleanup = 0;
    for (;;) {
        Frame_1FE198* p = udata;
        s32 isNew;
        udata = func_001FE100(pc, udata, subp);
        subp = p;
        if (udata == 0) {
            break;
        }
        if (udata->f4 == 0) {
            isNew = 0;
        } else {
            isNew = udata->f4->word == 0xFFFFFFFEu;
        }
        if (pending) {
            pending = 0;
            res = func_001FDEB0(obj->fC, udata->f4, a8, 1, &cleanup);
            obj->fC = 0;
        } else if (isNew) {
            res = func_001FDEB0((s32)pc, udata->f4, a8, 0, &cleanup);
        } else {
            res = func_001FDDD8((u32)pc, (Range_1FDDD8*)udata->f4);
        }
        if (res != 0) {
            if (cleanup != 0) {
                if (savedState == 0) {
                    saved = *udata;
                    savedPc = pc;
                    savedRes = res;
                    savedState = 1;
                    onlyCleanup = 1;
                }
            } else {
                onlyCleanup = 0;
                break;
            }
        }
        pc = (Pc_1FE198*)((s8*)ReturnAddr_1FE198(udata, subp) - 1);
    }
    if (savedState != 0) {
        udata = &saved;
        res = savedRes;
        pc = savedPc;
        if (onlyCleanup != 0) {
            func_001FE190();
        }
    }
    if (res == 0) {
        func_001FD930();
    }
    obj->f0 = res;
    if (pc == startPc) {
        udata = fb;
    } else {
        Pc_1FE198* handlerPc = pc;
        pc = startPc;
        *udata = *fb;
        while (pc != handlerPc) {
            Frame_1FE198* p = udata;
            udata = func_001FE100(pc, udata, subp);
            subp = p;
            for (i = 0; i < 0x4F; i++) {
                if (i != udata->f29A && udata->f29C[i] != 0) {
                    func_001FE080(i, (u32)udata, (u32)fb);
                }
            }
            pc = (Pc_1FE198*)((s8*)ReturnAddr_1FE198(udata, subp) - 1);
        }
        if (udata->f29C[udata->f29A] == 2) {
            i = udata->f10[udata->f29A];
            if (RegWindow_1FE198_In(i, udata)) {
                func_001FE080(i, (u32)udata, (u32)fb);
            }
        }
    }
    *pout = udata;
    return (void*)res;
}

/* Rethrow: unwind from the caller to the handler of the exception being handled. */
void func_001FE4C8(void)
{
    EhContext* ctx = (*D_0027804C)();
    UnwindFrame mine, copy;
    UnwindFrame* cur = &mine;
    UnwindFrame* cp = &copy;
    void* handler;
    s32 offset;

    if (ctx->f8 == 0)
        func_001FD930();

    __builtin_unwind_init();
here:
    cur = func_001FFC80(&&here, cur);
    if (cur == 0)
        func_001FD930();
    cur->cfa = (s32)__builtin_dwarf_cfa();
    *cp = *cur;
    handler = func_001FE198(ctx, (char*)__builtin_return_address(0) - 1, cp, &cur);
    offset = cur->cfa - cp->cfa;
    __builtin_eh_return(ctx, offset, handler);
}

/* Throw: the same, after recording the index the thrower passes. */
void func_001FE6A8(void* index)
{
    EhContext* ctx = (*D_0027804C)();
    UnwindFrame mine, copy;
    UnwindFrame* cur = &mine;
    UnwindFrame* cp = &copy;
    void* handler;
    s32 offset;

    if (ctx->f8 == 0)
        func_001FD930();
    ctx->fC = (s32)index;

    __builtin_unwind_init();
here:
    cur = func_001FFC80(&&here, cur);
    if (cur == 0)
        func_001FD930();
    cur->cfa = (s32)__builtin_dwarf_cfa();
    *cp = *cur;
    handler = func_001FE198(ctx, (char*)__builtin_return_address(0) - 1, cp, &cur);
    offset = cur->cfa - cp->cfa;
    __builtin_eh_return(ctx, offset, handler);
}
