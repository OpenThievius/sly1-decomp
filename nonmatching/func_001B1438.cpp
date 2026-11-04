// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 398/404 (98.5%), checked 2026-11-04
#include "common.h"
// NEAR: k (&D_00248D20) and the constant 2 swap $s7/$s8 (4 lines). Global-alloc priority is 5 refs each, live 122 (k) vs 120 (2): 2 wins. The 2 is hoisted by the second loop pass, after k's set; moving k into the loop makes D hoist in pass 1 (still before 2) and drops the 2 hoist.

struct __attribute__((aligned(16))) Quad_1B1438 { s32 w[4]; };

struct Self_1B1438;
struct Tgt_1B1438;
struct Req_1B1438;
void func_001F5C0C(Req_1B1438* p, s32 zero, s32 size);
struct Req_1B1438 {
    void Init(Self_1B1438* s, Tgt_1B1438* o, Quad_1B1438* k);
    void* self;
    void* tgt;
    s32 pad8[6];
    Quad_1B1438 q20;
    Quad_1B1438 q30;
};

struct Side_1B1438 {
    void* f0;
    void* f4;
    u8 pad[0x38];
};

struct Link_1B1438 {
    Side_1B1438 side[2];
    u8 pad80[0x50];
    Link_1B1438* fD0;
};

struct List_1B1438 {
    Link_1B1438* f0;
    List_1B1438* f4;
};

struct Owner_1B1438 {
    u8 pad[0x480];
    List_1B1438** f480;
};

typedef s32 (*VFn_1B1438)(void* self, void* arg);
struct Tgt_1B1438 {
    VFn_1B1438* vtbl;
    u8 pad[0x13C];
    Quad_1B1438 f140;
};

struct Self_1B1438 {
    u8 pad0[0x50];
    Owner_1B1438* f50;
    u8 pad54[0x500];
    s32 f554;
    u8 pad558[0xC0];
    s32 f618;
};

inline void Req_1B1438::Init(Self_1B1438* s, Tgt_1B1438* o, Quad_1B1438* k)
{
    func_001F5C0C(this, 0, 0x40);
    tgt = o;
    self = s;
    q20 = o->f140;
    q30 = *k;
}
extern Tgt_1B1438* D_00262E10;
extern Quad_1B1438 D_00248D20;

s32 func_001AED78(Self_1B1438* self, Tgt_1B1438* t);
struct Buf_1B1438 { s32 w[4]; };
void func_001D7098(Buf_1B1438* out, s32 a, Self_1B1438* self);
void func_001AEF68(Self_1B1438* self);
void func_00177838(Req_1B1438* p, s32 a, s32 b);

void func_001B1438(Self_1B1438* self, s32* out)
{
    Buf_1B1438 buf;
    Req_1B1438 req;
    Owner_1B1438* owner = self->f50;
    List_1B1438* l = *owner->f480;
    if (l != 0) {
        do {
            Link_1B1438* n = l->f0;
            if (n != 0) {
                Quad_1B1438* k = &D_00248D20;
                do {
                    s32 x = owner != n->side[0].f0;
                    Side_1B1438* b = &n->side[1 - x];
                    Side_1B1438* a = &n->side[x];
                    Tgt_1B1438* o = (Tgt_1B1438*)b->f0;
                    if (a->f4 == self && func_001AED78(self, o) != 0) {
                        if (self->f618 == 0) {
                            *out = self->f554 == 0 ? 2 : 6;
                        }
                        if ((u32)(*out - 5) < 2) {
                            if (o == D_00262E10) {
                                func_001D7098(&buf, 1, self);
                                if (D_00262E10->vtbl[0x140 / 4](D_00262E10, &buf) != 0) {
                                    func_001AEF68(self);
                                }
                            } else {
                                req.Init(self, o, k);
                                func_00177838(&req, 0, 0);
                            }
                        }
                    }
                    n = n->fD0;
                } while (n != 0);
            }
            l = l->f4;
        } while (l != 0);
    }
}
