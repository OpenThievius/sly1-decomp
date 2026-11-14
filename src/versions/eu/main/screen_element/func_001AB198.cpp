// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: fields moved (+0x310), u16 flag at +8, globals at 0x560/0x594, PAL-only callees, a pointer argument to func_00137260 and a 0xC0 byte buffer.
struct Obj_1AB198_eu {
    u8 pad0[4];
    s32 f4;
    u16 f8;
    u8 pad1[0x408 - 0xA];
    u8 f408[0x518 - 0x408];
    T217D_Word f518;
    f32 f51c;
    u8 pad3[0x52C - 0x520];
    f32 f52c;
    f32 f530;
    u8 pad4[0x544 - 0x534];
    f32 f544;
    f32 f548;
};

struct Glob_1AB198_eu {
    u8 pad0[0x560];
    s32 f560;
    u8 pad1[0x594 - 0x564];
    f32 f594;
};

void PushFontScale(s32 handle, f32 a, f32 b);
void PopFontScale(s32 handle);
void SetTextLayoutVerticalPlacement(void* out, s32 flag);
// PAL hands the layout's word at 0x14 an object where the US build passes flags: left as the free
// function it was on that word (a 64-bit hazard for a port), not a cast to the method's s32.
void SetTextLayoutHorizontalAlign(void* out, void* p);
void InitWideTextReader(void* buf, void* out, s32 handle, s32 zero);
void DrawWrappedAlignedText(void* buf, void* out, s32 zero, void* data);

void DrawCounterCaption(Obj_1AB198_eu* self)
{
    u8 out[0x20];
    T217D_Word packed;
    s32 held;
    s32 tmp[4];
    u8 buf[0xC0];
    f32 scale;
    f32 px;
    f32 py;
    Glob_1AB198_eu* g;

    if (self->f8 == 0) {
        return;
    }
    g = (Glob_1AB198_eu*)&g_pauseMenuElement;
    scale = 1.0f;
    if (g->f560 != 0) {
        scale = g->f594;
    }
    packed = self->f518;
    void* q = self->f408;
    ((u8*)&packed)[3] = (u8)(s32)(scale * 255.0f);
    held = packed.v;
    px = self->f544;
    py = self->f548;
    ((Layout_137228*)out)->Pos(self->f52c, self->f530);
    ((Layout_137228*)out)->Size(px, py);
    tmp[0] = held;
    ((Layout_137228*)out)->Color(&tmp[0]);
    SetTextLayoutHorizontalAlign(out, q);
    ((Layout_137228*)out)->SetF18(0);
    SetTextLayoutVerticalPlacement(out, 0);
    PushFontScale(self->f4, self->f51c, self->f51c);
    InitWideTextReader(buf, &self->f8, self->f4, 0);
    DrawWrappedAlignedText(buf, out, 0, &g_gsPacketWriter);
    PopFontScale(self->f4);
}
