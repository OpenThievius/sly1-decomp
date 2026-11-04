// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"

struct State_193288 { void* ptr; s32 scaled; s32 size; s32 value; s32 repeat; };
void func_00168AF8(State_193288*);
void func_00193318(State_193288*);

s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);

void func_001AA268(void* self);
s32 func_0015C188(s32 k);
void* func_0015C1C0(s32 k);

struct Obj_193E58 {
    u8 pad0[0x210];
    void** f210;
    u8 pad1[0x4C];
    s32 f260;
    u8 pad2[0x4];
    s32 arr268[3];
    u8 pad3[0x8];
    s32 f27C;
    u8 pad4[0x4];
    f32 f284;
};

struct S_193270 { s32 a,b,c,d,e; };

struct S_193300 { s32 a,b,c,d,e; };

struct __attribute__((packed)) Word_193210 { u32 value; };
struct Obj_193210 {
    s32 f00; s32 f04; s32 f08; s32 f0C; s32 f10;
    Word_193210 f14; Word_193210 f18; Word_193210 f1C; Word_193210 f20;
};

struct Obj_193EE8 {
    void** vt;
};
struct Self_193EE8 {
    u8 pad[0x288];
    s32 f288;
};
struct Dev_193EE8 {
    u8 pad[0x18];
    union {
        struct {
            u32 x : 12;
        } a;
        s64 q18;
    };
};

extern f32 D_0026A700;
extern f32 D_0026A704;
extern f32 D_0026A708;
extern f32 D_0026A70C;

void func_001BE998(void);
void func_001AA8B8(Obj_193EE8* self, f32 v);
void func_001AA788(Obj_193EE8* self, f32 v);

typedef void (*VFn_193EE8)(void*);

struct Obj_1935B0 {
    u8 pad0[0xC];
    f32 fC;
    u8 pad1[0x19D8 - 0x10];
    s32 f19D8;
    s32 f19DC;
};
struct Dst_1935B0 { char c; };

void* func_00160B28(Obj_1935B0* p);
s32 func_00160148(s32 v);
s32 func_001E1FD0(Dst_1935B0* dst, const char* fmt, ...);

struct __attribute__((packed)) Col_193318 { u8 r, g, b, a; };
struct Obj_193318 {
    u8 pad0[4];
    s32 h;
    s32 w;
    s32 x;
    s32 cnt;
    u8 r, g, b, pad1;
    Col_193318 c0;
    Col_193318 c1;
    Col_193318 c2;
};
struct Frame_193318 { u8 bytes[0x30]; };
struct Buf_193318 { u8 bytes[0x400]; Frame_193318 f; };

void func_001611B8(Frame_193318* f);
void func_001529C8(Frame_193318* f, s32 n, Buf_193318* b);
void func_00152B38(Frame_193318* f);
f32 func_001EAF28(f32 x);
void func_0019DDA0(s32 a, s32 b, s32 c, s32 d, Frame_193318* e, f32 x, f32 y, f32 z, f32 w);
void func_00161200(Frame_193318* f);
void func_00152D30(Frame_193318* f);
void func_00152D70(Frame_193318* f);
void func_001529E0(Frame_193318* f, s32 a, s32 b);
void func_00168A48(Buf_193318* b);

void func_001AA8F0(void* self);

struct Ctl_194F00 { u8 pad[0x250]; s32 mode250; u8 pad2[0x20]; s32 f274; };

void func_001AA958(void* self);

struct Ctl_194F38 { u8 pad[0x250]; s32 mode250; u8 pad2[0x20]; s32 f274; s32 f278; };

void func_001936A0(void* self, s32 v);

struct Ctl_195928 { u8 pad[0x260]; s32 f260; };

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

extern Boot_195958 D_00264A40;
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
typedef Obj_193EE8 Obj_1943E8;
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
extern f32 D_0026A22C;
struct Pair_26A230 { f32 f0; f32 f4; };
extern Pair_26A230 D_0026A230;
extern f32 D_0026A700;
extern f32 D_0026A704;

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
struct Menu_194F80 { char* title; f32 titleScale; f32 itemScale; s32 vertical; s32 count; s32* items; };
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
char* func_00193598(s32 index);
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

void func_001F5C0C(void* p, s32 zero, s32 size);

// The file's .data, in retail's order from 0x269CD8, and the strings of its menus, which open
// its .rodata. The style (func_00196330, the static initialiser, builds it) and the buffers the
// menus' labels are written into at run time are zeros until then.
struct Style_196330 {
    void* f0;
    u8 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    u32 f18;
    Style_196330(s32 size)
    {
        func_001F5C0C(this, 0, 0x1C);
        f4 = 0x2D;
        f8 = size;
        f14 = f10 = 0.6f;
        f18 = 0xFF7D4B00;
    }
};
struct Choice_26A138 { s32 count; char** labels; };

extern s32 D_0026A238[];
extern s32 D_0026A258[];
extern char D_0026A480[];
extern char D_0026A4C0[];
extern char D_0026A500[];
extern char D_0026A540[];
extern char D_0026A580[];
extern char D_0026A5C0[];
extern char D_0026A600[];
extern char D_0026A640[];
extern char D_0026A680[];
extern char D_0026A6C0[];

s32 D_00269CD8[8] = { 3, 18, 19, 20, 4, 5, 21, 9 };
s32 D_00269CF8[2] = { 0, 1 };
s32 D_00269D00[2] = { 2, 0 };
s32 D_00269D08[4] = { 10, 11, 12, 17 };
s32 D_00269D18[10] = { 6, 7, 8, 15, 16, 13, 14, 23, 17, 0 };
s32 D_00269D40[4] = { 24, 25, 26, 17 };
Menu_194F80 D_00269D50[33] = {
    { "Paused", 1.0f, 1.0f, 1, 8, D_0026A238 },
    { "Game Over. Try again?", 1.0f, 1.0f, 0, 2, D_00269CF8 },
    { "Really Quit?", 1.0f, 1.0f, 0, 2, D_00269CF8 },
    { "There is no Memory Card (PS2) inserted in\nMemory Card Slot 1\n\nSly Cooper requires 49 KB of free space\n\nPlease insert a Memory Card (PS2) containing sufficient space or you will not be able to save your progress\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "The Memory Card (PS2) in Memory Card Slot 1 is unformatted\n\nIf you do not format it then you will not be able to save your progress\n\nDo you want to format?", 0.7f, 1.0f, 0, 2, D_00269CF8 },
    { "\nFormatting the Memory Card (PS2) in Memory Card Slot 1\n\nPlease do not turn off your system or remove the Memory Card (PS2)\n", 0.7f, 1.0f, 1, 0, 0 },
    { "An error occurred while formatting the Memory Card (PS2) in Memory Card Slot 1\n\nYou will not be able to save your progress\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "No Sly Cooper Save File on the Memory Card (PS2) inserted in Memory Card Slot 1\n\nSly Cooper requires 49 KB of free space\n\nIf you do not create a Sly Cooper Save File then you will not be able to save your progress\n\nDo you want to create a Sly Cooper Save File?", 0.7f, 1.0f, 0, 2, D_00269CF8 },
    { "\nCreating the Sly Cooper Save File on the Memory Card (PS2) in Memory Card Slot 1\n\nPlease do not turn off your system or remove the Memory Card (PS2)\n", 0.7f, 1.0f, 1, 0, 0 },
    { "An error occurred while creating the Sly Cooper Save File on the Memory Card (PS2) in Memory Card Slot 1\n\nYour progress is not being saved\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "The Memory Card (PS2) inserted in Memory Card Slot 1 does not have enough free space to create a Sly Cooper Save File\n\nSly Cooper requires 49 KB of free space\n\nPlease insert a Memory Card (PS2) containing sufficient space or you will not be able to save your progress\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "Save Game", 1.0f, 0.7f, 1, 4, D_00269D08 },
    { "\nSaving...\n\nPlease do not turn off your system or remove the Memory Card (PS2)\n", 0.7f, 1.0f, 1, 0, 0 },
    { "Game Saved", 1.0f, 1.0f, 1, 1, D_00269D00 },
    { "Do you want to overwrite this game?", 0.7f, 1.0f, 0, 2, D_00269CF8 },
    { "An error occurred while writing to the Sly Cooper Save File on the Memory Card (PS2) in Memory Card Slot 1\n\nYour progress is not being saved\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "New Game", 1.0f, 0.7f, 1, 4, D_00269D08 },
    { "Load Game", 1.0f, 0.7f, 1, 4, D_00269D08 },
    { "Do you want to erase this game?", 0.7f, 1.0f, 0, 2, D_00269CF8 },
    { "\nErasing...\n\nPlease do not turn off your system or remove the Memory Card (PS2)\n", 0.7f, 1.0f, 1, 0, 0 },
    { "When the following icon appears,\nyour progress is being saved\n\n^15&2a&.^.\n\nWhile this icon is on screen, please\ndo not turn off your system or remove\nthe Memory Card (PS2)\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "The Memory Card (PS2) in Memory Card Slot 1 was removed\n\nAuto-save has been disabled\n\nUse the save game option to manually save your game and re-enable auto-save\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "The disc was removed\n\nPlease insert the Sly Cooper disc to continue playing", 0.8f, 1.0f, 1, 0, 0 },
    { "Options", 1.0f, 1.0f, 1, 9, D_0026A258 },
    { "&2T&. : Cancel\n&2+&. : Move\n&2X&. : Accept", 0.8f, 1.0f, 1, 0, 0 },
    { "Try again?", 1.0f, 1.0f, 0, 2, D_00269CF8 },
    { "Try again?", 1.0f, 1.0f, 0, 2, D_00269CF8 },
    { "CONGRATULATIONS!\n\nYou have beaten the\nMaster Thief Sprint!\n\nReturn to this level at any time\nto hear the Bonus Commentary!", 0.8f, 1.0f, 0, 1, D_00269D00 },
    { "TIME EXPIRED\n\nWould you like to retry\nthe Master Thief Sprint?\n\n", 0.8f, 1.0f, 0, 2, D_00269CF8 },
    { "CONGRATULATIONS!\n\nYou beat your best\nMaster Thief Sprint time!\n\nTry Again?", 0.8f, 1.0f, 0, 2, D_00269CF8 },
    { "You didn't beat your best\nMaster Thief Sprint time\n\nTry again?", 0.8f, 1.0f, 0, 2, D_00269CF8 },
    { "Controls", 1.0f, 0.8f, 1, 4, D_00269D40 },
    { "\nPlease insert a Memory Card (PS2) in Memory Card Slot 1 that contains a Sly Cooper Save File\n", 1.0f, 1.0f, 1, 1, D_00269D00 },
};
char* D_0026A068[28] = {
    "Yes",
    "No",
    "Continue",
    "Return to Game",
    "View Map",
    "Options...",
    "New Game...",
    "Load Game...",
    "Save Game...",
    D_0026A540,
    D_0026A480,
    D_0026A4C0,
    D_0026A500,
    D_0026A580,
    "Center Screen...",
    D_0026A5C0,
    D_0026A600,
    "Back",
    "Restart Race",
    "Restart Sprint",
    "Restart Level",
    "Exit Level",
    "Exit to Hideout",
    "Controls...",
    D_0026A640,
    D_0026A680,
    D_0026A6C0,
    0,
};
char* D_0026A0D8 = "New Game";
char* D_0026A0DC = "Empty";
char* D_0026A0E0[2] = { "Quit Game", "Save and Quit" };
char* D_0026A0E8[2] = { "Vibrations: On", "Vibrations: Off" };
char* D_0026A0F0[2] = { "Music: On", "Music: Off" };
char* D_0026A0F8[2] = { "Speakers: Stereo", "Speakers: Mono" };
char* D_0026A100[2] = { "Binoc-u-com: &2(&. Up = Look Down", "Binoc-u-com: &2(&. Up = Look Up" };
char* D_0026A108[2] = { "Turrets: &2(&. Up = Aim Down", "Turrets: &2(&. Up = Aim Up" };
char* D_0026A110[2] = { "Jet Pack: &2(&. Up = Fly Down", "Jet Pack: &2(&. Up = Fly Up" };
u32 D_0026A118[8] = { 0x2815A489, 0x4A3840F1, 0xDB146408, 0x9260417F, 0x4CCB23D6, 0x281349F9, 0xDB146685, 0x4A39BF71 };
Choice_26A138 D_0026A138[27] = {
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 2, D_0026A0E0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 2, D_0026A0E8 },
    { 0, 0 },
    { 2, D_0026A0F0 },
    { 2, D_0026A0F8 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 2, D_0026A100 },
    { 2, D_0026A108 },
    { 2, D_0026A110 },
};
Style_196330 D_0026A210(15);
f32 D_0026A22C = 5.0f;
Pair_26A230 D_0026A230 = { 2.0f, 0.0f };
s32 D_0026A238[8] = { 0 };
s32 D_0026A258[138] = { 0 };
char D_0026A480[64] = { 0 };
char D_0026A4C0[64] = { 0 };
char D_0026A500[64] = { 0 };
char D_0026A540[64] = { 0 };
char D_0026A580[64] = { 0 };
char D_0026A5C0[64] = { 0 };
char D_0026A600[64] = { 0 };
char D_0026A640[64] = { 0 };
char D_0026A680[64] = { 0 };
char D_0026A6C0[64] = { 0 };
f32 D_0026A700 = 0;
f32 D_0026A704 = 0;
f32 D_0026A708 = 0;
f32 D_0026A70C = 0;

Obj_193210* func_00193210(Obj_193210* self, Word_193210* s1, Word_193210* s2, Word_193210* s3, Word_193210* s4);
void func_00193270(S_193270* p);
void func_00193288(State_193288* self, s32 value);
void func_00193300(S_193300* p);
void func_00193318(Obj_193318* o);
void func_001935B0(Obj_1935B0* self, Dst_1935B0* dst);
s32 func_00193660(void);
void func_00193E58(Obj_193E58* self);
void func_00193EE8(Self_193EE8* self, s32 a, s32 b);
void func_001940E8(Obj_1940E8* self, s32 mode);
void func_00194278(void* a0, s32 a1, s32 a2);
void func_00194398(void);
void func_001943E8(Self_1943E8* self);
void func_00194D30(Self_194D30* self, s32 idx, s32 value);
void func_00194E60(Ctl_194E60* self, s32 v);
void func_00194F00(Ctl_194F00* self);
void func_00194F38(Ctl_194F38* self);
void func_00194F80(Self_194F80* self);
void func_00195928(Ctl_195928* self, s32 v);
void func_00195958(Menu_195958* self);
void func_001961C0(Self_1961C0* self);

Obj_193210* func_00193210(Obj_193210* self, Word_193210* s1, Word_193210* s2, Word_193210* s3, Word_193210* s4)
{
    self->f14 = *s1;
    self->f18 = *s2;
    self->f1C = *s3;
    self->f20 = *s4;
    self->f00 = 0;
    self->f10 = 0;
    self->f0C = 0;
    self->f08 = 0;
    self->f04 = 0;
    return self;
}

void func_00193270(S_193270* p) { p->a=0; p->e=0; p->d=0; p->c=0; p->b=0; }

void func_00193288(State_193288* self, s32 value)
{
	if (self->ptr != 0) {
		if (self->size == 0) { self->scaled = value << 1; self->size = value; func_00168AF8(self); }
		else if (self->value == value) self->repeat++;
		else self->repeat = 0;
		self->value = value;
		func_00193318(self);
	}
}

void func_00193300(S_193300* p) { p->a=0; p->e=0; p->d=0; p->c=0; p->b=0; }

void func_00193318(Obj_193318* o)
{
    Buf_193318 buf;
    s32 n1;
    s32 n2;
    Col_193318 c;

    n1 = (s32)((f32)o->w * 620.0f / (f32)o->h);
    n2 = (s32)((f32)n1 * (f32)(o->w - o->x) / (f32)o->w);
    func_001611B8(&buf.f);
    func_001529C8(&buf.f, 0x40, &buf);
    func_00152B38(&buf.f);
    {
        u8 r = o->r;
        u8 g = o->g;
        u8 b = o->b;
        f32 y = func_001EAF28(412.909088f) * 1.1f;
        f32 z = (f32)(n2 + 10);
        func_0019DDA0(r, g, b, 255, &buf.f, 10.0f, y, z, func_001EAF28(412.909088f) * 1.1f + 6.6000004f);
    }
    if (o->cnt <= 0) {
        c = o->c0;
    } else if (o->cnt == 1) {
        c = o->c1;
    } else {
        c = o->c2;
    }
    {
        u8 r = c.r;
        u8 g = c.g;
        u8 b = c.b;
        f32 x = (f32)(n2 + 10);
        f32 y = func_001EAF28(412.909088f) * 1.1f;
        f32 z = (f32)(n1 + 10);
        func_0019DDA0(r, g, b, 255, &buf.f, x, y, z, func_001EAF28(412.909088f) * 1.1f + 6.6000004f);
    }
    func_00161200(&buf.f);
    func_00152D30(&buf.f);
    func_00152D70(&buf.f);
    func_001529E0(&buf.f, 0, 0);
    func_00168A48(&buf);
}

char* func_00193598(s32 index)
{
    return D_0026A068[index];
}

void func_001935B0(Obj_1935B0* self, Dst_1935B0* dst)
{
    void* a = func_00160B28(self);
    s32 b = func_00160148((self->f19D8 << 8) | self->f19DC);
    s32 v = (s32)(self->fC * (1.0f / 60.0f));
    s32 t = v > 0 ? v : 1;
    func_001E1FD0(dst, "%d%% - %s - %d:%02d", a, b, t / 60, t % 60);
}

s32 func_00193660(void)
{
    s32 r = func_0015A418(D_00275710, 5, 0x42C, 0);
    s32 v;
    if (r == 0) {
        v = 0;
    } else {
        v = *(s32*)(r + 0x48);
    }
    return v;
}

// The jump tables of func_001936A0.
INCLUDE_RODATA(jtbl_0024C430);
INCLUDE_RODATA(jtbl_0024C480);
INCLUDE_RODATA(jtbl_0024C4D0);
ASM_FUNC(func_001936A0);

void func_00193E58(Obj_193E58* self)
{
    func_001AA268(self);
    if (func_0015C188(2)) {
        self->f210 = (void**)&D_0026A210;
        *self->f210 = func_0015C1C0(2);
    }
    self->f260 = -1;
    self->f27C = -1;
    for (u32 i = 0; i < 3; i++) {
        self->arr268[i] = -1;
    }
    self->f284 = 1.0f;
}

void func_00193EE8(Self_193EE8* self, s32 a, s32 b)
{
    if (a == b) {
        return;
    }
    if (self->f288 != 0) {
        func_001BE998();
        self->f288 = 0;
    }
    if (a == 11) {
        goto call;
    }
    if (a > 10) {
        if (a < 18) {
            if (a > 15) {
            call:
                ((VFn_193EE8)D_0026EC70.vt[15])(&D_0026EC70);
            }
        }
    }
    switch (b) {
    case 11:
    case 16:
    case 17: {
        Obj_193EE8* o = &D_0026EC70;
        func_001AA8B8(o, 0.0f);
        func_001AA788(o, 0.6f);
        break;
    }
    case 24: {
        D_0026A700 = D_0026A708 = (f32)(u32)((Dev_193EE8*)&D_00262490)->a.x;
        D_0026A704 = D_0026A70C = (f32)((u32)(((Dev_193EE8*)&D_00262490)->q18 >> 12) & 0x7FF);
        break;
    }
    case -1:
        ((VFn_193EE8)D_0026C6C8.vt[15])(&D_0026C6C8);
        ((VFn_193EE8)D_0026C948.vt[15])(&D_0026C948);
        ((VFn_193EE8)D_0026CBC8.vt[15])(&D_0026CBC8);
        ((VFn_193EE8)D_0026CE48.vt[15])(&D_0026CE48);
        ((VFn_193EE8)D_00274118.vt[15])(&D_00274118);
        break;
    }
}

void func_001940E8(Obj_1940E8* self, s32 mode) {
    if (self->f25C == mode) return;
    if (mode != 0) {
        s32 key = (*(u32*)((*(u8**)&D_002623C0) + 0x19D8) << 8) | *(u32*)((*(u8**)&D_002623C0) + 0x19DC);
        if (key == 0x308) {
            func_001BED48();
            func_001E96F8((Obj_1940E8*)D_00275BC0, 5);
        } else if (D_0027051C != 0) {
            func_001E96F8((Obj_1940E8*)D_00275BC0, 5);
        } else {
            u8* base = D_00275BC0;
            if (((s32*)base)[1] == 3) {
                func_001E96F8((Obj_1940E8*)base, 4);
            } else {
                func_001E96F8((Obj_1940E8*)base, 5);
            }
        }
        func_00193EE8(self, -1, self->f260);
        ((VFn_1940E8)self->vtbl[14])(self);
        func_0016E0F0((Bits_1940E8)1);
        func_0016EC88((Pool_1940E8*)((u8*)&D_00262C70));
    } else {
        s32 key = (*(u32*)((*(u8**)&D_002623C0) + 0x19D8) << 8) | *(u32*)((*(u8**)&D_002623C0) + 0x19DC);
        if (key == 0x308) {
            func_001BED70();
            func_001E96F8((Obj_1940E8*)D_00275BC0, 3);
        } else if (D_0027051C != 0) {
            func_001E96F8((Obj_1940E8*)D_00275BC0, 3);
        } else if (self->f260 != 0) {
            func_001E96F8((Obj_1940E8*)D_00275BC0, 3);
        } else {
            func_001E96F8((Obj_1940E8*)D_00275BC0, 6);
        }
        func_00193EE8(self, self->f260, -1);
        ((VFn_1940E8)self->vtbl[15])(self);
        func_0016E118((Bits_1940E8)1);
    }
    self->f25C = mode;
}

void func_00194278(void* a0, s32 a1, s32 a2)
{
    func_00194D30(a0, 0, -1);
    Glob_194278* g = (Glob_194278*)D_002623C0;
    s32 key = (g->f19D8 << 8) | g->f19DC;
    if (key == 0x106) {
        if (a1 != 0) {
            Rec_194278 r;
            r.f0 = 1;
            r.f4 = D_00275B04;
            r.f8 = -1;
            r.fC = -1;
            r.f10 = 0;
            func_001EFFA0(D_00275F80, &r, a2);
        } else {
            void* p = func_0015A838(D_00275710, 5, 0x5F, 0);
            func_001A4EF0(p, 6);
        }
        return;
    }
    if (a1 != 0) {
        Rec_194278 r;
        r.f0 = 1;
        r.f4 = D_00275B04;
        r.f8 = -1;
        r.fC = -1;
        r.f10 = 0x10;
        func_001EFFA0(D_00275F80, &r, a2);
    } else {
        func_001F4408(0, a2);
    }
}

void func_00194398(void)
{
    Args_194398 args;
    args.kind = 1;
    args.text = D_00247AB0;
    args.x = -1;
    args.y = -1;
    args.z = 4;
    func_001EFFA0(D_00275F80, &args, 0);
}

void func_001943E8(Self_1943E8* self)
{
    Glob_1943E8* g = (*(Glob_1943E8**)&D_002623C0);
    Row_1943E8* row = &((Row_1943E8*)&D_00269D50)[self->f260];
    s32 on;
    s32 n;
    Pad_1943E8* pad;

    on = 0;
    switch ((g->f19D8 << 8) | g->f19DC) {
    case 0x106:
    case 0x204:
    case 0x304:
    case 0x307:
    case 0x407:
    case 0x502:
    case 0x504:
        break;
    default:
        on = self->f260 == 0;
        break;
    }
    if (on) {
        ((VFn_1943E8)D_0026C6C8.vt[14])(&D_0026C6C8);
        ((VFn_1943E8)D_0026C948.vt[14])(&D_0026C948);
        ((VFn_1943E8)D_0026CBC8.vt[14])(&D_0026CBC8);
        ((VFn_1943E8)D_0026CE48.vt[14])(&D_0026CE48);
    } else {
        ((VFn_1943E8)D_0026C6C8.vt[15])(&D_0026C6C8);
        ((VFn_1943E8)D_0026C948.vt[15])(&D_0026C948);
        ((VFn_1943E8)D_0026CBC8.vt[15])(&D_0026CBC8);
        ((VFn_1943E8)D_0026CE48.vt[15])(&D_0026CE48);
    }
    switch (self->f260) {
    case 0:
    case 11:
    case 17:
        D_00274118.f27C = func_00160B28((*(Glob_1943E8**)&D_002623C0));
        D_00274118.f264 = &D_00274118.f27C;
        ((VFn_1943E8)D_00274118.vt[14])(&D_00274118);
        break;
    default:
        ((VFn_1943E8)D_00274118.vt[15])(&D_00274118);
        break;
    }
    if (self->f288 != 0) {
        if (func_001BE810() != 0) {
            func_0011CE30();
        }
        self->f288 = func_001BE980();
    }
    s32 ready = 1;
    if (self->f274 != 0 || self->f250 != 2 || !(0.1f < D_00261868 - self->f254)) {
        ready = 0;
    }
    pad = &D_00262C70;
    if (row->f10 == 0) {
        n = 0;
    } else if (row->fC != 0) {
        n = func_0016EED0(pad);
    } else {
        n = func_0016EC98(pad);
    }
    if (n > 0) {
        self->f264 = (self->f264 + 1) % row->f10;
        func_001BFCD8(0x79, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    if (n < 0) {
        self->f264 = (self->f264 + row->f10 - 1) % row->f10;
        func_001BFCD8(0x79, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    if (!ready) {
        return;
    }
    if (pad->fAA & 0x810) {
        func_0016EC20(&D_00262C70, 0x810);
        func_001961C0(self);
        return;
    }
    if (pad->fAA & 0x80) {
        func_0016EC20(&D_00262C70, 0x80);
        if (self->f260 == 11 || self->f260 == 16) {
            Ent_1943E8* e = &((Ent_1943E8*)&D_002542D8)[row->items[self->f264]];
            if (e->fC != 0.0f) {
                D_0026998C = e;
                func_00194D30(self, 1, 0x12);
            }
        }
        return;
    }
    if (pad->fAA & 0x40) {
        func_0016EC20(&D_00262C70, 0x40);
        func_00195958(self);
        return;
    }
    switch (self->f260) {
    case 24: {
        f32 a = func_0016F108(pad, 0);
        f32 dx = a - func_0016F108(pad, 1);
        f32 b = func_0016F108(pad, 3);
        f32 dy = b - func_0016F108(pad, 2);
        f32 v;
        if (dx == 0.0f && dy == 0.0f) {
            return;
        }
        D_0026A700 = Clamp_1943E8::Of(D_0026A700 + dx * D_0026A22C, 424.0f, 848.0f);
        v = Clamp_1943E8::Of(D_0026A704 + dy * D_0026A230.f0, 10.0f, 90.0f);
        D_0026A704 = v;
        {
            Gs_1943E8* gs = ((Gs_1943E8*)&D_00262490);
            s32 h = func_001FD7A0(D_0026A700);
            Reg_1943E8 ra = gs->f40;
            RegA_1943E8 rb = gs->f18;
            ra.lo = h;
            rb.lo = h;
            gs->f40 = ra;
            gs->f18 = rb;
            s32 w = func_001FD7A0(v);
            ra.mid = w & ~1;
            rb.mid = w & 0x7FE;
            gs->f40 = ra;
            gs->f18 = rb;
        }
        break;
    }
    case 11:
    case 16:
    case 17:
        if (D_00264A58.v[0] != 1) {
            func_001961C0(self);
            return;
        } else {
            s32 id = row->items[self->f264];
            if ((u32)(id - 10) < 3) {
                Ent_1943E8* e = &((Ent_1943E8*)&D_002542D8)[id];
                if (self->f260 == 16) {
                    if (e->fC != 0.0f) {
                        ((VFnS_1943E8)D_0026EC70.vt[8])(&D_0026EC70, "&2S&. : Erase Game");
                    } else {
                        ((VFnS_1943E8)D_0026EC70.vt[8])(&D_0026EC70, "&2X&. : New Game");
                    }
                } else if (self->f260 == 17) {
                    if (e->fC != 0.0f) {
                        ((VFnS_1943E8)D_0026EC70.vt[8])(&D_0026EC70, "&2X&. : Load Game");
                    } else {
                        ((VFnS_1943E8)D_0026EC70.vt[8])(&D_0026EC70, "&2X&. : New Game");
                    }
                } else {
                    if (e->fC != 0.0f) {
                        ((VFnS_1943E8)D_0026EC70.vt[8])(&D_0026EC70, "&2X&. : Overwrite Game\n&2S&. : Erase Game");
                    } else {
                        ((VFnS_1943E8)D_0026EC70.vt[8])(&D_0026EC70, "&2X&. : Save Game");
                    }
                }
                ((VFn_1943E8)D_0026EC70.vt[14])(&D_0026EC70);
            } else {
                ((VFn_1943E8)D_0026EC70.vt[15])(&D_0026EC70);
            }
        }
        break;
    case 18:
        if (D_00264A58.v[0] != 1) {
            func_001961C0(self);
        }
        break;
    case 20: {
        Item_1943E8* it;
        if (D_00264A58.v[0] != 1) {
            func_001961C0(self);
        }
        it = func_001F6880(row->f0, "&2");
        if (it != 0) {
            it->f2 = func_001AEA08();
        }
        break;
    }
    case 3:
    case 4:
    case 7:
    case 10:
    case 32:
        if (D_00264A4C == 5) {
            func_00194D30((Self_1943E8*)D_0026FF68, 1, -1);
        }
        break;
    case 5: {
        Pool_1943E8* p = ((Pool_1943E8*)&D_00269990);
        if (func_0018B770(p) == 0) {
            if (p->f10 == 0) {
                func_0018B670(p, (void*)(void (*)(Boot_195958*))func_0018C250, ((u8*)&D_00264A40));
                func_00194D30(self, 1, 8);
            } else {
                func_00194D30(self, 1, 6);
            }
        }
        break;
    }
    case 8: {
        Pool_1943E8* p = ((Pool_1943E8*)&D_00269990);
        if (func_0018B770(p) == 0) {
            if (p->f10 == 0) {
                func_00194D30(self, 1, -1);
            } else {
                func_00194D30(self, 1, 9);
            }
        }
        break;
    }
    case 12: {
        Pool_1943E8* p = ((Pool_1943E8*)&D_00269990);
        if (func_0018B770(p) == 0) {
            if (p->f10 == 0) {
                func_00194D30(self, 1, -1);
                if (self->f27C == 2) {
                    func_00194398();
                }
            } else {
                func_00194D30(self, 0, 0x17);
                func_00194D30(self, 1, 0xF);
            }
        }
        break;
    }
    case 19: {
        Pool_1943E8* p = ((Pool_1943E8*)&D_00269990);
        if (func_0018B770(p) == 0) {
            D_0026998C = 0;
            if (p->f10 == 0) {
                func_00194D30(self, 1, -1);
            } else {
                func_00194D30(self, 0, 0x17);
                func_00194D30(self, 1, 0xF);
            }
        }
        break;
    }
    }
}

void func_00194D30(Self_194D30* self, s32 idx, s32 value)
{
    s32 s1;
    s32 s2;
    u32 i;
    s32* p;

    s2 = value;
    self->arr268[idx] = s2;
    p = self->arr268;
    for (i = 0; i < 3; i++) {
        if (*p != -1) {
            s2 = *p;
        }
        p++;
    }
    if (self->f274 != 0) {
        s1 = self->f278;
    } else {
        s1 = self->f260;
    }
    func_00193EE8(self, s1, s2);
    if (s1 != s2) {
        if (self->f250 == 0) {
            func_00195928(self, s2);
        } else if (self->f250 >= 0) {
          if (self->f250 < 4) {
            if (s2 == -1) {
                self->f274 = 0;
                self->f278 = s2;
            } else {
                self->f278 = s2;
                self->f274 = 1;
                ((Obj_194D30*)self)->vtbl[16](self, 3);
            }
          }
        }
    }
    if (s2 == -1) {
        if (self->f25C != 0) {
            func_001E9570(D_00275BC0);
        }
    } else {
        if (self->f25C == 0) {
            func_001E9498(D_00275BC0, self);
        }
    }
}

void func_00194E60(Ctl_194E60* self, s32 v)
{
    s32 flag = v;

    if (self->f250 == v) return;
    if (self->f250 == 0 && self->f260 == 0) {
        func_001936A0(self);
    }
    if (v == 0) {
        if (self->f274 != 0) {
            func_00195928(self, self->f278);
            flag = 1;
            self->f274 = 0;
            self->f278 = -1;
        } else {
            if (self->f260 == 0) {
                func_001936A0(self);
            }
        }
    }
    func_001AA998(self, flag);
}

void func_00194F00(Ctl_194F00* self)
{
    if (self->mode250 == 3 && self->f274 != 0) return;
    func_001AA8F0(self);
}

void func_00194F38(Ctl_194F38* self)
{
    if (self->mode250 == 3 && self->f274 != 0) {
        self->f274 = 0;
        self->f278 = -1;
        return;
    }
    func_001AA958(self);
}

void func_00194F80(Self_194F80* self)
{
    f32 cx;
    f32 cy;
    f32 h;
    f32 w;
    f32 pulse;
    f32 fade;
    s32 alpha;
    Menu_194F80* menu;
    f32 lineH;
    f32 base;
    f32 x;
    s32 i;

    if (self->f250 == 0) {
        return;
    }
    {
        f32 ww = self->f234;
        f32 hh = self->f238;
        f32 s = self->f23C;
        f32 x0 = self->f224 + ww * 0.5f; 
        f32 y0 = self->f228 + hh * 0.5f; 
        w = ww * s; 
        cx = self->f224 * s + x0 * (1.0f - s); 
        cy = self->f228 * s + y0 * (1.0f - s); 
        h = hh * s; 
    }
    pulse = func_00205400(D_00261858[4] * 10.0f) * 0.5f + 0.5f;
    menu = &((Menu_194F80*)&D_00269D50)[self->f260];
    fade = 1.0f;
    if (self->f260 == 0 && D_00275BEC == 2) {
        fade = 1.0f - D_00262CEC;
    }
    self->f284 = func_001EA4B8(D_00260ED0, 0, self->f284, fade, D_00261858[5]);
    alpha = (u8)(s32)(self->f284 * 255.0f);
    if (self->f210 != 0) {
        Out_194F80 out;
        s32 backColor = 0xFF808080;
        func_00137228(&out, cx, cy);
        func_00137238(&out, w, h);
        {
            Col_194F80 tmp;
            tmp.v[0] = backColor;
            func_00137248(&out, &tmp);
        }
        func_00137260(&out, 0);
        func_00137268(&out, 0);
        Rgba_194F80 saved = self->f210->f18;
        {
            Rgba_194F80 t = saved;
            t.a = alpha;
            self->f210->f18 = t;
        }
        if (menu->count == 0) {
            Owner_194F80* cur = self->f210;
            Rgba_194F80 gray;
            gray.r = 0x6F; 
            gray.g = 0x6F; 
            gray.b = 0x6F; 
            gray.a = alpha; 
            Rgba_194F80 res;
            Lerp_194F80::Do(&res, cur->f18, gray, pulse * pulse);
            cur->f18 = res;
        }
        CallHook_194F80::Do(self->f210, &out, D_00262280);
        self->f210->f18 = saved;
    }
    if (menu->title != 0) {
        Buf_194F80 buf;
        Out_194F80 out;
        Rgba_194F80 c;
        f32 sc = menu->titleScale * self->f23C;
        func_0015C8B8(self->f4, sc, sc);
        func_0015DB28(&buf, menu->title, self->f4);
        c.r = 0x7F;
        c.g = 0x7F;
        c.b = 0x7F;
        c.a = alpha;
        Setup_194F80::Do(&out, cx, cy, w, h, *(s32*)&c, 1);
        func_0015E318(&buf, &out, 0, D_00262280);
        cy += func_0015E1B0(&buf, 500.0f);
        func_0015C900(self->f4);
    }
    base = cy + -1.0f;
    {
        f32 sc = menu->itemScale * self->f23C;
        func_0015C8B8(self->f4, sc, sc);
    }
    lineH = (f32)self->f4->f8 * self->f4->f48;
    if (menu->vertical == 0) {
        f32 total = 0.0f;
        for (s32 k = 0; k < menu->count; k++) {
            Buf_194F80 buf;
            if (k != 0) {
                total += (f32)self->f4->f4 * self->f4->f44 + (f32)self->f4->f4 * self->f4->f44;
            }
            void* str = func_00193598(menu->items[k]);
            func_0015DB28(&buf, str, self->f4);
            total += func_0015DFF8(&buf);
        }
        x = cx + (w - total) * 0.5f;
    }
    for (i = 0; i < menu->count; i++) {
        Rgba_194F80 col;
        f32 grow;
        f32 width;
        void* str;
        f32 th;
        if (i == self->f264) {
            Rgba_194F80 c;
            c.r = 0x6F;
            c.g = 0x6F;
            c.b = (s32)(pulse * 64.0f) + 0x2F;
            c.a = alpha;
            col = c;
            grow = (1.0f - pulse) * 0.1f + 1.0f;
        } else {
            Rgba_194F80 c;
            c.r = 0x5F;
            c.g = 0x5F;
            c.b = 0x5F;
            c.a = alpha;
            col = c;
            grow = 1.0f;
        }
        Buf_194F80 buf;
        str = func_00193598(menu->items[i]);
        func_0015DB28(&buf, str, self->f4);
        width = func_0015DFF8(&buf);
        if (menu->vertical != 0) {
            x = cx + (w - width) * 0.5f;
        }
        {
            f32 sc = menu->itemScale * self->f23C * grow;
            func_0015C8B8(self->f4, sc, sc);
        }
        func_0015DB28(&buf, str, self->f4);
        f32 width2 = func_0015DFF8(&buf);
        th = (f32)self->f4->f8 * self->f4->f48;
        Out_194F80 out;
        Setup_194F80::Do(&out, x + (width - width2) * 0.5f, cy + (lineH - th) * 0.5f, w, th, *(s32*)&col, 0);
        func_0015E318(&buf, &out, 0, D_00262280);
        func_0015C900(self->f4);
        if (menu->vertical != 0) {
            cy += (f32)self->f4->f8 * self->f4->f48;
        } else {
            x += width + ((f32)self->f4->f4 * self->f4->f44 + (f32)self->f4->f4 * self->f4->f44);
        }
    }
    func_0015C900(self->f4);
    if (menu->title != 0 && menu->count != 0) {
        Rgba_194F80 c = *(Rgba_194F80*)&D_0026A210.f18;
        c.a = alpha;
        s32 y = (s32)((base * 0.45454547f + 1936.0f) * 16.0f);
        func_001AE3B8((s32)((cx + 1728.0f) * 16.0f), y, 0, (s32)((cx + w + 1728.0f) * 16.0f), y, 0, &c, 0);
    }
}

void func_00195928(Ctl_195928* self, s32 v)
{
    if (self->f260 != v) {
        self->f260 = v;
        if (v != -1) func_001936A0(self, v);
    }
}

void func_00195958(Menu_195958* self)
{
    s32 sel = D_00269D50[self->f260].items ? D_00269D50[self->f260].items[self->f264] : -1;
    if (sel == 0x11) {
        func_001961C0(self);
        return;
    }
    switch (self->f260) {
    case 0:
        switch (sel) {
        case 3:
            func_00194D30(self, 0, -1);
            return;
        case 4: {
            Sub_195958* s = &D_0026F808;
            if (s->f260 != 0) {
                func_00194D30(self, 0, -1);
                func_001E9498(D_00275BC0, s);
                return;
            }
            func_001BFCD8(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            return;
        }
        case 18: {
            s32 v;
            void* s2 = (void*)func_00193660();
            void* s0 = func_001925F0();
            if (s2 != 0 && s0 != 0 && func_001300E8(s0, 0x19) != 0) {
                func_001B6598(s2, &v);
                if (v < 0x431) {
                    if (v >= 0x42F) {
                        func_001D9338(s0);
                        func_001B6628(s2, 0x42E);
                    }
                }
            }
            func_00194D30(self, 0, -1);
            return;
        }
        case 19:
        case 20:
            func_00194278(self, 1, 1);
            return;
        case 21:
            func_00194D30(self, 0, -1);
            func_001F4408(1, 2);
            return;
        case 22:
            func_00194D30(self, 0, -1);
            func_001F0428(D_00247AD0, -1, 2);
            return;
        case 9:
            func_00194D30(self, 0, 2);
            return;
        case 5:
            func_00194D30(self, 0, 0x17);
            return;
        case 23:
            func_00194D30(self, 0, 0x1F);
            return;
        }
        return;
    case 23:
        switch (sel) {
        case 6:
            func_0018C178(&D_00264A40, 1);
            func_00194D30(self, 0, 0x10);
            return;
        case 7:
            func_0018C178(&D_00264A40, 1);
            func_00194D30(self, 0, 0x11);
            return;
        case 8:
            func_0018C178(&D_00264A40, 1);
            func_00194D30(self, 0, 0xB);
            return;
        case 13:
            func_001A7F50(((Glob_195958*)D_002623C0));
            {
                s32 keep;
                keep = self->f264;
                func_001936A0(self);
                self->f264 = keep;
            }
            return;
        case 15: {
            Glob_195958* g = ((Glob_195958*)D_002623C0);
            g->f19EC ^= 0x80;
            func_001C0760(g->f19EC & 0x80);
            {
                s32 keep;
                keep = self->f264;
                func_001936A0(self);
                self->f264 = keep;
            }
            return;
        }
        case 16: {
            Glob_195958* g = ((Glob_195958*)D_002623C0);
            g->f19EC ^= 0x40;
            func_001C0790(g->f19EC & 0x40);
            {
                s32 keep;
                keep = self->f264;
                func_001936A0(self);
                self->f264 = keep;
            }
            return;
        }
        case 14:
            func_00194D30(self, 0, 0x18);
            return;
        case 23:
            func_00194D30(self, 0, 0x1F);
            return;
        }
        return;
    case 27:
        if ((func_001602A0() & 8) != 0) {
            func_00160578(8);
            return;
        }
        func_00194278(self, 0, 2);
        return;
    case 1:
    case 26:
    case 28:
    case 29:
    case 30:
        func_00194278(self, (u32)sel < 1, 1);
        return;
    case 25: {
        s32 a = self->f280;
        self->f280 = 0;
        func_001B64D8(a, sel == 0 ? 0x434 : 0x435);
        func_00194D30(self, 0, -1);
        return;
    }
    case 2:
        if (sel == 0) {
            Boot_195958* b = &D_00264A40;
            if (b->f4F44 != 0) {
                self->f27C = 2;
                if ((((Glob_195958*)D_002623C0)->f19EC & 0x100) == 0) {
                    func_00194D30(self, 1, 0x14);
                } else {
                    func_00194D30(self, 1, 0xC);
                    func_0018B670(&D_00269990, (void*)func_0018C638, b);
                }
            } else {
                func_00194398();
            }
            func_00194D30(self, 0, -1);
            return;
        }
        func_00194D30(self, 0, -1);
        return;
    case 31:
        switch (sel) {
        case 0x18: {
            ((Glob_195958*)D_002623C0)->f19EC ^= 0x200;
            s32 keep = self->f264;
            func_001936A0(self);
            self->f264 = keep;
            return;
        }
        case 0x19: {
            ((Glob_195958*)D_002623C0)->f19EC ^= 0x400;
            s32 keep = self->f264;
            func_001936A0(self);
            self->f264 = keep;
            return;
        }
        case 0x1A: {
            ((Glob_195958*)D_002623C0)->f19EC ^= 0x800;
            s32 keep = self->f264;
            func_001936A0(self);
            self->f264 = keep;
            return;
        }
        }
        return;
    case 14:
        if (sel == 0) {
            goto c6030;
        }
        func_00194D30(self, 1, -1);
        return;
    case 4:
        if (sel == 0) {
            func_0018B670(&D_00269990, (void*)func_0018C1A8, &D_00264A40);
            func_00194D30(self, 1, 5);
            return;
        }
        goto c5EC0;
    case 7:
        if (sel == 0) {
            func_0018B670(&D_00269990, (void*)func_0018C250, &D_00264A40);
            func_00194D30(self, 1, 8);
            return;
        }
        goto c5EC0;
    case 3:
    case 6:
    case 9:
    case 10:
    case 21:
    case 32:
    c5EC0: {
        s32 v;
        func_00194D30(self, 1, -1);
        func_0018C178(&D_00264A40, 2);
        v = self->f268;
        if (v == 0xB) {
            goto c5F08;
        }
        if (v < 0xB) {
            return;
        }
        if (v >= 0x12) {
            return;
        }
        if (v < 0x10) {
            return;
        }
    }
    case 24:
    c5F08:
        func_00194D30(self, 0, 0x17);
        return;
    case 16: {
        Ent_195958* e = &D_002542D8[sel];
        if (e->fC == 0.0f) {
            func_00194D30(self, 0, -1);
            D_00264A40.f4F44 = e;
            func_0018C568(&D_00264A40);
            func_00160948();
            return;
        }
        func_001BFCD8(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    case 17:
        func_00194D30(self, 0, -1);
        D_00264A40.f4F44 = &D_002542D8[sel];
        func_0018C568(&D_00264A40);
        func_00160948();
        return;
    case 11: {
        Ent_195958* e;
        u32 p;
        p = sel * sizeof(Ent_195958);
        p += (u32)D_002542D8;
        e = (Ent_195958*)p;
        D_00264A40.f4F4C = e;
        if (e->fC == 0.0f) {
        c6030:
            Boot_195958* b;
            b = &D_00264A40;
            b->f4F44 = b->f4F4C;
            self->f27C = 0xB;
            if ((((Glob_195958*)D_002623C0)->f19EC & 0x100) == 0) {
                func_00194D30(self, 1, 0x14);
            } else {
                func_00194D30(self, 1, 0xC);
                func_0018B670(&D_00269990, (void*)func_0018C638, b);
            }
            func_00194D30(self, 0, -1);
            return;
        }
        func_00194D30(self, 1, 0xE);
        return;
    }
    case 18:
        if (sel == 0) {
            func_0018B670(&D_00269990, (void*)func_0018C770, &D_00264A40);
            func_00194D30(self, 1, 0x13);
            return;
        }
        func_00194D30(self, 1, -1);
        return;
    case 13:
        func_00194D30(self, 1, -1);
        return;
    case 20: {
        ((Glob_195958*)D_002623C0)->f19EC |= 0x100;
        s32 v = self->f27C;
        switch (v) {
        case 2:
        case 0xB:
            func_00194D30(self, 1, 0xC);
            break;
        case -1:
            func_00194D30(self, 1, -1);
            D_00273EB0.vt->f38(&D_00273EB0);
            break;
        }
        func_0018B670(&D_00269990, (void*)func_0018C638, &D_00264A40);
        return;
    }
    }
}

void func_001961C0(Self_1961C0* self)
{
    switch (self->state) {
    case 0:
        func_00194D30(self, 0, -1);
        break;
    case 23:
        if ((u32)(D_00275BF0 - 1) < 2) {
            func_00194D30(self, 0, -1);
            break;
        }
        func_00194D30(self, 0, 0);
        break;
    case 24: {
        Gs_1961C0* g = &D_00262490;
        s32 v = func_001FD7A0(D_0026A708);
        Reg_1961C0 a = g->f40;
        RegA_1961C0 b = g->f18;
        a.lo = v;
        b.lo = v;
        g->f40 = a;
        g->f18 = b;
        s32 w = func_001FD7A0(D_0026A70C);
        a.mid = w;
        b.mid = w;
        g->f40 = a;
        g->f18 = b;
        func_00194D30(self, 0, 0x17);
        break;
    }
    case 2:
        func_00194D30(self, 0, 0);
        break;
    case 13:
        func_00194D30(self, 1, -1);
        break;
    case 11:
    case 16:
    case 17:
    case 31:
        func_00194D30(self, 0, 0x17);
        break;
    case 14:
    case 18:
        func_00194D30(self, 1, -1);
        break;
    }
}

// The style above is built by the static initialiser GCC writes here (func_00196330), and its
// _GLOBAL_$I$ (func_001963B8) follows the 16 bytes the linker left of two layout setters this
// file wrote out after it (tools/compile.py moves the block there).
LINKER_REMNANT_AFTER_INIT(func_001963A8);
