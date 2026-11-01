// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 424/420, checked 2026-11-01
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001AD438.cpp func_eu_001AD438 --unit src/main/001A8000.cpp
// Still differs: Draws a fading label; now 424 bytes vs 420 (stack slot sharing fixed), ours keeps &L in an extra saved register s4 and swaps s1/s2 and f20/f21.
// Draws a fading label: builds a transform/colour block, lets the attached object draw into it, then draws the text.
struct Actor_eu_1AD438 {
    u8 pad0[4]; void* p4; u16 f08; u8 pad1[0x408 - 0xA]; PackedWord_001AB710 f408;
    u8 pad2[0x518 - 0x40C]; PackedWord_001AB710 col; f32 f51C; void* f520; u8 pad3[8];
    f32 f52C; f32 f530; u8 pad4[0x10]; f32 f544; f32 f548; f32 f54C;
};
struct Local_eu_1AD438 { f32 x; f32 y; u8 pad0[8]; PackedWord_001AB710 w10; u8 pad1[0xC]; };
struct Attach_eu_1AD438 { u8 pad0[0x18]; PackedWord_001AB710 col; };
extern u8 D_eu_00263590[];
void func_eu_001374E0(void* out, s32 v);
void func_00137260(void* out, void* p);
void func_eu_0015DCB8(void* buf, void* name, void* p, s32 zero);
void func_eu_0015E7E0(void* buf, void* out, s32 zero, void* d);

void func_eu_001AD438(Actor_eu_1AD438* self)
{
    PackedWord_001AB710 c;
    Local_eu_1AD438 L;
    if (self->f08 != 0) {
        c = self->col;
        ((u8*)&c)[3] = (u8)((f32)((u8*)&c)[3] * self->f54C);
        f32 f544 = self->f544;
        f32 f548 = self->f548;
        func_00137228(&L, self->f52C, self->f530);
        func_00137238(&L, f544, f548);
        {
            PackedWord_001AB710 tag;
            tag.v = c.v;
            func_00137248(&L, &tag);
        }
        func_00137260(&L, &self->f408);
        func_00137268(&L, 0);
        func_eu_001374E0(&L, 0);
        Attach_eu_1AD438* obj = (Attach_eu_1AD438*)self->f520;
        f32 v;
        if (obj != 0) {
            PackedWord_001AB710 saved = obj->col;
            ((u8*)&obj->col)[3] = (u8)((f32)((u8*)&obj->col)[3] * self->f54C);
            SubObj_001AB710* sub = *(SubObj_001AB710**)self->f520;
            if (sub != 0) {
                VDesc_001AB710* d = sub->desc4C;
                d->fn4C((u8*)sub + d->off48, self->f520, &L, D_eu_00263590);
            }
            ((Attach_eu_1AD438*)self->f520)->col = saved;
        }
        v = self->f51C;
        func_0015C8B8(self->p4, v, v);
        u8 buf[0xC0];
        func_eu_0015DCB8(buf, (u8*)self + 8, self->p4, 0);
        func_eu_0015E7E0(buf, &L, 0, D_eu_00263590);
        func_0015C900(self->p4);
    }
}
