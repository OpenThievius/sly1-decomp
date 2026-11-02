// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 434/480 (90.4%), checked 2026-11-02
#include "common.h"
// NEAR: 14 lines differ: retail has "b; nop" for the default switch arm (ours fills the slot with the join's lw), 0x279454 store order in the call setup, and in the failure path the lw of the argument sits in the jal delay slot (ours the sw).
// NEAR: frame/prologue now match (size initialised from the p14 value, no longer live across calls); still differs: retail has p10 in a0, p14/size in a1, const 1 in a2; ours swaps a0/a1 and copies size to a3; arm layout of the t==1/2 chain differs (retail puts the 0x918 arm out of line).

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
extern s32 D_00279434;
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
