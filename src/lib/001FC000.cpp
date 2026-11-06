// SPDX-License-Identifier: AGPL-3.0-or-later
// The runtime's exception classes keep their vtables where retail has them (config/us/libcalls.tsv):
// with `#pragma interface` the compiler refers to them by name instead of writing its own.
#pragma interface
#include "common.h"

// SPDX-License-Identifier: AGPL-3.0-or-later

#include "common.h"

void func_001FD988() {}

s16 func_001FDDC8(void* object)
{
	return *(s16*)((u8*)object + 6);
}

s16 func_001FDDD0(void* object)
{
	return *(s16*)((u8*)object + 4);
}

void func_001FE190() {}

u8* func_001FF048(u8* input, u32* output)
{
	u8 byte = *input;
	u32 shift = 0;
	input++;
	u32 value = byte & 0x7F;
	if (byte & 0x80) {
		do {
			byte = *input;
			shift += 7;
			input++;
			value |= (byte & 0x7F) << shift;
		} while (byte & 0x80);
	}
	*output = value;
	return input;
}

void* func_001FFFE0(void* a0, void* a1) { return a1; }

void* func_001FFFE8(void* a0, void* a1) { return a1; }

u8* func_001FF090(u8* input, s32* output)
{
    u32 shift = 0;
    u32 value = 0;
    u8 byte;

    do {
        byte = *input++;
        value |= (u32)(byte & 0x7F) << shift;
        shift += 7;
    } while (byte & 0x80);

    if (shift < 32) {
        s32 signMask = -1;
        if (byte & 0x40) {
            value |= signMask << shift;
        }
    }
    *output = (s32)value;
    return input;
}

extern s32 D_00278640;

s32 func_001FE928(s32 value)
{
    s32 previous = D_00278640;
    D_00278640 = value;
    return previous;
}

struct Node_1FFBE0 { s32 first; s32 second; s32 value; s32 link; s32 flag; Node_1FFBE0* previous; };
extern Node_1FFBE0* D_0062A7B8;

void func_001FFBE0(s32 value, Node_1FFBE0* item)
{
    item->value = value;
    item->second = 0;
    item->first = 0;
    item->flag = 0;
    item->link = value;
    item->previous = D_0062A7B8;
    D_0062A7B8 = item;
}

s32 D_002789D8;

s32 func_001FFFD0(s32 value)
{
    s32 previous = D_002789D8;
    D_002789D8 = value;
    return previous;
}

struct Cur_1FF490 { s32 off; s32 f4; s32 f8; s32 fC; };
struct List_1FF490 { Cur_1FF490** items; s32 count; };

void func_001FF490(Cur_1FF490* cur, List_1FF490* list, s32* lo, s32* hi)
{
    s32 mn = *lo;
    s32 mx = *hi;
    if (cur->off != 0) {
        do {
            if (cur->f4 == 0) goto next;
            if (cur->f8 == 0) goto next;
            {
                list->items[list->count++] = cur;
                {
                    s32 x = cur->f8;
                    s32 e = x + cur->fC;
                    if ((u32)x < (u32)mn) mn = x;
                    if ((u32)mx < (u32)e) mx = e;
                }
            }
        next:
            cur = (Cur_1FF490*)((u8*)cur + cur->off + 4);
        } while (cur->off != 0);
    }
    *lo = mn;
    *hi = mx;
}

struct Src_1FD6E0 {
    u32 bits;
};

struct Parts_1FD6E0 {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
};

void func_001FD6E0(struct Src_1FD6E0* src, struct Parts_1FD6E0* out)
{
    u32 bits = src->bits;
    u32 exp = bits >> 23;
    u32 mant = bits & 0x7FFFFF;
    exp &= 0xFF;

    out->f04 = bits >> 31;
    if (exp == 0) {
        out->f00 = 2;
        return;
    }
    if (exp == 0xFF) {
        if (mant == 0) {
            out->f00 = 4;
            return;
        }
        if ((mant & 0x100000) != 0) {
            out->f00 = 1;
        } else {
            out->f00 = 0;
        }
        out->f0C = mant;
        return;
    }
    out->f08 = exp - 0x7F;
    out->f00 = 3;
    out->f0C = (mant << 7) | 0x40000000;
}

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_0024F0C0[];

void* func_001FEF58(void* self)
{
    *(void**)self = ((u8*)D_0024F0C0);
    return self;
}

extern u8 D_0024F0D8[];

void* func_001FEFF0(void* self)
{
    *(void**)self = D_0024F0D8;
    return self;
}

void func_00200000(void);
void func_00200050(void);
void* func_001FFFF0(void);
struct VEnt_24F1E0 { s32 delta; void (*fn)(); };
struct Bad_24F1E0 { char name[24]; VEnt_24F1E0 vt[3]; };
extern const Bad_24F1E0 D_0024F1E0;

void* func_001FFFF0(void)
{
    return (void*)&D_0024F1E0;
}

// NEAR: retail saves $ra and $s0 with sd (8 bytes), not sq, and computes the third call argument earlier; retail is in the double-precision range that docs/TOOLCHAIN.md says is built by Sony 2.9-ee-991111, not SN GCC.

struct Blob_1FCD20 {
    u8 pad0[0x20];
};

struct Key_1FCD20 {
    s64 v;
};

void func_001FCA40(Key_1FCD20* key, Blob_1FCD20* out);
Blob_1FCD20* func_001FCAE0(Blob_1FCD20* a, Blob_1FCD20* b, Blob_1FCD20* c);
s32 func_001FC910(void* p);

s32 func_001FCD20(s64 pa, s64 pb)
{
    Blob_1FCD20 a;
    Blob_1FCD20 b;
    Blob_1FCD20 c;

    func_001FCA40((Key_1FCD20*)&pa, &a);
    func_001FCA40((Key_1FCD20*)&pb, &b);
    return func_001FC910(func_001FCAE0(&a, &b, &c));
}

// NEAR: the 8-byte register saves (sd) and the tail of the call sequence are the Sony 2.9-ee-991111 shape of the lib float range (docs/TOOLCHAIN.md); under the SN build the prologue and the call order differ. Not landable with the default compiler.

struct Cell_1FCD78 { s32 f0; s32 f4; s32 f8; s32 fC; s32 f10; s32 f14; s32 f18; s32 f1C; };
struct Frame_1FCD78 { Cell_1FCD78 c0; Cell_1FCD78 c20; Cell_1FCD78 c40; u64 a; u64 b; };

void func_001FCA40(Cell_1FCD78* dst, void* src);
s32 func_001FCAE0(Cell_1FCD78* a, void* b, void* c);
void func_001FC910(Cell_1FCD78* v);

void func_001FCD78(u64 a0, u64 a1)
{
    Frame_1FCD78 f;
    f.a = a0;
    f.b = a1;
    func_001FCA40((Cell_1FCD78*)&f.a, &f.c0);
    func_001FCA40((Cell_1FCD78*)&f.b, &f.c20);
    f.c20.f4 ^= 1;
    func_001FC910((Cell_1FCD78*)(u32)func_001FCAE0(&f.c0, &f.c20, &f.c40));
}

// NEAR: retail saves s0/ra with sd/ld in a different order (8-byte, Sony 2.9-ee-991111 pattern); calls and frame match.

struct __attribute__((aligned(8))) Pair_001FD308 { s32 a; s32 b; };
struct Out_001FD308 { s32 w[8]; };
struct Frame_001FD308 { Out_001FD308 o0; Out_001FD308 o1; Pair_001FD308 a; Pair_001FD308 b; };

void func_001FCA40(Pair_001FD308* in, Out_001FD308* out);
s32 func_001FD1F0(Out_001FD308* a, Out_001FD308* b);

void func_001FD308(Pair_001FD308 a, Pair_001FD308 b)
{
    Frame_001FD308 f;
    f.a = a;
    f.b = b;
    func_001FCA40(&f.a, &f.o0);
    func_001FCA40(&f.b, &f.o1);
    func_001FD1F0(&f.o0, &f.o1);
}

struct Args_1FD548 {
    s32 a0;
    s32 a1;
    s32 a2;
    s64 a3;
};

s32 func_001FC910(Args_1FD548* args);

s32 func_001FD548(s32 a0, s32 a1, s32 a2, s32 a3)
{
    Args_1FD548 args;
    args.a0 = a0;
    args.a1 = a1;
    args.a2 = a2;
    args.a3 = a3;
    return func_001FC910(&args);
}

struct Args_1FD838 {
    s32 a0;
    s32 a1;
    s32 a2;
    s32 a3;
};

s32 func_001FD5D0(Args_1FD838* args);

s32 func_001FD838(s32 a0, s32 a1, s32 a2, s32 a3)
{
    Args_1FD838 args;
    args.a0 = a0;
    args.a1 = a1;
    args.a2 = a2;
    args.a3 = a3;
    return func_001FD5D0(&args);
}

// NEAR: retail saves $ra with sd (Sony 2.9-ee-991111 library code, 0x1F59C4 on); the default compiler saves it with sq. Nothing else differs.

extern void (*D_00278048)();

void func_001FD930() { D_00278048(); }

struct Obj_1FD958;
s32 func_001F6738(Obj_1FD958* self, s32 v);

s32 func_001FD958(Obj_1FD958* self, s32 v, s32 fallback)
{
    s32 result = fallback;
    if (func_001F6738(self, v) != 0) {
        result = 0;
    }
    return result;
}

// NEAR: ra is saved with sq/lq, retail sd/ld (Sony 2.9-ee-991111 lib build); body otherwise EXACT

extern void* D_0027804C;

u8* func_001FDA10(void)
{
    return ((u8* (*)(void))D_0027804C)() + 8;
}

// NEAR: ra is saved with sq/lq, retail sd/ld (Sony 2.9-ee-991111 lib build); body otherwise EXACT

extern void* D_0027804C;

u8* func_001FDAC8(void)
{
    return ((u8* (*)(void))D_0027804C)() + 4;
}

// NEAR: retail saves $ra with sd, default compiler with sq; body identical
struct Ctx_001FE978;
void* func_001FDA10(Ctx_001FE978* self);

s32 func_001FE978(Ctx_001FE978* self)
{
	return *(s32*)func_001FDA10(self);
}

// NEAR: default 2.95.3 saves $ra with sq/lq where retail has sd/ld; EXACT with SLY1_COMPILER=2.9-ee-991111

struct Obj_001FE998 {
    u8 pad[0x14];
    s32 flag;
    u8 pad2[8];
    s64 count;
};


Obj_001FE998* func_001FE998(void)
{
    Obj_001FE998* obj = *(Obj_001FE998**)func_001FDA10();
    obj->flag = 1;
    obj->count++;
    return obj;
}

// NEAR: retail saves s0..s3 and ra with 8-byte sd/ld (the default compiler: 16-byte sq/lq); and retail stores the function pointer at +0 before the two halfword stores, and computes its address before the `li v1,1`, where ours keeps the halfword stores first. Otherwise identical

struct Size_1FEA88;
struct Fn_1FEA88;

struct Obj_1FEA88 {
    void* f00;
    u16 f04;
    u16 f06;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    u64 f20;
    s32 f28;
};

struct Obj_1FEA88* func_001FE9D0(struct Size_1FEA88* n);
s32 func_001FEA18(struct Fn_1FEA88* self);

void func_001FEA88(s32 a0, s32 a1, s32 a2)
{
    struct Obj_1FEA88* obj = func_001FE9D0((struct Size_1FEA88*)0x30);
    obj->f0C = a1;
    obj->f10 = a2;
    obj->f08 = a0;
    obj->f28 = a0;
    obj->f20 = 0;
    obj->f14 = 0;
    obj->f00 = (void*)func_001FEA18;
    obj->f04 = 4;
    obj->f06 = 1;
    s32* p = (s32*)func_001FDA10();
    obj->f18 = *p;
    *p = (s32)obj;
}

// NEAR: retail is library code (0x1F59C4 onward, Sony's 2.9-ee-991111) and saves $ra with sd, 8 bytes; the default compiler saves it with sq, 16 bytes. The body matches.

struct Obj_1FEEC8 { u8 pad[0x14]; s32 count; };
struct Slot_1FEEC8 { Obj_1FEEC8* obj; };


s32 func_001FEEC8(void)
{
    Obj_1FEEC8* obj = ((Slot_1FEEC8*)func_001FDA10())->obj;
    s32 result = 0;
    if (obj != 0) {
        result = obj->count == 0;
    }
    return result;
}

// NEAR: ra is saved with sq/lq, retail sd/ld (Sony 2.9-ee-991111 lib build); body otherwise EXACT

struct Obj_001FEF00;

struct Vtbl_001FEF00 {
    void* slot0;
    void* (*slot1)(Obj_001FEF00* self);
};

struct Obj_001FEF00 {
    Vtbl_001FEF00* vtbl;
};

s32 func_001FEF00(Obj_001FEF00* self)
{
    return *(s32*)self->vtbl->slot1(self);
}

// NEAR: only the $ra and $s0 saves differ: retail sd/ld, ours sq/lq

extern u8 D_0062C5A8[];
extern const char D_0024F0F0[16];
extern u8 D_0027B318[];

struct Node_1FEF70 {
    void *field0;
};

void func_00200118(struct Node_1FEF70 *self, void *a1, void *a2);

void* func_001FF008(void);
void* func_001FEF70(void) {
    struct Node_1FEF70 *node = (struct Node_1FEF70 *)D_0062C5A8;
    if (node->field0 == 0) {
        func_001FF008();
        func_00200118(node, (void*)D_0024F0F0, D_0027B318);
    }
    return node;
}

// NEAR: only the s0 and ra saves differ: retail saves ra and s0 with sd (8 bytes), the SN builds with sq; the 8-byte save is the Sony 2.9-ee-991111 form (docs/TOOLCHAIN.md), not used here.

extern u8 D_0027B318[];
extern const char D_0024F100[16];

struct Node_1FF008 {
    void *field0;
    void *vtbl;
};

void func_00200138(struct Node_1FF008 *self, void *value);

void *func_001FF008(void) {
    struct Node_1FF008 *node = (struct Node_1FF008 *)D_0027B318;
    if (*(void **)D_0027B318 == 0) {
        func_00200138(node, (void*)D_0024F100);
    }
    return node;
}

struct Out_001FD410 {
    s32 kind;
    s32 sign;
    s32 exp;
    s32 pad;
    u64 mant;
};

void func_001FCA40(u64* in, Out_001FD410* out);

s32 func_001FD410(u64 value)
{
    u64 in = value;
    Out_001FD410 out;
    s32 v;

    func_001FCA40(&in, &out);
    if ((out.kind ^ 2) == 0) {
        return 0;
    }
    if ((u32)out.kind < 2) {
        return 0;
    }
    if ((out.kind ^ 4) == 0) {
        goto saturate;
    }
    if (out.exp < 0) {
        return 0;
    }
    if (out.exp < 0x1F) {
        goto compute;
    }
saturate:
    return (out.sign != 0) ? (s32)0x80000000 : 0x7FFFFFFF;
compute:
    v = (s32)(out.mant >> (0x3C - out.exp));
    if (out.sign != 0) {
        v = -v;
    }
    return v;
}

struct FloatIn_1FD7A0 { f32 value; };
struct FloatParts_1FD7A0 { u32 kind; s32 sign; s32 exp; u32 mant; };
void func_001FD6E0(FloatIn_1FD7A0* in, FloatParts_1FD7A0* out);

u32 func_001FD7A0(f32 value)
{
    f32 in = value;
    FloatParts_1FD7A0 p;
    func_001FD6E0((FloatIn_1FD7A0*)&in, &p);
    if ((p.kind ^ 2) == 0) {
        return 0;
    }
    if (p.kind < 2) {
        return 0;
    }
    if (p.sign != 0) {
        return 0;
    }
    if ((p.kind ^ 4) == 0) {
        return 0xFFFFFFFFu;
    }
    if (p.exp < 0) {
        return 0;
    }
    if (p.exp >= 0x20) {
        return 0xFFFFFFFFu;
    }
    if (p.exp >= 0x1F) {
        return p.mant << (p.exp - 0x1E);
    }
    return p.mant >> (0x1E - p.exp);
}

typedef s32 (*FnPtr_001FD9E8)(void);

s32 func_001FD9E8(void)
{
    return (*(FnPtr_001FD9E8*)&D_0027804C)();
}

typedef void (*Fn_1FDA38)(void);
struct Once_1FDA60;
Once_1FDA60* func_001FDA60(void);

void func_001FDA38(void)
{
    Fn_1FDA38 f = (Fn_1FDA38)func_001FDA60;
    (*(Fn_1FDA38*)&D_0027804C) = f;
    f();
}

struct Once_1FDA60 { s32 a; void* b; };

extern s32 D_0062A7A8;
extern Once_1FDA60 D_0062A798;
extern u8 D_0062A7B0[];

s32 func_001F5C0C(Once_1FDA60* p, s32 v, s32 n);

Once_1FDA60* func_001FDA60(void)
{
    if (D_0062A7A8 == 0) {
        D_0062A7A8 = 1;
        (void)func_001F5C0C(&D_0062A798, 0, 0x10);
        D_0062A798.b = D_0062A7B0;
    }
    return &D_0062A798;
}

struct Ctx_001FE100 { s32 f0; u8 pad4[4]; s32 f8; u8 padC[0x298 - 0xC]; u16 f298; u8 pad29A[2]; s8 f29C; };

Ctx_001FE100* func_001FFC80(Ctx_001FE100* ctx, s32 a2);
void* func_001FDFF8(u16 idx, s32* base, s32 flag);

Ctx_001FE100* func_001FE100(Ctx_001FE100* a0, s32* a1, s32 a2)
{
    Ctx_001FE100* s0 = func_001FFC80(a0, a2);
    if (s0 == 0) {
        return 0;
    }
    u16 idx = s0->f298;
    if (*(s8*)((u8*)a1 + idx + 0x29C) != 0) {
        s64 v = *(s64*)func_001FDFF8(idx, a1, 0);
        s0->f0 = (s32)v;
    } else {
        s0->f0 = *a1;
    }
    s0->f0 += s0->f8;
    return s0;
}

s32 func_0018D750(void);

s32 func_001FE9F8(void)
{
    return func_0018D750();
}

struct Obj_001FEF28 { u8* f0; };

s32 func_0018D778(Obj_001FEF28* self);
extern u8 D_0024F0D8[];

u8* func_001FEF28(Obj_001FEF28* self, s32 flag)
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

s32 func_001FEFC0(void* self, s32 flags)
{
    void* v = D_0024F0D8;
    *(void**)self = v;
    if (flags & 1) {
        return func_0018D778(self);
    }
    return (s32)v;
}

struct Node_001FD990 { s32 f0; u8* f4; s32 f8; s32 fc; s32 f10; s32 f14; };

Node_001FD990* func_0018D740(s32 size);
void func_001FD930(void);
void* func_001F5C0C(Node_001FD990* p, s32 value, u32 size);

Node_001FD990* func_001FD990(void)
{
    Node_001FD990* p = (Node_001FD990*)func_0018D740(0x18);
    if (p == 0) {
        func_001FD930();
    }
    (void)func_001F5C0C(p, 0, 0x18);
    p->f4 = (u8*)p + 0x10;
    return p;
}

struct Range_1FDDD8 { u32 lo; u32 hi; s32 value; };

s32 func_001FDDD8(u32 key, Range_1FDDD8* t)
{
    s32 best, i;
    if (t == 0) goto none;
    best = -1;
    i = 0;
    if (t[0].lo == 0xFFFFFFFF) goto check;
    do {
        if (key >= t[i].lo && key < t[i].hi) {
            if (best == -1 || (t[best].hi >= t[i].hi && t[best].lo <= t[i].lo)) best = i;
        } else if (best >= 0 && key < t[i].lo) {
            break;
        }
        i++;
    } while (t[i].lo != 0xFFFFFFFF);
check:
    if (best == -1) goto none;
    return t[best].value;
none:
    return 0;
}

struct Arg_1FE080 { u8 pad[4]; };
struct Dst_1FE080 { u8 pad[4]; };

extern u32 func_001FDFF8(Arg_1FE080* a, u32 b, s32 c);
extern s32 func_001F5A58(Dst_1FE080* dst, Arg_1FE080* src, s32 n);

s32 func_001FE080(s32 a0, u32 a1, u32 a2)
{
    u32 r1 = func_001FDFF8((Arg_1FE080*)a0, a1, 0);
    u32 r2 = func_001FDFF8((Arg_1FE080*)a0, a2, 0);
    s32 n;
    if (a0 >= 0x1F) {
        n = 8;
        if (!(0x3F < a0)) {
            n = 4;
        }
    } else {
        n = 16;
    }
    return func_001F5A58((Dst_1FE080*)r2, (Arg_1FE080*)r1, n);
}

// NEAR: retail saves with sd/ld (ours sq/lq); jalr's delay slot is a nop in retail, ours moves a0 there

struct Node_001FEA18 {
    u8 pad0[8];
    s32 f8;
    s32 fC;
    u8 pad1[0x18];
    s32 f28;
};

struct Hdr_001FEA18 {
    u8 pad0[4];
    s16 kind;
};

struct Res_001FEA18;

typedef s32 (*Fn_001FEA18)();

s32 func_00200778(Res_001FEA18* a, s32 b, s32 c);

s32 func_001FEA18(Node_001FEA18* self, void* fn, Hdr_001FEA18* a2)
{
    if (a2 != 0 && a2->kind != 4) {
        return 0;
    }
    if (fn == (void*)-1) {
        return self->f8;
    }
    s32 r = ((Fn_001FEA18)fn)();
    r = func_00200778((Res_001FEA18*)r, self->fC, self->f28);
    if (r != 0) {
        self->f8 = r;
    }
    return r;
}

struct Node_1FEBE0 { u8 pad[0x14]; s32 flag; };
struct Head_1FEBE0 { Node_1FEBE0* node; };

extern void func_001FE8F0(void) __attribute__((noreturn));

void func_001FEBE0(void)
{
    Node_1FEBE0* n = ((Head_1FEBE0*)func_001FDA10())->node;
    if (n == 0)
        func_001FE8F0();
    n->flag = 0;
}

struct Chain_1FF448 { s32 next; s32 a; s32 b; };
s32 func_001FF448(Chain_1FF448* p)
{
    s32 n = 0;
    s32 off = p->next;
    s32 nx;
    if (off != 0) {
        goto body;
        for (;;) {
            off = nx;
        body:
            if (p->a != 0 && p->b != 0) n++;
            p = (Chain_1FF448*)((u8*)p + off + 4);
            nx = p->next;
            if (nx == 0) break;
        }
    }
    return n;
}

struct Cmp_1FD1F0 {
    s32 tag;
    s32 ptr;
    s32 f8;
    s32 padC;
    u64 f10;
};

s32 func_001FD1F0(Cmp_1FD1F0* a, Cmp_1FD1F0* b)
{
    if ((u32)a->tag < 2) {
        return 1;
    }
    if ((u32)b->tag < 2) {
        return 1;
    }
    if ((a->tag ^ 4) == 0) {
        if ((b->tag ^ 4) == 0) {
            return b->ptr - a->ptr;
        }
        return a->ptr != 0 ? -1 : 1;
    }
    if ((b->tag ^ 4) == 0) {
        return b->ptr != 0 ? 1 : -1;
    }
    if ((a->tag ^ 2) == 0) {
        if ((b->tag ^ 2) == 0) {
            return 0;
        }
        return b->ptr == 0 ? -1 : 1;
    }
    if ((b->tag ^ 2) == 0) {
        return a->ptr != 0 ? -1 : 1;
    }
    if (a->ptr != b->ptr) {
        return a->ptr != 0 ? -1 : 1;
    }
    if (a->f8 > b->f8) {
        return a->ptr != 0 ? -1 : 1;
    }
    if (a->f8 < b->f8) {
        return a->ptr != 0 ? 1 : -1;
    }
    if (a->f10 > b->f10) {
        return a->ptr != 0 ? -1 : 1;
    }
    if (a->f10 < b->f10) {
        return a->ptr != 0 ? 1 : -1;
    }
    return 0;
}

struct Parts_1FD358 {
    u32 kind;
    u32 sign;
    s32 exponent;
    u32 pad;
    u64 mantissa;
    u32 tail[2];
};

u64 func_001FC910(Parts_1FD358* p);

u64 func_001FD358(s32 value)
{
    Parts_1FD358 parts;
    parts.kind = 3;
    parts.sign = (u32)value >> 31;
    if (value == 0) {
        parts.kind = 2;
    } else {
        parts.exponent = 0x3C;
        if (parts.sign != 0) {
            if (value == (s32)0x80000000) {
                return 0xC1E0000000000000ULL;
            }
            parts.mantissa = (s32)-value;
        } else {
            parts.mantissa = value;
        }
        u64 m = parts.mantissa;
        if (m <= 0x0FFFFFFFFFFFFFFFULL) {
            s32 e = parts.exponent;
            u64 n;
            do {
                n = m << 1;
                e--;
                m = n;
            } while (n <= 0x0FFFFFFFFFFFFFFFULL);
            parts.exponent = e;
            parts.mantissa = m;
        }
    }
    return func_001FC910(&parts);
}

// EXACT: u32 return (-1 as lui/ori) and (kind ^ N) == 0 compares give retail xori/beqz.

struct Double_001FD4A8 {
    u32 kind;          // 0x00
    s32 sign;          // 0x04
    s32 exponent;      // 0x08
    u8 pad_0C[4];      // 0x0C
    u64 mantissa;      // 0x10
};

struct Bits_001FD4A8 {
    u64 v;             // 0x00
};

void func_001FCA40(Bits_001FD4A8* src, Double_001FD4A8* out);

u32 func_001FD4A8(u64 value)
{
    Double_001FD4A8 d;
    Bits_001FD4A8 b;
    b.v = value;
    func_001FCA40(&b, &d);
    if ((d.kind ^ 2) == 0) {
        return 0;
    }
    if ((u32)d.kind < 2) {
        return 0;
    }
    if (d.sign != 0) {
        return 0;
    }
    if ((d.kind ^ 4) == 0) {
        return 0xFFFFFFFF;
    }
    if (d.exponent < 0) {
        return 0;
    }
    if (d.exponent >= 0x20) {
        return 0xFFFFFFFF;
    }
    s32 e = d.exponent;
    if (e >= 0x3D) {
        return (u32)(d.mantissa << (e - 0x3C));
    }
    return (u32)(d.mantissa >> (0x3C - e));
}

// EXACT: func_001FF1E0 takes (acc, count) so count lives in s4; f0 stored before f4.

struct Obj_1FF518 { s32 f0; s32 f4; s32 f8; s32* f0C; s32 f10; };
struct Acc_1FF518 { s32* items; s32 count; s32* other; s32 unused; u32 lo; s32 hi; };
struct Cur_1FF518 { s32 pad[1]; };

s32 func_001FF448(Cur_1FF518* cur);
void func_001FF490(Cur_1FF518* cur, Acc_1FF518* list, u32* lo, s32* hi);
s32 func_001FF1E0(Acc_1FF518* acc, s32 n);

void func_001FF518(Obj_1FF518* self)
{
    s32 count;
    s32* p;
    Acc_1FF518 acc;

    if (self->f0C != 0) {
        p = self->f0C;
        count = 0;
        if (*p != 0) {
            do {
                count += func_001FF448((Cur_1FF518*)*p);
                p++;
            } while (*p != 0);
        }
    } else {
        count = func_001FF448((Cur_1FF518*)self->f8);
    }
    self->f10 = count;
    acc.items = (s32*)func_0018D740(count << 2);
    acc.other = (s32*)func_0018D740(count << 2);
    acc.lo = 0xFFFFFFFF;
    acc.count = 0;
    acc.unused = 0;
    acc.hi = 0;
    if (self->f0C != 0) {
        p = self->f0C;
        if (*p != 0) {
            do {
                func_001FF490((Cur_1FF518*)*p, &acc, &acc.lo, &acc.hi);
                p++;
            } while (*p != 0);
        }
    } else {
        func_001FF490((Cur_1FF518*)self->f8, &acc, &acc.lo, &acc.hi);
    }
    self->f0C = (s32*)func_001FF1E0(&acc, count);
    self->f0 = acc.lo;
    self->f4 = acc.hi;
}

struct Cie_1FF740;

struct Fde_1FF740 {
    s32 length;
    s32 cieOffset;
    Cie_1FF740* Cie()
    {
        return (Cie_1FF740*)((char*)&cieOffset - cieOffset);
    }
};

struct Cie_1FF740 {
    s32 length;
    s32 id;
    s8 version;
    char augmentation[1];
};

struct __attribute__((packed)) Unaligned_1FF740 {
    s32 v;
};

struct Info_1FF740 {
    char *augmentation;
    s32 ehPtr;
    s32 codeAlign;
    s32 dataAlign;
    s32 raReg;
};

s32 func_001F6738(const char *a, const char *b);
s32 func_001E2100(const char *s);
u8 *func_001FF048(u8 *p, s32 *out);
u8 *func_001FF090(u8 *p, s32 *out);

u8 *func_001FF740(struct Fde_1FF740 *fde, struct Info_1FF740 *info) {
    struct Cie_1FF740 *cie = fde->Cie();
    u8 *p;
    s32 len;

    info->augmentation = cie->augmentation;
    if (func_001F6738(cie->augmentation, "") != 0 &&
        func_001F6738(info->augmentation, "eh") != 0 &&
        info->augmentation[0] != 'z') {
        return 0;
    }
    p = (u8 *)info->augmentation + GetStringLength(info->augmentation) + 1;
    if (func_001F6738(info->augmentation, "eh") == 0) {
        info->ehPtr = ((struct Unaligned_1FF740 *)p)->v;
        p += 4;
    } else {
        info->ehPtr = 0;
    }
    p = func_001FF048(p, &info->codeAlign);
    p = func_001FF090(p, &info->dataAlign);
    info->raReg = *p++;
    if (info->augmentation[0] == 'z') {
        p = func_001FF048(p, &len);
        p += len;
    }
    return p;
}

struct RuleSet_1FF848 {
    u8 pad0[8];
    s64 cfaOffset;
    s64 cfaReg;
    s64 value[0x50];
    u16 retColumn;
    u8 pad29A[2];
    u8 how[0x54];
    struct RuleSet_1FF848 *saved;
    u8 pad2F4[4];
};

struct Cie_1FF848 {
    u8 pad0[8];
    s32 codeAlign;
    s32 dataAlign;
};

struct __attribute__((packed)) U16_1FF848 {
    u16 v;
};

struct __attribute__((packed)) U32_1FF848 {
    u32 v;
};

u8 *func_001FF048(u8 *p, u32 *out);
void func_002014D0(void);
struct RuleSet_1FF848 *func_0018D740(u32 size);
void func_0018D750(struct RuleSet_1FF848 *p);

u8 *func_001FF848(u8 *p, struct RuleSet_1FF848 *rs, struct Cie_1FF848 *cie, u32 *pc) {
    s32 offset;
    u32 reg;
    u32 reg2;
    u8 op = *p++;

    if (op & 0x40) {
        *pc += (op & 0x3F) * cie->codeAlign;
    } else if (op & 0x80) {
        reg = op & 0x3F;
        p = func_001FF048(p, (u32 *)&offset);
        offset *= cie->dataAlign;
        rs->how[reg] = 1;
        rs->value[reg] = offset;
    } else if (op & 0xC0) {
        reg = op & 0x3F;
        rs->how[reg] = 0;
    } else {
        switch (op) {
        case 0:
            break;
        case 1:
            *pc = ((struct U32_1FF848 *)p)->v;
            p += 4;
            break;
        case 2:
            *pc += *p;
            p += 1;
            break;
        case 3:
            *pc += ((struct U16_1FF848 *)p)->v;
            p += 2;
            break;
        case 4:
            *pc += ((struct U32_1FF848 *)p)->v;
            p += 4;
            break;
        case 5:
            p = func_001FF048(p, &reg);
            p = func_001FF048(p, (u32 *)&offset);
            offset *= cie->dataAlign;
            rs->how[reg] = 1;
            rs->value[reg] = offset;
            break;
        case 6:
            p = func_001FF048(p, &reg);
            rs->how[reg] = 0;
            break;
        case 7:
        case 8:
            break;
        case 9:
            p = func_001FF048(p, &reg);
            p = func_001FF048(p, &reg2);
            rs->how[reg] = 2;
            rs->value[reg] = reg2;
            break;
        case 12:
            p = func_001FF048(p, &reg);
            p = func_001FF048(p, (u32 *)&offset);
            rs->retColumn = reg;
            rs->cfaOffset = offset;
            break;
        case 13:
            p = func_001FF048(p, &reg);
            rs->retColumn = reg;
            break;
        case 14:
            p = func_001FF048(p, (u32 *)&offset);
            rs->cfaOffset = offset;
            break;
        case 10: {
            struct RuleSet_1FF848 *copy = func_0018D740(sizeof(struct RuleSet_1FF848));
            *copy = *rs;
            rs->saved = copy;
            break;
        }
        case 11: {
            struct RuleSet_1FF848 *copy = rs->saved;
            *rs = *copy;
            func_0018D750(copy);
            break;
        }
        case 45:
            for (reg = 16; reg < 32; reg++) {
                rs->how[reg] = 1;
                rs->value[reg] = (reg - 16) * 4;
            }
            break;
        case 46:
            p = func_001FF048(p, (u32 *)&offset);
            rs->cfaReg = offset;
            break;
        default:
            func_002014D0();
            break;
        }
    }
    return p;
}

void func_002014D0(void) __attribute__((noreturn));

void func_001FD920(void)
{
    func_002014D0();
}

struct Info_001FEC10 {
    u8 pad[8];
    void* value;
    void* type;
};

extern void func_001FE938() __attribute__((noreturn));

// The runtime's exceptions: a base class with a description, and the classes thrown below.
class Error_1FEC10 {
public:
    Error_1FEC10() {}
    virtual ~Error_1FEC10() {}
    virtual const char* Describe() const;
};

class Unlisted_1FEC10 : public Error_1FEC10 {
public:
    Unlisted_1FEC10() {}
    virtual ~Unlisted_1FEC10() {}
};

class Fault_1FEDC8 : public Error_1FEC10 {
public:
    Fault_1FEDC8() {}
    virtual ~Fault_1FEDC8() {}
};

class Fault_1FEE48 : public Error_1FEC10 {
public:
    Fault_1FEE48() {}
    virtual ~Fault_1FEE48() {}
};

void func_001FEC10(s32 count, void** allowed)
{
    Info_001FEC10* info = *(Info_001FEC10**)func_001FDA10();
    s32 i;

    for (i = 0; i < count; i++) {
        if (func_00200778((Res_001FEA18*)allowed[i], (s32)info->type, (s32)info->value)) {
            throw;
        }
    }
    try {
        func_001FE938();
    } catch (...) {
        if (info != (Info_001FEC10*)__exception_info) {
            info = (Info_001FEC10*)__exception_info;
            for (i = 0; i < count; i++) {
                if (func_00200778((Res_001FEA18*)allowed[i], (s32)info->type, (s32)info->value)) {
                    throw;
                }
            }
        }
        void* type = func_001FEF70();
        for (i = 0; i < count; i++) {
            if (func_00200778((Res_001FEA18*)allowed[i], (s32)type, (s32)info->value)) {
                throw Unlisted_1FEC10();
            }
        }
        func_001FE8F0();
    }
}

void func_001FEDC8()
{
    throw Fault_1FEDC8();
}

void func_001FEE48()
{
    throw Fault_1FEE48();
}

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
extern const Fn_Table D_0024F0C0[6] = { 0, (Fn_Table)func_001FEF70, 0, (Fn_Table)func_001FEF28, 0, (Fn_Table)func_001FEF00 };

struct Vec_001FD868
{
	s32 w0;
	s32 w1;
	s32 w2;
	u32 w3;
};

void func_001FD6E0(f32* in, Vec_001FD868* out);
s32 func_001FD548(s32 a, s32 b, s32 c, u64 d);

s32 func_001FD868(f32 x)
{
	Vec_001FD868 v;
	func_001FD6E0(&x, &v);
	return func_001FD548(v.w0, v.w1, v.w2, (u64)v.w3 << 30);
}

typedef void (*Handler_001FE8F0)(void) __attribute__((noreturn));

void func_001FE8F0(void) __attribute__((noreturn));

void func_001FE8F0(void)
{
	((Handler_001FE8F0)D_00278048)();
}

void func_001FE908(void) __attribute__((noreturn));

void func_001FE908(void)
{
	func_001FE8F0();
}

Handler_001FE8F0 func_001FE918(Handler_001FE8F0 handler)
{
	Handler_001FE8F0 old = (Handler_001FE8F0)D_00278048;
	D_00278048 = (void (*)())handler;
	return old;
}

typedef void (*Handler_001FE938)(void) __attribute__((noreturn));

void func_001FE938(void) __attribute__((noreturn));

void func_001FE938(void)
{
	((Handler_001FE938)D_00278640)();
}

s32 func_001FE950(void)
{
	return *(s32*)func_001FDA10() + 8;
}

struct Arg_1FE9D0;
s32 func_0018D740(Arg_1FE9D0* size);
extern void func_001FE8F0(void) __attribute__((noreturn));

s32 func_001FE9D0(Arg_1FE9D0* size)
{
    s32 p = func_0018D740(size);
    if (p == 0)
        func_001FE8F0();
    return p;
}

// The unpacked form of a double: class, sign, exponent and fraction.
struct Unpacked_1FD578 {
    s32 kind;
    s32 sign;
    s32 exponent;
    u32 pad;
    u64 fraction;
};

struct Bits_1FD578 { u64 bits; };

void func_001FCA40(Bits_1FD578* bits, Unpacked_1FD578* out);
s32 func_001FD838(s32 a0, s32 a1, s32 a2, s32 a3);  // defined earlier in src/lib/001FC000.cpp

s32 func_001FD578(Bits_1FD578 bits)
{
    Unpacked_1FD578 u;
    func_001FCA40(&bits, &u);
    s32 fraction = (s32)(u.fraction >> 30) | 1;
    if ((u.fraction & 0x3FFFFFFFULL) == 0) fraction = (s32)(u.fraction >> 30);
    return func_001FD838(u.kind, u.sign, u.exponent, fraction);
}

// The exception an allocation failure throws (its typeinfo function is func_00200000).
class Fault_1FD8A8 {
public:
    virtual ~Fault_1FD8A8();
};

struct Arg_001FD8A8;

void* func_0018D758(Arg_001FD8A8* q);

void* func_001FD8A8(Arg_001FD8A8* a) throw(Fault_1FD8A8)
{
    return func_0018D758(a);
}

struct Obj_1FDFF8 { u8* f0; u8 pad[0x14]; s64 tbl[80]; s32 pad2; s8 st[64]; };

void func_002014D0(void);

u8* func_001FDFF8(u32 idx, Obj_1FDFF8* self, Obj_1FDFF8* other)
{
    while (self->st[idx] == 2) {
        idx = self->tbl[idx];
    }
    if (self->st[idx] == 1) {
        return self->f0 + self->tbl[idx];
    }
    func_002014D0();
}

struct Handle_1FEB18 {
    u8 pad_00[0x8];
    void* object;
    void* data;
    void (*callback)(void*, s32);
    s32 state;
    Handle_1FEB18* next;
    u8 pad_1C[4];
    s64 refs;
    void* buf;
};

extern void func_001FE8F0(void) __attribute__((noreturn));
s32 func_001FE9F8(void*);
s32 func_00200C40(void*);

void func_001FEB18(Handle_1FEB18* self)
{
    Handle_1FEB18** link = (Handle_1FEB18**)func_001FDA10();
    if (--self->refs != 0) {
        return;
    }
    if (self == *link && self->state == 0) {
        return;
    }
    for (; *link != 0; link = &(*link)->next) {
        if (*link == self) {
            break;
        }
    }
    if (*link == 0) {
        func_001FE8F0();
    }
    *link = self->next;
    if (self->callback != 0) {
        self->callback(self->object, 2);
    }
    if (func_00200C40(self->data) == 0) {
        func_001FE9F8(self->buf);
    }
    func_001FE9F8(self);
}

struct Elem_001FF0E0 { s32 a; s32 b; s32 key; };
struct Arr_001FF0E0 { Elem_001FF0E0** data; s32 count; };

void func_001FF0E0(Arr_001FF0E0* self, Arr_001FF0E0* other)
{
    s32 j = other->count;
    if (j != 0) {
        s32 n1 = self->count;
        s32 i = n1;
        do {
            Elem_001FF0E0* x = other->data[--j];
            if (i != 0 && self->data[i - 1]->key - x->key > 0) {
                do {
                    self->data[i + j] = self->data[i - 1];
                    i--;
                } while (i != 0 && self->data[i - 1]->key - x->key > 0);
            }
            self->data[i + j] = x;
        } while (j != 0);
        self->count = n1 + other->count;
    }
}

struct Packed_1FD5D0 {
    u32 kind;
    u32 sign;
    s32 exp;
    u32 mant;
};

union Bits_1FD5D0 {
    f32 f;
    struct {
        u32 mant : 23;
        u32 expo : 8;
        u32 sign : 1;
    } b;
};

struct Class_1FD5D0 {
    static s32 IsNan(Packed_1FD5D0* p) { return p->kind < 2; }
    static s32 IsInf(Packed_1FD5D0* p) { return p->kind == 4; }
    static s32 IsZero(Packed_1FD5D0* p) { return p->kind == 2; }
};

f32 func_001FD5D0(Packed_1FD5D0* p)
{
    Bits_1FD5D0 bits;
    u32 mant = p->mant;
    s32 expo = 0;
    u32 sign = p->sign;

    if (Class_1FD5D0::IsNan(p)) {
        expo = 0xFF;
        mant = mant | 0x100000;
    } else if (Class_1FD5D0::IsInf(p)) {
        expo = 0xFF;
        mant = 0;
    } else if (Class_1FD5D0::IsZero(p)) {
        mant = 0;
    } else if (mant != 0) {
        s32 e = p->exp;
        if (e < -0x7E) {
            s32 sh = -0x7E - e;
            if (sh > 0x19) {
                mant = 0;
            } else {
                mant = mant >> sh;
            }
            mant = mant >> 7;
        } else if (e >= 0x80) {
            expo = 0xFF;
            mant = 0;
        } else {
            expo = e + 0x7F;
            if ((mant & 0x7F) == 0x40) {
                if ((mant & 0x80) != 0) {
                    mant = mant + 0x40;
                }
            } else {
                mant = mant + 0x3F;
            }
            if ((s32)mant < 0) {
                mant = mant >> 1;
                expo = expo + 1;
            }
            mant = mant >> 7;
        }
    }

    bits.b.mant = mant;
    bits.b.expo = expo;
    bits.b.sign = sign;
    return bits.f;
}

struct Packed_1FC910 {
    u32 kind;
    u32 sign;
    s32 exp;
    u32 pad;
    u64 mant;
};

union Bits_1FC910 {
    double d;
    struct {
        u64 mant : 52;
        u64 expo : 11;
        u64 sign : 1;
    } b;
};

struct Class_1FC910 {
    static s32 IsNan(Packed_1FC910* p) { return p->kind < 2; }
    static s32 IsInf(Packed_1FC910* p) { return p->kind == 4; }
    static s32 IsZero(Packed_1FC910* p) { return p->kind == 2; }
};

double func_001FC910(Packed_1FC910* p)
{
    Bits_1FC910 bits;
    u64 mant = p->mant;
    s32 expo = 0;
    u32 sign = p->sign;

    if (Class_1FC910::IsNan(p)) {
        expo = 0x7FF;
        mant = mant | ((u64)1 << 51);
    } else if (Class_1FC910::IsInf(p)) {
        expo = 0x7FF;
        mant = 0;
    } else if (Class_1FC910::IsZero(p)) {
        mant = 0;
    } else if (mant != 0) {
        s32 e = p->exp;
        if (e < -0x3FE) {
            s32 sh = -0x3FE - e;
            if (sh > 0x38) {
                mant = 0;
            } else {
                mant = mant >> sh;
            }
            mant = mant >> 8;
        } else if (e >= 0x400) {
            expo = 0x7FF;
            mant = 0;
        } else {
            expo = e + 0x3FF;
            if ((mant & 0xFF) == 0x80) {
                if ((mant & 0x100) != 0) {
                    mant = mant + 0x80;
                }
            } else {
                mant = mant + 0x7F;
            }
            if (mant > 0x1FFFFFFFFFFFFFFFull) {
                mant = mant >> 1;
                expo = expo + 1;
            }
            mant = mant >> 8;
        }
    }

    bits.b.mant = mant;
    bits.b.expo = expo;
    bits.b.sign = sign;
    return bits.d;
}

struct Span_001FDEB0 { u32 lo; u32 hi; s32 value; void* cb; };
struct Ctx_001FDEB0 { void* fn; };
struct Cur_001FDEB0 { s32 pad0; s32 count; };

s32 func_001FDEB0(s32 a0, void* a1, Ctx_001FDEB0* a2, s32 a3, s32* a4)
{
    s32 result = 0;
    s32 key = a0;
    Span_001FDEB0* base;
    s32 idx;
    s32 r;

    *a4 = 1;
    if (a1 != 0) {
        idx = 0;
        base = (Span_001FDEB0*)((u8*)a1 + 8);
        if (a3 != 0) {
            idx = ((u8*)a0 - (u8*)base) >> 4;
            key = ((Cur_001FDEB0*)a0)->count - 1;
            if (base[idx].lo != 0xFFFFFFFF) {
                idx++;
            }
        } else {
            key = key - 1;
        }
        while (base[idx].lo != 0xFFFFFFFF) {
            if ((u32)key >= base[idx].lo && (u32)key < base[idx].hi) {
                if (base[idx].cb != 0) {
                    if (a2->fn != 0) {
                        r = ((s32 (*)(Ctx_001FDEB0*, void*, void*))a2->fn)(a2, base[idx].cb, a1);
                        if (r != 0) {
                            if (result == 0) {
                                result = base[idx].value;
                            }
                            *a4 = 0;
                            return result;
                        }
                    }
                } else {
                    if (result == 0) {
                        result = base[idx].value;
                    }
                }
            }
            idx++;
        }
    }
    return result;
}

struct Sf_1FD088 { u32 cls; s32 sign; s32 exp; u8 pad[4]; u64 mant; u8 tail[8]; };
struct Pk_1FD088 { u64 bits; };

void func_001FCA40(Pk_1FD088* src, Sf_1FD088* dst);
u64 func_001FC910(Sf_1FD088* src);
extern Sf_1FD088 D_0062A770;

struct Div_1FD088 {
    static s32 IsNan(Sf_1FD088* p) { return p->cls < 2; }
    static s32 IsInf(Sf_1FD088* p) { return p->cls == 4; }
    static s32 IsZero(Sf_1FD088* p) { return p->cls == 2; }
    static Sf_1FD088* Parts(Sf_1FD088* a, Sf_1FD088* b)
    {
        u64 rem;
        u64 div;
        u64 bit;
        u64 quo;

        if (IsNan(a)) {
            return a;
        }
        if (IsNan(b)) {
            return b;
        }
        a->sign ^= b->sign;
        if (IsInf(a) || IsZero(a)) {
            if (a->cls == b->cls) {
                return &D_0062A770;
            }
            return a;
        }
        if (IsInf(b)) {
            a->mant = 0;
            a->exp = 0;
            return a;
        }
        if (IsZero(b)) {
            a->cls = 4;
            return a;
        }
        a->exp = a->exp - b->exp;
        rem = a->mant;
        div = b->mant;
        if (rem < div) {
            a->exp--;
            rem <<= 1;
        }
        bit = (u64)1 << 60;
        quo = 0;
        while (bit) {
            if (rem >= div) {
                quo |= bit;
                rem -= div;
            }
            bit >>= 1;
            rem <<= 1;
        }
        if ((quo & 0xFF) == 0x80) {
            if (quo & 0x100) {
                quo += 0x80;
            } else if (rem) {
                quo += 0x80;
            }
        }
        a->mant = quo;
        return a;
    }
};

u64 func_001FD088(u64 x, u64 y)
{
    Sf_1FD088 pa;
    Sf_1FD088 pb;

    func_001FCA40((Pk_1FD088*)&x, &pa);
    func_001FCA40((Pk_1FD088*)&y, &pb);
    return func_001FC910(Div_1FD088::Parts(&pa, &pb));
}

struct Node_1FFE58 { s32 a; s32 b; s32 key; };
struct List_1FFE58 { Node_1FFE58** data; u32 count; };

void func_001FFE58(List_1FFE58* self, List_1FFE58* out)
{
    u32 n = self->count;
    u32 next[n];
    u32 head = 0xFFFFFFFFu;
    u32 i;
    u32 cur;
    for (i = 0; i < n; i++) {
        for (cur = head; cur != 0xFFFFFFFFu; cur = next[cur]) {
            if (self->data[i]->key - self->data[cur]->key >= 0) break;
            out->data[out->count++] = self->data[cur];
            self->data[cur] = 0;
        }
        head = i;
        next[i] = cur;
    }
    cur = 0;
    for (i = 0; i < n; i++) {
        Node_1FFE58* x = self->data[i];
        if (x != 0) {
            self->data[cur++] = x;
        }
    }
    self->count = cur;
}

struct Fp_1FCAE0 {
    u32 cls;
    s32 sign;
    s32 exp;
    s32 pad;
    u64 frac;
};


struct Add_1FCAE0 {
    static s32 IsNan(Fp_1FCAE0* p) { return p->cls < 2; }
    static s32 IsInf(Fp_1FCAE0* p) { return p->cls == 4; }
    static s32 IsZero(Fp_1FCAE0* p) { return p->cls == 2; }
};

Fp_1FCAE0* func_001FCAE0(Fp_1FCAE0* a, Fp_1FCAE0* b, Fp_1FCAE0* tmp)
{
    s32 ae, be;
    u64 af, bf;
    s64 tf;

    if (Add_1FCAE0::IsNan(a)) return a;
    if (Add_1FCAE0::IsNan(b)) return b;
    if (Add_1FCAE0::IsInf(a)) {
        if (Add_1FCAE0::IsInf(b) && a->sign != b->sign) return ((Fp_1FCAE0*)&D_0062A770);
        return a;
    }
    if (Add_1FCAE0::IsInf(b)) return b;
    if (Add_1FCAE0::IsZero(b)) {
        if (Add_1FCAE0::IsZero(a)) {
            *tmp = *a;
            tmp->sign = a->sign & b->sign;
            return tmp;
        }
        return a;
    }
    if (Add_1FCAE0::IsZero(a)) return b;

    ae = a->exp;
    be = b->exp;
    af = a->frac;
    bf = b->frac;
    {
        s32 diff = ae - be;
        if (diff < 0) diff = -diff;
        if (diff < 64) {
            while (ae > be) {
                be++;
                bf = (bf & 1) | (bf >> 1);
            }
            while (be > ae) {
                ae++;
                af = (af & 1) | (af >> 1);
            }
        } else {
            if (ae > be) {
                bf = 0;
            } else {
                ae = be;
                af = 0;
            }
        }
    }
    if (a->sign != b->sign) {
        if (a->sign) tf = -af + bf;
        else tf = af - bf;
        if (tf >= 0) {
            tmp->sign = 0;
            tmp->exp = ae;
            tmp->frac = tf;
        } else {
            tmp->sign = 1;
            tmp->exp = ae;
            tmp->frac = -tf;
        }
        while (tmp->frac < 0x1000000000000000ULL && tmp->frac) {
            tmp->frac <<= 1;
            tmp->exp--;
        }
    } else {
        tmp->sign = a->sign;
        tmp->exp = ae;
        tmp->frac = af + bf;
    }
    tmp->cls = 3;
    if (tmp->frac >= 0x2000000000000000ULL) {
        tmp->frac = (tmp->frac & 1) | (tmp->frac >> 1);
        tmp->exp++;
    }
    return tmp;
}

union Frac_1FCDE0 { u64 ll; u32 l[2]; };
struct Sf_1FCDE0 { u32 cls; s32 sign; s32 exp; u8 pad[4]; Frac_1FCDE0 mant; u8 tail[8]; };
struct Pk_1FCDE0 { u64 bits; };

void func_001FCA40(Pk_1FCDE0* src, Sf_1FCDE0* dst);
u64 func_001FC910(Sf_1FCDE0* src);
u64 func_001FE890(u64 a, u64 b);

struct Mul_1FCDE0 {
    static s32 IsNan(Sf_1FCDE0* x) { return x->cls < 2; }
    static s32 IsZero(Sf_1FCDE0* x) { return x->cls == 2; }
    static s32 IsInf(Sf_1FCDE0* x) { return x->cls == 4; }

    static Sf_1FCDE0* Parts(Sf_1FCDE0* a, Sf_1FCDE0* b, Sf_1FCDE0* tmp)
    {
        u64 high;
        u64 low;

        if (IsNan(a)) {
            a->sign = a->sign != b->sign;
            return a;
        }
        if (IsNan(b)) {
            b->sign = a->sign != b->sign;
            return b;
        }
        if (IsInf(a)) {
            if (IsZero(b)) {
                return ((Sf_1FCDE0*)&D_0062A770);
            }
            a->sign = a->sign != b->sign;
            return a;
        }
        if (IsInf(b)) {
            if (IsZero(a)) {
                return ((Sf_1FCDE0*)&D_0062A770);
            }
            b->sign = a->sign != b->sign;
            return b;
        }
        if (IsZero(a)) {
            a->sign = a->sign != b->sign;
            return a;
        }
        if (IsZero(b)) {
            b->sign = a->sign != b->sign;
            return b;
        }
        {
            u64 alo = a->mant.ll & 0xFFFFFFFF;
            u64 ahi = a->mant.ll >> 32;
            u64 blo = b->mant.ll & 0xFFFFFFFF;
            u64 bhi = b->mant.ll >> 32;
            u64 p0 = func_001FE890(blo, alo);
            u64 p1 = func_001FE890(bhi, alo);
            u64 p2 = func_001FE890(blo, ahi);
            u64 p3 = func_001FE890(bhi, ahi);
            u64 mid = p1 + p2;
            u64 hi = 0;
            if (mid < p1) {
                hi += (u64)1 << 32;
            }
            u64 lo = p0 + (mid << 32);
            if (lo < p0) {
                hi++;
            }
            hi += ((mid >> 32) & 0xFFFFFFFF) + p3;
            high = hi;
            low = lo;
        }
        tmp->exp = a->exp + b->exp;
        tmp->sign = a->sign != b->sign;
        tmp->exp += 4;
        while (high > (~(u64)0 >> 3)) {
            tmp->exp++;
            if (high & 1) {
                low >>= 1;
                low |= 0x8000000000000000ull;
            }
            high >>= 1;
        }
        while (high <= (~(u64)0 >> 4)) {
            tmp->exp--;
            high <<= 1;
            if (low & 0x8000000000000000ull) {
                high |= 1;
            }
            low <<= 1;
        }
        if ((high & 0xFF) == 0x80) {
            if (high & 0x100) {
                high += 0x80;
            } else if (low) {
                high += 0x80;
            }
        }
        tmp->mant.ll = high;
        tmp->cls = 3;
        return tmp;
    }
};

u64 func_001FCDE0(u64 x, u64 y)
{
    Sf_1FCDE0 a;
    Sf_1FCDE0 b;
    Sf_1FCDE0 tmp;
    Pk_1FCDE0 xa;
    Pk_1FCDE0 xb;

    xa.bits = x;
    xb.bits = y;
    func_001FCA40(&xa, &a);
    func_001FCA40(&xb, &b);
    return func_001FC910(Mul_1FCDE0::Parts(&a, &b, &tmp));
}

// The runtime's exception context: the handler chain at +4, the active exception at +8.
struct Ctx_1FDAF0 {
    s32 f0;
    void** chain;
    void* active;
};

typedef Ctx_1FDAF0* (*GetCtx_1FDAF0)(void);
extern void* D_0027804C;

void func_001FD930();
void func_001FDAF0(void) __attribute__((noreturn));

// Throws: runs the cleanups registered in the top handler, then jumps to that handler.
void func_001FDAF0(void)
{
    Ctx_1FDAF0* ctx = ((GetCtx_1FDAF0)D_0027804C)();
    void*** chain = &ctx->chain;
    void*** cleanups = (void***)&(*chain)[1];

    if (cleanups[0] != 0) {
        double space[200];
        void** frame = (void**)space;
        frame[1] = 0;
        frame[0] = *chain;
        if (!__builtin_setjmp(&frame[2])) {
            *chain = frame;
            while (cleanups[0] != 0) {
                void (*fn)(void*, s32) = (void (*)(void*, s32))cleanups[0][1];
                void* arg = cleanups[0][2];
                cleanups[0] = (void**)cleanups[0][0];
                fn(arg, 2);
            }
            *chain = (void**)frame[0];
        } else {
            func_001FD930();
        }
    }

    if (ctx->active == 0 || (*chain)[0] == 0) {
        func_001FD930();
    }

    void* buf = &(*chain)[2];
    *chain = (void**)(*chain)[0];
    __builtin_longjmp(buf, 1);
}

// Pops the top handler after running its cleanups, then throws again.
void func_001FDC68(void)
{
    Ctx_1FDAF0* ctx = ((GetCtx_1FDAF0)D_0027804C)();
    void*** chain = &ctx->chain;
    void*** cleanups = (void***)&(*chain)[1];

    if (cleanups[0] != 0) {
        double space[200];
        void** frame = (void**)space;
        frame[1] = 0;
        frame[0] = *chain;
        if (!__builtin_setjmp(&frame[2])) {
            *chain = frame;
            while (cleanups[0] != 0) {
                void (*fn)(void*, s32) = (void (*)(void*, s32))cleanups[0][1];
                void* arg = cleanups[0][2];
                cleanups[0] = (void**)cleanups[0][0];
                fn(arg, 2);
            }
            *chain = (void**)frame[0];
        } else {
            func_001FD930();
        }
    }

    *chain = (void**)(*chain)[0];
    func_001FDAF0();
}

// The active exception, asked whether it matches a runtime type through its matcher.
struct Info_1FDD80 {
    void* (*match)(Info_1FDD80* info, void* type, void* extra);
};

s32 func_001FDD80(void* type)
{
    Info_1FDD80* info = *(struct Info_1FDD80 **)func_001FDA10();
    void* (*match)(Info_1FDD80*, void*, void*) = info->match;
    if (match == 0) {
        return 0;
    }
    return match(info, type, 0) != 0;
}

struct Tag_1FE198 {
    u32 word;
};

struct __attribute__((aligned(8))) Frame_1FE198 {
    s32 f0;
    Tag_1FE198* f4;
    s32 f8;
    s32 fC;
    s32 f10[0xA2];
    u16 f298;
    u16 f29A;
    s8 f29C[0x54];
};

struct Obj_1FE198 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
};

struct Pc_1FE198;
Frame_1FE198* func_001FE100(Pc_1FE198* pc, Frame_1FE198* f, Frame_1FE198* prev);
s32 func_001FDEB0(s32 a, Tag_1FE198* t, s32 c, s32 d, s32* e);
s32 func_001FDDD8(Pc_1FE198* pc, Tag_1FE198* t);
s64* func_001FDFF8(u16 idx, Frame_1FE198* f, Frame_1FE198* g);
s32 func_001FE080(s32 idx, Frame_1FE198* f, Frame_1FE198* g);
void func_001FE190(void);
void func_001FD930(void);

struct ReturnAddr_1FE198 {
    static Pc_1FE198* Of(Frame_1FE198* f, Frame_1FE198* g)
    {
        s64 w = *func_001FDFF8(f->f29A, f, g);
        return (Pc_1FE198*)(s32)w;
    }
};

struct RegWindow_1FE198 {
    static s32 In(s32 i, Frame_1FE198* f) { return 0; }
};

s32 func_001FE198(Obj_1FE198* obj, Pc_1FE198* pc, Frame_1FE198* fb, Frame_1FE198** pout)
{
    Frame_1FE198 sub;
    Frame_1FE198 saved;
    Frame_1FE198* udata = *pout;
    Frame_1FE198* subp = &sub;
    Pc_1FE198* startPc = pc;
    s32 res = 0;
    s32 pending = obj->fC != 0;
    s32 a8 = obj->f8;
    s32 cleanup;
    s32 savedRes;
    Pc_1FE198* savedPc;
    s32 onlyCleanup;
    s32 savedState;
    s32 i;

    onlyCleanup = 0;
    savedState = 0;
    cleanup = 0;
    for (;;) {
        Frame_1FE198* p = udata;
        s32 isNew;
        udata = func_001FE100(pc, udata, subp);
        subp = p;
        if (udata == 0) {
            break;
        }
        if (udata->f4 == 0) {
            isNew = 0;
        } else {
            isNew = udata->f4->word == 0xFFFFFFFEu;
        }
        if (pending) {
            pending = 0;
            res = func_001FDEB0(obj->fC, udata->f4, a8, 1, &cleanup);
            obj->fC = 0;
        } else if (isNew) {
            res = func_001FDEB0((s32)pc, udata->f4, a8, 0, &cleanup);
        } else {
            res = func_001FDDD8(pc, udata->f4);
        }
        if (res != 0) {
            if (cleanup != 0) {
                if (savedState == 0) {
                    saved = *udata;
                    savedPc = pc;
                    savedRes = res;
                    savedState = 1;
                    onlyCleanup = 1;
                }
            } else {
                onlyCleanup = 0;
                break;
            }
        }
        pc = (Pc_1FE198*)((s8*)ReturnAddr_1FE198::Of(udata, subp) - 1);
    }
    if (savedState != 0) {
        udata = &saved;
        res = savedRes;
        pc = savedPc;
        if (onlyCleanup != 0) {
            func_001FE190();
        }
    }
    if (res == 0) {
        func_001FD930();
    }
    obj->f0 = res;
    if (pc == startPc) {
        udata = fb;
    } else {
        Pc_1FE198* handlerPc = pc;
        pc = startPc;
        *udata = *fb;
        while (pc != handlerPc) {
            Frame_1FE198* p = udata;
            udata = func_001FE100(pc, udata, subp);
            subp = p;
            for (i = 0; i < 0x4F; i++) {
                if (i != udata->f29A && udata->f29C[i] != 0) {
                    func_001FE080(i, udata, fb);
                }
            }
            pc = (Pc_1FE198*)((s8*)ReturnAddr_1FE198::Of(udata, subp) - 1);
        }
        if (udata->f29C[udata->f29A] == 2) {
            i = udata->f10[udata->f29A];
            if (RegWindow_1FE198::In(i, udata)) {
                func_001FE080(i, udata, fb);
            }
        }
    }
    *pout = udata;
    return res;
}

// Globals defined from C.
void (*D_00278048)() = func_001FD920;
s32 D_00278640 = (s32)func_001FE908;
extern const char D_0024F0F0[16] = "13bad_exception";
extern const char D_0024F100[16] = "9exception";
extern const Bad_24F1E0 D_0024F1E0 = { "bad_alloc", { { 0, func_00200000 }, { 0, func_00200050 }, { 0, (void(*)())func_001FFFF0 } } };
