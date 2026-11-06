// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"

// The game's memory: the heap's bounds, its permanent, front and back cursors (the back one
// with a stack of marks, under a lock), the copy routines, and the allocation hooks the
// libraries call.

extern u8 D_0064C70F[];

s32 D_002699A4 = 0;
s32 D_002699A8;

extern s32 D_002C2A10;
extern u8* D_002C2A14;
extern u8* D_002C2A18;
extern u8* D_002C2A1C;
extern u8* D_002C2A20;
extern s32 D_002C2A24;
extern u8 D_002C2A28[];
extern s32 D_002C2A34;
extern u8 D_002C2A38[];

void func_001F5C0C(void* p, s32 v, s32 n);
void func_001E22C0(void* self);
void func_001E22F8(void* obj);
void func_001E2358(void* obj);

void func_0018D4F8(s32 size);
u8* func_0018D500(s32 size);
void* func_0018D5C0(u32 n);
u8* func_0018D658(s32 size);

typedef u64 Q18D780 __attribute__((mode(TI)));

void func_0018D780(void* dst, void* src, u32 count);

void func_0018D410(void* p)
{
    func_001F5C0C(p, 0, 8);
}

void func_0018D430(void)
{
    g_heapStart = (s32)g_imageEnd & -16;
    g_heapEnd = 0x2000000;
    // The heap's pointers (u8* elsewhere in this file), written as words.
    D_002C2A10 = *(s32*)&g_permanentCursor = *(s32*)&g_frontResetMark = *(s32*)&g_frontCursor = g_heapStart;
    *(s32*)&g_backCursor = D_002C2A24 = g_heapEnd;
    g_backMarkIndex = -1;
    InitRecursiveLock(g_heapLock);
}

u8* func_0018D4B0(s32 size)
{
    u8* result;
    u8* next;

    if (size == 0) {
        return 0;
    }
    result = g_permanentCursor;
    next = result + ((size + 15) & ~15);
    g_permanentCursor = next;
    g_frontResetMark = g_frontCursor = next;
    return result;
}

LINKER_REMNANT(func_0018D4F0);

void func_0018D4F8(s32 size)
{
    (void)size;
}

u8* func_0018D500(s32 size)
{
    u8* result;

    if (size == 0) {
        return 0;
    }
    func_0018D4F8(size);
    result = g_frontCursor;
    g_frontCursor = result + ((size + 15) & ~15);
    return result;
}

void func_0018D550(void)
{
    g_frontCursor = g_frontResetMark;
}

void func_0018D800(u8* dst, void* src, s32 count);

u8* func_0018D568(s32 size, void* src)
{
    u8* result = AllocateFrontMemory(size);

    if (result != 0) {
        CopyMemory(result, src, size);
    }
    return result;
}

void* func_0018D5C0(u32 n)
{
    void* p = AllocateFrontMemory(n);
    if (p) {
        func_001F5C0C(p, 0, n);
    }
    return p;
}

void func_0018D608(void)
{
    EnterRecursiveLock(g_heapLock);
    g_backMarkIndex = g_backMarkIndex + 1;
    ((u8**)g_backMarks)[g_backMarkIndex] = g_backCursor;
}

u8* func_0018D658(s32 size)
{
    u8* result;

    if (size == 0) {
        return 0;
    }
    func_0018D4F8(size);
    result = g_backCursor;
    result = result - ((size + 15) & ~15);
    g_backCursor = result;
    return result;
}

void* func_0018D6A8(s32 size)
{
    u8* p = AllocateBackMemory(size);
    if (p) {
        func_001F5C0C(p, 0, size);
    }
    return p;
}

void func_0018D6F0(void)
{
    s32 n = g_backMarkIndex;
    u8** slot = &((u8**)g_backMarks)[n];
    n = n - 1;
    g_backMarkIndex = n;
    g_backCursor = *slot;
    LeaveRecursiveLock(g_heapLock);
}

int func_0018D740(void)
{
    return 0;
}

s32 func_0018D748() { return 0; }

void func_0018D750() {}

void* func_0018D758(u32 n)
{
    return AllocateZeroedFrontMemory(n);
}

void func_0018D778(void* self)
{
}

void func_0018D780(Q18D780* dst, Q18D780* src, s32 n)
{
    Q18D780* d = dst;
    Q18D780* s = src;
    s32 rem = n & 3;
    s32 total = n - rem;
    s32 k;
    if (rem != 0) {
        k = rem;
        do {
            *d++ = *s++;
        } while (--k != 0);
    }
    if (total > 0) {
        k = 0;
        do {
            Q18D780 q0 = s[0];
            Q18D780 q1 = s[1];
            Q18D780 q2 = s[2];
            Q18D780 q3 = s[3];
            s += 4;
            k += 4;
            d[0] = q0;
            d[1] = q1;
            d[2] = q2;
            d[3] = q3;
            d += 4;
        } while (k < total);
    }
}

void func_0018D800(u8* dst, u8* src, u32 size)
{
    u32 any = (u32)dst | (u32)src | size;
    if (any & 3) {
        u32 i = 0;
        if (size != 0) {
            do {
                *dst++ = *src++;
                i++;
            } while (i < size);
        }
    } else if (any & 0xF) {
        s32 words = size >> 2;
        u32* wd = (u32*)dst;
        size = words & 3;
        u32* ws = (u32*)src;
        s32 i;
        s32 blocks = words - size;
        if (size != 0) {
            i = size;
            do {
                *wd++ = *ws++;
                i--;
            } while (i != 0);
        }
        if (blocks > 0) {
            i = 0;
            do {
                u32 a = ws[0];
                i += 4;
                u32 b = ws[1];
                u32 c = ws[2];
                u32 d = ws[3];
                wd[0] = a;
                ws += 4;
                wd[1] = b;
                wd[2] = c;
                wd[3] = d;
                wd += 4;
            } while (i < blocks);
        }
    } else {
        CopyQuadwords(dst, src, size >> 4);
    }
}
