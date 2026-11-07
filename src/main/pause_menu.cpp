// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
#include "screen_element.h"
#include "v24a0.h"
#include "v24a2.h"
#include "shapes.h"
#include "s193210.h"
#include "text_reader.h"
#include "layout_137228.h"
#include "game_progress.h"
#include "pad_record.h"
#include "memory_card.h"
#include "background_job.h"

struct State_193288 { void* ptr; s32 scaled; s32 size; s32 value; s32 repeat; };
void func_00168AF8(State_193288*);
void func_00193318(State_193288*);

s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);

s32 func_0015C188(s32 k);
V24A2* func_0015C1C0(s32 k);

struct S_193270 { s32 a,b,c,d,e; };

struct S_193300 { s32 a,b,c,d,e; };

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

s32 func_00160148(s32 v);
s32 func_001E1FD0(char* dst, const char* fmt, ...);

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
struct Buf_193318 { u8 bytes[0x400]; V24A0 f; };

void* func_001611B8(V24A0* f);
void func_001529C8(V24A0* f, s32 n, Buf_193318* b);
void func_00152B38(V24A0* f);
f32 func_001EAF28(f32 x);
void func_0019DDA0(s32 a, s32 b, s32 c, s32 d, V24A0* e, f32 x, f32 y, f32 z, f32 w);
void func_00161200(V24A0* f);
void func_00152D30(V24A0* f);
void func_00152D70(V24A0* f);
void func_001529E0(V24A0* f, s32 a, s32 b);
void func_00168A48(Buf_193318* b);

void func_001AA8F0(void* self);

void func_001AA958(void* self);

void func_001936A0(void* self, s32 v);

struct Rec_194278 { s32 f0; void* f4; s32 f8; s32 fC; s32 f10; };

extern void* D_00275710;
extern u8 D_00275B04[];
extern u8 D_00275F80[];

void func_00194D30(void* self, s32 a, s32 b);
void func_001EFFA0(void* obj, void* rec, s32 n);
void* func_0015A838(void* a, s32 b, s32 c, s32 d);
void func_001A4EF0(void* p, s32 mode);
void func_001F4408(void* a, s32 b);

void func_001936A0(T217D_6D0* self);
void func_00195928(void* self, s32 v);
void func_001AA998(void* self, s32 flag);

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
void func_00194D30(T217D_6D0* self, s32 a, s32 b);
s32 func_001FD7A0(f32 x);

struct Ent_195958 {
    u8 pad0[0xC];
    f32 fC;
    u8 pad1[0x1A5C - 0x10];
};

extern u8 D_00275BC0[];
extern u8 D_00247AD0[];
extern Ent_195958 D_002542D8[];

void func_001961C0(T217D_6D0* self);
void func_00194D30(T217D_6D0* self, s32 a, s32 b);
void func_00194278(T217D_6D0* self, s32 a, s32 b);
void func_001E9498(u8* a, void* b);
void func_001F4408(s32 a, s32 b);
void func_001F0428(u8* a, s32 b, s32 c);
void func_0018C178(MemoryCard* a, s32 b);
void func_0018B670(BackgroundJob* a, void* fn, MemoryCard* self);
s32 func_0018C638(MemoryCard* self);
s32 func_0018C1A8(MemoryCard* self);
s32 func_0018C250(MemoryCard* self);
s32 func_0018C770(MemoryCard* self);
s32 func_0018C568(MemoryCard* self);
void func_00160948(void);
void func_001936A0(T217D_6D0* self);
void* func_001925F0(void);
s32 func_001300E8(void* node, s32 kind);
void func_001B6598(void* ptr, s32* out);
void func_001D9338(void* p);
void func_001B6628(void* h, s32 arg);
void func_001B64D8(s32 a, s32 b);
s32 func_001602A0(void);
void func_00160578(s32 n);
void func_00194398(void);
void func_001A7F50(GameProgress* g);
void func_001C0760(s32 flag);
s32 func_001C0790(s32 flag);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

struct Row_1943E8 {
    void* f0;
    u8 pad4[0xC - 0x4];
    s32 fC;
    s32 f10;
    s32* items;
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

extern f32 D_00261868;
extern Ent_1943E8* D_0026998C;
struct Words6_264A58 { s32 v[6]; };
extern Words6_264A58 D_00264A58;
extern s32 D_00264A4C;
extern f32 D_0026A22C;
struct Pair_26A230 { f32 f0; f32 f4; };
extern Pair_26A230 D_0026A230;
extern f32 D_0026A700;
extern f32 D_0026A704;

s32 func_00160B28(GameProgress* g);
s32 func_001BE810(void);
s32 func_0011CE30(void);
s32 func_001BE980(void);
s32 func_0016EED0(PadRecord* p);
s32 func_0016EC98(PadRecord* p);
void func_0016EC20(PadRecord* p, s32 mask);
f32 func_0016F108(PadRecord* p, s32 idx);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_00194D30(T217D_6D0* self, s32 a, s32 b);
void func_00195958(T217D_6D0* self);
void func_001961C0(T217D_6D0* self);
void func_00194398(void);
s32 func_0018B770(BackgroundJob* p);
void func_0018B670(BackgroundJob* p, void* fn, void* arg);
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

enum Bits_1940E8 {
    BITS_1940E8_ZERO = 0
};

extern u8 D_00275BC0[];
extern u8* D_0027051C;

void func_001BED48(void);
void func_001BED70(void);
void func_001E96F8(void* self, s32 mode);
void func_00193EE8(T217D_6D0* self, s32 a, s32 b);
s32 func_0016E0F0(Bits_1940E8 bits);
void func_0016E118(Bits_1940E8 n);
void func_0016EC88(PadRecord* p);

// func_0015DB28 builds a text buffer and returns it (a constructor's `this`).

struct Rgba_194F80 { u8 r, g, b, a; };
struct Owner_194F80;
struct VEnt_194F80 { s16 delta; s16 idx; void (*fn)(void* self, Owner_194F80* o, Layout_137228* out, void* d); };
struct Hook_194F80 { u8 pad[0x4C]; VEnt_194F80* vt; };
struct Owner_194F80 { Hook_194F80* f0; u8 pad[0x14]; Rgba_194F80 f18; };
struct Menu_194F80 { char* title; f32 titleScale; f32 itemScale; s32 vertical; s32 count; s32* items; };

extern f32 D_00261858[];
extern s32 D_00275BEC;
extern f32 D_00262CEC;
extern u8 D_00260ED0[];
extern u8 D_00262280[];

f32 func_00205400(f32 x);
void func_00137228(Layout_137228* out, f32 x, f32 y);
void func_00137238(Layout_137228* out, f32 x, f32 y);
void func_00137248(Layout_137228* out, Quad4* value);
void func_00137260(Layout_137228* out, s32 flag);
void func_00137268(Layout_137228* out, s32 flag);
f32 func_001EA4B8(void* p, s32 zero, f32 a, f32 b, f32 c);
void func_0015C8B8(V24A2* font, f32 a, f32 b);
TextReader* func_0015DB28(TextReader* out, void* str, V24A2* font);
void func_0015E318(TextReader* buf, Layout_137228* out, s32 zero, void* data);
f32 func_0015E1B0(TextReader* buf, f32 w);
void func_0015C900(V24A2* font);
f32 func_0015DFF8(TextReader* buf);
char* func_00193598(s32 index);
void func_001AE3B8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, Rgba_194F80* c, s32 k);

struct Setup_194F80 { static void Do(Layout_137228* out, f32 x, f32 y, f32 w, f32 h, s32 color, s32 flag)
{
    func_00137228(out, x, y);
    func_00137238(out, w, h);
    Quad4 tmp;
    tmp.w[0] = color;
    func_00137248(out, &tmp);
    func_00137260(out, flag);
    func_00137268(out, 0);
} };

struct CallHook_194F80 { static void Do(Owner_194F80* o, Layout_137228* out, void* d)
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
        FillMemory(this, 0, 0x1C);
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
    { "Paused", 1.0f, 1.0f, 1, 8, g_pauseMenuItems },
    { "Game Over. Try again?", 1.0f, 1.0f, 0, 2, g_yesNoItems },
    { "Really Quit?", 1.0f, 1.0f, 0, 2, g_yesNoItems },
    { "There is no Memory Card (PS2) inserted in\nMemory Card Slot 1\n\nSly Cooper requires 49 KB of free space\n\nPlease insert a Memory Card (PS2) containing sufficient space or you will not be able to save your progress\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "The Memory Card (PS2) in Memory Card Slot 1 is unformatted\n\nIf you do not format it then you will not be able to save your progress\n\nDo you want to format?", 0.7f, 1.0f, 0, 2, g_yesNoItems },
    { "\nFormatting the Memory Card (PS2) in Memory Card Slot 1\n\nPlease do not turn off your system or remove the Memory Card (PS2)\n", 0.7f, 1.0f, 1, 0, 0 },
    { "An error occurred while formatting the Memory Card (PS2) in Memory Card Slot 1\n\nYou will not be able to save your progress\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "No Sly Cooper Save File on the Memory Card (PS2) inserted in Memory Card Slot 1\n\nSly Cooper requires 49 KB of free space\n\nIf you do not create a Sly Cooper Save File then you will not be able to save your progress\n\nDo you want to create a Sly Cooper Save File?", 0.7f, 1.0f, 0, 2, g_yesNoItems },
    { "\nCreating the Sly Cooper Save File on the Memory Card (PS2) in Memory Card Slot 1\n\nPlease do not turn off your system or remove the Memory Card (PS2)\n", 0.7f, 1.0f, 1, 0, 0 },
    { "An error occurred while creating the Sly Cooper Save File on the Memory Card (PS2) in Memory Card Slot 1\n\nYour progress is not being saved\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "The Memory Card (PS2) inserted in Memory Card Slot 1 does not have enough free space to create a Sly Cooper Save File\n\nSly Cooper requires 49 KB of free space\n\nPlease insert a Memory Card (PS2) containing sufficient space or you will not be able to save your progress\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "Save Game", 1.0f, 0.7f, 1, 4, D_00269D08 },
    { "\nSaving...\n\nPlease do not turn off your system or remove the Memory Card (PS2)\n", 0.7f, 1.0f, 1, 0, 0 },
    { "Game Saved", 1.0f, 1.0f, 1, 1, D_00269D00 },
    { "Do you want to overwrite this game?", 0.7f, 1.0f, 0, 2, g_yesNoItems },
    { "An error occurred while writing to the Sly Cooper Save File on the Memory Card (PS2) in Memory Card Slot 1\n\nYour progress is not being saved\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "New Game", 1.0f, 0.7f, 1, 4, D_00269D08 },
    { "Load Game", 1.0f, 0.7f, 1, 4, D_00269D08 },
    { "Do you want to erase this game?", 0.7f, 1.0f, 0, 2, g_yesNoItems },
    { "\nErasing...\n\nPlease do not turn off your system or remove the Memory Card (PS2)\n", 0.7f, 1.0f, 1, 0, 0 },
    { "When the following icon appears,\nyour progress is being saved\n\n^15&2a&.^.\n\nWhile this icon is on screen, please\ndo not turn off your system or remove\nthe Memory Card (PS2)\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "The Memory Card (PS2) in Memory Card Slot 1 was removed\n\nAuto-save has been disabled\n\nUse the save game option to manually save your game and re-enable auto-save\n", 0.7f, 1.0f, 1, 1, D_00269D00 },
    { "The disc was removed\n\nPlease insert the Sly Cooper disc to continue playing", 0.8f, 1.0f, 1, 0, 0 },
    { "Options", 1.0f, 1.0f, 1, 9, g_optionsMenuItems },
    { "&2T&. : Cancel\n&2+&. : Move\n&2X&. : Accept", 0.8f, 1.0f, 1, 0, 0 },
    { "Try again?", 1.0f, 1.0f, 0, 2, g_yesNoItems },
    { "Try again?", 1.0f, 1.0f, 0, 2, g_yesNoItems },
    { "CONGRATULATIONS!\n\nYou have beaten the\nMaster Thief Sprint!\n\nReturn to this level at any time\nto hear the Bonus Commentary!", 0.8f, 1.0f, 0, 1, D_00269D00 },
    { "TIME EXPIRED\n\nWould you like to retry\nthe Master Thief Sprint?\n\n", 0.8f, 1.0f, 0, 2, g_yesNoItems },
    { "CONGRATULATIONS!\n\nYou beat your best\nMaster Thief Sprint time!\n\nTry Again?", 0.8f, 1.0f, 0, 2, g_yesNoItems },
    { "You didn't beat your best\nMaster Thief Sprint time\n\nTry again?", 0.8f, 1.0f, 0, 2, g_yesNoItems },
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

S193210* func_00193210(S193210* self, U32P* s1, U32P* s2, U32P* s3, U32P* s4);
void func_00193270(S_193270* p);
void func_00193288(State_193288* self, s32 value);
void func_00193300(S_193300* p);
void func_00193318(Obj_193318* o);
void func_001935B0(GameProgress* self, char* dst);
s32 func_00193660(void);
void func_00193E58(T217D_6D0* self);
void func_00193EE8(T217D_6D0* self, s32 a, s32 b);
void func_001940E8(T217D_6D0* self, s32 mode);
void func_00194278(void* a0, s32 a1, s32 a2);
void func_00194398(void);
void func_001943E8(T217D_6D0* self);
void func_00194D30(T217D_6D0* self, s32 idx, s32 value);
void func_00194E60(T217D_6D0* self, s32 v);
void func_00194F00(T217D_6D0* self);
void func_00194F38(T217D_6D0* self);
void func_00194F80(T217D_6D0* self);
void func_00195928(T217D_6D0* self, s32 v);
void func_00195958(T217D_6D0* self);
void func_001961C0(T217D_6D0* self);

S193210* func_00193210(S193210* self, U32P* s1, U32P* s2, U32P* s3, U32P* s4)
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
		if (self->size == 0) { self->scaled = value << 1; self->size = value; SendDisplayResetPacket(self); }
		else if (self->value == value) self->repeat++;
		else self->repeat = 0;
		self->value = value;
		DrawLoadProgressBar(self);
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
    InitGifPacket(&buf.f);
    UsePacketBufferMemory(&buf.f, 0x40, &buf);
    BeginDmaTag(&buf.f);
    {
        u8 r = o->r;
        u8 g = o->g;
        u8 b = o->b;
        f32 y = TruncateFloat(412.909088f) * 1.1f;
        f32 z = (f32)(n2 + 10);
        WriteColoredSpritePacket(r, g, b, 255, &buf.f, 10.0f, y, z, TruncateFloat(412.909088f) * 1.1f + 6.6000004f);
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
        f32 y = TruncateFloat(412.909088f) * 1.1f;
        f32 z = (f32)(n1 + 10);
        WriteColoredSpritePacket(r, g, b, 255, &buf.f, x, y, z, TruncateFloat(412.909088f) * 1.1f + 6.6000004f);
    }
    EndGifPacket(&buf.f);
    AddDmaEndTag(&buf.f);
    CloseDmaTag(&buf.f);
    DetachPacketBuffer(&buf.f, 0, 0);
    SendPacketToBothBuffers(&buf);
}

char* func_00193598(s32 index)
{
    return g_menuChoiceLabels[index];
}

void func_001935B0(GameProgress* self, char* dst)
{
    s32 a = ComputeCompletionPercent(self);
    s32 b = GetEntryName((self->f19D8 << 8) | self->f19DC);
    s32 v = (s32)(self->fC * (1.0f / 60.0f));
    s32 t = v > 0 ? v : 1;
    FormatToString(dst, "%d%% - %s - %d:%02d", a, b, t / 60, t % 60);
}

s32 func_00193660(void)
{
    s32 r = FindFirstObjectById(g_currentWorld, 5, 0x42C, 0);
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

void func_00193E58(T217D_6D0* self)
{
    SetupScreenElementText(self);
    if (IsFontLoaded(2)) {
        self->frame = (V24A2**)&D_0026A210;
        *self->frame = GetFontById(2);
    }
    self->page = -1;
    self->stage = -1;
    for (u32 i = 0; i < 3; i++) {
        self->want[i] = -1;
    }
    self->fade = 1.0f;
}

void func_00193EE8(T217D_6D0* self, s32 a, s32 b)
{
    if (a == b) {
        return;
    }
    if (self->sound != 0) {
        StopStreamVoice();
        self->sound = 0;
    }
    if (a == 11) {
        goto call;
    }
    if (a > 10) {
        if (a < 18) {
            if (a > 15) {
            call:
                g_buttonHintElement.vt->m15(&g_buttonHintElement);
            }
        }
    }
    switch (b) {
    case 11:
    case 16:
    case 17: {
        T217D_330* o = &g_buttonHintElement;
        SetScreenElementHoldTime(o, 0.0f);
        SetScreenElementScale(o, 0.6f);
        break;
    }
    case 24: {
        D_0026A700 = D_0026A708 = (f32)(u32)((Dev_193EE8*)&D_00262490)->a.x;
        D_0026A704 = D_0026A70C = (f32)((u32)(((Dev_193EE8*)&D_00262490)->q18 >> 12) & 0x7FF);
        break;
    }
    case -1:
        D_0026C6C8.vt->m15(&D_0026C6C8);
        D_0026C948.vt->m15(&D_0026C948);
        D_0026CBC8.vt->m15(&D_0026CBC8);
        D_0026CE48.vt->m15(&D_0026CE48);
        D_00274118.vt->m15(&D_00274118);
        break;
    }
}

void func_001940E8(T217D_6D0* self, s32 mode) {
    if (self->open == mode) return;
    if (mode != 0) {
        s32 key = (g_saveData->f19D8 << 8) | g_saveData->f19DC;
        if (key == 0x308) {
            func_001BED48();
            SetElementStackState(g_elementStack, 5);
        } else if (D_0027051C != 0) {
            SetElementStackState(g_elementStack, 5);
        } else {
            u8* base = g_elementStack;
            if (((s32*)base)[1] == 3) {
                SetElementStackState(base, 4);
            } else {
                SetElementStackState(base, 5);
            }
        }
        ChangePauseMenuPage(self, -1, self->page);
        self->vt->m14(self);
        SetPadSelectFlags((Bits_1940E8)1);
        ResetPadStepRepeat(&g_padRecord);
    } else {
        s32 key = (g_saveData->f19D8 << 8) | g_saveData->f19DC;
        if (key == 0x308) {
            func_001BED70();
            SetElementStackState(g_elementStack, 3);
        } else if (D_0027051C != 0) {
            SetElementStackState(g_elementStack, 3);
        } else if (self->page != 0) {
            SetElementStackState(g_elementStack, 3);
        } else {
            SetElementStackState(g_elementStack, 6);
        }
        ChangePauseMenuPage(self, self->page, -1);
        self->vt->m15(self);
        ClearPadSelectFlags((Bits_1940E8)1);
    }
    self->open = mode;
}

void func_00194278(void* a0, s32 a1, s32 a2)
{
    SetPauseMenuLayerPage(a0, 0, -1);
    GameProgress* g = g_saveData;
    s32 key = (g->f19D8 << 8) | g->f19DC;
    if (key == 0x106) {
        if (a1 != 0) {
            Rec_194278 r;
            r.f0 = 1;
            r.f4 = D_00275B04;
            r.f8 = -1;
            r.fC = -1;
            r.f10 = 0;
            StartScreenFade(g_screenFade, &r, a2);
        } else {
            void* p = FindFirstObjectByIdGathered(g_currentWorld, 5, 0x5F, 0);
            SetPairControllerState(p, 6);
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
        StartScreenFade(g_screenFade, &r, a2);
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
    StartScreenFade(g_screenFade, &args, 0);
}

void func_001943E8(T217D_6D0* self)
{
    GameProgress* g = g_saveData;
    Row_1943E8* row = &((Row_1943E8*)&g_pauseMenuPages)[self->page];
    s32 on;
    s32 n;
    PadRecord* pad;

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
        on = self->page == 0;
        break;
    }
    if (on) {
        D_0026C6C8.vt->m14(&D_0026C6C8);
        D_0026C948.vt->m14(&D_0026C948);
        D_0026CBC8.vt->m14(&D_0026CBC8);
        D_0026CE48.vt->m14(&D_0026CE48);
    } else {
        D_0026C6C8.vt->m15(&D_0026C6C8);
        D_0026C948.vt->m15(&D_0026C948);
        D_0026CBC8.vt->m15(&D_0026CBC8);
        D_0026CE48.vt->m15(&D_0026CE48);
    }
    switch (self->page) {
    case 0:
    case 11:
    case 17:
        D_00274118.own = ComputeCompletionPercent(g_saveData);
        D_00274118.target = &D_00274118.own;
        D_00274118.vt->m14(&D_00274118);
        break;
    default:
        D_00274118.vt->m15(&D_00274118);
        break;
    }
    if (self->sound != 0) {
        if (func_001BE810() != 0) {
            PollIopCommands();
        }
        self->sound = HasStreamVoice();
    }
    s32 ready = 1;
    if (self->queued != 0 || self->mode != 2 || !(0.1f < g_elapsedTime - self->since)) {
        ready = 0;
    }
    pad = &g_padRecord;
    if (row->f10 == 0) {
        n = 0;
    } else if (row->fC != 0) {
        n = GetPadVerticalStep(pad);
    } else {
        n = GetPadHorizontalStep(pad);
    }
    if (n > 0) {
        self->cursor = (self->cursor + 1) % row->f10;
        StartSoundEffect(0x79, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    if (n < 0) {
        self->cursor = (self->cursor + row->f10 - 1) % row->f10;
        StartSoundEffect(0x79, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    if (!ready) {
        return;
    }
    if (pad->flags & 0x810) {
        ClearPadPressedBits(&g_padRecord, 0x810);
        CancelPauseMenuPage(self);
        return;
    }
    if (pad->flags & 0x80) {
        ClearPadPressedBits(&g_padRecord, 0x80);
        if (self->page == 11 || self->page == 16) {
            Ent_1943E8* e = &((Ent_1943E8*)&D_002542D8)[row->items[self->cursor]];
            if (e->fC != 0.0f) {
                D_0026998C = e;
                SetPauseMenuLayerPage(self, 1, 0x12);
            }
        }
        return;
    }
    if (pad->flags & 0x40) {
        ClearPadPressedBits(&g_padRecord, 0x40);
        ActivatePauseMenuSelection(self);
        return;
    }
    switch (self->page) {
    case 24: {
        f32 a = GetPadButtonAnalog(pad, 0);
        f32 dx = a - GetPadButtonAnalog(pad, 1);
        f32 b = GetPadButtonAnalog(pad, 3);
        f32 dy = b - GetPadButtonAnalog(pad, 2);
        f32 v;
        if (dx == 0.0f && dy == 0.0f) {
            return;
        }
        D_0026A700 = Clamp_1943E8::Of(D_0026A700 + dx * D_0026A22C, 424.0f, 848.0f);
        v = Clamp_1943E8::Of(D_0026A704 + dy * D_0026A230.f0, 10.0f, 90.0f);
        D_0026A704 = v;
        {
            Gs_1943E8* gs = ((Gs_1943E8*)&D_00262490);
            s32 h = ConvertFloatToU32(D_0026A700);
            Reg_1943E8 ra = gs->f40;
            RegA_1943E8 rb = gs->f18;
            ra.lo = h;
            rb.lo = h;
            gs->f40 = ra;
            gs->f18 = rb;
            s32 w = ConvertFloatToU32(v);
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
            CancelPauseMenuPage(self);
            return;
        } else {
            s32 id = row->items[self->cursor];
            if ((u32)(id - 10) < 3) {
                Ent_1943E8* e = &((Ent_1943E8*)&D_002542D8)[id];
                if (self->page == 16) {
                    if (e->fC != 0.0f) {
                        g_buttonHintElement.vt->m08(&g_buttonHintElement, "&2S&. : Erase Game");
                    } else {
                        g_buttonHintElement.vt->m08(&g_buttonHintElement, "&2X&. : New Game");
                    }
                } else if (self->page == 17) {
                    if (e->fC != 0.0f) {
                        g_buttonHintElement.vt->m08(&g_buttonHintElement, "&2X&. : Load Game");
                    } else {
                        g_buttonHintElement.vt->m08(&g_buttonHintElement, "&2X&. : New Game");
                    }
                } else {
                    if (e->fC != 0.0f) {
                        g_buttonHintElement.vt->m08(&g_buttonHintElement, "&2X&. : Overwrite Game\n&2S&. : Erase Game");
                    } else {
                        g_buttonHintElement.vt->m08(&g_buttonHintElement, "&2X&. : Save Game");
                    }
                }
                g_buttonHintElement.vt->m14(&g_buttonHintElement);
            } else {
                g_buttonHintElement.vt->m15(&g_buttonHintElement);
            }
        }
        break;
    case 18:
        if (D_00264A58.v[0] != 1) {
            CancelPauseMenuPage(self);
        }
        break;
    case 20: {
        Item_1943E8* it;
        if (D_00264A58.v[0] != 1) {
            CancelPauseMenuPage(self);
        }
        it = FindSubstring(row->f0, "&2");
        if (it != 0) {
            it->f2 = GetCyclingGlyph();
        }
        break;
    }
    case 3:
    case 4:
    case 7:
    case 10:
    case 32:
        if (D_00264A4C == 5) {
            SetPauseMenuLayerPage(&g_pauseMenuElement, 1, -1);
        }
        break;
    case 5: {
        BackgroundJob* p = &g_backgroundJob;
        if (IsBackgroundJobRunning(p) == 0) {
            if (p->result == 0) {
                StartBackgroundJob(p, (void*)(void (*)(MemoryCard*))CreateMemoryCardSaveFiles, ((u8*)&g_memoryCard));
                SetPauseMenuLayerPage(self, 1, 8);
            } else {
                SetPauseMenuLayerPage(self, 1, 6);
            }
        }
        break;
    }
    case 8: {
        BackgroundJob* p = &g_backgroundJob;
        if (IsBackgroundJobRunning(p) == 0) {
            if (p->result == 0) {
                SetPauseMenuLayerPage(self, 1, -1);
            } else {
                SetPauseMenuLayerPage(self, 1, 9);
            }
        }
        break;
    }
    case 12: {
        BackgroundJob* p = &g_backgroundJob;
        if (IsBackgroundJobRunning(p) == 0) {
            if (p->result == 0) {
                SetPauseMenuLayerPage(self, 1, -1);
                if (self->stage == 2) {
                    StartPauseMenuExitFade();
                }
            } else {
                SetPauseMenuLayerPage(self, 0, 0x17);
                SetPauseMenuLayerPage(self, 1, 0xF);
            }
        }
        break;
    }
    case 19: {
        BackgroundJob* p = &g_backgroundJob;
        if (IsBackgroundJobRunning(p) == 0) {
            D_0026998C = 0;
            if (p->result == 0) {
                SetPauseMenuLayerPage(self, 1, -1);
            } else {
                SetPauseMenuLayerPage(self, 0, 0x17);
                SetPauseMenuLayerPage(self, 1, 0xF);
            }
        }
        break;
    }
    }
}

void func_00194D30(T217D_6D0* self, s32 idx, s32 value)
{
    s32 s1;
    s32 s2;
    u32 i;
    s32* p;

    s2 = value;
    self->want[idx] = s2;
    p = self->want;
    for (i = 0; i < 3; i++) {
        if (*p != -1) {
            s2 = *p;
        }
        p++;
    }
    if (self->queued != 0) {
        s1 = self->queuedPage;
    } else {
        s1 = self->page;
    }
    ChangePauseMenuPage(self, s1, s2);
    if (s1 != s2) {
        if (self->mode == 0) {
            SetPauseMenuPage(self, s2);
        } else if (self->mode >= 0) {
          if (self->mode < 4) {
            if (s2 == -1) {
                self->queued = 0;
                self->queuedPage = s2;
            } else {
                self->queuedPage = s2;
                self->queued = 1;
                self->vt->m16(self, 3);
            }
          }
        }
    }
    if (s2 == -1) {
        if (self->open != 0) {
            PopStackElement(g_elementStack);
        }
    } else {
        if (self->open == 0) {
            PushStackElement(g_elementStack, self);
        }
    }
}

void func_00194E60(T217D_6D0* self, s32 v)
{
    s32 flag = v;

    if (self->mode == v) return;
    if (self->mode == 0 && self->page == 0) {
        func_001936A0(self);
    }
    if (v == 0) {
        if (self->queued != 0) {
            SetPauseMenuPage(self, self->queuedPage);
            flag = 1;
            self->queued = 0;
            self->queuedPage = -1;
        } else {
            if (self->page == 0) {
                func_001936A0(self);
            }
        }
    }
    SetScreenElementMode(self, flag);
}

void func_00194F00(T217D_6D0* self)
{
    if (self->mode == 3 && self->queued != 0) return;
    ShowScreenElement(self);
}

void func_00194F38(T217D_6D0* self)
{
    if (self->mode == 3 && self->queued != 0) {
        self->queued = 0;
        self->queuedPage = -1;
        return;
    }
    HideScreenElement(self);
}

void func_00194F80(T217D_6D0* self)
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

    if (self->mode == 0) {
        return;
    }
    {
        f32 ww = self->w;
        f32 hh = self->h;
        f32 s = self->blend;
        f32 x0 = self->shownX + ww * 0.5f; 
        f32 y0 = self->shownY + hh * 0.5f; 
        w = ww * s; 
        cx = self->shownX * s + x0 * (1.0f - s); 
        cy = self->shownY * s + y0 * (1.0f - s); 
        h = hh * s; 
    }
    pulse = Sine(g_gameClock[4] * 10.0f) * 0.5f + 0.5f;
    menu = &((Menu_194F80*)&g_pauseMenuPages)[self->page];
    fade = 1.0f;
    if (self->page == 0 && D_00275BEC == 2) {
        fade = 1.0f - D_00262CEC;
    }
    self->fade = ApproachValueWithRamp(g_fadeRampProfile, 0, self->fade, fade, g_gameClock[5]);
    alpha = (u8)(s32)(self->fade * 255.0f);
    if (((Owner_194F80*)self->frame) != 0) {
        Layout_137228 out;
        s32 backColor = 0xFF808080;
        func_00137228(&out, cx, cy);
        func_00137238(&out, w, h);
        {
            Quad4 tmp;
            tmp.w[0] = backColor;
            func_00137248(&out, &tmp);
        }
        func_00137260(&out, 0);
        func_00137268(&out, 0);
        Rgba_194F80 saved = ((Owner_194F80*)self->frame)->f18;
        {
            Rgba_194F80 t = saved;
            t.a = alpha;
            ((Owner_194F80*)self->frame)->f18 = t;
        }
        if (menu->count == 0) {
            Owner_194F80* cur = ((Owner_194F80*)self->frame);
            Rgba_194F80 gray;
            gray.r = 0x6F; 
            gray.g = 0x6F; 
            gray.b = 0x6F; 
            gray.a = alpha; 
            Rgba_194F80 res;
            Lerp_194F80::Do(&res, cur->f18, gray, pulse * pulse);
            cur->f18 = res;
        }
        CallHook_194F80::Do(((Owner_194F80*)self->frame), &out, g_gsPacketWriter);
        ((Owner_194F80*)self->frame)->f18 = saved;
    }
    if (menu->title != 0) {
        TextReader buf;
        Layout_137228 out;
        Rgba_194F80 c;
        f32 sc = menu->titleScale * self->blend;
        PushFontScale(self->font, sc, sc);
        InitTextReader(&buf, menu->title, self->font);
        c.r = 0x7F;
        c.g = 0x7F;
        c.b = 0x7F;
        c.a = alpha;
        Setup_194F80::Do(&out, cx, cy, w, h, *(s32*)&c, 1);
        DrawAlignedText(&buf, &out, 0, g_gsPacketWriter);
        cy += MeasureTextHeight(&buf, 500.0f);
        PopFontScale(self->font);
    }
    base = cy + -1.0f;
    {
        f32 sc = menu->itemScale * self->blend;
        PushFontScale(self->font, sc, sc);
    }
    lineH = (f32)self->font->height * self->font->sy;
    if (menu->vertical == 0) {
        f32 total = 0.0f;
        for (s32 k = 0; k < menu->count; k++) {
            TextReader buf;
            if (k != 0) {
                total += (f32)self->font->advance * self->font->sx + (f32)self->font->advance * self->font->sx;
            }
            void* str = GetMenuChoiceLabel(menu->items[k]);
            InitTextReader(&buf, str, self->font);
            total += SumTextWidth(&buf);
        }
        x = cx + (w - total) * 0.5f;
    }
    for (i = 0; i < menu->count; i++) {
        Rgba_194F80 col;
        f32 grow;
        f32 width;
        void* str;
        f32 th;
        if (i == self->cursor) {
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
        TextReader buf;
        str = GetMenuChoiceLabel(menu->items[i]);
        InitTextReader(&buf, str, self->font);
        width = SumTextWidth(&buf);
        if (menu->vertical != 0) {
            x = cx + (w - width) * 0.5f;
        }
        {
            f32 sc = menu->itemScale * self->blend * grow;
            PushFontScale(self->font, sc, sc);
        }
        InitTextReader(&buf, str, self->font);
        f32 width2 = SumTextWidth(&buf);
        th = (f32)self->font->height * self->font->sy;
        Layout_137228 out;
        Setup_194F80::Do(&out, x + (width - width2) * 0.5f, cy + (lineH - th) * 0.5f, w, th, *(s32*)&col, 0);
        DrawAlignedText(&buf, &out, 0, g_gsPacketWriter);
        PopFontScale(self->font);
        if (menu->vertical != 0) {
            cy += (f32)self->font->height * self->font->sy;
        } else {
            x += width + ((f32)self->font->advance * self->font->sx + (f32)self->font->advance * self->font->sx);
        }
    }
    PopFontScale(self->font);
    if (menu->title != 0 && menu->count != 0) {
        Rgba_194F80 c = *(Rgba_194F80*)&D_0026A210.f18;
        c.a = alpha;
        s32 y = (s32)((base * 0.45454547f + 1936.0f) * 16.0f);
        DrawLineSegment((s32)((cx + 1728.0f) * 16.0f), y, 0, (s32)((cx + w + 1728.0f) * 16.0f), y, 0, &c, 0);
    }
}

void func_00195928(T217D_6D0* self, s32 v)
{
    if (self->page != v) {
        self->page = v;
        if (v != -1) func_001936A0(self, v);
    }
}

void func_00195958(T217D_6D0* self)
{
    s32 sel = g_pauseMenuPages[self->page].items ? g_pauseMenuPages[self->page].items[self->cursor] : -1;
    if (sel == 0x11) {
        CancelPauseMenuPage(self);
        return;
    }
    switch (self->page) {
    case 0:
        switch (sel) {
        case 3:
            SetPauseMenuLayerPage(self, 0, -1);
            return;
        case 4: {
            T217D_0F0* s = &g_mapScreenList;
            if (s->current != 0) {
                SetPauseMenuLayerPage(self, 0, -1);
                PushStackElement(g_elementStack, s);
                return;
            }
            StartSoundEffect(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            return;
        }
        case 18: {
            s32 v;
            void* s2 = (void*)func_00193660();
            void* s0 = GetActiveSwitchedCollider();
            if (s2 != 0 && s0 != 0 && IsObjectOfKind(s0, 0x19) != 0) {
                func_001B6598(s2, &v);
                if (v < 0x431) {
                    if (v >= 0x42F) {
                        RecordPathFollowerProgress(s0);
                        TeleportStateWalker(s2, 0x42E);
                    }
                }
            }
            SetPauseMenuLayerPage(self, 0, -1);
            return;
        }
        case 19:
        case 20:
            ExitLevelFromPauseMenu(self, 1, 1);
            return;
        case 21:
            SetPauseMenuLayerPage(self, 0, -1);
            func_001F4408(1, 2);
            return;
        case 22:
            SetPauseMenuLayerPage(self, 0, -1);
            StartObjectFade(D_00247AD0, -1, 2);
            return;
        case 9:
            SetPauseMenuLayerPage(self, 0, 2);
            return;
        case 5:
            SetPauseMenuLayerPage(self, 0, 0x17);
            return;
        case 23:
            SetPauseMenuLayerPage(self, 0, 0x1F);
            return;
        }
        return;
    case 23:
        switch (sel) {
        case 6:
            SetMemoryCardDisplayMode(&g_memoryCard, 1);
            SetPauseMenuLayerPage(self, 0, 0x10);
            return;
        case 7:
            SetMemoryCardDisplayMode(&g_memoryCard, 1);
            SetPauseMenuLayerPage(self, 0, 0x11);
            return;
        case 8:
            SetMemoryCardDisplayMode(&g_memoryCard, 1);
            SetPauseMenuLayerPage(self, 0, 0xB);
            return;
        case 13:
            TogglePadPatternSetting(g_saveData);
            {
                s32 keep;
                keep = self->cursor;
                func_001936A0(self);
                self->cursor = keep;
            }
            return;
        case 15: {
            GameProgress* g = g_saveData;
            g->u19EC ^= 0x80;
            func_001C0760(g->u19EC & 0x80);
            {
                s32 keep;
                keep = self->cursor;
                func_001936A0(self);
                self->cursor = keep;
            }
            return;
        }
        case 16: {
            GameProgress* g = g_saveData;
            g->u19EC ^= 0x40;
            func_001C0790(g->u19EC & 0x40);
            {
                s32 keep;
                keep = self->cursor;
                func_001936A0(self);
                self->cursor = keep;
            }
            return;
        }
        case 14:
            SetPauseMenuLayerPage(self, 0, 0x18);
            return;
        case 23:
            SetPauseMenuLayerPage(self, 0, 0x1F);
            return;
        }
        return;
    case 27:
        if ((ComputeCompletionMask() & 8) != 0) {
            FadeOutAndQueueMovie(8);
            return;
        }
        ExitLevelFromPauseMenu(self, 0, 2);
        return;
    case 1:
    case 26:
    case 28:
    case 29:
    case 30:
        ExitLevelFromPauseMenu(self, (u32)sel < 1, 1);
        return;
    case 25: {
        s32 a = self->f280;
        self->f280 = 0;
        SetStateWalkerTarget(a, sel == 0 ? 0x434 : 0x435);
        SetPauseMenuLayerPage(self, 0, -1);
        return;
    }
    case 2:
        if (sel == 0) {
            MemoryCard* b = &g_memoryCard;
            if (b->f4F44 != 0) {
                self->stage = 2;
                if ((g_saveData->u19EC & 0x100) == 0) {
                    SetPauseMenuLayerPage(self, 1, 0x14);
                } else {
                    SetPauseMenuLayerPage(self, 1, 0xC);
                    StartBackgroundJob(&g_backgroundJob, (void*)SaveGameToMemoryCardSlot, b);
                }
            } else {
                StartPauseMenuExitFade();
            }
            SetPauseMenuLayerPage(self, 0, -1);
            return;
        }
        SetPauseMenuLayerPage(self, 0, -1);
        return;
    case 31:
        switch (sel) {
        case 0x18: {
            g_saveData->u19EC ^= 0x200;
            s32 keep = self->cursor;
            func_001936A0(self);
            self->cursor = keep;
            return;
        }
        case 0x19: {
            g_saveData->u19EC ^= 0x400;
            s32 keep = self->cursor;
            func_001936A0(self);
            self->cursor = keep;
            return;
        }
        case 0x1A: {
            g_saveData->u19EC ^= 0x800;
            s32 keep = self->cursor;
            func_001936A0(self);
            self->cursor = keep;
            return;
        }
        }
        return;
    case 14:
        if (sel == 0) {
            goto c6030;
        }
        SetPauseMenuLayerPage(self, 1, -1);
        return;
    case 4:
        if (sel == 0) {
            StartBackgroundJob(&g_backgroundJob, (void*)func_0018C1A8, &g_memoryCard);
            SetPauseMenuLayerPage(self, 1, 5);
            return;
        }
        goto c5EC0;
    case 7:
        if (sel == 0) {
            StartBackgroundJob(&g_backgroundJob, (void*)CreateMemoryCardSaveFiles, &g_memoryCard);
            SetPauseMenuLayerPage(self, 1, 8);
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
        SetPauseMenuLayerPage(self, 1, -1);
        SetMemoryCardDisplayMode(&g_memoryCard, 2);
        v = self->want[0];
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
        SetPauseMenuLayerPage(self, 0, 0x17);
        return;
    case 16: {
        Ent_195958* e = &D_002542D8[sel];
        if (e->fC == 0.0f) {
            SetPauseMenuLayerPage(self, 0, -1);
            g_memoryCard.f4F44 = e;
            ApplyMemoryCardImage(&g_memoryCard);
            ResumeAtSavedLevel();
            return;
        }
        StartSoundEffect(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    case 17:
        SetPauseMenuLayerPage(self, 0, -1);
        g_memoryCard.f4F44 = &D_002542D8[sel];
        ApplyMemoryCardImage(&g_memoryCard);
        ResumeAtSavedLevel();
        return;
    case 11: {
        Ent_195958* e;
        u32 p;
        p = sel * sizeof(Ent_195958);
        p += (u32)D_002542D8;
        e = (Ent_195958*)p;
        g_memoryCard.f4F4C = e;
        if (e->fC == 0.0f) {
        c6030:
            MemoryCard* b;
            b = &g_memoryCard;
            b->f4F44 = b->f4F4C;
            self->stage = 0xB;
            if ((g_saveData->u19EC & 0x100) == 0) {
                SetPauseMenuLayerPage(self, 1, 0x14);
            } else {
                SetPauseMenuLayerPage(self, 1, 0xC);
                StartBackgroundJob(&g_backgroundJob, (void*)SaveGameToMemoryCardSlot, b);
            }
            SetPauseMenuLayerPage(self, 0, -1);
            return;
        }
        SetPauseMenuLayerPage(self, 1, 0xE);
        return;
    }
    case 18:
        if (sel == 0) {
            StartBackgroundJob(&g_backgroundJob, (void*)WriteSelectedMemoryCardSlot, &g_memoryCard);
            SetPauseMenuLayerPage(self, 1, 0x13);
            return;
        }
        SetPauseMenuLayerPage(self, 1, -1);
        return;
    case 13:
        SetPauseMenuLayerPage(self, 1, -1);
        return;
    case 20: {
        g_saveData->u19EC |= 0x100;
        s32 v = self->stage;
        switch (v) {
        case 2:
        case 0xB:
            SetPauseMenuLayerPage(self, 1, 0xC);
            break;
        case -1:
            SetPauseMenuLayerPage(self, 1, -1);
            D_00273EB0.vt->m14(&D_00273EB0);
            break;
        }
        StartBackgroundJob(&g_backgroundJob, (void*)SaveGameToMemoryCardSlot, &g_memoryCard);
        return;
    }
    }
}

void func_001961C0(T217D_6D0* self)
{
    switch (self->page) {
    case 0:
        SetPauseMenuLayerPage(self, 0, -1);
        break;
    case 23:
        if ((u32)(D_00275BF0 - 1) < 2) {
            SetPauseMenuLayerPage(self, 0, -1);
            break;
        }
        SetPauseMenuLayerPage(self, 0, 0);
        break;
    case 24: {
        Gs_1961C0* g = &D_00262490;
        s32 v = ConvertFloatToU32(D_0026A708);
        Reg_1961C0 a = g->f40;
        RegA_1961C0 b = g->f18;
        a.lo = v;
        b.lo = v;
        g->f40 = a;
        g->f18 = b;
        s32 w = ConvertFloatToU32(D_0026A70C);
        a.mid = w;
        b.mid = w;
        g->f40 = a;
        g->f18 = b;
        SetPauseMenuLayerPage(self, 0, 0x17);
        break;
    }
    case 2:
        SetPauseMenuLayerPage(self, 0, 0);
        break;
    case 13:
        SetPauseMenuLayerPage(self, 1, -1);
        break;
    case 11:
    case 16:
    case 17:
    case 31:
        SetPauseMenuLayerPage(self, 0, 0x17);
        break;
    case 14:
    case 18:
        SetPauseMenuLayerPage(self, 1, -1);
        break;
    }
}

// The style above is built by the static initialiser GCC writes here (func_00196330), and its
// _GLOBAL_$I$ (func_001963B8) follows the 16 bytes the linker left of two layout setters this
// file wrote out after it (tools/compile.py moves the block there).
LINKER_REMNANT_AFTER_INIT(func_001963A8);
