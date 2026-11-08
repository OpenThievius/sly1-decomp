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
#include "transform_object.h"
#include "c8b.h"
#include "game_clock.h"

extern f32 g_gameTime[];
extern u8 g_class75List[];
void BuildAxisAngleMatrix(const Vec02* axis, Mat02* out, f32 angle);
void TransformPointBetweenFrames(void* a0, void* a1, void* a2, void* a3);
s32 ComputeObjectFrameAtTime(void* object, s32 b, Vec02* pos, Mat02* rot, f32 t, s32 e, s32 f);
void GetObjectWorldPosition(void* p, Vec02* out);
void MeasurePointToSegment(Vec02* p, Vec02* a, Vec02* b, f32* o1, f32* o2);
f32 WrapAngle(f32 a);
f32 ArctangentOfRatio(f32 a, f32 b);
extern const T2195_Vt D_00219560;

// The pose source that adds up the offsets of the attachments after it (D_0021A9A8): the number
// of them to take.
struct ChildPoseSource : Attachment {
    u8 pad18[0x1C - 0x18];  // 0x18
    s32 count;              // 0x1C
};

struct Rec_274BA0 { s32 a[12]; f32 b; };

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

// An item of an animation player's list (func_001C61E0): two byte states and a time.
struct AimPlayerItem {
    u8 pad0[0x10];
    s8 state10;             // 0x10
    s8 state11;             // 0x11
    u8 pad12[0x18 - 0x12];
    f32 time;               // 0x18
    u8 pad1C[0x20 - 0x1C];
    AimPlayerItem* next;    // 0x20
};

// The animation player the aim keeps at Player+0x2244.
struct AimPlayer {
    u8 pad0[8];
    Gr8B* anim;             // 0x08
    u8 pad0C[0x14 - 0x0C];
    f32 time;               // 0x14
    f32 speed;              // 0x18
    f32 rate;               // 0x1C
    u8 pad20[0x44 - 0x20];
    AimPlayerItem* items;   // 0x44
};

struct AimSlotObject;
typedef void (*AimSlotFn)(AimSlotObject* self, ...);
struct AimSlotObject { AimSlotFn* vt; };

struct AimSoundSource { u8 pad0[0xAC]; s32 fAC; };
struct AimSoundPoint { u8 pad0[0x54]; s32 f54; };
struct AimTarget { u8 pad0[0x3E4]; Gr8B* f3E4; };

void StartSoundEffect(s32 id, void* a1, void* a2, void* a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
void TeleportStateWalker(void* p, s32 n);
s32 FindStateEntryIndex(void* p, s32 n);
void SetPlayerClass75AheadBlend(Player* self, void* blend, void* anim);
void ReplaceAnimationPlayer(void* anim, Player* self, s32 c, void* slot, f32 start, f32 speed);
extern f32 D_00274B90;
extern f32 D_00274B94;
extern f32 D_00274B98;
extern s32 D_00274C10;
extern s32 D_00274C14;

void func_001C61E0(Player* self, s32 state)
{
    s32 old = self->f223C;
    if (old == state) {
        return;
    }
    s32 chained = 0;
    if (state != -1 && old != -1) {
        chained = state == D_00274BA0.a[old];
    }
    AimSlotObject* hold = (AimSlotObject*)self->f25D8[0];
    if (hold != 0 && chained == 0) {
        hold->vt[7](hold);
    }
    s32 id;
    self->f2254 &= ~2;
    switch (self->f223C) {
    case 1:
        id = ((AimSoundSource*)self->f2204)->fAC;
        goto play;
    case 2:
        id = ((AimSoundPoint*)self->f2208)->f54;
    play:
        StartSoundEffect(id, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    case 0:
        self->f4B8 = 0;
        break;
    case 6:
    case 7:
    case 8:
    case 9:
        if (self->f2220 == 0) {
            TeleportStateWalker(self->f2234, 0x146);
        }
        break;
    case -1:
        break;
    }
    f32 start = 0.0f;
    void* anim = 0;
    f32 speed = 1.0f;
    f32 delay = 0.0f;
    s32 sound = -1;
    switch (state) {
    case -1:
        self->f2200 = 0;
        self->f2204 = 0;
        self->f2208 = 0;
        break;
    case 1:
        self->f4B8 = 0;
        break;
    case 2:
        self->f4B8 = 0;
        break;
    case 10:
        self->f4B8 = 0;
        anim = self->f1018;
        break;
    case 11:
        self->f4B8 = 0;
        anim = self->f101C;
        break;
    case 0: {
        Gr8B* g = ((AimTarget*)self->f21C4)->f3E4;
        anim = g;
        sound = 13;
        speed = 0.0f;
        start = g->pC0->p8->f8;
        self->f4B8 = 0;
        self->f2210 = 0;
        self->f2214 = 0;
        self->f2424 = g_gameClock.time + 0.1f;
        break;
    }
    case 3: {
        Vec02 v;
        self->f25EC = 0;
        self->f21C8 = -1.0f;
        TransformPointBetweenFrames(0, self, (u8*)self->f23D4 + 0x140, &v);
        Vu0::Vec h = Vu0::Vec::Scalar(0.5f);
        Vu0::Q(v) = Vu0::MulXSum(Vu0::Vec::Of(v), h, Vu0::Vec::Of(*(Vec02*)((u8*)self->f61C + 0x100)), h).q;
        if (self->f2220 == 0) {
            if (D_00274C10 != 0) {
                state = 6;
                goto aim6;
            }
            if (D_00274C14 != 0) {
                state = 7;
                goto aim7;
            }
            if (v.y < 0.0f) {
                state = 6;
                goto aim6;
            }
            state = 7;
            goto aim7;
        } else {
            if (D_00274C10 != 0) {
                state = 4;
                goto aim4;
            }
            if (D_00274C14 != 0) {
                state = 5;
                goto aim5;
            }
            if (v.y < 0.0f) {
                state = 4;
                goto aim4;
            }
            state = 5;
            goto aim5;
        }
    }
    case 4:
    aim4:
        self->f25EC = 0;
        SetPlayerClass75AheadBlend(self, self->f2540, self->f2558);
        sound = 11;
        delay = D_00274B90;
        anim = self->f2558;
        self->f2424 = g_gameClock.time + D_00274B94;
        break;
    case 5:
    aim5:
        self->f25EC = 0;
        SetPlayerClass75AheadBlend(self, self->f255C, self->f2574);
        sound = 11;
        delay = D_00274B90;
        anim = self->f2574;
        self->f2424 = g_gameClock.time + D_00274B98;
        break;
    case 6:
    aim6:
        self->f25EC = 0;
        SetPlayerClass75AheadBlend(self, self->f2578, (void*)self->f2590);
        sound = 11;
        delay = D_00274B90;
        anim = (void*)self->f2590;
        if (FindStateEntryIndex(self->f1188, 0x14F) >= 0) {
            TeleportStateWalker(self->f2234, 0x14F);
        }
        self->f2424 = g_gameClock.time + D_00274B94;
        break;
    case 7:
    aim7:
        self->f25EC = 0;
        SetPlayerClass75AheadBlend(self, self->f2594, (void*)self->f25AC);
        sound = 11;
        delay = D_00274B90;
        anim = (void*)self->f25AC;
        if (FindStateEntryIndex(self->f1188, 0x14F) >= 0) {
            TeleportStateWalker(self->f2234, 0x14F);
        }
        self->f2424 = g_gameClock.time + D_00274B98;
        break;
    case 8:
        anim = self->f25B0;
        break;
    case 9:
        anim = self->f25B4;
        break;
    }
    if (chained != 0) {
        f32 s = ((AimPlayer*)self->f2244)->speed;
        start = ((AimPlayer*)self->f2244)->time;
        if (s == 0.0f) {
            if (start == 0.0f) {
                speed = -1.0f;
            } else if (start == ((AimPlayer*)self->f2244)->anim->f34) {
                speed = 1.0f;
            }
        } else {
            speed = s;
        }
        sound = -1;
        speed /= ((AimPlayer*)self->f2244)->rate;
    } else {
        self->f2248 = 0;
    }
    s32 wasPair = self->f223C == 11 || self->f223C == 2;
    s32 isPair = state == 11 || state == 2;
    if (wasPair != isPair) {
        if (state == 11 || state == 2) {
            AimSlotObject* a = (AimSlotObject*)self->f23D8;
            a->vt[6](a);
            a = (AimSlotObject*)self->f23D8;
            a->vt[35](a, self->f23D0);
            a = (AimSlotObject*)self->f23D0;
            a->vt[7](a);
        } else {
            AimSlotObject* a = (AimSlotObject*)self->f23D0;
            a->vt[6](a);
            a = (AimSlotObject*)self->f23D0;
            a->vt[35](a, self->f23D8);
            a = (AimSlotObject*)self->f23D8;
            a->vt[7](a);
        }
    }
    self->f223C = state;
    self->f2240 = g_gameClock.time;
    self->f21CC = 0;
    ReplaceAnimationPlayer(anim, self, 1, &self->f2244, start, speed);
    if (delay != 0.0f) {
        AimPlayerItem* it = ((AimPlayer*)self->f2244)->items;
        if (it != 0) {
            do {
                if (it->state10 == 3) {
                    it->state10 = 6;
                    it->time = g_gameClock.time + delay;
                }
                if (it->state11 == 3) {
                    it->state11 = 6;
                    it->time = g_gameClock.time + delay;
                }
                it = it->next;
            } while (it != 0);
        }
    }
    if (sound != -1) {
        StartSoundEffect(sound, 0, 0, &self->v140, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
}

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

void FindNearestClass75Ahead(Player* self, s32 mode, void* tbl, void** found, f32* dir, f32 a, f32 b)
{
    ListFrame frame;
    Mat02 rot;
    Vec02 eye;
    Vec02 here;
    Vec02 world;
    Vec02 local;
    Mat02 objRot;
    Vec02 objOrigin;
    Vec02 delta;
    Vec02 hitPoint;
    Vec02 bestPoint;
    u8* list = g_class75List;
    f32 bestDist = 300.0f;
    Class75Object* best = 0;
    BuildAxisAngleMatrix(&g_unitZVector, &rot, self->f638);
    {
        Vec02 k;
        Vu0::Q(k) = Vu0::FromFloat(a);
        Vu0::Q(eye) = Vu0::MulAddX(Vu0::Q(self->pos), Vu0::Q(self->v150), Vu0::Q(k));
    }
    TransformPointBetweenFrames(self, 0, tbl, &here);
    Vu0::Q(world) = Vu0::Add(Vu0::Rotate(rot, Vu0::Q(*(Vec02*)tbl)), Vu0::Q(eye));
    Vu0::Q(local) = Vu0::Sub(Vu0::Q(world), Vu0::Q(here));
    for (Class75Object* n = *(Class75Object**)list; n != 0; n = *(Class75Object**)((u8*)n + 0x80)) {
        Vec02 bestDir;
        f32 hit[2];
        if ((n->count & mode) == 0) {
            continue;
        }
        ComputeObjectFrameAtTime(n->parent, 0, &objOrigin, &objRot, a, 0, 0);
        GetObjectWorldPosition(n, &delta);
        Vu0::Q(delta) = Vu0::Add(Vu0::Q(delta), Vu0::Q(local));
        Vu0::Q(hitPoint) = Vu0::Add(Vu0::Rotate(objRot, Vu0::Q(*(Vec02*)((u8*)n + 0x40))), Vu0::Q(objOrigin));
        MeasurePointToSegment(&world, &delta, &hitPoint, &hit[0], &hit[1]);
        if (n->parent != 0) {
            if (((PlacedObject*)n->parent)->root->desc->flags & 8) {
                hit[1] = hit[1] + D_00274BD4;
            }
        }
        if (hit[1] < bestDist) {
            Vu0::Q(bestDir) = Vu0::Sub(Vu0::Q(delta), Vu0::Q(self->v140));
            f32 ang = ArctangentOfRatio(bestDir.y, bestDir.x);
            f32 diff = WrapAngle(ang - self->f638);
            if (__builtin_fabsf(diff) > b) {
                continue;
            }
            best = n;
            Vu0::Q(bestPoint) = Vu0::Sub(Vu0::Q(hitPoint), Vu0::Q(eye));
            bestDist = hit[1];
        }
    }
    *found = best;
    Vu0::Q(*(Vec02*)dir) = Vu0::Q(bestPoint);
}

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
