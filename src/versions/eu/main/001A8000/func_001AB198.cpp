// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: fields moved (+0x310), u16 flag at +8, globals at 0x560/0x594, PAL-only callees, a pointer argument to func_00137260 and a 0xC0 byte buffer.
struct Obj_1AB198_eu {
    u8 pad0[4];
    s32 f4;
    u16 f8;
    u8 pad1[0x408 - 0xA];
    u8 f408[0x518 - 0x408];
    Word_1AB198 f518;
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

void func_00137260(void* out, void* p);
void func_eu_001374E0(void* out, s32 flag);
void func_eu_0015DCB8(void* buf, void* out, s32 handle, s32 zero);
void func_eu_0015E7E0(void* buf, void* out, s32 zero, void* data);

void func_001AB198(Obj_1AB198_eu* self)
{
    u8 out[0x20];
    Word_1AB198 packed;
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
    g = (Glob_1AB198_eu*)D_0026FF68;
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
    func_00137228(out, self->f52c, self->f530);
    func_00137238(out, px, py);
    tmp[0] = held;
    func_00137248(out, &tmp[0]);
    func_00137260(out, q);
    func_00137268(out, 0);
    func_eu_001374E0(out, 0);
    func_0015C8B8(self->f4, self->f51c, self->f51c);
    func_eu_0015DCB8(buf, &self->f8, self->f4, 0);
    func_eu_0015E7E0(buf, out, 0, D_00262280);
    func_0015C900(self->f4);
}
