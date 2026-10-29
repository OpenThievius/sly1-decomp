// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

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

struct Obj_16DF30 { u8 pad0[0x6E8]; s32 f6e8; u8 pad1[0x7A0 - 0x6EC]; s32 f7a0; u8 pad2[0x7A8 - 0x7A4]; s32 f7a8; };

void func_001400A8(void* self);

void func_0016DF30(Obj_16DF30* self)
{
    func_001400A8(self);
    self->f6e8 = 0;
    self->f7a0 = -1;
    self->f7a8 = -1;
}

struct Obj_16EC38 { u8 pad0[0x14]; s32 f14; s32 f18; u8 pad1[0xBC - 0x1C]; void* fBC; void* fC0; };

void func_001A7CE8(void* p);

void func_0016EC38(Obj_16EC38* self)
{
    if (self->fC0 == 0) return;
    if (self->f18 < 3) return;
    if (self->f14 != 3) return;
    func_001A7CE8(self->fBC);
}

struct Obj_16F7B0 { u8 pad0[0x21C8]; f32 f21c8; u8 pad1[0x2284 - 0x21CC]; f32 f2284; };

extern void* D_00262E10;
extern u8 D_00262E40[];

void func_001BAC30(void* self);
void func_00124DF8(void* self, s32 id, void* table);
void func_00159478(void* a, void* b);

void func_0016F7B0(Obj_16F7B0* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 0x97, D_00262E40);
    func_00159478((u8*)self + 0x2428, self);
    self->f2284 = -1.0f;
    self->f21c8 = -1.0f;
    D_00262E10 = self;
}

extern u8 D_00262A80[];
extern u8 D_00262AB8[];
extern u8 D_00262AF0[];
extern u8 D_00262B28[];
extern u8 D_00262B60[];
extern u8 D_00262B98[];
extern u8 D_00262BD0[];
extern u8 D_00262C08[];
extern u8 D_00262C48[];

void func_0016F188(void* entry);

void func_0016F588(void)
{
    func_0016F188(D_00262A80);
    func_0016F188(D_00262AB8);
    func_0016F188(D_00262AF0);
    func_0016F188(D_00262B28);
    func_0016F188(D_00262B60);
    func_0016F188(D_00262B98);
    func_0016F188(D_00262BD0);
    func_0016F188(D_00262C08);
    func_0016F188(D_00262C48);
}

struct Packet_0016DA00 {
    u8 pad0[0x8];
    s32 code;
};

void func_00127378(void* self, s32 type, void* packet);
void func_0016D490(void* self);
void func_0016D828(void* self);
void func_0016D928(void* self);
void func_0016DAC0(void* self, s32 mode);

void func_0016DA00(void* self, s32 type, Packet_0016DA00* packet)
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

struct Tune_0016DD10 {
    u8 pad0[0x31C];
    f32 f31C;
    f32 f320;
    f32 f324;
    f32 f328;
    f32 f32C;
    f32 f330;
    f32 f334;
};

void func_00123ED0(void* self);

void func_0016DD10(Tune_0016DD10* self)
{
    func_00123ED0(self);
    self->f31C = 2.25f;
    self->f320 = 2.0f;
    self->f324 = 0.8f;
    self->f328 = 4.0f;
    self->f32C = 0.5f;
    self->f330 = 1000.0f;
    self->f334 = 2000.0f;
}

void func_001289C0(void* self);
s32 func_0015A4F0(s32 a, s32 b, s32 c, void* d, s32 e, void* f);

void func_0016DD90(u8* self)
{
    func_001289C0(self);
    s32 r = func_0015A4F0(*(s32*)(self + 0x14), 0x201, 0x73, self, 0x10, self + 0x2D0);
    *(s32*)(self + 0x310) = r;
    if ((u32)r >= 0x11) {
        *(s32*)(self + 0x310) = 0x10;
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

struct Pair_16E1A0 { f32 lo; f32 hi; };

struct Stream_16E1A0 {
    u8 pad00[4];
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    f32 f1C;
    s32 f20;
    u8 pad24[0x2C];
    s32 f50;
    Pair_16E1A0 a54[4];
    u8 pad74[0x10];
    s32 f84;
    Pair_16E1A0 a88[4];
    s16 fA8;
    u8 padAA[0x12];
    void* fBC;
    s32 fC0;
};

void func_001F5C0C(void* p, s32 value, s32 size);
void* func_0018D4B0(s32 size);
void func_002042C8(s32 a, s32 b, s32 c);
void func_0016E630(Stream_16E1A0* self, s32 mode, s32 n);

void func_0016E1A0(Stream_16E1A0* self, s32 a, s32 b)
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

extern f32 D_00261858[];

void func_001A7B20(void* a, s32 b, s32 c);

void func_0016E630(Stream_16E1A0* self, s32 mode, s32 n)
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
    self->f1C = D_00261858[4];
}

struct FlagWord_16EC20 { u8 pad[0xAA]; u16 flags; };

void func_0016EC20(FlagWord_16EC20* self, u32 mask)
{
    u16 m = (u16)mask;
    self->flags &= (u16)~m;
}

struct Item_16D3F0 { u8 pad0[0x318]; s32 f318; };
struct Actor_16D3F0 { u8 pad0[0x7AC]; Item_16D3F0* f7AC; };
struct Sub_16D3F0 { u8 pad0[0x44]; s32 f44; };
struct Obj_1BF0D8;
struct Obj_16D3F0 { u8 pad0[0x558]; Actor_16D3F0* f558; u8 pad1[0x14]; Sub_16D3F0* f570; u8 pad2[0x48]; Obj_1BF0D8* f5BC; u8 pad3[0x10]; void* f5D0; s32 f5D4; };

void func_001A8AF8(void* p);
Obj_1BF0D8* func_001BEEF8(s32 kind);
void func_001BF0D8(Obj_1BF0D8* p);

void func_0016D3F0(Obj_16D3F0* self, Actor_16D3F0* x)
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
        self->f570->f44 = x->f7AC->f318;
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

struct Obj_16D9A8 { u8 pad0[0x5C4]; f32 f5C4; f32 f5C8; s32 f5CC; };

s32 func_001BE810(void* self);
void func_001BE8F8(void* self, s32 mode, f32 a, f32 b);

void func_0016D9A8(Obj_16D9A8* self)
{
    if (self->f5CC != 0) {
        if (func_001BE810(self) == 0) {
            self->f5CC = 0;
            func_001BE8F8(self, 0, self->f5C4, self->f5C8);
        }
    }
}

struct Timer_16F1F8 { s32 f0; s32 f4; void (*f8)(void*); void* fC; s32 f10; s32 f14; Timer_16F1F8* f18; };

extern Timer_16F1F8* D_00262DFC;

void func_0016F1F8(void)
{
    Timer_16F1F8* p = D_00262DFC;
    if (p != 0) {
        do {
            p->f10 = 0;
            p = p->f18;
        } while (p != 0);
    }
}

extern f32 D_00261868[];
extern f32 D_00262E00;

void func_0016F1F8(void);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);

void func_0016F2E0(void)
{
    if (D_00262E00 == 0.0f) {
        return;
    }
    if (!(D_00262E00 <= D_00261868[0])) {
        return;
    }
    Timer_16F1F8* best = 0;
    Timer_16F1F8** link = &D_00262DFC;
    Timer_16F1F8* p = D_00262DFC;
    while (p != 0) {
        if (p->f14 != 0) {
            *link = p->f18;
            p->f10 = 0;
            p->f14 = 0;
            p->f18 = 0;
        } else if (p->f10 < p->f4) {
            link = &p->f18;
        } else {
            if (best == 0 || best->f4 < p->f4) {
                best = p;
            }
            link = &p->f18;
        }
        p = *link;
    }
    if (best != 0) {
        func_001BFCD8(0x79, 0, 0, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f);
        best->f8(best->fC);
    }
    func_0016F1F8();
    D_00262E00 = 0.0f;
}

typedef void (*VFn_16DDE8)(void* self);
struct Obj_16DDE8 { VFn_16DDE8* vtbl; };

void func_00124A48(void* self);

void func_0016DDE8(Obj_16DDE8* self)
{
    func_00124A48(self);
    self->vtbl[7](self);
}

struct Obj_16DF68 { u8 pad0[0x14]; void* f14; u8 pad1[0x7A0 - 0x18]; s32 f7A0; s32 f7A4; s32 f7A8; s32 f7AC; };

void func_001249A8(void* self);
s32 func_0015A418(void* a0, s32 a1, s32 a2, void* a3);
s32 func_0015A838(void* a0, s32 a1, s32 a2, void* a3);

void func_0016DF68(Obj_16DF68* self)
{
    func_001249A8(self);
    if (self->f7A0 != -1) {
        self->f7A4 = func_0015A418(self->f14, 4, self->f7A0, self);
    } else {
        self->f7A4 = func_0015A838(self->f14, 2, 0x7E, self);
    }
    self->f7AC = func_0015A418(self->f14, 4, self->f7A8, self);
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

struct S_16EC88 { u8 pad[0x28]; s32 a; s32 b; };
void func_0016EC88(S_16EC88* p) { p->a = 0; p->b = 0; }

void func_001261C0(void);

void func_0016C508(void)
{
    func_001261C0();
}

struct Self_16D040 {
    u8 pad_00[0x14];
    void* f14;
    u8 pad_18[0x578 - 0x18];
    void* f578;
};

struct Res_16D040 {
    u8 pad_00[0x7AC];
    s32 f7AC;
};

void* func_0015A448(void* obj, void* id, void* owner);
void func_0016D3F0(Self_16D040* self, void* x);
void func_0016D788(Self_16D040* self);
void func_0016DAC0(Self_16D040* self, s32 mode);

void func_0016D040(Self_16D040* self, void* x)
{
    self->f578 = x;
    Res_16D040* p = (Res_16D040*)func_0015A448(self->f14, x, self);
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

struct Pair_16CE00 { f32 a; s32 b; f32 c; };

struct Obj_16CE00 {
    u8 pad0[0x578];
    s32 f578;
    u8 pad1[0x598 - 0x57C];
    s32 f598;
    u8 pad2[0x5B0 - 0x59C];
    Pair_16CE00 f5B0;
    u8 pad3[0x5C4 - 0x5BC];
    f32 f5C4;
    f32 f5C8;
};

void func_0016CE00(Obj_16CE00* self)
{
    func_001B7968(self);
    self->f578 = -1;
    self->f598 = -1;
    self->f5C4 = 3000.0f;
    self->f5C8 = 1000.0f;
    func_00152438((u8*)self + 0x55C, 0x7B0);
    Pair_16CE00* q = &self->f5B0;
    q->a = 25.0f;
    q->c = 0.25f;
    q->b = 0;
    D_002629C8 = 0;
}

struct Self_16CF70 {
    u8 pad_00[0x14];
    void* f14;
    u8 pad_18[0x148 - 0x18];
    f32 f148;
    u8 pad_14C[0x538 - 0x14C];
    u64 f538;
    u8 pad_540[0x550 - 0x540];
    void* f550;
    void* f554;
    u8 pad_558[0x568 - 0x558];
    void* f568;
    f32 f56C;
    void* f570;
    u8 pad_574[0x578 - 0x574];
    void* f578;
    u8 pad_57C[0x594 - 0x57C];
    void* f594;
};

extern u8 D_00262A10[];
extern void* D_00275710;

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
void func_001920B0(void* self, f32* arg);
void func_0016D040(Self_16CF70* self, void* x);
void* func_0011E580(s32 a, void* b, s32 c, s32 d, s32 e);

void func_0016CF70(Self_16CF70* self)
{
    f32 scratch[4];

    func_00124A48(self);
    func_00124DF8(self, 2, D_00262A10);
    self->f554 = func_001B6290(self->f550, self, -1, 1);
    self->f570 = (void*)func_0015A838(self->f14, 1, 0x8C, self);
    func_001920B0(self->f568, scratch);
    self->f56C = self->f148 - scratch[2];
    if ((s32)self->f578 != -1)
    {
        func_0016D040(self, self->f578);
    }
    u64 m = 0x8000;
    s32 sh = 27;
    m <<= sh;
    self->f538 |= m;
    self->f594 = func_0011E580(0x73, D_00275710, 0, 0x302, -1);
}

extern s32 D_002629C8;

void func_00127378(void* self, s32 kind);
s32 func_001526D0(void* a, void* b);
void func_00152470(void* list, void* item);
void func_00152600(void* table, void* self);

void func_0016DFE0(void* self, s32 kind)
{
    func_00127378(self, kind);
    switch (kind)
    {
    case 2:
        if (D_002629C8 != 0)
        {
            if (func_001526D0((u8*)D_002629C8 + 0x55C, self) != 0)
            {
                func_00152600((u8*)D_002629C8 + 0x55C, self);
            }
        }
        break;
    case 0xC:
        if (D_002629C8 != 0)
        {
            func_00152470((u8*)D_002629C8 + 0x55C, self);
        }
        break;
    case 0xD:
        if (D_002629C8 != 0)
        {
            func_00152600((u8*)D_002629C8 + 0x55C, self);
        }
        break;
    }
}

extern u8 D_00262C70[];

void func_0016E148(void);
void func_002040E8(void* a);
void func_0016E1A0(void* self, s32 a, s32 b);

void func_0016E0B8(void)
{
    func_0016E148();
    func_002040E8(0);
    func_0016E1A0(D_00262C70, 0, 0);
}

struct Obj_16F108 { u8 pad0[0x18]; s32 f18; u8 pad1[0xA8 - 0x1C]; u16 flags; u8 pad2[0xAE - 0xAA]; u8 fAE[1]; };

extern u16 D_00262A50[];

f32 func_0016F108(Obj_16F108* self, s32 idx)
{
    if (self->flags & D_00262A50[idx]) {
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

struct Obj_16EED0 { u8 pad0[0x2C]; s32 f2C; u8 pad1[0x8]; f32 f38; f32 f3C; f32 f40; f32 f44; f32 f48; u8 pad2[0x5C]; u16 fA8; u16 fAA; };

void func_0016EC20(Obj_16EED0* self, s32 mask);
extern f32 D_00261858[];

s32 func_0016EED0(Obj_16EED0* self)
{
    f32 c;
    f32 base;
    if (self->f2C == 0) {
        u16 fl = self->fAA;
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
            if (self->fA8 & 0x1000) {
                v1 = 1;
            } else if (0.25f <= self->f48) {
                f32 a = fabsf(self->f44);
                f32 b = fabsf(self->f40);
                if (b < a) {
                    if (0.0f < self->f44) v1 = 1;
                }
            }
        } else {
            if (self->fA8 & 0x4000) {
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
        if (self->f38 <= D_00261858[4]) {
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
            base = D_00261858[4];
        } else {
            return 0;
        }
    }
    self->f38 = base + c;
done:
    return self->f2C;
}
