// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "point_object.h"
#include "entry_queue.h"
#include "switched_collider.h"
#include "collider.h"
#include "globals.h"
#include "shapes.h"

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

struct Obj_17D040 { u8 pad0[0xC]; union { s32 f0C; f32 f0Cf; }; };
Obj_17D040* func_0017CF38(void* self, s32 a, s32 b, s32 c);

void func_0017D040(void* self, s32 value)
{
    Obj_17D040* o = AddQueueEntry(self, 2, -1, 1);
    o->f0C = value;
}

void func_0017D148(void* self, s32 a, s32 b, f32 value)
{
    Obj_17D040* o = AddQueueEntry(self, 6, a, b);
    o->f0Cf = value;
}

s32 func_0017D220(void* self)
{
    return (s32)AddQueueEntry(self, 0xC, -1, 0);
}

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

void* func_0017CFC8(void* self, s32 b)
{
    return AddQueueEntry(self, 0, b, 1);
}

void* func_0017CFF0(void* self, s32 b)
{
    return AddQueueEntry(self, 1, b, 1);
}

void* func_0017D018(void* self, s32 b)
{
    return AddQueueEntry(self, 10, b, 1);
}

void* func_0017D078(void* self, s32 value)
{
    return AddQueueEntry(self, 3, value, 1);
}

void* func_0017D0D8(void* self, s32 value, s32 c)
{
    return AddQueueEntry(self, 9, value, c);
}

struct Obj_17D100 {
    u8 pad0[0xC];
    s32 fC;
    s32 f10;
};

void func_0017D100(void* self, s32 b, s32 c, s32 d, s32 e)
{
    Obj_17D100* o = (Obj_17D100*)AddQueueEntry(self, 5, b, e);
    o->fC = c;
    o->f10 = d;
}

struct Obj_17D1B8 {
    u8 pad0[0xC];
    s32 fC;
};

void func_0017D1B8(void* self, s32 b, s32 c, s32 d)
{
    Obj_17D1B8* o = (Obj_17D1B8*)AddQueueEntry(self, 8, b, d);
    o->fC = c;
}

struct Obj_17D0A0 { u8 pad0[0xC]; f32 f0C; };

void func_0017D0A0(void* self, s32 a, f32 value)
{
    Obj_17D0A0* o = (Obj_17D0A0*)AddQueueEntry(self, 4, a, 0);
    o->f0C = value;
}

struct Obj_17D180 { u8 pad0[0xC]; f32 f0C; };

void func_0017D180(void* self, s32 b, s32 c, f32 value)
{
    Obj_17D180* o = (Obj_17D180*)AddQueueEntry(self, 7, b, c);
    o->f0C = value;
}

struct Obj_17D1E8 { u8 pad0[0xC]; f32 f0C; };

void func_0017D1E8(void* self, f32 value)
{
    Obj_17D1E8* o = (Obj_17D1E8*)AddQueueEntry(self, 11, -1, 1);
    o->f0C = value;
}

extern u8 D_002BE478[];
void func_001F5C0C(void* p, s32 zero, s32 size);

void* func_0017CF38(EntryQueue* pool, s32 a, s32 b, s32 c)
{
    if (pool->f34 >= 0x80) {
        return D_002BE478;
    }
    s32 n = pool->f34;
    u8* e = (u8*)pool->buffer + n * 0x14;
    pool->f34 = n + 1;
    func_001F5C0C(e, 0, 0x14);
    s32* f = (s32*)e;
    f[0] = a;
    f[1] = b;
    f[2] = c;
    return e;
}

struct Entry_17C660 { u8 pad[8]; s32 state; u8 tail[8]; };
void func_0017BCD0(EntryQueue* self);
s32 func_0017C428(EntryQueue* self, void* item);

void func_0017C660(EntryQueue* self)
{
    if (self->f40 < 0 && self->f34 > 0)
        func_0017BCD0(self);
    while (self->f40 < self->f34) {
        Entry_17C660* entry = &((Entry_17C660*)self->buffer)[self->f40];
        if (entry->state == 0 && !func_0017C428(self, entry))
            break;
        func_0017BCD0(self);
    }
    if (self->f48 && func_0017C428(self, self->f48))
        self->f48 = 0;
}
