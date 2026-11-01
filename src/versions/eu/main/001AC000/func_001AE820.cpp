// SPDX-License-Identifier: AGPL-3.0-or-later
extern f32 D_eu_0027939C;
// PAL lays the object out 0x310 bytes later from f208 on, calls one more setter
// (func_eu_001374E0), reads a PAL-only float, has a 0xC0 buffer, passes a fourth argument to func_0015DB28 and uses its own func_eu_0015E7E0.
struct Obj_1AE820_eu {
    VFn_1AE820* vtbl;
    void* f4;
    u8 pad0[0x518 - 8];
    s32 f208;
    f32 f20c;
    u8 pad1[0x52C - 0x520];
    f32 f21c;
    f32 f220;
    u8 pad2[0x544 - 0x534];
    f32 f234;
    f32 f238;
    u8 pad3[0x560 - 0x54C];
    s32 f250;
    f32 f254;
    u8 pad4[0x570 - 0x568];
    s32 f260;
};
void func_eu_001374E0(void* out, s32 flag);
void func_0015DB28(void* out, void* p, void* handle, s32 extra);
void func_eu_0015E7E0(void* buf, void* out, s32 zero, void* data);

void func_001AE820(Obj_1AE820_eu* self)
{
    u8 out[0x20];
    s32 tmp[4];
    char str[0x20];
    u8 buf[0xC0];
    f32 adj;
    f32 d;
    s32 held;
    s32 c;
    const char* fmt;
    char* sp;
    f32 px;
    f32 py;

    if (self->f250 == 0) {
        return;
    }
    d = D_00261868 - self->f254;
    if (self->f250 == 2) {
        if (D_00272420 == self->f250) {
            self->f260 = d < 2.0f;
        }
    }
    if (self->f260 != 0) {
        adj = (1.0f - D_eu_0027939C) * 54.305084f;
    } else {
        adj = 0.0f;
        if (self->f250 == 2) {
            if (1.0f < d) {
                if (func_0018B770(D_00269990) == 0) {
                    self->vtbl[0x3C / 4](self);
                }
            }
        }
    }
    held = self->f208;
    px = self->f234;
    py = self->f238;
    func_00137228(out, self->f21c, self->f220 + adj);
    func_00137238(out, px, py);
    tmp[0] = held;
    func_00137248(out, tmp);
    func_00137260(out, 0);
    func_00137268(out, 0);
    func_eu_001374E0(out, 0);
    fmt = "%c&1^07~b2a83d%d%%&.";
    sp = str;
    c = func_001AEA08();
    func_001E1FD0(sp, fmt, c, func_00160B28(D_002623C0));
    func_0015C8B8(self->f4, self->f20c, self->f20c);
    func_0015DB28(buf, sp, self->f4, 0);
    func_eu_0015E7E0(buf, out, 0, D_00262280);
    func_0015C900(self->f4);
}
