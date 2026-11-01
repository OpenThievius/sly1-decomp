// SPDX-License-Identifier: AGPL-3.0-or-later
// NEAR (only in PAL): python3 tools/check.py nonmatching/eu/func_eu_001AE138.cpp func_eu_001AE138 --unit src/main/001AC000.cpp
// Still differs: Label draw with slide-in offset and backdrop box; ours 24 bytes longer (732 vs 708): &L still cached in extra saved registers (s0/s4) where retail recomputes addiu a0,sp,16.
// Draws a label with a slide-in offset; when the owner is absent also draws a translucent backdrop box, then the text.
struct __attribute__((packed)) PW_eu_1AE138 { s32 v; };
struct Actor_eu_1AE138 {
    u8 pad0[4]; void* p4; u16 f08; u8 pad1[0x518 - 0xA]; PW_eu_1AE138 col; f32 f51C; u8 pad2[0x534 - 0x520];
    f32 f534; f32 f538; u8 pad3[0x544 - 0x53C]; f32 f544; f32 f548; f32 f54C;
    u8 pad4[0x974 - 0x550]; void* f974;
};
struct Local_eu_1AE138 { f32 x; f32 y; u8 pad[0x18]; s32 tmp; };
struct Globals_eu_1AE138 { u8 pad0[0x560]; s32 f560; u8 pad1[0xC]; s32 f570; };
struct Mode_eu_1AE138 { u8 pad0[0x56C]; s32 f56C; struct Owner_eu_1AE138* f570; };
struct Owner_eu_1AE138 { u8 pad0[0x2D0]; s32 f2D0; };
extern Globals_eu_1AE138 D_eu_00275E98;
extern Mode_eu_1AE138 D_eu_00274868;
extern f32 D_eu_0027939C;
extern u8 D_eu_00263590[];
void func_eu_001374E0(void* out, s32 v);
void func_eu_0015DCB8(void* buf, void* name, void* p, s32 zero);
void func_eu_0015E7E0(void* buf, void* out, s32 zero, void* d);
void func_eu_00161A20(void* ctx, s32 a, s32 b, u64 c);
void func_eu_00161D68(void* ctx, s32 a, s64 b);
void func_eu_00161AB8(void* ctx, s32 color);
void func_eu_00161C50(void* ctx, s32 a, s32 b, s32 c, s32 d);

void func_eu_001AE138(Actor_eu_1AE138* self)
{
    PW_eu_1AE138 c;
    Local_eu_1AE138 L;
    u8 buf[0xC0];
    f32 phase;
    f32 slide;
    f32 f12;
    if (self->f08 == 0) {
        return;
    }
    if (D_eu_00275E98.f560 != 0) {
        if ((u32)(D_eu_00275E98.f570 - 1) < 2) {
            return;
        }
    }
    if (self->f974 != 0) {
        phase = 1.0f;
        slide = (phase - D_eu_0027939C) * 54.305084f;
    } else {
        phase = self->f54C;
        slide = 0.0f;
    }
    c = self->col;
    ((u8*)&c)[3] = (u8)((f32)((u8*)&c)[3] * phase);
    f32 f544 = self->f544;
    f32 f548 = self->f548;
    s32 s0v = c.v;
    func_00137228(&L, self->f534, self->f538 + slide);
    func_00137238(&L, f544, f548);
    L.tmp = s0v;
    func_00137248(&L, &L.tmp);
    func_00137260(&L, 0);
    func_00137268(&L, 0);
    func_eu_001374E0(&L, 0);
    if (self->f974 == 0) {
        u8* ctx = D_eu_00263590;
        f32 a = phase;
        if (D_eu_00274868.f56C != 0 && D_eu_00274868.f570 != 0 && D_eu_00274868.f570->f2D0 == 2) {
            a = 1.0f;
        }
        f32 y = slide + 468.61017f;
        ((u8*)&L.tmp)[0] = 0;
        ((u8*)&L.tmp)[1] = 0;
        ((u8*)&L.tmp)[2] = 0;
        ((u8*)&L.tmp)[3] = (u8)(a * 64.0f);
        func_eu_00161A20(ctx, 0x46, 5, 0x441EE);
        y = y - 54.305084f;
        func_eu_00161D68(ctx, 0x47, 0x30000);
        func_eu_00161D68(ctx, 0x42, 0x44);
        func_eu_00161AB8(ctx, L.tmp);
        y = (y * 0.5462963f + 1920.0f) * 16.0f;
        func_eu_00161C50(ctx, 0x6C00, (s32)y, 0xFFFFFF0, 0);
        func_eu_00161C50(ctx, 0x9400, 0x8800, 0xFFFFFF0, 0);
    }
    f12 = self->f51C;
    func_0015C8B8(self->p4, f12, f12);
    func_eu_0015DCB8(buf, (u8*)self + 8, self->p4, 0);
    func_eu_0015E7E0(buf, &L, 0, D_eu_00263590);
    func_0015C900(self->p4);
}
