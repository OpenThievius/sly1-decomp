// SPDX-License-Identifier: AGPL-3.0-or-later
// Draws a fading label: builds a transform/colour block, lets the attached object draw into it, then draws the text.
struct Actor_eu_1AD438 {
    u8 pad0[4]; Font* p4; u16 f08; u8 pad1[0x408 - 0xA]; T217D_Word f408;
    u8 pad2[0x518 - 0x40C]; T217D_Word col; f32 f51C; void* f520; u8 pad3[8];
    f32 f52C; f32 f530; u8 pad4[0x10]; f32 f544; f32 f548; f32 f54C;
};
struct Out_eu_1AD438;
void func_00137228(Out_eu_1AD438* out, f32 x, f32 y);
void func_00137238(Out_eu_1AD438* out, f32 x, f32 y);
void func_00137248(Out_eu_1AD438* out, s32* value);
void func_00137260(Out_eu_1AD438* out, void* p);
void func_00137268(Out_eu_1AD438* out, s32 flag);
void func_eu_001374E0(Out_eu_1AD438* out, s32 v);
struct Out_eu_1AD438 {
    u8 d[0x20];
    void Pos(f32 x, f32 y) { func_00137228(this, x, y); }
    void Size(f32 x, f32 y) { func_00137238(this, x, y); }
    void Color(s32* c) { func_00137248(this, c); }
    void Link(void* p) { func_00137260(this, p); }
    void FlagB(s32 f) { func_00137268(this, f); }
    void FlagC(s32 f) { func_eu_001374E0(this, f); }
};
struct Attach_eu_1AD438 { u8 pad0[0x18]; T217D_Word col; };
struct Hd_eu_1AD438 {
    static void Draw(void* h, Out_eu_1AD438* out, void* tbl)
    {
        SubObj_001AB710* sub = *(SubObj_001AB710**)h;
        if (sub != 0) {
            VDesc_001AB710* d = sub->desc4C;
            d->fn4C((u8*)sub + d->off48, h, (void*)out, tbl);
        }
    }
};
extern u8 D_eu_00263590[];
void func_eu_0015DCB8(void* buf, void* name, void* p, s32 zero);
void func_eu_0015E7E0(void* buf, Out_eu_1AD438* out, s32 zero, void* d);

void func_eu_001AD438(Actor_eu_1AD438* self)
{
    T217D_Word c;
    Out_eu_1AD438 L;
    if (self->f08 != 0) {
        T217D_Word* link = &self->f408;
        c = self->col;
        ((u8*)&c)[3] = (u8)((f32)((u8*)&c)[3] * self->f54C);
        f32 f544 = self->f544;
        f32 f548 = self->f548;
        s32 held = c.v;
        L.Pos(self->f52C, self->f530);
        L.Size(f544, f548);
        {
            T217D_Word tag;
            tag.v = held;
            L.Color(&tag.v);
        }
        L.Link(link);
        L.FlagB(0);
        L.FlagC(0);
        Attach_eu_1AD438* obj = (Attach_eu_1AD438*)self->f520;
        f32 v;
        if (obj != 0) {
            T217D_Word saved = obj->col;
            ((u8*)&obj->col)[3] = (u8)((f32)((u8*)&obj->col)[3] * self->f54C);
            Hd_eu_1AD438::Draw(self->f520, &L, D_eu_00263590);
            ((Attach_eu_1AD438*)self->f520)->col = saved;
        }
        v = self->f51C;
        PushFontScale(self->p4, v, v);
        u8 buf[0xC0];
        func_eu_0015DCB8(buf, (u8*)self + 8, self->p4, 0);
        func_eu_0015E7E0(buf, &L, 0, D_eu_00263590);
        PopFontScale(self->p4);
    }
}
