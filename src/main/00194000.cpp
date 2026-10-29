// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Manager_197458 { u8 pad[0x6B8]; void* object; };
extern Manager_197458* D_0026A904;
void func_001B6568(void*, s32*);
void func_001B6598(void*, s32*);
void func_001B64D8(void*, s32);
void func_001973D8(Manager_197458*);

void func_00197458(void*, s32 mode)
{
    if (mode == 1) {
        if (D_0026A904->object != 0) {
            s32 a, b;
            func_001B6568(D_0026A904->object, &a);
            func_001B6598(D_0026A904->object, &b);
            if (a != 0x3F4 && b != 0x3F4) {
                func_001B64D8(D_0026A904->object, 0x3F5);
                func_001973D8(D_0026A904);
            }
        }
    }
}

void func_001AA8F0(void* self);

struct Ctl_194F00 { u8 pad[0x250]; s32 mode250; u8 pad2[0x20]; s32 f274; };

void func_00194F00(Ctl_194F00* self)
{
    if (self->mode250 == 3 && self->f274 != 0) return;
    func_001AA8F0(self);
}

void func_001AA958(void* self);

struct Ctl_194F38 { u8 pad[0x250]; s32 mode250; u8 pad2[0x20]; s32 f274; s32 f278; };

void func_00194F38(Ctl_194F38* self)
{
    if (self->mode250 == 3 && self->f274 != 0) {
        self->f274 = 0;
        self->f278 = -1;
        return;
    }
    func_001AA958(self);
}

void func_001936A0(void* self, s32 v);

struct Ctl_195928 { u8 pad[0x260]; s32 f260; };

void func_00195928(Ctl_195928* self, s32 v)
{
    if (self->f260 != v) {
        self->f260 = v;
        if (v != -1) func_001936A0(self, v);
    }
}

struct Obj_1963D8 { u8 pad0[0x14]; u8* f14; };

void func_00123ED0(Obj_1963D8* self);
void func_00152470(u8* dst, Obj_1963D8* src);

void func_001963D8(Obj_1963D8* self)
{
    func_00123ED0(self);
    func_00152470(self->f14 + 0x1C3C, self);
}

struct Obj_196900 { void** vtbl; };

void func_00124A48(Obj_196900* self);

void func_00196900(Obj_196900* self)
{
    func_00124A48(self);
    ((void (*)(Obj_196900*))self->vtbl[7])(self);
}

extern u8 D_0026A728[];

void func_001BAC30(void* self);
void func_00124DF8(void* self, s32 n, void* table);

void func_001969C0(void* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 1, D_0026A728);
}

struct Obj_196E48 { u8 pad0[0x50]; s32 f50; u8 pad1[0x538 - 0x54]; u64 bits538; };

s32 func_001300E8(void* self, s32 kind);

s32 func_00196E48(s32 a0, Obj_196E48* self)
{
    if (self->bits538 & 0x80000000000ULL) {
        if (func_001300E8(self, 0x1F) == 0) return 0;
    }
    return self->f50 != a0;
}

void func_001B6598(void* obj, s32* out);
void* func_001E9970(s32 arg);

typedef void (*VFn_197788)(void* self);
struct Iface_197788 { VFn_197788* vtbl; };
extern Iface_197788 D_0026D348;
extern Iface_197788 D_0026E4E0;
extern Iface_197788 D_0026E760;

struct Obj_197788 { u8 pad[0x6B8]; void* f6B8; };

void func_00197788(Obj_197788* self)
{
    s32 v;
    func_001B6598(self->f6B8, &v);
    void* p = 0;
    if (v == 0x3F3) p = func_001E9970(0);
    if (p != 0) {
        D_0026D348.vtbl[14](&D_0026D348);
        D_0026E4E0.vtbl[14](&D_0026E4E0);
        D_0026E760.vtbl[14](&D_0026E760);
        return;
    }
    D_0026D348.vtbl[15](&D_0026D348);
    D_0026E4E0.vtbl[15](&D_0026E4E0);
    D_0026E760.vtbl[15](&D_0026E760);
}

void func_001A76A0(void* node, s32 flag);
void func_00152600(void* a, void* b);
void func_00152470(void* a, void* b);

struct Ctx_197A08 { u8 pad[0xC14]; void* fC14; };

void func_00197A08(u8* self, Ctx_197A08* ctx)
{
    void* p = ctx->fC14;
    func_001A76A0(p, 0);
    func_00152600(self + 0x6A8, p);
    func_00152470(self + 0x69C, p);
    ctx->fC14 = 0;
}

struct Glob_194278 { u8 pad[0x19D8]; s32 f19D8; s32 f19DC; };
struct Rec_194278 { s32 f0; void* f4; s32 f8; s32 fC; s32 f10; };

extern void* D_002623C0;
extern void* D_00275710;
extern u8 D_00275B04[];
extern u8 D_00275F80[];

void func_00194D30(void* self, s32 a, s32 b);
void func_001EFFA0(void* obj, void* rec, s32 n);
void* func_0015A838(void* a, s32 b, s32 c, s32 d);
void func_001A4EF0(void* p, s32 mode);
void func_001F4408(void* a, s32 b);

void func_00194278(void* a0, s32 a1, s32 a2)
{
    func_00194D30(a0, 0, -1);
    Glob_194278* g = (Glob_194278*)D_002623C0;
    s32 key = (g->f19D8 << 8) | g->f19DC;
    if (key == 0x106) {
        if (a1 != 0) {
            Rec_194278 r;
            r.f0 = 1;
            r.f4 = D_00275B04;
            r.f8 = -1;
            r.fC = -1;
            r.f10 = 0;
            func_001EFFA0(D_00275F80, &r, a2);
        } else {
            void* p = func_0015A838(D_00275710, 5, 0x5F, 0);
            func_001A4EF0(p, 6);
        }
        return;
    }
    if (a1 != 0) {
        Rec_194278 r;
        r.f0 = 1;
        r.f4 = D_00275B04;
        r.f8 = -1;
        r.fC = -1;
        r.f10 = 0x10;
        func_001EFFA0(D_00275F80, &r, a2);
    } else {
        func_001F4408(0, a2);
    }
}

extern f32 D_0026A83C;
extern f32 D_0026A840;

struct Pair_00197A68 { u8 pad[0x94]; f32 f94; f32 f98; };

void func_00197A68(void* ctx, Pair_00197A68* out)
{
    (void)ctx;
    out->f98 = D_0026A83C;
    out->f94 = D_0026A840;
}

void func_001936A0(void* self);
void func_00195928(void* self, s32 value);
void func_001AA998(void* self, s32 value);
struct Obj_194E60 { u8 pad[0x250]; s32 mode; u8 pad1[0xC]; s32 f260; u8 pad2[0x10]; s32 f274; s32 f278; };
void func_00194E60(Obj_194E60* self, s32 mode)
{
    if (self->mode == mode) return;
    if (self->mode == 0 && self->f260 == 0) func_001936A0(self);
    if (mode == 0) {
        if (self->f274 != 0) {
            func_00195928(self, self->f278);
            mode = 1;
            self->f274 = 0;
            self->f278 = -1;
        } else if (self->f260 == 0) {
            func_001936A0(self);
        }
    }
    func_001AA998(self, mode);
}
