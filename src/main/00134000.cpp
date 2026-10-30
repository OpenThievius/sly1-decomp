// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Node_1363D0 { u8 pad0[0x324]; void* child; };

void func_001AA8C8(void* self);
s32 func_00150790(void* obj, s32 mode);

void func_001363D0(Node_1363D0* self)
{
    func_001AA8C8(self);
    if (self->child != 0) {
        func_00150790(self->child, 2);
    }
}

struct Child_136EF8 { u8 pad0[0x2D0]; s32 kind; };
struct Owner_136EF8 { u8 pad0[0x324]; Child_136EF8* child; };

void func_001356C0(Owner_136EF8* self, s32 mode);
void func_00150790(Child_136EF8* obj, s32 mode);

void func_00136EF8(Owner_136EF8* self)
{
    if (self->child != 0) {
        switch (self->child->kind) {
        case 0:
            func_001356C0(self, 2);
            break;
        case 1:
            func_001356C0(self, 3);
            break;
        case 2:
            func_001356C0(self, 4);
            break;
        }
        func_00150790(self->child, 3);
    } else {
        func_001356C0(self, 1);
    }
}

struct Obj_137268 { u8 pad[0x18]; void* field18; };

void func_00137268(Obj_137268* self, void* value)
{
    self->field18 = value;
}

struct Pair_1373B0 { void* first; s32 second; };

void func_00137328(void* a, void* b, s32 c);

void func_001373B0(void* a, Pair_1373B0* pair)
{
    func_00137328(a, pair->first, pair->second);
}

struct Ring_137B60 { u8 pad0[0x18]; s32 head; s32 size; };

void func_00137B60(Ring_137B60* self, s32 n)
{
    s32 head = self->head;
    s32 t = head - 1;
    t = t + n;
    s32 aligned = t & -n;
    s32 delta = aligned - head;
    self->head = aligned;
    self->size -= delta;
}

struct Entry_1357F0 {
    void* obj;
    f32 key;
};

s32 func_00182FC8(void* obj);

s32 func_001357F0(Entry_1357F0* a, Entry_1357F0* b)
{
    if (func_00182FC8(a->obj) == 0) {
        return 1;
    }
    if (func_00182FC8(b->obj) == 0) {
        return -1;
    }
    if (a->key < b->key) {
        return -1;
    }
    return 1;
}

struct Entry_135858 {
    void* obj;
    f32 key;
};

void func_00199C10(void* obj, s32* out);

s32 func_00135858(Entry_135858* a, Entry_135858* b)
{
    s32 flag;

    func_00199C10(a->obj, &flag);
    if (flag != 0) {
        return 1;
    }
    func_00199C10(b->obj, &flag);
    if (flag != 0) {
        return -1;
    }
    if (a->key < b->key) {
        return -1;
    }
    return 1;
}

struct Chan_1373D0 {
    s32 a00;
    s32 mode;
    s32 a08;
    s32 a0C;
    s32 a10;
    s32 a14;
    s32 a18;
    s32 a1C;
    s32 a20;
    s32 a24;
    s32 a28;
    s32 a2C;
    void* a30;
    void* a34;
    s32 a38;
    s32 a3C;
    s32 a40;
};

s32 func_00137480(Chan_1373D0* self, s32 n)
{
    return self->a40 -= n;
}

struct SlotEntry_135E78 { void* handle; s32 extra; };

struct SlotBank_135E78 {
    u8 pad0[0x328];
    s32 state;
    u8 pad1[0x4];
    u8 blockA[0x10];
    u8 blockB[0x10];
    s32 countA;
    s32 count;
    u8 pad2[0x4];
    SlotEntry_135E78 entries[1];
};

void func_0019EBE8(void* handle);
void func_001A1DF0(void* handle, s32 mode);
void func_001F5C0C(void* block, s32 value, s32 size);

void func_00135E78(SlotBank_135E78* self, s32 state, s32 flag)
{
    if (state == self->state) return;
    s32 i = 0;
    u8* blockA = self->blockA;
    if (self->count > 0) {
        SlotEntry_135E78* e = self->entries;
        do {
            if (flag != 0) {
                func_0019EBE8(e->handle);
                func_001F5C0C(self->blockB, 0, 16);
            } else {
                func_001A1DF0(e->handle, 2);
            }
            i++;
            e++;
        } while (i < self->count);
    }
    self->count = 0;
    self->countA = 0;
    func_001F5C0C(blockA, 0, 16);
    self->state = state;
}

struct Owner_136FA8 { u8 pad0[0x324]; void* child; };

s32 func_001356C0(Owner_136FA8* self, s32 mode);

s32 func_00136FA8(Owner_136FA8* self)
{
    s32 r;
    if (self->child != 0) {
        r = func_00150790(self->child, 4);
        goto done;
    }
    r = func_001356C0(self, 0);
done:
    return r;
}

struct Pair_137228 { f32 x; f32 y; };

void func_00137228(Pair_137228* out, f32 x, f32 y)
{
    out->x = x;
    out->y = y;
}

struct Reader_137D10 { u8 pad0[0x18]; u8* cur_18; s32 remaining_1C; };

void func_00137A60(void* self, s32 count, void* out);

s32 func_00137D10(Reader_137D10* self)
{
    if (self->remaining_1C >= 2) {
        u8* p = self->cur_18;
        u8 lo = p[0];
        s32 hi = p[1];
        self->cur_18 = p + 2;
        self->remaining_1C -= 2;
        return lo | ((s16)(hi << 8));
    }
    s16 tmp;
    func_00137A60(self, 2, &tmp);
    return tmp;
}

struct Vec2_137238 { u8 pad0[0x8]; f32 x; f32 y; };

void func_00137238(void* out, f32 x, f32 y)
{
    Vec2_137238* v = (Vec2_137238*)out;
    v->x = x;
    v->y = y;
}

struct __attribute__((packed)) Unaligned_137248 { u32 value; };

void func_00137248(void* out, s32* value)
{
    *(Unaligned_137248*)((u8*)out + 0x10) = *(Unaligned_137248*)value;
}

struct Reader_137DF8 {
    u8 pad0[0x18];
    u8* cursor_18;
    s32 left_1C;
};

void func_00137A60(void* self, s32 size, void* dst);

f32 func_00137DF8(Reader_137DF8* r)
{
    s32 left = r->left_1C;
    if (left >= 4) {
        u8* p = r->cursor_18;
        u32 v = p[0] + (p[1] << 8) + (p[2] << 16) + (p[3] << 24);
        r->cursor_18 = p + 4;
        r->left_1C = left - 4;
        return *(f32*)&v;
    }
    f32 tmp;
    func_00137A60(r, 4, &tmp);
    return tmp;
}

void func_00137A60(void* self, s32 size, void* dst);

void func_00137E70(void* src, void* dst)
{
    func_00137A60(src, 12, dst);
}

// Newly matched US functions from the small-function wave.
struct Obj_1365A0 { u8 pad[0x2FC]; s32 f2FC; };
struct Obj_137260 { u8 pad[0x14]; s32 f14; };
extern void func_00136FE8(s32, s32);
extern void func_001373D0(void*);
extern void func_0018D778(void*);
struct Obj_137398 { u8 pad0[4]; s32 state; u8 pad8[0x10]; s32 f18; s32 f1C; };
extern void func_00137A60(void*, s32, void*);

void func_001365A0(Obj_1365A0* self, s32 value) { self->f2FC = value; }

void func_00137260(Obj_137260* self, s32 value) { self->f14 = value; }

void func_00137270() { func_00136FE8(1, 0xFFFF); }

void func_001372E0(void* self, s32 flags)
{
    func_001373D0(self);
    if (flags & 1) func_0018D778(self);
}

void func_00137398(Obj_137398* self, s32 a1, s32 a2) { self->f1C = a1; self->f18 = a2; self->state = 2; }

void func_00137E90(void* self, void* out) { func_00137A60(self, 0x10, out); }

void func_00137EB0(void* self, u8* buffer)
{
    func_00137A60(self, 0xC, buffer);
    func_00137A60(self, 0xC, buffer + 0x10);
    func_00137A60(self, 0xC, buffer + 0x20);
}

struct State_001365A8 { u8 pad[0x300]; f32 value;
    void set(f32 x, f32 lo, f32 hi) {
        if (x < lo) x = lo;
        else if (hi < x) x = hi;
        value = x;
    }
};
void func_001365A8(State_001365A8* self, f32 value)
{
    self->set(value * 0.01f, 0.0f, 1.0f);
}

struct State_00136EC8 { u8 pad[0x304]; f32 x; f32 y; };
void func_00136EC8(State_00136EC8* self, f32* x, f32* y)
{
    *x = self->x + 320.0f;
    *y = self->y + 180.4000091552734375f;
}

struct State_00137820 { s32 w[13]; s32 maximum(s32 a, s32 b) { return a < b ? b : a; } };
void func_001377C0(void* self);
void func_00137490(void* self);
void func_00193288(void* self, s32 value);
void func_00137820(State_00137820* self)
{
    switch (self->w[1]) {
    case 0: func_001377C0(self); break;
    case 1: func_00137490(self); break;
    }
    s32 value = self->w[5] - self->w[9];
    value = self->maximum(0, value);
    self->w[5] = value;
    if (self->w[12]) func_00193288((void*)self->w[12], value);
}

s32 func_00137B90(Reader_137D10* self)
{
    s32 count = self->remaining_1C;
    if (count >= 1) {
        u8* p = self->cur_18;
        s32 value = p[0];
        self->cur_18 = p + 1;
        self->remaining_1C = count - 1;
        return value;
    }
    u8 value;
    func_00137A60(self, 1, &value);
    return value;
}

s32 func_00137BE0(Reader_137D10* self)
{
    s32 count = self->remaining_1C;
    if (count >= 2) {
        u8* p = self->cur_18;
        s32 value = p[0] | (p[1] << 8);
        self->cur_18 = p + 2;
        self->remaining_1C = count - 2;
        return value;
    }
    u16 value;
    func_00137A60(self, 2, &value);
    return value;
}

u32 func_00137C40(Reader_137D10* self)
{
    s32 count = self->remaining_1C;
    if (count >= 4) {
        u8* p = self->cur_18;
        u32 value = p[0] + (p[1] << 8) + (p[2] << 16) + (p[3] << 24);
        self->cur_18 = p + 4;
        self->remaining_1C = count - 4;
        return value;
    }
    u32 value;
    func_00137A60(self, 4, &value);
    return value;
}

s32 func_00137CC0(Reader_137D10* self)
{
    s32 count = self->remaining_1C;
    if (count >= 1) {
        u8* p = self->cur_18;
        s32 value = (s8)p[0];
        self->cur_18 = p + 1;
        self->remaining_1C = count - 1;
        return value;
    }
    s8 value;
    func_00137A60(self, 1, &value);
    return value;
}

s32 func_00137D78(Reader_137D10* self)
{
    s32 count = self->remaining_1C;
    if (count >= 4) {
        u8* p = self->cur_18;
        s32 value = p[0] + (p[1] << 8) + (p[2] << 16) + ((s8)p[3] << 24);
        self->cur_18 = p + 4;
        self->remaining_1C = count - 4;
        return value;
    }
    s32 value;
    func_00137A60(self, 4, &value);
    return value;
}

struct Obj_136530 {
    u8 pad0[4];
    s32 handle;
    s8 flag;
    u8 pad1[0x268 - 9];
    f32 f268;
    u8 pad2[0x2F0 - 0x26C];
    f32 scale;
};

extern f32 D_0026185C;

void func_0015DB28(void* out, void* p, s32 handle);
s32 func_0015DF58(void* self);

s32 func_00136530(Obj_136530* self)
{
    u8 buf[0xB0];

    if (self->flag == 0) {
        return 1;
    }
    func_0015DB28(buf, &self->flag, self->handle);
    s32 n = func_0015DF58(buf);
    s32 v = (s32)((D_0026185C - self->f268) * self->scale);
    return v >= n;
}

void func_00137A60(void* self, s32 size, void* obj);

void func_00137F08(void* self, u8* p)
{
    u8* a = p + 0x10;
    u8* b = p + 0x20;
    u8* c = p + 0x30;

    func_00137A60(self, 12, p);
    func_00137A60(self, 12, a);
    func_00137A60(self, 12, b);
    func_00137A60(self, 12, c);
    *(s32*)(p + 0xC) = 0;
    *(s32*)(a + 0xC) = 0;
    *(s32*)(b + 0xC) = 0;
    *(f32*)(c + 0xC) = 1.0f;
}

extern u8 D_00261858[];

struct Scratch_00136408 {
    u8 bytes[0xB0];
};

struct Entry_00136408 {
    u8 pad0[4];
    s32 f04;
    u8 name08[0x258];
    s32 f260;
    u8 pad264[4];
    f32 f268;
    s32 f26C;
    s32 list270[16];
};

s32 func_001E2100(const char* s);
void func_001E2138(void* dst, const char* src);
void func_0015C8B8(s32 a, f32 x, f32 y);
void func_0015DB28(void* buf, void* p, s32 v);
void func_0015E068(void* buf, f32 x);
void func_0015C900(s32 v);
void func_0015DB80(void* buf);
s32 func_0015DBE0(void* buf);

void func_00136408(Entry_00136408* self, const char* name)
{
    Scratch_00136408 buf;
    s32 s1;
    s32 r;
    s32 idx;
    f32 scale;
    f32 lim;
    f32* tab;

    self->f26C = 0;
    if (name == 0) goto fail;
    if (func_001E2100(name) == 0) goto fail;
    func_001E2138(self->name08, name);
    s1 = 4;
    scale = 1.0f;
    if ((r = self->f260) == s1) scale = 0.8f;
    func_0015C8B8(self->f04, scale, scale);
    func_0015DB28(&buf, self->name08, self->f04);
    lim = 280.0f;
    if ((r = self->f260) == s1) lim = 380.0f;
    s1 = 0;
    func_0015E068(&buf, lim);
    func_0015C900(self->f04);
    func_0015DB80(&buf);
    while ((r = func_0015DBE0(&buf)) != 0) {
        if (r == 10) {
            idx = self->f26C;
            self->list270[idx] = s1;
            self->f26C = idx + 1;
        }
        s1++;
    }
    goto tail;
fail:
    self->name08[0] = 0;
tail:
    tab = (f32*)D_00261858;
    self->f268 = tab[1];
}

struct Chan_001373D0 {
    s32 a00;
    s32 mode;
    s32 a08;
    s32 a0C;
    s32 a10;
    s32 a14;
    s32 a18;
    s32 a1C;
    s32 a20;
    s32 a24;
    s32 a28;
    s32 a2C;
    s32 a30;
    s32 a34;
    s32 a38;
    s32 a3C;
    s32 a40;
};

s32 func_001F8DB8(s32 p, s32 a, s32 b);

void func_001F8C38(s32 p);
void func_00203E28(void);
void func_0011E2A0(void);

void func_001373D0(Chan_001373D0* self)
{
    s32 next = -1;
    switch (self->mode) {
    case 0:
        if (self->a34 >= 0) {
            func_001F8C38(self->a34);
        }
        break;
    case 1:
        if (self->a3C != 0) {
            if ((self->a00 & 2) != 0) {
                func_00203E28();
            } else {
                func_0011E2A0();
            }
        }
        break;
    default:
        break;
    }
    self->mode = next;
    self->a20 = 0;
    self->a18 = 0;
    self->a24 = 0;
    self->a1C = 0;
    self->a28 = 0;
    self->a2C = 0;
}
