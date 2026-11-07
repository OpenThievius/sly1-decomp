// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL's state change of a sliding UI object: picks the new position and speed for the mode and notifies.
struct Obj_eu_1AA998;
struct Vt_eu_1AA998 {
    void* s[11];
    f32 (*m2C)(Obj_eu_1AA998* self);
    void* s12;
    f32 (*m34)(Obj_eu_1AA998* self);
};
void PlaceScreenElement(Obj_eu_1AA998* self);

struct Obj_eu_1AA998 {
    Vt_eu_1AA998* vt;
    u8 pad0[0x52C - 4];
    f32 f52C;
    f32 f530;
    f32 f534;
    f32 f538;
    f32 f53C;
    f32 f540;
    u8 pad1[0x54C - 0x544];
    f32 f54C;
    u8 pad2[0x55C - 0x550];
    f32 f55C;
    s32 f560;
    f32 f564;
    f32* f568;
};

void SetScreenElementMode(Obj_eu_1AA998* self, s32 mode)
{
    if (self->f560 == mode) {
        return;
    }
    s32 notify = 0;
    switch (mode) {
    case 1:
    case 3:
        if (mode == 1) {
            self->f55C = self->f54C * self->vt->m2C(self);
        } else {
            self->f55C = (1.0f - self->f54C) * self->vt->m34(self);
        }
        if (self->f560 == 0 || self->f560 == 2) {
            notify = 1;
        }
        break;
    case 2:
        notify = 1;
        self->f52C = self->f534;
        self->f530 = self->f538;
        self->f54C = 1.0f;
        self->f55C = 0.0f;
        break;
    case 0:
        notify = 1;
        self->f52C = self->f53C;
        self->f530 = self->f540;
        self->f54C = 0.0f;
        self->f55C = 0.0f;
        break;
    }
    self->f560 = mode;
    self->f564 = *self->f568;
    if (notify) {
        PlaceScreenElement(self);
    }
}
