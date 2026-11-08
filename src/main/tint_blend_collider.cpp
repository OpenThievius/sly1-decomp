// SPDX-License-Identifier: AGPL-3.0-or-later
// Class 0x5E (RedirectObject) and class 0x14 (TintBlendCollider), from 0x1DDCE0 to 0x1DFD48. Its .data opens
// with the vector func_001DDCE0 reads (0x275730), just after the zeroed globals that close the
// previous file's, and ends at 0x2758D0, where file_1DFD48.cpp's starts; its .rodata is the one
// float func_001DFBE0 reads (0x24DCA8).
#include "common.h"
#include "vu0.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "state_trigger.h"
#include "cone_volume.h"
#include "redirect_object.h"
#include "world.h"
#include "screen_element.h"
#include "font.h"
#include "globals.h"
#include "game_progress.h"
#include "level_entry.h"
#include "message_body.h"
#include "owner_message.h"
#include "shapes.h"
#include "state_walker.h"

// The links func_001DE808 resolves (ResolveObjectLinks: flags, id, offset), and the word after
// them that aligns the next table.
struct ColliderLink { s32 flags, id, offset; };
struct ColliderLinkTable { ColliderLink e[9]; s32 end; };

extern u8 g_unitRange[];

Quad16 D_00275730 = { 0x42C80000, 0, 0, 0 };
Quad16 D_00275740 = { { 0x3F800000, 0, 0, 0 } };
ColliderLinkTable D_00275750 = { {
    { 0x0, 0x34D, 0x6DC }, { 0x0, 0x350, 0x758 }, { 0x4, 0x60, 0x748 },
    { 0x4, 0x50, 0x750 }, { 0x4, 0x34E, 0x744 }, { 0x2, 0x161, 0x588 },
    { 0x2, 0x162, 0x58C }, { 0x2, 0x163, 0x590 }, { 0x4, 0x160, 0x584 }
    }, 0 };
f32 D_002757C0[4] = { 0.0f, 2.0f, 0.0f, 0.0f };
f32 D_002757D0[1] = { 6.0f };
f32 D_002757D4 = 3.0f;
Vec02 D_002757E0 = { 0.0f, 0.0f, 800.0f, 0.0f };
f32 D_002757F0[4] = { 0.0f, 800.0f, 0.0f, 0.0f };
f32 D_00275800[4] = { 0.0f, 1.0f, 0.0f, 0.0f };
f32 D_00275810[8] = { 0.150000006f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f };
f32 D_00275830[4] = { -0.200000003f, 0.0f, 0.0f, 0.0f };
f32 D_00275840[4] = { 0.0f, 0.00124999997f, 0.0f, 0.0f };
f32 D_00275850[4] = { 0.0f, 2.0f, -1.0f, 0.0f };
f32 D_00275860 = 15.0f;
f32 D_00275864 = 10.0f;
Vec02 D_00275870 = { 1.0f, 0.0f, -0.75f, 0.0f };
f32 D_00275880[4] = { 0.699999988f, 0.300000012f, 0.0f, 0.0f };
f32 D_00275890 = 0.5f;
f32 D_00275894 = 700.0f;
f32 D_00275898 = 650.0f;
f32 D_0027589C = 650.0f;
f32 D_002758A0 = 300.0f;
f32 D_002758A4 = 400.0f;
f32 D_002758A8 = -100.0f;
f32 D_002758AC = 5.0f;
f32 D_002758B0[4] = { 1.5f, 0.0f, 0.0f, 0.0f };
f32 D_002758C0[4] = { 0.0f, 2.0f, 0.0f, 0.0f };



void InitPlacedObject(RedirectObject* self);

void InitRedirectObject(RedirectObject* self)
{
    InitPlacedObject(self);
    self->q320 = D_00275730;
}

void StartPlacedObject(void* self);
s32 IsObjectOfKind(void* node, s32 kind);
void* AllocateZeroedFrontMemory(s32 bytes);
void TransformPointBetweenFrames(void* node, s32 frame, Vec02* in, Vec02* out);

void StartRedirectObject(RedirectObject* self)
{
    PlacedObject* p;
    BaseObject* c;
    RedirectStep* step;

    StartPlacedObject(self);
    if (self->parent != 0 && IsObjectOfKind(self->parent, 0x5E) != 0) {
        return;
    }
    p = self;
    if (self != 0) {
        do {
            self->chainCount++;
            c = (BaseObject*)p->children.head;
            while (c != 0 && IsObjectOfKind(c, 0x5E) == 0) {
                c = c->next;
            }
            p = (PlacedObject*)c;
        } while (c != 0);
    }
    if (self->chainCount < 2 && self->f310 == 0) {
        self->chainCount = 0;
        return;
    }
    self->chainCount++;
    self->steps = (RedirectStep*)AllocateZeroedFrontMemory(self->chainCount << 6);
    step = self->steps;
    p = self;
    if (self != 0) {
        do {
            ((RedirectObject*)p)->target = self;
            step->node = p;
            step->pos = p->v140;
            *(u32*)&step->length = Vu0::ToBits(Vu0::Length(Vu0::Q(p->pos)));
            c = (BaseObject*)p->children.head;
            while (c != 0 && IsObjectOfKind(c, 0x5E) == 0) {
                c = c->next;
            }
            p = (PlacedObject*)c;
            if (c != 0) {
                step->below = p->pos;
            } else {
                step->below = *(Vec02*)&self->q320;
            }
            step++;
        } while (c != 0);
    }
    TransformPointBetweenFrames(step[-1].node, 0, &step[-1].below, &step->pos);
    step->length = step[-1].length;
}

INCLUDE_ASM(func_001DDE90);

void CopyPlacedObjectFrame(RedirectObject* self);

void MarkRedirectToSelf(RedirectObject* self)
{
    if (self->target == self) {
        self->targetIsSelf = 1;
    }
    CopyPlacedObjectFrame(self);
}


void InitTurningCollider(TintBlendCollider* self);
f32 ArctangentOfRatio(f32 a, f32 b);
void BuildAxisAngleMatrix(const Vec02* t, void* out, f32 x);

void InitTintBlendCollider(TintBlendCollider* self)
{
    f32 f;

    InitTurningCollider(self);
    f = ArctangentOfRatio(self->rot.r[0].y, self->rot.r[0].x);
    self->f638 = f;
    BuildAxisAngleMatrix(&g_unitZVector, (u8*)self + 0x660, f);
    self->f720 = -1;
    self->f72C = -10.0f;
    (*(Quad16*)&self->v6F0) = D_00275740;
}

// EXACT: literal 1 stores (no `one` local), `||` condition, D_00262E10 compared as a pointer

struct AttachedEffect { void** vtbl; };
typedef void (*LinkTargetFn)(void* self, void* a1, s32 a2);
typedef void (*AttachedEffectFn)(void* self);


void StartTurningCollider(void* self);
void ResolveObjectLinks(void* self, s32 n, void* table);
void AddMatrixAttachment(void* a, s32 b, void* c);
void* CreateStateWalker(void* a, void* b, s32 c, s32 d);
void SetTintBlendColliderState(void* self, s32 flag);

void StartTintBlendCollider(TintBlendCollider* self)
{
    TintBlendCollider* s = self;
    s32 flag;

    StartTurningCollider(self);
    ResolveObjectLinks(self, 9, &D_00275750);
    ((LinkTargetFn)s->desc03()->m34)(self, s->f6DC, 1);
    AddMatrixAttachment(s->f748, 5, &s->f74C);
    ((u8*)s->f74C)[0x10] = 1;
    ((u8*)s->f74C)[0x11] = 1;
    ((AttachedEffectFn)((AttachedEffect*)s->f748)->vtbl[47])(s->f748);
    AddMatrixAttachment(s->f750, 5, &s->f754);
    ((u8*)s->f754)[0x11] = 1;
    ((AttachedEffectFn)((AttachedEffect*)s->f750)->vtbl[47])(s->f750);
    s->f75C = (StateWalker*)CreateStateWalker(s->f758, self, -1, 1);
    if (s->f73C == 0 || g_player == 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    SetTintBlendColliderState(self, flag);
    s->f598 = self;
    s->f594 = 150.0f;
}

// NEAR: the call sequence, the list walk and the frame (0xC0) match; the scale constant D_002757D0 is held in s8 in retail but the C here addresses it through a pointer, so the register numbering of the constants 1 and 4 and the float tail differ (40 differing lines).

struct TintGlowEffect;
typedef s32 (*ContactClaimFn)(void* self, void* a1, void* a2);
typedef void (*OwnerMessageFn)(void* self, void* a1);
extern f32 g_gameClock[];

void UpdateTurningCollider(void);
s32 HasAnimationDrivenAttachment(TintBlendCollider* self);
void ResetTintBlendColliderOrientation(TintBlendCollider* self);
void InitOwnerMessage(OwnerMessage* l, s32 zero, Collider* c);
void FreePooledContactChain(World* a0, Contact03* a1);
void SetScaledPositionSpring(TintGlowEffect* a, f32 v);
void SetScaledRotationSpring(TintGlowEffect* a, f32 v);

void UpdateTintBlendCollider(TintBlendCollider* self)
{
    OwnerMessage loc;
    f32 f20;
    Contact03* s1;
    Collider* s0;
    s32 v;
    s32 idx;

    UpdateTurningCollider();
    if (HasAnimationDrivenAttachment(self) != 0) {
        ResetTintBlendColliderOrientation(self);
    }
    Contact03* head = ((Contact03*)self->f740);
    if (head != 0) {
        s1 = head;
        do {
            idx = (s1->end[0].body != self);
            s0 = s1->end[1 - idx].part;
            while (s0 != 0 && s0->f4E0 == 0) {
                s0 = (Collider*)s0->parent;
            }
            if (s0 != 0) {
                v = s0->f4E0;
                if (v == 1 || v == 4) {
                    InitOwnerMessage(&loc, 0, s0);
                    while (s0 != 0) {
                        if (((ContactClaimFn)s0->desc03()->m47)(s0, s1, &loc)) {
                            break;
                        }
                        s0 = (Collider*)s0->parent;
                    }
                    ((OwnerMessageFn*)self->desc)[80](self, &loc);
                }
            }
            s1 = s1->next;
        } while (s1 != 0);
        FreePooledContactChain(self->world, ((Contact03*)self->f740));
        self->f740 = 0;
    }
    {
        f32 d = g_gameClock[1] - self->f72C;
        f32 x = D_002757C0[0] + d * (D_002757C0[1] + d * D_002757C0[2]);
        f32 c0 = ((f32*)g_unitRange)[0];
        f32 c1 = ((f32*)g_unitRange)[1];
        if (x < c0) {
            f20 = c0;
        } else if (c1 < x) {
            f20 = c1;
        } else {
            f20 = x;
        }
    }
    SetScaledPositionSpring(((TintGlowEffect*)self->f748), f20 * D_002757D0[0]);
    SetScaledRotationSpring(((TintGlowEffect*)self->f748), f20 * D_002757D4);
    if (self->f728 != 0 && self->f720 != 2) {
        f32 e = g_gameClock[1] - self->f730;
        if (2.0f < e) {
            self->f728 = 0;
        }
    }
}

extern f32 g_frameDt;
void func_00128598(f32 a, f32 b, void* self, s32 c, s32 d, f32* e, f32* f, f32* g);
void BuildYawPitchMatrix(Mat02* out, f32 yaw, f32 pitch);

void ResetTintBlendColliderOrientation(TintBlendCollider* self)
{
    f32 heading, pitch, speed;
    func_00128598(g_frameDt, self->f638, self, 0, 0, &heading, &pitch, &speed);
    self->f638 = heading;
    BuildYawPitchMatrix(&self->m660, heading, pitch);
    Vu0::Q(self->v640) = Vu0::FromFloats(-speed, 0.0f, 0.0f);
}

void FinishSwitchedCollider(void* self);
void SetTintBlendColliderState(void* self, s32 flag);

void FinishTintBlendColliderRequest(TintBlendCollider* self)
{
    FinishSwitchedCollider(self);
    SetTintBlendColliderState(self, 1);
}

INCLUDE_ASM(func_001DEBE8);

void HandleSwitchedColliderActivation(void* self, void* p);

void SetTintBlendColliderTracked(TintBlendCollider* self, void* p)
{
    HandleSwitchedColliderActivation(self, p);
    if (p == 0) {
        self->f728 = 0;
    }
}

extern f32 g_gameClock[];
extern Rgba4 D_002623E0;

struct UnitClamp {
    static f32 Of(f32 v, f32 lo, f32 hi)
    {
        return v < lo ? lo : (hi < v ? hi : v);
    }
};

f32 Cosine(f32 x);
void SetObjectTreeRecordValue(TintBlendCollider* s, u32 c);
void func_00125C90(TintBlendCollider* s, void* a, void* b);

void ApplyTintBlendColliderTint(TintBlendCollider* self, void* a1, void* a2)
{
    Rgba4 out;
    Rgba4 col;
    f32 t;
    if (!(self->flags & 0x100000000UL)) {
        *(u32*)&col = 0x800000A0;
        if (self->f728 != 0) {
            if (self->f720 != 2) {
                t = (g_gameClock[1] - self->f730) * 0.5f;
            } else {
                t = 0.0f;
            }
            f32 r = Cosine((g_gameClock[1] - self->f72C) * 10.0f);
            f32 a = D_00275870.x + t * (D_00275870.y + t * D_00275870.z);
            a = UnitClamp::Of(a, ((f32*)&g_unitRange)[0], ((f32*)&g_unitRange)[1]);
            f32 b = D_00275880[0] + r * (D_00275880[1] + r * D_00275880[2]);
            b = UnitClamp::Of(b, ((f32*)&g_unitRange)[0], ((f32*)&g_unitRange)[1]);
            f32 k = a * b;
            f32 inv = 1.0f - k;
            out.r = (s32)(inv * D_002623E0.r + k * col.r);
            out.g = (s32)(inv * D_002623E0.g + k * col.g);
            out.b = (s32)(inv * D_002623E0.b + k * col.b);
            out.a = D_002623E0.a;
        } else {
            out = D_002623E0;
        }
        SetObjectTreeRecordValue(self, *(u32*)&out);
        func_00125C90(self, a1, a2);
    }
}

INCLUDE_ASM(func_001DF520);

s32 IsPadSelectFlagHeld(void* p);

s32 IsTintBlendColliderRequestBlocked(TintBlendCollider* self, s32 mode)
{
    if (mode == 5 || self->f720 == 2 || self->f720 == 0 || self->f720 == 3 || self->f728 != 0 || IsPadSelectFlagHeld(self->world) != 0) return 1;
    return 0;
}

INCLUDE_ASM(func_001DF600);

INCLUDE_ASM(func_001DF700);

void ExtractContactsByPartMode(void* self, void* sub);
void CollectTurningColliderContacts(void* self);

void CollectTintBlendColliderContacts(TintBlendCollider* self)
{
    ExtractContactsByPartMode(self, (u8*)self + 0x740);
    CollectTurningColliderContacts(self);
}

struct TintBlendOutput { u8 pad0[0x94]; f32 f94; s32 f98; };

typedef s32 (*TintBlendTestFn)(void* self, void* out);

extern f32 g_gameTime;

void ComputeTintBlendColliderContactValue(TintBlendCollider* self, void* out)
{
    TintBlendCollider* obj = self;
    TintBlendOutput* o = (TintBlendOutput*)out;

    if (((TintBlendTestFn)obj->desc06()->m56)(self, out)) {
        f32 d = g_gameTime - obj->f72C;
        f32 lo = ((f32*)g_unitRange)[0];
        f32 hi = ((f32*)g_unitRange)[1];
        f32 v = D_002758C0[0] + d * (D_002758C0[1] + d * D_002758C0[2]);
        f32 r;
        if (v < lo) {
            r = lo;
        } else if (hi < v) {
            r = hi;
        } else {
            r = v;
        }
        f32 k = D_002758B0[0];
        o->f98 = 0;
        o->f94 = r * k;
    } else {
        o->f94 = 0.0f;
        o->f98 = 0;
    }
}

void GetStateWalkerCurrentKey(void* dev, s32* out);
void GetStateWalkerTargetKey(void* dev, s32* out);
void HandleSwitchedColliderNotification(void* self, s32 kind, MessageBody* rec);

void HandleTintBlendColliderNotification(TintBlendCollider* self, s32 code, MessageBody* rec)
{
    s32 loc[2];

    if (code != 0x13) {
        if (code == 0x14) {
            if (rec == (MessageBody*)self->f75C) {
                GetStateWalkerCurrentKey(rec, &loc[0]);
                GetStateWalkerTargetKey(self->f75C, &loc[1]);
            }
        }
    } else {
        StateWalker* dev = self->f75C;
        s32 key = rec->sourceId;
        if (dev != 0 && key == (s32)dev->player) {
            s32 kind = rec->code;
            if (kind != 0x15E) {
                if (kind == 0x15F) {
                    self->f738 = 0;
                }
            } else {
                self->f738 = 1;
            }
        }
    }
    HandleSwitchedColliderNotification(self, code, rec);
}

s32 GetTintBlendColliderRequestPhase(TintBlendCollider* self)
{
    return self->f728 != 0;
}

extern f32 g_gameClock[];



void SetStateWalkerTarget(StateTrigger* h, s32 b);
void TeleportStateWalker(StateTrigger* h, s32 b);
void BuildAxisAngleMatrix(const Vec02* tab, void* out, f32 v);

void SetTintBlendColliderState(TintBlendCollider* self, s32 mode)
{
    s32 old = self->f720;
    if (mode != old) {
        switch (old) {
        case 2:
            self->f730 = g_gameClock[1];
            break;
        case 3:
            self->f4E0 = 0;
            self->f730 = g_gameClock[1];
            break;
        }
        switch (mode) {
        case 0:
            SetStateWalkerTarget((StateTrigger*)self->f75C, 0x351);
            break;
        case 1:
            SetStateWalkerTarget((StateTrigger*)self->f75C, 0x352);
            break;
        case 2:
            TeleportStateWalker((StateTrigger*)self->f75C, 0x354);
            self->f730 = 3.40282347e+38f;
            break;
        case 3:
            TeleportStateWalker((StateTrigger*)self->f75C, 0x355);
            self->f4E0 = mode;
            self->f730 = 3.40282347e+38f;
            break;
        }
        switch (mode) {
        case 0:
        case 2:
        case 3:
            self->v640 = D_00248D30;
            BuildAxisAngleMatrix(&g_unitZVector, &self->m660, self->f638);

            self->f580 = 0;
            break;
        default:
            self->f580 = 1;
            break;
        }
        self->f720 = mode;
        self->f724 = g_gameClock[1];
    }
}
