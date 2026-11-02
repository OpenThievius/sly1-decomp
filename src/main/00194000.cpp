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

extern u8 D_00247AB0[];
extern u8 D_00275F80[];

void func_001EFFA0(void* dst, void* args, s32 count);

struct Args_194398 {
    s32 kind;
    void* text;
    s32 x;
    s32 y;
    s32 z;
};

void func_00194398(void)
{
    Args_194398 args;
    args.kind = 1;
    args.text = D_00247AB0;
    args.x = -1;
    args.y = -1;
    args.z = 4;
    func_001EFFA0(D_00275F80, &args, 0);
}

extern u8 D_00248D20[];
extern f32 D_0026A71C;
extern f32 D_0026A718;

struct __attribute__((aligned(16))) Quad_196938 { s32 a, b, c, d; };

struct Sub_196938 { u8 bytes[0x568]; };

struct Obj_196938 {
    u8 pad0[0x61C];
    f32 f61C;
    u8 pad620[0x624 - 0x620];
    f32 f624;
    f32 f628;
    u8 pad62C[0x630 - 0x62C];
    Quad_196938 q630;
    u8 pad640[0x688 - 0x640];
    f32 f688;
};

void func_001921A8(Obj_196938* self);
void func_00152438(Sub_196938* p, s32 value);

void func_00196938(Obj_196938* self)
{
    func_001921A8(self);
    self->f61C = -10.0f;
    self->q630 = *(Quad_196938*)D_00248D20;
    self->f688 = 120.0f;
    self->f624 = D_0026A71C;
    self->f628 = D_0026A718;
    func_00152438((Sub_196938*)((u8*)self + 0x6A8), 0x568);
    func_00152438((Sub_196938*)((u8*)self + 0x69C), 0x568);
    *(Obj_196938**)&D_0026A904 = self;
}

struct Self_1961C0 {
    u8 pad0[0x260];
    s32 state;
};
// The register at +0x18 is described with 32-bit bit-fields, the one at +0x40 with 64-bit ones;
// the mixed types are what give retail's copy of the masked value.
struct Reg_1961C0 { u64 lo : 12; u64 mid : 11; u64 rest : 41; };
struct RegA_1961C0 { u32 lo : 12; u32 mid : 11; u32 rest : 9; u32 hi; } __attribute__((aligned(8)));
struct Gs_1961C0 {
    u8 pad0[0x18];
    RegA_1961C0 f18;
    u8 pad20[0x20];
    Reg_1961C0 f40;
};
extern Gs_1961C0 D_00262490;
extern s32 D_00275BF0;
extern f32 D_0026A708;
extern f32 D_0026A70C;
void func_00194D30(Self_1961C0* self, s32 a, s32 b);
s32 func_001FD7A0(f32 x);

void func_001961C0(Self_1961C0* self)
{
    switch (self->state) {
    case 0:
        func_00194D30(self, 0, -1);
        break;
    case 23:
        if ((u32)(D_00275BF0 - 1) < 2) {
            func_00194D30(self, 0, -1);
            break;
        }
        func_00194D30(self, 0, 0);
        break;
    case 24: {
        Gs_1961C0* g = &D_00262490;
        s32 v = func_001FD7A0(D_0026A708);
        Reg_1961C0 a = g->f40;
        RegA_1961C0 b = g->f18;
        a.lo = v;
        b.lo = v;
        g->f40 = a;
        g->f18 = b;
        s32 w = func_001FD7A0(D_0026A70C);
        a.mid = w;
        b.mid = w;
        g->f40 = a;
        g->f18 = b;
        func_00194D30(self, 0, 0x17);
        break;
    }
    case 2:
        func_00194D30(self, 0, 0);
        break;
    case 13:
        func_00194D30(self, 1, -1);
        break;
    case 11:
    case 16:
    case 17:
    case 31:
        func_00194D30(self, 0, 0x17);
        break;
    case 14:
    case 18:
        func_00194D30(self, 1, -1);
        break;
    }
}

struct Menu_195958 {
    u8 pad0[0x260];
    s32 f260;
    s32 f264;
    s32 f268;
    u8 pad1[0x27C - 0x26C];
    s32 f27C;
    s32 f280;
};
struct Row_195958 {
    u8 pad0[0x14];
    s32* items;
};
struct Glob_195958 {
    u8 pad0[0x19EC];
    u32 f19EC;
};
struct Boot_195958 {
    u8 pad0[0x4F44];
    void* f4F44;
    u8 pad1[0x4F4C - 0x4F48];
    void* f4F4C;
};
struct Sub_195958 {
    u8 pad0[0x260];
    s32 f260;
};
struct VT_195958 {
    u8 pad0[0x38];
    void (*f38)(void* self);
};
struct Dev_195958 {
    VT_195958* vt;
};
struct Ent_195958 {
    u8 pad0[0xC];
    f32 fC;
    u8 pad1[0x1A5C - 0x10];
};
struct Pool_195958 {
    u8 pad0[1];
};

extern Row_195958 D_00269D50[];
extern Boot_195958 D_00264A40;
extern Sub_195958 D_0026F808;
extern u8 D_00275BC0[];
extern u8 D_00247AD0[];
extern Pool_195958 D_00269990;
extern Ent_195958 D_002542D8[];
extern Dev_195958 D_00273EB0;

void func_001961C0(Menu_195958* self);
void func_00194D30(Menu_195958* self, s32 a, s32 b);
void func_00194278(Menu_195958* self, s32 a, s32 b);
void func_001E9498(u8* a, Sub_195958* b);
void func_001F4408(s32 a, s32 b);
void func_001F0428(u8* a, s32 b, s32 c);
void func_0018C178(Boot_195958* a, s32 b);
void func_0018B670(Pool_195958* a, void* fn, Boot_195958* self);
void func_0018C638(Boot_195958* self);
void func_0018C1A8(Boot_195958* self);
void func_0018C250(Boot_195958* self);
void func_0018C770(Boot_195958* self);
void func_0018C568(Boot_195958* self);
void func_00160948(void);
void func_001936A0(Menu_195958* self);
void* func_00193660(void);
void* func_001925F0(void);
s32 func_001300E8(void* node, s32 kind);
void func_001B6598(void* ptr, s32* out);
void func_001D9338(void* p);
void func_001B6628(void* h, s32 arg);
void func_001B64D8(s32 a, s32 b);
s32 func_001602A0(void);
void func_00160578(s32 n);
void func_00194398(void);
void func_001A7F50(Glob_195958* g);
void func_001C0760(s32 flag);
void func_001C0790(s32 flag);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

void func_00195958(Menu_195958* self)
{
    s32 sel = D_00269D50[self->f260].items ? D_00269D50[self->f260].items[self->f264] : -1;
    if (sel == 0x11) {
        func_001961C0(self);
        return;
    }
    switch (self->f260) {
    case 0:
        switch (sel) {
        case 3:
            func_00194D30(self, 0, -1);
            return;
        case 4: {
            Sub_195958* s = &D_0026F808;
            if (s->f260 != 0) {
                func_00194D30(self, 0, -1);
                func_001E9498(D_00275BC0, s);
                return;
            }
            func_001BFCD8(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            return;
        }
        case 18: {
            s32 v;
            void* s2 = func_00193660();
            void* s0 = func_001925F0();
            if (s2 != 0 && s0 != 0 && func_001300E8(s0, 0x19) != 0) {
                func_001B6598(s2, &v);
                if (v < 0x431) {
                    if (v >= 0x42F) {
                        func_001D9338(s0);
                        func_001B6628(s2, 0x42E);
                    }
                }
            }
            func_00194D30(self, 0, -1);
            return;
        }
        case 19:
        case 20:
            func_00194278(self, 1, 1);
            return;
        case 21:
            func_00194D30(self, 0, -1);
            func_001F4408(1, 2);
            return;
        case 22:
            func_00194D30(self, 0, -1);
            func_001F0428(D_00247AD0, -1, 2);
            return;
        case 9:
            func_00194D30(self, 0, 2);
            return;
        case 5:
            func_00194D30(self, 0, 0x17);
            return;
        case 23:
            func_00194D30(self, 0, 0x1F);
            return;
        }
        return;
    case 23:
        switch (sel) {
        case 6:
            func_0018C178(&D_00264A40, 1);
            func_00194D30(self, 0, 0x10);
            return;
        case 7:
            func_0018C178(&D_00264A40, 1);
            func_00194D30(self, 0, 0x11);
            return;
        case 8:
            func_0018C178(&D_00264A40, 1);
            func_00194D30(self, 0, 0xB);
            return;
        case 13:
            func_001A7F50(((Glob_195958*)D_002623C0));
            {
                s32 keep;
                keep = self->f264;
                func_001936A0(self);
                self->f264 = keep;
            }
            return;
        case 15: {
            Glob_195958* g = ((Glob_195958*)D_002623C0);
            g->f19EC ^= 0x80;
            func_001C0760(g->f19EC & 0x80);
            {
                s32 keep;
                keep = self->f264;
                func_001936A0(self);
                self->f264 = keep;
            }
            return;
        }
        case 16: {
            Glob_195958* g = ((Glob_195958*)D_002623C0);
            g->f19EC ^= 0x40;
            func_001C0790(g->f19EC & 0x40);
            {
                s32 keep;
                keep = self->f264;
                func_001936A0(self);
                self->f264 = keep;
            }
            return;
        }
        case 14:
            func_00194D30(self, 0, 0x18);
            return;
        case 23:
            func_00194D30(self, 0, 0x1F);
            return;
        }
        return;
    case 27:
        if ((func_001602A0() & 8) != 0) {
            func_00160578(8);
            return;
        }
        func_00194278(self, 0, 2);
        return;
    case 1:
    case 26:
    case 28:
    case 29:
    case 30:
        func_00194278(self, (u32)sel < 1, 1);
        return;
    case 25: {
        s32 a = self->f280;
        self->f280 = 0;
        func_001B64D8(a, sel == 0 ? 0x434 : 0x435);
        func_00194D30(self, 0, -1);
        return;
    }
    case 2:
        if (sel == 0) {
            Boot_195958* b = &D_00264A40;
            if (b->f4F44 != 0) {
                self->f27C = 2;
                if ((((Glob_195958*)D_002623C0)->f19EC & 0x100) == 0) {
                    func_00194D30(self, 1, 0x14);
                } else {
                    func_00194D30(self, 1, 0xC);
                    func_0018B670(&D_00269990, (void*)func_0018C638, b);
                }
            } else {
                func_00194398();
            }
            func_00194D30(self, 0, -1);
            return;
        }
        func_00194D30(self, 0, -1);
        return;
    case 31:
        switch (sel) {
        case 0x18: {
            ((Glob_195958*)D_002623C0)->f19EC ^= 0x200;
            s32 keep = self->f264;
            func_001936A0(self);
            self->f264 = keep;
            return;
        }
        case 0x19: {
            ((Glob_195958*)D_002623C0)->f19EC ^= 0x400;
            s32 keep = self->f264;
            func_001936A0(self);
            self->f264 = keep;
            return;
        }
        case 0x1A: {
            ((Glob_195958*)D_002623C0)->f19EC ^= 0x800;
            s32 keep = self->f264;
            func_001936A0(self);
            self->f264 = keep;
            return;
        }
        }
        return;
    case 14:
        if (sel == 0) {
            goto c6030;
        }
        func_00194D30(self, 1, -1);
        return;
    case 4:
        if (sel == 0) {
            func_0018B670(&D_00269990, (void*)func_0018C1A8, &D_00264A40);
            func_00194D30(self, 1, 5);
            return;
        }
        goto c5EC0;
    case 7:
        if (sel == 0) {
            func_0018B670(&D_00269990, (void*)func_0018C250, &D_00264A40);
            func_00194D30(self, 1, 8);
            return;
        }
        goto c5EC0;
    case 3:
    case 6:
    case 9:
    case 10:
    case 21:
    case 32:
    c5EC0: {
        s32 v;
        func_00194D30(self, 1, -1);
        func_0018C178(&D_00264A40, 2);
        v = self->f268;
        if (v == 0xB) {
            goto c5F08;
        }
        if (v < 0xB) {
            return;
        }
        if (v >= 0x12) {
            return;
        }
        if (v < 0x10) {
            return;
        }
    }
    case 24:
    c5F08:
        func_00194D30(self, 0, 0x17);
        return;
    case 16: {
        Ent_195958* e = &D_002542D8[sel];
        if (e->fC == 0.0f) {
            func_00194D30(self, 0, -1);
            D_00264A40.f4F44 = e;
            func_0018C568(&D_00264A40);
            func_00160948();
            return;
        }
        func_001BFCD8(0x7B, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    case 17:
        func_00194D30(self, 0, -1);
        D_00264A40.f4F44 = &D_002542D8[sel];
        func_0018C568(&D_00264A40);
        func_00160948();
        return;
    case 11: {
        Ent_195958* e;
        u32 p;
        p = sel * sizeof(Ent_195958);
        p += (u32)D_002542D8;
        e = (Ent_195958*)p;
        D_00264A40.f4F4C = e;
        if (e->fC == 0.0f) {
        c6030:
            Boot_195958* b;
            b = &D_00264A40;
            b->f4F44 = b->f4F4C;
            self->f27C = 0xB;
            if ((((Glob_195958*)D_002623C0)->f19EC & 0x100) == 0) {
                func_00194D30(self, 1, 0x14);
            } else {
                func_00194D30(self, 1, 0xC);
                func_0018B670(&D_00269990, (void*)func_0018C638, b);
            }
            func_00194D30(self, 0, -1);
            return;
        }
        func_00194D30(self, 1, 0xE);
        return;
    }
    case 18:
        if (sel == 0) {
            func_0018B670(&D_00269990, (void*)func_0018C770, &D_00264A40);
            func_00194D30(self, 1, 0x13);
            return;
        }
        func_00194D30(self, 1, -1);
        return;
    case 13:
        func_00194D30(self, 1, -1);
        return;
    case 20: {
        ((Glob_195958*)D_002623C0)->f19EC |= 0x100;
        s32 v = self->f27C;
        switch (v) {
        case 2:
        case 0xB:
            func_00194D30(self, 1, 0xC);
            break;
        case -1:
            func_00194D30(self, 1, -1);
            D_00273EB0.vt->f38(&D_00273EB0);
            break;
        }
        func_0018B670(&D_00269990, (void*)func_0018C638, &D_00264A40);
        return;
    }
    }
}

struct Self_001969F8 {
    u8 pad0[0x14];
    void* p14;
    u8 pad1[0xD0 - 0x18];
    f32 fD0;
    f32 fD4;
    u8 pad2[0x610 - 0xD8];
    void* p610;
    void* p614;
    f32 f618;
    u8 pad3[0x65C - 0x61C];
    void* p65C;
    void* p660;
    void* p664;
    u8 pad4[0x690 - 0x668];
    s32 n690;
    void* p694;
    u8 pad5[0x69C - 0x698];
    u8 list69C[0x6B4 - 0x69C];
    void* p6B4;
    void* p6B8;
};

struct __attribute__((aligned(16))) Quad_001969F8 { s32 a, b, c, d; };
struct Root_001969F8 { u8 pad[0x11]; u8 b11; };
struct Table_001969F8 { u8 pad[0x10]; };
struct Item_001969F8 { u8 pad[0x24]; void* p24; };

struct Any_001969F8;

extern u8 D_0026A738[];
extern u8 D_0021A790[];
extern u8 D_00248D30[];

void func_00124A48(Self_001969F8* self);
void func_00124DF8(Self_001969F8* self, s32 n, void* table);
f32 func_00205778(f32 a, f32 b);
void* func_001B6290(Any_001969F8* a, void* b, s32 c, s32 d);
void* func_00121228(Root_001969F8* root, void* value, Table_001969F8* table);
void func_001299E0(Any_001969F8* a, void* b);
s32 func_0015A4F0(Any_001969F8* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void* func_0018D500(s32 size);
void func_00152470(Any_001969F8* list, void* item);
void func_001B6DF8(Any_001969F8* a, void* b);

void func_001969F8(Self_001969F8* self)
{
    s32 arr[32];
    func_00124A48(self);
    func_00124DF8(self, 0xD, D_0026A738);
    self->f618 = func_00205778(self->fD4, self->fD0);
    self->p614 = func_001B6290((Any_001969F8*)self->p610, self, -1, 1);
    self->p664 = func_00121228((Root_001969F8*)self->p14, self->p65C, (Table_001969F8*)D_0021A790);
    ((Root_001969F8*)self->p664)->b11 = 2;
    func_001299E0((Any_001969F8*)self->p65C, self->p664);
    ((s32*)self->p664)[7] = 1;
    ((Item_001969F8*)self->p664)->p24 = self->p660;
    *(Quad_001969F8*)((u8*)self->p664 + 0x30) = *(Quad_001969F8*)D_00248D30;
    s32 n1 = func_0015A4F0((Any_001969F8*)self->p14, 0x305, 0xF, 0, 0, 0);
    self->n690 = n1;
    void* buf = func_0018D500(n1 * 4);
    self->p694 = buf;
    self->n690 = func_0015A4F0((Any_001969F8*)self->p14, 0x105, 0xF, 0, self->n690, buf);
    s32 cnt = func_0015A4F0((Any_001969F8*)self->p14, 5, 0x44, 0, 0x20, arr);
    for (s32 i = 0; i < cnt; i++) {
        func_00152470((Any_001969F8*)self->list69C, (void*)arr[i]);
    }
    self->p6B8 = func_001B6290((Any_001969F8*)self->p6B4, 0, -1, 0);
    func_001B6DF8((Any_001969F8*)self->p6B8, self);
}

struct Self_1943E8 {
    u8 pad0[0x250];
    s32 f250;
    f32 f254;
    u8 pad258[0x260 - 0x258];
    s32 f260;
    s32 f264;
    u8 pad268[0x274 - 0x268];
    s32 f274;
    u8 pad278[0x27C - 0x278];
    s32 f27C;
    u8 pad280[0x288 - 0x280];
    s32 f288;
};
struct Glob_1943E8 {
    u8 pad0[0x19D8];
    s32 f19D8;
    s32 f19DC;
};
struct Row_1943E8 {
    void* f0;
    u8 pad4[0xC - 0x4];
    s32 fC;
    s32 f10;
    s32* items;
};
struct Obj_1943E8 {
    void** vt;
};
struct Hud_1943E8 {
    void** vt;
    u8 pad4[0x264 - 0x4];
    s32* f264;
    u8 pad268[0x27C - 0x268];
    s32 f27C;
};
struct Pad_1943E8 {
    u8 pad0[0xAA];
    u16 fAA;
};
struct Pool_1943E8 {
    u8 pad0[0x10];
    s32 f10;
};
struct Ent_1943E8 {
    u8 pad0[0xC];
    f32 fC;
    u8 pad10[0x1A5C - 0x10];
};
struct Item_1943E8 {
    u8 pad0[2];
    u8 f2;
};
struct Reg_1943E8 { u64 lo : 12; u64 mid : 11; u64 rest : 41; };
struct RegA_1943E8 { u32 lo : 12; u32 mid : 11; u32 rest : 9; u32 hi; } __attribute__((aligned(8)));
struct Gs_1943E8 {
    u8 pad0[0x18];
    RegA_1943E8 f18;
    u8 pad20[0x20];
    Reg_1943E8 f40;
};

typedef void (*VFn_1943E8)(void* self);
typedef void (*VFnS_1943E8)(void* self, const char* s);

extern Obj_1943E8 D_0026C6C8;
extern Obj_1943E8 D_0026C948;
extern Obj_1943E8 D_0026CBC8;
extern Obj_1943E8 D_0026CE48;
extern Hud_1943E8 D_00274118;
extern Obj_1943E8 D_0026EC70;
extern f32 D_00261868;
extern Pad_1943E8 D_00262C70;
extern Ent_1943E8* D_0026998C;
extern s32 D_00264A58;
extern s32 D_00264A4C;
extern u8 D_0026FF68[];
extern f32 D_0026A22C;
extern f32 D_0026A230;
extern f32 D_0026A700;
extern f32 D_0026A704;
extern char D_0024C588[];
extern char D_0024C5A0[];
extern char D_0024C5B8[];
extern char D_0024C5D0[];
extern char D_0024C600[];
extern char D_0024C618[];

s32 func_00160B28(Glob_1943E8* g);
s32 func_001BE810(void);
s32 func_0011CE30(void);
s32 func_001BE980(void);
s32 func_0016EED0(Pad_1943E8* p);
s32 func_0016EC98(Pad_1943E8* p);
void func_0016EC20(Pad_1943E8* p, s32 mask);
f32 func_0016F108(Pad_1943E8* p, s32 idx);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_00194D30(Self_1943E8* self, s32 a, s32 b);
void func_00195958(Self_1943E8* self);
void func_001961C0(Self_1943E8* self);
void func_00194398(void);
s32 func_0018B770(Pool_1943E8* p);
void func_0018B670(Pool_1943E8* p, void* fn, void* arg);
void func_0018C250(void* arg);
Item_1943E8* func_001F6880(void* a, const char* name);
s32 func_001AEA08(void);
s32 func_001FD7A0(f32 x);

struct Clamp_1943E8 {
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        if (x < lo) {
            return lo;
        }
        if (hi < x) {
            return hi;
        }
        return x;
    }
};

void func_001943E8(Self_1943E8* self)
{
    Glob_1943E8* g = (*(Glob_1943E8**)&D_002623C0);
    Row_1943E8* row = &((Row_1943E8*)&D_00269D50)[self->f260];
    s32 on;
    s32 n;
    Pad_1943E8* pad;

    on = 0;
    switch ((g->f19D8 << 8) | g->f19DC) {
    case 0x106:
    case 0x204:
    case 0x304:
    case 0x307:
    case 0x407:
    case 0x502:
    case 0x504:
        break;
    default:
        on = self->f260 == 0;
        break;
    }
    if (on) {
        ((VFn_1943E8)D_0026C6C8.vt[14])(&D_0026C6C8);
        ((VFn_1943E8)D_0026C948.vt[14])(&D_0026C948);
        ((VFn_1943E8)D_0026CBC8.vt[14])(&D_0026CBC8);
        ((VFn_1943E8)D_0026CE48.vt[14])(&D_0026CE48);
    } else {
        ((VFn_1943E8)D_0026C6C8.vt[15])(&D_0026C6C8);
        ((VFn_1943E8)D_0026C948.vt[15])(&D_0026C948);
        ((VFn_1943E8)D_0026CBC8.vt[15])(&D_0026CBC8);
        ((VFn_1943E8)D_0026CE48.vt[15])(&D_0026CE48);
    }
    switch (self->f260) {
    case 0:
    case 11:
    case 17:
        D_00274118.f27C = func_00160B28((*(Glob_1943E8**)&D_002623C0));
        D_00274118.f264 = &D_00274118.f27C;
        ((VFn_1943E8)D_00274118.vt[14])(&D_00274118);
        break;
    default:
        ((VFn_1943E8)D_00274118.vt[15])(&D_00274118);
        break;
    }
    if (self->f288 != 0) {
        if (func_001BE810() != 0) {
            func_0011CE30();
        }
        self->f288 = func_001BE980();
    }
    s32 ready = 1;
    if (self->f274 != 0 || self->f250 != 2 || !(0.1f < D_00261868 - self->f254)) {
        ready = 0;
    }
    pad = &D_00262C70;
    if (row->f10 == 0) {
        n = 0;
    } else if (row->fC != 0) {
        n = func_0016EED0(pad);
    } else {
        n = func_0016EC98(pad);
    }
    if (n > 0) {
        self->f264 = (self->f264 + 1) % row->f10;
        func_001BFCD8(0x79, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    if (n < 0) {
        self->f264 = (self->f264 + row->f10 - 1) % row->f10;
        func_001BFCD8(0x79, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        return;
    }
    if (!ready) {
        return;
    }
    if (pad->fAA & 0x810) {
        func_0016EC20(&D_00262C70, 0x810);
        func_001961C0(self);
        return;
    }
    if (pad->fAA & 0x80) {
        func_0016EC20(&D_00262C70, 0x80);
        if (self->f260 == 11 || self->f260 == 16) {
            Ent_1943E8* e = &((Ent_1943E8*)&D_002542D8)[row->items[self->f264]];
            if (e->fC != 0.0f) {
                D_0026998C = e;
                func_00194D30(self, 1, 0x12);
            }
        }
        return;
    }
    if (pad->fAA & 0x40) {
        func_0016EC20(&D_00262C70, 0x40);
        func_00195958(self);
        return;
    }
    switch (self->f260) {
    case 24: {
        f32 a = func_0016F108(pad, 0);
        f32 dx = a - func_0016F108(pad, 1);
        f32 b = func_0016F108(pad, 3);
        f32 dy = b - func_0016F108(pad, 2);
        f32 v;
        if (dx == 0.0f && dy == 0.0f) {
            return;
        }
        D_0026A700 = Clamp_1943E8::Of(D_0026A700 + dx * D_0026A22C, 424.0f, 848.0f);
        v = Clamp_1943E8::Of(D_0026A704 + dy * D_0026A230, 10.0f, 90.0f);
        D_0026A704 = v;
        {
            Gs_1943E8* gs = ((Gs_1943E8*)&D_00262490);
            s32 h = func_001FD7A0(D_0026A700);
            Reg_1943E8 ra = gs->f40;
            RegA_1943E8 rb = gs->f18;
            ra.lo = h;
            rb.lo = h;
            gs->f40 = ra;
            gs->f18 = rb;
            s32 w = func_001FD7A0(v);
            ra.mid = w & ~1;
            rb.mid = w & 0x7FE;
            gs->f40 = ra;
            gs->f18 = rb;
        }
        break;
    }
    case 11:
    case 16:
    case 17:
        if (D_00264A58 != 1) {
            func_001961C0(self);
            return;
        } else {
            s32 id = row->items[self->f264];
            if ((u32)(id - 10) < 3) {
                Ent_1943E8* e = &((Ent_1943E8*)&D_002542D8)[id];
                if (self->f260 == 16) {
                    if (e->fC != 0.0f) {
                        ((VFnS_1943E8)D_0026EC70.vt[8])(&D_0026EC70, D_0024C588);
                    } else {
                        ((VFnS_1943E8)D_0026EC70.vt[8])(&D_0026EC70, D_0024C5A0);
                    }
                } else if (self->f260 == 17) {
                    if (e->fC != 0.0f) {
                        ((VFnS_1943E8)D_0026EC70.vt[8])(&D_0026EC70, D_0024C5B8);
                    } else {
                        ((VFnS_1943E8)D_0026EC70.vt[8])(&D_0026EC70, D_0024C5A0);
                    }
                } else {
                    if (e->fC != 0.0f) {
                        ((VFnS_1943E8)D_0026EC70.vt[8])(&D_0026EC70, D_0024C5D0);
                    } else {
                        ((VFnS_1943E8)D_0026EC70.vt[8])(&D_0026EC70, D_0024C600);
                    }
                }
                ((VFn_1943E8)D_0026EC70.vt[14])(&D_0026EC70);
            } else {
                ((VFn_1943E8)D_0026EC70.vt[15])(&D_0026EC70);
            }
        }
        break;
    case 18:
        if (D_00264A58 != 1) {
            func_001961C0(self);
        }
        break;
    case 20: {
        Item_1943E8* it;
        if (D_00264A58 != 1) {
            func_001961C0(self);
        }
        it = func_001F6880(row->f0, D_0024C618);
        if (it != 0) {
            it->f2 = func_001AEA08();
        }
        break;
    }
    case 3:
    case 4:
    case 7:
    case 10:
    case 32:
        if (D_00264A4C == 5) {
            func_00194D30((Self_1943E8*)D_0026FF68, 1, -1);
        }
        break;
    case 5: {
        Pool_1943E8* p = ((Pool_1943E8*)&D_00269990);
        if (func_0018B770(p) == 0) {
            if (p->f10 == 0) {
                func_0018B670(p, (void*)(void (*)(Boot_195958*))func_0018C250, ((u8*)&D_00264A40));
                func_00194D30(self, 1, 8);
            } else {
                func_00194D30(self, 1, 6);
            }
        }
        break;
    }
    case 8: {
        Pool_1943E8* p = ((Pool_1943E8*)&D_00269990);
        if (func_0018B770(p) == 0) {
            if (p->f10 == 0) {
                func_00194D30(self, 1, -1);
            } else {
                func_00194D30(self, 1, 9);
            }
        }
        break;
    }
    case 12: {
        Pool_1943E8* p = ((Pool_1943E8*)&D_00269990);
        if (func_0018B770(p) == 0) {
            if (p->f10 == 0) {
                func_00194D30(self, 1, -1);
                if (self->f27C == 2) {
                    func_00194398();
                }
            } else {
                func_00194D30(self, 0, 0x17);
                func_00194D30(self, 1, 0xF);
            }
        }
        break;
    }
    case 19: {
        Pool_1943E8* p = ((Pool_1943E8*)&D_00269990);
        if (func_0018B770(p) == 0) {
            D_0026998C = 0;
            if (p->f10 == 0) {
                func_00194D30(self, 1, -1);
            } else {
                func_00194D30(self, 0, 0x17);
                func_00194D30(self, 1, 0xF);
            }
        }
        break;
    }
    }
}
