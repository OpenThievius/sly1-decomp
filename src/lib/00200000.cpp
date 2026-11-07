// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

typedef void (*Fn_Table)();
// Two type-name strings, a class's mangled name and "bad_alloc" (runtime support data).
struct Strs_24F210 { char a[16]; char b[16]; };
extern const Fn_Table D_0024F230[6];

struct Node_2000F0 {
    s32 field0;
    void *vtbl;
    s32 field2;
    s32 field3;
};

extern const Fn_Table D_0024F248[6];

struct Node_200118 {
    s32 field0;
    void *vtbl;
    s32 field2;
};

extern const Fn_Table D_0024F260[6];

struct Node_2003F8 {
    s32 field0;
    void *vtbl;
    s32 field2;
    s32 field3;
};

extern u8 D_0024F278[];

extern u8 D_0024F290[];

extern const Fn_Table D_0024F2A8[4];

// An entry of a table of functions defined at the end of this file.
extern const Fn_Table D_0024F428[];

struct Node_200C90 {
    s32 field0;
    void *vtbl;
    s32 field2;
};

extern const Fn_Table D_0024F3F8[];

struct Node_200CD8 {
    s32 field0;
    void *vtbl;
};

extern const Fn_Table D_0024F3E8[];

struct Node_200CF8 {
    s32 field0;
    void *vtbl;
};

extern const Fn_Table D_0024F3D8[];

struct Node_200D18 {
    s32 field0;
    void *vtbl;
};

extern const Fn_Table D_0024F3C8[];

struct Node_200D38 {
    s32 field0;
    void *vtbl;
};

extern const Fn_Table D_0024F418[];

struct Node_200CB0 {
    s32 field0;
    void *vtbl;
    s32 field2;
    s32 field3;
};

// NEAR: retail saves $s0 and $ra with 8-byte sd (ld to restore); 2.95.3 saves
// them with 16-byte sq/lq, and no source form tried changed that. Otherwise
// the body matches.

struct Obj_200158;
s32 func_002000B0(Obj_200158* self, s32 a1, s32 a2);

// NEAR: identical except the register saves: retail saves s0/ra with sd (8 bytes), ours with sq (16 bytes); only the Sony 2.9-ee build saves in 8 bytes (docs/TOOLCHAIN.md), so the SN build cannot match this function.

extern u8 D_0062C5C8[];
extern const char D_0024F2B8[24];
extern u8 D_0062C5D8[];

struct Node_200418 { s32 field0; };

void func_00200118(struct Node_200418* self, void* a1, void* a2);

void* func_00200530(void);
// NEAR: US: retail saves s0 and ra with sd (8 bytes, the Sony 2.9-ee compiler), the default compiler saves sq; the body matches.

struct Self_002004A8;

void* func_00200530(struct Self_002004A8* a0);
void func_00200118(struct Self_002004A8* self, void* a1, void* a2);

extern u8 D_0062C5E8[];
extern u8 D_0062C5D8[];
extern const char D_0024F2D0[24];

// NEAR: every instruction matches except the two register saves: retail
// saves $s0 and $ra with sd (8 bytes), ours with sq (16 bytes): the Sony SDK
// compiler's saves (docs/TOOLCHAIN.md), not the default compiler's. The frame,
// the calls and the return are the same. An s64 local made it 88 bytes.

extern u8 D_0062C5D8[];
extern const char D_0024F2E8[24];
extern u8 D_0027B320[];

struct Ctx_200530 { s32 field0; };
void func_00200118(struct Ctx_200530 *self, void *a1, void *a2);

void* func_00200710(void);
// NEAR: the body is EXACT as far as the listing goes; retail saves $s0 and $ra with sd (8 bytes), ours with sq: only the prologue and epilogue differ.

extern u8 D_0062C5F8[];
extern const char D_0024F300[16];
extern u8 D_0027B318[];

struct Obj_002005E8 {
    void *vtbl;
};

void* func_001FF008(void);
void func_00200118(struct Obj_002005E8 *self, void *a1, void *a2);

// NEAR: retail saves $ra and $s0 with sd (8 bytes); this compiler saves them with sq (16 bytes). The body is otherwise identical.

extern u8 D_0062C608[];
extern const char D_0024F310[16];
extern u8 D_0027B318[];

struct Node_200680 {
    void *field0;
};

void* func_001FF008(void);
void func_00200118(struct Node_200680 *self, void *a1, void *a2);

// NEAR: retail saves $ra with sd, default compiler with sq; body identical
struct Ctx_002006D0;
s32 func_002000B0(Ctx_002006D0* a, Ctx_002006D0* b);

// NEAR: body matches; retail saves $s0 and $ra with sd/ld (8 bytes), this compiler saves sq/lq: a lib-code compiler difference

extern u8 D_0027B320[];
extern const Strs_24F210 D_0024F320;

struct Node_200710 {
    void *vtbl;
};

void func_00200138(struct Node_200710 *self, void *value);

// NEAR: retail saves $ra with sd (Sony 2.9-ee-991111 library code, 0x1F59C4 on); the default compiler saves it with sq. Nothing else differs.

struct Key_200750;
s32 func_001F6738(Key_200750* p, s32 v);

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
void* func_00201460(void);

// NEAR: ra and s0 saved with sq, retail sd (the body matches).

extern u8 D_0062C618[];
extern const char D_0024F438[24];
extern u8 D_0027B320[];

struct Node_2011C0 {
    s32 field0;
    void *vtbl;
};

void func_00200118(struct Node_2011C0 *self, s32 a1, s32 a2);

// NEAR: only the s0 and ra saves differ: retail saves ra and s0 with sd (8 bytes), the SN builds with sq; the 8-byte save is the Sony 2.9-ee-991111 form (docs/TOOLCHAIN.md), not used here.

extern u8 D_0062C628[];
extern const char D_0024F450[24];
extern u8 D_0027B320[];

struct Node_201230 {
    s32 field0;
    void *vtbl;
};

void func_00200118(struct Node_201230 *self, void *a1, void *a2);

// NEAR: body matches; retail saves $s0 and $ra with sd/ld (8 bytes), this compiler saves sq/lq: a lib-code compiler difference

extern u8 D_0062C638[];
extern const char D_0024F468[24];
extern u8 D_0027B320[];

struct Node_2012A0 {
    void *vtbl;
    s32 field1;
    s32 field2;
};

void *func_00200710(void);
void func_00200118(struct Node_2012A0 *self, void *a1, void *a2);

// NEAR: only the $ra and $s0 saves differ: retail sd/ld, ours sq/lq

extern u8 D_0062C648[];
extern const char D_0024F480[24];
extern u8 D_0027B320[];

struct Node_201310 {
    void *field0;
};

void func_00200118(struct Node_201310 *self, void *a1, void *a2);

// NEAR: retail saves $s0 and $ra with 8-byte sd (ld to restore); 2.95.3 saves
// them with 16-byte sq/lq, and no source form tried changed that. Otherwise
// the body matches.

extern u8 D_0062C658[];
extern const char D_0024F498[24];
extern u8 D_0027B320[];

struct Node_201380 {
    s32 field0;
    void *vtbl;
    s32 field2;
};

void func_00200118(struct Node_201380 *self, void *a1, void *a2);

// NEAR: identical except the register saves: retail saves s0/ra with sd (8 bytes), ours with sq (16 bytes); only the Sony 2.9-ee build saves in 8 bytes (docs/TOOLCHAIN.md), so the SN build cannot match this function.

extern u8 D_0062C668[];
extern const char D_0024F4B0[24];
extern u8 D_0027B320[];

struct Node_2013F0 { s32 field0; };

void func_00200118(struct Node_2013F0* self, void* a1, void* a2);

// NEAR: US: retail saves s0 and ra with sd (8 bytes, the Sony 2.9-ee compiler), the default compiler saves sq; the body matches.

struct Self_00201460;

void* func_00200710(struct Self_00201460* a0);
void func_00200118(struct Self_00201460* self, void* a1, void* a2);

extern u8 D_0062C678[];
extern const char D_0024F4C8[24];
extern u8 D_0027B320[];


// NEAR: exact only with the Sony 2.9-ee-991111 compiler (retail saves ra with sd/ld); the default SN GCC 2.95.3 saves it with sq/lq and differs.

struct Ctx_202058;

void* func_001F6C60(Ctx_202058* self);
void func_001F6C70(Ctx_202058* self);



extern u8 D_0024F0D8[];

s32 func_0018D778(void* self);

struct Ctx_002004F8;
s32 func_00200080(Ctx_002004F8* ctx);

extern s32 func_00200080(void);
struct Obj_002005A0 { u8* f0; };

s32 func_0018D778(Obj_002005A0* self);
extern u8 D_0024F0D8[];

extern u8 D_0024F0D8[];

s32 func_0018D778(void* self);

s32 func_00200080(void);

struct Ctx_002004F8;
s32 func_00200080(Ctx_002004F8* ctx);

extern s32 func_00200080(void);
s32 func_00200080(void);

s32 func_00200080(void);

struct Cfg_00202120;
s32 func_001F6C60(Cfg_00202120* c);



// BYTES 183/188 (97.3%), checked 2026-11-01
// NEAR: the function body matches in behavior, but the candidate is 192 bytes versus retail 188 and uses sq/lq instead of sd/ld.
// NEAR: all body instructions match; SN emits sq/lq saves where retail uses sd/ld (and reports 192 vs 188 bytes).
void* func_00201BA8(void*);


struct Obj_200080 { void* f0; void* f4; };
u8* func_0018D778(struct Obj_200080* self);
struct Key_2000B0;
s32 func_001F6738(Key_2000B0* p, s32 v);

extern s32 func_002000B0(void*, void*);
struct VTable {
    u8 pad[0x10];
    s16 offset;
    u8 pad2[2];
    s32 (*method)(void*, void*, void*, void*, void*, void*);
};
struct Object { u8 pad[4]; VTable* vtable; };
struct Handler { u8 pad[8]; Object* object; };
struct Callee_200468 { u8 pad[4]; s32 f4; };

s32 func_00200080(Callee_200468* self, s32 flag);

// func_00200D58: the callee pointers keep their order; the offset is read as an s32 local before the two calls.
typedef void* (*Factory_200D58)(void);
typedef s32 (*Value_200D58)(void);
typedef void (*Apply_200D58)(void*, s32, s32, s32, s32, s32);

struct Callee_201280 { u8 pad[4]; s32 f4; };

s32 func_00200080(Callee_201280* self, s32 flag);

struct Obj_002014B0 { void* f0; void* f4; };
s32 func_00200080(struct Obj_002014B0* self, s32 flag);


struct Elem_201FF8;

struct Obj_201FF8 {
    u8 pad0[0x50];
};

void func_00201BB8(Elem_201FF8* p);
s32 func_00201C78(Elem_201FF8* p);



// EXACT: n++ inside the compare (old value tested, increment in the delay slot)

extern const char D_0024F4E0[48];

struct Fmt_201C78 { s32 field0; };
s32 func_001E1F10(struct Fmt_201C78 *fmt, ...);


u64* func_00201BA8();

typedef int V128_201D60 __attribute__((mode(TI)));

// A 16-byte record of two 64-bit words of bitfields.
struct Tag_201D60 {
    u64 count : 15;
    u64 last : 1;
    u64 pad0 : 44;
    u64 words : 4;
    u64 kind : 4;
    u64 pad1 : 60;
};

struct Low9_201D60 {
    u64 value : 9;
    u64 pad : 55;
};

struct Obj_201D60 {
    u8 pad0[0x38];
    Low9_201D60 f38;
    u8 pad40[0x50 - 0x40];
    Tag_201D60 tag50;
    Low9_201D60 f60;
    u8 pad68[0x140 - 0x68];
    Tag_201D60 tag140;
};

void func_00202140(void* p, s32 a, s32 b, s32 c, s32 d, s32 e);
void func_00202478(void* p, s32 a, s32 b, s32 c, s32 d, s32 e);
void func_00202660(void* p, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i, s32 j);



struct Rec_201A18 { s16 x; s16 y; s16 flag; s16 ext; s32 f8; s32 fC; };

s32 func_001F6C70(u64 value);
void func_001F6D40(s32 n);
void func_001F6960(s32 n, s32 ptr);
void func_001F6910(s32 a, s32 b, s32 c);




// The runtime's type names of the built-in types: each function builds its object in place
// the first time it is asked for, and returns it.
extern const void* const D_0024F408[];

struct TypeName_Raw_200E08 {
    const char* name;
    const void* vtbl;
};

struct TypeName_200E08 : TypeName_Raw_200E08 {
    TypeName_200E08(const char* n)
    {
        vtbl = D_0024F408;
        name = n;
    }
    static void* operator new(unsigned int, void* p) throw() { return p; }
};

extern TypeName_Raw_200E08 D_00278E00;
extern const char D_0024F340[];

extern TypeName_Raw_200E08 D_00278E08;
extern const char D_0024F348[];

extern TypeName_Raw_200E08 D_00278E10;
extern const char D_0024F350[];

extern TypeName_Raw_200E08 D_00278E18;
extern const char D_0024F358[];

extern TypeName_Raw_200E08 D_00278E20;
extern const char D_0024F360[];

extern TypeName_Raw_200E08 D_00278E28;
extern const char D_0024F368[];

extern TypeName_Raw_200E08 D_00278E30;
extern const char D_0024F370[];

extern TypeName_Raw_200E08 D_00278E38;
extern const char D_0024F378[];

extern TypeName_Raw_200E08 D_00278E40;
extern const char D_0024F380[];

extern TypeName_Raw_200E08 D_00278E48;
extern const char D_0024F388[];

extern TypeName_Raw_200E08 D_00278E50;
extern const char D_0024F390[];

extern TypeName_Raw_200E08 D_00278E58;
extern const char D_0024F398[];

extern TypeName_Raw_200E08 D_00278E60;
extern const char D_0024F3A0[];

extern TypeName_Raw_200E08 D_00278E68;
extern const char D_0024F3A8[];

extern TypeName_Raw_200E08 D_00278E70;
extern const char D_0024F3B0[];

extern TypeName_Raw_200E08 D_00278E78;
extern const char D_0024F3B8[];

extern TypeName_Raw_200E08 D_00278E80;
extern const char D_0024F3C0[];

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


// The EE DMA channel's register block (CHCR at 0x00, QWC at 0x20; bit 8 of CHCR is STR),
// passed in by pointer: volatile as a hardware register, which retail re-reads at every use.
struct DmaChan_202B68 {
    volatile s32 chcr;
    u8 pad4[0x1C];
    s32 qwc;
};

extern "C" int func_001E1F10(const char* fmt, ...);


// The EE DMA channel's register block (CHCR at 0x00; bit 8 of CHCR is STR), passed in by
// pointer: volatile as a hardware register, which retail re-reads at every use.
struct DmaChan_202C38 {
    volatile s32 chcr;
};

extern "C" int func_001E1F10(const char* fmt, ...);



// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.

struct Obj_202098 { u8 pad0[0x20]; u64 out; u8 pad1[0x8]; u64 in; };



struct Obj_200220;
struct VT_200220 { s16 pad[8]; s16 delta; s16 pad2; s32 (*fn)(Obj_200220* self, s32 a, s32 b, s32 c, s32 d, s32 e); };
struct Obj_200220 { s32 x0; VT_200220* vt; };
struct Ent_200220 { Obj_200220* obj; u32 w; };
struct Tab_200220 { s32 p0; s32 p4; Ent_200220* ents; u32 count; };

s32 func_002000B0(Tab_200220* a, Obj_200220* b);



struct Obj_200778;
typedef void* (*Fn_200778)(Obj_200778* self, Obj_200778* want, s32 boff, void* obj, void* sub, void* subobj);
struct Slot_200778
{
    s16 off;
    s16 idx;
    void* fn;
};
struct Obj_200778
{
    const char* name;
    Slot_200778* vtbl;
    Obj_200778* type;
    s32 attr;
};

s32 func_002000B0(Obj_200778* a, Obj_200778* b);
void* func_00200D58(void* a0, void* a1, s32 a2, void* a3, void* a4, Obj_200778* a5);
void* func_00200530(void);
void* func_00200710(void);
void* func_00201460(void);
void* func_002013F0(void);
void* func_00201310(void);

template <void* (*TF)(void)> struct Cast_200778
{
    static Obj_200778* To(Obj_200778* p)
    {
        if (p == 0)
            return 0;
        return (Obj_200778*)func_00200D58(p->vtbl->fn, (void*)TF, 1, (u8*)p + p->vtbl->off, (void*)(void* (*)(void))func_00200710, p);
    }
};

// Data of this file: type-name strings, class tables and the runtime's zero-initialised objects.
