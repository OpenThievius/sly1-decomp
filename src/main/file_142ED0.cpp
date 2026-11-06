// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "asm_func.h"
#include "game_clock.h"

// The file's .data, in retail's order: the two scale factors, the clock, and the tick count
// the assembly func_001430C8 and func_001430F8 keep.
f32 D_00261850 = 1.0f;
f32 D_00261854 = 1.0f;
GameClock D_00261858 = { 0 };
u64 D_00261878 = 0;

void func_001430C0(GameClock* clock, s32 running);
s64 func_001430F8(void);
f32 func_001FB6B0(s64 value);

void func_00142ED0(f32 x)
{
    g_timeScale = x;
    SetGameClockRunning(&g_gameClock, x > 0.0f ? 1 : 0);
}

void func_00142F10(GameClock* self)
{
    s64 now = func_001430F8();
    s64 delta = now - self->lastTick;
    u64 half = (u64)delta >> 1;
    f32 t;
    if (delta >= 0) {
        t = func_001FB6B0(delta);
    } else {
        t = func_001FB6B0((delta & 1) | half);
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

void func_00143030(GameClock* self)
{
    s64 now = func_001430F8();
    s64 delta = now - self->lastTick;
    u64 half = (u64)delta >> 1;
    f32 t;
    if (delta >= 0) {
        t = func_001FB6B0(delta);
    } else {
        t = func_001FB6B0((delta & 1) | half);
        t = t + t;
    }
    f32 dt = t * 0.0000000033908420f;
    self->lastTick = now;
    self->step = dt;
    self->elapsed = self->elapsed + dt;
}

void func_001430B8(GameClock* self, f32 value)
{
    self->time = value;
}

void func_001430C0(GameClock* clock, s32 running)
{
    clock->running = running;
}

ASM_FUNC(func_001430C8);

ASM_FUNC(func_001430F8);
