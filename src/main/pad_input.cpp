// SPDX-License-Identifier: AGPL-3.0-or-later
// The file from 0x16E0B8 to 0x16F608: the pads (set-up, connection, polling, repeat steps and
// analog values, include/pad_record.h) and the button codes (include/button_code.h). Its name
// is ours, after the pad input it reads.
#include "common.h"
#include "button_code.h"
#include "globals.h"
#include "game_clock.h"
#include "pad_record.h"
#include "game_progress.h"
#include "screen_element.h"
#include "asm_func.h"

// The pad and button-code file: the pad records D_00262C70 and D_00262D38, their connection
// state machine and input polling, the repeating step readers, and the cheat-code list with its
// nine slots. Its .rodata is the password message (0x24A848); its .data runs from 0x262A30 to
// 0x262E10, in retail's order: the stick-response floats func_0016E738 reads, the button masks,
// the code sequences with their slots, the flags, the two records, the list head and the timer.

extern const char D_0024A848[24] = "The password is: %s";
f32 D_00262A30[8] = { 1.0f, 0.0f, 0.0f, 1.0f, 0.699999988f, 0.699999988f, 0.699999988f, -0.699999988f };

u16 g_padButtonMasks[12] = { 0x2000, 0x8000, 0x1000, 0x4000, 0x0010, 0x0020, 0x0040, 0x0080, 0x0004, 0x0008, 0x0001, 0x0002 };
u32 g_worldLoadButtonSequence[6] = { 0x14000, 0x400002, 0x14000, 0x400002, 0x208000, 0x100 };

void RequestWorldLoadByMode(s32 mode);
void ClearButtonCodeFlags(void);
void SetButtonCodeFlags(s32 flags);
void ShowPasswordMessage(void);
void FlagAllNumberedItems(void);
void SetSavedWorldBits(void);
void MarkAllLevelRecordsComplete(void);
ButtonCodeSlot g_worldLoadButtonCode = { { (const u16*)g_worldLoadButtonSequence, 0xB, (ButtonCodeFn)RequestWorldLoadByMode, 0x0 } };
u32 g_clearFlagsButtonSequence[6] = { 0x14000, 0x400002, 0x14000, 0x400002, 0x208000, 0x800 };
ButtonCodeSlot g_clearFlagsButtonCode = { { (const u16*)g_clearFlagsButtonSequence, 0xB, (ButtonCodeFn)ClearButtonCodeFlags, 0x0 } };
u32 D_00262AD8[6] = { 0x14000, 0x400002, 0x14000, 0x400002, 0x208000, 0x8000 };
ButtonCodeSlot D_00262AF0 = { { (const u16*)D_00262AD8, 0xB, (ButtonCodeFn)SetButtonCodeFlags, 0x4004 } };
u32 D_00262B10[6] = { 0x14000, 0x400002, 0x14000, 0x400002, 0x208000, 0x2000 };
ButtonCodeSlot D_00262B28 = { { (const u16*)D_00262B10, 0xB, (ButtonCodeFn)SetButtonCodeFlags, 0x8 } };
u32 g_setFlagsButtonSequenceC[6] = { 0x14000, 0x400002, 0x14000, 0x400002, 0x208000, 0x20 };
ButtonCodeSlot g_setFlagsButtonCodeC = { { (const u16*)g_setFlagsButtonSequenceC, 0xB, (ButtonCodeFn)SetButtonCodeFlags, 0x2 } };
u32 g_flagNumberedItemsButtonSequence[6] = { 0x14000, 0x400002, 0x14000, 0x400002, 0x208000, 0x1000 };
ButtonCodeSlot g_flagNumberedItemsButtonCode = { { (const u16*)g_flagNumberedItemsButtonSequence, 0xB, (ButtonCodeFn)FlagAllNumberedItems, 0x0 } };
u32 D_00262BB8[6] = { 0x14000, 0x400002, 0x14000, 0x400002, 0x208000, 0x4000 };
ButtonCodeSlot D_00262BD0 = { { (const u16*)D_00262BB8, 0xB, (ButtonCodeFn)SetSavedWorldBits, 0xF000FFFF } };
u32 D_00262BF0[6] = { 0x14000, 0x400002, 0x14000, 0x400002, 0x208000, 0x10 };
ButtonCodeSlot D_00262C08 = { { (const u16*)D_00262BF0, 0xB, (ButtonCodeFn)MarkAllLevelRecordsComplete, 0x0 } };
u32 g_passwordMessageButtonSequence[8] = { 0x14000, 0x400002, 0x14000, 0x400002, 0x208000, 0x800080, 0x80, 0x0 };
ButtonCode g_passwordMessageButtonCode = { (const u16*)g_passwordMessageButtonSequence, 0xD, (ButtonCodeFn)ShowPasswordMessage, 0x0 };
// size: s32 flags, word accesses only
s32 g_buttonCodeFlags = 0;
// size: s32 flags, word accesses only
s32 g_padRouting = 0;
// size: s32 flags, word accesses only
s32 g_padSelectFlags = 0;
PadRecord g_padRecord = {};
// size: chosen with D_00262C70 as the same pad pointer (conditional), 0xC4 to the next label
PadRecord g_blankPadRecord = {};

ButtonCode* g_buttonCodes = 0;

extern f32 g_elapsedTime[];
struct ButtonCodeTimer { f32 time; f32 pad[3]; };
ButtonCodeTimer D_00262E00 = { 0.0f, { 0.0f, 0.0f, 0.0f } };

void UpdatePadRouting(void);
s32 InitPadLibrary(void* a);
void InitPadRecord(PadRecord* self, s32 a, s32 b);

void InitPadSystem(void)
{
    UpdatePadRouting();
    InitPadLibrary(0);
    InitPadRecord(&g_padRecord, 0, 0);
}

extern s32 g_padSelectFlags;

void UpdatePadRouting();

s32 SetPadSelectFlags(s32 bits)
{
    g_padSelectFlags |= bits;
    return ((s32 (*)())UpdatePadRouting)();
}

void UpdatePadRouting(void);

void ClearPadSelectFlags(u32 mask)
{
    mask = ~mask;
    g_padSelectFlags = g_padSelectFlags & mask;
    UpdatePadRouting();
}

extern s32 g_padSelectFlags;
extern s32 g_padRouting;

void UpdatePadRouting()
{
    s32 flags = g_padSelectFlags;
    if ((flags & 0x84) != 0)
    {
        g_padRouting = 0;
        return;
    }
    if ((flags & 1) != 0)
    {
        g_padRouting = 5;
        return;
    }
    if ((flags & 2) != 0)
    {
        g_padRouting = 4;
        return;
    }
    g_padRouting = 7;
}

void FillMemory(void* p, s32 value, s32 size);
void* ReservePermanentMemory(s32 size);
void OpenPadPort(s32 a, s32 b, s32 c);
void SetPadConnectionState(PadRecord* self, s32 mode, s32 n);

void InitPadRecord(PadRecord* self, s32 a, s32 b)
{
    FillMemory(self, 0, 0xC4);
    SetPadConnectionState(self, 1, 0);
    self->f04 = a;
    self->f08 = b;
    s32 size = ((s32)ReservePermanentMemory(0x140) + 0x3F) & -0x40;
    self->f0C = size;
    OpenPadPort(self->f04, self->f08, size);
    self->fBC = ReservePermanentMemory(0x20);
    self->fC0 = 1;
}

s32 GetPadSlotState(s32 a, s32 b);
s32 func_002047F8(s32 a, s32 b, s32 c, s32 d);
s32 SendPadTwoWordRequest(s32 a, s32 b, s32 c, s32 d);
s32 func_002046D0(s32 a, s32 b, s32 c, s32 d);
void FillMemory(u8* p, s32 value, s32 size);
s32 SendPadSixByteRequest(s32 a, s32 b, u8* buf);
s32 HasFullPadMask(s32 a, s32 b);
s32 SendFullPadMask(s32 a, s32 b);
s32 GetPadRequestMode(s32 a, s32 b);
s32 PollPadInput(PadRecord* self);
void UpdatePadPattern(void* p);
void SetPadConnectionState(PadRecord* self, s32 mode, s32 n);

void UpdatePadConnection(PadRecord* self)
{
    u8 buf[16];
    if (self->f14 == 0)
    {
        return;
    }
    s32 ready = 0;
    s32 r = GetPadSlotState(self->f04, self->f08);
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
            mode = (SendPadTwoWordRequest(self->f04, self->f08, 1, 3) == 1) ? two : n;
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
            FillMemory(buf, 0xFF, 6);
            for (s32 i = 0; i < count; i++)
            {
                buf[i] = i;
            }
            if (SendPadSixByteRequest(self->f04, self->f08, buf) == 1)
            {
                mode = 2;
            }
            break;
        }
        case 3:
            if (HasFullPadMask(self->f04, self->f08) != mode)
            {
                mode = 3;
                break;
            }
            if (SendFullPadMask(self->f04, self->f08) == 1)
            {
                mode = two;
            }
            break;
        }
        break;
    case 2:
        switch (GetPadRequestMode(self->f04, self->f08))
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

void RequestPadPattern(void* a, s32 b, s32 c);

void SetPadConnectionState(PadRecord* self, s32 mode, s32 n)
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

void FillMemory(u8* p, s32 a, s32 b);
s32 ReadPadFrame(s32 a, s32 b, u8* c);
void CopyMemory(u8* dst, u8* src, s32 n);
void ReadAnalogStick(PadRecord* p, s32 a, s32 b, f32* c, f32* d, f32* e, u8* f, u8* g, f32* h, f32* i);
void AdvanceButtonCodes(PadRecord* p, s32 old);

s32 PollPadInput(PadRecord* self)
{
    u8 buf[0x40];
    s32 res;
    u16 old;
    u16 cur;

    u8* b = buf;
    FillMemory(b, 0, 0x40);
    res = 1;
    if (ReadPadFrame(self->f04, self->f08, b) > 0) {
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
            ReadAnalogStick(self, buf[6], buf[7], &self->f40, &self->f44, &self->f48, &self->f4C, &self->f4D, &self->x50, &self->a54[0].lo);
            ReadAnalogStick(self, buf[4], buf[5], &self->f74, &self->f78, &self->f7C, &self->f80, &self->f81, &self->x84, &self->a88[0].lo);
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

void ClearPadPressedBits(PadRecord* self, u32 mask)
{
    u16 m = (u16)mask;
    self->flags &= (u16)~m;
}

void StartPadPatternFromTable(void* p);

void StartPadRecordPattern(PadRecord* self)
{
    if (self->pC0 == 0) return;
    if (self->f18 < 3) return;
    if (self->f14 != 3) return;
    StartPadPatternFromTable(self->fBC);
}

LINKER_REMNANT(func_0016EC80);

void ResetPadStepRepeat(PadRecord* p) { p->f28 = 0; p->f2C = 0; }

extern f32 g_elapsedTime[];

s32 GetPadHorizontalStep(PadRecord* self)
{
    f32 c;
    f32 base;
    if (self->f28 == 0) {
        u16 fl = self->flags;
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
            if (self->keyA8 & 0x8000) {
                v1 = 1;
            } else if (0.25f <= self->f48) {
                f32 a = fabsf(self->f40);
                f32 b = fabsf(self->f44);
                if (b < a) {
                    if (self->f40 < 0.0f) v1 = 1;
                }
            }
        } else {
            if (self->keyA8 & 0x2000) {
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

void ClearPadPressedBits(PadRecord* self, s32 mask);

s32 GetPadVerticalStep(PadRecord* self)
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

f32 GetPadButtonAnalog(PadRecord* self, s32 idx)
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

void AddButtonCode(ButtonCode* node)
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

void ResetButtonCodes(void)
{
    ButtonCode* p = g_buttonCodes;
    if (p != 0) {
        do {
            p->pos = 0;
            p = p->next;
        } while (p != 0);
    }
}

struct ButtonCodeAdvance {
    static void Of(ButtonCode* node)
    {
        do {
            s32 index = node->pos;
            if (index < node->length) {
                if (g_padRecord.keyA8 == node->buttons[index])
                    node->pos = index + 1;
                else
                    node->pos = 0;
            }
            node = node->next;
        } while (node);
    }
};

void AdvanceButtonCodes(PadRecord* self, s32 value)
{
    u16 id = (u16)value;
    ButtonCode* head = g_buttonCodes;
    if (head == 0) return;
    if (self != &g_padRecord) return;
    u16 previous = self->keyA8;
    if (id == previous || previous == 0) return;
    ButtonCodeAdvance::Of(head);
    GameClock* clock = &g_gameClock;
    D_00262E00.time = clock->elapsed + 1.0f;
}

void ResetButtonCodes(void);
void StartSoundEffect(s32 a0, void* a1, s32 a2, s32 a3, s32 a4, s32 a5, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);

void RunCompletedButtonCode(void)
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

extern s32 g_buttonCodeFlags;

void RequestWorldLoadByMode(s32 mode);

void ClearButtonCodeFlags(void)
{
    g_buttonCodeFlags = 0;
    RequestWorldLoadByMode(0);
}

extern s32 g_buttonCodeFlags;

void RequestWorldLoadByMode(s32 mode);

void SetButtonCodeFlags(s32 flags)
{
    g_buttonCodeFlags = g_buttonCodeFlags | (flags & ~0x4000);
    if (flags & 0x4000)
    {
        RequestWorldLoadByMode(0);
    }
}

LINKER_REMNANT(func_0016F470);

extern const char D_002483B8[24];

s32 ComputeCompletionMask(void);
void* CopyString(char* dst, const u8* src);
s32 FormatToString(char* dst, const u8* fmt, ...);

void ShowPasswordMessage(void)
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
                g_buttonHintElement.vt->m08(&g_buttonHintElement, text);
                SetScreenElementHoldTime(&g_buttonHintElement, 10.0f);
                g_buttonHintElement.vt->m14(&g_buttonHintElement);
            }
        }
    }
}

void AddButtonCode(ButtonCode* entry);

void RegisterButtonCodes(void)
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
