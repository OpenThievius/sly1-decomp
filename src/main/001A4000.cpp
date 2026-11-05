// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "c05.h"
#include "paired_object.h"
#include "hit_target.h"
#include "sound_state_object.h"
#include "object_creator.h"
#include "list_iter.h"
#include "c8c.h"
#include "pair_controller.h"
#include "t217d.h"
#include "shapes.h"
#include "object_link.h"
#include "target_binding.h"
#include "g27c220.h"
#include "globals.h"

void func_001A76A0(void* child, int flag);

void func_001A5DD8(void* unused, PairedObject* obj)
{
    func_001A76A0(obj->attachment, 1);
}

void* func_001A6480(void* self)
{
    PairController* obj = (PairController*)self;
    return (u8*)self + (obj->poseIndex * 0xC0 + 0x3E0);
}

void func_001BAC30(void* self);
void func_00124DF8(void* self, int idx, void* table);
void func_00159478(void* sub, void* self);

void func_001A64F8(PairedObject* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 6, D_0026B7E8);
    func_00159478(&self->notifyRecord, self);
}

struct Blob8_1A6540 { u8 b[8]; };

void func_001BA130(void* self);

void func_001A6540(PairedObject* self)
{
    Blob8_1A6540 tmp = *(Blob8_1A6540*)&self->blob5B0;
    func_001BA130(self);
    *(Blob8_1A6540*)&self->blob5B0 = tmp;
}

typedef void (*Fn_1A6588)(void* self);

void func_00124A48(void* self);
void func_001A6BE0(PairedObject* self, int flag);

void func_001A6588(PairedObject* self)
{
    func_00124A48(self);
    func_001A6BE0(self, 0);
    Fn_1A6588* vt = *(Fn_1A6588**)self;
    vt[7](self);
}

struct Node_1A6F28 { void* flags; struct Node_1A6F28* next; s32 pad8; void* data; };

s32 func_001300E8(void* self, int kind);

void* func_001A6F28(u8* self)
{
    Node_1A6F28* cur = *(Node_1A6F28**)(*(u8**)(self + 0x480));
    while (cur) {
        if (cur->flags != 0 && func_001300E8(cur->data, 0x43) != 0)
            return cur->data;
        cur = cur->next;
    }
    return 0;
}

void func_001BAC30(void* self);
void func_00124DF8(void* self, int idx, void* table);
void func_00159478(void* sub, void* self);

void func_001A7008(HitTarget* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 1, D_0026B830);
    func_00159478(&self->notifyRecord, self);
}

struct Blob8_1A7050 { u8 b[8]; };

void func_001BA130(void* self);

void func_001A7050(HitTarget* self)
{
    Blob8_1A7050 tmp = *(Blob8_1A7050*)&self->blob5A0;
    func_001BA130(self);
    *(Blob8_1A7050*)&self->blob5A0 = tmp;
}

struct Blob8_1A7098 { u8 b[8]; };
typedef void (*Fn_1A7098)(void* self);

void func_00124A48(void* self);
void func_00124DF8(void* self, int idx, void* table);
void func_001A7480(void* self, int flag);
s32 func_001B6290(void* a, void* b, s32 c, s32 d);

void func_001A7098(HitTarget* self)
{
    func_00124A48(self);
    func_00124DF8(self, 1, D_0026B840);
    if (self->scaledObject != 0) {
        *(Blob8_1A7098*)&self->f57C = *(Blob8_1A7098*)((u8*)self->scaledObject + 0x2DC);
    }
    if (self->soundId != 0) {
        self->soundHandle = (void*)func_001B6290(self->soundId, self, -1, 0);
    }
    func_001A7480(self, 0);
    Fn_1A7098* vt = *(Fn_1A7098**)self;
    vt[7](self);
}

extern f32 D_00261860;
extern f32 D_0026B850[4];

void func_001B9338(void* self);
void func_00189378(void* sub, int zero, void* out);
void func_001B9D10(void* self, void* out, void* data, f32 scale);

void func_001A7230(HitTarget* self)
{
    func_001B9338(self);
    if (self->parent == 0) {
        u8 buf[0x30];
        func_00189378(&self->m110, 0, buf);
        func_001B9D10(self, buf, D_0026B850, D_00261860);
    }
}

struct Obj_1A7290 { u8 pad[0x98]; f32 a98; };

void func_001A7290(HitTarget* self, Obj_1A7290* obj)
{
    obj->a98 = obj->a98 * 0.6f;
}

void func_001A4868(u8* self, s32 value)
{
    *(s32*)(self + 0x2D8) = value;
}

typedef void (*VFn_1A7798)(void* self);

void func_00124A48(void* self);
void* func_0015A838(void* a, int b, int c, void* d);
void func_001A7998(ObjectCreator* self, int flag);

void func_001A7798(ObjectCreator* self)
{
    func_00124A48(self);
    if (self->createsObject == 0) {
        VFn_1A7798* vt = *(VFn_1A7798**)self;
        vt[7](self);
        return;
    }
    self->created = func_0015A838(self->world, 0x101, 0x59, self->children.head);
    func_001A7998(self, 0);
}

struct Vec_1A7D18 { s32 count; s32 pad; f32 x; };

int func_001A7EE8(void* a);
void func_001A7D98(void* self, int mode);

void func_001A7D18(void* self, Vec_1A7D18* p, f32 f)
{
    u8* s = (u8*)self;
    if (*(s32*)(s + 0xC) != 0 && p->count > 0) {
        if (func_001A7EE8((void*)D_002623C0) != 0) {
            *(f32*)(s + 0x18) = f;
            *(Vec_1A7D18**)(s + 0x10) = p;
            *(s32*)(s + 0x14) = 0;
            f32 x = p->x;
            *(s32*)(s + 0xC) = -1;
            *(f32*)(s + 0x1C) = x;
            func_001A7D98(self, 2);
        }
    }
}

struct Self_1A5F78 {
    u8 pad0[0x35C];
    u8 a35C[0xC];
    u8 a368[0xC];
    u8 a374[0xC];
    s32 a380;
    u8 a384[0xC];
    u8 a390[0xC];
    s32 a39C;
    u8 a3A0[0xC];
    u8 a3AC[0x14];
    u8 pad1[0x628 - 0x3C0];
    s32 a628;
    u8 pad2[0x638 - 0x62C];
    f32 a638;
    f32 a63C;
    f32 a640;
};

extern f32 D_0026185C[];

void func_00152600(void* a, void* b);
void func_00152470(void* a, void* b);
void func_001A76A0(void* child, s32 flag);
void func_001A5D50(void* self, void* obj);
s32 func_001A6238(void* self, void* child);
f32 func_001EAAE0(f32 a, f32 b);

void func_001A5F78(Self_1A5F78* self, PairedObject* obj)
{
    func_00152600(self->a384, obj);
    func_00152470(self->a390, obj);
    if (obj->attachment != 0) {
        func_00152600(self->a3AC, obj->attachment);
        func_00152470(self->a3A0, obj->attachment);
        func_001A76A0(obj->attachment, 0);
    }
    PairedObject* child = (PairedObject*)obj->partner;
    if (child != 0) {
        if (child->parent == obj) {
            func_001A5D50(self, obj);
        }
        func_00152600(self->a35C, child);
        func_00152470(self->a368, child);
        if (func_001A6238(self, child) == 0) {
            child->partner = 0;
        }
    }
    obj->attachment = 0;
    obj->partner = 0;
    obj->desc->m03(obj);
    if (self->a39C == self->a628) {
        f32 r = func_001EAAE0(self->a638, self->a63C);
        self->a640 = D_0026185C[0] + r;
    }
    self->a39C = self->a39C - 1;
}

void func_00152600(void* a, void* b);
void func_00152470(void* a, void* b);
s32 func_001A6238(void* self, void* child);
void func_001A6BE0(void* self, s32 mode);
s32 func_001A6090(void* self, void* child);

void func_001A6168(u8* self, PairedObject* obj, PairedObject* node)
{
    PairedObject* cur = (PairedObject*)obj->partner;
    if (cur != 0 && cur == node) {
        return;
    }
    PairedObject* s2 = (PairedObject*)node->partner;
    obj->partner = node;
    node->partner = obj;
    if (s2 == 0) {
        func_00152600(self + 0x368, node);
        func_00152470(self + 0x35C, node);
    }
    if (cur != 0) {
        func_00152600(self + 0x35C, cur);
        func_00152470(self + 0x368, cur);
        cur->partner = 0;
        func_001A6238(self, cur);
    }
    if (s2 != 0) {
        s2->partner = 0;
        func_001A6BE0(s2, 2);
        if (func_001A6090(self, s2) != 0) {
            func_001A6BE0(s2, 3);
        }
    }
}

void func_001B7968(void* self);

void func_001A7520(SoundStateObject* self)
{
    func_001B7968(self);
    self->state = -1;
}

s32 func_001A4258(C15* self)
{
    s32 r = self->f614;
    switch (r) {
    case 0:
        if (0.8f <= self->f624) {
            r = 1;
        }
        break;
    case 1:
        if (self->f624 < 0.8f) {
            r = 0;
        }
        break;
    }
    return r;
}

extern f32 D_00261860;
extern f32 D_0026B7D8[4];

void func_001B9338(C15* self);
void func_001892A0(f32* out, f32 unused, f32 value);
void func_001B9D10(C15* self, f32* buf, u8* table, f32 scale);

void func_001A44E8(C15* self)
{
    f32 buf[12];
    func_001B9338(self);
    func_001892A0(buf, self->f618, 0.0f);
    func_001B9D10(self, buf, D_0026B7D8, D_00261860);
}

void func_001A7D18(void* self, void* entry);
struct Entry_26B8B0 { s32 w[65]; };
extern Entry_26B8B0 D_0026B8B0[11];

void func_001A7CE8(void* self, s32 index)
{
    func_001A7D18(self, (u8*)D_0026B8B0 + index * 0x104);
}

s32 func_002049E8(void* owner, s32 channel, u8* bytes);

struct Pair_001A7E40 { u8 pad0[4]; void* owner; s32 channel; };

void func_001A7E40(Pair_001A7E40* self)
{
    u8 bytes[2];
    bytes[0] = 0;
    bytes[1] = 0;
    func_002049E8(self->owner, self->channel, bytes);
}

struct Obj_1A45B8 { u8 pad0[0x88]; f32 ratio; u8 pad1[8]; f32 value; };

s32 func_00128230(void* ctx);

void func_001A45B8(C15* ctx, Obj_1A45B8* obj)
{
    if (func_00128230(ctx) != 0) {
        return;
    }
    if (0.7f < obj->ratio) {
        obj->value = 20.0f;
    }
}

s32 func_001A4710(void)
{
    return 0;
}

void func_001A4858(PairController* obj, s32 value)
{
    obj->id2D0 = value;
}

void func_001A4860(PairController* obj, s32 value)
{
    obj->id2D4 = value;
}

s32 D_0026C3DC = 0;

void func_001A7E70(void)
{
    if (D_0026C3DC == 0) {
        D_0026C3DC = 1;
    }
}

extern s32 D_0026C3DC;

void func_001A7E90(G27C220* ctx)
{
    s32 v = D_0026C3DC;
    if (v == 2) {
        goto clear;
    }
    if (v < 3) {
        return;
    }
    if (v == 3) {
        goto set;
    }
    return;
clear:
    ctx->f19EC &= 0xFFFFFFDF;
    return;
set:
    ctx->f19EC |= 0x20;
}

extern s32 D_0026C3DC;

s32 func_001A7EE8(G27C220* ctx)
{
    s32 v = D_0026C3DC;
    if (v == 1) {
        goto tail;
    }
    if (v < 2) {
        if (v == 0) {
            goto zero;
        }
        goto tail;
    }
    if (v == 2) {
        goto one;
    }
    if (v == 3) {
        goto zero;
    }
    goto tail;
one:
    return 1;
zero:
    return 0;
tail:
    return ((ctx->f19EC >> 5) ^ 1) & 1;
}

void func_001A4870(PairController* obj, s32 value)
{
    obj->id2DC = value;
}

void func_001A4878(PairController* list, s32 value)
{
    s32 n = list->idCount;
    list->ids[n] = value;
    list->idCount = n + 1;
}

extern f32 D_00275C60[];

void func_00124A48(void* self);
s32 func_001A4898(void);
void func_001A5760(void* self, f32 t);
void func_001A4EF0(void* self, void* p);

void func_001A4B30(PairController* self)
{
    func_00124A48(self);
    if (self->id64C != func_001A4898()) {
        self->desc->m03(self);
    } else {
        BlendMotion* k = &self->kin;
        f32 dt = D_002623C8->dt;
        f32 v = k->pos + dt * (k->vel + dt * k->acc);
        f32 lo = D_00275C60[0];
        f32 hi = D_00275C60[1];
        f32 t;
        if (v < lo) {
            t = lo;
        } else if (hi < v) {
            t = hi;
        } else {
            t = v;
        }
        f32 u = 1.0f - t;
        f32* pa = self->poseA;
        f32* pb = self->poseB;
        f32* po = self->poseOut;
        for (u32 i = 0; i < 48; i++) {
            *po++ = u * *pa++ + t * *pb++;
        }
        func_001A5760(self, 0.0f);
        func_001A4EF0(self, 0);
    }
}


void* func_001E9970(void* zero);

void func_001A4D60(PairController* self)
{
    void* p = 0;
    if (self->state == 2) {
        p = func_001E9970(p);
    }
    if (p != 0) {
        D_0026D0C8.vt->m14(&D_0026D0C8);
    } else {
        D_0026D0C8.vt->m15(&D_0026D0C8);
    }
}

void func_00152600(void* table, void* node);
void func_00152470(void* table, void* node);
void func_001A76A0(void* node, s32 flag);

void func_001A5C38(u8* self, PairedObject* obj)
{
    func_00152600(self + 0x3AC, obj->attachment);
    func_00152470(self + 0x3A0, obj->attachment);
    func_001A76A0(obj->attachment, 0);
    obj->attachment = 0;
}


void func_001BAC30(void* self);
void func_00124DF8(void* self, int idx, void* table);

void func_001A7550(SoundStateObject* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 1, D_0026B888);
}

s32 func_001A7698(SoundStateObject* p) { return p->state; }

void func_001BA130(void* self);

void func_001A7588(SoundStateObject* self)
{
    PackedWord8 tmp;
    tmp = self->keptBytes;
    func_001BA130(self);
    self->keptBytes = tmp;
}

void func_00124A48(void* self);
s32 func_001300E8(void* node, s32 kind);
void func_001A76A0(void* node, s32 flag);

void func_001A75D0(SoundStateObject* self)
{
    ListFrame frame;
    func_00124A48(self);
    if (self->soundId != 0) {
        self->soundHandle = (void*)func_001B6290(self->soundId, self, -1, 1);
    }
    C01* n = (C01*)self->children.head;
    while (n != 0) {
        if (func_001300E8(n, 0x7E) != 0) {
            self->child7E = n;
            break;
        }
        n = n->next;
    }
    func_001A76A0(self, 0);
}

void func_001B93F8(void* self);
s32 func_001A7698(SoundStateObject* self);
void func_001A76A0(SoundStateObject* node, s32 flag);

void func_001A7648(SoundStateObject* self)
{
    func_001B93F8(self);
    s32 v;
    while ((v = func_001A7698(self)) != self->state) {
        func_001A76A0(self, v);
    }
}

void func_001B7968(C03* self);
void func_001B9AE0(C03* self, s32 a, s32 b, s32 c, s32 d);

void func_001A7708(ObjectCreator* self)
{
    func_001B7968(self);
    self->state = -1;
    func_001B9AE0(self, 3, 0, 3, 0);
}

f32 func_001EAAE0(f32 a, f32 b);
void func_001A5760(void* self, f32 t);
void func_00152600(u8* a, void* b);
void func_00152470(u8* a, void* b);
s32 func_001A6090(void* self, void* child);
void func_001A6BE0(void* self, s32 mode);

struct Self_1A5B28 {
    u8 pad0[0x35C];
    u8 a35C[0x368 - 0x35C];
    u8 a368[0x374 - 0x368];
    u8 a374[0x380 - 0x374];
    s32 i380;
    u8 pad1[0x3B8 - 0x384];
    s32 i3B8;
    u8 pad2[0x3C4 - 0x3BC];
    s32 i3C4;
    u8 pad3[0x624 - 0x3C8];
    s32 i624;
    u8 pad4[0x62C - 0x628];
    f32 f62C;
    f32 f630;
    f32 f634;
};

void func_001A5B28(Self_1A5B28* self, HitTarget* obj)
{
    s32 n = self->i3C4 + 1;
    f32 x = (f32)self->i3B8;
    self->i3C4 = n;
    func_001A5760(self, (f32)n / x);
    if (obj->partner != 0) {
        func_00152600(self->a35C, obj);
    } else {
        func_00152600(self->a368, obj);
    }
    func_00152470(self->a374, obj);
    if (obj->partner != 0) {
        if (func_001A6090(self, obj->partner) != 0) {
            func_001A6BE0(obj->partner, 3);
        } else {
            ((HitTarget*)obj->partner)->partner = 0;
            func_001A6BE0(obj->partner, 2);
        }
    }
    obj->partner = 0;
    obj->desc->m03(obj);
    if (self->i380 == self->i624) {
        f32 t = func_001EAAE0(self->f62C, self->f630);
        self->f634 = D_0026185C[0] + t;
    }
    self->i380 = self->i380 - 1;
}

f32 func_001EAAE0(f32 a, f32 b);
void func_001ED650(void* self, f32 x, f32 y, f32 z);

struct Self_1A63F8 { u8 pad[0x348]; f32 f348; f32 f34C; };

void func_001A63F8(Self_1A63F8* self, PairedObject* b)
{
    f32 r0 = func_001EAAE0(0.0f, 6.2831855f);
    f32 r1 = func_001EAAE0(0.0f, self->f348);
    func_001ED650((u8*)b + 0x570, r0, r1, 0.0f);
    b->f574 = b->f574 * self->f34C;
}

extern f32 D_00275C60[];

void func_001B93F8(void* self);
s32 func_001A7420(HitTarget* self);
void func_001A7480(HitTarget* self, int flag);
void func_00155FA0(void* x);
void func_00155F90(void* x);

void func_001A7128(HitTarget* self)
{
    func_001B93F8(self);
    s32 n;
    while ((n = func_001A7420(self)) != self->state) {
        func_001A7480(self, n);
    }
    void* sub = self->scaledObject;
    if (sub != 0) {
        f32 t = -self->v150.z;
        if (9.99999975e-05f < t) {
            func_00155FA0(sub);
            TimePolynomial* v = &self->scalePoly;
            f32 p = v->x + t * (v->y + t * v->z);
            f32 lo = D_00275C60[0];
            f32 hi = D_00275C60[1];
            f32 x;
            if (p < lo) {
                x = lo;
            } else if (hi < p) {
                x = hi;
            } else {
                x = p;
            }
            f32 a = self->f57C * x;
            f32 b = self->f580 * x;
            u8* o = (u8*)self->scaledObject;
            *(f32*)(o + 0x2DC) = a;
            *(f32*)(o + 0x2E0) = b;
        } else {
            func_00155F90(sub);
        }
    }
}

s32 func_001A7420(HitTarget* self)
{
    s32 v = self->state;
    if (v > 0) {
        if (v >= 9) {
            if (v == 9) {
                goto zero;
            }
            goto end;
        }
        f32 t = D_0026185C[0] - self->stateTime;
        if (self->recoverDelay < t) {
            v -= 1;
        }
        goto end;
    }
    goto end;
zero:
    v = 0;
end:
    return v;
}


void func_001BAC30(void* self);
void func_00124DF8(void* self, int idx, void* table);
void func_00159478(void* sub, void* self);

void func_001A7750(ObjectCreator* self)
{
    func_001BAC30(self);
    func_00124DF8(self, 1, D_0026B8A0);
    func_00159478(&self->notifyRecord, self);
}

struct Q_1A7AA0 { u8 pad[0x34]; f32 f34; };
struct P_1A7AA0 { u8 pad0[0x8]; Q_1A7AA0* q; u8 pad1[0x8]; f32 f14; };

s32 func_001A7AA0(ObjectCreator* self)
{
    s32 mode = self->state;
    s32 r = mode;
    P_1A7AA0* p;
    s32* g;
    s32 bits;
    if (mode == 1) {
        goto acc;
    }
    if (mode < 2) {
        goto out;
    }
    if (mode == 2) {
        goto flags;
    }
    goto out;
acc:
    p = (P_1A7AA0*)self->activeHandle;
    if (p == 0) {
        goto two;
    }
    if (!(p->q->f34 <= p->f14)) {
        goto flags;
    }
two:
    r = 2;
flags:
    g = *(s32**)&D_002623C8;
    bits = *g;
    r = (bits & 2) ? 3 : r;
out:
    return r;
}

void func_00192230(void* self, s32 code, void* rec);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_00155FA0(void* self);

struct Rec_1A43C8 { u8 pad[8]; s32 kind; };
void func_001A43C8(C15* self, s32 code, Rec_1A43C8* rec)
{
    func_00192230(self, code, rec);
    if (code == 5) {
        goto code5;
    }
    if (code != 0x13) {
        return;
    }
    if (rec->kind == 0x295) {
        goto kind295;
    }
    if (rec->kind == 0x296) {
        goto kind296;
    }
    return;
kind295:
    func_001BFCD8(0x152, 0, 0, (s32)((u8*)self + 0x140), 12000.0f, 8000.0f, 0.5f, 0.0f, 0.0f, 0, 0);
    func_00155FA0(self->f65C);
    return;
kind296:
    func_001BFCD8(0x152, 0, 0, (s32)((u8*)self + 0x140), 12000.0f, 8000.0f, 0.5f, 0.0f, 0.0f, 0, 0);
    func_00155FA0(self->f660);
    return;
code5:
    if (rec == self->f684) {
        self->f688 = 1;
    }
}

f32 func_001EAAE0(f32 a, f32 b);
void func_00152600(u8* a, void* b);
void func_00152470(u8* a, void* b);
void func_001A76A0(void* node, s32 flag);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

struct Self_1A5DF8 {
    u8 pad0[0x35C];
    u8 a35C[0x374 - 0x35C];
    u8 a374[0x380 - 0x374];
    s32 i380;
    u8 pad1[0x384 - 0x384];
    u8 a384[0x390 - 0x384];
    u8 a390[0x39C - 0x390];
    s32 i39C;
    u8 a3A0[0x3AC - 0x3A0];
    u8 a3AC[0x3C0 - 0x3AC];
    s32 i3C0;
    u8 pad2[0x624 - 0x3C4];
    s32 i624;
    s32 i628;
    f32 f62C;
    f32 f630;
    f32 f634;
    f32 f638;
    f32 f63C;
    f32 f640;
};

void func_001A5DF8(Self_1A5DF8* self, PairedObject* obj)
{
    self->i3C0 = self->i3C0 + 1;
    func_00152600(self->a35C, obj->partner);
    func_00152470(self->a374, obj->partner);
    func_00152600(self->a384, obj);
    func_00152470(self->a390, obj);
    func_00152600(self->a3AC, obj->attachment);
    func_00152470(self->a3A0, obj->attachment);
    {
        PairedObject* p = (PairedObject*)obj->partner;
        p->desc->m15(p, 0);
    }
    {
        PairedObject* q = (PairedObject*)obj->partner;
        q->desc->m03(q);
    }
    obj->desc->m03(obj);
    func_001A76A0(obj->attachment, 0);
    obj->attachment = 0;
    ((PairedObject*)obj->partner)->partner = 0;
    obj->partner = 0;
    if (self->i380 == self->i624) {
        f32 t = func_001EAAE0(self->f62C, self->f630);
        self->f634 = D_0026185C[0] + t;
    }
    self->i380 = self->i380 - 1;
    if (self->i39C == self->i628) {
        f32 t2 = func_001EAAE0(self->f638, self->f63C);
        self->f640 = D_0026185C[0] + t2;
    }
    self->i39C = self->i39C - 1;
    func_001BFCD8(0x51, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
}

struct __attribute__((aligned(16))) Quad_1A72B0 { s32 a; s32 b; f32 f; s32 d; };

struct Msg_1A72B0 {
    s32 kind;
    u8 pad[0xC];
    Quad_1A72B0 q10;
    Quad_1A72B0 q20;
    u8 pad2[0x20];
};

typedef void (*Fn_1A72B0)(void* self, void* msg);

void func_001A7480(HitTarget* self, int flag);
void func_001BFCD8(s32 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, void* a4, void* a5);

s32 func_001A72B0(HitTarget* self, u8* p)
{
    s32 st;

    if ((*(s32*)(p + 0xC) & 0x10) == 0) {
        goto done;
    }
    if (self->parent != 0) {
        goto done;
    }
    st = self->state;
    if (st == 9) {
        goto done;
    }
    if (D_0026185C[0] < self->stateTime + self->hitInterval) {
        goto done;
    }
    st += 1;
    if (st >= self->hitLimit) {
        func_001A7480(self, 9);
        void* obj = self->notifyRecord;
        if (obj != 0) {
            Msg_1A72B0 msg;
            msg.q10 = *(Quad_1A72B0*)(p + 0x30);
            f32 f = msg.q10.f + 1000.0f;
            msg.kind = 6;
            msg.q20 = *(Quad_1A72B0*)(p + 0x20);
            msg.q10.f = f;
            Fn_1A72B0* vt = *(Fn_1A72B0**)obj;
            vt[31](obj, &msg);
        }
        func_001BFCD8(0x23, 0, 0, p + 0x20, 12000.0f, 8000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    } else {
        func_001A7480(self, st);
        func_001BFCD8(0x14F, 0, 0, p + 0x20, 12000.0f, 8000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
done:
    return *(s32*)(p + 0xC) != 0;
}

s32 D_0026B898[2] = { 688, 689 };

void func_001B6628(void* a, s32 b);
void func_001B64D8(void* a, s32 b);

void func_001A76A0(SoundStateObject* self, s32 idx)
{
    s32 old = self->state;
    if (old == idx) return;
    self->state = idx;
    void* child = self->soundHandle;
    f32 d = D_0026185C[0];
    self->stateTime = d;
    if (child == 0) return;
    s32 v = D_0026B898[idx];
    if (old == -1) func_001B6628(child, v);
    else func_001B64D8(child, v);
}

struct Quad_1A7998 { s32 a, b, c, d; } __attribute__((aligned(16)));
struct Buf_1A7998 { s32 n; u8 pad[0x1C]; Quad_1A7998 q; u8 tail[0x20]; };
typedef void (*FnP_1A7998)(void* self, void* arg);
typedef void (*FnI_1A7998)(void* self, s32 arg);

void func_0012E760(void* p);
void func_0012C7B0(void* a, void* b, s32 c, void* d, f32 x, f32 y);

void func_001A7998(ObjectCreator* self, s32 idx)
{
    if (self->state != idx) {
        if (self->activeHandle != 0) {
            func_0012E760(self->activeHandle);
            self->activeHandle = 0;
        }
        self->state = idx;
        void* s2 = 0;
        self->stateTime = D_0026185C[0];
        switch (idx) {
        case 1: {
            void* a2 = self->notifyRecord;
            s2 = self->f560;
            if (a2 != 0) {
                Buf_1A7998 buf;
                buf.n = 4;
                buf.q = *(Quad_1A7998*)&self->v140;
                FnP_1A7998* vt = *(FnP_1A7998**)a2;
                vt[31](a2, &buf);
            }
            break;
        }
        case 2: {
            void* a = self->created;
            ((FnI_1A7998*)*(void**)a)[25](a, 0);
            a = self->created;
            ((FnI_1A7998*)*(void**)a)[51](a, 1);
            break;
        }
        }
        if (s2 != 0) func_0012C7B0(s2, self, 0, &self->activeHandle, 0.0f, 1.0f);
    }
}

void func_001B6628(void* p, s32 a);
void func_001B64D8(void* p, s32 a);
void func_001BF788(void* p, s32 flag);
void func_001BFCD8(s32 a0, void* a1, void* a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

void func_001A42C8(C15* self, s32 state)
{
    s32 old = self->f614;
    if (old == state) {
        return;
    }
    self->f614 = state;
    s32 a2;
    s32 s1;
    switch (state) {
    case 0:
        a2 = 0x293;
        s1 = -1;
        break;
    case 1:
        a2 = 0x294;
        s1 = 0x150;
        break;
    }
    if (self->f654 != 0) {
        if (old == -1) {
            func_001B6628(self->f654, a2);
        } else {
            func_001B64D8(self->f654, a2);
        }
    }
    s32 cur = -1;
    if (self->f658 != 0) {
        cur = *(s32*)self->f658;
        if (s1 == cur) {
            return;
        }
        func_001BF788(self->f658, 0);
        self->f658 = 0;
        cur = -1;
    }
    if (s1 == cur) {
        return;
    }
    f32 zero = 0.0f;
    func_001BFCD8(s1, &self->f658, self, 0, 10000.0f, 6000.0f, 1.0f, zero, zero, 0, 0);
}

void func_001A7D98(void* self, s32 mode);

struct Track_001A7B20 { u8 pad0[4]; s32 value4; s32 value8; s32 state; };

void func_001A7B20(Track_001A7B20* self, s32 a1, s32 a2)
{
    if (self->state == 0) {
        func_001A7D98(self, 1);
    } else {
        func_001A7D98(self, 3);
    }
    self->value4 = a1;
    self->value8 = a2;
}

extern void* D_0026B860[10];

void func_001A5B28(void* a, void* b);
void func_001B6628(void* self, void* item);
void func_001B64D8(void* self, void* item);

void func_001A7480(HitTarget* self, s32 value)
{
    s32 old = self->state;
    if (value == old) {
        return;
    }
    if (old == 9) {
        func_001A5B28(self->controller, self);
    }
    self->state = value;
    self->stateTime = D_0026185C[0];
    void* a2 = self->soundHandle;
    if (a2 != 0) {
        void* item = D_0026B860[value];
        if (old == -1) {
            func_001B6628(a2, item);
        } else {
            func_001B64D8(a2, item);
        }
    }
}

s32 func_001300E8(void* node, s32 kind);
void func_001BC828(void* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_001A4610(C15* self, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5)
{
    Vec02 s0;
    Vec02 s1;
    s32 n = *(s32*)(a2 + ((1 - a3) << 6));
    s0 = self->v440;
    s1 = self->q450;
    if (n != 0) {
        if (func_001300E8((void*)n, 0x43) || func_001300E8((void*)n, 0x42)) {
            self->mode450 = 1;
            self->v440 = D_00248D20;
        }
    }
    func_001BC828(self, a1, a2, a3, a4, a5);
    self->v440 = s0;
    self->q450 = s1;
}

struct Frame_1A54F8;

struct Frame_1A54F8 {
    List01* iter;
    void* cursor;
    s32 link;
    Frame_1A54F8* prev;
    Frame_1A54F8(List01* i)
    {
        iter = i;
        cursor = i;
        link = i->offset;
        prev = (Frame_1A54F8*)D_0027B314;
        D_0027B314 = (ListFrame*)this;
    }
    ~Frame_1A54F8() { D_0027B314 = (ListFrame*)prev; }
    void* Next()
    {
        void* n = *(void**)cursor;
        cursor = (u8*)n + link;
        return n;
    }
};

struct Node_1A54F8 {
    void** vtbl;
};

s32 func_001527D8(List01* list);
void func_00152600(void* list, void* item);
void func_00152470(void* list, void* item);
s32 func_001EAA70(s32 a, s32 b);
f32 func_001EAAE0(f32 a, f32 b);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void func_001A6BE0(void* self, s32 mode);
void func_001A76A0(void* node, s32 flag);
extern f32 D_00261858[];

void func_001A54F8(PairController* self)
{
    if (*(s32*)(self->list390 + 0xC) >= self->f628) {
        self->f640 = 3.4028234663852886e+38f;
    } else {
        Node_1A54F8* owner = *(Node_1A54F8**)(self->list390);
        s32 count = func_001527D8((List01*)self->list3A0);
        if (count != 0) {
            Frame_1A54F8 w((List01*)self->list3A0);
            u8* node;
            s32 r = func_001EAA70(0, count - 1);
            s32 j = r;
            j--;
            if (r >= 0) {
                do {
                    node = (u8*)w.Next();
                } while (j-- >= 0);
            }
            func_00152600(self->list3A0, node);
            func_00152470(self->list3AC, node);
            func_00152600(self->list390, owner);
            func_00152470(self->list384, owner);
            *(void**)((u8*)owner + 0x560) = node;
            (*(s32*)(self->list390 + 0xC))++;
            ((void (*)(void*))owner->vtbl[0x18 / 4])(owner);
            ((void (*)(void*, void*))owner->vtbl[0x84 / 4])(owner, node + 0x140);
            ((void (*)(void*, void*))owner->vtbl[0x88 / 4])(owner, node + 0x110);
            func_001A6BE0(owner, 1);
            func_001A76A0(*(void**)((u8*)owner + 0x560), 1);
            *(f32*)((u8*)owner + 0x564) = self->f644;
            *(f32*)((u8*)owner + 0x568) = self->f648;
            f32* fp = &self->f638;
            self->f640 = D_00261858[1] + func_001EAAE0(self->f638, fp[1]);
            func_001BFCD8(-1, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            func_001BFCD8(0x14E, 0, (s32)node, 0, 12000.0f, 5000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
    }
}

s32 func_001A4898(void)
{
    s32 flags = D_002623C8->flags;
    if ((flags & 4) == 0) {
        s32 bit = flags & 2;
        return bit != 0;
    }
    return 2;
}


enum Kind_1A5C90 { };

void func_001B9AE0(C03* self, s32 a, s32 b, s32 c, s32 d);
void func_001BFCD8(Kind_1A5C90 a0, void* a1, s32 a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

void func_001A5C90(void* a0, void* a1)
{
    PairedObject* s = (PairedObject*)a1;
    ((C03*)s->partner)->desc->m15((C03*)s->partner, (C01*)a1);
    s = (PairedObject*)a1;
    ((C03*)s->partner)->desc02()->m20((C03*)s->partner, (Vec02*)&D_00248D30);
    s = (PairedObject*)a1;
    ((C03*)s->partner)->desc02()->m21((C03*)s->partner, (Vec02*)&D_00248D30);
    func_001B9AE0((C03*)((PairedObject*)a1)->partner, 3, 0, 3, 0);
    func_001BFCD8((Kind_1A5C90)0x151, (void*)0, 0, (void*)0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
}


struct Ctx_1A5D50 { u8 bytes[4]; };

void func_001B9AE0(C03* self, s32 a, void* b, s32 c, s32 d);

void func_001A5D50(Ctx_1A5D50* unused, PairedObject* h)
{
    C03* o = (C03*)h->partner;

    (void)unused;
    o->desc->m15(o, 0);
    o->desc02()->m20(o, (Vec02*)&D_00248D30);
    o->desc02()->m21(o, (Vec02*)&D_00248D30);
    func_001B9AE0(o, 2, (void*)&D_00248D20, 3, 0);
}

void func_001B7968(C03* self);
void func_001B9AE0(C03* self, s32 a, void* b, s32 c, void* d);

void func_001A6498(PairedObject* self)
{
    func_001B7968(self);
    self->state = -1;
    self->f584 = 1.0f;
    self->f588 = 2.5f;
    func_001B9AE0(self, 1, (void*)&D_00248D20, 2, (void*)&D_00248D20);
}

// Matched: float stores in retail's order with constants loaded as locals; int stores 0x2D0..0x2DC, 0x64C, 0x650 in that order.

struct __attribute__((aligned(16))) Table_1A4718 {
    AlignedQuad q[12];
};

extern const Table_1A4718 D_0024C9D0;
extern AlignedQuad D_00275C50;

void func_00123ED0(PairController* self);
void func_00152438(void* self, s32 value);
void func_0018D800(void* dst, void* src, s32 count);

void func_001A4718(PairController* self)
{
    Table_1A4718 tmp;

    func_00123ED0(self);
    func_00152438(self->list35C, 0x5A0);
    func_00152438(self->list368, 0x5A0);
    func_00152438(self->list374, 0x5A0);
    func_00152438(self->list384, 0x5B0);
    func_00152438(self->list390, 0x5B0);
    func_00152438(self->list3A0, 0x568);
    func_00152438(self->list3AC, 0x568);
    self->id2D0 = -1;
    self->id2D4 = -1;
    self->id2D8 = -1;
    self->id2DC = -1;
    self->id64C = -1;
    self->state = -1;
    self->limit3B8 = 0x28;
    tmp = D_0024C9D0;
    func_0018D800(self->poseA, &tmp, 0xC0);
    func_0018D800(self->poseB, &tmp, 0xC0);
    self->q3D0 = D_00275C50;
    f32 k2300 = 2300.0f;
    f32 k1500 = 1500.0f;
    f32 k146 = 1.46f;
    f32 k3000 = 3000.0f;
    self->tune350 = k3000;
    self->tune348 = k2300;
    self->tune344 = k1500;
    self->tune34C = k146;
    self->mode340 = 0;
}

enum Kind_1A4070 { K_1A4070_0 };

void func_001F4408(C15* a, s32 n);
void func_00155F90(void* p);
void func_00155FA0(void* p);
void func_001B6628(void* p, s32 n);
void func_001B64D8(void* p, s32 n);
void func_0012C7B0(void* a, C15* self, s32 c, s32* out, f32 fa, f32 fb);
void func_001BF788(s32* p, s32 n);

void func_001A4070(C15* self, s32 n)
{
    s32 old = self->f610;
    if (old == n) return;
    void* h = 0;
    self->f610 = n;
    s32 snd = -1;
    s32 flag = 0;
    s32 kind = 0x14D;
    switch (n) {
    case 0:
        snd = 0x28F;
        flag = 1;
        kind = -1;
        break;
    case 1:
        snd = 0x290;
        break;
    case 2:
        snd = 0x290;
        h = self->f680;
        break;
    case 3:
        snd = 0x290;
        h = self->f67C;
        func_001F4408(0, 1);
        break;
    }
    for (s32 i = 0; i < self->f668; i++) {
        if (flag) func_00155F90(((void**)self->f66C)[i]);
        else func_00155FA0(((void**)self->f66C)[i]);
    }
    if (self->f644) {
        if (old == -1) func_001B6628(self->f644, snd);
        else func_001B64D8(self->f644, snd);
    }
    if (h) {
        func_0012C7B0(h, self, 1, (s32*)&self->f684, 0.0f, 1.0f);
    }
    if (self->f648) {
        if (kind == *self->f648) return;
        func_001BF788(self->f648, 0);
        self->f648 = 0;
    }
    if (kind != -1) {
        func_001BFCD8((s32)(Kind_1A4070)kind, (void*)&self->f648, (void*)self, 0, 10000.0f, 6000.0f, 0.5f, 0.0f, 0.0f, 0, 0);
    }
}


void func_001B7968(C03* self);
void func_001B9AE0(C03* self, s32 a, void* b, s32 c, s32 d);
void func_001A6F88(HitTarget* self)
{
    s32* z;
    func_001B7968(self);
    func_001B9AE0(self, 2, (void*)&D_00248D20, 3, 0);
    f32 one = 1.0f;
    f32 pt2 = 0.2f;
    z = (s32*)&self->scalePoly;
self->recoverDelay = one;
self->scalePoly.x = one;
self->hitLimit = 8;
self->state = -1;
self->hitInterval = pt2;
z[1]=0;z[2]=0;
}

void func_001A7F50(G27C220* self)
{
    s32 g = D_0026C3DC;
    switch (g) {
    case 1: self->f19EC = self->f19EC ^ 0x20; break;
    case 2: self->f19EC = self->f19EC | 0x20; break;
    case 3: self->f19EC = self->f19EC & 0xFFFFFFDF; break;
    }
    if (self->f19EC & 0x20) {
        D_0026C3DC = 3;
        return;
    }
    D_0026C3DC = 2;
}

extern f32 D_0024CBC4;

void func_00182C18(C8C* self);
struct Buf_1A7FE8 { u8 b[1]; };
s32 func_001F5C0C(Buf_1A7FE8* p, s32 zero, s32 size);
void func_001DBCC8(void* owner, void* fn, void* arg, s32 a3, s32 a4);
void func_001A8208(C8C* self);

void func_001A7FE8(C8C* self)
{
    func_00182C18(self);
    u8* s1 = (u8*)self + 0x60;
    self->id4C = -1;
    self->id50 = -1;
    self->id54 = -1;
    self->id58 = -1;
    (void)func_001F5C0C((Buf_1A7FE8*)s1, 0, 0x80);
    const Quad16* src = (const Quad16*)&D_002483D0;
    *(Quad16*)(s1 + 0x20) = src[0];
    *(Quad16*)(s1 + 0x30) = src[1];
    *(Quad16*)(s1 + 0x40) = src[2];
    (void)func_001F5C0C((Buf_1A7FE8*)((u8*)self + 0xE0), 0, 0x70);
    V8C* p = &self->v110;
    p->a = 0;
    p->b = 1.0f;
    p->c = 0;
    self->f120 = 0;
    self->f124 = 20000.0f;
    (void)func_001F5C0C((Buf_1A7FE8*)((u8*)self + 0x150), 0, 0x18);
    f32 d = D_0024CBC4;
    self->fD8 = 5.0f;
    self->f168 = 0;
    self->f144 = d;
    func_001DBCC8(self->world, (void*)func_001A8208, self, 0, 0);
}

struct LinkedObject { u8 pad0[0x2D4]; s32 f2D4; };
extern f32 D_00261858[];
void func_00124FC0(PairController* self);
s32 func_001A4DC0(PairController* self);
void func_001A4EF0(PairController* self, s32 mode);
void func_001A5120(PairController* self);
void func_001A54F8(PairController* self);
void func_001A7998(ObjectCreator* t, s32 flag);

void func_001A4C48(PairController* self)
{
    ObjectCreator* t;
    s32 st;
    func_00124FC0(self);
    while ((st = func_001A4DC0(self)) != self->state) {
        func_001A4EF0(self, st);
    }
    switch (st) {
    case 0:
    case 1:
    case 3:
    case 4:
    case 6:
        break;
    case 2:
        if (self->count3BC < self->limit3B8) {
            if (self->f634 < D_00261858[1]) {
                func_001A5120(self);
            }
        }
        if (self->f640 < D_00261858[1]) {
            func_001A54F8(self);
        }
        break;
    case 5: {
        t = self->target;
        if (t) {
            if (t->state == 0) {
                LinkedObject* s = self->link;
                if (s == 0 || s->f2D4 != 3) {
                    func_001A7998(t, 1);
                }
            }
        }
        break;
    }
    }
}

struct Par_1A4DC0 { u8 pad[0x610]; u32 f610; };

s32 func_001A4DC0(PairController* self)
{
    u32 s = self->state;
    switch (s) {
    case 0:
        { u32 one = 1;
        if (((Par_1A4DC0*)self->f354)->f610 <= one) s = one; }
        break;
    case 1:
        if (!self->link || self->link->f2D4 != 3) s = 2;
        break;
    case 2:
        if (self->f3C0) { s = 3; break; }
        if (self->f3C4 == self->limit3B8) s = 5;
        break;
    case 3:
        if (self->link->f2D4 != 3) s = 4;
        break;
    case 5:
        if (self->target) {
            if (self->target->state == 3 && self->target->stateTime + 3.0f < D_0026185C[0]) s = 6;
        } else if (self->f654 + 5.0f < D_0026185C[0]) {
            if (!self->link || self->link->f2D4 != 3) s = 6;
        }
        break;
    case 4:
    case 6:
        break;
    }
    return s;
}

struct __attribute__((aligned(16))) Vec_1A6DE0 { f32 x, y, z, w; };
struct Msg_1A6DE0 {
    s32 kind;
    u8 pad4[0xC];
    Vec_1A6DE0 a;
    Vec_1A6DE0 b;
    Vec_1A6DE0 c;
    Vec_1A6DE0 d;
};
struct Ev_1A6DE0 {
    u8 pad0[0xC];
    u32 flags;
    u8 pad10[0x10];
    Vec_1A6DE0 b;
    Vec_1A6DE0 a;
};
enum Id_1A6DE0 { id_1A6DE0_37 = 0x37 };

extern void func_001A6BE0(PairedObject* o, s32 n);
extern void func_001BFCD8(Id_1A6DE0 id, s32 a1, s32 a2, Vec_1A6DE0* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

s32 func_001A6DE0(PairedObject* o, Ev_1A6DE0* ev) {
    if (ev->flags & 0x20) {
        switch (o->state) {
        case 1: case 2: case 3: case 4: case 5: case 7: case 8:
            func_001A6BE0(o, 9);
            break;
        case 6: {
            HitTarget* c = (HitTarget*)o->partner;
            func_001A6BE0(o, 9);
            if (c) func_001A7480(c, 9);
            break;
        }
        }
        if (o->state == 9) {
            HitTarget* t = (HitTarget*)o->notifyRecord;
            if (t) {
                Msg_1A6DE0 m;
                m.kind = 6;
                m.a = ev->a;
                m.b = ev->b;
                m.a.z += 3000.0f;
                t->desc->m1B(t, &m);
            }
            func_001BFCD8(id_1A6DE0_37, 0, 0, &ev->b, 12000.0f, 8000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
    }
    return ev->flags != 0;
}

struct Src_1A7D98 { u8 pad[4]; u8 b4; u8 b5; };
struct Obj_1A7D98 {
    u8 pad0[4];
    void* owner;
    s32 channel;
    s32 state;
    Src_1A7D98* src;
    u8 pad1[8];
    f32 f1C;
};

s32 func_002049E8(void* owner, s32 channel, u8* bytes);
void func_001A7E40(Obj_1A7D98* self);
extern f32 D_0026186C;

void func_001A7D98(Obj_1A7D98* self, s32 state)
{
    u8 bytes[2];
    if (state == self->state) return;
    switch (state) {
    case 2:
        bytes[0] = self->src->b4;
        bytes[1] = self->src->b5;
        func_002049E8(self->owner, self->channel, bytes);
        self->state = state;
        return;
    case 3:
    case 4:
        func_001A7E40(self);
        self->f1C = D_0026186C * 4.0f;
        break;
    case 0:
    case 1:
        break;
    }
    self->state = state;
}

struct Link_1A4EF0 { u8 pad[0x18]; PairController* f18; };

extern u8 D_00275BC0[];
extern u8 D_00261EF0[];

s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
void func_001E9498(u8* a, u8* b);
void func_001DDC38(void* host, PairController* self);
void func_001A6BE0(PairController* o, s32 n);
void func_001A4070(void* a, s32 n);
void func_00151E20(u8* a, f32 b);
void func_00151FC8(u8* a);
void func_00194D30(u8* a, s32 b, s32 c);

#define F(o, off) (*(f32*)((u8*)(o) + (off)))
#define W(o, off) (*(s32*)((u8*)(o) + (off)))
#define P(o, off) (*(void**)((u8*)(o) + (off)))
#define O(o, off) (*(PairController**)((u8*)(o) + (off)))

void func_001A4EF0(PairController* self, s32 state)
{
    PairController* o;
    s32 v;
    ListFrame frame;
    if (W(self, 0x650) == state) return;
    W(self, 0x650) = state;
    F(self, 0x654) = D_0026185C[0];
    W(self, 0x658) = 0;
    switch (state) {
    case 0:
        break;
    case 1: {
        if (W(self, 0x64C) < 3) {
            if (W(self, 0x64C) >= 0) {
                if (D_002623C8->f14) {
                    W(self, 0x658) = 0;
                } else {
                    W(self, 0x658) = func_0015A418(self->world, 0x105, 0x33B, 0);
                }
            }
        }
        s32 w = W(self, 0x658);
        if (w) {
            T217D_440* box = &D_002701F8;
            ((U32P*)&box->child)->v = w;
            func_001E9498(D_00275BC0, (u8*)box);
        }
        break;
    }
    case 2: {
        D_0026D0C8.target = &self->f3C4;
        D_0026D0C8.limit = &self->limit3B8;
        func_001DDC38(self->world, self);
        break;
    }
    case 5:
        v = func_0015A418(self->world, 0x105, 0x33D, 0);
        W(self, 0x658) = v;
        if (v) {
            D_002701F8.child = (void*)v;
            func_001E9498(D_00275BC0, (u8*)&D_002701F8);
        }
        for (o = O(self, 0x384); o; o = O(o, 0x5B0)) func_001A6BE0(o, 8);
        func_00151FC8(D_00261EF0);
        break;
    case 3:
        v = func_0015A418(self->world, 0x105, 0x33E, 0);
        W(self, 0x658) = v;
        if (v) {
            D_002701F8.child = (void*)v;
            func_001E9498(D_00275BC0, (u8*)&D_002701F8);
        }
        for (o = O(self, 0x384); o; o = O(o, 0x5B0)) {
            Link_1A4EF0* l = (Link_1A4EF0*)P(o, 0x55C);
            if (l == 0 || l->f18 != o) func_001A6BE0(o, 7);
        }
        func_00151E20(D_00261EF0, 1.0f);
        break;
    case 4:
        func_00194D30((u8*)&D_0026FF68, 0, 0x1A);
        break;
    case 6:
        func_001A4070(P(self, 0x354), 3);
        D_0026EC70.vt->m15(&D_0026EC70);
        break;
    }
}

void func_0012E760(PairedObject* o);
void func_001B6438(PairedObject* o);
void func_001A5C38(void* p, PairedObject* o);
void func_001A5DD8(void* p, PairedObject* o);
void func_001A5DF8(void* p, PairedObject* o);
void func_001A5F78(void* p, PairedObject* o);
void func_001A5C90(void* p, PairedObject* o);
void func_0012C288(f32 a, f32 b, void* h, PairedObject* o, s32 n, TargetBinding* buf, s32 e, void** out);
void* func_001B6290(void* a, PairedObject* o, s32 c, s32 d);

void func_001A6BE0(PairedObject* self, s32 mode)
{
    TargetBinding buf[2];
    TargetBinding* w;
    void* h;
    void* s3;

    if (self->state == mode) return;
    if (self->activeHandle) {
        func_0012E760((PairedObject*)self->activeHandle);
        self->activeHandle = 0;
    }
    if (self->soundHandle) {
        func_001B6438((PairedObject*)self->soundHandle);
        self->soundHandle = 0;
    }
    switch (self->state) {
    case 1:
        func_001A5C38(self->controller, self);
        break;
    case 5:
        if (mode == 6) func_001A5DD8(self->controller, self);
        break;
    case 6:
        if (mode == 0) func_001A5DF8(self->controller, self);
        break;
    case 9:
        func_001A5F78(self->controller, self);
        break;
    default:
        break;
    }
    self->state = mode;
    h = 0;
    s3 = 0;
    self->stateTime = D_0026185C[0];
    w = buf;
    switch (mode) {
    case 0: case 10:
        break;
    case 1: case 2: case 3:
        h = self->f58C;
        break;
    case 4:
        func_001A5C90(self->controller, self);
        w->key = 0x2A0; w->object = self->partner; w++;
        h = self->f594;
        break;
    case 5: case 6:
        w->key = 0x2A0; w->object = self->partner; w++;
        h = self->f590;
        break;
    case 7:
        s3 = self->f5A0;
        break;
    case 8:
        s3 = self->f5A4;
        break;
    case 9:
        h = self->f598;
        break;
    }
    if (h) func_0012C288(0.0f, 1.0f, h, self, w - buf, buf, 1, &self->activeHandle);
    if (s3) self->soundHandle = func_001B6290(s3, self, -1, 1);
}

extern f32 D_00261858[];

struct Entry_1A7B88 { s32 f0; u8 b[2]; u8 pad[2]; f32 delay; };
struct Table_1A7B88 { s32 count; Entry_1A7B88 entries[1]; };
struct Obj_1A7B88 { u8 pad0[0x4]; void* owner; s32 channel; s32 state; Table_1A7B88* table; s32 index; f32 f18; f32 f1C; };

void func_001A7D98(void* self, s32 mode);
void func_001A7E40(Obj_1A7B88* self);
s32 func_002049E8(void* owner, s32 channel, u8* bytes);

void func_001A7B88(Obj_1A7B88* s)
{
    f32 dt = D_00261858[5];
    switch (s->state) {
    case 2:
        if (*(s32*)D_00261858 != 0 && s->f18 > 0.0f) {
            s->f1C -= dt;
            if (s->f1C <= 0.0f) {
                s->index++;
                if (s->index >= s->table->count) {
                    s->index = 0;
                }
                u8 bytes[2];
                Entry_1A7B88* e = (Entry_1A7B88*)((u8*)s->table + (s->index << 3));
                bytes[0] = e->b[0];
                bytes[1] = e->b[1];
                func_002049E8(s->owner, s->channel, bytes);
                s->f1C = ((Entry_1A7B88*)((u8*)s->table + (s->index << 3)))->delay;
            }
            s->f18 -= dt;
        } else {
            func_001A7D98(s, 3);
        }
        break;
    case 3:
    case 4:
        if (s->f1C > 0.0f) {
            func_001A7E40(s);
            s->f1C -= dt;
        } else {
            func_001A7D98(s, s->state == 3);
        }
        break;
    }
}

#define F(o) (*(f32*)((u8*)self + (o)))
#define I(o) (*(s32*)((u8*)self + (o)))

struct Poly_1A5760 { f32 a, b, c; };
struct Range_1A5760 { f32 lo, hi; };
f32 func_001EAAE0(f32 a, f32 b);

struct Curve_1A5760 {
    static f32 Eval(const Poly_1A5760* p, f32 t)
    {
        return p->a + t * (p->b + t * p->c);
    }
    static void Clamp(f32& c, f32 v, const Range_1A5760* r)
    {
        f32 lo = r->lo;
        f32 hi = r->hi;
        if (v < lo) {
            c = lo;
        } else if (hi < v) {
            c = hi;
        } else {
            c = v;
        }
    }
    static void Get(f32& c, const Poly_1A5760* p, f32 t)
    {
        Clamp(c, Eval(p, t), ((Range_1A5760*)&D_00275C60));
    }
};

#define P(o) ((const Poly_1A5760*)((u8*)self + (o)))

void func_001A5760(PairController* self, f32 dt)
{
    f32 t0;
    Curve_1A5760::Get(t0, P(0x5B0), dt);
    F(0x62C) = (1.0f - t0) * F(0x5A0) + t0 * F(0x5A8);
    F(0x630) = (1.0f - t0) * F(0x5A4) + t0 * F(0x5AC);

    f32 t1;
    Curve_1A5760::Get(t1, P(0x5D0), dt);
    F(0x638) = (1.0f - t1) * F(0x5C0) + t1 * F(0x5C8);
    F(0x63C) = (1.0f - t1) * F(0x5C4) + t1 * F(0x5CC);

    f32 t2;
    Curve_1A5760::Get(t2, P(0x5F0), dt);
    F(0x644) = (1.0f - t2) * F(0x5E0) + t2 * F(0x5E4);

    f32 t3;
    Curve_1A5760::Get(t3, P(0x610), dt);
    F(0x648) = (1.0f - t3) * F(0x600) + t3 * F(0x604);

    f32 t4;
    Curve_1A5760::Get(t4, P(0x570), dt);
    s32 n = (s32)((1.0f - t4) * F(0x560) + t4 * F(0x564));
    if (I(0x624) < n && I(0x380) == I(0x624)) {
        F(0x634) = (*(f32*)&D_0026185C) + func_001EAAE0(F(0x62C), F(0x630));
    }
    I(0x624) = n;

    f32 t5;
    Curve_1A5760::Get(t5, P(0x590), dt);
    n = (s32)((1.0f - t5) * F(0x580) + t5 * F(0x584));
    if (I(0x628) < n && I(0x39C) == I(0x628)) {
        F(0x640) = (*(f32*)&D_0026185C) + func_001EAAE0(F(0x638), F(0x63C));
    }
    I(0x628) = n;
}

// Data

f32 D_0026B7D8[4] = { 20.0f, 0.0f, 0.30000001192092896f, 0.0f };
ObjectLink D_0026B7E8[6] = {
    { 0x2, 0x29C, 0x58C },
    { 0x2, 0x29D, 0x590 },
    { 0x2, 0x29E, 0x594 },
    { 0x2, 0x29F, 0x598 },
    { 0x2, 0x2A1, 0x5A0 },
    { 0x2, 0x2A2, 0x5A4 }
};
ObjectLink D_0026B830[1] = { { 0x2, 0x2A3, 0x560 } };
ObjectLink D_0026B840[1] = { { 0x6, 0x2AE, 0x578 } };
ObjectLink D_0026B888[1] = { { 0x2, 0x2AF, 0x55C } };
ObjectLink D_0026B8A0[1] = { { 0x2, 0x2B3, 0x560 } };
f32 D_0026B850[4] = { 2.0f, 0.0f, 0.699999988079071f, 0.0f };
void* D_0026B860[10] = { (void*)0x2A4, (void*)0x2A5, (void*)0x2A6, (void*)0x2A7, (void*)0x2A8, (void*)0x2A9, (void*)0x2AA, (void*)0x2AB, (void*)0x2AC, (void*)0x2AD };
Entry_26B8B0 D_0026B8B0[11] = {
    { { 0x1, 0x1, 0x3D4CCCCD, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } },
    { { 0x2, 0x9600, 0x3D4CCCCD, 0x0, 0x3D4CCCCD, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } },
    { { 0x2, 0xD200, 0x3D4CCCCD, 0x0, 0x3DCCCCCD, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } },
    { { 0x2, 0xFF00, 0x3DCCCCCD, 0x0, 0x3DCCCCCD, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } },
    { { 0x7, 0xD200, 0x3DCCCCCD, 0xBE00, 0x3C23D70A, 0xAA00, 0x3C23D70A, 0x9600, 0x3C23D70A, 0x8200, 0x3C23D70A, 0x6E00, 0x3C23D70A, 0x0, 0x3E800000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } },
    { { 0x2, 0xFF01, 0x3DCCCCCD, 0x1, 0x3D4CCCCD, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } },
    { { 0x2, 0xAA00, 0x3D4CCCCD, 0x0, 0x3DCCCCCD, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } },
    { { 0x2, 0xAA00, 0x3D4CCCCD, 0x0, 0x3DCCCCCD, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } },
    { { 0x2, 0xAA00, 0x3D4CCCCD, 0x0, 0x3DCCCCCD, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } },
    { { 0x3, 0xA000, 0x3E19999A, 0x0, 0x3DCCCCCD, 0x5A00, 0x3D4CCCCD, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } },
    { { 0x5, 0xFF00, 0x3E4CCCCD, 0x0, 0x3DA3D70A, 0xC800, 0x3E051EB8, 0x0, 0x3D75C28F, 0x9600, 0x3DE147AE, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } }
};
extern const Table_1A4718 D_0024C9D0 = { {
    { 2.0f, 5.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 8.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 1.0f, 2.5f, 0.10000000149011612f, 0.30000001192092896f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 1.5f, 3.0f, 0.15000000596046448f, 0.4000000059604645f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 400.0f, 1500.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 3.0f, 6.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f }
} };
