// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "key_id.h"
#include "functions/heap.h"
#include "functions/text_format.h"
struct RecursiveLock;


// The game's memory: the heap's bounds, its permanent, front and back cursors (the back one
// with a stack of marks, under a lock), the copy routines, and the allocation hooks the
// libraries call.

extern u8 g_imageEnd[];

s32 g_heapStart = 0;
s32 g_heapEnd;

extern s32 D_002C2A10;
extern u8* g_permanentCursor;
extern u8* g_frontResetMark;
extern u8* g_frontCursor;
extern u8* g_backCursor;
extern s32 D_002C2A24;
extern u8 g_heapLock[];
extern s32 g_backMarkIndex;
extern u8 g_backMarks[];

extern "C" void* FillMemory(void* p, s32 value, s32 size);


typedef u64 Q18D780 __attribute__((mode(TI)));


// Zeroes an 8-byte key id.
void ClearKeyId(KeyId* p)
{
    FillMemory(p, 0, 8);
}

// Sets up the main heap: the front, permanent and back cursors all start at the end of the loaded
// image (16-aligned) or at the 32 MB top, the back-mark stack is emptied and the heap lock is
// initialised.
void InitHeap(void)
{
    g_heapStart = (s32)g_imageEnd & -16;
    g_heapEnd = 0x2000000;
    // The heap's pointers (u8* elsewhere in this file), written as words.
    D_002C2A10 = *(s32*)&g_permanentCursor = *(s32*)&g_frontResetMark = *(s32*)&g_frontCursor = g_heapStart;
    *(s32*)&g_backCursor = D_002C2A24 = g_heapEnd;
    g_backMarkIndex = -1;
    InitRecursiveLock((RecursiveLock*)g_heapLock);
}

// Takes size bytes (rounded up to 16) at the permanent cursor and moves the front cursor and its
// reset mark past them, so ResetFrontMemory no longer frees them.
u8* ReservePermanentMemory(s32 size)
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

// Empty: the size check of the original allocator is compiled out of retail.
void CheckAllocationSize(s32 size)
{
    (void)size;
}

// Bump-allocates size bytes (rounded up to 16) at the heap's front cursor; gives back 0 for a size
// of 0. Never freed one by one: ResetFrontMemory drops all of them.
u8* AllocateFrontMemory(s32 size)
{
    u8* result;

    if (size == 0) {
        return 0;
    }
    CheckAllocationSize(size);
    result = g_frontCursor;
    g_frontCursor = result + ((size + 15) & ~15);
    return result;
}

// Frees every front allocation made since the permanent reservations, by putting the front cursor
// back to its reset mark.
void ResetFrontMemory(void)
{
    g_frontCursor = g_frontResetMark;
}


// Allocates size bytes from the front of the heap and copies src into them; gives back the new
// block, or 0 for a zero size.
u8* CopyToFrontMemory(s32 size, void* src)
{
    u8* result = AllocateFrontMemory(size);

    if (result != 0) {
        CopyMemory(result, src, size);
    }
    return result;
}

// AllocateFrontMemory, then clears the n bytes; 0 if nothing was allocated.
void* AllocateZeroedFrontMemory(s32 n)
{
    void* p = AllocateFrontMemory(n);
    if (p) {
        FillMemory(p, 0, n);
    }
    return p;
}

// Takes the heap lock and records the back cursor on the mark stack, so PopBackMemoryMark can free
// what is allocated from the back after this.
void PushBackMemoryMark(void)
{
    EnterRecursiveLock((RecursiveLock*)g_heapLock);
    g_backMarkIndex = g_backMarkIndex + 1;
    ((u8**)g_backMarks)[g_backMarkIndex] = g_backCursor;
}

// Bump-allocates size bytes (rounded up to 16) downward from the heap's top end; gives back 0 for a
// size of 0. PopBackMemoryMark releases everything allocated since the matching mark.
u8* AllocateBackMemory(s32 size)
{
    u8* result;

    if (size == 0) {
        return 0;
    }
    CheckAllocationSize(size);
    result = g_backCursor;
    result = result - ((size + 15) & ~15);
    g_backCursor = result;
    return result;
}

// AllocateBackMemory, then clears the size bytes; 0 if nothing was allocated.
void* AllocateZeroedBackMemory(s32 size)
{
    u8* p = AllocateBackMemory(size);
    if (p) {
        FillMemory(p, 0, size);
    }
    return p;
}

// Restores the back cursor to the last mark pushed (freeing every back allocation made since) and
// releases the heap lock PushBackMemoryMark took.
void PopBackMemoryMark(void)
{
    s32 n = g_backMarkIndex;
    u8** slot = &((u8**)g_backMarks)[n];
    n = n - 1;
    g_backMarkIndex = n;
    g_backCursor = *slot;
    LeaveRecursiveLock((RecursiveLock*)g_heapLock);
}

// The allocation hooks the C runtime calls (throw.c, unwind.c, signal.c): a size in, nothing
// allocated.
struct LibcState;

extern "C" void* EnterRuntimeLock(u32 size)
{
    return 0;
}

extern "C" void* AllocateSignalTable(LibcState* state, s32 size) { return 0; }

extern "C" void LeaveRuntimeLock(void* p) {}

// The allocator for game objects: zeroed memory from the front of the heap.
void* AllocateObjectMemory(u32 n)
{
    return AllocateZeroedFrontMemory(n);
}

// Does nothing: front-heap memory is never freed one block at a time.
void FreeObjectMemory(void* self)
{
}

// Copies n quadwords (16 bytes each) from src to dst: the n % 4 leftovers first, one at a time,
// then the rest four quadwords per pass.
void CopyQuadwords(void* dst, void* src, s32 n)
{
    Q18D780* d = (Q18D780*)dst;
    Q18D780* s = (Q18D780*)src;
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

// memcpy of the game: byte by byte when the addresses or the size are not word aligned; word by
// word (the remainder first, then four words per step) when they are word aligned only; and
// CopyQuadwords when all three are 16-byte aligned.
void CopyMemory(void* dst, void* src, u32 size)
{
    u32 any = (u32)dst | (u32)src | size;
    if (any & 3) {
        u32 i = 0;
        if (size != 0) {
            u8* d = (u8*)dst;
            u8* s = (u8*)src;
            do {
                *d++ = *s++;
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
