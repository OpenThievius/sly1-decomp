// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "c05.h"
#include "asm_func.h"
extern f32 D_0026185C[];
#include "list_iter.h"
#include "c53.h"
#include "c6c.h"
#include "c48.h"

// A four-float vector, aligned as the VU0 reads it.
struct __attribute__((aligned(16))) Vec4_1963D8 { f32 x, y, z, w; };


void func_00123ED0(C53* self);
void func_00152470(u8* dst, C53* src);



void func_00124A48(C53* self);



struct Rec_26A728 { s32 id; s32 off; s32 flags; };
struct Tbl_26A728 { s32 f0; Rec_26A728 r[1]; };

void func_001BAC30(void* self);
void func_00124DF8(void* self, s32 n, void* table);



struct Obj_196E48 { u8 pad0[0x50]; s32 f50; u8 pad1[0x538 - 0x54]; u64 bits538; };

s32 func_001300E8(void* self, s32 kind);



void func_001B6598(void* obj, s32* out);
void* func_001E9970(s32 arg);

typedef void (*VFn_197788)(void* self);
struct Iface_197788 { VFn_197788* vtbl; };
extern Iface_197788 D_0026D348;
extern Iface_197788 D_0026E4E0;
extern Iface_197788 D_0026E760;

void func_001A76A0(void* node, s32 flag);
void func_00152600(void* a, void* b);
void func_00152470(void* a, void* b);

struct Ctx_197A08 { u8 pad[0xC14]; void* fC14; };




struct Pair_00197A68 { u8 pad[0x94]; f32 f94; f32 f98; };



void func_001922E8(void* a, void* b);



extern u8 D_00261EF0[];
void func_00151E20(void* self, f32 amount);



void func_001B6568(void* dev, s32* out);
void func_001B6598(void* dev, s32* out);
void func_001B64D8(void* dev, s32 value);
void func_001973D8(u8* self);



extern u8 D_0026E744[];

typedef void (*VFn_197F10)(void* self);
struct Vt_197F10 { VFn_197F10* vtbl; };

void func_00192230(void* self, s32 kind, void* rec);
void func_001B6598(void* dev, s32* out);
void func_001DDC38(void* sub, void* self);
void func_001AB890(void* obj, f32 x);
void func_001AB928(void* obj, f32 x, void* fn);
void func_001AB938(void* obj);
void func_001AB958(void* obj);
void func_00197458(s32 unused, s32 flag);



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
extern Obj_197848* func_00182FC8(Obj_197848*);
extern s32 func_001527D8(void* list);
extern s32 func_001EAA70(s32 a, s32 b);
extern void func_00152600(void* a, void* b);
extern void func_00152470(void* a, void* b);
extern void func_001C8F20(void* node, s32 kind, s32 flag);
extern void func_001A76A0(void* node, s32 flag);



extern u8 D_00248D20[];

struct __attribute__((aligned(16))) Quad_196938 { s32 a, b, c, d; };

struct Sub_196938 { u8 bytes[0x568]; };


void func_001921A8(C18* self);
void func_00152438(Sub_196938* p, s32 value);



struct __attribute__((aligned(16))) Quad_001969F8 { s32 a, b, c, d; };
struct Root_001969F8 { u8 pad[0x11]; u8 b11; };
struct Table_001969F8 { u8 pad[0x10]; };
struct Item_001969F8 { u8 pad[0x24]; void* p24; };

struct Any_001969F8;

struct Tbl_26A738 { s32 f0; Rec_26A728 r[13]; };
extern u8 D_0021A790[];
extern u8 D_00248D30[];

void func_00124A48(C18* self);
void func_00124DF8(C18* self, s32 n, void* table);
f32 func_00205778(f32 a, f32 b);
void* func_001B6290(Any_001969F8* a, void* b, s32 c, s32 d);
void* func_00121228(Root_001969F8* root, void* value, Table_001969F8* table);
void func_001299E0(Any_001969F8* a, void* b);
s32 func_0015A4F0(Any_001969F8* a0, s32 a1, s32 a2, void* a3, s32 a4, void* a5);
void* func_0018D500(s32 size);
void func_00152470(Any_001969F8* list, void* item);
void func_001B6DF8(Any_001969F8* a, void* b);



struct Nd_196410;
struct VT_196410 {
    u8 pad0[8];
    u32 flags;
    u8 pad0C[0x38 - 0xC];
    void (*m38)(Nd_196410*, Stream53*);
    u8 pad3C[0x58 - 0x3C];
    void (*m58)(Nd_196410*);
    u8 pad5C[0x64 - 0x5C];
    void (*m64)(Nd_196410*, void*);
    void (*m68)(Nd_196410*, void*);
};
struct Nd_196410 {
    VT_196410* vt;
    u8 pad04[4];
    s32 f08;
    u8 pad0C[0x2C - 0xC];
    void* f2C;
    void* f30;
    u8 pad34[0x80 - 0x34];
    f32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[0x2C8 - 0x8C];
    u64 b0 : 28;
    u64 mode : 2;
    u64 b30 : 34;
};
struct Cell_196410 { Nd_196410* node; s32 link; };
struct Frame_196410 {
    List01* list;
    u8* cursor;
    s32 link;
    Frame_196410* prev;
};

void func_00152438(u8* a, s32 v);
void func_00137EB0(Stream53* r, void* out);
void func_00137E70(Stream53* r, void* out);
s32 func_00137B90(Stream53* r);
s32 func_00137D10(Stream53* r);
Nd_196410* func_001DC208(void* host, s32 a);
Nd_196410* func_0011E580(s32 slot, void* host, s32 z, s32 key, s32 flag);
void func_001DC150(void* host, Nd_196410* n, s32 v);
Cell_196410* func_0018D5C0(s32 n);
void func_00152470(u8* list, Cell_196410* c);
Nd_196410* func_0015A418(void* host, s32 kind, s32 id, Nd_196410* c);
void* func_001C1390(s32 id, void* host);
void func_0011A338(void* a, void* b);
s32 func_00137C40(Stream53* r);
s32 func_00137CC0(Stream53* r);
f32 func_00137DF8(Stream53* r);
void func_0011EC40(Nd_196410* n, Stream53* r);
void func_0011ECB8(void* host, C53* self, Stream53* r);
s32 func_00152720(List01* list);

// The id that names no object.
struct Id_196410 {
    static s32 None() { return -1; }
};




struct Cell_196810 { void* node; s32 link; };
struct Elem_196810 { s32 f0; u8 pad4[4]; Elem_196810* next; };
struct Item_196810 { u8 pad0[0x1C]; Item_196810* next; u8 pad20[0x10]; void* f30; };
void func_00127048(C53* self, C53* src);
void func_00152440(List53* p);
void func_00152470(List53* list, Cell_196810* c);



void func_001BA130(void*);
void func_00198980(void*);
void func_001B7F78(void);
void func_00182D48(void*);
void func_00152470(void*, void*);
void func_00182ED0(void*);
void func_00152600(void*, void*);
void func_00182C58(void*);
void* func_0015A418(void*, s32, s32, void*);
void func_001B7A98(void*);
void func_001B7B78(void*);
void func_00182C18(void*);
void func_00144848(void*);
void func_0015EAE0(void*, void*, void*);
void func_0019D860(void);
void func_0019D968(void);
void func_0019D930(void);
void func_0019EBE8(void*);
void func_001831E8(void*, void*, s32, void*);
void func_001831E8(void*, void*, void*, void*);
void func_00183238(void*, void*, void*, void*);
void func_0019F9D0(void*, u32);




struct Found_198920 {
    u8 pad0[0x684];
    s32 f684;
};

void func_00124A48(void* self);
void func_00124DF8(void* self, s32 n, void* table);
void* func_0015A838(void* a, s32 b, s32 c, void* d);



void func_001C72A0(void* self);



struct __attribute__((aligned(16))) Quad_1984B8 { s32 a, b, c, d; };
typedef void (*VFn_1984B8)(void* self, void* ctx);
struct Actor_1984B8 { VFn_1984B8* vtbl; u8 pad0[0x150 - 4]; Quad_1984B8 q150; u8 pad1[0x724 - 0x160]; s32 kind; };

void* func_001925F0(void);
void func_00197A08(void* h, void* self);
void func_001C9008(void* self, void* arg);



struct Actor_198530 { u8 pad0[0x724]; s32 kind; };

void func_001C91C8(void* self);
void func_001C8920(void* self);



struct Req_1986E8 {
    s32 a;
    s32 b;
};

void func_001C9DE0(void* self, s32 code, void* req);



struct Actor_1982A0 { u8 pad0[0x724]; s32 kind; u8 pad1[0xC10 - 0x728]; s32 fC10; };

s32 func_001C96B8(void* self);
s32 func_001C8010(void* self);




struct Obj_198760 {
    u8 pad000[0x640];
    void* f640;
    u8 pad644[0x67C - 0x644];
    s32 f67C;
    u8 pad680[0x698 - 0x680];
    f32 f698;
};

struct Tmp_198760 {
    void* f00;
    void* f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    u8 pad14[0x40 - 0x14];
};

void* func_001925F0(C0F* self, f32 f);
s32 func_001300E8(void* key, s32 kind);
s32 func_00182FC8(void* p);
s32 func_00141170(void* self, void* value);
s32 func_00177838(Tmp_198760* f, s32 a, s32 b);
void func_001C7CB8(C0F* self, f32 f);

// The file's .data, in retail's order.
f32 D_0026A710 = 2200.0f;
f32 D_0026A714 = 4000.0f;
f32 D_0026A718 = 2000.0f;
f32 D_0026A71C = 4000.0f;
s32 D_0026A720 = 5;
Tbl_26A728 D_0026A728 = { 0, { { 0x3D9, 0x610, 0 } } };
Tbl_26A738 D_0026A738 = { 0x24, {
    { 0x3DD, 0x640, 0x20 },
    { 0x3DE, 0x648, 0x0 },
    { 0x3E7, 0x64C, 0x0 },
    { 0x3E8, 0x650, 0x0 },
    { 0x3E9, 0x654, 0x0 },
    { 0x3EA, 0x658, 0x0 },
    { 0x3EC, 0x670, 0x4 },
    { 0x3ED, 0x65C, 0x0 },
    { 0x3EE, 0x668, 0x0 },
    { 0x3F0, 0x66C, 0x4 },
    { 0x3EF, 0x660, 0x24 },
    { 0x3EB, 0x678, 0x1 },
    { 0x3F1, 0x6B4, 0x0 },
} };
f32 D_0026A7D8[6] = { 7.0f, 0.0f, 0.1f, 0.0f, 0.0f, 0.0f };
Vec4_1963D8 D_0026A7F0 = { 3.0f, -2.0f, -1.0f, 0.0f };
Vec4_1963D8 D_0026A800 = { 0.25f, 0.0f, 0.0f, 0.0f };
Vec4_1963D8 D_0026A810 = { 1.2f, -1.2f, 0.0f, 0.0f };
f32 D_0026A820 = 60.0f;
f32 D_0026A824 = -30.0f;
f32 D_0026A828 = 0.25f;
f32 D_0026A82C = 0.7f;
f32 D_0026A830 = 250.0f;
f32 D_0026A834 = 0.25f;
f32 D_0026A838 = 0.5f;
f32 D_0026A83C = 0.2f;
f32 D_0026A840 = 0.1f;
f32 D_0026A844 = 1.3f;
Vec4_1963D8 D_0026A850 = { 0.0f, 3.0f, 0.0f, 0.0f };
Vec4_1963D8 D_0026A860 = { 0.0f, 0.75f, 0.0f, 0.0f };
Vec4_1963D8 D_0026A870 = { 5000.0f, 0.0f, 0.0f, 0.0f };
Vec4_1963D8 D_0026A880 = { 3.0f, -2.0f, -1.0f, 0.0f };
Vec4_1963D8 D_0026A890 = { 500.0f, 0.0f, 0.0f, 0.0f };
Vec4_1963D8 D_0026A8A0 = { 1.8f, -0.00024999998f, 0.0f, 0.0f };
Vec4_1963D8 D_0026A8B0 = { 1.1f, 1.6f, 0.0f, 0.0f };
Vec4_1963D8 D_0026A8C0 = { 1.4f, -0.005f, 0.0f, 0.0f };
f32 D_0026A8D0[2] = { 0.9f, 1.2f };
f32 D_0026A8D8 = 2000.0f;
f32 D_0026A8DC = 1100.0f;
s32 D_0026A8E0[9] = { 0x0, 0x3E4, 0x558, 0x0, 0x3E5, 0x554, 0x20, 0x3E6, 0x55C };
// The object func_00196938 registers itself as; filled at run time.
void* D_0026A904 = 0;

void func_001963D8(C53* self);
void func_00196410(C53* self, Stream53* rd);
void func_00196810(C53* self, C53* src);
void func_00196900(C53* self);
void func_00196938(C18* self);
void func_001969C0(C18* self);
void func_001969F8(C18* self);
s32 func_00196E48(s32 a0, Obj_196E48* self);
void func_001973D8(u8* self);
void func_00197458(s32 unused, s32 flag);
void func_001974D8(C18* a, void* b);
void func_00197788(C18* self);
void func_00197848(Self_197848* self);
void func_00197A08(u8* self, Ctx_197A08* ctx);
void func_00197A68(C18* ctx, Pair_00197A68* out);
void func_00197F10(C18* self, s32 kind, void* rec);
void func_00198090(C0F* self);
s32 func_001982A0(C0F* self);
void func_001984B8(C0F* self, void* arg);
void func_00198530(C0F* self);
void func_001986E8(C0F* self, s32 code, Req_1986E8* req);
void func_00198760(C0F* s1, f32 f);
u32 func_00198858(void);
void func_00198920(C48* self);

void func_001963D8(C53* self)
{
    func_00123ED0(self);
    func_00152470(&self->world->list1C3C, self);
}

void func_00196410(C53* self, Stream53* rd)
{
    Nd_196410* arr[64];
    Frame_196410 fr;
    Nd_196410* t;
    Nd_196410* c;
    s32 n;
    s32 i;
    s32 j;
    s32 cnt;
    s32 id;
    Nd_196410* x;
    Nd_196410* h;

    func_00152438((u8*)&self->cells, 8);
    func_00137EB0(rd, &self->rot);
    func_00137E70(rd, &self->pos);
    n = func_00137B90(rd);
    if (self->desc->m12 != 0)
    {
        self->desc->m12(self);
    }
    for (i = 0; i < n; i++)
    {
        Cell_196410* cell;
        id = func_00137D10(rd);
        if (id == Id_196410::None())
        {
            c = func_001DC208(self->world, func_00137D10(rd));
        }
        else
        {
            s32 a = func_00137D10(rd);
            c = func_0011E580(id, self->world, 0, a, func_00137D10(rd));
            c->vt->m38(c, rd);
            func_001DC150(self->world, c, func_00137D10(rd));
        }
        cell = func_0018D5C0(16);
        cell->node = c;
        cell->link = self->id;
        c->f30 = cell;
        func_00152470((u8*)&self->cells, cell);
        arr[i] = c;
    }
    cnt = func_00137B90(rd);
    for (j = 0; j < cnt; j++)
    {
        f32 big = 1.0e10f;
        t = 0;
        id = func_00137D10(rd);
        for (i = 0; i < n; i++)
        {
            c = arr[i];
            if (c->f08 == id)
            {
                t = c;
            }
            else if (c->vt->flags & 1)
            {
                t = func_0015A418(self->world, 0x101, id, c);
            }
            if (t != 0)
            {
                break;
            }
        }
        s32 res = func_00137D10(rd);
        if (res != Id_196410::None())
        {
            void* r = func_001C1390(res, self->world);
            if (t->f2C != 0)
            {
                func_0011A338(r, t->f2C);
            }
            t->f2C = r;
        }
        s32 w = func_00137C40(rd);
        if (t->vt->flags & 1)
        {
            t->f88 = w;
        }
        s32 m = func_00137CC0(rd);
        if (m == 2)
        {
            t->mode = m;
            t->f80 = func_00137DF8(rd);
            if (t->f80 == 3.4028235e+38f)
            {
                t->f80 = big;
            }
        }
        func_0011EC40(t, rd);
    }
    for (i = 0; i < n; i++)
    {
        c = arr[i];
        if (c->vt->m68 != 0)
        {
            c->vt->m68(c, self);
        }
        c->vt->m64(c, self->parent);
    }
    if (n == 1)
    {
        List01* list = &self->children;
        func_0011ECB8(self->world, self, rd);
        if (func_00152720(list) == 0)
        {
            fr.list = list;
            fr.prev = (Frame_196410*)D_0027B314;
            fr.link = list->offset;
            D_0027B314 = (ListFrame*)&fr;
            c = arr[0];
            h = *(Nd_196410**)list;
            fr.cursor = (u8*)h + fr.link;
            x = h;
            while (x != 0)
            {
                x->vt->m64(x, c);
                Nd_196410* nx = *(Nd_196410**)fr.cursor;
                fr.cursor = (u8*)nx + fr.link;
                x = nx;
            }
            D_0027B314 = (ListFrame*)fr.prev;
        }
    }
    self->desc->m03(self);
    self->desc->m02(self);
}

void func_00196810(C53* self, C53* src)
{
    Pair53 saved = self->kept;
    func_00127048(self, src);
    self->kept = saved;
    List53 list = self->cells;
    func_00152440(&self->cells);
    ListFrame frame;
    Elem_196810* e = (Elem_196810*)list.first;
    while (e != 0) {
        Item_196810* it = (Item_196810*)((C02*)self->parent)->children.head;
        for (; it != 0; it = it->next) {
            if (it->f30 == e) break;
        }
        Cell_196810* cell = (Cell_196810*)func_0018D5C0(16);
        cell->link = self->id;
        if (it != 0) {
            cell->node = it;
            it->f30 = cell;
        } else {
            cell->node = (void*)e->f0;
        }
        func_00152470(&self->cells, cell);
        e = e->next;
    }
}

void func_00196900(C53* self)
{
    func_00124A48(self);
    self->desc->m03(self);
}

void func_00196938(C18* self)
{
    func_001921A8(self);
    self->f61C = -10.0f;
    (*(Quad_196938*)&self->v630) = *(Quad_196938*)D_00248D20;
    self->f688 = 120.0f;
    self->f624 = D_0026A71C;
    self->f628 = D_0026A718;
    func_00152438((Sub_196938*)&self->f6A8, 0x568);
    func_00152438((Sub_196938*)&self->f69C, 0x568);
    *(C18**)&D_0026A904 = self;
}

void func_001969C0(C18* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 1, &D_0026A728);
}

void func_001969F8(C18* self)
{
    s32 arr[32];
    func_00124A48(self);
    func_00124DF8(self, 0xD, &D_0026A738);
    self->f618 = func_00205778(self->rot.r[0].y, self->rot.r[0].x);
    self->f614 = func_001B6290((Any_001969F8*)self->f610, self, -1, 1);
    self->f664 = func_00121228((Root_001969F8*)self->world, self->f65C, (Table_001969F8*)D_0021A790);
    ((Root_001969F8*)self->f664)->b11 = 2;
    func_001299E0((Any_001969F8*)self->f65C, self->f664);
    ((s32*)self->f664)[7] = 1;
    ((Item_001969F8*)self->f664)->p24 = self->f660;
    *(Quad_001969F8*)((u8*)self->f664 + 0x30) = *(Quad_001969F8*)D_00248D30;
    s32 n1 = func_0015A4F0((Any_001969F8*)self->world, 0x305, 0xF, 0, 0, 0);
    self->f690 = n1;
    void* buf = func_0018D500(n1 * 4);
    self->f694 = buf;
    self->f690 = func_0015A4F0((Any_001969F8*)self->world, 0x105, 0xF, 0, self->f690, buf);
    s32 cnt = func_0015A4F0((Any_001969F8*)self->world, 5, 0x44, 0, 0x20, arr);
    for (s32 i = 0; i < cnt; i++) {
        func_00152470((Any_001969F8*)&self->f69C, (void*)arr[i]);
    }
    self->f6B8 = func_001B6290((Any_001969F8*)self->f6B4, 0, -1, 0);
    func_001B6DF8((Any_001969F8*)self->f6B8, self);
}

ASM_FUNC(func_00196B78);

s32 func_00196E48(s32 a0, Obj_196E48* self)
{
    if (self->bits538 & 0x80000000000ULL) {
        if (func_001300E8(self, 0x1F) == 0) return 0;
    }
    return self->f50 != a0;
}

ASM_FUNC(func_00196EB0);

ASM_FUNC(func_001971B8);

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

void func_001974D8(C18* a, void* b)
{
    func_001922E8(a, b);
}

ASM_FUNC(func_001974F8);

void func_00197788(C18* self)
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

void func_00197848(Self_197848* self)
{
    ListFrame frame;
    if (D_00261858[1] < self->time) return;
    s32 i = 0;
    for (; i < self->count; i++) {
        if (func_00182FC8(self->items[i]) == 0) break;
    }
    if (i >= self->count) {
        self->time = 3.4028235e+38f;
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

void func_00197A08(u8* self, Ctx_197A08* ctx)
{
    void* p = ctx->fC14;
    func_001A76A0(p, 0);
    func_00152600(self + 0x6A8, p);
    func_00152470(self + 0x69C, p);
    ctx->fC14 = 0;
}

void func_00197A68(C18* ctx, Pair_00197A68* out)
{
    (void)ctx;
    out->f98 = D_0026A83C;
    out->f94 = D_0026A840;
}

ASM_FUNC(func_00197A88);

void func_00197F10(C18* self, s32 kind, void* rec)
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
            func_001DDC38(self->world, self);
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
                func_001DDC38(self->world, 0);
            }
        }
        return;
    }
}

void func_00198090(C0F* self)
{
    func_001C72A0(self);
}

ASM_FUNC(func_001980B0);

s32 func_001982A0(C0F* self)
{
    Actor_1982A0* actor = (Actor_1982A0*)self;
    s32 r;

    switch (actor->kind) {
    case 2:
        if (func_001C96B8(self) == 0) {
            r = 4;
            break;
        }
        r = func_001C8010(self);
        break;
    case 0x10:
        r = 0x10;
        if (actor->fC10 != 0) {
            r = 0;
        }
        break;
    default:
        r = func_001C8010(self);
        break;
    }
    return r;
}

ASM_FUNC(func_00198318);

void func_001984B8(C0F* self, void* arg)
{
    Actor_1984B8* actor = (Actor_1984B8*)self;
    if (actor->kind == 0x10) {
        void* h = func_001925F0();
        func_00197A08(h, self);
        Quad_1984B8 ctx = actor->q150;
        ctx.c = 0;
        actor->vtbl[36](self, &ctx);
    }
    func_001C9008(self, arg);
}

void func_00198530(C0F* self)
{
    Actor_198530* actor = (Actor_198530*)self;
    func_001C91C8(self);
    if (actor->kind == 0x10) {
        func_001C8920(self);
    }
}

ASM_FUNC(func_00198570);

void func_001986E8(C0F* self, s32 code, Req_1986E8* req)
{
    func_001C9DE0(self, code, req);
    if (code != 10) {
        if (code == 11) {
            if (req->b == (s32)self) {
                self->fC10 = 0;
            }
        }
    } else {
        if (req->b == (s32)self) {
            self->fC10 = req->a;
        }
    }
}

void func_00198760(C0F* s1, f32 f)
{
    Obj_198760* s0 = (Obj_198760*)func_001925F0(s1, f);
    if (func_001300E8(s0, 0x18) != 0) {
        if (s0->f640 != 0) {
            if (func_00182FC8(s0->f640) != 0) {
                if (func_00141170(s0->f640, (u8*)s1 + 0x140) != 0) {
                    Tmp_198760 t;
                    t.f00 = s1;
                    t.f10 = 2;
                    t.f04 = s1;
                    if (func_00177838(&t, 0, 0) != 0) {
                        s32 n = s0->f67C + 1;
                        if (!(n < D_0026A720)) {
                            n = D_0026A720;
                        }
                        s0->f67C = n;
                        if (s0->f698 == 3.4028235e+38f) {
                            s0->f698 = D_0026185C[0] + D_0026A838;
                        }
                    }
                }
            }
        }
    }
    func_001C7CB8(s1, f);
}

u32 func_00198858(void) { return 0; }

ASM_FUNC(func_00198860);

void func_00198920(C48* self)
{
    func_00124DF8(self, 3, (u8*)D_0026A8E0);
    func_00124A48(self);
    Found_198920* p = (Found_198920*)func_0015A838(self->world, 5, 0x18, 0);
    if (p != 0) {
        p->f684 = p->f684 + 1;
    }
}
