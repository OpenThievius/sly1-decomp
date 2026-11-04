// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the mode is at 0x570 (US 0x260).
struct S_136648_eu { u8 pad[0x570]; s32 mode; };
extern f32 func_001AA8A8(S_136648_eu* s);

f32 func_00136648(S_136648_eu* s) {
    switch (s->mode) {
    case 1:
    case 2:
    case 5:
        return 0.0f;
    case 3:
    case 4:
    default:
        return func_001AA8A8(s);
    }
}
