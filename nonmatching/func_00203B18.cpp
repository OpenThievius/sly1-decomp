// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 439/480 (91.5%), checked 2026-11-04
#include "common.h"
// NEAR (r60f): 12 lines differ (m59e's all-volatile version: 26 with the nop shift). Only
// D_00279434 is volatile here (not declared anywhere else in src/; it is the mode word the
// RPC end callback func_00202E40 updates, and retail rereads it after calls without CSE,
// and its join load is not stolen into the default arm's "b" slot, which is what volatile does).
// D_00279454/30/28 are plain. What still differs is only sched1 order of the two flag stores
// (call setup and failure path). Retail's order (sw 454, lui, sw 430, lw 428; and sw 454 first
// in the call setup) is exactly the order haifa gives when the three memory references form a
// dependence chain (sw454 -> sw430 -> lw428): v_all.cpp (all four volatile) reproduces it
// instruction for instruction, but reorg rejects a volatile load for the jal slot (nop).
// So retail's lw 428 is plain yet depends on the stores; with three distinct symbols
// base_alias_check always separates them, and a struct over 0x279410 (one base) is rejected
// by retail's separate %hi/%lo per word (sA-sD tried: base CSE'd into one register).
// TU facts measured: func_002032C8 stays EXACT with D_00279430 as `volatile s32`, but
// func_00203050/203230/203CF8/203A20 break if D_00279424/28/2C are volatile (they need the
// plain access in a delay slot), so D_00279428 must stay plain.
struct Req_203B18 {
    s32 a;
    s32 b;
    s32 c;
    u8 m0, m1, m2, pad;
    u8* p10;
    u8* p14;
};
struct Mode_203B18 { u8 b0, b1, b2; };

extern Req_203B18 D_00279500;
extern volatile s32 D_00279434;
extern u8 D_0027A500[];
extern u8 D_0027A5C0[];
extern u8 D_0027A5D0[];
extern s32 D_00279410;
extern s32 D_00279454;
extern s32 D_00279430;
extern s32 D_00279428;
extern u8 D_0024F710[];
extern u8 D_0024F728[];
extern u8 func_00202E40[];

s32 func_00203230(void);
s32 func_002030C0(s32 a);
void func_001FA7D8(void* a, s32 b);
void func_001F7B88(u8* a);
s32 func_001F8290(u8* a, s32 b, s32 c, Req_203B18* d, s32 e, s32 f, s32 g, u8* h, u8* i);
void func_001F6B40(s32 a);

s32 func_00203B18(s32 a, s32 b, s32 c, Mode_203B18* m)
{
    Req_203B18* r = &D_00279500;
    s32 size;
    if (D_00279434 & 1) goto L1;
    if (func_00203230() == 6) return 0;
L1:
    if (func_002030C0(4) == 0) return 0;
    r->a = a;
    r->b = b;
    r->c = c;
    r->m0 = m->b0;
    r->m1 = m->b1;
    r->m2 = m->b2;
    r->p10 = D_0027A500;
    r->p14 = D_0027A5C0;
    switch (m->b2) {
    case 1:
        size = b * 0x918;
        break;
    case 0:
        size = b << 11;
        break;
    case 2:
        size = b * 0x924;
        break;
    default:
        size = b << 11;
        break;
    }
    *(s32*)D_0027A5C0 = 0;
    if (!(D_00279434 & 2)) func_001FA7D8((void*)c, size);
    func_001FA7D8(D_0027A500, 0x90);
    func_001FA7D8(r, 0x18);
    func_001FA7D8(D_0027A5C0, 4);
    if (D_00279410 > 0) func_001F7B88(D_0024F710);
    D_00279454 = 1;
    D_00279430 = 1;
    if (func_001F8290(D_0027A5D0, 1, 1, r, 0x18, 0, 0, func_00202E40 + 0x10, D_0027A500) < 0) {
        D_00279454 = 0;
        D_00279430 = 0;
        func_001F6B40(D_00279428);
        return 0;
    }
    if (D_00279410 > 0) func_001F7B88(D_0024F728);
    return 1;
}
