// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

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

void func_0011B008(void* obj);
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

void func_0011B008(void* obj);
Node_116600* func_0011AF28(void);
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

void func_0011B008(void* obj);
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

void func_0011B008(void* obj);
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

void func_0011B008(void* obj);
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

void func_0011B008(void* self);
void* func_0011C968(void);
void func_0011B9A8(void* out, void* src);
void func_0011B0A8(void* self, void* other);
void func_0011B060(void* self, s32 n);
void func_0011B860(void* a, void* b);
void func_0011B018(void* dst, void* src);



struct Vec_116DC8 { f32 x, y, z, w; };
struct Src_116DC8 { s32 pad0; f32* poly; s32 pad8; f32* range; };
void func_0011B008(void* self);
void func_0011B9A8(void* out, void* src);
void* func_0011B5B0(void* obj, f32 x);
void func_0011B060(void* self, s32 n);
void func_0011B018(void* dst, void* src);


struct Tmp_1171F0 { s32 w[4]; };
struct Src_1171F0 { s32 pad0; f32 v; };

void func_0011B008(void* self);
void func_0011B570(void* self, s32 n);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* self, s32 n);



struct Tmp_117880 { s32 w[4]; };
struct Obj_117880 { u8 pad[0x29C]; f32 value; };
struct Src_117880 { s32 pad0; Obj_117880* obj; };

void func_0011B008(void* self);
void func_0011B9A8(void* out, void* src);
void func_0011B060(void* self, s32 n);
void func_0011B018(void* dst, void* src);



struct Quad_114080 { s32 a, b, c, d; };
struct Tag_114080 { s32 tag; };

void func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, s32 n);
void func_0011B5F0(void* q, s32 flag);



struct Quad_1140E8 { s32 a, b, c, d; };
struct Tag_1140E8 { s32 tag; };

void func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, s32 n);
void func_0011B5F0(void* q, s32 flag);



struct Quad_114150 { s32 a, b, c, d; };
struct Tag_114150 { s32 tag; };

void func_0011B008(void* q);
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

void func_0011B008(void* self);
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
void func_0011B008(void* self);



struct Entry_1157E0 { s32 tag; s32 word; };
struct Var_1157E0 { s32 tag; f32 value; u8 pad[8]; };

void* func_0011C858();
void func_0011B9A8(void* out, void* src);
void func_0011B0A8(void* dst, void* src);
void func_0011B060(void* self, s32 mode);
void func_0011B818(void* self, void* ptr);
void func_0011B018(void* out, void* src);
void func_0011B008(void* self);



union Word_115B78 { s32 i; f32 f; };
struct Entry_115B78 { s32 tag; Word_115B78 word; };
struct Var_115B78 { s32 tag; f32 value; u8 pad[8]; };

void func_0011B008(void* self);
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

void func_0011B008(void* obj);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);
void func_0011B740(void* a, void* b);
void* func_0011C508(void);
void func_00188FD8(void* a, void* b);



struct Src_116B08 { s32 pad0; void* p; };
struct Tmp_116B08 { u8 bytes[0x10]; };
struct Vec_116B08 { f32 v[4]; };

void func_0011B008(void* obj);
void* func_0011C508(void);
void func_0011B740(void* a, void* b);
void func_00188D28(void* a, void* b, void* c);
void func_0011B6C0(void* a, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);



struct Src_116C80 { s32 pad0; void* p; };
struct Tmp_116C80 { u8 bytes[0x10]; };
struct Vec_116C80 { u8 bytes[0x30]; };

void func_0011B008(void* obj);
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

void func_0011B008(void* obj);
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
void func_0011B008(void* v);
void* func_0011B9A8(void* out, u8* src);
void func_0011B060(void* v, int mode);
void func_0011B018(void* dst, void* src);
void func_0011B7D0(void* self, void* ptr);
void func_001EB018(void* a0, f32 x, f32 y, f32 z, f32 w);



struct Vec_116FE8 { f32 x, y, z, w; };
struct Src_116FE8 { s32 pad0; void* p4; };

void func_0011B008(void* v);
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

void func_0011B008(void* self);
void func_0011B570(void* self, s32 n);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* self, s32 n);



struct Tmp_117260 { s32 w[4]; };
struct Src_117260 { s32 pad0; f32 v; };

void func_0011B008(void* self);
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

void func_0011B008(void* q);
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

void func_0011B008(void* obj);
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

void func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, int mode);
void func_0011B570(void* q, s32 v);



struct Quad_117BC8 { s32 a, b, c, d; };
struct In_117BC8 { u8 pad0[4]; s32 w4; s32 w8; s32 wc; };

extern void* D_00275710;

void func_0011B008(Quad_117BC8* q);
s32 func_0011B8A8(Quad_117BC8* q, s32 v);
void func_0011B018(void* dst, Quad_117BC8* src);
void func_0011B060(Quad_117BC8* q, int mode);
s32 func_0015A418(void* host, s32 a1, s32 a2, s32 ctx);



struct Quad_117D00 { s32 a, b, c, d; };
struct In_117D00 { u8 pad0[4]; s32 w4; s32 w8; s32 wc; };

extern void* D_00275710;

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

extern s32 D_00261990;

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

void func_0011B008(void* obj);
void* func_0011C508(void);
s32 func_0011B740(Tmp_116978* a, void* b);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* obj, s32 n);



struct Node_117360 { s32 tag; union { s32 i; f32 f; } v; Node_117360* next; Node_117360* child; };

void func_0011B008(void* q);
void func_0011B018(void* dst, void* src);
void func_0011B060(void* q, int mode);
s32 func_0011B0A8(Node_117360* a, void* b);



struct Node_117478 { s32 tag; union { s32 i; f32 f; } v; Node_117478* next; Node_117478* child; };

void func_0011B008(void* q);
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
struct Self_117668 { u8 pad0[0x2C]; void* f2C; u8 pad30[0x1EF8 - 0x30]; s32 f1EF8; };

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

extern void* D_00275710;

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

struct Quad_117D78 { s32 a, b, c, d; };
struct In_117D78 { u8 pad0[4]; s32 w4; s32 w8; s32 wc; };
struct Host_117D78;

extern void* D_00275710;

s32 func_0011B008(Quad_117D78* q);
void func_00117AF0(Quad_117D78* t, s32 a, void* b);
s32 func_0011B0A8(Quad_117D78* a, Quad_117D78* b);
s32 func_0011B060(Quad_117D78* q, int mode);
s32 func_0011B018(void* dst, Quad_117D78* src);
s32 func_0015A198(Host_117D78* host, s32 a1, s32 a2, void* ctx, s32 a4, void* a5);



struct Quad_117F28 { s32 a, b, c, d; };
struct In_117F28 { u8 pad0[4]; s32 w4; s32 w8; s32 wc; };
struct Host_117F28;

extern void* D_00275710;

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
Node_116600* func_0011AF28(void);

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


