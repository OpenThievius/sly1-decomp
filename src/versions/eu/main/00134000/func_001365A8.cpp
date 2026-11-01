// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the value is at 0x58C (US 0x300).
struct State_001365A8_eu { u8 pad[0x58C]; f32 value;
    void set(f32 x, f32 lo, f32 hi) {
        if (x < lo) x = lo;
        else if (hi < x) x = hi;
        value = x;
    }
};
void func_001365A8(State_001365A8_eu* self, f32 value)
{
    self->set(value * 0.01f, 0.0f, 1.0f);
}
