// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: state and timer are at 0x570 and 0x574 (US 0x260), and the packed tail word at 0x974 (US 0x464).
struct __attribute__((packed)) Tail_1356C0_eu { u8 pad0[0x974]; s32 v; };
struct Obj_1356C0_eu { u8 pad0[0x570]; s32 state; f32 timer; };

void func_00131140(Obj_1356C0_eu* self);

void func_001356C0(Obj_1356C0_eu* self, s32 mode)
{
    if (mode != self->state) {
        if (self->state != 1) {
            if (self->state < 2) {
                if (self->state == 0) {
                    func_00131140(self);
                }
            }
        } else {
            func_001BFCD8(0x8F, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
        switch (mode) {
        case 1:
            func_001BFCD8(0x8E, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
            self->state = mode;
            break;
        case 4:
            ((Tail_1356C0_eu*)&D_0026F138)->v = 0;
            D_0026F138.vtbl[15](&D_0026F138);
            self->state = mode;
            break;
        default:
            self->state = mode;
            break;
        }
        self->timer = D_0026185C;
    }
}
