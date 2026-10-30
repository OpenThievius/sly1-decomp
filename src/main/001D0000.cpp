// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Obj_D27C0 {
    u8 pad0[0x14];
    void* owner;
    u8 pad1[0x2718 - 0x18];
    s32 state;
};

void func_001DDA20(void* a);
void func_001DDB58(void* a);
void func_001DDA50(void* a);
void func_001DDBB8(void* a);

void func_001D27C0(Obj_D27C0* a0, s32 a1)
{
    if (a0->state != a1) {
        if (a0->state == -1) {
            func_001DDA20(a0->owner);
            func_001DDB58(a0->owner);
        }
        a0->state = a1;
        if (a1 == -1) {
            func_001DDA50(a0->owner);
            func_001DDBB8(a0->owner);
        }
    }
}

struct Ref_D3500;

struct Node_D3500 {
    Ref_D3500* ref;
    u8 pad0[0xC - 4];
    s32 flags;
};

struct Ref_D3500 {
    s32* vtbl;
    u8 pad0[0x18 - 4];
    Ref_D3500* f18;
    u8 pad1[0x50 - 0x1C];
    s32 f50;
};

struct Self_D3500 {
    u8 pad0[0x14];
    void* f14;
    u8 pad1[0x554 - 0x18];
    s32 f554;
};

extern s32 D_00262E10;

void* func_001BC320(Self_D3500* a);
void func_001D32D8(Self_D3500* a, Ref_D3500* b, s32 c);
void func_001861E8(void* a, s32 b);

void* func_001D3500(Self_D3500* a0, Node_D3500* a1)
{
    void* r = func_001BC320(a0);
    if (r != 0 && (a1->flags & 0x20)) {
        Ref_D3500* a2 = a1->ref;
        s32 v1;
        if (a2->vtbl[2] & 1) {
            v1 = a2->f50;
        } else {
            v1 = a2->f18->f50;
        }
        func_001D32D8(a0, a1->ref, (v1 ^ D_00262E10) == 0);
        func_001861E8(a0->f14, a0->f554);
        a0->f554 = 0;
    }
    return r;
}

struct Thing_1D1200 {
    u8 pad0[0x2674];
    s32 f2674;
    s32 f2678;
    u8 pad1[0x2684 - 0x267C];
    s32 f2684;
    f32 f2688;
    s32 f268C;
    u8 pad2[0x26A0 - 0x2690];
    s32 f26A0;
};

extern f32 D_0026185C;

void func_001D1200(Thing_1D1200* self, s32 n)
{
    if (n == self->f2684) {
        return;
    }
    self->f2684 = n;
    self->f2688 = D_0026185C;
    self->f26A0 = 0;
    if (n <= 0) {
        return;
    }
    if (n >= 3) {
        if (n == 3) {
            self->f268C = 1;
        }
        return;
    }
    {
        s32 v = self->f2674;
        if (v == self->f2678) {
            self->f268C = 2;
        } else {
            self->f268C = 0;
        }
    }
}

struct __attribute__((aligned(16))) Blob_274E60_1D1260 { u8 bytes[0x90]; };

struct __attribute__((aligned(16))) Obj_1D1260 {
    u8 p0[0x2D4];
    s32 f2D4;
    u8 p1[4];
    s32 f2DC;
    u8 p2[4];
    s32 f2E4;
    u8 p3[0x2F0 - 0x2E8];
    Blob_274E60_1D1260 blob;
    s32 f380;
    s32 f384;
    s32 f388;
    u8 p4[0x390 - 0x38C];
    s32 f390;
    u8 p5[0x3A0 - 0x394];
    s32 f3A0;
    u8 p6[0x414 - 0x3A4];
    s32 f414;
    s32 f418;
    s32 f41C;
};

struct Thing_1D1260 {
    u8 pad0[0x2678];
    Obj_1D1260* f2678;
};

extern Blob_274E60_1D1260 D_00274E60;

void func_001E2840(Obj_1D1260* o, s32 v);

void func_001D1260(Thing_1D1260* self)
{
    Obj_1D1260* o = self->f2678;
    o->f414 = 5;
    o->f2D4 = 0;
    o->f2DC = 0;
    o->f2E4 = 0;
    o->blob = D_00274E60;
    o->f418 = 1;
    o->f388 = 3;
    o->f380 = 0;
    o->f384 = 0;
    o->f41C = 0;
    o->f390 = 0;
    o->f3A0 = 0;
    func_001E2840(o, 0);
}

struct Self_1D1478 { u8 pad[0x14]; void* f14; };
struct Obj_1D1478 { u8 pad[0x50]; s32 f50; };
s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
s32 func_001D1478(Self_1D1478* self)
{
    void* arr[64];
    s32 n = func_0015A4F0(self->f14, 5, 0x89, 0, 0x40, arr);
    for (s32 i = 0; i < n; i++) {
        Obj_1D1478* o = (Obj_1D1478*)arr[i];
        s32 v = o->f50;
        if (v < 3) {
            if (v > 0) {
                return 0;
            }
        }
    }
    return 1;
}

void func_001BC4D8(void* self, void* sub);

void func_001D34E0(void* self)
{
    func_001BC4D8(self, (u8*)self + 0x554);
}

typedef void (*VFn_1D3290)(void* self);
struct Obj_1D3290 { VFn_1D3290* vtbl; };

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a1, void* a2);
extern u8 D_00274F90[];

void func_001D3290(Obj_1D3290* self)
{
    func_00124A48(self);
    func_00124DF8(self, 1, D_00274F90);
    self->vtbl[7](self);
}

// NEAR: argument setup order of the func_0012CD78 calls differs ($a1 load and the $f12/$f13 constants in the loop call, $a4 address and float moves in the two calls after it); stores and frame match.

struct Entry_1D14F0 {
    u8 pad0[4];
    void* p4;
    u8 pad8[4];
    f32 fC;
};

struct Self_1D14F0 {
    u8 pad0[0x614];
    void* f614;
    void* f618;
    u8 pad61C[0x103C - 0x61C];
    Entry_1D14F0 entries[2];
    u8 f105C[4];
    u8 pad1060[4];
    void* f1064;
    u8 pad1068[0x23E0 - 0x1068];
    f32 f23E0;
    f32 f23E4;
    u8 pad23E8[8];
    f32 f23F0;
    f32 f23F4;
};

void func_00139038(void* self, s32 a1, s32 a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);
void func_0012CD78(f32 f12, f32 f13, void* a0, void* a1, void* a2, s32 a3, void* a4, s32 a5, void* a6, s32 a7);

void func_001D14F0(Self_1D14F0* self)
{
    f32 out[4];
    Entry_1D14F0* e = self->entries;
    s32 i = 1;
    do {
        func_0012CD78(0.0f, 1.0f, e->p4, self->f614, self, 1, 0, 0, out, 0);
        e->fC = out[2];
        e++;
        i--;
    } while (i >= 0);
    func_00139038(self, 0x10, 2, self->entries, 0, 0, 0, &self->f105C);
    func_0012CD78(0.0f, 1.0f, self->f1064, self->f618, self, 1, &self->f23E0, 0, 0, 0);
    func_0012CD78(0.0f, 1.0f, self->f1064, self->f614, self, 1, &self->f23F0, 0, 0, 0);
    f32 avg = (self->f23E0 + self->f23F0) * 0.5f;
    self->f23F4 = 0.0f;
    self->f23E4 = 0.0f;
    self->f23F0 = avg;
    self->f23E0 = avg;
}

f32 func_001FD578(u64 v);

s32 func_001D3C68(s32 stride, s32 n, s32 m, char* out, ...) {
    f32 rows[16];
    f32 cols[16];
    u64* ap = (u64*)((char*)__builtin_next_arg(out) - 32);
    f32 sum = 0.0f;
    s32 i;
    s32 j;
    s32 changed;
    for (i = 1; i < n; i++) {
        ap++;
        rows[i] = func_001FD578(ap[-1]);
        sum += rows[i];
    }
    rows[0] = 1.0f - sum;
    sum = 0.0f;
    for (j = 1; j < m; j++) {
        ap++;
        cols[j] = func_001FD578(ap[-1]);
        sum += cols[j];
    }
    cols[0] = 1.0f - sum;
    char* p = out;
    changed = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            sum = rows[i] * cols[j];
            if (sum != *(f32*)p) {
                *(f32*)p = sum;
                changed = 1;
            }
            p += stride;
        }
    }
    return changed;
}

struct Self_1D32D8 {
    void** vt;
    u8 pad0[0x140 - 4];
    u8 f140[0x550 - 0x140];
    s32 f550;
    u8 pad2[4];
    void* f558;
};

enum Kind_1D32D8 { };

void func_00158730(void* x);
void func_001837E0(Self_1D32D8* self, s32 a, s32 b, s32 c);
void func_001BFCD8(Kind_1D32D8 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

void func_001D32D8(Self_1D32D8* self, s32 a1, s32 a2)
{
    s32 args[2];
    if (a2 == 0) {
        args[1] = a1;
        args[0] = (s32)self;
        ((void (*)(Self_1D32D8*, s32, s32*))self->vt[18])(self, 0x17, args);
        self->f550 = self->f550 - 1;
        if (self->f550 > 0) {
            return;
        }
    }
    func_00158730(self->f558);
    func_001BFCD8((Kind_1D32D8)0x67, 0, 0, self->f140, 4000.0f, 750.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    func_001837E0(self, 2, 0, 0);
    ((void (*)(Self_1D32D8*))self->vt[7])(self);
}

struct Node_1D3470;
struct Sub_1D3470;

struct Node_1D3470 {
    u8 pad0[0x18];
    s32 w18;
    u8 pad1[0x214 - 0x1C];
    s32 w214;
    s32 w218;
};

extern u8 D_00248D30[];
void func_001B9338(Node_1D3470* self, f32 t);
void func_00189378(Sub_1D3470* sub, s32 zero, void* out);
void func_001B91A8(Node_1D3470* self, void* buf, s32 a, void* p, s32 b, f32 t);

void func_001D3470(Node_1D3470* self, f32 t)
{
    u8 buf[0x30];

    func_001B9338(self, t);
    if (self->w18 == 0) {
        func_00189378((Sub_1D3470*)((u8*)self + 0xD0), 0, buf);
        func_001B91A8(self, buf, self->w214, D_00248D30, self->w218, t);
    }
}

struct Self_001D3678 { s32 pad; };
struct Msg_001D3678 { s32 value; };

extern u8 D_00248D20[];

void func_00127378(Self_001D3678* self, s32 kind, Msg_001D3678* msg);
void func_00185D20(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);

void func_001D3678(Self_001D3678* self, s32 kind, Msg_001D3678* msg)
{
    func_00127378(self, kind, msg);
    if (kind == 10) {
        func_00185D20(0.0f, self, (void*)msg->value, (u8*)self + 0x140, D_00248D20, 10, 0, 0, (u8*)self + 0x554);
    }
}
