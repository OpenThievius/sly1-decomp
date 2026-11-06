// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "switched_collider.h"
#include "state_trigger.h"
#include "child_group_object.h"
#include "screen_element.h"
#include "object_link.h"
#include "object_message.h"
#include "owner_message.h"
#include "output_buffer.h"
#include "shapes.h"
#include "globals.h"


extern f32 D_00261858[];

typedef void (*VFnA)(void* self);
typedef void (*VFnB)(void* self, void* arg);

struct Node_1D6CB0 {
    void** vtbl;
};


s32 func_00182FC8(void* node);

void func_001D6CB0(Player* self)
{
    C3F* obj = (C3F*)self->f1518;
    if (obj != 0) {
        Node_1D6CB0* s0 = 0;
        u32 i = 0;
        while (i < 4) {
            s0 = (Node_1D6CB0*)self->f1508[i];
            if (s0 != 0 && IsObjectAttached(s0) != 0) {
                break;
            }
            i++;
        }
        if (i >= 4) {
            s0 = (Node_1D6CB0*)self->f1504;
        }
        obj->desc->m02(obj);
        ((VFnB)((void**)obj->desc)[25])(obj, 0);
        ((VFnB)((void**)obj->desc)[35])(obj, s0);
        obj->f690 = g_gameClock[1];
        obj->f694 = 1;
        if (s0 != self->f1504) {
            ((VFnA)s0->vtbl[7])(s0);
        }
    }
}

s32 func_001B8A08(void* self, s32 value);

s32 func_001D6DA0(C3F* self, s32 value)
{
    if (value == (s32)g_player) {
        return 1;
    }
    return TestCollidersMayContact(self, value);
}


void func_001D7018(C3F* self)
{
    func_0013BA70(self);
    self->f694 = 0;
}

struct Node_1D7100 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
};

Node_1D7100* func_001D7100(Node_1D7100* self, s32 value)
{
    self->fC = value;
    self->f0 = 0;
    self->f4 = 0;
    self->f8 = 0;
    self->f10 = 0;
    self->f14 = 0;
    return self;
}

s32 func_001D65D8(Player* self)
{
    if (self->f2220 != 4) {
        return self->f26C4 != 0;
    }
    if (self->f2228 < 45) {
        return 1;
    }
    return 2;
}





struct Obj_001D7120 { s32 a; s32 b; s32 c; s32 d; s32 e; s32 f; };
Obj_001D7120* func_001D7120(Obj_001D7120* self, s32 a, s32 b) { self->a = a; self->b = b; self->c = 0; self->d = -1; self->e = 0; self->f = 0; return self; }







struct __attribute__((aligned(16))) Quad_1D73A8 { s32 a, b, c, d; };
f32 D_00275250[16] = {
    1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f
};
f32 D_00275290[4] = { 0.0f, 1.0f, 0.0f, 0.0f };

void func_001921A8(void* self);
void func_0018D800(void* dst, void* src, u32 size);
void func_001DB290(void* self);

void func_001D73A8(C19* self)
{
    InitSwitchedCollider(self);
    self->f614 = 50.0f;
    self->f610 = 50.0f;
    self->f618 = 3000.0f;
    self->f61C = 1300.0f;
    self->f868 = 2.0f;
    self->fB04 = 3;
    (*(Quad_1D73A8*)&self->v620) = *(Quad_1D73A8*)D_00275290;
    CopyMemory(self->f630, D_00275250, 0x40);
    ResetPathFollower(self);
}

void func_0013B708(C3F* self, s32 kind, ObjectMessage* ref);

void func_001D7040(C3F* self, s32 kind, ObjectMessage* ref)
{
    HandleChildGroupNotification(self, kind, ref);
    if (kind == 10 && ref->target == self) {
        ((C3F*)ref->target)->f694 = 0;
    }
}

void func_001F5C0C(OwnerMessage* p, s32 zero, s32 size);
void func_001D7098(OwnerMessage* self, s32 mode, s32 owner) { func_001F5C0C(self, 0, 0x10); self->owner = owner; self->mode = mode; self->c = owner; }

void func_001D72C8(OutputBuffer* a0, s32 a1);
void func_0018D778(OutputBuffer* a0);

void func_001D7148(OutputBuffer* a0, s32 a1)
{
    FlushOutputBuffer(a0, a1);
    if (a1 & 1) func_0018D778(a0);
}




extern const char D_0024DC90[4];

void func_0018D800(void* dst, void* src, s32 bytes);
s32 func_001F7B88(void* a, void* b);
void func_001F9028(s32 a, void* b, s32 n);

void func_001D72C8(OutputBuffer* self)
{
    u8 buf[0x90];
    s32 done;
    u8* p;
    s32 chunk;
    s32 rem;

    if (self->pending == 0) {
        return;
    }
    if (self->targetWord != 0) {
        return;
    }
    if (self->handle < 0) {
        p = self->buf;
        for (done = 0; done < self->pending; done += chunk) {
            rem = self->pending - done;
            chunk = 0x80;
            if (!(rem > 0x7F)) {
                chunk = rem;
            }
            CopyMemory(buf, p, chunk);
            p += chunk;
            buf[chunk] = 0;
            func_001F7B88((void*)D_0024DC90, buf);
        }
    } else {
        func_001F9028(self->handle, self->buf, self->pending);
    }
    self->pending = 0;
}

void func_0018D800(void* dst, void* src, s32 count);
void func_001D72C8(OutputBuffer* self);

s32 func_001D7190(OutputBuffer* self, void* src, s32 size)
{
    s32 n = size;
    s32 done = 0;

    if (self->target != 0 && self->capacity != 0 && n != 0) {
        s32 avail = self->capacity - self->used;
        if (avail < n) {
            n -= avail;
        }
    }
    if (n == 0) {
        return 0;
    }
    if (self->target != 0) {
        CopyMemory(self->target + self->used, src, n);
        self->used += n;
        done = n;
    } else if (n > 0) {
        do {
            s32 room = 0x400 - self->pending;
            s32 rem = n - done;
            s32 take = (room < rem) ? room : rem;
            if (take != 0) {
                CopyMemory((u8*)self + (self->pending + 0x18), (u8*)src + done, take);
                done += take;
                self->pending += take;
            }
            if (self->pending == 0x400) {
                FlushOutputBuffer(self);
            }
        } while (done < n);
    }
    self->count += done;
    return n;
}

ObjectLink D_002752A0[20] = {
    { 4, 0x416, 0x6B0 }, { 4, 0x417, 0x710 }, { 4, 0x418, 0x770 }, { 4, 0x419, 0x7D0 },
    { 0, 0x41A, 0x6B8 }, { 0, 0x41B, 0x718 }, { 0, 0x41C, 0x778 }, { 0, 0x41D, 0x7D8 },
    { 6, 0x41E, 0x6B4 }, { 6, 0x41F, 0x714 }, { 6, 0x420, 0x774 }, { 6, 0x421, 0x7D4 },
    { 0, 0x422, 0x690 }, { 2, 0x428, 0xB28 }, { 2, 0x429, 0xB2C }, { 2, 0x42A, 0xB44 },
    { 2, 0x42B, 0xB4C }, { 0x22, 0x423, 0xB14 }, { 0x20, 0x424, 0xB18 }, { 0x20, 0x425, 0xB1C }
};
struct Snd_1D7440 { s32 pad; };

struct __attribute__((aligned(16))) Quad_1D7440 { s32 a, b, c, d; };
struct Src_1D7440 { u8 pad[0x100]; Quad_1D7440 q; };
struct Slot_1D7440 {
    Src_1D7440* p;
    u8 pad4[0xC];
    Quad_1D7440 q;
    u8 pad20[0x40];
};
struct Vt_1D7440 { u8 pad[0x6C]; void (*fn6C)(void* o, void* arg); };
struct Ent_1D7440 { Vt_1D7440* vt; };

void func_00124A48(C19* self);
void func_00124DF8(C19* self, s32 n, void* table);
f32 func_00205778(f32 a, f32 b);
StateTrigger* func_001B6290(Snd_1D7440* a, C19* self, s32 b, s32 c);
void func_001B64D8(StateTrigger* a, s32 b);
void func_001BFCD8(s32 id, void* a1, C19* a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
f32 func_001EAAE0(f32 a, f32 b);
void* func_0015A418(World* host, s32 a1, s32 a2, C19* ctx);
s32 func_0015A198(World* host, s32 a1, s32 a2, s32 a3, s32 a4, Ent_1D7440** out);
void func_001DB290(C19* self);

void func_001D7440(C19* self)
{
    Ent_1D7440* buf[16];
    s32 id0;
    s32 id1;
    s32 id2;
    StartPlacedObject(self);
    ResolveObjectLinks(self, 0x14, D_002752A0);
    self->f694 = func_00205778(self->rot.r[0].y, self->rot.r[0].x);
    if (((Snd_1D7440*)self->fB44) != 0) {
        StateTrigger* v = CreateStateWalker(((Snd_1D7440*)self->fB44), self, -1, 0);
        self->fB48 = v;
        SetStateWalkerTarget(v, self->fB30 == 1 ? 0x484 : 0x384);
    }
    switch (g_currentWorld->f1D70) {
    case 3:
        id0 = self->f550 ? 0x1D2 : 0x1AD;
        id1 = 0x1BB;
        id2 = 0x1AF;
        goto spawn;
    case 5:
        id0 = self->f550 ? 0x2A6 : 0x280;
        id1 = 0x27F;
        id2 = 0x27D;
        goto spawn;
    case 6:
        id0 = self->f550 ? 0x2DE : 0x2DC;
        id1 = 0x2DB;
        id2 = 0x2DD;
    spawn:
        StartSoundEffect(id0, self->fB80, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        StartSoundEffect(id1, self->fB84, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        StartSoundEffect(id2, self->fB7C, self, 0, 6000.0f, 1000.0f, 1.0f, 0.0f, 0.5f, 0, 0);
        {
            f32 r = RandomFloatInRange(-0.1f, 0.1f);
            self->fB8C = self->fB90 = self->fB94 = self->fB98 = r;
        }
        break;
    default:
        break;
    }
    {
        void* c = FindFirstObjectById(g_currentWorld, 0x104, 7, self);
        if (c != 0) {
            self->f594 = 200.0f;
            self->fB78 = c;
            self->f598 = c;
        }
    }
    if (self->fB30 == 1) {
        s32 n = func_0015A198(self->world, 0x105, 0x426, 0, 0x10, buf);
        for (s32 i = 0; i < n; i++) {
            buf[i]->vt->fn6C(buf[i], self);
        }
        T217D_E30* boxA = &D_00272430;
        T217D_E30* boxB = &D_002726B0;
        ((U32P*)&boxA->own)->v = 0;
        ((U32P*)&boxB->own)->v = 0;
        boxA->target = &boxA->own;
        boxB->target = &boxB->own;
    }
    for (s32 k = 0; k < 4; k++) {
        Slot_1D7440* s = (Slot_1D7440*)&self->f6B0[k];
        s->q = s->p->q;
    }
    ResetPathFollower(self);
}

extern const char D_0024DC90[4] = "%s";
