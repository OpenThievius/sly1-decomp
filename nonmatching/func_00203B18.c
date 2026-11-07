// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 466/480 (97.1%), checked 2026-11-06
/* SPDX-License-Identifier: AGPL-3.0-or-later */
/* NEAR (whole file, src/lib/cdvd.c's declarations): 4 lines. The switch matches with case 0
 * written out, and D_00279434 (the read mode) is volatile. Left: the failure path, where retail
 * stores D_00279454 and D_00279430 (volatile, as the end callback func_00202DA0 shares them)
 * before loading D_00279428 into the call's delay slot; ours loads D_00279428 before the store
 * to D_00279430 and puts that store in the slot. A volatile read of D_00279428 keeps the order
 * but leaves the slot empty (nop); plain 0x279454 or 0x279430 break func_00202DA0 and
 * func_00202EF0. */
#include "common.h"

typedef struct RpcClient {
    u8 pad00[0x24];
    void* server;
} RpcClient;

extern s32 D_00279410;
extern s32 D_00279428;
extern volatile s32 D_00279430;
extern volatile u32 D_00279434;
extern volatile s32 D_00279454;
extern u8 D_00279500[0x1000];
extern u8 D_0027A500[192];
extern u32 D_0027A5C0[4];
extern RpcClient D_0027A5D0;

s32 func_001F6B40(s32 sema);
s32 func_001F7B88(const char* format, ...);
s32 func_001F8290(RpcClient* client, s32 function, s32 mode, void* send, s32 send_size, void* receive,
                  s32 receive_size, void (*end)(void*), void* end_arg);
void func_001FA7D8(void* start, s32 size);
void func_00202E50(void* tail);
s32 func_002030C0(s32 command);
s32 func_00203230(void);

typedef struct ReadRequest {
    s32 lsn;
    s32 sectors;
    void* buffer;
    u8 tries;
    u8 speed;
    u8 pattern;
    u8 pad0F;
    u8* tail;
    u32* result;
} ReadRequest;

typedef struct ReadMode {
    u8 tries;
    u8 speed;
    u8 pattern;
} ReadMode;

s32 func_00203B18(s32 lsn, s32 sectors, void* buffer, ReadMode* mode)
{
    ReadRequest* r = (ReadRequest*)D_00279500;
    s32 size;

    if (!(D_00279434 & 1)) {
        if (func_00203230() == 6)
            return 0;
    }
    if (func_002030C0(4) == 0)
        return 0;
    r->lsn = lsn;
    r->sectors = sectors;
    r->buffer = buffer;
    r->tries = mode->tries;
    r->speed = mode->speed;
    r->pattern = mode->pattern;
    r->tail = D_0027A500;
    r->result = D_0027A5C0;
    switch (mode->pattern) {
    case 1:
        size = sectors * 0x918;
        break;
    case 0:
        size = sectors << 11;
        break;
    case 2:
        size = sectors * 0x924;
        break;
    default:
        size = sectors << 11;
        break;
    }
    D_0027A5C0[0] = 0;
    if (!(D_00279434 & 2))
        func_001FA7D8(buffer, size);
    func_001FA7D8(D_0027A500, 0x90);
    func_001FA7D8(r, 0x18);
    func_001FA7D8(D_0027A5C0, 4);
    if (D_00279410 > 0)
        func_001F7B88("call cdread cmd\n");
    D_00279454 = 1;
    D_00279430 = 1;
    if (func_001F8290(&D_0027A5D0, 1, 1, r, 0x18, 0, 0, (void (*)(void*))func_00202E50, D_0027A500) < 0) {
        D_00279454 = 0;
        D_00279430 = 0;
        func_001F6B40(D_00279428);
        return 0;
    }
    if (D_00279410 > 0)
        func_001F7B88("cdread end\n");
    return 1;
}
