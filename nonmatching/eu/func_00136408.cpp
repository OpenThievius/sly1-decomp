// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR (PAL, func_00136408 at PAL 0x136568): PAL's own definition, built in src/main/00134000.cpp's unit
// (python3 tools/check.py nonmatching/eu/func_00136408.cpp func_00136408 --unit src/main/00134000.cpp).
// 4 instructions differ: the load of the field at 0x570 uses v0 where PAL has v1.
// PAL: 16-bit text (func_eu_001E3018/001E3050), fields at 0x408/0x570/0x578, line breaks laid out by func_eu_0015E4A8, no line-start scan.
struct Entry_00136408_eu {
    u8 pad0[4];
    s32 f04;
    u16 name08[0x200];
    u8 list408[0x168];
    s32 f570;
    u8 pad574[4];
    f32 f578;
};

s32 func_eu_001E3018(const char* s);
void func_eu_001E3050(void* dst, const char* src);
void func_0015DB28(void* buf, void* p, s32 v, s32 zero);
void func_eu_0015DCB8(void* buf, void* name, s32 v, s32 zero);
void func_eu_0015E4A8(void* buf, void* list, f32 lim);

void func_00136408(Entry_00136408_eu* self, const char* name)
{
    u8 buf[0xC0];
    s32 s0;
    s32 r;
    f32 scale;
    f32 lim;
    f32* tab;

    if (name == 0) goto fail;
    if (func_eu_001E3018(name) == 0) goto fail;
    func_eu_001E3050(self->name08, name);
    s0 = 4;
    scale = 1.0f;
    if ((r = self->f570) == s0) scale = 0.8f;
    func_0015C8B8(self->f04, scale, scale);
    func_eu_0015DCB8(buf, self->name08, self->f04, 0);
    lim = 280.0f;
    if ((r = self->f570) == s0) lim = 380.0f;
    func_eu_0015E4A8(buf, self->list408, lim);
    func_0015C900(self->f04);
    goto tail;
fail:
    self->name08[0] = 0;
tail:
    tab = (f32*)D_00261858;
    self->f578 = tab[1];
}
