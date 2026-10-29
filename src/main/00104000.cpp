// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Quad_105020 { s32 a, b, c, d; };
struct Frame_105020 { Quad_105020 q; Quad_105020 t; s32 n; s32 out; };

void func_0011B008(Quad_105020* q);
void func_0011B018(void* dst, Quad_105020* src);
void func_0011B060(Quad_105020* q, int mode);
void func_0011B0A8(Quad_105020* a, Quad_105020* b);
s32 func_0011B8A8(Quad_105020* q, s32 v);
void func_001C23B0(Quad_105020* t, int mode, int c, void* z, void* z2);
s32 func_001CA6D0(void* obj, s32 v);

void* func_00105020(void* self, void* x, int unused, int c)
{
    Frame_105020 f;
    func_0011B008(&f.q);
    f.n = 0x1000;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_0011B8A8(&f.q, func_001CA6D0(x, f.out));
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_105CC0 { s32 a, b, c, d; };
struct Frame_105CC0 { Quad_105CC0 q; Quad_105CC0 t; };

void func_0011B008(Quad_105CC0* q);
void func_0011B018(void* dst, Quad_105CC0* src);
void func_0011B060(Quad_105CC0* q, int mode);
void func_0011B0A8(Quad_105CC0* a, Quad_105CC0* b);
void func_0011B538(Quad_105CC0* q, int n);
void func_001C23B0(Quad_105CC0* t, int mode, int c, void* z);
void func_001D6CB0(void* obj);

void* func_00105CC0(void* self, void* x, int unused, int c)
{
    Frame_105CC0 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001D6CB0(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_105D60 { s32 a, b, c, d; };
struct Frame_105D60 { Quad_105D60 q; Quad_105D60 t; s32 n; s32 out; };

void func_0011B008(Quad_105D60* q);
void func_0011B018(void* dst, Quad_105D60* src);
void func_0011B060(Quad_105D60* q, int mode);
void func_0011B0A8(Quad_105D60* a, Quad_105D60* b);
void func_0011B538(Quad_105D60* q, int n);
void func_001C23B0(Quad_105D60* t, int mode, int c, void* z, void* z2);
s32 func_001781E0(void* obj, s32 v);

void* func_00105D60(void* self, void* x, int unused, int c)
{
    Frame_105D60 f;
    func_0011B008(&f.q);
    f.n = 0x2000;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_001781E0(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_105E10 { s32 a, b, c, d; };
struct Frame_105E10 { Quad_105E10 q; Quad_105E10 t; s32 n; s32 out; };

void func_0011B008(Quad_105E10* q);
void func_0011B018(void* dst, Quad_105E10* src);
void func_0011B060(Quad_105E10* q, int mode);
void func_0011B0A8(Quad_105E10* a, Quad_105E10* b);
void func_0011B538(Quad_105E10* q, int n);
void func_001C23B0(Quad_105E10* t, int mode, int c, void* z, void* z2);
s32 func_00178258(void* obj, s32 v);

void* func_00105E10(void* self, void* x, int unused, int c)
{
    Frame_105E10 f;
    func_0011B008(&f.q);
    f.n = 0x2000;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_00178258(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct State_107350;
struct Handle_107350 { s32 id; s32 aux; };

void func_0011B008(Handle_107350* h);
void func_0011B018(Handle_107350* dst, Handle_107350* src);
void func_0011B060(Handle_107350* h, s32 mode);
void func_0011B0A8(Handle_107350* dst, Handle_107350* src);
void func_0011B538(Handle_107350* h, s32 id);
void func_001C23B0(Handle_107350* t, s32 n, void* c, void* d, ...);
void func_0018AC58(State_107350* st);

Handle_107350* func_00107350(Handle_107350* ret, State_107350* st, void* unused, void* c)
{
    Handle_107350 h;
    Handle_107350 t;
    func_0011B008(&h);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&h, &t);
    func_0011B060(&t, 2);
    func_0018AC58(st);
    func_0011B538(&h, 0x22);
    func_0011B018(ret, &h);
    func_0011B060(&h, 2);
    return ret;
}

struct State_107678;
struct Handle_107678 { s32 id; s32 aux; };

void func_0011B008(Handle_107678* h);
void func_0011B018(Handle_107678* dst, Handle_107678* src);
void func_0011B060(Handle_107678* h, s32 mode);
void func_0011B0A8(Handle_107678* dst, Handle_107678* src);
void func_0011B538(Handle_107678* h, s32 id);
void func_001C23B0(Handle_107678* t, s32 n, void* c, void* d, ...);
void func_001DB290(State_107678* st);

Handle_107678* func_00107678(Handle_107678* ret, State_107678* st, void* unused, void* c)
{
    Handle_107678 h;
    Handle_107678 t;
    func_0011B008(&h);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&h, &t);
    func_0011B060(&t, 2);
    func_001DB290(st);
    func_0011B538(&h, 0x22);
    func_0011B018(ret, &h);
    func_0011B060(&h, 2);
    return ret;
}

struct Quad_104A78 { s32 a, b, c, d; };

void func_0011B008(Quad_104A78* q);
void func_0011B018(void* out, Quad_104A78* q);
void func_0011B060(Quad_104A78* q, int mode);
void func_0011B0A8(Quad_104A78* a, Quad_104A78* b);
void func_0011B538(Quad_104A78* q, int n);
void func_001C23B0(Quad_104A78* t, int mode, int c, void* z);
void func_001455F0(void* p);

void* func_00104A78(void* out, void* x, int unused, int c)
{
    Quad_104A78 q;
    Quad_104A78 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001455F0(x);
    func_0011B538(&q, 0x22);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

struct Quad_104CA0 { s32 a, b, c, d; };

void func_0011B008(Quad_104CA0* q);
void func_0011B018(void* out, Quad_104CA0* q);
void func_0011B060(Quad_104CA0* q, int mode);
void func_0011B0A8(Quad_104CA0* a, Quad_104CA0* b);
void func_0011B538(Quad_104CA0* q, int n);
void func_001C23B0(Quad_104CA0* t, int mode, int c, void* z);
void func_001F4F20(void* p);

void* func_00104CA0(void* out, void* x, int unused, int c)
{
    Quad_104CA0 q;
    Quad_104CA0 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001F4F20(x);
    func_0011B538(&q, 0x22);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

struct Quad_104D40 { s32 a, b, c, d; };

void func_0011B008(Quad_104D40* q);
void func_0011B018(void* out, Quad_104D40* q);
void func_0011B060(Quad_104D40* q, int mode);
void func_0011B0A8(Quad_104D40* a, Quad_104D40* b);
void func_0011B538(Quad_104D40* q, int n);
void func_001C23B0(Quad_104D40* t, int mode, int c, void* z);
void func_001F5210(void* p);

void* func_00104D40(void* out, void* x, int unused, int c)
{
    Quad_104D40 q;
    Quad_104D40 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001F5210(x);
    func_0011B538(&q, 0x22);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

struct Quad_104DE0 { s32 a, b, c, d; };

void func_0011B008(Quad_104DE0* q);
void func_0011B018(void* out, Quad_104DE0* q);
void func_0011B060(Quad_104DE0* q, int mode);
void func_0011B0A8(Quad_104DE0* a, Quad_104DE0* b);
void func_0011B538(Quad_104DE0* q, int n);
void func_001C23B0(Quad_104DE0* t, int mode, int c, void* z);
void func_00199AF0(void* p);

void* func_00104DE0(void* out, void* x, int unused, int c)
{
    Quad_104DE0 q;
    Quad_104DE0 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_00199AF0(x);
    func_0011B538(&q, 0x22);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

struct Quad_106C50 { s32 a, b, c, d; };
struct Frame_106C50 { Quad_106C50 q; Quad_106C50 t; };

void func_0011B008(Quad_106C50* q);
void func_0011B018(void* dst, Quad_106C50* src);
void func_0011B060(Quad_106C50* q, int mode);
void func_0011B0A8(Quad_106C50* a, Quad_106C50* b);
void func_0011B538(Quad_106C50* q, int n);
void func_001C23B0(Quad_106C50* t, int mode, int c, void* z);
void func_00150750(void* x);

void* func_00106C50(void* self, void* x, int unused, int c)
{
    Frame_106C50 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_00150750(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_106CF0 { s32 a, b, c, d; };
struct Frame_106CF0 { Quad_106CF0 q; Quad_106CF0 t; };

void func_0011B008(Quad_106CF0* q);
void func_0011B018(void* dst, Quad_106CF0* src);
void func_0011B060(Quad_106CF0* q, int mode);
void func_0011B0A8(Quad_106CF0* a, Quad_106CF0* b);
void func_0011B538(Quad_106CF0* q, int n);
void func_001C23B0(Quad_106CF0* t, int mode, int c, void* z);
void func_00150760(void* x);

void* func_00106CF0(void* self, void* x, int unused, int c)
{
    Frame_106CF0 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_00150760(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_106E60 { s32 a, b, c, d; };
struct Frame_106E60 { Quad_106E60 q; Quad_106E60 t; };

void func_0011B008(Quad_106E60* q);
void func_0011B018(void* dst, Quad_106E60* src);
void func_0011B060(Quad_106E60* q, int mode);
void func_0011B0A8(Quad_106E60* a, Quad_106E60* b);
void func_0011B538(Quad_106E60* q, int n);
void func_001C23B0(Quad_106E60* t, int mode, int c, void* z);
void func_001518B8(void* x);

void* func_00106E60(void* self, void* x, int unused, int c)
{
    Frame_106E60 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001518B8(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_106F00 { s32 a, b, c, d; };
struct Frame_106F00 { Quad_106F00 q; Quad_106F00 t; };

void func_0011B008(Quad_106F00* q);
void func_0011B018(void* dst, Quad_106F00* src);
void func_0011B060(Quad_106F00* q, int mode);
void func_0011B0A8(Quad_106F00* a, Quad_106F00* b);
void func_0011B538(Quad_106F00* q, int n);
void func_001C23B0(Quad_106F00* t, int mode, int c, void* z);
void func_001519A8(void* x);

void* func_00106F00(void* self, void* x, int unused, int c)
{
    Frame_106F00 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001519A8(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_104020 { s32 a, b, c, d; };

void func_0011B008(Quad_104020* q);
void func_0011B018(void* out, Quad_104020* q);
void func_0011B060(Quad_104020* q, int mode);
void func_0011B0A8(Quad_104020* a, Quad_104020* b);
void func_0011B538(Quad_104020* q, int n);
void func_001C23B0(Quad_104020* t, int mode, int c, void* z);
void func_001DDBB8(void* x);

void* func_00104020(void* self, void* x, int unused, int c)
{
    Quad_104020 q;
    Quad_104020 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001DDBB8(x);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

struct Quad_106FA0 { s32 a, b, c, d; };
struct Frame_106FA0 { Quad_106FA0 q; Quad_106FA0 t; };

void func_0011B008(Quad_106FA0* q);
void func_0011B018(void* dst, Quad_106FA0* src);
void func_0011B060(Quad_106FA0* q, int mode);
void func_0011B0A8(Quad_106FA0* a, Quad_106FA0* b);
void func_0011B538(Quad_106FA0* q, int n);
void func_001C23B0(Quad_106FA0* t, int mode, int c, void* z);
void func_001993C0(void* x);

void* func_00106FA0(void* self, void* x, int unused, int c)
{
    Frame_106FA0 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001993C0(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_1070E0 { s32 a, b, c, d; };
struct Frame_1070E0 { Quad_1070E0 q; Quad_1070E0 t; };

void func_0011B008(Quad_1070E0* q);
void func_0011B018(void* dst, Quad_1070E0* src);
void func_0011B060(Quad_1070E0* q, int mode);
void func_0011B0A8(Quad_1070E0* a, Quad_1070E0* b);
void func_0011B538(Quad_1070E0* q, int n);
void func_001C23B0(Quad_1070E0* t, int mode, int c, void* z);
void func_001F3768(void* x);

void* func_001070E0(void* self, void* x, int unused, int c)
{
    Frame_1070E0 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001F3768(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_104170 { s32 a, b, c, d; };
struct Frame_104170 { Quad_104170 q; Quad_104170 t; s32 n; s32 out; };

void func_0011B008(Quad_104170* q);
void func_0011B018(void* dst, Quad_104170* src);
void func_0011B060(Quad_104170* q, int mode);
void func_0011B0A8(Quad_104170* a, Quad_104170* b);
void func_0011B538(Quad_104170* q, int n);
void func_001C23B0(Quad_104170* t, int mode, int c, void* z, void* z2);
s32 func_001DDC18(void* unused, s32 p);

void* func_00104170(void* self, void* x, int unused, int c)
{
    Frame_104170 f;
    func_0011B008(&f.q);
    f.n = 0x5;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_001DDC18(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_104860 { s32 a, b, c, d; };
struct Frame_104860 { Quad_104860 q; Quad_104860 t; };

void func_0011B008(Quad_104860* q);
void func_0011B018(void* dst, Quad_104860* src);
void func_0011B060(Quad_104860* q, int mode);
void func_0011B0A8(Quad_104860* a, Quad_104860* b);
s32 func_0011B570(Quad_104860* q, s32 v);
void func_001C23B0(Quad_104860* t, int mode, int c, void* z);
s32 func_00145FF8(void* x);

void* func_00104860(void* self, void* x, int unused, int c)
{
    Frame_104860 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    s32 v = func_00145FF8(x);
    (void)func_0011B570(&f.q, v);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_1049D8 { s32 a, b, c, d; };
struct Frame_1049D8 { Quad_1049D8 q; Quad_1049D8 t; };

void func_0011B008(Quad_1049D8* q);
void func_0011B018(void* dst, Quad_1049D8* src);
void func_0011B060(Quad_1049D8* q, int mode);
void func_0011B0A8(Quad_1049D8* a, Quad_1049D8* b);
void func_0011B538(Quad_1049D8* q, int n);
void func_001C23B0(Quad_1049D8* t, int mode, int c, void* z);
void func_00146028(void* x);

void* func_001049D8(void* self, void* x, int unused, int c)
{
    Frame_1049D8 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_00146028(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_1069C0 { s32 a, b, c, d; };
struct Frame_1069C0 { Quad_1069C0 q; Quad_1069C0 t; s32 n; s32 out; };

void func_0011B008(Quad_1069C0* q);
void func_0011B018(void* dst, Quad_1069C0* src);
void func_0011B060(Quad_1069C0* q, int mode);
void func_0011B0A8(Quad_1069C0* a, Quad_1069C0* b);
s32 func_0011B5F0(Quad_1069C0* q, s32 flag);
void func_001C23B0(Quad_1069C0* t, int mode, int c, void* z, void* z2);
s32 func_001A8C90(void* obj, s32 v);

void* func_001069C0(void* self, void* x, int unused, int c)
{
    Frame_1069C0 f;
    func_0011B008(&f.q);
    f.n = 0;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    s32 flag = func_001A8C90(x, f.out);
    (void)func_0011B5F0(&f.q, flag);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_106A70 { s32 a, b, c, d; };
struct Frame_106A70 { Quad_106A70 q; Quad_106A70 t; };

void func_0011B008(Quad_106A70* q);
void func_0011B018(void* dst, Quad_106A70* src);
void func_0011B060(Quad_106A70* q, int mode);
void func_0011B0A8(Quad_106A70* a, Quad_106A70* b);
void func_0011B538(Quad_106A70* q, int n);
void func_001C23B0(Quad_106A70* t, int mode, int c, void* z);
void func_001A93E8(void* x);

void* func_00106A70(void* self, void* x, int unused, int c)
{
    Frame_106A70 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001A93E8(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_104470 { s32 a, b, c, d; };

void func_0011B008(Quad_104470* q);
void func_0011B018(void* dst, Quad_104470* src);
void func_0011B060(Quad_104470* q, int mode);
void func_0011B0A8(Quad_104470* a, Quad_104470* b);
void func_0011B538(Quad_104470* q, int n);
void func_001C23B0(Quad_104470* t, int mode, int c, void* z);
void func_001DDA20(void* a);

void* func_00104470(void* out, void* x, int unused, int c)
{
    Quad_104470 q;
    Quad_104470 t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_001DDA20(x);
    func_0011B538(&q, 0x22);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

struct Quad_106B10 { s32 a, b, c, d; };
struct Frame_106B10 { Quad_106B10 q; Quad_106B10 t; };

void func_0011B008(Quad_106B10* q);
void func_0011B018(void* dst, Quad_106B10* src);
void func_0011B060(Quad_106B10* q, int mode);
void func_0011B0A8(Quad_106B10* a, Quad_106B10* b);
void func_0011B538(Quad_106B10* q, int n);
void func_001C23B0(Quad_106B10* t, int mode, int c, void* z);
void func_001A9438(void* x);

void* func_00106B10(void* self, void* x, int unused, int c)
{
    Frame_106B10 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001A9438(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

struct Quad_107898 { s32 a, b, c, d; };
struct Frame_107898 { Quad_107898 q; Quad_107898 t; s32 n; s32 out; };

void func_0011B008(Quad_107898* q);
void func_0011B018(void* dst, Quad_107898* src);
void func_0011B060(Quad_107898* q, int mode);
void func_0011B0A8(Quad_107898* a, Quad_107898* b);
s32 func_0011B5F0(Quad_107898* q, s32 flag);
void func_001C23B0(Quad_107898* t, int mode, int c, void* z, void* z2);
s32 func_00190660(void* x, s32 v);

void* func_00107898(void* self, void* x, int unused, int c)
{
    Frame_107898 f;
    func_0011B008(&f.q);
    f.n = 0x2000;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_0011B5F0(&f.q, func_00190660(x, f.out));
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

// Newly matched US functions from the small-function wave.
struct Quad_1040 { s32 a,b,c,d; };
struct Frame_1040 { Quad_1040 q; Quad_1040 t; s32 n; s32 out; };
void func_0011B008(Quad_1040*);
void func_0011B018(void*,Quad_1040*);
void func_0011B060(Quad_1040*,int);
void func_0011B0A8(Quad_1040*,Quad_1040*);
s32 func_0011B538(Quad_1040*,s32);
s32 func_0011B570(Quad_1040*,s32);
void func_001C23B0(Quad_1040*,int,int,void*,void*);
s32 func_001DDBF8(void*,s32);
s32 func_001DBAE0(void*,s32);
struct Frame2_1040 { Quad_1040 q; Quad_1040 t; };
void func_001C23B0(Quad_1040*,int,int,void*);
void func_001DDA50(void*);
s32 func_001DDC90(void*,s32);
s32 func_001DDC78(void*,s32);
s32 func_00145FB8(void*,s32);
struct Quad_1047C0 { s32 a, b, c, d; };
struct Frame_1047C0 { Quad_1047C0 q; Quad_1047C0 t; };
void func_0011B008(Quad_1047C0*);
void func_0011B018(void*, Quad_1047C0*);
void func_0011B060(Quad_1047C0*, int);
void func_0011B0A8(Quad_1047C0*, Quad_1047C0*);
s32 func_0011B570(Quad_1047C0*, s32);
void func_001C23B0(Quad_1047C0*, int, int, void*);
s32 func_00145FD8(void*);
void func_001F4ED0(void*);
struct Quad_105500 { s32 a, b, c, d; };
struct Frame_105500 { Quad_105500 q; Quad_105500 t; };
struct VTable_105500 { u8 pad[0x194]; void (*f194)(void*); };
struct Object_105500 { VTable_105500* vtable; };
void func_0011B008(Quad_105500*);
void func_0011B018(void*, Quad_105500*);
void func_0011B060(Quad_105500*, int);
void func_0011B0A8(Quad_105500*, Quad_105500*);
s32 func_0011B538(Quad_105500*, s32);
void func_001C23B0(Quad_105500*, int, int, void*);
struct Quad_1055A8 { s32 a, b, c, d; };
struct Frame_1055A8 { Quad_1055A8 q; Quad_1055A8 t; s32 n; s32 out; };
void func_0011B008(Quad_1055A8*);
void func_0011B018(void*, Quad_1055A8*);
void func_0011B060(Quad_1055A8*, int);
void func_0011B0A8(Quad_1055A8*, Quad_1055A8*);
s32 func_0011B538(Quad_1055A8*, s32);
void func_001C23B0(Quad_1055A8*, int, int, void*, void*);
void func_001CB328(void*, s32);
void func_0013BF68(void*);
void func_00171FE0(void*);
struct Quad_func_00105A00 { s32 a,b,c,d; };
struct Frame_func_00105A00 { Quad_func_00105A00 q; Quad_func_00105A00 t; s32 n; s32 out; };
void func_0011B008(Quad_func_00105A00*);
void func_0011B018(void*,Quad_func_00105A00*);
void func_0011B060(Quad_func_00105A00*,int);
void func_0011B0A8(Quad_func_00105A00*,Quad_func_00105A00*);
s32 func_0011B538(Quad_func_00105A00*,s32);
void func_001C23B0(Quad_func_00105A00*,int,int,void*,void*);
void func_001777F8(void*,s32);
struct Quad_func_00105AB0 { s32 a,b,c,d; };
struct Frame_func_00105AB0 { Quad_func_00105AB0 q; Quad_func_00105AB0 t; s32 n; s32 out; };
void func_0011B008(Quad_func_00105AB0*);
void func_0011B018(void*,Quad_func_00105AB0*);
void func_0011B060(Quad_func_00105AB0*,int);
void func_0011B0A8(Quad_func_00105AB0*,Quad_func_00105AB0*);
s32 func_0011B538(Quad_func_00105AB0*,s32);
void func_001C23B0(Quad_func_00105AB0*,int,int,void*,void*);
void func_001D2830(void*,s32);
struct Quad_func_00105B60 { s32 a,b,c,d; };
struct Frame_func_00105B60 { Quad_func_00105B60 q; Quad_func_00105B60 t; s32 n; s32 out; };
void func_0011B008(Quad_func_00105B60*);
void func_0011B018(void*,Quad_func_00105B60*);
void func_0011B060(Quad_func_00105B60*,int);
void func_0011B0A8(Quad_func_00105B60*,Quad_func_00105B60*);
s32 func_0011B538(Quad_func_00105B60*,s32);
void func_001C23B0(Quad_func_00105B60*,int,int,void*,void*);
void func_00177800(void*,s32);
struct Quad_func_00105C10 { s32 a,b,c,d; };
struct Frame_func_00105C10 { Quad_func_00105C10 q; Quad_func_00105C10 t; s32 n; s32 out; };
void func_0011B008(Quad_func_00105C10*);
void func_0011B018(void*,Quad_func_00105C10*);
void func_0011B060(Quad_func_00105C10*,int);
void func_0011B0A8(Quad_func_00105C10*,Quad_func_00105C10*);
s32 func_0011B538(Quad_func_00105C10*,s32);
void func_001C23B0(Quad_func_00105C10*,int,int,void*,void*);
void func_001D31D0(void*,s32);
struct Quad_func_00105EC0 { s32 a,b,c,d; };
struct Frame_func_00105EC0 { Quad_func_00105EC0 q; Quad_func_00105EC0 t; s32 n; s32 out; };
void func_0011B008(Quad_func_00105EC0*);
void func_0011B018(void*,Quad_func_00105EC0*);
void func_0011B060(Quad_func_00105EC0*,int);
void func_0011B0A8(Quad_func_00105EC0*,Quad_func_00105EC0*);
s32 func_0011B538(Quad_func_00105EC0*,s32);
void func_001C23B0(Quad_func_00105EC0*,int,int,void*,void*);
void func_00178280(void*,s32);
struct Quad_func_00106120 { s32 a,b,c,d; };
struct Frame_func_00106120 { Quad_func_00106120 q; Quad_func_00106120 t; };
void func_0011B008(Quad_func_00106120*);
void func_0011B018(void*,Quad_func_00106120*);
void func_0011B060(Quad_func_00106120*,int);
void func_0011B0A8(Quad_func_00106120*,Quad_func_00106120*);
s32 func_0011B538(Quad_func_00106120*,s32);
void func_001C23B0(Quad_func_00106120*,int,int,void*);
void func_00150408(void*);
struct Quad_func_001061C0 { s32 a,b,c,d; };
struct Frame_func_001061C0 { Quad_func_001061C0 q; Quad_func_001061C0 t; s32 n; s32 out; };
void func_0011B008(Quad_func_001061C0*);
void func_0011B018(void*,Quad_func_001061C0*);
void func_0011B060(Quad_func_001061C0*,int);
void func_0011B0A8(Quad_func_001061C0*,Quad_func_001061C0*);
s32 func_0011B538(Quad_func_001061C0*,s32);
void func_001C23B0(Quad_func_001061C0*,int,int,void*,void*);
void func_00150418(void*,s32);
struct __attribute__((aligned(16))) Quad_func_00106270 { s32 a,b,c,d; };
struct Frame_func_00106270 { Quad_func_00106270 q; Quad_func_00106270 t; s32 n; s32 out; };
void func_0011B008(Quad_func_00106270*);
void func_0011B018(void*,Quad_func_00106270*);
void func_0011B060(Quad_func_00106270*,int);
void func_0011B0A8(Quad_func_00106270*,Quad_func_00106270*);
s32 func_0011B538(Quad_func_00106270*,s32);
void func_001C23B0(Quad_func_00106270*,int,int,void*,void*);
void func_0018DD50(void*,s32);
struct __attribute__((aligned(16))) Quad_func_00106320 { s32 a,b,c,d; };
struct Frame_func_00106320 { Quad_func_00106320 q; Quad_func_00106320 t; s32 n; s32 out; };
void func_0011B008(Quad_func_00106320*);
void func_0011B018(void*,Quad_func_00106320*);
void func_0011B060(Quad_func_00106320*,int);
void func_0011B0A8(Quad_func_00106320*,Quad_func_00106320*);
s32 func_0011B538(Quad_func_00106320*,s32);
void func_001C23B0(Quad_func_00106320*,int,int,void*,void*);
void func_0018DD78(void*,s32);
void func_0016DCF0(void*);
void func_0016DD00(void*);
struct __attribute__((aligned(16))) Quad_func_001066F0 { s32 a,b,c,d; };
struct Frame_func_001066F0 { Quad_func_001066F0 q; Quad_func_001066F0 t; s32 n; s32 out; };
void func_0011B008(Quad_func_001066F0*);
void func_0011B018(void*,Quad_func_001066F0*);
void func_0011B060(Quad_func_001066F0*,int);
void func_0011B0A8(Quad_func_001066F0*,Quad_func_001066F0*);
s32 func_0011B538(Quad_func_001066F0*,s32);
void func_001C23B0(Quad_func_001066F0*,int,int,void*,void*);
void func_001A8778(void*,s32);
struct __attribute__((aligned(16))) Quad_func_001067A0 { s32 a,b,c,d; };
struct Frame_func_001067A0 { Quad_func_001067A0 q; Quad_func_001067A0 t; s32 n; s32 out; };
void func_0011B008(Quad_func_001067A0*);
void func_0011B018(void*,Quad_func_001067A0*);
void func_0011B060(Quad_func_001067A0*,int);
void func_0011B0A8(Quad_func_001067A0*,Quad_func_001067A0*);
s32 func_0011B538(Quad_func_001067A0*,s32);
void func_001C23B0(Quad_func_001067A0*,int,int,void*,void*);
void func_001A87A8(void*,s32);
struct __attribute__((aligned(16))) Quad_func_00106920 { s32 a,b,c,d; };
struct Frame_func_00106920 { Quad_func_00106920 q; Quad_func_00106920 t; };
void func_0011B008(Quad_func_00106920*);
void func_0011B018(void*,Quad_func_00106920*);
void func_0011B060(Quad_func_00106920*,int);
void func_0011B0A8(Quad_func_00106920*,Quad_func_00106920*);
s32 func_0011B538(Quad_func_00106920*,s32);
void func_001C23B0(Quad_func_00106920*,int,int,void*);
void func_001A8AF8(void*);
struct __attribute__((aligned(16))) Quad_func_00106BB0 { s32 a,b,c,d; };
struct Frame_func_00106BB0 { Quad_func_00106BB0 q; Quad_func_00106BB0 t; };
void func_0011B008(Quad_func_00106BB0*);
void func_0011B018(void*,Quad_func_00106BB0*);
void func_0011B060(Quad_func_00106BB0*,int);
void func_0011B0A8(Quad_func_00106BB0*,Quad_func_00106BB0*);
s32 func_0011B538(Quad_func_00106BB0*,s32);
void func_001C23B0(Quad_func_00106BB0*,int,int,void*);
void func_001A9498(void*);
struct __attribute__((aligned(16))) Quad_func_00107040 { s32 a,b,c,d; };
struct Frame_func_00107040 { Quad_func_00107040 q; Quad_func_00107040 t; };
void func_0011B008(Quad_func_00107040*);
void func_0011B018(void*,Quad_func_00107040*);
void func_0011B060(Quad_func_00107040*,int);
void func_0011B0A8(Quad_func_00107040*,Quad_func_00107040*);
s32 func_0011B538(Quad_func_00107040*,s32);
void func_001C23B0(Quad_func_00107040*,int,int,void*);
void func_001F36E8(void*);
struct __attribute__((aligned(16))) Quad_func_001074C0 { s32 a,b,c,d; };
struct Frame_func_001074C0 { Quad_func_001074C0 q; Quad_func_001074C0 t; s32 n; s32 out; };
void func_0011B008(Quad_func_001074C0*);
void func_0011B018(void*,Quad_func_001074C0*);
void func_0011B060(Quad_func_001074C0*,int);
void func_0011B0A8(Quad_func_001074C0*,Quad_func_001074C0*);
s32 func_0011B538(Quad_func_001074C0*,s32);
void func_001C23B0(Quad_func_001074C0*,int,int,void*,void*);
void func_001DB110(void*,s32);
struct __attribute__((aligned(16))) Quad_func_00107718 { s32 a,b,c,d; };
struct Frame_func_00107718 { Quad_func_00107718 q; u8 out[16]; Quad_func_00107718 t; s32 n; };
void func_0011B008(Quad_func_00107718*);
void func_0011B018(void*,Quad_func_00107718*);
void func_0011B060(Quad_func_00107718*,int);
void func_0011B0A8(Quad_func_00107718*,Quad_func_00107718*);
s32 func_0011B5F0(Quad_func_00107718*,s32);
void func_001C23B0(Quad_func_00107718*,int,int,void*,void*);
s32 func_00141170(void*,void*);
struct __attribute__((aligned(16))) Quad_func_001077D8 { s32 a,b,c,d; };
struct Frame_func_001077D8 { Quad_func_001077D8 q; u8 out[16]; Quad_func_001077D8 t; s32 n; };
void func_0011B008(Quad_func_001077D8*);
void func_0011B018(void*,Quad_func_001077D8*);
void func_0011B060(Quad_func_001077D8*,int);
void func_0011B0A8(Quad_func_001077D8*,Quad_func_001077D8*);
s32 func_0011B5F0(Quad_func_001077D8*,s32);
void func_001C23B0(Quad_func_001077D8*,int,int,void*,void*);
s32 func_0015AA50(void*,void*);
struct Quad_00107A10 { s32 a, b, c, d; };
void func_0011B008(Quad_00107A10*);
void func_0011B018(void*, Quad_00107A10*);
void func_0011B060(Quad_00107A10*, s32);
void func_0011B0A8(Quad_00107A10*, Quad_00107A10*);
void func_0011B538(Quad_00107A10*, s32);
void func_001C23B0(Quad_00107A10*, s32, s32, void*);
void func_0017CDE0(void*);
struct Quad_00107B60 { s32 a, b, c, d; };
void func_0011B008(Quad_00107B60*);
void func_0011B018(void*, Quad_00107B60*);
void func_0011B060(Quad_00107B60*, s32);
void func_0011B0A8(Quad_00107B60*, Quad_00107B60*);
void func_0011B538(Quad_00107B60*, s32);
void func_001C23B0(Quad_00107B60*, s32, s32, void*);
void func_0017CE80(void*);

void* func_001040C0(void* self, void* x, int unused, int c)
{
 Frame_1040 f; func_0011B008(&f.q); f.n=5; func_001C23B0(&f.t,1,c,&f.n,&f.out); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); s32 v=func_001DDBF8(x,f.out); (void)func_0011B570(&f.q,v); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_001042F0(void* self, void* x, int unused, int c)
{
 Frame_1040 f; func_0011B008(&f.q); f.n=5; func_001C23B0(&f.t,1,c,&f.n,&f.out); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); s32 v=func_001DBAE0(x,f.out); (void)func_0011B570(&f.q,v); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_00104510(void* self, void* x, int unused, int c)
{
 Frame2_1040 f; func_0011B008(&f.q); func_001C23B0(&f.t,0,c,0); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); func_001DDA50(x); func_0011B538(&f.q,0x22); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_001045B0(void* self, void* x, int unused, int c)
{
 Frame_1040 f; func_0011B008(&f.q); f.n=0x1000; func_001C23B0(&f.t,1,c,&f.n,&f.out); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); func_001DDC90(x,f.out); func_0011B538(&f.q,0x22); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_00104660(void* self, void* x, int unused, int c)
{
 Frame_1040 f; func_0011B008(&f.q); f.n=0x1000; func_001C23B0(&f.t,1,c,&f.n,&f.out); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); func_001DDC78(x,f.out); func_0011B538(&f.q,0x22); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_00104710(void* self, void* x, int unused, int c)
{
 Frame_1040 f; func_0011B008(&f.q); f.n=0x1000; func_001C23B0(&f.t,1,c,&f.n,&f.out); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); func_00145FB8(x,f.out); func_0011B538(&f.q,0x22); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_001047C0(void* self, void* x, int unused, int c)
{
    Frame_1047C0 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    (void)func_0011B570(&f.q, func_00145FD8(x));
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

void* func_00104C00(void* self, void* x, int unused, int c)
{
 Frame2_1040 f; func_0011B008(&f.q); func_001C23B0(&f.t,0,c,0); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); func_001F4ED0(x); func_0011B538(&f.q,0x22); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_00105500(void* self, Object_105500* x, int unused, int c)
{
    Frame_105500 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    x->vtable->f194(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

void* func_001055A8(void* self, void* x, int unused, int c)
{
    Frame_1055A8 f;
    func_0011B008(&f.q);
    f.n = 0x2000;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001CB328(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

void* func_001057D8(void* self, void* x, int unused, int c)
{
 Frame2_1040 f; func_0011B008(&f.q); func_001C23B0(&f.t,0,c,0); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); func_0013BF68(x); func_0011B538(&f.q,0x22); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_00105960(void* self, void* x, int unused, int c)
{
 Frame2_1040 f; func_0011B008(&f.q); func_001C23B0(&f.t,0,c,0); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); func_00171FE0(x); func_0011B538(&f.q,0x22); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_00105A00(void* self, void* x, int unused, int c)
{
    Frame_func_00105A00 f;
    func_0011B008(&f.q);
    f.n = 0;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001777F8(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

void* func_00105AB0(void* self, void* x, int unused, int c)
{
    Frame_func_00105AB0 f;
    func_0011B008(&f.q);
    f.n = 0x2000;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001D2830(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

void* func_00105B60(void* self, void* x, int unused, int c)
{
    Frame_func_00105B60 f;
    func_0011B008(&f.q);
    f.n = 0;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_00177800(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

void* func_00105C10(void* self, void* x, int unused, int c)
{
    Frame_func_00105C10 f;
    func_0011B008(&f.q);
    f.n = 0;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_001D31D0(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

void* func_00105EC0(void* self, void* x, int unused, int c)
{
    Frame_func_00105EC0 f;
    func_0011B008(&f.q);
    f.n = 0x2000;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_00178280(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

void* func_00106120(void* self, void* x, int unused, int c)
{
    Frame_func_00106120 f;
    func_0011B008(&f.q);
    func_001C23B0(&f.t, 0, c, 0);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_00150408(x);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

void* func_001061C0(void* self, void* x, int unused, int c)
{
    Frame_func_001061C0 f;
    func_0011B008(&f.q);
    f.n = 0x2000;
    func_001C23B0(&f.t, 1, c, &f.n, &f.out);
    func_0011B0A8(&f.q, &f.t);
    func_0011B060(&f.t, 2);
    func_00150418(x, f.out);
    func_0011B538(&f.q, 0x22);
    func_0011B018(self, &f.q);
    func_0011B060(&f.q, 2);
    return self;
}

void* func_00106270(void* self,void* x,int unused,int c)
{
 Frame_func_00106270 f; func_0011B008(&f.q); f.n=6; func_001C23B0(&f.t,1,c,&f.n,&f.out); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); func_0018DD50(x,f.out); func_0011B538(&f.q,0x22); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_00106320(void* self,void* x,int unused,int c)
{
 Frame_func_00106320 f; func_0011B008(&f.q); f.n=7; func_001C23B0(&f.t,1,c,&f.n,&f.out); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); func_0018DD78(x,f.out); func_0011B538(&f.q,0x22); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_001064C0(void* self, void* x, int unused, int c)
{
 Frame2_1040 f; func_0011B008(&f.q); func_001C23B0(&f.t,0,c,0); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); func_0016DCF0(x); func_0011B538(&f.q,0x22); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_00106560(void* self, void* x, int unused, int c)
{
 Frame2_1040 f; func_0011B008(&f.q); func_001C23B0(&f.t,0,c,0); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); func_0016DD00(x); func_0011B538(&f.q,0x22); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_001066F0(void* self,void* x,int unused,int c)
{
 Frame_func_001066F0 f; func_0011B008(&f.q); f.n=6; func_001C23B0(&f.t,1,c,&f.n,&f.out); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); func_001A8778(x,f.out); func_0011B538(&f.q,0x22); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_001067A0(void* self,void* x,int unused,int c)
{
 Frame_func_001067A0 f; func_0011B008(&f.q); f.n=6; func_001C23B0(&f.t,1,c,&f.n,&f.out); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); func_001A87A8(x,f.out); func_0011B538(&f.q,0x22); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_00106920(void* self,void* x,int unused,int c)
{
 Frame_func_00106920 f; func_0011B008(&f.q); func_001C23B0(&f.t,0,c,0); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); func_001A8AF8(x); func_0011B538(&f.q,0x22); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_00106BB0(void* self,void* x,int unused,int c)
{
 Frame_func_00106BB0 f; func_0011B008(&f.q); func_001C23B0(&f.t,0,c,0); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); func_001A9498(x); func_0011B538(&f.q,0x22); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_00107040(void* self,void* x,int unused,int c)
{
 Frame_func_00107040 f; func_0011B008(&f.q); func_001C23B0(&f.t,0,c,0); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); func_001F36E8(x); func_0011B538(&f.q,0x22); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_001074C0(void* self,void* x,int unused,int c)
{
 Frame_func_001074C0 f; func_0011B008(&f.q); f.n=0x2000; func_001C23B0(&f.t,1,c,&f.n,&f.out); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); func_001DB110(x,f.out); func_0011B538(&f.q,0x22); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_00107718(void* self,void* x,int unused,int c)
{
 Frame_func_00107718 f; func_0011B008(&f.q); f.n=2; func_001C23B0(&f.t,1,c,&f.n,f.out); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); func_0011B5F0(&f.q,func_00141170(x,f.out)); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_001077D8(void* self,void* x,int unused,int c)
{
 Frame_func_001077D8 f; func_0011B008(&f.q); f.n=2; func_001C23B0(&f.t,1,c,&f.n,f.out); func_0011B0A8(&f.q,&f.t); func_0011B060(&f.t,2); func_0011B5F0(&f.q,func_0015AA50(x,f.out)); func_0011B018(self,&f.q); func_0011B060(&f.q,2); return self;
}

void* func_00107A10(void* self, void* x, s32 unused, s32 c)
{
    Quad_00107A10 q, t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0017CDE0(x);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

void* func_00107B60(void* self, void* x, s32 unused, s32 c)
{
    Quad_00107B60 q, t;
    func_0011B008(&q);
    func_001C23B0(&t, 0, c, 0);
    func_0011B0A8(&q, &t);
    func_0011B060(&t, 2);
    func_0017CE80(x);
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}
