// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "c05.h"
#include "c52.h"
#include "c64.h"
#include "c29.h"
#include "c47.h"
#include "button_code.h"
#include "globals.h"
#include "g261858.h"
#include "g262c70.h"
#include "g27c220.h"
#include "s1be728.h"
#include "shapes.h"

void func_001F3A40(void);

void func_0016C4B8(void)
{
    func_001F3A40();
}

extern s32 D_002629C8;

void func_0016DCF0(s32 value)
{
    D_002629C8 = value;
}


void func_0016DF30(C2A* self)
{
    func_001400A8(self);
    self->zone.duration = 0;
    self->id7A0 = -1;
    self->id7A8 = -1;
}

void func_001A7CE8(void* p);

void func_0016EC38(G262C70* self)
{
    if (self->pC0 == 0) return;
    if (self->f18 < 3) return;
    if (self->f14 != 3) return;
    func_001A7CE8(self->fBC);
}

struct Row_262E40 { s32 a; s32 b; s32 c; };
struct Table_262E40 { Row_262E40 rows[151]; s32 tail; };
Table_262E40 D_00262E40 = {
{
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
},
0x0
};

void func_001BAC30(void* self);
void func_00124DF8(void* self, s32 id, void* table);
void func_00159478(void* a, void* b);

void func_0016F7B0(C07* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 0x97, &D_00262E40);
    func_00159478((u8*)self + 0x2428, self);
    self->f2284 = -1.0f;
    self->f21C8 = -1.0f;
    D_00262E10 = self;
}


extern u8 D_00262A68[];
extern u8 D_00262AA0[];
extern u8 D_00262AD8[];
extern u8 D_00262B10[];
extern u8 D_00262B48[];
extern u8 D_00262B80[];
extern u8 D_00262BB8[];
extern u8 D_00262BF0[];
extern u8 D_00262C28[];
void func_001E5278(s32 mode);
void func_0016F408(void);
void func_0016F430(s32 flags);
void func_0016F478(void);
void func_00199F38(void);
void func_00199FF0(void);
void func_0019A0F0(void);
ButtonCodeSlot D_00262A80 = { { (const u16*)D_00262A68, 0xB, (ButtonCodeFn)func_001E5278, 0x0 } };
ButtonCodeSlot D_00262AB8 = { { (const u16*)D_00262AA0, 0xB, (ButtonCodeFn)func_0016F408, 0x0 } };
ButtonCodeSlot D_00262AF0 = { { (const u16*)D_00262AD8, 0xB, (ButtonCodeFn)func_0016F430, 0x4004 } };
ButtonCodeSlot D_00262B28 = { { (const u16*)D_00262B10, 0xB, (ButtonCodeFn)func_0016F430, 0x8 } };
ButtonCodeSlot D_00262B60 = { { (const u16*)D_00262B48, 0xB, (ButtonCodeFn)func_0016F430, 0x2 } };
ButtonCodeSlot D_00262B98 = { { (const u16*)D_00262B80, 0xB, (ButtonCodeFn)func_00199F38, 0x0 } };
ButtonCodeSlot D_00262BD0 = { { (const u16*)D_00262BB8, 0xB, (ButtonCodeFn)func_00199FF0, 0xF000FFFF } };
ButtonCodeSlot D_00262C08 = { { (const u16*)D_00262BF0, 0xB, (ButtonCodeFn)func_0019A0F0, 0x0 } };
ButtonCode D_00262C48 = { (const u16*)D_00262C28, 0xD, (ButtonCodeFn)func_0016F478, 0x0 };

void func_0016F188(ButtonCode* entry);

void func_0016F588(void)
{
    AddButtonCode(&D_00262A80.rec);
    AddButtonCode(&D_00262AB8.rec);
    AddButtonCode(&D_00262AF0.rec);
    AddButtonCode(&D_00262B28.rec);
    AddButtonCode(&D_00262B60.rec);
    AddButtonCode(&D_00262B98.rec);
    AddButtonCode(&D_00262BD0.rec);
    AddButtonCode(&D_00262C08.rec);
    AddButtonCode(&D_00262C48);
}


void func_00127378(void* self, s32 type, void* packet);
void func_0016D490(void* self);
void func_0016D828(void* self);
void func_0016D928(void* self);
void func_0016DAC0(void* self, s32 mode);

void func_0016DA00(C47* self, s32 type, Packet47* packet)
{
    func_00127378(self, type, packet);
    if (type != 0x13) {
        return;
    }
    s32 code = packet->code;
    if (code == 0x2FE) {
        goto call928;
    }
    if (code < 0x2FF) {
        if (code == 0x2FD) {
            goto call490;
        }
        return;
    }
    if (code == 0x2FF) {
        goto callDAC0;
    }
    if (code == 0x300) {
        func_0016D828(self);
    }
    return;
call490:
    func_0016D490(self);
    return;
callDAC0:
    func_0016DAC0(self, 2);
    return;
call928:
    func_0016D928(self);
}

extern s32 D_002629C8;

void func_0016DD00(void)
{
    D_002629C8 = 0;
}

void func_00123ED0(void* self);

void func_0016DD10(C64* self)
{
    func_00123ED0(self);
    self->tune31C = 2.25f;
    self->tune320 = 2.0f;
    self->tune324 = 0.8f;
    self->tune328 = 4.0f;
    self->tune32C = 0.5f;
    self->tune330 = 1000.0f;
    self->tune334 = 2000.0f;
}

void func_001289C0(void* self);
s32 func_0015A4F0(s32 a, s32 b, s32 c, void* d, s32 e, void* f);

void func_0016DD90(C64* self)
{
    func_001289C0(self);
    s32 r = func_0015A4F0((s32)self->world, 0x201, 0x73, self, 0x10, self->table2D0);
    self->tableCount = r;
    if ((u32)r >= 0x11) {
        self->tableCount = 0x10;
    }
}

extern s32 D_00262C6C;

void func_0016E148();

s32 func_0016E0F0(s32 bits)
{
    D_00262C6C |= bits;
    return ((s32 (*)())func_0016E148)();
}

extern s32 D_00262C6C;
extern s32 D_00262C68;

void func_0016E148()
{
    s32 flags = D_00262C6C;
    if ((flags & 0x84) != 0)
    {
        D_00262C68 = 0;
        return;
    }
    if ((flags & 1) != 0)
    {
        D_00262C68 = 5;
        return;
    }
    if ((flags & 2) != 0)
    {
        D_00262C68 = 4;
        return;
    }
    D_00262C68 = 7;
}

void func_001F5C0C(void* p, s32 value, s32 size);
void* func_0018D4B0(s32 size);
void func_002042C8(s32 a, s32 b, s32 c);
void func_0016E630(G262C70* self, s32 mode, s32 n);

void func_0016E1A0(G262C70* self, s32 a, s32 b)
{
    func_001F5C0C(self, 0, 0xC4);
    func_0016E630(self, 1, 0);
    self->f04 = a;
    self->f08 = b;
    s32 size = ((s32)func_0018D4B0(0x140) + 0x3F) & -0x40;
    self->f0C = size;
    func_002042C8(self->f04, self->f08, size);
    self->fBC = func_0018D4B0(0x20);
    self->fC0 = 1;
}


void func_001A7B20(void* a, s32 b, s32 c);

void func_0016E630(G262C70* self, s32 mode, s32 n)
{
    s32 next = mode;
    if (mode == self->f14)
    {
        if (n == self->f18)
        {
            return;
        }
    }
    if (n == 0)
    {
        self->f10 = 0;
        next = 1;
    }
    if (self->f18 < 3 && n >= 3)
    {
        func_001A7B20(self->fBC, self->f04, self->f08);
    }
    if (next == 3)
    {
        self->f20 = 0;
        self->f84 = 0;
        self->f50 = 0;
        self->fA8 = 0;
        for (u32 i = 0; i < 4; i++)
        {
            self->a88[i].lo = -0.75f;
            self->a54[i].lo = -0.75f;
            self->a88[i].hi = 0.75f;
            self->a54[i].hi = 0.75f;
        }
    }
    self->f14 = next;
    self->f18 = n;
    self->f1C = D_00261858.f10;
}

void func_0016EC20(G262C70* self, u32 mask)
{
    u16 m = (u16)mask;
    self->flags &= (u16)~m;
}

struct Item_16D3F0 { u8 pad0[0x318]; s32 f318; };

void func_001A8AF8(void* p);
Obj_1BF0D8* func_001BEEF8(s32 kind);
void func_001BF0D8(Obj_1BF0D8* p);

void func_0016D3F0(C47* self, C2A* x)
{
    if (x == self->f558) {
        return;
    }
    void* v = 0;
    if (x != 0) {
        v = x->f7AC;
    }
    if (v != self->f5D0) {
        self->f5D0 = v;
        self->f5D4 = 3;
    }
    self->f558 = x;
    if (v != 0) {
        self->f570->f44 = ((Item_16D3F0*)x->f7AC)->f318;
        func_001A8AF8(self->f570);
        if (self->f5BC != 0) {
            return;
        }
        self->f5BC = func_001BEEF8(0x6B);
    } else {
        if (self->f5BC != 0) {
            func_001BF0D8(self->f5BC);
            self->f5BC = 0;
        }
    }
}


s32 func_001BE810(void* self);
void func_001BE8F8(void* self, s32 mode, f32 a, f32 b);

void func_0016D9A8(C47* self)
{
    if (self->f5CC != 0) {
        if (func_001BE810(self) == 0) {
            self->f5CC = 0;
            func_001BE8F8(self, 0, self->f5C4, self->f5C8);
        }
    }
}

ButtonCode* D_00262DFC = 0;

void func_0016F1F8(void)
{
    ButtonCode* p = g_buttonCodes;
    if (p != 0) {
        do {
            p->pos = 0;
            p = p->next;
        } while (p != 0);
    }
}

extern f32 D_00261868[];
struct Next_262E00 { f32 time; f32 pad[3]; };
Next_262E00 D_00262E00 = { 0.0f, { 0.0f, 0.0f, 0.0f } };

void func_0016F1F8(void);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);

void func_0016F2E0(void)
{
    if (D_00262E00.time == 0.0f) {
        return;
    }
    if (!(D_00262E00.time <= D_00261868[0])) {
        return;
    }
    ButtonCode* best = 0;
    ButtonCode** link = &g_buttonCodes;
    ButtonCode* p = g_buttonCodes;
    while (p != 0) {
        if (p->drop != 0) {
            *link = p->next;
            p->pos = 0;
            p->drop = 0;
            p->next = 0;
        } else if (p->pos < p->length) {
            link = &p->next;
        } else {
            if (best == 0 || best->length < p->length) {
                best = p;
            }
            link = &p->next;
        }
        p = *link;
    }
    if (best != 0) {
        func_001BFCD8(0x79, 0, 0, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f);
        best->fn(best->arg);
    }
    ResetButtonCodes();
    D_00262E00.time = 0.0f;
}

void func_00124A48(void* self);

void func_0016DDE8(C64* self)
{
    func_00124A48(self);
    self->desc->m03(self);
}


void func_001249A8(void* self);
s32 func_0015A418(void* a0, s32 a1, s32 a2, void* a3);
s32 func_0015A838(void* a0, s32 a1, s32 a2, void* a3);

void func_0016DF68(C2A* self)
{
    func_001249A8(self);
    if (self->id7A0 != -1) {
        self->f7A4 = (void*)func_0015A418(self->world, 4, self->id7A0, self);
    } else {
        self->f7A4 = (void*)func_0015A838(self->world, 2, 0x7E, self);
    }
    self->f7AC = (void*)func_0015A418(self->world, 4, self->id7A8, self);
}

extern s32 D_00262C64;

void func_001E5278(s32 mode);

void func_0016F408(void)
{
    D_00262C64 = 0;
    func_001E5278(0);
}

extern s32 D_00262C64;

void func_001E5278(s32 mode);

void func_0016F430(s32 flags)
{
    D_00262C64 = D_00262C64 | (flags & ~0x4000);
    if (flags & 0x4000)
    {
        func_001E5278(0);
    }
}

void func_0016EC88(G262C70* p) { p->f28 = 0; p->f2C = 0; }

void func_001261C0(void);

void func_0016C508(void)
{
    func_001261C0();
}



void* func_0015A448(void* obj, void* id, void* owner);
void func_0016D3F0(C47* self, C2A* x);
void func_0016D788(C47* self);
void func_0016DAC0(C47* self, s32 mode);

void func_0016D040(C47* self, void* x)
{
    self->f578 = (s32)x;
    C2A* p = (C2A*)func_0015A448(self->world, x, self);
    if (p != 0) {
        func_0016D3F0(self, p);
        func_0016D788(self);
        if (p->f7AC != 0) {
            func_0016DAC0(self, 2);
        } else {
            func_0016DAC0(self, 4);
        }
    }
}

extern u8 D_00262988[];
extern u8 D_002629A8[];
void func_001F5C0C(void* p, s32 v, s32 n);

struct Rec_16C360 { u8 pad0[4]; u8 b4; u8 pad5[3]; f32 f8; f32 fC; f32 f10; f32 f14; s32 w18; };

void func_0016C360(s32 a0, s32 a1)
{
    if (a1 == 0xFFFF && a0 != 0) {
        Rec_16C360* p = (Rec_16C360*)D_00262988;
        func_001F5C0C(p, 0, 0x1C);
        p->b4 = 0x2D;
        p->f8 = 2.0f;
        p->fC = 1.0f;
        p->f10 = 0.3f;
        p->f14 = 0.3f;
        p->w18 = (s32)0xFF7D4B00;
        Rec_16C360* q = (Rec_16C360*)D_002629A8;
        func_001F5C0C(q, 0, 0x1C);
        q->b4 = 0x2D;
        q->f8 = 2.0f;
        q->fC = 1.0f;
        q->f10 = 0.3f;
        q->f14 = 0.3f;
        q->w18 = (s32)0xFF7D4B00;
    }
}

void func_001B7968(void* self);
void func_00152438(void* self, s32 value);
extern s32 D_002629C8;



void func_0016CE00(C47* self)
{
    func_001B7968(self);
    self->f578 = -1;
    self->f598 = -1;
    self->f5C4 = 3000.0f;
    self->f5C8 = 1000.0f;
    func_00152438(&self->list55C, 0x7B0);
    Tune47* q = &self->tune5B0;
    q->a = 25.0f;
    q->c = 0.25f;
    q->b = 0;
    D_002629C8 = 0;
}


s32 D_00262A10[6] = { 0x0, 0x2FA, 0x584, 0x0, 0x2F7, 0x568 };

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
void func_001920B0(void* self, f32* arg);
void func_0016D040(C47* self, void* x);
void* func_0011E580(s32 a, void* b, s32 c, s32 d, s32 e);

void func_0016CF70(C47* self)
{
    f32 scratch[4];

    func_00124A48(self);
    func_00124DF8(self, 2, D_00262A10);
    self->f554 = func_001B6290(self->list550, self, -1, 1);
    self->f570 = (Sub47*)func_0015A838(self->world, 1, 0x8C, self);
    func_001920B0(self->f568, scratch);
    self->f56C = self->v140.z - scratch[2];
    if (self->f578 != -1)
    {
        func_0016D040(self, (void*)self->f578);
    }
    u64 m = 0x8000;
    s32 sh = 27;
    m <<= sh;
    self->flags538 |= m;
    self->f594 = func_0011E580(0x73, D_00275710, 0, 0x302, -1);
}

extern s32 D_002629C8;

void func_00127378(void* self, s32 kind);
s32 func_001526D0(void* a, void* b);
void func_00152470(void* list, void* item);
void func_00152600(void* table, void* self);

void func_0016DFE0(C2A* self, s32 kind)
{
    func_00127378(self, kind);
    switch (kind)
    {
    case 2:
        if (D_002629C8 != 0)
        {
            if (func_001526D0(&((C47*)D_002629C8)->list55C, self) != 0)
            {
                func_00152600(&((C47*)D_002629C8)->list55C, self);
            }
        }
        break;
    case 0xC:
        if (D_002629C8 != 0)
        {
            func_00152470(&((C47*)D_002629C8)->list55C, self);
        }
        break;
    case 0xD:
        if (D_002629C8 != 0)
        {
            func_00152600(&((C47*)D_002629C8)->list55C, self);
        }
        break;
    }
}

void func_0016E148(void);
void func_002040E8(void* a);

void func_0016E0B8(void)
{
    func_0016E148();
    func_002040E8(0);
    func_0016E1A0(&D_00262C70, 0, 0);
}

u16 D_00262A50[12] = { 0x2000, 0x8000, 0x1000, 0x4000, 0x0010, 0x0020, 0x0040, 0x0080, 0x0004, 0x0008, 0x0001, 0x0002 };

f32 func_0016F108(G262C70* self, s32 idx)
{
    if (self->keyA8 & D_00262A50[idx]) {
        if (self->f18 >= 4) {
            s32 v = 1;
            s32 b = self->fAE[idx];
            if (v < b) {
                v = b;
            }
            return (f32)v * 0.00392156886f;
        }
        return 1.0f;
    }
    return 0.0f;
}

void func_0016EC20(G262C70* self, s32 mask);

s32 func_0016EED0(G262C70* self)
{
    f32 c;
    f32 base;
    if (self->f2C == 0) {
        u16 fl = self->flags;
        if (fl & 0x1000) {
            func_0016EC20(self, 0x1000);
            self->f2C = -1;
        } else if (fl & 0x4000) {
            func_0016EC20(self, 0x4000);
            self->f2C = 1;
        } else if (0.8f <= self->f48) {
            f32 a = fabsf(self->f44);
            f32 b = fabsf(self->f40);
            if (b < a) {
                if (0.0f < self->f44) {
                    self->f2C = -1;
                } else {
                    self->f2C = 1;
                }
            }
        }
        if (self->f2C == 0) {
            goto done;
        }
        c = 0.33329999446868896f;
        self->f3C = c;
        base = D_00261868[0];
    } else {
        s32 v1 = 0;
        if (self->f2C < 0) {
            if (self->keyA8 & 0x1000) {
                v1 = 1;
            } else if (0.25f <= self->f48) {
                f32 a = fabsf(self->f44);
                f32 b = fabsf(self->f40);
                if (b < a) {
                    if (0.0f < self->f44) v1 = 1;
                }
            }
        } else {
            if (self->keyA8 & 0x4000) {
                v1 = 1;
            } else if (0.25f <= self->f48) {
                f32 a = fabsf(self->f44);
                f32 b = fabsf(self->f40);
                if (b < a) {
                    if (self->f44 < 0.0f) v1 = 1;
                }
            }
        }
        if (v1 == 0) {
            self->f2C = 0;
            goto done;
        }
        if (self->f38 <= D_00261858.f10) {
            f32 lo = 0.1f;
            f32 hi = 0.33329999446868896f;
            f32 t = (self->f3C + self->f3C) * 0.33333334f;
            if (t < lo) {
                c = lo;
            } else if (hi < t) {
                c = hi;
            } else {
                c = t;
            }
            self->f3C = c;
            base = D_00261858.f10;
        } else {
            return 0;
        }
    }
    self->f38 = base + c;
done:
    return self->f2C;
}

extern u16 D_00262D18;

void func_0016F188(ButtonCode* node)
{
    ButtonCode* p = g_buttonCodes;
    if (p != 0) {
        do {
            if (node == p) {
                return;
            }
            p = p->next;
        } while (p != 0);
    }
    node->next = g_buttonCodes;
    g_buttonCodes = node;
    if (D_00262D18 == *(u16*)node->buttons) {
        node->pos = 1;
    } else {
        node->pos = 0;
    }
}

void func_0016E148(void);

void func_0016E118(u32 mask)
{
    mask = ~mask;
    D_00262C6C = D_00262C6C & mask;
    func_0016E148();
}


void func_001BAC30(void* self);
void func_00124DF8(void* self, s32 id, void* table);
s32 func_001B6420(void* a, s32 b);
s32 D_002629D0[16] = { 0x0, 0x2EE, 0x550, 0x0, 0x2F8, 0x57C, 0x0, 0x2F9, 0x580, 0x0, 0x2FB, 0x588, 0x0, 0x2FC, 0x58C, 0x0 };

void func_0016CE80(C47* self)
{
    s32 k1 = 0x2EF;
    s32 k2 = 0x2F0;
    s32 i = 0;
    s32 off = 0;
    func_001BAC30(self);
    func_00124DF8(self, 5, D_002629D0);
    for (;;) {
        if (i >= self->list550->count) {
            return;
        }
        Entry47* e = (Entry47*)((u8*)self->list550->items + off);
        if (func_001B6420(self->list550, e->a) == k1 && func_001B6420(self->list550, e->b) == k2) {
            break;
        }
        off += 0x14;
        i++;
    }
    if (i < self->list550->count) {
        Entry47* p = (Entry47*)((u8*)(i * 0x14) + (s32)self->list550->items);
        self->f5A4 = p->ref->f34;
    }
}

void func_001DFD90(void* self);

struct Obj_16C470 {
    u8 pad0[0x88];
    s32 f88;
    u8 pad8C[0xA8 - 0x8C];
    s32 fA8;
    s32 fAC;
    u8 padB0[0xB4 - 0xB0];
    f32 fB4;
};

void func_0016C470(void* a0)
{
    Obj_16C470* self = (Obj_16C470*)a0;
    func_001DFD90(a0);
    self->f88 = 1;
    self->fA8 = 8;
    self->fAC = 9;
    self->fB4 = 3.4028234663852886e+38f;
}


void func_001F5C0C(u8* p, s32 a, s32 b);
s32 func_00204510(s32 a, s32 b, u8* c);
void func_0018D800(u8* dst, u8* src, s32 n);
void func_0016E738(G262C70* p, s32 a, s32 b, f32* c, f32* d, f32* e, u8* f, u8* g, f32* h, f32* i);
void func_0016F238(G262C70* p, s32 old);

s32 func_0016E940(G262C70* self)
{
    u8 buf[0x40];
    s32 res;
    u16 old;
    u16 cur;

    u8* b = buf;
    func_001F5C0C(b, 0, 0x40);
    res = 1;
    if (func_00204510(self->f04, self->f08, b) > 0) {
        old = self->keyA8;
        self->keyA8 = ~((buf[2] << 8) | buf[3]);
        if (self->f10 != 0) {
            if (self->f10 != buf[1]) res = 0;
        }
        self->f10 = buf[1];
        if (self->f18 == 4) {
            func_0018D800(self->fAE, buf + 8, 0xC);
        }
        cur = self->keyA8;
        self->flags = cur & ~old;
        self->hAC = old & ~cur;
        if (self->f18 >= 2) {
            func_0016E738(self, buf[6], buf[7], &self->f40, &self->f44, &self->f48, &self->f4C, &self->f4D, &self->x50, &self->a54[0].lo);
            func_0016E738(self, buf[4], buf[5], &self->f74, &self->f78, &self->f7C, &self->f80, &self->f81, &self->x84, &self->a88[0].lo);
        } else {
            self->f74 = self->f78 = self->f7C = self->f40 = self->f44 = self->f48 = 0.0f;
        }
        if (D_00261990 == 0 || D_00261990->stackCount == 0 || D_00261990->stack[0].ctl != &D_00261990->ctl454) {
            if ((self->keyA8 & 0xF000) != 0) {
                self->f40 = self->f44 = self->f48 = 0.0f;
                if ((self->keyA8 & 0x8000) != 0) {
                    self->f40 = -1.0f;
                } else if ((self->keyA8 & 0x2000) != 0) {
                    self->f40 = 1.0f;
                }
                if ((self->keyA8 & 0x1000) != 0) {
                    self->f44 = 1.0f;
                } else if ((self->keyA8 & 0x4000) != 0) {
                    self->f44 = -1.0f;
                }
                if (self->f40 * self->f44 != 0.0f) {
                    self->f40 = self->f40 * 0.8f;
                    self->f44 = self->f44 * 0.8f;
                }
                self->f48 = 1.0f;
            }
        }
        AdvanceButtonCodes(self, old);
        self->x20 = D_00261858.f10;
        if (self->keyA8 != 0 || self->f48 != 0.0f || self->f7C != 0.0f) {
            self->f24 = D_00261858.f10;
        }
    } else {
        if (D_00261868[0] - self->x20 >= 2.0f) res = 0;
    }
    return res;
}

void func_001B9338(C03* self, f32 t);
void func_00188850(const Vec02* tab, Mat3U* out, f32 v);
void func_001B9D10(C03* self, f32 t, Mat3U* out, void* data);

void func_0016D0C0(C47* self, f32 t)
{
    Mat3U buf;

    func_001B9338(self, t);
    if (self->w5D8 != 0) {
        return;
    }
    func_00188850(&D_00248D20, &buf, self->f5A0);
    func_001B9D10(self, t, &buf, self->sub5B0);
}

typedef void (*VFn_16D788)(C47* self, const void* arg);

void func_001B9AE0(C03* self, s32 a, s32 b, s32 c, s32 d);
void func_001920B0(void* arg, Vec3* out);

void func_0016D788(C47* self) {
    Vec3 v;
    func_001B9AE0(self, 3, 0, 3, 0);
    ((VFn_16D788*)self->desc)[36](self, &D_00248D30);
    ((VFn_16D788*)self->desc)[37](self, &D_00248D30);
    func_001920B0(self->f558->f7A4, &v);
    v.z = v.z + self->f56C;
    ((VFn_16D788*)self->desc)[33](self, &v);
}

struct Slot_2482D8 { u32 w[8]; };
extern const Slot_2482D8 D_002482D8[7] = {
    {0x239C1F4B, 0x4F1B6BCE, 0x332880C9, 0xDC1FC810, 0xB3EF7189, 0x239FB500, 0x332882F6, 0x4F1B486E},
    {0x674A1AEF, 0xEAAAB4AD, 0xCE2EF724, 0xB0B61237, 0x30E7A079, 0x67448204, 0xCE2EF564, 0xEAAA8C7D},
    {0x9FFD39A4, 0x92C0B086, 0x1904453E, 0x13763226, 0x52A098D3, 0x9FFD0941, 0x1904477F, 0x92C08E66},
    {0x631F4A84, 0xB9572D78, 0xA364788C, 0xBAF57CFC, 0xB7D7C188, 0x63176250, 0xA3647ACE, 0xB9571298},
    {0x816C657F, 0xB563A94D, 0x90993FD9, 0x2B5164CE, 0xA46DB733, 0x81696BC7, 0x90993D9A, 0xB563EFCD},
    {0xD4312CB4, 0xC376AE2A, 0x8D50D2C3, 0xC7A8D28C, 0x39A7CE66, 0xD422EB19, 0x8D50D087, 0xC3769B7A},
    {0x3909A2A2, 0xDA5D87C2, 0xC3446569, 0x59D126B9, 0x6943323B, 0x390995E6, 0xC344672C, 0xDA5DAE02}
};

s32 func_001BE980(void);
s32 func_001EAA70(void* a, s32 b);
void func_001BE728(S1BE728* slot);

void func_0016D928(C47* self)
{
    s32 r;

    if (self->f5C0 == 0) {
        return;
    }
    if (func_001BE980() != 0) {
        return;
    }
    r = func_001EAA70(0, 0x64);
    if (r >= 0x14) {
        return;
    }
    r = func_001EAA70(0, 6);
    func_001BE728((S1BE728*)((u8*)D_002482D8 + (r << 5)));
    self->f5CC = 1;
}

struct Obj_16EC98 { u8 pad0[0x28]; s32 f28; f32 f2C_unused; f32 f30; f32 f34; u8 pad1[8]; f32 f40; f32 f44; f32 f48; u8 pad2[0x5C]; u16 fA8; u16 fAA; };

void func_0016EC20(Obj_16EC98* self, s32 mask);
extern f32 D_00261868[];

s32 func_0016EC98(Obj_16EC98* self)
{
    f32 c;
    f32 base;
    if (self->f28 == 0) {
        u16 fl = self->fAA;
        if (fl & 0x8000) {
            func_0016EC20(self, 0x8000);
            self->f28 = -1;
        } else if (fl & 0x2000) {
            func_0016EC20(self, 0x2000);
            self->f28 = 1;
        } else if (0.8f <= self->f48) {
            f32 a = fabsf(self->f40);
            f32 b = fabsf(self->f44);
            if (b < a) {
                if (self->f40 < 0.0f) {
                    self->f28 = -1;
                } else {
                    self->f28 = 1;
                }
            }
        }
        if (self->f28 == 0) {
            goto done;
        }
        c = 0.33329999446868896f;
        self->f34 = c;
        base = D_00261868[0];
    } else {
        s32 v1 = 0;
        if (self->f28 < 0) {
            if (self->fA8 & 0x8000) {
                v1 = 1;
            } else if (0.25f <= self->f48) {
                f32 a = fabsf(self->f40);
                f32 b = fabsf(self->f44);
                if (b < a) {
                    if (self->f40 < 0.0f) v1 = 1;
                }
            }
        } else {
            if (self->fA8 & 0x2000) {
                v1 = 1;
            } else if (0.25f <= self->f48) {
                f32 a = fabsf(self->f40);
                f32 b = fabsf(self->f44);
                if (b < a) {
                    if (0.0f < self->f40) v1 = 1;
                }
            }
        }
        if (v1 == 0) {
            self->f28 = 0;
            goto done;
        }
        if (self->f30 <= D_00261858.f10) {
            f32 lo = 0.1f;
            f32 hi = 0.33329999446868896f;
            f32 t = (self->f34 + self->f34) * 0.33333334f;
            if (t < lo) {
                c = lo;
            } else if (hi < t) {
                c = hi;
            } else {
                c = t;
            }
            self->f34 = c;
            base = D_00261858.f10;
        } else {
            return 0;
        }
    }
    self->f30 = base + c;
done:
    return self->f28;
}


s32 func_00204590(s32 a, s32 b);
s32 func_002047F8(s32 a, s32 b, s32 c, s32 d);
s32 func_00204930(s32 a, s32 b, s32 c, s32 d);
s32 func_002046D0(s32 a, s32 b, s32 c, s32 d);
void func_001F5C0C(u8* p, s32 value, s32 size);
s32 func_00204AA8(s32 a, s32 b, u8* buf);
s32 func_00204CE8(s32 a, s32 b);
s32 func_00204D48(s32 a, s32 b);
s32 func_00204678(s32 a, s32 b);
s32 func_0016E940(G262C70* self);
void func_001A7B88(void* p);
void func_0016E630(G262C70* self, s32 mode, s32 n);

void func_0016E238(G262C70* self)
{
    u8 buf[16];
    if (self->f14 == 0)
    {
        return;
    }
    s32 ready = 0;
    s32 r = func_00204590(self->f04, self->f08);
    if (r == 6 || r == 2)
    {
        ready = 1;
    }
    s32 cur = self->f18;
    if (self->f14 != 3 && cur != 0 && 2.0f <= D_00261858.f10 - self->f1C)
    {
        r = 0;
    }
    if (cur != 0 && r == 0)
    {
        func_0016E630(self, 1, 0);
    }
    if (!ready)
    {
        return;
    }
    s32 two = 2;
    s32 mode = self->f14;
    s32 n = self->f18;
    switch (mode)
    {
    case 1:
        switch (n)
        {
        case 0:
        {
            s32 a = func_002047F8(self->f04, self->f08, 1, 0);
            if (a != 0)
            {
                s32 b = func_002047F8(self->f04, self->f08, 2, 0);
                if (b > 0)
                {
                    a = b;
                }
                if (a == 4 || a == 7)
                {
                    n = 1;
                    mode = 3;
                    if (b != 0)
                    {
                        mode = n;
                    }
                }
            }
            break;
        }
        case 1:
            mode = (func_00204930(self->f04, self->f08, 1, 3) == 1) ? two : n;
            break;
        case 2:
        {
            s32 count = func_002046D0(self->f04, self->f08, -1, 0);
            if (count != n
                || func_002046D0(self->f04, self->f08, 0, 1) != mode
                || func_002046D0(self->f04, self->f08, 0, 2) != n
                || func_002046D0(self->f04, self->f08, 0, 3) != 0
                || func_002046D0(self->f04, self->f08, 1, 1) != mode
                || func_002046D0(self->f04, self->f08, 1, 2) != mode
                || func_002046D0(self->f04, self->f08, 1, 3) != mode)
            {
                mode = 3;
                break;
            }
            func_001F5C0C(buf, 0xFF, 6);
            for (s32 i = 0; i < count; i++)
            {
                buf[i] = i;
            }
            if (func_00204AA8(self->f04, self->f08, buf) == 1)
            {
                mode = 2;
            }
            break;
        }
        case 3:
            if (func_00204CE8(self->f04, self->f08) != mode)
            {
                mode = 3;
                break;
            }
            if (func_00204D48(self->f04, self->f08) == 1)
            {
                mode = two;
            }
            break;
        }
        break;
    case 2:
        switch (func_00204678(self->f04, self->f08))
        {
        case 0:
            switch (self->f18)
            {
            case 1:
                n = 2;
                mode = 1;
                break;
            case 2:
                n = 3;
                mode = 1;
                break;
            case 3:
                n = 4;
                mode = 3;
                break;
            default:
                n = 0;
                break;
            }
            break;
        case 1:
            mode = 1;
            break;
        case 2:
            break;
        default:
            n = 0;
            break;
        }
        break;
    case 3:
        if (func_0016E940(self) != 0)
        {
            if (self->fC0 != 0 && self->f18 >= 3)
            {
                func_001A7B88(self->fBC);
            }
        }
        else
        {
            mode = 1;
            n = 0;
        }
        break;
    }
    func_0016E630(self, mode, n);
}

void func_001B93D8(void);

void func_0016C4E8(void)
{
    func_001B93D8();
}

struct Obj_16F478;
struct Vt_16F478 { u8 pad0[0x20]; void (*f20)(Obj_16F478* self, char* text); u8 pad1[0x14]; void (*f38)(Obj_16F478* self); };
struct Obj_16F478 { Vt_16F478* vt; };

extern Obj_16F478 D_0026EC70;
extern const char D_002483B8[24] = "@KFWHJGL";
extern const char D_0024A848[24] = "The password is: %s";

s32 func_001602A0(void);
void func_001E2138(char* dst, const u8* src);
s32 func_001E1FD0(char* dst, const u8* fmt, ...);
void func_001AA8B8(Obj_16F478* self, f32 v);

void func_0016F478(void)
{
    char text[0x40];
    char buf[0x10];

    if ((D_002623C0->f19D8 << 8 | D_002623C0->f19DC) == 0x400) {
        if ((func_001602A0() & 6) == 6) {
            if (D_002623C0->f19E8 == 99 && D_002623C0->f19E0 == 0) {
                char* p = buf;
                func_001E2138(p, (const u8*)D_002483B8);
                while (*p != 0) {
                    *p ^= 0x23;
                    p++;
                }
                func_001E1FD0(text, (const u8*)D_0024A848, buf);
                D_0026EC70.vt->f20(&D_0026EC70, text);
                func_001AA8B8(&D_0026EC70, 10.0f);
                D_0026EC70.vt->f38(&D_0026EC70);
            }
        }
    }
}

struct Advance_16F238 {
    static void Of(ButtonCode* node)
    {
        do {
            s32 index = node->pos;
            if (index < node->length) {
                if (D_00262C70.keyA8 == node->buttons[index])
                    node->pos = index + 1;
                else
                    node->pos = 0;
            }
            node = node->next;
        } while (node);
    }
};

void func_0016F238(G262C70* self, s32 value)
{
    u16 id = (u16)value;
    ButtonCode* head = g_buttonCodes;
    if (head == 0) return;
    if (self != &D_00262C70) return;
    u16 previous = self->keyA8;
    if (id == previous || previous == 0) return;
    Advance_16F238::Of(head);
    G261858* clock = &D_00261858;
    D_00262E00.time = clock->f10 + 1.0f;
}

// _GLOBAL_$I$ of the file, after the 16 bytes the linker left of two layout setters.
void func_0016C450(void)
{
    func_0016C360(1, 0xFFFF);
}
