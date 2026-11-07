// SPDX-License-Identifier: AGPL-3.0-or-later
// BYTES 172/188 (91.5%), checked 2026-11-07
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001AB2B0.cpp func_eu_001AB2B0 --unit src/main/file_1A7FE8.cpp
// Still differs: Key-gated sub-object work; layout offset fixed (f51C at 0x51C), all instructions match except self and key are in swapped s-registers (retail self in s2).
// With a key that func_eu_001E3018 accepts, runs the PAL-only calls on the sub-object at +0x8 and on the buffer they fill, then func_001AAB20 and func_0015C900; otherwise clears the s16 at +0x8 and calls func_001AAB20 with 0.0 and 0.0.
struct Obj_001AAB20_eu;
void SetScreenElementSize(Obj_001AAB20_eu* self, f32 x, f32 y);
s32 func_eu_001E3018(void* key);
void func_eu_001E3050(void* p, void* key);
void func_eu_0015DCB8(void* buf, void* name, void* p, s32 zero);
void func_eu_0015E4A8(void* buf, void* p, f32 v);

struct Obj_eu_001AB2B0 { u8 pad0[4]; void* f4; s16 f8; u8 pad1[0x40C - 0xA]; f32 f40C; f32 f410; u8 pad2[0x51C - 0x414]; f32 f51C; };

void func_eu_001AB2B0(Obj_eu_001AB2B0* self, void* key)
{
    u8 buf[0xC0];
    if (key != 0 && func_eu_001E3018(key) != 0) {
        func_eu_001E3050((u8*)self + 8, key);
        PushFontScale((Font*)self->f4, self->f51C, self->f51C);
        func_eu_0015DCB8(buf, (u8*)self + 8, self->f4, 0);
        func_eu_0015E4A8(buf, (u8*)self + 0x408, 0.0f);
        SetScreenElementSize((Obj_001AAB20_eu*)self, self->f40C, self->f410);
        PopFontScale((Font*)self->f4);
    } else {
        self->f8 = 0;
        SetScreenElementSize((Obj_001AAB20_eu*)self, 0.0f, 0.0f);
    }
}
