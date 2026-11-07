// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "switched_collider.h"
#include "memory_card.h"
#include "game_progress.h"
#include "screen_element.h"

// The methods of class 0x0C (0xE50 bytes, an agent): its links and clips, the search for the
// object it acts on, its states and the notifications it answers.

struct Ent_264910 { s32 a, b, c; };
struct Ent_264960 { s32 key; f32 f; s32 v; };

Ent_264910 D_00264910[2] = { { 0, 0x82, 0xC24 }, { 0, 0x83, 0xC74 } };
s32 D_00264928[10] = { 1, 0x437, 0xE0C, 0, 0x440, 0xE18, 0, 0x441, 0xE1C, 0 };
s32 D_00264950[4] = { 0x446, 0x447, 0x448, 0 };
Ent_264960 D_00264960[6] = {
    { 0x35, 50.0f, 0 }, { 0x36, 50.0f, 0 }, { 0x38, 80.0f, 0 },
    { 0x3B, 80.0f, 0 }, { 0x60, 70.0f, 0 }, { 0x50, 220.0f, 0 }
};
s32 D_002649A8 = 0;
s32 D_002649B0[5] = { 4, 5, 60, 41, 76 };
f32 D_002649C4 = 1.5e+02f;
f32 D_002649C8 = 0.25f;
f32 D_002649D0[2] = { 0.0f, 0.25f };
s32 D_002649D8[4] = { 16, 16, 11, 0 };
s32 D_002649E8[6] = { 1083, 1085, 1087, 0, 0, 0 };
f32 D_00264A00[4] = { 0.0f, 0.00125f, 0.0f, 0.0f };
f32 D_00264A10[4] = { 0.0f, 0.0004f, 0.0f, 0.0f };
f32 D_00264A20[5] = { 1.3f, -0.2546479f, 0.0f, 0.0f, 0.1f };
f32 D_00264A34 = 20.0f;
f32 D_00264A38 = 20.0f;

extern f32 D_0026185C;

void func_001C6F48(void*);
void func_001C7140(void*);
void func_00124DF8(void* self, s32 n, void* table);
void func_001C72A0(void* self);
void func_001DDC38(void* sub, void* self);
void func_001D36F0(void* self, void* a, void* b);
void* func_001B6290(void* a, void* b, s32 c, s32 d);
s32 func_001CA758(void* self, s32 id);
u8* func_0018D568(s32 size, void* src);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);
s32 func_00141D00(void* self, void* p1, void* p2, f32 x, s32 p3, void* p4);
s32 func_001300E8(BaseObject* a, s32 b);
s32 func_001833F0(BaseObject* a, s32 b);
void func_0018D608(void* self, void* a1, void* a2);
void func_0018D6F0(void);
s32 func_00125750(void* a, s32 b, void* c, s32 d, s32 e, s32 f, f32 g);
void func_001B6598(void* dev, s32* out);
s32 func_001DDA80(void* p);
void func_001C91C8(void* self);
void func_001603E8(s32 n);
void func_0018C7F8(MemoryCard* p);
s32 func_001C96B8(void* self);
s32 func_001C8010(void* self);
void func_001AC060(void* p);
void func_001C8F20(void* node, s32 kind, s32 flag);
void func_001C7CB8(void);
s32 func_001E9970(void);
void func_001C9008(void*);
void func_001B64D8(s32, s32);
s32 func_001A8C90(void* obj, s32 v);
void func_001C9DE0(void* self, s32 code, void* req);

void func_0018A388(C0C* self)
{
	InitAgent(self);
	*(s32*)((char*)self + 0xE3C) = -1;
}

void func_0018A3B8(C0C* self)
{
    LoadAgent(self);
    ResolveObjectLinks(self, 2, D_00264910);
}

struct Ent_18A3F0 { s32 key; s32 pad4; s32 value; };

void func_0018A3F0(C0C* self)
{
    s32 n;
    s32 i;

    StartAgent(self);
    SetWorldActiveFollower(self->world, self);
    ResolveObjectLinks(self, 3, D_00264928);
    func_001D36F0(self, (u8*)self + 0xC20, (u8*)self + 0xE00);
    self->f758[12].obj = (void*)self->fE00;
    self->fE10 = CreateStateWalker(self->fE0C, 0, 0x438, 0);
    for (n = 0; n < 3; n++)
        self->fE30[n] = ResolveAgentClip(self, D_00264950[n]);
    self->fE20 = 6;
    self->fE24 = (Ent_18A3F0*)CopyToFrontMemory(0x48, D_00264960);
    for (i = 0; i < self->fE20; i++) {
        Ent_18A3F0* e = ((Ent_18A3F0*)self->fE24) + i;
        e->value = FindFirstObjectById(self->world, 1, e->key, self);
    }
}

INCLUDE_ASM(func_0018A510);

ASM_FUNC(func_0018A628);

struct __attribute__((aligned(16))) Cand_18A6C0 { u8 pad0[0x40]; f32 score; u8 pad1[0x70 - 0x44]; };

s32 func_0018A6C0(s32 a0, void* a1, void* a2, s32 a3, s32 a4, void* a5, f32 f)
{
    Cand_18A6C0 buf[2];
    s32* table = (s32*)a4;
    s32 best = 0;
    f32 bestScore = 3.4028234663852886e+38f;
    s32 i;

    for (i = 0; i < a3; i++) {
        s32 self = table[i];
        s32 r = func_00141D00((void*)self, a1, a2, f, 2, (void*)buf);
        s32 k = 0;
        if (r > 0) {
            if (buf[0].score == 0.0f && (a0 & 1)) {
                k = 1;
            }
        }
        if (k < r) {
            Cand_18A6C0* c = &buf[k];
            if (c->score < bestScore) {
                bestScore = c->score;
                best = self;
                if (a5 != 0) {
                    *(Cand_18A6C0*)a5 = *c;
                }
            }
        }
    }
    return best;
}

typedef s32 (*VFn_18A830)(BaseObject* self, void* arg);
struct Rec_18A830 { u8 pad[0x50]; BaseObject* sub; };

s32 func_0018A830(void* self, Rec_18A830* rec)
{
    s32* e = D_002649B0;
    u32 i;
    for (i = 0; i < 5; e++, i++) {
        if (IsObjectOfKind(rec->sub, *e) != 0) {
            break;
        }
    }
    if (i < 5) {
        return 0;
    }
    if (rec->sub->desc->id == 3) {
        return 0;
    }
    if (IsObjectOfKind(rec->sub, 0x34) != 0) {
        if (((VFn_18A830*)rec->sub->desc)[60](rec->sub, self) == 0) {
            return 0;
        }
    }
    if (MatchesObjectId(rec->sub, 0x449) != 0 || MatchesObjectId(rec->sub, 0x44A) != 0) {
        return 0;
    }
    return 1;
}

typedef s32 (*Cb_18A910)(void* self, Rec_18A830* ctx);

void func_001DC238(void* a0, s32 a1, void* a2, void* a3, Cb_18A910 a4, void* a5, s32* a6, s32* a7);

s32 func_0018A910(C0C* self, void* a1, void* a2)
{
    u8 buf[0x70];
    s32 x;
    s32 y;
    PushBackMemoryMark(self, a1, a2);
    func_001DC238(self->world, 0, a1, a2, IsGaugeAgentBlocker, self, &x, &y);
    s32 r = FindNearestHitObject(0, a1, a2, x, y, buf, D_002649C4);
    PopBackMemoryMark();
    return r != 0;
}

typedef void* (*FnSelf_18A9A8)(void* self);
typedef s32 (*FnSub_18A9A8)(void* self);

struct Loc_18A9A8 {
    u8 buf[0x10];
    s32 code;
};

s32 func_0018A9A8(C0C* self)
{
    u8* obj = (u8*)self;
    Loc_18A9A8 loc;
    void* sub;
    s32 code;

    if (g_gameTime < *(f32*)(obj + 0x748)) {
        return 0;
    }
    sub = ((FnSelf_18A9A8)(*(void***)obj)[0x198 / 4])(obj);
    if (sub == 0) {
        return 0;
    }
    if (*(u32*)((u8*)*(void**)sub + 8) & 8) {
        if (((FnSub_18A9A8)(*(void***)sub)[0x144 / 4])(sub)) {
            return 0;
        }
    }
    func_001B6598(*(void**)(obj + 0xE10), &loc.code);
    code = loc.code;
    if (code != 0x43C) {
        if (code < 0x43D) {
            if (code != 0x43A) {
                return 0;
            }
        } else {
            if (code == 0x43E) {
                goto one;
            }
            return 0;
        }
    }
    if (IsGaugeAgentLineBlocked((C0C*)obj, obj + 0x140, (u8*)sub + 0x140) != 0) {
        goto second;
    }
one:
    return 1;
second:
    func_00125750(sub, 0, loc.buf, 0, 0, 0, D_002649C8);
    if (IsGaugeAgentLineBlocked((C0C*)obj, obj + 0x140, loc.buf) == 0) {
        goto one;
    }
    return 0;
}

typedef s32 (*VFnI_0018AAE0)(void* self);

s32 func_0018AAE0(C0C* self)
{
    s32 out;
    if (func_001DDA80(self->world) != 0) goto zero;
    if (self->fC10 != 0) goto zero;
    if (self->f724 == 0x10) goto zero;
    if (self->f724 == 0xB) goto zero;
    if (((VFnI_0018AAE0*)self->desc)[0x66](self) == 0) goto zero;
    func_001B6598(self->fE10, &out);
    if (out == 0x43C) goto one;
    if (out < 0x43D) {
        if (out == 0x43A) goto one;
        goto zero;
    }
    if (out == 0x43E) goto one;
zero:
    return 0;
one:
    return 1;
}

void func_0018AB88(C0C* self)
{
    EnterAgentState(self);
    s32 st = self->f724;
    if (st != 0xB) {
        if (st == 0x10) {
            s32 n = self->fA68;
            self->fC04 = 0;
            self->fA68 = n + 1;
        }
    } else {
        MarkLevelDone(2);
        StartMemoryCardSave(&g_memoryCard);
    }
}

s32 func_0018ABF0(C0C* self)
{
    if (self->f724 == 4) {
        s32 kind;
        func_001B6598(self->fE10, &kind);
        if (kind == 0x438) {
            if (func_001C96B8(self) == 0)
                return 2;
        }
    }
    return ChooseAgentState(self);
}

void func_0018AC58(C0C* self)
{
    DecrementGaugeCount((u8*)&g_gaugeBarElement);
    s32 idx = self->fE28;
    ChangeAgentState(self, D_002649D8[idx], self->fE30[idx]);
    s32 n = self->fE28;
    self->fE3C = D_002649E8[n];
    self->fE28 = n + 1;
}

void func_0018ACD0(void)
{
    UpdateAgent();
}

void func_0018ACF0(C0C* self)
{
    s32 kind;
    func_001B6598(self->fE10, &kind);
    s32 pick = 0;
    switch (kind) {
    case 0x43A:
    case 0x43C:
    case 0x43E:
        pick = AreMenusAndFadeClear();
        break;
    default:
        break;
    }
    if (pick)
        g_gaugeBarElement.vt->m14(&g_gaugeBarElement);
    else
        g_gaugeBarElement.vt->m15(&g_gaugeBarElement);
}

INCLUDE_ASM(func_0018AD88);

ASM_FUNC(func_0018AE38);

void func_0018B2E8(C0C* self)
{
    LeaveAgentState(self);
    if (self->f724 == 16) {
        s32 token = self->fE3C;
        if (token == -1) return;
        SetStateWalkerTarget((s32)self->fE10, token);
        self->fE3C = -1;
    }
}

struct __attribute__((aligned(16))) Quad_18B340 { s32 w[4]; };

struct Key_18B340 {
    s32 a;
    s32 pad0;
    s32 b;
};

struct Obj_18B340 {
    u8 pad0[0xF0];
    Quad_18B340 fF0;
};

void func_0018B340(C0C* self, s32 a1, Key_18B340* key)
{
    if (a1 == 0x13 && key->a == (s32)self->f7E0) {
        switch (key->b) {
        case 0x442:
        case 0x443: {
            Obj_18B340* obj;
            if (key->b == 0x442) {
                obj = (Obj_18B340*)self->fE18;
            } else {
                obj = (Obj_18B340*)self->fE1C;
            }
            s32 kind;
            func_001B6598(self->fE10, &kind);
            switch (kind) {
            case 0x43A:
            case 0x43C:
                obj->fF0 = (*(Quad_18B340*)&self->vE40);
                *(f32*)((u8*)obj + 0xF8) = self->v140.z + D_00264A34;
                break;
            case 0x43E:
                obj->fF0 = (*(Quad_18B340*)&self->vE40);
                *(f32*)((u8*)obj + 0xF8) = *(f32*)((u8*)obj + 0xF8) + D_00264A38;
                break;
            }
            func_001A8C90(obj, 1);
            return;
        }
        case 0x444:
            self->fE2C = 1;
            break;
        case 0x445:
            self->fE2C = 0;
            break;
        }
    }
    HandleAgentNotification(self, a1, key);
}

// Hoisting 1.0f into a local `one` matched the constant scheduling.
void func_0018B460(C0C* a0, f32* a1)
{
    s32 kind;
    func_001B6598(a0->fE10, &kind);
    switch (kind) {
    case 0x43A:
        {
            f32 v = g_currentEntry->dt * 1.3f - 0.3f;
            f32 one = 1.0f;
            if (v < 0.0f) {
                v = 0.0f;
            } else if (one < v) {
                v = one;
            }
            *a1 = v;
        }
        break;
    case 0x43C:
        {
            f32 v = g_currentEntry->dt * 1.3f - 0.3f;
            f32 one = 1.0f;
            if (v < 0.0f) {
                v = 0.0f;
            } else if (one < v) {
                v = one;
            }
            *a1 = v;
        }
        break;
    default:
        *a1 = g_currentEntry->dt * g_currentEntry->dt;
        break;
    }
}
