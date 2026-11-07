// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 215/232 (92.7%), checked 2026-11-06
// NEAR: registers only: every instruction lines up once the last test is `if (base == 0)` and the
//       table is read through a pointer local; temporaries differ in the two table paths. The
//       tables are Sjis_274588 in 001E4000.cpp.
#include "common.h"
#include "script_value.h"
#include "cursor_animator.h"
#include "switched_collider.h"
#include "list_iter.h"
#include "collider.h"
#include "state_graph.h"
#include "c54.h"
#include "world.h"
#include "attachment.h"
#include "state_walker.h"
#include "globals.h"

void func_001B4AA0(CursorAnimator* self, const AnimatorParams* src);
void func_001B4AD0(CursorAnimator* self);
void func_001B46E0(AnimCursor* cur, s32 idx);
void func_001B4750(AnimCursor* cur, f32 x, f32 y);
AnimRecord* func_001B4688(s32 key);
extern AnimCursor* D_00274544;
extern AnimCursor* D_0027451C;

f32 func_001EAAE0(f32 a, f32 b);

void func_001B4BC8(FrameRunAnimator* p)
{
    func_001B4AD0(p);
    if (p->cursor.record != 0) {
        f32 a = func_001EAAE0(p->durMin, p->durMax);
        p->rate = (f32)p->cursor.record->count / a;
        f32 b = func_001EAAE0(p->waitMin, p->waitMax);
        p->wait0 = b;
        p->wait = b;
    }
}

f32 func_001B4D18(FrameRunAnimator* p)
{
    return (p->pos / p->rate) / ((f32)p->cursor.record->count / p->rate + p->wait0);
}


void func_001B4D48(FramePingPongAnimator* p, AnimatorParams* s)
{
    func_001B4AA0(p, s);
    p->durMin = s->f4;
    p->durMax = s->f8;
    p->waitMin = s->fC;
    p->waitMax = s->f10;
    p->pos = (f32)s->u14;
}

f32 func_001B4F18(FramePingPongAnimator* p)
{
    f32 x = p->rate;
    f32 a;
    if (x < 0.0f) {
        x = -x;
        a = (f32)(p->cursor.record->count << 1) - p->pos;
    } else {
        a = p->pos;
    }
    return (a / x) / ((f32)(p->cursor.record->count << 1) / x + p->wait0);
}


void func_001B4F80(RandomJumpAnimator* p, AnimatorParams* s)
{
    func_001B4AA0(p, s);
    p->waitMin = s->f4;
    p->waitMax = s->f8;
}


void func_001B5108(AngleFrameAnimator* p)
{
    func_001B4AD0(p);
    if (p->cursor.record != 0) {
        s32 n = p->cursor.record->count;
        if (n >= 2) {
            p->step = p->sector / (f32)n;
        }
    }
}

struct Vec2_1B5160 { f32 x; f32 y; };
struct Inner_1B5160 { u8 pad0[0x34]; s32 i34; };
struct Other_1B5160 {
    void* vt; u8 pad0[0xC]; Vec2_1B5160 vec; u8 pad1[0x60]; Inner_1B5160* p78;
};

extern u8 func_00166690[];
f32 func_00205778(f32 a, f32 b);
f32 func_001EAFE0(f32 a, f32 b);

void func_001B5160(AngleFrameAnimator* p, void* unused, Other_1B5160* q)
{
    if (p->cursor.record == 0) {
        return;
    }
    if (p->cursor.record->count < 2) {
        return;
    }
    if (*(void**)q != (void*)func_00166690) {
        return;
    }
    Vec2_1B5160* vv;
    if (q->p78->i34 != 0) {
        vv = &q->vec;
    } else {
        vv = (Vec2_1B5160*)D_00261990->g80;
    }
    f32 t = func_00205778(vv->y, vv->x);
    f32 r = func_001EAFE0(p->phase - t, p->sector);
    s32 k = (s32)(r / p->step);
    func_001B46E0(&p->cursor, k);
}

f32 func_002058A0(f32 a, f32 b);

void func_001B5278(ScrollAnimator* p, f32 t)
{
    if (p->cursor.record != 0) {
        f32 r1 = func_002058A0(p->cursor.u + p->velU * p->mulU * t, p->wrapU);
        f32 r2 = func_002058A0(p->cursor.v + p->velV * p->mulV * t, p->wrapV);
        func_001B4750(&p->cursor, r1, r2);
    }
}

void func_001B5388(ScrollAnimator* p, f32 a, f32 b)
{
    p->mulU = a;
    p->mulV = b;
}


void func_001B4750(AnimCursor* a0, f32 a, f32 b)
{
    if (a0->record == 0) return;
    if (a0->u == a && a0->v == b) return;
    a0->u = a;
    AnimCursor* v = a0->next;
    a0->v = b;
    if (v != 0) return;
    if (a0 == D_00274544) return;
    if (D_00274544 == 0) D_00274544 = a0;
    a0->next = D_0027451C;
    D_0027451C = a0;
}

extern f32 D_0026185C;

s32 func_001B4B08(CursorAnimator* a0)
{
    if (a0->stamp != D_0026185C) {
        a0->stamp = D_0026185C;
        return 1;
    }
    return 0;
}

struct Vec2_1B55A8 { f32 x; f32 y; };

void func_001B55A8(Vec2_1B55A8* a0, Vec2_1B55A8* a1)
{
    a0->x = a1->x;
    a0->y = a1->y;
}

struct Walk_1B5D80 { s32 a; u32 b; u32 c; };

void func_001B5D80(Walk_1B5D80* s, s32 v, s32 n)
{
    u32 cur = s->b;
    s->a = v;
    s->c = cur;
    for (s32 i = 1; i < n; i++) {
        u32 prev = cur;
        s32 a = s->a;
        cur = s->b + i * a;
        *(u32*)prev = cur;
    }
    *(u32*)cur = 0;
}

void func_001B5F28(Pool6C* list, Attachment* item)
{
    if (item) {
        item->vt = (const T2195_Vt*)list->head;
        list->head = item;
    }
}

u32 func_001B6420(StateGraph* a0, s32 a1)
{
    a1 = (a1 << 3) + (u32)a0->f38;
    return *(u32*)a1;
}

struct Obj_1B65F8 {
    u8 pad0[0x24];
    void* f24;
    u8 pad1[0x10];
    f32 f38;
};

void func_0012F6B0(void* p);

void func_001B65F8(Obj_1B65F8* self, f32 v)
{
    self->f38 = v;
    if (self->f24 != 0) {
        func_0012F6B0(self->f24);
    }
}

struct Slot_1B71C8 {
    void* first;
    s32 second;
};

struct Self_1B71C8 {
    u8 pad0[0xCD4];
    s32 count;
    u8 pad1[4];
    Slot_1B71C8 slots[1];
};

s32 func_001300E8(void* a, s32 b);
s32 func_00182F40(Collider* e, void* b);

s32 func_001B71C8(Self_1B71C8* self, Collider* ent)
{
    if (ent->flags538 & (1ULL << 43)) {
        return 0;
    }
    if (func_001300E8(ent->root, 5) != 0) {
        return 0;
    }
    if (func_001300E8(ent->root, 0x4C) != 0) {
        return 0;
    }
    for (s32 i = 0; i < self->count; i++) {
        if (func_00182F40(ent, self->slots[i].first) != 0) {
            return 0;
        }
    }
    return 1;
}

void func_0015FCD8(C09* self, void* p);
void func_001BF048(void* p);

void func_001B7920(C09* self, void* p)
{
    func_0015FCD8(self, p);
    if (p != 0) {
        func_001BF048(self->fCC0);
        self->fCC0 = 0;
    }
}

struct Entry_1B65C8 { s32 value; s32 extra; };
struct Host_1B65C8 { u8 pad[0x38]; Entry_1B65C8* entries; };
struct Node_1B65C8 { u8 pad[0x18]; Host_1B65C8* host; u8 pad2[0x2C - 0x1C]; s32 index; };

void func_001B65C8(Node_1B65C8* self, s32* out)
{
    s32 value;
    if (self->index >= 0) {
        value = self->host->entries[self->index].value;
    } else {
        value = -1;
    }
    *out = value;
}

struct Node_1B6C68 {
    u8 pad[0x28];
    s32 f28;
    s32 index;
};

void func_001B6E28(Node_1B6C68* self, s32 a, s32 b);

void func_001B6C68(Node_1B6C68* self)
{
    func_001B6E28(self, self->f28, self->index);
    s32 v = self->index;
    self->index = -1;
    self->f28 = v;
}

struct Node_1B6CA8 {
    u8 pad[0x24];
    s32 f24;
};

void func_001B6C68(Node_1B6CA8* self);
void func_001B66A0(Node_1B6CA8* self);

void func_001B6CA8(Node_1B6CA8* self, s32 a, s32 b)
{
    if (a == 5 && b == self->f24) {
        func_001B6C68(self);
        func_001B66A0(self);
    }
}

typedef void (*VFn_1B6D78)(void* self);
struct Obj_1B6D78 { VFn_1B6D78* vtbl; };
typedef void (*Cb_1B6D78)(void* obj, s32 a, s32 b);
struct Link_1B6D78 {
    Cb_1B6D78 fn;
    void* obj;
    u8 pad[0x8];
    Link_1B6D78* next;
};
struct Node_1B6D78 {
    u8 pad[0x1C];
    Obj_1B6D78* f1C;
    u8 pad2[0x3C - 0x20];
    Link_1B6D78* f3C;
};

void func_001B6D78(Node_1B6D78* self, s32 a, s32 b)
{
    Obj_1B6D78* o = self->f1C;
    if (o != 0) {
        o->vtbl[18](o);
    }
    Link_1B6D78* link = self->f3C;
    if (link != 0) {
        do {
            void* obj = link->obj;
            Cb_1B6D78 fn = link->fn;
            link = link->next;
            fn(obj, a, b);
        } while (link != 0);
    }
}

struct Entry_1B6E28 { s32 value; s32 extra; };
struct Node_1B6E28 { u8 pad[0x18]; StateGraph* host; };

void func_001837E0(StateGraph* host, s32 a, s32 b, void** args);

void func_001B6E28(Node_1B6E28* self, s32 idx1, s32 idx2)
{
    void* args[3];
    s32 v1;
    s32 v2;
    if (idx1 >= 0) {
        v1 = ((Entry_1B6E28*)self->host->f38)[idx1].value;
    } else {
        v1 = -1;
    }
    if (idx2 >= 0) {
        v2 = ((Entry_1B6E28*)self->host->f38)[idx2].value;
    } else {
        v2 = -1;
    }
    args[0] = &self;
    args[1] = &v1;
    args[2] = &v2;
    func_001837E0(self->host, 0xE, 3, args);
}


void func_001B46E0(AnimCursor* a0, s32 a1)
{
    if (a0->record != 0) {
        s32 hi = a0->record->count - 1;
        if (a1 < 0) {
            a1 = 0;
        } else {
            a1 = (hi < a1) ? hi : a1;
        }
        if (a0->frame != a1) {
            AnimCursor* n = a0->next;
            a0->frame = a1;
            if (n == 0) {
                if (a0 != D_00274544) {
                    if (D_00274544 == 0) {
                        D_00274544 = a0;
                    }
                    a0->next = D_0027451C;
                    D_0027451C = a0;
                }
            }
        }
    }
}


void func_001694A0(void* p);

void func_001B47C0(void)
{
    AnimCursor* n = D_0027451C;
    while (n != 0) {
        for (FrameLink* e = n->links; e != 0; e = e->next) {
            if (n->flags & 1) {
                e->dst->value = e->src->base + ((n->frame * e->src->stride) << 4);
            }
            func_001694A0(e->dst);
        }
        AnimCursor* nx = n->next;
        n->next = 0;
        n = nx;
    }
    D_0027451C = 0;
    D_00274544 = 0;
}

extern s32 D_0027453C;
extern CursorAnimator** D_00274540;

s32 func_001B4B08(CursorAnimator* p);

void func_001B4878(f32 t)
{
    for (s32 i = 0; i < D_0027453C; i++) {
        CursorAnimator* o = D_00274540[i];
        if (func_001B4B08(o) != 0) {
            void (*fn)(CursorAnimator*, f32) = o->methods->step;
            if (fn != 0) {
                fn(o, t);
            }
        }
    }
}

s32 func_00137BE0(void* a);
s32 func_001B4920(s32 type);
void* func_0018D5C0(s32 size);
void* func_001B4980(s32 type);
void func_00137A60(void* owner, s32 key, void* out);

CursorAnimator* func_001B4A10(void* a0)
{
    s32 type = func_00137BE0(a0);
    CursorAnimator* result = 0;
    if (type != 0) {
        CursorAnimator* o = (CursorAnimator*)func_0018D5C0(func_001B4920(type));
        void* vt = func_001B4980(type);
        o->type = type;
        o->methods = (const CursorAnimatorMethods*)vt;
        u32 buf[8];
        func_00137A60(a0, 0x1C, buf);
        o->methods->load(o, (AnimatorParams*)buf);
        result = o;
    }
    return result;
}

struct Node_1B5EA0 { Node_1B5EA0* next; };
struct Pool_1B5EA0 { u8 pad[8]; Node_1B5EA0* head; };

void* func_001B5EA0(Pool_1B5EA0* pool)
{
    Node_1B5EA0* n = pool->head;
    if (n != 0) {
        pool->head = n->next;
    }
    return n;
}

struct Node_1B5EC0 { Node_1B5EC0* next; };
struct Pool_1B5EC0 { u8 pad[8]; Node_1B5EC0* head; };

void* func_001B5EA0(Pool_1B5EC0* pool);

void* func_001B5EC0(Pool_1B5EC0* pool)
{
    return func_001B5EA0(pool);
}

struct Node_1B5EE0 { Node_1B5EE0* next; };
struct Pool_1B5EE0 { s32 count; u8 pad[4]; Node_1B5EE0* head; };

void* func_001B5EA0(Pool_1B5EE0* pool);
void func_001F5C0C(void* p, int zero, s32 count);

void* func_001B5EE0(Pool_1B5EE0* pool)
{
    void* p = func_001B5EA0(pool);
    func_001F5C0C(p, 0, pool->count);
    return p;
}

void func_00138828(void* owner, void* self);
Contacts03* func_001DC7D0(void* owner, void* self);
void func_00138F28(void* owner, void* self);
void func_00152470(void* p, void* self);
void func_001240F8(void* self);
void func_001B7C40(Collider* self, s32 flag);
void func_001BB580(void* p);
void func_001BB4A0(void* self);

void func_001B7A98(Collider* self)
{
    World* owner = self->world;
    owner->count34++;
    if (self->parent == 0) {
        func_00138828(owner, self);
        self->contacts = func_001DC7D0(owner, self);
        func_00138F28(owner, self);
        owner->count38++;
        func_00152470(&owner->bodies, self);
    }
    func_001240F8(self);
    func_001B7C40(self, 1);
    self->desc03()->m44(self);
    if (!(self->flags538 & (1ULL << 54))) {
        func_001BB580(self->root03());
    } else {
        func_001BB580(self);
    }
    func_001BB4A0(self);
}

void func_001243E0(void* self);
void func_001388A0(void* owner, void* self);
void func_001DC828(void* owner, Contacts03* contacts);
void func_00152600(void* p, void* self);
void func_001DC108(void* owner, Touch03* list);

void func_001B7B78(Collider* self)
{
    Collider* old50 = self->root03();
    World* owner = self->world;
    func_001B7C40(self, 0);
    func_001243E0(self);
    owner->count34--;
    if (self->parent == 0) {
        func_001388A0(owner, self);
        func_001DC828(owner, self->contacts);
        owner->count38--;
        func_00152600(&owner->bodies, self);
    }
    func_001DC108(owner, self->touching);
    u64 flags = self->flags538;
    self->touching = 0;
    if (!(flags & (1ULL << 54)) && old50 != self) {
        func_001BB580(old50);
    }
}

void func_00138BE0(void* owner, void* self, s32 n);

void func_001B7C40(Collider* self, s32 flag)
{
    if (flag == ((self->flags538 >> 50) & 1)) {
        return;
    }
    if (flag != 0) {
        func_00152470(&self->root03()->parts, self);
    } else {
        func_00152600(&self->root03()->parts, self);
    }
    self->flags538 = (self->flags538 & ~(1ULL << 50)) | ((u64)(flag & 1) << 50);
    func_00138BE0(self->world, self, 7);
    Collider* sub = self->root03();
    sub->desc03()->m32(sub);
}

void func_001B4AA0(CursorAnimator* self, const AnimatorParams* src)
{
    s32 old = self->cursor.flags;
    self->recordKey = src->recordKey;
    self->cursor.flags = old | 1;
    if (src->flag != 0) {
        self->cursor.flags = old | 5;
    }
}


void func_001B4AD0(CursorAnimator* self)
{
    if (self->cursor.record == 0) {
        self->cursor.record = func_001B4688(self->recordKey);
    }
}

f32 func_001B4B38(void)
{
    return 0.0f;
}

AnimCursor* func_001B4B48(CursorAnimator* self, const AnimRecord* key)
{
    if (key->key == self->recordKey) {
        return &self->cursor;
    }
    return 0;
}


void func_00182C58(void* self);
void func_001B61F0(void* self);
void func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);

void func_001B61A8(StateGraph* self)
{
    func_00182C58(self);
    if (self->armed != 0) {
        func_001DBCC8(self->world, (void*)func_001B61F0, self, 0, 0);
    }
}

struct Pair_1B63C0 {
    s32 key_00;
    s32 value_04;
};

s32 func_001B63C0(StateGraph* self, s32 key)
{
    s32 count = self->f34;
    if (count > 0) {
        Pair_1B63C0* p = (Pair_1B63C0*)self->f38;
        s32 i = 0;
        do {
            if (p->key_00 == key) {
                return i;
            }
            i++;
            p++;
        } while (i < count);
    }
    return -1;
}


void func_001B4B68(FrameRunAnimator* p, AnimatorParams* s)
{
    func_001B4AA0(p, s);
    p->durMin = s->f4;
    p->durMax = s->f8;
    p->waitMin = s->fC;
    p->waitMax = s->f10;
    p->pos = (f32)s->u14;
}

f32 func_001EAAE0(f32 a, f32 b);
f32 func_001EAFE0(f32 a, f32 b);

void func_001B4C30(FrameRunAnimator* p, f32 dt)
{
    if (p->cursor.record == 0) {
        return;
    }
    if (p->cursor.record->count < 2) {
        return;
    }
    if (p->wait > 0.0f) {
        p->wait = p->wait - dt;
        return;
    }
    p->pos = p->pos + p->rate * dt;
    if ((f32)p->cursor.record->count <= p->pos) {
        f32 a = func_001EAAE0(p->durMin, p->durMax);
        p->rate = (f32)p->cursor.record->count / a;
        f32 b = func_001EAAE0(p->waitMin, p->waitMax);
        p->wait0 = b;
        p->wait = b;
    }
    f32 t = func_001EAFE0(p->pos, (f32)p->cursor.record->count);
    p->pos = t;
    func_001B46E0(&p->cursor, (s32)t);
}

s32 func_001B63C0(void* self, s32 key);

s32 func_001B63F8(void* self, s32 key)
{
    s32 r = func_001B63C0(self, key);
    return r < 0 ? 0 : r;
}

struct Reg_001B6438 { u8 pad0[0x1B88]; };
struct Owner_001B6438 { u8 pad0[0x14]; Reg_001B6438* reg_14; };
struct Obj_001B6438 {
    u8 pad0[0x18];
    Owner_001B6438* owner_18;
    u8 pad1[0x24 - 0x1C];
    void* handle_24;
    u8 pad2[0x3C - 0x28];
    void* ptr_3C;
};

void func_0012E760(void* p);
void func_001DBC18(void* a, void* b);
void func_00152600(void* a, void* b);
void func_001B5F28(void* a, void* b);
void func_001837E0(void* a, s32 b, s32 c, s32 d);

void func_001B6438(Obj_001B6438* self)
{
    Owner_001B6438* owner = self->owner_18;
    if (self->handle_24 != 0) {
        func_0012E760(self->handle_24);
        self->handle_24 = 0;
    }
    func_001DBC18(self->owner_18->reg_14, self->ptr_3C);
    self->ptr_3C = 0;
    func_00152600((u8*)self->owner_18 + 0x48, self);
    func_00152600((u8*)self->owner_18->reg_14 + 0x1B94, self);
    func_001B5F28((u8*)self->owner_18->reg_14 + 0x1B88, self);
    func_001837E0(owner, 0x12, 0, 0);
}

struct Vec3_1B5588 { f32 x; f32 y; f32 z; };

void func_001B5588(Vec3_1B5588* dst, Vec3_1B5588* src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

void func_00152438(void* self, s32 value);
void func_00123ED0(void* self);
void func_00160E80(Mesh03* mesh);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);
s32 func_0011A498(void* a, s32 b, s32 c, ScriptValue* d);
void func_001BB4A0(void* self);

void func_001B7968(Collider* self)
{
    ScriptValue local;
    s32 s0;
    func_0011B008(&local);
    func_00152438(&self->parts, 0x2E4);
    func_00123ED0(self);
    func_00160E80(&self->mesh);
    self->meshCopy = self->mesh;
    if (self->parent != 0) {
        func_001B9AE0(self, 3, 0, 3, 0);
    }
    self->f4BC = -1;
    self->index = -1;
    if (self->f2C != 0) {
        s0 = func_0011A498(self->f2C, 6, 1, &local);
        s0 |= func_0011A498(self->f2C, 7, 1, &local);
        if (s0 != 0) {
            self->flags538 |= (u64)0x8000 << 48;
        }
    }
    self->gravity = self->world->gravity;
    func_001BB4A0(self);
    func_0011B060(&local, 2);
}

struct __attribute__((aligned(16))) Quad_001B4580 { f32 v[4]; };

void func_001B4330(Quad_001B4580* p);

void func_001B4580(Quad_001B4580* src, f32* dst)
{
    Quad_001B4580 tmp = *src;
    tmp.v[1] = tmp.v[1] * 0.003921569f;
    tmp.v[2] = tmp.v[2] * 0.003921569f;
    func_001B4330(&tmp);
    dst[0] = dst[0] * 255.0f;
    dst[1] = dst[1] * 255.0f;
    dst[2] = dst[2] * 255.0f;
}

struct Slot_1B70B0 { s32 value; s32 pad4; };
struct Self_1B70B0 { u8 pad0[0xC38]; Slot_1B70B0 slots[1]; };

s32 func_001CA600(s32 index);

void func_001B70B0(Self_1B70B0* self, s32 index, s32 value)
{
    (void)func_001CA600(index);
    self->slots[index].value = value;
}


void func_001B7100(C09* self, s32 value)
{
    s32 n = self->fCD4;
    if ((u32)n < 4) {
        self->fCD8[n].id = value;
        n++;
        self->fCD4 = n;
    }
}

f32 func_001B5308(ScrollAnimator* p) { f32 result=0.0f; if (p->velU != 0.0f) result=(p->cursor.u/p->wrapU)*0.5f; else result=0.5f; if (p->velV != 0.0f) result += (p->cursor.v/p->wrapV)*0.5f; else result += 0.5f; return result; }

void func_001B5568(TriangleAnimator* self, void** out) { out[0] = &self->out44; out[1] = &self->out4C; out[2] = &self->out48; }

void func_00124A48(void* self);

void func_001B5CD8(C54* self)
{
    func_00124A48(self);
    self->flags = (self->flags & 0xFFFFFCFFFFFFFFFFULL) | 0x10000000000ULL;
}

struct Walk_1B5DD0 { s32 a; void* b; s32 c; };

void* func_0018D500(s32 size);
void func_001B5D80(void* s, s32 v, s32 n);

void func_001B5DD0(Walk_1B5DD0* s, s32 size, s32 count)
{
    s32 stride = (size + 7) & ~7;
    s->b = func_0018D500(stride * count);
    func_001B5D80(s, stride, count);
}

struct Walk_1B5E30 { s32 a; void* b; s32 c; };

void* func_0018D500(s32 size);
void func_001B5D80(void* s, s32 v, s32 n);

void func_001B5E30(Walk_1B5E30* s, s32 size, s32 count)
{
    s32 addr = (s32)func_0018D500(size * count + 0x30);
    s->b = (void*)((addr + 0x3F) & -0x40);
    func_001B5D80(s, size, count);
}

struct Node_1B6388 {
    u8 pad0[0x8];
    Node_1B6388* next;
    u8 pad1[0x10];
    s32 key;
};

struct Owner_1B6388 {
    u8 pad0[0x48];
    Node_1B6388* head;
};

void* func_001B6388(Owner_1B6388* self, s32 key)
{
    ListFrame frame;
    Node_1B6388* node = self->head;
    if (node != 0) {
        do {
            if (node->key == key) {
                return node;
            }
            node = node->next;
        } while (node != 0);
    }
    return 0;
}

struct Holder_1B6DF8 {
    u8 pad0[0x14];
    void* ptr;
};

struct Self_1B6DF8 {
    u8 pad0[0x18];
    Holder_1B6DF8* holder;
};

void func_001831E8(void* a, void* b, s32 c, void* d);

void func_001B6DF8(Self_1B6DF8* self, PlacedObject** p)
{
    func_001831E8(self->holder->ptr, (u8*)self + 0x3C, (s32)(*p)->link40.prev, p);
}

struct Pair_1B7128 {
    s32 key;
    s32 value;
};

void func_001C72A0(void* self);
void func_001B6F50(void* self);
s32 func_0015A448(void* host, s32 id, void* ctx);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);

void func_001B7128(C09* self)
{
    func_001C72A0(self);
    func_001B6F50(self);
    if (self->fC28 != -1) {
        self->fC2C = func_0015A448(self->world, self->fC28, self);
    }
    if (self->fCD4 > 0) {
        s32 i = 0;
        Pair_1B7128* p = (Pair_1B7128*)self->fCD8;
        do {
            p->value = func_0015A418(self->world, 0x104, p->key, self);
            p++;
            i++;
        } while (i < self->fCD4);
    }
}

void func_001C7CB8(void* self);
void func_001B7638(void* self);

void func_001B7608(C09* self)
{
    func_001C7CB8(self);
    func_001B7638(self);
}

typedef void (*VFn_1B7790)(void* self);
struct Sub_1B7790 { VFn_1B7790* vtbl; };
void func_001C91C8(void* self);
void func_001BF048(void* p);

void func_001B7790(C09* self)
{
    func_001C91C8(self);
    switch (self->f724) {
    case 6:
        self->fCC4 = 0;
        break;
    case 0xB: {
        Sub_1B7790* p = ((Sub_1B7790*)self->fC14);
        if (p != 0) {
            p->vtbl[7](p);
        }
        func_001BF048(self->fCC0);
        self->fCC0 = 0;
        break;
    }
    }
    self->fC30 = *(s32*)((u8*)self + (self->f724 << 3) + 0xC3C);
}

typedef s32 (*VFn_1B7818)(void* self);

s32 func_001CA468(void* self);

s32 func_001B7818(C09* self)
{
    if (func_001CA468(self) == 0) {
        return 0;
    }
    return ((VFn_1B7818*)self->desc)[91](self);
}

void func_001C9DE0(void* self, s32 code, void* req);

void func_001B78C0(C09* self, s32 code, void* req)
{
    func_001C9DE0(self, code, req);
    if (code == 7) {
        if (req == self->f7E0) {
            self->fCC4++;
        }
    }
}

f32 func_001EAAE0(f32 a, f32 b);

void func_001B4DA8(FramePingPongAnimator* p)
{
    func_001B4AD0(p);
    if (p->cursor.record != 0) {
        f32 a = func_001EAAE0(p->durMin, p->durMax);
        p->rate = (f32)(p->cursor.record->count * 2) / a;
        f32 b = func_001EAAE0(p->waitMin, p->waitMax);
        p->wait0 = b;
        p->wait = b;
    }
}

f32 func_001EAAE0(f32 a, f32 b);

void func_001B4E18(FramePingPongAnimator* p, f32 dt)
{
    AnimRecord* d = p->cursor.record;
    if (d == 0) return;
    if (d->count < 2) return;
    if (0.0f < p->wait) {
        p->wait = p->wait - dt;
        return;
    }
    f32 prod = p->rate * dt;
    f32 sum = p->pos + prod;
    p->pos = sum;
    if ((f32)d->count <= sum) {
        p->pos = sum - prod;
        p->rate = -p->rate;
    }
    if (p->pos < 0.0f) {
        p->pos = 0.0f;
        f32 a = func_001EAAE0(p->durMin, p->durMax);
        p->rate = (f32)(p->cursor.record->count * 2) / a;
        f32 b = func_001EAAE0(p->waitMin, p->waitMax);
        p->wait0 = b;
        p->wait = b;
    }
    func_001B46E0(&p->cursor, (s32)p->pos);
}

extern f32 D_0026185C;
f32 func_001EA408(f32 a);
void func_001EAD88(f32 angle, f32* a, f32* b);

void func_001B5400(CircleAnimator* self)
{
    if (self->cursor.record != 0) {
        f32 t[2];
        f32 ang = func_001EA408(D_0026185C * self->omega);
        func_001EAD88(ang, &t[0], &t[1]);
        t[0] = t[0] * self->radius + self->centerU;
        t[1] = t[1] * self->radius + self->centerV;
        func_001B4750(&self->cursor, t[0], t[1]);
    }
}

extern f32 D_0026185C;
f32 func_001EAFE0(f32 x, f32 y);

f32 func_001B5488(CircleAnimator* p)
{
    f32 a = func_001EAFE0(D_0026185C * p->omega, 6.2831855f);
    return a * 0.15915494f;
}


void func_001B54D0(TriangleAnimator* self, AnimatorParams* src)
{
    func_001B4AA0(self, src);
    s32 fl = self->cursor.flags;
    self->u0 = src->f4;
    self->v0 = src->f8;
    self->du1 = src->fC - src->f4;
    self->du2 = src->f10 - src->f4;
    self->dv1 = src->f14 - src->f8;
    f32 d = src->f18 - src->f8;
    self->cursor.flags = (fl & -2) | 2;
    self->dv2 = d;
}

void func_00124FC0(void* self);


void func_001B5D28(C54* self)
{
    func_00124FC0(self);
    Vec02* src = (Vec02*)D_00261990->f40;
    Vec02 q = *src;
    if (self->f2D0 == 0) {
        q.z = self->v140.z;
    }
    self->desc02()->m1D(self, &q);
}

void func_001C6F48(void* self);

struct Ent_1B6EC8 { s32 v; s32 pad; };
void func_001B6EC8(C09* self)
{
    func_001C6F48(self);
    self->fC20 = 2000.0f;
    self->fC18 = 300.0f;
    self->fC1C = 300.0f;
    self->fC24 = 300.0f;
    self->fC28 = -1;
    self->fC2C = 0;
    s32 i = 16;
    Ent_1B6EC8* e = (Ent_1B6EC8*)((u8*)self + 0xCB8);
    do {
        e->v = -1;
        i--;
        e--;
    } while (i >= 0);
    self->fC10 = -1;
}


void func_001B5398(CircleAnimator* p, AnimatorParams* s)
{
    func_001B4AA0(p, s);
    p->omega = s->f4; p->radius = s->f8; p->centerU = s->fC; p->centerV = s->f10; p->cursor.flags = (p->cursor.flags & ~1) | 2;
}

extern f32 D_0026185C;

s32 func_001B7860(C09* self)
{
    s32 r;
    if (self->f724 == 11) {
        goto ret1;
    }
    if (self->f724 != 6) {
        goto ret0;
    }
    if (self->fCC4 <= 0) {
        goto ret0;
    }
    if (5.0f < D_0026185C - self->f728) {
        r = 2;
        return r;
    }
ret1:
    return 1;
ret0:
    r = 0;
    return r;
}

extern s32 D_002744F8;
extern AnimRecord* D_002744FC;

AnimRecord* func_001B4688(s32 key)
{
    if (key == -1) {
        return 0;
    }
    s32 i = 0;
    if (i < D_002744F8) {
        AnimRecord* p = D_002744FC;
        do {
            if (p->key == key) {
                return p;
            }
            i++;
            p++;
        } while (i < D_002744F8);
    }
    return 0;
}

struct Item_1B61F0 {
    u8 pad_00[0x40];
    s32 value_40;
};

struct Slot_1B61F0 {
    Item_1B61F0* item_00;
    s32 pad_04[4];
};

struct Bank_1B61F0 {
    u8 pad_00[0x14];
    void* owner_14;
    u8 pad_18[0x24];
    s32 count_3C;
    Slot_1B61F0* slots_40;
};

s32 func_0015A448(void* owner, s32 value, void* bank);
void func_001B6290(void* bank, s32 r, s32 minus_one, s32 zero);

void func_001B61F0(Bank_1B61F0* self)
{
    s32 i = 0;
    s32 n = self->count_3C;
    Item_1B61F0* e = 0;
    if (n > 0) {
        Slot_1B61F0* p = self->slots_40;
        do {
            e = p->item_00;
            i++;
            p++;
        } while (i < n && e == 0);
    }
    s32 r;
    if (self->count_3C > 0 && e != 0 && e->value_40 != -1) {
        r = func_0015A448(self->owner_14, e->value_40, self);
    } else {
        r = 0;
    }
    func_001B6290(self, r, -1, 0);
}

void func_001B5200(ScrollAnimator* p, AnimatorParams* s)
{
    func_001B4AA0(p, s);
    p->velU = s->f4;
    p->velV = s->f8;
    p->wrapU = s->fC;
    p->wrapV = s->f10;
    p->mulV = 1.0f;
    p->mulU = 1.0f;
    p->cursor.flags = (p->cursor.flags & ~1) | 2;
}

struct Sjis_274588 { u16 sjis; u16 ascii; };
extern Sjis_274588 D_00274588[];
extern Sjis_274588 D_00274610[];

u16 func_001B5B58(u8 ch)
{
    s32 base = 0;
    s32 idx;
    if (ch >= 0x20 && ch < 0x30) {
        base = 1;
    } else if (ch >= 0x30 && ch < 0x3A) {
        idx = 0;
    } else if (ch >= 0x3A && ch < 0x41) {
        base = 0xB;
    } else if (ch >= 0x41 && ch < 0x5B) {
        idx = 1;
    } else if (ch >= 0x5B && ch < 0x61) {
        base = 0x25;
    } else if (ch >= 0x61 && ch < 0x7B) {
        idx = 2;
    } else if (ch >= 0x7B && ch < 0x7F) {
        base = 0x3F;
    } else {
        return 0;
    }
    if (base == 0) {
        return D_00274610[idx].sjis + ch - D_00274610[idx].ascii;
    }
    Sjis_274588* e = &D_00274588[ch - (base + 0x1F)];
    return e->sjis;
}
s32 func_001E2100(void* p);

void func_001B5C40(u8* src, u16* dst)
{
    s32 n = func_001E2100(src);
    s32 i;
    for (i = 0; i < n; i++) {
        u32 r = func_001B5B58(src[i]);
        u32 lo = (r & 0xFF) << 8;
        u32 hi = (r >> 8) & 0xFF;
        dst[i] = (u16)(hi | lo);
    }
    dst[i] = 0;
}

struct Inner_1B6CF0 { u8 pad[0x34]; f32 f34; };
struct Item_1B6CF0 {
    u8 pad[0x8];
    Inner_1B6CF0* inner;
    u8 pad2[0x14 - 0x0C];
    f32 f14;
};
struct Node_1B6CF0 { u8 pad[0x24]; s32 f24; };

f32 func_001B6C68(Node_1B6CF0* self);
void func_001B66A0(Node_1B6CF0* self);
void func_0012F0A0(void* a, f32 b, f32 c, s32 d);

void func_001B6CF0(Node_1B6CF0* self, f32 t)
{
    f32 rem = t;
    Item_1B6CF0* item = (Item_1B6CF0*)self->f24;
    while (item) {
        f32 diff = item->inner->f34 - item->f14;
        if (rem < diff) {
            func_0012F0A0(item, rem, 1.0f, 1);
            break;
        }
        rem = rem - diff;
        (void)func_001B6C68(self);
        func_001B66A0(self);
        item = (Item_1B6CF0*)self->f24;
    }
}

f32 func_001EAAE0(f32 a, f32 b);

void func_001B5060(AngleFrameAnimator* self, AnimatorParams* key)
{
    func_001B4AA0(self, key);
    self->phase = key->f4;
    f32 d = (f32)(u32)key->i8;
    f32 q = 6.2831855f / d;
    self->sector = q;
    if (self->phase == 3.4028234663852886e+38f) {
        self->phase = func_001EAAE0(0.0f, q);
    }
}

struct Entry_001B6568 {
    s32 value;
    s32 extra;
};
struct Sub_001B6568 {
    u8 pad0[0x38];
    Entry_001B6568* table;
};
void func_001B6568(StateWalker* a0, s32* out) {
    s32 idx = a0->index;
    s32 v;
    if (idx >= 0) {
        v = ((Sub_001B6568*)a0->owner)->table[idx].value;
    } else {
        v = -1;
    }
    *out = v;
}

struct Entry_001B6598 {
    s32 value;
    s32 extra;
};
struct Sub_001B6598 {
    u8 pad0[0x38];
    Entry_001B6598* table;
};
struct Ctx_001B6598 {
    u8 pad0[0x18];
    Sub_001B6598* sub;
    u8 pad1[0x28 - 0x1C];
    s32 index;
};

void func_001B6598(Ctx_001B6598* a0, s32* out) {
    s32 idx = a0->index;
    s32 v;
    if (idx >= 0) {
        v = a0->sub->table[idx].value;
    } else {
        v = -1;
    }
    *out = v;
}

s32 func_001B63F8(void* self, s32 key);
void func_001B6E28(StateWalker* self, s32 a, s32 b);
void func_001B66A0(StateWalker* self);

void func_001B6628(StateWalker* self, s32 key)
{
    s32 s1 = func_001B63F8(self->owner, key);
    if (self->f28 == s1) {
        s32 v = self->index;
        if (v == s1 || v == -1) {
            return;
        }
    }
    func_001B6E28(self, self->f28, s1);
    self->index = s1;
    self->f28 = s1;
    self->f2C = -1;
    func_001B66A0(self);
}

struct Flags_1B64D8 { u8 pad0[0xC]; s32 flags; };
struct Node_1B64D8 {
    u8 pad0[0x18];
    void* f18;
    u8 pad1[0x24 - 0x1C];
    void* f24;
    u8 pad2[0x30 - 0x28];
    s32 f30;
    Flags_1B64D8* f34;
};

s32 func_001B63F8(StateGraph* self, s32 key);
void func_001B6C68(Node_1B64D8* self);
void func_0012E760(AnimationPlayer* obj);
void func_001B66A0(Node_1B64D8* self);

void func_001B64D8(Node_1B64D8* self, s32 key)
{
    s32 v;
    if (key != -1) {
        v = func_001B63F8((StateGraph*)self->f18, key);
    } else {
        v = -1;
    }
    if (v != self->f30) {
        self->f30 = v;
        Flags_1B64D8* p = self->f34;
        if (p != 0 && (p->flags & 2)) {
            func_001B6C68(self);
            func_0012E760((AnimationPlayer*)self->f24);
            self->f24 = 0;
        }
        if (self->f24 == 0) {
            func_001B66A0(self);
        }
    }
}

struct Entry_2198E8 { const u8* f0; s32 f4; };
extern const Entry_2198E8 D_002198E8;
extern const u8 D_00217410[];

void* func_001B5EE0(Pool6C* pool);
void func_00152470(List01* list, StateWalker* item);
s32 func_001B63F8(StateGraph* self, s32 key);
void func_001B6E28(StateWalker* self, s32 a, s32 b);
void func_001B66A0(StateWalker* self);
void func_001837E0(StateGraph* self, s32 a, s32 b, void* c);

StateWalker* func_001B6290(StateGraph* self, s32 a1, s32 a2, s32 a3)
{
    StateWalker* obj = (StateWalker*)func_001B5EE0(&self->world->pool1B88);
    obj->f1C = a1;
    obj->vt = (void*)&D_002198E8;
    obj->f20 = a3;
    obj->f38 = 1.0f;
    obj->owner = self;
    obj->f2C = -1;
    func_00152470(&self->world->list1B94, obj);

    func_00152470((List01*)((u8*)self + 0x48), obj);
    if (a2 != -1) {
        s32 v = func_001B63F8(self, a2);
        obj->f28 = v;
        obj->index = v;
        func_001B6E28(obj, -1, v);
    }
    func_001B66A0(obj);
    StateWalker** pp = &obj;
    func_001837E0(self, 0x11, 1, (void*)&pp);
    return obj;
}

s32 func_001B4920(s32 k)
{
    switch (k) {
    case 1:
    case 2:
        return 0x4C;
    case 3:
    case 4:
        return 0x38;
    case 5:
        return 0x78;
    case 6:
        return 0x44;
    case 7:
        return 0x3C;
    case 8:
        return 0x50;
    }
    return 0;
}

// An entry of a table of functions defined at the end of this file.
typedef void (*Fn_Table)();
extern const Fn_Table D_0021E358[];
extern const Fn_Table D_0021E378[];
extern const Fn_Table D_0021E398[];
extern const Fn_Table D_0021E3B8[];
extern u8 D_0021E438[];
extern const Fn_Table D_0021E3D8[];
extern const Fn_Table D_0021E3F8[];
extern const Fn_Table D_0021E418[];

void* func_001B4980(s32 n)
{
    switch (n) {
    case 1: return ((u8*)D_0021E358);
    case 2: return ((u8*)D_0021E378);
    case 3: return ((u8*)D_0021E398);
    case 4: return ((u8*)D_0021E3B8);
    case 5: return D_0021E438;
    case 6: return ((u8*)D_0021E3D8);
    case 7: return ((u8*)D_0021E3F8);
    case 8: return ((u8*)D_0021E418);
    }
    return 0;
}

struct Hdr_1B6F50;
struct Elem_1B6F50;
struct Sub_1B6F50 { u8 p0[0x11]; u8 f11; u8 p1[0x0A]; s32 f1C; u8 p2[0x60]; s32 f80; s32 f84; };
typedef void (*VFn_1B6F50)(void* self);
struct Elem_1B6F50 { VFn_1B6F50* vtbl; };
struct Ent_1B6F50 { s32 key; void* val; };
extern u8 D_0021A790[];
void* func_0015A448(Hdr_1B6F50* obj, s32 id, C09* flags);
s32 func_0015A4F0(Hdr_1B6F50* a0, s32 a1, s32 a2, C09* a3, s32 a4, void* a5);
s32 func_001833F0(Elem_1B6F50* a, s32 b);
void func_0018D608(void);
void func_0018D6F0(void);
void* func_0018D658(u32 bytes);
void* func_00121228(Hdr_1B6F50* root, s32 value, void* table);
void func_001299E0(Hdr_1B6F50* self, void* src);

void func_001B6F50(C09* self)
{
    s32 best = -1;
    s32 j = 16;
    Ent_1B6F50* e = (Ent_1B6F50*)self->fC38;
    do {
        s32 key = e->key;
        if (key == best) {
            e->val = 0;
        } else {
            e->val = func_0015A448((Hdr_1B6F50*)self->world, key, self);
        }
        e++;
        j--;
    } while (j >= 0);

    func_0018D608();
    best = 0;
    s32 count = func_0015A4F0((Hdr_1B6F50*)self->world, 0x201, 0x60, self, 0, 0);
    Elem_1B6F50** list = (Elem_1B6F50**)func_0018D658(count << 2);
    count = func_0015A4F0((Hdr_1B6F50*)self->world, 0x201, 0x60, self, count, list);
    if (count > 0) {
        do {
            if (func_001833F0(*list, self->fC10) != 0) {
                best = (s32)*list;
            } else {
                (*list)->vtbl[7](*list);
            }
            list++;
            count--;
        } while (count != 0);
    }
    self->fC14 = (void*)best;
    func_0018D6F0();
    if (self->fC14 != 0) {
        self->fC34 = func_00121228((Hdr_1B6F50*)self->world, (s32)self->fC14, D_0021A790);
        ((Sub_1B6F50*)self->fC34)->f11 = 2;
        ((Sub_1B6F50*)self->fC34)->f1C = 1;
        ((Sub_1B6F50*)self->fC34)->f84 = ((Sub_1B6F50*)self->fC34)->f80 = 0;
        func_001299E0((Hdr_1B6F50*)self->fC14, self->fC34);
        self->fBF0 = (s32)self->fC14;
    }
}

extern f32 D_002746A0[8];

struct Quad_1B7638 {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} __attribute__((aligned(16)));

struct Sub_1B7638 {
    u8 pad0[0x2F0];
    f32 f2F0;
};

struct Target_1B7638 {
    u8 pad0[0x24];
    void *field24;
    u8 pad1[0x30 - 0x28];
    struct Quad_1B7638 quad30;
};


s32 func_001C96B8(C09 *self);
s32 func_001CB578(C09 *self);

void func_001B7638(C09 *self) {
    struct Target_1B7638 *t;
    s32 r;
    s32 res;
    f32 f;

    if (self->fC14 == 0) {
        return;
    }
    t = (struct Target_1B7638 *)self->fC34;
    r = func_001C96B8(self);
    switch (r) {
    case 0:
    case 1:
        if ((void *)self->fC30 != 0) {
            t->field24 = (void *)self->fC30;
            t->quad30 = *(struct Quad_1B7638 *)&D_00248D30;
        } else {
            t->field24 = self;
            t->quad30 = *(struct Quad_1B7638 *)D_002746A0;
        }
        f = 1.3f;
        if (r == 0) {
            f = 1.0f;
        }
        break;
    case 2:
        if ((void *)self->fC30 != 0) {
            t->field24 = (void *)self->fC30;
            t->quad30 = *(struct Quad_1B7638 *)&D_00248D30;
        } else if (func_001CB578(self) != 0) {
            t->field24 = self;
            t->quad30 = *(struct Quad_1B7638 *)D_002746A0;
        } else {
            res = (s32)self->desc08()->m62(self);
            if (res != 0) {
                t->field24 = (void *)res;
                t->quad30 = *(struct Quad_1B7638 *)&D_00248D30;
            } else {
                t->field24 = self;
                t->quad30 = *(struct Quad_1B7638 *)D_002746A0;
            }
        }
        f = 1.3f;
        break;
    case 3:
        t->field24 = self;
        t->quad30 = *(struct Quad_1B7638 *)D_002746A0;
        f = 0.1f;
        break;
    }
    ((struct Sub_1B7638 *)self->fC14)->f2F0 = f;
}

struct Lo_1B4FC0 { s32 v; };
s32 func_001EAA70(Lo_1B4FC0 lo, s32 hi);
f32 func_001EAAE0(f32 a, f32 b);

void func_001B4FC0(RandomJumpAnimator* self, f32 x)
{
    AnimRecord* p = self->cursor.record;
    if (p == 0)
        return;
    s32 count = p->count;
    if (count < 2)
        return;
    if (0.0f < self->wait) {
        self->wait = self->wait - x;
        return;
    }
    Lo_1B4FC0 lo;
    lo.v = 1;
    s32 v = func_001EAA70(lo, count - 1);
    s32 rem = (self->cursor.frame + v) % self->cursor.record->count;
    func_001B46E0(&self->cursor, rem);
    self->wait = func_001EAAE0(self->waitMin, self->waitMax);
}

// Tables of functions this file's code reads: a class's methods, or a dispatch table by kind.
void func_001B55C0();
extern const Fn_Table D_0021E358[8] = { (Fn_Table)func_001B4B68, (Fn_Table)func_001B4BC8, (Fn_Table)func_001B4C30, (Fn_Table)func_001B4D18, 0, (Fn_Table)func_001B4B48, 0, 0 };
extern const Fn_Table D_0021E378[8] = { (Fn_Table)func_001B4D48, (Fn_Table)func_001B4DA8, (Fn_Table)func_001B4E18, (Fn_Table)func_001B4F18, 0, (Fn_Table)func_001B4B48, 0, 0 };
extern const Fn_Table D_0021E398[8] = { (Fn_Table)func_001B4F80, (Fn_Table)func_001B4AD0, (Fn_Table)func_001B4FC0, (Fn_Table)func_001B4B38, 0, (Fn_Table)func_001B4B48, 0, 0 };
extern const Fn_Table D_0021E3B8[8] = { (Fn_Table)func_001B5060, (Fn_Table)func_001B5108, 0, (Fn_Table)func_001B4B38, (Fn_Table)func_001B5160, (Fn_Table)func_001B4B48, 0, 0 };
extern const Fn_Table D_0021E3D8[8] = { (Fn_Table)func_001B5200, (Fn_Table)func_001B4AD0, (Fn_Table)func_001B5278, (Fn_Table)func_001B5308, 0, (Fn_Table)func_001B4B48, 0, 0 };
extern const Fn_Table D_0021E3F8[8] = { (Fn_Table)func_001B5398, (Fn_Table)func_001B4AD0, (Fn_Table)func_001B5400, (Fn_Table)func_001B5488, 0, (Fn_Table)func_001B4B48, 0, 0 };
extern const Fn_Table D_0021E418[8] = { (Fn_Table)func_001B54D0, (Fn_Table)func_001B4AD0, 0, (Fn_Table)func_001B4B38, (Fn_Table)func_001B55C0, (Fn_Table)func_001B4B48, (Fn_Table)func_001B5568, 0 };

struct Track_1B66A0
{
    u8 pad00[0x34];
    f32 f34;
};
struct Edge_1B66A0
{
    Track_1B66A0* track;
    s32 a;
    s32 b;
    u32 flags;
    f32 weight;
};
struct Link_1B66A0
{
    s32 f0;
    s32 next;
};
struct Graph_1B66A0
{
    u8 pad00[0x34];
    s32 nodeCount;
    Link_1B66A0* links;
    s32 edgeCount;
    Edge_1B66A0* edges;
};
struct Mover_1B66A0
{
    u8 pad00[0x18];
    Graph_1B66A0* graph;
    s32 f1C;
    s32 f20;
    void* f24;
    s32 cur;
    s32 f2C;
    s32 target;
    Edge_1B66A0* edge;
    f32 f38;
};

void func_0018D608(void);
void* func_0018D658(s32 size);
void func_0018D6F0(void);
f32 func_001EAAE0(f32 a, f32 b);
void func_001B6E28(Mover_1B66A0* self, s32 a, s32 b);
void func_0012C7B0(Track_1B66A0* track, s32 a1, s32 a2, void** out, f32 fa, f32 fb);
void func_0012F7E0(void* obj, void (*fn)(Mover_1B66A0*, s32, s32), Mover_1B66A0* self);
void func_001B6CA8(Mover_1B66A0* self, s32 a, s32 b);
void func_0012F190(void* obj, s32 zero);
void func_0012E760(void* obj);
void func_001B6D78(Mover_1B66A0* self, s32 a, Mover_1B66A0* b);

void func_001B66A0(Mover_1B66A0* self)
{
    Graph_1B66A0* g = self->graph;
    func_0018D608();
    if (self->target == self->cur)
    {
        self->target = g->links[self->target].next;
    }
    s32 target = self->target;
    if (target == -1)
    {
        goto fail;
    }
    {
        s32 cur = self->cur;
        s32* dist = (s32*)func_0018D658(g->nodeCount * 4);
        s32 i;
        s32 j;
        Edge_1B66A0* p;
        for (i = 0; i < g->nodeCount; i++)
        {
            dist[i] = (i == cur) ? 0 : -1;
        }
        s32 level = 1;
        for (;;)
        {
            s32 changed = 0;
            for (j = 0; j < g->edgeCount; j++)
            {
                p = &g->edges[j];
                if (dist[p->a] == level - 1 && dist[p->b] < 0)
                {
                    dist[p->b] = level;
                    changed = 1;
                }
                if ((p->flags & 1) && dist[p->b] == level - 1 && dist[p->a] < 0)
                {
                    dist[p->a] = level;
                    changed = 1;
                }
            }
            if (level == 1)
            {
                for (j = 0; j < g->edgeCount; j++)
                {
                    p = &g->edges[j];
                    if (p->a == cur && p->b == cur)
                    {
                        dist[cur] = 1;
                        changed = 1;
                    }
                }
            }
            if (!changed)
            {
                break;
            }
            if (dist[target] > 0)
            {
                goto found;
            }
            level++;
        }
        if (dist[target] < 0)
        {
            self->target = -1;
            goto fail;
        }
    found:
        for (i = 0; i < g->nodeCount; i++)
        {
            if (i != target && dist[i] == level)
            {
                dist[i] = -1;
            }
        }
        for (s32 m = level; m > 1; m--)
        {
            level++;
            for (j = 0; j < g->edgeCount; j++)
            {
                p = &g->edges[j];
                if (dist[p->b] == level - 1 && dist[p->a] == m - 1)
                {
                    dist[p->a] = level;
                }
                if ((p->flags & 1) && dist[p->a] == level - 1 && dist[p->b] == m - 1)
                {
                    dist[p->b] = level;
                }
            }
        }
        Edge_1B66A0** cand = (Edge_1B66A0**)func_0018D658(g->edgeCount * 4);
        Edge_1B66A0* e;
        for (;;)
        {
            s32 n = 0;
            for (j = 0; j < g->edgeCount; j++)
            {
                Edge_1B66A0* c = &g->edges[j];
                if (dist[c->b] == level && c->a == cur)
                {
                    cand[n++] = c;
                }
                else if ((c->flags & 1) && dist[c->a] == level && c->b == cur)
                {
                    cand[n++] = c;
                }
            }
            f32 sum = 0.0f;
            for (i = 0; i < n; i++)
            {
                sum += cand[i]->weight;
            }
            f32 r = func_001EAAE0(0.0f, sum);
            for (i = 0; i < n; i++)
            {
                r -= cand[i]->weight;
                if (r < 0.0f)
                {
                    break;
                }
            }
            e = cand[i];
            if (e->track != 0)
            {
                break;
            }
            if (e->a == cur)
            {
                func_001B6E28(self, self->cur, e->b);
                self->cur = cur = e->b;
            }
            else
            {
                func_001B6E28(self, self->cur, e->a);
                self->cur = cur = e->a;
            }
            if (cur == target)
            {
                goto arrived;
            }
            level--;
        }
        {
            f32 fa;
            f32 fb;
            if (e->a == cur)
            {
                self->f2C = e->b;
                fa = 0.0f;
                fb = self->f38;
            }
            else
            {
                self->f2C = e->a;
                fb = -self->f38;
                fa = e->track->f34;
            }
            void* old = self->f24;
            self->edge = e;
            self->f24 = 0;
            if (e->track != 0)
            {
                func_0012C7B0(e->track, self->f1C, self->f20, &self->f24, fa, fb);
                if (self->f24 != 0)
                {
                    func_0012F7E0(self->f24, func_001B6CA8, self);
                }
            }
            if (old != 0)
            {
                func_0012F190(old, 0);
                func_0012E760(old);
            }
            goto done;
        }
    }
arrived:
    func_001B66A0(self);
    func_0018D6F0();
    return;
fail:
    self->edge = 0;
    if (self->f24 != 0)
    {
        func_0012F190(self->f24, 0);
        func_0012E760(self->f24);
        self->f24 = 0;
    }
done:
    func_0018D6F0();
    func_001B6D78(self, 0x14, self);
}

extern const Entry_2198E8 D_002198E8 = { D_00217410, 0x93 };
f32 D_002746A0[8] = { 1000.0f, 0.0f, 0.0f, 0.0f, 2.0f, -2.0f, 0.0f, 0.0f };
