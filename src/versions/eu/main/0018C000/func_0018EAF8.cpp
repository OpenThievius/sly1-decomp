// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL checks a key byte first and, when the first part is done, starts the next with a PAL-only call.
struct Stream_18EAF8_eu {
    s32 mode;
    s32 key;
    u8 sub8[0x28];
    u8 sub30[0x10];
    s32 v40;
    u8 pad44[0x50 - 0x44];
    u8 sub50[0x10];
    s32 v60;
    u8 pad64[0x70 - 0x64];
    u8 sub70[0x10];
};

extern s32 D_eu_00263710;
s32 func_eu_0018ED38(void* a, void* b);

s32 func_0018EAF8(Stream_18EAF8_eu* self, s32 left, s32 right)
{
    s32 n;
    s32 b;

    if (self->mode == 0) {
        return 0;
    }
    b = *(u8*)(right + 3);
    if (self->key == -1) {
        if (b == 0 || b == D_eu_00263710 + 1) {
            self->key = b;
        }
    }
    if (self->key != b) {
        return 1;
    }
    left -= 4;
    right += 4;
    if (self->mode == 1) {
        n = func_0013CC00(self->sub30, left, right);
        left -= n;
        right += n;
        if (self->v40 > 0) {
            return 1;
        }
        if (func_eu_0018ED38(self->sub70, self->sub8) != 0) {
            self->mode = 2;
        } else {
            self->mode = 0;
        }
    }
    if (self->v60 >= left) {
        func_0013CC00(self->sub50, left, right);
        return 1;
    }
    return 0;
}
