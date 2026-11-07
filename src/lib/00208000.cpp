// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

// SPDX-License-Identifier: AGPL-3.0-or-later

#include "common.h"

s32 func_0020B048(void) {
	return 1;
}

struct Device_20B0B0 {
	u8 padding[0x40];
	void* state;
};

s32 func_0020B0B0(Device_20B0B0* device) {
	return *(s32*)device->state;
}

struct Device_20B110 {
	u8 padding[0x40];
	u8* state;
};

struct DeviceState_20B110 {
	u8 padding[0x1B8];
	void* a;
	void* d;
	u8 padding2[8];
	void* b;
	void* e;
	u8 padding3[8];
	void* c;
	void* f;
};

s32 func_0020B110(Device_20B110* device) {
	DeviceState_20B110* state = (DeviceState_20B110*)device->state;
	if (state->a) *(s32*)((char*)state->a + 0x28) = 0;
	if (state->b) *(s32*)((char*)state->b + 0x28) = 0;
	if (state->c) *(s32*)((char*)state->c + 0x28) = 0;
	if (state->d) *(s32*)((char*)state->d + 0x28) = 0;
	if (state->e) *(s32*)((char*)state->e + 0x28) = 0;
	if (state->f) *(s32*)((char*)state->f + 0x28) = 0;
	return 1;
}

struct Field_20B258 {
	u8 padding[8];
	s32 f8;
	s32 fc;
};

s32 func_0020B258(Field_20B258* field) {
	return field->fc = field->f8;
}

struct Obj_20B168 { u8 pad[0x40]; u32* values; };

s32 func_0020B168(Obj_20B168* obj, s32 index, s32 value, s32 second)
{
    u32* array = obj->values;
    u32* current = array + 3;
    u32 offset = index * 2;
    current += offset;
    array += offset;
    array[4] = second;
    s32 old = *current;
    *current = value;
    return old;
}

struct Item_20B240 { s32 a; s32 b; s32 c; s32 d; };
void func_0020B240(Item_20B240* item, s32 value, s32 field)
{
    item->a = value;
    item->b = field;
    item->c = value;
    item->d = value;
}

s32 func_0020B268(s32* item)
{
    s32 value = item[3];
    item[2] = value;
    return value;
}

struct Item_20B9D0 { u8 pad[4]; s32 x; s32 y; s32 left; s32 top; };
s32 func_0020B9D0(Item_20B9D0* item, s32 x, s32 y)
{
    item->x = x;
    item->y = y;
    item->left = x >> 4;
    item->top = y >> 4;
    return 1;
}

// NEAR: the body matches; retail saves s0, s1 and ra with 8-byte sd/ld, the default 2.95.3 build with 16-byte sq/lq (PAL differs too)

struct Inner_20B718 {
    u8 pad0[4];
    s32 a;
    s32 b;
    u8 pad1[0xA0];
    s32 c;
    u8 pad2[0x68];
    s32 d;
};

struct Obj_20B718 {
    u8 pad0[8];
    s32 out;
    u8 pad1[0x34];
    Inner_20B718* inner;
};

extern void func_0020B790(Inner_20B718* self);

s32 func_0020B718(Obj_20B718* self)
{
    s32 r = 0;
    Inner_20B718* in = self->inner;

    if (in->a != 0) {
        if (in->b != 0) {
            func_0020B790(in);
            self->out = in->d - in->c;
            in->a = 0;
            r = 1;
        }
    }
    return r;
}

// NEAR: only the s0 and ra saves and restores differ (ours sq/lq, retail sd/ld)

struct Buf_0020B940;
struct Ctx_0020B940;
s32 func_001E1FD0(Buf_0020B940* dst, const char* fmt, ...);
s32 func_0020B978(Ctx_0020B940* self, char* buf);

void func_0020B940(Ctx_0020B940* self, const char* fmt)
{
    char buf[0x100];
    FormatToString((Buf_0020B940*)buf, fmt);
    func_0020B978(self, buf);
}

// NEAR: retail saves $ra with sd (8 bytes) and reloads with ld; SN GCC 2.95.3 saves it with sq. Body otherwise matches.

struct Self_20B978 {
    u8 pad0[0xC];
    s32 f0C;
    u8 pad1[0x848];
    void* f858;
};

struct Pair_20B978 {
    s32 a;
    s32 b;
};

struct Sub_20B978;
struct Arg_20B978;

s32 func_0020B190(Sub_20B978* sub, Pair_20B978* pair);
s32 func_0020B930(Arg_20B978* arg);

s32 func_0020B978(Self_20B978* self, s32 value)
{
    Pair_20B978 pair;

    if (self->f858 != 0 && self != 0 && self->f0C != 0) {
        pair.a = 0;
        pair.b = value;
        return func_0020B190((Sub_20B978*)self->f858, &pair);
    }
    return func_0020B930((Arg_20B978*)value);
}

// NEAR: retail saves $ra and $s0-$s5 with sd (8 bytes), not the 16-byte sq of this compiler; the body is otherwise identical.
extern const char D_00250160[];
extern const char D_00250188[];

struct Obj_20BF78 {
    u8 pad0[0x124];
    u32 field124;
    u32 field128;
    u8 pad12C[0x8];
    u32 field134;
    u32 field138;
    u32 field13C;
    u32 field140;
    u8 pad144[0x704];
    u32 field848;
};

u32 func_0020DEE8(u32 value);
u32 func_0020F5B8(struct Obj_20BF78 *self, u32 n);
s32 func_0020B978(struct Obj_20BF78 *self, const void *p);

void func_0020BF78(struct Obj_20BF78 *self)
{
    u32 s2;
    u32 s0;
    u32 s3;
    u32 s4;
    u32 s5;

    self->field848 = 1;
    func_0020DEE8(0);
    s2 = func_0020F5B8(self, 0x1C);
    s5 = (s2 >> 1) & 0xFFF;
    self->field140 = (s2 >> 17) & 3;
    s4 = (s2 >> 13) & 3;
    s3 = (s2 >> 15) & 3;
    if (self->field140 != 1) {
        func_0020B978(self, D_00250160);
    }
    self->field13C = (s2 >> 19) & 1;
    s0 = s2 >> 20;
    s2 = func_0020F5B8(self, 0x10) >> 8;
    if (s0 != 0x48 && s0 != 0x58 && s0 != 0x44) {
        func_0020B978(self, D_00250188);
    }
    self->field124 = (s3 << 12) | (self->field124 & 0xFFF);
    self->field128 = (s4 << 12) | (self->field128 & 0xFFF);
    self->field134 += s5 << 18;
    self->field138 += s2 << 10;
}

struct Obj_20B058 { u8 pad[0x40]; u8* state; };

s32 func_0020B2E8(Obj_20B058* obj);

s32 func_0020B058(Obj_20B058* obj, u32 a1, s32 a2)
{
    u8* st = obj->state;
    *(s32*)(st + 0xB0) = 1;
    *(u32*)(st + 0xD8) = (a1 & 0xFFFFFFFu) | 0x20000000u;
    *(s32*)(st + 0xE4) = a2;
    *(s32*)(st + 0xE0) = 0;
    *(s32*)(st + 0xDC) = 0;
    return func_0020B2E8(obj);
}

struct Q_0020B1E0;
s32 func_0020B190(Q_0020B1E0* q, s32* out);

s32 func_0020B1E0(Q_0020B1E0* q)
{
    s32 flag[8];
    flag[0] = 1;
    return func_0020B190(q, flag);
}

struct Owner_0020B278;

struct Pool_0020B278 {
    u32 f00;
    u32 f04;
    u32 f08;
};

extern const char D_00250098[];

s32 func_0020B978(Owner_0020B278* owner, const char* p);

s32 func_0020B278(Owner_0020B278* owner, Pool_0020B278* pool, u32 offset, u32 align)
{
    u32 base;
    u32 end;

    base = (pool->f08 + align - 1) / align;
    base = base * align;
    end = base + offset;
    if (pool->f00 + pool->f04 >= end) {
        pool->f08 = end;
        return base;
    }
    (void)func_0020B978(owner, D_00250098);
    return 0;
}

struct Ctx_0020B190;
typedef s32 (*Fn_0020B190)(Ctx_0020B190*, s32*, s32);
struct Ent_0020B190 { Fn_0020B190 fn; s32 arg; };
struct Tab_0020B190 { u8 pad[0xC]; Ent_0020B190 e[1]; };
struct Ctx_0020B190 { u8 pad[0x40]; Tab_0020B190* table; };
s32 func_0020B190(Ctx_0020B190* p, s32* idx) {
    s32 r = 0;
    if (p != 0) {
        Tab_0020B190* t = p->table;
        if (t != 0) {
            Fn_0020B190 fn = t->e[*idx].fn;
            if (fn != 0) {
                r = fn(p, idx, t->e[*idx].arg);
            }
        }
    }
    return r;
}

struct Sub_20B5B8 {
    s32 f0;
    s32 f4;
    s32 f8;
    u8 pad0C[0xA0];
    s32 fAC;
    u8 pad1[0x24];
    s32 fD4;
    u8 pad2[0x40];
    s32 f118;
    s32 f11C;
    s32 f120;
    u8 pad3[0x50];
    s32 f174;
};

struct Ctx_20B5B8 {
    u8 pad0[0x8];
    s32 f8;
    u8 pad1[0x34];
    Sub_20B5B8* sub;
};

s32 func_002101F0(Sub_20B5B8* sub, s32 flag);
s32 func_00210090(Sub_20B5B8* sub);
s32 func_0020F7F0(Sub_20B5B8* sub);
s32 func_0020B718(Ctx_20B5B8* ctx);
void func_00210160(Sub_20B5B8* sub, s32 a1, s32 a2);
s32 func_0020B1E0(Ctx_20B5B8* ctx);

s32 func_0020B5B8(Ctx_20B5B8* self, s32 a1, s32 a2)
{
    s32 s3 = 0;
    Sub_20B5B8* s0;
    s32 s1;
    s32 s4;
    s32 t;
    s32 r;

    s0 = self->sub;
    s0->f120 = 0;
    if (a2 == -1 || a1 < a2) {
        s3 = 1;
    }
    if (s0->f8 == 0) {
        self->f8 = 0;
        s0->f8 = 1;
    }
    if (func_002101F0(s0, 0) != 0) {
        if (s3 != 0) {
            (void)func_00210090(s0);
        }
    }
    s1 = 1;
    s0->f120 = s1;
    if (func_0020F7F0(s0) == 0) {
        (void)func_0020B718(self);
        s0->f0 = s1;
        return 0;
    }
    t = (s0->fD4 ^ 1) != 0 ? s1 : 2;
    if (s0->f174 != t) {
        return -1;
    }
    r = func_002101F0(s0, 1);
    s32 u = 0;
    if (r != 0) {
        u = s1;
    }
    s4 = 0;
    if (u != 0) {
        if (s3 != 0) {
            s4 = (func_00210090(s0) != 0) ? s1 : 0;
        }
    }
    func_00210160(s0, s0->f118, s0->f4);
    s0->f120 = 0;
    self->f8 = s0->f118 - s0->fAC;
    s0->f118 = s0->f118 + 1;
    s0->f4 = s0->f4 + 1;
    if (s3 == 0) {
        func_0020B1E0(self);
    }
    return s4;
}

struct Ctx_20B2E8 {
    s32 f0;
    u8 pad0[0x94 - 4];
    s32 f94, f98, f9C, fA0, fA4, fA8;
    u8 pad1[0xD4 - 0xAC];
    s32 fD4;
    s32 fD8;
    u8 pad2[0x174 - 0xDC];
    s32 f174;
    u8 pad3[0x820 - 0x178];
    s32 f820;
    u8 pad4[0x848 - 0x824];
    s32 f848;
};
struct Self_20B2E8 { u8 pad[0x40]; Ctx_20B2E8* ctx; };

void func_0020B940(Ctx_20B2E8* c, s32 msg, s32 flags);
s32 func_0020F7F0(Ctx_20B2E8* c);
s32 func_0020B570(Self_20B2E8* self, s32 a, s32 b);
s32 func_0020B718(Self_20B2E8* self);
extern const char D_002500B8[];

s32 func_0020B2E8(Self_20B2E8* self)
{
    s32 s3 = 1;
    s32 s2 = 0;
    Ctx_20B2E8* c = self->ctx;
    c->f0 = 0;
    if ((c->fD8 & 0x3F) != 0) {
        func_0020B940(c, (s32)D_002500B8, c->fD8);
        return -1;
    }
    c->f820 = 0;
    for (;;) {
        if (s2 != -1) {
            do {
                s3 = func_0020F7F0(c);
                if (s3 == 0) break;
                if (c->f174 == c->fD4) break;
            } while (c->f848 != 0);
        }
        switch (s3) {
        case 0:
            (void)func_0020B718(self);
            c->f0 = 1; 
            break;
        case 1:
            c->fA8 = 0;
            c->fA4 = 0;
            c->fA0 = 0;
            s2 = func_0020B570(self, 0, c->f94);
            c->fA0++;
            break;
        case 2:
            s2 = func_0020B570(self, c->fA4, c->f98);
            c->fA4++;
            break;
        case 3:
        case 4:
            s2 = func_0020B570(self, c->fA8, c->f9C);
            c->fA8++;
            break;
        }
        if (c->f820 != 0 || c->f0 != 0) break;
    }
    return 1;
}

struct Outer_20AE40 {
    s32 f0; s32 f4; s32 f8; s32 pad0C;
    s64 f10; s64 f18; s64 f20; s64 f28; s64 f30; s64 f38;
    s32 f40;
};
struct Plane_20AE40 { u8 data[0x68]; };
struct Ring_20AE40 { u8* start; u32 size; u8* head; u8* tail; };
struct Inner_20AE40 {
    s32 f00; s32 f04; s32 f08; s32 f0C; s32 f10; s32 f14; s32 f18; s32 f1C;
    s32 f20; s32 f24; s32 f28; s32 f2C; s32 f30; s32 f34; s32 f38; s32 f3C;
    s32 f40; s32 f44; s32 f48; s32 f4C; s32 f50; s32 f54; s32 f58; s32 f5C;
    s32 f60; s32 f64; s32 f68; s32 f6C; s32 f70; s32 pad74; s64 f78; s32 f80; s32 pad84;
    s64 f88; s32 f90; s32 f94; s32 f98; s32 f9C; s32 fA0; s32 fA4; s32 fA8; s32 fAC;
    s32 fB0; s32 fB4; s32 fB8; s32 fBC; s32 fC0; s32 fC4; s32 fC8; s32 fCC;
    s32 fD0; s32 fD4; s32 fD8; s32 fDC; s32 fE0; s32 fE4; s32 fE8; s32 fEC;
    s64 fF0; s32 fF8; s32 fFC; s32 f100; s32 f104;
    Ring_20AE40 ring;
    u8 pad118[0x1B8 - 0x118];
    Plane_20AE40* planes[3][4];
    Plane_20AE40 plane[9];
    u8 pad590[0x81C - 0x590];
    s32 f81C;
    u8 pad820[0x84C - 0x820];
    s32 f84C;
    s32 f850;
    s32 f854;
    Outer_20AE40* f858;
};

void* func_001F5C0C(s32 dst, s32 c, u32 n);
s32 func_0020B978(Inner_20AE40* a, const char* msg);
void func_0020B240(Ring_20AE40* r, u8* start, u32 size);
s32 func_0020B278(Inner_20AE40* a, Ring_20AE40* r, u32 size, u32 align);
void func_0020B810(Inner_20AE40* a);
void func_0020B0C0(Outer_20AE40* a);
s32 func_0020B110(Outer_20AE40* a);
void func_0020B258(Ring_20AE40* r);
void func_0020C178(void);
void func_0020C188(void);

s32 func_0020AE40(Outer_20AE40* out, s32 mem, u32 size)
{
    func_001F5C0C(mem, 0, size);
    Inner_20AE40* in = (Inner_20AE40*)(((u32)(mem + 3) >> 2) << 2);
    s32 diff = (s32)in - mem;
    u32 rest = size - diff;
    if (rest < 0x10C0) {
        func_0020B978(in, "The size of work area is too small");
        return 0;
    }
    out->f40 = (s32)in;
    rest -= 0x10C0;
    func_0020B240(&in->ring, (u8*)in + 0x10C0, rest);
    out->f0 = 0;
    out->f4 = 0;
    out->f8 = 0;
    out->f10 = -1;
    out->f18 = -1;
    out->f20 = 0;
    out->f28 = -1;
    out->f30 = -1;
    out->f38 = 0;
    in->fB4 = 0;
    in->fB8 = 0;
    in->fBC = 0;
    in->fC0 = 0;
    in->fC4 = 0;
    in->fC8 = 0;
    in->fCC = 0;
    in->fD0 = 0;
    in->fD4 = 0;
    in->fD8 = 0;
    in->fDC = 0;
    in->fE0 = 0;
    in->fE4 = 0;
    in->fE8 = 0;
    in->fF8 = 0;
    in->f0C = 0;
    in->f14 = 0;
    in->f2C = 0;
    in->f34 = 0;
    in->f3C = 0;
    in->fF0 = -1;
    in->f1C = (s32)func_0020C178;
    in->f24 = (s32)func_0020C188;
    s32 r278 = func_0020B278(in, &in->ring, 0x600, 8);
    in->f48 = 0;
    in->fFC = 0;
    in->f100 = 0;
    in->f104 = 0;
    in->f70 = 0;
    in->f78 = 0;
    in->f80 = -1;
    in->f88 = 0;
    in->f90 = 0;
    in->fAC = 0;
    in->f94 = -1;
    in->f98 = -1;
    in->f9C = -1;
    in->f858 = out;
    in->f44 = r278;
    in->fB0 = 1;
    func_0020B810(in);
    func_0020B0C0(out);
    func_0020B110(out);
    in->planes[0][0] = &in->plane[0];
    in->planes[0][1] = &in->plane[1];
    in->planes[0][3] = &in->plane[2];
    in->planes[1][0] = &in->plane[3];
    in->planes[1][1] = &in->plane[4];
    in->planes[1][3] = &in->plane[5];
    in->planes[2][0] = &in->plane[6];
    in->planes[2][1] = &in->plane[7];
    in->planes[2][3] = &in->plane[8];
    func_0020B258(&in->ring);
    in->f850 = -1;
    in->f854 = 0;
    in->f84C = 0;
    in->f81C = 0x70003600;
}

struct Obj_0020B790 {
    u8 pad000[0x118];
    s32 f118;
    s32 f11C;
    s32 f120;
    u8 pad124[0x174 - 0x124];
    s32 f174;
    u8 pad178[0x1BC - 0x178];
    s32 f1BC;
    u8 pad1C0[0x1CC - 0x1C0];
    s32 f1CC;
    u8 pad1D0[0x1DC - 0x1D0];
    s32 f1DC;
};

s32 func_0020B978(struct Obj_0020B790 *self, const char *msg);
void func_00210970(struct Obj_0020B790 *self, s32 a1, s32 a2);
void func_00210A80(struct Obj_0020B790 *self, s32 a1, s32 a2, s32 a3);

void func_0020B790(struct Obj_0020B790 *self)
{
    s32 n = self->f118;
    if (self->f120 != 0)
        func_0020B978(self, "the second field is missing");
    else if (self->f174 == 3)
        func_00210970(self, self->f1BC, n - 1);
    else
        func_00210A80(self, self->f1CC, self->f1DC, n - 1);
    self->f120 = 0;
}

void func_0020B780(void* s);
void func_0020B870(void* s);
struct S_20B0C0 { u8 pad0[8]; s32 f8; u8 pad[0x34]; u8* st; };
void func_0020B0C0(S_20B0C0* d) {
    u8* s = d->st;
    *(s32*)s = 0;
    *(s32*)(s + 4) = 0;
    *(s32*)(s + 8) = 0;
    d->f8 = 0;
    *(s32*)(s + 0xAC) = 0;
    *(s32*)(s + 0x80) = -1;
    func_0020B870(s);
    *(s32*)(s + 0x118) = 0;
    func_0020B780(s);
}

void func_0020DEE8(s32 a);
struct S_20B780 { u8 pad[0x848]; s32 f; };
void func_0020B780(S_20B780* s) {
    s->f = 0;
    func_0020DEE8(1);
}

s32 func_001E1F10(const char* fmt, s32 msg);

void func_0020B930(s32 msg) {
    PrintFormatted("[MPEG ERROR]%s\n", msg);
}

struct Dec_20B9F0 {
    u8 pad0[0xD4];
    s32 fD4;
    u8 pad1[0x124 - 0xD8];
    u32 f124;
    s32 f128;
    u8 pad2[0x134 - 0x12C];
    u32 f134;
    u32 f138;
    u8 pad3[0x840 - 0x13C];
    u32 f840;
    u32 f844;
    u8 pad4[0x858 - 0x848];
    void* f858;
};

extern u8 D_0027AF80[64];
extern u8 D_0027AFC0[64];

u32 func_0020F5B8(Dec_20B9F0* d, s32 bits);
s32 func_0020B978(Dec_20B9F0* d, const char* msg);
void func_0020F0F0(Dec_20B9F0* d);
void func_0020F0C0(Dec_20B9F0* d, u32 value);
void func_0020BEA0(Dec_20B9F0* d, u32 value, u8* table);
void func_0020F9C8(Dec_20B9F0* d);
void func_0020BB18(void* p);

void func_0020B9F0(Dec_20B9F0* d) {
    d->fD4 = 0;
    u32 v = func_0020F5B8(d, 0x20);
    d->f124 = v >> 20;
    d->f128 = (v >> 8) & 0xFFF;
    if (d->f128 > 0xAF0) {
        func_0020B978(d, "vertical size > 2800");
    }
    v = func_0020F5B8(d, 0x1E);
    d->f134 = v >> 12;
    d->f138 = (v >> 1) & 0x3FF;
    d->f840 = func_0020F5B8(d, 1);
    if (d->f840) {
        func_0020F0F0(d);
        func_0020F0C0(d, 0x50000000);
        func_0020F0F0(d);
    } else {
        func_0020BEA0(d, 0x50000000, D_0027AF80);
    }
    d->f844 = func_0020F5B8(d, 1);
    if (d->f844) {
        func_0020F0F0(d);
        func_0020F0C0(d, 0x58000000);
        func_0020F0F0(d);
    } else {
        func_0020BEA0(d, 0x58000000, D_0027AFC0);
    }
    func_0020F9C8(d);
    func_0020BB18(d->f858);
}

s32 func_001F9D60(void);
s32 func_001F9DA8(void);
void func_00211BA8(void);

void func_0020ADA0(void) {
    func_001F9D60();
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
    *(volatile u32*)0x1000B000 &= 0xFFFFFEFF;
    *(volatile u32*)0x1000B400 &= 0xFFFFFEFF;
    *(u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
    func_001F9DA8();
    *(volatile u32*)0x1000B020 = 0;
    *(volatile u32*)0x1000B420 = 0;
    func_00211BA8();
}

s32 func_001F9D60(void);
s32 func_001F9DA8(void);
u32 func_00211AD8(s32 a, s32 b);

struct Chan_20B870 {
    u8 pad0[0x1B0];
    s32 f1B0;
    u8 pad1[0x818 - 0x1B4];
    s32 f818;
};

void func_0020B870(Chan_20B870* c) {
    c->f818 = 1;
    c->f1B0 = 0;
    func_001F9D60();
    *(volatile u32*)0x1000F590 = *(volatile u32*)0x1000F520 | 0x10000;
    *(volatile u32*)0x1000B000 = 0;
    *(volatile u32*)0x1000B400 = 0;
    *(volatile u32*)0x1000D400 = 0;
    *(u32*)0x1000F590 = *(volatile u32*)0x1000F520 & 0xFFFEFFFF;
    func_001F9DA8();
    *(volatile u32*)0x1000B020 = 0;
    *(volatile u32*)0x1000B420 = 0;
    *(volatile u32*)0x1000D420 = 0;
    *(volatile u32*)0x10002010 = 0x40000000;
    func_00211AD8(0, 0);
}

struct Child_0020B570 { u8 pad[0x174]; s32 kind; };
struct Owner_0020B570 {
    u8 pad[0x40];
    Child_0020B570* child;
};

s32 func_0020B458(Owner_0020B570* self, s32 a, s32 b);
s32 func_0020B5B8(Owner_0020B570* self, s32 a, s32 b);

s32 func_0020B570(Owner_0020B570* self, s32 a, s32 b)
{
    if (self->child->kind != 3) {
        return func_0020B5B8(self, a, b);
    }
    return func_0020B458(self, a, b);
}

struct Dev_20B810 {
    u8 pad0[0x590];
    u8* f590;
    u8* f594;
    u8 pad1[0x6D0 - 0x598];
    u8* f6D0;
    u8* f6D4;
    u8 pad2[0x810 - 0x6D8];
    u32 f810;
};

void func_0020DEE8(s32 a);

void func_0020B810(Dev_20B810* self)
{
    u8* spr = (u8*)0x70000000;
    func_0020DEE8(1);
    self->f590 = spr;
    self->f594 = spr + 0x1800;
    self->f6D0 = spr + 0x1B00;
    self->f6D4 = spr + 0x3300;
    self->f810 = 0;
}

void func_0020BDC0(u32* a0, u32* a1, u32* a2, u32* a3, u32* a4, u32* a5, u32* a6, u32* a7, u32* p9, u32 p10, u32 p11, u32 p12, s32 p13, s32 p14)
{
    u32 mask = 0x0FFFFFFF;
    u32 bits = 0x20000000;
    s32 n = (p13 * p14) / 512;
    *a0 = (p10 & mask) | bits;
    *a1 = (p11 & mask) | bits;
    *a2 = (p12 & mask) | bits;
    *a3 = (p10 & mask) | bits;
    *a4 = (p11 & mask) | bits;
    *a5 = (p12 & mask) | bits;
    u32 y2 = n * 0x180;
    y2 = ((y2 + p10) & mask) | bits;
    u32 u2 = n * 0x180;
    u2 = ((u2 + p11) & mask) | bits;
    u32 v2 = n * 0x180;
    v2 = ((v2 + p12) & mask) | bits;
    *a6 = y2;
    *a7 = u2;
    *p9 = v2;
}

struct Ent_20B458 {
    u8 pad0[0x4];
    s32 f4;
    s32 f8;
    u8 pad1[0xAC - 0xC];
    s32 fAC;
    u8 pad2[0x118 - 0xB0];
    s32 f118;
    s32 f11C;
    s32 f120;
    u8 pad3[0x174 - 0x124];
    s32 f174;
};
struct Ctx_20B458 {
    u8 pad0[0x8];
    s32 f8;
    u8 pad1[0x40 - 0xC];
    Ent_20B458* f40;
};
struct Ent_arg_20B458 { u32 v; };

extern s32 func_002101F0(Ent_20B458* e, u32 a1);
extern s32 func_00210090(Ent_20B458* e);
extern void func_00210160(Ent_20B458* e, s32 a1, s32 a2);
extern s32 func_0020B1E0(Ctx_20B458* c);

struct Ent_ops_20B458 {
    static s8 Ready(Ent_20B458* e)
    {
        s32 t = func_002101F0(e, 0);
        s8 r = 0;
        if (t != 0) {
            r = func_00210090(e) != 0;
        }
        return r;
    }
};

s32 func_0020B458(Ctx_20B458* s1, s32 a1, s32 a2)
{
    s32 s2;
    Ent_20B458* s0 = s1->f40;
    s32 s3 = 0;

    if (a2 == -1 || a1 < a2) {
        if (s0->f8 == 0) {
            s1->f8 = 0;
            s0->f8 = 1;
        }
        s2 = Ent_ops_20B458::Ready(s0);
    } else {
        s2 = func_002101F0(s0, 0);
        s3 = 1;
        (void)func_0020B1E0(s1);
    }
    func_00210160(s0, s0->f118, s0->f4);
    if (s0->f174 == 3) {
        ;
    } else if (s3 == 0) {
        s0->f120 = (s0->f120 == 0);
    }
    s1->f8 = s0->f118 - s0->fAC;
    if (s0->f120 == 0) {
        s0->f118 = s0->f118 + 1;
        s0->f4 = s0->f4 + 1;
    }
    return s2;
}

struct Obj_20BEA0 { u8 pad000[0x858]; u32 field858; };
struct Handle_20BEA0;
struct Req_20BEA0 { s32 mode; s32 pad[7]; };
s32 func_0020B190(Handle_20BEA0* h, Req_20BEA0* out);
void func_0020F0F0(Obj_20BEA0* self);
void func_0020F0C0(Obj_20BEA0* self, u32 value);
s32 func_001F9D60(void);
s32 func_001F9DA8(void);

void func_0020BEA0(Obj_20BEA0* obj, u32 value, u32 mask)
{
    Req_20BEA0 req;
    req.mode = 2;

    func_0020B190((Handle_20BEA0*)obj->field858, &req);
    func_0020F0F0(obj);
    *(volatile u32*)0x10002000 = 0;
    func_0020F0F0(obj);
    (void)func_001F9D60();
    *(volatile u32*)0x1000B410 = mask & 0x0FFFFFFF;
    *(volatile u32*)0x1000B420 = 4;
    *(volatile u32*)0x1000B400 = 0x101;
    (void)func_001F9DA8();
    func_0020F0C0(obj, value);
    func_0020F0F0(obj);
    req.mode = 3;
    func_0020B190((Handle_20BEA0*)obj->field858, &req);
}

extern const char D_00250070[40] = "The size of work area is too small";
extern const char D_00250098[32] = "work area size is too small";
extern const char D_002500B8[72] = "image buffer needs to be aligned to 64byte boundary(0x%08x)";
extern const char D_00250118[32] = "the second field is missing";
extern const char D_00250138[16] = "[MPEG ERROR]%s\n";
extern const char D_00250148[24] = "vertical size > 2800";
extern const char D_00250160[40] = "_chroma_format needs to be 1: 420";
extern const char D_00250188[32] = "Unsupported profile/level";
u8 D_0027AF80[64] = { 0x08, 0x10, 0x10, 0x13, 0x10, 0x13, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x1a, 0x18, 0x1a, 0x1b, 0x1b, 0x1b, 0x1a, 0x1a, 0x1a, 0x1a, 0x1b, 0x1b, 0x1b, 0x1d, 0x1d, 0x1d, 0x22, 0x22, 0x22, 0x1d, 0x1d, 0x1d, 0x1b, 0x1b, 0x1d, 0x1d, 0x20, 0x20, 0x22, 0x22, 0x25, 0x26, 0x25, 0x23, 0x23, 0x22, 0x23, 0x26, 0x26, 0x28, 0x28, 0x28, 0x30, 0x30, 0x2e, 0x2e, 0x38, 0x38, 0x3a, 0x45, 0x45, 0x53 };
u8 D_0027AFC0[64] = { 16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
