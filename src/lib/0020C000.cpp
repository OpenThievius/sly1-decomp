// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

u32 func_0020DEE8(u32 value)
{
    u32* setting = (u32*)0x10002010;
    u32 result = (*setting & 0xFF7FFFFFu) | (value << 23);
    *setting = result;
    return result;
}

struct Obj_20F0C0 { u8 pad[0x818]; u32 value; };
extern u32 D_0027B040[];

void func_0020F0C0(Obj_20F0C0* obj, u32 value)
{
    u32 index = value >> 28;
    volatile u32* setting = (volatile u32*)0x10002000;
    *setting = value;
    obj->value = D_0027B040[index];
}

// NEAR: retail saves s0 and ra with 8-byte sd/ld, the default compiler with 16-byte sq/lq; and retail stores the result of the call to f148 before the next call, where ours moves the argument first. Otherwise identical

struct Node_20C0A8;

s32 func_0020F5B8(struct Node_20C0A8* a, s32 b);

struct Node_20C0A8 {
    u8 pad00[0x144];
    s32 f144;
    s32 f148;
    s32 f14C;
};

void func_0020C0A8(struct Node_20C0A8* self)
{
    func_0020F5B8(self, 3);
    if (func_0020F5B8(self, 1) != 0) {
        func_0020F5B8(self, 8);
        func_0020F5B8(self, 8);
        self->f144 = func_0020F5B8(self, 8);
    }
    self->f148 = func_0020F5B8(self, 0xE);
    func_0020F5B8(self, 1);
    self->f14C = func_0020F5B8(self, 0xE);
}

// NEAR: retail saves $ra with sd, the default compiler saves it with sq; code otherwise identical
struct Ctx_0020E100;
s32 func_0020F248(Ctx_0020E100* self, s32 kind);

s32 func_0020E100(Ctx_0020E100* self)
{
	return func_0020F248(self, 3);
}

// NEAR: only the s0 and ra saves differ: retail saves ra and s0 with sd (8 bytes), the SN builds with sq; the 8-byte save is the Sony 2.9-ee-991111 form (docs/TOOLCHAIN.md), not used here.

extern u8 D_002503E0[];

struct Node_20E7E0 {
    s32 field0;
};

void func_0020B978(struct Node_20E7E0 *self, void *a1);

s32 func_0020E7E0(struct Node_20E7E0 *self, s32 *a1, s32 *a2, s32 *a3, s32 *flags)
{
    s32 ret = 1;
    u32 t;

    *(s32 *)((u8 *)self + *(s32 *)((u8 *)self + 0x810) * 0x140 + 0x6CC) = 1;
    *(s32 *)((u8 *)self + 0x1B0) = 1;
    if (*(s32 *)((u8 *)self + 0x150) == 2) {
        a1[5] = 0;
        a1[4] = 0;
        a1[1] = 0;
        a1[0] = 0;
    }
    if (*(s32 *)((u8 *)self + 0x174) == 3) {
        *a2 = 2;
    } else {
        *a2 = 1;
        t = (u32)(*(s32 *)((u8 *)self + 0x174) ^ 2) < 1;
        a3[1] = t;
        a3[0] = t;
    }
    if (*(s32 *)((u8 *)self + 0x150) == 1) {
        func_0020B978(self, D_002503E0);
        ret = 0;
    }
    *flags &= -2;
    return ret;
}

// NEAR: every instruction of the body matches; retail saves and restores its callee-saved registers with sd/ld (64-bit), ours with sq/lq. A 64-bit local or parameter did not change the save form.

struct Self_20EF70 { s32 f00; };
struct Node_20EF70 { s32 f00; s32 f04; };

s32 func_0020F248(Self_20EF70* self, s32 mode);
s32 func_0020F5B8(Self_20EF70* self, s32 x);
s32 func_0020E100(Self_20EF70* self);
void func_0020ED48(Node_20EF70* n, s32 a, s32 b, s32 c, s32 d);

void func_0020EF70(Self_20EF70* self, Node_20EF70* n, s32* out, s32 p3, s32 p4, s32 want, s32 shift, s32 p7)
{
    s32 s0;
    s32 a3;

    s0 = func_0020F248(self, 2);
    if (p3 != 0 && s0 != 0) {
        a3 = func_0020F5B8(self, p3);
    } else {
        a3 = 0;
    }
    func_0020ED48(n, p3, s0, a3, p7);
    if (want != 0) {
        out[0] = func_0020E100(self);
    }
    s0 = func_0020F248(self, 2);
    if (p4 != 0 && s0 != 0) {
        a3 = func_0020F5B8(self, p4);
    } else {
        a3 = 0;
    }
    if (shift != 0) {
        n->f04 = n->f04 >> 1;
    }
    func_0020ED48((Node_20EF70*)&n->f04, p4, s0, a3, p7);
    if (shift != 0) {
        n->f04 = n->f04 << 1;
    }
    if (want != 0) {
        out[1] = func_0020E100(self);
    }
}

// NEAR: body matches; retail saves ra and s0 with sd (lib code), ours with sq

struct Obj_20F788 {
    u8 pad0[0x1B4];
    s32 f1B4;
};

s32 func_0020F5B8(Obj_20F788* self, s32 arg);
void func_0020F4C8(Obj_20F788* self, s32 arg);
void func_0020FCE0(Obj_20F788* self);

s32 func_0020F788(Obj_20F788* self)
{
    self->f1B4 = func_0020F5B8(self, 5);
    if (func_0020F5B8(self, 1) != 0) {
        func_0020F5B8(self, 1);
        func_0020F4C8(self, 7);
        func_0020FCE0(self);
    }
    return 0;
}

// NEAR: retail saves registers with sd (8 bytes; Sony 2.9-ee-991111 region, docs/TOOLCHAIN.md); the default SN build saves with sq, so the prologue and epilogue differ.

struct Self_0020F7F0 { u8 pad000[0x150]; s32 f150; u8 pad154[0x828 - 0x154]; s64 f828; s64 f830; u8 pad838[0x858 - 0x838]; s32 f858; };
struct Loc_0020F7F0 { s32 a; s64 b; s64 c; };

void func_0020F708(Self_0020F7F0* self);
s32 func_0020F5B8(Self_0020F7F0* self, s32 mask);
void func_0020B9F0(Self_0020F7F0* self);
void func_0020FDA0(Self_0020F7F0* self);
void func_0020F900(Self_0020F7F0* self);
void func_0020B190(s32 a0, Loc_0020F7F0* out);

s32 func_0020F7F0(Self_0020F7F0* self)
{
    u32 v;
    for (;;) {
        func_0020F708(self);
        v = func_0020F5B8(self, 0x20);
        if (v == 0x1B3) goto c1B3;
        if (v < 0x1B4) {
            if (v == 0x100) goto c100;
            continue;
        }
        if (v == 0x1B7) return 0;
        if (v == 0x1B8) goto c1B8;
        continue;
    c1B3:
        func_0020B9F0(self);
        continue;
    c1B8:
        func_0020FDA0(self);
        continue;
    c100:
        {
            Loc_0020F7F0 loc;
            func_0020F900(self);
            loc.a = 5;
            loc.b = -1;
            loc.c = -1;
            func_0020B190(self->f858, &loc);
            self->f830 = loc.c;
            self->f828 = loc.b;
            return self->f150;
        }
    }
}

// NEAR: retail saves s0/ra with sd/ld (8-byte, Sony 2.9-ee-991111 pattern); SN GCC emits sq/lq. Body matches.

struct Obj_0020FCE0;

s32 func_0020F5B8(Obj_0020FCE0* self, s32 a1);
void func_0020F4C8(Obj_0020FCE0* self, s32 a1);

void func_0020FCE0(Obj_0020FCE0* self)
{
    while (func_0020F5B8(self, 1))
        func_0020F4C8(self, 8);
}

// NEAR: retail saves $s0 and $ra with 8-byte sd (ld to restore); 2.95.3 saves
// them with 16-byte sq/lq, and no source form tried changed that.

extern u8 D_00250460[];
extern u8 D_00250488[];

struct Obj_20FE40 {
    u8 pad[0x840];
    void *field840;
    void *field844;
};

void* func_0020F5B8(struct Obj_20FE40 *self, s32 a1);
void func_0020F0F0(struct Obj_20FE40 *self);
void func_0020F0C0(struct Obj_20FE40 *self, u32 value);
void func_0020B978(struct Obj_20FE40 *self, void *a1);

void func_0020FE40(struct Obj_20FE40 *self)
{
    void *v;

    v = func_0020F5B8(self, 1);
    self->field840 = v;
    if (v != 0) {
        func_0020F0F0(self);
        func_0020F0C0(self, 0x50000000);
        func_0020F0F0(self);
    }
    v = func_0020F5B8(self, 1);
    self->field844 = v;
    if (v != 0) {
        func_0020F0F0(self);
        func_0020F0C0(self, 0x58000000);
        func_0020F0F0(self);
    }
    v = func_0020F5B8(self, 1);
    if (v != 0) {
        func_0020B978(self, D_00250460);
    }
    v = func_0020F5B8(self, 1);
    if (v == 0) {
        return;
    }
    return func_0020B978(self, D_00250488);
}
