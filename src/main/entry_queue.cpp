// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x17B998 to 0x17D248: the entry queue, class 0x8F (include/entry_queue.h), and
// the adders of each kind of entry. Its name is ours, after the class.
#include "common.h"
#include "switched_collider.h"
#include "gauge_mode_object.h"
#include "countdown_collider.h"
#include "entry_queue.h"
#include "globals.h"
#include "object_link.h"
#include "message_body.h"
#include "object_event.h"
#include "shapes.h"
#include "screen_element.h"
#include "point_object.h"
#include "collider.h"
#include "placed_object.h"
#include "path_curve_object.h"
#include "on_off_object.h"
#include "asm_func.h"

// The entry queue (class 0x8F): its set-up, the functions that start, advance, bind and fill it,
// and the script commands that add entries. Its .rodata (0x24B000-0x24B054) is the jump tables
// of func_0017BCD0 and func_0017C428; its .data (0x263E34-0x263E48) the five floats its VU0
// functions read; its .bss the spare entry D_002BE478.

f32 D_00263E34 = -200.0f;
f32 D_00263E38 = 25.0f;
f32 D_00263E3C = 15.0f;
f32 D_00263E40 = 0.200000003f;
f32 D_00263E44 = 0.5f;

void InitObject(void* self);
void* AllocateFrontMemory(int size);

void InitEntryQueue(EntryQueue* self)
{
    InitObject(self);
    self->buffer = AllocateFrontMemory(0xA00);
    self->flag68 = 1;
}

s32 IsObjectOfKind(BaseObject* n, s32 kind);
void ConvertPositionToWorld(BaseObject* n, Vec02* out);
s32 GetObjectWorldPosition(BaseObject* n, Vec02* out);
s32 GetObjectWorldRotation(BaseObject* n, Vec02* out);
f32 ArctangentOfRatio(f32 a, f32 b);
void TransformPointBetweenFrames(void* a, void* b, void* c, Vec02* d);
void TransformDirectionBetweenFrames(void* a, void* b, Vec02* c, Vec02* d);

void GetNodeAnchorAndHeading(EntryQueue* self, BaseObject* n, Vec02* out, f32* outf)
{
    Vec02 v;
    Vec02 a;
    Vec02 b;
    Vec02 c;
    Player* s1 = (Player*)self->f3C;
    f32 r;

    if (n == 0)
    {
        goto tail;
    }
    if (IsObjectOfKind(n, 0x7E))
    {
        ConvertPositionToWorld(n, &v);
        r = s1->f638;
    }
    else if (IsObjectOfKind(n, 0x73))
    {
        GetObjectWorldPosition(n, &v);
        GetObjectWorldRotation(n, &a);
        r = ArctangentOfRatio(a.y, a.x);
    }
    else if (IsObjectOfKind(n, 0x6E))
    {
        TransformPointBetweenFrames(0, n->parent, &s1->pos, &a);
        {
            PathCurve* curve = ((PathCurveObject*)n)->curve;
            void (*fn)(void*, Vec02*, s32, Vec02*, Vec02*, s32, s32) =
                (void (*)(void*, Vec02*, s32, Vec02*, Vec02*, s32, s32))curve->vt->m10;
            if (fn)
            {
                fn(curve, &a, 0, &a, &b, 0, 0);
            }
        }
        TransformPointBetweenFrames(n->parent, 0, &a, &v);
        TransformDirectionBetweenFrames(n->parent, 0, &b, &c);
        r = ArctangentOfRatio(c.y, c.x);
    }
    else if (IsObjectOfKind(n, 2))
    {
        v = ((PlacedObject*)n)->v140;
        r = ArctangentOfRatio(((f32*)n)[0x114 / 4], ((f32*)n)[0x110 / 4]);
    }
    else
    {
    tail:
        v = s1->pos;
        v.z -= 75.0f;
        r = s1->f638;
    }
    if (out)
    {
        *out = v;
    }
    if (outf)
    {
        *outf = r;
    }
}

ASM_FUNC(func_0017BB78);


void SetOnOffObjectForcedState(void* p, s32 n);
s32 IsObjectAttached(void* p);

void ReplaceQueueOnOffObject(EntryQueue* self, OnOffObject* next)
{
    if (self->f58 != 0) {
        SetOnOffObjectForcedState(self->f58, -1);
        self->f58->f2D0 = 0;
        if (self->f5C != 0) {
            self->f58->desc->m03(self->f58);
        }
        self->f58 = 0;
    }
    if (next != 0) {
        self->f58 = next;
        s32 isNull = IsObjectAttached(next) == 0;
        self->f5C = isNull;
        if (isNull != 0) {
            next->desc->m02(next);
        }
        next->f2D0 = self->f3C;
        SetOnOffObjectForcedState(next, 1);
    }
}

INCLUDE_RODATA(jtbl_0024B000);
ASM_FUNC(func_0017BCD0);

INCLUDE_RODATA(jtbl_0024B030);
ASM_FUNC(func_0017C428);

void StartNextQueueEntry(EntryQueue* self);
s32 CheckQueueEntryDone(EntryQueue* self, void* item);

void AdvanceEntryQueue(EntryQueue* self)
{
    if (self->f40 < 0 && self->f34 > 0)
        StartNextQueueEntry(self);
    while (self->f40 < self->f34) {
        QueueEntry* entry = &((QueueEntry*)self->buffer)[self->f40];
        if (entry->state == 0 && !CheckQueueEntryDone(self, entry))
            break;
        StartNextQueueEntry(self);
    }
    if (self->f48 && CheckQueueEntryDone(self, self->f48))
        self->f48 = 0;
}

ASM_FUNC(func_0017C718);

void AdvanceEntryQueue(EntryQueue* self);

s32 IsEntryQueueRunning(EntryQueue* self)
{
    AdvanceEntryQueue(self);
    if (self->f34 > 0) {
        return self->f40 < self->f34;
    }
    return 0;
}

void UnbindEntryQueue(EntryQueue* self);

void ResetEntryQueue(EntryQueue* self)
{
    if (self->f3C != 0) {
        UnbindEntryQueue(self);
        self->f34 = 0;
    } else {
        self->f34 = 0;
    }
    self->f40 = 0;
}

void TriggerScriptEvent(void* self, s32 kind, s32 a, s32 b);
s32 SetPadSelectFlags(s32 a);
void AcquirePadSelectFlag(void* a);


void BindEntryQueueToObject(void* a0, void* a1)
{
    EntryQueue* self = (EntryQueue*)a0;
    ((Player*)a1)->entryQueue = self;
    self->f3C = a1;
    self->f40 = -1;
    TriggerScriptEvent(self, 0x17, 0, 0);
    if (self->flag68 != 0) {
        SetPadSelectFlags(4);
        AcquirePadSelectFlag(self->world);
    }
}


void SetEntryQueueTargetNode(void* self, s32 n);
void StopAnimationPlayer(void* p);
void SetGameClockScale(f32 x);
void TriggerScriptEvent(void* self, s32 a, s32 b, s32 c);
void ClearPadSelectFlags(s32 n);
void ReleasePadSelectFlag(void* p);

void UnbindEntryQueue(EntryQueue* self)
{
    if (self->f3C != 0) {
        ReplaceQueueOnOffObject(self, 0);
        SetEntryQueueTargetNode(self, 0);
        if (self->f50 != 0) {
            StopAnimationPlayer(self->f50);
            self->f50 = 0;
        }
        SetGameClockScale(1.0f);
        self->f40 = self->f34;
        self->f4C = 0;
        self->f48 = 0;
        ((Player*)self->f3C)->entryQueue = 0;
        self->f3C = 0;
        TriggerScriptEvent(self, 25, 0, 0);
        if (self->flag68 != 0) {
            ClearPadSelectFlags(4);
            ReleasePadSelectFlag(self->world);
        }
    }
}

// The entry AddQueueEntry hands out once the queue's 0x80 entries are used (0x14 bytes).
static u8 D_002BE478[0x14];
void FillMemory(void* p, s32 zero, s32 size);

void* AddQueueEntry(EntryQueue* pool, s32 a, s32 b, s32 c)
{
    if (pool->f34 >= 0x80) {
        return D_002BE478;
    }
    s32 n = pool->f34;
    u8* e = (u8*)pool->buffer + n * 0x14;
    pool->f34 = n + 1;
    FillMemory(e, 0, 0x14);
    s32* f = (s32*)e;
    f[0] = a;
    f[1] = b;
    f[2] = c;
    return e;
}

void* AddQueueEntryKind0(void* self, s32 b)
{
    return AddQueueEntry((EntryQueue*)self, 0, b, 1);
}

void* AddQueueEntryKind1(void* self, s32 b)
{
    return AddQueueEntry((EntryQueue*)self, 1, b, 1);
}

void* AddQueueEntryKind10(void* self, s32 b)
{
    return AddQueueEntry((EntryQueue*)self, 10, b, 1);
}


void AddQueueEntryKind2(void* self, s32 value)
{
    QueueEntry* o = (QueueEntry*)AddQueueEntry((EntryQueue*)self, 2, -1, 1);
    o->value = value;
}

void* AddQueueEntryKind3(void* self, s32 value)
{
    return AddQueueEntry((EntryQueue*)self, 3, value, 1);
}

void AddQueueEntryKind4(void* self, s32 a, f32 value)
{
    QueueEntry* o = (QueueEntry*)AddQueueEntry((EntryQueue*)self, 4, a, 0);
    o->valueF = value;
}

void* AddQueueEntryKind9(void* self, s32 value, s32 c)
{
    return AddQueueEntry((EntryQueue*)self, 9, value, c);
}

void AddQueueEntryKind5(void* self, s32 b, s32 c, s32 d, s32 e)
{
    QueueEntry* o = (QueueEntry*)AddQueueEntry((EntryQueue*)self, 5, b, e);
    o->value = c;
    o->value10 = d;
}

void AddQueueEntryKind6(void* self, s32 a, s32 b, f32 value)
{
    QueueEntry* o = (QueueEntry*)AddQueueEntry((EntryQueue*)self, 6, a, b);
    o->valueF = value;
}

void AddQueueEntryKind7(void* self, s32 b, s32 c, f32 value)
{
    QueueEntry* o = (QueueEntry*)AddQueueEntry((EntryQueue*)self, 7, b, c);
    o->valueF = value;
}

void AddQueueEntryKind8(void* self, s32 b, s32 c, s32 d)
{
    QueueEntry* o = (QueueEntry*)AddQueueEntry((EntryQueue*)self, 8, b, d);
    o->value = c;
}

void AddQueueEntryKind11(void* self, f32 value)
{
    QueueEntry* o = (QueueEntry*)AddQueueEntry((EntryQueue*)self, 11, -1, 1);
    o->valueF = value;
}

s32 AddQueueEntryKind12(void* self)
{
    return (s32)AddQueueEntry((EntryQueue*)self, 0xC, -1, 0);
}
