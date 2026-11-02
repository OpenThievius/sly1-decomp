// SPDX-License-Identifier: AGPL-3.0-or-later
// PAL: the object fields sit 0x310 bytes later (0x568..0x57C); the best-time text is a
// translated label (text id 0xAB) followed by the formatted time, built in a 16-bit string
// on the stack, and the opening line is text id 0xA9.
struct Obj_1E02C8_eu { VT_1E02C8* vt; u8 pad04[0x564]; f32* f568; s32 f56C_pad; s32 f570; f32 f574; s32 f578; s32 f57C; };
struct Obj2_1E02C8_eu { VT_1E00B0* vt; u8 pad04[0x574]; f32 f578; };
const char* func_eu_001DDAB0(s32 id);
u16* func_eu_001E3050(u16* dst, const char* src);
u16* func_eu_001E3178(u16* dst, const u8* src);
s32 func_001E1FD0(char* dst, const char* fmt, ...);
void func_001AA8B8(Obj_1E02C8_eu* o, f32 v);

void func_001E02C8(Obj_1E02C8_eu* self, s32 n)
{
    if (self->f570 == n) {
        return;
    }
    switch (self->f570) {
    case 1:
        if (self->f57C != 0) {
            self->vt->m3C(self);
            self->f57C = 0;
        }
        break;
    case 2:
        func_001AB958(&D_0026E760);
        D_0026E760.vt->m3C(&D_0026E760);
        self->vt->m3C(self);
        break;
    }
    switch (n) {
    case 2: {
        f32 zero = 0.0f;
        f32 one = 1.0f;
        func_001BFCD8(0x6D, 0, 0, 0, 3000.0f, 300.0f, one, zero, zero, 0, 0);
        func_00160C48(0);
        func_001DDAD0(D_00275710);
        func_001AB890(&D_0026E760, D_00275710->f230C + 0.99f);
        func_001AB920(&D_0026E760, -func_00205C78(2.0f, (f32)D_002623DC));
        func_001AB928(&D_0026E760, zero, 0);
        func_001AB938(&D_0026E760);
        Cam_1E00B0* cam = D_002623C8;
        if (cam->flags & 8) {
            char time[32];
            u16 text[128];
            f32 t = cam->f08;
            if (t < one) {
                func_001E1FD0(time, " &10.%d", (s32)(t * 10.0f));
            } else {
                s32 s = (s32)t;
                s32 minutes = s / 60;
                s32 seconds = s % 60;
                func_001E1FD0(time, " &1%d:%02d", minutes, seconds);
            }
            func_eu_001E3050(text, func_eu_001DDAB0(0xAB));
            func_eu_001E3178(text, (u8*)time);
            func_001AA8B8(self, zero);
            self->vt->m20(self, text);
        } else {
            func_001AA8B8(self, 5.0f);
            self->vt->m20(self, (void*)func_eu_001DDAB0(0xA9));
        }
        self->vt->m38(self);
        break;
    }
    case 3: {
        Obj2_1E02C8_eu* o = (Obj2_1E02C8_eu*)&D_0026E760;
        s32 id;
        f32 t = o->f578;
        if (0.0f < t) {
            Cam_1E00B0* cam = D_002623C8;
            if (cam->flags & 8) {
                if (cam->f08 < t) {
                    cam->f08 = t;
                    id = 0x1D;
                    func_0018C7F8(&D_00264A40);
                } else {
                    id = 0x1E;
                }
            } else {
                id = 0x1B;
                cam->flags |= 8;
                cam->f08 = o->f578;
                D_002623C4->f440 = D_002623C4->f440 + 1;
                if (func_001602A0() & 8) {
                    func_001604B8(8);
                    func_0018C7F8(&D_00264A40);
                }
            }
        } else {
            id = 0x1C;
            if (D_002623C8->flags & 8) {
                id = 0x1E;
            }
        }
        func_00194D30(&D_0026FF68, 0, id);
        break;
    }
    }
    self->f570 = n;
    self->f574 = *self->f568;
    if (n == 2) {
        func_00148CE0(D_00275710);
    }
    self->f578 = (self->f570 != 0);
}
