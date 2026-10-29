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
