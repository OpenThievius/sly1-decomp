// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "button_code.h"
#include "globals.h"
#include "game_clock.h"
#include "pad_record.h"
#include "game_progress.h"
#include "asm_func.h"

// The pad and button-code file: the pad records D_00262C70 and D_00262D38, their connection
// state machine and input polling, the repeating step readers, and the cheat-code list with its
// nine slots. Its .rodata is the password message (0x24A848); its .data runs from 0x262A30 to
// 0x262E10, in retail's order: the stick-response floats func_0016E738 reads, the button masks,
// the code sequences with their slots, the flags, the two records, the list head and the timer.

extern const char D_0024A848[24] = "The password is: %s";
f32 D_00262A30[8] = { 1.0f, 0.0f, 0.0f, 1.0f, 0.699999988f, 0.699999988f, 0.699999988f, -0.699999988f };

u16 D_00262A50[12] = { 0x2000, 0x8000, 0x1000, 0x4000, 0x0010, 0x0020, 0x0040, 0x0080, 0x0004, 0x0008, 0x0001, 0x0002 };
u32 D_00262A68[6] = { 0x14000, 0x400002, 0x14000, 0x400002, 0x208000, 0x100 };

void func_001E5278(s32 mode);
void func_0016F408(void);
void func_0016F430(s32 flags);
void func_0016F478(void);
void func_00199F38(void);
void func_00199FF0(void);
void func_0019A0F0(void);
ButtonCodeSlot D_00262A80 = { { (const u16*)D_00262A68, 0xB, (ButtonCodeFn)func_001E5278, 0x0 } };
u32 D_00262AA0[6] = { 0x14000, 0x400002, 0x14000, 0x400002, 0x208000, 0x800 };
ButtonCodeSlot D_00262AB8 = { { (const u16*)D_00262AA0, 0xB, (ButtonCodeFn)func_0016F408, 0x0 } };
u32 D_00262AD8[6] = { 0x14000, 0x400002, 0x14000, 0x400002, 0x208000, 0x8000 };
ButtonCodeSlot D_00262AF0 = { { (const u16*)D_00262AD8, 0xB, (ButtonCodeFn)func_0016F430, 0x4004 } };
u32 D_00262B10[6] = { 0x14000, 0x400002, 0x14000, 0x400002, 0x208000, 0x2000 };
ButtonCodeSlot D_00262B28 = { { (const u16*)D_00262B10, 0xB, (ButtonCodeFn)func_0016F430, 0x8 } };
u32 D_00262B48[6] = { 0x14000, 0x400002, 0x14000, 0x400002, 0x208000, 0x20 };
ButtonCodeSlot D_00262B60 = { { (const u16*)D_00262B48, 0xB, (ButtonCodeFn)func_0016F430, 0x2 } };
u32 D_00262B80[6] = { 0x14000, 0x400002, 0x14000, 0x400002, 0x208000, 0x1000 };
ButtonCodeSlot D_00262B98 = { { (const u16*)D_00262B80, 0xB, (ButtonCodeFn)func_00199F38, 0x0 } };
u32 D_00262BB8[6] = { 0x14000, 0x400002, 0x14000, 0x400002, 0x208000, 0x4000 };
ButtonCodeSlot D_00262BD0 = { { (const u16*)D_00262BB8, 0xB, (ButtonCodeFn)func_00199FF0, 0xF000FFFF } };
u32 D_00262BF0[6] = { 0x14000, 0x400002, 0x14000, 0x400002, 0x208000, 0x10 };
ButtonCodeSlot D_00262C08 = { { (const u16*)D_00262BF0, 0xB, (ButtonCodeFn)func_0019A0F0, 0x0 } };
u32 D_00262C28[8] = { 0x14000, 0x400002, 0x14000, 0x400002, 0x208000, 0x800080, 0x80, 0x0 };
ButtonCode D_00262C48 = { (const u16*)D_00262C28, 0xD, (ButtonCodeFn)func_0016F478, 0x0 };
// size: s32 flags, word accesses only
s32 D_00262C64 = 0;
// size: s32 flags, word accesses only
s32 D_00262C68 = 0;
// size: s32 flags, word accesses only
s32 D_00262C6C = 0;
PadRecord D_00262C70 = {};
// size: chosen with D_00262C70 as the same pad pointer (conditional), 0xC4 to the next label
PadRecord D_00262D38 = {};

ButtonCode* D_00262DFC = 0;

extern f32 D_00261868[];
struct Next_262E00 { f32 time; f32 pad[3]; };
Next_262E00 D_00262E00 = { 0.0f, { 0.0f, 0.0f, 0.0f } };

void func_0016E148(void);
s32 func_002040E8(void* a);
void func_0016E1A0(PadRecord* self, s32 a, s32 b);

void func_0016E0B8(void)
{
    func_0016E148();
    func_002040E8(0);
    InitPadRecord(&g_padRecord, 0, 0);
}

extern s32 D_00262C6C;

void func_0016E148();

s32 func_0016E0F0(s32 bits)
{
    D_00262C6C |= bits;
    return ((s32 (*)())func_0016E148)();
}

void func_0016E148(void);

void func_0016E118(u32 mask)
{
    mask = ~mask;
    D_00262C6C = D_00262C6C & mask;
    func_0016E148();
}

extern s32 D_00262C6C;
extern s32 D_00262C68;

void func_0016E148()
{
    s32 flags = D_00262C6C;
    if ((flags & 0x84) != 0)
    {
        D_00262C68 = 0;
        return;
    }
    if ((flags & 1) != 0)
    {
        D_00262C68 = 5;
        return;
    }
    if ((flags & 2) != 0)
    {
        D_00262C68 = 4;
        return;
    }
    D_00262C68 = 7;
}

void func_001F5C0C(void* p, s32 value, s32 size);
void* func_0018D4B0(s32 size);
void func_002042C8(s32 a, s32 b, s32 c);
void func_0016E630(PadRecord* self, s32 mode, s32 n);

void func_0016E1A0(PadRecord* self, s32 a, s32 b)
{
    func_001F5C0C(self, 0, 0xC4);
    SetPadConnectionState(self, 1, 0);
    self->f04 = a;
    self->f08 = b;
    s32 size = ((s32)ReservePermanentMemory(0x140) + 0x3F) & -0x40;
    self->f0C = size;
    func_002042C8(self->f04, self->f08, size);
    self->fBC = ReservePermanentMemory(0x20);
    self->fC0 = 1;
}

s32 func_00204590(s32 a, s32 b);
s32 func_002047F8(s32 a, s32 b, s32 c, s32 d);
s32 func_00204930(s32 a, s32 b, s32 c, s32 d);
s32 func_002046D0(s32 a, s32 b, s32 c, s32 d);
void func_001F5C0C(u8* p, s32 value, s32 size);
s32 func_00204AA8(s32 a, s32 b, u8* buf);
s32 func_00204CE8(s32 a, s32 b);
s32 func_00204D48(s32 a, s32 b);
s32 func_00204678(s32 a, s32 b);
s32 func_0016E940(PadRecord* self);
void func_001A7B88(void* p);
void func_0016E630(PadRecord* self, s32 mode, s32 n);

void func_0016E238(PadRecord* self)
{
    u8 buf[16];
    if (self->f14 == 0)
    {
        return;
    }
    s32 ready = 0;
    s32 r = func_00204590(self->f04, self->f08);
    if (r == 6 || r == 2)
    {
        ready = 1;
    }
    s32 cur = self->f18;
    if (self->f14 != 3 && cur != 0 && 2.0f <= g_gameClock.elapsed - self->f1C)
    {
        r = 0;
    }
    if (cur != 0 && r == 0)
    {
        SetPadConnectionState(self, 1, 0);
    }
    if (!ready)
    {
        return;
    }
    s32 two = 2;
    s32 mode = self->f14;
    s32 n = self->f18;
    switch (mode)
    {
    case 1:
        switch (n)
        {
        case 0:
        {
            s32 a = func_002047F8(self->f04, self->f08, 1, 0);
            if (a != 0)
            {
                s32 b = func_002047F8(self->f04, self->f08, 2, 0);
                if (b > 0)
                {
                    a = b;
                }
                if (a == 4 || a == 7)
                {
                    n = 1;
                    mode = 3;
                    if (b != 0)
                    {
                        mode = n;
                    }
                }
            }
            break;
        }
        case 1:
            mode = (func_00204930(self->f04, self->f08, 1, 3) == 1) ? two : n;
            break;
        case 2:
        {
            s32 count = func_002046D0(self->f04, self->f08, -1, 0);
            if (count != n
                || func_002046D0(self->f04, self->f08, 0, 1) != mode
                || func_002046D0(self->f04, self->f08, 0, 2) != n
                || func_002046D0(self->f04, self->f08, 0, 3) != 0
                || func_002046D0(self->f04, self->f08, 1, 1) != mode
                || func_002046D0(self->f04, self->f08, 1, 2) != mode
                || func_002046D0(self->f04, self->f08, 1, 3) != mode)
            {
                mode = 3;
                break;
            }
            func_001F5C0C(buf, 0xFF, 6);
            for (s32 i = 0; i < count; i++)
            {
                buf[i] = i;
            }
            if (func_00204AA8(self->f04, self->f08, buf) == 1)
            {
                mode = 2;
            }
            break;
        }
        case 3:
            if (func_00204CE8(self->f04, self->f08) != mode)
            {
                mode = 3;
                break;
            }
            if (func_00204D48(self->f04, self->f08) == 1)
            {
                mode = two;
            }
            break;
        }
        break;
    case 2:
        switch (func_00204678(self->f04, self->f08))
        {
        case 0:
            switch (self->f18)
            {
            case 1:
                n = 2;
                mode = 1;
                break;
            case 2:
                n = 3;
                mode = 1;
                break;
            case 3:
                n = 4;
                mode = 3;
                break;
            default:
                n = 0;
                break;
            }
            break;
        case 1:
            mode = 1;
            break;
        case 2:
            break;
        default:
            n = 0;
            break;
        }
        break;
    case 3:
        if (PollPadInput(self) != 0)
        {
            if (self->fC0 != 0 && self->f18 >= 3)
            {
                UpdatePadPattern(self->fBC);
            }
        }
        else
        {
            mode = 1;
            n = 0;
        }
        break;
    }
    SetPadConnectionState(self, mode, n);
}

void func_001A7B20(void* a, s32 b, s32 c);

void func_0016E630(PadRecord* self, s32 mode, s32 n)
{
    s32 next = mode;
    if (mode == self->f14)
    {
        if (n == self->f18)
        {
            return;
        }
    }
    if (n == 0)
    {
        self->f10 = 0;
        next = 1;
    }
    if (self->f18 < 3 && n >= 3)
    {
        RequestPadPattern(self->fBC, self->f04, self->f08);
    }
    if (next == 3)
    {
        self->f20 = 0;
        self->f84 = 0;
        self->f50 = 0;
        self->fA8 = 0;
        for (u32 i = 0; i < 4; i++)
        {
            self->a88[i].lo = -0.75f;
            self->a54[i].lo = -0.75f;
            self->a88[i].hi = 0.75f;
            self->a54[i].hi = 0.75f;
        }
    }
    self->f14 = next;
    self->f18 = n;
    self->f1C = g_gameClock.elapsed;
}

INCLUDE_ASM(func_0016E738);

void func_001F5C0C(u8* p, s32 a, s32 b);
s32 func_00204510(s32 a, s32 b, u8* c);
void func_0018D800(u8* dst, u8* src, s32 n);
void func_0016E738(PadRecord* p, s32 a, s32 b, f32* c, f32* d, f32* e, u8* f, u8* g, f32* h, f32* i);
void func_0016F238(PadRecord* p, s32 old);

s32 func_0016E940(PadRecord* self)
{
    u8 buf[0x40];
    s32 res;
    u16 old;
    u16 cur;

    u8* b = buf;
    func_001F5C0C(b, 0, 0x40);
    res = 1;
    if (func_00204510(self->f04, self->f08, b) > 0) {
        old = self->keyA8;
        self->keyA8 = ~((buf[2] << 8) | buf[3]);
        if (self->f10 != 0) {
            if (self->f10 != buf[1]) res = 0;
        }
        self->f10 = buf[1];
        if (self->f18 == 4) {
            CopyMemory(self->fAE, buf + 8, 0xC);
        }
        cur = self->keyA8;
        self->flags = cur & ~old;
        self->hAC = old & ~cur;
        if (self->f18 >= 2) {
            func_0016E738(self, buf[6], buf[7], &self->f40, &self->f44, &self->f48, &self->f4C, &self->f4D, &self->x50, &self->a54[0].lo);
            func_0016E738(self, buf[4], buf[5], &self->f74, &self->f78, &self->f7C, &self->f80, &self->f81, &self->x84, &self->a88[0].lo);
        } else {
            self->f74 = self->f78 = self->f7C = self->f40 = self->f44 = self->f48 = 0.0f;
        }
        if (g_camera == 0 || g_camera->stackCount == 0 || g_camera->stack[0].ctl != &g_camera->ctl454) {
            if ((self->keyA8 & 0xF000) != 0) {
                self->f40 = self->f44 = self->f48 = 0.0f;
                if ((self->keyA8 & 0x8000) != 0) {
                    self->f40 = -1.0f;
                } else if ((self->keyA8 & 0x2000) != 0) {
                    self->f40 = 1.0f;
                }
                if ((self->keyA8 & 0x1000) != 0) {
                    self->f44 = 1.0f;
                } else if ((self->keyA8 & 0x4000) != 0) {
                    self->f44 = -1.0f;
                }
                if (self->f40 * self->f44 != 0.0f) {
                    self->f40 = self->f40 * 0.8f;
                    self->f44 = self->f44 * 0.8f;
                }
                self->f48 = 1.0f;
            }
        }
        AdvanceButtonCodes(self, old);
        self->x20 = g_gameClock.elapsed;
        if (self->keyA8 != 0 || self->f48 != 0.0f || self->f7C != 0.0f) {
            self->f24 = g_gameClock.elapsed;
        }
    } else {
        if (g_elapsedTime[0] - self->x20 >= 2.0f) res = 0;
    }
    return res;
}

void func_0016EC20(PadRecord* self, u32 mask)
{
    u16 m = (u16)mask;
    self->flags &= (u16)~m;
}

void func_001A7CE8(void* p);

void func_0016EC38(PadRecord* self)
{
    if (self->pC0 == 0) return;
    if (self->f18 < 3) return;
    if (self->f14 != 3) return;
    StartPadPatternFromTable(self->fBC);
}

LINKER_REMNANT(func_0016EC80);

void func_0016EC88(PadRecord* p) { p->f28 = 0; p->f2C = 0; }

struct Obj_16EC98 { u8 pad0[0x28]; s32 f28; f32 f2C_unused; f32 f30; f32 f34; u8 pad1[8]; f32 f40; f32 f44; f32 f48; u8 pad2[0x5C]; u16 fA8; u16 fAA; };

void func_0016EC20(Obj_16EC98* self, s32 mask);
extern f32 D_00261868[];

s32 func_0016EC98(Obj_16EC98* self)
{
    f32 c;
    f32 base;
    if (self->f28 == 0) {
        u16 fl = self->fAA;
        if (fl & 0x8000) {
            ClearPadPressedBits(self, 0x8000);
            self->f28 = -1;
        } else if (fl & 0x2000) {
            ClearPadPressedBits(self, 0x2000);
            self->f28 = 1;
        } else if (0.8f <= self->f48) {
            f32 a = fabsf(self->f40);
            f32 b = fabsf(self->f44);
            if (b < a) {
                if (self->f40 < 0.0f) {
                    self->f28 = -1;
                } else {
                    self->f28 = 1;
                }
            }
        }
        if (self->f28 == 0) {
            goto done;
        }
        c = 0.33329999446868896f;
        self->f34 = c;
        base = g_elapsedTime[0];
    } else {
        s32 v1 = 0;
        if (self->f28 < 0) {
            if (self->fA8 & 0x8000) {
                v1 = 1;
            } else if (0.25f <= self->f48) {
                f32 a = fabsf(self->f40);
                f32 b = fabsf(self->f44);
                if (b < a) {
                    if (self->f40 < 0.0f) v1 = 1;
                }
            }
        } else {
            if (self->fA8 & 0x2000) {
                v1 = 1;
            } else if (0.25f <= self->f48) {
                f32 a = fabsf(self->f40);
                f32 b = fabsf(self->f44);
                if (b < a) {
                    if (0.0f < self->f40) v1 = 1;
                }
            }
        }
        if (v1 == 0) {
            self->f28 = 0;
            goto done;
        }
        if (self->f30 <= g_gameClock.elapsed) {
            f32 lo = 0.1f;
            f32 hi = 0.33329999446868896f;
            f32 t = (self->f34 + self->f34) * 0.33333334f;
            if (t < lo) {
                c = lo;
            } else if (hi < t) {
                c = hi;
            } else {
                c = t;
            }
            self->f34 = c;
            base = g_gameClock.elapsed;
        } else {
            return 0;
        }
    }
    self->f30 = base + c;
done:
    return self->f28;
}

void func_0016EC20(PadRecord* self, s32 mask);

s32 func_0016EED0(PadRecord* self)
{
    f32 c;
    f32 base;
    if (self->f2C == 0) {
        u16 fl = self->flags;
        if (fl & 0x1000) {
            ClearPadPressedBits(self, 0x1000);
            self->f2C = -1;
        } else if (fl & 0x4000) {
            ClearPadPressedBits(self, 0x4000);
            self->f2C = 1;
        } else if (0.8f <= self->f48) {
            f32 a = fabsf(self->f44);
            f32 b = fabsf(self->f40);
            if (b < a) {
                if (0.0f < self->f44) {
                    self->f2C = -1;
                } else {
                    self->f2C = 1;
                }
            }
        }
        if (self->f2C == 0) {
            goto done;
        }
        c = 0.33329999446868896f;
        self->f3C = c;
        base = g_elapsedTime[0];
    } else {
        s32 v1 = 0;
        if (self->f2C < 0) {
            if (self->keyA8 & 0x1000) {
                v1 = 1;
            } else if (0.25f <= self->f48) {
                f32 a = fabsf(self->f44);
                f32 b = fabsf(self->f40);
                if (b < a) {
                    if (0.0f < self->f44) v1 = 1;
                }
            }
        } else {
            if (self->keyA8 & 0x4000) {
                v1 = 1;
            } else if (0.25f <= self->f48) {
                f32 a = fabsf(self->f44);
                f32 b = fabsf(self->f40);
                if (b < a) {
                    if (self->f44 < 0.0f) v1 = 1;
                }
            }
        }
        if (v1 == 0) {
            self->f2C = 0;
            goto done;
        }
        if (self->f38 <= g_gameClock.elapsed) {
            f32 lo = 0.1f;
            f32 hi = 0.33329999446868896f;
            f32 t = (self->f3C + self->f3C) * 0.33333334f;
            if (t < lo) {
                c = lo;
            } else if (hi < t) {
                c = hi;
            } else {
                c = t;
            }
            self->f3C = c;
            base = g_gameClock.elapsed;
        } else {
            return 0;
        }
    }
    self->f38 = base + c;
done:
    return self->f2C;
}

f32 func_0016F108(PadRecord* self, s32 idx)
{
    if (self->keyA8 & g_padButtonMasks[idx]) {
        if (self->f18 >= 4) {
            s32 v = 1;
            s32 b = self->fAE[idx];
            if (v < b) {
                v = b;
            }
            return (f32)v * 0.00392156886f;
        }
        return 1.0f;
    }
    return 0.0f;
}

extern u16 D_00262D18;

void func_0016F188(ButtonCode* node)
{
    ButtonCode* p = g_buttonCodes;
    if (p != 0) {
        do {
            if (node == p) {
                return;
            }
            p = p->next;
        } while (p != 0);
    }
    node->next = g_buttonCodes;
    g_buttonCodes = node;
    if (D_00262D18 == *(u16*)node->buttons) {
        node->pos = 1;
    } else {
        node->pos = 0;
    }
}

LINKER_REMNANT(func_0016F1F0);

void func_0016F1F8(void)
{
    ButtonCode* p = g_buttonCodes;
    if (p != 0) {
        do {
            p->pos = 0;
            p = p->next;
        } while (p != 0);
    }
}

struct Advance_16F238 {
    static void Of(ButtonCode* node)
    {
        do {
            s32 index = node->pos;
            if (index < node->length) {
                if (D_00262C70.keyA8 == node->buttons[index])
                    node->pos = index + 1;
                else
                    node->pos = 0;
            }
            node = node->next;
        } while (node);
    }
};

void func_0016F238(PadRecord* self, s32 value)
{
    u16 id = (u16)value;
    ButtonCode* head = g_buttonCodes;
    if (head == 0) return;
    if (self != &g_padRecord) return;
    u16 previous = self->keyA8;
    if (id == previous || previous == 0) return;
    Advance_16F238::Of(head);
    GameClock* clock = &g_gameClock;
    D_00262E00.time = clock->elapsed + 1.0f;
}

void func_0016F1F8(void);
void func_001BFCD8(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);

void func_0016F2E0(void)
{
    if (D_00262E00.time == 0.0f) {
        return;
    }
    if (!(D_00262E00.time <= g_elapsedTime[0])) {
        return;
    }
    ButtonCode* best = 0;
    ButtonCode** link = &g_buttonCodes;
    ButtonCode* p = g_buttonCodes;
    while (p != 0) {
        if (p->drop != 0) {
            *link = p->next;
            p->pos = 0;
            p->drop = 0;
            p->next = 0;
        } else if (p->pos < p->length) {
            link = &p->next;
        } else {
            if (best == 0 || best->length < p->length) {
                best = p;
            }
            link = &p->next;
        }
        p = *link;
    }
    if (best != 0) {
        StartSoundEffect(0x79, 0, 0, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f);
        best->fn(best->arg);
    }
    ResetButtonCodes();
    D_00262E00.time = 0.0f;
}

extern s32 D_00262C64;

void func_001E5278(s32 mode);

void func_0016F408(void)
{
    g_buttonCodeFlags = 0;
    RequestWorldLoadByMode(0);
}

extern s32 D_00262C64;

void func_001E5278(s32 mode);

void func_0016F430(s32 flags)
{
    g_buttonCodeFlags = g_buttonCodeFlags | (flags & ~0x4000);
    if (flags & 0x4000)
    {
        RequestWorldLoadByMode(0);
    }
}

LINKER_REMNANT(func_0016F470);

struct Obj_16F478;
struct Vt_16F478 { u8 pad0[0x20]; void (*f20)(Obj_16F478* self, char* text); u8 pad1[0x14]; void (*f38)(Obj_16F478* self); };
struct Obj_16F478 { Vt_16F478* vt; };

extern Obj_16F478 D_0026EC70;
extern const char D_002483B8[24];

s32 func_001602A0(void);
void* func_001E2138(char* dst, const u8* src);
s32 func_001E1FD0(char* dst, const u8* fmt, ...);
void func_001AA8B8(Obj_16F478* self, f32 v);

void func_0016F478(void)
{
    char text[0x40];
    char buf[0x10];

    if ((g_saveData->f19D8 << 8 | g_saveData->f19DC) == 0x400) {
        if ((ComputeCompletionMask() & 6) == 6) {
            if (g_saveData->f19E8 == 99 && g_saveData->f19E0 == 0) {
                char* p = buf;
                CopyString(p, (const u8*)D_002483B8);
                while (*p != 0) {
                    *p ^= 0x23;
                    p++;
                }
                FormatToString(text, (const u8*)D_0024A848, buf);
                D_0026EC70.vt->f20(&D_0026EC70, text);
                SetScreenElementHoldTime(&D_0026EC70, 10.0f);
                D_0026EC70.vt->f38(&D_0026EC70);
            }
        }
    }
}

void func_0016F188(ButtonCode* entry);

void func_0016F588(void)
{
    AddButtonCode(&g_worldLoadButtonCode.rec);
    AddButtonCode(&g_clearFlagsButtonCode.rec);
    AddButtonCode(&D_00262AF0.rec);
    AddButtonCode(&D_00262B28.rec);
    AddButtonCode(&g_setFlagsButtonCodeC.rec);
    AddButtonCode(&g_flagNumberedItemsButtonCode.rec);
    AddButtonCode(&D_00262BD0.rec);
    AddButtonCode(&D_00262C08.rec);
    AddButtonCode(&g_passwordMessageButtonCode);
}
