// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

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

void func_001922E8(void* a, void* b);

void func_001974D8(void* a, void* b)
{
    func_001922E8(a, b);
}

extern u8 D_0026A210[];
void func_001F5C0C(void* p, s32 zero, s32 size);

void func_00196330(void* p, s32 flag)
{
    if (flag == 0xFFFF && p != 0) {
        u8* s = D_0026A210;
        func_001F5C0C(s, 0, 0x1C);
        f32 k = 0.6f;
        f32 big = 15.0f;
        s[0x4] = 0x2D;
        *(f32*)(s + 0x8) = big;
        *(f32*)(s + 0x10) = k;
        *(f32*)(s + 0x14) = k;
        *(s32*)(s + 0x18) = (s32)0xFF7D4B00;
    }
}

extern u8 D_00261EF0[];
void func_00151E20(void* self, f32 amount);

void func_001973D8(u8* self)
{
    f32 one = 1.0f;
    f32 t = (f32)*(s32*)(self + 0x680) / (f32)*(s32*)(self + 0x684);
    f32 c;
    if (t < 0.0f) {
        c = 0.0f;
    } else if (one < t) {
        c = one;
    } else {
        c = t;
    }
    func_00151E20(D_00261EF0, 1.0f - c * 0.8f);
}

extern void* D_0026A904;
void func_001B6568(void* dev, s32* out);
void func_001B6598(void* dev, s32* out);
void func_001B64D8(void* dev, s32 value);
void func_001973D8(u8* self);

void func_00197458(s32 unused, s32 flag)
{
    s32 out[4];
    if (flag == 1) {
        if (*(void**)((u8*)*(void**)&D_0026A904 + 0x6B8) != 0) {
            func_001B6568(*(void**)((u8*)*(void**)&D_0026A904 + 0x6B8), &out[0]);
            func_001B6598(*(void**)((u8*)*(void**)&D_0026A904 + 0x6B8), &out[1]);
            if (out[0] != 0x3F4 && out[1] != 0x3F4) {
                func_001B64D8(*(void**)((u8*)*(void**)&D_0026A904 + 0x6B8), 0x3F5);
                func_001973D8(*(u8**)&D_0026A904);
            }
        }
    }
}

extern u8 D_0026E744[];

typedef void (*VFn_197F10)(void* self);
struct Vt_197F10 { VFn_197F10* vtbl; };

struct Obj_197F10 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x644 - 0x18];
    s32 f644;
    u8 pad2[0x688 - 0x648];
    f32 f688;
    u8 pad3[0x6B8 - 0x68C];
    void* f6B8;
};

void func_00192230(void* self, s32 kind, void* rec);
void func_001B6598(void* dev, s32* out);
void func_001DDC38(void* sub, void* self);
void func_001AB890(void* obj, f32 x);
void func_001AB928(void* obj, f32 x, void* fn);
void func_001AB938(void* obj);
void func_001AB958(void* obj);
void func_00197458(s32 unused, s32 flag);

void func_00197F10(Obj_197F10* self, s32 kind, void* rec)
{
    s32 code;
    func_00192230(self, kind, rec);
    switch (kind) {
    case 0xB:
        self->f644 = 0;
        return;
    case 0xA:
        self->f644 = *(s32*)rec;
        return;
    case 0x14:
        if (rec != self->f6B8) {
            return;
        }
        func_001B6598(rec, &code);
        if (code == 0x3F3) {
            u8* tbl;
            *(void**)D_0026E744 = (u8*)self + 0x67C;
            tbl = (u8*)&D_0026D348;
            *(void**)(tbl + 0x264) = (u8*)self + 0x680;
            *(void**)(tbl + 0x268) = (u8*)self + 0x684;
            func_001DDC38(self->f14, self);
            func_001AB890(&D_0026E760, self->f688);
            func_001AB928(&D_0026E760, 0.0f, (void*)func_00197458);
            func_001AB938(&D_0026E760);
        } else {
            if (code < 0x3F3) {
                return;
            }
            if (code < 0x3F6) {
                func_001AB958(&D_0026E760);
                ((Vt_197F10*)&D_0026D348)->vtbl[15](&D_0026D348);
                ((Vt_197F10*)&D_0026E4E0)->vtbl[15](&D_0026E4E0);
                ((Vt_197F10*)&D_0026E760)->vtbl[15](&D_0026E760);
                func_001DDC38(self->f14, 0);
            }
        }
        return;
    }
}

struct Ctl_194E60 {
    u8 pad0[0x250];
    s32 f250;
    u8 pad1[0x0C];
    s32 f260;
    u8 pad2[0x10];
    s32 f274;
    s32 f278;
};

void func_001936A0(Ctl_194E60* self);
void func_00195928(void* self, s32 v);
void func_001AA998(void* self, s32 flag);

void func_00194E60(Ctl_194E60* self, s32 v)
{
    s32 flag = v;

    if (self->f250 == v) return;
    if (self->f250 == 0 && self->f260 == 0) {
        func_001936A0(self);
    }
    if (v == 0) {
        if (self->f274 != 0) {
            func_00195928(self, self->f278);
            flag = 1;
            self->f274 = 0;
            self->f278 = -1;
        } else {
            if (self->f260 == 0) {
                func_001936A0(self);
            }
        }
    }
    func_001AA998(self, flag);
}

typedef void (*VFn_194D30)(void* self, s32 a);
struct Obj_194D30 { VFn_194D30* vtbl; };

struct Self_194D30 {
    u8 pad0[0x250];
    s32 f250;
    u8 pad1[0x25C - 0x254];
    s32 f25C;
    s32 f260;
    u8 pad2[0x268 - 0x264];
    s32 arr268[3];
    s32 f274;
    s32 f278;
};

extern u8 D_00275BC0[];

void func_00193EE8(void* self, s32 a, s32 b);
void func_00195928(void* self, s32 v);
void func_001E9570(void* q);
void func_001E9498(void* a, void* b);

void func_00194D30(Self_194D30* self, s32 idx, s32 value)
{
    s32 s1;
    s32 s2;
    u32 i;
    s32* p;

    s2 = value;
    self->arr268[idx] = s2;
    p = self->arr268;
    for (i = 0; i < 3; i++) {
        if (*p != -1) {
            s2 = *p;
        }
        p++;
    }
    if (self->f274 != 0) {
        s1 = self->f278;
    } else {
        s1 = self->f260;
    }
    func_00193EE8(self, s1, s2);
    if (s1 != s2) {
        if (self->f250 == 0) {
            func_00195928(self, s2);
        } else if (self->f250 >= 0) {
          if (self->f250 < 4) {
            if (s2 == -1) {
                self->f274 = 0;
                self->f278 = s2;
            } else {
                self->f278 = s2;
                self->f274 = 1;
                ((Obj_194D30*)self)->vtbl[16](self, 3);
            }
          }
        }
    }
    if (s2 == -1) {
        if (self->f25C != 0) {
            func_001E9570(D_00275BC0);
        }
    } else {
        if (self->f25C == 0) {
            func_001E9498(D_00275BC0, self);
        }
    }
}

struct Obj_197848;
struct VT_197848 {
    u8 pad0[0x18];
    void (*f18)(Obj_197848*);
    u8 pad1[0x84 - 0x1C];
    void (*f84)(Obj_197848*, void*);
    void (*f88)(Obj_197848*, void*);
    u8 pad2[0x90 - 0x8C];
    void (*f90)(Obj_197848*, void*);
    void (*f94)(Obj_197848*, void*);
};
struct Obj_197848 {
    VT_197848* vt;
    u8 pad[0xC14 - 4];
    void* fC14;
};
struct Node_197848 {
    u8 pad[0x568];
    Node_197848* next;
};
struct Self_197848 {
    u8 pad[0x690];
    s32 count;
    Obj_197848** items;
    f32 time;
    u8 list[4];
};

extern f32 D_00261858[];
extern u8 D_00248D30[];
extern f32 D_0026A838;
extern Obj_197848* func_00182FC8(Obj_197848*);
extern s32 func_001527D8(void* list);
extern s32 func_001EAA70(s32 a, s32 b);
extern void func_00152600(void* a, void* b);
extern void func_00152470(void* a, void* b);
extern void func_001C8F20(void* node, s32 kind, s32 flag);
extern void func_001A76A0(void* node, s32 flag);

void func_00197848(Self_197848* self)
{
    s32 scratch[4];
    if (D_00261858[1] < self->time) return;
    s32 i = 0;
    for (; i < self->count; i++) {
        if (func_00182FC8(self->items[i]) == 0) break;
    }
    if (i >= self->count) {
        self->time = 3.4028234663852886e+38f;
        return;
    }
    Obj_197848* o = self->items[i];
    s32 n = func_001EAA70(0, func_001527D8(self->list) - 1);
    Node_197848* nd = *(Node_197848**)self->list;
    if (n > 0) {
        do {
            nd = nd->next;
        } while (--n);
    }
    if (nd == 0) return;
    func_00152600(self->list, nd);
    func_00152470((u8*)self + 0x6A8, nd);
    o->vt->f18(o);
    o->vt->f84(o, (u8*)nd + 0x140);
    o->vt->f88(o, (u8*)nd + 0x110);
    o->vt->f90(o, D_00248D30);
    o->vt->f94(o, D_00248D30);
    func_001C8F20(o, 0x10, 0);
    o->fC14 = nd;
    func_001A76A0(nd, 1);
    self->time = D_00261858[1] + D_0026A838;
}
