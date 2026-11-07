// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: 16-bit text (func_eu_001E3018/001E3050), fields at 0x408/0x570/0x578, line breaks laid out by func_eu_0015E4A8, no line-start scan.
struct Entry_00136408_eu {
    u8 pad0[4];
    Font* f04;
    u16 name08[0x200];
    u8 list408[0x168];
    s32 f570;
    u8 pad574[4];
    f32 f578;
};

s32 func_eu_001E3018(const char* s);
s32 func_eu_001E3050(void* dst, const char* src);
void* func_eu_0015DCB8(void* buf, void* name, Font* v, s32 zero);  // returns buf
void func_eu_0015E4A8(void* buf, void* list, f32 lim);

void SetTextPanelText(Entry_00136408_eu* self, const char* name)
{
    u8 buf[0xC0];
    s32 wide;
    s32 r;
    f32 scale;
    f32 lim;
    f32* tab;

    if (name == 0) goto fail;
    if ((r = func_eu_001E3018(name)) == 0) goto fail;
    func_eu_001E3050(self->name08, name);
    wide = 4;
    scale = 1.0f;
    if (self->f570 == wide) scale = 0.8f;
    PushFontScale(self->f04, scale, scale);
    func_eu_0015DCB8(buf, self->name08, self->f04, 0);
    lim = 280.0f;
    if (self->f570 == wide) lim = 380.0f;
    func_eu_0015E4A8(buf, self->list408, lim);
    PopFontScale(self->f04);
    goto tail;
fail:
    self->name08[0] = 0;
tail:
    tab = (f32*)g_gameClock;
    self->f578 = tab[1];
}
