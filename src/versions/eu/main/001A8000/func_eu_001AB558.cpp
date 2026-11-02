// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 265/300 (88.3%), checked 2026-11-01
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001AB558.cpp func_eu_001AB558 --unit src/main/001A8000.cpp
// Still differs: Rect record from owner fields, virtual call, font scale, buffer builders; matches except self/record-pointer s1/s2 swap (retail self in s2) and load order of f544/f548 vs lui.
// Builds a rect record from the owner's fields, lets the +0x520 object fill it through a virtual call, scales the font and draws via the buffer builders.
struct Actor_eu_001AB558 { u8 pad0[4]; void* p4; u16 f08; u8 pad1[0x518 - 0xA]; s32 f518; f32 f51C; void* f520; u8 pad2[8]; f32 f52C; f32 f530; u8 pad3[0x10]; f32 f544; f32 f548; };

void func_eu_001374E0(void* out, s32 v);
void func_eu_0015DCB8(void* buf, void* name, void* p, s32 zero);
void func_eu_0015E7E0(void* buf, void* out, s32 zero, void* d);
extern u8 D_eu_00263590[];
struct Local_eu_001AB558 { f32 x; f32 y; u8 pad0[0x18]; s32 tag; u8 pad1[0xC]; };

void func_eu_001AB558(Actor_eu_001AB558* self)
{
    Local_eu_001AB558 L;
    u8 buf[0xC0];
    if (self->f08 != 0) {
        u8* rt = (u8*)self + 0x408;
        f32 f544 = self->f544;
        f32 f548 = self->f548;
        s32 s0v = self->f518;
        func_00137228(&L, self->f52C, self->f530);
        func_00137238(&L, f544, f548);
        L.tag = s0v;
        func_00137248(&L, &L.tag);
        func_00137260(&L, (s32)rt);
        func_00137268(&L, 0);
        func_eu_001374E0(&L, 0);
        void* obj = self->f520;
        if (obj != 0) {
            SubObj_001AB710* sub = *(SubObj_001AB710**)obj;
            if (sub != 0) {
                VDesc_001AB710* d = sub->desc4C;
                d->fn4C((u8*)sub + d->off48, obj, &L, D_eu_00263590);
            }
        }
        f32 v = self->f51C;
        func_0015C8B8(self->p4, v, v);
        func_eu_0015DCB8(buf, (u8*)self + 8, self->p4, 0);
        func_eu_0015E7E0(buf, &L, 0, D_eu_00263590);
        func_0015C900(self->p4);
    }
}
