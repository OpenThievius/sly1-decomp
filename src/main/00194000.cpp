// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"

void func_001AA8F0(void* self);

struct Ctl_194F00 { u8 pad[0x250]; s32 mode250; u8 pad2[0x20]; s32 f274; };



void func_001AA958(void* self);

struct Ctl_194F38 { u8 pad[0x250]; s32 mode250; u8 pad2[0x20]; s32 f274; s32 f278; };



void func_001936A0(void* self, s32 v);

struct Ctl_195928 { u8 pad[0x260]; s32 f260; };



struct Obj_1963D8 { u8 pad0[0x14]; u8* f14; };

void func_00123ED0(Obj_1963D8* self);
void func_00152470(u8* dst, Obj_1963D8* src);



struct Obj_196900 { void** vtbl; };

void func_00124A48(Obj_196900* self);



struct Rec_26A728 { s32 id; s32 off; s32 flags; };
struct Tbl_26A728 { s32 f0; Rec_26A728 r[1]; };

void func_001BAC30(void* self);
void func_00124DF8(void* self, s32 n, void* table);



struct Obj_196E48 { u8 pad0[0x50]; s32 f50; u8 pad1[0x538 - 0x54]; u64 bits538; };

s32 func_001300E8(void* self, s32 kind);



void func_001B6598(void* obj, s32* out);
void* func_001E9970(s32 arg);

typedef void (*VFn_197788)(void* self);
struct Iface_197788 { VFn_197788* vtbl; };
extern Iface_197788 D_0026D348;
extern Iface_197788 D_0026E4E0;
extern Iface_197788 D_0026E760;

struct Obj_197788 { u8 pad[0x6B8]; void* f6B8; };



void func_001A76A0(void* node, s32 flag);
void func_00152600(void* a, void* b);
void func_00152470(void* a, void* b);

struct Ctx_197A08 { u8 pad[0xC14]; void* fC14; };



struct Glob_194278 { u8 pad[0x19D8]; s32 f19D8; s32 f19DC; };
struct Rec_194278 { s32 f0; void* f4; s32 f8; s32 fC; s32 f10; };

extern void* D_002623C0;
extern void* D_00275710;
extern u8 D_00275B04[];
extern u8 D_00275F80[];

void func_00194D30(void* self, s32 a, s32 b);
void func_001EFFA0(void* obj, void* rec, s32 n);
void* func_0015A838(void* a, s32 b, s32 c, s32 d);
void func_001A4EF0(void* p, s32 mode);
void func_001F4408(void* a, s32 b);




struct Pair_00197A68 { u8 pad[0x94]; f32 f94; f32 f98; };



void func_001922E8(void* a, void* b);



extern u8 D_0026A210[];
void func_001F5C0C(void* p, s32 zero, s32 size);



extern u8 D_00261EF0[];
void func_00151E20(void* self, f32 amount);



extern void* D_0026A904;
void func_001B6568(void* dev, s32* out);
void func_001B6598(void* dev, s32* out);
void func_001B64D8(void* dev, s32 value);
void func_001973D8(u8* self);



extern u8 D_0026E744[];

typedef void (*VFn_197F10)(void* self);
struct Vt_197F10 { VFn_197F10* vtbl; };

struct Obj_197F10 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x644 - 0x18];
    s32 f644;
    u8 pad2[0x688 - 0x648];
    f32 f688;
    u8 pad3[0x6B8 - 0x68C];
    void* f6B8;
};

void func_00192230(void* self, s32 kind, void* rec);
void func_001B6598(void* dev, s32* out);
void func_001DDC38(void* sub, void* self);
void func_001AB890(void* obj, f32 x);
void func_001AB928(void* obj, f32 x, void* fn);
void func_001AB938(void* obj);
void func_001AB958(void* obj);
void func_00197458(s32 unused, s32 flag);



struct Ctl_194E60 {
    u8 pad0[0x250];
    s32 f250;
    u8 pad1[0x0C];
    s32 f260;
    u8 pad2[0x10];
    s32 f274;
    s32 f278;
};

void func_001936A0(Ctl_194E60* self);
void func_00195928(void* self, s32 v);
void func_001AA998(void* self, s32 flag);



typedef void (*VFn_194D30)(void* self, s32 a);
struct Obj_194D30 { VFn_194D30* vtbl; };

struct Self_194D30 {
    u8 pad0[0x250];
    s32 f250;
    u8 pad1[0x25C - 0x254];
    s32 f25C;
    s32 f260;
    u8 pad2[0x268 - 0x264];
    s32 arr268[3];
    s32 f274;
    s32 f278;
};

extern u8 D_00275BC0[];

void func_00193EE8(void* self, s32 a, s32 b);
void func_00195928(void* self, s32 v);
void func_001E9570(void* q);
void func_001E9498(void* a, void* b);



struct Obj_197848;
struct VT_197848 {
    u8 pad0[0x18];
    void (*f18)(Obj_197848*);
    u8 pad1[0x84 - 0x1C];
    void (*f84)(Obj_197848*, void*);
    void (*f88)(Obj_197848*, void*);
    u8 pad2[0x90 - 0x8C];
    void (*f90)(Obj_197848*, void*);
    void (*f94)(Obj_197848*, void*);
};
struct Obj_197848 {
    VT_197848* vt;
    u8 pad[0xC14 - 4];
    void* fC14;
};
struct Node_197848 {
    u8 pad[0x568];
    Node_197848* next;
};
struct Self_197848 {
    u8 pad[0x690];
    s32 count;
    Obj_197848** items;
    f32 time;
    u8 list[4];
};

extern f32 D_00261858[];
extern u8 D_00248D30[];
extern Obj_197848* func_00182FC8(Obj_197848*);
extern s32 func_001527D8(void* list);
extern s32 func_001EAA70(s32 a, s32 b);
extern void func_00152600(void* a, void* b);
extern void func_00152470(void* a, void* b);
extern void func_001C8F20(void* node, s32 kind, s32 flag);
extern void func_001A76A0(void* node, s32 flag);



extern u8 D_00247AB0[];
extern u8 D_00275F80[];

void func_001EFFA0(void* dst, void* args, s32 count);

struct Args_194398 {
    s32 kind;
    void* text;
    s32 x;
    s32 y;
    s32 z;
};



extern u8 D_00248D20[];

struct __attribute__((aligned(16))) Quad_196938 { s32 a, b, c, d; };

struct Sub_196938 { u8 bytes[0x568]; };

struct Obj_196938 {
    u8 pad0[0x61C];
    f32 f61C;
    u8 pad620[0x624 - 0x620];
    f32 f624;
    f32 f628;
    u8 pad62C[0x630 - 0x62C];
    Quad_196938 q630;
    u8 pad640[0x688 - 0x640];
    f32 f688;
};

void func_001921A8(Obj_196938* self);
void func_00152438(Sub_196938* p, s32 value);



struct Self_1961C0 {
    u8 pad0[0x260];
    s32 state;
};
// The register at +0x18 is described with 32-bit bit-fields, the one at +0x40 with 64-bit ones;
// the mixed types are what give retail's copy of the masked value.
struct Reg_1961C0 { u64 lo : 12; u64 mid : 11; u64 rest : 41; };
struct RegA_1961C0 { u32 lo : 12; u32 mid : 11; u32 rest : 9; u32 hi; } __attribute__((aligned(8)));
struct Gs_1961C0 {
    u8 pad0[0x18];
    RegA_1961C0 f18;
    u8 pad20[0x20];
    Reg_1961C0 f40;
};
extern Gs_1961C0 D_00262490;
extern s32 D_00275BF0;
extern f32 D_0026A708;
extern f32 D_0026A70C;
void func_00194D30(Self_1961C0* self, s32 a, s32 b);
s32 func_001FD7A0(f32 x);



struct Menu_195958 {
    u8 pad0[0x260];
    s32 f260;
    s32 f264;
    s32 f268;
    u8 pad1[0x27C - 0x26C];
    s32 f27C;
    s32 f280;
};
struct Row_195958 {
    u8 pad0[0x14];
    s32* items;
};
struct Glob_195958 {
    u8 pad0[0x19EC];
    u32 f19EC;
};
struct Boot_195958 {
    u8 pad0[0x4F44];
    void* f4F44;
    u8 pad1[0x4F4C - 0x4F48];
    void* f4F4C;
};
struct Sub_195958 {
    u8 pad0[0x260];
    s32 f260;
};
struct VT_195958 {
    u8 pad0[0x38];
    void (*f38)(void* self);
};
struct Dev_195958 {
    VT_195958* vt;
};
struct Ent_195958 {
    u8 pad0[0xC];
    f32 fC;
    u8 pad1[0x1A5C - 0x10];
};
struct Pool_195958 {
    u8 pad0[1];
};

extern Row_195958 D_00269D50[];
Boot_195958 D_00264A40 = {};
extern Sub_195958 D_0026F808;
extern u8 D_00275BC0[];
extern u8 D_00247AD0[];
extern Pool_195958 D_00269990;
extern Ent_195958 D_002542D8[];
extern Dev_195958 D_00273EB0;

void func_001961C0(Menu_195958* self);
void func_00194D30(Menu_195958* self, s32 a, s32 b);
void func_00194278(Menu_195958* self, s32 a, s32 b);
void func_001E9498(u8* a, Sub_195958* b);
void func_001F4408(s32 a, s32 b);
void func_001F0428(u8* a, s32 b, s32 c);
void func_0018C178(Boot_195958* a, s32 b);
void func_0018B670(Pool_195958* a, void* fn, Boot_195958* self);
void func_0018C638(Boot_195958* self);
void func_0018C1A8(Boot_195958* self);
void func_0018C250(Boot_195958* self);
void func_0018C770(Boot_195958* self);
void func_0018C568(Boot_195958* self);
void func_00160948(void);
void func_001936A0(Menu_195958* self);
void* func_00193660(void);
void* func_001925F0(void);
s32 func_001300E8(void* node, s32 kind);
void func_001B6598(void* ptr, s32* out);
void func_001D9338(void* p);
void func_001B6628(void* h, s32 arg);
void func_001B64D8(s32 a, s32 b);
s32 func_001602A0(void);
void func_00160578(s32 n);
void func_00194398(void);
void func_001A7F50(Glob_195958* g);
void func_001C0760(s32 flag);
void func_001C0790(s32 flag);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);



struct Self_001969F8 {
    u8 pad0[0x14];
    void* p14;
    u8 pad1[0xD0 - 0x18];
    f32 fD0;
    f32 fD4;
    u8 pad2[0x610 - 0xD8];
    void* p610;
    void* p614;
    f32 f618;
    u8 pad3[0x65C - 0x61C];
    void* p65C;
    void* p660;
    void* p664;
    u8 pad4[0x690 - 0x668];
    s32 n690;
    void* p694;
    u8 pad5[0x69C - 0x698];
    u8 list69C[0x6B4 - 0x69C];
    void* p6B4;
    void* p6B8;
};

struct __attribute__((aligned(16))) Quad_001969F8 { s32 a, b, c, d; };
struct Root_001969F8 { u8 pad[0x11]; u8 b11; };
struct Table_001969F8 { u8 pad[0x10]; };
struct Item_001969F8 { u8 pad[0x24]; void* p24; };

struct Any_001969F8;

struct Tbl_26A738 { s32 f0; Rec_26A728 r[13]; };
extern u8 D_0021A790[];
extern u8 D_00248D30[];

void func_00124A48(Self_001969F8* self);
void func_00124DF8(Self_001969F8* self, s32 n, void* table);
f32 func_00205778(f32 a, f32 b);
void* func_001B6290(Any_001969F8* a, void* b, s32 c, s32 d);
void* func_00121228(Root_001969F8* root, void* value, Table_001969F8* table);
void func_001299E0(Any_001969F8* a, void* b);
s32 func_0015A4F0(Any_001969F8* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void* func_0018D500(s32 size);
void func_00152470(Any_001969F8* list, void* item);
void func_001B6DF8(Any_001969F8* a, void* b);



struct Self_1943E8 {
    u8 pad0[0x250];
    s32 f250;
    f32 f254;
    u8 pad258[0x260 - 0x258];
    s32 f260;
    s32 f264;
    u8 pad268[0x274 - 0x268];
    s32 f274;
    u8 pad278[0x27C - 0x278];
    s32 f27C;
    u8 pad280[0x288 - 0x280];
    s32 f288;
};
struct Glob_1943E8 {
    u8 pad0[0x19D8];
    s32 f19D8;
    s32 f19DC;
};
struct Row_1943E8 {
    void* f0;
    u8 pad4[0xC - 0x4];
    s32 fC;
    s32 f10;
    s32* items;
};
struct Obj_1943E8 {
    void** vt;
};
struct Hud_1943E8 {
    void** vt;
    u8 pad4[0x264 - 0x4];
    s32* f264;
    u8 pad268[0x27C - 0x268];
    s32 f27C;
};
struct Pad_1943E8 {
    u8 pad0[0xAA];
    u16 fAA;
};
struct Pool_1943E8 {
    u8 pad0[0x10];
    s32 f10;
};
struct Ent_1943E8 {
    u8 pad0[0xC];
    f32 fC;
    u8 pad10[0x1A5C - 0x10];
};
struct Item_1943E8 {
    u8 pad0[2];
    u8 f2;
};
struct Reg_1943E8 { u64 lo : 12; u64 mid : 11; u64 rest : 41; };
struct RegA_1943E8 { u32 lo : 12; u32 mid : 11; u32 rest : 9; u32 hi; } __attribute__((aligned(8)));
struct Gs_1943E8 {
    u8 pad0[0x18];
    RegA_1943E8 f18;
    u8 pad20[0x20];
    Reg_1943E8 f40;
};

typedef void (*VFn_1943E8)(void* self);
typedef void (*VFnS_1943E8)(void* self, const char* s);

extern Obj_1943E8 D_0026C6C8;
extern Obj_1943E8 D_0026C948;
extern Obj_1943E8 D_0026CBC8;
extern Obj_1943E8 D_0026CE48;
extern Hud_1943E8 D_00274118;
extern Obj_1943E8 D_0026EC70;
extern f32 D_00261868;
extern Pad_1943E8 D_00262C70;
extern Ent_1943E8* D_0026998C;
struct Words6_264A58 { s32 v[6]; };
extern Words6_264A58 D_00264A58;
extern s32 D_00264A4C;
extern u8 D_0026FF68[];
struct Pair_26A230 { f32 f0; f32 f4; };
extern f32 D_0026A700;
extern f32 D_0026A704;
extern const char D_0024C588[];
extern const char D_0024C5A0[];
extern const char D_0024C5B8[];
extern const char D_0024C5D0[];
extern const char D_0024C600[];
extern const char D_0024C618[];

s32 func_00160B28(Glob_1943E8* g);
s32 func_001BE810(void);
s32 func_0011CE30(void);
s32 func_001BE980(void);
s32 func_0016EED0(Pad_1943E8* p);
s32 func_0016EC98(Pad_1943E8* p);
void func_0016EC20(Pad_1943E8* p, s32 mask);
f32 func_0016F108(Pad_1943E8* p, s32 idx);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_00194D30(Self_1943E8* self, s32 a, s32 b);
void func_00195958(Self_1943E8* self);
void func_001961C0(Self_1943E8* self);
void func_00194398(void);
s32 func_0018B770(Pool_1943E8* p);
void func_0018B670(Pool_1943E8* p, void* fn, void* arg);
void func_0018C250(void* arg);
Item_1943E8* func_001F6880(void* a, const char* name);
s32 func_001AEA08(void);
s32 func_001FD7A0(f32 x);

struct Clamp_1943E8 {
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        if (x < lo) {
            return lo;
        }
        if (hi < x) {
            return hi;
        }
        return x;
    }
};



struct Rd_196410;
struct Nd_196410;
struct VT_196410 {
    u8 pad0[8];
    u32 flags;
    u8 pad0C[0x38 - 0xC];
    void (*m38)(Nd_196410*, Rd_196410*);
    u8 pad3C[0x58 - 0x3C];
    void (*m58)(Nd_196410*);
    u8 pad5C[0x64 - 0x5C];
    void (*m64)(Nd_196410*, void*);
    void (*m68)(Nd_196410*, void*);
};
struct Nd_196410 {
    VT_196410* vt;
    u8 pad04[4];
    s32 f08;
    u8 pad0C[0x2C - 0xC];
    void* f2C;
    void* f30;
    u8 pad34[0x80 - 0x34];
    f32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[0x2C8 - 0x8C];
    u64 b0 : 28;
    u64 mode : 2;
    u64 b30 : 34;
};
struct List_196410 { Nd_196410* head; s32 pad4; s32 link; };
struct Cell_196410 { Nd_196410* node; s32 link; };
struct Self_196410 {
    VT_196410* vt;
    u8 pad04[4];
    s32 f08;
    u8 pad0C[0x14 - 0xC];
    void* f14;
    void* f18;
    u8 pad1C[0x34 - 0x1C];
    List_196410 f34;
    u8 pad40[0xD0 - 0x40];
    u8 fD0[0x30];
    u8 f100[0x2D0 - 0x100];
    u8 f2D0[1];
};
struct Frame_196410 {
    List_196410* list;
    u8* cursor;
    s32 link;
    Frame_196410* prev;
};

void func_00152438(u8* a, s32 v);
void func_00137EB0(Rd_196410* r, u8* out);
void func_00137E70(Rd_196410* r, u8* out);
s32 func_00137B90(Rd_196410* r);
s32 func_00137D10(Rd_196410* r);
Nd_196410* func_001DC208(void* host, s32 a);
Nd_196410* func_0011E580(s32 slot, void* host, s32 z, s32 key, s32 flag);
void func_001DC150(void* host, Nd_196410* n, s32 v);
Cell_196410* func_0018D5C0(s32 n);
void func_00152470(u8* list, Cell_196410* c);
Nd_196410* func_0015A418(void* host, s32 kind, s32 id, Nd_196410* c);
void* func_001C1390(s32 id, void* host);
void func_0011A338(void* a, void* b);
s32 func_00137C40(Rd_196410* r);
s32 func_00137CC0(Rd_196410* r);
f32 func_00137DF8(Rd_196410* r);
void func_0011EC40(Nd_196410* n, Rd_196410* r);
void func_0011ECB8(void* host, Self_196410* self, Rd_196410* r);
s32 func_00152720(List_196410* list);

// The id that names no object.
struct Id_196410 {
    static s32 None() { return -1; }
};



struct Obj_1940E8 {
    void** vtbl;
    u8 pad_004[0x25C - 4];
    s32 f25C;
    s32 f260;
};

typedef void (*VFn_1940E8)(Obj_1940E8* self);

enum Bits_1940E8 {
    BITS_1940E8_ZERO = 0
};

struct Pool_1940E8 {
    u8 pad[1];
};

extern u8 D_00275BC0[];
extern u8* D_0027051C;

void func_001BED48(void);
void func_001BED70(void);
void func_001E96F8(Obj_1940E8* self, s32 mode);
void func_00193EE8(Obj_1940E8* self, s32 a, s32 b);
void func_0016E0F0(Bits_1940E8 bits);
void func_0016E118(Bits_1940E8 n);
void func_0016EC88(Pool_1940E8* p);



// func_0015DB28 builds a text buffer and returns it (a constructor's `this`).

struct Rgba_194F80 { u8 r, g, b, a; };
struct Out_194F80 { u8 b[0x20]; };
struct Col_194F80 { s32 v[4]; };
struct Buf_194F80 { u8 b[0xB0]; };
struct Font_194F80 { u8 pad0[4]; s32 f4; s32 f8; u8 pad1[0x44 - 0xC]; f32 f44; f32 f48; };
struct Owner_194F80;
struct VEnt_194F80 { s16 delta; s16 idx; void (*fn)(void* self, Owner_194F80* o, Out_194F80* out, void* d); };
struct Hook_194F80 { u8 pad[0x4C]; VEnt_194F80* vt; };
struct Owner_194F80 { Hook_194F80* f0; u8 pad[0x14]; Rgba_194F80 f18; };
struct Menu_194F80 { void* title; f32 titleScale; f32 itemScale; s32 vertical; s32 count; s32* items; };
struct Self_194F80 {
    u8 pad0[4];
    Font_194F80* f4;
    u8 pad1[0x210 - 8];
    Owner_194F80* f210;
    u8 pad2[0x224 - 0x214];
    f32 f224;
    f32 f228;
    u8 pad3[0x234 - 0x22C];
    f32 f234;
    f32 f238;
    f32 f23C;
    u8 pad4[0x250 - 0x240];
    s32 f250;
    u8 pad5[0x260 - 0x254];
    s32 f260;
    s32 f264;
    u8 pad6[0x284 - 0x268];
    f32 f284;
};

extern f32 D_00261858[];
extern s32 D_00275BEC;
extern f32 D_00262CEC;
extern u8 D_00260ED0[];
extern u8 D_00262280[];

f32 func_00205400(f32 x);
f32 func_001EA4B8(void* p, s32 zero, f32 a, f32 b, f32 c);
void func_00137228(Out_194F80* out, f32 x, f32 y);
void func_00137238(Out_194F80* out, f32 x, f32 y);
void func_00137248(Out_194F80* out, Col_194F80* value);
void func_00137260(Out_194F80* out, s32 flag);
void func_00137268(Out_194F80* out, s32 flag);
void func_0015C8B8(Font_194F80* font, f32 a, f32 b);
Buf_194F80* func_0015DB28(Buf_194F80* out, void* str, Font_194F80* font);
void func_0015E318(Buf_194F80* buf, Out_194F80* out, s32 zero, void* data);
f32 func_0015E1B0(Buf_194F80* buf, f32 w);
void func_0015C900(Font_194F80* font);
f32 func_0015DFF8(Buf_194F80* buf);
void* func_00193598(s32 id);
void func_001AE3B8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, Rgba_194F80* c, s32 k);

struct Setup_194F80 { static void Do(Out_194F80* out, f32 x, f32 y, f32 w, f32 h, s32 color, s32 flag)
{
    func_00137228(out, x, y);
    func_00137238(out, w, h);
    Col_194F80 tmp;
    tmp.v[0] = color;
    func_00137248(out, &tmp);
    func_00137260(out, flag);
    func_00137268(out, 0);
} };

struct CallHook_194F80 { static void Do(Owner_194F80* o, Out_194F80* out, void* d)
{
    Hook_194F80* hk = o->f0;
    if (hk != 0) {
        hk->vt[9].fn((u8*)hk + hk->vt[9].delta, o, out, d);
    }
} };

struct LerpChan_194F80 { static s32 Do(s32 a, s32 b, f32 t)
{
    if (a == b) {
        return b;
    }
    if (a < b) {
        return a + (s32)(t * ((f32)b + 0.999f - (f32)a));
    }
    return b + (s32)((1.0f - t) * ((f32)a + 0.999f - (f32)b));
} };

struct Lerp_194F80 { static void Do(Rgba_194F80* out, Rgba_194F80 a, Rgba_194F80 b, f32 t)
{
    Rgba_194F80 r;
    r.r = LerpChan_194F80::Do(a.r, b.r, t);
    r.g = LerpChan_194F80::Do(a.g, b.g, t);
    r.b = LerpChan_194F80::Do(a.b, b.b, t);
    r.a = LerpChan_194F80::Do(a.a, b.a, t);
    *out = r;
} };




struct Pair_196810 { u32 first, second; };
struct Trip_196810 { u32 first, second, third; };
struct Cell_196810 { void* node; s32 link; };
struct Elem_196810 { s32 f0; u8 pad4[4]; Elem_196810* next; };
struct Item_196810 { u8 pad0[0x1C]; Item_196810* next; u8 pad20[0x10]; void* f30; };
struct Head_196810 { u8 pad0[0x34]; Item_196810* f34; };
struct Self_196810 {
    u8 pad0[8];
    s32 f08;
    u8 pad0C[0xC];
    Head_196810* f18;
    u8 pad1C[0x2D0 - 0x1C];
    Trip_196810 f2D0;
    Pair_196810 f2DC;
};

void func_00127048(Self_196810* self, Self_196810* src);
void func_00152440(Trip_196810* p);
void func_00152470(Trip_196810* list, Cell_196810* c);



// _GLOBAL_$I$ of the file, after the 16 bytes the linker left of two layout setters.

