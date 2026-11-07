// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "flag_table.h"
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
// state (disc_access.cpp uses it; its own .data must start 8-aligned).
f32 D_00261390[8] = { 0.0f, 0.0f, 0.0f, 0.0f, -100000000.0f, 0.0f, 0.0f, 0.0f };
f32 D_002613B0[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 100000000.0f, 0.0f, 0.0f, 0.0f };
f32* D_002613D0[4] = { D_00261390, 0, 0, 0 };
f32* D_002613E0[3] = { D_002613B0, 0, 0 };
s32 g_discSectorCheckState = 0;
void TriggerScriptEvent(void* obj, s32 kind, s32 a, s32 b);

extern u8 g_flagTable[];
void InitCollider(void* self);
void* TakeFlagTableIndex(FlagTable* p);

void InitMaskedCollider(MaskedCollider* self)
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
    o->id688 = (s32)TakeFlagTableIndex((FlagTable*)g_flagTable);
    o->f614 = -1;
}

void LoadCollider(void* self);
s32 FindFirstObjectById(void* host, s32 a1, s32 a2, void* ctx);
void FindOrBuildMemberGroup(void* sub, void* self);
void ResolveAndStartObject(s32 a);

void LoadMaskedCollider(MaskedCollider* self)
{
    LoadCollider(self);
    if (self->f614 == -1) {
        FindOrBuildMemberGroup(&self->f618, self);
        return;
    }
    s32 v = FindFirstObjectById(self->world, 0x101, self->f614, self);
    self->f618 = v;
    if (v != 0) {
        ResolveAndStartObject(v);
    }
}

void CopyCollider(MaskedCollider* self, MaskedCollider* other);
void* CopyToFrontMemory(s32 size, void* owner);

void CopyMaskedCollider(MaskedCollider* self, MaskedCollider* other)
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

void InitSoundParams(void* p);



typedef void (*Hook_CE40)(void* self);

void StartPlacedObject(MaskedCollider* self);
void AttachMaskedColliderChildren(MaskedCollider* self);
void* AppendQueuedCall(void* target, Hook_CE40 fn, MaskedCollider* ctx, s32 a3, s32 a4);

void StartMaskedCollider(MaskedCollider* self)
{
    StartPlacedObject(self);
    AppendQueuedCall(self->world, AttachMaskedColliderChildren, self, 0, 0);
}

extern u8 g_flagTable[];

// A list walk's frame (ListFrame's words) with one more word after it, the flag
// func_00199C10 reads for each child.
struct ListFrameWithFlag { s32 list; s32 cursor; s32 link; s32 prev; s32 out; };
s32 TestFlagTableBit(FlagTable* t, s32 v);
s32 IsObjectOfKind(MaskedCollider* n, s32 kind);
void GetNumberedItemFlag(MaskedCollider* n, s32* out);
s32 MatchesObjectId(MaskedCollider* n, s32 key);

void AttachMaskedColliderChildren(MaskedCollider* self)
{
    ListFrameWithFlag fr;
    MaskedCollider* n;
    s32 i;
    Slot20* e;
    if (TestFlagTableBit((FlagTable*)g_flagTable, self->id688)) self->f678 = 1;
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

void UpdateCollider(void* self);

void UpdateMaskedCollider(MaskedCollider* self)
{
    UpdateCollider(self);
    if (self->f678 != 0) {
        self->f678 = 0;
        self->desc20()->m48(self);
    }
}

INCLUDE_ASM(func_0013D0B0);

INCLUDE_ASM(func_0013D278);

extern u8 g_flagTable[];

void SetFlagTableBit(FlagTable* table, s32 v);
void ClearFlagTableBit(FlagTable* table, s32 v);

void SetObjectHold(MaskedCollider* self, s32 v)
{
    self->hold = v;
    if (v != 0) {
        SetFlagTableBit((FlagTable*)g_flagTable, self->id688);
    } else {
        ClearFlagTableBit((FlagTable*)g_flagTable, self->id688);
    }
}

void AddMaskedColliderKeyKind0(MaskedCollider* q, s32 value)
{
    if ((u32)q->count550 < 16) {
        q->slots[q->count550].key = value;
        q->slots[q->count550].kind = 0;
        q->count550++;
    }
}

void AddMaskedColliderKeyKind1(MaskedCollider* q, s32 value)
{
    if ((u32)q->count550 < 16) {
        q->slots[q->count550].key = value;
        q->slots[q->count550].kind = 1;
        q->count550++;
    }
}



void AddMaskedColliderKeyKind2(MaskedCollider* self, s32 value)
{
    if ((u32)self->count550 < 16) {
        self->slots[self->count550].key = value;
        self->slots[self->count550].kind = 2;
        self->count550++;
    }
}

void AddMaskedColliderKeyKind3(MaskedCollider* q, s32 value)
{
    if ((u32)q->count550 < 16) {
        q->slots[q->count550].key = value;
        q->slots[q->count550].kind = 3;
        q->count550++;
    }
}

void SetAcceptsPlayer(MaskedCollider* self, s32 enabled)
{
    if (enabled) {
        self->mask = (self->mask | 1) & ~8;
    } else {
        self->mask &= ~1;
        if (self->mask == 0) self->mask = 8;
    }
}

void GetAcceptsPlayer(MaskedCollider* state, s32* result) {
	*result = state->mask & 1;
}

void SetAcceptsFlaggedObjects(MaskedCollider* self, s32 enabled)
{
    if (enabled) {
        self->mask = (self->mask | 4) & ~8;
    } else {
        self->mask &= ~4;
        if (self->mask == 0) self->mask = 8;
    }
}

void GetAcceptsFlaggedObjects(MaskedCollider* state, s32* result) {
	*result = (state->mask >> 2) & 1;
}

void AddAcceptedObjectId(MaskedCollider* obj, s32 value) { if ((u32)obj->count640 < 4) { obj->list644[obj->count640++] = (void*)value; obj->mask |= 2; } }

void AddAcceptedKind(MaskedCollider* r, s32 value)
{
    s32 n = r->count654;
    if ((u32)n < 4) {
        r->list658[n] = (void*)value;
        r->count654 = n + 1;
        r->mask |= 2;
    }
}

void AddMaskedColliderListEntry(MaskedCollider* obj, s32 value) { if ((u32)obj->count668 < 3) { obj->list66C[obj->count668++] = (void*)value; obj->mask |= 2; } }

void* GetMaskedColliderSoundParams(MaskedCollider* self)
{
    if (!self->f6B4) InitSoundParams(&self->f6B4);
    return self->f6B4;
}

void* GetActiveSwitchedCollider(void);
s32 MatchesObjectId(void* msg, void* item);
s32 IsObjectOfKind(void* msg, void* item);

s32 IsObjectAccepted(MaskedCollider* self, PathFollower* msg)
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

extern f32 g_gameTime;
void UpdateCollider(Collider* self);

void UpdateTimedState(TimedStateObject* self)
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

void HandlePlacedObjectNotification(TimedStateObject* self, s32 kind, ObjectMessage* msg);

void HandleTimedStateNotification(TimedStateObject* self, s32 kind, ObjectMessage* msg)
{
    HandlePlacedObjectNotification(self, kind, msg);
    if (kind == 0xF) {
        if ((TimedStateObject*)msg->target == self) {
            SetTimedState(self, 1);
        }
    }
}

s32 IsObjectOfKind(Collider* src, s32 kind);
s32 TestTimedStateContact(TimedStateObject* node, Collider* src)
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

extern f32 g_gameTime;
s32 FadeOutPlacedObject(f32 value);

void SetTimedState(TimedStateObject* self, s32 state)
{
    if (state != self->state) {
        *(s32*)((u8*)self + 0x550) = state;
        f32 t = g_gameTime;
        self->stamp = t;
        if (state == 2) {
            (void)FadeOutPlacedObject(self->param);
        }
    }
}

void InitMaskedCollider(MaskedCollider* self);

void InitPlayerFlaggedCollider(PlayerFlaggedCollider* self)
{
    InitMaskedCollider(self);
    self->mask = 5;
    self->f698 = -1;
}

void InitMassScalingCollider(MassScalingCollider* self)
{
    InitMaskedCollider(self);
    self->mask = 1;
    self->scale = 1.0f;
    self->sel6C4 = -1;
    self->sel6C8 = -1;
}

s32 IsObjectAccepted(MaskedCollider* self, s32 value);
void SetColliderTurnAnchorPreset(MassScalingCollider* self, s32 sel);
void SetColliderMoveAnchorPreset(MassScalingCollider* self, s32 sel);
void LatchContactObject(MassScalingCollider* self, u8* table, s32 index)
{
    s32 value;
    s32 one;

    if (self->hold != 0) return;
    one = 1;
    value = *(s32*)(table + ((one - index) << 6));
    if (self->f678 != 0) return;
    if (IsObjectAccepted(self, value) == 0) return;
    if (self->sel6C4 != -1) SetColliderTurnAnchorPreset(self, self->sel6C4);
    if (self->sel6C8 != -1) SetColliderMoveAnchorPreset(self, self->sel6C8);
    self->f678 = one;
    self->cur = value;
    self->mass = self->mass * self->scale;
}

void LatchContactObject(MassScalingCollider* self, u8* table, s32 index);
s32 IsObjectAccepted(MaskedCollider* self, s32 value);
s32 IsObjectOfKind(void* node, s32 kind);

void LatchAcceptedSwitchedCollider(LatchedSwitchCollider* self, u8* table, s32 index)
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

void UpdateMaskedCollider(MaskedCollider* self);
void* GetActiveSwitchedCollider(void);
void InitOwnerMessage(void* out, void* a1, void* self);

void UpdateLatchedSwitchCollider(LatchedSwitchCollider* self)
{
    s32 local[4];
    UpdateMaskedCollider(self);
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

INCLUDE_ASM(func_0013DFD8);

INCLUDE_ASM(func_0013E430);

LINKER_REMNANT(func_0013E650);

ASM_FUNC(func_0013E658);

void* AllocateFrontMemory(s32 size);

void CloneTreeNodes(Mesh03* self, Tree03* src, Mesh03* base, Tree03* dst)
{
    dst->count = src->count;
    dst->count2 = src->count2;
    dst->nodes = (TreeNode03*)AllocateFrontMemory(src->count * 12);
    for (s32 i = 0; i < dst->count; i++) {
        TreeNode03* s = &src->nodes[i];
        TreeNode03* d = &dst->nodes[i];
        d->face = (void*)((s32)base->faces + ((s32)s->face - (s32)self->faces));
        d->back = s->back != 0 ? (TreeNode03*)((s32)dst->nodes + ((s32)s->back - (s32)src->nodes)) : 0;
        d->front = s->front != 0 ? (TreeNode03*)((s32)dst->nodes + ((s32)s->front - (s32)src->nodes)) : 0;

    }
}

void* FindFirstObjectById(void*, s32, void*, void*);
bool AppendToQueuedObjects(Pair28*, void*);
void ResolveAndStartObject(void*);

void ResolveZoneObjects(void* self, Pair28* list, void* context)
{
    s32 n = list->seen.count;
    void** items = (void**)list->seen.values;
    for (s32 i = 0; i < n; i++) {
        void* object = FindFirstObjectById(self, 0x104, items[i], context);
        if (object) {
            AppendToQueuedObjects(list, object);
            ResolveAndStartObject(object);
        }
    }
}

s32 MatchesObjectId(void* key, s32 item);

s32 IsObjectInIdList(Queue28* set, void* key)
{
    s32 i = set->count - 1;
    s32* base = set->values;
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

bool AppendToQueuedObjects(Pair28* pair, s32 value) {
	pair->queued.values[pair->queued.count++] = value;
	return pair->queued.count < 16;
}

bool AppendToObjectQueue(Queue28* queue, s32 value) {
	queue->values[queue->count++] = value;
	return queue->count < 16;
}

extern u8 g_flagTable[];
void* TakeFlagTableIndex(FlagTable* p);

void InitZoneRecord(void* self)
{
    Zone28* s = (Zone28*)self;
    s->id120 = (s32)TakeFlagTableIndex((FlagTable*)g_flagTable);
    s->f140 = -1;
}




s32 IsObjectInIdList(Queue28* set, void* key);
bool AppendToQueuedObjects(Pair28* pair, void* value);

struct ListWalkNext {
    static BaseObject* Of(ListFrame* it)
    {
        BaseObject* obj = *(BaseObject**)it->link;
        it->link = (u8*)obj + it->offset;
        return obj;
    }
};

struct ListWalkBegin {
    static void Of(ListFrame* it, List01* list)
    {
        it->list = list;
        it->link = (u8*)list;
        it->offset = list->offset;
        it->prev = (g_activeListFrames);
        g_activeListFrames = (ListFrame*)it;
    }
};

void CollectZoneChildren(Zone28* self, Collider* a1)
{
    ListFrame it;
    ListWalkBegin::Of(&it, &a1->children);
    self->owner = a1;
    BaseObject* node;
    while ((node = ListWalkNext::Of(&it)) != 0) {
        if (node->desc->flags & 0x40) {
            if (IsObjectInIdList(&self->pairs[1].seen, node) == 0) {
                if (IsObjectInIdList(&self->pairs[0].seen, node) == 0) {
                    AppendToQueuedObjects(&self->pairs[0], node);
                }
            }
        }
    }
    g_activeListFrames = (ListFrame*)it.prev;
}

extern u8 g_flagTable[];

void ResolveZoneObjects(void* a, void* b, void* c);
s32 TestFlagTableBit(FlagTable* table, s32 v);
void* AppendQueuedCall(void* a, void* fn, void* c, s32 d, s32 e);
void DeferZoneRecordActivation(void* self, s32 mode);

void StartZoneRecord(Zone28* self)
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
        if (TestFlagTableBit((FlagTable*)g_flagTable, self->id120)) {
            AppendQueuedCall(target, (void*)DeferZoneRecordActivation, self, 0, 0);
        }
    }
}

void* AppendQueuedCall(void* a, void* fn, void* c, s32 d, s32 e);
void ActivateZoneRecord(void* self, s32 a, s32 b);

void DeferZoneRecordActivation(void* selfp, s32 mode)
{
    Zone28* self = (Zone28*)selfp;
    if (mode == 0) {
        AppendQueuedCall(self->owner->world, (void*)DeferZoneRecordActivation, self, 0xC, 0);
    } else {
        ActivateZoneRecord(self, 1, 1);
    }
}

s32 UpsertKeyedEntry(void* list, s32 size, void* count, s32 a, s32 b, s32 c, s32 d);
void SetZoneEntry(Zone28* self, s32 a, s32 b, s32 c, s32 d)
{
    UpsertKeyedEntry(self->table14C, 8, &self->count148, a, b, c, d);
}

extern f32 g_gameTime;
void ClearRootTries(void* self);
void ActivateZoneRecord(void* self, s32 a, s32 b);
void DeactivateZoneRecord(void* self, void* p);

void SetZoneMode(void* a, s32 b)
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
    ClearRootTries(self->owner);
    if (s1 != 0) {
        ActivateZoneRecord(self, 0, 0);
    }
    if (s2 != 0) {
        DeactivateZoneRecord(self, 0);
    }
}

// An entry of Zone28::table14C (func_0013EC00 adds or updates one, func_0013ECB0 applies a
// list of them): an object's id, a key it answers to (-1 any), and the states to set it to.
struct ZoneTargetEntry {
    s32 id;                 // 0x00
    s32 key;                // 0x04: -1 matches any
    s32 onState;            // 0x08: when the flag is set
    s32 offState;           // 0x0C: otherwise
};

s32 UpsertKeyedEntry(ZoneTargetEntry* tab, s32 cap, s32* count, s32 flag, s32 k1, s32 k2, s32 val)
{
    for (s32 i = 0; i < *count; i++) {
        ZoneTargetEntry* p = &tab[i];
        if (p->id == k1 && (p->key == -1 || p->key == k2)) {
            if (flag != 0) {
                p->onState = val;
            } else {
                p->offState = val;
            }
            return 1;
        }
    }
    s32 n = *count;
    if (n + 1 >= cap) {
        return 0;
    }
    *count = n + 1;
    ZoneTargetEntry* e = (ZoneTargetEntry*)((n << 4) + (s32)tab);
    e->id = k1;
    e->key = k2;
    if (flag != 0) {
        e->onState = val;
        e->offState = -1;
    } else {
        e->offState = val;
        e->onState = -1;
    }
    return 1;
}

s32 GatherObjectsByMode(void* self, s32 kind, s32 key, void* arg, s32 flags, void* out);
void* FindObjectHandle(void* a, s32 b);
void SetStateWalkerTarget(void* a, s32 b);

s32 SetGatheredWalkerTargets(void* self, s32 n, ZoneTargetEntry* ent, void* arg, s32 flag)
{
    s32 count = 0;
    s32 more;
    void* out;
    if (n > 0) {
        ZoneTargetEntry* p = ent;
        do {
            s32 r = GatherObjectsByMode(self, 0x304, p->id, arg, 1, &out);
            if (r != 1) {
                return r;
            }
            void* v = FindObjectHandle(out, p->key);
            if (v == 0) {
                count++;
            } else {
                s32 k;
                if (flag != 0) {
                    k = p->onState;
                } else {
                    k = p->offState;
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

void* FindFirstObjectByIdMode4(void* world, s32 key, void* requester);
s32 MatchesObjectId(void* owner, s32 key);
void* FindOrCreateSeekedAnimationPlayer(void* obj, void* other, s32 a2, s32 a3, f32 fa, f32 fb);
void ChooseStepSequenceState(void* t);
void ResetStepSequence(void* t);

// An object queued in a zone (func_0013ED90): the id of the object it goes to and a flag.
struct ZoneQueuedObject { u8 pad[0x40]; s32 key40; s32 flag44; };

void RunZoneRecordEntries(Zone28* self, s32 mode, void* p, void* q)
{
    s32 n = self->pairs[mode].queued.count;
    {
        s32* list = self->pairs[mode].queued.values;
        s32 i;
        for (i = 0; i < n; i++) {
            ZoneQueuedObject* obj = *(ZoneQueuedObject**)&list[i];
            void* other;
            s32 dir;
            if (MatchesObjectId(self->owner, obj->key40)) {
                other = self->owner;
            } else if (obj->key40 != -1) {
                other = FindFirstObjectByIdMode4(self->owner->world, obj->key40, self->owner);
            } else {
                other = 0;
            }
            if (p != 0 && obj->flag44 == 0) {
                f32 t = self->f118;
                dir = 0;
                if (t >= 0.0f) {
                    dir = 2;
                }
                FindOrCreateSeekedAnimationPlayer(obj, other, dir, 0, 0.0f, t);
            } else if (self->f138 != 0) {
                f32 t = self->f118;
                dir = 0;
                if (t < 0.0f) {
                    dir = 2;
                }
                FindOrCreateSeekedAnimationPlayer(obj, other, dir, 0, 0.0f, t);
            } else {
                FindOrCreateSeekedAnimationPlayer(obj, other, 1, 0, 0.0f, self->f118);
            }
        }
    }
    SetGatheredWalkerTargets(self->owner->world, self->count148, (ZoneTargetEntry*)self->table14C, self->owner, mode == 0);
    if (self->f140 != -1 && q == 0) {
        void* t = FindFirstObjectByIdMode4(self->owner->world, self->f140, self->owner);
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

extern u8 g_flagTable[];

void StartSoundEffect(Kind_13EF50 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void RunZoneRecordEntries(Zone28* self, s32 mode, void* p, void* q);
void SetZoneMode(Zone28* self, s32 k);
void SetFlagTableBit(FlagTable* t, s32 v);

void ActivateZoneRecord(Zone28* self, void* p, void* q)
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
    RunZoneRecordEntries(self, 0, p, q);
    if (self->f13C == 0) {
        SetZoneMode(self, 2);
    }
    if (self->f11C != 0) {
        SetFlagTableBit((FlagTable*)g_flagTable, self->id120);
    }
    self->owner->desc->m0E(self->owner, 0xC, self);
}

void TriggerScriptEvent(void* obj, s32 kind, s32 a, s32 b);
void RunZoneRecordEntries(Zone28* self, s32 mode, void* p, void* q);

void DeactivateZoneRecord(Zone28* self, void* p)
{
    TriggerScriptEvent(self->owner, 3, 0, 0);
    RunZoneRecordEntries(self, 1, p, 0);
    Collider* o = self->owner;
    o->desc->m0E(o, 13, self);
}

void InitCollider(Collider* self);
void InitZoneRecord(void* p);

void InitTriggerZone(TriggerZone* self)
{
    InitCollider(self);
    InitZoneRecord(&self->zone);
}

void LoadCollider(Collider* self);
void CollectZoneChildren(Zone28* p, Collider* self);

void LoadTriggerZone(TriggerZone* self)
{
    LoadCollider(self);
    CollectZoneChildren(&self->zone, self);
}

s32 MatchesObjectId(void* a, s32 n);
void MoveMemory(void* end, void* begin, s32 bytes);

void AddTriggerZoneQuad(TriggerZone* self, void* a1, Quad28* q)
{
    s32 n = self->f7B4;
    s32 idx;
    if (MatchesObjectId(a1, 0x200)) {
        idx = 0;
        if (n > 0) {
            u8* p = (u8*)self + n * 16;
            s32 o = n * 16;
            MoveMemory((u8*)(o + (s32)self) + 0x7C0, &self->quads[0], o);
        }
    } else {
        idx = n;
    }
    self->quads[idx] = *q;
    self->f7B4++;
}

INCLUDE_ASM(func_0013F1D8);

INCLUDE_ASM(func_0013F290);

void CopyCollider(Collider* self);

void CopyTriggerZone(TriggerZone* self)
{
    s32 keep = self->zone.id120;
    CopyCollider(self);
    self->zone.id120 = keep;
    self->zone.owner = self;
}

extern void SetZoneMode(void* state);

void SetTriggerZoneMode(TriggerZone* state) {
	SetZoneMode(&state->zone);
}

s32 MatchesObjectId(void* node, s32 key);
s32 IsObjectOfKind(void* node, s32 kind);

s32 PassesTriggerFilters(TriggerZone* self, void* arg)
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

extern void MultiplyMatrices3x3(void*, void*, void*);
f32 GetMatrixRotationCosine(void* p);
f32 Arccosine(f32 x);

s32 FindLargestEntryIndex(TriggerZone* s, f32* out)
{
    Mat3U loc;
    f32 best = 0.0f;
    s32 idx;
    s32 i;

    if (s->count7E0 == 0) {
        return 0;
    }
    for (i = s->count7E0 - 1; i >= 0; i--) {
        Entry28* e = (Entry28*)((u8*)s + 0x7F0 + i * 0x30);
        MultiplyMatrices3x3(&s->rot, e, &loc);
        f32 t = GetMatrixRotationCosine(&loc);
        if (best < t) {
            best = t;
            idx = i;
        }
    }
    if (out != 0) {
        *out = Arccosine(best);
    }
    return idx;
}

extern u8 D_00248D30[];

void StepCollider(Collider* self, f32 t);
void SteerColliderTowardPosition(Collider* self, void* buf, s32 a, void* table, s32 b, f32 t);
void SteerColliderTowardRotation(Collider* self, void* buf, s32 a, void* table, s32 b, f32 t);

void StepTriggerZone(TriggerZone* self, f32 t)
{
    StepCollider(self, t);
    switch (self->state) {
    case 0:
        if (self->f7B4 != 0) {
            u8* p = (u8*)self + 0x7C0;
            if (self->zone.mode != 4) {
                p += self->f7B0 << 4;
            }
            SteerColliderTowardPosition(self, p, (s32)self->p20C, D_00248D30, (s32)self->p210, t);
        }
        break;
    case 1:
        if (self->count7E0 != 0) {
            u8* p = (u8*)self + 0x7F0;
            if (self->zone.mode != 4) {
                p += self->f7B0 * 0x30;
            }
            SteerColliderTowardRotation(self, p, (s32)self->p214, D_00248D30, (s32)self->p218, t);
        }
        break;
    }
}

INCLUDE_ASM(func_0013FAE8);

extern u8* g_player;
extern f32 g_gameTime;

void UpdateCollider(Collider* self);
void SetTriggerZoneMode(TriggerZone* self, s32 v);
s32 func_0013F8A0(TriggerZone* self, f32* out);
s32 FindLargestEntryIndex(TriggerZone* self, f32* out);
s32 PassesTriggerFilters(TriggerZone* self, void* p);
void ClearRootTries(void* self);

void UpdateTriggerZone(TriggerZone* self)
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
                ClearRootTries(self);
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

s32 HandleObjectEvent(void* self, void* ev);
void SetTriggerZoneMode(TriggerZone* state, s32 mode);

s32 HandleTriggerZoneEvent(TriggerZone* a0, void* a1)
{
    s32 r = HandleObjectEvent(a0, a1);
    if (r != 0 && (*(s32*)((u8*)a1 + 0xC) & 4) == 0 && a0->state == 3 && a0->zone.mode == 0) {
        SetTriggerZoneMode(a0, 1);
    }
    return r;
}

void InitZoneRecord(Zone28* p);
void InitCollider(Collider* self);
void SetColliderAnchors(void* self, s32 a, s32 b, s32 c, s32 d);

void InitZoneCollider(ZoneCollider* self)
{
    u64 m = 0x8000;
    InitCollider(self);
    InitZoneRecord(&self->zone);
    m <<= 28;
    self->flags538 = self->flags538 | m;
    SetColliderAnchors(self, 3, 0, 3, 0);
}

void LoadCollider(void* self);
void CollectZoneChildren(void* p, void* self);

void LoadZoneCollider(ZoneCollider* self)
{
    LoadCollider(self);
    CollectZoneChildren(&self->zone, self);
    if (self->f790 != 0) {
        self->zone.f13C = 1;
    }
}

void StartPlacedObject(void* self);
void StartZoneRecord(void* p);
void SetZoneColliderMode(ZoneCollider* self, s32 flag);
void* FindFirstObjectByIdMode4(void* obj, s32 id, void* ctx);


void StartZoneCollider(ZoneCollider* self)
{
    StartPlacedObject(self);
    StartZoneRecord(&self->zone);
    SetZoneColliderMode(self, 0);
    for (s32 i = 0; i < self->countIds; i++) {
        void* p = FindFirstObjectByIdMode4(self->world, self->ids[i], self);
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

void CopyCollider(void* self);


void CopyZoneCollider(ZoneCollider* self)
{
    s32 saved = self->zone.id120;
    CopyCollider(self);
    self->zone.id120 = saved;
    self->zone.owner = self;
}


extern void SetZoneMode(void* state);

void SetZoneColliderMode(ZoneCollider* self, s32 flag)
{
    SetZoneMode(&self->zone);
}

INCLUDE_ASM(func_00140258);

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


s32 AppendPropertyToScriptList(void* a, void* b);

s32 TestListedEntriesAccepted(ZoneCollider* self, void* arg)
{
    for (s32 i = 0; i < self->countInside; i++) {
        if (AppendPropertyToScriptList(arg, &self->inside[i]) == 0) {
            return 0;
        }
    }
    return 1;
}


bool AppendToObjectQueue(void* a, s32 b);

void AppendZoneFirstQueue(void* a, void* b, s32 c)
{
    AppendToObjectQueue((u8*)a + 0x8, c);
}



void AppendTriggerZoneFirstQueue(u8* self, s32 value)
{
    AppendZoneFirstQueue(self + 0x554, self, value);
}

void AppendZoneFirstQueue(void* a, void* b, int c);

void AppendZoneColliderFirstQueue(void* self, int value)
{
    AppendZoneFirstQueue((u8*)self + 0x5C0, self, value);
}

bool AppendToObjectQueue(void* a, int b);

void AppendZoneSecondQueue(void* self, void* unused, int value)
{
    AppendToObjectQueue((u8*)self + 0x90, value);
}

void AppendZoneSecondQueue(void* self, void* unused, int value);

void AppendTriggerZoneSecondQueue(TriggerZone* self, int value)
{
    AppendZoneSecondQueue(&self->zone, self, value);
}

void SetZoneEntry(void* p);
void AppendZoneSecondQueue(void* a, void* b, void* c);

void AppendZoneColliderSecondQueue(void* self, void* b)
{
    AppendZoneSecondQueue((u8*)self + 0x5C0, self, b);
}

void AddIncludedId(TriggerZone* list, s32 value)
{
    list->idsIn[list->countIdsIn++] = value;
}

void AddExcludedId(TriggerZone* self, s32 value)
{
    s32 n = self->countIdsOut;
    self->idsOut[n] = value;
    self->countIdsOut = n + 1;
}

void AddIncludedKind(TriggerZone* self, s32 value)
{
    s32 n = self->countKindsIn;
    self->kindsIn[n] = value;
    self->countKindsIn = n + 1;
}

// Newly matched US functions from the small-function wave.
extern void SetZoneEntry(void*);
extern s32 SyncDiscRead(s32);
extern void SetCameraFogNear(void*);
extern void SetCameraFogFar(void*);
extern void SetCameraFogStrength(void*);
extern void SetCameraFogColor(void*);
extern void* g_camera;
extern void SetCameraPlacement(void*, s32, void*);

void AddExcludedKind(TriggerZone* self, void* value)
{
    s32 i = self->countKindsOut;
    u32 address = (u32)self + (u32)(i << 2);
    *(u32*)(address + 0x790) = (u32)value;
    self->countKindsOut = i + 1;
}

void AddZoneColliderId(void* self, void* value)
{
    s32 i = *(s32*)((u8*)self + 0x550);
    u32 address = (u32)self + (u32)(i << 2);
    *(u32*)(address + 0x554) = (u32)value;
    *(s32*)((u8*)self + 0x550) = i + 1;
}

void SetZoneEntry(void* p);

void SetTriggerZoneEntry(void* self)
{
    SetZoneEntry((u8*)self + 0x554);
}

void SetZoneColliderEntry(void* self) { SetZoneEntry((u8*)self + 0x5C0); }
