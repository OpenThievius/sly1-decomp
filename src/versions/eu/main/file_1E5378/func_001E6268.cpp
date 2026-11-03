// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: field at 0x1190 and the scale is 69 instead of 57
struct Obj_001E6268_eu { u8 pad[0x1190]; f32 value; };
void func_001E6268(Obj_001E6268_eu* self, s32* first, s32* second) { s32 n = (s32)(self->value * 69.0f); s32 half = (69 - n) / 2; *first = half; *second = half + n; }
