// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
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
#include "game_clock.h"

s32 D_00274FA0[2] = {286, 287};
s32 D_00274FA8[2] = {288, 289};
s32 D_00274FB0[2] = {2, 2};
s32 D_00274FB8[2] = {48, 64};

struct PlayerTableEntry { s32 id; f32 v; s32 object; };
PlayerTableEntry D_00274FC0[8] = {
    { 0x35, 30.0f, 0 }, { 0x36, 30.0f, 0 }, { 0x37, 30.0f, 0 }, { 0x3A, 30.0f, 0 },
    { 0x50, 60.0f, 0 }, { 0x58, 30.0f, 0 }, { 0x170, 30.0f, 0 }, { 0, 0.0f, 0 }
};
float D_00275020[4] = {0.0f, 10.0f, 0.00999999978f, 0.0f};
f32 D_00275030[4] = { 3.5f, 0.0f, 0.5f, 0.0f };
f32 D_00275040[4] = { 0.0f, 0.0f, -1000.0f, 0.0f };
f32 D_00275050[4] = { -0.5f, -0.0025f, 0.0f, 0.0f };
f32 D_00275060[2] = { 0.0f, 0.7f };
f32 D_00275068[1] = { 0 };
float D_0027506C = 0.25f;
float D_00275070[14] = {0.0f, 1.0f, 0.781831503f, 0.623489797f, 0.974927902f, -0.222520933f, 0.433883727f, -0.90096885f, -0.433883727f, -0.90096885f, -0.974927902f, -0.222520933f, -0.781831503f, 0.623489797f};
float D_002750A8[34] = {1.0f, 0.0f, 0.932472229f, 0.361241668f, 0.739008904f, 0.673695624f, 0.445738345f, 0.895163298f, 0.0922683626f, 0.995734155f, -0.273662984f, 0.961825669f, -0.602634609f, 0.798017204f, -0.850217164f, 0.526432157f, -0.982973099f, 0.183749512f, -0.982973099f, -0.183749512f, -0.850217164f, -0.526432157f, -0.602634609f, -0.798017204f, -0.273662984f, -0.961825669f, 0.0922683626f, -0.995734155f, 0.445738345f, -0.895163298f, 0.739008904f, -0.673695624f, 0.932472229f, -0.361241668f};
s32 D_00275130 = 0;
s32 D_00275134 = 0;
s32 D_00275138 = 0;

ASM_FUNC(func_001D36F0);
ASM_FUNC(func_001D39E0);
ASM_FUNC(func_001D3A38);
ASM_FUNC(func_001D3B58);

f32 func_001FD578(u64 v);

s32 func_001D3C68(s32 stride, s32 n, s32 m, char* out, ...) {
    f32 rows[16];
    f32 cols[16];
    u64* ap = (u64*)((char*)__builtin_next_arg(out) - 32);
    f32 sum = 0.0f;
    s32 i;
    s32 j;
    s32 changed;
    for (i = 1; i < n; i++) {
        ap++;
        rows[i] = func_001FD578(ap[-1]);
        sum += rows[i];
    }
    rows[0] = 1.0f - sum;
    sum = 0.0f;
    for (j = 1; j < m; j++) {
        ap++;
        cols[j] = func_001FD578(ap[-1]);
        sum += cols[j];
    }
    cols[0] = 1.0f - sum;
    char* p = out;
    changed = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            sum = rows[i] * cols[j];
            if (sum != *(f32*)p) {
                *(f32*)p = sum;
                changed = 1;
            }
            p += stride;
        }
    }
    return changed;
}

ASM_FUNC(func_001D3E00);

struct Obj_1D40A0 {
    f32 f0;
    u8 pad4[0x4C];
    f32 f50;
    s32 f54;
    u8 pad58[0x48];
    s32 fA0;
    u8 padA4[0x4C];
    s32 fF0;
    u8 padF4[0x4C];
    s32 f140;
    u8 pad144[0x4C];
    s32 f190;
};

struct Sub_1D40A0 {
    u8 pad0[0x8];
    s32 f8;
};

struct Ctx_1D40A0 {
    u8 pad0[0xC0];
    Sub_1D40A0* sub;
};

void func_001399F8(void* obj, s32 a1, s32 a2, void* a3);
void func_001D39E0(s32 a0, void* a1, s32 a2, void* a3);

void func_001D40A0(TurningCollider* a0, Obj_1D40A0* a1, Ctx_1D40A0* a2, f32 f12, f32 f13)
{
    a0->f638 = f12;
    if (a1->f54 == 0) {
        a1->f0 = 1.0f;
        a1->f50 = 0.0f;
    } else {
        f32 one = 1.0f;
        a1->f50 = f13;
        a1->f0 = one - f13;
    }
    a1->fA0 = 0;
    a1->f140 = 0;
    a1->fF0 = 0;
    a1->f190 = 0;
    func_001399F8(a2, 0x50, 6, a1);
    func_001D39E0(6, a1, a2->sub->f8, &a0->f640);
}

INCLUDE_RODATA(jtbl_0024DBD0);
ASM_FUNC(func_001D4148);
ASM_FUNC(func_001D4348);
ASM_FUNC(func_001D4698);



u8* func_0018D568(s32 size, void* src);
s32 func_0015A418(void* host, s32 a1, s32 a2, void* ctx);

void func_001D4848(Player* self)
{
    self->f26A8 = 7;
    self->f26AC = CopyToFrontMemory(0x54, g_playerObjectTable);
    for (s32 i = 0; i < self->f26A8; i++) {
        PlayerTableEntry* it = (PlayerTableEntry*)self->f26AC + i;
        it->object = FindFirstObjectById(self->world, 1, it->id, self);
    }
}


INCLUDE_RODATA(jtbl_0024DBF0);
ASM_FUNC(func_001D48E8);

f32 func_00205778(f32 a, f32 b);
f32 func_001EA728(f32* p, s32 a, f32 b, f32 c, f32 d);
s32 func_001300E8(void* e, s32 k);
void func_001D4C98(Player* self);
void func_00175170(Player* self, s32 a, s32 b);
s32 func_001CF158(Player* self, void* b);
void func_001782C0(Player* self, void* s2, f32 f, void* a2, void* a3, void* a4);

void func_001D4A98(Player* self) {
    switch (self->f2228) {
    case 0x2B: {
        f32 t = func_00205778(self->v150.y, self->v150.x);
        self->f638 = ApproachAngleWithRamp(D_00275030, 0, self->f638, t + 3.1415927f, g_gameClock.dt);
        if (0.25f < g_gameClock.time - self->f222C && self->f690 != 0) {

            RunPlayerCallback(self);
        }
        break;
    }
    case 0x2C: {
        if (*(f32*)((u8*)self->f2514 + 0x18) < g_gameClock.time) {
            RunPlayerCallback(self);
        } else if (self->f2B70 != 0 && *(f32*)((u8*)self->f2514 + 0x18) < g_gameClock.time + 0.25f &&
                   (IsObjectOfKind(self->f2B70, 0x76) || IsObjectOfKind(self->f2B70, 0x70) ||
                    IsObjectOfKind(self->f2B70, 0x71) || IsObjectOfKind(self->f2B70, 0x81) ||
                    IsObjectOfKind(self->f2B70, 0x6F) || IsObjectOfKind(self->f2B70, 0x7F))) {
            if (self->f26B0 != 0) {
                RunPlayerCallback(self);
            } else {
                void* o = self->f2B70;
                func_00175170(self, 2, 2);
                s32 r = func_001CF158(self, o);
                func_00175170(self, 2, r);
            }
        } else {
            func_001782C0(self, &self->f2B70, *(f32*)((u8*)self->f2514 + 0x18) - g_gameClock.time, 0, (u8*)self->f2514 + 0x20, 0);
        }
        break;
    }
    }
}

void func_001D4C90(Player* self, s32 value)
{
    self->f26B0 = value;
}

extern void func_001D5620(Player* self);
extern void func_00175170(Player* self, s32 mode, s32 count);

void func_001D4C98(Player* self)
{
    s32 v = self->f2254;
    void (*fn)(Player* self) = self->cb26B0;

    v &= -0x11;
    self->cb26B0 = 0;

    self->f2254 = v;
    if (fn != 0) {
        fn(self);
        return;
    }
    if ((u32)(self->f2228 - 0x2D) < 5) {
        EndPlayerRequestState(self);
    } else {
        func_00175170(self, 2, 2);
    }
}

void func_001D51A0(Player* self);
void func_001D5398(Player* self);
void func_001D5418(Player* self);
void func_001D5468(Player* self);
void func_001D6608(void);

typedef void (*PlayerRequestFn)(s32 data, Player* self);
struct PlayerRequestMessage { Player* self; s32 v; };

void func_001837E0(s32 target, s32 a, s32 b, Ev07** c);
void func_00175170(Player* self, s32 a, s32 b);
void func_001D4C90(Player* self, s32 value);
s32 func_001DDA80(s32 p);
s32 func_00160D10(void);
s32 func_00160C58(void);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);
extern u32 D_00262C64;
extern f32 D_0026185C[];

s32 func_001D4D08(Player* self, Ev07* msg)
{
    if (self->desc05()->m4B(self, msg->kind) != 0) {
        return 0;
    }
    if (self->f2220 == 6 && self->f239C == 2) {
        Ev07* tmp = msg;
        TriggerScriptEvent((s32)self->f23B0, 0x13, 1, &tmp);
        func_00175170(self, 2, 5);
        return 0;
    }
    self->f26B4 = *msg;
    if (self->f2220 != 4 && self->f2220 != 0xB && self->f26C4 == 0 && (g_buttonCodeFlags & 1) == 0 &&
        func_001DDA80((s32)self->world) == 0) {
        s32 c;
        switch (self->f26B4.kind) {
        case 3:
            c = func_00160D10() & 0x100;
            break;
        case 5:
            c = func_00160D10() & 0x4000;
            break;
        default:
            self->f2730 = 1;
            goto check;
        }
        if (c == 0) {
            self->f2730 = 1;
        }
    check:
        if (self->f2730 != 0) {
            if (func_00160C58() != 0) {
                self->f26C4 = 1;
                self->f26C8 = g_gameTime[0];
            }
        }
    }
    SetPlayerCallback(self, 0);
    switch (msg->kind) {
    case 0:
        StartSoundEffect(0xA3, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        {
            PlayerRequestFn fn = (PlayerRequestFn)self->f26B4.fn;
            if (fn != 0) {
                self->f26B4.fn = 0;
                fn(self->f26B4.data, self);
            } else {
                func_00175170(self, 4, 0x2B);
            }
        }
        SetPlayerCallback(self, (s32)ContinuePlayerRequestKind0);
        break;
    case 6:
        {
            PlayerRequestFn fn = (PlayerRequestFn)self->f26B4.fn;
            if (fn != 0) {
                self->f26B4.fn = 0;
                fn(self->f26B4.data, self);
            } else {
                func_00175170(self, 4, 0x2B);
            }
        }
        if (400.0f < self->v150.z) {
            StartSoundEffect(0xA3, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
        SetPlayerCallback(self, (s32)ContinuePlayerRequestKind6);
        break;
    case 1:
    case 2: {
        s32 id;
        if (self->f2220 == 0xD) {
            (*(Quad16*)&self->v2BB0) = (*(Quad16*)&self->v2BC0) = *(const Quad16*)&D_00248D30;
        } else {
            (*(Quad16*)&self->v2BB0) = (*(Quad16*)&self->v150);
            (*(Quad16*)&self->v2BC0) = (*(Quad16*)&self->v160);
        }
        self->desc02()->m20(self, (Vec02*)&D_00248D30);
        self->desc02()->m21(self, (Vec02*)&D_00248D30);
        switch (msg->kind) {
        case 1:
            id = 0x25;
            break;
        case 2:
            id = 0x26;
            break;
        }
        func_00175170(self, 4, id);
        SetPlayerCallback(self, (s32)ContinuePlayerRequestKind1Or2);
        break;
    }
    case 3:
        if (self->f2730 == 0 || func_00160C58() != 0) {
            func_00175170(self, 4, 0x27);
            SetPlayerCallback(self, (s32)FinishPlayerRequest);
        } else {
            func_00175170(self, 4, 0x2F);
        }
        break;
    case 4:
        self->desc02()->m20(self, (Vec02*)D_00275040);
        if (func_00160C58() != 0) {
            func_00175170(self, 4, 0x28);
            SetPlayerCallback(self, (s32)FinishPlayerRequest);
        } else {
            func_00175170(self, 4, 0x31);
        }
        break;
    case 5:
        if (self->f2730 == 0 || func_00160C58() != 0) {
            func_00175170(self, 4, 0x29);
            SetPlayerCallback(self, (s32)FinishPlayerRequest);
        } else {
            func_00175170(self, 4, 0x30);
        }
        break;
    }
    if (self->f2730 != 0) {
        PlayerRequestMessage m;
        m.self = self;
        m.v = msg->arg;
        self->desc->m0E(self, 0x17, &m);
    }
    return self->f2730;
}

s32 func_00160C58(void);
void func_00192C58(Player* o);
void func_00175170(Player* o, s32 a, s32 b);
s32 func_001CF158(Player* o, void* p);
void func_001D4C90(Player* o, s32 value);
void func_001D6608(void);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, s32 a4, s32 a5);

void func_001D51A0(Player* self)
{
    if (self->f2228 == 0x2C && self->f2B70 != 0 &&
        (IsObjectOfKind(self->f2B70, 0x70) || IsObjectOfKind(self->f2B70, 0x71) ||
         IsObjectOfKind(self->f2B70, 0x81) || IsObjectOfKind(self->f2B70, 0x6F) ||
         IsObjectOfKind(self->f2B70, 0x7F) || IsObjectOfKind(self->f2B70, 0x76))) {
        if (func_00160C58()) {
            func_00192C58(self);
            void* p = self->f2B70;
            func_00175170(self, 2, 2);
            func_00175170(self, 2, func_001CF158(self, p));
        } else {
            func_00175170(self, 4, 0x2D);
        }
    } else {
        if (func_00160C58()) {
            func_00175170(self, 4, 0x24);
            SetPlayerCallback(self, (s32)FinishPlayerRequest);
        } else {
            func_00175170(self, 4, 0x2D);
        }
    }
    if (self->f2220 == 4) {
        f32 t = self->v150.z;
        f32 x = D_00275050[0] + t * (D_00275050[1] + t * D_00275050[2]);
        f32 lo = D_00275060[0];
        f32 hi = D_00275060[1];
        if (x < lo) {
            x = lo;
        } else if (hi < x) {
            x = hi;
        }
        f32 z = 0.0f;
        StartSoundEffect(0x49, 0, 0, 0, z, z, x, D_00275068[0], z, 0, 0);
    }
}

void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);

void func_001D5398(Player* self)
{
    StartSoundEffect(0xA6, 0, 0, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f);
    func_00175170(self, 4, 0x2A);
    SetPlayerCallback(self, (s32)ContinuePlayerSubState2A);
}

void func_001D5418(Player* self)
{
    if (func_00160C58()) {
        self->desc05()->m50(self);
    } else {
        func_00175170(self, 4, 0x2D);
    }
}

void func_001D5468(Player* self)
{
    self->desc02()->m20(self, &self->v2BB0);
    self->desc02()->m21(self, &self->v2BC0);
    if (func_00160C58()) {
        self->desc05()->m50(self);
    } else {
        func_00175170(self, 4, 0x2D);
    }
}

struct PlayerWorld;
s32 func_001DDA80(PlayerWorld* k);
extern u32 D_00262C64;

s32 func_001D54E0(Player* self, s32 n)
{
    s32 v;
    s32 k;
    if (n == 3 || n == 5) {
        switch (self->f2220) {
        case 4:
            switch (self->f2228) {
            case 0x27:
            case 0x29:
            case 0x2C:
            case 0x2F:
            case 0x30:
                return 1;
            case 0x28:
            case 0x2A:
            case 0x2B:
            case 0x2D:
            case 0x2E:
            default:
                return 0;
            }
        case 6:
            k = self->f239C;
            if (k != 3) { if (k != 6) return 1; }
            return 0;
        case 2:
            if (self->f2228 < 16) {
                if (!(self->f2228 < 9)) return 1;
            }
        case 5:
        default: {
            s32 r = 0;
            if (self->f2220 == 11) goto set;
            if (func_001DDA80((PlayerWorld*)self->world) != 0) {
set:
                r = 1;
            }
            return r;
        }
        case 3:
        case 7:
        case 8:
            goto one;
        }
    }
    v = self->f2220;
    if (v == 4) goto one;
    if (v == 11) goto one;
    if (self->f26C4 != 0) goto one;
    if ((g_buttonCodeFlags & 1) != 0) goto one;
    if (func_001DDA80((PlayerWorld*)self->world) != 0) goto one;
    goto zero;
one:
    return 1;
zero:
    return 0;
}

void func_0012AAE8(void* self, f32 value);
void func_00160DA0(void);

void func_001D5620(void* self)
{
    func_0012AAE8(self, 1.0f);
    func_00160DA0();
}

struct SortedTarget { u8 pad[0x10]; f32 key; };
s32 func_001D5650(SortedTarget* a, SortedTarget* b) { if (a->key < b->key) return -1; return 1; }


INCLUDE_RODATA(D_0024DC88);
ASM_FUNC(func_001D5678);


INCLUDE_ASM(func_001D5FA8);
INCLUDE_ASM(func_001D60B0);
INCLUDE_ASM(func_001D61C8);
