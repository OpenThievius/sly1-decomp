// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "c6c.h"
#include "globals.h"
#include "s1dbbd8.h"

// The script machine's built-in functions (the table D_00259958, which func_00119BB0 calls through,
// lists them from func_00112698 on), their helpers and the collector's mark stacks: one source
// file, 0x112698 to 0x11AE78 (.rodata from 0x248FE0, .data from 0x259938 to 0x25C250, no .bss).

// The mark stacks of the collector (func_0011A850 walks them; value.cpp's functions run it through
// func_0011AB58). Its constructor (func_0011A678) and destructor (func_0011A680) are defined below at
// their places; the compiler's initialiser, constructor and destructor for this file are
// func_0011ADF8, func_0011AE38 and func_0011AE58 (config/us/generated.tsv).
struct Gc_259F38 {
    u8 data[0x2318];
    Gc_259F38();
    ~Gc_259F38();
};

struct Quad_113780 { s32 a, b, c, d; };

void* func_0011B008(void* state);
extern void func_0011B538(void* state, s32 n);
extern void func_0011B018(void* state, void* value);
extern void func_0011B060(void* state, s32 mode);

extern void* func_00113888(void* state, void* value, s32 mode);
extern void* func_00113B60(void* state, void* value, void* rangeEnd);

extern void func_0011B5F0(void* state, bool condition);

struct Quad_113730 { s32 a, b, c, d; };

void* func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, s32 n);
void func_0011B538(void* q, s32 n);

struct Quad_1137D0 { s32 a, b, c, d; };

void* func_0011B008(void* q);
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

void* func_0011B008(void* q);
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

void func_00115CA0(void* self, s32 value, s32 mode);

void func_00115CA0(void* self, s32 value, s32 mode);

void func_00115CA0(void* self, s32 value, s32 mode);

void func_00115CA0(void* self, s32 value, s32 mode);

void func_00115CA0(void* self, s32 value, s32 mode);

void func_00115CA0(void* self, s32 value, s32 mode);

void func_00115CA0(void* self, s32 value, s32 mode);

struct Entry_115EC8 {
    s32 tag;
    union {
        s32 i;
        f32 f;
    } v;
};

struct Frame_115EC8 {
    u8 obj[0x10];
    f32 xy[2];
};

void* func_0011B008(void* obj);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);
f32 func_00205778(f32 x, f32 y);
void* func_0011B5B0(void* obj, f32 x);

struct Node_116600 {
    u8 pad[8];
    void* link;
};

struct Tmp_116600 {
    u8 bytes[0x10];
};

struct Src_116600 {
    s32 pad0;
    s32 a;
    s32 pad2;
    s32 b;
};

void* func_0011B008(void* obj);
struct Node_11AF28* func_0011AF28(void);
void* func_0011C508(void);
void func_0011B740(void* a, void* b);
f32 func_001ED908(s32 a, s32 b, void* c);
void func_0011B6C0(void* a, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

struct Tmp_1166C0 {
    u8 bytes[0x10];
};

struct Src_1166C0 {
    s32 pad0;
    s32 a;
};

void* func_0011B008(void* obj);
void* func_0011C618(void);
void func_00188770(s32 a, void* b);
void func_0011B788(void* obj, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

struct Tmp_116740 {
    u8 bytes[0x10];
};

struct Src_116740 {
    s32 pad0;
    s32 a;
};

void* func_0011B008(void* obj);
void* func_0011C618(void);
void func_00189AF0(s32 a, void* b);
void func_0011B788(void* obj, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

struct Tmp_1167C0 {
    u8 bytes[0x10];
};

struct Src_1167C0 {
    s32 pad0;
    s32 a;
    s32 pad2;
    s32 b;
};

void* func_0011B008(void* obj);
void* func_0011C618(void);
void func_001891C0(s32 a, s32 b, void* c);
void func_0011B788(void* obj, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

struct Quad_114018 { s32 a, b, c, d; };

void func_0011B008(Quad_114018* q);
void func_0011B5F0(Quad_114018* q, int flag);
void func_0011B018(void* out, Quad_114018* q);
void func_0011B060(Quad_114018* q, int mode);

struct Quad_114288 { s32 a, b, c, d; };

void func_0011B008(Quad_114288* q);
void func_0011B5F0(Quad_114288* q, int flag);
void func_0011B018(void* out, Quad_114288* q);
void func_0011B060(Quad_114288* q, int mode);

void func_001147B8(void* self, int a, void* b, void* c, int n);

struct Vec_1158B8 { f32 x, y, z, w; };

void* func_0011B008(void* self);
void* func_0011C968(void);
void func_0011B9A8(void* out, void* src);
void func_0011B0A8(void* self, void* other);
void func_0011B060(void* self, s32 n);
void func_0011B860(void* a, void* b);
void func_0011B018(void* dst, void* src);

struct Vec_116DC8 { f32 x, y, z, w; };
struct Src_116DC8 { s32 pad0; f32* poly; s32 pad8; f32* range; };
void* func_0011B008(void* self);
void func_0011B9A8(void* out, void* src);
void* func_0011B5B0(void* obj, f32 x);
void func_0011B060(void* self, s32 n);
void func_0011B018(void* dst, void* src);

struct Tmp_1171F0 { s32 w[4]; };
struct Src_1171F0 { s32 pad0; f32 v; };

void* func_0011B008(void* self);
void func_0011B570(void* self, s32 n);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* self, s32 n);

struct Tmp_117880 { s32 w[4]; };
struct Obj_117880 { u8 pad[0x29C]; f32 value; };
struct Src_117880 { s32 pad0; Obj_117880* obj; };

void* func_0011B008(void* self);
void func_0011B9A8(void* out, void* src);
void func_0011B060(void* self, s32 n);
void func_0011B018(void* dst, void* src);

struct Quad_114080 { s32 a, b, c, d; };
struct Tag_114080 { s32 tag; };

void* func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, s32 n);
void func_0011B5F0(void* q, s32 flag);

struct Quad_1140E8 { s32 a, b, c, d; };
struct Tag_1140E8 { s32 tag; };

void* func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, s32 n);
void func_0011B5F0(void* q, s32 flag);

struct Quad_114150 { s32 a, b, c, d; };
struct Tag_114150 { s32 tag; };

void* func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, s32 n);
void func_0011B5F0(void* q, s32 flag);

// Calls the common builder with kind 0x63 and returns its first argument.
void* func_00117910(void* ret, s32 a1, void* src, s32 a3, s32 kind);

// Calls the common builder with kind 0x64 and returns its first argument.
void* func_00117910(void* ret, s32 a1, void* src, s32 a3, s32 kind);

// Calls the common builder with kind 0x65 and returns its first argument.
void* func_00117910(void* ret, s32 a1, void* src, s32 a3, s32 kind);

// Calls the common builder with kind 0x66 and returns its first argument.
void* func_00117910(void* ret, s32 a1, void* src, s32 a3, s32 kind);

struct Handle_1141B8 { s32 word; u8 pad[12]; };

void func_0011B008(Handle_1141B8* h);
void func_0011B018(void* dst, Handle_1141B8* src);
void func_0011B060(Handle_1141B8* h, int mode);
void func_0011B5F0(Handle_1141B8* h, int flag);

struct Handle_114220 { s32 word; u8 pad[12]; };

void func_0011B008(Handle_114220* h);
void func_0011B018(void* dst, Handle_114220* src);
void func_0011B060(Handle_114220* h, int mode);
void func_0011B5F0(Handle_114220* h, int flag);

struct Entry_1156B0 { u8 pad0[4]; s32 index; u8 pad1[4]; s32 value; };
struct Var_1156B0 { s32 tag; s32 value; u8 pad[8]; };

void* func_0011B008(void* self);
void func_0011B538(void* self, s32 n);
void func_0011B018(void* out, void* src);
void func_0011B060(void* self, s32 mode);
void func_001C0C08(s32 index, s32 value);

struct Entry_115710 { s32 tag; s32 word; };
struct Var_115710 { s32 tag; f32 value; u8 pad[8]; };

void* func_0011C748();
void func_0011B9A8(void* out, void* src);
void func_0011B0A8(void* dst, void* src);
void func_0011B060(void* self, s32 mode);
void func_0011B7D0(void* self, void* ptr);
void func_0011B018(void* out, void* src);
void* func_0011B008(void* self);

struct Entry_1157E0 { s32 tag; s32 word; };
struct Var_1157E0 { s32 tag; f32 value; u8 pad[8]; };

void* func_0011C858();
void func_0011B9A8(void* out, void* src);
void func_0011B0A8(void* dst, void* src);
void func_0011B060(void* self, s32 mode);
void func_0011B818(void* self, void* ptr);
void func_0011B018(void* out, void* src);
void* func_0011B008(void* self);

union Word_115B78 { s32 i; f32 f; };
struct Entry_115B78 { s32 tag; Word_115B78 word; };
struct Var_115B78 { s32 tag; f32 value; u8 pad[8]; };

void* func_0011B008(void* self);
void func_0011B018(void* out, void* src);
void func_0011B060(void* self, s32 mode);
void func_001F66F8(s32 v);

struct Quad_1146E0 { s32 a, b, c, d; };
struct Src_1146E0 { s32 pad0; Quad_1146E0* other; };

void func_0011B008(Quad_1146E0* q);
void func_0011B018(void* dst, Quad_1146E0* src);
void func_0011B060(Quad_1146E0* q, int mode);
void func_0011B0A8(Quad_1146E0* a, Quad_1146E0* b);

struct Quad_147B8 { s32 a, b, c, d; };
struct Args_147B8 { s32 pad0; Quad_147B8* p; Quad_147B8 q; };

void func_0011B008(Quad_147B8* q);
void func_0011B018(void* dst, Quad_147B8* src);
void func_0011B060(Quad_147B8* q, int mode);
void func_0011B0A8(Quad_147B8* a, Quad_147B8* b);
void func_0011B538(Quad_147B8* q, int n);

void* func_001147B8(void* self, s32 u1, void* src, s32 u3, s32 mode);

struct Src_116A88 { s32 pad0; void* p; };
struct Tmp_116A88 { u8 bytes[0x10]; };

void* func_0011B008(void* obj);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);
void func_0011B740(void* a, void* b);
void* func_0011C508(void);
void func_00188FD8(void* a, void* b);

struct Src_116B08 { s32 pad0; void* p; };
struct Tmp_116B08 { u8 bytes[0x10]; };
struct Vec_116B08 { f32 v[4]; };

void* func_0011B008(void* obj);
void* func_0011C508(void);
void func_0011B740(void* a, void* b);
void func_00188D28(void* a, void* b, void* c);
void func_0011B6C0(void* a, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

struct Src_116C80 { s32 pad0; void* p; };
struct Tmp_116C80 { u8 bytes[0x10]; };
struct Vec_116C80 { u8 bytes[0x30]; };

void* func_0011B008(void* obj);
void* func_0011C618(void);
void func_00189378(void* sub, s32 zero, void* out);
void func_00188B08(void* a, void* b, void* c);
void func_0011B788(void* obj, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

struct Coef_116D20 { f32 a; f32 b; f32 c; };
struct Src_116D20 { s32 pad0; Coef_116D20* coef; };
struct Tmp_116D20 { u8 bytes[0x10]; };
struct Vec_116D20 { f32 v[4]; };

void* func_0011B008(void* obj);
void func_0011B9A8(void* out, void* src);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

struct Quad_1148B8 { s32 a, b, c, d; };
struct Node_1148B8 { s32 a, b; Node_1148B8* next; };
struct Rec_1148B8 { s32 tag; Node_1148B8* head; };

void func_0011B008(Quad_1148B8* q);
void func_0011B570(Quad_1148B8* q, int n);
void func_0011B018(void* self, Quad_1148B8* q);
void func_0011B060(Quad_1148B8* q, int mode);

struct Quad_114950 { s32 a, b, c, d; };
struct Node_114950 { s32 a, b; Node_114950* next; };
struct Sub_114950 { s32 pad; s32 idx; };
struct Rec_114950 { s32 tag; Node_114950* head; Sub_114950 sub; };

void func_0011B008(Quad_114950* q);
void func_0011B538(Quad_114950* q, int n);
void func_0011B0A8(Quad_114950* a, Node_114950* b);
void func_0011B018(void* self, Quad_114950* q);
void func_0011B060(Quad_114950* q, int mode);

struct Vec_116EA8 { f32 x, y, z, w; };

void* func_0011C748();
void* func_0011B008(void* v);
void* func_0011B9A8(void* out, u8* src);
void func_0011B060(void* v, int mode);
void func_0011B018(void* dst, void* src);
void func_0011B7D0(void* self, void* ptr);
void func_001EB018(void* a0, f32 x, f32 y, f32 z, f32 w);

struct Vec_116FE8 { f32 x, y, z, w; };
struct Src_116FE8 { s32 pad0; void* p4; };

void* func_0011B008(void* v);
void* func_0011B9A8(void* out, u8* src);
f32 func_001EB0F8(void* span, f32 x);
void* func_0011B5B0(void* obj, f32 x);
void func_0011B060(void* v, int mode);
void func_0011B018(void* dst, void* src);

struct Quad_1143C8 { s32 a, b, c, d; };

void func_0011B008(Quad_1143C8* q);
void func_0011B5F0(Quad_1143C8* q, int flag);
void func_0011B018(void* out, Quad_1143C8* q);
void func_0011B060(Quad_1143C8* q, int mode);

struct Quad_114438 { s32 a, b, c, d; };

void func_0011B008(Quad_114438* q);
void func_0011B5F0(Quad_114438* q, int flag);
void func_0011B018(void* out, Quad_114438* q);
void func_0011B060(Quad_114438* q, int mode);

struct Pair_115440 { s32 a; s32 b; };
struct Frame_115440 { s32 w[4]; };

void func_0011B008(Frame_115440* f);
void func_0011B018(void* dst, Frame_115440* src);
void func_0011B060(Frame_115440* f, s32 mode);
void func_0011B9A8(Frame_115440* out, Pair_115440* src);
void func_0011B0A8(Frame_115440* a, Frame_115440* b);
void func_0011B740(Frame_115440* a, f32* out);
void* func_0011C508(void);

union Cell_115C00 { f32 f; s32 i; };
struct Tagged_115C00 { s32 tag; Cell_115C00 cell; };
struct Pair_115C00 { Tagged_115C00 x; Tagged_115C00 y; };
struct Frame_115C00 { s32 w[4]; };

void func_0011B008(Frame_115C00* f);
void func_0011B018(void* dst, Frame_115C00* src);
void func_0011B060(Frame_115C00* f, s32 mode);
void func_0011B5B0(Frame_115C00* f, f32 v);
f32 func_001EAAE0(f32 a, f32 b);

struct Tmp_117180 { s32 w[4]; };
struct Src_117180 { s32 pad0; f32 v; };

void* func_0011B008(void* self);
void func_0011B570(void* self, s32 n);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* self, s32 n);

struct Tmp_117260 { s32 w[4]; };
struct Src_117260 { s32 pad0; f32 v; };

void* func_0011B008(void* self);
void func_0011B570(void* self, s32 n);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* self, s32 n);

struct Quad_1144A0 { s32 a, b, c, d; };

void func_0011B008(Quad_1144A0* q);
void func_0011B5F0(Quad_1144A0* q, int flag);
void func_0011B018(void* out, Quad_1144A0* q);
void func_0011B060(Quad_1144A0* q, int mode);

struct Quad_1145C8 { s32 a, b, c, d; };

void func_0011B008(Quad_1145C8* q);
void func_0011B5F0(Quad_1145C8* q, int flag);
void func_0011B018(void* out, Quad_1145C8* q);
void func_0011B060(Quad_1145C8* q, int mode);

union Cell_115CA0 { f32 f; s32 i; };
struct Tagged_115CA0 { s32 tag; Cell_115CA0 cell; };
struct Frame_115CA0 { s32 w[4]; };
typedef f32 (*FloatFn_115CA0)(f32 v);
// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern Fn_Table D_00259938[];

void func_0011B008(Frame_115CA0* f);
void func_0011B018(void* dst, Frame_115CA0* src);
void func_0011B060(Frame_115CA0* f, s32 mode);
void func_0011B5B0(Frame_115CA0* f, f32 v);

union Cell_115D48 { f32 f; s32 i; };
struct Tagged_115D48 { s32 tag; Cell_115D48 cell; };

void* func_00115CA0(void* self, Tagged_115D48* src, s32 index);

union Num_1172C8 { s32 i; f32 f; };
struct Value_1172C8 { s32 type; Num_1172C8 num; s32 pad8; s32 padC; };
struct Quad_1172C8 { s32 type; Num_1172C8 num; s32 c; s32 d; };

void* func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, s32 mode);
void func_0011B570(void* q, s32 v);

struct Quad_114300 { s32 a, b, c, d; };
struct Src_114300 { s32 flag; };

void func_0011B008(Quad_114300* q);
s32 func_0011B5F0(Quad_114300* q, s32 flag);
void func_0011B018(void* dst, Quad_114300* src);
void func_0011B060(Quad_114300* q, int mode);

struct Quad_114360 { s32 a, b, c, d; };
struct Src_114360 { s32 flag; };

void func_0011B008(Quad_114360* q);
s32 func_0011B5F0(Quad_114360* q, s32 flag);
void func_0011B018(void* dst, Quad_114360* src);
void func_0011B060(Quad_114360* q, int mode);

struct Quad_114638 { s32 a, b, c, d; };
struct Node_114638 { u8 pad[8]; s32 val; };
struct Src_114638 { u8 pad[8]; s32 kind; s32 val; };
struct Sub_114638 { s32 pad; s32 val; };

void func_0011B008(Quad_114638* q);
void func_0011B0A8(void* node, Src_114638* src);
void func_0011B6C0(Quad_114638* q, void* node);
void func_0011B018(void* dst, Quad_114638* src);
void func_0011B060(Quad_114638* q, int mode);

struct Tmp_115398 { u8 bytes[0x10]; };

void* func_0011B008(void* obj);
void func_0011B0A8(void* a, void* b);
void func_0011A080(void* t, void* n, s32 c);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

struct Quad_1169E8 { s32 a, b, c, d; };
struct __attribute__((aligned(16))) Block_1169E8 { s32 w[16]; };
struct Src_1169E8 { s32 f0; Block_1169E8* f4; };

void func_0011B008(Quad_1169E8* q);
void func_0011B018(void* dst, Quad_1169E8* src);
void func_0011B060(Quad_1169E8* q, int mode);
void* func_0011C618(void);
void func_001884C0(void* p);
void func_0011B788(Quad_1169E8* q, void* b);

struct Quad_117E20 { s32 a, b, c, d; };

void func_0011B008(Quad_117E20* q);
void func_0011B018(void* dst, Quad_117E20* src);
void func_0011B060(Quad_117E20* q, int mode);
s32 func_0011B8A8(Quad_117E20* q, s32 v);
void* func_001925F0(void);

struct Quad_114518 { s32 a, b, c, d; };
struct Frame_114518 { Quad_114518 q; f32 out[3]; };
union Bits_114518 { s32 i; f32 f; };
struct Elem_114518 { s32 tag; Bits_114518 v; };

void func_0011B008(Quad_114518* q);
void func_0011B018(void* dst, Quad_114518* src);
void func_0011B060(Quad_114518* q, int mode);
s32 func_001EAC68(f32 a, f32 b, f32 c);
s32 func_0011B5F0(Quad_114518* q, s32 flag);

struct Quad_116520 { s32 a, b, c, d; };
struct Value_116520 { s32 tag; f32 payload; };
struct Obj4_116520 { s32 pad0; void* f4; };
struct Src_116520 { s32 pad0; void* f4; s32 pad8; void* fC; Value_116520 f10; void* f18; void* f1C; };
struct Frame_116520 { Quad_116520 q; Value_116520 v; };

void func_0011B008(Quad_116520* q);
void func_0011B018(void* dst, Quad_116520* src);
void func_0011B060(void* q, int mode);
void func_0011B9A8(void* out, void* src);
void func_0011B740(Quad_116520* q, void* p);
void* func_0011C508(void);
void func_001EDEF0(void* a0, void* a1, void* a2, void* a3, f32 f);

struct Quad_117080 { s32 a, b, c, d; };
struct Value_117080 { s32 tag; f32 payload; };
struct Src_117080 { s32 pad0; void* f4; Value_117080 f8; };
struct Frame_117080 { Quad_117080 q; Value_117080 v; };

void func_0011B008(Quad_117080* q);
void func_0011B018(void* dst, Quad_117080* src);
void func_0011B060(void* q, int mode);
void func_0011B9A8(void* out, void* src);
s32 func_001EB050(void* target, f32 scale);
s32 func_0011B5F0(Quad_117080* q, s32 flag);

struct Quad_117118 { s32 a, b, c, d; };
struct In_117118 { s32 pad0; f32 f4; };

void* func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, int mode);
void func_0011B570(void* q, s32 v);

struct Quad_117BC8 { s32 a, b, c, d; };
struct In_117BC8 { u8 pad0[4]; s32 w4; s32 w8; s32 wc; };

void func_0011B008(Quad_117BC8* q);
s32 func_0011B8A8(Quad_117BC8* q, s32 v);
void func_0011B018(void* dst, Quad_117BC8* src);
void func_0011B060(Quad_117BC8* q, int mode);
s32 func_0015A418(void* host, s32 a1, s32 a2, s32 ctx);

struct Quad_117D00 { s32 a, b, c, d; };
struct In_117D00 { u8 pad0[4]; s32 w4; s32 w8; s32 wc; };

void func_0011B008(Quad_117D00* q);
s32 func_0011B8A8(Quad_117D00* q, s32 v);
void func_0011B018(void* dst, Quad_117D00* src);
void func_0011B060(Quad_117D00* q, int mode);
s32 func_0015A418(void* host, s32 a1, s32 a2, s32 ctx);

struct Quad_117E78 { s32 a, b, c, d; };

s32 func_0011B008(Quad_117E78* q);
void func_0011B018(void* dst, Quad_117E78* src);
void func_0011B060(Quad_117E78* q, int mode);
void func_0011B8A8(Quad_117E78* q, s32 v);

struct Quad_117ED0 { s32 a, b, c, d; };

s32 func_0011B008(Quad_117ED0* q);
void func_0011B018(void* dst, Quad_117ED0* src);
void func_0011B060(Quad_117ED0* q, int mode);
void func_0011B8A8(Quad_117ED0* q, s32 v);

struct Quad_114740 { s32 a, b, c, d; };
struct Inner_114740 { u8 pad[8]; s32 val; };
struct Src_114740 { u8 pad[4]; Inner_114740* inner; };

s32 func_0011B008(Quad_114740* q);
void func_0011B6C0(Quad_114740* q, s32 v);
void func_0011B538(Quad_114740* q, s32 n);
void func_0011B018(void* dst, Quad_114740* src);
void func_0011B060(Quad_114740* q, int mode);

struct Tmp_116978 { u8 bytes[0x10]; };
struct __attribute__((aligned(16))) Quad_116978 { s32 a, b, c, d; };
struct Src_116978 { s32 pad0; void* p; };

void* func_0011B008(void* obj);
void* func_0011C508(void);
s32 func_0011B740(Tmp_116978* a, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

struct Node_117360 { s32 tag; union { s32 i; f32 f; } v; Node_117360* next; Node_117360* child; };

void* func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, int mode);
s32 func_0011B0A8(Node_117360* a, void* b);

struct Node_117478 { s32 tag; union { s32 i; f32 f; } v; Node_117478* next; Node_117478* child; };

void* func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, int mode);
s32 func_0011B0A8(Node_117478* a, void* b);

// NEAR: the lui/lwc1 pair of D_0026185C uses $v1 in retail, $v0 here (scalar and array externs and a local float all tried).

struct Quad_117610 { s32 a, b, c, d; };

extern f32 D_0026185C;

s32 func_0011B008(Quad_117610* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, int mode);
void func_0011B5B0(Quad_117610* q, f32 v);

struct __attribute__((aligned(16))) Quad_115510 { f32 f[4]; };
struct Node_115510 { s32 pad0; Quad_115510* f4; Node_115510* f8; };
struct List_115510 { s32 pad0; Node_115510* f4; };

s32 func_0011B008(Quad_115510* q);
void func_0011B018(void* out, Quad_115510* q);
void func_0011B060(Quad_115510* q, s32 mode);
void func_0011B0A8(Quad_115510* a, Quad_115510* b);
void func_0011B788(Quad_115510* q, Quad_115510* v);
void func_0011B9A8(Quad_115510* out, Node_115510* n);
void func_001884C0(Quad_115510* v);

struct Quad_117668;
void func_0011B008(Quad_117668* q);
void func_0011B060(Quad_117668* q, s32 mode);
struct Quad_117668 {
    s32 a, b, c, d;
    Quad_117668() { func_0011B008(this); }
    ~Quad_117668() { func_0011B060(this, 2); }
};
struct QP_117668 { s32 a, b, c, d; };
struct TQ_117668 { s32 a; f32 f4; s32 c, d; };
struct Node_117668 { s32 type; Node_117668* head; Node_117668* next; };
struct Ent_117668 { s32 pad0; Node_117668* node; };
struct Src_117668 { Ent_117668 e[1]; };

void func_0011B008(QP_117668* q);
void func_0011B060(QP_117668* q, s32 mode);
void func_0011B6C0(QP_117668* q, Node_117668* v);
s32 func_0011A498(void* a, s32 b, s32 c, QP_117668* d);
void func_0011A400(TQ_117668* self, void* table, s32 key, QP_117668* item);
void func_0011B018(void* out, Quad_117668* q);
void func_0011B060(TQ_117668* q, s32 mode);
void func_0011B538(Node_117668* q, s32 n);
void func_0011B538(Quad_117668* q, s32 n);
void func_0011B5B0(Node_117668* obj, f32 x);
void func_0011B6C0(Node_117668* q, Node_117668* v);
void func_0011B6C0(Quad_117668* q, Node_117668* v);
void func_0011B700(Node_117668* n, s32 v);
void func_0011B9A8(TQ_117668* t, Src_117668* s);
s32 func_0011A498(void* a, s32 b, s32 c, Quad_117668* d);
void func_0011A400(TQ_117668* self, void* table, s32 key, Quad_117668* item);
extern s32 D_00259DE8;

struct __attribute__((aligned(16))) Quad_1149F0 { s32 a, b, c, d; };
struct Pair_1149F0 { s32 a, b; };
struct Frame_1149F0 {
    Quad_1149F0 A;
    Quad_1149F0 B;
    Pair_1149F0 C[2];
    Quad_1149F0 D;
};
struct Node_1149F0 { s32 pad0; s32 pad1; Node_1149F0* next; };
struct Src_1149F0 { s32 pad0; s32 pad1; s32 kind; Node_1149F0* head; };

void func_0011B008(Pair_1149F0* obj);
void func_0011B008(Quad_1149F0* obj);
s32 func_0011B5F0(Quad_1149F0* q, s32 flag);
void func_0011B0A8(Pair_1149F0* a, void* b);
void func_0011B0A8(Quad_1149F0* a, void* b);
void func_00113E48(Quad_1149F0* a, s32 mode, Pair_1149F0* b, void* c);
void func_0011B018(void* dst, Quad_1149F0* src);
void func_0011B060(Pair_1149F0* obj, s32 n);
void func_0011B060(Quad_1149F0* obj, s32 n);

struct Quad_117C48 { s32 a, b, c, d; };
struct In_117C48 { u8 pad0[4]; s32 w4; s32 w8; s32 wc; };

s32 func_0011B008(Quad_117C48* q);
void func_00117AF0(Quad_117C48* t, s32 a, void* b);
s32 func_0011B0A8(Quad_117C48* a, Quad_117C48* b);
s32 func_0011B060(Quad_117C48* q, int mode);
s32 func_0011B018(void* dst, Quad_117C48* src);
s32 func_0015A198(void* host, s32 a1, s32 a2, void* ctx, s32 a4, void* a5);

struct __attribute__((aligned(16))) Quad_1159B8 { s32 a, b, c, d; };
struct Idx_1159B8 { s32 f0; s32 f4; Idx_1159B8* f8; };
struct __attribute__((aligned(16))) Arr_1159B8 { f32 v[4]; };
struct Mat_1159B8 { Arr_1159B8 row[4]; };
struct Src_1159B8 { s32 type; f32* f4; s32 f8; Idx_1159B8* fC; };

void func_0011B008(Quad_1159B8* q);
void func_0011B018(Quad_1159B8* out, Quad_1159B8* q);
void func_0011B060(Quad_1159B8* q, s32 mode);
void func_0011B5B0(Quad_1159B8* q, f32 x);
void func_0011B740(Quad_1159B8* q, Arr_1159B8* c);

struct Quad_117AF0 { u8 pad0[16]; };
struct Node_117AF0 { u8 pad0[8]; Node_117AF0* next; };

void func_0011B008(Quad_117AF0* q);
void func_0011B6C0(Quad_117AF0* q, Node_117AF0* n);
void func_0011B8A8(Node_117AF0* n, s32 v);
void func_0011B538(Quad_117AF0* q, s32 n);
void func_0011B018(void* dst, Quad_117AF0* src);
void func_0011B060(Quad_117AF0* q, s32 mode);

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_001EA408();
void func_00204F68();
void func_00205210();
void func_00205400();
void func_002054F0();
void func_00205578();
void func_00205678();
void func_00206180();
Fn_Table D_00259938[8] = { (Fn_Table)func_00206180, (Fn_Table)func_00205400, (Fn_Table)func_00205210, (Fn_Table)func_002054F0, (Fn_Table)func_00205678, (Fn_Table)func_00205578, (Fn_Table)func_00204F68, (Fn_Table)func_001EA408 };
INCLUDE_DATA(D_00259958);
INCLUDE_DATA(D_00259DE8);
Gc_259F38 D_00259F38;

struct Quad_117D78 { s32 a, b, c, d; };
struct In_117D78 { u8 pad0[4]; s32 w4; s32 w8; s32 wc; };
struct Host_117D78;

s32 func_0011B008(Quad_117D78* q);
void func_00117AF0(Quad_117D78* t, s32 a, void* b);
s32 func_0011B0A8(Quad_117D78* a, Quad_117D78* b);
s32 func_0011B060(Quad_117D78* q, int mode);
s32 func_0011B018(void* dst, Quad_117D78* src);
s32 func_0015A198(Host_117D78* host, s32 a1, s32 a2, void* ctx, s32 a4, void* a5);

struct Quad_117F28 { s32 a, b, c, d; };
struct In_117F28 { u8 pad0[4]; s32 w4; s32 w8; s32 wc; };
struct Host_117F28;

s32 func_0011B008(Quad_117F28* q);
void func_00117AF0(Quad_117F28* t, s32 a, void* b);
s32 func_0011B0A8(Quad_117F28* a, Quad_117F28* b);
s32 func_0011B060(Quad_117F28* q, int mode);
s32 func_0011B018(void* dst, Quad_117F28* src);
s32 func_0015A4F0(Host_117F28* host, s32 a1, s32 a2, void* ctx, s32 a4, void* a5);

struct Quad_117910 { u8 b[16]; };
struct Src_117910 { u8 pad0[4]; s32 f4; u8 pad8[4]; s32 fC; u8 f10[4]; };
struct Sub_117910 { u8 pad[1]; };

void func_0011B008(Quad_117910* q);
void func_0011B018(void* dst, Quad_117910* src);
void func_0011B060(Quad_117910* q, s32 mode);
void func_0011B0A8(Quad_117910* a, Quad_117910* b);
void* func_001C2238(Sub_117910* self, s32 a1, s32 a2, void* a3);
void* func_001C2320(Sub_117910* self, s32 a1, s32 a2, void* a3);
void* func_001C22B8(Sub_117910* self, s32 a1, s32 a2, void* a3);
void* func_001C21A0(Sub_117910* self, s32 a1, s32 a2);

struct Val_1151C0;
struct Obj_1151C0;

void func_0011B008(Val_1151C0* v);
void func_0011B018(Val_1151C0* dst, const Val_1151C0* src);
void func_0011B060(Val_1151C0* v, s32 mode);
Val_1151C0& func_0011B0A8(Val_1151C0* dst, const Val_1151C0& src);
void func_0011B6C0(Val_1151C0* v, Val_1151C0* target);

struct Val_1151C0 {
    s32 tag;
    Val_1151C0* f4;
    Val_1151C0* f8;
    Val_1151C0() { func_0011B008(this); }
    Val_1151C0(const Val_1151C0& o) { func_0011B018(this, &o); }
    ~Val_1151C0() { func_0011B060(this, 2); }
};

struct Cell_1151C0 : Val_1151C0 {
    Cell_1151C0() { tag = -1; }
};

struct Obj_1151C0 {
    s32 f0;
    s32 f4;
    Val_1151C0 m;
};

Val_1151C0 func_0011A080(Val_1151C0* expr, s32 c);

struct Val_114D18;

void func_0011B008(Val_114D18* v);
void func_0011B018(Val_114D18* dst, const Val_114D18* src);
void func_0011B060(Val_114D18* v, s32 mode);
Val_114D18& func_0011B0A8(Val_114D18* dst, const Val_114D18& src);
void func_0011B6C0(Val_114D18* v, Val_114D18* target);

struct Val_114D18 {
    s32 tag;
    Val_114D18* f4;
    Val_114D18* f8;
    Val_114D18() { func_0011B008(this); }
    Val_114D18(const Val_114D18& o) { func_0011B018(this, &o); }
    ~Val_114D18() { func_0011B060(this, 2); }
};

struct Cell_114D18 : Val_114D18 {
    Cell_114D18() { tag = -1; }
};

struct Obj_114D18 {
    s32 f0;
    s32 f4;
    Val_114D18 m;
};

Val_114D18 func_0011A080(Val_114D18* expr, s32 c);

struct Val_114F48;

void func_0011B008(Val_114F48* v);
void func_0011B018(Val_114F48* dst, const Val_114F48* src);
void func_0011B060(Val_114F48* v, s32 mode);
Val_114F48& func_0011B0A8(Val_114F48* dst, const Val_114F48& src);
void func_0011B6C0(Val_114F48* v, Val_114F48* target);
struct Node_116600;
struct Node_11AF28* func_0011AF28(void);

struct Val_114F48 {
    s32 tag;
    Val_114F48* f4;
    Val_114F48* f8;
    Val_114F48();
    Val_114F48(const Val_114F48& o) { func_0011B018(this, &o); }
    ~Val_114F48();
};

struct Cell_114F48 {
    Val_114F48 v;
    Cell_114F48() { v.tag = -1; }
};

struct Obj_114F48 {
    s32 f0;
    s32 f4;
    Val_114F48 m;
};

Val_114F48 func_0011A080(Val_114F48* expr, s32 c);

// A count followed by that many values.
struct IntList { s32 count; s32 items[1]; };

// A record that keeps a stack of values at 0x708.
struct StackAt708 { u8 pad[0x708]; s32 count; s32 items[1]; };

struct Vec_1188F0 { f32 x, y, z, w; };
struct Src_1188F0 { s32 pad0; void* p4; };

void* func_0011B008(void* self);
void func_0011B9A8(void* out, void* src);
void func_001566C8(void* obj, f32 f);
void func_0011B060(void* self, s32 n);
void func_0011B538(void* self, s32 k);
void func_0011B018(void* dst, void* src);

struct __attribute__((aligned(16))) Quad_119A58 { s32 w[4]; };
struct Node_119A58 { s32 pad[2]; Node_119A58* next; };

void func_0011B008(Quad_119A58* q);
void func_0011B018(void* out, Quad_119A58* q);
void func_0011B060(Quad_119A58* q, s32 mode);
void func_0011B0A8(Quad_119A58* a, Quad_119A58* b);
void func_0011A080(Quad_119A58* t, Node_119A58* n, s32 c);

void* func_0011A4D8(void* a, s32 b, s32 c, void* d);
void func_0011B0A8(void* a, void* b);

void func_0018D778(void);

struct Stack_11A790 { u8 pad[0xF0C]; s32 count; s32 items[1]; };

extern u8 D_0025C2B0[];
void* func_0011C240(void* p);
void* func_001F5C0C(void* p, s32 value, s32 size);

void func_0011B418(void* self);

void func_0011B418(void* self);

void func_0011B418(void* self);

void func_0011B0A8(void* a, void* b);

struct Node_11AF28 {
    s32 kind;
    s32 value;
    Node_11AF28* child;
};
typedef Node_11AF28 Node_11AEB8;

void func_0011B258(void* src, void* dst, void* arg);
Node_11AEB8* func_0011AF28(void);

extern u8 D_0025C250[];

void* func_0011C240(void* pool);
void* func_001F5C0C(void* dst, s32 value, s32 size);
Node_11AF28* func_0011B008(Node_11AF28* self);

void func_0011B060(void* self, s32 flags);

void func_0011B418(void* self);
void func_0018D778(void* self);

extern u8 D_0025C250[];
extern u8 D_0025C270[];
extern u8 D_0025C290[];
extern u8 D_0025C2B0[];
extern u8 D_0025C2D0[];

void func_0011C2A0(void* p);

extern u8 D_0025C2D0[];

void* func_0011C240(void* p);
void* func_001F5C0C(void* p, s32 v, s32 n);

s32 func_0011C498(void);
void func_0011C418(void* obj, s32 value, s32 zero);

void* func_0018D5C0(s32 size);
void* func_001F5C0C(void* p, s32 value, s32 size);

extern u8 D_0025C250[];
extern u8 D_0025C270[];
extern u8 D_0025C290[];
extern u8 D_0025C2B0[];
extern u8 D_0025C2D0[];

void func_0011A6A8(void* p);
void func_0011A670(void);
void func_0011AF78(void* self);
void func_0011C4E8(void);
void func_0011C128(void* obj, s32 count, s32 size);
void func_0011CA90(void);

struct Quad_1180C0 { s32 a, b, c, d; };
struct Frame_1180C0 { Quad_1180C0 q; Quad_1180C0 t; s32 a; s32 b; };
union Raw_1180C0 { s32 i; f32 f; };
struct In_1180C0 { u8 pad0[4]; s32 w4; s32 kind; Raw_1180C0 raw; };

void func_0011B008(Quad_1180C0* q);
void func_0018D608(void);
void func_0018D6F0(void);
void func_001DC4D0(void* self, f32 scale, s32 p1, s32 p2, s32 p3, s32 p4, s32* o1, s32* o2);
void func_00117AF0(Quad_1180C0* t, s32 a, s32 b);
void func_0011B0A8(Quad_1180C0* a, Quad_1180C0* b);
void func_0011B060(Quad_1180C0* q, int mode);
void func_0011B018(void* dst, Quad_1180C0* src);

struct Quad_1183B8 { s32 a, b, c, d; };
struct Frame_1183B8 { Quad_1183B8 q; Quad_1183B8 t; };

void func_0011B008(Quad_1183B8* q);
void func_00118198(Quad_1183B8* dst, s32 code, s32 x, s32 y, s32 z);
void func_0011B0A8(Quad_1183B8* a, Quad_1183B8* b);
void func_0011B060(Quad_1183B8* q, int mode);
void func_0011B018(void* dst, Quad_1183B8* src);

struct Quad_118458 { s32 a, b, c, d; };
struct Frame_118458 { Quad_118458 q; Quad_118458 t; };

void func_0011B008(Quad_118458* q);
void func_00118198(Quad_118458* dst, s32 code, s32 x, s32 y, s32 z);
void func_0011B0A8(Quad_118458* a, Quad_118458* b);
void func_0011B060(Quad_118458* q, int mode);
void func_0011B018(void* dst, Quad_118458* src);

struct Blob_119FA0 { s32 w[4]; };
struct Inner_119FA0 { u8 pad0[4]; s32 id; };
struct Mid_119FA0 { u8 pad0[8]; Inner_119FA0* inner; };
struct Outer_119FA0 { u8 pad0[4]; Mid_119FA0* mid; };

void func_0011B008(Blob_119FA0* b);
void func_0011B018(void* dst, Blob_119FA0* src);
void func_0011B060(Blob_119FA0* b, s32 mode);
void func_0011B0A8(Blob_119FA0* a, void* b);
void func_0011B538(Blob_119FA0* b, s32 n);
void func_001C13E8(void* dst, s32 id, u8* ctx);
void* func_001C1390(s32 id, u8* ctx);
void func_0011A338(void* list, void* value);

struct Slot_11A328 { s32 flag; s32 value; };

struct Blob_11A358 { s32 w[4]; };
struct Node_11A358 { s32 kind; u8 body[8]; Node_11A358* next; };
struct Owner_11A358 { u8 pad0[0x14]; Node_11A358* head; };

void func_0011B008(Blob_11A358* b);
void func_0011B018(void* dst, Blob_11A358* src);
void func_0011B060(Blob_11A358* b, s32 mode);
s32 func_0011B0A8(u8* a, void* b);
void func_0011B538(Blob_11A358* b, s32 n);
s32 func_0011C498(void);

struct Blob_11A400 { s32 w[4]; };

void func_0011B008(Blob_11A400* b);
void func_0011B018(void* dst, Blob_11A400* src);
void func_0011B060(Blob_11A400* b, s32 mode);
void func_0011B0A8(void* a, void* b);
void func_0011B538(Blob_11A400* b, s32 n);
void* func_0011A4D8(void* table, void* key, s32 mode);

struct Stack_11A7D8 { u8 pad[0x1310]; s32 count; s32 items[1]; };

void func_0011B418(void* self);
void func_0011B4A8(void* self);

void func_0011B418(void* self);

void func_0011B418(void* self);

struct Value_11B008 { s32 tag; s32 payload; };

void func_0011B008(Value_11B008* v);
void func_0011B018(Value_11B008* dst, Value_11B008* src);
void func_0011B060(Value_11B008* v, int mode);
void func_0011B5B0(Value_11B008* v, f32 f);

struct Quad_118608 { s32 a, b, c, d; };
struct Frame_118608 { Quad_118608 q; };
struct In_118608 { u8 pad0[4]; s32 f4; u8 pad8[4]; s32 fC; u8 pad10[4]; s32 f14; };

void func_0011B008(Quad_118608* q);
void* func_0011C618(void);
void func_00128150(s32 a, s32 b, s32 c, void* d);
void func_001884C0(void* p);
void func_0011B788(Quad_118608* q, void* b);
void func_0011B018(void* dst, Quad_118608* src);
void func_0011B060(Quad_118608* q, int mode);

struct Quad_118720 { s32 a, b, c, d; };
struct Frame_118720 { Quad_118720 q; s32 n; s32 pad[3]; };
struct In_118720 { u8 pad0[4]; s32 f4; u8 pad8[4]; s32 fC; };

void func_0011B008(Quad_118720* q);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void func_0011B570(Quad_118720* q, s32 n);
void func_001BF718(void* slot);
void func_0011B018(void* dst, Quad_118720* src);
void func_0011B060(Quad_118720* q, int mode);

// A node of a keyed list: the key, a value whose address is returned, and the next node at 0xC.
struct Node_11A4D8 { s32 key; s32 value; s32 pad8; struct Node_11A4D8* next; };

// A tree node: count and child pointers at 0x0 and 0x4, a list head at 0x14, a busy flag at 0x18.
struct Tree_11A4D8 {
    s32 count;
    struct Tree_11A4D8* items[4];
    struct Node_11A4D8* head;
    s32 flag;
};

// The same tree node as func_0011A4D8: count and child pointers, a list head at 0x14, a flag at 0x18.
struct Node_11A5B0;
struct Tree_11A5B0 {
    s32 count;
    struct Tree_11A5B0* items[4];
    struct Node_11A5B0* head;
    s32 flag;
};

void func_0018D800(void* dst, void* src, s32 bytes);
s32 func_0011C498(void);
void func_0011C418(void* a, void* b, void* c);

void func_0011B418(void* self);

void func_0011B418(void* self);

struct Vec_118850 { f32 x, y, z, w; };
struct Src_118850 { s32 pad0; s32 n; };

void* func_0011B008(void* self);
void func_0011B9A8(void* out, void* src);
void func_0016EC38(void* p, s32 n, f32 f);
void func_0011B060(void* self, s32 mode);
void func_0011B018(void* dst, void* src);

extern u8 D_00262C70[];

extern u8 D_0025C270[];
void* func_0011C240(void* p);

struct Stack_11A7B8 { u8 pad[0x1310]; s32 count; s32 items[1]; };

void func_0011B418(void* self);

void func_0011B418(void* self);

void func_0011B018(void* dst, void* src);

// A 128-bit value, copied as one quadword.
typedef u64 Quad_118D10 __attribute__((mode(TI)));

// Copies the quadword at src into out and returns out.

// A 128-bit value, stored as one quadword.
typedef u64 Quad_118D20 __attribute__((mode(TI)));

// Stores the quadword v into out and returns out.

struct Counters_11A6A8 {
    s32 count;
    u8 pad[0x500];
    s32 count2;
};

void func_0011B418(void* self);

void func_0011B418(void* self);
s32 func_0011C580(u32 addr);

struct Obj_0011A708 { u8 pad[0x504]; s32 count; s32 values[1]; };

struct Obj_0011A728 { u8 pad[0x708]; s32 count; s32 values[1]; };

struct Obj_0011A770 { u8 pad[0xF0C]; s32 count; s32 values[1]; };

s32 func_0011C690(u32 value);

s32 func_0011C7C0(u32 value);

s32 func_0011C8D0(u32 value);

s32 func_0011C9E0(u32 value);

struct Tmp_1184F8 { u8 bytes[0x10]; };
struct Src_1184F8 { s32 pad0; void* a; s32 pad2; s32 b; s32 pad4; void* c; };

void* func_0011B008(void* obj);
void* func_0011C508(void);
s32 func_00128018(void* a, s32 b, void* c, void* d);
void func_0011B740(void* a, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

struct Tmp_118580 { u8 bytes[0x10]; };
struct Src_118580 { s32 pad0; void* a; s32 pad2; s32 b; s32 pad4; void* c; };

void* func_0011B008(void* obj);
void* func_0011C508(void);
s32 func_001280C0(void* a, s32 b, void* c, void* d);
void func_0011B740(void* a, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

struct Tmp_1187E8 { s32 w0; s32 w1; s32 w2; s32 w3; };
struct Src_1187E8 { s32 pad0; void* a; };

void* func_0011B008(void* obj);
void func_001BF788(void* self, s32 n);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

struct Tmp_118D48 { u8 bytes[0x10]; };
struct Src_118D48 { s32 pad0; s32 a; };

void* func_0011B008(void* obj);
s32 func_0011A498(void* a, s32 b, s32 c, void* d);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);

struct __attribute__((aligned(16))) Quad_119AF8 { s32 w[4]; };
struct Node_119AF8 { s32 pad[2]; Node_119AF8* next; };
struct Wrap_119AF8 { s32 pad[2]; Node_119AF8* first; };
struct Owner_119AF8 { s32 pad; Wrap_119AF8* wrap; };

void func_0011B008(Quad_119AF8* q);
void func_0011B538(Quad_119AF8* q, s32 k);
void func_0011A080(Quad_119AF8* t, Node_119AF8* n, s32 c);
void func_0011B0A8(Quad_119AF8* a, Quad_119AF8* b);
void func_0011B060(Quad_119AF8* q, s32 mode);
void func_0011B018(void* dst, Quad_119AF8* src);

// EXACT: callee 0011B008 declared s32 and called as statement.

struct __attribute__((aligned(16))) Quad_118DB8 { s32 w[4]; };
struct Node_118DB8 { s32 pad0; Node_118DB8* f4; Node_118DB8* f8; };

s32 func_0011B008(Quad_118DB8* q);
void func_0011B018(void* out, Quad_118DB8* q);
void func_0011B060(Quad_118DB8* q, s32 mode);
void func_0011B0A8(Quad_118DB8* a, Quad_118DB8* b);
void func_0011B538(Quad_118DB8* q, s32 n);
void func_0011A080(Quad_118DB8* t, Node_118DB8* n, s32 c);
void* func_0011A400(void* self, s32 table, void* key, void* item);

// EXACT: func_0011B008 declared s32, called as statement.

struct __attribute__((aligned(16))) Quad_118E80 { s32 w[4]; };
struct Node_118E80 { s32 pad0; Node_118E80* f4; Node_118E80* f8; };

s32 func_0011B008(Quad_118E80* q);
void func_0011B018(void* out, Quad_118E80* q);
void func_0011B060(Quad_118E80* q, s32 mode);
void func_0011B0A8(Quad_118E80* a, Quad_118E80* b);
void func_0011B538(Quad_118E80* q, s32 n);
void func_0011A080(Quad_118E80* t, Node_118E80* n, s32 c);
void* func_0011A358(void* self, s32 owner, void* kind, void* body);

// EXACT: func_0011B008 declared s32, called as statement.

struct __attribute__((aligned(16))) Quad_119878 { s32 w[4]; };
struct Node_119878 { s32 pad[2]; Node_119878* next; };
struct Wrap_119878 { s32 pad[2]; Node_119878* first; };
struct Owner_119878 { s32 pad; Wrap_119878* wrap; };

s32 func_0011B008(Quad_119878* q);
void func_0011A080(Quad_119878* t, Node_119878* n, s32 c);
void func_0011B0A8(Quad_119878* a, Quad_119878* b);
void func_0011B060(Quad_119878* q, s32 mode);
void func_0011B538(Quad_119878* q, s32 k);
void func_0011B018(void* dst, Quad_119878* src);

// EXACT: func_0011B008 declared s32, called as statement.

struct __attribute__((aligned(16))) Quad_119970 { s32 w[4]; };
struct Item_119970 { s32 tag; Item_119970* child; Item_119970* next; };
struct Wrap_119970 { s32 pad[2]; Item_119970* first; };
struct Owner_119970 { s32 pad; Wrap_119970* wrap; };
struct Rec_119970 { s32 c; Item_119970* head; s32 count; s32 found; Item_119970* after; };

s32 func_0011B008(Quad_119970* q);
void* func_0011AFC8(void);
void func_0011B700(Quad_119970* r, Rec_119970* value);
void func_0011B018(void* dst, Quad_119970* src);
void func_0011B060(Quad_119970* q, s32 mode);

struct Node_11BD28 { s32 key; Value_11B008 value; Node_11BD28* next; };

void func_0011B008(Value_11B008* v);
void func_0011B018(Value_11B008* dst, Value_11B008* src);
void func_0011B060(Value_11B008* v, int mode);
Value_11B008* func_0011B0A8(Value_11B008* dst, Value_11B008* src);
void func_0011B538(Value_11B008* v, s32 tag);

struct Node_119218 { s32 f0; s32 f4; Node_119218* next; };
struct Holder_119218 { s32 f0; s32 f4; Node_119218* head; };
struct Args_119218 { s32 f0; Holder_119218* holder; };

void* func_0011B008(void* p);
void func_0011B5F0(void* p, s32 flag);
void func_0011B060(void* p, s32 flags);
struct Tmp_119218;
void func_0011B018(void* out, void* p);

struct Tmp_119218 {
    s32 tag; s32 value; s32 pad[2];
    ~Tmp_119218() { func_0011B060(this, 2); }
};
struct Cursor_119218 {
    s32 tag; s32 value; s32 pad[2];
    Cursor_119218(const Cursor_119218& o) { func_0011B018(this, (void*)&o); }
    Cursor_119218() { func_0011B008(this); }
    ~Cursor_119218() { func_0011B060(this, 2); }
};

Tmp_119218 func_0011A080(void* node, void* extra);
void func_0011B0A8(void* a, const Tmp_119218& b);

struct Cursor_119128 { s32 tag; s32 value; s32 pad[2]; };
struct Node_119128 { s32 f0; s32 f4; Node_119128* next; };
struct Holder_119128 { s32 f0; s32 f4; Node_119128* head; };
struct Args_119128 { s32 f0; Holder_119128* holder; };

void func_0011B5F0(void* p, s32 flag);
void func_0011A080(void* out, void* node, void* extra);
void func_0011B0A8(void* a, void* b);
void func_0011B060(void* p, s32 flags);
void func_0011B018(void* out, void* p);

struct Link_1194A8 { s32 f0; Link_1194A8* f4; Link_1194A8* f8; };
struct __attribute__((aligned(16))) Quad_1194A8 { s32 type; Link_1194A8* head; s32 w2; s32 w3; };
struct Ent_1194A8 { s32 f0; Link_1194A8* f4; Link_1194A8* f8; };
struct Owner_1194A8 { s32 f0; Ent_1194A8* f4; };

void* func_0011B008(void* q);
void func_0011B018(void* self, void* q);
void func_0011B538(void* q, s32 n);
void func_0011A080(void* t, void* n, void* c);
void func_0011B0A8(void* a, void* b);
void func_0011B060(void* q, s32 mode);
void func_00113AA8(void* a, s32 b, void* c, void* d);

// Fixed by merging the two flag tests into one "kind != 0x1B || p != 0".

struct __attribute__((aligned(16))) Quad_119310 { s32 kind; void* p; s32 w[2]; };
struct Node_119310 { s32 kind; Node_119310* f4; Node_119310* f8; };

s32 func_0011B008(Quad_119310* q);
void func_0011B018(void* out, Quad_119310* q);
void func_0011B060(Quad_119310* q, s32 mode);
void func_0011B0A8(Quad_119310* a, Quad_119310* b);
void func_0011B538(Quad_119310* q, s32 n);
void func_0011A080(Quad_119310* t, Node_119310* n, s32 c);

struct Quad_118F48 { s32 a, b, c, d; };
struct Frame_118F48 { Quad_118F48 q; Quad_118F48 t; };

void func_0011B008(Quad_118F48* q);
void func_0011B018(void* dst, Quad_118F48* src);
void func_0011B060(Quad_118F48* q, int mode);
void func_0011B0A8(Quad_118F48* a, Quad_118F48* b);
void func_0011B538(Quad_118F48* q, int n);
void func_0011A080(Quad_118F48* t, void* n, s32 c);
void func_001E1F10(const char* x);
s32 func_00113730(Quad_118F48* t, s32 mode, void* a, s32 c);

struct Ent_11AB58;
struct Sub_11AB58 { s32 type; Ent_11AB58* ent; };
struct Node_11AB58 { Ent_11AB58* f0; Sub_11AB58 sub; Node_11AB58* fC; };
struct List_11AB58 { Node_11AB58* head; };
struct World_11AB58 {
    s32 count;
    Ent_11AB58* ents[0x140];
    s32 n504;
    List_11AB58* lists[1];
};

extern u8 D_0025C250[];
extern u8 D_0025C270[];
extern u8 D_0025C290[];
extern u8 D_0025C2B0[];
extern u8 D_0025C2D0[];

void func_0011C2B0(u8* p);
void func_0011C2E8(u8* p);
s32 func_0011C3C8(Ent_11AB58* e);
void func_0011C3F0(Ent_11AB58* e);
void func_0011A728(World_11AB58* w, Ent_11AB58* e);
void func_0011A770(World_11AB58* w, Ent_11AB58* e);
void func_0011A7B8(World_11AB58* w, Ent_11AB58* e);
void func_0011A850(World_11AB58* w);
void func_001834A0(void* a);

struct __attribute__((aligned(16))) Quad_1196C8 { s32 w[4]; };
struct Node_1196C8 { s32 kind; Node_1196C8* f4; Node_1196C8* f8; };

s32 func_0011B008(Quad_1196C8* q);
void func_0011B018(void* out, Quad_1196C8* q);
void func_0011B060(Quad_1196C8* q, s32 mode);
void func_0011B0A8(Quad_1196C8* a, Quad_1196C8* b);
void func_0011A080(Quad_1196C8* t, Node_1196C8* n, void* c);
void* func_0011A630(void);
void func_0011A358(Quad_1196C8* t, void* owner, Node_1196C8* kind, Quad_1196C8* body);
void func_0011A328(void* slot, void* c);

s32 func_001F59C4(void* a, void* b, s32 n);

struct Arg_11B418;
void func_0011C5B0(Arg_11B418* a);
void func_0011C6C0(Arg_11B418* a);
void func_0011C7F0(Arg_11B418* a);
void func_0011C900(Arg_11B418* a);
void func_0011CA20(Arg_11B418* a);

struct Tmp_11A080 { s32 w[4]; };
struct Inner_11A080 { s32 type; s32 f4; s32 f8; };
struct In_11A080 { s32 kind; Inner_11A080* inner; };
struct Ret_11A080;

void func_0011B008(Tmp_11A080* t);
void func_0011B018(Ret_11A080* dst, Tmp_11A080* src);
void func_0011B060(Tmp_11A080* t, s32 mode);
void func_0011B0A8(Tmp_11A080* dst, void* src);
void func_00118D48(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00118DB8(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00118E80(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00118F48(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00119030(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00119128(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00119218(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00119310(Tmp_11A080* o, In_11A080* a, s32 b);
void func_001194A8(Tmp_11A080* o, In_11A080* a, s32 b);
void func_001196C8(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00119878(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00119970(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00119AF8(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00119BB0(Tmp_11A080* o, In_11A080* a, s32 b);
void func_00119FA0(Tmp_11A080* o, In_11A080* a, s32 b);

struct __attribute__((aligned(16))) Q16_11B258 { s32 w[4]; };
struct __attribute__((packed)) D8_11B258 { s32 a, b; };

void* func_0011C748(void);
void* func_0011C858(void);
void* func_0011C968(void);
s32 func_0011C580(Q16_11B258* p);
s32 func_0011C7C0(Q16_11B258* p);
s32 func_0011C8D0(D8_11B258* p);

struct Rd_11BA28;

extern s32 D_00275714;

s32 func_00137B90(Rd_11BA28* r);
void func_00137BE0(Rd_11BA28* r);
s32 func_00137D78(Rd_11BA28* r);
f32 func_00137DF8(Rd_11BA28* r);
s32 func_00137C40(Rd_11BA28* r);

struct V_119BB0 { s32 type; void* p; };
struct Node_119BB0 { s32 f0; void* f4; Node_119BB0* f8; };
typedef void (*Fn1D_119BB0)(V_119BB0* ret, s32 n, V_119BB0* args, void* ctx);
struct Ent_119BB0 { Fn1D_119BB0 f0; s32 f4; s32 f8; };
typedef void (*Fn21_119BB0)(V_119BB0* ret, void* a, s32 n, V_119BB0* args);
struct O21_119BB0 { void* f0; Fn21_119BB0 f4; s32 f8; };
struct Def_119BB0 { s32 f0; Node_119BB0* f4; s32 f8; s32 fC; s32 f10; };

V_119BB0* func_0011B008(V_119BB0* q);
void func_0011B060(V_119BB0* q, s32 mode);
void func_0011B0A8(V_119BB0* a, V_119BB0* b);
void func_0011B018(V_119BB0* dst, V_119BB0* src);
void func_0011A080(V_119BB0* ret, Node_119BB0* n, void* ctx);
void func_0011B6C0(V_119BB0* q, V_119BB0* head);
void func_0011B538(V_119BB0* q, s32 n);
void* func_0011A630(void);
void func_0011A328(void* s, s32 v);
void func_0011A358(V_119BB0* ret, void* s, void* x, V_119BB0* arg);
void func_00119A58(V_119BB0* ret, s32 v, void* s);
extern Ent_119BB0 D_00259958[];

struct __attribute__((aligned(16))) Quad_119030 { s32 w[4]; };
struct Node_119030 { s32 pad0; Node_119030* f4; Node_119030* f8; };

void func_0011B008(Quad_119030* q);
void func_0011B018(void* out, Quad_119030* q);
void func_0011B060(Quad_119030* q, s32 mode);
void func_0011B0A8(Quad_119030* a, Quad_119030* b);
void func_0011B538(Quad_119030* q, s32 n);
void func_0011A080(Quad_119030* t, Node_119030* n, s32 c);

struct __attribute__((aligned(16))) Quad_118198 { s32 type; struct Node_118198* head; s32 w2; s32 w3; };
struct Ent_118198;
struct Node_118198 { s32 f0; Ent_118198* f4; Node_118198* f8; };
struct Pair_118198 { s32 a; s32 b; };
struct Src_118198 {
    s32 type;
    Node_118198* head;
    Pair_118198 p0;
    Pair_118198 p1;
};
struct Hit_118198 { Quad_118198 q[7]; };

struct Val_118198;
Val_118198* func_0011B008(Val_118198* q);
void func_0011B018(Val_118198* dst, const Val_118198* src);
void func_0011B060(Val_118198* q, s32 mode);
struct __attribute__((aligned(16))) Val_118198 {
    s32 type;
    Node_118198* head;
    s32 w2;
    s32 w3;
    Val_118198() { func_0011B008(this); }
    Val_118198(const Val_118198& o) { func_0011B018(this, &o); }
    ~Val_118198() { func_0011B060(this, 2); }
};
void func_0011B0A8(Val_118198* a, Src_118198* b);
s32 func_001419E8(Quad_118198* z, s32 a, s32 b, s32 c, Ent_118198** d, Hit_118198* e);
void func_0011B8A8(Node_118198* n, Ent_118198* e);
void func_0011B740(Node_118198* n, Quad_118198* q);
void func_0011B6C0(void* q, Node_118198* n);

struct Stk_11A850;

// One generic record: a queued event is { type, object, next }; the lists
// and the object table use the same words.
struct Obj_11A850 {
    s32 f0;
    Obj_11A850* f4;
    Obj_11A850* f8;
    Obj_11A850* fC;
    Obj_11A850* f10;
    Obj_11A850* f14;
};

// What func_0011A7D8 returns: a queue of records and two objects.
struct Batch_11A850 {
    Obj_11A850* f0;
    Obj_11A850* f4;
    s32 f8;
    s32 fC;
    Obj_11A850* f10;
};

Obj_11A850* func_0011A748(Stk_11A850* s);
void func_0011A770(Stk_11A850* s, Obj_11A850* o);
void func_0011A7B8(Stk_11A850* s, Obj_11A850* o);
void func_0011A728(Stk_11A850* s, Obj_11A850* o);
Batch_11A850* func_0011A7D8(Stk_11A850* s);
Obj_11A850* func_0011A790(Stk_11A850* s);
void func_0011C3F0(Obj_11A850* o);
s32 func_0011C3C8(Obj_11A850* o);

ASM_FUNC(func_00112698);

ASM_FUNC(func_00112968);

INCLUDE_RODATA(jtbl_00248FE0);
INCLUDE_RODATA(jtbl_00249000);
INCLUDE_RODATA(jtbl_00249020);
INCLUDE_RODATA(jtbl_00249040);
ASM_FUNC(func_00112C38);

INCLUDE_RODATA(jtbl_00249060);
INCLUDE_RODATA(jtbl_00249080);
INCLUDE_RODATA(jtbl_002490A0);
ASM_FUNC(func_00113240);

void* func_00113730(void* self);
void* func_00113780(void* self);
void* func_001137D0(void* self);
void* func_00113820(void* self, void* x, Src_113820* src);
void* func_00113888(void* self, Entry_113888* e, s32 mode);
void* func_001139E8(void* state, void* arg1, void* value);
void* func_00113A18(void* state, void* arg1, void* value);
void* func_00113A48(void* self, int unused, void* x);
void* func_00113A78(void* state, void* arg1, void* value);
void* func_00113AA8(void* self, void* unused, Ent_113AA8* k);
Q_113B60* func_00113B60(Q_113B60* out, Q_113B60* a, Q_113B60* b);
void* func_00113E48(void* state, void* arg1, void* value);
void* func_00113E78(void* state, void* arg1, s32* value);
void* func_00113EE0(void* state, void* arg1, s32* value);
void* func_00113F48(void* state, void* arg1, s32* value);
void* func_00113FB0(void* state, void* arg1, s32* value);
void* func_00114018(void* self, int unused, s32* kind);
void* func_00114080(void* self, s32 unused, Tag_114080* p);
void* func_001140E8(void* self, s32 unused, Tag_1140E8* p);
void* func_00114150(void* self, s32 unused, Tag_114150* p);
void* func_001141B8(void* dst, int unused, s32* key);
void* func_00114220(void* dst, int unused, s32* key);
void* func_00114288(void* self, int unused, s32* kind);
void* func_00114300(void* self, s32 unused, Src_114300* src);
void* func_00114360(void* self, s32 unused, Src_114360* src);
void* func_001143C8(void* self, int unused, s32* value);
void* func_00114438(void* self, int unused, s32* value);
void* func_001144A0(void* self, int unused, s32* p);
void* func_00114518(void* self, s32 unused, Elem_114518* e);
void* func_001145C8(void* self, int unused, s32* p);
void* func_00114638(void* self, s32 unused, Src_114638* src);
void* func_001146E0(void* self, void* unused, Src_1146E0* src);
void* func_00114740(void* self, s32 unused, Src_114740* src);
void* func_001147B8(void* self, s32 u1, Args_147B8* src, s32 u3, s32 mode);
void* func_00114858(void* self, int a, void* b, void* c);
void* func_00114888(void* self, s32 u1, void* src, s32 u3);
void* func_001148B8(void* self, void* unused, Rec_1148B8* p);
void* func_00114950(void* self, void* unused, Rec_114950* p);
void* func_001149F0(void* ret, s32 unused, Src_1149F0* src, void* arg3);
void* func_00114B80(void* self, void* unused, void* value);
Val_114D18 func_00114D18(s32 unused, Obj_114D18* obj, s32 c);
Val_114F48 func_00114F48(s32 unused, Obj_114F48* obj, s32 c);
Val_1151C0 func_001151C0(s32 unused, Obj_1151C0* obj, s32 c);
void* func_00115398(void* ret, s32 unused, void* src, s32 c);
void* func_00115440(void* self, void* unused, Pair_115440* src);
void* func_00115510(void* self, s32 kind, List_115510* list);
void* func_001156B0(void* self, s32, Entry_1156B0* src);
void* func_00115710(void* self, s32, Entry_115710* in);
void* func_001157E0(void* self, s32, Entry_1157E0* in);
void* func_001158B8(void* ret, s32 unused, void* src);
Quad_1159B8* func_001159B8(Quad_1159B8* out, s32 mode, Src_1159B8* s);
void* func_00115B78(void* self, s32, Entry_115B78* e);
void* func_00115C00(void* self, void* unused, Pair_115C00* p);
void* func_00115CA0(void* self, Tagged_115CA0* src, s32 index);
void* func_00115D48(void* self, s32 unused, Tagged_115D48* src);
void* func_00115D78(void* self, s32 unused, s32 value);
void* func_00115DA8(void* self, s32 unused, s32 value);
void* func_00115DD8(void* self, s32 unused, s32 value);
void* func_00115E08(void* self, s32 unused, s32 value);
void* func_00115E38(void* self, s32 unused, s32 value);
void* func_00115E68(void* self, s32 unused, s32 value);
void* func_00115E98(void* self, s32 unused, s32 value);
void* func_00115EC8(void* self, s32 unused, Entry_115EC8* e);
void* func_00116520(void* self, s32 unused, Src_116520* src);
void* func_00116600(void* ret, s32 unused, Src_116600* src);
void* func_001166C0(void* ret, s32 unused, Src_1166C0* src);
void* func_00116740(void* ret, s32 unused, Src_116740* src);
void* func_001167C0(void* ret, s32 unused, Src_1167C0* src);
void* func_00116978(void* ret, s32 unused, Src_116978* src);
void* func_001169E8(void* self, void* x, Src_1169E8* src);
void* func_00116A88(void* ret, s32 unused, Src_116A88* src);
void* func_00116B08(void* ret, s32 unused, Src_116B08* src);
void* func_00116C80(void* ret, s32 unused, Src_116C80* src);
void* func_00116D20(void* ret, s32 unused, Src_116D20* src);
void* func_00116DC8(void* ret, s32 unused, Src_116DC8* src);
void* func_00116EA8(void* self, s32 unused, u8* src);
void* func_00116FE8(void* self, s32 unused, Src_116FE8* src);
void* func_00117080(void* self, s32 unused, Src_117080* src);
void* func_00117118(void* self, s32 unused, In_117118* x);
void* func_00117180(void* ret, s32 unused, Src_117180* src);
void* func_001171F0(void* ret, s32 unused, Src_1171F0* src);
void* func_00117260(void* ret, s32 unused, Src_117260* src);
void* func_001172C8(void* dst, int unused, Value_1172C8* p);
void* func_00117360(void* self, s32 unused, Node_117360* x);
void* func_00117478(void* self, s32 unused, Node_117478* x);
void* func_00117610(void* self);
void* func_00117668(void* ret, s32 limit, Src_117668* src);
void* func_00117880(void* ret, s32 unused, Src_117880* src);
void* func_00117910(void* a0, void* a1, Src_117910* a2, void* a3, s32 a4);
void* func_00117A30(void* ret, s32 a1, void* src, s32 a3);
void* func_00117A60(void* ret, s32 a1, void* src, s32 a3);
void* func_00117A90(void* ret, s32 a1, void* src, s32 a3);
void* func_00117AC0(void* ret, s32 a1, void* src, s32 a3);
void* func_00117AF0(void* self, s32 count, s32* values);
void* func_00117BC8(void* out, s32 unused, In_117BC8* in);
void* func_00117C48(void* out, s32 unused, In_117C48* in);
void* func_00117D00(void* out, s32 unused, In_117D00* in);
void* func_00117D78(void* out, s32 unused, In_117D78* in);
void* func_00117E20(void* self);
void* func_00117E78(void* self);
void* func_00117ED0(void* self);
void* func_00117F28(void* out, s32 unused, In_117F28* in);
void* func_001180C0(void* out, s32 unused, In_1180C0* in);
Val_118198 func_00118198(s32 id, s32 unused, Src_118198* src);
void* func_001183B8(void* out, s32 x, s32 y, s32 z);
void* func_00118458(void* out, s32 x, s32 y, s32 z);
void* func_001184F8(void* ret, s32 unused, Src_1184F8* src);
void* func_00118580(void* ret, s32 unused, Src_118580* src);
void* func_00118608(void* out, s32 unused, In_118608* in);
void* func_00118720(void* out, s32 unused, In_118720* in);
void* func_001187E8(void* ret, s32 unused, Src_1187E8* src);
void* func_00118850(void* ret, s32 unused, Src_118850* src);
void* func_001188F0(void* ret, s32 unused, Src_1188F0* src);
Quad_118D10* func_00118D10(Quad_118D10* out, void* src);
Quad_118D20* func_00118D20(Quad_118D20* out, Quad_118D20 v);
void* func_00118D48(void* ret, Src_118D48* src, void* ctx);
void* func_00118DB8(void* self, Node_118DB8* x, s32 c);
void* func_00118E80(void* self, Node_118E80* x, s32 c);
void* func_00118F48(void* self, void* p, s32 x);
void* func_00119030(void* self, Node_119030* x, s32 c);
void* func_00119128(void* out, Args_119128* a1, void* a2);
Cursor_119218 func_00119218(Args_119218* a1, void* a2);
void* func_00119310(void* self, Node_119310* x, s32 c);
void* func_001194A8(void* self, Link_1194A8* h, void* arg);
void* func_001196C8(void* self, Node_1196C8* x, void* c);
void* func_00119878(void* self, Owner_119878* owner, s32 c);
void* func_00119970(void* self, Owner_119970* owner, s32 c);
void* func_00119A58(void* out, Node_119A58* list, s32 c);
void* func_00119AF8(void* self, Owner_119AF8* owner, s32 c);
V_119BB0* func_00119BB0(V_119BB0* ret, Node_119BB0* self, void* ctx);
void* func_00119FA0(void* self, Outer_119FA0* src, void* item);
Ret_11A080* func_0011A080(Ret_11A080* ret, In_11A080* in, s32 arg);
void func_0011A328(Slot_11A328* slot, s32 value);
void func_0011A338(IntList* list, int value);
void* func_0011A358(void* self, Owner_11A358* owner, s32 kind, void* body);
void* func_0011A400(void* self, void* table, void* key, void* item);
s32 func_0011A498(void* a, s32 b, s32 c, void* d);
void* func_0011A4D8(struct Tree_11A4D8* self, s32 key, s32 flag);
void func_0011A5B0(struct Tree_11A5B0* src, struct Tree_11A5B0* dst);
void* func_0011A630(void);
void func_0011A670(void);
void func_0011A6A8(Counters_11A6A8* self);
void func_0011A6B8();
void func_0011A6C0(IntList* list, int value);
void func_0011A708(Obj_0011A708* obj, s32 value);
void func_0011A728(Obj_0011A728* obj, s32 value);
int func_0011A748(StackAt708* stack);
void func_0011A770(Obj_0011A770* obj, s32 value);
s32 func_0011A790(Stack_11A790* s);
void func_0011A7B8(Stack_11A7B8* s, s32 value);
s32 func_0011A7D8(Stack_11A7D8* s);
void func_0011A800(void);
void func_0011A850(Stk_11A850* self);
void func_0011AB58(World_11AB58* w);

void* func_00113730(void* self)
{
    Quad_113730 q;
    func_0011B008(&q);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00113780(void* self)
{
    Quad_113780 q;
    func_0011B008(&q);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_001137D0(void* self)
{
    Quad_1137D0 q;
    func_0011B008(&q);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00113820(void* self, void* x, Src_113820* src)
{
    Quad_113820 q;
    func_0011B008(&q);
    (void)func_0011B5F0(&q, src->f4 == src->fC);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

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

void* func_00113E48(void* state, void* arg1, void* value) {
	func_00113B60(state, value, (char*)value + 8);
	return state;
}

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

void* func_00114018(void* self, int unused, s32* kind)
{
    Quad_114018 q;
    func_0011B008(&q);
    func_0011B5F0(&q, *kind == 0x1C);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00114080(void* self, s32 unused, Tag_114080* p)
{
    Quad_114080 q;
    func_0011B008(&q);
    func_0011B5F0(&q, p->tag == 0x16);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_001140E8(void* self, s32 unused, Tag_1140E8* p)
{
    Quad_1140E8 q;
    func_0011B008(&q);
    func_0011B5F0(&q, p->tag == 0x17);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00114150(void* self, s32 unused, Tag_114150* p)
{
    Quad_114150 q;
    func_0011B008(&q);
    func_0011B5F0(&q, p->tag == 0x18);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_001141B8(void* dst, int unused, s32* key)
{
    Handle_1141B8 a;
    func_0011B008(&a);
    func_0011B5F0(&a, *key == 0x19);
    func_0011B018(dst, &a);
    func_0011B060(&a, 2);
    return dst;
}

void* func_00114220(void* dst, int unused, s32* key)
{
    Handle_114220 a;
    func_0011B008(&a);
    func_0011B5F0(&a, *key == 0x1A);
    func_0011B018(dst, &a);
    func_0011B060(&a, 2);
    return dst;
}

void* func_00114288(void* self, int unused, s32* kind)
{
    Quad_114288 q;
    func_0011B008(&q);
    s32 v = *kind;
    func_0011B5F0(&q, v == 0x1E || v == 0);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00114300(void* self, s32 unused, Src_114300* src)
{
    Quad_114300 q;
    func_0011B008(&q);
    (void)func_0011B5F0(&q, src->flag == 0);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00114360(void* self, s32 unused, Src_114360* src)
{
    Quad_114360 q;
    func_0011B008(&q);
    (void)func_0011B5F0(&q, (src->flag ^ 0x20) == 0);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_001143C8(void* self, int unused, s32* value)
{
    Quad_1143C8 q;
    func_0011B008(&q);
    int flag = 0;
    if (value[0] == 0x20) {
        flag = value[1] == 0;
    }
    func_0011B5F0(&q, flag);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00114438(void* self, int unused, s32* value)
{
    Quad_114438 q;
    func_0011B008(&q);
    func_0011B5F0(&q, value[0] == 0x21);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_001144A0(void* self, int unused, s32* p)
{
    Quad_1144A0 q;
    func_0011B008(&q);
    s32 v = *p;
    int flag = (v == 0x1F || v == 0x1D);
    func_0011B5F0(&q, flag);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00114518(void* self, s32 unused, Elem_114518* e)
{
    Frame_114518 f;
    func_0011B008(&f.q);
    for (s32 k = 0; k < 3; k++) {
        if (e[k].tag == 0x14) {
            f.out[k] = (f32)e[k].v.i;
        } else {
            f.out[k] = e[k].v.f;
        }
    }
    s32 flag = func_001EAC68(f.out[0], f.out[1], f.out[2]);
    (void)func_0011B5F0(&f.q, flag);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

void* func_001145C8(void* self, int unused, s32* p)
{
    Quad_1145C8 q;
    func_0011B008(&q);
    int flag = 0;
    if (p[0] == 0x1B) {
        flag = (u32)p[1] < 1;
    }
    func_0011B5F0(&q, flag);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00114638(void* self, s32 unused, Src_114638* src)
{
    Quad_114638 q;
    func_0011B008(&q);
    Node_114638* node = (Node_114638*)func_0011AF28();
    func_0011B0A8(node, src);
    s32 kind = src->kind;
    src = (Src_114638*)((u8*)src + 8);
    if (kind == 0) {
        node->val = 0;
    } else if (kind == 0x1E) {
        node->val = ((Sub_114638*)src)->val;
    }
    func_0011B6C0(&q, node);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_001146E0(void* self, void* unused, Src_1146E0* src)
{
    Quad_1146E0 q;
    func_0011B008(&q);
    func_0011B0A8(&q, src->other);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00114740(void* self, s32 unused, Src_114740* src)
{
    Quad_114740 q;
    (void)func_0011B008(&q);
    Inner_114740* in = src->inner;
    s32 v = in->val;
    if (v != 0) {
        func_0011B6C0(&q, v);
    } else {
        func_0011B538(&q, 0);
    }
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_001147B8(void* self, s32 u1, Args_147B8* src, s32 u3, s32 mode)
{
    Quad_147B8 q;
    Quad_147B8* p;
    func_0011B008(&q);
    p = src->p;
    if (mode == 0x23) {
        func_0011B0A8(p, &src->q);
    } else {
        if (src->q.a == 0x1E) {
            p->c = src->q.b;
        } else {
            p->c = 0;
        }
    }
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00114858(void* self, int a, void* b, void* c)
{
    func_001147B8(self, a, b, c, 0x23);
    return self;
}

void* func_00114888(void* self, s32 u1, void* src, s32 u3)
{
    (void)func_001147B8(self, u1, src, u3, 0x24);
    return self;
}

void* func_001148B8(void* self, void* unused, Rec_1148B8* p)
{
    Quad_1148B8 q;
    func_0011B008(&q);
    s32 n = 0;
    if (p->tag == 0x1E && p->head) {
        Node_1148B8* node = p->head;
        do {
            node = node->next;
            n++;
        } while (node);
    }
    func_0011B570(&q, n);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00114950(void* self, void* unused, Rec_114950* p)
{
    Quad_114950 q;
    func_0011B008(&q);
    func_0011B538(&q, 0);
    if (p->tag == 0x1E) {
        Node_114950* node = p->head;
        Sub_114950* sub = &p->sub;
        s32 i = 0;
        while (node != 0) {
            if (i == sub->idx) {
                func_0011B0A8(&q, node);
                break;
            }
            node = node->next;
            i++;
        }
    }
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_001149F0(void* ret, s32 unused, Src_1149F0* src, void* arg3)
{
    Frame_1149F0 f;
    s32 n;
    Node_1149F0* cur;

    func_0011B008(&f.A);
    func_0011B008(&f.B);
    Pair_1149F0* q = f.C;
    n = 1;
    do {
        func_0011B008(q);
        n--;
        q++;
    } while (n != -1);
    (void)func_0011B5F0(&f.A, 0);
    if (src->kind == 0x1E) {
        func_0011B0A8(f.C, src);
        cur = src->head;
        while (cur != 0) {
            func_0011B0A8(&f.C[1], cur);
            func_00113E48(&f.D, 2, f.C, arg3);
            func_0011B0A8(&f.B, &f.D);
            func_0011B060(&f.D, 2);
            if (f.B.a == 0x1B) {
                if (f.B.b != 0) {
                    (void)func_0011B5F0(&f.A, 1);
                    break;
                }
            }
            cur = cur->next;
        }
    }
    func_0011B018(ret, &f.A);
    q = (Pair_1149F0*)&f.D;
    if (f.C != q) {
        do {
            q--;
            func_0011B060(q, 0);
        } while (f.C != q);
    }
    func_0011B060(&f.B, 2);
    func_0011B060(&f.A, 2);
    return ret;
}

void* func_00114B80(void* self, void* unused, void* value)
{
    func_0011B018(self, value);
    return self;
}

INCLUDE_ASM(func_00114BB0);

Val_114D18 func_00114D18(s32 unused, Obj_114D18* obj, s32 c)
{
    Val_114D18 q;
    Cell_114D18 arr[5];
    if (obj->m.tag == 0) {
        func_0011B0A8(&q, obj->m);
    } else {
        Val_114D18* list = (struct Val_114D18 *)func_0011AF28();
        Val_114D18* p[2];
        Val_114D18* last;
        list->tag = 0x1E;
        for (u32 i = 0; i < 2; i++) {
            p[i] = (struct Val_114D18 *)func_0011AF28();
        }
        func_0011B6C0(&arr[0], &arr[1]);
        arr[0].f8 = 0;
        func_0011B6C0(&arr[1], &arr[3]);
        arr[1].f8 = &arr[2];
        func_0011B6C0(&arr[2], &arr[4]);
        arr[2].f8 = 0;
        arr[3].tag = 0x11;
        arr[3].f8 = p[0];
        func_0011B0A8(p[0], *(Val_114D18*)obj);
        arr[4].tag = 0x11;
        arr[4].f8 = p[1];
        Val_114D18* m = &obj->m;
        for (Val_114D18* l = m->f4; l != 0; l = l->f8) {
            Val_114D18* e = (struct Val_114D18 *)func_0011AF28();
            func_0011B0A8(p[1], *l);
            func_0011B0A8(e, func_0011A080(&arr[0], c));
            if (list->f4 == 0) {
                func_0011B6C0(list, e);
            } else {
                last->f8 = e;
            }
            last = e;
        }
        func_0011B6C0(&q, list->f4);
    }
    return q;
}

Val_114F48 func_00114F48(s32 unused, Obj_114F48* obj, s32 c)
{
    Val_114F48 q;
    Cell_114F48 arr[5];
    Val_114F48* p[2];
    Val_114F48 r;
    if (obj->m.tag == 0) {
        func_0011B0A8(&q, obj->m);
    } else {
        Val_114F48* list = 0;
        Val_114F48* last;
        for (u32 i = 0; i < 2; i++) {
            p[i] = (Val_114F48*)func_0011AF28();
        }
        func_0011B6C0(&arr[0].v, &arr[1].v);
        arr[0].v.f8 = 0;
        func_0011B6C0(&arr[1].v, &arr[3].v);
        arr[1].v.f8 = &arr[2].v;
        func_0011B6C0(&arr[2].v, &arr[4].v);
        arr[2].v.f8 = 0;
        arr[3].v.tag = 0x11;
        arr[3].v.f8 = p[0];
        func_0011B0A8(p[0], *(Val_114F48*)obj);
        arr[4].v.tag = 0x11;
        arr[4].v.f8 = p[1];
        Val_114F48* m = &obj->m;
        for (Val_114F48* l = m->f4; l != 0; l = l->f8) {
            func_0011B0A8(p[1], *l);
            func_0011B0A8(&r, func_0011A080(&arr[0].v, c));
            if (r.tag == 0x1B && r.f4 != 0) {
                Val_114F48* e = (Val_114F48*)func_0011AF28();
                func_0011B0A8(e, *l);
                if (list == 0) {
                    list = (Val_114F48*)func_0011AF28();
                    func_0011B6C0(list, e);
                } else {
                    last->f8 = e;
                }
                last = e;
            }
        }
        if (list != 0) {
            func_0011B6C0(&q, list->f4);
        } else {
            q.tag = 0;
        }
    }
    return q;
}

Val_1151C0 func_001151C0(s32 unused, Obj_1151C0* obj, s32 c)
{
    Val_1151C0 q;
    Cell_1151C0 arr[5];
    if (obj->m.tag == 0x1E) {
        Val_1151C0* p[2];
        for (u32 i = 0; i < 2; i++) {
            p[i] = (struct Val_1151C0 *)func_0011AF28();
        }
        func_0011B6C0(&arr[0], &arr[1]);
        arr[0].f8 = 0;
        func_0011B6C0(&arr[1], &arr[3]);
        arr[1].f8 = &arr[2];
        func_0011B6C0(&arr[2], &arr[4]);
        arr[2].f8 = 0;
        arr[3].tag = 0x11;
        arr[3].f8 = p[0];
        func_0011B0A8(p[0], *(Val_1151C0*)obj);
        arr[4].tag = 0x11;
        arr[4].f8 = p[1];
        Val_1151C0* m = &obj->m;
        for (Val_1151C0* l = m->f4; l != 0; l = l->f8) {
            func_0011B0A8(p[1], *l);
            func_0011B0A8(&q, func_0011A080(&arr[0], c));
        }
    }
    q.tag = 0x22;
    return q;
}

void* func_00115398(void* ret, s32 unused, void* src, s32 c)
{
    Tmp_115398 t;
    Tmp_115398 u;
    func_0011B008(&t);
    void* n = func_0011AF28();
    func_0011B0A8(n, src);
    func_0011A080(&u, n, c);
    func_0011B0A8(&t, &u);
    func_0011B060(&u, 2);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

void* func_00115440(void* self, void* unused, Pair_115440* src)
{
    Frame_115440 a;
    Frame_115440 b;
    s32 count = 2;
    func_0011B008(&a);
    Pair_115440* in = src;
    f32* base = (f32*)func_0011C508();
    f32* out = base;
    do {
        func_0011B9A8(&b, in);
        in++;
        func_0011B0A8(&a, &b);
        count--;
        func_0011B060(&b, 2);
        *out = *(f32*)&a.w[1];
        out++;
    } while (count >= 0);
    func_0011B740(&a, base);
    func_0011B018(self, &a);
    func_0011B060(&a, 2);
    return self;
}

void* func_00115510(void* self, s32 kind, List_115510* list)
{
    Quad_115510 t, u;
    func_0011B008(&t);
    Quad_115510* a = (Quad_115510*)func_0011C618();
    Node_115510* n = list->f4;
    switch (kind) {
    case 3:
    case 4: {
        func_001884C0(a);
        for (s32 i = 0; i < kind; i++) {
            a[i] = *n->f4;
            n = n->f8;
        }
        break;
    }
    case 9:
        func_001884C0(a);
    case 16: {
        s32 m = kind == 9 ? 3 : 4;
        for (s32 i = 0; i < m; i++) {
            for (s32 j = 0; j < m; j++) {
                func_0011B9A8(&u, n);
                func_0011B0A8(&t, &u);
                func_0011B060(&u, 2);
                a[i].f[j] = t.f[1];
                n = n->f8;
            }
        }
        break;
    }
    }
    func_0011B788(&t, a);
    func_0011B018(self, &t);
    func_0011B060(&t, 2);
    return self;
}

void* func_001156B0(void* self, s32, Entry_1156B0* src)
{
    Var_1156B0 q;
    func_001C0C08(src->index, src->value);
    func_0011B008(&q);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00115710(void* self, s32, Entry_115710* in)
{
    Var_115710 a;
    Var_115710 b;
    f32* base;
    f32* out;
    s32 n = 2;
    func_0011B008(&a);
    Entry_115710* p = in;
    base = (f32*)func_0011C748();
    out = base;
    do {
        func_0011B9A8(&b, p);
        p++;
        func_0011B0A8(&a, &b);
        n--;
        func_0011B060(&b, 2);
        *out++ = a.value;
    } while (n >= 0);
    func_0011B7D0(&a, base);
    func_0011B018(self, &a);
    func_0011B060(&a, 2);
    return self;
}

void* func_001157E0(void* self, s32, Entry_1157E0* in)
{
    Var_1157E0 a;
    Var_1157E0 b;
    f32* out;
    func_0011B008(&a);
    out = (f32*)func_0011C858();
    func_0011B9A8(&b, in);
    func_0011B0A8(&a, &b);
    func_0011B060(&b, 2);
    out[0] = a.value;
    func_0011B9A8(&b, in + 1);
    func_0011B0A8(&a, &b);
    func_0011B060(&b, 2);
    out[1] = a.value;
    func_0011B818(&a, out);
    func_0011B018(self, &a);
    func_0011B060(&a, 2);
    return self;
}

void* func_001158B8(void* ret, s32 unused, void* src)
{
    Vec_1158B8 t;
    Vec_1158B8 u;
    func_0011B008(&t);
    f32* out = (f32*)func_0011C968();
    func_0011B9A8(&u, src);
    func_0011B0A8(&t, &u);
    func_0011B060(&u, 2);
    out[0] = t.y;
    func_0011B9A8(&u, (u8*)src + 8);
    func_0011B0A8(&t, &u);
    func_0011B060(&u, 2);
    out[1] = t.y;
    func_0011B9A8(&u, (u8*)src + 0x10);
    func_0011B0A8(&t, &u);
    func_0011B060(&u, 2);
    out[2] = t.y;
    func_0011B860(&t, out);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

Quad_1159B8* func_001159B8(Quad_1159B8* out, s32 mode, Src_1159B8* s)
{
    Quad_1159B8 q;
    func_0011B008(&q);
    Idx_1159B8* ix = s->fC;
    switch (s->type) {
    case 0x16:
        func_0011B5B0(&q, ((Arr_1159B8*)s->f4)->v[ix->f4]);
        break;
    case 0x17: {
        s32 i = ix->f4;
        Arr_1159B8* v;
        if (mode == 2) {
            v = (Arr_1159B8*)func_0011C508();
            *v = ((Arr_1159B8*)s->f4)[i];
            func_0011B740(&q, v);
        } else {
            ix = ix->f8;
            v = &((Mat_1159B8*)s->f4)->row[i];
            func_0011B5B0(&q, v->v[ix->f4]);
        }
        break;
    }
    case 0x18:
        func_0011B5B0(&q, ((Arr_1159B8*)s->f4)->v[ix->f4]);
        break;
    case 0x19:
        func_0011B5B0(&q, ix->f4 == 0 ? s->f4[0] : s->f4[1]);
        break;
    case 0x1A:
        switch (ix->f4) {
        case 0:
            func_0011B5B0(&q, s->f4[0]);
            break;
        case 1:
            func_0011B5B0(&q, s->f4[1]);
            break;
        case 2:
            func_0011B5B0(&q, s->f4[2]);
            break;
        }
        break;
    }
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

void* func_00115B78(void* self, s32, Entry_115B78* e)
{
    Var_115B78 q;
    func_0011B008(&q);
    if (e->tag == 0x14) {
        func_001F66F8(e->word.i);
    } else {
        func_001F66F8((s32)e->word.f);
    }
    q.tag = 0x22;
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00115C00(void* self, void* unused, Pair_115C00* p)
{
    Frame_115C00 f;
    func_0011B008(&f);
    f32 x;
    f32 y;
    if (p->x.tag == 0x14) {
        x = (f32)p->x.cell.i;
    } else {
        x = p->x.cell.f;
    }
    if (p->y.tag == 0x14) {
        y = (f32)p->y.cell.i;
    } else {
        y = p->y.cell.f;
    }
    f32 r = func_001EAAE0(x, y);
    func_0011B5B0(&f, r);
    func_0011B018(self, &f);
    func_0011B060(&f, 2);
    return self;
}

void* func_00115CA0(void* self, Tagged_115CA0* src, s32 index)
{
    Frame_115CA0 f;
    func_0011B008(&f);
    f32 v;
    if (src->tag == 0x15) {
        v = src->cell.f;
    } else {
        v = (f32)src->cell.i;
    }
    f32 r = ((FloatFn_115CA0*)D_00259938)[index](v);
    func_0011B5B0(&f, r);
    func_0011B018(self, &f);
    func_0011B060(&f, 2);
    return self;
}

void* func_00115D48(void* self, s32 unused, Tagged_115D48* src)
{
    func_00115CA0(self, src, 0);
    return self;
}

void* func_00115D78(void* self, s32 unused, s32 value)
{
    func_00115CA0(self, value, 1);
    return self;
}

void* func_00115DA8(void* self, s32 unused, s32 value)
{
    func_00115CA0(self, value, 2);
    return self;
}

void* func_00115DD8(void* self, s32 unused, s32 value)
{
    func_00115CA0(self, value, 3);
    return self;
}

void* func_00115E08(void* self, s32 unused, s32 value)
{
    func_00115CA0(self, value, 4);
    return self;
}

void* func_00115E38(void* self, s32 unused, s32 value)
{
    func_00115CA0(self, value, 5);
    return self;
}

void* func_00115E68(void* self, s32 unused, s32 value)
{
    func_00115CA0(self, value, 6);
    return self;
}

void* func_00115E98(void* self, s32 unused, s32 value)
{
    func_00115CA0(self, value, 7);
    return self;
}

void* func_00115EC8(void* self, s32 unused, Entry_115EC8* e)
{
    Frame_115EC8 f;
    func_0011B008(&f);
    f32* out = f.xy;
    for (s32 i = 1; i >= 0; i--, e++) {
        if (e->tag == 0x15) {
            *out = e->v.f;
        } else {
            *out = (f32)e->v.i;
        }
        out++;
    }
    f32 d = func_00205778(f.xy[0], f.xy[1]);
    func_0011B5B0(&f, d);
    func_0011B018(self, &f);
    func_0011B060(&f, 2);
    return self;
}

ASM_FUNC(func_00115F70);

ASM_FUNC(func_00115FF8);

ASM_FUNC(func_00116080);

ASM_FUNC(func_00116108);

ASM_FUNC(func_001161F8);

ASM_FUNC(func_001162D0);

ASM_FUNC(func_00116400);

ASM_FUNC(func_00116490);

void* func_00116520(void* self, s32 unused, Src_116520* src)
{
    Frame_116520 f;
    func_0011B008(&f.q);
    void* p = func_0011C508();
    void* s3;
    if (src->f18 == 0) {
        s3 = 0;
    } else {
        s3 = ((Obj4_116520*)src->f1C)->f4;
    }
    void* s1 = src->f4;
    void* fc = src->fC;
    func_0011B9A8(&f.v, &src->f10);
    func_001EDEF0(s1, fc, p, s3, f.v.payload);
    func_0011B060(&f.v, 2);
    func_0011B740(&f.q, p);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

void* func_00116600(void* ret, s32 unused, Src_116600* src)
{
    Tmp_116600 t;
    func_0011B008(&t);
    Node_116600* a = (Node_116600*)func_0011AF28();
    void* b = func_0011AF28();
    a->link = b;
    void* c = func_0011C508();
    func_0011B740(b, c);
    f32 d = func_001ED908(src->a, src->b, c);
    func_0011B5B0(a, d);
    func_0011B6C0(&t, a);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

void* func_001166C0(void* ret, s32 unused, Src_1166C0* src)
{
    Tmp_1166C0 t;
    func_0011B008(&t);
    void* a = func_0011C618();
    func_00188770(src->a, a);
    func_0011B788(&t, a);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

void* func_00116740(void* ret, s32 unused, Src_116740* src)
{
    Tmp_116740 t;
    func_0011B008(&t);
    void* a = func_0011C618();
    func_00189AF0(src->a, a);
    func_0011B788(&t, a);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

void* func_001167C0(void* ret, s32 unused, Src_1167C0* src)
{
    Tmp_1167C0 t;
    func_0011B008(&t);
    void* a = func_0011C618();
    func_001891C0(src->a, src->b, a);
    func_0011B788(&t, a);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

ASM_FUNC(func_00116840);

void* func_00116978(void* ret, s32 unused, Src_116978* src)
{
    Tmp_116978 t;
    func_0011B008(&t);
    void* c = func_0011C508();
    *(Quad_116978*)c = *(Quad_116978*)((u8*)src->p + 0x30);
    (void)func_0011B740(&t, c);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

void* func_001169E8(void* self, void* x, Src_1169E8* src)
{
    Quad_1169E8 q;
    void* obj;
    func_0011B008(&q);
    obj = func_0011C618();
    *(Block_1169E8*)obj = *src->f4;
    func_001884C0(obj);
    func_0011B788(&q, obj);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00116A88(void* ret, s32 unused, Src_116A88* src)
{
    Tmp_116A88 t;
    func_0011B008(&t);
    void* c = func_0011C508();
    func_00188FD8(src->p, c);
    func_0011B740(&t, c);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

void* func_00116B08(void* ret, s32 unused, Src_116B08* src)
{
    Tmp_116B08 t;
    Vec_116B08 vec;
    func_0011B008(&t);
    void* a = func_0011AF28();
    void* b = func_0011AF28();
    void* c = func_0011C508();
    func_0011B740(b, c);
    *(void**)((u8*)a + 8) = b;
    func_00188D28(src->p, &vec, c);
    func_0011B5B0(a, vec.v[0]);
    func_0011B6C0(&t, a);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

ASM_FUNC(func_00116BC8);

void* func_00116C80(void* ret, s32 unused, Src_116C80* src)
{
    Tmp_116C80 t;
    Vec_116C80 v;
    func_0011B008(&t);
    void* a = func_0011C618();
    func_00189378(src->p, 0, &v);
    func_00188B08((u8*)src->p + 0x30, &v, a);
    func_0011B788(&t, a);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

void* func_00116D20(void* ret, s32 unused, Src_116D20* src)
{
    Tmp_116D20 t;
    Vec_116D20 v;
    func_0011B008(&t);
    Coef_116D20* k = src->coef;
    func_0011B9A8(&v, (u8*)src + 8);
    f32 x = v.v[1];
    f32 r = k->a + x * (k->b + x * k->c);
    func_0011B5B0(&t, r);
    func_0011B060(&v, 2);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

void* func_00116DC8(void* ret, s32 unused, Src_116DC8* src)
{
    Vec_116DC8 t;
    Vec_116DC8 u;
    func_0011B008(&t);
    f32* poly = src->poly;
    f32* range = src->range;
    func_0011B9A8(&u, (u8*)src + 0x10);
    f32 k = u.y;
    f32 v = poly[0] + k * (poly[1] + k * poly[2]);
    f32 lo = range[0];
    f32 hi = range[1];
    if (v < lo) {
        v = lo;
    } else if (hi < v) {
        v = hi;
    }
    func_0011B5B0(&t, v);
    func_0011B060(&u, 2);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

void* func_00116EA8(void* self, s32 unused, u8* src)
{
    Vec_116EA8 q0;
    Vec_116EA8 q1;
    Vec_116EA8 q2;
    Vec_116EA8 q3;
    Vec_116EA8 q4;
    func_0011B008(&q0);
    void* p = func_0011C748();
    (void)func_0011B9A8(&q1, src);
    f32 x = q1.y;
    (void)func_0011B9A8(&q2, src + 8);
    f32 y = q2.y;
    (void)func_0011B9A8(&q3, src + 0x10);
    f32 z = q3.y;
    (void)func_0011B9A8(&q4, src + 0x18);
    f32 w = q4.y;
    func_001EB018(p, x, y, z, w);
    func_0011B060(&q4, 2);
    func_0011B060(&q3, 2);
    func_0011B060(&q2, 2);
    func_0011B060(&q1, 2);
    func_0011B7D0(&q0, p);
    func_0011B018(self, &q0);
    func_0011B060(&q0, 2);
    return self;
}

void* func_00116FE8(void* self, s32 unused, Src_116FE8* src)
{
    Vec_116FE8 q0;
    Vec_116FE8 q1;
    func_0011B008(&q0);
    void* span = src->p4;
    (void)func_0011B9A8(&q1, (u8*)src + 8);
    f32 r = func_001EB0F8(span, q1.y);
    (void)func_0011B5B0(&q0, r);
    func_0011B060(&q1, 2);
    func_0011B018(self, &q0);
    func_0011B060(&q0, 2);
    return self;
}

void* func_00117080(void* self, s32 unused, Src_117080* src)
{
    Frame_117080 f;
    func_0011B008(&f.q);
    void* s1 = src->f4;
    func_0011B9A8(&f.v, &src->f8);
    s32 flag = func_001EB050(s1, f.v.payload);
    (void)func_0011B5F0(&f.q, flag);
    func_0011B060(&f.v, 2);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

void* func_00117118(void* self, s32 unused, In_117118* x)
{
    Quad_117118 q;
    func_0011B008(&q);
    func_0011B570(&q, (s32)x->f4);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00117180(void* ret, s32 unused, Src_117180* src)
{
    Tmp_117180 t;
    func_0011B008(&t);
    s32 n = (s32)(src->v + 1.0f);
    func_0011B570(&t, n);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

void* func_001171F0(void* ret, s32 unused, Src_1171F0* src)
{
    Tmp_1171F0 t;
    func_0011B008(&t);
    s32 n = (s32)(src->v + 0.5f);
    func_0011B570(&t, n);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

void* func_00117260(void* ret, s32 unused, Src_117260* src)
{
    Tmp_117260 t;
    func_0011B008(&t);
    s32 n = (s32)src->v;
    func_0011B570(&t, n);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

void* func_001172C8(void* dst, int unused, Value_1172C8* p)
{
    Quad_1172C8 q;
    func_0011B008(&q);
    if (p->type == 20) {
        s32 v = p->num.i; v = v < 0 ? -v : v;
        func_0011B570(&q, v);
    } else {
        f32 v = p->num.f;
        if (v < 0.0f) {
            v = -v;
        }
        func_0011B5B0(&q, v);
    }
    func_0011B018(dst, &q);
    func_0011B060(&q, 2);
    return dst;
}

void* func_00117360(void* self, s32 unused, Node_117360* x)
{
    Node_117360 q;
    func_0011B008(&q);
    (void)func_0011B0A8(&q, x);
    if (x->next == 0) {
        x = 0;
    } else {
        x = x->child;
    }
    if (x != 0) {
        do {
            if (q.tag == 0x14) {
                if (x->tag == 0x14) {
                    if (q.v.i < x->v.i) {
                        func_0011B0A8(&q, x);
                    }
                } else {
                    if ((f32)q.v.i < x->v.f) {
                        func_0011B0A8(&q, x);
                    }
                }
            } else {
                if (x->tag == 0x14) {
                    if (q.v.f < (f32)x->v.i) {
                        func_0011B0A8(&q, x);
                    }
                } else {
                    f32 pf = x->v.f;
                    if (q.v.f < pf) {
                        func_0011B0A8(&q, x);
                    }
                }
            }
            x = x->next;
        } while (x != 0);
    }
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00117478(void* self, s32 unused, Node_117478* x)
{
    Node_117478 q;
    func_0011B008(&q);
    (void)func_0011B0A8(&q, x);
    if (x->next == 0) {
        x = 0;
    } else {
        x = x->child;
    }
    if (x != 0) {
        do {
            if (q.tag == 0x14) {
                if (x->tag == 0x14) {
                    if (x->v.i < q.v.i) {
                        func_0011B0A8(&q, x);
                    }
                } else {
                    if (x->v.f < (f32)q.v.i) {
                        func_0011B0A8(&q, x);
                    }
                }
            } else {
                if (x->tag == 0x14) {
                    if ((f32)x->v.i < q.v.f) {
                        func_0011B0A8(&q, x);
                    }
                } else {
                    f32 pf = x->v.f;
                    if (pf < q.v.f) {
                        func_0011B0A8(&q, x);
                    }
                }
            }
            x = x->next;
        } while (x != 0);
    }
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_117598 { s32 a, b, c, d; };
struct Rec_117598 { s32 f0; s32 f4; s32 f8; s32 fC; };

void* func_0011B008(Quad_117598* q);
void func_0011B018(void* dst, Quad_117598* src);
void func_0011B060(Quad_117598* q, s32 mode);
void func_0011B570(Quad_117598* q, s32 v);

void* func_00117598(void* self, void* unused, Rec_117598* r)
{
    Quad_117598 t;
    func_0011B008(&t);
    s32 v = r->f4 % r->fC;
    func_0011B570(&t, v);
    func_0011B018(self, &t);
    func_0011B060(&t, 2);
    return self;
}

void* func_00117610(void* self)
{
    Quad_117610 q;
    func_0011B008(&q);
    func_0011B5B0(&q, D_0026185C);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00117668(void* ret, s32 limit, Src_117668* src)
{
    Quad_117668 q;
    QP_117668 r;
    TQ_117668 t;
    func_0011B008(&r);
    Node_117668* a = (Node_117668*)func_0011AF28();
    Node_117668* b = (Node_117668*)func_0011AF28();
    Node_117668* c = (Node_117668*)func_0011AF28();
    Node_117668* d = (Node_117668*)func_0011AF28();
    Node_117668* e;
    Node_117668* f;
    e = (Node_117668*)func_0011AF28();
    f = (Node_117668*)func_0011AF28();
    func_0011B6C0(a, b);
    func_0011B9A8(&t, src);
    func_0011B5B0(b, t.f4);
    func_0011B060(&t, 2);
    b->next = c;
    func_0011B6C0(c, d);
    func_0011B6C0(d, e);
    func_0011B538(e, 0x11);
    e->next = f;
    func_0011B700(f, ((s32*)src)[3]);
    s32 idx = D_00259DE8;
    if (idx < limit) {
        Node_117668* n = *(Node_117668**)(idx * 8 + (u8*)src + 4);
        if (n) {
            Node_117668* prev = d;
            do {
                d = (Node_117668*)func_0011AF28();
                e = (Node_117668*)func_0011AF28();
                func_0011B6C0(d, e);
                func_0011B538(e, 0x11);
                e->next = n;
                prev->next = d;
                Node_117668* nx = n->next;
                n->next = 0;
                n = nx;
                prev = d;
            } while (n);
        }
    }
    func_0011A498(D_00275710->f2C, D_00275710->f1EF8, 0, &r);
    if (r.a == 0x1E) {
        a->next = (Node_117668*)r.b;
    }
    func_0011B6C0(&r, a);
    func_0011A400(&t, D_00275710->f2C, D_00275710->f1EF8, &r);
    func_0011B060(&t, 2);
    func_0011B018(ret, &q);
    func_0011B060(&r, 2);
    return ret;
}

void* func_00117880(void* ret, s32 unused, Src_117880* src)
{
    Tmp_117880 t;
    Tmp_117880 u;
    func_0011B008(&t);
    Obj_117880* obj = src->obj;
    func_0011B9A8(&u, (u8*)src + 8);
    f32 f = ((f32*)&u)[1];
    func_0011B060(&u, 2);
    obj->value = f;
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

void* func_00117910(void* a0, void* a1, Src_117910* a2, void* a3, s32 a4)
{
    Quad_117910 q1;
    Quad_117910 q2;

    func_0011B008(&q1);
    s32 x1 = a2->f4;
    s32 x2 = a2->fC;
    switch (a4) {
    case 0x63:
        func_001C22B8((Sub_117910*)&q2, x1, x2, &a2->f10);
        func_0011B0A8(&q1, &q2);
        func_0011B060(&q2, 2);
        break;
    case 0x64:
        func_001C2320((Sub_117910*)&q2, x1, x2, &a2->f10);
        func_0011B0A8(&q1, &q2);
        func_0011B060(&q2, 2);
        break;
    case 0x65:
        func_001C2238((Sub_117910*)&q2, x1, x2, &a2->f10);
        func_0011B0A8(&q1, &q2);
        func_0011B060(&q2, 2);
        break;
    case 0x66:
        func_001C21A0((Sub_117910*)&q2, x1, x2);
        func_0011B0A8(&q1, &q2);
        func_0011B060(&q2, 2);
        break;
    }
    func_0011B018(a0, &q1);
    func_0011B060(&q1, 2);
    return a0;
}

void* func_00117A30(void* ret, s32 a1, void* src, s32 a3)
{
    func_00117910(ret, a1, src, a3, 0x63);
    return ret;
}

void* func_00117A60(void* ret, s32 a1, void* src, s32 a3)
{
    func_00117910(ret, a1, src, a3, 0x64);
    return ret;
}

void* func_00117A90(void* ret, s32 a1, void* src, s32 a3)
{
    func_00117910(ret, a1, src, a3, 0x65);
    return ret;
}

void* func_00117AC0(void* ret, s32 a1, void* src, s32 a3)
{
    func_00117910(ret, a1, src, a3, 0x66);
    return ret;
}

void* func_00117AF0(void* self, s32 count, s32* values)
{
    Quad_117AF0 q;
    func_0011B008(&q);
    if (count != 0) {
        Node_117AF0* prev = 0;
        if (count > 0) {
            s32* v = values;
            s32 n = count;
            do {
                Node_117AF0* node = (Node_117AF0*)func_0011AF28();
                if (prev) {
                    prev->next = node;
                } else {
                    func_0011B6C0(&q, node);
                }
                func_0011B8A8(node, *v);
                prev = node;
                v++;
            } while (--n != 0);
        }
    } else {
        func_0011B538(&q, 0);
    }
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00117BC8(void* out, s32 unused, In_117BC8* in)
{
    Quad_117BC8 q;
    s32 r;
    func_0011B008(&q);
    s32 flag = 0x105;
    s32 k = 0x101;
    if (in->wc != 0) flag = k;
    r = func_0015A418(D_00275710, flag, in->w4, in->wc);
    func_0011B8A8(&q, r);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

void* func_00117C48(void* out, s32 unused, In_117C48* in)
{
    Quad_117C48 q;
    u8 buf[0x100];
    Quad_117C48 t;
    (void)func_0011B008(&q);
    s32 r = func_0015A198(D_00275710, in->wc ? 0x101 : 0x105, in->w4, (void*)in->wc, 0x40, buf);
    func_00117AF0(&t, r, buf);
    (void)func_0011B0A8(&q, &t);
    (void)func_0011B060(&t, 2);
    (void)func_0011B018(out, &q);
    (void)func_0011B060(&q, 2);
    return out;
}

void* func_00117D00(void* out, s32 unused, In_117D00* in)
{
    Quad_117D00 q;
    s32 r;
    func_0011B008(&q);
    r = func_0015A418(D_00275710, 0x104, in->w4, in->wc);
    func_0011B8A8(&q, r);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

void* func_00117D78(void* out, s32 unused, In_117D78* in)
{
    Quad_117D78 q;
    u8 buf[0x100];
    Quad_117D78 t;
    (void)func_0011B008(&q);
    s32 r = func_0015A198((Host_117D78*)D_00275710, 0x104, in->w4, (void*)in->wc, 0x40, buf);
    func_00117AF0(&t, r, buf);
    (void)func_0011B0A8(&q, &t);
    (void)func_0011B060(&t, 2);
    (void)func_0011B018(out, &q);
    (void)func_0011B060(&q, 2);
    return out;
}

void* func_00117E20(void* self)
{
    Quad_117E20 q;
    func_0011B008(&q);
    (void)func_0011B8A8(&q, (s32)func_001925F0());
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00117E78(void* self)
{
    Quad_117E78 q;
    s32 r = func_0011B008(&q);
    func_0011B8A8(&q, (s32)D_00275710);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00117ED0(void* self)
{
    Quad_117ED0 q;
    s32 r = func_0011B008(&q);
    func_0011B8A8(&q, (s32)D_00261990);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00117F28(void* out, s32 unused, In_117F28* in)
{
    Quad_117F28 q;
    u8 buf[0x400];
    Quad_117F28 t;
    (void)func_0011B008(&q);
    s32 r = func_0015A4F0((Host_117F28*)D_00275710, in->wc ? 0x101 : 0x105, in->w4, (void*)in->wc, 0x100, buf);
    func_00117AF0(&t, r, buf);
    (void)func_0011B0A8(&q, &t);
    (void)func_0011B060(&t, 2);
    (void)func_0011B018(out, &q);
    (void)func_0011B060(&q, 2);
    return out;
}

ASM_FUNC(func_00117FE0);

void* func_001180C0(void* out, s32 unused, In_1180C0* in)
{
    Frame_1180C0 f;
    f32 scale;
    func_0011B008(&f.q);
    if (in->kind == 0x14) scale = (f32)in->raw.i; else scale = in->raw.f;
    func_0018D608();
    func_001DC4D0(D_00275710, scale, 0, in->w4, 0, 0, &f.a, &f.b);
    func_00117AF0(&f.t, f.a, f.b);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0018D6F0();
    func_0011B018(out, &f.q);
    func_0011B060(&f.q, 2);
    return out;
}

Val_118198 func_00118198(s32 id, s32 unused, Src_118198* src)
{
    Val_118198 l0;
    Hit_118198 hit;
    Ent_118198* slot;
    if (src->type == 0) {
        func_0011B0A8(&l0, src);
    } else {
        s32 kind = 0x71;
        Node_118198* head = 0;
        Node_118198* tail;
        Node_118198* it;
        for (it = src->head; it != 0; it = it->f8) {
            Pair_118198* pa = &src->p0;
            Pair_118198* pb = &src->p1;
            Node_118198* n1;
            Node_118198* n2;
            Node_118198* n3;
            Quad_118198* v;
            Ent_118198* e = it->f4;
            if (e == 0)
                continue;
            slot = e;
            if (func_001419E8(0, pa->b, pb->b, 1, &slot, &hit) == 0)
                continue;
            if (id == kind) {
                n1 = (struct Node_118198 *)func_0011AF28();
                n2 = (struct Node_118198 *)func_0011AF28();
                n3 = (struct Node_118198 *)func_0011AF28();
                func_0011B8A8(n1, e);
                n1->f8 = n2;
                v = (struct Quad_118198 *)func_0011C508();
                *v = hit.q[0];
                func_0011B740(n2, v);
                n2->f8 = n3;
                v = (struct Quad_118198 *)func_0011C508();
                *v = hit.q[1];
                func_0011B740(n3, v);
                n3 = (struct Node_118198 *)func_0011AF28();
                func_0011B6C0(n3, n1);
                if (head != 0)
                    tail->f8 = n3;
                else
                    head = n3;
                tail = n3;
            } else {
                n1 = (struct Node_118198 *)func_0011AF28();
                n2 = (struct Node_118198 *)func_0011AF28();
                func_0011B8A8(n1, e);
                n1->f8 = n2;
                v = (struct Quad_118198 *)func_0011C508();
                *v = hit.q[1];
                func_0011B740(n2, v);
                func_0011B6C0(&l0, n1);
                return l0;
            }
        }
        if (head != 0)
            func_0011B6C0(&l0, head);
        else
            l0.type = 0;
    }
    return l0;
}

void* func_001183B8(void* out, s32 x, s32 y, s32 z)
{
    Frame_1183B8 f;
    func_0011B008(&f.q);
    func_00118198(&f.t, 0x71, x, y, z);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0011B018(out, &f.q);
    func_0011B060(&f.q, 2);
    return out;
}

void* func_00118458(void* out, s32 x, s32 y, s32 z)
{
    Frame_118458 f;
    func_0011B008(&f.q);
    func_00118198(&f.t, 0x72, x, y, z);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_0011B018(out, &f.q);
    func_0011B060(&f.q, 2);
    return out;
}

void* func_001184F8(void* ret, s32 unused, Src_1184F8* src)
{
    Tmp_1184F8 t;
    func_0011B008(&t);
    void* p = func_0011C508();
    (void)func_00128018(src->a, src->b, src->c, p);
    func_0011B740(&t, p);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

void* func_00118580(void* ret, s32 unused, Src_118580* src)
{
    Tmp_118580 t;
    func_0011B008(&t);
    void* p = func_0011C508();
    (void)func_001280C0(src->a, src->b, src->c, p);
    func_0011B740(&t, p);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

void* func_00118608(void* out, s32 unused, In_118608* in)
{
    Frame_118608 f;
    void* obj;
    func_0011B008(&f.q);
    obj = func_0011C618();
    func_00128150(in->f4, in->fC, in->f14, obj);
    func_001884C0(obj);
    func_0011B788(&f.q, obj);
    func_0011B018(out, &f.q);
    func_0011B060(&f.q, 2);
    return out;
}

ASM_FUNC(func_00118698);

void* func_00118720(void* out, s32 unused, In_118720* in)
{
    Frame_118720 f;
    func_0011B008(&f.q);
    f.n = 0;
    func_001BFCD8(in->f4, in->fC ? &f.n : 0, in->fC, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f);
    func_0011B570(&f.q, f.n);
    if (f.n != 0) func_001BF718(&f.n);
    func_0011B018(out, &f.q);
    func_0011B060(&f.q, 2);
    return out;
}

void* func_001187E8(void* ret, s32 unused, Src_1187E8* src)
{
    Tmp_1187E8 t;
    func_0011B008(&t);
    func_001BF788(src->a, 0);
    t.w0 = 0x22;
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

void* func_00118850(void* ret, s32 unused, Src_118850* src)
{
    Vec_118850 t;
    Vec_118850 u;
    func_0011B008(&t);
    void* p = D_00262C70;
    s32 n = src->n;
    func_0011B9A8(&u, (u8*)src + 8);
    func_0016EC38(p, n, u.y);
    func_0011B060(&u, 2);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

void* func_001188F0(void* ret, s32 unused, Src_1188F0* src)
{
    Vec_1188F0 t;
    Vec_1188F0 u;
    func_0011B008(&t);
    void* s1 = src->p4;
    func_0011B9A8(&u, (u8*)src + 8);
    func_001566C8(s1, u.y);
    func_0011B060(&u, 2);
    func_0011B538(&t, 0x22);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

INCLUDE_ASM(func_00118988);

INCLUDE_ASM(func_00118CF0);

Quad_118D10* func_00118D10(Quad_118D10* out, void* src)
{
    Quad_118D10 v = *(Quad_118D10*)src;
    *out = v;
    return out;
}

Quad_118D20* func_00118D20(Quad_118D20* out, Quad_118D20 v)
{
    *out = v;
    return out;
}

ASM_FUNC(func_00118D30);

void* func_00118D48(void* ret, Src_118D48* src, void* ctx)
{
    Tmp_118D48 t;
    func_0011B008(&t);
    (void)func_0011A498(ctx, src->a, 1, &t);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

void* func_00118DB8(void* self, Node_118DB8* x, s32 c)
{
    Quad_118DB8 q;
    Quad_118DB8 t;
    func_0011B008(&q);
    Node_118DB8* p = x->f4;
    Node_118DB8* m = p->f8;
    func_0011A080(&t, m->f8, c);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011A400(&t, c, m->f4, &q);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00118E80(void* self, Node_118E80* x, s32 c)
{
    Quad_118E80 q;
    Quad_118E80 t;
    func_0011B008(&q);
    Node_118E80* p = x->f4;
    Node_118E80* m = p->f8;
    func_0011A080(&t, m->f8, c);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011A358(&t, c, m->f4, &q);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

// The message func_00118F48 prints, kept as retail's bytes: retail places it on 16 bytes, 8 past
// where GCC puts the literal (the 8 zero bytes before it are not explained yet).
extern const char D_00249200[];
INCLUDE_RODATA(D_00249200);

void* func_00118F48(void* self, void* p, s32 x)
{
    Frame_118F48 f;
    func_0011B008(&f.q);
    u8* a = *(u8**)((u8*)p + 4);
    u8* b = *(u8**)(a + 8);
    u8* c = *(u8**)(b + 8);
    func_0011A080(&f.t, b, x);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    if (f.q.b == 0) {
        u8* v = *(u8**)(c + 4);
        u8* w = *(u8**)(v + 8);
        func_001E1F10(D_00249200);
        func_00113730(&f.t, 1, w, x);
        func_0011B060(&f.t, 2);
    }
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

void* func_00119030(void* self, Node_119030* x, s32 c)
{
    Quad_119030 q;
    Quad_119030 t;
    Node_119030* m;
    Node_119030* n2;
    Node_119030* n3;
    func_0011B008(&q);
    m = x->f4->f8;
    n2 = m->f8;
    n3 = n2->f8;
    func_0011A080(&t, m, c);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    if (q.w[1] == 1) {
        func_0011A080(&t, n2, c);
        func_0011B0A8(&q, &t);
        func_0011B060(&t, 2);
    } else if (n3 != 0) {
        func_0011A080(&t, n3, c);
        func_0011B0A8(&q, &t);
        func_0011B060(&t, 2);
    } else {
        func_0011B538(&q, 0x22);
    }
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00119128(void* out, Args_119128* a1, void* a2)
{
    Cursor_119128 L;
    Cursor_119128 M;
    Node_119128* n;

    func_0011B008(&L);
    n = a1->holder->head;
    if (n != 0) {
        do {
            func_0011A080(&M, n, a2);
            func_0011B0A8(&L, &M);
            func_0011B060(&M, 2);
            if (L.tag != 27 || L.value != 0) {
                func_0011B018(out, &L);
                func_0011B060(&L, 2);
                goto done;
            }
            n = n->next;
        } while (n != 0);
    }
    func_0011B5F0(&L, 0);
    func_0011B018(out, &L);
    func_0011B060(&L, 2);
done:
    return out;
}

Cursor_119218 func_00119218(Args_119218* a1, void* a2)
{
    Cursor_119218 L;
    func_0011B5F0(&L, 1);
    for (Node_119218* n = a1->holder->head; n != 0; n = n->next) {
        func_0011B0A8(&L, func_0011A080(n, a2));
        if (L.tag == 27 && L.value == 0)
            return L;
    }
    return L;
}

void* func_00119310(void* self, Node_119310* x, s32 c)
{
    Quad_119310 q, r, t;
    func_0011B008(&q);
    func_0011B008(&r);
    func_0011B538(&q, 0x22);
    Node_119310* n = x->f4->f8;
    while (n) {
        Node_119310* e = n->f4;
        s32 flag;
        if (e->kind == 10) {
            flag = 1;
        } else {
            func_0011A080(&t, e, c);
            flag = 0;
            func_0011B0A8(&r, &t);
            func_0011B060(&t, 2);
            if (r.kind != 0x1B || r.p != 0)
                flag = 1;
            if (flag && e->f8 == 0)
                func_0011B0A8(&q, &r);
        }
        if (flag) {
            e = e->f8;
            while (e) {
                func_0011A080(&t, e, c);
                func_0011B0A8(&q, &t);
                func_0011B060(&t, 2);
                e = e->f8;
            }
            n = 0;
        } else {
            n = n->f8;
        }
    }
    func_0011B018(self, &q);
    func_0011B060(&r, 2);
    func_0011B060(&q, 2);
    return self;
}

void* func_001194A8(void* self, Link_1194A8* h, void* arg)
{
    Quad_1194A8 a;
    Quad_1194A8 b;
    Quad_1194A8 c;
    Quad_1194A8 d;
    func_0011B008(&a);
    u8* p = (u8*)&b;
    for (s32 k = 1; k != -1; k--) {
        func_0011B008(p);
        p += 8;
    }
    func_0011B008(&c);
    func_0011B538(&a, 0x22);
    Link_1194A8* s0 = ((Owner_1194A8*)h)->f4->f8;
    func_0011A080(&d, s0, arg);
    func_0011B0A8(&b, &d);
    func_0011B060(&d, 2);
    h = s0->f8;
    if (h) do {
        Link_1194A8* e = h->f4;
        s32 found;
        if (e->f0 == 10) {
            found = 1;
        } else {
            found = 0;
            Link_1194A8* x = e->f4;
            if (x) {
                do {
                    func_0011B0A8((u8*)&b + 8, x);
                    func_00113AA8(&d, 2, &b, arg);
                    func_0011B0A8(&c, &d);
                    func_0011B060(&d, 2);
                    if (c.type == 0x1B && c.head != 0) {
                        found = 1;
                        x = 0;
                    } else {
                        x = x->f8;
                    }
                } while (x);
            }
        }
        if (found) {
            e = e->f8;
            if (e) {
                do {
                    func_0011A080(&d, e, arg);
                    func_0011B0A8(&a, &d);
                    func_0011B060(&d, 2);
                    e = e->f8;
                } while (e);
            }
            h = 0;
        } else {
            h = h->f8;
        }
    } while (h);
    func_0011B018(self, &a);
    func_0011B060(&c, 2);
    u8* p2 = (u8*)&c;
    if ((u8*)&b != p2) {
        do {
            p2 -= 8;
            func_0011B060(p2, 0);
        } while ((u8*)&b != p2);
    }
    func_0011B060(&a, 2);
    return self;
}

void* func_001196C8(void* self, Node_1196C8* x, void* c)
{
    Quad_1196C8 q, r, u, t;
    func_0011B008(&q);
    func_0011B008(&r);
    func_0011B008(&u);
    Node_1196C8* p = x->f4->f8;
    void* d;
    Node_1196C8* n;
    if (p->kind == 0x1E) {
        d = func_0011A630();
        Node_1196C8* l = p->f4;
        if (l) {
            do {
                Node_1196C8* e = l->f4;
                Quad_1196C8* pr = &r;
                func_0011A080(&t, e->f8, c);
                func_0011B0A8(pr, &t);
                func_0011B060(&t, 2);
                func_0011A358(&t, d, e->f4, pr);
                func_0011B0A8(&u, &t);
                func_0011B060(&t, 2);
                l = l->f8;
            } while (l);
        }
        func_0011A328(d, c);
    } else {
        d = c;
    }
    n = p->f8;
    while (n) {
        func_0011A080(&t, n, d);
        func_0011B0A8(&q, &t);
        func_0011B060(&t, 2);
        n = n->f8;
    }
    func_0011B018(self, &q);
    func_0011B060(&u, 2);
    func_0011B060(&r, 2);
    func_0011B060(&q, 2);
    return self;
}

void* func_00119878(void* self, Owner_119878* owner, s32 c)
{
    Quad_119878 q, t;
    s32 a, b;
    func_0011B008(&q);
    Node_119878* first = owner->wrap->first;
    Node_119878* second = first->next;
    for (;;) {
        func_0011A080(&t, first, c);
        func_0011B0A8(&q, &t);
        func_0011B060(&t, 2);
        a = q.w[0];
        if (a != 0x1B)
            goto other;
        b = q.w[1];
        if (b != 0)
            goto other;
        break;
    other:
        func_0011A080(&t, second, c);
        func_0011B0A8(&q, &t);
        func_0011B060(&t, 2);
    }
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00119970(void* self, Owner_119970* owner, s32 c)
{
    Quad_119970 q;
    func_0011B008(&q);
    Item_119970* first = owner->wrap->first;
    Item_119970* after = first->next;
    Rec_119970* p = (Rec_119970*)func_0011AFC8();
    p->c = c;
    if (first->tag == 0)
        p->head = 0;
    else
        p->head = first->child;
    p->after = after;
    s32 found = 0;
    s32 count = 0;
    Item_119970* n = p->head;
    while (n != 0) {
        if (n->tag == 0x13) {
            found = 1;
            n = 0;
        } else {
            n = n->next;
            count++;
        }
    }
    p->count = count;
    p->found = found;
    func_0011B700(&q, p);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00119A58(void* out, Node_119A58* list, s32 c)
{
    Quad_119A58 q, t;
    func_0011B008(&q);
    Node_119A58* n = list;
    do {
        func_0011A080(&t, n, c);
        func_0011B0A8(&q, &t);
        func_0011B060(&t, 2);
        n = n->next;
    } while (n);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

void* func_00119AF8(void* self, Owner_119AF8* owner, s32 c)
{
    Quad_119AF8 q, t;
    func_0011B008(&q);
    func_0011B538(&q, 0x22);
    Node_119AF8* n = owner->wrap->first;
    while (n != 0) {
        func_0011A080(&t, n, c);
        func_0011B0A8(&q, &t);
        func_0011B060(&t, 2);
        n = n->next;
    }
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

V_119BB0* func_00119BB0(V_119BB0* ret, Node_119BB0* self, void* ctx)
{
    Node_119BB0* node;
    V_119BB0 a;
    V_119BB0 b;
    V_119BB0 arr[32];
    V_119BB0 t;
    V_119BB0 u;
    s32 total;
    Ent_119BB0* ent;
    O21_119BB0* o21;
    Def_119BB0* d;
    s32 n;
    s32 last;
    s32 count;
    s32 i;
    V_119BB0* p;

    func_0011B008(&a);
    func_0011B008(&b);
    p = arr;
    for (s32 k = 31; k != -1; k--) {
        func_0011B008(p);
        p++;
    }
    Node_119BB0* first = (Node_119BB0*)self->f4;
    func_0011A080(&t, first, ctx);
    func_0011B0A8(&a, &t);
    func_0011B060(&t, 2);
    if (a.type == 0x1D) {
        ent = &D_00259958[(s32)a.p];
        n = ent->f4;
        last = ent->f8;
    } else if (a.type == 0x21) {
        o21 = (O21_119BB0*)a.p;
        last = 0;
        n = o21->f8;
    } else {
        d = (Def_119BB0*)a.p;
        n = d->f8;
        last = d->fC;
    }
    node = first->f8;
    total = n + (last != 0);
    count = n;
    for (i = 0; i < n; i++) {
        V_119BB0* bp = &b;
        func_0011A080(&t, node, ctx);
        func_0011B0A8(bp, &t);
        func_0011B060(&t, 2);
        func_0011B0A8(&arr[i], bp);
        node = node->f8;
    }
    if (last) {
        V_119BB0* tail = 0;
        V_119BB0* head = 0;
        Node_119BB0* m;
        for (m = node; m; m = m->f8) {
            V_119BB0* e = (V_119BB0*)func_0011AF28();
            func_0011A080(&t, m, ctx);
            func_0011B0A8(e, &t);
            func_0011B060(&t, 2);
            if (tail) {
                ((Node_119BB0*)tail)->f8 = (Node_119BB0*)e;
                tail = e;
            } else {
                tail = e;
                head = e;
            }
            count++;
        }
        if (head) {
            func_0011B6C0(&arr[i], head);
        } else {
            func_0011B538(&arr[i], 0);
        }
    }
    switch (a.type) {
    case 0x1D:
        ent->f0(&t, count, arr, ctx);
        func_0011B0A8(&b, &t);
        func_0011B060(&t, 2);
        break;
    case 0x1F: {
        d = (Def_119BB0*)a.p;
        void* s = func_0011A630();
        func_0011A328(s, d->f0);
        Node_119BB0* q = d->f4;
        for (i = 0; i < total; i++) {
            func_0011B008(&t);
            if (0x13 == q->f0) {
                q = q->f8;
            }
            func_0011A358(&u, s, q->f4, &arr[i]);
            func_0011B0A8(&t, &u);
            func_0011B060(&u, 2);
            q = q->f8;
            func_0011B060(&t, 2);
        }
        func_00119A58(&t, d->f10, s);
        func_0011B0A8(&b, &t);
        func_0011B060(&t, 2);
        break;
    }
    case 0x21:
        o21->f4(&t, o21->f0, count, arr);
        func_0011B0A8(&b, &t);
        func_0011B060(&t, 2);
        break;
    }
    func_0011B018(ret, &b);
    p = &t;
    while (arr != p) {
        p--;
        func_0011B060(p, 0);
    }
    func_0011B060(&b, 2);
    func_0011B060(&a, 2);
    return ret;
}

void* func_00119FA0(void* self, Outer_119FA0* src, void* item)
{
    Blob_119FA0 a;
    Blob_119FA0 b;
    void* found;
    s32 id;

    func_0011B008(&a);
    id = src->mid->inner->id;
    found = func_001C1390(id, (u8*)D_00275710);
    if (found == 0) {
        func_001C13E8(&b, id, (u8*)D_00275710);
        func_0011B0A8(&a, &b);
        func_0011B060(&b, 2);
        found = func_001C1390(id, (u8*)D_00275710);
    }
    func_0011A338(item, found);
    func_0011B538(&a, 0x22);
    func_0011B018(self, &a);
    func_0011B060(&a, 2);
    return self;
}

Ret_11A080* func_0011A080(Ret_11A080* ret, In_11A080* in, s32 arg)
{
    Tmp_11A080 t;
    Tmp_11A080 u;
    void* src;
    Inner_11A080* p;
    func_0011B008(&t);
    switch (in->kind) {
    case 0:
    case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27:
    case 29:
    case 32: case 33:
        src = in;
        goto copy;
    case 28:
        func_00118D48(&u, in, arg);
        goto tail;
    case 30:
        p = in->inner;
        switch (p->type) {
        case 1: func_00118DB8(&u, in, arg); goto tail;
        case 2: func_00118E80(&u, in, arg); goto tail;
        case 5: func_00118F48(&u, in, arg); goto tail;
        case 6: func_00119030(&u, in, arg); goto tail;
        case 7: func_00119128(&u, in, arg); goto tail;
        case 8: func_00119218(&u, in, arg); goto tail;
        case 9: func_00119310(&u, in, arg); goto tail;
        case 11: func_001194A8(&u, in, arg); goto tail;
        case 12: func_001196C8(&u, in, arg); goto tail;
        case 13: func_00119878(&u, in, arg); goto tail;
        case 15: func_00119AF8(&u, in, arg); goto tail;
        case 14: func_00119970(&u, in, arg); goto tail;
        case 17:
            src = (void*)p->f8;
        copy:
            func_0011B0A8(&t, src);
            goto end;
        case 16:
            func_00119FA0(&u, in, arg);
        tail:
            func_0011B0A8(&t, &u);
            func_0011B060(&u, 2);
            goto end;
        default:
            func_00119BB0(&u, in, arg);
            func_0011B0A8(&t, &u);
            func_0011B060(&u, 2);
            break;
        }
        break;
    default:
        break;
    }
end:
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

void func_0011A328(Slot_11A328* slot, s32 value)
{
    slot->value = value;
    slot->flag = 1;
}

void func_0011A338(IntList* list, int value)
{
    list->items[list->count++] = value;
}

void* func_0011A358(void* self, Owner_11A358* owner, s32 kind, void* body)
{
    Blob_11A358 a;
    Node_11A358* node;

    func_0011B008(&a);
    node = (Node_11A358*)func_0011C498();
    node->kind = kind;
    (void)func_0011B0A8(node->body, body);
    node->next = owner->head;
    owner->head = node;
    func_0011B538(&a, 0x22);
    func_0011B018(self, &a);
    func_0011B060(&a, 2);
    return self;
}

void* func_0011A400(void* self, void* table, void* key, void* item)
{
    Blob_11A400 a;
    void* found;

    func_0011B008(&a);
    found = func_0011A4D8(table, key, 1);
    if (found != 0) {
        (void)func_0011B0A8(found, item);
    }
    func_0011B538(&a, 0x22);
    func_0011B018(self, &a);
    func_0011B060(&a, 2);
    return self;
}

s32 func_0011A498(void* a, s32 b, s32 c, void* d)
{
    void* r = func_0011A4D8(a, b, c, d);
    if (r != 0) {
        if (d)
            func_0011B0A8(d, r);
        return 1;
    }
    return 0;
}

void* func_0011A4D8(struct Tree_11A4D8* self, s32 key, s32 flag)
{
    void* found = 0;
    struct Node_11A4D8* n;
    s32 i;

    self->flag = 1;
    for (n = self->head; n != 0; n = n->next) {
        if (n->key == key) {
            found = &n->value;
            goto done;
        }
    }
    if (flag != 0) {
        for (i = 0; i < self->count; i++) {
            struct Tree_11A4D8* c = self->items[i];
            if (c->flag == 0) {
                found = func_0011A4D8(c, key, flag);
                if (found != 0)
                    goto done;
            }
        }
    }
done:
    self->flag = 0;
    return found;
}

void func_0011A5B0(struct Tree_11A5B0* src, struct Tree_11A5B0* dst)
{
    dst->count = src->count;
    func_0018D800(dst->items, src->items, src->count * 4);
    if (src->head != 0) {
        void* n = (void*)func_0011C498();
        func_0011C418(src->head, n, dst);
        dst->head = (struct Node_11A5B0*)n;
    }
}

void* func_0011A630(void)
{
    void* p = func_0011C240(D_0025C270);
    func_001F5C0C(p, 0, 0x1C);
    return p;
}

void func_0011A670(void)
{
}

Gc_259F38::Gc_259F38()
{
}

Gc_259F38::~Gc_259F38()
{
}

void func_0011A6A8(Counters_11A6A8* self)
{
    self->count = 0;
    self->count2 = 0;
}

void func_0011A6B8() {}

void func_0011A6C0(IntList* list, int value)
{
    for (int i = 0; i < list->count; i++)
        if (list->items[i] == value)
            return;
    list->items[list->count++] = value;
}

void func_0011A708(Obj_0011A708* obj, s32 value) { obj->values[obj->count++] = value; }

void func_0011A728(Obj_0011A728* obj, s32 value) { obj->values[obj->count++] = value; }

int func_0011A748(StackAt708* stack)
{
    if (stack->count > 0)
        return stack->items[--stack->count];
    return 0;
}

void func_0011A770(Obj_0011A770* obj, s32 value) { obj->values[obj->count++] = value; }

s32 func_0011A790(Stack_11A790* s)
{
    if (s->count > 0) {
        s32 n = s->count - 1;
        s->count = n;
        return s->items[n];
    }
    return 0;
}

void func_0011A7B8(Stack_11A7B8* s, s32 value)
{
    s32 n = s->count;
    s->items[n] = value;
    s->count = n + 1;
}

s32 func_0011A7D8(Stack_11A7D8* s)
{
    s32 n = s->count;
    if (n > 0) {
        n = n - 1;
        s->count = n;
        return s->items[n];
    }
    return 0;
}

void func_0011A800(void)
{
    func_0011C2A0(D_0025C250);
    func_0011C2A0(D_0025C270);
    func_0011C2A0(D_0025C290);
    func_0011C2A0(D_0025C2B0);
    func_0011C2A0(D_0025C2D0);
}

void func_0011A850(Stk_11A850* self)
{
    Obj_11A850* obj;
    Obj_11A850* other;
    Obj_11A850* group;
    for (;;) {
        group = func_0011A748(self);
        if (group) {
            Obj_11A850* link = group->f14;
            if (link) {
                do {
                    func_0011C3F0(link);
                    Obj_11A850* ev = (Obj_11A850*)&link->f4;
                    switch (ev->f0) {
                    case 0x1E:
                        obj = ev->f4;
                        if (func_0011C3C8(obj)) {
                            func_0011C3F0(obj);
                            func_0011A770(self, obj);
                        }
                        break;
                    case 0x1F:
                        other = ev->f4;
                        if (func_0011C3C8(other)) {
                            func_0011C3F0(other);
                            func_0011A7B8(self, other);
                        }
                        break;
                    case 0x21:
                        func_0011C3F0(ev->f4);
                        break;
                    }
                    link = link->fC;
                } while (link);
            }
            if (group->f0 > 0) {
                s32 i = 0;
                Obj_11A850** p = &group->f4;
                do {
                    obj = *p;
                    if (func_0011C3C8(obj)) {
                        func_0011C3F0(obj);
                        func_0011A728(self, obj);
                    }
                    i++;
                    p++;
                } while (i < group->f0);
            }
            continue;
        }
        Batch_11A850* b = func_0011A7D8(self);
        if (b) {
            obj = b->f4;
            if (obj) {
                do {
                    func_0011C3F0(obj);
                    obj = obj->f8;
                } while (obj);
            }
            obj = b->f10;
            if (func_0011C3C8(obj)) {
                func_0011C3F0(obj);
                func_0011A770(self, obj);
            }
            group = b->f0;
            if (func_0011C3C8(group)) {
                func_0011C3F0(group);
                func_0011A728(self, group);
            }
            continue;
        }
        obj = func_0011A790(self);
        if (!obj)
            return;
        switch (obj->f0) {
        case 0x1E:
            other = obj->f4;
            if (func_0011C3C8(other)) {
                func_0011C3F0(other);
                func_0011A770(self, other);
            }
            break;
        case 0x1F:
            other = obj->f4;
            if (func_0011C3C8(other)) {
                func_0011C3F0(other);
                func_0011A7B8(self, other);
            }
            break;
        case 0x21:
            func_0011C3F0(obj->f4);
            break;
        }
        obj = obj->f8;
        if (obj) {
            if (func_0011C3C8(obj)) {
                func_0011C3F0(obj);
                func_0011A770(self, obj);
            }
        }
    }
}

void func_0011AB58(World_11AB58* w) {
    func_0011C2B0(D_0025C250);
    func_0011C2B0(D_0025C270);
    func_0011C2B0(D_0025C290);
    func_0011C2B0(D_0025C2B0);
    func_0011C2B0(D_0025C2D0);
    s32 i = w->count;
    *(s32*)((u8*)w + 0x708) = 0;
    *(s32*)((u8*)w + 0xF0C) = 0;
    *(s32*)((u8*)w + 0x1310) = 0;
    for (i--; i >= 0; i--) {
        Ent_11AB58* e = w->ents[i];
        if (func_0011C3C8(e)) {
            func_0011C3F0(e);
            func_0011A728(w, e);
        }
    }
    s32 j = w->n504;
    for (j--; j >= 0; j--) {
        Node_11AB58* n = w->lists[j]->head;
        while (n) {
            func_0011C3F0((Ent_11AB58*)n);
            Sub_11AB58* sp = &n->sub;
            switch (sp->type) {
            case 0x1E: {
                Ent_11AB58* e = sp->ent;
                if (func_0011C3C8(e)) {
                    func_0011C3F0(e);
                    func_0011A770(w, e);
                }
                break;
            }
            case 0x1F: {
                Ent_11AB58* e = sp->ent;
                if (func_0011C3C8(e)) {
                    func_0011C3F0(e);
                    func_0011A7B8(w, e);
                }
                break;
            }
            case 0x21:
                func_0011C3F0(sp->ent);
                break;
            }
            n = n->fC;
        }
    }
    for (S1DBBD8* it = (S1DBBD8*)D_00275710->f1EC8; it; it = it->next) {
        if ((void*)it->fn == (void*)func_001834A0) {
            Ent_11AB58* e = (Ent_11AB58*)it->p0C;
            if (e && func_0011C3C8(e)) {
                func_0011C3F0(e);
                func_0011A770(w, e);
            }
        }
    }
    func_0011A850(w);
    func_0011C2E8(D_0025C250);
    func_0011C2E8(D_0025C270);
    func_0011C2E8(D_0025C290);
    func_0011C2E8(D_0025C2B0);
    func_0011C2E8(D_0025C2D0);
}
