// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "c4c.h"

s32 D_00274F38[8] = { 0x12, 0x404, 0x1008, 0x40, 0x80, 0x200, 0x8000, 0 };
const char* D_00274F58[7] = { "&2T&.: Dive", "&2T&.: Roll", "&2T&.: Slow", "&2T&.: Mine", "&2T&.: Fast", "&2T&.: Decoy", "&2T&.: Stun" };
s32 D_00274F74 = -1;
float D_00274F78[3] = {2.0f, 0.0f, 0.100000001f};
float D_00274F84 = 1.5f;
float D_00274F88[2] = {0.25f, 0.0f};
s32 D_00274F90[4] = { 0x22, 0x152, 0x558, 0 };

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


extern s32 D_00262E10;

void* func_001BC320(C03* a);
void func_001861E8(void* a, s32 b);

void func_001BC4D8(void* self, void* sub);

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 a1, void* a2);

struct Msg_D32D8 {
    void* self;
    void* v;
};

void func_00158730(void* x);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
void func_001837E0(void* self, s32 a, s32 b, s32 c);

struct Item_1D31D0 { u8 pad[0x7E0]; void* obj; };
struct Obj_1D31D0 { u8 pad0[0x14]; void* f14; u8 pad1[0x2758 - 0x18]; f32 f2758; s32 f275C; };

struct T_1D31D0 { f32 a; f32 b; };
extern T_1D31D0 D_00261858;

s32 func_0015A4F0(void* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void func_0012F0A0(void* obj, s32 a1, f32 fa, f32 fb);


extern u8 D_00248D30[];
void func_001B9338(C03* self, f32 t);
void func_00189378(Mat02* sub, s32 zero, void* out);
void func_001B91A8(C03* self, void* buf, s32 a, void* p, s32 b, f32 t);

struct Msg_001D3678 { s32 value; };

extern u8 D_00248D20[];

void func_00127378(C02* self, s32 kind, Msg_001D3678* msg);
void func_00185D20(f32 f, void* a0, void* a1, void* a2, void* a3, s32 a4, s32 a5, s32 a6, void* a7);

struct Self_1D3100 { u8 pad[0xAA]; u16 flags; };
void func_0016EC20(Self_1D3100* self, s32 mask);
s32 func_00160D10(void);

struct Vt_1D29C8 { u8 pad0[0x20]; void (*fn20)(void* self, s32 a); u8 pad24[0x14]; void (*fn38)(void* self); };
struct Obj_1D29C8 { Vt_1D29C8* vt; };
struct Sub_1D29C8;
struct Ctx_1D29C8 {
    u8 pad0[0x1518];
    Sub_1D29C8* f1518;
    u8 pad151C[0xD04];
    s32 f2220;
    u8 pad2224[0x52C];
    Sub_1D29C8* f2750;
};
struct Glob_1D29C8 {
    u8 pad0[0x19FC];
    u32 f19FC;
};

extern Glob_1D29C8* D_002623C0;
extern f32 D_00261854;
extern Obj_1D29C8 D_0026EC70;

void func_00175170(Ctx_1D29C8* self, s32 a, s32 b);
s32 func_00182FC8(Sub_1D29C8* self);
void func_00126D60(Sub_1D29C8* self, f32 v);
void func_001D32D8(Sub_1D29C8* self, Ctx_1D29C8* a, s32 b);
void func_001D31D0(Ctx_1D29C8* self, s32 a);
void* func_001925F0(void);
void func_001AA8B8(Obj_1D29C8* self, f32 v);
void func_001AA788(Obj_1D29C8* self, f32 v);

void func_001D29C8(u32 mode);
s32 func_001D3100(Self_1D3100* self, s32 start, s32 count, s32* table);
void func_001D31D0(Obj_1D31D0* self, s32 value);
void func_001D32D8(C4C* self, void* v, s32 flag);
void* func_001D3500(C4C* a0, Node_D3500* a1);
void func_001D3678(C4C* self, s32 kind, Msg_001D3678* msg);

void func_001D29C8(u32 mode)
{
    switch (D_00274F74) {
    case 1:
        if ((*(Ctx_1D29C8**)&D_00262E10) == 0)
            goto tail;
        if ((*(Ctx_1D29C8**)&D_00262E10)->f2220 == 0xD)
            func_00175170((*(Ctx_1D29C8**)&D_00262E10), 0, -1);
        break;
    case 3:
        if ((*(Ctx_1D29C8**)&D_00262E10) == 0)
            goto tail;
        if ((*(Ctx_1D29C8**)&D_00262E10)->f1518 != 0) {
            if (func_00182FC8((*(Ctx_1D29C8**)&D_00262E10)->f1518) != 0)
                func_00126D60((*(Ctx_1D29C8**)&D_00262E10)->f1518, 0.5f);
        }
        break;
    }
    if ((*(Ctx_1D29C8**)&D_00262E10) != 0) {
        D_00261854 = 1.0f;
        if ((*(Ctx_1D29C8**)&D_00262E10)->f2750 != 0) {
            if (func_00182FC8((*(Ctx_1D29C8**)&D_00262E10)->f2750) != 0)
                func_001D32D8((*(Ctx_1D29C8**)&D_00262E10)->f2750, (*(Ctx_1D29C8**)&D_00262E10), 1);
        }
        func_001D31D0((*(Ctx_1D29C8**)&D_00262E10), 0);
        if ((*(Ctx_1D29C8**)&D_00262E10) != 0) {
            if ((void*)(*(Ctx_1D29C8**)&D_00262E10) == func_001925F0())
                D_00274F74 = mode;
        }
    }
tail:
    if (mode != D_002623C0->f19FC && mode < 7) {
        func_001AA8B8(&D_0026EC70, ((*(Ctx_1D29C8**)&D_00262E10) != 0 && (void*)(*(Ctx_1D29C8**)&D_00262E10) == func_001925F0()) ? 3.0f : 8.0f);
        func_001AA788(&D_0026EC70, 0.6f);
        D_0026EC70.vt->fn20(&D_0026EC70, (s32)D_00274F58[mode]);
        D_0026EC70.vt->fn38(&D_0026EC70);
        D_002623C0->f19FC = mode;
    }
}

INCLUDE_RODATA(jtbl_0024DB90);
INCLUDE_RODATA(jtbl_0024DBB0);
ASM_FUNC(func_001D2BB8);

s32 func_001D3100(Self_1D3100* self, s32 start, s32 count, s32* table)
{
    s32 step;
    s32 left;
    s32 idx;

    if ((self->flags & 3) == 0) {
        return start;
    }
    step = (self->flags & 1) ? -1 : 1;
    func_0016EC20(self, 3);
    idx = start;
    left = count;
    do {
        if (--left < 0) {
            return start;
        }
        idx += step;
        if (idx < 0) {
            idx = count - 1;
        } else if (idx >= count) {
            idx = 0;
        }
    } while (!(func_00160D10() & table[idx]));
    return idx;
}

void func_001D31D0(Obj_1D31D0* self, s32 value)
{
    void* buf[0x100];
    if (value == self->f275C) {
        return;
    }
    s32 n = func_0015A4F0(self->f14, 0x105, 8, 0, 0x100, buf);
    for (s32 i = 0; i < n; i++) {
        Item_1D31D0* item = (Item_1D31D0*)buf[i];
        if (item->obj != 0) {
            func_0012F0A0(item->obj, 1, 0.0f, value != 0 ? 0.0f : 1.0f);
        }
    }
    self->f275C = value;
    self->f2758 = D_00261858.b;
}

void func_001D3290(C4C* self)
{
    func_00124A48(self);
    func_00124DF8(self, 1, D_00274F90);
    self->desc->m03(self);
}

void func_001D32D8(C4C* self, void* v, s32 flag)
{
    if (flag == 0) {
        Msg_D32D8 msg;
        msg.v = v;
        msg.self = self;
        self->desc->m0E(self, 0x17, &msg);
        self->count = self->count - 1;
        if (self->count > 0) {
            return;
        }
    }
    func_00158730(self->f558);
    func_001BFCD8(0x67, 0, 0, (s32)&self->v140, 0, 0, 4000.0f, 750.0f, 1.0f, 0.0f, 0.0f);
    func_001837E0(self, 2, 0, 0);
    self->desc->m03(self);
}

ASM_FUNC(func_001D3398);

void func_001D3470(C4C* self, f32 t)
{
    u8 buf[0x30];

    func_001B9338(self, t);
    if (self->parent == 0) {
        func_00189378(&self->rot, 0, buf);
        func_001B91A8(self, buf, (s32)self->p214, D_00248D30, (s32)self->p218, t);
    }
}

void func_001D34E0(C4C* self)
{
    func_001BC4D8(self, &self->f554);
}

void* func_001D3500(C4C* a0, Node_D3500* a1)
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
        func_001861E8(a0->world, a0->f554);
        a0->f554 = 0;
    }
    return r;
}

ASM_FUNC(func_001D35A8);

void func_001D3678(C4C* self, s32 kind, Msg_001D3678* msg)
{
    func_00127378(self, kind, msg);
    if (kind == 10) {
        func_00185D20(0.0f, self, (void*)msg->value, &self->v140, D_00248D20, 10, 0, 0, &self->f554);
    }
}
