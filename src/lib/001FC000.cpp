// SPDX-License-Identifier: AGPL-3.0-or-later
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

extern s32 D_002789D8;

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

extern u8 D_0024F0C0[];

void* func_001FEF58(void* self)
{
    *(void**)self = D_0024F0C0;
    return self;
}

extern u8 D_0024F0D8[];

void* func_001FEFF0(void* self)
{
    *(void**)self = D_0024F0D8;
    return self;
}

extern u8 D_0024F1E0[];

void* func_001FFFF0(void)
{
    return D_0024F1E0;
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
void func_001FD1F0(Out_001FD308* a, Out_001FD308* b);

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
void func_001FEA18(struct Fn_1FEA88* self);

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
extern u8 D_0024F0F0[];
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
        func_00200118(node, D_0024F0F0, D_0027B318);
    }
    return node;
}

// NEAR: only the s0 and ra saves differ: retail saves ra and s0 with sd (8 bytes), the SN builds with sq; the 8-byte save is the Sony 2.9-ee-991111 form (docs/TOOLCHAIN.md), not used here.

extern u8 D_0027B318[];
extern u8 D_0024F100[];

struct Node_1FF008 {
    void *field0;
    void *vtbl;
};

void func_00200138(struct Node_1FF008 *self, void *value);

void *func_001FF008(void) {
    struct Node_1FF008 *node = (struct Node_1FF008 *)D_0027B318;
    if (*(void **)D_0027B318 == 0) {
        func_00200138(node, D_0024F100);
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
