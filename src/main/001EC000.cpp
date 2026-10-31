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

struct Obj_1ED050 { u8 pad0[0xC5C]; s32 count; u8 pad1[0x2C]; f32 ratio; };

void func_001ED050(Obj_1ED050* self, s32 v)
{
    self->count = v;
    self->ratio = 60.0f / (f32)v;
}

struct Obj_1ED070 { u8 pad0[0xC60]; s32 count; f32 scaled; u8 pad1[0x20]; f32 rate; };

void func_001ED070(Obj_1ED070* self, s32 v)
{
    self->count = v;
    self->scaled = self->rate * (f32)v;
}

typedef void (*VFn_1EF3A8)(void* self, void* arg);
struct Obj_1EF3A8 { VFn_1EF3A8* vtbl; };
struct Link_1EF3A8 { u8 pad0[4]; Obj_1EF3A8* target; };

void func_001EF3A8(void* self, Link_1EF3A8* link)
{
    Obj_1EF3A8* target = link->target;
    target->vtbl[0x128 / 4](target, self);
}

void func_001EF8F8(void) {}

struct Obj_001EFA60 { u32 pad; u32 count; s32 items[8]; };
void func_001EFA60(Obj_001EFA60* self, s32 value) { u32 i = self->count; if (i < 8) { self->items[i] = value; self->count = i + 1; } }

struct Obj_1EC380 { u8 pad[0x724]; s32 f724; };

void func_00125B70(void* obj, void* c, void* out);
void func_00125C90(void* obj, void* s, void* out);

void func_001EC380(void* self, void* s, void* c)
{
    u8 tmp[0x50];
    void* out = c;
    if (((Obj_1EC380*)self)->f724 == 16) {
        func_00125B70(self, c, tmp);
        *(s32*)(tmp + 0x44) = 0;
        out = tmp;
    }
    func_00125C90(self, s, out);
}

struct Obj_1ECE98 { u8 pad0[0x724]; s32 f724; u8 pad1[0xC48 - 0x728]; void* fC48; u8 pad2[0x140 - 0x4C]; };

void func_001C8418(void* self, void* p);
void func_001C8C08(void* self);
void func_001F3BD8(void* self, void* arg);

void func_001ECE98(Obj_1ECE98* self)
{
    s32 loc[4];
    s32 v = self->f724;
    if (v >= 14) goto tail;
    if (v < 12) goto tail;
    {
        void* q = self->fC48;
        if (q != 0) {
            func_001F3BD8(q, loc);
            func_001C8418(self, loc);
        } else {
            func_001C8418(self, (u8*)self + 0x140);
        }
    }
    return;
tail:
    func_001C8C08(self);
}

struct Obj_1ED168 { u8 pad[0x38]; void* f38; };

void func_00182C18(void* self);
void* func_0018D500(s32 size);

void func_001ED168(Obj_1ED168* self)
{
    func_00182C18(self);
    self->f38 = func_0018D500(0xC00);
}

struct Out_1ED6B0 { f32 x; f32 y; f32 z; };

void func_001EAD88(f32 angle, f32* a, f32* b);

void func_001ED6B0(Out_1ED6B0* out, f32 first, f32 second, f32 scale)
{
    f32 t[4];
    func_001EAD88(first, &t[0], &t[1]);
    func_001EAD88(second, &t[2], &t[3]);
    out->x = t[3] * t[1] * scale;
    out->y = t[3] * t[0] * scale;
    out->z = t[2] * scale;
}

struct Packer_1EE718 { u8 pad0[0x8]; s32 f8; u8 pad1[0x4]; u32* cursor; };

void func_001EE368(void* s, s32 target);
s32 func_001EE560(void* self, s32 a, s32 b, s32 c);
void func_00152B80(void* obj, s32 a, s32 b);

void func_001EE718(Packer_1EE718* self, s32 a, s32 b, s32 c, s32 d, s32* out)
{
    if (b != 0) {
        func_001EE368(self, 3);
        s32 r = func_001EE560(self, a, b, d);
        s32 t = r + 0xF;
        s32 u = r + 0x1E;
        s32 n = (t >= 0) ? t : u;
        func_00152B80(self, n >> 4, c);
        if (out != 0) {
            *out = self->f8 - 0xC;
        }
    }
}

struct Packer_1EE850 { u8 pad0[0xC]; u32* cursor; };

void func_001EE368(void* s, s32 target);
void func_00152B80(void* obj, s32 a, s32 b);

void func_001EE850(Packer_1EE850* self, s32 a, s32 b, s32 c)
{
    func_001EE368(self, 3);
    u32* p = self->cursor;
    u32 w = (u32)c << 31;
    self->cursor = p + 1;
    w = w | 0x50000000u;
    *p = (u32)a | w;
    func_00152B80(self, a, b);
}

void func_00138398(void* src, s32* count, void** out);
s32 func_00137BE0(void* src);
s32 func_00137C40(void* src);
void* func_0018D500(s32 size);
void func_0011EC40(void* a, void* b);

struct Obj_1EE930 {
    u8 pad0[0x34];
    s32 f34;
    void* f38;
    s32 f3C;
    s32* f40;
};

void func_001EE930(Obj_1EE930* self, void* src)
{
    s32 i;
    s32 n;

    func_00138398(src, &self->f34, &self->f38);
    n = func_00137BE0(src);
    self->f3C = n;
    self->f40 = (s32*)func_0018D500(n * 4);
    for (i = 0; i < self->f3C; i++) {
        self->f40[i] = func_00137C40(src);
    }
    func_0011EC40(self, src);
}

struct Node_1EF3D8 { s32 f0; struct Obj_1EF3D8* obj; s32 f8; Node_1EF3D8* next; };
struct Self_1EF3D8 { u8 pad0[0x14]; void* f14; u8 pad1[0x538]; Node_1EF3D8* f550; };
typedef void (*VFn_1EF3D8)(void* self, s32 kind, void* msg);
struct Obj_1EF3D8 { VFn_1EF3D8* vtbl; };
struct Msg_1EF3D8 { Self_1EF3D8* self; Obj_1EF3D8* obj; };

void func_001BA550(void* o, Node_1EF3D8* node);
void func_001DBB90(void* owner, Node_1EF3D8* list);
void func_001EF520(Self_1EF3D8* self);
void func_00127378(void* self, s32 kind, void* msg);

void func_001EF3D8(Self_1EF3D8* self, s32 kind, void* msg)
{
    s32 flag = 0;
    if (kind == 2) {
        if (msg == (void*)self) {
            Node_1EF3D8* n = self->f550;
            if (n != 0) {
                do {
                    func_001BA550(n->obj, n);
                    n = n->next;
                } while (n != 0);
            }
            flag = 1;
            func_001DBB90(self->f14, self->f550);
            self->f550 = 0;
        } else {
            Node_1EF3D8** link = &self->f550;
            Node_1EF3D8* n = *link;
            if (n != 0) {
                if (n->obj == (Obj_1EF3D8*)msg) {
                    *link = n->next;
                } else {
                    for (;;) {
                        link = &(*link)->next;
                        n = *link;
                        if (n == 0) {
                            break;
                        }
                        if (n->obj == (Obj_1EF3D8*)msg) {
                            *link = n->next;
                            break;
                        }
                    }
                }
            }
            Msg_1EF3D8 m;
            m.self = self;
            m.obj = n->obj;
            if (n != 0) {
                n->next = 0;
                flag = 1;
                func_001BA550(n->obj, n);
                func_001DBB90(self->f14, n);
            }
            m.obj->vtbl[18](m.obj, 11, &m);
        }
    }
    if (flag != 0) {
        func_001EF520(self);
    }
    func_00127378(self, kind, msg);
}

struct Obj_1EF9C8 { u8 pad0[0x2DC]; s32 f2DC; };
struct Msg_1EF9C8 { s32 f0; s32 f4; s32 f8; };

void func_00127378(void* self, s32 kind, void* msg);
void func_001EF900(void* self, s32 b);

void func_001EF9C8(Obj_1EF9C8* self, s32 kind, Msg_1EF9C8* msg)
{
    func_00127378(self, kind, msg);
    if (kind == 5) {
        if (msg->f8 == self->f2DC) {
            func_001EF900(self, 0);
        }
    }
}

struct Buf_1EE4C0 { u8 pad[0xC]; u32* cur; };
void func_001EE4C0(Buf_1EE4C0* b, u32* src){
 u32 *p1,*p2,*p3,*p4,*p5;
 p1=b->cur; b->cur=p1+1; *p1=0x30000000;
 p2=b->cur; b->cur=p2+1; *p2=src[0];
 p3=b->cur; b->cur=p3+1; *p3=src[1];
 p4=b->cur; b->cur=p4+1; *p4=src[2];
 p5=b->cur; b->cur=p5+1; *p5=src[3];
}

// NEAR: the calls and the single-field stores match; the order of the four stores to 0x360 to 0x588 differs (retail: 0x588, the 64-bit flags at 0x538, 0x360, 0x584, 0x364)
void func_001B7968(void* self);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);
void func_001F5590(void* a, void* b);

struct Obj_1EEC60 {
    u8 pad0[0x360];
    f32 f360;
    f32 f364;
    u8 pad1[0x584 - 0x368];
    s32 f584;
    s32 f588;
    u8 pad2[0x590 - 0x58C];
    u8 f590[4];
    s32 f594;
};

void func_001EEC60(Obj_1EEC60* self)
{
    u64 bits;
    s32 one;

    func_001B7968(self);
    bits = *(u64*)((u8*)self + 0x538);
    one = 0x8000;
    bits |= (u64)one << 28;
    *(u64*)((u8*)self + 0x538) = bits;
    self->f584 = 1;
    self->f588 = 1;
    self->f364 = 1.0f;
    self->f360 = 1.0f;
    func_001B9AE0(self, 3, 0, 3, 0);
    func_001F5590((u8*)self + 0x590, self);
    self->f594 = 3;
}

struct Obj_1EFD10 {
    u8 pad0[4];
    s32 state;
    f32 f08;
    f32 f0C;
    s32 i10;
    u8 pad14[0xC];
    s32 i20;
    s32 i24;
};

extern f32 D_00261858[];
extern s32 D_00275AF0;

s32 func_001F00F0(Obj_1EFD10* self, s32 a1, s32 a2);
void func_001F0220(Obj_1EFD10* self, s32 state);
void func_001C0000(s32 flag, f32 x);

void func_001EFD10(Obj_1EFD10* self, s32 a1)
{
    s32 s = self->state;
    f32 t = D_00261858[4] - self->f08;
    f32 thr;
    f32 r;
    switch (s) {
    case 0:
        if (func_001F00F0(self, a1, 1) != 0) return;
        break;
    case 1:
        if (self->i24 != 2) {
            thr = 0.5f;
            if (self->i24 == s) thr = 1.5f;
            if (thr < t) {
                s = 2;
                func_001C0000(((self->i20 >> 3) ^ 1) & 1, 0.0f);
            } else {
                r = t / thr;
                f32 hi = 1.0f;
                f32 lo = 0.0f;
                if (r < lo) r = lo;
                else if (hi < r) r = hi;
                self->f0C = r;
                func_001C0000(((self->i20 >> 3) ^ 1) & 1, 1.0f - r);
            }
        }
        break;
    case 3: {
        s32 v = self->i24;
        if (v != 2) {
            thr = 0.25f;
            if (v == 1) thr = 1.0f;
            if (thr < t) {
                if (v == s) {
                    self->i24 = 0;
                    self->f08 = D_00261858[4];
                    self->f0C = 1.0f;
                } else {
                    s = 0;
                }
            } else {
                self->f0C = 1.0f - t / thr;
            }
        }
        break;
    }
    case 2:
        if (self->i10 == 0 && D_00275AF0 != 0) {
        } else {
            s = 3;
        }
        break;
    }
    func_001F0220(self, s);
}

struct Sub_1ECBC8;
struct Dev_1ECBC8;
typedef void (*Cb_1ECBC8)(void);
typedef s32 Id_1ECBC8;

struct Obj_1ECBC8 {
    u8 p0[0x14];
    Dev_1ECBC8* f14;
    u8 p1[0xC34 - 0x18];
    Sub_1ECBC8* fC34;
    Sub_1ECBC8* fC38;
    u8 p2[0xC54 - 0xC3C];
    Dev_1ECBC8* fC54;
    u8 p3[0xC60 - 0xC58];
    s32 fC60;
    f32 fC64;
    u8 p4[0xC70 - 0xC68];
    s32 fC70;
    s32 fC74;
    s32 fC78;
    f32 fC7C;
    f32 fC80;
    f32 fC84;
    f32 fC88;
    f32 fC8C;
    u8 p5[0xC94 - 0xC90];
    s32 fC94;
};

extern f32 D_00261858[];
extern s32 D_00275DB8;
extern s32 D_00275DBC;

void func_001C7CB8(Obj_1ECBC8* self);
void func_001ED1D8(Sub_1ECBC8* sub);
void func_001ED278(Sub_1ECBC8* sub);
void func_001B6598(Dev_1ECBC8* dev, s32* out);
void func_001C0C68(Id_1ECBC8 a, Dev_1ECBC8* b);
s32 func_001C0C50(Id_1ECBC8 a);
void func_001DBCC8(Dev_1ECBC8* dev, Cb_1ECBC8 cb, Obj_1ECBC8* self, s32 a3, s32 a4);
void func_001ECB18(void);

void func_001ECBC8(Obj_1ECBC8* self)
{
    Sub_1ECBC8* sub;
    s32 code;

    func_001C7CB8(self);
    if (D_00275DB8 == 2) {
        if (self->fC88 != self->fC8C) {
            self->fC88 = self->fC8C;
            self->fC64 = self->fC8C * (f32)self->fC60;
        }
        sub = self->fC34;
        self->fC84 = D_00261858[1] + self->fC88;
        self->fC80 = D_00261858[1];
        self->fC70 = 0;
        self->fC78 = 0;
        self->fC74 = 0;
        if (sub != 0) {
            self->fC34 = 0;
            self->fC38 = sub;
            func_001ED1D8(sub);
        }
        D_00275DB8 = 0;
    }
    if (self->fC84 <= D_00261858[1]) {
        s32 a = self->fC74 + 1;
        s32 b = self->fC78 + 1;
        self->fC80 = self->fC84;
        self->fC74 = a;
        self->fC78 = b;
        if (b >= 4) {
            self->fC78 = 0;
            self->fC70 = self->fC70 + 1;
            if (self->fC88 != self->fC8C) {
                self->fC88 = self->fC8C;
                self->fC64 = self->fC8C * (f32)self->fC60;
            }
        }
        if (self->fC94 == 1) {
            func_001B6598(self->fC54, &code);
            if (code == 0x4F1 || (code < 0x4F2 ? code == 0x4EE : (code == 0x4F4 || code == 0x4F7))) self->fC94 = 2;
        }
        self->fC84 = self->fC84 + self->fC88;
    }
    self->fC7C = (f32)self->fC78 + (D_00261858[1] - self->fC80) / self->fC88;
    if (self->fC38 != 0) func_001ED278(self->fC38);
    if (D_00275DB8 == 1) {
        func_001C0C68(1, 0);
        if (func_001C0C50(1) == D_00275DBC) D_00275DB8 = 2;
    }
    func_001DBCC8(self->f14, func_001ECB18, self, 0, 0);
}

void func_001C9008(void* self, void* arg);
void func_001B6598(void* sub, s32* out);
void func_001B64D8(void* p, s32 n);

void func_001EC478(u8* self, void* arg)
{
    s32 out;
    s32 sel;
    func_001C9008(self, arg);
    s32 st = *(s32*)(self + 0x724);
    if (st != 0xE) {
        if (st != 0x10) {
            return;
        }
        *(s32*)(self + 0xC94) = 0;
        func_001B6598(*(void**)(self + 0xC54), &out);
        switch (out) {
        case 0x4EE:
            sel = 0x4EF;
            break;
        case 0x4F1:
            sel = 0x4F2;
            break;
        case 0x4F4:
            sel = 0x4F5;
            break;
        }
        func_001B64D8(*(void**)(self + 0xC54), sel);
    } else {
        *(s32*)(self + 0xC94) = 0;
    }
}

struct Cursor_1EE7D0 { u8 pad[0xC]; u32* cursor; };

void func_001EE368(void* s, s32 target);
void func_00152CE0(void* self, s32 index, s32 count);

void func_001EE7D0(Cursor_1EE7D0* self, s32 n, void* buf, s32 flag)
{
    func_001EE368(self, 3);
    u32* p = self->cursor;
    u32 w = (u32)flag << 31;
    self->cursor = p + 1;
    w = w | 0x50000000u;
    *p = (u32)n | w;
    func_00152CE0(self, n, (s32)buf);
}

struct Obj_1EFA30 { void* vtbl; };

extern u8 D_002505C0[];
void* func_0018D5C0(u32 n);

void* func_001EFA30(void)
{
    Obj_1EFA30* p = (Obj_1EFA30*)func_0018D5C0(48);
    p->vtbl = D_002505C0;
    return p;
}

void func_001EE5C8(void* s, void* a1, s32 size, void* a3, s32* outSize, u8** outCursor);

void func_001EE668(void* s, void* a1, s32 size, u32* src, void* a4)
{
    s32 outSize;
    u8* outCursor;
    s32 n;
    s32 rem;
    s32 full;
    s32 i;
    u32* dst;

    func_001EE5C8(s, a1, size, a4, &outSize, &outCursor);
    dst = (u32*)outCursor;
    n = (outSize + 3) >> 2;
    rem = n & 3;
    full = n - rem;
    if (rem != 0) {
        i = rem;
        do {
            *dst++ = *src++;
        } while (--i != 0);
    }
    i = 0;
    if (full > 0) {
        do {
            u32 w0 = src[0];
            u32 w1 = src[1];
            u32 w2 = src[2];
            u32 w3 = src[3];
            i += 4;
            dst[0] = w0;
            dst[1] = w1;
            dst[2] = w2;
            dst[3] = w3;
            src += 4;
            dst += 4;
        } while (i < full);
    }
}

struct Mask_1EE9D0 { u8 pad[0x3C]; s32 count; s32* table; };

s32 func_001EE9D0(Mask_1EE9D0* self, s32 bits)
{
    s32 acc;
    bits &= 0x7FFFFFFF;
    if (bits == 0) return 0;
    acc = -1;
    for (s32 i = 0; i < self->count; i++) {
        if ((bits >> i) & 1) acc &= self->table[i];
    }
    return acc | bits;
}

extern s32 D_00275710;
extern s32 D_00275F84;
extern s32 D_002640A4;
extern u8 D_00262280[];
void func_00180398(s32 a, f32 v);
void func_0019DDA0(s32 a, s32 b, s32 c, s32 d, void* e, f32 f, f32 g, f32 h, f32 i);

struct Emitter_1EFEE0 { u8 pad[0xC]; f32 scale; u8 pad2[0x14]; s32 mode; };

void func_001EFEE0(Emitter_1EFEE0* self)
{
    if (D_00275710 != 0 && D_00275F84 != 0) {
        s32 mode = self->mode;
        if (mode != 1) {
            if (mode < 2) {
                if (mode == 0) goto draw;
            }
            return;
        }
        if (D_002640A4 != 0) {
        func_00180398(D_002640A4, self->scale);
            return;
        }
        draw:
    f32 v = self->scale * 255.0f;
    func_0019DDA0(0, 0, 0, (s32)v, D_00262280, 0.0f, 0.0f, 640.0f, 492.80002f);
    }
}

extern f32 D_00261858[];
void func_001EF900(void* item, s32 mode);

struct Item_1EFB20 { u8 pad[0x2D0]; s32 kind; f32 lo; f32 hi; s32 sub; s32 tag; };
struct Owner_1EFB20 { u8 pad[0x180]; s32 link; };
struct Set_1EFB20 { s32 pad0; s32 count; Item_1EFB20* items[8]; s32 flag; Owner_1EFB20* owner; };

void func_001EFB20(Set_1EFB20* s)
{
    s->flag = 0;
    if (s->owner != 0 && s->owner->link != -1 && s->items[0]->tag == s->owner->link) {
        s32 i;
        for (i = 0; i < s->count; i++) {
            if (s->items[i]->kind != 1) break;
        }
        if (i >= s->count) {
            for (i = 0; i < s->count; i++) {
                func_001EF900(s->items[i], 2);
            }
            s->owner->link = -1;
        }
        return;
    }
    for (s32 i = 0; i < s->count; i++) {
        Item_1EFB20* it = s->items[i];
        if (it->kind != 2) continue;
        if (it->sub != 0) continue;
        f32 d = D_00261858[1] - it->lo;
        if (it->hi < d) {
            func_001EF900(it, 0);
        }
    }
}

struct Self_1EC528 { u8 pad0[0xA68]; s32 fA68; };
struct Glob_1EC528 { u8 pad0[0x274]; f32 f274; f32 f278; };

void func_001AC060(void* p);


void func_001EC528(Self_1EC528* self)
{
    Glob_1EC528* g = (Glob_1EC528*)&D_0026E248;
    func_001AC060((u8*)&D_0026E248);
    self->fA68 = 2;
    g->f274 = g->f278;
}

struct Obj_1EE8D0 {
    u8 pad_00[0x4];
    u32 f4;
    u32 f8;
    u32 fC;
};

void func_001EE7D0(Obj_1EE8D0* self, s32 n, void* buf, s32 flag);

void func_001EE8D0(Obj_1EE8D0* a0, Obj_1EE8D0* a1) {
    u32 span = a1->fC - a1->f4;
    func_001EE7D0(a0, span >> 4, (void*)a1->f4, 0);
}

// EXACT: callee declared s32 and called as (void)

struct Self_1EE318 { u8 pad0[0x10]; s32 f10; u8 pad1[0x18 - 0x14]; u8* f18; s32 f1C; s32 f20; };

extern u8 D_0024A0E0[];
s32 func_00152888(Self_1EE318* self);

Self_1EE318* func_001EE318(Self_1EE318* self)
{
    (void)func_00152888(self);
    self->f10 = 1;
    self->f18 = D_0024A0E0;
    self->f1C = 0;
    self->f20 = 0;
    return self;
}

struct Obj_1EECE0;
struct Link_1EECE0;
extern Link_1EECE0* D_0027B314;
struct Link_1EECE0 {
    s32* a; s32* b; s32 c; Link_1EECE0* prev;
    Link_1EECE0(s32* p) : a(p), b(p), c(p[2]), prev(D_0027B314) {}
    ~Link_1EECE0() { D_0027B314 = prev; }
};
struct Obj_1EECE0 { void (**vtbl)(Obj_1EECE0*); };

void func_00124A48(Obj_1EECE0* self);
void func_001F55A8(void* self);
void* func_0018D500(s32 size);

extern Link_1EECE0* D_0027B314;

void func_001EECE0(Obj_1EECE0* self)
{
    Link_1EECE0 fr((s32*)((u8*)self + 0x34));
    D_0027B314 = &fr;
    func_00124A48(self);
    func_001F55A8((u8*)self + 0x590);
    *(void**)((u8*)self + 0x560) = func_0018D500(0x80);
    if (*(s32*)((u8*)self + 0x278) != 0) {
        self->vtbl[0x36](self);
    }
}

struct Obj_1EF900;
struct Mgr_1EF900;
typedef void (*VFn_1EF900)(Obj_1EF900* self, s32 id, void* evt);

struct Obj_1EF900 {
    VFn_1EF900* vtbl;
    u8 pad0[0x2CC];
    s32 state;
    f32 timer;
    u8 pad1[0xC];
    s32 f2E4;
    u8 f2E8[1];
};

struct Evt_1EF900 {
    void* self;
    s32 old;
    s32 cur;
};

extern f32 D_0026185C[];

void func_0013ECB0(Mgr_1EF900* mgr, s32 a, void* b, Obj_1EF900* self, s32 c);

void func_001EF900(Obj_1EF900* self, s32 state)
{
    if (self->state != state) {
        if (state != 0) {
            if (state == 2)
                func_0013ECB0((Mgr_1EF900*)D_00275710, self->f2E4, self->f2E8, self, 1);
        } else {
            if (self->state == 2)
                func_0013ECB0((Mgr_1EF900*)D_00275710, self->f2E4, self->f2E8, self, 0);
        }
        Evt_1EF900 evt;
        evt.old = self->state;
        evt.self = self;
        evt.cur = state;
        self->state = state;
        self->timer = D_0026185C[0];
        self->vtbl[18](self, 0x16, &evt);
    }
}

struct Obj_1EC0D8 {
    u8 pad0[0xC20];
    s32 fC20;
    u8 pad1[0x30];
    s32 fC54;
    u8 pad2[0x3C];
    s32 fC94;
};
void func_001B6598(s32 sub, s32* out);

s32 func_001EC0D8(Obj_1EC0D8* self)
{
    s32 r[4];
    func_001B6598(self->fC54, r);
    switch (r[0]) {
    case 0x4ED:
    case 0x4F0:
    case 0x4F3:
    case 0x4F6:
        if (self->fC20 == 0) goto zero;
    yes:
        return 1;
    case 0x4EE:
    case 0x4F1:
    case 0x4F4:
    case 0x4F7:
        if (self->fC94 == 1) goto zero;
        if (self->fC94 < 2) {
            if (self->fC94 == 0) goto set;
            return 0;
        }
        if (self->fC94 == 2) goto yes;
        return 0;
    set:
        self->fC94 = 1;
    }
zero:
    return 0;
}

struct Chain_1ED318 {
    u8 pad[0x680];
    s32 f680;
    s32 pad2;
    s32 f688;
};
struct Owner_1ED318 {
    u8 pad[0x40];
    u8 pad40[0x4];
};
struct Inner_1ED318 {
    u8 pad[0xC3C];
    Chain_1ED318* fC3C;
    u8 pad2[0xC4C - 0xC40];
    s32 fC4C;
};
struct Self_1ED318 {
    u8 pad[0x40];
    Inner_1ED318* f40;
};
struct Msg_1ED318 {
    s32 kind;
    s32 pad[2];
    s32 f0C;
};
struct Obj_1ED318 {
    void** vt;
};

extern Obj_1ED318 D_00273C50;
extern Obj_1ED318 D_002739F0;
extern u8 D_00262C70[];

void func_001EC7A8(Inner_1ED318* p);
void func_001837E0(Self_1ED318* self, s32 a, s32 b, s32* c);
void func_0016EC88(void* p);
void func_001BFCD8(s32 a0, Self_1ED318* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

typedef void (*VFn_1ED318)(Obj_1ED318*, s32);

void func_001ED318(Self_1ED318* self, Msg_1ED318* msg)
{
    switch (msg->kind) {
    case 0:
        func_001EC7A8(self->f40);
        break;
    case 1: {
        s32* loc = &msg->f0C;
        func_001837E0(self, 0x1B, 1, (s32*)&loc);
        break;
    }
    case 2:
        self->f40->fC3C->f680 = 1;
        ((VFn_1ED318)D_00273C50.vt[16])(&D_00273C50, 2);
        func_0016EC88(D_00262C70);
        func_001BFCD8(0, 0, 0, 0, 80000.0f, 70000.0f, 1.5f, 0.5f, 0.0f, 0, 0);
        break;
    case 3:
        self->f40->fC3C->f680 = 0;
        self->f40->fC3C->f688 = 0;
        ((VFn_1ED318)D_00273C50.vt[16])(&D_00273C50, 0);
        break;
    case 4:
        self->f40->fC4C = 1;
        ((VFn_1ED318)D_002739F0.vt[16])(&D_002739F0, 2);
        func_001BFCD8(0, 0, 0, 0, 80000.0f, 70000.0f, 1.5f, -0.25f, 0.0f, 0, 0);
        break;
    case 5:
        self->f40->fC4C = 0;
        ((VFn_1ED318)D_002739F0.vt[16])(&D_002739F0, 0);
        break;
    }
}

// NEAR: only the order of `lw s0,56(a0)` (items) and `sll v0,v1,4` (count*16) differs; retail loads items first, GCC schedules the shift first

struct Pool_1ED4C8 { u8 pad000[0x34]; s32 count; u8* items; };
struct Entry_1ED4C8 { s32 f00; s32 f04; f32 f08; s32 pad0C; };
extern u8 D_00625760[];
s32 func_001F5C0C(Entry_1ED4C8* dst, s32 value, s32 size);

void* func_001ED4C8(Pool_1ED4C8* self, s32 a, s32 b, f32 c)
{
    if (self->count >= 0xC0) return D_00625760;
    Entry_1ED4C8* e = (Entry_1ED4C8*)(self->items + self->count * 16);
    self->count = self->count + 1;
    (void)func_001F5C0C(e, 0, 16);
    e->f00 = a;
    e->f04 = b;
    e->f08 = c;
    return e;
}
