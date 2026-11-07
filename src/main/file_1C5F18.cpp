// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "fpu.h"
#include "globals.h"
#include "pad_record.h"
#include "attachment.h"
#include "list_iter.h"
#include "vu0.h"

extern f32 g_gameTime[];
extern const T2195_Vt D_00219560;

// The pose source that adds up the offsets of the attachments after it (D_0021A9A8): the number
// of them to take.
struct ChildPoseSource : Attachment {
    u8 pad18[0x1C - 0x18];  // 0x18
    s32 count;              // 0x1C
};

struct Rec_274BA0 { s32 a[12]; f32 b; };

// The file's .rodata: the jump tables of its assembly (func_001C6928's own follows them).
INCLUDE_RODATA(jtbl_0024D5A0);
INCLUDE_RODATA(jtbl_0024D5D0);

// The file's .data, in retail's order.
f32 D_00274B90 = 0.06666667f;
f32 D_00274B94 = 0.16666667f;
f32 D_00274B98 = 0.116666675f;
Rec_274BA0 D_00274BA0 = { { (s32)0xFFFFFFFF, (s32)0xFFFFFFFF, (s32)0xFFFFFFFF, (s32)0xFFFFFFFF, 6, 7, 4, 5, (s32)0xFFFFFFFF, (s32)0xFFFFFFFF, (s32)0xFFFFFFFF, (s32)0xFFFFFFFF }, 0.15f };
float D_00274BD4 = -250.0f;
f32 D_00274BD8 = -1.0f;
f32 D_00274BE0[4] = { 175.0f, 0.0f, 0.0f, 0.0f };
f32 D_00274BF0[4] = { 250.0f, 0.0f, 125.0f, 0.0f };
f32 D_00274C00[4] = { 125.0f, 0.0f, 0.0f, 0.0f };
s32 D_00274C10 = 0;
s32 D_00274C14 = 0;

void SumChildPoseOffsets(ChildPoseSource* self, f32 t, Vec02* pos, Vec02* vec)
{
    ListFrame frame;
    Vec02 a;
    Vec02 b;
    Vec02 d;
    PlacedObject* owner = self->owner;
    *pos = owner->v190;
    *vec = D_00248D30;
    Attachment* c = self;
    s32 n = ((ChildPoseSource*)c)->count;
    if (n > 0) {
        c = c->link.next;
        while (c != 0) {
            if ((u8)(c->mode0 + 1) >= 2) {
                if (c->vt != &D_00219560) {
                    c->vt->getPos(c, t, &a, &b);
                    Vu0::Q(d) = Vu0::Sub(Vu0::Q(a), Vu0::Q(owner->v190));
                    Vu0::Q(*pos) = Vu0::Add(Vu0::Q(*pos), Vu0::Q(d));
                    Vu0::Q(*vec) = Vu0::Add(Vu0::Q(*vec), Vu0::Q(b));
                }
                n--;
            }
            if (n <= 0) {
                break;
            }
            c = c->link.next;
        }
    }
}

INCLUDE_ASM(func_001C6028);

INCLUDE_ASM(func_001C61E0);

s32 IsObjectAttached(void* p);
void func_001C61E0(Player* self, s32 mode);
void TrackAimTargetObject(Player* self, s32 v, void* p);
void TrackAimTargetPoint(Player* self, s32 v, s32 w, void* blk);

void UpdatePlayerAimTarget(Player* s)
{
    if (s->f2200 != 0 && IsObjectAttached(s->f2200) == 0) {
        s32 v = s->f223C;
        s->f2200 = 0;
        s->f2204 = 0;
        if (v != 0) {
            return;
        }
        func_001C61E0(s, -1);
    }
    if (s->f223C != 0) {
        return;
    }
    void* p = s->f2200;
    if (p != 0) {
        TrackAimTargetObject(s, s->f21C4, p);
        return;
    }
    if (s->f2208 != 0) {
        TrackAimTargetPoint(s, s->f21C4, s->f2208, s->pad220C);
    }
}

void SetPlayerState(Player* self, s32 a, s32 b);
void func_001C61E0(Player* self, s32 state);

void HandlePlayerAimButton(Player* self, PadRecord* other)
{
    s32 flag = 1;
    s32 held = other->flags & 0x80;
    switch (self->f2220) {
    case 3:
        if (held == 0) goto tail;
        flag = 0;
        SetPlayerState(self, 2, 2);
        break;
    case 6:
        if (self->f239C < 6) {
            if (self->f239C >= 4) break;
        }
        flag = 0;
        break;
    case 2:
    case 4:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        flag = 0;
        break;
    case 0:
        if (self->f2590 != 0 && self->f25AC != 0) {
            switch (self->f223C) {
            case 4:
                func_001C61E0(self, 6);
                break;
            case 5:
                func_001C61E0(self, 7);
                break;
            }
        }
        break;
    }
    if (held != 0)
        self->f21C8 = g_gameTime[0];
tail:
    s32 st = self->f223C;
    if (st == -1) {
        if (flag != 0) {
            if (g_gameTime[0] - self->f21C8 < 0.35f) st = 3;
        }
    } else if (st >= -1) {
        if (st < 8) {
            if (st >= 4) {
                if (flag != 0 && self->f2248 != 0) {
                    if (g_gameTime[0] - self->f21C8 < 0.35f) st = 3;
                }
            }
        }
    }
    func_001C61E0(self, st);
}

INCLUDE_ASM(func_001C6AA8);

// What FindNearestClass75Ahead finds: the direction to the nearest class 0x75 object ahead
// and the object, 0 for none.
struct NearestAhead {
    f32 dir[4];
    void* found;
};
// Two entries of a blend record, 0xC bytes apart, whose weights func_001399F8 takes.
struct TwoBlendWeights { f32 a; u8 pad[0xC - 4]; f32 b; };

void FindNearestClass75Ahead(Player* self, s32 mode, void* tbl, void** found, f32* dir, f32 a, f32 b);
void SetBlendItemWeights(void* ctx, s32 n, s32 m, TwoBlendWeights* out);
f32 ArctangentOfRatio(f32 a, f32 b);
void TurnColliderTowardHeading(Player* self);

void SetPlayerClass75AheadBlend(Player* s, TwoBlendWeights* out, void* ctx)
{
    NearestAhead fr;
    f32 k = 1.60000002f;
    if (s->f2220 == 0) {
        k = 3.1500001f;
    }
    FindNearestClass75Ahead(s, 2, D_00274BE0, &fr.found, fr.dir, 0.150000006f, k);
    f32 t;
    if (fr.found != 0) {
        f32 v = (fr.dir[2] - -50.0f) * 0.0090909088f;
        f32 hi = 1.0f;
        f32 lo = 0.0f;
        if (v < lo) {
            t = lo;
        } else if (hi < v) {
            t = 1.0f;
        } else {
            t = v;
        }
    } else {
        t = 1.0f;
    }
    if (D_00274BD8 >= 0.0f) {
        t = D_00274BD8;
    }
    out->a = 1.0f - t;
    out->b = t;
    SetBlendItemWeights(ctx, 0xC, 2, out);
    s->f2204 = 0;
    s->f2200 = fr.found;
    s->f2208 = 0;
    if (fr.found != 0 && s->f2220 == 0) {
        s->f638 = ArctangentOfRatio(fr.dir[1], fr.dir[0]);
        TurnColliderTowardHeading(s);
    }
}

void TurnPlayerToClass75AheadMask8(Player* self)
{
    NearestAhead t;
    FindNearestClass75Ahead(self, 8, D_00274BF0, &t.found, t.dir, 0.25f, 1.0f);
    self->f2204 = 0;
    self->f2200 = t.found;
    self->f2208 = 0;
    if (t.found != 0) {
        self->f638 = ArctangentOfRatio(t.dir[1], t.dir[0]);
        TurnColliderTowardHeading(self);
    }
}

void TurnPlayerToClass75AheadMask4(Player* self)
{
    NearestAhead t;
    FindNearestClass75Ahead(self, 4, D_00274C00, &t.found, t.dir, 0.25f, 3.15f);
    self->f2204 = 0;
    self->f2200 = t.found;
    self->f2208 = 0;
    if (t.found != 0) {
        self->f638 = ArctangentOfRatio(t.dir[1], t.dir[0]);
        TurnColliderTowardHeading(self);
    }
}
