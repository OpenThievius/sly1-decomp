// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the fields from 0x218 on sit 0x310 bytes further on, and the screen's height and its
// scale are PAL's (468.6 for 492.8, 1.0926 and 0.9153 for 0.9091 and 1.1).
struct Self_1AAB60_eu;
struct Vt_1AAB60_eu { u8 p[0x48]; s32 (*m48)(Self_1AAB60_eu*, Self_1AAB60_eu*); };
struct Self_1AAB60_eu {
    Vt_1AAB60_eu* vt;
    u8 p0[0x218 + 0x310 - 4];
    Rec_1AAB60* f218;
    f32 f21C; f32 f220; f32 f224; f32 f228; f32 f22C; f32 f230; f32 f234; f32 f238;
    u8 p1[0x250 - 0x23C];
    s32 f250;
};

void func_001AAEC0(Self_1AAB60_eu* self);

void func_001AAB60(Self_1AAB60_eu* self) {
    Rec_1AAB60* r = self->f218;
    f32 x0 = 0.0f;
    f32 x1 = 640.0f;
    f32 y1 = 468.61016845703125f;
    f32 y0 = x0;

    if (r->fC != -1) {
        Self_1AAB60_eu** objs = (Self_1AAB60_eu**)D_002486B0;
        Rec_1AAB60* recs = (Rec_1AAB60*)&D_0026C3E0;
        do {
            Self_1AAB60_eu* o = objs[r->fC];
            if (o->vt->m48(o, self)) {
                switch (r->f10) {
                case 0:
                    if (o->f234 != 0.0f) x0 = o->f21C + o->f234;
                    break;
                case 1:
                    if (o->f234 != 0.0f) x1 = o->f21C;
                    break;
                case 2:
                    if (o->f238 != 0.0f) y0 = o->f220 + o->f238;
                    break;
                case 3:
                    if (o->f238 != 0.0f) y1 = o->f220;
                    break;
                }
                break;
            }
            r = &recs[r->fC];
        } while (r->fC != -1);
    }
    f32 a = self->f218->f0;
    if (a == 0.0f) {
        self->f224 = (x1 - x0 - self->f234) * 0.5f;
    } else if (0.0f < a) {
        self->f224 = x0 + a;
    } else {
        self->f224 = x1 + a - self->f234;
    }
    f32 b = self->f218->f4;
    if (b == 0.0f) {
        self->f228 = (y1 - y0 - self->f238) * 0.5f;
    } else if (0.0f < b) {
        self->f228 = y0 + b;
    } else {
        self->f228 = y1 + b - self->f238;
    }
    f32 t = func_001EAF28(self->f228 * 1.0925925970077515f) * 0.9152542352676392f;
    self->f22C = self->f224;
    self->f228 = t;
    self->f230 = t;
    switch (self->f218->f8) {
    case 0: self->f22C = -self->f234; break;
    case 1: self->f22C = 640.0f; break;
    case 2: self->f230 = -self->f238; break;
    case 3: self->f230 = 468.61016845703125f; break;
    }
    s32 m = self->f250;
    if (m != 0) {
        if (m == 2) {
            self->f21C = self->f224;
            self->f220 = self->f228;
        }
    } else {
        self->f21C = self->f22C;
        self->f220 = self->f230;
    }
    func_001AAEC0(self);
}
