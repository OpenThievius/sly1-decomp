// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_177828 {
    u8 pad0[0x4B8];
    s32 f4B8;
    u8 pad1[0x2BD8 - 0x4BC];
    s32 f2BD8;
};

void func_00177828(Obj_177828* self, s32 value)
{
    self->f2BD8 = value;
    self->f4B8 = 0;
}

void func_001777F8(void)
{
}

void func_00175170(void* self, s32 mode, s32 count);

void func_00177800(void* self, s32 flag)
{
    func_00175170(self, flag ? 11 : 0, -1);
}

struct Keyed_177968 { u8 pad0[0x14]; f32 key; };

s32 func_00177968(Keyed_177968* a, Keyed_177968* b)
{
    s32 r = -1;
    if (a->key > b->key) r = 1;
    return r;
}

struct Ctx_177E20 { u8 pad0[0x2220]; s32 kind; u8 pad1[4]; s32 sub; };

extern u8* D_00261990;
s32 func_001493A0(u8* p);

s32 func_00177E20(Ctx_177E20* self)
{
    if (self->kind == 12 && self->sub == 0x22) return 0;
    return func_001493A0(D_00261990 + 0x454) == 0;
}

void func_001924C8(void* self, s32 mode);
void func_00175170(void* self, s32 a, s32 b);

void func_00177E70(void* self, s32 mode)
{
    func_001924C8(self, mode);
    switch (mode) {
    case 0:
        (void)func_00175170(self, 9, 0x1C);
        break;
    case 1:
        (void)func_00175170(self, 9, 0x1D);
        break;
    }
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

extern u8 D_00275BC0[];

struct Global_177F98 {
    u8 pad0[0x324];
    void* f324;
};

extern Global_177F98 D_002701F8;

struct Node_177F98 {
    u8 pad0[0x2D0];
    s32 kind;
};

struct Obj_177F98 {
    u8 pad0[0x2220];
    s32 state;
    u8 pad1[0x30];
    s32 flags;
    s32 f2258;
    s32 f225C;
    u8 pad2[0x2BD0 - 0x2260];
    void* f2BD0;
};

void func_001E9498(void* a, void* b);

void func_00177F98(Obj_177F98* self, Node_177F98* node)
{
    if ((u32)(node->kind - 1) < 2) {
        D_002701F8.f324 = node;
        func_001E9498(D_00275BC0, &D_002701F8);
        return;
    }
    if (self->state != 0xC) {
        s32 f = self->flags;
        self->f225C = 0x21;
        self->f2BD0 = node;
        self->f2258 = 0xC;
        self->flags = f | 1;
    }
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
struct Hold_177838 {
    Head_177838* head;
    u8 pad4[0x14];
    Node_177838* first;
};
struct Q_177838 {
    s32 pad0;
    Node_177838* hold;
    s32 pad8;
    s32 out;
    s32 kind;
};

Node_177838* func_00177838(Q_177838* q, s32 n, Node_177838** list) {
    Node_177838* node;
    if (q->hold->vt->flags & 1) {
        node = q->hold;
    } else {
        node = q->hold->next;
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

struct Self_177EE0 { u8 pad0[0x2220]; s32 mode; u8 pad1[0x2BD0 - 0x2224]; s32 f2BD0; };
struct Other_177EE0 { u8 pad0[0x2D0]; s32 f2D0; };
extern s32 D_00275BC4;

void func_00177EE0(Self_177EE0* self, Other_177EE0* other, s32* out)
{
    s32 v;
    switch (self->mode) {
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
        out[1] = self->f2BD0 == (s32)other;
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
