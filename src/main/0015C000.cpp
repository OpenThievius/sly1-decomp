// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"

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

s32 D_0026230C;

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
s32 func_001F6B40(void* a);

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

void func_0015D338(Self_15D338* self, u32 color, f32 x0, f32 y0, f32 x1, f32 y1,
                   f32 u0, f32 v0, f32 u1, f32 v1, Strm_15D338* s)
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

struct Obj_0015C2E8;
struct Vec4_0015C2E8 { f32 x; f32 y; f32 z; f32 w; };

void func_001613C0(Obj_0015C2E8* obj, s32 a1, s32 a2, s32 a3);
void func_00161708(Obj_0015C2E8* obj, s32 a1, u64 key);

void func_0015C2E8(void* unused, Vec4_0015C2E8* v, Obj_0015C2E8* obj)
{
    if (v != 0) {
        s32 pw = (s32)(v->x + v->z) - 1;
        s32 pz = (s32)((v->y + v->w) * 0.454545468f) - 1;
        s32 py = (s32)(v->y * 0.454545468f);
        s32 px = (s32)v->x;
        func_001613C0(obj, 0, 1, 0xE);
        u64 key = (u64)px | ((u64)pw << 16) | ((u64)py << 32) | ((u64)pz << 48);
        func_00161708(obj, 0x40, key);
    }
}

extern u32 D_002C3B00[];
extern u8 D_00148D74[];
extern s32 D_00262310;

void func_0015EDB8(void)
{
    const u8* table = (const u8*)D_002C3B00;
    s32 n = (s32)D_00148D74;
    u32 crc = 0xFFFFFFFF;
    u32* p = (u32*)0x00100000;
    if (n > 0) {
        do {
            u32 w = *p;
            n -= 4;
            p++;
            crc = *(u32*)(table + (((crc ^ w) & 0xFF) << 2)) ^ (crc >> 8);
            crc = *(u32*)(table + (((crc ^ (w >> 8)) & 0xFF) << 2)) ^ (crc >> 8);
            crc = *(u32*)(table + (((crc ^ (w >> 16)) & 0xFF) << 2)) ^ (crc >> 8);
            crc = *(u32*)(table + (((crc ^ (w >> 24)) & 0xFF) << 2)) ^ (crc >> 8);
        } while (n > 0);
    }
    if (crc != 0) {
        D_00262310 = 1;
    }
}

typedef f32 (*Fn_15C418)(void* self, s8 ch);
struct Node_15C418 { u8 pad0[0x18]; s16 off; u8 pad1[2]; Fn_15C418 fn; };
struct Obj_15C418 { u8 pad0[0x4C]; Node_15C418* node; };
f32 func_0015C418(Obj_15C418* self, s8* s)
{
    f32 acc;
    s8* p;
    if (s == 0) {
        return 0.0f;
    }
    p = s;
    acc = 0.0f;
    while (*p != 0) {
        Node_15C418* n = self->node;
        acc = acc + n->fn((u8*)self + n->off, (u8)*p++);
    }
    return acc;
}

extern void* D_002623B4;
extern volatile s32 D_002623B8;
extern void* D_0026231C;
extern s32 D_002626CC;
extern u8 D_00262320[];

s32 func_001F6B60(void* a);
void func_0015EF88(void* self, s32 flag);
void func_0015F320(void);
void func_001683E8(void);
void func_0015EFE8(void* p);
void func_00191EB0(s32 a);

void func_0015F210(s32 flag)
{
    for (s32 i = 0; (u32)i < 2; i++) {
        func_001F6B60(D_002623B4);
    }
    for (s32 i = 0; (u32)i < 2; i++) {
        func_001F6B40(D_002623B4);
    }
    while (D_002623B8 == 0) {
    }
    if (flag != 0 && D_0026231C != 0) {
        s32 n = 2;
        do {
            func_0015EF88(D_0026231C, 1);
            func_0015F320();
            func_001683E8();
        } while (--n >= 0);
        D_002626CC = 3;
    }
    u8* p = D_00262320;
    u8* end = p + 0x90;
    do {
        func_0015EFE8(p);
        p += 0x48;
    } while (p < end);
    func_00191EB0(3);
    D_0026231C = 0;
}

struct Local_15D8A8 {
    u16 u0;
    u16 u2;
    u8 b4;
    u8 b5;
    u8 b6;
    u8 b7;
    f32 f8;
    u16 uC;
    u16 padE;
};

struct Obj_15D8A8 {
    s32 f0;
    s32 f4;
    s32 f8;
    u8 pad0C[0x44 - 0x0C];
    f32 f44;
    f32 f48;
    s32 f4C;
    s32 f50;
    void* f54;
    void* f58;
    u8 pad5C[0x78 - 0x5C];
    s32 f78;
    void* f7C;
};

extern u8* D_00274504;
extern u8* D_0027450C;

void func_00137A60(void* src, s32 n, void* dst);
void* func_0018D500(s32 n);

void func_0015D8A8(Obj_15D8A8* obj, void* src)
{
    Local_15D8A8 l;
    func_00137A60(src, 0x10, &l);
    s32 idx = l.b7;
    obj->f50 = idx;
    D_00262268[idx] = (s32)obj;
    obj->f54 = D_00274504 + l.u0 * 32;
    void* t;
    if (l.u2 != 0xFFFF) {
        t = D_0027450C + l.u2 * 24;
    } else {
        t = 0;
    }
    obj->f58 = t;
    s32 n = l.uC;
    s32 A = l.b4, B = l.b5, C = l.b6; f32 F = l.f8;
    obj->f0 = A;
    obj->f44 = F;
    obj->f78 = n;
    obj->f8 = C;
    obj->f4 = B;
    obj->f48 = F;
    obj->f7C = func_0018D500(n << 3);
    func_00137A60(src, obj->f78 << 3, obj->f7C);
}

typedef void (*Fn_15CF70)(void* at, s32 a, void* b);
struct Disp_15CF70 { u8 pad[0x38]; s16 offset; u8 pad2[2]; Fn_15CF70 fn; };
struct Self_15CF70 {
    u8 p0[4];
    s32 m4;
    s32 m8;
    u8 p0c[0x30 - 0x0C];
    s32 f30;
    u8 p34[4];
    u64 f38;
    s32 m40;
    f32 f44;
    f32 f48;
    Disp_15CF70* disp;
    u8 p50[0x60 - 0x50];
    u64 m60;
};
struct Entry_15CF70 { u8 p0[2]; u16 a2; u16 a4; u16 a6; };
struct Strm_15CF70 { u8 pad[4]; };

s32 D_00262258 = -8;
s32 D_0026225C = -8;
extern u8 D_00262280[];

Entry_15CF70* func_0015DAB8(Self_15CF70* self, s8 key);
s32 func_0015CAB8(Self_15CF70* self, Strm_15CF70* s);
void func_001613C0(Strm_15CF70* s, s32 a, s32 b, s32 c);
void func_00161708(Strm_15CF70* s, s32 a, u64 b);
void func_00161768(Strm_15CF70* s, s32 a, u64 b);
void func_001617E8(Strm_15CF70* s, u32 tag, f32 value);
void func_00161860(Strm_15CF70* s, s32 a, s32 b);
void func_001618C0(Strm_15CF70* s, s32 a, s32 b, s32 c, s32 d);

void func_0015CF70(Self_15CF70* self, s8 key, u32 color, Strm_15CF70* s, f32 x, f32 y)
{
    Entry_15CF70* e = func_0015DAB8(self, key);
    if (e != 0) {
        s32 shift = (s32)((self->m60 >> 30) & 0xF);
        s32 s4 = 1 << shift;
        f32 h = (f32)self->m8 * self->f48;
        f32 w = (f32)e->a6 * self->f44;
        f32 px = x + h;
        f32 py = y + w;
        if (0.0f <= px && x <= 640.0f && 0.0f <= py && y <= 492.80002f) {
            s32 u0 = (e->a2 << 4) + D_00262258;
            s32 v0 = ((s4 - e->a4) << 4) + D_0026225C;
            s32 u1 = ((e->a2 + e->a6) << 4) + D_00262258;
            s32 v1 = ((s4 - (e->a4 + self->m8)) << 4) + D_0026225C;
            s32 ok = func_0015CAB8(self, s);
            func_001613C0(s, 6, 1, 0xE);
            if (ok != 0) {
                func_00161708(s, 0x3F, (u64)0);
            }
            u64 v = 0x31001;
            if (self->f30 != 0) {
                v = self->f38;
            }
            func_00161708(s, 0x47, (u64)v);
            func_00161708(s, 0x42, (u64)0x44);
            func_00161708(s, 6, (u64)self->m60);
            func_00161708(s, 0x14, (u64)0x60);
            func_00161708(s, 8, (u64)5);
            func_00161708(s, 0, (u64)0x1D4);
            func_00161768(s, 9, 0x434343431ULL);
            u32 tag = (color & 0xFFFFFF) | ((((color >> 24) + 1) & 0x1FE) << 23);
            func_001617E8(s, tag, 0.0f);
            func_00161860(s, u0, v0);
            s32 sx = (s32)((x + 1728.0f) * 16.0f);
            s32 sy = (s32)((py * 0.45454547f + 1936.0f) * 16.0f);
            func_001618C0(s, sx, sy, self->m40, 0);
            func_00161860(s, u1, v0);
            s32 sy2 = (s32)((y * 0.45454547f + 1936.0f) * 16.0f);
            func_001618C0(s, sx, sy2, self->m40, 0);
            func_00161860(s, u0, v1);
            s32 sx2 = (s32)((px + 1728.0f) * 16.0f);
            func_001618C0(s, sx2, sy, self->m40, 0);
            func_00161860(s, u1, v1);
            func_001618C0(s, sx2, sy2, self->m40, 0);
            self->disp->fn((u8*)self + self->disp->offset, 0, D_00262280);
        }
    }
}

struct Dispatch_15C4E8 {
    u8 pad0[0x18];
    s16 off;
    u8 pad1A[2];
    void* fn;
};

struct Obj_15C4E8 {
    u8 pad0[0x4C];
    Dispatch_15C4E8* tbl;
};

s32 func_0015C4E8(Obj_15C4E8* self, u8* s, f32 w)
{
    s32 count = 1;
    s8* cur = (s8*)s;
    f32 acc = 0.0f;
    while (*cur != 0) {
        s32 c = (s8)(s32)*(u8*)cur;
        if (c == 10) {
            acc = 0.0f;
            count++;
        } else {
            Dispatch_15C4E8* t = self->tbl;
            acc += ((f32 (*)(void*, s32))t->fn)((u8*)self + t->off, c);
        }
        if (w != 0.0f && w < acc) {
            s8* p = cur;
            while (p >= (s8*)s) {
                s8 c2 = *p;
                if (c2 == 10) {
                    break;
                }
                if (c2 == 32 || c2 == 9) {
                    cur = p;
                    acc = 0.0f;
                    *cur = 10;
                    count++;
                    break;
                }
                p--;
            }
            if (acc != 0.0f) {
                *cur = 10;
                count++;
                acc = 0.0f;
            }
        }
        cur++;
    }
    return count;
}

// NEAR: CRC table loop: retail keeps inner counter k in v1 and n*4 in a1; ours swaps them (5 insns)

struct Sub_15E810 { u8 pad[0xC]; };
struct Rec_15E810 {
    u8 p0[4];
    u8* a4;
    u8 p8[4];
    u8* aC;
    u8* a10;
    u8 p14[0xC];
    Sub_15E810 s20;
    Sub_15E810 s2C;
    Sub_15E810 s38;
    u8 p44[4];
};
extern u8 D_003C3B00[], D_005C3B00[];
extern void* D_002623B0;
extern void* D_002623B4;
extern void* D_00275958[];
void func_00152438(Sub_15E810* self, s32 value);
void func_001F6950(s32 a0, void (*fn)(void), s32 a2);
void func_001F6DA8(s32 a0);
void* func_001E2268(s32 a, s32 b);
void func_001F6A20(void* a, s32 b);
void func_0015E678(void);

void func_0015E810(void)
{
    for (u32 i = 0; i < 2; i++) {
        Rec_15E810* r = &((Rec_15E810*)D_00262320)[i];
        r->a4 = (u8*)D_002C3B00 + i * 0x80000;
        r->aC = D_003C3B00 + i * 0x100000;
        r->a10 = D_005C3B00 + i * 0x10600;
        func_00152438(&r->s20, 0x630);
        func_00152438(&r->s2C, 0x1090);
        func_00152438(&r->s38, 0xB8);
    }
    func_00152438((Sub_15E810*)&D_002622E0, 0x630);
    func_00152438((Sub_15E810*)&D_002622F0, 0x1090);
    func_00152438((Sub_15E810*)&D_00262300, 0xB8);
    func_001F6950(5, (void (*)(void))((u8*)func_0015E678 + 0x30), 0);
    func_001F6DA8(5);
    D_002623B0 = func_001E2268(0, 2);
    D_002623B4 = func_001E2268(2, 2);
    u32* tab = (u32*)D_002C3B00;
    s32 n = 0;
    do {
        u32 c = n;
        s32 off = n * 4;
        for (s32 k = 7; k >= 0; k--) {
            if (c & 1) c = (c >> 1) ^ 0xEDB88320;
            else c >>= 1;
        }
        *(u32*)((u8*)tab + off) = c;
        n++;
    } while (n < 256);
    func_001F6A20(D_00275958[1], 0);
}

s32 func_0015C188(s32 a0)
{
    if (a0 == -1) {
        goto none;
    }
    if (((s32*)D_00262268)[a0] != 0) {
        goto some;
    }
none:
    return 0;
some:
    return 1;
}

struct Block_0015DB80 { s32 w0; s32 w4; s32 w8; s32 wC; u8 pad10[0x88]; s32 tail98; };
struct __attribute__((packed)) Unaligned_0015DB80 { s32 value; };

void func_0015DB80(Block_0015DB80* self)
{
    s32 t;
    self->w4 = self->w0;
    self->w8 = self->wC;
    t = ((Unaligned_0015DB80*)((u8*)self + 0xA4))->value;
    ((Unaligned_0015DB80*)((u8*)self + 0xA0))->value = t;
    t = ((Unaligned_0015DB80*)((u8*)self + 0xA0))->value;
    ((Unaligned_0015DB80*)((u8*)self + 0x9C))->value = t;
    self->tail98 = 0;
}

struct Blk_0015DB28 {
    s32 f00;
    u8 pad0[0x0C - 0x04];
    s32 f0C;
    u8 pad1[0x5C - 0x10];
    void* f5C;
    u8 pad2[0x9C - 0x60];
    u32 f9C;
    u32 fA0;
    u32 fA4;
    u32 fA8;
};

void func_0015DB80(Blk_0015DB28* self);

Blk_0015DB28* func_0015DB28(Blk_0015DB28* self, s32 a1, s32 a2)
{
    self->f5C = (u8*)&D_0024A220;
    self->f00 = a1;
    self->f0C = a2;
    self->fA8 = 0xFF808080;
    self->fA4 = 0xFF808080;
    self->fA0 = 0xFF808080;
    self->f9C = 0xFF808080;
    func_0015DB80(self);
    return self;
}

// EXACT: element address written as off + (u32)entries

struct Entry_15DAB8 {
    u16 key;
    u8 pad[6];
};

struct Table_15DAB8 {
    u8 pad0[0x78];
    s32 count;
    Entry_15DAB8* entries;
};

void* func_0015DAB8(Table_15DAB8* self, u8 key)
{
    s32 lo = 0;
    s32 hi = self->count - 1;

    if (hi >= 0) {
        do {
            s32 mid = (hi + lo) / 2;
            s32 off = mid * 8;
            Entry_15DAB8* e = (Entry_15DAB8*)(off + (u32)self->entries);
            s32 d = key - e->key;

            if (d == 0) {
                return e;
            }
            if (d > 0) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        } while (!(hi < lo));
    }
    return 0;
}

struct A_0015C058 { u8 pad[0x50]; s32 f50; };
struct B_0015C058 { u8 pad0[0x50]; s32 f50; u8 pad1[0x278]; u32 f2CC; u8 pad2[0x268]; u64 f538; };

s32 func_0015C058(A_0015C058* a0, B_0015C058* a1)
{
    if ((a1->f538 & 0x80000000000ULL) || a1->f50 == a0->f50) return 0;
    u64 v = a1->f2CC;
    return ((s32)v ^ 1) & 1;
}

struct Frame_15EE80 { u8 pad0[0x4]; s32 f4; u8 pad8[0x4]; s32 fC; u8 pad10[0x38]; };

extern void* D_002623B0;
extern void* D_002623B4;
u32 D_00262314;
extern s32 D_00261F18;
extern s32 D_00261F1C;
extern s32 D_002626CC;

void func_0015EDB8(void);
s32 func_001F6B60(void* p);
void func_0015ED50(Frame_15EE80* f);
void func_001684E8(void);
void func_001686E8(s32 a, s32 b);
void func_0015F320(void);
void func_00202C38(s32 a, s32 b, s32 c);
void func_001683E8(void);

void func_0015EE80(void)
{
    func_0015EDB8();
    for (;;) {
        D_002623B8 = 1;
        func_001F6B60(D_002623B0);
        D_002623B8 = 0;
        D_0026231C = &((Frame_15EE80*)D_00262320)[D_00262314];
        D_00262314++;
        if (D_00262314 >= 2) {
            D_00262314 = 0;
        }
        func_0015ED50((Frame_15EE80*)D_0026231C);
        func_001684E8();
        func_001686E8(D_00261F18, ((Frame_15EE80*)D_0026231C)->fC);
        *(volatile s32*)0x10003010 = 0;
        func_001686E8(D_00261F1C, ((Frame_15EE80*)D_0026231C)->f4);
        func_0015F320();
        func_00202C38(D_00261F18, 0, 0);
        func_001F6B40(D_002623B4);
        func_001683E8();
        D_002626CC = 1;
    }
}

struct List_15EFE8 {
    u8* head;
    u8* tail;
    s32 offset;
};

struct Iter_15EFE8 {
    List_15EFE8* list;
    u8* link;
    s32 offset;
    Iter_15EFE8* prev;
};

struct Node_15EFE8 {
    u8 pad0[0x14];
    u8* f14;
    u8 pad18[0x1088 - 0x18];
    void* f1088;
};

struct Obj_15EFE8 {
    u8 pad0[0x20];
    List_15EFE8 l0;
    List_15EFE8 l1;
    List_15EFE8 l2;
};

extern u8* D_00275710;

s32 func_00152720(List_15EFE8* l);
void func_00152600(List_15EFE8* l, Node_15EFE8* n);
void func_00152470(u8* l, Node_15EFE8* n);
void func_00152440(List_15EFE8* l);
void func_001B5F28(u8* l, void* n);

struct Begin_15EFE8 {
    static void Of(Iter_15EFE8* it, List_15EFE8* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = ((Iter_15EFE8*)D_0027B314);
        D_0027B314 = (ListFrame*)it;
    }
};

struct Next_15EFE8 {
    static Node_15EFE8* Of(Iter_15EFE8* it)
    {
        Node_15EFE8* obj = *(Node_15EFE8**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

void func_0015EFE8(Obj_15EFE8* self)
{
    Iter_15EFE8 it;
    Node_15EFE8* n;
    if (func_00152720(&self->l0) == 0) {
        Begin_15EFE8::Of(&it, &self->l0);
        while ((n = Next_15EFE8::Of(&it)) != 0) {
            func_00152600(&self->l0, n);
            func_00152470(n->f14 + 0x1CC0, n);
        }
        func_00152440(&self->l0);
        D_0027B314 = (ListFrame*)it.prev;
    }
    if (func_00152720(&self->l1) == 0) {
        Begin_15EFE8::Of(&it, &self->l1);
        while ((n = Next_15EFE8::Of(&it)) != 0) {
            if (n->f1088 != 0) {
                func_001B5F28(D_00275710 + 0x1B4C, n->f1088);
            }
            func_00152600(&self->l1, n);
            func_001B5F28(D_00275710 + 0x1B40, n);
        }
        func_00152440(&self->l1);
        D_0027B314 = (ListFrame*)it.prev;
    }
    if (func_00152720(&self->l2) == 0) {
        Begin_15EFE8::Of(&it, &self->l2);
        while ((n = Next_15EFE8::Of(&it)) != 0) {
            func_00152600(&self->l2, n);
            func_001B5F28(D_00275710 + 0x1BF4, n);
        }
        D_0027B314 = (ListFrame*)it.prev;
    }
}

typedef struct Obj_15C638 Obj_15C638;
typedef struct Par_15C638 Par_15C638;
typedef struct VT_15C638 VT_15C638;
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long s64;
typedef unsigned long u64;
typedef float f32;
struct Obj_15C638;
typedef void (*FnA_15C638)(Obj_15C638 *self, s32 a, s32 b);
typedef f32 (*FnW_15C638)(Obj_15C638 *self, s32 ch);
typedef f32 (*FnD_15C638)(f32 x, f32 y, Obj_15C638 *self, s32 ch, s32 p, s32 q);
struct VT_15C638
{
  u8 pad0[0x18];
  s16 adj18;
  u16 pad1A;
  FnW_15C638 fn1C;
  s16 adj20;
  u16 pad22;
  FnA_15C638 fn24;
  u8 pad28[0x30 - 0x28];
  s16 adj30;
  u16 pad32;
  FnD_15C638 fn34;
  s16 adj38;
  u16 pad3A;
  FnA_15C638 fn3C;
};
struct Obj_15C638
{
  u8 pad0[8];
  s32 f8;
  u8 pad0C[0x48 - 0x0C];
  f32 f48;
  VT_15C638 *f4C;
};
struct Par_15C638
{
  f32 f0;
  f32 f4;
  f32 f8;
  f32 fC;
  s32 f10;
  s32 f14;
  s32 f18;
};
void func_0015C638(Obj_15C638 *self, char *str, Par_15C638 *par, s32 a3, s32 a4)
{
  char *p;
  char *next;
  s32 pending = 1;
  f32 x;
  f32 y;
  self->f4C->fn24((Obj_15C638 *) (((u8 *) self) + self->f4C->adj20), a3, a4);
  if (par->f18 == 0)
  {
    y = par->f4;
  }
  else
  {
    f32 sc = self->f48;
    f32 h = ((f32) self->f8) * sc;
    char *q = str;
    if ((*q) != 0)
    {
      do
      {
        if ((*(q++)) == '\n')
        {
          h += ((f32) self->f8) * sc;
        }
      }
      while ((*q) != 0);
    }
    if (par->f18 == 2)
    {
      y = (par->f4 + par->fC) - h;
    }
    else
    {
      y = par->f4 + ((par->fC - h) * 0.5f);
    }
  }
  for (p = str; (*p) != 0; p = next)
  {
    f32 half = 0.5f;
    s32 right = 2;
    char c = *((u8 *) p);
    next = p + 1;
    if (c == '\n')
    {
      pending = 1;
      y += ((f32) self->f8) * self->f48;
    }
    else
    {
      if (pending != 0)
      {
        if (par->f14 == 0)
        {
          x = par->f0;
        }
        else
        {
          char *q;
          x = 0.0f;
          for (q = p; (*q != 0) && (*q != '\n'); q++)
          {
            x += self->f4C->fn1C((Obj_15C638 *) (((u8 *) self) + self->f4C->adj18), *q);
          }
          if (par->f14 == right)
          {
            x = (par->f0 + par->f8) - x;
          }
          else
          {
            x = par->f0 + ((par->f8 - x) * half);
          }
        }
        pending = 0;
      }
      x += self->f4C->fn34(x, y, (Obj_15C638 *) (((u8 *) self) + self->f4C->adj30), *p, par->f10, a4);
    }
  }

  self->f4C->fn3C((Obj_15C638 *) (((u8 *) self) + self->f4C->adj38), a3, a4);
}

struct __attribute__((packed)) U4_15E318 { u32 v; };
class Font_15E318 {
public:
    u8 pad[0x4C];
    virtual void V0();
    virtual void V1();
    virtual f32 Width(s32 c);
    virtual void Begin(s32 x, s32 y);
    virtual void Flush(s32 y);
    virtual f32 Draw(f32 left, f32 top, s32 c, s32 d, s32 y);
    virtual void End(s32 x, s32 y);
};
struct Line_15E318 { u8 pad[8]; s32 w; u8 pad2[0x3C]; f32 h; };
struct Self_15E318 {
    u8 pad0[8];
    Font_15E318* font;
    Line_15E318* line;
    u8 pad10[0x88];
    s32 f98;
    s32 f9c;
};
struct P_15E318 {
    f32 f0, f4, f8, fC;
    U4_15E318 f10;
    s32 f14;
    s32 f18;
};

void func_001F5C0C(void* p, s32 v, s32 n);
void func_0015DB80(Self_15E318* self);
s32 func_0015DBE0(Self_15E318* self);
void func_0015DBB8(Self_15E318* self, U4_15E318* p);

void func_0015E318(Self_15E318* self, P_15E318* p, s32 x, s32 y)
{
    f32 f[64];
    U4_15E318 u;
    s32 first = 1;
    s32 n = 0;
    f32 top;
    f32 left;
    s32 c;
    func_001F5C0C(f, 0, 0x100);
    func_0015DB80(self);
    while ((c = func_0015DBE0(self)) != 0) {
        if (c == 10) {
            n++;
        } else {
            f[n] += self->font->Width(c);
        }
    }
    c = p->f18;
    if (c == 0) {
        top = p->f4;
    } else {
        f32 tot = (f32)(n + 1) * ((f32)self->line->w * self->line->h);
        if (c == 2)
            top = (p->f4 + p->fC) - tot;
        else
            top = p->f4 + (p->fC - tot) * 0.5f;
    }
    u = p->f10;
    func_0015DBB8(self, &u);
    Font_15E318* started = 0;
    f32 half = 0.5f;
    func_0015DB80(self);
    s32 right = 2;
    f32* fp = f;
    while ((n = func_0015DBE0(self)) != 0) {
        if (n == 10) {
            first = 1;
            fp++;
            top += (f32)self->line->w * self->line->h;
            continue;
        }
        if (first) {
            if (p->f14 == 0) {
                left = p->f0;
            } else {
                f32 g = *fp;
                if (p->f14 == right)
                    left = (p->f0 + p->f8) - g;
                else
                    left = p->f0 + (p->f8 - g) * half;
            }
            first = 0;
        }
        if (started == 0) {
            self->font->Begin(x, y);
            started = self->font;
        } else if (self->f98 != 0) {
            self->font->Flush(y);
            self->f98 = 0;
        }
        left += self->font->Draw(left, top, n, self->f9c, y);
    }
    self->font->End(x, y);
}

// Inline text codes: ~RRGGBB / ~. colour, &<id> / &. font, ^<d><d> / ^. scale.
struct __attribute__((packed)) Col_15DBE0 { u8 r, g, b, a; };
struct Font_15DBE0 {
    u8 pad0[8];
    s32 f8;
    u8 pad0C[0x38];
    f32 f44;
    f32 f48;
};
struct Parser_15DBE0 {
    u8 pad0[4];
    char* cur;
    Font_15DBE0* font;
    Font_15DBE0* deffont;
    u8 inl[0x44];
    f32 f54;
    f32 f58;
    u8 pad5C[0x3C];
    s32 fontChanged;
    Col_15DBE0 c9C;
    Col_15DBE0 cA0;
    Col_15DBE0 cA4;
    Col_15DBE0 cA8;
};

s32 func_0015C200(s32 id);
void func_0015C9B0(Font_15DBE0* font, Font_15DBE0* out);
void func_0015C900(Font_15DBE0* font);
void func_0015C8B8(Font_15DBE0* font, f32 a, f32 b);

s32 func_0015DBE0(Parser_15DBE0* self)
{
    s32 done = 0;
    s32 changed = 1;
    Font_15DBE0* inl = (Font_15DBE0*)self->inl;
    do {
        char* p = self->cur;
        switch (*p) {
        case '~':
            if (p[1] == '~') {
                self->cur = p + 1;
                done = 1;
            } else if (p[1] == '.') {
                self->cA0 = self->cA4;
                self->c9C = self->cA0;
                self->cur += 2;
            } else {
                char* q = p + 1;
                u32 acc = 0;
                while (*q != 0 && q - self->cur < 7) {
                    u32 ch = (u8)*q;
                    u32 d;
                    if (ch - '0' < 10)
                        d = (s8)ch - '0';
                    else if (ch - 'A' < 6)
                        d = (s8)ch - 55;
                    else if (ch - 'a' < 6)
                        d = (s8)ch - 87;
                    else
                        break;
                    q++;
                    acc = (acc << 4) + d;
                }
                if (q - self->cur >= 7) {
                    self->cA0.r = ((acc >> 16) & 0xFF) + 1 >> 1;
                    self->cA0.g = ((acc & 0xFF00) >> 8) + 1 >> 1;
                    self->cA0.b = (acc & 0xFF) + 1 >> 1;
                    self->c9C = self->cA0;
                    self->cur += 7;
                } else {
                    self->font = self->deffont;
                    self->c9C = self->cA4;
                    done = 1;
                }
            }
            break;
        case '&':
            if (p[1] == '&') {
                self->cur = p + 1;
                done = 1;
            } else if (p[1] == '.') {
                self->font = self->deffont;
                self->c9C = self->cA0;
                self->fontChanged = changed;
                self->cur += 2;
            } else {
                Font_15DBE0* nf = (Font_15DBE0*)func_0015C200(p[1]);
                if (nf != 0) {
                    func_0015C9B0(nf, inl);
                    self->cur += 2;
                    Font_15DBE0* d = self->deffont;
                    f32 ratio = ((f32)d->f8 * d->f48) / ((f32)inl->f8 * inl->f48);
                    self->font = inl;
                    u8 al = self->c9C.a;
                    self->f54 *= ratio;
                    self->f58 *= ratio;
                    Col_15DBE0 t = self->cA8;
                    t.a = al;
                    self->c9C = t;
                    self->fontChanged = changed;
                } else {
                    self->font = self->deffont;
                    done = 1;
                    self->c9C = self->cA4;
                    self->fontChanged = changed;
                }
            }
            break;
        case '^':
            if (p[1] == '^') {
                self->cur = p + 1;
                done = 1;
            } else if (p[1] == '.') {
                func_0015C900(self->font);
                self->cur += 2;
            } else {
                f32 a = (f32)(p[1] - '0') + (f32)(p[2] - '0') * 0.1f;
                Font_15DBE0* f = self->font;
                func_0015C8B8(f, a * f->f44, a * f->f48);
                self->cur += 3;
            }
            break;
        default:
            done = 1;
            break;
        }
    } while (done == 0);
    char* e = self->cur;
    char r = *e;
    self->cur = e + 1;
    return r;
}

typedef void (*Fn_15D4E0)(void* at, s32 a, void* b);
struct Disp_15D4E0 {
    u8 pad[0x20];
    s16 offA;
    u8 padA[2];
    Fn_15D4E0 fnA;
    u8 padB[0x38 - 0x28];
    s16 offB;
    u8 padC[2];
    Fn_15D4E0 fnB;
};
struct Self_15D4E0 {
    u8 p0[8];
    s32 m8;
    u8 p0c[0x44 - 0x0C];
    f32 f44;
    f32 f48;
    Disp_15D4E0* disp;
    u8 p50[0x60 - 0x50];
    u64 m60;
};
struct Font_15D4E0;
struct Item_15D4E0 {
    Font_15D4E0* f0;
    s8 key;
    u8 p5[3];
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    u32 color;
};
struct Rect_15D4E0 { f32 x, y, w, h; };
struct Entry_15D4E0 { u8 p0[2]; u16 a2; u16 a4; u16 a6; };
struct Strm_15D4E0 { u8 pad[4]; };

Entry_15D4E0* func_0015DAB8(Self_15D4E0* self, s8 key);
void func_0015C8B8(Font_15D4E0* p, f32 a, f32 b);
void func_0015C900(Font_15D4E0* p);
void func_0015D338(Self_15D4E0* self, u32 color, f32 x0, f32 y0, f32 x1, f32 y1,
                   f32 u0, f32 v0, f32 u1, f32 v1, Strm_15D4E0* s);

void func_0015D4E0(Self_15D4E0* self, Item_15D4E0* item, Rect_15D4E0* r, Strm_15D4E0* s)
{
    Entry_15D4E0* e = func_0015DAB8(self, item->key);
    if (e != 0) {
        func_0015C8B8(item->f0, item->f10, item->f14);
        f32 top = r->y;
        f32 sx = self->f44;
        f32 left = r->x;
        s32 u2i = e->a2 + e->a6;
        f32 x2 = left + r->w + item->f8 * sx;
        f32 cw = (f32)e->a6 * sx;
        f32 x1 = left - item->f8 * sx;
        s32 sz = 1 << (s32)((self->m60 >> 30) & 0xF);
        s32 height = self->m8;
        f32 sy = self->f48;
        s32 v0i = sz - e->a4;
        f32 x0 = x1 - cw;
        s32 v2i = sz - (e->a4 + height);
        f32 u1 = (f32)((e->a2 + u2i) / 2);
        f32 v1 = (f32)((v0i + v2i) / 2);
        f32 u0 = (f32)e->a2;
        f32 y1 = top - item->fC * sy;
        f32 v0 = (f32)v0i;
        f32 x3 = x2 + cw;
        f32 y2 = top + r->h + item->fC * sy;
        f32 y0 = y1 - (f32)height * sy;
        f32 y3 = y2 + (f32)height * sy;
        self->disp->fnA((u8*)self + self->disp->offA, 0, s);
        f32 v2 = (f32)v2i;
        f32 u2 = (f32)u2i;
        func_0015D338(self, item->color, x0, y0, x1, y1, u0, v0, u1, v1, s);
        func_0015D338(self, item->color, x2, y0, x3, y1, u1, v0, u2, v1, s);
        func_0015D338(self, item->color, x0, y2, x1, y3, u0, v1, u1, v2, s);
        func_0015D338(self, item->color, x2, y2, x3, y3, u1, v1, u2, v2, s);
        func_0015D338(self, item->color, x1, y0, x2, y1, u1, v0, u1, v1, s);
        func_0015D338(self, item->color, x1, y2, x2, y3, u1, v1, u1, v2, s);
        func_0015D338(self, item->color, x0, y1, x1, y2, u0, v1, u1, v1, s);
        func_0015D338(self, item->color, x2, y1, x3, y2, u1, v1, u2, v1, s);
        func_0015D338(self, item->color, x1, y1, x2, y2, u1, v1, u1, v1, s);
        func_0015C900(item->f0);
        self->disp->fnB((u8*)self + self->disp->offB, 0, s);
    }
}

void* D_0026231C = 0;
void* D_002623B0 = 0;
volatile s32 D_002623B8 = 0;
