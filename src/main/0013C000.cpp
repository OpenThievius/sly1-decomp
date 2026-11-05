// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "timed_state_object.h"
#include "c28.h"
#include "c20.h"
#include "c3b.h"
#include "c05.h"
#include "memory_reader.h"
#include "object_message.h"

void func_001BE4D8(void* p);

s32 func_0013C950(C3B* self)
{
    if (self->slot == 0) {
        func_001BE4D8(&self->slot);
    }
    return (s32)self->slot;
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

void func_001F5A58(void* dst, void* src, s32 n);

s32 func_0013CC80(MemoryReader* self, s32 want, void* dst)
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

typedef void (*Hook_CE40)(void* self);

void func_00124A48(C20* self);
void func_0013CE80(C20* self);
void func_001DBCC8(void* target, Hook_CE40 fn, C20* ctx, s32 a3, s32 a4);

void func_0013CE40(C20* self)
{
    func_00124A48(self);
    func_001DBCC8(self->world, func_0013CE80, self, 0, 0);
}

void func_001B93F8(void* self);

void func_0013D068(C20* self)
{
    func_001B93F8(self);
    if (self->f678 != 0) {
        self->f678 = 0;
        self->desc20()->m48(self);
    }
}

extern u8 D_00261420[];

void func_00141040(void* table, s32 v);
void func_001410A0(void* table, s32 v);

void func_0013D820(C20* self, s32 v)
{
    self->hold = v;
    if (v != 0) {
        func_00141040(D_00261420, self->id688);
    } else {
        func_001410A0(D_00261420, self->id688);
    }
}

void func_0013D868(C20* q, s32 value)
{
    if ((u32)q->count550 < 16) {
        q->slots[q->count550].key = value;
        q->slots[q->count550].kind = 0;
        q->count550++;
    }
}

void func_0013D8B0(C20* q, s32 value)
{
    if ((u32)q->count550 < 16) {
        q->slots[q->count550].key = value;
        q->slots[q->count550].kind = 1;
        q->count550++;
    }
}

void func_0013D950(C20* q, s32 value)
{
    if ((u32)q->count550 < 16) {
        q->slots[q->count550].key = value;
        q->slots[q->count550].kind = 3;
        q->count550++;
    }
}

void func_0013D9E0(C20* state, s32* result) {
	*result = state->mask & 1;
}

void func_0013DA30(C20* state, s32* result) {
	*result = (state->mask >> 2) & 1;
}

void func_0013DA80(C20* r, s32 value)
{
    s32 n = r->count654;
    if ((u32)n < 4) {
        r->list658[n] = (void*)value;
        r->count654 = n + 1;
        r->mask |= 2;
    }
}

extern f32 D_0026185C;
void func_001B93F8(C03* self);

void func_0013DC38(TimedStateObject* self)
{
    s32 next;

    func_001B93F8(self);
    next = self->state;
    if (next != 0) {
        if (next == 1) {
            if (self->tries >= 2 || self->limit < D_0026185C - self->stamp) {
                next = 2;
            }
        }
    }
    SetTimedState(self, next);
}

void func_00127378(TimedStateObject* self, s32 kind, ObjectMessage* msg);

void func_0013DCA8(TimedStateObject* self, s32 kind, ObjectMessage* msg)
{
    func_00127378(self, kind, msg);
    if (kind == 0xF) {
        if ((TimedStateObject*)msg->target == self) {
            SetTimedState(self, 1);
        }
    }
}

void func_0013CCF8(C20* self);

void func_0013DDB8(C21* self)
{
    func_0013CCF8(self);
    self->mask = 5;
    self->f698 = -1;
}

void func_0013DDF0(C25* self)
{
    func_0013CCF8(self);
    self->mask = 1;
    self->scale = 1.0f;
    self->sel6C4 = -1;
    self->sel6C8 = -1;
}

void func_0013DE38(C25* self, u8* table, s32 index);
s32 func_0013DB28(C20* self, s32 value);
s32 func_001300E8(void* node, s32 kind);

void func_0013DEE8(C26* self, u8* table, s32 index)
{
    s32 value;

    func_0013DE38(self, table, index);
    if (self->hold != 0) return;
    value = *(s32*)(table + ((1 - index) << 6));
    if (func_001300E8((void*)value, 5) != 0) {
        if (func_0013DB28(self, value) != 0) {
            self->sel6D4 = (C05*)value;
        }
    }
}

void func_0013D068(C20* self);
void* func_001925F0(void);
void func_001D7098(void* out, void* a1, void* self);

void func_0013DF68(C26* self)
{
    s32 local[4];
    func_0013D068(self);
    if (self->sel6D4 != 0) {
        if (self->sel6D4 != func_001925F0()) {
            self->sel6D4 = 0;
            return;
        }
        func_001D7098(local, self->f6D0, self);
        C05* p = self->sel6D4;
        p->desc05()->m4C(p, local);
        self->sel6D4 = 0;
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

void func_0013E918(void* self)
{
    Zone28* s = (Zone28*)self;
    s->id120 = (s32)func_00140FF8(D_00261420);
    s->f140 = -1;
}

extern u8 D_00261420[];

void func_0013E7C0(void* a, void* b, void* c);
s32 func_00141008(void* table, s32 v);
void func_001DBCC8(void* a, void* fn, void* c, s32 d, s32 e);
void func_0013EAE0(void* self, s32 mode);

void func_0013EA38(Zone28* self)
{
    s32 n;
    Pair28* p;
    void* target;

    self->mode = -1;
    target = self->owner->world;
    p = self->pairs;
    n = 1;
    do {
        func_0013E7C0(target, p, self->owner);
        p++;
    } while (--n >= 0);
    if (self->f11C != 0) {
        if (func_00141008(D_00261420, self->id120)) {
            func_001DBCC8(target, (void*)func_0013EAE0, self, 0, 0);
        }
    }
}

void func_001DBCC8(void* a, void* fn, void* c, s32 d, s32 e);
void func_0013EF50(void* self, s32 a, s32 b);

void func_0013EAE0(void* selfp, s32 mode)
{
    Zone28* self = (Zone28*)selfp;
    if (mode == 0) {
        func_001DBCC8(self->owner->world, (void*)func_0013EAE0, self, 0xC, 0);
    } else {
        func_0013EF50(self, 1, 1);
    }
}

void func_001837E0(void* obj, s32 kind, s32 a, s32 b);
void func_0013ED90(Zone28* self, s32 mode, void* p, s32 flag);

void func_0013F070(Zone28* self, void* p)
{
    func_001837E0(self->owner, 3, 0, 0);
    func_0013ED90(self, 1, p, 0);
    C03* o = self->owner;
    o->desc->m0E(o, 13, self);
}

void func_001B7968(C03* self);
void func_0013E918(void* p);

void func_0013F0E0(C28* self)
{
    func_001B7968(self);
    func_0013E918(&self->zone);
}

void func_001BAC30(C03* self);
void func_0013E950(Zone28* p, C03* self);

void func_0013F110(C28* self)
{
    func_001BAC30(self);
    func_0013E950(&self->zone, self);
}

void func_001BA130(C03* self);

void func_0013F6C0(C28* self)
{
    s32 keep = self->zone.id120;
    func_001BA130(self);
    self->zone.id120 = keep;
    self->zone.owner = self;
}

extern void func_0013EB68(void* state);

void func_0013F6F8(C28* state) {
	func_0013EB68(&state->zone);
}

void func_0013DA48(C20* obj, s32 value) { if ((u32)obj->count640 < 4) { obj->list644[obj->count640++] = (void*)value; obj->mask |= 2; } }

void func_0013DAB8(C20* obj, s32 value) { if ((u32)obj->count668 < 3) { obj->list66C[obj->count668++] = (void*)value; obj->mask |= 2; } }

void func_0013D900(C20* self, s32 value)
{
    if ((u32)self->count550 < 16) {
        self->slots[self->count550].key = value;
        self->slots[self->count550].kind = 2;
        self->count550++;
    }
}

void func_0013D9A0(C20* self, s32 enabled)
{
    if (enabled) {
        self->mask = (self->mask | 1) & ~8;
    } else {
        self->mask &= ~1;
        if (self->mask == 0) self->mask = 8;
    }
}

void func_0013D9F0(C20* self, s32 enabled)
{
    if (enabled) {
        self->mask = (self->mask | 4) & ~8;
    } else {
        self->mask &= ~4;
        if (self->mask == 0) self->mask = 8;
    }
}

void* func_0013DAF0(C20* self)
{
    if (!self->f6B4) func_001BE4D8(&self->f6B4);
    return self->f6B4;
}

void func_0013EC00(void* list, s32 size, void* count, s32 a, s32 b, s32 c, s32 d);
void func_0013EB30(Zone28* self, s32 a, s32 b, s32 c, s32 d)
{
    func_0013EC00(self->table14C, 8, &self->count148, a, b, c, d);
}

void func_001BAC30(void* self);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_00159478(void* sub, void* self);
void func_00182ED8(s32 a);

void func_0013CD80(C20* self)
{
    func_001BAC30(self);
    if (self->f614 == -1) {
        func_00159478(&self->f618, self);
        return;
    }
    s32 v = func_0015A418(self->world, 0x101, self->f614, self);
    self->f618 = v;
    if (v != 0) {
        func_00182ED8(v);
    }
}

struct Self_13E6C8 { u8 pad0[0x10]; s32 f10; };
struct Base_13E6C8 { u8 pad0[0x10]; s32 f10; };

void* func_0018D500(s32 size);

void func_0013E6C8(Self_13E6C8* self, Tree03* src, Base_13E6C8* base, Tree03* dst)
{
    dst->count = src->count;
    dst->count2 = src->count2;
    dst->nodes = (TreeNode03*)func_0018D500(src->count * 12);
    for (s32 i = 0; i < dst->count; i++) {
        TreeNode03* s = &src->nodes[i];
        TreeNode03* d = &dst->nodes[i];
        d->face = (void*)(base->f10 + ((s32)s->face - self->f10));
        d->back = s->back != 0 ? (TreeNode03*)((s32)dst->nodes + ((s32)s->back - (s32)src->nodes)) : 0;
        d->front = s->front != 0 ? (TreeNode03*)((s32)dst->nodes + ((s32)s->front - (s32)src->nodes)) : 0;

    }
}

extern void func_00189150(void*, void*, void*);
f32 func_00188CE0(void* p);
f32 func_00205578(f32 x);

struct Loc_13F940 {
    f32 v[12];
};

s32 func_0013F940(C28* s, f32* out)
{
    Loc_13F940 loc;
    f32 best = 0.0f;
    s32 idx;
    s32 i;

    if (s->count7E0 == 0) {
        return 0;
    }
    for (i = s->count7E0 - 1; i >= 0; i--) {
        Entry28* e = (Entry28*)((u8*)s + 0x7F0 + i * 0x30);
        func_00189150(&s->rot, e, &loc);
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

extern u8 D_00261420[];
void func_001B7968(void* self);
void* func_00140FF8(void* p);

void func_0013CCF8(C20* self)
{
    C20* o = self;
    func_001B7968(self);
    o->f628 = 0.8f;
    o->f62C = 1.2f;
    o->f68C = 1;
    o->f624 = 1.0f;
    o->f2B4 = 16;
    o->tint[3] = 16;
    o->tint[2] = 16;
    o->tint[1] = 16;
    o->tint[0] = 16;
    o->id688 = (s32)func_00140FF8(D_00261420);
    o->f614 = -1;
}

void* func_001925F0(void);
s32 func_001833F0(void* msg, void* item);
s32 func_001300E8(void* msg, void* item);

s32 func_0013DB28(C20* self, C19* msg)
{


    if (self->mask == 0) {
        return 1;
    }
    if (self->mask & 1) {
        if (msg == func_001925F0()) {
            return 1;
        }
    }
    if (self->mask & 4) {
        if (msg->desc->flags & 0x20) {
            return 1;
        }
    }
    if ((self->mask & 2) == 0) {
        return 0;
    }
    for (s32 i = 0; i < self->count640; i++) {
        if (func_001833F0(msg, self->list644[i]) != 0) {
            return 1;
        }
    }
    for (s32 i = 0; i < self->count654; i++) {
        if (func_001300E8(msg, self->list658[i]) != 0) {
            return 1;
        }
    }
    return 0;
}

struct Ent_13EC00 { s32 k1; s32 k2; s32 f8; s32 fC; };

s32 func_0013EC00(Ent_13EC00* tab, s32 cap, s32* count, s32 flag, s32 k1, s32 k2, s32 val)
{
    for (s32 i = 0; i < *count; i++) {
        Ent_13EC00* p = &tab[i];
        if (p->k1 == k1 && (p->k2 == -1 || p->k2 == k2)) {
            if (flag != 0) {
                p->f8 = val;
            } else {
                p->fC = val;
            }
            return 1;
        }
    }
    s32 n = *count;
    if (n + 1 >= cap) {
        return 0;
    }
    *count = n + 1;
    Ent_13EC00* e = (Ent_13EC00*)((n << 4) + (s32)tab);
    e->k1 = k1;
    e->k2 = k2;
    if (flag != 0) {
        e->f8 = val;
        e->fC = -1;
    } else {
        e->fC = val;
        e->f8 = -1;
    }
    return 1;
}

s32 func_0015A198(void* self, s32 kind, s32 key, void* arg, s32 flags, void* out);
void* func_00129C20(void* a, s32 b);
void func_001B64D8(void* a, s32 b);

struct Ent_13ECB0 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
};

s32 func_0013ECB0(void* self, s32 n, Ent_13ECB0* ent, void* arg, s32 flag)
{
    s32 count = 0;
    s32 more;
    void* out;
    if (n > 0) {
        Ent_13ECB0* p = ent;
        do {
            s32 r = func_0015A198(self, 0x304, p->f0, arg, 1, &out);
            if (r != 1) {
                return r;
            }
            void* v = func_00129C20(out, p->f4);
            if (v == 0) {
                count++;
            } else {
                s32 k;
                if (flag != 0) {
                    k = p->f8;
                } else {
                    k = p->fC;
                }
                if (k != -1) {
                    func_001B64D8(v, k);
                }
                count++;
            }
            p++;
            more = count < n;
        } while (more != 0);
    }
    return more;
}

extern f32 D_0026185C;
s32 func_00126D60(f32 value);

void func_0013DD78(TimedStateObject* self, s32 state)
{
    if (state != self->state) {
        *(s32*)((u8*)self + 0x550) = state;
        f32 t = D_0026185C;
        self->stamp = t;
        if (state == 2) {
            (void)func_00126D60(self->param);
        }
    }
}

s32 func_0013DB28(C20* self, s32 value);
void func_001BB058(C25* self, s32 sel);
void func_001BB0C8(C25* self, s32 sel);
void func_0013DE38(C25* self, u8* table, s32 index)
{
    s32 value;
    s32 one;

    if (self->hold != 0) return;
    one = 1;
    value = *(s32*)(table + ((one - index) << 6));
    if (self->f678 != 0) return;
    if (func_0013DB28(self, value) == 0) return;
    if (self->sel6C4 != -1) func_001BB058(self, self->sel6C4);
    if (self->sel6C8 != -1) func_001BB0C8(self, self->sel6C8);
    self->f678 = one;
    self->cur = value;
    self->mass = self->mass * self->scale;
}

extern f32 D_0026185C;
void func_00129DF8(void* self);
void func_0013EF50(void* self, s32 a, s32 b);
void func_0013F070(void* self, void* p);

void func_0013EB68(void* a, s32 b)
{
    Zone28* self = (Zone28*)a;
    s32 old = self->mode;
    if (b == old) {
        return;
    }
    s32 s1 = 0;
    if (old == 0) {
        s1 = (b == 1);
    }
    s32 s2 = 0;
    if (old != -1) {
        if (b == 0) {
            s2 = 1;
        }
    }
    *(s32*)((u8*)self + 0x12C) = b;
    self->stamp = D_0026185C;
    func_00129DF8(self->owner);
    if (s1 != 0) {
        func_0013EF50(self, 0, 0);
    }
    if (s2 != 0) {
        func_0013F070(self, 0);
    }
}

s32 func_001300E8(C03* src, s32 kind);
s32 func_0013DD08(TimedStateObject* node, C03* src)
{
    s32 r;
    if (src->flags538 & (1ULL << 55)) return 0;
    if (node->acceptAll != 0) return 1;
    Child27* c = node->child;
    if (c == 0 || c->f694 == 0) {
        r = func_001300E8(src, 0x27);
        if (r != 0) return 0;
    }
    return 1;
}

s32 func_001833F0(void* a, s32 n);
void func_001F5B08(void* end, void* begin, s32 bytes);

void func_0013F140(C28* self, void* a1, Quad28* q)
{
    s32 n = self->f7B4;
    s32 idx;
    if (func_001833F0(a1, 0x200)) {
        idx = 0;
        if (n > 0) {
            u8* p = (u8*)self + n * 16;
            s32 o = n * 16;
            func_001F5B08((u8*)(o + (s32)self) + 0x7C0, &self->quads[0], o);
        }
    } else {
        idx = n;
    }
    self->quads[idx] = *q;
    self->f7B4++;
}

enum Kind_13EF50 { kind_13EF50_2 = 2 };
struct Tab_13EF50 { u8 pad[1]; };

extern u8 D_00261420[];

void func_001BFCD8(Kind_13EF50 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_0013ED90(Zone28* self, s32 mode, void* p, void* q);
void func_0013EB68(Zone28* self, s32 k);
void func_00141040(Tab_13EF50* t, s32 v);

void func_0013EF50(Zone28* self, void* p, void* q)
{
    if (q != 0) {
        func_001837E0(self->owner, 0x16, 0, 0);
    } else {
        func_001837E0(self->owner, 2, 0, 0);
    }
    if (self->f134 == 0) {
        if (q == 0) {
            func_001BFCD8(kind_13EF50_2, 0, (s32)self->owner, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
    }
    func_0013ED90(self, 0, p, q);
    if (self->f13C == 0) {
        func_0013EB68(self, 2);
    }
    if (self->f11C != 0) {
        func_00141040((Tab_13EF50*)D_00261420, self->id120);
    }
    self->owner->desc->m0E(self->owner, 0xC, self);
}

extern u8 D_00248D30[];

void func_001B9338(C03* self, f32 t);
void func_001B9058(C03* self, void* buf, s32 a, void* table, s32 b, f32 t);
void func_001B91A8(C03* self, void* buf, s32 a, void* table, s32 b, f32 t);

void func_0013FA10(C28* self, f32 t)
{
    func_001B9338(self, t);
    switch (self->state) {
    case 0:
        if (self->f7B4 != 0) {
            u8* p = (u8*)self + 0x7C0;
            if (self->zone.mode != 4) {
                p += self->f7B0 << 4;
            }
            func_001B9058(self, p, (s32)self->p20C, D_00248D30, (s32)self->p210, t);
        }
        break;
    case 1:
        if (self->count7E0 != 0) {
            u8* p = (u8*)self + 0x7F0;
            if (self->zone.mode != 4) {
                p += self->f7B0 * 0x30;
            }
            func_001B91A8(self, p, (s32)self->p214, D_00248D30, (s32)self->p218, t);
        }
        break;
    }
}

extern u8 D_00261420[];

struct Frame_13CE80 { s32 list; s32 cursor; s32 link; s32 prev; s32 out; };
s32 func_00141008(Frame_13CE80* t, s32 v);
s32 func_001300E8(C20* n, s32 kind);
void func_00199C10(C20* n, s32* out);
s32 func_001833F0(C20* n, s32 key);

void func_0013CE80(C20* self)
{
    Frame_13CE80 fr;
    C20* n;
    s32 i;
    Slot20* e;
    if (func_00141008((Frame_13CE80*)D_00261420, self->id688)) self->f678 = 1;
    s32 l = (s32)&self->children;
    fr.cursor = l;
    fr.list = l;
    s32 old = *(s32*)&D_0027B314;
    s32 link = *(s32*)(l + 8);
    *(s32*)&D_0027B314 = (s32)&fr;
    fr.prev = old;
    s32 h = (s32)self->children.head;
    fr.link = link;
    fr.cursor = h + link;
    n = (C20*)h;
    while (n != 0) {
        if (self->f678) {
            if (!func_001300E8(n, 0x2E)) goto next;
            func_00199C10(n, &fr.out);
            if (fr.out) goto next;
        }
        if (func_001300E8(n, 0x75)) goto next;
        if (func_001300E8(n, 0x7A)) goto next;
        if (func_001300E8(n, 0x53)) goto next;
        if (func_001300E8(n, 0x27)) n->slots[1].kind = (s32)self;
        for (i = 0; i < self->count550; i++) {
            e = &self->slots[i];
            if (func_001833F0(n, e->key)) {
                e->node = (s32)n;
                switch (e->kind) {
                case 0:
                case 1:
                case 3:
                    goto next;
                case 2:
                case 4:
                default:
                    break;
                }
                break;
            }
        }
        if (i >= self->count550) {
            e = &self->slots[self->count550];
            self->count550 = self->count550 + 1;
            e->kind = 4;
            e->node = (s32)n;
        }
        n->desc->m03(n);
    next:
        s32 nx = *(s32*)fr.cursor;
        fr.cursor = nx + fr.link;
        n = (C20*)nx;
    }
    *(s32*)&D_0027B314 = fr.prev;
}

extern u8* D_00262E10;
extern f32 D_0026185C;

void func_001B93F8(C03* self);
void func_0013F6F8(C28* self, s32 v);
s32 func_0013F8A0(C28* self, f32* out);
s32 func_0013F940(C28* self, f32* out);
s32 func_0013F718(C28* self, void* p);
void func_00129DF8(void* self);

void func_0013FD20(C28* self)
{
    func_001B93F8(self);
    switch (self->zone.mode) {
    case 2: {
        u8* g = D_00262E10;
        f32 t;
        if (g) {
            if (*(s32*)(g + 0x2220) == 3 && *(s32*)(g + 0x2204) == self->id880) self->zone.stamp = D_0026185C;
        }
        t = self->zone.duration;
        if (0.0f <= t) {
            if (t < D_0026185C - self->zone.stamp) func_0013F6F8(self, 4);
        }
        break;
    }
    case 3:
        break;
    case 4: {
        s32 r = -1;
        switch (self->state) {
        case 0: if (!func_0013F8A0(self, 0)) r = 1; break;
        case 1: if (!func_0013F940(self, 0)) r = 1; break;
        case 2:
        case 4: r = 1; break;
        case 3: r = 0; break;
        }
        if (r != -1) func_0013F6F8(self, r);
        break;
    }
    case 0:
    case 1: {
        s32 r = self->zone.mode;
        s32 st = self->state;
        switch (st) {
        case 3:
            break;
        case 4: {
            u8* g = D_00262E10;
            r = 0;
            if (g) {
                if (*(s32*)(g + 0x2220) == 3) r = *(s32*)(g + 0x2204) == self->id880;
            }
            break;
        }
        case 2: {
            C03* s4 = self->root03();
            ContactRow03* l = s4->contacts->head;
            r = 0;
            for (; l; l = l->next) {
                Contact03* n = l->head;
                for (; n; n = n->next) {
                    s32 k = n->end[0].body != s4;
                    if (((ContactEnd03*)((u8*)n + (k << 6)))->part == self) {
                        if (func_0013F718(self, n->end[1 - k].body)) { r = 1; goto done; }
                    }
                }
            }
            break;
        }
        default: {
            f32 v[2];
            s32 s0;
            s32 lt;
            s32 mode = self->zone.mode;
            r = mode;
            if (st == 0) {
                s0 = func_0013F8A0(self, &v[0]);
                lt = v[0] < 2.0f;
            } else {
                s0 = func_0013F940(self, &v[1]);
                lt = v[1] < 0.1f;
            }
            if (lt) {
                if (s0 == 0 && mode == 1) r = 0;
                else if (s0 == 1 && !mode) r = 1;
            }
            if (self->f7B0 != s0) {
                func_00129DF8(self);
                self->f7B0 = s0;
            }
            break;
        }
        }
    done:
        func_0013F6F8(self, r);
        break;
    }
    }
}

struct Self_13CC00 { u8 pad[4]; };
// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_00249D98[];
s32 func_0013C9D0(Self_13CC00* self, void* a1, MemoryReader* arg);

s32 func_0013CC00(Self_13CC00* self, void* a1, void* a2)
{
    if (a1 != 0) {
        MemoryReader arg;
        arg.methods = (const MemoryReaderMethods*)D_00249D98;
        arg.base = (u8*)a2;
        arg.f10 = a1;
        arg.f08 = a1;
        arg.pos = 0;
        return func_0013C9D0(self, a1, &arg);
    }
    return 0;
}

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
extern const Fn_Table D_00249D98[6] = { 0, 0, 0, (Fn_Table)func_0013CC80, 0, 0 };


void func_001BA130(C20* self, C20* other);
void* func_0018D568(s32 size, void* owner);

void func_0013CDE8(C20* self, C20* other)
{
    s32 saved = self->id688;
    func_001BA130(self, other);
    self->id688 = saved;
    if (other->f6B4)
        self->f6B4 = func_0018D568(0x24, other->f6B4);
}

struct IntList_13E7C0 { s32 count; void* items[1]; };
void* func_0015A418(void*, s32, void*, void*);
void func_0013E8D8(IntList_13E7C0*, void*);
void func_00182ED8(void*);

void func_0013E7C0(void* self, IntList_13E7C0* list, void* context)
{
    s32 n = list->count;
    void** items = list->items;
    for (s32 i = 0; i < n; i++) {
        void* object = func_0015A418(self, 0x104, items[i], context);
        if (object) {
            func_0013E8D8(list, object);
            func_00182ED8(object);
        }
    }
}

struct Desc_13E950 {
    u8 pad0[8];
    u32 f8;
};

struct Node_13E950 {
    Desc_13E950* f0;
};

struct Iter_13E950 { List01* list; u8* link; s32 offset; Iter_13E950* saved; };

struct Call_13E950;


s32 func_0013E868(Call_13E950* set, void* key);
void func_0013E8D8(Call_13E950* queue, void* value);

struct Next_13E950 {
    static Node_13E950* Of(Iter_13E950* it)
    {
        Node_13E950* obj = *(Node_13E950**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct Begin_13E950 {
    static void Of(Iter_13E950* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->saved = ((Iter_13E950*)D_0027B314);
        D_0027B314 = (ListFrame*)it;
    }
};

void func_0013E950(Zone28* self, C03* a1)
{
    Iter_13E950 it;
    Begin_13E950::Of(&it, &a1->children);
    self->owner = a1;
    Node_13E950* node;
    while ((node = Next_13E950::Of(&it)) != 0) {
        if (node->f0->f8 & 0x40) {
            if (func_0013E868((Call_13E950*)((u8*)self + 0x90), node) == 0) {
                if (func_0013E868((Call_13E950*)((u8*)self + 8), node) == 0) {
                    func_0013E8D8((Call_13E950*)((u8*)self + 8), node);
                }
            }
        }
    }
    D_0027B314 = (ListFrame*)it.saved;
}

struct Ring_0013C9D0 {
    u8* buf;
    s32 size;
    s32 pos;
    u8 pad_0c[0x04];
    s32 avail;
    s32 f14;
    u8 pad_18[0x04];
    s32 f1c;
};
s32 func_0013C9D0(Ring_0013C9D0* self, s32 n, MemoryReader* port)
{
    s32 total = 0;
    s32 rem = n;
    if (n <= 0 || self->avail < n) {
        rem = self->avail;
    }
    while (rem != 0) {
        s32 avail = self->size - self->pos;
        s32 cnt = rem < avail ? rem : avail;
        s32 r = port->methods->read((MemoryReader*)((u8*)port + port->methods->adj1), cnt, self->buf + self->pos);
        if (r == 0) {
            break;
        }
        total += r;
        rem -= r;
        self->pos += r;
        self->pos %= self->size;
        self->f14 += r;
        self->avail -= r;
        self->f1c += r;
        if (n <= 0) {
            break;
        }
    }
    return total;
}

struct Self_13CAD8 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
};
typedef s32 (*FnA_13CAD8)(void* self, s32 a1, s32 a2);
typedef s32 (*FnB_13CAD8)(void* self);
struct Vt_13CAD8 {
    u8 pad0[8];
    s16 adj8;
    u8 pad1[2];
    FnA_13CAD8 fn0C;
    s16 adj10;
    u8 pad2[2];
    FnB_13CAD8 fn14;
};
struct Obj_13CAD8 {
    Vt_13CAD8* vt;
};

s32 func_0013CAD8(Self_13CAD8* self, s32 n, Obj_13CAD8* o)
{
    s32 total = 0;
    s32 rem = n;
    if (rem <= 0 || self->f14 < rem)
        rem = self->f14;
    for (;;) {
        if (rem == 0)
            break;
        s32 chunk = self->f4 - self->fC;
        if (rem < chunk)
            chunk = rem;
        s32 s0 = o->vt->fn0C((u8*)o + o->vt->adj8, chunk, self->f0 + self->fC);
        if (s0 == 0)
            break;
        self->fC = (self->fC += s0) % self->f4;
        self->f14 -= s0;
        if (o->vt->fn14((u8*)o + o->vt->adj10) != 0)
            self->f18 += s0;
        else
            self->f10 += s0;
        rem -= s0;
        total += s0;
        if (n <= 0)
            break;
    }
    return total;
}

s32 func_001833F0(void* node, s32 key);
s32 func_001300E8(void* node, s32 kind);

s32 func_0013F718(C28* self, void* arg)
{
    if (self->countIdsIn > 0) {
        s32 i;
        for (i = 0; i < self->countIdsIn; i++) {
            if (func_001833F0(arg, self->idsIn[i]) != 0) {
                break;
            }
        }
        if (i >= self->countIdsIn) {
            return 0;
        }
    } else if (self->countIdsOut > 0) {
        s32 i;
        for (i = 0; i < self->countIdsOut; i++) {
            if (func_001833F0(arg, self->idsOut[i]) != 0) {
                break;
            }
        }
        if (i < self->countIdsOut) {
            return 0;
        }
    }
    if (self->countKindsIn > 0) {
        s32 i;
        for (i = 0; i < self->countKindsIn; i++) {
            if (func_001300E8(arg, self->kindsIn[i]) != 0) {
                break;
            }
        }
        if (i >= self->countKindsIn) {
            return 0;
        }
    } else if (self->countKindsOut > 0) {
        s32 i;
        for (i = 0; i < self->countKindsOut; i++) {
            if (func_001300E8(arg, self->kindsOut[i]) != 0) {
                break;
            }
        }
        if (i < self->countKindsOut) {
            return 0;
        }
    }
    return 1;
}
