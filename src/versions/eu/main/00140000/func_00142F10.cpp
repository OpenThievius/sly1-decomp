// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL runs at 50 Hz: the frame step is clamped to 1/50 to 1/25 of a second.
void func_00142F10(Timer_00142F10* self)
{
    s64 now = func_001430F8();
    s64 delta = now - self->last;
    u64 half = (u64)delta >> 1;
    f32 t;
    if (delta >= 0) {
        t = func_001FB6B0(delta);
    } else {
        t = func_001FB6B0((delta & 1) | half);
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
    s = s * (D_00261854 * D_00261850);
    if (0.02f <= s) {
        self->step = s;
    }
    f32 new_a = self->acc_a + s;
    f32 old_b = self->hist_b;
    f32 new_d = self->acc_d + self->step;
    self->acc_a = new_a;
    self->hist_c = old_b;
    self->hist_b = s;
    self->acc_d = new_d;
    self->last = now;
}
