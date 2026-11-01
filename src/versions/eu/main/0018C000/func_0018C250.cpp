// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the memory-card directory names carry SCES-50917, the title is "Sly Raccoon", and the save count is 11.
s32 func_0018C250(Card_18C250* self)
{
    char name[0x50];
    s32 info[4];
    s32 r = func_0018BD00(func_0020A078(self->f4, self->f8, "/"), 0x12, info);
    if (r != 0) return r;
    s32 need = info[0] == 0 ? 2 : 1;
    s32 sz = func_0018C1E8(D_00248470);
    need += 5;
    need += (sz + 1023) / 1024;
    need += 0x15;
    if (self->f28 < need) return 1;
    const char* dir = "/BESCES-50917YAOTWTD!";
    r = func_0018D228(self, dir);
    if (r == 0) {
        const char* title = "Sly Raccoon";
        r = func_0018D368(self, "/BESCES-50917YAOTWTD!/BESCES-50917YAOTWTD!", title, 11);
        if (r == 0) {
            r = func_0018CA10(self, dir, title);
            if (r == 0) {
                r = func_0018CBF8(self, dir);
                if (r == 0) {
                    for (s32 i = 0; i < 3; i++) {
                        func_001E1FD0(name, "/%s/%s%d", "BESCES-50917YAOTWTD!", "save", i + 1);
                        r = func_0018D028(self, name, (u8*)self + 0x30 + i * 0x1A5C, (u8*)self + 0x1A30 + i * 0x1A5C);
                        if (r != 0) return r;
                    }
                    if (self->f14 < 5) self->f14 = 5;
                }
            }
        }
    }
    return r;
}
