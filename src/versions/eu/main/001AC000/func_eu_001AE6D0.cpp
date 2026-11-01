// SPDX-License-Identifier: AGPL-3.0-or-later
// Changes the state at +0x560 (remapped by mode), starting or stopping two UI objects around the change, then applies it with func_001AA998.
struct VT_eu_1AE6D0 { u8 pad0[0x40]; void (*fn40)(void* self, s32 v); };
struct Ui_eu_1AE6D0 { VT_eu_1AE6D0* vtbl; u8 pad4[0x56C]; s32 f570; u8 pad574[0x974 - 0x574]; s32 f974; };
struct Game_eu_1AE6D0 { u8 pad0[0x19D8]; s32 f19D8; s32 f19DC; };
struct Obj_eu_1AE6D0 { u8 pad0[0x560]; s32 f560; };

extern s32 D_eu_0027F700[];
extern s32 D_eu_0027F270;
extern Game_eu_1AE6D0* D_eu_002636F0;
extern s32 D_eu_00276448;
extern Ui_eu_1AE6D0 D_eu_00273978;
extern Ui_eu_1AE6D0 D_eu_0027CFE8;
void func_eu_001ADE38(void* ui, s32 a, s32 b);
void func_001AA8B8(void* self, f32 v);

void func_eu_001AE6D0(Obj_eu_1AE6D0* self, s32 st)
{
    if (self->f560 != st) {
        if (D_eu_0027F700[1] == 1) {
            if (st == 3 || st == 0) {
                st = self->f560;
            }
        }
        if (D_eu_0027F700[1] == 3) {
            if ((u32)(st - 1) < 2) {
                st = 0;
                if ((D_eu_0027F270 & 8) == 0) {
                    st = 2;
                    if (D_eu_002636F0->f19D8 != 0 && D_eu_00276448 == 0) {
                        Ui_eu_1AE6D0* ui = &D_eu_00273978;
                        ui->f570 = 0;
                        ui->vtbl->fn40(ui, 0);
                        func_eu_001ADE38(ui, D_eu_002636F0->f19D8, D_eu_002636F0->f19DC);
                        ui->f974 = 1;
                        func_001AA8B8(ui, 0.0f);
                        ui->vtbl->fn40(ui, 2);
                    }
                }
            }
        }
        if (self->f560 != st && st == 0) {
            if (D_eu_00273978.f974 != 0) {
                D_eu_00273978.vtbl->fn40(&D_eu_00273978, 0);
            }
            if (D_eu_0027CFE8.f570 != 0) {
                D_eu_0027CFE8.vtbl->fn40(&D_eu_0027CFE8, 0);
            }
        }
    }
    func_001AA998(self, st);
}
