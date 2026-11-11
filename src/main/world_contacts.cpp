// SPDX-License-Identifier: AGPL-3.0-or-later
// The world's contact pairs, 0x1385A0 to 0x138FF0 (no .rodata, .data or .bss of its own):
// SetContactPairFlags and the contact rows, the three sweep axes (add, remove, sort) and
// UpdateWorldContacts. The edges are not proved by retail, only by the change of role: the
// buffered stream reader ends before it (buffered_stream.cpp) and the blend animations begin
// after it (blend_animation.cpp), and none of the three reads .rodata or .data of its own, so
// a cut anywhere between their functions links to the same bytes. The cut before could lie
// from 0x138550 to 0x1385A0, the one after from 0x138F28 to 0x139038 (LoopOverMinCountNoOp,
// which BuildCombinedBlendAnimation calls, goes with the blend animations). The name is ours,
// after its role.
#include "common.h"
#include "asm_func.h"
#include "list_iter.h"
#include "buffered_stream.h"
#include "key_id.h"
#include "world_listed_object.h"
#include "effect_spawner.h"
#include "world.h"
#include "child_group_object.h"
#include "aim_blend_grid.h"
#include "packet_writer.h"
#include "owned_record.h"
#include "object_message.h"
#include "globals.h"
#include "anim_curve.h"
#include "attachment.h"
#include "cursor_animator.h"
#include "texture_table.h"
#include "vu0.h"
#include "placed_object.h"
#include "collider.h"
#include "common.h"
#include "list_iter.h"
#include "buffered_stream.h"
#include "key_id.h"
#include "common.h"
#include "list_iter.h"
#include "world_listed_object.h"
#include "effect_spawner.h"
#include "world.h"
#include "child_group_object.h"
#include "aim_blend_grid.h"
#include "packet_writer.h"
#include "owned_record.h"
#include "object_message.h"
#include "globals.h"
#include "list_iter.h"



struct ContactPairLink { s32 f0; s32 f4; ContactPairLink* f8; Collider* fC; };

ContactPairLink* PushContactRow(World* w, s32 a, s32 b);
ContactPairLink* UnlinkContactRow(World* w, s32 a, s32 b);
void FreePooledContactChain(World* w, s32 a);
void ClearRootTries(Collider* e);
void PushFreeSlot(u8* w, ContactPairLink* l);


void SetContactPairFlags(World* w, s32 a, s32 b, u8 set, u8 clr) {
    ContactPairLink* n1;
    ContactPairLink* n2;
    s32 ia = (a - (s32)w->tables) >> 4;
    s32 ib = (b - (s32)w->tables) >> 4;
    u8* p = (u8*)w->buf1ADC + (ia << 8) + ib;
    u8* q = (u8*)w->buf1ADC + (ib << 8) + ia;
    u8 v = (set | *p) & ~clr;
    *q = v;
    *p = v;
    if ((v & 0xF) == 0xF || (v & 0x40)) {
        if (v & 0x80) return;
        u8 v2 = v | 0x80;
        *p = v2;
        *q = v2;
        n1 = PushContactRow(w, a, b);
        n2 = PushContactRow(w, b, a);
        n1->f8 = n2;
        n2->f8 = n1;
    } else if (v & 0x80) {
        u8 v2 = v & 0x7F;
        *p = v2;
        *q = v2;
        n1 = UnlinkContactRow(w, a, b);
        n2 = UnlinkContactRow(w, b, a);
        if (n1->f0) {
            u64 m = (u64)0x8000 << 40;
            FreePooledContactChain(w, n1->f0);
            if (!(n1->fC->flags538 & m)) ClearRootTries(n1->fC);
            if (!(n2->fC->flags538 & m)) ClearRootTries(n2->fC);
        }
        PushFreeSlot((u8*)w + 0x1AF0, n1);
        PushFreeSlot((u8*)w + 0x1AF0, n2);
    }
}

struct ContactRowNode { s32 a0; ContactRowNode* next; void* a8; s32 value; };
struct ContactRowList { ContactRowNode* head; };
struct ContactRowSource { u8 pad0[4]; s32 value4; };

void* TakePoolSlot(void* pool);

ContactRowNode* PushContactRow(World* self, ContactRowList* list, ContactRowSource* src)
{
    ContactRowNode* n = (ContactRowNode*)TakePoolSlot((u8*)self + 0x1AF0);
    n->a0 = 0;
    n->value = src->value4;
    n->next = list->head;
    list->head = n;
    return n;
}

ContactRow03* UnlinkContactRow(void* unused, ContactRow03** head, Contacts03* key)
{
    ContactRow03* node = *head;
    Collider* wanted = key->owner;
    while (node) {
        if (node->other == wanted) {
            *head = node->next;
            break;
        }
        head = &node->next;
        node = node->next;
    }
    return node;
}

void* FindContactRow(Collider* self, Collider* other)
{
    ContactRow03* cur = self->root03()->contacts->head;
    PlacedObject* key = other->root;
    if (cur != 0) {
        do {
            if (cur->other != key) {
                cur = cur->next;
            } else {
                return cur;
            }
        } while (cur != 0);
    }
    return 0;
}

void* FindContactRow(void* self, void* other);

s32 GetContactRowHead(void* self, void* other)
{
    s32* p = (s32*)FindContactRow(self, other);
    s32 r = 0;
    if (p != 0) {
        r = *p;
    }
    return r;
}

struct SweepAxisSlot {
    s32 flag;
    void* owner;
    void* link;
};

void MarkSweepAxesUnsorted(void* self);

void AddColliderToSweepAxes(World* self, void* arg)
{
    World* t = self;
    s32 stride = 24;
    s32 one = 1;
    u8* a3 = (u8*)arg + 0x430;
    u8* a2 = (u8*)arg + 0x420;
    s32 off = 0;
    s32 n = 2;
    do {
        n--;
        SweepAxisSlot* e = (SweepAxisSlot*)((u8*)t->buf1AD8 + off + t->count38 * stride);
        off += 0x1800;
        e->link = a2;
        e->flag = 0;
        e->owner = arg;
        a2 += 4;
        e++;
        e->link = a3;
        e->owner = arg;
        e->flag = one;
        a3 += 4;
    } while (n >= 0);
    MarkSweepAxesUnsorted(self);
}

void* MoveMemory(void* dst, void* src, s32 bytes);

// Takes the collider's two entries out of each of the three axes: the scan passes the other
// colliders' entries, remembers the collider's start entry (flag 0) and stops at its end entry,
// and MoveMemory closes the two gaps. The pass over another collider's entry is its own
// `continue`: g++ rolls the loop's tests to its end with that label among them, so jump.c does
// not copy them in front of the loop, the owner is compared once at this loop's depth, and its
// few references put it after self in global-alloc's order (docs/TOOLCHAIN.md, "Loops").
void RemoveColliderFromSweepAxes(World* self, void* owner)
{
    s32 i;
    SweepAxisSlot* base;
    SweepAxisSlot* cur;
    SweepAxisSlot* start;

    for (i = 0; i < 3; i++) {
        base = (SweepAxisSlot*)((u8*)self->buf1AD8 + i * 0x1800);
        cur = base;
        for (;;) {
            if (cur->owner != owner) {
                cur++;
                continue;
            }
            if (cur->flag == 0) {
                start = cur;
            } else {
                break;
            }
            cur++;
        }
        s32 n = cur - start;
        MoveMemory(start, start + 1, n * 12 - 12);
        MoveMemory(cur - 1, cur + 1, (self->count38 * 2 - (cur - base)) * 12 - 12);
    }
}

#include "common.h"
#include "list_iter.h"
#include "world_listed_object.h"
#include "effect_spawner.h"
#include "world.h"
#include "child_group_object.h"
#include "aim_blend_grid.h"
#include "packet_writer.h"
#include "owned_record.h"
#include "object_message.h"
#include "globals.h"

void MarkSweepAxesUnsorted(World* a0)
{
    a0->f1AEC = 0;
}

void* MoveMemory(void* dst, void* src, s32 bytes);

// An entry of one of the three sweep axes (0x200 of them each in buf1AD8): a body's start (0)
// or end (1) on the axis and the bound it reads.
struct SweepEntry {
    s32 end;                // 0x00
    Collider* body;         // 0x04
    f32* bound;             // 0x08
};

// The axes' size (0x1800 bytes) is a named local, as AddColliderToSweepAxes names its stride:
// a pseudo live over the loop that gets no saved register, so reload rematerialises it before
// the multiply and the product takes its own register (docs/TOOLCHAIN.md, "Loops").
void SortSweepAxes(World* self)
{
    if (self->count38 == 0 || self->f1AEC != 0) {
        return;
    }
    s32 axisSize = 0x1800; // one axis: 0x200 entries
    s32 axis = 0;
    u8 bit = 1;
    for (; axis < 3; axis++) {
        SweepEntry* list = (SweepEntry*)((u8*)self->buf1AD8 + axis * axisSize);
        SweepEntry* p = list;
        f32 top = *p->bound;
        p++;
        for (s32 k = self->count38 * 2; --k > 0; p++) {
            f32 v = *p->bound;
            if (top <= v) {
                top = v;
            } else {
                SweepEntry* q = p - 1;
                while (q >= list) {
                    if (*q->bound <= v) {
                        break;
                    }
                    if (p->end != q->end) {
                        if (p->end == 0) {
                            SetContactPairFlags(self, (s32)p->body->contacts, (s32)q->body->contacts, bit, 0);
                        } else {
                            SetContactPairFlags(self, (s32)p->body->contacts, (s32)q->body->contacts, 0, bit);
                        }
                    }
                    q--;
                }
                q++;
                SweepEntry tmp = *p;
                MoveMemory(q + 1, q, (p - q) * sizeof(SweepEntry));
                *q = tmp;
            }
        }
        bit <<= 1;
    }
    self->f1AEC = 1;
}

void ClearRootObjectStateBits(void* a0, Collider* owner, u32 mask)
{
    Collider* n = owner->root03();
    if (n) {
        n->f4B8 &= ~mask;
    }
}

struct ContactBody;
struct ContactPart;

struct ContactPartVt
{
    u8 pad0[0x10C];
    void (*f10C)(ContactPart* c);
    void (*f110)(ContactPart* c);
};

struct ContactPart
{
    ContactPartVt* vt;
    u8 pad[0x2E4 - 4];
    ContactPart* next;
};

struct ContactCursor
{
    Contact03* prev;
    Contact03* it;
};

struct ContactSlot
{
    Contact03* f0;
};

struct ContactNode
{
    Contact03* f0;
    ContactNode* f4;
    ContactSlot* f8;
    ContactBody* fC;
};

struct ContactNodeList
{
    ContactNode* head;
};

struct ContactBody
{
    u8 pad0[0x2C8];
    u64 bits2C8;
    u8 pad1[0x2D8 - 0x2D0];
    ContactPart* children;
    u8 pad2[0x414 - 0x2DC];
    ContactBody* next;
    u8 pad3[0x480 - 0x418];
    ContactNodeList* list;
    u8 pad4[0x4B8 - 0x484];
    s32 kind;
    u8 pad5[0x538 - 0x4BC];
    u64 bits538;
};

void SortSweepAxes(World* w);
void FreePooledContactChain(World* w, Contact03* item);
Contact03* BuildObjectPairContacts(World* w, ContactBody** pair, s32 arg);
void NotifyContactEnds(World* w, s32 one, Contact03** item);
void ClearRootTries(ContactBody* o);

void UpdateWorldContacts(World* w, s32 arg)
{
    ContactBody* pair[2];
    ContactBody* o;
    ContactPart* ch;
    SortSweepAxes(w);
    for (o = (ContactBody*)w->list6C.head; o; o = o->next)
    {
        pair[0] = o;
        if (o->kind == 7)
        {
            continue;
        }
        if (o->bits538 & (0x8000ull << 27))
        {
            continue;
        }
        o->bits538 |= 0x8000ull << 46;
        ContactNode* node = pair[0]->list->head;
        for (; node; node = node->f4)
        {
            s32 dead = 7;
            u64 linked = 0x8000ull << 22;
            u64 visited = 0x8000ull << 27;
            u64 marked = 0x8000ull << 46;
            pair[1] = node->fC;
            if (pair[1] < pair[0] && pair[1]->kind != dead && (pair[1]->bits2C8 & linked))
            {
                continue;
            }
            if (pair[1]->bits538 & visited)
            {
                continue;
            }
            pair[1]->bits538 |= marked;
            if (((pair[0]->kind ^ 1) & 1) || ((pair[1]->kind ^ 1) & 1))
            {
                Contact03* old = node->f0;
                if (old)
                {
                    FreePooledContactChain(w, old);
                }
                Contact03* nw = BuildObjectPairContacts(w, pair, arg);
                node->f0 = nw;
                node->f8->f0 = nw;
                if ((old == 0) != (node->f0 == 0))
                {
                    if (!(pair[0]->bits538 & (0x8000ull << 40)))
                    {
                        ClearRootTries(pair[0]);
                    }
                    if (!(pair[1]->bits538 & (0x8000ull << 40)))
                    {
                        ClearRootTries(pair[1]);
                    }
                }
            }
            else
            {
                ContactCursor p;
                for (p.it = node->f0; p.it; p.it = p.it->next)
                {
                    NotifyContactEnds(w, 1, &p.it);
                }
            }
        }
    }
    for (o = (ContactBody*)w->list6C.head; o; o = o->next)
    {
        if (o->kind & 4)
        {
            continue;
        }
        for (ch = o->children; ch; ch = ch->next)
        {
            if (ch->vt->f110)
            {
                ch->vt->f110(ch);
            }
        }
        o->bits538 |= 0x8000ull << 46;
    }
    for (o = (ContactBody*)w->list6C.head; o; o = o->next)
    {
        if (o->bits538 & (0x8000ull << 46))
        {
            for (ch = o->children; ch; ch = ch->next)
            {
                if (ch->vt->f10C)
                {
                    ch->vt->f10C(ch);
                }
            }
            o->bits538 &= ~(0x8000ull << 46);
        }
        o->kind = 7;
    }
}

void SetContactPairFlags(World* a0, s32 a1, Contacts03* a2, s32 a3, s32 a4);

void InitContactPairFlags(World* self, Collider* obj)
{
    obj->f4B8 = 0;
    Contacts03* n = self->usedTables;
    while (n != 0) {
        if (n->owner != obj) {
            s32 s2 = 0;
            if (obj->desc03()->m38(obj, n->owner) || n->owner->desc03()->m38(n->owner, obj)) {
                s2 = 1;
            }
            SetContactPairFlags(self, (s32)obj->contacts, n, s2 == 0 ? 8 : 0, s2 ? 8 : 0);
        }
        n = n->next;
    }
}
