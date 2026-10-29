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
