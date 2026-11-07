// SPDX-License-Identifier: AGPL-3.0-or-later
// The C library's sort, its own object from 0x1F5CD0 to 0x1F66F4, padded to 0x1F66F8 where the
// next object starts on 8 (config/us/files.tsv): one function, word for word a member of the
// toolchain's libc.a built from a .c source. No data of its own.
#include "common.h"

// Sorts n elements of size bytes each in place with a three-way-partition quicksort:
// insertion sort below seven elements, a median of three (of nine above forty) as the
// pivot, elements equal to it gathered at both ends and moved to the middle afterwards.
typedef s32 (*Compare_1F5CD0)(const void* x, const void* y);

struct Sort_1F5CD0 {
    // Exchanges count bytes at x and y, by 64-bit words when kind allows it.
    static inline void Exchange(char* x, char* y, s32 count, s32 kind)
    {
        if (kind <= 1) {
            s64 i = count / sizeof(s64);
            s64* p = (s64*)x;
            s64* q = (s64*)y;
            do {
                s64 t = *p;
                *p++ = *q;
                *q++ = t;
            } while (--i > 0);
        } else {
            s64 i = count / sizeof(char);
            char* p = x;
            char* q = y;
            do {
                char t = *p;
                *p++ = *q;
                *q++ = t;
            } while (--i > 0);
        }
    }

    // The middle one of three elements.
    static inline char* Median(char* x, char* y, char* z, Compare_1F5CD0 compare)
    {
        return compare(x, y) < 0
            ? (compare(y, z) < 0 ? y : (compare(x, z) < 0 ? z : x))
            : (compare(y, z) > 0 ? y : (compare(x, z) < 0 ? x : z));
    }
};

#define SWAP_1F5CD0(x, y) \
    if (kind == 0) { \
        s64 t = *(s64*)(x); \
        *(s64*)(x) = *(s64*)(y); \
        *(s64*)(y) = t; \
    } else \
        Sort_1F5CD0::Exchange(x, y, size, kind)

#define BLOCKSWAP_1F5CD0(x, y, count) \
    if ((count) > 0) Sort_1F5CD0::Exchange(x, y, count, kind)

void func_001F5CD0(void* base, u32 n, u32 size, Compare_1F5CD0 compare)
{
    char *pa, *pb, *pc, *pd, *pl, *pm, *pn;
    s32 d, r, kind, swapped;

again:
    kind = ((u32)base % sizeof(s64)) || size % sizeof(s64) ? 2 : size == sizeof(s64) ? 0 : 1;
    swapped = 0;
    if (n < 7) {
        for (pm = (char*)base + size; pm < (char*)base + n * size; pm += size) {
            for (pl = pm; pl > (char*)base && compare(pl - size, pl) > 0; pl -= size) {
                SWAP_1F5CD0(pl, pl - size);
            }
        }
        return;
    }
    pm = (char*)base + (n / 2) * size;
    if (n > 7) {
        pl = (char*)base;
        pn = (char*)base + (n - 1) * size;
        if (n > 40) {
            d = (n / 8) * size;
            pl = Sort_1F5CD0::Median(pl, pl + d, pl + 2 * d, compare);
            pm = Sort_1F5CD0::Median(pm - d, pm, pm + d, compare);
            pn = Sort_1F5CD0::Median(pn - 2 * d, pn - d, pn, compare);
        }
        pm = Sort_1F5CD0::Median(pl, pm, pn, compare);
    }
    SWAP_1F5CD0((char*)base, pm);
    pa = pb = (char*)base + size;
    pc = pd = (char*)base + (n - 1) * size;
    for (;;) {
        while (pb <= pc && (r = compare(pb, base)) <= 0) {
            if (r == 0) {
                swapped = 1;
                SWAP_1F5CD0(pa, pb);
                pa += size;
            }
            pb += size;
        }
        while (pb <= pc && (r = compare(pc, base)) >= 0) {
            if (r == 0) {
                swapped = 1;
                SWAP_1F5CD0(pc, pd);
                pd -= size;
            }
            pc -= size;
        }
        if (pb > pc) {
            break;
        }
        SWAP_1F5CD0(pb, pc);
        swapped = 1;
        pb += size;
        pc -= size;
    }
    if (swapped == 0) {
        for (pm = (char*)base + size; pm < (char*)base + n * size; pm += size) {
            for (pl = pm; pl > (char*)base && compare(pl - size, pl) > 0; pl -= size) {
                SWAP_1F5CD0(pl, pl - size);
            }
        }
        return;
    }
    pn = (char*)base + n * size;
    r = pa - (char*)base < pb - pa ? pa - (char*)base : pb - pa;
    BLOCKSWAP_1F5CD0((char*)base, pb - r, r);
    if (pd - pc < pn - pd - (s32)size) {
        r = pd - pc;
    } else {
        r = pn - pd - (s32)size;
    }
    BLOCKSWAP_1F5CD0(pb, pn - r, r);
    if ((u32)(r = pb - pa) > size) {
        func_001F5CD0(base, r / size, size, compare);
    }
    if ((u32)(r = pd - pc) > size) {
        base = pn - r;
        n = r / size;
        goto again;
    }
}
