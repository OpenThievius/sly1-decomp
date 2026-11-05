// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "c6c.h"
#include "globals.h"
#include "shapes.h"
#include "r11b008.h"
#include "r119bb0.h"
#include "s1dbbd8.h"

// The script machine's built-in functions (the table D_00259958, which func_00119BB0 calls through,
// lists them from func_00112698 on), their helpers and the collector's mark stacks: one source
// file, 0x112698 to 0x11AE78 (.rodata from 0x248FE0, .data from 0x259938 to 0x25C250, no .bss).
// A built-in has R119BB0Fn's signature (r119bb0.h); the evaluator (func_0011A080) and the
// handlers it dispatches to take the result's place, an expression (a chain of R11B008Node) and
// the scope.

// The mark stacks of the collector (func_0011A850 walks them; value.cpp's functions run it through
// func_0011AB58). Its constructor (func_0011A678) and destructor (func_0011A680) are defined below at
// their places; the compiler's initialiser, constructor and destructor for this file are
// func_0011ADF8, func_0011AE38 and func_0011AE58 (config/us/generated.tsv).
struct Gc_259F38 {
    u8 data[0x2318];        // 0x0000
    Gc_259F38();
    ~Gc_259F38();
};

// The table of one-float math functions func_00115CA0 calls by index (src/libm, and
// func_001EA408).
typedef f32 (*MathFn_259938)(f32 x);

// The pooled payloads (0011C000.cpp): the 16-byte vectors of tags 0x16 and 0x18, the 0x40-byte
// block of tag 0x17, the two and three floats of tags 0x19 and 0x1A.
f32* func_0011C508(void);
f32* func_0011C618(void);
f32* func_0011C748(void);
f32* func_0011C858(void);
f32* func_0011C968(void);
R11B008Key* func_0011C498(void);
void func_0011C418(R11B008Key* src, R11B008Key* dst, s32 first);

// The pools (value.cpp) and the collector's calls on them (0011C000.cpp).
extern u8 D_0025C250[];
extern u8 D_0025C270[];
extern u8 D_0025C290[];
extern u8 D_0025C2B0[];
extern u8 D_0025C2D0[];
void* func_0011C240(void* pool);
void func_0011C2A0(void* pool);
void func_0011C2B0(u8* pool);
void func_0011C2E8(u8* pool);

void* func_001F5C0C(void* p, s32 value, s32 size);
void func_0018D800(void* dst, void* src, s32 bytes);

// Other files' functions the built-ins call.
f32 func_00205778(f32 x, f32 y);
f32 func_001EAAE0(f32 a, f32 b);
s32 func_001EAC68(f32 a, f32 b, f32 c);
f32 func_001ED908(s32 a, s32 b, f32* c);
void func_001EDEF0(void* a0, void* a1, f32* a2, void* a3, f32 f);
void func_001EB018(f32* a0, f32 x, f32 y, f32 z, f32 w);
f32 func_001EB0F8(void* span, f32 x);
s32 func_001EB050(void* target, f32 scale);
void func_00188770(s32 a, f32* b);
void func_00189AF0(s32 a, f32* b);
void func_001891C0(s32 a, s32 b, f32* c);
void func_00188FD8(void* a, f32* b);
void func_00188D28(void* a, f32* b, f32* c);
void func_00189378(void* sub, s32 zero, void* out);
void func_00188B08(void* a, void* b, f32* c);
void func_001884C0(void* p);
void func_001C0C08(s32 index, s32 value);
void func_001F66F8(s32 v);
void* func_0015A418(void* host, s32 a1, s32 a2, s32 ctx);
s32 func_0015A198(void* host, s32 a1, s32 a2, void* ctx, s32 a4, u8* a5);
s32 func_0015A4F0(void* host, s32 a1, s32 a2, void* ctx, s32 a4, u8* a5);
void* func_001925F0(void);
R11B008* func_001C2238(R11B008* out, s32 a1, s32 a2, R11B008* a3);
R11B008* func_001C2320(R11B008* out, s32 a1, s32 a2, R11B008* a3);
R11B008* func_001C22B8(R11B008* out, s32 a1, s32 a2, R11B008* a3);
R11B008* func_001C21A0(R11B008* out, s32 a1, s32 a2);
void func_0018D608(void);
void func_0018D6F0(void);
void func_001DC4D0(void* self, f32 scale, s32 p1, s32 p2, s32 p3, s32 p4, s32* o1, u8** o2);
s32 func_00128018(void* a, s32 b, void* c, f32* d);
s32 func_001280C0(void* a, s32 b, void* c, f32* d);
void func_00128150(s32 a, s32 b, s32 c, f32* d);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void func_001BF718(void* slot);
void func_001BF788(void* self, s32 n);
void func_0016EC38(void* p, s32 n, f32 f);
void func_001566C8(void* obj, f32 f);
void func_001E1F10(const char* x);
R11B008* func_001C13E8(R11B008* out, s32 id, u8* ctx);
R11A630* func_001C1390(s32 id, u8* ctx);
void func_001834A0(void* a);

extern f32 D_0026185C;
extern u8 D_00262C70[];

// The table's records (r119bb0.h): D_00259DE8 is the count word of the last record of the first
// label (func_00117668's, 0x259DE4), the one word func_00117668 reads.
extern R119BB0 D_00259958[];
extern s32 D_00259DE8;

// The collector's views (func_0011A6A8 to func_0011AB58).
struct Stk_11A850;

// One generic record: a queued event is { type, object, next }; the lists
// and the object table use the same words.
struct Obj_11A850 {
    s32 f0;                 // 0x00
    Obj_11A850* f4;         // 0x04
    Obj_11A850* f8;         // 0x08
    Obj_11A850* fC;         // 0x0C
    Obj_11A850* f10;        // 0x10
    Obj_11A850* f14;        // 0x14
};

// What func_0011A7D8 returns: a queue of records and two objects.
struct Batch_11A850 {
    Obj_11A850* f0;         // 0x00
    Obj_11A850* f4;         // 0x04
    s32 f8;                 // 0x08
    s32 fC;                 // 0x0C
    Obj_11A850* f10;        // 0x10
};

Obj_11A850* func_0011A748(Stk_11A850* s);
void func_0011A770(Stk_11A850* s, Obj_11A850* o);
void func_0011A7B8(Stk_11A850* s, Obj_11A850* o);
void func_0011A728(Stk_11A850* s, Obj_11A850* o);
Batch_11A850* func_0011A7D8(Stk_11A850* s);
Obj_11A850* func_0011A790(Stk_11A850* s);
void func_0011C3F0(Obj_11A850* o);
s32 func_0011C3C8(Obj_11A850* o);

struct Ent_11AB58;
struct World_11AB58 {
    s32 count;              // 0x000
    Ent_11AB58* ents[0x140];    // 0x004
    s32 n504;               // 0x504
    R11B008List* lists[1];  // 0x508: the lists of keyed values func_0011AB58 marks
};

s32 func_0011C3C8(Ent_11AB58* e);
void func_0011C3F0(Ent_11AB58* e);
void func_0011A728(World_11AB58* w, Ent_11AB58* e);
void func_0011A770(World_11AB58* w, Ent_11AB58* e);
void func_0011A7B8(World_11AB58* w, Ent_11AB58* e);
void func_0011A850(World_11AB58* w);

// A count followed by that many values.
struct IntList {
    s32 count;              // 0x00
    s32 items[1];           // 0x04
};

// A record that keeps a stack of values at 0x708.
struct StackAt708 {
    u8 pad[0x708];          // 0x000
    s32 count;              // 0x708
    s32 items[1];           // 0x70C
};

struct Counters_11A6A8 {
    s32 count;              // 0x000
    u8 pad[0x500];          // 0x004
    s32 count2;             // 0x504
};

struct Obj_0011A708 {
    u8 pad[0x504];          // 0x000
    s32 count;              // 0x504
    s32 values[1];          // 0x508
};
struct Obj_0011A728 {
    u8 pad[0x708];          // 0x000
    s32 count;              // 0x708
    s32 values[1];          // 0x70C
};
struct Obj_0011A770 {
    u8 pad[0xF0C];          // 0x000
    s32 count;              // 0xF0C
    s32 values[1];          // 0xF10
};
struct Stack_11A790 {
    u8 pad[0xF0C];          // 0x000
    s32 count;              // 0xF0C
    s32 items[1];           // 0xF10
};
struct Stack_11A7B8 {
    u8 pad[0x1310];         // 0x000
    s32 count;              // 0x1310
    s32 items[1];           // 0x1314
};
struct Stack_11A7D8 {
    u8 pad[0x1310];         // 0x000
    s32 count;              // 0x1310
    s32 items[1];           // 0x1314
};

// What func_001419E8 fills in for func_00118198: 16-byte vectors, the first two read.
struct Hit_118198 {
    Quad16 q[7];            // 0x00
};
s32 func_001419E8(Quad16* z, s32 a, s32 b, s32 c, void** d, Hit_118198* e);

// This file's functions. The built-ins (R119BB0Fn) and their helpers:
R11B008* func_00113730(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00113780(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001137D0(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00113820(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00113888(R11B008* ret, R11B008* args, s32 mode);
R11B008* func_001139E8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00113A18(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00113A48(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00113A78(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00113AA8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00113B60(R11B008* ret, R11B008* a, R11B008* b);
R11B008* func_00113E48(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00113E78(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00113EE0(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00113F48(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00113FB0(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00114018(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00114080(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001140E8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00114150(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001141B8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00114220(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00114288(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00114300(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00114360(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001143C8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00114438(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001144A0(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00114518(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001145C8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00114638(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001146E0(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00114740(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001147B8(R11B008* ret, s32 count, R11B008* args, R11A630* scope, s32 mode);
R11B008* func_00114858(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00114888(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001148B8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00114950(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001149F0(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00114B80(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00114D18(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00114F48(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001151C0(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00115398(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00115440(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00115510(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001156B0(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00115710(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001157E0(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001158B8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001159B8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00115B78(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00115C00(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00115CA0(R11B008* ret, R11B008* arg, s32 index);
R11B008* func_00115D48(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00115D78(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00115DA8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00115DD8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00115E08(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00115E38(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00115E68(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00115E98(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00115EC8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00116520(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00116600(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001166C0(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00116740(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001167C0(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00116978(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001169E8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00116A88(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00116B08(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00116C80(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00116D20(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00116DC8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00116EA8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00116FE8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117080(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117118(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117180(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001171F0(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117260(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001172C8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117360(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117478(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117598(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117610(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117668(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117880(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117910(R11B008* ret, s32 count, R11B008* args, R11A630* scope, s32 kind);
R11B008* func_00117A30(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117A60(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117A90(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117AC0(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117AF0(R11B008* ret, s32 count, void** values);
// How its callers declare it (KEPT: see build/swarm/v2/NOTES.md): they call it as GCC calls a
// function that gives a class back, a `call` with no value (expand_call has no value register when
// the result goes through the hidden address), which schedules the argument moves differently
// from a call of a function returning a pointer. The plain value cannot say that.
void func_00117AF0(R11B008* ret, s32 count, u8* values);
R11B008* func_00117BC8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117C48(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117D00(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117D78(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117E20(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117E78(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117ED0(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00117F28(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001180C0(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
// How its callers declare it; it is defined giving back a RetValue (KEPT, see there).
R11B008* func_00118198(R11B008* ret, s32 id, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001183B8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00118458(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001184F8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00118580(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00118608(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00118720(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001187E8(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_00118850(R11B008* ret, s32 count, R11B008* args, R11A630* scope);
R11B008* func_001188F0(R11B008* ret, s32 count, R11B008* args, R11A630* scope);

// A 128-bit value, copied as one quadword.
typedef u64 Quad_118D10 __attribute__((mode(TI)));

// A 128-bit value, stored as one quadword.
typedef u64 Quad_118D20 __attribute__((mode(TI)));

Quad_118D10* func_00118D10(Quad_118D10* out, void* src);
Quad_118D20* func_00118D20(Quad_118D20* out, Quad_118D20 v);

// The evaluator (func_0011A080) and the handlers it dispatches to by the expression's kind.
R11B008* func_00118D48(R11B008* ret, R11B008Node* expr, R11A630* scope);
R11B008* func_00118DB8(R11B008* ret, R11B008Node* expr, R11A630* scope);
R11B008* func_00118E80(R11B008* ret, R11B008Node* expr, R11A630* scope);
R11B008* func_00118F48(R11B008* ret, R11B008Node* expr, R11A630* scope);
R11B008* func_00119030(R11B008* ret, R11B008Node* expr, R11A630* scope);
R11B008* func_00119128(R11B008* ret, R11B008Node* expr, R11A630* scope);
// How func_0011A080 declares it; it is defined giving back a RetValue (KEPT, see there).
R11B008* func_00119218(R11B008* ret, R11B008Node* expr, R11A630* scope);
R11B008* func_00119310(R11B008* ret, R11B008Node* expr, R11A630* scope);
R11B008* func_001194A8(R11B008* ret, R11B008Node* expr, R11A630* scope);
R11B008* func_001196C8(R11B008* ret, R11B008Node* expr, R11A630* scope);
R11B008* func_00119878(R11B008* ret, R11B008Node* expr, R11A630* scope);
R11B008* func_00119970(R11B008* ret, R11B008Node* expr, R11A630* scope);
R11B008* func_00119A58(R11B008* ret, R11B008Node* list, R11A630* scope);
R11B008* func_00119AF8(R11B008* ret, R11B008Node* expr, R11A630* scope);
R11B008* func_00119BB0(R11B008* ret, R11B008Node* expr, R11A630* scope);
R11B008* func_00119FA0(R11B008* ret, R11B008Node* expr, R11A630* scope);
R11B008* func_0011A080(R11B008* ret, R11B008Node* expr, R11A630* scope);

// The scopes.
void func_0011A328(R11A630* scope, R11A630* parent);
void func_0011A338(R11A630* scope, R11A630* parent);
R11B008* func_0011A358(R11B008* ret, R11A630* scope, s32 key, R11B008* value);
R11B008* func_0011A400(R11B008* ret, R11A630* scope, s32 key, R11B008* value);
s32 func_0011A498(R11A630* scope, s32 key, s32 flag, R11B008* out);
R11B008* func_0011A4D8(R11A630* scope, s32 key, s32 flag);
void func_0011A5B0(R11A630* src, R11A630* dst);
R11A630* func_0011A630(void);
void func_0011A670(void);

// The collector.
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

// Tables of functions this file's code reads: the math functions of func_00115CA0.
f32 func_001EA408(f32 x);
f32 func_00204F68(f32 x);
f32 func_00205210(f32 x);
f32 func_00205400(f32 x);
f32 func_002054F0(f32 x);
f32 func_00205578(f32 x);
f32 func_00205678(f32 x);
f32 func_00206180(f32 x);
MathFn_259938 D_00259938[8] = { func_00206180, func_00205400, func_00205210, func_002054F0, func_00205678, func_00205578, func_00204F68, func_001EA408 };
INCLUDE_DATA(D_00259958);
INCLUDE_DATA(D_00259DE8);
Gc_259F38 D_00259F38;

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

R11B008* func_00113730(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00113780(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001137D0(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00113820(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    func_0011B5F0(&q, args[0].i == args[1].i);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00113888(R11B008* ret, R11B008* e, s32 mode)
{
    f32 xy[2];
    R11B008 obj;
    func_0011B008(&obj);
    f32* out = xy;
    for (s32 i = 1; i >= 0; i--, e++) {
        if (e->tag == 0x15) {
            *out = e->f;
        } else {
            *out = (f32)e->i;
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
    func_0011B018(ret, &obj);
    func_0011B060(&obj, 2);
    return ret;
}

R11B008* func_001139E8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    func_00113888(ret, args, 0);
    return ret;
}

R11B008* func_00113A18(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    func_00113888(ret, args, 1);
    return ret;
}

R11B008* func_00113A48(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    func_00113888(ret, args, 2);
    return ret;
}

R11B008* func_00113A78(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    func_00113888(ret, args, 3);
    return ret;
}

R11B008* func_00113AA8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    s32 r;
    func_0011B008(&q);
    R11B008* k = args;
    R11B008* p = k + 1;
    if (k->tag != p->tag) {
        r = 0;
    } else {
        switch (k->tag) {
        case 20:
        case 27: case 28: case 29: case 30: case 31: case 32: case 33:
            r = (k->i == p->i);
            break;
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
        case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
        case 34:
            r = 1;
            break;
        }
    }
    func_0011B5F0(&q, r);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00113B60(R11B008* ret, R11B008* a, R11B008* b)
{
    R11B008 R;
    R11B008 A;
    R11B008 B;
    R11B008 C;
    R11B008 D;
    R11B008 E;
    R11B008 F;
    s32 r;

    func_0011B008(&R);
    if (a->tag != b->tag) {
        r = 0;
    } else {
        switch (a->tag) {
        case 30: {
            R11B008Node* p = a->node;
            R11B008Node* q = b->node;
            if (p == q) {
                r = 1;
            } else if ((p->next == 0) != (q->next == 0)) {
                r = 0;
            } else {
                func_0011B008(&A);
                func_00113B60(&B, p, q);
                func_0011B0A8(&A, &B);
                func_0011B060(&B, 2);
                if (A.i == 0) {
                    r = 0;
                } else if (p->next == 0) {
                    r = 1;
                } else {
                    func_0011B008(&B);
                    func_0011B008(&C);
                    func_0011B6C0(&B, p->next);
                    func_0011B6C0(&C, q->next);
                    func_00113B60(&D, &B, &C);
                    func_0011B0A8(&A, &D);
                    func_0011B060(&D, 2);
                    r = A.i;
                    func_0011B060(&C, 2);
                    func_0011B060(&B, 2);
                }
                func_0011B060(&A, 2);
            }
            break;
        }
        case 31: {
            R11AFC8* p = a->rec;
            R11AFC8* q = b->rec;
            if (p == q) {
                r = 1;
            } else if (p->w8 != q->w8 || p->wC != q->wC || p->w0 != q->w0) {
                r = 0;
            } else {
                func_0011B008(&A);
                func_0011B008(&B);
                func_0011B008(&E);
                func_0011B6C0(&A, (R11B008Node*)p->w10);
                func_0011B6C0(&B, (R11B008Node*)q->w10);
                func_00113B60(&F, &A, &B);
                func_0011B0A8(&E, &F);
                func_0011B060(&F, 2);
                r = E.i;
                func_0011B060(&E, 2);
                func_0011B060(&B, 2);
                func_0011B060(&A, 2);
            }
            break;
        }
        case 20: case 27: case 28: case 29: case 32:
            r = a->i == b->i;
            break;
        case 33: {
            R119BB0Host* p = (R119BB0Host*)a->p;
            R119BB0Host* q = (R119BB0Host*)b->p;
            if (p == q) {
                r = 1;
            } else {
                r = p->self == q->self && p->fn == q->fn;
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
    func_0011B018(ret, &R);
    func_0011B060(&R, 2);
    return ret;
}

R11B008* func_00113E48(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    func_00113B60(ret, args, args + 1);
    return ret;
}

R11B008* func_00113E78(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 local;
    func_0011B008(&local);
    func_0011B5F0(&local, args[0].tag == 0x1B);
    func_0011B018(ret, &local);
    func_0011B060(&local, 2);
    return ret;
}

R11B008* func_00113EE0(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 local;
    func_0011B008(&local);
    func_0011B5F0(&local, args[0].tag >= 0x14 && args[0].tag < 0x16);
    func_0011B018(ret, &local);
    func_0011B060(&local, 2);
    return ret;
}

R11B008* func_00113F48(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 local;
    func_0011B008(&local);
    func_0011B5F0(&local, args[0].tag == 0x15);
    func_0011B018(ret, &local);
    func_0011B060(&local, 2);
    return ret;
}

R11B008* func_00113FB0(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 local;
    func_0011B008(&local);
    func_0011B5F0(&local, args[0].tag == 0x14);
    func_0011B018(ret, &local);
    func_0011B060(&local, 2);
    return ret;
}

R11B008* func_00114018(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    func_0011B5F0(&q, args->tag == 0x1C);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00114080(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    func_0011B5F0(&q, args->tag == 0x16);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001140E8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    func_0011B5F0(&q, args->tag == 0x17);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00114150(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    func_0011B5F0(&q, args->tag == 0x18);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001141B8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 a;
    func_0011B008(&a);
    func_0011B5F0(&a, args->tag == 0x19);
    func_0011B018(ret, &a);
    func_0011B060(&a, 2);
    return ret;
}

R11B008* func_00114220(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 a;
    func_0011B008(&a);
    func_0011B5F0(&a, args->tag == 0x1A);
    func_0011B018(ret, &a);
    func_0011B060(&a, 2);
    return ret;
}

R11B008* func_00114288(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    s32 v = args->tag;
    func_0011B5F0(&q, v == 0x1E || v == 0);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00114300(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    func_0011B5F0(&q, args->tag == 0);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00114360(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    func_0011B5F0(&q, (args->tag ^ 0x20) == 0);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001143C8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    int flag = 0;
    if (args[0].tag == 0x20) {
        flag = args[0].i == 0;
    }
    func_0011B5F0(&q, flag);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00114438(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    func_0011B5F0(&q, args[0].tag == 0x21);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001144A0(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    s32 v = args->tag;
    int flag = (v == 0x1F || v == 0x1D);
    func_0011B5F0(&q, flag);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00114518(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    f32 out[3];
    func_0011B008(&q);
    for (s32 k = 0; k < 3; k++) {
        if (args[k].tag == 0x14) {
            out[k] = (f32)args[k].i;
        } else {
            out[k] = args[k].f;
        }
    }
    s32 flag = func_001EAC68(out[0], out[1], out[2]);
    func_0011B5F0(&q, flag);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001145C8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    int flag = 0;
    if (args[0].tag == 0x1B) {
        flag = (u32)args[0].i < 1;
    }
    func_0011B5F0(&q, flag);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00114638(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    R11B008Node* node = func_0011AF28();
    func_0011B0A8(node, args);
    s32 kind = args[1].tag;
    args = args + 1;
    if (kind == 0) {
        node->next = 0;
    } else if (kind == 0x1E) {
        node->next = args->node;
    }
    func_0011B6C0(&q, node);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001146E0(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    func_0011B0A8(&q, args->node);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00114740(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    R11B008Node* in = args->node;
    R11B008Node* v = in->next;
    if (v != 0) {
        func_0011B6C0(&q, v);
    } else {
        func_0011B538(&q, 0);
    }
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001147B8(R11B008* ret, s32 count, R11B008* args, R11A630* scope, s32 mode)
{
    R11B008 q;
    R11B008Node* p;
    func_0011B008(&q);
    p = args[0].node;
    if (mode == 0x23) {
        func_0011B0A8(p, &args[1]);
    } else {
        if (args[1].tag == 0x1E) {
            p->next = args[1].node;
        } else {
            p->next = 0;
        }
    }
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00114858(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    func_001147B8(ret, count, args, scope, 0x23);
    return ret;
}

R11B008* func_00114888(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    func_001147B8(ret, count, args, scope, 0x24);
    return ret;
}

R11B008* func_001148B8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    s32 n = 0;
    if (args->tag == 0x1E && args->node) {
        R11B008Node* node = args->node;
        do {
            node = node->next;
            n++;
        } while (node);
    }
    func_0011B570(&q, n);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00114950(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    func_0011B538(&q, 0);
    if (args->tag == 0x1E) {
        R11B008Node* node = args->node;
        R11B008* sub = &args[1];
        s32 i = 0;
        while (node != 0) {
            if (i == sub->i) {
                func_0011B0A8(&q, node);
                break;
            }
            node = node->next;
            i++;
        }
    }
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001149F0(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 A;
    R11B008 B;
    R11B008 C[2];
    R11B008 D;
    s32 n;
    R11B008Node* cur;

    func_0011B008(&A);
    func_0011B008(&B);
    R11B008* q = C;
    n = 1;
    do {
        func_0011B008(q);
        n--;
        q++;
    } while (n != -1);
    func_0011B5F0(&A, 0);
    if (args[1].tag == 0x1E) {
        func_0011B0A8(C, args);
        cur = args[1].node;
        while (cur != 0) {
            func_0011B0A8(&C[1], cur);
            func_00113E48(&D, 2, C, scope);
            func_0011B0A8(&B, &D);
            func_0011B060(&D, 2);
            if (B.tag == 0x1B) {
                if (B.i != 0) {
                    func_0011B5F0(&A, 1);
                    break;
                }
            }
            cur = cur->next;
        }
    }
    func_0011B018(ret, &A);
    q = &D;
    if (C != q) {
        do {
            q--;
            func_0011B060(q, 0);
        } while (C != q);
    }
    func_0011B060(&B, 2);
    func_0011B060(&A, 2);
    return ret;
}

R11B008* func_00114B80(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    func_0011B018(ret, args);
    return ret;
}

INCLUDE_ASM(func_00114BB0);

R11B008* func_00114D18(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    R11B008Node arr[5];
    R11B008Node* it;
    func_0011B008(&q);
    it = arr;
    for (s32 k = 4; k != -1; k--) {
        func_0011B008(it);
        it->tag = -1;
        it++;
    }
    if (args[1].tag == 0) {
        func_0011B0A8(&q, &args[1]);
    } else {
        R11B008Node* list = func_0011AF28();
        R11B008Node* p[2];
        R11B008Node* last;
        list->tag = 0x1E;
        for (u32 i = 0; i < 2; i++) {
            p[i] = func_0011AF28();
        }
        func_0011B6C0(&arr[0], &arr[1]);
        arr[0].next = 0;
        func_0011B6C0(&arr[1], &arr[3]);
        arr[1].next = &arr[2];
        func_0011B6C0(&arr[2], &arr[4]);
        arr[2].next = 0;
        arr[3].tag = 0x11;
        arr[3].next = p[0];
        func_0011B0A8(p[0], args);
        arr[4].tag = 0x11;
        arr[4].next = p[1];
        R11B008* m = &args[1];
        for (R11B008Node* l = m->node; l != 0; l = l->next) {
            R11B008Node* e = func_0011AF28();
            R11B008 t;
            func_0011B0A8(p[1], l);
            func_0011A080(&t, &arr[0], scope);
            func_0011B0A8(e, &t);
            func_0011B060(&t, 2);
            if (list->node == 0) {
                func_0011B6C0(list, e);
            } else {
                last->next = e;
            }
            last = e;
        }
        func_0011B6C0(&q, list->node);
    }
    func_0011B018(ret, &q);
    R11B008Node* end = arr + 5;
    while (arr != end) {
        end--;
        func_0011B060(end, 2);
    }
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00114F48(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    R11B008Node arr[5];
    R11B008Node* it;
    R11B008Node* p[2];
    R11B008 r;
    func_0011B008(&q);
    it = arr;
    for (s32 k = 4; k != -1; k--) {
        func_0011B008(it);
        it->tag = -1;
        it++;
    }
    func_0011B008(&r);
    if (args[1].tag == 0) {
        func_0011B0A8(&q, &args[1]);
    } else {
        R11B008Node* list = 0;
        R11B008Node* last;
        for (u32 i = 0; i < 2; i++) {
            p[i] = func_0011AF28();
        }
        func_0011B6C0(&arr[0], &arr[1]);
        arr[0].next = 0;
        func_0011B6C0(&arr[1], &arr[3]);
        arr[1].next = &arr[2];
        func_0011B6C0(&arr[2], &arr[4]);
        arr[2].next = 0;
        arr[3].tag = 0x11;
        arr[3].next = p[0];
        func_0011B0A8(p[0], args);
        arr[4].tag = 0x11;
        arr[4].next = p[1];
        R11B008* m = &args[1];
        for (R11B008Node* l = m->node; l != 0; l = l->next) {
            R11B008 t;
            func_0011B0A8(p[1], l);
            func_0011A080(&t, &arr[0], scope);
            func_0011B0A8(&r, &t);
            func_0011B060(&t, 2);
            if (r.tag == 0x1B && r.i != 0) {
                R11B008Node* e = func_0011AF28();
                func_0011B0A8(e, l);
                if (list == 0) {
                    list = func_0011AF28();
                    func_0011B6C0(list, e);
                } else {
                    last->next = e;
                }
                last = e;
            }
        }
        if (list != 0) {
            func_0011B6C0(&q, list->node);
        } else {
            q.tag = 0;
        }
    }
    func_0011B018(ret, &q);
    func_0011B060(&r, 2);
    R11B008Node* end = arr + 5;
    while (arr != end) {
        end--;
        func_0011B060(end, 2);
    }
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001151C0(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    R11B008Node arr[5];
    R11B008Node* it;
    func_0011B008(&q);
    it = arr;
    for (s32 k = 4; k != -1; k--) {
        func_0011B008(it);
        it->tag = -1;
        it++;
    }
    if (args[1].tag == 0x1E) {
        R11B008Node* p[2];
        for (u32 i = 0; i < 2; i++) {
            p[i] = func_0011AF28();
        }
        func_0011B6C0(&arr[0], &arr[1]);
        arr[0].next = 0;
        func_0011B6C0(&arr[1], &arr[3]);
        arr[1].next = &arr[2];
        func_0011B6C0(&arr[2], &arr[4]);
        arr[2].next = 0;
        arr[3].tag = 0x11;
        arr[3].next = p[0];
        func_0011B0A8(p[0], args);
        arr[4].tag = 0x11;
        arr[4].next = p[1];
        R11B008* m = &args[1];
        for (R11B008Node* l = m->node; l != 0; l = l->next) {
            R11B008 t;
            func_0011B0A8(p[1], l);
            func_0011A080(&t, &arr[0], scope);
            func_0011B0A8(&q, &t);
            func_0011B060(&t, 2);
        }
    }
    q.tag = 0x22;
    func_0011B018(ret, &q);
    R11B008Node* end = arr + 5;
    while (arr != end) {
        end--;
        func_0011B060(end, 2);
    }
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00115398(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    R11B008 u;
    func_0011B008(&t);
    R11B008Node* n = func_0011AF28();
    func_0011B0A8(n, args);
    func_0011A080(&u, n, scope);
    func_0011B0A8(&t, &u);
    func_0011B060(&u, 2);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

R11B008* func_00115440(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 a;
    R11B008 b;
    s32 n = 2;
    func_0011B008(&a);
    R11B008* in = args;
    f32* base = func_0011C508();
    f32* out = base;
    do {
        func_0011B9A8(&b, in);
        in++;
        func_0011B0A8(&a, &b);
        n--;
        func_0011B060(&b, 2);
        *out = a.f;
        out++;
    } while (n >= 0);
    func_0011B740(&a, base);
    func_0011B018(ret, &a);
    func_0011B060(&a, 2);
    return ret;
}

// A row of the 0x40-byte block of tag 0x17 (func_0011C618), 16-aligned: copied with lq/sq.
struct __attribute__((aligned(16))) Row_115510 {
    f32 f[4];               // 0x00
};

R11B008* func_00115510(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t, u;
    func_0011B008(&t);
    Row_115510* a = (Row_115510*)func_0011C618();
    R11B008Node* n = args->node;
    switch (count) {
    case 3:
    case 4: {
        func_001884C0(a);
        for (s32 i = 0; i < count; i++) {
            a[i] = *(Row_115510*)n->v;
            n = n->next;
        }
        break;
    }
    case 9:
        func_001884C0(a);
    case 16: {
        s32 m = count == 9 ? 3 : 4;
        for (s32 i = 0; i < m; i++) {
            for (s32 j = 0; j < m; j++) {
                func_0011B9A8(&u, n);
                func_0011B0A8(&t, &u);
                func_0011B060(&u, 2);
                a[i].f[j] = t.f;
                n = n->next;
            }
        }
        break;
    }
    }
    func_0011B788(&t, (f32*)a);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

R11B008* func_001156B0(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_001C0C08(args[0].i, args[1].i);
    func_0011B008(&q);
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00115710(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 a;
    R11B008 b;
    f32* base;
    f32* out;
    s32 n = 2;
    func_0011B008(&a);
    R11B008* p = args;
    base = func_0011C748();
    out = base;
    do {
        func_0011B9A8(&b, p);
        p++;
        func_0011B0A8(&a, &b);
        n--;
        func_0011B060(&b, 2);
        *out++ = a.f;
    } while (n >= 0);
    func_0011B7D0(&a, base);
    func_0011B018(ret, &a);
    func_0011B060(&a, 2);
    return ret;
}

R11B008* func_001157E0(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 a;
    R11B008 b;
    f32* out;
    func_0011B008(&a);
    out = func_0011C858();
    func_0011B9A8(&b, args);
    func_0011B0A8(&a, &b);
    func_0011B060(&b, 2);
    out[0] = a.f;
    func_0011B9A8(&b, args + 1);
    func_0011B0A8(&a, &b);
    func_0011B060(&b, 2);
    out[1] = a.f;
    func_0011B818(&a, out);
    func_0011B018(ret, &a);
    func_0011B060(&a, 2);
    return ret;
}

R11B008* func_001158B8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    R11B008 u;
    func_0011B008(&t);
    f32* out = func_0011C968();
    func_0011B9A8(&u, args);
    func_0011B0A8(&t, &u);
    func_0011B060(&u, 2);
    out[0] = t.f;
    func_0011B9A8(&u, args + 1);
    func_0011B0A8(&t, &u);
    func_0011B060(&u, 2);
    out[1] = t.f;
    func_0011B9A8(&u, args + 2);
    func_0011B0A8(&t, &u);
    func_0011B060(&u, 2);
    out[2] = t.f;
    func_0011B860(&t, out);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

// The payloads func_001159B8 reads: a 16-byte vector (tags 0x16, 0x18) and the four rows of the
// 0x40-byte block (tag 0x17), 16-aligned (a row is copied with lq/sq).
struct __attribute__((aligned(16))) Arr_1159B8 {
    f32 v[4];               // 0x00
};
struct Mat_1159B8 {
    Arr_1159B8 row[4];      // 0x00
};

R11B008* func_001159B8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    R11B008Node* ix = args[1].node;
    switch (args[0].tag) {
    case 0x16:
        func_0011B5B0(&q, ((Arr_1159B8*)args[0].v)->v[ix->i]);
        break;
    case 0x17: {
        s32 i = ix->i;
        Arr_1159B8* v;
        if (count == 2) {
            v = (Arr_1159B8*)func_0011C508();
            *v = ((Arr_1159B8*)args[0].v)[i];
            func_0011B740(&q, (f32*)v);
        } else {
            ix = ix->next;
            v = &((Mat_1159B8*)args[0].v)->row[i];
            func_0011B5B0(&q, v->v[ix->i]);
        }
        break;
    }
    case 0x18:
        func_0011B5B0(&q, ((Arr_1159B8*)args[0].v)->v[ix->i]);
        break;
    case 0x19:
        func_0011B5B0(&q, ix->i == 0 ? args[0].v[0] : args[0].v[1]);
        break;
    case 0x1A:
        switch (ix->i) {
        case 0:
            func_0011B5B0(&q, args[0].v[0]);
            break;
        case 1:
            func_0011B5B0(&q, args[0].v[1]);
            break;
        case 2:
            func_0011B5B0(&q, args[0].v[2]);
            break;
        }
        break;
    }
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00115B78(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    if (args->tag == 0x14) {
        func_001F66F8(args->i);
    } else {
        func_001F66F8((s32)args->f);
    }
    q.tag = 0x22;
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00115C00(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 f;
    func_0011B008(&f);
    f32 x;
    f32 y;
    if (args[0].tag == 0x14) {
        x = (f32)args[0].i;
    } else {
        x = args[0].f;
    }
    if (args[1].tag == 0x14) {
        y = (f32)args[1].i;
    } else {
        y = args[1].f;
    }
    f32 r = func_001EAAE0(x, y);
    func_0011B5B0(&f, r);
    func_0011B018(ret, &f);
    func_0011B060(&f, 2);
    return ret;
}

R11B008* func_00115CA0(R11B008* ret, R11B008* arg, s32 index)
{
    R11B008 f;
    func_0011B008(&f);
    f32 v;
    if (arg->tag == 0x15) {
        v = arg->f;
    } else {
        v = (f32)arg->i;
    }
    f32 r = D_00259938[index](v);
    func_0011B5B0(&f, r);
    func_0011B018(ret, &f);
    func_0011B060(&f, 2);
    return ret;
}

R11B008* func_00115D48(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    func_00115CA0(ret, args, 0);
    return ret;
}

R11B008* func_00115D78(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    func_00115CA0(ret, args, 1);
    return ret;
}

R11B008* func_00115DA8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    func_00115CA0(ret, args, 2);
    return ret;
}

R11B008* func_00115DD8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    func_00115CA0(ret, args, 3);
    return ret;
}

R11B008* func_00115E08(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    func_00115CA0(ret, args, 4);
    return ret;
}

R11B008* func_00115E38(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    func_00115CA0(ret, args, 5);
    return ret;
}

R11B008* func_00115E68(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    func_00115CA0(ret, args, 6);
    return ret;
}

R11B008* func_00115E98(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    func_00115CA0(ret, args, 7);
    return ret;
}

R11B008* func_00115EC8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 obj;
    f32 xy[2];
    func_0011B008(&obj);
    f32* out = xy;
    for (s32 i = 1; i >= 0; i--, args++) {
        if (args->tag == 0x15) {
            *out = args->f;
        } else {
            *out = (f32)args->i;
        }
        out++;
    }
    f32 d = func_00205778(xy[0], xy[1]);
    func_0011B5B0(&obj, d);
    func_0011B018(ret, &obj);
    func_0011B060(&obj, 2);
    return ret;
}

ASM_FUNC(func_00115F70);

ASM_FUNC(func_00115FF8);

ASM_FUNC(func_00116080);

ASM_FUNC(func_00116108);

ASM_FUNC(func_001161F8);

ASM_FUNC(func_001162D0);

ASM_FUNC(func_00116400);

ASM_FUNC(func_00116490);

R11B008* func_00116520(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    R11B008 v;
    func_0011B008(&q);
    f32* p = func_0011C508();
    void* s3;
    if (args[3].tag == 0) {
        s3 = 0;
    } else {
        s3 = args[3].node->p;
    }
    void* s1 = args[0].p;
    void* fc = args[1].p;
    func_0011B9A8(&v, &args[2]);
    func_001EDEF0(s1, fc, p, s3, v.f);
    func_0011B060(&v, 2);
    func_0011B740(&q, p);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00116600(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    func_0011B008(&t);
    R11B008Node* a = func_0011AF28();
    R11B008Node* b = func_0011AF28();
    a->next = b;
    f32* c = func_0011C508();
    func_0011B740(b, c);
    f32 d = func_001ED908(args[0].i, args[1].i, c);
    func_0011B5B0(a, d);
    func_0011B6C0(&t, a);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

R11B008* func_001166C0(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    func_0011B008(&t);
    f32* a = func_0011C618();
    func_00188770(args[0].i, a);
    func_0011B788(&t, a);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

R11B008* func_00116740(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    func_0011B008(&t);
    f32* a = func_0011C618();
    func_00189AF0(args[0].i, a);
    func_0011B788(&t, a);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

R11B008* func_001167C0(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    func_0011B008(&t);
    f32* a = func_0011C618();
    func_001891C0(args[0].i, args[1].i, a);
    func_0011B788(&t, a);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

ASM_FUNC(func_00116840);

R11B008* func_00116978(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    func_0011B008(&t);
    f32* c = func_0011C508();
    *(Quad16*)c = *(Quad16*)((u8*)args[0].p + 0x30);
    func_0011B740(&t, c);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

R11B008* func_001169E8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    f32* obj;
    func_0011B008(&q);
    obj = func_0011C618();
    *(Mat4A*)obj = *(Mat4A*)args[0].v;
    func_001884C0(obj);
    func_0011B788(&q, obj);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00116A88(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    func_0011B008(&t);
    f32* c = func_0011C508();
    func_00188FD8(args[0].p, c);
    func_0011B740(&t, c);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

R11B008* func_00116B08(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    Vec4U vec;
    func_0011B008(&t);
    R11B008Node* a = func_0011AF28();
    R11B008Node* b = func_0011AF28();
    f32* c = func_0011C508();
    func_0011B740(b, c);
    a->next = b;
    func_00188D28(args[0].p, &vec.x, c);
    func_0011B5B0(a, vec.x);
    func_0011B6C0(&t, a);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

ASM_FUNC(func_00116BC8);

// What func_00189378 fills in for func_00188B08: 0x30 bytes.
struct Vec_116C80 {
    u8 bytes[0x30];         // 0x00
};

R11B008* func_00116C80(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    Vec_116C80 v;
    func_0011B008(&t);
    f32* a = func_0011C618();
    func_00189378(args[0].p, 0, &v);
    func_00188B08((u8*)args[0].p + 0x30, &v, a);
    func_0011B788(&t, a);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

R11B008* func_00116D20(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    R11B008 v;
    func_0011B008(&t);
    Vec3* k = (Vec3*)args[0].v;
    func_0011B9A8(&v, args + 1);
    f32 x = v.f;
    f32 r = k->x + x * (k->y + x * k->z);
    func_0011B5B0(&t, r);
    func_0011B060(&v, 2);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

R11B008* func_00116DC8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    R11B008 u;
    func_0011B008(&t);
    f32* poly = args[0].v;
    f32* range = args[1].v;
    func_0011B9A8(&u, args + 2);
    f32 k = u.f;
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

R11B008* func_00116EA8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q0;
    R11B008 q1;
    R11B008 q2;
    R11B008 q3;
    R11B008 q4;
    func_0011B008(&q0);
    f32* p = func_0011C748();
    func_0011B9A8(&q1, args);
    f32 x = q1.f;
    func_0011B9A8(&q2, args + 1);
    f32 y = q2.f;
    func_0011B9A8(&q3, args + 2);
    f32 z = q3.f;
    func_0011B9A8(&q4, args + 3);
    f32 w = q4.f;
    func_001EB018(p, x, y, z, w);
    func_0011B060(&q4, 2);
    func_0011B060(&q3, 2);
    func_0011B060(&q2, 2);
    func_0011B060(&q1, 2);
    func_0011B7D0(&q0, p);
    func_0011B018(ret, &q0);
    func_0011B060(&q0, 2);
    return ret;
}

R11B008* func_00116FE8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q0;
    R11B008 q1;
    func_0011B008(&q0);
    void* span = args[0].p;
    func_0011B9A8(&q1, args + 1);
    f32 r = func_001EB0F8(span, q1.f);
    func_0011B5B0(&q0, r);
    func_0011B060(&q1, 2);
    func_0011B018(ret, &q0);
    func_0011B060(&q0, 2);
    return ret;
}

R11B008* func_00117080(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    R11B008 v;
    func_0011B008(&q);
    void* s1 = args[0].p;
    func_0011B9A8(&v, &args[1]);
    s32 flag = func_001EB050(s1, v.f);
    func_0011B5F0(&q, flag);
    func_0011B060(&v, 2);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00117118(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    func_0011B570(&q, (s32)args->f);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00117180(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    func_0011B008(&t);
    s32 n = (s32)(args->f + 1.0f);
    func_0011B570(&t, n);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

R11B008* func_001171F0(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    func_0011B008(&t);
    s32 n = (s32)(args->f + 0.5f);
    func_0011B570(&t, n);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

R11B008* func_00117260(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    func_0011B008(&t);
    s32 n = (s32)args->f;
    func_0011B570(&t, n);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

R11B008* func_001172C8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    if (args->tag == 20) {
        s32 v = args->i; v = v < 0 ? -v : v;
        func_0011B570(&q, v);
    } else {
        f32 v = args->f;
        if (v < 0.0f) {
            v = -v;
        }
        func_0011B5B0(&q, v);
    }
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00117360(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    func_0011B0A8(&q, args);
    if (args[1].tag == 0) {
        args = 0;
    } else {
        args = args[1].node;
    }
    R11B008Node* x = (R11B008Node*)args;
    if (x != 0) {
        do {
            if (q.tag == 0x14) {
                if (x->tag == 0x14) {
                    if (q.i < x->i) {
                        func_0011B0A8(&q, x);
                    }
                } else {
                    if ((f32)q.i < x->f) {
                        func_0011B0A8(&q, x);
                    }
                }
            } else {
                if (x->tag == 0x14) {
                    if (q.f < (f32)x->i) {
                        func_0011B0A8(&q, x);
                    }
                } else {
                    f32 pf = x->f;
                    if (q.f < pf) {
                        func_0011B0A8(&q, x);
                    }
                }
            }
            x = x->next;
        } while (x != 0);
    }
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00117478(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    func_0011B0A8(&q, args);
    if (args[1].tag == 0) {
        args = 0;
    } else {
        args = args[1].node;
    }
    R11B008Node* x = (R11B008Node*)args;
    if (x != 0) {
        do {
            if (q.tag == 0x14) {
                if (x->tag == 0x14) {
                    if (x->i < q.i) {
                        func_0011B0A8(&q, x);
                    }
                } else {
                    if (x->f < (f32)q.i) {
                        func_0011B0A8(&q, x);
                    }
                }
            } else {
                if (x->tag == 0x14) {
                    if ((f32)x->i < q.f) {
                        func_0011B0A8(&q, x);
                    }
                } else {
                    f32 pf = x->f;
                    if (pf < q.f) {
                        func_0011B0A8(&q, x);
                    }
                }
            }
            x = x->next;
        } while (x != 0);
    }
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00117598(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    func_0011B008(&t);
    s32 v = args[0].i % args[1].i;
    func_0011B570(&t, v);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

R11B008* func_00117610(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    func_0011B5B0(&q, D_0026185C);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00117668(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    R11B008 r;
    func_0011B008(&q);
    func_0011B008(&r);
    R11B008Node* a = func_0011AF28();
    R11B008Node* b = func_0011AF28();
    R11B008Node* c = func_0011AF28();
    R11B008Node* d = func_0011AF28();
    R11B008Node* e;
    R11B008Node* f;
    e = func_0011AF28();
    f = func_0011AF28();
    func_0011B6C0(a, b);
    R11B008 t;
    func_0011B9A8(&t, args);
    func_0011B5B0(b, t.f);
    func_0011B060(&t, 2);
    b->next = c;
    func_0011B6C0(c, d);
    func_0011B6C0(d, e);
    func_0011B538(e, 0x11);
    e->next = f;
    func_0011B700(f, args[1].rec);
    s32 idx = D_00259DE8;
    if (idx < count) {
        R11B008Node* n = args[idx].node;
        if (n) {
            R11B008Node* prev = d;
            do {
                d = func_0011AF28();
                e = func_0011AF28();
                func_0011B6C0(d, e);
                func_0011B538(e, 0x11);
                e->next = n;
                prev->next = d;
                R11B008Node* nx = n->next;
                n->next = 0;
                n = nx;
                prev = d;
            } while (n);
        }
    }
    func_0011A498((R11A630*)D_00275710->f2C, D_00275710->f1EF8, 0, &r);
    if (r.tag == 0x1E) {
        a->next = r.node;
    }
    func_0011B6C0(&r, a);
    func_0011A400(&t, (R11A630*)D_00275710->f2C, D_00275710->f1EF8, &r);
    func_0011B060(&t, 2);
    func_0011B018(ret, &q);
    func_0011B060(&r, 2);
    func_0011B060(&q, 2);
    return ret;
}

// The object func_00117880 writes: a float at 0x29C.
struct Obj_117880 {
    u8 pad[0x29C];          // 0x000
    f32 value;              // 0x29C
};

R11B008* func_00117880(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    R11B008 u;
    func_0011B008(&t);
    Obj_117880* obj = (Obj_117880*)args[0].p;
    func_0011B9A8(&u, args + 1);
    f32 f = u.f;
    func_0011B060(&u, 2);
    obj->value = f;
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

R11B008* func_00117910(R11B008* ret, s32 count, R11B008* args, R11A630* scope, s32 kind)
{
    R11B008 q1;
    R11B008 q2;

    func_0011B008(&q1);
    s32 x1 = args[0].i;
    s32 x2 = args[1].i;
    switch (kind) {
    case 0x63:
        func_001C22B8(&q2, x1, x2, &args[2]);
        func_0011B0A8(&q1, &q2);
        func_0011B060(&q2, 2);
        break;
    case 0x64:
        func_001C2320(&q2, x1, x2, &args[2]);
        func_0011B0A8(&q1, &q2);
        func_0011B060(&q2, 2);
        break;
    case 0x65:
        func_001C2238(&q2, x1, x2, &args[2]);
        func_0011B0A8(&q1, &q2);
        func_0011B060(&q2, 2);
        break;
    case 0x66:
        func_001C21A0(&q2, x1, x2);
        func_0011B0A8(&q1, &q2);
        func_0011B060(&q2, 2);
        break;
    }
    func_0011B018(ret, &q1);
    func_0011B060(&q1, 2);
    return ret;
}

R11B008* func_00117A30(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    func_00117910(ret, count, args, scope, 0x63);
    return ret;
}

R11B008* func_00117A60(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    func_00117910(ret, count, args, scope, 0x64);
    return ret;
}

R11B008* func_00117A90(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    func_00117910(ret, count, args, scope, 0x65);
    return ret;
}

R11B008* func_00117AC0(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    func_00117910(ret, count, args, scope, 0x66);
    return ret;
}

R11B008* func_00117AF0(R11B008* ret, s32 count, void** values)
{
    R11B008 q;
    func_0011B008(&q);
    if (count != 0) {
        R11B008Node* prev = 0;
        if (count > 0) {
            void** v = values;
            s32 n = count;
            do {
                R11B008Node* node = func_0011AF28();
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
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00117BC8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    void* r;
    func_0011B008(&q);
    s32 flag = 0x105;
    s32 k = 0x101;
    if (args[1].i != 0) flag = k;
    r = func_0015A418(D_00275710, flag, args[0].i, args[1].i);
    func_0011B8A8(&q, r);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00117C48(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    u8 buf[0x100];
    R11B008 t;
    func_0011B008(&q);
    s32 r = func_0015A198(D_00275710, args[1].i ? 0x101 : 0x105, args[0].i, args[1].p, 0x40, buf);
    func_00117AF0(&t, r, buf);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00117D00(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    void* r;
    func_0011B008(&q);
    r = func_0015A418(D_00275710, 0x104, args[0].i, args[1].i);
    func_0011B8A8(&q, r);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00117D78(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    u8 buf[0x100];
    R11B008 t;
    func_0011B008(&q);
    s32 r = func_0015A198(D_00275710, 0x104, args[0].i, args[1].p, 0x40, buf);
    func_00117AF0(&t, r, buf);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00117E20(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    func_0011B8A8(&q, func_001925F0());
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00117E78(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    func_0011B8A8(&q, D_00275710);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00117ED0(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    func_0011B8A8(&q, D_00261990);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00117F28(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    u8 buf[0x400];
    R11B008 t;
    func_0011B008(&q);
    s32 r = func_0015A4F0(D_00275710, args[1].i ? 0x101 : 0x105, args[0].i, args[1].p, 0x100, buf);
    func_00117AF0(&t, r, buf);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

ASM_FUNC(func_00117FE0);

R11B008* func_001180C0(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    R11B008 t;
    s32 n;
    u8* list;
    f32 scale;
    func_0011B008(&q);
    if (args[1].tag == 0x14) scale = (f32)args[1].i; else scale = args[1].f;
    func_0018D608();
    func_001DC4D0(D_00275710, scale, 0, args[0].i, 0, 0, &n, &list);
    func_00117AF0(&t, n, list);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0018D6F0();
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

// KEPT (build/swarm/v2/NOTES.md): func_00118198 and func_00119218 give their value back as a
// class (the result's place is GCC's hidden first argument), and their early return inside a
// loop keeps its own copy and destruction only so: written with the plain value and explicit
// calls, GCC cross-jumps that return into the last one. Their callers call them through the
// plain declarations above (R11B008* first).
struct RetValue : R11B008 {
    RetValue() { func_0011B008(this); }
    RetValue(const RetValue& o) { func_0011B018(this, &o); }
    ~RetValue() { func_0011B060(this, 2); }
};

RetValue func_00118198(s32 id, s32 count, R11B008* args, R11A630* scope)
{
    RetValue l0;
    Hit_118198 hit;
    void* slot;
    if (args[0].tag == 0) {
        func_0011B0A8(&l0, args);
    } else {
        s32 kind = 0x71;
        R11B008Node* head = 0;
        R11B008Node* tail;
        R11B008Node* it;
        for (it = args[0].node; it != 0; it = it->next) {
            R11B008* pa = &args[1];
            R11B008* pb = &args[2];
            R11B008Node* n1;
            R11B008Node* n2;
            R11B008Node* n3;
            Quad16* v;
            void* e = it->p;
            if (e == 0)
                continue;
            slot = e;
            if (func_001419E8(0, pa->i, pb->i, 1, &slot, &hit) == 0)
                continue;
            if (id == kind) {
                n1 = func_0011AF28();
                n2 = func_0011AF28();
                n3 = func_0011AF28();
                func_0011B8A8(n1, e);
                n1->next = n2;
                v = (Quad16*)func_0011C508();
                *v = hit.q[0];
                func_0011B740(n2, (f32*)v);
                n2->next = n3;
                v = (Quad16*)func_0011C508();
                *v = hit.q[1];
                func_0011B740(n3, (f32*)v);
                n3 = func_0011AF28();
                func_0011B6C0(n3, n1);
                if (head != 0)
                    tail->next = n3;
                else
                    head = n3;
                tail = n3;
            } else {
                n1 = func_0011AF28();
                n2 = func_0011AF28();
                func_0011B8A8(n1, e);
                n1->next = n2;
                v = (Quad16*)func_0011C508();
                *v = hit.q[1];
                func_0011B740(n2, (f32*)v);
                func_0011B6C0(&l0, n1);
                return l0;
            }
        }
        if (head != 0)
            func_0011B6C0(&l0, head);
        else
            l0.tag = 0;
    }
    return l0;
}

R11B008* func_001183B8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_00118198(&t, 0x71, count, args, scope);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00118458(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    func_00118198(&t, 0x72, count, args, scope);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001184F8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    func_0011B008(&t);
    f32* p = func_0011C508();
    func_00128018(args[0].p, args[1].i, args[2].p, p);
    func_0011B740(&t, p);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

R11B008* func_00118580(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    func_0011B008(&t);
    f32* p = func_0011C508();
    func_001280C0(args[0].p, args[1].i, args[2].p, p);
    func_0011B740(&t, p);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

R11B008* func_00118608(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    f32* obj;
    func_0011B008(&q);
    obj = func_0011C618();
    func_00128150(args[0].i, args[1].i, args[2].i, obj);
    func_001884C0(obj);
    func_0011B788(&q, obj);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

ASM_FUNC(func_00118698);

R11B008* func_00118720(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 q;
    s32 n;
    func_0011B008(&q);
    n = 0;
    func_001BFCD8(args[0].i, args[1].i ? &n : 0, args[1].i, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f);
    func_0011B570(&q, n);
    if (n != 0) func_001BF718(&n);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001187E8(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    func_0011B008(&t);
    func_001BF788(args[0].p, 0);
    t.tag = 0x22;
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

R11B008* func_00118850(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    R11B008 u;
    func_0011B008(&t);
    void* p = D_00262C70;
    s32 n = args[0].i;
    func_0011B9A8(&u, args + 1);
    func_0016EC38(p, n, u.f);
    func_0011B060(&u, 2);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

R11B008* func_001188F0(R11B008* ret, s32 count, R11B008* args, R11A630* scope)
{
    R11B008 t;
    R11B008 u;
    func_0011B008(&t);
    void* s1 = args[0].p;
    func_0011B9A8(&u, args + 1);
    func_001566C8(s1, u.f);
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

R11B008* func_00118D48(R11B008* ret, R11B008Node* expr, R11A630* scope)
{
    R11B008 t;
    func_0011B008(&t);
    func_0011A498(scope, expr->i, 1, &t);
    func_0011B018(ret, &t);
    func_0011B060(&t, 2);
    return ret;
}

R11B008* func_00118DB8(R11B008* ret, R11B008Node* expr, R11A630* scope)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    R11B008Node* p = expr->node;
    R11B008Node* m = p->next;
    func_0011A080(&t, m->next, scope);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011A400(&t, scope, m->i, &q);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00118E80(R11B008* ret, R11B008Node* expr, R11A630* scope)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    R11B008Node* p = expr->node;
    R11B008Node* m = p->next;
    func_0011A080(&t, m->next, scope);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011A358(&t, scope, m->i, &q);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

// The message func_00118F48 prints, kept as retail's bytes: retail places it on 16 bytes, 8 past
// where GCC puts the literal (the 8 zero bytes before it are not explained yet).
extern const char D_00249200[];
INCLUDE_RODATA(D_00249200);

R11B008* func_00118F48(R11B008* ret, R11B008Node* expr, R11A630* scope)
{
    R11B008 q;
    R11B008 t;
    func_0011B008(&q);
    R11B008Node* a = expr->node;
    R11B008Node* b = a->next;
    R11B008Node* c = b->next;
    func_0011A080(&t, b, scope);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    if (q.i == 0) {
        R11B008Node* v = c->node;
        R11B008Node* w = v->next;
        func_001E1F10(D_00249200);
        func_00113730(&t, 1, w, scope);
        func_0011B060(&t, 2);
    }
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00119030(R11B008* ret, R11B008Node* expr, R11A630* scope)
{
    R11B008 q;
    R11B008 t;
    R11B008Node* m;
    R11B008Node* n2;
    R11B008Node* n3;
    func_0011B008(&q);
    m = expr->node->next;
    n2 = m->next;
    n3 = n2->next;
    func_0011A080(&t, m, scope);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    if (q.i == 1) {
        func_0011A080(&t, n2, scope);
        func_0011B0A8(&q, &t);
        func_0011B060(&t, 2);
    } else if (n3 != 0) {
        func_0011A080(&t, n3, scope);
        func_0011B0A8(&q, &t);
        func_0011B060(&t, 2);
    } else {
        func_0011B538(&q, 0x22);
    }
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00119128(R11B008* ret, R11B008Node* expr, R11A630* scope)
{
    R11B008 L;
    R11B008 M;
    R11B008Node* n;

    func_0011B008(&L);
    n = expr->node->next;
    if (n != 0) {
        do {
            func_0011A080(&M, n, scope);
            func_0011B0A8(&L, &M);
            func_0011B060(&M, 2);
            if (L.tag != 27 || L.i != 0) {
                func_0011B018(ret, &L);
                func_0011B060(&L, 2);
                goto done;
            }
            n = n->next;
        } while (n != 0);
    }
    func_0011B5F0(&L, 0);
    func_0011B018(ret, &L);
    func_0011B060(&L, 2);
done:
    return ret;
}

RetValue func_00119218(R11B008Node* expr, R11A630* scope)
{
    RetValue L;
    func_0011B5F0(&L, 1);
    for (R11B008Node* n = expr->node->next; n != 0; n = n->next) {
        R11B008 t;
        func_0011A080(&t, n, scope);
        func_0011B0A8(&L, &t);
        func_0011B060(&t, 2);
        if (L.tag == 27 && L.i == 0)
            return L;
    }
    return L;
}

R11B008* func_00119310(R11B008* ret, R11B008Node* expr, R11A630* scope)
{
    R11B008 q, r, t;
    func_0011B008(&q);
    func_0011B008(&r);
    func_0011B538(&q, 0x22);
    R11B008Node* n = expr->node->next;
    while (n) {
        R11B008Node* e = n->node;
        s32 flag;
        if (e->tag == 10) {
            flag = 1;
        } else {
            func_0011A080(&t, e, scope);
            flag = 0;
            func_0011B0A8(&r, &t);
            func_0011B060(&t, 2);
            if (r.tag != 0x1B || r.i != 0)
                flag = 1;
            if (flag && e->next == 0)
                func_0011B0A8(&q, &r);
        }
        if (flag) {
            e = e->next;
            while (e) {
                func_0011A080(&t, e, scope);
                func_0011B0A8(&q, &t);
                func_0011B060(&t, 2);
                e = e->next;
            }
            n = 0;
        } else {
            n = n->next;
        }
    }
    func_0011B018(ret, &q);
    func_0011B060(&r, 2);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_001194A8(R11B008* ret, R11B008Node* expr, R11A630* scope)
{
    R11B008 a;
    R11B008 b[2];
    R11B008 c;
    R11B008 d;
    func_0011B008(&a);
    R11B008* p = b;
    for (s32 k = 1; k != -1; k--) {
        func_0011B008(p);
        p++;
    }
    func_0011B008(&c);
    func_0011B538(&a, 0x22);
    R11B008Node* s0 = expr->node->next;
    func_0011A080(&d, s0, scope);
    func_0011B0A8(&b[0], &d);
    func_0011B060(&d, 2);
    expr = s0->next;
    if (expr) do {
        R11B008Node* e = expr->node;
        s32 found;
        if (e->tag == 10) {
            found = 1;
        } else {
            found = 0;
            R11B008Node* x = e->node;
            if (x) {
                do {
                    func_0011B0A8(&b[1], x);
                    func_00113AA8(&d, 2, b, scope);
                    func_0011B0A8(&c, &d);
                    func_0011B060(&d, 2);
                    if (c.tag == 0x1B && c.i != 0) {
                        found = 1;
                        x = 0;
                    } else {
                        x = x->next;
                    }
                } while (x);
            }
        }
        if (found) {
            e = e->next;
            if (e) {
                do {
                    func_0011A080(&d, e, scope);
                    func_0011B0A8(&a, &d);
                    func_0011B060(&d, 2);
                    e = e->next;
                } while (e);
            }
            expr = 0;
        } else {
            expr = expr->next;
        }
    } while (expr);
    func_0011B018(ret, &a);
    func_0011B060(&c, 2);
    R11B008* p2 = &c;
    if (b != p2) {
        do {
            p2--;
            func_0011B060(p2, 0);
        } while (b != p2);
    }
    func_0011B060(&a, 2);
    return ret;
}

R11B008* func_001196C8(R11B008* ret, R11B008Node* expr, R11A630* scope)
{
    R11B008 q, r, u, t;
    func_0011B008(&q);
    func_0011B008(&r);
    func_0011B008(&u);
    R11B008Node* p = expr->node->next;
    R11A630* d;
    R11B008Node* n;
    if (p->tag == 0x1E) {
        d = func_0011A630();
        R11B008Node* l = p->node;
        if (l) {
            do {
                R11B008Node* e = l->node;
                R11B008* pr = &r;
                func_0011A080(&t, e->next, scope);
                func_0011B0A8(pr, &t);
                func_0011B060(&t, 2);
                func_0011A358(&t, d, e->i, pr);
                func_0011B0A8(&u, &t);
                func_0011B060(&t, 2);
                l = l->next;
            } while (l);
        }
        func_0011A328(d, scope);
    } else {
        d = scope;
    }
    n = p->next;
    while (n) {
        func_0011A080(&t, n, d);
        func_0011B0A8(&q, &t);
        func_0011B060(&t, 2);
        n = n->next;
    }
    func_0011B018(ret, &q);
    func_0011B060(&u, 2);
    func_0011B060(&r, 2);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00119878(R11B008* ret, R11B008Node* expr, R11A630* scope)
{
    R11B008 q, t;
    s32 a, b;
    func_0011B008(&q);
    R11B008Node* first = expr->node->next;
    R11B008Node* second = first->next;
    for (;;) {
        func_0011A080(&t, first, scope);
        func_0011B0A8(&q, &t);
        func_0011B060(&t, 2);
        a = q.tag;
        if (a != 0x1B)
            goto other;
        b = q.i;
        if (b != 0)
            goto other;
        break;
    other:
        func_0011A080(&t, second, scope);
        func_0011B0A8(&q, &t);
        func_0011B060(&t, 2);
    }
    func_0011B538(&q, 0x22);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00119970(R11B008* ret, R11B008Node* expr, R11A630* scope)
{
    R11B008 q;
    func_0011B008(&q);
    R11B008Node* first = expr->node->next;
    R11B008Node* after = first->next;
    R11AFC8* p = func_0011AFC8();
    p->w0 = (s32)scope;
    if (first->tag == 0)
        p->w4 = 0;
    else
        p->w4 = (s32)first->node;
    p->w10 = (s32)after;
    s32 found = 0;
    s32 count = 0;
    R11B008Node* n = (R11B008Node*)p->w4;
    while (n != 0) {
        if (n->tag == 0x13) {
            found = 1;
            n = 0;
        } else {
            n = n->next;
            count++;
        }
    }
    p->w8 = count;
    p->wC = found;
    func_0011B700(&q, p);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00119A58(R11B008* ret, R11B008Node* list, R11A630* scope)
{
    R11B008 q, t;
    func_0011B008(&q);
    R11B008Node* n = list;
    do {
        func_0011A080(&t, n, scope);
        func_0011B0A8(&q, &t);
        func_0011B060(&t, 2);
        n = n->next;
    } while (n);
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00119AF8(R11B008* ret, R11B008Node* expr, R11A630* scope)
{
    R11B008 q, t;
    func_0011B008(&q);
    func_0011B538(&q, 0x22);
    R11B008Node* n = expr->node->next;
    while (n != 0) {
        func_0011A080(&t, n, scope);
        func_0011B0A8(&q, &t);
        func_0011B060(&t, 2);
        n = n->next;
    }
    func_0011B018(ret, &q);
    func_0011B060(&q, 2);
    return ret;
}

R11B008* func_00119BB0(R11B008* ret, R11B008Node* expr, R11A630* scope)
{
    R11B008Node* node;
    R11B008 a;
    R11B008 b;
    R11B008 arr[32];
    R11B008 t;
    R11B008 u;
    s32 total;
    R119BB0* ent;
    R119BB0Host* host;
    R11AFC8* d;
    s32 n;
    s32 last;
    s32 count;
    s32 i;
    R11B008* p;

    func_0011B008(&a);
    func_0011B008(&b);
    p = arr;
    for (s32 k = 31; k != -1; k--) {
        func_0011B008(p);
        p++;
    }
    R11B008Node* first = expr->node;
    func_0011A080(&t, first, scope);
    func_0011B0A8(&a, &t);
    func_0011B060(&t, 2);
    if (a.tag == 0x1D) {
        ent = &D_00259958[a.i];
        n = ent->count;
        last = ent->rest;
    } else if (a.tag == 0x21) {
        host = (R119BB0Host*)a.p;
        last = 0;
        n = host->count;
    } else {
        d = a.rec;
        n = d->w8;
        last = d->wC;
    }
    node = first->next;
    total = n + (last != 0);
    count = n;
    for (i = 0; i < n; i++) {
        R11B008* bp = &b;
        func_0011A080(&t, node, scope);
        func_0011B0A8(bp, &t);
        func_0011B060(&t, 2);
        func_0011B0A8(&arr[i], bp);
        node = node->next;
    }
    if (last) {
        R11B008Node* tail = 0;
        R11B008Node* head = 0;
        R11B008Node* m;
        for (m = node; m; m = m->next) {
            R11B008Node* e = func_0011AF28();
            func_0011A080(&t, m, scope);
            func_0011B0A8(e, &t);
            func_0011B060(&t, 2);
            if (tail) {
                tail->next = e;
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
    switch (a.tag) {
    case 0x1D:
        ent->fn(&t, count, arr, scope);
        func_0011B0A8(&b, &t);
        func_0011B060(&t, 2);
        break;
    case 0x1F: {
        d = a.rec;
        R11A630* s = func_0011A630();
        func_0011A328(s, (R11A630*)d->w0);
        R11B008Node* q = (R11B008Node*)d->w4;
        for (i = 0; i < total; i++) {
            func_0011B008(&t);
            if (0x13 == q->tag) {
                q = q->next;
            }
            func_0011A358(&u, s, q->i, &arr[i]);
            func_0011B0A8(&t, &u);
            func_0011B060(&u, 2);
            q = q->next;
            func_0011B060(&t, 2);
        }
        func_00119A58(&t, (R11B008Node*)d->w10, s);
        func_0011B0A8(&b, &t);
        func_0011B060(&t, 2);
        break;
    }
    case 0x21:
        host->fn(&t, host->self, count, arr);
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

R11B008* func_00119FA0(R11B008* ret, R11B008Node* expr, R11A630* scope)
{
    R11B008 a;
    R11B008 b;
    R11A630* found;
    s32 id;

    func_0011B008(&a);
    id = expr->node->next->i;
    found = func_001C1390(id, (u8*)D_00275710);
    if (found == 0) {
        func_001C13E8(&b, id, (u8*)D_00275710);
        func_0011B0A8(&a, &b);
        func_0011B060(&b, 2);
        found = func_001C1390(id, (u8*)D_00275710);
    }
    func_0011A338(scope, found);
    func_0011B538(&a, 0x22);
    func_0011B018(ret, &a);
    func_0011B060(&a, 2);
    return ret;
}

R11B008* func_0011A080(R11B008* ret, R11B008Node* expr, R11A630* scope)
{
    R11B008 t;
    R11B008 u;
    R11B008* src;
    R11B008Node* p;
    func_0011B008(&t);
    switch (expr->tag) {
    case 0:
    case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27:
    case 29:
    case 32: case 33:
        src = expr;
        goto copy;
    case 28:
        func_00118D48(&u, expr, scope);
        goto tail;
    case 30:
        p = expr->node;
        switch (p->tag) {
        case 1: func_00118DB8(&u, expr, scope); goto tail;
        case 2: func_00118E80(&u, expr, scope); goto tail;
        case 5: func_00118F48(&u, expr, scope); goto tail;
        case 6: func_00119030(&u, expr, scope); goto tail;
        case 7: func_00119128(&u, expr, scope); goto tail;
        case 8: func_00119218(&u, expr, scope); goto tail;
        case 9: func_00119310(&u, expr, scope); goto tail;
        case 11: func_001194A8(&u, expr, scope); goto tail;
        case 12: func_001196C8(&u, expr, scope); goto tail;
        case 13: func_00119878(&u, expr, scope); goto tail;
        case 15: func_00119AF8(&u, expr, scope); goto tail;
        case 14: func_00119970(&u, expr, scope); goto tail;
        case 17:
            src = p->next;
        copy:
            func_0011B0A8(&t, src);
            goto end;
        case 16:
            func_00119FA0(&u, expr, scope);
        tail:
            func_0011B0A8(&t, &u);
            func_0011B060(&u, 2);
            goto end;
        default:
            func_00119BB0(&u, expr, scope);
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

void func_0011A328(R11A630* scope, R11A630* parent)
{
    scope->parents[0] = parent;
    scope->count = 1;
}

void func_0011A338(R11A630* scope, R11A630* parent)
{
    scope->parents[scope->count++] = parent;
}

R11B008* func_0011A358(R11B008* ret, R11A630* scope, s32 key, R11B008* value)
{
    R11B008 a;
    R11B008Key* node;

    func_0011B008(&a);
    node = func_0011C498();
    node->key = key;
    func_0011B0A8(&node->value, value);
    node->next = scope->head;
    scope->head = node;
    func_0011B538(&a, 0x22);
    func_0011B018(ret, &a);
    func_0011B060(&a, 2);
    return ret;
}

R11B008* func_0011A400(R11B008* ret, R11A630* scope, s32 key, R11B008* value)
{
    R11B008 a;
    R11B008* found;

    func_0011B008(&a);
    found = func_0011A4D8(scope, key, 1);
    if (found != 0) {
        func_0011B0A8(found, value);
    }
    func_0011B538(&a, 0x22);
    func_0011B018(ret, &a);
    func_0011B060(&a, 2);
    return ret;
}

s32 func_0011A498(R11A630* scope, s32 key, s32 flag, R11B008* out)
{
    R11B008* r = func_0011A4D8(scope, key, flag);
    if (r != 0) {
        if (out)
            func_0011B0A8(out, r);
        return 1;
    }
    return 0;
}

R11B008* func_0011A4D8(R11A630* scope, s32 key, s32 flag)
{
    R11B008* found = 0;
    R11B008Key* n;
    s32 i;

    scope->busy = 1;
    for (n = scope->head; n != 0; n = n->next) {
        if (n->key == key) {
            found = &n->value;
            goto done;
        }
    }
    if (flag != 0) {
        for (i = 0; i < scope->count; i++) {
            R11A630* c = scope->parents[i];
            if (c->busy == 0) {
                found = func_0011A4D8(c, key, flag);
                if (found != 0)
                    goto done;
            }
        }
    }
done:
    scope->busy = 0;
    return found;
}

void func_0011A5B0(R11A630* src, R11A630* dst)
{
    dst->count = src->count;
    func_0018D800(dst->parents, src->parents, src->count * 4);
    if (src->head != 0) {
        R11B008Key* n = func_0011C498();
        func_0011C418(src->head, n, (s32)dst);
        dst->head = n;
    }
}

R11A630* func_0011A630(void)
{
    R11A630* p = (R11A630*)func_0011C240(D_0025C270);
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
        R11B008Key* n = w->lists[j]->head;
        while (n) {
            func_0011C3F0((Ent_11AB58*)n);
            R11B008* sp = &n->value;
            switch (sp->tag) {
            case 0x1E: {
                Ent_11AB58* e = (Ent_11AB58*)sp->p;
                if (func_0011C3C8(e)) {
                    func_0011C3F0(e);
                    func_0011A770(w, e);
                }
                break;
            }
            case 0x1F: {
                Ent_11AB58* e = (Ent_11AB58*)sp->p;
                if (func_0011C3C8(e)) {
                    func_0011C3F0(e);
                    func_0011A7B8(w, e);
                }
                break;
            }
            case 0x21:
                func_0011C3F0((Ent_11AB58*)sp->p);
                break;
            }
            n = n->next;
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
