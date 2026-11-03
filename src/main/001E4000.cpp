// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern s32 D_00261990;
extern f32 D_00261858[];
extern u8* D_00275710;


struct Ret_1E4880 { u8 pad[0x20]; f32 value; };

f32 func_001E4880(void* a0, void* a1, void* a2, Ret_1E4880* a3)
{
    return a3->value;
}

void func_001F5C0C(void* p, s32 v, s32 n);

struct Ctor_1E4E38 { s32 f0; s32 f4; s32 f8; s32 fC; s32 f10; u8 body[0x20]; };

Ctor_1E4E38* func_001E4E38(Ctor_1E4E38* self)
{
    self->f4 = 0;
    self->f10 = 0;
    self->fC = self->f8 = -1;
    func_001F5C0C(self->body, 0, 0x20);
    return self;
}

struct Blk_1E4E80 { s32 state; s32 a; s32 b; s32 c; s32 d; };

void func_001E4E80(Blk_1E4E80* self, s32 a1, s32 a2, s32 a3, s32 a4)
{
    if (self->state == 0) {
        self->state = 1;
        self->a = a1;
        self->b = a2;
        self->c = a3;
        self->d = a4;
    }
}

extern u8 D_00275AF0[];

void func_001E4E38(void* item);

void func_001E5328(void* owner, s32 code)
{
    if (code == 0xFFFF && owner != 0) {
        func_001E4E38(D_00275AF0);
    }
}

void func_001E5328(void* owner, s32 code);

void func_001E5358(void)
{
    func_001E5328((void*)1, 0xFFFF);
}

struct Blk_1E5278 { u8 pad[0x14]; };
struct Ring_1E5278 { s32 w; };

extern u8 D_00261420[];
extern u8 D_00275AF0[];

void func_001C05D0(f32 x);
void func_00140ED0(Ring_1E5278* r);
void func_001E4E80(Blk_1E5278* self, u8* p, s32 a, s32 b, s32 c);

void func_001E5278(s32 mode)
{
    s32 n;
    func_001C05D0(0.0f);
    switch (mode) {
    case 0:
        n = 0;
        break;
    case 1:
        func_00140ED0((Ring_1E5278*)D_00261420);
        return;
    case 2:
        n = 2;
        break;
    case 3:
        n = 4;
        break;
    }
    func_001E4E80((Blk_1E5278*)D_00275AF0, D_00275AF0 + 0x14, -1, -1, n);
}

struct Blob_1E4EA8 { u32 w[8]; };
struct Eq_1E4EA8 {
    static s32 Of(Blob_1E4EA8* a, Blob_1E4EA8* b)
    {
        if (a == b) return 1;
        if (b == 0) return 0;
        return ((a->w[2] ^ a->w[6]) ^ (b->w[2] ^ b->w[6])) == 0;
    }
};
struct Key_1E4EA8 { s32 a; s32 b; };
struct VT_1E4EA8 { u8 pad[0x38]; void (*m38)(void*, void*); };
struct VT1_1E4EA8 { u8 pad[0x38]; void (*m38)(void*); };
struct Mgr_1E4EA8 { VT_1E4EA8* vt; u8 pad04[0x1D78]; f32 f1D7C; };
struct Self_1E4EA8 { s32 f0; Blob_1E4EA8* f4; s32 f8; s32 fC; s32 f10; Blob_1E4EA8 f14; };
struct __attribute__((packed)) Word_1E4EA8 { u32 v; };
struct Sub_1E4EA8 {
    s32 pad[0xC]; void* f30; s32 pad34[3]; s32 pad40[8];
    void SetOwner(void* o) { f30 = o; }
};
struct Obj30_1E4EA8 { s32 pad[10]; };
struct Cur_1E4EA8 { u8 pad[0x19D8]; s32 f19D8; s32 f19DC; u32 f19E0; };
struct Cur2_1E4EA8 { u8 pad[0x19D8]; s32 f19D8; s32 f19DC; u32 pad19E0[3]; u32 f19EC; };
struct Pl_1E4EA8 { u8 pad[0x4F44]; Cur_1E4EA8* f4F44; };
struct Vo_1E4EA8 { void* vt; };

extern u8 D_002C3B00[];
extern u8 D_00261EF0[];
extern u8 D_002623D8[];
extern u8 D_0026FA90[];
extern f32 D_0026186C;
extern Vo_1E4EA8 D_0026C6C8;
extern Cur2_1E4EA8* D_002623C0;
extern Pl_1E4EA8 D_00264A40;

void func_00191E70(s32 a);
void func_0018D410(Key_1E4EA8* q);
Obj30_1E4EA8* func_00193210(Obj30_1E4EA8* q, Word_1E4EA8* a, Word_1E4EA8* b, Word_1E4EA8* c, Word_1E4EA8* d);
void func_00137290(Sub_1E4EA8* q, s32 a, u8* b, s32 c);
void func_00193270(void* q);
s32 func_001373B0(Sub_1E4EA8* q, Key_1E4EA8* k);
void func_001372E0(Sub_1E4EA8* q, s32 n);
void func_001DB838(Mgr_1E4EA8* q);
void func_001DB928(s32 a, Sub_1E4EA8* q);
void func_001430B8(u8* q, f32 v);
void func_0016E0F0(s32 n);
void func_00160690(Blob_1E4EA8* q, s32 n);
Mgr_1E4EA8* func_0011E580(s32 a, s32 b, s32 c, s32 d, s32 e);
void func_001C06A0(s32 a, s32 b, f32 x);
void func_001373D0(Sub_1E4EA8* q);
void func_00193300(void* q);
void func_0018C7F8(Pl_1E4EA8* q);
void func_00143A60(s32 q, s32 f);
void func_001C0070(void);
void func_001F4318(Mgr_1E4EA8* q, s32 a, s32 b);
void func_00151E18(u8* q);
void func_00160CE8(u8* q);
void func_0016B520(u8* q);
void func_00138C00(Mgr_1E4EA8* q, s32 n);
void func_00143E40(s32 q, s32 n, f32 v);
void func_00142ED0(f32 x);
void func_001C06D8(void);
void func_00191EB0(s32 a);

void func_001E4EA8(Self_1E4EA8* self)
{
    Key_1E4EA8 key;
    Blob_1E4EA8 blob;
    Obj30_1E4EA8 o30;
    Word_1E4EA8 w60, w70, w80, w90;
    Sub_1E4EA8 sub;
    func_00191E70(2);
    if (self->f4 != 0) {
        func_0018D410(&key);
        blob = *self->f4;
        self->f4 = 0;
        key.b = blob.w[1] ^ blob.w[7];
        key.a = blob.w[0] ^ blob.w[5];
        if (key.b == 0) goto end;
        {
            Blob_1E4EA8* s2 = &self->f14;
            s32 ne = !Eq_1E4EA8::Of(&blob, s2);
            w60.v = 0x3F00;
            w70.v = 0x3F3F3F;
            w80.v = 0x3F3F;
            w90.v = 0x3F;
            func_00193210(&o30, &w60, &w70, &w80, &w90);
            func_00137290(&sub, 0x340C00, D_002C3B00, 6);
            sub.SetOwner(&o30);
            if (sub.f30 != 0) func_00193270(sub.f30);
            if (func_001373B0(&sub, &key) == 0) {
                func_001372E0(&sub, 2);
                goto end;
            }
            func_001DB838((*(Mgr_1E4EA8**)&D_00275710));
            (*(Mgr_1E4EA8**)&D_00275710) = 0;
            func_001DB928(ne, &sub);
            func_001430B8(((u8*)&D_00261858), 0.0f);
            func_0016E0F0(0x80);
            self->f14 = blob;
            func_00160690(s2, self->f10);
            (*(Mgr_1E4EA8**)&D_00275710) = func_0011E580(0x6C, 0, 0, 3, -1);
            func_001C06A0(0xA, 0, 0.0f);
            (*(Mgr_1E4EA8**)&D_00275710)->vt->m38((*(Mgr_1E4EA8**)&D_00275710), &sub);
            func_001373D0(&sub);
            if (sub.f30 != 0) func_00193300(sub.f30);
            if (D_002623C0->f19EC & 0x100) {
                Cur_1E4EA8* c = D_00264A40.f4F44;
                if (c != 0 && (c->f19D8 != D_002623C0->f19D8 || c->f19DC != D_002623C0->f19DC))
                    func_0018C7F8(&D_00264A40);
            }
            func_001372E0(&sub, 2);
        }
    }
    func_00143A60((*(s32*)&D_00261990), 1);
    func_001C0070();
    func_001C06A0(0xA, 0, 1.0f);
    func_001F4318((*(Mgr_1E4EA8**)&D_00275710), self->f8, self->fC);
    func_00151E18(D_00261EF0);
    func_00160CE8(D_002623D8);
    func_0016B520(D_0026FA90);
    func_00138C00((*(Mgr_1E4EA8**)&D_00275710), 0);
    func_00143E40((*(s32*)&D_00261990), 0, D_0026186C);
    if (self->f10 & 0x10) ((VT1_1E4EA8*)D_0026C6C8.vt)->m38(&D_0026C6C8);
    func_00142ED0(1.0f);
end:
    func_001C06D8();
    func_001C06A0(1, 1, (*(Mgr_1E4EA8**)&D_00275710)->f1D7C);
    func_00191EB0(2);
    self->f0 = 0;
}
