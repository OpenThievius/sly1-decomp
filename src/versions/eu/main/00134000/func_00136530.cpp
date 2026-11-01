// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: 16-bit flag, fields at 0x578/0x57C, a 0xC0-byte buffer and a fourth argument (0) to the setup call.
struct Obj_136530_eu {
    u8 pad0[4];
    s32 handle;
    u16 flag;
    u8 pad1[0x578 - 0xA];
    f32 f578;
    f32 scale;
};

void func_eu_0015DCB8(void* out, void* p, s32 handle, s32 d);

s32 func_00136530(Obj_136530_eu* self)
{
    u8 buf[0xC0];

    if (self->flag == 0) {
        return 1;
    }
    func_eu_0015DCB8(buf, &self->flag, self->handle, 0);
    s32 n = func_0015DF58(buf);
    s32 v = (s32)((D_0026185C - self->f578) * self->scale);
    return v >= n;
}
