// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's overlay height is 468.61017 where US has 492.80002.
void func_001EFEE0(Emitter_1EFEE0* self)
{
    if (D_00275710 != 0 && D_00275F84 != 0) {
        s32 mode = self->mode;
        if (mode != 1) {
            if (mode < 2) {
                if (mode == 0) goto draw;
            }
            return;
        }
        if (D_002640A4 != 0) {
        func_00180398(D_002640A4, self->scale);
            return;
        }
        draw:
    f32 v = self->scale * 255.0f;
    func_0019DDA0(0, 0, 0, (s32)v, D_00262280, 0.0f, 0.0f, 640.0f, 468.61017f);
    }
}
