// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

extern void* D_0024A220;
struct Render_15C930 { u8 pad[0x44]; f32 x; f32 y; void* callback; };
void* func_0018D758(u32);
void func_0015C9B0(void*, Render_15C930*);
Render_15C930* func_0015C930(void* owner, f32 x, f32 y)
{
	Render_15C930* out = (Render_15C930*)func_0018D758(0x88);
	out->callback = &D_0024A220;
	func_0015C9B0(owner, out);
	out->x *= x;
	out->y *= y;
	return out;
}

struct Point2 { f32 x, y; };

// Points recorded in order, the first of them scaled into u and v.
struct Trail
{
    u8 pad[0xC];
    s32 count;
    Point2 points[6];
    f32 spare;
    f32 u, v;
};

void func_0015C8B8(Trail* trail, f32 su, f32 sv)
{
    Point2* point = &trail->points[trail->count++];
    point->x = trail->u;
    point->y = trail->u;
    trail->u = trail->points[0].x * su;
    trail->v = trail->points[0].y * sv;
}

extern s32 D_00262268[];
extern s32 D_0026227C;

s32 func_0015C1C0(s32 a)
{
    if (a == -1) {
        return 0;
    }
    s32 v = D_00262268[a];
    if (v != 0) {
        return v;
    }
    return D_0026227C;
}

s32 func_0015DAB8(void* a, s32 b);

s32 func_0015CA38(void* a, s32 b)
{
    return func_0015DAB8(a, (s8)b) != 0;
}

void func_0015DB80(void* self);
s32 func_0015DBE0(void* self);

s32 func_0015DF58(void* self)
{
    s32 n = 0;
    func_0015DB80(self);
    while (func_0015DBE0(self) != 0) {
        n++;
    }
    return n;
}

struct Frame_15EB20 {
    u8 scratch[0x80];
    u8 obj[0x30];
};

extern u8 D_00212160[];
extern u8 D_00215C50[];

void func_001611B8(void* p);
void func_001529C8(void* p, s32 n, void* q);
void func_001613C0(void* p, s32 a, s32 b, s32 c);
void func_00161708(void* p, s32 a, s32 b);
void func_00161200(void* p);
void func_001EE450(void* self);
void func_001EE8D0(void* self, void* p);
void func_0015EAE0(void* self, void* a, void* b);
void func_00152D30(void* self);
void func_001529E0(void* self, void* p, s32 n);

void func_0015EB20(void* self, void* p, s32 n)
{
    Frame_15EB20 fr;
    void* buf = fr.obj;
    func_001611B8(buf);
    func_001529C8(buf, 8, fr.scratch);
    func_001613C0(buf, 0, 1, 0xE);
    func_00161708(buf, 0x61, 0);
    func_00161200(buf);
    func_001EE450(self);
    func_001EE8D0(self, buf);
    func_0015EAE0(self, D_00212160, D_00215C50);
    func_00152D30(self);
    func_001529E0(self, p, n);
}

struct Owner_15F678
{
    u8 pad[0x1ED0];
    s32 count;
    void** items;
};

void func_0015F678(Owner_15F678* owner, u8* obj)
{
    u64 flags = *(u64*)(obj + 0x2C8);
    u64 bit = (u64)0x8000 << 24;
    if (!(flags & bit))
    {
        *(u64*)(obj + 0x2C8) = flags | bit;
        s32 n = owner->count;
        owner->items[n] = obj;
        owner->count = n + 1;
    }
}

void func_0015FA58(void* self);
void func_0015FD78(void* self);

void func_0015FF58(void* self)
{
    func_0015FA58(self);
    func_0015FD78(self);
}

struct Rec_15C9B0 {
    u8 pad0[0x50];
    s32 f50;
    s32 f54;
    s32 f58;
    u8 pad5C[4];
    s64 f60;
    s32 f68;
    s32 f6C;
    s32 f70;
    s32 f74;
    s32 f78;
    s32 f7C;
    s32 f80;
};

void func_0015C260(void* self, void* dst);

void func_0015C9B0(Rec_15C9B0* self, Rec_15C9B0* dst)
{
    func_0015C260(self, dst);
    dst->f50 = self->f50;
    dst->f54 = self->f54;
    dst->f58 = self->f58;
    dst->f60 = self->f60;
    dst->f68 = self->f68;
    dst->f6C = self->f6C;
    dst->f70 = self->f70;
    dst->f74 = self->f74;
    dst->f78 = self->f78;
    dst->f7C = self->f7C;
    dst->f80 = self->f80;
}

struct Entry_15CA60 {
    u16 key;
    u8 pad2[4];
    u16 value;
};

struct Owner_15CA60 {
    u8 pad0[4];
    s32 a4;
    u8 pad8[0x3C];
    f32 a44;
};

Entry_15CA60* func_0015DAB8(void* table, s8 key);

f32 func_0015CA60(Owner_15CA60* self, s8 key)
{
    Entry_15CA60* e = func_0015DAB8(self, key);
    f32 x;
    f32 y;
    if (e == 0) {
        x = self->a44;
        y = (f32)self->a4;
    } else {
        x = (f32)(e->value + 1);
        y = self->a44;
    }
    return x * y;
}

struct __attribute__((packed)) Lo8_0015EC68 { u64 v; };
struct Rec12_0015EC68 { Lo8_0015EC68 lo; s32 hi; };

struct Slot_262320 {
    u8 pad00[0x18];
    u32 flags;
    u32 pad1C;
    Rec12_0015EC68 r20;
    Rec12_0015EC68 r2C;
    Rec12_0015EC68 r38;
    s32 f44;
};

struct PairA_15CAB8 {
    u8 pad0[0x10];
    s32 f10;
    s32 f14;
};

struct PairB_15CAB8 {
    u8 pad0[8];
    s32 f8;
    s32 fC;
};

struct Obj_15CAB8 {
    u8 pad0[0x54];
    PairA_15CAB8* pa;
    PairB_15CAB8* pb;
    u8 pad5C[0xC];
    s32 f68;
    s32 f6C;
    s32 f70;
    s32 f74;
    u8 pad78[8];
    u32 mask;
};

extern Slot_262320* D_002622D8;

void func_00152D70(void* obj);
void func_00152B80(void* obj, s32 a, s32 b);
void func_00152B38(void* obj);

s32 func_0015CAB8(Obj_15CAB8* self, void* obj)
{
    s32 r = (D_002622D8->flags & self->mask) == 0;
    if (r != 0) {
        func_00152D70(obj);
        func_00152B80(obj, self->f68, self->f6C);
        func_00152B80(obj, self->pa->f14, self->pa->f10);
        if (self->pb != 0) {
            func_00152B80(obj, self->f70, self->f74);
            func_00152B80(obj, self->pb->fC, self->pb->f8);
        }
        func_00152B38(obj);
        D_002622D8->flags |= self->mask;
    }
    return r;
}

struct Flags_15CB88 {
    u8 pad0[0x18];
    u32 flags;
};

struct PairA_15CB88 {
    u8 pad0[0x10];
    s32 f10;
    s32 f14;
};

struct PairB_15CB88 {
    u8 pad0[8];
    s32 f8;
    s32 fC;
};

struct Obj_15CB88 {
    u8 pad0[0x30];
    s32 f30;
    u8 pad34[4];
    s64 f38;
    u8 pad40[0x20];
    s64 f60;
    u8 pad68[0x18];
    u32 mask;
};

void func_0015C2E8(void* a0, s32 a1, void* a2);
s32 func_0015CAB8(Obj_15CB88* self, void* obj);
void func_001613C0(void* obj, s32 a, s32 b, s32 c);
void func_00161708(void* obj, s32 tag, s64 value);
void func_00161768(void* obj, s32 tag, s64 value);

void func_0015CB88(Obj_15CB88* self, s32 a1, void* obj)
{
    func_0015C2E8(self, a1, obj);
    s32 ok = func_0015CAB8(self, obj);
    func_001613C0(obj, 6, 1, 0xE);
    if (ok != 0) {
        func_00161708(obj, 0x3F, 0);
    }
    s64 v = 0x31001;
    if (self->f30 != 0) {
        v = self->f38;
    }
    func_00161708(obj, 0x47, v);
    func_00161708(obj, 0x42, 0x44);
    func_00161708(obj, 6, self->f60);
    func_00161708(obj, 0x14, 0x60);
    func_00161708(obj, 8, 5);
    func_00161708(obj, 0, 0x1D6);
    func_00161768(obj, 5, 0x43431);
}

struct Flags_15CC80 {
    u8 pad0[0x18];
    u32 flags;
};

struct PairA_15CC80 {
    u8 pad0[0x10];
    s32 f10;
    s32 f14;
};

struct PairB_15CC80 {
    u8 pad0[8];
    s32 f8;
    s32 fC;
};

struct Obj_15CC80 {
    u8 pad0[0x54];
    PairA_15CC80* pa;
    PairB_15CC80* pb;
    u8 pad5C[4];
    s64 f60;
    u8 pad68[0x18];
    u32 mask;
};

s32 func_0015CAB8(Obj_15CC80* self, void* obj);

void func_0015CC80(Obj_15CC80* self, void* obj)
{
    s32 ok = func_0015CAB8(self, obj);
    func_001613C0(obj, 6, 1, 0xE);
    if (ok != 0) {
        func_00161708(obj, 0x3F, 0);
    }
    func_00161708(obj, 6, self->f60);
    func_00161708(obj, 0, 0x1D6);
    func_00161768(obj, 5, 0x43431);
}

extern s32 D_0026227C;

void func_0015C178(void)
{
    D_0026227C = 0;
}

struct Record_0015C260 {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 count0C;
    u8 body10[0x20];
    s32 f30;
    s64 f38;
    s32 f40;
    f32 f44;
    f32 f48;
};

void func_0018D800(void* dst, void* src, s32 size);

void func_0015C260(Record_0015C260* src, Record_0015C260* dst)
{
    dst->f00 = src->f00;
    dst->f04 = src->f04;
    dst->f08 = src->f08;
    dst->f44 = src->f44;
    dst->f48 = src->f48;
    dst->count0C = src->count0C;
    func_0018D800(dst->body10, src->body10, src->count0C << 3);
    dst->f30 = src->f30;
    dst->f38 = src->f38;
    dst->f40 = src->f40;
}

struct Pair_15EF88 { u8 pad0[0x4]; s32 f4; u8 pad8[0x4]; s32 fC; };

extern s32 D_00261F18;
extern s32 D_00261F1C;

void func_0015ED50(void* a, s32 b);
void func_001686E8(s32 a, s32 b);

void func_0015EF88(Pair_15EF88* self, s32 flag)
{
    func_0015ED50(self, flag);
    func_001686E8(D_00261F18, self->fC);
    if (flag != 0) {
        *(volatile s32*)0x10003010 = 0;
        func_001686E8(D_00261F1C, self->f4);
    }
}

extern u8 D_00262280[];
extern u8 D_002622A8[];

void func_001611B8(void* p);
void func_001EE318(void* p);

void func_0015F618(s32 flag, s32 code)
{
    if (code == 0xFFFF && flag != 0) {
        func_001611B8(D_00262280);
        func_001EE318(D_002622A8);
    }
}

void func_0015F618(s32 flag, s32 code);

void func_0015F658(void)
{
    func_0015F618(1, 0xFFFF);
}

struct __attribute__((aligned(16))) Quad_15C0A0 {
    s32 w0;
    s32 w1;
    f32 f2;
    s32 w3;
};

struct Frame_15C0A0 {
    Quad_15C0A0 q;
    s32 a;
    s32 b;
};

struct Obj_15C0A0 {
    u8 pad0[0x14];
    s32 x14;
    u8 pad1[0x140 - 0x18];
    Quad_15C0A0 q140;
    u8 pad2[0x64C - 0x150];
    f32 f64c;
    u8 pad3[0x66C - 0x650];
    f32 f66c;
};

extern f32 D_00261858[];

typedef s32 (*Pred_15C0A0)(void* a, void* b);

s32 func_0015C058(void* a, void* b);
void func_0018D608(void* self);
s32 func_001419E8(s32 zero, void* p, void* q, s32 a, s32 b, s32 c);
void func_0018D6F0(void);
void func_001DC4D0(s32 a0, s32 a1, void* a2, Pred_15C0A0 a3, void* a4, s32* a5, s32* a6, f32 f12);

s32 func_0015C0A0(Obj_15C0A0* self)
{
    f32* tbl = D_00261858;
    if (tbl[1] - self->f66c < 0.05f) {
        return 0;
    }
    func_0018D608(self);
    Frame_15C0A0 fr;
    func_001DC4D0(self->x14, 0, &self->q140, func_0015C058, self, &fr.a, &fr.b, self->f64c);
    fr.q = self->q140;
    fr.q.f2 = fr.q.f2 - self->f64c;
    s32 r = func_001419E8(0, &self->q140, &fr.q, fr.a, fr.b, 0);
    func_0018D6F0();
    self->f66c = tbl[1];
    return r == 0;
}

void func_00152B80(void* list, u32 count, s32 value);

extern s32 D_0026230C;

void func_0015EAE0(void* list, s32 value, s32 end)
{
    if (D_0026230C != value) {
        D_0026230C = value;
        func_00152B80(list, ((u32)(end - value) + 15) >> 4, value);
    }
}

void func_001613C0(void* obj, s32 a, s32 b, s32 c);
void func_00161708(void* obj, s32 a, s32 b);
void func_00161200(void* obj);
void func_00152D30(void* obj);
void func_001529E0(void* obj, void* a, s32 b);

void func_0015EBF0(void* obj, void* a, s32 b)
{
    func_001613C0(obj, 0, 1, 0xE);
    func_00161708(obj, 0x61, 0);
    func_00161200(obj);
    func_00152D30(obj);
    func_001529E0(obj, a, b);
}


void func_0015EB20(void* list, void* a, s32 b);
void func_0015EBF0(void* obj, void* a, s32 b);
void func_00152440(void* p);
void func_001F6B40(void* a);

extern u8 D_002622A8[];
extern u8 D_00262280[];
extern Rec12_0015EC68 D_002622E0;
extern Rec12_0015EC68 D_002622F0;
extern Rec12_0015EC68 D_00262300;
extern s32 D_002622D0;
extern void* D_002623B0;

void func_0015EC68(void)
{
    func_0015EB20(D_002622A8, (u8*)D_002622D8 + 8, 0);
    func_0015EBF0(D_00262280, D_002622D8, 0);
    D_002622D8->r20 = D_002622E0;
    func_00152440(&D_002622E0);
    D_002622D8->r2C = D_002622F0;
    func_00152440(&D_002622F0);
    D_002622D8->r38 = D_00262300;
    func_00152440(&D_00262300);
    D_002622D0 = 0;
    D_002622D8 = 0;
    func_001F6B40(D_002623B0);
}

struct Obj_0015C3C0;

void func_001613C0(Obj_0015C3C0* obj, s32 a1, s32 a2, s32 a3);
void func_00161708(Obj_0015C3C0* obj, s32 a1, u64 key);

void func_0015C3C0(void* unused, s32 flag, Obj_0015C3C0* obj)
{
    if (flag != 0) {
        func_001613C0(obj, 0, 1, 0xE);
        func_00161708(obj, 0x40, 0xDF0000027F0000UL);
    }
}

struct Ctx_15ED50 {
    u8 pad0[0x10];
    s32 f10;
    u8 pad1[0x08];
    s32 f1C;
    u8 pad2[0x24];
    s32 f44;
};

extern s32 D_002622D4;
extern s32 D_00274538;
extern s32 D_00261F1C;

void func_001B3488(s32 value);
void func_00202A80(s32 a, s32 b);

void func_0015ED50(Ctx_15ED50* self)
{
    D_002622D4 = self->f10;
    func_001B3488(self->f44);
    if (self->f1C != 0 && D_00274538 != 0) {
        *(volatile s32*)0x10003010 = 4;
        func_00202A80(D_00261F1C, D_00274538);
    }
}

struct Cursor_15DFA0 { u8 pad[4]; u8* flag; };

void func_0015DB80(void* self);
s32 func_0015DBE0(void* self);

void func_0015DFA0(Cursor_15DFA0* self, s32 n)
{
    func_0015DB80(self);
    for (;;) {
        if (func_0015DBE0(self) == 0) {
            break;
        }
        if (n == 0) {
            break;
        }
        n--;
    }
    *self->flag = 0;
}

typedef f32 (*Visit_15DFF8)(void* at, s32 item);

struct Dispatch_15DFF8 { u8 pad[0x18]; s16 offset; u8 pad2[2]; Visit_15DFF8 visit; };
struct Holder_15DFF8 { u8 pad[0x4C]; Dispatch_15DFF8* disp; };
struct Walker_15DFF8 { u8 pad[8]; Holder_15DFF8* holder; };

void func_0015DB80(void* self);
s32 func_0015DBE0(void* self);

f32 func_0015DFF8(Walker_15DFF8* self)
{
    f32 acc = 0.0f;
    func_0015DB80(self);
    s32 item;
    while ((item = func_0015DBE0(self)) != 0) {
        Holder_15DFF8* holder = self->holder;
        Dispatch_15DFF8* disp = holder->disp;
        acc += disp->visit((u8*)holder + disp->offset, item);
    }
    return acc;
}

struct Sub_15F9A0 { u8 pad0[8]; s32 count; void** items; };
struct Obj_15F9A0 { u8 pad0[0x54]; void* f54; u8 pad1[0x6C - 0x58]; s32 count6C; void* items70[1]; };

void func_0015F930(void* list, void* base, void* item);
void func_0015F710(void* self, void* value);

void func_0015F9A0(void* self, Sub_15F9A0* s)
{
    s32 i;
    Obj_15F9A0* obj;
    if (s->count >= 2) {
        for (i = 0; i < s->count; i++) {
            obj = (Obj_15F9A0*)s->items[i];
            func_0015F930(&obj->count6C, obj->items70, s);
        }
        for (i = 0; i < s->count; i++) {
            obj = (Obj_15F9A0*)s->items[i];
            if (obj->f54 != 0) {
                func_0015F710(self, obj->f54);
                break;
            }
        }
    }
}

typedef f32 (*Measure_15E068)(void* at, s32 ch);
struct Glyph_15E068 { u8 pad[0x18]; s16 offset; u8 pad2[2]; Measure_15E068 measure; };
struct Holder_15E068 { u8 pad[8]; s32 units; u8 pad2[0x3C]; f32 scale; Glyph_15E068* glyph; };
struct Lines_15E068 { s8* start; s8* cur; Holder_15E068* holder; };

void func_0015DB80(void* self);
s32 func_0015DBE0(void* self);

s32 func_0015E068(Lines_15E068* self, f32 limit)
{
    s32 lines = 1;
    f32 width = 0.0f;
    s32 newline = 10;
    s32 space = 32;
    s32 tab = 9;
    func_0015DB80(self);
    s32 c;
    while ((c = func_0015DBE0(self)) != 0) {
        if (c == newline) {
            width = 0.0f;
            lines++;
        } else {
            Holder_15E068* holder = self->holder;
            Glyph_15E068* glyph = holder->glyph;
            width += glyph->measure((u8*)holder + glyph->offset, c);
        }
        if (limit != 0.0f && limit < width) {
            s8* p = self->cur - 1;
            while (p >= self->start) {
                if (*p == 10) {
                    break;
                }
                if (*p == space || *p == tab) {
                    width = 0.0f;
                    self->cur = p + 1;
                    lines++;
                    *p = 10;
                    break;
                }
                p--;
            }
            if (width != 0.0f) {
                *self->cur = (s8)newline;
                lines++;
                width = 0.0f;
            }
        }
    }
    return lines;
}

struct Wrap_15E1B0 { u8 pad[0xC]; Holder_15E068* holder; };

s32 func_0015E068(void* self);

f32 func_0015E1B0(Wrap_15E1B0* self)
{
    Holder_15E068* holder = self->holder;
    f32 width = (f32)holder->units * holder->scale;
    s32 lines = func_0015E068(self);
    return width * (f32)lines;
}

struct Class_0015FB28 { u8 pad0[8]; s32 flags; u8 pad1[0x54]; void (*visit)(void* self, void* arg); };
struct Node_0015FB28 { Class_0015FB28* cls; u8 pad0[0x18]; Node_0015FB28* next; u8 pad1[0x14]; Node_0015FB28* child; };

void func_0015FB28(Node_0015FB28* self, void* arg)
{
    s32 scratch[4];
    (void)scratch;
    if (self->cls->visit != 0)
        self->cls->visit(self, arg);
    Node_0015FB28* node = self->child;
    if (node != 0)
    {
        do
        {
            if (node->cls->flags & 1)
                func_0015FB28(node, arg);
            node = node->next;
        } while (node != 0);
    }
}

struct Obj_0015FBA0 { u8 pad[0x2C8]; u64 flags; };

s32 func_0015FBA0(Obj_0015FBA0* self, s32* out)
{
    s32 bit = (s32)(self->flags >> 38) & 1;
    *out = bit;
    return bit;
}

struct Obj_15C900 { u8 pad0[0xC]; s32 index; u8 pad1[0x34]; f32 first; f32 second; };
void func_0015C900(Obj_15C900* obj) { obj->index--; f32* item = (f32*)((u8*)obj + 0x10 + obj->index * 8); obj->first = item[0]; obj->second = item[1]; }

struct __attribute__((packed)) Unaligned_15DBB8 { s32 v; };

void func_0015DBB8(u8* dst, u8* src)
{
    s32 v = ((Unaligned_15DBB8*)src)->v;
    ((Unaligned_15DBB8*)(dst + 0xA4))->v = v;
    v = ((Unaligned_15DBB8*)(dst + 0xA4))->v;
    ((Unaligned_15DBB8*)(dst + 0x9C))->v = v;
}

struct Elem_15F6C0 { u8 pad[0x54]; void* owner; Elem_15F6C0* next; };
struct Owner_15F6C0 { u8 pad[0x60]; Elem_15F6C0* head; };

void func_00152730(void* dst, void* src);

void func_0015F6C0(void* ctx, Owner_15F6C0* self, Owner_15F6C0* other)
{
    s32 scratch[4];
    (void)scratch;
    if (self != other) {
        Elem_15F6C0* e = other->head;
        if (e != 0) {
            e->owner = self;
            for (e = e->next; e != 0; e = e->next) {
                e->owner = self;
            }
        }
        func_00152730(&self->head, &other->head);
    }
}

extern s8 D_00262250[];
extern s32 D_00262268[];

s32 func_0015C200(s32 a0)
{
    s8 key = (s8)a0;
    s32 i = 0;
    while (i < 5 && key != D_00262250[i]) {
        i++;
    }
    if (i < 5) {
        return D_00262268[i];
    }
    return 0;
}

struct Obj_15C4A8 {
    u8 pad0[8];
    s32 f8;
    u8 pad0C[0x3C];
    f32 f48;
};

s32 func_0015C4E8(void* self, u8* s);

f32 func_0015C4A8(Obj_15C4A8* self, u8* s)
{
    f32 a = (f32)self->f8 * self->f48;
    s32 n = func_0015C4E8(self, s);
    return a * (f32)n;
}

// NEAR: the first load of self->p54 goes to $v0 (retail $v1), so two
// pointer loads differ in register choice; everything else matches.

struct Frame_15D998 { u8 a[0x30]; u8 buf[0x100]; };
struct Obj_15D998 { u8 pad[0x54]; u8* p54; u8* p58; u64 f60; u32 f68; u32 f6C; u32 f70; u32 f74; };
struct Sub_15D998 { u8 pad[0xA]; u16 f0A; u8 pad2[0xC]; u64 f18; };
struct Next_15D998 { u8 pad[6]; u16 f6; u8 pad8[8]; u64 f10; };

s32 func_001611B8(Frame_15D998* p);
s32 func_00168D88(void* self, s32 size);
void func_00168FB0(void* self, s32 v);
void func_001529C8(void* self, s32 count, void* base);
void func_00169088(void* self, s32 dbp, void* ctx);
void func_00152A50(void* self, u32* count, u32* begin, u32* out, s32 flag);
void func_00168E78(void* self, s32 v);
void func_00168F48(void* self, s32 v, void* ctx);

void func_0015D998(Obj_15D998* self, void* arg)
{
    Frame_15D998 f;
    s32 n;

    (void)func_001611B8(&f);
    Sub_15D998* q = (Sub_15D998*)self->p54;
    n = func_00168D88(arg, q->f0A);
    func_00168FB0(self->p54, n);
    self->f60 = ((Sub_15D998*)self->p54)->f18;
    func_001529C8(f.a, 16, f.buf);
    func_00169088(self->p54, n, f.a);
    func_00152A50(f.a, &self->f68, 0, &self->f6C, 7);
    if (self->p58 != 0) {
        n = func_00168D88(arg, ((Next_15D998*)self->p58)->f6);
        func_00168E78(self->p58, n);
        u64 t = self->f60;
        t |= ((Next_15D998*)self->p58)->f10;
        self->f60 = t;
        func_001529C8(f.a, 16, f.buf);
        func_00168F48(self->p58, n, f.a);
        func_00152A50(f.a, &self->f70, 0, &self->f74, 7);
    }
}

// Matched: for loop over i with D_00262264 + i * 0x88.

extern s32 D_00262260;
extern u8* D_00262264;

void func_00168D68(void* dst, s32 size, s32 align);
void func_0015D998(void* item, void* buf);

void func_0015E5F0(void)
{
    u8 buf[16];
    func_00168D68(buf, 0x1400, 0x1E00);
    for (s32 i = 0; i < D_00262260; i++) {
        func_0015D998(D_00262264 + i * 0x88, buf);
    }
}

struct Self_15D338 { u8 pad[0x40]; u32 f40; };
struct Strm_15D338 { u8 pad[4]; };
void func_001617E8(Strm_15D338* s, u32 tag, f32 value);
void func_00161860(Strm_15D338* s, s32 a, s32 b);
void func_001618C0(Strm_15D338* s, s32 a, s32 b, u32 c, u32 d);

void func_0015D338(Self_15D338* self, u32 color, Strm_15D338* s, f32 x0, f32 y0, f32 x1, f32 y1,
                   f32 u0, f32 v0, f32 u1, f32 v1)
{
    color = (color & 0xFFFFFF) | ((((color >> 24) + 1) & 0x1FE) << 23);
    func_001617E8(s, color, 0.0f);
    func_00161860(s, (s32)(u0 * 16.0f), (s32)(v0 * 16.0f));
    func_001618C0(s, (s32)((x0 + 1728.0f) * 16.0f), (s32)((y0 * 0.45454547f + 1936.0f) * 16.0f), self->f40, 0);
    func_00161860(s, (s32)(u1 * 16.0f), (s32)(v1 * 16.0f));
    func_001618C0(s, (s32)((x1 + 1728.0f) * 16.0f), (s32)((y1 * 0.45454547f + 1936.0f) * 16.0f), self->f40, 0);
}

struct Self_15CD18 {
    u8 p0[0x4];
    s32 m4;
    s32 m8;
    u8 p0c[0x40 - 0x0C];
    s32 m40;
    f32 f44;
    f32 f48;
    u8 p4c[0x60 - 0x4C];
    u64 m60;
};

struct Entry_15CD18 {
    u8 p0[0x2];
    u16 a2;
    u16 a4;
    u16 a6;
};

struct Stream_15CD18 {
    s32 unused;
};

Entry_15CD18* func_0015DAB8(Self_15CD18* self, s8 key);
void func_001617E8(Stream_15CD18* s, s32 tag, f32 value);
void func_00161860(Stream_15CD18* s, s32 a, s32 b);
void func_001618C0(Stream_15CD18* s, s32 a, s32 b, s32 c, s32 d);

f32 func_0015CD18(f32 x, f32 y, Self_15CD18* self, s8 key, u32 color, Stream_15CD18* s)
{
    Entry_15CD18* e = func_0015DAB8(self, key);
    if (e != 0) {
        s32 shift = (s32)((self->m60 >> 30) & 0xF);
        s32 s4 = 1 << shift;
        f32 h = (f32)self->m8 * self->f48;
        f32 w = (f32)e->a6 * self->f44;
        f32 px = x + w;
        f32 py = y + h;
        if (0.0f <= px && x <= 640.0f && 0.0f <= py && y <= 492.80002f) {
            u32 tag = (color & 0xFFFFFF) | ((((color >> 24) + 1) & 0x1FE) << 23);
            func_001617E8(s, tag, 0.0f);
            func_00161860(s, e->a2 << 4, (s4 - e->a4) << 4);
            func_001618C0(s, (s32)((x + 1728.0f) * 16.0f),
                          (s32)((y * 0.45454547f + 1936.0f) * 16.0f), self->m40, 0);
            func_00161860(s, (e->a2 + e->a6) << 4, (s4 - (e->a4 + self->m8)) << 4);
            func_001618C0(s, (s32)((px + 1728.0f) * 16.0f),
                          (s32)((py * 0.45454547f + 1936.0f) * 16.0f), self->m40, 0);
        }
        return (f32)(e->a6 + 1) * self->f44;
    }
    return (f32)self->m4 * self->f44;
}

struct Params_15E290 { u8 pad0[8]; s32 count; u8 pad1[0x3C]; f32 scale; };
struct __attribute__((aligned(4))) Owner_15E290 { u8 pad0[0xC]; Params_15E290* params; };

s32 func_0015E068(void* self, f32 f);
f32 func_0015E1F0(void* self);

void func_0015E290(void* self, f32 f, f32* out1, f32* out2)
{
    s32 n = func_0015E068(self, f);
    f32 g = func_0015E1F0(self);
    Owner_15E290* o = (Owner_15E290*)self;
    f32 k = (f32)o->params->count * o->params->scale;
    f32 t = (f32)n * k;
    if (out1 != 0) {
        *out1 = g;
    }
    if (out2 != 0) {
        *out2 = t;
    }
}

struct Item_15F7D8 { u8 pad[0x54]; void* f54; };
struct Group_15F7D8 { u8 pad[8]; s32 count; Item_15F7D8** items; };

s32 func_00182FC8(void* p);
void func_0015F6C0(void* ctx, void* a, void* b);

void func_0015F7D8(void* self, Group_15F7D8* group)
{
    s32 i = 0;
    while (i < group->count) {
        if (func_00182FC8(group->items[i]) != 0) {
            break;
        }
        i++;
    }
    s32 first = i;
    for (; i < group->count; i++) {
        if (func_00182FC8(group->items[i]) != 0) {
            func_0015F6C0(self, group->items[first]->f54, group->items[i]->f54);
        }
    }
}

struct Item_15F8B0 { u8 pad[0x6C]; s32 count6C; void* items70[4]; };
struct Group_15F8B0 { u8 pad[8]; s32 count; Item_15F8B0** items; };

void func_0015F7D8(void* self, Group_15F8B0* group);

void func_0015F8B0(void* self, Group_15F8B0* group)
{
    if (group->count >= 2) {
        for (s32 i = 0; i < group->count; i++) {
            Item_15F8B0* item = group->items[i];
            u32 n = item->count6C;
            if (n < 4) {
                item->items70[n] = group;
                item->count6C = n + 1;
            }
        }
        func_0015F7D8(self, group);
    }
}
