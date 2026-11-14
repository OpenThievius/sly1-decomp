// SPDX-License-Identifier: AGPL-3.0-or-later
// SIZE 732/708, checked 2026-11-01
// Still differs: Label draw with slide-in offset and backdrop box; ours 24 bytes longer (732 vs 708): &L still cached in extra saved registers (s0/s4) where retail recomputes addiu a0,sp,16.
// Draws a label with a slide-in offset; when the owner is absent also draws a translucent backdrop box, then the text.
struct __attribute__((packed)) PW_eu_1AE138 { s32 v; };
struct Actor_eu_1AE138 {
    u8 pad0[4]; Font* p4; u16 f08; u8 pad1[0x518 - 0xA]; PW_eu_1AE138 col; f32 f51C; u8 pad2[0x534 - 0x520];
    f32 f534; f32 f538; u8 pad3[0x544 - 0x53C]; f32 f544; f32 f548; f32 f54C;
    u8 pad4[0x974 - 0x550]; void* f974;
};
struct Out_eu_1AE138;
void SetTextLayoutVerticalPlacement(Out_eu_1AE138* out, s32 v);
struct Out_eu_1AE138 {
    u8 d[0x20];
    void Pos(f32 x, f32 y) { ((Layout_137228*)this)->Pos(x, y); }
    void Size(f32 x, f32 y) { ((Layout_137228*)this)->Size(x, y); }
    void Color(s32* c) { ((Layout_137228*)this)->Color(c); }
    void FlagA(s32 f) { ((Layout_137228*)this)->SetF14(f); }
    void FlagB(s32 f) { ((Layout_137228*)this)->SetF18(f); }
    void Fin(s32 v) { SetTextLayoutVerticalPlacement(this, v); }
};
struct Globals_eu_1AE138 { u8 pad0[0x560]; s32 f560; u8 pad1[0xC]; s32 f570; };
struct Mode_eu_1AE138 { u8 pad0[0x56C]; s32 f56C; struct Owner_eu_1AE138* f570; };
struct Owner_eu_1AE138 { u8 pad0[0x2D0]; s32 f2D0; };
extern Globals_eu_1AE138 D_eu_00275E98;
extern Mode_eu_1AE138 D_eu_00274868;
extern f32 D_eu_0027939C;
extern u8 D_eu_00263590[];
void InitWideTextReader(void* buf, void* name, void* p, s32 zero);
void DrawWrappedAlignedText(void* buf, Out_eu_1AE138* out, s32 zero, void* d);

void DrawMessageElement(Actor_eu_1AE138* self)
{
    PW_eu_1AE138 c;
    Out_eu_1AE138 L;
    PW_eu_1AE138 slot;
    u8 buf[0xC0];
    f32 phase;
    f32 slide;
    f32 f12;
    if (self->f08 == 0) {
        return;
    }
    if (D_eu_00275E98.f560 != 0) {
        if ((u32)(D_eu_00275E98.f570 - 1) < 2) {
            return;
        }
    }
    if (self->f974 != 0) {
        phase = 1.0f;
        slide = (phase - D_eu_0027939C) * 54.305084f;
    } else {
        phase = self->f54C;
        slide = 0.0f;
    }
    c = self->col;
    ((u8*)&c)[3] = (u8)((f32)((u8*)&c)[3] * phase);
    f32 f544 = self->f544;
    f32 f548 = self->f548;
    s32 s0v = c.v;
    L.Pos(self->f534, self->f538 + slide);
    L.Size(f544, f548);
    slot.v = s0v;
    L.Color(&slot.v);
    L.FlagA(0);
    L.FlagB(0);
    L.Fin(0);
    if (self->f974 == 0) {
        PacketWriter* ctx = (PacketWriter*)D_eu_00263590;
        f32 a = phase;
        if (D_eu_00274868.f56C != 0 && D_eu_00274868.f570 != 0 && D_eu_00274868.f570->f2D0 == 2) {
            a = 1.0f;
        }
        f32 y = 468.61017f;
        y += slide;
        ((u8*)&slot)[0] = 0;
        ((u8*)&slot)[1] = 0;
        ((u8*)&slot)[2] = 0;
        ((u8*)&slot)[3] = (u8)(a * 64.0f);
        y = y - 54.305084f;
        BeginGifTag(ctx, 0x46, 5, 0x441EE);
        AddGifRegisterWrite(ctx, 0x47, 0x30000);
        AddGifRegisterWrite(ctx, 0x42, 0x44);
        AddGifRgbaEntry(ctx, slot.v);
        y *= 0.5462963f;
        y += 1920.0f;
        y *= 16.0f;
        AddGifXyzfEntry(ctx, 0x6C00, (s32)y, 0xFFFFFF0, 0);
        AddGifXyzfEntry(ctx, 0x9400, 0x8800, 0xFFFFFF0, 0);
    }
    f12 = self->f51C;
    PushFontScale(self->p4, f12, f12);
    InitWideTextReader(buf, (u8*)self + 8, self->p4, 0);
    DrawWrappedAlignedText(buf, &L, 0, D_eu_00263590);
    PopFontScale(self->p4);
}
