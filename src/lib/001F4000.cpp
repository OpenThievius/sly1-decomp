// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

// NEAR: retail saves $ra with sd (Sony 2.9-ee-991111 library code, 0x1F59C4 on); the default compiler saves it with sq. Nothing else differs.

void func_001FA468();
extern u32 D_00277134;

void func_001F7D88() { func_001FA468(); D_00277134 = 0; }

// NEAR: body EXACT; only the save/restore ops differ: retail sd/ld, default flags give sq/lq

typedef void (*Fn_1F7EA8)(s32 arg);
struct Node_1F7EA8 {
    s32 f0;
    u8 pad4[4];
    s32 f8;
    u8 pad12[8];
    s32 f14;
    s32 f18;
    Fn_1F7EA8 f1C;
    s32 f20;
    s32 f24;
};
struct Obj_1F7EA8 { u8 pad[0x1C]; Node_1F7EA8* node; s32 tag; s32 v24; s32 v28; s32 v2C; };
struct Ref_1F7EA8;
void func_001F6B50(Ref_1F7EA8* a);
void func_001F7E58(Ref_1F7EA8* a);

void func_001F7EA8(Obj_1F7EA8* obj) {
    Node_1F7EA8* s0;
    u32 tag = obj->tag;
    if (tag == 0x8000000A) goto call_path;
    if (tag > 0x8000000A) {
        s0 = obj->node;
        goto after;
    }
    if (tag == 0x80000009) goto set_fields;
    s0 = obj->node;
    goto after;
call_path:
    s0 = obj->node;
    if (s0->f1C != 0) {
        s0->f1C(s0->f20);
        s0 = obj->node;
    }
    goto after;
set_fields:
    s0 = obj->node;
    s0->f24 = obj->v24;
    s0->f14 = obj->v28;
    s0->f18 = obj->v2C;
after:
    s32 a0 = s0->f8;
    if (a0 >= 0) func_001F6B50((Ref_1F7EA8*)a0);
    func_001F7E58((Ref_1F7EA8*)s0->f0);
    s0->f0 = 0;
}

struct Ring_001F7E78 {
    u8 pad_00[0x14];
    s32 base;
    s32 count;
    u8 pad_1c[0x08];
    s32 cursor;
};

s32 func_001F7E78(Ring_001F7E78* r)
{
    s32 index = r->cursor % r->count;
    s32 off = index << 6;
    r->cursor = index + 1;
    return r->base + off;
}

struct Ring_1F7F60;
struct Msg_1F7F60 { u8 p0[0x14]; s32 f14; u8 p18[4]; s32 f1C; u32 f20; };
struct Src_1F7F60 { u8 p0[0x14]; s32 f14; u8 p18[4]; s32 f1C; s32 f20; s32 f24; s32 f28; };
struct Ctx_1FA670;

Msg_1F7F60* func_001F7E78(Ring_1F7F60* r);
s32 func_001FA670(Ctx_1FA670* a, Msg_1F7F60* b, s32 c, s32 d, s32 e, s32 f);

void func_001F7F60(Src_1F7F60* src, Ring_1F7F60* ring)
{
    Msg_1F7F60* m = func_001F7E78(ring);
    s32 a = src->f14;
    s32 b = src->f1C;
    m->f14 = a;
    m->f1C = b;
    m->f20 = 0x8000000C;
    func_001FA670((Ctx_1FA670*)0x80000008, m, 0x40, src->f20, src->f24, src->f28);
}

struct Item_1F7DB0 { u8 pad00[0x10]; u32 flags; Item_1F7DB0* next; s32 state; };
struct Owner_1F7DB0 { s32 index; Item_1F7DB0* items; s32 count; };
s32 func_001F9D60(Owner_1F7DB0*);
void func_001F9DA8(void);

Item_1F7DB0* func_001F7DB0(Owner_1F7DB0* self)
{
    func_001F9D60(self);
    s32 count = self->count;
    s32 index = 0;
    Item_1F7DB0* item = self->items;
    if (count > 0) {
        do {
            if ((item->flags & 1) == 0) {
                item->flags = (index << 16) | 5;
                s32 state;
                self->index++;
                if (self->index == 1) {
                    state = self->index++;
                } else {
                    state = self->index;
                }
                item->next = item;
                item->state = state;
                func_001F9DA8();
                return item;
            }
            index++;
            item = (Item_1F7DB0*)((u8*)item + 0x40);
        } while (index < count);
    }
    func_001F9DA8();
    return 0;
}

