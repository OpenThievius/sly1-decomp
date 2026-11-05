// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "c7e.h"
#include "c66.h"
#include "c6c.h"
#include "globals.h"
#include "g27c220.h"
#include "r11b008.h"
#include "shapes.h"
extern const f32 D_0024D2A0[2] = { 3.4028235e38f, 0.0f };
#include "list_iter.h"

void func_00130110(void* p);


void func_001C27B0(s32 a, s32 b);


s32 func_0011D4E0(s32 flag);


struct Pk8_1C0A50 { u64 v; } __attribute__((packed));
struct Ent_1C0A50 { s32 key; Pk8_1C0A50 a; Pk8_1C0A50 b; };

extern Pk8_1C0A50 D_00274820;
extern Pk8_1C0A50 D_00274828;


extern s32 D_00274728;
extern s32 D_006053E0[];

s32 func_0011D8F0(s32 a, s32 b);


void func_00182ED0(void* self);
void func_00152600(void* table, void* self);




extern s32 D_006053E0[];


void func_001C0C08(s32 index, s32 value);


void func_00124A48(void* self);

void func_001B6438(s32 p);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
s32 func_001B6290(s32 p, void* ctx, s32 a2, s32 a3);


void func_00182D48(void* self);
void func_00152470(void* table, void* self);


void func_001830D8(void* self);


struct Entry_1C1390 { s32 key; void* value; };

extern u8 D_00259F38[];
void func_0011A6C0(void* a, void* b);


void func_0011D480(s32 a, s32 b);


extern s32 D_00274808[6];

void func_0011E328(s32 a, s32 b);
void func_0011E360(s32 a, s32 b, s32 c);


struct Pt_1C0AB8 { f32 x; f32 y; };
struct Ent_1C0AB8 { s32 key; f32 a0; f32 a1; f32 b0; f32 b1; };


extern f32 D_00274838[11][4];

void func_0011D480(s32 slot, s32 value);


extern f32 D_00274838[11][4];

void func_001C0600(s32 column);


struct __attribute__((packed)) Pk8_1C0B38 { u64 v; };
struct Ent_1C0B38 { s32 key; Pk8_1C0B38 a; Pk8_1C0B38 b; };

extern u8 D_002748E8[4];

void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, void* a4, void* a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);


struct Packed_001C0B08 { u64 value; } __attribute__((packed));


void func_0011E010(void);
s32 func_0011CE30(void);
void func_0011E110(s32 a0);
void func_0011E1F8(s32 flag);
void func_001C0808(s32 a0);
void func_001BEE48(void);
void func_001C0CB0(void);


struct Rec_1C1530 { s32 a; R11B008Node* head; s32 cnt; };
typedef void (*Cb_1C1530)(void* a, void* b);


struct Obj_1C2238 { u8 pad[4]; R11B008List* f4; };
void* func_001C14C0(void* a, s32 b);
void func_001C1F20(R11B008* self, void* a, void* b, R11B008* c);


struct Obj_1C22B8 { u8 pad[4]; R11B008List* f4; };
void func_00130110(void* p);


void func_001C06A0(s32 a, s32 b, f32 x);


struct Ring_1C25B0 {
    s32 f0;
    s32 f4;
    s32 f8[8];
    s32 f28[0x20 / 4];
    s32 f48;
    s32 f4C;
};

struct Dma_1C25B0 {
    s32 f0;
    u8 pad4[0x7C];
    s32 f80;
};

extern Dma_1C25B0* D_00261F20;
void func_00202C38(Dma_1C25B0* d, s32 b, s32 c);
void func_00202B68(Dma_1C25B0* d);


extern f32 D_00274758[11][4];

void func_0018D800(void* dst, void* src, s32 count);


struct Pair_1C08B0 { s32 a; s32 b; };
struct Stack_1C08B0 { u8 pad0[0x2328]; Pair_1C08B0 pairs[4]; s32 count; };

extern s32 D_00274808[];

void func_0011E328(s32 channel, s32 value);
void func_0011E360(s32 channel, s32 value, s32 value2);


struct Pair_1C0950 { s32 a; s32 b; };
struct Stack_1C0950 { u8 pad0[0x2328]; Pair_1C0950 pairs[4]; s32 count; };

extern s32 D_00274808[];

void func_0011E328(s32 channel, s32 value);
void func_0011E360(s32 channel, s32 value, s32 value2);


struct List_1C1A28 { s32 type; R11B008Node* head; R11B008Node* tail; };
struct Desc_1C15D8;
typedef void (*Get_1C15D8)(void* obj, void* out);
typedef void* (*Base_1C15D8)(void* obj, s32 z);
struct Desc_1C15D8 {
    s32 kind;
    u32 flags;
    s32 pad8;
    s32 off;
    s32 imm;
    s32 imm2;
    s32 pad18;
    Base_1C15D8 base;
};

void func_001F5C0C(void* p, s32 v, s32 n);
void func_001C15D8(R11B008* t, s32 value, Desc_1C15D8* d);


s32 func_001C0CF0(void);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);



struct KeyPair_1C14C0 { s32 key; s32 value; };
struct KeyTable_1C14C0 { s32 count; KeyPair_1C14C0* items; };
struct KeyRef_1C14C0 { s32 pad0; s32 index; };
struct KeyHolder_1C14C0 { KeyRef_1C14C0* ref; };

extern KeyTable_1C14C0 D_00244950[];


struct TabA_24D2A8 { s32 v[42]; };
struct TabB_24D350 { s32 v[25]; };
extern const TabA_24D2A8 D_0024D2A8;
extern const TabB_24D350 D_0024D350;
extern s32 D_00274830;
s32 func_001EAA70(s32 a, s32 b);


// (if/else with the small path first moved $s0/$s1)
struct Obj_1C21A0 { u8 pad[4]; R11B008List* f4; };
void func_001C15D8(R11B008* self, void* a, s32 r);


struct Owner_1C0C08 { u8 pad0[1]; };

void func_0011D8B0(Owner_1C0C08* a0, s32 a1, s32 a2);

extern s32 D_006053E0[];


void func_00182C18(C01* self);


struct E_1C1190 { R11B008Node* a; s32 b; };

s32 func_00137C40(void* src);
void* func_0018D500(u32 size);
void func_00138518(void* self);
s32 func_0011A630(void);
void func_0011A6C0(u8* a, s32 b);
void func_0011A358(R11B008* out, s32 a, s32 b, R11B008* body);
extern s32 D_00275714;
extern u8 D_00259F38[];


// NEAR: the entry pointer is loaded into v0 where retail uses v1 (register choice only); five lines differ.

struct Ent_1C13E8 { R11B008Node* a; s32 b; };

s32 func_0011A630(void);
void func_0011A080(R11B008* t, R11B008Node* node, s32 b);


struct Cmd_1C1AD8 { u32 kind; R11B008Node* list; };


struct __attribute__((aligned(16))) Blob_1C1BF8 { Quad16 q[3]; };
struct W8_1C1BF8 { s32 a, b; };
struct W12_1C1BF8 { s32 a, b, c; };


struct Rec3_1C15D8 { s32 a, b, c; };
struct D8_1C15D8 { s32 a, b; };

extern void* func_0011C508(void);
extern void* func_0011C618(void);
extern void func_001884E0(void* d, void* s);
extern void func_001884C0(void* d);
extern void* func_0011C748(void);
extern void* func_0011C858(void);
extern void* func_0011C968(void);


struct List_1C0808 {
    u8* first;
    s32 pad04;
    s32 offset;
};
struct Iter_1C0808 {
    List_1C0808* list;
    u8** link;
    s32 offset;
    Iter_1C0808* prev;
};
void func_001BF788(u8* obj, void* item);

struct Begin_1C0808 {
    static void Of(Iter_1C0808* it, List_1C0808* list)
    {
        it->list = list;
        it->link = (u8**)list;
        it->offset = list->offset;
        it->prev = (Iter_1C0808*)D_0027B314;
        D_0027B314 = (ListFrame*)it;
    }
};

struct Next_1C0808 {
    static u8* Of(Iter_1C0808* it)
    {
        u8* obj = *it->link;
        it->link = (u8**)(obj + it->offset);
        return obj;
    }
};

struct End_1C0808 {
    static void Of(Iter_1C0808* it)
    {
        D_0027B314 = (ListFrame*)it->prev;
    }
};


struct Tag_1C2430 { u64 lo; u64 hi; };

struct Slot_1C2430 {
    Tag_1C2430* tags;
    u32 base;
    u32 addrs[8];
    s32 sizes[8];
    s32 count;
    s32 state;
};

struct Chan_1C2430 {
    u32 f0;
    u8 pad4[0x7C];
    u32 f80;
};

extern Chan_1C2430* D_00261F24;

typedef char* VaList_1C2430;
#define VA_ARG_1C2430(ap, T) (*(T*)((ap += 8) - 8))

void func_00202C38(void* p, s32 a, s32 b);
void func_00202A80(Chan_1C2430* c, u32 addr);

void func_001C05D0(f32 x);
void func_001C0600(s32 column);
void func_001C06A0(s32 row, s32 column, f32 value);
void func_001C06D8(void);
void func_001C0760(s32 flag);
s32 func_001C0790(s32 value);
void func_001C07B0(void);
void func_001C0808(void* item);
void func_001C08B0(Stack_1C08B0* self, s32 a, s32 b);
void func_001C0950(Stack_1C0950* self);
void func_001C09D8(C6C* self, s32 index, s32 value);
void func_001C0A50(C6C* self, s32 key);
void func_001C0AB8(C6C* self, Pt_1C0AB8* p);
void func_001C0B08(C6C* self, Packed_001C0B08* item);
void func_001C0B38(C6C* self);
void func_001C0C08(s32 idx, s32 val);
s32 func_001C0C50(s32 index);
void func_001C0C68(s32 i);
void func_001C0CB0(void);
s32 func_001C0CF0();
void func_001C0EC0(void);
void func_001C1190(C6C* self, S137290* arg);
void* func_001C1390(s32 index, C6C* self);
R11B008* func_001C13E8(R11B008* self, s32 index, C6C* ctx);
s32 func_001C14C0(KeyHolder_1C14C0* self, s32 key);
R11B008* func_001C1530(R11B008* self, void* ctx, s32 v, Cb_1C1530 cb);
R11B008* func_001C15D8(R11B008* out, void* base, Desc_1C15D8* d);
s32 func_001C1A28(List_1C1A28* self, s32 value);
s32 func_001C1AD8(Cmd_1C1AD8* cmd, s32* val);
R11B008* func_001C1BF8(R11B008* out, s32 n, R11B008* args, const u32* kinds, void** dsts);
R11B008* func_001C1E48(R11B008* self, s32 n, s32* keys, s32* vals);
R11B008* func_001C21A0(R11B008* self, Obj_1C21A0* p, s32 n);
R11B008* func_001C2238(R11B008* self, Obj_1C2238* p, s32 key, R11B008* value);
R11B008* func_001C22B8(R11B008* self, Obj_1C22B8* p, s32 key, R11B008* value);
R11B008* func_001C2320(R11B008* self, C01* p, s32 key, R11B008* value);
R11B008* func_001C23B0(R11B008* ret, s32 count, R11B008* args, const void* kinds, ...);
void func_001C2430(s32 size, ...);
void func_001C25B0(s32 first, ...);
void func_001C29C8();

// The file's .data, in retail's order.
f32 D_00274758[11][4] = { 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
s32 D_00274808[6] = { 0, 2, 3, 4, 9, 1 };
Pk8_1C0A50 D_00274820 = { 0x40C0000040800000ULL };
Pk8_1C0A50 D_00274828 = { 0x45FA0000453B8000ULL };
s32 D_00274830 = 0;
f32 D_00274838[11][4] = { 0 };
u8 D_002748E8[4] = { 0 };
s32 D_002748EC = 0;
Ring_1C25B0 D_002748F0[2] = { { 0 } };
s32 D_00274990 = 0;

void func_001C05D0(f32 x)
{
    func_0011D480(8, (s32)(x * 1024.0f));
}

void func_001C0600(s32 column)
{
    f32* p = &D_00274838[0][column];
    f32 prod = 1.0f;
    s32 n = 10;

    do {
        prod = prod * *p;
        p += 4;
        n--;
    } while (n >= 0);

    f32 one = 1.0f;

    if (prod < 0.0f) {
        prod = 0.0f;
    } else if (one < prod) {
        prod = one;
    }

    func_0011D480(column, (s32)(prod * 1024.0f));
}

void func_001C06A0(s32 row, s32 column, f32 value)
{
    D_00274838[row][column] = value;
    func_001C0600(column);
}

void func_001C06D8(void)
{
    func_0018D800(D_00274838, D_00274758, 0xB0);
    func_001C05D0(1.0f);
    for (s32 i = 0; i < 4; i++) {
        func_001C0600(i);
    }
    func_001C0760(D_002623C0->f19EC & 0x80);
    func_001C0790(D_002623C0->f19EC & 0x40);
}

void func_001C0760(s32 flag)
{
    func_001C06A0(3, 1, flag ? 0.0f : 1.0f);
}

s32 func_001C0790(s32 value)
{
    return func_0011D4E0(value != 0);
}

void func_001C07B0(void)
{
    func_0011E010();
    func_001C0808(0);
    func_001BEE48();
    func_001C0CB0();
    while (func_0011CE30() != 0) {
    }
    func_0011E110(1);
    func_0011E1F8(0);
}

void func_001C0808(void* item)
{
    if (D_00275710) {
        Iter_1C0808 it;
        u8* obj;
        Begin_1C0808::Of(&it, (List_1C0808*)&D_00275710->f1BAC);
        for (obj = Next_1C0808::Of(&it); obj; obj = Next_1C0808::Of(&it)) {
            func_001BF788(obj, item);
        }
        End_1C0808::Of(&it);
    }
    func_0011CE30();
}

void func_001C08B0(Stack_1C08B0* self, s32 a, s32 b)
{
    if ((u32)self->count < 4) {
        func_0011E328(2, D_00274808[a]);
        func_0011E360(2, b, b);
        self->pairs[self->count].a = a;
        self->pairs[self->count].b = b;
        self->count++;
    }
}

void func_001C0950(Stack_1C0950* self)
{
    s32 n = self->count;
    if (n >= 2) {
        self->count = n - 1;
        func_0011E328(2, D_00274808[self->pairs[n - 2].a]);
        func_0011E360(2, self->pairs[self->count - 1].b, self->pairs[self->count - 1].b);
    }
}

void func_001C09D8(C6C* self, s32 index, s32 value)
{
    func_0011E328(2, D_00274808[index]);
    func_0011E360(2, value, value);
    *(s32*)self->f2328 = index;
    *(s32*)(self->f2328 + 4) = value;
    self->f2348 = 1;
}

void func_001C0A50(C6C* self, s32 key)
{
    if (self->f1D80 < 16) {
        Ent_1C0A50* e = &((Ent_1C0A50*)self->f1D84)[self->f1D80];
        e->key = key;
        e->a = D_00274820;
        e->b = D_00274828;
        self->f1D80++;
    }
}

void func_001C0AB8(C6C* self, Pt_1C0AB8* p)
{
    s32 n = self->f1D80;
    if (n != 0) {
        Ent_1C0AB8* e = (Ent_1C0AB8*)((u8*)self + 0x1D70 + n * 20);
        e->b0 = 8000.0f - p->y * 50.0f;
        e->b1 = 8000.0f - p->x * 50.0f;
    }
}

void func_001C0B08(C6C* self, Packed_001C0B08* item) { if (!self->f1D80) return; u8* dst = (u8*)self + 0x1D70 + self->f1D80 * 20; *(Packed_001C0B08*)(dst + 4) = *item; }

void func_001C0B38(C6C* self)
{
    for (s32 i = 0; i < self->f1D80; i++) {
        Ent_1C0B38* e = &((Ent_1C0B38*)self->f1D84)[i];
        func_001BFCD8(e->key, D_002748E8, 0, 0, &e->a, &e->b, 8000.0f, 3000.0f, 1.0f, 0.0f, 0.0f);
    }
}

void func_001C0C08(s32 idx, s32 val)
{
    if (val != D_006053E0[idx]) {
        D_006053E0[idx] = val;
        func_0011D8B0((Owner_1C0C08*)D_00274728, idx, val);
    }
}

s32 func_001C0C50(s32 index)
{
    return D_006053E0[index];
}

void func_001C0C68(s32 i)
{
    D_006053E0[i] = func_0011D8F0(D_00274728, i);
}

void func_001C0CB0(void)
{
    for (s32 i = 0; i < 8; i++) {
        func_001C0C08(i, 0);
    }
}

extern const TabA_24D2A8 D_0024D2A8 = { { -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, 1, -5, -5, -5, -5, 1, 1, -5, -5, -5, 1, 1, 1, -5, -5, 1, 1, 1, 1, -5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } };
extern const TabB_24D350 D_0024D350 = { { 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0 } };

s32 func_001C0CF0() {
    TabA_24D2A8 a = D_0024D2A8;
    TabB_24D350 b = D_0024D350;
    s32 r = func_001EAA70(0, 5);
    D_00274830 += *(s32*)((u8*)&a + (b.v[D_00274830 + 12] * 24 + r * 4));
    return D_00274830;
}

void func_001C0EC0(void)
{
    if (D_002748EC != 0) {
        f32 scale = (f32)func_001C0CF0();
        func_001BFCD8(0x77, 0, 0, 0, 0.0f, 0.0f, 0.5f, scale * 0.083333336f, 0.0f, 0, 0);
    }
}

ASM_FUNC(func_001C0F30);

void func_001C0FF0(C66* self)
{
    func_00124A48(self);
    func_001C1030(self, self->id32C);
    self->desc->m03(self);
}

void func_001C1030(C66* self, s32 v)
{
    if (self->link334 != 0) {
        func_001B6438(self->link334);
        self->link334 = 0;
    }
    s32 r = func_0015A418(self->world, 0x101, v, self);
    self->found330 = r;
    if (r != 0) {
        self->link334 = func_001B6290(r, self, -1, 1);
    }
    self->id32C = v;
}

void func_001C10A8(C81* self)
{
    func_00182C18(self);
    self->f58 = 3.4028235e38f;
}

void func_001C10D8(C81* self)
{
    func_00182D48(self);
    func_00152470(&self->world->list1C84, self);
}

void func_001C1110(C81* self)
{
    func_00182ED0(self);
    func_00152600(&self->world->list1C84, self);
}

void func_001C1148(C81* self)
{
    Keep7E saved;
    saved = self->keep;
    func_001830D8(self);
    self->keep = saved;
}

void func_001C1190(C6C* self, S137290* arg) {
    R11B008 q0;
    R11B008 q1;
    R11B008 q2;
    s32 i = 0;
    func_0011B008(&q0);
    self->f1EF0 = func_00137C40(arg);
    self->f1EF4 = func_0018D500(self->f1EF0 << 3);
    s32 n1 = func_00137C40(arg);
    s32 n2 = func_00137C40(arg);
    for (i = 0; i < self->f1EF0; i++) {
        {
            E_1C1190* e = (E_1C1190*)self->f1EF4 + i;
            e->a = func_0011BA28(arg);
            e->b = 0;
            if (D_00275714) {
                func_00138518(arg);
                func_00138518(arg);
                func_00138518(arg);
            }
        }
    }
    if (D_00275714) {
        if (n1 > 0) { s32 k = n1; do func_00138518(arg); while (--k); }
        if (n2 > 0) { s32 k = n2; do func_00138518(arg); while (--k); }
    }
    s32 r = func_0011A630();
    i = 0;
    self->f2C = (void*)r;
    func_0011A6C0(D_00259F38, r);
    self->f1EF8 = n1;
    func_0011B538(&q0, 0);
    func_0011A358(&q1, (s32)self->f2C, self->f1EF8, &q0);
    func_0011B060(&q1, 2);
    if (self->f1EF0 > 0) {
        do {
            func_0011B008(&q1);
            func_001C13E8(&q2, i, self);
            i++;
            func_0011B0A8(&q1, &q2);
            func_0011B060(&q2, 2);
            func_0011B060(&q1, 2);
        } while (i < self->f1EF0);
    }
    func_0011B060(&q0, 2);
}

void* func_001C1390(s32 index, C6C* self)
{
    if (index == -1) {
        return 0;
    } else {
        Entry_1C1390* e = (Entry_1C1390*)((index << 3) + (u32)self->f1EF4);
        void* p = e->value;
        if (p != 0) func_0011A6C0(D_00259F38, p);
        return p;
    }
}

R11B008* func_001C13E8(R11B008* self, s32 index, C6C* ctx)
{
    s32 off = index << 3;
    R11B008 q;
    Ent_1C13E8* e;
    func_0011B008(&q);
    e = (Ent_1C13E8*)(off + (s32)ctx->f1EF4);
    if (e->a != 0 && e->b == 0) {
        R11B008 t;
        ((Ent_1C13E8*)(off + (s32)ctx->f1EF4))->b = func_0011A630();
        func_0011A080(&t, ((Ent_1C13E8*)(off + (s32)ctx->f1EF4))->a, ((Ent_1C13E8*)(off + (s32)ctx->f1EF4))->b);
        func_0011B0A8(&q, &t);
        func_0011B060(&t, 2);
    }
    func_0011B538(&q, 0x22);
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

s32 func_001C14C0(KeyHolder_1C14C0* self, s32 key)
{
    KeyTable_1C14C0* entry = &D_00244950[self->ref->index];
    s32 lo = 0;
    s32 hi = entry->count - 1;
    KeyPair_1C14C0* items = entry->items;

    while (lo <= hi) {
        s32 mid = (lo + hi) >> 1;
        s32 k = items[mid].key;
        if (k == key) {
            return items[mid].value;
        }
        if (key < k) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return 0;
}

R11B008* func_001C1530(R11B008* self, void* ctx, s32 v, Cb_1C1530 cb)
{
    R11B008 q;
    Rec_1C1530 r;
    func_0011B008(&q);
    r.a = v;
    r.head = 0;
    r.cnt = 0;
    cb(ctx, &r);
    if (r.head != 0) {
        func_0011B6C0(&q, r.head);
    } else {
        func_0011B538(&q, 0);
    }
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

R11B008* func_001C15D8(R11B008* out, void* base, Desc_1C15D8* d)
{
    R11B008 q;
    R11B008 q2;
    s32 t20, t28, t2c, t30;
    f32 t24;
    char* p;
    Get_1C15D8 fn;
    func_0011B008(&q);
    if (d->flags & 1) {
        s32* r = (s32*)func_0011AE78();
        r[0] = (s32)base;
        r[1] = d->imm;
        r[2] = d->imm2;
        func_0011B8E8(&q, (s32)r);
    } else if (d->flags & 2) {
        if (d->flags & 0x1000) {
            p = (char*)d->base(base, 0) + d->off;
        } else {
            p = (char*)base + d->off;
        }
        switch (d->kind) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17:
            func_0011B570(&q, *(s32*)p);
            break;
        case 1:
            func_0011B5B0(&q, *(f32*)p);
            break;
        case 0:
            func_0011B5F0(&q, *(s32*)p);
            break;
        case 2: {
            Quad16* r = (Quad16*)func_0011C508();
            *r = *(Quad16*)p;
            func_0011B740(&q, (f32*)r);
            break;
        }
        case 4: {
            void* r = func_0011C618();
            func_001884E0(r, p);
            func_0011B788(&q, (f32*)r);
            break;
        }
        case 9: {
            Quad16* r = (Quad16*)func_0011C748();
            *r = *(Quad16*)p;
            func_0011B7D0(&q, (f32*)r);
            break;
        }
        case 10: {
            D8_1C15D8* r = (D8_1C15D8*)func_0011C858();
            *r = *(D8_1C15D8*)p;
            func_0011B818(&q, (f32*)r);
            break;
        }
        case 11: {
            Rec3_1C15D8* r = (Rec3_1C15D8*)func_0011C968();
            *r = *(Rec3_1C15D8*)p;
            func_0011B860(&q, (f32*)r);
            break;
        }
        case 13:
            break;
        default:
            if (d->kind & 0x1000) {
                func_0011B570(&q, *(s32*)p);
            } else if (d->kind & 0x2000) {
                func_0011B8A8(&q, (void*)*(s32*)p);
            }
            break;
        }
    } else {
        if (d->flags & 0x1000) {
            p = (char*)d->base(base, 0);
        } else {
            p = (char*)base;
        }
        if (d->flags & 4) {
            fn = (Get_1C15D8)d->off;
        } else {
            fn = *(Get_1C15D8*)(*(char**)base + d->off);
        }
        switch (d->kind) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17:
            fn(p, &t20);
            func_0011B570(&q, t20);
            break;
        case 1:
            fn(p, &t24);
            func_0011B5B0(&q, t24);
            break;
        case 0:
            fn(p, &t28);
            func_0011B5F0(&q, t28);
            break;
        case 2: {
            void* r = func_0011C508();
            fn(p, r);
            func_0011B740(&q, (f32*)r);
            break;
        }
        case 4: {
            void* r = func_0011C618();
            fn(p, r);
            func_001884C0(r);
            func_0011B788(&q, (f32*)r);
            break;
        }
        case 9: {
            void* r = func_0011C748();
            fn(p, r);
            func_0011B7D0(&q, (f32*)r);
            break;
        }
        case 10: {
            void* r = func_0011C858();
            fn(p, r);
            func_0011B818(&q, (f32*)r);
            break;
        }
        case 11: {
            void* r = func_0011C968();
            fn(p, r);
            func_0011B860(&q, (f32*)r);
            break;
        }
        case 13:
            break;
        default:
            if (d->kind < 0) {
                func_001C1530(&q2, base, d->kind & 0x7fffffff, fn);
                func_0011B0A8(&q, &q2);
                func_0011B060(&q2, 2);
            } else if (d->kind & 0x1000) {
                fn(p, &t2c);
                func_0011B570(&q, t2c);
            } else if (d->kind & 0x2000) {
                fn(p, &t30);
                func_0011B8A8(&q, (void*)t30);
            }
            break;
        }
    }
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

s32 func_001C1A28(List_1C1A28* self, s32 value)
{
    Desc_1C15D8 d;
    R11B008 t;
    func_001F5C0C(&d, 0, 0x20);
    d.flags = 2;
    d.kind = self->type;
    d.off = 0;
    R11B008Node* n = func_0011AF28();
    func_001C15D8(&t, value, &d);
    func_0011B0A8(n, &t);
    func_0011B060(&t, 2);
    if (self->head != 0) {
        self->tail->next = n;
    } else {
        self->head = n;
    }
    self->tail = n;
    return 1;
}

s32 func_001C1AD8(Cmd_1C1AD8* cmd, s32* val) {
    R11B008 q;
    R11B008Node* l;
    func_0011B008(&q);
    l = cmd->list;
    if (l) {
        switch (cmd->kind) {
        case 1:
            func_0011B5B0(&q, *(f32*)val);
            break;
        case 0:
            func_0011B5F0(&q, *val);
            break;
        case 2: case 4: case 9: case 10: case 11: case 13:
            break;
        default:
            if (cmd->kind & 0x1000) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17:
                func_0011B570(&q, *val);
            } else if (cmd->kind & 0x2000) {
                func_0011B8A8(&q, (void*)*val);
            }
            break;
        }
        while (l) {
            if (func_0011B0F8(l, &q)) {
                func_0011B060(&q, 2);
                return 1;
            }
            l = l->next;
        }
    }
    func_0011B060(&q, 2);
    return 0;
}

R11B008* func_001C1BF8(R11B008* out, s32 n, R11B008* args, const u32* kinds, void** dsts)
{
    R11B008 q;
    R11B008 a;
    R11B008 b;
    R11B008 c;
    s32 i;
    func_0011B008(&q);
    for (i = 0; i < n; i++) {
        func_0011B0A8(&q, args + i);
        u32 t = kinds[i];
        void* d = dsts[i];
        switch (t) {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17:
        case 20:
            if (q.tag == 0x14) {
                goto store;
            }
            func_0011B008(&a);
            func_0011B928(&b, &q);
            func_0011B0A8(&a, &b);
            func_0011B060(&b, 2);
            *(s32*)d = a.i;
            func_0011B060(&a, 2);
            break;
        case 1:
            if (q.tag == 0x15) {
                *(f32*)d = q.f;
            } else {
                func_0011B008(&a);
                func_0011B9A8(&c, &q);
                func_0011B0A8(&a, &c);
                func_0011B060(&c, 2);
                *(f32*)d = a.f;
                func_0011B060(&a, 2);
            }
            break;
        case 4:
            *(Blob_1C1BF8*)d = *(Blob_1C1BF8*)q.p;
            break;
        case 2:
        case 9:
            *(Quad16*)d = *(Quad16*)q.p;
            break;
        case 10:
            *(W8_1C1BF8*)d = *(W8_1C1BF8*)q.p;
            break;
        case 11:
            *(W12_1C1BF8*)d = *(W12_1C1BF8*)q.p;
            break;
        default:
            if (t & 0x1000) {
                goto store;
            }
            if (t & 0x2000) {
                goto store;
            }
            break;
        case 0:
        store:
            *(s32*)d = q.i;
            break;
        case 13:
            break;
        }
    }
    func_0011B538(&q, 0x22);
    func_0011B018(out, &q);
    func_0011B060(&q, 2);
    return out;
}

R11B008* func_001C1E48(R11B008* self, s32 n, s32* keys, s32* vals)
{
    R11B008 q;
    List_1C1A28 list;
    func_0011B008(&q);
    list.head = 0;
    list.tail = 0;
    for (s32 i = 0; i < n; i++) {
        list.type = keys[i];
        func_001C1A28(&list, vals[i]);
    }
    if (list.head) {
        func_0011B6C0(&q, list.head);
    } else {
        func_0011B538(&q, 0);
    }
    func_0011B018(self, &q);
    func_0011B060(&q, 2);
    return self;
}

INCLUDE_RODATA(jtbl_0024D510);
INCLUDE_ASM(func_001C1F20);

R11B008* func_001C21A0(R11B008* self, Obj_1C21A0* p, s32 n)
{
    if (n < 0x495) {
        s32 r = (s32)func_001C14C0(p, n);
        func_001C15D8(self, p, r);
    } else {
        R11B008 q;
        func_0011B008(&q);
        func_0011BE90(p->f4, n, &q);
        func_0011B018(self, &q);
        func_0011B060(&q, 2);
    }
    return self;
}

R11B008* func_001C2238(R11B008* self, Obj_1C2238* p, s32 key, R11B008* value)
{
    if (key < 0x495) {
        void* v = func_001C14C0(p, key);
        func_001C1F20(self, p, v, value);
    } else {
        func_0011BDD0(self, p->f4, key, value);
    }
    return self;
}

R11B008* func_001C22B8(R11B008* self, Obj_1C22B8* p, s32 key, R11B008* value)
{
    func_00130110(p);
    func_0011BD28(self, p->f4, key, value);
    return self;
}

R11B008* func_001C2320(R11B008* self, C01* p, s32 key, R11B008* value)
{
    func_00130110(p);
    if (func_0011BE90((R11B008List*)p->f04, key, 0)) func_0011BDD0(self, (R11B008List*)p->f04, key, value);
    else func_0011BD28(self, (R11B008List*)p->f04, key, value);
    return self;
}

R11B008* func_001C23B0(R11B008* ret, s32 count, R11B008* args, const void* kinds, ...)
{
    void* arr[32];
    void* ap = (char*)__builtin_next_arg(kinds) - 32;
    if (count > 0) {
        void** d = arr;
        s32 i = count;
        do {
            ap = (char*)ap + 8;
            *d = *(void**)((char*)ap - 8);
            d++;
            i--;
        } while (i != 0);
    }
    func_001C1BF8(ret, count, args, (const u32*)kinds, arr);
    return ret;
}

void func_001C2430(s32 size, ...)
{
    VaList_1C2430 ap;
    Slot_1C2430* e = &((Slot_1C2430*)D_002748F0)[1 - D_00274990];
    s32 n = 0;
    ap = (VaList_1C2430)__builtin_next_arg(size) - (8 - __builtin_args_info(0)) * 8;
    u32 addr = e->base;
    if (e->state == 3) {
        func_00202C38((*(void**)&D_00261F20), 0, 0);
    }
    e->state = 1;
    s32 data = VA_ARG_1C2430(ap, s32);
    if (size != 0) {
        do {
            s32 nsize = VA_ARG_1C2430(ap, s32);
            size = (size + 15) & ~15;
            addr += 16;
            e->sizes[n] = size;
            e->addrs[n] = addr;
            addr += size;
            s32 ndata = VA_ARG_1C2430(ap, s32);
            if (data != 0) {
                e->tags[n].lo = (u64)(size >> 4) | ((u64)(ndata != 0 ? 3 : 0) << 28) | ((u64)data << 32);
            }
            data = ndata;
            size = nsize;
            n++;
        } while (size != 0);
    }
    e->count = n;
    Chan_1C2430* c = D_00261F24;
    c->f0 |= 0x40;
    c->f80 = (e->base & 0x0FFFFFFF) | 0x80000000;
    func_00202A80(c, (u32)e->tags & 0x0FFFFFFF);
}

void func_001C25B0(s32 first, ...) {
    s32 buf[8];
    Ring_1C25B0* r = &D_002748F0[D_00274990];
    s32 n = 0;
    s32 x = first;
    r->f4C = 3;
    func_00202C38(D_00261F20, 0, 0);
    void* ap = (char*)__builtin_next_arg(first) - 56;
    while (x) {
        buf[n] = x;
        ap = (char*)ap + 8;
        x = *(s32*)((char*)ap - 8);
        n++;
    }
    s32 i = 0;
    n = r->f48 - n;
    while (n < r->f48 - 1) {
        *(u64*)(r->f8[n] - 0x10) = ((r->f28[n] >> 4) | 0x10000000) | ((u64)buf[i] << 32);
        n++;
        i++;
    }
    Dma_1C25B0* d = D_00261F20;
    *(u64*)(r->f8[n] - 0x10) = ((r->f28[n] >> 4) | 0x70000000) | ((u64)buf[i] << 32);
    d->f0 &= ~0x40;
    d->f80 = (r->f4 & 0xFFFFFFF) + 0x80000000;
    func_00202B68(d);
    r = &D_002748F0[1 - D_00274990];
    if (r->f4C == 3) r->f4C = 0;
}

LINKER_REMNANT(func_001C27A8);

INCLUDE_ASM(func_001C27B0);

void func_001C29C8()
{
    func_001C27B0(1, 0xFFFF);
}
