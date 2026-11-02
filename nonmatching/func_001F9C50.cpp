// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 266/272 (97.8%), checked 2026-11-02
#include "common.h"
// NEAR: 6 lines (was 58). Matched by: s8 pointers, args (D_0024EBA0, s) / (buf, 0), base = s - 11 declared just before use, error arm as the fall-through, and the first copy loop as a pre-loaded `u8 ch` plus a separate `s8 sc` test. Still differs: the second copy loop; retail reuses the pre-loaded c (move a0,a1) for the first store and tests with lb, ours reloads lbu. Tried s8/u8 ch, ++s forms.

extern s8 D_0024EB90[];
extern s8 D_0024EBA0[];

struct Buf_1F9C50 {
    u8 c;
};

void func_001F7B88(s8 *msg, s8 *s);
void func_001F7BE8(struct Buf_1F9C50 *self);
void func_001F7D88(void);
s32 func_001F9AD8(u8 *buf, s32 z);

s32 func_001F9C50(s8 *s) {
    u8 buf[80];
    s8 *e = s;
    u8 *d;
    s8 *pre = D_0024EB90;
    u8 c;

    if (*s != 0) {
        do {
            e++;
        } while (*e != 0);
    }
    s8 *base = s - 11;
    if ((u32)(e - base) >= 81) {
        func_001F7B88(D_0024EBA0, s);
        return 0;
    }
    func_001F7BE8(0);
    func_001F7D88();
    d = buf;
    {
        s8 sc = *pre;
        u8 ch = *pre;
        while (sc != 0) {
            *d++ = ch;
            pre++;
            sc = *pre;
            ch = *pre;
        }
    }
    c = *s;
    if (c == 0) {
        *d = 0;
    } else {
        s8 sc;
        do {
            *d++ = c;
            s++;
            sc = *s;
            c = *s;
        } while (sc != 0);
        *d = 0;
    }
    return func_001F9AD8(buf, 0);
}
