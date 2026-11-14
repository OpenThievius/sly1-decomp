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
#include "fpu.h"

// Types other files define, named by the parameters of their functions declared here.
struct PadPatternPlayer;

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
void SetSavedWorldBits(u32 value);
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
extern "C" s32 InitPadLibrary(s32 mode);
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

extern "C" void* FillMemory(void* p, s32 value, s32 size);
void* ReservePermanentMemory(s32 size);
extern "C" s32 OpenPadPort(s32 port, s32 slot, u8* buffer);
void SetPadConnectionState(PadRecord* self, s32 mode, s32 n);

void InitPadRecord(PadRecord* self, s32 a, s32 b)
{
    FillMemory(self, 0, 0xC4);
    SetPadConnectionState(self, 1, 0);
    self->port = a;
    self->slot = b;
    u8* buffer = (u8*)(((s32)ReservePermanentMemory(0x140) + 0x3F) & -0x40);
    self->f0C = buffer;
    OpenPadPort(self->port, self->slot, buffer);
    self->patternPlayer = ReservePermanentMemory(0x20);
    self->patternsEnabled = 1;
}

extern "C" s32 GetPadSlotState(s32 port, s32 slot);
extern "C" s32 GetPadReplyListValue(s32 port, s32 slot, s32 kind, s32 index);
extern "C" s32 SendPadTwoWordRequest(s32 port, s32 slot, s32 a2, s32 a3);
extern "C" s32 GetPadReplyTableByte(s32 port, s32 slot, s32 index, s32 kind);
extern "C" void* FillMemory(void* p, s32 value, s32 size);
extern "C" s32 SendPadSixByteRequest(s32 port, s32 slot, u8* src);
extern "C" s32 HasFullPadMask(s32 port, s32 slot);
extern "C" s32 SendFullPadMask(s32 port, s32 slot);
extern "C" s32 GetPadRequestMode(s32 port, s32 slot);
s32 PollPadInput(PadRecord* self);
void UpdatePadPattern(PadPatternPlayer* s);
void SetPadConnectionState(PadRecord* self, s32 mode, s32 n);

void UpdatePadConnection(PadRecord* self)
{
    u8 buf[16];
    if (self->connectionMode == 0)
    {
        return;
    }
    s32 ready = 0;
    s32 r = GetPadSlotState(self->port, self->slot);
    if (r == 6 || r == 2)
    {
        ready = 1;
    }
    s32 cur = self->connectionStep;
    if (self->connectionMode != 3 && cur != 0 && 2.0f <= g_gameClock.elapsed - self->connectionChangeTime)
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
    s32 mode = self->connectionMode;
    s32 n = self->connectionStep;
    switch (mode)
    {
    case 1:
        switch (n)
        {
        case 0:
        {
            s32 a = GetPadReplyListValue(self->port, self->slot, 1, 0);
            if (a != 0)
            {
                s32 b = GetPadReplyListValue(self->port, self->slot, 2, 0);
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
            mode = (SendPadTwoWordRequest(self->port, self->slot, 1, 3) == 1) ? two : n;
            break;
        case 2:
        {
            s32 count = GetPadReplyTableByte(self->port, self->slot, -1, 0);
            if (count != n
                || GetPadReplyTableByte(self->port, self->slot, 0, 1) != mode
                || GetPadReplyTableByte(self->port, self->slot, 0, 2) != n
                || GetPadReplyTableByte(self->port, self->slot, 0, 3) != 0
                || GetPadReplyTableByte(self->port, self->slot, 1, 1) != mode
                || GetPadReplyTableByte(self->port, self->slot, 1, 2) != mode
                || GetPadReplyTableByte(self->port, self->slot, 1, 3) != mode)
            {
                mode = 3;
                break;
            }
            FillMemory(buf, 0xFF, 6);
            for (s32 i = 0; i < count; i++)
            {
                buf[i] = i;
            }
            if (SendPadSixByteRequest(self->port, self->slot, buf) == 1)
            {
                mode = 2;
            }
            break;
        }
        case 3:
            if (HasFullPadMask(self->port, self->slot) != mode)
            {
                mode = 3;
                break;
            }
            if (SendFullPadMask(self->port, self->slot) == 1)
            {
                mode = two;
            }
            break;
        }
        break;
    case 2:
        switch (GetPadRequestMode(self->port, self->slot))
        {
        case 0:
            switch (self->connectionStep)
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
            if (self->patternsEnabled != 0 && self->connectionStep >= 3)
            {
                UpdatePadPattern((PadPatternPlayer*)self->patternPlayer);
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

void RequestPadPattern(PadPatternPlayer* self, s32 a1, s32 a2);

void SetPadConnectionState(PadRecord* self, s32 mode, s32 n)
{
    s32 next = mode;
    if (mode == self->connectionMode)
    {
        if (n == self->connectionStep)
        {
            return;
        }
    }
    if (n == 0)
    {
        self->deviceType = 0;
        next = 1;
    }
    if (self->connectionStep < 3 && n >= 3)
    {
        RequestPadPattern((PadPatternPlayer*)self->patternPlayer, self->port, self->slot);
    }
    if (next == 3)
    {
        self->f20 = 0;
        self->secondStickActive = 0;
        self->stickActive = 0;
        self->fA8 = 0;
        for (u32 i = 0; i < 4; i++)
        {
            self->secondStickRanges[i].lo = -0.75f;
            self->stickRanges[i].lo = -0.75f;
            self->secondStickRanges[i].hi = 0.75f;
            self->stickRanges[i].hi = 0.75f;
        }
    }
    self->connectionMode = next;
    self->connectionStep = n;
    self->connectionChangeTime = g_gameClock.elapsed;
}

// The stick's response clamp, 0 to 1.
static inline f32 ClampStick(f32 v, f32 lo, f32 hi)
{
    if (v < lo) return lo;
    if (hi < v) return hi;
    return v;
}

// len is the stick's projection on each response axis, then its length; frac is the
// projection's fraction of the axis's widest reach so far, then the response.
void ReadAnalogStick(PadRecord* p, u8 x, u8 y, f32* outX, f32* outY, f32* outMag,
                     u8* prevX, u8* prevY, s32* latch, ValueRange* range)
{
    f32 nx, ny;
    if (*latch == 0) {
        s32 moved = 0;
        if (p->lastReadTime != 0.0f
            && (x != *prevX || y != *prevY || x < 0x60 || x > 0xA0 || y < 0x60 || y > 0xA0)) {
            moved = 1;
        }
        *latch = moved;
    }
    if (*latch != 0) {
        nx = ((f32)(s32)x + (f32)(s32)x) * 0.003921569f + -1.0f;
        ny = 1.0f - ((f32)(s32)y + (f32)(s32)y) * 0.003921569f;
    } else {
        nx = 0.0f;
        ny = 0.0f;
    }
    f32 sx = nx * nx;
    f32 sy = ny * ny;
    f32 best = 0.0f;
    f32 len;
    f32 frac;
    for (u32 i = 0; i < 4; i++) {
        len = nx * D_00262A30[i * 2] + ny * D_00262A30[i * 2 + 1];
        if (0.0f <= len) {
            if (range[i].hi < len) range[i].hi = len;
            frac = len / range[i].hi;
        } else {
            if (len < range[i].lo) range[i].lo = len;
            frac = len / range[i].lo;
        }
        if (best < frac) best = frac;
    }
    f32 t = best - 0.35f;
    t = t + t;
    frac = ClampStick(t, 0.0f, 1.0f);
    *outMag = frac;
    len = Fpu::Sqrt(sx + sy);
    if (0.0001f < len) {
        *outX = frac * nx / len;
        *outY = frac * ny / len;
    } else {
        *outX = *outY = 0.0f;
    }
    *prevX = x;
    *prevY = y;
}

extern "C" void* FillMemory(void* p, s32 value, s32 size);
extern "C" s32 ReadPadFrame(s32 port, s32 slot, u8* data);
void CopyMemory(void* dst, void* src, u32 size);
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
    if (ReadPadFrame(self->port, self->slot, b) > 0) {
        old = self->buttons;
        self->buttons = ~((buf[2] << 8) | buf[3]);
        if (self->deviceType != 0) {
            if (self->deviceType != buf[1]) res = 0;
        }
        self->deviceType = buf[1];
        if (self->connectionStep == 4) {
            CopyMemory(self->pressure, buf + 8, 0xC);
        }
        cur = self->buttons;
        self->flags = cur & ~old;
        self->released = old & ~cur;
        if (self->connectionStep >= 2) {
            ReadAnalogStick(self, buf[6], buf[7], &self->stickX, &self->stickY, &self->stickMagnitude, &self->stickPrevRawX, &self->stickPrevRawY, &self->stickActive, self->stickRanges);
            ReadAnalogStick(self, buf[4], buf[5], &self->secondStickX, &self->secondStickY, &self->secondStickMagnitude, &self->secondStickPrevRawX, &self->secondStickPrevRawY, &self->secondStickActive, self->secondStickRanges);
        } else {
            self->secondStickX = self->secondStickY = self->secondStickMagnitude = self->stickX = self->stickY = self->stickMagnitude = 0.0f;
        }
        if (g_camera == 0 || g_camera->stackCount == 0 || g_camera->stack[0].ctl != &g_camera->ctl454) {
            if ((self->buttons & 0xF000) != 0) {
                self->stickX = self->stickY = self->stickMagnitude = 0.0f;
                if ((self->buttons & 0x8000) != 0) {
                    self->stickX = -1.0f;
                } else if ((self->buttons & 0x2000) != 0) {
                    self->stickX = 1.0f;
                }
                if ((self->buttons & 0x1000) != 0) {
                    self->stickY = 1.0f;
                } else if ((self->buttons & 0x4000) != 0) {
                    self->stickY = -1.0f;
                }
                if (self->stickX * self->stickY != 0.0f) {
                    self->stickX = self->stickX * 0.8f;
                    self->stickY = self->stickY * 0.8f;
                }
                self->stickMagnitude = 1.0f;
            }
        }
        AdvanceButtonCodes(self, old);
        self->lastReadTime = g_gameClock.elapsed;
        if (self->buttons != 0 || self->stickMagnitude != 0.0f || self->secondStickMagnitude != 0.0f) {
            self->lastActiveTime = g_gameClock.elapsed;
        }
    } else {
        if (g_elapsedTime[0] - self->lastReadTime >= 2.0f) res = 0;
    }
    return res;
}

void ClearPadPressedBits(PadRecord* self, u32 mask)
{
    u16 m = (u16)mask;
    self->flags &= (u16)~m;
}

struct PadPatternPlayer;
void StartPadPatternFromTable(PadPatternPlayer* self, s32 index, f32 time);

void StartPadRecordPattern(PadRecord* self, s32 pattern, f32 duration)
{
    if (self->pC0 == 0) return;
    if (self->connectionStep < 3) return;
    if (self->connectionMode != 3) return;
    StartPadPatternFromTable((PadPatternPlayer*)self->patternPlayer, pattern, duration);
}

LINKER_REMNANT(func_0016EC80);

void ResetPadStepRepeat(PadRecord* p) { p->stepX = 0; p->stepY = 0; }

extern f32 g_elapsedTime[];

s32 GetPadHorizontalStep(PadRecord* self)
{
    f32 c;
    f32 base;
    if (self->stepX == 0) {
        u16 fl = self->flags;
        if (fl & 0x8000) {
            ClearPadPressedBits(self, 0x8000);
            self->stepX = -1;
        } else if (fl & 0x2000) {
            ClearPadPressedBits(self, 0x2000);
            self->stepX = 1;
        } else if (0.8f <= self->stickMagnitude) {
            f32 a = fabsf(self->stickX);
            f32 b = fabsf(self->stickY);
            if (b < a) {
                if (self->stickX < 0.0f) {
                    self->stepX = -1;
                } else {
                    self->stepX = 1;
                }
            }
        }
        if (self->stepX == 0) {
            goto done;
        }
        c = 0.33329999446868896f;
        self->stepDelayX = c;
        base = g_elapsedTime[0];
    } else {
        s32 v1 = 0;
        if (self->stepX < 0) {
            if (self->buttons & 0x8000) {
                v1 = 1;
            } else if (0.25f <= self->stickMagnitude) {
                f32 a = fabsf(self->stickX);
                f32 b = fabsf(self->stickY);
                if (b < a) {
                    if (self->stickX < 0.0f) v1 = 1;
                }
            }
        } else {
            if (self->buttons & 0x2000) {
                v1 = 1;
            } else if (0.25f <= self->stickMagnitude) {
                f32 a = fabsf(self->stickX);
                f32 b = fabsf(self->stickY);
                if (b < a) {
                    if (0.0f < self->stickX) v1 = 1;
                }
            }
        }
        if (v1 == 0) {
            self->stepX = 0;
            goto done;
        }
        if (self->nextStepTimeX <= g_gameClock.elapsed) {
            f32 lo = 0.1f;
            f32 hi = 0.33329999446868896f;
            f32 t = (self->stepDelayX + self->stepDelayX) * 0.33333334f;
            if (t < lo) {
                c = lo;
            } else if (hi < t) {
                c = hi;
            } else {
                c = t;
            }
            self->stepDelayX = c;
            base = g_gameClock.elapsed;
        } else {
            return 0;
        }
    }
    self->nextStepTimeX = base + c;
done:
    return self->stepX;
}

void ClearPadPressedBits(PadRecord* self, u32 mask);

s32 GetPadVerticalStep(PadRecord* self)
{
    f32 c;
    f32 base;
    if (self->stepY == 0) {
        u16 fl = self->flags;
        if (fl & 0x1000) {
            ClearPadPressedBits(self, 0x1000);
            self->stepY = -1;
        } else if (fl & 0x4000) {
            ClearPadPressedBits(self, 0x4000);
            self->stepY = 1;
        } else if (0.8f <= self->stickMagnitude) {
            f32 a = fabsf(self->stickY);
            f32 b = fabsf(self->stickX);
            if (b < a) {
                if (0.0f < self->stickY) {
                    self->stepY = -1;
                } else {
                    self->stepY = 1;
                }
            }
        }
        if (self->stepY == 0) {
            goto done;
        }
        c = 0.33329999446868896f;
        self->stepDelayY = c;
        base = g_elapsedTime[0];
    } else {
        s32 v1 = 0;
        if (self->stepY < 0) {
            if (self->buttons & 0x1000) {
                v1 = 1;
            } else if (0.25f <= self->stickMagnitude) {
                f32 a = fabsf(self->stickY);
                f32 b = fabsf(self->stickX);
                if (b < a) {
                    if (0.0f < self->stickY) v1 = 1;
                }
            }
        } else {
            if (self->buttons & 0x4000) {
                v1 = 1;
            } else if (0.25f <= self->stickMagnitude) {
                f32 a = fabsf(self->stickY);
                f32 b = fabsf(self->stickX);
                if (b < a) {
                    if (self->stickY < 0.0f) v1 = 1;
                }
            }
        }
        if (v1 == 0) {
            self->stepY = 0;
            goto done;
        }
        if (self->nextStepTimeY <= g_gameClock.elapsed) {
            f32 lo = 0.1f;
            f32 hi = 0.33329999446868896f;
            f32 t = (self->stepDelayY + self->stepDelayY) * 0.33333334f;
            if (t < lo) {
                c = lo;
            } else if (hi < t) {
                c = hi;
            } else {
                c = t;
            }
            self->stepDelayY = c;
            base = g_gameClock.elapsed;
        } else {
            return 0;
        }
    }
    self->nextStepTimeY = base + c;
done:
    return self->stepY;
}

f32 GetPadButtonAnalog(PadRecord* self, s32 idx)
{
    if (self->buttons & g_padButtonMasks[idx]) {
        if (self->connectionStep >= 4) {
            s32 v = 1;
            s32 b = self->pressure[idx];
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
                if (g_padRecord.buttons == node->buttons[index])
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
    u16 previous = self->buttons;
    if (id == previous || previous == 0) return;
    ButtonCodeAdvance::Of(head);
    GameClock* clock = &g_gameClock;
    D_00262E00.time = clock->elapsed + 1.0f;
}

void ResetButtonCodes(void);
struct PlayingSound;
void StartSoundEffect(s32 id, PlayingSound** out, BaseObject* p2, Vec02* p3,
                   f32 fa, f32 fb, f32 fc, f32 fd, f32 fe, f32* p4, U64P* p5);

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
        StartSoundEffect(0x79, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
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
void* CopyString(void* dst, const char* src);
s32 FormatToString(char* dst, const char* fmt, ...);

void ShowPasswordMessage(void)
{
    char text[0x40];
    char buf[0x10];

    if ((g_saveData->levelIndex << 8 | g_saveData->entryIndex) == 0x400) {
        if ((ComputeCompletionMask() & 6) == 6) {
            if (g_saveData->pickupCount == 99 && g_saveData->reserveCount == 0) {
                char* p = buf;
                CopyString(p, (const char*)D_002483B8);
                while (*p != 0) {
                    *p ^= 0x23;
                    p++;
                }
                FormatToString(text, (const char*)D_0024A848, buf);
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
