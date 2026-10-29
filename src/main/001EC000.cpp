// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_1ED198 { u8 pad0[0x14]; void* f14; u8 pad1[0x28]; s32 f40; };

void func_00182C58(void);
s32 func_0015A838(void* a, s32 b, s32 c, s32 d);

void func_001ED198(Obj_1ED198* self)
{
    func_00182C58();
    self->f40 = func_0015A838(self->f14, 5, 0x13, 0);
}

struct Inner_1ED1D8 { u8 pad[0xC70]; s32 c70; };
struct Obj_1ED1D8 { u8 pad0[0x3C]; s32 f3C; Inner_1ED1D8* f40; s32 f44; };

void func_001837E0(void* self, s32 a, s32 b, s32 c);

void func_001ED1D8(Obj_1ED1D8* self)
{
    self->f3C = 0;
    self->f44 = self->f40->c70;
    func_001837E0(self, 0x1A, 0, 0);
}

struct Inner_1ED210 { u8 pad[0xC3C]; s32 c3C; };
struct Obj_1ED210 { u8 pad0[0x40]; Inner_1ED210* f40; };

void func_001837E0(void* self, s32 a, s32 b, s32 c);
void func_001ED318(Obj_1ED210* self, s32* p);

void func_001ED210(Obj_1ED210* self)
{
    s32 n;
    func_001837E0(self, 0x1C, 0, 0);
    n = 5;
    func_001ED318(self, &n);
    if (self->f40->c3C) {
        n = 3;
        func_001ED318(self, &n);
    }
}

struct Item_1ED558 { s32 kind; s32 p; f32 f8; s32 fC; };

Item_1ED558* func_001ED4C8(void* self, s32 kind, s32 p);

void func_001ED558(void* self, s32 p, s32 val)
{
    func_001ED4C8(self, 0, p)->fC = val;
}



void func_001ED588(void* self, s32 p, s32 val)
{
    func_001ED4C8(self, 1, p)->fC = val;
}


void func_001ED5B8(void* self, s32 p)
{
    func_001ED4C8(self, 2, p);
}


void func_001ED5D8(void* self, s32 p)
{
    func_001ED4C8(self, 3, p);
}


void func_001ED5F8(void* self, s32 p)
{
    func_001ED4C8(self, 4, p);
}


void func_001ED618(void* self, s32 p)
{
    func_001ED4C8(self, 5, p);
}

struct Out_1ED650 { f32 x; f32 y; f32 z; };
struct Pair_1ED650 { f32 a; f32 b; };

void func_001EAD88(f32* a, f32* b);

void func_001ED650(Out_1ED650* out, f32 unused, f32 scale, f32 z)
{
    Pair_1ED650 p;
    func_001EAD88(&p.a, &p.b);
    out->x = p.b * scale;
    out->y = p.a * scale;
    out->z = z;
}

void func_00192820(void);

void func_001EC0B8(void)
{
    func_00192820();
}

typedef void (*VFn_1ECDF8)(void* self);
struct Obj_1ECDF8 { VFn_1ECDF8* vtbl; };
struct Sub_1ECDF8 { u8 pad[0xC54]; void* sub; };
extern Obj_1ECDF8 D_0026E248;

void func_001B6598(void* sub, s32* out);
void* func_001E9970(void);

void func_001ECDF8(Sub_1ECDF8* self)
{
    s32 code;
    func_001B6598(self->sub, &code);
    void* obj = 0;
    if (code == 0x4F1 || (code < 0x4F2 ? code == 0x4EE : (code == 0x4F4 || code == 0x4F7))) {
        obj = func_001E9970();
    }
    if (obj) D_0026E248.vtbl[14](&D_0026E248);
    else D_0026E248.vtbl[15](&D_0026E248);
}

struct Entry_1ED090 { void* a; s32 b; };
struct Self_1ED090 { u8 pad[0xC68]; s32 count; Entry_1ED090* items; };
void func_0012F810(void* a, Self_1ED090* self);

void func_001ED090(Self_1ED090* self, void* a, s32 b)
{
    Entry_1ED090* e = &self->items[self->count++];
    e->b = b;
    e->a = a;
    func_0012F810(a, self);
}

void func_001EDEF0(void* self);

void func_001EE290(void* self)
{
    func_001EDEF0(self);
}

struct Buf_1EE468 { u8 pad[0xC]; u32* out; };

void func_001EE468(Buf_1EE468* b)
{
    u32* p = b->out;
    b->out = p + 1;
    *p = 0x13000000;
}

struct Stream_1EE5C8 { u8 pad[0xC]; u8* cursor; };
s32 func_001EE560(Stream_1EE5C8* s);

void func_001EE5C8(Stream_1EE5C8* s, void* unused1, s32 size, void* unused3, s32* outSize, u8** outCursor)
{
    if (size == 0) {
        if (outCursor) *outCursor = 0;
        if (outSize) *outSize = 0;
    } else {
        size = func_001EE560(s);
        if (outCursor) *outCursor = s->cursor;
        s->cursor += ((size + 3) / 4) * 4;
        if (outSize) *outSize = size;
    }
}

struct Owner_1EE900 { u8 pad[0x1EC4]; void* slot; };
struct Self_1EE900 { u8 pad[0x14]; Owner_1EE900* owner; };
void func_00182C18(Self_1EE900* self);

void func_001EE900(Self_1EE900* self)
{
    func_00182C18(self);
    self->owner->slot = self;
}

struct Obj_1EEE50 { u8 pad[0x538]; u64 flags; };
struct Node_1EEE50 { s32 unused0; Obj_1EEE50* obj; s32 unused2; Node_1EEE50* next; };

void func_001BA550(void* o, Node_1EEE50* node);
void func_001BA528(void* o, Node_1EEE50* node);
void func_001DBB90(void* owner, Node_1EEE50* list);

void func_001EEE50(void* owner, Node_1EEE50** head)
{
    Node_1EEE50** link = head;
    Node_1EEE50* node = *head;
    Node_1EEE50* removed = 0;
    while (node != 0) {
        Obj_1EEE50* o = node->obj;
        Node_1EEE50* next = node->next;
        if (((o->flags >> 59) & 1) != ((o->flags >> 60) & 1)) {
            if (o->flags & (1ULL << 59)) {
                func_001BA550(o, node);
            } else {
                func_001BA528(o, node);
            }
        }
        Obj_1EEE50* p = node->obj;
        if (p->flags & (1ULL << 60)) {
            link = &node->next;
        } else {
            *link = next;
            node->next = removed;
            removed = node;
        }
        Obj_1EEE50* q = node->obj;
        q->flags = q->flags & ~(1ULL << 60);
        q->flags = q->flags & ~(1ULL << 59);
        node = next;
    }
    func_001DBB90(owner, removed);
}

struct Obj_1EF830 { u8 pad[0x624]; s32 field624; };

void func_001EF830(Obj_1EF830* o)
{
    o->field624 = 0;
}

struct Obj_1EFCE8 { u8 pad[4]; s32 field4; };

void func_001F0220(void* o, s32 mode);

void func_001EFCE8(Obj_1EFCE8* o)
{
    o->field4 = -1;
    func_001F0220(o, 0);
}

struct Node_1EF520 { s32 pad0; void* obj; s32 pad2; Node_1EF520* next; };
struct Sub_1EF520 { u8 pad0[8]; s32 count; void** items; };
struct Self_1EF520 { u8 pad0[0x14]; void* f14; u8 pad1[0x38]; void* f50; u8 pad2[0x4FC]; Node_1EF520* head; Sub_1EF520 sub; };

void func_0015F9A0(void* a, Sub_1EF520* s);
void func_0015F8B0(void* a, Sub_1EF520* s);

void func_001EF520(Self_1EF520* self)
{
    if (self->f50 == self) {
        Sub_1EF520* s = &self->sub;
        func_0015F9A0(self->f14, s);
        s->items[0] = self;
        s->count = 1;
        Node_1EF520* node = self->head;
        if (node) {
            do {
                s->items[s->count++] = node->obj;
                node = node->next;
            } while (node);
        }
        func_0015F8B0(self->f14, s);
    }
}

void func_001F57E0(void* p);

s32 func_001EF808(void* self)
{
    func_001F57E0((u8*)self + 0x590);
    return 1;
}

void* func_001EF828(void* self)
{
    return (u8*)self + 0x590;
}

struct Obj_1EF838 { u8 pad0[0x2D0]; s32 f2D0; u8 pad1[0xC]; s32 f2E0; };

void func_00123ED0(void* self);

void func_001EF838(Obj_1EF838* self)
{
    func_00123ED0(self);
    self->f2D0 = -1;
    self->f2E0 = -1;
}

typedef void (*VFn_1EF868)(void* self);
struct Obj_1EF868 { VFn_1EF868* vtbl; };

extern u8 D_00275E10[];

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a, void* b);
void func_001EF900(void* self, s32 b);

void func_001EF868(Obj_1EF868* self)
{
    func_00124A48(self);
    func_00124DF8(self, 1, D_00275E10);
    func_001EF900(self, 0);
    self->vtbl[7](self);
}

void func_0013EC00(void* a, s32 b, void* c, s32 d, s32 e, s32 f, s32 g, s32 h);

void func_001EF8C0(void* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7)
{
    func_0013EC00((u8*)self + 0x2E8, 4, (u8*)self + 0x2E4, a1, a2, a3, a4, a7);
}

struct Cursor_1EE368 { u8 pad[0xC]; u32* cursor; };

void func_001EE368(Cursor_1EE368* s, s32 target)
{
    u32 raw = (u32)s->cursor;
    s32 idx = (s32)((raw & 0xC) >> 2);
    u32* p = (u32*)raw;
    if (idx == target) goto done;
    do {
        *p = 0;
        idx = (idx + 1) % 4;
        p++;
    } while (idx != target);
done:
    s->cursor = p;
}

struct Cursor_1EE3B8 { u8 pad[0xC]; u32* cursor; };

void func_001EE3B8(Cursor_1EE3B8* s, u32 a, u32 b)
{
    u32* p = s->cursor;
    s->cursor = p + 1;
    *p = a | 0x3000000;
    u32* q = s->cursor;
    s->cursor = q + 1;
    *q = b | 0x2000000;
}

struct Cursor_1EE3F0 { u8 pad[0xC]; u32* cursor; };

void func_001EE3F0(Cursor_1EE3F0* s, s32 n)
{
    u32* p = s->cursor;
    s->cursor = p + 1;
    *p = (u32)((n / 8) | 0x14000000);
}

struct Cursor_1EE420 { u8 pad[0xC]; u32* cursor; };

void func_001EE420(Cursor_1EE420* s, s32 n)
{
    u32* p = s->cursor;
    s->cursor = p + 1;
    *p = (u32)((n / 8) | 0x15000000);
}

extern s32 D_00275710;
void func_001EFB20(void* self);
void func_001DBCC8(s32 a, void* b, void* c, s32 d, s32 e);

struct Node_1EFC98 { u8 pad[0x28]; s32 flag; };

void func_001EFC98(Node_1EFC98* self)
{
    if (self->flag == 0) {
        self->flag = 1;
        func_001DBCC8(D_00275710, (void*)func_001EFB20, self, -1, 0);
    }
}

struct PktBuf_1EE450 { u8 pad[0xC]; u32* cur; };

void func_001EE450(PktBuf_1EE450* b)
{
    u32* p = b->cur;
    b->cur = p + 1;
    *p = 0x11000000;
}

struct PktBuf_1EE480 { u8 pad[0xC]; u32* cur; };

void func_001EE480(PktBuf_1EE480* b)
{
    u32* p = b->cur;
    b->cur = p + 1;
    *p = 0x10000000;
}

struct PktBuf_1EE498 { u8 pad[0xC]; u32* cur; };

void func_001EE498(PktBuf_1EE498* b, u32 x, u32 y)
{
    u32* p = b->cur;
    b->cur = p + 1;
    *p = y | (x << 8) | 0x01000000;
}

void func_00192850(void);

void func_001EC098(void)
{
    func_00192850();
}

s32 func_001EC188(void)
{
    return 1;
}

struct Packer_1EE528 {
    u8 pad0[0xC]; u32* cursor; u8 pad1[0xC]; s32 last;
    void push(u32 word)
    {
        u32* p = cursor;
        cursor = p + 1;
        *p = word;
    }
};

void func_001EE528(Packer_1EE528* self, s32 value)
{
    if (value != 0) {
        self->push(0x20000000);
        self->push((u32)value);
    }
    self->last = value;
}

struct Packer_1EE560 { u8 pad0[0xC]; u32* cursor; u8 pad1[0xC]; s32 last; };

extern s32 D_00275DD0[];

s32 func_001EE560(Packer_1EE560* self, s32 a, s32 b, s32 c)
{
    u32 lo = ((u32)b << 16) | 0x6000C000u;
    u32 head = ((u32)a << 24) | lo;
    u32* p = self->cursor;
    self->cursor = p + 1;
    u32 tag = head | (u32)c;
    *p = tag;
    if (self->last != 0) {
        *p = tag | 0x10000000;
    }
    return D_00275DD0[a] * b;
}

struct Obj_1ED018 { u8 pad0[0xC34]; s32 fC34; };

void func_001ED018(Obj_1ED018* self, s32 value)
{
    self->fC34 = value;
}

struct Obj_1ED020 { u8 pad0[0xC38]; void* fC38; };

void func_001ED210(void* p);

void func_001ED020(Obj_1ED020* self)
{
    func_001ED210(self->fC38);
    self->fC38 = 0;
}

struct Angles_1EDE38 { f32 unused; f32 first; f32 second; };
struct Vec3_1EDE38 { f32 x; f32 y; f32 z; };

void func_001EAD88(f32 angle, f32* a, f32* b);

void func_001EDE38(Angles_1EDE38* in, Vec3_1EDE38* b, Vec3_1EDE38* out)
{
    f32 t[4];
    func_001EAD88(in->first, &t[0], &t[1]);
    func_001EAD88(in->second, &t[2], &t[3]);
    out->x = t[1] * t[3] * b->x - t[2] * b->y;
    out->y = t[1] * t[2] * b->x + t[3] * b->y;
    out->z = -t[0] * b->x + b->z;
}

typedef u64 Quad_1EEB60 __attribute__((mode(TI)));
struct Obj_1EEB60 { u8 pad0[0x38]; void* node; };
s32 func_001EEA40(void* self, void* node, Quad_1EEB60 q, s32* out);

s32 func_001EEB60(Obj_1EEB60* self, Quad_1EEB60* vec, s32* out)
{
    s32 r;
    if (self != 0 && self->node != 0) {
        Quad_1EEB60 q = *vec;
        *out = 0;
        r = func_001EEA40(self, self->node, q, out);
    } else {
        r = 0x0FFFFFFF;
        *out = r;
    }
    return r;
}
