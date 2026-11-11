// SPDX-License-Identifier: AGPL-3.0-or-later
// Sets the element's 16-bit text: a string that is set and not empty (func_eu_001E3018, its length) is copied
// to the text at +0x8, measured with the element's font scale into the record at +0x408, and the size taken from
// it; otherwise the text is cleared and the size is zero.
struct Obj_001AAB20_eu;
void SetScreenElementSize(Obj_001AAB20_eu* self, f32 x, f32 y);
s32 func_eu_001E3018(u16* s);
u16* func_eu_001E3050(u16* dst, u16* src);
void func_eu_0015DCB8(void* buf, void* name, void* p, s32 zero);
void func_eu_0015E4A8(void* buf, void* p, f32 v);

struct Obj_eu_001AB2B0 { u8 pad0[4]; void* f4; u16 text[0x200]; f32 f408; f32 f40C; f32 f410; u8 pad2[0x51C - 0x414]; f32 f51C; };

void func_eu_001AB2B0(Obj_eu_001AB2B0* self, u16* s)
{
    u8 buf[0xC0];
    if (s != 0 && func_eu_001E3018(s) != 0) {
        func_eu_001E3050(self->text, s);
        f32 scale = self->f51C;
        PushFontScale((Font*)self->f4, scale, scale);
        func_eu_0015DCB8(buf, self->text, self->f4, 0);
        func_eu_0015E4A8(buf, &self->f408, 0.0f);
        SetScreenElementSize((Obj_001AAB20_eu*)self, self->f40C, self->f410);
        PopFontScale((Font*)self->f4);
    } else {
        self->text[0] = 0;
        SetScreenElementSize((Obj_001AAB20_eu*)self, 0.0f, 0.0f);
    }
}
