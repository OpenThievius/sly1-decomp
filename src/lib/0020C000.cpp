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
u32 D_0027B040[10] = { 0x1, 0x1, 0x0, 0x0, 0x0, 0x1, 0x1, 0x1, 0x1, 0x1 };

void func_0020F0C0(Obj_20F0C0* obj, u32 value)
{
    u32 index = value >> 28;
    volatile u32* setting = (volatile u32*)0x10002000;
    *setting = value;
    obj->value = D_0027B040[index];
}

// NEAR: retail saves $ra with sd, the default compiler saves it with sq; code otherwise identical
struct Ctx_0020E100;
s32 func_0020F248(Ctx_0020E100* self, s32 kind);

s32 func_0020E100(Ctx_0020E100* self)
{
	return func_0020F248(self, 3);
}

// NEAR: only the s0 and ra saves differ: retail saves ra and s0 with sd (8 bytes), the SN builds with sq; the 8-byte save is the Sony 2.9-ee-991111 form (docs/TOOLCHAIN.md), not used here.

extern const char D_002503E0[];

struct Node_20E7E0 {
    s32 field0;
};

void func_0020B978(struct Node_20E7E0 *self, const char *a1);

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

extern const char D_00250460[];
extern const char D_00250488[];

struct Obj_20FE40 {
    u8 pad[0x840];
    void *field840;
    void *field844;
};

void* func_0020F5B8(struct Obj_20FE40 *self, s32 a1);
void func_0020F0F0(struct Obj_20FE40 *self);
void func_0020F0C0(struct Obj_20FE40 *self, u32 value);
void func_0020B978(struct Obj_20FE40 *self, const char *a1);

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

struct Ctx_20E5F0 {
    u8 pad0[0x11C];
    s32 f11c;
    u8 pad1[0x6CC - 0x120];
    u8 slots[0x144];
    u8 pad2[0x810 - 0x810];
    s32 f810;
};
struct Buf_20E5F0 { s32 w[8]; };
struct Half_20E5F0 { s32 w[4]; };

extern const char D_002503C0[];

s32 func_0020E4C0(Ctx_20E5F0* c, s32 n, s32* i, s32* j, Buf_20E5F0* b);
s32 func_0020DF10(Ctx_20E5F0* c);
s32 func_0020F3C0(Ctx_20E5F0* c, s32 k);
s32 func_0020E2A8(Ctx_20E5F0* c);
void func_0020B978(Ctx_20E5F0* c, const char* s);
s32 func_0020E8A0(Ctx_20E5F0* c, s32* a, s32* b, s32* d, Buf_20E5F0* e, Half_20E5F0* f, Half_20E5F0* g);
s32 func_0020E7E0(Ctx_20E5F0* c, Buf_20E5F0* e, s32* b, Half_20E5F0* f, s32* a);
s32 func_0020C1A0(Ctx_20E5F0* c, s32 i, s32 j, s32 a, s32 b, Buf_20E5F0* e, Half_20E5F0* f, Half_20E5F0* g);
void func_0020CF18(Ctx_20E5F0* c, s32 v);

s32 func_0020E5F0(Ctx_20E5F0* c, s32 n)
{
    Buf_20E5F0 e;
    Half_20E5F0 f;
    Half_20E5F0 g;
    s32 i, j, a, b, d;
    i = 0;
    j = 0;
    s32 r = func_0020E4C0(c, n, &i, &j, &e);
    if (r != 0) return r;
    c->f11c = 0;
    for (;;) {
        if (!(i < n)) return 0;
        *(s32*)((u8*)c + c->f810 * 0x140 + 0x6CC) = 0;
        if (func_0020DF10(c) == 0) return 2;
        if (j == 0) {
            if (func_0020F3C0(c, 0x17) == 0) {
                c->f11c = 0;
                return 3;
            }
            if (c->f11c != 0) {
                c->f11c = 0;
                return 3;
            }
            j = func_0020E2A8(c);
            if (c->f11c != 0) {
                c->f11c = 0;
                return 1;
            }
        }
        if (!(i < n)) {
            func_0020B978(c, D_002503C0);
            return 2;
        }
        if (j == 1) {
            if (func_0020E8A0(c, &a, &b, &d, &e, &f, &g) == 0) {
                c->f11c = 0;
                return 1;
            }
        } else {
            if (func_0020E7E0(c, &e, &b, &f, &a) == 0) {
                c->f11c = 0;
                return 2;
            }
        }
        if (func_0020C1A0(c, i, j, a, b, &e, &f, &g) == 0) {
            c->f11c = 0;
            return 2;
        }
        if (i != 0) func_0020CF18(c, c->f810 ^ 1);
        i = i + 1;
        c->f810 = c->f810 ^ 1;
        j = j - 1;
    }
}

struct Ctx_20E3B8 { u8 pad0[0x12C]; s32 f12C; s32 f130; u8 pad134[0x40]; s32 f174; u8 pad178[0x698]; s32 f810; s32 f814; };

extern const char D_00250358[];
s32 func_0020E5F0(Ctx_20E3B8* c, s32 n);
void func_0020F0F0(Ctx_20E3B8* c);
s32 func_0020DF10(Ctx_20E3B8* c);
void func_0020CF18(Ctx_20E3B8* c, s32 a);
void func_0020B978(Ctx_20E3B8* c, const char* s);

s32 func_0020E3B8(Ctx_20E3B8* c)
{
    s32 r;
    s32 n;
    s32 res;
    c->f810 = 0;
    c->f814 = 0;
    n = c->f12C * c->f130;
    if (c->f174 != 3) n = n >> 1;
    do {
        r = func_0020E5F0(c, n);
    } while (r == 1 || r == 3);
    func_0020F0F0(c);
    if (func_0020DF10(c) == 0) r = 2;
    while ((*(volatile u32*)0x1000D400 >> 8) & 1) {}
    if (r == 0) func_0020CF18(c, c->f810 == 0);
    if ((u32)(r - 1) < 2) func_0020B978(c, D_00250358);
    res = (r == 0);
    return res;
}

extern const char D_00250378[];
extern const char D_002503A0[];

struct Ctx_20E4C0 {
    u8 pad0[0x11C];
    s32 f11C;
    u8 pad1[0x0C];
    s32 f12C;
    u8 pad2[0x80];
    s32 f1B0;
};

struct Out_20E4C0 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
};

void func_0020F708(struct Ctx_20E4C0 *self);
s32 func_0020F3C0(struct Ctx_20E4C0 *self, s32 a1);
void func_0020B940(struct Ctx_20E4C0 *self, const char *a1, u32 a2);
void func_0020F4C8(struct Ctx_20E4C0 *self, s32 a1);
s32 func_0020F788(struct Ctx_20E4C0 *self);
s32 func_0020E2A8(struct Ctx_20E4C0 *self);
void func_0020B978(struct Ctx_20E4C0 *self, const char *a1);

s32 func_0020E4C0(struct Ctx_20E4C0 *self, s32 a1, s32 *outA, s32 *outB, struct Out_20E4C0 *outC) {
    u32 s2;
    s32 s3;
    s32 e;

    self->f11C = 0;
    func_0020F708(self);
    s2 = (u32)func_0020F3C0(self, 0x20);
    if (s2 - 0x101 >= 0xAF) {
        func_0020B940(self, D_00250378, s2);
        return 2;
    }
    func_0020F4C8(self, 0x20);
    s3 = func_0020F788(self);
    e = func_0020E2A8(self);
    *outB = e;
    if (self->f11C != 0) {
        func_0020B978(self, D_002503A0);
        return 1;
    }
    *outA = ((s3 << 7) + (s2 & 0xFF) - 1) * self->f12C + e - 1;
    *outB = 1;
    self->f1B0 = 1;
    outC->f14 = 0;
    outC->f10 = 0;
    outC->f4 = 0;
    outC->f0 = 0;
    outC->f1C = 0;
    outC->f18 = 0;
    outC->fC = 0;
    outC->f8 = 0;
    return 0;
}

struct Obj_0020F708 { u8 pad[4]; };
void func_0020F0F0(Obj_0020F708* self);
void func_0020F4C8(Obj_0020F708* self, s32 mode);
s32 func_0020F3C0(Obj_0020F708* self, s32 mode);
void func_0020F708(Obj_0020F708* self)
{
    func_0020F0F0(self);
    volatile u32* reg = (volatile u32*)0x10002020;
    s32 mask = -(*reg & 7) & 7;
    if (mask != 0) {
        func_0020F4C8(self, mask);
    }
    while (func_0020F3C0(self, 0x18) != 1) {
        func_0020F4C8(self, 8);
    }
}

extern const char D_00250320[];

struct Node_20E2A8 {
    u8 pad0[0x11C];
    s32 field11C;
    u8 pad1[0x848 - 0x120];
    s32 field848;
};

s32 func_0020F248(struct Node_20E2A8 *self, s32 a1);
s32 func_0020F3C0(struct Node_20E2A8 *self, s32 a1);
void func_0020F4C8(struct Node_20E2A8 *self, s32 a1);
void func_0020B940(struct Node_20E2A8 *self, const char *a1, s32 a2);

s32 func_0020E2A8(struct Node_20E2A8 *self) {
    s32 total = 0;
    s32 again;
    do {
        s32 tok = func_0020F248(self, 0);
        switch ((u32)tok) {
        case 0x22:
            again = 1;
            break;
        case 0x23:
            again = 1;
            total += 0x21;
            break;
        case 0: {
            s32 v3 = func_0020F3C0(self, 0xB);
            if (self->field848 != 0 && v3 == 0xF) {
                func_0020F4C8(self, 0xB);
                again = 1;
            } else {
                func_0020B940(self, D_00250320, tok);
                self->field11C = 1;
                return 1;
            }
            break;
        }
        default:
            total += tok;
            again = 0;
            break;
        }
    } while (again);
    return total;
}

// EXACT: the first compare cast to s32 on both sides so the return constant shares the compare's register

struct Dev_0020F0F0;

struct Obj_0020F0F0 {
    u8 pad_000[0x858];     // 0x000
    s32 dev;               // 0x858
};

s32 func_0020B1E0(Dev_0020F0F0* d);

s32 func_0020F0F0(Obj_0020F0F0* self)
{
    s32 n = 0;
    if ((s32)(*(volatile u32*)0x10002010 & 0x80004000) == (s32)0x80000000) {
        do {
            s32 c = n;
            n = c + 1;
            if (c >= 0x1389) {
                func_0020B1E0((Dev_0020F0F0*)self->dev);
                n = 0;
            }
        } while ((*(volatile u32*)0x10002010 & 0x80004000) == 0x80000000);
        return n;
    }
    return 0x80000000;
}

// EXACT: do-while behind a duplicated first test, i = 0 before the first read

struct Dev_0020F198;
struct Ctx_0020F198 { u8 pad[0x858]; Dev_0020F198* dev; };
s32 func_0020B1E0(Dev_0020F198* a);

s64 func_0020F198(Ctx_0020F198* p) {
    s32 i = 0;
    s64 v = *(volatile s64*)0x10002000;
    if (v < 0 && (*(volatile u32*)0x10002010 & 0x4000) == 0) {
        do {
            s32 old = i;
            i++;
            if (old >= 5001) {
                func_0020B1E0(p->dev);
                i = 0;
            }
            v = *(volatile s64*)0x10002000;
        } while (v < 0 && (*(volatile u32*)0x10002010 & 0x4000) == 0);
    }
    return v;
}

struct Ctx_20F4C8 {
    u8 pad0[0x818];
    s32 f818;
    u8 pad1[0x838 - 0x81C];
    s32 f838;
    s32 f83C;
    u8 pad2[0x858 - 0x840];
    s32 f858;
};
struct Arg_20F4C8 { u32 v; };

extern u32 D_0027B040[];
extern s32 func_0020B1E0(Arg_20F4C8* a);
extern s64 func_0020F198(Ctx_20F4C8* c, u32* v);

void func_0020F4C8(Ctx_20F4C8* s0, u32 s1)
{
    s32 cnt = 0;
    u32 v;
    u32* p;

    while ((*(volatile u32*)0x10002010 & 0x80004000u) == 0x80000000u) {
        if (cnt++ > 0x1388) {
            func_0020B1E0((Arg_20F4C8*)s0->f858);
            cnt = 0;
        }
    }
    v = s1 | 0x40000000u;
    *(volatile u32*)0x10002000 = v;
    p = &D_0027B040[v >> 28];
    s0->f818 = *p;
    s0->f838 = func_0020F198(s0, p);
    s0->f83C = 0x20;
}

// EXACT: while ((r = f()) == kB || r == kA) loop, limit declared before the loop, table as a union with Fn fn[11] indexed t.fn[idx].

struct Self_0020F9C8;

typedef void (*Fn_0020F9C8)(struct Self_0020F9C8* self);

struct __attribute__((packed)) Pack_0020F9C8 {
    u64 a[5];
};

struct Tbl_0020F9C8 {
    struct Pack_0020F9C8 p;
    Fn_0020F9C8 last;
};

union TblU_0020F9C8 {
    struct Tbl_0020F9C8 t;
    Fn_0020F9C8 fn[11];
};

void func_0020F708(struct Self_0020F9C8* self);
void func_0020F4C8(struct Self_0020F9C8* self, s32 a1);
s32 func_0020F5B8(struct Self_0020F9C8* self, s32 a1);
s32 func_0020F3C0(struct Self_0020F9C8* self, s32 a1);

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_00250430[];

void func_0020F9C8(struct Self_0020F9C8* self)
{
    s32 kA = 0x1B2;
    union TblU_0020F9C8 t;
    t.t = *(struct Tbl_0020F9C8*)((u8*)D_00250430);
    s32 kB = 0x1B5;
    s32 r;

    func_0020F708(self);
    u32 limit = 10;
    while ((r = func_0020F3C0(self, 0x20)) == kB || r == kA) {
        if (r == kB) {
            func_0020F4C8(self, 0x20);
            u32 idx = (u32)func_0020F5B8(self, 4);
            if (limit < idx) {
                idx = 0;
            }
            t.fn[idx](self);
            func_0020F708(self);
        } else {
            func_0020F4C8(self, 0x20);
            func_0020F708(self);
        }
    }
}

// EXACT: lim/neg locals, one if with f150 != 3 && a1 != 0, neg = (u32)f854 < 1 (not goto form).
struct Obj_20FD28 {
    u8 pad0[0x150];
    s32 f150;
    u8 pad1[0x1AC - 0x154];
    s32 f1AC;
    u8 pad2[0x84C - 0x1B0];
    s32 f84C;
    s32 f850;
    s32 f854;
};

s32 func_0020FD28(Obj_20FD28* self, s32 a1)
{
    s32 lim = 0;
    s32 neg = 0;
    if (self->f150 != 3 && a1 != 0) {
        if (a1 < 0) {
            neg = (u32)self->f854 < 1;
        }
        self->f854 = 0;
        lim = a1;
    }
    s32 v1 = self->f84C + a1;
    self->f1AC = v1;
    if (neg && lim >= a1) {
        self->f1AC = v1 + 0x400;
    }
    s32 v0 = self->f850;
    if (v0 < self->f1AC) {
        v0 = self->f1AC;
    }
    self->f850 = v0;
    return v0;
}

struct Mode_E120 { u8 pad[0x174]; s32 mode; s32 flag; };

void func_0020E120(Mode_E120* self, s32* out, s32* in, s32 x, s32 y)
{
    if (self->mode == 3) {
        if (self->flag != 0) {
            out[0] = ((x > 0 ? x + 1 : x) >> 1) + in[0];
            out[1] = ((y > 0 ? y + 1 : y) >> 1) + in[1] - 1;
            { s32 gx = x * 3;
            out[2] = ((x > 0 ? gx + 1 : gx) >> 1) + in[0]; }
            { s32 gy = y * 3;
            out[3] = ((y > 0 ? gy + 1 : gy) >> 1) + in[1] + 1; }
        } else {
            { s32 gx = x * 3;
            out[0] = ((x > 0 ? gx + 1 : gx) >> 1) + in[0]; }
            { s32 gy = y * 3;
            out[1] = ((y > 0 ? gy + 1 : gy) >> 1) + in[1] - 1; }
            out[2] = ((x > 0 ? x + 1 : x) >> 1) + in[0];
            out[3] = ((y > 0 ? y + 1 : y) >> 1) + in[1] + 1;
        }
        return;
    }
    out[0] = ((x > 0 ? x + 1 : x) >> 1) + in[0];
    s32 r = ((y > 0 ? y + 1 : y) >> 1) + in[1];
    out[1] = r;
    if (self->mode == 1) {
        out[1] = r - 1;
    } else {
        out[1] = r + 1;
    }
}

struct Self_20E8A0 {
    u8 pad0[0x11C];
    s32 f11C;
    u8 pad1[0x150 - 0x120];
    s32 f150;
    s32 f154;
    s32 f158;
    s32 f15C;
    s32 f160;
    s32 f164;
    s32 f168;
    s32 f16C;
    s32 f170;
    s32 f174;
    u8 pad2[4];
    s32 f17C;
    s32 f180;
    u8 pad3[0x1B0 - 0x184];
    s32 f1B0;
    s32 f1B4;
    u8 pad4[0x810 - 0x1B8];
    s32 f810;
    u8 pad5[0x848 - 0x814];
    s32 f848;
};

extern const char D_00250410[];

s16 func_0020F248(Self_20E8A0* self, s32 mode);
void func_0020B978(Self_20E8A0* self, const char* msg);
s32 func_0020F5B8(Self_20E8A0* self, s32 n);
void func_0020F4C8(Self_20E8A0* self, s32 n);
void func_0020F0F0(Self_20E8A0* self);
void func_0020F0C0(Self_20E8A0* self, s32 v);
void func_00210D90(s32 a, s32 b);
void func_0020EDD0(Self_20E8A0* self, s32* b1, s32* b2, s32* o5, s32 a4, s32 a5, s32 a6, s32 a7, s32 s0, s32 s8, s32 s10);
void func_0020EF70(Self_20E8A0* self, s32* b1, s32* b2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7);

s32 func_0020E8A0(Self_20E8A0* self, s32* st, s32* mode, s32* o3, s32* b1, s32* o5, s32* b2)
{
    s32 m3, m4, m7, mfp;
    s32 v;

    *(volatile u32*)0x10002010 = (*(volatile u32*)0x10002010 & 0xF8FFFFFF) | (self->f150 << 24);
    v = func_0020F248(self, 1);
    *st = v;
    if (v == 0) {
        func_0020B978(self, D_00250410);
        self->f11C = 1;
        return 0;
    }
    if (v & 0xC) {
        if (self->f174 == 3 && self->f17C != 0) {
            *mode = 2;
        } else {
            *mode = func_0020F5B8(self, 2);
        }
    } else if (v & 1) {
        if (self->f180 != 0) {
            *mode = (self->f174 == 3) ? 2 : 1;
        }
    }
    if (self->f174 == 3) {
        m3 = (*mode == 1) ? 2 : 1;
        m4 = (*mode == 2);
    } else {
        m4 = 0;
        m3 = (*mode == 2) ? 2 : 1;
    }
    mfp = (*mode == 3);
    m7 = 0;
    if (m4 == 0) {
        m7 = (self->f174 == 3);
    }
    s32 w;
    if (self->f174 == 3 && self->f17C == 0) {
        if ((*st & 3) != 0) {
            w = func_0020F5B8(self, 1);
        } else {
            w = 0;
        }
    } else {
        w = 0;
    }
    *o3 = w;
    if (*st & 0x10) {
        self->f1B4 = func_0020F5B8(self, 5);
    }
    if ((*st & 8) || ((*st & 1) && self->f180)) {
        if (self->f848) {
            func_0020EDD0(self, b1, b2, o5, 0, m3, m4, self->f164 - 1, self->f168 - 1, mfp, m7);
        } else {
            s32 t = self->f158 - 1;
            func_0020EF70(self, b1, b2, t, t, 0, 0, self->f154);
        }
    }
    if (self->f11C) {
        return 0;
    }
    if (*st & 4) {
        if (self->f848) {
            func_0020EDD0(self, b1, b2, o5, 1, m3, m4, self->f16C - 1, self->f170 - 1, 0, m7);
        } else {
            s32 t = self->f160 - 1;
            func_0020EF70(self, b1 + 2, b2, t, t, 0, 0, self->f15C);
        }
    }
    if (self->f11C) {
        return 0;
    }
    if ((*st & 1) && self->f180) {
        func_0020F4C8(self, 1);
    }
    if (*st & 3) {
        func_00210D90(*(s32*)((u8*)self + self->f810 * 0x140 + 0x594), 0x300);
        func_0020F0F0(self);
        s32 x = ((*st & 1) << 27) | (self->f1B4 << 16);
        s32 y = (self->f1B0 << 26) | 0x20000000;
        s32 z = *o3 << 25;
        func_0020F0C0(self, x | y | z);
    } else {
        *(s32*)((u8*)self + self->f810 * 0x140 + 0x6CC) = 1;
    }
    self->f1B0 = 0;
    if (self->f11C) {
        return 0;
    }
    if ((*st & 1) == 0) {
        self->f1B0 = 1;
    }
    if ((*st & 1) && self->f180 == 0) {
        b1[5] = 0;
        b1[4] = 0;
        b1[1] = 0;
        b1[0] = 0;
        b1[7] = 0;
        b1[6] = 0;
        b1[3] = 0;
        b1[2] = 0;
    }
    s32 d = self->f150;
    if (d == 2 && (*st & 9) == 0) {
        b1[5] = 0;
        b1[4] = 0;
        b1[1] = 0;
        b1[0] = 0;
        if (self->f174 == 3) {
            *mode = d;
        } else {
            *mode = 1;
            *o5 = (self->f174 == 2);
        }
    }
    return 1;
}

struct Queue_20DF10;
struct Obj_20DF10 { u8 pad0[0x838]; s32 f838; s32 f83C; u8 pad840[0x18]; Queue_20DF10* f858; };
struct Msg_20DF10 { s32 cmd; s32 pad[7]; };

void func_0020F0F0(Obj_20DF10* o);
void func_0020B190(Queue_20DF10* q, Msg_20DF10* m);
void func_0020B978(Obj_20DF10* o, const char* msg);
s32 func_001F9D60(void);
s32 func_001F9DA8(void);

s32 func_0020DF10(Obj_20DF10* o)
{
    Msg_20DF10 m;
    Msg_20DF10 n;
    s32 result = 1;
    func_0020F0F0(o);
    while (*(volatile u32*)0x1000B020 != 0 && (*(volatile u32*)0x10002010 & 0x4000) == 0) {
        if (*(volatile u32*)0x1000B420 == 0 && (*(volatile u32*)0x1000B400 & 0x100) == 0) {
            m.cmd = 1;
            func_0020B190(o->f858, &m);
        }
    }
    u32 bp = *(volatile u32*)0x10002020;
    s64 top = *(s64*)0x10002030;
    o->f838 = (s32)top;
    if (top < 0) {
        u32 frac = bp & 0x1F;
        o->f83C = frac != 0 ? 0x20 - frac : 0;
    } else {
        o->f83C = 0x20;
    }
    if ((*(volatile u32*)0x10002010 & 0x4000) != 0) {
        result = 0;
        func_0020B978(o, "Error code detected(BDEC)");
        n.cmd = 2;
        func_0020B190(o->f858, &n);
        *(volatile u32*)0x10002010 = 0x40000000;
        n.cmd = 3;
        func_0020B190(o->f858, &n);
        func_001F9D60();
        *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
        *(volatile u32*)0x1000B000 = 0;
        *(u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
        func_001F9DA8();
        *(volatile u32*)0x1000B020 = 0;
    }
    return result;
}

struct Obj_0020F900 {
    u8 pad000[0x150];
    s32 f150;
    s32 f154;
    s32 f158;
    s32 f15C;
    s32 f160;
};

s32 func_0020F5B8(Obj_0020F900* self, s32 bits);
void func_0020FCE0(Obj_0020F900* self);
void func_0020F9C8(Obj_0020F900* self);
s32 func_0020FD28(Obj_0020F900* self, s32 a1);

void func_0020F900(Obj_0020F900* self)
{
    s32 first = func_0020F5B8(self, 10);
    self->f150 = func_0020F5B8(self, 3);
    func_0020F5B8(self, 16);
    if ((u32)(self->f150 - 2) < 2) {
        self->f154 = func_0020F5B8(self, 1);
        self->f158 = func_0020F5B8(self, 3);
    }
    if (self->f150 == 3) {
        self->f15C = func_0020F5B8(self, 1);
        self->f160 = func_0020F5B8(self, 3);
    }
    func_0020FCE0(self);
    func_0020F9C8(self);
    func_0020FD28(self, first);
}

struct Obj_0020FDA0 {
    u8 pad000[0xE8];
    s32 fE8;
    u8 padEC[0x1A4 - 0xEC];
    s32 f1A4;
    s32 f1A8;
    u8 pad1AC[0x84C - 0x1AC];
    s32 f84C;
    s32 f850;
    s32 f854;
};

s32 func_0020F5B8(Obj_0020FDA0* self, s32 bits);
void func_0020F9C8(Obj_0020FDA0* self);

void func_0020FDA0(Obj_0020FDA0* self)
{
    self->fE8 = 0;
    self->f84C = self->f850 + 1;
    self->f854 = 1;
    func_0020F5B8(self, 1);
    func_0020F5B8(self, 5);
    func_0020F5B8(self, 6);
    func_0020F5B8(self, 1);
    func_0020F5B8(self, 6);
    func_0020F5B8(self, 6);
    self->f1A4 = func_0020F5B8(self, 1);
    self->f1A8 = func_0020F5B8(self, 1);
    func_0020F9C8(self);
}

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_0020BF78();
void func_0020C0A8();
void func_0020C138();
void func_0020C148();
void func_0020C158();
void func_0020C168();
void func_0020FAF0();
void func_0020FF08();
void func_00210000();
extern const Fn_Table D_00250430[12] = { (Fn_Table)func_0020C148, (Fn_Table)func_0020BF78, (Fn_Table)func_0020C0A8, (Fn_Table)func_0020FE40, (Fn_Table)func_00210000, (Fn_Table)func_0020C138, (Fn_Table)func_0020C148, (Fn_Table)func_0020FF08, (Fn_Table)func_0020FAF0, (Fn_Table)func_0020C158, (Fn_Table)func_0020C168, 0 };

struct Self_0020FF08 {
    u8 pad0[0x13C];
    s32 f13C;
    u8 pad1[0x174 - 0x140];
    s32 f174;
    s32 f178;
    u8 pad2[0x184 - 0x17C];
    s32 f184;
    u8 pad3[0x18C - 0x188];
    s32 a[3];
    s32 b[3];
};

s32 func_0020F5B8(Self_0020FF08* self, s32 k);

void func_0020FF08(Self_0020FF08* self)
{
    s32 n;
    s32 i;
    if (self->f13C != 0) {
        if (self->f184 != 0) n = (self->f178 != 0) ? 3 : 2;
        else n = 1;
    } else if (self->f174 != 3) {
        n = 1;
    } else {
        n = (self->f184 != 0) ? 3 : 2;
    }
    for (i = 0; i < n; i++) {
        self->a[i] = func_0020F5B8(self, 0x10);
        func_0020F5B8(self, 1);
        self->b[i] = func_0020F5B8(self, 0x10);
        func_0020F5B8(self, 1);
    }
}

struct Obj_20F3C0 {
    u8 pad0[0x818];
    s32 f818;
    u8 pad81C[0x838 - 0x81C];
    s32 f838;
    s32 f83C;
    u8 pad840[0x858 - 0x840];
    u8* f858;
};

s64 func_0020F198(Obj_20F3C0* obj);
s32 func_0020B1E0(u8* p);

extern u32 D_0027B040[];

s32 func_0020F3C0(Obj_20F3C0* obj, s32 a1)
{
    if (obj->f818 != 0 || obj->f83C < a1) {
        s32 cnt = 0;
        while ((*(volatile u32*)0x10002010 & 0x80004000) == 0x80000000) {
            if (cnt++ > 0x1388) {
                func_0020B1E0(obj->f858);
                cnt = 0;
            }
        }
        *(volatile u32*)0x10002000 = 0x40000000;
        obj->f818 = D_0027B040[4];
        obj->f838 = func_0020F198(obj);
        obj->f83C = 0x20;
    }
    return (u32)obj->f838 >> (32 - a1);
}

struct Obj_20F5B8 {
    u8 pad0[0x818];
    s32 f818;
    u8 pad81C[0x838 - 0x81C];
    s32 f838;
    s32 f83C;
    u8 pad840[0x858 - 0x840];
    u8* f858;
};

s64 func_0020F198(Obj_20F5B8* obj);
s32 func_0020B1E0(u8* p);

extern u32 D_0027B040[];

struct Cmd_20F5B8 {
    static void Send(Obj_20F5B8* obj, u32 cmd)
    {
        *(volatile u32*)0x10002000 = cmd;
        obj->f818 = D_0027B040[cmd >> 28];
        obj->f838 = func_0020F198(obj);
    }
};

s32 func_0020F5B8(Obj_20F5B8* obj, s32 a1)
{
    s32 cnt = 0;
    u32 v;
    while ((*(volatile u32*)0x10002010 & 0x80004000) == 0x80000000) {
        if (cnt++ > 0x1388) {
            func_0020B1E0(obj->f858);
            cnt = 0;
        }
    }
    if (obj->f818 != 0 || obj->f83C < a1) {
        Cmd_20F5B8::Send(obj, 0x40000000);
    }
    v = (u32)obj->f838 >> (32 - a1);
    obj->f83C = 0x20;
    Cmd_20F5B8::Send(obj, a1 | 0x40000000);
    return v;
}

struct Ctx_20EDD0;
s32 func_0020F5B8(Ctx_20EDD0* c, s32 n);
void func_0020EF70(Ctx_20EDD0* c, u8* p, s32 a2, s32 a3, s32 a4, s32 a5, s32* a6, s32 a7);

void func_0020EDD0(Ctx_20EDD0* c, u8* arr, s32 a2, s32* out, s32 i, s32 mode, s32 a6, s32 a7, s32 s6, s32 s3, s32* fp)
{
    s32 v;
    s32* o;

    if (mode == 1) {
        if (a6 == 0 && s3 == 0) {
            v = func_0020F5B8(c, 1);
            out[i] = v;
            out[i + 2] = v;
        }
        i <<= 3;
        func_0020EF70(c, arr + i, a2, a7, s6, s3, fp, 0);
        u32* q = (u32*)(arr + i);
        u32 x = q[0];
        u32 y = q[1];
        q[4] = x;
        q[5] = y;
    } else {
        s32 j = i << 3;
        v = func_0020F5B8(c, 1);
        out[i] = v;
        o = out + i;
        func_0020EF70(c, arr + j, a2, a7, s6, s3, fp, 0);
        o[2] = func_0020F5B8(c, 1);
        func_0020EF70(c, arr + (j + 16), a2, a7, s6, s3, fp, 0);
    }
}

extern u32 D_0027B040[];

struct Sub_20F248;
struct Self_20F248 {
    u8 pad0[0x11C];
    s32 f11C;
    u8 pad1[0x6F8];
    s32 f818;
    u8 pad2[0x1C];
    s32 f838;
    s32 f83C;
    u8 pad3[0x18];
    Sub_20F248* f858;
};

s32 func_0020B1E0(Sub_20F248* s);

s16 func_0020F248(Self_20F248* self, s32 mode)
{
    s32 m = 0;
    s32 n = 0;
    s32 cmd;
    s64 st;
    s64 hw;

    if ((*(volatile u32*)0x10002010 & 0x80004000) == 0x80000000) {
        do {
            if (n++ >= 5001) {
                func_0020B1E0(self->f858);
                n = 0;
            }
        } while ((*(volatile u32*)0x10002010 & 0x80004000) == 0x80000000);
    }
    cmd = (mode << 26) | 0x30000000;
    *(volatile u32*)0x10002000 = cmd;
    self->f818 = D_0027B040[cmd >> 28];
    st = *(volatile s64*)0x10002000;
    if (st < 0) {
        do {
            if (m++ >= 5001) {
                func_0020B1E0(self->f858);
                m = 0;
            }
            st = *(volatile s64*)0x10002000;
        } while (st < 0);
    }
    u32 cnt = *(volatile u32*)0x10002020;
    hw = *(s64*)0x10002030;
    self->f838 = (s32)hw;
    if (hw < 0) {
        self->f83C = (-(cnt & 0x1F)) & 0x1F;
    } else {
        self->f83C = 0x20;
    }
    self->f11C = ((s32)st == 0);
    return (s16)st;
}

struct Ctx_20FAF0 {
    u8 pad0[0xD4];
    s32 f_d4;
    u8 pad1[0x164 - 0xD8];
    s32 f164, f168, f16c, f170, f174, f178, f17c, f180, f184, f188;
};

s32 func_0020F5B8(Ctx_20FAF0* c, s32 n);

void func_0020FAF0(Ctx_20FAF0* c)
{
    c->f164 = func_0020F5B8(c, 4);
    c->f168 = func_0020F5B8(c, 4);
    c->f16c = func_0020F5B8(c, 4);
    c->f170 = func_0020F5B8(c, 4);
    *(u32*)0x10002010 = (*(u32*)0x10002010 & 0xFFFCFFFF) | (func_0020F5B8(c, 2) << 16);
    s32 v = func_0020F5B8(c, 2);
    c->f174 = v;
    if (c->f_d4 == 0) c->f_d4 = v;
    c->f178 = func_0020F5B8(c, 1);
    c->f17c = func_0020F5B8(c, 1);
    c->f180 = func_0020F5B8(c, 1);
    *(volatile u32*)0x10002010 = (*(volatile u32*)0x10002010 & 0xFFBFFFFF) | (func_0020F5B8(c, 1) << 22);
    *(volatile u32*)0x10002010 = (*(volatile u32*)0x10002010 & 0xFFDFFFFF) | (func_0020F5B8(c, 1) << 21);
    *(volatile u32*)0x10002010 = (*(volatile u32*)0x10002010 & 0xFFEFFFFF) | (func_0020F5B8(c, 1) << 20);
    c->f184 = func_0020F5B8(c, 1);
    func_0020F5B8(c, 1);
    c->f188 = func_0020F5B8(c, 1);
    if (func_0020F5B8(c, 1) == 0) return;
    func_0020F5B8(c, 1);
    func_0020F5B8(c, 3);
    func_0020F5B8(c, 1);
    func_0020F5B8(c, 7);
    func_0020F5B8(c, 8);
}

extern const char D_00250300[32] = "Error code detected(BDEC)";
extern const char D_00250320[56] = "Invalid macroblock_address_increment code(0x%08x)";
extern const char D_00250358[32] = "= Skip to the next picture =";
extern const char D_00250378[40] = "slice_start_code(0x%08x) out of range";
extern const char D_002503A0[32] = "_sliceA0(): error happens";
extern const char D_002503C0[32] = "Too many macroblocks in picture";
extern const char D_002503E0[48] = "skiped macroblock in I picure is not allowed";
extern const char D_00250410[32] = "Invalid macroblock_type code: 0";
extern const char D_00250460[40] = "load_chroma_intra_quantizer_matrix == 1";
extern const char D_00250488[48] = "load_chroma_non_intra_quantizer_matrix == 1";
