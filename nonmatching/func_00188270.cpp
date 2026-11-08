// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 560/592 (94.6%), checked 2026-11-08
#include "common.h"
// NEAR: only the call to func_0013E430: retail stores fr.cur (sw s2) before the lwc1 of eps and has x in a1 (addiu a1,a1,992 last, in the jal slot); ours loads eps first and stores in the slot, or (store first) keeps x in v0. Fixed by reading both pair loads into f32 locals before fr.res = 0 (prologue now matches). Tried: eps local before/after the store, x local, pointer to fr.cur, p local.

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

void PushBackMemoryMark(void);
void* AllocateBackMemory(s32 size);
void PopBackMemoryMark(void);
s32 func_0013E430(Item_188270* node, void* p, f32 f, Item_188270** out);

s32 BuildObjectPairContacts(s32 unused, Pair_188270* pair, s32 arg)
{
    Frame_188270 fr;
    Obj_188270* pa = pair->a;
    Obj_188270* pb = pair->b;
    f32 da = pa->f3D0;
    f32 db = pb->f3D0;
    fr.res = 0;
    if (da > db) {
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
    PushBackMemoryMark();
    Item_188270* buf = (Item_188270*)AllocateBackMemory(most * 12);
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
            if (func_0013E430(h, fr.x->blob, fr.x->f3D4, &fr.cur) != 2) {
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
    PopBackMemoryMark();
    return fr.res;
}
