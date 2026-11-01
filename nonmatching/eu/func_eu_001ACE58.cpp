// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 77/132 (58.3%), checked 2026-11-01
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001ACE58.cpp func_eu_001ACE58 --unit src/main/001A8000.cpp
// Still differs: Timer countdown and ratio store; retail loads/converts the 0x578 divisor early and loads the 0x58C constant after the 0x588 store, ours hoists the constant load.
// Counts down a timer at 0x580 with the reload at 0x574 and the stage at 0x57C, then stores a ratio of the count to 0x578 and a constant at 0x58C.
extern f32 D_eu_00262B5C;
struct Timer_eu_1ACE58 { u8 pad[0x574]; s32 f574; s32 f578; s32 f57C; s32 f580; u8 pad2[0x588 - 0x584]; f32 f588; f32 f58C; };
void func_eu_001ACE58(Timer_eu_1ACE58* a0)
{
    a0->f580 = a0->f580 - 1;
    if (a0->f580 <= 0) {
        s32 t = a0->f57C - 1;
        a0->f57C = t;
        if (t <= 0) {
            a0->f580 = 0;
            a0->f57C = 0;
        } else {
            a0->f580 = a0->f574;
        }
    }
    f32 den = (f32)a0->f578;
    s32 v = a0->f57C - 1;
    if (v < 0) {
        v = 0;
    }
    a0->f588 = (f32)(v * a0->f574 + a0->f580) / den;
    a0->f58C = D_eu_00262B5C;
}
