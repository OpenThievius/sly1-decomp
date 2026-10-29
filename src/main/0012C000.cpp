// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

s32 func_0012C288(void* a, void* b, s32 c, s32 d, s32 e, s32 f);

s32 func_0012C7B0(void* a, void* b, s32 c, s32 d)
{
    return func_0012C288(a, b, 0, 0, c, d);
}

struct Obj_12C9A8 { u8 pad[0x5C]; s32 count; u8* table; };

s32 func_0012C9A8(Obj_12C9A8* a0)
{
    s32 n = a0->count;
    if (n > 0) {
        s32 i = 0;
        u8* p = a0->table + 4;
        do {
            i++;
            if (*(s32*)p == 0x19) return 1;
            p += 0x10;
        } while (i < n);
    }
    return 0;
}

struct Obj_12D398 { u8 pad[0x9C]; s32 f9C; };

void* func_0012CCE8(void);
void func_0012D2A8(Obj_12D398* a, void* b);

void func_0012D398(Obj_12D398* a0)
{
    if (a0->f9C == 0) {
        void* r = func_0012CCE8();
        if (r) func_0012D2A8(a0, r);
    }
}

struct Node_12D570 { u8 pad0[4]; void* item; u8 pad1[0x18]; Node_12D570* next; };
struct Obj_12D570 { u8 pad[0x44]; Node_12D570* head; };

s32 func_001833F0(void* a, void* b);

Node_12D570* func_0012D570(Obj_12D570* a0, void* a1)
{
    s32 scratch[4];
    Node_12D570* n = a0->head;
    while (n) {
        if (func_001833F0(n->item, a1)) return n;
        n = n->next;
    }
    (void)scratch;
    return 0;
}

struct Node_12F190 { u8 pad[0x20]; Node_12F190* next; };
struct Obj_12F190 { u8 pad[0x44]; Node_12F190* head; };

void func_00121648(void* n, void* b);

void func_0012F190(Obj_12F190* a0, void* a1)
{
    s32 scratch[4];
    Node_12F190* n = a0->head;
    while (n) {
        func_00121648(n, a1);
        n = n->next;
    }
    (void)scratch;
}

struct Mid_12F7E0 { u8 pad[0x14]; void* p14; };
struct Obj_12F7E0 { u8 pad[8]; Mid_12F7E0* mid; };

void func_001831E8(void* a, void* b, void* c, s32 d);

void func_0012F7E0(Obj_12F7E0* a0, void* a1, s32 a2)
{
    func_001831E8(a0->mid->p14, (u8*)a0 + 0xE4, a1, a2);
}

struct Obj_12FCB0 { u8 pad[0x554]; s32 count; void* items[1]; };

void func_0012FCB0(Obj_12FCB0* a0, void* a1)
{
    a0->items[a0->count++] = a1;
}

struct Obj_12FDE8 { s32 state; s32 f4; s32 f8; };

s32 func_0012FF10(Obj_12FDE8* self);
void func_001F8C38(s32 h);
void func_002032C8(s32 x);
void func_0012FFE8(Obj_12FDE8* self);

void func_0012FDE8(Obj_12FDE8* a0)
{
    switch (a0->state) {
    case 0:
        if (a0->f4 >= 0) func_001F8C38(a0->f4);
        a0->f4 = -1;
        break;
    case 1:
        if (func_0012FF10(a0)) {
            func_002032C8(0);
            func_0012FFE8(a0);
        }
        a0->f8 = 0;
        break;
    }
    a0->state = -1;
}
