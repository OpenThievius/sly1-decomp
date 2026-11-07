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

void func_00182C18(void* self);
void* func_0018D500(int size);

void func_0017B998(EntryQueue* self)
{
    InitObject(self);
    self->buffer = AllocateFrontMemory(0xA00);
    self->flag68 = 1;
}

struct Vt_17B9D0
{
    u8 pad0[0x28];
    void (*f28)(void* self, Vec02* a, s32 b, Vec02* c, Vec02* d, s32 e, s32 f);
};

struct Node_17B9D0
{
    u8 pad0[0x18];
    void* f18;
    u8 pad1c[0x18];
    struct { Vt_17B9D0* vt; }* f34;
    u8 pad38[0x108];
    Vec02 f140;
};

struct Self_17B9D0
{
    u8 pad0[0x3C];
    u8* f3C;
};

s32 func_001300E8(Node_17B9D0* n, s32 kind);
void func_001920B0(Node_17B9D0* n, Vec02* out);
s32 func_001F3BD8(Node_17B9D0* n, Vec02* out);
s32 func_001F3C08(Node_17B9D0* n, Vec02* out);
f32 func_00205778(f32 a, f32 b);
void func_00128018(void* a, void* b, void* c, Vec02* d);
void func_001280C0(void* a, void* b, Vec02* c, Vec02* d);

void func_0017B9D0(Self_17B9D0* self, Node_17B9D0* n, Vec02* out, f32* outf)
{
    Vec02 v;
    Vec02 a;
    Vec02 b;
    Vec02 c;
    u8* s1 = self->f3C;
    f32 r;

    if (n == 0)
    {
        goto tail;
    }
    if (IsObjectOfKind(n, 0x7E))
    {
        ConvertPositionToWorld(n, &v);
        r = *(f32*)(s1 + 0x638);
    }
    else if (IsObjectOfKind(n, 0x73))
    {
        GetObjectWorldPosition(n, &v);
        GetObjectWorldRotation(n, &a);
        r = ArctangentOfRatio(a.y, a.x);
    }
    else if (IsObjectOfKind(n, 0x6E))
    {
        func_00128018(0, n->f18, s1 + 0x100, &a);
        {
            void (*fn)(void*, Vec02*, s32, Vec02*, Vec02*, s32, s32) =
                (void (*)(void*, Vec02*, s32, Vec02*, Vec02*, s32, s32))n->f34->vt->f28;
            if (fn)
            {
                fn(n->f34, &a, 0, &a, &b, 0, 0);
            }
        }
        func_00128018(n->f18, 0, &a, &v);
        func_001280C0(n->f18, 0, &b, &c);
        r = ArctangentOfRatio(c.y, c.x);
    }
    else if (IsObjectOfKind(n, 2))
    {
        v = n->f140;
        r = ArctangentOfRatio(((f32*)n)[0x114 / 4], ((f32*)n)[0x110 / 4]);
    }
    else
    {
    tail:
        v = *(Vec02*)(s1 + 0x100);
        v.z -= 75.0f;
        r = *(f32*)(s1 + 0x638);
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

typedef void (*VFn_17BC20)(void* self);

struct Comp_17BC20 {
    VFn_17BC20* vtbl;
    u8 pad0[0x2D0 - 4];
    s32 f2D0;
};

struct Obj_17BC20 {
    u8 pad0[0x3C];
    s32 f3C;
    u8 pad1[0x58 - 0x40];
    Comp_17BC20* f58;
    s32 f5C;
};

void func_001E2840(void* p, s32 n);
s32 func_00182FC8(void* p);

void func_0017BC20(Obj_17BC20* self, Comp_17BC20* next)
{
    if (self->f58 != 0) {
        SetOnOffObjectForcedState(self->f58, -1);
        self->f58->f2D0 = 0;
        if (self->f5C != 0) {
            self->f58->vtbl[7](self->f58);
        }
        self->f58 = 0;
    }
    if (next != 0) {
        self->f58 = next;
        s32 isNull = IsObjectAttached(next) == 0;
        self->f5C = isNull;
        if (isNull != 0) {
            next->vtbl[6](next);
        }
        next->f2D0 = self->f3C;
        SetOnOffObjectForcedState(next, 1);
    }
}

INCLUDE_RODATA(jtbl_0024B000);
ASM_FUNC(func_0017BCD0);

INCLUDE_RODATA(jtbl_0024B030);
ASM_FUNC(func_0017C428);

struct Entry_17C660 { u8 pad[8]; s32 state; u8 tail[8]; };
void func_0017BCD0(EntryQueue* self);
s32 func_0017C428(EntryQueue* self, void* item);

void func_0017C660(EntryQueue* self)
{
    if (self->f40 < 0 && self->f34 > 0)
        StartNextQueueEntry(self);
    while (self->f40 < self->f34) {
        Entry_17C660* entry = &((Entry_17C660*)self->buffer)[self->f40];
        if (entry->state == 0 && !CheckQueueEntryDone(self, entry))
            break;
        StartNextQueueEntry(self);
    }
    if (self->f48 && CheckQueueEntryDone(self, self->f48))
        self->f48 = 0;
}

ASM_FUNC(func_0017C718);

void func_0017C660(EntryQueue* self);

s32 func_0017CDA8(EntryQueue* self)
{
    AdvanceEntryQueue(self);
    if (self->f34 > 0) {
        return self->f40 < self->f34;
    }
    return 0;
}

void func_0017CE80(EntryQueue* self);

void func_0017CDE0(EntryQueue* self)
{
    if (self->f3C != 0) {
        UnbindEntryQueue(self);
        self->f34 = 0;
    } else {
        self->f34 = 0;
    }
    self->f40 = 0;
}

void func_001837E0(void* self, s32 kind, s32 a, s32 b);
s32 func_0016E0F0(s32 a);
void func_001DDA20(void* a);

struct Other_17CE20 {
    u8 pad[0x2740];
    void* f2740;
};

void func_0017CE20(void* a0, void* a1)
{
    EntryQueue* self = (EntryQueue*)a0;
    ((Other_17CE20*)a1)->f2740 = self;
    self->f3C = a1;
    self->f40 = -1;
    TriggerScriptEvent(self, 0x17, 0, 0);
    if (self->flag68 != 0) {
        SetPadSelectFlags(4);
        AcquirePadSelectFlag(self->world);
    }
}

struct Comp_17CE80 {
    u8 pad0[0x2740];
    s32 f2740;
};

void func_0017BC20(void* self, s32 n);
void func_0017BB78(void* self, s32 n);
void func_0012E760(void* p);
void func_00142ED0(f32 x);
void func_001837E0(void* self, s32 a, s32 b, s32 c);
void func_0016E118(s32 n);
void func_001DDA50(void* p);

void func_0017CE80(EntryQueue* self)
{
    if (self->f3C != 0) {
        ReplaceQueueOnOffObject(self, 0);
        func_0017BB78(self, 0);
        if (self->f50 != 0) {
            StopAnimationPlayer(self->f50);
            self->f50 = 0;
        }
        SetGameClockScale(1.0f);
        self->f40 = self->f34;
        self->f4C = 0;
        self->f48 = 0;
        ((Comp_17CE80*)self->f3C)->f2740 = 0;
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
void func_001F5C0C(void* p, s32 zero, s32 size);

void* func_0017CF38(EntryQueue* pool, s32 a, s32 b, s32 c)
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

void* func_0017CFC8(void* self, s32 b)
{
    return AddQueueEntry((EntryQueue*)self, 0, b, 1);
}

void* func_0017CFF0(void* self, s32 b)
{
    return AddQueueEntry((EntryQueue*)self, 1, b, 1);
}

void* func_0017D018(void* self, s32 b)
{
    return AddQueueEntry((EntryQueue*)self, 10, b, 1);
}

struct Obj_17D040 { u8 pad0[0xC]; union { s32 f0C; f32 f0Cf; }; };

void func_0017D040(void* self, s32 value)
{
    Obj_17D040* o = (Obj_17D040*)AddQueueEntry((EntryQueue*)self, 2, -1, 1);
    o->f0C = value;
}

void* func_0017D078(void* self, s32 value)
{
    return AddQueueEntry((EntryQueue*)self, 3, value, 1);
}

struct Obj_17D0A0 { u8 pad0[0xC]; f32 f0C; };

void func_0017D0A0(void* self, s32 a, f32 value)
{
    Obj_17D0A0* o = (Obj_17D0A0*)AddQueueEntry((EntryQueue*)self, 4, a, 0);
    o->f0C = value;
}

void* func_0017D0D8(void* self, s32 value, s32 c)
{
    return AddQueueEntry((EntryQueue*)self, 9, value, c);
}

struct Obj_17D100 {
    u8 pad0[0xC];
    s32 fC;
    s32 f10;
};

void func_0017D100(void* self, s32 b, s32 c, s32 d, s32 e)
{
    Obj_17D100* o = (Obj_17D100*)AddQueueEntry((EntryQueue*)self, 5, b, e);
    o->fC = c;
    o->f10 = d;
}

void func_0017D148(void* self, s32 a, s32 b, f32 value)
{
    Obj_17D040* o = (Obj_17D040*)AddQueueEntry((EntryQueue*)self, 6, a, b);
    o->f0Cf = value;
}

struct Obj_17D180 { u8 pad0[0xC]; f32 f0C; };

void func_0017D180(void* self, s32 b, s32 c, f32 value)
{
    Obj_17D180* o = (Obj_17D180*)AddQueueEntry((EntryQueue*)self, 7, b, c);
    o->f0C = value;
}

struct Obj_17D1B8 {
    u8 pad0[0xC];
    s32 fC;
};

void func_0017D1B8(void* self, s32 b, s32 c, s32 d)
{
    Obj_17D1B8* o = (Obj_17D1B8*)AddQueueEntry((EntryQueue*)self, 8, b, d);
    o->fC = c;
}

struct Obj_17D1E8 { u8 pad0[0xC]; f32 f0C; };

void func_0017D1E8(void* self, f32 value)
{
    Obj_17D1E8* o = (Obj_17D1E8*)AddQueueEntry((EntryQueue*)self, 11, -1, 1);
    o->f0C = value;
}

s32 func_0017D220(void* self)
{
    return (s32)AddQueueEntry((EntryQueue*)self, 0xC, -1, 0);
}
