// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 460/492 (93.5%), checked 2026-11-06
#include "common.h"
// NEAR: store scheduling of the node/out init block and the flag-path exit (bnez to epilogue, v0=0 in delay slot) differ

struct Node_1F8290;
struct Out_1F8290 { Node_1F8290* f0; s32 f4; s32 f8; s32 pad_c; s32 f10; s32 f14; s32 f18; s32 f1C; s32 f20; s32 f24; };
struct Node_1F8290 { u8 pad0[0x14]; Node_1F8290* f14; s32 f18; Out_1F8290* f1C; s32 f20; s32 f24; s32 f28; s32 f2C; s32 f30; s32 f34; };
struct Ring_1F8290;
struct Args_1F8290 { s32 a; s32 b; s32 c; };

extern u8 D_00627800[];

Node_1F8290* func_001F7DB0(Ring_1F8290* r);
s32 func_001F6B20(Args_1F8290* a);
void func_001F7E58(Node_1F8290* n);
s32 func_001FA630(s32 k, Node_1F8290* n, s32 sz, s32 a3, s32 a4, s32 a5);
s32 func_001F6B60(s32 c);
void func_001F6B30(s32 c);
void func_001FA7D8(s32 p, s32 n);

s32 func_001F8290(Out_1F8290* out, s32 a1, s32 flags, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8)
{
    Args_1F8290 args;
    Node_1F8290* node;
    s32 t4;
    s32 ret;
    s32 scratch[4];
    (void)scratch;

    node = func_001F7DB0((Ring_1F8290*)D_00627800);
    if (node == 0) return -1;
    out->f20 = a8;
    out->f0 = node;
    out->f4 = node->f18;
    out->f1C = a7;
    node->f20 = a1;
    node->f24 = a4;
    node->f28 = a5;
    node->f2C = a6;
    node->f14 = node;
    {
        s32 t = out->f24;
        node->f1C = out;
        node->f34 = t;
    }
    if ((flags & 2) == 0) {
        if (a3 == a5) {
            func_001FA7D8(a3, a4 < a6 ? a6 : a4);
        } else {
            if (a4 > 0) func_001FA7D8(a3, a4);
            if (a6 > 0) func_001FA7D8(a5, a6);
        }
    }
    if (flags & 1) {
        if (a7 == 0) node->f30 = 0; else node->f30 = 1;
        out->f8 = -1;
        if (func_001FA630(0x8000000A, node, 0x40, a3, out->f14, a4) != 0) { ret = 0; goto out; }
        goto fail;
    }
    args.c = 0;
    args.b = 1;
    out->f8 = func_001F6B20(&args);
    if (out->f8 < 0) {
        func_001F7E58(node);
        return -3;
    }
    node->f30 = 1;
    if (func_001FA630(0x8000000A, node, 0x40, a3, out->f14, a4) != 0) goto ok;
    func_001F6B30(out->f8);
fail:
    func_001F7E58(node);
    ret = -2;
    goto out;
ok:
    func_001F6B60(out->f8);
    func_001F6B30(out->f8);
    ret = 0;
out:
    return ret;
}
