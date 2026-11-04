// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Quad_113780 { s32 a, b, c, d; };

extern void func_0011B008(void* state);
extern void func_0011B538(void* state, s32 n);
extern void func_0011B018(void* state, void* value);
extern void func_0011B060(void* state, s32 mode);



extern void* func_00113888(void* state, void* value, s32 mode);
extern void* func_00113B60(void* state, void* value, void* rangeEnd);











extern void func_0011B5F0(void* state, bool condition);









struct Quad_113730 { s32 a, b, c, d; };

void func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, s32 n);
void func_0011B538(void* q, s32 n);



struct Quad_1137D0 { s32 a, b, c, d; };

void func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, s32 n);
void func_0011B538(void* q, s32 n);



// NEAR: the second field load (0xC) goes to $v0, retail loads it into $v1 (xor operand register)

struct Quad_113820 { s32 a, b, c, d; };
struct Src_113820 { s32 f0; s32 f4; s32 f8; s32 fC; };

Quad_113820* func_0011B008(Quad_113820* q);
void func_0011B018(void* dst, Quad_113820* src);
void func_0011B060(Quad_113820* q, int mode);
s32 func_0011B5F0(Quad_113820* q, s32 flag);



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



struct Quad_113AA8 { s32 a, b, c, d; };
struct Ent_113AA8 { s32 kind; s32 val; };

s32 func_0011B008(Quad_113AA8* q);
s32 func_0011B5F0(Quad_113AA8* q, s32 flag);
void func_0011B018(void* dst, Quad_113AA8* src);
void func_0011B060(Quad_113AA8* q, s32 mode);



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


