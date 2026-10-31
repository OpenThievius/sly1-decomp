// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Quad_113780 { s32 a, b, c, d; };

extern void func_0011B008(void* state);
extern void func_0011B538(void* state, s32 n);
extern void func_0011B018(void* state, void* value);
extern void func_0011B060(void* state, s32 mode);

void* func_00113780(void* self)
{
    Quad_113780 q;
    func_0011B008(&q);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

extern void* func_00113888(void* state, void* value, s32 mode);
extern void* func_00113B60(void* state, void* value, void* rangeEnd);

void* func_001139E8(void* state, void* arg1, void* value) {
	func_00113888(state, value, 0);
	return state;
}

void* func_00113A18(void* state, void* arg1, void* value) {
	func_00113888(state, value, 1);
	return state;
}

void* func_00113A48(void* self, int unused, void* x)
{
    func_00113888(self, x, 2);
    return self;
}

void* func_00113A78(void* state, void* arg1, void* value) {
	func_00113888(state, value, 3);
	return state;
}

void* func_00113E48(void* state, void* arg1, void* value) {
	func_00113B60(state, value, (char*)value + 8);
	return state;
}

extern void func_0011B5F0(void* state, bool condition);

void* func_00113E78(void* state, void* arg1, s32* value) {
	char local[0x10];
	func_0011B008(local);
	func_0011B5F0(local, value[0] == 0x1B);
	func_0011B018(state, local);
	func_0011B060(local, 2);
	return state;
}

void* func_00113EE0(void* state, void* arg1, s32* value) {
	char local[0x10];
	func_0011B008(local);
	func_0011B5F0(local, value[0] >= 0x14 && value[0] < 0x16);
	func_0011B018(state, local);
	func_0011B060(local, 2);
	return state;
}

void* func_00113F48(void* state, void* arg1, s32* value) {
	char local[0x10];
	func_0011B008(local);
	func_0011B5F0(local, value[0] == 0x15);
	func_0011B018(state, local);
	func_0011B060(local, 2);
	return state;
}

void* func_00113FB0(void* state, void* arg1, s32* value) {
	char local[0x10];
	func_0011B008(local);
	func_0011B5F0(local, value[0] == 0x14);
	func_0011B018(state, local);
	func_0011B060(local, 2);
	return state;
}

struct Quad_113730 { s32 a, b, c, d; };

void func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, s32 n);
void func_0011B538(void* q, s32 n);

void* func_00113730(void* self)
{
    Quad_113730 q;
    func_0011B008(&q);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_1137D0 { s32 a, b, c, d; };

void func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, s32 n);
void func_0011B538(void* q, s32 n);

void* func_001137D0(void* self)
{
    Quad_1137D0 q;
    func_0011B008(&q);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

// NEAR: the second field load (0xC) goes to $v0, retail loads it into $v1 (xor operand register)

struct Quad_113820 { s32 a, b, c, d; };
struct Src_113820 { s32 f0; s32 f4; s32 f8; s32 fC; };

Quad_113820* func_0011B008(Quad_113820* q);
void func_0011B018(void* dst, Quad_113820* src);
void func_0011B060(Quad_113820* q, int mode);
s32 func_0011B5F0(Quad_113820* q, s32 flag);

void* func_00113820(void* self, void* x, Src_113820* src)
{
    Quad_113820 q;
    func_0011B008(&q);
    (void)func_0011B5F0(&q, src->f4 == src->fC);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Entry_113888 {
    s32 tag;
    union {
        s32 i;
        f32 f;
    } v;
};

struct __attribute__((aligned(16))) Quad_113888 { s32 a, b, c, d; };

void func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, s32 n);
void func_0011B5F0(void* q, s32 flag);

void* func_00113888(void* self, Entry_113888* e, s32 mode)
{
    f32 xy[2];
    Quad_113888 obj;
    func_0011B008(&obj);
    f32* out = xy;
    for (s32 i = 1; i >= 0; i--, e++) {
        if (e->tag == 0x15) {
            *out = e->v.f;
        } else {
            *out = (f32)e->v.i;
        }
        out++;
    }
    switch (mode) {
    case 0:
        func_0011B5F0(&obj, xy[0] < xy[1]);
        break;
    case 1:
        func_0011B5F0(&obj, xy[0] <= xy[1]);
        break;
    case 2:
        func_0011B5F0(&obj, xy[0] > xy[1]);
        break;
    case 3:
        func_0011B5F0(&obj, xy[0] >= xy[1]);
        break;
    }
    func_0011B018(self, &obj);
    func_0011B060(&obj, 2);
    return self;
}

struct Quad_113AA8 { s32 a, b, c, d; };
struct Ent_113AA8 { s32 kind; s32 val; };

s32 func_0011B008(Quad_113AA8* q);
s32 func_0011B5F0(Quad_113AA8* q, s32 flag);
void func_0011B018(void* dst, Quad_113AA8* src);
void func_0011B060(Quad_113AA8* q, s32 mode);

void* func_00113AA8(void* self, void* unused, Ent_113AA8* k)
{
    Quad_113AA8 q;
    s32 r;
    func_0011B008(&q);
    Ent_113AA8* p = k + 1;
    if (k->kind != p->kind) {
        r = 0;
    } else {
        switch (k->kind) {
        case 20:
        case 27: case 28: case 29: case 30: case 31: case 32: case 33:
            r = (k->val == p->val);
            break;
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
        case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
        case 34:
            r = 1;
            break;
        }
    }
    func_0011B5F0(&q, r);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct __attribute__((aligned(16))) Q_113B60 {
    s32 f0;
    Q_113B60* f4;
    Q_113B60* f8;
    s32 fC;
};
struct E_113B60 {
    s32 f0;
    Q_113B60* f4;
    Q_113B60* f8;
    s32 fC;
    Q_113B60* f10;
};

void func_0011B008(Q_113B60* q);
void func_0011B018(Q_113B60* out, Q_113B60* q);
void func_0011B060(Q_113B60* q, s32 mode);
void func_0011B0A8(Q_113B60* a, Q_113B60* b);
void func_0011B5F0(Q_113B60* q, s32 v);
void func_0011B6C0(Q_113B60* q, Q_113B60* v);

Q_113B60* func_00113B60(Q_113B60* out, Q_113B60* a, Q_113B60* b)
{
    Q_113B60 R;
    Q_113B60 A;
    Q_113B60 B;
    Q_113B60 C;
    Q_113B60 D;
    Q_113B60 E;
    Q_113B60 F;
    s32 r;

    func_0011B008(&R);
    if (a->f0 != b->f0) {
        r = 0;
    } else {
        switch (a->f0) {
        case 30: {
            Q_113B60* p = a->f4;
            Q_113B60* q = b->f4;
            if (p == q) {
                r = 1;
            } else if ((p->f8 == 0) != (q->f8 == 0)) {
                r = 0;
            } else {
                func_0011B008(&A);
                func_00113B60(&B, p, q);
                func_0011B0A8(&A, &B);
                func_0011B060(&B, 2);
                if (A.f4 == 0) {
                    r = 0;
                } else if (p->f8 == 0) {
                    r = 1;
                } else {
                    func_0011B008(&B);
                    func_0011B008(&C);
                    func_0011B6C0(&B, p->f8);
                    func_0011B6C0(&C, q->f8);
                    func_00113B60(&D, &B, &C);
                    func_0011B0A8(&A, &D);
                    func_0011B060(&D, 2);
                    r = (s32)A.f4;
                    func_0011B060(&C, 2);
                    func_0011B060(&B, 2);
                }
                func_0011B060(&A, 2);
            }
            break;
        }
        case 31: {
            E_113B60* p = (E_113B60*)a->f4;
            E_113B60* q = (E_113B60*)b->f4;
            if (p == q) {
                r = 1;
            } else if (p->f8 != q->f8 || p->fC != q->fC || p->f0 != q->f0) {
                r = 0;
            } else {
                func_0011B008(&A);
                func_0011B008(&B);
                func_0011B008(&E);
                func_0011B6C0(&A, p->f10);
                func_0011B6C0(&B, q->f10);
                func_00113B60(&F, &A, &B);
                func_0011B0A8(&E, &F);
                func_0011B060(&F, 2);
                r = (s32)E.f4;
                func_0011B060(&E, 2);
                func_0011B060(&B, 2);
                func_0011B060(&A, 2);
            }
            break;
        }
        case 20: case 27: case 28: case 29: case 32:
            r = a->f4 == b->f4;
            break;
        case 33: {
            Q_113B60* p = a->f4;
            Q_113B60* q = b->f4;
            if (p == q) {
                r = 1;
            } else {
                r = p->f0 == q->f0 && p->f4 == q->f4;
            }
            break;
        }
        case 21: case 22: case 23: case 24: case 25: case 26:
            break;
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
        case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
        case 34:
            r = 1;
            break;
        }
    }
    func_0011B5F0(&R, r);
    func_0011B018(out, &R);
    func_0011B060(&R, 2);
    return out;
}
