// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL runs at 50 Hz: the frame step is clamped to 1/50 to 1/25 of a second.
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
    f32 lo = 0.02f;
    f32 hi = 0.04f;
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
    if (0.02f <= s) {
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
