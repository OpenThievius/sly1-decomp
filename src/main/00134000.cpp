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
