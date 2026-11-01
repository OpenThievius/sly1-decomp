// SPDX-License-Identifier: AGPL-3.0-or-later
// Copies four words of the source record into self, picks two sets of arguments by the source kind to call func_0011E428 (PAL), and on success calls func_eu_0018EDE8.
struct Src_eu_0018ED38 {
    u8 pad00[8];
    s32 kind;
    s32 a;
    s32 b;
    s32 c;
};

struct Self_eu_0018ED38 {
    s32 pad00;
    s32 kind;
    s32 a;
    s32 b;
    s32 c;
    s32 result;
    s32 size;
};

s32 func_0011E428(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
void func_eu_0018EDE8(void* self);

s32 func_eu_0018ED38(Self_eu_0018ED38* self, Src_eu_0018ED38* src)
{
    s32 kind = src->kind;
    self->kind = kind;
    self->a = src->a;
    s32 b = src->b;
    self->b = b;
    self->c = src->c;
    if (kind == 16) {
        self->size = b << 12;
        self->result = func_0011E428(0x400, 0x1000, 0x400, 0, 2, 3);
    } else {
        self->size = 0x6000;
        self->result = func_0011E428(0x6000, 0, 0x400, 0, 2, 2);
    }
    if (self->result >= 0) {
        func_eu_0018EDE8(self);
        return 1;
    }
    return 0;
}
