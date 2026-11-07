// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x16F608 to 0x1793C0: the player, class 0x07 (struct Player in
// include/switched_collider.h), its methods, its state changes and its target choice. Its name
// is ours, after the class.
#include "common.h"
#include "globals.h"
#include "switched_collider.h"
#include "node_query.h"
#include "c4a.h"
#include "countdown_collider.h"
#include "entry_queue.h"
#include "object_link.h"
#include "message_body.h"
#include "object_event.h"
#include "shapes.h"
#include "screen_element.h"
#include "base_object.h"
#include "placed_object.h"
#include "world.h"
#include "v24a2.h"
#include "level_entry.h"
#include "threshold_range.h"
#include "g261ef0.h"
#include "render_frame.h"
#include "background_job.h"
#include "group_marker.h"
#include "game_progress.h"
#include "bump_allocator.h"
#include "camera.h"
#include "asm_func.h"

extern f32 D_00261860[];
extern f32 D_0026185C[];

struct Obj_2639B8 { s32 f0; u8 pad04[4]; };
struct Params_2638A0 { f32 f0; f32 f4; f32 f8; f32 fC; s32 f10; s32 f14; };

// size: pointer, word accesses only
Player* D_00262E10 = 0;
f32 D_00262E14 = 455.0f;
f32 D_00262E18 = 0.699999988f;
f32 D_00262E1C = 0.600000024f;
f32 D_00262E20 = 0.699999988f;
f32 D_00262E24 = 0.600000024f;
f32 D_00262E28 = 1000.0f;
f32 D_00262E2C = 850.0f;
f32 D_00262E30 = 50.0f;

// NEAR: frame, saves, the vtable call and the branch tree match; the 0xD path loads its two floats into $f1/$f0 where retail uses $f0/$f1, so the shared store tail differs

struct Sub_170410 { u8 pad0[0x40]; s32 f40; };
typedef s32 (*VFn_170410)(Player* self, void* out);
struct Out_170410 { u8 pad0[0x94]; f32 f94; f32 f98; };

f32 D_00262E34 = 0.8f;
f32 D_00262E38 = 0.5f;
f32 D_00262E3C = 0.25f;

ObjectLink D_00262E40[151] = {
    {0x0, 0x145, 0x1188},
    {0x0, 0x82, 0x724},
    {0x0, 0x83, 0x774},
    {0x2, 0x84, 0x7C4},
    {0x2, 0x85, 0x814},
    {0x2, 0x86, 0x864},
    {0x2, 0x87, 0x8B4},
    {0x0, 0x92, 0x914},
    {0x0, 0x93, 0x934},
    {0x0, 0x94, 0x954},
    {0x0, 0x95, 0x974},
    {0x0, 0x96, 0x994},
    {0x0, 0x97, 0x9B4},
    {0x0, 0x98, 0x9D4},
    {0x0, 0x99, 0x9F4},
    {0x0, 0x9F, 0xA24},
    {0x0, 0xA0, 0xA44},
    {0x0, 0xA1, 0xA64},
    {0x0, 0xA2, 0xA84},
    {0x0, 0xA3, 0xAA4},
    {0x0, 0xA4, 0xAC4},
    {0x0, 0xA5, 0xAE4},
    {0x0, 0xA6, 0xB04},
    {0x0, 0xA7, 0xB24},
    {0x0, 0xA9, 0xB28},
    {0x0, 0xA8, 0xB2C},
    {0x0, 0xAA, 0xB34},
    {0x0, 0xAB, 0xB54},
    {0x0, 0xAC, 0xB74},
    {0x0, 0xAD, 0xB94},
    {0x0, 0xAE, 0xBB4},
    {0x0, 0xAF, 0xBD4},
    {0x0, 0xB0, 0xBF4},
    {0x0, 0xB1, 0xC14},
    {0x0, 0xB2, 0xC34},
    {0x0, 0xB4, 0xC38},
    {0x0, 0xB3, 0xC3C},
    {0x0, 0xB5, 0xC44},
    {0x0, 0xB6, 0xC94},
    {0x2, 0xB7, 0xCE4},
    {0x2, 0xB8, 0xD34},
    {0x2, 0xB9, 0xD84},
    {0x2, 0xBA, 0xDD4},
    {0x0, 0xBB, 0xE24},
    {0x0, 0xBC, 0xE28},
    {0x0, 0xBD, 0xE2C},
    {0x2, 0xBE, 0xE34},
    {0x2, 0xBF, 0xE84},
    {0x2, 0xC0, 0xED4},
    {0x2, 0xC1, 0xF24},
    {0x2, 0xC2, 0xF74},
    {0x2, 0xC3, 0xFC4},
    {0x2, 0xC4, 0x1014},
    {0x2, 0xDD, 0x1018},
    {0x2, 0xDE, 0x101C},
    {0x0, 0x8C, 0x1020},
    {0x0, 0x8D, 0x1024},
    {0x0, 0x8E, 0x1028},
    {0x0, 0x90, 0x1030},
    {0x0, 0x91, 0x1034},
    {0x0, 0x157, 0x2364},
    {0x0, 0x158, 0x2370},
    {0x0, 0x159, 0x237C},
    {0x0, 0x8B, 0x1038},
    {0x2, 0x9E, 0x1060},
    {0x0, 0x9A, 0x1064},
    {0x0, 0x9D, 0x1068},
    {0x0, 0x9B, 0x1040},
    {0x0, 0x9C, 0x1050},
    {0x0, 0x7D, 0x21C4},
    {0x0, 0xF3, 0x2544},
    {0x0, 0xF7, 0x2550},
    {0x0, 0xF5, 0x2560},
    {0x0, 0xF9, 0x256C},
    {0x2, 0xFB, 0x257C},
    {0x2, 0xFF, 0x2588},
    {0x2, 0xFD, 0x2598},
    {0x2, 0x101, 0x25A4},
    {0x2, 0x103, 0x25B0},
    {0x2, 0x104, 0x25B4},
    {0x0, 0x105, 0x25B8},
    {0x0, 0x107, 0x25C0},
    {0x0, 0x1B8, 0x25C8},
    {0x2, 0x106, 0x25BC},
    {0x2, 0x108, 0x25C4},
    {0x2, 0x11A, 0x25D4},
    {0x0, 0x64, 0x1390},
    {0x2, 0x65, 0x1394},
    {0x2, 0x66, 0x1398},
    {0x2, 0x67, 0x13AC},
    {0x2, 0x68, 0x13B0},
    {0x2, 0x69, 0x13D4},
    {0x2, 0x6A, 0x13D8},
    {0x2, 0x6B, 0x13DC},
    {0x2, 0x6C, 0x13E0},
    {0x2, 0x6D, 0x13EC},
    {0x2, 0x6E, 0x14A8},
    {0x2, 0x6F, 0x14AC},
    {0x2, 0x70, 0x14B0},
    {0x2, 0x71, 0x14B4},
    {0x2, 0x72, 0x14B8},
    {0x2, 0x73, 0x14BC},
    {0x2, 0x74, 0x14C0},
    {0x2, 0x75, 0x14C4},
    {0x2, 0x76, 0x14CC},
    {0x2, 0x78, 0x14D0},
    {0x2, 0x77, 0x14D4},
    {0x2, 0x79, 0x14D8},
    {0x2, 0x7A, 0x14DC},
    {0x2, 0x7B, 0x146C},
    {0x2, 0x7C, 0x13C4},
    {0x0, 0xE2, 0x112C},
    {0x0, 0xE3, 0x1130},
    {0x0, 0xE4, 0x1134},
    {0x0, 0xE5, 0x1138},
    {0x0, 0xE6, 0x113C},
    {0x0, 0xE7, 0x1140},
    {0x0, 0xE8, 0x1144},
    {0x0, 0xE9, 0x1148},
    {0x0, 0xEA, 0x1150},
    {0x0, 0xEC, 0x1154},
    {0x0, 0xEB, 0x1158},
    {0x0, 0xED, 0x115C},
    {0x0, 0xEE, 0x1160},
    {0x2, 0xEF, 0x110C},
    {0x2, 0xF1, 0x1110},
    {0x2, 0xF2, 0x1114},
    {0x2, 0x109, 0x25CC},
    {0x2, 0x10A, 0x25D0},
    {0x2, 0x172, 0x243C},
    {0x6, 0x51, 0x2490},
    {0x6, 0x5A, 0x2494},
    {0x2, 0x17D, 0x26D8},
    {0x2, 0x17E, 0x26E0},
    {0x2, 0x17F, 0x26E8},
    {0x2, 0x180, 0x26F0},
    {0x2, 0x181, 0x26F8},
    {0x2, 0x182, 0x2700},
    {0x2, 0x183, 0x2708},
    {0x2, 0x184, 0x2710},
    {0x2, 0x185, 0x271C},
    {0x2, 0x186, 0x2720},
    {0x2, 0x18B, 0x272C},
    {0x20, 0x18D, 0x604},
    {0x2, 0x11B, 0x1070},
    {0x2, 0x11C, 0x107C},
    {0x2, 0x11D, 0x1088},
    {0x2, 0x153, 0x274C},
    {0x2, 0x154, 0x2754},
    {0x2, 0x155, 0x2760},
    {0x2, 0x156, 0x2764}
};
ObjectLink D_00263558[27] = {
    { 0x4, 0x60, 0x24F8 },
    { 0x2, 0x161, 0x588 },
    { 0x2, 0x162, 0x58C },
    { 0x2, 0x163, 0x590 },
    { 0x4, 0x5B, 0x2390 },
    { 0x2, 0x62, 0x2394 },
    { 0x2, 0x63, 0x2398 },
    { 0x4, 0x16F, 0x23D0 },
    { 0x4, 0x170, 0x23D4 },
    { 0x2, 0x173, 0x23D8 },
    { 0x4, 0x160, 0x584 },
    { 0x20, 0x164, 0x59C },
    { 0x20, 0x165, 0x5A0 },
    { 0x20, 0x166, 0x5A4 },
    { 0x22, 0x169, 0x267C },
    { 0x22, 0x7E, 0x25D8 },
    { 0x2, 0x7F, 0x25DC },
    { 0x2, 0x80, 0x25E0 },
    { 0x2, 0x1B9, 0x25E4 },
    { 0x22, 0x81, 0x25E8 },
    { 0x6, 0x50, 0x1504 },
    { 0x26, 0x18E, 0x1508 },
    { 0x26, 0x18F, 0x150C },
    { 0x26, 0x190, 0x1510 },
    { 0x26, 0x191, 0x1514 },
    { 0x22, 0x192, 0x1518 },
    { 0x26, 0x151, 0x2750 }
};
f32 D_002636A0[4] = { 0.0f, 0.5f, 0.5f, 0.5f };
f32 D_002636B0[4] = { 0.0f, 0.25f, 0.449999988f, 0.449999988f };
f32 D_002636C0[4] = { 0.0f, 0.25f, 0.449999988f, 0.449999988f };
f32 D_002636D0[4] = { 0.0f, 0.5f, 0.5f, 0.5f };
f32 D_002636E0[4] = { 0.0f, 0.5f, 0.5f, 0.5f };
f32 D_002636F0[4] = { 37.0f, 0.0f, 25.0f, 0.0f };
f32 D_00263700 = 1.29999995f;
f32 D_00263704 = 238689.0f;
f32 D_00263708 = 0.0f;
f32 D_0026370C = 0.0f;
f32 D_00263710[4] = { -1.5f, 0.00100000005f, 0.0f, 0.0f };

// Globals typed by worker dv02, from retail's bytes and their readers.
f32 D_00263720[4] = { 1.0f, -4.0f, 0.0f, 0.0f };
f32 D_00263730[4] = { 10.0f, 0.0f, 0.5f, 50.0f };
f32 D_00263740[4] = { 40.0f, 0.0f, 0.25f, 200.0f };
f32 D_00263750[4] = { 15.0f, 0.0f, 0.25f, 100.0f };
f32 D_00263760[4] = { -0.200000003f, 0.00200000009f, 0.0f, 0.0f };
f32 D_00263770[4] = { 0.200000003f, 0.0f, 0.800000012f, 0.0f };
f32 D_00263780[4] = { 40.0f, 0.0f, 0.100000001f, 0.0f };
f32 D_00263790[4] = { 0.0f, 2.5f, 0.0f, 0.0f };
f32 D_002637A0[4] = { 0.0f, 5.0f, 0.0f, 0.0f };
f32 D_002637B0 = 1.0f;
f32 D_002637B4 = 0.3f;
f32 D_002637B8 = 1.5f;

f32 D_002637BC = 2.0f;

f32 D_002637C0[3] = { 0.1f, 2.0f, 0.0f };
f32 D_002637CC = 0.875999987f;
s32 D_002637D0 = 50;
s32 D_002637D4 = 100;
f32 D_002637D8 = 0.100000001f;
f32 D_002637DC = 1000.0f;
f32 D_002637E0 = 20.0f;
f32 D_002637E4 = -7.5f;
f32 D_002637E8[2] = { 0.5f, 0.0f };
f32 D_002637F0[4] = { 0.0f, 2.0f, -1.0f, 0.0f };
f32 D_00263800[4] = { -20.0f, 5.0f, -25.0f, 0.0f };
f32 D_00263810[4] = { 0.0f, -0.600000024f, 0.5f, 0.0f };
f32 D_00263820[4] = { -20.0f, 5.0f, -25.0f, 0.0f };
f32 D_00263830[4] = { 0.0f, -0.600000024f, 0.5f, 0.0f };
f32 D_00263840[4] = { 0.0f, 0.0f, -100.0f, 0.0f };
f32 D_00263850 = -0.5f;
f32 D_00263854 = 100.0f;
f32 D_00263858[6] = { 4.0f, 0.0f, 0.5f, 10.0f, 0.0f, 0.0f };
f32 D_00263870[4] = { 0.0f, 0.5f, 0.0f, 0.0f };
f32 D_00263880 = 50.0f;
f32 D_00263884 = -50.0f;
f32 D_00263888[3] = { 5.0f, 0.0f, 0.100000001f };
f32 D_00263894 = 0.349999994f;
f32 D_00263898 = 0.0f;
Params_2638A0 D_002638A0 = { 50.0f, 0.0f, 0.25f, 0.0f, 0x16F, 0x170 };
f32 D_002638B8 = 75.0f;
f32 D_002638BC = -325.0f;
f32 D_002638C0 = -50.0f;
f32 D_002638C4 = -350.0f;
f32 D_002638C8[2] = { -300.0f, 0.0f };
f32 D_002638D0[4] = { 1.5f, -0.5f, 0.0f, 0.0f };
f32 D_002638E0[4] = { 1500.0f, 0.0f, 0.5f, 0.0f };
f32 D_002638F0[4] = { 4000.0f, 0.0f, 4.0f, 0.0f };
f32 D_00263900[4] = { 600.0f, 300.0f, 0.100000001f, 50.0f };
f32 D_00263910[2] = { 0.150000006f, 0.25f };
f32 D_00263918[3] = { 1000.0f, 0.0f, 0.25f };
f32 D_00263924 = 0.899999976f;
f32 D_00263928[2] = { 8.0f, 0.0f };

s32 D_00263930[16] = { -1, 36, 36, 36, -1, 36, 36, 36, 36, -1, 45, 45, 41, 40, 0, 0 };
f32 D_00263970[4] = { 0.0f, 0.0f, -750.0f, 0.0f };
f32 D_00263980[4] = { 0.0f, 0.0f, 500.0f, 0.0f };
f32 D_00263990 = -0.200000003f;
f32 D_00263994 = 1.0f;
f32 D_00263998 = 0.5f;
f32 D_0026399C = 0.25f;
f32 D_002639A0[4] = { -1.0f, 0.00400000019f, 0.0f, 0.0f };
f32 D_002639B0[2] = { 150.0f, -0.75f };
// 8 bytes, one word read whole
Obj_2639B8 D_002639B8 = {0};
f32 D_002639C0[4] = { 0.0f, 0.0f, 75.0f, 0.0f };
f32 D_002639D0[4] = { 0.0f, 0.0f, -225.0f, 0.0f };
f32 D_002639E0[2] = { -75.0f, 0.0f };
f32 D_002639E8[10] = { 0.699999988f, 0.800000012f, 0.899999976f, 1.0f, 1.20000005f, 1.39999998f, 1.60000002f, 1.79999995f, 2.0f, 0.0f };
f32 D_00263A10[32] = { 40.0f, 0.0f, 0.0f, 0.0f, 28.2999992f, 28.2999992f, 0.0f, 0.0f, 0.0f, 40.0f, 0.0f, 0.0f, -28.2999992f, 28.2999992f, 0.0f, 0.0f, -40.0f, 0.0f, 0.0f, 0.0f, -28.2999992f, -28.2999992f, 0.0f, 0.0f, 0.0f, -40.0f, 0.0f, 0.0f, 28.2999992f, -28.2999992f, 0.0f, 0.0f };
f32 D_00263A90[4] = { 200.0f, 200.0f, 200.0f, 0.0f };
f32 D_00263AA0[4] = { 400.0f, -1.0f, 0.0f, 0.0f };
f32 D_00263AB0[4] = { 0.0f, 1000.0f, 0.0f, 0.0f };

INCLUDE_RODATA(D_0024A860);
ASM_FUNC(func_0016F608);

void func_001BAC30(void* self);
void func_00124DF8(void* self, s32 id, void* table);
void func_00159478(void* a, void* b);

void func_0016F7B0(Player* self)
{
    LoadCollider(self);
    ResolveObjectLinks(self, 0x97, g_playerCharacterLinks);
    FindOrBuildMemberGroup((u8*)self + 0x2428, self);
    self->f2284 = -1.0f;
    self->f21C8 = -1.0f;
    g_player = self;
}

ASM_FUNC(func_0016F810);

ASM_FUNC(func_0016FD70);

INCLUDE_RODATA(jtbl_0024A870);
ASM_FUNC(func_001701B0);

void func_00170410(Player* self, Out_170410* out)
{
    f32 a;
    f32 b;
    if (self->f2220 == 0xD) {
        a = D_00262E34;
        b = D_00262E38;
    } else if (self->f2220 == 7) {
        goto zero_both;
    } else if (((VFn_170410*)self->desc)[90](self, out) != 0) {
        if (self->f2220 == 6 && self->f239C == 4 && ((Sub_170410*)self->f23BC)->f40 != 0) {
            goto zero_both;
        }
        a = D_002637B8;
        out->f98 = 0.0f;
        out->f94 = a;
        goto divide;
    } else {
        if (self->f2220 != 4) {
            goto zero_both;
        }
        s32 v = self->f2228;
        if (v == 0x28 || v == 0x31) {
            a = D_002637B0;
            out->f98 = 0.0f;
            out->f94 = a;
            goto divide;
        }
        a = D_002637B0;
        b = D_002637B4;
    }
    out->f94 = a;
    out->f98 = b;
    goto divide;
zero_both:
    out->f94 = 0.0f;
    out->f98 = 0.0f;
divide:
    out->f94 = out->f94 / self->f700;
}
extern f32 D_002637C0[3];

void func_001C53A8(void* self, s32 flags, void* out);

struct Out_170528 {
    u8 pad0[0x30];
    f32 f30;
};

void func_00170528(Player* self, s32 flags, Out_170528* out)
{
    if (self->f2220 == 4) {
        if (flags & 0x10) {
            f32 v;
            if (flags & 1) {
                v = -self->mass * self->gravity.z * g_frameDt[0] * D_002637BC;
            } else {
                v = -self->mass * self->gravity.z * D_002637C0[0];
            }
            if (v < out->f30) {
                out->f30 = v;
            }
        }
    } else {
        func_001C53A8(self, flags, out);
    }
}

void func_00175170(void* self, s32 mode, s32 count);
void func_001C61E0(void* self, s32 arg);
void func_001D4C98(void* self);

void func_001705C8(Player* self)
{
    s32 flags = self->f2254;
    if (flags == 0) {
        return;
    }
    if (flags & 8) {
        self->f2254 = flags & ~8;
        self->f224C = self->f2264;
    }
    if (self->f2254 & 1) {
        SetPlayerState(self, self->f2258, self->f225C);
    }
    if (self->f2254 & 2) {
        func_001C61E0(self, self->f2260);
    }
    if (self->f2254 & 0x10) {
        RunPlayerCallback(self);
    }
}

ASM_FUNC(func_00170660);

extern f32 D_00274AD0[];

s32 func_001C5248(void* self);

struct Ent_170790 {
    u8 pad0[0x88];
    f32 f88;
    u8 pad1[0x10];
    s32 i9C;
};

s32 func_00170790(Player* self, Ent_170790* e, s32 idx)
{
    if (self->f2220 != 0xD) {
        return func_001C5248(self);
    }
    f32 scale = D_00274AD0[idx];
    if (e->f88 * scale < 0.7f) {
        return 0;
    }
    s32 k = e->i9C;
    if (k < 7) {
        if (k >= 4) {
            return idx == 0;
        }
    }
    return 0;
}

ASM_FUNC(func_00170820);

INCLUDE_RODATA(jtbl_0024A8A0);
INCLUDE_RODATA(jtbl_0024A8F0);
INCLUDE_RODATA(jtbl_0024A930);
ASM_FUNC(func_00170960);

ASM_FUNC(func_00171180);

ASM_FUNC(func_00171238);

ASM_FUNC(func_001719E8);

ASM_FUNC(func_00171C80);

struct Loc_171DD8 { u8 pad0[8]; f32 f8; };

s32 func_00171180(void* self);
s32 func_00171C80(void* self, void* p, s32 n);
void func_001719E8(void* self, s32 a, s32 b, s32 c, f32 k, void* d);
void func_001278A8(s32 a, s32 b, void* c, s32 d, void* e, s32 f, s32 g);
f32 func_001EA480(f32 a, f32 b);
s32 func_001B63C0(void* p, s32 n);
void func_001B6628(void* p, s32 n);


void func_00171DD8(Player* self)
{
    Loc_171DD8 loc;
    if (func_00171180(self) == 0) {
        if (self->f690 != 0) {
            func_001278A8((s32)self->f6C0, 0, (u8*)self + 0x6A0, 0, &loc, 0, 0);
            loc.f8 = ClampToMagnitude(loc.f8, 10.0f);
            self->f638 = self->f638 + loc.f8 * g_frameDt[0];
        }
    }
    if (self->f250C == 0) return;
    u8* p1 = (u8*)self + 0x1190;
    f32 k = 5.0f;
    func_001719E8(self, (s32)self->f628, (s32)self->f620, self->f250C, k, p1);
    u8* p2 = (u8*)self + 0x1290;
    func_001719E8(self, (s32)self->f62C, (s32)self->f624, self->f2510, k, p2);
    if (func_00171C80(self, p1, self->f250C) != 0) {
        if (func_00171C80(self, p2, self->f2510) != 0) return;
    }
    if (self->f118C != 0) return;
    if (self->f1188 == 0) return;
    if (FindStateEntryIndex(self->f1188, 0x148) >= 0) TeleportStateWalker(self->f2234, 0x148);
    self->f118C = 1;
}

struct Vec4_171F28 {
    f32 x, y, z, w;
} __attribute__((aligned(16)));

s32 func_001EDEF0(void* a0, void* a1, void* a2, void* a3);

void func_00171F28(Player* self, f32 unusedF12, f32 scale)
{
    Vec4_171F28 tmp = *(Vec4_171F28*)((u8*)self + 0x140);
    tmp.z = tmp.z - 75.0f;
    Vec4_171F28 out;
    void* a1;
    func_001EDEF0(&tmp, a1, &out, self);
    self->desc02()->m20(self, (Vec02*)&out);
    if (self->f2220 != 4) {
        SetPlayerState(self, 2, 6);
        self->f226C = self->f226C * scale;
        if (scale == 0.0f) {
            self->f2498 = 0;
        }
    }
}

void func_00171FE0(Player* self)
{
    s32 st = self->f2220;
    if (st != 6) {
        if (st < 7) {
            if (st == 3) {
                goto act;
            }
        } else if (st == 7) {
            goto act;
        }
        return;
    act:
        self->f224C = 1;
        SetPlayerState(self, 2, 2);
    } else {
        s32 w = self->f239C;
        if (w >= 6) {
            return;
        }
        if (w < 4) {
            return;
        }
        SetPlayerState(self, 2, 2);
    }
}

ASM_FUNC(func_00172078);

ASM_FUNC(func_001721B0);

void func_001C5438(Player* self);
void func_001C4618(Player* self, void* a1, void* a2, s32 a3, f32 f12, void* a4);

void func_00172530(Player* self)
{
    RecomputeTurningColliderFrame(self);
    if (self->f2220 == 6 && self->f239C == 7) {
        self->f1290.f50 = 0;
        goto clear;
    }
    {
        void* a1 = self->f610;
        if (a1 == 0) {
            self->f1290.f50 = 0;
            goto clear;
        }
        if (self->f614 == 0) {
            self->f1290.f50 = 0;
            goto clear;
        }
        f32 k = 6.0f;
        func_001C4618(self, a1, a1, (s32)self->f620, k, (u8*)self + 0x1190);
        func_001C4618(self, self->f614, self->f614, (s32)self->f624, k, (u8*)self + 0x1290);
    }
    return;
clear:
    self->f1190.f50 = 0;
}

struct Aux_1725E0
{
    u8 pad0[0x2C8];
    u64 f2C8;
};
struct VtObj_1725E0
{
    void** vt;
};
void func_001C4848(Player* s, void* a, void* b, void* c);
void func_00125B70(Player* s, void* c, f32* out);
void func_00172078(Player* s, f32* buf, f32 t);
void func_00188B08(void* a, f32* b, f32* out);
void func_001CDD98(Player* s);
void func_001C49C8(Player* s, void* a, void* b);
void func_001C3028(void* a, void* b);
void func_001D62E0(Player* s, void* a, void* b);

void func_001725E0(Player* self, void* a, void* b)
{
    f32 buf[12];
    f32 out[20];
    s32 i;

    if (!(self->f2220 == 6 && self->f239C == 7))
    {
        func_001C4848(self, self->f610, self->f610, &self->f1190);
        func_001C4848(self, self->f614, self->f614, &self->f1290);
    }
    if (self->f2434 != 0.0f || self->f2430 != 0.0f)
    {
        ((Aux_1725E0*)self->f61C)->f2C8 &= ~(1ULL << 32);
        BuildPlacedObjectTransform(self, b, out);
        out[16] *= 0.25f;
        for (i = 0; i < 4; i++)
        {
            func_00172078(self, buf, (f32)i * 0.25f);
            BuildMatrixFromRotationAndTranslation((u8*)((Aux_1725E0*)self->f61C) + 0x140, buf, out);
            ((void (*)(void*, void*, f32*))((VtObj_1725E0*)((Aux_1725E0*)self->f61C))->vt[0xA0 / 4])(((Aux_1725E0*)self->f61C), a, out);
        }
        ((Aux_1725E0*)self->f61C)->f2C8 |= 0x100000000UL;
    }
    if (self->f2220 == 3)
    {
        func_001CDD98(self);
    }
    func_001C49C8(self, a, b);
    if (self->f21C0)
    {
        func_001C3028(self->f1520, a);
    }
    func_001D62E0(self, a, b);
}


f32 func_002058A0(f32 v, f32 m);
f32 func_001EA4B8(void* p, f32 a, f32 b, void* o, f32 c);

void func_001727B0(Player* self)
{
    if (self->f242C == 0.0f) {
        if (self->f2434 == 0.0f) {
            return;
        }
    }
    if (self->f242C != 0.0f) {
        *(f32*)((u8*)self + 0x2430) = self->f242C;
        self->f2434 = func_002058A0(self->f2434 + self->f242C * g_frameDt[0], 6.2831855f);
    } else {
        if (self->f2434 == 0.0f) {
            return;
        }
        f32 r = ApproachValueWithRamp(&D_002638A0, self->f2434, 6.2831855f, &self->f2430, g_frameDt[0]);
        self->f2434 = r;
        if (r == 6.2831855f) {
            self->f2434 = 0.0f;
        }
    }
}

// EXACT: callee func_001300E8 declared with a third parameter and called with k, which puts k in a2

struct Aux_172898 { u8 pad0[0x50]; void* f50; u8 pad1[0x554 - 0x54]; Contact03* f554; };

void func_001BC4D8(Player* a, void* b);
s32 func_001300E8(void* key, s32 kind, s32 extra);
void func_001C57C8(Player* a);
void func_00128018(Aux_172898* a, s32 b, void* c, void* d);
void func_001861E8(void* a, Contact03* b);

void func_00172898(Player* self)
{
    ContactRow03* row;
    Contact03** slot;
    Contact03* n;
    Contact03* head = 0;
    ExtractContactsByPartMode(self, self->f151C);
    row = self->contacts->head;
    if (row) {
        do {
            slot = &row->head;
            n = row->head;
            if (n) {
                do {
                    s32 k = (n->end[0].body != self);
                    if (*(void**)((u8*)n + (k << 6) + 4) == self->f23B0) {
                        void* other = n->end[1 - k].body;
                        if (other == 0 || IsObjectOfKind(other, 0x46, k) == 0) {
                            *slot = n->next;
                            n->next = head;
                            head = n;
                        } else {
                            slot = &n->next;
                        }
                    } else if ((void*)n->end[1 - k].body == ((Aux_172898*)self->f2750) && ((s32 (*)(Player*, Contact03*))self->desc06()->m56)(self, n)) {
                        *slot = n->next;
                        n->next = ((Aux_172898*)self->f2750)->f554;
                        ((Aux_172898*)self->f2750)->f554 = n;
                    } else {
                        slot = &n->next;
                    }
                    n = *slot;
                } while (n);
            }
            *row->link = row->head;
            row = row->next;
        } while (row);
    }
    func_001C57C8(self);
    if (self->f2220 == 8) {
        self->f690 = 1;
        self->f694 = g_gameTime[0];
        func_00128018(((Aux_172898*)self->f24A0), 0, self->f24B0, &self->v6A0);
        self->v6B0 = g_unitZVector;
        self->f6C0 = ((Aux_172898*)self->f24A0);
        row = self->contacts->head;
        if (row) {
            do {
                slot = &row->head;
                n = row->head;
                if (n) {
                    do {
                        s32 k = (self != n->end[0].body);
                        if (n->kind == 0xB) {
                            slot = &n->next;
                        } else {
                            if ((void*)n->end[1 - k].body == ((Aux_172898*)self->f24A0)->f50) {
                                *slot = n->next;
                                n->next = head;
                                head = n;
                            } else {
                                slot = &n->next;
                            }
                        }
                        n = *slot;
                    } while (n);
                }
                *row->link = row->head;
                row = row->next;
            } while (row);
        }
    }
    FreePooledContactChain(self->world, head);
}

void func_001B9680(void* self);

void func_00172AE0(Player* self)
{
    SaveColliderPreviousPosition(self);
    self->f21CC = 0;
}

// EXACT: declaring D_00261860 as an array (extern f32 D_00261860[], passed as D_00261860[0]) moved the float load into the jal delay slot.


struct __attribute__((aligned(16))) Quad_172B08 {
    s32 a, b, c, d;
};

struct Inner_172B08 {
    u8 pad0[0x140];
    Quad_172B08 q140;
};

typedef void (*VFn_172B08)(void* self);

void func_001BC088(void* self, void* b, f32 x);

void func_00172B08(Player* self)
{
    *(Quad_172B08*)&self->v21D0[1] = ((Inner_172B08*)self->f23D4)->q140;
    self->f21CC = 0;
    func_001BC088(self, 0, g_frameDt[0]);
    if (self->f223C == 0) {
        *(Quad_172B08*)&self->v21D0[0] = *(Quad_172B08*)&self->v140;
        *(Quad_172B08*)&self->v21D0[2] = ((Inner_172B08*)self->f23D4)->q140;
        self->f21CC = 3;
        ((VFn_172B08)((void**)self->desc)[0xD8 / 4])(self);
    } else {
        self->f21CC = 0;
    }
}

struct __attribute__((aligned(16))) Quad_172B88 { s32 a, b, c, d; };
void func_001B8540(void* self);
void func_001B8420(void* self, void* p, f32 f);

void func_00172B88(Player* self)
{
    s32 i = 0;
    UpdateColliderBounds(self);
    if (self->f21CC > 0) {
        Quad_172B88* p = (Quad_172B88*)self->v21D0;
        do {
            func_001B8420(self, p, self->f2420);
            i++;
            p++;
        } while (i < self->f21CC);
    }
}

s32 func_00182FC8(void* p);

void* func_00172BF8(Player* self, s32* out)
{
    void* p = self->f25D8[0];
    if (p != 0 && IsObjectAttached(p) != 0) {
        *out = 0;
        return self->f25D8[0];
    }
    p = self->f25D8[2];
    if (p != 0 && IsObjectAttached(p) != 0) {
        *out = 1;
        return self->f25D8[2];
    }
    p = self->f25D8[1];
    if (p != 0 && IsObjectAttached(p) != 0) {
        *out = 2;
        return self->f25D8[1];
    }
    p = self->f25D8[3];
    if (p != 0 && IsObjectAttached(p) != 0) {
        *out = 2;
        return self->f25D8[3];
    }
    p = self->f25D8[4];
    if (p != 0 && IsObjectAttached(p) != 0) {
        *out = 1;
        return self->f25D8[4];
    }
    return 0;
}

void func_001C5C10(Player* a, Collider* b, void* c, void* d);
void func_001C4790(Player* a, Collider* b, void* c, void* d);
void func_001879C0(Collider* a, f32 f, void* b, void* c, s32 d, s32 e, s32 g, void* h);
void func_00186BA8(void* a, Collider* b, void* c, void* d, void* e, void* f);

void func_00172CF0(Player* self, Collider* a1, void* a2, void* a3, void* a4, void* a5)
{
    s32 idx;
    Collider* v;
    Collider* cur;

    switch (self->f2220)
    {
    case 4:
        if (self->f2BD8 == 0)
        {
            switch (self->f2228)
            {
            case 0x24:
            case 0x2A:
            case 0x2B:
                func_001C5C10(self, a1, a4, a5);
                break;
            }
        }
        break;
    case 3:
    case 7:
    case 0xD:
        break;
    default:
        if (self->f2BD8 == 0)
        {
            func_001C5C10(self, a1, a4, a5);
        }
        break;
    }
    func_001C4790(self, a1, a4, &self->f1190);
    func_001C4790(self, a1, a4, &self->f1290);
    v = (Collider*)FindFirstAttachedSlotObject(self, &idx);
    if (v)
    {
        for (cur = a1; cur; cur = (Collider*)cur->parent)
        {
            if (*((u8*)cur + idx + 0x2B0))
            {
                if (a1->flags538 & (1ULL << 40))
                {
                    func_001879C0(a1, a1->radius3CC, (u8*)a1 + 0x140, v, v->tree.count, (s32)v->tree.nodes, 0, (u8*)self + 0x2670);
                }
                else if (a3)
                {
                    func_00186BA8(v, a1, a2, a3, a4, (u8*)self + 0x2670);
                }
                return;
            }
        }
    }
}

s32 func_00172EB8(Player* self)
{
    if (self->f2220 == 3 || self->f2220 == 0xD) {
        return 0;
    }
    return 3;
}

INCLUDE_RODATA(jtbl_0024A9D0);
ASM_FUNC(func_00172EE0);

ASM_FUNC(func_001733B8);


void func_001922E8(void* a, void* b);
void func_001D29C8(s32 id);

void func_00173708(Player* a, void* b)
{
    HandleSwitchedColliderActivation(a, b);
    s32 id;
    if (b != 0) id = g_saveData->f19FC;
    else id = -1;
    ShowModeLabel(id);
}

ASM_FUNC(func_00173750);

INCLUDE_RODATA(jtbl_0024A9F0);
INCLUDE_RODATA(jtbl_0024AA10);
INCLUDE_RODATA(jtbl_0024AA60);
INCLUDE_RODATA(jtbl_0024AAB0);
ASM_FUNC(func_00173888);

INCLUDE_RODATA(jtbl_0024AB00);
ASM_FUNC(func_00174808);

INCLUDE_RODATA(jtbl_0024AB40);
ASM_FUNC(func_00174E20);


void func_001C4D60(Player* self, void* a1, s32 zero);

void func_00174F50(Player* self, void* node)
{
    switch (self->f2220) {
    case 6: {
        s32 m = self->f239C;
        if ((m == 0 && self->f2228 == 0x15) || m == 7) {
            node = self->f146C;
        } else {
            node = self->f13D4[m];
        }
        break;
    }
    case 4: {
        s32 i = self->f2228;
        if (i != -1) {
            node = self->f1418[i];
            if (node == 0) {
                do {
                    s32 k = D_00263930[i - 0x24];
                    if (k == -1) {
                        break;
                    }
                    node = self->f1418[k];
                    i = k;
                } while (node == 0);
            }
        }
        break;
    }
    case 2: {
        s32 i = self->f2228;
        if (i < 0xE) {
            if (i >= 0xC) {
                node = self->f146C;
                break;
            }
        }
    }
    default:
        node = self->f1390[self->f2220];
        break;
    case 0xD:
        return;
    }
    if (node == 0) {
        node = self->f1390[0];
    }
    func_001C4D60(self, node, 0);
}

typedef void (*VFn_175078)(void* self);

struct Obj_175078 {
    VFn_175078* vtbl;
};

struct Dev_175078 {
    u8 pad_00[0x10];
    s8 f10;
};

struct Self_175078 {
    u8 pad_000[0x610];
    Obj_175078* f610;
    Obj_175078* f614;
    Obj_175078* f618;
    Obj_175078* f61C;
    u8 pad_620[0x24F8 - 0x620];
    Obj_175078* f24F8;
    u8 pad_24FC[0x2500 - 0x24FC];
    Dev_175078* f2500;
    Dev_175078* f2504;
    Dev_175078* f2508;
    Dev_175078* f250C;
    Dev_175078* f2510;
};

void func_00175078(Self_175078* self, s32 flags)
{
    if (self->f2500 != 0) {
        s32 a = flags & 1;
        self->f2500->f10 = a ? 9 : -1;
        self->f2504->f10 = a ? 9 : -1;
        self->f2508->f10 = a ? 9 : -1;
        s32 b = flags & 2;
        self->f250C->f10 = b ? 9 : -1;
        self->f2510->f10 = b ? 9 : -1;
        Obj_175078* o = self->f24F8;
        o->vtbl[47](o);
        o = self->f618;
        o->vtbl[47](o);
        o = self->f61C;
        o->vtbl[47](o);
        o = self->f610;
        o->vtbl[47](o);
        o = self->f614;
        o->vtbl[47](o);
    }
}

INCLUDE_RODATA(D_0024AB7C);
INCLUDE_RODATA(jtbl_0024AB80);
INCLUDE_RODATA(jtbl_0024ABC0);
INCLUDE_RODATA(jtbl_0024AC00);
INCLUDE_RODATA(jtbl_0024AC20);
INCLUDE_RODATA(jtbl_0024AC40);
INCLUDE_RODATA(jtbl_0024AC90);
INCLUDE_RODATA(jtbl_0024ACB0);
INCLUDE_RODATA(jtbl_0024AD80);
INCLUDE_RODATA(jtbl_0024AE70);
INCLUDE_RODATA(jtbl_0024AE90);
INCLUDE_RODATA(jtbl_0024AEB0);
ASM_FUNC(func_00175170);

void func_001777F8(void)
{
}

void func_00175170(void* self, s32 mode, s32 count);

void func_00177800(void* self, s32 flag)
{
    SetPlayerState(self, flag ? 11 : 0, -1);
}

void func_00177828(Player* self, s32 value)
{
    self->f2BD8 = value;
    self->f4B8 = 0;
}

struct Node_177838;
struct VT_177838 {
    u32 pad0;
    u32 pad4;
    u32 flags;
    u8 pad[0xB8];
    s32 (*f_c4)(Node_177838* self, void* q);
};
struct Node_177838 {
    VT_177838* vt;
    u8 pad4[0x14];
    Node_177838* next;
    u8 pad1c[0x294];
    u8 b2B0;
    u8 b2B1;
    u8 b2B2;
    u8 b2B3;
    u8 b2B4;
};
struct Head_177838 { u32 pad0; u32 pad4; u32 flags; };
Node_177838* func_00177838(NodeQuery* q, s32 n, Node_177838** list) {
    Node_177838* node;
    if (((Node_177838*)q->hold)->vt->flags & 1) {
        node = (Node_177838*)q->hold;
    } else {
        node = ((Node_177838*)q->hold)->next;
    }
    for (; node != 0; node = node->next) {
        s32 i;
        for (i = 0; i < n; i++) {
            if (node == list[i]) return 0;
        }
        switch (q->kind) {
        case 2: q->out = node->b2B0; break;
        case 8: q->out = node->b2B1; break;
        case 4: q->out = node->b2B2; break;
        case 16: q->out = node->b2B3; break;
        case 32: q->out = node->b2B4; break;
        default: q->out = 0; break;
        }
        if (node->vt->f_c4(node, q)) return node;
    }
    return node;
}

struct Keyed_177968 { u8 pad0[0x14]; f32 key; };

s32 func_00177968(Keyed_177968* a, Keyed_177968* b)
{
    s32 r = -1;
    if (a->key > b->key) r = 1;
    return r;
}

ASM_FUNC(func_00177990);

s32 func_001493A0(u8* p);

s32 func_00177E20(Player* self)
{
    if (self->f2220 == 12 && self->f2228 == 0x22) return 0;
    return IsTopCameraController((u8*)&g_camera->ctl454) == 0;
}

void func_001924C8(void* self, s32 mode);
void func_00175170(void* self, s32 a, s32 b);

void func_00177E70(Player* self, s32 mode)
{
    func_001924C8(self, mode);
    switch (mode) {
    case 0:
        (void)SetPlayerState(self, 9, 0x1C);
        break;
    case 1:
        (void)SetPlayerState(self, 9, 0x1D);
        break;
    }
}

struct Other_177EE0 { u8 pad0[0x2D0]; s32 f2D0; };
extern s32 D_00275BC4;

void func_00177EE0(Player* self, Other_177EE0* other, s32* out)
{
    s32 v;
    switch (self->f2220) {
    case 0:
    case 1:
    case 5:
        v = 1;
        goto both;
    case 2:
    case 8:
    case 10:
    case 13:
    case 14:
    case 15:
    case 16:
        out[0] = 1;
        out[1] = other->f2D0 == 1;
        break;
    case 3:
    case 6:
    case 7:
        v = other->f2D0 == 1;
    both:
        out[0] = v;
        out[1] = v;
        break;
    case 12:
        out[0] = 0;
        out[1] = (s32)self->f2BD0 == (s32)other;
        break;
    case 4:
    case 9:
        out[0] = 0;
        out[1] = other->f2D0 == 1;
        break;
    case 11:
        out[0] = 0;
        out[1] = 1;
        break;
    }
    if (D_00275BC4 != 3)
        out[0] = 0;
}

extern u8 D_00275BC0[];

struct Node_177F98 {
    u8 pad0[0x2D0];
    s32 kind;
};

void func_001E9498(void* a, void* b);

void func_00177F98(Player* self, Node_177F98* node)
{
    if ((u32)(node->kind - 1) < 2) {
        g_typedTextCaptionBox.child = node;
        PushStackElement(g_elementStack, &g_typedTextCaptionBox);
        return;
    }
    if (self->f2220 != 0xC) {
        s32 f = self->f2254;
        self->f225C = 0x21;
        self->f2BD0 = node;
        self->f2258 = 0xC;
        self->f2254 = f | 1;
    }
}

void func_001B9690(void* self);
void func_001C29E8(void* sub);

void func_00178008(Player* self)
{
    SetColliderPosition(self);
    ResetTrailRing(self->f1520);
    self->f2768 = 0;
}

void func_001921A8(void* self);


struct Sub_1793F0 { u8 pad0[0xE0]; void* fE0; };
struct Packed_1793F0 { f32 v; } __attribute__((packed));

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a1, void* a2);
void func_0012B5B8(void* a, s32 b, s32 c);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
void func_00139038(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void** a7);
void func_001399F8(void* obj, s32 a1, s32 a2, void* a3);
void func_0017ABE8(void* self, s32 a1);
s32 func_001B4688(s32 key);


void func_001C29E8(void* sub);
void func_00192820(void* self);

void func_00178038(Player* self)
{
    ResetTrailRing(self->f1520);
    RegisterSwitchedCollider(self);
}

ASM_FUNC(func_00178068);

// NEAR: the float store of f6D4 is scheduled before the li/sw of f6D0; retail stores f6D0 first

typedef s32 (*VFn_17AA40_A)(void* self, s32 v);
typedef void (*VFn_17AA40_B)(void* self, void* p);
typedef void (*VFn_17AA40_C)(void* self, s32 a, void* b);

struct Msg_17AA40 {
    void* self;
    s32 v;
};

s32 func_00160C58(void);
void func_001794E0(void* self, void* a, void* b);
void func_00127E60(void* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);
void func_0017ABE8(void* self, s32 a1);



// NEAR: 0x558 clamp uses movz with the operand order ours does not reproduce; msg->fC mask load goes to the other register

extern s32 D_00263E2C;

void func_001AC060(void* p);
void func_001837E0(void* self, s32 a, s32 b, s32 c);
void func_0012C918(void* a, CountdownCollider* b, s32 c, void* d, f32 e, f32 f);
s32 func_001BC320(void* self, ObjectEvent* msg);


struct Vt_17B9D0
{
    u8 pad0[0x28];
    void (*f28)(void* self, Vec02* a, s32 b, Vec02* c, Vec02* d, s32 e, s32 f);
};

struct Node_17B9D0
{
    u8 pad0[0x18];
    void* f18;
    u8 pad1c[0x18];
    struct { Vt_17B9D0* vt; }* f34;
    u8 pad38[0x108];
    Vec02 f140;
};

struct Self_17B9D0
{
    u8 pad0[0x3C];
    u8* f3C;
};

s32 func_001300E8(Node_17B9D0* n, s32 kind);
void func_00128018(void* a, void* b, void* c, Vec02* d);

// Matches retail's bytes (EXACT us and eu): the call result is tested directly with a goto to the zero return.

struct Ptr_17A9E0;
s32 func_001DDA80(Ptr_17A9E0* p);

struct Pair_1781E0 { s32 a, b; };

void func_001B6598(void* ptr, s32* out);
void func_001B6568(void* ptr, s32* out);

void func_001781E0(u8* self, u8* other)
{
    Pair_1781E0 r;
    if (*(s32*)(self + 0x2220) != 9) {
        func_001B6598(*(void**)(other + 0x2D8), &r.a);
        func_001B6568(*(void**)(other + 0x2D8), &r.b);
        if (r.a == 0x22E && (r.b == r.a || r.b == -1)) {
            *(u8**)(self + 0x2BE0) = other;
        }
    }
}

void func_001B7968(void* self);


s32 func_0012C918(void* a, void* b, s32 c, void* d, f32 e, f32 f);


typedef void (*VFn_17BC20)(void* self);

struct Comp_17BC20 {
    VFn_17BC20* vtbl;
    u8 pad0[0x2D0 - 4];
    s32 f2D0;
};

struct Obj_17BC20 {
    u8 pad0[0x3C];
    s32 f3C;
    u8 pad1[0x58 - 0x40];
    Comp_17BC20* f58;
    s32 f5C;
};

s32 func_00182FC8(void* p);


extern s32 D_00263E2C;


void func_00124A48(void* self);
void func_00124DF8(void* self, int n, void* table);


void func_001794E0(void* self, void* a, void* b);
void func_00127E60(void* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);


void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a1, void* a2);
void func_00139038(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void** a7);
void func_001399F8(void* obj, s32 a1, s32 a2, void* a3);
void func_0017B410(C4A* self, s32 a1);
s32 func_0017B510(C4A* self, s32 a1);


struct Msg_17B3A8 {
    u8 pad0[4];
    s32 f4;
    u8 pad1[8];
    u32 f10;
};

void func_001AC060(void* p);
void func_0017B598(C4A* self);
void func_001837E0(void* self, s32 a, s32 b, s32 c);


s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);


struct Item_178258 { u8 pad[0x2D0]; s32 link; };

void func_00178258(Player* a0, Item_178258* a1)
{
    if (a0->f2220 != 9 && a1->link == 0) {
        a0->f2BE4 = a1;
    }
}

struct Item_178280 { u8 pad[0x2D0]; s32 link; };

void func_00178280(Player* a0, Item_178280* a1)
{
    if (a0->f2220 != 9 && a1->link == 0) {
        a0->f2BE8 = a1;
    }
}

ASM_FUNC(func_001782A8);

ASM_FUNC(func_001782C0);

typedef void (*VFn_179690)(void*);

void func_001BC088(void* self, void* b);


void func_00192C58(void* self);
void func_0017ABE8(void* self, s32 a1);


void func_00192230(void* self, s32 kind, MessageBody* rec);


struct __attribute__((aligned(16))) Quad_178598 {
    s32 a, b, c, d;
};

struct Pair_178598 {
    Quad_178598 q0;
    Quad_178598 q1;
};

struct Sub_178598 {
    u8 pad0[0x18];
    f32 f18;
    u8 pad1[0x20 - 0x1C];
    Quad_178598 q20;
    Quad_178598 q30;
};

struct Frame_178598 {
    Quad_178598 q0;
    Quad_178598 q1;
    Quad_178598 q2;
    Quad_178598 p0;
    Quad_178598 p1;
    f32 fl;
};

void func_00178D98(void* self, s32 a1, s32 a2, void* a3, void* a4);
void func_001782C0(void* self, void* s2, f32 f, void* a2, void* a3, void* a4);
void func_00175170(void* self, s32 a, s32 b);


void func_00178598(Player* self, Pair_178598* s2, f32 f)
{
    Frame_178598 fr;
    fr.fl = f;
    if (s2 == 0) {
        ChooseBestTargetCandidate(self, 0, 0, &fr.p0, &fr.fl);
        s2 = (Pair_178598*)&fr.p0;
    }
    void* q1 = &fr.q1;
    ComputeTargetArc(self, s2, fr.fl, q1, &fr.q0, &fr.q2);
    ((Sub_178598*)self->f2514)->f18 = g_gameTime[0] + fr.fl;
    ((Sub_178598*)self->f2514)->q20 = fr.q0;
    ((Sub_178598*)self->f2514)->q30 = fr.q2;
    self->desc02()->m20(self, (Vec02*)q1);
    self->q2B70[0] = *(Vec02*)&s2->q0;
    self->q2B70[1] = *(Vec02*)&s2->q1;

    SetPlayerState(self, 4, 0x2C);
}

INCLUDE_RODATA(D_0024AFA0);
ASM_FUNC(func_00178678);

ASM_FUNC(func_001788F0);

ASM_FUNC(func_00178D18);

typedef void (*Fn_17B410)(void* self);

struct Sys_17B410 {
    Fn_17B410* vtbl;
    u8 pad0[0x260 - 4];
    s32 f260;
    s32 f264;
    u8 pad1[0x26C - 0x268];
    s32 f26C;
    s32 f270;
    s32 f274;
    f32 f278;
};


void func_001DDC38(void* a, void* b);
s32 func_0012C918(void* a, void* b, s32 c, void* d, f32 e, f32 f);


extern s32 D_00263E2C;
extern s32 D_00263E30;

void func_001B93F8(void* self);
void func_0012E760(void* p);
void func_0017B8C0(void* self, s32 state);
void func_00160578(s32 n);


extern s32 D_00270458;
extern s32 D_00270B54;
extern s32 D_002717CC;
s32 func_001E9970(void* self);


extern s32 D_00270458;
extern s32 D_00270B54;
extern s32 D_002717CC;
s32 func_001E9970(void* self);


extern f32 D_00261858[];
extern f32 D_00275C60[];
extern Rgba4 D_002623E0;

f32 func_00205210(f32 x);
void func_00126A48(C1B* o, u32 value);
void func_00125C90(C1B* o, void* s, void* out);


// NEAR: last call (func_001B9D10) loads a2 before $f12 is moved; retail moves $f12 first. Otherwise every instruction matches.

struct Sub_179590;
extern f32 D_00263C20[];
extern f32 D_00263C30[];
extern f32 D_00263C40[];

void func_001B9338(C1B* self, f32 t);
void func_001794E0(C1B* self, Vec02* a, Vec02* b);
void func_00127E60(Sub_179590* obj, s32 a1, void* a2, s32 a3, void* a4, s32 a5);
void func_001B9058(C1B* self, void* buf, f32 f, void* d1, void* d2, void* d3);
void func_001B9D10(C1B* self, f32 scale, void* out, void* data);


struct Q_178D98 {
    u8 b[16];
} __attribute__((aligned(16)));
struct Hit_178D98 {
    Q_178D98 q0;
    Q_178D98 q1;
};
struct Node_178D98;
struct Vt_178D98;
struct Sub_178D98 {
    Vt_178D98* vt;
};
struct Vt_178D98 {
    u8 pad00[0x28];
    void (*f28)(Sub_178D98* self, Q_178D98* a, s32 b, s32 c, s32 d, s32 e, f32* out);
};
struct Node_178D98 {
    u8 pad00[0x18];
    void* f18;
    u8 pad1C[0x34 - 0x1C];
    Sub_178D98* f34;
};
struct Entry_178D98 {
    Node_178D98* node;
    f32 f4;
    u8 pad08[8];
    u8 f10[16];
};
struct Slot_178D98 {
    Node_178D98* node;
    u8 pad04[0x1C];
};
s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void func_0018D608(void);
Entry_178D98* func_0018D6A8(s32 size);
void func_0018D6F0(void);
s32 func_00182FC8(Node_178D98* p);
s32 func_001300E8(Node_178D98* n, s32 kind);
void func_00128018(void* a, void* b, Q_178D98* c, Q_178D98* d);
void func_001782C0(Player* self, Entry_178D98* e, f32 f, void* a2, void* a3, void* a4);
s32 func_00178D18(Entry_178D98* a, Entry_178D98* b);
void func_001F5CD0(Entry_178D98* base, s32 n, s32 size, s32 (*cmp)(Entry_178D98*, Entry_178D98*));
f32 func_001788F0(Player* self, void* e, s32 v, void* a3, Hit_178D98* a4, f32* a5);
void func_001F5C0C(void* dst, s32 value, s32 size);

void func_00178D98(Player* self, s32 n, Node_178D98** items, Hit_178D98* out, f32* outf)
{
    u8 scratch[0x80];
    Hit_178D98 hit;
    Q_178D98 tmp;
    f32 dist;
    f32 r;
    s32 v;
    Entry_178D98* buf;
    f32 best;
    s32 cnt = 0;

    v = GatherObjectsById(self->world, 5, 8, 0, 0x20, scratch);
    PushBackMemoryMark();
    buf = AllocateZeroedBackMemory(n << 5);
    for (s32 i = 0; i < n; i++) {
        Node_178D98* node = items[i];
        if (IsObjectAttached(node) != 0) {
            Entry_178D98* e = buf + cnt;
            cnt = cnt + 1;
            e->node = node;
            if (IsObjectOfKind(node, 0x6E) != 0) {
                func_00128018(0, node->f18, (Q_178D98*)&self->v140, &tmp);
                Sub_178D98* s = node->f34;
                if (s->vt->f28 != 0) {
                    s->vt->f28(s, &tmp, 0, 0, 0, 0, &e->f4);
                }
            } else {
                e->f4 = 0;
            }
            ComputeTargetArc(self, e, 0.7f, 0, e->f10, 0);
        }
    }
    func_001F5CD0(buf, cnt, 0x20, func_00178D18);
    best = 3.40282347e+38f;
    for (s32 i = 0; i < cnt; i++) {
        r = func_001788F0(self, &buf[i], v, scratch, &hit, &dist);
        if (r < best) {
            best = r;
            *out = hit;
            *outf = dist;
            if (best == 0.0f)
                goto done;
        }
    }
    if (best <= 1000.0f)
        goto done;
    for (s32 i = 0; i < self->f2768; i++) {
        Slot_178D98* q = &((Slot_178D98*)self->f2770)[i];
        if (q->node == 0 || IsObjectAttached(q->node) != 0) {
            r = func_001788F0(self, q, v, scratch, &hit, &dist);
            if (r < best) {
                best = r;
                *out = hit;
                *outf = dist;
                if (best == 0.0f)
                    goto done;
            }
        }
    }
    if (best == 3.40282347e+38f) {
        func_001F5C0C(out, 0, 0x20);
        *(s32*)out = 0;
        out->q1 = *(Q_178D98*)&self->v140;
        ((f32*)out)[6] -= 75.0f;
        *outf = 0.75f;
    }
done:
    PopBackMemoryMark();
}

INCLUDE_RODATA(jtbl_0024AFB0);
ASM_FUNC(func_001790B8);
