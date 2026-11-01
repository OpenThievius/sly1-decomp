// SPDX-License-Identifier: AGPL-3.0-or-later
// When D_eu_0027F360 is 1, sets the +0x570 and +0x574 flags from D_eu_00263EEC and the float at +0x0C of D_eu_0026ABE8 and calls func_eu_001AED58 if they changed; then calls func_eu_001AAFE0 on self.
struct Pal_eu_001AEEA0 {
    u8 pad00[0xC];
    f32 f0C;
};

struct Obj_eu_001AEEA0 {
    u8 pad000[0x570];
    s32 flag;
    s32 value;
};

extern s32 D_eu_0027F360;
extern s32 D_eu_00263EEC;
extern Pal_eu_001AEEA0* D_eu_0026ABE8;
void func_eu_001AED58(void* self);
void func_eu_001AAFE0(void* self);

void func_eu_001AEEA0(Obj_eu_001AEEA0* self)
{
    s32 a0 = 0;
    s32 a1;

    if (1 == D_eu_0027F360) {
        a0 = (D_eu_00263EEC == 3);
        a1 = 0;
        if (D_eu_0026ABE8 != 0) {
            if (D_eu_0026ABE8->f0C != 0.0f) {
                a1 = 1;
            }
        }
        if (((a0 == 0) != (self->flag == 0)) || ((a1 == 0) != (self->value == 0))) {
            self->flag = a0;
            self->value = a1;
            func_eu_001AED58(self);
        }
    }
    func_eu_001AAFE0(self);
}
