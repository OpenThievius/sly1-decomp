// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "system.h"
#include "game_clock.h"

// The file's .data, in retail's order: the two scale factors, the clock, and the tick count
// func_001430C8 and the assembly func_001430F8 keep.
f32 g_timeScale = 1.0f;
f32 g_stepScale = 1.0f;
GameClock g_gameClock = { 0 };
u64 g_lastCycleCount = 0;

void SetGameClockRunning(GameClock* clock, s32 running);
s64 ReadCycleCounter(void);
f32 ConvertS64ToFloat(s64 value);

void SetGameClockScale(f32 x)
{
    g_timeScale = x;
    SetGameClockRunning(&g_gameClock, x > 0.0f ? 1 : 0);
}

void AdvanceGameClock(GameClock* self)
{
    s64 now = ReadCycleCounter();
    s64 delta = now - self->lastTick;
    u64 half = (u64)delta >> 1;
    f32 t;
    if (delta >= 0) {
        t = ConvertS64ToFloat(delta);
    } else {
        t = ConvertS64ToFloat((delta & 1) | half);
        t = t + t;
    }
    f32 dt = t * 0.0000000033908420f;
    f32 lo = 0.016666668f;
    f32 hi = 0.033333335f;
    if (dt < lo) {
        dt = lo;
    } else if (hi < dt) {
        dt = hi;
    }
    self->step = dt;
    f32 s = 0.0f;
    if (self->running) {
        s = dt;
    }
    s = s * (g_stepScale * g_timeScale);
    if (0.016666668f <= s) {
        self->step = s;
    }
    f32 new_a = self->time + s;
    f32 old_b = self->dt;
    f32 new_d = self->elapsed + self->step;
    self->time = new_a;
    self->previousDt = old_b;
    self->dt = s;
    self->elapsed = new_d;
    self->lastTick = now;
}

void AdvanceGameClockElapsed(GameClock* self)
{
    s64 now = ReadCycleCounter();
    s64 delta = now - self->lastTick;
    u64 half = (u64)delta >> 1;
    f32 t;
    if (delta >= 0) {
        t = ConvertS64ToFloat(delta);
    } else {
        t = ConvertS64ToFloat((delta & 1) | half);
        t = t + t;
    }
    f32 dt = t * 0.0000000033908420f;
    self->lastTick = now;
    self->step = dt;
    self->elapsed = self->elapsed + dt;
}

void SetGameClockTime(GameClock* self, f32 value)
{
    self->time = value;
}

void SetGameClockRunning(GameClock* clock, s32 running)
{
    clock->running = running;
}

// Starts the tick count over: the cycle counter now, and the clock's last tick.
void ResetGameClockTick(void)
{
    g_lastCycleCount = ReadCop0Count();
    g_gameClock.lastTick = ReadCycleCounter();
}

ASM_FUNC(func_001430F8);
