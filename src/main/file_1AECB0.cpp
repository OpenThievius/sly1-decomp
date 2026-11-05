// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"

#include "list_iter.h"
#include "c30.h"
#include "c05.h"
#include "c6c.h"
#include "globals.h"
#include "s124df8.h"

void func_001B7968(C03* self);
void func_001B93F8(C03* self);
Node30* func_00129CA8(C30* self);
// Slot 17 takes the frame time (Desc01::m11); func_001AEFA0 ignores it, but func_001AF5C8's call
// passes it (retail's frame shows the argument live).
void func_001AEFA0(C30* self, f32 dt);

S124DF8 D_002744B8[2] = { { 2, 0x28A, 0xAE4 }, { 2, 0x28B, 0xAE8 } };

void func_001BAC30(C03* self);
void func_00124DF8(void* self, s32 n, void* table);

s32 func_001833F0(void* key, s32 item);
s32 func_001300E8(void* key, s32 item);

extern f32 D_00261858[];
s32 D_002744D0 = 0;

void func_0015FCD8(void* self, void* p);
void func_00152470(void* list, void* item);
void func_00152600(void* list, void* item);

void func_00124A48(C02* self);
void* func_00183058(void* a, void* b, void* c);

s32 func_001AEE50(C30* self, void* key);
s32 func_00160D10();

extern f32 D_0026185C[];
void func_00123AB0(void* object, s32 mode);
void func_001837E0(C02* self, s32 a, s32 b, s32 c);

// The target a C30 follows (+0x550): its state and the time it changed.
struct Rec_1B0EE0 {
    u8 pad0[0x550];
    s32 f550;
    f32 f554;
};

S124DF8 D_002744D8[2] = {
    { 2, 0x28C, 0x5D0 },
    { 2, 0x28D, 0x5D4 },
};
void func_001B9AE0(C03* self, s32 a1, Vec02* a2, s32 a3, Vec02* a4);

struct Sub_1B04D0 {
    u8 pad0[0x44];
    s32 x44;
};

s32 func_001925F0(void);

void func_001BF788(void* snd, s32 n);
void func_001BFCD8(s32 kind, void* snd, void* owner, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_00155F90(void* p);

struct Cfg_1B0360 {
    f32 pad0;
    f32 f4;
    f32 f8;
};

void func_001D7098(void* buf, s32 n, void* self);

void func_001B46E0(s32 a, s32 frame);

struct Node_1B1070 {
    u8 pad0[0x44];
    s32 f44;
};

struct Clk_1B1070 { f32 t; };

void func_001B1070(C32* self, s32 arg);
void func_001AEF68(C30* self);
s32 func_001AEF00(C30* o, void* p);
void func_001AF508();
void func_001B1898(C33* self);

void func_001AECB0(C30* a0) {
    func_001B7968(a0);
    a0->f554 = 0;
    a0->state = -1;
}

void func_001AECE0(C30* self, s32 value)
{
    self->f550 = (void*)value;
}

void func_001AECE8(C30* self, s32 state)
{
    if (self->state == state) return;
    if (self->state == 1 && state == 2) {
        if (self->f550 != 0) {
            func_00123AB0(self->f550, 0);
            if (self->state != 1) state = self->state;
        }
        func_001837E0(self, 2, 0, 0);
    }
    self->state = state;
    self->f55C = D_0026185C[0];
}

s32 func_001AED78(C30* self, void* value)
{

    if (self->f5B4 != 0) {
        return 1;
    }
    if (func_001AEE50(self, value) != 0) {
        return 0;
    }
    for (s32 i = 0; i < self->ids564.count; i++) {
        if (func_001833F0(value, self->ids564.items[i]) != 0) {
            return 1;
        }
    }
    for (s32 i = 0; i < self->ids58C.count; i++) {
        if (func_001300E8(value, self->ids58C.items[i]) != 0) {
            return 1;
        }
    }
    return 0;
}

s32 func_001AEE50(C30* self, void* key)
{
    for (s32 i = 0; i < self->ids578.count; i++) {
        if (func_001833F0(key, self->ids578.items[i]) != 0) {
            return 1;
        }
    }
    for (s32 i = 0; i < self->ids5A0.count; i++) {
        if (func_001300E8(key, self->ids5A0.items[i]) != 0) {
            return 1;
        }
    }
    return 0;
}

s32 func_001AEF00(C30* o, void* p)
{
    if (p == 0) return 0;
    if (o->f5B4 == 0 && o->ids564.count == 1 && o->ids58C.count == 0 && func_001833F0(p, o->ids564.items[0]) != 0) return 1;
    return 0;
}

void func_001AEF68(C30* self)
{
    Node30* node = func_00129CA8(self);

    if (node != 0) {
        self->f5CC = node->f18.f;
        node->f18.w = 0;
        self->f5C8 = node;
    }
}

void func_001AEFA0(C30* self)
{
    func_001B93F8(self);
    Node30* sink = self->f5C8;
    if (sink != 0) {
        C07* g = D_00262E10;
        if (g != 0) {
            if (g->f2220 != 4) {
                sink->f18.f = self->f5CC;
                self->f5C8 = 0;
                *(s32*)&self->f5CC = 0;
            }
        }
    }
}

void func_001AF000(C30* self, s32 value)
{
    u32 n = self->ids564.count;
    if (n < 4) {
        self->ids564.items[n] = value;
        self->ids564.count = n + 1;
    }
}

void func_001AF028(C30* self, s32 item)
{
    s32 n = self->ids578.count;
    if ((u32)n < 4) {
        self->ids578.items[n] = item;
        self->ids578.count = n + 1;
    }
}

void func_001AF050(C30* self, s32 item)
{
    s32 n = self->ids58C.count;
    if ((u32)n < 4) {
        self->ids58C.items[n] = item;
        self->ids58C.count = n + 1;
    }
}

void func_001AF078(C30* q, u32 value)
{
    u32 n = q->ids5A0.count;
    if (n < 4) {
        q->ids5A0.items[n] = value;
        q->ids5A0.count = n + 1;
    }
}

void func_001AF0A0(C31* self)
{
    func_001AECB0(self);
    self->fB04 = 1.0f;
}

void func_001AF0D0(C31* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 2, D_002744B8);
}

ASM_FUNC(func_001AF108);

void func_001AF3B8(C31* self)
{
    Group31* src = &self->groups[0];
    func_00124A48(self);
    for (s32 i = 0; i < self->groupCount; i++) {
        Group31* g = &self->groups[i];
        C01* c = g->child;
        c->desc->m03(c);
        if (i != 0) {
            {
                s32 j;
                for (j = 0; j < src->count; j++) {
                    Entry31* s = src->items + j;
                    Entry31* d = g->items + j;
                    C01* o = (C01*)func_00183058(s->obj, self->world, self);
                    d->obj = o;
                    if (o->desc->m0F != 0) {
                        o->desc->m0F(o);
                    }
                    o = d->obj;
                    o->desc->m10(o);
                    d->value = s->value;
                }
            }
            g->count = src->count;
        }
    }
    self->fB00 = func_001AEF00(self, (void*)D_00262E10);
    self->desc30()->m4D(self, self->f560);
}

void func_001AF508()
{
    ListFrame frame;
    s32 count = 0;
    C31* n = (C31*)D_00275710->list1CA8.head;
    while (n != 0) {
        s32 t = count + 1;
        count = (n->state != 8) ? t : count;
        n = n->listNext;
    }
    if (count != 0) {
        s32 idx = 0;
        n = (C31*)D_00275710->list1CA8.head;
        while (n != 0) {
            if (n->state != 8) {
                n->fAFC = D_00261858[1] + (0.03333333507180214f / (f32)count) * (f32)idx;
                idx++;
            }
            n = n->listNext;
        }
    }
    D_002744D0 = 0;
}

void func_001AF5C8(C31* self, f32 amount)
{
    s32 cmd;
    f32 v;
    f32 hi;
    f32 lo;

    func_001AEFA0(self, amount);
    v = self->fB04 + amount * self->fB08;
    hi = 1.0f;
    lo = 0.0f;
    if (v < lo)
        v = lo;
    else if (hi < v)
        v = hi;
    self->fB04 = v;
    if (D_002744D0)
        func_001AF508();
    cmd = self->state;
    switch (cmd) {
    case 0:
        if (self->f5B8 < D_0026185C[0] - self->f55C)
            cmd = 1;
        if (self->desc30()->m48)
            self->desc30()->m48(self, &cmd);
        break;
    case 2:
        cmd = 3;
        if (self->desc30()->m48)
            self->desc30()->m48(self, &cmd);
        break;
    case 3:
        if (self->f5BC < D_0026185C[0] - self->f55C) {
            if (self->f554 == 0) {
                cmd = 8;
                break;
            }
            if (self->f554 != 1)
                break;
            cmd = 4;
            if (self->desc30()->m48)
                self->desc30()->m48(self, &cmd);
            break;
        }
        if (self->desc30()->m48)
            self->desc30()->m48(self, &cmd);
        break;
    case 4:
        if (self->f5B8 < D_0026185C[0] - self->f55C)
            cmd = 5;
        if (self->desc30()->m48)
            self->desc30()->m48(self, &cmd);
        break;
    case 1:
    case 5:
    case 6:
        if (self->desc30()->m48)
            self->desc30()->m48(self, &cmd);
        break;
    case 7:
        if (self->fAEC < D_0026185C[0] - self->f55C)
            cmd = 8;
        else if (self->desc30()->m48)
            self->desc30()->m48(self, &cmd);
        break;
    case 8:
        break;
    }
    self->desc30()->m4D(self, cmd);
}

void func_001AF7A8(C31* self, void* p)
{
    func_0015FCD8(self, p);
    if (p != 0) {
        if (self->flagAF8 != 0) {
            func_00152600(&self->world->list1CA8, self);
            self->flagAF8 = 0;
        }
    } else {
        func_00152470(&self->world->list1CA8, self);
        self->flagAF8 = 1;
    }
    D_002744D0 = 1;
}

ASM_FUNC(func_001AF820);

s32 func_001AFAF8(C30* a0, C03* a1)
{
    u64 m = 0x8000;
    m <<= 28;
    if ((a1->flags538 & m) != 0 || a1->root == a0->root || func_001AEE50(a0, a1) != 0) {
        return 0;
    }
    if ((void*)a1 == (void*)D_00262E10 && ((C07*)a1)->f2220 == 6 && ((C07*)a1)->f239C == 3) {
        if ((func_00160D10() & 0x12000) != 0) {
            return 0;
        }
    }
    s64 t = (s64)a1->flagsHi;
    return ((s32)t ^ 1) & 1;

}

INCLUDE_RODATA(jtbl_0024CFF0);
ASM_FUNC(func_001AFBB0);

void func_001B00E8(C31* self, s32 flag)
{
    s32 m = 5;
    self->f554 = flag;
    if (!flag) {
        m = 1;
    }
    self->desc30()->m4D(self, m);
}

void func_001B0120(C31* self)
{
    if (self->state == 8) {
        return;
    }
    s32 m = 7;
    if (!self->f554) {
        m = 3;
    }
    self->desc30()->m4D(self, m);
}

void func_001B0160(C31* self)
{
    if (self->state < 3) {
        if (self->state >= 0) {
            self->desc30()->m4D(self, 3);
        }
    }
    self->f554 = 1;
}

void func_001B01B0(C31* self, s32 s)
{
    s32 st = self->state;
    if (st == s) return;
    if (st == -1 || st == 8) {
        f32 z = 0.0f;
        f32 a = 1000.0f, c = 100.0f, d = 0.4f;
        func_001BFCD8(0x1A, &self->f5C4, self, 0, a, c, d, z, z, 0, 0);
    }
    switch (s) {
    case 3:
    case 7:
        for (s32 i = 0; i < self->groupCount; i++) {
            Group31* e = &self->groups[i];
            for (s32 j = 0; j < e->count; j++) func_00155F90(e->items[j].obj);
        }
        break;
    case 8: {
        f32 v;
        if (self->f554 == 0) v = self->f5BC; else v = self->fAEC;
        func_001BF788(self->f5C4, (s32)v * 1000);
        self->desc->m03(self);
        D_002744D0 = 1;
        break;
    }
    default:
        break;
    }
    func_001AECE8(self, s);
}

f32 func_001B0360(C31* o, Cfg_1B0360* c)
{
    f32 s = c->f4;
    f32 r;
    f32 m;
    f32 t;
    switch (o->state) {
    case 0:
    case 4: {
        f32 t0 = o->f5B8;
        if (t0 == 0.0f) {
            r = o->fB04;
        } else {
            f32 q = (D_0026185C[0] - o->f55C) / t0;
            m = o->fB04;
            if (q < 0.0f)
                r = 0.0f;
            else if (m < q)
                r = m;
            else
                r = q;
        }
        break;
    }
    case 1:
    case 2:
    case 5:
    case 6:
        r = o->fB04;
        break;
    case 3:
    case 7:
        t = o->f554 == 0 ? o->f5BC : o->fAEC;
        if (t == 0.0f) {
            r = 0.0f;
        } else {
            f32 m = o->fB04;
            r = 1.0f - (D_0026185C[0] - o->f55C) / t;
            if (r < 0.0f)
                r = 0.0f;
            else if (m < r)
                r = m;
        }
        s = c->f8;
        break;
    case 8:
        r = 0.0f;
        break;
    }
    return s * r;
}

void func_001B0470(C31* self, f32 x)
{
    self->fB08 = -1.0f / x;
}

void func_001B0488(C31* p, f32 x) { p->fB08 = 1.0f / x; }

void func_001B04A0(C32* o)
{
    func_001AECB0(o);
    o->state5D8 = -1;
}

void func_001B04D0(C32* self)
{
    func_00124A48(self);
    func_00124DF8(self, 2, D_002744D8);
    if (self->f5D0 == 0) {
        self->f5D0 = self;
    }
    if (self->f5D4 == 0) {
        self->f5D4 = self->world->f1D14;
    }
    if (self->f200 != 0) {
        ((Sub_1B04D0*)self->f200)->x44 = 0;
    }
    u64 m = 0x8000;
    m <<= 28;
    self->flags538 |= m;
    func_001B9AE0(self, 3, 0, 3, 0);
    self->desc30()->m4D(self, self->f560);
}

void func_001B0578(C32* self) {
    s32 st;
    s32 s1;
    func_001AEFA0(self);
    st = self->state;
    switch (self->state) {
    case 0:
        if (self->f5B8 < D_0026185C[0] - self->f55C) st = 1;
        break;
    case 2:
        st = 3;
        break;
    case 3:
        if (self->f5BC < D_0026185C[0] - self->f55C) st = 8;
        break;
    case 4:
        if (self->f5B8 < D_0026185C[0] - self->f55C) st = 5;
        break;
    case 1:
    case 5:
        if (self->desc30()->m48) {
            self->desc30()->m48(self, &st);
        }
        goto tail;
    case 6:
        s1 = self->state5D8;
        switch (s1) {
        case 0:
            if (D_00262E10 && D_00262E10->desc06()->m4B(D_00262E10, 2)) {
                s1 = 2;
            } else if (self->f5E0 < D_0026185C[0] - self->f5DC) {
                if (D_00262E10) {
                    u8 buf[16];
                    func_001D7098(buf, 2, self);
                    if (D_00262E10->desc06()->m4C(D_00262E10, buf)) {
                        s1 = 1;
                        func_001AEF68(self);
                    }
                } else {
                    s1 = 1;
                }
            }
            break;
        case 1:
            if (self->f5E4 < D_0026185C[0] - self->f5DC) s1 = 2;
            break;
        case 2:
            if (self->f5E8 < D_0026185C[0] - self->f5DC) {
                s1 = -1;
                st = 5;
            }
            break;
        }
        func_001B1070(self, s1);
        goto tail;
    case 7:
        if (self->f5BC < D_0026185C[0] - self->f55C) st = 8;
        break;
    case 8:
        if (self->f5C0 == 0) {
            switch (self->f554) {
            case 0: st = 0; break;
            case 1: st = 4; break;
            }
        }
        goto tail;
    }
tail:
    self->desc30()->m4D(self, st);
}

INCLUDE_RODATA(jtbl_0024D070);
ASM_FUNC(func_001B0838);

s32 func_001B0BD8() { return 1; }

s32 func_001B0BE0(C30* self, C03* other)
{
    if ((other->flags538 & (1UL << 43)) != 0 || (s32)other->root == func_001925F0() || other->root == self->root || func_001AEE50(self, other) != 0) {
        return 0;
    }
    s64 t = (s64)other->flagsHi;
    return ((s32)t ^ 1) & 1;
}

ASM_FUNC(func_001B0C68);

void func_001B0EA8(C32* self, s32 value)
{
    s32 m = 5;
    self->f554 = value;
    if (!value) {
        m = 1;
    }
    self->desc30()->m4D(self, m);
}

void func_001B0EE0(C32* self)
{
    if (self->state != 8) {
        self->desc30()->m4D(self, self->f554 == 0 ? 3 : 7);
    }
    Rec_1B0EE0* r = (Rec_1B0EE0*)self->f550;
    if (r != 0) {
        if (r->f550 == 1) {
            if (__builtin_fabsf(D_0026185C[0] - r->f554) < 0.2f) {
                self->f5C0 = r->f550;
            }
        }
    }
}

void func_001B0F70(C32* o)
{
    if (o->f554 == 0) {
        o->f554 = 1;
        if (o->state != 8) {
            o->desc30()->m4D(o, 3);
        }
    }
}

void func_001B0FC0(C32* self, s32 s)
{
    if (self->state != s) {
        switch (self->state) {
        case -1: case 0: case 1: case 2: case 3: case 4: case 5: case 7:
            break;
        case 6:
            func_001B1070(self, -1);
            break;
        case 8:
            self->f5C0 = 0;
            break;
        }
        switch (s) {
        case 6:
            func_001B1070(self, 0);
            break;
        case 0: case 1: case 2: case 3: case 4: case 5: case 7: case 8:
            break;
        }
        func_001AECE8(self, s);
    }
}

void func_001B1070(C32* self, s32 arg)
{
    if (self->state5D8 == arg) return;
    switch (self->state5D8) {
    case -1:
        break;
    case 0:
        break;
    case 1:
        func_001BF788(self->f5C4, 0);
        break;
    case 2:
        break;
    }
    switch (arg) {
    case -1:
        break;
    case 0:
        if (self->f200 != 0) {
            ((Node_1B1070*)self->f200)->f44 = 4;
        }
        break;
    case 1:
        func_001BFCD8(0x1B, &self->f5C4, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        break;
    case 2:
        if (self->f200 != 0) {
            ((Node_1B1070*)self->f200)->f44 = 0;
        }
        break;
    }
    self->state5D8 = arg;
    self->f5DC = (*(Clk_1B1070*)D_0026185C).t;
}

void func_001B1158(C33* self)
{
    func_001AECB0(self);
    self->animB.first = -1;
    self->animB.last = -1;
    self->animC.first = -1;
    self->animC.last = -1;
    self->animA.first = -1;
    self->animA.last = -1;
    self->blinkFrame = -1;
}

void func_001B11A0(C33* self)
{
    func_00124A48(self);
    for (s32 i = 0; i < self->elemCount; i++) {
        Elem02* it = self->elems[i];
        if (it->kind == 1 && it->f14 != 0) {
            self->f610 = it;
            break;
        }
    }
    self->desc30()->m4D(self, self->f560);
}

void func_001B1238(C33* self)
{
    s32 state;

    func_001AEFA0(self);
    state = self->state;
    switch (state) {
    case 0:
        if (self->f5B8 < D_0026185C[0] - self->f55C) {
            state = 1;
        }
        break;
    case 1:
        if (0.0f <= self->f608) {
            if (self->f608 < D_0026185C[0] - self->f55C) {
                state = 3;
                break;
            }
        }
        if (self->desc30()->m48 != 0) {
            self->desc30()->m48(self, &state);
        }
        break;
    case 3:
        if (self->f5BC < D_0026185C[0] - self->f55C) {
            state = 8;
        }
        break;
    case 4:
        if (self->f5B8 < D_0026185C[0] - self->f55C) {
            state = 5;
        }
        break;
    case 5:
        if (0.0f <= self->f608) {
            if (self->f608 < D_0026185C[0] - self->f55C) {
                state = 7;
                break;
            }
        }
        if (self->desc30()->m48 != 0) {
            self->desc30()->m48(self, &state);
        }
        break;
    case 7:
        if (self->f5BC < D_0026185C[0] - self->f55C) {
            state = 8;
        }
        break;
    case 8:
        if (self->f5C0 == 0) {
            if (self->f60C < D_0026185C[0] - self->f55C) {
                switch (self->f554) {
                case 0:
                    state = 0;
                    break;
                case 1:
                    state = 4;
                    break;
                }
            }
        }
        break;
    }
    self->desc30()->m4D(self, state);
    func_001B1898(self);
}

INCLUDE_ASM(func_001B1438);

void func_001B15D0(C33* self, s32 mode)
{
    self->f554 = mode;
    self->desc30()->m4D(self, mode == 0 ? 1 : 5);
}

void func_001B1608(C33* self)
{
    if (self->state != 8) {
        self->desc30()->m4D(self, self->f554 == 0 ? 3 : 7);
    }
    Rec_1B0EE0* r = (Rec_1B0EE0*)self->f550;
    if (r != 0) {
        if (r->f550 == 1) {
            if (__builtin_fabsf(D_0026185C[0] - r->f554) < 0.2f) {
                self->f5C0 = r->f550;
            }
        }
    }
}

void func_001B1698(C33* self)
{
    self->f554 = 1;
    if (self->f608 < 0.0f) {
        self->f618 = 0;
        switch (self->state) {
        case 1:
            self->desc30()->m4D(self, 3);
            break;
        case 5:
            self->desc30()->m4D(self, 7);
            break;
        }
    }
}

void func_001B1710(C33* self, s32 n)
{
    if (self->state == n) return;
    switch (self->state) {
    case 1:
    case 5:
        func_001BF788(self->f5C4, 0);
        self->f614 = self->f55C;
        break;
    case 8:
        self->f5C0 = 0;
        self->f618 = 0;
        break;
    }
    switch (n) {
    case 1:
        func_001BFCD8(15, &self->f5C4, self, 0, 2000.0f, 500.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        break;
    case 2:
    case 6:
        self->f618 = 1;
        break;
    case 3:
    case 4:
    case 7:
        break;
    case 5:
        func_001BFCD8(27, &self->f5C4, self, 0, 2000.0f, 500.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        break;
    }
    func_001AECE8(self, n);
    if (self->f618 != 0 && (n == 2 || n == 6)) {
        self->state = (n == 2) ? 1 : 5;
        self->f55C = self->f614;
    }
}

void func_001B1898(C33* self)
{
    s32 first, last, mode, frame;
    f32 duration, start;

    switch (self->state) {
    case 0:
    case 4:
    case 8:
        first = self->animA.first;
        last = self->animA.last;
        duration = self->animA.duration;
        mode = self->animA.mode;
        start = self->f55C;
        break;
    case 1:
        first = self->animB.first;
        last = self->animB.last;
        duration = self->animB.duration;
        mode = self->animB.mode;
        start = self->f55C;
        break;
    case 3:
        frame = (s32)((D_0026185C[0] - self->f55C) / (1.0f / self->blinkRate)) % 2;
        if (frame != 0) {
            first = self->animB.first;
            last = self->animB.last;
            duration = self->animB.duration;
            mode = self->animB.mode;
            start = self->f614;
        } else {
            first = self->blinkFrame;
            last = first;
        }
        break;
    case 7:
        frame = (s32)((D_0026185C[0] - self->f55C) / (1.0f / self->blinkRate)) % 2;
        if (frame != 0) {
            first = self->animC.first;
            last = self->animC.last;
            duration = self->animC.duration;
            mode = self->animC.mode;
            start = self->f614;
        } else {
            first = self->blinkFrame;
            last = first;
        }
        break;
    case 5:
        first = self->animC.first;
        last = self->animC.last;
        duration = self->animC.duration;
        mode = self->animC.mode;
        start = self->f55C;
        break;
    }

    s32 count = last - first + 1;
    if (count == 1 || duration <= 0.0f) {
        frame = first;
    } else {
        switch (mode) {
        case 0:
            frame = (s32)((D_0026185C[0] - start) / (duration / (f32)count)) % count;
            break;
        case 1: {
            s32 period = count * 2 - 2;
            frame = (s32)((D_0026185C[0] - start) / (duration / (f32)period)) % period;
            if (frame >= count)
                frame -= (frame - count + 1) * 2;
            break;
        }
        }
        frame += first;
    }
    func_001B46E0((s32)self->f610 + 0x10, frame);
}
