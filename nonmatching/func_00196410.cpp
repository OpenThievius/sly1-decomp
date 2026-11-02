// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 1006/1024 (98.2%), checked 2026-11-02
#include "common.h"
// NEAR: 5 lines differ (was 28). The list walk now matches: the head is read as the list's
// first word (`*(Nd_196410**)list`), a plain scalar load, so the scheduler no longer moves it
// above the store to D_0027B314 (a `list->head` field load is an in-struct varying load that
// 2.95's alias check lets pass a fixed scalar store); with that, permute.py found the order
// fr.list, fr.prev, fr.link, push, arr[0], head. Still differs: the second id read. Retail
// keeps it in $v0 and -1 in $v1 (sched1 put the li -1 before the copy from $v0, so local-alloc
// gave -1 $v1 and the value stayed in $v0); ours copies it to $a0 first and -1 takes $v0.
// Tried: assignment in the condition, -1 != res, a local for self->f14, reusing id, s16 return
// and parameter types (func_00137D10 does return an s16): no change.

struct Rd_196410;
struct Nd_196410;
struct VT_196410 {
    u8 pad0[8];
    u32 flags;
    u8 pad0C[0x38 - 0xC];
    void (*m38)(Nd_196410*, Rd_196410*);
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
struct List_196410 { Nd_196410* head; s32 pad4; s32 link; };
struct Cell_196410 { Nd_196410* node; s32 link; };
struct Self_196410 {
    VT_196410* vt;
    u8 pad04[4];
    s32 f08;
    u8 pad0C[0x14 - 0xC];
    void* f14;
    void* f18;
    u8 pad1C[0x34 - 0x1C];
    List_196410 f34;
    u8 pad40[0xD0 - 0x40];
    u8 fD0[0x30];
    u8 f100[0x2D0 - 0x100];
    u8 f2D0[1];
};
struct Frame_196410 {
    List_196410* list;
    u8* cursor;
    s32 link;
    Frame_196410* prev;
};
extern const f32 D_0024C860;
extern Frame_196410* D_0027B314;

void func_00152438(u8* a, s32 v);
void func_00137EB0(Rd_196410* r, u8* out);
void func_00137E70(Rd_196410* r, u8* out);
s32 func_00137B90(Rd_196410* r);
s32 func_00137D10(Rd_196410* r);
Nd_196410* func_001DC208(void* host, s32 a);
Nd_196410* func_0011E580(s32 slot, void* host, s32 z, s32 key, s32 flag);
void func_001DC150(void* host, Nd_196410* n, s32 v);
Cell_196410* func_0018D5C0(s32 n);
void func_00152470(u8* list, Cell_196410* c);
Nd_196410* func_0015A418(void* host, s32 kind, s32 id, Nd_196410* c);
void* func_001C1390(s32 id, void* host);
void func_0011A338(void* a, void* b);
s32 func_00137C40(Rd_196410* r);
s32 func_00137CC0(Rd_196410* r);
f32 func_00137DF8(Rd_196410* r);
void func_0011EC40(Nd_196410* n, Rd_196410* r);
void func_0011ECB8(void* host, Self_196410* self, Rd_196410* r);
s32 func_00152720(List_196410* list);

void func_00196410(Self_196410* self, Rd_196410* rd)
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

    func_00152438(self->f2D0, 8);
    func_00137EB0(rd, self->fD0);
    func_00137E70(rd, self->f100);
    n = func_00137B90(rd);
    if (self->vt->m58 != 0)
    {
        self->vt->m58((Nd_196410*)self);
    }
    for (i = 0; i < n; i++)
    {
        Cell_196410* cell;
        id = func_00137D10(rd);
        if (id == -1)
        {
            c = func_001DC208(self->f14, func_00137D10(rd));
        }
        else
        {
            s32 a = func_00137D10(rd);
            c = func_0011E580(id, self->f14, 0, a, func_00137D10(rd));
            c->vt->m38(c, rd);
            func_001DC150(self->f14, c, func_00137D10(rd));
        }
        cell = func_0018D5C0(16);
        cell->node = c;
        cell->link = self->f08;
        c->f30 = cell;
        func_00152470(self->f2D0, cell);
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
                t = func_0015A418(self->f14, 0x101, id, c);
            }
            if (t != 0)
            {
                break;
            }
        }
        s32 res = func_00137D10(rd);
        if (res != -1)
        {
            void* r = func_001C1390(res, self->f14);
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
            if (t->f80 == D_0024C860)
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
        c->vt->m64(c, self->f18);
    }
    if (n == 1)
    {
        List_196410* list = &self->f34;
        func_0011ECB8(self->f14, self, rd);
        if (func_00152720(list) == 0)
        {
            fr.list = list;
            fr.prev = D_0027B314;
            fr.link = list->link;
            D_0027B314 = &fr;
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
            D_0027B314 = fr.prev;
        }
    }
    ((void (**)(Self_196410*))self->vt)[0x1C / 4](self);
    ((void (**)(Self_196410*))self->vt)[0x18 / 4](self);
}
