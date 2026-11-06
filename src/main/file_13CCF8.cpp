// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
#include "timed_state_object.h"
#include "trigger_zone.h"
#include "zone_collider.h"
#include "masked_collider.h"
#include "child_group_object.h"
#include "switched_collider.h"
#include "object_message.h"
#include "world.h"
#include "object_event.h"

// The file's .data, in retail's order: two boxes (the corners 0 and the size -1e8 or 1e8) and
// the records that point at them, which func_0013E430 reads, then the disc code's sector check
// state (file_140790 uses it; its own .data must start 8-aligned).
f32 D_00261390[8] = { 0.0f, 0.0f, 0.0f, 0.0f, -100000000.0f, 0.0f, 0.0f, 0.0f };
f32 D_002613B0[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 100000000.0f, 0.0f, 0.0f, 0.0f };
f32* D_002613D0[4] = { D_00261390, 0, 0, 0 };
f32* D_002613E0[3] = { D_002613B0, 0, 0 };
s32 D_002613EC = 0;
void func_001837E0(void* obj, s32 kind, s32 a, s32 b);

extern u8 D_00261420[];
void func_001B7968(void* self);
void* func_00140FF8(void* p);

void func_0013CCF8(MaskedCollider* self)
{
    MaskedCollider* o = self;
    InitCollider(self);
    o->f628 = 0.8f;
    o->f62C = 1.2f;
    o->f68C = 1;
    o->f624 = 1.0f;
    o->f2B4 = 16;
    o->tint[3] = 16;
    o->tint[2] = 16;
    o->tint[1] = 16;
    o->tint[0] = 16;
    o->id688 = (s32)TakeFlagTableIndex(g_flagTable);
    o->f614 = -1;
}

void func_001BAC30(void* self);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_00159478(void* sub, void* self);
void func_00182ED8(s32 a);

void func_0013CD80(MaskedCollider* self)
{
    LoadCollider(self);
    if (self->f614 == -1) {
        FindOrBuildMemberGroup(&self->f618, self);
        return;
    }
    s32 v = FindFirstObjectById(self->world, 0x101, self->f614, self);
    self->f618 = v;
    if (v != 0) {
        func_00182ED8(v);
    }
}

void func_001BA130(MaskedCollider* self, MaskedCollider* other);
void* func_0018D568(s32 size, void* owner);

void func_0013CDE8(MaskedCollider* self, MaskedCollider* other)
{
    s32 saved = self->id688;
    CopyCollider(self, other);
    self->id688 = saved;
    if (other->f6B4)
        self->f6B4 = CopyToFrontMemory(0x24, other->f6B4);
}

// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "timed_state_object.h"
#include "trigger_zone.h"
#include "masked_collider.h"
#include "child_group_object.h"
#include "switched_collider.h"
#include "memory_reader.h"
#include "object_message.h"

void func_001BE4D8(void* p);



typedef void (*Hook_CE40)(void* self);

void func_00124A48(MaskedCollider* self);
void func_0013CE80(MaskedCollider* self);
void* func_001DBCC8(void* target, Hook_CE40 fn, MaskedCollider* ctx, s32 a3, s32 a4);

void func_0013CE40(MaskedCollider* self)
{
    StartPlacedObject(self);
    AppendQueuedCall(self->world, func_0013CE80, self, 0, 0);
}

extern u8 D_00261420[];

struct Frame_13CE80 { s32 list; s32 cursor; s32 link; s32 prev; s32 out; };
s32 func_00141008(Frame_13CE80* t, s32 v);
s32 func_001300E8(MaskedCollider* n, s32 kind);
void func_00199C10(MaskedCollider* n, s32* out);
s32 func_001833F0(MaskedCollider* n, s32 key);

void func_0013CE80(MaskedCollider* self)
{
    Frame_13CE80 fr;
    MaskedCollider* n;
    s32 i;
    Slot20* e;
    if (TestFlagTableBit((Frame_13CE80*)g_flagTable, self->id688)) self->f678 = 1;
    s32 l = (s32)&self->children;
    fr.cursor = l;
    fr.list = l;
    s32 old = *(s32*)&g_activeListFrames;
    s32 link = *(s32*)(l + 8);
    *(s32*)&g_activeListFrames = (s32)&fr;
    fr.prev = old;
    s32 h = (s32)self->children.head;
    fr.link = link;
    fr.cursor = h + link;
    n = (MaskedCollider*)h;
    while (n != 0) {
        if (self->f678) {
            if (!IsObjectOfKind(n, 0x2E)) goto next;
            GetNumberedItemFlag(n, &fr.out);
            if (fr.out) goto next;
        }
        if (IsObjectOfKind(n, 0x75)) goto next;
        if (IsObjectOfKind(n, 0x7A)) goto next;
        if (IsObjectOfKind(n, 0x53)) goto next;
        if (IsObjectOfKind(n, 0x27)) n->slots[1].kind = (s32)self;
        for (i = 0; i < self->count550; i++) {
            e = &self->slots[i];
            if (MatchesObjectId(n, e->key)) {
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
        n = (MaskedCollider*)nx;
    }
    *(s32*)&g_activeListFrames = fr.prev;
}

void func_001B93F8(void* self);

void func_0013D068(MaskedCollider* self)
{
    UpdateCollider(self);
    if (self->f678 != 0) {
        self->f678 = 0;
        self->desc20()->m48(self);
    }
}

ASM_FUNC(func_0013D0B0);

ASM_FUNC(func_0013D278);

extern u8 D_00261420[];

void func_00141040(void* table, s32 v);
void func_001410A0(void* table, s32 v);

void func_0013D820(MaskedCollider* self, s32 v)
{
    self->hold = v;
    if (v != 0) {
        SetFlagTableBit(g_flagTable, self->id688);
    } else {
        ClearFlagTableBit(g_flagTable, self->id688);
    }
}

void func_0013D868(MaskedCollider* q, s32 value)
{
    if ((u32)q->count550 < 16) {
        q->slots[q->count550].key = value;
        q->slots[q->count550].kind = 0;
        q->count550++;
    }
}

void func_0013D8B0(MaskedCollider* q, s32 value)
{
    if ((u32)q->count550 < 16) {
        q->slots[q->count550].key = value;
        q->slots[q->count550].kind = 1;
        q->count550++;
    }
}



void func_0013D900(MaskedCollider* self, s32 value)
{
    if ((u32)self->count550 < 16) {
        self->slots[self->count550].key = value;
        self->slots[self->count550].kind = 2;
        self->count550++;
    }
}

void func_0013D950(MaskedCollider* q, s32 value)
{
    if ((u32)q->count550 < 16) {
        q->slots[q->count550].key = value;
        q->slots[q->count550].kind = 3;
        q->count550++;
    }
}

void func_0013D9A0(MaskedCollider* self, s32 enabled)
{
    if (enabled) {
        self->mask = (self->mask | 1) & ~8;
    } else {
        self->mask &= ~1;
        if (self->mask == 0) self->mask = 8;
    }
}

void func_0013D9E0(MaskedCollider* state, s32* result) {
	*result = state->mask & 1;
}

void func_0013D9F0(MaskedCollider* self, s32 enabled)
{
    if (enabled) {
        self->mask = (self->mask | 4) & ~8;
    } else {
        self->mask &= ~4;
        if (self->mask == 0) self->mask = 8;
    }
}

void func_0013DA30(MaskedCollider* state, s32* result) {
	*result = (state->mask >> 2) & 1;
}

void func_0013DA48(MaskedCollider* obj, s32 value) { if ((u32)obj->count640 < 4) { obj->list644[obj->count640++] = (void*)value; obj->mask |= 2; } }

void func_0013DA80(MaskedCollider* r, s32 value)
{
    s32 n = r->count654;
    if ((u32)n < 4) {
        r->list658[n] = (void*)value;
        r->count654 = n + 1;
        r->mask |= 2;
    }
}

void func_0013DAB8(MaskedCollider* obj, s32 value) { if ((u32)obj->count668 < 3) { obj->list66C[obj->count668++] = (void*)value; obj->mask |= 2; } }

void* func_0013DAF0(MaskedCollider* self)
{
    if (!self->f6B4) InitSoundParams(&self->f6B4);
    return self->f6B4;
}

void* func_001925F0(void);
s32 func_001833F0(void* msg, void* item);
s32 func_001300E8(void* msg, void* item);

s32 func_0013DB28(MaskedCollider* self, C19* msg)
{


    if (self->mask == 0) {
        return 1;
    }
    if (self->mask & 1) {
        if (msg == GetActiveSwitchedCollider()) {
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
        if (MatchesObjectId(msg, self->list644[i]) != 0) {
            return 1;
        }
    }
    for (s32 i = 0; i < self->count654; i++) {
        if (IsObjectOfKind(msg, self->list658[i]) != 0) {
            return 1;
        }
    }
    return 0;
}

extern f32 D_0026185C;
void func_001B93F8(Collider* self);

void func_0013DC38(TimedStateObject* self)
{
    s32 next;

    UpdateCollider(self);
    next = self->state;
    if (next != 0) {
        if (next == 1) {
            if (self->tries >= 2 || self->limit < g_gameTime - self->stamp) {
                next = 2;
            }
        }
    }
    SetTimedState(self, next);
}

void func_00127378(TimedStateObject* self, s32 kind, ObjectMessage* msg);

void func_0013DCA8(TimedStateObject* self, s32 kind, ObjectMessage* msg)
{
    HandlePlacedObjectNotification(self, kind, msg);
    if (kind == 0xF) {
        if ((TimedStateObject*)msg->target == self) {
            SetTimedState(self, 1);
        }
    }
}

s32 func_001300E8(Collider* src, s32 kind);
s32 func_0013DD08(TimedStateObject* node, Collider* src)
{
    s32 r;
    if (src->flags538 & (1ULL << 55)) return 0;
    if (node->acceptAll != 0) return 1;
    Child27* c = node->child;
    if (c == 0 || c->f694 == 0) {
        r = IsObjectOfKind(src, 0x27);
        if (r != 0) return 0;
    }
    return 1;
}

extern f32 D_0026185C;
s32 func_00126D60(f32 value);

void func_0013DD78(TimedStateObject* self, s32 state)
{
    if (state != self->state) {
        *(s32*)((u8*)self + 0x550) = state;
        f32 t = g_gameTime;
        self->stamp = t;
        if (state == 2) {
            (void)func_00126D60(self->param);
        }
    }
}

void func_0013CCF8(MaskedCollider* self);

void func_0013DDB8(C21* self)
{
    InitMaskedCollider(self);
    self->mask = 5;
    self->f698 = -1;
}

void func_0013DDF0(C25* self)
{
    InitMaskedCollider(self);
    self->mask = 1;
    self->scale = 1.0f;
    self->sel6C4 = -1;
    self->sel6C8 = -1;
}

s32 func_0013DB28(MaskedCollider* self, s32 value);
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
    if (IsObjectAccepted(self, value) == 0) return;
    if (self->sel6C4 != -1) func_001BB058(self, self->sel6C4);
    if (self->sel6C8 != -1) func_001BB0C8(self, self->sel6C8);
    self->f678 = one;
    self->cur = value;
    self->mass = self->mass * self->scale;
}

void func_0013DE38(C25* self, u8* table, s32 index);
s32 func_0013DB28(MaskedCollider* self, s32 value);
s32 func_001300E8(void* node, s32 kind);

void func_0013DEE8(C26* self, u8* table, s32 index)
{
    s32 value;

    LatchContactObject(self, table, index);
    if (self->hold != 0) return;
    value = *(s32*)(table + ((1 - index) << 6));
    if (IsObjectOfKind((void*)value, 5) != 0) {
        if (IsObjectAccepted(self, value) != 0) {
            self->sel6D4 = (SwitchedCollider*)value;
        }
    }
}

void func_0013D068(MaskedCollider* self);
void* func_001925F0(void);
void func_001D7098(void* out, void* a1, void* self);

void func_0013DF68(C26* self)
{
    s32 local[4];
    func_0013D068(self);
    if (self->sel6D4 != 0) {
        if (self->sel6D4 != GetActiveSwitchedCollider()) {
            self->sel6D4 = 0;
            return;
        }
        InitOwnerMessage(local, self->f6D0, self);
        SwitchedCollider* p = self->sel6D4;
        p->desc05()->m4C(p, local);
        self->sel6D4 = 0;
    }
}

ASM_FUNC(func_0013DFD8);

ASM_FUNC(func_0013E430);

LINKER_REMNANT(func_0013E650);

ASM_FUNC(func_0013E658);

struct Self_13E6C8 { u8 pad0[0x10]; s32 f10; };
struct Base_13E6C8 { u8 pad0[0x10]; s32 f10; };

void* func_0018D500(s32 size);

void func_0013E6C8(Self_13E6C8* self, Tree03* src, Base_13E6C8* base, Tree03* dst)
{
    dst->count = src->count;
    dst->count2 = src->count2;
    dst->nodes = (TreeNode03*)AllocateFrontMemory(src->count * 12);
    for (s32 i = 0; i < dst->count; i++) {
        TreeNode03* s = &src->nodes[i];
        TreeNode03* d = &dst->nodes[i];
        d->face = (void*)(base->f10 + ((s32)s->face - self->f10));
        d->back = s->back != 0 ? (TreeNode03*)((s32)dst->nodes + ((s32)s->back - (s32)src->nodes)) : 0;
        d->front = s->front != 0 ? (TreeNode03*)((s32)dst->nodes + ((s32)s->front - (s32)src->nodes)) : 0;

    }
}

struct IntList_13E7C0 { s32 count; void* items[1]; };
void* func_0015A418(void*, s32, void*, void*);
bool func_0013E8D8(IntList_13E7C0*, void*);
void func_00182ED8(void*);

void func_0013E7C0(void* self, IntList_13E7C0* list, void* context)
{
    s32 n = list->count;
    void** items = list->items;
    for (s32 i = 0; i < n; i++) {
        void* object = FindFirstObjectById(self, 0x104, items[i], context);
        if (object) {
            AppendToQueuedObjects(list, object);
            func_00182ED8(object);
        }
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
            if (MatchesObjectId(key, *p) != 0) {
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
    s->id120 = (s32)TakeFlagTableIndex(g_flagTable);
    s->f140 = -1;
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
bool func_0013E8D8(Call_13E950* queue, void* value);

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

void func_0013E950(Zone28* self, Collider* a1)
{
    Iter_13E950 it;
    Begin_13E950::Of(&it, &a1->children);
    self->owner = a1;
    Node_13E950* node;
    while ((node = Next_13E950::Of(&it)) != 0) {
        if (node->f0->f8 & 0x40) {
            if (IsObjectInIdList((Call_13E950*)((u8*)self + 0x90), node) == 0) {
                if (IsObjectInIdList((Call_13E950*)((u8*)self + 8), node) == 0) {
                    AppendToQueuedObjects((Call_13E950*)((u8*)self + 8), node);
                }
            }
        }
    }
    g_activeListFrames = (ListFrame*)it.saved;
}

extern u8 D_00261420[];

void func_0013E7C0(void* a, void* b, void* c);
s32 func_00141008(void* table, s32 v);
void* func_001DBCC8(void* a, void* fn, void* c, s32 d, s32 e);
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
        ResolveZoneObjects(target, p, self->owner);
        p++;
    } while (--n >= 0);
    if (self->f11C != 0) {
        if (TestFlagTableBit(g_flagTable, self->id120)) {
            AppendQueuedCall(target, (void*)func_0013EAE0, self, 0, 0);
        }
    }
}

void* func_001DBCC8(void* a, void* fn, void* c, s32 d, s32 e);
void func_0013EF50(void* self, s32 a, s32 b);

void func_0013EAE0(void* selfp, s32 mode)
{
    Zone28* self = (Zone28*)selfp;
    if (mode == 0) {
        AppendQueuedCall(self->owner->world, (void*)func_0013EAE0, self, 0xC, 0);
    } else {
        func_0013EF50(self, 1, 1);
    }
}

s32 func_0013EC00(void* list, s32 size, void* count, s32 a, s32 b, s32 c, s32 d);
void func_0013EB30(Zone28* self, s32 a, s32 b, s32 c, s32 d)
{
    UpsertKeyedEntry(self->table14C, 8, &self->count148, a, b, c, d);
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
    self->stamp = g_gameTime;
    func_00129DF8(self->owner);
    if (s1 != 0) {
        func_0013EF50(self, 0, 0);
    }
    if (s2 != 0) {
        func_0013F070(self, 0);
    }
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
            void* v = FindObjectHandle(out, p->f4);
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
                    SetStateWalkerTarget(v, k);
                }
                count++;
            }
            p++;
            more = count < n;
        } while (more != 0);
    }
    return more;
}

void* func_0015A448(void* world, s32 key, void* requester);
s32 func_001833F0(void* owner, s32 key);
void* func_0012C8F8(void* obj, void* other, s32 a2, s32 a3, f32 fa, f32 fb);
void func_001518B8(void* t);
void func_001519A8(void* t);

struct Obj_13ED90 { u8 pad[0x40]; s32 key40; s32 flag44; };

void func_0013ED90(Zone28* self, s32 mode, void* p, void* q)
{
    s32 n = self->pairs[mode].queued.count;
    {
        s32* list = self->pairs[mode].queued.values;
        s32 i;
        for (i = 0; i < n; i++) {
            Obj_13ED90* obj = *(Obj_13ED90**)&list[i];
            void* other;
            s32 dir;
            if (MatchesObjectId(self->owner, obj->key40)) {
                other = self->owner;
            } else if (obj->key40 != -1) {
                other = func_0015A448(self->owner->world, obj->key40, self->owner);
            } else {
                other = 0;
            }
            if (p != 0 && obj->flag44 == 0) {
                f32 t = self->f118;
                dir = 0;
                if (t >= 0.0f) {
                    dir = 2;
                }
                func_0012C8F8(obj, other, dir, 0, 0.0f, t);
            } else if (self->f138 != 0) {
                f32 t = self->f118;
                dir = 0;
                if (t < 0.0f) {
                    dir = 2;
                }
                func_0012C8F8(obj, other, dir, 0, 0.0f, t);
            } else {
                func_0012C8F8(obj, other, 1, 0, 0.0f, self->f118);
            }
        }
    }
    func_0013ECB0(self->owner->world, self->count148, (Ent_13ECB0*)self->table14C, self->owner, mode == 0);
    if (self->f140 != -1 && q == 0) {
        void* t = func_0015A448(self->owner->world, self->f140, self->owner);
        if (mode != 0) {
            if (mode == 1) {
                ResetStepSequence(t);
            }
            return;
        }
        ChooseStepSequenceState(t);
    }
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
        TriggerScriptEvent(self->owner, 0x16, 0, 0);
    } else {
        TriggerScriptEvent(self->owner, 2, 0, 0);
    }
    if (self->f134 == 0) {
        if (q == 0) {
            StartSoundEffect(kind_13EF50_2, 0, (s32)self->owner, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
    }
    func_0013ED90(self, 0, p, q);
    if (self->f13C == 0) {
        SetZoneMode(self, 2);
    }
    if (self->f11C != 0) {
        SetFlagTableBit((Tab_13EF50*)g_flagTable, self->id120);
    }
    self->owner->desc->m0E(self->owner, 0xC, self);
}

void func_001837E0(void* obj, s32 kind, s32 a, s32 b);
void func_0013ED90(Zone28* self, s32 mode, void* p, void* q);

void func_0013F070(Zone28* self, void* p)
{
    TriggerScriptEvent(self->owner, 3, 0, 0);
    func_0013ED90(self, 1, p, 0);
    Collider* o = self->owner;
    o->desc->m0E(o, 13, self);
}

void func_001B7968(Collider* self);
void func_0013E918(void* p);

void func_0013F0E0(TriggerZone* self)
{
    InitCollider(self);
    InitZoneRecord(&self->zone);
}

void func_001BAC30(Collider* self);
void func_0013E950(Zone28* p, Collider* self);

void func_0013F110(TriggerZone* self)
{
    LoadCollider(self);
    CollectZoneChildren(&self->zone, self);
}

s32 func_001833F0(void* a, s32 n);
void func_001F5B08(void* end, void* begin, s32 bytes);

void func_0013F140(TriggerZone* self, void* a1, Quad28* q)
{
    s32 n = self->f7B4;
    s32 idx;
    if (MatchesObjectId(a1, 0x200)) {
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

INCLUDE_ASM(func_0013F1D8);

ASM_FUNC(func_0013F290);

void func_001BA130(Collider* self);

void func_0013F6C0(TriggerZone* self)
{
    s32 keep = self->zone.id120;
    CopyCollider(self);
    self->zone.id120 = keep;
    self->zone.owner = self;
}

extern void func_0013EB68(void* state);

void func_0013F6F8(TriggerZone* state) {
	SetZoneMode(&state->zone);
}

s32 func_001833F0(void* node, s32 key);
s32 func_001300E8(void* node, s32 kind);

s32 func_0013F718(TriggerZone* self, void* arg)
{
    if (self->countIdsIn > 0) {
        s32 i;
        for (i = 0; i < self->countIdsIn; i++) {
            if (MatchesObjectId(arg, self->idsIn[i]) != 0) {
                break;
            }
        }
        if (i >= self->countIdsIn) {
            return 0;
        }
    } else if (self->countIdsOut > 0) {
        s32 i;
        for (i = 0; i < self->countIdsOut; i++) {
            if (MatchesObjectId(arg, self->idsOut[i]) != 0) {
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
            if (IsObjectOfKind(arg, self->kindsIn[i]) != 0) {
                break;
            }
        }
        if (i >= self->countKindsIn) {
            return 0;
        }
    } else if (self->countKindsOut > 0) {
        s32 i;
        for (i = 0; i < self->countKindsOut; i++) {
            if (IsObjectOfKind(arg, self->kindsOut[i]) != 0) {
                break;
            }
        }
        if (i < self->countKindsOut) {
            return 0;
        }
    }
    return 1;
}

// The vector func_0013F8A0 loads.
extern const Vec02 D_00249DD0 = { 3.4028235e+38f, 0.0f, 0.0f, 0.0f };

ASM_FUNC(func_0013F8A0);

extern void func_00189150(void*, void*, void*);
f32 func_00188CE0(void* p);
f32 func_00205578(f32 x);

struct Loc_13F940 {
    f32 v[12];
};

s32 func_0013F940(TriggerZone* s, f32* out)
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

extern u8 D_00248D30[];

void func_001B9338(Collider* self, f32 t);
void func_001B9058(Collider* self, void* buf, s32 a, void* table, s32 b, f32 t);
void func_001B91A8(Collider* self, void* buf, s32 a, void* table, s32 b, f32 t);

void func_0013FA10(TriggerZone* self, f32 t)
{
    StepCollider(self, t);
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

ASM_FUNC(func_0013FAE8);

extern u8* D_00262E10;
extern f32 D_0026185C;

void func_001B93F8(Collider* self);
void func_0013F6F8(TriggerZone* self, s32 v);
s32 func_0013F8A0(TriggerZone* self, f32* out);
s32 func_0013F940(TriggerZone* self, f32* out);
s32 func_0013F718(TriggerZone* self, void* p);
void func_00129DF8(void* self);

void func_0013FD20(TriggerZone* self)
{
    UpdateCollider(self);
    switch (self->zone.mode) {
    case 2: {
        u8* g = g_player;
        f32 t;
        if (g) {
            if (*(s32*)(g + 0x2220) == 3 && *(s32*)(g + 0x2204) == self->id880) self->zone.stamp = g_gameTime;
        }
        t = self->zone.duration;
        if (0.0f <= t) {
            if (t < g_gameTime - self->zone.stamp) SetTriggerZoneMode(self, 4);
        }
        break;
    }
    case 3:
        break;
    case 4: {
        s32 r = -1;
        switch (self->state) {
        case 0: if (!func_0013F8A0(self, 0)) r = 1; break;
        case 1: if (!FindLargestEntryIndex(self, 0)) r = 1; break;
        case 2:
        case 4: r = 1; break;
        case 3: r = 0; break;
        }
        if (r != -1) SetTriggerZoneMode(self, r);
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
            u8* g = g_player;
            r = 0;
            if (g) {
                if (*(s32*)(g + 0x2220) == 3) r = *(s32*)(g + 0x2204) == self->id880;
            }
            break;
        }
        case 2: {
            Collider* s4 = self->root03();
            ContactRow03* l = s4->contacts->head;
            r = 0;
            for (; l; l = l->next) {
                Contact03* n = l->head;
                for (; n; n = n->next) {
                    s32 k = n->end[0].body != s4;
                    if (((ContactEnd03*)((u8*)n + (k << 6)))->part == self) {
                        if (PassesTriggerFilters(self, n->end[1 - k].body)) { r = 1; goto done; }
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
                s0 = FindLargestEntryIndex(self, &v[1]);
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
        SetTriggerZoneMode(self, r);
        break;
    }
    }
}

s32 func_001BC320(void* self, void* ev);
void func_0013F6F8(TriggerZone* state, s32 mode);

s32 func_00140028(TriggerZone* a0, void* a1)
{
    s32 r = HandleObjectEvent(a0, a1);
    if (r != 0 && (*(s32*)((u8*)a1 + 0xC) & 4) == 0 && a0->state == 3 && a0->zone.mode == 0) {
        SetTriggerZoneMode(a0, 1);
    }
    return r;
}

void func_0013E918(Zone28* p);
void func_001B7968(Collider* self);
void func_001B9AE0(void* self, s32 a, s32 b, s32 c, s32 d);

void func_001400A8(ZoneCollider* self)
{
    u64 m = 0x8000;
    InitCollider(self);
    InitZoneRecord(&self->zone);
    m <<= 28;
    self->flags538 = self->flags538 | m;
    SetColliderAnchors(self, 3, 0, 3, 0);
}

void func_001BAC30(void* self);
void func_0013E950(void* p, void* self);

void func_00140100(ZoneCollider* self)
{
    LoadCollider(self);
    CollectZoneChildren(&self->zone, self);
    if (self->f790 != 0) {
        self->zone.f13C = 1;
    }
}

void func_00124A48(void* self);
void func_0013EA38(void* p);
void func_00140238(ZoneCollider* self, s32 flag);
void* func_0015A448(void* obj, s32 id, void* ctx);


void func_00140140(ZoneCollider* self)
{
    StartPlacedObject(self);
    StartZoneRecord(&self->zone);
    func_00140238(self, 0);
    for (s32 i = 0; i < self->countIds; i++) {
        void* p = func_0015A448(self->world, self->ids[i], self);
        if (p != 0) {
            s32 n = self->countObjs;
            self->objs[n] = (s32)p;
            self->countObjs = n + 1;
        }
    }
    if (self->countIds == 0) {
        self->f5BC = 1;
    }
}

void func_001BA130(void* self);


void func_00140200(ZoneCollider* self)
{
    s32 saved = self->zone.id120;
    CopyCollider(self);
    self->zone.id120 = saved;
    self->zone.owner = self;
}


extern void func_0013EB68(void* state);

void func_00140238(ZoneCollider* self, s32 flag)
{
    SetZoneMode(&self->zone);
}

ASM_FUNC(func_00140258);

// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "list_iter.h"
#include "trigger_zone.h"
#include "zone_collider.h"
#include "flagged_object.h"
#include "object_gatherer.h"
#include "world.h"
#include "game_clock.h"
#include "object_event.h"


s32 func_001C1A28(void* a, void* b);

struct Self_140550 {
    u8 pad0[0x598];
    s32 f598;
    void* f59C[32];
};

s32 func_00140550(Self_140550* self, void* arg)
{
    for (s32 i = 0; i < self->f598; i++) {
        if (AppendPropertyToScriptList(arg, &self->f59C[i]) == 0) {
            return 0;
        }
    }
    return 1;
}


bool func_0013E8F8(void* a, s32 b);

void func_001405D0(void* a, void* b, s32 c)
{
    AppendToObjectQueue((u8*)a + 0x8, c);
}



void func_001405F0(u8* self, s32 value)
{
    func_001405D0(self + 0x554, self, value);
}

void func_001405D0(void* a, void* b, int c);

void func_00140618(void* self, int value)
{
    func_001405D0((u8*)self + 0x5C0, self, value);
}

bool func_0013E8F8(void* a, int b);

void func_00140640(void* self, void* unused, int value)
{
    AppendToObjectQueue((u8*)self + 0x90, value);
}

void func_00140640(void* self, void* unused, int value);

void func_00140660(TriggerZone* self, int value)
{
    func_00140640(&self->zone, self, value);
}

void func_0013EB30(void* p);
void func_00140640(void* a, void* b, void* c);

void func_00140688(void* self, void* b)
{
    func_00140640((u8*)self + 0x5C0, self, b);
}

void func_001406B0(TriggerZone* list, s32 value)
{
    list->idsIn[list->countIdsIn++] = value;
}

void func_001406D0(TriggerZone* self, s32 value)
{
    s32 n = self->countIdsOut;
    self->idsOut[n] = value;
    self->countIdsOut = n + 1;
}

void func_001406F0(TriggerZone* self, s32 value)
{
    s32 n = self->countKindsIn;
    self->kindsIn[n] = value;
    self->countKindsIn = n + 1;
}

// Newly matched US functions from the small-function wave.
extern void func_0013EB30(void*);
extern s32 func_0011E1F8(s32);
extern void func_001439A8(void*);
extern void func_001439C8(void*);
extern void func_001439E8(void*);
extern void func_00143A08(void*);
extern void* D_00261990;
extern void func_001448C8(void*, s32, void*);

void func_00140710(TriggerZone* self, void* value)
{
    s32 i = self->countKindsOut;
    u32 address = (u32)self + (u32)(i << 2);
    *(u32*)(address + 0x790) = (u32)value;
    self->countKindsOut = i + 1;
}

void func_00140730(void* self, void* value)
{
    s32 i = *(s32*)((u8*)self + 0x550);
    u32 address = (u32)self + (u32)(i << 2);
    *(u32*)(address + 0x554) = (u32)value;
    *(s32*)((u8*)self + 0x550) = i + 1;
}

void func_0013EB30(void* p);

void func_00140750(void* self)
{
    SetZoneEntry((u8*)self + 0x554);
}

void func_00140770(void* self) { SetZoneEntry((u8*)self + 0x5C0); }
