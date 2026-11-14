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

/* A frame's unwind table entry: its first word is 0xFFFFFFFE when the frame has no handler. */
typedef struct UnwindEntry {
    u32 word;
} UnwindEntry;

/* A frame's unwind state, 0x2F0 bytes: its canonical frame address, the unwind table entry of
 * its code, then the registers it saved: a table of 8-byte values (what each register held)
 * and, from 0x29C, how each is kept (1: in memory at the address above, 2: as another
 * register), read by ResolveSavedRegisterSlot. The 4-byte words from 0x10 are the same bytes
 * (FindHandlerAndRestoreRegisters reads the alias of a register that way). */
typedef struct __attribute__((aligned(8))) UnwindFrame {
    s32 cfa;                /* 0x00 */
    UnwindEntry* entry;     /* 0x04 */
    s32 cfaAdjust;          /* 0x08 */
    s32 fC;                 /* 0x0C */
    union {
        s32 words[0xA2];    /* 0x10 */
        struct {
            u8 pad10[8];
            s64 tbl[80];    /* 0x18 */
        } wide;
    } saved;
    u16 cfaReg;               /* 0x298 */
    u16 returnReg;               /* 0x29A */
    s8 how[0x54];          /* 0x29C: 0 unsaved, 1 in memory, 2 alias */
} UnwindFrame;

typedef char check_UnwindFrame[sizeof(UnwindFrame) == 0x2F0 ? 1 : -1];

typedef struct ActiveException ActiveException;
/* The record of the exception being handled: the function that asks whether it matches a type. */
struct ActiveException {
    s32 (*match)(ActiveException* self, void* type, void* extra);
};

/* The runtime's exception context, one per thread (GetExceptionContext): the handler found at 0,
 * the chain of handlers at 4, the active exception at 8 and the index a throw recorded at 0xC. */
typedef struct EhContext {
    s32 handler;            /* 0x00 */
    void** chain;           /* 0x04 */
    ActiveException* active; /* 0x08 */
    s32 pending;            /* 0x0C */
} EhContext;

UnwindFrame* FindFrameUnwindState(void* pc, UnwindFrame* frame);
void* FillMemory(void* p, s32 value, s32 size);
s32 CopyBytes(void* dst, void* src, s32 n);
s32 CompareStrings(void* self, s32 v);
void* EnterRuntimeLock(u32 size);
void AbortProgram(void) __attribute__((noreturn));

void AbortOnTerminate(void);
EhContext* GetStaticExceptionContext(void);
void InstallExceptionContextGetter(void);

/* The terminate hook, and the function that returns the exception context. */
void (*D_00278048)(void) = AbortOnTerminate;
EhContext* (*g_exceptionContextGetter)(void) = (EhContext* (*)(void))InstallExceptionContextGetter;

void AbortOnTerminate(void)
{
    AbortProgram();
}

void RunTerminateHook(void)
{
    (*D_00278048)();
}

s32 SelectArgumentIfTypeNamesEqual(void* self, s32 v, s32 fallback)
{
    s32 result = fallback;
    if (CompareStrings(self, v) != 0) {
        result = 0;
    }
    return result;
}

void DoNothingForExceptionRuntime(void) {}

/* The 0x18-byte block the runtime allocates zeroed, its word at 4 pointing to its own 0x10. */
typedef struct ExceptionBlock {
    s32 f0;
    u8* f4;
    s32 f8;
    s32 fc;
    s32 f10;
    s32 f14;
} ExceptionBlock;

ExceptionBlock* AllocateZeroedNodeOrTerminate(void)
{
    ExceptionBlock* p = (ExceptionBlock*)EnterRuntimeLock(0x18);
    if (p == 0) {
        RunTerminateHook();
    }
    (void)FillMemory(p, 0, 0x18);
    p->f4 = (u8*)p + 0x10;
    return p;
}

s32 GetExceptionContext(void)
{
    return (s32)(*g_exceptionContextGetter)();
}

u8* GetActiveExceptionSlot(void)
{
    return (u8*)(*g_exceptionContextGetter)() + 8;
}

void InstallExceptionContextGetter(void)
{
    void (*f)(void) = (void (*)(void))GetStaticExceptionContext;
    g_exceptionContextGetter = (EhContext* (*)(void))f;
    f();
}


static EhContext g_staticExceptionContext;
static s32 g_staticExceptionContextReady;
static void* g_staticHandlerChain[2];

EhContext* GetStaticExceptionContext(void)
{
    if (g_staticExceptionContextReady == 0) {
        g_staticExceptionContextReady = 1;
        (void)FillMemory(&g_staticExceptionContext, 0, 0x10);
        g_staticExceptionContext.chain = g_staticHandlerChain;
    }
    return (EhContext*)&g_staticExceptionContext;
}

u8* GetHandlerChainSlot(void)
{
    return (u8*)(*g_exceptionContextGetter)() + 4;
}


void ThrowToTopHandler(void) __attribute__((noreturn));

/* Throws: runs the cleanups registered in the top handler, then jumps to that handler. */
void ThrowToTopHandler(void)
{
    EhContext* ctx = (EhContext*)(*g_exceptionContextGetter)();
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
            RunTerminateHook();
        }
    }

    if (ctx->active == 0 || (*chain)[0] == 0) {
        RunTerminateHook();
    }

    buf = &(*chain)[2];
    *chain = (void**)(*chain)[0];
    __builtin_longjmp(buf, 1);
}

/* Pops the top handler after running its cleanups, then throws again. */
void PopHandlerAndThrow(void)
{
    EhContext* ctx = (EhContext*)(*g_exceptionContextGetter)();
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
            RunTerminateHook();
        }
    }

    *chain = (void**)(*chain)[0];
    ThrowToTopHandler();
}

/* The active exception, asked whether it matches a runtime type through its matcher. */

s32 ActiveExceptionMatches(void* type)
{
    ActiveException* info = *(ActiveException**)GetActiveExceptionSlot();
    s32 (*match)(ActiveException*, void*, void*) = info->match;
    if (match == 0) {
        return 0;
    }
    return match(info, type, 0) != 0;
}

s16 GetExceptionRecordSubkind(void* object)
{
    return *(s16*)((u8*)object + 6);
}

s16 GetExceptionRecordKind(void* object)
{
    return *(s16*)((u8*)object + 4);
}

typedef struct UnwindRange {
    u32 lo;
    u32 hi;
    s32 value;
} UnwindRange;

s32 FindInnermostRangeValue(u32 key, UnwindRange* t)
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

/* An entry of a handler span table: the code range it covers, its handler and the matcher's
 * argument (0 for a cleanup). */
typedef struct HandlerSpan {
    u32 lo;
    u32 hi;
    s32 value;
    void* cb;
} HandlerSpan;
/* The pending record the context's word at 0xC points to: its count is the key to resume from. */
typedef struct PendingHandlerRecord {
    s32 pad0;
    s32 count;
} PendingHandlerRecord;

s32 FindHandlerInSpanTable(s32 a0, void* a1, ActiveException* a2, s32 a3, s32* a4)
{
    s32 result = 0;
    s32 key = a0;
    HandlerSpan* base;
    s32 idx;
    s32 r;

    *a4 = 1;
    if (a1 != 0) {
        idx = 0;
        base = (HandlerSpan*)((u8*)a1 + 8);
        if (a3 != 0) {
            idx = ((u8*)a0 - (u8*)base) >> 4;
            key = ((PendingHandlerRecord*)a0)->count - 1;
            if (base[idx].lo != 0xFFFFFFFF) {
                idx++;
            }
        } else {
            key = key - 1;
        }
        while (base[idx].lo != 0xFFFFFFFF) {
            if ((u32)key >= base[idx].lo && (u32)key < base[idx].hi) {
                if (base[idx].cb != 0) {
                    if (a2->match != 0) {
                        r = a2->match(a2, base[idx].cb, a1);
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

u8* ResolveSavedRegisterSlot(u32 idx, UnwindFrame* self, UnwindFrame* other)
{
    while (self->how[idx] == 2) {
        idx = self->saved.wide.tbl[idx];
    }
    if (self->how[idx] == 1) {
        return (u8*)self->cfa + self->saved.wide.tbl[idx];
    }
    AbortProgram();
}

s32 CopySavedRegister(s32 a0, u32 a1, u32 a2)
{
    u8* r1 = ResolveSavedRegisterSlot(a0, (UnwindFrame*)a1, 0);
    u8* r2 = ResolveSavedRegisterSlot(a0, (UnwindFrame*)a2, 0);
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

typedef struct CodeAddress CodeAddress;

UnwindFrame* UnwindOneFrame(CodeAddress* a0, UnwindFrame* a1, UnwindFrame* a2)
{
    UnwindFrame* s0 = FindFrameUnwindState(a0, a2);
    u16 idx;
    if (s0 == 0) {
        return 0;
    }
    idx = s0->cfaReg;
    if (*(s8*)((u8*)a1 + idx + 0x29C) != 0) {
        s64 v = *(s64*)ResolveSavedRegisterSlot(idx, (UnwindFrame*)a1, 0);
        s0->cfa = (s32)v;
    } else {
        s0->cfa = a1->cfa;
    }
    s0->cfa += s0->cfaAdjust;
    return s0;
}

void NoteCleanupOnlyHandler(void) {}

static inline CodeAddress* FrameReturnAddress(UnwindFrame* f, UnwindFrame* g)
{
    s64 w = *(s64*)ResolveSavedRegisterSlot(f->returnReg, (UnwindFrame*)f, (UnwindFrame*)g);
    return (CodeAddress*)(s32)w;
}

static inline s32 RegisterInWindow(s32 i, UnwindFrame* f)
{
    return 0;
}

void* FindHandlerAndRestoreRegisters(EhContext* eh, void* pc_, UnwindFrame* fb_, UnwindFrame** pout_)
{
    EhContext* obj = eh;
    CodeAddress* pc = (CodeAddress*)pc_;
    UnwindFrame* fb = (UnwindFrame*)fb_;
    UnwindFrame** pout = (UnwindFrame**)pout_;
    UnwindFrame sub;
    UnwindFrame saved;
    UnwindFrame* udata = *pout;
    UnwindFrame* subp = &sub;
    CodeAddress* startPc = pc;
    s32 res = 0;
    s32 pending = obj->pending != 0;
    ActiveException* a8 = obj->active;
    s32 cleanup;
    s32 savedRes;
    CodeAddress* savedPc;
    s32 onlyCleanup;
    s32 savedState;
    s32 i;

    onlyCleanup = 0;
    savedState = 0;
    cleanup = 0;
    for (;;) {
        UnwindFrame* p = udata;
        s32 isNew;
        udata = UnwindOneFrame(pc, udata, subp);
        subp = p;
        if (udata == 0) {
            break;
        }
        if (udata->entry == 0) {
            isNew = 0;
        } else {
            isNew = udata->entry->word == 0xFFFFFFFEu;
        }
        if (pending) {
            pending = 0;
            res = FindHandlerInSpanTable(obj->pending, udata->entry, a8, 1, &cleanup);
            obj->pending = 0;
        } else if (isNew) {
            res = FindHandlerInSpanTable((s32)pc, udata->entry, a8, 0, &cleanup);
        } else {
            res = FindInnermostRangeValue((u32)pc, (UnwindRange*)udata->entry);
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
        pc = (CodeAddress*)((s8*)FrameReturnAddress(udata, subp) - 1);
    }
    if (savedState != 0) {
        udata = &saved;
        res = savedRes;
        pc = savedPc;
        if (onlyCleanup != 0) {
            NoteCleanupOnlyHandler();
        }
    }
    if (res == 0) {
        RunTerminateHook();
    }
    obj->handler = res;
    if (pc == startPc) {
        udata = fb;
    } else {
        CodeAddress* handlerPc = pc;
        pc = startPc;
        *udata = *fb;
        while (pc != handlerPc) {
            UnwindFrame* p = udata;
            udata = UnwindOneFrame(pc, udata, subp);
            subp = p;
            for (i = 0; i < 0x4F; i++) {
                if (i != udata->returnReg && udata->how[i] != 0) {
                    CopySavedRegister(i, (u32)udata, (u32)fb);
                }
            }
            pc = (CodeAddress*)((s8*)FrameReturnAddress(udata, subp) - 1);
        }
        if (udata->how[udata->returnReg] == 2) {
            i = udata->saved.words[udata->returnReg];
            if (RegisterInWindow(i, udata)) {
                CopySavedRegister(i, (u32)udata, (u32)fb);
            }
        }
    }
    *pout = udata;
    return (void*)res;
}

/* Rethrow: unwind from the caller to the handler of the exception being handled. */
void RethrowActiveException(void)
{
    EhContext* ctx = (*g_exceptionContextGetter)();
    UnwindFrame mine, copy;
    UnwindFrame* cur = &mine;
    UnwindFrame* cp = &copy;
    void* handler;
    s32 offset;

    if (ctx->active == 0)
        RunTerminateHook();

    __builtin_unwind_init();
here:
    cur = FindFrameUnwindState(&&here, cur);
    if (cur == 0)
        RunTerminateHook();
    cur->cfa = (s32)__builtin_dwarf_cfa();
    *cp = *cur;
    handler = FindHandlerAndRestoreRegisters(ctx, (char*)__builtin_return_address(0) - 1, cp, &cur);
    offset = cur->cfa - cp->cfa;
    __builtin_eh_return(ctx, offset, handler);
}

/* Throw: the same, after recording the index the thrower passes. */
void ThrowException(void* index)
{
    EhContext* ctx = (*g_exceptionContextGetter)();
    UnwindFrame mine, copy;
    UnwindFrame* cur = &mine;
    UnwindFrame* cp = &copy;
    void* handler;
    s32 offset;

    if (ctx->active == 0)
        RunTerminateHook();
    ctx->pending = (s32)index;

    __builtin_unwind_init();
here:
    cur = FindFrameUnwindState(&&here, cur);
    if (cur == 0)
        RunTerminateHook();
    cur->cfa = (s32)__builtin_dwarf_cfa();
    *cp = *cur;
    handler = FindHandlerAndRestoreRegisters(ctx, (char*)__builtin_return_address(0) - 1, cp, &cur);
    offset = cur->cfa - cp->cfa;
    __builtin_eh_return(ctx, offset, handler);
}
