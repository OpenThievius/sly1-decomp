// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 98/108 (90.7%), checked 2026-11-05
// NEAR: order: 25 of 27 instructions line up; s2 and s3 (self and the loop counter) are swapped.
//       Eight source variants did not move them.
#include "common.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "fpu.h"
#include "world.h"
#include "c67.h"
#include "screen_element.h"
#include "globals.h"
#include "shapes.h"
#include "object_link.h"
#include "owner_message.h"
#include "game_clock.h"
#include "pad_record.h"
#include "memory_card.h"

void func_001C9AF8(void);

void func_001E8E08(C0B* a0)
{
    if (a0->fC58 != 0x2DA) {
        s32 v = a0->fC5C - 1;
        if (!(0 < v)) v = 0;
        a0->fC5C = v;
    }
    func_001C9AF8();
}

extern u8 D_00275BC0[];
void func_001E90A8(void* p);

void func_001E9088(void)
{
    func_001E90A8(D_00275BC0);
}

void func_001AA110(void);

void func_001E9668(void)
{
    func_001AA110();
}

void func_001EB018(f32* a0, f32 x, f32 y, f32 z, f32 w)
{
    f32 p = w - x;
    f32 q = y - x;
    a0[0] = x;
    f32 r = p / z - q;
    r = r / (z - 1.0f);
    a0[2] = r;
    a0[1] = q - r;
}

struct __attribute__((packed)) Entry8_1EBCD8 { u8 b[8]; };
struct List_1EBCD8 { u8 pad[0x630]; s32 count; Entry8_1EBCD8 items[1]; };

void func_001EBCD8(List_1EBCD8* list, const Entry8_1EBCD8* src)
{
    s32 n = list->count;
    list->count = n + 1;
    Entry8_1EBCD8* dst = (Entry8_1EBCD8*)((u8*)list + (n * 8 + 0x634));
    *dst = *src;
}

ObjectLink D_00275CA0[4] = {
    { 4, 0x4D0, 0x618 }, { 4, 0x4D1, 0x61C }, { 4, 0x4D2, 0x620 }, { 4, 0x4D3, 0x624 }
};
void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a, void* p);
void* func_001B6290(void* a, void* self, s32 b, s32 c);
void func_001DBCC8(void* a, void* cb, void* ctx, s32 b, s32 c);
void func_001EB550(C1C* self);

void func_001EB598(C1C* self)
{
    func_00124A48(self);
    func_00124DF8(self, 4, D_00275CA0);
    self->f614 = func_001B6290(self->f610, self, 0x4CA, 1);
    func_001DBCC8(self->world, (void*)func_001EB550, self, 0, 0);
}

struct Inner_1EB608 { u8 pad[0xC3C]; void* c3C; };

void func_001922E8(void* self);
void* func_0015A838(void* a, s32 b, s32 c, s32 d);
void func_001B64D8(void* a, s32 b);

void func_001EB608(C1C* self, void* p)
{
    func_001922E8(self);
    Inner_1EB608* r = (Inner_1EB608*)func_0015A838(self->world, 5, 0x13, 0);
    if (p != 0) {
        func_001B64D8(self->f614, 0x4CB);
        r->c3C = self;
        self->f68C = r;
    } else {
        func_001B64D8(self->f614, 0x4CA);
        *(f32*)((u8*)D_00262E10 + 0x26D0) = 2.0f;
    }
}

extern s32 D_00262C64;
s32 func_001DDA80(void* p);

s32 func_001EBC88(C1C* self)
{
    if (D_00262C64 & 1) return 1;
    if (func_001DDA80(self->world) == 0) return self->f688 != 0;
    return 1;
}

s32 func_001EBD08(void)
{
    return 0;
}

struct Probe_001E9038 {
    u8 pad0[0x50];
    s32 key;
};

s32 func_001C7468(void* self, void* probe);

s32 func_001E9038(C0B* self, Probe_001E9038* probe)
{
    s32 key = probe->key;
    u32 i = 0;
    s32 result;
    do {
        if (key == self->fC64[i]) {
            result = 0;
            goto done;
        }
        i++;
    } while (i < 6);
    result = func_001C7468(self, probe);
done:
    return result;
}

struct Ctor_001E90A8 {
    u8 pad0[4];
    s32 a04;
    u8 pad1[4];
    s32 a0C;
    u8 pad2[0x1C];
    s32 a2C;
    s32 a30;
};

void func_001E96F8(void* self, s32 mode);

void func_001E90A8(Ctor_001E90A8* self)
{
    self->a30 = -1;
    self->a04 = -1;
    func_001E96F8(self, 3);
    self->a0C = 0;
    self->a2C = 1;
}

void func_001E96F8(void* self, s32 mode);

void func_001E90E8(void* self)
{
    func_001E96F8(self, 3);
}


struct Set_001E9498 {
    u8 pad0[0xC];
    ScreenElement* items[8];
    s32 count;
};

s32 func_001BE5E8(void);
void func_001BEA28(void);

void func_001E9498(Set_001E9498* self, ScreenElement* node)
{
    if (func_001BE5E8() && self->count == 1) {
        func_001BEA28();
    }
    if (self->count >= 2) {
        ScreenElement* last = self->items[self->count - 1];
        if (last->vt->m03) {
            last->vt->m03(last, 0);
        }
    }
    if (node->vt->m03) {
        node->vt->m03(node, 1);
    }
    s32 index = self->count;
    self->items[index] = node;
    self->count = index + 1;
    if (node->vt->m06) {
        node->vt->m06(node);
    }
}

f32 func_002058A0(f32 v);

f32 func_001EAFE0(f32 x, f32 y)
{
    f32 r = func_002058A0(x);
    if (r < 0.0f) {
        r += y;
    }
    return r;
}

s32 func_001EB050(S1EB050* span, f32 x)
{
    s32 inside = 0;
    if (span->lo < x) {
        if (x < span->hi) {
            inside = 1;
        }
    }
    return inside;
}

s32 func_001EB050(S1EB050* span, f32 x);

s32 func_001EB080(s32 count, S1EB050* spans, f32 x)
{
    for (s32 i = 0; i < count; i++) {
        if (func_001EB050(&spans[i], x)) {
            return 1;
        }
    }
    return 0;
}

f32 func_001EB0F8(S1EB050* span, f32 x)
{
    if (x < span->lo) {
        return span->lo;
    }
    if (span->hi < x) {
        return span->hi;
    }
    return x;
}

typedef void (*VFn3_1E9570)(void* self, int arg);
typedef void (*VFn7_1E9570)(void* self);
struct VTable_1E9570 {
    u8 pad0[0xC];
    VFn3_1E9570 slot3;
    u8 pad1[0xC];
    VFn7_1E9570 slot7;
};
struct Item_1E9570 { VTable_1E9570* vt; };
struct Group_1E9570 {
    u8 pad0[0xC];
    Item_1E9570* items[8];
    s32 count;
};

int func_001BE5E8(void);
void func_001BEA50(void);

void func_001E9570(Group_1E9570* g)
{
    Item_1E9570* item = g->items[--g->count];
    if (item->vt->slot3) item->vt->slot3(item, 0);
    if (item->vt->slot7) item->vt->slot7(item);
    if (g->count >= 2) {
        Item_1E9570* other = g->items[g->count - 1];
        if (other->vt->slot3) other->vt->slot3(other, 1);
    }
    if (func_001BE5E8()) {
        if (g->count == 1) func_001BEA50();
    }
}

void func_001AA178(void);

void func_001E9648(void)
{
    func_001AA178();
}

extern float D_0026185C[];

void func_001C06A0(int a, int b, float t);
void func_00142ED0(float x);

void func_001E98E8(float x)
{
    if (0.0f < D_0026185C[0]) {
        float t = (1.0f - x) * 0.6f + x;
        func_001C06A0(4, 1, t);
        func_001C06A0(4, 0, t);
    }
    func_00142ED0(x);
}

s32 func_001EB128(f32* a, f32* b)
{
    f32 x = *a;
    f32 y = *b;
    if (y < x) return 1;
    if (x < y) return -1;
    return 0;
}

void func_001EB160(void)
{
}

void func_001BAC30(void* self);
void func_00124DF8(void* self, s32 n, void* data);
ObjectLink D_00275C90[1] = { { 0, 0x4C9, 0x610 } };

void func_001EB518(C1C* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 1, D_00275C90);
}


extern s32 D_00275F84;

s32 func_001E9A10(void)
{
    if (D_00275F84 != 0) goto fail;
    if (D_0026FF68.open != 0) goto fail;
    if (D_0026FF68.mode != 0) goto fail;
    if (D_0026F808.open != 0) goto fail;
    if (D_0026F808.mode == 0) goto ok;
fail:
    return 0;
ok:
    return 1;
}

s32 func_001E8DB0(C0B* a0)
{
    if (a0->fC40 != 0) return 0;
    return a0->fC5C != 0;
}

s32 func_001E8DD0(C0B* a0)
{
    if (a0->fC58 != 0x2DB) return 0;
    {
        s32 v = a0->fC5C;
        if (v == 5 || v == 0) return 0;
        return 1;
    }
}

f32 func_001EAFE0(f32 x, f32 y);

f32 func_001EA408(f32 a)
{
    f32 r = a;
    if (a < -3.1415927f || a > 3.1415927f) {
        r = func_001EAFE0(a + 3.1415927f, 6.2831855f) - 3.1415927f;
    }
    return r;
}

f32 func_001EA480(f32 a, f32 b)
{
    f32 r = a;
    if (b < r) {
        r = b;
    } else {
        b = -b;
        if (r < b) {
            r = b;
        }
    }
    return r;
}

struct Vec3_1EAD30 { f32 x; f32 y; f32 z; };

void func_001EAD30(Vec3_1EAD30* in, Vec3_1EAD30* out, f32 s, f32 t)
{
    out->z = in->z * s * s;
    out->y = (in->z + in->z) * s * t + in->y * s;
    out->x = (in->z * t * t + in->y * t) + in->x;
}

s32 func_001BB290(void* a, s32 b, s32 c);
s32 func_001E89F0(void* a, void* b);
void* func_00129C20(s32 a, s32 b);
void func_001B64D8(void* p, s32 n);
void func_001C9CF8(void* a);

void func_001E8E48(C0B* self)
{
    if (self->fC58 == 0x2DA && self->f724 == 0xC && func_001BB290(self, 0, 0) != 0) {
        s32 s = func_001E89F0(self, (u8*)self + 0x140);
        if (s != self->fC7C) {
            s32 n = self->fC5C - 1;
            if (!(0 < n)) n = 0;
            self->fC5C = n;
            if (n > 0) {
                void* p = func_00129C20(s, -1);
                if (p != 0) func_001B64D8(p, 0x2E0);
                self->fC7C = s;
            }
        }
    }
    func_001C9CF8(self);
}

typedef void* (*VFn_1E8EF8)(void* self);
struct Buf_1E8EF8 { s32 v[4]; };

void func_001C8418(C0B* self, void* p);
void func_001C8C08(C0B* self);
void func_001F3BD8(void* self, void* arg);

void func_001E8EF8(C0B* self)
{
    Buf_1E8EF8 loc;
    switch (self->f724) {
    case 4:
        if (self->fC40 != 0) {
            func_001C8418(self, (u8*)self + 0x190);
        } else {
            func_001F3BD8(self->fC60, &loc);
            func_001C8418(self, &loc);
        }
        break;
    case 8: {
        void* r = ((VFn_1E8EF8*)self->desc)[102](self);
        if (r != 0) func_001C8418(self, (u8*)r + 0x140);
        break;
    }
    default:
        func_001C8C08(self);
        break;
    }
}

void func_001C8BC0(C0B* self);
void func_001C8E28(C0B* self);

void func_001E8FA8(C0B* self)
{
    if (self->f724 == 8) {
        func_001C8BC0(self);
    } else {
        func_001C8E28(self);
    }
}

void func_001E9E30(World* self)
{
    ListFrame frame;
    Collider* s1 = (Collider*)self->list6C.head;
    if (s1 != 0) {
        do {
            Collider* s0 = (Collider*)s1->parts.head;
            if (s0 != 0) {
                do {
                    u64 bit = (u64)1 << 53;
                    if ((s0->flags538 & bit) == 0) {
                        ((Desc03*)s0->desc)->m44(s0);
                    }
                    s0->flags538 &= ~bit;
                    s0 = (Collider*)s0->link2E4.next;
                } while (s0 != 0);
            }
            s1 = (Collider*)s1->link414.next;
        } while (s1 != 0);
    }
}

extern u8 D_00261420[];
ObjectLink D_00275B60[8] = {
    { 3, 0x2D5, 0xC50 }, { 3, 0x2E7, 0xC60 }, { 7, 0x2E1, 0xC64 }, { 7, 0x2E2, 0xC68 },
    { 7, 0x2E3, 0xC6C }, { 7, 0x2E4, 0xC70 }, { 7, 0x2E5, 0xC74 }, { 7, 0x2E6, 0xC78 }
};

void func_00124DF8(void* self, s32 a1, void* a2);
void func_001DDC38(void* sub, void* self);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
void* func_00140FF8(void* p);
void func_00167E08(void* self);

void func_001E8948(C0B* self)
{
    func_00124DF8(self, 8, D_00275B60);
    func_001DDC38(self->world, self);
    if (self->fC50 != 0) {
        self->fC54 = func_001B6290(self->fC50, 0, 0x2D7, 0);
    }
    self->fC90 = 4;
    for (u32 i = 0; i < 4; i++) {
        self->fC80[i] = func_00140FF8(D_00261420);
    }
    func_00167E08(self);
}



s32 func_001E9970(void);

void func_001E8FE8(void)
{
    if (func_001E9970()) {
        D_0026E248.vt->m14(&D_0026E248);
    } else {
        D_0026E248.vt->m15(&D_0026E248);
    }
}


extern s32 D_00275F84;
extern s32 D_00270458;

s32 func_001E9A68(void)
{
    s32 m;
    if (D_00275F84 != 0) goto fail;
    if (D_0026FF68.open != 0) goto fail;
    if (D_0026FF68.mode != 0) goto fail;
    if (D_0026F808.open != 0) goto fail;
    if (D_0026F808.mode != 0) goto fail;
    m = D_00270458;
    if (m == 4) goto fail;
    if (m != 1) goto ok;
fail:
    return 0;
ok:
    return 1;
}


extern s32 D_00275F84;

s32 func_001E9AD8(void)
{
    if (D_00275F84 != 0) goto fail;
    if (D_0026FF68.open != 0) goto fail;
    if (D_0026FF68.mode != 0) goto fail;
    if (D_0026F808.open != 0) goto fail;
    if (D_0026F808.mode == 0) goto ok;
fail:
    return 0;
ok:
    return 1;
}

extern u8 D_00275DB8[];
extern u8 D_00275DBC[];
void func_001C6F48(void* self);
void* func_0018D500(s32 size);
void func_001BEA78(void);

void func_001EBEB0(C13* self)
{
    func_001C6F48(self);
    *(s32*)((u8*)self + 0xC5C) = 0x3C;
    self->fC8C = 1.0f;
    self->fC64 = 8.0f;
    self->fC70 = 0;
    self->fC78 = -1;
    self->fC74 = -1;
    self->fC60 = 8;
    *(s32*)((u8*)self + 0xC6C) = (s32)func_0018D500(0x400);
    self->world->f2358 = 1;
    func_001BEA78();
    *(s32*)D_00275DB8 = 2;
    *(s32*)D_00275DBC = 0;
}

// NEAR: the li and lui registers differ (retail keeps 1 in v0 and the global base in a2)


struct Obj_1E9688 {
    u8 pad0[0xC];
    s32 f_0C;
    u8 pad1[0x2C - 0x10];
    s32 f_2C;
    s32 f_30;
};

void func_001E9570(void* g);
void func_001A7D98(void* self, s32 mode);
void func_001AA0C0(void);

void func_001E9688(Obj_1E9688* self)
{
    while (self->f_2C >= 2) {
        func_001E9570(self);
    }
    s32 one = 1;
    self->f_30 = -1;
    u8* base = (u8*)&D_00262C70;
    self->f_2C = one;
    self->f_0C = 0;
    func_001A7D98(*(void**)(base + 0xBC), 3);
    func_001AA0C0();
}

// NEAR: prologue copies: retail moves $f12 to $f22 before $a1 to $s1, and sets $f14 from $f20 before $a1 = sp; the compiler orders both differently (4 lines).

struct Obj_1EA620 { u8 pad[0xC]; f32 f0C; };

f32 func_001EA4B8(f32 a, f32 b, f32 c, void* p, f32* out);

f32 func_001EA620(f32 a, f32 b, f32 c, f32 d, void* self, f32* out)
{
    Obj_1EA620* o = (Obj_1EA620*)self;
    f32 tmp;
    f32 res = func_001EA4B8(a, c, d, self, &tmp);
    f32 k = o->f0C;
    if (0.0f < k) {
        f32 hi = b + k * d;
        f32 lo = b - k * d;
        if (hi < tmp) {
            tmp = hi;
            res = a + b * d + (k * (d * 0.5f)) * d;
        } else if (tmp < lo) {
            tmp = lo;
            res = a + b * d - (k * (d * 0.5f)) * d;
        }
    }
    if (out != 0) *out = tmp;
    return res;
}

// NEAR: ints are saved to s0/s1 the wrong way round (self in s1, a1 in s0) and mov.s f21,f15 lands in the delay slot; ordering of the callee-saved moves differs.

f32 func_001EA408(f32 a);
f32 func_001EA620(f32 f12, f32 f13, f32 f14, f32 f15, void* self, s32 a1);

f32 func_001EA798(f32 f12, f32 f13, f32 f14, f32 f15, void* self, s32 a1)
{
    f32 t = func_001EA408(f14 - f12);
    f32 r = func_001EA620(0.0f, f13, t, f15, self, a1);
    return func_001EA408(f12 + r);
}

f32 func_001EA408(f32 a);
f32 func_001EA4B8(f32 a, f32 b, f32 c, void* p, f32* out);

f32 func_001EA728(f32 a, f32 b, f32 c, void* self, f32* out)
{
    f32 t = func_001EA408(b - a);
    f32 r = func_001EA4B8(0.0f, t, c, self, out);
    return func_001EA408(a + r);
}

s32 func_001F6708(void);

f32 func_001EAAE0(f32 a, f32 b)
{
    f32 r;
    if (a != b) {
        s32 n = func_001F6708();
        r = a + (b - a) * (f32)n * 0.0000000004656613f;
    } else {
        r = a;
    }
    return r;
}

struct Coeffs_1EA4B8 { f32 p0; f32 p1; f32 p2; };

s32 func_001EACA0(f32* roots, f32 a, f32 b, f32 c);

f32 func_001EA4B8(Coeffs_1EA4B8* k, f32* out, f32 x, f32 y, f32 z)
{
    f32 roots[4];
    s32 flip = 0;
    f32 d = x - y;
    f32 c = z;
    f32 half;
    f32 t;
    f32 res;
    f32 r;
    if (d < 0.0f) {
        flip = 1;
        d = -d;
    }
    half = (k->p1 + k->p0) * k->p2 * 0.5f;
    if (half <= d) {
        f32 u = (d - half) / k->p0;
        if (c <= u) {
            res = d - k->p0 * c;
            t = -k->p0;
            goto tail;
        }
        c = c - u;
        d = half;
    }
    func_001EACA0(roots, (k->p0 - k->p1) / (k->p2 + k->p2), k->p1, -d);
    r = roots[0] - c;
    if (0.0f < r) {
        res = (k->p0 - k->p1) * r * r / (k->p2 + k->p2) + k->p1 * r;
        t = -(k->p1 + (k->p0 - k->p1) * r / k->p2);
    } else {
        t = -k->p1;
        res = 0.0f;
    }
tail:
    if (flip) {
        res = y - res;
        if (out) {
            *out = -t;
        }
    } else {
        res = res + y;
        if (out) {
            *out = t;
        }
    }
    return res;
}

void func_00167D68(void* self);

void func_001E88D0(C0B* self)
{
    func_00167D68(self);
    self->fC58 = 0x2D8;
    self->fC14 = 30000.0f;
    self->fC10 = 30000000.0f;
    self->fC20 = 3000000.0f;
    self->fC24 = 3000000.0f;
    self->fC28 = 0;
    self->fC2C = 6.2831855f;
}

f32 func_001EAF28(f32 x)
{
    f32 buf[2];
    u64* qp = (u64*)buf;
    buf[0] = x;
    u64 bits = *qp;
    u32 ex = (u32)((s64)(bits << 9) >> 32) & 0xFF;
    s32 e = (s32)ex - 0x7F;
    if (e < 0)
        return 0.0f;
    if (e < 0x17) {
        s32 mask = (s32)(((u64)1 << (0x17 - e)) - 1);
        s32 frac = *(s32*)buf & 0x7FFFFF;
        if ((frac & mask) == mask) {
            { u64 lo = (u64)(s64)(frac & ~mask); *qp = (bits & (s32)0xFF800000) | lo; }
            buf[0] = buf[0] + 1.0f;
        } else {
            { u64 lo = (u64)(s64)(frac & ~mask); *qp = (bits & (s32)0xFF800000) | lo; }
        }
    }
    return buf[0];
}

struct Entry_1EBFB0 { s32 a; s32 b; s32 c; };
void func_001C72A0(void* self);
void func_001DDC38(void* a, void* self);
void func_00124DF8(void* self, s32 n, void* data);
void* func_001B6290(void* a, s32 b, s32 c, s32 d);
void func_001B6DF8(void* a, void* self);
void* func_0018D568(s32 size, void* name);
s32 func_0015A418(void* a, s32 b, s32 c, void* self);
ObjectLink D_00275D08[5] = {
    { 1, 0x4EB, 0xC50 }, { 0, 0x4E7, 0xC24 }, { 0, 0x4E8, 0xC28 }, { 0, 0x4E9, 0xC2C },
    { 0, 0x4EA, 0xC30 }
};
struct Entry_275D48 { s32 id; f32 v; s32 z; };
Entry_275D48 D_00275D48[9] = {
    { 0x35, 50.0f, 0 }, { 0x36, 50.0f, 0 }, { 0x38, 80.0f, 0 }, { 0x3B, 80.0f, 0 },
    { 0x60, 70.0f, 0 }, { 0x50, 220.0f, 0 }, { 0x52, 80.0f, 0 }, { 0x53, 80.0f, 0 },
    { 0x54, 80.0f, 0 }
};

void func_001EBFB0(C13* self)
{
    func_001C72A0(self);
    func_001DDC38(self->world, self);
    func_00124DF8(self, 5, D_00275D08);
    void* r = func_001B6290(self->fC50, 0, -1, 0);
    self->fC54 = r;
    func_001B6DF8(r, self);
    self->fC98 = 9;
    self->fC9C = func_0018D568(0x6C, D_00275D48);
    s32 i = 0;
    if (self->fC98 > 0) {
        s32 off = 0;
        do {
            Entry_1EBFB0* e = (Entry_1EBFB0*)((u8*)self->fC9C + off);
            e->c = func_0015A418(self->world, 1, e->a, self);
            i++;
            off += 12;
        } while (i < self->fC98);
    }
}

f32 D_00275C18[4] = { 2.0f, 0.0f, 0.1f, 0.0f };
f32 D_00275C28[3] = { 1.0f, 0.0f, 0.1f };

f32 func_001EA4B8(void* p, void* out, f32 a, f32 b, f32 c);

void func_001EA0A8(World* self, f32 x)
{
    World* o = self;
    f32 a = o->f234C;
    f32 b = o->f2350;
    if (b < a) {
        o->f234C = func_001EA4B8(D_00275C18, 0, a, b, x);
    } else if (a < b) {
        o->f234C = func_001EA4B8(D_00275C28, 0, a, b, x);
    }
}

extern const f32 D_0024E66C = 3.4028235e+38f;
s32 func_001C8010(C0B* self);

s32 func_001E8D58(C0B* self)
{
    s32 a1;
    if (self->fC5C <= 0) {
        self->fBFC = D_0024E66C;
    }
    a1 = self->f724;
    if (a1 == 10) {
        a1 = (self->f7E0 == 0) ? 8 : 10;
    } else {
        a1 = func_001C8010(self);
    }
    return a1;
}

void func_001EB550(C1C* a0)
{
    a0->blk580 = D_00262E10->blk580;
    a0->f604 = D_00262E10->f604;
}

struct Obj_1E96F8 { u8 pad0[4]; s32 f4; f32 f8; u8 pad1[0x24]; s32 f30; };

extern u8 D_00275F80[];
extern s32 D_00274738;
extern f32 D_00261868[];

void func_001E98E8(Obj_1E96F8* a, f32 f);
void func_0018C178(MemoryCard* a, s32 v);
void func_001F0220(u8* a, s32 v);
void func_001DDA50(void* a);
void func_001DDA20(void* a);
void func_001A7E70();

void func_001E96F8(Obj_1E96F8* self, s32 state)
{
    if (state == 3) {
        s32 t = self->f30;
        if (t != -1) state = t;
    }
    if (self->f4 != state) {
        if (self->f4 != 0) {
            if (self->f4 == 1) {
                D_00272930.vt->m15(&D_00272930);
                D_00272B98.vt->m15(&D_00272B98);
                func_001DDA50(D_00275710);
            }
        }
        self->f4 = state;
    self->f8 = D_00261868[0];
    switch (state) {
    case 0:
        if (g_memoryCard.displayMode == 0) func_0018C178(&g_memoryCard, 1);
        func_001F0220(g_screenFade, 0);
        func_001E98E8(self, 1.0f);
        break;
    case 1:
        func_001E98E8(self, 1.0f);
        D_00272930.vt->m14(&D_00272930);
        D_00272B98.vt->m14(&D_00272B98);
        func_001DDA20(D_00275710);
        func_001A7E70();
        break;
    case 2:
        func_001E98E8(self, 1.0f);
        break;
    case 3:
        func_001E98E8(self, 1.0f);
        D_00274738 = -100;
        break;
    case 5:
    case 7:
        func_001E98E8(self, 0.0f);
        break;
    case 8:
        D_0026C6C8.vt->m15(&D_0026C6C8);
        D_0026C948.vt->m15(&D_0026C948);
        D_0026CBC8.vt->m15(&D_0026CBC8);
        D_0026CE48.vt->m15(&D_0026CE48);
        break;
    }
    }
}

struct Elem_1E9108;
struct Vt_1E9108 {
    u8 pad[0x10];
    void (*fn)(Elem_1E9108* self, void* arg);
};
struct Elem_1E9108 {
    Vt_1E9108* vt;
};
struct Obj_1E9108 {
    u8 pad0[4];
    s32 state;
    f32 f8;
    Elem_1E9108* stack[1];
    u8 pad10[0x2C - 0x10];
    s32 count;
};

extern u32 D_00262C68;
extern u32 D_00262C6C;
extern s32 D_002701B8;
extern s32 D_00275F84;


extern void func_0016E118(s32 n);
extern void* func_001F4378(void);
extern void func_001F4808(void* x);
extern void func_0016EC20(PadRecord* p, s32 n);
extern void func_0018C568(MemoryCard* g);
extern void func_001605E8(void* p);
extern void func_00160948(void);
extern void func_00194D30(void* self, s32 a, s32 b);
extern void func_001E9498(Obj_1E9108* o, ScreenElement* g);
extern void func_001E98E8(Obj_1E9108* o, f32 v);
extern void func_001E96F8(Obj_1E9108* o, s32 mode);
extern void func_001409E0(void);
extern void func_001A9FD0(void);

void func_001E9108(Obj_1E9108* obj)
{
    f32 d = D_00261858.elapsed - obj->f8;
    s32 s1 = obj->state;
    PadRecord* s2;
    s32 s5;
    if (D_00262C68 & 4) {
        s2 = &D_00262C70;
    } else {
        s2 = &D_00262D38;
    }
    s5 = 0;
    if (D_00262C6C & 0x80) {
        if (0.1f < D_00261858.time) {
            func_0016E118(0x80);
        }
    }
    switch (obj->state) {
    case 0: {
        s32 a2 = 0;
        if (D_002701B8 == 0) {
            s32 m = g_memoryCard.displayMode;
            if (m == 2 || (m == 1 && g_memoryCard.state == 5)) {
                a2 = 1;
            }
        }
        if (a2) {
            func_001F4808(func_001F4378());
        }
        break;
    }
    case 1: {
        u32 v = s2->flags;
        if (v & 0x800) {
            s32 t;
            func_0016EC20(s2, 0x800);
            t = g_memoryCard.i4F48;
            g_memoryCard.i4F44 = t;
            if (t) {
                func_0018C568(&g_memoryCard);
            } else {
                func_001605E8(D_002623C0);
            }
            func_00160948();
            s1 = obj->state;
        } else if (v & 0x100) {
            func_0016EC20(s2, 0x100);
            func_00194D30(&D_0026FF68, 0, 0x17);
            s1 = obj->state;
        }
        break;
    }
    case 3: {
        if (D_00262C6C & 2) break;
        if (D_00275F84) break;
        {
            u32 v = s2->flags;
            if ((v & 0x800) || (s2->f14 == 1 && 5.0f <= D_00261858.time)) {
                func_00194D30(&D_0026FF68, 0, 0);
                s1 = obj->state;
                func_0016EC20(s2, 0x800);
            } else if ((v = s2->flags) & 0x100) {
                T217D_0F0* g2 = &D_0026F808;
                C67* x = g2->current;
                if (x == 0) break;
                if (x->mode) break;
                func_001E9498(obj, g2);
                s1 = obj->state;
                func_0016EC20(s2, 0x100);
            }
        }
        break;
    }
    case 4:
        if (d <= 0.2f) {
            func_001E98E8(obj, (0.2f - d) * 5.0f);
        } else {
            s1 = 5;
        }
        break;
    case 6:
        if (d <= 0.5f) {
            func_001E98E8(obj, d + d);
        } else {
            s1 = 3;
        }
        break;
    case 2:
    case 5:
    case 7:
        s5 = 1;
        break;
    case 8:
    default:
        break;
    }
    func_001E96F8(obj, s1);
    {
        Elem_1E9108* e = obj->stack[obj->count - 1];
        if (e) {
            if (e->vt->fn) {
                e->vt->fn(e, s2);
            }
        } else if (s5) {
            func_001E96F8(obj, 3);
        }
    }
    func_001409E0();
    func_001A9FD0();
}

struct Item_1EB748 { s32 type; s32 a; f32 b; s32 c; };
struct List_1EB748 { u8 pad[0x34]; s32 n; Item_1EB748* items; s32 cur; };
struct Grid_1EB748 {
    u8 pad0[0xC38];
    List_1EB748* list;
    u8 pad1[0xC70 - 0xC3C];
    s32 row;
    u8 pad2[0xC7C - 0xC74];
    f32 base;
    u8 pad3[0xC88 - 0xC80];
    f32 scale;
};
typedef s32 (*Fn_1EB748)(C1C* self, void* arg);
typedef void (*GFn_1EB748)(Player* g, void* arg);
struct In_1EB748 { u8 pad[0xAA]; u16 fAA; };

s32 D_00275CD8[4] = { 1228, 1230, 1229, 1231 };
s32 D_00275CE8[4] = { 574, 576, 575, 577 };

void func_001F3BD8(void* a, Vec4U* out);
void func_001F3C08(void* a, Mat3U* out);
void func_001BFCD8(s32 a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_001B64D8(void* a, s32 b);
s32 func_00160C58(void);
void func_001929D0(Player* g);
void func_001D7098(OwnerMessage* out, s32 mode, C1C* self);
void func_001EB698(void);
void func_001ED020(C13* o);
void func_001C0C08(s32 a, s32 b);
void func_0017CE20(void* a, Player* g);

void func_001EB748(C1C* self, In_1EB748* in)
{
    if (self->f67C != 0 && D_00262E10 != 0) {
        Vec4U pos;
        Mat3U mat;
        func_001F3BD8(self->f67C, &pos);
        func_001F3C08(self->f67C, &mat);
        ((GFn_1EB748*)D_00262E10->desc)[0x84 / 4](D_00262E10, &pos);
        ((GFn_1EB748*)D_00262E10->desc)[0x88 / 4](D_00262E10, &mat);
        ((Fn_1EB748*)self->desc)[0x84 / 4](self, &pos);
        ((Fn_1EB748*)self->desc)[0x88 / 4](self, &mat);
    }
    if (self->f680 != 0) {
        u32 f = in->fAA;
        if (f & 0xF0) {
            s32 dir;
            s32 ok;
            f32 at;
            if (f & 0x80) {
                dir = 0;
            } else if (f & 0x10) {
                dir = 1;
            } else if (f & 0x20) {
                dir = 2;
            } else if (f & 0x40) {
                dir = 3;
            }
            ok = 0;
            if (self->f62C < self->f630) {
                Ent1C* e = &self->f634[self->f62C];
                if (e->dir == dir) {
                    Grid_1EB748* g = ((Grid_1EB748*)self->f68C);
                    at = (f32)g->row * 4.0f + g->base;
                    if (__builtin_fabsf(e->t - at) < self->f684 * 0.5f) {
                        ok = 1;
                    }
                }
            }
            if (ok) {
                self->f678 = dir;
                self->f674 = at;
            } else {
                func_001BFCD8(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            }
        }
    }
    if (self->f62C < self->f630) {
        Ent1C* e = &self->f634[self->f62C];
        Grid_1EB748* g = ((Grid_1EB748*)self->f68C);
        f32 at = (f32)g->row * 4.0f + g->base;
        f32 win = self->f684;
        if (self->f678 == e->dir && __builtin_fabsf(e->t - self->f674) < win * 0.5f) {
            func_001B64D8(self->f614, D_00275CD8[self->f678]);
            func_001BFCD8(D_00275CE8[self->f678], 0, 0, 0, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0, 0);
        } else {
            if (!(at - e->t > win * 0.5f)) {
                return;
            }
            func_001BFCD8(0x51, 0, 0, 0, 30000.0f, 20000.0f, 1.5f, 0.3f, 0.0f, 0, 0);
            if (func_00160C58() == 0 && ((Fn_1EB748*)self->desc)[0x13C / 4](self, 0) == 0) {
                OwnerMessage msg;
                C13* o;
                func_001929D0(D_00262E10);
                func_001D7098(&msg, 0, self);
                msg.fn = func_001EB698;
                ((s32 (*)(Player*, OwnerMessage*))((GFn_1EB748*)D_00262E10->desc)[0x140 / 4])(D_00262E10, &msg);
                o = (C13*)func_0015A838(self->world, 5, 0x13, 0);
                func_001ED020(o);
                o->fBFC = D_0026185C[0];
                func_001C0C08(2, 1);
                goto next;
            }
            if (((Fn_1EB748*)self->desc)[0x13C / 4](self, 0) == 0) {
                List_1EB748* l;
                ((void (*)(C1C*))((Fn_1EB748*)self->desc)[0x150 / 4])(self);
                Player* gl = D_00262E10;
                self->f688 = 1;
                gl->f26C4 = 1;
                f32 v = D_0026185C[0];
                *(f32*)((u8*)gl + 0x26CC) = v;
                gl->f26C8 = v;
                l = ((Grid_1EB748*)self->f68C)->list;
                *(f32*)((u8*)gl + 0x26D0) = 2.0f;
                if (l != 0) {
                    s32 j = l->cur;
                    while (j < l->n) {
                        Item_1EB748* p = &l->items[j];
                        if (p->type == 3) break;
                        j++;
                    }
                    if (j < l->n) {
                        Item_1EB748* it = &l->items[j];
                        Grid_1EB748* gg = ((Grid_1EB748*)self->f68C);
                        *(f32*)((u8*)D_00262E10 + 0x26D0) = ((f32)it->a * 4.0f + it->b - ((f32)gg->row * 4.0f + gg->base)) * gg->scale;
                    }
                }
            }
        }
        if (e->dir == 3) {
            func_001929D0(D_00262E10);
            func_0017CE20(self->f628, D_00262E10);
            self->f628 = 0;
        }
    next:
        self->f62C++;
        if (self->f62C == self->f630) {
            self->f62C = 0;
            self->f630 = 0;
        }
    }
}

extern s32 D_00275C34;
extern u32* D_006256D0;
extern s32 D_006256D4;
extern u32 D_006256D8;
extern u8 D_00148D7C[];
extern u32 D_002476A0[];

struct Crc_1E9B30 {
    static u32 Step(u32 h, u8 b) { return D_002476A0[(h ^ b) & 0xFF] ^ (h >> 8); }
};

void func_001E9B30(void) {
    if (D_00275C34 == 0) {
        if (D_006256D4 == 0) {
            D_006256D0 = (u32*)0x100004;
            D_006256D4 = (s32)D_00148D7C;
            D_006256D8 = 0xFFFFFFFF;
        }
    }
    if (D_006256D4 == 0) {
        return;
    }
    u32* p = D_006256D0;
    s32 cnt = D_006256D4;
    u32 h = D_006256D8;
    for (s32 i = 0; i < 32 && cnt > 0; i++) {
        u32 w = *p;
        cnt -= 4;
        p++;
        h = Crc_1E9B30::Step(h, w);
        h = Crc_1E9B30::Step(h, w >> 8);
        h = Crc_1E9B30::Step(h, w >> 16);
        h = Crc_1E9B30::Step(h, w >> 24);
    }
    D_006256D0 = p;
    D_006256D8 = h;
    D_006256D4 = cnt;
    if (cnt == 0 && h != 0) {
        D_00275C34 = 1;
    }
}

s32 func_001EAA70(s32 a, s32 b)
{
    if (a == b) {
        return a;
    }
    s32 r = (s32)(u32)func_001F6708();
    s32 span = b - a + 1;
    r = r % 0x95675;
    r = r % span;
    return a + r;
}

f32 D_00275C80[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
f32 D_00275C70[4] = { 0.5f, 0.8f, 0.0f, 0.0f };

void func_001921A8(C1C* self);

void func_001EB460(C1C* self)
{
    func_001921A8(self);
    f32 t = D_002623C8->dt;
    f32 x = D_00275C80[0] + t * (D_00275C80[1] + t * D_00275C80[2]);
    f32 lo = D_00275C60.lo;
    f32 hi = D_00275C60.hi;
    f32 c;
    if (x < lo) {
        c = lo;
    } else if (hi < x) {
        c = hi;
    } else {
        c = x;
    }
    self->f684 = (1.0f - c) * D_00275C70[0] + c * D_00275C70[1];
}

f32 func_001EAAE0(f32 lo, f32 hi);
f32 func_002059E0(f32 x);

f32 func_001EAB48(f32 mean, f32 deviation, f32 limit)
{
    f32 x;
    f32 y;
    f32 r;
    do {
        x = func_001EAAE0(-1.0f, 1.0f);
        y = func_001EAAE0(-1.0f, 1.0f);
        r = x * x + y * y;
    } while (r > 1.0f || r == 0.0f);
    f32 v = mean + deviation * y * Fpu::Sqrt(func_002059E0(r) * -2.0f / r);
    if (limit != 0.0f) {
        f32 lo = mean - limit;
        f32 hi = mean + limit;
        if (v < lo) {
            v = lo;
        } else if (hi < v) {
            v = hi;
        }
    }
    return v;
}

s32 func_001EACA0(f32* roots, f32 a, f32 b, f32 c)
{
    f32 disc = b * b - a * (4.0f * c);
    if (disc < 0.0f) {
        return 0;
    }
    a = a + a;
    disc = Fpu::Sqrt(disc) / a;
    b = b / a;
    if (__builtin_fabsf(disc) < 0.0001f) {
        roots[0] = -b;
        return 1;
    }
    roots[0] = -b + disc;
    roots[1] = -b - disc;
    return 2;
}

void func_001EAD88(f32* sinOut, f32* cosOut, f32 angle)
{
    f32 t = (angle + 1.5707964f) * 0.31830987f;
    s32 n = (s32)t;
    if (t < 0.0f) {
        n--;
    }
    angle -= (f32)n * 3.1415927f;
    if (n & 1) {
        angle = -angle;
    }
    f32 x2 = angle * angle;
    f32 s = angle;
    angle *= x2;
    s += angle * -0.166666567f;
    angle *= x2;
    s += angle * 0.00833302550f;
    angle *= x2;
    s += angle * -0.000198074136f;
    angle *= x2;
    s += angle * 2.60188699e-06f;
    f32 c = Fpu::Sqrt(1.0f - s * s);
    if (n & 1) {
        *cosOut = -c;
    } else {
        *cosOut = c;
    }
    *sinOut = s;
}


extern s32 D_00275F84;
extern s32 D_00270458;
s32 func_001DDA80(World* p);

s32 func_001E9970(void)
{
    if (D_00275F84 != 0) goto fail;
    if (func_001DDA80((World*)D_00275710) != 0) goto fail;
    if (D_0026FF68.open != 0 && D_0026FF68.page != 0) goto fail;
    if (D_0026F808.open != 0) goto fail;
    if (D_0026F808.mode != 0) goto fail;
    if (D_00270458 == 2) goto fail;
    if (D_00270458 == 1) goto fail;
    if (D_00270458 != 4) goto ok;
fail:
    return 0;
ok:
    return 1;
}

union Bits_1EAE78 {
    double d;
    u64 u;
};

double func_001FCD20(double a, double b);

double func_001EAE78(double x)
{
    Bits_1EAE78 v;
    v.d = x;
    s32 e = ((u16)(v.u >> 52) & 0x7FF) - 0x3FF;
    if (e < 0) {
        return 0.0;
    }
    if (e < 0x34) {
        u64 frac = ((u64)1 << (0x34 - e)) - 1;
        u64 mant = v.u & ((u64)-1 >> 12);
        if ((mant & frac) == frac) {
            v.u = (v.u & ((u64)0xFFF0 << 48)) | (mant & ~frac & ((u64)-1 >> 12));
            x = v.d;
            x = func_001FCD20(x, 1.0);
        } else {
            v.u = (v.u & ((u64)0xFFF0 << 48)) | (mant & ~frac & ((u64)-1 >> 12));
            x = v.d;
        }
    }
    return x;
}

struct Node_1E9EE8;
struct Vtbl_1E9EE8 {
    u8 pad0[0x7C];
    void (*update)(Node_1E9EE8*, s32, f32);
};
struct Node_1E9EE8 { Vtbl_1E9EE8* vtbl; };
struct Iter_1E9EE8 { List01* list; u8* link; s32 offset; Iter_1E9EE8* prev; };
struct Begin_1E9EE8 {
    static void Of(Iter_1E9EE8* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        Iter_1E9EE8* prev = (Iter_1E9EE8*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
        it->prev = prev;
    }
};
struct Next_1E9EE8 {
    static Node_1E9EE8* Of(Iter_1E9EE8* it)
    {
        Node_1E9EE8* obj = *(Node_1E9EE8**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};
struct End_1E9EE8 {
    static void Of(Iter_1E9EE8* it) { D_0027B314 = (ListFrame*)it->prev; }
};

void func_00124EE8(Node_1E9EE8* n, f32 dt);
void func_0012EBD8(Node_1E9EE8* n, f32 dt);
void func_00159AD0(Node_1E9EE8* n, f32 dt);
void func_001DBE48(World* self);

void func_001E9EE8(World* self, f32 dt)
{
    if (dt == 0.0f) return;
    Iter_1E9EE8 it;
    Begin_1E9EE8::Of(&it, &self->list78);
    for (Node_1E9EE8* obj = Next_1E9EE8::Of(&it); obj; obj = Next_1E9EE8::Of(&it)) func_00124EE8(obj, dt);
    End_1E9EE8::Of(&it);
    Begin_1E9EE8::Of(&it, (List01*)&self->f1B70);
    for (Node_1E9EE8* obj = Next_1E9EE8::Of(&it); obj; obj = Next_1E9EE8::Of(&it)) func_0012EBD8(obj, dt);
    End_1E9EE8::Of(&it);
    Begin_1E9EE8::Of(&it, (List01*)&self->f1C30);
    for (Node_1E9EE8* obj = Next_1E9EE8::Of(&it); obj; obj = Next_1E9EE8::Of(&it)) func_00159AD0(obj, dt);
    End_1E9EE8::Of(&it);
    Begin_1E9EE8::Of(&it, &self->list78);
    for (Node_1E9EE8* obj = Next_1E9EE8::Of(&it); obj; obj = Next_1E9EE8::Of(&it)) obj->vtbl->update(obj, 0, dt);
    End_1E9EE8::Of(&it);
    func_001DBE48(self);
}

struct Iter_1E9C78 {
    List01* list;
    u8** link;
    s32 offset;
    Iter_1E9C78* prev;
};


struct Begin_1E9C78 {
    static void Of(Iter_1E9C78* it, List01* list)
    {
        it->list = list;
        it->link = (u8**)list;
        it->offset = list->offset;
        it->prev = (Iter_1E9C78*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};
struct Next_1E9C78 {
    static u8* Of(Iter_1E9C78* it)
    {
        u8* obj = *it->link;
        it->link = (u8**)(obj + it->offset);
        return obj;
    }
};
struct End_1E9C78 {
    static void Of(Iter_1E9C78* it)
    {
        D_0027B314 = (ListFrame*)it->prev;
    }
};

struct Holder_1E9C78;
struct Vt_1E9C78 {
    u8 pad0[0x134];
    void (*fn134)(Holder_1E9C78* self, f32 dt, u8* arg);
};
struct Holder_1E9C78 {
    Vt_1E9C78* vt;
};

void func_001E9B30(void);
Holder_1E9C78* func_001925F0(void);
void func_0015FF58(World* self);
void func_00124EE8(u8* n, f32 dt);
void func_0012EBD8(u8* n, f32 dt);
void func_00159AD0(u8* n, f32 dt);
void func_00159588(World* self);
void func_001C0070(void);
void func_001DBE48(World* self);

void func_001E9C78(World* self, f32 dt)
{
    func_001E9B30();
    Holder_1E9C78* h = func_001925F0();
    if (h != 0) {
        Vt_1E9C78* vt = h->vt;
        if (vt->fn134 != 0) {
            u8* a;
            if ((*(s32*)&D_00262C68) & 2)
                a = (u8*)&D_00262C70;
            else
                a = ((u8*)&D_00262D38);
            vt->fn134(h, dt, a);
        }
    }
    func_0015FF58(self);
    {
        Iter_1E9C78 it;
        Begin_1E9C78::Of(&it, (List01*)&self->list60);
        for (u8* n = Next_1E9C78::Of(&it); n != 0; n = Next_1E9C78::Of(&it)) {
            func_00124EE8(n, dt);
        }
        End_1E9C78::Of(&it);
    }
    {
        Iter_1E9C78 it;
        Begin_1E9C78::Of(&it, (List01*)&self->f1B64);
        for (u8* n = Next_1E9C78::Of(&it); n != 0; n = Next_1E9C78::Of(&it)) {
            func_0012EBD8(n, dt);
        }
        End_1E9C78::Of(&it);
    }
    {
        Iter_1E9C78 it;
        Begin_1E9C78::Of(&it, (List01*)&self->f1C24);
        for (u8* n = Next_1E9C78::Of(&it); n != 0; n = Next_1E9C78::Of(&it)) {
            func_00159AD0(n, dt);
        }
        End_1E9C78::Of(&it);
    }
    func_00159588(self);
    func_001C0070();
    func_001DBE48(self);
}

struct Iter_1EA118 { ActorList6C* list; u8* link; s32 offset; Iter_1EA118* saved; };


struct Next_1EA118 {
    static Actor6C* Of(Iter_1EA118* it)
    {
        Actor6C* obj = *(Actor6C**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_1EA118 {
    static void Of(Iter_1EA118* it, ActorList6C* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = ((Iter_1EA118*)D_0027B314);
        D_0027B314 = (ListFrame*)it;
    }
};

void func_001E9EE8(World* self, f32 t);
void func_001E9C78(World* self, f32 t);
void func_001E9E30(World* self);
void func_00138C00(World* self, s32 a);
void func_001BDD00(World* self, s32 a, f32 t);
s32 func_00129D70(Actor6C* n);
void func_00129DF8(Actor6C* n);
void func_001BB9D0(Actor6C* n);
void func_001DBEC8(World* self, f32 t);
void func_001DBE48(World* self);
void func_001B4878(f32 t);
void func_001DDC40(World* self);
void func_0012E710(Actor6C* n);
void func_00143E40(Camera* a, s32 b, f32 t);
void func_001EA0A8(World* self, f32 t);

void func_001EA118(World* self)
{
    Iter_1EA118 it;
    GameClock* clock = &D_00261858;
    func_001E9EE8(self, clock->step);
    if (clock->dt != 0.0f) {
        func_001E9C78(self, clock->dt);
        func_001E9E30(self);
        func_00138C00(self, 0);
        func_001BDD00(self, 1, clock->dt);
        Begin_1EA118::Of(&it, &self->list6C);
        for (Actor6C* obj; (obj = Next_1EA118::Of(&it)) != 0;) {
            if (obj->vtable->update != 0) {
                obj->vtable->update(obj, clock->dt);
            }
        }
        D_0027B314 = (ListFrame*)it.saved;
        func_00138C00(self, 1);
        func_001BDD00(self, 6, D_00261858.dt);
        Begin_1EA118::Of(&it, &self->list60);
        for (Actor6C* obj; (obj = Next_1EA118::Of(&it)) != 0;) {
            if (obj->tries < 2) {
                if (func_00129D70(obj) != 0) {
                    obj->tries++;
                } else {
                    func_00129DF8(obj);
                }
            }
        }
        D_0027B314 = (ListFrame*)it.saved;
        Begin_1EA118::Of(&it, &self->list6C);
        for (Actor6C* obj; (obj = Next_1EA118::Of(&it)) != 0;) {
            obj->vtable->post(obj);
            if (obj->flags & 0x8000000000000000ULL) {
                func_001BB9D0(obj);
            }
        }
        D_0027B314 = (ListFrame*)it.saved;
        func_001DBEC8(self, D_00261858.dt);
        func_001DBE48(self);
        func_001B4878(D_00261858.dt);
    }
    func_001DDC40(self);
    Begin_1EA118::Of(&it, &self->list1B7C);
    for (Actor6C* obj; (obj = Next_1EA118::Of(&it)) != 0;) {
        func_0012E710(obj);
    }
    D_0027B314 = (ListFrame*)it.saved;
    func_00143E40(D_00261990, 1, D_00261858.dt);
    func_001EA0A8(self, D_00261858.step);
}

extern s32 D_00275CF8[4];
s32 func_001CA758(void* self, s32 id);
void func_001C7140(void* self);

struct Obj_1EBF40 { u8 pad[0xC10]; s32 fC10[4]; };

void func_001EBF40(Obj_1EBF40* self)
{
    func_001C7140(self);
    for (s32 i = 0; i < 4; i++) {
        self->fC10[i] = func_001CA758(self, D_00275CF8[i]);
    }
}
