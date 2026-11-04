// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "c05.h"

struct Loc_171DD8 { u8 pad0[8]; f32 f8; };

s32 func_00171180(void* self);
s32 func_00171C80(void* self, void* p, s32 n);
void func_001719E8(void* self, s32 a, s32 b, s32 c, f32 k, void* d);
void func_001278A8(s32 a, s32 b, void* c, s32 d, void* e, s32 f, s32 g);
f32 func_001EA480(f32 a, f32 b);
s32 func_001B63C0(void* p, s32 n);
void func_001B6628(void* p, s32 n);

extern f32 D_00261860[];

void func_00171DD8(C07* self)
{
    Loc_171DD8 loc;
    if (func_00171180(self) == 0) {
        if (self->f690 != 0) {
            func_001278A8((s32)self->f6C0, 0, (u8*)self + 0x6A0, 0, &loc, 0, 0);
            loc.f8 = func_001EA480(loc.f8, 10.0f);
            self->f638 = self->f638 + loc.f8 * D_00261860[0];
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
    if (func_001B63C0(self->f1188, 0x148) >= 0) func_001B6628(self->f2234, 0x148);
    self->f118C = 1;
}

void func_001B9680(void* self);

void func_00172AE0(C07* self)
{
    func_001B9680(self);
    self->f21CC = 0;
}

extern u8* D_002623C0;

void func_001922E8(void* a, void* b);
void func_001D29C8(s32 id);

void func_00173708(C07* a, void* b)
{
    func_001922E8(a, b);
    s32 id;
    if (b != 0) id = *(s32*)(D_002623C0 + 0x19FC);
    else id = -1;
    func_001D29C8(id);
}

f32 D_002637BC = 2.0f;
extern f32 D_002637C0[3];

void func_001C53A8(void* self, s32 flags, void* out);

struct Out_170528 {
    u8 pad0[0x30];
    f32 f30;
};

void func_00170528(C07* self, s32 flags, Out_170528* out)
{
    if (self->f2220 == 4) {
        if (flags & 0x10) {
            f32 v;
            if (flags & 1) {
                v = -self->mass * self->gravity.z * D_00261860[0] * D_002637BC;
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

void func_001705C8(C07* self)
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
        func_00175170(self, self->f2258, self->f225C);
    }
    if (self->f2254 & 2) {
        func_001C61E0(self, self->f2260);
    }
    if (self->f2254 & 0x10) {
        func_001D4C98(self);
    }
}

extern f32 D_00274AD0[];

s32 func_001C5248(void* self);

struct Ent_170790 {
    u8 pad0[0x88];
    f32 f88;
    u8 pad1[0x10];
    s32 i9C;
};

s32 func_00170790(C07* self, Ent_170790* e, s32 idx)
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

struct Vec4_171F28 {
    f32 x, y, z, w;
} __attribute__((aligned(16)));

void func_001EDEF0(void* a0, void* a1, void* a2, void* a3);

void func_00171F28(C07* self, f32 unusedF12, f32 scale)
{
    Vec4_171F28 tmp = *(Vec4_171F28*)((u8*)self + 0x140);
    tmp.z = tmp.z - 75.0f;
    Vec4_171F28 out;
    void* a1;
    func_001EDEF0(&tmp, a1, &out, self);
    self->desc02()->m20(self, (Vec02*)&out);
    if (self->f2220 != 4) {
        func_00175170(self, 2, 6);
        self->f226C = self->f226C * scale;
        if (scale == 0.0f) {
            self->f2498 = 0;
        }
    }
}

void func_00171FE0(C07* self)
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
        func_00175170(self, 2, 2);
    } else {
        s32 w = self->f239C;
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
void func_001B8540(void* self);
void func_001B8420(void* self, void* p, f32 f);

void func_00172B88(C07* self)
{
    s32 i = 0;
    func_001B8540(self);
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

void* func_00172BF8(C07* self, s32* out)
{
    void* p = self->f25D8[0];
    if (p != 0 && func_00182FC8(p) != 0) {
        *out = 0;
        return self->f25D8[0];
    }
    p = self->f25D8[2];
    if (p != 0 && func_00182FC8(p) != 0) {
        *out = 1;
        return self->f25D8[2];
    }
    p = self->f25D8[1];
    if (p != 0 && func_00182FC8(p) != 0) {
        *out = 2;
        return self->f25D8[1];
    }
    p = self->f25D8[3];
    if (p != 0 && func_00182FC8(p) != 0) {
        *out = 2;
        return self->f25D8[3];
    }
    p = self->f25D8[4];
    if (p != 0 && func_00182FC8(p) != 0) {
        *out = 1;
        return self->f25D8[4];
    }
    return 0;
}

s32 func_00172EB8(C07* self)
{
    if (self->f2220 == 3 || self->f2220 == 0xD) {
        return 0;
    }
    return 3;
}

void func_001C5438(C07* self);
void func_001C4618(C07* self, void* a1, void* a2, s32 a3, f32 f12, void* a4);

void func_00172530(C07* self)
{
    func_001C5438(self);
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

void func_00172B08(C07* self)
{
    *(Quad_172B08*)&self->v21D0[1] = ((Inner_172B08*)self->f23D4)->q140;
    self->f21CC = 0;
    func_001BC088(self, 0, D_00261860[0]);
    if (self->f223C == 0) {
        *(Quad_172B08*)&self->v21D0[0] = *(Quad_172B08*)&self->v140;
        *(Quad_172B08*)&self->v21D0[2] = ((Inner_172B08*)self->f23D4)->q140;
        self->f21CC = 3;
        ((VFn_172B08)((void**)self->desc)[0xD8 / 4])(self);
    } else {
        self->f21CC = 0;
    }
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
void func_001C4848(C07* s, void* a, void* b, void* c);
void func_00125B70(C07* s, void* c, f32* out);
void func_00172078(C07* s, f32* buf, f32 t);
void func_00188B08(void* a, f32* b, f32* out);
void func_001CDD98(C07* s);
void func_001C49C8(C07* s, void* a, void* b);
void func_001C3028(void* a, void* b);
void func_001D62E0(C07* s, void* a, void* b);

void func_001725E0(C07* self, void* a, void* b)
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
        func_00125B70(self, b, out);
        out[16] *= 0.25f;
        for (i = 0; i < 4; i++)
        {
            func_00172078(self, buf, (f32)i * 0.25f);
            func_00188B08((u8*)((Aux_1725E0*)self->f61C) + 0x140, buf, out);
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

struct Params_2638A0 { f32 f0; f32 f4; f32 f8; f32 fC; s32 f10; s32 f14; };
extern Params_2638A0 D_002638A0;

f32 func_002058A0(f32 v, f32 m);
f32 func_001EA4B8(void* p, f32 a, f32 b, void* o, f32 c);

void func_001727B0(C07* self)
{
    if (self->f242C == 0.0f) {
        if (self->f2434 == 0.0f) {
            return;
        }
    }
    if (self->f242C != 0.0f) {
        *(f32*)((u8*)self + 0x2430) = self->f242C;
        self->f2434 = func_002058A0(self->f2434 + self->f242C * D_00261860[0], 6.2831855f);
    } else {
        if (self->f2434 == 0.0f) {
            return;
        }
        f32 r = func_001EA4B8(&D_002638A0, self->f2434, 6.2831855f, &self->f2430, D_00261860[0]);
        self->f2434 = r;
        if (r == 6.2831855f) {
            self->f2434 = 0.0f;
        }
    }
}

// NEAR: frame, saves, the vtable call and the branch tree match; the 0xD path loads its two floats into $f1/$f0 where retail uses $f0/$f1, so the shared store tail differs

struct Sub_170410 { u8 pad0[0x40]; s32 f40; };
typedef s32 (*VFn_170410)(C07* self, void* out);
struct Out_170410 { u8 pad0[0x94]; f32 f94; f32 f98; };

f32 D_00262E34 = 0.8f;
f32 D_00262E38 = 0.5f;
f32 D_002637B0 = 1.0f;
f32 D_002637B4 = 0.3f;
f32 D_002637B8 = 1.5f;

void func_00170410(C07* self, Out_170410* out)
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

// EXACT: callee func_001300E8 declared with a third parameter and called with k, which puts k in a2

struct __attribute__((aligned(16))) Quad_172898 { s32 a, b, c, d; };
struct Aux_172898 { u8 pad0[0x50]; void* f50; u8 pad1[0x554 - 0x54]; Contact03* f554; };

void func_001BC4D8(C07* a, void* b);
s32 func_001300E8(void* key, s32 kind, s32 extra);
void func_001C57C8(C07* a);
void func_00128018(Aux_172898* a, s32 b, void* c, void* d);
void func_001861E8(void* a, Contact03* b);
extern f32 D_0026185C[];
extern Quad_172898 D_00248D20;

void func_00172898(C07* self)
{
    ContactRow03* row;
    Contact03** slot;
    Contact03* n;
    Contact03* head = 0;
    func_001BC4D8(self, self->f151C);
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
                        if (other == 0 || func_001300E8(other, 0x46, k) == 0) {
                            *slot = n->next;
                            n->next = head;
                            head = n;
                        } else {
                            slot = &n->next;
                        }
                    } else if ((void*)n->end[1 - k].body == ((Aux_172898*)self->f2750) && ((s32 (*)(C07*, Contact03*))self->desc06()->m56)(self, n)) {
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
        self->f694 = D_0026185C[0];
        func_00128018(((Aux_172898*)self->f24A0), 0, self->f24B0, &self->v6A0);
        (*(Quad_172898*)&self->v6B0) = D_00248D20;
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
    func_001861E8(self->world, head);
}

struct Ent_172CF0
{
    u8 pad0[0x18];
    Ent_172CF0* f18;
    u8 pad1C[0x3CC - 0x1C];
    f32 f3CC;
    u8 pad3D0[0x3F0 - 0x3D0];
    s32 f3F0;
    u8 pad3F4[4];
    s32 f3F8;
    u8 pad3FC[0x538 - 0x3FC];
    u64 f538;
};

void func_001C5C10(C07* a, Ent_172CF0* b, void* c, void* d);
void func_001C4790(C07* a, Ent_172CF0* b, void* c, void* d);
void func_001879C0(Ent_172CF0* a, f32 f, void* b, void* c, s32 d, s32 e, s32 g, void* h);
void func_00186BA8(void* a, Ent_172CF0* b, void* c, void* d, void* e, void* f);

void func_00172CF0(C07* self, Ent_172CF0* a1, void* a2, void* a3, void* a4, void* a5)
{
    s32 idx;
    Ent_172CF0* v;
    Ent_172CF0* cur;

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
    v = (Ent_172CF0*)func_00172BF8(self, &idx);
    if (v)
    {
        for (cur = a1; cur; cur = cur->f18)
        {
            if (*((u8*)cur + idx + 0x2B0))
            {
                if (a1->f538 & (1ULL << 40))
                {
                    func_001879C0(a1, a1->f3CC, (u8*)a1 + 0x140, v, v->f3F0, v->f3F8, 0, (u8*)self + 0x2670);
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

f32 D_002637C0[3] = { 0.1f, 2.0f, 0.0f };
Params_2638A0 D_002638A0 = { 50.0f, 0.0f, 0.25f, 0.0f, 0x16F, 0x170 };
