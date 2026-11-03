// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

extern u8 D_0024F230[];

struct Node_2000F0 {
    s32 field0;
    void *vtbl;
    s32 field2;
    s32 field3;
};

void func_002000F0(struct Node_2000F0 *self, s32 a1, s32 a2, s32 a3) {
    if (self != 0) {
        self->field0 = a1;
        self->vtbl = D_0024F230;
        self->field2 = a2;
        self->field3 = a3;
    }
}

extern u8 D_0024F248[];

struct Node_200118 {
    s32 field0;
    void *vtbl;
    s32 field2;
};

void func_00200118(struct Node_200118 *self, s32 a1, s32 a2) {
    if (self != 0) {
        self->field2 = a2;
        self->field0 = a1;
        self->vtbl = D_0024F248;
    }
}

extern u8 D_0024F260[];

void func_00200138(void* self, void* value)
{
    if (self != 0) {
        *(void**)self = value;
        *(void**)((u8*)self + 4) = D_0024F260;
    }
}

extern u8 D_0024F230[];

struct Node_2003F8 {
    s32 field0;
    void *vtbl;
    s32 field2;
    s32 field3;
};

struct Node_2003F8 *func_002003F8(struct Node_2003F8 *self, s32 a1, s32 a2, s32 a3) {
    self->field0 = a1;
    self->vtbl = D_0024F230;
    self->field2 = a2;
    self->field3 = a3;
    return self;
}

extern u8 D_0024F248[];

void* func_00200488(void* self, void* a, void* b)
{
    *(void**)self = a;
    *(void**)((u8*)self + 4) = D_0024F248;
    *(void**)((u8*)self + 8) = b;
    return self;
}

extern u8 D_0024F260[];

void* func_00200518(void* self, void* value)
{
    *(void**)self = value;
    *(void**)((u8*)self + 4) = D_0024F260;
    return self;
}

extern u8 D_0024F278[];

void* func_002005D0(void* self)
{
    *(void**)self = D_0024F278;
    return self;
}

extern u8 D_0024F290[];

void* func_00200668(void* self)
{
    *(void**)self = D_0024F290;
    return self;
}

extern u8 D_0024F2A8[];

void* func_002006F8(void* self, void* value)
{
    *(void**)self = value;
    *(void**)((u8*)self + 4) = D_0024F2A8;
    return self;
}

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_0024F428[];

struct Node_200C90 {
    s32 field0;
    void *vtbl;
    s32 field2;
};

void func_00200C90(struct Node_200C90 *self, s32 a1, s32 a2) {
    if (self != 0) {
        self->field2 = a2;
        self->field0 = a1;
        self->vtbl = ((u8*)D_0024F428);
    }
}

extern const Fn_Table D_0024F3F8[];

struct Node_200CD8 {
    s32 field0;
    void *vtbl;
};

void func_00200CD8(struct Node_200CD8 *self, s32 a1) {
    if (self != 0) {
        self->field0 = a1;
        self->vtbl = ((u8*)D_0024F3F8);
    }
}

extern const Fn_Table D_0024F3E8[];

struct Node_200CF8 {
    s32 field0;
    void *vtbl;
};

void func_00200CF8(struct Node_200CF8 *self, s32 a1) {
    if (self != 0) {
        self->field0 = a1;
        self->vtbl = ((u8*)D_0024F3E8);
    }
}

extern const Fn_Table D_0024F3D8[];

struct Node_200D18 {
    s32 field0;
    void *vtbl;
};

void func_00200D18(struct Node_200D18 *self, s32 a1) {
    if (self != 0) {
        self->field0 = a1;
        self->vtbl = ((u8*)D_0024F3D8);
    }
}

extern const Fn_Table D_0024F3C8[];

struct Node_200D38 {
    s32 field0;
    void *vtbl;
};

void func_00200D38(struct Node_200D38 *self, s32 a1) {
    if (self != 0) {
        self->field0 = a1;
        self->vtbl = ((u8*)D_0024F3C8);
    }
}

extern const Fn_Table D_0024F418[];

struct Node_200CB0 {
    s32 field0;
    void *vtbl;
    s32 field2;
    s32 field3;
};

void func_00200CB0(struct Node_200CB0 *self, s32 a1, s32 a2, s32 a3) {
    if (self != 0) {
        self->field0 = a1;
        self->vtbl = ((u8*)D_0024F418);
        self->field2 = a3;
        self->field3 = a2;
    }
}

// NEAR: retail saves $s0 and $ra with 8-byte sd (ld to restore); 2.95.3 saves
// them with 16-byte sq/lq, and no source form tried changed that. Otherwise
// the body matches.

extern u8 D_0062C5B8[];
extern u8 D_0024F210[];
extern u8 D_0027B318[];

struct Node_200000 {
    s32 field0;
    void *vtbl;
    s32 field2;
};

void func_001FF008(void);
void func_00200118(struct Node_200000 *self, void *a1, void *a2);

void* func_00200000(void)
{
    struct Node_200000 *self = (struct Node_200000 *)D_0062C5B8;
    if (*(void**)D_0062C5B8 == 0) {
        func_001FF008();
        func_00200118(self, D_0024F210, D_0027B318);
    }
    return self;
}

struct Obj_200158;
s32 func_002000B0(Obj_200158* self, s32 a1, s32 a2);

s32 func_00200158(Obj_200158* self, s32 a1, s32 a2, s32 fallback)
{
    s32 result = fallback;
    if (func_002000B0(self, a1, a2) == 0) {
        result = 0;
    }
    return result;
}

// NEAR: identical except the register saves: retail saves s0/ra with sd (8 bytes), ours with sq (16 bytes); only the Sony 2.9-ee build saves in 8 bytes (docs/TOOLCHAIN.md), so the SN build cannot match this function.

extern u8 D_0062C5C8[];
extern u8 D_0024F2B8[];
extern u8 D_0062C5D8[];

struct Node_200418 { s32 field0; };

void func_00200118(struct Node_200418* self, void* a1, void* a2);

void* func_00200530(void);
void* func_00200418(void)
{
    u8* obj = D_0062C5C8;
    if (*(void**)obj == 0) {
        func_00200530();
        func_00200118((struct Node_200418*)obj, D_0024F2B8, D_0062C5D8);
    }
    return obj;
}

// NEAR: US: retail saves s0 and ra with sd (8 bytes, the Sony 2.9-ee compiler), the default compiler saves sq; the body matches.

struct Self_002004A8;

void func_00200530(struct Self_002004A8* a0);
void func_00200118(struct Self_002004A8* self, void* a1, void* a2);

extern u8 D_0062C5E8[];
extern u8 D_0062C5D8[];
extern u8 D_0024F2D0[];

void* func_002004A8(struct Self_002004A8* a0)
{
    u8* self = D_0062C5E8;
    if (*(s32*)self == 0) {
        func_00200530(a0);
        func_00200118((struct Self_002004A8*)self, D_0024F2D0, D_0062C5D8);
    }
    return self;
}

// NEAR: every instruction matches except the two register saves: retail
// saves $s0 and $ra with sd (8 bytes), ours with sq (16 bytes): the Sony SDK
// compiler's saves (docs/TOOLCHAIN.md), not the default compiler's. The frame,
// the calls and the return are the same. An s64 local made it 88 bytes.

extern u8 D_0062C5D8[];
extern u8 D_0024F2E8[];
extern u8 D_0027B320[];

struct Ctx_200530 { s32 field0; };
void func_00200118(struct Ctx_200530 *self, void *a1, void *a2);

void* func_00200710(void);
void *func_00200530(void) {
    if (*(void **)D_0062C5D8 == 0) {
        func_00200710();
        func_00200118((struct Ctx_200530 *)D_0062C5D8, D_0024F2E8, D_0027B320);
    }
    return D_0062C5D8;
}

// NEAR: the body is EXACT as far as the listing goes; retail saves $s0 and $ra with sd (8 bytes), ours with sq: only the prologue and epilogue differ.

extern u8 D_0062C5F8[];
extern u8 D_0024F300[];
extern u8 D_0027B318[];

struct Obj_002005E8 {
    void *vtbl;
};

void func_001FF008(void);
void func_00200118(struct Obj_002005E8 *self, void *a1, void *a2);

void *func_002005E8(void)
{
    struct Obj_002005E8 *p = (struct Obj_002005E8 *)D_0062C5F8;
    if (p->vtbl == 0) {
        func_001FF008();
        func_00200118(p, D_0024F300, D_0027B318);
    }
    return p;
}

// NEAR: retail saves $ra and $s0 with sd (8 bytes); this compiler saves them with sq (16 bytes). The body is otherwise identical.

extern u8 D_0062C608[];
extern u8 D_0024F310[];
extern u8 D_0027B318[];

struct Node_200680 {
    void *field0;
};

void func_001FF008(void);
void func_00200118(struct Node_200680 *self, void *a1, void *a2);

void *func_00200680(void)
{
    struct Node_200680 *self = (struct Node_200680 *)D_0062C608;
    if (self->field0 == 0) {
        func_001FF008();
        func_00200118(self, D_0024F310, D_0027B318);
    }
    return self;
}

// NEAR: retail saves $ra with sd, default compiler with sq; body identical
struct Ctx_002006D0;
s32 func_002000B0(Ctx_002006D0* a, Ctx_002006D0* b);

s32 func_002006D0(Ctx_002006D0* a, Ctx_002006D0* b)
{
	return func_002000B0(a, b) ^ 1;
}

// NEAR: body matches; retail saves $s0 and $ra with sd/ld (8 bytes), this compiler saves sq/lq: a lib-code compiler difference

extern u8 D_0027B320[];
extern u8 D_0024F320[];

struct Node_200710 {
    void *vtbl;
};

void func_00200138(struct Node_200710 *self, void *value);

void *func_00200710(void) {
    void **p = (void **)D_0027B320;
    if (*p == 0) {
        func_00200138((struct Node_200710 *)D_0027B320, D_0024F320);
    }
    return D_0027B320;
}

// NEAR: retail saves $ra with sd (Sony 2.9-ee-991111 library code, 0x1F59C4 on); the default compiler saves it with sq. Nothing else differs.

struct Key_200750;
s32 func_001F6738(Key_200750* p, s32 v);

s32 func_00200750(Key_200750** a, s32* b) { return (s32)((u32)func_001F6738(*a, *b) >> 31); }

// NEAR: retail saves and restores ra with sd/ld (8-byte); the SN build uses sq/lq. The body matches otherwise.

struct Sub_00200C40 {
    s16 off;
    u8 pad2[2];
    void* ptr;
};

struct Obj_00200C40 {
    u8 pad0[4];
    struct Sub_00200C40* sub;
};

s32 func_00200D58(void* a0, void* a1, s32 a2, void* a3, void* a4, struct Obj_00200C40* a5);
s32 func_00201460(void);

s32 func_00200C40(struct Obj_00200C40* p) {
    s32 r = 0;
    if (p != 0) {
        struct Sub_00200C40* sub = p->sub;
        r = func_00200D58(sub->ptr, (void*)func_00201460, 1,
                          (u8*)p + sub->off, (void*)func_00200710, p);
    }
    return r != 0;
}

// NEAR: ra and s0 saved with sq, retail sd (the body matches).

extern u8 D_0062C618[];
extern u8 D_0024F438[];
extern u8 D_0027B320[];

struct Node_2011C0 {
    s32 field0;
    void *vtbl;
};

void func_00200118(struct Node_2011C0 *self, s32 a1, s32 a2);

struct Node_2011C0 *func_002011C0(void) {
    struct Node_2011C0 *self = (struct Node_2011C0 *)D_0062C618;
    if (*(s32 *)D_0062C618 == 0) {
        func_00200710();
        func_00200118(self, (s32)D_0024F438, (s32)D_0027B320);
    }
    return self;
}

// NEAR: only the s0 and ra saves differ: retail saves ra and s0 with sd (8 bytes), the SN builds with sq; the 8-byte save is the Sony 2.9-ee-991111 form (docs/TOOLCHAIN.md), not used here.

extern u8 D_0062C628[];
extern u8 D_0024F450[];
extern u8 D_0027B320[];

struct Node_201230 {
    s32 field0;
    void *vtbl;
};

void func_00200118(struct Node_201230 *self, void *a1, void *a2);

void *func_00201230(void) {
    struct Node_201230 *node = (struct Node_201230 *)D_0062C628;
    if (*(void **)D_0062C628 == 0) {
        func_00200710();
        func_00200118(node, D_0024F450, D_0027B320);
    }
    return node;
}

// NEAR: body matches; retail saves $s0 and $ra with sd/ld (8 bytes), this compiler saves sq/lq: a lib-code compiler difference

extern u8 D_0062C638[];
extern u8 D_0024F468[];
extern u8 D_0027B320[];

struct Node_2012A0 {
    void *vtbl;
    s32 field1;
    s32 field2;
};

void *func_00200710(void);
void func_00200118(struct Node_2012A0 *self, void *a1, void *a2);

void *func_002012A0(void) {
    void **p = (void **)D_0062C638;
    if (*p == 0) {
        func_00200710();
        func_00200118((struct Node_2012A0 *)D_0062C638, D_0024F468, D_0027B320);
    }
    return D_0062C638;
}

// NEAR: only the $ra and $s0 saves differ: retail sd/ld, ours sq/lq

extern u8 D_0062C648[];
extern u8 D_0024F480[];
extern u8 D_0027B320[];

struct Node_201310 {
    void *field0;
};

void func_00200118(struct Node_201310 *self, void *a1, void *a2);

void* func_00201310(void) {
    struct Node_201310 *node = (struct Node_201310 *)D_0062C648;
    if (node->field0 == 0) {
        func_00200710();
        func_00200118(node, D_0024F480, D_0027B320);
    }
    return node;
}

// NEAR: retail saves $s0 and $ra with 8-byte sd (ld to restore); 2.95.3 saves
// them with 16-byte sq/lq, and no source form tried changed that. Otherwise
// the body matches.

extern u8 D_0062C658[];
extern u8 D_0024F498[];
extern u8 D_0027B320[];

struct Node_201380 {
    s32 field0;
    void *vtbl;
    s32 field2;
};

void func_00200118(struct Node_201380 *self, void *a1, void *a2);

void* func_00201380(void)
{
    struct Node_201380 *self = (struct Node_201380 *)D_0062C658;
    if (*(void**)D_0062C658 == 0) {
        func_00200710();
        func_00200118(self, D_0024F498, D_0027B320);
    }
    return self;
}

// NEAR: identical except the register saves: retail saves s0/ra with sd (8 bytes), ours with sq (16 bytes); only the Sony 2.9-ee build saves in 8 bytes (docs/TOOLCHAIN.md), so the SN build cannot match this function.

extern u8 D_0062C668[];
extern u8 D_0024F4B0[];
extern u8 D_0027B320[];

struct Node_2013F0 { s32 field0; };

void func_00200118(struct Node_2013F0* self, void* a1, void* a2);

void* func_002013F0(void)
{
    u8* obj = D_0062C668;
    if (*(void**)obj == 0) {
        func_00200710();
        func_00200118((struct Node_2013F0*)obj, D_0024F4B0, D_0027B320);
    }
    return obj;
}

// NEAR: US: retail saves s0 and ra with sd (8 bytes, the Sony 2.9-ee compiler), the default compiler saves sq; the body matches.

struct Self_00201460;

void func_00200710(struct Self_00201460* a0);
void func_00200118(struct Self_00201460* self, void* a1, void* a2);

extern u8 D_0062C678[];
extern u8 D_0024F4C8[];
extern u8 D_0027B320[];

void* func_00201460(struct Self_00201460* a0)
{
    u8* self = D_0062C678;
    if (*(s32*)self == 0) {
        func_00200710(a0);
        func_00200118((struct Self_00201460*)self, D_0024F4C8, D_0027B320);
    }
    return self;
}

// NEAR: EXACT only with SLY1_COMPILER=2.9-ee-991111 (Sony's release, saves in 8 bytes, as in the libraries); the default 2.9.3 build saves with sq/lq and differs (docs/TOOLCHAIN.md, lib compiler row not supported by tools/compile.py).

struct Arg_2016A0;

struct Out_2016A0 {
    s32 f0;
};

s32 func_001FA0E0(Arg_2016A0* a, void* b);

extern s32 D_0027B328;

s32 func_002016A0(Out_2016A0* self, Arg_2016A0* a1, void* a2)
{
    s32 r;
    D_0027B328 = 0;
    r = func_001FA0E0(a1, a2);
    if (r == -1) {
        if (D_0027B328 != 0) {
            self->f0 = D_0027B328;
        }
    }
    return r;
}

// NEAR: retail saves and reloads $ra as sd/ld (8 bytes); 2.95.3 emits sq/lq (16 bytes). Nothing else differs.

s32 func_001FA0D8(void);

s32 func_00201700(void)
{
    return func_001FA0D8();
}

// NEAR: exact only with the Sony 2.9-ee-991111 compiler (retail saves ra with sd/ld); the default SN GCC 2.95.3 saves it with sq/lq and differs.

struct Ctx_202058;

void* func_001F6C60(Ctx_202058* self);
void func_001F6C70(Ctx_202058* self);

void* func_00202058(Ctx_202058* self)
{
    void* r = func_001F6C60(self);
    func_001F6C70(self);
    return r;
}

// NEAR: retail saves s0, s1 and ra with 8-byte sd/ld; the default 2.95.3 build saves 16-byte sq/lq, so the prologue, epilogue and the 0x50 frame's store order differ (default compiler cannot make sd saves here)

struct Arg_202D30;
struct Tmp_202D30 {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
    s32 w4;
    s32 w5;
};

extern void* func_001F6B20(Tmp_202D30* p);
extern void func_001F69E0(Arg_202D30* a, void* cb, void* ctx);
extern void func_001F6B60(void* p);
extern void func_001F6B30(void* p);
extern void func_00202D00(void);

void func_00202D30(u16 id)
{
    Tmp_202D30 tmp;
    void* obj;

    tmp.w1 = 1;
    tmp.w2 = 0;
    tmp.w5 = 0;
    obj = func_001F6B20(&tmp);
    func_001F69E0((Arg_202D30*)(u32)id, (void*)((char*)func_00202D00 + 8), obj);
    func_001F6B60(obj);
    func_001F6B30(obj);
}

// NEAR: retail saves $ra and $s0-$s1 with sd (8 bytes); this compiler saves them with sq (16 bytes). The body is otherwise identical.

extern u8 D_00279410[];
extern u8 D_0024F638[];
extern u8 D_00279430[];
extern u8 D_0027A5D0[];

struct Arg_2032C8 {
    s32 field0;
};

void func_001F7B88(void *p);
void func_00202D30(s32 frames);
s32 func_001F8480(void *p);

s32 func_002032C8(void *p)
{
    if (p == 0) {
        if (*(s32 *)D_00279410 > 0) {
            func_001F7B88(D_0024F638);
        }
        while (*(s32 *)D_00279430 != 0 || func_001F8480(D_0027A5D0) != 0) {
            func_00202D30(60);
        }
        return 0;
    }
    if (*(s32 *)D_00279430 != 0 || func_001F8480(D_0027A5D0)) {
        return 1;
    }
    return 0;
}

// NEAR: every instruction matches except the two register saves: retail
// saves $ra and $s0 with sd (8 bytes), ours with sq (16 bytes). Retail's
// sd saves are the Sony SDK compiler's (2.9-ee-991111), which the default
// compiler does not emit (docs/TOOLCHAIN.md), so this stays NEAR.

extern u8 D_00279410[];
extern u8 D_0024F648[];
extern u8 D_0027AE48[];

struct Ctx_203368 { s32 field0; };
void func_001F7B88(struct Ctx_203368 *self);
s32 func_001F8480(struct Ctx_203368 *self);
void func_00202D30(struct Ctx_203368 *self);

s32 func_00203368(s32 flag) {
    if (flag == 0) {
        if (*(s32 *)D_00279410 > 0) {
            func_001F7B88((struct Ctx_203368 *)D_0024F648);
        }
        while (func_001F8480((struct Ctx_203368 *)D_0027AE48) != 0) {
            func_00202D30((struct Ctx_203368 *)60);
        }
        return 0;
    }
    return func_001F8480((struct Ctx_203368 *)D_0027AE48);
}

// NEAR: sd saves (library code, 2.9-ee-991111); same shape as func_00203230 (D_0027A600, 3-length), same branch-layout difference.

struct Blk_203CF8;
s32 func_002033D8(s32 kind);
s32 func_001F8290(Blk_203CF8* a, s32 b, s32 c, s32 d, s32 e, u32 f, s32 g, s32 h, s32 i);
void func_001F6B40(s32 h);
extern u8 D_0027AE48[];
extern u8 D_0027A600[];
extern s32 D_0027942C;

s32 func_00203CF8(void)
{
    u32 base;
    s32 v;

    if (!func_002033D8(1)) return 0;
    base = (u32)D_0027A600;
    if (func_001F8290((Blk_203CF8*)D_0027AE48, 3, 0, 0, 0, base, 4, 0, 0) < 0) {
        func_001F6B40(D_0027942C);
        return 0;
    }
    v = *(s32*)(base | 0x20000000);
    func_001F6B40(D_0027942C);
    return v;
}

// NEAR: sd saves (library code, 2.9-ee-991111); same shape as func_00203230 (D_0027A600, 4-length, returns -1), same branch-layout difference.

struct Blk_203D90;
s32 func_002033D8(s32 kind);
s32 func_001F8290(Blk_203D90* a, s32 b, s32 c, s32 d, s32 e, u32 f, s32 g, s32 h, s32 i);
void func_001F6B40(s32 h);
extern u8 D_0027AE48[];
extern u8 D_0027A600[];
extern s32 D_0027942C;

s32 func_00203D90(void)
{
    u32 base;
    s32 v;

    if (!func_002033D8(3)) return -1;
    base = (u32)D_0027A600;
    if (func_001F8290((Blk_203D90*)D_0027AE48, 4, 0, 0, 0, base, 4, 0, 0) < 0) {
        func_001F6B40(D_0027942C);
        return -1;
    }
    v = *(s32*)(base | 0x20000000);
    func_001F6B40(D_0027942C);
    return v;
}

extern u8 D_0024F0D8[];

s32 func_0018D778(void* self);

s32 func_00200050(void* self, s32 flags)
{
    void* v = D_0024F0D8;
    *(void**)self = v;
    if (flags & 1) {
        return func_0018D778(self);
    }
    return (s32)v;
}

struct Ctx_002004F8;
s32 func_00200080(Ctx_002004F8* ctx);

s32 func_002004F8(Ctx_002004F8* ctx)
{
    return func_00200080(ctx);
}

extern s32 func_00200080(void);
s32 func_00200580(void)
{
    return func_00200080();
}

struct Obj_002005A0 { u8* f0; };

s32 func_0018D778(Obj_002005A0* self);
extern u8 D_0024F0D8[];

u8* func_002005A0(Obj_002005A0* self, s32 flag)
{
    u8* value = D_0024F0D8;
    self->f0 = value;
    if (flag & 1) {
        return (u8*)func_0018D778(self);
    }
    return value;
}

extern u8 D_0024F0D8[];

s32 func_0018D778(void* self);

s32 func_00200638(void* self, s32 flags)
{
    void* v = D_0024F0D8;
    *(void**)self = v;
    if (flags & 1) {
        return func_0018D778(self);
    }
    return (s32)v;
}

s32 func_00200080(void);

s32 func_00201210(void)
{
    return func_00200080();
}

struct Ctx_002004F8;
s32 func_00200080(Ctx_002004F8* ctx);

s32 func_002012F0(Ctx_002004F8* ctx)
{
    return func_00200080(ctx);
}

extern s32 func_00200080(void);
s32 func_00201360(void)
{
    return func_00200080();
}

s32 func_00200080(void);

s32 func_002013D0(void)
{
    return func_00200080();
}

s32 func_00200080(void);

s32 func_00201440(void)
{
    return func_00200080();
}

struct Cfg_00202120;
s32 func_001F6C60(Cfg_00202120* c);

s32 func_00202120(Cfg_00202120* c)
{
    return func_001F6C60(c);
}

void func_00202768(u8* p, s32 n)
{
    s32 i = n - 1;
    if (n != 0) {
        do {
            *p = 0;
            i--;
            p++;
        } while (i != -1);
    }
}

// BYTES 183/188 (97.3%), checked 2026-11-01
// NEAR: the function body matches in behavior, but the candidate is 192 bytes versus retail 188 and uses sq/lq instead of sd/ld.
// NEAR: all body instructions match; SN emits sq/lq saves where retail uses sd/ld (and reports 192 vs 188 bytes).
void* func_00201BA8(void*);

void func_00201BB8(void* self)
{
    s16 kind = *(s16*)((u8*)func_00201BA8(self) + 6);
    if (kind == 1) {
        *(volatile u64*)0x12000000 = *(u64*)self;
        *(volatile u64*)0x12000070 = *(u64*)((u8*)self + 0x10);
        *(volatile u64*)0x12000080 = *(u64*)((u8*)self + 0x18);
        *(volatile u64*)0x120000C0 = *(u64*)((u8*)self + 0x20);
    } else {
        *(volatile u64*)0x12000000 = *(u64*)self;
        *(volatile u64*)0x12000020 = *(u64*)((u8*)self + 8);
        *(volatile u64*)0x12000090 = *(u64*)((u8*)self + 0x10);
        *(volatile u64*)0x120000A0 = *(u64*)((u8*)self + 0x18);
        *(volatile u64*)0x120000E0 = *(u64*)((u8*)self + 0x20);
    }
}

extern u8 D_0024F2A8[];
struct Obj_200080 { void* f0; void* f4; };
u8* func_0018D778(struct Obj_200080* self);
u8* func_00200080(struct Obj_200080* self, s32 flag)
{
    u8* p = D_0024F2A8;
    self->f4 = p;
    if ((flag & 1) != 0) return func_0018D778(self);
    return p;
}

struct Key_2000B0;
s32 func_001F6738(Key_2000B0* p, s32 v);

s32 func_002000B0(s32* a, s32* b)
{
    s32 r = 0;
    if (b == a || func_001F6738((Key_2000B0*)*a, *b) == 0)
        r = 1;
    return r;
}

extern s32 func_002000B0(void*, void*);
struct VTable {
    u8 pad[0x10];
    s16 offset;
    u8 pad2[2];
    s32 (*method)(void*, void*, void*, void*, void*, void*);
};
struct Object { u8 pad[4]; VTable* vtable; };
struct Handler { u8 pad[8]; Object* object; };
s32 func_00200188(Handler* handler, void* first, void* second, s32 fallback,
                  void* arg4, void* last)
{
    if (func_002000B0(handler, first)) {
        return fallback;
    }
    Object* object = handler->object;
    VTable* vtable = object->vtable;
    void* self = (u8*)object + vtable->offset;
    return vtable->method(self, first, second, (void*)fallback, arg4, last);
}

struct Callee_200468 { u8 pad[4]; s32 f4; };

s32 func_00200080(Callee_200468* self, s32 flag);

s32 func_00200468(Callee_200468* self, s32 flag) {
    return func_00200080(self, flag);
}

// func_00200D58: the callee pointers keep their order; the offset is read as an s32 local before the two calls.
typedef void* (*Factory_200D58)(void);
typedef s32 (*Value_200D58)(void);
typedef void (*Apply_200D58)(void*, s32, s32, s32, s32, s32);

void func_00200D58(Factory_200D58 factory, Value_200D58 firstValue, s32 arg2, s32 arg3, Value_200D58 secondValue, s32 arg5)
{
    void* object = factory();
    u8* state = *(u8**)((u8*)object + 4);
    s32 off = *(s16*)(state + 0x10);
    state += 0x10;
    object = (u8*)object + off;
    s32 first = firstValue();
    s32 second = secondValue();
    Apply_200D58 apply = *(Apply_200D58*)(state + 4);
    apply(object, first, arg2, arg3, second, arg5);
}

struct Callee_201280 { u8 pad[4]; s32 f4; };

s32 func_00200080(Callee_201280* self, s32 flag);

s32 func_00201280(Callee_201280* self, s32 flag) {
    return func_00200080(self, flag);
}

struct Obj_002014B0 { void* f0; void* f4; };
s32 func_00200080(struct Obj_002014B0* self, s32 flag);

s32 func_002014B0(struct Obj_002014B0* self, s32 flag)
{
    return func_00200080(self, flag);
}

struct Obj_201500 { u8 pad[0x1D4]; s32 buf; };
s32 func_0018D748(Obj_201500* o, s32 size);
s32 func_00201500(Obj_201500* o)
{
    if (o->buf == 0) {
        s32 r = func_0018D748(o, 0x80);
        o->buf = r;
        if (r == 0) return -1;
        s32* p = (s32*)r + 31;
        for (s32 i = 31; i >= 0; i--) *p-- = 0;
    }
    return 0;
}

struct Ctx_201668;
s32 func_00201578(Ctx_201668* ctx, s32 value);
extern s32 D_0027696C;

s32 func_00201668(s32 value)
{
    return func_00201578((Ctx_201668*)D_0027696C, value);
}

struct Elem_201FF8;

struct Obj_201FF8 {
    u8 pad0[0x50];
};

s32 func_00201BB8(Elem_201FF8* p);
s32 func_00201C78(Elem_201FF8* p);

s32 func_00201FF8(Obj_201FF8* self, s32 flag)
{
    u8* base = (u8*)self;
    s32 idx = flag & 1;
    s32 r;
    (void)func_00201BB8((Elem_201FF8*)(base + idx * 0x28));
    if (idx != 0) {
        r = func_00201C78((Elem_201FF8*)(base + 0x140));
    } else {
        r = func_00201C78((Elem_201FF8*)(base + 0x50));
    }
    return r;
}

extern s32 D_00279424;
extern s32 D_0027943C;

s32 func_001F9D60(void);
s32 func_001F9DA8(void);
s32 func_001FA4A0(s32 index, void* first, s32 second);
void func_00203008(void);

s32 func_00203050(void)
{
    D_00279424 = 1;
    func_001F9D60();
    func_001FA4A0(0x80000012, (u8*)func_00203008 + 8, 0);
    func_001F9DA8();
    D_00279424 = 0;
    D_0027943C = 1;
    return 1;
}

// EXACT: n++ inside the compare (old value tested, increment in the delay slot)

extern u8 D_0024F4E0[];

struct Fmt_201C78 { s32 field0; };
s32 func_001E1F10(struct Fmt_201C78 *fmt, ...);

s32 func_00201C78(void *self) {
    u32 n = 0;
    if (*(volatile u32 *)0x1000A000 & 0x100) {
        do {
            if (n++ > 0x1000000) {
                func_001E1F10((struct Fmt_201C78 *)D_0024F4E0);
                return -1;
            }
        } while (*(volatile u32 *)0x1000A000 & 0x100);
    }
    *(volatile u32 *)0x1000A020 = (s32)(*(s64 *)self & 0x7FFF) + 1;
    if (((u32)self & 0x70000000) == 0x70000000) {
        *(volatile u32 *)0x1000A010 = ((u32)self & 0x0FFFFFFF) | 0x80000000;
    } else {
        *(volatile u32 *)0x1000A010 = (u32)self & 0x0FFFFFFF;
    }
    *(volatile u32 *)0x1000A000 = 0x101;
    return 0;
}

u64* func_00201BA8();
s32 func_002023B0(s16 px, s16 py, s16 pz)
{
    u64* bits = func_00201BA8();
    s32 yS = (py + 63) / 64;
    s32 c;
    if (px & 2) {
        c = (pz + 63) / 64;
    } else {
        c = (pz + 31) / 32;
    }
    if ((*bits & 0x0000FFFF0000FFFFULL) == 1) {
        return ((yS * c) << 16) >> 16;
    }
    return ((yS * c) << 17) >> 16;
}

struct Q_203230;
struct Dev_203230;
extern u8 D_00279480[];
extern u8 D_0027A5D0[];
extern s32 D_00279428;
s32 func_002030C0(Q_203230* q);
s32 func_001F8290(Q_203230* q, s32 a1, s32 a2, s32 a3, s32 a4, u8* a5, s32 a6, s32 a7, s32 stack0);
s32 func_001F6B40(Dev_203230* d);

s32 func_00203230(void)
{
    if (func_002030C0((Q_203230*)2) == 0) {
        return 0;
    }
    u32 s0 = (u32)D_00279480;
    s32 r = func_001F8290((Q_203230*)D_0027A5D0, 0xE, 0, 0, 0, (u8*)s0, 4, 0, 0);
    if (r < 0) {
        (void)func_001F6B40((Dev_203230*)D_00279428);
        return 0;
    }
    s0 = *(u32*)(s0 | 0x20000000u);
    (void)func_001F6B40((Dev_203230*)D_00279428);
    return (s32)s0;
}

// NEAR: register roles ($s0/$s1/$s2) and branch layout after the first call differ; frame matches in size class.

struct Slot_203A20 { u32 value; };
struct Code_203A20 { u32 code; };
struct Hdl_203A20 { u32 h; };
struct Req_203A20 { u32 a; };

extern u32 D_0027AA40;
extern u8 D_0027A600[];
extern u8 D_0027AE48[];

extern s32 func_002033D8(Code_203A20* c);
extern void func_001FA7D8(Slot_203A20* q, s32 n);
extern s32 func_001F8290(Req_203A20* p, s32 a1, s32 a2, Slot_203A20* q, s32 a4, u8* a5, s32 a6, s32 a7, s32 a8);
extern void func_001F6B40(Hdl_203A20* h);

u32 func_00203A20(u32 a0)
{
    Slot_203A20* s2 = (Slot_203A20*)&D_0027AA40;
    u32 s0;
    s32 r;

    if (func_002033D8((Code_203A20*)0x22) != 0) {
        D_0027AA40 = a0;
    } else {
        return 0;
    }
    func_001FA7D8(s2, 4);
    s0 = (u32)D_0027A600;
    r = func_001F8290((Req_203A20*)D_0027AE48, 0x22, 0, s2, 4, D_0027A600, 4, 0, 0);
    if (r < 0) {
        func_001F6B40((Hdl_203A20*)(*(u32*)&D_0027942C));
        return 0;
    }
    s0 = *(u32*)(s0 | 0x20000000);
    func_001F6B40((Hdl_203A20*)(*(u32*)&D_0027942C));
    return s0;
}

struct Rec_201A18 { s16 x; s16 y; s16 flag; s16 ext; s32 f8; s32 fC; };

s32 func_001F6C70(u64 value);
void func_001F6D40(s32 n);
void func_001F6960(s32 n, s32 ptr);
void func_001F6910(s32 a, s32 b, s32 c);

void func_00201A18(s16 mode, s16 x, s16 y, s16 flag)
{
    Rec_201A18* p;
    u16 ext;

    switch (mode) {
    case 0:
        p = (Rec_201A18*)(u32)func_00201BA8();
        *(volatile u64*)0x12001000 = 0x200;
        p->x = x;
        ext = (u16)((*(volatile u64*)0x12001000 >> 16) & 0xFF);
        p->y = y;
        p->ext = ext;
        func_001F6C70(0xFF00);
        p->flag = (flag != 0);
        if (p->f8 != 0) {
            func_001F6D40(2);
            func_001F6960(2, p->fC);
            p->f8 = 0;
            p->fC = 0;
        }
        func_001F6910(x & 1, (u8)y, flag & 1);
        return;
    case 1:
        *(volatile u64*)0x12001000 = 0x100;
        return;
    case 5:
        p = (Rec_201A18*)(u32)func_00201BA8();
        p->flag = (flag != 0);
        p->x = x;
        p->y = y;
        p->ext = (u16)((*(volatile u64*)0x12001000 >> 16) & 0xFF);
        func_001F6910(x & 1, (u8)y, flag & 1);
        return;
    default:
        return;
    }
}

struct Buf_2027C8 { u8 bytes[0x14]; };
struct Slot_2027C8 { s32 w00; u8 pad04[0x0C]; s32 w10; u8 pad14[0x1C]; s32 w30; u8 pad34[0x0C]; s32 w40; u8 pad44[0x0C]; s32 w50; u8 pad54[0x2C]; s32 w80; };

s32 D_00279380[10] = { 1, 1, 1, 1, 1, 0, 0, 0, 1, 1 };
extern Slot_2027C8* D_00279340[];

void func_00202768(Buf_2027C8* b, s32 n);
s32 func_002028A8(Buf_2027C8* b);

s32 func_002027C8(s32 mode)
{
    Buf_2027C8 buf;
    s32 flag = *(volatile u32*)0x1000E000 & 1;
    s32 i;

    for (i = 0; i < 10; i++) {
        if (D_00279380[i] != 0) {
            Slot_2027C8* p = D_00279340[i];
            p->w00 = 0;
            p->w30 = 0;
            p->w10 = 0;
            p->w50 = 0;
            p->w40 = 0;
            p->w80 = 0;
        }
    }
    *(volatile u32*)0x1000E010 = 0xFF1F;
    u32 m = *(volatile u32*)0x1000E010 & 0xFF1F0000;
    *(u32*)0x1000E010 = m;
    func_00202768(&buf, 0x14);
    func_002028A8(&buf);
    if (mode == 1) {
        volatile u32* p = (volatile u32*)0x1000E000;
        *p |= 1;
    }
    return flag;
}

// The runtime's type names of the built-in types: each function builds its object in place
// the first time it is asked for, and returns it.
extern const void* const D_0024F408[];

struct TypeName_200E08 {
    const char* name;
    const void* vtbl;
    TypeName_200E08(const char* n)
    {
        vtbl = D_0024F408;
        name = n;
    }
    static void* operator new(unsigned int, void* p) throw() { return p; }
};

extern TypeName_200E08 D_00278E00;
extern const char D_0024F340[];

TypeName_200E08* func_00200E08(void)
{
    if (D_00278E00.name == 0) {
        new (&D_00278E00) TypeName_200E08(D_0024F340);
    }
    return &D_00278E00;
}

extern TypeName_200E08 D_00278E08;
extern const char D_0024F348[];

TypeName_200E08* func_00200E40(void)
{
    if (D_00278E08.name == 0) {
        new (&D_00278E08) TypeName_200E08(D_0024F348);
    }
    return &D_00278E08;
}

extern TypeName_200E08 D_00278E10;
extern const char D_0024F350[];

TypeName_200E08* func_00200E78(void)
{
    if (D_00278E10.name == 0) {
        new (&D_00278E10) TypeName_200E08(D_0024F350);
    }
    return &D_00278E10;
}

extern TypeName_200E08 D_00278E18;
extern const char D_0024F358[];

TypeName_200E08* func_00200EB0(void)
{
    if (D_00278E18.name == 0) {
        new (&D_00278E18) TypeName_200E08(D_0024F358);
    }
    return &D_00278E18;
}

extern TypeName_200E08 D_00278E20;
extern const char D_0024F360[];

TypeName_200E08* func_00200EE8(void)
{
    if (D_00278E20.name == 0) {
        new (&D_00278E20) TypeName_200E08(D_0024F360);
    }
    return &D_00278E20;
}

extern TypeName_200E08 D_00278E28;
extern const char D_0024F368[];

TypeName_200E08* func_00200F20(void)
{
    if (D_00278E28.name == 0) {
        new (&D_00278E28) TypeName_200E08(D_0024F368);
    }
    return &D_00278E28;
}

extern TypeName_200E08 D_00278E30;
extern const char D_0024F370[];

TypeName_200E08* func_00200F58(void)
{
    if (D_00278E30.name == 0) {
        new (&D_00278E30) TypeName_200E08(D_0024F370);
    }
    return &D_00278E30;
}

extern TypeName_200E08 D_00278E38;
extern const char D_0024F378[];

TypeName_200E08* func_00200F90(void)
{
    if (D_00278E38.name == 0) {
        new (&D_00278E38) TypeName_200E08(D_0024F378);
    }
    return &D_00278E38;
}

extern TypeName_200E08 D_00278E40;
extern const char D_0024F380[];

TypeName_200E08* func_00200FC8(void)
{
    if (D_00278E40.name == 0) {
        new (&D_00278E40) TypeName_200E08(D_0024F380);
    }
    return &D_00278E40;
}

extern TypeName_200E08 D_00278E48;
extern const char D_0024F388[];

TypeName_200E08* func_00201000(void)
{
    if (D_00278E48.name == 0) {
        new (&D_00278E48) TypeName_200E08(D_0024F388);
    }
    return &D_00278E48;
}

extern TypeName_200E08 D_00278E50;
extern const char D_0024F390[];

TypeName_200E08* func_00201038(void)
{
    if (D_00278E50.name == 0) {
        new (&D_00278E50) TypeName_200E08(D_0024F390);
    }
    return &D_00278E50;
}

extern TypeName_200E08 D_00278E58;
extern const char D_0024F398[];

TypeName_200E08* func_00201070(void)
{
    if (D_00278E58.name == 0) {
        new (&D_00278E58) TypeName_200E08(D_0024F398);
    }
    return &D_00278E58;
}

extern TypeName_200E08 D_00278E60;
extern const char D_0024F3A0[];

TypeName_200E08* func_002010A8(void)
{
    if (D_00278E60.name == 0) {
        new (&D_00278E60) TypeName_200E08(D_0024F3A0);
    }
    return &D_00278E60;
}

extern TypeName_200E08 D_00278E68;
extern const char D_0024F3A8[];

TypeName_200E08* func_002010E0(void)
{
    if (D_00278E68.name == 0) {
        new (&D_00278E68) TypeName_200E08(D_0024F3A8);
    }
    return &D_00278E68;
}

extern TypeName_200E08 D_00278E70;
extern const char D_0024F3B0[];

TypeName_200E08* func_00201118(void)
{
    if (D_00278E70.name == 0) {
        new (&D_00278E70) TypeName_200E08(D_0024F3B0);
    }
    return &D_00278E70;
}

extern TypeName_200E08 D_00278E78;
extern const char D_0024F3B8[];

TypeName_200E08* func_00201150(void)
{
    if (D_00278E78.name == 0) {
        new (&D_00278E78) TypeName_200E08(D_0024F3B8);
    }
    return &D_00278E78;
}

extern TypeName_200E08 D_00278E80;
extern const char D_0024F3C0[];

TypeName_200E08* func_00201188(void)
{
    if (D_00278E80.name == 0) {
        new (&D_00278E80) TypeName_200E08(D_0024F3C0);
    }
    return &D_00278E80;
}

// An EE DMA channel's register block (CHCR at 0x00, QWC at 0x20, TADR at 0x30; bit 8 of CHCR
// is STR), passed in by pointer: CHCR is a hardware register, read again at every use.
struct DmaChan_202A80 {
    volatile s32 chcr;
    u8 pad4[0x1C];
    s32 qwc;
    u8 pad24[0xC];
    u32 tadr;
};

extern "C" int func_001E1F10(const char* fmt, ...);

void func_00202A80(DmaChan_202A80* ch, u32 tadr)
{
    s32 timeout = 0x1000000;
    while (ch->chcr & 0x100) {
        if (--timeout < 0) {
            func_001E1F10("libdma: sync timeout\n");
            s32 cur = ch->chcr;
            s32 next;
            if (((u32)cur >> 8) & 1) {
                while (((u32)cur >> 8) & 1) {
                    next = cur & ~0x100;
                    cur = next;
                }
                ch->chcr = next;
            }
        }
    }
    if (ch->tadr != 0xFFFFFFFF) {
        ch->tadr = tadr;
    }
    ch->qwc = 0;
    ch->chcr = (ch->chcr & ~0xC) | 0x105;
}

// The EE DMA channel's register block (CHCR at 0x00, QWC at 0x20; bit 8 of CHCR is STR),
// passed in by pointer: volatile as a hardware register, which retail re-reads at every use.
struct DmaChan_202B68 {
    volatile s32 chcr;
    u8 pad4[0x1C];
    s32 qwc;
};

extern "C" int func_001E1F10(const char* fmt, ...);

void func_00202B68(DmaChan_202B68* ch)
{
    s32 timeout = 0x1000000;
    while (ch->chcr & 0x100) {
        if (--timeout < 0) {
            func_001E1F10("libdma: sync timeout\n");
            s32 cur = ch->chcr;
            s32 next;
            if (((u32)cur >> 8) & 1) {
                while (((u32)cur >> 8) & 1) {
                    next = cur & ~0x100;
                    cur = next;
                }
                ch->chcr = next;
            }
        }
    }
    ch->qwc = 0;
    ch->chcr = ((((ch->chcr & ~0xC) | 0x4) & ~0x1) | 0x100);
}

// The EE DMA channel's register block (CHCR at 0x00; bit 8 of CHCR is STR), passed in by
// pointer: volatile as a hardware register, which retail re-reads at every use.
struct DmaChan_202C38 {
    volatile s32 chcr;
};

extern "C" int func_001E1F10(const char* fmt, ...);

s32 func_00202C38(DmaChan_202C38* ch, s32 mode, s32 timeout)
{
    if (mode == 1) {
        return ((u32)ch->chcr >> 8) & 1;
    }
    if (timeout == 0) {
        timeout = 0x1000000;
    }
    while (ch->chcr & 0x100) {
        if (--timeout < 0) {
            func_001E1F10("libdma: sync timeout\n");
            s32 cur = ch->chcr;
            s32 next;
            if (((u32)cur >> 8) & 1) {
                while (((u32)cur >> 8) & 1) {
                    next = cur & ~0x100;
                    cur = next;
                }
                ch->chcr = next;
            }
        }
    }
    return 0;
}

struct Pkt_202E50 {
    s32 n0;
    s32 n1;
    u8* dst0;
    u8* dst1;
    u8 src0[0x40];
    u8 src1[0x40];
};

extern s32 D_00279454;
void func_00202DA0(s32* code);

void func_00202E50(Pkt_202E50* p) {
    Pkt_202E50* q = (Pkt_202E50*)((u32)p | 0x20000000);
    if (q->n0 > 0) {
        u8* d = q->dst0;
        for (s32 i = 0; i < q->n0; i++) {
            d[i] = q->src0[i];
        }
    }
    if (q->n1 > 0) {
        u8* d = q->dst1;
        for (s32 i = 0; i < q->n1; i++) {
            d[i] = q->src1[i];
        }
    }
    func_00202DA0(&D_00279454);
}

extern void (*D_0062A7C4)(s32);
extern s32 D_0062A7C8;
extern s32 D_00279424;

void func_00203010(void) {
    if (D_0062A7C4 && !D_00279424) {
        D_0062A7C4(D_0062A7C8);
    }
}

s32 func_00201668(s32 value);
void func_001000B8(s32 value);

void func_002014D0(void)
{
    for (;;) {
        func_00201668(6);
        func_001000B8(1);
    }
}

extern s32 D_00279414;
extern s32 D_00279454;
extern s32 D_00279420;
extern s32 D_00279428;
extern s32 D_0027942C;

s32 func_001F6B30(s32 a);
s32 func_001F9D60(void);
s32 func_001FA4D0(u32 a);
s32 func_001F9DA8(void);

void func_00202F88(void) {
    if (D_00279414) {
        // A bare do/while(0), allowed for this function alone by the project's decision: retail stores
        // -1 here before loading D_00279420, and only this keeps the compiler from moving the load first.
        do { D_00279454 = -1; } while (0);
        func_001F6B40(D_00279420);
    }
    func_001F6B30(D_00279428);
    func_001F6B30(D_0027942C);
    func_001F6B30(D_00279420);
    func_001F9D60();
    func_001FA4D0(0x80000012);
    func_001F9DA8();
}

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
extern const Fn_Table D_0024F3C8[4] = { 0, (Fn_Table)func_002011C0, 0, (Fn_Table)func_00201210 };
extern const Fn_Table D_0024F3D8[4] = { 0, (Fn_Table)func_00201230, 0, (Fn_Table)func_00201280 };
extern const Fn_Table D_0024F3E8[4] = { 0, (Fn_Table)func_002012A0, 0, (Fn_Table)func_002012F0 };
extern const Fn_Table D_0024F3F8[4] = { 0, (Fn_Table)func_00201310, 0, (Fn_Table)func_00201360 };
extern const Fn_Table D_0024F418[4] = { 0, (Fn_Table)func_002013F0, 0, (Fn_Table)func_00201440 };
extern const Fn_Table D_0024F428[4] = { 0, (Fn_Table)(void* (*)(struct Self_00201460* a0))func_00201460, 0, (Fn_Table)func_002014B0 };

struct Obj_202098 { u8 pad0[0x20]; u64 out; u8 pad1[0x8]; u64 in; };

void func_00202098(struct Obj_202098* self, s16 a1, s16 a2, s16 a3)
{
    u64 v = self->in;
    s64 y = (u64)((s32)((v >> 48) & 0x7FF) + 1) >> 1;
    s64 b2 = a2;
    s64 b1 = a1;
    s64 x = (u64)((s32)((v >> 16) & 0x7FF) + 1) >> 1;
    b2 -= y;
    b1 -= x;
    s64 t = b2 << 4;
    u64 lo = b1 << 4;
    u64 hi;
    if (a3 != 0) {
        hi = (u64)(t + 8) << 32;
    } else {
        hi = (u64)t << 32;
    }
    self->out = lo | hi;
}
