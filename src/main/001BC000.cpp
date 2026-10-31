// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_1BC748 { u8 pad[0x538]; u64 flags; };

void func_001BC748(Obj_1BC748* self, u32* out)
{
    u32 bit = (u32)(self->flags >> 52) & 1;
    *out = bit;
}

extern s32 D_00274744;

void func_001BE998(void);

void func_001BE708(void)
{
    D_00274744 = 0;
    func_001BE998();
}

extern s32 D_00274720;
extern s32 D_00274728;
extern s32 D_0027473C;

void func_001BEB10(void* self);
s32 func_0011CE30(void);
void func_001F6C20(s32 a);
s32 func_0011D598(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);

void func_001BEC58(void* self)
{
    func_001BEB10(self);
    if (self == 0) return;
    while (func_0011CE30() != 0 && D_00274720 == 1) {
        func_001F6C20(0);
    }
    if (D_00274720 == 2) {
        s32 h = func_0011D598(D_0027473C, 0, 0x400, -1, 0, 0);
        D_00274728 = h;
        if (h == 0) return;
        D_00274720 = 3;
    }
}

extern u8* D_00275710;

void func_00152600(u8* a, void* b);
void func_001B5F28(u8* a, void* b);

void func_001BEDF8(void* self)
{
    func_00152600(D_00275710 + 0x1BC4, self);
    func_001B5F28(D_00275710 + 0x1BB8, self);
}

extern u8 D_00604790[];

void func_001F5C0C(u8* p, s32 a, s32 b);
void func_0011CBB8(void);
void func_001BE268(s32 a);
void func_0011DF58(s32 a, s32 b, s32 c, s32 d);
void func_0011D928(s32 a);
void func_001C06D8(void);
void func_0011D520(s32 a, s32 b);
void func_0011D558(s32 a, s32 b, s32 c);
void func_0011E3A0(s32 a, s32 b);

void func_001BF130(void)
{
    func_001F5C0C(D_00604790, 0, 0x1C);
    func_0011CBB8();
    func_001BE268(0);
    func_0011DF58(1, 0x2000, 1, 1);
    func_0011D928(0x14);
    func_001C06D8();
    func_0011D520(0, 1);
    func_0011D558(0, 0, 0x2F);
    func_0011D558(1, 0x18, 0x2F);
    func_0011D558(3, 0x18, 0x2F);
    func_0011D558(2, 0x18, 0x2F);
    func_0011E3A0(2, 4);
}

void* func_001B5EA0(void* p);
void func_001F5C0C(void* p, s32 zero, s32 size);
void func_00152470(void* list, void* item);

void* func_001BF6B8(void)
{
    void* s = func_001B5EA0(D_00275710 + 0x1BA0);
    if (s) {
        func_001F5C0C(s, 0, 0x90);
        func_00152470(D_00275710 + 0x1BAC, s);
    }
    return s;
}

struct Entry_1BF718 { u8 pad[0xC]; s32 f0C; };
struct Slot_1BF718 { Entry_1BF718* entry; };

void func_001BF718(Slot_1BF718* slot)
{
    Entry_1BF718* e = slot->entry;
    e->f0C = 0;
    slot->entry = 0;
}

struct Obj_1BF728 { u8 pad0[4]; s32 f04; u8 pad1[4]; void* f0C; };

extern u8* D_00275710;

void func_00152600(u8* p, Obj_1BF728* self);
void func_001B5F28(u8* p, Obj_1BF728* self);

void func_001BF728(Obj_1BF728* self)
{
    if (self->f0C != 0) {
        *(s32*)self->f0C = 0;
    }
    self->f04 = -1;
    func_00152600(D_00275710 + 0x1BAC, self);
    func_001B5F28(D_00275710 + 0x1BA0, self);
}

struct Obj_1BF788 { u8 pad[0x18]; u8* f18; };

void func_001BF728(Obj_1BF788* self);
void func_0011D600(u8* p);
void func_0011D860(u8* p, s32 a, s32 b, s32 c);

void func_001BF788(Obj_1BF788* self, s32 n)
{
    if (self != 0) {
        if (n == 0) {
            func_0011D600(self->f18);
        } else {
            f32 t = (f32)n * 0.24000001f;
            s32 q = (s32)t;
            func_0011D860(self->f18, -4, q, 2);
        }
        func_001BF728(self);
    }
}

struct Obj_1BF8E8 { u8 pad0[0x14]; f32 f14; u8 pad1[0x38]; f32 f50; };

void func_001BE860(Obj_1BF8E8* self);

void func_001BF8E8(Obj_1BF8E8* self, f32 a)
{
    if (self != 0) {
        f32 scale = a / self->f14;
        f32 base = self->f50;
        self->f14 = a;
        self->f50 = base * scale;
        func_001BE860(self);
    }
}

struct Rec_1BFFC8 { u8 pad0[4]; s32 f04; u8 pad1[0x40]; s32 f48; };

void func_001BFFC8(void* guard, s64 key)
{
    if (guard == 0) {
        s32 tag = (s32)(key >> 32);
        Rec_1BFFC8* r = (Rec_1BFFC8*)(s32)(key & 0xFFFFFFFFu);
        if (r->f04 == tag) {
            r->f48 = 1;
        }
    }
}

struct Owner_001BC088 { u8 pad0[0x3C8]; void* hook; };

void func_001BBEB8(Owner_001BC088* self);
void func_00125440(Owner_001BC088* self, f32 x, void* b);

void func_001BC088(Owner_001BC088* self, void* b, f32 x)
{
    if (self->hook != 0) {
        func_001BBEB8(self);
    }
    func_00125440(self, x, b);
}

struct Shape_001BC320 { u8 pad0[8]; f32 radius; s32 flags; };

void func_001BC0E0(void* a0, f32 x, void* a1, void* a2);

s32 func_001BC320(void* a0, Shape_001BC320* self)
{
    if (self->flags & 0x8) {
        func_001BC0E0(a0, self->radius, (u8*)self + 0x20, (u8*)self + 0x30);
    }
    return self->flags != 0;
}

struct Flagged_001BC710 { u8 pad[0x538]; u64 bits; };

void func_001BC710(Flagged_001BC710* self, u32 flag)
{
    self->bits = (self->bits & 0xFFEFFFFFFFFFFFFFULL) | ((u64)(flag & 1) << 52);
}

void func_001C06A0(s32 a, s32 b, f32 x);

void func_001BED20(void)
{
    func_001C06A0(2, 1, 1.0f);
}

extern s32 D_00274728;

void func_0011D640(s32 a);

void func_001BED48(void)
{
    func_0011D640(D_00274728);
}

extern s32 D_00274728;

void func_0011D670(s32 a);

void func_001BED70(void)
{
    func_0011D670(D_00274728);
}

extern u8* D_00275710;

void* func_001B5EA0(void* p);
void func_001F5C0C(u8* p, s32 a, s32 b);
void func_00152470(u8* a, void* b);

void* func_001BED98(void)
{
    void* p = func_001B5EA0(D_00275710 + 0x1BB8);
    if (p != 0) {
        func_001F5C0C((u8*)p, 0, 12);
        func_00152470(D_00275710 + 0x1BC4, p);
    }
    return p;
}

struct VtItem_1BC760 { u8 pad0[8]; u32 flags; u8 pad1[0xE4 - 0x0C]; void (*visit)(void* item, s32* index, void* list); };
struct Item_1BC760 { VtItem_1BC760* vtbl; u8 pad[0x18]; Item_1BC760* next; };
struct Obj_1BC760 { u8 pad0[0x34]; Item_1BC760* head; u8 pad1[0x4C0 - 0x38]; s32 count; };

void func_001BC760(Obj_1BC760* self, s32* index, Obj_1BC760** list)
{
    s32 scratch[4];
    (void)scratch;
    self->count = *index;
    list[*index] = self;
    (*index)++;
    for (Item_1BC760* item = self->head; item; item = item->next)
        if (item->vtbl->flags & 2)
            item->vtbl->visit(item, index, list);
}

struct Entry_1BF048 {
    s32 key;
};

extern s32 D_002748EC;
extern s32 D_00274734;
extern s32 D_00274738;

void func_001BEDF8(void* self);
void func_001BEF88(void* self);
void func_0011D928(s32 a);
void func_001C06A0(s32 a, s32 b, f32 x);

void func_001BF048(Entry_1BF048* self)
{
    if (self != 0) {
        s32 key = self->key;
        func_001BEDF8(self);
        if (key == D_00274734) {
            func_001BEF88(self);
            s32 cur = D_00274734;
            if (cur >= 0) {
                D_002748EC = 0;
            }
            D_00274738 = cur;
            func_0011D928(cur + 0x14);
            func_001C06A0(7, 1, 1.0f);
            D_00274738 = -0x64;
        }
    }
}

typedef signed int s32;
typedef unsigned char u8;

void func_001BE068(u8* base, s32 stride, s32 rowB, s32 rowA)
{
    s32* b = (s32*)(base + rowB * stride);
    s32* a = (s32*)(base + rowA * stride);
    for (s32 n = stride; n > 0; n -= 4) {
        s32 y = *a;
        s32 x = *b;
        *b = y;
        *a = x;
        a++;
        b++;
    }
}

typedef signed int s32;

extern s32 D_00274720;
extern s32 D_00274728;
extern s32 D_0027473C;

s32 func_0011CE30(void);
void func_0011D450(s32 handle);
void func_0011D600(s32 handle);

void func_001BE1E8(void)
{
    if (D_0027473C != 0) {
        if (D_00274728 != 0) {
            func_0011D600(D_00274728);
        }
        func_0011D450(D_0027473C);
        while (func_0011CE30() != 0) {
        }
        D_0027473C = 0;
    }
    D_00274720 = 0;
    D_00274728 = 0;
}

struct Obj_1BF0D8 { s32 kind; };

extern s32 D_00274734;
extern s32 D_00274738;

void func_001BEDF8(Obj_1BF0D8* self);
void func_001BEF88(Obj_1BF0D8* self);

void func_001BF0D8(Obj_1BF0D8* self)
{
    if (self == 0) {
        return;
    }
    s32 k = self->kind;
    func_001BEDF8(self);
    if (k == D_00274734) {
        D_00274738 = k;
        func_001BEF88(self);
    }
}

extern s32 D_0027472C;

s32 func_001BE980(void)
{
    return D_0027472C != 0;
}

typedef void (*Fn_001BF578)(void);

extern u8* D_00261990;
s32 func_001493A0(u8* p);
s32 func_00149638(u8* s);
void func_001BF398(void);
void func_001BF2E0(void);

Fn_001BF578 func_001BF578(void)
{
    s32 n;
    if (func_001493A0(D_00261990 + 0x460) == 0) return func_001BF398;
    n = func_00149638(D_00261990 + 0x460);
    if (n >= 3) return func_001BF398;
    if (n <= 0) return func_001BF398;
    return func_001BF2E0;
}

struct Rec_1BE4D8 {
    s32 f00;
    f32 f04;
    f32 f08;
    f32 f0C;
    s32 f10;
    f32 f14;
    u8 pad18[4];
    s32 f1C;
    s32 f20;
};

struct Owner_1BE4D8 {
    Rec_1BE4D8* rec;
};

void* func_0018D5C0(s32 bytes);

void func_001BE4D8(Owner_1BE4D8* self)
{
    self->rec = (Rec_1BE4D8*)func_0018D5C0(0x24);
    self->rec->f00 = -1;
    self->rec->f04 = 3000.0f;
    self->rec->f08 = 300.0f;
    self->rec->f0C = 1.0f;
    self->rec->f10 = 0;
    self->rec->f1C = 0;
    self->rec->f14 = -1.0f;
    self->rec->f20 = 0;
}

extern s32 D_00274730;

void func_001BE5D8(void)
{
    D_00274730 = 0;
}

extern s32 D_0027472C;

void func_0011D640(s32 a);

void func_001BEA28(void)
{
    if (D_0027472C != 0) {
        func_0011D640(D_0027472C);
    }
}

extern s32 D_0027472C;

void func_0011D670(s32 a);

void func_001BEA50(void)
{
    if (D_0027472C != 0) {
        func_0011D670(D_0027472C);
    }
}

extern s32 D_00274744;
s32 func_001BE5E8(void) { return D_00274744; }

extern s32 D_00274748;
s32 func_001BF1F0(void) { return D_00274748; }

typedef s32 (*Cmp_1BE0A8)(void* a, void* b);

void func_001BE068(u8* base, s32 stride, s32 rowB, s32 rowA);

void func_001BE0A8(u8* base, s32 n, s32 size, Cmp_1BE0A8 cmp)
{
    if (n < 2) return;
    s32 end = n - 1;
    s32 start = n / 2;
    for (;;) {
        if (start > 0) {
            start--;
        } else {
            func_001BE068(base, size, end, 0);
            s32 t = end;
            end = t - 1;
            if (t < 2) return;
        }
        s32 i = start;
        s32 c = 2 * i + 1;
        if (end < c) continue;
        for (;;) {
            if (c < end) {
                s32 s0 = c + 1;
                if (cmp(base + c * size, base + s0 * size) < 0) c = s0;
            }
            if (cmp(base + i * size, base + c * size) < 0) {
                func_001BE068(base, size, i, c);
                i = c;
                c = c + (c + 1);
                if (end < c) break;
                continue;
            }
            break;
        }
    }
}

extern s32 D_00274744;
extern s32 D_0027472C;
extern s32 D_00274730;

s32 func_001BE980(void);
void func_001BE998(void);
void func_0018D410(void* p);
s32 func_0011E048(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8);
void func_001C06A0(s32 a, s32 b, f32 x);

struct Obj_1BE5F8 { s32 w0; s32 w4; u8 pad8[0xC]; s32 w14; u8 pad18[4]; s32 w1C; };
struct Local_1BE5F8 { s32 a; s32 b; };

void func_001BE5F8(Obj_1BE5F8* self)
{
    if (D_00274744 != 0) {
        return;
    }
    if (self == 0) {
        return;
    }
    Local_1BE5F8 l;
    Local_1BE5F8* p;
    if (func_001BE980() != 0) {
        func_001BE998();
    }
    p = &l;
    func_0018D410(p);
    s32 b = self->w4 ^ self->w1C;
    p->b = b;
    p->a = self->w0 ^ self->w14;
    if (b == 0) {
        return;
    }
    s32 h = func_0011E048(p->a, 0, 0, 0, 0x400, 0, 2, 0, 0);
    if (h == 0) {
        return;
    }
    D_0027472C = h;
    D_00274744 = 1;
    D_00274730 = 0;
    func_001C06A0(8, 1, 0.5f);
    func_001C06A0(8, 0, 0.5f);
    func_001C06A0(8, 3, 0.5f);
}

extern s32 D_00274744;
extern s32 D_0027472C;
extern s32 D_00274730;

s32 func_001BE980(void);
void func_001BE998(void);
void func_001BE5D8(void);
void func_0018D410(void* p);
s32 func_0011E048(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8);
void func_0011E0E0(s32 a0, void (*a1)(void), u64 a2);

struct Obj_1BE728 { s32 w0; s32 w4; u8 pad8[0xC]; s32 w14; u8 pad18[4]; s32 w1C; };
struct Local_1BE728 { s32 a; s32 b; };

void func_001BE728(Obj_1BE728* self)
{
    if (D_00274744 != 0) {
        return;
    }
    Local_1BE728 l;
    Local_1BE728* p;
    if (func_001BE980() != 0) {
        func_001BE998();
    }
    p = &l;
    func_0018D410(p);
    s32 r = 0;
    if (self != 0) {
        s32 b = self->w4 ^ self->w1C;
        p->b = b;
        l.a = self->w0 ^ self->w14;
        r = b != 0;
    }
    if (r == 0) {
        return;
    }
    s32 h = func_0011E048(l.a, 0, 0, 0, 0x400, 0, 2, 0, 1);
    if (h == 0) {
        return;
    }
    D_0027472C = h;
    D_00274730 = 1;
    func_0011E0E0(h, func_001BE5D8, (u32)h);
}

extern s32 D_00274720;
extern s32 D_00274728;

void func_0011D600(s32 handle);

void func_001BEA78(void)
{
    if (D_00274720 == 3) {
        func_0011D600(D_00274728);
        D_00274728 = 0;
        D_00274720 = 2;
    }
}

extern s32 D_0027473C;
extern s32 D_00274720;
extern s32 D_00274724;

void func_0011D420(void);

void func_001BEAC8(s32 h)
{
    D_0027473C = h;
    if (h != 0) {
        func_0011D420();
        D_00274720 = 2;
    } else {
        D_00274724 = 0;
        D_00274720 = 0;
    }
}

void func_001C06A0(s32 a, s32 b, f32 x);

void func_001BECF8(void)
{
    func_001C06A0(2, 1, 0.0f);
}

extern u8* D_00261990;

void* func_001925F0(void);

typedef s32 (*VFn_001BF3D0)(void* self);

struct Obj_001BF3D0 {
    VFn_001BF3D0* vtbl;
};

void* func_001BF3D0(void)
{
    Obj_001BF3D0* p = (Obj_001BF3D0*)func_001925F0();
    u8* r;
    if (p != 0 && p->vtbl[78](p) != 0) {
        r = (u8*)p + 0x140;
    } else {
        r = D_00261990 + 0x40;
    }
    return r;
}

f32 func_001BF5E0(void* self);
void func_001BF200(f32 r, void* self, f32* out, s32* flag, f32 a, f32 b, f32 c);

void func_001BF620(void* self, f32* out, s32* flag, f32 a, f32 b, f32 c)
{
    if (self != 0) {
        f32 r = func_001BF5E0(self);
        func_001BF200(r, self, out, flag, a, b, c);
    } else {
        *out = a;
        *flag = 0;
    }
}

struct Obj_1BE860 { u8 pad0[0x18]; void* f18; u8 pad1[0x34]; f32 f50; f32 f54; };

void func_0011D798(void* a0, s32 a1, s32 a2);

void func_001BE860(Obj_1BE860* self)
{
    s32 a1 = (s32)(self->f50 * 1024.0f);
    s32 a2;
    if (0.0f < self->f54) {
        a2 = (s32)((self->f54 + 2.0f) * 179.5f) - 359;
    } else {
        a2 = (s32)((self->f54 + 2.0f) * 179.5f);
    }
    func_0011D798(self->f18, a1, a2);
}

void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_001BE860(void* self);
void func_001BF718(void* slot);

void func_001BE8F8(s32 a0, void** a1, f32 f12, f32 f13)
{
    s32 flag = 0;
    void* local;
    void** p = a1;
    if (p == 0) {
        flag = 1;
        p = (void**)&local;
    }
    func_001BFCD8(-2, p, a0, 0, f12, f13, 1.0f, 0.0f, 0.0f, 0, 0);
    if (*p != 0) {
        func_001BE860(*p);
        if (flag != 0) {
            func_001BF718(p);
        }
    }
}

struct Rec_1BEB10 { s32 f0; s32 f4; s32 f8; u8 pad0[8]; s32 f14; s32 f18; s32 f1C; };

extern s32 D_00274720;

void func_001BEA78(void);
void func_001BE1E8(void);
void func_0018D410(void* p);
s32 func_0011E1F8(s32 a);
s32 func_0011CE30(void);
void func_001F6C20(s32 a);
void func_001BEAC8(s32 h);
void func_0011D2A8(s32 a0, s32 a1, void* a2, s32 a3);

void func_001BEB10(Rec_1BEB10* self)
{
    s32 local[2];
    s32 same;
    s32 flag;

    if (self == 0) {
        func_001BEA78();
        return;
    }
    Rec_1BEB10* old = (Rec_1BEB10*)D_00274724;
    if (self == old) {
        same = 1;
    } else if (self == 0) {
        same = 0;
    } else if (old == 0) {
        same = 0;
    } else {
        same = ((self->f8 ^ self->f18) ^ (old->f8 ^ old->f18)) == 0;
    }
    if (same != 0 && D_00274720 != 0) {
        return;
    }
    while (func_0011CE30() != 0 && D_00274720 == 1) {
        func_001F6C20(0);
    }
    func_001BE1E8();
    D_00274724 = (s32)self;
    func_0018D410(local);
    if (self == 0) {
        flag = 0;
    } else {
        s32 x = self->f4 ^ self->f1C;
        local[0] = self->f0 ^ self->f14;
        local[1] = x;
        flag = x != 0;
    }
    if (flag != 0) {
        D_00274720 = 1;
        func_0011E1F8(0);
        func_0011D2A8(local[0], 0, (void*)func_001BEAC8, 0);
    }
}

struct Node_1BD888 { void* f0; Node_1BD888* f4; };
struct Chain_1BD888 { Node_1BD888* head; };
struct Obj_1BD888 { u8 pad0[0x480]; Chain_1BD888* f480; u8 pad1[0xB4]; u64 f538; };

void func_0018D608(void);
void* func_0018D658(s32 size);
void func_001F5C0C(void* p, s32 zero, s32 size);
void func_0018D800(void* dst, void* src, s32 count);
void func_0018D6F0(void);

void func_001BD888(s32 n, Obj_1BD888** objs)
{
    s32 local[5];
    Obj_1BD888** sorted;
    s32* counts;
    s32 i;

    if (n < 2) {
        return;
    }
    func_0018D608();
    sorted = (Obj_1BD888**)func_0018D658(n * 4);
    counts = (s32*)func_0018D658(n * 4);
    func_001F5C0C(counts, 0, n * 4);
    func_001F5C0C(local, 0, 20);
    for (i = 0; i < n; i++) {
        Obj_1BD888* o = objs[i];
        u32 cnt = 0;
        Node_1BD888* p = o->f480->head;
        while (p != 0) {
            if (p->f0 != 0 && (o->f538 & 0x0080000000000000ULL) != 0) {
                cnt++;
                if (cnt >= 4) {
                    break;
                }
            }
            p = p->f4;
        }
        counts[i] = cnt;
        if (cnt < 4) {
            local[cnt + 1]++;
        }
    }
    i = 1;
    do {
        local[i] += local[i - 1];
        i++;
    } while ((u32)i < 5);
    for (i = 0; i < n; i++) {
        s32 cnt = counts[i];
        s32 idx = local[cnt];
        sorted[idx] = objs[i];
        local[cnt] = idx + 1;
    }
    func_0018D800(objs, sorted, n * 4);
    func_0018D6F0();
}

extern u8* D_00275710;
extern s32 D_00274734;
extern s32 D_00274738;

s32 func_00152720(void* a);
void* func_001BED98(void);

void* func_001BEEF8(s32 x)
{
    s32 flag = func_00152720(D_00275710 + 0x1BC4);
    void* p = func_001BED98();
    s32 hi = 0x6B;
    s32 v = -20;
    if (x >= -20) {
        if (hi < x) v = hi; else v = x;
    }
    if (p != 0) {
        *(s32*)p = v;
        s32 cur = D_00274734;
        if (cur < v || flag != 0) {
            D_00274734 = v;
            D_00274738 = cur;
        }
    }
    return p;
}

struct Item_1BD558 { u8 pad0[0xD0]; Item_1BD558* next; };
struct Node_1BD558;
struct Group_1BD558 { Item_1BD558* items; Group_1BD558* next; u8 pad[4]; Node_1BD558* child; };
struct GroupHead_1BD558 { Group_1BD558* first; };
struct Node_1BD558 { u8 pad0[0x480]; GroupHead_1BD558* groups; u8 pad1[0x4B4 - 0x484]; Item_1BD558* items; u8 pad2[0x538 - 0x4B8]; u64 flags; };

s32 func_001BD558(s32 count, Node_1BD558** roots, s32 cap, Item_1BD558** out)
{
    s32 n = 0;
    s32 i;
    Node_1BD558* root;
    for (i = 0; i < count; i++) {
        root = roots[i];
        root->flags |= ((u64)1 << 58);
        for (Item_1BD558* item = root->items; item; item = item->next) {
            if (n >= cap) goto done;
            out[n++] = item;
        }
        GroupHead_1BD558* gh = root->groups;
        for (Group_1BD558* g = gh->first; g; g = g->next) {
            if (g->child->flags & ((u64)1 << 58)) continue;
            for (Item_1BD558* item = g->items; item; item = item->next) {
                if (n >= cap) goto done;
                out[n++] = item;
            }
        }
    }
done:
    {
        Node_1BD558** r = roots;
        if (count > 0) {
            i = count;
            do {
                root = *r;
                i--;
                r++;
                root->flags &= ~((u64)1 << 58);
            } while (i != 0);
        }
    }
    return n;
}

extern s32 D_00274744;
extern s32 D_0027472C;
extern s32 D_00274730;

void func_0011D600(s32 handle);
s32 func_0011D708(s32 handle);

void func_001BE998(void)
{
    s32 r;
    if (D_00274744 != 0) return;
    if (D_0027472C == 0) return;
    func_0011D600(D_0027472C);
    while ((r = func_0011D708(D_0027472C)) != 0) {
        r = 0x4E20;
        while (--r >= 0) {
        }
    }
    D_0027472C = 0;
    D_00274730 = 0;
}

struct Obj_1BD790 {
    u8 pad0[0x90]; s32 save90; s32 save94; u8 pad1[0xC0 - 0x98]; u64 saved;
    u8 pad2[0x450 - 0xC8]; s32 f450; u8 pad3[0x470 - 0x454]; s32 f470;
    u8 pad4[0x538 - 0x474]; u64 flags;
};

void func_001BD790(Obj_1BD790* obj, s32 mode)
{
    if (mode) {
        u64 f = obj->flags;
        u64 sv = obj->saved;
        sv &= ~(u64)1;
        sv |= (f >> 54) & 1;
        sv &= ~(u64)2;
        u64 b55 = (f >> 55) & 1;
        f |= (u64)1 << 54;
        s32 a = obj->f450;
        s32 b = obj->f470;
        f |= (u64)1 << 55;
        sv |= b55 << 1;
        obj->save90 = a;
        obj->save94 = b;
        obj->saved = sv;
        obj->f450 = 3;
        obj->f470 = 3;
        obj->flags = f;
    } else {
        u64 bit0 = (s32)obj->saved & 1;
        u64 bit1 = (u64)((s32)(obj->saved >> 1) & 1);
        s32 a = obj->save90;
        s32 b = obj->save94;
        obj->f450 = a;
        obj->f470 = b;
        obj->flags = ((obj->flags & ~((u64)1 << 54)) | (bit0 << 54)) & ~((u64)1 << 55) | (bit1 << 55);
    }
}

extern u8 D_0027B314[];
extern f32 D_00261858[];

struct Frame_1BDD00 { s32 list; s32 cursor; s32 link; s32 prev; };
struct Cnt_1BDD00 { s32 pad; s32 n1; s32 n2; };
struct Cls_1BDD00;
struct Node_1BDD00;
typedef void (*VFn_1BDD00)(Node_1BDD00* self, s32 a, f32 f);
struct Cls_1BDD00 {
    u8 pad0[8];
    s32 flags;
    u8 pad0C[0x70];
    VFn_1BDD00 fn7C;
};
struct Node_1BDD00 {
    Cls_1BDD00* cls;
    u8 pad4[0x224];
    s32 f228;
    u8 pad22C[0x30C];
    u64 flags538;
};
struct Obj_1BDD00 {
    u8 pad0[0x38];
    s32 count;
    s32 head3C;
    u8 pad40[0x20];
    s32 list60;
    u8 pad64[8];
    Node_1BDD00* head6C;
};
struct Item_1BDD00 {
    u8 pad0[0x414];
    Item_1BDD00* next;
};

void func_0018D608();
void func_0018D6F0();
void func_001F6C20(s32 a);
void func_001BD678(Node_1BDD00* n, s32* c1, Node_1BDD00** a1, s32* c2, Node_1BDD00** a2);
void func_001BDA50(Obj_1BDD00* ctx, s32 n, Node_1BDD00** arr, f32 f, s32 flags);
s32 func_00129D70(Node_1BDD00* n);
void func_00129DF8(Node_1BDD00* n);

void func_001BDD00(Obj_1BDD00* self, s32 flags, f32 f)
{
    Frame_1BDD00 fr;
    Cnt_1BDD00 c;
    Node_1BDD00** arr1;
    Node_1BDD00** arr2;
    s32 j;
    s32 i;
    Node_1BDD00* s;
    func_0018D608();
    arr1 = (Node_1BDD00**)func_0018D658(self->count * 4);
    c.n1 = 0;
    arr2 = (Node_1BDD00**)func_0018D658(self->count * 4);
    c.n2 = 0;
    func_001F6C20(0);
    if (flags & 1) {
        s32 e = (s32)&self->list60;
        fr.cursor = e;
        fr.list = e;
        s32 old = *(s32*)D_0027B314;
        s32 link = *(s32*)(e + 8);
        *(s32*)D_0027B314 = (s32)&fr;
        fr.prev = old;
        s32 h = *(s32*)e;
        fr.link = link;
        fr.cursor = h + link;
        s32 p = h;
        while (p != 0) {
            Node_1BDD00* node = (Node_1BDD00*)p;
            if (!(node->cls->flags & 2) || (node->flags538 & (1ULL << 55))) {
                if (node->f228 < 2) {
                    node->cls->fn7C(node, 0, D_00261858[2]);
                }
            }
            s32 nx = *(s32*)fr.cursor;
            fr.cursor = nx + fr.link;
            p = nx;
        }
        *(s32*)D_0027B314 = fr.prev;
    }
    for (s = self->head6C; s != 0; s = (Node_1BDD00*)((Item_1BDD00*)s)->next) {
        if (s->flags538 & (1ULL << 57)) continue;
        if (s->flags538 & (1ULL << 55)) continue;
        func_001BD678(s, &c.n1, arr1, &c.n2, arr2);
        if (flags & 1) {
            for (i = 0; i < c.n1; i++) {
                if (arr1[i]->f228 < 2) break;
            }
            if (i >= c.n1) {
                for (j = 0; j < c.n2; j++) {
                    if (arr2[j]->f228 < 2) break;
                }
                if (j >= c.n2) continue;
            }
            for (i = 0; i < c.n1; i++) {
                arr1[i]->cls->fn7C(arr1[i], 0, D_00261858[2]);
            }
        }
        func_001BDA50(self, c.n1, arr1, f, flags);
        for (i = 0; i < c.n1; i++) {
            if (!func_00129D70(arr1[i])) {
                func_00129DF8(arr1[i]);
            }
        }
    }
    for (s = (Node_1BDD00*)self->head3C; s != 0; s = *(Node_1BDD00**)((u8*)s + 0x2D0)) {
        s->flags538 &= ~(1ULL << 57);
    }
    func_0018D6F0();
}

extern s32 D_00274744;
extern s32 D_0027472C;
extern s32 D_00274730;

void func_0011E0B0(s32 a0);

s32 func_001BE810(void)
{
    if (D_00274744 != 0)
        return 0;
    if (D_0027472C != 0) {
        if (D_00274730 != 0)
            return 1;
        func_0011E0B0(D_0027472C);
    }
    return 0;
}

struct Ent_1BE4A8 { u8 pad[0]; };

struct Ent_1BFAF8 { s32 a; s32 b; };
extern Ent_1BFAF8 D_00245020[];
void func_001BE268(Ent_1BE4A8* e);

void func_001BE4A8(s32 idx)
{
    func_001BE268(*(Ent_1BE4A8**)((u8*)D_00245020 + idx * 8));
}

struct Sel_1BE568;
struct Pair_1BE568 { s32 key; s32 w4; };

extern u8 D_006047B0[];
extern u8 D_006047D0[];
void func_001BE4A8(Sel_1BE568* self);

s32 func_001BE568(s32 idx)
{
    Pair_1BE568* p = (Pair_1BE568*)D_00245020 + idx;

    if (((s32*)D_006047B0)[p->key] == 0) {
        func_001BE4A8((Sel_1BE568*)idx);
    }
    return ((s32*)D_006047D0)[idx];
}

// NEAR: the lui of D_0026185C is scheduled before the sw of self->idx; retail stores idx first. Otherwise every instruction matches.

struct Idx_1BFAF8;
struct Link_1BFAF8;
struct Node_1BFAF8 {
    s32 idx;            // 0x00
    u8 pad04[0x04];
    s32 link;           // 0x08
    u8 pad0c[0x04];
    f32 f10;            // 0x10
    u8 pad14[0x04];
    s32 f18;            // 0x18
    u8 pad1c[0x24];
    s32 f40;            // 0x40
    u8 pad44[0x0C];
    f32 f50;            // 0x50
    u8 pad54[0x04];
    f32 f58;            // 0x58
    u8 pad5c[0x1C];
    f32 f78;            // 0x78
};

extern f32 D_0026185C[];
extern s32 D_0027472C;

s32 func_001BE4A8(Idx_1BFAF8* idx);
s32 func_0011D598(Link_1BFAF8* a, s32 b, s32 c, s32 d, s32 e, s32 f);
void func_001BF428(Node_1BFAF8* self);
void func_001BF7F8(Node_1BFAF8* self, f32 x);
void func_001BE860(Node_1BFAF8* self);

void func_001BFAF8(Node_1BFAF8* self, s32 idx)
{
    s32 link;
    s32 v3;
    if (idx != -2) {
        link = func_001BE4A8((Idx_1BFAF8*)idx);
        v3 = D_00245020[idx].b;
        self->link = link;
    }
    self->idx = idx;
    self->f10 = D_0026185C[0];
    if (idx == -2) {
        v3 = D_0027472C;
        self->f40 = 0;
        self->f18 = v3;
        return;
    }
    if (self->f50 != 0.0f && self->f78 < 0.0f) {
        s32 r = func_0011D598((Link_1BFAF8*)link, v3, 0, 0, 0, 0);
        self->f40 = 0;
        self->f18 = r;
        func_001BF428(self);
        func_001BF7F8(self, self->f58);
        func_001BE860(self);
    } else {
        self->f18 = 0;
        self->f40 = 1;
    }
}

// NEAR: first load of the chain pointer lands in $v1 and the sum in $v0, retail has them in $v0/$v1; one instruction short so the final branch targets 0x1BF028 instead of 0x1BF02C

struct Frame_1BEF88 { s32 f0; s32 f4; s32 f8; s32 fC; };

extern s32 D_00274734;

s32 func_00152720(Frame_1BEF88* p);

void func_001BEF88(void)
{
    Frame_1BEF88 f;
    s32 P = (s32)D_00275710 + 0x1BC4;
    s32 x;
    f.f0 = P;
    f.f4 = P;
    f.f8 = *(s32*)(P + 8);
    f.fC = *(s32*)D_0027B314;
    *(s32*)D_0027B314 = (s32)&f;
    if (func_00152720((Frame_1BEF88*)P) != 0) {
        D_00274734 = 0;
    } else {
        D_00274734 = -20;
        s32 x0 = *(s32*)f.f4;
        f.f4 = x0 + f.f8;
        x = x0;
        if (x != 0) {
            do {
                s32 v = *(s32*)x;
                if (D_00274734 < v) {
                    D_00274734 = v;
                }
                s32 y = *(s32*)f.f4;
                f.f4 = y + f.f8;
                x = y;
            } while (x != 0);
        }
    }
    *(s32*)D_0027B314 = f.fC;
}

// NEAR: 23 diff lines, register allocation only: queue index in t1 (retail) vs v1 (ours), mask built in a0 vs a2, cleanup counter in t1 vs a0

struct Obj_1BD678;
struct Node_1BD678;

struct Holder_1BD678 {
    Node_1BD678* head;
};

struct Node_1BD678 {
    Obj_1BD678* list0;
    Node_1BD678* next4;
    u8 pad[4];
    Obj_1BD678* owner;
};

struct Obj_1BD678 {
    u8 pad0[0x480];
    Holder_1BD678* holder480;
    u8 pad1[0x538 - 0x484];
    u64 flags;
};

void func_001BD678(Obj_1BD678* self, s32* outQueued, Obj_1BD678** queue, s32* outFlagged, Obj_1BD678** list)
{
    s32 nq = 1;
    s32 nl = 0;
    queue[0] = self;
    self->flags |= (u64)1 << 57;
    s32 qi;
    for (qi = 0; qi < nq; qi++) {
        Obj_1BD678* x = queue[qi];
        Node_1BD678* node = x->holder480->head;
        while (node != 0) {
            Obj_1BD678* y = node->owner;
            if ((y->flags & ((u64)1 << 57)) == 0 && node->list0 != 0) {
                if (y->flags & ((u64)1 << 55)) {
                    list[nl] = y;
                    nl++;
                } else {
                    queue[nq] = y;
                    nq++;
                }
                y->flags |= (u64)1 << 57;
            }
            node = node->next4;
        }
    }
    if (nl > 0) {
        qi = nl;
        Obj_1BD678** p = list;
        do {
            Obj_1BD678* z = *p;
            p++;
            z->flags &= ~((u64)1 << 57);
        } while (--qi != 0);
    }
    *outQueued = nq;
    *outFlagged = nl;
}

struct Ent_1BF7F8 {
    s32 idx;
    s32 f4;
    s32 f8;
    u8 pad0C[0xC];
    s32 f18;
    u8 pad1C[0x14];
    s32 f30;
    u8 pad34[0x24];
    f32 f58;
    f32 f5C;
    s32 f60;
    u8 pad64[8];
    s32 flag6C;
    s32 f70;
    s32 clampv(s32 v, s32 lo, s32 hi)
    {
        if (v < lo) {
            return lo;
        }
        if (hi < v) {
            return hi;
        }
        return v;
    }
};

s32 func_0011D7D8(s32 a, s32 b);
void func_0011D810(s32 x, s32 y);

void func_001BF7F8(Ent_1BF7F8* p, f32 a)
{
    if (p == 0) {
        return;
    }
    if (a == p->f58) {
        if (p->f30 == 0) {
            return;
        }
        if (!(0.0001f < p->f5C)) {
            return;
        }
    }
    s32 v0 = p->flag6C;
    p->f58 = a;
    if (v0 == 0) {
        p->f70 = func_0011D7D8(p->f8, D_00245020[p->idx].b);
        p->flag6C = 1;
    }
    s32 v = p->f70 + (s32)(p->f58 * 1524.0f) + p->f60;
    func_0011D810(p->f18, p->clampv(v, -0x8000, 0x7FFF));
}
