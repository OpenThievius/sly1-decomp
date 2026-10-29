// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_171DD8 { u8 pad0[0x620]; s32 f620; s32 f624; s32 f628; s32 f62C; u8 pad1[0x8]; f32 f638; u8 pad2[0x54]; void* f690; u8 pad3[0x2C]; s32 f6C0; u8 pad4[0xAC4]; void* f1188; s32 f118C; u8 pad5[0x10A4]; void* f2234; u8 pad6[0x2D4]; s32 f250C; s32 f2510; };
struct Loc_171DD8 { u8 pad0[8]; f32 f8; };

s32 func_00171180(void* self);
s32 func_00171C80(void* self, void* p, s32 n);
void func_001719E8(void* self, s32 a, s32 b, s32 c, f32 k, void* d);
void func_001278A8(s32 a, s32 b, void* c, s32 d, void* e, s32 f, s32 g);
f32 func_001EA480(f32 a, f32 b);
s32 func_001B63C0(void* p, s32 n);
void func_001B6628(void* p, s32 n);

extern f32 D_00261860;

void func_00171DD8(Obj_171DD8* self)
{
    Loc_171DD8 loc;
    if (func_00171180(self) == 0) {
        if (self->f690 != 0) {
            func_001278A8(self->f6C0, 0, (u8*)self + 0x6A0, 0, &loc, 0, 0);
            loc.f8 = func_001EA480(loc.f8, 10.0f);
            self->f638 = self->f638 + loc.f8 * D_00261860;
        }
    }
    if (self->f250C == 0) return;
    u8* p1 = (u8*)self + 0x1190;
    f32 k = 5.0f;
    func_001719E8(self, self->f628, self->f620, self->f250C, k, p1);
    u8* p2 = (u8*)self + 0x1290;
    func_001719E8(self, self->f62C, self->f624, self->f2510, k, p2);
    if (func_00171C80(self, p1, self->f250C) != 0) {
        if (func_00171C80(self, p2, self->f2510) != 0) return;
    }
    if (self->f118C != 0) return;
    if (self->f1188 == 0) return;
    if (func_001B63C0(self->f1188, 0x148) >= 0) func_001B6628(self->f2234, 0x148);
    self->f118C = 1;
}

struct Obj_172AE0 { u8 pad0[0x21CC]; s32 f21cc; };

void func_001B9680(void* self);

void func_00172AE0(Obj_172AE0* self)
{
    func_001B9680(self);
    self->f21cc = 0;
}

extern u8* D_002623C0;

void func_001922E8(void* a, void* b);
void func_001D29C8(s32 id);

void func_00173708(void* a, void* b)
{
    func_001922E8(a, b);
    s32 id;
    if (b != 0) id = *(s32*)(D_002623C0 + 0x19FC);
    else id = -1;
    func_001D29C8(id);
}

extern f32 D_002637BC;
extern f32 D_002637C0;

void func_001C53A8(void* self, s32 flags, void* out);

struct Obj_170528 {
    u8 pad0[0x358];
    f32 f358;
    u8 pad1[0x368 - 0x35C];
    f32 f368;
    u8 pad2[0x2220 - 0x36C];
    s32 state;
};

struct Out_170528 {
    u8 pad0[0x30];
    f32 f30;
};

void func_00170528(Obj_170528* self, s32 flags, Out_170528* out)
{
    if (self->state == 4) {
        if (flags & 0x10) {
            f32 v;
            if (flags & 1) {
                v = -self->f368 * self->f358 * D_00261860 * D_002637BC;
            } else {
                v = -self->f368 * self->f358 * D_002637C0;
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

struct Obj_1705C8 {
    u8 pad0[0x224C];
    s32 f224C;
    s32 pad2250;
    s32 flags;
    s32 f2258;
    s32 f225C;
    s32 f2260;
    s32 f2264;
};

void func_001705C8(Obj_1705C8* self)
{
    s32 flags = self->flags;
    if (flags == 0) {
        return;
    }
    if (flags & 8) {
        self->flags = flags & ~8;
        self->f224C = self->f2264;
    }
    if (self->flags & 1) {
        func_00175170(self, self->f2258, self->f225C);
    }
    if (self->flags & 2) {
        func_001C61E0(self, self->f2260);
    }
    if (self->flags & 0x10) {
        func_001D4C98(self);
    }
}

extern f32 D_00274AD0[];

s32 func_001C5248(void* self);

struct Obj_170790 {
    u8 pad0[0x2220];
    s32 state;
};

struct Ent_170790 {
    u8 pad0[0x88];
    f32 f88;
    u8 pad1[0x10];
    s32 i9C;
};

s32 func_00170790(Obj_170790* self, Ent_170790* e, s32 idx)
{
    if (self->state != 0xD) {
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

struct Vec4_171F28 {
    f32 x, y, z, w;
} __attribute__((aligned(16)));

typedef void (*VFn_171F28)(void* self, void* out);

struct Obj_171F28 {
    VFn_171F28* vtbl;
    u8 pad0[0x226C - 4];
    f32 f226C;
    u8 pad1[0x2498 - 0x2270];
    s32 i2498;
};

void func_001EDEF0(void* a0, void* a1, void* a2, void* a3);

void func_00171F28(Obj_171F28* self, f32 unusedF12, f32 scale)
{
    Vec4_171F28 tmp = *(Vec4_171F28*)((u8*)self + 0x140);
    tmp.z = tmp.z - 75.0f;
    Vec4_171F28 out;
    void* a1;
    func_001EDEF0(&tmp, a1, &out, self);
    self->vtbl[36](self, &out);
    if (*(s32*)((u8*)self + 0x2220) != 4) {
        func_00175170(self, 2, 6);
        self->f226C = self->f226C * scale;
        if (scale == 0.0f) {
            self->i2498 = 0;
        }
    }
}

struct Obj_171FE0 {
    u8 pad0[0x2220];
    s32 state;
    u8 pad1[0x224C - 0x2224];
    s32 i224C;
    u8 pad2[0x239C - 0x2250];
    s32 i239C;
};

void func_00171FE0(Obj_171FE0* self)
{
    s32 st = self->state;
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
        self->i224C = 1;
        func_00175170(self, 2, 2);
    } else {
        s32 w = self->i239C;
        if (w >= 6) {
            return;
        }
        if (w < 4) {
            return;
        }
        func_00175170(self, 2, 2);
    }
}

struct __attribute__((aligned(16))) Quad_172B88 { s32 a, b, c, d; };
struct Unit_172B88 {
    void** vtbl;
    u8 pad0[0x21CC - 4];
    s32 count;
    Quad_172B88 slots[3];
    u8 pad1[0x2420 - 0x2200];
    f32 f2420;
};

void func_001B8540(void* self);
void func_001B8420(void* self, void* p, f32 f);

void func_00172B88(Unit_172B88* self)
{
    s32 i = 0;
    func_001B8540(self);
    if (self->count > 0) {
        Quad_172B88* p = self->slots;
        do {
            func_001B8420(self, p, self->f2420);
            i++;
            p++;
        } while (i < self->count);
    }
}

struct Unit_172BF8 {
    u8 pad0[0x25D8];
    void* table[5];
};

s32 func_00182FC8(void* p);

void* func_00172BF8(Unit_172BF8* self, s32* out)
{
    void* p = self->table[0];
    if (p != 0 && func_00182FC8(p) != 0) {
        *out = 0;
        return self->table[0];
    }
    p = self->table[2];
    if (p != 0 && func_00182FC8(p) != 0) {
        *out = 1;
        return self->table[2];
    }
    p = self->table[1];
    if (p != 0 && func_00182FC8(p) != 0) {
        *out = 2;
        return self->table[1];
    }
    p = self->table[3];
    if (p != 0 && func_00182FC8(p) != 0) {
        *out = 2;
        return self->table[3];
    }
    p = self->table[4];
    if (p != 0 && func_00182FC8(p) != 0) {
        *out = 1;
        return self->table[4];
    }
    return 0;
}

struct Unit_172EB8 {
    u8 pad0[0x2220];
    s32 state;
};

s32 func_00172EB8(Unit_172EB8* self)
{
    if (self->state == 3 || self->state == 0xD) {
        return 0;
    }
    return 3;
}

struct Obj_172530 {
    u8 pad0[0x610];
    void* f610;
    void* f614;
    u8 pad1[0x620 - 0x618];
    s32 f620;
    s32 f624;
    u8 pad2[0x11E0 - 0x628];
    s32 f11E0;
    u8 pad3[0x12E0 - 0x11E4];
    s32 f12E0;
    u8 pad4[0x2220 - 0x12E4];
    s32 f2220;
    u8 pad5[0x239C - 0x2224];
    s32 f239C;
};

void func_001C5438(Obj_172530* self);
void func_001C4618(Obj_172530* self, void* a1, void* a2, s32 a3, f32 f12, void* a4);

void func_00172530(Obj_172530* self)
{
    func_001C5438(self);
    if (self->f2220 == 6 && self->f239C == 7) {
        self->f12E0 = 0;
        goto clear;
    }
    {
        void* a1 = self->f610;
        if (a1 == 0) {
            self->f12E0 = 0;
            goto clear;
        }
        if (self->f614 == 0) {
            self->f12E0 = 0;
            goto clear;
        }
        f32 k = 6.0f;
        func_001C4618(self, a1, a1, self->f620, k, (u8*)self + 0x1190);
        func_001C4618(self, self->f614, self->f614, self->f624, k, (u8*)self + 0x1290);
    }
    return;
clear:
    self->f11E0 = 0;
}
