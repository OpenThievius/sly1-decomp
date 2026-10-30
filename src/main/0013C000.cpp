// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

struct Slot_13C950 { u8 pad[0x680]; s32 slot; };

void func_001BE4D8(void* p);

s32 func_0013C950(Slot_13C950* self)
{
    if (self->slot == 0) {
        func_001BE4D8(&self->slot);
    }
    return self->slot;
}

struct InitialState {
	s32 field_00;
	s32 field_04;
	s32 field_08;
	s32 field_0C;
	s32 field_10;
	s32 field_14;
	s32 field_18;
	s32 field_1C;
};

extern void func_0013C9B0(InitialState* state);

void func_0013C988(InitialState* state, s32 initialValue, s32 secondaryValue) {
	state->field_04 = initialValue;
	state->field_00 = secondaryValue;
	func_0013C9B0(state);
}

void func_0013C9B0(InitialState* state)
{
    state->field_1C = 0;
    state->field_18 = 0;
    state->field_14 = 0;
    state->field_0C = 0;
    state->field_08 = 0;
    state->field_10 = state->field_04;
}

struct Span_CC48 {
    u8 pad0[0x10];
    s32 a;
    u8 pad1[0x4];
    s32 b;
};

void func_0013CC48(Span_CC48* p, s32 n)
{
    if (n == 0) {
        n = p->b;
        if (n == 0) {
            return;
        }
    }
    p->a += n;
    p->b -= n;
}

struct Cursor_13CC80 {
    u8 pad0[4];
    u8* base;
    u8 pad8[4];
    s32 pos;
    s32 remain;
};

void func_001F5A58(void* dst, void* src, s32 n);

s32 func_0013CC80(Cursor_13CC80* self, s32 want, void* dst)
{
    s32 n = self->remain;
    u8* base = self->base;
    s32 pos = self->pos;
    if (want < n) {
        n = want;
    }
    func_001F5A58(dst, base + pos, n);
    self->pos += n;
    self->remain -= n;
    return n;
}

int func_0013CCE8() {
	return 0;
}

struct Node_CE40 {
    u8 pad0[0x14];
    void* child;
};

typedef void (*Hook_CE40)(void* self);

void func_00124A48(Node_CE40* self);
void func_0013CE80(void* self);
void func_001DBCC8(void* target, Hook_CE40 fn, Node_CE40* ctx, s32 a3, s32 a4);

void func_0013CE40(Node_CE40* self)
{
    func_00124A48(self);
    func_001DBCC8(self->child, func_0013CE80, self, 0, 0);
}

void func_001B93F8(void* self);

typedef void (*VFn_13D068)(void* self);

struct Self_13D068 {
    VFn_13D068* vtbl;
    u8 pad0[0x678 - 4];
    s32 f678;
};

void func_0013D068(void* self0)
{
    Self_13D068* self = (Self_13D068*)self0;
    func_001B93F8(self0);
    if (self->f678 != 0) {
        self->f678 = 0;
        self->vtbl[76](self0);
    }
}

extern u8 D_00261420[];

void func_00141040(void* table, s32 v);
void func_001410A0(void* table, s32 v);

struct Self_13D820 {
    u8 pad0[0x680];
    s32 f680;
    u8 pad1[4];
    s32 f688;
};

void func_0013D820(void* self0, s32 v)
{
    Self_13D820* self = (Self_13D820*)self0;
    self->f680 = v;
    if (v != 0) {
        func_00141040(D_00261420, self->f688);
    } else {
        func_001410A0(D_00261420, self->f688);
    }
}

struct Slot_13D868 {
    s32 x;
    s32 y;
    s32 z;
};

struct Queue_13D868 {
    u8 pad0[0x550];
    s32 count;
    Slot_13D868 slots[16];
};

void func_0013D868(Queue_13D868* q, s32 value)
{
    if ((u32)q->count < 16) {
        q->slots[q->count].y = value;
        q->slots[q->count].x = 0;
        q->count++;
    }
}

struct Slot_13D8B0 {
    s32 x;
    s32 y;
    s32 z;
};

struct Queue_13D8B0 {
    u8 pad0[0x550];
    s32 count;
    Slot_13D8B0 slots[16];
};

void func_0013D8B0(Queue_13D8B0* q, s32 value)
{
    if ((u32)q->count < 16) {
        q->slots[q->count].y = value;
        q->slots[q->count].x = 1;
        q->count++;
    }
}

struct Slot_D950 {
    s32 x;
    s32 y;
    s32 z;
};

struct Queue_D950 {
    u8 pad0[0x550];
    s32 count;
    Slot_D950 slots[16];
};

void func_0013D950(Queue_D950* q, s32 value)
{
    if ((u32)q->count < 16) {
        q->slots[q->count].y = value;
        q->slots[q->count].x = 3;
        q->count++;
    }
}

struct FlagState {
	char padding[0x63C];
	s32 flags;
};

void func_0013D9E0(FlagState* state, s32* result) {
	*result = state->flags & 1;
}

void func_0013DA30(FlagState* state, s32* result) {
	*result = (state->flags >> 2) & 1;
}

struct Ring_DA80 {
    u8 pad0[0x63C];
    u32 flags;
    u8 pad1[0x654 - 0x640];
    s32 count;
    s32 items[4];
};

void func_0013DA80(Ring_DA80* r, s32 value)
{
    s32 n = r->count;
    if ((u32)n < 4) {
        r->items[n] = value;
        r->count = n + 1;
        r->flags |= 2;
    }
}

struct Actor_13DB28 {
    u8 pad0[0x228];
    s32 count_228;
    u8 pad1[0x550 - 0x22C];
    s32 state_550;
    f32 stamp_554;
    f32 limit_558;
    f32 param_55C;
};

extern f32 D_0026185C;
void func_001B93F8(Actor_13DB28* self);
void func_0013DD78(Actor_13DB28* self, s32 state);

void func_0013DC38(Actor_13DB28* self)
{
    s32 next;

    func_001B93F8(self);
    next = self->state_550;
    if (next != 0) {
        if (next == 1) {
            if (self->count_228 >= 2 || self->limit_558 < D_0026185C - self->stamp_554) {
                next = 2;
            }
        }
    }
    func_0013DD78(self, next);
}

struct Msg_13DB28 {
    s32 kind_00;
    Actor_13DB28* target_04;
};

void func_00127378(Actor_13DB28* self, s32 kind, Msg_13DB28* msg);

void func_0013DCA8(Actor_13DB28* self, s32 kind, Msg_13DB28* msg)
{
    func_00127378(self, kind, msg);
    if (kind == 0xF) {
        if (msg->target_04 == self) {
            func_0013DD78(self, 1);
        }
    }
}

struct Track_13DDB8 {
    u8 pad0[0x63C];
    s32 state;
    u8 pad1[0x698 - 0x640];
    s32 flag;
};

void func_0013CCF8(void* self);

void func_0013DDB8(Track_13DDB8* self)
{
    func_0013CCF8(self);
    self->state = 5;
    self->flag = -1;
}

struct Track_13DDF0 {
    u8 pad0[0x63C];
    s32 state;
    u8 pad1[0x6C0 - 0x640];
    f32 scale;
    s32 dropA;
    s32 dropB;
};


void func_0013DDF0(Track_13DDF0* self)
{
    func_0013CCF8(self);
    self->state = 1;
    self->scale = 1.0f;
    self->dropA = -1;
    self->dropB = -1;
}

struct Ctl_13DEE8 {
    u8 pad0[0x368];
    f32 level_368;
    u8 pad1[0x680 - 0x36C];
    s32 hold_680;
    u8 pad2[0x6D4 - 0x684];
    s32 sel_6D4;
};

void func_0013DE38(Ctl_13DEE8* self, u8* table, s32 index);
s32 func_0013DB28(Ctl_13DEE8* self, s32 value);
s32 func_001300E8(void* node, s32 kind);

void func_0013DEE8(Ctl_13DEE8* self, u8* table, s32 index)
{
    s32 value;

    func_0013DE38(self, table, index);
    if (self->hold_680 != 0) return;
    value = *(s32*)(table + ((1 - index) << 6));
    if (func_001300E8((void*)value, 5) != 0) {
        if (func_0013DB28(self, value) != 0) {
            self->sel_6D4 = value;
        }
    }
}

void func_0013D068(void* self);
void* func_001925F0(void);
void func_001D7098(void* out, void* a1, void* self);

typedef void (*VFn_13DF68)(void* self, void* out);
struct Obj_13DF68 { VFn_13DF68* vtbl; };

struct Self_13DF68 {
    u8 pad0[0x6D0];
    void* f6D0;
    Obj_13DF68* f6D4;
};

void func_0013DF68(void* self0)
{
    Self_13DF68* self = (Self_13DF68*)self0;
    s32 local[4];
    func_0013D068(self0);
    if (self->f6D4 != 0) {
        if (self->f6D4 != func_001925F0()) {
            self->f6D4 = 0;
            return;
        }
        func_001D7098(local, self->f6D0, self0);
        Obj_13DF68* p = self->f6D4;
        p->vtbl[80](p, local);
        self->f6D4 = 0;
    }
}

struct Set_0013E868 { s32 count; s32 items[1]; };

s32 func_001833F0(void* key, s32 item);

s32 func_0013E868(Set_0013E868* set, void* key)
{
    s32 i = set->count - 1;
    s32* base = set->items;
    if (i >= 0) {
        s32* p = (s32*)(i * 4 + (s32)base);
        do {
            if (func_001833F0(key, *p) != 0) {
                return 1;
            }
            i--;
            p--;
        } while (i >= 0);
    }
    return 0;
}

struct QueueWithPrefix {
	char padding[0x44];
	s32 count;
	s32 values[16];
};

bool func_0013E8D8(QueueWithPrefix* queue, s32 value) {
	queue->values[queue->count++] = value;
	return queue->count < 16;
}

struct Queue {
	s32 count;
	s32 values[16];
};

bool func_0013E8F8(Queue* queue, s32 value) {
	queue->values[queue->count++] = value;
	return queue->count < 16;
}

extern u8 D_00261420[];
void* func_00140FF8(void* p);

struct Self_13E918 {
    u8 pad0[0x120];
    void* f120;
    u8 pad1[0x140 - 0x124];
    s32 f140;
};

void func_0013E918(void* self)
{
    Self_13E918* s = (Self_13E918*)self;
    s->f120 = func_00140FF8(D_00261420);
    s->f140 = -1;
}

struct Item_13EA38 {
    u8 pad0[0x88];
};

struct Source_13EA38 {
    u8 pad0[0x14];
    void* f14;
};

struct Ctx_13EA38 {
    u8 pad0[0x4];
    Source_13EA38* f4;
    Item_13EA38 items[2];
    u8 pad1[0x4];
    s32 f11C;
    s32 f120;
    u8 pad2[0x8];
    s32 f12C;
};

extern u8 D_00261420[];

void func_0013E7C0(void* a, void* b, void* c);
s32 func_00141008(void* table, s32 v);
void func_001DBCC8(void* a, void* fn, void* c, s32 d, s32 e);
void func_0013EAE0(void* self, s32 mode);

void func_0013EA38(Ctx_13EA38* self)
{
    s32 n;
    Item_13EA38* p;
    void* target;

    self->f12C = -1;
    target = self->f4->f14;
    p = self->items;
    n = 1;
    do {
        func_0013E7C0(target, p, self->f4);
        p++;
    } while (--n >= 0);
    if (self->f11C != 0) {
        if (func_00141008(D_00261420, self->f120)) {
            func_001DBCC8(target, (void*)func_0013EAE0, self, 0, 0);
        }
    }
}

struct Item_13EAE0 {
    u8 pad0[0x88];
};

struct Source_13EAE0 {
    u8 pad0[0x14];
    void* f14;
};

struct Ctx_13EAE0 {
    u8 pad0[0x4];
    Source_13EAE0* f4;
    Item_13EAE0 items[2];
};

void func_001DBCC8(void* a, void* fn, void* c, s32 d, s32 e);
void func_0013EF50(void* self, s32 a, s32 b);

void func_0013EAE0(void* selfp, s32 mode)
{
    Ctx_13EAE0* self = (Ctx_13EAE0*)selfp;
    if (mode == 0) {
        func_001DBCC8(self->f4->f14, (void*)func_0013EAE0, self, 0xC, 0);
    } else {
        func_0013EF50(self, 1, 1);
    }
}

typedef void (*VFn_13F070)(void* self, s32 code, void* arg);
struct Node_13F070 { VFn_13F070* vtbl; };
struct Ctl_13F070 {
    u8 pad0[4];
    Node_13F070* obj4;
};

void func_001837E0(void* obj, s32 kind, s32 a, s32 b);
void func_0013ED90(void* self, s32 mode, void* p, s32 flag);

void func_0013F070(Ctl_13F070* self, void* p)
{
    func_001837E0(self->obj4, 3, 0, 0);
    func_0013ED90(self, 1, p, 0);
    Node_13F070* o = self->obj4;
    o->vtbl[18](o, 13, self);
}

void func_001B7968(void* self);
void func_0013E918(void* p);

void func_0013F0E0(void* self)
{
    func_001B7968(self);
    func_0013E918((u8*)self + 0x554);
}

void func_001BAC30(void* self);
void func_0013E950(void* p, void* self);

void func_0013F110(void* self)
{
    func_001BAC30(self);
    func_0013E950((u8*)self + 0x554, self);
}

struct Ctl_13F6C0 {
    u8 pad0[0x558];
    Ctl_13F6C0* self558;
    u8 pad1[0x674 - 0x55C];
    void* p674;
};

void func_001BA130(void* self);

void func_0013F6C0(Ctl_13F6C0* self)
{
    void* keep = self->p674;
    func_001BA130(self);
    self->p674 = keep;
    self->self558 = self;
}

extern void func_0013EB68(void* state);

void func_0013F6F8(void* state) {
	func_0013EB68((char*)state + 0x554);
}

struct Obj_0013DA48 { u8 pad[0x63C]; u32 flags; u32 count; u32 values[4]; };
void func_0013DA48(Obj_0013DA48* obj, s32 value) { if (obj->count < 4) { obj->values[obj->count++] = value; obj->flags |= 2; } }

struct Obj_13DAB8 { u8 pad[0x63C]; u32 flags; u8 gap[0x28]; u32 count; u32 values[4]; };
void func_0013DAB8(Obj_13DAB8* obj, s32 value) { if (obj->count < 3) { obj->values[obj->count++] = value; obj->flags |= 2; } }

void func_0013D900(Queue_D950* self, s32 value)
{
    if ((u32)self->count < 16) {
        self->slots[self->count].y = value;
        self->slots[self->count].x = 2;
        self->count++;
    }
}

void func_0013D9A0(FlagState* self, s32 enabled)
{
    if (enabled) {
        self->flags = (self->flags | 1) & ~8;
    } else {
        self->flags &= ~1;
        if (self->flags == 0) self->flags = 8;
    }
}

void func_0013D9F0(FlagState* self, s32 enabled)
{
    if (enabled) {
        self->flags = (self->flags | 4) & ~8;
    } else {
        self->flags &= ~4;
        if (self->flags == 0) self->flags = 8;
    }
}

struct State_0013DAF0 { u8 pad[0x6B4]; void* slot; };
void* func_0013DAF0(State_0013DAF0* self)
{
    if (!self->slot) func_001BE4D8(&self->slot);
    return self->slot;
}

void func_0013EC00(void* list, s32 size, void* count, s32 a, s32 b, s32 c, s32 d);
void func_0013EB30(u8* self, s32 a, s32 b, s32 c, s32 d)
{
    func_0013EC00(self + 0x14C, 8, self + 0x148, a, b, c, d);
}

struct Obj_13CD80 { u8 pad0[0x14]; void* f14; u8 pad1[0x5FC]; s32 f614; s32 f618; };

void func_001BAC30(void* self);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_00159478(void* sub, void* self);
void func_00182ED8(s32 a);

void func_0013CD80(Obj_13CD80* self)
{
    func_001BAC30(self);
    if (self->f614 == -1) {
        func_00159478(&self->f618, self);
        return;
    }
    s32 v = func_0015A418(self->f14, 0x101, self->f614, self);
    self->f618 = v;
    if (v != 0) {
        func_00182ED8(v);
    }
}

struct Elem_13E6C8 { s32 f0; s32 f4; s32 f8; };
struct Tbl_13E6C8 { s32 count; s32 f4; Elem_13E6C8* elems; };
struct Self_13E6C8 { u8 pad0[0x10]; s32 f10; };
struct Base_13E6C8 { u8 pad0[0x10]; s32 f10; };

void* func_0018D500(s32 size);

void func_0013E6C8(Self_13E6C8* self, Tbl_13E6C8* src, Base_13E6C8* base, Tbl_13E6C8* dst)
{
    dst->count = src->count;
    dst->f4 = src->f4;
    dst->elems = (Elem_13E6C8*)func_0018D500(src->count * 12);
    for (s32 i = 0; i < dst->count; i++) {
        Elem_13E6C8* s = &src->elems[i];
        Elem_13E6C8* d = &dst->elems[i];
        d->f0 = base->f10 + (s->f0 - self->f10);
        d->f4 = s->f4 != 0 ? (s32)dst->elems + (s->f4 - (s32)src->elems) : 0;
        d->f8 = s->f8 != 0 ? (s32)dst->elems + (s->f8 - (s32)src->elems) : 0;
    }
}

extern void func_00189150(void*, void*, void*);
f32 func_00188CE0(void* p);
f32 func_00205578(f32 x);

struct Entry_13F940 {
    u8 pad0[0x30];
};

struct Self_13F940 {
    u8 pad0[0x7E0];
    s32 f7E0;
    u8 pad1[0x7F0 - 0x7E4];
    Entry_13F940 entries[1];
};

struct Loc_13F940 {
    f32 v[12];
};

s32 func_0013F940(void* self, f32* out)
{
    Self_13F940* s = (Self_13F940*)self;
    Loc_13F940 loc;
    f32 best = 0.0f;
    s32 idx;
    s32 i;

    if (s->f7E0 == 0) {
        return 0;
    }
    for (i = s->f7E0 - 1; i >= 0; i--) {
        Entry_13F940* e = (Entry_13F940*)((u8*)s + 0x7F0 + i * 0x30);
        func_00189150((u8*)s + 0xD0, e, &loc);
        f32 t = func_00188CE0(&loc);
        if (best < t) {
            best = t;
            idx = i;
        }
    }
    if (out != 0) {
        *out = func_00205578(best);
    }
    return idx;
}

struct Obj_13CCF8 {
    u8 pad0[0x2B0];
    u8 f2B0;
    u8 f2B1;
    u8 f2B2;
    u8 f2B3;
    u8 f2B4;
    u8 pad1[0x614 - 0x2B5];
    s32 f614;
    u8 pad2[0x624 - 0x618];
    f32 f624;
    f32 f628;
    f32 f62C;
    u8 pad3[0x688 - 0x630];
    s32 f688;
    s32 f68C;
};

extern u8 D_00261420[];

void func_001B7968(Obj_13CCF8* self);
s32 func_00140FF8(Obj_13CCF8* p);

void func_0013CCF8(Obj_13CCF8* self)
{
    func_001B7968(self);
    self->f628 = 0.8f;
    self->f62C = 1.2f;
    self->f68C = 1;
    self->f624 = 1.0f;
    self->f2B4 = 16;
    self->f2B3 = 16;
    self->f2B2 = 16;
    self->f2B1 = 16;
    self->f2B0 = 16;
    self->f688 = func_00140FF8((Obj_13CCF8*)D_00261420);
    self->f614 = -1;
}

struct Sub_13EF50 { u8 pad[1]; };
enum Kind_13EF50 { kind_13EF50_2 = 2 };
struct Tab_13EF50 { u8 pad[1]; };
struct Obj_13EF50 {
    u8 pad0[4];
    Sub_13EF50* p4;
    u8 pad1[0x11C - 8];
    s32 f11C;
    s32 f120;
    u8 pad2[0x134 - 0x124];
    s32 f134;
    u8 pad3[4];
    s32 f13C;
};
typedef void (*VFn_13EF50)(void* self, s32 k, void* a);

extern u8 D_00261420[];

void func_001837E0(Sub_13EF50* a, s32 b, s32 c, s32 d);
void func_001BFCD8(Kind_13EF50 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_0013ED90(Obj_13EF50* self, s32 mode, void* p, void* q);
void func_0013EB68(Obj_13EF50* self, s32 k);
void func_00141040(Tab_13EF50* t, s32 v);

void func_0013EF50(Obj_13EF50* self, void* p, void* q)
{
    if (q != 0) {
        func_001837E0(self->p4, 0x16, 0, 0);
    } else {
        func_001837E0(self->p4, 2, 0, 0);
    }
    if (self->f134 == 0) {
        if (q == 0) {
            func_001BFCD8(kind_13EF50_2, 0, (s32)self->p4, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
    }
    func_0013ED90(self, 0, p, q);
    if (self->f13C == 0) {
        func_0013EB68(self, 2);
    }
    if (self->f11C != 0) {
        func_00141040((Tab_13EF50*)D_00261420, self->f120);
    }
    {
        void** vt = *(void***)self->p4;
        ((VFn_13EF50)vt[0x48 / 4])(self->p4, 0xC, self);
    }
}
