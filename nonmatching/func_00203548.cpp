// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 690/736 (93.8%), checked 2026-11-02
#include "common.h"
// NEAR (r60f): 26 lines, same as m59e but with D_0062A7D0 stored from a local after
// D_00279424 = 1 (retail stores 424 before 62A7D0; the C++ front end otherwise computes
// %hi(D_0062A7D0) before the call, in $s0). Init block: sched2 issues li 1 / lui 424 (prio 6)
// before lw D_00279450 (prio 5) at the first cycle after the call; retail issues the lw first.
// BLOCKED regardless: this needs D_00279424/28/2C volatile, and measured in this TU
// func_00203050 (sw D_00279424 in a jal slot), func_00203230 (lw D_00279428 in a jal slot),
// func_00203CF8 and func_00203A20 (lw D_0027942C in a jal slot) all stop matching when those
// words are volatile, so retail's 203548 must use them plain. With every word plain (n548.cpp)
// 95 lines differ: %hi(D_00279424) is CSE'd/hoisted into $s8 and %hi(D_0027A600) is not.
// The source shape that keeps hi(424) unshared while plain was not found.
// (m59e) unchanged from p58f. Tried every combination of volatile on D_00279424, D_0062A7D0,
// D_00279450 and the case-5 words, with and without storing D_0062A7D0 after D_00279424
// through a local: best stays 26 lines (sched2 picks sw D_00279424 before lw D_00279450).

// NEAR (26 lines): the loop, the RPC, the status decode and the switch match; what still
// differs is the init block's scheduling: retail loads D_00279450 first and stores
// D_00279424 = 1 before D_0062A7D0, ours stores D_0062A7D0 first (registers follow), and two
// lui's at the end swap. This attempt needs D_00279420/24/28/2C and D_0062A7D0 volatile
// (not hardware registers): without volatile on D_00279424 the hi of D_00279424 is kept in
// $s8 across the loop (36+ lines differ), without it on D_00279420/28/2C the case-5 stores
// reorder.

struct Rpc_203548 { u8 pad[0x24]; s32 server; };

extern s32 D_00279410;
extern volatile s32 D_00279420;
extern volatile s32 D_00279424;
extern volatile s32 D_00279428;
extern volatile s32 D_0027942C;
extern s32 D_00279434;
extern s32 D_00279438;
extern s32 D_0027943C;
extern s32 D_00279440;
extern s32 D_00279444;
extern s32 D_00279448;
extern s32 D_0027944C;
extern s32 D_00279450;
extern volatile s32 D_0062A7D0;
extern Rpc_203548 D_0062A9E8;
extern s32 D_0062AA40;
extern s32 D_0027A600;

void func_00202EF0(void);
void func_00202F88(void);
void func_00203050(void);
extern "C" s32 func_001F6A90(void);
extern "C" int func_001F7B88(const char* fmt, ...);
s32 func_00203368(s32 a);
extern "C" void func_001F7BE8(s32 a);
extern "C" s32 func_001F80C0(Rpc_203548* r, u32 id, s32 mode);
extern "C" void func_001FA7D8(void* p, s32 size);
extern "C" s32 func_001F8290(Rpc_203548* r, s32 fno, s32 mode, void* send, s32 ssize,
                             void* recv, s32 rsize, void* end, void* arg);

s32 func_00203548(s32 mode)
{
    s32 r;
    s32 result;
    s32 status;
    s32 a;
    s32 b;
    u32 recv;

    if (func_00203368(1) != 0) {
        return 0;
    }
    func_001F7BE8(0);
    s32 id = func_001F6A90();
    D_00279424 = 1;
    D_0062A7D0 = id;
    D_0027943C = -1;
    D_00279440 = -1;
    D_00279438 = -1;
    D_00279448 = -1;
    D_00279444 = -1;
    D_00279434 = 0;
    D_00279450++;
    D_0027944C = -1;
    while (1) {
        r = func_001F80C0(&D_0062A9E8, 0x80000592, 0);
        if (r < 0) {
            if (D_00279410 > 0) {
                func_001F7B88("Libcdvd bind err %d CD_Init %d\n", r, D_00279450);
            }
            for (s32 i = 0x100000; i != -1; i--) {
            }
            continue;
        }
        if (D_0062A9E8.server != 0) {
            D_0062AA40 = mode;
            D_0027944C = 0;
            func_001FA7D8(&D_0062AA40, 4);
            recv = (u32)&D_0027A600;
            if (func_001F8290(&D_0062A9E8, 0, 0, &D_0062AA40, 4, (void*)recv, 0x10, 0, 0) < 0) {
                D_00279424 = 0;
                return 0;
            }
            break;
        }
        for (s32 i = 0x100000; i != -1; i--) {
        }
    }
    a = *(s32*)((recv + 4) | 0x20000000);
    b = *(s32*)((recv + 8) | 0x20000000);
    status = *(s32*)((recv + 12) | 0x20000000);
    result = 1;
    if (status != 0xFF) {
        if (status == 0xFE) {
            D_00279410 = 1;
        } else if (a / 256 < 2 || b / 256 < 2) {
            result = 2;
        }
    }
    D_00279424 = 0;
    switch (mode) {
    case 0:
    case 1:
        break;
    case 5:
        if (D_00279410 > 0) {
            func_001F7B88("Libcdvd Exit\n");
        }
        func_00202F88();
        D_00279428 = -1;
        D_0027942C = -1;
        D_00279420 = -1;
        return result;
    }
    func_00202EF0();
    func_00203050();
    return result;
}
