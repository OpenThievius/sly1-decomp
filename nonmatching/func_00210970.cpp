// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 268/272 (98.5%), checked 2026-11-08
// NEAR: registers only: four lines differ, all register numbers; the 24 orders of the four stores
//       were tried.
// Still differs (2026-11-08, night-close6): the index inline, signed, the entry in a local, the table through a pointer, p assigned apart, c->f858 read at each use: the same four registers.
#include "common.h"
struct Blk_210970 { u8 p0[0x10]; s32 f10; u8 p14[0xC]; u64 f20; };
struct Src_210970 { u8 p0[0x28]; s32 f28; u8 p2C[0x18]; s32 f44; s32 f48; s32 f4C; s32 f50; s32 f54; s32 f58; s32 f5C; s32 f60; };
struct Ctx_210970 {
    u8 p0[0x80]; s32 f80; u8 p84[4]; u64 f88; u8 p90[0x20]; s32 fB0; s32 fB4; s32 fB8; s32 fBC; s32 fC0; s32 fC4; s32 fC8; s32 fCC; s32 fD0;
    u8 pD4[0x858 - 0xD4]; Blk_210970* f858;
};
extern u32 D_0027B068[];
s32 func_002107E0(Ctx_210970* c, Src_210970* s, void* a, void* b, void* d);
s32 func_002104A8(Ctx_210970* c, Src_210970* s);
s32 ConvertPictureColours(Ctx_210970* c, Src_210970* s);
s32 func_00210548(Ctx_210970* c, Src_210970* s);
void func_002107B8(Ctx_210970* c);

void func_00210970(Ctx_210970* c, Src_210970* s)
{
    (void)func_002107E0(c, s, (u8*)c->f858 + 0x10, (u8*)c->f858 + 0x18, (u8*)c->f858 + 0x20);
    Blk_210970* p = c->f858;
    u32 idx = (s32)(((s64)p->f20 << 27) >> 32) & 0xF;
    c->f80 = p->f10;
    c->f88 = D_0027B068[idx];
    c->fCC = s->f5C;
    c->fD0 = s->f60;
    c->fB4 = s->f44;
    c->fB8 = s->f48;
    c->fBC = s->f4C;
    c->fC0 = s->f50;
    c->fC4 = s->f54;
    c->fC8 = s->f58;
    if (func_002104A8(c, s)) {
        if (s->f28 == 1) {
            if (c->fB0) {
                ConvertPictureColours(c, s);
            } else {
                func_00210548(c, s);
            }
            func_002107B8(c);
        }
    }
}
