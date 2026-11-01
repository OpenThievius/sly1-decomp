// SPDX-License-Identifier: AGPL-3.0-or-later
// Builds a title string on the stack (a name, a separator, an optional suffix), sets the colour at +0x518 and passes it to virtual slot 8.
struct Rgba_eu_1AED58 {
    u8 r, g, b, a;
};
struct Obj_eu_1AED58 {
    void** vt;
    u8 pad4[0x514];
    Rgba_eu_1AED58 color;
    u8 pad51C[0x54];
    s32 f570;
    s32 f574;
};
extern s32 D_eu_0027DBC8[];
extern u8 D_eu_0024E358[];
extern s32 D_eu_002636EC;
const char* func_eu_001DDAB0(s32 id);
u16* func_eu_001E3050(u16* dst, const char* src);
u16* func_eu_001E3178(u16* dst, const u8* src);
u16* func_eu_001E30A0(u16* dst, const char* src);

void func_eu_001AED58(Obj_eu_1AED58* self)
{
    u16 buf[256];
    Rgba_eu_1AED58 c;
    if (self->f570 != 0) {
        c.r = 0x6F;
        c.g = 0x6F;
        c.b = 0x6F;
        c.a = 0xFF;
        self->color = c;
        func_eu_001E3050(buf, func_eu_001DDAB0(D_eu_0027DBC8[self->f574 != 0]));
        func_eu_001E3178(buf, D_eu_0024E358);
        func_eu_001E30A0(buf, func_eu_001DDAB0(D_eu_0027DBC8[2]));
        if (D_eu_002636EC >= 2) {
            func_eu_001E3178(buf, D_eu_0024E358);
            func_eu_001E30A0(buf, func_eu_001DDAB0(5));
        }
    } else {
        c.r = 0x6F;
        c.g = 0x1F;
        c.b = 0x1F;
        c.a = 0xFF;
        self->color = c;
        func_eu_001E3050(buf, func_eu_001DDAB0(4));
    }
    ((void (*)(void*, u16*))self->vt[8])(self, buf);
}
