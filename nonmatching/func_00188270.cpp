// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 560/592 (94.6%), checked 2026-11-05
#include "common.h"
// NEAR: 2-3 instruction scheduling diffs: retail moves a2 to s5 right after sq ra, and loads fr.x into a1 (not v0) for the func_0013E430 call

struct Item_188270 {
    s32 a, b, c;
};

struct Obj_188270;

struct Node_188270 {
    u8 pad0[0x3F0];
    s32 f3F0;
    s32 f3F4;
    Item_188270* f3F8;
    u8 pad3FC[0x13C];
    u64 flags;
};

struct Vt_188270 {
    u8 pad[0xF4];
    s32 (*f0)(Obj_188270*, Node_188270*, s32, s32, Item_188270*, Item_188270*, s32*);
    s32 (*f1)(Obj_188270*, Node_188270*, s32, Item_188270*, Item_188270*, s32*);
};

struct Obj_188270 {
    Vt_188270* vt;
    u8 pad4[0x3D0 - 4];
    f32 f3D0;
    f32 f3D4;
    u8 pad3D8[8];
    u8 blob[1];
};

struct Pair_188270 {
    Obj_188270* a;
    Obj_188270* b;
};

struct Frame_188270 {
    Obj_188270* x;
    Obj_188270* y;
    s32 pad[3];
    Item_188270* cur;
    s32 res;
};

void func_0018D608(void);
void* func_0018D658(s32 size);
void func_0018D6F0(void);
s32 func_0013E430(Item_188270* node, f32 f, void* p, Item_188270** out);

s32 func_00188270(s32 unused, Pair_188270* pair, s32 arg)
{
    Frame_188270 fr;
    fr.res = 0;
    Obj_188270* pa = pair->a;
    Obj_188270* pb = pair->b;
    if (pa->f3D0 > pb->f3D0) {
        fr.x = pb;
        fr.y = pa;
    } else {
        fr.x = pa;
        fr.y = pb;
    }
    s32 most = 0;
    Node_188270* n;
    for (n = *(Node_188270**)((u8*)fr.y + 0x2D8); n; n = *(Node_188270**)((u8*)n + 0x2E4)) {
        if (n->f3F4 > most) {
            most = n->f3F4;
        }
    }
    func_0018D608();
    Item_188270* buf = (Item_188270*)func_0018D658(most * 12);
    s32 idx;
    for (n = *(Node_188270**)((u8*)fr.y + 0x2D8); n; n = *(Node_188270**)((u8*)n + 0x2E4)) {
        if (n->flags & 0x80000000000ULL) {
            continue;
        }
        if (n->flags & 0x10000000000ULL) {
            fr.cur = 0;
        } else {
            Item_188270* h = n->f3F8;
            if (h == 0) {
                continue;
            }
            fr.cur = buf;
            if (func_0013E430(h, fr.x->f3D4, fr.x->blob, &fr.cur) != 2) {
                continue;
            }
            idx = fr.cur - buf;
            fr.cur = fr.cur - 1;
        }
        fr.x->vt->f0(fr.x, n, arg, idx, buf, fr.cur, &fr.res);
        if (fr.x->vt->f1) {
            fr.x->vt->f1(fr.x, n, idx, buf, fr.cur, &fr.res);
        }
    }
    for (n = *(Node_188270**)((u8*)fr.x + 0x2D8); n; n = *(Node_188270**)((u8*)n + 0x2E4)) {
        if (n->flags & 0x80000000000ULL) {
            continue;
        }
        if (!(n->flags & 0x10000000000ULL) && n->f3F8 == 0) {
            continue;
        }
        if (fr.y->vt->f1) {
            fr.y->vt->f1(fr.y, n, n->f3F0, n->f3F8, n->f3F8, &fr.res);
        }
    }
    func_0018D6F0();
    return fr.res;
}
