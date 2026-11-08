// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 600/612, checked 2026-11-08
/* NEAR: in its file, src/lib/unwind.c (the Linux cc1 of 2.9-ee-991111). The checks, the split,
 * the merge and the free match, and the loops have retail's shape (the sift loop entered at its
 * test, which the statement `j = 2 * i + 1` at the top of its body gives; without it the test is
 * copied ahead of the loop). Left: retail keeps 2 * i in a register across the sift loop (its
 * update recomputes it, the right child's bound and new index are 2 * i + 2 from it, the left
 * child's index 2 * i + 1) and addresses both children from i * 8; ours keeps 2 * i + 1 and the
 * registers differ throughout. Tried: j = 2 * i (worse), j in the loop's condition or update,
 * the children indexed through j. Written for this project from retail's code. */
#include "common.h"

typedef struct FrameDesc FrameDesc;
typedef struct FrameList {
    FrameDesc** items;
    s32 count;
    FrameDesc** other;
    s32 unused;
    u32 lo;
    s32 hi;
} FrameList;
typedef struct KeyedElem {
    s32 a;
    s32 b;
    s32 key;
} KeyedElem;
typedef struct KeyedArray {
    KeyedElem** data;
    u32 count;
} KeyedArray;

void AbortProgram(void) __attribute__((noreturn));
void LeaveRuntimeLock(void* p);
void func_001FF0E0(KeyedArray* self, KeyedArray* other);
void func_001FFE58(KeyedArray* self, KeyedArray* out);

static inline void HeapifyFrames(KeyedElem** a, u32 lo, u32 hi)
{
    u32 i, j;
    KeyedElem* t;

    for (i = lo; 2 * i + 1 < hi;) {
        j = 2 * i + 1;
        if (j + 1 < hi && a[2 * i + 2]->key - a[2 * i + 1]->key > 0
            && a[2 * i + 2]->key - a[i]->key > 0) {
            t = a[i];
            a[i] = a[2 * i + 2];
            a[2 * i + 2] = t;
            i = j + 1;
        } else if (a[2 * i + 1]->key - a[i]->key > 0) {
            t = a[i];
            a[i] = a[2 * i + 1];
            a[2 * i + 1] = t;
            i = j;
        } else
            break;
    }
}

static inline void SortFrames(KeyedArray* erratic)
{
    KeyedElem** a = erratic->data;
    u32 n = erratic->count;
    u32 m;
    KeyedElem* t;

    for (m = n; m != 0;)
        HeapifyFrames(a, --m, n);
    while (n > 1) {
        t = a[0];
        a[0] = a[n - 1];
        a[n - 1] = t;
        HeapifyFrames(a, 0, --n);
    }
}

FrameDesc** func_001FF1E0(FrameList* list, s32 count)
{
    if (list->count != count)
        AbortProgram();
    func_001FFE58((KeyedArray*)list, (KeyedArray*)&list->other);
    if (list->count + list->unused != count)
        AbortProgram();
    SortFrames((KeyedArray*)&list->other);
    func_001FF0E0((KeyedArray*)list, (KeyedArray*)&list->other);
    LeaveRuntimeLock(list->other);
    return list->items;
}
