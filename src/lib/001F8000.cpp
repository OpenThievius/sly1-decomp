// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

extern s32 D_002779B0;

void func_001FA0A0(void)
{
    D_002779B0 = 0;
}

s32 func_001FA0D8(void)
{
    return 1;
}

s32 func_001FA1B0(s32* src, s32* dst)
{
    s32 value = src[4];
    dst[2] = value;
    return value;
}

extern s32 D_006294C0[];

s32 func_001FA1C0(s32 index)
{
    return D_006294C0[index];
}

extern s32 D_006293A4;
extern s32 D_006293AC;

void func_001FA4A0(s32 index, s32 first, s32 second)
{
    s32 scaled = index << 3;
    if (index < 0) {
        index = D_006293A4;
    } else {
        index = D_006293AC;
    }
    scaled += index;
    s32* p = (s32*)scaled;
    p[0] = first;
    p[1] = second;
}

// NEAR: EXACT only with SLY1_COMPILER=2.9-ee-991111 (Sony's release, saves in 8 bytes, as in the libraries); the default 2.9.3 build saves with sq/lq and differs (docs/TOOLCHAIN.md, lib compiler row not supported by tools/compile.py).

struct Buf_1F84D8 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
};

s32 func_001F6B20(Buf_1F84D8* self);

extern s32 D_002771C0;
extern s32 D_002771C4;

void func_001F84D8(void)
{
    if (D_002771C0 == -1) {
        Buf_1F84D8 b;
        b.f8 = 1;
        b.f14 = 0;
        b.f4 = 1;
        D_002771C0 = func_001F6B20(&b);
        D_002771C4 = func_001F6B20(&b);
    }
}

// NEAR: retail saves s0/ra with sd/ld (8-byte, Sony 2.9-ee-991111 pattern); SN GCC emits sq/lq. Body matches.

struct Desc_001F8968 { s32 f0; s32 f4; s32 f8; s32 fc; s32 f10; s32 f14; };
struct Handle_001F8968;

extern s32 D_002771BC;

s32 func_001F6B20(Desc_001F8968* self);

void func_001F8968(void)
{
    if (D_002771BC == -1) {
        Desc_001F8968 d;
        d.f8 = 1;
        d.f4 = 1;
        d.f14 = 0;
        D_002771BC = func_001F6B20(&d);
    }
}

extern s32 D_002771BC;
void func_001F8968(void);
void func_001F6B60(s32 a);

s32 func_001F89B8(void)
{
    func_001F8968();
    func_001F6B60(D_002771BC);
    return 0;
}

// NEAR: prologue and epilogue save $ra with sd/ld (8 bytes) where ours uses sq/lq (16 bytes); the rest of the body matches. Retail's 8-byte saves match the 2.9-ee-991111 library compiler, which tools/check.py cannot select per file.
struct Arg_1F8BF8;
void func_001F5C0C(Arg_1F8BF8* p, s32 a, s32 b);

extern s32 D_002771B8;
extern u8 D_00628B68[];

s32 func_001F8BF8(void)
{
    D_002771B8 = 0;
    func_001F5C0C((Arg_1F8BF8*)D_00628B68, 0, 4);
    return 0;
}

// NEAR: retail saves s0..s3 and ra with 8-byte sd/ld; the default compiler saves them with 16-byte sq/lq. Otherwise identical

struct Arg_1F9790;

extern u8 D_0027697C[];
extern u8 D_00628E28[];
extern void* D_002771D0;

s32 func_001F59C4(struct Arg_1F9790* a, void* b, s32 c);

s32 func_001F9790(void)
{
    s32 result = 0;
    void* second = D_0027697C;
    if (func_001F59C4((struct Arg_1F9790*)D_00628E28, second, 4) != 0) {
        if (func_001F59C4((struct Arg_1F9790*)D_00628E28, D_002771D0, 4) != 0) {
            result = func_001F59C4((struct Arg_1F9790*)second, D_002771D0, 4) != 0;
        }
    }
    return result;
}

// NEAR: only the ra save and restore differ (ours sq/lq, retail sd/ld; 0x1F lib region, see docs/TOOLCHAIN.md)

struct Clear_1F9820;
extern s32 D_002771CC;
extern u8 D_00628E28[];
void func_001F5C0C(Clear_1F9820* p, s32 value, s32 size);

s32 func_001F9820(void)
{
    D_002771CC = -1;
    func_001F5C0C((Clear_1F9820*)D_00628E28, 0, 4);
    return 0;
}

// NEAR: retail saves $ra with sd, default compiler with sq; call and frame identical
struct Ctx_001F9A90;
void func_001F9868(Ctx_001F9A90* a0, void* a1, void* a2, u32* a3, s32 a4);

void func_001F9A90(Ctx_001F9A90* a0, void* a1, void* a2)
{
	u32 out[4];
	func_001F9868(a0, a1, a2, out, 0);
}

// NEAR: default 2.95.3 saves $ra with sq/lq where retail has sd/ld; EXACT with SLY1_COMPILER=2.9-ee-991111 (docs/TOOLCHAIN.md item 3)

enum Arg_001F9C18 { ARG_001F9C18_NONE = 0 };

s32 func_001F6CF0(Arg_001F9C18 which);
void func_001FA0A0(void);

s32 func_001F9C18(void)
{
    if ((func_001F6CF0((Arg_001F9C18)4) & 0x40000) != 0) {
        func_001FA0A0();
        return 1;
    }
    return 0;
}

// NEAR: exact only with the Sony 2.9-ee-991111 compiler (retail saves ra with sd/ld); the default SN GCC 2.95.3 saves it with sq/lq and differs.

struct Ctx_1F9E50;

extern s32 D_002771D8[];

void func_001F9E90(Ctx_1F9E50* a, s32 b);
s32 func_001F9E40(s32 fn);
s32 func_001F9E08(Ctx_1F9E50* a);

s32 func_001F9E50(void)
{
    func_001F9E90((Ctx_1F9E50*)D_002771D8[0], D_002771D8[1]);
    s32 r = func_001F9E40((s32)func_001F9E08);
    return r - 0x20C;
}

// NEAR: default 2.95.3 leaves the loop one nop short (beqz target off by 4); EXACT with SLY1_COMPILER=2.9-ee-991111

struct Words_001F9F08 { s32 w[1]; };

s32 func_001F9F08(Words_001F9F08* dst, Words_001F9F08* src, u32 bytes)
{
    s32* d = (s32*)dst;
    s32* s = (s32*)src;
    u32 n = bytes >> 2;
    u32 i;
    for (i = 0; i < n; i++) {
        s32 v = *s++;
        *d++ = v;
    }
    return 0;
}

// NEAR: body close; retail saves ra and s0 with sd (lib code), ours with sq

struct Word_1F9F50 { u32 value; };

void func_001F6BA0(Word_1F9F50* w);
void func_001F6B90(Word_1F9F50* w);

s32 func_001F9F50(void)
{
    Word_1F9F50 a;
    Word_1F9F50 b;
    func_001F6BA0(&a);
    b.value = (a.value & 0xFFFF1FFF) | 0x2000;
    func_001F6B90(&b);
    func_001F6BA0(&b);
    func_001F6B90(&a);
    return ((b.value >> 13) & 7) == 0;
}

// NEAR: retail is a bare tail jump `j` with a nop delay slot; SN 2.95.3 keeps a frame (sq ra) and uses jal. Only Sony 2.9-ee-991111 tail-calls (docs/TOOLCHAIN.md).

struct Node_001FA068 { s32 a; };

void func_001FA9C0(Node_001FA068* p);

void func_001FA068(Node_001FA068* p)
{
    func_001FA9C0(p);
}

// NEAR: ra is saved with sq/lq, retail sd/ld (Sony 2.9-ee-991111 lib build, docs/TOOLCHAIN.md); body otherwise EXACT

void func_001FA078(void* arg);

s32 func_001FA0E0(s32 mode, void* arg)
{
    if (mode == 1) {
        func_001FA078(arg);
    }
    return 0;
}

// NEAR: retail saves $ra with sd (Sony 2.9-ee-991111 library code, 0x1F59C4 on); the default compiler saves it with sq. Nothing else differs.

enum Req_1FA140 { REQ_1FA140_CLOCK = 0x10 };
void func_001F6D10(Req_1FA140 req, void* arg);

void func_001FA140(s32 value) { s32 local = value; func_001F6D10(REQ_1FA140_CLOCK, &local); }

// NEAR: exact only with the Sony 2.9-ee-991111 compiler (retail saves ra with sd/ld); the default SN GCC 2.95.3 saves it with sq/lq and differs.

struct Ctx_1FA630;

s32 func_001FA4F8(Ctx_1FA630* a, s32 mode, s32 b, s32 c, s32 d, s32 e, s32 f);

s32 func_001FA630(Ctx_1FA630* a, s32 b, s32 c, s32 d, s32 e, s32 f)
{
    return func_001FA4F8(a, 0, b, c, d, e, f);
}

// NEAR: exact only with the Sony 2.9-ee-991111 compiler (retail saves ra with sd/ld); the default SN GCC 2.95.3 saves it with sq/lq and differs.

struct Ctx_1FA670;

s32 func_001FA4F8(Ctx_1FA670* a, s32 mode, s32 b, s32 c, s32 d, s32 e, s32 f);

s32 func_001FA670(Ctx_1FA670* a, s32 b, s32 c, s32 d, s32 e, s32 f)
{
    return func_001FA4F8(a, 1, b, c, d, e, f);
}

// NEAR: default 2.95.3 leaves the loop one nop short; EXACT with SLY1_COMPILER=2.9-ee-991111

struct Words_001FA8A0 { s32 w[1]; };

s32 func_001FA8A0(Words_001FA8A0* dst, Words_001FA8A0* src, u32 bytes)
{
    s32* d = (s32*)dst;
    s32* s = (s32*)src;
    u32 n = bytes >> 2;
    u32 i;
    for (i = 0; i < n; i++) {
        s32 v = *s++;
        *d++ = v;
    }
    return 0;
}

// NEAR: body EXACT; only the save/restore ops differ: retail sd/ld, default flags give sq/lq

struct Blk_1FA8F8;
extern u32 D_00277D30[];
extern u8 D_002779C0[];
u32 func_001FA8D8(Blk_1FA8F8* a);
void func_001FA8E8(Blk_1FA8F8* a, u32 b);
void func_001FA890(Blk_1FA8F8* a, void* b, s32 c);
void func_001F6C20(s32 a);

void func_001FA8F8() {
    u32* s0 = D_00277D30;
    u32* s1;
    u32 k = 3;
    func_001FA8E8((Blk_1FA8F8*)s0[0], s0[1]);
    func_001FA890((Blk_1FA8F8*)0x80075000, D_002779C0, 0x328);
    func_001F6C20(0);
    func_001F6C20(2);
    func_001FA8E8((Blk_1FA8F8*)s0[2], s0[3]);
    func_001FA8E8((Blk_1FA8F8*)s0[4], s0[5]);
    s1 = s0 + 6;
    do {
        k++;
        u32 v = func_001FA8D8((Blk_1FA8F8*)s1[0]);
        func_001FA8E8((Blk_1FA8F8*)s1[0], v);
        s1 += 2;
    } while (k < 8);
}

// NEAR: retail tail-calls with j and fills its delay slot with the store; default compiler emits jal with a frame
extern s32 D_0062A76C;
void func_001FAD68(void);

void func_001FAE18(void)
{
	if (D_0062A76C == 0) {
		D_0062A76C = 1;
		func_001FAD68();
	}
}
