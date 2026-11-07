// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 475/504 (94.2%), checked 2026-11-06
/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* NEAR (src/lib/cdvd.c's declarations; built as C by 2.9-ee-991111): 22 lines in its unit,
 * every one a register. The code is retail's instruction for instruction (the bind loop and its padded delay
 * loops, the shared failure path, the uncached read of the reply), but global allocation gives
 * the high halves other saved registers: retail has s1 for D_00279444, s2 mode, s3 D_0027942C,
 * s4 D_0062AA50, s5 D_0062AA10, s6 D_00279410, s7 D_0027A600; ours s7, s2, s3, s1, s4, s5, s6.
 * With `while (D_00279444 < 0)` instead of `if` (25 lines; the loop-depth weight of its references lifts
 * D_00279444 to s1, and D_0062AA50 and D_0027A600 follow) D_0062AA10's
 * references weigh too much and D_0027942C's too little (cc1 -dg: allocno priorities). The
 * failure's -1 or 6 comes out as `li v1,6; li v0,-1; movn` where retail has `li v1,-1;
 * li v0,6; movz`, with ?:, if/else or a local alike. */
#include "common.h"

typedef struct RpcClient {
    u8 pad00[0x24];
    void* server;
} RpcClient;

char D_00279400[16] __attribute__((aligned(64))) = "PsIIlibcdvd 2420";
s32 D_00279410 = 0;
s32 D_00279414 = 0;
u32 D_00279418 = 0;
u32 D_0027941C = 0;
s32 D_00279420 = -1;
s32 D_00279424 = 0;
s32 D_00279428 = -1;
s32 D_0027942C = -1;
volatile s32 D_00279430 = 0;
u32 D_00279434 = 0;
s32 D_00279438 = -1;
s32 D_0027943C = -1;
s32 D_00279440 = -1;
s32 D_00279444 = -1;
s32 D_00279448 = -1;
s32 D_0027944C = -1;
u32 D_00279450 = 0;
volatile s32 D_00279454 = 0;
volatile s32 D_00279458 = 0;
u8 D_00279480[128] __attribute__((aligned(64))) = { 0 };
u8 D_00279500[0x1000] __attribute__((aligned(64))) = { 0 };
u8 D_0027A500[192] __attribute__((aligned(64))) = { 0 };
u32 D_0027A5C0[4] __attribute__((aligned(64))) = { 0 };
RpcClient D_0027A5D0 = { { 0 } };
u8 D_0027A600[1088] __attribute__((aligned(64))) = { 0 };
u32 D_0027AA40[0x102] __attribute__((aligned(64))) = { 0 };
RpcClient D_0027AE48 = { { 0 } };

static s32 D_0062A7C0;
static void (*D_0062A7C4)(s32);
/* The callback's argument: 8 bytes in retail, of which only the first word is read. */
static s32 D_0062A7C8[2];
static s32 D_0062A7D0;
static u8 D_0062A7D8[0x210];
static RpcClient D_0062A9E8;
static RpcClient D_0062AA10;
static s32 D_0062AA40[4] __attribute__((aligned(64)));
/* What func_00203828 sends: its one word, in a buffer of 16 bytes as D_0062AA40. */
static s32 D_0062AA50[4];

s32 func_001F6A90(void);
s32 func_001F6B40(s32 sema);
s32 func_001F6B70(s32 sema);
s32 func_001F7B88(const char* format, ...);
void func_001F7BE8(s32 mode);
s32 func_001F80C0(RpcClient* client, u32 server, s32 mode);
s32 func_001F8290(RpcClient* client, s32 function, s32 mode, void* send, s32 send_size, void* receive,
                  s32 receive_size, void (*end)(void*), void* end_arg);
void func_001FA7D8(void* start, s32 size);
void func_00202EF0(void);
void func_00202F88(void);
s32 func_00203050(void);
s32 func_00203368(s32 mode);

s32 func_00203828(s32 mode)
{
    s32 i;
    s32 r;

    if (D_00279410 > 0) {
        func_001F7B88("DiskReady 0\n");
    }
    func_00202EF0();
    if (*(volatile s32*)&D_0027942C != func_001F6B70(*(volatile s32*)&D_0027942C)) {
        return 6;
    }
    if (func_00203368(1)) {
        func_001F6B40(*(volatile s32*)&D_0027942C);
        return mode == 8 ? -1 : 6;
    }
    func_001F7BE8(0);
    if (D_00279444 < 0) {
        while (1) {
            if (func_001F80C0(&D_0062AA10, 0x8000059A, 0) < 0) {
                if (D_00279410 > 0) {
                    func_001F7B88("Libcdvd bind err CdDiskReady\n");
                }
                for (i = 0x100000; i != -1; i--) {
                }
                continue;
            }
            if (D_0062AA10.server != 0)
                break;
            for (i = 0x100000; i != -1; i--) {
            }
        }
        D_00279444 = 0;
    }
    D_0062AA50[0] = mode;
    func_001FA7D8(D_0062AA50, 4);
    r = (s32)D_0027A600;
    if (func_001F8290(&D_0062AA10, 0, 0, D_0062AA50, 4, (void*)r, 4, 0, 0) < 0) {
        func_001F6B40(*(volatile s32*)&D_0027942C);
        return mode == 8 ? -1 : 6;
    }
    if (D_00279410 > 0) {
        func_001F7B88("DiskReady ended\n");
    }
    r = *(s32*)((u32)r | 0x20000000);
    func_001F6B40(D_0027942C);
    return r;
}
