// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "screen_element.h"
#include "switched_collider.h"
#include "path_curve_object.h"
#include "cone_volume.h"
#include "world.h"
#include "masked_collider.h"
#include "object_link.h"
#include "message_body.h"
#include "shapes.h"
#include "game_progress.h"
#include "globals.h"
#include "script_value.h"
#include "fpu.h"
#include "collider.h"
#include "state_walker.h"
#include "asm_func.h"

void func_001830D8(void* self);

void func_00192C58(void* self);

void func_00181DA8(ModeWalker* self, s32 n);

void func_00152600(void* a, void* b);

void func_00128018(void* a0, s32 zero, void* table, void* out);

void func_001BC260(f32 t, void* obj, void* a, void* b);

f32 func_00205778(f32 a, f32 b);

f32 func_001EA408(f32 a);

void func_001C5D58(void* obj);

void func_00175170(void* obj, s32 a, s32 b);

void func_001BC4D8(void* self, void* sub);

void func_0013CE40(void* self);

void func_00124DF8(void* self, s32 a, void* table);

s32 func_001B6290(void* a0, void* self, s32 b, s32 c);

s32 func_00121160(s32 a);

void* func_0018D500(s32 size);

void func_00152600(u8* p, void* self);

void func_00152470(u8* p, void* self);

void func_00152470(void* sub, void* self);

void func_00182D48(void* self);

void func_00152470(u8* table, void* self);

void func_00152600(List01* list, BaseObject* item);

void func_00182ED0(void* self);

void func_00152600(u8* table, void* self);

void func_001D73A8(void* self);

void func_001DAE48(void);

void func_001DAF08(void* self, s32 code, MessageBody* rec);

void func_0013DDB8(void* self);

void func_00152470(List01* list, BaseObject* item);

typedef void (*LaunchFn)(void);

s32 func_00160C58();

void func_00192990(void* self, s32 value);

void func_00175170(void* self, s32 a, s32 b);

void func_001929D0(void* value);

void func_001D7098(void* out, s32 mode, void* owner);

void func_00181B20(void);

extern f32 D_0026185C;

// What func_00181BC8 builds on its stack: an owner message (InitOwnerMessage) whose function
// the player calls (slot 76), then the two words it tells its listeners (kind 0x17).
struct LaunchMessage { void* self; s32 val; s32 pad8; LaunchFn fn; };

extern f32 D_00261858[];

extern f32 D_00275C60[];

void func_001D9C98(ModeWalker* self, f32 dt);

void func_001D7098(void* out, s32 mode, Collider* c);

void func_001861E8(void* a, void* head);

void func_00129E10(void* o, f32 v);

void func_00129FB0(void* o, f32 v);

s32 func_001DDA80(void* p);


void func_001D7440(void* self);

void func_00124DF8(void* self, s32 a1, void* a2);

void func_00129D00(void* a, s32 b, void* c);

void func_00128018(void* a, void* b, void* c, void* d);

s32 func_001B4688(s32 key);

void func_001B64D8(void* p, s32 n);

void func_001B6628(void* p, s32 n);

struct ClampHelper
{
    static f32 Of(f32 x, f32 lo, f32 hi)
    {
        if (x < lo)
        {
            return lo;
        }
        if (hi < x)
        {
            return hi;
        }
        return x;
    }
};

extern Rgba4 D_002623E0[];

f32 func_00205210(f32 x);

void func_00126A48(ModeWalker* o, u32 c);

void func_00125C90(ModeWalker* o, void* a, void* b);

f32 func_00205210(f32 value);

// The file's .data, 0x2640B0 to 0x264260, in retail's order. GCC puts an object of eight bytes
// or more on 8, so the words after D_00264128, D_00264154 and D_00264190 are padding: the three
// vectors at 0x264160 are on 16 (Vec02; func_00128018 loads D_00264180 with lqc2).
ObjectLink D_002640B0[10] = {
    { 0, 0x35D, 0xBB8 }, { 4, 0x363, 0xBC0 }, { 4, 0x364, 0xBC4 }, { 4, 0x60, 0xBCC }, { 4, 0x365, 0xBC8 },
    { 2, 0x161, 0x588 }, { 2, 0x162, 0x58C }, { 2, 0x163, 0x590 }, { 4, 0x160, 0x584 }, { 7, 0x366, 0xC08 }
};
f32 D_00264128 = 0.150000006f;
f32 D_00264130[3] = { 30.0f, 0.0f, 0.5f };
f32 D_0026413C = 0.5f;
f32 D_00264140[4] = { 0.0f, 2.0f, 0.0f, 0.0f };
f32 D_00264150 = 6.0f;
f32 D_00264154 = 3.0f;
Vec02 D_00264160 = { 1.0f, 0.0f, -0.75f, 0.0f };
Vec02 D_00264170 = { 0.699999988f, 0.300000012f, 0.0f, 0.0f };
Vec02 D_00264180 = { -300.0f, 0.0f, 200.0f, 0.0f };
f32 D_00264190 = 150.0f;
f32 D_00264198[3] = { 20.0f, 0.0f, 0.100000001f };
f32 D_002641A4 = 1.5f;
f32 D_002641A8[4] = { 5000.0f, 500.0f, 0.150000006f, 0.0f };
f32 D_002641B8[3] = { 5.0f, 0.0f, 0.100000001f };
f32 D_002641C4 = 3.0f;
f32 D_002641C8[10] = { 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f };
f32 D_002641F0[16] = { 24.0f, -24.0f, 0.0f, 0.0f, 24.0f, 24.0f, 0.0f, 0.0f, -24.0f, -24.0f, 0.0f, 0.0f, -24.0f, 24.0f, 0.0f, 0.0f };
ObjectLink D_00264230[2] = { { 0, 0x36B, 0x6C4 }, { 0x20, 0x36C, 0x6EC } };
f32 D_00264248 = 2.5f;
f32 D_0026424C = 300.0f;
f32 D_00264250[4] = { 20.0f, 0.0f, 0.5f, 0.0f };

void func_00180EB0(ListedKeepObject* self)
{
    RegisterObject(self);
    AppendToList(&self->world->list1C9C, self);
}

void func_00180EE8(ListedKeepObject* self)
{
    UnregisterObject(self);
    RemoveFromList(&self->world->list1C9C, self);
}

void func_00180F20(ListedKeepObject* self)
{
    PathCurveKeptBits saved = self->keep;
    CopyObjectData(self);
    self->keep = saved;
}

void func_00180F68(ModeWalker* self)
{
    InitPathFollower(self);
    self->fBF4 = -10.0f;
}

void func_00180F98(ModeWalker* self)
{
    StartPathFollower(self);
    ResolveObjectLinks(self, 0xA, g_modeWalkerLinks);
    self->fBBC = (StateWalker*)CreateStateWalker(self->fBB8, self, -1, 0);
    AddMatrixAttachment(self->fBCC, 5, &self->fBD0);
    ((u8*)self->fBD0)[0x10] = 9;
    ((u8*)self->fBD0)[0x11] = 9;
    ((PlacedObject*)self->fBCC)->desc02()->m2B((PlacedObject*)self->fBCC);
    func_00128018(0, self->fBC0, (u8*)self->fBCC + 0x140, (u8*)self + 0xBE0);
    SetModeWalkerMode(self, 1);
    self->f864 = 3.4028234663852886e+38f;
    T217D_BF0* base = &D_00270650;
    ((T217D_Float*)&base->f288)->v = 0.0f;
    base->icon = FindAnimRecord(0x36A);
}

ASM_FUNC(func_00181078);

void func_00181448(ModeWalker* self, f32 dt)
{
    s32 buf[4];
    UpdatePathFollower(self, dt);
    if (self->fC04 != 0) {
        Contact03* n = (Contact03*)self->fC04;
        do {
            s32 j = (n->end[0].body != self);
            Collider* c = n->end[1 - j].part;
            while (c != 0 && c->f4E0 == 0) c = (Collider*)c->parent;
            if (c != 0 && (c->f4E0 == 1 || c->f4E0 == 4)) {
                InitOwnerMessage(buf, 0, c);
                while (c != 0) {
                    if (((s32 (*)(Collider*, Contact03*, void*))c->desc03()->m47)(c, n, buf) != 0) break;
                    c = (Collider*)c->parent;
                }
                ((Desc05*)self->desc)->m4C(self, buf);
            }
            n = n->next;
        } while (n != 0);
        FreePooledContactChain(self->world, self->fC04);
        self->fC04 = 0;
    }
    f32 t = g_gameClock[1] - self->fBF4;
    f32 v = D_00264140[0] + t * (D_00264140[1] + t * D_00264140[2]);
    f32* r = g_unitRange;
    f32 lo = g_unitRange[0];
    f32 hi = r[1];
    f32 x;
    if (v < lo) x = lo;
    else if (hi < v) x = hi;
    else x = v;
    func_00129E10(self->fBCC, x * D_00264150);
    func_00129FB0(self->fBCC, x * D_00264154);
    if (self->fBF0 != 0 && self->fBB0 != 2 && g_gameClock[1] - self->fBF8 > 2.0f) self->fBF0 = 0;
}

ASM_FUNC(func_00181658);

ASM_FUNC(func_00181780);

void func_00181818(ModeWalker* o, void* a, void* b)
{
    Rgba4 c;
    u8 from[4];
    *(u32*)from = 0x800000A0;
    if (o->fBF0) {
        f32 t;
        if (o->fBB0 != 2) {
            t = (g_gameClock[1] - o->fBF8) * 0.5f;
        } else {
            t = 0.0f;
        }
        f32 s = Cosine((g_gameClock[1] - o->fBF4) * 10.0f);
        f32 p = D_00264160.x + t * (D_00264160.y + t * D_00264160.z);
        f32 x = ClampHelper::Of(p, g_unitRange[0], g_unitRange[1]);
        f32 q = D_00264170.x + s * (D_00264170.y + s * D_00264170.z);
        f32 y = ClampHelper::Of(q, g_unitRange[0], g_unitRange[1]);
        f32 w = x * y;
        f32 u = 1.0f - w;
        c.r = (u8)(u * D_002623E0[0].r + w * from[0]);
        c.g = (u8)(u * D_002623E0[0].g + w * from[1]);
        c.b = (u8)(u * D_002623E0[0].b + w * from[2]);
        c.a = D_002623E0[0].a;
    } else {
        c = D_002623E0[0];
    }
    SetObjectTreeRecordValue(o, *(u32*)&c);
    func_00125C90(o, a, b);
}

void func_00181A58(ModeWalker* self, void* outv)
{
    Vec02* out = (Vec02*)((u8*)outv + 0x10);
    CapturePathFollowerPose();
    *out = ((PlacedObject*)self->fBC0)->v140;
}

s32 func_00181A98(ModeWalker* self)
{
    if (self->fBB0 != 1 || self->fBF0 != 0 || IsPadSelectFlagHeld(self->world) != 0) return 1;
    return 0;
}

s32 func_00181AE0(ModeWalker* p) { return p->fBF0 != 0; }

void func_00181AF0(ModeWalker* self)
{
    FinishSwitchedCollider(self);
    SetModeWalkerMode(self, 1);
}

void func_00181B20(void* unused, void* obj_)
{
    Player* obj = (Player*)obj_;
    Vec02 first;
    Vec02 second;

    func_00128018(unused, 0, &D_00264180, &first);
    func_001BC260(D_00264190, obj, &first, &second);
    obj->desc02()->m20(obj, &second);
    f32 r = ArctangentOfRatio(second.y, second.x);
    obj->f638 = WrapAngle(r + 3.1415927f);
    TurnColliderTowardHeading(obj);
    SetPlayerState(obj, 4, 0x2B);
}

s32 func_00181BC8(ModeWalker* self, s32* arg)
{
    LaunchMessage loc;
    s32 r;
    Player* g;
    Player* gp;

    if (self->desc05()->m4B(self, arg[0])) {
        return 0;
    }
    if (HasSpareCount()) {
        self->fBF0 = 1;
    }
    self->fBF4 = g_gameTime;
    r = HasSpareCount();
    if (r == 0) {
        g = g_player;
        if (g != 0) {
            goto then_block;
        }
    }
    SetModeWalkerMode(self, 2);
    goto tail;
then_block:
    g_player->desc->m02(g_player);
    g_player->desc02()->m1F(g_player, (PlacedObject*)self->fBC8);
    ((BaseObject*)self->fBC8)->desc->m03((BaseObject*)self->fBC8);
    SetSwitchedColliderEnabled((void*)g_player, 1);
    SetPlayerState((void*)g_player, 2, 2);
    ActivateSwitchedCollider((void*)g_player);
    SetModeWalkerMode(self, 3);
    InitOwnerMessage(&loc, 0, self);
    gp = g_player;
    gp = g_player;
    loc.fn = LaunchPlayerFromModeWalker;
    (void)gp->desc05()->m4C(gp, &loc);
tail:
    loc.self = self;
    loc.val = arg[1];
    self->desc->m0E(self, 0x17, &loc);
    return 1;
}

void func_00181D28(ModeWalker* self, s32 code, MessageBody* rec)
{
    if (code == 0x13) {
        StateWalker* sub = self->fBBC;
        s32 key = rec->sourceId;
        if (sub != 0 && key == (s32)sub->player) {
            s32 kind = rec->code;
            if (kind != 0x15E) {
                if (kind == 0x15F) {
                    self->fC00 = 0;
                }
            } else {
                self->fC00 = 1;
            }
        }
    }
    HandlePathFollowerNotification(self, code, rec);
}

void func_00181D88(ModeWalker* self)
{
    ExtractContactsByPartMode(self, (u8*)self + 0xC04);
}

void func_00181DA8(ModeWalker* self, s32 mode)
{
    s32 old;

    if (mode == self->fBB0) {
        return;
    }
    old = self->fBB0;
    if (old < 4) {
        if (old >= 2) {
            self->fBF8 = g_gameClock[1];
        }
    }
    switch (mode) {
    case 0:
        SetStateWalkerTarget(self->fBBC, 0x35E);
        break;
    case 1:
        SetStateWalkerTarget(self->fBBC, 0x35F);
        break;
    case 2:
        TeleportStateWalker(self->fBBC, 0x361);
        self->fBF8 = 3.40282347e+38f;
        break;
    case 3:
        TeleportStateWalker(self->fBBC, 0x362);
        self->fBF8 = 3.40282347e+38f;
        break;
    }
    if (mode == 0) {
        self->f580 = 0;
    } else if (mode < 0) {
        self->f580 = 1;
    } else if (mode >= 4) {
        self->f580 = 1;
    } else if (mode >= 2) {
        self->f580 = 0;
    } else {
        self->f580 = 1;
    }
    self->fBB0 = mode;
    self->fBB4 = g_gameClock[1];
}

INCLUDE_RODATA(D_0024B16C);
ASM_FUNC(func_00181ED0);

ASM_FUNC(func_001821B0);

void func_00182470(C24* self)
{
    InitPlayerFlaggedCollider(self);
    self->f6DC = 10.0f;
    self->f6E0 = 1.0f;
    self->f6D8 = 3000.0f;
    self->f6CC = 1000.0f;
    self->f6D0 = 0;
    self->f6D4 = 0.5f;
}

void func_001824D8(C24* self)
{
    StartMaskedCollider(self);
    ResolveObjectLinks(self, 2, D_00264230);
    self->x6C8 = (StateWalker*)CreateStateWalker(self->x6C4, self, 0x36E, 0);
    Alloc24* n = (Alloc24*)CreateWeightCurve(0);
    self->x6E8 = n;
    n->field8 = 0;
    self->x6E8->field_c = AllocateFrontMemory(0xC00);
}

ASM_FUNC(func_00182548);

ASM_FUNC(func_00182748);

ASM_FUNC(func_00182948);
