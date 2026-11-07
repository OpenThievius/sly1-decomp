// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the field is at 0x588 (US 0x2FC).
struct Obj_1365A0_eu { u8 pad[0x588]; s32 f2FC; };

void func_001365A0(Obj_1365A0_eu* self, s32 value) { self->f2FC = value; }
